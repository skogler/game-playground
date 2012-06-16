#ifndef LEVEL_HPP_
#define LEVEL_HPP_

#include <vector>
#include <glm/glm.hpp>
#include <boost/shared_ptr.hpp>

#include "../graphics/resources/terrain.hpp"

class Level
{
public:
	Level();
	virtual ~Level();
protected:
	boost::shared_ptr<Terrain> terrain;
	std::vector<glm::vec2> spawnPoints;

};

#endif /* LEVEL_HPP_ */
