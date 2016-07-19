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

	Project::System::Runtime runtime = Project::System::Runtime();
	runtime.Init();
	return 0;
}
