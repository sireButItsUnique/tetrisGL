#include "./piece.cpp"
#include <AUDIO/bgm.h>
#include <GL/glad.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <RENDER/Renderer.hpp>
#include <vector>

class Game {
  private:
	bool bgmEnabled = true;
	bool escDown = false;
	Renderer *renderer;

  public:
	Game() {
		renderer = new Renderer();
		renderer->addBlock(0, 0, 0);
		renderer->addBlock(1, 1, 0);
		renderer->addBlock(2, 0, 0);
		renderer->addBlock(1, 0, 0);
		renderer->render();
	}

	// INPUT
	void getInput(GLFWwindow *window) {

		// ESC: pause game
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			escDown = true;
		}
		if (escDown && glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_RELEASE) {
			escDown = false;
			renderer->addBlock(0, 5, 0);
			renderer->addBlock(1, 6, 0);
			renderer->addBlock(2, 5, 0);
			renderer->addBlock(1, 5, 0);
			renderer->render();
			pauseAudio(bgmEnabled);
		}
	}

	// VISUAL
	void draw() {

		// draw black bg
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// draw blocks
		renderer->draw();
	}
};