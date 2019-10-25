#include <stdio.h>
#include <stdlib.h>

/*-------------------- INICIO DEL TDA GRAFO -----------------------*/

#define VISITADO 1                      // Se define globalmente VISITADO = 1 y NOVISITADO = 0 para marcar los vertices
#define NOVISITADO 0                    // del grafo

/*---Definicion de estructuras---*/

typedef int Vertice;                    // Se crea el tipo vertice como un int.

typedef struct nodo{                    // Se crea el struct nodo, el cual formara parte de las listas de adyacencia
    struct lista* ciudad;               // del grafo. Tienen un puntero a la lista de la adyacencia de la ciudad que
   	struct nodo* next;                  // representan y un puntero al siguiente nodo.
}nodo;

typedef struct lista{                   // Se crea el struct lista, el cual representara la adyacencia de los vertices
    int marca;                          // del grafo. Tiene un campo marca el cual representara si fue visitado o no,
    int numero;                         // un campo numero el cual indica su posicion en el arreglo de listas y un
	nodo *cabeza;                       // campo que indica el tamaño de la lista. Tambien
	nodo *cola;                         // tiene campos que apuntan a la cabeza, a la cola y al actual.
	nodo *act;
	int tamano;
}lista;

typedef struct Grafo{                   // Se crea el struct grafo, el cual posee el arreglo de listas de adyacencia,
    lista *pl;                          // un campo que indica la cantidad de vertices y otro que indica la cantidad
    int cv;                             // de aristas del grafo.
    int ca;
}Grafo;

/*---Definicion de Funciones---*/

/*****
*
void iniciarLista
******
*
funcion que inicia un la lista vacia, asigando valores a sus principales variables.
******
*
Input:
*
lista *l : puntero tipo lista el cual indica donde esta la lista a iniciar.
*
.......
******
*
Returns:
*
void, no retorna nada pero nos inicia las principales variables de nuestra
      estructura lista.
*****/

void iniciarLista(lista *l, int i){
    l->numero = i;
    l->cabeza = NULL;
    l->cola = NULL;
    l->act = NULL;
    l-> tamano = 0;
}

/*****
*
int primero
******
*
funcion que entrega el primer vecino del vertice solicitado.
******
*
Input:
*
Grafo *G : puntero tipo grafo el cual indica donde esta el grafo.
Vertice v: vertice del cual se busca su primer vecino
*
.......
******
*
Returns:
*
int, retorna el primer vertice vecino de v
*****/

int primero(Grafo *G, Vertice v){
    (&(G->pl[v]))->act = (&(G->pl[v]))->cabeza;
    if((&(G->pl[v]))->cabeza == NULL) return G->cv;
    return (&(G->pl[v]))->cabeza->ciudad->numero;
}

/*****
*
int siguiente
******
*
funcion que entrega el siguiente vecino de un vertice v.
******
*
Input:
*
Grafo *G : puntero tipo grafo el cual indica donde esta el grafo.
Vertice v: vertice del que se quiere buscar un vertice vecino.
*
.......
******
*
Returns:
*
int, retorna el siguiente vecino de v desde el vertice n.
*****/

int siguiente(Grafo *G,Vertice v) {
    if ((&(G->pl[v]))->act->next == NULL) {
      return G->cv;
    }
    (&(G->pl[v]))->act = (&(G->pl[v]))->act->next;
    return (&(G->pl[v]))->act->ciudad->numero;
}

/*****
*
void marcar
******
*
funcion que marca el vertice v asignando al campo marca el valor m
******
*
Input:
*
Grafo *G : puntero tipo grafo el cual indica donde esta el grafo.
Vertice v: vertice que se quiere marcar
int m: entero el cual se le asignara ese valor al campo marca del vertice
*
.......
******
*
Returns:
*
No retorna nada, solo cambia le asigna al campo marca el valor m.
*****/

void marcar(Grafo *G, Vertice v, int m) {
    (&(G->pl[v]))->marca = m;
}

/*****
*
int obt_marca
******
*
funcion que obtiene el valor del campo marca del vertice
******
*
Input:
*
Grafo *G : puntero tipo grafo el cual indica donde esta el grafo.
Vertice v: vertice del que se quiere obtener la marca.
*
.......
******
*
Returns:
*
int, retorna el valor del campo marca del vertice v.
*****/

int obt_marca(Grafo *G, Vertice v){
    return ((&(G->pl[v]))->marca );
}

/*****
*
void reiniciarMarca
******
*
funcion que reinicia el campo marca de los vertices del grafo
******
*
Input:
*
Grafo *G : puntero tipo grafo el cual indica donde esta el grafo.
*
.......
******
*
Returns:
*
No retorna nada, pero cambia el valor del campo marca de los vertices.
*****/

void reiniciarMarca(Grafo *G){
    int i;
    for (i = 0; i < G->cv; i++) {
        marcar(G,i,NOVISITADO);
    }
}

/*****
*
void DFS
******
*
funcion que recorre el grafo a profundidad desde un vertice v
******
*
Input:
*
Grafo *G : puntero tipo grafo el cual indica donde esta el grafo.
Vertice v: vertice del que se partirá el recorrido.
int *cont: puntero del tipo int, el cual fucionara como un contador para saber a cuantos vertices
          alcanza el DFS
*
.......
******
*
Returns:
*
no retorna nada, pero recorre el grafo a profundida desde el vertice v.
*****/

void DFS(Grafo *G,Vertice v, int *c){
    Vertice w;
    marcar(G,v,VISITADO);
    (*c)++;
    for (w = primero(G,v); w < G->cv ; w = siguiente(G,v)) {
        if (obt_marca(G,w)==NOVISITADO) {
            DFS(G,w,c);
        }
    }
}

