// Source file is "L/RVC/src/org/sc29/wg11/mpegh/part2/main/IT/IT_Merger.cal"

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
extern actor_t HevcDecoder_xIT_IT_Merger;

////////////////////////////////////////////////////////////////////////////////
// Input FIFOs
extern fifo_i8_t *HevcDecoder_xIT_IT_Merger_Size;
extern fifo_i16_t *HevcDecoder_xIT_IT_Merger_Block_skip;
extern fifo_i16_t *HevcDecoder_xIT_IT_Merger_Block_4x4_DST;
extern fifo_i16_t *HevcDecoder_xIT_IT_Merger_Block_4x4_IT;
extern fifo_i16_t *HevcDecoder_xIT_IT_Merger_Block_8x8;
extern fifo_i16_t *HevcDecoder_xIT_IT_Merger_Block_16x16;
extern fifo_i16_t *HevcDecoder_xIT_IT_Merger_Block_32x32;

////////////////////////////////////////////////////////////////////////////////
// Input Fifo control variables
static unsigned int index_Size;
static unsigned int numTokens_Size;
#define SIZE_Size SIZE
#define tokens_Size HevcDecoder_xIT_IT_Merger_Size->contents

extern connection_t connection_HevcDecoder_xIT_IT_Merger_Size;
#define rate_Size connection_HevcDecoder_xIT_IT_Merger_Size.rate

static unsigned int index_Block_skip;
static unsigned int numTokens_Block_skip;
#define SIZE_Block_skip SIZE
#define tokens_Block_skip HevcDecoder_xIT_IT_Merger_Block_skip->contents

extern connection_t connection_HevcDecoder_xIT_IT_Merger_Block_skip;
#define rate_Block_skip connection_HevcDecoder_xIT_IT_Merger_Block_skip.rate

static unsigned int index_Block_4x4_DST;
static unsigned int numTokens_Block_4x4_DST;
#define SIZE_Block_4x4_DST SIZE
#define tokens_Block_4x4_DST HevcDecoder_xIT_IT_Merger_Block_4x4_DST->contents

extern connection_t connection_HevcDecoder_xIT_IT_Merger_Block_4x4_DST;
#define rate_Block_4x4_DST connection_HevcDecoder_xIT_IT_Merger_Block_4x4_DST.rate

static unsigned int index_Block_4x4_IT;
static unsigned int numTokens_Block_4x4_IT;
#define SIZE_Block_4x4_IT SIZE
#define tokens_Block_4x4_IT HevcDecoder_xIT_IT_Merger_Block_4x4_IT->contents

extern connection_t connection_HevcDecoder_xIT_IT_Merger_Block_4x4_IT;
#define rate_Block_4x4_IT connection_HevcDecoder_xIT_IT_Merger_Block_4x4_IT.rate

static unsigned int index_Block_8x8;
static unsigned int numTokens_Block_8x8;
#define SIZE_Block_8x8 SIZE
#define tokens_Block_8x8 HevcDecoder_xIT_IT_Merger_Block_8x8->contents

extern connection_t connection_HevcDecoder_xIT_IT_Merger_Block_8x8;
#define rate_Block_8x8 connection_HevcDecoder_xIT_IT_Merger_Block_8x8.rate

static unsigned int index_Block_16x16;
static unsigned int numTokens_Block_16x16;
#define SIZE_Block_16x16 SIZE
#define tokens_Block_16x16 HevcDecoder_xIT_IT_Merger_Block_16x16->contents

extern connection_t connection_HevcDecoder_xIT_IT_Merger_Block_16x16;
#define rate_Block_16x16 connection_HevcDecoder_xIT_IT_Merger_Block_16x16.rate

static unsigned int index_Block_32x32;
static unsigned int numTokens_Block_32x32;
#define SIZE_Block_32x32 SIZE
#define tokens_Block_32x32 HevcDecoder_xIT_IT_Merger_Block_32x32->contents

extern connection_t connection_HevcDecoder_xIT_IT_Merger_Block_32x32;
#define rate_Block_32x32 connection_HevcDecoder_xIT_IT_Merger_Block_32x32.rate

////////////////////////////////////////////////////////////////////////////////
// Predecessors
extern actor_t HevcDecoder_Algo_Parser;
extern actor_t HevcDecoder_xIT_IT_Splitter;
extern actor_t HevcDecoder_xIT_invDST4x4_2nd;
extern actor_t HevcDecoder_xIT_IT4x4_IT4x4_1d_1;
extern actor_t HevcDecoder_xIT_IT8x8_IT8x8_1d_1;
extern actor_t HevcDecoder_xIT_IT16x16_IT16x16_1d_1;
extern actor_t HevcDecoder_xIT_IT32x32_IT32x32_1d_1;

////////////////////////////////////////////////////////////////////////////////
// Output FIFOs
extern fifo_i16_t *HevcDecoder_xIT_IT_Merger_Block;

////////////////////////////////////////////////////////////////////////////////
// Output Fifo control variables
static unsigned int index_Block;
static unsigned int numFree_Block;
#define NUM_READERS_Block 1
#define SIZE_Block SIZE
#define tokens_Block HevcDecoder_xIT_IT_Merger_Block->contents

////////////////////////////////////////////////////////////////////////////////
// Successors
extern actor_t HevcDecoder_xIT_Block_Merger;




////////////////////////////////////////////////////////////////////////////////
// Token functions
static void read_Size() {
	index_Size = HevcDecoder_xIT_IT_Merger_Size->read_inds[1];
	numTokens_Size = index_Size + fifo_i8_get_num_tokens(HevcDecoder_xIT_IT_Merger_Size, 1);
}

static void read_end_Size() {
	HevcDecoder_xIT_IT_Merger_Size->read_inds[1] = index_Size;
}
static void read_Block_skip() {
	index_Block_skip = HevcDecoder_xIT_IT_Merger_Block_skip->read_inds[0];
	numTokens_Block_skip = index_Block_skip + fifo_i16_get_num_tokens(HevcDecoder_xIT_IT_Merger_Block_skip, 0);
}

static void read_end_Block_skip() {
	HevcDecoder_xIT_IT_Merger_Block_skip->read_inds[0] = index_Block_skip;
}
static void read_Block_4x4_DST() {
	index_Block_4x4_DST = HevcDecoder_xIT_IT_Merger_Block_4x4_DST->read_inds[0];
	numTokens_Block_4x4_DST = index_Block_4x4_DST + fifo_i16_get_num_tokens(HevcDecoder_xIT_IT_Merger_Block_4x4_DST, 0);
}

static void read_end_Block_4x4_DST() {
	HevcDecoder_xIT_IT_Merger_Block_4x4_DST->read_inds[0] = index_Block_4x4_DST;
}
static void read_Block_4x4_IT() {
	index_Block_4x4_IT = HevcDecoder_xIT_IT_Merger_Block_4x4_IT->read_inds[0];
	numTokens_Block_4x4_IT = index_Block_4x4_IT + fifo_i16_get_num_tokens(HevcDecoder_xIT_IT_Merger_Block_4x4_IT, 0);
}

static void read_end_Block_4x4_IT() {
	HevcDecoder_xIT_IT_Merger_Block_4x4_IT->read_inds[0] = index_Block_4x4_IT;
}
static void read_Block_8x8() {
	index_Block_8x8 = HevcDecoder_xIT_IT_Merger_Block_8x8->read_inds[0];
	numTokens_Block_8x8 = index_Block_8x8 + fifo_i16_get_num_tokens(HevcDecoder_xIT_IT_Merger_Block_8x8, 0);
}

