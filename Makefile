CC	:=	g++
RM  	:= rm -rf
TARGET	:=	example.exe

SOURCES = $(wildcard *.cpp)
OBJECTS = $(patsubst %.cpp, %.o, $(SOURCES))

CPPFLAGS = -g -std=c++11 -Werror -DDEBUG -c
LINK_FLAG = -O0

$(OBJECTS): %.o: %.cpp
	$(CC) $(CPPFLAGS) $< -o $@

all:  $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS)  $(LINK_FLAG)

clean:
	$(RM) $(TARGET)  *.o