// Source file is "L/RVC/src/org/sc29/wg11/mpegh/part2/main/Filters/DeblockingFilter.cal"

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
extern actor_t HevcDecoder_DBFilter_DeblockFilt;

////////////////////////////////////////////////////////////////////////////////
// Input FIFOs
extern fifo_u8_t *HevcDecoder_DBFilter_DeblockFilt_BsHor;
extern fifo_u8_t *HevcDecoder_DBFilter_DeblockFilt_BsVer;
extern fifo_i32_t *HevcDecoder_DBFilter_DeblockFilt_DBFDisable;
extern fifo_u8_t *HevcDecoder_DBFilter_DeblockFilt_IsPicSlcLcu;
extern fifo_u8_t *HevcDecoder_DBFilter_DeblockFilt_LcuSizeMax;
extern fifo_u16_t *HevcDecoder_DBFilter_DeblockFilt_PicSize;
extern fifo_i8_t *HevcDecoder_DBFilter_DeblockFilt_Qp;
extern fifo_u8_t *HevcDecoder_DBFilter_DeblockFilt_SampleIn;
extern fifo_i8_t *HevcDecoder_DBFilter_DeblockFilt_SyntaxElem;
extern fifo_u16_t *HevcDecoder_DBFilter_DeblockFilt_TilesCoord;

////////////////////////////////////////////////////////////////////////////////
// Input Fifo control variables
static unsigned int index_BsHor;
static unsigned int numTokens_BsHor;
#define SIZE_BsHor SIZE
#define tokens_BsHor HevcDecoder_DBFilter_DeblockFilt_BsHor->contents

extern connection_t connection_HevcDecoder_DBFilter_DeblockFilt_BsHor;
#define rate_BsHor connection_HevcDecoder_DBFilter_DeblockFilt_BsHor.rate

static unsigned int index_BsVer;
static unsigned int numTokens_BsVer;
#define SIZE_BsVer SIZE
#define tokens_BsVer HevcDecoder_DBFilter_DeblockFilt_BsVer->contents

extern connection_t connection_HevcDecoder_DBFilter_DeblockFilt_BsVer;
#define rate_BsVer connection_HevcDecoder_DBFilter_DeblockFilt_BsVer.rate

static unsigned int index_DBFDisable;
static unsigned int numTokens_DBFDisable;
#define SIZE_DBFDisable SIZE
#define tokens_DBFDisable HevcDecoder_DBFilter_DeblockFilt_DBFDisable->contents

extern connection_t connection_HevcDecoder_DBFilter_DeblockFilt_DBFDisable;
#define rate_DBFDisable connection_HevcDecoder_DBFilter_DeblockFilt_DBFDisable.rate

static unsigned int index_IsPicSlcLcu;
static unsigned int numTokens_IsPicSlcLcu;
#define SIZE_IsPicSlcLcu SIZE
#define tokens_IsPicSlcLcu HevcDecoder_DBFilter_DeblockFilt_IsPicSlcLcu->contents

extern connection_t connection_HevcDecoder_DBFilter_DeblockFilt_IsPicSlcLcu;
#define rate_IsPicSlcLcu connection_HevcDecoder_DBFilter_DeblockFilt_IsPicSlcLcu.rate

static unsigned int index_LcuSizeMax;
static unsigned int numTokens_LcuSizeMax;
#define SIZE_LcuSizeMax SIZE
#define tokens_LcuSizeMax HevcDecoder_DBFilter_DeblockFilt_LcuSizeMax->contents

extern connection_t connection_HevcDecoder_DBFilter_DeblockFilt_LcuSizeMax;
#define rate_LcuSizeMax connection_HevcDecoder_DBFilter_DeblockFilt_LcuSizeMax.rate

static unsigned int index_PicSize;
static unsigned int numTokens_PicSize;
#define SIZE_PicSize SIZE
#define tokens_PicSize HevcDecoder_DBFilter_DeblockFilt_PicSize->contents

extern connection_t connection_HevcDecoder_DBFilter_DeblockFilt_PicSize;
#define rate_PicSize connection_HevcDecoder_DBFilter_DeblockFilt_PicSize.rate

static unsigned int index_Qp;
static unsigned int numTokens_Qp;
#define SIZE_Qp SIZE
#define tokens_Qp HevcDecoder_DBFilter_DeblockFilt_Qp->contents

extern connection_t connection_HevcDecoder_DBFilter_DeblockFilt_Qp;
#define rate_Qp connection_HevcDecoder_DBFilter_DeblockFilt_Qp.rate

static unsigned int index_SampleIn;
static unsigned int numTokens_SampleIn;
#define SIZE_SampleIn SIZE
#define tokens_SampleIn HevcDecoder_DBFilter_DeblockFilt_SampleIn->contents

extern connection_t connection_HevcDecoder_DBFilter_DeblockFilt_SampleIn;
#define rate_SampleIn connection_HevcDecoder_DBFilter_DeblockFilt_SampleIn.rate

static unsigned int index_SyntaxElem;
static unsigned int numTokens_SyntaxElem;
#define SIZE_SyntaxElem SIZE
#define tokens_SyntaxElem HevcDecoder_DBFilter_DeblockFilt_SyntaxElem->contents

extern connection_t connection_HevcDecoder_DBFilter_DeblockFilt_SyntaxElem;
#define rate_SyntaxElem connection_HevcDecoder_DBFilter_DeblockFilt_SyntaxElem.rate

static unsigned int index_TilesCoord;
static unsigned int numTokens_TilesCoord;
#define SIZE_TilesCoord SIZE
#define tokens_TilesCoord HevcDecoder_DBFilter_DeblockFilt_TilesCoord->contents

extern connection_t connection_HevcDecoder_DBFilter_DeblockFilt_TilesCoord;
#define rate_TilesCoord connection_HevcDecoder_DBFilter_DeblockFilt_TilesCoord.rate

////////////////////////////////////////////////////////////////////////////////
// Predecessors
extern actor_t HevcDecoder_DBFilter_GenerateBs;
extern actor_t HevcDecoder_DBFilter_GenerateBs;
extern actor_t HevcDecoder_Algo_Parser;
extern actor_t HevcDecoder_Algo_Parser;
extern actor_t HevcDecoder_Algo_Parser;
extern actor_t HevcDecoder_Algo_Parser;
extern actor_t HevcDecoder_Algo_Parser;
extern actor_t HevcDecoder_SelectCU;
extern actor_t HevcDecoder_Algo_Parser;
extern actor_t HevcDecoder_Algo_Parser;

////////////////////////////////////////////////////////////////////////////////
// Output FIFOs
extern fifo_u8_t *HevcDecoder_DBFilter_DeblockFilt_FiltSample;

////////////////////////////////////////////////////////////////////////////////
// Output Fifo control variables
static unsigned int index_FiltSample;
static unsigned int numFree_FiltSample;
#define NUM_READERS_FiltSample 1
#define SIZE_FiltSample SIZE
#define tokens_FiltSample HevcDecoder_DBFilter_DeblockFilt_FiltSample->contents

////////////////////////////////////////////////////////////////////////////////
// Successors
extern actor_t HevcDecoder_SAO;

////////////////////////////////////////////////////////////////////////////////
// Parameter values of the instance
#define FILT_VERT_EDGES 1
#define FILT_HOR_EDGES 1
#define DEBUG 0


////////////////////////////////////////////////////////////////////////////////
// State variables of the actor
#define HevcDecoder_DBFilter_DeblockFilt_PICT_WIDTH 4096
static const u8 HevcDecoder_DBFilter_DeblockFilt_ZscanToAbsCoord0[257] = {0, 4, 0, 4, 8, 12, 8, 12, 0, 4, 0, 4, 8, 12, 8, 12, 16, 20, 16, 20, 24, 28, 24, 28, 16, 20, 16, 20, 24, 28, 24, 28, 0, 4, 0, 4, 8, 12, 8, 12, 0, 4, 0, 4, 8, 12, 8, 12, 16, 20, 16, 20, 24, 28, 24, 28, 16, 20, 16, 20, 24, 28, 24, 28, 32, 36, 32, 36, 40, 44, 40, 44, 32, 36, 32, 36, 40, 44, 40, 44, 48, 52, 48, 52, 56, 60, 56, 60, 48, 52, 48, 52, 56, 60, 56, 60, 32, 36, 32, 36, 40, 44, 40, 44, 32, 36, 32, 36, 40, 44, 40, 44, 48, 52, 48, 52, 56, 60, 56, 60, 48, 52, 48, 52, 56, 60, 56, 60, 0, 4, 0, 4, 8, 12, 8, 12, 0, 4, 0, 4, 8, 12, 8, 12, 16, 20, 16, 20, 24, 28, 24, 28, 16, 20, 16, 20, 24, 28, 24, 28, 0, 4, 0, 4, 8, 12, 8, 12, 0, 4, 0, 4, 8, 12, 8, 12, 16, 20, 16, 20, 24, 28, 24, 28, 16, 20, 16, 20, 24, 28, 24, 28, 32, 36, 32, 36, 40, 44, 40, 44, 32, 36, 32, 36, 40, 44, 40, 44, 48, 52, 48, 52, 56, 60, 56, 60, 48, 52, 48, 52, 56, 60, 56, 60, 32, 36, 32, 36, 40, 44, 40, 44, 32, 36, 32, 36, 40, 44, 40, 44, 48, 52, 48, 52, 56, 60, 56, 60, 48, 52, 48, 52, 56, 60, 56, 60, 0};
static const u8 HevcDecoder_DBFilter_DeblockFilt_ZscanToAbsCoord1[257] = {0, 0, 4, 4, 0, 0, 4, 4, 8, 8, 12, 12, 8, 8, 12, 12, 0, 0, 4, 4, 0, 0, 4, 4, 8, 8, 12, 12, 8, 8, 12, 12, 16, 16, 20, 20, 16, 16, 20, 20, 24, 24, 28, 28, 24, 24, 28, 28, 16, 16, 20, 20, 16, 16, 20, 20, 24, 24, 28, 28, 24, 24, 28, 28, 0, 0, 4, 4, 0, 0, 4, 4, 8, 8, 12, 12, 8, 8, 12, 12, 0, 0, 4, 4, 0, 0, 4, 4, 8, 8, 12, 12, 8, 8, 12, 12, 16, 16, 20, 20, 16, 16, 20, 20, 24, 24, 28, 28, 24, 24, 28, 28, 16, 16, 20, 20, 16, 16, 20, 20, 24, 24, 28, 28, 24, 24, 28, 28, 32, 32, 36, 36, 32, 32, 36, 36, 40, 40, 44, 44, 40, 40, 44, 44, 32, 32, 36, 36, 32, 32, 36, 36, 40, 40, 44, 44, 40, 40, 44, 44, 48, 48, 52, 52, 48, 48, 52, 52, 56, 56, 60, 60, 56, 56, 60, 60, 48, 48, 52, 52, 48, 48, 52, 52, 56, 56, 60, 60, 56, 56, 60, 60, 32, 32, 36, 36, 32, 32, 36, 36, 40, 40, 44, 44, 40, 40, 44, 44, 32, 32, 36, 36, 32, 32, 36, 36, 40, 40, 44, 44, 40, 40, 44, 44, 48, 48, 52, 52, 48, 48, 52, 52, 56, 56, 60, 60, 56, 56, 60, 60, 48, 48, 52, 52, 48, 48, 52, 52, 56, 56, 60, 60, 56, 56, 60, 60, 0};
#define HevcDecoder_DBFilter_DeblockFilt_PICT_HEIGHT 2048
#define HevcDecoder_DBFilter_DeblockFilt_NEW_SLC 1
#define HevcDecoder_DBFilter_DeblockFilt_NEW_PIC 0
#define HevcDecoder_DBFilter_DeblockFilt_NEW_LCU 2
#define BIT_DEPTH 8
static const u8 betaTable[52] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48, 50, 52, 54, 56, 58, 60, 62, 64};
static const u8 tcTable[54] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 5, 5, 6, 6, 7, 8, 9, 10, 11, 13, 14, 16, 18, 20, 22, 24};
static const u8 qPcTable[52] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 29, 30, 31, 32, 33, 33, 34, 34, 35, 35, 36, 36, 37, 37, 38, 39, 40, 41, 42, 43, 44, 45};
static i16 iLoop;
static u16 numTiles;
static u16 tileIdx;
static u16 numPartition;
static u16 tilesBegSamp[128][2];
static u16 tilesEndSamp[128][2];
static i8 qpChrOff[2];
static u8 lcuSizeMax;
static u8 log2lcuSizeMax;
static u16 picSize[2];
static u16 xIdx;
static u16 yIdx;
static u8 compIdx;
static u16 xAddrVert;
static u16 yAddrVert;
static i16 xAddrHor;
static i16 yAddrHor;
static u16 numTokenPerLcu[2];
static u16 tokenSent;
static u16 pixAddr[2];
static u16 blkIdx = 0;
static i32 disDbf = 0;
static u8 pictureBuffer[3][2048][4096];
static i8 qpTab[1024][512];
static u8 bSTableVert[256];
static u8 bSTableHoriz[64][32][256];
static i32 betaOffset;
static u8 dE;
static i32 dEp;
static i32 dEq;
static i32 qPi;
static i32 tcOffset;
static u8 tc;
static u16 beta;

////////////////////////////////////////////////////////////////////////////////
// Initial FSM state of the actor
enum states {
	my_state_CheckEdgeFiltered,
	my_state_FilterEdges,
	my_state_GetBlk,
	my_state_GetBs4Blk,
	my_state_GetCuPix,
	my_state_GetNumTiles,
	my_state_GetPartition,
	my_state_GetTilesCoord,
	my_state_IsNewPict,
	my_state_SendSamples,
	my_state_SendSamplesChr,
	my_state_SendSamplesLuma
};

static char *stateNames[] = {
	"CheckEdgeFiltered",
	"FilterEdges",
	"GetBlk",
	"GetBs4Blk",
	"GetCuPix",
	"GetNumTiles",
	"GetPartition",
	"GetTilesCoord",
	"IsNewPict",
	"SendSamples",
	"SendSamplesChr",
	"SendSamplesLuma"
};

static enum states _FSM_state;



////////////////////////////////////////////////////////////////////////////////
// Token functions
static void read_BsHor() {
	index_BsHor = HevcDecoder_DBFilter_DeblockFilt_BsHor->read_inds[0];
	numTokens_BsHor = index_BsHor + fifo_u8_get_num_tokens(HevcDecoder_DBFilter_DeblockFilt_BsHor, 0);
}

static void read_end_BsHor() {
	HevcDecoder_DBFilter_DeblockFilt_BsHor->read_inds[0] = index_BsHor;
}
static void read_BsVer() {
	index_BsVer = HevcDecoder_DBFilter_DeblockFilt_BsVer->read_inds[0];
	numTokens_BsVer = index_BsVer + fifo_u8_get_num_tokens(HevcDecoder_DBFilter_DeblockFilt_BsVer, 0);
}

static void read_end_BsVer() {
	HevcDecoder_DBFilter_DeblockFilt_BsVer->read_inds[0] = index_BsVer;
}
static void read_DBFDisable() {
	index_DBFDisable = HevcDecoder_DBFilter_DeblockFilt_DBFDisable->read_inds[0];
	numTokens_DBFDisable = index_DBFDisable + fifo_i32_get_num_tokens(HevcDecoder_DBFilter_DeblockFilt_DBFDisable, 0);
}

static void read_end_DBFDisable() {
	HevcDecoder_DBFilter_DeblockFilt_DBFDisable->read_inds[0] = index_DBFDisable;
}
static void read_IsPicSlcLcu() {
	index_IsPicSlcLcu = HevcDecoder_DBFilter_DeblockFilt_IsPicSlcLcu->read_inds[1];
	numTokens_IsPicSlcLcu = index_IsPicSlcLcu + fifo_u8_get_num_tokens(HevcDecoder_DBFilter_DeblockFilt_IsPicSlcLcu, 1);
}

static void read_end_IsPicSlcLcu() {
	HevcDecoder_DBFilter_DeblockFilt_IsPicSlcLcu->read_inds[1] = index_IsPicSlcLcu;
}
static void read_LcuSizeMax() {
	index_LcuSizeMax = HevcDecoder_DBFilter_DeblockFilt_LcuSizeMax->read_inds[4];
	numTokens_LcuSizeMax = index_LcuSizeMax + fifo_u8_get_num_tokens(HevcDecoder_DBFilter_DeblockFilt_LcuSizeMax, 4);
}

static void read_end_LcuSizeMax() {
	HevcDecoder_DBFilter_DeblockFilt_LcuSizeMax->read_inds[4] = index_LcuSizeMax;
}
static void read_PicSize() {
	index_PicSize = HevcDecoder_DBFilter_DeblockFilt_PicSize->read_inds[4];
	numTokens_PicSize = index_PicSize + fifo_u16_get_num_tokens(HevcDecoder_DBFilter_DeblockFilt_PicSize, 4);
}

static void read_end_PicSize() {
	HevcDecoder_DBFilter_DeblockFilt_PicSize->read_inds[4] = index_PicSize;
}
static void read_Qp() {
	index_Qp = HevcDecoder_DBFilter_DeblockFilt_Qp->read_inds[0];
	numTokens_Qp = index_Qp + fifo_i8_get_num_tokens(HevcDecoder_DBFilter_DeblockFilt_Qp, 0);
}

static void read_end_Qp() {
	HevcDecoder_DBFilter_DeblockFilt_Qp->read_inds[0] = index_Qp;
}
static void read_SampleIn() {
	index_SampleIn = HevcDecoder_DBFilter_DeblockFilt_SampleIn->read_inds[1];
	numTokens_SampleIn = index_SampleIn + fifo_u8_get_num_tokens(HevcDecoder_DBFilter_DeblockFilt_SampleIn, 1);
}

static void read_end_SampleIn() {
	HevcDecoder_DBFilter_DeblockFilt_SampleIn->read_inds[1] = index_SampleIn;
}
static void read_SyntaxElem() {
	index_SyntaxElem = HevcDecoder_DBFilter_DeblockFilt_SyntaxElem->read_inds[0];
	numTokens_SyntaxElem = index_SyntaxElem + fifo_i8_get_num_tokens(HevcDecoder_DBFilter_DeblockFilt_SyntaxElem, 0);
}

static void read_end_SyntaxElem() {
	HevcDecoder_DBFilter_DeblockFilt_SyntaxElem->read_inds[0] = index_SyntaxElem;
}
static void read_TilesCoord() {
	index_TilesCoord = HevcDecoder_DBFilter_DeblockFilt_TilesCoord->read_inds[4];
	numTokens_TilesCoord = index_TilesCoord + fifo_u16_get_num_tokens(HevcDecoder_DBFilter_DeblockFilt_TilesCoord, 4);
}

static void read_end_TilesCoord() {
	HevcDecoder_DBFilter_DeblockFilt_TilesCoord->read_inds[4] = index_TilesCoord;
}

static void write_FiltSample() {
	index_FiltSample = HevcDecoder_DBFilter_DeblockFilt_FiltSample->write_ind;
	numFree_FiltSample = index_FiltSample + fifo_u8_get_room(HevcDecoder_DBFilter_DeblockFilt_FiltSample, NUM_READERS_FiltSample, SIZE_FiltSample);
}

static void write_end_FiltSample() {
	HevcDecoder_DBFilter_DeblockFilt_FiltSample->write_ind = index_FiltSample;
}

////////////////////////////////////////////////////////////////////////////////
// Functions/procedures
static i32 HevcDecoder_DBFilter_DeblockFilt_abs(i32 x);
static i32 HevcDecoder_DBFilter_DeblockFilt_clip_i32(i32 Value, i32 minVal, i32 maxVal);
static void HevcDecoder_DBFilter_DeblockFilt_zScanToAbsCoord(u16 rasterIdx, u16 coord[2]);
static i32 HevcDecoder_DBFilter_DeblockFilt_min(i32 a, i32 b);
static i32 decisionProcessLumaSamp(u8 p0, u8 p3, u8 q0, u8 q3, i32 dpq, i32 beta);
static void computeNextLcuAddr();
static void decisionProcessLumaBlkEdgeBetaTc(u16 addr[2], i32 isVertical, u8 bS);
static void decisionProcessLumaBlkEdgeBeta(u16 addr[2], i32 isVertical);
static void decisionProcessLumaBlkEdge(u16 addr[2], i32 isVertical, u16 betaLocal);
static void filterProcessLumaBlkVerticalEdge(u16 addr[2], u8 tcLocal);
static void filterProcessLumaBlkHorizontalEdge(u16 addr[2], u8 tcLocal);
static void filterProcessLumaBlkVertical(i32 idxBlk);
static void filterProcessLumaEdgeVertical(u8 pix[3][2048][4096], i32 offset, i32 stride, i32 betaTab[2], i32 tcTab[2], u8 no_p[2], u8 no_q[2], u16 blkAddr0[2], i32 idxBlk);
static void filterProcessLumaBlkHorizontal(i32 idxBlk);
static void filterProcessLumaEdgeHorizontal(u8 pix[3][2048][4096], i32 offset, i32 stride, i32 betaTab[2], i32 tcTab[2], u8 no_p[2], u8 no_q[2], u16 blkAddr0[2], i32 idxBlk);
static void filterProcessLumaSamp(u8 p[4], u8 q[4], u8 tcLocal);
static void decisionProcessChromaBlkEdgeTc(u16 addr[2], i32 isVertical, i32 cIdx);
static void filtProcessChrBlkHorizontalEdge(u16 addr[2], i32 isVerticalEdge, i32 cIdx, u8 tcLocal);
static void filtProcessChrBlkVerticalEdge(u16 addr[2], i32 cIdx, u8 tcLocal);
static void filterProcessChrSamp(u8 p[2], u8 q[2], u8 tc);
static void filterProcessChromaBlkVertical(i32 idxBlk);
static void filterProcessChromaEdgeVertical(u8 pix[3][2048][4096], i32 offset, i32 stride, i32 tcTab[2], u8 no_p[2], u8 no_q[2], u16 blkAddr0[2], i32 cIdx);
static void filterProcessChromaBlkHorizontal(i32 idxBlk);
static void filterProcessChromaEdgeHorizontal(u8 pix[3][2048][4096], i32 offset, i32 stride, i32 tcTab[2], u8 no_p[2], u8 no_q[2], u16 blkAddr0[2], i32 cIdx);
static void filterHorEdges();
static void saveRasterScanCu(u8 sample[24]);

