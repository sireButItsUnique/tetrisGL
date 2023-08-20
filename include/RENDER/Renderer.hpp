#include <GL/glad.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <UTIL/LoadShaders.h>
#include <iostream>
#include <vector>

class Renderer {
  private:
	unsigned int vVBO;
	unsigned int cVBO;
	unsigned int ghostvVBO;
	unsigned int ghostcVBO;
	std::vector<float> ghostVertexes;
	std::vector<float> ghostColors;
	std::vector<float> vertexes;
	std::vector<float> colors;
	GLuint programID;
	std::vector<std::vector<float>> colorMap;

  public:
	Renderer();

	void addBlock(int x, int y, int color);

	void addGhostBlock(int x, int y, int color);

	void rmvLastBlock();

	void clearBlocks();

	void clearGhost();

	void render();

	void draw();
};