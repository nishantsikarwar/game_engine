CC		:= g++
C_FLAGS := -std=c++17 -Wall -Wextra -g

BIN		:= bin
SRC		:= Sandbox/src
INCLUDE	:= Engine/src
LIB		:= Lib -lglfw3 -lX11 -lXrandr -lXinerama -lXi -lXxf86vm -lXcursor -ldl -lGL -lm -lpthread -lGLEW

LIBRARIES	:=

ifeq ($(OS),Windows_NT)
EXECUTABLE	:= main.exe
else
EXECUTABLE	:= main
endif

all: $(BIN)/$(EXECUTABLE)

clean:
	$(RM) $(BIN)/$(EXECUTABLE)

run: all
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp
	$(CC) $(C_FLAGS) -I$(INCLUDE) $^ -o $@ -L$(LIB) $(LIBRARIES)