/*
 * UIDGenerator.cpp
 *
 *  Created on: Jun 10, 2012
 *      Author: zeheron
 */

#include "UIDGenerator.hpp"

UIDGenerator* UIDGenerator::uidGen = 0;

UIDGenerator* UIDGenerator::instance() {
	if (!uidGen) {
		uidGen = new UIDGenerator();
	}
	return uidGen;
}
