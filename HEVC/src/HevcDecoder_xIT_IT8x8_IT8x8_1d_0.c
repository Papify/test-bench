// Source file is "L/RVC/src/org/sc29/wg11/mpegh/part2/main/IT/IT8x8_1d.cal"

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
extern actor_t HevcDecoder_xIT_IT8x8_IT8x8_1d_0;

////////////////////////////////////////////////////////////////////////////////
// Input FIFOs
extern fifo_i16_t *HevcDecoder_xIT_IT8x8_IT8x8_1d_0_Src;

////////////////////////////////////////////////////////////////////////////////
// Input Fifo control variables
static unsigned int index_Src;
static unsigned int numTokens_Src;
#define SIZE_Src SIZE
#define tokens_Src HevcDecoder_xIT_IT8x8_IT8x8_1d_0_Src->contents

extern connection_t connection_HevcDecoder_xIT_IT8x8_IT8x8_1d_0_Src;
#define rate_Src connection_HevcDecoder_xIT_IT8x8_IT8x8_1d_0_Src.rate

////////////////////////////////////////////////////////////////////////////////
// Predecessors
extern actor_t HevcDecoder_xIT_IT8x8_Transpose8x8_0;

////////////////////////////////////////////////////////////////////////////////
// Output FIFOs
extern fifo_i16_t *HevcDecoder_xIT_IT8x8_IT8x8_1d_0_Dst;

////////////////////////////////////////////////////////////////////////////////
// Output Fifo control variables
static unsigned int index_Dst;
static unsigned int numFree_Dst;
#define NUM_READERS_Dst 1
#define SIZE_Dst SIZE
#define tokens_Dst HevcDecoder_xIT_IT8x8_IT8x8_1d_0_Dst->contents

////////////////////////////////////////////////////////////////////////////////
// Successors
extern actor_t HevcDecoder_xIT_IT8x8_Transpose8x8_1;

////////////////////////////////////////////////////////////////////////////////
// Parameter values of the instance
#define shift 7


////////////////////////////////////////////////////////////////////////////////
// State variables of the actor
static const i8 HevcDecoder_xIT_IT8x8_IT8x8_1d_0_g_aiT8[8][8] = {{64, 64, 64, 64, 64, 64, 64, 64}, {89, 75, 50, 18, -18, -50, -75, -89}, {83, 36, -36, -83, -83, -36, 36, 83}, {75, -18, -89, -50, 50, 89, 18, -75}, {64, -64, -64, 64, 64, -64, -64, 64}, {50, -89, 18, 75, -75, -18, 89, -50}, {36, -83, 83, -36, -36, 83, -83, 36}, {18, -50, 75, -89, 89, -75, 50, -18}};



////////////////////////////////////////////////////////////////////////////////
// Token functions
static void read_Src() {
	index_Src = HevcDecoder_xIT_IT8x8_IT8x8_1d_0_Src->read_inds[0];
	numTokens_Src = index_Src + fifo_i16_get_num_tokens(HevcDecoder_xIT_IT8x8_IT8x8_1d_0_Src, 0);
}

static void read_end_Src() {
	HevcDecoder_xIT_IT8x8_IT8x8_1d_0_Src->read_inds[0] = index_Src;
}

static void write_Dst() {
	index_Dst = HevcDecoder_xIT_IT8x8_IT8x8_1d_0_Dst->write_ind;
	numFree_Dst = index_Dst + fifo_i16_get_room(HevcDecoder_xIT_IT8x8_IT8x8_1d_0_Dst, NUM_READERS_Dst, SIZE_Dst);
}

