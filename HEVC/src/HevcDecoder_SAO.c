// Source file is "L/RVC/src/org/sc29/wg11/mpegh/part2/main/Filters/SaoFilter.cal"

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
extern actor_t HevcDecoder_SAO;

////////////////////////////////////////////////////////////////////////////////
// Input FIFOs
extern fifo_u8_t *HevcDecoder_SAO_IsPicSlcLcu;
extern fifo_u8_t *HevcDecoder_SAO_LcuSizeMax;
extern fifo_u8_t *HevcDecoder_SAO_LFAcrossSlcTile;
extern fifo_u16_t *HevcDecoder_SAO_PicSize;
extern fifo_u8_t *HevcDecoder_SAO_SampleIn;
extern fifo_i16_t *HevcDecoder_SAO_SaoSe;
extern fifo_u16_t *HevcDecoder_SAO_TilesCoord;

////////////////////////////////////////////////////////////////////////////////
// Input Fifo control variables
static unsigned int index_IsPicSlcLcu;
static unsigned int numTokens_IsPicSlcLcu;
#define SIZE_IsPicSlcLcu SIZE
#define tokens_IsPicSlcLcu HevcDecoder_SAO_IsPicSlcLcu->contents

extern connection_t connection_HevcDecoder_SAO_IsPicSlcLcu;
#define rate_IsPicSlcLcu connection_HevcDecoder_SAO_IsPicSlcLcu.rate

static unsigned int index_LcuSizeMax;
static unsigned int numTokens_LcuSizeMax;
#define SIZE_LcuSizeMax SIZE
#define tokens_LcuSizeMax HevcDecoder_SAO_LcuSizeMax->contents

extern connection_t connection_HevcDecoder_SAO_LcuSizeMax;
#define rate_LcuSizeMax connection_HevcDecoder_SAO_LcuSizeMax.rate

static unsigned int index_LFAcrossSlcTile;
static unsigned int numTokens_LFAcrossSlcTile;
#define SIZE_LFAcrossSlcTile SIZE
#define tokens_LFAcrossSlcTile HevcDecoder_SAO_LFAcrossSlcTile->contents

extern connection_t connection_HevcDecoder_SAO_LFAcrossSlcTile;
#define rate_LFAcrossSlcTile connection_HevcDecoder_SAO_LFAcrossSlcTile.rate

static unsigned int index_PicSize;
static unsigned int numTokens_PicSize;
#define SIZE_PicSize SIZE
#define tokens_PicSize HevcDecoder_SAO_PicSize->contents

extern connection_t connection_HevcDecoder_SAO_PicSize;
#define rate_PicSize connection_HevcDecoder_SAO_PicSize.rate

static unsigned int index_SampleIn;
static unsigned int numTokens_SampleIn;
#define SIZE_SampleIn SIZE
#define tokens_SampleIn HevcDecoder_SAO_SampleIn->contents

extern connection_t connection_HevcDecoder_SAO_SampleIn;
#define rate_SampleIn connection_HevcDecoder_SAO_SampleIn.rate

static unsigned int index_SaoSe;
static unsigned int numTokens_SaoSe;
#define SIZE_SaoSe 16384
#define tokens_SaoSe HevcDecoder_SAO_SaoSe->contents

extern connection_t connection_HevcDecoder_SAO_SaoSe;
#define rate_SaoSe connection_HevcDecoder_SAO_SaoSe.rate

static unsigned int index_TilesCoord;
static unsigned int numTokens_TilesCoord;
#define SIZE_TilesCoord SIZE
#define tokens_TilesCoord HevcDecoder_SAO_TilesCoord->contents

extern connection_t connection_HevcDecoder_SAO_TilesCoord;
#define rate_TilesCoord connection_HevcDecoder_SAO_TilesCoord.rate

////////////////////////////////////////////////////////////////////////////////
// Predecessors
extern actor_t HevcDecoder_Algo_Parser;
extern actor_t HevcDecoder_Algo_Parser;
extern actor_t HevcDecoder_Algo_Parser;
extern actor_t HevcDecoder_Algo_Parser;
extern actor_t HevcDecoder_DBFilter_DeblockFilt;
extern actor_t HevcDecoder_Algo_Parser;
extern actor_t HevcDecoder_Algo_Parser;

////////////////////////////////////////////////////////////////////////////////
// Output FIFOs
extern fifo_u8_t *HevcDecoder_SAO_FiltSample;

////////////////////////////////////////////////////////////////////////////////
// Output Fifo control variables
static unsigned int index_FiltSample;
static unsigned int numFree_FiltSample;
#define NUM_READERS_FiltSample 3
#define SIZE_FiltSample SIZE
#define tokens_FiltSample HevcDecoder_SAO_FiltSample->contents

////////////////////////////////////////////////////////////////////////////////
// Successors
extern actor_t HevcDecoder_DecodingPictureBuffer;
extern actor_t display;
extern actor_t check_MD5_MD5SplitInfo;

////////////////////////////////////////////////////////////////////////////////
// Parameter values of the instance
#define DEBUG 1


////////////////////////////////////////////////////////////////////////////////
// State variables of the actor
#define HevcDecoder_SAO_MASK_WIDTH_POW_2 4095
#define HevcDecoder_SAO_MASK_HEIGHT_POW_2 2047
#define HevcDecoder_SAO_NEW_PIC 0
#define HevcDecoder_SAO_NEW_SLC 1
#define HevcDecoder_SAO_SAO_NO_MERGE 0
#define HevcDecoder_SAO_SAO_MERGE_LEFT 1
#define HevcDecoder_SAO_SAO_MERGE_UP 2
#define DEBUG_Trace 0
#define BIT_DEPTH 8
static const i8 constHPos0[4][2] = {{-1, 1}, {0, 0}, {-1, 1}, {1, -1}};
static const i8 constVPos0[4][2] = {{0, 0}, {-1, 1}, {-1, 1}, {-1, 1}};
static const i8 edgeIdxConv[5] = {1, 2, 0, 3, 4};
static i8 signResult[3][128][128];
static i32 slcSaoCompEn[3];
static u8 PictBuffer[3][2048][4096];
static u8 origPict[3][2048][4096];
static u8 cIdx;
static u8 saoTypeIdx[64][32][3];
static i16 saoOffset[64][32][3][5];
static u8 saoEoClass[64][32][3];
static u8 saoLeftClass[64][32][3];
static u8 lcuSizeMax;
static u8 log2LcuSizeMax;
static u8 picSizeInCu[2];
static u8 picSizeInMb[2];
static u16 picSize[3][2];
static u8 xCu = 0;
static u8 yCu = 0;
static u8 xMbSent = 0;
static u8 yMbSent = 0;
static u8 xCuFilt = 0;
static u8 yCuFilt = 0;
static u16 numTokenPerLcu[2];
static u16 tokenGot;
static i16 iLoop;
static u16 numTiles;
static u16 lcuTileIdx;
static u16 tilesBeg[128][2];
static u16 tilesEnd[128][2];
static i32 filtAcrSlc[64][32];
static i32 filtAcrTile[64][32];
static i32 filtAcrAllSlc;
static i32 filtAcrAllTiles;
static i32 filtAcrCurrSlc;
static i32 filtAcrCurrTile;
static u8 numSlc[64][32];
static u8 numTile[64][32];
static i32 mbFiltered[3][257][128];
static u8 numCurrSlc;

////////////////////////////////////////////////////////////////////////////////
// Initial FSM state of the actor
enum states {
	my_state_CheckSliceEn,
	my_state_GetCuPixChrFilt,
	my_state_GetCuPixChrSkipFilt,
	my_state_GetCuPixFilt,
	my_state_GetCuPixLumaFilt,
	my_state_GetCuPixLumaSkipFilt,
	my_state_GetCuPixSkipFilt,
	my_state_GetNumTilesFilt,
	my_state_GetNumTilesSkipFilt,
	my_state_GetSaoMergeFilt,
	my_state_GetSaoMergeSkipFilt,
	my_state_GetSaoTypeIdxFilt,
	my_state_GetTilesCoordFilt,
	my_state_GetTilesCoordSkipFilt,
	my_state_IsNewPict,
	my_state_SendLastSamplesFilt,
	my_state_SendLastSamplesSkipFilt,
	my_state_SendSamplesFilt,
	my_state_SendSamplesSkipFilt
};

static char *stateNames[] = {
	"CheckSliceEn",
	"GetCuPixChrFilt",
	"GetCuPixChrSkipFilt",
	"GetCuPixFilt",
	"GetCuPixLumaFilt",
	"GetCuPixLumaSkipFilt",
	"GetCuPixSkipFilt",
	"GetNumTilesFilt",
	"GetNumTilesSkipFilt",
	"GetSaoMergeFilt",
	"GetSaoMergeSkipFilt",
	"GetSaoTypeIdxFilt",
	"GetTilesCoordFilt",
	"GetTilesCoordSkipFilt",
	"IsNewPict",
	"SendLastSamplesFilt",
	"SendLastSamplesSkipFilt",
	"SendSamplesFilt",
	"SendSamplesSkipFilt"
};

static enum states _FSM_state;



////////////////////////////////////////////////////////////////////////////////
// Token functions
static void read_IsPicSlcLcu() {
	index_IsPicSlcLcu = HevcDecoder_SAO_IsPicSlcLcu->read_inds[0];
	numTokens_IsPicSlcLcu = index_IsPicSlcLcu + fifo_u8_get_num_tokens(HevcDecoder_SAO_IsPicSlcLcu, 0);
}

static void read_end_IsPicSlcLcu() {
	HevcDecoder_SAO_IsPicSlcLcu->read_inds[0] = index_IsPicSlcLcu;
}
static void read_LcuSizeMax() {
	index_LcuSizeMax = HevcDecoder_SAO_LcuSizeMax->read_inds[1];
	numTokens_LcuSizeMax = index_LcuSizeMax + fifo_u8_get_num_tokens(HevcDecoder_SAO_LcuSizeMax, 1);
}

static void read_end_LcuSizeMax() {
	HevcDecoder_SAO_LcuSizeMax->read_inds[1] = index_LcuSizeMax;
}
static void read_LFAcrossSlcTile() {
	index_LFAcrossSlcTile = HevcDecoder_SAO_LFAcrossSlcTile->read_inds[0];
	numTokens_LFAcrossSlcTile = index_LFAcrossSlcTile + fifo_u8_get_num_tokens(HevcDecoder_SAO_LFAcrossSlcTile, 0);
}

static void read_end_LFAcrossSlcTile() {
	HevcDecoder_SAO_LFAcrossSlcTile->read_inds[0] = index_LFAcrossSlcTile;
}
static void read_PicSize() {
	index_PicSize = HevcDecoder_SAO_PicSize->read_inds[2];
	numTokens_PicSize = index_PicSize + fifo_u16_get_num_tokens(HevcDecoder_SAO_PicSize, 2);
}

static void read_end_PicSize() {
	HevcDecoder_SAO_PicSize->read_inds[2] = index_PicSize;
}
static void read_SampleIn() {
	index_SampleIn = HevcDecoder_SAO_SampleIn->read_inds[0];
	numTokens_SampleIn = index_SampleIn + fifo_u8_get_num_tokens(HevcDecoder_SAO_SampleIn, 0);
}

static void read_end_SampleIn() {
	HevcDecoder_SAO_SampleIn->read_inds[0] = index_SampleIn;
}
static void read_SaoSe() {
	index_SaoSe = HevcDecoder_SAO_SaoSe->read_inds[0];
	numTokens_SaoSe = index_SaoSe + fifo_i16_get_num_tokens(HevcDecoder_SAO_SaoSe, 0);
}

static void read_end_SaoSe() {
	HevcDecoder_SAO_SaoSe->read_inds[0] = index_SaoSe;
}
static void read_TilesCoord() {
	index_TilesCoord = HevcDecoder_SAO_TilesCoord->read_inds[1];
	numTokens_TilesCoord = index_TilesCoord + fifo_u16_get_num_tokens(HevcDecoder_SAO_TilesCoord, 1);
}

static void read_end_TilesCoord() {
	HevcDecoder_SAO_TilesCoord->read_inds[1] = index_TilesCoord;
}

static void write_FiltSample() {
	index_FiltSample = HevcDecoder_SAO_FiltSample->write_ind;
	numFree_FiltSample = index_FiltSample + fifo_u8_get_room(HevcDecoder_SAO_FiltSample, NUM_READERS_FiltSample, SIZE_FiltSample);
}

static void write_end_FiltSample() {
	HevcDecoder_SAO_FiltSample->write_ind = index_FiltSample;
}

////////////////////////////////////////////////////////////////////////////////
// Functions/procedures
static i32 HevcDecoder_SAO_min(i32 a, i32 b);
static i8 HevcDecoder_SAO_Sign3(i32 value);
static i32 HevcDecoder_SAO_clip_i32(i32 Value, i32 minVal, i32 maxVal);
static i32 lcuFiltIsPictureBorder();
static void saveLcuBorder(u8 cIdx);
static void sendFilteredLcu(u32 xIdx, u32 yIdx, u32 cIdx);
static void nextLcuAddress();
static void nextMbAddr();
static void revertFiltering(u8 saoTypeIdxBorder[8], u8 lcuSizeMax, u16 idxOrig[2], i16 idxMax[2], u8 cIdx, u8 newPix[66][66]);
static void putBackFilteredPix(u8 saoTypeIdxBorder[8], u8 lcuSizeMax, u16 idxOrig[2], i16 idxMax[2], u8 cIdx, u8 newPix[66][66]);
static void resetTilesOrSliceEdgeLuma(u16 rx, u16 ry, i16 idxMin[2], i16 idxMax[2], i8 xOff[2], i8 yOff[2]);
static void resetTilesOrSliceEdgeChroma(u16 rx, u16 ry, u8 cIdx, u16 idxMin[2], u16 idxMax[2], i8 xOff[2], i8 yOff[2]);
static void saoFilterEdge(u8 saoEoClasss, u8 cIdx, u8 cIdxOffset, u16 idxMin[2], u8 lcuSizeMax, u16 picSize[2], i32 lcuIsPictBorder, i32 saoOff[5], i32 filtAcrossSlcAndTiles, u8 origPict[3][2048][4096], u8 PictBuffer[3][2048][4096], u8 saoTypeIdxBorder[8]);
static void saoFilterEdgeLuma_Horiz(u16 idxMin[2], u8 lcuSizeMax, u16 picSize[2], i32 lcuIsPictBorder, i32 saoOffset[5], i32 filtAcrossSlcAndTiles, u8 saoTypeIdxBorder[8]);
static void saoFilterEdgeLuma_Vert(u16 idxMin[2], u8 lcuSizeMax, u16 picSize[2], i32 lcuIsPictBorder, i32 saoOffset[5], i32 filtAcrossSlcAndTiles, u8 saoTypeIdxBorder[8]);
static void saoFilterEdgeLuma_Diag(u16 idxOrig[2], u8 lcuSizeMax, u16 picSize[2], i32 lcuIsPictBorder, i32 saoOffset[5], i32 filtAcrossSlcAndTiles, u8 saoTypeIdxBorder[8]);
static void saoBandFilter(u8 saoLeftClass, i32 saoOffset[5], u8 cIdx, u8 cIdxOffset, i16 idxMin[2], i16 idxMax[2], u8 PictBuffer[3][2048][4096]);
static void codingTreeBlockModif(u16 rx, u16 ry, u8 cIdx, u16 picSize[2], i32 lcuIsPictBorder);
static void saoFilterEdgeChroma_Horiz(u16 rx, u16 ry, u8 cIdx, u16 picSize[2], i32 lcuIsPictBorder, u8 saoTypeIdxBorder[8]);
static void saoFilterEdgeChroma_Vert(u16 rx, u16 ry, u8 cIdx, u16 picSize[2], i32 lcuIsPictBorder, u8 saoTypeIdxBorder[8]);
static void saoFilterEdgeChroma_Diag(u16 rx, u16 ry, u8 cIdx, u16 picSize[2], i32 lcuIsPictBorder, u8 saoTypeIdxBorder[8]);
static void filtPrevLcu();
static void sampAdapOffFilt(u32 cIdx);

