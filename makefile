amazed:
	gcc "src/main.c" "src/maze.c" "src/menu.c" -lncurses -o amazed
clean:
	rm -f amazed
