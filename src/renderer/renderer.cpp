#include <RENDER/Renderer.hpp>

Renderer::Renderer() {
	// use shader
	programID = LoadShaders(
		"D:\\robert2021\\projects\\tetrisGL\\src\\assets\\vertexShaders."
		"vertexshader",
		"D:\\robert2021\\projects\\tetrisGL\\src\\assets\\fragmentShaders."
		"fragmentshader");
	glUseProgram(programID);

	// link to vbo
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
}

void Renderer::addBlock(int x, int y, int color) {
	//-1 -> 1; 10 by 24
	float xAdj = 2 / 11.0f;
	float yAdj = 2 / 25.0f;

	// top left triangle
	vertexes.push_back((x * xAdj) - 1);
	vertexes.push_back(1 - (y * yAdj));
	vertexes.push_back(0.0f);

	vertexes.push_back(((x + 1) * xAdj) - 1);
	vertexes.push_back(1 - (y * yAdj));
	vertexes.push_back(0.0f);

	vertexes.push_back((x * xAdj) - 1);
	vertexes.push_back(1 - ((y + 1) * yAdj));
	vertexes.push_back(0.0f);

	// bottom right triangle
	vertexes.push_back(((x + 1) * xAdj) - 1);
	vertexes.push_back(1 - ((y + 1) * yAdj));
	vertexes.push_back(0.0f);

	vertexes.push_back(((x + 1) * xAdj) - 1);
	vertexes.push_back(1 - (y * yAdj));
	vertexes.push_back(0.0f);

	vertexes.push_back((x * xAdj) - 1);
	vertexes.push_back(1 - ((y + 1) * yAdj));
	vertexes.push_back(0.0f);
}

void Renderer::rmvLastBlock() {
	vertexes.erase(vertexes.end() - 18, vertexes.end());
}

void Renderer::clearBlocks() { vertexes = {}; }

void Renderer::render() {
	std::cout << vertexes.size() << std::endl;
	float *v = &vertexes[0];
	glBufferData(GL_ARRAY_BUFFER, 4 * vertexes.size(), v, GL_STATIC_DRAW);
}

void Renderer::draw() {

	// 1st attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

	// draw all triangles
	glDrawArrays(GL_TRIANGLES, 0, vertexes.size());
	glDisableVertexAttribArray(0);
}