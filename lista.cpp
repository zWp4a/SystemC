// Estructuras de Datos y Algoritmos
// lista.c
// Modulo de implementacion de una lista simple.

#include <stdio.h>
#include "lista.h"
#include "archivo.h"
#include <iostream>
#include <string.h>

struct nodo_lista
{
    Archivo dato;
    listaA sig;
    listaA ant;
};

listaA crear()
{
    // Crea la lista doblemente encadenada vacia.
    return NULL;
}

listaA cons(listaA l, Archivo n)
{
    // Inserta n al inicio de l.
    listaA aux = new (nodo_lista);
    aux->dato = n;
    aux->ant = NULL;
    if (l == NULL)
    {
        aux->sig = NULL;
        return aux;
    }
    else
    {
        listaA iter = l;
        while (iter->ant != NULL)
            iter = iter->ant;
        iter->ant = aux;
        aux->sig = iter;
        return l;
    }
}

void Insertar(listaA l, Archivo n)
{
    listaA aux = new (nodo_lista);
    aux->dato = n;
    aux->sig = l;
    aux->ant = l->ant;

    l->ant = aux;
    if (aux->ant != NULL)
    {
        aux->ant->sig = aux;
    }
}

void InsertarFinal(listaA l, Archivo n)
{
    listaA aux = new (nodo_lista);
    aux->dato = n;
    l->sig = aux;
    aux->ant = l;
    aux->sig = NULL;
}

listaA snoc(listaA l, Archivo n)
{
    // Inserta n al final de l.
    listaA aux = new (nodo_lista);
    aux->dato = n;
    aux->sig = NULL;
    if (l == NULL)
    {
        aux->ant = NULL;
        return aux;
    }
    else
    {
        listaA iter = l;
        while (iter->sig != NULL)
            iter = iter->sig;
        iter->sig = aux;
        aux->ant = iter;
        return l;
    }
}

Archivo first(listaA l)
{
    // Retorna el primer elemento de la lista.
    // Pre: l no vacia.
    while (l->ant != NULL)
        l = l->ant;
    return l->dato;
}

Archivo last(listaA l)
{
    // Retorna el ultimo elemento de la lista.
    // Pre: l no vacia.
    if (l->sig == NULL)
        return l->dato;
    else
        return last(l->sig);
}

Archivo actual(listaA l)
{
    // Retorna el elemento "actual" de la lista.
    // Pre: l no vacia.
    return l->dato;
}

listaA ant(listaA l)
{
    // Retorna los "anteriores" al nodo actual de la lista.
    // Pre: l no vacia.
    return l->ant;
}

listaA sig(listaA l)
{
    // Retorna los "siguientes" al nodo actual de la lista.
    // Pre: l no vacia.
    return l->sig;
}

bool isEmpty(listaA l)
{
    // Retorna true si l es vacia, false en caso contrario.
    return (l == NULL);
}

int cant_ant(listaA l)
{
    // Retorna la cantidad de elementos de l.
    if (l == NULL)
        return 0;
    else
        return 1 + cant_ant(l->ant);
}

int cant_sig(listaA l)
{
    // Retorna la cantidad de elementos de l.
    if (l == NULL)
        return 0;
    else
        return 1 + cant_sig(l->sig);
}

int cant(listaA l)
{
    // Retorna la cantidad de elementos de l.
    if (l == NULL)
        return 0;
    else
        return 1 + cant_ant(l->ant) + cant_sig(l->sig);
}

listaA tail(listaA l){
  if (l->sig !=NULL) {
    return l->sig;
  }else{
    return NULL;
  }
}
Archivo head (listaA l){
  return l->dato;
}

bool pertenece(listaA l, Archivo n)
{
    // Retorna true si n pertenece a l, false en caso contrario.
    if (l == NULL)
        return false;
    else
    {
        while (l->ant != NULL)
            l = l->ant;
        while ((l != NULL) && (l->dato != n))
            l = l->sig;
        if (l == NULL)
            return false;
        else
            return true;
    }
}

