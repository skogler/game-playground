/*
 * UIDGenerator.h
 *
 *  Created on: Jun 10, 2012
 *      Author: zeheron
 */

#ifndef UIDGENERATOR_H_
#define UIDGENERATOR_H_

class UIDGenerator
{
public:
	static UIDGenerator * instance();
	inline int next()
	{
		return uid++;
	}

private:
	UIDGenerator() :
			uid(0)
	{
	}

	static UIDGenerator * uidGen;
	int uid;
};

#endif /* UIDGENERATOR_H_ */
