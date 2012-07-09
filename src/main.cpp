#include <iostream>
#include <SFML/Graphics.hpp>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <boost/format.hpp>

#include "core/inputmanager.hpp"
#include "state/GameStateEngine.hpp"
#include "state/core_states/gamestateactive.hpp"
#include "utils/config.h"
#include "utils/logger.hpp"
#include "utils/FPSManager.hpp"
using namespace std;

int main()
{
	shared_ptr<FPSManager> fps(new FPSManager);
	GameStateEngine gse(fps);

	if(!gse.init())
	{
		//TODO error handling
		cout << "glew init failed" << endl;
		return 1;
	}

	gse.pushState(new GameStateActive(&gse));
	while(gse.isRunning())
	{
		fps->markStartPoint();
		gse.handleInput();
		gse.update();
		gse.render();
		gse.updateWindow();
		fps->markEndPoint();
		//Logger::debug((boost::format("Delta: %d") % fps->getDelta()).str());
	}

	gse.cleanup();

	return 0;
}

