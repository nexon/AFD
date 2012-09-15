#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "afd.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    afd *automata;
    QStringList *tmpIzq;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void changeEvent(QEvent *e);
    void limpiarCamposTransicion();

private slots:
    void on_ingresarNuevoAutomata_clicked();
    void on_verificarPalabra_clicked();
    void on_editarTransicion_clicked();
    void on_tablaDeTransiciones_cellPressed(int row, int column);
    void on_eliminarTransicion_clicked();
    void on_agregarTransicion_clicked();
};

#endif // MAINWINDOW_H
