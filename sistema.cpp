// Estructuras de Datos y Algoritmos - Curso 2023
// Tecnologo en Informatica FIng - DGETP - UTEC
//
// Trabajo Obligatorio
// sistema.c
// Modulo de Implementacion del File System.

#include "sistema.h"
#include "directorio.h"
#include <string.h>
#include "lista.h"
#include <iostream>

using namespace std;

struct _sistema
{
	directorio raiz;
	directorio actual;

	// aquí deben figurar los campos que usted considere necesarios para manipular el sistema de directorios
	// Se deberan crear nuevos modulos
};

TipoRet CREARSISTEMA(Sistema &s)
{
	// Inicializa el sistema para que contenga únicamente al directorio RAIZ, sin subdirectorios ni archivos.
	// Para mas detalles ver letra.

	s = new (_sistema);
	Cadena nombre = new char[MAX_NOMBRE];

	strcpy(nombre, "RAIZ");

	s->raiz = Crear_Directorio(nombre);
	s->actual = s->raiz;

	return OK;
}

TipoRet DESTRUIRSISTEMA(Sistema &s)
{
	// Destruye el sistema, liberando la memoria asignada a las estructuras que datos que constituyen el file system.
	// Para mas detalles ver letra.
	BorrarTodosLosArchivos(s->actual);
	delete (s->actual);
	delete (s);
	return OK;
}

TipoRet CD(Sistema &s, Cadena nombreDirectorio)
{
	char nombreDir[MAX_TEXTO] = "";
	Devolver_NombreDir(s->actual, nombreDir);

	if (strcasecmp(nombreDirectorio, "RAIZ") == 0)
	{
		if (s->actual == s->raiz)
		{
			std::cout << "Yo nos encontramos en la raiz del sistema";
			return ERROR;
		}
		else
		{
			s->actual = s->raiz;
			return OK;
		}
	}
	else if (strcasecmp(nombreDirectorio, "..") == 0)
	{
		if (strcasecmp(nombreDir, "RAIZ") == 0)
		{
			std::cout << "Yo nos encontramos en la raiz del sistema";
			return ERROR;
		}
		else
		{
			s->actual = GetPadre(s->actual);
			return OK;
		}
	}
	else if (ExisteDirectorio(s->actual, nombreDirectorio))
	{
		s->actual = ConseguirDirectorio(s->actual, nombreDirectorio);
		return OK;
	}
	else
	{
		std::cout << "No existe un directorio con ese nombre";
		return ERROR;
	}
}

TipoRet MKDIR(Sistema &s, Cadena nombreDirectorio)
{
	// Crea un nuevo directorio.
	// Para mas detalles ver letra.
	char nombreDir[MAX_TEXTO] = "";
	Devolver_NombreDir(s->actual, nombreDir);
	if (strcasecmp(nombreDirectorio, "RAIZ") == 0)
	{
		std::cout << "El directorio no puede tener el nombre RAIZ";
		return ERROR;
	}
	else if (ExisteDirectorio(s->actual, nombreDirectorio))
	{
		std::cout << "Ya existe un directorio con ese nombre";
		return ERROR;
	}
	else
	{
		directorio dir = Crear_Directorio(nombreDirectorio);
		Agregarhijo(s->actual, dir);
		return OK;
	}
}

TipoRet RMDIR(Sistema &s, Cadena nombreDirectorio)
{
	// Elimina un directorio.
	// Para mas detalles ver letra.
	if (strcasecmp(nombreDirectorio, "RAIZ") == 0)
	{
		std::cout << "El directorio RAIZ no puede ser eliminado.";
		return ERROR;
	}
	else if (ExisteDirectorio(s->actual, nombreDirectorio))
	{
		ELIMINAR_DIRECTORIO(s->actual, nombreDirectorio);
		return OK;
	}
	else
	{
		std::cout << "No se encontro carpeta para borrar" << '\n';
		return ERROR;
	}
	return OK;
}

