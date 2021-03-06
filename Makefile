# Defne compiler and options
CC   = g++
OPTS = -std=c++17

# define any compile-time flags
CFLAGS = -Wall -g
OPENCV = `pkg-config --cflags --libs opencv4`

# define any directories containing header files other than /usr/include
#
# e.g. INCLUDES = -I/home/newhall/include  -I../include
INCLUDES = $(shell curl-config --cflags)

# define library paths in addition to /usr/lib
#   if I wanted to include libraries not in /usr/lib I'd specify
#   their path using -Lpath, something like: -I/home/xavi/anaconda3/include  
# e.g. LFLAGS = -L/home/newhall/lib  -L../lib
LFLAGS = $(shell curl-config --libs)

# Define the output directory
OUT_DIR = build
BIN = $(OUT_DIR)/bin

all: $(OUT_DIR) main.o model.o pushoverapi.o logger.o boxdraw.o config.o
	$(CC) $(OPTS) -o $(BIN)/detect $(OUT_DIR)/main.o $(OUT_DIR)/model.o $(OUT_DIR)/pushoverapi.o $(OUT_DIR)/logger.o $(OUT_DIR)/boxdraw.o $(OUT_DIR)/config.o $(INCLUDES) $(LFLAGS) $(CFLAGS) $(OPENCV)

# Create the object files for the executable
main.o: src/main.cpp src/detector/model.hpp src/configuration/config.hpp
	$(CC) $(CFLAGS) $(INCLUDES) $(LFLAGS) $(OPTS) $(OPENCV) -c src/main.cpp -o $(OUT_DIR)/main.o

model.o: src/detector/model.cpp src/pushover/pushoverapi.hpp
	$(CC) $(CFLAGS) $(INCLUDES) $(LFLAGS) $(OPTS) $(OPENCV) -c src/detector/model.cpp -o $(OUT_DIR)/model.o

boxdraw.o: src/detector/boxdraw.cpp
	$(CC) $(CFLAGS) $(INCLUDES) $(LFLAGS) $(OPTS) $(OPENCV) -c src/detector/boxdraw.cpp -o $(OUT_DIR)/boxdraw.o

pushoverapi.o: src/pushover/pushoverapi.cpp
	$(CC) $(CFLAGS) $(INCLUDES) $(LFLAGS) $(OPTS) $(OPENCV) -c src/pushover/pushoverapi.cpp -o $(OUT_DIR)/pushoverapi.o

logger.o: src/logger/logger.cpp
	$(CC) $(CFLAGS) $(OPTS) $(OPENCV) -c src/logger/logger.cpp -o $(OUT_DIR)/logger.o

config.o: src/configuration/config.cpp
	$(CC) $(CFLAGS) $(OPTS) $(OPENCV) -c src/configuration/config.cpp -o $(OUT_DIR)/config.o


# Create buid directory
$(OUT_DIR):
	mkdir -p $(OUT_DIR)
	mkdir -p $(OUT_DIR)/bin

clean:
	rm -rf $(OUT_DIR)
