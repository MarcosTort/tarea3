#include "../include/usoTads.h"
#include "../include/cadena.h"
#include "../include/info.h"
#include "../include/utils.h"

#include <stddef.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
/*
  Devuelve 'true' si y solo si en 'cad' hay un elemento cuyo campo natural es
  'elem'.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos de 'cad'.
 */
void rellenarCadena(nat l,TCadena &c, TBinario b){
  if(!esVacioBinario(b)){
    if(l == alturaBinario(b)){ 
    insertarAlFinal(copiaInfo(raiz(b)), c);
    }
    else{
      rellenarCadena(l, c, derecho(b));
      rellenarCadena(l, c, izquierdo(b));
    }
  }
}
TCadena nivelEnBinario(nat l, TBinario b){
  TCadena ret = crearCadena();
  rellenarCadena(l, ret, b);
  ordenar(ret);
  return ret;
}
bool esCamino(TCadena c, TBinario b){return false;}

bool pertenece(nat elem, TCadena cad){
  TLocalizador rec = inicioCadena(cad);
  if(!esVaciaCadena(cad)){
  while((!esFinalCadena(rec, cad)) && (natInfo(infoCadena(rec, cad)) != elem)){
    rec = siguiente(rec, cad);
  }
  return natInfo(infoCadena(rec, cad)) == elem;
  }
  else{return false;}
}
/*
  Devuelve la cantidad de elementos de 'cad'.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos de 'cad'.
 */
nat longitud(TCadena cad){
  if(esVaciaCadena(cad)){
    return 0;
  }
  else{
  nat contador = 1;
  TLocalizador rec = inicioCadena(cad);
  while(!esFinalCadena(rec, cad)){
    rec = siguiente(rec, cad);
    contador ++;
  }
  return contador;
  }
}

/*
  Devuelve 'true' si y solo si 'cad' está ordenada de forma no dereciente
  (creciente de manera no estricta) según las campos naturales de sus elementos.
  Si esVaciaVadena(cad) devuelve 'true'.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos de 'cad'.
 */
bool estaOrdenadaPorNaturales(TCadena cad){
  TLocalizador ctr = inicioCadena(cad);
  if(esVaciaCadena(cad) || esFinalCadena(ctr, cad) ){
    return true;
  }
  else{
    bool ordenado = true;
    while(!esFinalCadena(ctr, cad) && ordenado){
      ordenado = natInfo(infoCadena(ctr, cad)) <= natInfo(infoCadena(siguiente(ctr, cad), cad));
      ctr = siguiente(ctr, cad);
    }
    return ordenado;
  }
}
/*
  Devuelve 'true' si y solo si los componentes naturales de algún par de
  elementos de 'cad' son iguales.
  El tiempo de ejecución en el peor caso es O(n^2), siendo 'n' la cantidad de
  elementos de 'cad'.
 */
 bool hayNatsRepetidos(TCadena cad){
  nat contador = 0;
  nat control;
  TLocalizador rec = inicioCadena(cad);
  TLocalizador rec2;
    if(esVaciaCadena(cad) || esFinalCadena(rec, cad) ){   //descarto cadena vacia o cadena con un elemento
      return false;
    }
    else{
    while((esLocalizador(rec)) && (contador < 1)){
      rec2 = siguiente(rec, cad);
      control = natInfo(infoCadena(rec, cad));
      while((esLocalizador(rec2)) && (contador < 1)){
        if (natInfo(infoCadena(rec2, cad)) == control){
          contador ++;
        }
        else
          rec2 = siguiente(rec2, cad);
      }
      rec = siguiente(rec, cad);
    }
    return contador == 1;
  }
}
/*
  Devuelve 'true' si y solo si 'c1' y 'c2' son iguales (es decir, si los
  elementos son iguales y en el mismo orden).
  Si esVaciaCadena(c1) y esVaciaCadena(c2) devuelve 'true'.
  El tiempo de ejecución en el peor caso es O(n1 + n2), siendo 'n1' u 'n2' la
  cantidad de elementos de 'c1' y 'c2' respectivamente.
 */
bool sonIgualesCadena(TCadena c1, TCadena c2){
  if(esVaciaCadena(c1) && esVaciaCadena(c2)){
    return true;}
    else{
      if(longitud(c1) != longitud(c2)){return false;}
      else{
        bool compar = true;
        TLocalizador l1 = inicioCadena(c1);
        TLocalizador l2 = inicioCadena(c2);
        compar = sonIgualesInfo(infoCadena(l1, c1), infoCadena(l2, c2));
        while(esLocalizador(l1) && compar){
          compar = sonIgualesInfo(infoCadena(l1, c1), infoCadena(l2, c2));
          l1 = siguiente(l1, c1);
          l2 = siguiente(l2, c2);
        }
        return compar;
      }
  }
}

