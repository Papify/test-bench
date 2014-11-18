// Source file is "L/RVC/src/org/sc29/wg11/mpegh/part2/main/intra/IntraPrediction.cal"

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
extern actor_t HevcDecoder_IntraPrediction;

////////////////////////////////////////////////////////////////////////////////
// Input FIFOs
extern fifo_u16_t *HevcDecoder_IntraPrediction_CUInfo;
extern fifo_u8_t *HevcDecoder_IntraPrediction_IntraPredMode;
extern fifo_u8_t *HevcDecoder_IntraPrediction_LcuSizeMax;
extern fifo_u8_t *HevcDecoder_IntraPrediction_PartMode;
extern fifo_u16_t *HevcDecoder_IntraPrediction_PictSize;
extern fifo_u8_t *HevcDecoder_IntraPrediction_Sample;
extern fifo_u16_t *HevcDecoder_IntraPrediction_SliceAddr;
extern fifo_i32_t *HevcDecoder_IntraPrediction_SplitTransform;
extern fifo_i32_t *HevcDecoder_IntraPrediction_StrongIntraSmoothing;
extern fifo_u16_t *HevcDecoder_IntraPrediction_TilesCoord;

////////////////////////////////////////////////////////////////////////////////
// Input Fifo control variables
static unsigned int index_CUInfo;
static unsigned int numTokens_CUInfo;
#define SIZE_CUInfo SIZE
#define tokens_CUInfo HevcDecoder_IntraPrediction_CUInfo->contents

extern connection_t connection_HevcDecoder_IntraPrediction_CUInfo;
#define rate_CUInfo connection_HevcDecoder_IntraPrediction_CUInfo.rate

static unsigned int index_IntraPredMode;
static unsigned int numTokens_IntraPredMode;
#define SIZE_IntraPredMode SIZE
#define tokens_IntraPredMode HevcDecoder_IntraPrediction_IntraPredMode->contents

extern connection_t connection_HevcDecoder_IntraPrediction_IntraPredMode;
#define rate_IntraPredMode connection_HevcDecoder_IntraPrediction_IntraPredMode.rate

static unsigned int index_LcuSizeMax;
static unsigned int numTokens_LcuSizeMax;
#define SIZE_LcuSizeMax SIZE
#define tokens_LcuSizeMax HevcDecoder_IntraPrediction_LcuSizeMax->contents

extern connection_t connection_HevcDecoder_IntraPrediction_LcuSizeMax;
#define rate_LcuSizeMax connection_HevcDecoder_IntraPrediction_LcuSizeMax.rate

static unsigned int index_PartMode;
static unsigned int numTokens_PartMode;
#define SIZE_PartMode SIZE
#define tokens_PartMode HevcDecoder_IntraPrediction_PartMode->contents

extern connection_t connection_HevcDecoder_IntraPrediction_PartMode;
#define rate_PartMode connection_HevcDecoder_IntraPrediction_PartMode.rate

static unsigned int index_PictSize;
static unsigned int numTokens_PictSize;
#define SIZE_PictSize SIZE
#define tokens_PictSize HevcDecoder_IntraPrediction_PictSize->contents

extern connection_t connection_HevcDecoder_IntraPrediction_PictSize;
#define rate_PictSize connection_HevcDecoder_IntraPrediction_PictSize.rate

static unsigned int index_Sample;
static unsigned int numTokens_Sample;
#define SIZE_Sample SIZE
#define tokens_Sample HevcDecoder_IntraPrediction_Sample->contents

extern connection_t connection_HevcDecoder_IntraPrediction_Sample;
#define rate_Sample connection_HevcDecoder_IntraPrediction_Sample.rate

static unsigned int index_SliceAddr;
static unsigned int numTokens_SliceAddr;
#define SIZE_SliceAddr SIZE
#define tokens_SliceAddr HevcDecoder_IntraPrediction_SliceAddr->contents

extern connection_t connection_HevcDecoder_IntraPrediction_SliceAddr;
#define rate_SliceAddr connection_HevcDecoder_IntraPrediction_SliceAddr.rate

static unsigned int index_SplitTransform;
static unsigned int numTokens_SplitTransform;
#define SIZE_SplitTransform SIZE
#define tokens_SplitTransform HevcDecoder_IntraPrediction_SplitTransform->contents

extern connection_t connection_HevcDecoder_IntraPrediction_SplitTransform;
#define rate_SplitTransform connection_HevcDecoder_IntraPrediction_SplitTransform.rate

static unsigned int index_StrongIntraSmoothing;
static unsigned int numTokens_StrongIntraSmoothing;
#define SIZE_StrongIntraSmoothing SIZE
#define tokens_StrongIntraSmoothing HevcDecoder_IntraPrediction_StrongIntraSmoothing->contents

extern connection_t connection_HevcDecoder_IntraPrediction_StrongIntraSmoothing;
#define rate_StrongIntraSmoothing connection_HevcDecoder_IntraPrediction_StrongIntraSmoothing.rate

static unsigned int index_TilesCoord;
static unsigned int numTokens_TilesCoord;
#define SIZE_TilesCoord SIZE
#define tokens_TilesCoord HevcDecoder_IntraPrediction_TilesCoord->contents

extern connection_t connection_HevcDecoder_IntraPrediction_TilesCoord;
#define rate_TilesCoord connection_HevcDecoder_IntraPrediction_TilesCoord.rate

////////////////////////////////////////////////////////////////////////////////
// Predecessors
extern actor_t HevcDecoder_Algo_Parser;
extern actor_t HevcDecoder_Algo_Parser;
extern actor_t HevcDecoder_Algo_Parser;
extern actor_t HevcDecoder_Algo_Parser;
extern actor_t HevcDecoder_Algo_Parser;
extern actor_t HevcDecoder_SelectCU;
extern actor_t HevcDecoder_Algo_Parser;
extern actor_t HevcDecoder_Algo_Parser;
extern actor_t HevcDecoder_Algo_Parser;
extern actor_t HevcDecoder_Algo_Parser;

////////////////////////////////////////////////////////////////////////////////
// Output FIFOs
extern fifo_u8_t *HevcDecoder_IntraPrediction_PredSample;

////////////////////////////////////////////////////////////////////////////////
// Output Fifo control variables
static unsigned int index_PredSample;
static unsigned int numFree_PredSample;
#define NUM_READERS_PredSample 1
#define SIZE_PredSample SIZE
#define tokens_PredSample HevcDecoder_IntraPrediction_PredSample->contents

////////////////////////////////////////////////////////////////////////////////
// Successors
extern actor_t HevcDecoder_SelectCU;

////////////////////////////////////////////////////////////////////////////////
// Parameter values of the instance
#define EnabSkipInPix 0


////////////////////////////////////////////////////////////////////////////////
// State variables of the actor
#define HevcDecoder_IntraPrediction_PART_MODE_SLICE_INDEP 10
#define HevcDecoder_IntraPrediction_PART_MODE_PICT 8
#define HevcDecoder_IntraPrediction_PART_MODE_SLICE_DEP 9
#define HevcDecoder_IntraPrediction_PART_2Nx2N 0
#define HevcDecoder_IntraPrediction_PART_NxN 3
static const u8 HevcDecoder_IntraPrediction_partModeToNumPart[8] = {1, 2, 2, 4, 2, 2, 2, 2};
#define HevcDecoder_IntraPrediction_IN_SAMP 8
#define HevcDecoder_IntraPrediction_NO_IN_SAMP 4
#define HevcDecoder_IntraPrediction_INTRA 1
#define HevcDecoder_IntraPrediction_INTER 0
#define HevcDecoder_IntraPrediction_SKIP 2
#define HevcDecoder_IntraPrediction_OTHER 16
static const i8 HevcDecoder_IntraPrediction_intraPredAngle[64] = {0, 0, 32, 26, 21, 17, 13, 9, 5, 2, 0, -2, -5, -9, -13, -17, -21, -26, -32, -26, -21, -17, -13, -9, -5, -2, 0, 2, 5, 9, 13, 17, 21, 26, 32};
static const i16 HevcDecoder_IntraPrediction_invAngle[64] = {0, 0, -256, -315, -390, -482, -630, -910, -1638, -4096, 0, -4096, -1638, -910, -630, -482, -390, -315, -256, -315, -390, -482, -630, -910, -1638, -4096, 0, -4096, -1638, -910, -630, -482, -390, -315, -256};
static const u8 HevcDecoder_IntraPrediction_ZscanToAbsCoord0[257] = {0, 4, 0, 4, 8, 12, 8, 12, 0, 4, 0, 4, 8, 12, 8, 12, 16, 20, 16, 20, 24, 28, 24, 28, 16, 20, 16, 20, 24, 28, 24, 28, 0, 4, 0, 4, 8, 12, 8, 12, 0, 4, 0, 4, 8, 12, 8, 12, 16, 20, 16, 20, 24, 28, 24, 28, 16, 20, 16, 20, 24, 28, 24, 28, 32, 36, 32, 36, 40, 44, 40, 44, 32, 36, 32, 36, 40, 44, 40, 44, 48, 52, 48, 52, 56, 60, 56, 60, 48, 52, 48, 52, 56, 60, 56, 60, 32, 36, 32, 36, 40, 44, 40, 44, 32, 36, 32, 36, 40, 44, 40, 44, 48, 52, 48, 52, 56, 60, 56, 60, 48, 52, 48, 52, 56, 60, 56, 60, 0, 4, 0, 4, 8, 12, 8, 12, 0, 4, 0, 4, 8, 12, 8, 12, 16, 20, 16, 20, 24, 28, 24, 28, 16, 20, 16, 20, 24, 28, 24, 28, 0, 4, 0, 4, 8, 12, 8, 12, 0, 4, 0, 4, 8, 12, 8, 12, 16, 20, 16, 20, 24, 28, 24, 28, 16, 20, 16, 20, 24, 28, 24, 28, 32, 36, 32, 36, 40, 44, 40, 44, 32, 36, 32, 36, 40, 44, 40, 44, 48, 52, 48, 52, 56, 60, 56, 60, 48, 52, 48, 52, 56, 60, 56, 60, 32, 36, 32, 36, 40, 44, 40, 44, 32, 36, 32, 36, 40, 44, 40, 44, 48, 52, 48, 52, 56, 60, 56, 60, 48, 52, 48, 52, 56, 60, 56, 60, 0};
static const u8 HevcDecoder_IntraPrediction_ZscanToAbsCoord1[257] = {0, 0, 4, 4, 0, 0, 4, 4, 8, 8, 12, 12, 8, 8, 12, 12, 0, 0, 4, 4, 0, 0, 4, 4, 8, 8, 12, 12, 8, 8, 12, 12, 16, 16, 20, 20, 16, 16, 20, 20, 24, 24, 28, 28, 24, 24, 28, 28, 16, 16, 20, 20, 16, 16, 20, 20, 24, 24, 28, 28, 24, 24, 28, 28, 0, 0, 4, 4, 0, 0, 4, 4, 8, 8, 12, 12, 8, 8, 12, 12, 0, 0, 4, 4, 0, 0, 4, 4, 8, 8, 12, 12, 8, 8, 12, 12, 16, 16, 20, 20, 16, 16, 20, 20, 24, 24, 28, 28, 24, 24, 28, 28, 16, 16, 20, 20, 16, 16, 20, 20, 24, 24, 28, 28, 24, 24, 28, 28, 32, 32, 36, 36, 32, 32, 36, 36, 40, 40, 44, 44, 40, 40, 44, 44, 32, 32, 36, 36, 32, 32, 36, 36, 40, 40, 44, 44, 40, 40, 44, 44, 48, 48, 52, 52, 48, 48, 52, 52, 56, 56, 60, 60, 56, 56, 60, 60, 48, 48, 52, 52, 48, 48, 52, 52, 56, 56, 60, 60, 56, 56, 60, 60, 32, 32, 36, 36, 32, 32, 36, 36, 40, 40, 44, 44, 40, 40, 44, 44, 32, 32, 36, 36, 32, 32, 36, 36, 40, 40, 44, 44, 40, 40, 44, 44, 48, 48, 52, 52, 48, 48, 52, 52, 56, 56, 60, 60, 56, 56, 60, 60, 48, 48, 52, 52, 48, 48, 52, 52, 56, 56, 60, 60, 56, 56, 60, 60, 0};
#define NEIGHB_TAB_SZ 8192
#define NEIGHB_TAB_MASK 8191
#define INTRA_PLANAR 0
#define INTRA_DC 1
static const u8 leftBlkAvail[256] = {0, 1, 0, 1, 2, 1, 1, 1, 0, 1, 0, 1, 2, 1, 1, 1, 4, 1, 3, 1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 0, 1, 0, 1, 2, 1, 1, 1, 0, 1, 0, 1, 2, 1, 1, 1, 4, 1, 3, 1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 8, 1, 7, 1, 2, 1, 1, 1, 6, 1, 5, 1, 2, 1, 1, 1, 4, 1, 3, 1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 4, 1, 3, 1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 4, 1, 3, 1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 0, 1, 0, 1, 2, 1, 1, 1, 0, 1, 0, 1, 2, 1, 1, 1, 4, 1, 3, 1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 0, 1, 0, 1, 2, 1, 1, 1, 0, 1, 0, 1, 2, 1, 1, 1, 4, 1, 3, 1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 8, 1, 7, 1, 2, 1, 1, 1, 6, 1, 5, 1, 2, 1, 1, 1, 4, 1, 3, 1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 4, 1, 3, 1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 4, 1, 3, 1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1};
static const u8 aboveBlkAvail[256] = {0, 0, 2, 1, 0, 0, 2, 1, 4, 3, 2, 1, 2, 1, 2, 1, 0, 0, 2, 1, 0, 0, 2, 1, 4, 3, 2, 1, 2, 1, 2, 1, 8, 7, 2, 1, 6, 5, 2, 1, 4, 3, 2, 1, 2, 1, 2, 1, 4, 3, 2, 1, 2, 1, 2, 1, 4, 3, 2, 1, 2, 1, 2, 1, 0, 0, 2, 1, 0, 0, 2, 1, 4, 3, 2, 1, 2, 1, 2, 1, 0, 0, 2, 1, 0, 0, 2, 1, 4, 3, 2, 1, 2, 1, 2, 1, 8, 7, 2, 1, 6, 5, 2, 1, 4, 3, 2, 1, 2, 1, 2, 1, 4, 3, 2, 1, 2, 1, 2, 1, 4, 3, 2, 1, 2, 1, 2, 1, 16, 15, 2, 1, 14, 13, 2, 1, 4, 3, 2, 1, 2, 1, 2, 1, 12, 11, 2, 1, 10, 9, 2, 1, 4, 3, 2, 1, 2, 1, 2, 1, 8, 7, 2, 1, 6, 5, 2, 1, 4, 3, 2, 1, 2, 1, 2, 1, 4, 3, 2, 1, 2, 1, 2, 1, 4, 3, 2, 1, 2, 1, 2, 1, 8, 7, 2, 1, 6, 5, 2, 1, 4, 3, 2, 1, 2, 1, 2, 1, 4, 3, 2, 1, 2, 1, 2, 1, 4, 3, 2, 1, 2, 1, 2, 1, 8, 7, 2, 1, 6, 5, 2, 1, 4, 3, 2, 1, 2, 1, 2, 1, 4, 3, 2, 1, 2, 1, 2, 1, 4, 3, 2, 1, 2, 1, 2, 1};
static i16 iLoop;
static u16 numTiles;
static u16 tilesBeg[128][2];
static u16 tilesEnd[128][2];
static i16 puTilesBeg[3][2];
static i16 puTilesEnd[3][2];
static u8 nS;
static u8 log2NS;
static u16 cuAddr[2];
static u8 cuMode;
static u16 treeAddr[2];
static u16 pictSize[3][2];
static u16 sliceAddr[3][2];
static u8 numPart;
static u8 numPartDecoded;
static i32 strongIntraSmoothing;
static i32 constrIntraPred;
static i32 isIndepSlc;
static u8 maxLcuSizeLuma;
static u8 maxLcuSizeChr;
static u8 predMode;
static u8 predModeTab[3];
static i8 trafoTreeDepth;
static u8 trafoTreeIdx[6];
static u8 pNeighb_left[129];
static u8 pNeighb_above[129];
static u8 puNeighb[3][8192];
static i32 puIsIntra[3][8192];
static u8 neighbBlkSz;
static u8 lumaComp[4096];
static u8 chrComp_u[4096];
static u8 chrComp_v[4096];
static u16 numBlkToSend;
static u16 idxBlk;
static i32 getInSamp;

////////////////////////////////////////////////////////////////////////////////
// Initial FSM state of the actor
enum states {
	my_state_GetCuInfo,
	my_state_GetCuInfoNonQT,
	my_state_GetCuMode,
	my_state_GetInSamples,
	my_state_GetInterSamples,
	my_state_GetIntraSamples,
	my_state_GetPartMode,
	my_state_GetSplitTrafoInter,
	my_state_GetSplitTrafoIntra,
	my_state_GetTilesCoord,
	my_state_SendSamples
};

static char *stateNames[] = {
	"GetCuInfo",
	"GetCuInfoNonQT",
	"GetCuMode",
	"GetInSamples",
	"GetInterSamples",
	"GetIntraSamples",
	"GetPartMode",
	"GetSplitTrafoInter",
	"GetSplitTrafoIntra",
	"GetTilesCoord",
	"SendSamples"
};

static enum states _FSM_state;



////////////////////////////////////////////////////////////////////////////////
// Token functions
static void read_CUInfo() {
	index_CUInfo = HevcDecoder_IntraPrediction_CUInfo->read_inds[0];
	numTokens_CUInfo = index_CUInfo + fifo_u16_get_num_tokens(HevcDecoder_IntraPrediction_CUInfo, 0);
}

static void read_end_CUInfo() {
	HevcDecoder_IntraPrediction_CUInfo->read_inds[0] = index_CUInfo;
}
static void read_IntraPredMode() {
	index_IntraPredMode = HevcDecoder_IntraPrediction_IntraPredMode->read_inds[0];
	numTokens_IntraPredMode = index_IntraPredMode + fifo_u8_get_num_tokens(HevcDecoder_IntraPrediction_IntraPredMode, 0);
}

static void read_end_IntraPredMode() {
	HevcDecoder_IntraPrediction_IntraPredMode->read_inds[0] = index_IntraPredMode;
}
static void read_LcuSizeMax() {
	index_LcuSizeMax = HevcDecoder_IntraPrediction_LcuSizeMax->read_inds[0];
	numTokens_LcuSizeMax = index_LcuSizeMax + fifo_u8_get_num_tokens(HevcDecoder_IntraPrediction_LcuSizeMax, 0);
}

static void read_end_LcuSizeMax() {
	HevcDecoder_IntraPrediction_LcuSizeMax->read_inds[0] = index_LcuSizeMax;
}
static void read_PartMode() {
	index_PartMode = HevcDecoder_IntraPrediction_PartMode->read_inds[0];
	numTokens_PartMode = index_PartMode + fifo_u8_get_num_tokens(HevcDecoder_IntraPrediction_PartMode, 0);
}

static void read_end_PartMode() {
	HevcDecoder_IntraPrediction_PartMode->read_inds[0] = index_PartMode;
}
static void read_PictSize() {
	index_PictSize = HevcDecoder_IntraPrediction_PictSize->read_inds[0];
	numTokens_PictSize = index_PictSize + fifo_u16_get_num_tokens(HevcDecoder_IntraPrediction_PictSize, 0);
}

static void read_end_PictSize() {
	HevcDecoder_IntraPrediction_PictSize->read_inds[0] = index_PictSize;
}
static void read_Sample() {
	index_Sample = HevcDecoder_IntraPrediction_Sample->read_inds[0];
	numTokens_Sample = index_Sample + fifo_u8_get_num_tokens(HevcDecoder_IntraPrediction_Sample, 0);
}

static void read_end_Sample() {
	HevcDecoder_IntraPrediction_Sample->read_inds[0] = index_Sample;
}
static void read_SliceAddr() {
	index_SliceAddr = HevcDecoder_IntraPrediction_SliceAddr->read_inds[0];
	numTokens_SliceAddr = index_SliceAddr + fifo_u16_get_num_tokens(HevcDecoder_IntraPrediction_SliceAddr, 0);
}

static void read_end_SliceAddr() {
	HevcDecoder_IntraPrediction_SliceAddr->read_inds[0] = index_SliceAddr;
}
static void read_SplitTransform() {
	index_SplitTransform = HevcDecoder_IntraPrediction_SplitTransform->read_inds[0];
	numTokens_SplitTransform = index_SplitTransform + fifo_i32_get_num_tokens(HevcDecoder_IntraPrediction_SplitTransform, 0);
}

static void read_end_SplitTransform() {
	HevcDecoder_IntraPrediction_SplitTransform->read_inds[0] = index_SplitTransform;
}
static void read_StrongIntraSmoothing() {
	index_StrongIntraSmoothing = HevcDecoder_IntraPrediction_StrongIntraSmoothing->read_inds[0];
	numTokens_StrongIntraSmoothing = index_StrongIntraSmoothing + fifo_i32_get_num_tokens(HevcDecoder_IntraPrediction_StrongIntraSmoothing, 0);
}

static void read_end_StrongIntraSmoothing() {
	HevcDecoder_IntraPrediction_StrongIntraSmoothing->read_inds[0] = index_StrongIntraSmoothing;
}
static void read_TilesCoord() {
	index_TilesCoord = HevcDecoder_IntraPrediction_TilesCoord->read_inds[0];
	numTokens_TilesCoord = index_TilesCoord + fifo_u16_get_num_tokens(HevcDecoder_IntraPrediction_TilesCoord, 0);
}

static void read_end_TilesCoord() {
	HevcDecoder_IntraPrediction_TilesCoord->read_inds[0] = index_TilesCoord;
}

static void write_PredSample() {
	index_PredSample = HevcDecoder_IntraPrediction_PredSample->write_ind;
	numFree_PredSample = index_PredSample + fifo_u8_get_room(HevcDecoder_IntraPrediction_PredSample, NUM_READERS_PredSample, SIZE_PredSample);
}

static void write_end_PredSample() {
	HevcDecoder_IntraPrediction_PredSample->write_ind = index_PredSample;
}

////////////////////////////////////////////////////////////////////////////////
// Functions/procedures
static i32 HevcDecoder_IntraPrediction_min(i32 a, i32 b);
static i32 HevcDecoder_IntraPrediction_max(i32 a, i32 b);
static i32 HevcDecoder_IntraPrediction_abs(i32 x);
static void HevcDecoder_IntraPrediction_intraPlanarPred3(u8 src[4096], u8 top[129], u8 left[129], i32 stride);
static void HevcDecoder_IntraPrediction_intraPlanarPred2(u8 src[4096], u8 top[129], u8 left[129], i32 stride);
static void HevcDecoder_IntraPrediction_intraPlanarPred1(u8 src[4096], u8 top[129], u8 left[129], i32 stride);
static void HevcDecoder_IntraPrediction_intraPlanarPred0(u8 src[4096], u8 top[129], u8 left[129], i32 stride);
static void HevcDecoder_IntraPrediction_intraPlanarPred(u8 src[4096], u8 top[129], u8 left[129], i32 stride, i32 log2Size);
static void HevcDecoder_IntraPrediction_intraAngularVertOrHor_chroma_3(i32 isVertical, u8 comp[4096], u8 pNeighb_above[129], u8 pNeighb_left[129], i32 stride);
static i32 HevcDecoder_IntraPrediction_clip_i32(i32 Value, i32 minVal, i32 maxVal);
static void HevcDecoder_IntraPrediction_intraAngularVertOrHor3(i32 isVertical, u8 comp[4096], u8 pNeighb_above[129], u8 pNeighb_left[129], i32 stride);
static void HevcDecoder_IntraPrediction_intraAngularPred3(u8 comp[4096], u8 pNeighb_above[129], u8 pNeighb_left[129], i32 stride, i32 idx, u8 mode);
static void HevcDecoder_IntraPrediction_intraAngularVertOrHor_chroma_2(i32 isVertical, u8 comp[4096], u8 pNeighb_above[129], u8 pNeighb_left[129], i32 stride);
static void HevcDecoder_IntraPrediction_intraAngularVertOrHor2(i32 isVertical, u8 comp[4096], u8 pNeighb_above[129], u8 pNeighb_left[129], i32 stride);
static void HevcDecoder_IntraPrediction_intraAngularPred2(u8 comp[4096], u8 pNeighb_above[129], u8 pNeighb_left[129], i32 stride, i32 idx, u8 mode);
static void HevcDecoder_IntraPrediction_intraAngularVertOrHor_chroma_1(i32 isVertical, u8 lumaComp[4096], u8 pNeighb_above[129], u8 pNeighb_left[129], i32 stride);
static void HevcDecoder_IntraPrediction_intraAngularVertOrHor1(i32 isVertical, u8 lumaComp[4096], u8 pNeighb_above[129], u8 pNeighb_left[129], i32 stride);
static void HevcDecoder_IntraPrediction_intraAngularPred1(u8 lumaComp[4096], u8 pNeighb_above[129], u8 pNeighb_left[129], i32 stride, i32 idx, u8 mode);
static void HevcDecoder_IntraPrediction_intraAngularVertOrHor_chroma_0(i32 isVertical, u8 comp[4096], u8 pNeighb_above[129], u8 pNeighb_left[129], i32 stride);
static void HevcDecoder_IntraPrediction_intraAngularVertOrHor0(i32 isVertical, u8 lumaComp[4096], u8 pNeighb_above[129], u8 pNeighb_left[129], i32 stride);
static void HevcDecoder_IntraPrediction_intraAngularPred0(u8 comp[4096], u8 pNeighb_above[129], u8 pNeighb_left[129], i32 stride, i32 idx, u8 mode);
static void HevcDecoder_IntraPrediction_intraAngularPred(u8 src[4096], u8 top[129], u8 left[129], i32 stride, i32 idx, u8 mode, i32 log2Size);
static void HevcDecoder_IntraPrediction_zScanToAbsCoord(u16 rasterIdx, u16 coord[2]);
static i32 absCoordToRasterScan(u16 coord[2]);
static void getNeighbSamples(u16 cuAddr[2], u8 cIdx, u8 nS, u8 log2NS);
static void neighbExist(u16 cuAddr[2], i32 minVal[2], i32 maxVal[2], i32 cIdx, u8 nS);
static void filterNeighbSamp(u8 nS, u8 log2NS);
static void intraDcPred(u8 cIdx, u8 nS, u8 log2NS);

