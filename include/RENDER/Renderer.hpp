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
	unsigned int nextVBO;
	unsigned int nextcVBO;
	unsigned int bordervVBO;
	unsigned int bordercVBO;
	std::vector<float> vertexes;
	std::vector<float> colors;
	GLuint programID;
	std::vector<std::vector<float>> colorMap;
	bool noSwap;
	bool noGhost;
	bool noBorders;

  public:
	Renderer();

	void addBlock(int x, int y, int color);

	void rmvLastBlock();

	void clearBlocks();

	void clearGhost();

	void clearSwap();

	void renderGhost(Piece *ghostPiece);

	void renderSwap(Piece *swapPiece);

	void renderBorders();

	void render();

	void clear();

	void draw();
};