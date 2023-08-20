#include <RENDER/Renderer.hpp>

Renderer::Renderer() {

	// init colorMap
	colorMap.resize(8);
	colorMap[1] = {1.00, 0.84, 0.00};
	colorMap[2] = {0.57, 0.27, 1.00};
	colorMap[3] = {0.24, 0.87, 1.00};
	colorMap[4] = {1.00, 0.59, 0.11};
	colorMap[5] = {0.01, 0.25, 0.68};
	colorMap[6] = {1.00, 0.20, 0.07};
	colorMap[7] = {0.45, 0.80, 0.23};

	// use shader
	programID = LoadShaders(
		"D:\\robert2021\\projects\\tetrisGL\\src\\assets\\vertexShaders."
		"vertexshader",
		"D:\\robert2021\\projects\\tetrisGL\\src\\assets\\fragmentShaders."
		"fragmentshader");
	glUseProgram(programID);

	// gen buffers + link to vbo
	glGenBuffers(1, &vVBO);
	glGenBuffers(1, &cVBO);
	glGenBuffers(1, &ghostvVBO);
	glGenBuffers(1, &ghostcVBO);
}

void Renderer::addBlock(int x, int y, int color) {

	// color
	for (int i = 0; i < 6; i++) {
		colors.push_back(colorMap[color][0]);
		colors.push_back(colorMap[color][1]);
		colors.push_back(colorMap[color][2]);
	}

	// position: -1 -> 1; 10 by 24
	float xAdj = 2 / 10.0f;
	float yAdj = 2 / 24.0f;

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
	colors.erase(colors.end() - 18, colors.end());
}

void Renderer::clearBlocks() {
	vertexes = {};
	colors = {};
}

void Renderer::render() {

	// vertexes
	float *v = &vertexes[0];
	glBindBuffer(GL_ARRAY_BUFFER, vVBO);
	glBufferData(GL_ARRAY_BUFFER, 4 * vertexes.size(), v, GL_STATIC_DRAW);

	// colors
	v = &colors[0];
	glBindBuffer(GL_ARRAY_BUFFER, cVBO);
	glBufferData(GL_ARRAY_BUFFER, 4 * colors.size(), v, GL_STATIC_DRAW);

	// ghost
	v = &ghostVertexes[0];
	glBindBuffer(GL_ARRAY_BUFFER, ghostvVBO);
	glBufferData(GL_ARRAY_BUFFER, 4 * ghostVertexes.size(), v, GL_STATIC_DRAW);

	v = &ghostColors[0];
	glBindBuffer(GL_ARRAY_BUFFER, ghostcVBO);
	glBufferData(GL_ARRAY_BUFFER, 4 * ghostColors.size(), v, GL_STATIC_DRAW);
}

void Renderer::draw() {

	// draw ghost beneath
	glEnableVertexAttribArray(0); // note 0 is accessed in shaders
	glBindBuffer(GL_ARRAY_BUFFER, ghostvVBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

	// 2nd attribute buffer : colors
	glEnableVertexAttribArray(1); // note 1 is accessed in shaders
	glBindBuffer(GL_ARRAY_BUFFER, ghostcVBO);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

	// draw all triangles
	glDrawArrays(GL_TRIANGLES, 0, ghostVertexes.size());
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	// 1st attribute buffer : vertices
	glEnableVertexAttribArray(0); // note 0 is accessed in shaders
	glBindBuffer(GL_ARRAY_BUFFER, vVBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

	// 2nd attribute buffer : colors
	glEnableVertexAttribArray(1); // note 1 is accessed in shaders
	glBindBuffer(GL_ARRAY_BUFFER, cVBO);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

	// draw all triangles
	glDrawArrays(GL_TRIANGLES, 0, vertexes.size());
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}