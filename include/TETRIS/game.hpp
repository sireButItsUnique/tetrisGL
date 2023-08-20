#include <AUDIO/bgm.h>
#include <GL/glad.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <RENDER/Renderer.hpp>
#include <TETRIS/piece.hpp>
#include <cstdlib>
#include <iostream>
#include <queue>
#include <time.h>
#include <vector>

class Game {
  private:
	std::vector<std::vector<int>> placed;
	Piece *curPiece;
	Piece *swapPiece;
	std::queue<Piece *> next;

	bool swapped;
	bool paused;
	bool escDown;
	bool leftDown;
	bool rightDown;
	bool upDown;
	bool downDown;
	bool cDown;
	bool spaceDown;
	Renderer *renderer;

  public:
	Game();

	// BOARD
	void genNextPiece();
	void place();
	void step();

	// ACTIONS
	void rotate();
	void instaDrop();
	void move(int x, int y);
	void swap();

	// INPUT
	void getInput(GLFWwindow *window);

	// VISUAL
	void render();
	void draw();

	// DATA
	void loadGame(std::string savedGame);
	void newGame();
};