;--------------------------------------------------
;  coef_genera.s
;  v1.0    08/05/2014
;--------------------------------------------------

    .include "p33Fxxxx.inc"

    .global _coef_genera
    .equ _BUFFER_SIZE,256

    .section .text

_coef_genera:

;save context

    PUSH    ACCAH
    PUSH    ACCAL
    PUSH    ACCBH
    PUSH    ACCBL
    PUSH    CORCON




    POP	    CORCON
    POP     ACCBL
    POP     ACCBH
    POP     ACCAL
    POP     ACCAH

    RETURN

    .end



