#include "guiinputlistener.hpp"

GuiInputListener::GuiInputListener(CEGUI::GUIContext& context)
    : context(context)
{
}

GuiInputListener::~GuiInputListener()
{
}


void GuiInputListener::handleinput(InputEvent& event)
{
    if (event.mouseMoved)
    {
        context.injectMouseMove(event.mouseMotionX, event.mouseMotionY);
    }
}
