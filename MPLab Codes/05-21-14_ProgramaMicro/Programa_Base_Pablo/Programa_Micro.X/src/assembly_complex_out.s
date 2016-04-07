;--------------------------------------------------
;  assembly_complex_out.s
;  Fuoco Cesar    v1.1    2/07/2013
;--------------------------------------------------

    .include "p33Fxxxx.inc"

    .global _assembly_complex_out

    .section .text

_assembly_complex_out:

;save context

    PUSH    ACCAH
    PUSH    ACCAL
    PUSH    ACCBH
    PUSH    ACCBL
    PUSH    CORCON

;dado que el lfo no deberia suoerar los 20Hz, y cada bloque provee un tiempo de
;procesamiento de 0.005 segundos y mi senoidal debe tener periodo de 0.05 seg, aprobechando
;la cte numsamp, mi sen resulta como sen(pi*i/127*10) con T= 0.05
;LOOP


    DEC     W2,W2                   ;decrementa 1 vez y lo copia
                                    ;hago el lazo hasta end w2 veces, o sea 256
    ;w0  = BufferC o D (salida)
    ;w1  = BufferA o B(entrada)
    ;w2  = numsamp
    MOV     #0x0000,W5
;--------------------------------------------

    DO      W2,final
            NOP

            MOV [W1++],[W0++]
     final: INC2 W1,W1
;--------------------------------------------


    POP	    CORCON
    POP     ACCBL
    POP     ACCBH
    POP     ACCAL
    POP     ACCAH

    RETURN

    .end
