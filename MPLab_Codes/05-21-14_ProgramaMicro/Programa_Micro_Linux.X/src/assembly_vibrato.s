;--------------------------------------------------
;  assembly_vibrato.s
;  Fuoco Cesar    v1.1    2/07/2013
;--------------------------------------------------

    .include "p33Fxxxx.inc"
    
    .global _assembly_vibrato
    .equ _BUFFER_SIZE,256
    
    .section .text

_assembly_vibrato:

;save context

    PUSH    ACCAH
    PUSH    ACCAL
    PUSH    ACCBH
    PUSH    ACCBL
    PUSH    CORCON    
   
                           	
;LOOP
    

    DEC     W2,W2                   ;decrementa 1 vez y lo copia
                                    ;w0=BufferC o D, w1= BufferA o B, W2 = DelayLine, w3 = numsamp, w4 = paso
                                    ;hago el lazo hasta end w3 veces, o sea 256
    MOV     #0x6000,W6              ;cargo en W6 el valor 0,75 en Q15
    ;MOV     #0x7FFF,W5
    ;MOV     #0x3100,W4
    DO      W2,final
            NOP
            
            MOV [W1++],W7           ;cargo valor actual DE ENTRADA en w7
            MOV [W9],W4
            ;MOV [W8],W4
            CLR  A                  ;pongo el acumulador en 0

            ADD W7,A               ;muevo el valor actual al acumulador A. A = BufferA/B*1, buscar como cambiar el x
            MAC  W4 * W6,A          ; A = A + 0.75 * DELAYLINE

            SAC A,W10               ; saco la suma del acumulador a un reg auxiliar
            MOV W10,[W9++]
            ;MOV W10,[W8++]

            
    final:  MOV W10,[W0++]        ;cargo resultado en buffer c,d y este lo lleva al dac


    POP	    CORCON
    POP     ACCBL
    POP     ACCBH
    POP     ACCAL
    POP     ACCAH
                     
    RETURN

    .end
