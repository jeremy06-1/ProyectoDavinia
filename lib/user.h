/*	Proyecto Davinia | user.h
	En este fichero se comprueba la existencia del ususario, si no existe,
entonces lo crea
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TECLA_ENTER 13
#define TECLA_BACKSPACE 8
#define LONGITUD 10

#if defined(_WIN32) || defined(_WIN64)
#include <conio.h>
// Código especial para Linux
#elif defined(__linux__)
void requestAndHidePasswdLnxFunc(void) {
	
}
#endif

// Declaración de los prototipos de las funciones
void	chekUserExistenceFunc(void),	
		createUserFunc(void),
		requestAndHidePasswdWinFunc(void),
		checkPasswdWinFunc(void),
		printInFileFunc(void);		

// Variables globales
char usuario[LONGITUD + 1];
char clave[LONGITUD + 1];
char clave2[LONGITUD + 1];
char caracter;
int i=0, registrado = 0;
FILE *username, *passwd;

// Comprueba que el usuario no exista para continuar
void chekUserExistenceFunc(void) {
	char _char[2];
	// Abre los ficheros correspondientes
	username = fopen("./ficheros/username.txt", "r");
	passwd = fopen("./ficheros/passwd.txt", "r");
	// Por defecto los ficheros almacenan un cero lo cual significa que no existen usuario aún
	_char[0] = fgetc(username);
	_char[1] = fgetc(passwd);
	
	if (_char[0] == '0' || _char[1] == '0')	createUserFunc(); // Crea el usuario
	
	fclose(username);
	fclose(passwd);
	return;
}
// Crea el usuario
void createUserFunc() {
	/* Pedro Alfonso*/
	printf("Bienvenido\nIngrese el nombre el nuevo usuario\n\n\tNOMBRE: ");
	fflush(stdin);
	gets(usuario);

	printf("\tCLAVE: ");
	// Detectar OS soportado (Windows y Linux)
	if (strcmp(OS, "Windows") == 0) {
		// Pedir clave y ocultarla (Windows)
		requestAndHidePasswdWinFunc();
	} else if (strcmp(OS, "Linux") == 0) {
		// Pedir clave y ocultarla (Linux)
		//requestAndHidePasswdLnxFunc();
	} else {
		printf("Error: Sistema operativo no soportado.");
		exit(EXIT_FAILURE);
	}
	
	checkPasswdWinFunc(); // Comprobar clave ingresada
	printInFileFunc();	// Guardar usuario en un fiechero
	return;
}
// Pide la clave para el usuario
void requestAndHidePasswdWinFunc(void) {
	while ((caracter = getch())) {
		if (caracter == TECLA_ENTER) {
			for (i=i; i < LONGITUD; i++) {
				clave[i] = '\0';
			}
			break;
		} else if (caracter == TECLA_BACKSPACE) {
			if (i > 0) {
				i--;
				printf("\b \b");
			}
		} else {
			if (i < LONGITUD) {
				printf("*");
				clave[i] = caracter;
				i++;
			}
		}
	}
	return;
}
// Comprueba que la clave ingresada anteriormente sea correcta
void checkPasswdWinFunc(void) {
	printf ("\n\nFavor vuelva a ingresar la clave\n\n\tCLAVE: ");
	i = 0;
	int comprobante = 1;
	
	do {
		while ((caracter = getch())) {
			if (caracter == TECLA_ENTER) {
				for (i=i; i < LONGITUD; i++) {
					clave2[i] = '\0';
				}
				break;
			} else if (caracter == TECLA_BACKSPACE) {
				if (i > 0) {
					i--;
					printf("\b \b");
				}
			} else {
				if (i < LONGITUD) {
					printf("*");
					clave2[i] = caracter;
					i++;
				}
			}
		}
		for (i = 0; i < LONGITUD; i++) {
			if (clave[i] != clave2[i]) {
				comprobante = 0;
			}
		}
		if ( comprobante == 0) {
			printf("\n\nLas claves no coinciden, favor volver a ingresarla clave\n\n\tCLAVE: ");
			registrado = 0;
			i=0;
			comprobante = 1;
		} else {
			printf("\n\nUsuario registrado correctamente\n\n");
			system("sleep 1.5");
			clearScreen();
			registrado = 1;
		}
	} while(registrado == 0);
	return;
}
// Guarda los datos en los ficheros
void printInFileFunc(void) {
	fflush(stdin);
	username = fopen("./ficheros/username.txt", "w");
	passwd = fopen("./ficheros/passwd.txt", "w");
	
	i = 0;
	// Almacena el nombre de usuario en un fichero
	while (usuario[i] != '\0') {
		fputc(usuario[i], username);
		++i;
	}
	// Lo mismo pero con la clave
	i = 0;
	while (clave[i] != '\0') {
		fputc(clave[i], passwd);
		++i;
	}
	
	fclose(username);
	fclose(passwd);
	return;
}
