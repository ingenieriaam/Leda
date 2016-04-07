;--------------------------------------------------
;  assembly_prueba_sin.s
;  Fuoco Cesar    v1.1    2/07/2013
;--------------------------------------------------

    .include "p33Fxxxx.inc"
    
    .global _assembly_cargo_sin
    .equ _BUFFER_SIZE,256
    .equ  NOISE_GATE_LEVEL,0x0000

    .section .text

_assembly_cargo_sin:

;save context

    PUSH    ACCAH
    PUSH    ACCAL
    PUSH    ACCBH
    PUSH    ACCBL
    PUSH    CORCON


    MOV     W0,[W3]
    ;INC     W3



    POP	    CORCON
    POP     ACCBL
    POP     ACCBH
    POP     ACCAL
    POP     ACCAH

    RETURN

    .end
