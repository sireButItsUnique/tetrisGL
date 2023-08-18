#include "./piece.cpp"
#include <GL/glad.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <Windows.h>
#include <iostream>

class Game {
  private:
	bool bgmEnabled = true;
	bool escDown = false;

  public:
	Game() {}

	// AUDIO
	void initAudio() {
		mciSendStringA(
			"open \"D:\\robert2021\\projects\\tetrisGL\\src\\assets\\bgm.mp3\" "
			"type mpegvideo alias bgm",
			NULL, 0, NULL);
		mciSendStringA("play bgm repeat", NULL, 0, NULL);
	}

	void pauseAudio() {
		if (bgmEnabled) {
			mciSendStringA("pause bgm", NULL, 0, NULL);
		} else {
			mciSendStringA("resume bgm", NULL, 0, NULL);
		}
		bgmEnabled = !bgmEnabled;
	}

	// INPUT
	void getInput(GLFWwindow *window) {

		// ESC: pause game
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			escDown = true;
		}
		if (escDown && glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_RELEASE) {
			escDown = false;
			pauseAudio();
		}
	}

	// RENDERING
	void render() {
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		float vertices[] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f,
							0.0f,  0.0f,  0.5f, 0.0f};

		unsigned int VBO;
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,
					 GL_STATIC_DRAW);
	}
};