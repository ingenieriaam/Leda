;--------------------------------------------------
;  _asm_frec_posibles_armonicos.s
;  Francisco Dominguez    v1.1    08/21/2015
;--------------------------------------------------

    .include "p33EP256MU806.inc"
    .include "include/adcdacDrv.inc"
    
    

    .global _asm_frec_posibles_armonicos
    .global _asm_inverse_numbervec_findpitch
    .global _asm_maximos_relativos
    .global _asm_piso_ruido
    .global _asm_VectorInt
    .global _asm_duracion
    .global _asm_VectorMod


    .section .text

_asm_frec_posibles_armonicos:
;W0: Direccion del vector de salida
;W1: Indice del armonico de maxima amplitud
;W2: Direccion del vector que contiene la inversa de los numeros naturales (asm_inverse_numbervec_findpitch)


;save context (Solo de lo que se modifica)
    PUSH    ACCAH
    PUSH    ACCAL
    PUSH    CORCON              ;Es modificado por la instruccion DO


    MOV     W1, [W0++]          ;Primero guardo el indice del armonico de maxima amplitud
    MOV     W1, W4              ;Tambien lo guardo en W4 para hacer el MPY

    DO      #CANT_M_2, final_frec_posibles_armonicos    ;Repite (CANT_M - 1) veces

            MOV     [++W2], W5  ;En el vector que tengo 1/2,1/3,1/4... en Q15, lo uso para MPY y lo incremento
            MPY     W4*W5, A    ;Hago la multiplicacion

    final_frec_posibles_armonicos:
            SAC     A,[W0++]    ;Cargo los datos en el vector de salida


    POP	 CORCON
    POP     ACCAL
    POP     ACCAH

    RETURN


;--------------------------------------------------
;  _asm_inverse_numbervecfindpitch.s
;  Francisco Dominguez    v1.1    08/21/2015
;--------------------------------------------------



_asm_inverse_numbervec_findpitch:
;W0: inv_number(out)

;save context (No se requiere salvar contexto porque no se modifica)
    PUSH    CORCON                  ;Es usado por el DO


    MOV     #0x0001, W3             ;W3 = 1 (Para hacer la division 1/x)

    MOV     W0, W4                  ;Muevo la direccion del vector a otro registro

    MOV     #0x7FFF, W7             ;W7 = 1 (en fractional)
    MOV     W7, [W4++]              ;inv_number[0] = W7 = 1 (en fractional)

    MOV     #0x0001, W7             ;i = 1 (Cargo W7 con 1 que será el iterador del siguiente DO)

    DO      #CANT_M_2, final_inverse_numbervec_findpitch    ;Repite (CANT_M - 1) veces
            INC     W7,W7           ;i++ (Incremento el iterador W7)

            REPEAT  #17
                    DIVF    W3,W7   ;W0 = 1/i (Realizo la division. repeat 17 porque necesita 18 ciclos)
                                    ;Guarda el resultado en W0 y el resto en W1
            
    final_inverse_numbervec_findpitch:
            MOV     W0,[W4++]       ;inv_number[i-1] = W0 (Guardo el resultado de la division en el contenido de W4, luego incremento el puntero)


    POP	 CORCON

    RETURN


;--------------------------------------------------
;  _asm_maximos_relativos.s
;  Francisco Dominguez    v1.1    08/21/2015
;--------------------------------------------------


_asm_maximos_relativos:
;W0: maxrel_idx(out)
;W1: fft_y(in)
;W2: piso(in)

;save context (No se requiere salvar contexto porque no se modifica)
    PUSH    CORCON


    MOV     #0x0000, W3     ;i = 0 (posicion actual en fft_y)
    MOV     #0x0000, W4     ;j = 0 (guarda la cantidad de maximos relativos encontrados hasta el momento)

    MOV     [W1],W5         ;W5 = fft_y[0] (guardo la primera posicion del vector fft_y)

        ;W0: maxrel_idx(out)
        ;W1: fft_y(in)
        ;W2: piso(in)
        ;W3: i
        ;W4: j
        ;W5: fft_y[i-1]
        ;W6: fft_y[i]
        ;W7: fft_y[i+1]
        ;W8: auxiliar
    DO      #NUMSAMP_2, final_maximos_relativos

            INC     W3, W3          ;i++
            MOV     [++W1],W6       ;W6 = fft_y[i]
            SUB     W6,W2,W8        ;fft_y[i] - piso_ruido
            BTSC    SR,#3           ;if(signal(i) < piso_ruido)
                BRA     final_maximos_relativos     ;continue (brancheo hasta final)

            INC2    W1, W7          ;W7 = fft_y + 1 (incremento la direccion de fft_y)
            MOV     [W7],W7         ;W7 = fft_y[i+1]
            SUB     W6,W7,W8        ;fft_y[i] - fft_y[i+1]
            BTSC    SR,#3           ;if(signal[i] < signal[i+1])
                BRA     final_maximos_relativos     ;continue

            SUB     W6,W5,W8        ;signal[i] - signal[i-1]
            BTSC    SR,#3           ;if(signal[i] < signal[i-1])
            BRA     final_maximos_relativos         ;continue

            MOV     W3,[W0++]       ;maxrel_idx[j] = i
            INC     W4,W4           ;j++
    final_maximos_relativos:
            MOV     W6,W5           ;W5 = fft_y[i]   (Guardo el valor actual en W5 para que en el siguiente ciclo contenga la posicion anterior)

    MOV     W4, W0          ;return j



    POP	 CORCON

    RETURN


