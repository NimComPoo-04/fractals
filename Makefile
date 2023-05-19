CC = gcc
CFLAGS = -Wall -Wextra -ggdb -std=c18 -O0 # -Werror

SRC = $(wildcard *.c)
OBJ = $(SRC:%.c=obj/%.o)

INC = -I libs/glfw/include -I libs/glad/include
LIB = libs/glad/glad.o -L libs/glfw/lib-mingw-w64/ -lglfw3dll

EXE = fractals.exe

all: build $(EXE)

build:
	@mkdir -p obj

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

obj/%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^ $(INC)

clean:
	rm -rf obj $(EXE)

run: all
	./$(EXE)
