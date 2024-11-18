ti = -Wall -Wextra
h = fonctions.h

main : main.o fonctions_bases.o IA.o
	gcc $^ -o $@ $(ti)

test : test.o fonctions_bases.o
	gcc $^ -o $@ $(ti)

main.o : main.c
	gcc -c $^ -o $@ $(ti)

fonctions_bases.o : fonctions_bases.c $(h)
	gcc -c $< -o $@ $(ti)

IA.o : IA.c $(h)
	gcc -c $< -o $@ $(ti)

test.o : test.c $(h)
	gcc -c $< -o $@ $(ti)

clean :
	rm -f main *.o

tar : 
	tar -cf projet.tar *.c *.h Makefile
