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

tarea buscarTarea(tarea **lista, int a);

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

    tarea buscador = buscarTarea(pendientes, cant);
    
    if (buscador.descripcion != NULL)
    {
        puts("-----TAREA ENCONTRADA-----");
        printf("ID: %d\n", buscador.tareaID);
        printf("Descripcion: %s\n", buscador.descripcion);
        printf("Duracion: %d\n", buscador.duracion);
    } else
    {
        puts("-----TAREA NO ENCONTRADA-----");
    }
    
    

    return 0;
}

tarea buscarTarea(tarea **lista, int a)
{
    int aux;
    tarea *buscador;

    puts("\n\n----BUSCADOR DE TAREAS----");
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