static i32 HevcDecoder_IntraPrediction_min(i32 a, i32 b) {
	i32 tmp_if;

	if (a < b) {
		tmp_if = a;
	} else {
		tmp_if = b;
	}
	return tmp_if;
}
static i32 HevcDecoder_IntraPrediction_max(i32 a, i32 b) {
	i32 tmp_if;

	if (a > b) {
		tmp_if = a;
	} else {
		tmp_if = b;
	}
	return tmp_if;
}
static i32 HevcDecoder_IntraPrediction_abs(i32 x) {
	i32 tmp_if;

	if (x > 0) {
		tmp_if = x;
	} else {
		tmp_if = -x;
	}
	return tmp_if;
}
static void HevcDecoder_IntraPrediction_intraPlanarPred3(u8 src[4096], u8 top[129], u8 left[129], i32 stride) {
	i32 x;
	i32 y;
	u8 tmp_left;
	u8 tmp_top;
	u8 tmp_top0;
	u8 tmp_left0;
	u8 tmp_left1;
	u8 tmp_top1;
	u8 tmp_top2;
	u8 tmp_left2;
	u8 tmp_left3;
	u8 tmp_top3;
	u8 tmp_top4;
	u8 tmp_left4;
	u8 tmp_left5;
	u8 tmp_top5;
	u8 tmp_top6;
	u8 tmp_left6;
	u8 tmp_left7;
	u8 tmp_top7;
	u8 tmp_top8;
	u8 tmp_left8;
	u8 tmp_left9;
	u8 tmp_top9;
	u8 tmp_top10;
	u8 tmp_left10;
	u8 tmp_left11;
	u8 tmp_top11;
	u8 tmp_top12;
	u8 tmp_left12;
	u8 tmp_left13;
	u8 tmp_top13;
	u8 tmp_top14;
	u8 tmp_left14;
	u8 tmp_left15;
	u8 tmp_top15;
	u8 tmp_top16;
	u8 tmp_left16;
	u8 tmp_left17;
	u8 tmp_top17;
	u8 tmp_top18;
	u8 tmp_left18;
	u8 tmp_left19;
	u8 tmp_top19;
	u8 tmp_top20;
	u8 tmp_left20;
	u8 tmp_left21;
	u8 tmp_top21;
	u8 tmp_top22;
	u8 tmp_left22;
	u8 tmp_left23;
	u8 tmp_top23;
	u8 tmp_top24;
	u8 tmp_left24;
	u8 tmp_left25;
	u8 tmp_top25;
	u8 tmp_top26;
	u8 tmp_left26;
	u8 tmp_left27;
	u8 tmp_top27;
	u8 tmp_top28;
	u8 tmp_left28;
	u8 tmp_left29;
	u8 tmp_top29;
	u8 tmp_top30;
	u8 tmp_left30;

	x = 0;
	y = 0;
	while (y < 32) {
		while (x < 32) {
			tmp_left = left[y + 1];
			tmp_top = top[33];
			tmp_top0 = top[x + 1];
			tmp_left0 = left[33];
			src[x + y * stride] = ((31 - x) * tmp_left + (x + 1) * tmp_top + (31 - y) * tmp_top0 + (y + 1) * tmp_left0 + 32) >> 6;
			tmp_left1 = left[y + 1];
			tmp_top1 = top[33];
			tmp_top2 = top[x + 1 + 1];
			tmp_left2 = left[33];
			src[x + 1 + y * stride] = ((31 - (x + 1)) * tmp_left1 + (x + 1 + 1) * tmp_top1 + (31 - y) * tmp_top2 + (y + 1) * tmp_left2 + 32) >> 6;
			tmp_left3 = left[y + 1];
			tmp_top3 = top[33];
			tmp_top4 = top[x + 2 + 1];
			tmp_left4 = left[33];
			src[x + 2 + y * stride] = ((31 - (x + 2)) * tmp_left3 + (x + 2 + 1) * tmp_top3 + (31 - y) * tmp_top4 + (y + 1) * tmp_left4 + 32) >> 6;
			tmp_left5 = left[y + 1];
			tmp_top5 = top[33];
			tmp_top6 = top[x + 3 + 1];
			tmp_left6 = left[33];
			src[x + 3 + y * stride] = ((31 - (x + 3)) * tmp_left5 + (x + 3 + 1) * tmp_top5 + (31 - y) * tmp_top6 + (y + 1) * tmp_left6 + 32) >> 6;
			x = x + 4;
		}
		x = 0;
		while (x < 32) {
			tmp_left7 = left[y + 1 + 1];
			tmp_top7 = top[33];
			tmp_top8 = top[x + 1];
			tmp_left8 = left[33];
			src[x + (y + 1) * stride] = ((31 - x) * tmp_left7 + (x + 1) * tmp_top7 + (31 - (y + 1)) * tmp_top8 + (y + 1 + 1) * tmp_left8 + 32) >> 6;
			tmp_left9 = left[y + 1 + 1];
			tmp_top9 = top[33];
			tmp_top10 = top[x + 1 + 1];
			tmp_left10 = left[33];
			src[x + 1 + (y + 1) * stride] = ((31 - (x + 1)) * tmp_left9 + (x + 1 + 1) * tmp_top9 + (31 - (y + 1)) * tmp_top10 + (y + 1 + 1) * tmp_left10 + 32) >> 6;
			tmp_left11 = left[y + 1 + 1];
			tmp_top11 = top[33];
			tmp_top12 = top[x + 2 + 1];
			tmp_left12 = left[33];
			src[x + 2 + (y + 1) * stride] = ((31 - (x + 2)) * tmp_left11 + (x + 2 + 1) * tmp_top11 + (31 - (y + 1)) * tmp_top12 + (y + 1 + 1) * tmp_left12 + 32) >> 6;
			tmp_left13 = left[y + 1 + 1];
			tmp_top13 = top[33];
			tmp_top14 = top[x + 3 + 1];
			tmp_left14 = left[33];
			src[x + 3 + (y + 1) * stride] = ((31 - (x + 3)) * tmp_left13 + (x + 3 + 1) * tmp_top13 + (31 - (y + 1)) * tmp_top14 + (y + 1 + 1) * tmp_left14 + 32) >> 6;
			x = x + 4;
		}
		x = 0;
		while (x < 32) {
			tmp_left15 = left[y + 2 + 1];
			tmp_top15 = top[33];
			tmp_top16 = top[x + 1];
			tmp_left16 = left[33];
			src[x + (y + 2) * stride] = ((31 - x) * tmp_left15 + (x + 1) * tmp_top15 + (31 - (y + 2)) * tmp_top16 + (y + 2 + 1) * tmp_left16 + 32) >> 6;
			tmp_left17 = left[y + 2 + 1];
			tmp_top17 = top[33];
			tmp_top18 = top[x + 1 + 1];
			tmp_left18 = left[33];
			src[x + 1 + (y + 2) * stride] = ((31 - (x + 1)) * tmp_left17 + (x + 1 + 1) * tmp_top17 + (31 - (y + 2)) * tmp_top18 + (y + 2 + 1) * tmp_left18 + 32) >> 6;
			tmp_left19 = left[y + 2 + 1];
			tmp_top19 = top[33];
			tmp_top20 = top[x + 2 + 1];
			tmp_left20 = left[33];
			src[x + 2 + (y + 2) * stride] = ((31 - (x + 2)) * tmp_left19 + (x + 2 + 1) * tmp_top19 + (31 - (y + 2)) * tmp_top20 + (y + 2 + 1) * tmp_left20 + 32) >> 6;
			tmp_left21 = left[y + 2 + 1];
			tmp_top21 = top[33];
			tmp_top22 = top[x + 3 + 1];
			tmp_left22 = left[33];
			src[x + 3 + (y + 2) * stride] = ((31 - (x + 3)) * tmp_left21 + (x + 3 + 1) * tmp_top21 + (31 - (y + 2)) * tmp_top22 + (y + 2 + 1) * tmp_left22 + 32) >> 6;
			x = x + 4;
		}
		x = 0;
		while (x < 32) {
			tmp_left23 = left[y + 3 + 1];
			tmp_top23 = top[33];
			tmp_top24 = top[x + 1];
			tmp_left24 = left[33];
			src[x + (y + 3) * stride] = ((31 - x) * tmp_left23 + (x + 1) * tmp_top23 + (31 - (y + 3)) * tmp_top24 + (y + 3 + 1) * tmp_left24 + 32) >> 6;
			tmp_left25 = left[y + 3 + 1];
			tmp_top25 = top[33];
			tmp_top26 = top[x + 1 + 1];
			tmp_left26 = left[33];
			src[x + 1 + (y + 3) * stride] = ((31 - (x + 1)) * tmp_left25 + (x + 1 + 1) * tmp_top25 + (31 - (y + 3)) * tmp_top26 + (y + 3 + 1) * tmp_left26 + 32) >> 6;
			tmp_left27 = left[y + 3 + 1];
			tmp_top27 = top[33];
			tmp_top28 = top[x + 2 + 1];
			tmp_left28 = left[33];
			src[x + 2 + (y + 3) * stride] = ((31 - (x + 2)) * tmp_left27 + (x + 2 + 1) * tmp_top27 + (31 - (y + 3)) * tmp_top28 + (y + 3 + 1) * tmp_left28 + 32) >> 6;
			tmp_left29 = left[y + 3 + 1];
			tmp_top29 = top[33];
			tmp_top30 = top[x + 3 + 1];
			tmp_left30 = left[33];
			src[x + 3 + (y + 3) * stride] = ((31 - (x + 3)) * tmp_left29 + (x + 3 + 1) * tmp_top29 + (31 - (y + 3)) * tmp_top30 + (y + 3 + 1) * tmp_left30 + 32) >> 6;
			x = x + 4;
		}
		x = 0;
		y = y + 4;
	}
}
static void HevcDecoder_IntraPrediction_intraPlanarPred2(u8 src[4096], u8 top[129], u8 left[129], i32 stride) {
	i32 x;
	i32 y;
	u8 tmp_left;
	u8 tmp_top;
	u8 tmp_top0;
	u8 tmp_left0;
	u8 tmp_left1;
	u8 tmp_top1;
	u8 tmp_top2;
	u8 tmp_left2;
	u8 tmp_left3;
	u8 tmp_top3;
	u8 tmp_top4;
	u8 tmp_left4;
	u8 tmp_left5;
	u8 tmp_top5;
	u8 tmp_top6;
	u8 tmp_left6;
	u8 tmp_left7;
	u8 tmp_top7;
	u8 tmp_top8;
	u8 tmp_left8;
	u8 tmp_left9;
	u8 tmp_top9;
	u8 tmp_top10;
	u8 tmp_left10;
	u8 tmp_left11;
	u8 tmp_top11;
	u8 tmp_top12;
	u8 tmp_left12;
	u8 tmp_left13;
	u8 tmp_top13;
	u8 tmp_top14;
	u8 tmp_left14;
	u8 tmp_left15;
	u8 tmp_top15;
	u8 tmp_top16;
	u8 tmp_left16;
	u8 tmp_left17;
	u8 tmp_top17;
	u8 tmp_top18;
	u8 tmp_left18;
	u8 tmp_left19;
	u8 tmp_top19;
	u8 tmp_top20;
	u8 tmp_left20;
	u8 tmp_left21;
	u8 tmp_top21;
	u8 tmp_top22;
	u8 tmp_left22;
	u8 tmp_left23;
	u8 tmp_top23;
	u8 tmp_top24;
	u8 tmp_left24;
	u8 tmp_left25;
	u8 tmp_top25;
	u8 tmp_top26;
	u8 tmp_left26;
	u8 tmp_left27;
	u8 tmp_top27;
	u8 tmp_top28;
	u8 tmp_left28;
	u8 tmp_left29;
	u8 tmp_top29;
	u8 tmp_top30;
	u8 tmp_left30;

	x = 0;
	y = 0;
	while (y < 16) {
		while (x < 16) {
			tmp_left = left[y + 1];
			tmp_top = top[17];
			tmp_top0 = top[x + 1];
			tmp_left0 = left[17];
			src[x + y * stride] = ((15 - x) * tmp_left + (x + 1) * tmp_top + (15 - y) * tmp_top0 + (y + 1) * tmp_left0 + 16) >> 5;
			tmp_left1 = left[y + 1];
			tmp_top1 = top[17];
			tmp_top2 = top[x + 1 + 1];
			tmp_left2 = left[17];
			src[x + 1 + y * stride] = ((15 - (x + 1)) * tmp_left1 + (x + 1 + 1) * tmp_top1 + (15 - y) * tmp_top2 + (y + 1) * tmp_left2 + 16) >> 5;
			tmp_left3 = left[y + 1];
			tmp_top3 = top[17];
			tmp_top4 = top[x + 2 + 1];
			tmp_left4 = left[17];
			src[x + 2 + y * stride] = ((15 - (x + 2)) * tmp_left3 + (x + 2 + 1) * tmp_top3 + (15 - y) * tmp_top4 + (y + 1) * tmp_left4 + 16) >> 5;
			tmp_left5 = left[y + 1];
			tmp_top5 = top[17];
			tmp_top6 = top[x + 3 + 1];
			tmp_left6 = left[17];
			src[x + 3 + y * stride] = ((15 - (x + 3)) * tmp_left5 + (x + 3 + 1) * tmp_top5 + (15 - y) * tmp_top6 + (y + 1) * tmp_left6 + 16) >> 5;
			x = x + 4;
		}
		x = 0;
		while (x < 16) {
			tmp_left7 = left[y + 1 + 1];
			tmp_top7 = top[17];
			tmp_top8 = top[x + 1];
			tmp_left8 = left[17];
			src[x + (y + 1) * stride] = ((15 - x) * tmp_left7 + (x + 1) * tmp_top7 + (15 - (y + 1)) * tmp_top8 + (y + 1 + 1) * tmp_left8 + 16) >> 5;
			tmp_left9 = left[y + 1 + 1];
			tmp_top9 = top[17];
			tmp_top10 = top[x + 1 + 1];
			tmp_left10 = left[17];
			src[x + 1 + (y + 1) * stride] = ((15 - (x + 1)) * tmp_left9 + (x + 1 + 1) * tmp_top9 + (15 - (y + 1)) * tmp_top10 + (y + 1 + 1) * tmp_left10 + 16) >> 5;
			tmp_left11 = left[y + 1 + 1];
			tmp_top11 = top[17];
			tmp_top12 = top[x + 2 + 1];
			tmp_left12 = left[17];
			src[x + 2 + (y + 1) * stride] = ((15 - (x + 2)) * tmp_left11 + (x + 2 + 1) * tmp_top11 + (15 - (y + 1)) * tmp_top12 + (y + 1 + 1) * tmp_left12 + 16) >> 5;
			tmp_left13 = left[y + 1 + 1];
			tmp_top13 = top[17];
			tmp_top14 = top[x + 3 + 1];
			tmp_left14 = left[17];
			src[x + 3 + (y + 1) * stride] = ((15 - (x + 3)) * tmp_left13 + (x + 3 + 1) * tmp_top13 + (15 - (y + 1)) * tmp_top14 + (y + 1 + 1) * tmp_left14 + 16) >> 5;
			x = x + 4;
		}
		x = 0;
		while (x < 16) {
			tmp_left15 = left[y + 2 + 1];
			tmp_top15 = top[17];
			tmp_top16 = top[x + 1];
			tmp_left16 = left[17];
			src[x + (y + 2) * stride] = ((15 - x) * tmp_left15 + (x + 1) * tmp_top15 + (15 - (y + 2)) * tmp_top16 + (y + 2 + 1) * tmp_left16 + 16) >> 5;
			tmp_left17 = left[y + 2 + 1];
			tmp_top17 = top[17];
			tmp_top18 = top[x + 1 + 1];
			tmp_left18 = left[17];
			src[x + 1 + (y + 2) * stride] = ((15 - (x + 1)) * tmp_left17 + (x + 1 + 1) * tmp_top17 + (15 - (y + 2)) * tmp_top18 + (y + 2 + 1) * tmp_left18 + 16) >> 5;
			tmp_left19 = left[y + 2 + 1];
			tmp_top19 = top[17];
			tmp_top20 = top[x + 2 + 1];
			tmp_left20 = left[17];
			src[x + 2 + (y + 2) * stride] = ((15 - (x + 2)) * tmp_left19 + (x + 2 + 1) * tmp_top19 + (15 - (y + 2)) * tmp_top20 + (y + 2 + 1) * tmp_left20 + 16) >> 5;
			tmp_left21 = left[y + 2 + 1];
			tmp_top21 = top[17];
			tmp_top22 = top[x + 3 + 1];
			tmp_left22 = left[17];
			src[x + 3 + (y + 2) * stride] = ((15 - (x + 3)) * tmp_left21 + (x + 3 + 1) * tmp_top21 + (15 - (y + 2)) * tmp_top22 + (y + 2 + 1) * tmp_left22 + 16) >> 5;
			x = x + 4;
		}
		x = 0;
		while (x < 16) {
			tmp_left23 = left[y + 3 + 1];
			tmp_top23 = top[17];
			tmp_top24 = top[x + 1];
			tmp_left24 = left[17];
			src[x + (y + 3) * stride] = ((15 - x) * tmp_left23 + (x + 1) * tmp_top23 + (15 - (y + 3)) * tmp_top24 + (y + 3 + 1) * tmp_left24 + 16) >> 5;
			tmp_left25 = left[y + 3 + 1];
			tmp_top25 = top[17];
			tmp_top26 = top[x + 1 + 1];
			tmp_left26 = left[17];
			src[x + 1 + (y + 3) * stride] = ((15 - (x + 1)) * tmp_left25 + (x + 1 + 1) * tmp_top25 + (15 - (y + 3)) * tmp_top26 + (y + 3 + 1) * tmp_left26 + 16) >> 5;
			tmp_left27 = left[y + 3 + 1];
			tmp_top27 = top[17];
			tmp_top28 = top[x + 2 + 1];
			tmp_left28 = left[17];
			src[x + 2 + (y + 3) * stride] = ((15 - (x + 2)) * tmp_left27 + (x + 2 + 1) * tmp_top27 + (15 - (y + 3)) * tmp_top28 + (y + 3 + 1) * tmp_left28 + 16) >> 5;
			tmp_left29 = left[y + 3 + 1];
			tmp_top29 = top[17];
			tmp_top30 = top[x + 3 + 1];
			tmp_left30 = left[17];
			src[x + 3 + (y + 3) * stride] = ((15 - (x + 3)) * tmp_left29 + (x + 3 + 1) * tmp_top29 + (15 - (y + 3)) * tmp_top30 + (y + 3 + 1) * tmp_left30 + 16) >> 5;
			x = x + 4;
		}
		x = 0;
		y = y + 4;
	}
}
static void HevcDecoder_IntraPrediction_intraPlanarPred1(u8 src[4096], u8 top[129], u8 left[129], i32 stride) {
	i32 y;
	i32 x;
	u8 tmp_left;
	u8 tmp_top;
	u8 tmp_top0;
	u8 tmp_left0;

	y = 0;
	while (y <= 8 - 1) {
		x = 0;
		while (x <= 8 - 1) {
			tmp_left = left[y + 1];
			tmp_top = top[9];
			tmp_top0 = top[x + 1];
			tmp_left0 = left[9];
			src[x + y * stride] = ((7 - x) * tmp_left + (x + 1) * tmp_top + (7 - y) * tmp_top0 + (y + 1) * tmp_left0 + 8) >> 4;
			x = x + 1;
		}
		y = y + 1;
	}
}
static void HevcDecoder_IntraPrediction_intraPlanarPred0(u8 src[4096], u8 top[129], u8 left[129], i32 stride) {
	i32 y;
	i32 x;
	u8 tmp_left;
	u8 tmp_top;
	u8 tmp_top0;
	u8 tmp_left0;

	y = 0;
	while (y <= 4 - 1) {
		x = 0;
		while (x <= 4 - 1) {
			tmp_left = left[y + 1];
			tmp_top = top[5];
			tmp_top0 = top[x + 1];
			tmp_left0 = left[5];
			src[x + y * stride] = ((3 - x) * tmp_left + (x + 1) * tmp_top + (3 - y) * tmp_top0 + (y + 1) * tmp_left0 + 4) >> 3;
			x = x + 1;
		}
		y = y + 1;
	}
}
static void HevcDecoder_IntraPrediction_intraPlanarPred(u8 src[4096], u8 top[129], u8 left[129], i32 stride, i32 log2Size) {
	#if defined(OPENHEVC_ENABLE)
	pred_planar_orcc(src, top, left, stride, log2Size);
	#else

	if (log2Size == 2) {
		HevcDecoder_IntraPrediction_intraPlanarPred0(src, top, left, stride);
	} else {
		if (log2Size == 3) {
			HevcDecoder_IntraPrediction_intraPlanarPred1(src, top, left, stride);
		} else {
			if (log2Size == 4) {
				HevcDecoder_IntraPrediction_intraPlanarPred2(src, top, left, stride);
			} else {
				HevcDecoder_IntraPrediction_intraPlanarPred3(src, top, left, stride);
			}
		}
	}
	#endif // defined(OPENHEVC_ENABLE)
}
static void HevcDecoder_IntraPrediction_intraAngularVertOrHor_chroma_3(i32 isVertical, u8 comp[4096], u8 pNeighb_above[129], u8 pNeighb_left[129], i32 stride) {
	u8 neighbIdx;
	i32 y;
	u32 x;
	u8 tmp_pNeighb_above;
	u8 tmp_pNeighb_above0;
	u8 tmp_pNeighb_above1;
	u8 tmp_pNeighb_above2;
	u8 tmp_pNeighb_left;
	u8 tmp_pNeighb_left0;
	u8 tmp_pNeighb_left1;
	u8 tmp_pNeighb_left2;

	if (isVertical) {
		neighbIdx = 0;
	} else {
		neighbIdx = 1;
	}
	y = 0;
	x = 0;
	while (x <= 32 - 1) {
		y = 0;
		while (y < 32) {
			if (neighbIdx == 0) {
				tmp_pNeighb_above = pNeighb_above[x + 1];
				comp[x + stride * y] = tmp_pNeighb_above;
				tmp_pNeighb_above0 = pNeighb_above[x + 1];
				comp[x + stride * (y + 1)] = tmp_pNeighb_above0;
				tmp_pNeighb_above1 = pNeighb_above[x + 1];
				comp[x + stride * (y + 2)] = tmp_pNeighb_above1;
				tmp_pNeighb_above2 = pNeighb_above[x + 1];
				comp[x + stride * (y + 3)] = tmp_pNeighb_above2;
			} else {
				tmp_pNeighb_left = pNeighb_left[x + 1];
				comp[y + stride * x] = tmp_pNeighb_left;
				tmp_pNeighb_left0 = pNeighb_left[x + 1];
				comp[y + 1 + stride * x] = tmp_pNeighb_left0;
				tmp_pNeighb_left1 = pNeighb_left[x + 1];
				comp[y + 2 + stride * x] = tmp_pNeighb_left1;
				tmp_pNeighb_left2 = pNeighb_left[x + 1];
				comp[y + 3 + stride * x] = tmp_pNeighb_left2;
			}
			y = y + 4;
		}
		x = x + 1;
	}
}
static i32 HevcDecoder_IntraPrediction_clip_i32(i32 Value, i32 minVal, i32 maxVal) {
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
static void HevcDecoder_IntraPrediction_intraAngularVertOrHor3(i32 isVertical, u8 comp[4096], u8 pNeighb_above[129], u8 pNeighb_left[129], i32 stride) {
	u8 minVal;
	i32 x;
	i32 y;
	u8 tmp_pNeighb_above;
	u8 tmp_pNeighb_left;
	u8 tmp_pNeighb_above0;
	i32 tmp_clip_i32;
	u8 tmp_pNeighb_above1;
	u8 tmp_pNeighb_left0;
	u8 tmp_pNeighb_above2;
	i32 tmp_clip_i320;
	u8 tmp_pNeighb_above3;
	u8 tmp_pNeighb_left1;
	u8 tmp_pNeighb_above4;
	i32 tmp_clip_i321;
	u8 tmp_pNeighb_above5;
	u8 tmp_pNeighb_left2;
	u8 tmp_pNeighb_above6;
	i32 tmp_clip_i322;
	u8 tmp_pNeighb_above7;
	u8 tmp_pNeighb_above8;
	u8 tmp_pNeighb_above9;
	u8 tmp_pNeighb_above10;
	u8 tmp_pNeighb_above11;
	u8 tmp_pNeighb_above12;
	u8 tmp_pNeighb_above13;
	u8 tmp_pNeighb_above14;
	u8 tmp_pNeighb_left3;
	u8 tmp_pNeighb_above15;
	u8 tmp_pNeighb_above16;
	i32 tmp_clip_i323;
	u8 tmp_pNeighb_left4;
	u8 tmp_pNeighb_above17;
	u8 tmp_pNeighb_above18;
	i32 tmp_clip_i324;
	u8 tmp_pNeighb_left5;
	u8 tmp_pNeighb_above19;
	u8 tmp_pNeighb_above20;
	i32 tmp_clip_i325;
	u8 tmp_pNeighb_left6;
	u8 tmp_pNeighb_above21;
	u8 tmp_pNeighb_above22;
	i32 tmp_clip_i326;
	u8 tmp_pNeighb_left7;
	u8 tmp_pNeighb_left8;
	u8 tmp_pNeighb_left9;
	u8 tmp_pNeighb_left10;
	u8 tmp_pNeighb_left11;

	x = 0;
	y = 0;
	if (32 > 16) {
		minVal = 0;
	} else {
		minVal = 1;
	}
	if (isVertical) {
		if (minVal != 0) {
			y = 0;
			while (y < 32) {
				tmp_pNeighb_above = pNeighb_above[0 + 1];
				tmp_pNeighb_left = pNeighb_left[y + 1];
				tmp_pNeighb_above0 = pNeighb_above[0];
				tmp_clip_i32 = HevcDecoder_IntraPrediction_clip_i32(tmp_pNeighb_above + ((tmp_pNeighb_left - tmp_pNeighb_above0) >> 1), 0, 255);
				comp[y * stride] = tmp_clip_i32;
				tmp_pNeighb_above1 = pNeighb_above[0 + 1];
				tmp_pNeighb_left0 = pNeighb_left[y + 1 + 1];
				tmp_pNeighb_above2 = pNeighb_above[0];
				tmp_clip_i320 = HevcDecoder_IntraPrediction_clip_i32(tmp_pNeighb_above1 + ((tmp_pNeighb_left0 - tmp_pNeighb_above2) >> 1), 0, 255);
				comp[(y + 1) * stride] = tmp_clip_i320;
				tmp_pNeighb_above3 = pNeighb_above[0 + 1];
				tmp_pNeighb_left1 = pNeighb_left[y + 2 + 1];
				tmp_pNeighb_above4 = pNeighb_above[0];
				tmp_clip_i321 = HevcDecoder_IntraPrediction_clip_i32(tmp_pNeighb_above3 + ((tmp_pNeighb_left1 - tmp_pNeighb_above4) >> 1), 0, 255);
				comp[(y + 2) * stride] = tmp_clip_i321;
				tmp_pNeighb_above5 = pNeighb_above[0 + 1];
				tmp_pNeighb_left2 = pNeighb_left[y + 3 + 1];
				tmp_pNeighb_above6 = pNeighb_above[0];
				tmp_clip_i322 = HevcDecoder_IntraPrediction_clip_i32(tmp_pNeighb_above5 + ((tmp_pNeighb_left2 - tmp_pNeighb_above6) >> 1), 0, 255);
				comp[(y + 3) * stride] = tmp_clip_i322;
				y = y + 4;
			}
			x = 1;
			while (x < 32) {
				y = 0;
				while (y < 32) {
					tmp_pNeighb_above7 = pNeighb_above[x + 1];
					comp[x + y * stride] = tmp_pNeighb_above7;
					tmp_pNeighb_above8 = pNeighb_above[x + 1];
					comp[x + (y + 1) * stride] = tmp_pNeighb_above8;
					tmp_pNeighb_above9 = pNeighb_above[x + 1];
					comp[x + (y + 2) * stride] = tmp_pNeighb_above9;
					tmp_pNeighb_above10 = pNeighb_above[x + 1];
					comp[x + (y + 3) * stride] = tmp_pNeighb_above10;
					y = y + 4;
				}
				x = x + 1;
			}
		} else {
			x = 0;
			while (x < 32) {
				y = 0;
				while (y < 32) {
					tmp_pNeighb_above11 = pNeighb_above[x + 1];
					comp[x + y * stride] = tmp_pNeighb_above11;
					tmp_pNeighb_above12 = pNeighb_above[x + 1];
					comp[x + (y + 1) * stride] = tmp_pNeighb_above12;
					tmp_pNeighb_above13 = pNeighb_above[x + 1];
					comp[x + (y + 2) * stride] = tmp_pNeighb_above13;
					tmp_pNeighb_above14 = pNeighb_above[x + 1];
					comp[x + (y + 3) * stride] = tmp_pNeighb_above14;
					y = y + 4;
				}
				x = x + 1;
			}
		}
	} else {
		if (minVal != 0) {
			x = 0;
			while (x < 32) {
				tmp_pNeighb_left3 = pNeighb_left[0 + 1];
				tmp_pNeighb_above15 = pNeighb_above[x + 1];
				tmp_pNeighb_above16 = pNeighb_above[0];
				tmp_clip_i323 = HevcDecoder_IntraPrediction_clip_i32(tmp_pNeighb_left3 + ((tmp_pNeighb_above15 - tmp_pNeighb_above16) >> 1), 0, 255);
				comp[x] = tmp_clip_i323;
				tmp_pNeighb_left4 = pNeighb_left[0 + 1];
				tmp_pNeighb_above17 = pNeighb_above[x + 1 + 1];
				tmp_pNeighb_above18 = pNeighb_above[0];
				tmp_clip_i324 = HevcDecoder_IntraPrediction_clip_i32(tmp_pNeighb_left4 + ((tmp_pNeighb_above17 - tmp_pNeighb_above18) >> 1), 0, 255);
				comp[x + 1] = tmp_clip_i324;
				tmp_pNeighb_left5 = pNeighb_left[0 + 1];
				tmp_pNeighb_above19 = pNeighb_above[x + 2 + 1];
				tmp_pNeighb_above20 = pNeighb_above[0];
				tmp_clip_i325 = HevcDecoder_IntraPrediction_clip_i32(tmp_pNeighb_left5 + ((tmp_pNeighb_above19 - tmp_pNeighb_above20) >> 1), 0, 255);
				comp[x + 2] = tmp_clip_i325;
				tmp_pNeighb_left6 = pNeighb_left[0 + 1];
				tmp_pNeighb_above21 = pNeighb_above[x + 3 + 1];
				tmp_pNeighb_above22 = pNeighb_above[0];
				tmp_clip_i326 = HevcDecoder_IntraPrediction_clip_i32(tmp_pNeighb_left6 + ((tmp_pNeighb_above21 - tmp_pNeighb_above22) >> 1), 0, 255);
				comp[x + 3] = tmp_clip_i326;
				x = x + 4;
			}
			x = 0;
			while (x < 32) {
				y = 1;
				while (y < 32) {
					tmp_pNeighb_left7 = pNeighb_left[y + 1];
					comp[x + y * stride] = tmp_pNeighb_left7;
					y = y + 1;
				}
				x = x + 1;
			}
		} else {
			while (x < 32) {
				y = 0;
				while (y < 32) {
					tmp_pNeighb_left8 = pNeighb_left[y + 1];
					comp[x + y * stride] = tmp_pNeighb_left8;
					tmp_pNeighb_left9 = pNeighb_left[y + 1 + 1];
					comp[x + (y + 1) * stride] = tmp_pNeighb_left9;
					tmp_pNeighb_left10 = pNeighb_left[y + 2 + 1];
					comp[x + (y + 2) * stride] = tmp_pNeighb_left10;
					tmp_pNeighb_left11 = pNeighb_left[y + 3 + 1];
					comp[x + (y + 3) * stride] = tmp_pNeighb_left11;
					y = y + 4;
				}
				x = x + 1;
			}
		}
	}
}
static void HevcDecoder_IntraPrediction_intraAngularPred3(u8 comp[4096], u8 pNeighb_above[129], u8 pNeighb_left[129], i32 stride, i32 idx, u8 mode) {
	u8 OFFSET;
	u8 angle;
	u8 refMain[161];
	i16 iIdx;
	u8 iFact;
	i32 x;
	u8 tmp_pNeighb_above;
	u8 tmp_pNeighb_above0;
	u8 tmp_pNeighb_above1;
	u8 tmp_pNeighb_above2;
	u8 tmp_pNeighb_above3;
	i8 tmp_intraPredAngle;
	i32 k;
	i8 tmp_intraPredAngle0;
	i16 tmp_invAngle;
	u8 tmp_pNeighb_left;
	u8 tmp_pNeighb_above4;
	u8 tmp_pNeighb_above5;
	u8 tmp_pNeighb_above6;
	u8 tmp_pNeighb_above7;
	u8 tmp_pNeighb_above8;
	u8 tmp_pNeighb_left0;
	u8 tmp_pNeighb_left1;
	u8 tmp_pNeighb_left2;
	u8 tmp_pNeighb_left3;
	i8 tmp_intraPredAngle1;
	i32 k0;
	i8 tmp_intraPredAngle2;
	i16 tmp_invAngle0;
	u8 tmp_pNeighb_above9;
	u8 tmp_pNeighb_left4;
	u8 tmp_pNeighb_left5;
	u8 tmp_pNeighb_left6;
	u8 tmp_pNeighb_left7;
	u32 y;
	i8 tmp_intraPredAngle3;
	i8 tmp_intraPredAngle4;
	u8 tmp_refMain;
	u8 tmp_refMain0;
	u8 tmp_refMain1;
	u8 tmp_refMain2;
	u8 tmp_refMain3;
	u8 tmp_refMain4;
	u8 tmp_refMain5;
	u8 tmp_refMain6;
	u8 tmp_refMain7;
	u8 tmp_refMain8;
	u8 tmp_refMain9;
	u8 tmp_refMain10;
	u32 y0;
	i8 tmp_intraPredAngle5;
	i8 tmp_intraPredAngle6;
	u8 tmp_refMain11;
	u8 tmp_refMain12;
	u8 tmp_refMain13;
	u8 tmp_refMain14;
	u8 tmp_refMain15;
	u8 tmp_refMain16;
	u8 tmp_refMain17;
	u8 tmp_refMain18;
	u8 tmp_refMain19;
	u8 tmp_refMain20;
	u8 tmp_refMain21;
	u8 tmp_refMain22;

	OFFSET = 33;
	angle = mode & 63;
	x = 0;
	if (angle == 26 || angle == 10) {
		if (idx == 0) {
			HevcDecoder_IntraPrediction_intraAngularVertOrHor3(angle == 26, comp, pNeighb_above, pNeighb_left, stride);
		} else {
			HevcDecoder_IntraPrediction_intraAngularVertOrHor_chroma_3(angle == 26, comp, pNeighb_above, pNeighb_left, stride);
		}
	} else {
		if (angle >= 18) {
			tmp_pNeighb_above = pNeighb_above[0];
			refMain[OFFSET] = tmp_pNeighb_above;
			x = 1;
			while (x <= 32) {
				tmp_pNeighb_above0 = pNeighb_above[x - 1 + 1];
				refMain[x + OFFSET] = tmp_pNeighb_above0;
				tmp_pNeighb_above1 = pNeighb_above[x + 1 - 1 + 1];
				refMain[x + 1 + OFFSET] = tmp_pNeighb_above1;
				tmp_pNeighb_above2 = pNeighb_above[x + 2 - 1 + 1];
				refMain[x + 2 + OFFSET] = tmp_pNeighb_above2;
				tmp_pNeighb_above3 = pNeighb_above[x + 3 - 1 + 1];
				refMain[x + 3 + OFFSET] = tmp_pNeighb_above3;
				x = x + 4;
			}
			tmp_intraPredAngle = HevcDecoder_IntraPrediction_intraPredAngle[angle];
			if (tmp_intraPredAngle < 0) {
				tmp_intraPredAngle0 = HevcDecoder_IntraPrediction_intraPredAngle[angle];
				k = (32 * tmp_intraPredAngle0) >> 5;
				while (k <= -1) {
					tmp_invAngle = HevcDecoder_IntraPrediction_invAngle[angle];
					tmp_pNeighb_left = pNeighb_left[((k * tmp_invAngle + 128) >> 8) - 1 + 1];
					refMain[k + OFFSET] = tmp_pNeighb_left;
					k = k + 1;
				}
			} else {
				x = 33;
				while (x <= 64) {
					tmp_pNeighb_above4 = pNeighb_above[x - 1 + 1];
					refMain[x + OFFSET] = tmp_pNeighb_above4;
					tmp_pNeighb_above5 = pNeighb_above[x + 1 - 1 + 1];
					refMain[x + 1 + OFFSET] = tmp_pNeighb_above5;
					tmp_pNeighb_above6 = pNeighb_above[x + 2 - 1 + 1];
					refMain[x + 2 + OFFSET] = tmp_pNeighb_above6;
					tmp_pNeighb_above7 = pNeighb_above[x + 3 - 1 + 1];
					refMain[x + 3 + OFFSET] = tmp_pNeighb_above7;
					x = x + 4;
				}
			}
		} else {
			tmp_pNeighb_above8 = pNeighb_above[0];
			refMain[OFFSET] = tmp_pNeighb_above8;
			x = 1;
			while (x <= 32) {
				tmp_pNeighb_left0 = pNeighb_left[x - 1 + 1];
				refMain[x + OFFSET] = tmp_pNeighb_left0;
				tmp_pNeighb_left1 = pNeighb_left[x + 1 - 1 + 1];
				refMain[x + 1 + OFFSET] = tmp_pNeighb_left1;
				tmp_pNeighb_left2 = pNeighb_left[x + 2 - 1 + 1];
				refMain[x + 2 + OFFSET] = tmp_pNeighb_left2;
				tmp_pNeighb_left3 = pNeighb_left[x + 3 - 1 + 1];
				refMain[x + 3 + OFFSET] = tmp_pNeighb_left3;
				x = x + 4;
			}
			tmp_intraPredAngle1 = HevcDecoder_IntraPrediction_intraPredAngle[angle];
			if (tmp_intraPredAngle1 < 0) {
				tmp_intraPredAngle2 = HevcDecoder_IntraPrediction_intraPredAngle[angle];
				k0 = (32 * tmp_intraPredAngle2) >> 5;
				while (k0 <= -1) {
					tmp_invAngle0 = HevcDecoder_IntraPrediction_invAngle[angle];
					tmp_pNeighb_above9 = pNeighb_above[((k0 * tmp_invAngle0 + 128) >> 8) - 1 + 1];
					refMain[k0 + OFFSET] = tmp_pNeighb_above9;
					k0 = k0 + 1;
				}
			} else {
				x = 33;
				while (x <= 64) {
					tmp_pNeighb_left4 = pNeighb_left[x - 1 + 1];
					refMain[x + OFFSET] = tmp_pNeighb_left4;
					tmp_pNeighb_left5 = pNeighb_left[x + 1 - 1 + 1];
					refMain[x + 1 + OFFSET] = tmp_pNeighb_left5;
					tmp_pNeighb_left6 = pNeighb_left[x + 2 - 1 + 1];
					refMain[x + 2 + OFFSET] = tmp_pNeighb_left6;
					tmp_pNeighb_left7 = pNeighb_left[x + 3 - 1 + 1];
					refMain[x + 3 + OFFSET] = tmp_pNeighb_left7;
					x = x + 4;
				}
			}
		}
		if (angle >= 18) {
			y = 0;
			while (y <= 32 - 1) {
				tmp_intraPredAngle3 = HevcDecoder_IntraPrediction_intraPredAngle[angle];
				iIdx = ((y + 1) * tmp_intraPredAngle3) >> 5;
				tmp_intraPredAngle4 = HevcDecoder_IntraPrediction_intraPredAngle[angle];
				iFact = (y + 1) * tmp_intraPredAngle4 & 31;
				x = 0;
				while (x < 32) {
					if (iFact != 0) {
						tmp_refMain = refMain[x + iIdx + 1 + OFFSET];
						tmp_refMain0 = refMain[x + iIdx + 2 + OFFSET];
						comp[x + y * stride] = ((32 - iFact) * tmp_refMain + iFact * tmp_refMain0 + 16) >> 5;
						tmp_refMain1 = refMain[x + 1 + iIdx + 1 + OFFSET];
						tmp_refMain2 = refMain[x + 1 + iIdx + 2 + OFFSET];
						comp[x + 1 + y * stride] = ((32 - iFact) * tmp_refMain1 + iFact * tmp_refMain2 + 16) >> 5;
						tmp_refMain3 = refMain[x + 2 + iIdx + 1 + OFFSET];
						tmp_refMain4 = refMain[x + 2 + iIdx + 2 + OFFSET];
						comp[x + 2 + y * stride] = ((32 - iFact) * tmp_refMain3 + iFact * tmp_refMain4 + 16) >> 5;
						tmp_refMain5 = refMain[x + 3 + iIdx + 1 + OFFSET];
						tmp_refMain6 = refMain[x + 3 + iIdx + 2 + OFFSET];
						comp[x + 3 + y * stride] = ((32 - iFact) * tmp_refMain5 + iFact * tmp_refMain6 + 16) >> 5;
					} else {
						tmp_refMain7 = refMain[x + iIdx + 1 + OFFSET];
						comp[x + y * stride] = tmp_refMain7;
						tmp_refMain8 = refMain[x + 1 + iIdx + 1 + OFFSET];
						comp[x + 1 + y * stride] = tmp_refMain8;
						tmp_refMain9 = refMain[x + 2 + iIdx + 1 + OFFSET];
						comp[x + 2 + y * stride] = tmp_refMain9;
						tmp_refMain10 = refMain[x + 3 + iIdx + 1 + OFFSET];
						comp[x + 3 + y * stride] = tmp_refMain10;
					}
					x = x + 4;
				}
				y = y + 1;
			}
		} else {
			y0 = 0;
			while (y0 <= 32 - 1) {
				tmp_intraPredAngle5 = HevcDecoder_IntraPrediction_intraPredAngle[angle];
				iIdx = ((y0 + 1) * tmp_intraPredAngle5) >> 5;
				tmp_intraPredAngle6 = HevcDecoder_IntraPrediction_intraPredAngle[angle];
				iFact = (y0 + 1) * tmp_intraPredAngle6 & 31;
				x = 0;
				while (x < 32) {
					if (iFact != 0) {
						tmp_refMain11 = refMain[x + iIdx + 1 + OFFSET];
						tmp_refMain12 = refMain[x + iIdx + 2 + OFFSET];
						comp[y0 + x * stride] = ((32 - iFact) * tmp_refMain11 + iFact * tmp_refMain12 + 16) >> 5;
						tmp_refMain13 = refMain[x + 1 + iIdx + 1 + OFFSET];
						tmp_refMain14 = refMain[x + 1 + iIdx + 2 + OFFSET];
						comp[y0 + (x + 1) * stride] = ((32 - iFact) * tmp_refMain13 + iFact * tmp_refMain14 + 16) >> 5;
						tmp_refMain15 = refMain[x + 2 + iIdx + 1 + OFFSET];
						tmp_refMain16 = refMain[x + 2 + iIdx + 2 + OFFSET];
						comp[y0 + (x + 2) * stride] = ((32 - iFact) * tmp_refMain15 + iFact * tmp_refMain16 + 16) >> 5;
						tmp_refMain17 = refMain[x + 3 + iIdx + 1 + OFFSET];
						tmp_refMain18 = refMain[x + 3 + iIdx + 2 + OFFSET];
						comp[y0 + (x + 3) * stride] = ((32 - iFact) * tmp_refMain17 + iFact * tmp_refMain18 + 16) >> 5;
					} else {
						tmp_refMain19 = refMain[x + iIdx + 1 + OFFSET];
						comp[y0 + x * stride] = tmp_refMain19;
						tmp_refMain20 = refMain[x + 1 + iIdx + 1 + OFFSET];
						comp[y0 + (x + 1) * stride] = tmp_refMain20;
						tmp_refMain21 = refMain[x + 2 + iIdx + 1 + OFFSET];
						comp[y0 + (x + 2) * stride] = tmp_refMain21;
						tmp_refMain22 = refMain[x + 3 + iIdx + 1 + OFFSET];
						comp[y0 + (x + 3) * stride] = tmp_refMain22;
					}
					x = x + 4;
				}
				y0 = y0 + 1;
			}
		}
	}
}
static void HevcDecoder_IntraPrediction_intraAngularVertOrHor_chroma_2(i32 isVertical, u8 comp[4096], u8 pNeighb_above[129], u8 pNeighb_left[129], i32 stride) {
	u8 neighbIdx;
	i32 y;
	u32 x;
	u8 tmp_pNeighb_above;
	u8 tmp_pNeighb_above0;
	u8 tmp_pNeighb_above1;
	u8 tmp_pNeighb_above2;
	u8 tmp_pNeighb_left;
	u8 tmp_pNeighb_left0;
	u8 tmp_pNeighb_left1;
	u8 tmp_pNeighb_left2;

	if (isVertical) {
		neighbIdx = 0;
	} else {
		neighbIdx = 1;
	}
	y = 0;
	x = 0;
	while (x <= 16 - 1) {
		y = 0;
		while (y < 16) {
			if (neighbIdx == 0) {
				tmp_pNeighb_above = pNeighb_above[x + 1];
				comp[x + stride * y] = tmp_pNeighb_above;
				tmp_pNeighb_above0 = pNeighb_above[x + 1];
				comp[x + stride * (y + 1)] = tmp_pNeighb_above0;
				tmp_pNeighb_above1 = pNeighb_above[x + 1];
				comp[x + stride * (y + 2)] = tmp_pNeighb_above1;
				tmp_pNeighb_above2 = pNeighb_above[x + 1];
				comp[x + stride * (y + 3)] = tmp_pNeighb_above2;
			} else {
				tmp_pNeighb_left = pNeighb_left[x + 1];
				comp[y + stride * x] = tmp_pNeighb_left;
				tmp_pNeighb_left0 = pNeighb_left[x + 1];
				comp[y + 1 + stride * x] = tmp_pNeighb_left0;
				tmp_pNeighb_left1 = pNeighb_left[x + 1];
				comp[y + 2 + stride * x] = tmp_pNeighb_left1;
				tmp_pNeighb_left2 = pNeighb_left[x + 1];
				comp[y + 3 + stride * x] = tmp_pNeighb_left2;
			}
			y = y + 4;
		}
		x = x + 1;
	}
}
static void HevcDecoder_IntraPrediction_intraAngularVertOrHor2(i32 isVertical, u8 comp[4096], u8 pNeighb_above[129], u8 pNeighb_left[129], i32 stride) {
	u8 minVal;
	i32 x;
	i32 y;
	u8 tmp_pNeighb_above;
	u8 tmp_pNeighb_left;
	u8 tmp_pNeighb_above0;
	i32 tmp_clip_i32;
	u8 tmp_pNeighb_above1;
	u8 tmp_pNeighb_left0;
	u8 tmp_pNeighb_above2;
	i32 tmp_clip_i320;
	u8 tmp_pNeighb_above3;
	u8 tmp_pNeighb_left1;
	u8 tmp_pNeighb_above4;
	i32 tmp_clip_i321;
	u8 tmp_pNeighb_above5;
	u8 tmp_pNeighb_left2;
	u8 tmp_pNeighb_above6;
	i32 tmp_clip_i322;
	u8 tmp_pNeighb_above7;
	u8 tmp_pNeighb_above8;
	u8 tmp_pNeighb_above9;
	u8 tmp_pNeighb_above10;
	u8 tmp_pNeighb_above11;
	u8 tmp_pNeighb_above12;
	u8 tmp_pNeighb_above13;
	u8 tmp_pNeighb_above14;
	u8 tmp_pNeighb_left3;
	u8 tmp_pNeighb_above15;
	u8 tmp_pNeighb_above16;
	i32 tmp_clip_i323;
	u8 tmp_pNeighb_left4;
	u8 tmp_pNeighb_above17;
	u8 tmp_pNeighb_above18;
	i32 tmp_clip_i324;
	u8 tmp_pNeighb_left5;
	u8 tmp_pNeighb_above19;
	u8 tmp_pNeighb_above20;
	i32 tmp_clip_i325;
	u8 tmp_pNeighb_left6;
	u8 tmp_pNeighb_above21;
	u8 tmp_pNeighb_above22;
	i32 tmp_clip_i326;
	u8 tmp_pNeighb_left7;
	u8 tmp_pNeighb_left8;
	u8 tmp_pNeighb_left9;
	u8 tmp_pNeighb_left10;
	u8 tmp_pNeighb_left11;

	x = 0;
	y = 0;
	if (16 > 16) {
		minVal = 0;
	} else {
		minVal = 1;
	}
	if (isVertical) {
		if (minVal != 0) {
			y = 0;
			while (y < 16) {
				tmp_pNeighb_above = pNeighb_above[0 + 1];
				tmp_pNeighb_left = pNeighb_left[y + 1];
				tmp_pNeighb_above0 = pNeighb_above[0];
				tmp_clip_i32 = HevcDecoder_IntraPrediction_clip_i32(tmp_pNeighb_above + ((tmp_pNeighb_left - tmp_pNeighb_above0) >> 1), 0, 255);
				comp[y * stride] = tmp_clip_i32;
				tmp_pNeighb_above1 = pNeighb_above[0 + 1];
				tmp_pNeighb_left0 = pNeighb_left[y + 1 + 1];
				tmp_pNeighb_above2 = pNeighb_above[0];
				tmp_clip_i320 = HevcDecoder_IntraPrediction_clip_i32(tmp_pNeighb_above1 + ((tmp_pNeighb_left0 - tmp_pNeighb_above2) >> 1), 0, 255);
				comp[(y + 1) * stride] = tmp_clip_i320;
				tmp_pNeighb_above3 = pNeighb_above[0 + 1];
				tmp_pNeighb_left1 = pNeighb_left[y + 2 + 1];
				tmp_pNeighb_above4 = pNeighb_above[0];
				tmp_clip_i321 = HevcDecoder_IntraPrediction_clip_i32(tmp_pNeighb_above3 + ((tmp_pNeighb_left1 - tmp_pNeighb_above4) >> 1), 0, 255);
				comp[(y + 2) * stride] = tmp_clip_i321;
				tmp_pNeighb_above5 = pNeighb_above[0 + 1];
				tmp_pNeighb_left2 = pNeighb_left[y + 3 + 1];
				tmp_pNeighb_above6 = pNeighb_above[0];
				tmp_clip_i322 = HevcDecoder_IntraPrediction_clip_i32(tmp_pNeighb_above5 + ((tmp_pNeighb_left2 - tmp_pNeighb_above6) >> 1), 0, 255);
				comp[(y + 3) * stride] = tmp_clip_i322;
				y = y + 4;
			}
			x = 1;
			while (x < 16) {
				y = 0;
				while (y < 16) {
					tmp_pNeighb_above7 = pNeighb_above[x + 1];
					comp[x + y * stride] = tmp_pNeighb_above7;
					tmp_pNeighb_above8 = pNeighb_above[x + 1];
					comp[x + (y + 1) * stride] = tmp_pNeighb_above8;
					tmp_pNeighb_above9 = pNeighb_above[x + 1];
					comp[x + (y + 2) * stride] = tmp_pNeighb_above9;
					tmp_pNeighb_above10 = pNeighb_above[x + 1];
					comp[x + (y + 3) * stride] = tmp_pNeighb_above10;
					y = y + 4;
				}
				x = x + 1;
			}
		} else {
			x = 0;
			while (x < 16) {
				y = 0;
				while (y < 16) {
					tmp_pNeighb_above11 = pNeighb_above[x + 1];
					comp[x + y * stride] = tmp_pNeighb_above11;
					tmp_pNeighb_above12 = pNeighb_above[x + 1];
					comp[x + (y + 1) * stride] = tmp_pNeighb_above12;
					tmp_pNeighb_above13 = pNeighb_above[x + 1];
					comp[x + (y + 2) * stride] = tmp_pNeighb_above13;
					tmp_pNeighb_above14 = pNeighb_above[x + 1];
					comp[x + (y + 3) * stride] = tmp_pNeighb_above14;
					y = y + 4;
				}
				x = x + 1;
			}
		}
	} else {
		if (minVal != 0) {
			x = 0;
			while (x < 16) {
				tmp_pNeighb_left3 = pNeighb_left[0 + 1];
				tmp_pNeighb_above15 = pNeighb_above[x + 1];
				tmp_pNeighb_above16 = pNeighb_above[0];
				tmp_clip_i323 = HevcDecoder_IntraPrediction_clip_i32(tmp_pNeighb_left3 + ((tmp_pNeighb_above15 - tmp_pNeighb_above16) >> 1), 0, 255);
				comp[x] = tmp_clip_i323;
				tmp_pNeighb_left4 = pNeighb_left[0 + 1];
				tmp_pNeighb_above17 = pNeighb_above[x + 1 + 1];
				tmp_pNeighb_above18 = pNeighb_above[0];
				tmp_clip_i324 = HevcDecoder_IntraPrediction_clip_i32(tmp_pNeighb_left4 + ((tmp_pNeighb_above17 - tmp_pNeighb_above18) >> 1), 0, 255);
				comp[x + 1] = tmp_clip_i324;
				tmp_pNeighb_left5 = pNeighb_left[0 + 1];
				tmp_pNeighb_above19 = pNeighb_above[x + 2 + 1];
				tmp_pNeighb_above20 = pNeighb_above[0];
				tmp_clip_i325 = HevcDecoder_IntraPrediction_clip_i32(tmp_pNeighb_left5 + ((tmp_pNeighb_above19 - tmp_pNeighb_above20) >> 1), 0, 255);
				comp[x + 2] = tmp_clip_i325;
				tmp_pNeighb_left6 = pNeighb_left[0 + 1];
				tmp_pNeighb_above21 = pNeighb_above[x + 3 + 1];
				tmp_pNeighb_above22 = pNeighb_above[0];
				tmp_clip_i326 = HevcDecoder_IntraPrediction_clip_i32(tmp_pNeighb_left6 + ((tmp_pNeighb_above21 - tmp_pNeighb_above22) >> 1), 0, 255);
				comp[x + 3] = tmp_clip_i326;
				x = x + 4;
			}
			x = 0;
			while (x < 16) {
				y = 1;
				while (y < 16) {
					tmp_pNeighb_left7 = pNeighb_left[y + 1];
					comp[x + y * stride] = tmp_pNeighb_left7;
					y = y + 1;
				}
				x = x + 1;
			}
		} else {
			while (x < 16) {
				y = 0;
				while (y < 16) {
					tmp_pNeighb_left8 = pNeighb_left[y + 1];
					comp[x + y * stride] = tmp_pNeighb_left8;
					tmp_pNeighb_left9 = pNeighb_left[y + 1 + 1];
					comp[x + (y + 1) * stride] = tmp_pNeighb_left9;
					tmp_pNeighb_left10 = pNeighb_left[y + 2 + 1];
					comp[x + (y + 2) * stride] = tmp_pNeighb_left10;
					tmp_pNeighb_left11 = pNeighb_left[y + 3 + 1];
					comp[x + (y + 3) * stride] = tmp_pNeighb_left11;
					y = y + 4;
				}
				x = x + 1;
			}
		}
	}
}
static void HevcDecoder_IntraPrediction_intraAngularPred2(u8 comp[4096], u8 pNeighb_above[129], u8 pNeighb_left[129], i32 stride, i32 idx, u8 mode) {
	u8 OFFSET;
	u8 angle;
	u8 refMain[161];
	i16 iIdx;
	u8 iFact;
	i32 x;
	u8 tmp_pNeighb_above;
	u8 tmp_pNeighb_above0;
	u8 tmp_pNeighb_above1;
	u8 tmp_pNeighb_above2;
	u8 tmp_pNeighb_above3;
	i8 tmp_intraPredAngle;
	i32 k;
	i8 tmp_intraPredAngle0;
	i16 tmp_invAngle;
	u8 tmp_pNeighb_left;
	u8 tmp_pNeighb_above4;
	u8 tmp_pNeighb_above5;
	u8 tmp_pNeighb_above6;
	u8 tmp_pNeighb_above7;
	u8 tmp_pNeighb_above8;
	u8 tmp_pNeighb_left0;
	u8 tmp_pNeighb_left1;
	u8 tmp_pNeighb_left2;
	u8 tmp_pNeighb_left3;
	i8 tmp_intraPredAngle1;
	i32 k0;
	i8 tmp_intraPredAngle2;
	i16 tmp_invAngle0;
	u8 tmp_pNeighb_above9;
	u8 tmp_pNeighb_left4;
	u8 tmp_pNeighb_left5;
	u8 tmp_pNeighb_left6;
	u8 tmp_pNeighb_left7;
	u32 y;
	i8 tmp_intraPredAngle3;
	i8 tmp_intraPredAngle4;
	u8 tmp_refMain;
	u8 tmp_refMain0;
	u8 tmp_refMain1;
	u8 tmp_refMain2;
	u8 tmp_refMain3;
	u8 tmp_refMain4;
	u8 tmp_refMain5;
	u8 tmp_refMain6;
	u8 tmp_refMain7;
	u8 tmp_refMain8;
	u8 tmp_refMain9;
	u8 tmp_refMain10;
	u32 y0;
	i8 tmp_intraPredAngle5;
	i8 tmp_intraPredAngle6;
	u8 tmp_refMain11;
	u8 tmp_refMain12;
	u8 tmp_refMain13;
	u8 tmp_refMain14;
	u8 tmp_refMain15;
	u8 tmp_refMain16;
	u8 tmp_refMain17;
	u8 tmp_refMain18;
	u8 tmp_refMain19;
	u8 tmp_refMain20;
	u8 tmp_refMain21;
	u8 tmp_refMain22;

	OFFSET = 33;
	angle = mode & 63;
	x = 0;
	if (angle == 26 || angle == 10) {
		if (idx == 0) {
			HevcDecoder_IntraPrediction_intraAngularVertOrHor2(angle == 26, comp, pNeighb_above, pNeighb_left, stride);
		} else {
			HevcDecoder_IntraPrediction_intraAngularVertOrHor_chroma_2(angle == 26, comp, pNeighb_above, pNeighb_left, stride);
		}
	} else {
		if (angle >= 18) {
			tmp_pNeighb_above = pNeighb_above[0];
			refMain[OFFSET] = tmp_pNeighb_above;
			x = 1;
			while (x <= 16) {
				tmp_pNeighb_above0 = pNeighb_above[x - 1 + 1];
				refMain[x + OFFSET] = tmp_pNeighb_above0;
				tmp_pNeighb_above1 = pNeighb_above[x + 1 - 1 + 1];
				refMain[x + 1 + OFFSET] = tmp_pNeighb_above1;
				tmp_pNeighb_above2 = pNeighb_above[x + 2 - 1 + 1];
				refMain[x + 2 + OFFSET] = tmp_pNeighb_above2;
				tmp_pNeighb_above3 = pNeighb_above[x + 3 - 1 + 1];
				refMain[x + 3 + OFFSET] = tmp_pNeighb_above3;
				x = x + 4;
			}
			tmp_intraPredAngle = HevcDecoder_IntraPrediction_intraPredAngle[angle];
			if (tmp_intraPredAngle < 0) {
				tmp_intraPredAngle0 = HevcDecoder_IntraPrediction_intraPredAngle[angle];
				k = (16 * tmp_intraPredAngle0) >> 5;
				while (k <= -1) {
					tmp_invAngle = HevcDecoder_IntraPrediction_invAngle[angle];
					tmp_pNeighb_left = pNeighb_left[((k * tmp_invAngle + 128) >> 8) - 1 + 1];
					refMain[k + OFFSET] = tmp_pNeighb_left;
					k = k + 1;
				}
			} else {
				x = 17;
				while (x <= 32) {
					tmp_pNeighb_above4 = pNeighb_above[x - 1 + 1];
					refMain[x + OFFSET] = tmp_pNeighb_above4;
					tmp_pNeighb_above5 = pNeighb_above[x + 1 - 1 + 1];
					refMain[x + 1 + OFFSET] = tmp_pNeighb_above5;
					tmp_pNeighb_above6 = pNeighb_above[x + 2 - 1 + 1];
					refMain[x + 2 + OFFSET] = tmp_pNeighb_above6;
					tmp_pNeighb_above7 = pNeighb_above[x + 3 - 1 + 1];
					refMain[x + 3 + OFFSET] = tmp_pNeighb_above7;
					x = x + 4;
				}
			}
		} else {
			tmp_pNeighb_above8 = pNeighb_above[0];
			refMain[OFFSET] = tmp_pNeighb_above8;
			x = 1;
			while (x <= 16) {
				tmp_pNeighb_left0 = pNeighb_left[x - 1 + 1];
				refMain[x + OFFSET] = tmp_pNeighb_left0;
				tmp_pNeighb_left1 = pNeighb_left[x + 1 - 1 + 1];
				refMain[x + 1 + OFFSET] = tmp_pNeighb_left1;
				tmp_pNeighb_left2 = pNeighb_left[x + 2 - 1 + 1];
				refMain[x + 2 + OFFSET] = tmp_pNeighb_left2;
				tmp_pNeighb_left3 = pNeighb_left[x + 3 - 1 + 1];
				refMain[x + 3 + OFFSET] = tmp_pNeighb_left3;
				x = x + 4;
			}
			tmp_intraPredAngle1 = HevcDecoder_IntraPrediction_intraPredAngle[angle];
			if (tmp_intraPredAngle1 < 0) {
				tmp_intraPredAngle2 = HevcDecoder_IntraPrediction_intraPredAngle[angle];
				k0 = (16 * tmp_intraPredAngle2) >> 5;
				while (k0 <= -1) {
					tmp_invAngle0 = HevcDecoder_IntraPrediction_invAngle[angle];
					tmp_pNeighb_above9 = pNeighb_above[((k0 * tmp_invAngle0 + 128) >> 8) - 1 + 1];
					refMain[k0 + OFFSET] = tmp_pNeighb_above9;
					k0 = k0 + 1;
				}
			} else {
				x = 17;
				while (x <= 32) {
					tmp_pNeighb_left4 = pNeighb_left[x - 1 + 1];
					refMain[x + OFFSET] = tmp_pNeighb_left4;
					tmp_pNeighb_left5 = pNeighb_left[x + 1 - 1 + 1];
					refMain[x + 1 + OFFSET] = tmp_pNeighb_left5;
					tmp_pNeighb_left6 = pNeighb_left[x + 2 - 1 + 1];
					refMain[x + 2 + OFFSET] = tmp_pNeighb_left6;
					tmp_pNeighb_left7 = pNeighb_left[x + 3 - 1 + 1];
					refMain[x + 3 + OFFSET] = tmp_pNeighb_left7;
					x = x + 4;
				}
			}
		}
		if (angle >= 18) {
			y = 0;
			while (y <= 16 - 1) {
				tmp_intraPredAngle3 = HevcDecoder_IntraPrediction_intraPredAngle[angle];
				iIdx = ((y + 1) * tmp_intraPredAngle3) >> 5;
				tmp_intraPredAngle4 = HevcDecoder_IntraPrediction_intraPredAngle[angle];
				iFact = (y + 1) * tmp_intraPredAngle4 & 31;
				x = 0;
				while (x < 16) {
					if (iFact != 0) {
						tmp_refMain = refMain[x + iIdx + 1 + OFFSET];
						tmp_refMain0 = refMain[x + iIdx + 2 + OFFSET];
						comp[x + y * stride] = ((32 - iFact) * tmp_refMain + iFact * tmp_refMain0 + 16) >> 5;
						tmp_refMain1 = refMain[x + 1 + iIdx + 1 + OFFSET];
						tmp_refMain2 = refMain[x + 1 + iIdx + 2 + OFFSET];
						comp[x + 1 + y * stride] = ((32 - iFact) * tmp_refMain1 + iFact * tmp_refMain2 + 16) >> 5;
						tmp_refMain3 = refMain[x + 2 + iIdx + 1 + OFFSET];
						tmp_refMain4 = refMain[x + 2 + iIdx + 2 + OFFSET];
						comp[x + 2 + y * stride] = ((32 - iFact) * tmp_refMain3 + iFact * tmp_refMain4 + 16) >> 5;
						tmp_refMain5 = refMain[x + 3 + iIdx + 1 + OFFSET];
						tmp_refMain6 = refMain[x + 3 + iIdx + 2 + OFFSET];
						comp[x + 3 + y * stride] = ((32 - iFact) * tmp_refMain5 + iFact * tmp_refMain6 + 16) >> 5;
					} else {
						tmp_refMain7 = refMain[x + iIdx + 1 + OFFSET];
						comp[x + y * stride] = tmp_refMain7;
						tmp_refMain8 = refMain[x + 1 + iIdx + 1 + OFFSET];
						comp[x + 1 + y * stride] = tmp_refMain8;
						tmp_refMain9 = refMain[x + 2 + iIdx + 1 + OFFSET];
						comp[x + 2 + y * stride] = tmp_refMain9;
						tmp_refMain10 = refMain[x + 3 + iIdx + 1 + OFFSET];
						comp[x + 3 + y * stride] = tmp_refMain10;
					}
					x = x + 4;
				}
				y = y + 1;
			}
		} else {
			y0 = 0;
			while (y0 <= 16 - 1) {
				tmp_intraPredAngle5 = HevcDecoder_IntraPrediction_intraPredAngle[angle];
				iIdx = ((y0 + 1) * tmp_intraPredAngle5) >> 5;
				tmp_intraPredAngle6 = HevcDecoder_IntraPrediction_intraPredAngle[angle];
				iFact = (y0 + 1) * tmp_intraPredAngle6 & 31;
				x = 0;
				while (x < 16) {
					if (iFact != 0) {
						tmp_refMain11 = refMain[x + iIdx + 1 + OFFSET];
						tmp_refMain12 = refMain[x + iIdx + 2 + OFFSET];
						comp[y0 + x * stride] = ((32 - iFact) * tmp_refMain11 + iFact * tmp_refMain12 + 16) >> 5;
						tmp_refMain13 = refMain[x + 1 + iIdx + 1 + OFFSET];
						tmp_refMain14 = refMain[x + 1 + iIdx + 2 + OFFSET];
						comp[y0 + (x + 1) * stride] = ((32 - iFact) * tmp_refMain13 + iFact * tmp_refMain14 + 16) >> 5;
						tmp_refMain15 = refMain[x + 2 + iIdx + 1 + OFFSET];
						tmp_refMain16 = refMain[x + 2 + iIdx + 2 + OFFSET];
						comp[y0 + (x + 2) * stride] = ((32 - iFact) * tmp_refMain15 + iFact * tmp_refMain16 + 16) >> 5;
						tmp_refMain17 = refMain[x + 3 + iIdx + 1 + OFFSET];
						tmp_refMain18 = refMain[x + 3 + iIdx + 2 + OFFSET];
						comp[y0 + (x + 3) * stride] = ((32 - iFact) * tmp_refMain17 + iFact * tmp_refMain18 + 16) >> 5;
					} else {
						tmp_refMain19 = refMain[x + iIdx + 1 + OFFSET];
						comp[y0 + x * stride] = tmp_refMain19;
						tmp_refMain20 = refMain[x + 1 + iIdx + 1 + OFFSET];
						comp[y0 + (x + 1) * stride] = tmp_refMain20;
						tmp_refMain21 = refMain[x + 2 + iIdx + 1 + OFFSET];
						comp[y0 + (x + 2) * stride] = tmp_refMain21;
						tmp_refMain22 = refMain[x + 3 + iIdx + 1 + OFFSET];
						comp[y0 + (x + 3) * stride] = tmp_refMain22;
					}
					x = x + 4;
				}
				y0 = y0 + 1;
			}
		}
	}
}
static void HevcDecoder_IntraPrediction_intraAngularVertOrHor_chroma_1(i32 isVertical, u8 lumaComp[4096], u8 pNeighb_above[129], u8 pNeighb_left[129], i32 stride) {
	u8 neighbIdx;
	u32 x;
	u32 y;
	u8 tmp_pNeighb_above;
	u8 tmp_pNeighb_left;

	if (isVertical) {
		neighbIdx = 0;
	} else {
		neighbIdx = 1;
	}
	x = 0;
	while (x <= 8 - 1) {
		y = 0;
		while (y <= 8 - 1) {
			if (neighbIdx == 0) {
				tmp_pNeighb_above = pNeighb_above[x + 1];
				lumaComp[x + stride * y] = tmp_pNeighb_above;
			} else {
				tmp_pNeighb_left = pNeighb_left[x + 1];
				lumaComp[y + stride * x] = tmp_pNeighb_left;
			}
			y = y + 1;
		}
		x = x + 1;
	}
}
static void HevcDecoder_IntraPrediction_intraAngularVertOrHor1(i32 isVertical, u8 lumaComp[4096], u8 pNeighb_above[129], u8 pNeighb_left[129], i32 stride) {
	u8 minVal;
	u32 y;
	u8 tmp_pNeighb_above;
	u8 tmp_pNeighb_left;
	u8 tmp_pNeighb_above0;
	i32 tmp_clip_i32;
	u32 x;
	u32 y0;
	u8 tmp_pNeighb_above1;
	u32 x0;
	u8 tmp_pNeighb_left0;
	u8 tmp_pNeighb_above2;
	u8 tmp_pNeighb_above3;
	i32 tmp_clip_i320;
	u32 x1;
	u32 y1;
	u8 tmp_pNeighb_left1;

	if (8 > 16) {
		minVal = 0;
	} else {
		minVal = 1;
	}
	if (isVertical) {
		if (minVal != 0) {
			y = 0;
			while (y <= 8 - 1) {
				tmp_pNeighb_above = pNeighb_above[0 + 1];
				tmp_pNeighb_left = pNeighb_left[y + 1];
				tmp_pNeighb_above0 = pNeighb_above[0];
				tmp_clip_i32 = HevcDecoder_IntraPrediction_clip_i32(tmp_pNeighb_above + ((tmp_pNeighb_left - tmp_pNeighb_above0) >> 1), 0, 255);
				lumaComp[y * stride] = tmp_clip_i32;
				y = y + 1;
			}
		}
		x = minVal;
		while (x <= 8 - 1) {
			y0 = 0;
			while (y0 <= 8 - 1) {
				tmp_pNeighb_above1 = pNeighb_above[x + 1];
				lumaComp[x + y0 * stride] = tmp_pNeighb_above1;
				y0 = y0 + 1;
			}
			x = x + 1;
		}
	} else {
		if (minVal != 0) {
			x0 = 0;
			while (x0 <= 8 - 1) {
				tmp_pNeighb_left0 = pNeighb_left[0 + 1];
				tmp_pNeighb_above2 = pNeighb_above[x0 + 1];
				tmp_pNeighb_above3 = pNeighb_above[0];
				tmp_clip_i320 = HevcDecoder_IntraPrediction_clip_i32(tmp_pNeighb_left0 + ((tmp_pNeighb_above2 - tmp_pNeighb_above3) >> 1), 0, 255);
				lumaComp[x0] = tmp_clip_i320;
				x0 = x0 + 1;
			}
		}
		x1 = 0;
		while (x1 <= 8 - 1) {
			y1 = minVal;
			while (y1 <= 8 - 1) {
				tmp_pNeighb_left1 = pNeighb_left[y1 + 1];
				lumaComp[x1 + y1 * stride] = tmp_pNeighb_left1;
				y1 = y1 + 1;
			}
			x1 = x1 + 1;
		}
	}
}
static void HevcDecoder_IntraPrediction_intraAngularPred1(u8 lumaComp[4096], u8 pNeighb_above[129], u8 pNeighb_left[129], i32 stride, i32 idx, u8 mode) {
	u8 OFFSET;
	u8 angle;
	u8 refMain[161];
	i16 iIdx;
	u8 iFact;
	u8 tmp_pNeighb_above;
	u32 x;
	u8 tmp_pNeighb_above0;
	i8 tmp_intraPredAngle;
	i32 k;
	i8 tmp_intraPredAngle0;
	i16 tmp_invAngle;
	u8 tmp_pNeighb_left;
	u32 x0;
	u8 tmp_pNeighb_above1;
	u8 tmp_pNeighb_above2;
	u32 x1;
	u8 tmp_pNeighb_left0;
	i8 tmp_intraPredAngle1;
	i32 k0;
	i8 tmp_intraPredAngle2;
	i16 tmp_invAngle0;
	u8 tmp_pNeighb_above3;
	u32 x2;
	u8 tmp_pNeighb_left1;
	u32 y;
	i8 tmp_intraPredAngle3;
	i8 tmp_intraPredAngle4;
	u32 x3;
	u8 tmp_refMain;
	u8 tmp_refMain0;
	u8 tmp_refMain1;
	u32 y0;
	i8 tmp_intraPredAngle5;
	i8 tmp_intraPredAngle6;
	u32 x4;
	u8 tmp_refMain2;
	u8 tmp_refMain3;
	u8 tmp_refMain4;

	OFFSET = 33;
	angle = mode & 63;
	if (angle == 26 || angle == 10) {
		if (idx == 0) {
			HevcDecoder_IntraPrediction_intraAngularVertOrHor1(angle == 26, lumaComp, pNeighb_above, pNeighb_left, stride);
		} else {
			HevcDecoder_IntraPrediction_intraAngularVertOrHor_chroma_1(angle == 26, lumaComp, pNeighb_above, pNeighb_left, stride);
		}
	} else {
		if (angle >= 18) {
			tmp_pNeighb_above = pNeighb_above[0];
			refMain[OFFSET] = tmp_pNeighb_above;
			x = 1;
			while (x <= 8) {
				tmp_pNeighb_above0 = pNeighb_above[x - 1 + 1];
				refMain[x + OFFSET] = tmp_pNeighb_above0;
				x = x + 1;
			}
			tmp_intraPredAngle = HevcDecoder_IntraPrediction_intraPredAngle[angle];
			if (tmp_intraPredAngle < 0) {
				tmp_intraPredAngle0 = HevcDecoder_IntraPrediction_intraPredAngle[angle];
				k = (8 * tmp_intraPredAngle0) >> 5;
				while (k <= -1) {
					tmp_invAngle = HevcDecoder_IntraPrediction_invAngle[angle];
					tmp_pNeighb_left = pNeighb_left[((k * tmp_invAngle + 128) >> 8) - 1 + 1];
					refMain[k + OFFSET] = tmp_pNeighb_left;
					k = k + 1;
				}
			} else {
				x0 = 8 + 1;
				while (x0 <= 2 * 8) {
					tmp_pNeighb_above1 = pNeighb_above[x0 - 1 + 1];
					refMain[x0 + OFFSET] = tmp_pNeighb_above1;
					x0 = x0 + 1;
				}
			}
		} else {
			tmp_pNeighb_above2 = pNeighb_above[0];
			refMain[OFFSET] = tmp_pNeighb_above2;
			x1 = 1;
			while (x1 <= 8) {
				tmp_pNeighb_left0 = pNeighb_left[x1 - 1 + 1];
				refMain[x1 + OFFSET] = tmp_pNeighb_left0;
				x1 = x1 + 1;
			}
			tmp_intraPredAngle1 = HevcDecoder_IntraPrediction_intraPredAngle[angle];
			if (tmp_intraPredAngle1 < 0) {
				tmp_intraPredAngle2 = HevcDecoder_IntraPrediction_intraPredAngle[angle];
				k0 = (8 * tmp_intraPredAngle2) >> 5;
				while (k0 <= -1) {
					tmp_invAngle0 = HevcDecoder_IntraPrediction_invAngle[angle];
					tmp_pNeighb_above3 = pNeighb_above[((k0 * tmp_invAngle0 + 128) >> 8) - 1 + 1];
					refMain[k0 + OFFSET] = tmp_pNeighb_above3;
					k0 = k0 + 1;
				}
			} else {
				x2 = 8 + 1;
				while (x2 <= 2 * 8) {
					tmp_pNeighb_left1 = pNeighb_left[x2 - 1 + 1];
					refMain[x2 + OFFSET] = tmp_pNeighb_left1;
					x2 = x2 + 1;
				}
			}
		}
		if (angle >= 18) {
			y = 0;
			while (y <= 8 - 1) {
				tmp_intraPredAngle3 = HevcDecoder_IntraPrediction_intraPredAngle[angle];
				iIdx = ((y + 1) * tmp_intraPredAngle3) >> 5;
				tmp_intraPredAngle4 = HevcDecoder_IntraPrediction_intraPredAngle[angle];
				iFact = (y + 1) * tmp_intraPredAngle4 & 31;
				x3 = 0;
				while (x3 <= 8 - 1) {
					if (iFact != 0) {
						tmp_refMain = refMain[x3 + iIdx + 1 + OFFSET];
						tmp_refMain0 = refMain[x3 + iIdx + 2 + OFFSET];
						lumaComp[x3 + y * stride] = ((32 - iFact) * tmp_refMain + iFact * tmp_refMain0 + 16) >> 5;
					} else {
						tmp_refMain1 = refMain[x3 + iIdx + 1 + OFFSET];
						lumaComp[x3 + y * stride] = tmp_refMain1;
					}
					x3 = x3 + 1;
				}
				y = y + 1;
			}
		} else {
			y0 = 0;
			while (y0 <= 8 - 1) {
				tmp_intraPredAngle5 = HevcDecoder_IntraPrediction_intraPredAngle[angle];
				iIdx = ((y0 + 1) * tmp_intraPredAngle5) >> 5;
				tmp_intraPredAngle6 = HevcDecoder_IntraPrediction_intraPredAngle[angle];
				iFact = (y0 + 1) * tmp_intraPredAngle6 & 31;
				x4 = 0;
				while (x4 <= 8 - 1) {
					if (iFact != 0) {
						tmp_refMain2 = refMain[x4 + iIdx + 1 + OFFSET];
						tmp_refMain3 = refMain[x4 + iIdx + 2 + OFFSET];
						lumaComp[y0 + x4 * stride] = ((32 - iFact) * tmp_refMain2 + iFact * tmp_refMain3 + 16) >> 5;
					} else {
						tmp_refMain4 = refMain[x4 + iIdx + 1 + OFFSET];
						lumaComp[y0 + x4 * stride] = tmp_refMain4;
					}
					x4 = x4 + 1;
				}
				y0 = y0 + 1;
			}
		}
	}
}
static void HevcDecoder_IntraPrediction_intraAngularVertOrHor_chroma_0(i32 isVertical, u8 comp[4096], u8 pNeighb_above[129], u8 pNeighb_left[129], i32 stride) {
	u8 neighbIdx;
	u32 x;
	u8 tmp_pNeighb_above;
	u8 tmp_pNeighb_above0;
	u8 tmp_pNeighb_above1;
	u8 tmp_pNeighb_above2;
	u8 tmp_pNeighb_left;
	u8 tmp_pNeighb_left0;
	u8 tmp_pNeighb_left1;
	u8 tmp_pNeighb_left2;

	if (isVertical) {
		neighbIdx = 0;
	} else {
		neighbIdx = 1;
	}
	x = 0;
	while (x <= 4 - 1) {
		if (neighbIdx == 0) {
			tmp_pNeighb_above = pNeighb_above[x + 1];
			comp[x + stride * 0] = tmp_pNeighb_above;
			tmp_pNeighb_above0 = pNeighb_above[x + 1];
			comp[x + stride * 1] = tmp_pNeighb_above0;
			tmp_pNeighb_above1 = pNeighb_above[x + 1];
			comp[x + stride * 2] = tmp_pNeighb_above1;
			tmp_pNeighb_above2 = pNeighb_above[x + 1];
			comp[x + stride * 3] = tmp_pNeighb_above2;
		} else {
			tmp_pNeighb_left = pNeighb_left[x + 1];
			comp[0 + stride * x] = tmp_pNeighb_left;
			tmp_pNeighb_left0 = pNeighb_left[x + 1];
			comp[1 + stride * x] = tmp_pNeighb_left0;
			tmp_pNeighb_left1 = pNeighb_left[x + 1];
			comp[2 + stride * x] = tmp_pNeighb_left1;
			tmp_pNeighb_left2 = pNeighb_left[x + 1];
			comp[3 + stride * x] = tmp_pNeighb_left2;
		}
		x = x + 1;
	}
}
static void HevcDecoder_IntraPrediction_intraAngularVertOrHor0(i32 isVertical, u8 lumaComp[4096], u8 pNeighb_above[129], u8 pNeighb_left[129], i32 stride) {
	u8 minVal;
	u32 y;
	u8 tmp_pNeighb_above;
	u8 tmp_pNeighb_left;
	u8 tmp_pNeighb_above0;
	i32 tmp_clip_i32;
	u32 x;
	u32 y0;
	u8 tmp_pNeighb_above1;
	u32 x0;
	u8 tmp_pNeighb_left0;
	u8 tmp_pNeighb_above2;
	u8 tmp_pNeighb_above3;
	i32 tmp_clip_i320;
	u32 x1;
	u32 y1;
	u8 tmp_pNeighb_left1;

	if (4 > 16) {
		minVal = 0;
	} else {
		minVal = 1;
	}
	if (isVertical) {
		if (minVal != 0) {
			y = 0;
			while (y <= 4 - 1) {
				tmp_pNeighb_above = pNeighb_above[0 + 1];
				tmp_pNeighb_left = pNeighb_left[y + 1];
				tmp_pNeighb_above0 = pNeighb_above[0];
				tmp_clip_i32 = HevcDecoder_IntraPrediction_clip_i32(tmp_pNeighb_above + ((tmp_pNeighb_left - tmp_pNeighb_above0) >> 1), 0, 255);
				lumaComp[y * stride] = tmp_clip_i32;
				y = y + 1;
			}
		}
		x = minVal;
		while (x <= 4 - 1) {
			y0 = 0;
			while (y0 <= 4 - 1) {
				tmp_pNeighb_above1 = pNeighb_above[x + 1];
				lumaComp[x + y0 * stride] = tmp_pNeighb_above1;
				y0 = y0 + 1;
			}
			x = x + 1;
		}
	} else {
		if (minVal != 0) {
			x0 = 0;
			while (x0 <= 4 - 1) {
				tmp_pNeighb_left0 = pNeighb_left[0 + 1];
				tmp_pNeighb_above2 = pNeighb_above[x0 + 1];
				tmp_pNeighb_above3 = pNeighb_above[0];
				tmp_clip_i320 = HevcDecoder_IntraPrediction_clip_i32(tmp_pNeighb_left0 + ((tmp_pNeighb_above2 - tmp_pNeighb_above3) >> 1), 0, 255);
				lumaComp[x0] = tmp_clip_i320;
				x0 = x0 + 1;
			}
		}
		x1 = 0;
		while (x1 <= 4 - 1) {
			y1 = minVal;
			while (y1 <= 4 - 1) {
				tmp_pNeighb_left1 = pNeighb_left[y1 + 1];
				lumaComp[x1 + y1 * stride] = tmp_pNeighb_left1;
				y1 = y1 + 1;
			}
			x1 = x1 + 1;
		}
	}
}
static void HevcDecoder_IntraPrediction_intraAngularPred0(u8 comp[4096], u8 pNeighb_above[129], u8 pNeighb_left[129], i32 stride, i32 idx, u8 mode) {
	u8 OFFSET;
	u8 angle;
	u8 refMain[161];
	i16 iIdx;
	u8 iFact;
	u8 tmp_pNeighb_above;
	u8 tmp_pNeighb_above0;
	u8 tmp_pNeighb_above1;
	u8 tmp_pNeighb_above2;
	u8 tmp_pNeighb_above3;
	i8 tmp_intraPredAngle;
	i32 k;
	i8 tmp_intraPredAngle0;
	i16 tmp_invAngle;
	u8 tmp_pNeighb_left;
	u8 tmp_pNeighb_above4;
	u8 tmp_pNeighb_above5;
	u8 tmp_pNeighb_above6;
	u8 tmp_pNeighb_above7;
	u8 tmp_pNeighb_above8;
	u8 tmp_pNeighb_left0;
	u8 tmp_pNeighb_left1;
	u8 tmp_pNeighb_left2;
	u8 tmp_pNeighb_left3;
	i8 tmp_intraPredAngle1;
	i32 k0;
	i8 tmp_intraPredAngle2;
	i16 tmp_invAngle0;
	u8 tmp_pNeighb_above9;
	u8 tmp_pNeighb_left4;
	u8 tmp_pNeighb_left5;
	u8 tmp_pNeighb_left6;
	u8 tmp_pNeighb_left7;
	u32 y;
	i8 tmp_intraPredAngle3;
	i8 tmp_intraPredAngle4;
	u8 tmp_refMain;
	u8 tmp_refMain0;
	u8 tmp_refMain1;
	u8 tmp_refMain2;
	u8 tmp_refMain3;
	u8 tmp_refMain4;
	u8 tmp_refMain5;
	u8 tmp_refMain6;
	u8 tmp_refMain7;
	u8 tmp_refMain8;
	u8 tmp_refMain9;
	u8 tmp_refMain10;
	u32 y0;
	i8 tmp_intraPredAngle5;
	i8 tmp_intraPredAngle6;
	u8 tmp_refMain11;
	u8 tmp_refMain12;
	u8 tmp_refMain13;
	u8 tmp_refMain14;
	u8 tmp_refMain15;
	u8 tmp_refMain16;
	u8 tmp_refMain17;
	u8 tmp_refMain18;
	u8 tmp_refMain19;
	u8 tmp_refMain20;
	u8 tmp_refMain21;
	u8 tmp_refMain22;

	OFFSET = 33;
	angle = mode & 63;
	if (angle == 26 || angle == 10) {
		if (idx == 0) {
			HevcDecoder_IntraPrediction_intraAngularVertOrHor0(angle == 26, comp, pNeighb_above, pNeighb_left, stride);
		} else {
			HevcDecoder_IntraPrediction_intraAngularVertOrHor_chroma_0(angle == 26, comp, pNeighb_above, pNeighb_left, stride);
		}
	} else {
		if (angle >= 18) {
			tmp_pNeighb_above = pNeighb_above[0];
			refMain[OFFSET] = tmp_pNeighb_above;
			tmp_pNeighb_above0 = pNeighb_above[1 - 1 + 1];
			refMain[1 + OFFSET] = tmp_pNeighb_above0;
			tmp_pNeighb_above1 = pNeighb_above[2 - 1 + 1];
			refMain[2 + OFFSET] = tmp_pNeighb_above1;
			tmp_pNeighb_above2 = pNeighb_above[3 - 1 + 1];
			refMain[3 + OFFSET] = tmp_pNeighb_above2;
			tmp_pNeighb_above3 = pNeighb_above[4 - 1 + 1];
			refMain[4 + OFFSET] = tmp_pNeighb_above3;
			tmp_intraPredAngle = HevcDecoder_IntraPrediction_intraPredAngle[angle];
			if (tmp_intraPredAngle < 0) {
				tmp_intraPredAngle0 = HevcDecoder_IntraPrediction_intraPredAngle[angle];
				k = (4 * tmp_intraPredAngle0) >> 5;
				while (k <= -1) {
					tmp_invAngle = HevcDecoder_IntraPrediction_invAngle[angle];
					tmp_pNeighb_left = pNeighb_left[((k * tmp_invAngle + 128) >> 8) - 1 + 1];
					refMain[k + OFFSET] = tmp_pNeighb_left;
					k = k + 1;
				}
			} else {
				tmp_pNeighb_above4 = pNeighb_above[5 - 1 + 1];
				refMain[5 + OFFSET] = tmp_pNeighb_above4;
				tmp_pNeighb_above5 = pNeighb_above[6 - 1 + 1];
				refMain[6 + OFFSET] = tmp_pNeighb_above5;
				tmp_pNeighb_above6 = pNeighb_above[7 - 1 + 1];
				refMain[7 + OFFSET] = tmp_pNeighb_above6;
				tmp_pNeighb_above7 = pNeighb_above[8 - 1 + 1];
				refMain[8 + OFFSET] = tmp_pNeighb_above7;
			}
		} else {
			tmp_pNeighb_above8 = pNeighb_above[0];
			refMain[OFFSET] = tmp_pNeighb_above8;
			tmp_pNeighb_left0 = pNeighb_left[1 - 1 + 1];
			refMain[1 + OFFSET] = tmp_pNeighb_left0;
			tmp_pNeighb_left1 = pNeighb_left[2 - 1 + 1];
			refMain[2 + OFFSET] = tmp_pNeighb_left1;
			tmp_pNeighb_left2 = pNeighb_left[3 - 1 + 1];
			refMain[3 + OFFSET] = tmp_pNeighb_left2;
			tmp_pNeighb_left3 = pNeighb_left[4 - 1 + 1];
			refMain[4 + OFFSET] = tmp_pNeighb_left3;
			tmp_intraPredAngle1 = HevcDecoder_IntraPrediction_intraPredAngle[angle];
			if (tmp_intraPredAngle1 < 0) {
				tmp_intraPredAngle2 = HevcDecoder_IntraPrediction_intraPredAngle[angle];
				k0 = (4 * tmp_intraPredAngle2) >> 5;
				while (k0 <= -1) {
					tmp_invAngle0 = HevcDecoder_IntraPrediction_invAngle[angle];
					tmp_pNeighb_above9 = pNeighb_above[((k0 * tmp_invAngle0 + 128) >> 8) - 1 + 1];
					refMain[k0 + OFFSET] = tmp_pNeighb_above9;
					k0 = k0 + 1;
				}
			} else {
				tmp_pNeighb_left4 = pNeighb_left[5 - 1 + 1];
				refMain[5 + OFFSET] = tmp_pNeighb_left4;
				tmp_pNeighb_left5 = pNeighb_left[6 - 1 + 1];
				refMain[6 + OFFSET] = tmp_pNeighb_left5;
				tmp_pNeighb_left6 = pNeighb_left[7 - 1 + 1];
				refMain[7 + OFFSET] = tmp_pNeighb_left6;
				tmp_pNeighb_left7 = pNeighb_left[8 - 1 + 1];
				refMain[8 + OFFSET] = tmp_pNeighb_left7;
			}
		}
		if (angle >= 18) {
			y = 0;
			while (y <= 4 - 1) {
				tmp_intraPredAngle3 = HevcDecoder_IntraPrediction_intraPredAngle[angle];
				iIdx = ((y + 1) * tmp_intraPredAngle3) >> 5;
				tmp_intraPredAngle4 = HevcDecoder_IntraPrediction_intraPredAngle[angle];
				iFact = (y + 1) * tmp_intraPredAngle4 & 31;
				if (iFact != 0) {
					tmp_refMain = refMain[0 + iIdx + 1 + OFFSET];
					tmp_refMain0 = refMain[0 + iIdx + 2 + OFFSET];
					comp[0 + y * stride] = ((32 - iFact) * tmp_refMain + iFact * tmp_refMain0 + 16) >> 5;
					tmp_refMain1 = refMain[1 + iIdx + 1 + OFFSET];
					tmp_refMain2 = refMain[1 + iIdx + 2 + OFFSET];
					comp[1 + y * stride] = ((32 - iFact) * tmp_refMain1 + iFact * tmp_refMain2 + 16) >> 5;
					tmp_refMain3 = refMain[2 + iIdx + 1 + OFFSET];
					tmp_refMain4 = refMain[2 + iIdx + 2 + OFFSET];
					comp[2 + y * stride] = ((32 - iFact) * tmp_refMain3 + iFact * tmp_refMain4 + 16) >> 5;
					tmp_refMain5 = refMain[3 + iIdx + 1 + OFFSET];
					tmp_refMain6 = refMain[3 + iIdx + 2 + OFFSET];
					comp[3 + y * stride] = ((32 - iFact) * tmp_refMain5 + iFact * tmp_refMain6 + 16) >> 5;
				} else {
					tmp_refMain7 = refMain[0 + iIdx + 1 + OFFSET];
					comp[0 + y * stride] = tmp_refMain7;
					tmp_refMain8 = refMain[1 + iIdx + 1 + OFFSET];
					comp[1 + y * stride] = tmp_refMain8;
					tmp_refMain9 = refMain[2 + iIdx + 1 + OFFSET];
					comp[2 + y * stride] = tmp_refMain9;
					tmp_refMain10 = refMain[3 + iIdx + 1 + OFFSET];
					comp[3 + y * stride] = tmp_refMain10;
				}
				y = y + 1;
			}
		} else {
			y0 = 0;
			while (y0 <= 4 - 1) {
				tmp_intraPredAngle5 = HevcDecoder_IntraPrediction_intraPredAngle[angle];
				iIdx = ((y0 + 1) * tmp_intraPredAngle5) >> 5;
				tmp_intraPredAngle6 = HevcDecoder_IntraPrediction_intraPredAngle[angle];
				iFact = (y0 + 1) * tmp_intraPredAngle6 & 31;
				if (iFact != 0) {
					tmp_refMain11 = refMain[0 + iIdx + 1 + OFFSET];
					tmp_refMain12 = refMain[0 + iIdx + 2 + OFFSET];
					comp[y0 + 0 * stride] = ((32 - iFact) * tmp_refMain11 + iFact * tmp_refMain12 + 16) >> 5;
					tmp_refMain13 = refMain[1 + iIdx + 1 + OFFSET];
					tmp_refMain14 = refMain[1 + iIdx + 2 + OFFSET];
					comp[y0 + 1 * stride] = ((32 - iFact) * tmp_refMain13 + iFact * tmp_refMain14 + 16) >> 5;
					tmp_refMain15 = refMain[2 + iIdx + 1 + OFFSET];
					tmp_refMain16 = refMain[2 + iIdx + 2 + OFFSET];
					comp[y0 + 2 * stride] = ((32 - iFact) * tmp_refMain15 + iFact * tmp_refMain16 + 16) >> 5;
					tmp_refMain17 = refMain[3 + iIdx + 1 + OFFSET];
					tmp_refMain18 = refMain[3 + iIdx + 2 + OFFSET];
					comp[y0 + 3 * stride] = ((32 - iFact) * tmp_refMain17 + iFact * tmp_refMain18 + 16) >> 5;
				} else {
					tmp_refMain19 = refMain[0 + iIdx + 1 + OFFSET];
					comp[y0 + 0 * stride] = tmp_refMain19;
					tmp_refMain20 = refMain[1 + iIdx + 1 + OFFSET];
					comp[y0 + 1 * stride] = tmp_refMain20;
					tmp_refMain21 = refMain[2 + iIdx + 1 + OFFSET];
					comp[y0 + 2 * stride] = tmp_refMain21;
					tmp_refMain22 = refMain[3 + iIdx + 1 + OFFSET];
					comp[y0 + 3 * stride] = tmp_refMain22;
				}
				y0 = y0 + 1;
			}
		}
	}
}
static void HevcDecoder_IntraPrediction_intraAngularPred(u8 src[4096], u8 top[129], u8 left[129], i32 stride, i32 idx, u8 mode, i32 log2Size) {
	#if defined(SSE_ENABLE) && HAVE_SSE4
	pred_angular_orcc(src, top, left, stride, idx, mode, log2Size);
	#else

	if (log2Size == 2) {
		HevcDecoder_IntraPrediction_intraAngularPred0(src, top, left, stride, idx, mode);
	} else {
		if (log2Size == 3) {
			HevcDecoder_IntraPrediction_intraAngularPred1(src, top, left, stride, idx, mode);
		} else {
			if (log2Size == 4) {
				HevcDecoder_IntraPrediction_intraAngularPred2(src, top, left, stride, idx, mode);
			} else {
				HevcDecoder_IntraPrediction_intraAngularPred3(src, top, left, stride, idx, mode);
			}
		}
	}
	#endif // defined(SSE_ENABLE) && HAVE_SSE4
}
static void HevcDecoder_IntraPrediction_zScanToAbsCoord(u16 rasterIdx, u16 coord[2]) {
	u8 tmp_ZscanToAbsCoord0;
	u8 tmp_ZscanToAbsCoord1;

	tmp_ZscanToAbsCoord0 = HevcDecoder_IntraPrediction_ZscanToAbsCoord0[rasterIdx];
	coord[0] = tmp_ZscanToAbsCoord0;
	tmp_ZscanToAbsCoord1 = HevcDecoder_IntraPrediction_ZscanToAbsCoord1[rasterIdx];
	coord[1] = tmp_ZscanToAbsCoord1;
}
static i32 absCoordToRasterScan(u16 coord[2]) {
	u16 tmp_coord;
	u8 xCoordInBlk;
	u16 tmp_coord0;
	u8 yCoordInBlk;
	u8 tmp_if;
	u8 tmp_if0;
	u8 tmp_if1;
	u8 tmp_if2;
	u8 tmp_if3;
	u8 tmp_if4;
	u8 tmp_if5;
	u8 tmp_if6;

	tmp_coord = coord[0];
	xCoordInBlk = tmp_coord / 4;
	tmp_coord0 = coord[1];
	yCoordInBlk = tmp_coord0 / 4;
	if ((xCoordInBlk & 1) != 0) {
		tmp_if = 1;
	} else {
		tmp_if = 0;
	}
	if ((xCoordInBlk & 2) != 0) {
		tmp_if0 = 4;
	} else {
		tmp_if0 = 0;
	}
	if ((xCoordInBlk & 4) != 0) {
		tmp_if1 = 16;
	} else {
		tmp_if1 = 0;
	}
	if ((xCoordInBlk & 8) != 0) {
		tmp_if2 = 64;
	} else {
		tmp_if2 = 0;
	}
	if ((yCoordInBlk & 1) != 0) {
		tmp_if3 = 2;
	} else {
		tmp_if3 = 0;
	}
	if ((yCoordInBlk & 2) != 0) {
		tmp_if4 = 8;
	} else {
		tmp_if4 = 0;
	}
	if ((yCoordInBlk & 4) != 0) {
		tmp_if5 = 32;
	} else {
		tmp_if5 = 0;
	}
	if ((yCoordInBlk & 8) != 0) {
		tmp_if6 = 128;
	} else {
		tmp_if6 = 0;
	}
	return tmp_if + tmp_if0 + tmp_if1 + tmp_if2 + tmp_if3 + tmp_if4 + tmp_if5 + tmp_if6;
}
static void getNeighbSamples(u16 cuAddr[2], u8 cIdx, u8 nS, u8 log2NS) {
	i32 minVal[2];
	i32 maxVal[2];
	i32 xMin;
	i32 yMin;
	i32 xMax;
	i32 yMax;
	i32 xIdx;
	i32 yIdx;
	i32 origPixIdx;
	u8 pixVal;
	u16 tmp_pictSize;
	u16 tmp_cuAddr;
	u16 tmp_cuAddr0;
	i32 y;
	u16 local_NEIGHB_TAB_MASK;
	u8 tmp_puNeighb;
	i32 x;
	u8 tmp_puNeighb0;
	u8 tmp_pNeighb_above;
	i32 local_constrIntraPred;
	i32 tmp_puIsIntra;
	i32 tmp_puIsIntra0;
	i32 tmp_puIsIntra1;
	i32 y0;
	i32 tmp_puIsIntra2;
	u8 tmp_pNeighb_left;
	i32 tmp_puIsIntra3;
	u8 tmp_pNeighb_left0;
	i32 tmp_puIsIntra4;
	u8 tmp_pNeighb_left1;
	u8 tmp_pNeighb_left2;
	i32 x0;
	i32 tmp_puIsIntra5;
	u8 tmp_pNeighb_above0;
	i32 y1;
	u8 tmp_pNeighb_left3;
	i32 y2;
	u8 tmp_pNeighb_left4;
	i32 x1;
	u8 tmp_pNeighb_left5;
	i32 x2;
	u8 tmp_pNeighb_above1;
	i32 idx;
	i32 x3;
	u8 tmp_pNeighb_left6;
	i32 y3;
	u8 tmp_pNeighb_above2;
	u8 tmp_pNeighb_above3;
	u8 tmp_pNeighb_left7;
	u8 tmp_puNeighb1;

	neighbExist(cuAddr, minVal, maxVal, cIdx, nS);
	xMin = minVal[0];
	yMin = minVal[1];
	xMax = maxVal[0];
	yMax = maxVal[1];
	tmp_pictSize = pictSize[cIdx][1];
	tmp_cuAddr = cuAddr[1];
	tmp_cuAddr0 = cuAddr[0];
	origPixIdx = tmp_pictSize - tmp_cuAddr + tmp_cuAddr0;
	y = yMin;
	while (y <= yMax - 1) {
		local_NEIGHB_TAB_MASK = NEIGHB_TAB_MASK;
		tmp_puNeighb = puNeighb[cIdx][origPixIdx - 1 - y & local_NEIGHB_TAB_MASK];
		pNeighb_left[y + 1] = tmp_puNeighb;
		y = y + 1;
	}
	x = xMin;
	while (x <= xMax - 1) {
		local_NEIGHB_TAB_MASK = NEIGHB_TAB_MASK;
		tmp_puNeighb0 = puNeighb[cIdx][origPixIdx + 1 + x - 1 & local_NEIGHB_TAB_MASK];
		pNeighb_above[x] = tmp_puNeighb0;
		x = x + 1;
	}
	tmp_pNeighb_above = pNeighb_above[0];
	pNeighb_left[0] = tmp_pNeighb_above;
	local_constrIntraPred = constrIntraPred;
	if (local_constrIntraPred) {
		local_NEIGHB_TAB_MASK = NEIGHB_TAB_MASK;
		tmp_puIsIntra = puIsIntra[cIdx][origPixIdx - 1 - (yMax - 1) & local_NEIGHB_TAB_MASK];
		if (yMax == 0 || !tmp_puIsIntra) {
			pixVal = 128;
			xIdx = xMax - 1;
			while (xIdx >= xMin) {
				local_NEIGHB_TAB_MASK = NEIGHB_TAB_MASK;
				tmp_puIsIntra0 = puIsIntra[cIdx][origPixIdx + 1 + xIdx - 1 & local_NEIGHB_TAB_MASK];
				if (tmp_puIsIntra0) {
					pixVal = pNeighb_above[xIdx];
				}
				xIdx = xIdx - 1;
			}
			local_NEIGHB_TAB_MASK = NEIGHB_TAB_MASK;
			tmp_puIsIntra1 = puIsIntra[cIdx][origPixIdx & local_NEIGHB_TAB_MASK];
			if (tmp_puIsIntra1) {
				pixVal = pNeighb_left[0];
			}
			y0 = yMin;
			while (y0 <= yMax - 2) {
				local_NEIGHB_TAB_MASK = NEIGHB_TAB_MASK;
				tmp_puIsIntra2 = puIsIntra[cIdx][origPixIdx - 1 - y0 & local_NEIGHB_TAB_MASK];
				if (tmp_puIsIntra2) {
					tmp_pNeighb_left = pNeighb_left[y0 + 2];
					pNeighb_left[y0 + 1] = tmp_pNeighb_left;
				}
				y0 = y0 + 1;
			}
			pNeighb_left[yMax - 1 + 1] = pixVal;
		}
		yIdx = yMax - 2;
		while (yIdx >= yMin) {
			local_NEIGHB_TAB_MASK = NEIGHB_TAB_MASK;
			tmp_puIsIntra3 = puIsIntra[cIdx][origPixIdx - 1 - yIdx & local_NEIGHB_TAB_MASK];
			if (!tmp_puIsIntra3) {
				tmp_pNeighb_left0 = pNeighb_left[yIdx + 2];
				pNeighb_left[yIdx + 1] = tmp_pNeighb_left0;
			}
			yIdx = yIdx - 1;
		}
		local_NEIGHB_TAB_MASK = NEIGHB_TAB_MASK;
		tmp_puIsIntra4 = puIsIntra[cIdx][origPixIdx & local_NEIGHB_TAB_MASK];
		if (!tmp_puIsIntra4) {
			tmp_pNeighb_left1 = pNeighb_left[1];
			pNeighb_left[0] = tmp_pNeighb_left1;
			tmp_pNeighb_left2 = pNeighb_left[1];
			pNeighb_above[0] = tmp_pNeighb_left2;
		}
		x0 = xMin;
		while (x0 <= xMax - 1) {
			local_NEIGHB_TAB_MASK = NEIGHB_TAB_MASK;
			tmp_puIsIntra5 = puIsIntra[cIdx][origPixIdx + 1 + x0 & local_NEIGHB_TAB_MASK];
			if (!tmp_puIsIntra5) {
				tmp_pNeighb_above0 = pNeighb_above[x0];
				pNeighb_above[x0 + 1] = tmp_pNeighb_above0;
			}
			x0 = x0 + 1;
		}
	}
	if (yMax != yMin) {
		y1 = 0;
		while (y1 <= yMin - 1) {
			tmp_pNeighb_left3 = pNeighb_left[yMin + 1];
			pNeighb_left[y1 + 1] = tmp_pNeighb_left3;
			y1 = y1 + 1;
		}
		y2 = yMax;
		while (y2 <= 2 * nS - 1) {
			tmp_pNeighb_left4 = pNeighb_left[yMax - 1 + 1];
			pNeighb_left[y2 + 1] = tmp_pNeighb_left4;
			y2 = y2 + 1;
		}
	}
	if (xMax != xMin) {
		x1 = 0;
		while (x1 <= xMin - 1) {
			tmp_pNeighb_left5 = pNeighb_left[0 + 1];
			pNeighb_above[x1] = tmp_pNeighb_left5;
			x1 = x1 + 1;
		}
		x2 = xMax;
		while (x2 <= 2 * nS) {
			tmp_pNeighb_above1 = pNeighb_above[xMax - 1];
			pNeighb_above[x2] = tmp_pNeighb_above1;
			x2 = x2 + 1;
		}
	}
	if (xMax == xMin && yMax == yMin) {
		idx = 0;
		while (idx <= 2 * nS) {
			pNeighb_above[idx] = 128;
			pNeighb_left[idx] = 128;
			idx = idx + 1;
		}
	} else {
		if (xMax == xMin && yMax != yMin) {
			x3 = 0;
			while (x3 <= 2 * nS) {
				tmp_pNeighb_left6 = pNeighb_left[0 + 1];
				pNeighb_above[x3] = tmp_pNeighb_left6;
				x3 = x3 + 1;
			}
		} else {
			if (xMax != xMin && yMax == yMin) {
				y3 = 0;
				while (y3 <= 2 * nS - 1) {
					tmp_pNeighb_above2 = pNeighb_above[0 + 1];
					pNeighb_left[y3 + 1] = tmp_pNeighb_above2;
					y3 = y3 + 1;
				}
				tmp_pNeighb_above3 = pNeighb_above[0 + 1];
				pNeighb_above[0] = tmp_pNeighb_above3;
			} else {
				if (xMin != 0 || yMin != 0) {
					tmp_pNeighb_left7 = pNeighb_left[0 + 1];
					pNeighb_above[0] = tmp_pNeighb_left7;
				} else {
					local_constrIntraPred = constrIntraPred;
					if (!local_constrIntraPred) {
						local_NEIGHB_TAB_MASK = NEIGHB_TAB_MASK;
						tmp_puNeighb1 = puNeighb[cIdx][origPixIdx & local_NEIGHB_TAB_MASK];
						pNeighb_above[0] = tmp_puNeighb1;
					}
				}
			}
		}
	}
	if (cIdx == 0) {
		filterNeighbSamp(nS, log2NS);
	}
}
static void neighbExist(u16 cuAddr[2], i32 minVal[2], i32 maxVal[2], i32 cIdx, u8 nS) {
	u8 local_maxLcuSizeLuma;
	u8 local_maxLcuSizeChr;
	u8 maxCuSize;
	i32 xMin;
	i32 yMin;
	i32 xMax;
	i32 yMax;
	i32 numPixRemain;
	u16 tmp_cuAddr;
	u16 tmp_cuAddr0;
	u16 tmp_cuAddr1;
	i32 tmp_absCoordToRasterScan;
	u8 tmp_leftBlkAvail;
	u16 tmp_cuAddr2;
	i32 tmp_min;
	u16 tmp_pictSize;
	u16 tmp_cuAddr3;
	i32 local_isIndepSlc;
	u16 tmp_cuAddr4;
	u16 tmp_sliceAddr;
	u16 tmp_sliceAddr0;
	u16 tmp_cuAddr5;
	u16 tmp_sliceAddr1;
	u16 tmp_cuAddr6;
	u16 tmp_sliceAddr2;
	u16 tmp_cuAddr7;
	u16 tmp_sliceAddr3;
	u16 tmp_cuAddr8;
	u16 tmp_sliceAddr4;
	u16 tmp_cuAddr9;
	u16 tmp_sliceAddr5;
	u16 tmp_cuAddr10;
	i16 tmp_puTilesBeg;
	u16 tmp_cuAddr11;
	i16 tmp_puTilesBeg0;
	u16 tmp_cuAddr12;
	i16 tmp_puTilesBeg1;
	u16 tmp_cuAddr13;
	i16 tmp_puTilesEnd;
	u16 tmp_cuAddr14;
	i16 tmp_puTilesEnd0;
	u16 tmp_cuAddr15;
	u16 tmp_cuAddr16;
	u16 tmp_cuAddr17;
	u16 tmp_cuAddr18;
	i32 tmp_absCoordToRasterScan0;
	u8 tmp_aboveBlkAvail;
	u16 tmp_pictSize0;
	u16 tmp_cuAddr19;
	u16 tmp_pictSize1;
	u16 tmp_cuAddr20;
	i32 tmp_min0;
	u16 tmp_cuAddr21;
	u16 tmp_sliceAddr6;
	u16 tmp_cuAddr22;
	u16 tmp_sliceAddr7;
	u16 tmp_cuAddr23;
	u16 tmp_sliceAddr8;
	u16 tmp_sliceAddr9;
	u16 tmp_cuAddr24;
	u16 tmp_sliceAddr10;
	u16 tmp_cuAddr25;
	u16 tmp_sliceAddr11;
	u16 tmp_cuAddr26;
	i16 tmp_puTilesBeg2;
	u16 tmp_cuAddr27;
	i16 tmp_puTilesBeg3;
	u16 tmp_cuAddr28;
	i16 tmp_puTilesBeg4;
	u16 tmp_cuAddr29;
	i16 tmp_puTilesEnd1;
	u16 tmp_cuAddr30;
	i16 tmp_puTilesEnd2;
	u16 tmp_cuAddr31;

	if (cIdx == 0) {
		local_maxLcuSizeLuma = maxLcuSizeLuma;
		maxCuSize = local_maxLcuSizeLuma;
	} else {
		local_maxLcuSizeChr = maxLcuSizeChr;
		maxCuSize = local_maxLcuSizeChr;
	}
	xMin = 0;
	yMin = 0;
	xMax = 0;
	yMax = 0;
	tmp_cuAddr = cuAddr[0];
	if (tmp_cuAddr != 0) {
		tmp_cuAddr0 = cuAddr[0];
		tmp_cuAddr1 = cuAddr[0];
		if ((tmp_cuAddr0 & ~(maxCuSize - 1)) == (tmp_cuAddr1 - 1 & ~(maxCuSize - 1))) {
			tmp_absCoordToRasterScan = absCoordToRasterScan(cuAddr);
			tmp_leftBlkAvail = leftBlkAvail[tmp_absCoordToRasterScan];
			numPixRemain = tmp_leftBlkAvail << 2;
		} else {
			tmp_cuAddr2 = cuAddr[1];
			numPixRemain = maxCuSize - (tmp_cuAddr2 & maxCuSize - 1);
		}
		tmp_min = HevcDecoder_IntraPrediction_min(2 * nS, numPixRemain);
		tmp_pictSize = pictSize[cIdx][1];
		tmp_cuAddr3 = cuAddr[1];
		yMax = HevcDecoder_IntraPrediction_min(tmp_min, tmp_pictSize - tmp_cuAddr3);
		local_isIndepSlc = isIndepSlc;
		if (local_isIndepSlc) {
			tmp_cuAddr4 = cuAddr[0];
			tmp_sliceAddr = sliceAddr[cIdx][0];
			if (tmp_cuAddr4 <= tmp_sliceAddr) {
				tmp_sliceAddr0 = sliceAddr[cIdx][1];
				tmp_cuAddr5 = cuAddr[1];
				if (tmp_sliceAddr0 + maxCuSize > tmp_cuAddr5 + 2 * nS) {
					yMin = yMax;
				} else {
					tmp_sliceAddr1 = sliceAddr[cIdx][1];
					tmp_cuAddr6 = cuAddr[1];
					if (tmp_sliceAddr1 + maxCuSize > tmp_cuAddr6) {
						tmp_sliceAddr2 = sliceAddr[cIdx][1];
						tmp_cuAddr7 = cuAddr[1];
						yMin = tmp_sliceAddr2 + maxCuSize - tmp_cuAddr7;
					}
				}
			} else {
				tmp_sliceAddr3 = sliceAddr[cIdx][1];
				tmp_cuAddr8 = cuAddr[1];
				if (tmp_sliceAddr3 > tmp_cuAddr8 + 2 * nS) {
					yMin = yMax;
				} else {
					tmp_sliceAddr4 = sliceAddr[cIdx][1];
					tmp_cuAddr9 = cuAddr[1];
					if (tmp_sliceAddr4 > tmp_cuAddr9) {
						tmp_sliceAddr5 = sliceAddr[cIdx][1];
						tmp_cuAddr10 = cuAddr[1];
						yMin = tmp_sliceAddr5 - tmp_cuAddr10;
					}
				}
			}
		}
		tmp_puTilesBeg = puTilesBeg[cIdx][0];
		tmp_cuAddr11 = cuAddr[0];
		if (tmp_puTilesBeg > tmp_cuAddr11 - 1) {
			yMin = yMax;
		} else {
			tmp_puTilesBeg0 = puTilesBeg[cIdx][1];
			tmp_cuAddr12 = cuAddr[1];
			if (tmp_puTilesBeg0 - tmp_cuAddr12 > yMin) {
				tmp_puTilesBeg1 = puTilesBeg[cIdx][1];
				tmp_cuAddr13 = cuAddr[1];
				yMin = HevcDecoder_IntraPrediction_max(tmp_puTilesBeg1 - tmp_cuAddr13 + 1, yMin);
			}
			tmp_puTilesEnd = puTilesEnd[cIdx][1];
			tmp_cuAddr14 = cuAddr[1];
			if (tmp_puTilesEnd - tmp_cuAddr14 < yMax) {
				tmp_puTilesEnd0 = puTilesEnd[cIdx][1];
				tmp_cuAddr15 = cuAddr[1];
				yMax = HevcDecoder_IntraPrediction_min(tmp_puTilesEnd0 - tmp_cuAddr15 + 1, yMax);
			}
		}
	}
	tmp_cuAddr16 = cuAddr[1];
	if (tmp_cuAddr16 != 0) {
		tmp_cuAddr17 = cuAddr[1];
		tmp_cuAddr18 = cuAddr[1];
		if ((tmp_cuAddr17 & ~(maxCuSize - 1)) == (tmp_cuAddr18 - 1 & ~(maxCuSize - 1))) {
			tmp_absCoordToRasterScan0 = absCoordToRasterScan(cuAddr);
			tmp_aboveBlkAvail = aboveBlkAvail[tmp_absCoordToRasterScan0];
			tmp_pictSize0 = pictSize[cIdx][0];
			tmp_cuAddr19 = cuAddr[0];
			numPixRemain = HevcDecoder_IntraPrediction_min(tmp_aboveBlkAvail << 2, tmp_pictSize0 - tmp_cuAddr19);
		} else {
			tmp_pictSize1 = pictSize[cIdx][0];
			tmp_cuAddr20 = cuAddr[0];
			numPixRemain = tmp_pictSize1 - tmp_cuAddr20;
		}
		tmp_min0 = HevcDecoder_IntraPrediction_min(2 * nS, numPixRemain);
		xMax = tmp_min0 + 1;
		local_isIndepSlc = isIndepSlc;
		if (local_isIndepSlc) {
			tmp_cuAddr21 = cuAddr[1];
			tmp_sliceAddr6 = sliceAddr[cIdx][1];
			if (tmp_cuAddr21 == tmp_sliceAddr6) {
				xMin = xMax;
			} else {
				tmp_cuAddr22 = cuAddr[1];
				tmp_sliceAddr7 = sliceAddr[cIdx][1];
				tmp_cuAddr23 = cuAddr[0];
				tmp_sliceAddr8 = sliceAddr[cIdx][0];
				if (tmp_cuAddr22 == tmp_sliceAddr7 + maxCuSize && tmp_cuAddr23 - 1 < tmp_sliceAddr8) {
					tmp_sliceAddr9 = sliceAddr[cIdx][0];
					tmp_cuAddr24 = cuAddr[0];
					if (tmp_sliceAddr9 > tmp_cuAddr24 + 2 * nS) {
						xMin = xMax;
					} else {
						tmp_sliceAddr10 = sliceAddr[cIdx][0];
						tmp_cuAddr25 = cuAddr[0];
						if (tmp_sliceAddr10 > tmp_cuAddr25 - 1) {
							tmp_sliceAddr11 = sliceAddr[cIdx][0];
							tmp_cuAddr26 = cuAddr[0];
							xMin = tmp_sliceAddr11 - tmp_cuAddr26 + 1;
						}
					}
				}
			}
		}
		tmp_puTilesBeg2 = puTilesBeg[cIdx][1];
		tmp_cuAddr27 = cuAddr[1];
		if (tmp_puTilesBeg2 > tmp_cuAddr27 - 1) {
			xMin = xMax;
		} else {
			tmp_puTilesBeg3 = puTilesBeg[cIdx][0];
			tmp_cuAddr28 = cuAddr[0];
			if (tmp_puTilesBeg3 - tmp_cuAddr28 > xMin) {
				tmp_puTilesBeg4 = puTilesBeg[cIdx][0];
				tmp_cuAddr29 = cuAddr[0];
				xMin = HevcDecoder_IntraPrediction_max(tmp_puTilesBeg4 - tmp_cuAddr29 + 1, xMin);
			}
			tmp_puTilesEnd1 = puTilesEnd[cIdx][0];
			tmp_cuAddr30 = cuAddr[0];
			if (tmp_puTilesEnd1 - tmp_cuAddr30 < xMax) {
				tmp_puTilesEnd2 = puTilesEnd[cIdx][0];
				tmp_cuAddr31 = cuAddr[0];
				xMax = HevcDecoder_IntraPrediction_min(tmp_puTilesEnd2 - tmp_cuAddr31 + 1, xMax);
			}
		}
	}
	maxVal[0] = xMax;
	maxVal[1] = yMax;
	minVal[0] = xMin;
	minVal[1] = yMin;
}
static void filterNeighbSamp(u8 nS, u8 log2NS) {
	u32 bitDepthY;
	u32 threshold;
	u8 bottomLeft;
	u8 topLeft;
	u8 topRight;
	u8 edgePix[2];
	i32 bilinearLeft;
	i32 bilinearAbove;
	u8 minDistVertHor;
	u8 pFNeighb[2][64];
	u8 local_predMode;
	u8 local_INTRA_DC;
	i32 tmp_abs;
	i32 tmp_abs0;
	i32 local_strongIntraSmoothing;
	u8 tmp_pNeighb_left;
	i32 tmp_abs1;
	u8 tmp_pNeighb_above;
	i32 tmp_abs2;
	u32 neighb;
	u32 i;
	u8 tmp_edgePix;
	u32 i0;
	u8 tmp_pFNeighb;
	u8 tmp_pFNeighb0;
	u8 tmp_pNeighb_above0;
	u8 tmp_pNeighb_above1;
	u8 tmp_pNeighb_above2;
	u8 tmp_pNeighb_above3;
	u8 tmp_pNeighb_left0;
	u8 tmp_pNeighb_left1;
	u32 i1;
	u8 tmp_pNeighb_above4;
	u8 tmp_pNeighb_above5;
	u8 tmp_pNeighb_above6;
	u8 tmp_pNeighb_left2;
	u8 tmp_pNeighb_left3;
	u8 tmp_pNeighb_left4;
	u8 tmp_pNeighb_left5;
	u8 tmp_pNeighb_above7;
	u8 tmp_pNeighb_above8;
	u32 i2;
	u8 tmp_pFNeighb1;
	u8 tmp_pFNeighb2;
	u8 tmp_pNeighb_above9;
	u8 tmp_pNeighb_above10;
	u8 tmp_pNeighb_above11;
	u8 tmp_pNeighb_above12;
	u8 tmp_pNeighb_left6;
	u8 tmp_pNeighb_left7;
	u32 i3;
	u8 tmp_pNeighb_above13;
	u8 tmp_pNeighb_above14;
	u8 tmp_pNeighb_above15;
	u8 tmp_pNeighb_left8;
	u8 tmp_pNeighb_left9;
	u8 tmp_pNeighb_left10;
	u8 tmp_pNeighb_left11;
	u8 tmp_pNeighb_above16;
	u8 tmp_pNeighb_above17;
	u32 i4;
	u8 tmp_pFNeighb3;
	u8 tmp_pFNeighb4;

	bitDepthY = 8;
	threshold = 1 << (bitDepthY - 5);
	bottomLeft = pNeighb_left[2 * nS];
	topLeft = pNeighb_above[0];
	topRight = pNeighb_above[2 * nS];
	edgePix[0] = topRight;
	edgePix[1] = bottomLeft;
	local_predMode = predMode;
	local_INTRA_DC = INTRA_DC;
	if (local_predMode != local_INTRA_DC) {
		local_predMode = predMode;
		tmp_abs = HevcDecoder_IntraPrediction_abs(local_predMode - 26);
		local_predMode = predMode;
		tmp_abs0 = HevcDecoder_IntraPrediction_abs(local_predMode - 10);
		minDistVertHor = HevcDecoder_IntraPrediction_min(tmp_abs, tmp_abs0);
		if (nS == 4 && minDistVertHor > 10 || nS == 8 && minDistVertHor > 7 || nS == 16 && minDistVertHor > 1 || nS == 32 && minDistVertHor > 0 || nS == 64 && minDistVertHor > 10) {
			local_strongIntraSmoothing = strongIntraSmoothing;
			if (local_strongIntraSmoothing) {
				tmp_pNeighb_left = pNeighb_left[nS];
				tmp_abs1 = HevcDecoder_IntraPrediction_abs(bottomLeft + topLeft - 2 * tmp_pNeighb_left);
				bilinearLeft = tmp_abs1 < threshold;
				tmp_pNeighb_above = pNeighb_above[nS];
				tmp_abs2 = HevcDecoder_IntraPrediction_abs(topLeft + topRight - 2 * tmp_pNeighb_above);
				bilinearAbove = tmp_abs2 < threshold;
				if (nS >= 32 && bilinearLeft && bilinearAbove) {
					neighb = 0;
					while (neighb <= 1) {
						i = 1;
						while (i <= nS * 2 - 1) {
							tmp_edgePix = edgePix[neighb];
							pFNeighb[neighb][i] = ((2 * nS - i) * topLeft + i * tmp_edgePix + nS) >> (log2NS + 1);
							i = i + 1;
						}
						neighb = neighb + 1;
					}
					i0 = 1;
					while (i0 <= nS * 2 - 1) {
						tmp_pFNeighb = pFNeighb[0][i0];
						pNeighb_above[i0] = tmp_pFNeighb;
						tmp_pFNeighb0 = pFNeighb[1][i0];
						pNeighb_left[i0] = tmp_pFNeighb0;
						i0 = i0 + 1;
					}
				} else {
					tmp_pNeighb_above0 = pNeighb_above[0];
					tmp_pNeighb_above1 = pNeighb_above[0 + 1];
					tmp_pNeighb_above2 = pNeighb_above[1 + 1];
					pFNeighb[0][0] = (tmp_pNeighb_above0 + 2 * tmp_pNeighb_above1 + tmp_pNeighb_above2 + 2) >> 2;
					tmp_pNeighb_above3 = pNeighb_above[0];
					tmp_pNeighb_left0 = pNeighb_left[0 + 1];
					tmp_pNeighb_left1 = pNeighb_left[1 + 1];
					pFNeighb[1][0] = (tmp_pNeighb_above3 + 2 * tmp_pNeighb_left0 + tmp_pNeighb_left1 + 2) >> 2;
					i1 = 1;
					while (i1 <= nS * 2 - 2) {
						tmp_pNeighb_above4 = pNeighb_above[i1 - 1 + 1];
						tmp_pNeighb_above5 = pNeighb_above[i1 + 1];
						tmp_pNeighb_above6 = pNeighb_above[i1 + 1 + 1];
						pFNeighb[0][i1] = (tmp_pNeighb_above4 + 2 * tmp_pNeighb_above5 + tmp_pNeighb_above6 + 2) >> 2;
						tmp_pNeighb_left2 = pNeighb_left[i1 - 1 + 1];
						tmp_pNeighb_left3 = pNeighb_left[i1 + 1];
						tmp_pNeighb_left4 = pNeighb_left[i1 + 1 + 1];
						pFNeighb[1][i1] = (tmp_pNeighb_left2 + 2 * tmp_pNeighb_left3 + tmp_pNeighb_left4 + 2) >> 2;
						i1 = i1 + 1;
					}
					tmp_pNeighb_left5 = pNeighb_left[0 + 1];
					tmp_pNeighb_above7 = pNeighb_above[0];
					tmp_pNeighb_above8 = pNeighb_above[0 + 1];
					pNeighb_above[0] = (tmp_pNeighb_left5 + 2 * tmp_pNeighb_above7 + tmp_pNeighb_above8 + 2) >> 2;
					i2 = 0;
					while (i2 <= nS * 2 - 2) {
						tmp_pFNeighb1 = pFNeighb[0][i2];
						pNeighb_above[i2 + 1] = tmp_pFNeighb1;
						tmp_pFNeighb2 = pFNeighb[1][i2];
						pNeighb_left[i2 + 1] = tmp_pFNeighb2;
						i2 = i2 + 1;
					}
				}
			} else {
				tmp_pNeighb_above9 = pNeighb_above[0];
				tmp_pNeighb_above10 = pNeighb_above[0 + 1];
				tmp_pNeighb_above11 = pNeighb_above[1 + 1];
				pFNeighb[0][0] = (tmp_pNeighb_above9 + 2 * tmp_pNeighb_above10 + tmp_pNeighb_above11 + 2) >> 2;
				tmp_pNeighb_above12 = pNeighb_above[0];
				tmp_pNeighb_left6 = pNeighb_left[0 + 1];
				tmp_pNeighb_left7 = pNeighb_left[1 + 1];
				pFNeighb[1][0] = (tmp_pNeighb_above12 + 2 * tmp_pNeighb_left6 + tmp_pNeighb_left7 + 2) >> 2;
				i3 = 1;
				while (i3 <= nS * 2 - 2) {
					tmp_pNeighb_above13 = pNeighb_above[i3 - 1 + 1];
					tmp_pNeighb_above14 = pNeighb_above[i3 + 1];
					tmp_pNeighb_above15 = pNeighb_above[i3 + 1 + 1];
					pFNeighb[0][i3] = (tmp_pNeighb_above13 + 2 * tmp_pNeighb_above14 + tmp_pNeighb_above15 + 2) >> 2;
					tmp_pNeighb_left8 = pNeighb_left[i3 - 1 + 1];
					tmp_pNeighb_left9 = pNeighb_left[i3 + 1];
					tmp_pNeighb_left10 = pNeighb_left[i3 + 1 + 1];
					pFNeighb[1][i3] = (tmp_pNeighb_left8 + 2 * tmp_pNeighb_left9 + tmp_pNeighb_left10 + 2) >> 2;
					i3 = i3 + 1;
				}
				tmp_pNeighb_left11 = pNeighb_left[0 + 1];
				tmp_pNeighb_above16 = pNeighb_above[0];
				tmp_pNeighb_above17 = pNeighb_above[0 + 1];
				pNeighb_above[0] = (tmp_pNeighb_left11 + 2 * tmp_pNeighb_above16 + tmp_pNeighb_above17 + 2) >> 2;
				i4 = 0;
				while (i4 <= nS * 2 - 2) {
					tmp_pFNeighb3 = pFNeighb[0][i4];
					pNeighb_above[i4 + 1] = tmp_pFNeighb3;
					tmp_pFNeighb4 = pFNeighb[1][i4];
					pNeighb_left[i4 + 1] = tmp_pFNeighb4;
					i4 = i4 + 1;
				}
			}
		}
	}
}
static void intraDcPred(u8 cIdx, u8 nS, u8 log2NS) {
	u8 minVal;
	u16 dcVal;
	u32 x;
	u8 tmp_pNeighb_above;
	u32 y;
	u8 tmp_pNeighb_left;
	u8 tmp_pNeighb_left0;
	u8 tmp_pNeighb_above0;
	u32 x0;
	u8 tmp_pNeighb_above1;
	u32 y0;
	u8 tmp_pNeighb_left1;
	u32 y1;
	u32 x1;
	u32 y2;
	u32 x2;

	dcVal = nS;
	x = 0;
	while (x <= nS - 1) {
		tmp_pNeighb_above = pNeighb_above[x + 1];
		dcVal = dcVal + tmp_pNeighb_above;
		x = x + 1;
	}
	y = 0;
	while (y <= nS - 1) {
		tmp_pNeighb_left = pNeighb_left[y + 1];
		dcVal = dcVal + tmp_pNeighb_left;
		y = y + 1;
	}
	dcVal = dcVal >> (log2NS + 1);
	if (cIdx == 0) {
		if (nS > 16) {
			minVal = 0;
		} else {
			minVal = 1;
		}
		if (nS <= 16) {
			tmp_pNeighb_left0 = pNeighb_left[0 + 1];
			tmp_pNeighb_above0 = pNeighb_above[0 + 1];
			lumaComp[0] = (tmp_pNeighb_left0 + 2 * dcVal + tmp_pNeighb_above0 + 2) >> 2;
			x0 = 1;
			while (x0 <= nS - 1) {
				tmp_pNeighb_above1 = pNeighb_above[x0 + 1];
				lumaComp[x0] = (tmp_pNeighb_above1 + 3 * dcVal + 2) >> 2;
				x0 = x0 + 1;
			}
			y0 = 1;
			while (y0 <= nS - 1) {
				tmp_pNeighb_left1 = pNeighb_left[y0 + 1];
				lumaComp[y0 * 64] = (tmp_pNeighb_left1 + 3 * dcVal + 2) >> 2;
				y0 = y0 + 1;
			}
		}
		y1 = minVal;
		while (y1 <= nS - 1) {
			x1 = minVal;
			while (x1 <= nS - 1) {
				lumaComp[x1 + 64 * y1] = dcVal;
				x1 = x1 + 1;
			}
			y1 = y1 + 1;
		}
	} else {
		y2 = 0;
		while (y2 <= nS - 1) {
			x2 = 0;
			while (x2 <= nS - 1) {
				if (cIdx == 1) {
					chrComp_u[x2 + 32 * y2] = dcVal;
				} else {
					chrComp_v[x2 + 32 * y2] = dcVal;
				}
				x2 = x2 + 1;
			}
			y2 = y2 + 1;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
// Actions
static i32 isSchedulable_isNewSliceOrPict_notDep() {
	i32 result;
	u8 partMode;
	u8 local_PART_MODE_SLICE_INDEP;
	u8 local_PART_MODE_PICT;

	partMode = tokens_PartMode[(index_PartMode + (0)) % SIZE_PartMode];
	local_PART_MODE_SLICE_INDEP = HevcDecoder_IntraPrediction_PART_MODE_SLICE_INDEP;
	local_PART_MODE_PICT = HevcDecoder_IntraPrediction_PART_MODE_PICT;
	result = partMode == local_PART_MODE_SLICE_INDEP || partMode == local_PART_MODE_PICT;
	return result;
}

static void isNewSliceOrPict_notDep() {

	u8 partMode;
	u8 log2_lcuSz;
	i32 smoothing;
	i32 constrIntra;
	u16 valNumTiles;
	i32 i;
	u16 tmp_SliceAddr;
	i32 i0;
	u16 tmp_SliceAddr0;
	i32 i1;
	u16 tmp_SliceAddr1;
	i32 i2;
	u16 tmp_PictSize;
	i32 i3;
	u16 tmp_PictSize0;
	i32 i4;
	u16 tmp_PictSize1;
	u8 local_PART_MODE_SLICE_INDEP;
	u8 local_maxLcuSizeLuma;

	partMode = tokens_PartMode[(index_PartMode + (0)) % SIZE_PartMode];
	log2_lcuSz = tokens_LcuSizeMax[(index_LcuSizeMax + (0)) % SIZE_LcuSizeMax];
	smoothing = tokens_StrongIntraSmoothing[(index_StrongIntraSmoothing + (0)) % SIZE_StrongIntraSmoothing];
	constrIntra = tokens_StrongIntraSmoothing[(index_StrongIntraSmoothing + (1)) % SIZE_StrongIntraSmoothing];
	valNumTiles = tokens_TilesCoord[(index_TilesCoord + (0)) % SIZE_TilesCoord];
	i = 0;
	while (i <= 1) {
		tmp_SliceAddr = tokens_SliceAddr[(index_SliceAddr + (i)) % SIZE_SliceAddr];
		sliceAddr[0][i] = tmp_SliceAddr;
		i = i + 1;
	}
	i0 = 0;
	while (i0 <= 1) {
		tmp_SliceAddr0 = tokens_SliceAddr[(index_SliceAddr + (i0)) % SIZE_SliceAddr];
		sliceAddr[1][i0] = tmp_SliceAddr0 >> 1;
		i0 = i0 + 1;
	}
	i1 = 0;
	while (i1 <= 1) {
		tmp_SliceAddr1 = tokens_SliceAddr[(index_SliceAddr + (i1)) % SIZE_SliceAddr];
		sliceAddr[2][i1] = tmp_SliceAddr1 >> 1;
		i1 = i1 + 1;
	}
	i2 = 0;
	while (i2 <= 1) {
		tmp_PictSize = tokens_PictSize[(index_PictSize % SIZE_PictSize) + (i2)];
		pictSize[0][i2] = tmp_PictSize;
		i2 = i2 + 1;
	}
	i3 = 0;
	while (i3 <= 1) {
		tmp_PictSize0 = tokens_PictSize[(index_PictSize % SIZE_PictSize) + (i3)];
		pictSize[1][i3] = tmp_PictSize0 >> 1;
		i3 = i3 + 1;
	}
	i4 = 0;
	while (i4 <= 1) {
		tmp_PictSize1 = tokens_PictSize[(index_PictSize % SIZE_PictSize) + (i4)];
		pictSize[2][i4] = tmp_PictSize1 >> 1;
		i4 = i4 + 1;
	}
	strongIntraSmoothing = smoothing;
	constrIntraPred = constrIntra;
	local_PART_MODE_SLICE_INDEP = HevcDecoder_IntraPrediction_PART_MODE_SLICE_INDEP;
	isIndepSlc = partMode == local_PART_MODE_SLICE_INDEP;
	numTiles = valNumTiles;
	iLoop = 0;
	maxLcuSizeLuma = 1 << log2_lcuSz;
	local_maxLcuSizeLuma = maxLcuSizeLuma;
	maxLcuSizeChr = local_maxLcuSizeLuma >> 1;

	// Update ports indexes
	index_PartMode += 1;
	index_LcuSizeMax += 1;
	index_PictSize += 2;
	read_end_PictSize();
	index_SliceAddr += 2;
	read_end_SliceAddr();
	index_StrongIntraSmoothing += 2;
	read_end_StrongIntraSmoothing();
	index_TilesCoord += 1;

	rate_PartMode += 1;
	rate_LcuSizeMax += 1;
	rate_PictSize += 2;
	rate_SliceAddr += 2;
	rate_StrongIntraSmoothing += 2;
	rate_TilesCoord += 1;
}
static void isNewSliceOrPict_notDep_aligned() {

	u8 partMode;
	u8 log2_lcuSz;
	i32 smoothing;
	i32 constrIntra;
	u16 valNumTiles;
	i32 i;
	u16 tmp_SliceAddr;
	i32 i0;
	u16 tmp_SliceAddr0;
	i32 i1;
	u16 tmp_SliceAddr1;
	i32 i2;
	u16 tmp_PictSize;
	i32 i3;
	u16 tmp_PictSize0;
	i32 i4;
	u16 tmp_PictSize1;
	u8 local_PART_MODE_SLICE_INDEP;
	u8 local_maxLcuSizeLuma;

	partMode = tokens_PartMode[(index_PartMode + (0)) % SIZE_PartMode];
	log2_lcuSz = tokens_LcuSizeMax[(index_LcuSizeMax + (0)) % SIZE_LcuSizeMax];
	smoothing = tokens_StrongIntraSmoothing[(index_StrongIntraSmoothing % SIZE_StrongIntraSmoothing) + (0)];
	constrIntra = tokens_StrongIntraSmoothing[(index_StrongIntraSmoothing % SIZE_StrongIntraSmoothing) + (1)];
	valNumTiles = tokens_TilesCoord[(index_TilesCoord + (0)) % SIZE_TilesCoord];
	i = 0;
	while (i <= 1) {
		tmp_SliceAddr = tokens_SliceAddr[(index_SliceAddr % SIZE_SliceAddr) + (i)];
		sliceAddr[0][i] = tmp_SliceAddr;
		i = i + 1;
	}
	i0 = 0;
	while (i0 <= 1) {
		tmp_SliceAddr0 = tokens_SliceAddr[(index_SliceAddr % SIZE_SliceAddr) + (i0)];
		sliceAddr[1][i0] = tmp_SliceAddr0 >> 1;
		i0 = i0 + 1;
	}
	i1 = 0;
	while (i1 <= 1) {
		tmp_SliceAddr1 = tokens_SliceAddr[(index_SliceAddr % SIZE_SliceAddr) + (i1)];
		sliceAddr[2][i1] = tmp_SliceAddr1 >> 1;
		i1 = i1 + 1;
	}
	i2 = 0;
	while (i2 <= 1) {
		tmp_PictSize = tokens_PictSize[(index_PictSize % SIZE_PictSize) + (i2)];
		pictSize[0][i2] = tmp_PictSize;
		i2 = i2 + 1;
	}
	i3 = 0;
	while (i3 <= 1) {
		tmp_PictSize0 = tokens_PictSize[(index_PictSize % SIZE_PictSize) + (i3)];
		pictSize[1][i3] = tmp_PictSize0 >> 1;
		i3 = i3 + 1;
	}
	i4 = 0;
	while (i4 <= 1) {
		tmp_PictSize1 = tokens_PictSize[(index_PictSize % SIZE_PictSize) + (i4)];
		pictSize[2][i4] = tmp_PictSize1 >> 1;
		i4 = i4 + 1;
	}
	strongIntraSmoothing = smoothing;
	constrIntraPred = constrIntra;
	local_PART_MODE_SLICE_INDEP = HevcDecoder_IntraPrediction_PART_MODE_SLICE_INDEP;
	isIndepSlc = partMode == local_PART_MODE_SLICE_INDEP;
	numTiles = valNumTiles;
	iLoop = 0;
	maxLcuSizeLuma = 1 << log2_lcuSz;
	local_maxLcuSizeLuma = maxLcuSizeLuma;
	maxLcuSizeChr = local_maxLcuSizeLuma >> 1;

	// Update ports indexes
	index_PartMode += 1;
	index_LcuSizeMax += 1;
	index_PictSize += 2;
	read_end_PictSize();
	index_SliceAddr += 2;
	read_end_SliceAddr();
	index_StrongIntraSmoothing += 2;
	read_end_StrongIntraSmoothing();
	index_TilesCoord += 1;

	rate_PartMode += 1;
	rate_LcuSizeMax += 1;
	rate_PictSize += 2;
	rate_SliceAddr += 2;
	rate_StrongIntraSmoothing += 2;
	rate_TilesCoord += 1;
}
static i32 isSchedulable_isNewSliceOrPict_dep() {
	i32 result;
	u8 partMode;
	u8 local_PART_MODE_SLICE_DEP;

	partMode = tokens_PartMode[(index_PartMode + (0)) % SIZE_PartMode];
	local_PART_MODE_SLICE_DEP = HevcDecoder_IntraPrediction_PART_MODE_SLICE_DEP;
	result = partMode == local_PART_MODE_SLICE_DEP;
	return result;
}

static void isNewSliceOrPict_dep() {

	u8 partMode;
	i32 smoothing;
	i32 constrIntra;
	i32 i;
	u16 tmp_SliceAddr;
	i32 i0;
	u16 tmp_SliceAddr0;
	i32 i1;
	u16 tmp_SliceAddr1;
	u8 local_PART_MODE_SLICE_INDEP;

	partMode = tokens_PartMode[(index_PartMode + (0)) % SIZE_PartMode];
	smoothing = tokens_StrongIntraSmoothing[(index_StrongIntraSmoothing + (0)) % SIZE_StrongIntraSmoothing];
	constrIntra = tokens_StrongIntraSmoothing[(index_StrongIntraSmoothing + (1)) % SIZE_StrongIntraSmoothing];
	i = 0;
	while (i <= 1) {
		tmp_SliceAddr = tokens_SliceAddr[(index_SliceAddr + (i)) % SIZE_SliceAddr];
		sliceAddr[0][i] = tmp_SliceAddr;
		i = i + 1;
	}
	i0 = 0;
	while (i0 <= 1) {
		tmp_SliceAddr0 = tokens_SliceAddr[(index_SliceAddr + (i0)) % SIZE_SliceAddr];
		sliceAddr[1][i0] = tmp_SliceAddr0 >> 1;
		i0 = i0 + 1;
	}
	i1 = 0;
	while (i1 <= 1) {
		tmp_SliceAddr1 = tokens_SliceAddr[(index_SliceAddr + (i1)) % SIZE_SliceAddr];
		sliceAddr[2][i1] = tmp_SliceAddr1 >> 1;
		i1 = i1 + 1;
	}
	strongIntraSmoothing = smoothing;
	constrIntraPred = constrIntra;
	local_PART_MODE_SLICE_INDEP = HevcDecoder_IntraPrediction_PART_MODE_SLICE_INDEP;
	isIndepSlc = partMode == local_PART_MODE_SLICE_INDEP;

	// Update ports indexes
	index_PartMode += 1;
	index_SliceAddr += 2;
	read_end_SliceAddr();
	index_StrongIntraSmoothing += 2;
	read_end_StrongIntraSmoothing();

	rate_PartMode += 1;
	rate_SliceAddr += 2;
	rate_StrongIntraSmoothing += 2;
}
static void isNewSliceOrPict_dep_aligned() {

	u8 partMode;
	i32 smoothing;
	i32 constrIntra;
	i32 i;
	u16 tmp_SliceAddr;
	i32 i0;
	u16 tmp_SliceAddr0;
	i32 i1;
	u16 tmp_SliceAddr1;
	u8 local_PART_MODE_SLICE_INDEP;

	partMode = tokens_PartMode[(index_PartMode + (0)) % SIZE_PartMode];
	smoothing = tokens_StrongIntraSmoothing[(index_StrongIntraSmoothing % SIZE_StrongIntraSmoothing) + (0)];
	constrIntra = tokens_StrongIntraSmoothing[(index_StrongIntraSmoothing % SIZE_StrongIntraSmoothing) + (1)];
	i = 0;
	while (i <= 1) {
		tmp_SliceAddr = tokens_SliceAddr[(index_SliceAddr % SIZE_SliceAddr) + (i)];
		sliceAddr[0][i] = tmp_SliceAddr;
		i = i + 1;
	}
	i0 = 0;
	while (i0 <= 1) {
		tmp_SliceAddr0 = tokens_SliceAddr[(index_SliceAddr % SIZE_SliceAddr) + (i0)];
		sliceAddr[1][i0] = tmp_SliceAddr0 >> 1;
		i0 = i0 + 1;
	}
	i1 = 0;
	while (i1 <= 1) {
		tmp_SliceAddr1 = tokens_SliceAddr[(index_SliceAddr % SIZE_SliceAddr) + (i1)];
		sliceAddr[2][i1] = tmp_SliceAddr1 >> 1;
		i1 = i1 + 1;
	}
	strongIntraSmoothing = smoothing;
	constrIntraPred = constrIntra;
	local_PART_MODE_SLICE_INDEP = HevcDecoder_IntraPrediction_PART_MODE_SLICE_INDEP;
	isIndepSlc = partMode == local_PART_MODE_SLICE_INDEP;

	// Update ports indexes
	index_PartMode += 1;
	index_SliceAddr += 2;
	read_end_SliceAddr();
	index_StrongIntraSmoothing += 2;
	read_end_StrongIntraSmoothing();

	rate_PartMode += 1;
	rate_SliceAddr += 2;
	rate_StrongIntraSmoothing += 2;
}
static i32 isSchedulable_getTilesCoord_launch() {
	i32 result;
	i16 local_iLoop;
	u16 local_numTiles;

	local_iLoop = iLoop;
	local_numTiles = numTiles;
	result = local_iLoop < local_numTiles;
	return result;
}

static void getTilesCoord_launch() {

	i16 local_iLoop;
	u16 tmp_TilesCoord;
	u16 tmp_TilesCoord0;
	u16 tmp_TilesCoord1;
	u16 tmp_TilesCoord2;

	local_iLoop = iLoop;
	tmp_TilesCoord = tokens_TilesCoord[(index_TilesCoord + (0)) % SIZE_TilesCoord];
	tilesBeg[local_iLoop][0] = tmp_TilesCoord;
	tmp_TilesCoord0 = tokens_TilesCoord[(index_TilesCoord + (1)) % SIZE_TilesCoord];
	tilesBeg[local_iLoop][1] = tmp_TilesCoord0;
	local_iLoop = iLoop;
	tmp_TilesCoord1 = tokens_TilesCoord[(index_TilesCoord + (2)) % SIZE_TilesCoord];
	tilesEnd[local_iLoop][0] = tmp_TilesCoord1;
	tmp_TilesCoord2 = tokens_TilesCoord[(index_TilesCoord + (3)) % SIZE_TilesCoord];
	tilesEnd[local_iLoop][1] = tmp_TilesCoord2;
	local_iLoop = iLoop;
	iLoop = local_iLoop + 1;

	// Update ports indexes
	index_TilesCoord += 4;
	read_end_TilesCoord();

	rate_TilesCoord += 4;
}
static void getTilesCoord_launch_aligned() {

	i16 local_iLoop;
	u16 tmp_TilesCoord;
	u16 tmp_TilesCoord0;
	u16 tmp_TilesCoord1;
	u16 tmp_TilesCoord2;

	local_iLoop = iLoop;
	tmp_TilesCoord = tokens_TilesCoord[(index_TilesCoord % SIZE_TilesCoord) + (0)];
	tilesBeg[local_iLoop][0] = tmp_TilesCoord;
	tmp_TilesCoord0 = tokens_TilesCoord[(index_TilesCoord % SIZE_TilesCoord) + (1)];
	tilesBeg[local_iLoop][1] = tmp_TilesCoord0;
	local_iLoop = iLoop;
	tmp_TilesCoord1 = tokens_TilesCoord[(index_TilesCoord % SIZE_TilesCoord) + (2)];
	tilesEnd[local_iLoop][0] = tmp_TilesCoord1;
	tmp_TilesCoord2 = tokens_TilesCoord[(index_TilesCoord % SIZE_TilesCoord) + (3)];
	tilesEnd[local_iLoop][1] = tmp_TilesCoord2;
	local_iLoop = iLoop;
	iLoop = local_iLoop + 1;

	// Update ports indexes
	index_TilesCoord += 4;
	read_end_TilesCoord();

	rate_TilesCoord += 4;
}
static i32 isSchedulable_getTilesCoord_done() {
	i32 result;
	i16 local_iLoop;
	u16 local_numTiles;

	local_iLoop = iLoop;
	local_numTiles = numTiles;
	result = local_iLoop == local_numTiles;
	return result;
}

static void getTilesCoord_done() {



	// Update ports indexes

}
static i32 isSchedulable_getPartMode_isNonQuadTree() {
	i32 result;
	u8 partMode;
	u8 local_PART_MODE_SLICE_DEP;
	u8 local_PART_MODE_SLICE_INDEP;
	u8 local_PART_MODE_PICT;
	u8 local_PART_2Nx2N;
	u8 local_PART_NxN;

	partMode = tokens_PartMode[(index_PartMode + (0)) % SIZE_PartMode];
	local_PART_MODE_SLICE_DEP = HevcDecoder_IntraPrediction_PART_MODE_SLICE_DEP;
	local_PART_MODE_SLICE_INDEP = HevcDecoder_IntraPrediction_PART_MODE_SLICE_INDEP;
	local_PART_MODE_PICT = HevcDecoder_IntraPrediction_PART_MODE_PICT;
	local_PART_2Nx2N = HevcDecoder_IntraPrediction_PART_2Nx2N;
	local_PART_NxN = HevcDecoder_IntraPrediction_PART_NxN;
	result = partMode != local_PART_MODE_SLICE_DEP && partMode != local_PART_MODE_SLICE_INDEP && partMode != local_PART_MODE_PICT && (partMode != local_PART_2Nx2N && partMode != local_PART_NxN);
	return result;
}

static void getPartMode_isNonQuadTree() {

	u8 partMode;

	partMode = tokens_PartMode[(index_PartMode + (0)) % SIZE_PartMode];

	// Update ports indexes
	index_PartMode += 1;

	rate_PartMode += 1;
}
static i32 isSchedulable_getPartMode_isQuadTree() {
	i32 result;
	u8 partMode;
	u8 local_PART_2Nx2N;
	u8 local_PART_NxN;

	partMode = tokens_PartMode[(index_PartMode + (0)) % SIZE_PartMode];
	local_PART_2Nx2N = HevcDecoder_IntraPrediction_PART_2Nx2N;
	local_PART_NxN = HevcDecoder_IntraPrediction_PART_NxN;
	result = partMode == local_PART_2Nx2N || partMode == local_PART_NxN;
	return result;
}

static void getPartMode_isQuadTree() {

	u8 partMode;
	u8 tmp_partModeToNumPart;

	partMode = tokens_PartMode[(index_PartMode + (0)) % SIZE_PartMode];
	tmp_partModeToNumPart = HevcDecoder_IntraPrediction_partModeToNumPart[partMode];
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
	i32 local_EnabSkipInPix;
	u16 tmp_CUInfo;
	u8 local_IN_SAMP;

	local_numPartDecoded = numPartDecoded;
	local_numPart = numPart;
	local_EnabSkipInPix = EnabSkipInPix;
	tmp_CUInfo = tokens_CUInfo[(index_CUInfo + (0)) % SIZE_CUInfo];
	local_IN_SAMP = HevcDecoder_IntraPrediction_IN_SAMP;
	result = local_numPartDecoded < local_numPart && (!local_EnabSkipInPix || tmp_CUInfo != local_IN_SAMP);
	return result;
}

static void getCuInfo_launch() {

	u16 tmp_CUInfo;
	i32 local_EnabSkipInPix;
	u8 local_cuMode;
	u8 local_NO_IN_SAMP;
	u16 tmp_CUInfo0;
	u16 tmp_CUInfo1;
	u16 tmp_CUInfo2;
	u8 local_numPartDecoded;

	tmp_CUInfo = tokens_CUInfo[(index_CUInfo + (0)) % SIZE_CUInfo];
	cuMode = tmp_CUInfo;
	getInSamp = 1;
	local_EnabSkipInPix = EnabSkipInPix;
	local_cuMode = cuMode;
	local_NO_IN_SAMP = HevcDecoder_IntraPrediction_NO_IN_SAMP;
	if (local_EnabSkipInPix && (local_cuMode & local_NO_IN_SAMP) != 0) {
		getInSamp = 0;
		local_cuMode = cuMode;
		local_NO_IN_SAMP = HevcDecoder_IntraPrediction_NO_IN_SAMP;
		cuMode = local_cuMode - local_NO_IN_SAMP;
	}
	tmp_CUInfo0 = tokens_CUInfo[(index_CUInfo + (3)) % SIZE_CUInfo];
	nS = tmp_CUInfo0;
	tmp_CUInfo1 = tokens_CUInfo[(index_CUInfo + (1)) % SIZE_CUInfo];
	cuAddr[0] = tmp_CUInfo1;
	tmp_CUInfo2 = tokens_CUInfo[(index_CUInfo + (2)) % SIZE_CUInfo];
	cuAddr[1] = tmp_CUInfo2;
	local_numPartDecoded = numPartDecoded;
	numPartDecoded = local_numPartDecoded + 1;

	// Update ports indexes
	index_CUInfo += 5;
	read_end_CUInfo();

	rate_CUInfo += 5;
}
static void getCuInfo_launch_aligned() {

	u16 tmp_CUInfo;
	i32 local_EnabSkipInPix;
	u8 local_cuMode;
	u8 local_NO_IN_SAMP;
	u16 tmp_CUInfo0;
	u16 tmp_CUInfo1;
	u16 tmp_CUInfo2;
	u8 local_numPartDecoded;

	tmp_CUInfo = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (0)];
	cuMode = tmp_CUInfo;
	getInSamp = 1;
	local_EnabSkipInPix = EnabSkipInPix;
	local_cuMode = cuMode;
	local_NO_IN_SAMP = HevcDecoder_IntraPrediction_NO_IN_SAMP;
	if (local_EnabSkipInPix && (local_cuMode & local_NO_IN_SAMP) != 0) {
		getInSamp = 0;
		local_cuMode = cuMode;
		local_NO_IN_SAMP = HevcDecoder_IntraPrediction_NO_IN_SAMP;
		cuMode = local_cuMode - local_NO_IN_SAMP;
	}
	tmp_CUInfo0 = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (3)];
	nS = tmp_CUInfo0;
	tmp_CUInfo1 = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (1)];
	cuAddr[0] = tmp_CUInfo1;
	tmp_CUInfo2 = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (2)];
	cuAddr[1] = tmp_CUInfo2;
	local_numPartDecoded = numPartDecoded;
	numPartDecoded = local_numPartDecoded + 1;

	// Update ports indexes
	index_CUInfo += 5;
	read_end_CUInfo();

	rate_CUInfo += 5;
}
static i32 isSchedulable_getCuInfo_getInSamp() {
	i32 result;
	u8 local_numPartDecoded;
	u8 local_numPart;
	i32 local_EnabSkipInPix;
	u16 tmp_CUInfo;
	u8 local_IN_SAMP;

	local_numPartDecoded = numPartDecoded;
	local_numPart = numPart;
	local_EnabSkipInPix = EnabSkipInPix;
	tmp_CUInfo = tokens_CUInfo[(index_CUInfo + (0)) % SIZE_CUInfo];
	local_IN_SAMP = HevcDecoder_IntraPrediction_IN_SAMP;
	result = local_numPartDecoded < local_numPart && (local_EnabSkipInPix && tmp_CUInfo == local_IN_SAMP);
	return result;
}

