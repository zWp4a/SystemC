#ifndef ARCHIVO_H
#define ARCHIVO_H

// Estructuras de Datos y Algoritmos - Curso 2023
// Tecnologo en Informatica FIng - DGETP - UTEC
//
// Trabajo Obligatorio
// archivo.h
// Modulo de Definición de los Archivos.

#include "definiciones.h"

typedef struct archivo * Archivo;

Archivo CREAR_ARCHIVO(Cadena nombreArchivo);
//Funcion CREAR_ARCHIVO la cual crea un archivo
//Nota: se crea con el permiso de escritura/lectura por default

Archivo CAMBIAR_NOMBRE(Archivo arch, Cadena nombrea);
//Funcion CAMBIAR_NOMBRE la cual cambia el nombre del archivo
//Pre: El nombre no puede ser vacio.

Archivo CAMBIAR_PERMISO(Archivo arch, bool esEscritura);
//Funcion CAMBIAR_PERMISO la cual cambia los permisos del archivo seleccionado

void ELIMINAR_ARCHIVO(Archivo arch);
//Funcion ELIMINAR_ARCHIVO la cual elimina del sistema el archivo seleccionado

void INSERTAR_COMIENZO(Archivo arch, Cadena contenido);
//Funcion INSERTAR_COMIENZO la cual ingresa contenido al comienzo del archivo

void INSERTAR_ALFINAL(Archivo arch, Cadena contenido);
//Funcion INSERTAR_ALFINAL la cual ingresa contenido al final del archivo

Archivo ELIMINAR_COMIENZO(Archivo arch, int caracteres);
//Funcion ELIMINAR_COMIENZO la cual elimina el contenido al comienzo del archivo

Archivo ELIMINAR_ALFINAL(Archivo arch, int caracteres);
//Funcion ELIMINAR_ALFINAL la cual elimina el contenido al final del archivo

Cadena DEVOLVER_NOMBRE (Archivo arch);
//Funcion DEVUELVE el nombre del archivo

void IMPRIMIR_ATRIBUTO(Archivo arch);
//Funcion que imprime el atributo del archivo

bool ES_SOLO_LECTURA(Archivo arch);
//Funcion que devuelte true si el archivo es solo lectura, false en si es lectura y escritura

Cadena DEVOLVER_CONTENIDO(Archivo arch);
//Funcion que devuelve el contenido de un archivo.

bool Contiene(Archivo arch, Cadena texto);
//Funcion que devuelve true si la cadena de texto esta contenida en el archivo

void REEMPLAZAR_CONTENIDO(Archivo arch, Cadena texto1, Cadena texto2);
//Funcion que replaza el texto1 por el texto2 en el texto.
//PRE: el "texto1" tiene que existir en el archivo y no puede superar los 22 caracteres.

#endif
