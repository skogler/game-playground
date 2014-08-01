/*
 * gamestateactive.hpp
 *
 *  Created on: Jun 15, 2012
 *      Author: zeheron
 */

#ifndef GAMESTATEACTIVE_HPP_
#define GAMESTATEACTIVE_HPP_

#include <list>
#include <boost/scoped_ptr.hpp>

#include "core/definitions.hpp"
#include "core/gameentity.hpp"
#include "core/inputmanager.hpp"
#include "core/resources/terrain.hpp"
#include "graphics/cameras/freemovementcam.hpp"
#include "graphics/renderedentity.hpp"
#include "graphics/renderer.hpp"
#include "graphics/light.hpp"
#include "state/gamestate.hpp"
#include "state/gamestateengine.hpp"

#include <SFML/Window.hpp>

class GameStateActive: public GameState
{
	public:
		GameStateActive(shared_ptr<Renderer> renderer,
				shared_ptr<InputManager> inputManager,
				shared_ptr<ResourceManager> resourceManager);
		virtual ~GameStateActive();

		void init();
		void cleanup();

		void pause();
		void resume();

		void handleEvents(InputEvent& inputEvent);
		void update();
		void render();
		void drawGround();

	private:
		shared_ptr<InputManager> inputManager;
		shared_ptr<ResourceManager> resourceManager;
		shared_ptr<FreeMovementCam> freeCam;
		shared_ptr<Renderer> renderer;
		std::list<shared_ptr<RenderedEntity> > entities;
		std::vector<shared_ptr<Light> > lights;

		//Test start
		shared_ptr<RenderedEntity> m1;
		shared_ptr<RenderedEntity> m2;
		shared_ptr<Terrain> terrain;
		//Test end
};

#endif /* GAMESTATEACTIVE_HPP_ */
