#include <RENDER/Renderer.hpp>

void Renderer::clearSwap() {
	// bind nothing to vbo
	float *v = {};
	glBindBuffer(GL_ARRAY_BUFFER, swapvVBO);
	glBufferData(GL_ARRAY_BUFFER, 0, v, GL_STATIC_DRAW);

	v = {};
	glBindBuffer(GL_ARRAY_BUFFER, swapcVBO);
	glBufferData(GL_ARRAY_BUFFER, 0, v, GL_STATIC_DRAW);
}

std::vector<float> generateLinePiece() {
	std::vector<float> swapVertexes;
	for (int x = 0; x < 4; x++) {

		// position: -0.9 -> -0.6; 4 cols
		// wtv -> 0.6875; 1 row
		float xMult = 0.3 / 4.0f; // 0.3 = 240p
		float yMult = 0.0625;	  // x = 60p
		float xAdj = 0.9;
		float yAdj = 0.68125;
		int y = 0;

		// top left triangle
		swapVertexes.push_back((x * xMult) - xAdj);
		swapVertexes.push_back(yAdj - (y * yMult));
		swapVertexes.push_back(0.0f);

		swapVertexes.push_back(((x + 1) * xMult) - xAdj);
		swapVertexes.push_back(yAdj - (y * yMult));
		swapVertexes.push_back(0.0f);

		swapVertexes.push_back((x * xMult) - xAdj);
		swapVertexes.push_back(yAdj - ((y + 1) * yMult));
		swapVertexes.push_back(0.0f);

		// bottom right triangle
		swapVertexes.push_back(((x + 1) * xMult) - xAdj);
		swapVertexes.push_back(yAdj - ((y + 1) * yMult));
		swapVertexes.push_back(0.0f);

		swapVertexes.push_back(((x + 1) * xMult) - xAdj);
		swapVertexes.push_back(yAdj - (y * yMult));
		swapVertexes.push_back(0.0f);

		swapVertexes.push_back((x * xMult) - xAdj);
		swapVertexes.push_back(yAdj - ((y + 1) * yMult));
		swapVertexes.push_back(0.0f);
	}
	return swapVertexes;
}

std::vector<float> generateSquarePiece(Piece *swapPiece) {
	return std::vector<float>();
}

void Renderer::renderSwap(Piece *swapPiece) {

	// edge case
	if (swapPiece == nullptr) {
		noSwap = true;
		return;
	}

	// get verticies
	noSwap = false;
	std::vector<float> swapVertexes;
	std::vector<float> swapColors;

	// color
	int color = swapPiece->getId();
	for (int i = 0; i < 24; i++) {
		swapColors.push_back(colorMap[color][0]);
		swapColors.push_back(colorMap[color][1]);
		swapColors.push_back(colorMap[color][2]);
	}
	if (swapPiece->getId() == 1) {
		// swapVertexes = generateSquarePiece();
	} else if (swapPiece->getId() == 3) {
		swapVertexes = generateLinePiece();
	} else {
		for (std::pair<int, int> block : swapPiece->getPos()) {

			// position: -0.9 -> -0.6; 3 cols
			// wtv -> 0.733; 2 rows
			float xMult = 0.3 / 3.0f;		// 240p
			float yMult = (1.0 / 6) / 2.0f; // 160p
			float xAdj = 0.9;
			float yAdj = 0.65 + (1.0 / 12);
			int x = block.first - 3;
			int y = block.second;

			// top left triangle
			swapVertexes.push_back((x * xMult) - xAdj);
			swapVertexes.push_back(yAdj - (y * yMult));
			swapVertexes.push_back(0.0f);

			swapVertexes.push_back(((x + 1) * xMult) - xAdj);
			swapVertexes.push_back(yAdj - (y * yMult));
			swapVertexes.push_back(0.0f);

			swapVertexes.push_back((x * xMult) - xAdj);
			swapVertexes.push_back(yAdj - ((y + 1) * yMult));
			swapVertexes.push_back(0.0f);

			// bottom right triangle
			swapVertexes.push_back(((x + 1) * xMult) - xAdj);
			swapVertexes.push_back(yAdj - ((y + 1) * yMult));
			swapVertexes.push_back(0.0f);

			swapVertexes.push_back(((x + 1) * xMult) - xAdj);
			swapVertexes.push_back(yAdj - (y * yMult));
			swapVertexes.push_back(0.0f);

			swapVertexes.push_back((x * xMult) - xAdj);
			swapVertexes.push_back(yAdj - ((y + 1) * yMult));
			swapVertexes.push_back(0.0f);
		}
	}

	// bind to vbo
	float *v = &swapVertexes[0];
	glBindBuffer(GL_ARRAY_BUFFER, swapvVBO);
	glBufferData(GL_ARRAY_BUFFER, 4 * swapVertexes.size(), v, GL_STATIC_DRAW);

	v = &swapColors[0];
	glBindBuffer(GL_ARRAY_BUFFER, swapcVBO);
	glBufferData(GL_ARRAY_BUFFER, 4 * swapColors.size(), v, GL_STATIC_DRAW);
}