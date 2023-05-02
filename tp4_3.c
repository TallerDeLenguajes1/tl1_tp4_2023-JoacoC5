#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>


struct Tarea
{
    int tareaID; //Numerado en ciclo iterativo
    char *descripcion;
    int duracion; //Entre 10 - 100
}typedef tarea;

typedef struct Tnodo
{
    tarea *T; 
    struct Tnodo *siguiente;
} Tnodo;

Tnodo * crearNodo (tarea *a);

Tnodo * crearListaVacia ();

void insertarNodo (Tnodo **lista, Tnodo *nuevoNodo);

Tnodo * buscarNodo (Tnodo *lista, int id);

void quitarNodo (Tnodo *lista, tarea a);

void eliminarNodo (Tnodo *nodo);

tarea * cargarTarea (char buff[], int id, int duracion);


int main () {

    srand(time(NULL));
    int aux= 1, cont = 1;
    Tnodo *pendientes = crearListaVacia(), *realizadas = crearListaVacia(), *auxLista = crearListaVacia();
    tarea *informacion = (tarea *) malloc(sizeof(tarea));
    char buff[50];

    do
    {
        printf("\nDescripcion tarea: ");
        gets(buff);
        informacion = cargarTarea(buff, cont, (10 +rand()%90));

        insertarNodo(&pendientes, crearNodo(informacion));
        cont++;

        printf("Desea agregar otro nodo? // 1=si - 0=no //: ");
        scanf("%d", &aux);
        fflush(stdin);

    } while (aux != 0);
    

    int opcion;
    tarea *quitado;
    Tnodo * nodoQuitado;

    auxLista = pendientes;
    puts("\n-----LISTADO DE TAREAS-----");

    while (auxLista != NULL)
    {
        printf("\nID: %d\n", auxLista->T->tareaID);
        printf("Duracion: %d\n", auxLista->T->duracion);
        printf("Descripcion: %s\n", auxLista->T->descripcion);

        printf("Se realizo esta tarea?? // 1=si - 0=no //: ");
        scanf("%d", &opcion);
        fflush(stdin);
        puts("---------------");

        if (opcion == 1)
        {
            quitado = auxLista->T;
            insertarNodo(&realizadas, crearNodo(quitado));
            quitarNodo(pendientes, *(auxLista->T));
        } 
        
        
        auxLista = auxLista->siguiente;
    }
    
    puts("\n------TAREAS REALIZADAS------");
    while (realizadas != NULL)
    {
        printf("\nID: %d\n", realizadas->T->tareaID);
        printf("Duracion: %d\n", realizadas->T->duracion);
        printf("Descripcion: %s\n", realizadas->T->descripcion);

        puts("---------------");
        realizadas = realizadas->siguiente;
    }

    puts("\n------TAREAS AUN PENDIENTES------");
    while (pendientes != NULL)
    {
        printf("\nID: %d\n", pendientes->T->tareaID);
        printf("Duracion: %d\n", pendientes->T->duracion);
        printf("Descripcion: %s\n", pendientes->T->descripcion);

        puts("---------------");
        pendientes = pendientes->siguiente;
    }
    
    
    return 0;
}



Tnodo * crearNodo (tarea *a)
{
    Tnodo * Nnodo = (Tnodo *) malloc (sizeof(Tnodo));
    Nnodo->T = a;
    Nnodo->siguiente = NULL;

    return Nnodo;
}

Tnodo * crearListaVacia ()
{
    return NULL;
}

void insertarNodo (Tnodo **lista, Tnodo *nuevoNodo)
{
    nuevoNodo->siguiente = *lista;
    *lista = nuevoNodo;
}

Tnodo * buscarNodo (Tnodo *lista, int id)
{
    Tnodo * aux = lista;

    while (aux && aux->T->tareaID != id);
    {
        aux = aux->siguiente;
    }

    return aux;
    
}

void quitarNodo (Tnodo *lista, tarea a)
{
    Tnodo * aux = lista;
    Tnodo * auxAnt = lista;

    if (aux != NULL && aux->T->tareaID == a.tareaID)
    {
        lista = lista->siguiente;
    } else
    {
        while (aux != NULL && aux->T->tareaID != a.tareaID)
        {
            auxAnt = aux;
            aux = aux->siguiente;
        }

        if (aux != NULL)
        {
            auxAnt->siguiente = aux->siguiente;
        }
        
        
    }
    
}

void eliminarNodo (Tnodo *nodo)
{
    free(nodo->T);
    free(nodo);
}

tarea * cargarTarea (char buff[], int id, int duracion)
{
    tarea * aux = (tarea *) malloc(sizeof(tarea));
    aux->descripcion = malloc(sizeof(char) * strlen(buff+1));
    strcpy(aux->descripcion,buff);
    aux->tareaID = id;
    aux->duracion = duracion;

    return aux;
}