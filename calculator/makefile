##
# TCALC: Terminal Calculator
#
# @file
# @version 0.1

CXX = clang++
CXXFLAGS =
LDFLAGS = -lncurses
TARGET = main
SRCS = main.cpp helpers.cpp
OBJS = $(SRCS:.cpp=.o)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

# end