/*****
*
void Agregar
******
*
funcion que agrega un nodo a la lista de adyacencia del vertice O (agrega la arista (O,D)
******
*
Input:
*
Grafo *G : puntero tipo grafo el cual indica donde esta el grafo.
Vertice O: vertice de origen que se le agregara el vertice D a su lista de adyacencia.
Vertice D: vertice de destino que sera agregado a la lista de adyacencia del vertice D.
*
.......
******
*
Returns:
*
No retorna nada, solo agrega el vertice D a la lista de adyacencia de O.
*****/


void Agregar(Grafo *G, Vertice O, Vertice D){
    nodo *temp = (nodo*)malloc(sizeof(nodo));              // Se verifica que el malloc se haya realizado exitosamente
    if (temp ==NULL){
        printf("No hay suficiente memoria\n");
        exit(1);
    }
    temp->ciudad = &G->pl[D];
    if ((G->pl[O]).tamano != 0) {
        (G->pl[O]).cola->next = temp;
        (G->pl[O]).cola = temp;
    }
    else{
        G->pl[O].cola = G->pl[O].cabeza = temp;
    }
    temp->next = NULL;
    G->pl[O].tamano ++;
}

/*****
*
void vaciar
******
*
funcion que vacia la lista l.
******
*
Input:
*
lista *l : puntero tipo lista el cual indica donde esta la lista a vaciar.
*
.......
******
*
Returns:
*
No retorna nada, pero libera la memoria de todos los nodos de la lista.
*****/

void vaciar(lista *l){
    int i;
    for (i = 0; i < l->tamano; i++) {
        l->act = l->cabeza->next;
        free((void *)l->cabeza);
        l->cabeza = l->act;
    }
    l->tamano = 0;
}

/*****
*
void IniciarGrafo
******
*
funcion que inicia el grafo G con sus principales valores.
******
*
Input:
*
Grafo *G : puntero tipo grafo el cual indica donde esta el grafo.
int cv: cantidad de vertices del grafo.
int ca: cantidad de arcos del grafo.
*
.......
******
*
Returns:
*
No retorna nada, pero inicializa el grafo con sus principales valores.
*****/

void iniciarGrafo(Grafo *G,int cv,int ca){
    int i;

    G->pl = (lista *)malloc(sizeof(lista)*cv);      // Se verifica que el malloc se haya realizado exitosamente
    if (G->pl == NULL){
        printf("No hay suficiente memoria\n");
        exit(1);
    }
    G->cv = cv;
    G->ca = ca;
    for (i = 0; i < cv; i++) {
        iniciarLista((&(G->pl[i])), i);
    }
}

/*****
*
void VaciarGrafo
******
*
funcion que vacia el grafo G
******
*
Input:
*
Grafo *G : puntero tipo grafo el cual indica donde esta el grafo.
*
.......
******
*
Returns:
*
No retorna nada, pero llama a la funcion vaciar para vaciar cada una de las listas de adyacencia
que posee el arreglo de listas del grafo, luego libera la memoria pedida para este arreglo.
*****/

void VaciarGrafo(Grafo *G) {
    int i;
    for (i = 0; i < G->cv; i++) {
        vaciar(&(G->pl[i]));
    }
    free((void *)G->pl);
    G->cv = 0;
    G->ca = 0;
    G->pl = NULL;
}

//-------------------FIN DEL TDA---------------------------//

int main() {
    Grafo G;
    int cn,ca,cc,O,D,i,k,*Q,cont;         // Se declaran las variables a utilizar en el programa.

    scanf("%d",&cn);
    scanf("%d",&ca);
    iniciarGrafo(&G,cn,ca);               // Se piden por consola la cantidad de nodos y arcos del grafo para iniciarlo.
    for (i = 0; i < ca; i++) {
        scanf("%d %d",&O,&D);             // Se consultan que arcos axistiran y se van añadiendo con la funcion Agregar.
        Agregar(&G,O,D);
    }
    scanf("%d",&cc);                      // Se pide por pantalla la cantidad de consultas a realizar
    Q = (int *)malloc(sizeof(int)*cc);    // y se crea un arreglo de ese tamaño.
    if (Q == NULL){
        printf("No hay suficiente memoria\n");  // Se verifica que el malloc se haya realizado exitosamente
        exit(1);
    }
    for (i = 0; i < cc; i++) {
        scanf("%d",&Q[i]);                // Luego se recorre el arreglo y por cada iteracion se va pidiendo
    }                                     // la consulta por pantalla y se va guardando en el arreglo.
    printf("%d\n",cc);                    // Se muestra por consola el numero de consultas realizadas.
    for (i = 0; i < cc; i++){
        cont = 0;                         // Se recorre el arreglo de consultas y por cada iteracion se inicializa
        reiniciarMarca(&G);               // un contador en 0, se reinician las marcas del grafo, se recorre con DFS,
        DFS(&G,Q[i],&cont);               // y se muestra por consola cuantos vertices no alcanza el vertice consultado.
        printf("%d", cn - cont);
        for (k = 0; k < cn; k++) {
            if (obt_marca(&G,k)==NOVISITADO) {    // Luego, se va consultando a cada vertice la marca que tiene,
                printf(" %d",k);                  // si resulta ser que no fue visitado, entonces el vertice consultado
            }                                     // no lo alcanza, por ende se muestra por pantalla el vertice
        }                                         // no alcanzado.
        printf("\n");
    }
    free((void *)Q);                      // Se libera la memoria pedida para el arreglo de consultas
    VaciarGrafo(&G);                      // y se vacia el grafo, liberando toda la memoria pedida para este.

    return 0;
}
