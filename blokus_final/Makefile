


EXE = Blocus
OFILES = Ressources.o \
	 Utilitaires.o \
         Game.o \
	main.o

CC = gcc

CFLAGS = -ansi -g



but: ${EXE}

Ressources.o: Ressources.h

Utilitaires.o : Utilitaires.h  Ressources.h  Game.h 

Game.o : Game.h Ressources.h Utilitaires.h

Main.o : Ressources.h Utilitaires.h Game.h



${EXE} : $(OFILES)
	$(CC) $(CFLAGS) -o ${EXE} $(OFILES) -lgraph


clean :
	-rm -f $(OFILES) ${EXE}


.PHONY : but clean
