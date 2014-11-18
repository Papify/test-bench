// Source file is "L/RVC/src/org/sc29/wg11/mpegh/part2/main/IT/IT_Splitter.cal"

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
extern actor_t HevcDecoder_xIT_IT_Splitter;

////////////////////////////////////////////////////////////////////////////////
// Input FIFOs
extern fifo_i16_t *HevcDecoder_xIT_IT_Splitter_Coeff;
extern fifo_i8_t *HevcDecoder_xIT_IT_Splitter_Size;

////////////////////////////////////////////////////////////////////////////////
// Input Fifo control variables
static unsigned int index_Coeff;
static unsigned int numTokens_Coeff;
#define SIZE_Coeff SIZE
#define tokens_Coeff HevcDecoder_xIT_IT_Splitter_Coeff->contents

extern connection_t connection_HevcDecoder_xIT_IT_Splitter_Coeff;
#define rate_Coeff connection_HevcDecoder_xIT_IT_Splitter_Coeff.rate

static unsigned int index_Size;
static unsigned int numTokens_Size;
#define SIZE_Size SIZE
#define tokens_Size HevcDecoder_xIT_IT_Splitter_Size->contents

extern connection_t connection_HevcDecoder_xIT_IT_Splitter_Size;
#define rate_Size connection_HevcDecoder_xIT_IT_Splitter_Size.rate

////////////////////////////////////////////////////////////////////////////////
// Predecessors
extern actor_t HevcDecoder_Algo_Parser;
extern actor_t HevcDecoder_Algo_Parser;

////////////////////////////////////////////////////////////////////////////////
// Output FIFOs
extern fifo_i16_t *HevcDecoder_xIT_IT_Splitter_Coeff_4x4_DST;
extern fifo_i16_t *HevcDecoder_xIT_IT_Splitter_Coeff_4x4_IT;
extern fifo_i16_t *HevcDecoder_xIT_IT_Splitter_Coeff_8x8;
extern fifo_i16_t *HevcDecoder_xIT_IT_Splitter_Coeff_16x16;
extern fifo_i16_t *HevcDecoder_xIT_IT_Splitter_Coeff_32x32;
extern fifo_i16_t *HevcDecoder_xIT_IT_Splitter_Coeff_skip;

////////////////////////////////////////////////////////////////////////////////
// Output Fifo control variables
static unsigned int index_Coeff_4x4_DST;
static unsigned int numFree_Coeff_4x4_DST;
#define NUM_READERS_Coeff_4x4_DST 1
#define SIZE_Coeff_4x4_DST SIZE
#define tokens_Coeff_4x4_DST HevcDecoder_xIT_IT_Splitter_Coeff_4x4_DST->contents

static unsigned int index_Coeff_4x4_IT;
static unsigned int numFree_Coeff_4x4_IT;
#define NUM_READERS_Coeff_4x4_IT 1
#define SIZE_Coeff_4x4_IT SIZE
#define tokens_Coeff_4x4_IT HevcDecoder_xIT_IT_Splitter_Coeff_4x4_IT->contents

static unsigned int index_Coeff_8x8;
static unsigned int numFree_Coeff_8x8;
#define NUM_READERS_Coeff_8x8 1
#define SIZE_Coeff_8x8 SIZE
#define tokens_Coeff_8x8 HevcDecoder_xIT_IT_Splitter_Coeff_8x8->contents

static unsigned int index_Coeff_16x16;
static unsigned int numFree_Coeff_16x16;
#define NUM_READERS_Coeff_16x16 1
#define SIZE_Coeff_16x16 SIZE
#define tokens_Coeff_16x16 HevcDecoder_xIT_IT_Splitter_Coeff_16x16->contents

static unsigned int index_Coeff_32x32;
static unsigned int numFree_Coeff_32x32;
#define NUM_READERS_Coeff_32x32 1
#define SIZE_Coeff_32x32 SIZE
#define tokens_Coeff_32x32 HevcDecoder_xIT_IT_Splitter_Coeff_32x32->contents

static unsigned int index_Coeff_skip;
static unsigned int numFree_Coeff_skip;
#define NUM_READERS_Coeff_skip 1
#define SIZE_Coeff_skip SIZE
#define tokens_Coeff_skip HevcDecoder_xIT_IT_Splitter_Coeff_skip->contents

////////////////////////////////////////////////////////////////////////////////
// Successors
extern actor_t HevcDecoder_xIT_invDST4x4_1st;
extern actor_t HevcDecoder_xIT_IT4x4_Transpose4x4_0;
extern actor_t HevcDecoder_xIT_IT8x8_Transpose8x8_0;
extern actor_t HevcDecoder_xIT_IT16x16_Transpose16x16_0;
extern actor_t HevcDecoder_xIT_IT32x32_Transpose32x32_0;
extern actor_t HevcDecoder_xIT_IT_Merger;


////////////////////////////////////////////////////////////////////////////////
// State variables of the actor
#define MAX_TR_DYNAMIC_RANGE 15
#define BIT_DEPTH 8
static i16 tabTransCoeffLevel[1024];



////////////////////////////////////////////////////////////////////////////////
// Token functions
static void read_Coeff() {
	index_Coeff = HevcDecoder_xIT_IT_Splitter_Coeff->read_inds[0];
	numTokens_Coeff = index_Coeff + fifo_i16_get_num_tokens(HevcDecoder_xIT_IT_Splitter_Coeff, 0);
}

static void read_end_Coeff() {
	HevcDecoder_xIT_IT_Splitter_Coeff->read_inds[0] = index_Coeff;
}
static void read_Size() {
	index_Size = HevcDecoder_xIT_IT_Splitter_Size->read_inds[0];
	numTokens_Size = index_Size + fifo_i8_get_num_tokens(HevcDecoder_xIT_IT_Splitter_Size, 0);
}

static void read_end_Size() {
	HevcDecoder_xIT_IT_Splitter_Size->read_inds[0] = index_Size;
}

static void write_Coeff_4x4_DST() {
	index_Coeff_4x4_DST = HevcDecoder_xIT_IT_Splitter_Coeff_4x4_DST->write_ind;
	numFree_Coeff_4x4_DST = index_Coeff_4x4_DST + fifo_i16_get_room(HevcDecoder_xIT_IT_Splitter_Coeff_4x4_DST, NUM_READERS_Coeff_4x4_DST, SIZE_Coeff_4x4_DST);
}

static void write_end_Coeff_4x4_DST() {
	HevcDecoder_xIT_IT_Splitter_Coeff_4x4_DST->write_ind = index_Coeff_4x4_DST;
}
static void write_Coeff_4x4_IT() {
	index_Coeff_4x4_IT = HevcDecoder_xIT_IT_Splitter_Coeff_4x4_IT->write_ind;
	numFree_Coeff_4x4_IT = index_Coeff_4x4_IT + fifo_i16_get_room(HevcDecoder_xIT_IT_Splitter_Coeff_4x4_IT, NUM_READERS_Coeff_4x4_IT, SIZE_Coeff_4x4_IT);
}

static void write_end_Coeff_4x4_IT() {
	HevcDecoder_xIT_IT_Splitter_Coeff_4x4_IT->write_ind = index_Coeff_4x4_IT;
}
static void write_Coeff_8x8() {
	index_Coeff_8x8 = HevcDecoder_xIT_IT_Splitter_Coeff_8x8->write_ind;
	numFree_Coeff_8x8 = index_Coeff_8x8 + fifo_i16_get_room(HevcDecoder_xIT_IT_Splitter_Coeff_8x8, NUM_READERS_Coeff_8x8, SIZE_Coeff_8x8);
}

static void write_end_Coeff_8x8() {
	HevcDecoder_xIT_IT_Splitter_Coeff_8x8->write_ind = index_Coeff_8x8;
}
static void write_Coeff_16x16() {
	index_Coeff_16x16 = HevcDecoder_xIT_IT_Splitter_Coeff_16x16->write_ind;
	numFree_Coeff_16x16 = index_Coeff_16x16 + fifo_i16_get_room(HevcDecoder_xIT_IT_Splitter_Coeff_16x16, NUM_READERS_Coeff_16x16, SIZE_Coeff_16x16);
}

static void write_end_Coeff_16x16() {
	HevcDecoder_xIT_IT_Splitter_Coeff_16x16->write_ind = index_Coeff_16x16;
}
static void write_Coeff_32x32() {
	index_Coeff_32x32 = HevcDecoder_xIT_IT_Splitter_Coeff_32x32->write_ind;
	numFree_Coeff_32x32 = index_Coeff_32x32 + fifo_i16_get_room(HevcDecoder_xIT_IT_Splitter_Coeff_32x32, NUM_READERS_Coeff_32x32, SIZE_Coeff_32x32);
}

static void write_end_Coeff_32x32() {
	HevcDecoder_xIT_IT_Splitter_Coeff_32x32->write_ind = index_Coeff_32x32;
}
static void write_Coeff_skip() {
	index_Coeff_skip = HevcDecoder_xIT_IT_Splitter_Coeff_skip->write_ind;
	numFree_Coeff_skip = index_Coeff_skip + fifo_i16_get_room(HevcDecoder_xIT_IT_Splitter_Coeff_skip, NUM_READERS_Coeff_skip, SIZE_Coeff_skip);
}

static void write_end_Coeff_skip() {
	HevcDecoder_xIT_IT_Splitter_Coeff_skip->write_ind = index_Coeff_skip;
}

