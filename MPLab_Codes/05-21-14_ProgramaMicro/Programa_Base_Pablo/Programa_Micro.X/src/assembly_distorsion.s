;--------------------------------------------------
;  assembly_distorcion.s
;  Fuoco Cesar    v1.1    2/07/2013
;--------------------------------------------------

    .include "p33Fxxxx.inc"
    
    .global _assembly_distorsion
    .equ _BUFFER_SIZE,256
    
    .section .text

_assembly_distorsion:

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
                                    ;w0=BufferC o D, w1= BufferA o B, w2 = numsamp
                                    ;hago el lazo hasta end w3 veces, o sea 256
    MOV     #0x3FFF,W6              ;cargo en W6 el valor 20mV en Q15(CREO QUE ES 20mV ESTO!)
    MOV     #0x8000,W5
    IOR     W5,W6,W10
    SUB     W5,W10,W10
    MOV     #0x0000,W5
    ;MOV     #0x7FF0,W6             ;prueba
    CLR B
    LAC W6,B                                        ;cargo el valor de W6 en el acumulador B
    
;--------------------------------------------

    DO      W2,final
            NOP

    ;MOV #0x5FFF,W1                                  ;para probar
    MOV [W1++],W7
    MOV W7,W4
    CLR A
    LAC W7,A                                        ;cargo la entrada en el acumulador A

    SUB A                                           ;hago la cuenta A = A-B

    BTSS SR,#13                                     ;me fijo si hubo overflow en la ultima cuenta
                                                    ;(BTSS: saltea si es 1).(estoy mirando SA)
                                                    ;Significa que se fue del rango Q15
    BRA NO_OVERFLOW
    BRA OVERFLOW
    NO_OVERFLOW: SAC A,W11                          ;ahora, para probar si esta entre +-W6,
                                                    ;primero cargo A en W11 para verificar
                                                    ;si la cuenta anterior fue positiva o negativa

    ADD W11,W5,W11                                  ;W11 = W11 + W5. Esto lo hago para que me cambie SR

    BTSC SR,#3                                      ;me fijo si la ultima cuenta dio >0 y, en caso de
                                                    ;serlo,no mando el valor al DAC (miro el bit N)

    BRA SEGUNDA_COMPROBACION
    BRA TERCERA_COMPROBACION

;---------------------------------------------
    SEGUNDA_COMPROBACION:CLR A
    LAC W7,A                                        ;si no se cumple lo ultimo, pruebo con -W6

    ;LAC W6,B
    ADD A                                           ;en vez de hacer A-(-W6), hago A + W6
    BTSC SR,#13                                     ;me fijo si hubo overflow en la ultima cuenta

    BRA final
    SAC A,W11                                       ;mismo que antes

    ADD W11,W5,W11
    BTSS SR,#3                                      ;me fijo si la ultima cuenta dio <0 y, en caso de
                                                    ;serlo, mando el valor al DAC (miro el bit N)
                                                    ;(BTSC: salteo si 0)

    BRA final

    MOV W10,W7                                      ;le cargo 0 a la salida

    BRA final

 ;***********************************************************************************

    OVERFLOW: BCLR SR,#10                      ;PARA LIMPIAR SAB Y, POR LO TANTO, SA Y SB

    ;HACER ACA ALGO MEJOR PARA QUE SEA ALGO GENERICO, QUE NO SOLO SEA PARA VALORES BAJOS

    ;PRUEBO:
    ;CLR A
    ;LAC W7,A
    ;ADD A                                           ;A = A + B
                                                    ;Se que va a ser negativo el numero, por lo tanto
                                                    ;me fijo si es menor o mayor a -W6

    ADD W7,W6,W9                                    ;Se que va a ser negativo el numero, por lo tanto
                                                    ;me fijo si es menor o mayor a -W6

    BTSS SR,#3                                      ;me fijo si la ultima cuenta dio >0 y, en caso de
                                                    ;serlo, mando el valor al DAC (miro el bit N)

    BRA final
    MOV W10,W7                                      ;le cargo 0 a la salida

    
 ;***********************************************************************************
    TERCERA_COMPROBACION: CLR A
    MOV W6,W7
    ADD W5,W4,W11
    BTSC SR,#3
    MOV W10,W7                                      ;le cargo 0 a la salida

;***********************************************************************************
    final: MOV W7,[W0++]                            ;cargo resultado en buffer c,d y este lo lleva al dac


    POP	    CORCON
    POP     ACCBL
    POP     ACCBH
    POP     ACCAL
    POP     ACCAH

    RETURN

    .end
