#ifndef INVALIDRESOURCEERROR_HPP_
#define INVALIDRESOURCEERROR_HPP_

#include <stdexcept>
#include <string>

class InvalidResourceError: virtual public std::exception
{
	public:
		InvalidResourceError(const std::string & filename, const std::string & message) :
			filename(filename),
			message(message)
	{
	}

		virtual ~InvalidResourceError() throw ()
		{
		}

		virtual const char* what() const throw ()
		{
			return (message + std::string(": ") + filename).c_str();
		}

	protected:
		std::string filename;
		std::string message;
};

#endif /* INVALIDRESOURCEERROR_HPP_ */
