//============================================================================
// Name        : PDS-project.cpp
// Author      : Luca Rickler
// Version     :
// Copyright   : All rights reserved
// Description : Hello World in C, Ansi-style
//============================================================================

#include "src/project.h"

int main(int argc, char** argv) {
	puts("Mine!");

	Project::Agent::Action act1 = Project::Agent::Action();

	act1.DoAction()();
	return 0;
}
