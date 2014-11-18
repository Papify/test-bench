// Source file is "L/RVC/src/org/sc29/wg11/mpegh/part2/SelectCu.cal"

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
extern actor_t HevcDecoder_SelectCU;

////////////////////////////////////////////////////////////////////////////////
// Input FIFOs
extern fifo_u16_t *HevcDecoder_SelectCU_CUInfo;
extern fifo_u8_t *HevcDecoder_SelectCU_InterSample;
extern fifo_u8_t *HevcDecoder_SelectCU_IntraSample;
extern fifo_u8_t *HevcDecoder_SelectCU_PartMode;
extern fifo_i16_t *HevcDecoder_SelectCU_ResidualSample;

////////////////////////////////////////////////////////////////////////////////
// Input Fifo control variables
static unsigned int index_CUInfo;
static unsigned int numTokens_CUInfo;
#define SIZE_CUInfo SIZE
#define tokens_CUInfo HevcDecoder_SelectCU_CUInfo->contents

extern connection_t connection_HevcDecoder_SelectCU_CUInfo;
#define rate_CUInfo connection_HevcDecoder_SelectCU_CUInfo.rate

static unsigned int index_InterSample;
static unsigned int numTokens_InterSample;
#define SIZE_InterSample SIZE
#define tokens_InterSample HevcDecoder_SelectCU_InterSample->contents

extern connection_t connection_HevcDecoder_SelectCU_InterSample;
#define rate_InterSample connection_HevcDecoder_SelectCU_InterSample.rate

static unsigned int index_IntraSample;
static unsigned int numTokens_IntraSample;
#define SIZE_IntraSample SIZE
#define tokens_IntraSample HevcDecoder_SelectCU_IntraSample->contents

extern connection_t connection_HevcDecoder_SelectCU_IntraSample;
#define rate_IntraSample connection_HevcDecoder_SelectCU_IntraSample.rate

static unsigned int index_PartMode;
static unsigned int numTokens_PartMode;
#define SIZE_PartMode SIZE
#define tokens_PartMode HevcDecoder_SelectCU_PartMode->contents

extern connection_t connection_HevcDecoder_SelectCU_PartMode;
#define rate_PartMode connection_HevcDecoder_SelectCU_PartMode.rate

static unsigned int index_ResidualSample;
static unsigned int numTokens_ResidualSample;
#define SIZE_ResidualSample SIZE
#define tokens_ResidualSample HevcDecoder_SelectCU_ResidualSample->contents

extern connection_t connection_HevcDecoder_SelectCU_ResidualSample;
#define rate_ResidualSample connection_HevcDecoder_SelectCU_ResidualSample.rate

////////////////////////////////////////////////////////////////////////////////
// Predecessors
extern actor_t HevcDecoder_Algo_Parser;
extern actor_t HevcDecoder_InterPrediction;
extern actor_t HevcDecoder_IntraPrediction;
extern actor_t HevcDecoder_Algo_Parser;
extern actor_t HevcDecoder_xIT_Block_Merger;

////////////////////////////////////////////////////////////////////////////////
// Output FIFOs
extern fifo_u8_t *HevcDecoder_SelectCU_Sample;

////////////////////////////////////////////////////////////////////////////////
// Output Fifo control variables
static unsigned int index_Sample;
static unsigned int numFree_Sample;
#define NUM_READERS_Sample 2
#define SIZE_Sample SIZE
#define tokens_Sample HevcDecoder_SelectCU_Sample->contents

////////////////////////////////////////////////////////////////////////////////
// Successors
extern actor_t HevcDecoder_IntraPrediction;
extern actor_t HevcDecoder_DBFilter_DeblockFilt;


////////////////////////////////////////////////////////////////////////////////
// State variables of the actor
#define HevcDecoder_SelectCU_PART_MODE_SLICE_DEP 9
#define HevcDecoder_SelectCU_PART_MODE_SLICE_INDEP 10
#define HevcDecoder_SelectCU_PART_MODE_PICT 8
static const u8 HevcDecoder_SelectCU_partModeToNumPart[8] = {1, 2, 2, 4, 2, 2, 2, 2};
#define HevcDecoder_SelectCU_PART_2NxN 1
#define HevcDecoder_SelectCU_PART_2NxnU 4
#define HevcDecoder_SelectCU_PART_2NxnD 5
#define HevcDecoder_SelectCU_INTRA 1
#define HevcDecoder_SelectCU_INTER 0
#define HevcDecoder_SelectCU_SKIP 2
#define HevcDecoder_SelectCU_OTHER 16
static const u8 HevcDecoder_SelectCU_absCoordInBlkToZScanTable[16][16] = {{0, 1, 4, 5, 16, 17, 20, 21, 64, 65, 68, 69, 80, 81, 84, 85}, {2, 3, 6, 7, 18, 19, 22, 23, 66, 67, 70, 71, 82, 83, 86, 87}, {8, 9, 12, 13, 24, 25, 28, 29, 72, 73, 76, 77, 88, 89, 92, 93}, {10, 11, 14, 15, 26, 27, 30, 31, 74, 75, 78, 79, 90, 91, 94, 95}, {32, 33, 36, 37, 48, 49, 52, 53, 96, 97, 100, 101, 112, 113, 116, 117}, {34, 35, 38, 39, 50, 51, 54, 55, 98, 99, 102, 103, 114, 115, 118, 119}, {40, 41, 44, 45, 56, 57, 60, 61, 104, 105, 108, 109, 120, 121, 124, 125}, {42, 43, 46, 47, 58, 59, 62, 63, 106, 107, 110, 111, 122, 123, 126, 127}, {128, 129, 132, 133, 144, 145, 148, 149, 192, 193, 196, 197, 208, 209, 212, 213}, {130, 131, 134, 135, 146, 147, 150, 151, 194, 195, 198, 199, 210, 211, 214, 215}, {136, 137, 140, 141, 152, 153, 156, 157, 200, 201, 204, 205, 216, 217, 220, 221}, {138, 139, 142, 143, 154, 155, 158, 159, 202, 203, 206, 207, 218, 219, 222, 223}, {160, 161, 164, 165, 176, 177, 180, 181, 224, 225, 228, 229, 240, 241, 244, 245}, {162, 163, 166, 167, 178, 179, 182, 183, 226, 227, 230, 231, 242, 243, 246, 247}, {168, 169, 172, 173, 184, 185, 188, 189, 232, 233, 236, 237, 248, 249, 252, 253}, {170, 171, 174, 175, 186, 187, 190, 191, 234, 235, 238, 239, 250, 251, 254, 255}};
static const u16 PU_SIZE_TO_NB_BLK_TO_CLIP[17] = {0, 1, 4, 4, 16, 16, 16, 16, 64, 64, 64, 64, 64, 64, 64, 64, 256};
#define SCU_SIZE 24
static u8 numPart;
static u8 numPartDecoded;
static u8 predSamp[6144];
static i32 sampGot[512];
static u16 nbBlkToClip;
static u8 cuMode;
static u8 partMode;
static u8 cuSize[4][2];
static u8 cuOff[4][2] = {{0, 0}, {0, 0}, {0, 0}, {0, 0}};
static u8 cuWidth;
static u16 nbBlk;
static u16 idxBlk;
static u16 idxBlkInterpred;
static u8 xIdx;
static u8 yIdx;

////////////////////////////////////////////////////////////////////////////////
// Initial FSM state of the actor
enum states {
	my_state_CheckNbBlkToClip,
	my_state_GetCuInfo,
	my_state_GetCuMode,
	my_state_GetCuSampleInter16Blk,
	my_state_GetCuSampleInter1Blk,
	my_state_GetCuSampleInter256Blk,
	my_state_GetCuSampleInter4Blk,
	my_state_GetCuSampleInter64Blk,
	my_state_GetCuSampleIntra,
	my_state_GetPartMode
};

