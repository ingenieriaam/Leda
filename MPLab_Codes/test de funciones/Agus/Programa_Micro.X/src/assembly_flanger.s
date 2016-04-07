;--------------------------------------------------
;  assembly_ruido.s
;  Fuoco Cesar    v1.1    2/07/2013
;--------------------------------------------------

    .include "p33Fxxxx.inc"

    .global _assembly_flanger
    .equ _BUFFER_SIZE,256

    .equ    FRECUENCIA_DE_MUESTREO,44211                    ;[Hz] = [muestras/segundo]

    .equ    FLANGER_MEDIO,FRECUENCIA_DE_MUESTREO/2000        ;[Hz*seg]=[muestras]    F/200  = F*0.005
    .equ    FLANGER_OFFSET,FRECUENCIA_DE_MUESTREO/10000      ;[Hz*seg]=[muestras]    F/1000 = F*0.0001
    .equ    FLANGER_DEPTH,0x6000                            ;0x6000  = 0.75 (?)

    .section .text

_assembly_flanger:

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
    MOV     W4,W5
    MOV     #FLANGER_OFFSET,W6
    MOV     #FLANGER_MEDIO,W9

    ;w0  = BufferC o D (salida)
    ;w1  = BufferA o B(entrada)
    ;w2  = numsamp
    ;w3  = Vector de entrada(grande)
    ;w4  = LIBRE
    ;w5  = Vector de la señal de Flanger (-1 < W4 < 1)
    ;w6  = flanger offset
    ;w7  = LIBRE
    ;w8  = LIBRE
    ;w9  = flanger medio
    
;--------------------------------------------

    DO      W2,final
            NOP

    MOV     [W1++],W7                   ;Guardo entrada en w7

    MOV     [W5++],W4
    CLR     A
    MPY     W6*W4,A                     ;#FLANGER_OFFSET * señal de Flanger

    LAC     W9,B
    ADD     A                           ;A = A + B

    LAC     W2,B                        ;A = (#FLANGER_OFFSET * señal de Flanger) + #FLANGER_MEDIO + numsamp

    ADD     A
    SAC     A,W4
;
;
;    CLR     A
;    ADD     W3,W4,W3
;
;    ;SAC     A,W3
;
;;    ADD     W3,W4,W10                    ;Vector de entrada(grande) corrido
;;    MOV     W10,W3
;
;    MOV     [W3++],W8
;
;    ADD     W7,W8,W7                  ;Entrada + flanger
;
;    SUB     W3,W4,W3                    ;Vector de entrada(grande) al inicio
;
;    DEC     W2,W2                       ;Decremento numsamp

    final: MOV W7,[W0++]


    POP	    CORCON
    POP     ACCBL
    POP     ACCBH
    POP     ACCAL
    POP     ACCAH

    RETURN

    .end
