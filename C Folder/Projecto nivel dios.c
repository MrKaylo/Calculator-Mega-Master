#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

typedef struct {       //typedef es para evitar usar tanto struct
    char codigo;
    char nombre[41];
    char puntaje;
} tequipo;


void continuar()
{
    printf("Presione una tecla para continuar\n\n");
    getch();
}

void crear()
{
    FILE *arch;
    arch=fopen("equipos.dat","wb");
    if (arch==NULL)
        exit(1);
    fclose(arch);
    continuar();
}


void cargar()
{
    FILE *arch;
    arch=fopen("equipos.dat","ab");
    if (arch==NULL)
        exit(1);
    tequipo equipo;
    printf("Ingrese el codigo del Equipo: ");
    scanf("%i",&equipo.codigo);
    fflush(stdin);
    printf("Ingrese el nombre del Equipo: ");
    gets(equipo.nombre);
    printf("Ingrese Puntaje: ");
    scanf("%f",&equipo.puntaje);
    fwrite(&equipo, sizeof(tequipo), 1, arch);
    fclose(arch);
    continuar();
}

void listado()
{
    FILE *arch;
    arch=fopen("equipos.dat","rb");
    if (arch==NULL)
        exit(1);
    tequipo equipo;
    fread(&equipo, sizeof(tequipo), 1, arch);
    while(!feof(arch))
    {
        printf("%i %s %0.2f\n", equipo.codigo, equipo.nombre, equipo.puntaje);
        fread(&equipo, sizeof(tequipo), 1, arch);
    }
    fclose(arch);
    continuar();
}

void consulta()
{
    FILE *arch;
    arch=fopen("equipos.dat","rb");
    if (arch==NULL)
        exit(1);
    printf("Ingrese el codigo de equipo a consultar: ");
    int cod;
    scanf("%i", &cod);
    tequipo equipo;
    int existe=0;
    fread(&equipo, sizeof(tequipo), 1, arch);
    while(!feof(arch))
    {
        if (cod==equipo.codigo)
        {
           printf("%i %s %0.2f\n", equipo.codigo, equipo.nombre, equipo.puntaje);
           existe=1;
           break;
        }
        fread(&equipo, sizeof(tequipo), 1, arch);
    }
    if (existe==0)
        printf("No existe un equipo con dicho codigo\n");
    fclose(arch);
    continuar();
}

void modificacion()
{
    FILE *arch;
    arch=fopen("equipos.dat","r+b");
    if (arch==NULL)
        exit(1);
    printf("Ingrese el codigo de equipo a modificar: ");
    int cod;
    scanf("%i", &cod);
    tequipo equipo;
    int existe=0;
    fread(&equipo, sizeof(tequipo), 1, arch);  //fread devuelve el número de elementos completos leídos por la función
    while(!feof(arch))
    {
        if (cod==equipo.codigo)         //Todo esto modificara el archivo que se creo
        {
           printf("%i %s %0.2f\n", equipo.codigo, equipo.nombre, equipo.puntaje);
           printf("Ingrese nuevo puntaje: ");
           scanf("%f",&equipo.puntaje);
           int pos=ftell(arch)-sizeof(tequipo);
           fseek(arch,pos,SEEK_SET);
           fwrite(&equipo, sizeof(tequipo), 1, arch);
           printf("Se modifico el puntaje para ese equipo.\n");
           existe=1;
           break;
        }
        fread(&equipo, sizeof(tequipo), 1, arch);
    }
    if (existe==0)
        printf("No existe un equipo con dicho codigo\n");
    fclose(arch);
    continuar();
}

int main()
{

    system("color 0c");      //Cambia el color de la pantalla
    int opcion;
    do {
            printf("\n\n\n\n\t\t\t\t      -----------------------------------------------\n");
		printf("\t\t\t\t\t        SISTEMA CONTROL DE EQUIPOS\n\n");
		printf("\t\t\t\t\t[1] - Crear un archivo binario llamado \"equipos.dat\"\n");
		printf("\t\t\t\t\t[2] - Registrar Equipo.\n");
		printf("\t\t\t\t\t[3] - Listado del Equipo.\n");
		printf("\t\t\t\t\t[4] - Consulta de un equipo por su codigo.\n");
		printf("\t\t\t\t\t[5] - Modificar Equipo.\n");
		printf("\t\t\t\t\t[6] - Salir\n\n");
		printf("\t\t\t\t      -----------------------------------------------\n");
		printf("\t\t\t\t\t\t   Elije una opcion: ");
        scanf("%i",&opcion);
        switch (opcion) {       //Lista de opciones
            case 1:crear();
                   break;
            case 2:cargar();
                   break;
            case 3:listado();
                   break;
            case 4:consulta();
                   break;
            case 5:modificacion();
                   break;
        }
    } while (opcion!=6);
    return 0;
}