////////////////////////////////////////////////////////////////////////////////
// Functions/procedures


////////////////////////////////////////////////////////////////////////////////
// Actions
static i32 isSchedulable_split_4x4_transf_skip() {
	i32 result;
	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;

	sizeOfTU = tokens_Size[(index_Size + (0)) % SIZE_Size];
	RCskip = tokens_Size[(index_Size + (1)) % SIZE_Size];
	isDST = tokens_Size[(index_Size + (2)) % SIZE_Size];
	transformSkipFlag = tokens_Size[(index_Size + (3)) % SIZE_Size];
	slice_qp = tokens_Size[(index_Size + (4)) % SIZE_Size];
	rc_cIdx = tokens_Size[(index_Size + (5)) % SIZE_Size];
	qp_offset = tokens_Size[(index_Size + (6)) % SIZE_Size];
	result = sizeOfTU == 4 && RCskip == 0 && transformSkipFlag == 1;
	return result;
}

static void split_4x4_transf_skip() {

	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;
	i32 local_MAX_TR_DYNAMIC_RANGE;
	i32 local_BIT_DEPTH;
	i32 shift;
	i32 transformSkipShift;
	i32 offset;
	i32 i;
	i16 tmp_Coeff;
	i32 i0;
	i16 tmp_tabTransCoeffLevel;

	sizeOfTU = tokens_Size[(index_Size + (0)) % SIZE_Size];
	RCskip = tokens_Size[(index_Size + (1)) % SIZE_Size];
	isDST = tokens_Size[(index_Size + (2)) % SIZE_Size];
	transformSkipFlag = tokens_Size[(index_Size + (3)) % SIZE_Size];
	slice_qp = tokens_Size[(index_Size + (4)) % SIZE_Size];
	rc_cIdx = tokens_Size[(index_Size + (5)) % SIZE_Size];
	qp_offset = tokens_Size[(index_Size + (6)) % SIZE_Size];
	local_MAX_TR_DYNAMIC_RANGE = MAX_TR_DYNAMIC_RANGE;
	local_BIT_DEPTH = BIT_DEPTH;
	shift = local_MAX_TR_DYNAMIC_RANGE - local_BIT_DEPTH - 2;
	transformSkipShift = shift;
	offset = 1 << (transformSkipShift - 1);
	i = 0;
	while (i <= sizeOfTU * sizeOfTU - 1) {
		tmp_Coeff = tokens_Coeff[(index_Coeff + (i)) % SIZE_Coeff];
		tabTransCoeffLevel[i] = tmp_Coeff;
		i = i + 1;
	}
	i0 = 0;
	while (i0 <= 15) {
		tmp_tabTransCoeffLevel = tabTransCoeffLevel[i0];
		tokens_Coeff_skip[(index_Coeff_skip + (i0)) % SIZE_Coeff_skip] = (tmp_tabTransCoeffLevel + offset) >> transformSkipShift;
		i0 = i0 + 1;
	}

	// Update ports indexes
	index_Coeff += 16;
	read_end_Coeff();
	index_Size += 7;
	read_end_Size();
	index_Coeff_skip += 16;
	write_end_Coeff_skip();

	rate_Coeff += 16;
	rate_Size += 7;
}
static void split_4x4_transf_skip_aligned() {

	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;
	i32 local_MAX_TR_DYNAMIC_RANGE;
	i32 local_BIT_DEPTH;
	i32 shift;
	i32 transformSkipShift;
	i32 offset;
	i32 i;
	i16 tmp_Coeff;
	i32 i0;
	i16 tmp_tabTransCoeffLevel;

	sizeOfTU = tokens_Size[(index_Size % SIZE_Size) + (0)];
	RCskip = tokens_Size[(index_Size % SIZE_Size) + (1)];
	isDST = tokens_Size[(index_Size % SIZE_Size) + (2)];
	transformSkipFlag = tokens_Size[(index_Size % SIZE_Size) + (3)];
	slice_qp = tokens_Size[(index_Size % SIZE_Size) + (4)];
	rc_cIdx = tokens_Size[(index_Size % SIZE_Size) + (5)];
	qp_offset = tokens_Size[(index_Size % SIZE_Size) + (6)];
	local_MAX_TR_DYNAMIC_RANGE = MAX_TR_DYNAMIC_RANGE;
	local_BIT_DEPTH = BIT_DEPTH;
	shift = local_MAX_TR_DYNAMIC_RANGE - local_BIT_DEPTH - 2;
	transformSkipShift = shift;
	offset = 1 << (transformSkipShift - 1);
	i = 0;
	while (i <= sizeOfTU * sizeOfTU - 1) {
		tmp_Coeff = tokens_Coeff[(index_Coeff % SIZE_Coeff) + (i)];
		tabTransCoeffLevel[i] = tmp_Coeff;
		i = i + 1;
	}
	i0 = 0;
	while (i0 <= 15) {
		tmp_tabTransCoeffLevel = tabTransCoeffLevel[i0];
		tokens_Coeff_skip[(index_Coeff_skip % SIZE_Coeff_skip) + (i0)] = (tmp_tabTransCoeffLevel + offset) >> transformSkipShift;
		i0 = i0 + 1;
	}

	// Update ports indexes
	index_Coeff += 16;
	read_end_Coeff();
	index_Size += 7;
	read_end_Size();
	index_Coeff_skip += 16;
	write_end_Coeff_skip();

	rate_Coeff += 16;
	rate_Size += 7;
}
static i32 isSchedulable_split_4x4_DST() {
	i32 result;
	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;

	sizeOfTU = tokens_Size[(index_Size + (0)) % SIZE_Size];
	RCskip = tokens_Size[(index_Size + (1)) % SIZE_Size];
	isDST = tokens_Size[(index_Size + (2)) % SIZE_Size];
	transformSkipFlag = tokens_Size[(index_Size + (3)) % SIZE_Size];
	slice_qp = tokens_Size[(index_Size + (4)) % SIZE_Size];
	rc_cIdx = tokens_Size[(index_Size + (5)) % SIZE_Size];
	qp_offset = tokens_Size[(index_Size + (6)) % SIZE_Size];
	result = sizeOfTU == 4 && RCskip == 0 && isDST == 1 && transformSkipFlag == 0;
	return result;
}

static void split_4x4_DST() {

	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;
	i32 i;
	i16 tmp_Coeff;
	i32 i0;
	i16 tmp_tabTransCoeffLevel;

	sizeOfTU = tokens_Size[(index_Size + (0)) % SIZE_Size];
	RCskip = tokens_Size[(index_Size + (1)) % SIZE_Size];
	isDST = tokens_Size[(index_Size + (2)) % SIZE_Size];
	transformSkipFlag = tokens_Size[(index_Size + (3)) % SIZE_Size];
	slice_qp = tokens_Size[(index_Size + (4)) % SIZE_Size];
	rc_cIdx = tokens_Size[(index_Size + (5)) % SIZE_Size];
	qp_offset = tokens_Size[(index_Size + (6)) % SIZE_Size];
	i = 0;
	while (i <= sizeOfTU * sizeOfTU - 1) {
		tmp_Coeff = tokens_Coeff[(index_Coeff + (i)) % SIZE_Coeff];
		tabTransCoeffLevel[i] = tmp_Coeff;
		i = i + 1;
	}
	i0 = 0;
	while (i0 <= 4 * 4 - 1) {
		tmp_tabTransCoeffLevel = tabTransCoeffLevel[i0];
		tokens_Coeff_4x4_DST[(index_Coeff_4x4_DST % SIZE_Coeff_4x4_DST) + (i0)] = tmp_tabTransCoeffLevel;
		i0 = i0 + 1;
	}

	// Update ports indexes
	index_Coeff += 16;
	read_end_Coeff();
	index_Size += 7;
	read_end_Size();
	index_Coeff_4x4_DST += 16;
	write_end_Coeff_4x4_DST();

	rate_Coeff += 16;
	rate_Size += 7;
}
static void split_4x4_DST_aligned() {

	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;
	i32 i;
	i16 tmp_Coeff;
	i32 i0;
	i16 tmp_tabTransCoeffLevel;

	sizeOfTU = tokens_Size[(index_Size % SIZE_Size) + (0)];
	RCskip = tokens_Size[(index_Size % SIZE_Size) + (1)];
	isDST = tokens_Size[(index_Size % SIZE_Size) + (2)];
	transformSkipFlag = tokens_Size[(index_Size % SIZE_Size) + (3)];
	slice_qp = tokens_Size[(index_Size % SIZE_Size) + (4)];
	rc_cIdx = tokens_Size[(index_Size % SIZE_Size) + (5)];
	qp_offset = tokens_Size[(index_Size % SIZE_Size) + (6)];
	i = 0;
	while (i <= sizeOfTU * sizeOfTU - 1) {
		tmp_Coeff = tokens_Coeff[(index_Coeff % SIZE_Coeff) + (i)];
		tabTransCoeffLevel[i] = tmp_Coeff;
		i = i + 1;
	}
	i0 = 0;
	while (i0 <= 4 * 4 - 1) {
		tmp_tabTransCoeffLevel = tabTransCoeffLevel[i0];
		tokens_Coeff_4x4_DST[(index_Coeff_4x4_DST % SIZE_Coeff_4x4_DST) + (i0)] = tmp_tabTransCoeffLevel;
		i0 = i0 + 1;
	}

	// Update ports indexes
	index_Coeff += 16;
	read_end_Coeff();
	index_Size += 7;
	read_end_Size();
	index_Coeff_4x4_DST += 16;
	write_end_Coeff_4x4_DST();

	rate_Coeff += 16;
	rate_Size += 7;
}
static i32 isSchedulable_split_4x4_IT() {
	i32 result;
	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;

	sizeOfTU = tokens_Size[(index_Size + (0)) % SIZE_Size];
	RCskip = tokens_Size[(index_Size + (1)) % SIZE_Size];
	isDST = tokens_Size[(index_Size + (2)) % SIZE_Size];
	transformSkipFlag = tokens_Size[(index_Size + (3)) % SIZE_Size];
	slice_qp = tokens_Size[(index_Size + (4)) % SIZE_Size];
	rc_cIdx = tokens_Size[(index_Size + (5)) % SIZE_Size];
	qp_offset = tokens_Size[(index_Size + (6)) % SIZE_Size];
	result = sizeOfTU == 4 && RCskip == 0 && isDST == 0 && transformSkipFlag == 0;
	return result;
}

