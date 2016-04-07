


;--------------------------------------------------
;  assembly_loopback.s
;  Fuoco Cesar    v1.1    2/07/2013
;--------------------------------------------------

    .include "p33Fxxxx.inc"

    .global _cero
    .equ _BUFFER_SIZE,256

    .section .text

_cero:

;save context

    PUSH    ACCAH
    PUSH    ACCAL
    PUSH    ACCBH
    PUSH    ACCBL
    PUSH    CORCON


;LOOP


    DEC     W2,W2

    DO      W2,final
        NOP

          MOV     [W1++],W3            ;cargo valor actual DE ENTRADA en w3

            BTSS    W3,#15
            MOV     #0x8000,W3              ;me fijo si es negativo o no

            BRA     salteo

            MOV     #0x7FFF,W3

   salteo:  MOV     W3,W10



    final:  MOV W10,[W0++]


    POP	    CORCON
    POP     ACCBL
    POP     ACCBH
    POP     ACCAL
    POP     ACCAH

    RETURN

    .end


