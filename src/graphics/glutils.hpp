#ifndef GLUTILS_HPP_
#define GLUTILS_HPP_

#include "graphics/exceptions/oglerror.hpp"

inline void checkGLErrors()
{
    int errorCode = glGetError();

    if (errorCode)
    {
        int* crash = 0;
        *crash = 0;
        throw OGLError(errorCode);
    }
}

#endif /* GLUTILS_HPP_ */
