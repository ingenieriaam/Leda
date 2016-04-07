;--------------------------------------------------
;  assembly_ruido.s
;  Fuoco Cesar    v1.1    2/07/2013
;--------------------------------------------------

    .include "p33Fxxxx.inc"

    .global _assembly_flanger
    .equ _BUFFER_SIZE,256

    .equ    FRECUENCIA_DE_MUESTREO,44211                    ;[Hz] = [muestras/segundo]

    .equ    FLANGER_MEDIO,FRECUENCIA_DE_MUESTREO/200        ;[Hz*seg]=[muestras]    F/200  = F*0.005
    .equ    FLANGER_OFFSET,FRECUENCIA_DE_MUESTREO/1000      ;[Hz*seg]=[muestras]    F/1000 = F*0.0001
    .equ    FLANGER_DEPTH,0x6000                            ;0x6000  = 0.75 (?)
    .equ    FLANGER_LENGHT,(256*10)-1
    .equ    FLANGER_REPEAT,17

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
    ADD     W4,W2,W8
    MOV     #FLANGER_OFFSET,W6
    MOV     #FLANGER_MEDIO,W9
    MOV     #FLANGER_REPEAT,W11
    MOV     #0x0000,W12

    ;w0  = BufferC o D (salida)
    ;w1  = BufferA o B(entrada)
    ;w2  = numsamp
    ;w3  = Vector de delay
    ;w4  = LIBRE
    ;w5  = Vector de la señal de Flanger (-1 < W4 < 1)
    ;w6  = flanger offset
    ;w7  = LIBRE    (En DO guardo la entrada)
    ;w8  = posicion del vector entrada grande
    ;w9  = flanger medio
;--------------------------------------------
;            CORRELACIÓN EN C
;        fractional BufferC/D[NUMSAMP] = W0 = &BufferC[0] ó &BufferD[0]
;        fractional BufferA/B[NUMSAMP] = W1 = &BufferA[0] ó &BufferB[0]
;        int numsamp = W2 = NUMSAMP
;        fractional Delay[LENGHTFDELAY] = W3 = &ENTRADA[0]
;        int aux1 = W4 (libre)
;        fractional Flanger[LENGHTFLANGER] = W5 = &FLANGER[0]
;        int flanger_offset = W6 = #FLANGER_OFFSET
;        int aux2 = W7 (libre)
;        int pos_delay = W8 = flanger_paso*NUMSAMP + NUMSAMP - 1
;        int flanger_medio = W9 = #FLANGER_MEDIO
;
;        for(int count=numsamp; count > 0; count--)
;        {
;            Delay[pos_delay] = *BufferA/B;
;            aux2 = *(BufferA/B++);
;            aux1 = *(Flanger++);
;            aux1 *= flanger_offset;
;            aux1 += flanger_medio;
;            aux1 += count;
;            aux1 += pos_delay;
;            aux1 *= #MOV_PTR;   //para mover el puntero una cantidad permitida
;            if(W4 > numsamp) aux1 -= numsamp;
;            aux1 = Delay[aux1];
;            aux2 += aux1;
;            pos_delay--;
;            *(BufferC/D++) = aux2;
;        }
;--------------------------------------------

    DO      W2,final
            NOP

    MUL.UU  W8,#0x0002,W10
    MOV     [W1],[W3+W10]               ;guardo entrada para futuro delay

    MOV     [W1++],W7                   ;Guardo entrada en w7
    ;MOV     #0,W7                   ;Guardo entrada en w7

    MOV     [W5],W4                   ;señal del flanger


    CLR     A
    MPY     W6*W4,A                     ;A = #_OFFSET * señal de Flanger
    SAC     A,W4

    ADD     W4,W9,W4                    ;W4 = (#FLANGER_OFFSET * señal de FLANGERFlanger) + #FLANGER_MEDIO

    ADD     W4,W8,W4                    ;W4 = (#FLANGER_OFFSET * señal de Flanger) + #FLANGER_MEDIO + Pos_delay

    MOV     W5,W13                      ;BUG

    MOV     #FLANGER_LENGHT,W12
    SUB     W12,W4,W10                   ;W10 = FLANGER_LENGHT - W4 (Se setea SR)
    BTSC    SR,#3                       ;Si W4 > FLANGER_LENGHT (miro bit N del SR), hago lo siguiente:
    SUB     W4,W12,W4                    ;Doy la vuelta del vector de entrada grande

    MUL.UU  W4,#0x0002,W4

    MOV     [W3+W4],W10                 ;Vector de entrada(grande) corrido

    ADD     W7,W10,W7                   ;Entrada + flanger

    DEC     W11,W11
    CPSEQ   W11,W12
    BRA     casi_final

    MOV     #FLANGER_REPEAT,W11
    INC2     W5,W5                       ;Incremento posicion del vector Flanger

casi_final:
    MOV     W13,W5                      ;Recupero del BUG (seno)
    DEC     W8,W8                       ;Decremento posicion del vector entrada grande

    final: MOV W7,[W0++]
;--------------------------------------------


    POP	    CORCON
    POP     ACCBL
    POP     ACCBH
    POP     ACCAL
    POP     ACCAH

    RETURN

    .end
