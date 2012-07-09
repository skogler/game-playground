#include "terrain.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <glm/glm.hpp>
#include "../../utils/logger.hpp"
#include <SFML/Graphics/Image.hpp>
using namespace std;

#define MESH_RESOLUTION 4.0f									// Pixels Per Vertex
#define MESH_HEIGHTSCALE 1.0f

Terrain::Terrain()
{
	this->hHeight = 1024;
	this->hWidth = 1024;
	yOffset = 0.0f;
	xOffset = 0.0f;
	zOffset = 0.0f;
	heighmap = NULL;
}

Terrain::~Terrain()
{
}

/**
 * Initializes the terrain
 */
void Terrain::init()
{
	//loadRawFile("resources/maps/Terrain.raw", 1024, 1024);
	//createVerticeData();
	//loadImageFile("resources/maps/testMap.tga");
	//createVerticeDataFromTGA();
	//createVerticeData();

	loadHeightMapFromTGA("resources/maps/cloud1.tga");

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3),
			&vertices[0], GL_STATIC_DRAW);

}

void Terrain::cleanup()
{
	glDeleteBuffers(1, &vertexBuffer);

}

void Terrain::renderTest()
{
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(0, // attribute
			3, // size
			GL_FLOAT, // type
			GL_FALSE, // normalized?
			0, // stride
			(void*) 0 // array buffer offset
			);
	glDrawArrays(GL_LINES, 0, vertices.size());
	glDisableVertexAttribArray(0);
}

/**
 * Creates the vertice data from the height map
 */
