CXXFLAGS =	-std=c++11	-O2 -g  -Wall -fmessage-length=0 -lpthread

SYSOBJ = 	src/Runtime.o src/FIFOQueue.o src/thread_code.o
AGENTOBJ = 	src/Agent.o src/Action.o
COMMSOBJ = 	src/Message.o
OBJS =		PDS-project.o
OBJS += 	$(SYSOBJ)
OBJS += 	$(AGENTOBJ)
OBJS +=		$(COMMSOBJ)

LIBS =

TARGET =	bin/PDS-project

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS) $(CXXFLAGS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
