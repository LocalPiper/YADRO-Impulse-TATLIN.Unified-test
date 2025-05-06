CXX = g++
CXXFLAGS = -std=c++17 -Wall -g

SRC = main.cpp tape.cpp generator.cpp k_way.cpp config.cpp
OBJ = $(SRC:.cpp=.o)

TARGET = external_sort

TMP_DIR = tmp

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET) $(TMP_DIR)/*

fclean: clean
	rm -rf $(TMP_DIR)

re: fclean all

