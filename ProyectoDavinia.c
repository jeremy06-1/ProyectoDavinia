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

/*Declaraciones de las funciones*/
void	checkFilesFunc(void), // Comprueba la existencia de ficheros necesarios
		startFunc(void), // Función de inicio
		addContactFunc(void), // Agregar productos
		loginFunc(void), // En espera...
		listContactsFunc(void); // Visualiza todos los contactos en la DB

// Función principal
int main() {
	checkFilesFunc();
	// loginFunc();
	while (1) startFunc();
	return 0;
}

// Verifica que existan los ficheros necesarios
void checkFilesFunc() {
	/*Jeremy Fonseca | Proyecto Davinia | Julio 09, 2021 | addContactFunc()
	DESCRIPCION DE VARIABLES
	------------------------
	dir		>> Fichero "ficheros"
	ret		>> Almacena el rotorno de "mkdir" para detectar errores.
	*/	
	FILE *contactDBFile, *contactsNumberFile;
	DIR *dir;
	int ret, opt;
	
	ret = 0;
	dir = opendir("ficheros");

	// Comprobar la existencia de "ficheros"
	if (dir) {
		closedir(dir);
	} else if (ENOENT == errno) { // Los ficheros no existen
		// Pedir consentimiento al usuario para crear archivos
		do {
			clearScreen();
			printf("\nEn el directorio actual se crearán\n\n");
			puts("./fichero/...");
			puts("./fichero/contacts_db.txt");
			puts("./fichero/contacts_number.txt");
			printf("\n1. Aceptar\n");
			printf("0. Abortar\n\n");
			printf("#? ");
			scanf("%i", &opt);
			
			if (opt == 0) {
				clearScreen();
				printf("¡Tenga buen día!\n");
				exit(EXIT_SUCCESS);
			}
			
		} while (opt != 1);	
		clearScreen();
		
		// Crear "ficheros"
		printf("Sistema operativo detectado: %s\n", OS);
		printf("Creando ficheros...\n");
		// Detectar OS soportado (Windows y Linux)
		if (strcmp(OS, "Windows") == 0) {
			// Windows
			ret = createFiles();
			// Retorno no esperado
			if (ret == -1) {
				switch (errno) {
				case EACCES:
					printf("Error: Acceso denegado.\n");
					exit(EXIT_FAILURE);
					break;
				default:
					printf("Error: Error desconocido.\n");
				}
			}
			
			contactDBFile = fopen("ficheros/contacts_db.txt", "w");
			contactsNumberFile = fopen("ficheros/contacts_number.txt", "w");
			
			fputc('1', contactsNumberFile);
			
			fclose(contactDBFile);
			fclose(contactsNumberFile);
			
		} else if (strcmp(OS, "Linux") == 0) {
			// Linux
			createFiles();
		} else {
			printf("Error: Sistema operativo no soportado.");
			exit(EXIT_FAILURE);
		}
		system("sleep 5");
		puts("Ficheros creados exitosamente.");
		system("sleep 3");
		clearScreen();
	}
}
// Función de inicio
void startFunc(void) {
	/*Raynner Altamirano | Proyecto Davinia | Julio 07, 2021 | startFunc()*/
	int opt;
	// Opciones disponibles
	printf("1. Ver contactos\n");
	printf("2. Agregar contacto\n");
	printf("0. Salir\n");
	
	printf("\nElija una opcion: ");
	scanf("%i", &opt);
	// Seleccionar las opciones que el usuario quiera.
	switch (opt) {
		case 0: exit(EXIT_SUCCESS); break;
		case 1: listContactsFunc();	break;
		case 2: addContactFunc(); break;
		default: printf("Opción ilegal.\n");
	}
	return;
}

