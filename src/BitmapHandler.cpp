#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "BitmapHandler.h"

BitmapHandler::BitmapHandler(const char* path) : data(nullptr)
{
	data = stbi_load(path, &width, &height, &channels, 0);
}

BitmapHandler::~BitmapHandler()
{
	if (data) stbi_image_free(data);
}

bool BitmapHandler::isLoaded() const { return data != nullptr; }

int BitmapHandler::getWidth() const { return width; }

int BitmapHandler::getHeight() const { return height; }

unsigned char* BitmapHandler::getData() const { return data; }