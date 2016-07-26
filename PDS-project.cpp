//============================================================================
// Name        : PDS-project.cpp
// Author      : Luca Rickler
// Version     :
// Copyright   : All rights reserved
// Description : Hello World in C, Ansi-style
//============================================================================

#include "src/project.h"
//#include "src/FIFOQueue.cpp"
//#include "src/Message.h"
//#include "src/Agent.h"
//#include "src/Action.h"
//#include "src/thread_code.h"
#include "src/Runtime.h"

int main(int argc, char** argv) {
	puts("Mine!");

	Project::System::Runtime* runtime = new Project::System::Runtime();
	runtime->Init(argc, argv);
	return 0;
}
