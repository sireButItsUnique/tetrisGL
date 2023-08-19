#include <AUDIO/bgm.h>
#include <GL/glad.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <RENDER/Renderer.hpp>
#include <TETRIS/piece.hpp>
#include <cstdlib>
#include <queue>
#include <time.h>
#include <vector>

class Game {
  private:
	std::vector<std::vector<int>> placed =
		std::vector<std::vector<int>>(24, std::vector<int>(10, 0));
	Piece *curPiece;
	Piece *swapPiece;
	std::queue<Piece *> next;

	bool swapped = false;
	bool bgmEnabled = true;
	bool escDown = false;
	Renderer *renderer;

  public:
	Game();

	// BOARD
	void genNextPiece();
	void rotate();
	void move(int x, int y);
	void swap();
	void step();

	// INPUT
	void getInput(GLFWwindow *window);

	// VISUAL
	void render();
	void draw();
};