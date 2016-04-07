.equ NUMSAMP,#256           ;Cantidad de muestras del buffer
.equ NUMSAMP_1,#255         ;(Cantidad - 1) de muestras del buffer
.equ NUMSAMP_2,#254         ;(Cantidad - 1) de muestras del buffer
.equ POW_NUMSAMP,#8         ;N tal que 2^N = NUMSAMP
.equ POW_NUMSAMP_7,#1       ;N tal que 2^(N+7) = NUMSAMP
.equ INV_NUMSAMP,#0x0080    ;inversa de NUMSAMP: 0x0080 = 1/256; 0x0010 = 1/2048
.equ CANT_M,#6              ;Cantidad de armonicos que analizo hacia abajo a partir del maximo
.equ CANT_M_2,#4            ;(Cantidad - 2) de armonicos que analizo hacia abajo a partir del maximo



