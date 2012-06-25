/*
 * gamestateactive.hpp
 *
 *  Created on: Jun 15, 2012
 *      Author: zeheron
 */

#ifndef GAMESTATEACTIVE_HPP_
#define GAMESTATEACTIVE_HPP_

#include "../gamestate.hpp"
#include <list>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include "../../graphics/cameras/freemovementcam.hpp"

#include "../../core/gameentity.hpp"
#include "../../core/inputmanager.hpp"
#include "../../state/GameStateEngine.hpp"
#include "../../graphics/renderedentity.hpp"
#include "../../core/resources/terrain.hpp"

class GameStateActive: public GameState
{
public:
	GameStateActive(GameStateEngine* game);
	virtual ~GameStateActive();

	void init();
	void cleanup();

	void pause();
	void resume();

	void handleEvents(InputEvent* inputEvent);
	void update();
	void render();
	void drawGround();

private:
	boost::shared_ptr<InputManager> inputManager;
	boost::shared_ptr<FreeMovementCam> freeCam;
	std::list<boost::shared_ptr<RenderedEntity> > entities;

	//Test start
	boost::shared_ptr<RenderedEntity> m1;
	boost::shared_ptr<RenderedEntity> m2;
	boost::shared_ptr<Terrain> terrain;
	//Test end

	GLuint modelMatrix;
	GLuint viewMatrix;
	GLuint projectionMatrix;
};

#endif /* GAMESTATEACTIVE_HPP_ */
