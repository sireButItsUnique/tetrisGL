#include <TETRIS/game.hpp>

Game::Game() {
	renderer = new Renderer();
	renderer->addBlock(0, 0, 0);
	renderer->addBlock(1, 1, 0);
	renderer->addBlock(2, 0, 0);
	renderer->addBlock(1, 0, 0);
	renderer->render();
}

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
void Game::draw() {

	// draw black bg
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// draw blocks
	renderer->draw();
}