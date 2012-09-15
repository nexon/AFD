#ifndef TRANSICION_H
#define TRANSICION_H
#include <string.h>
#include <iostream>
#include <cstdlib>
#include <qstring.h>


using namespace std;

class Transicion {
    protected:
        class Nodo {
            public:
                QString estado;
                QString simbolo;
                QString estadoLlegada;
                Nodo *siguiente;
           };
        Nodo *inicio;
        public:
                Transicion() {inicio = 0;}
                void inserta(QString estado, QString simbolo, QString estadoLlegada);
                void elimina(QString estado, QString simbolo);
                QString buscarTransicion(QString estado, QString simbolo);
                void eliminaTodo();
                QString transicionExiste(QString estado, QString simbolo);

  };

#endif // TRANSICION_H
