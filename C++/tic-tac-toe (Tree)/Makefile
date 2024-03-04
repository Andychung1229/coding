
CPPFLAGS = -std=c++11 -fsanitize=address
SRCS = main.cpp board.cpp boardtree.cpp hashtable.cpp
OBJS = $(SRCS:.cpp=.o)
DEPS = $(OBJS:.o=.d)

# //-fsanitize=address
all: pa3.exe

pa3.exe: $(OBJS)
	g++11 -o $@ $(CPPFLAGS) $^

%.o: %.cpp
	g++11 $(CPPFLAGS) -MMD -MP -c $< -o $@

-include $(DEPS)

clean:
	rm -f *.o pa3.exe *.d

.PRECIOUS: $(OBJS)