todo: main.o sistema.o directorio.o archivo.o lista.o
	g++ -o main main.o sistema.o directorio.o archivo.o lista.o

main.o: main.cpp
	g++ -c main.cpp

sistema.o: sistema.h sistema.cpp
	g++ -c sistema.cpp

directorio.o: directorio.h directorio.cpp
	g++ -c directorio.cpp

archivo.o: archivo.h archivo.cpp
	g++ -c archivo.cpp

lista.o: lista.h lista.cpp
	g++ -c lista.cpp
limpiar:
	rm *.o
	rm main

