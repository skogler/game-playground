/*
 * tgaloader.cpp
 *
 *  Created on: Jun 30, 2012
 *      Author: zeheron
 */

#include "tgaloader.hpp"



TgaLoader::TgaLoader()
{
	// TODO Auto-generated
}

TgaLoader::~TgaLoader()
{
	// TODO Auto-generated destructor stub
}

/**
 * Loads the specified TGA file
 * Check for compression
 * Extracts all relevant data
 */
bool TgaLoader::loadTGAFile(std::string filename)
{
	FILE * file;
	file = fopen(filename.c_str(), "rb");

	if (file == NULL)
	{
		Logger::error("Unable to load TGA file: " + filename);
		return false;
	}

	if (fread(&tgaheader, sizeof(TGAHeader), 1, file) == 0)
	{
		Logger::error("Unable to load TGA file HEADER: " + filename);
		if (file != NULL)
		{
			fclose(file);
		}
		return false;
	}
	loadUncompressed(file);

	return true;
}

/**
 * Loads a uncompressed TGA file
 */
bool TgaLoader::loadUncompressed(FILE * file)
{
	if (fread(tga.header, sizeof(tga.header), 1, file) == 0)
	{
		Logger::error("Failure reading uncompressed header");
		if (file != NULL)
		{
			fclose(file);
		}
		return false;
	}


	tga.width = tga.header[1] * 256 + tga.header[0]; // Determine The TGA Width	(highbyte*256+lowbyte)
	tga.height = tga.header[3] * 256 + tga.header[2]; // Determine The TGA Height	(highbyte*256+lowbyte)
	tga.bitsPerPixel = tga.header[4];

	std::cout << "loader: " << tga.width << " " << tga.height << std::endl;


	if (tga.bitsPerPixel == 24)
	{
		tga.type = RGB;
	}
	else
	{
		tga.type = RGBA;
	}

	tga.bytesPerPixel = (tga.bitsPerPixel / 8);
	// calculate needed memory
	tga.imageSize = (tga.bytesPerPixel * tga.width * tga.height);
	imageData = (GLubyte *) malloc(tga.imageSize);

	if (imageData == NULL)
	{
		Logger::error("Unable to allocate memory for image");
		fclose(file);
		return false;
	}

	if (fread(imageData, 1, tga.imageSize, file) != tga.imageSize)
	{
		Logger::error("Unable to READ image data");

		if (imageData != NULL)
		{
			free(imageData);
		}
		fclose(file);
		return false;
	}

	// Byte Swapping Optimized By Steve Thomas
	for (GLuint cswap = 0; cswap < tga.imageSize; cswap += tga.bytesPerPixel)
	{
		imageData[cswap] ^= imageData[cswap + 2] ^= imageData[cswap] ^=
			imageData[cswap + 2];
	}

	fclose(file);
	return true;
}

/**
 * Loads a RLE compressed TGA file
 */
bool TgaLoader::loadCompressed(FILE * file)
{
	//TODO: implement
	return false;
}

