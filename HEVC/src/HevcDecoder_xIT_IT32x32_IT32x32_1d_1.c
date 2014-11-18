// Source file is "L/RVC/src/org/sc29/wg11/mpegh/part2/main/IT/IT32x32_1d.cal"

#include <stdio.h>
#include <stdlib.h>
#include "config.h"

#include "types.h"
#include "fifo.h"
#include "util.h"
#include "scheduler.h"
#include "dataflow.h"
#include "cycle.h"

#define SIZE 8192

////////////////////////////////////////////////////////////////////////////////
// Instance
extern actor_t HevcDecoder_xIT_IT32x32_IT32x32_1d_1;

////////////////////////////////////////////////////////////////////////////////
// Input FIFOs
extern fifo_i16_t *HevcDecoder_xIT_IT32x32_IT32x32_1d_1_Src;

////////////////////////////////////////////////////////////////////////////////
// Input Fifo control variables
static unsigned int index_Src;
static unsigned int numTokens_Src;
#define SIZE_Src SIZE
#define tokens_Src HevcDecoder_xIT_IT32x32_IT32x32_1d_1_Src->contents

extern connection_t connection_HevcDecoder_xIT_IT32x32_IT32x32_1d_1_Src;
#define rate_Src connection_HevcDecoder_xIT_IT32x32_IT32x32_1d_1_Src.rate

////////////////////////////////////////////////////////////////////////////////
// Predecessors
extern actor_t HevcDecoder_xIT_IT32x32_Transpose32x32_1;

////////////////////////////////////////////////////////////////////////////////
// Output FIFOs
extern fifo_i16_t *HevcDecoder_xIT_IT32x32_IT32x32_1d_1_Dst;

////////////////////////////////////////////////////////////////////////////////
// Output Fifo control variables
static unsigned int index_Dst;
static unsigned int numFree_Dst;
#define NUM_READERS_Dst 1
#define SIZE_Dst SIZE
#define tokens_Dst HevcDecoder_xIT_IT32x32_IT32x32_1d_1_Dst->contents

////////////////////////////////////////////////////////////////////////////////
// Successors
extern actor_t HevcDecoder_xIT_IT_Merger;

////////////////////////////////////////////////////////////////////////////////
// Parameter values of the instance
#define shift 12


