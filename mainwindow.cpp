#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include "afd.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tablaDeTransiciones->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tablaDeTransiciones->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->verificarPalabra->setEnabled(false);
    automata = 0;
}
/**
 * Destructor de la clase.
 *
 * @author Jose Rodríguez A.
 * @author Alberto Lagos T.
 */
MainWindow::~MainWindow() {
    delete ui;
}

/**
 * Metodo agrega la transicion a la lista de la interfaz grafica.
 *
 * @author Jose Rodríguez A.
 * @author Alberto Lagos T.
 */
void MainWindow::on_agregarTransicion_clicked() {
    int row = ui->tablaDeTransiciones->rowCount();
        //hacer validacion
    if(ui->estado->text() == "" || ui->simbolo->text() == "" || ui->estadoLlegada->text() == "") {
        QMessageBox::warning(this, "Error Ingresando Datos", "Ingresa los datos necesarios para la transición");
    } else {
        if(ui->estado->text().at(0) == 'q' && ui->estado->text().at(1).isDigit()) {
            if(ui->simbolo->text().length() == 1 ) {
                    ui->tablaDeTransiciones->insertRow(row);
                    /* Haciendo valido el estado ingresado */
                    QString estado1 = ui->estado->text();
                    QString s = ui->simbolo->text();
                    QTableWidgetItem *ladoIzquierdo = new QTableWidgetItem("("+estado1+","+s+")",0);
                    QTableWidgetItem *ladoDerecho = new QTableWidgetItem(ui->estadoLlegada->text(),0);

                    ui->tablaDeTransiciones->setItem(row,0,ladoIzquierdo);
                    ui->tablaDeTransiciones->setItem(row,1,ladoDerecho);

                    //Preguntamos si el objeto AFD esta creado;
                    if(automata != 0) {
                        automata->agregarTransicion(ui->estado->text(), ui->simbolo->text(), ui->estadoLlegada->text());
                    } else {
                        automata = new afd(ui->estadoInicial->text(), ui->estadoFinal->text());
                        automata->agregarTransicion(ui->estado->text(), ui->simbolo->text(), ui->estadoLlegada->text());
                    }
                    //Limpiando los QLineEdit
                    ui->estado->setText("");
                    ui->simbolo->setText("");
                    ui->estadoLlegada->setText("");
                    ui->estado->setFocus();
            } else {
                QMessageBox::warning(this, "Error", "Solo una letra por transicion es permitida.");
                ui->simbolo->setFocus();
            }
        } else {
            QMessageBox::warning(this, "Error", "El estado DEBE comenzar con q");
            ui->estado->setFocus();
        }

    }
    ui->verificarPalabra->setEnabled(true);
}

/**
 * Metodo que elimina una transicion seleccionada de la lista.
 *
 * @author Jose Rodríguez A.
 * @author Alberto Lagos T.
 */
void MainWindow::on_eliminarTransicion_clicked() {
    //Buscamos la transicion y la eliminamos del automata.
    if(ui->estado->text() != "" && ui->estadoLlegada->text() != "" && ui->simbolo->text() != "") {
        int row = ui->tablaDeTransiciones->currentRow();
        QStringList ladoIzquierdo = ui->tablaDeTransiciones->item(row,0)->text().split(',');

        //Obtenemos el estado
        QString estadoE = ladoIzquierdo.at(0);
        estadoE = estadoE.split('(').at(1);

        //Obtenemos el simbolo a leer
        QString letraE = ladoIzquierdo.at(1);
        letraE = letraE.at(0);

        //Ahora borramos de transiciones la transicion seleccionada.

        automata->transicion()->elimina(estadoE, letraE);





        int count = ui->tablaDeTransiciones->currentRow();
        ui->tablaDeTransiciones->removeRow(count);
        if(ui->tablaDeTransiciones->rowCount() == 0) ui->eliminarTransicion->setEnabled(false);

        ui->agregarTransicion->setEnabled(true);
        ui->eliminarTransicion->setEnabled(false);
        ui->editarTransicion->setEnabled(false);
        limpiarCamposTransicion();

        if(ui->tablaDeTransiciones->rowCount() == 0) ui->verificarPalabra->setEnabled(false);
    }else {
        QMessageBox::warning(this, "Error", "Si quieres borrar una transicion, no debes borrar uno de sus elementos.");
    }
}
/**
 * Metodo que limpia los campos de ingreso de transiciones.
 *
 * @author Jose Rodríguez A.
 * @author Alberto Lagos T.
 */
