/*	Proyecto Davinia | agenda_logic.h
	En este archivo se ha programado la lógica que hace que se agreguen nuevos
contactos y que se puedan visualizar.
*/

void	listContactsFunc(void), // Visualiza todos los contactos en la DB
		addContactFunc(void); // Agrega nuevos contactos en la DB

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
	DESCRIPCIÃ“N DE VARIABLES
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
	
	printf("¿Cuantos contactos va a ingresar?\n>> ");
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
		printf("Telefono: ");
		scanf("%li", &contact1.number);
		fprintf(contactDBFile, "%li", contact1.number);
		
		fputc('\n', contactDBFile); // Salto de linea
	}
	fclose(contactDBFile);
	return;
}
