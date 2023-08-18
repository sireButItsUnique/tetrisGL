#include "./game.cpp"
#include "./home.cpp"
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <iostream>
#include <string>

int main(void) {

	// init window
	glfwInit();
	GLFWwindow *window;
	window = glfwCreateWindow(640, 480, "TetrisGL", NULL, NULL);
	glfwMakeContextCurrent(window);

	Game *game = new Game();
	// game->initAudio();

	// main game loop
	while (!glfwWindowShouldClose(window)) {
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}