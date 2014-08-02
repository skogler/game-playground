#ifndef WINDOW_HPP_
#define WINDOW_HPP_

struct VideoMode
{
    unsigned int width;
    unsigned int height;
    unsigned int bitsPerPixel;
};

/**
 * Creates the window, also manages the creation of the rendering context.
 */
class Window
{
public:
    Window()
    {
    }
    virtual ~Window()
    {
    }

    virtual void swapBuffers() = 0;

    virtual void setTitle(const std::string& title) = 0;
    virtual const std::string& getTitle()           = 0;

    virtual void setFullscreen(bool fullscreen) = 0;
    virtual bool getFullscreen()                = 0;

    virtual void setSize(unsigned int width, unsigned int height) = 0;
};

#endif /* WINDOW_HPP_ */