static char *stateNames[] = {
	"CheckNbBlkToClip",
	"GetCuInfo",
	"GetCuMode",
	"GetCuSampleInter16Blk",
	"GetCuSampleInter1Blk",
	"GetCuSampleInter256Blk",
	"GetCuSampleInter4Blk",
	"GetCuSampleInter64Blk",
	"GetCuSampleIntra",
	"GetPartMode"
};

static enum states _FSM_state;



////////////////////////////////////////////////////////////////////////////////
// Token functions
static void read_CUInfo() {
	index_CUInfo = HevcDecoder_SelectCU_CUInfo->read_inds[2];
	numTokens_CUInfo = index_CUInfo + fifo_u16_get_num_tokens(HevcDecoder_SelectCU_CUInfo, 2);
}

static void read_end_CUInfo() {
	HevcDecoder_SelectCU_CUInfo->read_inds[2] = index_CUInfo;
}
static void read_InterSample() {
	index_InterSample = HevcDecoder_SelectCU_InterSample->read_inds[0];
	numTokens_InterSample = index_InterSample + fifo_u8_get_num_tokens(HevcDecoder_SelectCU_InterSample, 0);
}

static void read_end_InterSample() {
	HevcDecoder_SelectCU_InterSample->read_inds[0] = index_InterSample;
}
static void read_IntraSample() {
	index_IntraSample = HevcDecoder_SelectCU_IntraSample->read_inds[0];
	numTokens_IntraSample = index_IntraSample + fifo_u8_get_num_tokens(HevcDecoder_SelectCU_IntraSample, 0);
}

static void read_end_IntraSample() {
	HevcDecoder_SelectCU_IntraSample->read_inds[0] = index_IntraSample;
}
static void read_PartMode() {
	index_PartMode = HevcDecoder_SelectCU_PartMode->read_inds[1];
	numTokens_PartMode = index_PartMode + fifo_u8_get_num_tokens(HevcDecoder_SelectCU_PartMode, 1);
}

static void read_end_PartMode() {
	HevcDecoder_SelectCU_PartMode->read_inds[1] = index_PartMode;
}
static void read_ResidualSample() {
	index_ResidualSample = HevcDecoder_SelectCU_ResidualSample->read_inds[0];
	numTokens_ResidualSample = index_ResidualSample + fifo_i16_get_num_tokens(HevcDecoder_SelectCU_ResidualSample, 0);
}

static void read_end_ResidualSample() {
	HevcDecoder_SelectCU_ResidualSample->read_inds[0] = index_ResidualSample;
}

static void write_Sample() {
	index_Sample = HevcDecoder_SelectCU_Sample->write_ind;
	numFree_Sample = index_Sample + fifo_u8_get_room(HevcDecoder_SelectCU_Sample, NUM_READERS_Sample, SIZE_Sample);
}

static void write_end_Sample() {
	HevcDecoder_SelectCU_Sample->write_ind = index_Sample;
}

////////////////////////////////////////////////////////////////////////////////
// Functions/procedures
static i32 HevcDecoder_SelectCU_max(i32 a, i32 b);
static i32 HevcDecoder_SelectCU_min(i32 a, i32 b);
static i32 HevcDecoder_SelectCU_clip_i32(i32 Value, i32 minVal, i32 maxVal);
static u16 HevcDecoder_SelectCU_absCoordInBlkToZScan(u16 addr[2]);

static i32 HevcDecoder_SelectCU_max(i32 a, i32 b) {
	i32 tmp_if;

	if (a > b) {
		tmp_if = a;
	} else {
		tmp_if = b;
	}
	return tmp_if;
}
static i32 HevcDecoder_SelectCU_min(i32 a, i32 b) {
	i32 tmp_if;

	if (a < b) {
		tmp_if = a;
	} else {
		tmp_if = b;
	}
	return tmp_if;
}
static i32 HevcDecoder_SelectCU_clip_i32(i32 Value, i32 minVal, i32 maxVal) {
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
static u16 HevcDecoder_SelectCU_absCoordInBlkToZScan(u16 addr[2]) {
	u16 tmp_addr;
	u16 tmp_addr0;
	u8 tmp_absCoordInBlkToZScanTable;

	tmp_addr = addr[1];
	tmp_addr0 = addr[0];
	tmp_absCoordInBlkToZScanTable = HevcDecoder_SelectCU_absCoordInBlkToZScanTable[tmp_addr][tmp_addr0];
	return tmp_absCoordInBlkToZScanTable;
}

////////////////////////////////////////////////////////////////////////////////
// Actions
static i32 isSchedulable_isNewSlice() {
	i32 result;
	u8 partModeVal;
	u8 local_PART_MODE_SLICE_DEP;
	u8 local_PART_MODE_SLICE_INDEP;
	u8 local_PART_MODE_PICT;

	partModeVal = tokens_PartMode[(index_PartMode + (0)) % SIZE_PartMode];
	local_PART_MODE_SLICE_DEP = HevcDecoder_SelectCU_PART_MODE_SLICE_DEP;
	local_PART_MODE_SLICE_INDEP = HevcDecoder_SelectCU_PART_MODE_SLICE_INDEP;
	local_PART_MODE_PICT = HevcDecoder_SelectCU_PART_MODE_PICT;
	result = partModeVal == local_PART_MODE_SLICE_DEP || partModeVal == local_PART_MODE_SLICE_INDEP || partModeVal == local_PART_MODE_PICT;
	return result;
}

static void isNewSlice() {

	u8 partModeVal;

	partModeVal = tokens_PartMode[(index_PartMode + (0)) % SIZE_PartMode];

	// Update ports indexes
	index_PartMode += 1;

	rate_PartMode += 1;
}
static i32 isSchedulable_getPartMode() {
	i32 result;
	u8 partModeVal;
	u8 local_PART_MODE_SLICE_DEP;
	u8 local_PART_MODE_SLICE_INDEP;
	u8 local_PART_MODE_PICT;

	partModeVal = tokens_PartMode[(index_PartMode + (0)) % SIZE_PartMode];
	local_PART_MODE_SLICE_DEP = HevcDecoder_SelectCU_PART_MODE_SLICE_DEP;
	local_PART_MODE_SLICE_INDEP = HevcDecoder_SelectCU_PART_MODE_SLICE_INDEP;
	local_PART_MODE_PICT = HevcDecoder_SelectCU_PART_MODE_PICT;
	result = partModeVal != local_PART_MODE_SLICE_DEP && partModeVal != local_PART_MODE_SLICE_INDEP && partModeVal != local_PART_MODE_PICT;
	return result;
}

static void getPartMode() {

	u8 partModeVal;
	u8 tmp_partModeToNumPart;

	partModeVal = tokens_PartMode[(index_PartMode + (0)) % SIZE_PartMode];
	partMode = partModeVal;
	tmp_partModeToNumPart = HevcDecoder_SelectCU_partModeToNumPart[partModeVal];
	numPart = tmp_partModeToNumPart;
	numPartDecoded = 0;

	// Update ports indexes
	index_PartMode += 1;

	rate_PartMode += 1;
}
static i32 isSchedulable_getCuInfo_launch() {
	i32 result;
	u8 local_numPartDecoded;
	u8 local_numPart;

	local_numPartDecoded = numPartDecoded;
	local_numPart = numPart;
	local_numPart = numPart;
	result = local_numPartDecoded < local_numPart && local_numPart != 2;
	return result;
}

static void getCuInfo_launch() {

	u16 tmp_CUInfo;
	u16 tmp_CUInfo0;
	u8 local_cuWidth;
	u16 tmp_PU_SIZE_TO_NB_BLK_TO_CLIP;
	u16 local_nbBlkToClip;
	i32 j;
	i32 i;
	u16 tmp_CUInfo1;
	i32 i0;

	tmp_CUInfo = tokens_CUInfo[(index_CUInfo + (0)) % SIZE_CUInfo];
	cuMode = tmp_CUInfo;
	tmp_CUInfo0 = tokens_CUInfo[(index_CUInfo + (3)) % SIZE_CUInfo];
	cuWidth = tmp_CUInfo0;
	local_cuWidth = cuWidth;
	tmp_PU_SIZE_TO_NB_BLK_TO_CLIP = PU_SIZE_TO_NB_BLK_TO_CLIP[local_cuWidth >> 2];
	nbBlkToClip = tmp_PU_SIZE_TO_NB_BLK_TO_CLIP;
	local_nbBlkToClip = nbBlkToClip;
	nbBlk = local_nbBlkToClip;
	idxBlk = 0;
	j = 0;
	while (j <= 3) {
		i = 3;
		while (i <= 4) {
			tmp_CUInfo1 = tokens_CUInfo[(index_CUInfo + (i)) % SIZE_CUInfo];
			cuSize[j][i - 3] = tmp_CUInfo1 / 4;
			i = i + 1;
		}
		j = j + 1;
	}
	i0 = 0;
	while (i0 <= 1) {
		cuOff[0][i0] = 0;
		i0 = i0 + 1;
	}

	// Update ports indexes
	index_CUInfo += 5;
	read_end_CUInfo();

	rate_CUInfo += 5;
}
static void getCuInfo_launch_aligned() {

	u16 tmp_CUInfo;
	u16 tmp_CUInfo0;
	u8 local_cuWidth;
	u16 tmp_PU_SIZE_TO_NB_BLK_TO_CLIP;
	u16 local_nbBlkToClip;
	i32 j;
	i32 i;
	u16 tmp_CUInfo1;
	i32 i0;

	tmp_CUInfo = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (0)];
	cuMode = tmp_CUInfo;
	tmp_CUInfo0 = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (3)];
	cuWidth = tmp_CUInfo0;
	local_cuWidth = cuWidth;
	tmp_PU_SIZE_TO_NB_BLK_TO_CLIP = PU_SIZE_TO_NB_BLK_TO_CLIP[local_cuWidth >> 2];
	nbBlkToClip = tmp_PU_SIZE_TO_NB_BLK_TO_CLIP;
	local_nbBlkToClip = nbBlkToClip;
	nbBlk = local_nbBlkToClip;
	idxBlk = 0;
	j = 0;
	while (j <= 3) {
		i = 3;
		while (i <= 4) {
			tmp_CUInfo1 = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (i)];
			cuSize[j][i - 3] = tmp_CUInfo1 / 4;
			i = i + 1;
		}
		j = j + 1;
	}
	i0 = 0;
	while (i0 <= 1) {
		cuOff[0][i0] = 0;
		i0 = i0 + 1;
	}

	// Update ports indexes
	index_CUInfo += 5;
	read_end_CUInfo();

	rate_CUInfo += 5;
}
static i32 isSchedulable_getCuInfo_launch_numPart2() {
	i32 result;
	u8 local_numPartDecoded;
	u8 local_numPart;

	local_numPartDecoded = numPartDecoded;
	local_numPart = numPart;
	local_numPart = numPart;
	result = local_numPartDecoded < local_numPart && local_numPart == 2;
	return result;
}

