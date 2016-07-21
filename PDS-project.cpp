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

	Project::System::Runtime* runtime = new Project::System::Runtime();
	runtime->Init(argc, argv);
	return 0;
}
