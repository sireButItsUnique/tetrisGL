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
	Game();

	// INPUT
	void getInput(GLFWwindow *window);

	// VISUAL
	void draw();
};