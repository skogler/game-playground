#ifndef WINDOW_INC
#define WINDOW_INC

class Window
{
public:
    Window ();
    virtual ~Window ();

private:
    void render() const;
    void clear() const;

    Scene * renderedScene;
};

#endif /* end of include guard: WINDOW_INC */
