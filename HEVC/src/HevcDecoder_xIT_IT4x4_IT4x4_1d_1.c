// Source file is "L/RVC/src/org/sc29/wg11/mpegh/part2/main/IT/IT4x4_1d.cal"

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
extern actor_t HevcDecoder_xIT_IT4x4_IT4x4_1d_1;

////////////////////////////////////////////////////////////////////////////////
// Input FIFOs
extern fifo_i16_t *HevcDecoder_xIT_IT4x4_IT4x4_1d_1_Src;

////////////////////////////////////////////////////////////////////////////////
// Input Fifo control variables
static unsigned int index_Src;
static unsigned int numTokens_Src;
#define SIZE_Src SIZE
#define tokens_Src HevcDecoder_xIT_IT4x4_IT4x4_1d_1_Src->contents

extern connection_t connection_HevcDecoder_xIT_IT4x4_IT4x4_1d_1_Src;
#define rate_Src connection_HevcDecoder_xIT_IT4x4_IT4x4_1d_1_Src.rate

////////////////////////////////////////////////////////////////////////////////
// Predecessors
extern actor_t HevcDecoder_xIT_IT4x4_Transpose4x4_1;

////////////////////////////////////////////////////////////////////////////////
// Output FIFOs
extern fifo_i16_t *HevcDecoder_xIT_IT4x4_IT4x4_1d_1_Dst;

////////////////////////////////////////////////////////////////////////////////
// Output Fifo control variables
static unsigned int index_Dst;
static unsigned int numFree_Dst;
#define NUM_READERS_Dst 1
#define SIZE_Dst SIZE
#define tokens_Dst HevcDecoder_xIT_IT4x4_IT4x4_1d_1_Dst->contents

////////////////////////////////////////////////////////////////////////////////
// Successors
extern actor_t HevcDecoder_xIT_IT_Merger;

////////////////////////////////////////////////////////////////////////////////
// Parameter values of the instance
#define shift 12


////////////////////////////////////////////////////////////////////////////////
// State variables of the actor
static const i8 HevcDecoder_xIT_IT4x4_IT4x4_1d_1_g_aiT4[4][4] = {{64, 64, 64, 64}, {83, 36, -36, -83}, {64, -64, -64, 64}, {36, -83, 83, -36}};



////////////////////////////////////////////////////////////////////////////////
// Token functions
static void read_Src() {
	index_Src = HevcDecoder_xIT_IT4x4_IT4x4_1d_1_Src->read_inds[0];
	numTokens_Src = index_Src + fifo_i16_get_num_tokens(HevcDecoder_xIT_IT4x4_IT4x4_1d_1_Src, 0);
}

static void read_end_Src() {
	HevcDecoder_xIT_IT4x4_IT4x4_1d_1_Src->read_inds[0] = index_Src;
}

static void write_Dst() {
	index_Dst = HevcDecoder_xIT_IT4x4_IT4x4_1d_1_Dst->write_ind;
	numFree_Dst = index_Dst + fifo_i16_get_room(HevcDecoder_xIT_IT4x4_IT4x4_1d_1_Dst, NUM_READERS_Dst, SIZE_Dst);
}