listaA elim(listaA l, Archivo elem)
{
    // En caso de que elem pertenezca a l, retorna l sin ese elemento.
    if (l == NULL)
    {
        return l;
    }
    else
    {
        listaA iter = l;
        while (iter->ant != NULL)
            iter = iter->ant;
        while (iter != NULL)
        {
            char nomb[MAX_NOMBRE + MAX_EXTENCION];
            strcpy(nomb, DEVOLVER_NOMBRE(iter->dato));
            char nombreComparar[MAX_NOMBRE + MAX_EXTENCION];
            strcpy(nombreComparar, DEVOLVER_NOMBRE(elem));
            if (strcasecmp(nomb, nombreComparar) == 0)
            {
                listaA ant = iter->ant;
                listaA sig = iter->sig;
                if (l == iter)
                {
                    if (ant != NULL)
                        l = ant;
                    else
                        l = sig;
                }
                delete iter;

                iter = sig;
                if (ant != NULL)
                    ant->sig = sig;
                if (sig != NULL)
                    sig->ant = ant;
            }
            else
            {
                iter = iter->sig;
            }
        }
        return l;
    }
}

listaA destruir(listaA l)
{
    // Destruye l y libera la memoria asociada.
    if (l != NULL)
    {
        while (l->ant != NULL)
            l = l->ant;
        while (l != NULL)
        {
            listaA aux = l;
            l = l->sig;
            delete aux;
        }
    }
    return l;
}

bool PERTENECE_LISTA(listaA l, Cadena Nombre)
{

    if (l == NULL)
        return false;
    else
    {
        if (strcasecmp(Nombre, DEVOLVER_NOMBRE(l->dato)) == 0)
            return true;
        else
            return PERTENECE_LISTA(l->sig, Nombre);
    }
}

Archivo ConseguirArchivoPorNombre(listaA l, Cadena Nombre)
{
    if (l == NULL)
        return NULL;
    else
    {
        if (strcasecmp(Nombre, DEVOLVER_NOMBRE(l->dato)) == 0)
            return l->dato;
        else
            return ConseguirArchivoPorNombre(l->sig, Nombre);
    }
}

listaA InsertarOrdenado(listaA l, Archivo arch)
{
    char nombreInsertar[MAX_NOMBRE + MAX_EXTENCION];
    strcpy(nombreInsertar, DEVOLVER_NOMBRE(arch));
    if (l == NULL)
    {
        return cons(l, arch);
    }
    else
    {
        listaA aux = l;
        bool seInserto = false;
        while (!seInserto)
        {
            int index = 0;
            char nombreComparar[MAX_NOMBRE + MAX_EXTENCION];
            strcpy(nombreComparar, DEVOLVER_NOMBRE(aux->dato));
            std::cout << "Insertar: " << nombreInsertar << ' ';
            std::cout << "Comparado: " << nombreComparar << '\n';
            if (strcasecmp(nombreInsertar, nombreComparar) < 0)
            {
                std::cout << "inserto porque es menor \n"
                          << " cantidad antes:" << cant(l);

                Insertar(aux, arch);
                seInserto = true;
                std::cout << " cantidad despues:" << cant(l);
            }
            else
            {
                if (aux->sig == NULL)
                {
                    std::cout << "inserto al final";
                    InsertarFinal(aux, arch);
                    seInserto = true;
                }
                else
                    aux = aux->sig;
            }
        }
        while (aux->ant != NULL)
        {
            aux = aux->ant;
        }
        return aux;
    }
}

void ImprimirNombres(listaA lista)
{
    if (lista != NULL)
    {

        std::cout << DEVOLVER_NOMBRE(lista->dato) << '\t' << '\t';
        IMPRIMIR_ATRIBUTO(lista->dato);
        std::cout << '\n';
        ImprimirNombres(lista->sig);
    }
}

Archivo Devolver_Solo_Archivo(listaA lista){
  return lista->dato;
}

Archivo DEVOLVER_ARCHIVO(listaA lista, Cadena nombre)
{

    listaA aux = lista;

    if (strcasecmp(DEVOLVER_NOMBRE(aux->dato), nombre) == 0)
    {
        return aux->dato;
    }
    else
    {
        aux = aux->sig;
        return DEVOLVER_ARCHIVO(aux, nombre);
    }
}

void BorrarLista(listaA l)
{
    if (l->sig != NULL)
    {
        BorrarLista(l->sig);
    }
    ELIMINAR_ARCHIVO(l->dato);
    delete l;
}