static void getCuInfo_launch_numPart2() {

	u16 tmp_CUInfo;
	u32 j;
	u32 i;
	u16 tmp_CUInfo0;
	u16 tmp_CUInfo1;
	u16 tmp_CUInfo2;
	i32 tmp_max;
	u8 local_cuWidth;
	u16 tmp_CUInfo3;
	u16 tmp_CUInfo4;
	i32 tmp_min;
	u16 tmp_PU_SIZE_TO_NB_BLK_TO_CLIP;
	u8 local_partMode;
	u8 local_PART_2NxN;
	u8 local_PART_2NxnU;
	u8 local_PART_2NxnD;
	u16 tmp_CUInfo5;
	u16 tmp_CUInfo6;

	tmp_CUInfo = tokens_CUInfo[(index_CUInfo + (0)) % SIZE_CUInfo];
	cuMode = tmp_CUInfo;
	j = 0;
	while (j <= 1) {
		i = 3;
		while (i <= 4) {
			tmp_CUInfo0 = tokens_CUInfo[(index_CUInfo + (i + 5 * j)) % SIZE_CUInfo];
			cuSize[j][i - 3] = tmp_CUInfo0 / 4;
			i = i + 1;
		}
		j = j + 1;
	}
	tmp_CUInfo1 = tokens_CUInfo[(index_CUInfo + (3)) % SIZE_CUInfo];
	tmp_CUInfo2 = tokens_CUInfo[(index_CUInfo + (4)) % SIZE_CUInfo];
	tmp_max = HevcDecoder_SelectCU_max(tmp_CUInfo1, tmp_CUInfo2);
	cuWidth = tmp_max;
	local_cuWidth = cuWidth;
	local_cuWidth = cuWidth;
	nbBlk = local_cuWidth * local_cuWidth / 16;
	idxBlk = 0;
	tmp_CUInfo3 = tokens_CUInfo[(index_CUInfo + (3)) % SIZE_CUInfo];
	tmp_CUInfo4 = tokens_CUInfo[(index_CUInfo + (4)) % SIZE_CUInfo];
	tmp_min = HevcDecoder_SelectCU_min(tmp_CUInfo3, tmp_CUInfo4);
	tmp_PU_SIZE_TO_NB_BLK_TO_CLIP = PU_SIZE_TO_NB_BLK_TO_CLIP[tmp_min >> 2];
	nbBlkToClip = tmp_PU_SIZE_TO_NB_BLK_TO_CLIP;
	local_partMode = partMode;
	local_PART_2NxN = HevcDecoder_SelectCU_PART_2NxN;
	local_partMode = partMode;
	local_PART_2NxnU = HevcDecoder_SelectCU_PART_2NxnU;
	local_partMode = partMode;
	local_PART_2NxnD = HevcDecoder_SelectCU_PART_2NxnD;
	if (local_partMode == local_PART_2NxN || local_partMode == local_PART_2NxnU || local_partMode == local_PART_2NxnD) {
		cuOff[1][0] = 0;
		tmp_CUInfo5 = tokens_CUInfo[(index_CUInfo + (4)) % SIZE_CUInfo];
		cuOff[1][1] = tmp_CUInfo5 / 4;
	} else {
		tmp_CUInfo6 = tokens_CUInfo[(index_CUInfo + (3)) % SIZE_CUInfo];
		cuOff[1][0] = tmp_CUInfo6 / 4;
		cuOff[1][1] = 0;
	}
	numPartDecoded = 0;

	// Update ports indexes
	index_CUInfo += 10;
	read_end_CUInfo();

	rate_CUInfo += 10;
}
static void getCuInfo_launch_numPart2_aligned() {

	u16 tmp_CUInfo;
	u32 j;
	u32 i;
	u16 tmp_CUInfo0;
	u16 tmp_CUInfo1;
	u16 tmp_CUInfo2;
	i32 tmp_max;
	u8 local_cuWidth;
	u16 tmp_CUInfo3;
	u16 tmp_CUInfo4;
	i32 tmp_min;
	u16 tmp_PU_SIZE_TO_NB_BLK_TO_CLIP;
	u8 local_partMode;
	u8 local_PART_2NxN;
	u8 local_PART_2NxnU;
	u8 local_PART_2NxnD;
	u16 tmp_CUInfo5;
	u16 tmp_CUInfo6;

	tmp_CUInfo = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (0)];
	cuMode = tmp_CUInfo;
	j = 0;
	while (j <= 1) {
		i = 3;
		while (i <= 4) {
			tmp_CUInfo0 = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (i + 5 * j)];
			cuSize[j][i - 3] = tmp_CUInfo0 / 4;
			i = i + 1;
		}
		j = j + 1;
	}
	tmp_CUInfo1 = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (3)];
	tmp_CUInfo2 = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (4)];
	tmp_max = HevcDecoder_SelectCU_max(tmp_CUInfo1, tmp_CUInfo2);
	cuWidth = tmp_max;
	local_cuWidth = cuWidth;
	local_cuWidth = cuWidth;
	nbBlk = local_cuWidth * local_cuWidth / 16;
	idxBlk = 0;
	tmp_CUInfo3 = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (3)];
	tmp_CUInfo4 = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (4)];
	tmp_min = HevcDecoder_SelectCU_min(tmp_CUInfo3, tmp_CUInfo4);
	tmp_PU_SIZE_TO_NB_BLK_TO_CLIP = PU_SIZE_TO_NB_BLK_TO_CLIP[tmp_min >> 2];
	nbBlkToClip = tmp_PU_SIZE_TO_NB_BLK_TO_CLIP;
	local_partMode = partMode;
	local_PART_2NxN = HevcDecoder_SelectCU_PART_2NxN;
	local_partMode = partMode;
	local_PART_2NxnU = HevcDecoder_SelectCU_PART_2NxnU;
	local_partMode = partMode;
	local_PART_2NxnD = HevcDecoder_SelectCU_PART_2NxnD;
	if (local_partMode == local_PART_2NxN || local_partMode == local_PART_2NxnU || local_partMode == local_PART_2NxnD) {
		cuOff[1][0] = 0;
		tmp_CUInfo5 = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (4)];
		cuOff[1][1] = tmp_CUInfo5 / 4;
	} else {
		tmp_CUInfo6 = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (3)];
		cuOff[1][0] = tmp_CUInfo6 / 4;
		cuOff[1][1] = 0;
	}
	numPartDecoded = 0;

	// Update ports indexes
	index_CUInfo += 10;
	read_end_CUInfo();

	rate_CUInfo += 10;
}
static i32 isSchedulable_getCuInfo_done() {
	i32 result;
	u8 local_numPartDecoded;
	u8 local_numPart;

	local_numPartDecoded = numPartDecoded;
	local_numPart = numPart;
	result = local_numPartDecoded == local_numPart;
	return result;
}

