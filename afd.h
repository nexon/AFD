#ifndef AFD_H
#define AFD_H

#include <QObject>
#include "transicion.h"
#include "QMessageBox"
/**
 * Clase de Automata Finito Determinista
 *
 * @author Alberto Lagos T.
 */
class afd : public QObject {
    public:
        afd(QString estadoInicial, QString estadoFinal);
        void agregarTransicion(QString estado, QString simbolo, QString estadoLlegada);
        Transicion *transicion();
        void modificarEstadoInicial(QString estadoInicial);
        void modificarEstadoFinal(QString estadoFinal);
        void modificarEstadoTransitorio(QString estado);
        void modificarPalabra(QString p);
        void modificarAlfabeto(QStringList *a);
        bool obtenerSolucion();
        QStringList *obtenerAlfabeto();
        QString obtenerPalabra();
        QString obtenerEstadoTransitorio();
        QString obtenerEstadoInicial();
        QString obtenerEstadoFinal();
    private:
        QString estadoInicial;
        QString estadoFinal;
        QString estadoTransitorio;
        QStringList *alfabeto;
        QString palabra;
        Transicion *transiciones;

};

#endif // AFD_H
