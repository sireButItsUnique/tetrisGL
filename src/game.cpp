#include "./piece.cpp"
#include <Windows.h>

class Game {
  public:
	Game() {}

	void initAudio() {
		mciSendStringA(
			"open \"D:\\robert2021\\projects\\tetrisGL\\src\\assets\\bgm.mp3\" "
			"type mpegvideo alias bgm",
			NULL, 0, NULL);
		mciSendStringA("play bgm repeat", NULL, 0, NULL);
	}
};