#include "../include/cadena.h"
#include "../include/info.h"
#include "../include/utils.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct nodoCadena {
  TInfo dato;
  TLocalizador anterior;
  TLocalizador siguiente;
};

struct _rep_cadena {
  TLocalizador inicio;
  TLocalizador final;
};

bool esLocalizador(TLocalizador loc) { return loc != NULL; }

TCadena crearCadena() {
  TCadena res = new _rep_cadena;
  res->inicio = res->final = NULL;
  return res;
}

void liberarCadena(TCadena cad) {
  if(!esVaciaCadena(cad)){
    nodoCadena *prox_a_borrar;
    while(cad->inicio != NULL)
    {
        prox_a_borrar = cad->inicio;
        cad->inicio = cad->inicio->siguiente;
        liberarInfo(prox_a_borrar->dato);
        delete(prox_a_borrar);
    }
  }
  delete cad;
}

bool esVaciaCadena(TCadena cad) {
    return cad->inicio == NULL;
}

TLocalizador inicioCadena(TCadena cad) {
    if (esVaciaCadena(cad)) {
      return NULL;
    } else {
      return cad->inicio;
    }
}

TLocalizador finalCadena(TCadena cad) {
    if (esVaciaCadena(cad)) {
      return NULL;
    } else {
      return cad->final;
    }
}

TInfo infoCadena(TLocalizador loc, TCadena cad) {
  if (localizadorEnCadena(loc, cad)){
    return loc->dato;
  }
  else{return NULL;}
}

TLocalizador siguiente(TLocalizador loc, TCadena cad) {
    assert(localizadorEnCadena(loc, cad));
    if (finalCadena(cad) != loc){
    
    TLocalizador aux = loc->siguiente;
    return aux;
  }
  else{return NULL;}
}

TLocalizador anterior(TLocalizador loc, TCadena cad) {
  assert(localizadorEnCadena(loc, cad));
  if (inicioCadena(cad) != loc){
    TLocalizador aux = loc->anterior;
    return aux;
  }
  else{return NULL;}
}
bool esFinalCadena(TLocalizador loc, TCadena cad) {
  if(esVaciaCadena(cad)){
    return false;
  }
  else{
    if (cad->final == loc){
      return true;
    }
    else{
      return false;
    }
  }
}

bool esInicioCadena(TLocalizador loc, TCadena cad) {
  if(esVaciaCadena(cad)){
    return false;
  }
  else{
    if (cad->inicio == loc){
      return true;
    }
    else{
      return false;
    }
  }
}

TCadena insertarAlFinal(TInfo i, TCadena cad) {
  nodoCadena *entrante = new nodoCadena;
  entrante->siguiente = NULL;
  entrante->anterior = cad->final;
  entrante->dato = i;
  if(!esVaciaCadena(cad)){
	  cad->final->siguiente = entrante;
  }
  else{
	  cad->inicio = entrante;
  }
  cad->final = entrante;
  return cad;
}

TCadena insertarAntes(TInfo i, TLocalizador loc, TCadena cad) {
  if (localizadorEnCadena(loc, cad)){
	  nodoCadena *entrante = new nodoCadena;
	  entrante->dato = i;
	  if(!esInicioCadena(loc, cad)){
	    entrante->siguiente = loc;
	    entrante->anterior = loc->anterior;
	    loc->anterior->siguiente = entrante;
	    loc->anterior = entrante;
	  }
	  else{
	    entrante->siguiente = loc;
	    loc->anterior = entrante; 
	    cad->inicio = entrante;
	    entrante->anterior = NULL;
	  }
  }
  return cad;
}

TCadena removerDeCadena(TLocalizador loc, TCadena cad) {
  TLocalizador aux = loc;
  if (!esVaciaCadena(cad)){
    if (esInicioCadena(loc, cad)){
      //inicio
      if (esLocalizador(loc->siguiente)){
        cad->inicio = aux->siguiente; 
        aux->siguiente->anterior = NULL; 
        liberarInfo(loc->dato);
        delete loc;
      } else {
        cad->inicio = NULL;
        cad->final = NULL;
        liberarInfo(loc->dato);
        delete loc;
      }

    } else {
      if (!esFinalCadena(loc, cad)){
        //medio 
        aux->anterior->siguiente = aux->siguiente;
        aux->siguiente->anterior = aux->anterior;
        liberarInfo(loc->dato);
        delete loc;
      } else {
        //final 
        cad->final = aux->anterior;
        aux->anterior->siguiente = NULL;
        liberarInfo(loc->dato);
        delete loc;
      }
    }		
  }
	return cad;
}

