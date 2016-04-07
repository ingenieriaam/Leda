;--------------------------------------------------
;  assembly_ruido.s
;  Fuoco Cesar    v1.1    2/07/2013
;--------------------------------------------------

    .include "p33Fxxxx.inc"

	.extern	_assembly_manual_reverse

    .global _assembly_fft_test

    .section .text

_assembly_fft_test:

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




    MOV     #1, W8                  ;pongo numero_de_vuelta = 1

    ;w0  = BufferC o D(salida)
    ;W1  = BufferA o B(entrada)
    ;w2  = numsamp
    ;w3  = twiddleFactors
    ;w4  = vector_complejo auxiliar
    ;W8  = numero_de_vuelta

;--------------------------------------------
;   Paso el vector entrada a la parte real del
;   vector complejo auxiliar y completo la parte
;   imaginaria con 0(cero)

    DEC     W2, W2

    PUSH    W1
    PUSH    W4

    DO      W2, final_in_to_complex
            NOP

            MOV     W1, W4
            INC2    W4, W4

            MOV     #0, W4
            INC2    W4, W4

    final_in_to_complex:    INC2    W1,W1

    POP     W4
    POP     W1

    INC     W2, W2

;--------------------------------------------


    DO      #7, final_vuelta
            NOP

            PUSH    W4                      ;Guardo posicion entrada en TOS (Top of Stack)

            LSR     W2, W8, W2              ;Shift a la derecha (divido por 2) 'numero_de_vuelta' veces
            DEC     W2,W2                   ;decremento 1 para usar en el DO

            DO      W2,final_tramo
                    NOP

                    MOV     #1, W6
                    SL      W6, W8, W7              ;W5 = 2^(numero_de_vuelta)
                    DEC     W7,W5                   ;decremento 1 para usar en el DO

                    SL      W7, #1, W7              ;W5 = 2^(numero_de_vuelta+1)

                    PUSH    W3                      ;Guardo posicion del vector twiddle factor

                    DO      W5,final_uno
                            NOP
;                           Operaciones con Numeros Complejos
;                           C1 + C2*C3
;                           (A1) + j(B1) + ((A2 + jB2)*(A3 + jB3))
;                           (A1) + j(B1) + (A2*A3-B2*B3) + j(A2*B3+B2*A3)
;                           (A1 + A2*A3 - B2*B3) + j(B1 + A2*B3 + B2*A3)

                            CLR         A
                            LAC         [W4], A
                            MOV         [W4+W7], W5
                            MOV         [W3], W6
                            MAC         W5*W6, A
                            INC2        W4,W4
                            INC2        W3,W3
                            MOV         [W4+W7], W5
                            NEG         W5, W5
                            MOV         [W3], W6
                            MAC         W5*W6, A
                            SAC         A, W9           ;W10 = Entrada[i] + Entrada[i+W7]*W[0]  (Parte real)
                            DEC2        W3,W3

                            CLR         A
                            LAC         [W4], A
                            MOV         [W4+W7], W5
                            MOV         [W3], W6
                            MAC         W5*W6, A
                            DEC2        W4,W4
                            INC2        W3,W3
                            MOV         [W4+W7], W5
                            MOV         [W3], W6
                            MAC         W5*W6, A
                            SAC         A, W10          ;W10 = Entrada[i] + Entrada[i+W7]*W[0]  (Parte imaginaria)
                            DEC2        W3,W3

;                           Operaciones con Numeros Complejos
;                           C1 - C2*C3
;                           (A1) + j(B1) - ((A2 + jB2)*(A3 + jB3))
;                           (A1) + j(B1) - (A2*A3-B2*B3) + j(A2*B3+B2*A3)
;                           (A1 - A2*A3 + B2*B3) + j(B1 - A2*B3 - B2*A3)

                            CLR         A
                            LAC         [W4], A
                            MOV         [W4+W7], W5
                            NEG         W5, W5
                            MOV         [W3], W6
                            MAC         W5*W6, A
                            INC2        W4,W4
                            INC2        W3,W3
                            MOV         [W4+W7], W5
                            MOV         [W3], W6
                            MAC         W5*W6, A
                            DEC2        W3,W3

                            CLR         B
                            LAC         [W4], B
                            MOV         [W4+W7], W5
                            MOV         [W3], W6
                            MAC         W5*W6, B
                            DEC2        W4,W4
                            INC2        W3,W3
                            MOV         [W4+W7], W5
                            MOV         [W3], W6
                            MAC         W5*W6, B

                            MOV         W9, [W4++]           ;Entrada[i] = W9 = Entrada[i] + Entrada[i+W7]*W[0]    (Parte real)
                            MOV         W10, [W4--]           ;Entrada[i] = W10 = Entrada[i] + Entrada[i+W7]*W[0]   (Parte imaginaria)

                            SAC         A, W9                  ;W9 = Entrada[i] - Entrada[i+W7]*W[0]
                            MOV         W9, [W4+W7]         ;Entrada[i+W7] = W9 = Entrada[i] - Entrada[i+W7]*W[0]   (Parte real)
                            INC2        W4,W4
                            SAC         B, W10                  ;W10 = Entrada[i] - Entrada[i+W7]*W[0]
                            MOV         W9, [W4+W7]         ;Entrada[i+W7] = W10 = Entrada[i] - Entrada[i+W7]*W[0]  (Parte imaginaria)

                            INC2        W4,W4
                    final_uno: INC2        W3,W3

                    POP     W3                      ;Recupero posicion del vector twiddle factor

                    MOV     DCOUNT, W5
                    MOV     #0, W6
                    CPSEQ   W5, W6              ;Si DCOUNT != 0, entonces:
                        ADD     W4, W7, W4      ;Voy al siguiente tramo

            final_tramo:  NOP

            POP     W4                  ;Recupero buffer_entrada

            INC     W8, W8              ;Incremento numero_de_vuelta

   final_vuelta:  INC     W2, W2              ;incremento 1 para que sea par

;--------------------------------------------



;--------------------------------------------


    POP	    CORCON
    POP     ACCBL
    POP     ACCBH
    POP     ACCAL
    POP     ACCAH

    RETURN

    .end