TipoRet MOVE(Sistema &s, Cadena nombre, Cadena directorioDestino)
{
	// mueve un directorio o archivo desde su directorio origen hacia un nuevo directorio destino.
	// Para mas detalles ver letra.

	char nombreDestino[MAX_COMANDO] = "";
	strcpy(nombreDestino, directorioDestino);

	directorio dirDestino = ENCONTRAR_DESTINO(s->raiz, nombreDestino);
	strcpy(nombreDestino, directorioDestino);
	if (PERTENECE_ARCHIVO(s->actual, nombre))
	{
		if (dirDestino != NULL)
		{
			std::cout << "Existe destino" << '\n';
			MoverArchivo(s->actual, nombre, dirDestino);
			return OK;
		}
		else
		{
			std::cout << "No se encontro el destino" << '\n';
			return ERROR;
		}
	}
	else if (ExisteDirectorio(s->actual, nombre))
	{
		if (dirDestino != NULL)
		{
			std::cout << "Existe destino" << '\n';
			directorio dirMover = ConseguirDirectorio(s->actual, nombre);
			char nombreActual[MAX_NOMBRE] = "";
			Devolver_NombreDir(s->actual, nombreActual);
			if (dirDestino == GetPadre(s->actual) && (strcasecmp(nombreActual, nombre) == 0))
			{
				std::cout << "No se puede reemplazar la carpeta actual" << '\n';
				return ERROR;
			}
			else
			{
				if (!EsSubDirectorio(dirMover, dirDestino))
				{
					Moverdirectorio(s->actual,dirMover,dirDestino);
					return OK;
				}
				else
				{
					std::cout << "No se puede mover a una subcarpeta" << '\n';
					return ERROR;
				}
			}
		}
		else
		{
			std::cout << "No se encontro el destino" << '\n';
			return ERROR;
		}
		return NO_IMPLEMENTADA;
	}
	else
	{
		std::cout << "No se encontro el elemento a mover. " << '\n';
		return ERROR;
	}
}

TipoRet DIR(Sistema &s, Cadena parametro)
{
	// Muestra el contenido del directorio actual.
	// Para mas detalles ver letra.

	if (parametro != NULL && strcasecmp(parametro, "/s") == 0)
	{

		Imprimir_Todo(s->actual);
	}
	else
	{
		char nombre[MAX_NOMBRE] = "";
		Devolver_NombreDir(s->raiz, nombre);
		ImprimirRaizDir(s->actual, nombre);
		std::cout << '\n';

		ImprimirArchivos(s->actual);
		Imprimir_Todos_Directorios(GetHijo(s->actual));
	}

	return OK;
}

TipoRet CREATEFILE(Sistema &s, Cadena nombreArchivo)
{
	// Crea un nuevo archivo en el directorio actual.
	// Para mas detalles ver letra.
	// verificar si existe archivo con mismo nombre
	if (PERTENECE_ARCHIVO(s->actual, nombreArchivo))
	{
		cout << "Este archivo ya existe \n";
		return ERROR;
	}
	else
	{
		cout << "El archivo no existe \n";
		AgregarArchivo(s->actual, nombreArchivo);
		return OK;
	}
}
TipoRet DELETE(Sistema &s, Cadena nombreArchivo)
{
	// Elimina un archivo del directorio actual, siempre y cuando no sea de sólo lectura.
	// Para mas detalles ver letra.}
	if (PERTENECE_ARCHIVO(s->actual, nombreArchivo))
	{
		if (SOLO_LECTURA(s->actual, nombreArchivo))
		{
			std::cout << "El archivo " << nombreArchivo << " es solo lectura, no se puede eliminar." << '\n';
			return ERROR;
		}
		else
		{
			ELIMINAR_ARCHIVO(s->actual, nombreArchivo);
			std::cout << "Se elimino:" << nombreArchivo << '\n';
			return OK;
		}
	}
	else
	{
		std::cout << "EL ARCHIVO NO EXISTE" << '\n';
		return ERROR;
	}
}

TipoRet ATTRIB(Sistema &s, Cadena nombreArchivo, Cadena parametro)
{
	// Agrega un texto al comienzo del archivo NombreArchivo.
	// Para mas detalles ver letra.
	if (PERTENECE_ARCHIVO(s->actual, nombreArchivo))
	{
		if (strcasecmp(parametro, "-W") == 0)
		{
			std::cout << "SE LE SACO ESCRITURA" << '\n';
			ACTUALIZAR_PERMISOS(s->actual, nombreArchivo, false);
		}
		else
		{
			std::cout << "SE AGREGO ESCRITURA" << '\n';
			ACTUALIZAR_PERMISOS(s->actual, nombreArchivo, true);
		}
		return OK;
	}
	else
	{
		std::cout << "NO SE ENCONTRO EL ARCHIVO" << '\n';
		return ERROR;
	}
}

TipoRet IC(Sistema &s, Cadena nombreArchivo, Cadena texto)
{
	if (PERTENECE_ARCHIVO(s->actual, nombreArchivo))
	{
		if (SOLO_LECTURA(s->actual, nombreArchivo))
		{
			std::cout << "El archivo " << nombreArchivo << " es solo lectura, no se puede modificar." << '\n';
			return ERROR;
		}
		else
		{
			InsertarContenido(s->actual, nombreArchivo, texto);
			std::cout << "Se modifico:" << nombreArchivo << '\n';
			return OK;
		}
	}
	else
	{
		std::cout << "NO SE ENCONTRO EL ARCHIVO" << '\n';
		return ERROR;
	}
}

