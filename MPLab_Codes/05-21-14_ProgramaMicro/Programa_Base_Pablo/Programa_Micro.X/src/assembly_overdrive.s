;--------------------------------------------------
;  assembly_overdrive.s
;  Ortiz, Agustin    v1.0    17/10/2013
;--------------------------------------------------

    .include "p33Fxxxx.inc"

    .global _assembly_overdrive
    .equ _BUFFER_SIZE,256

    .section .text

_assembly_overdrive:

;save context

    PUSH    ACCAH
    PUSH    ACCAL
    PUSH    ACCBH
    PUSH    ACCBL
    PUSH    CORCON


;LOOP
; hago en total out = (1/k + 1)*(in)./(1/k +abs(in)); (ver 1/k en el main)
;como 1+algo se me va de rango out = (1/k)*in + in / 1/k + abs(in)

    DEC     W2,W2                   ;decrementa 1 vez y lo copia
                                    ;w0=BufferC o D, w1= BufferA o B, W2 = numsamp, w3 = 1/k
    MOV     #0x7FFF,W11             ;le cargo un 1
    ;MOV     #0x0100,W3              ;0.00390625
    MOV     #0x00A5,W4               ;0.005050


    DO      W2,final
       NOP
            CLR A                        ;limpio el acumulador
            MOV     [W1++],W7            ;cargo valor actual DE ENTRADA en w7

            AND     W7,W11,W3           ;si habia un 1 en el 1er bit lo pongo en 0
            SUB     W11,W3,W3           ;W3 = |in|

            MOV     W3,W6
            MPY     W6*W4,A              ;W6=(1/K *|IN|)
            SAC     A,W6
            CLR     A                    ; V

            CLR     A                   ; V
            LAC     W4,A
            LAC     W3,B
            ADD     A                ;A = A + B   ;A = abs(in)+ 1/k
            ;MOV     #0x0005,W2
            ;LAC     W2,B
            ;SUB     A
            SAC     A,W10               ;W10 = abs(in) + 1/k DENOMINADOR

            CLR     A
            LAC     W6,A
            LAC     W3,B
            ADD     A
            SAC     A,W8                ;W8 = ((1/K *|IN|) + |IN|) NUMERADOR

            MOV     W0,W3              ;salvo el valor de W0
            MOV     W1,W9

            SUB     W8,W10,W4
            BTSS    SR,#1
            BRA     SIGO
            SUB     W8,#0x0001,W8

            SIGO: REPEAT #17
            DIVF   W8,W10              ;divido, el resultavo va a W0 y el Resto a W1 ERROR

            MOV     W0,W6             ;pongo el resultado final en W6
            MOV     W3,W0            ;retorno W0 a su valor previo a la division
            MOV     W9,W1

            MOV     #0x0000,W4
            ADD     W4,W7,W7
            BTSS    SR,#3
            BRA     final
            MOV     #0x8000,W5
            IOR     W5,W6,W10
            SUB     W5,W10,W6


    final:  MOV W6,[W0++]              ;cargo resultado en buffer c,d y este lo lleva al dac


    POP	    CORCON
    POP     ACCBL
    POP     ACCBH
    POP     ACCAL
    POP     ACCAH

    RETURN

    .end
