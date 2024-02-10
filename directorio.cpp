// Estructuras de Datos y Algoritmos - Curso 2023
// Tecnologo en Informatica FIng - DGETP - UTEC
//
// Trabajo Obligatorio
// directorio.c
// Modulo de Implementacion de directorio.

#include "directorio.h"
#include "definiciones.h"
#include "lista.h"
#include <iostream>
#include "archivo.h"

#include <string.h>
using namespace std;

struct nodo_directorio
{
	// directorios ver seg entrega
	// archivos archs;
	Cadena nombre;
	listaA lista_archivos;
	directorio padre;
	directorio sig_herm;
	directorio pr_hijo;
};

directorio Crear_Directorio(Cadena nombre)
{
	// Retorna un directorio de nombre "nombre".
	directorio d = new (nodo_directorio);
	d->nombre = new char[MAX_NOMBRE];
	strcpy(d->nombre, nombre);
	d->lista_archivos = crear();
	d->padre = NULL;
	d->sig_herm = NULL;
	d->pr_hijo = NULL;
	return d;
}

listaA GetListaArchivo(directorio directorio)
{
	return directorio->lista_archivos;
}

void SetListaArchivo(directorio directorio, listaA archivo)
{
	directorio->lista_archivos = archivo;
}

bool PERTENECE_ARCHIVO(directorio dir, Cadena nombre)
{
	// devuelve 1 si el ARCHVO pertenece al directorio y 0 en caso contrario.
	return PERTENECE_LISTA(dir->lista_archivos, nombre);
}

void ImprimirArchivos(directorio dir)
{
	ImprimirNombres(dir->lista_archivos);
}

void AgregarArchivo(directorio dir, Cadena nombreArchivo)
{
	SetListaArchivo(dir, InsertarOrdenado(GetListaArchivo(dir), CREAR_ARCHIVO(nombreArchivo)));
	cout << "Cantidad de archivos: " << cant(GetListaArchivo(dir)) << "\n";
}

void ACTUALIZAR_PERMISOS(directorio dir, Cadena nombre, bool esEscritura)
{
	CAMBIAR_PERMISO(DEVOLVER_ARCHIVO(GetListaArchivo(dir), nombre), esEscritura);
}

bool SOLO_LECTURA(directorio dir, Cadena nombre)
{

	return ES_SOLO_LECTURA(DEVOLVER_ARCHIVO(GetListaArchivo(dir), nombre));
}

void ELIMINAR_ARCHIVO(directorio dir, Cadena nombre)
{
	SetListaArchivo(dir, elim(GetListaArchivo(dir), DEVOLVER_ARCHIVO(GetListaArchivo(dir), nombre)));
}

Cadena GetContenido(directorio dir, Cadena nombre)
{

	return DEVOLVER_CONTENIDO(DEVOLVER_ARCHIVO(GetListaArchivo(dir), nombre));
}

void InsertarContenido(directorio dir, Cadena archivo, Cadena texto)
{

	INSERTAR_COMIENZO(DEVOLVER_ARCHIVO(GetListaArchivo(dir), archivo), texto);
}

void InsertarContenidoFinal(directorio dir, Cadena archivo, Cadena texto)
{
	INSERTAR_ALFINAL(DEVOLVER_ARCHIVO(GetListaArchivo(dir), archivo), texto);
}

void EliminarComienzo(directorio dir, Cadena archivo, int cantidad)
{
	ELIMINAR_COMIENZO(DEVOLVER_ARCHIVO(GetListaArchivo(dir), archivo), cantidad);
}

void EliminarFinal(directorio dir, Cadena archivo, int cantidad)
{
	ELIMINAR_ALFINAL(DEVOLVER_ARCHIVO(GetListaArchivo(dir), archivo), cantidad);
}

void BorrarTodosLosArchivos(directorio dir)
{
	BorrarLista(GetListaArchivo(dir));
}

bool ExisteContenido(directorio dir, Cadena archivo, Cadena texto)
{
	return Contiene(DEVOLVER_ARCHIVO(GetListaArchivo(dir), archivo), texto);
}

