/**********************************************************************
* © 2005 Microchip Technology Inc.
*
* FileName:        twiddleFactors.c
* Dependencies:    Header (.h) files if applicable}, see below
* Processor:       dsPIC30Fxxxx
* Compiler:        MPLAB® C30 v3.00 or higher
* IDE:             MPLAB® IDE v7.52 or later
* Dev. Board Used: dsPICDEM 1.1 Development Board
* Hardware Dependencies: None
*
* SOFTWARE LICENSE AGREEMENT:
* Microchip Technology Incorporated ("Microchip") retains all ownership and
* intellectual property rights in the code accompanying this message and in all
* derivatives hereto.  You may use this code}, and any derivatives created by
* any person or entity by or on your behalf}, exclusively with Microchip's
* proprietary products.  Your acceptance and/or use of this code constitutes
* agreement to the terms and conditions of this notice.
*
* CODE ACCOMPANYING THIS MESSAGE IS SUPPLIED BY MICROCHIP "AS IS".  NO
* WARRANTIES}, WHETHER EXPRESS}, IMPLIED OR STATUTORY}, INCLUDING}, BUT NOT LIMITED
* TO}, IMPLIED WARRANTIES OF NON-INFRINGEMENT}, MERCHANTABILITY AND FITNESS FOR A
* PARTICULAR PURPOSE APPLY TO THIS CODE}, ITS INTERACTION WITH MICROCHIP'S
* PRODUCTS}, COMBINATION WITH ANY OTHER PRODUCTS}, OR USE IN ANY APPLICATION.
*
* YOU ACKNOWLEDGE AND AGREE THAT}, IN NO EVENT}, SHALL MICROCHIP BE LIABLE}, WHETHER
* IN CONTRACT}, WARRANTY}, TORT (INCLUDING NEGLIGENCE OR BREACH OF STATUTORY DUTY)},
* STRICT LIABILITY}, INDEMNITY}, CONTRIBUTION}, OR OTHERWISE}, FOR ANY INDIRECT}, SPECIAL},
* PUNITIVE}, EXEMPLARY}, INCIDENTAL OR CONSEQUENTIAL LOSS}, DAMAGE}, FOR COST OR EXPENSE OF
* ANY KIND WHATSOEVER RELATED TO THE CODE}, HOWSOEVER CAUSED}, EVEN IF MICROCHIP HAS BEEN
* ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
* ALLOWABLE BY LAW}, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY RELATED TO
* THIS CODE}, SHALL NOT EXCEED THE PRICE YOU PAID DIRECTLY TO MICROCHIP SPECIFICALLY TO
* HAVE THIS CODE DEVELOPED.
*
* You agree that you are solely responsible for testing the code and
* determining its suitability.  Microchip has no obligation to modify, test,
* certify}, or support the code.
*
* REVISION HISTORY:
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Author            Date      Comments on this revision
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* HV               09/30/05  First release of source file
*
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*
* ADDITIONAL NOTES:
*
*
**********************************************************************/

#include <dsp.h>
#include "../h/fft.h"