void MainWindow::limpiarCamposTransicion() {
    ui->estado->setText("");
    ui->simbolo->setText("");
    ui->estadoLlegada->setText("");
}
/**
 * Metodo que se ejecuta cuando hay un cambio de evento.
 *
 * @author Jose Rodríguez A.
 * @author Alberto Lagos T.
 */
void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

/**
 * Metodo que se ejecuta cuando se presiona una fila de la lista de transiciones.
 *
 * @author Jose Rodríguez A.
 * @author Alberto Lagos T.
 */
void MainWindow::on_tablaDeTransiciones_cellPressed(int row, int column) {
    /* Lado Izquierdo de la Transicion */
    QStringList ladoIzquierdo = ui->tablaDeTransiciones->item(row,0)->text().split(',');

    //Obtenemos el estado
    QString estado1 = ladoIzquierdo.at(0);
    estado1 = estado1.split('(').at(1);
    ui->estado->setText(estado1);

    //Obtenemos el simbolo a leer
    QString simbolo1 = ladoIzquierdo.at(1).split(')').at(0);
    ui->simbolo->setText(simbolo1);

    /* Lado Derecho de la Transicion */
    QString estadoLlegada = ui->tablaDeTransiciones->item(row,1)->text();

    /* Obtenemos el estado de llegada y lo colocamos en el textfield*/
    ui->estadoLlegada->setText(estadoLlegada);

    tmpIzq = new QStringList();

    tmpIzq->append(estado1);
    tmpIzq->append(simbolo1);
    tmpIzq->append(estadoLlegada);


    ui->agregarTransicion->setEnabled(false);
    ui->eliminarTransicion->setEnabled(true);
    ui->editarTransicion->setEnabled(true);
}

/**
 * Metodo guarda los cambios realizados en una transicion seleccionada
 *
 * @author Jose Rodríguez A.
 * @author Alberto Lagos T.
 */
void MainWindow::on_editarTransicion_clicked() {
    //hace su gracia
    QString estado1 = ui->estado->text();
    QString simbolo1 = ui->simbolo->text();
    QString estado2  = ui->estadoLlegada->text();
        if(ui->estado->text().at(0) == 'q' && ui->estado->text().at(1).isDigit()) {
            if(ui->simbolo->text().length() == 1 ) {
                if(automata != 0 && automata->transicion()->buscarTransicion(ui->estado->text(),ui->simbolo->text())  != "0") {
                    QMessageBox::warning(this, "Error", "Esta transicion ya esta definida.");
                    ui->simbolo->setFocus();
                } else {
                    /* Haciendo valido el estado ingresado */
                    QString estado1 = ui->estado->text();
                    //EDICION

                    QString estadoLlegada = ui->estadoLlegada->text();

                    automata->agregarTransicion(ui->estado->text(), ui->simbolo->text(), estadoLlegada);

                    QTableWidgetItem *ladoIzquierdo = new QTableWidgetItem("("+estado1+","+ui->simbolo->text()+")",0);
                    QTableWidgetItem *ladoDerecho = new QTableWidgetItem(ui->estadoLlegada->text(),0);

                    ui->tablaDeTransiciones->setItem(ui->tablaDeTransiciones->currentRow(),0,ladoIzquierdo);
                    ui->tablaDeTransiciones->setItem(ui->tablaDeTransiciones->currentRow(),1,ladoDerecho);

                    ui->agregarTransicion->setEnabled(true);
                    ui->eliminarTransicion->setEnabled(false);
                    ui->editarTransicion->setEnabled(false);
                    limpiarCamposTransicion();
                    ui->estado->setFocus();
                    automata->transicion()->elimina(tmpIzq->at(0),tmpIzq->at(1));
                }
            } else {
                QMessageBox::warning(this, "Error", "Solo una letra por transicion es permitida.");
                ui->simbolo->setFocus();
            }
        } else {
            QMessageBox::warning(this, "Error", "El estado DEBE comenzar con q");
            ui->estado->setFocus();
        }
}

