#include <stdio.h>
#include <string.h> /* gets, strcmp */
#include <stdlib.h> /* system */
#include <conio.h> /*getch*/

#define TECLA_ENTER 13
#define TECLA_BACKSPACE 8
#define LONGITUD 5

int main(int argc, char const *argv[])
{
	char usuario[LONGITUD + 1];
	char clave[LONGITUD + 1];
    char clave2[LONGITUD + 1];
    char caracter;
    int i=0;
    printf("Bienvenido\nIngrese el nombre el nuevo usuario\n\n\tNOMBRE: ");
    scanf("%s",usuario);
    printf("%s",usuario);
  		printf("\tCLAVE: ");
		while (caracter = getch()) {
			if (caracter == TECLA_ENTER) {
				clave[i] = '\0';
				break;
				
			} else if (caracter == TECLA_BACKSPACE) {
				if (i > 0) {
					i--;
					printf("\b \b");
				}} else {
				if (i < LONGITUD) {
					printf("*");
					clave[i] = caracter;
					i++;
				}}}
                    printf("%s",clave);
            i=0;
    printf ("\n\nFavor vuelva a ingresar la clave\n\n\tCLAVE: ");
    		while (caracter = getch()) {
			if (caracter == TECLA_ENTER) {
				clave2[i] = '\0';
				break;
				
			} else if (caracter == TECLA_BACKSPACE) {
				if (i > 0) {
					i--;
					printf("\b \b");
				}} else {
				if (i < LONGITUD) {
					printf("*");
					clave2[i] = caracter;
					i++;
				}}}
            printf("%s",clave2);
	short comprobante = 1; 
	for (i = 0; i < LONGITUD+1; i++)
	{
		if (clave[i] != clave2[i])
		{
			comprobante = 0;
		}
	}
    if (comprobante){
        printf("\n\tUsuario registrado correctamente\n");
    }else{
   do
    {   i=0;
        printf("\n\nLas claves no coinciden, favor volver a ingresarla clave\n\n\tCLAVE: ");
    	while (caracter = getch()) {
		if (caracter == TECLA_ENTER) {
			clave2[i] = '\0';
			break;
            } 
            else if (caracter == TECLA_BACKSPACE) {
				if (i > 0) {
					i--;
					printf("\b \b");
				}} else {
				if (i < LONGITUD) {
					printf("*");
					clave2[i] = caracter;
					i++;
				}}}
            printf("%s",clave2);
    } while (clave[LONGITUD+1]==clave2[LONGITUD+1]);
    printf("\n\nUsuario registrado correctamente");
    }
    system("pause");
    return 0;}
