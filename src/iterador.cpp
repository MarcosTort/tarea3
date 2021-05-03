/*
  Módulo de definición de 'TIterador'.

  Los elementos de tipo 'TIterador' son estructuras para recorrer colecciones
  de elementos de tipo 'nat'.
  Tiene implcícita una posición actual.
  La posición no está definida si la colección es vacía o si se avanza cuando
  la posición es la última.

  La vida de un 'TIterador' tiene dos fases: en la primera se le puede agregar
  elementos pero no se puede recorrer; luego de que se reinicia se puede
  recorrer tantas veces como sea pero no se puede agregar elementos.

  Seudocódigo de una recorrida de un iterador:
  reiniciar
  mientras la posición actual está definida
    procesar el elemento definido por la posición actual
    avanzar

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#include "../include/utils.h"
#include "../include/iterador.h"
#include "../include/info.h"
#include <assert.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

// Representación de 'TIterador',
// Se debe definir en iterador.cpp
// struct _rep_iterador;
// Declaración del tipo 'TIterador'
//typedef struct _rep_iterador *TIterador;
struct nodoIt{
    nat num;
    nodoIt *sig;
};
struct _rep_iterador{
    nodoIt *inicio, *fin, *actual;
    bool bloqueado;
};

/*
  Crea un 'TIterador' vacío (sin elementos) cuya posición actual no está
  definida.
  Se le puede agregar elementos.
  El tiempo de ejecución en el peor caso es O(1).
 */
TIterador crearIterador(){
    TIterador i = new _rep_iterador;
    i->bloqueado = false;
    i->actual = i->inicio = i->fin = NULL;
    return i;
};

/*
  Agrega 'elem' al final de 'iter' si y solo si nunca se reinicio.
  Devuelve 'iter'.
  La posición actual sigue indefinida.
  El tiempo de ejecución en el peor caso es O(1).
 */
TIterador agregarAIterador(nat elem, TIterador iter){
    
    if(!iter->bloqueado){
      nodoIt *l = new nodoIt;
      l->num = elem;
      l->sig = NULL;
      if (iter->fin!= NULL) iter->fin->sig = l;
      else iter->inicio = l;
      iter->fin = l;
  }
  return iter;
}

/*
  Mueve la posición actual de 'iter' al primero si y solo si 'iter' tiene
  elementos.
  Devuelve 'iter'.
  No se podrán agregar más elementos (aunque no hubiera ninguno).
  El tiempo de ejecución en el peor caso es O(1).
 */
TIterador reiniciarIterador(TIterador iter){
  if ((iter != NULL) && (iter->inicio->sig != NULL))
  {iter->actual = iter->inicio;} 
   return iter; 
};

/*
  Avanza la posición actual de 'iter' hacia el siguiente si y solo si'
  estaDefinidaActual(iter).
  Devuelve 'iter'.
  Si la posición actual es la última posición entonces la posición actual
  queda indefinida.
  El tiempo de ejecución en el peor caso es O(1).
 */
TIterador avanzarIterador(TIterador iter){
  if(estaDefinidaActual(iter))
    iter->actual = iter->actual->sig;  
  return iter;
};

/*
  Devuelve el elemento de la posición actual de 'iter'.
  Precondición: estaDefinidaActual(iter).
  El tiempo de ejecución en el peor caso es O(1).
 */
nat actualEnIterador(TIterador iter){
  assert (estaDefinidaActual(iter));
    return iter->actual->num;
};

/*
  Devuelve 'true' si y solo si la posición actual de 'iter' está definida.
  El tiempo de ejecución en el peor caso es O(1).
 */
bool estaDefinidaActual(TIterador iter){
  return iter->actual != NULL;
};


/*
  Libera la memoria asignada a 'iter'.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad
  de elementos de 'iter'.
 */
void liberarIterador(TIterador iter){
  iter->actual = iter->inicio;
    while (estaDefinidaActual(iter)){
      nodoIt *a = iter->inicio;
      avanzarIterador(iter);
      delete a;
    }
    delete iter;
  }
