#include "oglerror.hpp"

#include <boost/format.hpp>

OGLError::OGLError(int errorCode) :
    errorCode(errorCode)
{
}

const char* OGLError::what() const throw ()
{
    return (boost::format("Error code: %d") % errorCode).str().c_str();
}
