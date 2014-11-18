// Source file is "L/RVC/src/org/sc29/wg11/mpegh/part2/main/IT/invDST4x4_2nd.cal"

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
extern actor_t HevcDecoder_xIT_invDST4x4_2nd;

////////////////////////////////////////////////////////////////////////////////
// Input FIFOs
extern fifo_i16_t *HevcDecoder_xIT_invDST4x4_2nd_IN;

////////////////////////////////////////////////////////////////////////////////
// Input Fifo control variables
static unsigned int index_IN;
static unsigned int numTokens_IN;
#define SIZE_IN SIZE
#define tokens_IN HevcDecoder_xIT_invDST4x4_2nd_IN->contents

extern connection_t connection_HevcDecoder_xIT_invDST4x4_2nd_IN;
#define rate_IN connection_HevcDecoder_xIT_invDST4x4_2nd_IN.rate

////////////////////////////////////////////////////////////////////////////////
// Predecessors
extern actor_t HevcDecoder_xIT_invDST4x4_1st;

////////////////////////////////////////////////////////////////////////////////
// Output FIFOs
extern fifo_i16_t *HevcDecoder_xIT_invDST4x4_2nd_OUT;

////////////////////////////////////////////////////////////////////////////////
// Output Fifo control variables
static unsigned int index_OUT;
static unsigned int numFree_OUT;
#define NUM_READERS_OUT 1
#define SIZE_OUT SIZE
#define tokens_OUT HevcDecoder_xIT_invDST4x4_2nd_OUT->contents

////////////////////////////////////////////////////////////////////////////////
// Successors
extern actor_t HevcDecoder_xIT_IT_Merger;


////////////////////////////////////////////////////////////////////////////////
// State variables of the actor
#define SHIFT2 12



////////////////////////////////////////////////////////////////////////////////
// Token functions
static void read_IN() {
	index_IN = HevcDecoder_xIT_invDST4x4_2nd_IN->read_inds[0];
	numTokens_IN = index_IN + fifo_i16_get_num_tokens(HevcDecoder_xIT_invDST4x4_2nd_IN, 0);
}

static void read_end_IN() {
	HevcDecoder_xIT_invDST4x4_2nd_IN->read_inds[0] = index_IN;
}

static void write_OUT() {
	index_OUT = HevcDecoder_xIT_invDST4x4_2nd_OUT->write_ind;
	numFree_OUT = index_OUT + fifo_i16_get_room(HevcDecoder_xIT_invDST4x4_2nd_OUT, NUM_READERS_OUT, SIZE_OUT);
}

static void write_end_OUT() {
	HevcDecoder_xIT_invDST4x4_2nd_OUT->write_ind = index_OUT;
}

////////////////////////////////////////////////////////////////////////////////
// Functions/procedures
static i32 HevcDecoder_xIT_invDST4x4_2nd_clip_i32(i32 Value, i32 minVal, i32 maxVal);

static i32 HevcDecoder_xIT_invDST4x4_2nd_clip_i32(i32 Value, i32 minVal, i32 maxVal) {
	i32 tmp_if;

	if (Value > maxVal) {
		tmp_if = maxVal;
	} else {
		if (Value < minVal) {
			tmp_if = minVal;
		} else {
			tmp_if = Value;
		}
	}
	return tmp_if;
}

////////////////////////////////////////////////////////////////////////////////
// Actions
static i32 isSchedulable_untagged_0() {
	i32 result;

	result = 1;
	return result;
}