;--------------------------------------------------
;  _asm_piso_ruido.s
;  Francisco Dominguez    v1.1    08/21/2015
;--------------------------------------------------



_asm_piso_ruido:
;W0: buffer in
;W1: coeficiente in


;save context (Solo de lo que se modifica)
    PUSH    ACCAH
    PUSH    ACCAL


    CLR     A                       ;Limpio el acumulador A

    REPEAT  #NUMSAMP_1              ;Repite la siguiente instruccion NUMSAMP veces
            ADD     [W0++], A       ;Es mas optimo sumar todo y luego multiplicar ya que se ahorran ciclos y no se pierde informacion

    SAC     A, #7, W4               ;Guardo el valor de A dividido 128
    LSR     W4, #POW_NUMSAMP_7, W4  ;Vuelvo a dividir por 2 tantas veces hasta llevar a NUMSAMP
    MOV     W1, W5
    MPY     W4*W5, A
    SAC     A, W0
            ;El valor de retorno es W0


    POP     ACCAL
    POP     ACCAH

    RETURN


;--------------------------------------------------
;  _asm_VectorInt.s
;  Francisco Dominguez    v1.1    08/21/2015
;--------------------------------------------------



_asm_VectorInt:
;W0: cantidad de elementos / salida
;W1: vector de entrada


;save context (Solo de lo que se modifica)
    PUSH    ACCAH
    PUSH    ACCAL


    CLR     A                       ;Limpio el acumulador A
    DEC	    W0, W0
    
    REPEAT	    W0
	ADD	[W1++], A
    
    SAC     A, W0


    POP     ACCAL
    POP     ACCAH

    RETURN



;--------------------------------------------------
;  _asm_duracion.s
;  Francisco Dominguez    v1.1    08/21/2015
;--------------------------------------------------



_asm_duracion:
;W0: vector fft actual
;W1: vector fft anterior
;W2: piso de ruido


;save context (Solo de lo que se modifica)
    PUSH    ACCAH
    PUSH    ACCAL
    PUSH    ACCBH
    PUSH    ACCBL
    PUSH    CORCON              ; Es modificado por la instruccion DO


    MOV	    W0,	    W3		    ; Copio puntero para no perder la direccion
    MOV	    W1,	    W4		    ; Copio puntero para no perder la direccion
    
    MOV	    #-1,    W5		    ; Guardo "-1" para multiplicar luego
    
    CLR     A                       ; Limpio el acumulador A
    CLR     B                       ; Limpio el acumulador B
    
    DO	    #NUMSAMP_1, END_PARAM
		    ADD	    [W3],   #0x07,  B	; sumo un bin de la fft actual al accumulador B
		    ADD	    [W4],   #0x07,  B	; sumo un bin de la fft anterior al accumulador B
						; B = FFT_actual(i) + FFT_anterior(i)
		    ADD	    [W3++], #0x07,  A	; sumo un bin de la fft actual al accumulador A
		    MUL.SS  W5,	    [W4++], W6	; niego un bin de la fft anterior
    END_PARAM:	    ADD	    W6,	    #0x07,  A	; sumo el bin negado de la fft anterior al accumulador A
						; A = FFT_actual(i) - FFT_anterior(i)
    
    
    SAC     A,	    W0


    POP     CORCON
    POP     ACCBL
    POP     ACCBH
    POP     ACCAL
    POP     ACCAH

    RETURN
    
    
    
    
    
    
;--------------------------------------------------
;  _asm_VectorMod.s
;  Francisco Dominguez    v1.1    08/21/2015
;--------------------------------------------------
    
_asm_VectorMod:

;save context
    
    ;W0: Cantidad de muestras
    ;W1: Vector de salida
    ;W2: Vector de entrada

    PUSH    CORCON

; se calcula el valor absoluto de un vector
; W1 destino W2 entrada
    
    DEC     W0,W0
    MOV     #0xFFFF,W3             ;le cargo un 1

    DO      W0,final_VectorMod
        MOV     [W2++],W1              ;llevo el dato al registro de salida
        BTSC    W2,#15             ;si el bit de signo es 0 saltea
        ;si es negativo
        XOR     W2,W3,W1           ;invierto todos los bits y obtengo el valor positivo

    final_VectorMod: INC2 W1, W1

    POP	    CORCON

    RETURN
    
    .end
    
    