static i32 HevcDecoder_SAO_min(i32 a, i32 b) {
	i32 tmp_if;

	if (a < b) {
		tmp_if = a;
	} else {
		tmp_if = b;
	}
	return tmp_if;
}
static i8 HevcDecoder_SAO_Sign3(i32 value) {
	i8 tmp_if;

	if (value > 0) {
		tmp_if = 1;
	} else {
		if (value == 0) {
			tmp_if = 0;
		} else {
			tmp_if = -1;
		}
	}
	return tmp_if;
}
static i32 HevcDecoder_SAO_clip_i32(i32 Value, i32 minVal, i32 maxVal) {
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
static i32 lcuFiltIsPictureBorder() {
	u8 local_xCuFilt;
	u8 local_yCuFilt;
	u8 tmp_picSizeInCu;
	u8 tmp_picSizeInCu0;

	local_xCuFilt = xCuFilt;
	local_yCuFilt = yCuFilt;
	local_xCuFilt = xCuFilt;
	tmp_picSizeInCu = picSizeInCu[0];
	local_yCuFilt = yCuFilt;
	tmp_picSizeInCu0 = picSizeInCu[1];
	return local_xCuFilt == 0 || local_yCuFilt == 0 || local_xCuFilt + 1 >= tmp_picSizeInCu || local_yCuFilt + 1 >= tmp_picSizeInCu0;
}
static void saveLcuBorder(u8 cIdx) {
	u8 local_xCu;
	u8 local_log2LcuSizeMax;
	u8 local_yCu;
	u16 addrBeg[2];
	u8 local_lcuSizeMax;
	u16 addrEnd[2];
	u16 tmp_addrBeg;
	u16 tmp_addrBeg0;
	u16 tmp_addrBeg1;
	u16 tmp_addrBeg2;
	u8 tmp_PictBuffer;
	u16 local_lcuTileIdx;
	u16 tmp_tilesBeg;
	u32 x;
	u16 tmp_addrEnd;
	u16 tmp_addrBeg3;
	u16 tmp_addrBeg4;
	u8 tmp_PictBuffer0;
	u8 tmp_saoTypeIdx;
	u8 tmp_saoEoClass;
	u32 x0;
	u16 tmp_addrBeg5;
	u16 tmp_addrEnd0;
	u16 tmp_addrBeg6;
	u16 tmp_addrBeg7;
	u8 tmp_PictBuffer1;
	u32 x1;
	u16 tmp_addrEnd1;
	u16 tmp_addrEnd2;
	u16 tmp_addrEnd3;
	u8 tmp_PictBuffer2;
	u16 tmp_tilesBeg0;
	u32 y;
	u16 tmp_addrEnd4;
	u16 tmp_addrBeg8;
	u16 tmp_addrBeg9;
	u8 tmp_PictBuffer3;
	u8 tmp_saoTypeIdx0;
	u8 tmp_saoEoClass0;
	u32 y0;
	u16 tmp_addrBeg10;
	u16 tmp_addrEnd5;
	u16 tmp_addrBeg11;
	u16 tmp_addrBeg12;
	u8 tmp_PictBuffer4;
	u32 y1;
	u16 tmp_addrEnd6;
	u16 tmp_addrEnd7;
	u16 tmp_addrEnd8;
	u8 tmp_PictBuffer5;
	u16 tmp_addrBeg13;
	u16 tmp_addrBeg14;
	u16 tmp_addrEnd9;
	u16 tmp_addrEnd10;
	u16 tmp_addrBeg15;
	u16 tmp_addrBeg16;
	u16 tmp_addrBeg17;
	u16 tmp_addrBeg18;
	u8 tmp_PictBuffer6;
	u16 tmp_tilesBeg1;
	u32 x2;
	u16 tmp_addrEnd11;
	u16 tmp_addrBeg19;
	u16 tmp_addrBeg20;
	u8 tmp_PictBuffer7;
	u8 tmp_saoTypeIdx1;
	u8 tmp_saoEoClass1;
	u32 x3;
	u16 tmp_addrBeg21;
	u16 tmp_addrEnd12;
	u16 tmp_addrBeg22;
	u16 tmp_addrBeg23;
	u8 tmp_PictBuffer8;
	u32 x4;
	u16 tmp_addrEnd13;
	u16 tmp_addrEnd14;
	u16 tmp_addrEnd15;
	u8 tmp_PictBuffer9;
	u16 tmp_tilesBeg2;
	u32 y2;
	u16 tmp_addrEnd16;
	u16 tmp_addrBeg24;
	u16 tmp_addrBeg25;
	u8 tmp_PictBuffer10;
	u8 tmp_saoTypeIdx2;
	u8 tmp_saoEoClass2;
	u32 y3;
	u16 tmp_addrBeg26;
	u16 tmp_addrEnd17;
	u16 tmp_addrBeg27;
	u16 tmp_addrBeg28;
	u8 tmp_PictBuffer11;
	u32 y4;
	u16 tmp_addrEnd18;
	u16 tmp_addrEnd19;
	u16 tmp_addrEnd20;
	u8 tmp_PictBuffer12;
	u16 tmp_addrBeg29;
	u16 tmp_addrBeg30;
	u16 tmp_addrBeg31;
	u16 tmp_addrBeg32;
	u8 tmp_PictBuffer13;
	u16 tmp_tilesBeg3;
	u32 x5;
	u16 tmp_addrEnd21;
	u16 tmp_addrBeg33;
	u16 tmp_addrBeg34;
	u8 tmp_PictBuffer14;
	u8 tmp_saoTypeIdx3;
	u8 tmp_saoEoClass3;
	u32 x6;
	u16 tmp_addrBeg35;
	u16 tmp_addrEnd22;
	u16 tmp_addrBeg36;
	u16 tmp_addrBeg37;
	u8 tmp_PictBuffer15;
	u32 x7;
	u16 tmp_addrEnd23;
	u16 tmp_addrEnd24;
	u16 tmp_addrEnd25;
	u8 tmp_PictBuffer16;
	u16 tmp_tilesBeg4;
	u32 y5;
	u16 tmp_addrEnd26;
	u16 tmp_addrBeg38;
	u16 tmp_addrBeg39;
	u8 tmp_PictBuffer17;
	u8 tmp_saoTypeIdx4;
	u8 tmp_saoEoClass4;
	u32 y6;
	u16 tmp_addrBeg40;
	u16 tmp_addrEnd27;
	u16 tmp_addrBeg41;
	u16 tmp_addrBeg42;
	u8 tmp_PictBuffer18;
	u32 y7;
	u16 tmp_addrEnd28;
	u16 tmp_addrEnd29;
	u16 tmp_addrEnd30;
	u8 tmp_PictBuffer19;

	local_xCu = xCu;
	local_log2LcuSizeMax = log2LcuSizeMax;
	addrBeg[0] = local_xCu << local_log2LcuSizeMax;
	local_yCu = yCu;
	local_log2LcuSizeMax = log2LcuSizeMax;
	addrBeg[1] = local_yCu << local_log2LcuSizeMax;
	local_xCu = xCu;
	local_log2LcuSizeMax = log2LcuSizeMax;
	local_lcuSizeMax = lcuSizeMax;
	addrEnd[0] = (local_xCu << local_log2LcuSizeMax) + local_lcuSizeMax - 1;
	local_yCu = yCu;
	local_log2LcuSizeMax = log2LcuSizeMax;
	local_lcuSizeMax = lcuSizeMax;
	addrEnd[1] = (local_yCu << local_log2LcuSizeMax) + local_lcuSizeMax - 1;
	if (cIdx == 0) {
		tmp_addrBeg = addrBeg[1];
		tmp_addrBeg0 = addrBeg[0];
		tmp_addrBeg1 = addrBeg[1];
		tmp_addrBeg2 = addrBeg[0];
		tmp_PictBuffer = PictBuffer[0][tmp_addrBeg1][tmp_addrBeg2];
		origPict[0][tmp_addrBeg][tmp_addrBeg0] = tmp_PictBuffer;
		local_yCu = yCu;
		if (local_yCu > 0) {
			local_lcuTileIdx = lcuTileIdx;
			tmp_tilesBeg = tilesBeg[local_lcuTileIdx][1];
			local_yCu = yCu;
			if (tmp_tilesBeg == local_yCu) {
				x = addrBeg[0];
				tmp_addrEnd = addrEnd[0];
				while (x <= tmp_addrEnd - 1) {
					tmp_addrBeg3 = addrBeg[1];
					tmp_addrBeg4 = addrBeg[1];
					tmp_PictBuffer0 = PictBuffer[0][tmp_addrBeg4][x];
					origPict[0][tmp_addrBeg3][x] = tmp_PictBuffer0;
					x = x + 1;
				}
			} else {
				local_xCu = xCu;
				local_yCu = yCu;
				tmp_saoTypeIdx = saoTypeIdx[local_xCu][local_yCu - 1][0];
				local_xCu = xCu;
				local_yCu = yCu;
				tmp_saoEoClass = saoEoClass[local_xCu][local_yCu - 1][0];
				if (tmp_saoTypeIdx == 2 && tmp_saoEoClass != 0) {
					tmp_addrBeg5 = addrBeg[0];
					x0 = tmp_addrBeg5 + 1;
					tmp_addrEnd0 = addrEnd[0];
					while (x0 <= tmp_addrEnd0 - 1) {
						tmp_addrBeg6 = addrBeg[1];
						tmp_addrBeg7 = addrBeg[1];
						tmp_PictBuffer1 = PictBuffer[0][tmp_addrBeg7][x0];
						origPict[0][tmp_addrBeg6][x0] = tmp_PictBuffer1;
						x0 = x0 + 1;
					}
				}
			}
		}
		x1 = addrBeg[0];
		tmp_addrEnd1 = addrEnd[0];
		while (x1 <= tmp_addrEnd1) {
			tmp_addrEnd2 = addrEnd[1];
			tmp_addrEnd3 = addrEnd[1];
			tmp_PictBuffer2 = PictBuffer[0][tmp_addrEnd3][x1];
			origPict[0][tmp_addrEnd2][x1] = tmp_PictBuffer2;
			x1 = x1 + 1;
		}
		local_xCu = xCu;
		if (local_xCu > 0) {
			local_lcuTileIdx = lcuTileIdx;
			tmp_tilesBeg0 = tilesBeg[local_lcuTileIdx][0];
			local_xCu = xCu;
			if (tmp_tilesBeg0 == local_xCu) {
				y = addrBeg[1];
				tmp_addrEnd4 = addrEnd[1];
				while (y <= tmp_addrEnd4 - 1) {
					tmp_addrBeg8 = addrBeg[0];
					tmp_addrBeg9 = addrBeg[0];
					tmp_PictBuffer3 = PictBuffer[0][y][tmp_addrBeg9];
					origPict[0][y][tmp_addrBeg8] = tmp_PictBuffer3;
					y = y + 1;
				}
			} else {
				local_xCu = xCu;
				local_yCu = yCu;
				tmp_saoTypeIdx0 = saoTypeIdx[local_xCu - 1][local_yCu][0];
				local_xCu = xCu;
				local_yCu = yCu;
				tmp_saoEoClass0 = saoEoClass[local_xCu - 1][local_yCu][0];
				if (tmp_saoTypeIdx0 == 2 && tmp_saoEoClass0 != 1) {
					tmp_addrBeg10 = addrBeg[1];
					y0 = tmp_addrBeg10 + 1;
					tmp_addrEnd5 = addrEnd[1];
					while (y0 <= tmp_addrEnd5 - 1) {
						tmp_addrBeg11 = addrBeg[0];
						tmp_addrBeg12 = addrBeg[0];
						tmp_PictBuffer4 = PictBuffer[0][y0][tmp_addrBeg12];
						origPict[0][y0][tmp_addrBeg11] = tmp_PictBuffer4;
						y0 = y0 + 1;
					}
				}
			}
		}
		y1 = addrBeg[1];
		tmp_addrEnd6 = addrEnd[1];
		while (y1 <= tmp_addrEnd6 - 1) {
			tmp_addrEnd7 = addrEnd[0];
			tmp_addrEnd8 = addrEnd[0];
			tmp_PictBuffer5 = PictBuffer[0][y1][tmp_addrEnd8];
			origPict[0][y1][tmp_addrEnd7] = tmp_PictBuffer5;
			y1 = y1 + 1;
		}
	}
	tmp_addrBeg13 = addrBeg[0];
	addrBeg[0] = tmp_addrBeg13 >> 1;
	tmp_addrBeg14 = addrBeg[1];
	addrBeg[1] = tmp_addrBeg14 >> 1;
	tmp_addrEnd9 = addrEnd[0];
	addrEnd[0] = tmp_addrEnd9 >> 1;
	tmp_addrEnd10 = addrEnd[1];
	addrEnd[1] = tmp_addrEnd10 >> 1;
	if (cIdx == 1) {
		tmp_addrBeg15 = addrBeg[1];
		tmp_addrBeg16 = addrBeg[0];
		tmp_addrBeg17 = addrBeg[1];
		tmp_addrBeg18 = addrBeg[0];
		tmp_PictBuffer6 = PictBuffer[1][tmp_addrBeg17][tmp_addrBeg18];
		origPict[1][tmp_addrBeg15][tmp_addrBeg16] = tmp_PictBuffer6;
		local_yCu = yCu;
		if (local_yCu > 0) {
			local_lcuTileIdx = lcuTileIdx;
			tmp_tilesBeg1 = tilesBeg[local_lcuTileIdx][1];
			local_yCu = yCu;
			if (tmp_tilesBeg1 == local_yCu) {
				x2 = addrBeg[0];
				tmp_addrEnd11 = addrEnd[0];
				while (x2 <= tmp_addrEnd11 - 1) {
					tmp_addrBeg19 = addrBeg[1];
					tmp_addrBeg20 = addrBeg[1];
					tmp_PictBuffer7 = PictBuffer[1][tmp_addrBeg20][x2];
					origPict[1][tmp_addrBeg19][x2] = tmp_PictBuffer7;
					x2 = x2 + 1;
				}
			} else {
				local_xCu = xCu;
				local_yCu = yCu;
				tmp_saoTypeIdx1 = saoTypeIdx[local_xCu][local_yCu - 1][1];
				local_xCu = xCu;
				local_yCu = yCu;
				tmp_saoEoClass1 = saoEoClass[local_xCu][local_yCu - 1][1];
				if (tmp_saoTypeIdx1 == 2 && tmp_saoEoClass1 != 0) {
					tmp_addrBeg21 = addrBeg[0];
					x3 = tmp_addrBeg21 + 1;
					tmp_addrEnd12 = addrEnd[0];
					while (x3 <= tmp_addrEnd12 - 1) {
						tmp_addrBeg22 = addrBeg[1];
						tmp_addrBeg23 = addrBeg[1];
						tmp_PictBuffer8 = PictBuffer[1][tmp_addrBeg23][x3];
						origPict[1][tmp_addrBeg22][x3] = tmp_PictBuffer8;
						x3 = x3 + 1;
					}
				}
			}
		}
		x4 = addrBeg[0];
		tmp_addrEnd13 = addrEnd[0];
		while (x4 <= tmp_addrEnd13) {
			tmp_addrEnd14 = addrEnd[1];
			tmp_addrEnd15 = addrEnd[1];
			tmp_PictBuffer9 = PictBuffer[1][tmp_addrEnd15][x4];
			origPict[1][tmp_addrEnd14][x4] = tmp_PictBuffer9;
			x4 = x4 + 1;
		}
		local_xCu = xCu;
		if (local_xCu > 0) {
			local_lcuTileIdx = lcuTileIdx;
			tmp_tilesBeg2 = tilesBeg[local_lcuTileIdx][0];
			local_xCu = xCu;
			if (tmp_tilesBeg2 == local_xCu) {
				y2 = addrBeg[1];
				tmp_addrEnd16 = addrEnd[1];
				while (y2 <= tmp_addrEnd16 - 1) {
					tmp_addrBeg24 = addrBeg[0];
					tmp_addrBeg25 = addrBeg[0];
					tmp_PictBuffer10 = PictBuffer[1][y2][tmp_addrBeg25];
					origPict[1][y2][tmp_addrBeg24] = tmp_PictBuffer10;
					y2 = y2 + 1;
				}
			} else {
				local_xCu = xCu;
				local_yCu = yCu;
				tmp_saoTypeIdx2 = saoTypeIdx[local_xCu - 1][local_yCu][1];
				local_xCu = xCu;
				local_yCu = yCu;
				tmp_saoEoClass2 = saoEoClass[local_xCu - 1][local_yCu][1];
				if (tmp_saoTypeIdx2 == 2 && tmp_saoEoClass2 != 1) {
					tmp_addrBeg26 = addrBeg[1];
					y3 = tmp_addrBeg26 + 1;
					tmp_addrEnd17 = addrEnd[1];
					while (y3 <= tmp_addrEnd17 - 1) {
						tmp_addrBeg27 = addrBeg[0];
						tmp_addrBeg28 = addrBeg[0];
						tmp_PictBuffer11 = PictBuffer[1][y3][tmp_addrBeg28];
						origPict[1][y3][tmp_addrBeg27] = tmp_PictBuffer11;
						y3 = y3 + 1;
					}
				}
			}
		}
		y4 = addrBeg[1];
		tmp_addrEnd18 = addrEnd[1];
		while (y4 <= tmp_addrEnd18 - 1) {
			tmp_addrEnd19 = addrEnd[0];
			tmp_addrEnd20 = addrEnd[0];
			tmp_PictBuffer12 = PictBuffer[1][y4][tmp_addrEnd20];
			origPict[1][y4][tmp_addrEnd19] = tmp_PictBuffer12;
			y4 = y4 + 1;
		}
	}
	if (cIdx == 2) {
		tmp_addrBeg29 = addrBeg[1];
		tmp_addrBeg30 = addrBeg[0];
		tmp_addrBeg31 = addrBeg[1];
		tmp_addrBeg32 = addrBeg[0];
		tmp_PictBuffer13 = PictBuffer[2][tmp_addrBeg31][tmp_addrBeg32];
		origPict[2][tmp_addrBeg29][tmp_addrBeg30] = tmp_PictBuffer13;
		local_yCu = yCu;
		if (local_yCu > 0) {
			local_lcuTileIdx = lcuTileIdx;
			tmp_tilesBeg3 = tilesBeg[local_lcuTileIdx][1];
			local_yCu = yCu;
			if (tmp_tilesBeg3 == local_yCu) {
				x5 = addrBeg[0];
				tmp_addrEnd21 = addrEnd[0];
				while (x5 <= tmp_addrEnd21 - 1) {
					tmp_addrBeg33 = addrBeg[1];
					tmp_addrBeg34 = addrBeg[1];
					tmp_PictBuffer14 = PictBuffer[2][tmp_addrBeg34][x5];
					origPict[2][tmp_addrBeg33][x5] = tmp_PictBuffer14;
					x5 = x5 + 1;
				}
			} else {
				local_xCu = xCu;
				local_yCu = yCu;
				tmp_saoTypeIdx3 = saoTypeIdx[local_xCu][local_yCu - 1][1];
				local_xCu = xCu;
				local_yCu = yCu;
				tmp_saoEoClass3 = saoEoClass[local_xCu][local_yCu - 1][1];
				if (tmp_saoTypeIdx3 == 2 && tmp_saoEoClass3 != 0) {
					tmp_addrBeg35 = addrBeg[0];
					x6 = tmp_addrBeg35 + 1;
					tmp_addrEnd22 = addrEnd[0];
					while (x6 <= tmp_addrEnd22 - 1) {
						tmp_addrBeg36 = addrBeg[1];
						tmp_addrBeg37 = addrBeg[1];
						tmp_PictBuffer15 = PictBuffer[2][tmp_addrBeg37][x6];
						origPict[2][tmp_addrBeg36][x6] = tmp_PictBuffer15;
						x6 = x6 + 1;
					}
				}
			}
		}
		x7 = addrBeg[0];
		tmp_addrEnd23 = addrEnd[0];
		while (x7 <= tmp_addrEnd23) {
			tmp_addrEnd24 = addrEnd[1];
			tmp_addrEnd25 = addrEnd[1];
			tmp_PictBuffer16 = PictBuffer[2][tmp_addrEnd25][x7];
			origPict[2][tmp_addrEnd24][x7] = tmp_PictBuffer16;
			x7 = x7 + 1;
		}
		local_xCu = xCu;
		if (local_xCu > 0) {
			local_lcuTileIdx = lcuTileIdx;
			tmp_tilesBeg4 = tilesBeg[local_lcuTileIdx][0];
			local_xCu = xCu;
			if (tmp_tilesBeg4 == local_xCu) {
				y5 = addrBeg[1];
				tmp_addrEnd26 = addrEnd[1];
				while (y5 <= tmp_addrEnd26 - 1) {
					tmp_addrBeg38 = addrBeg[0];
					tmp_addrBeg39 = addrBeg[0];
					tmp_PictBuffer17 = PictBuffer[2][y5][tmp_addrBeg39];
					origPict[2][y5][tmp_addrBeg38] = tmp_PictBuffer17;
					y5 = y5 + 1;
				}
			} else {
				local_xCu = xCu;
				local_yCu = yCu;
				tmp_saoTypeIdx4 = saoTypeIdx[local_xCu - 1][local_yCu][1];
				local_xCu = xCu;
				local_yCu = yCu;
				tmp_saoEoClass4 = saoEoClass[local_xCu - 1][local_yCu][1];
				if (tmp_saoTypeIdx4 == 2 && tmp_saoEoClass4 != 1) {
					tmp_addrBeg40 = addrBeg[1];
					y6 = tmp_addrBeg40 + 1;
					tmp_addrEnd27 = addrEnd[1];
					while (y6 <= tmp_addrEnd27 - 1) {
						tmp_addrBeg41 = addrBeg[0];
						tmp_addrBeg42 = addrBeg[0];
						tmp_PictBuffer18 = PictBuffer[2][y6][tmp_addrBeg42];
						origPict[2][y6][tmp_addrBeg41] = tmp_PictBuffer18;
						y6 = y6 + 1;
					}
				}
			}
		}
		y7 = addrBeg[1];
		tmp_addrEnd28 = addrEnd[1];
		while (y7 <= tmp_addrEnd28 - 1) {
			tmp_addrEnd29 = addrEnd[0];
			tmp_addrEnd30 = addrEnd[0];
			tmp_PictBuffer19 = PictBuffer[2][y7][tmp_addrEnd30];
			origPict[2][y7][tmp_addrEnd29] = tmp_PictBuffer19;
			y7 = y7 + 1;
		}
	}
}
static void sendFilteredLcu(u32 xIdx, u32 yIdx, u32 cIdx) {
	u8 local_lcuSizeMax;
	u32 nbBlkPerLcu;
	i32 x;
	i32 y;

	local_lcuSizeMax = lcuSizeMax;
	if (local_lcuSizeMax == 64) {
		nbBlkPerLcu = 4;
	} else {
		local_lcuSizeMax = lcuSizeMax;
		if (local_lcuSizeMax == 32) {
			nbBlkPerLcu = 2;
		} else {
			nbBlkPerLcu = 1;
		}
	}
	x = 0;
	while (x <= nbBlkPerLcu - 1) {
		y = 0;
		while (y <= nbBlkPerLcu - 1) {
			mbFiltered[cIdx][(xIdx >> 4) + x][(yIdx >> 4) + y] = 1;
			y = y + 1;
		}
		x = x + 1;
	}
}
static void nextLcuAddress() {
	u8 local_xCu;
	u16 local_lcuTileIdx;
	u16 tmp_tilesEnd;
	u16 tmp_tilesBeg;
	u8 local_yCu;
	u16 tmp_tilesEnd0;
	u16 tmp_tilesBeg0;
	u16 tmp_tilesBeg1;

	local_xCu = xCu;
	xCu = local_xCu + 1;
	local_xCu = xCu;
	local_lcuTileIdx = lcuTileIdx;
	tmp_tilesEnd = tilesEnd[local_lcuTileIdx][0];
	if (local_xCu == tmp_tilesEnd) {
		local_lcuTileIdx = lcuTileIdx;
		tmp_tilesBeg = tilesBeg[local_lcuTileIdx][0];
		xCu = tmp_tilesBeg;
		local_yCu = yCu;
		yCu = local_yCu + 1;
		local_yCu = yCu;
		local_lcuTileIdx = lcuTileIdx;
		tmp_tilesEnd0 = tilesEnd[local_lcuTileIdx][1];
		if (local_yCu == tmp_tilesEnd0) {
			local_lcuTileIdx = lcuTileIdx;
			lcuTileIdx = local_lcuTileIdx + 1;
			local_lcuTileIdx = lcuTileIdx;
			tmp_tilesBeg0 = tilesBeg[local_lcuTileIdx][0];
			xCu = tmp_tilesBeg0;
			local_lcuTileIdx = lcuTileIdx;
			tmp_tilesBeg1 = tilesBeg[local_lcuTileIdx][1];
			yCu = tmp_tilesBeg1;
		}
	}
}
static void nextMbAddr() {
	u8 local_xMbSent;
	u8 tmp_picSizeInMb;
	u8 local_yMbSent;

	local_xMbSent = xMbSent;
	xMbSent = local_xMbSent + 1;
	local_xMbSent = xMbSent;
	tmp_picSizeInMb = picSizeInMb[0];
	if (local_xMbSent == tmp_picSizeInMb) {
		xMbSent = 0;
		local_yMbSent = yMbSent;
		yMbSent = local_yMbSent + 1;
	}
}
static void revertFiltering(u8 saoTypeIdxBorder[8], u8 lcuSizeMax, u16 idxOrig[2], i16 idxMax[2], u8 cIdx, u8 newPix[66][66]) {
	u8 tmp_saoTypeIdxBorder;
	u16 tmp_idxOrig;
	u16 tmp_idxOrig0;
	u16 tmp_idxOrig1;
	u16 tmp_idxOrig2;
	u8 tmp_PictBuffer;
	u16 tmp_idxOrig3;
	u16 tmp_idxOrig4;
	u16 tmp_idxOrig5;
	u16 tmp_idxOrig6;
	u8 tmp_origPict;
	u8 tmp_saoTypeIdxBorder0;
	i16 tmp_idxMax;
	u16 tmp_idxOrig7;
	u16 tmp_idxOrig8;
	u16 tmp_idxOrig9;
	u8 tmp_PictBuffer0;
	u16 tmp_idxOrig10;
	u16 tmp_idxOrig11;
	u16 tmp_idxOrig12;
	u16 tmp_idxOrig13;
	u8 tmp_origPict0;
	u8 tmp_saoTypeIdxBorder1;
	u16 tmp_idxOrig14;
	i16 tmp_idxMax0;
	u16 tmp_idxOrig15;
	u16 tmp_idxOrig16;
	u8 tmp_PictBuffer1;
	u16 tmp_idxOrig17;
	u16 tmp_idxOrig18;
	u16 tmp_idxOrig19;
	u16 tmp_idxOrig20;
	u8 tmp_origPict1;
	u8 tmp_saoTypeIdxBorder2;
	i16 tmp_idxMax1;
	i16 tmp_idxMax2;
	u16 tmp_idxOrig21;
	u16 tmp_idxOrig22;
	u8 tmp_PictBuffer2;
	u16 tmp_idxOrig23;
	u16 tmp_idxOrig24;
	u16 tmp_idxOrig25;
	u16 tmp_idxOrig26;
	u8 tmp_origPict2;
	u8 tmp_saoTypeIdxBorder3;
	u16 tmp_idxOrig27;
	i32 y;
	u16 tmp_idxOrig28;
	u16 tmp_idxOrig29;
	u16 tmp_idxOrig30;
	u8 tmp_PictBuffer3;
	u16 tmp_idxOrig31;
	u16 tmp_idxOrig32;
	u8 tmp_origPict3;
	u8 tmp_saoTypeIdxBorder4;
	i16 tmp_idxMax3;
	i32 y0;
	u16 tmp_idxOrig33;
	u16 tmp_idxOrig34;
	u16 tmp_idxOrig35;
	u8 tmp_PictBuffer4;
	u16 tmp_idxOrig36;
	u16 tmp_idxOrig37;
	u8 tmp_origPict4;
	u8 tmp_saoTypeIdxBorder5;
	u16 tmp_idxOrig38;
	i32 x;
	u16 tmp_idxOrig39;
	u16 tmp_idxOrig40;
	u16 tmp_idxOrig41;
	u8 tmp_PictBuffer5;
	u16 tmp_idxOrig42;
	u16 tmp_idxOrig43;
	u8 tmp_origPict5;
	u8 tmp_saoTypeIdxBorder6;
	i16 tmp_idxMax4;
	i32 x0;
	u16 tmp_idxOrig44;
	u16 tmp_idxOrig45;
	u16 tmp_idxOrig46;
	u8 tmp_PictBuffer6;
	u16 tmp_idxOrig47;
	u16 tmp_idxOrig48;
	u8 tmp_origPict6;

	tmp_saoTypeIdxBorder = saoTypeIdxBorder[0];
	tmp_idxOrig = idxOrig[0];
	tmp_idxOrig0 = idxOrig[1];
	if (tmp_saoTypeIdxBorder != 0 && tmp_idxOrig != 0 && tmp_idxOrig0 != 0) {
		tmp_idxOrig1 = idxOrig[1];
		tmp_idxOrig2 = idxOrig[0];
		tmp_PictBuffer = PictBuffer[cIdx][tmp_idxOrig1 - 1][tmp_idxOrig2 - 1];
		newPix[0][0] = tmp_PictBuffer;
		tmp_idxOrig3 = idxOrig[1];
		tmp_idxOrig4 = idxOrig[0];
		tmp_idxOrig5 = idxOrig[1];
		tmp_idxOrig6 = idxOrig[0];
		tmp_origPict = origPict[cIdx][tmp_idxOrig5 - 1][tmp_idxOrig6 - 1];
		PictBuffer[cIdx][tmp_idxOrig3 - 1][tmp_idxOrig4 - 1] = tmp_origPict;
	}
	tmp_saoTypeIdxBorder0 = saoTypeIdxBorder[2];
	tmp_idxMax = idxMax[0];
	tmp_idxOrig7 = idxOrig[1];
	if (tmp_saoTypeIdxBorder0 != 0 && tmp_idxMax == lcuSizeMax - 1 && tmp_idxOrig7 != 0) {
		tmp_idxOrig8 = idxOrig[1];
		tmp_idxOrig9 = idxOrig[0];
		tmp_PictBuffer0 = PictBuffer[cIdx][tmp_idxOrig8 - 1][tmp_idxOrig9 + lcuSizeMax];
		newPix[0][lcuSizeMax + 1] = tmp_PictBuffer0;
		tmp_idxOrig10 = idxOrig[1];
		tmp_idxOrig11 = idxOrig[0];
		tmp_idxOrig12 = idxOrig[1];
		tmp_idxOrig13 = idxOrig[0];
		tmp_origPict0 = origPict[cIdx][tmp_idxOrig12 - 1][tmp_idxOrig13 + lcuSizeMax];
		PictBuffer[cIdx][tmp_idxOrig10 - 1][tmp_idxOrig11 + lcuSizeMax] = tmp_origPict0;
	}
	tmp_saoTypeIdxBorder1 = saoTypeIdxBorder[6];
	tmp_idxOrig14 = idxOrig[0];
	tmp_idxMax0 = idxMax[1];
	if (tmp_saoTypeIdxBorder1 != 0 && tmp_idxOrig14 != 0 && tmp_idxMax0 == lcuSizeMax - 1) {
		tmp_idxOrig15 = idxOrig[1];
		tmp_idxOrig16 = idxOrig[0];
		tmp_PictBuffer1 = PictBuffer[cIdx][tmp_idxOrig15 + lcuSizeMax][tmp_idxOrig16 - 1];
		newPix[lcuSizeMax + 1][0] = tmp_PictBuffer1;
		tmp_idxOrig17 = idxOrig[1];
		tmp_idxOrig18 = idxOrig[0];
		tmp_idxOrig19 = idxOrig[1];
		tmp_idxOrig20 = idxOrig[0];
		tmp_origPict1 = origPict[cIdx][tmp_idxOrig19 + lcuSizeMax][tmp_idxOrig20 - 1];
		PictBuffer[cIdx][tmp_idxOrig17 + lcuSizeMax][tmp_idxOrig18 - 1] = tmp_origPict1;
	}
	tmp_saoTypeIdxBorder2 = saoTypeIdxBorder[4];
	tmp_idxMax1 = idxMax[0];
	tmp_idxMax2 = idxMax[1];
	if (tmp_saoTypeIdxBorder2 != 0 && tmp_idxMax1 == lcuSizeMax - 1 && tmp_idxMax2 == lcuSizeMax - 1) {
		tmp_idxOrig21 = idxOrig[1];
		tmp_idxOrig22 = idxOrig[0];
		tmp_PictBuffer2 = PictBuffer[cIdx][tmp_idxOrig21 + lcuSizeMax][tmp_idxOrig22 + lcuSizeMax];
		newPix[lcuSizeMax + 1][lcuSizeMax + 1] = tmp_PictBuffer2;
		tmp_idxOrig23 = idxOrig[1];
		tmp_idxOrig24 = idxOrig[0];
		tmp_idxOrig25 = idxOrig[1];
		tmp_idxOrig26 = idxOrig[0];
		tmp_origPict2 = origPict[cIdx][tmp_idxOrig25 + lcuSizeMax][tmp_idxOrig26 + lcuSizeMax];
		PictBuffer[cIdx][tmp_idxOrig23 + lcuSizeMax][tmp_idxOrig24 + lcuSizeMax] = tmp_origPict2;
	}
	tmp_saoTypeIdxBorder3 = saoTypeIdxBorder[7];
	tmp_idxOrig27 = idxOrig[0];
	if (tmp_saoTypeIdxBorder3 != 0 && tmp_idxOrig27 != 0) {
		y = idxOrig[1];
		tmp_idxOrig28 = idxOrig[1];
		while (y <= tmp_idxOrig28 + lcuSizeMax - 1) {
			tmp_idxOrig29 = idxOrig[1];
			tmp_idxOrig30 = idxOrig[0];
			tmp_PictBuffer3 = PictBuffer[cIdx][y][tmp_idxOrig30 - 1];
			newPix[y - tmp_idxOrig29 + 1][0] = tmp_PictBuffer3;
			tmp_idxOrig31 = idxOrig[0];
			tmp_idxOrig32 = idxOrig[0];
			tmp_origPict3 = origPict[cIdx][y][tmp_idxOrig32 - 1];
			PictBuffer[cIdx][y][tmp_idxOrig31 - 1] = tmp_origPict3;
			y = y + 1;
		}
	}
	tmp_saoTypeIdxBorder4 = saoTypeIdxBorder[3];
	tmp_idxMax3 = idxMax[0];
	if (tmp_saoTypeIdxBorder4 != 0 && tmp_idxMax3 == lcuSizeMax - 1) {
		y0 = idxOrig[1];
		tmp_idxOrig33 = idxOrig[1];
		while (y0 <= tmp_idxOrig33 + lcuSizeMax - 1) {
			tmp_idxOrig34 = idxOrig[1];
			tmp_idxOrig35 = idxOrig[0];
			tmp_PictBuffer4 = PictBuffer[cIdx][y0][tmp_idxOrig35 + lcuSizeMax];
			newPix[y0 - tmp_idxOrig34 + 1][lcuSizeMax + 1] = tmp_PictBuffer4;
			tmp_idxOrig36 = idxOrig[0];
			tmp_idxOrig37 = idxOrig[0];
			tmp_origPict4 = origPict[cIdx][y0][tmp_idxOrig37 + lcuSizeMax];
			PictBuffer[cIdx][y0][tmp_idxOrig36 + lcuSizeMax] = tmp_origPict4;
			y0 = y0 + 1;
		}
	}
	tmp_saoTypeIdxBorder5 = saoTypeIdxBorder[1];
	tmp_idxOrig38 = idxOrig[1];
	if (tmp_saoTypeIdxBorder5 != 0 && tmp_idxOrig38 != 0) {
		x = idxOrig[0];
		tmp_idxOrig39 = idxOrig[0];
		while (x <= tmp_idxOrig39 + lcuSizeMax - 1) {
			tmp_idxOrig40 = idxOrig[0];
			tmp_idxOrig41 = idxOrig[1];
			tmp_PictBuffer5 = PictBuffer[cIdx][tmp_idxOrig41 - 1][x];
			newPix[0][x - tmp_idxOrig40 + 1] = tmp_PictBuffer5;
			tmp_idxOrig42 = idxOrig[1];
			tmp_idxOrig43 = idxOrig[1];
			tmp_origPict5 = origPict[cIdx][tmp_idxOrig43 - 1][x];
			PictBuffer[cIdx][tmp_idxOrig42 - 1][x] = tmp_origPict5;
			x = x + 1;
		}
	}
	tmp_saoTypeIdxBorder6 = saoTypeIdxBorder[5];
	tmp_idxMax4 = idxMax[1];
	if (tmp_saoTypeIdxBorder6 != 0 && tmp_idxMax4 == lcuSizeMax - 1) {
		x0 = idxOrig[0];
		tmp_idxOrig44 = idxOrig[0];
		while (x0 <= tmp_idxOrig44 + lcuSizeMax - 1) {
			tmp_idxOrig45 = idxOrig[0];
			tmp_idxOrig46 = idxOrig[1];
			tmp_PictBuffer6 = PictBuffer[cIdx][tmp_idxOrig46 + lcuSizeMax][x0];
			newPix[lcuSizeMax + 1][x0 - (tmp_idxOrig45 - 1)] = tmp_PictBuffer6;
			tmp_idxOrig47 = idxOrig[1];
			tmp_idxOrig48 = idxOrig[1];
			tmp_origPict6 = origPict[cIdx][tmp_idxOrig48 + lcuSizeMax][x0];
			PictBuffer[cIdx][tmp_idxOrig47 + lcuSizeMax][x0] = tmp_origPict6;
			x0 = x0 + 1;
		}
	}
}
static void putBackFilteredPix(u8 saoTypeIdxBorder[8], u8 lcuSizeMax, u16 idxOrig[2], i16 idxMax[2], u8 cIdx, u8 newPix[66][66]) {
	u8 tmp_saoTypeIdxBorder;
	u16 tmp_idxOrig;
	u16 tmp_idxOrig0;
	u16 tmp_idxOrig1;
	u16 tmp_idxOrig2;
	u8 tmp_newPix;
	u8 tmp_saoTypeIdxBorder0;
	i16 tmp_idxMax;
	u16 tmp_idxOrig3;
	u16 tmp_idxOrig4;
	u16 tmp_idxOrig5;
	u8 tmp_newPix0;
	u8 tmp_saoTypeIdxBorder1;
	u16 tmp_idxOrig6;
	i16 tmp_idxMax0;
	u16 tmp_idxOrig7;
	u16 tmp_idxOrig8;
	u8 tmp_newPix1;
	u8 tmp_saoTypeIdxBorder2;
	i16 tmp_idxMax1;
	i16 tmp_idxMax2;
	u16 tmp_idxOrig9;
	u16 tmp_idxOrig10;
	u8 tmp_newPix2;
	u8 tmp_saoTypeIdxBorder3;
	u16 tmp_idxOrig11;
	i32 y;
	u16 tmp_idxOrig12;
	u16 tmp_idxOrig13;
	u16 tmp_idxOrig14;
	u8 tmp_newPix3;
	u8 tmp_saoTypeIdxBorder4;
	i16 tmp_idxMax3;
	i32 y0;
	u16 tmp_idxOrig15;
	u16 tmp_idxOrig16;
	u16 tmp_idxOrig17;
	u8 tmp_newPix4;
	u8 tmp_saoTypeIdxBorder5;
	u16 tmp_idxOrig18;
	i32 x;
	u16 tmp_idxOrig19;
	u16 tmp_idxOrig20;
	u16 tmp_idxOrig21;
	u8 tmp_newPix5;
	u8 tmp_saoTypeIdxBorder6;
	i16 tmp_idxMax4;
	i32 x0;
	u16 tmp_idxOrig22;
	u16 tmp_idxOrig23;
	u16 tmp_idxOrig24;
	u8 tmp_newPix6;

	tmp_saoTypeIdxBorder = saoTypeIdxBorder[0];
	tmp_idxOrig = idxOrig[0];
	tmp_idxOrig0 = idxOrig[1];
	if (tmp_saoTypeIdxBorder != 0 && tmp_idxOrig != 0 && tmp_idxOrig0 != 0) {
		tmp_idxOrig1 = idxOrig[1];
		tmp_idxOrig2 = idxOrig[0];
		tmp_newPix = newPix[0][0];
		PictBuffer[cIdx][tmp_idxOrig1 - 1][tmp_idxOrig2 - 1] = tmp_newPix;
	}
	tmp_saoTypeIdxBorder0 = saoTypeIdxBorder[2];
	tmp_idxMax = idxMax[0];
	tmp_idxOrig3 = idxOrig[1];
	if (tmp_saoTypeIdxBorder0 != 0 && tmp_idxMax == lcuSizeMax - 1 && tmp_idxOrig3 != 0) {
		tmp_idxOrig4 = idxOrig[1];
		tmp_idxOrig5 = idxOrig[0];
		tmp_newPix0 = newPix[0][lcuSizeMax + 1];
		PictBuffer[cIdx][tmp_idxOrig4 - 1][tmp_idxOrig5 + lcuSizeMax] = tmp_newPix0;
	}
	tmp_saoTypeIdxBorder1 = saoTypeIdxBorder[6];
	tmp_idxOrig6 = idxOrig[0];
	tmp_idxMax0 = idxMax[1];
	if (tmp_saoTypeIdxBorder1 != 0 && tmp_idxOrig6 != 0 && tmp_idxMax0 == lcuSizeMax - 1) {
		tmp_idxOrig7 = idxOrig[1];
		tmp_idxOrig8 = idxOrig[0];
		tmp_newPix1 = newPix[lcuSizeMax + 1][0];
		PictBuffer[cIdx][tmp_idxOrig7 + lcuSizeMax][tmp_idxOrig8 - 1] = tmp_newPix1;
	}
	tmp_saoTypeIdxBorder2 = saoTypeIdxBorder[4];
	tmp_idxMax1 = idxMax[0];
	tmp_idxMax2 = idxMax[1];
	if (tmp_saoTypeIdxBorder2 != 0 && tmp_idxMax1 == lcuSizeMax - 1 && tmp_idxMax2 == lcuSizeMax - 1) {
		tmp_idxOrig9 = idxOrig[1];
		tmp_idxOrig10 = idxOrig[0];
		tmp_newPix2 = newPix[lcuSizeMax + 1][lcuSizeMax + 1];
		PictBuffer[cIdx][tmp_idxOrig9 + lcuSizeMax][tmp_idxOrig10 + lcuSizeMax] = tmp_newPix2;
	}
	tmp_saoTypeIdxBorder3 = saoTypeIdxBorder[7];
	tmp_idxOrig11 = idxOrig[0];
	if (tmp_saoTypeIdxBorder3 != 0 && tmp_idxOrig11 != 0) {
		y = idxOrig[1];
		tmp_idxOrig12 = idxOrig[1];
		while (y <= tmp_idxOrig12 + lcuSizeMax - 1) {
			tmp_idxOrig13 = idxOrig[0];
			tmp_idxOrig14 = idxOrig[1];
			tmp_newPix3 = newPix[y - tmp_idxOrig14 + 1][0];
			PictBuffer[cIdx][y][tmp_idxOrig13 - 1] = tmp_newPix3;
			y = y + 1;
		}
	}
	tmp_saoTypeIdxBorder4 = saoTypeIdxBorder[3];
	tmp_idxMax3 = idxMax[0];
	if (tmp_saoTypeIdxBorder4 != 0 && tmp_idxMax3 == lcuSizeMax - 1) {
		y0 = idxOrig[1];
		tmp_idxOrig15 = idxOrig[1];
		while (y0 <= tmp_idxOrig15 + lcuSizeMax - 1) {
			tmp_idxOrig16 = idxOrig[0];
			tmp_idxOrig17 = idxOrig[1];
			tmp_newPix4 = newPix[y0 - tmp_idxOrig17 + 1][lcuSizeMax + 1];
			PictBuffer[cIdx][y0][tmp_idxOrig16 + lcuSizeMax] = tmp_newPix4;
			y0 = y0 + 1;
		}
	}
	tmp_saoTypeIdxBorder5 = saoTypeIdxBorder[1];
	tmp_idxOrig18 = idxOrig[1];
	if (tmp_saoTypeIdxBorder5 != 0 && tmp_idxOrig18 != 0) {
		x = idxOrig[0];
		tmp_idxOrig19 = idxOrig[0];
		while (x <= tmp_idxOrig19 + lcuSizeMax - 1) {
			tmp_idxOrig20 = idxOrig[1];
			tmp_idxOrig21 = idxOrig[0];
			tmp_newPix5 = newPix[0][x - tmp_idxOrig21 + 1];
			PictBuffer[cIdx][tmp_idxOrig20 - 1][x] = tmp_newPix5;
			x = x + 1;
		}
	}
	tmp_saoTypeIdxBorder6 = saoTypeIdxBorder[5];
	tmp_idxMax4 = idxMax[1];
	if (tmp_saoTypeIdxBorder6 != 0 && tmp_idxMax4 == lcuSizeMax - 1) {
		x0 = idxOrig[0];
		tmp_idxOrig22 = idxOrig[0];
		while (x0 <= tmp_idxOrig22 + lcuSizeMax - 1) {
			tmp_idxOrig23 = idxOrig[1];
			tmp_idxOrig24 = idxOrig[0];
			tmp_newPix6 = newPix[lcuSizeMax + 1][x0 - (tmp_idxOrig24 - 1)];
			PictBuffer[cIdx][tmp_idxOrig23 + lcuSizeMax][x0] = tmp_newPix6;
			x0 = x0 + 1;
		}
	}
}
static void resetTilesOrSliceEdgeLuma(u16 rx, u16 ry, i16 idxMin[2], i16 idxMax[2], i8 xOff[2], i8 yOff[2]) {
	u16 xIdx;
	u16 yIdx;
	u16 pixIdx[2][2];
	i32 pixIsInPict;
	i16 y;
	i16 tmp_idxMax;
	i16 x;
	i16 tmp_idxMax0;
	u32 k;
	i8 tmp_xOff;
	i8 tmp_yOff;
	u8 local_log2LcuSizeMax;
	i32 tmp_filtAcrSlc;
	u16 tmp_pixIdx;
	u16 tmp_pixIdx0;
	u8 tmp_numSlc;
	u16 tmp_pixIdx1;
	u16 tmp_pixIdx2;
	u8 tmp_numSlc0;
	i32 tmp_filtAcrTile;
	u16 tmp_pixIdx3;
	u16 tmp_pixIdx4;
	u8 tmp_numTile;
	u16 tmp_pixIdx5;
	u16 tmp_pixIdx6;
	u8 tmp_numTile0;
	u8 tmp_origPict;

	y = idxMin[1];
	tmp_idxMax = idxMax[1];
	while (y <= tmp_idxMax) {
		yIdx = ry + y;
		x = idxMin[0];
		tmp_idxMax0 = idxMax[0];
		while (x <= tmp_idxMax0) {
			xIdx = rx + x;
			k = 0;
			while (k <= 1) {
				tmp_xOff = xOff[k];
				pixIdx[k][0] = xIdx + tmp_xOff;
				tmp_yOff = yOff[k];
				pixIdx[k][1] = yIdx + tmp_yOff;
				k = k + 1;
			}
			local_log2LcuSizeMax = log2LcuSizeMax;
			local_log2LcuSizeMax = log2LcuSizeMax;
			tmp_filtAcrSlc = filtAcrSlc[xIdx >> local_log2LcuSizeMax][yIdx >> local_log2LcuSizeMax];
			tmp_pixIdx = pixIdx[0][0];
			local_log2LcuSizeMax = log2LcuSizeMax;
			tmp_pixIdx0 = pixIdx[0][1];
			local_log2LcuSizeMax = log2LcuSizeMax;
			tmp_numSlc = numSlc[tmp_pixIdx >> local_log2LcuSizeMax][tmp_pixIdx0 >> local_log2LcuSizeMax];
			tmp_pixIdx1 = pixIdx[1][0];
			local_log2LcuSizeMax = log2LcuSizeMax;
			tmp_pixIdx2 = pixIdx[1][1];
			local_log2LcuSizeMax = log2LcuSizeMax;
			tmp_numSlc0 = numSlc[tmp_pixIdx1 >> local_log2LcuSizeMax][tmp_pixIdx2 >> local_log2LcuSizeMax];
			local_log2LcuSizeMax = log2LcuSizeMax;
			local_log2LcuSizeMax = log2LcuSizeMax;
			tmp_filtAcrTile = filtAcrTile[xIdx >> local_log2LcuSizeMax][yIdx >> local_log2LcuSizeMax];
			tmp_pixIdx3 = pixIdx[0][0];
			local_log2LcuSizeMax = log2LcuSizeMax;
			tmp_pixIdx4 = pixIdx[0][1];
			local_log2LcuSizeMax = log2LcuSizeMax;
			tmp_numTile = numTile[tmp_pixIdx3 >> local_log2LcuSizeMax][tmp_pixIdx4 >> local_log2LcuSizeMax];
			tmp_pixIdx5 = pixIdx[1][0];
			local_log2LcuSizeMax = log2LcuSizeMax;
			tmp_pixIdx6 = pixIdx[1][1];
			local_log2LcuSizeMax = log2LcuSizeMax;
			tmp_numTile0 = numTile[tmp_pixIdx5 >> local_log2LcuSizeMax][tmp_pixIdx6 >> local_log2LcuSizeMax];
			pixIsInPict = !(!tmp_filtAcrSlc && tmp_numSlc != tmp_numSlc0) && !(!tmp_filtAcrTile && tmp_numTile != tmp_numTile0);
			if (!pixIsInPict) {
				tmp_origPict = origPict[0][yIdx][xIdx];
				PictBuffer[0][yIdx][xIdx] = tmp_origPict;
			}
			x = x + 1;
		}
		y = y + 1;
	}
}
static void resetTilesOrSliceEdgeChroma(u16 rx, u16 ry, u8 cIdx, u16 idxMin[2], u16 idxMax[2], i8 xOff[2], i8 yOff[2]) {
	u16 xIdx;
	u16 yIdx;
	u16 pixIdx[2][2];
	i32 pixIsInPict;
	u16 y;
	u16 tmp_idxMax;
	i16 x;
	u16 tmp_idxMax0;
	u32 k;
	i8 tmp_xOff;
	i8 tmp_yOff;
	u8 local_log2LcuSizeMax;
	i32 tmp_filtAcrSlc;
	u8 tmp_numSlc;
	u16 tmp_pixIdx;
	u16 tmp_pixIdx0;
	u8 tmp_numSlc0;
	i32 tmp_filtAcrTile;
	u8 tmp_numTile;
	u16 tmp_pixIdx1;
	u16 tmp_pixIdx2;
	u8 tmp_numTile0;
	u8 tmp_origPict;

	y = idxMin[1];
	tmp_idxMax = idxMax[1];
	while (y <= tmp_idxMax) {
		yIdx = ry + y;
		x = idxMin[0];
		tmp_idxMax0 = idxMax[0];
		while (x <= tmp_idxMax0) {
			xIdx = rx + x;
			pixIsInPict = 1;
			k = 0;
			while (k <= 1) {
				tmp_xOff = xOff[k];
				pixIdx[k][0] = xIdx + tmp_xOff;
				tmp_yOff = yOff[k];
				pixIdx[k][1] = yIdx + tmp_yOff;
				local_log2LcuSizeMax = log2LcuSizeMax;
				local_log2LcuSizeMax = log2LcuSizeMax;
				tmp_filtAcrSlc = filtAcrSlc[xIdx >> (local_log2LcuSizeMax - 1)][yIdx >> (local_log2LcuSizeMax - 1)];
				local_log2LcuSizeMax = log2LcuSizeMax;
				local_log2LcuSizeMax = log2LcuSizeMax;
				tmp_numSlc = numSlc[xIdx >> (local_log2LcuSizeMax - 1)][yIdx >> (local_log2LcuSizeMax - 1)];
				tmp_pixIdx = pixIdx[k][0];
				local_log2LcuSizeMax = log2LcuSizeMax;
				tmp_pixIdx0 = pixIdx[k][1];
				local_log2LcuSizeMax = log2LcuSizeMax;
				tmp_numSlc0 = numSlc[tmp_pixIdx >> (local_log2LcuSizeMax - 1)][tmp_pixIdx0 >> (local_log2LcuSizeMax - 1)];
				local_log2LcuSizeMax = log2LcuSizeMax;
				local_log2LcuSizeMax = log2LcuSizeMax;
				tmp_filtAcrTile = filtAcrTile[xIdx >> (local_log2LcuSizeMax - 1)][yIdx >> (local_log2LcuSizeMax - 1)];
				local_log2LcuSizeMax = log2LcuSizeMax;
				local_log2LcuSizeMax = log2LcuSizeMax;
				tmp_numTile = numTile[xIdx >> (local_log2LcuSizeMax - 1)][yIdx >> (local_log2LcuSizeMax - 1)];
				tmp_pixIdx1 = pixIdx[k][0];
				local_log2LcuSizeMax = log2LcuSizeMax;
				tmp_pixIdx2 = pixIdx[k][1];
				local_log2LcuSizeMax = log2LcuSizeMax;
				tmp_numTile0 = numTile[tmp_pixIdx1 >> (local_log2LcuSizeMax - 1)][tmp_pixIdx2 >> (local_log2LcuSizeMax - 1)];
				pixIsInPict = pixIsInPict && !(!tmp_filtAcrSlc && tmp_numSlc != tmp_numSlc0) && !(!tmp_filtAcrTile && tmp_numTile != tmp_numTile0);
				k = k + 1;
			}
			if (!pixIsInPict) {
				tmp_origPict = origPict[cIdx][yIdx][xIdx];
				PictBuffer[cIdx][yIdx][xIdx] = tmp_origPict;
			}
			x = x + 1;
		}
		y = y + 1;
	}
}
static void saoFilterEdge(u8 saoEoClasss, u8 cIdx, u8 cIdxOffset, u16 idxMin[2], u8 lcuSizeMax, u16 picSize[2], i32 lcuIsPictBorder, i32 saoOff[5], i32 filtAcrossSlcAndTiles, u8 origPict[3][2048][4096], u8 PictBuffer[3][2048][4096], u8 saoTypeIdxBorder[8]) {
	#if OPENHEVC_ENABLE && HAVE_SSE4
	saoFilterEdge_orcc(saoEoClasss, cIdx, cIdxOffset, idxMin, lcuSizeMax, picSize, lcuIsPictBorder, saoOff, filtAcrossSlcAndTiles, origPict, PictBuffer, saoTypeIdxBorder);
	#else
	u8 local_xCuFilt;
	u8 local_yCuFilt;
	u8 tmp_saoEoClass;
	u16 tmp_idxMin;
	u16 tmp_idxMin0;
	u8 tmp_saoEoClass0;
	u16 tmp_idxMin1;
	u16 tmp_idxMin2;
	u16 tmp_idxMin3;
	u16 tmp_idxMin4;
	i16 inlined_idxMin[2];
	i16 inlined_idxMax[2];
	i16 inlined_xMax;
	i16 inlined_xIdx;
	i16 inlined_yIdx;
	u16 inlined_pixIdx[2][2];
	u8 inlined_edgeIdx;
	i8 inlined_xOff[2];
	i8 inlined_yOff[2];
	u8 inlined_newPix[66][66];
	u16 inlined_tmp_picSize;
	u16 inlined_tmp_idxOrig;
	i32 inlined_tmp_min;
	u16 inlined_tmp_picSize0;
	u16 inlined_tmp_idxOrig0;
	i32 inlined_tmp_min0;
	u32 inlined_k;
	u8 inlined_local_xCuFilt;
	u8 inlined_local_yCuFilt;
	u8 inlined_tmp_saoEoClass;
	i8 inlined_tmp_constHPos0;
	u8 inlined_tmp_saoEoClass0;
	i8 inlined_tmp_constVPos0;
	u16 inlined_tmp_idxOrig1;
	i8 inlined_tmp_xOff;
	i8 inlined_tmp_xOff0;
	i16 inlined_tmp_idxMax;
	u16 inlined_tmp_idxOrig2;
	u8 inlined_local_cIdx;
	u16 inlined_tmp_idxOrig3;
	i8 inlined_tmp_yOff;
	i16 inlined_tmp_idxMin;
	i16 inlined_y;
	i16 inlined_tmp_idxMax0;
	u16 inlined_tmp_idxOrig4;
	u16 inlined_tmp_idxOrig5;
	i8 inlined_tmp_xOff1;
	i16 inlined_tmp_idxMin0;
	i16 inlined_x;
	u16 inlined_tmp_idxOrig6;
	i8 inlined_tmp_yOff0;
	i8 inlined_tmp_xOff2;
	u16 inlined_tmp_pixIdx;
	u16 inlined_tmp_pixIdx0;
	u8 inlined_tmp_PictBuffer;
	u8 inlined_tmp_PictBuffer0;
	i8 inlined_tmp_Sign3;
	u16 inlined_tmp_pixIdx1;
	u16 inlined_tmp_pixIdx2;
	u16 inlined_tmp_idxOrig7;
	u16 inlined_tmp_idxOrig8;
	i16 inlined_tmp_idxMax1;
	u16 inlined_tmp_picSize1;
	i16 inlined_tmp_idxMax2;
	u16 inlined_tmp_idxOrig9;
	u16 inlined_tmp_idxOrig10;
	i16 inlined_tmp_idxMax3;
	u16 inlined_tmp_picSize2;
	i16 inlined_tmp_idxMax4;
	i16 inlined_y0;
	i16 inlined_tmp_idxMax5;
	u16 inlined_tmp_idxOrig11;
	i16 inlined_x0;
	i16 inlined_tmp_idxMax6;
	u16 inlined_tmp_idxOrig12;
	i8 inlined_tmp_signResult;
	i8 inlined_tmp_yOff1;
	i8 inlined_tmp_xOff3;
	i8 inlined_tmp_signResult0;
	u8 inlined_tmp_PictBuffer1;
	i32 inlined_tmp_saoOffset;
	i32 inlined_tmp_clip_i32;
	u16 inlined_tmp_idxOrig13;
	u16 inlined_tmp_idxOrig14;

	if (cIdx == 0) {
		if (saoEoClasss == 0) {
			saoFilterEdgeLuma_Horiz(idxMin, lcuSizeMax, picSize, lcuIsPictBorder, saoOff, filtAcrossSlcAndTiles, saoTypeIdxBorder);
		} else {
			if (saoEoClasss == 1) {
				saoFilterEdgeLuma_Vert(idxMin, lcuSizeMax, picSize, lcuIsPictBorder, saoOff, filtAcrossSlcAndTiles, saoTypeIdxBorder);
			} else {
				inlined_tmp_picSize = picSize[0];
				inlined_tmp_idxOrig = idxMin[0];
				inlined_tmp_min = HevcDecoder_SAO_min(lcuSizeMax - 1, inlined_tmp_picSize - inlined_tmp_idxOrig - 1);
				inlined_idxMax[0] = inlined_tmp_min;
				inlined_tmp_picSize0 = picSize[1];
				inlined_tmp_idxOrig0 = idxMin[1];
				inlined_tmp_min0 = HevcDecoder_SAO_min(lcuSizeMax - 1, inlined_tmp_picSize0 - inlined_tmp_idxOrig0 - 1);
				inlined_idxMax[1] = inlined_tmp_min0;
				inlined_k = 0;
				while (inlined_k <= 1) {
					inlined_local_xCuFilt = xCuFilt;
					inlined_local_yCuFilt = yCuFilt;
					inlined_tmp_saoEoClass = saoEoClass[inlined_local_xCuFilt][inlined_local_yCuFilt][0];
					inlined_tmp_constHPos0 = constHPos0[inlined_tmp_saoEoClass][inlined_k];
					inlined_xOff[inlined_k] = inlined_tmp_constHPos0;
					inlined_local_xCuFilt = xCuFilt;
					inlined_local_yCuFilt = yCuFilt;
					inlined_tmp_saoEoClass0 = saoEoClass[inlined_local_xCuFilt][inlined_local_yCuFilt][0];
					inlined_tmp_constVPos0 = constVPos0[inlined_tmp_saoEoClass0][inlined_k];
					inlined_yOff[inlined_k] = inlined_tmp_constVPos0;
					inlined_k = inlined_k + 1;
				}
				inlined_tmp_idxOrig1 = idxMin[0];
				inlined_tmp_xOff = inlined_xOff[0];
				if (inlined_tmp_idxOrig1 == 0 || inlined_tmp_xOff != -1) {
					inlined_idxMin[0] = 0;
				} else {
					inlined_idxMin[0] = -1;
				}
				inlined_tmp_xOff0 = inlined_xOff[0];
				if (inlined_tmp_xOff0 == -1) {
					inlined_xMax = inlined_idxMax[0];
				} else {
					inlined_tmp_idxMax = inlined_idxMax[0];
					inlined_xMax = inlined_tmp_idxMax + 1;
				}
				inlined_tmp_idxOrig2 = idxMin[1];
				if (inlined_tmp_idxOrig2 == 0) {
					inlined_idxMin[1] = 0;
				} else {
					inlined_idxMin[1] = -1;
				}
				inlined_local_cIdx = cIdx;
				revertFiltering(saoTypeIdxBorder, lcuSizeMax, idxMin, inlined_idxMax, inlined_local_cIdx, inlined_newPix);
				inlined_tmp_idxOrig3 = idxMin[1];
				inlined_tmp_yOff = inlined_yOff[1];
				inlined_tmp_idxMin = inlined_idxMin[1];
				inlined_pixIdx[1][1] = inlined_tmp_idxOrig3 + inlined_tmp_yOff + inlined_tmp_idxMin;
				inlined_y = inlined_idxMin[1];
				inlined_tmp_idxMax0 = inlined_idxMax[1];
				while (inlined_y <= inlined_tmp_idxMax0) {
					inlined_tmp_idxOrig4 = idxMin[1];
					inlined_yIdx = inlined_tmp_idxOrig4 + inlined_y;
					inlined_tmp_idxOrig5 = idxMin[0];
					inlined_tmp_xOff1 = inlined_xOff[1];
					inlined_tmp_idxMin0 = inlined_idxMin[0];
					inlined_pixIdx[1][0] = inlined_tmp_idxOrig5 + inlined_tmp_xOff1 + inlined_tmp_idxMin0;
					inlined_x = inlined_idxMin[0];
					while (inlined_x <= inlined_xMax) {
						inlined_tmp_idxOrig6 = idxMin[0];
						inlined_xIdx = inlined_tmp_idxOrig6 + inlined_x;
						inlined_tmp_yOff0 = inlined_yOff[1];
						inlined_tmp_xOff2 = inlined_xOff[1];
						inlined_tmp_pixIdx = inlined_pixIdx[1][1];
						inlined_tmp_pixIdx0 = inlined_pixIdx[1][0];
						inlined_tmp_PictBuffer = PictBuffer[0][inlined_tmp_pixIdx][inlined_tmp_pixIdx0];
						inlined_tmp_PictBuffer0 = PictBuffer[0][inlined_yIdx][inlined_xIdx];
						inlined_tmp_Sign3 = HevcDecoder_SAO_Sign3(inlined_tmp_PictBuffer - inlined_tmp_PictBuffer0);
						signResult[0][inlined_y + inlined_tmp_yOff0 & 127][inlined_x + inlined_tmp_xOff2 & 127] = inlined_tmp_Sign3;
						inlined_tmp_pixIdx1 = inlined_pixIdx[1][0];
						inlined_pixIdx[1][0] = inlined_tmp_pixIdx1 + 1;
						inlined_x = inlined_x + 1;
					}
					inlined_tmp_pixIdx2 = inlined_pixIdx[1][1];
					inlined_pixIdx[1][1] = inlined_tmp_pixIdx2 + 1;
					inlined_y = inlined_y + 1;
				}
				inlined_local_cIdx = cIdx;
				putBackFilteredPix(saoTypeIdxBorder, lcuSizeMax, idxMin, inlined_idxMax, inlined_local_cIdx, inlined_newPix);
				inlined_idxMin[0] = 0;
				inlined_idxMin[1] = 0;
				if (lcuIsPictBorder) {
					inlined_tmp_idxOrig7 = idxMin[0];
					if (inlined_tmp_idxOrig7 == 0) {
						inlined_idxMin[0] = 1;
					}
					inlined_tmp_idxOrig8 = idxMin[0];
					inlined_tmp_idxMax1 = inlined_idxMax[0];
					inlined_tmp_picSize1 = picSize[0];
					if (inlined_tmp_idxOrig8 + inlined_tmp_idxMax1 == inlined_tmp_picSize1 - 1) {
						inlined_tmp_idxMax2 = inlined_idxMax[0];
						inlined_idxMax[0] = inlined_tmp_idxMax2 - 1;
					}
					inlined_tmp_idxOrig9 = idxMin[1];
					if (inlined_tmp_idxOrig9 == 0) {
						inlined_idxMin[1] = 1;
					}
					inlined_tmp_idxOrig10 = idxMin[1];
					inlined_tmp_idxMax3 = inlined_idxMax[1];
					inlined_tmp_picSize2 = picSize[1];
					if (inlined_tmp_idxOrig10 + inlined_tmp_idxMax3 == inlined_tmp_picSize2 - 1) {
						inlined_tmp_idxMax4 = inlined_idxMax[1];
						inlined_idxMax[1] = inlined_tmp_idxMax4 - 1;
					}
				}
				inlined_y0 = inlined_idxMin[1];
				inlined_tmp_idxMax5 = inlined_idxMax[1];
				while (inlined_y0 <= inlined_tmp_idxMax5) {
					inlined_tmp_idxOrig11 = idxMin[1];
					inlined_yIdx = inlined_tmp_idxOrig11 + inlined_y0;
					inlined_x0 = inlined_idxMin[0];
					inlined_tmp_idxMax6 = inlined_idxMax[0];
					while (inlined_x0 <= inlined_tmp_idxMax6) {
						inlined_tmp_idxOrig12 = idxMin[0];
						inlined_xIdx = inlined_tmp_idxOrig12 + inlined_x0;
						inlined_tmp_signResult = signResult[0][inlined_y0][inlined_x0];
						inlined_tmp_yOff1 = inlined_yOff[1];
						inlined_tmp_xOff3 = inlined_xOff[1];
						inlined_tmp_signResult0 = signResult[0][inlined_y0 + inlined_tmp_yOff1 & 127][inlined_x0 + inlined_tmp_xOff3 & 127];
						inlined_edgeIdx = 2 + inlined_tmp_signResult - inlined_tmp_signResult0;
						inlined_edgeIdx = edgeIdxConv[inlined_edgeIdx];
						inlined_tmp_PictBuffer1 = PictBuffer[0][inlined_yIdx][inlined_xIdx];
						inlined_tmp_saoOffset = saoOff[inlined_edgeIdx];
						inlined_tmp_clip_i32 = HevcDecoder_SAO_clip_i32(inlined_tmp_PictBuffer1 + inlined_tmp_saoOffset, 0, 255);
						PictBuffer[0][inlined_yIdx][inlined_xIdx] = inlined_tmp_clip_i32;
						inlined_x0 = inlined_x0 + 1;
					}
					inlined_y0 = inlined_y0 + 1;
				}
				if (!filtAcrossSlcAndTiles) {
					inlined_tmp_idxOrig13 = idxMin[0];
					inlined_tmp_idxOrig14 = idxMin[1];
					resetTilesOrSliceEdgeLuma(inlined_tmp_idxOrig13, inlined_tmp_idxOrig14, inlined_idxMin, inlined_idxMax, inlined_xOff, inlined_yOff);
				}
			}
		}
	} else {
		local_xCuFilt = xCuFilt;
		local_yCuFilt = yCuFilt;
		tmp_saoEoClass = saoEoClass[local_xCuFilt][local_yCuFilt][cIdx];
		if (tmp_saoEoClass == 0) {
			tmp_idxMin = idxMin[0];
			tmp_idxMin0 = idxMin[1];
			saoFilterEdgeChroma_Horiz(tmp_idxMin, tmp_idxMin0, cIdx, picSize, lcuIsPictBorder, saoTypeIdxBorder);
		} else {
			local_xCuFilt = xCuFilt;
			local_yCuFilt = yCuFilt;
			tmp_saoEoClass0 = saoEoClass[local_xCuFilt][local_yCuFilt][cIdx];
			if (tmp_saoEoClass0 == 1) {
				tmp_idxMin1 = idxMin[0];
				tmp_idxMin2 = idxMin[1];
				saoFilterEdgeChroma_Vert(tmp_idxMin1, tmp_idxMin2, cIdx, picSize, lcuIsPictBorder, saoTypeIdxBorder);
			} else {
				tmp_idxMin3 = idxMin[0];
				tmp_idxMin4 = idxMin[1];
				saoFilterEdgeChroma_Diag(tmp_idxMin3, tmp_idxMin4, cIdx, picSize, lcuIsPictBorder, saoTypeIdxBorder);
			}
		}
	}
	#endif // OPENHEVC_ENABLE && HAVE_SSE4
}
static void saoFilterEdgeLuma_Horiz(u16 idxMin[2], u8 lcuSizeMax, u16 picSize[2], i32 lcuIsPictBorder, i32 saoOffset[5], i32 filtAcrossSlcAndTiles, u8 saoTypeIdxBorder[8]) {
	i16 xMax;
	u16 yMax;
	u16 xIdx;
	u16 yIdx;
	u16 xPix2;
	u8 edgeIdx;
	i16 xMin;
	u16 idxMinRst[2];
	u16 idxMaxRst[2];
	i8 xOff[2];
	i8 yOff[2];
	u16 tmp_picSize;
	u16 tmp_idxMin;
	u16 tmp_picSize0;
	u16 tmp_idxMin0;
	i16 y;
	u16 tmp_idxMin1;
	i16 x;
	u16 tmp_idxMin2;
	u8 tmp_PictBuffer;
	u8 tmp_PictBuffer0;
	i8 tmp_Sign3;
	u16 tmp_idxMin3;
	u16 tmp_idxMin4;
	i16 y0;
	u16 tmp_idxMin5;
	u8 tmp_saoTypeIdxBorder;
	u8 tmp_PictBuffer1;
	u8 tmp_origPict;
	i8 tmp_Sign30;
	u8 tmp_PictBuffer2;
	u8 tmp_PictBuffer3;
	i8 tmp_Sign31;
	u16 tmp_idxMin6;
	i16 y1;
	u16 tmp_idxMin7;
	u8 tmp_saoTypeIdxBorder0;
	i32 local_MASK_WIDTH_POW_2;
	u8 tmp_origPict0;
	u8 tmp_PictBuffer4;
	i8 tmp_Sign32;
	u8 tmp_PictBuffer5;
	u8 tmp_PictBuffer6;
	i8 tmp_Sign33;
	u16 tmp_idxMin8;
	u16 tmp_idxMin9;
	u16 tmp_picSize1;
	u8 y2;
	u16 tmp_idxMin10;
	i16 x0;
	u16 tmp_idxMin11;
	i8 tmp_signResult;
	i8 tmp_signResult0;
	u8 tmp_PictBuffer7;
	i32 tmp_saoOffset;
	i32 tmp_clip_i32;
	u16 tmp_idxMin12;
	u16 tmp_idxMin13;

	xOff[0] = -1;
	xOff[1] = 1;
	yOff[0] = 0;
	yOff[1] = 0;
	tmp_picSize = picSize[0];
	tmp_idxMin = idxMin[0];
	xMax = HevcDecoder_SAO_min(lcuSizeMax - 1, tmp_picSize - tmp_idxMin - 1);
	tmp_picSize0 = picSize[1];
	tmp_idxMin0 = idxMin[1];
	yMax = HevcDecoder_SAO_min(lcuSizeMax - 1, tmp_picSize0 - tmp_idxMin0 - 1);
	y = 0;
	while (y <= yMax) {
		tmp_idxMin1 = idxMin[1];
		yIdx = tmp_idxMin1 + y;
		x = 0;
		while (x <= xMax) {
			tmp_idxMin2 = idxMin[0];
			xIdx = tmp_idxMin2 + x;
			xPix2 = xIdx + 1;
			tmp_PictBuffer = PictBuffer[0][yIdx][xPix2];
			tmp_PictBuffer0 = PictBuffer[0][yIdx][xIdx];
			tmp_Sign3 = HevcDecoder_SAO_Sign3(tmp_PictBuffer - tmp_PictBuffer0);
			signResult[0][y][x + 1 & 127] = tmp_Sign3;
			x = x + 1;
		}
		y = y + 1;
	}
	tmp_idxMin3 = idxMin[0];
	if (tmp_idxMin3 != 0) {
		tmp_idxMin4 = idxMin[0];
		xIdx = tmp_idxMin4 - 1;
		xPix2 = xIdx + 1;
		y0 = 0;
		while (y0 <= yMax) {
			tmp_idxMin5 = idxMin[1];
			yIdx = tmp_idxMin5 + y0;
			tmp_saoTypeIdxBorder = saoTypeIdxBorder[7];
			if (tmp_saoTypeIdxBorder != 0) {
				tmp_PictBuffer1 = PictBuffer[0][yIdx][xPix2];
				tmp_origPict = origPict[0][yIdx][xIdx];
				tmp_Sign30 = HevcDecoder_SAO_Sign3(tmp_PictBuffer1 - tmp_origPict);
				signResult[0][y0][0] = tmp_Sign30;
			} else {
				tmp_PictBuffer2 = PictBuffer[0][yIdx][xPix2];
				tmp_PictBuffer3 = PictBuffer[0][yIdx][xIdx];
				tmp_Sign31 = HevcDecoder_SAO_Sign3(tmp_PictBuffer2 - tmp_PictBuffer3);
				signResult[0][y0][0] = tmp_Sign31;
			}
			y0 = y0 + 1;
		}
	}
	if (xMax == lcuSizeMax - 1) {
		tmp_idxMin6 = idxMin[0];
		xIdx = tmp_idxMin6 + lcuSizeMax - 1;
		xPix2 = xIdx + 1;
		y1 = 0;
		while (y1 <= yMax) {
			tmp_idxMin7 = idxMin[1];
			yIdx = tmp_idxMin7 + y1;
			tmp_saoTypeIdxBorder0 = saoTypeIdxBorder[3];
			if (tmp_saoTypeIdxBorder0 != 0) {
				local_MASK_WIDTH_POW_2 = HevcDecoder_SAO_MASK_WIDTH_POW_2;
				tmp_origPict0 = origPict[0][yIdx][xPix2 & local_MASK_WIDTH_POW_2];
				tmp_PictBuffer4 = PictBuffer[0][yIdx][xIdx];
				tmp_Sign32 = HevcDecoder_SAO_Sign3(tmp_origPict0 - tmp_PictBuffer4);
				signResult[0][y1][lcuSizeMax & 127] = tmp_Sign32;
			} else {
				tmp_PictBuffer5 = PictBuffer[0][yIdx][xPix2];
				tmp_PictBuffer6 = PictBuffer[0][yIdx][xIdx];
				tmp_Sign33 = HevcDecoder_SAO_Sign3(tmp_PictBuffer5 - tmp_PictBuffer6);
				signResult[0][y1][lcuSizeMax & 127] = tmp_Sign33;
			}
			y1 = y1 + 1;
		}
	}
	xMin = 0;
	if (lcuIsPictBorder) {
		tmp_idxMin8 = idxMin[0];
		if (tmp_idxMin8 == 0) {
			xMin = 1;
		}
		tmp_idxMin9 = idxMin[0];
		tmp_picSize1 = picSize[0];
		if (tmp_idxMin9 + xMax == tmp_picSize1 - 1) {
			xMax = xMax - 1;
		}
	}
	y2 = 0;
	while (y2 <= yMax) {
		tmp_idxMin10 = idxMin[1];
		yIdx = tmp_idxMin10 + y2;
		x0 = xMin;
		while (x0 <= xMax) {
			tmp_idxMin11 = idxMin[0];
			xIdx = tmp_idxMin11 + x0;
			xPix2 = xIdx + 1;
			tmp_signResult = signResult[0][y2][x0];
			tmp_signResult0 = signResult[0][y2][x0 + 1];
			edgeIdx = 2 + tmp_signResult - tmp_signResult0;
			edgeIdx = edgeIdxConv[edgeIdx];
			tmp_PictBuffer7 = PictBuffer[0][yIdx][xIdx];
			tmp_saoOffset = saoOffset[edgeIdx];
			tmp_clip_i32 = HevcDecoder_SAO_clip_i32(tmp_PictBuffer7 + tmp_saoOffset, 0, 255);
			PictBuffer[0][yIdx][xIdx] = tmp_clip_i32;
			x0 = x0 + 1;
		}
		y2 = y2 + 1;
	}
	if (!filtAcrossSlcAndTiles) {
		idxMinRst[0] = xMin;
		idxMinRst[1] = 0;
		idxMaxRst[0] = xMax;
		idxMaxRst[1] = yMax;
		tmp_idxMin12 = idxMin[0];
		tmp_idxMin13 = idxMin[1];
		resetTilesOrSliceEdgeLuma(tmp_idxMin12, tmp_idxMin13, idxMinRst, idxMaxRst, xOff, yOff);
	}
}
static void saoFilterEdgeLuma_Vert(u16 idxMin[2], u8 lcuSizeMax, u16 picSize[2], i32 lcuIsPictBorder, i32 saoOffset[5], i32 filtAcrossSlcAndTiles, u8 saoTypeIdxBorder[8]) {
	i16 yMin;
	i16 xMax;
	u16 yMax;
	u16 xIdx;
	u16 yIdx;
	u16 yPix2;
	u8 edgeIdx;
	u16 idxMinRst[2];
	u16 idxMaxRst[2];
	i8 xOff[2];
	i8 yOff[2];
	u16 tmp_picSize;
	u16 tmp_idxMin;
	u16 tmp_picSize0;
	u16 tmp_idxMin0;
	i16 y;
	u16 tmp_idxMin1;
	i16 x;
	u16 tmp_idxMin2;
	u8 tmp_PictBuffer;
	u8 tmp_PictBuffer0;
	i8 tmp_Sign3;
	u16 tmp_idxMin3;
	u16 tmp_idxMin4;
	i16 x0;
	u16 tmp_idxMin5;
	u8 tmp_saoTypeIdxBorder;
	u8 tmp_PictBuffer1;
	u8 tmp_origPict;
	i8 tmp_Sign30;
	u8 tmp_PictBuffer2;
	u8 tmp_PictBuffer3;
	i8 tmp_Sign31;
	u16 tmp_idxMin6;
	i16 x1;
	u16 tmp_idxMin7;
	u8 tmp_saoTypeIdxBorder0;
	i32 local_MASK_HEIGHT_POW_2;
	u8 tmp_origPict0;
	u8 tmp_PictBuffer4;
	i8 tmp_Sign32;
	u8 tmp_PictBuffer5;
	u8 tmp_PictBuffer6;
	i8 tmp_Sign33;
	u16 tmp_idxMin8;
	u16 tmp_idxMin9;
	u16 tmp_picSize1;
	i16 x2;
	u16 tmp_idxMin10;
	u8 y0;
	u16 tmp_idxMin11;
	i8 tmp_signResult;
	i8 tmp_signResult0;
	u8 tmp_PictBuffer7;
	i32 tmp_saoOffset;
	i32 tmp_clip_i32;
	u16 tmp_idxMin12;
	u16 tmp_idxMin13;

	xOff[0] = 0;
	xOff[1] = 0;
	yOff[0] = -1;
	yOff[1] = 1;
	tmp_picSize = picSize[0];
	tmp_idxMin = idxMin[0];
	xMax = HevcDecoder_SAO_min(lcuSizeMax - 1, tmp_picSize - tmp_idxMin - 1);
	tmp_picSize0 = picSize[1];
	tmp_idxMin0 = idxMin[1];
	yMax = HevcDecoder_SAO_min(lcuSizeMax - 1, tmp_picSize0 - tmp_idxMin0 - 1);
	y = 0;
	while (y <= yMax) {
		tmp_idxMin1 = idxMin[1];
		yIdx = tmp_idxMin1 + y;
		yPix2 = yIdx + 1;
		x = 0;
		while (x <= xMax) {
			tmp_idxMin2 = idxMin[0];
			xIdx = tmp_idxMin2 + x;
			tmp_PictBuffer = PictBuffer[0][yPix2][xIdx];
			tmp_PictBuffer0 = PictBuffer[0][yIdx][xIdx];
			tmp_Sign3 = HevcDecoder_SAO_Sign3(tmp_PictBuffer - tmp_PictBuffer0);
			signResult[0][y + 1 & 127][x] = tmp_Sign3;
			x = x + 1;
		}
		y = y + 1;
	}
	tmp_idxMin3 = idxMin[1];
	if (tmp_idxMin3 != 0) {
		tmp_idxMin4 = idxMin[1];
		yIdx = tmp_idxMin4 - 1;
		yPix2 = yIdx + 1;
		x0 = 0;
		while (x0 <= xMax) {
			tmp_idxMin5 = idxMin[0];
			xIdx = tmp_idxMin5 + x0;
			tmp_saoTypeIdxBorder = saoTypeIdxBorder[1];
			if (tmp_saoTypeIdxBorder != 0) {
				tmp_PictBuffer1 = PictBuffer[0][yPix2][xIdx];
				tmp_origPict = origPict[0][yIdx][xIdx];
				tmp_Sign30 = HevcDecoder_SAO_Sign3(tmp_PictBuffer1 - tmp_origPict);
				signResult[0][0][x0] = tmp_Sign30;
			} else {
				tmp_PictBuffer2 = PictBuffer[0][yPix2][xIdx];
				tmp_PictBuffer3 = PictBuffer[0][yIdx][xIdx];
				tmp_Sign31 = HevcDecoder_SAO_Sign3(tmp_PictBuffer2 - tmp_PictBuffer3);
				signResult[0][0][x0] = tmp_Sign31;
			}
			x0 = x0 + 1;
		}
	}
	if (yMax == lcuSizeMax - 1) {
		tmp_idxMin6 = idxMin[1];
		yIdx = tmp_idxMin6 + lcuSizeMax - 1;
		yPix2 = yIdx + 1;
		x1 = 0;
		while (x1 <= xMax) {
			tmp_idxMin7 = idxMin[0];
			xIdx = tmp_idxMin7 + x1;
			tmp_saoTypeIdxBorder0 = saoTypeIdxBorder[5];
			if (tmp_saoTypeIdxBorder0 != 0) {
				local_MASK_HEIGHT_POW_2 = HevcDecoder_SAO_MASK_HEIGHT_POW_2;
				tmp_origPict0 = origPict[0][yPix2 & local_MASK_HEIGHT_POW_2][xIdx];
				tmp_PictBuffer4 = PictBuffer[0][yIdx][xIdx];
				tmp_Sign32 = HevcDecoder_SAO_Sign3(tmp_origPict0 - tmp_PictBuffer4);
				signResult[0][lcuSizeMax & 127][x1] = tmp_Sign32;
			} else {
				tmp_PictBuffer5 = PictBuffer[0][yPix2][xIdx];
				tmp_PictBuffer6 = PictBuffer[0][yIdx][xIdx];
				tmp_Sign33 = HevcDecoder_SAO_Sign3(tmp_PictBuffer5 - tmp_PictBuffer6);
				signResult[0][lcuSizeMax & 127][x1] = tmp_Sign33;
			}
			x1 = x1 + 1;
		}
	}
	yMin = 0;
	if (lcuIsPictBorder) {
		tmp_idxMin8 = idxMin[1];
		if (tmp_idxMin8 == 0) {
			yMin = 1;
		}
		tmp_idxMin9 = idxMin[1];
		tmp_picSize1 = picSize[1];
		if (tmp_idxMin9 + yMax == tmp_picSize1 - 1) {
			yMax = yMax - 1;
		}
	}
	x2 = 0;
	while (x2 <= xMax) {
		tmp_idxMin10 = idxMin[0];
		xIdx = tmp_idxMin10 + x2;
		y0 = yMin;
		while (y0 <= yMax) {
			tmp_idxMin11 = idxMin[1];
			yIdx = tmp_idxMin11 + y0;
			yPix2 = yIdx + 1;
			tmp_signResult = signResult[0][y0][x2];
			tmp_signResult0 = signResult[0][y0 + 1][x2];
			edgeIdx = 2 + tmp_signResult - tmp_signResult0;
			edgeIdx = edgeIdxConv[edgeIdx];
			tmp_PictBuffer7 = PictBuffer[0][yIdx][xIdx];
			tmp_saoOffset = saoOffset[edgeIdx];
			tmp_clip_i32 = HevcDecoder_SAO_clip_i32(tmp_PictBuffer7 + tmp_saoOffset, 0, 255);
			PictBuffer[0][yIdx][xIdx] = tmp_clip_i32;
			y0 = y0 + 1;
		}
		x2 = x2 + 1;
	}
	if (!filtAcrossSlcAndTiles) {
		idxMinRst[0] = 0;
		idxMinRst[1] = yMin;
		idxMaxRst[0] = xMax;
		idxMaxRst[1] = yMax;
		tmp_idxMin12 = idxMin[0];
		tmp_idxMin13 = idxMin[1];
		resetTilesOrSliceEdgeLuma(tmp_idxMin12, tmp_idxMin13, idxMinRst, idxMaxRst, xOff, yOff);
	}
}
static void saoFilterEdgeLuma_Diag(u16 idxOrig[2], u8 lcuSizeMax, u16 picSize[2], i32 lcuIsPictBorder, i32 saoOffset[5], i32 filtAcrossSlcAndTiles, u8 saoTypeIdxBorder[8]) {
	i16 idxMin[2];
	i16 idxMax[2];
	i16 xMax;
	i16 xIdx;
	i16 yIdx;
	u16 pixIdx[2][2];
	u8 edgeIdx;
	i8 xOff[2];
	i8 yOff[2];
	u8 newPix[66][66];
	u16 tmp_picSize;
	u16 tmp_idxOrig;
	i32 tmp_min;
	u16 tmp_picSize0;
	u16 tmp_idxOrig0;
	i32 tmp_min0;
	u32 k;
	u8 local_xCuFilt;
	u8 local_yCuFilt;
	u8 tmp_saoEoClass;
	i8 tmp_constHPos0;
	u8 tmp_saoEoClass0;
	i8 tmp_constVPos0;
	u16 tmp_idxOrig1;
	i8 tmp_xOff;
	i8 tmp_xOff0;
	i16 tmp_idxMax;
	u16 tmp_idxOrig2;
	u8 local_cIdx;
	u16 tmp_idxOrig3;
	i8 tmp_yOff;
	i16 tmp_idxMin;
	i16 y;
	i16 tmp_idxMax0;
	u16 tmp_idxOrig4;
	u16 tmp_idxOrig5;
	i8 tmp_xOff1;
	i16 tmp_idxMin0;
	i16 x;
	u16 tmp_idxOrig6;
	i8 tmp_yOff0;
	i8 tmp_xOff2;
	u16 tmp_pixIdx;
	u16 tmp_pixIdx0;
	u8 tmp_PictBuffer;
	u8 tmp_PictBuffer0;
	i8 tmp_Sign3;
	u16 tmp_pixIdx1;
	u16 tmp_pixIdx2;
	u16 tmp_idxOrig7;
	u16 tmp_idxOrig8;
	i16 tmp_idxMax1;
	u16 tmp_picSize1;
	i16 tmp_idxMax2;
	u16 tmp_idxOrig9;
	u16 tmp_idxOrig10;
	i16 tmp_idxMax3;
	u16 tmp_picSize2;
	i16 tmp_idxMax4;
	i16 y0;
	i16 tmp_idxMax5;
	u16 tmp_idxOrig11;
	i16 x0;
	i16 tmp_idxMax6;
	u16 tmp_idxOrig12;
	i8 tmp_signResult;
	i8 tmp_yOff1;
	i8 tmp_xOff3;
	i8 tmp_signResult0;
	u8 tmp_PictBuffer1;
	i32 tmp_saoOffset;
	i32 tmp_clip_i32;
	u16 tmp_idxOrig13;
	u16 tmp_idxOrig14;

	tmp_picSize = picSize[0];
	tmp_idxOrig = idxOrig[0];
	tmp_min = HevcDecoder_SAO_min(lcuSizeMax - 1, tmp_picSize - tmp_idxOrig - 1);
	idxMax[0] = tmp_min;
	tmp_picSize0 = picSize[1];
	tmp_idxOrig0 = idxOrig[1];
	tmp_min0 = HevcDecoder_SAO_min(lcuSizeMax - 1, tmp_picSize0 - tmp_idxOrig0 - 1);
	idxMax[1] = tmp_min0;
	k = 0;
	while (k <= 1) {
		local_xCuFilt = xCuFilt;
		local_yCuFilt = yCuFilt;
		tmp_saoEoClass = saoEoClass[local_xCuFilt][local_yCuFilt][0];
		tmp_constHPos0 = constHPos0[tmp_saoEoClass][k];
		xOff[k] = tmp_constHPos0;
		local_xCuFilt = xCuFilt;
		local_yCuFilt = yCuFilt;
		tmp_saoEoClass0 = saoEoClass[local_xCuFilt][local_yCuFilt][0];
		tmp_constVPos0 = constVPos0[tmp_saoEoClass0][k];
		yOff[k] = tmp_constVPos0;
		k = k + 1;
	}
	tmp_idxOrig1 = idxOrig[0];
	tmp_xOff = xOff[0];
	if (tmp_idxOrig1 == 0 || tmp_xOff != -1) {
		idxMin[0] = 0;
	} else {
		idxMin[0] = -1;
	}
	tmp_xOff0 = xOff[0];
	if (tmp_xOff0 == -1) {
		xMax = idxMax[0];
	} else {
		tmp_idxMax = idxMax[0];
		xMax = tmp_idxMax + 1;
	}
	tmp_idxOrig2 = idxOrig[1];
	if (tmp_idxOrig2 == 0) {
		idxMin[1] = 0;
	} else {
		idxMin[1] = -1;
	}
	local_cIdx = cIdx;
	revertFiltering(saoTypeIdxBorder, lcuSizeMax, idxOrig, idxMax, local_cIdx, newPix);
	tmp_idxOrig3 = idxOrig[1];
	tmp_yOff = yOff[1];
	tmp_idxMin = idxMin[1];
	pixIdx[1][1] = tmp_idxOrig3 + tmp_yOff + tmp_idxMin;
	y = idxMin[1];
	tmp_idxMax0 = idxMax[1];
	while (y <= tmp_idxMax0) {
		tmp_idxOrig4 = idxOrig[1];
		yIdx = tmp_idxOrig4 + y;
		tmp_idxOrig5 = idxOrig[0];
		tmp_xOff1 = xOff[1];
		tmp_idxMin0 = idxMin[0];
		pixIdx[1][0] = tmp_idxOrig5 + tmp_xOff1 + tmp_idxMin0;
		x = idxMin[0];
		while (x <= xMax) {
			tmp_idxOrig6 = idxOrig[0];
			xIdx = tmp_idxOrig6 + x;
			tmp_yOff0 = yOff[1];
			tmp_xOff2 = xOff[1];
			tmp_pixIdx = pixIdx[1][1];
			tmp_pixIdx0 = pixIdx[1][0];
			tmp_PictBuffer = PictBuffer[0][tmp_pixIdx][tmp_pixIdx0];
			tmp_PictBuffer0 = PictBuffer[0][yIdx][xIdx];
			tmp_Sign3 = HevcDecoder_SAO_Sign3(tmp_PictBuffer - tmp_PictBuffer0);
			signResult[0][y + tmp_yOff0 & 127][x + tmp_xOff2 & 127] = tmp_Sign3;
			tmp_pixIdx1 = pixIdx[1][0];
			pixIdx[1][0] = tmp_pixIdx1 + 1;
			x = x + 1;
		}
		tmp_pixIdx2 = pixIdx[1][1];
		pixIdx[1][1] = tmp_pixIdx2 + 1;
		y = y + 1;
	}
	local_cIdx = cIdx;
	putBackFilteredPix(saoTypeIdxBorder, lcuSizeMax, idxOrig, idxMax, local_cIdx, newPix);
	idxMin[0] = 0;
	idxMin[1] = 0;
	if (lcuIsPictBorder) {
		tmp_idxOrig7 = idxOrig[0];
		if (tmp_idxOrig7 == 0) {
			idxMin[0] = 1;
		}
		tmp_idxOrig8 = idxOrig[0];
		tmp_idxMax1 = idxMax[0];
		tmp_picSize1 = picSize[0];
		if (tmp_idxOrig8 + tmp_idxMax1 == tmp_picSize1 - 1) {
			tmp_idxMax2 = idxMax[0];
			idxMax[0] = tmp_idxMax2 - 1;
		}
		tmp_idxOrig9 = idxOrig[1];
		if (tmp_idxOrig9 == 0) {
			idxMin[1] = 1;
		}
		tmp_idxOrig10 = idxOrig[1];
		tmp_idxMax3 = idxMax[1];
		tmp_picSize2 = picSize[1];
		if (tmp_idxOrig10 + tmp_idxMax3 == tmp_picSize2 - 1) {
			tmp_idxMax4 = idxMax[1];
			idxMax[1] = tmp_idxMax4 - 1;
		}
	}
	y0 = idxMin[1];
	tmp_idxMax5 = idxMax[1];
	while (y0 <= tmp_idxMax5) {
		tmp_idxOrig11 = idxOrig[1];
		yIdx = tmp_idxOrig11 + y0;
		x0 = idxMin[0];
		tmp_idxMax6 = idxMax[0];
		while (x0 <= tmp_idxMax6) {
			tmp_idxOrig12 = idxOrig[0];
			xIdx = tmp_idxOrig12 + x0;
			tmp_signResult = signResult[0][y0][x0];
			tmp_yOff1 = yOff[1];
			tmp_xOff3 = xOff[1];
			tmp_signResult0 = signResult[0][y0 + tmp_yOff1 & 127][x0 + tmp_xOff3 & 127];
			edgeIdx = 2 + tmp_signResult - tmp_signResult0;
			edgeIdx = edgeIdxConv[edgeIdx];
			tmp_PictBuffer1 = PictBuffer[0][yIdx][xIdx];
			tmp_saoOffset = saoOffset[edgeIdx];
			tmp_clip_i32 = HevcDecoder_SAO_clip_i32(tmp_PictBuffer1 + tmp_saoOffset, 0, 255);
			PictBuffer[0][yIdx][xIdx] = tmp_clip_i32;
			x0 = x0 + 1;
		}
		y0 = y0 + 1;
	}
	if (!filtAcrossSlcAndTiles) {
		tmp_idxOrig13 = idxOrig[0];
		tmp_idxOrig14 = idxOrig[1];
		resetTilesOrSliceEdgeLuma(tmp_idxOrig13, tmp_idxOrig14, idxMin, idxMax, xOff, yOff);
	}
}
static void saoBandFilter(u8 saoLeftClass, i32 saoOffset[5], u8 cIdx, u8 cIdxOffset, i16 idxMin[2], i16 idxMax[2], u8 PictBuffer[3][2048][4096]) {
	#if OPENHEVC_ENABLE
	saoBandFilter_orcc(saoLeftClass, saoOffset, cIdx, cIdxOffset, idxMin, idxMax, PictBuffer);
	#else
	u8 local_BIT_DEPTH;
	u8 bandShift;
	u8 bandIdx;
	i32 i;
	u8 bandTable[32];
	u32 k;
	u16 y;
	i16 tmp_idxMax;
	i16 x;
	i16 tmp_idxMax0;
	u8 tmp_PictBuffer;
	u8 tmp_PictBuffer0;
	i32 tmp_saoOffset;
	i32 tmp_clip_i32;

	local_BIT_DEPTH = BIT_DEPTH;
	bandShift = local_BIT_DEPTH - 5;
	i = 0;
	while (i <= 31) {
		bandTable[i] = 0;
		i = i + 1;
	}
	k = 0;
	while (k <= 3) {
		bandTable[k + saoLeftClass & 31] = k + 1;
		k = k + 1;
	}
	y = idxMin[1];
	tmp_idxMax = idxMax[1];
	while (y <= tmp_idxMax) {
		x = idxMin[0];
		tmp_idxMax0 = idxMax[0];
		while (x <= tmp_idxMax0) {
			tmp_PictBuffer = PictBuffer[cIdx][y][x];
			bandIdx = bandTable[tmp_PictBuffer >> bandShift];
			tmp_PictBuffer0 = PictBuffer[cIdx][y][x];
			tmp_saoOffset = saoOffset[bandIdx];
			tmp_clip_i32 = HevcDecoder_SAO_clip_i32(tmp_PictBuffer0 + tmp_saoOffset, 0, 255);
			PictBuffer[cIdx][y][x] = tmp_clip_i32;
			x = x + 1;
		}
		y = y + 1;
	}
	#endif // OPENHEVC_ENABLE
}
static void codingTreeBlockModif(u16 rx, u16 ry, u8 cIdx, u16 picSize[2], i32 lcuIsPictBorder) {
	i16 idxMax[2];
	i16 idxOrig[2];
	i32 saoOff[5];
	i8 compShift[3];
	u8 saoTypeIdxBorder[8];
	i32 i;
	u8 local_xCuFilt;
	u8 local_yCuFilt;
	i16 tmp_saoOffset;
	u8 tmp_saoTypeIdx;
	u8 tmp_saoTypeIdx0;
	u8 tmp_saoTypeIdx1;
	u8 tmp_saoTypeIdx2;
	u8 tmp_saoTypeIdx3;
	u8 tmp_saoTypeIdx4;
	u8 tmp_saoTypeIdx5;
	u8 tmp_saoTypeIdx6;
	u8 tmp_saoTypeIdx7;
	u8 tmp_saoEoClass;
	u8 local_lcuSizeMax;
	i8 tmp_compShift;
	i32 local_filtAcrAllSlc;
	i32 local_filtAcrAllTiles;
	i8 tmp_compShift0;
	u16 tmp_picSize;
	i32 tmp_min;
	i8 tmp_compShift1;
	u16 tmp_picSize0;
	i32 tmp_min0;
	u8 tmp_saoLeftClass;

	idxOrig[0] = rx;
	idxOrig[1] = ry;
	compShift[0] = 0;
	compShift[1] = 1;
	compShift[2] = 1;
	i = 0;
	while (i <= 4) {
		local_xCuFilt = xCuFilt;
		local_yCuFilt = yCuFilt;
		tmp_saoOffset = saoOffset[local_xCuFilt][local_yCuFilt][cIdx][i];
		saoOff[i] = tmp_saoOffset;
		i = i + 1;
	}
	local_xCuFilt = xCuFilt;
	local_yCuFilt = yCuFilt;
	tmp_saoTypeIdx = saoTypeIdx[local_xCuFilt][local_yCuFilt][cIdx];
	if (tmp_saoTypeIdx == 2) {
		local_xCuFilt = xCuFilt;
		local_yCuFilt = yCuFilt;
		tmp_saoTypeIdx0 = saoTypeIdx[local_xCuFilt - 1][local_yCuFilt - 1][cIdx];
		saoTypeIdxBorder[0] = tmp_saoTypeIdx0;
		local_xCuFilt = xCuFilt;
		local_yCuFilt = yCuFilt;
		tmp_saoTypeIdx1 = saoTypeIdx[local_xCuFilt][local_yCuFilt - 1][cIdx];
		saoTypeIdxBorder[1] = tmp_saoTypeIdx1;
		local_xCuFilt = xCuFilt;
		local_yCuFilt = yCuFilt;
		tmp_saoTypeIdx2 = saoTypeIdx[local_xCuFilt + 1][local_yCuFilt - 1][cIdx];
		saoTypeIdxBorder[2] = tmp_saoTypeIdx2;
		local_xCuFilt = xCuFilt;
		local_yCuFilt = yCuFilt;
		tmp_saoTypeIdx3 = saoTypeIdx[local_xCuFilt + 1][local_yCuFilt][cIdx];
		saoTypeIdxBorder[3] = tmp_saoTypeIdx3;
		local_xCuFilt = xCuFilt;
		local_yCuFilt = yCuFilt;
		tmp_saoTypeIdx4 = saoTypeIdx[local_xCuFilt + 1][local_yCuFilt + 1][cIdx];
		saoTypeIdxBorder[4] = tmp_saoTypeIdx4;
		local_xCuFilt = xCuFilt;
		local_yCuFilt = yCuFilt;
		tmp_saoTypeIdx5 = saoTypeIdx[local_xCuFilt][local_yCuFilt + 1][cIdx];
		saoTypeIdxBorder[5] = tmp_saoTypeIdx5;
		local_xCuFilt = xCuFilt;
		local_yCuFilt = yCuFilt;
		tmp_saoTypeIdx6 = saoTypeIdx[local_xCuFilt - 1][local_yCuFilt + 1][cIdx];
		saoTypeIdxBorder[6] = tmp_saoTypeIdx6;
		local_xCuFilt = xCuFilt;
		local_yCuFilt = yCuFilt;
		tmp_saoTypeIdx7 = saoTypeIdx[local_xCuFilt - 1][local_yCuFilt][cIdx];
		saoTypeIdxBorder[7] = tmp_saoTypeIdx7;
		local_xCuFilt = xCuFilt;
		local_yCuFilt = yCuFilt;
		tmp_saoEoClass = saoEoClass[local_xCuFilt][local_yCuFilt][cIdx];
		local_lcuSizeMax = lcuSizeMax;
		tmp_compShift = compShift[cIdx];
		local_filtAcrAllSlc = filtAcrAllSlc;
		local_filtAcrAllTiles = filtAcrAllTiles;
		saoFilterEdge(tmp_saoEoClass, cIdx, cIdx, idxOrig, local_lcuSizeMax >> tmp_compShift, picSize, lcuIsPictBorder, saoOff, local_filtAcrAllSlc && local_filtAcrAllTiles, origPict, PictBuffer, saoTypeIdxBorder);
	} else {
		local_lcuSizeMax = lcuSizeMax;
		tmp_compShift0 = compShift[cIdx];
		tmp_picSize = picSize[0];
		tmp_min = HevcDecoder_SAO_min((local_lcuSizeMax - 1) >> tmp_compShift0, tmp_picSize - rx - 1);
		idxMax[0] = tmp_min + rx;
		local_lcuSizeMax = lcuSizeMax;
		tmp_compShift1 = compShift[cIdx];
		tmp_picSize0 = picSize[1];
		tmp_min0 = HevcDecoder_SAO_min((local_lcuSizeMax - 1) >> tmp_compShift1, tmp_picSize0 - ry - 1);
		idxMax[1] = tmp_min0 + ry;
		local_xCuFilt = xCuFilt;
		local_yCuFilt = yCuFilt;
		tmp_saoLeftClass = saoLeftClass[local_xCuFilt][local_yCuFilt][cIdx];
		saoBandFilter(tmp_saoLeftClass, saoOff, cIdx, cIdx, idxOrig, idxMax, PictBuffer);
	}
}
static void saoFilterEdgeChroma_Horiz(u16 rx, u16 ry, u8 cIdx, u16 picSize[2], i32 lcuIsPictBorder, u8 saoTypeIdxBorder[8]) {
	i16 xMax;
	u16 yMax;
	u16 xIdx;
	u16 yIdx;
	u16 xPix1;
	u16 xPix2;
	i32 pixIsInPict;
	u8 edgeIdx;
	i16 idxMin;
	u8 local_lcuSizeMax;
	u16 tmp_picSize;
	u16 tmp_picSize0;
	i16 y;
	i16 x;
	u8 tmp_PictBuffer;
	u8 tmp_PictBuffer0;
	i8 tmp_Sign3;
	i16 y0;
	u8 tmp_saoTypeIdxBorder;
	u8 tmp_PictBuffer1;
	u8 tmp_origPict;
	i8 tmp_Sign30;
	u8 tmp_PictBuffer2;
	u8 tmp_PictBuffer3;
	i8 tmp_Sign31;
	i16 y1;
	u8 tmp_saoTypeIdxBorder0;
	i32 local_MASK_WIDTH_POW_2;
	u8 tmp_origPict0;
	u8 tmp_PictBuffer4;
	i8 tmp_Sign32;
	u8 tmp_PictBuffer5;
	u8 tmp_PictBuffer6;
	i8 tmp_Sign33;
	u16 tmp_picSize1;
	u8 y2;
	i16 x0;
	i8 tmp_signResult;
	i8 tmp_signResult0;
	u8 tmp_PictBuffer7;
	u8 local_xCuFilt;
	u8 local_yCuFilt;
	i16 tmp_saoOffset;
	i32 tmp_clip_i32;
	i32 local_filtAcrAllSlc;
	i32 local_filtAcrAllTiles;
	u8 y3;
	i16 x1;
	u8 local_log2LcuSizeMax;
	i32 tmp_filtAcrSlc;
	u8 tmp_numSlc;
	u8 tmp_numSlc0;
	i32 tmp_filtAcrTile;
	u8 tmp_numTile;
	u8 tmp_numTile0;
	u8 tmp_origPict1;

	local_lcuSizeMax = lcuSizeMax;
	tmp_picSize = picSize[0];
	xMax = HevcDecoder_SAO_min((local_lcuSizeMax - 1) >> 1, tmp_picSize - rx - 1);
	local_lcuSizeMax = lcuSizeMax;
	tmp_picSize0 = picSize[1];
	yMax = HevcDecoder_SAO_min((local_lcuSizeMax - 1) >> 1, tmp_picSize0 - ry - 1);
	y = 0;
	while (y <= yMax) {
		yIdx = ry + y;
		x = 0;
		while (x <= xMax) {
			xIdx = rx + x;
			xPix2 = xIdx + 1;
			tmp_PictBuffer = PictBuffer[cIdx][yIdx][xPix2];
			tmp_PictBuffer0 = PictBuffer[cIdx][yIdx][xIdx];
			tmp_Sign3 = HevcDecoder_SAO_Sign3(tmp_PictBuffer - tmp_PictBuffer0);
			signResult[cIdx][y][x + 1 & 127] = tmp_Sign3;
			x = x + 1;
		}
		y = y + 1;
	}
	if (rx != 0) {
		xIdx = rx - 1;
		xPix2 = xIdx + 1;
		y0 = 0;
		while (y0 <= yMax) {
			yIdx = ry + y0;
			tmp_saoTypeIdxBorder = saoTypeIdxBorder[7];
			if (tmp_saoTypeIdxBorder != 0) {
				tmp_PictBuffer1 = PictBuffer[cIdx][yIdx][xPix2];
				tmp_origPict = origPict[cIdx][yIdx][xIdx];
				tmp_Sign30 = HevcDecoder_SAO_Sign3(tmp_PictBuffer1 - tmp_origPict);
				signResult[cIdx][y0][0] = tmp_Sign30;
			} else {
				tmp_PictBuffer2 = PictBuffer[cIdx][yIdx][xPix2];
				tmp_PictBuffer3 = PictBuffer[cIdx][yIdx][xIdx];
				tmp_Sign31 = HevcDecoder_SAO_Sign3(tmp_PictBuffer2 - tmp_PictBuffer3);
				signResult[cIdx][y0][0] = tmp_Sign31;
			}
			y0 = y0 + 1;
		}
	}
	local_lcuSizeMax = lcuSizeMax;
	if (xMax == (local_lcuSizeMax - 1) >> 1) {
		local_lcuSizeMax = lcuSizeMax;
		xIdx = rx + ((local_lcuSizeMax - 1) >> 1);
		xPix2 = xIdx + 1;
		y1 = 0;
		while (y1 <= yMax) {
			yIdx = ry + y1;
			local_lcuSizeMax = lcuSizeMax;
			tmp_saoTypeIdxBorder0 = saoTypeIdxBorder[3];
			if (tmp_saoTypeIdxBorder0 != 0) {
				local_MASK_WIDTH_POW_2 = HevcDecoder_SAO_MASK_WIDTH_POW_2;
				tmp_origPict0 = origPict[cIdx][yIdx][xPix2 & local_MASK_WIDTH_POW_2];
				tmp_PictBuffer4 = PictBuffer[cIdx][yIdx][xIdx];
				tmp_Sign32 = HevcDecoder_SAO_Sign3(tmp_origPict0 - tmp_PictBuffer4);
				signResult[cIdx][y1][local_lcuSizeMax >> 1 & 127] = tmp_Sign32;
			} else {
				tmp_PictBuffer5 = PictBuffer[cIdx][yIdx][xPix2];
				tmp_PictBuffer6 = PictBuffer[cIdx][yIdx][xIdx];
				tmp_Sign33 = HevcDecoder_SAO_Sign3(tmp_PictBuffer5 - tmp_PictBuffer6);
				signResult[cIdx][y1][local_lcuSizeMax >> 1 & 127] = tmp_Sign33;
			}
			y1 = y1 + 1;
		}
	}
	idxMin = 0;
	if (lcuIsPictBorder) {
		if (rx == 0) {
			idxMin = 1;
		}
		tmp_picSize1 = picSize[0];
		if (rx + xMax == tmp_picSize1 - 1) {
			xMax = xMax - 1;
		}
	}
	y2 = 0;
	while (y2 <= yMax) {
		yIdx = ry + y2;
		x0 = idxMin;
		while (x0 <= xMax) {
			xIdx = rx + x0;
			xPix1 = xIdx - 1;
			xPix2 = xIdx + 1;
			tmp_signResult = signResult[cIdx][y2][x0];
			tmp_signResult0 = signResult[cIdx][y2][x0 + 1];
			edgeIdx = 2 + tmp_signResult - tmp_signResult0;
			edgeIdx = edgeIdxConv[edgeIdx];
			tmp_PictBuffer7 = PictBuffer[cIdx][yIdx][xIdx];
			local_xCuFilt = xCuFilt;
			local_yCuFilt = yCuFilt;
			tmp_saoOffset = saoOffset[local_xCuFilt][local_yCuFilt][cIdx][edgeIdx];
			tmp_clip_i32 = HevcDecoder_SAO_clip_i32(tmp_PictBuffer7 + tmp_saoOffset, 0, 255);
			PictBuffer[cIdx][yIdx][xIdx] = tmp_clip_i32;
			x0 = x0 + 1;
		}
		y2 = y2 + 1;
	}
	local_filtAcrAllSlc = filtAcrAllSlc;
	local_filtAcrAllTiles = filtAcrAllTiles;
	if (!local_filtAcrAllSlc || !local_filtAcrAllTiles) {
		y3 = 0;
		while (y3 <= yMax) {
			yIdx = ry + y3;
			x1 = idxMin;
			while (x1 <= xMax) {
				xIdx = rx + x1;
				xPix1 = xIdx - 1;
				xPix2 = xIdx + 1;
				local_log2LcuSizeMax = log2LcuSizeMax;
				local_log2LcuSizeMax = log2LcuSizeMax;
				tmp_filtAcrSlc = filtAcrSlc[xIdx >> (local_log2LcuSizeMax - 1)][yIdx >> (local_log2LcuSizeMax - 1)];
				local_log2LcuSizeMax = log2LcuSizeMax;
				local_log2LcuSizeMax = log2LcuSizeMax;
				tmp_numSlc = numSlc[xPix1 >> (local_log2LcuSizeMax - 1)][yIdx >> (local_log2LcuSizeMax - 1)];
				local_log2LcuSizeMax = log2LcuSizeMax;
				local_log2LcuSizeMax = log2LcuSizeMax;
				tmp_numSlc0 = numSlc[xPix2 >> (local_log2LcuSizeMax - 1)][yIdx >> (local_log2LcuSizeMax - 1)];
				local_log2LcuSizeMax = log2LcuSizeMax;
				local_log2LcuSizeMax = log2LcuSizeMax;
				tmp_filtAcrTile = filtAcrTile[xIdx >> (local_log2LcuSizeMax - 1)][yIdx >> (local_log2LcuSizeMax - 1)];
				local_log2LcuSizeMax = log2LcuSizeMax;
				local_log2LcuSizeMax = log2LcuSizeMax;
				tmp_numTile = numTile[xPix1 >> (local_log2LcuSizeMax - 1)][yIdx >> (local_log2LcuSizeMax - 1)];
				local_log2LcuSizeMax = log2LcuSizeMax;
				local_log2LcuSizeMax = log2LcuSizeMax;
				tmp_numTile0 = numTile[xPix2 >> (local_log2LcuSizeMax - 1)][yIdx >> (local_log2LcuSizeMax - 1)];
				pixIsInPict = !(!tmp_filtAcrSlc && tmp_numSlc != tmp_numSlc0) && !(!tmp_filtAcrTile && tmp_numTile != tmp_numTile0);
				if (!pixIsInPict) {
					tmp_origPict1 = origPict[cIdx][yIdx][xIdx];
					PictBuffer[cIdx][yIdx][xIdx] = tmp_origPict1;
				}
				x1 = x1 + 1;
			}
			y3 = y3 + 1;
		}
	}
}
static void saoFilterEdgeChroma_Vert(u16 rx, u16 ry, u8 cIdx, u16 picSize[2], i32 lcuIsPictBorder, u8 saoTypeIdxBorder[8]) {
	u16 xIdx;
	u16 yIdx;
	i16 xMax;
	u16 yMax;
	i32 pixIsInPict;
	u8 edgeIdx;
	i16 idxMin;
	u16 yPix1;
	u16 yPix2;
	u8 local_lcuSizeMax;
	u16 tmp_picSize;
	u16 tmp_picSize0;
	i16 y;
	i16 x;
	u8 tmp_PictBuffer;
	u8 tmp_PictBuffer0;
	i8 tmp_Sign3;
	i16 x0;
	u8 tmp_saoTypeIdxBorder;
	u8 tmp_PictBuffer1;
	u8 tmp_origPict;
	i8 tmp_Sign30;
	u8 tmp_PictBuffer2;
	u8 tmp_PictBuffer3;
	i8 tmp_Sign31;
	i16 x1;
	u8 tmp_saoTypeIdxBorder0;
	i32 local_MASK_HEIGHT_POW_2;
	u8 tmp_origPict0;
	u8 tmp_PictBuffer4;
	i8 tmp_Sign32;
	u8 tmp_PictBuffer5;
	u8 tmp_PictBuffer6;
	i8 tmp_Sign33;
	u16 tmp_picSize1;
	u8 y0;
	i16 x2;
	i8 tmp_signResult;
	i8 tmp_signResult0;
	u8 tmp_PictBuffer7;
	u8 local_xCuFilt;
	u8 local_yCuFilt;
	i16 tmp_saoOffset;
	i32 tmp_clip_i32;
	i32 local_filtAcrAllSlc;
	i32 local_filtAcrAllTiles;
	u8 y1;
	i16 x3;
	u8 local_log2LcuSizeMax;
	i32 tmp_filtAcrSlc;
	u8 tmp_numSlc;
	u8 tmp_numSlc0;
	i32 tmp_filtAcrTile;
	u8 tmp_numTile;
	u8 tmp_numTile0;
	u8 tmp_origPict1;

	local_lcuSizeMax = lcuSizeMax;
	tmp_picSize = picSize[0];
	xMax = HevcDecoder_SAO_min((local_lcuSizeMax - 1) >> 1, tmp_picSize - rx - 1);
	local_lcuSizeMax = lcuSizeMax;
	tmp_picSize0 = picSize[1];
	yMax = HevcDecoder_SAO_min((local_lcuSizeMax - 1) >> 1, tmp_picSize0 - ry - 1);
	y = 0;
	while (y <= yMax) {
		yIdx = ry + y;
		yPix2 = yIdx + 1;
		x = 0;
		while (x <= xMax) {
			xIdx = rx + x;
			tmp_PictBuffer = PictBuffer[cIdx][yPix2][xIdx];
			tmp_PictBuffer0 = PictBuffer[cIdx][yIdx][xIdx];
			tmp_Sign3 = HevcDecoder_SAO_Sign3(tmp_PictBuffer - tmp_PictBuffer0);
			signResult[cIdx][y + 1 & 127][x] = tmp_Sign3;
			x = x + 1;
		}
		y = y + 1;
	}
	if (ry != 0) {
		yIdx = ry - 1;
		yPix2 = yIdx + 1;
		x0 = 0;
		while (x0 <= xMax) {
			xIdx = rx + x0;
			tmp_saoTypeIdxBorder = saoTypeIdxBorder[1];
			if (tmp_saoTypeIdxBorder != 0) {
				tmp_PictBuffer1 = PictBuffer[cIdx][yPix2][xIdx];
				tmp_origPict = origPict[cIdx][yIdx][xIdx];
				tmp_Sign30 = HevcDecoder_SAO_Sign3(tmp_PictBuffer1 - tmp_origPict);
				signResult[cIdx][0][x0] = tmp_Sign30;
			} else {
				tmp_PictBuffer2 = PictBuffer[cIdx][yPix2][xIdx];
				tmp_PictBuffer3 = PictBuffer[cIdx][yIdx][xIdx];
				tmp_Sign31 = HevcDecoder_SAO_Sign3(tmp_PictBuffer2 - tmp_PictBuffer3);
				signResult[cIdx][0][x0] = tmp_Sign31;
			}
			x0 = x0 + 1;
		}
	}
	local_lcuSizeMax = lcuSizeMax;
	if (yMax == (local_lcuSizeMax - 1) >> 1) {
		local_lcuSizeMax = lcuSizeMax;
		yIdx = ry + ((local_lcuSizeMax - 1) >> 1);
		yPix2 = yIdx + 1;
		x1 = 0;
		while (x1 <= xMax) {
			xIdx = rx + x1;
			local_lcuSizeMax = lcuSizeMax;
			tmp_saoTypeIdxBorder0 = saoTypeIdxBorder[5];
			if (tmp_saoTypeIdxBorder0 != 0) {
				local_MASK_HEIGHT_POW_2 = HevcDecoder_SAO_MASK_HEIGHT_POW_2;
				tmp_origPict0 = origPict[cIdx][yPix2 & local_MASK_HEIGHT_POW_2][xIdx];
				tmp_PictBuffer4 = PictBuffer[cIdx][yIdx][xIdx];
				tmp_Sign32 = HevcDecoder_SAO_Sign3(tmp_origPict0 - tmp_PictBuffer4);
				signResult[cIdx][local_lcuSizeMax >> 1 & 127][x1] = tmp_Sign32;
			} else {
				tmp_PictBuffer5 = PictBuffer[cIdx][yPix2][xIdx];
				tmp_PictBuffer6 = PictBuffer[cIdx][yIdx][xIdx];
				tmp_Sign33 = HevcDecoder_SAO_Sign3(tmp_PictBuffer5 - tmp_PictBuffer6);
				signResult[cIdx][local_lcuSizeMax >> 1 & 127][x1] = tmp_Sign33;
			}
			x1 = x1 + 1;
		}
	}
	idxMin = 0;
	if (lcuIsPictBorder) {
		if (ry == 0) {
			idxMin = 1;
		}
		tmp_picSize1 = picSize[1];
		if (ry + yMax == tmp_picSize1 - 1) {
			yMax = yMax - 1;
		}
	}
	y0 = idxMin;
	while (y0 <= yMax) {
		yIdx = ry + y0;
		yPix2 = yIdx + 1;
		x2 = 0;
		while (x2 <= xMax) {
			xIdx = rx + x2;
			tmp_signResult = signResult[cIdx][y0][x2];
			tmp_signResult0 = signResult[cIdx][y0 + 1][x2];
			edgeIdx = 2 + tmp_signResult - tmp_signResult0;
			edgeIdx = edgeIdxConv[edgeIdx];
			tmp_PictBuffer7 = PictBuffer[cIdx][yIdx][xIdx];
			local_xCuFilt = xCuFilt;
			local_yCuFilt = yCuFilt;
			tmp_saoOffset = saoOffset[local_xCuFilt][local_yCuFilt][cIdx][edgeIdx];
			tmp_clip_i32 = HevcDecoder_SAO_clip_i32(tmp_PictBuffer7 + tmp_saoOffset, 0, 255);
			PictBuffer[cIdx][yIdx][xIdx] = tmp_clip_i32;
			x2 = x2 + 1;
		}
		y0 = y0 + 1;
	}
	local_filtAcrAllSlc = filtAcrAllSlc;
	local_filtAcrAllTiles = filtAcrAllTiles;
	if (!local_filtAcrAllSlc || !local_filtAcrAllTiles) {
		y1 = idxMin;
		while (y1 <= yMax) {
			yIdx = ry + y1;
			yPix1 = yIdx - 1;
			yPix2 = yIdx + 1;
			x3 = 0;
			while (x3 <= xMax) {
				xIdx = rx + x3;
				local_log2LcuSizeMax = log2LcuSizeMax;
				local_log2LcuSizeMax = log2LcuSizeMax;
				tmp_filtAcrSlc = filtAcrSlc[xIdx >> (local_log2LcuSizeMax - 1)][yIdx >> (local_log2LcuSizeMax - 1)];
				local_log2LcuSizeMax = log2LcuSizeMax;
				local_log2LcuSizeMax = log2LcuSizeMax;
				tmp_numSlc = numSlc[xIdx >> (local_log2LcuSizeMax - 1)][yPix1 >> (local_log2LcuSizeMax - 1)];
				local_log2LcuSizeMax = log2LcuSizeMax;
				local_log2LcuSizeMax = log2LcuSizeMax;
				tmp_numSlc0 = numSlc[xIdx >> (local_log2LcuSizeMax - 1)][yPix2 >> (local_log2LcuSizeMax - 1)];
				local_log2LcuSizeMax = log2LcuSizeMax;
				local_log2LcuSizeMax = log2LcuSizeMax;
				tmp_filtAcrTile = filtAcrTile[xIdx >> (local_log2LcuSizeMax - 1)][yIdx >> (local_log2LcuSizeMax - 1)];
				local_log2LcuSizeMax = log2LcuSizeMax;
				local_log2LcuSizeMax = log2LcuSizeMax;
				tmp_numTile = numTile[xIdx >> (local_log2LcuSizeMax - 1)][yPix1 >> (local_log2LcuSizeMax - 1)];
				local_log2LcuSizeMax = log2LcuSizeMax;
				local_log2LcuSizeMax = log2LcuSizeMax;
				tmp_numTile0 = numTile[xIdx >> (local_log2LcuSizeMax - 1)][yPix2 >> (local_log2LcuSizeMax - 1)];
				pixIsInPict = !(!tmp_filtAcrSlc && tmp_numSlc != tmp_numSlc0) && !(!tmp_filtAcrTile && tmp_numTile != tmp_numTile0);
				if (!pixIsInPict) {
					tmp_origPict1 = origPict[cIdx][yIdx][xIdx];
					PictBuffer[cIdx][yIdx][xIdx] = tmp_origPict1;
				}
				x3 = x3 + 1;
			}
			y1 = y1 + 1;
		}
	}
}
static void saoFilterEdgeChroma_Diag(u16 rx, u16 ry, u8 cIdx, u16 picSize[2], i32 lcuIsPictBorder, u8 saoTypeIdxBorder[8]) {
	u16 idxOrig[2];
	i16 idxMin[2];
	i16 idxMax[2];
	i16 xMax;
	i16 xIdx;
	i16 yIdx;
	u16 pixIdx[2][2];
	u8 edgeIdx;
	i8 xOff[2];
	i8 yOff[2];
	u8 newPix[66][66];
	u32 k;
	u8 local_xCuFilt;
	u8 local_yCuFilt;
	u8 tmp_saoEoClass;
	i8 tmp_constHPos0;
	u8 tmp_saoEoClass0;
	i8 tmp_constVPos0;
	u8 local_lcuSizeMax;
	u16 tmp_picSize;
	i32 tmp_min;
	u16 tmp_picSize0;
	i32 tmp_min0;
	i8 tmp_xOff;
	i8 tmp_xOff0;
	i16 tmp_idxMax;
	i8 tmp_yOff;
	i16 tmp_idxMin;
	i16 y;
	i16 tmp_idxMax0;
	i8 tmp_xOff1;
	i16 tmp_idxMin0;
	i16 x;
	i8 tmp_yOff0;
	i8 tmp_xOff2;
	u16 tmp_pixIdx;
	u16 tmp_pixIdx0;
	u8 tmp_PictBuffer;
	u8 tmp_PictBuffer0;
	i8 tmp_Sign3;
	u16 tmp_pixIdx1;
	u16 tmp_pixIdx2;
	i16 tmp_idxMax1;
	u16 tmp_picSize1;
	i16 tmp_idxMax2;
	i16 tmp_idxMax3;
	u16 tmp_picSize2;
	i16 tmp_idxMax4;
	i16 y0;
	i16 tmp_idxMax5;
	i16 x0;
	i16 tmp_idxMax6;
	u32 k0;
	i8 tmp_xOff3;
	i8 tmp_yOff1;
	i8 tmp_signResult;
	i8 tmp_yOff2;
	i8 tmp_xOff4;
	i8 tmp_signResult0;
	u8 tmp_PictBuffer1;
	i16 tmp_saoOffset;
	i32 tmp_clip_i32;
	i32 local_filtAcrAllSlc;
	i32 local_filtAcrAllTiles;

	idxOrig[0] = rx;
	idxOrig[1] = ry;
	k = 0;
	while (k <= 1) {
		local_xCuFilt = xCuFilt;
		local_yCuFilt = yCuFilt;
		tmp_saoEoClass = saoEoClass[local_xCuFilt][local_yCuFilt][cIdx];
		tmp_constHPos0 = constHPos0[tmp_saoEoClass][k];
		xOff[k] = tmp_constHPos0;
		local_xCuFilt = xCuFilt;
		local_yCuFilt = yCuFilt;
		tmp_saoEoClass0 = saoEoClass[local_xCuFilt][local_yCuFilt][cIdx];
		tmp_constVPos0 = constVPos0[tmp_saoEoClass0][k];
		yOff[k] = tmp_constVPos0;
		k = k + 1;
	}
	local_lcuSizeMax = lcuSizeMax;
	tmp_picSize = picSize[0];
	tmp_min = HevcDecoder_SAO_min((local_lcuSizeMax - 1) >> 1, tmp_picSize - rx - 1);
	idxMax[0] = tmp_min;
	local_lcuSizeMax = lcuSizeMax;
	tmp_picSize0 = picSize[1];
	tmp_min0 = HevcDecoder_SAO_min((local_lcuSizeMax - 1) >> 1, tmp_picSize0 - ry - 1);
	idxMax[1] = tmp_min0;
	tmp_xOff = xOff[0];
	if (rx == 0 || tmp_xOff != -1) {
		idxMin[0] = 0;
	} else {
		idxMin[0] = -1;
	}
	tmp_xOff0 = xOff[0];
	if (tmp_xOff0 == -1) {
		xMax = idxMax[0];
	} else {
		tmp_idxMax = idxMax[0];
		xMax = tmp_idxMax + 1;
	}
	if (ry == 0) {
		idxMin[1] = 0;
	} else {
		idxMin[1] = -1;
	}
	local_lcuSizeMax = lcuSizeMax;
	revertFiltering(saoTypeIdxBorder, local_lcuSizeMax >> 1, idxOrig, idxMax, cIdx, newPix);
	tmp_yOff = yOff[1];
	tmp_idxMin = idxMin[1];
	pixIdx[1][1] = ry + tmp_yOff + tmp_idxMin;
	y = idxMin[1];
	tmp_idxMax0 = idxMax[1];
	while (y <= tmp_idxMax0) {
		yIdx = ry + y;
		tmp_xOff1 = xOff[1];
		tmp_idxMin0 = idxMin[0];
		pixIdx[1][0] = rx + tmp_xOff1 + tmp_idxMin0;
		x = idxMin[0];
		while (x <= xMax) {
			xIdx = rx + x;
			tmp_yOff0 = yOff[1];
			tmp_xOff2 = xOff[1];
			tmp_pixIdx = pixIdx[1][1];
			tmp_pixIdx0 = pixIdx[1][0];
			tmp_PictBuffer = PictBuffer[cIdx][tmp_pixIdx][tmp_pixIdx0];
			tmp_PictBuffer0 = PictBuffer[cIdx][yIdx][xIdx];
			tmp_Sign3 = HevcDecoder_SAO_Sign3(tmp_PictBuffer - tmp_PictBuffer0);
			signResult[cIdx][y + tmp_yOff0 & 127][x + tmp_xOff2 & 127] = tmp_Sign3;
			tmp_pixIdx1 = pixIdx[1][0];
			pixIdx[1][0] = tmp_pixIdx1 + 1;
			x = x + 1;
		}
		tmp_pixIdx2 = pixIdx[1][1];
		pixIdx[1][1] = tmp_pixIdx2 + 1;
		y = y + 1;
	}
	local_lcuSizeMax = lcuSizeMax;
	putBackFilteredPix(saoTypeIdxBorder, local_lcuSizeMax >> 1, idxOrig, idxMax, cIdx, newPix);
	idxMin[0] = 0;
	idxMin[1] = 0;
	if (lcuIsPictBorder) {
		if (rx == 0) {
			idxMin[0] = 1;
		}
		tmp_idxMax1 = idxMax[0];
		tmp_picSize1 = picSize[0];
		if (rx + tmp_idxMax1 == tmp_picSize1 - 1) {
			tmp_idxMax2 = idxMax[0];
			idxMax[0] = tmp_idxMax2 - 1;
		}
		if (ry == 0) {
			idxMin[1] = 1;
		}
		tmp_idxMax3 = idxMax[1];
		tmp_picSize2 = picSize[1];
		if (ry + tmp_idxMax3 == tmp_picSize2 - 1) {
			tmp_idxMax4 = idxMax[1];
			idxMax[1] = tmp_idxMax4 - 1;
		}
	}
	y0 = idxMin[1];
	tmp_idxMax5 = idxMax[1];
	while (y0 <= tmp_idxMax5) {
		yIdx = ry + y0;
		x0 = idxMin[0];
		tmp_idxMax6 = idxMax[0];
		while (x0 <= tmp_idxMax6) {
			xIdx = rx + x0;
			k0 = 0;
			while (k0 <= 1) {
				tmp_xOff3 = xOff[k0];
				pixIdx[k0][0] = xIdx + tmp_xOff3;
				tmp_yOff1 = yOff[k0];
				pixIdx[k0][1] = yIdx + tmp_yOff1;
				k0 = k0 + 1;
			}
			tmp_signResult = signResult[cIdx][y0][x0];
			tmp_yOff2 = yOff[1];
			tmp_xOff4 = xOff[1];
			tmp_signResult0 = signResult[cIdx][y0 + tmp_yOff2 & 127][x0 + tmp_xOff4 & 127];
			edgeIdx = 2 + tmp_signResult - tmp_signResult0;
			edgeIdx = edgeIdxConv[edgeIdx];
			tmp_PictBuffer1 = PictBuffer[cIdx][yIdx][xIdx];
			local_xCuFilt = xCuFilt;
			local_yCuFilt = yCuFilt;
			tmp_saoOffset = saoOffset[local_xCuFilt][local_yCuFilt][cIdx][edgeIdx];
			tmp_clip_i32 = HevcDecoder_SAO_clip_i32(tmp_PictBuffer1 + tmp_saoOffset, 0, 255);
			PictBuffer[cIdx][yIdx][xIdx] = tmp_clip_i32;
			x0 = x0 + 1;
		}
		y0 = y0 + 1;
	}
	local_filtAcrAllSlc = filtAcrAllSlc;
	local_filtAcrAllTiles = filtAcrAllTiles;
	if (!local_filtAcrAllSlc || !local_filtAcrAllTiles) {
		resetTilesOrSliceEdgeChroma(rx, ry, cIdx, idxMin, idxMax, xOff, yOff);
	}
}
static void filtPrevLcu() {
	u32 cIdx;
	u8 local_xCu;
	u8 local_yCu;
	u8 tmp_saoTypeIdx;
	u8 tmp_saoTypeIdx0;
	u8 tmp_saoEoClass;
	u8 tmp_saoTypeIdx1;
	u8 tmp_saoEoClass0;
	u8 tmp_saoTypeIdx2;
	u8 tmp_saoEoClass1;
	u8 tmp_saoEoClass2;
	u8 tmp_picSizeInCu;
	u8 local_log2LcuSizeMax;
	i32 tmp_mbFiltered;
	u8 tmp_picSizeInCu0;
	i32 tmp_mbFiltered0;

	cIdx = 0;
	while (cIdx <= 2) {
		local_xCu = xCu;
		local_yCu = yCu;
		tmp_saoTypeIdx = saoTypeIdx[local_xCu][local_yCu][cIdx];
		if (tmp_saoTypeIdx == 1) {
			local_xCu = xCu;
			xCuFilt = local_xCu;
			local_yCu = yCu;
			yCuFilt = local_yCu;
			sampAdapOffFilt(cIdx);
		}
		local_xCu = xCu;
		local_yCu = yCu;
		tmp_saoTypeIdx0 = saoTypeIdx[local_xCu - 1][local_yCu][cIdx];
		local_xCu = xCu;
		local_yCu = yCu;
		tmp_saoEoClass = saoEoClass[local_xCu - 1][local_yCu][cIdx];
		if (tmp_saoTypeIdx0 == 2 && tmp_saoEoClass == 0) {
			local_xCu = xCu;
			xCuFilt = local_xCu - 1;
			local_yCu = yCu;
			yCuFilt = local_yCu;
			sampAdapOffFilt(cIdx);
		}
		local_xCu = xCu;
		local_yCu = yCu;
		tmp_saoTypeIdx1 = saoTypeIdx[local_xCu][local_yCu - 1][cIdx];
		local_xCu = xCu;
		local_yCu = yCu;
		tmp_saoEoClass0 = saoEoClass[local_xCu][local_yCu - 1][cIdx];
		if (tmp_saoTypeIdx1 == 2 && tmp_saoEoClass0 == 1) {
			local_xCu = xCu;
			xCuFilt = local_xCu;
			local_yCu = yCu;
			yCuFilt = local_yCu - 1;
			sampAdapOffFilt(cIdx);
		}
		local_xCu = xCu;
		local_yCu = yCu;
		tmp_saoTypeIdx2 = saoTypeIdx[local_xCu - 1][local_yCu - 1][cIdx];
		local_xCu = xCu;
		local_yCu = yCu;
		tmp_saoEoClass1 = saoEoClass[local_xCu - 1][local_yCu - 1][cIdx];
		local_xCu = xCu;
		local_yCu = yCu;
		tmp_saoEoClass2 = saoEoClass[local_xCu - 1][local_yCu - 1][cIdx];
		if (tmp_saoTypeIdx2 == 2 && (tmp_saoEoClass1 == 2 || tmp_saoEoClass2 == 3)) {
			local_xCu = xCu;
			xCuFilt = local_xCu - 1;
			local_yCu = yCu;
			yCuFilt = local_yCu - 1;
			sampAdapOffFilt(cIdx);
		}
		local_xCu = xCu;
		tmp_picSizeInCu = picSizeInCu[0];
		local_yCu = yCu;
		local_xCu = xCu;
		local_log2LcuSizeMax = log2LcuSizeMax;
		local_yCu = yCu;
		local_log2LcuSizeMax = log2LcuSizeMax;
		tmp_mbFiltered = mbFiltered[cIdx][local_xCu << (local_log2LcuSizeMax - 4)][(local_yCu - 1) << (local_log2LcuSizeMax - 4)];
		if (local_xCu == tmp_picSizeInCu - 1 && local_yCu > 0 && !tmp_mbFiltered) {
			local_xCu = xCu;
			xCuFilt = local_xCu;
			local_yCu = yCu;
			yCuFilt = local_yCu - 1;
			sampAdapOffFilt(cIdx);
		}
		local_xCu = xCu;
		local_yCu = yCu;
		tmp_picSizeInCu0 = picSizeInCu[1];
		local_xCu = xCu;
		local_log2LcuSizeMax = log2LcuSizeMax;
		local_yCu = yCu;
		local_log2LcuSizeMax = log2LcuSizeMax;
		tmp_mbFiltered0 = mbFiltered[cIdx][(local_xCu - 1) << (local_log2LcuSizeMax - 4)][local_yCu << (local_log2LcuSizeMax - 4)];
		if (local_xCu > 0 && local_yCu == tmp_picSizeInCu0 - 1 && !tmp_mbFiltered0) {
			local_xCu = xCu;
			xCuFilt = local_xCu - 1;
			local_yCu = yCu;
			yCuFilt = local_yCu;
			sampAdapOffFilt(cIdx);
		}
		cIdx = cIdx + 1;
	}
}
static void sampAdapOffFilt(u32 cIdx) {
	u16 picSizeLoc[2];
	i32 lcuIsPictBorder;
	i8 compShift[3];
	u8 local_xCuFilt;
	u8 local_log2LcuSizeMax;
	u8 local_yCuFilt;
	u16 tmp_picSize;
	u16 tmp_picSize0;
	u8 tmp_saoTypeIdx;
	i8 tmp_compShift;
	i8 tmp_compShift0;

	compShift[0] = 0;
	compShift[1] = 1;
	compShift[2] = 1;
	lcuIsPictBorder = lcuFiltIsPictureBorder();
	local_xCuFilt = xCuFilt;
	local_log2LcuSizeMax = log2LcuSizeMax;
	local_yCuFilt = yCuFilt;
	local_log2LcuSizeMax = log2LcuSizeMax;
	sendFilteredLcu(local_xCuFilt << local_log2LcuSizeMax, local_yCuFilt << local_log2LcuSizeMax, cIdx);
	tmp_picSize = picSize[cIdx][0];
	picSizeLoc[0] = tmp_picSize;
	tmp_picSize0 = picSize[cIdx][1];
	picSizeLoc[1] = tmp_picSize0;
	local_xCuFilt = xCuFilt;
	local_yCuFilt = yCuFilt;
	tmp_saoTypeIdx = saoTypeIdx[local_xCuFilt][local_yCuFilt][cIdx];
	if (tmp_saoTypeIdx != 0) {
		local_xCuFilt = xCuFilt;
		local_log2LcuSizeMax = log2LcuSizeMax;
		tmp_compShift = compShift[cIdx];
		local_yCuFilt = yCuFilt;
		local_log2LcuSizeMax = log2LcuSizeMax;
		tmp_compShift0 = compShift[cIdx];
		codingTreeBlockModif(local_xCuFilt << (local_log2LcuSizeMax - tmp_compShift), local_yCuFilt << (local_log2LcuSizeMax - tmp_compShift0), cIdx, picSizeLoc, lcuIsPictBorder);
	}
}

////////////////////////////////////////////////////////////////////////////////
// Actions
static i32 isSchedulable_isNewPict() {
	i32 result;
	u8 isNewPicSlcLcu;
	u8 local_NEW_PIC;

	isNewPicSlcLcu = tokens_IsPicSlcLcu[(index_IsPicSlcLcu + (0)) % SIZE_IsPicSlcLcu];
	local_NEW_PIC = HevcDecoder_SAO_NEW_PIC;
	result = isNewPicSlcLcu == local_NEW_PIC;
	return result;
}

static void isNewPict() {

	u8 isNewPicSlcLcu;
	u8 log2LcuSz;
	u8 lfAcrossSlcTile;
	u16 picWidthInPix;
	u16 picHeightInPix;
	i16 saoSe;
	u8 local_lcuSizeMax;
	u8 local_log2LcuSizeMax;
	u16 tmp_picSize;
	u16 tmp_picSize0;
	u16 tmp_picSize1;
	u16 tmp_picSize2;
	i32 tmp_slcSaoCompEn;
	i32 local_filtAcrCurrSlc;
	i32 local_filtAcrCurrTile;
	u16 tmp_numTokenPerLcu;
	i32 cIdx;
	i32 i;
	u8 tmp_picSizeInMb;
	i32 j;
	u8 tmp_picSizeInMb0;

	isNewPicSlcLcu = tokens_IsPicSlcLcu[(index_IsPicSlcLcu + (0)) % SIZE_IsPicSlcLcu];
	log2LcuSz = tokens_LcuSizeMax[(index_LcuSizeMax + (0)) % SIZE_LcuSizeMax];
	lfAcrossSlcTile = tokens_LFAcrossSlcTile[(index_LFAcrossSlcTile + (0)) % SIZE_LFAcrossSlcTile];
	picWidthInPix = tokens_PicSize[(index_PicSize + (0)) % SIZE_PicSize];
	picHeightInPix = tokens_PicSize[(index_PicSize + (1)) % SIZE_PicSize];
	saoSe = tokens_SaoSe[(index_SaoSe + (0)) % SIZE_SaoSe];
	lcuSizeMax = 1 << log2LcuSz;
	log2LcuSizeMax = log2LcuSz;
	local_lcuSizeMax = lcuSizeMax;
	local_log2LcuSizeMax = log2LcuSizeMax;
	picSizeInCu[0] = (picWidthInPix + (local_lcuSizeMax - 1)) >> local_log2LcuSizeMax;
	local_lcuSizeMax = lcuSizeMax;
	local_log2LcuSizeMax = log2LcuSizeMax;
	picSizeInCu[1] = (picHeightInPix + (local_lcuSizeMax - 1)) >> local_log2LcuSizeMax;
	picSizeInMb[0] = (picWidthInPix + 15) / 16;
	picSizeInMb[1] = (picHeightInPix + 15) / 16;
	picSize[0][0] = picWidthInPix;
	picSize[0][1] = picHeightInPix;
	tmp_picSize = picSize[0][0];
	picSize[1][0] = tmp_picSize >> 1;
	tmp_picSize0 = picSize[0][1];
	picSize[1][1] = tmp_picSize0 >> 1;
	tmp_picSize1 = picSize[1][0];
	picSize[2][0] = tmp_picSize1;
	tmp_picSize2 = picSize[1][1];
	picSize[2][1] = tmp_picSize2;
	slcSaoCompEn[0] = (saoSe & 1) != 0;
	slcSaoCompEn[1] = (saoSe & 2) != 0;
	tmp_slcSaoCompEn = slcSaoCompEn[1];
	slcSaoCompEn[2] = tmp_slcSaoCompEn;
	filtAcrCurrSlc = (lfAcrossSlcTile & 1) != 0;
	filtAcrCurrTile = (lfAcrossSlcTile & 2) != 0;
	local_filtAcrCurrSlc = filtAcrCurrSlc;
	filtAcrAllSlc = local_filtAcrCurrSlc;
	local_filtAcrCurrTile = filtAcrCurrTile;
	filtAcrAllTiles = local_filtAcrCurrTile;
	numCurrSlc = 0;
	lcuTileIdx = 0;
	numTokenPerLcu[0] = 1 << (2 * log2LcuSz);
	tmp_numTokenPerLcu = numTokenPerLcu[0];
	numTokenPerLcu[1] = tmp_numTokenPerLcu >> 2;
	xMbSent = 0;
	yMbSent = 0;
	xCuFilt = 0;
	yCuFilt = 0;
	xCu = 0;
	yCu = 0;
	cIdx = 0;
	while (cIdx <= 2) {
		i = 0;
		tmp_picSizeInMb = picSizeInMb[0];
		while (i <= tmp_picSizeInMb - 1) {
			j = 0;
			tmp_picSizeInMb0 = picSizeInMb[1];
			while (j <= tmp_picSizeInMb0 - 1) {
				mbFiltered[cIdx][i][j] = 0;
				j = j + 1;
			}
			i = i + 1;
		}
		cIdx = cIdx + 1;
	}

	// Update ports indexes
	index_IsPicSlcLcu += 1;
	index_LcuSizeMax += 1;
	index_LFAcrossSlcTile += 1;
	index_PicSize += 2;
	read_end_PicSize();
	index_SaoSe += 1;

	rate_IsPicSlcLcu += 1;
	rate_LcuSizeMax += 1;
	rate_LFAcrossSlcTile += 1;
	rate_PicSize += 2;
	rate_SaoSe += 1;
}
static void isNewPict_aligned() {

	u8 isNewPicSlcLcu;
	u8 log2LcuSz;
	u8 lfAcrossSlcTile;
	u16 picWidthInPix;
	u16 picHeightInPix;
	i16 saoSe;
	u8 local_lcuSizeMax;
	u8 local_log2LcuSizeMax;
	u16 tmp_picSize;
	u16 tmp_picSize0;
	u16 tmp_picSize1;
	u16 tmp_picSize2;
	i32 tmp_slcSaoCompEn;
	i32 local_filtAcrCurrSlc;
	i32 local_filtAcrCurrTile;
	u16 tmp_numTokenPerLcu;
	i32 cIdx;
	i32 i;
	u8 tmp_picSizeInMb;
	i32 j;
	u8 tmp_picSizeInMb0;

	isNewPicSlcLcu = tokens_IsPicSlcLcu[(index_IsPicSlcLcu + (0)) % SIZE_IsPicSlcLcu];
	log2LcuSz = tokens_LcuSizeMax[(index_LcuSizeMax + (0)) % SIZE_LcuSizeMax];
	lfAcrossSlcTile = tokens_LFAcrossSlcTile[(index_LFAcrossSlcTile + (0)) % SIZE_LFAcrossSlcTile];
	picWidthInPix = tokens_PicSize[(index_PicSize % SIZE_PicSize) + (0)];
	picHeightInPix = tokens_PicSize[(index_PicSize % SIZE_PicSize) + (1)];
	saoSe = tokens_SaoSe[(index_SaoSe + (0)) % SIZE_SaoSe];
	lcuSizeMax = 1 << log2LcuSz;
	log2LcuSizeMax = log2LcuSz;
	local_lcuSizeMax = lcuSizeMax;
	local_log2LcuSizeMax = log2LcuSizeMax;
	picSizeInCu[0] = (picWidthInPix + (local_lcuSizeMax - 1)) >> local_log2LcuSizeMax;
	local_lcuSizeMax = lcuSizeMax;
	local_log2LcuSizeMax = log2LcuSizeMax;
	picSizeInCu[1] = (picHeightInPix + (local_lcuSizeMax - 1)) >> local_log2LcuSizeMax;
	picSizeInMb[0] = (picWidthInPix + 15) / 16;
	picSizeInMb[1] = (picHeightInPix + 15) / 16;
	picSize[0][0] = picWidthInPix;
	picSize[0][1] = picHeightInPix;
	tmp_picSize = picSize[0][0];
	picSize[1][0] = tmp_picSize >> 1;
	tmp_picSize0 = picSize[0][1];
	picSize[1][1] = tmp_picSize0 >> 1;
	tmp_picSize1 = picSize[1][0];
	picSize[2][0] = tmp_picSize1;
	tmp_picSize2 = picSize[1][1];
	picSize[2][1] = tmp_picSize2;
	slcSaoCompEn[0] = (saoSe & 1) != 0;
	slcSaoCompEn[1] = (saoSe & 2) != 0;
	tmp_slcSaoCompEn = slcSaoCompEn[1];
	slcSaoCompEn[2] = tmp_slcSaoCompEn;
	filtAcrCurrSlc = (lfAcrossSlcTile & 1) != 0;
	filtAcrCurrTile = (lfAcrossSlcTile & 2) != 0;
	local_filtAcrCurrSlc = filtAcrCurrSlc;
	filtAcrAllSlc = local_filtAcrCurrSlc;
	local_filtAcrCurrTile = filtAcrCurrTile;
	filtAcrAllTiles = local_filtAcrCurrTile;
	numCurrSlc = 0;
	lcuTileIdx = 0;
	numTokenPerLcu[0] = 1 << (2 * log2LcuSz);
	tmp_numTokenPerLcu = numTokenPerLcu[0];
	numTokenPerLcu[1] = tmp_numTokenPerLcu >> 2;
	xMbSent = 0;
	yMbSent = 0;
	xCuFilt = 0;
	yCuFilt = 0;
	xCu = 0;
	yCu = 0;
	cIdx = 0;
	while (cIdx <= 2) {
		i = 0;
		tmp_picSizeInMb = picSizeInMb[0];
		while (i <= tmp_picSizeInMb - 1) {
			j = 0;
			tmp_picSizeInMb0 = picSizeInMb[1];
			while (j <= tmp_picSizeInMb0 - 1) {
				mbFiltered[cIdx][i][j] = 0;
				j = j + 1;
			}
			i = i + 1;
		}
		cIdx = cIdx + 1;
	}

	// Update ports indexes
	index_IsPicSlcLcu += 1;
	index_LcuSizeMax += 1;
	index_LFAcrossSlcTile += 1;
	index_PicSize += 2;
	read_end_PicSize();
	index_SaoSe += 1;

	rate_IsPicSlcLcu += 1;
	rate_LcuSizeMax += 1;
	rate_LFAcrossSlcTile += 1;
	rate_PicSize += 2;
	rate_SaoSe += 1;
}
static i32 isSchedulable_isNewSlice() {
	i32 result;
	u8 isNewPicSlcLcu;
	u8 local_NEW_SLC;

	isNewPicSlcLcu = tokens_IsPicSlcLcu[(index_IsPicSlcLcu + (0)) % SIZE_IsPicSlcLcu];
	local_NEW_SLC = HevcDecoder_SAO_NEW_SLC;
	result = isNewPicSlcLcu == local_NEW_SLC;
	return result;
}

static void isNewSlice() {

	u8 isNewPicSlcLcu;
	u8 log2LcuSz;
	u8 lfAcrossSlcTile;
	u16 picWidthInPix;
	u16 picHeightInPix;
	i32 local_filtAcrAllSlc;
	i32 local_filtAcrCurrSlc;
	i32 local_filtAcrAllTiles;
	i32 local_filtAcrCurrTile;
	u8 local_numCurrSlc;

	isNewPicSlcLcu = tokens_IsPicSlcLcu[(index_IsPicSlcLcu + (0)) % SIZE_IsPicSlcLcu];
	log2LcuSz = tokens_LcuSizeMax[(index_LcuSizeMax + (0)) % SIZE_LcuSizeMax];
	lfAcrossSlcTile = tokens_LFAcrossSlcTile[(index_LFAcrossSlcTile + (0)) % SIZE_LFAcrossSlcTile];
	picWidthInPix = tokens_PicSize[(index_PicSize + (0)) % SIZE_PicSize];
	picHeightInPix = tokens_PicSize[(index_PicSize + (1)) % SIZE_PicSize];
	filtAcrCurrSlc = (lfAcrossSlcTile & 1) != 0;
	filtAcrCurrTile = (lfAcrossSlcTile & 2) != 0;
	local_filtAcrAllSlc = filtAcrAllSlc;
	local_filtAcrCurrSlc = filtAcrCurrSlc;
	filtAcrAllSlc = local_filtAcrAllSlc && local_filtAcrCurrSlc;
	local_filtAcrAllTiles = filtAcrAllTiles;
	local_filtAcrCurrTile = filtAcrCurrTile;
	filtAcrAllTiles = local_filtAcrAllTiles && local_filtAcrCurrTile;
	local_numCurrSlc = numCurrSlc;
	numCurrSlc = local_numCurrSlc + 1;
	lcuSizeMax = 1 << log2LcuSz;
	log2LcuSizeMax = log2LcuSz;

	// Update ports indexes
	index_IsPicSlcLcu += 1;
	index_LcuSizeMax += 1;
	index_LFAcrossSlcTile += 1;
	index_PicSize += 2;
	read_end_PicSize();

	rate_IsPicSlcLcu += 1;
	rate_LcuSizeMax += 1;
	rate_LFAcrossSlcTile += 1;
	rate_PicSize += 2;
}
static void isNewSlice_aligned() {

	u8 isNewPicSlcLcu;
	u8 log2LcuSz;
	u8 lfAcrossSlcTile;
	u16 picWidthInPix;
	u16 picHeightInPix;
	i32 local_filtAcrAllSlc;
	i32 local_filtAcrCurrSlc;
	i32 local_filtAcrAllTiles;
	i32 local_filtAcrCurrTile;
	u8 local_numCurrSlc;

	isNewPicSlcLcu = tokens_IsPicSlcLcu[(index_IsPicSlcLcu + (0)) % SIZE_IsPicSlcLcu];
	log2LcuSz = tokens_LcuSizeMax[(index_LcuSizeMax + (0)) % SIZE_LcuSizeMax];
	lfAcrossSlcTile = tokens_LFAcrossSlcTile[(index_LFAcrossSlcTile + (0)) % SIZE_LFAcrossSlcTile];
	picWidthInPix = tokens_PicSize[(index_PicSize % SIZE_PicSize) + (0)];
	picHeightInPix = tokens_PicSize[(index_PicSize % SIZE_PicSize) + (1)];
	filtAcrCurrSlc = (lfAcrossSlcTile & 1) != 0;
	filtAcrCurrTile = (lfAcrossSlcTile & 2) != 0;
	local_filtAcrAllSlc = filtAcrAllSlc;
	local_filtAcrCurrSlc = filtAcrCurrSlc;
	filtAcrAllSlc = local_filtAcrAllSlc && local_filtAcrCurrSlc;
	local_filtAcrAllTiles = filtAcrAllTiles;
	local_filtAcrCurrTile = filtAcrCurrTile;
	filtAcrAllTiles = local_filtAcrAllTiles && local_filtAcrCurrTile;
	local_numCurrSlc = numCurrSlc;
	numCurrSlc = local_numCurrSlc + 1;
	lcuSizeMax = 1 << log2LcuSz;
	log2LcuSizeMax = log2LcuSz;

	// Update ports indexes
	index_IsPicSlcLcu += 1;
	index_LcuSizeMax += 1;
	index_LFAcrossSlcTile += 1;
	index_PicSize += 2;
	read_end_PicSize();

	rate_IsPicSlcLcu += 1;
	rate_LcuSizeMax += 1;
	rate_LFAcrossSlcTile += 1;
	rate_PicSize += 2;
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
	u8 local_log2LcuSizeMax;
	u16 tmp_TilesCoord0;
	u16 tmp_TilesCoord1;
	u8 local_lcuSizeMax;
	u16 tmp_TilesCoord2;

	local_iLoop = iLoop;
	tmp_TilesCoord = tokens_TilesCoord[(index_TilesCoord + (0)) % SIZE_TilesCoord];
	local_log2LcuSizeMax = log2LcuSizeMax;
	tilesBeg[local_iLoop][0] = tmp_TilesCoord >> local_log2LcuSizeMax;
	tmp_TilesCoord0 = tokens_TilesCoord[(index_TilesCoord + (1)) % SIZE_TilesCoord];
	local_log2LcuSizeMax = log2LcuSizeMax;
	tilesBeg[local_iLoop][1] = tmp_TilesCoord0 >> local_log2LcuSizeMax;
	local_iLoop = iLoop;
	tmp_TilesCoord1 = tokens_TilesCoord[(index_TilesCoord + (2)) % SIZE_TilesCoord];
	local_lcuSizeMax = lcuSizeMax;
	local_log2LcuSizeMax = log2LcuSizeMax;
	tilesEnd[local_iLoop][0] = (tmp_TilesCoord1 + (local_lcuSizeMax - 1)) >> local_log2LcuSizeMax;
	tmp_TilesCoord2 = tokens_TilesCoord[(index_TilesCoord + (3)) % SIZE_TilesCoord];
	local_lcuSizeMax = lcuSizeMax;
	local_log2LcuSizeMax = log2LcuSizeMax;
	tilesEnd[local_iLoop][1] = (tmp_TilesCoord2 + (local_lcuSizeMax - 1)) >> local_log2LcuSizeMax;
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
	u8 local_log2LcuSizeMax;
	u16 tmp_TilesCoord0;
	u16 tmp_TilesCoord1;
	u8 local_lcuSizeMax;
	u16 tmp_TilesCoord2;

	local_iLoop = iLoop;
	tmp_TilesCoord = tokens_TilesCoord[(index_TilesCoord % SIZE_TilesCoord) + (0)];
	local_log2LcuSizeMax = log2LcuSizeMax;
	tilesBeg[local_iLoop][0] = tmp_TilesCoord >> local_log2LcuSizeMax;
	tmp_TilesCoord0 = tokens_TilesCoord[(index_TilesCoord % SIZE_TilesCoord) + (1)];
	local_log2LcuSizeMax = log2LcuSizeMax;
	tilesBeg[local_iLoop][1] = tmp_TilesCoord0 >> local_log2LcuSizeMax;
	local_iLoop = iLoop;
	tmp_TilesCoord1 = tokens_TilesCoord[(index_TilesCoord % SIZE_TilesCoord) + (2)];
	local_lcuSizeMax = lcuSizeMax;
	local_log2LcuSizeMax = log2LcuSizeMax;
	tilesEnd[local_iLoop][0] = (tmp_TilesCoord1 + (local_lcuSizeMax - 1)) >> local_log2LcuSizeMax;
	tmp_TilesCoord2 = tokens_TilesCoord[(index_TilesCoord % SIZE_TilesCoord) + (3)];
	local_lcuSizeMax = lcuSizeMax;
	local_log2LcuSizeMax = log2LcuSizeMax;
	tilesEnd[local_iLoop][1] = (tmp_TilesCoord2 + (local_lcuSizeMax - 1)) >> local_log2LcuSizeMax;
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
static i32 isSchedulable_checkSliceEn_isFalse() {
	i32 result;
	i32 tmp_slcSaoCompEn;
	i32 tmp_slcSaoCompEn0;

	tmp_slcSaoCompEn = slcSaoCompEn[0];
	tmp_slcSaoCompEn0 = slcSaoCompEn[1];
	result = !tmp_slcSaoCompEn && !tmp_slcSaoCompEn0;
	return result;
}

static void checkSliceEn_isFalse() {



	// Update ports indexes

}
static i32 isSchedulable_checkSliceEn_isTrue() {
	i32 result;
	i32 tmp_slcSaoCompEn;
	i32 tmp_slcSaoCompEn0;

	tmp_slcSaoCompEn = slcSaoCompEn[0];
	tmp_slcSaoCompEn0 = slcSaoCompEn[1];
	result = tmp_slcSaoCompEn || tmp_slcSaoCompEn0;
	return result;
}

static void checkSliceEn_isTrue() {



	// Update ports indexes

}
static i32 isSchedulable_getCuPix_launch_init() {
	i32 result;
	u8 isNewLcu;
	u8 local_NEW_SLC;
	u16 local_lcuTileIdx;
	u16 local_numTiles;

	isNewLcu = tokens_IsPicSlcLcu[(index_IsPicSlcLcu + (0)) % SIZE_IsPicSlcLcu];
	local_NEW_SLC = HevcDecoder_SAO_NEW_SLC;
	local_lcuTileIdx = lcuTileIdx;
	local_numTiles = numTiles;
	result = isNewLcu != local_NEW_SLC && local_lcuTileIdx < local_numTiles;
	return result;
}

static void getCuPix_launch_init() {

	u8 isNewLcu;
	u8 local_xCu;
	u8 local_yCu;
	u8 local_numCurrSlc;
	u16 local_lcuTileIdx;
	i32 local_filtAcrCurrSlc;
	i32 local_filtAcrCurrTile;

	isNewLcu = tokens_IsPicSlcLcu[(index_IsPicSlcLcu + (0)) % SIZE_IsPicSlcLcu];
	local_xCu = xCu;
	local_yCu = yCu;
	local_numCurrSlc = numCurrSlc;
	numSlc[local_xCu][local_yCu] = local_numCurrSlc;
	local_xCu = xCu;
	local_yCu = yCu;
	local_lcuTileIdx = lcuTileIdx;
	numTile[local_xCu][local_yCu] = local_lcuTileIdx;
	local_xCu = xCu;
	local_yCu = yCu;
	local_filtAcrCurrSlc = filtAcrCurrSlc;
	filtAcrSlc[local_xCu][local_yCu] = local_filtAcrCurrSlc;
	local_xCu = xCu;
	local_yCu = yCu;
	local_filtAcrCurrTile = filtAcrCurrTile;
	filtAcrTile[local_xCu][local_yCu] = local_filtAcrCurrTile;

	// Update ports indexes
	index_IsPicSlcLcu += 1;

	rate_IsPicSlcLcu += 1;
}
static i32 isSchedulable_getCuPix_launch_luma() {
	i32 result;
	u16 local_tokenGot;
	u16 tmp_numTokenPerLcu;

	local_tokenGot = tokenGot;
	tmp_numTokenPerLcu = numTokenPerLcu[0];
	result = local_tokenGot < tmp_numTokenPerLcu;
	return result;
}

static void getCuPix_launch_luma() {

	u16 xPic;
	u16 yPic;
	u8 local_xCu;
	u8 local_lcuSizeMax;
	u16 local_tokenGot;
	u8 local_yCu;
	u8 local_log2LcuSizeMax;
	u32 x;
	u8 tmp_SampleIn;

	local_xCu = xCu;
	local_lcuSizeMax = lcuSizeMax;
	local_tokenGot = tokenGot;
	local_lcuSizeMax = lcuSizeMax;
	xPic = local_xCu * local_lcuSizeMax + (local_tokenGot & local_lcuSizeMax - 1);
	local_yCu = yCu;
	local_lcuSizeMax = lcuSizeMax;
	local_tokenGot = tokenGot;
	local_log2LcuSizeMax = log2LcuSizeMax;
	yPic = local_yCu * local_lcuSizeMax + (local_tokenGot >> local_log2LcuSizeMax);
	x = 0;
	while (x <= 15) {
		tmp_SampleIn = tokens_SampleIn[(index_SampleIn + (x)) % SIZE_SampleIn];
		PictBuffer[0][yPic][x + xPic] = tmp_SampleIn;
		x = x + 1;
	}
	local_tokenGot = tokenGot;
	tokenGot = local_tokenGot + 16;

	// Update ports indexes
	index_SampleIn += 16;
	read_end_SampleIn();

	rate_SampleIn += 16;
}
static void getCuPix_launch_luma_aligned() {

	u16 xPic;
	u16 yPic;
	u8 local_xCu;
	u8 local_lcuSizeMax;
	u16 local_tokenGot;
	u8 local_yCu;
	u8 local_log2LcuSizeMax;
	u32 x;
	u8 tmp_SampleIn;

	local_xCu = xCu;
	local_lcuSizeMax = lcuSizeMax;
	local_tokenGot = tokenGot;
	local_lcuSizeMax = lcuSizeMax;
	xPic = local_xCu * local_lcuSizeMax + (local_tokenGot & local_lcuSizeMax - 1);
	local_yCu = yCu;
	local_lcuSizeMax = lcuSizeMax;
	local_tokenGot = tokenGot;
	local_log2LcuSizeMax = log2LcuSizeMax;
	yPic = local_yCu * local_lcuSizeMax + (local_tokenGot >> local_log2LcuSizeMax);
	x = 0;
	while (x <= 15) {
		tmp_SampleIn = tokens_SampleIn[(index_SampleIn % SIZE_SampleIn) + (x)];
		PictBuffer[0][yPic][x + xPic] = tmp_SampleIn;
		x = x + 1;
	}
	local_tokenGot = tokenGot;
	tokenGot = local_tokenGot + 16;

	// Update ports indexes
	index_SampleIn += 16;
	read_end_SampleIn();

	rate_SampleIn += 16;
}
static i32 isSchedulable_getCuPix_launch_lumaDone() {
	i32 result;
	u16 local_tokenGot;
	u16 tmp_numTokenPerLcu;

	local_tokenGot = tokenGot;
	tmp_numTokenPerLcu = numTokenPerLcu[0];
	result = local_tokenGot == tmp_numTokenPerLcu;
	return result;
}

static void getCuPix_launch_lumaDone() {


	tokenGot = 0;
	cIdx = 1;

	// Update ports indexes

}
static i32 isSchedulable_getCuPix_launch_chroma() {
	i32 result;
	u8 local_cIdx;

	local_cIdx = cIdx;
	result = local_cIdx < 3;
	return result;
}

static void getCuPix_launch_chroma() {

	u16 xPic;
	u16 yPic;
	u8 local_xCu;
	u8 local_lcuSizeMax;
	u16 local_tokenGot;
	u8 local_yCu;
	u8 local_log2LcuSizeMax;
	u32 x;
	u8 local_cIdx;
	u8 tmp_SampleIn;
	u16 tmp_numTokenPerLcu;

	local_xCu = xCu;
	local_lcuSizeMax = lcuSizeMax;
	local_tokenGot = tokenGot;
	local_lcuSizeMax = lcuSizeMax;
	xPic = local_xCu * (local_lcuSizeMax >> 1) + (local_tokenGot & (local_lcuSizeMax - 1) >> 1);
	local_yCu = yCu;
	local_lcuSizeMax = lcuSizeMax;
	local_tokenGot = tokenGot;
	local_log2LcuSizeMax = log2LcuSizeMax;
	yPic = local_yCu * (local_lcuSizeMax >> 1) + (local_tokenGot >> (local_log2LcuSizeMax - 1));
	x = 0;
	while (x <= 7) {
		local_cIdx = cIdx;
		tmp_SampleIn = tokens_SampleIn[(index_SampleIn + (x)) % SIZE_SampleIn];
		PictBuffer[local_cIdx][yPic][x + xPic] = tmp_SampleIn;
		x = x + 1;
	}
	local_tokenGot = tokenGot;
	tokenGot = local_tokenGot + 8;
	local_tokenGot = tokenGot;
	tmp_numTokenPerLcu = numTokenPerLcu[1];
	if (local_tokenGot == tmp_numTokenPerLcu) {
		tokenGot = 0;
		local_cIdx = cIdx;
		cIdx = local_cIdx + 1;
	}

	// Update ports indexes
	index_SampleIn += 8;
	read_end_SampleIn();

	rate_SampleIn += 8;
}
static void getCuPix_launch_chroma_aligned() {

	u16 xPic;
	u16 yPic;
	u8 local_xCu;
	u8 local_lcuSizeMax;
	u16 local_tokenGot;
	u8 local_yCu;
	u8 local_log2LcuSizeMax;
	u32 x;
	u8 local_cIdx;
	u8 tmp_SampleIn;
	u16 tmp_numTokenPerLcu;

	local_xCu = xCu;
	local_lcuSizeMax = lcuSizeMax;
	local_tokenGot = tokenGot;
	local_lcuSizeMax = lcuSizeMax;
	xPic = local_xCu * (local_lcuSizeMax >> 1) + (local_tokenGot & (local_lcuSizeMax - 1) >> 1);
	local_yCu = yCu;
	local_lcuSizeMax = lcuSizeMax;
	local_tokenGot = tokenGot;
	local_log2LcuSizeMax = log2LcuSizeMax;
	yPic = local_yCu * (local_lcuSizeMax >> 1) + (local_tokenGot >> (local_log2LcuSizeMax - 1));
	x = 0;
	while (x <= 7) {
		local_cIdx = cIdx;
		tmp_SampleIn = tokens_SampleIn[(index_SampleIn % SIZE_SampleIn) + (x)];
		PictBuffer[local_cIdx][yPic][x + xPic] = tmp_SampleIn;
		x = x + 1;
	}
	local_tokenGot = tokenGot;
	tokenGot = local_tokenGot + 8;
	local_tokenGot = tokenGot;
	tmp_numTokenPerLcu = numTokenPerLcu[1];
	if (local_tokenGot == tmp_numTokenPerLcu) {
		tokenGot = 0;
		local_cIdx = cIdx;
		cIdx = local_cIdx + 1;
	}

	// Update ports indexes
	index_SampleIn += 8;
	read_end_SampleIn();

	rate_SampleIn += 8;
}
static i32 isSchedulable_getCuPix_launch_chromaDone() {
	i32 result;
	u8 local_cIdx;

	local_cIdx = cIdx;
	result = local_cIdx == 3;
	return result;
}

static void getCuPix_launch_chromaDone() {

	u8 local_xCu;
	u8 local_yCu;
	u8 local_numCurrSlc;
	i32 local_filtAcrCurrSlc;

	cIdx = 0;
	local_xCu = xCu;
	local_yCu = yCu;
	local_numCurrSlc = numCurrSlc;
	numSlc[local_xCu][local_yCu] = local_numCurrSlc;
	local_xCu = xCu;
	local_yCu = yCu;
	local_filtAcrCurrSlc = filtAcrCurrSlc;
	filtAcrSlc[local_xCu][local_yCu] = local_filtAcrCurrSlc;

	// Update ports indexes

}
static i32 isSchedulable_getCuPix_done() {
	i32 result;
	u16 local_lcuTileIdx;
	u16 local_numTiles;

	local_lcuTileIdx = lcuTileIdx;
	local_numTiles = numTiles;
	result = local_lcuTileIdx == local_numTiles;
	return result;
}

static void getCuPix_done() {

	u8 tmp_picSizeInCu;
	u8 tmp_picSizeInCu0;
	u32 cIdx;
	u8 local_xCuFilt;
	u8 local_log2LcuSizeMax;
	u8 local_yCuFilt;
	i32 tmp_mbFiltered;

	tmp_picSizeInCu = picSizeInCu[0];
	xCuFilt = tmp_picSizeInCu - 1;
	tmp_picSizeInCu0 = picSizeInCu[1];
	yCuFilt = tmp_picSizeInCu0 - 1;
	cIdx = 0;
	while (cIdx <= 2) {
		local_xCuFilt = xCuFilt;
		local_log2LcuSizeMax = log2LcuSizeMax;
		local_yCuFilt = yCuFilt;
		local_log2LcuSizeMax = log2LcuSizeMax;
		tmp_mbFiltered = mbFiltered[cIdx][local_xCuFilt << (local_log2LcuSizeMax - 4)][local_yCuFilt << (local_log2LcuSizeMax - 4)];
		if (!tmp_mbFiltered) {
			sampAdapOffFilt(cIdx);
		}
		cIdx = cIdx + 1;
	}
	xCu = 0;
	yCu = 0;

	// Update ports indexes

}
static i32 isSchedulable_getSaoMerge_noMerge() {
	i32 result;
	i16 mergeInfo;
	u8 local_SAO_NO_MERGE;

	mergeInfo = tokens_SaoSe[(index_SaoSe + (0)) % SIZE_SaoSe];
	local_SAO_NO_MERGE = HevcDecoder_SAO_SAO_NO_MERGE;
	result = mergeInfo == local_SAO_NO_MERGE;
	return result;
}

static void getSaoMerge_noMerge() {

	i16 mergeInfo;
	i32 local_DEBUG_Trace;

	mergeInfo = tokens_SaoSe[(index_SaoSe + (0)) % SIZE_SaoSe];
	local_DEBUG_Trace = DEBUG_Trace;
	if (local_DEBUG_Trace) {
		printf("=== getSaoMerge.noMerge ===\n");
		printf("SaoSe       = %i\n", mergeInfo);
	}

	// Update ports indexes
	index_SaoSe += 1;

	rate_SaoSe += 1;
}
static i32 isSchedulable_getSaoMerge_merge() {
	i32 result;
	i16 mergeInfo;
	u8 local_SAO_NO_MERGE;

	mergeInfo = tokens_SaoSe[(index_SaoSe + (0)) % SIZE_SaoSe];
	local_SAO_NO_MERGE = HevcDecoder_SAO_SAO_NO_MERGE;
	result = mergeInfo != local_SAO_NO_MERGE;
	return result;
}

static void getSaoMerge_merge() {

	i16 mergeInfo;
	u8 local_SAO_MERGE_LEFT;
	u8 local_xCu;
	u16 xMerge;
	u8 local_SAO_MERGE_UP;
	u8 local_yCu;
	u16 yMerge;
	i32 local_DEBUG_Trace;
	u32 cIdx;
	u8 tmp_saoTypeIdx;
	u8 tmp_saoTypeIdx0;
	u8 local_log2LcuSizeMax;
	u32 i;
	i16 tmp_saoOffset;
	u8 tmp_saoEoClass;
	u8 tmp_saoLeftClass;

	mergeInfo = tokens_SaoSe[(index_SaoSe + (0)) % SIZE_SaoSe];
	local_SAO_MERGE_LEFT = HevcDecoder_SAO_SAO_MERGE_LEFT;
	if (mergeInfo == local_SAO_MERGE_LEFT) {
		local_xCu = xCu;
		xMerge = local_xCu - 1;
	} else {
		local_xCu = xCu;
		xMerge = local_xCu;
	}
	local_SAO_MERGE_UP = HevcDecoder_SAO_SAO_MERGE_UP;
	if (mergeInfo == local_SAO_MERGE_UP) {
		local_yCu = yCu;
		yMerge = local_yCu - 1;
	} else {
		local_yCu = yCu;
		yMerge = local_yCu;
	}
	local_DEBUG_Trace = DEBUG_Trace;
	if (local_DEBUG_Trace) {
		printf("=== getSaoMerge.Merge ===\n");
		printf("SaoSe       = %i\n", mergeInfo);
	}
	cIdx = 0;
	while (cIdx <= 2) {
		local_xCu = xCu;
		local_yCu = yCu;
		tmp_saoTypeIdx = saoTypeIdx[xMerge][yMerge][cIdx];
		saoTypeIdx[local_xCu][local_yCu][cIdx] = tmp_saoTypeIdx;
		local_xCu = xCu;
		local_yCu = yCu;
		tmp_saoTypeIdx0 = saoTypeIdx[local_xCu][local_yCu][cIdx];
		if (tmp_saoTypeIdx0 == 0) {
			local_xCu = xCu;
			local_log2LcuSizeMax = log2LcuSizeMax;
			local_yCu = yCu;
			local_log2LcuSizeMax = log2LcuSizeMax;
			sendFilteredLcu(local_xCu << local_log2LcuSizeMax, local_yCu << local_log2LcuSizeMax, cIdx);
		} else {
			i = 1;
			while (i <= 4) {
				local_xCu = xCu;
				local_yCu = yCu;
				tmp_saoOffset = saoOffset[xMerge][yMerge][cIdx][i];
				saoOffset[local_xCu][local_yCu][cIdx][i] = tmp_saoOffset;
				i = i + 1;
			}
			local_xCu = xCu;
			local_yCu = yCu;
			tmp_saoEoClass = saoEoClass[xMerge][yMerge][cIdx];
			saoEoClass[local_xCu][local_yCu][cIdx] = tmp_saoEoClass;
			local_xCu = xCu;
			local_yCu = yCu;
			tmp_saoLeftClass = saoLeftClass[xMerge][yMerge][cIdx];
			saoLeftClass[local_xCu][local_yCu][cIdx] = tmp_saoLeftClass;
			saveLcuBorder(cIdx);
		}
		cIdx = cIdx + 1;
	}
	filtPrevLcu();
	nextLcuAddress();

	// Update ports indexes
	index_SaoSe += 1;

	rate_SaoSe += 1;
}
static i32 isSchedulable_getSaoMerge_skip() {
	i32 result;

	result = 1;
	return result;
}

static void getSaoMerge_skip() {

	u8 local_xCu;
	u8 local_yCu;
	u8 local_log2LcuSizeMax;

	local_xCu = xCu;
	local_yCu = yCu;
	saoTypeIdx[local_xCu][local_yCu][0] = 0;
	saoTypeIdx[local_xCu][local_yCu][1] = 0;
	saoTypeIdx[local_xCu][local_yCu][2] = 0;
	local_xCu = xCu;
	local_log2LcuSizeMax = log2LcuSizeMax;
	local_yCu = yCu;
	local_log2LcuSizeMax = log2LcuSizeMax;
	sendFilteredLcu(local_xCu << local_log2LcuSizeMax, local_yCu << local_log2LcuSizeMax, 0);
	local_xCu = xCu;
	local_log2LcuSizeMax = log2LcuSizeMax;
	local_yCu = yCu;
	local_log2LcuSizeMax = log2LcuSizeMax;
	sendFilteredLcu(local_xCu << local_log2LcuSizeMax, local_yCu << local_log2LcuSizeMax, 1);
	local_xCu = xCu;
	local_log2LcuSizeMax = log2LcuSizeMax;
	local_yCu = yCu;
	local_log2LcuSizeMax = log2LcuSizeMax;
	sendFilteredLcu(local_xCu << local_log2LcuSizeMax, local_yCu << local_log2LcuSizeMax, 2);
	nextLcuAddress();

	// Update ports indexes

}
static i32 isSchedulable_getSaoTypeIdx_is0() {
	i32 result;
	i16 typeIdx;
	u8 local_cIdx;
	i32 tmp_if;

	typeIdx = tokens_SaoSe[(index_SaoSe + (0)) % SIZE_SaoSe];
	local_cIdx = cIdx;
	if (local_cIdx < 3 && typeIdx == 0) {
		local_cIdx = cIdx;
		tmp_if = slcSaoCompEn[local_cIdx];
	} else {
		tmp_if = 0;
	}
	result = tmp_if;
	return result;
}

static void getSaoTypeIdx_is0() {

	i16 typeIdx;
	i32 local_DEBUG_Trace;
	u8 local_xCu;
	u8 local_log2LcuSizeMax;
	u8 local_yCu;
	u8 local_cIdx;

	typeIdx = tokens_SaoSe[(index_SaoSe + (0)) % SIZE_SaoSe];
	local_DEBUG_Trace = DEBUG_Trace;
	if (local_DEBUG_Trace) {
		printf("=== getSaoTypeIdx.is0 ===\n");
		printf("SaoSe       = %i\n", typeIdx);
	}
	local_xCu = xCu;
	local_log2LcuSizeMax = log2LcuSizeMax;
	local_yCu = yCu;
	local_log2LcuSizeMax = log2LcuSizeMax;
	local_cIdx = cIdx;
	sendFilteredLcu(local_xCu << local_log2LcuSizeMax, local_yCu << local_log2LcuSizeMax, local_cIdx);
	local_xCu = xCu;
	local_yCu = yCu;
	local_cIdx = cIdx;
	saoTypeIdx[local_xCu][local_yCu][local_cIdx] = 0;
	local_cIdx = cIdx;
	cIdx = local_cIdx + 1;

	// Update ports indexes
	index_SaoSe += 1;

	rate_SaoSe += 1;
}
static i32 isSchedulable_getSaoTypeIdx_isNot0() {
	i32 result;
	u8 local_cIdx;
	i32 tmp_if;
	i32 tmp_slcSaoCompEn;
	i16 tmp_SaoSe;

	local_cIdx = cIdx;
	if (local_cIdx < 3) {
		local_cIdx = cIdx;
		tmp_slcSaoCompEn = slcSaoCompEn[local_cIdx];
		tmp_SaoSe = tokens_SaoSe[(index_SaoSe + (0)) % SIZE_SaoSe];
		tmp_if = tmp_slcSaoCompEn && tmp_SaoSe != 0;
	} else {
		tmp_if = 0;
	}
	result = tmp_if;
	return result;
}

static void getSaoTypeIdx_isNot0() {

	i32 local_DEBUG_Trace;
	u32 i;
	i16 tmp_SaoSe;
	u8 local_cIdx;
	u8 local_xCu;
	u8 local_yCu;
	i16 tmp_SaoSe0;
	u32 i0;
	i16 tmp_SaoSe1;
	u8 tmp_saoTypeIdx;
	i16 tmp_SaoSe2;
	i16 tmp_SaoSe3;

	local_DEBUG_Trace = DEBUG_Trace;
	if (local_DEBUG_Trace) {
		printf("=== getSaoTypeIdx.isNot0 ===\n");
		printf("SaoSe       = [");
		i = 0;
		while (i <= 5) {
			tmp_SaoSe = tokens_SaoSe[(index_SaoSe + (i)) % SIZE_SaoSe];
			printf("%i, ", tmp_SaoSe);
			i = i + 1;
		}
		printf("]\n");
	}
	local_cIdx = cIdx;
	saveLcuBorder(local_cIdx);
	local_xCu = xCu;
	local_yCu = yCu;
	local_cIdx = cIdx;
	tmp_SaoSe0 = tokens_SaoSe[(index_SaoSe + (0)) % SIZE_SaoSe];
	saoTypeIdx[local_xCu][local_yCu][local_cIdx] = tmp_SaoSe0;
	i0 = 1;
	while (i0 <= 4) {
		local_xCu = xCu;
		local_yCu = yCu;
		local_cIdx = cIdx;
		tmp_SaoSe1 = tokens_SaoSe[(index_SaoSe + (i0)) % SIZE_SaoSe];
		saoOffset[local_xCu][local_yCu][local_cIdx][i0] = tmp_SaoSe1;
		i0 = i0 + 1;
	}
	local_xCu = xCu;
	local_yCu = yCu;
	local_cIdx = cIdx;
	tmp_saoTypeIdx = saoTypeIdx[local_xCu][local_yCu][local_cIdx];
	if (tmp_saoTypeIdx == 2) {
		local_xCu = xCu;
		local_yCu = yCu;
		local_cIdx = cIdx;
		tmp_SaoSe2 = tokens_SaoSe[(index_SaoSe + (5)) % SIZE_SaoSe];
		saoEoClass[local_xCu][local_yCu][local_cIdx] = tmp_SaoSe2;
	} else {
		local_xCu = xCu;
		local_yCu = yCu;
		local_cIdx = cIdx;
		tmp_SaoSe3 = tokens_SaoSe[(index_SaoSe + (5)) % SIZE_SaoSe];
		saoLeftClass[local_xCu][local_yCu][local_cIdx] = tmp_SaoSe3;
	}
	local_cIdx = cIdx;
	cIdx = local_cIdx + 1;

	// Update ports indexes
	index_SaoSe += 6;
	read_end_SaoSe();

	rate_SaoSe += 6;
}
static void getSaoTypeIdx_isNot0_aligned() {

	i32 local_DEBUG_Trace;
	u32 i;
	i16 tmp_SaoSe;
	u8 local_cIdx;
	u8 local_xCu;
	u8 local_yCu;
	i16 tmp_SaoSe0;
	u32 i0;
	i16 tmp_SaoSe1;
	u8 tmp_saoTypeIdx;
	i16 tmp_SaoSe2;
	i16 tmp_SaoSe3;

	local_DEBUG_Trace = DEBUG_Trace;
	if (local_DEBUG_Trace) {
		printf("=== getSaoTypeIdx.isNot0 ===\n");
		printf("SaoSe       = [");
		i = 0;
		while (i <= 5) {
			tmp_SaoSe = tokens_SaoSe[(index_SaoSe % SIZE_SaoSe) + (i)];
			printf("%i, ", tmp_SaoSe);
			i = i + 1;
		}
		printf("]\n");
	}
	local_cIdx = cIdx;
	saveLcuBorder(local_cIdx);
	local_xCu = xCu;
	local_yCu = yCu;
	local_cIdx = cIdx;
	tmp_SaoSe0 = tokens_SaoSe[(index_SaoSe % SIZE_SaoSe) + (0)];
	saoTypeIdx[local_xCu][local_yCu][local_cIdx] = tmp_SaoSe0;
	i0 = 1;
	while (i0 <= 4) {
		local_xCu = xCu;
		local_yCu = yCu;
		local_cIdx = cIdx;
		tmp_SaoSe1 = tokens_SaoSe[(index_SaoSe % SIZE_SaoSe) + (i0)];
		saoOffset[local_xCu][local_yCu][local_cIdx][i0] = tmp_SaoSe1;
		i0 = i0 + 1;
	}
	local_xCu = xCu;
	local_yCu = yCu;
	local_cIdx = cIdx;
	tmp_saoTypeIdx = saoTypeIdx[local_xCu][local_yCu][local_cIdx];
	if (tmp_saoTypeIdx == 2) {
		local_xCu = xCu;
		local_yCu = yCu;
		local_cIdx = cIdx;
		tmp_SaoSe2 = tokens_SaoSe[(index_SaoSe % SIZE_SaoSe) + (5)];
		saoEoClass[local_xCu][local_yCu][local_cIdx] = tmp_SaoSe2;
	} else {
		local_xCu = xCu;
		local_yCu = yCu;
		local_cIdx = cIdx;
		tmp_SaoSe3 = tokens_SaoSe[(index_SaoSe % SIZE_SaoSe) + (5)];
		saoLeftClass[local_xCu][local_yCu][local_cIdx] = tmp_SaoSe3;
	}
	local_cIdx = cIdx;
	cIdx = local_cIdx + 1;

	// Update ports indexes
	index_SaoSe += 6;
	read_end_SaoSe();

	rate_SaoSe += 6;
}
static i32 isSchedulable_getSaoTypeIdx_skip() {
	i32 result;
	u8 local_cIdx;
	i32 tmp_if;
	i32 tmp_slcSaoCompEn;

	local_cIdx = cIdx;
	if (local_cIdx < 3) {
		local_cIdx = cIdx;
		tmp_slcSaoCompEn = slcSaoCompEn[local_cIdx];
		tmp_if = !tmp_slcSaoCompEn;
	} else {
		tmp_if = 0;
	}
	result = tmp_if;
	return result;
}

static void getSaoTypeIdx_skip() {

	u8 local_xCu;
	u8 local_log2LcuSizeMax;
	u8 local_yCu;
	u8 local_cIdx;

	local_xCu = xCu;
	local_log2LcuSizeMax = log2LcuSizeMax;
	local_yCu = yCu;
	local_log2LcuSizeMax = log2LcuSizeMax;
	local_cIdx = cIdx;
	sendFilteredLcu(local_xCu << local_log2LcuSizeMax, local_yCu << local_log2LcuSizeMax, local_cIdx);
	local_xCu = xCu;
	local_yCu = yCu;
	local_cIdx = cIdx;
	saoTypeIdx[local_xCu][local_yCu][local_cIdx] = 0;
	local_cIdx = cIdx;
	cIdx = local_cIdx + 1;

	// Update ports indexes

}
static i32 isSchedulable_getSaoTypeIdxDone() {
	i32 result;
	u8 local_cIdx;

	local_cIdx = cIdx;
	result = local_cIdx == 3;
	return result;
}

static void getSaoTypeIdxDone() {


	cIdx = 0;
	filtPrevLcu();
	nextLcuAddress();

	// Update ports indexes

}
static i32 isSchedulable_sendSamples_launch() {
	i32 result;

	result = 1;
	return result;
}

static void sendSamples_launch() {

	u32 tokenOffset;
	u16 blkAddrX;
	u16 blkAddrY;
	u8 local_xMbSent;
	u8 local_yMbSent;
	u32 y;
	u32 x;
	i32 local_DEBUG;
	u8 tmp_PictBuffer;
	u16 tmp_picSize;
	u16 tmp_picSize0;
	u8 tmp_PictBuffer0;
	u32 comp;
	u32 y0;
	u32 x0;
	u8 tmp_PictBuffer1;
	u16 tmp_picSize1;
	u16 tmp_picSize2;
	u8 tmp_PictBuffer2;

	local_xMbSent = xMbSent;
	blkAddrX = local_xMbSent * 16;
	local_yMbSent = yMbSent;
	blkAddrY = local_yMbSent * 16;
	y = 0;
	while (y <= 15) {
		x = 0;
		while (x <= 15) {
			local_DEBUG = DEBUG;
			if (!local_DEBUG) {
				tmp_PictBuffer = PictBuffer[0][blkAddrY + y][blkAddrX + x];
				tokens_FiltSample[(index_FiltSample + (x + y * 16)) % SIZE_FiltSample] = tmp_PictBuffer;
			} else {
				tmp_picSize = picSize[0][0];
				tmp_picSize0 = picSize[0][1];
				if (blkAddrX + x < tmp_picSize && blkAddrY + y < tmp_picSize0) {
					tmp_PictBuffer0 = PictBuffer[0][blkAddrY + y][blkAddrX + x];
					tokens_FiltSample[(index_FiltSample + (x + y * 16)) % SIZE_FiltSample] = tmp_PictBuffer0;
				} else {
					tokens_FiltSample[(index_FiltSample + (x + y * 16)) % SIZE_FiltSample] = 0;
				}
			}
			x = x + 1;
		}
		y = y + 1;
	}
	blkAddrX = blkAddrX >> 1;
	blkAddrY = blkAddrY >> 1;
	tokenOffset = 16 * 16;
	comp = 1;
	while (comp <= 2) {
		y0 = 0;
		while (y0 <= 7) {
			x0 = 0;
			while (x0 <= 7) {
				local_DEBUG = DEBUG;
				if (!local_DEBUG) {
					tmp_PictBuffer1 = PictBuffer[comp][blkAddrY + y0][blkAddrX + x0];
					tokens_FiltSample[(index_FiltSample + (x0 + y0 * 8 + tokenOffset)) % SIZE_FiltSample] = tmp_PictBuffer1;
				} else {
					tmp_picSize1 = picSize[0][0];
					tmp_picSize2 = picSize[0][1];
					if (blkAddrX + x0 < tmp_picSize1 / 2 && blkAddrY + y0 < tmp_picSize2 / 2) {
						tmp_PictBuffer2 = PictBuffer[comp][blkAddrY + y0][blkAddrX + x0];
						tokens_FiltSample[(index_FiltSample + (x0 + y0 * 8 + tokenOffset)) % SIZE_FiltSample] = tmp_PictBuffer2;
					} else {
						tokens_FiltSample[(index_FiltSample + (x0 + y0 * 8 + tokenOffset)) % SIZE_FiltSample] = 0;
					}
				}
				x0 = x0 + 1;
			}
			y0 = y0 + 1;
		}
		tokenOffset = tokenOffset + 8 * 8;
		comp = comp + 1;
	}
	nextMbAddr();

	// Update ports indexes
	index_FiltSample += 384;
	write_end_FiltSample();

}
static void sendSamples_launch_aligned() {

	u32 tokenOffset;
	u16 blkAddrX;
	u16 blkAddrY;
	u8 local_xMbSent;
	u8 local_yMbSent;
	u32 y;
	u32 x;
	i32 local_DEBUG;
	u8 tmp_PictBuffer;
	u16 tmp_picSize;
	u16 tmp_picSize0;
	u8 tmp_PictBuffer0;
	u32 comp;
	u32 y0;
	u32 x0;
	u8 tmp_PictBuffer1;
	u16 tmp_picSize1;
	u16 tmp_picSize2;
	u8 tmp_PictBuffer2;

	local_xMbSent = xMbSent;
	blkAddrX = local_xMbSent * 16;
	local_yMbSent = yMbSent;
	blkAddrY = local_yMbSent * 16;
	y = 0;
	while (y <= 15) {
		x = 0;
		while (x <= 15) {
			local_DEBUG = DEBUG;
			if (!local_DEBUG) {
				tmp_PictBuffer = PictBuffer[0][blkAddrY + y][blkAddrX + x];
				tokens_FiltSample[(index_FiltSample % SIZE_FiltSample) + (x + y * 16)] = tmp_PictBuffer;
			} else {
				tmp_picSize = picSize[0][0];
				tmp_picSize0 = picSize[0][1];
				if (blkAddrX + x < tmp_picSize && blkAddrY + y < tmp_picSize0) {
					tmp_PictBuffer0 = PictBuffer[0][blkAddrY + y][blkAddrX + x];
					tokens_FiltSample[(index_FiltSample % SIZE_FiltSample) + (x + y * 16)] = tmp_PictBuffer0;
				} else {
					tokens_FiltSample[(index_FiltSample % SIZE_FiltSample) + (x + y * 16)] = 0;
				}
			}
			x = x + 1;
		}
		y = y + 1;
	}
	blkAddrX = blkAddrX >> 1;
	blkAddrY = blkAddrY >> 1;
	tokenOffset = 16 * 16;
	comp = 1;
	while (comp <= 2) {
		y0 = 0;
		while (y0 <= 7) {
			x0 = 0;
			while (x0 <= 7) {
				local_DEBUG = DEBUG;
				if (!local_DEBUG) {
					tmp_PictBuffer1 = PictBuffer[comp][blkAddrY + y0][blkAddrX + x0];
					tokens_FiltSample[(index_FiltSample % SIZE_FiltSample) + (x0 + y0 * 8 + tokenOffset)] = tmp_PictBuffer1;
				} else {
					tmp_picSize1 = picSize[0][0];
					tmp_picSize2 = picSize[0][1];
					if (blkAddrX + x0 < tmp_picSize1 / 2 && blkAddrY + y0 < tmp_picSize2 / 2) {
						tmp_PictBuffer2 = PictBuffer[comp][blkAddrY + y0][blkAddrX + x0];
						tokens_FiltSample[(index_FiltSample % SIZE_FiltSample) + (x0 + y0 * 8 + tokenOffset)] = tmp_PictBuffer2;
					} else {
						tokens_FiltSample[(index_FiltSample % SIZE_FiltSample) + (x0 + y0 * 8 + tokenOffset)] = 0;
					}
				}
				x0 = x0 + 1;
			}
			y0 = y0 + 1;
		}
		tokenOffset = tokenOffset + 8 * 8;
		comp = comp + 1;
	}
	nextMbAddr();

	// Update ports indexes
	index_FiltSample += 384;
	write_end_FiltSample();

}
static i32 isSchedulable_sendSamples_done() {
	i32 result;
	u8 local_xMbSent;
	u8 local_yMbSent;
	i32 tmp_mbFiltered;
	i32 tmp_mbFiltered0;
	i32 tmp_mbFiltered1;
	u8 tmp_picSizeInMb;

	local_xMbSent = xMbSent;
	local_yMbSent = yMbSent;
	tmp_mbFiltered = mbFiltered[0][local_xMbSent][local_yMbSent];
	local_xMbSent = xMbSent;
	local_yMbSent = yMbSent;
	tmp_mbFiltered0 = mbFiltered[1][local_xMbSent][local_yMbSent];
	local_xMbSent = xMbSent;
	local_yMbSent = yMbSent;
	tmp_mbFiltered1 = mbFiltered[2][local_xMbSent][local_yMbSent];
	local_yMbSent = yMbSent;
	tmp_picSizeInMb = picSizeInMb[1];
	result = !tmp_mbFiltered || !tmp_mbFiltered0 || !tmp_mbFiltered1 || local_yMbSent == tmp_picSizeInMb;
	return result;
}

static void sendSamples_done() {



	// Update ports indexes

}

////////////////////////////////////////////////////////////////////////////////
// Initializes

void HevcDecoder_SAO_initialize(schedinfo_t *si) {
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

void HevcDecoder_SAO_scheduler(schedinfo_t *si) {
	int i = 0;

	read_IsPicSlcLcu();
	read_LcuSizeMax();
	read_LFAcrossSlcTile();
	read_PicSize();
	read_SampleIn();
	read_SaoSe();
	read_TilesCoord();
	write_FiltSample();

	// jump to FSM state
	switch (_FSM_state) {
	case my_state_CheckSliceEn:
		goto l_CheckSliceEn;
	case my_state_GetCuPixChrFilt:
		goto l_GetCuPixChrFilt;
	case my_state_GetCuPixChrSkipFilt:
		goto l_GetCuPixChrSkipFilt;
	case my_state_GetCuPixFilt:
		goto l_GetCuPixFilt;
	case my_state_GetCuPixLumaFilt:
		goto l_GetCuPixLumaFilt;
	case my_state_GetCuPixLumaSkipFilt:
		goto l_GetCuPixLumaSkipFilt;
	case my_state_GetCuPixSkipFilt:
		goto l_GetCuPixSkipFilt;
	case my_state_GetNumTilesFilt:
		goto l_GetNumTilesFilt;
	case my_state_GetNumTilesSkipFilt:
		goto l_GetNumTilesSkipFilt;
	case my_state_GetSaoMergeFilt:
		goto l_GetSaoMergeFilt;
	case my_state_GetSaoMergeSkipFilt:
		goto l_GetSaoMergeSkipFilt;
	case my_state_GetSaoTypeIdxFilt:
		goto l_GetSaoTypeIdxFilt;
	case my_state_GetTilesCoordFilt:
		goto l_GetTilesCoordFilt;
	case my_state_GetTilesCoordSkipFilt:
		goto l_GetTilesCoordSkipFilt;
	case my_state_IsNewPict:
		goto l_IsNewPict;
	case my_state_SendLastSamplesFilt:
		goto l_SendLastSamplesFilt;
	case my_state_SendLastSamplesSkipFilt:
		goto l_SendLastSamplesSkipFilt;
	case my_state_SendSamplesFilt:
		goto l_SendSamplesFilt;
	case my_state_SendSamplesSkipFilt:
		goto l_SendSamplesSkipFilt;
	default:
		printf("unknown state in HevcDecoder_SAO.c : %s\n", stateNames[_FSM_state]);
		exit(1);
	}

	// FSM transitions
l_CheckSliceEn:
	if (isSchedulable_checkSliceEn_isFalse()) {
		checkSliceEn_isFalse();
		i++;
		goto l_GetNumTilesSkipFilt;
	} else if (isSchedulable_checkSliceEn_isTrue()) {
		checkSliceEn_isTrue();
		i++;
		goto l_GetNumTilesFilt;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_CheckSliceEn;
		goto finished;
	}
l_GetCuPixChrFilt:
	if (numTokens_SampleIn - index_SampleIn >= 8 && isSchedulable_getCuPix_launch_chroma()) {
		{
			int isAligned = 1;
			isAligned &= ((index_SampleIn % SIZE_SampleIn) < ((index_SampleIn + 8) % SIZE_SampleIn));
			if (isAligned) {
				getCuPix_launch_chroma_aligned();
			} else {
				getCuPix_launch_chroma();
			}
		}
		i++;
		goto l_GetCuPixChrFilt;
	} else if (isSchedulable_getCuPix_launch_chromaDone()) {
		getCuPix_launch_chromaDone();
		i++;
		goto l_GetSaoMergeFilt;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetCuPixChrFilt;
		goto finished;
	}
l_GetCuPixChrSkipFilt:
	if (numTokens_SampleIn - index_SampleIn >= 8 && isSchedulable_getCuPix_launch_chroma()) {
		{
			int isAligned = 1;
			isAligned &= ((index_SampleIn % SIZE_SampleIn) < ((index_SampleIn + 8) % SIZE_SampleIn));
			if (isAligned) {
				getCuPix_launch_chroma_aligned();
			} else {
				getCuPix_launch_chroma();
			}
		}
		i++;
		goto l_GetCuPixChrSkipFilt;
	} else if (isSchedulable_getCuPix_launch_chromaDone()) {
		getCuPix_launch_chromaDone();
		i++;
		goto l_GetSaoMergeSkipFilt;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetCuPixChrSkipFilt;
		goto finished;
	}
l_GetCuPixFilt:
	if (numTokens_IsPicSlcLcu - index_IsPicSlcLcu >= 1 && numTokens_LcuSizeMax - index_LcuSizeMax >= 1 && numTokens_LFAcrossSlcTile - index_LFAcrossSlcTile >= 1 && numTokens_PicSize - index_PicSize >= 2 && isSchedulable_isNewSlice()) {
		{
			int isAligned = 1;
			isAligned &= ((index_PicSize % SIZE_PicSize) < ((index_PicSize + 2) % SIZE_PicSize));
			if (isAligned) {
				isNewSlice_aligned();
			} else {
				isNewSlice();
			}
		}
		i++;
		goto l_GetNumTilesFilt;
	} else if (isSchedulable_getCuPix_done()) {
		getCuPix_done();
		i++;
		goto l_SendLastSamplesFilt;
	} else if (numTokens_IsPicSlcLcu - index_IsPicSlcLcu >= 1 && isSchedulable_getCuPix_launch_init()) {
		getCuPix_launch_init();
		i++;
		goto l_GetCuPixLumaFilt;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetCuPixFilt;
		goto finished;
	}
l_GetCuPixLumaFilt:
	if (numTokens_SampleIn - index_SampleIn >= 16 && isSchedulable_getCuPix_launch_luma()) {
		{
			int isAligned = 1;
			isAligned &= ((index_SampleIn % SIZE_SampleIn) < ((index_SampleIn + 16) % SIZE_SampleIn));
			if (isAligned) {
				getCuPix_launch_luma_aligned();
			} else {
				getCuPix_launch_luma();
			}
		}
		i++;
		goto l_GetCuPixLumaFilt;
	} else if (isSchedulable_getCuPix_launch_lumaDone()) {
		getCuPix_launch_lumaDone();
		i++;
		goto l_GetCuPixChrFilt;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetCuPixLumaFilt;
		goto finished;
	}
l_GetCuPixLumaSkipFilt:
	if (numTokens_SampleIn - index_SampleIn >= 16 && isSchedulable_getCuPix_launch_luma()) {
		{
			int isAligned = 1;
			isAligned &= ((index_SampleIn % SIZE_SampleIn) < ((index_SampleIn + 16) % SIZE_SampleIn));
			if (isAligned) {
				getCuPix_launch_luma_aligned();
			} else {
				getCuPix_launch_luma();
			}
		}
		i++;
		goto l_GetCuPixLumaSkipFilt;
	} else if (isSchedulable_getCuPix_launch_lumaDone()) {
		getCuPix_launch_lumaDone();
		i++;
		goto l_GetCuPixChrSkipFilt;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetCuPixLumaSkipFilt;
		goto finished;
	}
l_GetCuPixSkipFilt:
	if (numTokens_IsPicSlcLcu - index_IsPicSlcLcu >= 1 && numTokens_LcuSizeMax - index_LcuSizeMax >= 1 && numTokens_LFAcrossSlcTile - index_LFAcrossSlcTile >= 1 && numTokens_PicSize - index_PicSize >= 2 && isSchedulable_isNewSlice()) {
		{
			int isAligned = 1;
			isAligned &= ((index_PicSize % SIZE_PicSize) < ((index_PicSize + 2) % SIZE_PicSize));
			if (isAligned) {
				isNewSlice_aligned();
			} else {
				isNewSlice();
			}
		}
		i++;
		goto l_GetNumTilesSkipFilt;
	} else if (isSchedulable_getCuPix_done()) {
		getCuPix_done();
		i++;
		goto l_SendLastSamplesSkipFilt;
	} else if (numTokens_IsPicSlcLcu - index_IsPicSlcLcu >= 1 && isSchedulable_getCuPix_launch_init()) {
		getCuPix_launch_init();
		i++;
		goto l_GetCuPixLumaSkipFilt;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetCuPixSkipFilt;
		goto finished;
	}
l_GetNumTilesFilt:
	if (numTokens_TilesCoord - index_TilesCoord >= 1 && isSchedulable_getNumTiles()) {
		getNumTiles();
		i++;
		goto l_GetTilesCoordFilt;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetNumTilesFilt;
		goto finished;
	}
l_GetNumTilesSkipFilt:
	if (numTokens_TilesCoord - index_TilesCoord >= 1 && isSchedulable_getNumTiles()) {
		getNumTiles();
		i++;
		goto l_GetTilesCoordSkipFilt;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetNumTilesSkipFilt;
		goto finished;
	}
l_GetSaoMergeFilt:
	if (numTokens_SaoSe - index_SaoSe >= 1 && isSchedulable_getSaoMerge_noMerge()) {
		getSaoMerge_noMerge();
		i++;
		goto l_GetSaoTypeIdxFilt;
	} else if (numTokens_SaoSe - index_SaoSe >= 1 && isSchedulable_getSaoMerge_merge()) {
		getSaoMerge_merge();
		i++;
		goto l_SendSamplesFilt;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetSaoMergeFilt;
		goto finished;
	}
l_GetSaoMergeSkipFilt:
	if (isSchedulable_getSaoMerge_skip()) {
		getSaoMerge_skip();
		i++;
		goto l_SendSamplesSkipFilt;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetSaoMergeSkipFilt;
		goto finished;
	}
l_GetSaoTypeIdxFilt:
	if (numTokens_SaoSe - index_SaoSe >= 1 && isSchedulable_getSaoTypeIdx_is0()) {
		getSaoTypeIdx_is0();
		i++;
		goto l_GetSaoTypeIdxFilt;
	} else if (numTokens_SaoSe - index_SaoSe >= 6 && isSchedulable_getSaoTypeIdx_isNot0()) {
		{
			int isAligned = 1;
			isAligned &= ((index_SaoSe % SIZE_SaoSe) < ((index_SaoSe + 6) % SIZE_SaoSe));
			if (isAligned) {
				getSaoTypeIdx_isNot0_aligned();
			} else {
				getSaoTypeIdx_isNot0();
			}
		}
		i++;
		goto l_GetSaoTypeIdxFilt;
	} else if (isSchedulable_getSaoTypeIdx_skip()) {
		getSaoTypeIdx_skip();
		i++;
		goto l_GetSaoTypeIdxFilt;
	} else if (isSchedulable_getSaoTypeIdxDone()) {
		getSaoTypeIdxDone();
		i++;
		goto l_SendSamplesFilt;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetSaoTypeIdxFilt;
		goto finished;
	}
l_GetTilesCoordFilt:
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
		goto l_GetTilesCoordFilt;
	} else if (isSchedulable_getTilesCoord_done()) {
		getTilesCoord_done();
		i++;
		goto l_GetCuPixFilt;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetTilesCoordFilt;
		goto finished;
	}
l_GetTilesCoordSkipFilt:
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
		goto l_GetTilesCoordSkipFilt;
	} else if (isSchedulable_getTilesCoord_done()) {
		getTilesCoord_done();
		i++;
		goto l_GetCuPixSkipFilt;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetTilesCoordSkipFilt;
		goto finished;
	}
l_IsNewPict:
	if (numTokens_IsPicSlcLcu - index_IsPicSlcLcu >= 1 && numTokens_LcuSizeMax - index_LcuSizeMax >= 1 && numTokens_LFAcrossSlcTile - index_LFAcrossSlcTile >= 1 && numTokens_PicSize - index_PicSize >= 2 && numTokens_SaoSe - index_SaoSe >= 1 && isSchedulable_isNewPict()) {
		{
			int isAligned = 1;
			isAligned &= ((index_PicSize % SIZE_PicSize) < ((index_PicSize + 2) % SIZE_PicSize));
			if (isAligned) {
				isNewPict_aligned();
			} else {
				isNewPict();
			}
		}
		i++;
		goto l_CheckSliceEn;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_IsNewPict;
		goto finished;
	}
l_SendLastSamplesFilt:
	if (isSchedulable_sendSamples_done()) {
		sendSamples_done();
		i++;
		goto l_IsNewPict;
	} else if (isSchedulable_sendSamples_launch()) {
		int stop = 0;
		if (384 > SIZE_FiltSample - index_FiltSample + HevcDecoder_SAO_FiltSample->read_inds[0]) {
			stop = 1;
		}
		if (384 > SIZE_FiltSample - index_FiltSample + HevcDecoder_SAO_FiltSample->read_inds[1]) {
			stop = 1;
		}
		if (384 > SIZE_FiltSample - index_FiltSample + HevcDecoder_SAO_FiltSample->read_inds[2]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_SendLastSamplesFilt;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		{
			int isAligned = 1;
			isAligned &= ((index_FiltSample % SIZE_FiltSample) < ((index_FiltSample + 384) % SIZE_FiltSample));
			if (isAligned) {
				sendSamples_launch_aligned();
			} else {
				sendSamples_launch();
			}
		}
		i++;
		goto l_SendLastSamplesFilt;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_SendLastSamplesFilt;
		goto finished;
	}
l_SendLastSamplesSkipFilt:
	if (isSchedulable_sendSamples_done()) {
		sendSamples_done();
		i++;
		goto l_IsNewPict;
	} else if (isSchedulable_sendSamples_launch()) {
		int stop = 0;
		if (384 > SIZE_FiltSample - index_FiltSample + HevcDecoder_SAO_FiltSample->read_inds[0]) {
			stop = 1;
		}
		if (384 > SIZE_FiltSample - index_FiltSample + HevcDecoder_SAO_FiltSample->read_inds[1]) {
			stop = 1;
		}
		if (384 > SIZE_FiltSample - index_FiltSample + HevcDecoder_SAO_FiltSample->read_inds[2]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_SendLastSamplesSkipFilt;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		{
			int isAligned = 1;
			isAligned &= ((index_FiltSample % SIZE_FiltSample) < ((index_FiltSample + 384) % SIZE_FiltSample));
			if (isAligned) {
				sendSamples_launch_aligned();
			} else {
				sendSamples_launch();
			}
		}
		i++;
		goto l_SendLastSamplesSkipFilt;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_SendLastSamplesSkipFilt;
		goto finished;
	}
l_SendSamplesFilt:
	if (isSchedulable_sendSamples_done()) {
		sendSamples_done();
		i++;
		goto l_GetCuPixFilt;
	} else if (isSchedulable_sendSamples_launch()) {
		int stop = 0;
		if (384 > SIZE_FiltSample - index_FiltSample + HevcDecoder_SAO_FiltSample->read_inds[0]) {
			stop = 1;
		}
		if (384 > SIZE_FiltSample - index_FiltSample + HevcDecoder_SAO_FiltSample->read_inds[1]) {
			stop = 1;
		}
		if (384 > SIZE_FiltSample - index_FiltSample + HevcDecoder_SAO_FiltSample->read_inds[2]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_SendSamplesFilt;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		{
			int isAligned = 1;
			isAligned &= ((index_FiltSample % SIZE_FiltSample) < ((index_FiltSample + 384) % SIZE_FiltSample));
			if (isAligned) {
				sendSamples_launch_aligned();
			} else {
				sendSamples_launch();
			}
		}
		i++;
		goto l_SendSamplesFilt;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_SendSamplesFilt;
		goto finished;
	}
l_SendSamplesSkipFilt:
	if (isSchedulable_sendSamples_done()) {
		sendSamples_done();
		i++;
		goto l_GetCuPixSkipFilt;
	} else if (isSchedulable_sendSamples_launch()) {
		int stop = 0;
		if (384 > SIZE_FiltSample - index_FiltSample + HevcDecoder_SAO_FiltSample->read_inds[0]) {
			stop = 1;
		}
		if (384 > SIZE_FiltSample - index_FiltSample + HevcDecoder_SAO_FiltSample->read_inds[1]) {
			stop = 1;
		}
		if (384 > SIZE_FiltSample - index_FiltSample + HevcDecoder_SAO_FiltSample->read_inds[2]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_SendSamplesSkipFilt;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		{
			int isAligned = 1;
			isAligned &= ((index_FiltSample % SIZE_FiltSample) < ((index_FiltSample + 384) % SIZE_FiltSample));
			if (isAligned) {
				sendSamples_launch_aligned();
			} else {
				sendSamples_launch();
			}
		}
		i++;
		goto l_SendSamplesSkipFilt;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_SendSamplesSkipFilt;
		goto finished;
	}
finished:
	read_end_IsPicSlcLcu();
	read_end_LcuSizeMax();
	read_end_LFAcrossSlcTile();
	read_end_PicSize();
	read_end_SampleIn();
	read_end_SaoSe();
	read_end_TilesCoord();
	write_end_FiltSample();
}
