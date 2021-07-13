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

// Variables globales
char usuario[LONGITUD + 1];
char clave[LONGITUD + 1];
char clave2[LONGITUD + 1];
char caracter;
int i=0, registrado = 0;
FILE *username, *passwd;

#if defined(_WIN32) || defined(_WIN64)
// Código especial para Windows
#include <conio.h>
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
			registrado = 1;
		}
	} while(registrado == 0);
	return;
}
#elif defined(__linux__)
// Código especial para Linux
#include <termios.h>
#include <unistd.h>
#define ECHOFLAGS (ECHO | ECHOE | ECHOK | ECHONL)
int set_disp_mode(int fd, int option){
	struct termios term;  
	tcgetattr(fd, &term);
	
	if (option) term.c_lflag|=ECHOFLAGS;  
	else term.c_lflag &=~ECHOFLAGS;  
	
	tcsetattr(fd, TCSAFLUSH, &term);  
	return 0;
}
int getpasswd(char* passwd, int size) {
	int c, n = 0;  

	do {
		c = getchar();  
		if (c != '\n' || c != '\r') { 
			passwd[n++] = c;
		}
	} while (c != '\n' && c !='\r' && n < (size - 1));  
	passwd[n] = '\0';  
	return n;
} 
void requestAndHidePasswdLnxFunc(void) {
	getchar();
	set_disp_mode(STDIN_FILENO,0);
	
	getpasswd(clave, sizeof(clave));
	set_disp_mode(STDIN_FILENO,1);  
	return;
}
#endif

// Declaración de los prototipos de las funciones
void	chekUserExistenceFunc(void),	
		createUserFunc(void),
		requestAndHidePasswdWinFunc(void),
		checkPasswdWinFunc(void),
		printInFileFunc(void);		

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
	scanf("%s", usuario);

	printf("\tCLAVE: ");
	// Detectar OS soportado (Windows y Linux)
	if (strcmp(OS, "Windows") == 0) {
		// Pedir clave y ocultarla (Windows)
		requestAndHidePasswdWinFunc();
	} else if (strcmp(OS, "Linux") == 0) {
		// Pedir clave y ocultarla (Linux)
		requestAndHidePasswdLnxFunc();
	} else {
		printf("Error: Sistema operativo no soportado.");
		exit(EXIT_FAILURE);
	}
	printf("\n\nUsuario registrado correctamente\n\n");
	system("sleep 1.5");
	clearScreen();
	fflush(stdin);
	
	if (strcmp(OS, "Windows") == 0) {
		checkPasswdWinFunc(); // Comprobar clave ingresada
	} else if (strcmp(OS, "Linux") == 0) {
		// Pedir clave y ocultarla (Linux)
		//requestAndHidePasswdLnxFunc();
	} else {
		printf("Error: Sistema operativo no soportado.");
		exit(EXIT_FAILURE);
	}
	
	
	
	printInFileFunc();	// Guardar usuario en un fiechero
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
