CPPFLAGS = -std=c++11 -fsanitize=address
SRCS = main.cpp player.cpp match.cpp swiss.cpp
OBJS = $(SRCS:.cpp=.o)
DEPS = $(OBJS:.o=.d)

all: pa1.exe

pa1.exe: $(OBJS)
	g++11 -o $@ $(CPPFLAGS) $^

%.o: %.cpp
	g++11 $(CPPFLAGS) -MMD -MP -c $< -o $@

-include $(DEPS)

clean:
	 del *.o *.exe *.d
# On Windows, use: del *.o *.exe *.d
# On Linux or MacOS, use: rm -f *.o *.exe *.d

.PRECIOUS: $(OBJS)