static void read_end_Block_8x8() {
	HevcDecoder_xIT_IT_Merger_Block_8x8->read_inds[0] = index_Block_8x8;
}
static void read_Block_16x16() {
	index_Block_16x16 = HevcDecoder_xIT_IT_Merger_Block_16x16->read_inds[0];
	numTokens_Block_16x16 = index_Block_16x16 + fifo_i16_get_num_tokens(HevcDecoder_xIT_IT_Merger_Block_16x16, 0);
}

static void read_end_Block_16x16() {
	HevcDecoder_xIT_IT_Merger_Block_16x16->read_inds[0] = index_Block_16x16;
}
static void read_Block_32x32() {
	index_Block_32x32 = HevcDecoder_xIT_IT_Merger_Block_32x32->read_inds[0];
	numTokens_Block_32x32 = index_Block_32x32 + fifo_i16_get_num_tokens(HevcDecoder_xIT_IT_Merger_Block_32x32, 0);
}

static void read_end_Block_32x32() {
	HevcDecoder_xIT_IT_Merger_Block_32x32->read_inds[0] = index_Block_32x32;
}

static void write_Block() {
	index_Block = HevcDecoder_xIT_IT_Merger_Block->write_ind;
	numFree_Block = index_Block + fifo_i16_get_room(HevcDecoder_xIT_IT_Merger_Block, NUM_READERS_Block, SIZE_Block);
}

static void write_end_Block() {
	HevcDecoder_xIT_IT_Merger_Block->write_ind = index_Block;
}

////////////////////////////////////////////////////////////////////////////////
// Functions/procedures


