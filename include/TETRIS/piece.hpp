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
  protected:
	int id = 1;

  public:
	Square();
	void rotate() override;
};

class T : public Piece {
  protected:
	int id = 2;

  public:
	T();
	void rotate() override;
};

class Line : public Piece {
  protected:
	int id = 3;

  public:
	Line();
	void rotate() override;
};

class LeftL : public Piece {
  protected:
	int id = 4;

  public:
	LeftL();
	void rotate() override;
};

class RightL : public Piece {
  protected:
	int id = 5;

  public:
	RightL();
	void rotate() override;
};

class LeftZ : public Piece {
  protected:
	int id = 6;

  public:
	LeftZ();
	void rotate() override;
};

class RightZ : public Piece {
  protected:
	int id = 7;

  public:
	RightZ();
	void rotate() override;
};