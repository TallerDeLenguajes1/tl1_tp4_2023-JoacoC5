#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Tarea 
{
    int tareaID; //Numerado en ciclo iterativo
    char *descripcion;
    int duracion; //aleatorio entre 10-100

} typedef tarea;

tarea buscarTareaPorPalabra (tarea **lista, int a);
tarea buscarTareaPorID (tarea **lista, int a);

int main () {

    srand(time(NULL));
    int cant;

    printf("Ingrese cuantas tareas debe cargar: ");
    scanf("%d", &cant);

    tarea **pendientes = malloc(sizeof(struct Tarea *) * cant);
    tarea **realizadas = malloc(sizeof(struct Tarea *) * cant);
    char buff[100];

    for (int i = 0; i < cant; i++)
    {
        pendientes[i] = NULL;
        pendientes[i] = malloc(sizeof (struct Tarea) * cant);
        pendientes[i]->tareaID = (i+1);
        fflush(stdin);
        pendientes[i]->duracion = 10 + rand()%90;
        fflush(stdin);
        printf("Descripcion de la tarea: ");
        gets(buff);
        pendientes[i]->descripcion = malloc(sizeof(char) * strlen(buff + 1));
        strcpy(pendientes[i]->descripcion, buff);
        fflush(stdin);
    }

    int aux, j = 0;
    puts("\n\n------TAREAS LISTADAS------\n");
    for (int i = 0; i < cant; i++)
    {
        realizadas[i] = NULL;
        printf("\nTarea id: %d\n", pendientes[i]->tareaID);
        printf("Descripcion: %s\n", pendientes[i]->descripcion);
        printf("Duracion: %d\n", pendientes[i]->duracion);
        printf("Se realizo esta tarea? // 1=si - 0=no //\n");
        scanf("%d", &aux);

        if (aux == 1)
        {
            realizadas[j] = pendientes[i];
            pendientes[i] = NULL;
            j++;
        }
        
    }

    puts("\n\n------TAREAS REALIZADAS------\n");
    for (int i = 0; realizadas[i] != NULL; i++)
    {
        printf("\nTarea id: %d\n", realizadas[i]->tareaID);
        printf("Descripcion: %s\n", realizadas[i]->descripcion);
        printf("Duracion: %d\n", realizadas[i]->duracion);
    }
    puts("\n\n------TAREAS AUN PENDIENTES------\n");
    for (int i = 0; i < cant; i++)
    {
        if (pendientes[i] != NULL)
        {
            printf("\nTarea id: %d\n", pendientes[i]->tareaID);
            printf("Descripcion: %s\n", pendientes[i]->descripcion);
            printf("Duracion: %d\n", pendientes[i]->duracion);
        } 
    }

    fflush(stdin);
    
    
    tarea buscadorP = buscarTareaPorPalabra(pendientes, cant);

    if (buscadorP.descripcion != NULL)
    {
        puts("\n\n----TAREA ENCONTRADA----");
        printf("ID: %d\n", buscadorP.tareaID);
        printf("Descripcion: %s\n", buscadorP.descripcion);
        printf("Duracion: %d\n", buscadorP.duracion);
    } else
    {
        puts("\n\n----TAREA NO ENCONTRADA----");
    }

    tarea buscadorI = buscarTareaPorID(pendientes, cant);
    
    if (buscadorI.descripcion != NULL)
    {
        puts("\n\n-----TAREA ENCONTRADA-----");
        printf("ID: %d\n", buscadorI.tareaID);
        printf("Descripcion: %s\n", buscadorI.descripcion);
        printf("Duracion: %d\n", buscadorI.duracion);
    } else
    {
        puts("\n\n-----TAREA NO ENCONTRADA-----");
    }
    
    return 0;
}

tarea buscarTareaPorPalabra (tarea **lista, int a)
{
    char clave[20];
    int aux;
    tarea *buscador = NULL;

    puts("\n------BUSCADOR DE TAREA POR PALABRA------\n");
    printf("Ingrese la palabra clave: ");
    gets(clave);
    fflush(stdin);

    for (int i = 0; i < a; i++)
    {
        if (lista[i] != NULL)
        {
            if (strstr(lista[i]->descripcion, clave))
            {
                buscador = lista[i];
                break;
            } 
 
        }
        
    }
    return *buscador;   

}

tarea buscarTareaPorID(tarea **lista, int a)
{
    int aux;
    tarea *buscador;

    puts("\n\n----BUSCADOR DE TAREAS POR ID----");
    printf("\nID a buscar: ");
    scanf("%d", &aux);
    fflush(stdin);

    for (int i = 0; i < a; i++)
    {
        if (lista[i] != NULL)
        {
            if (lista[i]->tareaID == aux)
            {
                buscador = lista[i];
                break;
            }
        }
  
    }

    return *buscador;   
}