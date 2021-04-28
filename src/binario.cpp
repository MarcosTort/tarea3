/*
  Módulo de definición de 'TBinario'.

  Los elementos de tipo 'TBinario' son árboles binario de búsqueda cuyos
  elementos son de tipo 'TInfo'.
  La propiedad de orden de los árboles es definida por el componente natural de
  sus elementos.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */
#include "../include/utils.h"
#include "../include/iterador.h"
#include "../include/info.h"
#include "../include/utils.h"
#include "../include/cadena.h"
#include "../include/binario.h"
#include <assert.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
// Representación de 'TBinario'.
// Se debe definir en binario.cpp.
// struct _rep_binario;
// Declaración del tipo 'TBinario'

struct _rep_binario {
  TInfo dato;
  _rep_binario *izq;
  _rep_binario *der;
};

/*
  Devuelve un 'TBinario' vacío (sin elementos).
  El tiempo de ejecución es O(1).
 */
TBinario crearBinario(){
  return NULL;
}
//LISTO
/*
  Inserta 'i' en 'b' respetando la propiedad de orden definida.
  Devuelve 'b'.
  Precondición: esVacioBinario(buscarSubarbol(natInfo(i), b).
  El tiempo de ejecución es O(log n) en promedio, siendo 'n' la cantidad de
  elementos de 'b'.
 */
TBinario insertarEnBinario(TInfo i, TBinario b){

  assert(esVacioBinario(buscarSubarbol(natInfo(i), b)));

  if(!esVacioBinario(b)){
    if(natInfo(i)>natInfo(b->dato)){b = insertarEnBinario(i, b->izq);}
    else 
    if(natInfo(i)<natInfo(b->dato)){b = insertarEnBinario(i, b->der);}
  }
  else{
    b = new _rep_binario;
    b->dato = i;
    b->izq = NULL;
    b->der = NULL;
  }
  return b;
}
//LISTO
/*
  Devuelve el elemento mayor (según la propiedad de orden definida) de 'b'.
  Precondición: ! esVacioBinario(b).
  El tiempo de ejecución es O(log n) en promedio, siendo 'n' la cantidad de
  elementos de 'b'.
 */
TInfo mayor(TBinario b){//LISTO
  TInfo ret = b->dato;
  if (!esVacioBinario(b)){
    if(b->der == NULL){ret = b->dato;}
    else{mayor(b->der);ret = b->dato;}
  }
  return ret;
;}
/*
  Remueve el nodo en el que se localiza el elemento mayor de 'b'
  (libera la memoria  asignada al nodo, pero no la del elemento).
  Devuelve 'b'.
  Precondición: ! esVacioBinario(b).
  El tiempo de ejecución es O(log n) en promedio, siendo 'n' la cantidad de
  elementos de 'b'.
 */
TBinario removerMayor(TBinario b){//LISTO
  if(!esVacioBinario(b)){
    if( b->der == NULL){
      TBinario izquierda = b->izq;
      delete (b);
      b = izquierda;
    }
    else{removerMayor(b->der);}
  }
  return b;
} 

/*
  Remueve de 'b' el nodo en el que el componente natural de su elemento es
  'elem'.
  Si los dos subárboles del nodo a remover son no vacíos, en sustitución del
  elemento removido debe quedar el que es el mayor (segun la propiedad de orden
  definida) en el subárbol izquierdo.
  Devuelve 'b'.
  Precondición: !esVacioBinario(buscarSubarbol(elem, b).
  Libera la memoria del nodo y del elemento.
  El tiempo de ejecución es O(log n) en promedio, siendo 'n' la cantidad de
  elementos de 'b'.
 */
 TBinario removerDeBinario(nat elem, TBinario b);
 TBinario removerDeBinario(nat elem, TBinario b){//LISTO
if (b != NULL ){
  if (natInfo(b->dato) == elem){
    if (b->der != NULL && b->izq != NULL){
    b->dato =  mayor(b->izq);
    removerMayor(b->izq);
    }
    else if (b->der == NULL && b->izq != NULL){
    TBinario aucs = b;
    b = b->izq;
    delete aucs;
    }
    else if (b->izq == NULL && b->der != NULL){
    TBinario aucs = b;
    b = b->der;
    delete aucs;
    }
  }
else if (elem < natInfo(b->dato)) removerDeBinario(elem,b->izq);
else removerDeBinario(elem,b->der);
}
return b;
}
/*
  Libera la memoria asociada a 'b' y todos sus elementos.
  El tiempo de ejecución es O(n), siendo 'n' es la cantidad de elementos de 'b'.
 */
