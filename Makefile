
# DIR=$(shell pwd)
DIR=.
OBJ_DIR=$(DIR)/build
SRC_DIR=$(DIR)/src
INC_DIR=$(DIR)/include

OBJS=$(patsubst  $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(wildcard $(SRC_DIR)/*.$(EXTENSION) ))

EXTENSION=cpp
CC=g++
DEBUG=-DUSE_DEBUG
CFLAGS=-Wall -W 
LDFLAGS=
INCLUDE=-I$(INC_DIR)
TARGET=xcc




all:$(OBJS)
	$(CC) -o $(OBJ_DIR)/$(TARGET) $(OBJS) $(LDFLAGS)


$(OBJ_DIR)/%.o:$(SRC_DIR)/%.$(EXTENSION) 
	$(CC) $< -o $@ -c $(CFLAGS) $(INCLUDE)

run: 
	@./build/xcc ./test/print
	@gcc -static test.s -o tmp
	@-./tmp 
	


.PHONY:clean
clean:
	@echo "Remove linked and compiled files......"
	rm -rf $(OBJ) ./build