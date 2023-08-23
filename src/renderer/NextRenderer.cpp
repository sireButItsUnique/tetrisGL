#include <RENDER/Renderer.hpp>

void generateLinePiece(int n, std::vector<float> &nextVertexes) {
	for (int x = 0; x < 4; x++) {

		// position: -0.9 -> -0.6; 4 cols
		// wtv -> 0.6875; 1 row
		float xMult = 0.3 / 4.0f; // 0.3 = 240p
		float yMult = 0.0625;	  // x = 60p
		float xAdj = -0.6;
		float yAdj = 0.68125 - (n * 0.3);
		int y = 0;

		// top left triangle
		nextVertexes.push_back((x * xMult) - xAdj);
		nextVertexes.push_back(yAdj - (y * yMult));
		nextVertexes.push_back(0.0f);

		nextVertexes.push_back(((x + 1) * xMult) - xAdj);
		nextVertexes.push_back(yAdj - (y * yMult));
		nextVertexes.push_back(0.0f);

		nextVertexes.push_back((x * xMult) - xAdj);
		nextVertexes.push_back(yAdj - ((y + 1) * yMult));
		nextVertexes.push_back(0.0f);

		// bottom right triangle
		nextVertexes.push_back(((x + 1) * xMult) - xAdj);
		nextVertexes.push_back(yAdj - ((y + 1) * yMult));
		nextVertexes.push_back(0.0f);

		nextVertexes.push_back(((x + 1) * xMult) - xAdj);
		nextVertexes.push_back(yAdj - (y * yMult));
		nextVertexes.push_back(0.0f);

		nextVertexes.push_back((x * xMult) - xAdj);
		nextVertexes.push_back(yAdj - ((y + 1) * yMult));
		nextVertexes.push_back(0.0f);
	}
}

void generateSquarePiece(int n, std::vector<float> &nextVertexes) {

	// position: -0.85 -> -0.65; 3 cols
	// wtv -> 0.733; 2 rows
	float xMult = 0.1;				// 160p
	float yMult = (1.0 / 6) / 2.0f; // 160p
	float xAdj = -0.65;
	float yAdj = 0.65 + (1.0 / 12) - (n * 0.3);
	for (int x = 0; x < 2; x++) {
		for (int y = 0; y < 2; y++) {
			// top left triangle
			nextVertexes.push_back((x * xMult) - xAdj);
			nextVertexes.push_back(yAdj - (y * yMult));
			nextVertexes.push_back(0.0f);

			nextVertexes.push_back(((x + 1) * xMult) - xAdj);
			nextVertexes.push_back(yAdj - (y * yMult));
			nextVertexes.push_back(0.0f);

			nextVertexes.push_back((x * xMult) - xAdj);
			nextVertexes.push_back(yAdj - ((y + 1) * yMult));
			nextVertexes.push_back(0.0f);

			// bottom right triangle
			nextVertexes.push_back(((x + 1) * xMult) - xAdj);
			nextVertexes.push_back(yAdj - ((y + 1) * yMult));
			nextVertexes.push_back(0.0f);

			nextVertexes.push_back(((x + 1) * xMult) - xAdj);
			nextVertexes.push_back(yAdj - (y * yMult));
			nextVertexes.push_back(0.0f);

			nextVertexes.push_back((x * xMult) - xAdj);
			nextVertexes.push_back(yAdj - ((y + 1) * yMult));
			nextVertexes.push_back(0.0f);
		}
	}
}

void Renderer::renderNext(std::deque<Piece *> next) {

	// get verticies
	std::vector<float> nextVertexes;
	std::vector<float> nextColors;

	// display next 3 pieces
	for (int i = 0; i < 3; i++) {
		// color
		Piece *nextPiece = next[i];
		int color = nextPiece->getId();
		for (int i = 0; i < 24; i++) {
			nextColors.push_back(colorMap[color][0]);
			nextColors.push_back(colorMap[color][1]);
			nextColors.push_back(colorMap[color][2]);
		}

		// position
		if (nextPiece->getId() == 1) {
			generateSquarePiece(i, nextVertexes);
		} else if (nextPiece->getId() == 3) {
			generateLinePiece(i, nextVertexes);
		} else {
			for (std::pair<int, int> block : nextPiece->getPos()) {

				// position: -0.9 -> -0.6; 3 cols
				// wtv -> 0.733; 2 rows
				float xMult = 0.3 / 3.0f;		// 240p
				float yMult = (1.0 / 6) / 2.0f; // 160p
				float xAdj = -0.6;
				float yAdj = 0.65 + (1.0 / 12) - (i * 0.3);
				int x = block.first - 3;
				int y = block.second;

				// top left triangle
				nextVertexes.push_back((x * xMult) - xAdj);
				nextVertexes.push_back(yAdj - (y * yMult));
				nextVertexes.push_back(0.0f);

				nextVertexes.push_back(((x + 1) * xMult) - xAdj);
				nextVertexes.push_back(yAdj - (y * yMult));
				nextVertexes.push_back(0.0f);

				nextVertexes.push_back((x * xMult) - xAdj);
				nextVertexes.push_back(yAdj - ((y + 1) * yMult));
				nextVertexes.push_back(0.0f);

				// bottom right triangle
				nextVertexes.push_back(((x + 1) * xMult) - xAdj);
				nextVertexes.push_back(yAdj - ((y + 1) * yMult));
				nextVertexes.push_back(0.0f);

				nextVertexes.push_back(((x + 1) * xMult) - xAdj);
				nextVertexes.push_back(yAdj - (y * yMult));
				nextVertexes.push_back(0.0f);

				nextVertexes.push_back((x * xMult) - xAdj);
				nextVertexes.push_back(yAdj - ((y + 1) * yMult));
				nextVertexes.push_back(0.0f);
			}
		}
	}

	// bind to vbo
	float *v = &nextVertexes[0];
	glBindBuffer(GL_ARRAY_BUFFER, nextvVBO);
	glBufferData(GL_ARRAY_BUFFER, 4 * nextVertexes.size(), v, GL_STATIC_DRAW);

	v = &nextColors[0];
	glBindBuffer(GL_ARRAY_BUFFER, nextcVBO);
	glBufferData(GL_ARRAY_BUFFER, 4 * nextColors.size(), v, GL_STATIC_DRAW);
}