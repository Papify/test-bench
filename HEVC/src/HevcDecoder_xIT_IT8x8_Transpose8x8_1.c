// Source file is "L/RVC/src/org/sc29/wg11/mpegh/part2/main/IT/Transpose8x8.cal"

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
extern actor_t HevcDecoder_xIT_IT8x8_Transpose8x8_1;

////////////////////////////////////////////////////////////////////////////////
// Input FIFOs
extern fifo_i16_t *HevcDecoder_xIT_IT8x8_Transpose8x8_1_Src;

////////////////////////////////////////////////////////////////////////////////
// Input Fifo control variables
static unsigned int index_Src;
static unsigned int numTokens_Src;
#define SIZE_Src SIZE
#define tokens_Src HevcDecoder_xIT_IT8x8_Transpose8x8_1_Src->contents

extern connection_t connection_HevcDecoder_xIT_IT8x8_Transpose8x8_1_Src;
#define rate_Src connection_HevcDecoder_xIT_IT8x8_Transpose8x8_1_Src.rate

////////////////////////////////////////////////////////////////////////////////
// Predecessors
extern actor_t HevcDecoder_xIT_IT8x8_IT8x8_1d_0;

////////////////////////////////////////////////////////////////////////////////
// Output FIFOs
extern fifo_i16_t *HevcDecoder_xIT_IT8x8_Transpose8x8_1_Dst;

////////////////////////////////////////////////////////////////////////////////
// Output Fifo control variables
static unsigned int index_Dst;
static unsigned int numFree_Dst;
#define NUM_READERS_Dst 1
#define SIZE_Dst SIZE
#define tokens_Dst HevcDecoder_xIT_IT8x8_Transpose8x8_1_Dst->contents

////////////////////////////////////////////////////////////////////////////////
// Successors
extern actor_t HevcDecoder_xIT_IT8x8_IT8x8_1d_1;




////////////////////////////////////////////////////////////////////////////////
// Token functions
static void read_Src() {
	index_Src = HevcDecoder_xIT_IT8x8_Transpose8x8_1_Src->read_inds[0];
	numTokens_Src = index_Src + fifo_i16_get_num_tokens(HevcDecoder_xIT_IT8x8_Transpose8x8_1_Src, 0);
}

static void read_end_Src() {
	HevcDecoder_xIT_IT8x8_Transpose8x8_1_Src->read_inds[0] = index_Src;
}

static void write_Dst() {
	index_Dst = HevcDecoder_xIT_IT8x8_Transpose8x8_1_Dst->write_ind;
	numFree_Dst = index_Dst + fifo_i16_get_room(HevcDecoder_xIT_IT8x8_Transpose8x8_1_Dst, NUM_READERS_Dst, SIZE_Dst);
}

static void write_end_Dst() {
	HevcDecoder_xIT_IT8x8_Transpose8x8_1_Dst->write_ind = index_Dst;
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

	i32 row;
	i32 column;
	i16 tmp_Src;

	row = 0;
	while (row <= 7) {
		column = 0;
		while (column <= 7) {
			tmp_Src = tokens_Src[(index_Src % SIZE_Src) + (8 * column + row)];
			tokens_Dst[(index_Dst % SIZE_Dst) + (row * 8 + column)] = tmp_Src;
			column = column + 1;
		}
		row = row + 1;
	}

	// Update ports indexes
	index_Src += 64;
	read_end_Src();
	index_Dst += 64;
	write_end_Dst();

	rate_Src += 64;
}

////////////////////////////////////////////////////////////////////////////////
// Initializes

void HevcDecoder_xIT_IT8x8_Transpose8x8_1_initialize(schedinfo_t *si) {
	int i = 0;
	write_Dst();
finished:
	write_end_Dst();
	return;
}

////////////////////////////////////////////////////////////////////////////////
// Action scheduler
void HevcDecoder_xIT_IT8x8_Transpose8x8_1_scheduler(schedinfo_t *si) {
	int i = 0;
	si->ports = 0;

	read_Src();
	write_Dst();

	while (1) {
		if (numTokens_Src - index_Src >= 64 && isSchedulable_untagged_0()) {
			int stop = 0;
			if (64 > SIZE_Dst - index_Dst + HevcDecoder_xIT_IT8x8_Transpose8x8_1_Dst->read_inds[0]) {
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