void imprimirCadena(TCadena cad) {
  TLocalizador l = cad->inicio;
      while (esLocalizador(l)){
        char *dat = infoATexto(l->dato);
        printf("%s", dat);
       	delete[] dat;
        l = l->siguiente;
      }//end while
printf("\n"); 
}
TLocalizador kesimo(nat k, TCadena cad) {
  TLocalizador reco = cad->inicio;
  nat j = 1;
  if (k>0){
	  
    while((reco != NULL )&& (j < k)){
      reco = reco->siguiente;
      j++;
    }
    if (reco == NULL|| k > j){
      return NULL;
    }
    else{
      if ((j == k )&& (reco != NULL)){
        return reco;
      }
      else{
        return NULL;
      }
    }
  }
  else{return NULL;}
}

TCadena insertarSegmentoDespues(TCadena sgm, TLocalizador loc, TCadena cad) {
  if(!esVaciaCadena(cad)){                    
    if(!esVaciaCadena(sgm)){                  
      if(finalCadena(cad) != loc){
          sgm->inicio->anterior = loc;
          sgm->final->siguiente = loc->siguiente;
          loc->siguiente->anterior = sgm->final;
          loc->siguiente = sgm->inicio;
      }else{
          sgm->inicio->anterior = loc;
          sgm->final->siguiente = loc->siguiente;
          cad->final = sgm->final;
          loc->siguiente = sgm->inicio;
      }
    }
    else{ delete sgm; return cad;}
  }else{
       cad->inicio = sgm->inicio; 
       cad->final = sgm->final;
  }
  delete sgm;
  return cad;
}


TCadena copiarSegmento(TLocalizador desde, TLocalizador hasta, TCadena cad) {
  assert(esVaciaCadena(cad)||precedeEnCadena(desde, hasta, cad));
  TCadena copia = crearCadena();
  if(!esVaciaCadena(cad))
  {
    TLocalizador loc = desde;
    while(loc != siguiente(hasta, cad)){
      TInfo dato;
      dato = copiaInfo((loc->dato));//no comparte memoria con cad
      insertarAlFinal(dato, copia);
      loc = siguiente(loc, cad);
    }
  }
  return copia;
}

TCadena borrarSegmento(TLocalizador desde, TLocalizador hasta, TCadena cad) {
  TLocalizador eliminado;
  while (hasta != desde){
    eliminado = desde;
    desde = desde->siguiente;
    removerDeCadena(eliminado, cad);
  }
  removerDeCadena(hasta, cad);
  return cad;
}

TCadena cambiarEnCadena(TInfo i, TLocalizador loc, TCadena cad) {
  assert(localizadorEnCadena);
  loc->dato = i;
  return cad;
}

TCadena intercambiar(TLocalizador loc1, TLocalizador loc2, TCadena cad) {
  assert(localizadorEnCadena(loc1, cad)&&localizadorEnCadena(loc1, cad));
  TInfo mem = infoCadena(loc1, cad);
  loc1->dato = infoCadena(loc2, cad);
  loc2->dato = mem;
  return cad;
}

bool localizadorEnCadena(TLocalizador loc, TCadena cad) {
  if(esVaciaCadena(cad)){
    return false;
  }
  else{
    TLocalizador aux = cad->inicio;
    bool flag = false;
    if (esFinalCadena(loc, cad) || esInicioCadena(loc, cad)) {				
	flag = true;
    } 
    while ( !flag && esLocalizador(aux)){
      if(aux != loc)
        aux = aux->siguiente;
      else
        flag = aux == loc;
    }
    return flag;
  }
}
bool precedeEnCadena(TLocalizador loc1, TLocalizador loc2, TCadena cad) {
  
    TLocalizador precursor = loc1;
    bool esPrecursor = false;
    if( loc1 != loc2){
      while((!esPrecursor) && esLocalizador(precursor)){
        if(precursor == loc2)
          esPrecursor=true;
        else
          precursor = precursor->siguiente;
      }
    return esPrecursor;
    }
    else{return true;}
}

TLocalizador siguienteClave(nat clave, TLocalizador loc, TCadena cad) {
  assert(localizadorEnCadena(loc, cad));

  if(esVaciaCadena(cad)){return NULL;}
  else{
    TLocalizador rec = loc;
    while(esLocalizador(rec) && (natInfo(rec->dato) != clave)){
      rec = rec->siguiente;
    }
    return rec;
 }
}

TLocalizador anteriorClave(nat clave, TLocalizador loc, TCadena cad) {
  assert(localizadorEnCadena(loc, cad));

  if(esVaciaCadena(cad)){return NULL;}
  else{
    TLocalizador rec = loc;
    while(esLocalizador(rec) && (natInfo(rec->dato) != clave)){
      rec = rec->anterior;
    }
    return rec;
  }
}

TLocalizador menorEnCadena(TLocalizador loc, TCadena cad) {
  assert(localizadorEnCadena(loc, cad));
  TLocalizador res = loc;
	while (esLocalizador(siguiente(loc, cad))) {
	 loc = siguiente(loc, cad);
	 if (natInfo(infoCadena(loc, cad)) < natInfo(infoCadena(res, cad)))
	  res = loc;
	 }
	return res;
	}