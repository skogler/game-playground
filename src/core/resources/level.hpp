#ifndef LEVEL_HPP_
#define LEVEL_HPP_

#include <string>
#include <vector>
#define GLM_FORCE_RADIANS
#include "core/definitions.hpp"
#include <glm/glm.hpp>

#include "terrain.hpp"

/**
 * A level defines a loadable state of the game which has
 * several properties, like the terrain, resources etc.
 */
class Level
{
public:
    Level(const std::string& filename);
    virtual ~Level();
protected:
    shared_ptr<Terrain>      terrain;
    std::vector<glm::vec2>   spawnPoints;
    std::vector<std::string> resourceList;
};

#endif /* LEVEL_HPP_ */
