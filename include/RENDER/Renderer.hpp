#include <GL/glad.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <TETRIS/piece.hpp>
#include <UTIL/LoadShaders.h>
#include <iostream>
#include <vector>

class Renderer {
  private:
	unsigned int vVBO;
	unsigned int cVBO;
	unsigned int ghostvVBO;
	unsigned int ghostcVBO;
	unsigned int swapvVBO;
	unsigned int swapcVBO;
	std::vector<float> vertexes;
	std::vector<float> colors;
	GLuint programID;
	std::vector<std::vector<float>> colorMap;

  public:
	Renderer();

	void addBlock(int x, int y, int color);

	void rmvLastBlock();

	void clearBlocks();

	void clearGhost();

	void renderGhost(Piece *ghostPiece);

	void renderSwap(Piece *swapPiece);

	void render();

	void draw();
};