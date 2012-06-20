#ifndef LEVEL_HPP_
#define LEVEL_HPP_

#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <boost/shared_ptr.hpp>

#include "terrain.hpp"

/**
 * A level defines a loadable state of the game which has
 * several properties, like the terrain, resources etc.
 */
class Level
{
public:
	Level(const std::string & filename);
	virtual ~Level();
protected:
	boost::shared_ptr<Terrain> terrain;
	std::vector<glm::vec2> spawnPoints;
	std::vector<std::string> resourceList;
};

#endif /* LEVEL_HPP_ */
