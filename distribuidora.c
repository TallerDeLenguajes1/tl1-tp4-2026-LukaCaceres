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
    int encontrado =0;
    while(aux!=NULL  && encontrado==0){ //mientras no sea el end
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
            encontrado=1;
        }
         //paso al siguiente
        if(encontrado==0){
            anterior = aux;
            aux = aux->siguiente;
        }
        
    }
}

void listar(Nodo **start, Nodo **startC){
    Nodo *aux = *start;
    Nodo *auxC= *startC;
    //Listado de pendientes
    printf("\n----------Tareas Pendientes----------");
    while(aux!=NULL){
        printf("\nID: %d", aux->T.id);
        printf("\nDescrpcion: ");
        puts(aux->T.descripcion);
        printf("Duracion: %d", aux->T.duracion);
        aux=aux->siguiente;
    }
     printf("\n-----------------------");
    //Listado de completadas
    printf("\n----------Tareas Completadas----------");
    while(auxC!=NULL){
        printf("\nID: %d", auxC->T.id);
        printf("\nDescrpcion: ");
        puts(auxC->T.descripcion);
        printf("Duracion: %d", auxC->T.duracion);
        auxC=auxC->siguiente;
    }
    printf("\n-----------------------");


}

void consultarById(Nodo **start, Nodo **startC, int id){
    Nodo *aux = *start;
    Nodo *auxC= *startC;
    int encontrado=0;
    while(aux!=NULL){
        if(aux->T.id==id){
            printf("\n-----------------Tarea Pendiente-----------------");
            printf("\nID: %d", aux->T.id);
            printf("\nDescrpcion: ");
            puts(aux->T.descripcion);
            printf("Duracion: %d", aux->T.duracion);
            aux=NULL;
            encontrado = 1;
        }else{
            aux=aux->siguiente;
        }
    }
    while(encontrado==0 && auxC!=NULL){
        if(auxC->T.id==id){
            printf("\n-----------------Tarea Completada-----------------");
            printf("\nID: %d", auxC->T.id);
            printf("\nDescrpcion: ");
            puts(auxC->T.descripcion);
            printf("Duracion: %d", auxC->T.duracion);
            encontrado=1;
            auxC=NULL;
        }else{
            auxC=auxC->siguiente;
        }
    }

    if(encontrado==0){
        printf("\nTarea no encontrada");
    }
}

void consultarByKeyword(Nodo **start, Nodo **startC, char *keyword){
    Nodo *aux = *start;
    Nodo *auxC= *startC;
    int encontrado=0;
    while(aux!=NULL){
        if(strstr(aux->T.descripcion, keyword)){
            printf("\n-----------------Tarea Pendiente-----------------");
            printf("\nID: %d", aux->T.id);
            printf("\nDescrpcion: ");
            puts(aux->T.descripcion);
            printf("Duracion: %d", aux->T.duracion);
            aux=NULL;
            encontrado = 1;
        }else{
            aux=aux->siguiente;
        }
    }
    while(encontrado==0 && auxC!=NULL){
        if(strstr(auxC->T.descripcion, keyword)){
            printf("\n-----------------Tarea Completada-----------------");
            printf("\nID: %d", auxC->T.id);
            printf("\nDescrpcion: ");
            puts(auxC->T.descripcion);
            printf("Duracion: %d", auxC->T.duracion);
            encontrado=1;
            aux=NULL;
        }else{
            auxC=auxC->siguiente;
        }
    }

    if(encontrado==0){
        printf("\nTarea no encontrada");
    }
}

int main(){
    Nodo * start = NULL, *end=NULL, * startC = NULL, *endC=NULL;
    char buff[50];
    char *keyword;
    int indice=0, idBuscar;
    int menu=1;

    do{
        printf("\n-----------------------MENU-----------------------");

        printf("\n 1) Agregar Tarea Pendiente");
        printf("\n 2) Pasar de Pendiente a Completada");
        printf("\n 3) Listar todas las tareas");
        printf("\n 4) Consultar tarea por ID");
        printf("\n 5) Consultar tarea por palabra clave");
        printf("\n 0) Salir");
        printf("\n--------------------------------------------------");
        scanf("%d", &menu);
        fflush(stdin);
        switch(menu){
            case 1:
                crearTarea(&start, &end, indice);
                indice++;
                break;
            case 2:
                printf("\nIngrese el ID de la tarea completada: ");
                scanf("%d", &idBuscar);
                while(idBuscar<1000){
                    printf("\nEl ID debe ser mayor o igual a 1000: ");
                    scanf("%d", &idBuscar);
                }
                transferir(&start, &startC, &endC, idBuscar);
                break;
            case 3:
                listar(&start, &startC);
                break;
            case 4:
                printf("\nIngrese el ID de la tarea a Buscar: ");
                scanf("%d", &idBuscar);
                while(idBuscar<1000){
                    printf("\nEl ID debe ser mayor o igual a 1000: ");
                    scanf("%d", &idBuscar);
                }
                consultarById(&start, &startC, idBuscar);
                break;
            case 5:
                printf("\nIngrese la palabra clave a buscar: ");
                fgets(buff, sizeof(buff), stdin);
                buff[strcspn(buff, "\n")] = '\0';
                int len = strlen(buff)+1;
                keyword = malloc(sizeof(char)*len);
                strcpy(keyword, buff);
                consultarByKeyword(&start, &startC, keyword);
        }
    }while(menu!=0);


    //Liberar memoria
    Nodo *aux = start;
    Nodo *auxC= startC;
    Nodo *actual;
    int encontrado=0;
    while(aux!=NULL){
        free(aux->T.descripcion);
        actual=aux;
        aux=aux->siguiente;
        free(actual);
    }
    while(auxC!=NULL){
        free(auxC->T.descripcion);
        actual=auxC;
        auxC=auxC->siguiente;
        free(actual);
    }
    free(keyword);
    
    return 0;
}