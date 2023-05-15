# Variables
CXX = g++
SRC_DIR = src
OBJS = $(wildcard $(SRC_DIR)/*.cpp)
CXXFLAGS = -finput-charset=UTF-8 -static

# If in Windows, load resources
ifeq ($(OS),Windows_NT)
	RES_CMD = windres
	RES_FILE = res/resources.res
else
	RES_CMD = :
	RES_FILE = :
endif

# Targets
all: byter.exe

byter.exe: $(OBJS) $(RES_FILE)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(RES_FILE): res/resources.rc
	$(RES_CMD) -O coff -i $< -o $@

.PHONY: clean
clean:
	rm -f byter.exe $(RES_FILE) $(OBJS)