static void split_4x4_IT() {

	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;
	i32 i;
	i16 tmp_Coeff;
	i32 i0;
	i16 tmp_tabTransCoeffLevel;

	sizeOfTU = tokens_Size[(index_Size + (0)) % SIZE_Size];
	RCskip = tokens_Size[(index_Size + (1)) % SIZE_Size];
	isDST = tokens_Size[(index_Size + (2)) % SIZE_Size];
	transformSkipFlag = tokens_Size[(index_Size + (3)) % SIZE_Size];
	slice_qp = tokens_Size[(index_Size + (4)) % SIZE_Size];
	rc_cIdx = tokens_Size[(index_Size + (5)) % SIZE_Size];
	qp_offset = tokens_Size[(index_Size + (6)) % SIZE_Size];
	i = 0;
	while (i <= sizeOfTU * sizeOfTU - 1) {
		tmp_Coeff = tokens_Coeff[(index_Coeff + (i)) % SIZE_Coeff];
		tabTransCoeffLevel[i] = tmp_Coeff;
		i = i + 1;
	}
	i0 = 0;
	while (i0 <= 4 * 4 - 1) {
		tmp_tabTransCoeffLevel = tabTransCoeffLevel[i0];
		tokens_Coeff_4x4_IT[(index_Coeff_4x4_IT % SIZE_Coeff_4x4_IT) + (i0)] = tmp_tabTransCoeffLevel;
		i0 = i0 + 1;
	}

	// Update ports indexes
	index_Coeff += 16;
	read_end_Coeff();
	index_Size += 7;
	read_end_Size();
	index_Coeff_4x4_IT += 16;
	write_end_Coeff_4x4_IT();

	rate_Coeff += 16;
	rate_Size += 7;
}
static void split_4x4_IT_aligned() {

	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;
	i32 i;
	i16 tmp_Coeff;
	i32 i0;
	i16 tmp_tabTransCoeffLevel;

	sizeOfTU = tokens_Size[(index_Size % SIZE_Size) + (0)];
	RCskip = tokens_Size[(index_Size % SIZE_Size) + (1)];
	isDST = tokens_Size[(index_Size % SIZE_Size) + (2)];
	transformSkipFlag = tokens_Size[(index_Size % SIZE_Size) + (3)];
	slice_qp = tokens_Size[(index_Size % SIZE_Size) + (4)];
	rc_cIdx = tokens_Size[(index_Size % SIZE_Size) + (5)];
	qp_offset = tokens_Size[(index_Size % SIZE_Size) + (6)];
	i = 0;
	while (i <= sizeOfTU * sizeOfTU - 1) {
		tmp_Coeff = tokens_Coeff[(index_Coeff % SIZE_Coeff) + (i)];
		tabTransCoeffLevel[i] = tmp_Coeff;
		i = i + 1;
	}
	i0 = 0;
	while (i0 <= 4 * 4 - 1) {
		tmp_tabTransCoeffLevel = tabTransCoeffLevel[i0];
		tokens_Coeff_4x4_IT[(index_Coeff_4x4_IT % SIZE_Coeff_4x4_IT) + (i0)] = tmp_tabTransCoeffLevel;
		i0 = i0 + 1;
	}

	// Update ports indexes
	index_Coeff += 16;
	read_end_Coeff();
	index_Size += 7;
	read_end_Size();
	index_Coeff_4x4_IT += 16;
	write_end_Coeff_4x4_IT();

	rate_Coeff += 16;
	rate_Size += 7;
}
static i32 isSchedulable_split_4x4_skipIT() {
	i32 result;
	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;

	sizeOfTU = tokens_Size[(index_Size + (0)) % SIZE_Size];
	RCskip = tokens_Size[(index_Size + (1)) % SIZE_Size];
	isDST = tokens_Size[(index_Size + (2)) % SIZE_Size];
	transformSkipFlag = tokens_Size[(index_Size + (3)) % SIZE_Size];
	slice_qp = tokens_Size[(index_Size + (4)) % SIZE_Size];
	rc_cIdx = tokens_Size[(index_Size + (5)) % SIZE_Size];
	qp_offset = tokens_Size[(index_Size + (6)) % SIZE_Size];
	result = sizeOfTU == 4 && RCskip != 0 && transformSkipFlag == 0;
	return result;
}

static void split_4x4_skipIT() {

	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;

	sizeOfTU = tokens_Size[(index_Size + (0)) % SIZE_Size];
	RCskip = tokens_Size[(index_Size + (1)) % SIZE_Size];
	isDST = tokens_Size[(index_Size + (2)) % SIZE_Size];
	transformSkipFlag = tokens_Size[(index_Size + (3)) % SIZE_Size];
	slice_qp = tokens_Size[(index_Size + (4)) % SIZE_Size];
	rc_cIdx = tokens_Size[(index_Size + (5)) % SIZE_Size];
	qp_offset = tokens_Size[(index_Size + (6)) % SIZE_Size];

	// Update ports indexes
	index_Size += 7;
	read_end_Size();

	rate_Size += 7;
}
static void split_4x4_skipIT_aligned() {

	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;

	sizeOfTU = tokens_Size[(index_Size % SIZE_Size) + (0)];
	RCskip = tokens_Size[(index_Size % SIZE_Size) + (1)];
	isDST = tokens_Size[(index_Size % SIZE_Size) + (2)];
	transformSkipFlag = tokens_Size[(index_Size % SIZE_Size) + (3)];
	slice_qp = tokens_Size[(index_Size % SIZE_Size) + (4)];
	rc_cIdx = tokens_Size[(index_Size % SIZE_Size) + (5)];
	qp_offset = tokens_Size[(index_Size % SIZE_Size) + (6)];

	// Update ports indexes
	index_Size += 7;
	read_end_Size();

	rate_Size += 7;
}
static i32 isSchedulable_split_8x8_trans_skip() {
	i32 result;
	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;

	sizeOfTU = tokens_Size[(index_Size + (0)) % SIZE_Size];
	RCskip = tokens_Size[(index_Size + (1)) % SIZE_Size];
	isDST = tokens_Size[(index_Size + (2)) % SIZE_Size];
	transformSkipFlag = tokens_Size[(index_Size + (3)) % SIZE_Size];
	slice_qp = tokens_Size[(index_Size + (4)) % SIZE_Size];
	rc_cIdx = tokens_Size[(index_Size + (5)) % SIZE_Size];
	qp_offset = tokens_Size[(index_Size + (6)) % SIZE_Size];
	result = sizeOfTU == 8 && RCskip == 0 && transformSkipFlag == 1;
	return result;
}

