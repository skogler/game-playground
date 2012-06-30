#ifndef TERRAIN_HPP_
#define TERRAIN_HPP_

#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <GL/glew.h>

class Terrain
{
public:
	Terrain();
	virtual ~Terrain();

	void init();
	void cleanup();
	void createVerticeData();
	void renderTest();
	void render();
	void loadRawFile(std::string filename,  int width, int height);
	void loadImageFile(std::string filename);
	void createVerticeDataFromTGA();


private:
	//Heighfield vars
	float yOffset;
	float xOffset;
	float zOffset;
	unsigned int hWidth;
	unsigned int hHeight;
	float *terrainHeights;
	float *terrainNormals;

	unsigned char heightMap[1024][1024];

	//Render vars
	std::vector<glm::vec3> vertices;
	GLuint vertexBuffer;

};

#endif /* TERRAIN_HPP_ */
