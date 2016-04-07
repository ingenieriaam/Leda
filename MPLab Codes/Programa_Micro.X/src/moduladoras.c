#include "../h/adcdacDrv.h"
#include <p33Fxxxx.h>
#include "dsp.h"
#include <math.h>

extern int f;
void moduladoras (void)
{
//  Señales de modulacion para los efectos que requieran una senoidal, triagular o cuadrada
//  Variable propia del dispositivo fs

//  Variable controlada por el usuario (potenciometro)
int n,i,m;

float w;
f  = 4;             //frecuencia de la se?al de modulacion
n  = (int)Fs/f;     //la cantidad de muestras necesarias para un ciclo de la señal, en C, n es un int que se redondea
w  = 2*PI*f;        //frecuencia angular



// Generamos las señales
//cada una solo genera un periodo, de esta manera se pretende ahorrar
//memoria y facilitar la circularidad

//   Senoidal
for (i = 0; i < n; i++)
{
    seno(i) = 0.5+ (sin((w*i)/fs)/2);
}

//  Triangular y cuadrada
m = (int)n/2;

for (i = 0; i < m; i++)
{

    tria(i) = 2*i/n;
    tria(i + m) = 1-2*i/n;

    cuad(i) = 1;
    cuad(i + m) = 0;

}