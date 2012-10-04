#ifndef OGLERROR_HPP_
#define OGLERROR_HPP_

#include <stdexcept>

class OGLError: public std::exception
{
public:
	OGLError(int errorCode);

	virtual const char * what() const throw();

protected:
	int errorCode;
};

#endif /* OGLERROR_HPP_ */