static i32 HevcDecoder_DBFilter_DeblockFilt_abs(i32 x) {
	i32 tmp_if;

	if (x > 0) {
		tmp_if = x;
	} else {
		tmp_if = -x;
	}
	return tmp_if;
}
static i32 HevcDecoder_DBFilter_DeblockFilt_clip_i32(i32 Value, i32 minVal, i32 maxVal) {
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
static void HevcDecoder_DBFilter_DeblockFilt_zScanToAbsCoord(u16 rasterIdx, u16 coord[2]) {
	u8 tmp_ZscanToAbsCoord0;
	u8 tmp_ZscanToAbsCoord1;

	tmp_ZscanToAbsCoord0 = HevcDecoder_DBFilter_DeblockFilt_ZscanToAbsCoord0[rasterIdx];
	coord[0] = tmp_ZscanToAbsCoord0;
	tmp_ZscanToAbsCoord1 = HevcDecoder_DBFilter_DeblockFilt_ZscanToAbsCoord1[rasterIdx];
	coord[1] = tmp_ZscanToAbsCoord1;
}
static i32 HevcDecoder_DBFilter_DeblockFilt_min(i32 a, i32 b) {
	i32 tmp_if;

	if (a < b) {
		tmp_if = a;
	} else {
		tmp_if = b;
	}
	return tmp_if;
}
static i32 decisionProcessLumaSamp(u8 p0, u8 p3, u8 q0, u8 q3, i32 dpq, i32 beta) {
	i32 tmp_abs;
	i32 tmp_abs0;
	i32 tmp_abs1;
	u8 local_tc;

	tmp_abs = HevcDecoder_DBFilter_DeblockFilt_abs(p3 - p0);
	tmp_abs0 = HevcDecoder_DBFilter_DeblockFilt_abs(q0 - q3);
	tmp_abs1 = HevcDecoder_DBFilter_DeblockFilt_abs(p0 - q0);
	local_tc = tc;
	return dpq < beta >> 2 && tmp_abs + tmp_abs0 < beta >> 3 && tmp_abs1 < (5 * local_tc + 1) >> 1;
}
static void computeNextLcuAddr() {
	u16 local_xIdx;
	u8 local_lcuSizeMax;
	u16 local_tileIdx;
	u16 tmp_tilesEndSamp;
	u16 tmp_tilesBegSamp;
	u16 local_yIdx;
	u16 tmp_tilesEndSamp0;
	u16 tmp_tilesBegSamp0;
	u16 tmp_tilesBegSamp1;

	local_xIdx = xIdx;
	local_lcuSizeMax = lcuSizeMax;
	xIdx = local_xIdx + local_lcuSizeMax;
	local_xIdx = xIdx;
	local_tileIdx = tileIdx;
	tmp_tilesEndSamp = tilesEndSamp[local_tileIdx][0];
	if (local_xIdx >= tmp_tilesEndSamp) {
		local_tileIdx = tileIdx;
		tmp_tilesBegSamp = tilesBegSamp[local_tileIdx][0];
		xIdx = tmp_tilesBegSamp;
		local_yIdx = yIdx;
		local_lcuSizeMax = lcuSizeMax;
		yIdx = local_yIdx + local_lcuSizeMax;
		local_yIdx = yIdx;
		local_tileIdx = tileIdx;
		tmp_tilesEndSamp0 = tilesEndSamp[local_tileIdx][1];
		if (local_yIdx >= tmp_tilesEndSamp0) {
			local_tileIdx = tileIdx;
			tileIdx = local_tileIdx + 1;
			local_tileIdx = tileIdx;
			tmp_tilesBegSamp0 = tilesBegSamp[local_tileIdx][0];
			xIdx = tmp_tilesBegSamp0;
			local_tileIdx = tileIdx;
			tmp_tilesBegSamp1 = tilesBegSamp[local_tileIdx][1];
			yIdx = tmp_tilesBegSamp1;
		}
	}
}
static void decisionProcessLumaBlkEdgeBetaTc(u16 addr[2], i32 isVertical, u8 bS) {
	u16 tmp_addr;
	i32 local_PICT_WIDTH;
	u16 q0X;
	u16 tmp_addr0;
	u16 q0Y;
	u16 p0X;
	u16 p0Y;
	i32 Q;
	i8 tmp_qpTab;
	i8 tmp_qpTab0;
	i32 local_qPi;
	i32 local_betaOffset;
	u8 tmp_betaTable;
	u8 local_BIT_DEPTH;
	i32 local_tcOffset;
	u8 tmp_tcTable;

	tmp_addr = addr[0];
	local_PICT_WIDTH = HevcDecoder_DBFilter_DeblockFilt_PICT_WIDTH;
	q0X = tmp_addr / 4 & local_PICT_WIDTH / 4 - 1;
	tmp_addr0 = addr[1];
	q0Y = tmp_addr0 / 4;
	if (isVertical) {
		p0X = q0X - 1;
		p0Y = q0Y;
	} else {
		p0X = q0X;
		p0Y = q0Y - 1;
	}
	tmp_qpTab = qpTab[q0X][q0Y];
	tmp_qpTab0 = qpTab[p0X][p0Y];
	qPi = (tmp_qpTab + tmp_qpTab0 + 1) >> 1;
	local_qPi = qPi;
	local_betaOffset = betaOffset;
	Q = HevcDecoder_DBFilter_DeblockFilt_clip_i32(local_qPi + local_betaOffset, 0, 51);
	tmp_betaTable = betaTable[Q];
	local_BIT_DEPTH = BIT_DEPTH;
	beta = tmp_betaTable << (local_BIT_DEPTH - 8);
	local_qPi = qPi;
	local_tcOffset = tcOffset;
	Q = HevcDecoder_DBFilter_DeblockFilt_clip_i32(local_qPi + 2 * (bS - 1) + local_tcOffset, 0, 53);
	tmp_tcTable = tcTable[Q];
	local_BIT_DEPTH = BIT_DEPTH;
	tc = tmp_tcTable << (local_BIT_DEPTH - 8);
}
static void decisionProcessLumaBlkEdgeBeta(u16 addr[2], i32 isVertical) {
	u16 tmp_addr;
	i32 local_PICT_WIDTH;
	u16 q0X;
	u16 tmp_addr0;
	u16 q0Y;
	u16 p0X;
	u16 p0Y;
	i32 Q;
	i8 tmp_qpTab;
	i8 tmp_qpTab0;
	i32 local_qPi;
	i32 local_betaOffset;
	u8 tmp_betaTable;
	u8 local_BIT_DEPTH;

	tmp_addr = addr[0];
	local_PICT_WIDTH = HevcDecoder_DBFilter_DeblockFilt_PICT_WIDTH;
	q0X = tmp_addr / 4 & local_PICT_WIDTH / 4 - 1;
	tmp_addr0 = addr[1];
	q0Y = tmp_addr0 / 4;
	if (isVertical) {
		p0X = q0X - 1;
		p0Y = q0Y;
	} else {
		p0X = q0X;
		p0Y = q0Y - 1;
	}
	tmp_qpTab = qpTab[q0X][q0Y];
	tmp_qpTab0 = qpTab[p0X][p0Y];
	qPi = (tmp_qpTab + tmp_qpTab0 + 1) >> 1;
	local_qPi = qPi;
	local_betaOffset = betaOffset;
	Q = HevcDecoder_DBFilter_DeblockFilt_clip_i32(local_qPi + local_betaOffset, 0, 51);
	tmp_betaTable = betaTable[Q];
	local_BIT_DEPTH = BIT_DEPTH;
	beta = tmp_betaTable << (local_BIT_DEPTH - 8);
}
static void decisionProcessLumaBlkEdge(u16 addr[2], i32 isVertical, u16 betaLocal) {
	i32 dp0;
	i32 dp3;
	i32 dq0;
	i32 dq3;
	i32 dpq0;
	i32 dpq3;
	i32 dp;
	i32 dq;
	i32 d;
	i32 p0[4];
	i32 q0[4];
	i32 p3[4];
	i32 q3[4];
	i32 dSam0;
	i32 dSam3;
	i32 i;
	u16 tmp_addr;
	u16 tmp_addr0;
	u8 tmp_pictureBuffer;
	i32 i0;
	u16 tmp_addr1;
	u16 tmp_addr2;
	u8 tmp_pictureBuffer0;
	i32 i1;
	u16 tmp_addr3;
	u16 tmp_addr4;
	u8 tmp_pictureBuffer1;
	i32 i2;
	u16 tmp_addr5;
	u16 tmp_addr6;
	u8 tmp_pictureBuffer2;
	i32 i3;
	u16 tmp_addr7;
	u16 tmp_addr8;
	u8 tmp_pictureBuffer3;
	i32 i4;
	u16 tmp_addr9;
	u16 tmp_addr10;
	u8 tmp_pictureBuffer4;
	i32 i5;
	u16 tmp_addr11;
	u16 tmp_addr12;
	u8 tmp_pictureBuffer5;
	i32 i6;
	u16 tmp_addr13;
	u16 tmp_addr14;
	u8 tmp_pictureBuffer6;
	i32 tmp_p0;
	i32 tmp_p00;
	i32 tmp_p01;
	i32 tmp_q0;
	i32 tmp_q00;
	i32 tmp_q01;
	i32 tmp_p3;
	i32 tmp_p30;
	i32 tmp_p31;
	i32 tmp_q3;
	i32 tmp_q30;
	i32 tmp_q31;
	i32 tmp_p02;
	i32 tmp_p03;
	i32 tmp_q02;
	i32 tmp_q03;
	i32 tmp_p32;
	i32 tmp_p33;
	i32 tmp_q32;
	i32 tmp_q33;

	if (isVertical) {
		i = 0;
		while (i <= 3) {
			tmp_addr = addr[1];
			tmp_addr0 = addr[0];
			tmp_pictureBuffer = pictureBuffer[0][tmp_addr][tmp_addr0 + i];
			q0[i] = tmp_pictureBuffer;
			i = i + 1;
		}
		i0 = 1;
		while (i0 <= 4) {
			tmp_addr1 = addr[1];
			tmp_addr2 = addr[0];
			tmp_pictureBuffer0 = pictureBuffer[0][tmp_addr1][tmp_addr2 - i0];
			p0[i0 - 1] = tmp_pictureBuffer0;
			i0 = i0 + 1;
		}
		i1 = 0;
		while (i1 <= 3) {
			tmp_addr3 = addr[1];
			tmp_addr4 = addr[0];
			tmp_pictureBuffer1 = pictureBuffer[0][tmp_addr3 + 3][tmp_addr4 + i1];
			q3[i1] = tmp_pictureBuffer1;
			i1 = i1 + 1;
		}
		i2 = 1;
		while (i2 <= 4) {
			tmp_addr5 = addr[1];
			tmp_addr6 = addr[0];
			tmp_pictureBuffer2 = pictureBuffer[0][tmp_addr5 + 3][tmp_addr6 - i2];
			p3[i2 - 1] = tmp_pictureBuffer2;
			i2 = i2 + 1;
		}
	} else {
		i3 = 0;
		while (i3 <= 3) {
			tmp_addr7 = addr[1];
			tmp_addr8 = addr[0];
			tmp_pictureBuffer3 = pictureBuffer[0][tmp_addr7 + i3][tmp_addr8];
			q0[i3] = tmp_pictureBuffer3;
			i3 = i3 + 1;
		}
		i4 = 1;
		while (i4 <= 4) {
			tmp_addr9 = addr[1];
			tmp_addr10 = addr[0];
			tmp_pictureBuffer4 = pictureBuffer[0][tmp_addr9 - i4][tmp_addr10];
			p0[i4 - 1] = tmp_pictureBuffer4;
			i4 = i4 + 1;
		}
		i5 = 0;
		while (i5 <= 3) {
			tmp_addr11 = addr[1];
			tmp_addr12 = addr[0];
			tmp_pictureBuffer5 = pictureBuffer[0][tmp_addr11 + i5][tmp_addr12 + 3];
			q3[i5] = tmp_pictureBuffer5;
			i5 = i5 + 1;
		}
		i6 = 1;
		while (i6 <= 4) {
			tmp_addr13 = addr[1];
			tmp_addr14 = addr[0];
			tmp_pictureBuffer6 = pictureBuffer[0][tmp_addr13 - i6][tmp_addr14 + 3];
			p3[i6 - 1] = tmp_pictureBuffer6;
			i6 = i6 + 1;
		}
	}
	tmp_p0 = p0[2];
	tmp_p00 = p0[1];
	tmp_p01 = p0[0];
	dp0 = HevcDecoder_DBFilter_DeblockFilt_abs(tmp_p0 - 2 * tmp_p00 + tmp_p01);
	tmp_q0 = q0[2];
	tmp_q00 = q0[1];
	tmp_q01 = q0[0];
	dq0 = HevcDecoder_DBFilter_DeblockFilt_abs(tmp_q0 - 2 * tmp_q00 + tmp_q01);
	tmp_p3 = p3[2];
	tmp_p30 = p3[1];
	tmp_p31 = p3[0];
	dp3 = HevcDecoder_DBFilter_DeblockFilt_abs(tmp_p3 - 2 * tmp_p30 + tmp_p31);
	tmp_q3 = q3[2];
	tmp_q30 = q3[1];
	tmp_q31 = q3[0];
	dq3 = HevcDecoder_DBFilter_DeblockFilt_abs(tmp_q3 - 2 * tmp_q30 + tmp_q31);
	dpq0 = dp0 + dq0;
	dpq3 = dp3 + dq3;
	dp = dp0 + dp3;
	dq = dq0 + dq3;
	d = dpq0 + dpq3;
	if (d < betaLocal) {
		tmp_p02 = p0[0];
		tmp_p03 = p0[3];
		tmp_q02 = q0[0];
		tmp_q03 = q0[3];
		dSam0 = decisionProcessLumaSamp(tmp_p02, tmp_p03, tmp_q02, tmp_q03, 2 * dpq0, betaLocal);
		tmp_p32 = p3[0];
		tmp_p33 = p3[3];
		tmp_q32 = q3[0];
		tmp_q33 = q3[3];
		dSam3 = decisionProcessLumaSamp(tmp_p32, tmp_p33, tmp_q32, tmp_q33, 2 * dpq3, betaLocal);
		dE = 1;
		dEp = 0;
		dEq = 0;
		if (dSam0 && dSam3) {
			dE = 2;
		}
		if (dp < (betaLocal + (betaLocal >> 1)) >> 3) {
			dEp = 1;
		}
		if (dq < (betaLocal + (betaLocal >> 1)) >> 3) {
			dEq = 1;
		}
	} else {
		dE = 0;
		dEp = 0;
		dEq = 0;
	}
}
static void filterProcessLumaBlkVerticalEdge(u16 addr[2], u8 tcLocal) {
	u8 p[4];
	u8 q[4];
	u8 local_dE;
	i32 y;
	i32 i;
	u16 tmp_addr;
	u16 tmp_addr0;
	u8 tmp_pictureBuffer;
	i32 i0;
	u16 tmp_addr1;
	u16 tmp_addr2;
	u8 tmp_pictureBuffer0;
	i32 i1;
	u16 tmp_addr3;
	u16 tmp_addr4;
	u8 tmp_p;
	u16 tmp_addr5;
	u16 tmp_addr6;
	u8 tmp_q;

	local_dE = dE;
	if (local_dE != 0) {
		y = 0;
		while (y <= 3) {
			i = 1;
			while (i <= 4) {
				tmp_addr = addr[1];
				tmp_addr0 = addr[0];
				tmp_pictureBuffer = pictureBuffer[0][tmp_addr + y][tmp_addr0 - i];
				p[i - 1] = tmp_pictureBuffer;
				i = i + 1;
			}
			i0 = 0;
			while (i0 <= 3) {
				tmp_addr1 = addr[1];
				tmp_addr2 = addr[0];
				tmp_pictureBuffer0 = pictureBuffer[0][tmp_addr1 + y][tmp_addr2 + i0];
				q[i0] = tmp_pictureBuffer0;
				i0 = i0 + 1;
			}
			filterProcessLumaSamp(p, q, tcLocal);
			i1 = 0;
			while (i1 <= 2) {
				tmp_addr3 = addr[1];
				tmp_addr4 = addr[0];
				tmp_p = p[i1];
				pictureBuffer[0][tmp_addr3 + y][tmp_addr4 - 1 - i1] = tmp_p;
				tmp_addr5 = addr[1];
				tmp_addr6 = addr[0];
				tmp_q = q[i1];
				pictureBuffer[0][tmp_addr5 + y][tmp_addr6 + i1] = tmp_q;
				i1 = i1 + 1;
			}
			y = y + 1;
		}
	}
}
static void filterProcessLumaBlkHorizontalEdge(u16 addr[2], u8 tcLocal) {
	u8 p[4];
	u8 q[4];
	u8 local_dE;
	i32 x;
	i32 i;
	u16 tmp_addr;
	u16 tmp_addr0;
	u8 tmp_pictureBuffer;
	i32 i0;
	u16 tmp_addr1;
	u16 tmp_addr2;
	u8 tmp_pictureBuffer0;
	i32 i1;
	u16 tmp_addr3;
	u16 tmp_addr4;
	u8 tmp_p;
	u16 tmp_addr5;
	u16 tmp_addr6;
	u8 tmp_q;

	local_dE = dE;
	if (local_dE != 0) {
		x = 0;
		while (x <= 3) {
			i = 1;
			while (i <= 4) {
				tmp_addr = addr[1];
				tmp_addr0 = addr[0];
				tmp_pictureBuffer = pictureBuffer[0][tmp_addr - i][tmp_addr0 + x];
				p[i - 1] = tmp_pictureBuffer;
				i = i + 1;
			}
			i0 = 0;
			while (i0 <= 3) {
				tmp_addr1 = addr[1];
				tmp_addr2 = addr[0];
				tmp_pictureBuffer0 = pictureBuffer[0][tmp_addr1 + i0][tmp_addr2 + x];
				q[i0] = tmp_pictureBuffer0;
				i0 = i0 + 1;
			}
			filterProcessLumaSamp(p, q, tcLocal);
			i1 = 0;
			while (i1 <= 2) {
				tmp_addr3 = addr[1];
				tmp_addr4 = addr[0];
				tmp_p = p[i1];
				pictureBuffer[0][tmp_addr3 - 1 - i1][tmp_addr4 + x] = tmp_p;
				tmp_addr5 = addr[1];
				tmp_addr6 = addr[0];
				tmp_q = q[i1];
				pictureBuffer[0][tmp_addr5 + i1][tmp_addr6 + x] = tmp_q;
				i1 = i1 + 1;
			}
			x = x + 1;
		}
	}
}
static void filterProcessLumaBlkVertical(i32 idxBlk) {
	u16 blkAddr[2];
	u16 blkAddr0[2];
	i32 betaTab[2];
	i32 tcTab[2];
	i32 offset;
	i32 i;
	u8 no_p[2];
	i32 i0;
	u8 no_q[2];
	u8 bS0;
	u8 bS1;
	u16 tmp_blkAddr;
	u16 local_xAddrVert;
	u16 tmp_blkAddr0;
	u16 local_yAddrVert;
	u16 tmp_blkAddr00;
	u16 tmp_blkAddr01;
	u16 local_beta;
	u8 local_tc;
	u16 tmp_blkAddr02;
	u16 tmp_blkAddr03;
	i32 tmp_tcTab;
	i32 tmp_tcTab0;
	u16 tmp_blkAddr04;
	u16 tmp_blkAddr05;
	u16 tmp_blkAddr06;
	u16 tmp_blkAddr07;
	i32 local_PICT_WIDTH;
	i32 local_PICT_HEIGHT;
	u16 tmp_blkAddr08;
	u16 tmp_blkAddr09;

	i = 0;
	while (i <= 1) {
		no_p[i] = 0;
		i = i + 1;
	}
	i0 = 0;
	while (i0 <= 1) {
		no_q[i0] = 0;
		i0 = i0 + 1;
	}
	bS0 = bSTableVert[idxBlk];
	bS1 = bSTableVert[idxBlk + 2];
	if (bS0 != 0 || bS1 != 0) {
		HevcDecoder_DBFilter_DeblockFilt_zScanToAbsCoord(idxBlk, blkAddr);
		tmp_blkAddr = blkAddr[0];
		local_xAddrVert = xAddrVert;
		blkAddr0[0] = tmp_blkAddr + local_xAddrVert;
		tmp_blkAddr0 = blkAddr[1];
		local_yAddrVert = yAddrVert;
		blkAddr0[1] = tmp_blkAddr0 + local_yAddrVert;
		if (bS0 != 0) {
			tmp_blkAddr00 = blkAddr0[0];
			blkAddr[0] = tmp_blkAddr00;
			tmp_blkAddr01 = blkAddr0[1];
			blkAddr[1] = tmp_blkAddr01;
			decisionProcessLumaBlkEdgeBetaTc(blkAddr, 1, bS0);
			local_beta = beta;
			betaTab[0] = local_beta;
			local_tc = tc;
			tcTab[0] = local_tc;
		} else {
			tcTab[0] = 0;
		}
		if (bS1 != 0) {
			tmp_blkAddr02 = blkAddr0[0];
			blkAddr[0] = tmp_blkAddr02;
			tmp_blkAddr03 = blkAddr0[1];
			blkAddr[1] = tmp_blkAddr03 + 4;
			decisionProcessLumaBlkEdgeBetaTc(blkAddr, 1, bS1);
			local_beta = beta;
			betaTab[1] = local_beta;
			local_tc = tc;
			tcTab[1] = local_tc;
		} else {
			tcTab[1] = 0;
		}
		tmp_tcTab = tcTab[0];
		tmp_tcTab0 = tcTab[1];
		if (tmp_tcTab != 0 || tmp_tcTab0 != 0) {
			if (bS0 == 0) {
				tmp_blkAddr04 = blkAddr0[0];
				blkAddr[0] = tmp_blkAddr04;
				tmp_blkAddr05 = blkAddr0[1];
				blkAddr[1] = tmp_blkAddr05;
				decisionProcessLumaBlkEdgeBeta(blkAddr, 1);
				local_beta = beta;
				betaTab[0] = local_beta;
			}
			if (bS1 == 0) {
				tmp_blkAddr06 = blkAddr0[0];
				blkAddr[0] = tmp_blkAddr06;
				tmp_blkAddr07 = blkAddr0[1];
				blkAddr[1] = tmp_blkAddr07 + 4;
				decisionProcessLumaBlkEdgeBeta(blkAddr, 1);
				local_beta = beta;
				betaTab[1] = local_beta;
			}
			local_PICT_WIDTH = HevcDecoder_DBFilter_DeblockFilt_PICT_WIDTH;
			local_PICT_HEIGHT = HevcDecoder_DBFilter_DeblockFilt_PICT_HEIGHT;
			tmp_blkAddr08 = blkAddr0[1];
			local_PICT_WIDTH = HevcDecoder_DBFilter_DeblockFilt_PICT_WIDTH;
			tmp_blkAddr09 = blkAddr0[0];
			offset = 0 * (local_PICT_WIDTH * local_PICT_HEIGHT) + tmp_blkAddr08 * local_PICT_WIDTH + tmp_blkAddr09;
			local_PICT_WIDTH = HevcDecoder_DBFilter_DeblockFilt_PICT_WIDTH;
			filterProcessLumaEdgeVertical(pictureBuffer, offset, local_PICT_WIDTH, betaTab, tcTab, no_p, no_q, blkAddr0, idxBlk);
		}
	}
}
static void filterProcessLumaEdgeVertical(u8 pix[3][2048][4096], i32 offset, i32 stride, i32 betaTab[2], i32 tcTab[2], u8 no_p[2], u8 no_q[2], u16 blkAddr0[2], i32 idxBlk) {
	#if defined(OPENHEVC_ENABLE)
	hevc_v_loop_filter_luma_orcc(pix, offset, stride, betaTab, tcTab, no_p, no_q, blkAddr0, idxBlk);
	#else
	u16 blkAddr[2];
	u8 tmp_bSTableVert;
	u16 tmp_blkAddr0;
	u16 tmp_blkAddr00;
	i32 tmp_betaTab;
	i32 tmp_tcTab;
	u8 tmp_bSTableVert0;
	u16 tmp_blkAddr01;
	u16 tmp_blkAddr02;
	i32 tmp_betaTab0;
	i32 tmp_tcTab0;

	tmp_bSTableVert = bSTableVert[idxBlk];
	if (tmp_bSTableVert != 0) {
		tmp_blkAddr0 = blkAddr0[0];
		blkAddr[0] = tmp_blkAddr0;
		tmp_blkAddr00 = blkAddr0[1];
		blkAddr[1] = tmp_blkAddr00;
		tmp_betaTab = betaTab[0];
		decisionProcessLumaBlkEdge(blkAddr, 1, tmp_betaTab);
		tmp_tcTab = tcTab[0];
		filterProcessLumaBlkVerticalEdge(blkAddr, tmp_tcTab);
	}
	tmp_bSTableVert0 = bSTableVert[idxBlk + 2];
	if (tmp_bSTableVert0 != 0) {
		tmp_blkAddr01 = blkAddr0[0];
		blkAddr[0] = tmp_blkAddr01;
		tmp_blkAddr02 = blkAddr0[1];
		blkAddr[1] = tmp_blkAddr02 + 4;
		tmp_betaTab0 = betaTab[1];
		decisionProcessLumaBlkEdge(blkAddr, 1, tmp_betaTab0);
		tmp_tcTab0 = tcTab[1];
		filterProcessLumaBlkVerticalEdge(blkAddr, tmp_tcTab0);
	}
	#endif // defined(OPENHEVC_ENABLE)
}
static void filterProcessLumaBlkHorizontal(i32 idxBlk) {
	u16 blkAddr[2];
	u16 blkAddr0[2];
	i32 betaTab[2];
	i32 tcTab[2];
	i32 offset;
	i32 i;
	u8 no_p[2];
	i32 i0;
	u8 no_q[2];
	i16 local_xAddrHor;
	u8 local_log2lcuSizeMax;
	i16 local_yAddrHor;
	u8 bS0;
	u8 bS1;
	u16 tmp_blkAddr;
	u16 tmp_blkAddr0;
	u16 tmp_blkAddr00;
	u16 tmp_blkAddr01;
	u16 local_beta;
	u8 local_tc;
	u16 tmp_blkAddr02;
	u16 tmp_blkAddr03;
	i32 tmp_tcTab;
	i32 tmp_tcTab0;
	u16 tmp_blkAddr04;
	u16 tmp_blkAddr05;
	u16 tmp_blkAddr06;
	u16 tmp_blkAddr07;
	i32 local_PICT_WIDTH;
	i32 local_PICT_HEIGHT;
	u16 tmp_blkAddr08;
	u16 tmp_blkAddr09;

	i = 0;
	while (i <= 1) {
		no_p[i] = 0;
		i = i + 1;
	}
	i0 = 0;
	while (i0 <= 1) {
		no_q[i0] = 0;
		i0 = i0 + 1;
	}
	local_xAddrHor = xAddrHor;
	local_log2lcuSizeMax = log2lcuSizeMax;
	local_yAddrHor = yAddrHor;
	local_log2lcuSizeMax = log2lcuSizeMax;
	bS0 = bSTableHoriz[local_xAddrHor >> local_log2lcuSizeMax][local_yAddrHor >> local_log2lcuSizeMax][idxBlk];
	local_xAddrHor = xAddrHor;
	local_log2lcuSizeMax = log2lcuSizeMax;
	local_yAddrHor = yAddrHor;
	local_log2lcuSizeMax = log2lcuSizeMax;
	bS1 = bSTableHoriz[local_xAddrHor >> local_log2lcuSizeMax][local_yAddrHor >> local_log2lcuSizeMax][idxBlk + 1];
	if (bS0 != 0 || bS1 != 0) {
		HevcDecoder_DBFilter_DeblockFilt_zScanToAbsCoord(idxBlk, blkAddr);
		tmp_blkAddr = blkAddr[0];
		local_xAddrHor = xAddrHor;
		blkAddr0[0] = tmp_blkAddr + local_xAddrHor;
		tmp_blkAddr0 = blkAddr[1];
		local_yAddrHor = yAddrHor;
		blkAddr0[1] = tmp_blkAddr0 + local_yAddrHor;
		if (bS0 != 0) {
			tmp_blkAddr00 = blkAddr0[0];
			blkAddr[0] = tmp_blkAddr00;
			tmp_blkAddr01 = blkAddr0[1];
			blkAddr[1] = tmp_blkAddr01;
			decisionProcessLumaBlkEdgeBetaTc(blkAddr, 0, bS0);
			local_beta = beta;
			betaTab[0] = local_beta;
			local_tc = tc;
			tcTab[0] = local_tc;
		} else {
			tcTab[0] = 0;
		}
		if (bS1 != 0) {
			tmp_blkAddr02 = blkAddr0[0];
			blkAddr[0] = tmp_blkAddr02 + 4;
			tmp_blkAddr03 = blkAddr0[1];
			blkAddr[1] = tmp_blkAddr03;
			decisionProcessLumaBlkEdgeBetaTc(blkAddr, 0, bS1);
			local_beta = beta;
			betaTab[1] = local_beta;
			local_tc = tc;
			tcTab[1] = local_tc;
		} else {
			tcTab[1] = 0;
		}
		tmp_tcTab = tcTab[0];
		tmp_tcTab0 = tcTab[1];
		if (tmp_tcTab != 0 || tmp_tcTab0 != 0) {
			if (bS0 == 0) {
				tmp_blkAddr04 = blkAddr0[0];
				blkAddr[0] = tmp_blkAddr04;
				tmp_blkAddr05 = blkAddr0[1];
				blkAddr[1] = tmp_blkAddr05;
				decisionProcessLumaBlkEdgeBeta(blkAddr, 0);
				local_beta = beta;
				betaTab[0] = local_beta;
			}
			if (bS1 == 0) {
				tmp_blkAddr06 = blkAddr0[0];
				blkAddr[0] = tmp_blkAddr06 + 4;
				tmp_blkAddr07 = blkAddr0[1];
				blkAddr[1] = tmp_blkAddr07;
				decisionProcessLumaBlkEdgeBeta(blkAddr, 0);
				local_beta = beta;
				betaTab[1] = local_beta;
			}
			local_PICT_WIDTH = HevcDecoder_DBFilter_DeblockFilt_PICT_WIDTH;
			local_PICT_HEIGHT = HevcDecoder_DBFilter_DeblockFilt_PICT_HEIGHT;
			tmp_blkAddr08 = blkAddr0[1];
			local_PICT_WIDTH = HevcDecoder_DBFilter_DeblockFilt_PICT_WIDTH;
			tmp_blkAddr09 = blkAddr0[0];
			offset = 0 * (local_PICT_WIDTH * local_PICT_HEIGHT) + tmp_blkAddr08 * local_PICT_WIDTH + tmp_blkAddr09;
			local_PICT_WIDTH = HevcDecoder_DBFilter_DeblockFilt_PICT_WIDTH;
			filterProcessLumaEdgeHorizontal(pictureBuffer, offset, local_PICT_WIDTH, betaTab, tcTab, no_p, no_q, blkAddr0, idxBlk);
		}
	}
}
static void filterProcessLumaEdgeHorizontal(u8 pix[3][2048][4096], i32 offset, i32 stride, i32 betaTab[2], i32 tcTab[2], u8 no_p[2], u8 no_q[2], u16 blkAddr0[2], i32 idxBlk) {
	#if defined(OPENHEVC_ENABLE)
	hevc_h_loop_filter_luma_orcc(pix, offset, stride, betaTab, tcTab, no_p, no_q, blkAddr0, idxBlk);
	#else
	u16 blkAddr[2];
	i16 local_xAddrHor;
	u8 local_log2lcuSizeMax;
	i16 local_yAddrHor;
	u8 tmp_bSTableHoriz;
	u16 tmp_blkAddr0;
	u16 tmp_blkAddr00;
	i32 tmp_betaTab;
	i32 tmp_tcTab;
	u8 tmp_bSTableHoriz0;
	u16 tmp_blkAddr01;
	u16 tmp_blkAddr02;
	i32 tmp_betaTab0;
	i32 tmp_tcTab0;

	local_xAddrHor = xAddrHor;
	local_log2lcuSizeMax = log2lcuSizeMax;
	local_yAddrHor = yAddrHor;
	local_log2lcuSizeMax = log2lcuSizeMax;
	tmp_bSTableHoriz = bSTableHoriz[local_xAddrHor >> local_log2lcuSizeMax][local_yAddrHor >> local_log2lcuSizeMax][idxBlk];
	if (tmp_bSTableHoriz != 0) {
		tmp_blkAddr0 = blkAddr0[0];
		blkAddr[0] = tmp_blkAddr0;
		tmp_blkAddr00 = blkAddr0[1];
		blkAddr[1] = tmp_blkAddr00;
		tmp_betaTab = betaTab[0];
		decisionProcessLumaBlkEdge(blkAddr, 0, tmp_betaTab);
		tmp_tcTab = tcTab[0];
		filterProcessLumaBlkHorizontalEdge(blkAddr, tmp_tcTab);
	}
	local_xAddrHor = xAddrHor;
	local_log2lcuSizeMax = log2lcuSizeMax;
	local_yAddrHor = yAddrHor;
	local_log2lcuSizeMax = log2lcuSizeMax;
	tmp_bSTableHoriz0 = bSTableHoriz[local_xAddrHor >> local_log2lcuSizeMax][local_yAddrHor >> local_log2lcuSizeMax][idxBlk + 1];
	if (tmp_bSTableHoriz0 != 0) {
		tmp_blkAddr01 = blkAddr0[0];
		blkAddr[0] = tmp_blkAddr01 + 4;
		tmp_blkAddr02 = blkAddr0[1];
		blkAddr[1] = tmp_blkAddr02;
		tmp_betaTab0 = betaTab[1];
		decisionProcessLumaBlkEdge(blkAddr, 0, tmp_betaTab0);
		tmp_tcTab0 = tcTab[1];
		filterProcessLumaBlkHorizontalEdge(blkAddr, tmp_tcTab0);
	}
	#endif // defined(OPENHEVC_ENABLE)
}
static void filterProcessLumaSamp(u8 p[4], u8 q[4], u8 tcLocal) {
	u8 p0;
	u8 p1;
	u8 p2;
	u8 q0;
	u8 q1;
	u8 q2;
	u8 p3;
	u8 q3;
	i32 delta;
	i32 deltaP;
	i32 deltaQ;
	u8 local_dE;
	i32 tmp_clip_i32;
	i32 tmp_clip_i320;
	i32 tmp_clip_i321;
	i32 tmp_clip_i322;
	i32 tmp_clip_i323;
	i32 tmp_clip_i324;
	i32 tmp_abs;
	i32 tmp_clip_i325;
	i32 tmp_clip_i326;
	i32 local_dEp;
	i32 tmp_clip_i327;
	i32 local_dEq;
	i32 tmp_clip_i328;

	p0 = p[0];
	p1 = p[1];
	p2 = p[2];
	q0 = q[0];
	q1 = q[1];
	q2 = q[2];
	p3 = p[3];
	q3 = q[3];
	local_dE = dE;
	if (local_dE == 2) {
		tmp_clip_i32 = HevcDecoder_DBFilter_DeblockFilt_clip_i32((p2 + 2 * p1 + 2 * p0 + 2 * q0 + q1 + 4) >> 3, p0 - 2 * tcLocal, p0 + 2 * tcLocal);
		p[0] = tmp_clip_i32;
		tmp_clip_i320 = HevcDecoder_DBFilter_DeblockFilt_clip_i32((p2 + p1 + p0 + q0 + 2) >> 2, p1 - 2 * tcLocal, p1 + 2 * tcLocal);
		p[1] = tmp_clip_i320;
		tmp_clip_i321 = HevcDecoder_DBFilter_DeblockFilt_clip_i32((2 * p3 + 3 * p2 + p1 + p0 + q0 + 4) >> 3, p2 - 2 * tcLocal, p2 + 2 * tcLocal);
		p[2] = tmp_clip_i321;
		tmp_clip_i322 = HevcDecoder_DBFilter_DeblockFilt_clip_i32((p1 + 2 * p0 + 2 * q0 + 2 * q1 + q2 + 4) >> 3, q0 - 2 * tcLocal, q0 + 2 * tcLocal);
		q[0] = tmp_clip_i322;
		tmp_clip_i323 = HevcDecoder_DBFilter_DeblockFilt_clip_i32((p0 + q0 + q1 + q2 + 2) >> 2, q1 - 2 * tcLocal, q1 + 2 * tcLocal);
		q[1] = tmp_clip_i323;
		tmp_clip_i324 = HevcDecoder_DBFilter_DeblockFilt_clip_i32((p0 + q0 + q1 + 3 * q2 + 2 * q3 + 4) >> 3, q2 - 2 * tcLocal, q2 + 2 * tcLocal);
		q[2] = tmp_clip_i324;
	} else {
		delta = (9 * (q0 - p0) - 3 * (q1 - p1) + 8) >> 4;
		tmp_abs = HevcDecoder_DBFilter_DeblockFilt_abs(delta);
		if (tmp_abs < 10 * tcLocal) {
			delta = HevcDecoder_DBFilter_DeblockFilt_clip_i32(delta, -tcLocal, tcLocal);
			tmp_clip_i325 = HevcDecoder_DBFilter_DeblockFilt_clip_i32(p0 + delta, 0, 255);
			p[0] = tmp_clip_i325;
			tmp_clip_i326 = HevcDecoder_DBFilter_DeblockFilt_clip_i32(q0 - delta, 0, 255);
			q[0] = tmp_clip_i326;
			local_dEp = dEp;
			if (local_dEp) {
				deltaP = HevcDecoder_DBFilter_DeblockFilt_clip_i32((((p2 + p0 + 1) >> 1) - p1 + delta) >> 1, -(tcLocal >> 1), tcLocal >> 1);
				tmp_clip_i327 = HevcDecoder_DBFilter_DeblockFilt_clip_i32(p1 + deltaP, 0, 255);
				p[1] = tmp_clip_i327;
			}
			local_dEq = dEq;
			if (local_dEq) {
				deltaQ = HevcDecoder_DBFilter_DeblockFilt_clip_i32((((q2 + q0 + 1) >> 1) - q1 - delta) >> 1, -(tcLocal >> 1), tcLocal >> 1);
				tmp_clip_i328 = HevcDecoder_DBFilter_DeblockFilt_clip_i32(q1 + deltaQ, 0, 255);
				q[1] = tmp_clip_i328;
			}
		}
	}
}
static void decisionProcessChromaBlkEdgeTc(u16 addr[2], i32 isVertical, i32 cIdx) {
	u16 tmp_addr;
	i32 local_PICT_WIDTH;
	u16 q0X;
	u16 tmp_addr0;
	u16 q0Y;
	u16 p0X;
	u16 p0Y;
	u8 bS;
	i32 qPC;
	i32 Q;
	u16 idx;
	i8 tmp_qpTab;
	i8 tmp_qpTab0;
	i32 local_qPi;
	i8 tmp_qpChrOff;
	i32 tmp_min;
	i32 local_tcOffset;
	u8 tmp_tcTable;
	u8 local_BIT_DEPTH;

	tmp_addr = addr[0];
	local_PICT_WIDTH = HevcDecoder_DBFilter_DeblockFilt_PICT_WIDTH;
	q0X = tmp_addr / 4 & local_PICT_WIDTH / 4 - 1;
	tmp_addr0 = addr[1];
	q0Y = tmp_addr0 / 4;
	bS = 2;
	if (isVertical) {
		p0X = q0X - 1;
		p0Y = q0Y;
		idx = addr[0];
	} else {
		p0X = q0X;
		p0Y = q0Y - 1;
		idx = addr[1];
	}
	tmp_qpTab = qpTab[q0X][q0Y];
	tmp_qpTab0 = qpTab[p0X][p0Y];
	qPi = (tmp_qpTab + tmp_qpTab0 + 1) >> 1;
	local_qPi = qPi;
	tmp_qpChrOff = qpChrOff[cIdx - 1];
	tmp_min = HevcDecoder_DBFilter_DeblockFilt_min(local_qPi + tmp_qpChrOff, 51);
	qPC = qPcTable[tmp_min];
	local_tcOffset = tcOffset;
	Q = HevcDecoder_DBFilter_DeblockFilt_clip_i32(qPC + 2 * (bS - 1) + local_tcOffset, 0, 53);
	if ((idx >> 2 & 3) != 0) {
		tc = 0;
	} else {
		tmp_tcTable = tcTable[Q];
		local_BIT_DEPTH = BIT_DEPTH;
		tc = tmp_tcTable << (local_BIT_DEPTH - 8);
	}
}
static void filtProcessChrBlkHorizontalEdge(u16 addr[2], i32 isVerticalEdge, i32 cIdx, u8 tcLocal) {
	u16 tmp_addr;
	u16 addrX;
	u16 tmp_addr0;
	u16 addrY;
	u8 p[2];
	u8 q[2];
	i32 x;
	i32 i;
	u8 tmp_pictureBuffer;
	i32 i0;
	u8 tmp_pictureBuffer0;
	u8 tmp_p;
	u8 tmp_q;

	tmp_addr = addr[0];
	addrX = tmp_addr >> 1;
	tmp_addr0 = addr[1];
	addrY = tmp_addr0 >> 1;
	x = 0;
	while (x <= 3) {
		i = 1;
		while (i <= 2) {
			tmp_pictureBuffer = pictureBuffer[cIdx][addrY - i][addrX + x];
			p[i - 1] = tmp_pictureBuffer;
			i = i + 1;
		}
		i0 = 0;
		while (i0 <= 1) {
			tmp_pictureBuffer0 = pictureBuffer[cIdx][addrY + i0][addrX + x];
			q[i0] = tmp_pictureBuffer0;
			i0 = i0 + 1;
		}
		filterProcessChrSamp(p, q, tcLocal);
		tmp_p = p[0];
		pictureBuffer[cIdx][addrY - 1][addrX + x] = tmp_p;
		tmp_q = q[0];
		pictureBuffer[cIdx][addrY][addrX + x] = tmp_q;
		x = x + 1;
	}
}
static void filtProcessChrBlkVerticalEdge(u16 addr[2], i32 cIdx, u8 tcLocal) {
	u16 tmp_addr;
	u16 addrX;
	u16 tmp_addr0;
	u16 addrY;
	u8 p[2];
	u8 q[2];
	i32 y;
	i32 i;
	u8 tmp_pictureBuffer;
	i32 i0;
	u8 tmp_pictureBuffer0;
	u8 tmp_p;
	u8 tmp_q;

	tmp_addr = addr[0];
	addrX = tmp_addr >> 1;
	tmp_addr0 = addr[1];
	addrY = tmp_addr0 >> 1;
	y = 0;
	while (y <= 3) {
		i = 1;
		while (i <= 2) {
			tmp_pictureBuffer = pictureBuffer[cIdx][addrY + y][addrX - i];
			p[i - 1] = tmp_pictureBuffer;
			i = i + 1;
		}
		i0 = 0;
		while (i0 <= 1) {
			tmp_pictureBuffer0 = pictureBuffer[cIdx][addrY + y][addrX + i0];
			q[i0] = tmp_pictureBuffer0;
			i0 = i0 + 1;
		}
		filterProcessChrSamp(p, q, tcLocal);
		tmp_p = p[0];
		pictureBuffer[cIdx][addrY + y][addrX - 1] = tmp_p;
		tmp_q = q[0];
		pictureBuffer[cIdx][addrY + y][addrX] = tmp_q;
		y = y + 1;
	}
}
static void filterProcessChrSamp(u8 p[2], u8 q[2], u8 tc) {
	i32 delta;
	u8 p0;
	u8 p1;
	u8 q0;
	u8 q1;
	i32 tmp_clip_i32;
	i32 tmp_clip_i320;

	p0 = p[0];
	p1 = p[1];
	q0 = q[0];
	q1 = q[1];
	delta = HevcDecoder_DBFilter_DeblockFilt_clip_i32((((q0 - p0) << 2) + p1 - q1 + 4) >> 3, -tc, tc);
	tmp_clip_i32 = HevcDecoder_DBFilter_DeblockFilt_clip_i32(p0 + delta, 0, 255);
	p[0] = tmp_clip_i32;
	tmp_clip_i320 = HevcDecoder_DBFilter_DeblockFilt_clip_i32(q0 - delta, 0, 255);
	q[0] = tmp_clip_i320;
}
static void filterProcessChromaBlkVertical(i32 idxBlk) {
	u16 blkAddr[2];
	u16 blkAddr0[2];
	i32 tcTab[2];
	i32 offset;
	i32 i;
	u8 no_p[2];
	i32 i0;
	u8 no_q[2];
	u8 bS0;
	u8 bS1;
	i32 cIdx;
	u16 tmp_blkAddr;
	u16 local_xAddrVert;
	u16 tmp_blkAddr0;
	u16 local_yAddrVert;
	u16 tmp_blkAddr1;
	u16 tmp_blkAddr2;
	u8 local_tc;
	u16 tmp_blkAddr00;
	u16 tmp_blkAddr01;
	i32 tmp_tcTab;
	i32 tmp_tcTab0;
	i32 local_PICT_WIDTH;
	i32 local_PICT_HEIGHT;
	u16 tmp_blkAddr02;
	u16 tmp_blkAddr03;

	i = 0;
	while (i <= 1) {
		no_p[i] = 0;
		i = i + 1;
	}
	i0 = 0;
	while (i0 <= 1) {
		no_q[i0] = 0;
		i0 = i0 + 1;
	}
	bS0 = bSTableVert[idxBlk];
	bS1 = bSTableVert[idxBlk + 8];
	cIdx = 1;
	while (cIdx <= 2) {
		if (bS0 == 2 || bS1 == 2) {
			HevcDecoder_DBFilter_DeblockFilt_zScanToAbsCoord(idxBlk, blkAddr);
			tmp_blkAddr = blkAddr[0];
			local_xAddrVert = xAddrVert;
			blkAddr[0] = tmp_blkAddr + local_xAddrVert;
			tmp_blkAddr0 = blkAddr[1];
			local_yAddrVert = yAddrVert;
			blkAddr[1] = tmp_blkAddr0 + local_yAddrVert;
			tmp_blkAddr1 = blkAddr[0];
			blkAddr0[0] = tmp_blkAddr1;
			tmp_blkAddr2 = blkAddr[1];
			blkAddr0[1] = tmp_blkAddr2;
			if (bS0 == 2) {
				decisionProcessChromaBlkEdgeTc(blkAddr, 1, cIdx);
				local_tc = tc;
				tcTab[0] = local_tc;
			} else {
				tcTab[0] = 0;
			}
			if (bS1 == 2) {
				tmp_blkAddr00 = blkAddr0[0];
				blkAddr[0] = tmp_blkAddr00;
				tmp_blkAddr01 = blkAddr0[1];
				blkAddr[1] = tmp_blkAddr01 + 8;
				decisionProcessChromaBlkEdgeTc(blkAddr, 1, cIdx);
				local_tc = tc;
				tcTab[1] = local_tc;
			} else {
				tcTab[1] = 0;
			}
			tmp_tcTab = tcTab[0];
			tmp_tcTab0 = tcTab[1];
			if (tmp_tcTab != 0 || tmp_tcTab0 != 0) {
				local_PICT_WIDTH = HevcDecoder_DBFilter_DeblockFilt_PICT_WIDTH;
				local_PICT_HEIGHT = HevcDecoder_DBFilter_DeblockFilt_PICT_HEIGHT;
				tmp_blkAddr02 = blkAddr0[1];
				local_PICT_WIDTH = HevcDecoder_DBFilter_DeblockFilt_PICT_WIDTH;
				tmp_blkAddr03 = blkAddr0[0];
				offset = cIdx * (local_PICT_WIDTH * local_PICT_HEIGHT) + (tmp_blkAddr02 >> 1) * local_PICT_WIDTH + (tmp_blkAddr03 >> 1);
				local_PICT_WIDTH = HevcDecoder_DBFilter_DeblockFilt_PICT_WIDTH;
				filterProcessChromaEdgeVertical(pictureBuffer, offset, local_PICT_WIDTH, tcTab, no_p, no_q, blkAddr0, cIdx);
			}
		}
		cIdx = cIdx + 1;
	}
}
static void filterProcessChromaEdgeVertical(u8 pix[3][2048][4096], i32 offset, i32 stride, i32 tcTab[2], u8 no_p[2], u8 no_q[2], u16 blkAddr0[2], i32 cIdx) {
	#if defined(OPENHEVC_ENABLE)
	hevc_v_loop_filter_chroma_orcc(pix, offset, stride, tcTab, no_p, no_q, blkAddr0, cIdx);
	#else
	u16 blkAddr[2];
	i32 tmp_tcTab;
	u16 tmp_blkAddr0;
	u16 tmp_blkAddr00;
	i32 tmp_tcTab0;
	i32 tmp_tcTab1;
	u16 tmp_blkAddr01;
	u16 tmp_blkAddr02;
	i32 tmp_tcTab2;

	tmp_tcTab = tcTab[0];
	if (tmp_tcTab != 0) {
		tmp_blkAddr0 = blkAddr0[0];
		blkAddr[0] = tmp_blkAddr0;
		tmp_blkAddr00 = blkAddr0[1];
		blkAddr[1] = tmp_blkAddr00;
		tmp_tcTab0 = tcTab[0];
		filtProcessChrBlkVerticalEdge(blkAddr, cIdx, tmp_tcTab0);
	}
	tmp_tcTab1 = tcTab[1];
	if (tmp_tcTab1 != 0) {
		tmp_blkAddr01 = blkAddr0[0];
		blkAddr[0] = tmp_blkAddr01;
		tmp_blkAddr02 = blkAddr0[1];
		blkAddr[1] = tmp_blkAddr02 + 8;
		tmp_tcTab2 = tcTab[1];
		filtProcessChrBlkVerticalEdge(blkAddr, cIdx, tmp_tcTab2);
	}
	#endif // defined(OPENHEVC_ENABLE)
}
static void filterProcessChromaBlkHorizontal(i32 idxBlk) {
	u16 blkAddr[2];
	u16 blkAddr0[2];
	i32 tcTab[2];
	i32 offset;
	i32 i;
	u8 no_p[2];
	i32 i0;
	u8 no_q[2];
	i16 local_xAddrHor;
	u8 local_log2lcuSizeMax;
	i16 local_yAddrHor;
	u8 bS0;
	u8 bS1;
	i32 cIdx;
	u16 tmp_blkAddr;
	u16 tmp_blkAddr0;
	u16 tmp_blkAddr1;
	u16 tmp_blkAddr2;
	u8 local_tc;
	u16 tmp_blkAddr00;
	u16 tmp_blkAddr01;
	i32 tmp_tcTab;
	i32 tmp_tcTab0;
	i32 local_PICT_WIDTH;
	i32 local_PICT_HEIGHT;
	u16 tmp_blkAddr02;
	u16 tmp_blkAddr03;

	i = 0;
	while (i <= 1) {
		no_p[i] = 0;
		i = i + 1;
	}
	i0 = 0;
	while (i0 <= 1) {
		no_q[i0] = 0;
		i0 = i0 + 1;
	}
	local_xAddrHor = xAddrHor;
	local_log2lcuSizeMax = log2lcuSizeMax;
	local_yAddrHor = yAddrHor;
	local_log2lcuSizeMax = log2lcuSizeMax;
	bS0 = bSTableHoriz[local_xAddrHor >> local_log2lcuSizeMax][local_yAddrHor >> local_log2lcuSizeMax][idxBlk];
	local_xAddrHor = xAddrHor;
	local_log2lcuSizeMax = log2lcuSizeMax;
	local_yAddrHor = yAddrHor;
	local_log2lcuSizeMax = log2lcuSizeMax;
	bS1 = bSTableHoriz[local_xAddrHor >> local_log2lcuSizeMax][local_yAddrHor >> local_log2lcuSizeMax][idxBlk + 4];
	cIdx = 1;
	while (cIdx <= 2) {
		if (bS0 == 2 || bS1 == 2) {
			HevcDecoder_DBFilter_DeblockFilt_zScanToAbsCoord(idxBlk, blkAddr);
			tmp_blkAddr = blkAddr[0];
			local_xAddrHor = xAddrHor;
			blkAddr[0] = tmp_blkAddr + local_xAddrHor;
			tmp_blkAddr0 = blkAddr[1];
			local_yAddrHor = yAddrHor;
			blkAddr[1] = tmp_blkAddr0 + local_yAddrHor;
			tmp_blkAddr1 = blkAddr[0];
			blkAddr0[0] = tmp_blkAddr1;
			tmp_blkAddr2 = blkAddr[1];
			blkAddr0[1] = tmp_blkAddr2;
			if (bS0 == 2) {
				decisionProcessChromaBlkEdgeTc(blkAddr, 0, cIdx);
				local_tc = tc;
				tcTab[0] = local_tc;
			} else {
				tcTab[0] = 0;
			}
			if (bS1 == 2) {
				tmp_blkAddr00 = blkAddr0[0];
				blkAddr[0] = tmp_blkAddr00 + 8;
				tmp_blkAddr01 = blkAddr0[1];
				blkAddr[1] = tmp_blkAddr01;
				decisionProcessChromaBlkEdgeTc(blkAddr, 0, cIdx);
				local_tc = tc;
				tcTab[1] = local_tc;
			} else {
				tcTab[1] = 0;
			}
			tmp_tcTab = tcTab[0];
			tmp_tcTab0 = tcTab[1];
			if (tmp_tcTab != 0 || tmp_tcTab0 != 0) {
				local_PICT_WIDTH = HevcDecoder_DBFilter_DeblockFilt_PICT_WIDTH;
				local_PICT_HEIGHT = HevcDecoder_DBFilter_DeblockFilt_PICT_HEIGHT;
				tmp_blkAddr02 = blkAddr0[1];
				local_PICT_WIDTH = HevcDecoder_DBFilter_DeblockFilt_PICT_WIDTH;
				tmp_blkAddr03 = blkAddr0[0];
				offset = cIdx * (local_PICT_WIDTH * local_PICT_HEIGHT) + (tmp_blkAddr02 >> 1) * local_PICT_WIDTH + (tmp_blkAddr03 >> 1);
				local_PICT_WIDTH = HevcDecoder_DBFilter_DeblockFilt_PICT_WIDTH;
				filterProcessChromaEdgeHorizontal(pictureBuffer, offset, local_PICT_WIDTH, tcTab, no_p, no_q, blkAddr0, cIdx);
			}
		}
		cIdx = cIdx + 1;
	}
}
static void filterProcessChromaEdgeHorizontal(u8 pix[3][2048][4096], i32 offset, i32 stride, i32 tcTab[2], u8 no_p[2], u8 no_q[2], u16 blkAddr0[2], i32 cIdx) {
	#if defined(OPENHEVC_ENABLE)
	hevc_h_loop_filter_chroma_orcc(pix, offset, stride, tcTab, no_p, no_q, blkAddr0, cIdx);
	#else
	u16 blkAddr[2];
	i32 tmp_tcTab;
	u16 tmp_blkAddr0;
	u16 tmp_blkAddr00;
	i32 tmp_tcTab0;
	i32 tmp_tcTab1;
	u16 tmp_blkAddr01;
	u16 tmp_blkAddr02;
	i32 tmp_tcTab2;

	tmp_tcTab = tcTab[0];
	if (tmp_tcTab != 0) {
		tmp_blkAddr0 = blkAddr0[0];
		blkAddr[0] = tmp_blkAddr0;
		tmp_blkAddr00 = blkAddr0[1];
		blkAddr[1] = tmp_blkAddr00;
		tmp_tcTab0 = tcTab[0];
		filtProcessChrBlkHorizontalEdge(blkAddr, 0, cIdx, tmp_tcTab0);
	}
	tmp_tcTab1 = tcTab[1];
	if (tmp_tcTab1 != 0) {
		tmp_blkAddr01 = blkAddr0[0];
		blkAddr[0] = tmp_blkAddr01 + 8;
		tmp_blkAddr02 = blkAddr0[1];
		blkAddr[1] = tmp_blkAddr02;
		tmp_tcTab2 = tcTab[1];
		filtProcessChrBlkHorizontalEdge(blkAddr, 0, cIdx, tmp_tcTab2);
	}
	#endif // defined(OPENHEVC_ENABLE)
}
static void filterHorEdges() {
	u16 local_numPartition;
	i32 lumaPartMax;
	i32 chromaPartMax;
	i32 idxBlk;
	i32 idxBlk0;

	local_numPartition = numPartition;
	lumaPartMax = (local_numPartition >> 2) - 1;
	local_numPartition = numPartition;
	chromaPartMax = (local_numPartition >> 4) - 1;
	idxBlk = 0;
	while (idxBlk <= lumaPartMax) {
		filterProcessLumaBlkHorizontal(idxBlk << 2);
		idxBlk = idxBlk + 1;
	}
	idxBlk0 = 0;
	while (idxBlk0 <= chromaPartMax) {
		filterProcessChromaBlkHorizontal(idxBlk0 << 4);
		idxBlk0 = idxBlk0 + 1;
	}
}
static void saveRasterScanCu(u8 sample[24]) {
	u16 pixAddr[2];
	u32 tokenOffset;
	u16 local_blkIdx;
	u16 tmp_pixAddr;
	u16 local_xAddrVert;
	u16 tmp_pixAddr0;
	u16 local_yAddrVert;
	i32 y;
	i32 x;
	u16 tmp_pixAddr1;
	u16 tmp_pixAddr2;
	u8 tmp_sample;
	u16 tmp_pixAddr3;
	u16 tmp_pixAddr4;
	u32 comp;
	u32 y0;
	u32 x0;
	u16 tmp_pixAddr5;
	u16 tmp_pixAddr6;
	u8 tmp_sample0;

	local_blkIdx = blkIdx;
	HevcDecoder_DBFilter_DeblockFilt_zScanToAbsCoord(local_blkIdx, pixAddr);
	tmp_pixAddr = pixAddr[0];
	local_xAddrVert = xAddrVert;
	pixAddr[0] = tmp_pixAddr + local_xAddrVert;
	tmp_pixAddr0 = pixAddr[1];
	local_yAddrVert = yAddrVert;
	pixAddr[1] = tmp_pixAddr0 + local_yAddrVert;
	y = 0;
	while (y <= 3) {
		x = 0;
		while (x <= 3) {
			tmp_pixAddr1 = pixAddr[1];
			tmp_pixAddr2 = pixAddr[0];
			tmp_sample = sample[4 * y + x];
			pictureBuffer[0][tmp_pixAddr1 + y][tmp_pixAddr2 + x] = tmp_sample;
			x = x + 1;
		}
		y = y + 1;
	}
	tokenOffset = 16;
	tmp_pixAddr3 = pixAddr[0];
	pixAddr[0] = tmp_pixAddr3 >> 1;
	tmp_pixAddr4 = pixAddr[1];
	pixAddr[1] = tmp_pixAddr4 >> 1;
	comp = 1;
	while (comp <= 2) {
		y0 = 0;
		while (y0 <= 1) {
			x0 = 0;
			while (x0 <= 1) {
				tmp_pixAddr5 = pixAddr[1];
				tmp_pixAddr6 = pixAddr[0];
				tmp_sample0 = sample[tokenOffset + 2 * y0 + x0];
				pictureBuffer[comp][tmp_pixAddr5 + y0][tmp_pixAddr6 + x0] = tmp_sample0;
				x0 = x0 + 1;
			}
			y0 = y0 + 1;
		}
		tokenOffset = tokenOffset + 4;
		comp = comp + 1;
	}
}

////////////////////////////////////////////////////////////////////////////////
// Actions
static i32 isSchedulable_isNewSlc() {
	i32 result;
	u8 isNewPicSlcLcu;
	u8 local_NEW_SLC;

	isNewPicSlcLcu = tokens_IsPicSlcLcu[(index_IsPicSlcLcu + (0)) % SIZE_IsPicSlcLcu];
	local_NEW_SLC = HevcDecoder_DBFilter_DeblockFilt_NEW_SLC;
	result = isNewPicSlcLcu == local_NEW_SLC;
	return result;
}

static void isNewSlc() {

	u8 isNewPicSlcLcu;
	u16 picWidthInPix;
	u16 picHeightInPix;
	u8 log2_lcuSz;
	i32 disableFlag;
	i8 betaOff;
	i8 tcOff;
	i8 qpUOff;
	i8 qpVOff;

	isNewPicSlcLcu = tokens_IsPicSlcLcu[(index_IsPicSlcLcu + (0)) % SIZE_IsPicSlcLcu];
	picWidthInPix = tokens_PicSize[(index_PicSize + (0)) % SIZE_PicSize];
	picHeightInPix = tokens_PicSize[(index_PicSize + (1)) % SIZE_PicSize];
	log2_lcuSz = tokens_LcuSizeMax[(index_LcuSizeMax + (0)) % SIZE_LcuSizeMax];
	disableFlag = tokens_DBFDisable[(index_DBFDisable + (0)) % SIZE_DBFDisable];
	betaOff = tokens_SyntaxElem[(index_SyntaxElem + (0)) % SIZE_SyntaxElem];
	tcOff = tokens_SyntaxElem[(index_SyntaxElem + (1)) % SIZE_SyntaxElem];
	qpUOff = tokens_SyntaxElem[(index_SyntaxElem + (2)) % SIZE_SyntaxElem];
	qpVOff = tokens_SyntaxElem[(index_SyntaxElem + (3)) % SIZE_SyntaxElem];
	disDbf = disableFlag;
	betaOffset = betaOff;
	tcOffset = tcOff;
	qpChrOff[0] = qpUOff;
	qpChrOff[1] = qpVOff;

	// Update ports indexes
	index_IsPicSlcLcu += 1;
	index_PicSize += 2;
	read_end_PicSize();
	index_LcuSizeMax += 1;
	index_DBFDisable += 1;
	index_SyntaxElem += 4;
	read_end_SyntaxElem();

	rate_IsPicSlcLcu += 1;
	rate_PicSize += 2;
	rate_LcuSizeMax += 1;
	rate_DBFDisable += 1;
	rate_SyntaxElem += 4;
}
static void isNewSlc_aligned() {

	u8 isNewPicSlcLcu;
	u16 picWidthInPix;
	u16 picHeightInPix;
	u8 log2_lcuSz;
	i32 disableFlag;
	i8 betaOff;
	i8 tcOff;
	i8 qpUOff;
	i8 qpVOff;

	isNewPicSlcLcu = tokens_IsPicSlcLcu[(index_IsPicSlcLcu + (0)) % SIZE_IsPicSlcLcu];
	picWidthInPix = tokens_PicSize[(index_PicSize % SIZE_PicSize) + (0)];
	picHeightInPix = tokens_PicSize[(index_PicSize % SIZE_PicSize) + (1)];
	log2_lcuSz = tokens_LcuSizeMax[(index_LcuSizeMax + (0)) % SIZE_LcuSizeMax];
	disableFlag = tokens_DBFDisable[(index_DBFDisable + (0)) % SIZE_DBFDisable];
	betaOff = tokens_SyntaxElem[(index_SyntaxElem % SIZE_SyntaxElem) + (0)];
	tcOff = tokens_SyntaxElem[(index_SyntaxElem % SIZE_SyntaxElem) + (1)];
	qpUOff = tokens_SyntaxElem[(index_SyntaxElem % SIZE_SyntaxElem) + (2)];
	qpVOff = tokens_SyntaxElem[(index_SyntaxElem % SIZE_SyntaxElem) + (3)];
	disDbf = disableFlag;
	betaOffset = betaOff;
	tcOffset = tcOff;
	qpChrOff[0] = qpUOff;
	qpChrOff[1] = qpVOff;

	// Update ports indexes
	index_IsPicSlcLcu += 1;
	index_PicSize += 2;
	read_end_PicSize();
	index_LcuSizeMax += 1;
	index_DBFDisable += 1;
	index_SyntaxElem += 4;
	read_end_SyntaxElem();

	rate_IsPicSlcLcu += 1;
	rate_PicSize += 2;
	rate_LcuSizeMax += 1;
	rate_DBFDisable += 1;
	rate_SyntaxElem += 4;
}
static i32 isSchedulable_isNewPict() {
	i32 result;
	u8 isNewPicSlcLcu;
	u8 local_NEW_PIC;

	isNewPicSlcLcu = tokens_IsPicSlcLcu[(index_IsPicSlcLcu + (0)) % SIZE_IsPicSlcLcu];
	local_NEW_PIC = HevcDecoder_DBFilter_DeblockFilt_NEW_PIC;
	result = isNewPicSlcLcu == local_NEW_PIC;
	return result;
}

static void isNewPict() {

	u8 isNewPicSlcLcu;
	u16 picWidthInPix;
	u16 picHeightInPix;
	u8 log2lcuSz;
	i32 disableFlag;
	i8 betaOff;
	i8 tcOff;
	i8 qpUOff;
	i8 qpVOff;
	u8 local_log2lcuSizeMax;
	u8 local_lcuSizeMax;
	u16 tmp_numTokenPerLcu;

	isNewPicSlcLcu = tokens_IsPicSlcLcu[(index_IsPicSlcLcu + (0)) % SIZE_IsPicSlcLcu];
	picWidthInPix = tokens_PicSize[(index_PicSize + (0)) % SIZE_PicSize];
	picHeightInPix = tokens_PicSize[(index_PicSize + (1)) % SIZE_PicSize];
	log2lcuSz = tokens_LcuSizeMax[(index_LcuSizeMax + (0)) % SIZE_LcuSizeMax];
	disableFlag = tokens_DBFDisable[(index_DBFDisable + (0)) % SIZE_DBFDisable];
	betaOff = tokens_SyntaxElem[(index_SyntaxElem + (0)) % SIZE_SyntaxElem];
	tcOff = tokens_SyntaxElem[(index_SyntaxElem + (1)) % SIZE_SyntaxElem];
	qpUOff = tokens_SyntaxElem[(index_SyntaxElem + (2)) % SIZE_SyntaxElem];
	qpVOff = tokens_SyntaxElem[(index_SyntaxElem + (3)) % SIZE_SyntaxElem];
	log2lcuSizeMax = log2lcuSz;
	local_log2lcuSizeMax = log2lcuSizeMax;
	lcuSizeMax = 1 << local_log2lcuSizeMax;
	local_lcuSizeMax = lcuSizeMax;
	local_lcuSizeMax = lcuSizeMax;
	numPartition = local_lcuSizeMax * local_lcuSizeMax / 16;
	local_lcuSizeMax = lcuSizeMax;
	local_lcuSizeMax = lcuSizeMax;
	numTokenPerLcu[0] = local_lcuSizeMax * local_lcuSizeMax;
	tmp_numTokenPerLcu = numTokenPerLcu[0];
	numTokenPerLcu[1] = tmp_numTokenPerLcu >> 2;
	disDbf = disableFlag;
	picSize[0] = picWidthInPix;
	picSize[1] = picHeightInPix;
	xIdx = 0;
	yIdx = 0;
	xAddrHor = -1;
	tileIdx = 0;
	betaOffset = betaOff;
	tcOffset = tcOff;
	qpChrOff[0] = qpUOff;
	qpChrOff[1] = qpVOff;

	// Update ports indexes
	index_IsPicSlcLcu += 1;
	index_PicSize += 2;
	read_end_PicSize();
	index_LcuSizeMax += 1;
	index_DBFDisable += 1;
	index_SyntaxElem += 4;
	read_end_SyntaxElem();

	rate_IsPicSlcLcu += 1;
	rate_PicSize += 2;
	rate_LcuSizeMax += 1;
	rate_DBFDisable += 1;
	rate_SyntaxElem += 4;
}
static void isNewPict_aligned() {

	u8 isNewPicSlcLcu;
	u16 picWidthInPix;
	u16 picHeightInPix;
	u8 log2lcuSz;
	i32 disableFlag;
	i8 betaOff;
	i8 tcOff;
	i8 qpUOff;
	i8 qpVOff;
	u8 local_log2lcuSizeMax;
	u8 local_lcuSizeMax;
	u16 tmp_numTokenPerLcu;

	isNewPicSlcLcu = tokens_IsPicSlcLcu[(index_IsPicSlcLcu + (0)) % SIZE_IsPicSlcLcu];
	picWidthInPix = tokens_PicSize[(index_PicSize % SIZE_PicSize) + (0)];
	picHeightInPix = tokens_PicSize[(index_PicSize % SIZE_PicSize) + (1)];
	log2lcuSz = tokens_LcuSizeMax[(index_LcuSizeMax + (0)) % SIZE_LcuSizeMax];
	disableFlag = tokens_DBFDisable[(index_DBFDisable + (0)) % SIZE_DBFDisable];
	betaOff = tokens_SyntaxElem[(index_SyntaxElem % SIZE_SyntaxElem) + (0)];
	tcOff = tokens_SyntaxElem[(index_SyntaxElem % SIZE_SyntaxElem) + (1)];
	qpUOff = tokens_SyntaxElem[(index_SyntaxElem % SIZE_SyntaxElem) + (2)];
	qpVOff = tokens_SyntaxElem[(index_SyntaxElem % SIZE_SyntaxElem) + (3)];
	log2lcuSizeMax = log2lcuSz;
	local_log2lcuSizeMax = log2lcuSizeMax;
	lcuSizeMax = 1 << local_log2lcuSizeMax;
	local_lcuSizeMax = lcuSizeMax;
	local_lcuSizeMax = lcuSizeMax;
	numPartition = local_lcuSizeMax * local_lcuSizeMax / 16;
	local_lcuSizeMax = lcuSizeMax;
	local_lcuSizeMax = lcuSizeMax;
	numTokenPerLcu[0] = local_lcuSizeMax * local_lcuSizeMax;
	tmp_numTokenPerLcu = numTokenPerLcu[0];
	numTokenPerLcu[1] = tmp_numTokenPerLcu >> 2;
	disDbf = disableFlag;
	picSize[0] = picWidthInPix;
	picSize[1] = picHeightInPix;
	xIdx = 0;
	yIdx = 0;
	xAddrHor = -1;
	tileIdx = 0;
	betaOffset = betaOff;
	tcOffset = tcOff;
	qpChrOff[0] = qpUOff;
	qpChrOff[1] = qpVOff;

	// Update ports indexes
	index_IsPicSlcLcu += 1;
	index_PicSize += 2;
	read_end_PicSize();
	index_LcuSizeMax += 1;
	index_DBFDisable += 1;
	index_SyntaxElem += 4;
	read_end_SyntaxElem();

	rate_IsPicSlcLcu += 1;
	rate_PicSize += 2;
	rate_LcuSizeMax += 1;
	rate_DBFDisable += 1;
	rate_SyntaxElem += 4;
}
static i32 isSchedulable_getNumTiles() {
	i32 result;

	result = 1;
	return result;
}

static void getNumTiles() {

	u16 valNumTiles;

	valNumTiles = tokens_TilesCoord[(index_TilesCoord + (0)) % SIZE_TilesCoord];
	numTiles = valNumTiles;
	iLoop = 0;

	// Update ports indexes
	index_TilesCoord += 1;

	rate_TilesCoord += 1;
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
	tilesBegSamp[local_iLoop][0] = tmp_TilesCoord;
	tmp_TilesCoord0 = tokens_TilesCoord[(index_TilesCoord + (1)) % SIZE_TilesCoord];
	tilesBegSamp[local_iLoop][1] = tmp_TilesCoord0;
	local_iLoop = iLoop;
	tmp_TilesCoord1 = tokens_TilesCoord[(index_TilesCoord + (2)) % SIZE_TilesCoord];
	tilesEndSamp[local_iLoop][0] = tmp_TilesCoord1;
	tmp_TilesCoord2 = tokens_TilesCoord[(index_TilesCoord + (3)) % SIZE_TilesCoord];
	tilesEndSamp[local_iLoop][1] = tmp_TilesCoord2;
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
	tilesBegSamp[local_iLoop][0] = tmp_TilesCoord;
	tmp_TilesCoord0 = tokens_TilesCoord[(index_TilesCoord % SIZE_TilesCoord) + (1)];
	tilesBegSamp[local_iLoop][1] = tmp_TilesCoord0;
	local_iLoop = iLoop;
	tmp_TilesCoord1 = tokens_TilesCoord[(index_TilesCoord % SIZE_TilesCoord) + (2)];
	tilesEndSamp[local_iLoop][0] = tmp_TilesCoord1;
	tmp_TilesCoord2 = tokens_TilesCoord[(index_TilesCoord % SIZE_TilesCoord) + (3)];
	tilesEndSamp[local_iLoop][1] = tmp_TilesCoord2;
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
static i32 isSchedulable_getCuPix_launch_pict() {
	i32 result;
	u8 isLcu;
	u16 local_tileIdx;
	u16 local_numTiles;
	u16 local_yIdx;
	u16 tmp_picSize;
	u8 local_lcuSizeMax;
	u16 local_xIdx;
	u16 tmp_picSize0;
	u8 local_NEW_LCU;

	isLcu = tokens_IsPicSlcLcu[(index_IsPicSlcLcu + (0)) % SIZE_IsPicSlcLcu];
	local_tileIdx = tileIdx;
	local_numTiles = numTiles;
	local_yIdx = yIdx;
	tmp_picSize = picSize[1];
	local_lcuSizeMax = lcuSizeMax;
	local_xIdx = xIdx;
	tmp_picSize0 = picSize[0];
	local_lcuSizeMax = lcuSizeMax;
	local_NEW_LCU = HevcDecoder_DBFilter_DeblockFilt_NEW_LCU;
	result = local_tileIdx < local_numTiles && local_yIdx < tmp_picSize - local_lcuSizeMax && local_xIdx < tmp_picSize0 - local_lcuSizeMax && isLcu == local_NEW_LCU;
	return result;
}

static void getCuPix_launch_pict() {

	u8 isLcu;
	u16 local_xIdx;
	u16 local_yIdx;

	isLcu = tokens_IsPicSlcLcu[(index_IsPicSlcLcu + (0)) % SIZE_IsPicSlcLcu];
	local_xIdx = xIdx;
	xAddrVert = local_xIdx;
	local_yIdx = yIdx;
	yAddrVert = local_yIdx;
	blkIdx = 0;

	// Update ports indexes
	index_IsPicSlcLcu += 1;

	rate_IsPicSlcLcu += 1;
}
static i32 isSchedulable_getCuPix_launch_getPart_isHorVer() {
	i32 result;
	u16 local_blkIdx;
	u16 local_numPartition;

	local_blkIdx = blkIdx;
	local_numPartition = numPartition;
	local_blkIdx = blkIdx;
	result = local_blkIdx < local_numPartition && (local_blkIdx & 3) == 0;
	return result;
}

static void getCuPix_launch_getPart_isHorVer() {

	u8 bsVer;
	u8 bsHor;
	i8 qp;
	u16 coord[2];
	i32 local_FILT_VERT_EDGES;
	u8 local_SampleIn[24];
	i32 idx_SampleIn;
	u8 local_SampleIn0;
	u16 local_blkIdx;
	u16 local_xIdx;
	u16 tmp_coord;
	u16 local_yIdx;
	u16 tmp_coord0;
	u16 tmp_coord1;
	u16 tmp_coord2;
	u8 local_log2lcuSizeMax;

	bsVer = tokens_BsVer[(index_BsVer + (0)) % SIZE_BsVer];
	bsHor = tokens_BsHor[(index_BsHor + (0)) % SIZE_BsHor];
	qp = tokens_Qp[(index_Qp + (0)) % SIZE_Qp];
	local_FILT_VERT_EDGES = FILT_VERT_EDGES;
	if (local_FILT_VERT_EDGES) {
		idx_SampleIn = 0;
		while (idx_SampleIn < 24) {
			local_SampleIn0 = tokens_SampleIn[(index_SampleIn + (idx_SampleIn)) % SIZE_SampleIn];
			local_SampleIn[idx_SampleIn] = local_SampleIn0;
			idx_SampleIn = idx_SampleIn + 1;
		}
		saveRasterScanCu(local_SampleIn);
	}
	local_blkIdx = blkIdx;
	HevcDecoder_DBFilter_DeblockFilt_zScanToAbsCoord(local_blkIdx, coord);
	local_xIdx = xIdx;
	tmp_coord = coord[0];
	coord[0] = local_xIdx + tmp_coord;
	local_yIdx = yIdx;
	tmp_coord0 = coord[1];
	coord[1] = local_yIdx + tmp_coord0;
	tmp_coord1 = coord[0];
	tmp_coord2 = coord[1];
	qpTab[tmp_coord1 >> 2][tmp_coord2 >> 2] = qp;
	local_blkIdx = blkIdx;
	bSTableVert[local_blkIdx] = bsVer;
	local_xIdx = xIdx;
	local_log2lcuSizeMax = log2lcuSizeMax;
	local_yIdx = yIdx;
	local_log2lcuSizeMax = log2lcuSizeMax;
	local_blkIdx = blkIdx;
	bSTableHoriz[local_xIdx >> local_log2lcuSizeMax][local_yIdx >> local_log2lcuSizeMax][local_blkIdx] = bsHor;
	local_blkIdx = blkIdx;
	blkIdx = local_blkIdx + 1;

	// Update ports indexes
	index_BsVer += 1;
	index_BsHor += 1;
	index_Qp += 1;
	index_SampleIn += 24;
	read_end_SampleIn();

	rate_BsVer += 1;
	rate_BsHor += 1;
	rate_Qp += 1;
	rate_SampleIn += 24;
}
static void getCuPix_launch_getPart_isHorVer_aligned() {

	u8 bsVer;
	u8 bsHor;
	i8 qp;
	u16 coord[2];
	i32 local_FILT_VERT_EDGES;
	u8 local_SampleIn[24];
	i32 idx_SampleIn;
	u8 local_SampleIn0;
	u16 local_blkIdx;
	u16 local_xIdx;
	u16 tmp_coord;
	u16 local_yIdx;
	u16 tmp_coord0;
	u16 tmp_coord1;
	u16 tmp_coord2;
	u8 local_log2lcuSizeMax;

	bsVer = tokens_BsVer[(index_BsVer + (0)) % SIZE_BsVer];
	bsHor = tokens_BsHor[(index_BsHor + (0)) % SIZE_BsHor];
	qp = tokens_Qp[(index_Qp + (0)) % SIZE_Qp];
	local_FILT_VERT_EDGES = FILT_VERT_EDGES;
	if (local_FILT_VERT_EDGES) {
		idx_SampleIn = 0;
		saveRasterScanCu(&tokens_SampleIn[index_SampleIn % SIZE_SampleIn]);
	}
	local_blkIdx = blkIdx;
	HevcDecoder_DBFilter_DeblockFilt_zScanToAbsCoord(local_blkIdx, coord);
	local_xIdx = xIdx;
	tmp_coord = coord[0];
	coord[0] = local_xIdx + tmp_coord;
	local_yIdx = yIdx;
	tmp_coord0 = coord[1];
	coord[1] = local_yIdx + tmp_coord0;
	tmp_coord1 = coord[0];
	tmp_coord2 = coord[1];
	qpTab[tmp_coord1 >> 2][tmp_coord2 >> 2] = qp;
	local_blkIdx = blkIdx;
	bSTableVert[local_blkIdx] = bsVer;
	local_xIdx = xIdx;
	local_log2lcuSizeMax = log2lcuSizeMax;
	local_yIdx = yIdx;
	local_log2lcuSizeMax = log2lcuSizeMax;
	local_blkIdx = blkIdx;
	bSTableHoriz[local_xIdx >> local_log2lcuSizeMax][local_yIdx >> local_log2lcuSizeMax][local_blkIdx] = bsHor;
	local_blkIdx = blkIdx;
	blkIdx = local_blkIdx + 1;

	// Update ports indexes
	index_BsVer += 1;
	index_BsHor += 1;
	index_Qp += 1;
	index_SampleIn += 24;
	read_end_SampleIn();

	rate_BsVer += 1;
	rate_BsHor += 1;
	rate_Qp += 1;
	rate_SampleIn += 24;
}
static i32 isSchedulable_getCuPix_launch_getPart_isHor() {
	i32 result;
	u16 local_blkIdx;
	u16 local_numPartition;

	local_blkIdx = blkIdx;
	local_numPartition = numPartition;
	local_blkIdx = blkIdx;
	result = local_blkIdx < local_numPartition && (local_blkIdx & 3) < 2;
	return result;
}

static void getCuPix_launch_getPart_isHor() {

	u8 bsHor;
	i8 qp;
	u16 coord[2];
	i32 local_FILT_VERT_EDGES;
	u8 local_SampleIn[24];
	i32 idx_SampleIn;
	u8 local_SampleIn0;
	u16 local_blkIdx;
	u16 local_xIdx;
	u16 tmp_coord;
	u16 local_yIdx;
	u16 tmp_coord0;
	u16 tmp_coord1;
	u16 tmp_coord2;
	u8 local_log2lcuSizeMax;

	bsHor = tokens_BsHor[(index_BsHor + (0)) % SIZE_BsHor];
	qp = tokens_Qp[(index_Qp + (0)) % SIZE_Qp];
	local_FILT_VERT_EDGES = FILT_VERT_EDGES;
	if (local_FILT_VERT_EDGES) {
		idx_SampleIn = 0;
		while (idx_SampleIn < 24) {
			local_SampleIn0 = tokens_SampleIn[(index_SampleIn + (idx_SampleIn)) % SIZE_SampleIn];
			local_SampleIn[idx_SampleIn] = local_SampleIn0;
			idx_SampleIn = idx_SampleIn + 1;
		}
		saveRasterScanCu(local_SampleIn);
	}
	local_blkIdx = blkIdx;
	HevcDecoder_DBFilter_DeblockFilt_zScanToAbsCoord(local_blkIdx, coord);
	local_xIdx = xIdx;
	tmp_coord = coord[0];
	coord[0] = local_xIdx + tmp_coord;
	local_yIdx = yIdx;
	tmp_coord0 = coord[1];
	coord[1] = local_yIdx + tmp_coord0;
	tmp_coord1 = coord[0];
	tmp_coord2 = coord[1];
	qpTab[tmp_coord1 >> 2][tmp_coord2 >> 2] = qp;
	local_xIdx = xIdx;
	local_log2lcuSizeMax = log2lcuSizeMax;
	local_yIdx = yIdx;
	local_log2lcuSizeMax = log2lcuSizeMax;
	local_blkIdx = blkIdx;
	bSTableHoriz[local_xIdx >> local_log2lcuSizeMax][local_yIdx >> local_log2lcuSizeMax][local_blkIdx] = bsHor;
	local_blkIdx = blkIdx;
	blkIdx = local_blkIdx + 1;

	// Update ports indexes
	index_BsHor += 1;
	index_Qp += 1;
	index_SampleIn += 24;
	read_end_SampleIn();

	rate_BsHor += 1;
	rate_Qp += 1;
	rate_SampleIn += 24;
}
static void getCuPix_launch_getPart_isHor_aligned() {

	u8 bsHor;
	i8 qp;
	u16 coord[2];
	i32 local_FILT_VERT_EDGES;
	u8 local_SampleIn[24];
	i32 idx_SampleIn;
	u8 local_SampleIn0;
	u16 local_blkIdx;
	u16 local_xIdx;
	u16 tmp_coord;
	u16 local_yIdx;
	u16 tmp_coord0;
	u16 tmp_coord1;
	u16 tmp_coord2;
	u8 local_log2lcuSizeMax;

	bsHor = tokens_BsHor[(index_BsHor + (0)) % SIZE_BsHor];
	qp = tokens_Qp[(index_Qp + (0)) % SIZE_Qp];
	local_FILT_VERT_EDGES = FILT_VERT_EDGES;
	if (local_FILT_VERT_EDGES) {
		idx_SampleIn = 0;
		saveRasterScanCu(&tokens_SampleIn[index_SampleIn % SIZE_SampleIn]);
	}
	local_blkIdx = blkIdx;
	HevcDecoder_DBFilter_DeblockFilt_zScanToAbsCoord(local_blkIdx, coord);
	local_xIdx = xIdx;
	tmp_coord = coord[0];
	coord[0] = local_xIdx + tmp_coord;
	local_yIdx = yIdx;
	tmp_coord0 = coord[1];
	coord[1] = local_yIdx + tmp_coord0;
	tmp_coord1 = coord[0];
	tmp_coord2 = coord[1];
	qpTab[tmp_coord1 >> 2][tmp_coord2 >> 2] = qp;
	local_xIdx = xIdx;
	local_log2lcuSizeMax = log2lcuSizeMax;
	local_yIdx = yIdx;
	local_log2lcuSizeMax = log2lcuSizeMax;
	local_blkIdx = blkIdx;
	bSTableHoriz[local_xIdx >> local_log2lcuSizeMax][local_yIdx >> local_log2lcuSizeMax][local_blkIdx] = bsHor;
	local_blkIdx = blkIdx;
	blkIdx = local_blkIdx + 1;

	// Update ports indexes
	index_BsHor += 1;
	index_Qp += 1;
	index_SampleIn += 24;
	read_end_SampleIn();

	rate_BsHor += 1;
	rate_Qp += 1;
	rate_SampleIn += 24;
}
static i32 isSchedulable_getCuPix_launch_getPart_isVer() {
	i32 result;
	u16 local_blkIdx;
	u16 local_numPartition;

	local_blkIdx = blkIdx;
	local_numPartition = numPartition;
	local_blkIdx = blkIdx;
	result = local_blkIdx < local_numPartition && (local_blkIdx & 1) == 0;
	return result;
}

static void getCuPix_launch_getPart_isVer() {

	u8 bsVer;
	i8 qp;
	u16 coord[2];
	i32 local_FILT_VERT_EDGES;
	u8 local_SampleIn[24];
	i32 idx_SampleIn;
	u8 local_SampleIn0;
	u16 local_blkIdx;
	u16 local_xIdx;
	u16 tmp_coord;
	u16 local_yIdx;
	u16 tmp_coord0;
	u16 tmp_coord1;
	u16 tmp_coord2;

	bsVer = tokens_BsVer[(index_BsVer + (0)) % SIZE_BsVer];
	qp = tokens_Qp[(index_Qp + (0)) % SIZE_Qp];
	local_FILT_VERT_EDGES = FILT_VERT_EDGES;
	if (local_FILT_VERT_EDGES) {
		idx_SampleIn = 0;
		while (idx_SampleIn < 24) {
			local_SampleIn0 = tokens_SampleIn[(index_SampleIn + (idx_SampleIn)) % SIZE_SampleIn];
			local_SampleIn[idx_SampleIn] = local_SampleIn0;
			idx_SampleIn = idx_SampleIn + 1;
		}
		saveRasterScanCu(local_SampleIn);
	}
	local_blkIdx = blkIdx;
	HevcDecoder_DBFilter_DeblockFilt_zScanToAbsCoord(local_blkIdx, coord);
	local_xIdx = xIdx;
	tmp_coord = coord[0];
	coord[0] = local_xIdx + tmp_coord;
	local_yIdx = yIdx;
	tmp_coord0 = coord[1];
	coord[1] = local_yIdx + tmp_coord0;
	tmp_coord1 = coord[0];
	tmp_coord2 = coord[1];
	qpTab[tmp_coord1 >> 2][tmp_coord2 >> 2] = qp;
	local_blkIdx = blkIdx;
	bSTableVert[local_blkIdx] = bsVer;
	local_blkIdx = blkIdx;
	blkIdx = local_blkIdx + 1;

	// Update ports indexes
	index_BsVer += 1;
	index_Qp += 1;
	index_SampleIn += 24;
	read_end_SampleIn();

	rate_BsVer += 1;
	rate_Qp += 1;
	rate_SampleIn += 24;
}
static void getCuPix_launch_getPart_isVer_aligned() {

	u8 bsVer;
	i8 qp;
	u16 coord[2];
	i32 local_FILT_VERT_EDGES;
	u8 local_SampleIn[24];
	i32 idx_SampleIn;
	u8 local_SampleIn0;
	u16 local_blkIdx;
	u16 local_xIdx;
	u16 tmp_coord;
	u16 local_yIdx;
	u16 tmp_coord0;
	u16 tmp_coord1;
	u16 tmp_coord2;

	bsVer = tokens_BsVer[(index_BsVer + (0)) % SIZE_BsVer];
	qp = tokens_Qp[(index_Qp + (0)) % SIZE_Qp];
	local_FILT_VERT_EDGES = FILT_VERT_EDGES;
	if (local_FILT_VERT_EDGES) {
		idx_SampleIn = 0;
		saveRasterScanCu(&tokens_SampleIn[index_SampleIn % SIZE_SampleIn]);
	}
	local_blkIdx = blkIdx;
	HevcDecoder_DBFilter_DeblockFilt_zScanToAbsCoord(local_blkIdx, coord);
	local_xIdx = xIdx;
	tmp_coord = coord[0];
	coord[0] = local_xIdx + tmp_coord;
	local_yIdx = yIdx;
	tmp_coord0 = coord[1];
	coord[1] = local_yIdx + tmp_coord0;
	tmp_coord1 = coord[0];
	tmp_coord2 = coord[1];
	qpTab[tmp_coord1 >> 2][tmp_coord2 >> 2] = qp;
	local_blkIdx = blkIdx;
	bSTableVert[local_blkIdx] = bsVer;
	local_blkIdx = blkIdx;
	blkIdx = local_blkIdx + 1;

	// Update ports indexes
	index_BsVer += 1;
	index_Qp += 1;
	index_SampleIn += 24;
	read_end_SampleIn();

	rate_BsVer += 1;
	rate_Qp += 1;
	rate_SampleIn += 24;
}
static i32 isSchedulable_getCuPix_launch_getPart_qp() {
	i32 result;
	u16 local_blkIdx;
	u16 local_numPartition;

	local_blkIdx = blkIdx;
	local_numPartition = numPartition;
	local_blkIdx = blkIdx;
	result = local_blkIdx < local_numPartition && (local_blkIdx & 3) == 3;
	return result;
}

static void getCuPix_launch_getPart_qp() {

	i8 qp;
	u16 coord[2];
	i32 local_FILT_VERT_EDGES;
	u8 local_SampleIn[24];
	i32 idx_SampleIn;
	u8 local_SampleIn0;
	u16 local_blkIdx;
	u16 local_xIdx;
	u16 tmp_coord;
	u16 local_yIdx;
	u16 tmp_coord0;
	u16 tmp_coord1;
	u16 tmp_coord2;

	qp = tokens_Qp[(index_Qp + (0)) % SIZE_Qp];
	local_FILT_VERT_EDGES = FILT_VERT_EDGES;
	if (local_FILT_VERT_EDGES) {
		idx_SampleIn = 0;
		while (idx_SampleIn < 24) {
			local_SampleIn0 = tokens_SampleIn[(index_SampleIn + (idx_SampleIn)) % SIZE_SampleIn];
			local_SampleIn[idx_SampleIn] = local_SampleIn0;
			idx_SampleIn = idx_SampleIn + 1;
		}
		saveRasterScanCu(local_SampleIn);
	}
	local_blkIdx = blkIdx;
	HevcDecoder_DBFilter_DeblockFilt_zScanToAbsCoord(local_blkIdx, coord);
	local_xIdx = xIdx;
	tmp_coord = coord[0];
	coord[0] = local_xIdx + tmp_coord;
	local_yIdx = yIdx;
	tmp_coord0 = coord[1];
	coord[1] = local_yIdx + tmp_coord0;
	tmp_coord1 = coord[0];
	tmp_coord2 = coord[1];
	qpTab[tmp_coord1 >> 2][tmp_coord2 >> 2] = qp;
	local_blkIdx = blkIdx;
	blkIdx = local_blkIdx + 1;

	// Update ports indexes
	index_Qp += 1;
	index_SampleIn += 24;
	read_end_SampleIn();

	rate_Qp += 1;
	rate_SampleIn += 24;
}
static void getCuPix_launch_getPart_qp_aligned() {

	i8 qp;
	u16 coord[2];
	i32 local_FILT_VERT_EDGES;
	u8 local_SampleIn[24];
	i32 idx_SampleIn;
	u8 local_SampleIn0;
	u16 local_blkIdx;
	u16 local_xIdx;
	u16 tmp_coord;
	u16 local_yIdx;
	u16 tmp_coord0;
	u16 tmp_coord1;
	u16 tmp_coord2;

	qp = tokens_Qp[(index_Qp + (0)) % SIZE_Qp];
	local_FILT_VERT_EDGES = FILT_VERT_EDGES;
	if (local_FILT_VERT_EDGES) {
		idx_SampleIn = 0;
		saveRasterScanCu(&tokens_SampleIn[index_SampleIn % SIZE_SampleIn]);
	}
	local_blkIdx = blkIdx;
	HevcDecoder_DBFilter_DeblockFilt_zScanToAbsCoord(local_blkIdx, coord);
	local_xIdx = xIdx;
	tmp_coord = coord[0];
	coord[0] = local_xIdx + tmp_coord;
	local_yIdx = yIdx;
	tmp_coord0 = coord[1];
	coord[1] = local_yIdx + tmp_coord0;
	tmp_coord1 = coord[0];
	tmp_coord2 = coord[1];
	qpTab[tmp_coord1 >> 2][tmp_coord2 >> 2] = qp;
	local_blkIdx = blkIdx;
	blkIdx = local_blkIdx + 1;

	// Update ports indexes
	index_Qp += 1;
	index_SampleIn += 24;
	read_end_SampleIn();

	rate_Qp += 1;
	rate_SampleIn += 24;
}
static i32 isSchedulable_getCuPix_launch_getPartDone() {
	i32 result;
	u16 local_blkIdx;
	u16 local_numPartition;

	local_blkIdx = blkIdx;
	local_numPartition = numPartition;
	result = local_blkIdx == local_numPartition;
	return result;
}

static void getCuPix_launch_getPartDone() {


	computeNextLcuAddr();

	// Update ports indexes

}
static i32 isSchedulable_getCuPix_launch_lastColOrRow_vert() {
	i32 result;
	u8 isLcu;
	u16 local_xIdx;
	u16 tmp_picSize;
	u8 local_lcuSizeMax;
	u16 local_yIdx;
	u16 tmp_picSize0;
	i32 local_FILT_VERT_EDGES;
	u8 local_NEW_LCU;

	isLcu = tokens_IsPicSlcLcu[(index_IsPicSlcLcu + (0)) % SIZE_IsPicSlcLcu];
	local_xIdx = xIdx;
	tmp_picSize = picSize[0];
	local_lcuSizeMax = lcuSizeMax;
	local_yIdx = yIdx;
	tmp_picSize0 = picSize[1];
	local_lcuSizeMax = lcuSizeMax;
	local_FILT_VERT_EDGES = FILT_VERT_EDGES;
	local_NEW_LCU = HevcDecoder_DBFilter_DeblockFilt_NEW_LCU;
	result = (local_xIdx >= tmp_picSize - local_lcuSizeMax || local_yIdx >= tmp_picSize0 - local_lcuSizeMax) && local_FILT_VERT_EDGES && isLcu == local_NEW_LCU;
	return result;
}

static void getCuPix_launch_lastColOrRow_vert() {

	u8 isLcu;
	u16 local_xIdx;
	u16 local_yIdx;
	u16 tmp_pixAddr;
	u16 local_xAddrVert;
	u16 tmp_pixAddr0;
	u16 local_yAddrVert;

	isLcu = tokens_IsPicSlcLcu[(index_IsPicSlcLcu + (0)) % SIZE_IsPicSlcLcu];
	local_xIdx = xIdx;
	xAddrVert = local_xIdx;
	local_yIdx = yIdx;
	yAddrVert = local_yIdx;
	blkIdx = 0;
	HevcDecoder_DBFilter_DeblockFilt_zScanToAbsCoord(0, pixAddr);
	tmp_pixAddr = pixAddr[0];
	local_xAddrVert = xAddrVert;
	pixAddr[0] = tmp_pixAddr + local_xAddrVert;
	tmp_pixAddr0 = pixAddr[1];
	local_yAddrVert = yAddrVert;
	pixAddr[1] = tmp_pixAddr0 + local_yAddrVert;

	// Update ports indexes
	index_IsPicSlcLcu += 1;

	rate_IsPicSlcLcu += 1;
}
static i32 isSchedulable_getBlk_launch_isHorVer() {
	i32 result;
	u16 local_blkIdx;
	u16 local_numPartition;
	u16 tmp_pixAddr;
	u16 tmp_picSize;
	u16 tmp_pixAddr0;
	u16 tmp_picSize0;

	local_blkIdx = blkIdx;
	local_numPartition = numPartition;
	local_blkIdx = blkIdx;
	tmp_pixAddr = pixAddr[0];
	tmp_picSize = picSize[0];
	tmp_pixAddr0 = pixAddr[1];
	tmp_picSize0 = picSize[1];
	result = local_blkIdx < local_numPartition && (local_blkIdx & 3) == 0 && tmp_pixAddr < tmp_picSize && tmp_pixAddr0 < tmp_picSize0;
	return result;
}

static void getBlk_launch_isHorVer() {

	u8 bsHor;
	u8 bsVer;
	i8 qp;
	i32 y;
	i32 x;
	u16 tmp_pixAddr;
	u16 tmp_pixAddr0;
	u8 tmp_SampleIn;
	u16 tmp_pixAddr1;
	i32 local_PICT_WIDTH;
	u16 tmp_pixAddr2;
	u16 local_blkIdx;
	u16 local_xAddrVert;
	u8 local_log2lcuSizeMax;
	u16 local_yAddrVert;
	u16 tmp_pixAddr3;
	u16 tmp_pixAddr4;
	u32 comp;
	u32 y0;
	u32 x0;
	u16 tmp_pixAddr5;
	u16 tmp_pixAddr6;
	u8 tmp_SampleIn0;
	u16 tmp_pixAddr7;
	u16 tmp_pixAddr8;

	bsHor = tokens_BsHor[(index_BsHor + (0)) % SIZE_BsHor];
	bsVer = tokens_BsVer[(index_BsVer + (0)) % SIZE_BsVer];
	qp = tokens_Qp[(index_Qp + (0)) % SIZE_Qp];
	y = 0;
	while (y <= 3) {
		x = 0;
		while (x <= 3) {
			tmp_pixAddr = pixAddr[1];
			tmp_pixAddr0 = pixAddr[0];
			tmp_SampleIn = tokens_SampleIn[(index_SampleIn + (4 * y + x)) % SIZE_SampleIn];
			pictureBuffer[0][tmp_pixAddr + y][tmp_pixAddr0 + x] = tmp_SampleIn;
			x = x + 1;
		}
		y = y + 1;
	}
	tmp_pixAddr1 = pixAddr[0];
	local_PICT_WIDTH = HevcDecoder_DBFilter_DeblockFilt_PICT_WIDTH;
	tmp_pixAddr2 = pixAddr[1];
	qpTab[(tmp_pixAddr1 & local_PICT_WIDTH - 1) >> 2][tmp_pixAddr2 / 4] = qp;
	local_blkIdx = blkIdx;
	bSTableVert[local_blkIdx] = bsVer;
	local_xAddrVert = xAddrVert;
	local_log2lcuSizeMax = log2lcuSizeMax;
	local_yAddrVert = yAddrVert;
	local_log2lcuSizeMax = log2lcuSizeMax;
	local_blkIdx = blkIdx;
	bSTableHoriz[local_xAddrVert >> local_log2lcuSizeMax][local_yAddrVert >> local_log2lcuSizeMax][local_blkIdx] = bsHor;
	tmp_pixAddr3 = pixAddr[0];
	pixAddr[0] = tmp_pixAddr3 >> 1;
	tmp_pixAddr4 = pixAddr[1];
	pixAddr[1] = tmp_pixAddr4 >> 1;
	comp = 1;
	while (comp <= 2) {
		y0 = 0;
		while (y0 <= 1) {
			x0 = 0;
			while (x0 <= 1) {
				tmp_pixAddr5 = pixAddr[1];
				tmp_pixAddr6 = pixAddr[0];
				tmp_SampleIn0 = tokens_SampleIn[(index_SampleIn + (2 * y0 + x0 + 16 + 4 * (comp - 1))) % SIZE_SampleIn];
				pictureBuffer[comp][tmp_pixAddr5 + y0][tmp_pixAddr6 + x0] = tmp_SampleIn0;
				x0 = x0 + 1;
			}
			y0 = y0 + 1;
		}
		comp = comp + 1;
	}
	local_blkIdx = blkIdx;
	blkIdx = local_blkIdx + 1;
	local_blkIdx = blkIdx;
	HevcDecoder_DBFilter_DeblockFilt_zScanToAbsCoord(local_blkIdx, pixAddr);
	tmp_pixAddr7 = pixAddr[0];
	local_xAddrVert = xAddrVert;
	pixAddr[0] = tmp_pixAddr7 + local_xAddrVert;
	tmp_pixAddr8 = pixAddr[1];
	local_yAddrVert = yAddrVert;
	pixAddr[1] = tmp_pixAddr8 + local_yAddrVert;

	// Update ports indexes
	index_BsHor += 1;
	index_BsVer += 1;
	index_Qp += 1;
	index_SampleIn += 24;
	read_end_SampleIn();

	rate_BsHor += 1;
	rate_BsVer += 1;
	rate_Qp += 1;
	rate_SampleIn += 24;
}
static void getBlk_launch_isHorVer_aligned() {

	u8 bsHor;
	u8 bsVer;
	i8 qp;
	i32 y;
	i32 x;
	u16 tmp_pixAddr;
	u16 tmp_pixAddr0;
	u8 tmp_SampleIn;
	u16 tmp_pixAddr1;
	i32 local_PICT_WIDTH;
	u16 tmp_pixAddr2;
	u16 local_blkIdx;
	u16 local_xAddrVert;
	u8 local_log2lcuSizeMax;
	u16 local_yAddrVert;
	u16 tmp_pixAddr3;
	u16 tmp_pixAddr4;
	u32 comp;
	u32 y0;
	u32 x0;
	u16 tmp_pixAddr5;
	u16 tmp_pixAddr6;
	u8 tmp_SampleIn0;
	u16 tmp_pixAddr7;
	u16 tmp_pixAddr8;

	bsHor = tokens_BsHor[(index_BsHor + (0)) % SIZE_BsHor];
	bsVer = tokens_BsVer[(index_BsVer + (0)) % SIZE_BsVer];
	qp = tokens_Qp[(index_Qp + (0)) % SIZE_Qp];
	y = 0;
	while (y <= 3) {
		x = 0;
		while (x <= 3) {
			tmp_pixAddr = pixAddr[1];
			tmp_pixAddr0 = pixAddr[0];
			tmp_SampleIn = tokens_SampleIn[(index_SampleIn % SIZE_SampleIn) + (4 * y + x)];
			pictureBuffer[0][tmp_pixAddr + y][tmp_pixAddr0 + x] = tmp_SampleIn;
			x = x + 1;
		}
		y = y + 1;
	}
	tmp_pixAddr1 = pixAddr[0];
	local_PICT_WIDTH = HevcDecoder_DBFilter_DeblockFilt_PICT_WIDTH;
	tmp_pixAddr2 = pixAddr[1];
	qpTab[(tmp_pixAddr1 & local_PICT_WIDTH - 1) >> 2][tmp_pixAddr2 / 4] = qp;
	local_blkIdx = blkIdx;
	bSTableVert[local_blkIdx] = bsVer;
	local_xAddrVert = xAddrVert;
	local_log2lcuSizeMax = log2lcuSizeMax;
	local_yAddrVert = yAddrVert;
	local_log2lcuSizeMax = log2lcuSizeMax;
	local_blkIdx = blkIdx;
	bSTableHoriz[local_xAddrVert >> local_log2lcuSizeMax][local_yAddrVert >> local_log2lcuSizeMax][local_blkIdx] = bsHor;
	tmp_pixAddr3 = pixAddr[0];
	pixAddr[0] = tmp_pixAddr3 >> 1;
	tmp_pixAddr4 = pixAddr[1];
	pixAddr[1] = tmp_pixAddr4 >> 1;
	comp = 1;
	while (comp <= 2) {
		y0 = 0;
		while (y0 <= 1) {
			x0 = 0;
			while (x0 <= 1) {
				tmp_pixAddr5 = pixAddr[1];
				tmp_pixAddr6 = pixAddr[0];
				tmp_SampleIn0 = tokens_SampleIn[(index_SampleIn % SIZE_SampleIn) + (2 * y0 + x0 + 16 + 4 * (comp - 1))];
				pictureBuffer[comp][tmp_pixAddr5 + y0][tmp_pixAddr6 + x0] = tmp_SampleIn0;
				x0 = x0 + 1;
			}
			y0 = y0 + 1;
		}
		comp = comp + 1;
	}
	local_blkIdx = blkIdx;
	blkIdx = local_blkIdx + 1;
	local_blkIdx = blkIdx;
	HevcDecoder_DBFilter_DeblockFilt_zScanToAbsCoord(local_blkIdx, pixAddr);
	tmp_pixAddr7 = pixAddr[0];
	local_xAddrVert = xAddrVert;
	pixAddr[0] = tmp_pixAddr7 + local_xAddrVert;
	tmp_pixAddr8 = pixAddr[1];
	local_yAddrVert = yAddrVert;
	pixAddr[1] = tmp_pixAddr8 + local_yAddrVert;

	// Update ports indexes
	index_BsHor += 1;
	index_BsVer += 1;
	index_Qp += 1;
	index_SampleIn += 24;
	read_end_SampleIn();

	rate_BsHor += 1;
	rate_BsVer += 1;
	rate_Qp += 1;
	rate_SampleIn += 24;
}
static i32 isSchedulable_getBlk_launch_isHor() {
	i32 result;
	u16 local_blkIdx;
	u16 local_numPartition;
	u16 tmp_pixAddr;
	u16 tmp_picSize;
	u16 tmp_pixAddr0;
	u16 tmp_picSize0;

	local_blkIdx = blkIdx;
	local_numPartition = numPartition;
	local_blkIdx = blkIdx;
	tmp_pixAddr = pixAddr[0];
	tmp_picSize = picSize[0];
	tmp_pixAddr0 = pixAddr[1];
	tmp_picSize0 = picSize[1];
	result = local_blkIdx < local_numPartition && (local_blkIdx & 3) < 2 && tmp_pixAddr < tmp_picSize && tmp_pixAddr0 < tmp_picSize0;
	return result;
}

static void getBlk_launch_isHor() {

	u8 bsHor;
	i8 qp;
	i32 y;
	i32 x;
	u16 tmp_pixAddr;
	u16 tmp_pixAddr0;
	u8 tmp_SampleIn;
	u16 tmp_pixAddr1;
	u16 tmp_pixAddr2;
	i32 local_PICT_WIDTH;
	u16 local_xAddrVert;
	u8 local_log2lcuSizeMax;
	u16 local_yAddrVert;
	u16 local_blkIdx;
	u16 tmp_pixAddr3;
	u16 tmp_pixAddr4;
	u32 comp;
	u32 y0;
	u32 x0;
	u16 tmp_pixAddr5;
	u16 tmp_pixAddr6;
	u8 tmp_SampleIn0;
	u16 tmp_pixAddr7;
	u16 tmp_pixAddr8;

	bsHor = tokens_BsHor[(index_BsHor + (0)) % SIZE_BsHor];
	qp = tokens_Qp[(index_Qp + (0)) % SIZE_Qp];
	y = 0;
	while (y <= 3) {
		x = 0;
		while (x <= 3) {
			tmp_pixAddr = pixAddr[1];
			tmp_pixAddr0 = pixAddr[0];
			tmp_SampleIn = tokens_SampleIn[(index_SampleIn + (4 * y + x)) % SIZE_SampleIn];
			pictureBuffer[0][tmp_pixAddr + y][tmp_pixAddr0 + x] = tmp_SampleIn;
			x = x + 1;
		}
		y = y + 1;
	}
	tmp_pixAddr1 = pixAddr[0];
	tmp_pixAddr2 = pixAddr[1];
	local_PICT_WIDTH = HevcDecoder_DBFilter_DeblockFilt_PICT_WIDTH;
	qpTab[tmp_pixAddr1 / 4][(tmp_pixAddr2 & local_PICT_WIDTH - 1) >> 2] = qp;
	local_xAddrVert = xAddrVert;
	local_log2lcuSizeMax = log2lcuSizeMax;
	local_yAddrVert = yAddrVert;
	local_log2lcuSizeMax = log2lcuSizeMax;
	local_blkIdx = blkIdx;
	bSTableHoriz[local_xAddrVert >> local_log2lcuSizeMax][local_yAddrVert >> local_log2lcuSizeMax][local_blkIdx] = bsHor;
	tmp_pixAddr3 = pixAddr[0];
	pixAddr[0] = tmp_pixAddr3 >> 1;
	tmp_pixAddr4 = pixAddr[1];
	pixAddr[1] = tmp_pixAddr4 >> 1;
	comp = 1;
	while (comp <= 2) {
		y0 = 0;
		while (y0 <= 1) {
			x0 = 0;
			while (x0 <= 1) {
				tmp_pixAddr5 = pixAddr[1];
				tmp_pixAddr6 = pixAddr[0];
				tmp_SampleIn0 = tokens_SampleIn[(index_SampleIn + (2 * y0 + x0 + 16 + 4 * (comp - 1))) % SIZE_SampleIn];
				pictureBuffer[comp][tmp_pixAddr5 + y0][tmp_pixAddr6 + x0] = tmp_SampleIn0;
				x0 = x0 + 1;
			}
			y0 = y0 + 1;
		}
		comp = comp + 1;
	}
	local_blkIdx = blkIdx;
	blkIdx = local_blkIdx + 1;
	local_blkIdx = blkIdx;
	HevcDecoder_DBFilter_DeblockFilt_zScanToAbsCoord(local_blkIdx, pixAddr);
	tmp_pixAddr7 = pixAddr[0];
	local_xAddrVert = xAddrVert;
	pixAddr[0] = tmp_pixAddr7 + local_xAddrVert;
	tmp_pixAddr8 = pixAddr[1];
	local_yAddrVert = yAddrVert;
	pixAddr[1] = tmp_pixAddr8 + local_yAddrVert;

	// Update ports indexes
	index_BsHor += 1;
	index_Qp += 1;
	index_SampleIn += 24;
	read_end_SampleIn();

	rate_BsHor += 1;
	rate_Qp += 1;
	rate_SampleIn += 24;
}
static void getBlk_launch_isHor_aligned() {

	u8 bsHor;
	i8 qp;
	i32 y;
	i32 x;
	u16 tmp_pixAddr;
	u16 tmp_pixAddr0;
	u8 tmp_SampleIn;
	u16 tmp_pixAddr1;
	u16 tmp_pixAddr2;
	i32 local_PICT_WIDTH;
	u16 local_xAddrVert;
	u8 local_log2lcuSizeMax;
	u16 local_yAddrVert;
	u16 local_blkIdx;
	u16 tmp_pixAddr3;
	u16 tmp_pixAddr4;
	u32 comp;
	u32 y0;
	u32 x0;
	u16 tmp_pixAddr5;
	u16 tmp_pixAddr6;
	u8 tmp_SampleIn0;
	u16 tmp_pixAddr7;
	u16 tmp_pixAddr8;

	bsHor = tokens_BsHor[(index_BsHor + (0)) % SIZE_BsHor];
	qp = tokens_Qp[(index_Qp + (0)) % SIZE_Qp];
	y = 0;
	while (y <= 3) {
		x = 0;
		while (x <= 3) {
			tmp_pixAddr = pixAddr[1];
			tmp_pixAddr0 = pixAddr[0];
			tmp_SampleIn = tokens_SampleIn[(index_SampleIn % SIZE_SampleIn) + (4 * y + x)];
			pictureBuffer[0][tmp_pixAddr + y][tmp_pixAddr0 + x] = tmp_SampleIn;
			x = x + 1;
		}
		y = y + 1;
	}
	tmp_pixAddr1 = pixAddr[0];
	tmp_pixAddr2 = pixAddr[1];
	local_PICT_WIDTH = HevcDecoder_DBFilter_DeblockFilt_PICT_WIDTH;
	qpTab[tmp_pixAddr1 / 4][(tmp_pixAddr2 & local_PICT_WIDTH - 1) >> 2] = qp;
	local_xAddrVert = xAddrVert;
	local_log2lcuSizeMax = log2lcuSizeMax;
	local_yAddrVert = yAddrVert;
	local_log2lcuSizeMax = log2lcuSizeMax;
	local_blkIdx = blkIdx;
	bSTableHoriz[local_xAddrVert >> local_log2lcuSizeMax][local_yAddrVert >> local_log2lcuSizeMax][local_blkIdx] = bsHor;
	tmp_pixAddr3 = pixAddr[0];
	pixAddr[0] = tmp_pixAddr3 >> 1;
	tmp_pixAddr4 = pixAddr[1];
	pixAddr[1] = tmp_pixAddr4 >> 1;
	comp = 1;
	while (comp <= 2) {
		y0 = 0;
		while (y0 <= 1) {
			x0 = 0;
			while (x0 <= 1) {
				tmp_pixAddr5 = pixAddr[1];
				tmp_pixAddr6 = pixAddr[0];
				tmp_SampleIn0 = tokens_SampleIn[(index_SampleIn % SIZE_SampleIn) + (2 * y0 + x0 + 16 + 4 * (comp - 1))];
				pictureBuffer[comp][tmp_pixAddr5 + y0][tmp_pixAddr6 + x0] = tmp_SampleIn0;
				x0 = x0 + 1;
			}
			y0 = y0 + 1;
		}
		comp = comp + 1;
	}
	local_blkIdx = blkIdx;
	blkIdx = local_blkIdx + 1;
	local_blkIdx = blkIdx;
	HevcDecoder_DBFilter_DeblockFilt_zScanToAbsCoord(local_blkIdx, pixAddr);
	tmp_pixAddr7 = pixAddr[0];
	local_xAddrVert = xAddrVert;
	pixAddr[0] = tmp_pixAddr7 + local_xAddrVert;
	tmp_pixAddr8 = pixAddr[1];
	local_yAddrVert = yAddrVert;
	pixAddr[1] = tmp_pixAddr8 + local_yAddrVert;

	// Update ports indexes
	index_BsHor += 1;
	index_Qp += 1;
	index_SampleIn += 24;
	read_end_SampleIn();

	rate_BsHor += 1;
	rate_Qp += 1;
	rate_SampleIn += 24;
}
static i32 isSchedulable_getBlk_launch_isVer() {
	i32 result;
	u16 local_blkIdx;
	u16 local_numPartition;
	u16 tmp_pixAddr;
	u16 tmp_picSize;
	u16 tmp_pixAddr0;
	u16 tmp_picSize0;

	local_blkIdx = blkIdx;
	local_numPartition = numPartition;
	local_blkIdx = blkIdx;
	tmp_pixAddr = pixAddr[0];
	tmp_picSize = picSize[0];
	tmp_pixAddr0 = pixAddr[1];
	tmp_picSize0 = picSize[1];
	result = local_blkIdx < local_numPartition && (local_blkIdx & 1) == 0 && tmp_pixAddr < tmp_picSize && tmp_pixAddr0 < tmp_picSize0;
	return result;
}

static void getBlk_launch_isVer() {

	u8 bsVer;
	i8 qp;
	i32 y;
	i32 x;
	u16 tmp_pixAddr;
	u16 tmp_pixAddr0;
	u8 tmp_SampleIn;
	u16 tmp_pixAddr1;
	u16 tmp_pixAddr2;
	i32 local_PICT_WIDTH;
	u16 local_blkIdx;
	u16 tmp_pixAddr3;
	u16 tmp_pixAddr4;
	u32 comp;
	u32 y0;
	u32 x0;
	u16 tmp_pixAddr5;
	u16 tmp_pixAddr6;
	u8 tmp_SampleIn0;
	u16 tmp_pixAddr7;
	u16 local_xAddrVert;
	u16 tmp_pixAddr8;
	u16 local_yAddrVert;

	bsVer = tokens_BsVer[(index_BsVer + (0)) % SIZE_BsVer];
	qp = tokens_Qp[(index_Qp + (0)) % SIZE_Qp];
	y = 0;
	while (y <= 3) {
		x = 0;
		while (x <= 3) {
			tmp_pixAddr = pixAddr[1];
			tmp_pixAddr0 = pixAddr[0];
			tmp_SampleIn = tokens_SampleIn[(index_SampleIn + (4 * y + x)) % SIZE_SampleIn];
			pictureBuffer[0][tmp_pixAddr + y][tmp_pixAddr0 + x] = tmp_SampleIn;
			x = x + 1;
		}
		y = y + 1;
	}
	tmp_pixAddr1 = pixAddr[0];
	tmp_pixAddr2 = pixAddr[1];
	local_PICT_WIDTH = HevcDecoder_DBFilter_DeblockFilt_PICT_WIDTH;
	qpTab[tmp_pixAddr1 / 4][(tmp_pixAddr2 & local_PICT_WIDTH - 1) >> 2] = qp;
	local_blkIdx = blkIdx;
	bSTableVert[local_blkIdx] = bsVer;
	tmp_pixAddr3 = pixAddr[0];
	pixAddr[0] = tmp_pixAddr3 >> 1;
	tmp_pixAddr4 = pixAddr[1];
	pixAddr[1] = tmp_pixAddr4 >> 1;
	comp = 1;
	while (comp <= 2) {
		y0 = 0;
		while (y0 <= 1) {
			x0 = 0;
			while (x0 <= 1) {
				tmp_pixAddr5 = pixAddr[1];
				tmp_pixAddr6 = pixAddr[0];
				tmp_SampleIn0 = tokens_SampleIn[(index_SampleIn + (2 * y0 + x0 + 16 + 4 * (comp - 1))) % SIZE_SampleIn];
				pictureBuffer[comp][tmp_pixAddr5 + y0][tmp_pixAddr6 + x0] = tmp_SampleIn0;
				x0 = x0 + 1;
			}
			y0 = y0 + 1;
		}
		comp = comp + 1;
	}
	local_blkIdx = blkIdx;
	blkIdx = local_blkIdx + 1;
	local_blkIdx = blkIdx;
	HevcDecoder_DBFilter_DeblockFilt_zScanToAbsCoord(local_blkIdx, pixAddr);
	tmp_pixAddr7 = pixAddr[0];
	local_xAddrVert = xAddrVert;
	pixAddr[0] = tmp_pixAddr7 + local_xAddrVert;
	tmp_pixAddr8 = pixAddr[1];
	local_yAddrVert = yAddrVert;
	pixAddr[1] = tmp_pixAddr8 + local_yAddrVert;

	// Update ports indexes
	index_BsVer += 1;
	index_Qp += 1;
	index_SampleIn += 24;
	read_end_SampleIn();

	rate_BsVer += 1;
	rate_Qp += 1;
	rate_SampleIn += 24;
}
static void getBlk_launch_isVer_aligned() {

	u8 bsVer;
	i8 qp;
	i32 y;
	i32 x;
	u16 tmp_pixAddr;
	u16 tmp_pixAddr0;
	u8 tmp_SampleIn;
	u16 tmp_pixAddr1;
	u16 tmp_pixAddr2;
	i32 local_PICT_WIDTH;
	u16 local_blkIdx;
	u16 tmp_pixAddr3;
	u16 tmp_pixAddr4;
	u32 comp;
	u32 y0;
	u32 x0;
	u16 tmp_pixAddr5;
	u16 tmp_pixAddr6;
	u8 tmp_SampleIn0;
	u16 tmp_pixAddr7;
	u16 local_xAddrVert;
	u16 tmp_pixAddr8;
	u16 local_yAddrVert;

	bsVer = tokens_BsVer[(index_BsVer + (0)) % SIZE_BsVer];
	qp = tokens_Qp[(index_Qp + (0)) % SIZE_Qp];
	y = 0;
	while (y <= 3) {
		x = 0;
		while (x <= 3) {
			tmp_pixAddr = pixAddr[1];
			tmp_pixAddr0 = pixAddr[0];
			tmp_SampleIn = tokens_SampleIn[(index_SampleIn % SIZE_SampleIn) + (4 * y + x)];
			pictureBuffer[0][tmp_pixAddr + y][tmp_pixAddr0 + x] = tmp_SampleIn;
			x = x + 1;
		}
		y = y + 1;
	}
	tmp_pixAddr1 = pixAddr[0];
	tmp_pixAddr2 = pixAddr[1];
	local_PICT_WIDTH = HevcDecoder_DBFilter_DeblockFilt_PICT_WIDTH;
	qpTab[tmp_pixAddr1 / 4][(tmp_pixAddr2 & local_PICT_WIDTH - 1) >> 2] = qp;
	local_blkIdx = blkIdx;
	bSTableVert[local_blkIdx] = bsVer;
	tmp_pixAddr3 = pixAddr[0];
	pixAddr[0] = tmp_pixAddr3 >> 1;
	tmp_pixAddr4 = pixAddr[1];
	pixAddr[1] = tmp_pixAddr4 >> 1;
	comp = 1;
	while (comp <= 2) {
		y0 = 0;
		while (y0 <= 1) {
			x0 = 0;
			while (x0 <= 1) {
				tmp_pixAddr5 = pixAddr[1];
				tmp_pixAddr6 = pixAddr[0];
				tmp_SampleIn0 = tokens_SampleIn[(index_SampleIn % SIZE_SampleIn) + (2 * y0 + x0 + 16 + 4 * (comp - 1))];
				pictureBuffer[comp][tmp_pixAddr5 + y0][tmp_pixAddr6 + x0] = tmp_SampleIn0;
				x0 = x0 + 1;
			}
			y0 = y0 + 1;
		}
		comp = comp + 1;
	}
	local_blkIdx = blkIdx;
	blkIdx = local_blkIdx + 1;
	local_blkIdx = blkIdx;
	HevcDecoder_DBFilter_DeblockFilt_zScanToAbsCoord(local_blkIdx, pixAddr);
	tmp_pixAddr7 = pixAddr[0];
	local_xAddrVert = xAddrVert;
	pixAddr[0] = tmp_pixAddr7 + local_xAddrVert;
	tmp_pixAddr8 = pixAddr[1];
	local_yAddrVert = yAddrVert;
	pixAddr[1] = tmp_pixAddr8 + local_yAddrVert;

	// Update ports indexes
	index_BsVer += 1;
	index_Qp += 1;
	index_SampleIn += 24;
	read_end_SampleIn();

	rate_BsVer += 1;
	rate_Qp += 1;
	rate_SampleIn += 24;
}
static i32 isSchedulable_getBlk_launch_qp() {
	i32 result;
	u16 local_blkIdx;
	u16 local_numPartition;
	u16 tmp_pixAddr;
	u16 tmp_picSize;
	u16 tmp_pixAddr0;
	u16 tmp_picSize0;

	local_blkIdx = blkIdx;
	local_numPartition = numPartition;
	local_blkIdx = blkIdx;
	tmp_pixAddr = pixAddr[0];
	tmp_picSize = picSize[0];
	tmp_pixAddr0 = pixAddr[1];
	tmp_picSize0 = picSize[1];
	result = local_blkIdx < local_numPartition && (local_blkIdx & 3) == 3 && tmp_pixAddr < tmp_picSize && tmp_pixAddr0 < tmp_picSize0;
	return result;
}

static void getBlk_launch_qp() {

	i8 qp;
	i32 y;
	i32 x;
	u16 tmp_pixAddr;
	u16 tmp_pixAddr0;
	u8 tmp_SampleIn;
	u16 tmp_pixAddr1;
	u16 tmp_pixAddr2;
	i32 local_PICT_WIDTH;
	u16 tmp_pixAddr3;
	u16 tmp_pixAddr4;
	u32 comp;
	u32 y0;
	u32 x0;
	u16 tmp_pixAddr5;
	u16 tmp_pixAddr6;
	u8 tmp_SampleIn0;
	u16 local_blkIdx;
	u16 tmp_pixAddr7;
	u16 local_xAddrVert;
	u16 tmp_pixAddr8;
	u16 local_yAddrVert;

	qp = tokens_Qp[(index_Qp + (0)) % SIZE_Qp];
	y = 0;
	while (y <= 3) {
		x = 0;
		while (x <= 3) {
			tmp_pixAddr = pixAddr[1];
			tmp_pixAddr0 = pixAddr[0];
			tmp_SampleIn = tokens_SampleIn[(index_SampleIn + (4 * y + x)) % SIZE_SampleIn];
			pictureBuffer[0][tmp_pixAddr + y][tmp_pixAddr0 + x] = tmp_SampleIn;
			x = x + 1;
		}
		y = y + 1;
	}
	tmp_pixAddr1 = pixAddr[0];
	tmp_pixAddr2 = pixAddr[1];
	local_PICT_WIDTH = HevcDecoder_DBFilter_DeblockFilt_PICT_WIDTH;
	qpTab[tmp_pixAddr1 / 4][(tmp_pixAddr2 & local_PICT_WIDTH - 1) >> 2] = qp;
	tmp_pixAddr3 = pixAddr[0];
	pixAddr[0] = tmp_pixAddr3 >> 1;
	tmp_pixAddr4 = pixAddr[1];
	pixAddr[1] = tmp_pixAddr4 >> 1;
	comp = 1;
	while (comp <= 2) {
		y0 = 0;
		while (y0 <= 1) {
			x0 = 0;
			while (x0 <= 1) {
				tmp_pixAddr5 = pixAddr[1];
				tmp_pixAddr6 = pixAddr[0];
				tmp_SampleIn0 = tokens_SampleIn[(index_SampleIn + (2 * y0 + x0 + 16 + 4 * (comp - 1))) % SIZE_SampleIn];
				pictureBuffer[comp][tmp_pixAddr5 + y0][tmp_pixAddr6 + x0] = tmp_SampleIn0;
				x0 = x0 + 1;
			}
			y0 = y0 + 1;
		}
		comp = comp + 1;
	}
	local_blkIdx = blkIdx;
	blkIdx = local_blkIdx + 1;
	local_blkIdx = blkIdx;
	HevcDecoder_DBFilter_DeblockFilt_zScanToAbsCoord(local_blkIdx, pixAddr);
	tmp_pixAddr7 = pixAddr[0];
	local_xAddrVert = xAddrVert;
	pixAddr[0] = tmp_pixAddr7 + local_xAddrVert;
	tmp_pixAddr8 = pixAddr[1];
	local_yAddrVert = yAddrVert;
	pixAddr[1] = tmp_pixAddr8 + local_yAddrVert;

	// Update ports indexes
	index_Qp += 1;
	index_SampleIn += 24;
	read_end_SampleIn();

	rate_Qp += 1;
	rate_SampleIn += 24;
}
static void getBlk_launch_qp_aligned() {

	i8 qp;
	i32 y;
	i32 x;
	u16 tmp_pixAddr;
	u16 tmp_pixAddr0;
	u8 tmp_SampleIn;
	u16 tmp_pixAddr1;
	u16 tmp_pixAddr2;
	i32 local_PICT_WIDTH;
	u16 tmp_pixAddr3;
	u16 tmp_pixAddr4;
	u32 comp;
	u32 y0;
	u32 x0;
	u16 tmp_pixAddr5;
	u16 tmp_pixAddr6;
	u8 tmp_SampleIn0;
	u16 local_blkIdx;
	u16 tmp_pixAddr7;
	u16 local_xAddrVert;
	u16 tmp_pixAddr8;
	u16 local_yAddrVert;

	qp = tokens_Qp[(index_Qp + (0)) % SIZE_Qp];
	y = 0;
	while (y <= 3) {
		x = 0;
		while (x <= 3) {
			tmp_pixAddr = pixAddr[1];
			tmp_pixAddr0 = pixAddr[0];
			tmp_SampleIn = tokens_SampleIn[(index_SampleIn % SIZE_SampleIn) + (4 * y + x)];
			pictureBuffer[0][tmp_pixAddr + y][tmp_pixAddr0 + x] = tmp_SampleIn;
			x = x + 1;
		}
		y = y + 1;
	}
	tmp_pixAddr1 = pixAddr[0];
	tmp_pixAddr2 = pixAddr[1];
	local_PICT_WIDTH = HevcDecoder_DBFilter_DeblockFilt_PICT_WIDTH;
	qpTab[tmp_pixAddr1 / 4][(tmp_pixAddr2 & local_PICT_WIDTH - 1) >> 2] = qp;
	tmp_pixAddr3 = pixAddr[0];
	pixAddr[0] = tmp_pixAddr3 >> 1;
	tmp_pixAddr4 = pixAddr[1];
	pixAddr[1] = tmp_pixAddr4 >> 1;
	comp = 1;
	while (comp <= 2) {
		y0 = 0;
		while (y0 <= 1) {
			x0 = 0;
			while (x0 <= 1) {
				tmp_pixAddr5 = pixAddr[1];
				tmp_pixAddr6 = pixAddr[0];
				tmp_SampleIn0 = tokens_SampleIn[(index_SampleIn % SIZE_SampleIn) + (2 * y0 + x0 + 16 + 4 * (comp - 1))];
				pictureBuffer[comp][tmp_pixAddr5 + y0][tmp_pixAddr6 + x0] = tmp_SampleIn0;
				x0 = x0 + 1;
			}
			y0 = y0 + 1;
		}
		comp = comp + 1;
	}
	local_blkIdx = blkIdx;
	blkIdx = local_blkIdx + 1;
	local_blkIdx = blkIdx;
	HevcDecoder_DBFilter_DeblockFilt_zScanToAbsCoord(local_blkIdx, pixAddr);
	tmp_pixAddr7 = pixAddr[0];
	local_xAddrVert = xAddrVert;
	pixAddr[0] = tmp_pixAddr7 + local_xAddrVert;
	tmp_pixAddr8 = pixAddr[1];
	local_yAddrVert = yAddrVert;
	pixAddr[1] = tmp_pixAddr8 + local_yAddrVert;

	// Update ports indexes
	index_Qp += 1;
	index_SampleIn += 24;
	read_end_SampleIn();

	rate_Qp += 1;
	rate_SampleIn += 24;
}
static i32 isSchedulable_getBlk_skip_vertEdge() {
	i32 result;
	u16 local_blkIdx;
	u16 local_numPartition;
	i32 local_FILT_VERT_EDGES;
	u16 tmp_pixAddr;
	u16 tmp_picSize;
	u16 tmp_pixAddr0;
	u16 tmp_picSize0;

	local_blkIdx = blkIdx;
	local_numPartition = numPartition;
	local_FILT_VERT_EDGES = FILT_VERT_EDGES;
	tmp_pixAddr = pixAddr[0];
	tmp_picSize = picSize[0];
	tmp_pixAddr0 = pixAddr[1];
	tmp_picSize0 = picSize[1];
	result = local_blkIdx < local_numPartition && local_FILT_VERT_EDGES && (tmp_pixAddr >= tmp_picSize || tmp_pixAddr0 >= tmp_picSize0);
	return result;
}

static void getBlk_skip_vertEdge() {

	u16 local_blkIdx;
	u16 local_xAddrVert;
	u8 local_log2lcuSizeMax;
	u16 local_yAddrVert;
	u16 tmp_pixAddr;
	u16 tmp_pixAddr0;

	local_blkIdx = blkIdx;
	bSTableVert[local_blkIdx] = 0;
	local_xAddrVert = xAddrVert;
	local_log2lcuSizeMax = log2lcuSizeMax;
	local_yAddrVert = yAddrVert;
	local_log2lcuSizeMax = log2lcuSizeMax;
	local_blkIdx = blkIdx;
	bSTableHoriz[local_xAddrVert >> local_log2lcuSizeMax][local_yAddrVert >> local_log2lcuSizeMax][local_blkIdx] = 0;
	local_blkIdx = blkIdx;
	blkIdx = local_blkIdx + 1;
	local_blkIdx = blkIdx;
	HevcDecoder_DBFilter_DeblockFilt_zScanToAbsCoord(local_blkIdx, pixAddr);
	tmp_pixAddr = pixAddr[0];
	local_xAddrVert = xAddrVert;
	pixAddr[0] = tmp_pixAddr + local_xAddrVert;
	tmp_pixAddr0 = pixAddr[1];
	local_yAddrVert = yAddrVert;
	pixAddr[1] = tmp_pixAddr0 + local_yAddrVert;

	// Update ports indexes

}
static i32 isSchedulable_getBlk_skip_horEdge() {
	i32 result;
	u16 local_blkIdx;
	u16 local_numPartition;
	i32 local_FILT_VERT_EDGES;
	u16 tmp_pixAddr;
	u16 tmp_picSize;
	u16 tmp_pixAddr0;
	u16 tmp_picSize0;

	local_blkIdx = blkIdx;
	local_numPartition = numPartition;
	local_FILT_VERT_EDGES = FILT_VERT_EDGES;
	tmp_pixAddr = pixAddr[0];
	tmp_picSize = picSize[0];
	tmp_pixAddr0 = pixAddr[1];
	tmp_picSize0 = picSize[1];
	result = local_blkIdx < local_numPartition && !local_FILT_VERT_EDGES && (tmp_pixAddr >= tmp_picSize || tmp_pixAddr0 >= tmp_picSize0);
	return result;
}

static void getBlk_skip_horEdge() {

	u16 local_blkIdx;
	u16 local_xAddrVert;
	u8 local_log2lcuSizeMax;
	u16 local_yAddrVert;
	u16 tmp_pixAddr;
	u16 tmp_pixAddr0;

	local_blkIdx = blkIdx;
	bSTableVert[local_blkIdx] = 0;
	local_xAddrVert = xAddrVert;
	local_log2lcuSizeMax = log2lcuSizeMax;
	local_yAddrVert = yAddrVert;
	local_log2lcuSizeMax = log2lcuSizeMax;
	local_blkIdx = blkIdx;
	bSTableHoriz[local_xAddrVert >> local_log2lcuSizeMax][local_yAddrVert >> local_log2lcuSizeMax][local_blkIdx] = 0;
	local_blkIdx = blkIdx;
	blkIdx = local_blkIdx + 1;
	local_blkIdx = blkIdx;
	HevcDecoder_DBFilter_DeblockFilt_zScanToAbsCoord(local_blkIdx, pixAddr);
	tmp_pixAddr = pixAddr[0];
	local_xAddrVert = xAddrVert;
	pixAddr[0] = tmp_pixAddr + local_xAddrVert;
	tmp_pixAddr0 = pixAddr[1];
	local_yAddrVert = yAddrVert;
	pixAddr[1] = tmp_pixAddr0 + local_yAddrVert;

	// Update ports indexes
	index_SampleIn += 24;
	read_end_SampleIn();

	rate_SampleIn += 24;
}
static void getBlk_skip_horEdge_aligned() {

	u16 local_blkIdx;
	u16 local_xAddrVert;
	u8 local_log2lcuSizeMax;
	u16 local_yAddrVert;
	u16 tmp_pixAddr;
	u16 tmp_pixAddr0;

	local_blkIdx = blkIdx;
	bSTableVert[local_blkIdx] = 0;
	local_xAddrVert = xAddrVert;
	local_log2lcuSizeMax = log2lcuSizeMax;
	local_yAddrVert = yAddrVert;
	local_log2lcuSizeMax = log2lcuSizeMax;
	local_blkIdx = blkIdx;
	bSTableHoriz[local_xAddrVert >> local_log2lcuSizeMax][local_yAddrVert >> local_log2lcuSizeMax][local_blkIdx] = 0;
	local_blkIdx = blkIdx;
	blkIdx = local_blkIdx + 1;
	local_blkIdx = blkIdx;
	HevcDecoder_DBFilter_DeblockFilt_zScanToAbsCoord(local_blkIdx, pixAddr);
	tmp_pixAddr = pixAddr[0];
	local_xAddrVert = xAddrVert;
	pixAddr[0] = tmp_pixAddr + local_xAddrVert;
	tmp_pixAddr0 = pixAddr[1];
	local_yAddrVert = yAddrVert;
	pixAddr[1] = tmp_pixAddr0 + local_yAddrVert;

	// Update ports indexes
	index_SampleIn += 24;
	read_end_SampleIn();

	rate_SampleIn += 24;
}
static i32 isSchedulable_getBlk_done() {
	i32 result;
	u16 local_blkIdx;
	u16 local_numPartition;

	local_blkIdx = blkIdx;
	local_numPartition = numPartition;
	result = local_blkIdx == local_numPartition;
	return result;
}

static void getBlk_done() {


	computeNextLcuAddr();

	// Update ports indexes

}
static i32 isSchedulable_getBs4Blk_launch_isHorVer() {
	i32 result;
	u16 local_blkIdx;
	u16 local_numPartition;
	u16 tmp_pixAddr;
	u16 tmp_picSize;
	u16 tmp_pixAddr0;
	u16 tmp_picSize0;

	local_blkIdx = blkIdx;
	local_numPartition = numPartition;
	local_blkIdx = blkIdx;
	tmp_pixAddr = pixAddr[0];
	tmp_picSize = picSize[0];
	tmp_pixAddr0 = pixAddr[1];
	tmp_picSize0 = picSize[1];
	result = local_blkIdx < local_numPartition && (local_blkIdx & 3) == 0 && tmp_pixAddr < tmp_picSize && tmp_pixAddr0 < tmp_picSize0;
	return result;
}

static void getBs4Blk_launch_isHorVer() {

	u8 bsHor;
	u8 bsVer;
	i8 qp;
	u16 tmp_pixAddr;
	i32 local_PICT_WIDTH;
	u16 tmp_pixAddr0;
	u16 local_blkIdx;
	u16 local_xAddrVert;
	u8 local_log2lcuSizeMax;
	u16 local_yAddrVert;
	u16 tmp_pixAddr1;
	u16 tmp_pixAddr2;

	bsHor = tokens_BsHor[(index_BsHor + (0)) % SIZE_BsHor];
	bsVer = tokens_BsVer[(index_BsVer + (0)) % SIZE_BsVer];
	qp = tokens_Qp[(index_Qp + (0)) % SIZE_Qp];
	tmp_pixAddr = pixAddr[0];
	local_PICT_WIDTH = HevcDecoder_DBFilter_DeblockFilt_PICT_WIDTH;
	tmp_pixAddr0 = pixAddr[1];
	qpTab[(tmp_pixAddr & local_PICT_WIDTH - 1) >> 2][tmp_pixAddr0 / 4] = qp;
	local_blkIdx = blkIdx;
	bSTableVert[local_blkIdx] = bsVer;
	local_xAddrVert = xAddrVert;
	local_log2lcuSizeMax = log2lcuSizeMax;
	local_yAddrVert = yAddrVert;
	local_log2lcuSizeMax = log2lcuSizeMax;
	local_blkIdx = blkIdx;
	bSTableHoriz[local_xAddrVert >> local_log2lcuSizeMax][local_yAddrVert >> local_log2lcuSizeMax][local_blkIdx] = bsHor;
	local_blkIdx = blkIdx;
	blkIdx = local_blkIdx + 1;
	local_blkIdx = blkIdx;
	HevcDecoder_DBFilter_DeblockFilt_zScanToAbsCoord(local_blkIdx, pixAddr);
	tmp_pixAddr1 = pixAddr[0];
	local_xAddrVert = xAddrVert;
	pixAddr[0] = tmp_pixAddr1 + local_xAddrVert;
	tmp_pixAddr2 = pixAddr[1];
	local_yAddrVert = yAddrVert;
	pixAddr[1] = tmp_pixAddr2 + local_yAddrVert;

	// Update ports indexes
	index_BsHor += 1;
	index_BsVer += 1;
	index_Qp += 1;

	rate_BsHor += 1;
	rate_BsVer += 1;
	rate_Qp += 1;
}
static i32 isSchedulable_getBs4Blk_launch_isHor() {
	i32 result;
	u16 local_blkIdx;
	u16 local_numPartition;
	u16 tmp_pixAddr;
	u16 tmp_picSize;
	u16 tmp_pixAddr0;
	u16 tmp_picSize0;

	local_blkIdx = blkIdx;
	local_numPartition = numPartition;
	local_blkIdx = blkIdx;
	tmp_pixAddr = pixAddr[0];
	tmp_picSize = picSize[0];
	tmp_pixAddr0 = pixAddr[1];
	tmp_picSize0 = picSize[1];
	result = local_blkIdx < local_numPartition && (local_blkIdx & 3) < 2 && tmp_pixAddr < tmp_picSize && tmp_pixAddr0 < tmp_picSize0;
	return result;
}

static void getBs4Blk_launch_isHor() {

	u8 bsHor;
	i8 qp;
	u16 tmp_pixAddr;
	i32 local_PICT_WIDTH;
	u16 tmp_pixAddr0;
	u16 local_xAddrVert;
	u8 local_log2lcuSizeMax;
	u16 local_yAddrVert;
	u16 local_blkIdx;
	u16 tmp_pixAddr1;
	u16 tmp_pixAddr2;

	bsHor = tokens_BsHor[(index_BsHor + (0)) % SIZE_BsHor];
	qp = tokens_Qp[(index_Qp + (0)) % SIZE_Qp];
	tmp_pixAddr = pixAddr[0];
	local_PICT_WIDTH = HevcDecoder_DBFilter_DeblockFilt_PICT_WIDTH;
	tmp_pixAddr0 = pixAddr[1];
	qpTab[(tmp_pixAddr & local_PICT_WIDTH - 1) >> 2][tmp_pixAddr0 / 4] = qp;
	local_xAddrVert = xAddrVert;
	local_log2lcuSizeMax = log2lcuSizeMax;
	local_yAddrVert = yAddrVert;
	local_log2lcuSizeMax = log2lcuSizeMax;
	local_blkIdx = blkIdx;
	bSTableHoriz[local_xAddrVert >> local_log2lcuSizeMax][local_yAddrVert >> local_log2lcuSizeMax][local_blkIdx] = bsHor;
	local_blkIdx = blkIdx;
	blkIdx = local_blkIdx + 1;
	local_blkIdx = blkIdx;
	HevcDecoder_DBFilter_DeblockFilt_zScanToAbsCoord(local_blkIdx, pixAddr);
	tmp_pixAddr1 = pixAddr[0];
	local_xAddrVert = xAddrVert;
	pixAddr[0] = tmp_pixAddr1 + local_xAddrVert;
	tmp_pixAddr2 = pixAddr[1];
	local_yAddrVert = yAddrVert;
	pixAddr[1] = tmp_pixAddr2 + local_yAddrVert;

	// Update ports indexes
	index_BsHor += 1;
	index_Qp += 1;

	rate_BsHor += 1;
	rate_Qp += 1;
}
static i32 isSchedulable_getBs4Blk_launch_isVer() {
	i32 result;
	u16 local_blkIdx;
	u16 local_numPartition;
	u16 tmp_pixAddr;
	u16 tmp_picSize;
	u16 tmp_pixAddr0;
	u16 tmp_picSize0;

	local_blkIdx = blkIdx;
	local_numPartition = numPartition;
	local_blkIdx = blkIdx;
	tmp_pixAddr = pixAddr[0];
	tmp_picSize = picSize[0];
	tmp_pixAddr0 = pixAddr[1];
	tmp_picSize0 = picSize[1];
	result = local_blkIdx < local_numPartition && (local_blkIdx & 1) == 0 && tmp_pixAddr < tmp_picSize && tmp_pixAddr0 < tmp_picSize0;
	return result;
}

static void getBs4Blk_launch_isVer() {

	u8 bsVer;
	i8 qp;
	u16 tmp_pixAddr;
	i32 local_PICT_WIDTH;
	u16 tmp_pixAddr0;
	u16 local_blkIdx;
	u16 tmp_pixAddr1;
	u16 local_xAddrVert;
	u16 tmp_pixAddr2;
	u16 local_yAddrVert;

	bsVer = tokens_BsVer[(index_BsVer + (0)) % SIZE_BsVer];
	qp = tokens_Qp[(index_Qp + (0)) % SIZE_Qp];
	tmp_pixAddr = pixAddr[0];
	local_PICT_WIDTH = HevcDecoder_DBFilter_DeblockFilt_PICT_WIDTH;
	tmp_pixAddr0 = pixAddr[1];
	qpTab[(tmp_pixAddr & local_PICT_WIDTH - 1) >> 2][tmp_pixAddr0 / 4] = qp;
	local_blkIdx = blkIdx;
	bSTableVert[local_blkIdx] = bsVer;
	local_blkIdx = blkIdx;
	blkIdx = local_blkIdx + 1;
	local_blkIdx = blkIdx;
	HevcDecoder_DBFilter_DeblockFilt_zScanToAbsCoord(local_blkIdx, pixAddr);
	tmp_pixAddr1 = pixAddr[0];
	local_xAddrVert = xAddrVert;
	pixAddr[0] = tmp_pixAddr1 + local_xAddrVert;
	tmp_pixAddr2 = pixAddr[1];
	local_yAddrVert = yAddrVert;
	pixAddr[1] = tmp_pixAddr2 + local_yAddrVert;

	// Update ports indexes
	index_BsVer += 1;
	index_Qp += 1;

	rate_BsVer += 1;
	rate_Qp += 1;
}
static i32 isSchedulable_getBs4Blk_launch_qp() {
	i32 result;
	u16 local_blkIdx;
	u16 local_numPartition;
	u16 tmp_pixAddr;
	u16 tmp_picSize;
	u16 tmp_pixAddr0;
	u16 tmp_picSize0;

	local_blkIdx = blkIdx;
	local_numPartition = numPartition;
	local_blkIdx = blkIdx;
	tmp_pixAddr = pixAddr[0];
	tmp_picSize = picSize[0];
	tmp_pixAddr0 = pixAddr[1];
	tmp_picSize0 = picSize[1];
	result = local_blkIdx < local_numPartition && (local_blkIdx & 3) == 3 && tmp_pixAddr < tmp_picSize && tmp_pixAddr0 < tmp_picSize0;
	return result;
}

static void getBs4Blk_launch_qp() {

	i8 qp;
	u16 tmp_pixAddr;
	i32 local_PICT_WIDTH;
	u16 tmp_pixAddr0;
	u16 local_blkIdx;
	u16 tmp_pixAddr1;
	u16 local_xAddrVert;
	u16 tmp_pixAddr2;
	u16 local_yAddrVert;

	qp = tokens_Qp[(index_Qp + (0)) % SIZE_Qp];
	tmp_pixAddr = pixAddr[0];
	local_PICT_WIDTH = HevcDecoder_DBFilter_DeblockFilt_PICT_WIDTH;
	tmp_pixAddr0 = pixAddr[1];
	qpTab[(tmp_pixAddr & local_PICT_WIDTH - 1) >> 2][tmp_pixAddr0 / 4] = qp;
	local_blkIdx = blkIdx;
	blkIdx = local_blkIdx + 1;
	local_blkIdx = blkIdx;
	HevcDecoder_DBFilter_DeblockFilt_zScanToAbsCoord(local_blkIdx, pixAddr);
	tmp_pixAddr1 = pixAddr[0];
	local_xAddrVert = xAddrVert;
	pixAddr[0] = tmp_pixAddr1 + local_xAddrVert;
	tmp_pixAddr2 = pixAddr[1];
	local_yAddrVert = yAddrVert;
	pixAddr[1] = tmp_pixAddr2 + local_yAddrVert;

	// Update ports indexes
	index_Qp += 1;

	rate_Qp += 1;
}
static i32 isSchedulable_getBs4Blk_skip() {
	i32 result;
	u16 local_blkIdx;
	u16 local_numPartition;
	u16 tmp_pixAddr;
	u16 tmp_picSize;
	u16 tmp_pixAddr0;
	u16 tmp_picSize0;

	local_blkIdx = blkIdx;
	local_numPartition = numPartition;
	tmp_pixAddr = pixAddr[0];
	tmp_picSize = picSize[0];
	tmp_pixAddr0 = pixAddr[1];
	tmp_picSize0 = picSize[1];
	result = local_blkIdx < local_numPartition && (tmp_pixAddr >= tmp_picSize || tmp_pixAddr0 >= tmp_picSize0);
	return result;
}

static void getBs4Blk_skip() {

	u16 local_blkIdx;
	u16 local_xAddrVert;
	u8 local_log2lcuSizeMax;
	u16 local_yAddrVert;
	u16 tmp_pixAddr;
	u16 tmp_pixAddr0;

	local_blkIdx = blkIdx;
	bSTableVert[local_blkIdx] = 0;
	local_xAddrVert = xAddrVert;
	local_log2lcuSizeMax = log2lcuSizeMax;
	local_yAddrVert = yAddrVert;
	local_log2lcuSizeMax = log2lcuSizeMax;
	local_blkIdx = blkIdx;
	bSTableHoriz[local_xAddrVert >> local_log2lcuSizeMax][local_yAddrVert >> local_log2lcuSizeMax][local_blkIdx] = 0;
	local_blkIdx = blkIdx;
	blkIdx = local_blkIdx + 1;
	local_blkIdx = blkIdx;
	HevcDecoder_DBFilter_DeblockFilt_zScanToAbsCoord(local_blkIdx, pixAddr);
	tmp_pixAddr = pixAddr[0];
	local_xAddrVert = xAddrVert;
	pixAddr[0] = tmp_pixAddr + local_xAddrVert;
	tmp_pixAddr0 = pixAddr[1];
	local_yAddrVert = yAddrVert;
	pixAddr[1] = tmp_pixAddr0 + local_yAddrVert;

	// Update ports indexes

}
static i32 isSchedulable_getBs4Blk_done() {
	i32 result;
	u16 local_blkIdx;
	u16 local_numPartition;

	local_blkIdx = blkIdx;
	local_numPartition = numPartition;
	result = local_blkIdx == local_numPartition;
	return result;
}

static void getBs4Blk_done() {


	computeNextLcuAddr();

	// Update ports indexes

}
static i32 isSchedulable_getCuPix_done() {
	i32 result;
	u16 local_tileIdx;
	u16 local_numTiles;

	local_tileIdx = tileIdx;
	local_numTiles = numTiles;
	result = local_tileIdx == local_numTiles;
	return result;
}

static void getCuPix_done() {


	tokenSent = 0;
	xIdx = 0;
	yIdx = 0;
	tileIdx = 0;

	// Update ports indexes

}
static i32 isSchedulable_filterEdges() {
	i32 result;

	result = 1;
	return result;
}

static void filterEdges() {

	u16 local_numPartition;
	i32 lumaPartMax;
	i32 chromaPartMax;
	i32 local_disDbf;
	i32 local_FILT_VERT_EDGES;
	i32 idxBlk;
	i32 idxBlk0;
	i32 local_FILT_HOR_EDGES;
	u16 local_xAddrVert;
	u8 local_lcuSizeMax;
	u16 local_yAddrVert;
	u16 tmp_picSize;

	local_numPartition = numPartition;
	lumaPartMax = (local_numPartition >> 2) - 1;
	local_numPartition = numPartition;
	chromaPartMax = (local_numPartition >> 4) - 1;
	local_disDbf = disDbf;
	if (!local_disDbf) {
		local_FILT_VERT_EDGES = FILT_VERT_EDGES;
		if (local_FILT_VERT_EDGES) {
			idxBlk = 0;
			while (idxBlk <= lumaPartMax) {
				filterProcessLumaBlkVertical(idxBlk << 2);
				idxBlk = idxBlk + 1;
			}
			idxBlk0 = 0;
			while (idxBlk0 <= chromaPartMax) {
				filterProcessChromaBlkVertical(idxBlk0 << 4);
				idxBlk0 = idxBlk0 + 1;
			}
		}
		local_FILT_HOR_EDGES = FILT_HOR_EDGES;
		if (local_FILT_HOR_EDGES) {
			local_xAddrVert = xAddrVert;
			if (local_xAddrVert > 0) {
				local_xAddrVert = xAddrVert;
				local_lcuSizeMax = lcuSizeMax;
				xAddrHor = local_xAddrVert - local_lcuSizeMax;
				local_yAddrVert = yAddrVert;
				yAddrHor = local_yAddrVert;
				filterHorEdges();
			}
			local_xAddrVert = xAddrVert;
			local_lcuSizeMax = lcuSizeMax;
			tmp_picSize = picSize[0];
			if (local_xAddrVert + local_lcuSizeMax >= tmp_picSize) {
				local_xAddrVert = xAddrVert;
				xAddrHor = local_xAddrVert;
				filterHorEdges();
			}
		}
	}
	local_xAddrVert = xAddrVert;
	xAddrHor = local_xAddrVert;
	local_yAddrVert = yAddrVert;
	yAddrHor = local_yAddrVert;

	// Update ports indexes

}
static i32 isSchedulable_filteringOnlyVertEdge_isFalse() {
	i32 result;
	i32 local_FILT_HOR_EDGES;

	local_FILT_HOR_EDGES = FILT_HOR_EDGES;
	result = local_FILT_HOR_EDGES;
	return result;
}

static void filteringOnlyVertEdge_isFalse() {



	// Update ports indexes

}
static i32 isSchedulable_sendSamples_launch_luma() {
	i32 result;
	u16 local_tileIdx;
	u16 local_numTiles;
	u16 local_tokenSent;
	u16 tmp_numTokenPerLcu;

	local_tileIdx = tileIdx;
	local_numTiles = numTiles;
	local_tokenSent = tokenSent;
	tmp_numTokenPerLcu = numTokenPerLcu[0];
	result = local_tileIdx < local_numTiles && local_tokenSent < tmp_numTokenPerLcu;
	return result;
}

static void sendSamples_launch_luma() {

	u16 xOff;
	u16 yOff;
	u16 local_tokenSent;
	u8 local_lcuSizeMax;
	u8 local_log2lcuSizeMax;
	u32 x;
	i32 local_DEBUG;
	u16 local_yIdx;
	u16 local_xIdx;
	u8 tmp_pictureBuffer;
	u16 tmp_picSize;
	u16 tmp_picSize0;
	u8 tmp_pictureBuffer0;

	local_tokenSent = tokenSent;
	local_lcuSizeMax = lcuSizeMax;
	xOff = local_tokenSent & local_lcuSizeMax - 1;
	local_tokenSent = tokenSent;
	local_log2lcuSizeMax = log2lcuSizeMax;
	yOff = local_tokenSent >> local_log2lcuSizeMax;
	x = 0;
	while (x <= 15) {
		local_DEBUG = DEBUG;
		if (!local_DEBUG) {
			local_yIdx = yIdx;
			local_xIdx = xIdx;
			tmp_pictureBuffer = pictureBuffer[0][local_yIdx + yOff][local_xIdx + xOff + x];
			tokens_FiltSample[(index_FiltSample + (x)) % SIZE_FiltSample] = tmp_pictureBuffer;
		} else {
			local_xIdx = xIdx;
			tmp_picSize = picSize[0];
			local_yIdx = yIdx;
			tmp_picSize0 = picSize[1];
			if (local_xIdx + xOff + x < tmp_picSize && local_yIdx + yOff < tmp_picSize0) {
				local_yIdx = yIdx;
				local_xIdx = xIdx;
				tmp_pictureBuffer0 = pictureBuffer[0][local_yIdx + yOff][local_xIdx + xOff + x];
				tokens_FiltSample[(index_FiltSample + (x)) % SIZE_FiltSample] = tmp_pictureBuffer0;
			} else {
				tokens_FiltSample[(index_FiltSample + (x)) % SIZE_FiltSample] = 0;
			}
		}
		x = x + 1;
	}
	local_tokenSent = tokenSent;
	tokenSent = local_tokenSent + 16;

	// Update ports indexes
	index_FiltSample += 16;
	write_end_FiltSample();

}
static void sendSamples_launch_luma_aligned() {

	u16 xOff;
	u16 yOff;
	u16 local_tokenSent;
	u8 local_lcuSizeMax;
	u8 local_log2lcuSizeMax;
	u32 x;
	i32 local_DEBUG;
	u16 local_yIdx;
	u16 local_xIdx;
	u8 tmp_pictureBuffer;
	u16 tmp_picSize;
	u16 tmp_picSize0;
	u8 tmp_pictureBuffer0;

	local_tokenSent = tokenSent;
	local_lcuSizeMax = lcuSizeMax;
	xOff = local_tokenSent & local_lcuSizeMax - 1;
	local_tokenSent = tokenSent;
	local_log2lcuSizeMax = log2lcuSizeMax;
	yOff = local_tokenSent >> local_log2lcuSizeMax;
	x = 0;
	while (x <= 15) {
		local_DEBUG = DEBUG;
		if (!local_DEBUG) {
			local_yIdx = yIdx;
			local_xIdx = xIdx;
			tmp_pictureBuffer = pictureBuffer[0][local_yIdx + yOff][local_xIdx + xOff + x];
			tokens_FiltSample[(index_FiltSample % SIZE_FiltSample) + (x)] = tmp_pictureBuffer;
		} else {
			local_xIdx = xIdx;
			tmp_picSize = picSize[0];
			local_yIdx = yIdx;
			tmp_picSize0 = picSize[1];
			if (local_xIdx + xOff + x < tmp_picSize && local_yIdx + yOff < tmp_picSize0) {
				local_yIdx = yIdx;
				local_xIdx = xIdx;
				tmp_pictureBuffer0 = pictureBuffer[0][local_yIdx + yOff][local_xIdx + xOff + x];
				tokens_FiltSample[(index_FiltSample % SIZE_FiltSample) + (x)] = tmp_pictureBuffer0;
			} else {
				tokens_FiltSample[(index_FiltSample % SIZE_FiltSample) + (x)] = 0;
			}
		}
		x = x + 1;
	}
	local_tokenSent = tokenSent;
	tokenSent = local_tokenSent + 16;

	// Update ports indexes
	index_FiltSample += 16;
	write_end_FiltSample();

}
static i32 isSchedulable_sendSamples_launch_lumaDone() {
	i32 result;
	u16 local_tokenSent;
	u16 tmp_numTokenPerLcu;

	local_tokenSent = tokenSent;
	tmp_numTokenPerLcu = numTokenPerLcu[0];
	result = local_tokenSent == tmp_numTokenPerLcu;
	return result;
}

static void sendSamples_launch_lumaDone() {


	tokenSent = 0;
	compIdx = 1;

	// Update ports indexes

}
static i32 isSchedulable_sendSamples_launch_chroma() {
	i32 result;
	u8 local_compIdx;

	local_compIdx = compIdx;
	result = local_compIdx < 3;
	return result;
}

static void sendSamples_launch_chroma() {

	u16 xOff;
	u16 yOff;
	u16 local_tokenSent;
	u8 local_lcuSizeMax;
	u8 local_log2lcuSizeMax;
	u32 x;
	i32 local_DEBUG;
	u8 local_compIdx;
	u16 local_yIdx;
	u16 local_xIdx;
	u8 tmp_pictureBuffer;
	u16 tmp_picSize;
	u16 tmp_picSize0;
	u8 tmp_pictureBuffer0;
	u16 tmp_numTokenPerLcu;

	local_tokenSent = tokenSent;
	local_lcuSizeMax = lcuSizeMax;
	xOff = local_tokenSent & (local_lcuSizeMax - 1) >> 1;
	local_tokenSent = tokenSent;
	local_log2lcuSizeMax = log2lcuSizeMax;
	yOff = local_tokenSent >> (local_log2lcuSizeMax - 1);
	x = 0;
	while (x <= 7) {
		local_DEBUG = DEBUG;
		if (!local_DEBUG) {
			local_compIdx = compIdx;
			local_yIdx = yIdx;
			local_xIdx = xIdx;
			tmp_pictureBuffer = pictureBuffer[local_compIdx][local_yIdx / 2 + yOff][local_xIdx / 2 + xOff + x];
			tokens_FiltSample[(index_FiltSample + (x)) % SIZE_FiltSample] = tmp_pictureBuffer;
		} else {
			local_xIdx = xIdx;
			tmp_picSize = picSize[0];
			local_yIdx = yIdx;
			tmp_picSize0 = picSize[1];
			if (local_xIdx / 2 + xOff + x < tmp_picSize / 2 && local_yIdx / 2 + yOff < tmp_picSize0 / 2) {
				local_compIdx = compIdx;
				local_yIdx = yIdx;
				local_xIdx = xIdx;
				tmp_pictureBuffer0 = pictureBuffer[local_compIdx][local_yIdx / 2 + yOff][local_xIdx / 2 + xOff + x];
				tokens_FiltSample[(index_FiltSample + (x)) % SIZE_FiltSample] = tmp_pictureBuffer0;
			} else {
				tokens_FiltSample[(index_FiltSample + (x)) % SIZE_FiltSample] = 0;
			}
		}
		x = x + 1;
	}
	local_tokenSent = tokenSent;
	tokenSent = local_tokenSent + 8;
	local_tokenSent = tokenSent;
	tmp_numTokenPerLcu = numTokenPerLcu[1];
	if (local_tokenSent == tmp_numTokenPerLcu) {
		tokenSent = 0;
		local_compIdx = compIdx;
		compIdx = local_compIdx + 1;
	}

	// Update ports indexes
	index_FiltSample += 8;
	write_end_FiltSample();

}
static void sendSamples_launch_chroma_aligned() {

	u16 xOff;
	u16 yOff;
	u16 local_tokenSent;
	u8 local_lcuSizeMax;
	u8 local_log2lcuSizeMax;
	u32 x;
	i32 local_DEBUG;
	u8 local_compIdx;
	u16 local_yIdx;
	u16 local_xIdx;
	u8 tmp_pictureBuffer;
	u16 tmp_picSize;
	u16 tmp_picSize0;
	u8 tmp_pictureBuffer0;
	u16 tmp_numTokenPerLcu;

	local_tokenSent = tokenSent;
	local_lcuSizeMax = lcuSizeMax;
	xOff = local_tokenSent & (local_lcuSizeMax - 1) >> 1;
	local_tokenSent = tokenSent;
	local_log2lcuSizeMax = log2lcuSizeMax;
	yOff = local_tokenSent >> (local_log2lcuSizeMax - 1);
	x = 0;
	while (x <= 7) {
		local_DEBUG = DEBUG;
		if (!local_DEBUG) {
			local_compIdx = compIdx;
			local_yIdx = yIdx;
			local_xIdx = xIdx;
			tmp_pictureBuffer = pictureBuffer[local_compIdx][local_yIdx / 2 + yOff][local_xIdx / 2 + xOff + x];
			tokens_FiltSample[(index_FiltSample % SIZE_FiltSample) + (x)] = tmp_pictureBuffer;
		} else {
			local_xIdx = xIdx;
			tmp_picSize = picSize[0];
			local_yIdx = yIdx;
			tmp_picSize0 = picSize[1];
			if (local_xIdx / 2 + xOff + x < tmp_picSize / 2 && local_yIdx / 2 + yOff < tmp_picSize0 / 2) {
				local_compIdx = compIdx;
				local_yIdx = yIdx;
				local_xIdx = xIdx;
				tmp_pictureBuffer0 = pictureBuffer[local_compIdx][local_yIdx / 2 + yOff][local_xIdx / 2 + xOff + x];
				tokens_FiltSample[(index_FiltSample % SIZE_FiltSample) + (x)] = tmp_pictureBuffer0;
			} else {
				tokens_FiltSample[(index_FiltSample % SIZE_FiltSample) + (x)] = 0;
			}
		}
		x = x + 1;
	}
	local_tokenSent = tokenSent;
	tokenSent = local_tokenSent + 8;
	local_tokenSent = tokenSent;
	tmp_numTokenPerLcu = numTokenPerLcu[1];
	if (local_tokenSent == tmp_numTokenPerLcu) {
		tokenSent = 0;
		local_compIdx = compIdx;
		compIdx = local_compIdx + 1;
	}

	// Update ports indexes
	index_FiltSample += 8;
	write_end_FiltSample();

}
static i32 isSchedulable_sendSamples_launch_chromaDone() {
	i32 result;
	u8 local_compIdx;

	local_compIdx = compIdx;
	result = local_compIdx == 3;
	return result;
}

static void sendSamples_launch_chromaDone() {


	tokenSent = 0;
	computeNextLcuAddr();

	// Update ports indexes

}
static i32 isSchedulable_sendSamples_done() {
	i32 result;
	u16 local_tileIdx;
	u16 local_numTiles;

	local_tileIdx = tileIdx;
	local_numTiles = numTiles;
	result = local_tileIdx == local_numTiles;
	return result;
}

static void sendSamples_done() {



	// Update ports indexes

}

////////////////////////////////////////////////////////////////////////////////
// Initializes

void HevcDecoder_DBFilter_DeblockFilt_initialize(schedinfo_t *si) {
	int i = 0;
	write_FiltSample();
	/* Set initial state to current FSM state */
	_FSM_state = my_state_IsNewPict;
finished:
	write_end_FiltSample();
	return;
}

////////////////////////////////////////////////////////////////////////////////
// Action scheduler

void HevcDecoder_DBFilter_DeblockFilt_scheduler(schedinfo_t *si) {
	int i = 0;

	read_BsHor();
	read_BsVer();
	read_DBFDisable();
	read_IsPicSlcLcu();
	read_LcuSizeMax();
	read_PicSize();
	read_Qp();
	read_SampleIn();
	read_SyntaxElem();
	read_TilesCoord();
	write_FiltSample();

	// jump to FSM state
	switch (_FSM_state) {
	case my_state_CheckEdgeFiltered:
		goto l_CheckEdgeFiltered;
	case my_state_FilterEdges:
		goto l_FilterEdges;
	case my_state_GetBlk:
		goto l_GetBlk;
	case my_state_GetBs4Blk:
		goto l_GetBs4Blk;
	case my_state_GetCuPix:
		goto l_GetCuPix;
	case my_state_GetNumTiles:
		goto l_GetNumTiles;
	case my_state_GetPartition:
		goto l_GetPartition;
	case my_state_GetTilesCoord:
		goto l_GetTilesCoord;
	case my_state_IsNewPict:
		goto l_IsNewPict;
	case my_state_SendSamples:
		goto l_SendSamples;
	case my_state_SendSamplesChr:
		goto l_SendSamplesChr;
	case my_state_SendSamplesLuma:
		goto l_SendSamplesLuma;
	default:
		printf("unknown state in HevcDecoder_DBFilter_DeblockFilt.c : %s\n", stateNames[_FSM_state]);
		exit(1);
	}

	// FSM transitions
l_CheckEdgeFiltered:
	if (isSchedulable_filteringOnlyVertEdge_isFalse()) {
		filteringOnlyVertEdge_isFalse();
		i++;
		goto l_GetCuPix;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_CheckEdgeFiltered;
		goto finished;
	}
l_FilterEdges:
	if (isSchedulable_filterEdges()) {
		filterEdges();
		i++;
		goto l_CheckEdgeFiltered;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_FilterEdges;
		goto finished;
	}
l_GetBlk:
	if (numTokens_BsHor - index_BsHor >= 1 && numTokens_BsVer - index_BsVer >= 1 && numTokens_Qp - index_Qp >= 1 && numTokens_SampleIn - index_SampleIn >= 24 && isSchedulable_getBlk_launch_isHorVer()) {
		{
			int isAligned = 1;
			isAligned &= ((index_SampleIn % SIZE_SampleIn) < ((index_SampleIn + 24) % SIZE_SampleIn));
			if (isAligned) {
				getBlk_launch_isHorVer_aligned();
			} else {
				getBlk_launch_isHorVer();
			}
		}
		i++;
		goto l_GetBlk;
	} else if (numTokens_BsHor - index_BsHor >= 1 && numTokens_Qp - index_Qp >= 1 && numTokens_SampleIn - index_SampleIn >= 24 && isSchedulable_getBlk_launch_isHor()) {
		{
			int isAligned = 1;
			isAligned &= ((index_SampleIn % SIZE_SampleIn) < ((index_SampleIn + 24) % SIZE_SampleIn));
			if (isAligned) {
				getBlk_launch_isHor_aligned();
			} else {
				getBlk_launch_isHor();
			}
		}
		i++;
		goto l_GetBlk;
	} else if (numTokens_BsVer - index_BsVer >= 1 && numTokens_Qp - index_Qp >= 1 && numTokens_SampleIn - index_SampleIn >= 24 && isSchedulable_getBlk_launch_isVer()) {
		{
			int isAligned = 1;
			isAligned &= ((index_SampleIn % SIZE_SampleIn) < ((index_SampleIn + 24) % SIZE_SampleIn));
			if (isAligned) {
				getBlk_launch_isVer_aligned();
			} else {
				getBlk_launch_isVer();
			}
		}
		i++;
		goto l_GetBlk;
	} else if (numTokens_Qp - index_Qp >= 1 && numTokens_SampleIn - index_SampleIn >= 24 && isSchedulable_getBlk_launch_qp()) {
		{
			int isAligned = 1;
			isAligned &= ((index_SampleIn % SIZE_SampleIn) < ((index_SampleIn + 24) % SIZE_SampleIn));
			if (isAligned) {
				getBlk_launch_qp_aligned();
			} else {
				getBlk_launch_qp();
			}
		}
		i++;
		goto l_GetBlk;
	} else if (isSchedulable_getBlk_skip_vertEdge()) {
		getBlk_skip_vertEdge();
		i++;
		goto l_GetBlk;
	} else if (numTokens_SampleIn - index_SampleIn >= 24 && isSchedulable_getBlk_skip_horEdge()) {
		{
			int isAligned = 1;
			isAligned &= ((index_SampleIn % SIZE_SampleIn) < ((index_SampleIn + 24) % SIZE_SampleIn));
			if (isAligned) {
				getBlk_skip_horEdge_aligned();
			} else {
				getBlk_skip_horEdge();
			}
		}
		i++;
		goto l_GetBlk;
	} else if (isSchedulable_getBlk_done()) {
		getBlk_done();
		i++;
		goto l_FilterEdges;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetBlk;
		goto finished;
	}
l_GetBs4Blk:
	if (numTokens_BsHor - index_BsHor >= 1 && numTokens_BsVer - index_BsVer >= 1 && numTokens_Qp - index_Qp >= 1 && isSchedulable_getBs4Blk_launch_isHorVer()) {
		getBs4Blk_launch_isHorVer();
		i++;
		goto l_GetBs4Blk;
	} else if (numTokens_BsHor - index_BsHor >= 1 && numTokens_Qp - index_Qp >= 1 && isSchedulable_getBs4Blk_launch_isHor()) {
		getBs4Blk_launch_isHor();
		i++;
		goto l_GetBs4Blk;
	} else if (numTokens_BsVer - index_BsVer >= 1 && numTokens_Qp - index_Qp >= 1 && isSchedulable_getBs4Blk_launch_isVer()) {
		getBs4Blk_launch_isVer();
		i++;
		goto l_GetBs4Blk;
	} else if (numTokens_Qp - index_Qp >= 1 && isSchedulable_getBs4Blk_launch_qp()) {
		getBs4Blk_launch_qp();
		i++;
		goto l_GetBs4Blk;
	} else if (isSchedulable_getBs4Blk_skip()) {
		getBs4Blk_skip();
		i++;
		goto l_GetBs4Blk;
	} else if (isSchedulable_getBs4Blk_done()) {
		getBs4Blk_done();
		i++;
		goto l_FilterEdges;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetBs4Blk;
		goto finished;
	}
l_GetCuPix:
	if (numTokens_IsPicSlcLcu - index_IsPicSlcLcu >= 1 && numTokens_PicSize - index_PicSize >= 2 && numTokens_LcuSizeMax - index_LcuSizeMax >= 1 && numTokens_DBFDisable - index_DBFDisable >= 1 && numTokens_SyntaxElem - index_SyntaxElem >= 4 && isSchedulable_isNewSlc()) {
		{
			int isAligned = 1;
			isAligned &= ((index_PicSize % SIZE_PicSize) < ((index_PicSize + 2) % SIZE_PicSize));
			isAligned &= ((index_SyntaxElem % SIZE_SyntaxElem) < ((index_SyntaxElem + 4) % SIZE_SyntaxElem));
			if (isAligned) {
				isNewSlc_aligned();
			} else {
				isNewSlc();
			}
		}
		i++;
		goto l_GetNumTiles;
	} else if (numTokens_IsPicSlcLcu - index_IsPicSlcLcu >= 1 && isSchedulable_getCuPix_launch_pict()) {
		getCuPix_launch_pict();
		i++;
		goto l_GetPartition;
	} else if (numTokens_IsPicSlcLcu - index_IsPicSlcLcu >= 1 && isSchedulable_getCuPix_launch_lastColOrRow_vert()) {
		getCuPix_launch_lastColOrRow_vert();
		i++;
		goto l_GetBlk;
	} else if (isSchedulable_getCuPix_done()) {
		getCuPix_done();
		i++;
		goto l_SendSamples;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetCuPix;
		goto finished;
	}
l_GetNumTiles:
	if (numTokens_TilesCoord - index_TilesCoord >= 1 && isSchedulable_getNumTiles()) {
		getNumTiles();
		i++;
		goto l_GetTilesCoord;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetNumTiles;
		goto finished;
	}
l_GetPartition:
	if (numTokens_BsVer - index_BsVer >= 1 && numTokens_BsHor - index_BsHor >= 1 && numTokens_Qp - index_Qp >= 1 && numTokens_SampleIn - index_SampleIn >= 24 && isSchedulable_getCuPix_launch_getPart_isHorVer()) {
		{
			int isAligned = 1;
			isAligned &= ((index_SampleIn % SIZE_SampleIn) < ((index_SampleIn + 24) % SIZE_SampleIn));
			if (isAligned) {
				getCuPix_launch_getPart_isHorVer_aligned();
			} else {
				getCuPix_launch_getPart_isHorVer();
			}
		}
		i++;
		goto l_GetPartition;
	} else if (numTokens_BsHor - index_BsHor >= 1 && numTokens_Qp - index_Qp >= 1 && numTokens_SampleIn - index_SampleIn >= 24 && isSchedulable_getCuPix_launch_getPart_isHor()) {
		{
			int isAligned = 1;
			isAligned &= ((index_SampleIn % SIZE_SampleIn) < ((index_SampleIn + 24) % SIZE_SampleIn));
			if (isAligned) {
				getCuPix_launch_getPart_isHor_aligned();
			} else {
				getCuPix_launch_getPart_isHor();
			}
		}
		i++;
		goto l_GetPartition;
	} else if (numTokens_BsVer - index_BsVer >= 1 && numTokens_Qp - index_Qp >= 1 && numTokens_SampleIn - index_SampleIn >= 24 && isSchedulable_getCuPix_launch_getPart_isVer()) {
		{
			int isAligned = 1;
			isAligned &= ((index_SampleIn % SIZE_SampleIn) < ((index_SampleIn + 24) % SIZE_SampleIn));
			if (isAligned) {
				getCuPix_launch_getPart_isVer_aligned();
			} else {
				getCuPix_launch_getPart_isVer();
			}
		}
		i++;
		goto l_GetPartition;
	} else if (numTokens_Qp - index_Qp >= 1 && numTokens_SampleIn - index_SampleIn >= 24 && isSchedulable_getCuPix_launch_getPart_qp()) {
		{
			int isAligned = 1;
			isAligned &= ((index_SampleIn % SIZE_SampleIn) < ((index_SampleIn + 24) % SIZE_SampleIn));
			if (isAligned) {
				getCuPix_launch_getPart_qp_aligned();
			} else {
				getCuPix_launch_getPart_qp();
			}
		}
		i++;
		goto l_GetPartition;
	} else if (isSchedulable_getCuPix_launch_getPartDone()) {
		getCuPix_launch_getPartDone();
		i++;
		goto l_FilterEdges;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetPartition;
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
		goto l_GetCuPix;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetTilesCoord;
		goto finished;
	}
l_IsNewPict:
	if (numTokens_IsPicSlcLcu - index_IsPicSlcLcu >= 1 && numTokens_PicSize - index_PicSize >= 2 && numTokens_LcuSizeMax - index_LcuSizeMax >= 1 && numTokens_DBFDisable - index_DBFDisable >= 1 && numTokens_SyntaxElem - index_SyntaxElem >= 4 && isSchedulable_isNewPict()) {
		{
			int isAligned = 1;
			isAligned &= ((index_PicSize % SIZE_PicSize) < ((index_PicSize + 2) % SIZE_PicSize));
			isAligned &= ((index_SyntaxElem % SIZE_SyntaxElem) < ((index_SyntaxElem + 4) % SIZE_SyntaxElem));
			if (isAligned) {
				isNewPict_aligned();
			} else {
				isNewPict();
			}
		}
		i++;
		goto l_GetNumTiles;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_IsNewPict;
		goto finished;
	}
l_SendSamples:
	if (isSchedulable_sendSamples_launch_luma()) {
		int stop = 0;
		if (16 > SIZE_FiltSample - index_FiltSample + HevcDecoder_DBFilter_DeblockFilt_FiltSample->read_inds[0]) {
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
			isAligned &= ((index_FiltSample % SIZE_FiltSample) < ((index_FiltSample + 16) % SIZE_FiltSample));
			if (isAligned) {
				sendSamples_launch_luma_aligned();
			} else {
				sendSamples_launch_luma();
			}
		}
		i++;
		goto l_SendSamplesLuma;
	} else if (isSchedulable_sendSamples_done()) {
		sendSamples_done();
		i++;
		goto l_IsNewPict;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_SendSamples;
		goto finished;
	}
l_SendSamplesChr:
	if (isSchedulable_sendSamples_launch_chroma()) {
		int stop = 0;
		if (8 > SIZE_FiltSample - index_FiltSample + HevcDecoder_DBFilter_DeblockFilt_FiltSample->read_inds[0]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_SendSamplesChr;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		{
			int isAligned = 1;
			isAligned &= ((index_FiltSample % SIZE_FiltSample) < ((index_FiltSample + 8) % SIZE_FiltSample));
			if (isAligned) {
				sendSamples_launch_chroma_aligned();
			} else {
				sendSamples_launch_chroma();
			}
		}
		i++;
		goto l_SendSamplesChr;
	} else if (isSchedulable_sendSamples_launch_chromaDone()) {
		sendSamples_launch_chromaDone();
		i++;
		goto l_SendSamples;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_SendSamplesChr;
		goto finished;
	}
l_SendSamplesLuma:
	if (isSchedulable_sendSamples_launch_luma()) {
		int stop = 0;
		if (16 > SIZE_FiltSample - index_FiltSample + HevcDecoder_DBFilter_DeblockFilt_FiltSample->read_inds[0]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_SendSamplesLuma;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		{
			int isAligned = 1;
			isAligned &= ((index_FiltSample % SIZE_FiltSample) < ((index_FiltSample + 16) % SIZE_FiltSample));
			if (isAligned) {
				sendSamples_launch_luma_aligned();
			} else {
				sendSamples_launch_luma();
			}
		}
		i++;
		goto l_SendSamplesLuma;
	} else if (isSchedulable_sendSamples_launch_lumaDone()) {
		sendSamples_launch_lumaDone();
		i++;
		goto l_SendSamplesChr;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_SendSamplesLuma;
		goto finished;
	}
finished:
	read_end_BsHor();
	read_end_BsVer();
	read_end_DBFDisable();
	read_end_IsPicSlcLcu();
	read_end_LcuSizeMax();
	read_end_PicSize();
	read_end_Qp();
	read_end_SampleIn();
	read_end_SyntaxElem();
	read_end_TilesCoord();
	write_end_FiltSample();
}
