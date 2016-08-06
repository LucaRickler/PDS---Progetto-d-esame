/*
 * main.cpp
 *
 *  Created on: 06/ago/2016
 *      Author: luca
 */

#include "../src/project.h"
using namespace Project;

//Define actions here

//Define  agents here

int main() {
	System::Runtime* runtime = new System::Runtime(1);
	runtime->SetMaxTurns(1);

	//Here goes agent creation

	runtime->Init(1);
}

