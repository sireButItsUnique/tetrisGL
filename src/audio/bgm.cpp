#include <AUDIO/bgm.h>

void initAudio() {
	mciSendStringA(
		"open \"D:\\robert2021\\projects\\tetrisGL\\src\\assets\\bgm.mp3\" "
		"type mpegvideo alias bgm",
		NULL, 0, NULL);
	mciSendStringA("play bgm repeat", NULL, 0, NULL);
}

void pauseAudio(bool &bgmEnabled) {
	if (bgmEnabled) {
		mciSendStringA("pause bgm", NULL, 0, NULL);
	} else {
		mciSendStringA("resume bgm", NULL, 0, NULL);
	}
	bgmEnabled = !bgmEnabled;
}