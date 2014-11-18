// Source file is "L/RVC/src/org/sc29/wg11/mpegh/part2/main/IT/Block_Merge.cal"

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
extern actor_t HevcDecoder_xIT_Block_Merger;

////////////////////////////////////////////////////////////////////////////////
// Input FIFOs
extern fifo_i8_t *HevcDecoder_xIT_Block_Merger_Size;
extern fifo_i16_t *HevcDecoder_xIT_Block_Merger_Block_in;

////////////////////////////////////////////////////////////////////////////////
// Input Fifo control variables
static unsigned int index_Size;
static unsigned int numTokens_Size;
#define SIZE_Size SIZE
#define tokens_Size HevcDecoder_xIT_Block_Merger_Size->contents

extern connection_t connection_HevcDecoder_xIT_Block_Merger_Size;
#define rate_Size connection_HevcDecoder_xIT_Block_Merger_Size.rate

static unsigned int index_Block_in;
static unsigned int numTokens_Block_in;
#define SIZE_Block_in SIZE
#define tokens_Block_in HevcDecoder_xIT_Block_Merger_Block_in->contents

extern connection_t connection_HevcDecoder_xIT_Block_Merger_Block_in;
#define rate_Block_in connection_HevcDecoder_xIT_Block_Merger_Block_in.rate

////////////////////////////////////////////////////////////////////////////////
// Predecessors
extern actor_t HevcDecoder_Algo_Parser;
extern actor_t HevcDecoder_xIT_IT_Merger;

////////////////////////////////////////////////////////////////////////////////
// Output FIFOs
extern fifo_i16_t *HevcDecoder_xIT_Block_Merger_Block;

////////////////////////////////////////////////////////////////////////////////
// Output Fifo control variables
static unsigned int index_Block;
static unsigned int numFree_Block;
#define NUM_READERS_Block 1
#define SIZE_Block SIZE
#define tokens_Block HevcDecoder_xIT_Block_Merger_Block->contents

////////////////////////////////////////////////////////////////////////////////
// Successors
extern actor_t HevcDecoder_SelectCU;


////////////////////////////////////////////////////////////////////////////////
// State variables of the actor
static i16 CoeffY[1024];
static i16 CoeffU[256];
static i16 CoeffV[256];
static u8 block4x4Idx = 0;
static u8 nbBlock4x4;
static const u16 scan16x16_UV_offset[4] = {0, 8, 128, 136};
static const u16 scan8x8_UV_offset[4] = {0, 4, 64, 68};
static const u16 scan4x4_UV_offset[4] = {0, 2, 32, 34};
static const u16 scan16x16_Y_offset[4] = {0, 16, 512, 528};
static const u16 scan8x8_Y_offset[4] = {0, 8, 256, 264};
static const u16 scan4x4_Y_offset[4] = {0, 4, 128, 132};

////////////////////////////////////////////////////////////////////////////////
// Initial FSM state of the actor
enum states {
	my_state_merge_U,
	my_state_merge_V,
	my_state_merge_Y,
	my_state_output_U,
	my_state_output_V,
	my_state_output_Y,
	my_state_zero_UV
};

static char *stateNames[] = {
	"merge_U",
	"merge_V",
	"merge_Y",
	"output_U",
	"output_V",
	"output_Y",
	"zero_UV"
};

static enum states _FSM_state;



////////////////////////////////////////////////////////////////////////////////
// Token functions
static void read_Size() {
	index_Size = HevcDecoder_xIT_Block_Merger_Size->read_inds[2];
	numTokens_Size = index_Size + fifo_i8_get_num_tokens(HevcDecoder_xIT_Block_Merger_Size, 2);
}

static void read_end_Size() {
	HevcDecoder_xIT_Block_Merger_Size->read_inds[2] = index_Size;
}
static void read_Block_in() {
	index_Block_in = HevcDecoder_xIT_Block_Merger_Block_in->read_inds[0];
	numTokens_Block_in = index_Block_in + fifo_i16_get_num_tokens(HevcDecoder_xIT_Block_Merger_Block_in, 0);
}

static void read_end_Block_in() {
	HevcDecoder_xIT_Block_Merger_Block_in->read_inds[0] = index_Block_in;
}

static void write_Block() {
	index_Block = HevcDecoder_xIT_Block_Merger_Block->write_ind;
	numFree_Block = index_Block + fifo_i16_get_room(HevcDecoder_xIT_Block_Merger_Block, NUM_READERS_Block, SIZE_Block);
}

static void write_end_Block() {
	HevcDecoder_xIT_Block_Merger_Block->write_ind = index_Block;
}

////////////////////////////////////////////////////////////////////////////////
// Functions/procedures


////////////////////////////////////////////////////////////////////////////////
// Actions
static i32 isSchedulable_merge_Y_loop_block4x4() {
	i32 result;
	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;
	u8 local_block4x4Idx;

	sizeOfTU = tokens_Size[(index_Size + (0)) % SIZE_Size];
	RCskip = tokens_Size[(index_Size + (1)) % SIZE_Size];
	isDST = tokens_Size[(index_Size + (2)) % SIZE_Size];
	transformSkipFlag = tokens_Size[(index_Size + (3)) % SIZE_Size];
	slice_qp = tokens_Size[(index_Size + (4)) % SIZE_Size];
	rc_cIdx = tokens_Size[(index_Size + (5)) % SIZE_Size];
	qp_offset = tokens_Size[(index_Size + (6)) % SIZE_Size];
	local_block4x4Idx = block4x4Idx;
	result = sizeOfTU == 4 && local_block4x4Idx != 3;
	return result;
}

static void merge_Y_loop_block4x4() {

	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;
	i16 offset;
	u8 local_block4x4Idx;
	i32 i;
	i32 j;
	i16 tmp_Block_in;

	sizeOfTU = tokens_Size[(index_Size + (0)) % SIZE_Size];
	RCskip = tokens_Size[(index_Size + (1)) % SIZE_Size];
	isDST = tokens_Size[(index_Size + (2)) % SIZE_Size];
	transformSkipFlag = tokens_Size[(index_Size + (3)) % SIZE_Size];
	slice_qp = tokens_Size[(index_Size + (4)) % SIZE_Size];
	rc_cIdx = tokens_Size[(index_Size + (5)) % SIZE_Size];
	qp_offset = tokens_Size[(index_Size + (6)) % SIZE_Size];
	offset = 0;
	local_block4x4Idx = block4x4Idx;
	offset = scan4x4_Y_offset[local_block4x4Idx];
	i = 0;
	while (i <= sizeOfTU - 1) {
		j = 0;
		while (j <= sizeOfTU - 1) {
			tmp_Block_in = tokens_Block_in[(index_Block_in + (i * sizeOfTU + j)) % SIZE_Block_in];
			CoeffY[offset + j] = tmp_Block_in;
			j = j + 1;
		}
		offset = 32 + offset;
		i = i + 1;
	}
	local_block4x4Idx = block4x4Idx;
	block4x4Idx = local_block4x4Idx + 1;

	// Update ports indexes
	index_Size += 7;
	read_end_Size();
	index_Block_in += 16;
	read_end_Block_in();

	rate_Size += 7;
	rate_Block_in += 16;
}
static void merge_Y_loop_block4x4_aligned() {

	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;
	i16 offset;
	u8 local_block4x4Idx;
	i32 i;
	i32 j;
	i16 tmp_Block_in;

	sizeOfTU = tokens_Size[(index_Size % SIZE_Size) + (0)];
	RCskip = tokens_Size[(index_Size % SIZE_Size) + (1)];
	isDST = tokens_Size[(index_Size % SIZE_Size) + (2)];
	transformSkipFlag = tokens_Size[(index_Size % SIZE_Size) + (3)];
	slice_qp = tokens_Size[(index_Size % SIZE_Size) + (4)];
	rc_cIdx = tokens_Size[(index_Size % SIZE_Size) + (5)];
	qp_offset = tokens_Size[(index_Size % SIZE_Size) + (6)];
	offset = 0;
	local_block4x4Idx = block4x4Idx;
	offset = scan4x4_Y_offset[local_block4x4Idx];
	i = 0;
	while (i <= sizeOfTU - 1) {
		j = 0;
		while (j <= sizeOfTU - 1) {
			tmp_Block_in = tokens_Block_in[(index_Block_in % SIZE_Block_in) + (i * sizeOfTU + j)];
			CoeffY[offset + j] = tmp_Block_in;
			j = j + 1;
		}
		offset = 32 + offset;
		i = i + 1;
	}
	local_block4x4Idx = block4x4Idx;
	block4x4Idx = local_block4x4Idx + 1;

	// Update ports indexes
	index_Size += 7;
	read_end_Size();
	index_Block_in += 16;
	read_end_Block_in();

	rate_Size += 7;
	rate_Block_in += 16;
}
static i32 isSchedulable_merge_Y_block4x4() {
	i32 result;
	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;
	u8 local_block4x4Idx;

	sizeOfTU = tokens_Size[(index_Size + (0)) % SIZE_Size];
	RCskip = tokens_Size[(index_Size + (1)) % SIZE_Size];
	isDST = tokens_Size[(index_Size + (2)) % SIZE_Size];
	transformSkipFlag = tokens_Size[(index_Size + (3)) % SIZE_Size];
	slice_qp = tokens_Size[(index_Size + (4)) % SIZE_Size];
	rc_cIdx = tokens_Size[(index_Size + (5)) % SIZE_Size];
	qp_offset = tokens_Size[(index_Size + (6)) % SIZE_Size];
	local_block4x4Idx = block4x4Idx;
	result = sizeOfTU == 4 && local_block4x4Idx == 3;
	return result;
}

