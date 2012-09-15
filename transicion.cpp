#include "transicion.h"
#include <string.h>
#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <QString.h>

/**
 * Transicion
 *
 * Clase que implementa las transiciones en una lista enlazada (Estructura de datos).
 *
 * @author Jose Rodríguez A.
 * @author Alberto Lagos T.
 */

/**
 * Metodo que inserta en la lista enlazada un nodo.
 *
 * @author Jose Rodríguez A.
 * @author Alberto Lagos T.
 */
void Transicion::inserta(QString estado, QString simbolo, QString estadoLlegada){
    Nodo *nuevo = new Nodo();
    nuevo->estado=estado;
    nuevo->simbolo=simbolo;
    nuevo->estadoLlegada = estadoLlegada;
    nuevo->siguiente=0;
    if (inicio ==0){//no existe la lista aun
       inicio = nuevo;
   }else{//hay mas de un elemento en la lista
         Nodo* aux=inicio;
         while(aux!=0 && aux->estado< nuevo->estado){//aux se mueve en la lista buscando un lugar de acuerdo al estado
                      aux=aux->siguiente;
         }
         if(aux!=0 && aux->estado==nuevo->estado){ //los estados son iguales
                   /*se movera en la lista de acuerdo a la letra, para insertar ordenadamente*/
                  while(aux->siguiente!=0 && (aux->siguiente)->estado==nuevo->estado && aux->simbolo <= nuevo->simbolo){
                              aux=aux->siguiente;
                  }
                  Nodo* aux1 =inicio;
               if(aux1!=aux){//no estamos al inicio de la lista
                   while(aux1!=0 && aux1->siguiente != aux){
                                 aux1=aux1->siguiente;
                   }//encuentra posible posicion
                   if(nuevo->simbolo < aux->simbolo){ //verifica letra
                                   nuevo->siguiente=aux;
                                   aux1->siguiente=nuevo;
                   }else{//aux->siguiente apunta donde debe ir "nuevo"
                         if(aux->siguiente==0){//al final de la lista
                                aux->siguiente=nuevo;
                         }else{//al medio de la lista
                             Nodo* p=(aux->siguiente);
                             aux->siguiente=nuevo;
                             nuevo->siguiente=p;
                         }
                   }
               }else{//estamos al inicio de la lista
                     if(nuevo->simbolo > aux->simbolo){//nuevo se agrega despus del 1er elemento de la lista
                          nuevo->siguiente=aux->siguiente;
                          aux->siguiente=nuevo;
                     }else{ //nuevo se agrega al inicio de la lista
                          nuevo->siguiente=aux;
                          inicio=nuevo;

                     }

               }

         }else{// los estados no son iguales
               Nodo* aux1 =inicio;
               while(aux1->siguiente!=0 && aux1->siguiente != aux){
                             aux1=aux1->siguiente;
               }
               nuevo->siguiente=aux;
               aux1->siguiente=nuevo;
         }
   }
}

/**
 * Metodo que elimina un nodo de la lista enlazada
 *
 * @author Jose Rodríguez A.
 * @author Alberto Lagos T.
 */
void Transicion::elimina(QString estado, QString simbolo){
    Nodo *prev = inicio;
    Nodo *aux = inicio->siguiente;
    while(aux!=0 && estado != prev->estado){
        prev=aux;
        aux = aux->siguiente;
    }
    if (aux!=0){//encontr estado
           while((prev->siguiente !=0)&&(prev->simbolo != simbolo)){
               prev=prev->siguiente;
           }
    }
    //final de la lista
     if(estado==prev->estado){//si coinciden los estados
           while((prev->siguiente !=0)&&(prev->simbolo != simbolo)){//busca letra
               prev=prev->siguiente;
            }
       }
if(prev==inicio){//se quiere eliminar el principio de la lista
    Nodo* p =prev;
    inicio = inicio->siguiente;
    delete p;
}else{
   Nodo* ant=inicio;
   while(ant!=0 && ant->siguiente!=prev){
         ant=ant->siguiente;
   }
   Nodo* p=prev;
   ant->siguiente = prev->siguiente;
   delete p;
}

}

/**
 * Metodo que elimina todos los nodos.
 *
 * @author Jose Rodríguez A.
 * @author Alberto Lagos T.
 */
void Transicion:: eliminaTodo(){
       while (inicio !=0){//mientras existan elementos
                Nodo *aux=inicio;
                if (aux->siguiente) //mas de un elemento en la cola
                    inicio = inicio->siguiente;
                else
                   inicio=0;
                delete aux;

       }
}

/**
 * Metodo que busca la transicion pedida (entregado previamente el estado-simbolo)
 *
 * @author Jose Rodríguez A.
 * @author Alberto Lagos T.
 */
QString Transicion:: buscarTransicion(QString estado, QString simbolo){
     Nodo *prev = inicio;
     Nodo *aux = inicio->siguiente;
     while(aux!=0 && estado != prev->estado){
         prev=aux;
         aux = aux->siguiente;
     }
     if (aux!=0){
         /* estado encontrado */
         while(prev->siguiente!=0 && prev->simbolo != simbolo) {
             prev = prev->siguiente;
         }
     } else {
         if(prev->estado == estado && prev->simbolo == simbolo) {
             return prev->estadoLlegada;
         } else {
             return "0";
         }
     }
     if(prev!=0) {
         if(prev->estado == estado && prev->simbolo == simbolo) {
             return prev->estadoLlegada;
         } else {
             return "0";
         }
     }

}

/**
 * Metodo que determina si una transicion existe (entregado previamente el estado-simbolo)
 *
 * @author Jose Rodríguez A.
 * @author Alberto Lagos T.
 */
QString Transicion:: transicionExiste(QString estado, QString simbolo){
     Nodo *prev = inicio;
     Nodo *aux = inicio->siguiente;
     bool flag = false;
     while(aux!=0 && !flag ){
         if(prev->estado == estado && prev->simbolo == simbolo) {
                flag = false;
         }
         prev=aux;
         aux = aux->siguiente;
     }
     if(flag) {
         return "SI";
     } else {
         return "NO";
     }
 }
