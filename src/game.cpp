#include "./piece.cpp"
#include <AUDIO/bgm.h>
#include <GL/glad.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <vector>

class Game {
  private:
	bool bgmEnabled = true;
	bool escDown = false;

  public:
	Game() {}

	// INPUT
	void getInput(GLFWwindow *window) {

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
	void draw() {

		// draw black bg
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// draw blocks
	}
};