


;--------------------------------------------------
;  assembly_loopback.s
;  Fuoco Cesar    v1.1    2/07/2013
;--------------------------------------------------

    .include "p33Fxxxx.inc"

    .global _assembly_loopback
    .equ _BUFFER_SIZE,256

    .section .text

_assembly_loopback:

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

        MOV [W1++],W3
        MOV W3,W10


    final:  MOV W10,[W0++]


    POP	    CORCON
    POP     ACCBL
    POP     ACCBH
    POP     ACCAL
    POP     ACCAH

    RETURN

    .end