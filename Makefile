CC = gcc
CXX = g++ 

CFLAGS = -Wall -I$(WORKDIR)/include -I$(WORKDIR)/Source -I. -L. -lzlib1
#CFLAGS = -Wall -fPIC -shared -I$(WORKDIR)/include -I$(WORKDIR)/Source

TARGET = zlibtest

DIRS = .
FILES = $(foreach dir, $(DIRS), $(wildcard $(dir)/*.cpp))
OBJS = $(patsubst %.cpp, %.o, $(FILES))

OTHERFILES = 
OTHEROBJS = $(patsubst %.cpp, %.o, $(OTHERFILES))

$(TARGET): $(OBJS) $(OTHEROBJS)
	$(CXX) $(OBJS) $(OTHEROBJS) $(CFLAGS) -o $(TARGET)

$(OBJS):%.o:%.cpp
	$(CXX) -c $< -o $@ $(CFLAGS)

$(OTHEROBJS):%.o:%.cpp
	$(CXX) -c $< -o $@ $(CFLAGS)

clean:
	$(RM) $(TARGET)
	$(RM) $(OBJS)
