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

void quitarNodo (Tnodo **lista, tarea a);

void eliminarNodo (Tnodo **nodo);

tarea * cargarTarea (char buff[], int id, int duracion);

void mostrarDatos (Tnodo *lista);


int main () {

    srand(time(NULL));
    int aux= 1, cont = 1;
    Tnodo *pendientes = crearListaVacia(), *realizadas = crearListaVacia();
    Tnodo *auxPendientes = crearListaVacia(), *proceso = crearListaVacia();
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

    auxPendientes = pendientes;
    puts("\n-----LISTADO DE TAREAS-----");

    while (auxPendientes != NULL)
    {
        printf("\nID: %d\n", auxPendientes->T->tareaID);
        printf("Duracion: %d\n", auxPendientes->T->duracion);
        printf("Descripcion: %s\n", auxPendientes->T->descripcion);

        printf("Estado de la tarea?? // 1=realizada - 2=proceso - 0=pendiente //: ");
        scanf("%d", &opcion);
        fflush(stdin);
        puts("---------------");

        if (opcion == 1)
        {
            quitado = auxPendientes->T;
            insertarNodo(&realizadas, crearNodo(quitado));
            quitarNodo(&pendientes, *(auxPendientes->T));
        } else
        {
            if (opcion == 2)
            {
                quitado = auxPendientes->T;
                insertarNodo(&proceso, crearNodo(quitado));
                quitarNodo(&pendientes, *(auxPendientes->T));
            }
            
        }
        
        auxPendientes = auxPendientes->siguiente;
    }

    int menu, buscador, opcionTarea, opcionLista, origen;
    Tnodo *buscado, *auxRealizadas=crearListaVacia(), *auxProceso = crearListaVacia();

    while (menu != 0)
    {       
        auxPendientes = pendientes;
        auxProceso = proceso;
        auxRealizadas = realizadas;
        buscado = NULL;

        puts("\n\n--------MENU DE TAREAS---------\n\n"); 

        puts("\n------TAREAS REALIZADAS------");
        while (auxRealizadas != NULL)
        {
            printf("\nID: %d\n", auxRealizadas->T->tareaID);
            printf("Duracion: %d\n", auxRealizadas->T->duracion);
            printf("Descripcion: %s\n", auxRealizadas->T->descripcion);

            puts("---------------");
            auxRealizadas = auxRealizadas->siguiente;
        }

        puts("\n------TAREAS EN PROCESO------");
        while (auxProceso != NULL)
        {
            printf("\nID: %d\n", auxProceso->T->tareaID);
            printf("Duracion: %d\n", auxProceso->T->duracion);
            printf("Descripcion: %s\n", auxProceso->T->descripcion);
            puts("---------------");

            auxProceso = auxProceso->siguiente;
        }

        puts("\n------TAREAS AUN PENDIENTES------");
        while (auxPendientes != NULL)
        {
            printf("\nID: %d\n", auxPendientes->T->tareaID);
            printf("Duracion: %d\n", auxPendientes->T->duracion);
            printf("Descripcion: %s\n", auxPendientes->T->descripcion);

            puts("---------------");
            auxPendientes = auxPendientes->siguiente;
        }

        auxPendientes = pendientes;
        auxProceso = proceso;
        auxRealizadas = realizadas;

        printf("Ingrese el id de una tarea: ");
        scanf("%d", &buscador);

        printf("\nQue desea hacer con la tarea?? \n// 1=mover a otra lista - 2=eliminar - 0=nada //: ");
        scanf("%d", &opcionTarea);

        if (buscador <= cont) //no deberia recibir numeros negativos, solo mayores o igual a 1
        {
            if (opcionTarea == 1) //solo funciona con la tarea q se encuentra arriba de su lista 
            {
                if (buscado == NULL)
                {
                    buscado = buscarNodo(auxPendientes, buscador);
                    if (buscado == NULL)
                    {
                        buscado = buscarNodo(auxProceso, buscador);    
                        if (buscado == NULL)
                        {
                            buscado = buscarNodo(auxRealizadas, buscador);
                            origen = 3;
                        } else
                        {
                            origen = 2;
                        }
                        
                    } else
                    {
                        origen = 1;
                    }
                    
                }

                auxPendientes = pendientes;
                auxProceso = proceso;
                auxRealizadas = realizadas;

                if (buscado != NULL)
                {
                    puts("\n\n----TAREA ENCONTRADA----\n");
                    printf("A que lista desea mover la tarea?? \n// 1=pendientes - 2=proceso - 3=realizadas //: ");
                    scanf("%d", &opcionLista);    

                    if (origen == 1)
                    {
                        if (opcionLista == 2)
                        {
                            quitado = buscado->T;
                            insertarNodo(&proceso, crearNodo(quitado));
                            quitarNodo(&pendientes, *(buscado->T));
                        } else
                        {
                            if (opcionLista == 3)
                            {
                                quitado = buscado->T;
                                insertarNodo(&realizadas, crearNodo(quitado));
                                quitarNodo(&pendientes, *(buscado->T));
                            } else
                            {
                                printf("\nYa se encuentra en esta lista\n");    
                            }    
                        }
                        puts("----MOVIMIENTO EXITOSO----");
                        
                    } else
                    {
                        if (origen == 2)
                        {
                            if (opcionLista == 1)
                            {
                                quitado = buscado->T;
                                insertarNodo(&pendientes, crearNodo(quitado));
                                quitarNodo(&proceso, *(buscado->T));
                            } else
                            {
                                if (opcionLista == 3)
                                {
                                    quitado = buscado->T;
                                    insertarNodo(&realizadas, crearNodo(quitado));
                                    quitarNodo(&proceso, *(buscado->T));
                                } else
                                {
                                    printf("\nYa se encuentra en esta lista\n");
                                }
                                
                            }
                            puts("----MOVIMIENTO EXITOSO----");
                            
                        } else
                        {
                            if (origen == 3)
                            {
                                if (opcionLista == 1)
                                {
                                    quitado = auxRealizadas->T;
                                    insertarNodo(&pendientes, crearNodo(quitado));
                                    quitarNodo(&realizadas, *(auxRealizadas->T));
                                } else
                                {
                                    if (opcionLista == 2)
                                    {
                                        quitado = auxRealizadas->T;
                                        insertarNodo(&proceso, crearNodo(quitado));
                                        quitarNodo(&realizadas, *(auxRealizadas->T));
                                    } else
                                    {
                                        printf("\nYa se encuentra en esta lista\n");
                                    }
                                }

                                puts("----MOVIMIENTO EXITOSO----");
                                
                            }
                            
                        }
                        
                        
                    }
                    
                    
                } else
                {
                    puts("\n----NO SE ENCONTRO LA TAREA----\n");
                }

            } else
            {
                if (opcionTarea == 2) 
                {
                    if (buscado == NULL)
                    {
                        buscado = buscarNodo(auxPendientes, buscador);
                        if (buscado == NULL)
                        {
                            buscado = buscarNodo(auxProceso, buscador);    
                            if (buscado == NULL)
                            {
                                buscado = buscarNodo(auxRealizadas, buscador);
                                origen = 3;
                            } else
                            {
                                origen = 2;
                            }
                            
                        } else
                        {
                            origen = 1;
                        }
                        
                    }

                    auxPendientes = pendientes;
                    auxProceso = proceso;
                    auxRealizadas = realizadas;

                    switch (origen)
                    {
                    case 1:
                        quitarNodo(&pendientes, *(buscado->T));
                        //eliminarNodo(&buscado);
                        break;
                    case 2:
                        quitarNodo(&proceso, *(buscado->T));
                        //eliminarNodo(&buscado);
                        break;
                    case 3:
                        quitarNodo(&realizadas, *(buscado->T));
                        //eliminarNodo(&buscado);
                        break;
                    }                    
                    
                }
                
            }
            
        } else
        {
            puts("\n-----ID incorrecto-----\n");
        }
        
        printf("\nDesea modificar otra tarea?? // 1=si - 0=no //: ");
        scanf("%d", &menu);

    }

    puts("\n\n------RESUMEN DE LAS LISTAS------\n");
    puts("--REALIZADAS--");
    mostrarDatos(realizadas);
    puts("\n\n--EN PROCESO--");
    mostrarDatos(proceso);
    puts("\n\n--PENDIENTES--");
    mostrarDatos(pendientes);
    

    puts("\n\n------FIN DEL PROCESO------");
    
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

    while (aux)
    {
        if (aux->T->tareaID == id)
        {
            return aux;
        } else
        {
            aux = aux->siguiente;
        }
        
        
    }
    
}

void quitarNodo (Tnodo **lista, tarea a)
{
    Tnodo * aux = *lista;
    Tnodo * auxAnt = *lista;

    while (aux != NULL && aux->T->tareaID != a.tareaID)
    {
            auxAnt = aux;
            aux = aux->siguiente;
    }

    if (aux != NULL)
    {
        if (aux == *lista)
        {
            *lista = aux->siguiente;
        } else
        {
            auxAnt->siguiente = aux->siguiente;
        }
        
    }
    
}

void eliminarNodo (Tnodo **nodo)
{
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

void mostrarDatos (Tnodo *lista)
{
    Tnodo *aux = lista;
    int cont = 0, duracion = 0;


    while (aux != NULL)
    {
        duracion += aux->T->duracion;
        cont ++; 

        aux = aux->siguiente;
    }

    printf("\nEn esta lista hay %d tareas\nLa duracion total de ellas es: %d", cont, duracion);
    
}