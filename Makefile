CC = gcc
CFLAGS = -Wall -Wextra -ggdb -std=c18 -O0

SRC = $(wildcard *.c)
OBJ = $(SRC:%.c=obj/%.o)

INC = -I libs/glfw/include -I libs/glad/include
LIB = libs/glad/glad.o -L libs/glfw/lib-mingw-w64/ -lglfw3 -lopengl32 -luser32 -lgdi32

EXE = fractals.exe

all: build $(EXE)

build:
	@mkdir -p obj

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

obj/main.o: main.c
	$(CC) $(CFLAGS) -c -o $@ $< $(INC)

obj/%.o: %.c %.h
	$(CC) $(CFLAGS) -c -o $@ $< $(INC)

clean:
	rm -rf obj $(EXE)

run: all
	./$(EXE)