static void write_end_Dst() {
	HevcDecoder_xIT_IT4x4_IT4x4_1d_1_Dst->write_ind = index_Dst;
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

	i32 even[2];
	i32 odd[2];
	i32 dst[4];
	i32 local_shift;
	i32 rouding_factor;
	i16 tmp_Src;
	i8 tmp_g_aiT4;
	i16 tmp_Src0;
	i8 tmp_g_aiT40;
	i16 tmp_Src1;
	i8 tmp_g_aiT41;
	i16 tmp_Src2;
	i8 tmp_g_aiT42;
	i16 tmp_Src3;
	i8 tmp_g_aiT43;
	i16 tmp_Src4;
	i8 tmp_g_aiT44;
	i16 tmp_Src5;
	i8 tmp_g_aiT45;
	i16 tmp_Src6;
	i8 tmp_g_aiT46;
	i32 tmp_even;
	i32 tmp_odd;
	i32 tmp_even0;
	i32 tmp_odd0;
	i32 tmp_even1;
	i32 tmp_odd1;
	i32 tmp_even2;
	i32 tmp_odd2;
	i32 i;
	i32 tmp_dst;

	local_shift = shift;
	rouding_factor = 1 << (local_shift - 1);
	tmp_Src = tokens_Src[(index_Src % SIZE_Src) + (0)];
	tmp_g_aiT4 = HevcDecoder_xIT_IT4x4_IT4x4_1d_1_g_aiT4[0][0];
	tmp_Src0 = tokens_Src[(index_Src % SIZE_Src) + (2)];
	tmp_g_aiT40 = HevcDecoder_xIT_IT4x4_IT4x4_1d_1_g_aiT4[2][0];
	even[0] = tmp_Src * tmp_g_aiT4 + tmp_Src0 * tmp_g_aiT40;
	tmp_Src1 = tokens_Src[(index_Src % SIZE_Src) + (0)];
	tmp_g_aiT41 = HevcDecoder_xIT_IT4x4_IT4x4_1d_1_g_aiT4[0][1];
	tmp_Src2 = tokens_Src[(index_Src % SIZE_Src) + (2)];
	tmp_g_aiT42 = HevcDecoder_xIT_IT4x4_IT4x4_1d_1_g_aiT4[2][1];
	even[1] = tmp_Src1 * tmp_g_aiT41 + tmp_Src2 * tmp_g_aiT42;
	tmp_Src3 = tokens_Src[(index_Src % SIZE_Src) + (1)];
	tmp_g_aiT43 = HevcDecoder_xIT_IT4x4_IT4x4_1d_1_g_aiT4[1][0];
	tmp_Src4 = tokens_Src[(index_Src % SIZE_Src) + (3)];
	tmp_g_aiT44 = HevcDecoder_xIT_IT4x4_IT4x4_1d_1_g_aiT4[3][0];
	odd[0] = tmp_Src3 * tmp_g_aiT43 + tmp_Src4 * tmp_g_aiT44;
	tmp_Src5 = tokens_Src[(index_Src % SIZE_Src) + (1)];
	tmp_g_aiT45 = HevcDecoder_xIT_IT4x4_IT4x4_1d_1_g_aiT4[1][1];
	tmp_Src6 = tokens_Src[(index_Src % SIZE_Src) + (3)];
	tmp_g_aiT46 = HevcDecoder_xIT_IT4x4_IT4x4_1d_1_g_aiT4[3][1];
	odd[1] = tmp_Src5 * tmp_g_aiT45 + tmp_Src6 * tmp_g_aiT46;
	tmp_even = even[0];
	tmp_odd = odd[0];
	dst[0] = tmp_even + tmp_odd;
	tmp_even0 = even[1];
	tmp_odd0 = odd[1];
	dst[1] = tmp_even0 + tmp_odd0;
	tmp_even1 = even[1];
	tmp_odd1 = odd[1];
	dst[2] = tmp_even1 - tmp_odd1;
	tmp_even2 = even[0];
	tmp_odd2 = odd[0];
	dst[3] = tmp_even2 - tmp_odd2;
	i = 0;
	while (i <= 3) {
		tmp_dst = dst[i];
		local_shift = shift;
		tokens_Dst[(index_Dst % SIZE_Dst) + (i)] = (tmp_dst + rouding_factor) >> local_shift;
		i = i + 1;
	}

	// Update ports indexes
	index_Src += 4;
	read_end_Src();
	index_Dst += 4;
	write_end_Dst();

	rate_Src += 4;
}

////////////////////////////////////////////////////////////////////////////////
// Initializes

void HevcDecoder_xIT_IT4x4_IT4x4_1d_1_initialize(schedinfo_t *si) {
	int i = 0;
	write_Dst();
finished:
	write_end_Dst();
	return;
}

////////////////////////////////////////////////////////////////////////////////
// Action scheduler
void HevcDecoder_xIT_IT4x4_IT4x4_1d_1_scheduler(schedinfo_t *si) {
	int i = 0;
	si->ports = 0;

	read_Src();
	write_Dst();

	while (1) {
		if (numTokens_Src - index_Src >= 4 && isSchedulable_untagged_0()) {
			int stop = 0;
			if (4 > SIZE_Dst - index_Dst + HevcDecoder_xIT_IT4x4_IT4x4_1d_1_Dst->read_inds[0]) {
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
