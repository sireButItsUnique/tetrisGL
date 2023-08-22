#include <TETRIS/game.hpp>

Game::Game() {
	srand(time(0));
	renderer = new Renderer();
}

// BOARD
void Game::genNextPieceSet() {

	// create set with every piece then shuffle
	std::vector<Piece *> set = {new Square(), new T(),		new Line(),
								new LeftL(),  new RightL(), new LeftZ(),
								new RightZ()};
	std::shuffle(set.begin(), set.end(), std::default_random_engine(time(0)));
	for (int i = 0; i < 7; i++) {
		next.push(set[i]);
	}
};

void Game::place() {

	// flash block into placed
	for (std::pair<int, int> block : curPiece->getPos()) {
		placed[block.second][block.first] = curPiece->getId();
	}

	// clear new line
	for (int row = 23; row >= 0; row--) {

		bool missing = false;
		for (int col = 0; col < 10; col++) {
			if (!placed[row][col]) {
				missing = true;
				break;
			}
		}

		if (!missing) {
			clearLine(row);
			row++;
		}
	}

	// allow new block to be swapped
	swapped = false;

	// rmv cur block + replace with next
	curPiece = next.front();
	next.pop();
	if (next.size() <= 7) {
		genNextPieceSet();
	}

	// render new block
	for (std::pair<int, int> block : curPiece->getPos()) {
		if (placed[block.second][block.first]) {
			std::cout << "bro u suck ass" << std::endl;
		}
		renderer->addBlock(block.first, block.second, curPiece->getId());
	}

	renderGhost();
	render();
}

void Game::step() { move(0, 1); };

void Game::clearLine(int row) {
	for (int r = row; r >= 1; r--) {
		placed[r] = placed[r - 1];
	}
	placed[0] = {};
}

void Game::tick() {
	if (!paused) {

		// tick block
		auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(
			std::chrono::high_resolution_clock::now() - lastTick);
		if (diff.count() >= 1000) {
			step();
			lastTick = std::chrono::high_resolution_clock::now();
		}
	}
}

// ACTIONS
void Game::pause() {

	// update state
	paused = !paused;

	// update audio
	pauseAudio(paused);

	// update visuals
	if (paused) {
		renderer->clearBlocks();
		renderer->clearGhost();
		renderer->render();
	} else {
		render();
	}
}

void Game::rotate() {

	// cant simulate movement -> acty do it then rotate it back
	curPiece->rotate();

	// test if collided with bounds or other block
	bool collided = false;
	for (std::pair<int, int> block : curPiece->getPos()) {
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

	renderGhost();
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

	renderGhost();
	renderer->render();
};

void Game::swap() {
	if (!swapped) {

		if (!swapPiece) {
			std::cout << "triggered";
			swapPiece = curPiece;
			curPiece = next.front();
			next.pop();
		} else {
			Piece *buffer = curPiece;
			curPiece = swapPiece;
			swapPiece = buffer;
		}

		// reset swap piece to initial position
		swapPiece->reset();

		// render it
		render();
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
		pause();
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

	// SPACE: insta drop
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		spaceDown = true;
	}
	if (spaceDown && glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE) {
		spaceDown = false;
		instaDrop();
	}

	// C: swap
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
		cDown = true;
	}
	if (cDown && glfwGetKey(window, GLFW_KEY_C) == GLFW_RELEASE) {
		cDown = false;
		swap();
	}
}

// VISUAL
void Game::renderGhost() {

	// delete old ghost
	renderer->clearGhost();

	// simulate insta drop
	Piece *shadow = new Piece(*curPiece);
	while (true) {
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

			// render the ghost
			shadow->move(0, -1);
			renderer->renderGhost(shadow);
			return;
		}
	}
}

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

	renderGhost();
	renderer->renderBorders();
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
	lastTick = std::chrono::high_resolution_clock::now();
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
		genNextPieceSet();
	}
	curPiece = next.front();
	swapPiece = nullptr;
	next.pop();
	this->render();
}