static void merge_Y_block4x4() {

	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;
	i16 offset;
	u8 local_block4x4Idx;
	i32 i;
	i32 j;
	i16 tmp_Block_in;

	sizeOfTU = tokens_Size[(index_Size + (0)) % SIZE_Size];
	RCskip = tokens_Size[(index_Size + (1)) % SIZE_Size];
	isDST = tokens_Size[(index_Size + (2)) % SIZE_Size];
	transformSkipFlag = tokens_Size[(index_Size + (3)) % SIZE_Size];
	slice_qp = tokens_Size[(index_Size + (4)) % SIZE_Size];
	rc_cIdx = tokens_Size[(index_Size + (5)) % SIZE_Size];
	qp_offset = tokens_Size[(index_Size + (6)) % SIZE_Size];
	offset = 0;
	local_block4x4Idx = block4x4Idx;
	offset = scan4x4_Y_offset[local_block4x4Idx];
	i = 0;
	while (i <= sizeOfTU - 1) {
		j = 0;
		while (j <= sizeOfTU - 1) {
			tmp_Block_in = tokens_Block_in[(index_Block_in + (i * sizeOfTU + j)) % SIZE_Block_in];
			CoeffY[offset + j] = tmp_Block_in;
			j = j + 1;
		}
		offset = 32 + offset;
		i = i + 1;
	}
	block4x4Idx = 0;
	nbBlock4x4 = 4;

	// Update ports indexes
	index_Size += 7;
	read_end_Size();
	index_Block_in += 16;
	read_end_Block_in();

	rate_Size += 7;
	rate_Block_in += 16;
}
static void merge_Y_block4x4_aligned() {

	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;
	i16 offset;
	u8 local_block4x4Idx;
	i32 i;
	i32 j;
	i16 tmp_Block_in;

	sizeOfTU = tokens_Size[(index_Size % SIZE_Size) + (0)];
	RCskip = tokens_Size[(index_Size % SIZE_Size) + (1)];
	isDST = tokens_Size[(index_Size % SIZE_Size) + (2)];
	transformSkipFlag = tokens_Size[(index_Size % SIZE_Size) + (3)];
	slice_qp = tokens_Size[(index_Size % SIZE_Size) + (4)];
	rc_cIdx = tokens_Size[(index_Size % SIZE_Size) + (5)];
	qp_offset = tokens_Size[(index_Size % SIZE_Size) + (6)];
	offset = 0;
	local_block4x4Idx = block4x4Idx;
	offset = scan4x4_Y_offset[local_block4x4Idx];
	i = 0;
	while (i <= sizeOfTU - 1) {
		j = 0;
		while (j <= sizeOfTU - 1) {
			tmp_Block_in = tokens_Block_in[(index_Block_in % SIZE_Block_in) + (i * sizeOfTU + j)];
			CoeffY[offset + j] = tmp_Block_in;
			j = j + 1;
		}
		offset = 32 + offset;
		i = i + 1;
	}
	block4x4Idx = 0;
	nbBlock4x4 = 4;

	// Update ports indexes
	index_Size += 7;
	read_end_Size();
	index_Block_in += 16;
	read_end_Block_in();

	rate_Size += 7;
	rate_Block_in += 16;
}
static i32 isSchedulable_merge_Y_block8x8() {
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
	result = sizeOfTU == 8;
	return result;
}

static void merge_Y_block8x8() {

	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;
	i16 offset;
	i32 i;
	i32 j;
	i16 tmp_Block_in;

	sizeOfTU = tokens_Size[(index_Size + (0)) % SIZE_Size];
	RCskip = tokens_Size[(index_Size + (1)) % SIZE_Size];
	isDST = tokens_Size[(index_Size + (2)) % SIZE_Size];
	transformSkipFlag = tokens_Size[(index_Size + (3)) % SIZE_Size];
	slice_qp = tokens_Size[(index_Size + (4)) % SIZE_Size];
	rc_cIdx = tokens_Size[(index_Size + (5)) % SIZE_Size];
	qp_offset = tokens_Size[(index_Size + (6)) % SIZE_Size];
	offset = 0;
	i = 0;
	while (i <= sizeOfTU - 1) {
		j = 0;
		while (j <= sizeOfTU - 1) {
			tmp_Block_in = tokens_Block_in[(index_Block_in + (i * sizeOfTU + j)) % SIZE_Block_in];
			CoeffY[offset + j] = tmp_Block_in;
			j = j + 1;
		}
		offset = 32 + offset;
		i = i + 1;
	}
	nbBlock4x4 = 4;

	// Update ports indexes
	index_Size += 7;
	read_end_Size();
	index_Block_in += 64;
	read_end_Block_in();

	rate_Size += 7;
	rate_Block_in += 64;
}
static void merge_Y_block8x8_aligned() {

	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;
	i16 offset;
	i32 i;
	i32 j;
	i16 tmp_Block_in;

	sizeOfTU = tokens_Size[(index_Size % SIZE_Size) + (0)];
	RCskip = tokens_Size[(index_Size % SIZE_Size) + (1)];
	isDST = tokens_Size[(index_Size % SIZE_Size) + (2)];
	transformSkipFlag = tokens_Size[(index_Size % SIZE_Size) + (3)];
	slice_qp = tokens_Size[(index_Size % SIZE_Size) + (4)];
	rc_cIdx = tokens_Size[(index_Size % SIZE_Size) + (5)];
	qp_offset = tokens_Size[(index_Size % SIZE_Size) + (6)];
	offset = 0;
	i = 0;
	while (i <= sizeOfTU - 1) {
		j = 0;
		while (j <= sizeOfTU - 1) {
			tmp_Block_in = tokens_Block_in[(index_Block_in % SIZE_Block_in) + (i * sizeOfTU + j)];
			CoeffY[offset + j] = tmp_Block_in;
			j = j + 1;
		}
		offset = 32 + offset;
		i = i + 1;
	}
	nbBlock4x4 = 4;

	// Update ports indexes
	index_Size += 7;
	read_end_Size();
	index_Block_in += 64;
	read_end_Block_in();

	rate_Size += 7;
	rate_Block_in += 64;
}
static i32 isSchedulable_merge_Y_block16x16() {
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
	result = sizeOfTU == 16;
	return result;
}