static void split_8x8_trans_skip() {

	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;
	i32 local_MAX_TR_DYNAMIC_RANGE;
	i32 local_BIT_DEPTH;
	i32 shift;
	i32 transformSkipShift;
	i32 offset;
	i32 i;
	i16 tmp_Coeff;
	i32 i0;
	i16 tmp_tabTransCoeffLevel;

	sizeOfTU = tokens_Size[(index_Size + (0)) % SIZE_Size];
	RCskip = tokens_Size[(index_Size + (1)) % SIZE_Size];
	isDST = tokens_Size[(index_Size + (2)) % SIZE_Size];
	transformSkipFlag = tokens_Size[(index_Size + (3)) % SIZE_Size];
	slice_qp = tokens_Size[(index_Size + (4)) % SIZE_Size];
	rc_cIdx = tokens_Size[(index_Size + (5)) % SIZE_Size];
	qp_offset = tokens_Size[(index_Size + (6)) % SIZE_Size];
	local_MAX_TR_DYNAMIC_RANGE = MAX_TR_DYNAMIC_RANGE;
	local_BIT_DEPTH = BIT_DEPTH;
	shift = local_MAX_TR_DYNAMIC_RANGE - local_BIT_DEPTH - 3;
	transformSkipShift = shift;
	offset = 1 << (transformSkipShift - 1);
	i = 0;
	while (i <= sizeOfTU * sizeOfTU - 1) {
		tmp_Coeff = tokens_Coeff[(index_Coeff + (i)) % SIZE_Coeff];
		tabTransCoeffLevel[i] = tmp_Coeff;
		i = i + 1;
	}
	i0 = 0;
	while (i0 <= 63) {
		tmp_tabTransCoeffLevel = tabTransCoeffLevel[i0];
		tokens_Coeff_skip[(index_Coeff_skip + (i0)) % SIZE_Coeff_skip] = (tmp_tabTransCoeffLevel + offset) >> transformSkipShift;
		i0 = i0 + 1;
	}

	// Update ports indexes
	index_Coeff += 64;
	read_end_Coeff();
	index_Size += 7;
	read_end_Size();
	index_Coeff_skip += 64;
	write_end_Coeff_skip();

	rate_Coeff += 64;
	rate_Size += 7;
}
static void split_8x8_trans_skip_aligned() {

	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;
	i32 local_MAX_TR_DYNAMIC_RANGE;
	i32 local_BIT_DEPTH;
	i32 shift;
	i32 transformSkipShift;
	i32 offset;
	i32 i;
	i16 tmp_Coeff;
	i32 i0;
	i16 tmp_tabTransCoeffLevel;

	sizeOfTU = tokens_Size[(index_Size % SIZE_Size) + (0)];
	RCskip = tokens_Size[(index_Size % SIZE_Size) + (1)];
	isDST = tokens_Size[(index_Size % SIZE_Size) + (2)];
	transformSkipFlag = tokens_Size[(index_Size % SIZE_Size) + (3)];
	slice_qp = tokens_Size[(index_Size % SIZE_Size) + (4)];
	rc_cIdx = tokens_Size[(index_Size % SIZE_Size) + (5)];
	qp_offset = tokens_Size[(index_Size % SIZE_Size) + (6)];
	local_MAX_TR_DYNAMIC_RANGE = MAX_TR_DYNAMIC_RANGE;
	local_BIT_DEPTH = BIT_DEPTH;
	shift = local_MAX_TR_DYNAMIC_RANGE - local_BIT_DEPTH - 3;
	transformSkipShift = shift;
	offset = 1 << (transformSkipShift - 1);
	i = 0;
	while (i <= sizeOfTU * sizeOfTU - 1) {
		tmp_Coeff = tokens_Coeff[(index_Coeff % SIZE_Coeff) + (i)];
		tabTransCoeffLevel[i] = tmp_Coeff;
		i = i + 1;
	}
	i0 = 0;
	while (i0 <= 63) {
		tmp_tabTransCoeffLevel = tabTransCoeffLevel[i0];
		tokens_Coeff_skip[(index_Coeff_skip % SIZE_Coeff_skip) + (i0)] = (tmp_tabTransCoeffLevel + offset) >> transformSkipShift;
		i0 = i0 + 1;
	}

	// Update ports indexes
	index_Coeff += 64;
	read_end_Coeff();
	index_Size += 7;
	read_end_Size();
	index_Coeff_skip += 64;
	write_end_Coeff_skip();

	rate_Coeff += 64;
	rate_Size += 7;
}
static i32 isSchedulable_split_8x8_default() {
	i32 result;
	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;

	sizeOfTU = tokens_Size[(index_Size + (0)) % SIZE_Size];
	RCskip = tokens_Size[(index_Size + (1)) % SIZE_Size];
	isDST = tokens_Size[(index_Size + (2)) % SIZE_Size];
	transformSkipFlag = tokens_Size[(index_Size + (3)) % SIZE_Size];
	slice_qp = tokens_Size[(index_Size + (4)) % SIZE_Size];
	rc_cIdx = tokens_Size[(index_Size + (5)) % SIZE_Size];
	qp_offset = tokens_Size[(index_Size + (6)) % SIZE_Size];
	result = sizeOfTU == 8 && RCskip == 0 && transformSkipFlag == 0;
	return result;
}

static void split_8x8_default() {

	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;
	i32 i;
	i16 tmp_Coeff;
	i32 i0;
	i16 tmp_tabTransCoeffLevel;

	sizeOfTU = tokens_Size[(index_Size + (0)) % SIZE_Size];
	RCskip = tokens_Size[(index_Size + (1)) % SIZE_Size];
	isDST = tokens_Size[(index_Size + (2)) % SIZE_Size];
	transformSkipFlag = tokens_Size[(index_Size + (3)) % SIZE_Size];
	slice_qp = tokens_Size[(index_Size + (4)) % SIZE_Size];
	rc_cIdx = tokens_Size[(index_Size + (5)) % SIZE_Size];
	qp_offset = tokens_Size[(index_Size + (6)) % SIZE_Size];
	i = 0;
	while (i <= sizeOfTU * sizeOfTU - 1) {
		tmp_Coeff = tokens_Coeff[(index_Coeff + (i)) % SIZE_Coeff];
		tabTransCoeffLevel[i] = tmp_Coeff;
		i = i + 1;
	}
	i0 = 0;
	while (i0 <= 8 * 8 - 1) {
		tmp_tabTransCoeffLevel = tabTransCoeffLevel[i0];
		tokens_Coeff_8x8[(index_Coeff_8x8 % SIZE_Coeff_8x8) + (i0)] = tmp_tabTransCoeffLevel;
		i0 = i0 + 1;
	}

	// Update ports indexes
	index_Coeff += 64;
	read_end_Coeff();
	index_Size += 7;
	read_end_Size();
	index_Coeff_8x8 += 64;
	write_end_Coeff_8x8();

	rate_Coeff += 64;
	rate_Size += 7;
}
static void split_8x8_default_aligned() {

	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;
	i32 i;
	i16 tmp_Coeff;
	i32 i0;
	i16 tmp_tabTransCoeffLevel;

	sizeOfTU = tokens_Size[(index_Size % SIZE_Size) + (0)];
	RCskip = tokens_Size[(index_Size % SIZE_Size) + (1)];
	isDST = tokens_Size[(index_Size % SIZE_Size) + (2)];
	transformSkipFlag = tokens_Size[(index_Size % SIZE_Size) + (3)];
	slice_qp = tokens_Size[(index_Size % SIZE_Size) + (4)];
	rc_cIdx = tokens_Size[(index_Size % SIZE_Size) + (5)];
	qp_offset = tokens_Size[(index_Size % SIZE_Size) + (6)];
	i = 0;
	while (i <= sizeOfTU * sizeOfTU - 1) {
		tmp_Coeff = tokens_Coeff[(index_Coeff % SIZE_Coeff) + (i)];
		tabTransCoeffLevel[i] = tmp_Coeff;
		i = i + 1;
	}
	i0 = 0;
	while (i0 <= 8 * 8 - 1) {
		tmp_tabTransCoeffLevel = tabTransCoeffLevel[i0];
		tokens_Coeff_8x8[(index_Coeff_8x8 % SIZE_Coeff_8x8) + (i0)] = tmp_tabTransCoeffLevel;
		i0 = i0 + 1;
	}

	// Update ports indexes
	index_Coeff += 64;
	read_end_Coeff();
	index_Size += 7;
	read_end_Size();
	index_Coeff_8x8 += 64;
	write_end_Coeff_8x8();

	rate_Coeff += 64;
	rate_Size += 7;
}
static i32 isSchedulable_split_8x8_skip() {
	i32 result;
	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;

	sizeOfTU = tokens_Size[(index_Size + (0)) % SIZE_Size];
	RCskip = tokens_Size[(index_Size + (1)) % SIZE_Size];
	isDST = tokens_Size[(index_Size + (2)) % SIZE_Size];
	transformSkipFlag = tokens_Size[(index_Size + (3)) % SIZE_Size];
	slice_qp = tokens_Size[(index_Size + (4)) % SIZE_Size];
	rc_cIdx = tokens_Size[(index_Size + (5)) % SIZE_Size];
	qp_offset = tokens_Size[(index_Size + (6)) % SIZE_Size];
	result = sizeOfTU == 8 && RCskip != 0 && transformSkipFlag == 0;
	return result;
}

static void split_8x8_skip() {

	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;

	sizeOfTU = tokens_Size[(index_Size + (0)) % SIZE_Size];
	RCskip = tokens_Size[(index_Size + (1)) % SIZE_Size];
	isDST = tokens_Size[(index_Size + (2)) % SIZE_Size];
	transformSkipFlag = tokens_Size[(index_Size + (3)) % SIZE_Size];
	slice_qp = tokens_Size[(index_Size + (4)) % SIZE_Size];
	rc_cIdx = tokens_Size[(index_Size + (5)) % SIZE_Size];
	qp_offset = tokens_Size[(index_Size + (6)) % SIZE_Size];

	// Update ports indexes
	index_Size += 7;
	read_end_Size();

	rate_Size += 7;
}
static void split_8x8_skip_aligned() {

	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;

	sizeOfTU = tokens_Size[(index_Size % SIZE_Size) + (0)];
	RCskip = tokens_Size[(index_Size % SIZE_Size) + (1)];
	isDST = tokens_Size[(index_Size % SIZE_Size) + (2)];
	transformSkipFlag = tokens_Size[(index_Size % SIZE_Size) + (3)];
	slice_qp = tokens_Size[(index_Size % SIZE_Size) + (4)];
	rc_cIdx = tokens_Size[(index_Size % SIZE_Size) + (5)];
	qp_offset = tokens_Size[(index_Size % SIZE_Size) + (6)];

	// Update ports indexes
	index_Size += 7;
	read_end_Size();

	rate_Size += 7;
}
static i32 isSchedulable_split_16x16_trans_skip() {
	i32 result;
	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;

	sizeOfTU = tokens_Size[(index_Size + (0)) % SIZE_Size];
	RCskip = tokens_Size[(index_Size + (1)) % SIZE_Size];
	isDST = tokens_Size[(index_Size + (2)) % SIZE_Size];
	transformSkipFlag = tokens_Size[(index_Size + (3)) % SIZE_Size];
	slice_qp = tokens_Size[(index_Size + (4)) % SIZE_Size];
	rc_cIdx = tokens_Size[(index_Size + (5)) % SIZE_Size];
	qp_offset = tokens_Size[(index_Size + (6)) % SIZE_Size];
	result = sizeOfTU == 16 && RCskip == 0 && transformSkipFlag == 1;
	return result;
}

