#include "afd.h"
#include <iostream>
#include <QDebug>

/**
 * AFD
 *
 * Clase que implementa las funcionalidades basicas para el automata pushdown.
 *
 * @author Jose Rodríguez A.
 * @author Alberto Lagos T.
 */


/**
 * Constructor de clase
 *
 * @author Jose Rodríguez A.
 * @author Alberto Lagos T.
 * @param QString
 * @param QString
 */
afd::afd(QString estadoInicial, QString estadoFinal) {
    this->estadoInicial = estadoInicial;
    this->estadoFinal = estadoFinal;
    this->estadoTransitorio = "0";
    this->transiciones = new Transicion();
}

/**
 * Metodo que agrega una transicion a la lista enlazada.
 *
 * @author Jose Rodríguez A.
 * @author Alberto Lagos T.
 * @param QString
 * @param QString
 * @param QString
 */
void afd::agregarTransicion(QString estado, QString simbolo, QString estadoLlegada) {
    this->transiciones->inserta(estado, simbolo, estadoLlegada);
}

/**
 * Metodo que devuelve el atributo transicion (getter)
 *
 * @author Jose Rodríguez A.
 * @author Alberto Lagos T.
 */
Transicion *afd::transicion() {
    return this->transiciones;
}

/**
 * Metodo que que modifica el estado inicial
 *
 * @author Jose Rodríguez A.
 * @author Alberto Lagos T.
 */
void afd::modificarEstadoInicial(QString estadoInicial) {
    this->estadoInicial = estadoInicial;
}

/**
 * Metodo que obtiene el estado inicial (getter)
 *
 * @author Jose Rodríguez A.
 * @author Alberto Lagos T.
 */
QString afd::obtenerEstadoInicial() {
    return this->estadoInicial;
}

/**
 * Metodo que obtiene el estado final (getter)
 *
 * @author Jose Rodríguez A.
 * @author Alberto Lagos T.
 */
QString afd::obtenerEstadoFinal() {
    return this->estadoFinal;
}

/**
 * Metodo que modifica el estado transitorio (setter)
 *
 * @author Jose Rodríguez A.
 * @author Alberto Lagos T.
 */
void afd::modificarEstadoTransitorio(QString estado) {
    this->estadoTransitorio = estado;
}

/**
 * Metodo que obtiene el estado Transitorio (getter)
 *
 * @author Jose Rodríguez A.
 * @author Alberto Lagos T.
 */
QString afd::obtenerEstadoTransitorio() {
    return this->estadoTransitorio;
}

/**
 * Metodo que modifica el estado final (setter)
 *
 * @author Jose Rodríguez A.
 * @author Alberto Lagos T.
 */
void afd::modificarEstadoFinal(QString estadoFinal) {
    this->estadoFinal = estadoFinal;
}

/**
 * Metodo que ejecuta el automata ingresado para validar la palabra dada.
 *
 * @author Jose Rodríguez A.
 * @author Alberto Lagos T.
 */
bool afd::obtenerSolucion() {
    QString palabrota = this->obtenerPalabra();
    int z = 0;
    bool flag = true;
    while(z<palabrota.length() && flag) {
        Transicion *p = this->transicion();
        QString ret = p->buscarTransicion(this->obtenerEstadoTransitorio(), palabrota.at(z));
        if(ret != "0") {
            this->modificarEstadoTransitorio(ret);
        } else {
            flag = false;
        }
        z++;
    }   
}

/**
 * Metodo que obtiene el alfabeto (getter)
 *
 * @author Jose Rodríguez A.
 * @author Alberto Lagos T.
 */

QStringList* afd::obtenerAlfabeto() {
    return this->alfabeto;
}

/**
 * Metodo que modifica el alfabeto (setter)
 *
 * @author Jose Rodríguez A.
 * @author Alberto Lagos T.
 */

void afd::modificarAlfabeto(QStringList *a) {
    this->alfabeto = a;
}

/**
 * Metodo que obtiene la Palabra (getter)
 *
 * @author Jose Rodríguez A.
 * @author Alberto Lagos T.
 */

QString afd::obtenerPalabra() {
    return this->palabra;
}

/**
 * Metodo que modifica la palabra
 *
 * @author Jose Rodríguez A.
 * @author Alberto Lagos T.
 */

void afd::modificarPalabra(QString p) {
    this->palabra = p;
}
