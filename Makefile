all: proj3.exe

setColorMenu.o: constants.h colorClass.h setColorMenu.h setColorMenu.cpp
	g++ -std=c++98 -g -Wall -c setColorMenu.cpp -o setColorMenu.o

checkOutOfBoundry.o: constants.h rowColumnClass.h checkOutOfBoundry.h checkOutOfBoundry.cpp
	g++ -std=c++98 -g -Wall -c checkOutOfBoundry.cpp -o checkOutOfBoundry.o

mainMenu.o: constants.h mainMenu.h mainMenu.cpp
	g++ -std=c++98 -g -Wall -c mainMenu.cpp -o mainMenu.o

rowColumnClass.o: constants.h rowColumnClass.h rowColumnClass.cpp
	g++ -std=c++98 -g -Wall -c rowColumnClass.cpp -o rowColumnClass.o

colorClass.o: constants.h colorClass.h colorClass.cpp
	g++ -std=c++98 -g -Wall -c colorClass.cpp -o colorClass.o

colorImageClass.o: checkOutOfBoundry.h constants.h rowColumnClass.h colorClass.h colorImageClass.h colorImageClass.cpp
	g++ -std=c++98 -g -Wall -c colorImageClass.cpp -o colorImageClass.o

proj3.o: proj3.cpp mainMenu.o rowColumnClass.o colorClass.o colorImageClass.o
	g++ -std=c++98 -g -Wall -c proj3.cpp -o proj3.o

proj3.exe: proj3.o mainMenu.o rowColumnClass.o colorClass.o colorImageClass.o checkOutOfBoundry.o setColorMenu.o
	g++ -std=c++98 proj3.o mainMenu.o rowColumnClass.o colorClass.o colorImageClass.o checkOutOfBoundry.o setColorMenu.o -o proj3.exe

clean:
	rm -f *.o *.exe