static void split_16x16_trans_skip() {

	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;
	i32 local_MAX_TR_DYNAMIC_RANGE;
	i32 local_BIT_DEPTH;
	i32 shift;
	i32 transformSkipShift;
	i32 offset;
	i32 i;
	i16 tmp_Coeff;
	i32 i0;
	i16 tmp_tabTransCoeffLevel;

	sizeOfTU = tokens_Size[(index_Size + (0)) % SIZE_Size];
	RCskip = tokens_Size[(index_Size + (1)) % SIZE_Size];
	isDST = tokens_Size[(index_Size + (2)) % SIZE_Size];
	transformSkipFlag = tokens_Size[(index_Size + (3)) % SIZE_Size];
	slice_qp = tokens_Size[(index_Size + (4)) % SIZE_Size];
	rc_cIdx = tokens_Size[(index_Size + (5)) % SIZE_Size];
	qp_offset = tokens_Size[(index_Size + (6)) % SIZE_Size];
	local_MAX_TR_DYNAMIC_RANGE = MAX_TR_DYNAMIC_RANGE;
	local_BIT_DEPTH = BIT_DEPTH;
	shift = local_MAX_TR_DYNAMIC_RANGE - local_BIT_DEPTH - 4;
	transformSkipShift = shift;
	offset = 1 << (transformSkipShift - 1);
	i = 0;
	while (i <= sizeOfTU * sizeOfTU - 1) {
		tmp_Coeff = tokens_Coeff[(index_Coeff + (i)) % SIZE_Coeff];
		tabTransCoeffLevel[i] = tmp_Coeff;
		i = i + 1;
	}
	i0 = 0;
	while (i0 <= 255) {
		tmp_tabTransCoeffLevel = tabTransCoeffLevel[i0];
		tokens_Coeff_skip[(index_Coeff_skip + (i0)) % SIZE_Coeff_skip] = (tmp_tabTransCoeffLevel + offset) >> transformSkipShift;
		i0 = i0 + 1;
	}

	// Update ports indexes
	index_Coeff += 256;
	read_end_Coeff();
	index_Size += 7;
	read_end_Size();
	index_Coeff_skip += 256;
	write_end_Coeff_skip();

	rate_Coeff += 256;
	rate_Size += 7;
}
static void split_16x16_trans_skip_aligned() {

	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;
	i32 local_MAX_TR_DYNAMIC_RANGE;
	i32 local_BIT_DEPTH;
	i32 shift;
	i32 transformSkipShift;
	i32 offset;
	i32 i;
	i16 tmp_Coeff;
	i32 i0;
	i16 tmp_tabTransCoeffLevel;

	sizeOfTU = tokens_Size[(index_Size % SIZE_Size) + (0)];
	RCskip = tokens_Size[(index_Size % SIZE_Size) + (1)];
	isDST = tokens_Size[(index_Size % SIZE_Size) + (2)];
	transformSkipFlag = tokens_Size[(index_Size % SIZE_Size) + (3)];
	slice_qp = tokens_Size[(index_Size % SIZE_Size) + (4)];
	rc_cIdx = tokens_Size[(index_Size % SIZE_Size) + (5)];
	qp_offset = tokens_Size[(index_Size % SIZE_Size) + (6)];
	local_MAX_TR_DYNAMIC_RANGE = MAX_TR_DYNAMIC_RANGE;
	local_BIT_DEPTH = BIT_DEPTH;
	shift = local_MAX_TR_DYNAMIC_RANGE - local_BIT_DEPTH - 4;
	transformSkipShift = shift;
	offset = 1 << (transformSkipShift - 1);
	i = 0;
	while (i <= sizeOfTU * sizeOfTU - 1) {
		tmp_Coeff = tokens_Coeff[(index_Coeff % SIZE_Coeff) + (i)];
		tabTransCoeffLevel[i] = tmp_Coeff;
		i = i + 1;
	}
	i0 = 0;
	while (i0 <= 255) {
		tmp_tabTransCoeffLevel = tabTransCoeffLevel[i0];
		tokens_Coeff_skip[(index_Coeff_skip % SIZE_Coeff_skip) + (i0)] = (tmp_tabTransCoeffLevel + offset) >> transformSkipShift;
		i0 = i0 + 1;
	}

	// Update ports indexes
	index_Coeff += 256;
	read_end_Coeff();
	index_Size += 7;
	read_end_Size();
	index_Coeff_skip += 256;
	write_end_Coeff_skip();

	rate_Coeff += 256;
	rate_Size += 7;
}
static i32 isSchedulable_split_16x16_default() {
	i32 result;
	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;

	sizeOfTU = tokens_Size[(index_Size + (0)) % SIZE_Size];
	RCskip = tokens_Size[(index_Size + (1)) % SIZE_Size];
	isDST = tokens_Size[(index_Size + (2)) % SIZE_Size];
	transformSkipFlag = tokens_Size[(index_Size + (3)) % SIZE_Size];
	slice_qp = tokens_Size[(index_Size + (4)) % SIZE_Size];
	rc_cIdx = tokens_Size[(index_Size + (5)) % SIZE_Size];
	qp_offset = tokens_Size[(index_Size + (6)) % SIZE_Size];
	result = sizeOfTU == 16 && RCskip == 0 && transformSkipFlag == 0;
	return result;
}

static void split_16x16_default() {

	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;
	i32 i;
	i16 tmp_Coeff;
	i32 i0;
	i16 tmp_tabTransCoeffLevel;

	sizeOfTU = tokens_Size[(index_Size + (0)) % SIZE_Size];
	RCskip = tokens_Size[(index_Size + (1)) % SIZE_Size];
	isDST = tokens_Size[(index_Size + (2)) % SIZE_Size];
	transformSkipFlag = tokens_Size[(index_Size + (3)) % SIZE_Size];
	slice_qp = tokens_Size[(index_Size + (4)) % SIZE_Size];
	rc_cIdx = tokens_Size[(index_Size + (5)) % SIZE_Size];
	qp_offset = tokens_Size[(index_Size + (6)) % SIZE_Size];
	i = 0;
	while (i <= sizeOfTU * sizeOfTU - 1) {
		tmp_Coeff = tokens_Coeff[(index_Coeff + (i)) % SIZE_Coeff];
		tabTransCoeffLevel[i] = tmp_Coeff;
		i = i + 1;
	}
	i0 = 0;
	while (i0 <= 16 * 16 - 1) {
		tmp_tabTransCoeffLevel = tabTransCoeffLevel[i0];
		tokens_Coeff_16x16[(index_Coeff_16x16 % SIZE_Coeff_16x16) + (i0)] = tmp_tabTransCoeffLevel;
		i0 = i0 + 1;
	}

	// Update ports indexes
	index_Coeff += 256;
	read_end_Coeff();
	index_Size += 7;
	read_end_Size();
	index_Coeff_16x16 += 256;
	write_end_Coeff_16x16();

	rate_Coeff += 256;
	rate_Size += 7;
}
static void split_16x16_default_aligned() {

	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;
	i32 i;
	i16 tmp_Coeff;
	i32 i0;
	i16 tmp_tabTransCoeffLevel;

	sizeOfTU = tokens_Size[(index_Size % SIZE_Size) + (0)];
	RCskip = tokens_Size[(index_Size % SIZE_Size) + (1)];
	isDST = tokens_Size[(index_Size % SIZE_Size) + (2)];
	transformSkipFlag = tokens_Size[(index_Size % SIZE_Size) + (3)];
	slice_qp = tokens_Size[(index_Size % SIZE_Size) + (4)];
	rc_cIdx = tokens_Size[(index_Size % SIZE_Size) + (5)];
	qp_offset = tokens_Size[(index_Size % SIZE_Size) + (6)];
	i = 0;
	while (i <= sizeOfTU * sizeOfTU - 1) {
		tmp_Coeff = tokens_Coeff[(index_Coeff % SIZE_Coeff) + (i)];
		tabTransCoeffLevel[i] = tmp_Coeff;
		i = i + 1;
	}
	i0 = 0;
	while (i0 <= 16 * 16 - 1) {
		tmp_tabTransCoeffLevel = tabTransCoeffLevel[i0];
		tokens_Coeff_16x16[(index_Coeff_16x16 % SIZE_Coeff_16x16) + (i0)] = tmp_tabTransCoeffLevel;
		i0 = i0 + 1;
	}

	// Update ports indexes
	index_Coeff += 256;
	read_end_Coeff();
	index_Size += 7;
	read_end_Size();
	index_Coeff_16x16 += 256;
	write_end_Coeff_16x16();

	rate_Coeff += 256;
	rate_Size += 7;
}
static i32 isSchedulable_split_16x16_skip() {
	i32 result;
	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;

	sizeOfTU = tokens_Size[(index_Size + (0)) % SIZE_Size];
	RCskip = tokens_Size[(index_Size + (1)) % SIZE_Size];
	isDST = tokens_Size[(index_Size + (2)) % SIZE_Size];
	transformSkipFlag = tokens_Size[(index_Size + (3)) % SIZE_Size];
	slice_qp = tokens_Size[(index_Size + (4)) % SIZE_Size];
	rc_cIdx = tokens_Size[(index_Size + (5)) % SIZE_Size];
	qp_offset = tokens_Size[(index_Size + (6)) % SIZE_Size];
	result = sizeOfTU == 16 && RCskip != 0 && transformSkipFlag == 0;
	return result;
}