static void getCuInfo_getInSamp() {

	u8 nS;
	u16 tmp_CUInfo;
	u16 tmp_CUInfo0;
	u8 local_numPartDecoded;

	nS = tokens_CUInfo[(index_CUInfo + (3)) % SIZE_CUInfo];
	getInSamp = 1;
	tmp_CUInfo = tokens_CUInfo[(index_CUInfo + (1)) % SIZE_CUInfo];
	treeAddr[0] = tmp_CUInfo;
	tmp_CUInfo0 = tokens_CUInfo[(index_CUInfo + (2)) % SIZE_CUInfo];
	treeAddr[1] = tmp_CUInfo0;
	idxBlk = 0;
	numBlkToSend = nS * nS / 16;
	neighbBlkSz = nS;
	local_numPartDecoded = numPartDecoded;
	numPartDecoded = local_numPartDecoded + 1;

	// Update ports indexes
	index_CUInfo += 5;
	read_end_CUInfo();

	rate_CUInfo += 5;
}
static void getCuInfo_getInSamp_aligned() {

	u8 nS;
	u16 tmp_CUInfo;
	u16 tmp_CUInfo0;
	u8 local_numPartDecoded;

	nS = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (3)];
	getInSamp = 1;
	tmp_CUInfo = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (1)];
	treeAddr[0] = tmp_CUInfo;
	tmp_CUInfo0 = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (2)];
	treeAddr[1] = tmp_CUInfo0;
	idxBlk = 0;
	numBlkToSend = nS * nS / 16;
	neighbBlkSz = nS;
	local_numPartDecoded = numPartDecoded;
	numPartDecoded = local_numPartDecoded + 1;

	// Update ports indexes
	index_CUInfo += 5;
	read_end_CUInfo();

	rate_CUInfo += 5;
}
static i32 isSchedulable_getCuInfo_nonQT_isInter() {
	i32 result;

	result = 1;
	return result;
}

