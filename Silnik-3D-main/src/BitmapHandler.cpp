#include "BitmapHandler.h"

#include <GL/glu.h>

#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <vector>

namespace
{
    bool hasExt(const std::string& path, const char* extLower)
    {
        const size_t n = path.size();
        const size_t m = std::strlen(extLower);
        if (n < m) return false;
        return path.compare(n - m, m, extLower) == 0;
    }

    // Pomocnicze: odwrócenie w pionie (gdy format ma "inne" pochodzenie układu).
    void flipVertical(unsigned char* data, int w, int h, int channels)
    {
        const int stride = w * channels;
        std::vector<unsigned char> tmp(stride);
        for (int y = 0; y < h / 2; ++y)
        {
            unsigned char* rowA = data + y * stride;
            unsigned char* rowB = data + (h - 1 - y) * stride;
            std::memcpy(tmp.data(), rowA, stride);
            std::memcpy(rowA, rowB, stride);
            std::memcpy(rowB, tmp.data(), stride);
        }
    }
}

std::string BitmapHandler::toLower(std::string s)
{
    std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return (char)std::tolower(c); });
    return s;
}

void BitmapHandler::freeImage(Image& img)
{
    delete[] img.data;
    img.data = nullptr;
    img.w = img.h = img.channels = 0;
}

