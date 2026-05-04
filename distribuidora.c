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

void listar(Nodo **start, Nodo **startC){
    Nodo *aux = *start;
    Nodo *auxC= *startC;
    //Listado de pendientes
    while(aux!=NULL){
        printf("\nID: %d", aux->T.id);
        printf("\nDescrpcion: ");
        puts(aux->T.descripcion);
        printf("Duracion: %d", aux->T.duracion);
        aux=aux->siguiente;
    }
    while(auxC!=NULL){
        printf("\nID: %d", auxC->T.id);
        printf("\nDescrpcion: ");
        puts(auxC->T.descripcion);
        printf("Duracion: %d", auxC->T.duracion);
        auxC=auxC->siguiente;
    }


}

int main(){
    Nodo * start = NULL, *end=NULL, * startC = NULL, *endC=NULL;
    int bandera=1, banderaC=1, indice=0, idBuscar;

    //Crear Tarea Pendiente
    while(bandera==1){
        crearTarea(&start, &end, indice);
        indice++;
        printf("Ingrese 1 para seguir la carga y 0 para salir: ");
        scanf("%d", &bandera);
        fflush(stdin);
    }

    //Pasar de pendiente a completada
    while(banderaC==1){
        printf("\nIngrese el ID de la tarea completada: ");
        scanf("%d", &idBuscar);
        while(idBuscar<1000){
            printf("\nEl ID debe ser mayor o igual a 1000: ");
            scanf("%d", &idBuscar);
        }
        transferir(&start, &startC, &endC, idBuscar);
        printf("Ingrese 1 para seguir la carga y 0 para salir: ");
        scanf("%d", &banderaC);
        fflush(stdin);
    }

    //Listar tareas
    listar(&start, &startC);

    

    return 0;
}