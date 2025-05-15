#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){ 
  /*- No se repitan números en las filas
  - No se repitan números en las columnas
  - No se repitan números en las submatrices de 3x3*/

  //No se repitan números en las filas
  for(int i = 0 ; i < 9 ; i++)
  { 
    int numeros[10] = {0};
    for(int k = 0 ; k < 9 ; k++)
    {
      if(n->sudo[i][k] != 0)
      {
        int actual = n->sudo[i][k];
        if(numeros[actual]) return 0; //si ya aparecio, significa que se repite
        numeros[actual] = 1; //si no, lo marcamos en para que en caso de aparecer retornar 0;
      }
    }
  }

  //No se repitan números en las columnas
  for(int i = 0 ; i < 9 ; i++) //es lo mismo que lo de arriba pero al revez
  { 
    int numeros[10] = {0};
    for(int k = 0 ; k < 9 ; k++)
    {
      if(n->sudo[k][i] != 0)
      {
        int actual = n->sudo[k][i];
        if(numeros[actual]) return 0; //si ya aparecio, significa que se repite
        numeros[actual] = 1; //si no, lo marcamos en para que en caso de aparecer retornar 0;
      }
    }
  }

  //No se repitan números en las submatrices de 3x3
  /***int i_inico; int k_inicio; esto esta mal u_u
  int i_final; int k_final;
  
  for(i_inico = 0, i_final = 3 ; i_inico < i_final ; i_inico += 3, i_final += 3)
  {
    for(k_inicio = 0, k_final = 3; k_inicio < k_final ; k_inicio += 3, k_final += 3)
    {
      int numeros[10] = {0};
      if(n->sudo[i_inico][k_inicio] != 0)
      {
        int actual = n->sudo[i_inico][k_inicio];
        if(numeros[actual]) return 0; 
        numeros[actual] = 1;
      }
    }
  } ***/

  int i_inicio, k_inicio; 

  for (i_inicio = 0; i_inicio < 9; i_inicio += 3) 
  {
      for (k_inicio = 0; k_inicio < 9; k_inicio += 3) 
      {
          int numeros[10] = {0}; 

          for (int i = i_inicio; i < i_inicio + 3; ++i) 
          {
              for (int k = k_inicio; k < k_inicio + 3; ++k) 
              {
                  int actual = n->sudo[i][k];
                  if (actual != 0) {
                      if (numeros[actual]) return 0; // Duplicado
                      numeros[actual] = 1;
                  }
              }
          }
      }
  }
  

    return 1;
}


List* get_adj_nodes(Node* n){
    List* list=createList();

    for(int i = 0 ; i < 9 ; i++) //recorro las filas
    {
      for(int k = 0 ; k < 9 ; k++)//y columnas
      {
        /*
        if(n->sudo[i][k] == 0) //si está vacio, puedo ingresar dato
        {
          for(int j = 1 ; j <= 9 ; j++) //y aqui veo que numero agregar
          {
            Node* new = copy(n); //creo una copia
            new->sudo[i][k] = j; //a la copia en la posicion [i][k] le asigno el valor j
            if(is_valid(new)) //si es valido
            {
              pushBack(list, new); //lo agrego a la lista
            }
            else
            {
              free(new); //si no, libero la copia
            }
          }
        }*/
         //no habia leido bien el README, no habia entendido que solo devo retornar nodos, 
         //pero sin usar el is_valid, tampoco me di cuenta que no taba completo hasta leer la 2 u_u
         if(n->sudo[i][k] == 0) //posicion vacía
         {
            //Ahora para la casilla vacia creamos los 9 nodos 
            for(int num = 1 ; num < 9 ; num++) //parte desde 1, no 0 xd
            {
              Node* newNodo = copy(n); //copiamos el nuevo nodo
              newNodo->sudo[i][k] = num; //y al nuevo nodo, le asignamos el numero correspondiente
              if(is_valid(newNodo))
              {
                pushBack(list, newNodo); //si es valido, lo agrego y me salgo
                //return list;
              }
              else free(newNodo); // si no, libero la copia y vuelvo a ver otro numero
            }
            
        }
      }
    }

    return list; //una vez recorrido cada espacio del sudoku se retorna la lista
}


int is_final(Node* n){
    return 0;
}

Node* DFS(Node* initial, int* cont){
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/