static void getCuInfo_done() {



	// Update ports indexes

}
static i32 isSchedulable_getCuMode_isIntra() {
	i32 result;
	u8 local_cuMode;
	u8 local_INTRA;

	local_cuMode = cuMode;
	local_INTRA = HevcDecoder_SelectCU_INTRA;
	result = local_cuMode == local_INTRA;
	return result;
}

static void getCuMode_isIntra() {

	u8 local_numPartDecoded;

	local_numPartDecoded = numPartDecoded;
	numPartDecoded = local_numPartDecoded + 1;

	// Update ports indexes

}
static i32 isSchedulable_getCuMode_isInter() {
	i32 result;
	u8 local_cuMode;
	u8 local_INTER;
	u8 local_SKIP;

	local_cuMode = cuMode;
	local_INTER = HevcDecoder_SelectCU_INTER;
	local_cuMode = cuMode;
	local_SKIP = HevcDecoder_SelectCU_SKIP;
	result = local_cuMode == local_INTER || local_cuMode == local_SKIP;
	return result;
}

static void getCuMode_isInter() {


	xIdx = 0;
	yIdx = 0;
	idxBlkInterpred = 0;

	// Update ports indexes

}
static i32 isSchedulable_getCuMode_isOther() {
	i32 result;
	u8 local_cuMode;
	u8 local_OTHER;

	local_cuMode = cuMode;
	local_OTHER = HevcDecoder_SelectCU_OTHER;
	result = local_cuMode == local_OTHER;
	return result;
}

static void getCuMode_isOther() {

	u8 local_numPartDecoded;

	local_numPartDecoded = numPartDecoded;
	numPartDecoded = local_numPartDecoded + 1;

	// Update ports indexes

}
static i32 isSchedulable_getCuSample_isIntra() {
	i32 result;

	result = 1;
	return result;
}

static void getCuSample_isIntra() {

	u32 sampIdx;
	u8 local_SCU_SIZE;
	u8 tmp_IntraSample;
	i16 tmp_ResidualSample;
	i32 tmp_clip_i32;
	u16 local_idxBlk;

	sampIdx = 0;
	local_SCU_SIZE = SCU_SIZE;
	while (sampIdx <= local_SCU_SIZE - 1) {
		tmp_IntraSample = tokens_IntraSample[(index_IntraSample + (sampIdx)) % SIZE_IntraSample];
		tmp_ResidualSample = tokens_ResidualSample[(index_ResidualSample + (sampIdx)) % SIZE_ResidualSample];
		tmp_clip_i32 = HevcDecoder_SelectCU_clip_i32(tmp_IntraSample + tmp_ResidualSample, 0, 255);
		tokens_Sample[(index_Sample + (sampIdx)) % SIZE_Sample] = tmp_clip_i32;
		sampIdx = sampIdx + 1;
	}
	local_idxBlk = idxBlk;
	idxBlk = local_idxBlk + 1;

	// Update ports indexes
	index_IntraSample += 24;
	read_end_IntraSample();
	index_ResidualSample += 24;
	read_end_ResidualSample();
	index_Sample += 24;
	write_end_Sample();

	rate_IntraSample += 24;
	rate_ResidualSample += 24;
}
static void getCuSample_isIntra_aligned() {

	u32 sampIdx;
	u8 local_SCU_SIZE;
	u8 tmp_IntraSample;
	i16 tmp_ResidualSample;
	i32 tmp_clip_i32;
	u16 local_idxBlk;

	sampIdx = 0;
	local_SCU_SIZE = SCU_SIZE;
	while (sampIdx <= local_SCU_SIZE - 1) {
		tmp_IntraSample = tokens_IntraSample[(index_IntraSample % SIZE_IntraSample) + (sampIdx)];
		tmp_ResidualSample = tokens_ResidualSample[(index_ResidualSample % SIZE_ResidualSample) + (sampIdx)];
		tmp_clip_i32 = HevcDecoder_SelectCU_clip_i32(tmp_IntraSample + tmp_ResidualSample, 0, 255);
		tokens_Sample[(index_Sample % SIZE_Sample) + (sampIdx)] = tmp_clip_i32;
		sampIdx = sampIdx + 1;
	}
	local_idxBlk = idxBlk;
	idxBlk = local_idxBlk + 1;

	// Update ports indexes
	index_IntraSample += 24;
	read_end_IntraSample();
	index_ResidualSample += 24;
	read_end_ResidualSample();
	index_Sample += 24;
	write_end_Sample();

	rate_IntraSample += 24;
	rate_ResidualSample += 24;
}
static i32 isSchedulable_getCuSample_isInter() {
	i32 result;
	u16 local_idxBlkInterpred;
	u16 local_nbBlk;

	local_idxBlkInterpred = idxBlkInterpred;
	local_nbBlk = nbBlk;
	result = local_idxBlkInterpred < local_nbBlk;
	return result;
}

