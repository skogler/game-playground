#ifndef TERRAIN_HPP_
#define TERRAIN_HPP_

#include <string>

class Terrain
{
public:
	Terrain();
	virtual ~Terrain();

	bool create(std::string filename, int width, int height);
	void init();
	void cleanup();
	void renderTest();
	void render();
	void loadRawFile(std::string filename,  int width, int height);


private:
	int hWidth;
	int hHeight;
	unsigned char heightMap[1024][1024];

};

#endif /* TERRAIN_HPP_ */
