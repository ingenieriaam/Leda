;--------------------------------------------------
;  assembly_xdata.s
;  Fuoco Cesar    v1.1    2/07/2013
;--------------------------------------------------

    .include "p33Fxxxx.inc"
    
    .global _assembly_xdata_init
    .equ _BUFFER_SIZE,256
    .equ  NOISE_GATE_LEVEL,0x0000

    .section .text

_assembly_xdata_init:

;save context

    PUSH    ACCAH
    PUSH    ACCAL
    PUSH    ACCBH
    PUSH    ACCBL
    PUSH    CORCON


    MOV     #0x0900,W6      ;set  modulo start address
    MOV     W6,XMODSRT

    MOV     #0x19FE,W6      ;set modulo end address
    MOV     W6,XMODEND

    MOV     #0x8FF9,W6      ;enable W3 as index register, X AGU
    MOV     W6,MODCON

    NOP
    
    MOV     #0x3000,W9      ;source buffer and modulo index register
;    MOV     #0x0920,W2      ;destination buffer

;    repeat #8
;    MOV     [W1++],[W2++]   ;W1 loop from 0x0900 to 0x0906 then repeats








    POP	    CORCON
    POP     ACCBL
    POP     ACCBH
    POP     ACCAL
    POP     ACCAH

    RETURN

    .end
