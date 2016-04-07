;--------------------------------------------------
;  assembly_saco_sin.s
;  Fuoco Cesar    v1.1    2/07/2013
;--------------------------------------------------

    .include "p33Fxxxx.inc"
    
    .global _assembly_saco_sin
    .equ _BUFFER_SIZE,256
    .equ  NOISE_GATE_LEVEL,0x0000

    .section .text

_assembly_saco_sin:

;save context

    PUSH    ACCAH
    PUSH    ACCAL
    PUSH    ACCBH
    PUSH    ACCBL
    PUSH    CORCON

    DEC     W1,W1

    REPEAT  #255
    MOV    [W3++],[W0++]



    POP	    CORCON
    POP     ACCBL
    POP     ACCBH
    POP     ACCAL
    POP     ACCAH

    RETURN

    .end
