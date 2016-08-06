CXXFLAGS =	-std=c++11	-O2 -g  -Wall -fmessage-length=0 -lpthread

RELPATH =	../

SYSOBJ = 	$(RELPATH)src/Runtime.o $(RELPATH)src/FIFOQueue.o $(RELPATH)src/thread_code.o
AGENTOBJ = 	$(RELPATH)src/Agent.o $(RELPATH)src/Action.o
COMMSOBJ = 	$(RELPATH)src/Message.o
OBJS =		main.o $(SYSOBJ) $(AGENTOBJ) $(COMMSOBJ)

LIBS =

TARGET =	project	

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS) $(CXXFLAGS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
