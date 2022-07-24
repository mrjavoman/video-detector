# Defne compiler and options
CC   = g++
OPTS = -std=c++17

# define any compile-time flags
CFLAGS = -Wall -g -lcurl
OPENCV = `pkg-config --cflags --libs opencv4`

# define any directories containing header files other than /usr/include
#
# e.g. INCLUDES = -I/home/newhall/include  -I../include
#INCLUDES = -I/home/xavi/anaconda3/include

# define library paths in addition to /usr/lib
#   if I wanted to include libraries not in /usr/lib I'd specify
#   their path using -Lpath, something like: -I/home/xavi/anaconda3/include  
# e.g. LFLAGS = -L/home/newhall/lib  -L../lib
#LFLAGS = -L/home/xavi/anaconda3/lib

# Define the output directory
OUT_DIR = build
BIN = $(OUT_DIR)/bin

all: $(OUT_DIR) main.o detector.o pushoverapi.o logger.o
	$(CC) $(CFLAGS) $(OPTS) $(OPENCV) -o $(BIN)/detect $(OUT_DIR)/main.o $(OUT_DIR)/detector.o $(OUT_DIR)/pushoverapi.o $(OUT_DIR)/logger.o

# Create the object files for the executable
main.o: src/main.cpp src/detector/detector.hpp
	$(CC) $(CFLAGS) $(OPTS) $(OPENCV) -c src/main.cpp -o $(OUT_DIR)/main.o

detector.o: src/detector/detector.cpp src/pushover/pushoverapi.hpp
	$(CC) $(CFLAGS) $(OPTS) $(OPENCV) -c src/detector/detector.cpp -o $(OUT_DIR)/detector.o

pushoverapi.o: src/pushover/pushoverapi.cpp
	$(CC) $(CFLAGS) $(OPTS) $(OPENCV) -c src/pushover/pushoverapi.cpp -o $(OUT_DIR)/pushoverapi.o

logger.o: src/logger/logger.cpp
	$(CC) $(CFLAGS) $(OPTS) $(OPENCV) -c src/logger/logger.cpp -o $(OUT_DIR)/logger.o

# Create buid directory
$(OUT_DIR):
	mkdir -p $(OUT_DIR)
	mkdir -p $(OUT_DIR)/bin

clean:
	rm -rf $(OUT_DIR)
