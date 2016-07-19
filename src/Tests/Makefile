CXXFLAGS =	-std=c++11	-O2 -g  -Wall -fmessage-length=0

RUNTIME = 	../Runtime.o ../FIFOQueue.o Runtime_test.o
FIFOQ = 	../FIFOQueue.o FIFOQueue_test.o 
AGENT = 	../Agent.o ../Action.o ../FIFOQueue.o ../Message.o Agent_test.o
ACTION = 	../Action.o ../Agent.o Action_test.o

OBJS = 	$(RUNTIME) $(FIFOQ) $(AGENT) $(ACTION)

LIBS =

RuntimeTest:	$(RUNTIME)
	$(CXX) -o $@ $(RUNTIME) $(LIBS)

FIFOQTest:	$(FIFOQ)
	$(CXX) -o $@ $(FIFOQ) $(LIBS)

AgentTest:	$(AGENT)
	$(CXX) -o $@ $(AGENT) $(LIBS)

ActionTest: $(ACTION)
	$(CXX) -o $@ $(ACTION) $(LIBS)

all:	RuntimeTest FIFOQTest AgentTest ActionTest


TARGET = 	RuntimeTest FIFOQTest AgentTest ActionTest

clean:
	rm -f $(OBJS) $(TARGET)
