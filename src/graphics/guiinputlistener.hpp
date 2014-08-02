#ifndef GUIINPUTLISTENER_HPP_RPDNXOWA
#define GUIINPUTLISTENER_HPP_RPDNXOWA

#include "core/inputlistener.hpp"
#include <CEGUI/CEGUI.h>

class GuiInputListener : public InputListener
{
public:
    GuiInputListener(CEGUI::GUIContext& context);
    virtual ~GuiInputListener();
    virtual void handleinput(InputEvent& inputEvent) override;

private:
    CEGUI::GUIContext& context;
};

#endif /* end of include guard: GUIINPUTLISTENER_HPP_RPDNXOWA */
