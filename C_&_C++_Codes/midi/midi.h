#ifndef MIDI_H
#define MIDI_H

#include <QMainWindow>
#include <QTimer>
#include <QtSerialPort>

namespace Ui {
class midi;
}

class midi : public QMainWindow
{
    Q_OBJECT

public:
    explicit midi(QWidget *parent = 0);
    ~midi();

private slots:


    void on_Comenzar_clicked();

    void on_metronomo_clicked();

    void sound();

    void leer();

    void escribir();

private:
    Ui::midi *ui;
    QTimer met;
    int metvolumen;
    int count;
    QSerialPort *conexion;
};

#endif // MIDI_H
