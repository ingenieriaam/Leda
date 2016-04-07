;--------------------------------------------------
;  assembly_overdrive2.s
;  Ortiz, Agustin    v648.221    28/04/2014
;--------------------------------------------------

    .include "p33Fxxxx.inc"

    .global _assembly_overdrive2
    .equ _BUFFER_SIZE,256

    .section .text

_assembly_overdrive2:

;save context

    PUSH    ACCAH
    PUSH    ACCAL
    PUSH    ACCBH
    PUSH    ACCBL
    PUSH    CORCON


;LOOP
; hago en total out = (1/k + 1)*(in)./(1/k +abs(in)); (ver 1/k en el main)
;como 1+algo se me va de rango out = (1/k)*in + in / 1/k + abs(in)

;si la consideracion de la divicion es respecto a los modulos => si c>0 ,in debe ser -1<in<1, o sea, cuidado con -1
;si se refiere a el valor signado => x<1 basta y sobra


    DEC     W2,W2                   ;decrementa 1 vez y lo copia
                                    ;w0=BufferC o D, w1= BufferA o B, W2 = numsamp, w3 = 1/k
    MOV     #0x7FFF,W11             ;le cargo un 1
    MOV     #0x8000,W5              ;-1
    MOV     #0x00A5,W4               ;0.005050


    DO      W2,final
       NOP

            CLR A                        ;limpio el acumulador
            MOV     [W1++],W3            ;cargo valor actual DE ENTRADA en w3

            MOV     W3,W6
            MPY     W6*W4,A              ;W6=(1/K *In)
            SAC     A,W6
            CLR     A                    ; V


            AND     W3,W11,W7           ;si habia un 1 en el 1er bit lo pongo en 0
            SUB     W5,W7,W7           ;W7 = |in|

            CLR     A                   ; V
            LAC     W4,A
            LAC     W7,B
            ADD     A                ;A = A + B   ;A = abs(in)+ 1/k
            SAC     A,W10               ;W10 = abs(in) + 1/k DENOMINADOR


            CLR     A
            LAC     W6,A
            LAC     W3,B
            ADD     A
            SAC     A,W8                ;W8 = ((1/K *IN) + IN) NUMERADOR


            ;me fijo si se cumple las condiciones para la divicion
            ;o sea W8 < W10

            SUB    W10,W8,W7        ;si da positivo entonces divido
            BTSC   SR,#3            ;si es negativo salteo
            BRA    cumple
            BRA    no_cumple

cumple:
            BTSC    SR,#1           ;si numerador y denominador son distintos saltea
            BRA     iguales


            MOV     W0,W3              ;salvo el valor de W0
            MOV     W1,W9
            ;PROCESAMIENTO PARA LOS CASOS NORMALES
            REPEAT #17
            DIVF   W8,W10              ;divido, el resultavo va a W0 y el Resto a W1 ERROR

            MOV     W0,W6             ;pongo el resultado final en W6
            MOV     W3,W0            ;retorno W0 a su valor previo a la division
            MOV     W9,W1
            BRA     final

no_cumple:  MOV     #0x0000,W6      ;si llego aca estamos hasta las manos !!!
            BRA     final

iguales:    MOV     0x8000,W6
            SUB     W3,W6,W6
            BTSS    SR,#1               ;si era 0x8000 saltea Y W6 ya es -1
            MOV     #0x7FFF,W6          ;sino le pongo un 1

    final:  MOV W6,[W0++]              ;cargo resultado en buffer c,d y este lo lleva al dac


    POP	    CORCON
    POP     ACCBL
    POP     ACCBH
    POP     ACCAL
    POP     ACCAH

    RETURN

    .end



