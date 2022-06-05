all: Demineur

main.o: main.c fonctionMenu.h fonctionJeu.h fonctionGenerale.h
	gcc -c $< -o $@

fonctionMenu.o: fonctionMenu.c fonctionMenu.h
	gcc -c $< -o $@

fonctionGenerale.o: fonctionGenerale.c fonctionGenerale.h
	gcc -c $< -o $@

fonctionJeu.o: fonctionJeu.c fonctionJeu.h
	gcc -c $< -o $@

Demineur: main.o fonctionMenu.o fonctionGenerale.o fonctionJeu.o
	gcc -c $^ -o $@