static void getCuSample_isInter() {

	u16 blkAddr[2];
	u8 local_numPartDecoded;
	u32 xOff;
	u32 yOff;
	u32 blkIdx;
	u8 local_xIdx;
	u8 local_yIdx;
	i32 i;
	u8 local_SCU_SIZE;
	u8 tmp_InterSample;
	u8 tmp_cuSize;
	u8 tmp_cuSize0;
	u16 local_idxBlkInterpred;

	local_numPartDecoded = numPartDecoded;
	xOff = cuOff[local_numPartDecoded][0];
	local_numPartDecoded = numPartDecoded;
	yOff = cuOff[local_numPartDecoded][1];
	local_xIdx = xIdx;
	blkAddr[0] = local_xIdx + xOff;
	local_yIdx = yIdx;
	blkAddr[1] = local_yIdx + yOff;
	blkIdx = HevcDecoder_SelectCU_absCoordInBlkToZScan(blkAddr);
	i = 0;
	local_SCU_SIZE = SCU_SIZE;
	while (i <= local_SCU_SIZE - 1) {
		tmp_InterSample = tokens_InterSample[(index_InterSample + (i)) % SIZE_InterSample];
		predSamp[24 * blkIdx + i] = tmp_InterSample;
		i = i + 1;
	}
	sampGot[blkIdx] = 1;
	local_xIdx = xIdx;
	xIdx = local_xIdx + 1;
	local_xIdx = xIdx;
	local_numPartDecoded = numPartDecoded;
	tmp_cuSize = cuSize[local_numPartDecoded][0];
	if (local_xIdx == tmp_cuSize) {
		xIdx = 0;
		local_yIdx = yIdx;
		yIdx = local_yIdx + 1;
		local_yIdx = yIdx;
		local_numPartDecoded = numPartDecoded;
		tmp_cuSize0 = cuSize[local_numPartDecoded][1];
		if (local_yIdx == tmp_cuSize0) {
			yIdx = 0;
			local_numPartDecoded = numPartDecoded;
			numPartDecoded = local_numPartDecoded + 1;
		}
	}
	local_idxBlkInterpred = idxBlkInterpred;
	idxBlkInterpred = local_idxBlkInterpred + 1;

	// Update ports indexes
	index_InterSample += 24;
	read_end_InterSample();

	rate_InterSample += 24;
}
static void getCuSample_isInter_aligned() {

	u16 blkAddr[2];
	u8 local_numPartDecoded;
	u32 xOff;
	u32 yOff;
	u32 blkIdx;
	u8 local_xIdx;
	u8 local_yIdx;
	i32 i;
	u8 local_SCU_SIZE;
	u8 tmp_InterSample;
	u8 tmp_cuSize;
	u8 tmp_cuSize0;
	u16 local_idxBlkInterpred;

	local_numPartDecoded = numPartDecoded;
	xOff = cuOff[local_numPartDecoded][0];
	local_numPartDecoded = numPartDecoded;
	yOff = cuOff[local_numPartDecoded][1];
	local_xIdx = xIdx;
	blkAddr[0] = local_xIdx + xOff;
	local_yIdx = yIdx;
	blkAddr[1] = local_yIdx + yOff;
	blkIdx = HevcDecoder_SelectCU_absCoordInBlkToZScan(blkAddr);
	i = 0;
	local_SCU_SIZE = SCU_SIZE;
	while (i <= local_SCU_SIZE - 1) {
		tmp_InterSample = tokens_InterSample[(index_InterSample % SIZE_InterSample) + (i)];
		predSamp[24 * blkIdx + i] = tmp_InterSample;
		i = i + 1;
	}
	sampGot[blkIdx] = 1;
	local_xIdx = xIdx;
	xIdx = local_xIdx + 1;
	local_xIdx = xIdx;
	local_numPartDecoded = numPartDecoded;
	tmp_cuSize = cuSize[local_numPartDecoded][0];
	if (local_xIdx == tmp_cuSize) {
		xIdx = 0;
		local_yIdx = yIdx;
		yIdx = local_yIdx + 1;
		local_yIdx = yIdx;
		local_numPartDecoded = numPartDecoded;
		tmp_cuSize0 = cuSize[local_numPartDecoded][1];
		if (local_yIdx == tmp_cuSize0) {
			yIdx = 0;
			local_numPartDecoded = numPartDecoded;
			numPartDecoded = local_numPartDecoded + 1;
		}
	}
	local_idxBlkInterpred = idxBlkInterpred;
	idxBlkInterpred = local_idxBlkInterpred + 1;

	// Update ports indexes
	index_InterSample += 24;
	read_end_InterSample();

	rate_InterSample += 24;
}
static i32 isSchedulable_chekNbBlkToClip_is1() {
	i32 result;
	u16 local_nbBlkToClip;

	local_nbBlkToClip = nbBlkToClip;
	result = local_nbBlkToClip == 1;
	return result;
}

static void chekNbBlkToClip_is1() {



	// Update ports indexes

}
static i32 isSchedulable_chekNbBlkToClip_is4() {
	i32 result;
	u16 local_nbBlkToClip;

	local_nbBlkToClip = nbBlkToClip;
	result = local_nbBlkToClip == 4;
	return result;
}

static void chekNbBlkToClip_is4() {



	// Update ports indexes

}
static i32 isSchedulable_chekNbBlkToClip_is16() {
	i32 result;
	u16 local_nbBlkToClip;

	local_nbBlkToClip = nbBlkToClip;
	result = local_nbBlkToClip == 16;
	return result;
}

static void chekNbBlkToClip_is16() {



	// Update ports indexes

}
static i32 isSchedulable_chekNbBlkToClip_is64() {
	i32 result;
	u16 local_nbBlkToClip;

	local_nbBlkToClip = nbBlkToClip;
	result = local_nbBlkToClip == 64;
	return result;
}

static void chekNbBlkToClip_is64() {



	// Update ports indexes

}
static i32 isSchedulable_chekNbBlkToClip_is256() {
	i32 result;
	u16 local_nbBlkToClip;

	local_nbBlkToClip = nbBlkToClip;
	result = local_nbBlkToClip == 256;
	return result;
}

static void chekNbBlkToClip_is256() {



	// Update ports indexes

}
static i32 isSchedulable_getInterRes_get1Blk() {
	i32 result;
	u16 local_idxBlk;
	i32 tmp_sampGot;

	local_idxBlk = idxBlk;
	tmp_sampGot = sampGot[local_idxBlk];
	result = tmp_sampGot;
	return result;
}

static void getInterRes_get1Blk() {

	i32 i;
	u8 local_SCU_SIZE;
	u16 local_idxBlk;
	u8 tmp_predSamp;
	i16 tmp_ResidualSample;
	i32 tmp_clip_i32;

	i = 0;
	local_SCU_SIZE = SCU_SIZE;
	while (i <= local_SCU_SIZE - 1) {
		local_idxBlk = idxBlk;
		tmp_predSamp = predSamp[24 * local_idxBlk + i];
		tmp_ResidualSample = tokens_ResidualSample[(index_ResidualSample + (i)) % SIZE_ResidualSample];
		tmp_clip_i32 = HevcDecoder_SelectCU_clip_i32(tmp_predSamp + tmp_ResidualSample, 0, 255);
		tokens_Sample[(index_Sample + (i)) % SIZE_Sample] = tmp_clip_i32;
		i = i + 1;
	}
	local_idxBlk = idxBlk;
	idxBlk = local_idxBlk + 1;

	// Update ports indexes
	index_ResidualSample += 24;
	read_end_ResidualSample();
	index_Sample += 24;
	write_end_Sample();

	rate_ResidualSample += 24;
}
static void getInterRes_get1Blk_aligned() {

	i32 i;
	u8 local_SCU_SIZE;
	u16 local_idxBlk;
	u8 tmp_predSamp;
	i16 tmp_ResidualSample;
	i32 tmp_clip_i32;

	i = 0;
	local_SCU_SIZE = SCU_SIZE;
	while (i <= local_SCU_SIZE - 1) {
		local_idxBlk = idxBlk;
		tmp_predSamp = predSamp[24 * local_idxBlk + i];
		tmp_ResidualSample = tokens_ResidualSample[(index_ResidualSample % SIZE_ResidualSample) + (i)];
		tmp_clip_i32 = HevcDecoder_SelectCU_clip_i32(tmp_predSamp + tmp_ResidualSample, 0, 255);
		tokens_Sample[(index_Sample % SIZE_Sample) + (i)] = tmp_clip_i32;
		i = i + 1;
	}
	local_idxBlk = idxBlk;
	idxBlk = local_idxBlk + 1;

	// Update ports indexes
	index_ResidualSample += 24;
	read_end_ResidualSample();
	index_Sample += 24;
	write_end_Sample();

	rate_ResidualSample += 24;
}
static i32 isSchedulable_getInterRes_get4Blk() {
	i32 result;
	u16 local_idxBlk;
	i32 tmp_sampGot;

	local_idxBlk = idxBlk;
	tmp_sampGot = sampGot[local_idxBlk + 3];
	result = tmp_sampGot;
	return result;
}

