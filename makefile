prog:main.o minimap.o
	gcc main.o minimap.o -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf -o prog -g;./prog
minimap.o:minimap.c
	gcc -c minimap.c
main.o:main.c
	gcc -c main.c -g
clean:
	rm -f *.o prog

.PHONY:clean