static void merge_Y_block16x16() {

	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;
	i16 offset;
	i32 i;
	i32 j;
	i16 tmp_Block_in;

	sizeOfTU = tokens_Size[(index_Size + (0)) % SIZE_Size];
	RCskip = tokens_Size[(index_Size + (1)) % SIZE_Size];
	isDST = tokens_Size[(index_Size + (2)) % SIZE_Size];
	transformSkipFlag = tokens_Size[(index_Size + (3)) % SIZE_Size];
	slice_qp = tokens_Size[(index_Size + (4)) % SIZE_Size];
	rc_cIdx = tokens_Size[(index_Size + (5)) % SIZE_Size];
	qp_offset = tokens_Size[(index_Size + (6)) % SIZE_Size];
	offset = 0;
	i = 0;
	while (i <= sizeOfTU - 1) {
		j = 0;
		while (j <= sizeOfTU - 1) {
			tmp_Block_in = tokens_Block_in[(index_Block_in + (i * sizeOfTU + j)) % SIZE_Block_in];
			CoeffY[offset + j] = tmp_Block_in;
			j = j + 1;
		}
		offset = 32 + offset;
		i = i + 1;
	}
	nbBlock4x4 = 16;

	// Update ports indexes
	index_Size += 7;
	read_end_Size();
	index_Block_in += 256;
	read_end_Block_in();

	rate_Size += 7;
	rate_Block_in += 256;
}
static void merge_Y_block16x16_aligned() {

	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;
	i16 offset;
	i32 i;
	i32 j;
	i16 tmp_Block_in;

	sizeOfTU = tokens_Size[(index_Size % SIZE_Size) + (0)];
	RCskip = tokens_Size[(index_Size % SIZE_Size) + (1)];
	isDST = tokens_Size[(index_Size % SIZE_Size) + (2)];
	transformSkipFlag = tokens_Size[(index_Size % SIZE_Size) + (3)];
	slice_qp = tokens_Size[(index_Size % SIZE_Size) + (4)];
	rc_cIdx = tokens_Size[(index_Size % SIZE_Size) + (5)];
	qp_offset = tokens_Size[(index_Size % SIZE_Size) + (6)];
	offset = 0;
	i = 0;
	while (i <= sizeOfTU - 1) {
		j = 0;
		while (j <= sizeOfTU - 1) {
			tmp_Block_in = tokens_Block_in[(index_Block_in % SIZE_Block_in) + (i * sizeOfTU + j)];
			CoeffY[offset + j] = tmp_Block_in;
			j = j + 1;
		}
		offset = 32 + offset;
		i = i + 1;
	}
	nbBlock4x4 = 16;

	// Update ports indexes
	index_Size += 7;
	read_end_Size();
	index_Block_in += 256;
	read_end_Block_in();

	rate_Size += 7;
	rate_Block_in += 256;
}
static i32 isSchedulable_merge_Y_block32x32() {
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
	result = sizeOfTU == 32;
	return result;
}

static void merge_Y_block32x32() {

	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;
	i32 i;
	i16 tmp_Block_in;

	sizeOfTU = tokens_Size[(index_Size + (0)) % SIZE_Size];
	RCskip = tokens_Size[(index_Size + (1)) % SIZE_Size];
	isDST = tokens_Size[(index_Size + (2)) % SIZE_Size];
	transformSkipFlag = tokens_Size[(index_Size + (3)) % SIZE_Size];
	slice_qp = tokens_Size[(index_Size + (4)) % SIZE_Size];
	rc_cIdx = tokens_Size[(index_Size + (5)) % SIZE_Size];
	qp_offset = tokens_Size[(index_Size + (6)) % SIZE_Size];
	i = 0;
	while (i <= 1023) {
		tmp_Block_in = tokens_Block_in[(index_Block_in + (i)) % SIZE_Block_in];
		CoeffY[i] = tmp_Block_in;
		i = i + 1;
	}
	nbBlock4x4 = 64;

	// Update ports indexes
	index_Size += 7;
	read_end_Size();
	index_Block_in += 1024;
	read_end_Block_in();

	rate_Size += 7;
	rate_Block_in += 1024;
}
static void merge_Y_block32x32_aligned() {

	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;
	i32 i;
	i16 tmp_Block_in;

	sizeOfTU = tokens_Size[(index_Size % SIZE_Size) + (0)];
	RCskip = tokens_Size[(index_Size % SIZE_Size) + (1)];
	isDST = tokens_Size[(index_Size % SIZE_Size) + (2)];
	transformSkipFlag = tokens_Size[(index_Size % SIZE_Size) + (3)];
	slice_qp = tokens_Size[(index_Size % SIZE_Size) + (4)];
	rc_cIdx = tokens_Size[(index_Size % SIZE_Size) + (5)];
	qp_offset = tokens_Size[(index_Size % SIZE_Size) + (6)];
	i = 0;
	while (i <= 1023) {
		tmp_Block_in = tokens_Block_in[(index_Block_in % SIZE_Block_in) + (i)];
		CoeffY[i] = tmp_Block_in;
		i = i + 1;
	}
	nbBlock4x4 = 64;

	// Update ports indexes
	index_Size += 7;
	read_end_Size();
	index_Block_in += 1024;
	read_end_Block_in();

	rate_Size += 7;
	rate_Block_in += 1024;
}
static i32 isSchedulable_merge_Y_64x64() {
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
	result = sizeOfTU == 64;
	return result;
}

static void merge_Y_64x64() {

	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;
	i32 idx_Block_in;
	i16 local_Block_in;

	sizeOfTU = tokens_Size[(index_Size + (0)) % SIZE_Size];
	RCskip = tokens_Size[(index_Size + (1)) % SIZE_Size];
	isDST = tokens_Size[(index_Size + (2)) % SIZE_Size];
	transformSkipFlag = tokens_Size[(index_Size + (3)) % SIZE_Size];
	slice_qp = tokens_Size[(index_Size + (4)) % SIZE_Size];
	rc_cIdx = tokens_Size[(index_Size + (5)) % SIZE_Size];
	qp_offset = tokens_Size[(index_Size + (6)) % SIZE_Size];
	idx_Block_in = 0;
	while (idx_Block_in < 4096) {
		local_Block_in = tokens_Block_in[(index_Block_in + (idx_Block_in)) % SIZE_Block_in];
		tokens_Block[(index_Block + (idx_Block_in)) % SIZE_Block] = local_Block_in;
		idx_Block_in = idx_Block_in + 1;
	}

	// Update ports indexes
	index_Size += 7;
	read_end_Size();
	index_Block_in += 4096;
	read_end_Block_in();
	index_Block += 4096;
	write_end_Block();

	rate_Size += 7;
	rate_Block_in += 4096;
}
static void merge_Y_64x64_aligned() {

	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;
	i32 idx_Block_in;
	i16 local_Block_in;

	sizeOfTU = tokens_Size[(index_Size % SIZE_Size) + (0)];
	RCskip = tokens_Size[(index_Size % SIZE_Size) + (1)];
	isDST = tokens_Size[(index_Size % SIZE_Size) + (2)];
	transformSkipFlag = tokens_Size[(index_Size % SIZE_Size) + (3)];
	slice_qp = tokens_Size[(index_Size % SIZE_Size) + (4)];
	rc_cIdx = tokens_Size[(index_Size % SIZE_Size) + (5)];
	qp_offset = tokens_Size[(index_Size % SIZE_Size) + (6)];
	idx_Block_in = 0;
	while (idx_Block_in < 4096) {
		local_Block_in = tokens_Block_in[(index_Block_in % SIZE_Block_in) + (idx_Block_in)];
		tokens_Block[(index_Block % SIZE_Block) + (idx_Block_in)] = local_Block_in;
		idx_Block_in = idx_Block_in + 1;
	}

	// Update ports indexes
	index_Size += 7;
	read_end_Size();
	index_Block_in += 4096;
	read_end_Block_in();
	index_Block += 4096;
	write_end_Block();

	rate_Size += 7;
	rate_Block_in += 4096;
}
static i32 isSchedulable_merge_UV_64x64() {
	i32 result;

	result = 1;
	return result;
}