static void getInterRes_get4Blk() {

	i32 i;
	u8 local_SCU_SIZE;
	u16 local_idxBlk;
	u8 tmp_predSamp;
	i16 tmp_ResidualSample;
	i32 tmp_clip_i32;

	i = 0;
	local_SCU_SIZE = SCU_SIZE;
	while (i <= local_SCU_SIZE * 4 - 1) {
		local_idxBlk = idxBlk;
		tmp_predSamp = predSamp[24 * local_idxBlk + i];
		tmp_ResidualSample = tokens_ResidualSample[(index_ResidualSample + (i)) % SIZE_ResidualSample];
		tmp_clip_i32 = HevcDecoder_SelectCU_clip_i32(tmp_predSamp + tmp_ResidualSample, 0, 255);
		tokens_Sample[(index_Sample + (i)) % SIZE_Sample] = tmp_clip_i32;
		i = i + 1;
	}
	local_idxBlk = idxBlk;
	idxBlk = local_idxBlk + 4;

	// Update ports indexes
	index_ResidualSample += 96;
	read_end_ResidualSample();
	index_Sample += 96;
	write_end_Sample();

	rate_ResidualSample += 96;
}
static void getInterRes_get4Blk_aligned() {

	i32 i;
	u8 local_SCU_SIZE;
	u16 local_idxBlk;
	u8 tmp_predSamp;
	i16 tmp_ResidualSample;
	i32 tmp_clip_i32;

	i = 0;
	local_SCU_SIZE = SCU_SIZE;
	while (i <= local_SCU_SIZE * 4 - 1) {
		local_idxBlk = idxBlk;
		tmp_predSamp = predSamp[24 * local_idxBlk + i];
		tmp_ResidualSample = tokens_ResidualSample[(index_ResidualSample % SIZE_ResidualSample) + (i)];
		tmp_clip_i32 = HevcDecoder_SelectCU_clip_i32(tmp_predSamp + tmp_ResidualSample, 0, 255);
		tokens_Sample[(index_Sample % SIZE_Sample) + (i)] = tmp_clip_i32;
		i = i + 1;
	}
	local_idxBlk = idxBlk;
	idxBlk = local_idxBlk + 4;

	// Update ports indexes
	index_ResidualSample += 96;
	read_end_ResidualSample();
	index_Sample += 96;
	write_end_Sample();

	rate_ResidualSample += 96;
}
static i32 isSchedulable_getInterRes_get16Blk() {
	i32 result;
	u16 local_idxBlk;
	i32 tmp_sampGot;

	local_idxBlk = idxBlk;
	tmp_sampGot = sampGot[local_idxBlk + 15];
	result = tmp_sampGot;
	return result;
}

static void getInterRes_get16Blk() {

	i32 i;
	u8 local_SCU_SIZE;
	u16 local_idxBlk;
	u8 tmp_predSamp;
	i16 tmp_ResidualSample;
	i32 tmp_clip_i32;

	i = 0;
	local_SCU_SIZE = SCU_SIZE;
	while (i <= local_SCU_SIZE * 16 - 1) {
		local_idxBlk = idxBlk;
		tmp_predSamp = predSamp[24 * local_idxBlk + i];
		tmp_ResidualSample = tokens_ResidualSample[(index_ResidualSample + (i)) % SIZE_ResidualSample];
		tmp_clip_i32 = HevcDecoder_SelectCU_clip_i32(tmp_predSamp + tmp_ResidualSample, 0, 255);
		tokens_Sample[(index_Sample + (i)) % SIZE_Sample] = tmp_clip_i32;
		i = i + 1;
	}
	local_idxBlk = idxBlk;
	idxBlk = local_idxBlk + 16;

	// Update ports indexes
	index_ResidualSample += 384;
	read_end_ResidualSample();
	index_Sample += 384;
	write_end_Sample();

	rate_ResidualSample += 384;
}
static void getInterRes_get16Blk_aligned() {

	i32 i;
	u8 local_SCU_SIZE;
	u16 local_idxBlk;
	u8 tmp_predSamp;
	i16 tmp_ResidualSample;
	i32 tmp_clip_i32;

	i = 0;
	local_SCU_SIZE = SCU_SIZE;
	while (i <= local_SCU_SIZE * 16 - 1) {
		local_idxBlk = idxBlk;
		tmp_predSamp = predSamp[24 * local_idxBlk + i];
		tmp_ResidualSample = tokens_ResidualSample[(index_ResidualSample % SIZE_ResidualSample) + (i)];
		tmp_clip_i32 = HevcDecoder_SelectCU_clip_i32(tmp_predSamp + tmp_ResidualSample, 0, 255);
		tokens_Sample[(index_Sample % SIZE_Sample) + (i)] = tmp_clip_i32;
		i = i + 1;
	}
	local_idxBlk = idxBlk;
	idxBlk = local_idxBlk + 16;

	// Update ports indexes
	index_ResidualSample += 384;
	read_end_ResidualSample();
	index_Sample += 384;
	write_end_Sample();

	rate_ResidualSample += 384;
}
static i32 isSchedulable_getInterRes_get64Blk() {
	i32 result;
	u16 local_idxBlk;
	i32 tmp_sampGot;

	local_idxBlk = idxBlk;
	tmp_sampGot = sampGot[local_idxBlk + 63];
	result = tmp_sampGot;
	return result;
}

static void getInterRes_get64Blk() {

	i32 i;
	u8 local_SCU_SIZE;
	u16 local_idxBlk;
	u8 tmp_predSamp;
	i16 tmp_ResidualSample;
	i32 tmp_clip_i32;

	i = 0;
	local_SCU_SIZE = SCU_SIZE;
	while (i <= local_SCU_SIZE * 64 - 1) {
		local_idxBlk = idxBlk;
		tmp_predSamp = predSamp[24 * local_idxBlk + i];
		tmp_ResidualSample = tokens_ResidualSample[(index_ResidualSample + (i)) % SIZE_ResidualSample];
		tmp_clip_i32 = HevcDecoder_SelectCU_clip_i32(tmp_predSamp + tmp_ResidualSample, 0, 255);
		tokens_Sample[(index_Sample + (i)) % SIZE_Sample] = tmp_clip_i32;
		i = i + 1;
	}
	local_idxBlk = idxBlk;
	idxBlk = local_idxBlk + 64;

	// Update ports indexes
	index_ResidualSample += 1536;
	read_end_ResidualSample();
	index_Sample += 1536;
	write_end_Sample();

	rate_ResidualSample += 1536;
}
static void getInterRes_get64Blk_aligned() {

	i32 i;
	u8 local_SCU_SIZE;
	u16 local_idxBlk;
	u8 tmp_predSamp;
	i16 tmp_ResidualSample;
	i32 tmp_clip_i32;

	i = 0;
	local_SCU_SIZE = SCU_SIZE;
	while (i <= local_SCU_SIZE * 64 - 1) {
		local_idxBlk = idxBlk;
		tmp_predSamp = predSamp[24 * local_idxBlk + i];
		tmp_ResidualSample = tokens_ResidualSample[(index_ResidualSample % SIZE_ResidualSample) + (i)];
		tmp_clip_i32 = HevcDecoder_SelectCU_clip_i32(tmp_predSamp + tmp_ResidualSample, 0, 255);
		tokens_Sample[(index_Sample % SIZE_Sample) + (i)] = tmp_clip_i32;
		i = i + 1;
	}
	local_idxBlk = idxBlk;
	idxBlk = local_idxBlk + 64;

	// Update ports indexes
	index_ResidualSample += 1536;
	read_end_ResidualSample();
	index_Sample += 1536;
	write_end_Sample();

	rate_ResidualSample += 1536;
}
static i32 isSchedulable_getCuSample_done() {
	i32 result;
	u16 local_idxBlk;
	u16 local_nbBlk;

	local_idxBlk = idxBlk;
	local_nbBlk = nbBlk;
	result = local_idxBlk == local_nbBlk;
	return result;
}