//Visualiza los contactos almacenados en "ficheros/contacts_db.txt"
void listContactsFunc(){
	/*Kenneth Lola | Proyecto Davinia | Julio 08, 2021 | listContactsFunc()
	DESCRIPCION DE VARIABLES
	------------------------
	fp		>> base de datos de contactos
	c		>> Caracter que almacena cada caracter de la base de datos
	EOF		>> final del fichero
	N		>> Cantidad de productos a ingresar
	*/
	
	FILE *fp;
	char c;
	
	fp=fopen("ficheros/contacts_db.txt", "r");
	
	if(fp==NULL){
		printf("\n No se ha podido abrir el fichero");
		exit(1);
	}
	
	printf("\n Contactos\n\n");
	
	c=fgetc(fp);
	while(c!=EOF){
		printf("%c", c);
		c=fgetc(fp);
	}
	
	printf("\n");
	
	fclose(fp);
}	

// Agrega nuevos contactos a la DB "ficheros/contacts_db.txt"
void addContactFunc(void) {
	/*Jeremy Fonseca | Proyecto Davinia | Julio 07, 2021 | addContactFunc()
	DESCRIPCIÓN DE VARIABLES
	------------------------
	contactDBFile			>> Fichero con la DB de los contactos
	contactsNumberFile		>> Fichero con la cantidad total de contactos
	i						>> Contador
	N						>> Cantidad de productos a ingresar
	cant					>> Cantidad de elementos de un contacto
	contactID				>> Identificacion de cada contacto
	contactsNumber			>> Numero de productos en DB
	*/

	// Estructura contacto
	struct Contact {
		char name[20], lastname[20], address[50], contactID[2];
		long int number;
		short int age;
	} contact1;
	
	FILE *contactDBFile, *contactsNumberFile;
	short int i, N;
	int contactsNumber;
	
	// Abrir ficheros a editar
	contactDBFile = fopen("ficheros/contacts_db.txt", "a+");
	contactsNumberFile = fopen("ficheros/contacts_number.txt", "r");
	
	printf("¿Cuántos contactos va a ingresar?\n>> ");
	scanf("%hi", &N);
	
	for (i = 1; i <= N; i++) {
		fscanf(contactsNumberFile, "%i", &contactsNumber); // Obtener la cantidad total de productos en la DB
		
		// Agrega un '0' si la cantidad de productos en DB es de 1 digito
		if (contactsNumber < 10) {
			contact1.contactID[0] = '0';
			contact1.contactID[1] = contactsNumber; // Numero de un digito
			// Imprimir el contactID del producto en la DB
			fprintf(contactDBFile, "%c", contact1.contactID[0]);
			fprintf(contactDBFile, "%i", contact1.contactID[1]);
		} else {
			*contact1.contactID = contactsNumber;
			// Imprimir el contactID del producto en la DB
			fprintf(contactDBFile, "%i", *contact1.contactID);
		}
		++contactsNumber;
		
		fclose(contactsNumberFile);
		contactsNumberFile = fopen("ficheros/contacts_number.txt", "w"); // Abriril it_cant.txt en modo escritura
		fprintf(contactsNumberFile, "%i", contactsNumber); // Actualiza la cantidad de productos en la DB
		fclose(contactsNumberFile);
		
		fprintf(contactDBFile, "%s", " ---- ");
		
		// Peticion de los datos de los contactos
		// Nombre
		printf("Nombre: ");
		scanf("%s", contact1.name);
		fprintf(contactDBFile, "%s", contact1.name);
		fprintf(contactDBFile, "%s", " ---- ");
		
		// Apellido
		printf("Apellido: ");
		scanf("%s", contact1.lastname);
		fprintf(contactDBFile, "%s", contact1.lastname);
		fprintf(contactDBFile, "%s", " ---- ");
		
		// Edad
		printf("Edad: ");
		scanf("%hi", &contact1.age);
		fprintf(contactDBFile, "%hi", contact1.age);
		fprintf(contactDBFile, "%s", " ---- ");
		
		// Telefono
		printf("Teléfono: ");
		scanf("%li", &contact1.number);
		fprintf(contactDBFile, "%li", contact1.number);
		
		fputc('\n', contactDBFile); // Salto de linea
	}
	fclose(contactDBFile);
	return;
}