static void getCuInfo_nonQT_isInter() {

	u16 tmp_CUInfo;
	i32 local_EnabSkipInPix;
	u8 local_cuMode;
	u8 local_NO_IN_SAMP;
	u16 tmp_CUInfo0;
	u16 tmp_CUInfo1;
	i32 tmp_max;
	u8 local_nS;
	u16 tmp_CUInfo2;
	u16 tmp_CUInfo3;

	tmp_CUInfo = tokens_CUInfo[(index_CUInfo + (0)) % SIZE_CUInfo];
	cuMode = tmp_CUInfo;
	getInSamp = 1;
	local_EnabSkipInPix = EnabSkipInPix;
	local_cuMode = cuMode;
	local_NO_IN_SAMP = HevcDecoder_IntraPrediction_NO_IN_SAMP;
	if (local_EnabSkipInPix && (local_cuMode & local_NO_IN_SAMP) != 0) {
		getInSamp = 0;
		local_cuMode = cuMode;
		local_NO_IN_SAMP = HevcDecoder_IntraPrediction_NO_IN_SAMP;
		cuMode = local_cuMode - local_NO_IN_SAMP;
	}
	tmp_CUInfo0 = tokens_CUInfo[(index_CUInfo + (3)) % SIZE_CUInfo];
	tmp_CUInfo1 = tokens_CUInfo[(index_CUInfo + (4)) % SIZE_CUInfo];
	tmp_max = HevcDecoder_IntraPrediction_max(tmp_CUInfo0, tmp_CUInfo1);
	nS = tmp_max;
	idxBlk = 0;
	local_nS = nS;
	local_nS = nS;
	numBlkToSend = local_nS * local_nS / 16;
	local_nS = nS;
	neighbBlkSz = local_nS;
	tmp_CUInfo2 = tokens_CUInfo[(index_CUInfo + (1)) % SIZE_CUInfo];
	treeAddr[0] = tmp_CUInfo2;
	tmp_CUInfo3 = tokens_CUInfo[(index_CUInfo + (2)) % SIZE_CUInfo];
	treeAddr[1] = tmp_CUInfo3;
	numPart = 2;
	numPartDecoded = 2;
	trafoTreeDepth = 0;
	trafoTreeIdx[0] = 3;

	// Update ports indexes
	index_CUInfo += 10;
	read_end_CUInfo();

	rate_CUInfo += 10;
}
static void getCuInfo_nonQT_isInter_aligned() {

	u16 tmp_CUInfo;
	i32 local_EnabSkipInPix;
	u8 local_cuMode;
	u8 local_NO_IN_SAMP;
	u16 tmp_CUInfo0;
	u16 tmp_CUInfo1;
	i32 tmp_max;
	u8 local_nS;
	u16 tmp_CUInfo2;
	u16 tmp_CUInfo3;

	tmp_CUInfo = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (0)];
	cuMode = tmp_CUInfo;
	getInSamp = 1;
	local_EnabSkipInPix = EnabSkipInPix;
	local_cuMode = cuMode;
	local_NO_IN_SAMP = HevcDecoder_IntraPrediction_NO_IN_SAMP;
	if (local_EnabSkipInPix && (local_cuMode & local_NO_IN_SAMP) != 0) {
		getInSamp = 0;
		local_cuMode = cuMode;
		local_NO_IN_SAMP = HevcDecoder_IntraPrediction_NO_IN_SAMP;
		cuMode = local_cuMode - local_NO_IN_SAMP;
	}
	tmp_CUInfo0 = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (3)];
	tmp_CUInfo1 = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (4)];
	tmp_max = HevcDecoder_IntraPrediction_max(tmp_CUInfo0, tmp_CUInfo1);
	nS = tmp_max;
	idxBlk = 0;
	local_nS = nS;
	local_nS = nS;
	numBlkToSend = local_nS * local_nS / 16;
	local_nS = nS;
	neighbBlkSz = local_nS;
	tmp_CUInfo2 = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (1)];
	treeAddr[0] = tmp_CUInfo2;
	tmp_CUInfo3 = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (2)];
	treeAddr[1] = tmp_CUInfo3;
	numPart = 2;
	numPartDecoded = 2;
	trafoTreeDepth = 0;
	trafoTreeIdx[0] = 3;

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
	local_INTRA = HevcDecoder_IntraPrediction_INTRA;
	result = local_cuMode == local_INTRA;
	return result;
}