static void merge_UV_64x64() {

	i32 idx_Block_in;
	i16 local_Block_in;

	idx_Block_in = 0;
	while (idx_Block_in < 2048) {
		local_Block_in = tokens_Block_in[(index_Block_in + (idx_Block_in)) % SIZE_Block_in];
		tokens_Block[(index_Block + (idx_Block_in)) % SIZE_Block] = local_Block_in;
		idx_Block_in = idx_Block_in + 1;
	}

	// Update ports indexes
	index_Size += 14;
	read_end_Size();
	index_Block_in += 2048;
	read_end_Block_in();
	index_Block += 2048;
	write_end_Block();

	rate_Size += 14;
	rate_Block_in += 2048;
}
static void merge_UV_64x64_aligned() {

	i32 idx_Block_in;
	i16 local_Block_in;

	idx_Block_in = 0;
	while (idx_Block_in < 2048) {
		local_Block_in = tokens_Block_in[(index_Block_in % SIZE_Block_in) + (idx_Block_in)];
		tokens_Block[(index_Block % SIZE_Block) + (idx_Block_in)] = local_Block_in;
		idx_Block_in = idx_Block_in + 1;
	}

	// Update ports indexes
	index_Size += 14;
	read_end_Size();
	index_Block_in += 2048;
	read_end_Block_in();
	index_Block += 2048;
	write_end_Block();

	rate_Size += 14;
	rate_Block_in += 2048;
}
static i32 isSchedulable_merge_U_block4x4() {
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
	result = sizeOfTU == 4;
	return result;
}

static void merge_U_block4x4() {

	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;
	i16 offset;
	i32 i;
	i32 j;
	i16 tmp_Block_in;

	sizeOfTU = tokens_Size[(index_Size + (0)) % SIZE_Size];
	RCskip = tokens_Size[(index_Size + (1)) % SIZE_Size];
	isDST = tokens_Size[(index_Size + (2)) % SIZE_Size];
	transformSkipFlag = tokens_Size[(index_Size + (3)) % SIZE_Size];
	slice_qp = tokens_Size[(index_Size + (4)) % SIZE_Size];
	rc_cIdx = tokens_Size[(index_Size + (5)) % SIZE_Size];
	qp_offset = tokens_Size[(index_Size + (6)) % SIZE_Size];
	offset = 0;
	i = 0;
	while (i <= sizeOfTU - 1) {
		j = 0;
		while (j <= sizeOfTU - 1) {
			tmp_Block_in = tokens_Block_in[(index_Block_in + (i * sizeOfTU + j)) % SIZE_Block_in];
			CoeffU[offset + j] = tmp_Block_in;
			j = j + 1;
		}
		offset = 16 + offset;
		i = i + 1;
	}

	// Update ports indexes
	index_Size += 7;
	read_end_Size();
	index_Block_in += 16;
	read_end_Block_in();

	rate_Size += 7;
	rate_Block_in += 16;
}
static void merge_U_block4x4_aligned() {

	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;
	i16 offset;
	i32 i;
	i32 j;
	i16 tmp_Block_in;

	sizeOfTU = tokens_Size[(index_Size % SIZE_Size) + (0)];
	RCskip = tokens_Size[(index_Size % SIZE_Size) + (1)];
	isDST = tokens_Size[(index_Size % SIZE_Size) + (2)];
	transformSkipFlag = tokens_Size[(index_Size % SIZE_Size) + (3)];
	slice_qp = tokens_Size[(index_Size % SIZE_Size) + (4)];
	rc_cIdx = tokens_Size[(index_Size % SIZE_Size) + (5)];
	qp_offset = tokens_Size[(index_Size % SIZE_Size) + (6)];
	offset = 0;
	i = 0;
	while (i <= sizeOfTU - 1) {
		j = 0;
		while (j <= sizeOfTU - 1) {
			tmp_Block_in = tokens_Block_in[(index_Block_in % SIZE_Block_in) + (i * sizeOfTU + j)];
			CoeffU[offset + j] = tmp_Block_in;
			j = j + 1;
		}
		offset = 16 + offset;
		i = i + 1;
	}

	// Update ports indexes
	index_Size += 7;
	read_end_Size();
	index_Block_in += 16;
	read_end_Block_in();

	rate_Size += 7;
	rate_Block_in += 16;
}
static i32 isSchedulable_merge_V_block4x4() {
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
	result = sizeOfTU == 4;
	return result;
}

static void merge_V_block4x4() {

	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;
	i16 offset;
	i32 i;
	i32 j;
	i16 tmp_Block_in;

	sizeOfTU = tokens_Size[(index_Size + (0)) % SIZE_Size];
	RCskip = tokens_Size[(index_Size + (1)) % SIZE_Size];
	isDST = tokens_Size[(index_Size + (2)) % SIZE_Size];
	transformSkipFlag = tokens_Size[(index_Size + (3)) % SIZE_Size];
	slice_qp = tokens_Size[(index_Size + (4)) % SIZE_Size];
	rc_cIdx = tokens_Size[(index_Size + (5)) % SIZE_Size];
	qp_offset = tokens_Size[(index_Size + (6)) % SIZE_Size];
	offset = 0;
	i = 0;
	while (i <= sizeOfTU - 1) {
		j = 0;
		while (j <= sizeOfTU - 1) {
			tmp_Block_in = tokens_Block_in[(index_Block_in + (i * sizeOfTU + j)) % SIZE_Block_in];
			CoeffV[offset + j] = tmp_Block_in;
			j = j + 1;
		}
		offset = 16 + offset;
		i = i + 1;
	}

	// Update ports indexes
	index_Size += 7;
	read_end_Size();
	index_Block_in += 16;
	read_end_Block_in();

	rate_Size += 7;
	rate_Block_in += 16;
}
static void merge_V_block4x4_aligned() {

	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;
	i16 offset;
	i32 i;
	i32 j;
	i16 tmp_Block_in;

	sizeOfTU = tokens_Size[(index_Size % SIZE_Size) + (0)];
	RCskip = tokens_Size[(index_Size % SIZE_Size) + (1)];
	isDST = tokens_Size[(index_Size % SIZE_Size) + (2)];
	transformSkipFlag = tokens_Size[(index_Size % SIZE_Size) + (3)];
	slice_qp = tokens_Size[(index_Size % SIZE_Size) + (4)];
	rc_cIdx = tokens_Size[(index_Size % SIZE_Size) + (5)];
	qp_offset = tokens_Size[(index_Size % SIZE_Size) + (6)];
	offset = 0;
	i = 0;
	while (i <= sizeOfTU - 1) {
		j = 0;
		while (j <= sizeOfTU - 1) {
			tmp_Block_in = tokens_Block_in[(index_Block_in % SIZE_Block_in) + (i * sizeOfTU + j)];
			CoeffV[offset + j] = tmp_Block_in;
			j = j + 1;
		}
		offset = 16 + offset;
		i = i + 1;
	}

	// Update ports indexes
	index_Size += 7;
	read_end_Size();
	index_Block_in += 16;
	read_end_Block_in();

	rate_Size += 7;
	rate_Block_in += 16;
}
static i32 isSchedulable_merge_U_block8x8() {
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
	result = sizeOfTU == 8;
	return result;
}

