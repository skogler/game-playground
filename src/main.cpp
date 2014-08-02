#include "core/inputmanager.hpp"
#include "errorhandler.hpp"
#include "graphics/guiinputlistener.hpp"
#include "state/core_states/gamestateactive.hpp"
#include "state/gamestateengine.hpp"
#include "utils/config.h"
#include "utils/fpsmanager.hpp"
#include "utils/logger.hpp"

#include <CEGUI/CEGUI.h>
#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <boost/format.hpp>
#include <glm/glm.hpp>
#include <iostream>

using std::cout;
using std::endl;

int main()
{
    registerErrorHandler();
    shared_ptr<FPSManager> fps(new FPSManager());
    GameStateEngine        gse(fps);

    if (!gse.init())
    {
        // TODO error handling
        cout << "glew init failed" << endl;
        return 1;
    }

    shared_ptr<InputListener> guiListener = make_shared<GuiInputListener>(
        CEGUI::System::getSingleton().getDefaultGUIContext());
    gse.getInputManager()->addListener(guiListener);

    shared_ptr<GameState> gameStateActive(new GameStateActive(
                                              gse.getRenderer(),
                                              gse.getInputManager(),
                                              gse.getResourceManager()));
    gse.pushState(gameStateActive);
    int count = 0;
    while (gse.isRunning())
    {
        // Log Delta every second
        count++;
        if (count == 50)
        {
            Logger::debug((boost::format("Delta: %d") %
                           (fps->getDelta())).str());
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
