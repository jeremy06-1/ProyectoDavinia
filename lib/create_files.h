/*	Proyecto Davinia | create_files.h
	En este archivo se ha programado la creación de los ficheros necesarios
para el funcionamiento del programa. Ningún fichero se creará sin el
consentimiento del usuario.
*/

void	checkFilesFunc(void); // Comprueba la existencia de ficheros necesarios

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
			printf("\nEn el directorio actual se crearan\n\n");
			puts("->>\t./fichero/...");
			puts("->>\t./fichero/contacts_db.txt");
			puts("->>\t./fichero/contacts_number.txt");
			printf("\n1. Aceptar\n");
			printf("0. Abortar\n\n");
			printf("#? ");
			scanf("%i", &opt);
			
			if (opt == 0) {
				clearScreen();
				printf("¡Tenga buen dia!\n");
				system("sleep 3");
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
