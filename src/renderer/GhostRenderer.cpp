#include <RENDER/Renderer.hpp>

void Renderer::clearGhost() {
	// bind nothing to vbo
	float *v = {};
	glBindBuffer(GL_ARRAY_BUFFER, ghostvVBO);
	glBufferData(GL_ARRAY_BUFFER, 0, v, GL_STATIC_DRAW);

	v = {};
	glBindBuffer(GL_ARRAY_BUFFER, ghostcVBO);
	glBufferData(GL_ARRAY_BUFFER, 0, v, GL_STATIC_DRAW);
}

void Renderer::renderGhost(Piece *ghostPiece) {
	noGhost = false;

	// get verticies
	std::vector<float> ghostVertexes;
	std::vector<float> ghostColors;
	for (std::pair<int, int> block : ghostPiece->getPos()) {

		// color
		int color = ghostPiece->getId();
		for (int i = 0; i < 6; i++) {
			ghostColors.push_back(0.3f * colorMap[color][0]);
			ghostColors.push_back(0.3f * colorMap[color][1]);
			ghostColors.push_back(0.3f * colorMap[color][2]);
		}

		// position: -0.5 -> 0.5; 10 by 24
		float xMult = 1 / 10.0f;
		float yMult = 2 / 24.0f;
		float xAdj = 0.5;
		int x = block.first;
		int y = block.second;

		// top left triangle
		ghostVertexes.push_back((x * xMult) - xAdj);
		ghostVertexes.push_back(1 - (y * yMult));
		ghostVertexes.push_back(0.0f);

		ghostVertexes.push_back(((x + 1) * xMult) - xAdj);
		ghostVertexes.push_back(1 - (y * yMult));
		ghostVertexes.push_back(0.0f);

		ghostVertexes.push_back((x * xMult) - xAdj);
		ghostVertexes.push_back(1 - ((y + 1) * yMult));
		ghostVertexes.push_back(0.0f);

		// bottom right triangle
		ghostVertexes.push_back(((x + 1) * xMult) - xAdj);
		ghostVertexes.push_back(1 - ((y + 1) * yMult));
		ghostVertexes.push_back(0.0f);

		ghostVertexes.push_back(((x + 1) * xMult) - xAdj);
		ghostVertexes.push_back(1 - (y * yMult));
		ghostVertexes.push_back(0.0f);

		ghostVertexes.push_back((x * xMult) - xAdj);
		ghostVertexes.push_back(1 - ((y + 1) * yMult));
		ghostVertexes.push_back(0.0f);
	}

	// bind to vbo
	float *v = &ghostVertexes[0];
	glBindBuffer(GL_ARRAY_BUFFER, ghostvVBO);
	glBufferData(GL_ARRAY_BUFFER, 4 * ghostVertexes.size(), v, GL_STATIC_DRAW);

	v = &ghostColors[0];
	glBindBuffer(GL_ARRAY_BUFFER, ghostcVBO);
	glBufferData(GL_ARRAY_BUFFER, 4 * ghostColors.size(), v, GL_STATIC_DRAW);
}