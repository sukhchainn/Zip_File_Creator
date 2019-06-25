all: main.exe

main.exe: main.o allegro_monolith-5.2.dll
	gcc -o main main.o Text_Box.o allegro_monolith-5.2.dll

main.o: main.c Text_Box.o
	gcc -c main.c -l Text_Box.o

Text_Box.o: Text_Box.c allegro_monolith-5.2.dll
	gcc -c Text_Box.c -l allegro_monolith-5.2.dll

clear:
	rm Text_Box.o main.o