static void split_16x16_skip() {

	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;

	sizeOfTU = tokens_Size[(index_Size + (0)) % SIZE_Size];
	RCskip = tokens_Size[(index_Size + (1)) % SIZE_Size];
	isDST = tokens_Size[(index_Size + (2)) % SIZE_Size];
	transformSkipFlag = tokens_Size[(index_Size + (3)) % SIZE_Size];
	slice_qp = tokens_Size[(index_Size + (4)) % SIZE_Size];
	rc_cIdx = tokens_Size[(index_Size + (5)) % SIZE_Size];
	qp_offset = tokens_Size[(index_Size + (6)) % SIZE_Size];

	// Update ports indexes
	index_Size += 7;
	read_end_Size();

	rate_Size += 7;
}
static void split_16x16_skip_aligned() {

	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;

	sizeOfTU = tokens_Size[(index_Size % SIZE_Size) + (0)];
	RCskip = tokens_Size[(index_Size % SIZE_Size) + (1)];
	isDST = tokens_Size[(index_Size % SIZE_Size) + (2)];
	transformSkipFlag = tokens_Size[(index_Size % SIZE_Size) + (3)];
	slice_qp = tokens_Size[(index_Size % SIZE_Size) + (4)];
	rc_cIdx = tokens_Size[(index_Size % SIZE_Size) + (5)];
	qp_offset = tokens_Size[(index_Size % SIZE_Size) + (6)];

	// Update ports indexes
	index_Size += 7;
	read_end_Size();

	rate_Size += 7;
}
static i32 isSchedulable_split_32x32_trans_skip() {
	i32 result;
	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;

	sizeOfTU = tokens_Size[(index_Size + (0)) % SIZE_Size];
	RCskip = tokens_Size[(index_Size + (1)) % SIZE_Size];
	isDST = tokens_Size[(index_Size + (2)) % SIZE_Size];
	transformSkipFlag = tokens_Size[(index_Size + (3)) % SIZE_Size];
	slice_qp = tokens_Size[(index_Size + (4)) % SIZE_Size];
	rc_cIdx = tokens_Size[(index_Size + (5)) % SIZE_Size];
	qp_offset = tokens_Size[(index_Size + (6)) % SIZE_Size];
	result = sizeOfTU == 32 && RCskip == 0 && transformSkipFlag == 1;
	return result;
}

static void split_32x32_trans_skip() {

	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;
	i32 local_MAX_TR_DYNAMIC_RANGE;
	i32 local_BIT_DEPTH;
	i32 shift;
	i32 transformSkipShift;
	i32 offset;
	i32 i;
	i16 tmp_Coeff;
	i32 i0;
	i16 tmp_tabTransCoeffLevel;

	sizeOfTU = tokens_Size[(index_Size + (0)) % SIZE_Size];
	RCskip = tokens_Size[(index_Size + (1)) % SIZE_Size];
	isDST = tokens_Size[(index_Size + (2)) % SIZE_Size];
	transformSkipFlag = tokens_Size[(index_Size + (3)) % SIZE_Size];
	slice_qp = tokens_Size[(index_Size + (4)) % SIZE_Size];
	rc_cIdx = tokens_Size[(index_Size + (5)) % SIZE_Size];
	qp_offset = tokens_Size[(index_Size + (6)) % SIZE_Size];
	local_MAX_TR_DYNAMIC_RANGE = MAX_TR_DYNAMIC_RANGE;
	local_BIT_DEPTH = BIT_DEPTH;
	shift = local_MAX_TR_DYNAMIC_RANGE - local_BIT_DEPTH - 5;
	transformSkipShift = shift;
	offset = 1 << (transformSkipShift - 1);
	i = 0;
	while (i <= sizeOfTU * sizeOfTU - 1) {
		tmp_Coeff = tokens_Coeff[(index_Coeff + (i)) % SIZE_Coeff];
		tabTransCoeffLevel[i] = tmp_Coeff;
		i = i + 1;
	}
	i0 = 0;
	while (i0 <= 1023) {
		tmp_tabTransCoeffLevel = tabTransCoeffLevel[i0];
		tokens_Coeff_skip[(index_Coeff_skip + (i0)) % SIZE_Coeff_skip] = (tmp_tabTransCoeffLevel + offset) >> transformSkipShift;
		i0 = i0 + 1;
	}

	// Update ports indexes
	index_Coeff += 1024;
	read_end_Coeff();
	index_Size += 7;
	read_end_Size();
	index_Coeff_skip += 1024;
	write_end_Coeff_skip();

	rate_Coeff += 1024;
	rate_Size += 7;
}
static void split_32x32_trans_skip_aligned() {

	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;
	i32 local_MAX_TR_DYNAMIC_RANGE;
	i32 local_BIT_DEPTH;
	i32 shift;
	i32 transformSkipShift;
	i32 offset;
	i32 i;
	i16 tmp_Coeff;
	i32 i0;
	i16 tmp_tabTransCoeffLevel;

	sizeOfTU = tokens_Size[(index_Size % SIZE_Size) + (0)];
	RCskip = tokens_Size[(index_Size % SIZE_Size) + (1)];
	isDST = tokens_Size[(index_Size % SIZE_Size) + (2)];
	transformSkipFlag = tokens_Size[(index_Size % SIZE_Size) + (3)];
	slice_qp = tokens_Size[(index_Size % SIZE_Size) + (4)];
	rc_cIdx = tokens_Size[(index_Size % SIZE_Size) + (5)];
	qp_offset = tokens_Size[(index_Size % SIZE_Size) + (6)];
	local_MAX_TR_DYNAMIC_RANGE = MAX_TR_DYNAMIC_RANGE;
	local_BIT_DEPTH = BIT_DEPTH;
	shift = local_MAX_TR_DYNAMIC_RANGE - local_BIT_DEPTH - 5;
	transformSkipShift = shift;
	offset = 1 << (transformSkipShift - 1);
	i = 0;
	while (i <= sizeOfTU * sizeOfTU - 1) {
		tmp_Coeff = tokens_Coeff[(index_Coeff % SIZE_Coeff) + (i)];
		tabTransCoeffLevel[i] = tmp_Coeff;
		i = i + 1;
	}
	i0 = 0;
	while (i0 <= 1023) {
		tmp_tabTransCoeffLevel = tabTransCoeffLevel[i0];
		tokens_Coeff_skip[(index_Coeff_skip % SIZE_Coeff_skip) + (i0)] = (tmp_tabTransCoeffLevel + offset) >> transformSkipShift;
		i0 = i0 + 1;
	}

	// Update ports indexes
	index_Coeff += 1024;
	read_end_Coeff();
	index_Size += 7;
	read_end_Size();
	index_Coeff_skip += 1024;
	write_end_Coeff_skip();

	rate_Coeff += 1024;
	rate_Size += 7;
}
static i32 isSchedulable_split_32x32_default() {
	i32 result;
	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;

	sizeOfTU = tokens_Size[(index_Size + (0)) % SIZE_Size];
	RCskip = tokens_Size[(index_Size + (1)) % SIZE_Size];
	isDST = tokens_Size[(index_Size + (2)) % SIZE_Size];
	transformSkipFlag = tokens_Size[(index_Size + (3)) % SIZE_Size];
	slice_qp = tokens_Size[(index_Size + (4)) % SIZE_Size];
	rc_cIdx = tokens_Size[(index_Size + (5)) % SIZE_Size];
	qp_offset = tokens_Size[(index_Size + (6)) % SIZE_Size];
	result = sizeOfTU == 32 && RCskip == 0 && transformSkipFlag == 0;
	return result;
}

