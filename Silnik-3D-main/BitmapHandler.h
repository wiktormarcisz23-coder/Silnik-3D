#pragma once

#include <GL/freeglut.h>
#include <string>

// Lab 11: obsługa wczytywania tekstur (bitmap).
// Instrukcja sugeruje stb_image, ale żeby projekt był samowystarczalny,
// poniższa klasa obsługuje proste BMP (24/32bit, bez kompresji) i TGA (typ 2).

class BitmapHandler
{
public:
    // Zwraca id tekstury OpenGL (0 w razie błędu). Tekstura jest 2D.
    GLuint loadTexture2D(const std::string& path, bool generateMipmaps = true) const;

    // Gdy pliku brak, można użyć proceduralnej "szachownicy".
    GLuint createCheckerTexture(int size = 64, int checkSize = 8, bool generateMipmaps = true) const;

private:
    struct Image
    {
        int w = 0;
        int h = 0;
        int channels = 0; // 3 lub 4
        unsigned char* data = nullptr;
    };

    static std::string toLower(std::string s);

    static bool loadTGA(const std::string& path, Image& out);
    static bool loadBMP(const std::string& path, Image& out);
    static void freeImage(Image& img);

    GLuint uploadToOpenGL(const Image& img, bool generateMipmaps) const;
};
