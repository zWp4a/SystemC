// Estructuras de Datos y Algoritmos - Curso 2023
// Tecnologo en Informatica FIng - DGETP - UTEC
//
// Trabajo Obligatorio
// sistema.c
// Modulo de Implementacion de los archivos.

#include "archivo.h"
#include "definiciones.h"
#include <string.h>
#include <iostream>

using namespace std;

struct archivo
{
  char nombrea[MAX_NOMBRE];
  char extenciona[MAX_EXTENCION];
  char nombreCompleto[MAX_NOMBRE + MAX_EXTENCION];
  char contenidoa[MAX_TEXTO];
  bool esEscritura;
  // Si esEscritura es false, tiene permiso solo de lectura, si es true, tiene permiso de ambos
};

Archivo CREAR_ARCHIVO(Cadena nombrea)
{
  // Funcion CAMBIAR_NOMBRE la cual cambia el nombre del archivo.
  // Pre: El nombre no puede ser vacio.
  // Nota: Se crea con el permiso de solo Lectura por default.

  Archivo nuevoa = new (archivo);
  nuevoa->esEscritura = true;
  int index = 0;

  while (nombrea[index] != '.' && nombrea[index] != '\0')
  {
    nuevoa->nombrea[index] = nombrea[index];
    index++;
  }
  while (nombrea[index] != '\0')
  {
    nuevoa->extenciona[index] = nombrea[index];
    index++;
  }
  strcpy(nuevoa->nombreCompleto, nombrea);

  strcpy(nuevoa->contenidoa, "");
  // nuevoa->contenidoa[0] = '\0';
  return nuevoa;
}

void ELIMINAR_ARCHIVO(Archivo arch)
{
  // Funcion ELIMINAR_ARCHIVO la cual elimina del sistema el archivo seleccionado

  delete arch;
}

void INSERTAR_COMIENZO(Archivo arch, Cadena contenidoa)
{
  // Funcion INSERTAR_COMIENZO la cual ingresa contenido al comienzo del archivo
  // Pre: el contenido a ingresar no puede ser vacio
  // archivo x void
  char resultado[MAX_TEXTO] = {"\0"};
  strcat(resultado, contenidoa);
  strcat(resultado, arch->contenidoa);
  strcpy(arch->contenidoa, resultado);
  std::cout << resultado << '\n';
}

void INSERTAR_ALFINAL(Archivo arch, Cadena contenido)
{
  // Funcion INSERTAR_ALFINAL la cual ingresa contenido al final del archivo
  // Pre: el contenido a ingresar no puede ser vacio
  // archivo x void

  strcat(arch->contenidoa, contenido);
  std::cout << arch->contenidoa << '\n';
}

Archivo ELIMINAR_COMIENZO(Archivo arch, int caracteres)
{
  // Funcion ELIMINAR_COMIENZO la cual elimina el contenido al comienzo del archivo
  char aux[MAX_TEXTO];
  int contador = 0;

  if (strlen(arch->contenidoa) <= caracteres)
  {
    strcpy(arch->contenidoa, "");
  }
  else
  {
    while (arch->contenidoa[caracteres + contador] != '\0')
    {
      aux[contador] = arch->contenidoa[caracteres + contador];
      contador++;
    }
    aux[contador] = '\0';
    strcpy(arch->contenidoa, aux);
  }

  std::cout << "Contenido del archivo quedo: " << arch->contenidoa << '\n';
}

Archivo ELIMINAR_ALFINAL(Archivo arch, int caracteres)
{
  // Funcion ELIMINAR_ALFINAL la cual elimina el contenido al final del archivo
  char aux[MAX_TEXTO];
  int cantidadCar = strlen(arch->contenidoa) - caracteres;
  if (cantidadCar <= 0)
  {
    strcpy(arch->contenidoa, "");
  }
  else
  {
    for (int i = 0; i < cantidadCar; i++)
    {
      aux[i] = arch->contenidoa[i];
    }
    aux[cantidadCar] = '\0';
    strcpy(arch->contenidoa,aux);
  }
    std::cout << "Contenido del archivo quedo: " << arch->contenidoa << '\n';
}
Archivo CAMBIAR_PERMISO(Archivo arch, bool esEscritura)
{
  // Funcion CAMBIAR_PERMISO la cual cambia los permisos del archivo seleccionado
  arch->esEscritura = esEscritura;
  return arch;
}

Cadena DEVOLVER_CONTENIDO(Archivo arch)
{
  // Funcion DEVOLVER_CONTENIDO la cual retorna el contenido dentro de un archivo

  return arch->contenidoa;
}

Cadena DEVOLVER_NOMBRE(Archivo arch)
{
  // Funcion DEVOLVER_NOMBRE la cual retorna el nombre del archivo seleccionado
  return arch->nombreCompleto;
}

void IMPRIMIR_ATRIBUTO(Archivo arch)
{
  if (arch->esEscritura == true)
  {
    std::cout << "Lectura/Escritura";
  }
  else
  {
    std::cout << "Lectura";
  }
}

bool ES_SOLO_LECTURA(Archivo arch)
{
  return !arch->esEscritura;
}
// pepon pepone

bool Contiene(Archivo arch, Cadena texto){

  int letraABuscar = 0;
  int indice =0;
  while (arch->contenidoa[indice] !='\0')
  {
    while (arch->contenidoa[indice + letraABuscar] == texto[letraABuscar])
    {
      letraABuscar ++;
      if(texto[letraABuscar] == '\0')
        return true;
    }
    letraABuscar=0;
    indice++;
  }
  return false;
}

void REEMPLAZAR_CONTENIDO(Archivo arch, Cadena texto1, Cadena texto2)
{
  int letraABuscar = 0;
  int indice =0;
  while (arch->contenidoa[indice] !='\0')
  {
    while (arch->contenidoa[indice + letraABuscar] == texto1[letraABuscar])
    {
      letraABuscar ++;
      if(texto1[letraABuscar] == '\0')
      {
        char aux[MAX_TEXTO];
        for (int i = 0; i < indice; i++)
        {
          aux[i] = arch->contenidoa[i];
        }

        int indiceAux = indice;

        for (int i = 0; i < strlen(texto2); i++)
        {
          aux[indiceAux] = texto2[i];
          indiceAux++;
        }
        indice += strlen(texto1);
        while (arch->contenidoa[indice] != '\0')
        {
          aux[indiceAux] = arch->contenidoa[indice];
          indiceAux ++;
          indice ++;
        }
        aux[indiceAux] = arch->contenidoa[indice];
        strcpy(arch->contenidoa, aux);
      }

    }
    letraABuscar=0;
    indice++;
  }
}
