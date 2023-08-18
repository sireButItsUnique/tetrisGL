#include "./game.cpp"
#include "./home.cpp"
#include <GL/glad.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <Windows.h>
#include <iostream>
#include <string>
#include <thread>

int main(void) {

	// init window
	glfwInit();
	GLFWwindow *window;
	window = glfwCreateWindow(400, 800, "TetrisGL", NULL, NULL);
	glfwMakeContextCurrent(window);

	// init openGL
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glViewport(0, 0, 400, 800);

	// init game
	Game *game = new Game();
	game->initAudio();

	// main game loop
	while (!glfwWindowShouldClose(window)) {

		// input
		game->getInput(window);

		// rendering
		game->render();

		// updates window
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}