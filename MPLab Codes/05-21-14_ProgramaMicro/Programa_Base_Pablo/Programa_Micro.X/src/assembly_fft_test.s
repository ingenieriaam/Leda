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




    MOV     W1, W8                  ;pongo numero_de_vuelta = LOG2(numsamp)

    MOV     #1, W7
    SL      W7, W1, W1              ;W2 = Numsamp


    ;w0  = BufferA o B(entrada)
    ;w1  = numsamp
    ;w2  = twiddleFactors
    ;w3  = vector_complejo salida
    ;W4  = offset del puntero
    ;W8  = numero_de_vuelta = LOG2(numsamp)

;--------------------------------------------
;   Paso el vector entrada a la parte real del
;   vector complejo auxiliar y completo la parte
;   imaginaria con 0(cero)

    DEC     W1, W1

    PUSH    W0
    PUSH    W3

    MOV     #0, W4
    DO      W1, final_in_to_complex
            NOP

            MOV     [W0], [W3]
            INC2    W3, W3

            MOV     W4, [W3]
            INC2    W3, W3

    final_in_to_complex:    INC2    W0,W0

    POP     W3
    POP     W0

    INC     W1, W1

;--------------------------------------------

    MOV     #0, W1
	
    DEC     W8, W8
    DO      W8, final_vuelta    ;Desde (LOG2(numsamp)-1) Hasta (0)          ;W8 = n_vuelta-1
            NOP

            PUSH    W3                      ;Guardo posicion entrada en TOS (Top of Stack)

            MOV     #1, W5
            MOV     DCOUNT, W10
            INC2    W10, W6
            SL      W5, W6, W4              ;Offset = 2^(n_vuelta+1)

            DO      W1,final_tramo
                    NOP

            	    PUSH    W2                      ;Guardo posicion del vector twiddle factor

                    SL      W5, W10, W5      ;W5 = 2^(n_vuelta-1)
                    DEC     W5, W5

                    DO      W5,final_uno
                            NOP

;                           Operaciones con Numeros Complejos
;                           C1 + C2
;                           (A1 + jB1) + (A2 + jB2)
;                           (A1 + A2) + j(B1 + B2)

                            MOV         [W3], W5
                            MOV         [W3+W4], W6
                            ADD         W5, W6, W7       ;W7 = Entrada[i] + Entrada[i+W4]  (Parte real)
                            INC2        W3, W3

                            MOV         [W3], W5
                            MOV         [W3+W4], W6
                            ADD         W5, W6, W9       ;W9 = Entrada[i] + Entrada[i+W4]  (Parte imaginaria)
                            DEC2        W3, W3

;                           Operaciones con Numeros Complejos
;                           (C1 - C2)*C3
;                           ((A1 + jB1) - (A2 + jB2))*(A3 + jB3)
;                           ((A1 - A2) + j(B1 - B2))*(A3 + jB3)
;                           (A1 - A2)*A3 + (B2 - B1)*B3) + j((A1 - A2)*B3 + (B1 - B2)*A3)

                            CLR         A
                            MOV         [W3], W5
                            MOV         [W3+W4], W6
                            SUB         W5, W6, W5
                            MOV         [W2++], W6
                            MAC         W5*W6, A

                            INC2        W3, W3
                            MOV         [W3], W5
                            MOV         [W3+W4], W6
                            SUB         W6, W5, W5
                            DEC2        W3, W3
                            MOV         [W2], W6
                            MAC         W5*W6, A	;A = (Entrada[w3]-Entrada[w3+W4])*W2  (Parte real)

                            CLR         B
                            MOV         [W3], W5
                            MOV         [W3+W4], W6
                            SUB         W5, W6, W5
                            MOV         [W2--], W6
                            MAC         W5*W6, B

                            INC2        W3, W3
                            MOV         [W3], W5
                            MOV         [W3+W4], W6
                            SUB         W5, W6, W5
                            DEC2        W3, W3
                            MOV         [W2], W6
                            MAC         W5*W6, B	;B = (Entrada[w3]-Entrada[w3+W4])*W2  (Parte imaginaria)


                            MOV         W7, [W3++]	;W3[0] = Entrada[i] + Entrada[i+W4]  (Parte real)
                            MOV         W9, [W3--]	;W3[0] = Entrada[i] + Entrada[i+W4]  (Parte imaginaria)

                            ADD         W3, W4, W3
                            SAC         A, [W3++]	;W3[W4]  = (Entrada[i+W4] - Entrada[i+W4])*W2  (Parte real)
                            SAC         B, [W3--]	;W3[W4] = (Entrada[i+W4] - Entrada[i+W4])*W2  (Parte imaginaria)
                            SUB         W3, W4, W3
                            INC2        W3, W3
                            INC2        W3, W3

                            SUB         W8, W10, W6
                            INC2        W6, W6
                            MOV         #1, W5
                            SL          W5, W6, W5

                    final_uno: ADD		W2, W5, W2	;W2 += 2^(LOG2(numsamp)-n_vuelta+2)

            	    
                    MOV     DCOUNT, W5
                    MOV     #0, W6
                    CPSEQ   W5, W6              ;Si DCOUNT != 0, entonces:
                        ADD     W3, W4, W3      ;Voy al siguiente tramo

            final_tramo:  POP     W2                      ;Guardo posicion del vector twiddle factor

            INC     W1, W1
            SL      W1, #1, W1
            DEC     W1, W1              ;W1 = W1*2+1

            POP     W3                  ;Recupero buffer_entrada

   final_vuelta:  NOP

;--------------------------------------------



;--------------------------------------------


    POP	    CORCON
    POP     ACCBL
    POP     ACCBH
    POP     ACCAL
    POP     ACCAH

    RETURN

    .end
