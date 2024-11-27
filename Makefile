ti = -Wall -Wextra
h = fonctions.h

main : main.o fonctions_bases.o IA.o
	gcc $^ -o $@ $(ti)

serv: userSimple.c fonctions_bases.c
	$(CC) $(CFLAGS) -L. -o serv userSimple.c fonctions_bases.c -lothello

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
	rm -f *.o test serv main

tar : 
	tar -cf projet.tar *.c *.h Makefile
