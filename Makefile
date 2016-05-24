##############################
# Makefile du TP "EDO"
##############################


#modifier le chemin de LINALG selon ou se trouve votre fichier Vecteur.h
LINALG=./Librairie_AlgebreLineaire

OBJECTS = main.o Particule.o $(LINALG)/Vecteur.o
all: main

COMPILCOMMAND=g++  -I$(LINALG)  -I`root-config --incdir` -c -o $@   $<

# Commande generique pour generer tous les fichiers objets
# a partir des fichiers d'en tete et des fichiers source
%.o: %.cpp %.h
	$(COMPILCOMMAND)

#la regle ci-dessus ne marche pas necessairement pour main.o du fait de l'absence d'un fichier main.h
%.o: %.cpp 
	$(COMPILCOMMAND)

# Fichiers source a generer
# A noter les "dependances" en plus des fichiers d'en tete et des fichiers source 
# definis dans la commande generique ci-dessus

Particule.o:       Particule.h
main.o:          Particule.h

# Creation de l'executable
# A noter la presence de la librairie gsl utilisee dans la classe Vecteur
main: $(OBJECTS)
	g++ -o main $(OBJECTS)  -lgsl -lgslcblas `root-config --libs`

# Commande de nettoyage
clean:
	rm -f *.o main *.dat *~
