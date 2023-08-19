#include <vector>

class Piece {
  protected:
	int id;
	int rotation = 0;
	std::vector<std::pair<int, int>> pos;

  public:
	void move(int x, int y);
	virtual void rotate();
	int getId();
	std::vector<std::pair<int, int>> getPos();
};

class Square : public Piece {
  public:
	Square();
	void rotate() override;
};

class T : public Piece {
  public:
	T();
	void rotate() override;
};

class Line : public Piece {
  public:
	Line();
	void rotate() override;
};

class LeftL : public Piece {
  public:
	LeftL();
	void rotate() override;
};

class RightL : public Piece {
  public:
	RightL();
	void rotate() override;
};

class LeftZ : public Piece {
  public:
	LeftZ();
	void rotate() override;
};

class RightZ : public Piece {
  public:
	RightZ();
	void rotate() override;
};