static void getCuMode_isIntra_aligned() {

	i32 tileIdx;
	u16 local_numTiles;
	u16 tmp_cuAddr;
	u16 tmp_tilesBeg;
	u16 tmp_cuAddr0;
	u16 tmp_tilesEnd;
	u16 tmp_cuAddr1;
	u16 tmp_tilesBeg0;
	u16 tmp_cuAddr2;
	u16 tmp_tilesEnd0;
	u16 tmp_tilesBeg1;
	u16 tmp_tilesBeg2;
	i16 tmp_puTilesBeg;
	i16 tmp_puTilesBeg0;
	i16 tmp_puTilesBeg1;
	i16 tmp_puTilesBeg2;
	u16 tmp_tilesEnd1;
	u16 tmp_tilesEnd2;
	i16 tmp_puTilesEnd;
	i16 tmp_puTilesEnd0;
	i16 tmp_puTilesEnd1;
	i16 tmp_puTilesEnd2;
	u8 tmp_IntraPredMode;
	u8 tmp_IntraPredMode0;
	u8 tmp_IntraPredMode1;
	u8 local_log2NS;
	u8 local_nS;

	tileIdx = 0;
	local_numTiles = numTiles;
	while (tileIdx <= local_numTiles - 1) {
		tmp_cuAddr = cuAddr[0];
		tmp_tilesBeg = tilesBeg[tileIdx][0];
		tmp_cuAddr0 = cuAddr[0];
		tmp_tilesEnd = tilesEnd[tileIdx][0];
		tmp_cuAddr1 = cuAddr[1];
		tmp_tilesBeg0 = tilesBeg[tileIdx][1];
		tmp_cuAddr2 = cuAddr[1];
		tmp_tilesEnd0 = tilesEnd[tileIdx][1];
		if (tmp_cuAddr >= tmp_tilesBeg && tmp_cuAddr0 < tmp_tilesEnd && tmp_cuAddr1 >= tmp_tilesBeg0 && tmp_cuAddr2 < tmp_tilesEnd0) {
			tmp_tilesBeg1 = tilesBeg[tileIdx][0];
			puTilesBeg[0][0] = tmp_tilesBeg1;
			tmp_tilesBeg2 = tilesBeg[tileIdx][1];
			puTilesBeg[0][1] = tmp_tilesBeg2;
			tmp_puTilesBeg = puTilesBeg[0][0];
			puTilesBeg[1][0] = tmp_puTilesBeg / 2;
			tmp_puTilesBeg0 = puTilesBeg[0][1];
			puTilesBeg[1][1] = tmp_puTilesBeg0 / 2;
			tmp_puTilesBeg1 = puTilesBeg[1][0];
			puTilesBeg[2][0] = tmp_puTilesBeg1;
			tmp_puTilesBeg2 = puTilesBeg[1][1];
			puTilesBeg[2][1] = tmp_puTilesBeg2;
			tmp_tilesEnd1 = tilesEnd[tileIdx][0];
			puTilesEnd[0][0] = tmp_tilesEnd1;
			tmp_tilesEnd2 = tilesEnd[tileIdx][1];
			puTilesEnd[0][1] = tmp_tilesEnd2;
			tmp_puTilesEnd = puTilesEnd[0][0];
			puTilesEnd[1][0] = tmp_puTilesEnd / 2;
			tmp_puTilesEnd0 = puTilesEnd[0][1];
			puTilesEnd[1][1] = tmp_puTilesEnd0 / 2;
			tmp_puTilesEnd1 = puTilesEnd[1][0];
			puTilesEnd[2][0] = tmp_puTilesEnd1;
			tmp_puTilesEnd2 = puTilesEnd[1][1];
			puTilesEnd[2][1] = tmp_puTilesEnd2;
		}
		tileIdx = tileIdx + 1;
	}
	tmp_IntraPredMode = tokens_IntraPredMode[(index_IntraPredMode % SIZE_IntraPredMode) + (0)];
	predModeTab[0] = tmp_IntraPredMode;
	tmp_IntraPredMode0 = tokens_IntraPredMode[(index_IntraPredMode % SIZE_IntraPredMode) + (1)];
	predModeTab[1] = tmp_IntraPredMode0;
	tmp_IntraPredMode1 = tokens_IntraPredMode[(index_IntraPredMode % SIZE_IntraPredMode) + (1)];
	predModeTab[2] = tmp_IntraPredMode1;
	log2NS = 2;
	local_log2NS = log2NS;
	local_nS = nS;
	while (1 << local_log2NS < local_nS) {
		local_log2NS = log2NS;
		log2NS = local_log2NS + 1;
		local_log2NS = log2NS;
		local_nS = nS;
	}
	trafoTreeDepth = 0;
	trafoTreeIdx[0] = 3;

	// Update ports indexes
	index_IntraPredMode += 2;
	read_end_IntraPredMode();

	rate_IntraPredMode += 2;
}
static i32 isSchedulable_getCuMode_isInter() {
	i32 result;
	u8 local_cuMode;
	u8 local_INTER;
	u8 local_SKIP;

	local_cuMode = cuMode;
	local_INTER = HevcDecoder_IntraPrediction_INTER;
	local_cuMode = cuMode;
	local_SKIP = HevcDecoder_IntraPrediction_SKIP;
	result = local_cuMode == local_INTER || local_cuMode == local_SKIP;
	return result;
}

