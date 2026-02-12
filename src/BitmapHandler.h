#pragma once

class BitmapHandler {

public:
	BitmapHandler(const char* path);
	~BitmapHandler();
	bool isLoaded() const;
	int getWidth() const;
	int getHeight() const;
	unsigned char* getData() const;

private:
	int width, height, channels;
	unsigned char* data;
};