static void split_32x32_default() {

	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;
	i32 i;
	i16 tmp_Coeff;
	i32 i0;
	i16 tmp_tabTransCoeffLevel;

	sizeOfTU = tokens_Size[(index_Size + (0)) % SIZE_Size];
	RCskip = tokens_Size[(index_Size + (1)) % SIZE_Size];
	isDST = tokens_Size[(index_Size + (2)) % SIZE_Size];
	transformSkipFlag = tokens_Size[(index_Size + (3)) % SIZE_Size];
	slice_qp = tokens_Size[(index_Size + (4)) % SIZE_Size];
	rc_cIdx = tokens_Size[(index_Size + (5)) % SIZE_Size];
	qp_offset = tokens_Size[(index_Size + (6)) % SIZE_Size];
	i = 0;
	while (i <= sizeOfTU * sizeOfTU - 1) {
		tmp_Coeff = tokens_Coeff[(index_Coeff + (i)) % SIZE_Coeff];
		tabTransCoeffLevel[i] = tmp_Coeff;
		i = i + 1;
	}
	i0 = 0;
	while (i0 <= 32 * 32 - 1) {
		tmp_tabTransCoeffLevel = tabTransCoeffLevel[i0];
		tokens_Coeff_32x32[(index_Coeff_32x32 % SIZE_Coeff_32x32) + (i0)] = tmp_tabTransCoeffLevel;
		i0 = i0 + 1;
	}

	// Update ports indexes
	index_Coeff += 1024;
	read_end_Coeff();
	index_Size += 7;
	read_end_Size();
	index_Coeff_32x32 += 1024;
	write_end_Coeff_32x32();

	rate_Coeff += 1024;
	rate_Size += 7;
}
static void split_32x32_default_aligned() {

	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;
	i32 i;
	i16 tmp_Coeff;
	i32 i0;
	i16 tmp_tabTransCoeffLevel;

	sizeOfTU = tokens_Size[(index_Size % SIZE_Size) + (0)];
	RCskip = tokens_Size[(index_Size % SIZE_Size) + (1)];
	isDST = tokens_Size[(index_Size % SIZE_Size) + (2)];
	transformSkipFlag = tokens_Size[(index_Size % SIZE_Size) + (3)];
	slice_qp = tokens_Size[(index_Size % SIZE_Size) + (4)];
	rc_cIdx = tokens_Size[(index_Size % SIZE_Size) + (5)];
	qp_offset = tokens_Size[(index_Size % SIZE_Size) + (6)];
	i = 0;
	while (i <= sizeOfTU * sizeOfTU - 1) {
		tmp_Coeff = tokens_Coeff[(index_Coeff % SIZE_Coeff) + (i)];
		tabTransCoeffLevel[i] = tmp_Coeff;
		i = i + 1;
	}
	i0 = 0;
	while (i0 <= 32 * 32 - 1) {
		tmp_tabTransCoeffLevel = tabTransCoeffLevel[i0];
		tokens_Coeff_32x32[(index_Coeff_32x32 % SIZE_Coeff_32x32) + (i0)] = tmp_tabTransCoeffLevel;
		i0 = i0 + 1;
	}

	// Update ports indexes
	index_Coeff += 1024;
	read_end_Coeff();
	index_Size += 7;
	read_end_Size();
	index_Coeff_32x32 += 1024;
	write_end_Coeff_32x32();

	rate_Coeff += 1024;
	rate_Size += 7;
}
static i32 isSchedulable_split_32x32_skip() {
	i32 result;
	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;

	sizeOfTU = tokens_Size[(index_Size + (0)) % SIZE_Size];
	RCskip = tokens_Size[(index_Size + (1)) % SIZE_Size];
	isDST = tokens_Size[(index_Size + (2)) % SIZE_Size];
	transformSkipFlag = tokens_Size[(index_Size + (3)) % SIZE_Size];
	slice_qp = tokens_Size[(index_Size + (4)) % SIZE_Size];
	rc_cIdx = tokens_Size[(index_Size + (5)) % SIZE_Size];
	qp_offset = tokens_Size[(index_Size + (6)) % SIZE_Size];
	result = sizeOfTU == 32 && RCskip != 0 && transformSkipFlag == 0;
	return result;
}

static void split_32x32_skip() {

	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;

	sizeOfTU = tokens_Size[(index_Size + (0)) % SIZE_Size];
	RCskip = tokens_Size[(index_Size + (1)) % SIZE_Size];
	isDST = tokens_Size[(index_Size + (2)) % SIZE_Size];
	transformSkipFlag = tokens_Size[(index_Size + (3)) % SIZE_Size];
	slice_qp = tokens_Size[(index_Size + (4)) % SIZE_Size];
	rc_cIdx = tokens_Size[(index_Size + (5)) % SIZE_Size];
	qp_offset = tokens_Size[(index_Size + (6)) % SIZE_Size];

	// Update ports indexes
	index_Size += 7;
	read_end_Size();

	rate_Size += 7;
}
static void split_32x32_skip_aligned() {

	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;

	sizeOfTU = tokens_Size[(index_Size % SIZE_Size) + (0)];
	RCskip = tokens_Size[(index_Size % SIZE_Size) + (1)];
	isDST = tokens_Size[(index_Size % SIZE_Size) + (2)];
	transformSkipFlag = tokens_Size[(index_Size % SIZE_Size) + (3)];
	slice_qp = tokens_Size[(index_Size % SIZE_Size) + (4)];
	rc_cIdx = tokens_Size[(index_Size % SIZE_Size) + (5)];
	qp_offset = tokens_Size[(index_Size % SIZE_Size) + (6)];

	// Update ports indexes
	index_Size += 7;
	read_end_Size();

	rate_Size += 7;
}
static i32 isSchedulable_split_64x64_skip() {
	i32 result;
	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;

	sizeOfTU = tokens_Size[(index_Size + (0)) % SIZE_Size];
	RCskip = tokens_Size[(index_Size + (1)) % SIZE_Size];
	isDST = tokens_Size[(index_Size + (2)) % SIZE_Size];
	transformSkipFlag = tokens_Size[(index_Size + (3)) % SIZE_Size];
	slice_qp = tokens_Size[(index_Size + (4)) % SIZE_Size];
	rc_cIdx = tokens_Size[(index_Size + (5)) % SIZE_Size];
	qp_offset = tokens_Size[(index_Size + (6)) % SIZE_Size];
	result = sizeOfTU == 64 && RCskip != 0 && transformSkipFlag == 0;
	return result;
}

static void split_64x64_skip() {

	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;

	sizeOfTU = tokens_Size[(index_Size + (0)) % SIZE_Size];
	RCskip = tokens_Size[(index_Size + (1)) % SIZE_Size];
	isDST = tokens_Size[(index_Size + (2)) % SIZE_Size];
	transformSkipFlag = tokens_Size[(index_Size + (3)) % SIZE_Size];
	slice_qp = tokens_Size[(index_Size + (4)) % SIZE_Size];
	rc_cIdx = tokens_Size[(index_Size + (5)) % SIZE_Size];
	qp_offset = tokens_Size[(index_Size + (6)) % SIZE_Size];

	// Update ports indexes
	index_Size += 7;
	read_end_Size();

	rate_Size += 7;
}
static void split_64x64_skip_aligned() {

	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;

	sizeOfTU = tokens_Size[(index_Size % SIZE_Size) + (0)];
	RCskip = tokens_Size[(index_Size % SIZE_Size) + (1)];
	isDST = tokens_Size[(index_Size % SIZE_Size) + (2)];
	transformSkipFlag = tokens_Size[(index_Size % SIZE_Size) + (3)];
	slice_qp = tokens_Size[(index_Size % SIZE_Size) + (4)];
	rc_cIdx = tokens_Size[(index_Size % SIZE_Size) + (5)];
	qp_offset = tokens_Size[(index_Size % SIZE_Size) + (6)];

	// Update ports indexes
	index_Size += 7;
	read_end_Size();

	rate_Size += 7;
}

////////////////////////////////////////////////////////////////////////////////
// Initializes

void HevcDecoder_xIT_IT_Splitter_initialize(schedinfo_t *si) {
	int i = 0;
	write_Coeff_4x4_DST();
	write_Coeff_4x4_IT();
	write_Coeff_8x8();
	write_Coeff_16x16();
	write_Coeff_32x32();
	write_Coeff_skip();
finished:
	write_end_Coeff_4x4_DST();
	write_end_Coeff_4x4_IT();
	write_end_Coeff_8x8();
	write_end_Coeff_16x16();
	write_end_Coeff_32x32();
	write_end_Coeff_skip();
	return;
}