static void getCuMode_isInter() {

	u8 local_nS;
	i32 i;
	u16 tmp_cuAddr;

	idxBlk = 0;
	local_nS = nS;
	local_nS = nS;
	numBlkToSend = local_nS * local_nS / 16;
	local_nS = nS;
	neighbBlkSz = local_nS;
	i = 0;
	while (i <= 1) {
		tmp_cuAddr = cuAddr[i];
		treeAddr[i] = tmp_cuAddr;
		i = i + 1;
	}
	trafoTreeDepth = 0;
	trafoTreeIdx[0] = 3;

	// Update ports indexes

}
static i32 isSchedulable_getCuMode_isOther() {
	i32 result;
	u8 local_cuMode;
	u8 local_OTHER;

	local_cuMode = cuMode;
	local_OTHER = HevcDecoder_IntraPrediction_OTHER;
	result = local_cuMode == local_OTHER;
	return result;
}

static void getCuMode_isOther() {



	// Update ports indexes

}
static i32 isSchedulable_getSplitTrafo_isTrue() {
	i32 result;
	i32 splitTrafo;
	i8 local_trafoTreeDepth;

	splitTrafo = tokens_SplitTransform[(index_SplitTransform + (0)) % SIZE_SplitTransform];
	local_trafoTreeDepth = trafoTreeDepth;
	result = splitTrafo && local_trafoTreeDepth > -1;
	return result;
}

