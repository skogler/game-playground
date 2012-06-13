/*
 * UIDGenerator.cpp
 *
 *  Created on: Jun 10, 2012
 *      Author: zeheron
 */

#include "UIDGenerator.hpp"

UIDGenerator* UIDGenerator::uidGen = 0;

UIDGenerator::UIDGenerator() {
	// TODO Auto-generated constructor stub

}

UIDGenerator* UIDGenerator::instance() {
	if (!uidGen) {
		uidGen = new UIDGenerator();
	}
	return uidGen;
}

UIDGenerator::~UIDGenerator() {
	// TODO Auto-generated destructor stub
}
