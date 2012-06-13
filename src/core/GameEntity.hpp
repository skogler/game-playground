/*
 * GameEntity.hpp
 *
 *  Created on: Jun 10, 2012
 *      Author: zeheron
 */

#ifndef GAMEENTITY_HPP_
#define GAMEENTITY_HPP_


class GameEntity {
public:
	GameEntity();
	virtual ~GameEntity();

	virtual void update() {} ;
	virtual void render() {} ;

private:
	 int uid;

};

#endif /* GAMEENTITY_HPP_ */
