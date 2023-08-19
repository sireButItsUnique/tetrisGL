#include <TETRIS/game.hpp>

Game::Game() {
	srand(time(0));
	renderer = new Renderer();
	renderer->addBlock(0, 0, 1);
	renderer->addBlock(1, 0, 2);
	renderer->addBlock(2, 0, 3);
	renderer->addBlock(3, 0, 4);
	renderer->addBlock(4, 0, 5);
	renderer->addBlock(5, 0, 6);
	renderer->addBlock(6, 0, 7);
	renderer->render();
}

// BOARD
void Game::genNextPiece() {
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
};

void Game::rotate(){

};

void Game::move(int x, int y){

};

void Game::swap(){

};

void Game::step(){

};
// INPUT
void Game::getInput(GLFWwindow *window) {

	// ESC: pause game
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		escDown = true;
	}
	if (escDown && glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_RELEASE) {
		escDown = false;
		renderer->clearBlocks();
		pauseAudio(bgmEnabled);
	}
}

// VISUAL
void Game::render() {

	// clear field
	renderer->clearBlocks();

	// add field blocks
	for (int row = 0; row <= 24; row++) {
		for (int col = 0; col <= 10; col++) {
			if (placed[row][col]) {
				renderer->addBlock(col, row, placed[row][col]);
			}
		}
	}

	// add cur block
	for (auto &block : curPiece->getPos()) {
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