void liberarBinario(TBinario b){//LISTO
  if(b != NULL){
  liberarBinario(b->der);
  liberarBinario(b->izq);
  delete b;
  b = NULL;
  }
}

/*
  Devuelve 'true' si y solo si 'b' es vacío (no tiene elementos).
  El tiempo de ejecución es O(1).
 */
bool esVacioBinario(TBinario b){return b == NULL;}//LISTO

/*
  Devuelve 'true' si y solo si cada nodo de 'b' cumple la condición de balanceo
  AVL. El árbol vacío cumple la condición.
  Un nodo cumple la condición de balanceo AVL si el valor absoluto de la
  diferencia de las alturas de sus subárboles izquierdo y derecho en menor o
  igual a 1.
  Cada nodo se puede visitar una sola vez.
  El tiempo de ejecución es O(n), siendo 'n' la cantidad de elementos de 'b'.
 */
bool esAvl(TBinario b){
  
  if(!esVacioBinario(b)){
    bool ret;
    if((izquierdo(b) != NULL)&&(derecho(b)==NULL)){
      if(izquierdo(izquierdo(b)) != NULL || derecho(izquierdo(b))!= NULL){ret = false;}
      else                                                               {ret = true;}
    }
    else
    if((izquierdo(b) == NULL)&&(derecho(b)!=NULL)){
      if(derecho(derecho(b)) != NULL || izquierdo(izquierdo(b))!= NULL){ret = false;}
      else                                                             {ret = true;}
    }
    else{
      ret = esAvl(izquierdo(b)) && esAvl(derecho(b));
    }
    return ret;
  }
  else return true;
}

/*
  Devuelve el elemento asociado a la raíz de 'b'.
  Precondición: ! esVacioBinario(b).
  El tiempo de ejecución es O(1).
 */
TInfo raiz(TBinario b){
  if(!esVacioBinario(b)){
  return b->dato;}
  else return NULL;
}
/*
  Devuelve el subárbol izquierdo de 'b'.
  Precondición: ! esVacioBinario(b).
  El tiempo de ejecución es O(1).
 */
TBinario izquierdo(TBinario b){return b->izq;}//LISTO

/*
  Devuelve el subárbol derecho de 'b'.
  Precondición: ! esVacioBinario(b).
  El tiempo de ejecución es O(1).
 */
TBinario derecho(TBinario b){return b->der;}//LISTO

/*
  Devuelve el subárbol que tiene como raíz al nodo con el elemento cuyo
  componente natural es 'elem'.
  Si 'elem' no pertenece a 'b', devuelve el árbol vacío.
  El tiempo de ejecución es O(log n) en promedio, siendo 'n' la cantidad de
  elementos de 'b'.
 */
TBinario buscarSubarbol(nat elem, TBinario b){//LISTO
  if(!esVacioBinario(b)){
    if(elem == natInfo(b->dato)){
      return b;
    }
    else if(elem>natInfo(b->dato)){
      return buscarSubarbol(elem, izquierdo(b));
    }
    else{
      return buscarSubarbol(elem, derecho(b));
    }
  }
  else return NULL;
}


/*
  Devuelve la altura de 'b'.
  La altura de un árbol vacío es 0.
  El tiempo de ejecución es O(n), siendo 'n' la cantidad de elementos de 'b'.
 */
