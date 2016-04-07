;--------------------------------------------------
;  assembly_xdata.s
;  Fuoco Cesar    v1.1    2/07/2013
;--------------------------------------------------

    .include "p33Fxxxx.inc"
    
    .global _assembly_xdata_init_BitReversed
    .equ _BUFFER_SIZE,256
    .equ  NOISE_GATE_LEVEL,0x0000

    .section .text

_assembly_xdata_init_BitReversed:

;save context

    PUSH    ACCAH
    PUSH    ACCAL
    PUSH    ACCBH
    PUSH    ACCBL
    PUSH    CORCON


    MOV     #0x8800,W6      ;enable bit-reversed addressing
    MOV     W6,XBREV        ;& config for 16384 word buffer

    MOV     #0x09FF,W6      ;config W9 como bit-reversed
    MOV     W6,MODCON       ;y deshabilito circular addressing del X e Y

    NOP
    
    MOV     #0x3000,W9      ;indico de donde empieza W9

;    repeat #8
;    MOV     [W1++],[W2++]   ;W1 loop from 0x0900 to 0x0906 then repeats








    POP	    CORCON
    POP     ACCBL
    POP     ACCBH
    POP     ACCAL
    POP     ACCAH

    RETURN

    .end
