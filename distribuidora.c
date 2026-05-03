#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tarea{
    int id;
    char *descripcion;
    int duracion; //10-100
}Tarea;

typedef struct Nodo{
    Tarea T;
    struct Nodo *siguiente;
}Nodo;


void crearTarea(Nodo **start, Nodo **end, int indice){
    char buffer[50];

    //crear el nodo
    Nodo * Ntarea = malloc(sizeof(Nodo));
    Ntarea->T.id=1000+indice;
    Ntarea->T.duracion=10+rand()%(100-10+1);
    printf("\nIngrese la descripcion de la tarea: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    int len = strlen(buffer)+1;
    Ntarea->T.descripcion=malloc(sizeof(char)*len);
    strcpy(Ntarea->T.descripcion, buffer);

    //Unirlo al inicio de la lista
    /*Ntarea->siguiente=*start;
    *start=Ntarea;
    */

    //Unirlo al final de la lista
    Ntarea->siguiente=NULL; //siempre sera el ultimo, entonces no linkea con nadie
    if(*start==NULL){
        *start=Ntarea;
        *end=Ntarea; //es el primero y el ultimo
    }else{
        //si no es el primero, entonces no cambio el start
        (*end)->siguiente=Ntarea;//modifico el anterior end para que linkee con el nuevo nodo - se usa el parentesis porque -> tiene mayor prioridad que *
        *end=Ntarea; //ahora el ultimo nodo es el recien creado - "modifica para que end ahora apunte al ultimo nodo creado"
    }
}

void transferir(Nodo **start, Nodo **startC, Nodo **endC, int id){
    Nodo *aux = *start;
    Nodo *anterior = NULL;
    while(aux!=NULL){ //mientras no sea el end
        if(aux->T.id==id){

             //Eliminar tarea de la lista de pendientes
            if(anterior==NULL){
                *start=aux->siguiente;
            }else{
                anterior->siguiente=aux->siguiente;
            }
            aux->siguiente=NULL;

            //Agregar a la lista de completadas
            Nodo * Tcompletada=aux;
            Tcompletada->siguiente=NULL;
            if(*startC==NULL){
                *startC=Tcompletada;
                *endC=Tcompletada;
            }else{
                (*endC)->siguiente=Tcompletada;
                *endC=Tcompletada;
            }

        }
        anterior = aux;
        aux = aux->siguiente; //paso al siguiente
    }
}

int main(){
    Nodo * start = NULL, *end=NULL, * startC = NULL, *endC=NULL;
    int bandera=1, indice=0, idBuscar;
    while(bandera==1){
        crearTarea(&start, &end, indice);
        indice++;
        printf("Si desea terminar la carga, ingrese cualquier numero distinto de 1: ");
        scanf("%d", &bandera);
        fflush(stdin);
    }
    printf("\nIngrese el ID de la tarea completada: ");
    scanf("%d", &idBuscar);

    return 0;
}