static void getCuSample_done() {

	i32 i;
	u16 local_nbBlk;

	idxBlk = 0;
	i = 0;
	local_nbBlk = nbBlk;
	while (i <= local_nbBlk - 1) {
		sampGot[i] = 0;
		i = i + 1;
	}

	// Update ports indexes

}

////////////////////////////////////////////////////////////////////////////////
// Initializes
static i32 isSchedulable_untagged_0() {
	i32 result;

	result = 1;
	return result;
}

static void untagged_0() {

	i32 i;

	i = 0;
	while (i <= 511) {
		sampGot[i] = 0;
		i = i + 1;
	}

	// Update ports indexes

}

void HevcDecoder_SelectCU_initialize(schedinfo_t *si) {
	int i = 0;
	write_Sample();
	/* Set initial state to current FSM state */
	_FSM_state = my_state_GetPartMode;
	if(isSchedulable_untagged_0()) {
		untagged_0();
	}
finished:
	write_end_Sample();
	return;
}

////////////////////////////////////////////////////////////////////////////////
// Action scheduler

void HevcDecoder_SelectCU_scheduler(schedinfo_t *si) {
	int i = 0;

	read_CUInfo();
	read_InterSample();
	read_IntraSample();
	read_PartMode();
	read_ResidualSample();
	write_Sample();

	// jump to FSM state
	switch (_FSM_state) {
	case my_state_CheckNbBlkToClip:
		goto l_CheckNbBlkToClip;
	case my_state_GetCuInfo:
		goto l_GetCuInfo;
	case my_state_GetCuMode:
		goto l_GetCuMode;
	case my_state_GetCuSampleInter16Blk:
		goto l_GetCuSampleInter16Blk;
	case my_state_GetCuSampleInter1Blk:
		goto l_GetCuSampleInter1Blk;
	case my_state_GetCuSampleInter256Blk:
		goto l_GetCuSampleInter256Blk;
	case my_state_GetCuSampleInter4Blk:
		goto l_GetCuSampleInter4Blk;
	case my_state_GetCuSampleInter64Blk:
		goto l_GetCuSampleInter64Blk;
	case my_state_GetCuSampleIntra:
		goto l_GetCuSampleIntra;
	case my_state_GetPartMode:
		goto l_GetPartMode;
	default:
		printf("unknown state in HevcDecoder_SelectCU.c : %s\n", stateNames[_FSM_state]);
		exit(1);
	}

	// FSM transitions
l_CheckNbBlkToClip:
	if (isSchedulable_chekNbBlkToClip_is64()) {
		chekNbBlkToClip_is64();
		i++;
		goto l_GetCuSampleInter64Blk;
	} else if (isSchedulable_chekNbBlkToClip_is16()) {
		chekNbBlkToClip_is16();
		i++;
		goto l_GetCuSampleInter16Blk;
	} else if (isSchedulable_chekNbBlkToClip_is4()) {
		chekNbBlkToClip_is4();
		i++;
		goto l_GetCuSampleInter4Blk;
	} else if (isSchedulable_chekNbBlkToClip_is256()) {
		chekNbBlkToClip_is256();
		i++;
		goto l_GetCuSampleInter256Blk;
	} else if (isSchedulable_chekNbBlkToClip_is1()) {
		chekNbBlkToClip_is1();
		i++;
		goto l_GetCuSampleInter1Blk;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_CheckNbBlkToClip;
		goto finished;
	}
l_GetCuInfo:
	if (numTokens_CUInfo - index_CUInfo >= 5 && isSchedulable_getCuInfo_launch()) {
		{
			int isAligned = 1;
			isAligned &= ((index_CUInfo % SIZE_CUInfo) < ((index_CUInfo + 5) % SIZE_CUInfo));
			if (isAligned) {
				getCuInfo_launch_aligned();
			} else {
				getCuInfo_launch();
			}
		}
		i++;
		goto l_GetCuMode;
	} else if (numTokens_CUInfo - index_CUInfo >= 10 && isSchedulable_getCuInfo_launch_numPart2()) {
		{
			int isAligned = 1;
			isAligned &= ((index_CUInfo % SIZE_CUInfo) < ((index_CUInfo + 10) % SIZE_CUInfo));
			if (isAligned) {
				getCuInfo_launch_numPart2_aligned();
			} else {
				getCuInfo_launch_numPart2();
			}
		}
		i++;
		goto l_GetCuMode;
	} else if (isSchedulable_getCuInfo_done()) {
		getCuInfo_done();
		i++;
		goto l_GetPartMode;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetCuInfo;
		goto finished;
	}
l_GetCuMode:
	if (isSchedulable_getCuMode_isIntra()) {
		getCuMode_isIntra();
		i++;
		goto l_GetCuSampleIntra;
	} else if (isSchedulable_getCuMode_isInter()) {
		getCuMode_isInter();
		i++;
		goto l_CheckNbBlkToClip;
	} else if (isSchedulable_getCuMode_isOther()) {
		getCuMode_isOther();
		i++;
		goto l_GetCuInfo;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetCuMode;
		goto finished;
	}
l_GetCuSampleInter16Blk:
	if (isSchedulable_getCuSample_done()) {
		getCuSample_done();
		i++;
		goto l_GetCuInfo;
	} else if (numTokens_ResidualSample - index_ResidualSample >= 384 && isSchedulable_getInterRes_get16Blk()) {
		int stop = 0;
		if (384 > SIZE_Sample - index_Sample + HevcDecoder_SelectCU_Sample->read_inds[0]) {
			stop = 1;
		}
		if (384 > SIZE_Sample - index_Sample + HevcDecoder_SelectCU_Sample->read_inds[1]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_GetCuSampleInter16Blk;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		{
			int isAligned = 1;
			isAligned &= ((index_ResidualSample % SIZE_ResidualSample) < ((index_ResidualSample + 384) % SIZE_ResidualSample));
			isAligned &= ((index_Sample % SIZE_Sample) < ((index_Sample + 384) % SIZE_Sample));
			if (isAligned) {
				getInterRes_get16Blk_aligned();
			} else {
				getInterRes_get16Blk();
			}
		}
		i++;
		goto l_GetCuSampleInter16Blk;
	} else if (numTokens_InterSample - index_InterSample >= 24 && isSchedulable_getCuSample_isInter()) {
		{
			int isAligned = 1;
			isAligned &= ((index_InterSample % SIZE_InterSample) < ((index_InterSample + 24) % SIZE_InterSample));
			if (isAligned) {
				getCuSample_isInter_aligned();
			} else {
				getCuSample_isInter();
			}
		}
		i++;
		goto l_GetCuSampleInter16Blk;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetCuSampleInter16Blk;
		goto finished;
	}
l_GetCuSampleInter1Blk:
	if (isSchedulable_getCuSample_done()) {
		getCuSample_done();
		i++;
		goto l_GetCuInfo;
	} else if (numTokens_ResidualSample - index_ResidualSample >= 24 && isSchedulable_getInterRes_get1Blk()) {
		int stop = 0;
		if (24 > SIZE_Sample - index_Sample + HevcDecoder_SelectCU_Sample->read_inds[0]) {
			stop = 1;
		}
		if (24 > SIZE_Sample - index_Sample + HevcDecoder_SelectCU_Sample->read_inds[1]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_GetCuSampleInter1Blk;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		{
			int isAligned = 1;
			isAligned &= ((index_ResidualSample % SIZE_ResidualSample) < ((index_ResidualSample + 24) % SIZE_ResidualSample));
			isAligned &= ((index_Sample % SIZE_Sample) < ((index_Sample + 24) % SIZE_Sample));
			if (isAligned) {
				getInterRes_get1Blk_aligned();
			} else {
				getInterRes_get1Blk();
			}
		}
		i++;
		goto l_GetCuSampleInter1Blk;
	} else if (numTokens_InterSample - index_InterSample >= 24 && isSchedulable_getCuSample_isInter()) {
		{
			int isAligned = 1;
			isAligned &= ((index_InterSample % SIZE_InterSample) < ((index_InterSample + 24) % SIZE_InterSample));
			if (isAligned) {
				getCuSample_isInter_aligned();
			} else {
				getCuSample_isInter();
			}
		}
		i++;
		goto l_GetCuSampleInter1Blk;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetCuSampleInter1Blk;
		goto finished;
	}
l_GetCuSampleInter256Blk:
	if (isSchedulable_getCuSample_done()) {
		getCuSample_done();
		i++;
		goto l_GetCuInfo;
	} else if (numTokens_ResidualSample - index_ResidualSample >= 1536 && isSchedulable_getInterRes_get64Blk()) {
		int stop = 0;
		if (1536 > SIZE_Sample - index_Sample + HevcDecoder_SelectCU_Sample->read_inds[0]) {
			stop = 1;
		}
		if (1536 > SIZE_Sample - index_Sample + HevcDecoder_SelectCU_Sample->read_inds[1]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_GetCuSampleInter256Blk;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		{
			int isAligned = 1;
			isAligned &= ((index_ResidualSample % SIZE_ResidualSample) < ((index_ResidualSample + 1536) % SIZE_ResidualSample));
			isAligned &= ((index_Sample % SIZE_Sample) < ((index_Sample + 1536) % SIZE_Sample));
			if (isAligned) {
				getInterRes_get64Blk_aligned();
			} else {
				getInterRes_get64Blk();
			}
		}
		i++;
		goto l_GetCuSampleInter256Blk;
	} else if (numTokens_InterSample - index_InterSample >= 24 && isSchedulable_getCuSample_isInter()) {
		{
			int isAligned = 1;
			isAligned &= ((index_InterSample % SIZE_InterSample) < ((index_InterSample + 24) % SIZE_InterSample));
			if (isAligned) {
				getCuSample_isInter_aligned();
			} else {
				getCuSample_isInter();
			}
		}
		i++;
		goto l_GetCuSampleInter256Blk;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetCuSampleInter256Blk;
		goto finished;
	}
l_GetCuSampleInter4Blk:
	if (isSchedulable_getCuSample_done()) {
		getCuSample_done();
		i++;
		goto l_GetCuInfo;
	} else if (numTokens_ResidualSample - index_ResidualSample >= 96 && isSchedulable_getInterRes_get4Blk()) {
		int stop = 0;
		if (96 > SIZE_Sample - index_Sample + HevcDecoder_SelectCU_Sample->read_inds[0]) {
			stop = 1;
		}
		if (96 > SIZE_Sample - index_Sample + HevcDecoder_SelectCU_Sample->read_inds[1]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_GetCuSampleInter4Blk;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		{
			int isAligned = 1;
			isAligned &= ((index_ResidualSample % SIZE_ResidualSample) < ((index_ResidualSample + 96) % SIZE_ResidualSample));
			isAligned &= ((index_Sample % SIZE_Sample) < ((index_Sample + 96) % SIZE_Sample));
			if (isAligned) {
				getInterRes_get4Blk_aligned();
			} else {
				getInterRes_get4Blk();
			}
		}
		i++;
		goto l_GetCuSampleInter4Blk;
	} else if (numTokens_InterSample - index_InterSample >= 24 && isSchedulable_getCuSample_isInter()) {
		{
			int isAligned = 1;
			isAligned &= ((index_InterSample % SIZE_InterSample) < ((index_InterSample + 24) % SIZE_InterSample));
			if (isAligned) {
				getCuSample_isInter_aligned();
			} else {
				getCuSample_isInter();
			}
		}
		i++;
		goto l_GetCuSampleInter4Blk;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetCuSampleInter4Blk;
		goto finished;
	}
l_GetCuSampleInter64Blk:
	if (isSchedulable_getCuSample_done()) {
		getCuSample_done();
		i++;
		goto l_GetCuInfo;
	} else if (numTokens_ResidualSample - index_ResidualSample >= 1536 && isSchedulable_getInterRes_get64Blk()) {
		int stop = 0;
		if (1536 > SIZE_Sample - index_Sample + HevcDecoder_SelectCU_Sample->read_inds[0]) {
			stop = 1;
		}
		if (1536 > SIZE_Sample - index_Sample + HevcDecoder_SelectCU_Sample->read_inds[1]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_GetCuSampleInter64Blk;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		{
			int isAligned = 1;
			isAligned &= ((index_ResidualSample % SIZE_ResidualSample) < ((index_ResidualSample + 1536) % SIZE_ResidualSample));
			isAligned &= ((index_Sample % SIZE_Sample) < ((index_Sample + 1536) % SIZE_Sample));
			if (isAligned) {
				getInterRes_get64Blk_aligned();
			} else {
				getInterRes_get64Blk();
			}
		}
		i++;
		goto l_GetCuSampleInter64Blk;
	} else if (numTokens_InterSample - index_InterSample >= 24 && isSchedulable_getCuSample_isInter()) {
		{
			int isAligned = 1;
			isAligned &= ((index_InterSample % SIZE_InterSample) < ((index_InterSample + 24) % SIZE_InterSample));
			if (isAligned) {
				getCuSample_isInter_aligned();
			} else {
				getCuSample_isInter();
			}
		}
		i++;
		goto l_GetCuSampleInter64Blk;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetCuSampleInter64Blk;
		goto finished;
	}
l_GetCuSampleIntra:
	if (isSchedulable_getCuSample_done()) {
		getCuSample_done();
		i++;
		goto l_GetCuInfo;
	} else if (numTokens_IntraSample - index_IntraSample >= 24 && numTokens_ResidualSample - index_ResidualSample >= 24 && isSchedulable_getCuSample_isIntra()) {
		int stop = 0;
		if (24 > SIZE_Sample - index_Sample + HevcDecoder_SelectCU_Sample->read_inds[0]) {
			stop = 1;
		}
		if (24 > SIZE_Sample - index_Sample + HevcDecoder_SelectCU_Sample->read_inds[1]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_GetCuSampleIntra;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		{
			int isAligned = 1;
			isAligned &= ((index_IntraSample % SIZE_IntraSample) < ((index_IntraSample + 24) % SIZE_IntraSample));
			isAligned &= ((index_ResidualSample % SIZE_ResidualSample) < ((index_ResidualSample + 24) % SIZE_ResidualSample));
			isAligned &= ((index_Sample % SIZE_Sample) < ((index_Sample + 24) % SIZE_Sample));
			if (isAligned) {
				getCuSample_isIntra_aligned();
			} else {
				getCuSample_isIntra();
			}
		}
		i++;
		goto l_GetCuSampleIntra;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetCuSampleIntra;
		goto finished;
	}
l_GetPartMode:
	if (numTokens_PartMode - index_PartMode >= 1 && isSchedulable_isNewSlice()) {
		isNewSlice();
		i++;
		goto l_GetPartMode;
	} else if (numTokens_PartMode - index_PartMode >= 1 && isSchedulable_getPartMode()) {
		getPartMode();
		i++;
		goto l_GetCuInfo;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetPartMode;
		goto finished;
	}
finished:
	read_end_CUInfo();
	read_end_InterSample();
	read_end_IntraSample();
	read_end_PartMode();
	read_end_ResidualSample();
	write_end_Sample();
}
