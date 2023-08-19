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
	for (auto &block : curPiece->getPos()) {
		placed[block.second][block.second] = curPiece->getId();
	}

	// rmv cur block + replace with next
	curPiece = next.front();
	next.pop();
	genNextPiece();
}

void Game::step(){

};

// ACTIONS
void Game::rotate(){

};

void Game::move(int x, int y){

};

void Game::swap() {
	if (!swapped) {
		swapped = true;
	}
};

// INPUT
void Game::getInput(GLFWwindow *window) {

	// ESC: pause game
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		escDown = true;
	}
	if (escDown && glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_RELEASE) {
		escDown = false;
		pauseAudio(bgmEnabled);
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
				std::cout << "added" << std::endl;
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
	bgmEnabled = true;
	escDown = false;

	// init some pieces
	for (int i = 0; i < 4; i++) {
		genNextPiece();
	}
	curPiece = next.front();
	next.pop();
	this->render();
}