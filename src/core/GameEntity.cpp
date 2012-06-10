/*
 * GameEntity.cpp
 *
 *  Created on: Jun 10, 2012
 *      Author: zeheron
 */

#include "GameEntity.hpp"

GameEntity::GameEntity() {
	uid = UIDGenerator::instance()->next();
}

GameEntity::~GameEntity() {
	// TODO Auto-generated destructor stub
}