static void write_end_Dst() {
	HevcDecoder_xIT_IT8x8_IT8x8_1d_0_Dst->write_ind = index_Dst;
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

	i32 evenEven[2];
	i32 evenOdd[2];
	i32 even[4];
	i32 odd[4];
	i32 dst[8];
	i32 local_shift;
	i32 rouding_factor;
	i16 tmp_Src;
	i8 tmp_g_aiT8;
	i16 tmp_Src0;
	i8 tmp_g_aiT80;
	i16 tmp_Src1;
	i8 tmp_g_aiT81;
	i16 tmp_Src2;
	i8 tmp_g_aiT82;
	i16 tmp_Src3;
	i8 tmp_g_aiT83;
	i16 tmp_Src4;
	i8 tmp_g_aiT84;
	i16 tmp_Src5;
	i8 tmp_g_aiT85;
	i16 tmp_Src6;
	i8 tmp_g_aiT86;
	i32 tmp_evenEven;
	i32 tmp_evenOdd;
	i32 tmp_evenEven0;
	i32 tmp_evenOdd0;
	i32 tmp_evenEven1;
	i32 tmp_evenOdd1;
	i32 tmp_evenEven2;
	i32 tmp_evenOdd2;
	i16 tmp_Src7;
	i8 tmp_g_aiT87;
	i16 tmp_Src8;
	i8 tmp_g_aiT88;
	i16 tmp_Src9;
	i8 tmp_g_aiT89;
	i16 tmp_Src10;
	i8 tmp_g_aiT810;
	i16 tmp_Src11;
	i8 tmp_g_aiT811;
	i16 tmp_Src12;
	i8 tmp_g_aiT812;
	i16 tmp_Src13;
	i8 tmp_g_aiT813;
	i16 tmp_Src14;
	i8 tmp_g_aiT814;
	i16 tmp_Src15;
	i8 tmp_g_aiT815;
	i16 tmp_Src16;
	i8 tmp_g_aiT816;
	i16 tmp_Src17;
	i8 tmp_g_aiT817;
	i16 tmp_Src18;
	i8 tmp_g_aiT818;
	i16 tmp_Src19;
	i8 tmp_g_aiT819;
	i16 tmp_Src20;
	i8 tmp_g_aiT820;
	i16 tmp_Src21;
	i8 tmp_g_aiT821;
	i16 tmp_Src22;
	i8 tmp_g_aiT822;
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
	i32 i;
	i32 tmp_dst;

	local_shift = shift;
	rouding_factor = 1 << (local_shift - 1);
	tmp_Src = tokens_Src[(index_Src % SIZE_Src) + (0)];
	tmp_g_aiT8 = HevcDecoder_xIT_IT8x8_IT8x8_1d_0_g_aiT8[0][0];
	tmp_Src0 = tokens_Src[(index_Src % SIZE_Src) + (4)];
	tmp_g_aiT80 = HevcDecoder_xIT_IT8x8_IT8x8_1d_0_g_aiT8[4][0];
	evenEven[0] = tmp_Src * tmp_g_aiT8 + tmp_Src0 * tmp_g_aiT80;
	tmp_Src1 = tokens_Src[(index_Src % SIZE_Src) + (0)];
	tmp_g_aiT81 = HevcDecoder_xIT_IT8x8_IT8x8_1d_0_g_aiT8[0][1];
	tmp_Src2 = tokens_Src[(index_Src % SIZE_Src) + (4)];
	tmp_g_aiT82 = HevcDecoder_xIT_IT8x8_IT8x8_1d_0_g_aiT8[4][1];
	evenEven[1] = tmp_Src1 * tmp_g_aiT81 + tmp_Src2 * tmp_g_aiT82;
	tmp_Src3 = tokens_Src[(index_Src % SIZE_Src) + (2)];
	tmp_g_aiT83 = HevcDecoder_xIT_IT8x8_IT8x8_1d_0_g_aiT8[2][0];
	tmp_Src4 = tokens_Src[(index_Src % SIZE_Src) + (6)];
	tmp_g_aiT84 = HevcDecoder_xIT_IT8x8_IT8x8_1d_0_g_aiT8[6][0];
	evenOdd[0] = tmp_Src3 * tmp_g_aiT83 + tmp_Src4 * tmp_g_aiT84;
	tmp_Src5 = tokens_Src[(index_Src % SIZE_Src) + (2)];
	tmp_g_aiT85 = HevcDecoder_xIT_IT8x8_IT8x8_1d_0_g_aiT8[2][1];
	tmp_Src6 = tokens_Src[(index_Src % SIZE_Src) + (6)];
	tmp_g_aiT86 = HevcDecoder_xIT_IT8x8_IT8x8_1d_0_g_aiT8[6][1];
	evenOdd[1] = tmp_Src5 * tmp_g_aiT85 + tmp_Src6 * tmp_g_aiT86;
	tmp_evenEven = evenEven[0];
	tmp_evenOdd = evenOdd[0];
	even[0] = tmp_evenEven + tmp_evenOdd;
	tmp_evenEven0 = evenEven[1];
	tmp_evenOdd0 = evenOdd[1];
	even[1] = tmp_evenEven0 + tmp_evenOdd0;
	tmp_evenEven1 = evenEven[1];
	tmp_evenOdd1 = evenOdd[1];
	even[2] = tmp_evenEven1 - tmp_evenOdd1;
	tmp_evenEven2 = evenEven[0];
	tmp_evenOdd2 = evenOdd[0];
	even[3] = tmp_evenEven2 - tmp_evenOdd2;
	tmp_Src7 = tokens_Src[(index_Src % SIZE_Src) + (1)];
	tmp_g_aiT87 = HevcDecoder_xIT_IT8x8_IT8x8_1d_0_g_aiT8[1][0];
	tmp_Src8 = tokens_Src[(index_Src % SIZE_Src) + (3)];
	tmp_g_aiT88 = HevcDecoder_xIT_IT8x8_IT8x8_1d_0_g_aiT8[3][0];
	tmp_Src9 = tokens_Src[(index_Src % SIZE_Src) + (5)];
	tmp_g_aiT89 = HevcDecoder_xIT_IT8x8_IT8x8_1d_0_g_aiT8[5][0];
	tmp_Src10 = tokens_Src[(index_Src % SIZE_Src) + (7)];
	tmp_g_aiT810 = HevcDecoder_xIT_IT8x8_IT8x8_1d_0_g_aiT8[7][0];
	odd[0] = tmp_Src7 * tmp_g_aiT87 + tmp_Src8 * tmp_g_aiT88 + tmp_Src9 * tmp_g_aiT89 + tmp_Src10 * tmp_g_aiT810;
	tmp_Src11 = tokens_Src[(index_Src % SIZE_Src) + (1)];
	tmp_g_aiT811 = HevcDecoder_xIT_IT8x8_IT8x8_1d_0_g_aiT8[1][1];
	tmp_Src12 = tokens_Src[(index_Src % SIZE_Src) + (3)];
	tmp_g_aiT812 = HevcDecoder_xIT_IT8x8_IT8x8_1d_0_g_aiT8[3][1];
	tmp_Src13 = tokens_Src[(index_Src % SIZE_Src) + (5)];
	tmp_g_aiT813 = HevcDecoder_xIT_IT8x8_IT8x8_1d_0_g_aiT8[5][1];
	tmp_Src14 = tokens_Src[(index_Src % SIZE_Src) + (7)];
	tmp_g_aiT814 = HevcDecoder_xIT_IT8x8_IT8x8_1d_0_g_aiT8[7][1];
	odd[1] = tmp_Src11 * tmp_g_aiT811 + tmp_Src12 * tmp_g_aiT812 + tmp_Src13 * tmp_g_aiT813 + tmp_Src14 * tmp_g_aiT814;
	tmp_Src15 = tokens_Src[(index_Src % SIZE_Src) + (1)];
	tmp_g_aiT815 = HevcDecoder_xIT_IT8x8_IT8x8_1d_0_g_aiT8[1][2];
	tmp_Src16 = tokens_Src[(index_Src % SIZE_Src) + (3)];
	tmp_g_aiT816 = HevcDecoder_xIT_IT8x8_IT8x8_1d_0_g_aiT8[3][2];
	tmp_Src17 = tokens_Src[(index_Src % SIZE_Src) + (5)];
	tmp_g_aiT817 = HevcDecoder_xIT_IT8x8_IT8x8_1d_0_g_aiT8[5][2];
	tmp_Src18 = tokens_Src[(index_Src % SIZE_Src) + (7)];
	tmp_g_aiT818 = HevcDecoder_xIT_IT8x8_IT8x8_1d_0_g_aiT8[7][2];
	odd[2] = tmp_Src15 * tmp_g_aiT815 + tmp_Src16 * tmp_g_aiT816 + tmp_Src17 * tmp_g_aiT817 + tmp_Src18 * tmp_g_aiT818;
	tmp_Src19 = tokens_Src[(index_Src % SIZE_Src) + (1)];
	tmp_g_aiT819 = HevcDecoder_xIT_IT8x8_IT8x8_1d_0_g_aiT8[1][3];
	tmp_Src20 = tokens_Src[(index_Src % SIZE_Src) + (3)];
	tmp_g_aiT820 = HevcDecoder_xIT_IT8x8_IT8x8_1d_0_g_aiT8[3][3];
	tmp_Src21 = tokens_Src[(index_Src % SIZE_Src) + (5)];
	tmp_g_aiT821 = HevcDecoder_xIT_IT8x8_IT8x8_1d_0_g_aiT8[5][3];
	tmp_Src22 = tokens_Src[(index_Src % SIZE_Src) + (7)];
	tmp_g_aiT822 = HevcDecoder_xIT_IT8x8_IT8x8_1d_0_g_aiT8[7][3];
	odd[3] = tmp_Src19 * tmp_g_aiT819 + tmp_Src20 * tmp_g_aiT820 + tmp_Src21 * tmp_g_aiT821 + tmp_Src22 * tmp_g_aiT822;
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
	tmp_even3 = even[3];
	tmp_odd3 = odd[3];
	dst[4] = tmp_even3 - tmp_odd3;
	tmp_even4 = even[2];
	tmp_odd4 = odd[2];
	dst[5] = tmp_even4 - tmp_odd4;
	tmp_even5 = even[1];
	tmp_odd5 = odd[1];
	dst[6] = tmp_even5 - tmp_odd5;
	tmp_even6 = even[0];
	tmp_odd6 = odd[0];
	dst[7] = tmp_even6 - tmp_odd6;
	i = 0;
	while (i <= 7) {
		tmp_dst = dst[i];
		local_shift = shift;
		tokens_Dst[(index_Dst % SIZE_Dst) + (i)] = (tmp_dst + rouding_factor) >> local_shift;
		i = i + 1;
	}

	// Update ports indexes
	index_Src += 8;
	read_end_Src();
	index_Dst += 8;
	write_end_Dst();

	rate_Src += 8;
}

////////////////////////////////////////////////////////////////////////////////
// Initializes

void HevcDecoder_xIT_IT8x8_IT8x8_1d_0_initialize(schedinfo_t *si) {
	int i = 0;
	write_Dst();
finished:
	write_end_Dst();
	return;
}

////////////////////////////////////////////////////////////////////////////////
// Action scheduler
void HevcDecoder_xIT_IT8x8_IT8x8_1d_0_scheduler(schedinfo_t *si) {
	int i = 0;
	si->ports = 0;

	read_Src();
	write_Dst();

	while (1) {
		if (numTokens_Src - index_Src >= 8 && isSchedulable_untagged_0()) {
			int stop = 0;
			if (8 > SIZE_Dst - index_Dst + HevcDecoder_xIT_IT8x8_IT8x8_1d_0_Dst->read_inds[0]) {
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
