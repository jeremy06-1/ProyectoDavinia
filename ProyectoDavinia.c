/* PROYECTO DAVINIA V1 | II Año de Ingeniería en Sistemas
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

int createFiles(void) {
	return mkdir("ficheros");
}

#elif defined(__linux__)
#define OS "Linux"
void clearScreen(void) {
	system("clear");
}

int createFiles(void) {
	system("mkdir ficheros");
	system("touch ficheros/contacts_db.txt");
	system("echo 1 > ficheros/contacts_number.txt");
	return 0;
}
#endif
//#include "./lib/login.h"
#include "./lib/create_files.h"
#include "./lib/agenda_logic.h"

// Funcion de inicio
void startFunc(void) {
	/*Raynner Altamirano | Proyecto Davinia | Julio 07, 2021 | startFunc()*/
	short opt;
	
	// Opciones disponibles
	printf("1. Ver contactos\n");
	printf("2. Agregar contacto\n");
	printf("0. Salir\n");
	
	printf("\nElija una opcion: ");
	scanf("%hi", &opt);
	
	// Seleccionar las opciones que el usuario quiera.
	switch (opt) {
	case 0: exit(EXIT_SUCCESS); break;
	case 1: listContactsFunc();	break;
	case 2: addContactFunc(); break;
	default: printf("Opcion ilegal.\n");
	}
	return;
}

// Funcion principal
int main() {
	short _true = 1;
	
	checkFilesFunc();
	
	// loginFunc();
	
	while (_true) {
		startFunc();
	}
	
	return 0;
}
