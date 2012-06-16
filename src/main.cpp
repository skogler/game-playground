#include <iostream>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <GL/glew.h>

#include "utils/config.h"
#include "graphics/resources/mesh.hpp"
#include "graphics/camera.hpp"
#include "graphics/scene.hpp"
#include <glm/glm.hpp>
#include <iostream>
#include "utils/FPSManager.hpp"
#include <boost/thread.hpp>
#include "state/GameStateEngine.hpp"
#include "core/inputmanager.hpp"
#include "state/core_states/gamestateactive.hpp"
using namespace std;

int main() {

	GameStateEngine gse;
	FPSManager* fps = new FPSManager();


	if(!gse.init())
	{
		//TODO error handling
		cout << "glew init failed" << endl;
		return 1;
	}

	gse.setRunning(true);
	gse.pushState(new GameStateActive());
	while(gse.isRunning())
	{
		fps->markStartPoint();
		cout << "input" << endl;
		gse.handleInput();
		cout << "update" << endl;
		gse.update();
		cout << "render" << endl;
		gse.render();

		fps->markEndPoint();
		cout << "Delta: " << fps->getDelta() << endl;
	}

	gse.cleanup();
/*
	while(window.isOpen())
	{
		fps->markStartPoint();

		//InputHandling
		sf::Event event;
		while(window.pollEvent(event))
		{
			gse->handleEvents();
		}

		//Update -> Render flow
		gse->update();
		gse->render();



		fps->markEndPoint();
	}
	/*

	 Camera * camera = new Camera();
	 camera->move(-20.0f);
	 Scene scene(camera);

	 while (window.isOpen())
	 {
	 fps->markStartPoint();

	 camera->turn(0.2, 0.0);

	 fps->markEndPoint();
	 cout << fps->getDelta() << endl;

	 sf::Event event;
	 while (window.pollEvent(event))
	 {
	 if (event.type == sf::Event::Closed)
	 window.close();
	 }

	 scene.render();
	 window.display();
	 }


	 */

	return 0;
}