/*
  Devuelve el resultado de concatenar 'c2' después de 'c1'.
  La 'TCadena' resultado no comparte memoria ni con 'c1' ni con 'c2'.
  El tiempo de ejecución en el peor caso es O(n1 + n2), siendo 'n1' u 'n2' la
  cantidad de elementos de 'c1' y 'c2' respectivamente.
 */
TCadena concatenar(TCadena c1, TCadena c2) {
	TCadena sgm = copiarSegmento(inicioCadena(c1), finalCadena(c1), c1);
  TCadena sgm2 = copiarSegmento(inicioCadena(c2), finalCadena(c2), c2);
	if(sgm == NULL)return sgm2;
  else if(sgm2 == NULL)
    return sgm; 
  else{
   insertarSegmentoDespues(sgm2, finalCadena(sgm), sgm);
  }
return sgm;
}

/*
  Se ordena 'cad' de manera creciente según los componentes naturales de sus
  elementos.
  Devuelve 'cad'
  Precondición: ! hayNatsRepetidos(cad)
  No se debe obtener ni devolver memoria de manera dinámica.
  Se debe mantener las relaciones de precedencia entre localizadores.
  Si esVaciaCadena(cad) no hace nada.
  El tiempo de ejecución en el peor caso es O(n^2), siendo 'n' la cantidad de
  elementos de 'cad'.
 */
TCadena ordenar(TCadena cad){
  if (longitud(cad) > 1){
    TLocalizador rec = inicioCadena(cad);
    while (esLocalizador(siguiente(rec, cad)))
    {
      TLocalizador aux = siguiente(rec, cad);
      while (esLocalizador(aux))
      {
        if(natInfo(infoCadena(rec, cad))>natInfo(infoCadena(aux, cad)))
          intercambiar(aux, rec, cad);
        aux = siguiente(aux, cad);
      }
      rec = siguiente(rec, cad);
    }
  }
  return cad;
}
/*
  Cambia todas las ocurrencias de 'original' por 'nuevo' en los elementos
  de 'cad'.
  Devuelve 'cad'
  No debe quedar memoria inaccesible.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos de 'cad'.
 */
TCadena cambiarTodos(nat original, nat nuevo, TCadena cad){
  if(!esVaciaCadena(cad)){
   double real;
   TInfo info;
   TInfo info_lib;
   TLocalizador loc = inicioCadena(cad);
   TLocalizador remov;
    while(esLocalizador(loc)){
      if(natInfo(infoCadena(loc, cad)) == original ){
         real = realInfo(infoCadena(loc, cad));
         info = crearInfo(nuevo, real);
         info_lib = copiaInfo(infoCadena(loc, cad));
         insertarAntes(info, loc, cad);
         remov = loc;
         loc = siguiente(loc, cad);
         removerDeCadena(remov, cad);
         liberarInfo(info_lib);
      }else{ loc = siguiente(loc, cad);
      }
    }
  }
  return cad;
}
/*
  Devuelve la 'TCadena' de elementos de 'cad' que cumplen
  "menor <= natInfo (elemento) <= mayor".
  El orden relativo de los elementos en la 'TCadena' resultado debe ser el mismo
  que en 'cad'.
  Precondición: estaOrdenadaPorNaturales (cad), 'menor' <= 'mayor',
  pertenece (menor, cad), pertenece (mayor, cad).
  La 'TCadena' resultado no comparte memoria con 'cad'.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos de 'cad'.
 */
TCadena subCadena(nat menor, nat mayor, TCadena cad){
  TCadena sub = crearCadena();
  TLocalizador rec = inicioCadena(cad);
  TLocalizador inicioSub = NULL;
  TLocalizador finalSub = NULL;
  
  while(esLocalizador(rec)){
    if(natInfo(infoCadena(rec, cad))<= mayor) 
      finalSub = rec;

    if ((natInfo(infoCadena(rec, cad)) >= menor) && (inicioSub == NULL)) 
      inicioSub = rec;

    rec = siguiente(rec, cad);
    }
  insertarSegmentoDespues(copiarSegmento(inicioSub, finalSub, cad ), finalCadena(sub), sub);
return sub;
}
