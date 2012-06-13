#ifndef STATE_INC
#define STATE_INC
#include <string>
#include <SFML/Window/Event.hpp>
using std::string;
class State
{
public:
    State ();
    virtual ~State ();

    virtual void handleEvent(sf::Event event) = 0;
    virtual void start() = 0;
    virtual void exit() = 0;
    virtual void pause() = 0;
    virtual void resume() = 0;

protected:
    string name;

};

#endif /* end of include guard: STATE_INC */
