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
		gse.handleInput();
		gse.update();
		gse.render();
		gse.updateWindow();
		fps->markEndPoint();
		//cout << "Delta: " << fps->getDelta() << endl;
	}

	gse.cleanup();

	return 0;
}

