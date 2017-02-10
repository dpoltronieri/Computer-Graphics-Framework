CC = g++
NAME = cgprog
FLAGS = -Wno-narrowing
HEADERS = -lglut -lGLU -lGL -I.

all: compile run

compile:
	$(CC) main.cpp -std=c++11 $(FLAGS) $(HEADERS) -o $(NAME)

run:
	./$(NAME) &

.PHONY: clean

clean:
	rm cgprog
