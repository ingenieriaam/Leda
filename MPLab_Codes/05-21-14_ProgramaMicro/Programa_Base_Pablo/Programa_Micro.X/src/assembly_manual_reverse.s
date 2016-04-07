;--------------------------------------------------
;  assembly_ruido.s
;  Fuoco Cesar    v1.1    2/07/2013
;--------------------------------------------------

    .include "p33Fxxxx.inc"

	.global	_assembly_manual_reverse

    .section .text

_assembly_manual_reverse:

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


    MOV     #1, W4
    CPSGT   W0, W4      ;Si (LOG base 2 del buffer size) <= 1, entonces:
        BRA     final

    MOV     #1, W3
    SL      W3, W0, W4      ;W4 = buffer_size

    ADD     W1, W4, W3      ;W3 = buffer de cambio (puntero a mitad del buffer)

    LSR     W4, #1, W4      ;W4 /= 2
    DEC2    W4, W4

    INC2    W1, W1

    ;w0  = LOG base 2 del buffer size
    ;w1  = Buffer
    ;W2  = Cantidad de swap's
    ;W3  = buffer de cambio
    ;W4  = veces en el DO
;--------------------------------------------
    DO      W4,final
            NOP

            MOV     [W1], W5
            MOV     [W3], [W1]
            MOV     W5, [W3]

            INC2    W3, W3
            
    final:  INC2    W1, W1
;--------------------------------------------


    POP	    CORCON
    POP     ACCBL
    POP     ACCBH
    POP     ACCAL
    POP     ACCAH

    RETURN

    .end