void Terrain::createVerticeData()
{

	for (int hMapX = 0; hMapX < hWidth; hMapX += 2)
	{
		for (int hMapZ = 0; hMapZ < hHeight; hMapZ += 2)
		{
			vertices.push_back(
					glm::vec3(hMapX, heightMap[hMapX][hMapZ], hMapZ));
			vertices.push_back(
					glm::vec3(hMapX, heightMap[hMapX][hMapZ + 1], hMapZ + 1));
			vertices.push_back(
					glm::vec3(hMapX + 1, heightMap[hMapX + 1][hMapZ], hMapZ));
			vertices.push_back(
					glm::vec3(hMapX + 1, heightMap[hMapX + 1][hMapZ + 1],
							hMapZ + 1));
		}

	}
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

void Terrain::loadImageFile(std::string filename)
{
	int aux;
	sf::Image img;
	if (img.loadFromFile(filename.c_str()))
	{
		std::cout << "worked" << endl;
	}

	hWidth = img.getSize().x;
	hHeight = img.getSize().y;

	terrainHeights = (float *) malloc(hWidth * hHeight * sizeof(float));

	std::size_t size = hWidth * hHeight * 4;
	std::vector<sf::Uint8> pixelData(size);
	const sf::Uint8 * p = img.getPixelsPtr();
	pixelData.assign(p, p + size);
	std::cout << "pixel Data size: " << pixelData.size() << "empty: "
			<< pixelData.empty() << std::endl;
	for (int i = 0; i < hHeight; i++)
	{
		for (int j = 0; j < hWidth; j++)
		{
			//std::cout << "i: " << i << " j: " << j << std::endl;
			// compute the height as a value between 0.0 and 1.0
			aux = (i * hWidth + j);
			terrainHeights[i * hWidth + j] = (pixelData[aux] / 1.0f);
			//std::cout << pixelData[aux] / 255.0f << std::endl;
		}
	}
	std::cout << "loadImageFilecomplete + Heights created" << endl;

}

/**
 * Renders the terrain
 */
void Terrain::render()
{

}

bool Terrain::loadTGA(const char *filename)
{
	FILE *file;
	unsigned char type[4];
	unsigned char info[6];

	file = fopen(filename, "rb");

	if (!file)
		return false;

	fread(&type, sizeof(char), 3, file);
	fseek(file, 12, SEEK_SET);
	fread(&info, sizeof(char), 6, file);

	//image type either 2 (color) or 3 (greyscale)
	if (type[1] != 0 || (type[2] != 2 && type[2] != 3))
	{
		fclose(file);
		return false;
	}

	tgaFile.width = info[0] + info[1] * 256;
	tgaFile.height = info[2] + info[3] * 256;
	tgaFile.byteCount = info[4] / 8;

	if (tgaFile.byteCount != 3 && tgaFile.byteCount != 4)
	{
		fclose(file);
		return false;
	}

	long imageSize = tgaFile.width * tgaFile.height * tgaFile.width
			* tgaFile.byteCount;

	//allocate memory for image data
	tgaFile.data = new unsigned char[imageSize];

	//read in image data
	fread(tgaFile.data, sizeof(unsigned char), imageSize, file);

	//close file
	fclose(file);

	return true;
}

/**
 * Loads the heightmap data from a tga file
 */
void Terrain::loadHeightMapFromTGA(std::string filename)
{
	int STEP_SIZE = 4;
	TgaLoader tl;

	if (tl.loadTGAFile(filename))
	{
		heighmap = tl.getImageData();
		tgaInf = tl.getTga();
	}

	int flX, flZ;
	for (int y = 0; y < tgaInf.height; y += STEP_SIZE)
	{
		for (int x = 0; x < tgaInf.width; x += STEP_SIZE)
		{

			for (int nTri = 0; nTri < 6; nTri++)
			{
				flX = (float) x
						+ ((nTri == 1 || nTri == 2 || nTri == 5) ?
								MESH_RESOLUTION : 0.0f);
				flZ = (float) y
						+ ((nTri == 2 || nTri == 4 || nTri == 5) ?
								MESH_RESOLUTION : 0.0f);

				int xx = flX - (tgaInf.width / 2);
				int yy = rgbHeight((int) flX, (int) flZ) * MESH_HEIGHTSCALE;
				int zz = flZ - (tgaInf.height / 2);

				vertices.push_back(glm::vec3(xx, yy, zz));

			}
		}
	}

	/*
	 int X = 0, Y = 0;

	 for (X = 0; X < tgaInf.width; X += STEP_SIZE)
	 for (Y = 0; Y < tgaInf.height; Y += STEP_SIZE)
	 {
	 vertices.push_back(glm::vec3(X, heighmap[Y + (X * tgaInf.width)], Y));

	 vertices.push_back(glm::vec3(X, retreiveHeight(X, Y), Y));

	 vertices.push_back(
	 glm::vec3(X + STEP_SIZE,
	 retreiveHeight(X + STEP_SIZE, Y + STEP_SIZE),
	 Y + STEP_SIZE));
	 vertices.push_back(
	 glm::vec3(X + STEP_SIZE,
	 retreiveHeight(X + STEP_SIZE, Y + STEP_SIZE),
	 Y + STEP_SIZE));
	 vertices.push_back(
	 glm::vec3(X + STEP_SIZE, retreiveHeight(X + STEP_SIZE, Y),
	 Y));

	 }
	 std::cout << tgaInf.width << "   "<< tgaInf.height << std::endl;
	 std::cout << "vert: " << vertices.size() << std::endl;

	 */
}

float Terrain::rgbHeight(int nX, int nY)
{
	// Calculate The Position In The Texture
	int nPos = ((nX % tgaInf.width) + ((nY % tgaInf.height) * tgaInf.width))
			* 3;
	float flR = (float) heighmap[nPos]; // Get The Red Component
	float flG = (float) heighmap[nPos + 1]; // Get The Green Component
	float flB = (float) heighmap[nPos + 2]; // Get The Blue Component
	return (0.299f * flR + 0.587f * flG + 0.114f * flB); // Calculate The Height Using The Luminance Algorithm
}

int Terrain::retreiveHeight(int x, int y)
{
	x = x % tgaInf.width;
	y = y % tgaInf.height;

	if (!heighmap)
		return 0;
	return heighmap[x + (y * tgaInf.width)];

}
void Terrain::createVerticeDataFromTGA()
{
	std::cout << "start create vertice" << endl;

	float startW, startL;
	int aux;
	float flx;
	float flz;

	// compute the initial point of the terrain on the XZ plane
	startW = hWidth / 2.0 - hWidth;
	startL = -hHeight / 2.0 + hHeight;
	startW = 0;
	startL = 0;

	if (terrainNormals != NULL)
	{
		glColorMaterial(GL_FRONT, GL_DIFFUSE);
		glEnable(GL_COLOR_MATERIAL);
	}

	std::cout << "start loop" << endl;
	for (int i = 0; i < hHeight - 1; i += 15)
	{
		for (int j = 0; j < hWidth; j += 15)
		{
			vertices.push_back(
					glm::vec3(startW + j + xOffset,
							terrainHeights[(i) * hWidth + j] + yOffset,
							startL - i + zOffset));

			std::cout << startW + j + xOffset << " || "
					<< terrainHeights[(i) * hWidth + j] + yOffset << " || "
					<< startL - i + zOffset << std::endl;

		}

	}
	std::cout << "end loop" << endl;
	std::cout << "vertice size " << vertices.front().x << vertices.front().y
			<< vertices.front().z << endl;

}