////////////////////////////////////////////////////////////////////////////////
// State variables of the actor
static const i8 HevcDecoder_xIT_IT32x32_IT32x32_1d_1_g_aiT32[32][32] = {{64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64}, {90, 90, 88, 85, 82, 78, 73, 67, 61, 54, 46, 38, 31, 22, 13, 4, -4, -13, -22, -31, -38, -46, -54, -61, -67, -73, -78, -82, -85, -88, -90, -90}, {90, 87, 80, 70, 57, 43, 25, 9, -9, -25, -43, -57, -70, -80, -87, -90, -90, -87, -80, -70, -57, -43, -25, -9, 9, 25, 43, 57, 70, 80, 87, 90}, {90, 82, 67, 46, 22, -4, -31, -54, -73, -85, -90, -88, -78, -61, -38, -13, 13, 38, 61, 78, 88, 90, 85, 73, 54, 31, 4, -22, -46, -67, -82, -90}, {89, 75, 50, 18, -18, -50, -75, -89, -89, -75, -50, -18, 18, 50, 75, 89, 89, 75, 50, 18, -18, -50, -75, -89, -89, -75, -50, -18, 18, 50, 75, 89}, {88, 67, 31, -13, -54, -82, -90, -78, -46, -4, 38, 73, 90, 85, 61, 22, -22, -61, -85, -90, -73, -38, 4, 46, 78, 90, 82, 54, 13, -31, -67, -88}, {87, 57, 9, -43, -80, -90, -70, -25, 25, 70, 90, 80, 43, -9, -57, -87, -87, -57, -9, 43, 80, 90, 70, 25, -25, -70, -90, -80, -43, 9, 57, 87}, {85, 46, -13, -67, -90, -73, -22, 38, 82, 88, 54, -4, -61, -90, -78, -31, 31, 78, 90, 61, 4, -54, -88, -82, -38, 22, 73, 90, 67, 13, -46, -85}, {83, 36, -36, -83, -83, -36, 36, 83, 83, 36, -36, -83, -83, -36, 36, 83, 83, 36, -36, -83, -83, -36, 36, 83, 83, 36, -36, -83, -83, -36, 36, 83}, {82, 22, -54, -90, -61, 13, 78, 85, 31, -46, -90, -67, 4, 73, 88, 38, -38, -88, -73, -4, 67, 90, 46, -31, -85, -78, -13, 61, 90, 54, -22, -82}, {80, 9, -70, -87, -25, 57, 90, 43, -43, -90, -57, 25, 87, 70, -9, -80, -80, -9, 70, 87, 25, -57, -90, -43, 43, 90, 57, -25, -87, -70, 9, 80}, {78, -4, -82, -73, 13, 85, 67, -22, -88, -61, 31, 90, 54, -38, -90, -46, 46, 90, 38, -54, -90, -31, 61, 88, 22, -67, -85, -13, 73, 82, 4, -78}, {75, -18, -89, -50, 50, 89, 18, -75, -75, 18, 89, 50, -50, -89, -18, 75, 75, -18, -89, -50, 50, 89, 18, -75, -75, 18, 89, 50, -50, -89, -18, 75}, {73, -31, -90, -22, 78, 67, -38, -90, -13, 82, 61, -46, -88, -4, 85, 54, -54, -85, 4, 88, 46, -61, -82, 13, 90, 38, -67, -78, 22, 90, 31, -73}, {70, -43, -87, 9, 90, 25, -80, -57, 57, 80, -25, -90, -9, 87, 43, -70, -70, 43, 87, -9, -90, -25, 80, 57, -57, -80, 25, 90, 9, -87, -43, 70}, {67, -54, -78, 38, 85, -22, -90, 4, 90, 13, -88, -31, 82, 46, -73, -61, 61, 73, -46, -82, 31, 88, -13, -90, -4, 90, 22, -85, -38, 78, 54, -67}, {64, -64, -64, 64, 64, -64, -64, 64, 64, -64, -64, 64, 64, -64, -64, 64, 64, -64, -64, 64, 64, -64, -64, 64, 64, -64, -64, 64, 64, -64, -64, 64}, {61, -73, -46, 82, 31, -88, -13, 90, -4, -90, 22, 85, -38, -78, 54, 67, -67, -54, 78, 38, -85, -22, 90, 4, -90, 13, 88, -31, -82, 46, 73, -61}, {57, -80, -25, 90, -9, -87, 43, 70, -70, -43, 87, 9, -90, 25, 80, -57, -57, 80, 25, -90, 9, 87, -43, -70, 70, 43, -87, -9, 90, -25, -80, 57}, {54, -85, -4, 88, -46, -61, 82, 13, -90, 38, 67, -78, -22, 90, -31, -73, 73, 31, -90, 22, 78, -67, -38, 90, -13, -82, 61, 46, -88, 4, 85, -54}, {50, -89, 18, 75, -75, -18, 89, -50, -50, 89, -18, -75, 75, 18, -89, 50, 50, -89, 18, 75, -75, -18, 89, -50, -50, 89, -18, -75, 75, 18, -89, 50}, {46, -90, 38, 54, -90, 31, 61, -88, 22, 67, -85, 13, 73, -82, 4, 78, -78, -4, 82, -73, -13, 85, -67, -22, 88, -61, -31, 90, -54, -38, 90, -46}, {43, -90, 57, 25, -87, 70, 9, -80, 80, -9, -70, 87, -25, -57, 90, -43, -43, 90, -57, -25, 87, -70, -9, 80, -80, 9, 70, -87, 25, 57, -90, 43}, {38, -88, 73, -4, -67, 90, -46, -31, 85, -78, 13, 61, -90, 54, 22, -82, 82, -22, -54, 90, -61, -13, 78, -85, 31, 46, -90, 67, 4, -73, 88, -38}, {36, -83, 83, -36, -36, 83, -83, 36, 36, -83, 83, -36, -36, 83, -83, 36, 36, -83, 83, -36, -36, 83, -83, 36, 36, -83, 83, -36, -36, 83, -83, 36}, {31, -78, 90, -61, 4, 54, -88, 82, -38, -22, 73, -90, 67, -13, -46, 85, -85, 46, 13, -67, 90, -73, 22, 38, -82, 88, -54, -4, 61, -90, 78, -31}, {25, -70, 90, -80, 43, 9, -57, 87, -87, 57, -9, -43, 80, -90, 70, -25, -25, 70, -90, 80, -43, -9, 57, -87, 87, -57, 9, 43, -80, 90, -70, 25}, {22, -61, 85, -90, 73, -38, -4, 46, -78, 90, -82, 54, -13, -31, 67, -88, 88, -67, 31, 13, -54, 82, -90, 78, -46, 4, 38, -73, 90, -85, 61, -22}, {18, -50, 75, -89, 89, -75, 50, -18, -18, 50, -75, 89, -89, 75, -50, 18, 18, -50, 75, -89, 89, -75, 50, -18, -18, 50, -75, 89, -89, 75, -50, 18}, {13, -38, 61, -78, 88, -90, 85, -73, 54, -31, 4, 22, -46, 67, -82, 90, -90, 82, -67, 46, -22, -4, 31, -54, 73, -85, 90, -88, 78, -61, 38, -13}, {9, -25, 43, -57, 70, -80, 87, -90, 90, -87, 80, -70, 57, -43, 25, -9, -9, 25, -43, 57, -70, 80, -87, 90, -90, 87, -80, 70, -57, 43, -25, 9}, {4, -13, 22, -31, 38, -46, 54, -61, 67, -73, 78, -82, 85, -88, 90, -90, 90, -90, 88, -85, 82, -78, 73, -67, 61, -54, 46, -38, 31, -22, 13, -4}};



////////////////////////////////////////////////////////////////////////////////
// Token functions
static void read_Src() {
	index_Src = HevcDecoder_xIT_IT32x32_IT32x32_1d_1_Src->read_inds[0];
	numTokens_Src = index_Src + fifo_i16_get_num_tokens(HevcDecoder_xIT_IT32x32_IT32x32_1d_1_Src, 0);
}