void ReemplazarContenido(directorio dir, Cadena nombreArchivo, Cadena texto1, Cadena texto2)
{
	REEMPLAZAR_CONTENIDO(DEVOLVER_ARCHIVO(GetListaArchivo(dir), nombreArchivo), texto1, texto2);
}

void Setpadre(directorio actual, directorio padre)
{
	actual->padre = padre;
}

void Agregarhijo(directorio padre, directorio hijo)
{
	hijo->padre = padre;
	if (padre->pr_hijo == NULL)
	{
		padre->pr_hijo = hijo;
	}
	else
	{
		if (strcasecmp(padre->pr_hijo->nombre, hijo->nombre) > 0)
		{
			hijo->sig_herm = padre->pr_hijo;
			padre->pr_hijo = hijo;
		}
		else
		{
			InsertarDirOrdenado(padre->pr_hijo, hijo);
		}
	}
}

void InsertarDirOrdenado(directorio dir, directorio insertar)
{

	if (dir->sig_herm == NULL)
	{
		dir->sig_herm = insertar;
		insertar->padre = dir->padre;
	}
	else if (strcasecmp(dir->sig_herm->nombre, insertar->nombre) > 0)
	{
		std::cout << "Insertando: " << insertar->nombre << " contra: " << dir->sig_herm->nombre;
		directorio aux = dir->sig_herm;
		dir->sig_herm = insertar;
		insertar->sig_herm = aux;
		insertar->padre = dir->padre;
	}
	else
	{
		InsertarDirOrdenado(dir->sig_herm, insertar);
	}
}

void Sethermano(directorio actual, directorio herm)
{
	actual->sig_herm = herm;
}

void Devolver_NombreDir(directorio actual, Cadena nombre)
{
	strcpy(nombre, actual->nombre);
}

void ImprimirRaizDir(directorio actual, Cadena nombre)
{
	if (actual->padre == NULL)
	{
		std::cout << actual->nombre;
	}
	else if (strcasecmp(actual->nombre, nombre) == 0)
	{
		std::cout << actual->nombre;
	}
	else
	{
		ImprimirRaizDir(actual->padre, nombre);
		std::cout << "/" << actual->nombre;
	}
}
void ImprimirDirectorio(directorio actual)
{
}

void Imprimir_Todos_Directorios(directorio actual)
{

	if (actual != NULL)
	{
		std::cout << actual->nombre << '\n';
		Imprimir_Todos_Directorios(actual->sig_herm);
	}
}

void Imprimir_Todo(directorio actual)
{
	directorio auxD = actual->pr_hijo;
	char nombre[MAX_NOMBRE] = "";
	Devolver_NombreDir(actual, nombre);
	ImprimirRaizDir(actual, "RAIZ");
	std::cout << '\n';
	listaA auxA = actual->lista_archivos;

	while (cant_sig(auxA) > 0)
	{
		ImprimirRaizDir(actual, "RAIZ");
		std::cout << "/" << DEVOLVER_NOMBRE(head(auxA)) << '\n';
		auxA = tail(auxA);
	}

	while (auxD != NULL)
	{
		Imprimir_Todo(auxD);
		auxD = auxD->sig_herm;
	}
}

directorio GetHijo(directorio dir)
{
	return dir->pr_hijo;
}

bool ExisteDirectorio(directorio dir, Cadena nombre)
{
	directorio hijo = dir->pr_hijo;
	while (hijo != NULL)
	{
		if (strcasecmp(hijo->nombre, nombre) == 0)
		{
			return true;
		}
		hijo = hijo->sig_herm;
	}
	return false;
}

directorio GetPadre(directorio dir)
{
	return dir->padre;
}

directorio ConseguirDirectorio(directorio dir, Cadena nombre)
{

	if (dir == NULL)
	{
		return NULL;
	}
	else
	{
		directorio hijo = dir->pr_hijo;
		while (hijo != NULL)
		{
			if (strcasecmp(hijo->nombre, nombre) == 0)
			{
				return hijo;
			}
			hijo = hijo->sig_herm;
		}
	}
	return NULL;
}

