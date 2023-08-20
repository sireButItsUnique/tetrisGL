#include <RENDER/Renderer.hpp>

void Renderer::addGhostBlock(int x, int y, int color) {

	// color
	for (int i = 0; i < 6; i++) {
		ghostColors.push_back(0.3f * colorMap[color][0]);
		ghostColors.push_back(0.3f * colorMap[color][1]);
		ghostColors.push_back(0.3f * colorMap[color][2]);
	}

	// position: -1 -> 1; 10 by 24
	float xAdj = 2 / 10.0f;
	float yAdj = 2 / 24.0f;

	// top left triangle
	ghostVertexes.push_back((x * xAdj) - 1);
	ghostVertexes.push_back(1 - (y * yAdj));
	ghostVertexes.push_back(0.0f);

	ghostVertexes.push_back(((x + 1) * xAdj) - 1);
	ghostVertexes.push_back(1 - (y * yAdj));
	ghostVertexes.push_back(0.0f);

	ghostVertexes.push_back((x * xAdj) - 1);
	ghostVertexes.push_back(1 - ((y + 1) * yAdj));
	ghostVertexes.push_back(0.0f);

	// bottom right triangle
	ghostVertexes.push_back(((x + 1) * xAdj) - 1);
	ghostVertexes.push_back(1 - ((y + 1) * yAdj));
	ghostVertexes.push_back(0.0f);

	ghostVertexes.push_back(((x + 1) * xAdj) - 1);
	ghostVertexes.push_back(1 - (y * yAdj));
	ghostVertexes.push_back(0.0f);

	ghostVertexes.push_back((x * xAdj) - 1);
	ghostVertexes.push_back(1 - ((y + 1) * yAdj));
	ghostVertexes.push_back(0.0f);
}

void Renderer::clearGhost() {
	ghostVertexes = {};
	ghostColors = {};
}