static void getSplitTrafo_isTrue() {

	i32 splitTrafo;
	i8 local_trafoTreeDepth;

	splitTrafo = tokens_SplitTransform[(index_SplitTransform + (0)) % SIZE_SplitTransform];
	local_trafoTreeDepth = trafoTreeDepth;
	trafoTreeDepth = local_trafoTreeDepth + 1;
	local_trafoTreeDepth = trafoTreeDepth;
	trafoTreeIdx[local_trafoTreeDepth] = 0;

	// Update ports indexes
	index_SplitTransform += 1;

	rate_SplitTransform += 1;
}
static i32 isSchedulable_getSplitTrafo_isFalse() {
	i32 result;
	i32 splitTrafo;
	i8 local_trafoTreeDepth;

	splitTrafo = tokens_SplitTransform[(index_SplitTransform + (0)) % SIZE_SplitTransform];
	local_trafoTreeDepth = trafoTreeDepth;
	result = !splitTrafo && local_trafoTreeDepth > -1;
	return result;
}

static void getSplitTrafo_isFalse() {

	i32 splitTrafo;
	u8 cIdxMax;
	u8 treeNS;
	u8 treeLog2NS;
	u16 locAddr[2];
	u8 off[2];
	i32 stride;
	u8 local_log2NS;
	i8 local_trafoTreeDepth;
	u8 local_nS;
	i32 i;
	u16 tmp_cuAddr;
	u32 idx;
	u8 tmp_trafoTreeIdx;
	u16 tmp_treeAddr;
	u8 tmp_trafoTreeIdx0;
	u16 tmp_treeAddr0;
	u16 tmp_treeAddr1;
	u16 tmp_treeAddr2;
	i32 i0;
	u16 tmp_treeAddr3;
	u32 cIdx;
	u8 tmp_predModeTab;
	u16 tmp_locAddr;
	u16 tmp_locAddr0;
	u8 tmp_pNeighb_above;
	u8 local_predMode;
	u8 local_INTRA_PLANAR;
	u8 local_INTRA_DC;
	i32 i1;
	u16 tmp_treeAddr4;
	u8 tmp_off;
	u8 tmp_off0;
	u32 comp;
	i32 y;
	i32 x;
	u8 tmp_off1;
	u8 tmp_off2;
	u8 tmp_chrComp_u;
	u8 tmp_off3;
	u8 tmp_off4;
	u8 tmp_chrComp_v;
	u8 tmp_trafoTreeIdx1;
	i32 tmp_if;
	u8 tmp_trafoTreeIdx2;
	u8 tmp_trafoTreeIdx3;

	splitTrafo = tokens_SplitTransform[(index_SplitTransform + (0)) % SIZE_SplitTransform];
	stride = 64;
	local_log2NS = log2NS;
	local_trafoTreeDepth = trafoTreeDepth;
	treeLog2NS = local_log2NS - local_trafoTreeDepth;
	local_nS = nS;
	treeNS = local_nS;
	i = 0;
	while (i <= 1) {
		tmp_cuAddr = cuAddr[i];
		treeAddr[i] = tmp_cuAddr;
		i = i + 1;
	}
	idx = 1;
	local_trafoTreeDepth = trafoTreeDepth;
	while (idx <= local_trafoTreeDepth) {
		treeNS = treeNS >> 1;
		tmp_trafoTreeIdx = trafoTreeIdx[idx];
		if ((tmp_trafoTreeIdx & 1) != 0) {
			tmp_treeAddr = treeAddr[0];
			treeAddr[0] = tmp_treeAddr + treeNS;
		}
		tmp_trafoTreeIdx0 = trafoTreeIdx[idx];
		if ((tmp_trafoTreeIdx0 & 2) != 0) {
			tmp_treeAddr0 = treeAddr[1];
			treeAddr[1] = tmp_treeAddr0 + treeNS;
		}
		idx = idx + 1;
	}
	numBlkToSend = treeNS * treeNS / 16;
	neighbBlkSz = treeNS;
	idxBlk = 0;
	if (treeLog2NS != 2) {
		cIdxMax = 3;
	} else {
		tmp_treeAddr1 = treeAddr[0];
		tmp_treeAddr2 = treeAddr[1];
		if ((tmp_treeAddr1 & 7) == 0 && (tmp_treeAddr2 & 7) == 0) {
			cIdxMax = 3;
		} else {
			cIdxMax = 1;
		}
	}
	i0 = 0;
	while (i0 <= 1) {
		tmp_treeAddr3 = treeAddr[i0];
		locAddr[i0] = tmp_treeAddr3;
		i0 = i0 + 1;
	}
	cIdx = 0;
	while (cIdx <= cIdxMax - 1) {
		tmp_predModeTab = predModeTab[cIdx];
		predMode = tmp_predModeTab;
		if (cIdx == 1) {
			if (treeLog2NS != 2) {
				treeNS = treeNS >> 1;
				treeLog2NS = treeLog2NS - 1;
			}
			tmp_locAddr = locAddr[0];
			locAddr[0] = tmp_locAddr >> 1;
			tmp_locAddr0 = locAddr[1];
			locAddr[1] = tmp_locAddr0 >> 1;
			stride = 32;
		}
		getNeighbSamples(locAddr, cIdx, treeNS, treeLog2NS);
		tmp_pNeighb_above = pNeighb_above[0];
		pNeighb_left[0] = tmp_pNeighb_above;
		if (cIdx == 0) {
			local_predMode = predMode;
			local_INTRA_PLANAR = INTRA_PLANAR;
			if (local_predMode == local_INTRA_PLANAR) {
				HevcDecoder_IntraPrediction_intraPlanarPred(lumaComp, pNeighb_above, pNeighb_left, stride, treeLog2NS);
			} else {
				local_predMode = predMode;
				local_INTRA_DC = INTRA_DC;
				if (local_predMode == local_INTRA_DC) {
					intraDcPred(cIdx, treeNS, treeLog2NS);
				} else {
					local_predMode = predMode;
					HevcDecoder_IntraPrediction_intraAngularPred(lumaComp, pNeighb_above, pNeighb_left, stride, cIdx, local_predMode, treeLog2NS);
				}
			}
		} else {
			if (cIdx == 1) {
				local_predMode = predMode;
				local_INTRA_PLANAR = INTRA_PLANAR;
				if (local_predMode == local_INTRA_PLANAR) {
					HevcDecoder_IntraPrediction_intraPlanarPred(chrComp_u, pNeighb_above, pNeighb_left, stride, treeLog2NS);
				} else {
					local_predMode = predMode;
					local_INTRA_DC = INTRA_DC;
					if (local_predMode == local_INTRA_DC) {
						intraDcPred(cIdx, treeNS, treeLog2NS);
					} else {
						local_predMode = predMode;
						HevcDecoder_IntraPrediction_intraAngularPred(chrComp_u, pNeighb_above, pNeighb_left, stride, cIdx, local_predMode, treeLog2NS);
					}
				}
			} else {
				local_predMode = predMode;
				local_INTRA_PLANAR = INTRA_PLANAR;
				if (local_predMode == local_INTRA_PLANAR) {
					HevcDecoder_IntraPrediction_intraPlanarPred(chrComp_v, pNeighb_above, pNeighb_left, stride, treeLog2NS);
				} else {
					local_predMode = predMode;
					local_INTRA_DC = INTRA_DC;
					if (local_predMode == local_INTRA_DC) {
						intraDcPred(cIdx, treeNS, treeLog2NS);
					} else {
						local_predMode = predMode;
						HevcDecoder_IntraPrediction_intraAngularPred(chrComp_v, pNeighb_above, pNeighb_left, stride, cIdx, local_predMode, treeLog2NS);
					}
				}
			}
		}
		cIdx = cIdx + 1;
	}
	if (cIdxMax == 1) {
		i1 = 0;
		while (i1 <= 1) {
			tmp_treeAddr4 = treeAddr[i1];
			off[i1] = tmp_treeAddr4 >> 1 & 2;
			i1 = i1 + 1;
		}
		tmp_off = off[0];
		tmp_off0 = off[1];
		if (tmp_off != 0 || tmp_off0 != 0) {
			comp = 0;
			while (comp <= 1) {
				y = 0;
				while (y <= 1) {
					x = 0;
					while (x <= 1) {
						tmp_off1 = off[0];
						tmp_off2 = off[1];
						tmp_chrComp_u = chrComp_u[x + tmp_off1 + 32 * (y + tmp_off2)];
						chrComp_u[x + y * 32] = tmp_chrComp_u;
						tmp_off3 = off[0];
						tmp_off4 = off[1];
						tmp_chrComp_v = chrComp_v[x + tmp_off3 + 32 * (y + tmp_off4)];
						chrComp_v[x + y * 32] = tmp_chrComp_v;
						x = x + 1;
					}
					y = y + 1;
				}
				comp = comp + 1;
			}
		}
	}
	local_trafoTreeDepth = trafoTreeDepth;
	local_trafoTreeDepth = trafoTreeDepth;
	tmp_trafoTreeIdx1 = trafoTreeIdx[local_trafoTreeDepth];
	trafoTreeIdx[local_trafoTreeDepth] = tmp_trafoTreeIdx1 + 1;
	local_trafoTreeDepth = trafoTreeDepth;
	if (local_trafoTreeDepth >= 0) {
		local_trafoTreeDepth = trafoTreeDepth;
		tmp_trafoTreeIdx2 = trafoTreeIdx[local_trafoTreeDepth];
		tmp_if = tmp_trafoTreeIdx2 == 4;
	} else {
		tmp_if = 0;
	}
	while (tmp_if) {
		local_trafoTreeDepth = trafoTreeDepth;
		trafoTreeDepth = local_trafoTreeDepth - 1;
		local_trafoTreeDepth = trafoTreeDepth;
		if (local_trafoTreeDepth > -1) {
			local_trafoTreeDepth = trafoTreeDepth;
			local_trafoTreeDepth = trafoTreeDepth;
			tmp_trafoTreeIdx3 = trafoTreeIdx[local_trafoTreeDepth];
			trafoTreeIdx[local_trafoTreeDepth] = tmp_trafoTreeIdx3 + 1;
		}
		local_trafoTreeDepth = trafoTreeDepth;
		if (local_trafoTreeDepth >= 0) {
			local_trafoTreeDepth = trafoTreeDepth;
			tmp_trafoTreeIdx2 = trafoTreeIdx[local_trafoTreeDepth];
			tmp_if = tmp_trafoTreeIdx2 == 4;
		} else {
			tmp_if = 0;
		}
	}

	// Update ports indexes
	index_SplitTransform += 1;

	rate_SplitTransform += 1;
}
static i32 isSchedulable_getSplitTrafo_isInter() {
	i32 result;
	i8 local_trafoTreeDepth;

	local_trafoTreeDepth = trafoTreeDepth;
	result = local_trafoTreeDepth > -1;
	return result;
}

static void getSplitTrafo_isInter() {

	i32 splitTrafo;
	i8 local_trafoTreeDepth;
	u8 tmp_trafoTreeIdx;
	i32 tmp_if;
	u8 tmp_trafoTreeIdx0;
	u8 tmp_trafoTreeIdx1;

	splitTrafo = tokens_SplitTransform[(index_SplitTransform + (0)) % SIZE_SplitTransform];
	if (splitTrafo) {
		local_trafoTreeDepth = trafoTreeDepth;
		trafoTreeDepth = local_trafoTreeDepth + 1;
		local_trafoTreeDepth = trafoTreeDepth;
		trafoTreeIdx[local_trafoTreeDepth] = 0;
	} else {
		local_trafoTreeDepth = trafoTreeDepth;
		local_trafoTreeDepth = trafoTreeDepth;
		tmp_trafoTreeIdx = trafoTreeIdx[local_trafoTreeDepth];
		trafoTreeIdx[local_trafoTreeDepth] = tmp_trafoTreeIdx + 1;
		local_trafoTreeDepth = trafoTreeDepth;
		local_trafoTreeDepth = trafoTreeDepth;
		if (local_trafoTreeDepth >= 0) {
			local_trafoTreeDepth = trafoTreeDepth;
			tmp_trafoTreeIdx0 = trafoTreeIdx[local_trafoTreeDepth];
			tmp_if = tmp_trafoTreeIdx0 == 4;
		} else {
			tmp_if = 0;
		}
		while (local_trafoTreeDepth > -1 && tmp_if) {
			local_trafoTreeDepth = trafoTreeDepth;
			trafoTreeDepth = local_trafoTreeDepth - 1;
			local_trafoTreeDepth = trafoTreeDepth;
			if (local_trafoTreeDepth > -1) {
				local_trafoTreeDepth = trafoTreeDepth;
				local_trafoTreeDepth = trafoTreeDepth;
				tmp_trafoTreeIdx1 = trafoTreeIdx[local_trafoTreeDepth];
				trafoTreeIdx[local_trafoTreeDepth] = tmp_trafoTreeIdx1 + 1;
			}
			local_trafoTreeDepth = trafoTreeDepth;
			local_trafoTreeDepth = trafoTreeDepth;
			if (local_trafoTreeDepth >= 0) {
				local_trafoTreeDepth = trafoTreeDepth;
				tmp_trafoTreeIdx0 = trafoTreeIdx[local_trafoTreeDepth];
				tmp_if = tmp_trafoTreeIdx0 == 4;
			} else {
				tmp_if = 0;
			}
		}
	}

	// Update ports indexes
	index_SplitTransform += 1;

	rate_SplitTransform += 1;
}
static i32 isSchedulable_getSplitTrafo_done() {
	i32 result;
	i8 local_trafoTreeDepth;

	local_trafoTreeDepth = trafoTreeDepth;
	result = local_trafoTreeDepth == -1;
	return result;
}

static void getSplitTrafo_done() {



	// Update ports indexes

}
static i32 isSchedulable_sendSamples_launch() {
	i32 result;
	u16 local_idxBlk;
	u16 local_numBlkToSend;

	local_idxBlk = idxBlk;
	local_numBlkToSend = numBlkToSend;
	result = local_idxBlk < local_numBlkToSend;
	return result;
}

