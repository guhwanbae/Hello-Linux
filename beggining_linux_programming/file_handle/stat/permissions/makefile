TARGET			= show_permissions

CXX			= g++
CXXFLAGS		= -W -Wall -O2

OBJECTS			= show_permissions.o
SRCS			= show_permissions.cpp

$(TARGET) : $(OBJECTS)
	$(CXX) -o $(TARGET) $(OBJECTS)

$(OBJECTS) : $(SRCS)
	$(CXX) $(CXXFLAGS) -c $(SRCS)

clean :
	rm -f *.o $(TARGET)