GLuint BitmapHandler::uploadToOpenGL(const Image& img, bool generateMipmaps) const
{
    if (!img.data || img.w <= 0 || img.h <= 0 || (img.channels != 3 && img.channels != 4))
        return 0;

    GLuint id = 0;
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    const GLenum fmt = (img.channels == 4) ? GL_RGBA : GL_RGB;

    if (generateMipmaps)
    {
        // GLU: wygenerowanie mipmap (zgodnie z instrukcją).
        gluBuild2DMipmaps(GL_TEXTURE_2D, (img.channels == 4) ? 4 : 3,
                          img.w, img.h, fmt, GL_UNSIGNED_BYTE, img.data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    }
    else
    {
        glTexImage2D(GL_TEXTURE_2D, 0, fmt, img.w, img.h, 0, fmt, GL_UNSIGNED_BYTE, img.data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    return id;
}

GLuint BitmapHandler::loadTexture2D(const std::string& path, bool generateMipmaps) const
{
    Image img;
    const std::string p = toLower(path);

    bool ok = false;
    if (hasExt(p, ".tga"))
        ok = loadTGA(path, img);
    else if (hasExt(p, ".bmp"))
        ok = loadBMP(path, img);
    else
    {
        // Spróbuj TGA/BMP "w ciemno".
        ok = loadTGA(path, img) || loadBMP(path, img);
    }

    if (!ok)
    {
        freeImage(img);
        return 0;
    }

    GLuint id = uploadToOpenGL(img, generateMipmaps);
    freeImage(img);
    return id;
}

GLuint BitmapHandler::createCheckerTexture(int size, int checkSize, bool generateMipmaps) const
{
    if (size <= 0) size = 64;
    if (checkSize <= 0) checkSize = 8;

    Image img;
    img.w = size;
    img.h = size;
    img.channels = 3;
    img.data = new unsigned char[img.w * img.h * img.channels];

    for (int y = 0; y < img.h; ++y)
    {
        for (int x = 0; x < img.w; ++x)
        {
            const int cx = x / checkSize;
            const int cy = y / checkSize;
            const bool white = ((cx + cy) % 2) == 0;
            const unsigned char v = white ? 230 : 25;
            const int idx = (y * img.w + x) * img.channels;
            img.data[idx + 0] = v;
            img.data[idx + 1] = v;
            img.data[idx + 2] = v;
        }
    }

    GLuint id = uploadToOpenGL(img, generateMipmaps);
    freeImage(img);
    return id;
}

#pragma pack(push, 1)
struct TGAHeader
{
    unsigned char idLength;
    unsigned char colorMapType;
    unsigned char imageType;
    unsigned short colorMapStart;
    unsigned short colorMapLength;
    unsigned char colorMapDepth;
    unsigned short xOrigin;
    unsigned short yOrigin;
    unsigned short width;
    unsigned short height;
    unsigned char bpp;
    unsigned char descriptor;
};
#pragma pack(pop)

bool BitmapHandler::loadTGA(const std::string& path, Image& out)
{
    std::FILE* f = std::fopen(path.c_str(), "rb");
    if (!f) return false;

    TGAHeader h{};
    if (std::fread(&h, sizeof(h), 1, f) != 1)
    {
        std::fclose(f);
        return false;
    }

    // Tylko: true color, bez kompresji.
    if (h.colorMapType != 0 || h.imageType != 2)
    {
        std::fclose(f);
        return false;
    }

    const int channels = (h.bpp == 32) ? 4 : (h.bpp == 24) ? 3 : 0;
    if (channels == 0 || h.width == 0 || h.height == 0)
    {
        std::fclose(f);
        return false;
    }

    if (h.idLength > 0)
        std::fseek(f, h.idLength, SEEK_CUR);

    const int w = (int)h.width;
    const int hgt = (int)h.height;
    const size_t bytes = (size_t)w * (size_t)hgt * (size_t)channels;

    unsigned char* data = new unsigned char[bytes];
    if (std::fread(data, 1, bytes, f) != bytes)
    {
        delete[] data;
        std::fclose(f);
        return false;
    }
    std::fclose(f);

    // TGA jest zwykle w BGR(A) -> konwersja do RGB(A)
    for (size_t i = 0; i < bytes; i += channels)
        std::swap(data[i + 0], data[i + 2]);

    // bit 5 (0x20): 0 = początek w lewym dolnym, 1 = lewy górny
    const bool originTop = (h.descriptor & 0x20) != 0;
    if (!originTop)
        flipVertical(data, w, hgt, channels);

    out.w = w;
    out.h = hgt;
    out.channels = channels;
    out.data = data;
    return true;
}

#pragma pack(push, 1)
struct BMPFileHeader
{
    unsigned short bfType;
    unsigned int bfSize;
    unsigned short bfReserved1;
    unsigned short bfReserved2;
    unsigned int bfOffBits;
};

struct BMPInfoHeader
{
    unsigned int biSize;
    int biWidth;
    int biHeight;
    unsigned short biPlanes;
    unsigned short biBitCount;
    unsigned int biCompression;
    unsigned int biSizeImage;
    int biXPelsPerMeter;
    int biYPelsPerMeter;
    unsigned int biClrUsed;
    unsigned int biClrImportant;
};
#pragma pack(pop)

bool BitmapHandler::loadBMP(const std::string& path, Image& out)
{
    std::FILE* f = std::fopen(path.c_str(), "rb");
    if (!f) return false;

    BMPFileHeader fh{};
    BMPInfoHeader ih{};

    if (std::fread(&fh, sizeof(fh), 1, f) != 1 || std::fread(&ih, sizeof(ih), 1, f) != 1)
    {
        std::fclose(f);
        return false;
    }

    if (fh.bfType != 0x4D42) // 'BM'
    {
        std::fclose(f);
        return false;
    }

    if (ih.biCompression != 0)
    {
        std::fclose(f);
        return false; // tylko bez kompresji
    }

    const int channels = (ih.biBitCount == 32) ? 4 : (ih.biBitCount == 24) ? 3 : 0;
    if (channels == 0 || ih.biWidth <= 0 || ih.biHeight == 0)
    {
        std::fclose(f);
        return false;
    }

    const int w = ih.biWidth;
    const int hAbs = std::abs(ih.biHeight);
    const bool originTop = (ih.biHeight < 0); // ujemna wysokość = dane od góry

    // Wiersze w BMP są wyrównane do 4 bajtów.
    const int rowStrideFile = ((w * channels + 3) / 4) * 4;

    std::fseek(f, (long)fh.bfOffBits, SEEK_SET);

    unsigned char* data = new unsigned char[(size_t)w * (size_t)hAbs * (size_t)channels];
    std::vector<unsigned char> row((size_t)rowStrideFile);

    for (int y = 0; y < hAbs; ++y)
    {
        if (std::fread(row.data(), 1, (size_t)rowStrideFile, f) != (size_t)rowStrideFile)
        {
            delete[] data;
            std::fclose(f);
            return false;
        }

        const int dstY = originTop ? y : (hAbs - 1 - y);
        unsigned char* dst = data + (size_t)dstY * (size_t)w * (size_t)channels;

        // BMP: BGR(A)
        for (int x = 0; x < w; ++x)
        {
            dst[x * channels + 0] = row[x * channels + 2];
            dst[x * channels + 1] = row[x * channels + 1];
            dst[x * channels + 2] = row[x * channels + 0];
            if (channels == 4)
                dst[x * channels + 3] = row[x * channels + 3];
        }
    }

    std::fclose(f);

    out.w = w;
    out.h = hAbs;
    out.channels = channels;
    out.data = data;
    return true;
}
