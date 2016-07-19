CXXFLAGS =	-std=c++11	-O2 -g  -Wall -fmessage-length=0

OBJS =		PDS-project.o src/Runtime.o src/project.h

LIBS =

TARGET =	bin/PDS-project

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
