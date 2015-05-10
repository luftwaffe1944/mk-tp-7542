/*
 * CollitionManager.cpp
 *
 *  Created on: 7/5/2015
 *      Author: diego
 */

#include "../headers/Box.h"
#include "../headers/Collitionable.h"
#include "../headers/CollitionManager.h"
#include "../headers/Log.h"

CollitionManager* CollitionManager::cm_pInstance = NULL;

CollitionManager* CollitionManager::Instance() {
	if (!cm_pInstance) {
		cm_pInstance = new CollitionManager();
		return cm_pInstance;
	} else {
		return cm_pInstance;
	}
}

CollitionManager::CollitionManager() {

}

void CollitionManager::solveCollitions(vector<Collitionable*> objects){

	Collitionable* actualObject;
	Collitionable* nextObject;
	vector<Box*> actualObjectBoxes;
	vector<Box*> nextObjectBoxes;

	int cantObjects = objects.size();
	for (std::vector<Collitionable*>::size_type i = 1; i <= cantObjects;	i++) {
	//for (int i=1; i<=(cantObjects-1); i++){  //itera todos los objectos
		 actualObject = objects[i-1];
		for (std::vector<Collitionable*>::size_type j=1;j<=(cantObjects-i); j++){ //itera uno contra todos
			nextObject = objects[(i-1)+j];
			//verificar colision entre boxes

			actualObjectBoxes = actualObject->getCShapes();
			nextObjectBoxes = nextObject->getCShapes();

			for (int k=1; k<=(actualObjectBoxes.size()); k++){
				Box* actualBox = actualObjectBoxes[k-1];
				Box* newActualBox = actualBox->cloneBox(); //box auxiliar clonada para expandir

				for (int n=1; n<=(nextObjectBoxes.size()); n++){
					Box* nextBox = nextObjectBoxes[n-1];
 					Box* newNextBox = nextBox->cloneBox(); //box auxiliar clonada para expandir

					if (actualObject->getCMoving()){
						//expandir box
						float newX,newY;
						actualObject->getCNextPosition(&newX, &newY);
					}
					if (nextObject->getCMoving()){
						//expandir box
						float newX,newY;
						nextObject->getCNextPosition(&newX, &newY);
					}

					if (newActualBox->isColliding(newNextBox)){ //verifica superposicion
						//resolver evento de colision
						FILE_LOG(logDEBUG) << "Collition detected" ;
					}

					//--
					newNextBox->~Box();
				}
				newActualBox->~Box();
			}
		}
	}
}





