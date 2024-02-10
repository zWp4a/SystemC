#ifndef LISTA_H
#define LISTA_H

// Estructuras de Datos y Algoritmos
// lista.h
// Modulo de definicion de una lista simple.

#include "archivo.h"

typedef struct nodo_lista * listaA;

listaA crear();
// Crea la lista doblemente encadenada vacia.

listaA cons(listaA l, Archivo n);
// Inserta n al inicio de l.

listaA snoc(listaA l, Archivo n);
// Inserta n al final de l.

listaA insOrd(listaA l, Archivo n);
// Inserta ordenadamente en l.
// Pre: l ordenada.

Archivo first(listaA l);
// Retorna el primer elemento de la lista.
// Pre: l no vacia.

Archivo last(listaA l);
// Retorna el ultimo elemento de la lista.
// Pre: l no vacia.

Archivo actual(listaA l);
// Retorna el elemento "actual" de la lista.
// Pre: l no vacia.

listaA ant(listaA l);
// Retorna los "anteriores" al nodo actual de la lista.
// Pre: l no vacia.

listaA sig(listaA l);
// Retorna los "siguientes" al nodo actual de la lista.
// Pre: l no vacia.

bool isEmpty(listaA l);
// Retorna true si l es vacia, false en caso contrario.

int cant(listaA l);
// Retorna la cantidad de elementos de l.

bool pertenece(listaA l, Archivo n);
// Retorna true si n pertenece a l, false en caso contrario.

listaA elim(listaA l, Archivo elem);
// En caso de que elem pertenezca a l, retorna l sin ese elemento.

listaA destruir(listaA l);
// Destruye l y libera la memoria asociada.

bool PERTENECE_LISTA(listaA lista, Cadena nombre);
//Funcion que retorna TRUE si el archivo con ese nombre pertenece a la lista

void Insertar(listaA l, Archivo n);
//Funcion que inserta el archivo al comienzo de la lista

listaA InsertarOrdenado(listaA l, Archivo arch);
//Funcion que inserta ordenado y devuelte el primer elemento.

void ImprimirNombres(listaA lista);
//Funcion que imprime el nombre del archivo y el imprime el atributo de los archivos

Archivo DEVOLVER_ARCHIVO (listaA lista, Cadena nombre);
//Funcion que devuelve el archivo con ese nombre.

void BorrarLista(listaA l);
//Funcion que libera la memoria del nodo y los archivos dentro.

int cant_sig(listaA l);
//Funcion que devuelve la cantidad de elementos en l.

Archivo Devolver_Solo_Archivo(listaA lista);
//Funcion que devuelve solo el archivo de una lista.

listaA tail(listaA l);
//Funcion que devuelve una lista sin su primer elemento.

Archivo head(listaA l);
//Funcion que devuelve el primer elemento de una lista.

Archivo ConseguirArchivoPorNombre(listaA l, Cadena Nombre);
//Funcion que devuelve un archivo por su nombre.

#endif