////////////////////////////////////////////////////////////////////////////////
// Actions
static i32 isSchedulable_merge_4x4_trans_skip() {
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

static void merge_4x4_trans_skip() {

	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;
	i32 idx_Block_skip;
	i16 local_Block_skip;

	sizeOfTU = tokens_Size[(index_Size + (0)) % SIZE_Size];
	RCskip = tokens_Size[(index_Size + (1)) % SIZE_Size];
	isDST = tokens_Size[(index_Size + (2)) % SIZE_Size];
	transformSkipFlag = tokens_Size[(index_Size + (3)) % SIZE_Size];
	slice_qp = tokens_Size[(index_Size + (4)) % SIZE_Size];
	rc_cIdx = tokens_Size[(index_Size + (5)) % SIZE_Size];
	qp_offset = tokens_Size[(index_Size + (6)) % SIZE_Size];
	idx_Block_skip = 0;
	while (idx_Block_skip < 16) {
		local_Block_skip = tokens_Block_skip[(index_Block_skip + (idx_Block_skip)) % SIZE_Block_skip];
		tokens_Block[(index_Block + (idx_Block_skip)) % SIZE_Block] = local_Block_skip;
		idx_Block_skip = idx_Block_skip + 1;
	}

	// Update ports indexes
	index_Size += 7;
	read_end_Size();
	index_Block_skip += 16;
	read_end_Block_skip();
	index_Block += 16;
	write_end_Block();

	rate_Size += 7;
	rate_Block_skip += 16;
}
static void merge_4x4_trans_skip_aligned() {

	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;
	i32 idx_Block_skip;
	i16 local_Block_skip;

	sizeOfTU = tokens_Size[(index_Size % SIZE_Size) + (0)];
	RCskip = tokens_Size[(index_Size % SIZE_Size) + (1)];
	isDST = tokens_Size[(index_Size % SIZE_Size) + (2)];
	transformSkipFlag = tokens_Size[(index_Size % SIZE_Size) + (3)];
	slice_qp = tokens_Size[(index_Size % SIZE_Size) + (4)];
	rc_cIdx = tokens_Size[(index_Size % SIZE_Size) + (5)];
	qp_offset = tokens_Size[(index_Size % SIZE_Size) + (6)];
	idx_Block_skip = 0;
	while (idx_Block_skip < 16) {
		local_Block_skip = tokens_Block_skip[(index_Block_skip % SIZE_Block_skip) + (idx_Block_skip)];
		tokens_Block[(index_Block % SIZE_Block) + (idx_Block_skip)] = local_Block_skip;
		idx_Block_skip = idx_Block_skip + 1;
	}

	// Update ports indexes
	index_Size += 7;
	read_end_Size();
	index_Block_skip += 16;
	read_end_Block_skip();
	index_Block += 16;
	write_end_Block();

	rate_Size += 7;
	rate_Block_skip += 16;
}
static i32 isSchedulable_merge_4x4_DST() {
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

static void merge_4x4_DST() {

	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;
	i32 idx_Block_4x4_DST;
	i16 local_Block_4x4_DST;

	sizeOfTU = tokens_Size[(index_Size + (0)) % SIZE_Size];
	RCskip = tokens_Size[(index_Size + (1)) % SIZE_Size];
	isDST = tokens_Size[(index_Size + (2)) % SIZE_Size];
	transformSkipFlag = tokens_Size[(index_Size + (3)) % SIZE_Size];
	slice_qp = tokens_Size[(index_Size + (4)) % SIZE_Size];
	rc_cIdx = tokens_Size[(index_Size + (5)) % SIZE_Size];
	qp_offset = tokens_Size[(index_Size + (6)) % SIZE_Size];
	idx_Block_4x4_DST = 0;
	while (idx_Block_4x4_DST < 16) {
		local_Block_4x4_DST = tokens_Block_4x4_DST[(index_Block_4x4_DST % SIZE_Block_4x4_DST) + (idx_Block_4x4_DST)];
		tokens_Block[(index_Block + (idx_Block_4x4_DST)) % SIZE_Block] = local_Block_4x4_DST;
		idx_Block_4x4_DST = idx_Block_4x4_DST + 1;
	}

	// Update ports indexes
	index_Size += 7;
	read_end_Size();
	index_Block_4x4_DST += 16;
	read_end_Block_4x4_DST();
	index_Block += 16;
	write_end_Block();

	rate_Size += 7;
	rate_Block_4x4_DST += 16;
}
static void merge_4x4_DST_aligned() {

	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;
	i32 idx_Block_4x4_DST;
	i16 local_Block_4x4_DST;

	sizeOfTU = tokens_Size[(index_Size % SIZE_Size) + (0)];
	RCskip = tokens_Size[(index_Size % SIZE_Size) + (1)];
	isDST = tokens_Size[(index_Size % SIZE_Size) + (2)];
	transformSkipFlag = tokens_Size[(index_Size % SIZE_Size) + (3)];
	slice_qp = tokens_Size[(index_Size % SIZE_Size) + (4)];
	rc_cIdx = tokens_Size[(index_Size % SIZE_Size) + (5)];
	qp_offset = tokens_Size[(index_Size % SIZE_Size) + (6)];
	idx_Block_4x4_DST = 0;
	while (idx_Block_4x4_DST < 16) {
		local_Block_4x4_DST = tokens_Block_4x4_DST[(index_Block_4x4_DST % SIZE_Block_4x4_DST) + (idx_Block_4x4_DST)];
		tokens_Block[(index_Block % SIZE_Block) + (idx_Block_4x4_DST)] = local_Block_4x4_DST;
		idx_Block_4x4_DST = idx_Block_4x4_DST + 1;
	}

	// Update ports indexes
	index_Size += 7;
	read_end_Size();
	index_Block_4x4_DST += 16;
	read_end_Block_4x4_DST();
	index_Block += 16;
	write_end_Block();

	rate_Size += 7;
	rate_Block_4x4_DST += 16;
}
static i32 isSchedulable_merge_4x4_IT() {
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

static void merge_4x4_IT() {

	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;
	i32 idx_Block_4x4_IT;
	i16 local_Block_4x4_IT;

	sizeOfTU = tokens_Size[(index_Size + (0)) % SIZE_Size];
	RCskip = tokens_Size[(index_Size + (1)) % SIZE_Size];
	isDST = tokens_Size[(index_Size + (2)) % SIZE_Size];
	transformSkipFlag = tokens_Size[(index_Size + (3)) % SIZE_Size];
	slice_qp = tokens_Size[(index_Size + (4)) % SIZE_Size];
	rc_cIdx = tokens_Size[(index_Size + (5)) % SIZE_Size];
	qp_offset = tokens_Size[(index_Size + (6)) % SIZE_Size];
	idx_Block_4x4_IT = 0;
	while (idx_Block_4x4_IT < 16) {
		local_Block_4x4_IT = tokens_Block_4x4_IT[(index_Block_4x4_IT % SIZE_Block_4x4_IT) + (idx_Block_4x4_IT)];
		tokens_Block[(index_Block + (idx_Block_4x4_IT)) % SIZE_Block] = local_Block_4x4_IT;
		idx_Block_4x4_IT = idx_Block_4x4_IT + 1;
	}

	// Update ports indexes
	index_Size += 7;
	read_end_Size();
	index_Block_4x4_IT += 16;
	read_end_Block_4x4_IT();
	index_Block += 16;
	write_end_Block();

	rate_Size += 7;
	rate_Block_4x4_IT += 16;
}
static void merge_4x4_IT_aligned() {

	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;
	i32 idx_Block_4x4_IT;
	i16 local_Block_4x4_IT;

	sizeOfTU = tokens_Size[(index_Size % SIZE_Size) + (0)];
	RCskip = tokens_Size[(index_Size % SIZE_Size) + (1)];
	isDST = tokens_Size[(index_Size % SIZE_Size) + (2)];
	transformSkipFlag = tokens_Size[(index_Size % SIZE_Size) + (3)];
	slice_qp = tokens_Size[(index_Size % SIZE_Size) + (4)];
	rc_cIdx = tokens_Size[(index_Size % SIZE_Size) + (5)];
	qp_offset = tokens_Size[(index_Size % SIZE_Size) + (6)];
	idx_Block_4x4_IT = 0;
	while (idx_Block_4x4_IT < 16) {
		local_Block_4x4_IT = tokens_Block_4x4_IT[(index_Block_4x4_IT % SIZE_Block_4x4_IT) + (idx_Block_4x4_IT)];
		tokens_Block[(index_Block % SIZE_Block) + (idx_Block_4x4_IT)] = local_Block_4x4_IT;
		idx_Block_4x4_IT = idx_Block_4x4_IT + 1;
	}

	// Update ports indexes
	index_Size += 7;
	read_end_Size();
	index_Block_4x4_IT += 16;
	read_end_Block_4x4_IT();
	index_Block += 16;
	write_end_Block();

	rate_Size += 7;
	rate_Block_4x4_IT += 16;
}
static i32 isSchedulable_merge_4x4_skip() {
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
	result = sizeOfTU == 4 && RCskip != 0;
	return result;
}

static void merge_4x4_skip() {

	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;
	i32 i;

	sizeOfTU = tokens_Size[(index_Size + (0)) % SIZE_Size];
	RCskip = tokens_Size[(index_Size + (1)) % SIZE_Size];
	isDST = tokens_Size[(index_Size + (2)) % SIZE_Size];
	transformSkipFlag = tokens_Size[(index_Size + (3)) % SIZE_Size];
	slice_qp = tokens_Size[(index_Size + (4)) % SIZE_Size];
	rc_cIdx = tokens_Size[(index_Size + (5)) % SIZE_Size];
	qp_offset = tokens_Size[(index_Size + (6)) % SIZE_Size];
	i = 1;
	while (i <= 4 * 4) {
		tokens_Block[(index_Block + (i - 1)) % SIZE_Block] = 0;
		i = i + 1;
	}

	// Update ports indexes
	index_Size += 7;
	read_end_Size();
	index_Block += 16;
	write_end_Block();

	rate_Size += 7;
}
static void merge_4x4_skip_aligned() {

	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;
	i32 i;

	sizeOfTU = tokens_Size[(index_Size % SIZE_Size) + (0)];
	RCskip = tokens_Size[(index_Size % SIZE_Size) + (1)];
	isDST = tokens_Size[(index_Size % SIZE_Size) + (2)];
	transformSkipFlag = tokens_Size[(index_Size % SIZE_Size) + (3)];
	slice_qp = tokens_Size[(index_Size % SIZE_Size) + (4)];
	rc_cIdx = tokens_Size[(index_Size % SIZE_Size) + (5)];
	qp_offset = tokens_Size[(index_Size % SIZE_Size) + (6)];
	i = 1;
	while (i <= 4 * 4) {
		tokens_Block[(index_Block % SIZE_Block) + (i - 1)] = 0;
		i = i + 1;
	}

	// Update ports indexes
	index_Size += 7;
	read_end_Size();
	index_Block += 16;
	write_end_Block();

	rate_Size += 7;
}
static i32 isSchedulable_merge_8x8_trans_skip() {
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

static void merge_8x8_trans_skip() {

	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;
	i32 idx_Block_skip;
	i16 local_Block_skip;

	sizeOfTU = tokens_Size[(index_Size + (0)) % SIZE_Size];
	RCskip = tokens_Size[(index_Size + (1)) % SIZE_Size];
	isDST = tokens_Size[(index_Size + (2)) % SIZE_Size];
	transformSkipFlag = tokens_Size[(index_Size + (3)) % SIZE_Size];
	slice_qp = tokens_Size[(index_Size + (4)) % SIZE_Size];
	rc_cIdx = tokens_Size[(index_Size + (5)) % SIZE_Size];
	qp_offset = tokens_Size[(index_Size + (6)) % SIZE_Size];
	idx_Block_skip = 0;
	while (idx_Block_skip < 64) {
		local_Block_skip = tokens_Block_skip[(index_Block_skip + (idx_Block_skip)) % SIZE_Block_skip];
		tokens_Block[(index_Block + (idx_Block_skip)) % SIZE_Block] = local_Block_skip;
		idx_Block_skip = idx_Block_skip + 1;
	}

	// Update ports indexes
	index_Size += 7;
	read_end_Size();
	index_Block_skip += 64;
	read_end_Block_skip();
	index_Block += 64;
	write_end_Block();

	rate_Size += 7;
	rate_Block_skip += 64;
}
static void merge_8x8_trans_skip_aligned() {

	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;
	i32 idx_Block_skip;
	i16 local_Block_skip;

	sizeOfTU = tokens_Size[(index_Size % SIZE_Size) + (0)];
	RCskip = tokens_Size[(index_Size % SIZE_Size) + (1)];
	isDST = tokens_Size[(index_Size % SIZE_Size) + (2)];
	transformSkipFlag = tokens_Size[(index_Size % SIZE_Size) + (3)];
	slice_qp = tokens_Size[(index_Size % SIZE_Size) + (4)];
	rc_cIdx = tokens_Size[(index_Size % SIZE_Size) + (5)];
	qp_offset = tokens_Size[(index_Size % SIZE_Size) + (6)];
	idx_Block_skip = 0;
	while (idx_Block_skip < 64) {
		local_Block_skip = tokens_Block_skip[(index_Block_skip % SIZE_Block_skip) + (idx_Block_skip)];
		tokens_Block[(index_Block % SIZE_Block) + (idx_Block_skip)] = local_Block_skip;
		idx_Block_skip = idx_Block_skip + 1;
	}

	// Update ports indexes
	index_Size += 7;
	read_end_Size();
	index_Block_skip += 64;
	read_end_Block_skip();
	index_Block += 64;
	write_end_Block();

	rate_Size += 7;
	rate_Block_skip += 64;
}
static i32 isSchedulable_merge_8x8_default() {
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

static void merge_8x8_default() {

	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;
	i32 idx_Block_8x8;
	i16 local_Block_8x8;

	sizeOfTU = tokens_Size[(index_Size + (0)) % SIZE_Size];
	RCskip = tokens_Size[(index_Size + (1)) % SIZE_Size];
	isDST = tokens_Size[(index_Size + (2)) % SIZE_Size];
	transformSkipFlag = tokens_Size[(index_Size + (3)) % SIZE_Size];
	slice_qp = tokens_Size[(index_Size + (4)) % SIZE_Size];
	rc_cIdx = tokens_Size[(index_Size + (5)) % SIZE_Size];
	qp_offset = tokens_Size[(index_Size + (6)) % SIZE_Size];
	idx_Block_8x8 = 0;
	while (idx_Block_8x8 < 64) {
		local_Block_8x8 = tokens_Block_8x8[(index_Block_8x8 % SIZE_Block_8x8) + (idx_Block_8x8)];
		tokens_Block[(index_Block + (idx_Block_8x8)) % SIZE_Block] = local_Block_8x8;
		idx_Block_8x8 = idx_Block_8x8 + 1;
	}

	// Update ports indexes
	index_Size += 7;
	read_end_Size();
	index_Block_8x8 += 64;
	read_end_Block_8x8();
	index_Block += 64;
	write_end_Block();

	rate_Size += 7;
	rate_Block_8x8 += 64;
}
static void merge_8x8_default_aligned() {

	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;
	i32 idx_Block_8x8;
	i16 local_Block_8x8;

	sizeOfTU = tokens_Size[(index_Size % SIZE_Size) + (0)];
	RCskip = tokens_Size[(index_Size % SIZE_Size) + (1)];
	isDST = tokens_Size[(index_Size % SIZE_Size) + (2)];
	transformSkipFlag = tokens_Size[(index_Size % SIZE_Size) + (3)];
	slice_qp = tokens_Size[(index_Size % SIZE_Size) + (4)];
	rc_cIdx = tokens_Size[(index_Size % SIZE_Size) + (5)];
	qp_offset = tokens_Size[(index_Size % SIZE_Size) + (6)];
	idx_Block_8x8 = 0;
	while (idx_Block_8x8 < 64) {
		local_Block_8x8 = tokens_Block_8x8[(index_Block_8x8 % SIZE_Block_8x8) + (idx_Block_8x8)];
		tokens_Block[(index_Block % SIZE_Block) + (idx_Block_8x8)] = local_Block_8x8;
		idx_Block_8x8 = idx_Block_8x8 + 1;
	}

	// Update ports indexes
	index_Size += 7;
	read_end_Size();
	index_Block_8x8 += 64;
	read_end_Block_8x8();
	index_Block += 64;
	write_end_Block();

	rate_Size += 7;
	rate_Block_8x8 += 64;
}
static i32 isSchedulable_merge_8x8_skip() {
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
	result = sizeOfTU == 8 && RCskip != 0;
	return result;
}

static void merge_8x8_skip() {

	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;
	i32 i;

	sizeOfTU = tokens_Size[(index_Size + (0)) % SIZE_Size];
	RCskip = tokens_Size[(index_Size + (1)) % SIZE_Size];
	isDST = tokens_Size[(index_Size + (2)) % SIZE_Size];
	transformSkipFlag = tokens_Size[(index_Size + (3)) % SIZE_Size];
	slice_qp = tokens_Size[(index_Size + (4)) % SIZE_Size];
	rc_cIdx = tokens_Size[(index_Size + (5)) % SIZE_Size];
	qp_offset = tokens_Size[(index_Size + (6)) % SIZE_Size];
	i = 1;
	while (i <= 8 * 8) {
		tokens_Block[(index_Block + (i - 1)) % SIZE_Block] = 0;
		i = i + 1;
	}

	// Update ports indexes
	index_Size += 7;
	read_end_Size();
	index_Block += 64;
	write_end_Block();

	rate_Size += 7;
}
static void merge_8x8_skip_aligned() {

	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;
	i32 i;

	sizeOfTU = tokens_Size[(index_Size % SIZE_Size) + (0)];
	RCskip = tokens_Size[(index_Size % SIZE_Size) + (1)];
	isDST = tokens_Size[(index_Size % SIZE_Size) + (2)];
	transformSkipFlag = tokens_Size[(index_Size % SIZE_Size) + (3)];
	slice_qp = tokens_Size[(index_Size % SIZE_Size) + (4)];
	rc_cIdx = tokens_Size[(index_Size % SIZE_Size) + (5)];
	qp_offset = tokens_Size[(index_Size % SIZE_Size) + (6)];
	i = 1;
	while (i <= 8 * 8) {
		tokens_Block[(index_Block % SIZE_Block) + (i - 1)] = 0;
		i = i + 1;
	}

	// Update ports indexes
	index_Size += 7;
	read_end_Size();
	index_Block += 64;
	write_end_Block();

	rate_Size += 7;
}
static i32 isSchedulable_merge_16x16_trans_skip() {
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

static void merge_16x16_trans_skip() {

	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;
	i32 idx_Block_skip;
	i16 local_Block_skip;

	sizeOfTU = tokens_Size[(index_Size + (0)) % SIZE_Size];
	RCskip = tokens_Size[(index_Size + (1)) % SIZE_Size];
	isDST = tokens_Size[(index_Size + (2)) % SIZE_Size];
	transformSkipFlag = tokens_Size[(index_Size + (3)) % SIZE_Size];
	slice_qp = tokens_Size[(index_Size + (4)) % SIZE_Size];
	rc_cIdx = tokens_Size[(index_Size + (5)) % SIZE_Size];
	qp_offset = tokens_Size[(index_Size + (6)) % SIZE_Size];
	idx_Block_skip = 0;
	while (idx_Block_skip < 256) {
		local_Block_skip = tokens_Block_skip[(index_Block_skip + (idx_Block_skip)) % SIZE_Block_skip];
		tokens_Block[(index_Block + (idx_Block_skip)) % SIZE_Block] = local_Block_skip;
		idx_Block_skip = idx_Block_skip + 1;
	}

	// Update ports indexes
	index_Size += 7;
	read_end_Size();
	index_Block_skip += 256;
	read_end_Block_skip();
	index_Block += 256;
	write_end_Block();

	rate_Size += 7;
	rate_Block_skip += 256;
}
static void merge_16x16_trans_skip_aligned() {

	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;
	i32 idx_Block_skip;
	i16 local_Block_skip;

	sizeOfTU = tokens_Size[(index_Size % SIZE_Size) + (0)];
	RCskip = tokens_Size[(index_Size % SIZE_Size) + (1)];
	isDST = tokens_Size[(index_Size % SIZE_Size) + (2)];
	transformSkipFlag = tokens_Size[(index_Size % SIZE_Size) + (3)];
	slice_qp = tokens_Size[(index_Size % SIZE_Size) + (4)];
	rc_cIdx = tokens_Size[(index_Size % SIZE_Size) + (5)];
	qp_offset = tokens_Size[(index_Size % SIZE_Size) + (6)];
	idx_Block_skip = 0;
	while (idx_Block_skip < 256) {
		local_Block_skip = tokens_Block_skip[(index_Block_skip % SIZE_Block_skip) + (idx_Block_skip)];
		tokens_Block[(index_Block % SIZE_Block) + (idx_Block_skip)] = local_Block_skip;
		idx_Block_skip = idx_Block_skip + 1;
	}

	// Update ports indexes
	index_Size += 7;
	read_end_Size();
	index_Block_skip += 256;
	read_end_Block_skip();
	index_Block += 256;
	write_end_Block();

	rate_Size += 7;
	rate_Block_skip += 256;
}
static i32 isSchedulable_merge_16x16_default() {
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

static void merge_16x16_default() {

	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;
	i32 idx_Block_16x16;
	i16 local_Block_16x16;

	sizeOfTU = tokens_Size[(index_Size + (0)) % SIZE_Size];
	RCskip = tokens_Size[(index_Size + (1)) % SIZE_Size];
	isDST = tokens_Size[(index_Size + (2)) % SIZE_Size];
	transformSkipFlag = tokens_Size[(index_Size + (3)) % SIZE_Size];
	slice_qp = tokens_Size[(index_Size + (4)) % SIZE_Size];
	rc_cIdx = tokens_Size[(index_Size + (5)) % SIZE_Size];
	qp_offset = tokens_Size[(index_Size + (6)) % SIZE_Size];
	idx_Block_16x16 = 0;
	while (idx_Block_16x16 < 256) {
		local_Block_16x16 = tokens_Block_16x16[(index_Block_16x16 % SIZE_Block_16x16) + (idx_Block_16x16)];
		tokens_Block[(index_Block + (idx_Block_16x16)) % SIZE_Block] = local_Block_16x16;
		idx_Block_16x16 = idx_Block_16x16 + 1;
	}

	// Update ports indexes
	index_Size += 7;
	read_end_Size();
	index_Block_16x16 += 256;
	read_end_Block_16x16();
	index_Block += 256;
	write_end_Block();

	rate_Size += 7;
	rate_Block_16x16 += 256;
}
static void merge_16x16_default_aligned() {

	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;
	i32 idx_Block_16x16;
	i16 local_Block_16x16;

	sizeOfTU = tokens_Size[(index_Size % SIZE_Size) + (0)];
	RCskip = tokens_Size[(index_Size % SIZE_Size) + (1)];
	isDST = tokens_Size[(index_Size % SIZE_Size) + (2)];
	transformSkipFlag = tokens_Size[(index_Size % SIZE_Size) + (3)];
	slice_qp = tokens_Size[(index_Size % SIZE_Size) + (4)];
	rc_cIdx = tokens_Size[(index_Size % SIZE_Size) + (5)];
	qp_offset = tokens_Size[(index_Size % SIZE_Size) + (6)];
	idx_Block_16x16 = 0;
	while (idx_Block_16x16 < 256) {
		local_Block_16x16 = tokens_Block_16x16[(index_Block_16x16 % SIZE_Block_16x16) + (idx_Block_16x16)];
		tokens_Block[(index_Block % SIZE_Block) + (idx_Block_16x16)] = local_Block_16x16;
		idx_Block_16x16 = idx_Block_16x16 + 1;
	}

	// Update ports indexes
	index_Size += 7;
	read_end_Size();
	index_Block_16x16 += 256;
	read_end_Block_16x16();
	index_Block += 256;
	write_end_Block();

	rate_Size += 7;
	rate_Block_16x16 += 256;
}
static i32 isSchedulable_merge_16x16_skip() {
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
	result = sizeOfTU == 16 && RCskip != 0;
	return result;
}

static void merge_16x16_skip() {

	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;
	i32 i;

	sizeOfTU = tokens_Size[(index_Size + (0)) % SIZE_Size];
	RCskip = tokens_Size[(index_Size + (1)) % SIZE_Size];
	isDST = tokens_Size[(index_Size + (2)) % SIZE_Size];
	transformSkipFlag = tokens_Size[(index_Size + (3)) % SIZE_Size];
	slice_qp = tokens_Size[(index_Size + (4)) % SIZE_Size];
	rc_cIdx = tokens_Size[(index_Size + (5)) % SIZE_Size];
	qp_offset = tokens_Size[(index_Size + (6)) % SIZE_Size];
	i = 1;
	while (i <= 16 * 16) {
		tokens_Block[(index_Block + (i - 1)) % SIZE_Block] = 0;
		i = i + 1;
	}

	// Update ports indexes
	index_Size += 7;
	read_end_Size();
	index_Block += 256;
	write_end_Block();

	rate_Size += 7;
}
static void merge_16x16_skip_aligned() {

	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;
	i32 i;

	sizeOfTU = tokens_Size[(index_Size % SIZE_Size) + (0)];
	RCskip = tokens_Size[(index_Size % SIZE_Size) + (1)];
	isDST = tokens_Size[(index_Size % SIZE_Size) + (2)];
	transformSkipFlag = tokens_Size[(index_Size % SIZE_Size) + (3)];
	slice_qp = tokens_Size[(index_Size % SIZE_Size) + (4)];
	rc_cIdx = tokens_Size[(index_Size % SIZE_Size) + (5)];
	qp_offset = tokens_Size[(index_Size % SIZE_Size) + (6)];
	i = 1;
	while (i <= 16 * 16) {
		tokens_Block[(index_Block % SIZE_Block) + (i - 1)] = 0;
		i = i + 1;
	}

	// Update ports indexes
	index_Size += 7;
	read_end_Size();
	index_Block += 256;
	write_end_Block();

	rate_Size += 7;
}
static i32 isSchedulable_merge_32x32_trans_skip() {
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

static void merge_32x32_trans_skip() {

	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;
	i32 idx_Block_skip;
	i16 local_Block_skip;

	sizeOfTU = tokens_Size[(index_Size + (0)) % SIZE_Size];
	RCskip = tokens_Size[(index_Size + (1)) % SIZE_Size];
	isDST = tokens_Size[(index_Size + (2)) % SIZE_Size];
	transformSkipFlag = tokens_Size[(index_Size + (3)) % SIZE_Size];
	slice_qp = tokens_Size[(index_Size + (4)) % SIZE_Size];
	rc_cIdx = tokens_Size[(index_Size + (5)) % SIZE_Size];
	qp_offset = tokens_Size[(index_Size + (6)) % SIZE_Size];
	idx_Block_skip = 0;
	while (idx_Block_skip < 1024) {
		local_Block_skip = tokens_Block_skip[(index_Block_skip + (idx_Block_skip)) % SIZE_Block_skip];
		tokens_Block[(index_Block + (idx_Block_skip)) % SIZE_Block] = local_Block_skip;
		idx_Block_skip = idx_Block_skip + 1;
	}

	// Update ports indexes
	index_Size += 7;
	read_end_Size();
	index_Block_skip += 1024;
	read_end_Block_skip();
	index_Block += 1024;
	write_end_Block();

	rate_Size += 7;
	rate_Block_skip += 1024;
}
static void merge_32x32_trans_skip_aligned() {

	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;
	i32 idx_Block_skip;
	i16 local_Block_skip;

	sizeOfTU = tokens_Size[(index_Size % SIZE_Size) + (0)];
	RCskip = tokens_Size[(index_Size % SIZE_Size) + (1)];
	isDST = tokens_Size[(index_Size % SIZE_Size) + (2)];
	transformSkipFlag = tokens_Size[(index_Size % SIZE_Size) + (3)];
	slice_qp = tokens_Size[(index_Size % SIZE_Size) + (4)];
	rc_cIdx = tokens_Size[(index_Size % SIZE_Size) + (5)];
	qp_offset = tokens_Size[(index_Size % SIZE_Size) + (6)];
	idx_Block_skip = 0;
	while (idx_Block_skip < 1024) {
		local_Block_skip = tokens_Block_skip[(index_Block_skip % SIZE_Block_skip) + (idx_Block_skip)];
		tokens_Block[(index_Block % SIZE_Block) + (idx_Block_skip)] = local_Block_skip;
		idx_Block_skip = idx_Block_skip + 1;
	}

	// Update ports indexes
	index_Size += 7;
	read_end_Size();
	index_Block_skip += 1024;
	read_end_Block_skip();
	index_Block += 1024;
	write_end_Block();

	rate_Size += 7;
	rate_Block_skip += 1024;
}
static i32 isSchedulable_merge_32x32_default() {
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

static void merge_32x32_default() {

	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;
	i32 idx_Block_32x32;
	i16 local_Block_32x32;

	sizeOfTU = tokens_Size[(index_Size + (0)) % SIZE_Size];
	RCskip = tokens_Size[(index_Size + (1)) % SIZE_Size];
	isDST = tokens_Size[(index_Size + (2)) % SIZE_Size];
	transformSkipFlag = tokens_Size[(index_Size + (3)) % SIZE_Size];
	slice_qp = tokens_Size[(index_Size + (4)) % SIZE_Size];
	rc_cIdx = tokens_Size[(index_Size + (5)) % SIZE_Size];
	qp_offset = tokens_Size[(index_Size + (6)) % SIZE_Size];
	idx_Block_32x32 = 0;
	while (idx_Block_32x32 < 1024) {
		local_Block_32x32 = tokens_Block_32x32[(index_Block_32x32 % SIZE_Block_32x32) + (idx_Block_32x32)];
		tokens_Block[(index_Block + (idx_Block_32x32)) % SIZE_Block] = local_Block_32x32;
		idx_Block_32x32 = idx_Block_32x32 + 1;
	}

	// Update ports indexes
	index_Size += 7;
	read_end_Size();
	index_Block_32x32 += 1024;
	read_end_Block_32x32();
	index_Block += 1024;
	write_end_Block();

	rate_Size += 7;
	rate_Block_32x32 += 1024;
}
static void merge_32x32_default_aligned() {

	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;
	i32 idx_Block_32x32;
	i16 local_Block_32x32;

	sizeOfTU = tokens_Size[(index_Size % SIZE_Size) + (0)];
	RCskip = tokens_Size[(index_Size % SIZE_Size) + (1)];
	isDST = tokens_Size[(index_Size % SIZE_Size) + (2)];
	transformSkipFlag = tokens_Size[(index_Size % SIZE_Size) + (3)];
	slice_qp = tokens_Size[(index_Size % SIZE_Size) + (4)];
	rc_cIdx = tokens_Size[(index_Size % SIZE_Size) + (5)];
	qp_offset = tokens_Size[(index_Size % SIZE_Size) + (6)];
	idx_Block_32x32 = 0;
	while (idx_Block_32x32 < 1024) {
		local_Block_32x32 = tokens_Block_32x32[(index_Block_32x32 % SIZE_Block_32x32) + (idx_Block_32x32)];
		tokens_Block[(index_Block % SIZE_Block) + (idx_Block_32x32)] = local_Block_32x32;
		idx_Block_32x32 = idx_Block_32x32 + 1;
	}

	// Update ports indexes
	index_Size += 7;
	read_end_Size();
	index_Block_32x32 += 1024;
	read_end_Block_32x32();
	index_Block += 1024;
	write_end_Block();

	rate_Size += 7;
	rate_Block_32x32 += 1024;
}
static i32 isSchedulable_merge_32x32_skip() {
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
	result = sizeOfTU == 32 && RCskip != 0;
	return result;
}

static void merge_32x32_skip() {

	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;
	i32 i;

	sizeOfTU = tokens_Size[(index_Size + (0)) % SIZE_Size];
	RCskip = tokens_Size[(index_Size + (1)) % SIZE_Size];
	isDST = tokens_Size[(index_Size + (2)) % SIZE_Size];
	transformSkipFlag = tokens_Size[(index_Size + (3)) % SIZE_Size];
	slice_qp = tokens_Size[(index_Size + (4)) % SIZE_Size];
	rc_cIdx = tokens_Size[(index_Size + (5)) % SIZE_Size];
	qp_offset = tokens_Size[(index_Size + (6)) % SIZE_Size];
	i = 1;
	while (i <= 32 * 32) {
		tokens_Block[(index_Block + (i - 1)) % SIZE_Block] = 0;
		i = i + 1;
	}

	// Update ports indexes
	index_Size += 7;
	read_end_Size();
	index_Block += 1024;
	write_end_Block();

	rate_Size += 7;
}
static void merge_32x32_skip_aligned() {

	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;
	i32 i;

	sizeOfTU = tokens_Size[(index_Size % SIZE_Size) + (0)];
	RCskip = tokens_Size[(index_Size % SIZE_Size) + (1)];
	isDST = tokens_Size[(index_Size % SIZE_Size) + (2)];
	transformSkipFlag = tokens_Size[(index_Size % SIZE_Size) + (3)];
	slice_qp = tokens_Size[(index_Size % SIZE_Size) + (4)];
	rc_cIdx = tokens_Size[(index_Size % SIZE_Size) + (5)];
	qp_offset = tokens_Size[(index_Size % SIZE_Size) + (6)];
	i = 1;
	while (i <= 32 * 32) {
		tokens_Block[(index_Block % SIZE_Block) + (i - 1)] = 0;
		i = i + 1;
	}

	// Update ports indexes
	index_Size += 7;
	read_end_Size();
	index_Block += 1024;
	write_end_Block();

	rate_Size += 7;
}
static i32 isSchedulable_merge_64x64_skip() {
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
	result = sizeOfTU == 64 && RCskip != 0;
	return result;
}

static void merge_64x64_skip() {

	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;
	i32 i;

	sizeOfTU = tokens_Size[(index_Size + (0)) % SIZE_Size];
	RCskip = tokens_Size[(index_Size + (1)) % SIZE_Size];
	isDST = tokens_Size[(index_Size + (2)) % SIZE_Size];
	transformSkipFlag = tokens_Size[(index_Size + (3)) % SIZE_Size];
	slice_qp = tokens_Size[(index_Size + (4)) % SIZE_Size];
	rc_cIdx = tokens_Size[(index_Size + (5)) % SIZE_Size];
	qp_offset = tokens_Size[(index_Size + (6)) % SIZE_Size];
	i = 1;
	while (i <= 64 * 64) {
		tokens_Block[(index_Block + (i - 1)) % SIZE_Block] = 0;
		i = i + 1;
	}

	// Update ports indexes
	index_Size += 7;
	read_end_Size();
	index_Block += 4096;
	write_end_Block();

	rate_Size += 7;
}
static void merge_64x64_skip_aligned() {

	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;
	i32 i;

	sizeOfTU = tokens_Size[(index_Size % SIZE_Size) + (0)];
	RCskip = tokens_Size[(index_Size % SIZE_Size) + (1)];
	isDST = tokens_Size[(index_Size % SIZE_Size) + (2)];
	transformSkipFlag = tokens_Size[(index_Size % SIZE_Size) + (3)];
	slice_qp = tokens_Size[(index_Size % SIZE_Size) + (4)];
	rc_cIdx = tokens_Size[(index_Size % SIZE_Size) + (5)];
	qp_offset = tokens_Size[(index_Size % SIZE_Size) + (6)];
	i = 1;
	while (i <= 64 * 64) {
		tokens_Block[(index_Block % SIZE_Block) + (i - 1)] = 0;
		i = i + 1;
	}

	// Update ports indexes
	index_Size += 7;
	read_end_Size();
	index_Block += 4096;
	write_end_Block();

	rate_Size += 7;
}

////////////////////////////////////////////////////////////////////////////////
// Initializes

void HevcDecoder_xIT_IT_Merger_initialize(schedinfo_t *si) {
	int i = 0;
	write_Block();
finished:
	write_end_Block();
	return;
}

////////////////////////////////////////////////////////////////////////////////
// Action scheduler
void HevcDecoder_xIT_IT_Merger_scheduler(schedinfo_t *si) {
	int i = 0;
	si->ports = 0;

	read_Size();
	read_Block_skip();
	read_Block_4x4_DST();
	read_Block_4x4_IT();
	read_Block_8x8();
	read_Block_16x16();
	read_Block_32x32();
	write_Block();

	while (1) {
		if (numTokens_Size - index_Size >= 7 && numTokens_Block_skip - index_Block_skip >= 16 && isSchedulable_merge_4x4_trans_skip()) {
			int stop = 0;
			if (16 > SIZE_Block - index_Block + HevcDecoder_xIT_IT_Merger_Block->read_inds[0]) {
				stop = 1;
			}
			if (stop != 0) {
				si->num_firings = i;
				si->reason = full;
				goto finished;
			}
			{
				int isAligned = 1;
				isAligned &= ((index_Size % SIZE_Size) < ((index_Size + 7) % SIZE_Size));
				isAligned &= ((index_Block_skip % SIZE_Block_skip) < ((index_Block_skip + 16) % SIZE_Block_skip));
				isAligned &= ((index_Block % SIZE_Block) < ((index_Block + 16) % SIZE_Block));
				if (isAligned) {
					merge_4x4_trans_skip_aligned();
				} else {
					merge_4x4_trans_skip();
				}
			}
			i++;
		} else if (numTokens_Size - index_Size >= 7 && numTokens_Block_4x4_DST - index_Block_4x4_DST >= 16 && isSchedulable_merge_4x4_DST()) {
			int stop = 0;
			if (16 > SIZE_Block - index_Block + HevcDecoder_xIT_IT_Merger_Block->read_inds[0]) {
				stop = 1;
			}
			if (stop != 0) {
				si->num_firings = i;
				si->reason = full;
				goto finished;
			}
			{
				int isAligned = 1;
				isAligned &= ((index_Size % SIZE_Size) < ((index_Size + 7) % SIZE_Size));
				isAligned &= ((index_Block % SIZE_Block) < ((index_Block + 16) % SIZE_Block));
				if (isAligned) {
					merge_4x4_DST_aligned();
				} else {
					merge_4x4_DST();
				}
			}
			i++;
		} else if (numTokens_Size - index_Size >= 7 && numTokens_Block_4x4_IT - index_Block_4x4_IT >= 16 && isSchedulable_merge_4x4_IT()) {
			int stop = 0;
			if (16 > SIZE_Block - index_Block + HevcDecoder_xIT_IT_Merger_Block->read_inds[0]) {
				stop = 1;
			}
			if (stop != 0) {
				si->num_firings = i;
				si->reason = full;
				goto finished;
			}
			{
				int isAligned = 1;
				isAligned &= ((index_Size % SIZE_Size) < ((index_Size + 7) % SIZE_Size));
				isAligned &= ((index_Block % SIZE_Block) < ((index_Block + 16) % SIZE_Block));
				if (isAligned) {
					merge_4x4_IT_aligned();
				} else {
					merge_4x4_IT();
				}
			}
			i++;
		} else if (numTokens_Size - index_Size >= 7 && isSchedulable_merge_4x4_skip()) {
			int stop = 0;
			if (16 > SIZE_Block - index_Block + HevcDecoder_xIT_IT_Merger_Block->read_inds[0]) {
				stop = 1;
			}
			if (stop != 0) {
				si->num_firings = i;
				si->reason = full;
				goto finished;
			}
			{
				int isAligned = 1;
				isAligned &= ((index_Size % SIZE_Size) < ((index_Size + 7) % SIZE_Size));
				isAligned &= ((index_Block % SIZE_Block) < ((index_Block + 16) % SIZE_Block));
				if (isAligned) {
					merge_4x4_skip_aligned();
				} else {
					merge_4x4_skip();
				}
			}
			i++;
		} else if (numTokens_Size - index_Size >= 7 && numTokens_Block_skip - index_Block_skip >= 64 && isSchedulable_merge_8x8_trans_skip()) {
			int stop = 0;
			if (64 > SIZE_Block - index_Block + HevcDecoder_xIT_IT_Merger_Block->read_inds[0]) {
				stop = 1;
			}
			if (stop != 0) {
				si->num_firings = i;
				si->reason = full;
				goto finished;
			}
			{
				int isAligned = 1;
				isAligned &= ((index_Size % SIZE_Size) < ((index_Size + 7) % SIZE_Size));
				isAligned &= ((index_Block_skip % SIZE_Block_skip) < ((index_Block_skip + 64) % SIZE_Block_skip));
				isAligned &= ((index_Block % SIZE_Block) < ((index_Block + 64) % SIZE_Block));
				if (isAligned) {
					merge_8x8_trans_skip_aligned();
				} else {
					merge_8x8_trans_skip();
				}
			}
			i++;
		} else if (numTokens_Size - index_Size >= 7 && numTokens_Block_8x8 - index_Block_8x8 >= 64 && isSchedulable_merge_8x8_default()) {
			int stop = 0;
			if (64 > SIZE_Block - index_Block + HevcDecoder_xIT_IT_Merger_Block->read_inds[0]) {
				stop = 1;
			}
			if (stop != 0) {
				si->num_firings = i;
				si->reason = full;
				goto finished;
			}
			{
				int isAligned = 1;
				isAligned &= ((index_Size % SIZE_Size) < ((index_Size + 7) % SIZE_Size));
				isAligned &= ((index_Block % SIZE_Block) < ((index_Block + 64) % SIZE_Block));
				if (isAligned) {
					merge_8x8_default_aligned();
				} else {
					merge_8x8_default();
				}
			}
			i++;
		} else if (numTokens_Size - index_Size >= 7 && isSchedulable_merge_8x8_skip()) {
			int stop = 0;
			if (64 > SIZE_Block - index_Block + HevcDecoder_xIT_IT_Merger_Block->read_inds[0]) {
				stop = 1;
			}
			if (stop != 0) {
				si->num_firings = i;
				si->reason = full;
				goto finished;
			}
			{
				int isAligned = 1;
				isAligned &= ((index_Size % SIZE_Size) < ((index_Size + 7) % SIZE_Size));
				isAligned &= ((index_Block % SIZE_Block) < ((index_Block + 64) % SIZE_Block));
				if (isAligned) {
					merge_8x8_skip_aligned();
				} else {
					merge_8x8_skip();
				}
			}
			i++;
		} else if (numTokens_Size - index_Size >= 7 && numTokens_Block_skip - index_Block_skip >= 256 && isSchedulable_merge_16x16_trans_skip()) {
			int stop = 0;
			if (256 > SIZE_Block - index_Block + HevcDecoder_xIT_IT_Merger_Block->read_inds[0]) {
				stop = 1;
			}
			if (stop != 0) {
				si->num_firings = i;
				si->reason = full;
				goto finished;
			}
			{
				int isAligned = 1;
				isAligned &= ((index_Size % SIZE_Size) < ((index_Size + 7) % SIZE_Size));
				isAligned &= ((index_Block_skip % SIZE_Block_skip) < ((index_Block_skip + 256) % SIZE_Block_skip));
				isAligned &= ((index_Block % SIZE_Block) < ((index_Block + 256) % SIZE_Block));
				if (isAligned) {
					merge_16x16_trans_skip_aligned();
				} else {
					merge_16x16_trans_skip();
				}
			}
			i++;
		} else if (numTokens_Size - index_Size >= 7 && numTokens_Block_16x16 - index_Block_16x16 >= 256 && isSchedulable_merge_16x16_default()) {
			int stop = 0;
			if (256 > SIZE_Block - index_Block + HevcDecoder_xIT_IT_Merger_Block->read_inds[0]) {
				stop = 1;
			}
			if (stop != 0) {
				si->num_firings = i;
				si->reason = full;
				goto finished;
			}
			{
				int isAligned = 1;
				isAligned &= ((index_Size % SIZE_Size) < ((index_Size + 7) % SIZE_Size));
				isAligned &= ((index_Block % SIZE_Block) < ((index_Block + 256) % SIZE_Block));
				if (isAligned) {
					merge_16x16_default_aligned();
				} else {
					merge_16x16_default();
				}
			}
			i++;
		} else if (numTokens_Size - index_Size >= 7 && isSchedulable_merge_16x16_skip()) {
			int stop = 0;
			if (256 > SIZE_Block - index_Block + HevcDecoder_xIT_IT_Merger_Block->read_inds[0]) {
				stop = 1;
			}
			if (stop != 0) {
				si->num_firings = i;
				si->reason = full;
				goto finished;
			}
			{
				int isAligned = 1;
				isAligned &= ((index_Size % SIZE_Size) < ((index_Size + 7) % SIZE_Size));
				isAligned &= ((index_Block % SIZE_Block) < ((index_Block + 256) % SIZE_Block));
				if (isAligned) {
					merge_16x16_skip_aligned();
				} else {
					merge_16x16_skip();
				}
			}
			i++;
		} else if (numTokens_Size - index_Size >= 7 && numTokens_Block_skip - index_Block_skip >= 1024 && isSchedulable_merge_32x32_trans_skip()) {
			int stop = 0;
			if (1024 > SIZE_Block - index_Block + HevcDecoder_xIT_IT_Merger_Block->read_inds[0]) {
				stop = 1;
			}
			if (stop != 0) {
				si->num_firings = i;
				si->reason = full;
				goto finished;
			}
			{
				int isAligned = 1;
				isAligned &= ((index_Size % SIZE_Size) < ((index_Size + 7) % SIZE_Size));
				isAligned &= ((index_Block_skip % SIZE_Block_skip) < ((index_Block_skip + 1024) % SIZE_Block_skip));
				isAligned &= ((index_Block % SIZE_Block) < ((index_Block + 1024) % SIZE_Block));
				if (isAligned) {
					merge_32x32_trans_skip_aligned();
				} else {
					merge_32x32_trans_skip();
				}
			}
			i++;
		} else if (numTokens_Size - index_Size >= 7 && numTokens_Block_32x32 - index_Block_32x32 >= 1024 && isSchedulable_merge_32x32_default()) {
			int stop = 0;
			if (1024 > SIZE_Block - index_Block + HevcDecoder_xIT_IT_Merger_Block->read_inds[0]) {
				stop = 1;
			}
			if (stop != 0) {
				si->num_firings = i;
				si->reason = full;
				goto finished;
			}
			{
				int isAligned = 1;
				isAligned &= ((index_Size % SIZE_Size) < ((index_Size + 7) % SIZE_Size));
				isAligned &= ((index_Block % SIZE_Block) < ((index_Block + 1024) % SIZE_Block));
				if (isAligned) {
					merge_32x32_default_aligned();
				} else {
					merge_32x32_default();
				}
			}
			i++;
		} else if (numTokens_Size - index_Size >= 7 && isSchedulable_merge_32x32_skip()) {
			int stop = 0;
			if (1024 > SIZE_Block - index_Block + HevcDecoder_xIT_IT_Merger_Block->read_inds[0]) {
				stop = 1;
			}
			if (stop != 0) {
				si->num_firings = i;
				si->reason = full;
				goto finished;
			}
			{
				int isAligned = 1;
				isAligned &= ((index_Size % SIZE_Size) < ((index_Size + 7) % SIZE_Size));
				isAligned &= ((index_Block % SIZE_Block) < ((index_Block + 1024) % SIZE_Block));
				if (isAligned) {
					merge_32x32_skip_aligned();
				} else {
					merge_32x32_skip();
				}
			}
			i++;
		} else if (numTokens_Size - index_Size >= 7 && isSchedulable_merge_64x64_skip()) {
			int stop = 0;
			if (4096 > SIZE_Block - index_Block + HevcDecoder_xIT_IT_Merger_Block->read_inds[0]) {
				stop = 1;
			}
			if (stop != 0) {
				si->num_firings = i;
				si->reason = full;
				goto finished;
			}
			{
				int isAligned = 1;
				isAligned &= ((index_Size % SIZE_Size) < ((index_Size + 7) % SIZE_Size));
				isAligned &= ((index_Block % SIZE_Block) < ((index_Block + 4096) % SIZE_Block));
				if (isAligned) {
					merge_64x64_skip_aligned();
				} else {
					merge_64x64_skip();
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

	read_end_Size();
	read_end_Block_skip();
	read_end_Block_4x4_DST();
	read_end_Block_4x4_IT();
	read_end_Block_8x8();
	read_end_Block_16x16();
	read_end_Block_32x32();
	write_end_Block();
}
