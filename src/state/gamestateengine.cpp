/*
 * GameStateEngine.cpp
 *
 *  Created on: Jun 11, 2012
 *      Author: zeheron
 */

#include "gamestateengine.hpp"

#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

#include "core/resourcemanager.hpp"
#include "gamestate.hpp"
#include "graphics/cameras/freemovementcam.hpp"
#include "graphics/cameras/noopcamera.hpp"
#include "graphics/oglrenderer.hpp"
#include "utils/logger.hpp"

#include <boost/filesystem.hpp>
#include <boost/thread.hpp>
#include <iostream>

void GLAPIENTRY oglErrorCallback(GLenum      source,
                                 GLenum      type,
                                 GLuint      id,
                                 GLenum      severity,
                                 GLsizei     length,
                                 const char* message,
                                 void*       userParam)
{
    Logger::debug(message);
}

GameStateEngine::GameStateEngine(shared_ptr<FPSManager> fpsManager)
    : inputManager(new InputManager())
    , inputMapper(new InputMapper())
    , resourceManager(new ResourceManager(boost::filesystem::path("resources")))
    , mMainWindow(nullptr)
    , mContext(nullptr)
    , fpsManager(fpsManager)
    , defaultCamera(new NoOpCamera())
    , mEvent()
{
}

GameStateEngine::~GameStateEngine()
{
    if (mContext)
    {
        SDL_GL_DeleteContext(mContext);
    }
    if (mMainWindow)
    {
        SDL_DestroyWindow(mMainWindow);
    }
    SDL_Quit();
}

/**
 * Initializes the GameStateEngine
 */
bool GameStateEngine::init()
{
    running = true;

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        throw std::runtime_error("Error initializing SDL.");
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);

    if (!(mMainWindow =
              SDL_CreateWindow("game-playground", SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED, 720, 480,
                               SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE)))
    {
        mMainWindow = nullptr;
        throw std::runtime_error("Error opening SDL window.");
    }

    mContext = SDL_GL_CreateContext(mMainWindow);
    if (!mContext)
    {
        throw std::runtime_error(
                  "Error initializing OpenGL(with SDL2), maybe because of no/old video driver.");
    }

    // Glew error checking
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        throw std::runtime_error(
                  "Error initializing OpenGL(GLEW), maybe because of no/old video driver.");
    }

    if (glewIsSupported("GL_ARB_debug_output"))
    {
        glDebugMessageCallbackARB(oglErrorCallback, NULL);
        glEnable(GL_DEBUG_OUTPUT);
    }
    else {
        Logger::error("NO DEBUG OUTPUT!!!!");
    }
    renderer =
        shared_ptr<Renderer>(new OGLRenderer(resourceManager, defaultCamera));
    int x;
    int y;
    SDL_GetWindowSize(mMainWindow, &x, &y);
    SDL_SetWindowGrab(mMainWindow, SDL_TRUE);
    SDL_SetRelativeMouseMode(SDL_TRUE);
    renderer->setWindowSize(x, y);
    return true;
}

void GameStateEngine::changeGameState(shared_ptr<GameState> state)
{
    this->pushState(state);
}

/*
 * Adds a new state to the vector stack
 */
void GameStateEngine::pushState(shared_ptr<GameState> state)
{
    state->init();
    states.push_back(state);
}

/*
 * Removes the last state
 */
void GameStateEngine::popState()
{
    shared_ptr<GameState> last = states.back();
    states.pop_back();
}

/*
 * This function will execute the input event handling of the last state in the
 * vector.
 */
void GameStateEngine::handleInput()
{
    shared_ptr<GameState> gstate = states.back();
    while (SDL_PollEvent(&mEvent))
    {
        if (mEvent.type == SDL_QUIT || 
                (mEvent.type == SDL_KEYDOWN && mEvent.key.keysym.sym == SDLK_ESCAPE))
        {
            quit();
        }
        if (mEvent.type == SDL_WINDOWEVENT &&
            mEvent.window.event == SDL_WINDOWEVENT_RESIZED)
        {
            renderer->setWindowSize(mEvent.window.data1, mEvent.window.data2);
        }
        inputMapper->mapInputEvent(mEvent);
    }
    gstate->handleEvents(inputMapper->retrieveInputEvent());
    inputMapper->endFrame();
}

/*
 * This function will execute the world update of the last state in the vector.
 */
void GameStateEngine::update()
{
    states.back()->update();
}

/*
 * This function will execute the rendering of the last state in the vector.
 */
void GameStateEngine::render()
{
    states.back()->render();
}

void GameStateEngine::updateWindow()
{
    SDL_GL_SwapWindow(mMainWindow);
}