void ELIMINAR_DIRECTORIO(directorio dir, Cadena nombre)
{

	directorio aux = dir->pr_hijo;
	directorio hijo = dir->pr_hijo;

	if (strcasecmp(hijo->nombre, nombre) == 0)
	{
		dir->pr_hijo = hijo->sig_herm;
		hijo->sig_herm = NULL;
		ELIMINAR_TODO_DIRECTORIO(hijo);
	}
	else
	{
		while (hijo != NULL)
		{
			if (strcasecmp(hijo->sig_herm->nombre, nombre) == 0)
			{
				std::cout << "entro" << '\n';
				aux = hijo->sig_herm;
				hijo->sig_herm = aux->sig_herm;
				aux->sig_herm = NULL;
				ELIMINAR_TODO_DIRECTORIO(aux);
				hijo = NULL;
			}
			else
			{
				hijo = hijo->sig_herm;
			}
		}
	}
}
void ELIMINAR_TODO_DIRECTORIO(directorio dir)
{
	destruir(GetListaArchivo(dir));

	directorio auxherm = dir->sig_herm;

	if (dir->pr_hijo != NULL)
	{
		ELIMINAR_TODO_DIRECTORIO(dir->pr_hijo);
	}
	while (auxherm != NULL)
	{
		directorio auxherm1 = auxherm->sig_herm;

		ELIMINAR_TODO_DIRECTORIO(auxherm);
		auxherm = auxherm1;
	}
	delete dir;
}

directorio ENCONTRAR_DESTINO(directorio raiz, Cadena destino)
{
	Cadena pch = strtok(destino, "/");
	directorio aux = raiz;

	while (aux != NULL)
	{
		if (strcasecmp(pch, aux->nombre) == 0)
		{
			pch = strtok(NULL, "/");
			if (pch == NULL)
			{
				return aux;
			}
			aux = aux->pr_hijo;
		}
		else
		{
			aux = aux->sig_herm;
		}
	}
	return NULL;
}

bool Subdirectorio(directorio dir, directorio comparar)
{
	if (dir == NULL)
		return false;
	if (dir == comparar)
	{
		return true;
	}
	else
	{
		return Subdirectorio(dir->pr_hijo, comparar) || Subdirectorio(dir->sig_herm, comparar);
	}
}
bool EsSubDirectorio(directorio mover, directorio destino)
{
	// en el mover niguno de sus hijos y para abajo no puede tener destino
	directorio aux = mover->pr_hijo;
	if (mover == destino)
		return true;

	return Subdirectorio(aux, destino);
}

void Moverdirectorio(directorio actual, directorio mover, directorio destino)
{
	DesencadenarDirectorio(actual, mover);
	directorio borrar = NULL;
	directorio aux = destino->pr_hijo;
	while (aux != NULL)
	{
		if (strcasecmp(aux->nombre, mover->nombre) == 0)
		{
			std::cout << "Las capeta son iguales, se sobre escribe" << '\n';
			borrar = aux;
			aux = NULL;
		}
		else
		{
			aux = aux->sig_herm;
		}
	}
	if (borrar != NULL)
	{
		ELIMINAR_DIRECTORIO(destino,borrar->nombre);
	}
	Agregarhijo(destino, mover);
}

void MoverArchivo(directorio actual, Cadena mover, directorio destino)
{
	Archivo archivo = DEVOLVER_ARCHIVO(GetListaArchivo(actual), mover);
	SetListaArchivo(actual, elim(GetListaArchivo(actual), archivo));
	Archivo eliminar = ConseguirArchivoPorNombre(GetListaArchivo(destino), mover);
	if (eliminar != NULL)
	{
		SetListaArchivo(destino, elim(GetListaArchivo(destino), eliminar));
		delete eliminar;
	}
	SetListaArchivo(destino, InsertarOrdenado(GetListaArchivo(destino), archivo));
}

void DesencadenarDirectorio(directorio dir, directorio sacar)
{

	if (dir->pr_hijo == sacar)
	{
		dir->pr_hijo = sacar->sig_herm;
	}
	else
	{
		directorio aux = dir->pr_hijo;

		while (aux->sig_herm != sacar)
		{
			aux = aux->sig_herm;
		}
		aux->sig_herm = sacar->sig_herm;
	}
	sacar->sig_herm = NULL;
	sacar->padre = NULL;
}
