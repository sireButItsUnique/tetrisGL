#include <TETRIS/piece.hpp>

// Parent
void Piece::move(int x, int y) {
	for (std::pair<int, int> &block : pos) {
		block.first += x;
		block.first += y;
	}
}

void Piece::rotate() {}

int Piece::getId() { return id; }

std::vector<std::pair<int, int>> Piece::getPos() { return pos; }

// Construstors
Square::Square() {
	pos.resize(4);
	pos[0] = {11, 0};
	pos[1] = {12, 0};
	pos[2] = {11, 1};
	pos[3] = {12, 1};
}

T::T() {
	pos.resize(4);
	pos[0] = {11, 0};
	pos[1] = {10, 1};
	pos[2] = {11, 1};
	pos[3] = {12, 1};
}

Line::Line() {
	pos.resize(4);
	pos[0] = {10, 0};
	pos[1] = {11, 0};
	pos[2] = {12, 0};
	pos[3] = {13, 0};
}

LeftL::LeftL() {
	pos.resize(4);
	pos[0] = {10, 0};
	pos[1] = {10, 1};
	pos[2] = {11, 1};
	pos[3] = {12, 1};
}

RightL::RightL() {
	pos.resize(4);
	pos[0] = {12, 0};
	pos[1] = {10, 1};
	pos[2] = {11, 1};
	pos[3] = {12, 1};
}

LeftZ::LeftZ() {
	pos.resize(4);
	pos[0] = {11, 0};
	pos[1] = {12, 0};
	pos[2] = {12, 1};
	pos[3] = {13, 1};
}

RightZ::RightZ() {
	pos.resize(4);
	pos[0] = {11, 0};
	pos[1] = {12, 0};
	pos[2] = {11, 1};
	pos[3] = {10, 1};
}
// Rotation
void Square::rotate() {}

void T::rotate() {}

void Line::rotate() {}

void LeftL::rotate() {}

void RightL::rotate() {}

void LeftZ::rotate() {}

void RightZ::rotate() {}