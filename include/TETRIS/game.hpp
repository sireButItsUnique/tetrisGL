#include <AUDIO/bgm.h>
#include <GL/glad.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <RENDER/Renderer.hpp>
#include <TETRIS/piece.hpp>
#include <algorithm>
#include <iostream>
#include <queue>
#include <random>
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
	void genNextPieceSet();
	void place();
	void step();
	void clearLine(int row);

	// ACTIONS
	void pause();
	void rotate();
	void instaDrop();
	void move(int x, int y);
	void swap();

	// INPUT
	void getInput(GLFWwindow *window);

	// VISUAL
	void render();
	void renderGhost();
	void draw();

	// DATA
	void loadGame(std::string savedGame);
	void newGame();
};