/**
 * Metodo que verifica si la palabra de entrada dada es reconocida por el automata dado.
 *
 * @author Jose Rodríguez A.
 * @author Alberto Lagos T.
 */
void MainWindow::on_verificarPalabra_clicked() {
    if(ui->estadoInicial->text() != "") {
        //le damos al automata el estado inicia/final
        automata->modificarEstadoInicial(ui->estadoInicial->text());
        automata->modificarEstadoTransitorio(automata->obtenerEstadoInicial());

        //le damos la palabra al automata
        automata->modificarPalabra(ui->palabraDeEntrada->text());

        QStringList *lista = new QStringList();
        QStringList estadosFinales =  ui->estadoFinal->text().split(',');

        for(int i=0;i<automata->obtenerPalabra().length();i++) {
            if(!lista->contains(automata->obtenerPalabra().at(i))) {
                lista->append(automata->obtenerPalabra().at(i));
            }
        }
        automata->modificarAlfabeto(lista);
        automata->modificarEstadoFinal(ui->estadoFinal->text());
        automata->obtenerSolucion();
        if(estadosFinales.contains(automata->obtenerEstadoTransitorio(), Qt::CaseInsensitive)) {
            QMessageBox::warning(this, "Estado Final", "Palabra reconocida por el automata dado.");
         } else {
            QMessageBox::warning(this, "Estado Final", "Palabra no reconocida por el automata dado.");
        }
        ui->ingresarNuevoAutomata->setEnabled(true);
    } else {
         QMessageBox::warning(this, "Error", "Debes rellenar el campo de estado inicial y final.");
    }

}

/**
 * Metodo que limpia todas las variables para que se pueda ingresar un nuevo automata sin la necesidad de volver a abrir la aplicación
 *
 * @author Jose Rodríguez A.
 * @author Alberto Lagos T.
 */
void MainWindow::on_ingresarNuevoAutomata_clicked() {
    /* Borramos todos los campos */
    //Campos de transicion
    limpiarCamposTransicion();

    //Campos de E.I y E.F
    ui->estadoInicial->setText("");
    ui->estadoFinal->setText("");
    automata->obtenerEstadoFinal() = "";
    automata->obtenerEstadoInicial() = "";
    automata->obtenerEstadoTransitorio() = "";

    //Palabra
    ui->palabraDeEntrada->setText("");
    automata->modificarAlfabeto(new QStringList());
    automata->modificarPalabra("");

    //transiciones de Automata
    automata->transicion()->eliminaTodo();

    //transiciones de la Interfaz
    for (int i=ui->tablaDeTransiciones->rowCount()-1; i >= 0; --i)
        ui->tablaDeTransiciones->removeRow(i);

    /* editamos el estado de cada  boton (para hacerlo clickeable o no) */
    if(!ui->agregarTransicion->isEnabled()) ui->agregarTransicion->setEnabled(true);
    if(ui->editarTransicion->isEnabled()) ui->editarTransicion->setEnabled(false);
    if(ui->eliminarTransicion->isEnabled()) ui->eliminarTransicion->setEnabled(false);

    ui->ingresarNuevoAutomata->setEnabled(false);
    ui->verificarPalabra->setEnabled(false);
}
