/*
 * CollitionManager.h
 *
 *  Created on: 7/5/2015
 *      Author: diego
 */

#ifndef COLLITIONMANAGER_H_
#define COLLITIONMANAGER_H_

#include <iostream>
#include <map>
using namespace std;

class CollitionManager {
public:
	static CollitionManager* Instance();
	virtual ~CollitionManager() {
			delete(t_pInstance);
			t_pInstance = NULL;
		}

	void resetInstance();
	void solveCollitions();

private:
	static CollitionManager* t_pInstance;
	CollitionManager();
};

#endif /* COLLITIONMANAGER_H_ */
