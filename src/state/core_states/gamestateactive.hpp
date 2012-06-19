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
#include "../../graphics/camera.hpp"
#include "../../core/gameentity.hpp"
#include "../../graphics/resources/mesh.hpp"
#include "../../graphics/renderedentity.hpp"

class GameStateActive: public GameState {
public:
	GameStateActive();
	virtual ~GameStateActive();

	void init();
	void cleanup();

	void pause();
	void Resume();

	void handleEvents(InputEvent* inputEvent);
	void update(GameStateEngine* game);
	void render(GameStateEngine* game);

private:
	InputManager* inputManager;
	Camera * camera;
	std::list< boost::shared_ptr<RenderedEntity> > entities;
	boost::shared_ptr<RenderedEntity> m1;
	boost::shared_ptr<RenderedEntity> m2;


	GLuint modelMatrix;
	GLuint viewMatrix;
	GLuint projectionMatrix;


};

#endif /* GAMESTATEACTIVE_HPP_ */