void init_twiddleFactor_real(fractional *twiddleFactors_real)
{
    #if (FFT_BLOCK_LENGTH == 64)
            twiddleFactors_real[0] = 0x7FFF;
            twiddleFactors_real[1] = 0x7F62;
            twiddleFactors_real[2] = 0x7D8A;
            twiddleFactors_real[3] = 0x7A7D;
            twiddleFactors_real[4] = 0x7642;
            twiddleFactors_real[5] = 0x70E3;
            twiddleFactors_real[6] = 0x6A6E;
            twiddleFactors_real[7] = 0x62F2;
            twiddleFactors_real[8] = 0x5A82;
            twiddleFactors_real[9] = 0x5134;
            twiddleFactors_real[10] = 0x471D;
            twiddleFactors_real[11] = 0x3C57;
            twiddleFactors_real[12] = 0x30FC;
            twiddleFactors_real[13] = 0x2528;
            twiddleFactors_real[14] = 0x18F9;
            twiddleFactors_real[15] = 0x0C8C;
            twiddleFactors_real[16] = 0x0000;
            twiddleFactors_real[17] = 0xF374;
            twiddleFactors_real[18] = 0xE707;
            twiddleFactors_real[19] = 0xDAD8;
            twiddleFactors_real[20] = 0xCF04;
            twiddleFactors_real[21] = 0xC3A9;
            twiddleFactors_real[22] = 0xB8E3;
            twiddleFactors_real[23] = 0xAECC;
            twiddleFactors_real[24] = 0xA57D;
            twiddleFactors_real[25] = 0x9D0E;
            twiddleFactors_real[26] = 0x9592;
            twiddleFactors_real[27] = 0x8F1D;
            twiddleFactors_real[28] = 0x89BE;
            twiddleFactors_real[29] = 0x8583;
            twiddleFactors_real[30] = 0x8276;
            twiddleFactors_real[31] = 0x809E;
    #endif
    #if (FFT_BLOCK_LENGTH == 128)
            const fractcomplex twiddleFactors[] __attribute__ ((space(auto_psv), aligned (FFT_BLOCK_LENGTH*2)))=
            {
            {0x7FFF}, {0x0000}, {0x7FD9}, {0xF9B8}, {0x7F62}, {0xF374}, {0x7E9D}, {0xED38},
            {0x7D8A}, {0xE707}, {0x7C2A}, {0xE0E6}, {0x7A7D}, {0xDAD8}, {0x7885}, {0xD4E1},
            {0x7642}, {0xCF04}, {0x73B6}, {0xC946}, {0x70E3}, {0xC3A9}, {0x6DCA}, {0xBE32},
            {0x6A6E}, {0xB8E3}, {0x66D0}, {0xB3C0}, {0x62F2}, {0xAECC}, {0x5ED7}, {0xAA0A},
            {0x5A82}, {0xA57E}, {0x55F6}, {0xA129}, {0x5134}, {0x9D0E}, {0x4C40}, {0x9930},
            {0x471D}, {0x9592}, {0x41CE}, {0x9236}, {0x3C57}, {0x8F1D}, {0x36BA}, {0x8C4A},
            {0x30FC}, {0x89BE}, {0x2B1F}, {0x877B}, {0x2528}, {0x8583}, {0x1F1A}, {0x83D6},
            {0x18F9}, {0x8276}, {0x12C8}, {0x8163}, {0x0C8C}, {0x809E}, {0x0648}, {0x8027},
            {0x0000}, {0x8000}, {0xF9B8}, {0x8027}, {0xF374}, {0x809E}, {0xED38}, {0x8163},
            {0xE707}, {0x8276}, {0xE0E6}, {0x83D6}, {0xDAD8}, {0x8583}, {0xD4E1}, {0x877C},
            {0xCF04}, {0x89BE}, {0xC946}, {0x8C4A}, {0xC3A9}, {0x8F1D}, {0xBE32}, {0x9236},
            {0xB8E3}, {0x9592}, {0xB3C0}, {0x9931}, {0xAECC}, {0x9D0E}, {0xAA0A}, {0xA129},
            {0xA57E}, {0xA57E}, {0xA129}, {0xAA0A}, {0x9D0E}, {0xAECC}, {0x9931}, {0xB3C0},
            {0x9592}, {0xB8E3}, {0x9236}, {0xBE32}, {0x8F1D}, {0xC3A9}, {0x8C4A}, {0xC946},
            {0x89BE}, {0xCF04}, {0x877C}, {0xD4E1}, {0x8583}, {0xDAD8}, {0x83D6}, {0xE0E6},
            {0x8276}, {0xE707}, {0x8163}, {0xED38}, {0x809E}, {0xF374}, {0x8027}, {0xF9B8}
            } ;
    #endif
    #if (FFT_BLOCK_LENGTH == 256)
            twiddleFactors_real[0] = 0x7FFF;
            twiddleFactors_real[1] = 0x7FF6;
            twiddleFactors_real[2] = 0x7FD9;
            twiddleFactors_real[3] = 0x7FA7;
            
            twiddleFactors_real[4] = 0x7F62;
            twiddleFactors_real[5] = 0x7F0A;
            twiddleFactors_real[6] = 0x7E9D;
            twiddleFactors_real[7] = 0x7E1E;

            twiddleFactors_real[8] = 0x7D8A;
            twiddleFactors_real[9] = 0x7CE4;
            twiddleFactors_real[10] = 0x7C2A;
            twiddleFactors_real[11] = 0x7B5D;
            
            twiddleFactors_real[12] = 0x7A7D;
            twiddleFactors_real[13] = 0x798A;
            twiddleFactors_real[14] = 0x7884;
            twiddleFactors_real[15] = 0x776C;

            twiddleFactors_real[16] = 0x7642;
            twiddleFactors_real[17] = 0x7505;
            twiddleFactors_real[18] = 0x73B6;
            twiddleFactors_real[19] = 0x7255;
            
            twiddleFactors_real[20] = 0x70E3;
            twiddleFactors_real[21] = 0x6F5F;
            twiddleFactors_real[22] = 0x6DCA;
            twiddleFactors_real[23] = 0x6C24;

            twiddleFactors_real[24] = 0x6A6E;
            twiddleFactors_real[25] = 0x68A7;
            twiddleFactors_real[26] = 0x66CF;
            twiddleFactors_real[27] = 0x64E8;
            
            twiddleFactors_real[28] = 0x62F2;
            twiddleFactors_real[29] = 0x60EC;
            twiddleFactors_real[30] = 0x5ED7;
            twiddleFactors_real[31] = 0x5CB4;

            twiddleFactors_real[32] = 0x5A82;
            twiddleFactors_real[33] = 0x5843;
            twiddleFactors_real[34] = 0x55F6;
            twiddleFactors_real[35] = 0x539B;

            twiddleFactors_real[36] = 0x5134;
            twiddleFactors_real[37] = 0x4EC0;
            twiddleFactors_real[38] = 0x4C40;
            twiddleFactors_real[39] = 0x49B4;

            twiddleFactors_real[40] = 0x471D;
            twiddleFactors_real[41] = 0x447B;
            twiddleFactors_real[42] = 0x41CE;
            twiddleFactors_real[43] = 0x3F17;

            twiddleFactors_real[44] = 0x3C57;
            twiddleFactors_real[45] = 0x398D;
            twiddleFactors_real[46] = 0x36BA;
            twiddleFactors_real[47] = 0x33DF;

            twiddleFactors_real[48] = 0x30FC;
            twiddleFactors_real[49] = 0x2E11;
            twiddleFactors_real[50] = 0x2B1F;
            twiddleFactors_real[51] = 0x2827;

            twiddleFactors_real[52] = 0x2528;
            twiddleFactors_real[53] = 0x2224;
            twiddleFactors_real[54] = 0x1F1A;
            twiddleFactors_real[55] = 0x1C0B;

            twiddleFactors_real[56] = 0x18F9;
            twiddleFactors_real[57] = 0x15E2;
            twiddleFactors_real[58] = 0x12C8;
            twiddleFactors_real[59] = 0x0FAB;

            twiddleFactors_real[60] = 0x0C8C;
            twiddleFactors_real[61] = 0x096B;
            twiddleFactors_real[62] = 0x0648;
            twiddleFactors_real[63] = 0x0324;

            twiddleFactors_real[64] = 0x0000;
            twiddleFactors_real[65] = 0xFCDC;
            twiddleFactors_real[66] = 0xF9B8;
            twiddleFactors_real[67] = 0xF695;

            twiddleFactors_real[68] = 0xF374;
            twiddleFactors_real[69] = 0xF055;
            twiddleFactors_real[70] = 0xED38;
            twiddleFactors_real[71] = 0xEA1E;

            twiddleFactors_real[72] = 0xE707;
            twiddleFactors_real[73] = 0xE3F5;
            twiddleFactors_real[74] = 0xE0E6;
            twiddleFactors_real[75] = 0xDDDC;

            twiddleFactors_real[76] = 0xDAD8;
            twiddleFactors_real[77] = 0xD7D9;
            twiddleFactors_real[78] = 0xD4E1;
            twiddleFactors_real[79] = 0xD1EF;

            twiddleFactors_real[80] = 0xCF04;
            twiddleFactors_real[81] = 0xCC21;
            twiddleFactors_real[82] = 0xC946;
            twiddleFactors_real[83] = 0xC673;

            twiddleFactors_real[84] = 0xC3A9;
            twiddleFactors_real[85] = 0xC0E9;
            twiddleFactors_real[86] = 0xBE32;
            twiddleFactors_real[87] = 0xBB85;

            twiddleFactors_real[88] = 0xB8E3;
            twiddleFactors_real[89] = 0xB64C;
            twiddleFactors_real[90] = 0xB3C0;
            twiddleFactors_real[91] = 0xB140;

            twiddleFactors_real[92] = 0xAECC;
            twiddleFactors_real[93] = 0xAC65;
            twiddleFactors_real[94] = 0xAA0A;
            twiddleFactors_real[95] = 0xA7BD;

            twiddleFactors_real[96] = 0xA57E;
            twiddleFactors_real[97] = 0xA34C;
            twiddleFactors_real[98] = 0xA129;
            twiddleFactors_real[99] = 0x9F14;

            twiddleFactors_real[100] = 0x9D0E;
            twiddleFactors_real[101] = 0x9B18;
            twiddleFactors_real[102] = 0x9931;
            twiddleFactors_real[103] = 0x975A;

            twiddleFactors_real[104] = 0x9593;
            twiddleFactors_real[105] = 0x93DC;
            twiddleFactors_real[106] = 0x9236;
            twiddleFactors_real[107] = 0x90A1;

            twiddleFactors_real[108] = 0x8F1D;
            twiddleFactors_real[109] = 0x8DAB;
            twiddleFactors_real[110] = 0x8C4A;
            twiddleFactors_real[111] = 0x8AFB;

            twiddleFactors_real[112] = 0x89BF;
            twiddleFactors_real[113] = 0x8894;
            twiddleFactors_real[114] = 0x877C;
            twiddleFactors_real[115] = 0x8676;

            twiddleFactors_real[116] = 0x8583;
            twiddleFactors_real[117] = 0x84A3;
            twiddleFactors_real[118] = 0x83D6;
            twiddleFactors_real[119] = 0x831C;

            twiddleFactors_real[120] = 0x8276;
            twiddleFactors_real[121] = 0x81E3;
            twiddleFactors_real[122] = 0x8163;
            twiddleFactors_real[123] = 0x80F7;

            twiddleFactors_real[124] = 0x809E;
            twiddleFactors_real[125] = 0x8059;
            twiddleFactors_real[126] = 0x8028;
            twiddleFactors_real[127] = 0x800A;
    #endif
    #if (FFT_BLOCK_LENGTH == 512 )
            const fractcomplex twiddleFactors[] __attribute__ ((space(auto_psv), aligned (FFT_BLOCK_LENGTH*2*2))) =
            {
            {0x7FFF}, {0x0000}, {0x7FFE}, {0xFE6E}, {0x7FF6}, {0xFCDC}, {0x7FEA}, {0xFB4A},
            {0x7FD9}, {0xF9B8}, {0x7FC2}, {0xF827}, {0x7FA7}, {0xF695}, {0x7F87}, {0xF505},
            {0x7F62}, {0xF374}, {0x7F38}, {0xF1E4}, {0x7F0A}, {0xF055}, {0x7ED6}, {0xEEC6},
            {0x7E9D}, {0xED38}, {0x7E60}, {0xEBAB}, {0x7E1E}, {0xEA1E}, {0x7DD6}, {0xE892},
            {0x7D8A}, {0xE707}, {0x7D3A}, {0xE57D}, {0x7CE4}, {0xE3F4}, {0x7C89}, {0xE26D},
            {0x7C2A}, {0xE0E6}, {0x7BC6}, {0xDF61}, {0x7B5D}, {0xDDDC}, {0x7AEF}, {0xDC59},
            {0x7A7D}, {0xDAD8}, {0x7A06}, {0xD958}, {0x798A}, {0xD7D9}, {0x790A}, {0xD65C},
            {0x7885}, {0xD4E1}, {0x77FB}, {0xD367}, {0x776C}, {0xD1EF}, {0x76D9}, {0xD079},
            {0x7642}, {0xCF04}, {0x75A6}, {0xCD92}, {0x7505}, {0xCC21}, {0x7460}, {0xCAB2},
            {0x73B6}, {0xC946}, {0x7308}, {0xC7DB}, {0x7255}, {0xC673}, {0x719E}, {0xC50D},
            {0x70E3}, {0xC3A9}, {0x7023}, {0xC248}, {0x6F5F}, {0xC0E9}, {0x6E97}, {0xBF8C},
            {0x6DCA}, {0xBE32}, {0x6CF9}, {0xBCDA}, {0x6C24}, {0xBB85}, {0x6B4B}, {0xBA33},
            {0x6A6E}, {0xB8E3}, {0x698C}, {0xB796}, {0x68A7}, {0xB64C}, {0x67BD}, {0xB505},
            {0x66D0}, {0xB3C0}, {0x65DE}, {0xB27F}, {0x64E9}, {0xB140}, {0x63EF}, {0xB005},
            {0x62F2}, {0xAECC}, {0x61F1}, {0xAD97}, {0x60EC}, {0xAC65}, {0x5FE4}, {0xAB36},
            {0x5ED8}, {0xAA0A}, {0x5DC8}, {0xA8E2}, {0x5CB4}, {0xA7BD}, {0x5B9D}, {0xA69C},
            {0x5A83}, {0xA57E}, {0x5964}, {0xA463}, {0x5843}, {0xA34C}, {0x571E}, {0xA238},
            {0x55F6}, {0xA128}, {0x54CA}, {0xA01C}, {0x539B}, {0x9F14}, {0x5269}, {0x9E0F},
            {0x5134}, {0x9D0E}, {0x4FFB}, {0x9C11}, {0x4EC0}, {0x9B17}, {0x4D81}, {0x9A22},
            {0x4C40}, {0x9930}, {0x4AFB}, {0x9843}, {0x49B4}, {0x9759}, {0x486A}, {0x9674},
            {0x471D}, {0x9592}, {0x45CD}, {0x94B5}, {0x447B}, {0x93DC}, {0x4326}, {0x9307},
            {0x41CE}, {0x9236}, {0x4074}, {0x9169}, {0x3F17}, {0x90A1}, {0x3DB8}, {0x8FDD},
            {0x3C57}, {0x8F1D}, {0x3AF3}, {0x8E62}, {0x398D}, {0x8DAB}, {0x3825}, {0x8CF8},
            {0x36BA}, {0x8C4A}, {0x354E}, {0x8BA0}, {0x33DF}, {0x8AFB}, {0x326E}, {0x8A5A},
            {0x30FC}, {0x89BE}, {0x2F87}, {0x8927}, {0x2E11}, {0x8894}, {0x2C99}, {0x8805},
            {0x2B1F}, {0x877B}, {0x29A4}, {0x86F6}, {0x2827}, {0x8676}, {0x26A8}, {0x85FA},
            {0x2528}, {0x8583}, {0x23A7}, {0x8511}, {0x2224}, {0x84A3}, {0x209F}, {0x843A},
            {0x1F1A}, {0x83D6}, {0x1D93}, {0x8377}, {0x1C0C}, {0x831C}, {0x1A83}, {0x82C6},
            {0x18F9}, {0x8276}, {0x176E}, {0x822A}, {0x15E2}, {0x81E2}, {0x1455}, {0x81A0},
            {0x12C8}, {0x8163}, {0x113A}, {0x812A}, {0x0FAB}, {0x80F6}, {0x0E1C}, {0x80C8},
            {0x0C8C}, {0x809E}, {0x0AFB}, {0x8079}, {0x096B}, {0x8059}, {0x07D9}, {0x803E},
            {0x0648}, {0x8027}, {0x04B6}, {0x8016}, {0x0324}, {0x800A}, {0x0192}, {0x8002},
            {0x0000}, {0x8000}, {0xFE6E}, {0x8002}, {0xFCDC}, {0x800A}, {0xFB4A}, {0x8016},
            {0xF9B8}, {0x8027}, {0xF827}, {0x803E}, {0xF695}, {0x8059}, {0xF505}, {0x8079},
            {0xF374}, {0x809E}, {0xF1E4}, {0x80C8}, {0xF055}, {0x80F6}, {0xEEC6}, {0x812A},
            {0xED38}, {0x8163}, {0xEBAB}, {0x81A0}, {0xEA1E}, {0x81E2}, {0xE892}, {0x822A},
            {0xE707}, {0x8276}, {0xE57D}, {0x82C6}, {0xE3F4}, {0x831C}, {0xE26D}, {0x8377},
            {0xE0E6}, {0x83D6}, {0xDF61}, {0x843A}, {0xDDDC}, {0x84A3}, {0xDC59}, {0x8511},
            {0xDAD8}, {0x8583}, {0xD958}, {0x85FA}, {0xD7D9}, {0x8676}, {0xD65C}, {0x86F6},
            {0xD4E1}, {0x877B}, {0xD367}, {0x8805}, {0xD1EF}, {0x8894}, {0xD079}, {0x8927},
            {0xCF04}, {0x89BE}, {0xCD92}, {0x8A5A}, {0xCC21}, {0x8AFB}, {0xCAB2}, {0x8BA0},
            {0xC946}, {0x8C4A}, {0xC7DB}, {0x8CF8}, {0xC673}, {0x8DAB}, {0xC50D}, {0x8E62},
            {0xC3A9}, {0x8F1D}, {0xC248}, {0x8FDD}, {0xC0E9}, {0x90A1}, {0xBF8C}, {0x9169},
            {0xBE32}, {0x9236}, {0xBCDA}, {0x9307}, {0xBB85}, {0x93DC}, {0xBA33}, {0x94B5},
            {0xB8E3}, {0x9592}, {0xB796}, {0x9674}, {0xB64C}, {0x9759}, {0xB505}, {0x9843},
            {0xB3C0}, {0x9930}, {0xB27F}, {0x9A22}, {0xB140}, {0x9B17}, {0xB005}, {0x9C11},
            {0xAECC}, {0x9D0E}, {0xAD97}, {0x9E0F}, {0xAC65}, {0x9F14}, {0xAB36}, {0xA01C},
            {0xAA0A}, {0xA128}, {0xA8E2}, {0xA238}, {0xA7BD}, {0xA34C}, {0xA69C}, {0xA463},
            {0xA57D}, {0xA57D}, {0xA463}, {0xA69C}, {0xA34C}, {0xA7BD}, {0xA238}, {0xA8E2},
            {0xA128}, {0xAA0A}, {0xA01C}, {0xAB36}, {0x9F14}, {0xAC65}, {0x9E0F}, {0xAD97},
            {0x9D0E}, {0xAECC}, {0x9C11}, {0xB005}, {0x9B17}, {0xB140}, {0x9A22}, {0xB27F},
            {0x9930}, {0xB3C0}, {0x9843}, {0xB504}, {0x9759}, {0xB64C}, {0x9674}, {0xB796},
            {0x9592}, {0xB8E3}, {0x94B5}, {0xBA33}, {0x93DC}, {0xBB85}, {0x9307}, {0xBCDA},
            {0x9236}, {0xBE32}, {0x9169}, {0xBF8C}, {0x90A1}, {0xC0E9}, {0x8FDD}, {0xC248},
            {0x8F1D}, {0xC3A9}, {0x8E62}, {0xC50D}, {0x8DAB}, {0xC673}, {0x8CF8}, {0xC7DB},
            {0x8C4A}, {0xC946}, {0x8BA0}, {0xCAB2}, {0x8AFB}, {0xCC21}, {0x8A5A}, {0xCD92},
            {0x89BE}, {0xCF04}, {0x8927}, {0xD079}, {0x8894}, {0xD1EF}, {0x8805}, {0xD367},
            {0x877B}, {0xD4E1}, {0x86F6}, {0xD65C}, {0x8676}, {0xD7D9}, {0x85FA}, {0xD958},
            {0x8583}, {0xDAD8}, {0x8510}, {0xDC59}, {0x84A3}, {0xDDDC}, {0x843A}, {0xDF61},
            {0x83D6}, {0xE0E6}, {0x8377}, {0xE26D}, {0x831C}, {0xE3F4}, {0x82C6}, {0xE57D},
            {0x8275}, {0xE707}, {0x8229}, {0xE892}, {0x81E2}, {0xEA1E}, {0x81A0}, {0xEBAB},
            {0x8163}, {0xED38}, {0x812A}, {0xEEC6}, {0x80F6}, {0xF055}, {0x80C8}, {0xF1E4},
            {0x809E}, {0xF374}, {0x8079}, {0xF505}, {0x8059}, {0xF695}, {0x803E}, {0xF827},
            {0x8027}, {0xF9B8}, {0x8016}, {0xFB4A}, {0x800A}, {0xFCDC}, {0x8002}, {0xFE6E}
            } ;
    #endif
}