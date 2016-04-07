;--------------------------------------------------
;  assembly_ruido.s
;  Fuoco Cesar    v1.1    2/07/2013
;--------------------------------------------------

    .include "p33Fxxxx.inc"

    .global _assembly_flanger_triang
    .equ _BUFFER_SIZE,256

    .equ    FRECUENCIA_DE_MUESTREO,44211                    ;[Hz] = [muestras/segundo]

    .equ    FLANGER_MEDIO,FRECUENCIA_DE_MUESTREO/200        ;[Hz*seg]=[muestras]    F/200  = F*0.005
    .equ    FLANGER_OFFSET,FRECUENCIA_DE_MUESTREO/200      ;[Hz*seg]=[muestras]    F/1000 = F*0.0001
    .equ    FLANGER_DEPTH,0x6000                            ;0x6000  = 0.75 (?)
    .equ    FLANGER_LENGHT_,(256*20)-1
    .equ    FLANGER_REPEAT,2


    .equ    FLANGER_LENGHT,FLANGER_LENGHT_*2

    .section .text

_assembly_flanger_triang:

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
    ADD     W4,W2,W8
    MUL.UU  W8,#0x0002,W8

    ;MOV     #0x0000,W5                   ;Señal triangular
    MOV     #0x0000,W10                   ;Flag triangular        0x0001: rising  -   0xFFFF: falling

    ;w0  = BufferC o D (salida)
    ;w1  = BufferA o B(entrada)
    ;w2  = numsamp
    ;w3  = Vector de delay
    ;w4  = LIBRE
    ;w5  = valor flanger triangular
    ;w6  = LIBRE
    ;w7  = En DO guardo la entrada
    ;w8  = posicion del vector entrada grande
    ;w9  = LIBRE
    ;w10 = flag flanger triangular
;--------------------------------------------

    DO      W2,final
            NOP

            MOV     [W1],[W3+W8]
            MOV     [W1++],W7

            MOV     #FLANGER_OFFSET,W6
            CLR     A
            MAC     W5*W6,A                 ;SEÑAL TRIANGULAR * #FLANGER_OFFSET
            SAC     A,W4

            MOV     #FLANGER_MEDIO,W9
            ADD     W4,W9,W4                ;(SEÑAL TRIANGULAR * #FLANGER_OFFSET) + #FLANGER_MEDIO
            MOV     W5,W9
            MUL.UU  W4,#2,W4
            MOV     W9,W5
            ADD     W4,W8,W4                ;(SEÑAL TRIANGULAR * #FLANGER_OFFSET) + #FLANGER_MEDIO + DELAY_POS


            MOV     #FLANGER_LENGHT,W11
mayor_pos:
            CPSGT   W4,W11                      ;IF ((SEÑAL TRIANGULAR * #FLANGER_OFFSET) + #FLANGER_MEDIO) <= #FLANGER_LENGHT, ENTONCES:
            BRA     continua
            SUB     W4,W11,W4                   ;W4 -= #FLANGER_LENGHT
            BRA     mayor_pos

continua:
            MOV     [W3+W4],W4
            MOV     #0x7FFF,W6
            CLR     B
            MPY     W4*W6,B
            SAC     B,W4
            ADD     W4,W7,W7

            DEC2    W8,W8

            MOV     #0x7FFE,W6
            CPSEQ   W10,W6          ;IF(W10 != W6), ENTONCES:
            BRA     incremento
            BRA     decremento


incremento: INC2    W5,W5
            MOV     #0x7FFE,W6
            CPSNE   W5,W6          ;IF(W5 == W6), ENTONCES:
            MOV     #0x7FFE,W10
            BRA     final
            
decremento: DEC2    W5,W5
            MOV     #0x0000,W6
            CPSNE   W5,W6          ;IF(W5 == W6), ENTONCES:
            MOV     #0x0000,W10



    final: MOV W7,[W0++]
;--------------------------------------------


    POP	    CORCON
    POP     ACCBL
    POP     ACCBH
    POP     ACCAL
    POP     ACCAH

    RETURN

    .end
