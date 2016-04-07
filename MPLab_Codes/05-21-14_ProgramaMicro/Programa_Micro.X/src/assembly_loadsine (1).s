;--------------------------------------------------
;  assembly_eco_xdata.s
;  Fuoco Cesar    v1.1    2/07/2013
;--------------------------------------------------

    .include "p33Fxxxx.inc"
    
    .global _assembly_loadsine
    .equ _BUFFER_SIZE,256
    
    .section .text

_assembly_loadsine:

;save context

    PUSH    ACCAH
    PUSH    ACCAL
    PUSH    ACCBH
    PUSH    ACCBL
    PUSH    CORCON    
   
                           	
;LOOP
    

    DEC     W1,W1                   ;decrementa 1 vez y lo copia
                                    ;w0=BufferC o D, w1= BufferA o B, W2 = DelayLine, w3 = numsamp, w4 = paso
                                    ;hago el lazo hasta end w3 veces, o sea 256
    MOV     #0x6000,W6              ;cargo en W6 el valor 0,75 en Q15
    ;MOV     #0x7FFF,W5
    ;MOV     #0x3100,W4
    DO      W1,final
            NOP
            
            MOV [W0++],W10           ;cargo valor actual DE ENTRADA en w7
            
     final: MOV W10,[W9++]
            ;MOV W10,[W8++]

            
    


    POP	    CORCON
    POP     ACCBL
    POP     ACCBH
    POP     ACCAL
    POP     ACCAH
                     
    RETURN

    .end
