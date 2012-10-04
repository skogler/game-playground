#include <iostream>
#include <SFML/Graphics.hpp>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <boost/format.hpp>

#include "errorhandler.hpp"
#include "core/inputmanager.hpp"
#include "state/GameStateEngine.hpp"
#include "state/core_states/gamestateactive.hpp"
#include "utils/config.h"
#include "utils/logger.hpp"
#include "utils/FPSManager.hpp"
using namespace std;

int main()
{
	registerErrorHandler();
	shared_ptr<FPSManager> fps(new FPSManager);
	GameStateEngine gse(fps);

	if (!gse.init())
	{
		//TODO error handling
		cout << "glew init failed" << endl;
		return 1;
	}

	gse.pushState(new GameStateActive(gse.getRenderer(), gse.getInputManager(), gse.getResourceManager(), gse.getWindow()));
	int count = 0;
	while (gse.isRunning())
	{
		// Log Delta every second
		count++;
		if (count == 50)
		{
			Logger::debug((boost::format("Delta: %d") % (fps->getDelta())).str());
			count = 0;
		}
		fps->markStartPoint();
		gse.handleInput();
		gse.update();
		gse.render();
		gse.updateWindow();
		fps->markEndPoint();
	}

	return 0;
}

