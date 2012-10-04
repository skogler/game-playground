#include "texture.hpp"

#include "utils/logger.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <boost/format.hpp>
#include <boost/filesystem.hpp>
namespace fs = boost::filesystem;
using namespace std;

Texture::Texture(const fs::path& path)
{
	loadFromFile(path);
	Logger::debug("Loaded texture: " + path.string());
}

Texture::~Texture()
{
}

void Texture::loadFromFile(const fs::path& path)
{
#define ID_DXT1 0x31545844 // "DXT1" in ASCII
#define ID_DXT3 0x33545844 // "DXT3" in ASCII
#define ID_DXT5 0x35545844 // "DXT5" in ASCII

	unsigned char header[124];

	FILE *fp;

	fp = fopen(path.string().c_str(), "rb");
	if (fp == NULL)
		throw std::runtime_error("Cannot read file:" + path.string());

	char filecode[4];
	fread(filecode, 1, 4, fp);
	if (strncmp(filecode, "DDS ", 4) != 0)
	{
		fclose(fp);
		throw std::runtime_error("Invalid DDS file:" + path.string());;
	}

	// DDS header is 124 bytes
	fread(&header, 124, 1, fp);

	// All those nasty constants
	unsigned int height = *(unsigned int*) &(header[8]);
	unsigned int width = *(unsigned int*) &(header[12]);
	unsigned int linearSize = *(unsigned int*) &(header[16]);
	unsigned int numMipMaps = *(unsigned int*) &(header[24]);
	unsigned int compressionFormat = *(unsigned int*) &(header[80]);
	unsigned char * buffer;
	unsigned int bufsize;
	/* how big is it going to be including all mipmaps? */
	bufsize = numMipMaps > 1 ? linearSize * 2 : linearSize;
	buffer = (unsigned char*) malloc(bufsize * sizeof(unsigned char));
	fread(buffer, 1, bufsize, fp);
	/* close the file pointer */
	fclose(fp);

	unsigned int textureFormat;
	switch (compressionFormat)
	{
	case ID_DXT1:
		textureFormat = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
		break;
	case ID_DXT3:
		textureFormat = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
		break;
	case ID_DXT5:
		textureFormat = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
		break;
	default:
		free(buffer);
		throw std::runtime_error("Unsupported DDS image format: " + path.string());
	}

	// Create OpenGL texture and use it
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	unsigned int blockSize = (textureFormat == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
	unsigned int offset = 0;

	/* load the mipmaps */
	for (unsigned int level = 0; level < numMipMaps && (width || height); ++level)
	{
		unsigned int size = ((width + 3) / 4) * ((height + 3) / 4) * blockSize;
		glCompressedTexImage2D(GL_TEXTURE_2D, level, textureFormat, width, height, 0, size, buffer + offset);

		offset += size;
		width /= 2;
		height /= 2;
	}
	free(buffer);
}

