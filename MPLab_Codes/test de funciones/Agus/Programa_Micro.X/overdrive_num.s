;--------------------------------------------------
;  overdrive_num.s
;  Ortiz, Agustin    v1.0    17/10/2013
;--------------------------------------------------

    .include "p33Fxxxx.inc"

    .global _overdrive_num
    .equ _BUFFER_SIZE,256

    .section .text

_overdrive_num:

;save context

    PUSH    ACCAH
    PUSH    ACCAL
    PUSH    ACCBH
    PUSH    ACCBL
    PUSH    CORCON


;LOOP
; hago en total out = (1/k + 1)*(in)./(1/k +abs(in)); (ver 1/k en el main)
;como 1+algo se me va de rango out = (1/k)*in + in / 1/k + abs(in)

    DEC     W2,W2                   ;decrementa 1 vez y lo copia
                                    ;w0=BufferC o D, w1= BufferA o B, W2 = numsamp, w3 = 1/k
    MOV     #0x7FFF,W11             ;le cargo un 1
    ;MOV     #0x0100,W3              ;0.00390625
    MOV     #0x00A5,W4               ;0.005050


    DO      W2,final
       NOP
            CLR A                        ;limpio el acumulador
            MOV     [W1++],W7            ;cargo valor actual DE ENTRADA en w7

            AND     W7,W11,W3           ;si habia un 1 en el 1er bit lo pongo en 0
            SUB     W11,W3,W3           ;W3 = |in|

            MOV     W3,W6
            MPY     W6*W4,A              ;W6=(1/K *|IN|)
            SAC     A,W6

            CLR     A
            LAC     W6,A
            LAC     W3,B
            ADD     A
            SAC     A,W8                ;W8 = ((1/K *|IN|) + |IN|) NUMERADOR

    final:  MOV W8,[W0++]              ;cargo numerador en num


    POP	    CORCON
    POP     ACCBL
    POP     ACCBH
    POP     ACCAL
    POP     ACCAH

    RETURN

    .end



