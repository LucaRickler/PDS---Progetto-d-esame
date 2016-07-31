CXXFLAGS =	-std=c++11 -O2 -g -Wall -fmessage-length=0 -lpthread

RUNTIME = 	 ../Action.o ../FIFOQueue.o ../Agent.o ../thread_code.o ../Runtime.o Runtime_test.o  #../LogOutput.o
FIFOQ = 	../FIFOQueue.o FIFOQueue_test.o 
AGENT = 	../Agent.o ../Action.o ../FIFOQueue.o ../Message.o Agent_test.o
ACTION = 	../Action.o Action_test.o

OBJS = 	$(RUNTIME) $(FIFOQ) $(AGENT) $(ACTION)

LIBS =

RuntimeTest:	$(RUNTIME)
	$(CXX) -o $@ $(RUNTIME) $(LIBS) $(CXXFLAGS)

FIFOQTest:	$(FIFOQ)
	$(CXX) -o $@ $(FIFOQ) $(LIBS) $(CXXFLAGS)

AgentTest:	$(AGENT)
	$(CXX) -o $@ $(AGENT) $(LIBS) $(CXXFLAGS)

ActionTest: $(ACTION)
	$(CXX) -o $@ $(ACTION) $(LIBS) $(CXXFLAGS)

all:	RuntimeTest FIFOQTest AgentTest ActionTest


TARGET = 	RuntimeTest FIFOQTest AgentTest ActionTest

clean:
	rm -f $(OBJS) $(TARGET)
