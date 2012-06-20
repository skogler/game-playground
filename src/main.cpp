#include <iostream>
#include <SFML/Graphics.hpp>
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "core/inputmanager.hpp"
#include "state/GameStateEngine.hpp"
#include "state/core_states/gamestateactive.hpp"
#include "utils/config.h"
#include "utils/FPSManager.hpp"

using namespace std;

int main()
{
	//ResourceManager res("resources");

	GameStateEngine gse;
	FPSManager* fps = new FPSManager();

	if(!gse.init())
	{
		//TODO error handling
		cout << "glew init failed" << endl;
		return 1;
	}

	gse.setRunning(true);
	gse.pushState(new GameStateActive(&gse));
	while(gse.isRunning())
	{
		fps->markStartPoint();
		gse.handleInput();
		gse.update();
		gse.render();
		gse.updateWindow();
		fps->markEndPoint();
		cout << "Delta: " << fps->getDelta() << endl;
	}

	gse.cleanup();

	return 0;
}