static void merge_U_block8x8() {

	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;
	i16 offset;
	i32 i;
	i32 j;
	i16 tmp_Block_in;

	sizeOfTU = tokens_Size[(index_Size + (0)) % SIZE_Size];
	RCskip = tokens_Size[(index_Size + (1)) % SIZE_Size];
	isDST = tokens_Size[(index_Size + (2)) % SIZE_Size];
	transformSkipFlag = tokens_Size[(index_Size + (3)) % SIZE_Size];
	slice_qp = tokens_Size[(index_Size + (4)) % SIZE_Size];
	rc_cIdx = tokens_Size[(index_Size + (5)) % SIZE_Size];
	qp_offset = tokens_Size[(index_Size + (6)) % SIZE_Size];
	offset = 0;
	i = 0;
	while (i <= sizeOfTU - 1) {
		j = 0;
		while (j <= sizeOfTU - 1) {
			tmp_Block_in = tokens_Block_in[(index_Block_in + (i * sizeOfTU + j)) % SIZE_Block_in];
			CoeffU[offset + j] = tmp_Block_in;
			j = j + 1;
		}
		offset = 16 + offset;
		i = i + 1;
	}

	// Update ports indexes
	index_Size += 7;
	read_end_Size();
	index_Block_in += 64;
	read_end_Block_in();

	rate_Size += 7;
	rate_Block_in += 64;
}
static void merge_U_block8x8_aligned() {

	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;
	i16 offset;
	i32 i;
	i32 j;
	i16 tmp_Block_in;

	sizeOfTU = tokens_Size[(index_Size % SIZE_Size) + (0)];
	RCskip = tokens_Size[(index_Size % SIZE_Size) + (1)];
	isDST = tokens_Size[(index_Size % SIZE_Size) + (2)];
	transformSkipFlag = tokens_Size[(index_Size % SIZE_Size) + (3)];
	slice_qp = tokens_Size[(index_Size % SIZE_Size) + (4)];
	rc_cIdx = tokens_Size[(index_Size % SIZE_Size) + (5)];
	qp_offset = tokens_Size[(index_Size % SIZE_Size) + (6)];
	offset = 0;
	i = 0;
	while (i <= sizeOfTU - 1) {
		j = 0;
		while (j <= sizeOfTU - 1) {
			tmp_Block_in = tokens_Block_in[(index_Block_in % SIZE_Block_in) + (i * sizeOfTU + j)];
			CoeffU[offset + j] = tmp_Block_in;
			j = j + 1;
		}
		offset = 16 + offset;
		i = i + 1;
	}

	// Update ports indexes
	index_Size += 7;
	read_end_Size();
	index_Block_in += 64;
	read_end_Block_in();

	rate_Size += 7;
	rate_Block_in += 64;
}
static i32 isSchedulable_merge_V_block8x8() {
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
	result = sizeOfTU == 8;
	return result;
}

static void merge_V_block8x8() {

	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;
	i16 offset;
	i32 i;
	i32 j;
	i16 tmp_Block_in;

	sizeOfTU = tokens_Size[(index_Size + (0)) % SIZE_Size];
	RCskip = tokens_Size[(index_Size + (1)) % SIZE_Size];
	isDST = tokens_Size[(index_Size + (2)) % SIZE_Size];
	transformSkipFlag = tokens_Size[(index_Size + (3)) % SIZE_Size];
	slice_qp = tokens_Size[(index_Size + (4)) % SIZE_Size];
	rc_cIdx = tokens_Size[(index_Size + (5)) % SIZE_Size];
	qp_offset = tokens_Size[(index_Size + (6)) % SIZE_Size];
	offset = 0;
	i = 0;
	while (i <= sizeOfTU - 1) {
		j = 0;
		while (j <= sizeOfTU - 1) {
			tmp_Block_in = tokens_Block_in[(index_Block_in + (i * sizeOfTU + j)) % SIZE_Block_in];
			CoeffV[offset + j] = tmp_Block_in;
			j = j + 1;
		}
		offset = 16 + offset;
		i = i + 1;
	}

	// Update ports indexes
	index_Size += 7;
	read_end_Size();
	index_Block_in += 64;
	read_end_Block_in();

	rate_Size += 7;
	rate_Block_in += 64;
}
static void merge_V_block8x8_aligned() {

	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;
	i16 offset;
	i32 i;
	i32 j;
	i16 tmp_Block_in;

	sizeOfTU = tokens_Size[(index_Size % SIZE_Size) + (0)];
	RCskip = tokens_Size[(index_Size % SIZE_Size) + (1)];
	isDST = tokens_Size[(index_Size % SIZE_Size) + (2)];
	transformSkipFlag = tokens_Size[(index_Size % SIZE_Size) + (3)];
	slice_qp = tokens_Size[(index_Size % SIZE_Size) + (4)];
	rc_cIdx = tokens_Size[(index_Size % SIZE_Size) + (5)];
	qp_offset = tokens_Size[(index_Size % SIZE_Size) + (6)];
	offset = 0;
	i = 0;
	while (i <= sizeOfTU - 1) {
		j = 0;
		while (j <= sizeOfTU - 1) {
			tmp_Block_in = tokens_Block_in[(index_Block_in % SIZE_Block_in) + (i * sizeOfTU + j)];
			CoeffV[offset + j] = tmp_Block_in;
			j = j + 1;
		}
		offset = 16 + offset;
		i = i + 1;
	}

	// Update ports indexes
	index_Size += 7;
	read_end_Size();
	index_Block_in += 64;
	read_end_Block_in();

	rate_Size += 7;
	rate_Block_in += 64;
}
static i32 isSchedulable_merge_U_block16x16() {
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
	result = sizeOfTU == 16;
	return result;
}

static void merge_U_block16x16() {

	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;
	i32 i;
	i16 tmp_Block_in;

	sizeOfTU = tokens_Size[(index_Size + (0)) % SIZE_Size];
	RCskip = tokens_Size[(index_Size + (1)) % SIZE_Size];
	isDST = tokens_Size[(index_Size + (2)) % SIZE_Size];
	transformSkipFlag = tokens_Size[(index_Size + (3)) % SIZE_Size];
	slice_qp = tokens_Size[(index_Size + (4)) % SIZE_Size];
	rc_cIdx = tokens_Size[(index_Size + (5)) % SIZE_Size];
	qp_offset = tokens_Size[(index_Size + (6)) % SIZE_Size];
	i = 0;
	while (i <= 255) {
		tmp_Block_in = tokens_Block_in[(index_Block_in + (i)) % SIZE_Block_in];
		CoeffU[i] = tmp_Block_in;
		i = i + 1;
	}

	// Update ports indexes
	index_Size += 7;
	read_end_Size();
	index_Block_in += 256;
	read_end_Block_in();

	rate_Size += 7;
	rate_Block_in += 256;
}
static void merge_U_block16x16_aligned() {

	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;
	i32 i;
	i16 tmp_Block_in;

	sizeOfTU = tokens_Size[(index_Size % SIZE_Size) + (0)];
	RCskip = tokens_Size[(index_Size % SIZE_Size) + (1)];
	isDST = tokens_Size[(index_Size % SIZE_Size) + (2)];
	transformSkipFlag = tokens_Size[(index_Size % SIZE_Size) + (3)];
	slice_qp = tokens_Size[(index_Size % SIZE_Size) + (4)];
	rc_cIdx = tokens_Size[(index_Size % SIZE_Size) + (5)];
	qp_offset = tokens_Size[(index_Size % SIZE_Size) + (6)];
	i = 0;
	while (i <= 255) {
		tmp_Block_in = tokens_Block_in[(index_Block_in % SIZE_Block_in) + (i)];
		CoeffU[i] = tmp_Block_in;
		i = i + 1;
	}

	// Update ports indexes
	index_Size += 7;
	read_end_Size();
	index_Block_in += 256;
	read_end_Block_in();

	rate_Size += 7;
	rate_Block_in += 256;
}
static i32 isSchedulable_merge_V_block16x16() {
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
	result = sizeOfTU == 16;
	return result;
}

