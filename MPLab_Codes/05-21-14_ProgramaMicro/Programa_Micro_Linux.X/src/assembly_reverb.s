
;--------------------------------------------------
;  assembly_function.s
;  Fuoco Cesar    v1.1    2/07/2013
;--------------------------------------------------

    .include "p33Fxxxx.inc"

    .global _assembly_reverb
    .equ _BUFFER_SIZE,256

    .section .text

_assembly_reverb:

;save context

    PUSH    ACCAH
    PUSH    ACCAL
    PUSH    ACCBH
    PUSH    ACCBL
    PUSH    CORCON


;LOOP

   

    DEC     W3,W3                   ;decrementa 1 vez y lo copia
                                    ;w0=BufferC o D, w1= BufferA o B, W2 = DelayLine, w3 = numsamp, w4 = paso
                                    ;hago el lazo hasta end w3 veces, o sea 256
    MOV     #0x0666,W6              ;cargo en W6 el valor 0,75 en Q15
    MOV     #10,W5                  ;cantidad de muestras a sumar

    DO      W3,final
            NOP

            MOV [W1++],W7           ;cargo valor actual DE ENTRADA en w7
            MOV [W2],W4
            CLR  A                  ;pongo el acumulador en 0

            ADD W7,A                ;muevo el valor actual al acumulador A. A = BufferA/B*1, buscar como cambiar el x

            MOV W5,W12          ;tiene el valor decrementado de w5
            DO  W5,reverb
            NOP


                MOV #100,W8
                ;CLR B
                MUL.UU W12,W8,W8
                ;SAC B,W8


                MUL.UU W8,#2,W8
                MOV [W2+W8],W4          ;Voy a la muestra mas vieja +100 * nº de pasada

                DEC W12,W12
            reverb:MAC  W4 * W6,A

            SAC A,W10           ; saco la suma del acumulador a un reg auxiliar
            
            MOV W10,[W2++]


    final:  MOV W10,[W0++]        ;cargo resultado en buffer c,d y este lo lleva al dac


    POP	    CORCON
    POP     ACCBL
    POP     ACCBH
    POP     ACCAL
    POP     ACCAH

    RETURN

    .end


