#include <RENDER/Renderer.hpp>

void Renderer::renderBorders() {
	noBorders = false;

	// get verticies
	float nextXBeg = 0.95;
	float nextXEnd = 0.55;
	float nextYBeg = 0.8;
	float nextYEnd = -0.1;
	float swapXBeg = -0.95;
	float swapXEnd = -0.55;
	float swapYBeg = 0.8;
	float swapYEnd = 0.5;
	std::vector<float> borderVertexes = {
		-0.5f,	  -1.0f,	0.0f,	  -0.5f,	1.0f,	  0.0f,		0.5f,
		-1.0f,	  0.0f,		0.5f,	  1.0f,		0.0f,	  nextXBeg, nextYBeg,
		0.0f,	  nextXEnd, nextYBeg, 0.0f,		nextXBeg, nextYEnd, 0.0f,
		nextXEnd, nextYEnd, 0.0f,	  nextXBeg, nextYBeg, 0.0f,		nextXBeg,
		nextYEnd, 0.0f,		nextXEnd, nextYBeg, 0.0f,	  nextXEnd, nextYEnd,
		0.0f,	  swapXBeg, swapYBeg, 0.0f,		swapXEnd, swapYBeg, 0.0f,
		swapXBeg, swapYEnd, 0.0f,	  swapXEnd, swapYEnd, 0.0f,		swapXBeg,
		swapYBeg, 0.0f,		swapXBeg, swapYEnd, 0.0f,	  swapXEnd, swapYBeg,
		0.0f,	  swapXEnd, swapYEnd, 0.0f,
	};
	std::vector<float> borderColors;

	// 2 + 4 + 4 = 10 lines = 20 vertexes = 60 points
	for (int i = 0; i < 60; i++) {
		borderColors.push_back(1.0);
	}

	// bind to vbo
	float *v = &borderVertexes[0];
	glBindBuffer(GL_ARRAY_BUFFER, bordervVBO);
	glBufferData(GL_ARRAY_BUFFER, 4 * borderVertexes.size(), v, GL_STATIC_DRAW);

	v = &borderColors[0];
	glBindBuffer(GL_ARRAY_BUFFER, bordercVBO);
	glBufferData(GL_ARRAY_BUFFER, 4 * borderColors.size(), v, GL_STATIC_DRAW);
}