nat max(nat a ,nat b){//LISTO
if(a > b) return a;
else      return b;
}
nat alturaBinario(TBinario b){//LISTO
  
if(b == NULL) return 0;
  else{
  return 1 + max(alturaBinario(b->izq), alturaBinario(b->der));
  }
}


/*
  Devuelve la cantidad de elementos de 'b'.
  El tiempo de ejecución es O(n), siendo 'n' la cantidad de elementos de 'b'.
 */
nat cantidadBinario(TBinario b){//LISTO
  if(esVacioBinario(b)) return 0;
  else{
    nat cant = 0;
    cant = 1 + cantidadBinario(b->der) + cantidadBinario(b->izq);
    return cant;
  }
}


/*
  Devuelve la suma de los componentes reales de los últimos 'i' elementos
  (considerados según la propiedad de orden de los árboles TBinario)
  de 'b' cuyos componentes reales sean mayores que 0.
  Si en 'b' hay menos de 'i' elementos que cumplan esa condición devuelve la
  suma de los componenetes reales de ellos.
  No se deben crear estructuras auxiliares.
  No se deben visitar nuevos nodos después que se hayan encontrado los
  'i' elementos.
  El tiempo de ejecución es O(n), siendo 'n' la cantidad de elementos de 'b'.
 */
double sumaUltimosPositivos(nat i, TBinario b){
  return 0;
} //ultimo

/*
  Devuelve una 'TCadena' con los elementos de 'b' en orden creciente según
  sus componentes naturales.
  La 'TCadena' devuelta no comparte memoria con 'b'.
  El tiempo de ejecución es O(n), siendo 'n' la cantidad de elementos de 'b'.
 */
TCadena lineaux(TCadena cad, TBinario b){//LISTO
  if (!esVacioBinario(b)){
    lineaux(cad, b->izq);//llegar al mayor
    TInfo dato = copiaInfo(b->dato);
    insertarAlFinal(dato, cad);//insertar de mayor a menor de izq
    lineaux(cad, b->der);
    return cad;
  }
  else return NULL;
}
TCadena linealizacion(TBinario b){//LISTO
  if(!esVacioBinario(b)){
  TCadena cad = crearCadena();
  lineaux(cad, b);
    return cad;
  }
  else return NULL;
}

/*
  Devuelve un árbol con copias de los elementos de 'b' que cumplen la condición
  "realInfo(elemento) < cota".
  La estructura del árbol resultado debe ser análoga a la de 'b'. Esto
  significa que dados dos nodos 'U' y 'V' de 'b' en los que se cumple la
  condición y tal que 'U' es ancestro de 'V', en el árbol resultado la copia de
  'U' debe ser ancestro de la copia de 'V' cuando sea posible. Esto no siempre
  se puede lograr y al mismo tiempo mantener la propiedad de orden del árbol
  en el caso en el que en un nodo 'V' no se cumple la condición y en sus dos
  subárboles hay nodos en los que se cumple. En este caso, la copia del nodo
  cuyo elemento es el mayor (según la propiedad de orden definida) de los que
  cumplen la condición en el subárbol izquierdo de 'V' deberá ser ancestro de
  las copias de todos los descendientes de 'V' que cumplen la condición.
  Ver ejemplos en la letra.
  El árbol resultado no comparte memoria con 'b'. *)
  El tiempo de ejecución es O(n), siendo 'n' es la cantidad de elementos de 'b'.
 */
TBinario menores(double cota, TBinario b){return NULL;} //ultimo

/*
  Imprime los elementos de 'b', uno por línea, en orden descendente de la
  propiedad de orden de los árboles 'TBinario'.
  Antes del elemento imprime una cantidad de guiones igual a su profundidad.
  El elemento se imprime según la especificación dada en 'infoATexto'.
  La profundidad de la raíz es 0.
  Antes del primer elemento, se debe imprimir un fin de linea.
  Si esVacioBinario(b) solo se imprime el fin de línea.
  El tiempo de ejecución es O(n . log n) en promedio, siendo 'n' la cantidad
  de elementos de 'b'.
 */
void imprimirBinario(TBinario b){}//FALTA

