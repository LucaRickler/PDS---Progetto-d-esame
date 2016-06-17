CXXFLAGS =	-O2 -g -Wall -fmessage-length=0

OBJS =		PDS-project.o

LIBS =

TARGET =	PDS-project

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
