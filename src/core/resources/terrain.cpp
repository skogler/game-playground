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

Terrain::Terrain()
{
	this->hHeight = 1024;
	this->hWidth = 1024;
	yOffset = 0.0f;
	xOffset = 0.0f;
	zOffset = 0.0f;
}

Terrain::~Terrain()
{
}

/**
 * Initializes the terrain
 */
void Terrain::init()
{
	loadRawFile("resources/maps/heightField.raw", 1024, 1024);
	createVerticeData();
	//loadImageFile("resources/maps/testMap.tga");
	//createVerticeDataFromTGA();
	//createVerticeData();


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
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
	glDisableVertexAttribArray(0);
}

/**
 * Creates the vertice data formt the height map
 */
void Terrain::createVerticeData()
{

	for (int hMapX = 0; hMapX < hWidth; hMapX += 1)
	{
		for (int hMapZ = 0; hMapZ < hHeight; hMapZ += 1)
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
	for (int i = 0; i < hHeight - 1; i+= 15)
	{
		for (int j = 0; j < hWidth; j+= 15)
		{
			 vertices.push_back(
			 glm::vec3(startW + j + xOffset,
			 terrainHeights[(i) * hWidth + j] + yOffset,
			 startL - i + zOffset));

			 std::cout  << startW + j + xOffset << " || " <<
			 terrainHeights[(i) * hWidth + j] + yOffset << " || " <<
			 startL - i + zOffset << std::endl;

		}

	}
	std::cout << "end loop" << endl;
	std::cout << "vertice size " << vertices.front().x << vertices.front().y
			<< vertices.front().z << endl;

}