static void merge_V_block16x16() {

	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;
	i32 i;
	i16 tmp_Block_in;

	sizeOfTU = tokens_Size[(index_Size + (0)) % SIZE_Size];
	RCskip = tokens_Size[(index_Size + (1)) % SIZE_Size];
	isDST = tokens_Size[(index_Size + (2)) % SIZE_Size];
	transformSkipFlag = tokens_Size[(index_Size + (3)) % SIZE_Size];
	slice_qp = tokens_Size[(index_Size + (4)) % SIZE_Size];
	rc_cIdx = tokens_Size[(index_Size + (5)) % SIZE_Size];
	qp_offset = tokens_Size[(index_Size + (6)) % SIZE_Size];
	i = 0;
	while (i <= 255) {
		tmp_Block_in = tokens_Block_in[(index_Block_in + (i)) % SIZE_Block_in];
		CoeffV[i] = tmp_Block_in;
		i = i + 1;
	}

	// Update ports indexes
	index_Size += 7;
	read_end_Size();
	index_Block_in += 256;
	read_end_Block_in();

	rate_Size += 7;
	rate_Block_in += 256;
}
static void merge_V_block16x16_aligned() {

	i8 sizeOfTU;
	i8 RCskip;
	i8 isDST;
	i8 transformSkipFlag;
	i8 slice_qp;
	i8 rc_cIdx;
	i8 qp_offset;
	i32 i;
	i16 tmp_Block_in;

	sizeOfTU = tokens_Size[(index_Size % SIZE_Size) + (0)];
	RCskip = tokens_Size[(index_Size % SIZE_Size) + (1)];
	isDST = tokens_Size[(index_Size % SIZE_Size) + (2)];
	transformSkipFlag = tokens_Size[(index_Size % SIZE_Size) + (3)];
	slice_qp = tokens_Size[(index_Size % SIZE_Size) + (4)];
	rc_cIdx = tokens_Size[(index_Size % SIZE_Size) + (5)];
	qp_offset = tokens_Size[(index_Size % SIZE_Size) + (6)];
	i = 0;
	while (i <= 255) {
		tmp_Block_in = tokens_Block_in[(index_Block_in % SIZE_Block_in) + (i)];
		CoeffV[i] = tmp_Block_in;
		i = i + 1;
	}

	// Update ports indexes
	index_Size += 7;
	read_end_Size();
	index_Block_in += 256;
	read_end_Block_in();

	rate_Size += 7;
	rate_Block_in += 256;
}
static i32 isSchedulable_output_Y() {
	i32 result;
	u8 local_block4x4Idx;
	u8 local_nbBlock4x4;

	local_block4x4Idx = block4x4Idx;
	local_nbBlock4x4 = nbBlock4x4;
	result = local_block4x4Idx != local_nbBlock4x4;
	return result;
}

static void output_Y() {

	i16 offset;
	u8 local_block4x4Idx;
	u16 tmp_scan4x4_Y_offset;
	u16 tmp_scan8x8_Y_offset;
	u16 tmp_scan16x16_Y_offset;
	i32 i;
	i32 j;
	i16 tmp_CoeffY;

	offset = 0;
	local_block4x4Idx = block4x4Idx;
	tmp_scan4x4_Y_offset = scan4x4_Y_offset[local_block4x4Idx & 3];
	local_block4x4Idx = block4x4Idx;
	tmp_scan8x8_Y_offset = scan8x8_Y_offset[local_block4x4Idx >> 2 & 3];
	local_block4x4Idx = block4x4Idx;
	tmp_scan16x16_Y_offset = scan16x16_Y_offset[local_block4x4Idx >> 4 & 3];
	offset = tmp_scan4x4_Y_offset + tmp_scan8x8_Y_offset + tmp_scan16x16_Y_offset;
	i = 0;
	while (i <= 3) {
		j = 0;
		while (j <= 3) {
			tmp_CoeffY = CoeffY[offset + j];
			tokens_Block[(index_Block + ((i << 2) + j)) % SIZE_Block] = tmp_CoeffY;
			j = j + 1;
		}
		offset = 32 + offset;
		i = i + 1;
	}

	// Update ports indexes
	index_Block += 16;
	write_end_Block();

}
static void output_Y_aligned() {

	i16 offset;
	u8 local_block4x4Idx;
	u16 tmp_scan4x4_Y_offset;
	u16 tmp_scan8x8_Y_offset;
	u16 tmp_scan16x16_Y_offset;
	i32 i;
	i32 j;
	i16 tmp_CoeffY;

	offset = 0;
	local_block4x4Idx = block4x4Idx;
	tmp_scan4x4_Y_offset = scan4x4_Y_offset[local_block4x4Idx & 3];
	local_block4x4Idx = block4x4Idx;
	tmp_scan8x8_Y_offset = scan8x8_Y_offset[local_block4x4Idx >> 2 & 3];
	local_block4x4Idx = block4x4Idx;
	tmp_scan16x16_Y_offset = scan16x16_Y_offset[local_block4x4Idx >> 4 & 3];
	offset = tmp_scan4x4_Y_offset + tmp_scan8x8_Y_offset + tmp_scan16x16_Y_offset;
	i = 0;
	while (i <= 3) {
		j = 0;
		while (j <= 3) {
			tmp_CoeffY = CoeffY[offset + j];
			tokens_Block[(index_Block % SIZE_Block) + ((i << 2) + j)] = tmp_CoeffY;
			j = j + 1;
		}
		offset = 32 + offset;
		i = i + 1;
	}

	// Update ports indexes
	index_Block += 16;
	write_end_Block();

}
static i32 isSchedulable_output_done() {
	i32 result;
	u8 local_block4x4Idx;
	u8 local_nbBlock4x4;

	local_block4x4Idx = block4x4Idx;
	local_nbBlock4x4 = nbBlock4x4;
	result = local_block4x4Idx == local_nbBlock4x4;
	return result;
}

static void output_done() {


	block4x4Idx = 0;

	// Update ports indexes

}
static i32 isSchedulable_output_U() {
	i32 result;

	result = 1;
	return result;
}

static void output_U() {

	i16 offset;
	u8 local_block4x4Idx;
	u16 tmp_scan4x4_UV_offset;
	u16 tmp_scan8x8_UV_offset;
	u16 tmp_scan16x16_UV_offset;
	i32 i;
	i32 j;
	i16 tmp_CoeffU;

	offset = 0;
	local_block4x4Idx = block4x4Idx;
	tmp_scan4x4_UV_offset = scan4x4_UV_offset[local_block4x4Idx & 3];
	local_block4x4Idx = block4x4Idx;
	tmp_scan8x8_UV_offset = scan8x8_UV_offset[local_block4x4Idx >> 2 & 3];
	local_block4x4Idx = block4x4Idx;
	tmp_scan16x16_UV_offset = scan16x16_UV_offset[local_block4x4Idx >> 4 & 3];
	offset = tmp_scan4x4_UV_offset + tmp_scan8x8_UV_offset + tmp_scan16x16_UV_offset;
	i = 0;
	while (i <= 1) {
		j = 0;
		while (j <= 1) {
			tmp_CoeffU = CoeffU[offset + j];
			tokens_Block[(index_Block + ((i << 1) + j)) % SIZE_Block] = tmp_CoeffU;
			j = j + 1;
		}
		offset = 16 + offset;
		i = i + 1;
	}

	// Update ports indexes
	index_Block += 4;
	write_end_Block();

}
static void output_U_aligned() {

	i16 offset;
	u8 local_block4x4Idx;
	u16 tmp_scan4x4_UV_offset;
	u16 tmp_scan8x8_UV_offset;
	u16 tmp_scan16x16_UV_offset;
	i32 i;
	i32 j;
	i16 tmp_CoeffU;

	offset = 0;
	local_block4x4Idx = block4x4Idx;
	tmp_scan4x4_UV_offset = scan4x4_UV_offset[local_block4x4Idx & 3];
	local_block4x4Idx = block4x4Idx;
	tmp_scan8x8_UV_offset = scan8x8_UV_offset[local_block4x4Idx >> 2 & 3];
	local_block4x4Idx = block4x4Idx;
	tmp_scan16x16_UV_offset = scan16x16_UV_offset[local_block4x4Idx >> 4 & 3];
	offset = tmp_scan4x4_UV_offset + tmp_scan8x8_UV_offset + tmp_scan16x16_UV_offset;
	i = 0;
	while (i <= 1) {
		j = 0;
		while (j <= 1) {
			tmp_CoeffU = CoeffU[offset + j];
			tokens_Block[(index_Block % SIZE_Block) + ((i << 1) + j)] = tmp_CoeffU;
			j = j + 1;
		}
		offset = 16 + offset;
		i = i + 1;
	}

	// Update ports indexes
	index_Block += 4;
	write_end_Block();

}
static i32 isSchedulable_output_V() {
	i32 result;

	result = 1;
	return result;
}

