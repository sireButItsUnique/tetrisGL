#include <TETRIS/game.hpp>

Game::Game() {
	srand(time(0));
	renderer = new Renderer();
}

// BOARD
void Game::genNextPiece() {

	// get random block
	switch (rand() % 7) {
	case 1:
		next.push(new Square());
		break;
	case 2:
		next.push(new T());
		break;
	case 3:
		next.push(new Line());
		break;
	case 4:
		next.push(new LeftL());
		break;
	case 5:
		next.push(new RightL());
		break;
	case 6:
		next.push(new LeftZ());
		break;
	case 7:
		next.push(new RightZ());
		break;
	}

	// everytime a block is generated allow swap again
	swapped = false;
};

void Game::place() {

	// flash block into placed
	for (std::pair<int, int> block : curPiece->getPos()) {
		placed[block.second][block.first] = curPiece->getId();
	}

	// rmv cur block + replace with next
	curPiece = next.front();
	next.pop();
	genNextPiece();

	// render new block
	for (std::pair<int, int> block : curPiece->getPos()) {
		if (placed[block.second][block.first]) {
			std::cout << "bro u suck ass" << std::endl;
		}
		renderer->addBlock(block.first, block.second, curPiece->getId());
	}

	renderer->render();
}

void Game::step() { move(0, 1); };

// ACTIONS
void Game::rotate() {

	// cant simulate movement -> acty do it then rotate it back
	curPiece->rotate();

	// test if collided with bounds or other block
	bool collided = false;
	for (std::pair<int, int> block : curPiece->getPos()) {
		std::cout << "row " << block.second << ", col " << block.first
				  << std::endl;
		if (block.first >= 0 && block.first <= 9 && block.second >= 0 &&
			block.second <= 23) {
			if (placed[block.second][block.first]) {
				collided = true;
				break;
			}
		} else {
			collided = true;
			break;
		}
	}

	if (collided) {
		curPiece->rotate();
		curPiece->rotate();
		curPiece->rotate();
		return;
	}

	// render the rotation
	for (int i = 0; i < 4; i++) {
		renderer->rmvLastBlock();
	}

	// add cur block
	for (std::pair<int, int> block : curPiece->getPos()) {
		renderer->addBlock(block.first, block.second, curPiece->getId());
	}

	renderer->render();
};

void Game::move(int x, int y) {

	// simulate movement
	Piece *shadow = new Piece(*curPiece);
	shadow->move(x, y);

	// test if collided with bounds or other block
	bool collided = false;
	for (std::pair<int, int> block : shadow->getPos()) {
		if (block.first >= 0 && block.first <= 9 && block.second >= 0 &&
			block.second <= 23) {
			if (placed[block.second][block.first]) {
				collided = true;
				break;
			}
		} else {
			collided = true;
			break;
		}
	}

	if (collided) {
		if (y) {
			place();
		}
		return;
	} else {
		curPiece->move(x, y);
	}

	// render the move
	for (int i = 0; i < 4; i++) {
		renderer->rmvLastBlock();
	}

	// add cur block
	for (std::pair<int, int> block : curPiece->getPos()) {
		renderer->addBlock(block.first, block.second, curPiece->getId());
	}

	renderer->render();
};

void Game::swap() {
	if (!swapped) {
		swapped = true;
	}
};

void Game::instaDrop() {
	while (true) {
		// simulate movement
		Piece *shadow = new Piece(*curPiece);
		shadow->move(0, 1);

		// test if collided with bounds or other block
		bool collided = false;
		for (std::pair<int, int> block : shadow->getPos()) {
			if (block.first >= 0 && block.first <= 9 && block.second >= 0 &&
				block.second <= 23) {
				if (placed[block.second][block.first]) {
					collided = true;
					break;
				}
			} else {
				collided = true;
				break;
			}
		}

		// has collided -> render the placed piece at its new pos
		if (collided) {
			// render the move
			for (int i = 0; i < 4; i++) {
				renderer->rmvLastBlock();
			}

			// add cur block
			for (std::pair<int, int> block : curPiece->getPos()) {
				renderer->addBlock(block.first, block.second,
								   curPiece->getId());
			}

			renderer->render();
			place();
			return;
		}
		curPiece = shadow;
	}
}

// INPUT
void Game::getInput(GLFWwindow *window) {

	// ESC: pause game
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		escDown = true;
	}
	if (escDown && glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_RELEASE) {
		escDown = false;
		pauseAudio(!paused);

		// scuffed pause/unpause
		paused = !paused;
		if (paused) {
			renderer->clearBlocks();
			renderer->render();
		} else {
			render();
		}
	}

	// DOWN: move down
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		downDown = true;
	}
	if (downDown && (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_RELEASE)) {
		downDown = false;
		move(0, 1);
	}

	// UP: rotate
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		upDown = true;
	}
	if (upDown && (glfwGetKey(window, GLFW_KEY_UP) == GLFW_RELEASE)) {
		upDown = false;
		rotate();
	}

	// LEFT: move left
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		leftDown = true;
	}
	if (leftDown && glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_RELEASE) {
		leftDown = false;
		move(-1, 0);
	}

	// RIGHT: move right
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		rightDown = true;
	}
	if (rightDown && glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_RELEASE) {
		rightDown = false;
		move(1, 0);
	}

	// SPACE: insta drop
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		spaceDown = true;
	}
	if (spaceDown && glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE) {
		spaceDown = false;
		instaDrop();
	}
}

// VISUAL
void Game::render() {

	// clear field
	renderer->clearBlocks();

	// add field blocks
	for (int row = 0; row < 24; row++) {
		for (int col = 0; col < 10; col++) {
			if (placed[row][col]) {
				renderer->addBlock(col, row, placed[row][col]);
			}
		}
	}

	// add cur block
	for (std::pair<int, int> block : curPiece->getPos()) {
		renderer->addBlock(block.first, block.second, curPiece->getId());
	}

	renderer->render();
}

void Game::draw() {

	// draw black bg
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// draw blocks
	renderer->draw();
}

// DATA
void Game::loadGame(std::string savedGame) {}

void Game::newGame() {

	// create empty board
	placed = std::vector<std::vector<int>>(24, std::vector<int>(10, 0));
	swapped = false;

	// set all keys to false
	paused = false;
	escDown = false;
	leftDown = false;
	rightDown = false;
	downDown = false;
	cDown = false;
	spaceDown = false;

	// init some pieces
	for (int i = 0; i < 4; i++) {
		next.push(new Line());
		next.push(new LeftL());
		next.push(new T());
		// genNextPiece();
	}
	curPiece = next.front();
	next.pop();
	this->render();
}