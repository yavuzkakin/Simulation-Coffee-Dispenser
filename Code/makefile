Cafe.o : Cafe.h enum.h Cafe.cpp
	g++ -c Cafe.cpp

Gobelets.o : Gobelets.h enum.h Gobelets.cpp
	g++ -c Gobelets.cpp

IHM.o : IHM.h enum.h IHM.cpp
	g++ -c IHM.cpp

Monnayeur.o : IHM.h enum.h Monnayeur.h Monnayeur.cpp
	g++ -c Monnayeur.cpp

Controleur.o : IHM.h enum.h Monnayeur.h Cafe.h Luxe.h Normale.h Controleur.h Controleur.cpp
	g++ -c Controleur.cpp

Distributeur.o : IHM.h enum.h Monnayeur.h Cafe.h Gobelets.h Sucre.h Distributeur.h Distributeur.cpp
	g++ -c Distributeur.cpp


main.o : Distributeur.h main.cpp
	g++ -c main.cpp

uml_distributeur : Cafe.o Gobelets.o IHM.o Monnayeur.o Controleur.o Distributeur.o main.o
	g++ -o uml_distributeur Cafe.o Gobelets.o IHM.o Monnayeur.o Controleur.o Distributeur.o main.o

