#include "midi.h"
#include "ui_midi.h"
#include <QtMultimedia/QAudio>
#include <QSound>
#include <stdio.h>
#include <QMessageBox>
#include <QAudioOutput>

#define  DURACION  "U"
#define  DETECCION "E"

midi::midi(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::midi)
{
    ui->setupUi(this);

    // Seteo de la conexion serie
    conexion=new QSerialPort(this);
    connect(conexion,SIGNAL(readyRead()),this,SLOT(leer()));
    conexion->setPortName("/dev/tty/usb0");
    conexion->setBaudRate(QSerialPort::Baud9600);
    conexion->setDataBits(QSerialPort::Data8);
    conexion->setParity(QSerialPort::NoParity);
    conexion->setFlowControl(QSerialPort::NoFlowControl);
    conexion->setStopBits(QSerialPort::OneStop);
    if(conexion->open(QIODevice::ReadWrite)==0) QMessageBox::warning(this,"error","no se logró la conexión") ;
}

midi::~midi()
{
    delete ui;
}


void midi::on_Comenzar_clicked()
{
    QString filename;
    int dur,det,numcomp,dencomp,tempo;
    dur=det=numcomp=dencomp=tempo=0;
    if(ui->Comenzar->text() == "Comenzar grabación")
    {
        ui->Comenzar->setText("Finalizar grabación");


        numcomp=ui->numCompas->value();
        dencomp=ui->denCompas->value();
        tempo=ui->Tempo->value();
        dur=ui->duracion->value();
        det=ui->deteccion->value();

        conexion->write(DURACION+dur);
        conexion->write(DETECCION+det);
    }
    else
    {
        ui->Comenzar->setText("Comenzar grabación");
        //crear archivo midi
    }
}

void midi::on_metronomo_clicked()
{
    /*tempo=negras cada min, y el compas dará cada cuantas negras hay unna ascentuación*/
    float tick;  // negras por seg


    tick= (ui->Tempo->value())/(60*(4.0/ui->denCompas->value()));  // negras por seg

    if(ui->metronomo->isChecked() == true)
    {
        // hacer sonar el metronomo
        connect(&met, SIGNAL(timeout()), this, SLOT(sound()));
        met.setSingleShot(false);

        met.start(1000/tick);
    }
    else
    {
        disconnect(&met, SIGNAL(timeout()), this, SLOT(sound()));
        met.stop();
    }

}

void midi::sound (void)
{
    if(count < ui->numCompas->value()-1)
    {
        QSound::play("click.wav");
    }
    else
    {
        QSound::play("loudclick.wav");
    }

    count++;
    count = count%ui->numCompas->value();
}

void midi::leer (void)
{
    QByteArray dato = conexion->readAll();

    QMessageBox::warning(this,"llego",dato);
}
void midi::escribir(void)
{
//    conexion->write(dato);
}
