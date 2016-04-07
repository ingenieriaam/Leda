


;--------------------------------------------------
;  decimador.s
;  Fuoco Cesar    v1.1    2/07/2013
;--------------------------------------------------

    .include "p33Fxxxx.inc"

    .global _decimador
    .equ _BUFFER_SIZE,256

    .section .text

_decimador:

;save context

    PUSH    ACCAH
    PUSH    ACCAL
    PUSH    ACCBH
    PUSH    ACCBL
    PUSH    CORCON

;W0 -> salida
;W1 -> entrada
;W2 -> NUMDEC = NUMSAMP/16


    GOTO fnc

Mul_dos:                                                            ;Necesito W8 que es lo que quiero multiplicar por 2
                            PUSH    W7
                            PUSH    W4
                            MOV     #0x0002,W4
                            MUL.SS  W6,W4,W6
                            POP     W4
                            POP     W7
                            RETURN


;LOOP

fnc:
            PUSH    W6
            MOV     W2,W6
            CALL    Mul_dos
            MOV     W6,W2                           ;W2 = NUMDEC * 2
            POP     W6
            MOV     [W1],[W0++]                     ;Paso la primer posicion de la entrada
            MOV     #0x0000,W4                      ;W4 es mi contador del loop
            MOV     #0x0020,W6                      ;Cargo en W6 32 (16 posiciones en vector)
decimador:  ADD     W4,W6,W8                        ;W8 = posicion de filter_signal
            MOV     [W1+W8],[W0]
            CPSEQ   W8,W2
            CALL    Mul_dos                         ;W6 * 2
            CPSEQ   W8,W2
            INC2    W0,W0
            CPSEQ   W8,W2
            GOTO decimador


    POP	    CORCON
    POP     ACCBL
    POP     ACCBH
    POP     ACCAL
    POP     ACCAH

    RETURN

    .end


