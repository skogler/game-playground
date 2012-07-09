#ifndef INVALIDRESOURCEERROR_HPP_
#define INVALIDRESOURCEERROR_HPP_

#include <stdexcept>
#include <string>

class InvalidResourceError: virtual public std::exception
{
public:
	InvalidResourceError(const std::string & filename) :
					filename(filename)
	{
	}
	virtual ~InvalidResourceError() throw ()
	{
	}

	virtual const char* what() const throw ()
	{
		return filename.c_str();
	}

protected:
	std::string filename;
};

#endif /* INVALIDRESOURCEERROR_HPP_ */