TipoRet IF(Sistema &s, Cadena nombreArchivo, Cadena texto)
{
	// Agrega un texto al final del archivo NombreArchivo.
	// Para mas detalles ver letra.
	if (PERTENECE_ARCHIVO(s->actual, nombreArchivo))
	{
		if (SOLO_LECTURA(s->actual, nombreArchivo))
		{
			std::cout << "El archivo " << nombreArchivo << " es solo lectura, no se puede modificar." << '\n';
			return ERROR;
		}
		else
		{
			InsertarContenidoFinal(s->actual, nombreArchivo, texto);
			std::cout << "Se modifico:" << nombreArchivo << '\n';
			return OK;
		}
	}
	else
	{
		std::cout << "NO SE ENCONTRO EL ARCHIVO" << '\n';
		return ERROR;
	}
}

TipoRet DC(Sistema &s, Cadena nombreArchivo, int k)
{
	// Elimina los a lo sumo K primeros caracteres del archivo parámetro.
	// Para mas detalles ver letra.

	if (PERTENECE_ARCHIVO(s->actual, nombreArchivo))
	{
		if (SOLO_LECTURA(s->actual, nombreArchivo))
		{
			std::cout << "El archivo " << nombreArchivo << " es solo lectura, no se puede modificar." << '\n';
			return ERROR;
		}
		else
		{
			EliminarComienzo(s->actual, nombreArchivo, k);
			std::cout << "Se modifico:" << nombreArchivo << '\n';
			return OK;
		}
	}
	else
	{
		std::cout << "NO SE ENCONTRO EL ARCHIVO" << '\n';
		return ERROR;
	}
	return NO_IMPLEMENTADA;
}

TipoRet DF(Sistema &s, Cadena nombreArchivo, int k)
{
	// Elimina los a lo sumo K últimos caracteres del archivo parámetro.
	// Para mas detalles ver letra.
	if (PERTENECE_ARCHIVO(s->actual, nombreArchivo))
	{
		if (SOLO_LECTURA(s->actual, nombreArchivo))
		{
			std::cout << "El archivo " << nombreArchivo << " es solo lectura, no se puede modificar." << '\n';
			return ERROR;
		}
		else
		{
			EliminarFinal(s->actual, nombreArchivo, k);
			std::cout << "Se modifico:" << nombreArchivo << '\n';
			return OK;
		}
	}
	else
	{
		std::cout << "NO SE ENCONTRO EL ARCHIVO" << '\n';
		return ERROR;
	}
	return NO_IMPLEMENTADA;
}

TipoRet TYPE(Sistema &s, Cadena nombreArchivo)
{
	if (PERTENECE_ARCHIVO(s->actual, nombreArchivo))
	{
		Cadena contenido = GetContenido(s->actual, nombreArchivo);

		if (strlen(contenido) == 0)
		{
			std::cout << "El archivo no tiene contenido." << '\n';
			return ERROR;
		}
		else
		{
			std::cout << "Contenido: " << contenido << '\n';
			return OK;
		}
	}
	else
	{
		std::cout << "NO SE ENCONTRO EL ARCHIVO" << '\n';
		return ERROR;
	}
}

TipoRet SEARCH(Sistema &s, Cadena nombreArchivo, Cadena texto)
{
	// Busca dentro del archivo la existencia del texto.
	// Para mas detalles ver letra.
	if (PERTENECE_ARCHIVO(s->actual, nombreArchivo))
	{
		if (ExisteContenido(s->actual, nombreArchivo, texto))
		{
			std::cout << "El archivo contiene la busqueda." << '\n';
			return OK;
		}
		else
		{
			std::cout << "No se encontro " << texto << " en " << nombreArchivo << "." << '\n';
			return ERROR;
		}
	}
	else
	{
		std::cout << "NO SE ENCONTRO EL ARCHIVO" << '\n';
		return ERROR;
	}
}

TipoRet REPLACE(Sistema &s, Cadena nombreArchivo, Cadena texto1, Cadena texto2)
{
	// Busca y reemplaza dentro del archivo la existencia del texto1 por el texto2.
	// Para mas detalles ver letra.
	if (PERTENECE_ARCHIVO(s->actual, nombreArchivo))
	{
		if (ExisteContenido(s->actual, nombreArchivo, texto1))
		{
			ReemplazarContenido(s->actual, nombreArchivo, texto1, texto2);
			std::cout << "El archivo fue modificado." << '\n';
			return OK;
		}
		else
		{
			std::cout << "No se encontro " << texto1 << " en " << nombreArchivo << "." << '\n';
			return ERROR;
		}
	}
	else
	{
		std::cout << "NO SE ENCONTRO EL ARCHIVO" << '\n';
		return ERROR;
	}
}
