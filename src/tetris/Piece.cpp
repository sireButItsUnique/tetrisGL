#include <TETRIS/piece.hpp>

// Parent
void Piece::move(int x, int y) {
	for (std::pair<int, int> &block : pos) {
		block.first += x;
		block.second += y;
	}
}

void Piece::rotate() {}

int Piece::getId() { return id; }

std::vector<std::pair<int, int>> Piece::getPos() { return pos; }

// Construstors
Square::Square() {
	id = 1;
	pos.resize(4);
	pos[0] = {4, 0};
	pos[1] = {5, 0};
	pos[2] = {4, 1};
	pos[3] = {5, 1};
}

T::T() {
	id = 2;
	pos.resize(4);
	pos[0] = {4, 0};
	pos[1] = {3, 1};
	pos[2] = {4, 1};
	pos[3] = {5, 1};
}

Line::Line() {
	id = 3;
	pos.resize(4);
	pos[0] = {3, 0};
	pos[1] = {4, 0};
	pos[2] = {5, 0};
	pos[3] = {6, 0};
}

LeftL::LeftL() {
	id = 4;
	pos.resize(4);
	pos[0] = {3, 0};
	pos[1] = {3, 1};
	pos[2] = {4, 1};
	pos[3] = {5, 1};
}

RightL::RightL() {
	id = 5;
	pos.resize(4);
	pos[0] = {5, 0};
	pos[1] = {3, 1};
	pos[2] = {4, 1};
	pos[3] = {5, 1};
}

LeftZ::LeftZ() {
	id = 6;
	pos.resize(4);
	pos[0] = {4, 0};
	pos[1] = {5, 0};
	pos[2] = {5, 1};
	pos[3] = {6, 1};
}

RightZ::RightZ() {
	id = 7;
	pos.resize(4);
	pos[0] = {4, 0};
	pos[1] = {5, 0};
	pos[2] = {4, 1};
	pos[3] = {3, 1};
}

// Rotation
void Square::rotate() {}

void T::rotate() {}

void Line::rotate() {}

void LeftL::rotate() {}

void RightL::rotate() {}

void LeftZ::rotate() {}

void RightZ::rotate() {}