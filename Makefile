# Variables
CXX = g++
CXXFLAGS = -std=c++17 -Wall

# Directorys
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp) \
       $(wildcard $(SRC_DIR)/todolist/*.cpp) \
       $(wildcard $(SRC_DIR)/exceptions/*.cpp)

# Object files
OBJS = $(patsybst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# Executable name
TARGET = $(BIN_DIR)/task_list

# Rules
all: $(TARGET)

$(TARGET): $(OBJS)
	# Creates /bin/ directory if not exists
	@mkdir -p $(BIN_DIR)  
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	# Creates /bin/ directory if not exists
	@mkdir -p $(OBJ_DIR)  
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET)