static void sendSamples_launch() {

	u8 idxSample;
	u16 blkAddr[2];
	u16 local_idxBlk;
	u32 y;
	u16 tmp_blkAddr;
	u32 x;
	u16 tmp_blkAddr0;
	u8 tmp_lumaComp;
	u16 tmp_blkAddr1;
	u16 tmp_blkAddr2;
	u32 y0;
	u16 tmp_blkAddr3;
	u32 x0;
	u16 tmp_blkAddr4;
	u8 tmp_chrComp_u;
	u32 y1;
	u16 tmp_blkAddr5;
	u32 x1;
	u16 tmp_blkAddr6;
	u8 tmp_chrComp_v;

	idxSample = 0;
	local_idxBlk = idxBlk;
	HevcDecoder_IntraPrediction_zScanToAbsCoord(local_idxBlk, blkAddr);
	y = blkAddr[1];
	tmp_blkAddr = blkAddr[1];
	while (y <= tmp_blkAddr + 3) {
		x = blkAddr[0];
		tmp_blkAddr0 = blkAddr[0];
		while (x <= tmp_blkAddr0 + 3) {
			tmp_lumaComp = lumaComp[x + y * 64];
			tokens_PredSample[(index_PredSample + (idxSample)) % SIZE_PredSample] = tmp_lumaComp;
			idxSample = idxSample + 1;
			x = x + 1;
		}
		y = y + 1;
	}
	tmp_blkAddr1 = blkAddr[0];
	blkAddr[0] = tmp_blkAddr1 >> 1;
	tmp_blkAddr2 = blkAddr[1];
	blkAddr[1] = tmp_blkAddr2 >> 1;
	y0 = blkAddr[1];
	tmp_blkAddr3 = blkAddr[1];
	while (y0 <= tmp_blkAddr3 + 1) {
		x0 = blkAddr[0];
		tmp_blkAddr4 = blkAddr[0];
		while (x0 <= tmp_blkAddr4 + 1) {
			tmp_chrComp_u = chrComp_u[x0 + 32 * y0];
			tokens_PredSample[(index_PredSample + (idxSample)) % SIZE_PredSample] = tmp_chrComp_u;
			idxSample = idxSample + 1;
			x0 = x0 + 1;
		}
		y0 = y0 + 1;
	}
	y1 = blkAddr[1];
	tmp_blkAddr5 = blkAddr[1];
	while (y1 <= tmp_blkAddr5 + 1) {
		x1 = blkAddr[0];
		tmp_blkAddr6 = blkAddr[0];
		while (x1 <= tmp_blkAddr6 + 1) {
			tmp_chrComp_v = chrComp_v[x1 + 32 * y1];
			tokens_PredSample[(index_PredSample + (idxSample)) % SIZE_PredSample] = tmp_chrComp_v;
			idxSample = idxSample + 1;
			x1 = x1 + 1;
		}
		y1 = y1 + 1;
	}
	local_idxBlk = idxBlk;
	idxBlk = local_idxBlk + 1;

	// Update ports indexes
	index_PredSample += 24;
	write_end_PredSample();

}
static void sendSamples_launch_aligned() {

	u8 idxSample;
	u16 blkAddr[2];
	u16 local_idxBlk;
	u32 y;
	u16 tmp_blkAddr;
	u32 x;
	u16 tmp_blkAddr0;
	u8 tmp_lumaComp;
	u16 tmp_blkAddr1;
	u16 tmp_blkAddr2;
	u32 y0;
	u16 tmp_blkAddr3;
	u32 x0;
	u16 tmp_blkAddr4;
	u8 tmp_chrComp_u;
	u32 y1;
	u16 tmp_blkAddr5;
	u32 x1;
	u16 tmp_blkAddr6;
	u8 tmp_chrComp_v;

	idxSample = 0;
	local_idxBlk = idxBlk;
	HevcDecoder_IntraPrediction_zScanToAbsCoord(local_idxBlk, blkAddr);
	y = blkAddr[1];
	tmp_blkAddr = blkAddr[1];
	while (y <= tmp_blkAddr + 3) {
		x = blkAddr[0];
		tmp_blkAddr0 = blkAddr[0];
		while (x <= tmp_blkAddr0 + 3) {
			tmp_lumaComp = lumaComp[x + y * 64];
			tokens_PredSample[(index_PredSample % SIZE_PredSample) + (idxSample)] = tmp_lumaComp;
			idxSample = idxSample + 1;
			x = x + 1;
		}
		y = y + 1;
	}
	tmp_blkAddr1 = blkAddr[0];
	blkAddr[0] = tmp_blkAddr1 >> 1;
	tmp_blkAddr2 = blkAddr[1];
	blkAddr[1] = tmp_blkAddr2 >> 1;
	y0 = blkAddr[1];
	tmp_blkAddr3 = blkAddr[1];
	while (y0 <= tmp_blkAddr3 + 1) {
		x0 = blkAddr[0];
		tmp_blkAddr4 = blkAddr[0];
		while (x0 <= tmp_blkAddr4 + 1) {
			tmp_chrComp_u = chrComp_u[x0 + 32 * y0];
			tokens_PredSample[(index_PredSample % SIZE_PredSample) + (idxSample)] = tmp_chrComp_u;
			idxSample = idxSample + 1;
			x0 = x0 + 1;
		}
		y0 = y0 + 1;
	}
	y1 = blkAddr[1];
	tmp_blkAddr5 = blkAddr[1];
	while (y1 <= tmp_blkAddr5 + 1) {
		x1 = blkAddr[0];
		tmp_blkAddr6 = blkAddr[0];
		while (x1 <= tmp_blkAddr6 + 1) {
			tmp_chrComp_v = chrComp_v[x1 + 32 * y1];
			tokens_PredSample[(index_PredSample % SIZE_PredSample) + (idxSample)] = tmp_chrComp_v;
			idxSample = idxSample + 1;
			x1 = x1 + 1;
		}
		y1 = y1 + 1;
	}
	local_idxBlk = idxBlk;
	idxBlk = local_idxBlk + 1;

	// Update ports indexes
	index_PredSample += 24;
	write_end_PredSample();

}
static i32 isSchedulable_sendSamples_done() {
	i32 result;
	u16 local_idxBlk;
	u16 local_numBlkToSend;

	local_idxBlk = idxBlk;
	local_numBlkToSend = numBlkToSend;
	result = local_idxBlk == local_numBlkToSend;
	return result;
}

static void sendSamples_done() {


	idxBlk = 0;

	// Update ports indexes

}
static i32 isSchedulable_getSamples_launch() {
	i32 result;
	u16 local_idxBlk;
	u16 local_numBlkToSend;
	i32 local_EnabSkipInPix;
	i32 local_getInSamp;

	local_idxBlk = idxBlk;
	local_numBlkToSend = numBlkToSend;
	local_EnabSkipInPix = EnabSkipInPix;
	local_getInSamp = getInSamp;
	result = local_idxBlk < local_numBlkToSend && (!local_EnabSkipInPix || local_getInSamp);
	return result;
}

static void getSamples_launch() {

	u16 blkAddr[2];
	i32 bottomBlk;
	i32 leftBlk;
	u8 sampOff;
	u16 tabIdx;
	u16 local_idxBlk;
	u16 tmp_blkAddr;
	u8 local_neighbBlkSz;
	u16 tmp_blkAddr0;
	u16 tmp_blkAddr1;
	u16 tmp_treeAddr;
	u16 tmp_blkAddr2;
	u16 tmp_treeAddr0;
	u32 x;
	u16 tmp_pictSize;
	u16 tmp_blkAddr3;
	u16 tmp_blkAddr4;
	u8 tmp_Sample;
	u8 local_cuMode;
	u8 local_INTRA;
	u32 y;
	u16 tmp_pictSize0;
	u16 tmp_blkAddr5;
	u16 tmp_blkAddr6;
	u8 tmp_Sample0;
	u16 tmp_blkAddr7;
	u16 tmp_blkAddr8;
	u32 comp;
	u32 x0;
	u16 tmp_pictSize1;
	u16 tmp_blkAddr9;
	u16 tmp_blkAddr10;
	u8 tmp_Sample1;
	u32 y0;
	u16 tmp_pictSize2;
	u16 tmp_blkAddr11;
	u16 tmp_blkAddr12;
	u8 tmp_Sample2;

	bottomBlk = 0;
	leftBlk = 0;
	sampOff = 16;
	local_idxBlk = idxBlk;
	HevcDecoder_IntraPrediction_zScanToAbsCoord(local_idxBlk, blkAddr);
	tmp_blkAddr = blkAddr[0];
	local_neighbBlkSz = neighbBlkSz;
	if (tmp_blkAddr + 4 >= local_neighbBlkSz) {
		leftBlk = 1;
	}
	tmp_blkAddr0 = blkAddr[1];
	local_neighbBlkSz = neighbBlkSz;
	if (tmp_blkAddr0 + 4 >= local_neighbBlkSz) {
		bottomBlk = 1;
	}
	tmp_blkAddr1 = blkAddr[0];
	tmp_treeAddr = treeAddr[0];
	blkAddr[0] = tmp_blkAddr1 + tmp_treeAddr;
	tmp_blkAddr2 = blkAddr[1];
	tmp_treeAddr0 = treeAddr[1];
	blkAddr[1] = tmp_blkAddr2 + tmp_treeAddr0;
	if (bottomBlk) {
		x = 0;
		while (x <= 3) {
			tmp_pictSize = pictSize[0][1];
			tmp_blkAddr3 = blkAddr[1];
			tmp_blkAddr4 = blkAddr[0];
			tabIdx = tmp_pictSize - (tmp_blkAddr3 + 3) + tmp_blkAddr4 + x;
			tmp_Sample = tokens_Sample[(index_Sample + (4 * 3 + x)) % SIZE_Sample];
			puNeighb[0][tabIdx] = tmp_Sample;
			local_cuMode = cuMode;
			local_INTRA = HevcDecoder_IntraPrediction_INTRA;
			puIsIntra[0][tabIdx] = local_cuMode == local_INTRA;
			x = x + 1;
		}
	}
	if (leftBlk) {
		y = 0;
		while (y <= 3) {
			tmp_pictSize0 = pictSize[0][1];
			tmp_blkAddr5 = blkAddr[1];
			tmp_blkAddr6 = blkAddr[0];
			tabIdx = tmp_pictSize0 - (tmp_blkAddr5 + y) + tmp_blkAddr6 + 3;
			tmp_Sample0 = tokens_Sample[(index_Sample + (4 * y + 3)) % SIZE_Sample];
			puNeighb[0][tabIdx] = tmp_Sample0;
			local_cuMode = cuMode;
			local_INTRA = HevcDecoder_IntraPrediction_INTRA;
			puIsIntra[0][tabIdx] = local_cuMode == local_INTRA;
			y = y + 1;
		}
	}
	tmp_blkAddr7 = blkAddr[0];
	blkAddr[0] = tmp_blkAddr7 >> 1;
	tmp_blkAddr8 = blkAddr[1];
	blkAddr[1] = tmp_blkAddr8 >> 1;
	comp = 1;
	while (comp <= 2) {
		if (bottomBlk) {
			x0 = 0;
			while (x0 <= 1) {
				tmp_pictSize1 = pictSize[1][1];
				tmp_blkAddr9 = blkAddr[1];
				tmp_blkAddr10 = blkAddr[0];
				tabIdx = tmp_pictSize1 - (tmp_blkAddr9 + 1) + tmp_blkAddr10 + x0;
				tmp_Sample1 = tokens_Sample[(index_Sample + (2 * 1 + x0 + sampOff)) % SIZE_Sample];
				puNeighb[comp][tabIdx] = tmp_Sample1;
				local_cuMode = cuMode;
				local_INTRA = HevcDecoder_IntraPrediction_INTRA;
				puIsIntra[comp][tabIdx] = local_cuMode == local_INTRA;
				x0 = x0 + 1;
			}
		}
		if (leftBlk) {
			y0 = 0;
			while (y0 <= 1) {
				tmp_pictSize2 = pictSize[1][1];
				tmp_blkAddr11 = blkAddr[1];
				tmp_blkAddr12 = blkAddr[0];
				tabIdx = tmp_pictSize2 - (tmp_blkAddr11 + y0) + tmp_blkAddr12 + 1;
				tmp_Sample2 = tokens_Sample[(index_Sample + (2 * y0 + 1 + sampOff)) % SIZE_Sample];
				puNeighb[comp][tabIdx] = tmp_Sample2;
				local_cuMode = cuMode;
				local_INTRA = HevcDecoder_IntraPrediction_INTRA;
				puIsIntra[comp][tabIdx] = local_cuMode == local_INTRA;
				y0 = y0 + 1;
			}
		}
		sampOff = sampOff + 4;
		comp = comp + 1;
	}
	local_idxBlk = idxBlk;
	idxBlk = local_idxBlk + 1;

	// Update ports indexes
	index_Sample += 24;
	read_end_Sample();

	rate_Sample += 24;
}
static void getSamples_launch_aligned() {

	u16 blkAddr[2];
	i32 bottomBlk;
	i32 leftBlk;
	u8 sampOff;
	u16 tabIdx;
	u16 local_idxBlk;
	u16 tmp_blkAddr;
	u8 local_neighbBlkSz;
	u16 tmp_blkAddr0;
	u16 tmp_blkAddr1;
	u16 tmp_treeAddr;
	u16 tmp_blkAddr2;
	u16 tmp_treeAddr0;
	u32 x;
	u16 tmp_pictSize;
	u16 tmp_blkAddr3;
	u16 tmp_blkAddr4;
	u8 tmp_Sample;
	u8 local_cuMode;
	u8 local_INTRA;
	u32 y;
	u16 tmp_pictSize0;
	u16 tmp_blkAddr5;
	u16 tmp_blkAddr6;
	u8 tmp_Sample0;
	u16 tmp_blkAddr7;
	u16 tmp_blkAddr8;
	u32 comp;
	u32 x0;
	u16 tmp_pictSize1;
	u16 tmp_blkAddr9;
	u16 tmp_blkAddr10;
	u8 tmp_Sample1;
	u32 y0;
	u16 tmp_pictSize2;
	u16 tmp_blkAddr11;
	u16 tmp_blkAddr12;
	u8 tmp_Sample2;

	bottomBlk = 0;
	leftBlk = 0;
	sampOff = 16;
	local_idxBlk = idxBlk;
	HevcDecoder_IntraPrediction_zScanToAbsCoord(local_idxBlk, blkAddr);
	tmp_blkAddr = blkAddr[0];
	local_neighbBlkSz = neighbBlkSz;
	if (tmp_blkAddr + 4 >= local_neighbBlkSz) {
		leftBlk = 1;
	}
	tmp_blkAddr0 = blkAddr[1];
	local_neighbBlkSz = neighbBlkSz;
	if (tmp_blkAddr0 + 4 >= local_neighbBlkSz) {
		bottomBlk = 1;
	}
	tmp_blkAddr1 = blkAddr[0];
	tmp_treeAddr = treeAddr[0];
	blkAddr[0] = tmp_blkAddr1 + tmp_treeAddr;
	tmp_blkAddr2 = blkAddr[1];
	tmp_treeAddr0 = treeAddr[1];
	blkAddr[1] = tmp_blkAddr2 + tmp_treeAddr0;
	if (bottomBlk) {
		x = 0;
		while (x <= 3) {
			tmp_pictSize = pictSize[0][1];
			tmp_blkAddr3 = blkAddr[1];
			tmp_blkAddr4 = blkAddr[0];
			tabIdx = tmp_pictSize - (tmp_blkAddr3 + 3) + tmp_blkAddr4 + x;
			tmp_Sample = tokens_Sample[(index_Sample % SIZE_Sample) + (4 * 3 + x)];
			puNeighb[0][tabIdx] = tmp_Sample;
			local_cuMode = cuMode;
			local_INTRA = HevcDecoder_IntraPrediction_INTRA;
			puIsIntra[0][tabIdx] = local_cuMode == local_INTRA;
			x = x + 1;
		}
	}
	if (leftBlk) {
		y = 0;
		while (y <= 3) {
			tmp_pictSize0 = pictSize[0][1];
			tmp_blkAddr5 = blkAddr[1];
			tmp_blkAddr6 = blkAddr[0];
			tabIdx = tmp_pictSize0 - (tmp_blkAddr5 + y) + tmp_blkAddr6 + 3;
			tmp_Sample0 = tokens_Sample[(index_Sample % SIZE_Sample) + (4 * y + 3)];
			puNeighb[0][tabIdx] = tmp_Sample0;
			local_cuMode = cuMode;
			local_INTRA = HevcDecoder_IntraPrediction_INTRA;
			puIsIntra[0][tabIdx] = local_cuMode == local_INTRA;
			y = y + 1;
		}
	}
	tmp_blkAddr7 = blkAddr[0];
	blkAddr[0] = tmp_blkAddr7 >> 1;
	tmp_blkAddr8 = blkAddr[1];
	blkAddr[1] = tmp_blkAddr8 >> 1;
	comp = 1;
	while (comp <= 2) {
		if (bottomBlk) {
			x0 = 0;
			while (x0 <= 1) {
				tmp_pictSize1 = pictSize[1][1];
				tmp_blkAddr9 = blkAddr[1];
				tmp_blkAddr10 = blkAddr[0];
				tabIdx = tmp_pictSize1 - (tmp_blkAddr9 + 1) + tmp_blkAddr10 + x0;
				tmp_Sample1 = tokens_Sample[(index_Sample % SIZE_Sample) + (2 * 1 + x0 + sampOff)];
				puNeighb[comp][tabIdx] = tmp_Sample1;
				local_cuMode = cuMode;
				local_INTRA = HevcDecoder_IntraPrediction_INTRA;
				puIsIntra[comp][tabIdx] = local_cuMode == local_INTRA;
				x0 = x0 + 1;
			}
		}
		if (leftBlk) {
			y0 = 0;
			while (y0 <= 1) {
				tmp_pictSize2 = pictSize[1][1];
				tmp_blkAddr11 = blkAddr[1];
				tmp_blkAddr12 = blkAddr[0];
				tabIdx = tmp_pictSize2 - (tmp_blkAddr11 + y0) + tmp_blkAddr12 + 1;
				tmp_Sample2 = tokens_Sample[(index_Sample % SIZE_Sample) + (2 * y0 + 1 + sampOff)];
				puNeighb[comp][tabIdx] = tmp_Sample2;
				local_cuMode = cuMode;
				local_INTRA = HevcDecoder_IntraPrediction_INTRA;
				puIsIntra[comp][tabIdx] = local_cuMode == local_INTRA;
				y0 = y0 + 1;
			}
		}
		sampOff = sampOff + 4;
		comp = comp + 1;
	}
	local_idxBlk = idxBlk;
	idxBlk = local_idxBlk + 1;

	// Update ports indexes
	index_Sample += 24;
	read_end_Sample();

	rate_Sample += 24;
}
static i32 isSchedulable_getSamples_done() {
	i32 result;
	u16 local_idxBlk;
	u16 local_numBlkToSend;
	i32 local_EnabSkipInPix;
	i32 local_getInSamp;

	local_idxBlk = idxBlk;
	local_numBlkToSend = numBlkToSend;
	local_EnabSkipInPix = EnabSkipInPix;
	local_getInSamp = getInSamp;
	result = local_idxBlk == local_numBlkToSend || local_EnabSkipInPix && !local_getInSamp;
	return result;
}

static void getSamples_done() {



	// Update ports indexes

}

////////////////////////////////////////////////////////////////////////////////
// Initializes

void HevcDecoder_IntraPrediction_initialize(schedinfo_t *si) {
	int i = 0;
	write_PredSample();
	/* Set initial state to current FSM state */
	_FSM_state = my_state_GetPartMode;
finished:
	write_end_PredSample();
	return;
}

////////////////////////////////////////////////////////////////////////////////
// Action scheduler

void HevcDecoder_IntraPrediction_scheduler(schedinfo_t *si) {
	int i = 0;

	read_CUInfo();
	read_IntraPredMode();
	read_LcuSizeMax();
	read_PartMode();
	read_PictSize();
	read_Sample();
	read_SliceAddr();
	read_SplitTransform();
	read_StrongIntraSmoothing();
	read_TilesCoord();
	write_PredSample();

	// jump to FSM state
	switch (_FSM_state) {
	case my_state_GetCuInfo:
		goto l_GetCuInfo;
	case my_state_GetCuInfoNonQT:
		goto l_GetCuInfoNonQT;
	case my_state_GetCuMode:
		goto l_GetCuMode;
	case my_state_GetInSamples:
		goto l_GetInSamples;
	case my_state_GetInterSamples:
		goto l_GetInterSamples;
	case my_state_GetIntraSamples:
		goto l_GetIntraSamples;
	case my_state_GetPartMode:
		goto l_GetPartMode;
	case my_state_GetSplitTrafoInter:
		goto l_GetSplitTrafoInter;
	case my_state_GetSplitTrafoIntra:
		goto l_GetSplitTrafoIntra;
	case my_state_GetTilesCoord:
		goto l_GetTilesCoord;
	case my_state_SendSamples:
		goto l_SendSamples;
	default:
		printf("unknown state in HevcDecoder_IntraPrediction.c : %s\n", stateNames[_FSM_state]);
		exit(1);
	}

	// FSM transitions
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
	} else if (numTokens_CUInfo - index_CUInfo >= 5 && isSchedulable_getCuInfo_getInSamp()) {
		{
			int isAligned = 1;
			isAligned &= ((index_CUInfo % SIZE_CUInfo) < ((index_CUInfo + 5) % SIZE_CUInfo));
			if (isAligned) {
				getCuInfo_getInSamp_aligned();
			} else {
				getCuInfo_getInSamp();
			}
		}
		i++;
		goto l_GetInSamples;
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
l_GetCuInfoNonQT:
	if (numTokens_CUInfo - index_CUInfo >= 10 && isSchedulable_getCuInfo_nonQT_isInter()) {
		{
			int isAligned = 1;
			isAligned &= ((index_CUInfo % SIZE_CUInfo) < ((index_CUInfo + 10) % SIZE_CUInfo));
			if (isAligned) {
				getCuInfo_nonQT_isInter_aligned();
			} else {
				getCuInfo_nonQT_isInter();
			}
		}
		i++;
		goto l_GetSplitTrafoInter;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetCuInfoNonQT;
		goto finished;
	}
l_GetCuMode:
	if (numTokens_IntraPredMode - index_IntraPredMode >= 2 && isSchedulable_getCuMode_isIntra()) {
		getCuMode_isIntra_aligned();
		i++;
		goto l_GetSplitTrafoIntra;
	} else if (isSchedulable_getCuMode_isInter()) {
		getCuMode_isInter();
		i++;
		goto l_GetSplitTrafoInter;
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
l_GetInSamples:
	if (numTokens_Sample - index_Sample >= 24 && isSchedulable_getSamples_launch()) {
		{
			int isAligned = 1;
			isAligned &= ((index_Sample % SIZE_Sample) < ((index_Sample + 24) % SIZE_Sample));
			if (isAligned) {
				getSamples_launch_aligned();
			} else {
				getSamples_launch();
			}
		}
		i++;
		goto l_GetInSamples;
	} else if (isSchedulable_getSamples_done()) {
		getSamples_done();
		i++;
		goto l_GetCuInfo;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetInSamples;
		goto finished;
	}
l_GetInterSamples:
	if (numTokens_Sample - index_Sample >= 24 && isSchedulable_getSamples_launch()) {
		{
			int isAligned = 1;
			isAligned &= ((index_Sample % SIZE_Sample) < ((index_Sample + 24) % SIZE_Sample));
			if (isAligned) {
				getSamples_launch_aligned();
			} else {
				getSamples_launch();
			}
		}
		i++;
		goto l_GetInterSamples;
	} else if (isSchedulable_getSamples_done()) {
		getSamples_done();
		i++;
		goto l_GetCuInfo;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetInterSamples;
		goto finished;
	}
l_GetIntraSamples:
	if (numTokens_Sample - index_Sample >= 24 && isSchedulable_getSamples_launch()) {
		{
			int isAligned = 1;
			isAligned &= ((index_Sample % SIZE_Sample) < ((index_Sample + 24) % SIZE_Sample));
			if (isAligned) {
				getSamples_launch_aligned();
			} else {
				getSamples_launch();
			}
		}
		i++;
		goto l_GetIntraSamples;
	} else if (isSchedulable_getSamples_done()) {
		getSamples_done();
		i++;
		goto l_GetSplitTrafoIntra;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetIntraSamples;
		goto finished;
	}
l_GetPartMode:
	if (numTokens_PartMode - index_PartMode >= 1 && numTokens_LcuSizeMax - index_LcuSizeMax >= 1 && numTokens_PictSize - index_PictSize >= 2 && numTokens_SliceAddr - index_SliceAddr >= 2 && numTokens_StrongIntraSmoothing - index_StrongIntraSmoothing >= 2 && numTokens_TilesCoord - index_TilesCoord >= 1 && isSchedulable_isNewSliceOrPict_notDep()) {
		{
			int isAligned = 1;
			isAligned &= ((index_SliceAddr % SIZE_SliceAddr) < ((index_SliceAddr + 2) % SIZE_SliceAddr));
			isAligned &= ((index_StrongIntraSmoothing % SIZE_StrongIntraSmoothing) < ((index_StrongIntraSmoothing + 2) % SIZE_StrongIntraSmoothing));
			if (isAligned) {
				isNewSliceOrPict_notDep_aligned();
			} else {
				isNewSliceOrPict_notDep();
			}
		}
		i++;
		goto l_GetTilesCoord;
	} else if (numTokens_PartMode - index_PartMode >= 1 && numTokens_SliceAddr - index_SliceAddr >= 2 && numTokens_StrongIntraSmoothing - index_StrongIntraSmoothing >= 2 && isSchedulable_isNewSliceOrPict_dep()) {
		{
			int isAligned = 1;
			isAligned &= ((index_SliceAddr % SIZE_SliceAddr) < ((index_SliceAddr + 2) % SIZE_SliceAddr));
			isAligned &= ((index_StrongIntraSmoothing % SIZE_StrongIntraSmoothing) < ((index_StrongIntraSmoothing + 2) % SIZE_StrongIntraSmoothing));
			if (isAligned) {
				isNewSliceOrPict_dep_aligned();
			} else {
				isNewSliceOrPict_dep();
			}
		}
		i++;
		goto l_GetPartMode;
	} else if (numTokens_PartMode - index_PartMode >= 1 && isSchedulable_getPartMode_isNonQuadTree()) {
		getPartMode_isNonQuadTree();
		i++;
		goto l_GetCuInfoNonQT;
	} else if (numTokens_PartMode - index_PartMode >= 1 && isSchedulable_getPartMode_isQuadTree()) {
		getPartMode_isQuadTree();
		i++;
		goto l_GetCuInfo;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetPartMode;
		goto finished;
	}
l_GetSplitTrafoInter:
	if (numTokens_SplitTransform - index_SplitTransform >= 1 && isSchedulable_getSplitTrafo_isInter()) {
		getSplitTrafo_isInter();
		i++;
		goto l_GetSplitTrafoInter;
	} else if (isSchedulable_getSplitTrafo_done()) {
		getSplitTrafo_done();
		i++;
		goto l_GetInterSamples;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetSplitTrafoInter;
		goto finished;
	}
l_GetSplitTrafoIntra:
	if (numTokens_SplitTransform - index_SplitTransform >= 1 && isSchedulable_getSplitTrafo_isTrue()) {
		getSplitTrafo_isTrue();
		i++;
		goto l_GetSplitTrafoIntra;
	} else if (numTokens_SplitTransform - index_SplitTransform >= 1 && isSchedulable_getSplitTrafo_isFalse()) {
		getSplitTrafo_isFalse();
		i++;
		goto l_SendSamples;
	} else if (isSchedulable_getSplitTrafo_done()) {
		getSplitTrafo_done();
		i++;
		goto l_GetCuInfo;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetSplitTrafoIntra;
		goto finished;
	}
l_GetTilesCoord:
	if (numTokens_TilesCoord - index_TilesCoord >= 4 && isSchedulable_getTilesCoord_launch()) {
		{
			int isAligned = 1;
			isAligned &= ((index_TilesCoord % SIZE_TilesCoord) < ((index_TilesCoord + 4) % SIZE_TilesCoord));
			if (isAligned) {
				getTilesCoord_launch_aligned();
			} else {
				getTilesCoord_launch();
			}
		}
		i++;
		goto l_GetTilesCoord;
	} else if (isSchedulable_getTilesCoord_done()) {
		getTilesCoord_done();
		i++;
		goto l_GetPartMode;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetTilesCoord;
		goto finished;
	}
l_SendSamples:
	if (isSchedulable_sendSamples_launch()) {
		int stop = 0;
		if (24 > SIZE_PredSample - index_PredSample + HevcDecoder_IntraPrediction_PredSample->read_inds[0]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_SendSamples;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		{
			int isAligned = 1;
			isAligned &= ((index_PredSample % SIZE_PredSample) < ((index_PredSample + 24) % SIZE_PredSample));
			if (isAligned) {
				sendSamples_launch_aligned();
			} else {
				sendSamples_launch();
			}
		}
		i++;
		goto l_SendSamples;
	} else if (isSchedulable_sendSamples_done()) {
		sendSamples_done();
		i++;
		goto l_GetIntraSamples;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_SendSamples;
		goto finished;
	}
finished:
	read_end_CUInfo();
	read_end_IntraPredMode();
	read_end_LcuSizeMax();
	read_end_PartMode();
	read_end_PictSize();
	read_end_Sample();
	read_end_SliceAddr();
	read_end_SplitTransform();
	read_end_StrongIntraSmoothing();
	read_end_TilesCoord();
	write_end_PredSample();
}
