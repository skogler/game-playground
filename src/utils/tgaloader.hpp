/*
 * tgaloader.hpp
 *
 *  Created on: Jun 30, 2012
 *      Author: zeheron
 */

#ifndef TGALOADER_HPP_
#define TGALOADER_HPP_

#include "utils/logger.hpp"
#include <GL/glew.h>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string.h>


#define RGB 1;
#define RGBA 2;

typedef struct
{
    GLubyte header[12];     // TGA File Header
} TGAHeader;

typedef struct
{
    GLubyte header[6];     // First 6 Useful Bytes From The Header
    GLuint  bytesPerPixel;
    GLuint  imageSize;
    GLuint  temp;
    GLuint  type;
    GLuint  height;
    GLuint  width;
    GLuint  bitsPerPixel;
} TGAInfo;
class TgaLoader
{
public:
    TgaLoader();
    virtual ~TgaLoader();

    bool loadTGAFile(std::string filename);

    TGAInfo getTga() const
    {
        return tga;
    }

    GLubyte* getImageData() const
    {
        return imageData;
    }

private:
    // TGA data
    TGAHeader tgaheader;
    TGAInfo   tga;
    GLubyte*  imageData;

    bool loadUncompressed(FILE* file);
    bool loadCompressed(FILE* file);
};

#endif /* TGALOADER_HPP_ */
