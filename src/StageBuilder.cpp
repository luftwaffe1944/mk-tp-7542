/*
 * StageBuilder.cpp
 *
 *  Created on: 28/3/2015
 *      Author: mauro
 */

#include "../headers/StageBuilder.h"

StageBuilder::StageBuilder() {
	// TODO Auto-generated constructor stub

}

StageBuilder::~StageBuilder() {
	// TODO Auto-generated destructor stub
}

Stage StageBuilder::create(){

	Stage stage;

	Json::Value root;

	std::ifstream config_doc("config_doc.json", std::ifstream::binary);

	// Get the value of the member of root named 'my-encoding', return 'UTF-32' if there is no
	// such member.
	std::string my_encoding = root.get("ventana", "ventana_default" ).asString();


	return stage;

}

