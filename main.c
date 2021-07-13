/* PROYECTO DAVINIA | II Año de Ingeniería en Sistemas | main.c
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
	FILE *username;
	short opt, rsult;
	char _char;
	// Opciones disponibles
	
	username = fopen("./ficheros/username.txt", "r");

	printf("\tBienvenid@ ");
	// Imprimir el nombre del usuario
	_char = fgetc(username);
	while (_char != EOF) {
		printf("%c", _char);
		_char = fgetc(username);
	}
	fclose(username);
	
	puts("\t\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	puts("\n\t   Inicio\n");
	puts("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("1. Agregar contacto\n");
	printf("2. Ver contactos\n");
	printf("3. Cerrar sesión\n");
	printf("0. Salir\n");
	
	printf("\nElija una opcion: ");
	scanf("%hi", &opt);
	// Continuar si se cumple la condición
	rsult = (opt >= 0 && opt <= 3);
	if (rsult) {
		// Seleccionar las opciones que el usuario quiera.
		switch (opt) {
			case 0: 
				clearScreen();
				printf("¡Tenga un buen día!\n");
				system("sleep 2");
				clearScreen();
				exit(EXIT_SUCCESS);
				break;
			case 1: addContactFunc(); break;
			case 2: listContactsFunc();	break;
			case 3: loginFunc(); break;
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