static void output_V() {

	i16 offset;
	u8 local_block4x4Idx;
	u16 tmp_scan4x4_UV_offset;
	u16 tmp_scan8x8_UV_offset;
	u16 tmp_scan16x16_UV_offset;
	i32 i;
	i32 j;
	i16 tmp_CoeffV;

	offset = 0;
	local_block4x4Idx = block4x4Idx;
	tmp_scan4x4_UV_offset = scan4x4_UV_offset[local_block4x4Idx & 3];
	local_block4x4Idx = block4x4Idx;
	tmp_scan8x8_UV_offset = scan8x8_UV_offset[local_block4x4Idx >> 2 & 3];
	local_block4x4Idx = block4x4Idx;
	tmp_scan16x16_UV_offset = scan16x16_UV_offset[local_block4x4Idx >> 4 & 3];
	offset = tmp_scan4x4_UV_offset + tmp_scan8x8_UV_offset + tmp_scan16x16_UV_offset;
	i = 0;
	while (i <= 1) {
		j = 0;
		while (j <= 1) {
			tmp_CoeffV = CoeffV[offset + j];
			tokens_Block[(index_Block + ((i << 1) + j)) % SIZE_Block] = tmp_CoeffV;
			j = j + 1;
		}
		offset = 16 + offset;
		i = i + 1;
	}
	local_block4x4Idx = block4x4Idx;
	block4x4Idx = local_block4x4Idx + 1;

	// Update ports indexes
	index_Block += 4;
	write_end_Block();

}
static void output_V_aligned() {

	i16 offset;
	u8 local_block4x4Idx;
	u16 tmp_scan4x4_UV_offset;
	u16 tmp_scan8x8_UV_offset;
	u16 tmp_scan16x16_UV_offset;
	i32 i;
	i32 j;
	i16 tmp_CoeffV;

	offset = 0;
	local_block4x4Idx = block4x4Idx;
	tmp_scan4x4_UV_offset = scan4x4_UV_offset[local_block4x4Idx & 3];
	local_block4x4Idx = block4x4Idx;
	tmp_scan8x8_UV_offset = scan8x8_UV_offset[local_block4x4Idx >> 2 & 3];
	local_block4x4Idx = block4x4Idx;
	tmp_scan16x16_UV_offset = scan16x16_UV_offset[local_block4x4Idx >> 4 & 3];
	offset = tmp_scan4x4_UV_offset + tmp_scan8x8_UV_offset + tmp_scan16x16_UV_offset;
	i = 0;
	while (i <= 1) {
		j = 0;
		while (j <= 1) {
			tmp_CoeffV = CoeffV[offset + j];
			tokens_Block[(index_Block % SIZE_Block) + ((i << 1) + j)] = tmp_CoeffV;
			j = j + 1;
		}
		offset = 16 + offset;
		i = i + 1;
	}
	local_block4x4Idx = block4x4Idx;
	block4x4Idx = local_block4x4Idx + 1;

	// Update ports indexes
	index_Block += 4;
	write_end_Block();

}

////////////////////////////////////////////////////////////////////////////////
// Initializes

void HevcDecoder_xIT_Block_Merger_initialize(schedinfo_t *si) {
	int i = 0;
	write_Block();
	/* Set initial state to current FSM state */
	_FSM_state = my_state_merge_Y;
finished:
	write_end_Block();
	return;
}

////////////////////////////////////////////////////////////////////////////////
// Action scheduler

