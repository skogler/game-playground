#ifndef TERRAIN_HPP_
#define TERRAIN_HPP_

#include <string>
#include <vector>
#define GLM_FORCE_RADIANS
#include "utils/tgaloader.hpp"
#include <GL/glew.h>
#include <glm/glm.hpp>

// testing struct will be removed shortly
struct STGA
{
    STGA()
    {
        data      = (unsigned char*) 0;
        width     = 0;
        height    = 0;
        byteCount = 0;
    }

    ~STGA()
    {
        delete[] data;
        data = 0;
    }

    void destroy()
    {
        delete[] data;
        data = 0;
    }

    int            width;
    int            height;
    unsigned char  byteCount;
    unsigned char* data;
};

class Terrain
{
public:
    Terrain();
    virtual ~Terrain();

    void init();
    void cleanup();

    void loadHeightMapFromTGA(std::string filename);

    void createVerticeData();
    void renderTest();
    void render();
    void loadRawFile(std::string filename, int width, int height);
    // void loadImageFile(std::string filename);
    void createVerticeDataFromTGA();
    bool loadTGA(const char* filename);
    float rgbHeight(int nX, int nY);

private:
    GLubyte* heighmap;
    TGAInfo  tgaInf;

    int retreiveHeight(int x, int y);

    // To be removed
    STGA tgaFile;

    // Heighfield vars
    float        yOffset;
    float        xOffset;
    float        zOffset;
    unsigned int hWidth;
    unsigned int hHeight;
    float*       terrainHeights;
    float*       terrainNormals;

    unsigned char heightMap[1024][1024];

    // Render vars
    std::vector<glm::vec3> vertices;
    GLuint                 vertexBuffer;
};

#endif /* TERRAIN_HPP_ */
