CXX = g++
CXXFLAGS = -I./header

SRCS = main.cpp \
       src/linkedlist.cpp \
       src/avl.cpp \
       src/bot.cpp \
       src/server.cpp \
	   src/utils.cpp

OBJS = $(SRCS:.cpp=.o)

EXEC = server

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(EXEC)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)
