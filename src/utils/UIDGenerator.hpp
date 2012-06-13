/*
 * UIDGenerator.h
 *
 *  Created on: Jun 10, 2012
 *      Author: zeheron
 */

#ifndef UIDGENERATOR_H_
#define UIDGENERATOR_H_

class UIDGenerator {

public:
      static UIDGenerator * instance ();
      int next () { return uid++; }

private:
      UIDGenerator ();
      virtual ~UIDGenerator();

      static UIDGenerator * uidGen;
      int uid;
};

#endif /* UIDGENERATOR_H_ */