static void read_end_Src() {
	HevcDecoder_xIT_IT32x32_IT32x32_1d_1_Src->read_inds[0] = index_Src;
}

static void write_Dst() {
	index_Dst = HevcDecoder_xIT_IT32x32_IT32x32_1d_1_Dst->write_ind;
	numFree_Dst = index_Dst + fifo_i16_get_room(HevcDecoder_xIT_IT32x32_IT32x32_1d_1_Dst, NUM_READERS_Dst, SIZE_Dst);
}

static void write_end_Dst() {
	HevcDecoder_xIT_IT32x32_IT32x32_1d_1_Dst->write_ind = index_Dst;
}

////////////////////////////////////////////////////////////////////////////////
// Functions/procedures


////////////////////////////////////////////////////////////////////////////////
// Actions
static i32 isSchedulable_untagged_0() {
	i32 result;

	result = 1;
	return result;
}

static void untagged_0_aligned() {

	i32 evenEvenEvenEven[2];
	i32 evenEvenEvenOdd[2];
	i32 evenEvenEven[4];
	i32 evenEvenOdd[4];
	i32 evenEven[8];
	i32 evenOdd[8];
	i32 even[16];
	i32 odd[16];
	i32 dst[32];
	i32 local_shift;
	i32 rouding_factor;
	i16 tmp_Src;
	i8 tmp_g_aiT32;
	i16 tmp_Src0;
	i8 tmp_g_aiT320;
	i16 tmp_Src1;
	i8 tmp_g_aiT321;
	i16 tmp_Src2;
	i8 tmp_g_aiT322;
	i16 tmp_Src3;
	i8 tmp_g_aiT323;
	i16 tmp_Src4;
	i8 tmp_g_aiT324;
	i16 tmp_Src5;
	i8 tmp_g_aiT325;
	i16 tmp_Src6;
	i8 tmp_g_aiT326;
	i32 tmp_evenEvenEvenEven;
	i32 tmp_evenEvenEvenOdd;
	i32 tmp_evenEvenEvenEven0;
	i32 tmp_evenEvenEvenOdd0;
	i32 tmp_evenEvenEvenEven1;
	i32 tmp_evenEvenEvenOdd1;
	i32 tmp_evenEvenEvenEven2;
	i32 tmp_evenEvenEvenOdd2;
	i32 i;
	i16 tmp_Src7;
	i8 tmp_g_aiT327;
	i16 tmp_Src8;
	i8 tmp_g_aiT328;
	i16 tmp_Src9;
	i8 tmp_g_aiT329;
	i16 tmp_Src10;
	i8 tmp_g_aiT3210;
	i32 tmp_evenEvenEven;
	i32 tmp_evenEvenOdd;
	i32 tmp_evenEvenEven0;
	i32 tmp_evenEvenOdd0;
	i32 tmp_evenEvenEven1;
	i32 tmp_evenEvenOdd1;
	i32 tmp_evenEvenEven2;
	i32 tmp_evenEvenOdd2;
	i32 tmp_evenEvenEven3;
	i32 tmp_evenEvenOdd3;
	i32 tmp_evenEvenEven4;
	i32 tmp_evenEvenOdd4;
	i32 tmp_evenEvenEven5;
	i32 tmp_evenEvenOdd5;
	i32 tmp_evenEvenEven6;
	i32 tmp_evenEvenOdd6;
	i32 i0;
	i16 tmp_Src11;
	i8 tmp_g_aiT3211;
	i16 tmp_Src12;
	i8 tmp_g_aiT3212;
	i16 tmp_Src13;
	i8 tmp_g_aiT3213;
	i16 tmp_Src14;
	i8 tmp_g_aiT3214;
	i16 tmp_Src15;
	i8 tmp_g_aiT3215;
	i16 tmp_Src16;
	i8 tmp_g_aiT3216;
	i16 tmp_Src17;
	i8 tmp_g_aiT3217;
	i16 tmp_Src18;
	i8 tmp_g_aiT3218;
	i32 tmp_evenEven;
	i32 tmp_evenOdd;
	i32 tmp_evenEven0;
	i32 tmp_evenOdd0;
	i32 tmp_evenEven1;
	i32 tmp_evenOdd1;
	i32 tmp_evenEven2;
	i32 tmp_evenOdd2;
	i32 tmp_evenEven3;
	i32 tmp_evenOdd3;
	i32 tmp_evenEven4;
	i32 tmp_evenOdd4;
	i32 tmp_evenEven5;
	i32 tmp_evenOdd5;
	i32 tmp_evenEven6;
	i32 tmp_evenOdd6;
	i32 tmp_evenEven7;
	i32 tmp_evenOdd7;
	i32 tmp_evenEven8;
	i32 tmp_evenOdd8;
	i32 tmp_evenEven9;
	i32 tmp_evenOdd9;
	i32 tmp_evenEven10;
	i32 tmp_evenOdd10;
	i32 tmp_evenEven11;
	i32 tmp_evenOdd11;
	i32 tmp_evenEven12;
	i32 tmp_evenOdd12;
	i32 tmp_evenEven13;
	i32 tmp_evenOdd13;
	i32 tmp_evenEven14;
	i32 tmp_evenOdd14;
	i32 i1;
	i16 tmp_Src19;
	i8 tmp_g_aiT3219;
	i16 tmp_Src20;
	i8 tmp_g_aiT3220;
	i16 tmp_Src21;
	i8 tmp_g_aiT3221;
	i16 tmp_Src22;
	i8 tmp_g_aiT3222;
	i16 tmp_Src23;
	i8 tmp_g_aiT3223;
	i16 tmp_Src24;
	i8 tmp_g_aiT3224;
	i16 tmp_Src25;
	i8 tmp_g_aiT3225;
	i16 tmp_Src26;
	i8 tmp_g_aiT3226;
	i16 tmp_Src27;
	i8 tmp_g_aiT3227;
	i16 tmp_Src28;
	i8 tmp_g_aiT3228;
	i16 tmp_Src29;
	i8 tmp_g_aiT3229;
	i16 tmp_Src30;
	i8 tmp_g_aiT3230;
	i16 tmp_Src31;
	i8 tmp_g_aiT3231;
	i16 tmp_Src32;
	i8 tmp_g_aiT3232;
	i16 tmp_Src33;
	i8 tmp_g_aiT3233;
	i16 tmp_Src34;
	i8 tmp_g_aiT3234;
	i32 tmp_even;
	i32 tmp_odd;
	i32 tmp_even0;
	i32 tmp_odd0;
	i32 tmp_even1;
	i32 tmp_odd1;
	i32 tmp_even2;
	i32 tmp_odd2;
	i32 tmp_even3;
	i32 tmp_odd3;
	i32 tmp_even4;
	i32 tmp_odd4;
	i32 tmp_even5;
	i32 tmp_odd5;
	i32 tmp_even6;
	i32 tmp_odd6;
	i32 tmp_even7;
	i32 tmp_odd7;
	i32 tmp_even8;
	i32 tmp_odd8;
	i32 tmp_even9;
	i32 tmp_odd9;
	i32 tmp_even10;
	i32 tmp_odd10;
	i32 tmp_even11;
	i32 tmp_odd11;
	i32 tmp_even12;
	i32 tmp_odd12;
	i32 tmp_even13;
	i32 tmp_odd13;
	i32 tmp_even14;
	i32 tmp_odd14;
	i32 tmp_even15;
	i32 tmp_odd15;
	i32 tmp_even16;
	i32 tmp_odd16;
	i32 tmp_even17;
	i32 tmp_odd17;
	i32 tmp_even18;
	i32 tmp_odd18;
	i32 tmp_even19;
	i32 tmp_odd19;
	i32 tmp_even20;
	i32 tmp_odd20;
	i32 tmp_even21;
	i32 tmp_odd21;
	i32 tmp_even22;
	i32 tmp_odd22;
	i32 tmp_even23;
	i32 tmp_odd23;
	i32 tmp_even24;
	i32 tmp_odd24;
	i32 tmp_even25;
	i32 tmp_odd25;
	i32 tmp_even26;
	i32 tmp_odd26;
	i32 tmp_even27;
	i32 tmp_odd27;
	i32 tmp_even28;
	i32 tmp_odd28;
	i32 tmp_even29;
	i32 tmp_odd29;
	i32 tmp_even30;
	i32 tmp_odd30;
	i32 i2;
	i32 tmp_dst;

	local_shift = shift;
	rouding_factor = 1 << (local_shift - 1);
	tmp_Src = tokens_Src[(index_Src % SIZE_Src) + (0)];
	tmp_g_aiT32 = HevcDecoder_xIT_IT32x32_IT32x32_1d_1_g_aiT32[0][0];
	tmp_Src0 = tokens_Src[(index_Src % SIZE_Src) + (16)];
	tmp_g_aiT320 = HevcDecoder_xIT_IT32x32_IT32x32_1d_1_g_aiT32[16][0];
	evenEvenEvenEven[0] = tmp_Src * tmp_g_aiT32 + tmp_Src0 * tmp_g_aiT320;
	tmp_Src1 = tokens_Src[(index_Src % SIZE_Src) + (0)];
	tmp_g_aiT321 = HevcDecoder_xIT_IT32x32_IT32x32_1d_1_g_aiT32[0][1];
	tmp_Src2 = tokens_Src[(index_Src % SIZE_Src) + (16)];
	tmp_g_aiT322 = HevcDecoder_xIT_IT32x32_IT32x32_1d_1_g_aiT32[16][1];
	evenEvenEvenEven[1] = tmp_Src1 * tmp_g_aiT321 + tmp_Src2 * tmp_g_aiT322;
	tmp_Src3 = tokens_Src[(index_Src % SIZE_Src) + (8)];
	tmp_g_aiT323 = HevcDecoder_xIT_IT32x32_IT32x32_1d_1_g_aiT32[8][0];
	tmp_Src4 = tokens_Src[(index_Src % SIZE_Src) + (24)];
	tmp_g_aiT324 = HevcDecoder_xIT_IT32x32_IT32x32_1d_1_g_aiT32[24][0];
	evenEvenEvenOdd[0] = tmp_Src3 * tmp_g_aiT323 + tmp_Src4 * tmp_g_aiT324;
	tmp_Src5 = tokens_Src[(index_Src % SIZE_Src) + (8)];
	tmp_g_aiT325 = HevcDecoder_xIT_IT32x32_IT32x32_1d_1_g_aiT32[8][1];
	tmp_Src6 = tokens_Src[(index_Src % SIZE_Src) + (24)];
	tmp_g_aiT326 = HevcDecoder_xIT_IT32x32_IT32x32_1d_1_g_aiT32[24][1];
	evenEvenEvenOdd[1] = tmp_Src5 * tmp_g_aiT325 + tmp_Src6 * tmp_g_aiT326;
	tmp_evenEvenEvenEven = evenEvenEvenEven[0];
	tmp_evenEvenEvenOdd = evenEvenEvenOdd[0];
	evenEvenEven[0] = tmp_evenEvenEvenEven + tmp_evenEvenEvenOdd;
	tmp_evenEvenEvenEven0 = evenEvenEvenEven[1];
	tmp_evenEvenEvenOdd0 = evenEvenEvenOdd[1];
	evenEvenEven[1] = tmp_evenEvenEvenEven0 + tmp_evenEvenEvenOdd0;
	tmp_evenEvenEvenEven1 = evenEvenEvenEven[1];
	tmp_evenEvenEvenOdd1 = evenEvenEvenOdd[1];
	evenEvenEven[2] = tmp_evenEvenEvenEven1 - tmp_evenEvenEvenOdd1;
	tmp_evenEvenEvenEven2 = evenEvenEvenEven[0];
	tmp_evenEvenEvenOdd2 = evenEvenEvenOdd[0];
	evenEvenEven[3] = tmp_evenEvenEvenEven2 - tmp_evenEvenEvenOdd2;
	i = 0;
	while (i <= 3) {
		tmp_Src7 = tokens_Src[(index_Src % SIZE_Src) + (4)];
		tmp_g_aiT327 = HevcDecoder_xIT_IT32x32_IT32x32_1d_1_g_aiT32[4][i];
		tmp_Src8 = tokens_Src[(index_Src % SIZE_Src) + (12)];
		tmp_g_aiT328 = HevcDecoder_xIT_IT32x32_IT32x32_1d_1_g_aiT32[12][i];
		tmp_Src9 = tokens_Src[(index_Src % SIZE_Src) + (20)];
		tmp_g_aiT329 = HevcDecoder_xIT_IT32x32_IT32x32_1d_1_g_aiT32[20][i];
		tmp_Src10 = tokens_Src[(index_Src % SIZE_Src) + (28)];
		tmp_g_aiT3210 = HevcDecoder_xIT_IT32x32_IT32x32_1d_1_g_aiT32[28][i];
		evenEvenOdd[i] = tmp_Src7 * tmp_g_aiT327 + tmp_Src8 * tmp_g_aiT328 + tmp_Src9 * tmp_g_aiT329 + tmp_Src10 * tmp_g_aiT3210;
		i = i + 1;
	}
	tmp_evenEvenEven = evenEvenEven[0];
	tmp_evenEvenOdd = evenEvenOdd[0];
	evenEven[0] = tmp_evenEvenEven + tmp_evenEvenOdd;
	tmp_evenEvenEven0 = evenEvenEven[1];
	tmp_evenEvenOdd0 = evenEvenOdd[1];
	evenEven[1] = tmp_evenEvenEven0 + tmp_evenEvenOdd0;
	tmp_evenEvenEven1 = evenEvenEven[2];
	tmp_evenEvenOdd1 = evenEvenOdd[2];
	evenEven[2] = tmp_evenEvenEven1 + tmp_evenEvenOdd1;
	tmp_evenEvenEven2 = evenEvenEven[3];
	tmp_evenEvenOdd2 = evenEvenOdd[3];
	evenEven[3] = tmp_evenEvenEven2 + tmp_evenEvenOdd2;
	tmp_evenEvenEven3 = evenEvenEven[3];
	tmp_evenEvenOdd3 = evenEvenOdd[3];
	evenEven[4] = tmp_evenEvenEven3 - tmp_evenEvenOdd3;
	tmp_evenEvenEven4 = evenEvenEven[2];
	tmp_evenEvenOdd4 = evenEvenOdd[2];
	evenEven[5] = tmp_evenEvenEven4 - tmp_evenEvenOdd4;
	tmp_evenEvenEven5 = evenEvenEven[1];
	tmp_evenEvenOdd5 = evenEvenOdd[1];
	evenEven[6] = tmp_evenEvenEven5 - tmp_evenEvenOdd5;
	tmp_evenEvenEven6 = evenEvenEven[0];
	tmp_evenEvenOdd6 = evenEvenOdd[0];
	evenEven[7] = tmp_evenEvenEven6 - tmp_evenEvenOdd6;
	i0 = 0;
	while (i0 <= 7) {
		tmp_Src11 = tokens_Src[(index_Src % SIZE_Src) + (2)];
		tmp_g_aiT3211 = HevcDecoder_xIT_IT32x32_IT32x32_1d_1_g_aiT32[2][i0];
		tmp_Src12 = tokens_Src[(index_Src % SIZE_Src) + (6)];
		tmp_g_aiT3212 = HevcDecoder_xIT_IT32x32_IT32x32_1d_1_g_aiT32[6][i0];
		tmp_Src13 = tokens_Src[(index_Src % SIZE_Src) + (10)];
		tmp_g_aiT3213 = HevcDecoder_xIT_IT32x32_IT32x32_1d_1_g_aiT32[10][i0];
		tmp_Src14 = tokens_Src[(index_Src % SIZE_Src) + (14)];
		tmp_g_aiT3214 = HevcDecoder_xIT_IT32x32_IT32x32_1d_1_g_aiT32[14][i0];
		tmp_Src15 = tokens_Src[(index_Src % SIZE_Src) + (18)];
		tmp_g_aiT3215 = HevcDecoder_xIT_IT32x32_IT32x32_1d_1_g_aiT32[18][i0];
		tmp_Src16 = tokens_Src[(index_Src % SIZE_Src) + (22)];
		tmp_g_aiT3216 = HevcDecoder_xIT_IT32x32_IT32x32_1d_1_g_aiT32[22][i0];
		tmp_Src17 = tokens_Src[(index_Src % SIZE_Src) + (26)];
		tmp_g_aiT3217 = HevcDecoder_xIT_IT32x32_IT32x32_1d_1_g_aiT32[26][i0];
		tmp_Src18 = tokens_Src[(index_Src % SIZE_Src) + (30)];
		tmp_g_aiT3218 = HevcDecoder_xIT_IT32x32_IT32x32_1d_1_g_aiT32[30][i0];
		evenOdd[i0] = tmp_Src11 * tmp_g_aiT3211 + tmp_Src12 * tmp_g_aiT3212 + tmp_Src13 * tmp_g_aiT3213 + tmp_Src14 * tmp_g_aiT3214 + tmp_Src15 * tmp_g_aiT3215 + tmp_Src16 * tmp_g_aiT3216 + tmp_Src17 * tmp_g_aiT3217 + tmp_Src18 * tmp_g_aiT3218;
		i0 = i0 + 1;
	}
	tmp_evenEven = evenEven[0];
	tmp_evenOdd = evenOdd[0];
	even[0] = tmp_evenEven + tmp_evenOdd;
	tmp_evenEven0 = evenEven[1];
	tmp_evenOdd0 = evenOdd[1];
	even[1] = tmp_evenEven0 + tmp_evenOdd0;
	tmp_evenEven1 = evenEven[2];
	tmp_evenOdd1 = evenOdd[2];
	even[2] = tmp_evenEven1 + tmp_evenOdd1;
	tmp_evenEven2 = evenEven[3];
	tmp_evenOdd2 = evenOdd[3];
	even[3] = tmp_evenEven2 + tmp_evenOdd2;
	tmp_evenEven3 = evenEven[4];
	tmp_evenOdd3 = evenOdd[4];
	even[4] = tmp_evenEven3 + tmp_evenOdd3;
	tmp_evenEven4 = evenEven[5];
	tmp_evenOdd4 = evenOdd[5];
	even[5] = tmp_evenEven4 + tmp_evenOdd4;
	tmp_evenEven5 = evenEven[6];
	tmp_evenOdd5 = evenOdd[6];
	even[6] = tmp_evenEven5 + tmp_evenOdd5;
	tmp_evenEven6 = evenEven[7];
	tmp_evenOdd6 = evenOdd[7];
	even[7] = tmp_evenEven6 + tmp_evenOdd6;
	tmp_evenEven7 = evenEven[7];
	tmp_evenOdd7 = evenOdd[7];
	even[8] = tmp_evenEven7 - tmp_evenOdd7;
	tmp_evenEven8 = evenEven[6];
	tmp_evenOdd8 = evenOdd[6];
	even[9] = tmp_evenEven8 - tmp_evenOdd8;
	tmp_evenEven9 = evenEven[5];
	tmp_evenOdd9 = evenOdd[5];
	even[10] = tmp_evenEven9 - tmp_evenOdd9;
	tmp_evenEven10 = evenEven[4];
	tmp_evenOdd10 = evenOdd[4];
	even[11] = tmp_evenEven10 - tmp_evenOdd10;
	tmp_evenEven11 = evenEven[3];
	tmp_evenOdd11 = evenOdd[3];
	even[12] = tmp_evenEven11 - tmp_evenOdd11;
	tmp_evenEven12 = evenEven[2];
	tmp_evenOdd12 = evenOdd[2];
	even[13] = tmp_evenEven12 - tmp_evenOdd12;
	tmp_evenEven13 = evenEven[1];
	tmp_evenOdd13 = evenOdd[1];
	even[14] = tmp_evenEven13 - tmp_evenOdd13;
	tmp_evenEven14 = evenEven[0];
	tmp_evenOdd14 = evenOdd[0];
	even[15] = tmp_evenEven14 - tmp_evenOdd14;
	i1 = 0;
	while (i1 <= 15) {
		tmp_Src19 = tokens_Src[(index_Src % SIZE_Src) + (1)];
		tmp_g_aiT3219 = HevcDecoder_xIT_IT32x32_IT32x32_1d_1_g_aiT32[1][i1];
		tmp_Src20 = tokens_Src[(index_Src % SIZE_Src) + (3)];
		tmp_g_aiT3220 = HevcDecoder_xIT_IT32x32_IT32x32_1d_1_g_aiT32[3][i1];
		tmp_Src21 = tokens_Src[(index_Src % SIZE_Src) + (5)];
		tmp_g_aiT3221 = HevcDecoder_xIT_IT32x32_IT32x32_1d_1_g_aiT32[5][i1];
		tmp_Src22 = tokens_Src[(index_Src % SIZE_Src) + (7)];
		tmp_g_aiT3222 = HevcDecoder_xIT_IT32x32_IT32x32_1d_1_g_aiT32[7][i1];
		tmp_Src23 = tokens_Src[(index_Src % SIZE_Src) + (9)];
		tmp_g_aiT3223 = HevcDecoder_xIT_IT32x32_IT32x32_1d_1_g_aiT32[9][i1];
		tmp_Src24 = tokens_Src[(index_Src % SIZE_Src) + (11)];
		tmp_g_aiT3224 = HevcDecoder_xIT_IT32x32_IT32x32_1d_1_g_aiT32[11][i1];
		tmp_Src25 = tokens_Src[(index_Src % SIZE_Src) + (13)];
		tmp_g_aiT3225 = HevcDecoder_xIT_IT32x32_IT32x32_1d_1_g_aiT32[13][i1];
		tmp_Src26 = tokens_Src[(index_Src % SIZE_Src) + (15)];
		tmp_g_aiT3226 = HevcDecoder_xIT_IT32x32_IT32x32_1d_1_g_aiT32[15][i1];
		tmp_Src27 = tokens_Src[(index_Src % SIZE_Src) + (17)];
		tmp_g_aiT3227 = HevcDecoder_xIT_IT32x32_IT32x32_1d_1_g_aiT32[17][i1];
		tmp_Src28 = tokens_Src[(index_Src % SIZE_Src) + (19)];
		tmp_g_aiT3228 = HevcDecoder_xIT_IT32x32_IT32x32_1d_1_g_aiT32[19][i1];
		tmp_Src29 = tokens_Src[(index_Src % SIZE_Src) + (21)];
		tmp_g_aiT3229 = HevcDecoder_xIT_IT32x32_IT32x32_1d_1_g_aiT32[21][i1];
		tmp_Src30 = tokens_Src[(index_Src % SIZE_Src) + (23)];
		tmp_g_aiT3230 = HevcDecoder_xIT_IT32x32_IT32x32_1d_1_g_aiT32[23][i1];
		tmp_Src31 = tokens_Src[(index_Src % SIZE_Src) + (25)];
		tmp_g_aiT3231 = HevcDecoder_xIT_IT32x32_IT32x32_1d_1_g_aiT32[25][i1];
		tmp_Src32 = tokens_Src[(index_Src % SIZE_Src) + (27)];
		tmp_g_aiT3232 = HevcDecoder_xIT_IT32x32_IT32x32_1d_1_g_aiT32[27][i1];
		tmp_Src33 = tokens_Src[(index_Src % SIZE_Src) + (29)];
		tmp_g_aiT3233 = HevcDecoder_xIT_IT32x32_IT32x32_1d_1_g_aiT32[29][i1];
		tmp_Src34 = tokens_Src[(index_Src % SIZE_Src) + (31)];
		tmp_g_aiT3234 = HevcDecoder_xIT_IT32x32_IT32x32_1d_1_g_aiT32[31][i1];
		odd[i1] = tmp_Src19 * tmp_g_aiT3219 + tmp_Src20 * tmp_g_aiT3220 + tmp_Src21 * tmp_g_aiT3221 + tmp_Src22 * tmp_g_aiT3222 + tmp_Src23 * tmp_g_aiT3223 + tmp_Src24 * tmp_g_aiT3224 + tmp_Src25 * tmp_g_aiT3225 + tmp_Src26 * tmp_g_aiT3226 + tmp_Src27 * tmp_g_aiT3227 + tmp_Src28 * tmp_g_aiT3228 + tmp_Src29 * tmp_g_aiT3229 + tmp_Src30 * tmp_g_aiT3230 + tmp_Src31 * tmp_g_aiT3231 + tmp_Src32 * tmp_g_aiT3232 + tmp_Src33 * tmp_g_aiT3233 + tmp_Src34 * tmp_g_aiT3234;
		i1 = i1 + 1;
	}
	tmp_even = even[0];
	tmp_odd = odd[0];
	dst[0] = tmp_even + tmp_odd;
	tmp_even0 = even[1];
	tmp_odd0 = odd[1];
	dst[1] = tmp_even0 + tmp_odd0;
	tmp_even1 = even[2];
	tmp_odd1 = odd[2];
	dst[2] = tmp_even1 + tmp_odd1;
	tmp_even2 = even[3];
	tmp_odd2 = odd[3];
	dst[3] = tmp_even2 + tmp_odd2;
	tmp_even3 = even[4];
	tmp_odd3 = odd[4];
	dst[4] = tmp_even3 + tmp_odd3;
	tmp_even4 = even[5];
	tmp_odd4 = odd[5];
	dst[5] = tmp_even4 + tmp_odd4;
	tmp_even5 = even[6];
	tmp_odd5 = odd[6];
	dst[6] = tmp_even5 + tmp_odd5;
	tmp_even6 = even[7];
	tmp_odd6 = odd[7];
	dst[7] = tmp_even6 + tmp_odd6;
	tmp_even7 = even[8];
	tmp_odd7 = odd[8];
	dst[8] = tmp_even7 + tmp_odd7;
	tmp_even8 = even[9];
	tmp_odd8 = odd[9];
	dst[9] = tmp_even8 + tmp_odd8;
	tmp_even9 = even[10];
	tmp_odd9 = odd[10];
	dst[10] = tmp_even9 + tmp_odd9;
	tmp_even10 = even[11];
	tmp_odd10 = odd[11];
	dst[11] = tmp_even10 + tmp_odd10;
	tmp_even11 = even[12];
	tmp_odd11 = odd[12];
	dst[12] = tmp_even11 + tmp_odd11;
	tmp_even12 = even[13];
	tmp_odd12 = odd[13];
	dst[13] = tmp_even12 + tmp_odd12;
	tmp_even13 = even[14];
	tmp_odd13 = odd[14];
	dst[14] = tmp_even13 + tmp_odd13;
	tmp_even14 = even[15];
	tmp_odd14 = odd[15];
	dst[15] = tmp_even14 + tmp_odd14;
	tmp_even15 = even[15];
	tmp_odd15 = odd[15];
	dst[16] = tmp_even15 - tmp_odd15;
	tmp_even16 = even[14];
	tmp_odd16 = odd[14];
	dst[17] = tmp_even16 - tmp_odd16;
	tmp_even17 = even[13];
	tmp_odd17 = odd[13];
	dst[18] = tmp_even17 - tmp_odd17;
	tmp_even18 = even[12];
	tmp_odd18 = odd[12];
	dst[19] = tmp_even18 - tmp_odd18;
	tmp_even19 = even[11];
	tmp_odd19 = odd[11];
	dst[20] = tmp_even19 - tmp_odd19;
	tmp_even20 = even[10];
	tmp_odd20 = odd[10];
	dst[21] = tmp_even20 - tmp_odd20;
	tmp_even21 = even[9];
	tmp_odd21 = odd[9];
	dst[22] = tmp_even21 - tmp_odd21;
	tmp_even22 = even[8];
	tmp_odd22 = odd[8];
	dst[23] = tmp_even22 - tmp_odd22;
	tmp_even23 = even[7];
	tmp_odd23 = odd[7];
	dst[24] = tmp_even23 - tmp_odd23;
	tmp_even24 = even[6];
	tmp_odd24 = odd[6];
	dst[25] = tmp_even24 - tmp_odd24;
	tmp_even25 = even[5];
	tmp_odd25 = odd[5];
	dst[26] = tmp_even25 - tmp_odd25;
	tmp_even26 = even[4];
	tmp_odd26 = odd[4];
	dst[27] = tmp_even26 - tmp_odd26;
	tmp_even27 = even[3];
	tmp_odd27 = odd[3];
	dst[28] = tmp_even27 - tmp_odd27;
	tmp_even28 = even[2];
	tmp_odd28 = odd[2];
	dst[29] = tmp_even28 - tmp_odd28;
	tmp_even29 = even[1];
	tmp_odd29 = odd[1];
	dst[30] = tmp_even29 - tmp_odd29;
	tmp_even30 = even[0];
	tmp_odd30 = odd[0];
	dst[31] = tmp_even30 - tmp_odd30;
	i2 = 0;
	while (i2 <= 31) {
		tmp_dst = dst[i2];
		local_shift = shift;
		tokens_Dst[(index_Dst % SIZE_Dst) + (i2)] = (tmp_dst + rouding_factor) >> local_shift;
		i2 = i2 + 1;
	}

	// Update ports indexes
	index_Src += 32;
	read_end_Src();
	index_Dst += 32;
	write_end_Dst();

	rate_Src += 32;
}

////////////////////////////////////////////////////////////////////////////////
// Initializes

void HevcDecoder_xIT_IT32x32_IT32x32_1d_1_initialize(schedinfo_t *si) {
	int i = 0;
	write_Dst();
finished:
	write_end_Dst();
	return;
}

////////////////////////////////////////////////////////////////////////////////
// Action scheduler
void HevcDecoder_xIT_IT32x32_IT32x32_1d_1_scheduler(schedinfo_t *si) {
	int i = 0;
	si->ports = 0;

	read_Src();
	write_Dst();

	while (1) {
		if (numTokens_Src - index_Src >= 32 && isSchedulable_untagged_0()) {
			int stop = 0;
			if (32 > SIZE_Dst - index_Dst + HevcDecoder_xIT_IT32x32_IT32x32_1d_1_Dst->read_inds[0]) {
				stop = 1;
			}
			if (stop != 0) {
				si->num_firings = i;
				si->reason = full;
				goto finished;
			}
			untagged_0_aligned();
			i++;
		} else {
			si->num_firings = i;
			si->reason = starved;
			goto finished;
		}
	}

finished:

	read_end_Src();
	write_end_Dst();
}
