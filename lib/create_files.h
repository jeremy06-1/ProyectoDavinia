/*	Proyecto Davinia | create_files.h
	En este archivo se ha programado la creación de los ficheros necesarios
para el funcionamiento del programa. Ningún fichero se creará sin el
consentimiento del usuario.
*/
#if defined(_WIN32) || defined(_WIN64)
int createFiles(void) {
	return mkdir("ficheros");
}
#elif defined(__linux__)
int createFiles(void) {
	system("mkdir ficheros");
	system("touch ficheros/contacts_db.txt");
	system("echo 0 > ficheros/username.txt");
	system("echo 0 > ficheros/passwd.txt");
	system("echo 1 > ficheros/contacts_number.txt");
	return 0;
}
#endif

void checkFilesFunc(void); // Comprueba la existencia de ficheros necesarios

void checkFilesFunc() {
	/*Jeremy Fonseca | Proyecto Davinia | Julio 09, 2021 | addContactFunc()
	DESCRIPCION DE VARIABLES
	------------------------
	dir		>> Fichero "ficheros"
	ret		>> Almacena el rotorno de "mkdir" para detectar errores.
	*/	
	FILE *contactDBFile, *contactsNumberFile, *username, *passwd;
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
			printf("En el directorio actual se crearán\n\n");
			puts("->>\t./ficheros/...");
			puts("->>\t./ficheros/username.txt");
			puts("->>\t./ficheros/passwd.txt");
			puts("->>\t./ficheros/contacts_db.txt");
			puts("->>\t./ficheros/contacts_number.txt");
			printf("\n1. Aceptar\n");
			printf("0. Abortar\n\n");
			printf("#? ");
			scanf("%i", &opt);
			
			if (opt == 0) {
				clearScreen();
				printf("¡Tenga un buen día!\n");
				system("sleep 2");
				clearScreen();
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
					exit(EXIT_FAILURE);
				}
			}
			// Crear los ficheros
			contactDBFile = fopen("ficheros/contacts_db.txt", "w");
			contactsNumberFile = fopen("ficheros/contacts_number.txt", "w");
			username = fopen("ficheros/username.txt", "w");
			passwd = fopen("ficheros/passwd.txt", "w");
			
			fputc('1', contactsNumberFile);
			fputc('0', username);
			fputc('0', passwd);
			
			// Cerrar ficheros
			fclose(contactDBFile);
			fclose(contactsNumberFile);
			fclose(username);
			fclose(passwd);
			
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
