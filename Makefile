CC=clang++
CFLAGS= -std=c++11 -g -O2 -msse2
LDFLAGS = -lpthread -lX11
SOURCES=as2.cpp Camera.cpp Film.cpp Intersection.cpp Light.cpp Material.cpp Ray.cpp Scene.cpp Shape.cpp stdafx.cpp Transformation.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=as2

RM = /bin/rm -f

all: $(SOURCES) $(EXECUTABLE)
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(CFLAGS) $(OBJECTS) -o $@ $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) *.o $(EXECUTABLE)
