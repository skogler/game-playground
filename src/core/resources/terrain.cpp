#include "terrain.hpp"
#include <stdio.h>
#include <iostream>
#include <GL/gl.h>
#include "../../utils/logger.hpp"

#define		STEP_SIZE	  16							// Width And Height Of Each Quad

Terrain::Terrain()
{
}

Terrain::~Terrain()
{
}

bool Terrain::create(std::string filename, int width, int height)
{
	hHeight = height;
	hWidth = width;
	FILE *fp;

	fp = fopen(filename.c_str(), "rb");
	fread(heightMap, 1, width * height, fp);
	fclose(fp);

	return true;
}

/**
 * Renders the terrain
 */
void Terrain::render()
{

	for (int hMapX = 0; hMapX < hWidth; hMapX++)
	{

		for (int hMapZ = 0; hMapZ < hHeight; hMapZ++)
		{
			glBegin (GL_TRIANGLE_STRIP);
			glVertex3f(hMapX, heightMap[hMapX][hMapZ], hMapZ);
			glVertex3f(hMapX, heightMap[hMapX][hMapZ + 1], hMapZ + 1);
			glVertex3f(hMapX + 1, heightMap[hMapX + 1][hMapZ], hMapZ);
			glVertex3f(hMapX + 1, heightMap[hMapX + 1][hMapZ + 1], hMapZ + 1);
			glEnd();

		}

	}
}

void Terrain::init()
{
}

void Terrain::cleanup()
{
}

void Terrain::renderTest()
{
}

/**
 * Loads The .RAW file and stores it in heightField
 */
void Terrain::loadRawFile(std::string filename, int width, int height)
{
	hHeight = height;
	hWidth = width;
	FILE *pFile = NULL;

	pFile = fopen(filename.c_str(), "rb");
	if (pFile == NULL)
	{
		// Display Error Message And Stop The Function
		Logger::error("HeightMap RAW file not found!");
		return;
	}

	fread(heightMap, 1, width * height, pFile);

	if (ferror(pFile))
	{
		Logger::error("Failed to retrieve heightmap data!");
	}

	// Close The File.
	fclose(pFile);
}