static void untagged_0_aligned() {

	i32 c[4];
	i32 local_SHIFT2;
	i32 rnd_factor;
	i32 shift;
	i32 i;
	i16 tmp_IN;
	i16 tmp_IN0;
	i16 tmp_IN1;
	i16 tmp_IN2;
	i16 tmp_IN3;
	i16 tmp_IN4;
	i16 tmp_IN5;
	i32 tmp_c;
	i32 tmp_c0;
	i32 tmp_c1;
	i32 tmp_clip_i32;
	i32 tmp_c2;
	i32 tmp_c3;
	i32 tmp_c4;
	i32 tmp_clip_i320;
	i16 tmp_IN6;
	i16 tmp_IN7;
	i16 tmp_IN8;
	i32 tmp_clip_i321;
	i32 tmp_c5;
	i32 tmp_c6;
	i32 tmp_c7;
	i32 tmp_clip_i322;

	local_SHIFT2 = SHIFT2;
	rnd_factor = 1 << (local_SHIFT2 - 1);
	local_SHIFT2 = SHIFT2;
	shift = local_SHIFT2;
	i = 0;
	while (i <= 3) {
		tmp_IN = tokens_IN[(index_IN % SIZE_IN) + (i)];
		tmp_IN0 = tokens_IN[(index_IN % SIZE_IN) + (8 + i)];
		c[0] = tmp_IN + tmp_IN0;
		tmp_IN1 = tokens_IN[(index_IN % SIZE_IN) + (8 + i)];
		tmp_IN2 = tokens_IN[(index_IN % SIZE_IN) + (12 + i)];
		c[1] = tmp_IN1 + tmp_IN2;
		tmp_IN3 = tokens_IN[(index_IN % SIZE_IN) + (i)];
		tmp_IN4 = tokens_IN[(index_IN % SIZE_IN) + (12 + i)];
		c[2] = tmp_IN3 - tmp_IN4;
		tmp_IN5 = tokens_IN[(index_IN % SIZE_IN) + (4 + i)];
		c[3] = 74 * tmp_IN5;
		tmp_c = c[0];
		tmp_c0 = c[1];
		tmp_c1 = c[3];
		tmp_clip_i32 = HevcDecoder_xIT_invDST4x4_2nd_clip_i32((29 * tmp_c + 55 * tmp_c0 + tmp_c1 + rnd_factor) >> shift, -32768, 32767);
		tokens_OUT[(index_OUT % SIZE_OUT) + (4 * i + 0)] = tmp_clip_i32;
		tmp_c2 = c[2];
		tmp_c3 = c[1];
		tmp_c4 = c[3];
		tmp_clip_i320 = HevcDecoder_xIT_invDST4x4_2nd_clip_i32((55 * tmp_c2 - 29 * tmp_c3 + tmp_c4 + rnd_factor) >> shift, -32768, 32767);
		tokens_OUT[(index_OUT % SIZE_OUT) + (4 * i + 1)] = tmp_clip_i320;
		tmp_IN6 = tokens_IN[(index_IN % SIZE_IN) + (i)];
		tmp_IN7 = tokens_IN[(index_IN % SIZE_IN) + (8 + i)];
		tmp_IN8 = tokens_IN[(index_IN % SIZE_IN) + (12 + i)];
		tmp_clip_i321 = HevcDecoder_xIT_invDST4x4_2nd_clip_i32((74 * (tmp_IN6 - tmp_IN7 + tmp_IN8) + rnd_factor) >> shift, -32768, 32767);
		tokens_OUT[(index_OUT % SIZE_OUT) + (4 * i + 2)] = tmp_clip_i321;
		tmp_c5 = c[0];
		tmp_c6 = c[2];
		tmp_c7 = c[3];
		tmp_clip_i322 = HevcDecoder_xIT_invDST4x4_2nd_clip_i32((55 * tmp_c5 + 29 * tmp_c6 - tmp_c7 + rnd_factor) >> shift, -32768, 32767);
		tokens_OUT[(index_OUT % SIZE_OUT) + (4 * i + 3)] = tmp_clip_i322;
		i = i + 1;
	}

	// Update ports indexes
	index_IN += 16;
	read_end_IN();
	index_OUT += 16;
	write_end_OUT();

	rate_IN += 16;
}

////////////////////////////////////////////////////////////////////////////////
// Initializes

void HevcDecoder_xIT_invDST4x4_2nd_initialize(schedinfo_t *si) {
	int i = 0;
	write_OUT();
finished:
	write_end_OUT();
	return;
}

////////////////////////////////////////////////////////////////////////////////
// Action scheduler
void HevcDecoder_xIT_invDST4x4_2nd_scheduler(schedinfo_t *si) {
	int i = 0;
	si->ports = 0;

	read_IN();
	write_OUT();

	while (1) {
		if (numTokens_IN - index_IN >= 16 && isSchedulable_untagged_0()) {
			int stop = 0;
			if (16 > SIZE_OUT - index_OUT + HevcDecoder_xIT_invDST4x4_2nd_OUT->read_inds[0]) {
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

	read_end_IN();
	write_end_OUT();
}
