/* PROYECTO DAVINIA | II Año de Ingeniería en Sistemas
Programadores: Pedro Alfonso, Kenneth Lola, Katherinne Castro, Raynner Altamirano, Jeremy Fonseca
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>
#if defined(_WIN32) || defined(_WIN64)
#define OS "Windows"
void clearScreen(void) {
	system("cls");
}
#elif defined(__linux__)
#define OS "Linux"
void clearScreen(void) {
	system("clear");
}
#endif
#include "./lib/create_files.h"
#include "./lib/user.h"
#include "./lib/login.h"
#include "./lib/agenda_logic.h"


// Funcion de inicio
void startFunc(void) {
	/*Raynner Altamirano | Proyecto Davinia | Julio 07, 2021 | startFunc()*/
	short opt, rsult;

	// Opciones disponibles
	puts("Inicio");
	puts("~~~~~~");
	printf("1. Agregar contacto\n");
	printf("2. Ver contactos\n");
	printf("0. Salir\n");
	
	printf("\nElija una opcion: ");
	scanf("%hi", &opt);
	
	// Continuar si se cumple la condición
	rsult = (opt >= 0 && opt <= 2);
	if (rsult) {
		// Seleccionar las opciones que el usuario quiera.
		switch (opt) {
			case 0: exit(EXIT_SUCCESS); break;
			case 1: addContactFunc(); break;
			case 2: listContactsFunc();	break;
		}
	} else {
		clearScreen();
		printf("Error: (%i) Carácter u opción ilegal.\n", opt);
		exit(EXIT_SUCCESS);
	}
	return;
}

// Funcion principal
int main() {
	short _true = 1;
	
	checkFilesFunc(); // Comprueba que existan los ficheros para continuar
	chekUserExistenceFunc(); // Comprueba que el usuario no exista para continuar
	loginFunc(); // Inicia sesión con el usuario creado
	
	while (_true) startFunc();
	return 0;
}