void HevcDecoder_xIT_Block_Merger_scheduler(schedinfo_t *si) {
	int i = 0;

	read_Size();
	read_Block_in();
	write_Block();

	// jump to FSM state
	switch (_FSM_state) {
	case my_state_merge_U:
		goto l_merge_U;
	case my_state_merge_V:
		goto l_merge_V;
	case my_state_merge_Y:
		goto l_merge_Y;
	case my_state_output_U:
		goto l_output_U;
	case my_state_output_V:
		goto l_output_V;
	case my_state_output_Y:
		goto l_output_Y;
	case my_state_zero_UV:
		goto l_zero_UV;
	default:
		printf("unknown state in HevcDecoder_xIT_Block_Merger.c : %s\n", stateNames[_FSM_state]);
		exit(1);
	}

	// FSM transitions
l_merge_U:
	if (numTokens_Size - index_Size >= 7 && numTokens_Block_in - index_Block_in >= 16 && isSchedulable_merge_U_block4x4()) {
		{
			int isAligned = 1;
			isAligned &= ((index_Size % SIZE_Size) < ((index_Size + 7) % SIZE_Size));
			isAligned &= ((index_Block_in % SIZE_Block_in) < ((index_Block_in + 16) % SIZE_Block_in));
			if (isAligned) {
				merge_U_block4x4_aligned();
			} else {
				merge_U_block4x4();
			}
		}
		i++;
		goto l_merge_V;
	} else if (numTokens_Size - index_Size >= 7 && numTokens_Block_in - index_Block_in >= 64 && isSchedulable_merge_U_block8x8()) {
		{
			int isAligned = 1;
			isAligned &= ((index_Size % SIZE_Size) < ((index_Size + 7) % SIZE_Size));
			isAligned &= ((index_Block_in % SIZE_Block_in) < ((index_Block_in + 64) % SIZE_Block_in));
			if (isAligned) {
				merge_U_block8x8_aligned();
			} else {
				merge_U_block8x8();
			}
		}
		i++;
		goto l_merge_V;
	} else if (numTokens_Size - index_Size >= 7 && numTokens_Block_in - index_Block_in >= 256 && isSchedulable_merge_U_block16x16()) {
		{
			int isAligned = 1;
			isAligned &= ((index_Size % SIZE_Size) < ((index_Size + 7) % SIZE_Size));
			isAligned &= ((index_Block_in % SIZE_Block_in) < ((index_Block_in + 256) % SIZE_Block_in));
			if (isAligned) {
				merge_U_block16x16_aligned();
			} else {
				merge_U_block16x16();
			}
		}
		i++;
		goto l_merge_V;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_merge_U;
		goto finished;
	}
l_merge_V:
	if (numTokens_Size - index_Size >= 7 && numTokens_Block_in - index_Block_in >= 16 && isSchedulable_merge_V_block4x4()) {
		{
			int isAligned = 1;
			isAligned &= ((index_Size % SIZE_Size) < ((index_Size + 7) % SIZE_Size));
			isAligned &= ((index_Block_in % SIZE_Block_in) < ((index_Block_in + 16) % SIZE_Block_in));
			if (isAligned) {
				merge_V_block4x4_aligned();
			} else {
				merge_V_block4x4();
			}
		}
		i++;
		goto l_output_Y;
	} else if (numTokens_Size - index_Size >= 7 && numTokens_Block_in - index_Block_in >= 64 && isSchedulable_merge_V_block8x8()) {
		{
			int isAligned = 1;
			isAligned &= ((index_Size % SIZE_Size) < ((index_Size + 7) % SIZE_Size));
			isAligned &= ((index_Block_in % SIZE_Block_in) < ((index_Block_in + 64) % SIZE_Block_in));
			if (isAligned) {
				merge_V_block8x8_aligned();
			} else {
				merge_V_block8x8();
			}
		}
		i++;
		goto l_output_Y;
	} else if (numTokens_Size - index_Size >= 7 && numTokens_Block_in - index_Block_in >= 256 && isSchedulable_merge_V_block16x16()) {
		{
			int isAligned = 1;
			isAligned &= ((index_Size % SIZE_Size) < ((index_Size + 7) % SIZE_Size));
			isAligned &= ((index_Block_in % SIZE_Block_in) < ((index_Block_in + 256) % SIZE_Block_in));
			if (isAligned) {
				merge_V_block16x16_aligned();
			} else {
				merge_V_block16x16();
			}
		}
		i++;
		goto l_output_Y;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_merge_V;
		goto finished;
	}
l_merge_Y:
	if (numTokens_Size - index_Size >= 7 && numTokens_Block_in - index_Block_in >= 16 && isSchedulable_merge_Y_loop_block4x4()) {
		{
			int isAligned = 1;
			isAligned &= ((index_Size % SIZE_Size) < ((index_Size + 7) % SIZE_Size));
			isAligned &= ((index_Block_in % SIZE_Block_in) < ((index_Block_in + 16) % SIZE_Block_in));
			if (isAligned) {
				merge_Y_loop_block4x4_aligned();
			} else {
				merge_Y_loop_block4x4();
			}
		}
		i++;
		goto l_merge_Y;
	} else if (numTokens_Size - index_Size >= 7 && numTokens_Block_in - index_Block_in >= 16 && isSchedulable_merge_Y_block4x4()) {
		{
			int isAligned = 1;
			isAligned &= ((index_Size % SIZE_Size) < ((index_Size + 7) % SIZE_Size));
			isAligned &= ((index_Block_in % SIZE_Block_in) < ((index_Block_in + 16) % SIZE_Block_in));
			if (isAligned) {
				merge_Y_block4x4_aligned();
			} else {
				merge_Y_block4x4();
			}
		}
		i++;
		goto l_merge_U;
	} else if (numTokens_Size - index_Size >= 7 && numTokens_Block_in - index_Block_in >= 64 && isSchedulable_merge_Y_block8x8()) {
		{
			int isAligned = 1;
			isAligned &= ((index_Size % SIZE_Size) < ((index_Size + 7) % SIZE_Size));
			isAligned &= ((index_Block_in % SIZE_Block_in) < ((index_Block_in + 64) % SIZE_Block_in));
			if (isAligned) {
				merge_Y_block8x8_aligned();
			} else {
				merge_Y_block8x8();
			}
		}
		i++;
		goto l_merge_U;
	} else if (numTokens_Size - index_Size >= 7 && numTokens_Block_in - index_Block_in >= 256 && isSchedulable_merge_Y_block16x16()) {
		{
			int isAligned = 1;
			isAligned &= ((index_Size % SIZE_Size) < ((index_Size + 7) % SIZE_Size));
			isAligned &= ((index_Block_in % SIZE_Block_in) < ((index_Block_in + 256) % SIZE_Block_in));
			if (isAligned) {
				merge_Y_block16x16_aligned();
			} else {
				merge_Y_block16x16();
			}
		}
		i++;
		goto l_merge_U;
	} else if (numTokens_Size - index_Size >= 7 && numTokens_Block_in - index_Block_in >= 1024 && isSchedulable_merge_Y_block32x32()) {
		{
			int isAligned = 1;
			isAligned &= ((index_Size % SIZE_Size) < ((index_Size + 7) % SIZE_Size));
			isAligned &= ((index_Block_in % SIZE_Block_in) < ((index_Block_in + 1024) % SIZE_Block_in));
			if (isAligned) {
				merge_Y_block32x32_aligned();
			} else {
				merge_Y_block32x32();
			}
		}
		i++;
		goto l_merge_U;
	} else if (numTokens_Size - index_Size >= 7 && numTokens_Block_in - index_Block_in >= 4096 && isSchedulable_merge_Y_64x64()) {
		int stop = 0;
		if (4096 > SIZE_Block - index_Block + HevcDecoder_xIT_Block_Merger_Block->read_inds[0]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_merge_Y;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		{
			int isAligned = 1;
			isAligned &= ((index_Size % SIZE_Size) < ((index_Size + 7) % SIZE_Size));
			isAligned &= ((index_Block_in % SIZE_Block_in) < ((index_Block_in + 4096) % SIZE_Block_in));
			isAligned &= ((index_Block % SIZE_Block) < ((index_Block + 4096) % SIZE_Block));
			if (isAligned) {
				merge_Y_64x64_aligned();
			} else {
				merge_Y_64x64();
			}
		}
		i++;
		goto l_zero_UV;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_merge_Y;
		goto finished;
	}
l_output_U:
	if (isSchedulable_output_U()) {
		int stop = 0;
		if (4 > SIZE_Block - index_Block + HevcDecoder_xIT_Block_Merger_Block->read_inds[0]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_output_U;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		{
			int isAligned = 1;
			isAligned &= ((index_Block % SIZE_Block) < ((index_Block + 4) % SIZE_Block));
			if (isAligned) {
				output_U_aligned();
			} else {
				output_U();
			}
		}
		i++;
		goto l_output_V;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_output_U;
		goto finished;
	}
l_output_V:
	if (isSchedulable_output_V()) {
		int stop = 0;
		if (4 > SIZE_Block - index_Block + HevcDecoder_xIT_Block_Merger_Block->read_inds[0]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_output_V;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		{
			int isAligned = 1;
			isAligned &= ((index_Block % SIZE_Block) < ((index_Block + 4) % SIZE_Block));
			if (isAligned) {
				output_V_aligned();
			} else {
				output_V();
			}
		}
		i++;
		goto l_output_Y;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_output_V;
		goto finished;
	}
l_output_Y:
	if (isSchedulable_output_Y()) {
		int stop = 0;
		if (16 > SIZE_Block - index_Block + HevcDecoder_xIT_Block_Merger_Block->read_inds[0]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_output_Y;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		{
			int isAligned = 1;
			isAligned &= ((index_Block % SIZE_Block) < ((index_Block + 16) % SIZE_Block));
			if (isAligned) {
				output_Y_aligned();
			} else {
				output_Y();
			}
		}
		i++;
		goto l_output_U;
	} else if (isSchedulable_output_done()) {
		output_done();
		i++;
		goto l_merge_Y;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_output_Y;
		goto finished;
	}
l_zero_UV:
	if (numTokens_Size - index_Size >= 14 && numTokens_Block_in - index_Block_in >= 2048 && isSchedulable_merge_UV_64x64()) {
		int stop = 0;
		if (2048 > SIZE_Block - index_Block + HevcDecoder_xIT_Block_Merger_Block->read_inds[0]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_zero_UV;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		{
			int isAligned = 1;
			isAligned &= ((index_Size % SIZE_Size) < ((index_Size + 14) % SIZE_Size));
			isAligned &= ((index_Block_in % SIZE_Block_in) < ((index_Block_in + 2048) % SIZE_Block_in));
			isAligned &= ((index_Block % SIZE_Block) < ((index_Block + 2048) % SIZE_Block));
			if (isAligned) {
				merge_UV_64x64_aligned();
			} else {
				merge_UV_64x64();
			}
		}
		i++;
		goto l_merge_Y;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_zero_UV;
		goto finished;
	}
finished:
	read_end_Size();
	read_end_Block_in();
	write_end_Block();
}