////////////////////////////////////////////////////////////////////////////////
// Action scheduler
void HevcDecoder_xIT_IT_Splitter_scheduler(schedinfo_t *si) {
	int i = 0;
	si->ports = 0;

	read_Coeff();
	read_Size();
	write_Coeff_4x4_DST();
	write_Coeff_4x4_IT();
	write_Coeff_8x8();
	write_Coeff_16x16();
	write_Coeff_32x32();
	write_Coeff_skip();

	while (1) {
		if (numTokens_Coeff - index_Coeff >= 16 && numTokens_Size - index_Size >= 7 && isSchedulable_split_4x4_transf_skip()) {
			int stop = 0;
			if (16 > SIZE_Coeff_skip - index_Coeff_skip + HevcDecoder_xIT_IT_Splitter_Coeff_skip->read_inds[0]) {
				stop = 1;
			}
			if (stop != 0) {
				si->num_firings = i;
				si->reason = full;
				goto finished;
			}
			{
				int isAligned = 1;
				isAligned &= ((index_Coeff % SIZE_Coeff) < ((index_Coeff + 16) % SIZE_Coeff));
				isAligned &= ((index_Size % SIZE_Size) < ((index_Size + 7) % SIZE_Size));
				isAligned &= ((index_Coeff_skip % SIZE_Coeff_skip) < ((index_Coeff_skip + 16) % SIZE_Coeff_skip));
				if (isAligned) {
					split_4x4_transf_skip_aligned();
				} else {
					split_4x4_transf_skip();
				}
			}
			i++;
		} else if (numTokens_Coeff - index_Coeff >= 16 && numTokens_Size - index_Size >= 7 && isSchedulable_split_4x4_DST()) {
			int stop = 0;
			if (16 > SIZE_Coeff_4x4_DST - index_Coeff_4x4_DST + HevcDecoder_xIT_IT_Splitter_Coeff_4x4_DST->read_inds[0]) {
				stop = 1;
			}
			if (stop != 0) {
				si->num_firings = i;
				si->reason = full;
				goto finished;
			}
			{
				int isAligned = 1;
				isAligned &= ((index_Coeff % SIZE_Coeff) < ((index_Coeff + 16) % SIZE_Coeff));
				isAligned &= ((index_Size % SIZE_Size) < ((index_Size + 7) % SIZE_Size));
				if (isAligned) {
					split_4x4_DST_aligned();
				} else {
					split_4x4_DST();
				}
			}
			i++;
		} else if (numTokens_Coeff - index_Coeff >= 16 && numTokens_Size - index_Size >= 7 && isSchedulable_split_4x4_IT()) {
			int stop = 0;
			if (16 > SIZE_Coeff_4x4_IT - index_Coeff_4x4_IT + HevcDecoder_xIT_IT_Splitter_Coeff_4x4_IT->read_inds[0]) {
				stop = 1;
			}
			if (stop != 0) {
				si->num_firings = i;
				si->reason = full;
				goto finished;
			}
			{
				int isAligned = 1;
				isAligned &= ((index_Coeff % SIZE_Coeff) < ((index_Coeff + 16) % SIZE_Coeff));
				isAligned &= ((index_Size % SIZE_Size) < ((index_Size + 7) % SIZE_Size));
				if (isAligned) {
					split_4x4_IT_aligned();
				} else {
					split_4x4_IT();
				}
			}
			i++;
		} else if (numTokens_Size - index_Size >= 7 && isSchedulable_split_4x4_skipIT()) {
			{
				int isAligned = 1;
				isAligned &= ((index_Size % SIZE_Size) < ((index_Size + 7) % SIZE_Size));
				if (isAligned) {
					split_4x4_skipIT_aligned();
				} else {
					split_4x4_skipIT();
				}
			}
			i++;
		} else if (numTokens_Coeff - index_Coeff >= 64 && numTokens_Size - index_Size >= 7 && isSchedulable_split_8x8_trans_skip()) {
			int stop = 0;
			if (64 > SIZE_Coeff_skip - index_Coeff_skip + HevcDecoder_xIT_IT_Splitter_Coeff_skip->read_inds[0]) {
				stop = 1;
			}
			if (stop != 0) {
				si->num_firings = i;
				si->reason = full;
				goto finished;
			}
			{
				int isAligned = 1;
				isAligned &= ((index_Coeff % SIZE_Coeff) < ((index_Coeff + 64) % SIZE_Coeff));
				isAligned &= ((index_Size % SIZE_Size) < ((index_Size + 7) % SIZE_Size));
				isAligned &= ((index_Coeff_skip % SIZE_Coeff_skip) < ((index_Coeff_skip + 64) % SIZE_Coeff_skip));
				if (isAligned) {
					split_8x8_trans_skip_aligned();
				} else {
					split_8x8_trans_skip();
				}
			}
			i++;
		} else if (numTokens_Coeff - index_Coeff >= 64 && numTokens_Size - index_Size >= 7 && isSchedulable_split_8x8_default()) {
			int stop = 0;
			if (64 > SIZE_Coeff_8x8 - index_Coeff_8x8 + HevcDecoder_xIT_IT_Splitter_Coeff_8x8->read_inds[0]) {
				stop = 1;
			}
			if (stop != 0) {
				si->num_firings = i;
				si->reason = full;
				goto finished;
			}
			{
				int isAligned = 1;
				isAligned &= ((index_Coeff % SIZE_Coeff) < ((index_Coeff + 64) % SIZE_Coeff));
				isAligned &= ((index_Size % SIZE_Size) < ((index_Size + 7) % SIZE_Size));
				if (isAligned) {
					split_8x8_default_aligned();
				} else {
					split_8x8_default();
				}
			}
			i++;
		} else if (numTokens_Size - index_Size >= 7 && isSchedulable_split_8x8_skip()) {
			{
				int isAligned = 1;
				isAligned &= ((index_Size % SIZE_Size) < ((index_Size + 7) % SIZE_Size));
				if (isAligned) {
					split_8x8_skip_aligned();
				} else {
					split_8x8_skip();
				}
			}
			i++;
		} else if (numTokens_Coeff - index_Coeff >= 256 && numTokens_Size - index_Size >= 7 && isSchedulable_split_16x16_trans_skip()) {
			int stop = 0;
			if (256 > SIZE_Coeff_skip - index_Coeff_skip + HevcDecoder_xIT_IT_Splitter_Coeff_skip->read_inds[0]) {
				stop = 1;
			}
			if (stop != 0) {
				si->num_firings = i;
				si->reason = full;
				goto finished;
			}
			{
				int isAligned = 1;
				isAligned &= ((index_Coeff % SIZE_Coeff) < ((index_Coeff + 256) % SIZE_Coeff));
				isAligned &= ((index_Size % SIZE_Size) < ((index_Size + 7) % SIZE_Size));
				isAligned &= ((index_Coeff_skip % SIZE_Coeff_skip) < ((index_Coeff_skip + 256) % SIZE_Coeff_skip));
				if (isAligned) {
					split_16x16_trans_skip_aligned();
				} else {
					split_16x16_trans_skip();
				}
			}
			i++;
		} else if (numTokens_Coeff - index_Coeff >= 256 && numTokens_Size - index_Size >= 7 && isSchedulable_split_16x16_default()) {
			int stop = 0;
			if (256 > SIZE_Coeff_16x16 - index_Coeff_16x16 + HevcDecoder_xIT_IT_Splitter_Coeff_16x16->read_inds[0]) {
				stop = 1;
			}
			if (stop != 0) {
				si->num_firings = i;
				si->reason = full;
				goto finished;
			}
			{
				int isAligned = 1;
				isAligned &= ((index_Coeff % SIZE_Coeff) < ((index_Coeff + 256) % SIZE_Coeff));
				isAligned &= ((index_Size % SIZE_Size) < ((index_Size + 7) % SIZE_Size));
				if (isAligned) {
					split_16x16_default_aligned();
				} else {
					split_16x16_default();
				}
			}
			i++;
		} else if (numTokens_Size - index_Size >= 7 && isSchedulable_split_16x16_skip()) {
			{
				int isAligned = 1;
				isAligned &= ((index_Size % SIZE_Size) < ((index_Size + 7) % SIZE_Size));
				if (isAligned) {
					split_16x16_skip_aligned();
				} else {
					split_16x16_skip();
				}
			}
			i++;
		} else if (numTokens_Coeff - index_Coeff >= 1024 && numTokens_Size - index_Size >= 7 && isSchedulable_split_32x32_trans_skip()) {
			int stop = 0;
			if (1024 > SIZE_Coeff_skip - index_Coeff_skip + HevcDecoder_xIT_IT_Splitter_Coeff_skip->read_inds[0]) {
				stop = 1;
			}
			if (stop != 0) {
				si->num_firings = i;
				si->reason = full;
				goto finished;
			}
			{
				int isAligned = 1;
				isAligned &= ((index_Coeff % SIZE_Coeff) < ((index_Coeff + 1024) % SIZE_Coeff));
				isAligned &= ((index_Size % SIZE_Size) < ((index_Size + 7) % SIZE_Size));
				isAligned &= ((index_Coeff_skip % SIZE_Coeff_skip) < ((index_Coeff_skip + 1024) % SIZE_Coeff_skip));
				if (isAligned) {
					split_32x32_trans_skip_aligned();
				} else {
					split_32x32_trans_skip();
				}
			}
			i++;
		} else if (numTokens_Coeff - index_Coeff >= 1024 && numTokens_Size - index_Size >= 7 && isSchedulable_split_32x32_default()) {
			int stop = 0;
			if (1024 > SIZE_Coeff_32x32 - index_Coeff_32x32 + HevcDecoder_xIT_IT_Splitter_Coeff_32x32->read_inds[0]) {
				stop = 1;
			}
			if (stop != 0) {
				si->num_firings = i;
				si->reason = full;
				goto finished;
			}
			{
				int isAligned = 1;
				isAligned &= ((index_Coeff % SIZE_Coeff) < ((index_Coeff + 1024) % SIZE_Coeff));
				isAligned &= ((index_Size % SIZE_Size) < ((index_Size + 7) % SIZE_Size));
				if (isAligned) {
					split_32x32_default_aligned();
				} else {
					split_32x32_default();
				}
			}
			i++;
		} else if (numTokens_Size - index_Size >= 7 && isSchedulable_split_32x32_skip()) {
			{
				int isAligned = 1;
				isAligned &= ((index_Size % SIZE_Size) < ((index_Size + 7) % SIZE_Size));
				if (isAligned) {
					split_32x32_skip_aligned();
				} else {
					split_32x32_skip();
				}
			}
			i++;
		} else if (numTokens_Size - index_Size >= 7 && isSchedulable_split_64x64_skip()) {
			{
				int isAligned = 1;
				isAligned &= ((index_Size % SIZE_Size) < ((index_Size + 7) % SIZE_Size));
				if (isAligned) {
					split_64x64_skip_aligned();
				} else {
					split_64x64_skip();
				}
			}
			i++;
		} else {
			si->num_firings = i;
			si->reason = starved;
			goto finished;
		}
	}

finished:

	read_end_Coeff();
	read_end_Size();
	write_end_Coeff_4x4_DST();
	write_end_Coeff_4x4_IT();
	write_end_Coeff_8x8();
	write_end_Coeff_16x16();
	write_end_Coeff_32x32();
	write_end_Coeff_skip();
}
