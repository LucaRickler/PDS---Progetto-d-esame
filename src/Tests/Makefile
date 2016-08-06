CXXFLAGS =	-std=c++11 -O2 -g -Wall -fmessage-length=0 -lpthread

RUNTIME = 	 ../Action.o ../FIFOQueue.o ../Agent.o ../thread_code.o ../Runtime.o Runtime_test.o ../Message.o #../LogOutput.o
FIFOQ = 	../FIFOQueue.o FIFOQueue_test.o 
#AGENT = 	../Agent.o ../Action.o ../FIFOQueue.o ../Message.o Agent_test.o
ACTION = 	../Action.o Action_test.o
MESSAGE =	../Action.o ../FIFOQueue.o ../Agent.o ../thread_code.o ../Runtime.o Message_test.o ../Message.o

OBJS = 	$(RUNTIME) $(FIFOQ) $(AGENT) $(ACTION)

LIBS =

MessageTest:	$(MESSAGE)
	$(CXX) -o $@ $(MESSAGE) $(LIBS) $(CXXFLAGS)

RuntimeTest:	$(RUNTIME)
	$(CXX) -o $@ $(RUNTIME) $(LIBS) $(CXXFLAGS)

FIFOQTest:	$(FIFOQ)
	$(CXX) -o $@ $(FIFOQ) $(LIBS) $(CXXFLAGS)

#AgentTest:	$(AGENT)
#	$(CXX) -o $@ $(AGENT) $(LIBS) $(CXXFLAGS)

ActionTest: $(ACTION)
	$(CXX) -o $@ $(ACTION) $(LIBS) $(CXXFLAGS)

all:	RuntimeTest FIFOQTest ActionTest MessageTest #AgentTest


TARGET = 	RuntimeTest FIFOQTest AgentTest ActionTest MessageTest

clean:
	rm -f $(OBJS) $(TARGET)
