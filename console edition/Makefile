all : application

application : main adherents livres empruntes fichiers
	gcc -o LoanApp obj/*.o

main :
	gcc -o obj/main.o -c src/main.c

adherents :
	gcc -o obj/adherents.o -c src/adherents.c

livres :
	gcc -o obj/livres.o -c src/livres.c

empruntes :
	gcc -o obj/empruntes.o -c src/empruntes.c

fichiers :
	gcc -o obj/fichiers.o -c src/fichiers.c