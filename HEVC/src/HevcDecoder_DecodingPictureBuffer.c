// Source file is "L/RVC/src/org/sc29/wg11/mpegh/part2/main/inter/DecodingPictureBuffer.cal"

#include <stdio.h>
#include <stdlib.h>
#include "config.h"

#include "types.h"
#include "fifo.h"
#include "util.h"
#include "scheduler.h"
#include "dataflow.h"
#include "cycle.h"
#include "eventLib.h"
FILE* papi_output_HevcDecoder_DecodingPictureBuffer;
papi_action_s *Papi_actions_HevcDecoder_DecodingPictureBuffer;

#define SIZE 8192

////////////////////////////////////////////////////////////////////////////////
// Instance
extern actor_t HevcDecoder_DecodingPictureBuffer;

////////////////////////////////////////////////////////////////////////////////
// Input FIFOs
extern fifo_u8_t *HevcDecoder_DecodingPictureBuffer_IsPicSlc;
extern fifo_u8_t *HevcDecoder_DecodingPictureBuffer_ReorderPics;
extern fifo_u8_t *HevcDecoder_DecodingPictureBuffer_IsBiPredOrLx;
extern fifo_u8_t *HevcDecoder_DecodingPictureBuffer_IsReadOrNewSlc;
extern fifo_i32_t *HevcDecoder_DecodingPictureBuffer_Mv;
extern fifo_u16_t *HevcDecoder_DecodingPictureBuffer_PicSize;
extern fifo_i16_t *HevcDecoder_DecodingPictureBuffer_Poc;
extern fifo_i16_t *HevcDecoder_DecodingPictureBuffer_PocRef;
extern fifo_u8_t *HevcDecoder_DecodingPictureBuffer_PredCuSize;
extern fifo_i16_t *HevcDecoder_DecodingPictureBuffer_RpsPoc;
extern fifo_u8_t *HevcDecoder_DecodingPictureBuffer_Sample;

////////////////////////////////////////////////////////////////////////////////
// Input Fifo control variables
static unsigned int index_IsPicSlc;
static unsigned int numTokens_IsPicSlc;
#define SIZE_IsPicSlc SIZE
#define tokens_IsPicSlc HevcDecoder_DecodingPictureBuffer_IsPicSlc->contents

extern connection_t connection_HevcDecoder_DecodingPictureBuffer_IsPicSlc;
#define rate_IsPicSlc connection_HevcDecoder_DecodingPictureBuffer_IsPicSlc.rate

static unsigned int index_ReorderPics;
static unsigned int numTokens_ReorderPics;
#define SIZE_ReorderPics SIZE
#define tokens_ReorderPics HevcDecoder_DecodingPictureBuffer_ReorderPics->contents

extern connection_t connection_HevcDecoder_DecodingPictureBuffer_ReorderPics;
#define rate_ReorderPics connection_HevcDecoder_DecodingPictureBuffer_ReorderPics.rate

static unsigned int index_IsBiPredOrLx;
static unsigned int numTokens_IsBiPredOrLx;
#define SIZE_IsBiPredOrLx SIZE
#define tokens_IsBiPredOrLx HevcDecoder_DecodingPictureBuffer_IsBiPredOrLx->contents

extern connection_t connection_HevcDecoder_DecodingPictureBuffer_IsBiPredOrLx;
#define rate_IsBiPredOrLx connection_HevcDecoder_DecodingPictureBuffer_IsBiPredOrLx.rate

static unsigned int index_IsReadOrNewSlc;
static unsigned int numTokens_IsReadOrNewSlc;
#define SIZE_IsReadOrNewSlc SIZE
#define tokens_IsReadOrNewSlc HevcDecoder_DecodingPictureBuffer_IsReadOrNewSlc->contents

extern connection_t connection_HevcDecoder_DecodingPictureBuffer_IsReadOrNewSlc;
#define rate_IsReadOrNewSlc connection_HevcDecoder_DecodingPictureBuffer_IsReadOrNewSlc.rate

static unsigned int index_Mv;
static unsigned int numTokens_Mv;
#define SIZE_Mv SIZE
#define tokens_Mv HevcDecoder_DecodingPictureBuffer_Mv->contents

extern connection_t connection_HevcDecoder_DecodingPictureBuffer_Mv;
#define rate_Mv connection_HevcDecoder_DecodingPictureBuffer_Mv.rate

static unsigned int index_PicSize;
static unsigned int numTokens_PicSize;
#define SIZE_PicSize SIZE
#define tokens_PicSize HevcDecoder_DecodingPictureBuffer_PicSize->contents

extern connection_t connection_HevcDecoder_DecodingPictureBuffer_PicSize;
#define rate_PicSize connection_HevcDecoder_DecodingPictureBuffer_PicSize.rate

static unsigned int index_Poc;
static unsigned int numTokens_Poc;
#define SIZE_Poc SIZE
#define tokens_Poc HevcDecoder_DecodingPictureBuffer_Poc->contents

extern connection_t connection_HevcDecoder_DecodingPictureBuffer_Poc;
#define rate_Poc connection_HevcDecoder_DecodingPictureBuffer_Poc.rate

static unsigned int index_PocRef;
static unsigned int numTokens_PocRef;
#define SIZE_PocRef SIZE
#define tokens_PocRef HevcDecoder_DecodingPictureBuffer_PocRef->contents

extern connection_t connection_HevcDecoder_DecodingPictureBuffer_PocRef;
#define rate_PocRef connection_HevcDecoder_DecodingPictureBuffer_PocRef.rate

static unsigned int index_PredCuSize;
static unsigned int numTokens_PredCuSize;
#define SIZE_PredCuSize SIZE
#define tokens_PredCuSize HevcDecoder_DecodingPictureBuffer_PredCuSize->contents

extern connection_t connection_HevcDecoder_DecodingPictureBuffer_PredCuSize;
#define rate_PredCuSize connection_HevcDecoder_DecodingPictureBuffer_PredCuSize.rate

static unsigned int index_RpsPoc;
static unsigned int numTokens_RpsPoc;
#define SIZE_RpsPoc SIZE
#define tokens_RpsPoc HevcDecoder_DecodingPictureBuffer_RpsPoc->contents

extern connection_t connection_HevcDecoder_DecodingPictureBuffer_RpsPoc;
#define rate_RpsPoc connection_HevcDecoder_DecodingPictureBuffer_RpsPoc.rate

static unsigned int index_Sample;
static unsigned int numTokens_Sample;
#define SIZE_Sample SIZE
#define tokens_Sample HevcDecoder_DecodingPictureBuffer_Sample->contents

extern connection_t connection_HevcDecoder_DecodingPictureBuffer_Sample;
#define rate_Sample connection_HevcDecoder_DecodingPictureBuffer_Sample.rate

////////////////////////////////////////////////////////////////////////////////
// Predecessors
extern actor_t HevcDecoder_Algo_Parser;
extern actor_t HevcDecoder_Algo_Parser;
extern actor_t HevcDecoder_generateInfo_MvComponentPred;
extern actor_t HevcDecoder_generateInfo_MvComponentPred;
extern actor_t HevcDecoder_generateInfo_MvComponentPred;
extern actor_t HevcDecoder_Algo_Parser;
extern actor_t HevcDecoder_Algo_Parser;
extern actor_t HevcDecoder_generateInfo_MvComponentPred;
extern actor_t HevcDecoder_generateInfo_MvComponentPred;
extern actor_t HevcDecoder_Algo_Parser;
extern actor_t HevcDecoder_SAO;

////////////////////////////////////////////////////////////////////////////////
// Output FIFOs
extern fifo_u8_t *HevcDecoder_DecodingPictureBuffer_RefSample;

////////////////////////////////////////////////////////////////////////////////
// Output Fifo control variables
static unsigned int index_RefSample;
static unsigned int numFree_RefSample;
#define NUM_READERS_RefSample 1
#define SIZE_RefSample SIZE
#define tokens_RefSample HevcDecoder_DecodingPictureBuffer_RefSample->contents

////////////////////////////////////////////////////////////////////////////////
// Successors
extern actor_t HevcDecoder_InterPrediction;


////////////////////////////////////////////////////////////////////////////////
// State variables of the actor
#define HevcDecoder_DecodingPictureBuffer_BORDER_SIZE_LUM 128
#define HevcDecoder_DecodingPictureBuffer_BORDER_SIZE_CHR 64
#define HevcDecoder_DecodingPictureBuffer_DPB_SIZE 17
#define HevcDecoder_DecodingPictureBuffer_BI_PRED 2
static u8 pictureBuffer[17][3][2304][4352];
static i16 pocRef[17];
static i32 isRef[17];
static i32 isStillRef[17];
static i16 currIdx = -1;
static i8 lastIdx = -1;
static u8 picSizeInCu[2];
static u16 picSize[2];
static u16 picSizeChr[2];
static u8 xIdx;
static u8 yIdx;
static u8 numPocRef;
static u8 nbList;
static u8 sizeOfList;
static i32 mvOffset[2];
static i32 mvOffChr[2];
static u8 iLoop;
static u8 jLoop;
static u8 compIdx;
static u8 puSize[2];
static u8 puSizeChr[2];
static i16 refPicIdx;
static i32 isBiPred;
static i16 lastPocRef;
static i32 lastMvRef[2];
static i32 isNewPicture;

////////////////////////////////////////////////////////////////////////////////
// Initial FSM state of the actor
enum states {
	my_state_CheckChromaWidth,
	my_state_CheckIsNewPict,
	my_state_CheckLumaWidth,
	my_state_GetCuPix,
	my_state_GetFirstRps,
	my_state_GetMvInfo,
	my_state_GetRps,
	my_state_GetRpsFirstPoc,
	my_state_GetRpsPoc,
	my_state_IsFirstNewPic,
	my_state_IsNewSlice,
	my_state_SendCuChroma,
	my_state_SendCuChroma11,
	my_state_SendCuChroma19,
	my_state_SendCuChroma35,
	my_state_SendCuChroma5,
	my_state_SendCuChroma7,
	my_state_SendCuLuma,
	my_state_SendCuLuma11,
	my_state_SendCuLuma15,
	my_state_SendCuLuma23,
	my_state_SendCuLuma39,
	my_state_SendCuLuma71
};

static char *stateNames[] = {
	"CheckChromaWidth",
	"CheckIsNewPict",
	"CheckLumaWidth",
	"GetCuPix",
	"GetFirstRps",
	"GetMvInfo",
	"GetRps",
	"GetRpsFirstPoc",
	"GetRpsPoc",
	"IsFirstNewPic",
	"IsNewSlice",
	"SendCuChroma",
	"SendCuChroma11",
	"SendCuChroma19",
	"SendCuChroma35",
	"SendCuChroma5",
	"SendCuChroma7",
	"SendCuLuma",
	"SendCuLuma11",
	"SendCuLuma15",
	"SendCuLuma23",
	"SendCuLuma39",
	"SendCuLuma71"
};

static enum states _FSM_state;



////////////////////////////////////////////////////////////////////////////////
// Token functions
static void read_IsPicSlc() {
	index_IsPicSlc = HevcDecoder_DecodingPictureBuffer_IsPicSlc->read_inds[0];
	numTokens_IsPicSlc = index_IsPicSlc + fifo_u8_get_num_tokens(HevcDecoder_DecodingPictureBuffer_IsPicSlc, 0);
}

static void read_end_IsPicSlc() {
	HevcDecoder_DecodingPictureBuffer_IsPicSlc->read_inds[0] = index_IsPicSlc;
}
static void read_ReorderPics() {
	index_ReorderPics = HevcDecoder_DecodingPictureBuffer_ReorderPics->read_inds[0];
	numTokens_ReorderPics = index_ReorderPics + fifo_u8_get_num_tokens(HevcDecoder_DecodingPictureBuffer_ReorderPics, 0);
}

static void read_end_ReorderPics() {
	HevcDecoder_DecodingPictureBuffer_ReorderPics->read_inds[0] = index_ReorderPics;
}
static void read_IsBiPredOrLx() {
	index_IsBiPredOrLx = HevcDecoder_DecodingPictureBuffer_IsBiPredOrLx->read_inds[1];
	numTokens_IsBiPredOrLx = index_IsBiPredOrLx + fifo_u8_get_num_tokens(HevcDecoder_DecodingPictureBuffer_IsBiPredOrLx, 1);
}

static void read_end_IsBiPredOrLx() {
	HevcDecoder_DecodingPictureBuffer_IsBiPredOrLx->read_inds[1] = index_IsBiPredOrLx;
}
static void read_IsReadOrNewSlc() {
	index_IsReadOrNewSlc = HevcDecoder_DecodingPictureBuffer_IsReadOrNewSlc->read_inds[0];
	numTokens_IsReadOrNewSlc = index_IsReadOrNewSlc + fifo_u8_get_num_tokens(HevcDecoder_DecodingPictureBuffer_IsReadOrNewSlc, 0);
}

static void read_end_IsReadOrNewSlc() {
	HevcDecoder_DecodingPictureBuffer_IsReadOrNewSlc->read_inds[0] = index_IsReadOrNewSlc;
}
static void read_Mv() {
	index_Mv = HevcDecoder_DecodingPictureBuffer_Mv->read_inds[1];
	numTokens_Mv = index_Mv + fifo_i32_get_num_tokens(HevcDecoder_DecodingPictureBuffer_Mv, 1);
}

static void read_end_Mv() {
	HevcDecoder_DecodingPictureBuffer_Mv->read_inds[1] = index_Mv;
}
static void read_PicSize() {
	index_PicSize = HevcDecoder_DecodingPictureBuffer_PicSize->read_inds[1];
	numTokens_PicSize = index_PicSize + fifo_u16_get_num_tokens(HevcDecoder_DecodingPictureBuffer_PicSize, 1);
}

static void read_end_PicSize() {
	HevcDecoder_DecodingPictureBuffer_PicSize->read_inds[1] = index_PicSize;
}
static void read_Poc() {
	index_Poc = HevcDecoder_DecodingPictureBuffer_Poc->read_inds[0];
	numTokens_Poc = index_Poc + fifo_i16_get_num_tokens(HevcDecoder_DecodingPictureBuffer_Poc, 0);
}

static void read_end_Poc() {
	HevcDecoder_DecodingPictureBuffer_Poc->read_inds[0] = index_Poc;
}
static void read_PocRef() {
	index_PocRef = HevcDecoder_DecodingPictureBuffer_PocRef->read_inds[0];
	numTokens_PocRef = index_PocRef + fifo_i16_get_num_tokens(HevcDecoder_DecodingPictureBuffer_PocRef, 0);
}

static void read_end_PocRef() {
	HevcDecoder_DecodingPictureBuffer_PocRef->read_inds[0] = index_PocRef;
}
static void read_PredCuSize() {
	index_PredCuSize = HevcDecoder_DecodingPictureBuffer_PredCuSize->read_inds[0];
	numTokens_PredCuSize = index_PredCuSize + fifo_u8_get_num_tokens(HevcDecoder_DecodingPictureBuffer_PredCuSize, 0);
}

static void read_end_PredCuSize() {
	HevcDecoder_DecodingPictureBuffer_PredCuSize->read_inds[0] = index_PredCuSize;
}
static void read_RpsPoc() {
	index_RpsPoc = HevcDecoder_DecodingPictureBuffer_RpsPoc->read_inds[0];
	numTokens_RpsPoc = index_RpsPoc + fifo_i16_get_num_tokens(HevcDecoder_DecodingPictureBuffer_RpsPoc, 0);
}

static void read_end_RpsPoc() {
	HevcDecoder_DecodingPictureBuffer_RpsPoc->read_inds[0] = index_RpsPoc;
}
static void read_Sample() {
	index_Sample = HevcDecoder_DecodingPictureBuffer_Sample->read_inds[0];
	numTokens_Sample = index_Sample + fifo_u8_get_num_tokens(HevcDecoder_DecodingPictureBuffer_Sample, 0);
}

static void read_end_Sample() {
	HevcDecoder_DecodingPictureBuffer_Sample->read_inds[0] = index_Sample;
}

static void write_RefSample() {
	index_RefSample = HevcDecoder_DecodingPictureBuffer_RefSample->write_ind;
	numFree_RefSample = index_RefSample + fifo_u8_get_room(HevcDecoder_DecodingPictureBuffer_RefSample, NUM_READERS_RefSample, SIZE_RefSample);
}

static void write_end_RefSample() {
	HevcDecoder_DecodingPictureBuffer_RefSample->write_ind = index_RefSample;
}

////////////////////////////////////////////////////////////////////////////////
// Functions/procedures
static i32 HevcDecoder_DecodingPictureBuffer_max(i32 a, i32 b);
static i32 HevcDecoder_DecodingPictureBuffer_min(i32 a, i32 b);
static void HevcDecoder_DecodingPictureBuffer_computeMvOffsetLuma(i32 mvOffset[2], i32 mv[2], u16 picSize[2], u8 sideMax);
static void HevcDecoder_DecodingPictureBuffer_computeMvOffsetChroma(i32 mvOffChr[2], i32 mv[2], u16 picSize[2], u8 sideMaxChr);
static void fillBorder();

static i32 HevcDecoder_DecodingPictureBuffer_max(i32 a, i32 b) {
	i32 tmp_if;

	if (a > b) {
		tmp_if = a;
	} else {
		tmp_if = b;
	}
	return tmp_if;
}
static i32 HevcDecoder_DecodingPictureBuffer_min(i32 a, i32 b) {
	i32 tmp_if;

	if (a < b) {
		tmp_if = a;
	} else {
		tmp_if = b;
	}
	return tmp_if;
}
static void HevcDecoder_DecodingPictureBuffer_computeMvOffsetLuma(i32 mvOffset[2], i32 mv[2], u16 picSize[2], u8 sideMax) {
	i32 tmp_mv;
	i32 tmp_mvOffset;
	u16 tmp_picSize;
	i32 tmp_min;
	i32 tmp_mvOffset0;
	i32 tmp_max;
	i32 tmp_mvOffset1;
	u16 local_BORDER_SIZE_LUM;
	i32 tmp_mv0;
	i32 tmp_mvOffset2;
	u16 tmp_picSize0;
	i32 tmp_min0;
	i32 tmp_mvOffset3;
	i32 tmp_max0;
	i32 tmp_mvOffset4;

	tmp_mv = mv[0];
	mvOffset[0] = tmp_mv >> 2;
	tmp_mvOffset = mvOffset[0];
	tmp_picSize = picSize[0];
	tmp_min = HevcDecoder_DecodingPictureBuffer_min(tmp_mvOffset, tmp_picSize + 3);
	mvOffset[0] = tmp_min;
	tmp_mvOffset0 = mvOffset[0];
	tmp_max = HevcDecoder_DecodingPictureBuffer_max(tmp_mvOffset0, -(8 + 3 - 1) - (sideMax - 1));
	mvOffset[0] = tmp_max;
	tmp_mvOffset1 = mvOffset[0];
	local_BORDER_SIZE_LUM = HevcDecoder_DecodingPictureBuffer_BORDER_SIZE_LUM;
	mvOffset[0] = tmp_mvOffset1 + local_BORDER_SIZE_LUM - 3;
	tmp_mv0 = mv[1];
	mvOffset[1] = tmp_mv0 >> 2;
	tmp_mvOffset2 = mvOffset[1];
	tmp_picSize0 = picSize[1];
	tmp_min0 = HevcDecoder_DecodingPictureBuffer_min(tmp_mvOffset2, tmp_picSize0 + 3);
	mvOffset[1] = tmp_min0;
	tmp_mvOffset3 = mvOffset[1];
	tmp_max0 = HevcDecoder_DecodingPictureBuffer_max(tmp_mvOffset3, -(8 + 3 - 1) - (sideMax - 1));
	mvOffset[1] = tmp_max0;
	tmp_mvOffset4 = mvOffset[1];
	local_BORDER_SIZE_LUM = HevcDecoder_DecodingPictureBuffer_BORDER_SIZE_LUM;
	mvOffset[1] = tmp_mvOffset4 + local_BORDER_SIZE_LUM - 3;
}
static void HevcDecoder_DecodingPictureBuffer_computeMvOffsetChroma(i32 mvOffChr[2], i32 mv[2], u16 picSize[2], u8 sideMaxChr) {
	i32 tmp_mv;
	i32 tmp_mvOffChr;
	u16 tmp_picSize;
	i32 tmp_min;
	i32 tmp_mvOffChr0;
	i32 tmp_max;
	i32 tmp_mvOffChr1;
	u16 local_BORDER_SIZE_CHR;
	i32 tmp_mv0;
	i32 tmp_mvOffChr2;
	u16 tmp_picSize0;
	i32 tmp_min0;
	i32 tmp_mvOffChr3;
	i32 tmp_max0;
	i32 tmp_mvOffChr4;

	tmp_mv = mv[0];
	mvOffChr[0] = tmp_mv >> 3;
	tmp_mvOffChr = mvOffChr[0];
	tmp_picSize = picSize[0];
	tmp_min = HevcDecoder_DecodingPictureBuffer_min(tmp_mvOffChr, tmp_picSize / 2 + 1);
	mvOffChr[0] = tmp_min;
	tmp_mvOffChr0 = mvOffChr[0];
	tmp_max = HevcDecoder_DecodingPictureBuffer_max(tmp_mvOffChr0, -(4 + 1 - 1) - (sideMaxChr - 1));
	mvOffChr[0] = tmp_max;
	tmp_mvOffChr1 = mvOffChr[0];
	local_BORDER_SIZE_CHR = HevcDecoder_DecodingPictureBuffer_BORDER_SIZE_CHR;
	mvOffChr[0] = tmp_mvOffChr1 + local_BORDER_SIZE_CHR - 1;
	tmp_mv0 = mv[1];
	mvOffChr[1] = tmp_mv0 >> 3;
	tmp_mvOffChr2 = mvOffChr[1];
	tmp_picSize0 = picSize[1];
	tmp_min0 = HevcDecoder_DecodingPictureBuffer_min(tmp_mvOffChr2, tmp_picSize0 / 2 + 1);
	mvOffChr[1] = tmp_min0;
	tmp_mvOffChr3 = mvOffChr[1];
	tmp_max0 = HevcDecoder_DecodingPictureBuffer_max(tmp_mvOffChr3, -(4 + 1 - 1) - (sideMaxChr - 1));
	mvOffChr[1] = tmp_max0;
	tmp_mvOffChr4 = mvOffChr[1];
	local_BORDER_SIZE_CHR = HevcDecoder_DecodingPictureBuffer_BORDER_SIZE_CHR;
	mvOffChr[1] = tmp_mvOffChr4 + local_BORDER_SIZE_CHR - 1;
}
static void fillBorder() {
	u16 xPixIdx;
	u16 yPixIdx;
	u16 xPixIdxChr;
	u16 yPixIdxChr;
	u16 xIdxDownRightBlk;
	u16 yIdxDownRightBlk;
	i32 leftEdge;
	i32 upEdge;
	i32 rightEdge;
	i32 downEdge;
	i32 isEdge;
	u8 local_xIdx;
	u8 local_yIdx;
	u16 local_BORDER_SIZE_LUM;
	u16 local_BORDER_SIZE_CHR;
	u16 tmp_picSize;
	u16 tmp_picSize0;
	u32 y;
	u32 x;
	i8 local_lastIdx;
	u8 tmp_pictureBuffer;
	u32 comp;
	u32 y0;
	u32 x0;
	u8 tmp_pictureBuffer0;
	u32 y1;
	u32 x1;
	u16 tmp_picSize1;
	u16 tmp_picSize2;
	u8 tmp_pictureBuffer1;
	u32 comp0;
	u32 y2;
	u32 x2;
	u16 tmp_picSizeChr;
	u16 tmp_picSizeChr0;
	u8 tmp_pictureBuffer2;
	u32 y3;
	u32 x3;
	u8 tmp_pictureBuffer3;
	u32 comp1;
	u32 y4;
	u32 x4;
	u8 tmp_pictureBuffer4;
	u32 y5;
	u32 x5;
	u8 tmp_pictureBuffer5;
	i32 comp2;
	u32 y6;
	u32 x6;
	u8 tmp_pictureBuffer6;
	u32 y7;
	u32 x7;
	u16 tmp_picSize3;
	u16 tmp_picSize4;
	u8 tmp_pictureBuffer7;
	i32 comp3;
	u32 y8;
	u32 x8;
	u16 tmp_picSizeChr1;
	u16 tmp_picSizeChr2;
	u8 tmp_pictureBuffer8;
	u32 y9;
	u32 x9;
	u16 tmp_picSize5;
	u16 tmp_picSize6;
	u8 tmp_pictureBuffer9;
	i32 comp4;
	u32 y10;
	u32 x10;
	u16 tmp_picSizeChr3;
	u16 tmp_picSizeChr4;
	u8 tmp_pictureBuffer10;
	u32 y11;
	u32 x11;
	u16 tmp_picSize7;
	u16 tmp_picSize8;
	u8 tmp_pictureBuffer11;
	i32 comp5;
	u32 y12;
	u32 x12;
	u16 tmp_picSizeChr5;
	u16 tmp_picSizeChr6;
	u8 tmp_pictureBuffer12;
	u32 y13;
	u32 x13;
	u16 tmp_picSize9;
	u16 tmp_picSize10;
	u16 tmp_picSize11;
	u16 tmp_picSize12;
	u8 tmp_pictureBuffer13;
	i32 comp6;
	u32 y14;
	u32 x14;
	u16 tmp_picSizeChr7;
	u16 tmp_picSizeChr8;
	u16 tmp_picSizeChr9;
	u16 tmp_picSizeChr10;
	u8 tmp_pictureBuffer14;

	local_xIdx = xIdx;
	xIdxDownRightBlk = local_xIdx * 16 + 16;
	local_yIdx = yIdx;
	yIdxDownRightBlk = local_yIdx * 16 + 16;
	local_BORDER_SIZE_LUM = HevcDecoder_DecodingPictureBuffer_BORDER_SIZE_LUM;
	local_xIdx = xIdx;
	xPixIdx = local_BORDER_SIZE_LUM + local_xIdx * 16;
	local_BORDER_SIZE_LUM = HevcDecoder_DecodingPictureBuffer_BORDER_SIZE_LUM;
	local_yIdx = yIdx;
	yPixIdx = local_BORDER_SIZE_LUM + local_yIdx * 16;
	local_BORDER_SIZE_CHR = HevcDecoder_DecodingPictureBuffer_BORDER_SIZE_CHR;
	local_xIdx = xIdx;
	xPixIdxChr = local_BORDER_SIZE_CHR + local_xIdx * 8;
	local_BORDER_SIZE_CHR = HevcDecoder_DecodingPictureBuffer_BORDER_SIZE_CHR;
	local_yIdx = yIdx;
	yPixIdxChr = local_BORDER_SIZE_CHR + local_yIdx * 8;
	local_xIdx = xIdx;
	leftEdge = local_xIdx == 0;
	local_yIdx = yIdx;
	upEdge = local_yIdx == 0;
	tmp_picSize = picSize[0];
	rightEdge = xIdxDownRightBlk >= tmp_picSize;
	tmp_picSize0 = picSize[1];
	downEdge = yIdxDownRightBlk >= tmp_picSize0;
	isEdge = leftEdge || upEdge || downEdge || rightEdge;
	if (isEdge) {
		if (leftEdge) {
			y = yPixIdx;
			while (y <= yPixIdx + 15) {
				x = 0;
				local_BORDER_SIZE_LUM = HevcDecoder_DecodingPictureBuffer_BORDER_SIZE_LUM;
				while (x <= local_BORDER_SIZE_LUM - 1) {
					local_lastIdx = lastIdx;
					local_lastIdx = lastIdx;
					local_BORDER_SIZE_LUM = HevcDecoder_DecodingPictureBuffer_BORDER_SIZE_LUM;
					tmp_pictureBuffer = pictureBuffer[local_lastIdx][0][y][local_BORDER_SIZE_LUM];
					pictureBuffer[local_lastIdx][0][y][x] = tmp_pictureBuffer;
					x = x + 1;
				}
				y = y + 1;
			}
			comp = 1;
			while (comp <= 2) {
				y0 = yPixIdxChr;
				while (y0 <= yPixIdxChr + 7) {
					x0 = 0;
					local_BORDER_SIZE_CHR = HevcDecoder_DecodingPictureBuffer_BORDER_SIZE_CHR;
					while (x0 <= local_BORDER_SIZE_CHR - 1) {
						local_lastIdx = lastIdx;
						local_lastIdx = lastIdx;
						local_BORDER_SIZE_CHR = HevcDecoder_DecodingPictureBuffer_BORDER_SIZE_CHR;
						tmp_pictureBuffer0 = pictureBuffer[local_lastIdx][comp][y0][local_BORDER_SIZE_CHR];
						pictureBuffer[local_lastIdx][comp][y0][x0] = tmp_pictureBuffer0;
						x0 = x0 + 1;
					}
					y0 = y0 + 1;
				}
				comp = comp + 1;
			}
		} else {
			if (rightEdge) {
				y1 = yPixIdx;
				while (y1 <= yPixIdx + 15) {
					x1 = 0;
					local_BORDER_SIZE_LUM = HevcDecoder_DecodingPictureBuffer_BORDER_SIZE_LUM;
					while (x1 <= local_BORDER_SIZE_LUM - 1) {
						local_lastIdx = lastIdx;
						tmp_picSize1 = picSize[0];
						local_BORDER_SIZE_LUM = HevcDecoder_DecodingPictureBuffer_BORDER_SIZE_LUM;
						local_lastIdx = lastIdx;
						tmp_picSize2 = picSize[0];
						local_BORDER_SIZE_LUM = HevcDecoder_DecodingPictureBuffer_BORDER_SIZE_LUM;
						tmp_pictureBuffer1 = pictureBuffer[local_lastIdx][0][y1][tmp_picSize2 + local_BORDER_SIZE_LUM - 1];
						pictureBuffer[local_lastIdx][0][y1][x1 + tmp_picSize1 + local_BORDER_SIZE_LUM] = tmp_pictureBuffer1;
						x1 = x1 + 1;
					}
					y1 = y1 + 1;
				}
				comp0 = 1;
				while (comp0 <= 2) {
					y2 = yPixIdxChr;
					while (y2 <= yPixIdxChr + 7) {
						x2 = 0;
						local_BORDER_SIZE_CHR = HevcDecoder_DecodingPictureBuffer_BORDER_SIZE_CHR;
						while (x2 <= local_BORDER_SIZE_CHR - 1) {
							local_lastIdx = lastIdx;
							tmp_picSizeChr = picSizeChr[0];
							local_BORDER_SIZE_CHR = HevcDecoder_DecodingPictureBuffer_BORDER_SIZE_CHR;
							local_lastIdx = lastIdx;
							tmp_picSizeChr0 = picSizeChr[0];
							local_BORDER_SIZE_CHR = HevcDecoder_DecodingPictureBuffer_BORDER_SIZE_CHR;
							tmp_pictureBuffer2 = pictureBuffer[local_lastIdx][comp0][y2][tmp_picSizeChr0 + local_BORDER_SIZE_CHR - 1];
							pictureBuffer[local_lastIdx][comp0][y2][x2 + tmp_picSizeChr + local_BORDER_SIZE_CHR] = tmp_pictureBuffer2;
							x2 = x2 + 1;
						}
						y2 = y2 + 1;
					}
					comp0 = comp0 + 1;
				}
			}
		}
		if (upEdge) {
			y3 = 0;
			local_BORDER_SIZE_LUM = HevcDecoder_DecodingPictureBuffer_BORDER_SIZE_LUM;
			while (y3 <= local_BORDER_SIZE_LUM - 1) {
				x3 = xPixIdx;
				while (x3 <= xPixIdx + 15) {
					local_lastIdx = lastIdx;
					local_lastIdx = lastIdx;
					local_BORDER_SIZE_LUM = HevcDecoder_DecodingPictureBuffer_BORDER_SIZE_LUM;
					tmp_pictureBuffer3 = pictureBuffer[local_lastIdx][0][local_BORDER_SIZE_LUM][x3];
					pictureBuffer[local_lastIdx][0][y3][x3] = tmp_pictureBuffer3;
					x3 = x3 + 1;
				}
				y3 = y3 + 1;
			}
			comp1 = 1;
			while (comp1 <= 2) {
				y4 = 0;
				local_BORDER_SIZE_CHR = HevcDecoder_DecodingPictureBuffer_BORDER_SIZE_CHR;
				while (y4 <= local_BORDER_SIZE_CHR - 1) {
					x4 = xPixIdxChr;
					while (x4 <= xPixIdxChr + 7) {
						local_lastIdx = lastIdx;
						local_lastIdx = lastIdx;
						local_BORDER_SIZE_CHR = HevcDecoder_DecodingPictureBuffer_BORDER_SIZE_CHR;
						tmp_pictureBuffer4 = pictureBuffer[local_lastIdx][comp1][local_BORDER_SIZE_CHR][x4];
						pictureBuffer[local_lastIdx][comp1][y4][x4] = tmp_pictureBuffer4;
						x4 = x4 + 1;
					}
					y4 = y4 + 1;
				}
				comp1 = comp1 + 1;
			}
			if (leftEdge) {
				y5 = 0;
				local_BORDER_SIZE_LUM = HevcDecoder_DecodingPictureBuffer_BORDER_SIZE_LUM;
				while (y5 <= local_BORDER_SIZE_LUM - 1) {
					x5 = 0;
					local_BORDER_SIZE_LUM = HevcDecoder_DecodingPictureBuffer_BORDER_SIZE_LUM;
					while (x5 <= local_BORDER_SIZE_LUM - 1) {
						local_lastIdx = lastIdx;
						local_lastIdx = lastIdx;
						local_BORDER_SIZE_LUM = HevcDecoder_DecodingPictureBuffer_BORDER_SIZE_LUM;
						local_BORDER_SIZE_LUM = HevcDecoder_DecodingPictureBuffer_BORDER_SIZE_LUM;
						tmp_pictureBuffer5 = pictureBuffer[local_lastIdx][0][local_BORDER_SIZE_LUM][local_BORDER_SIZE_LUM];
						pictureBuffer[local_lastIdx][0][y5][x5] = tmp_pictureBuffer5;
						x5 = x5 + 1;
					}
					y5 = y5 + 1;
				}
				comp2 = 1;
				while (comp2 <= 2) {
					y6 = 0;
					local_BORDER_SIZE_CHR = HevcDecoder_DecodingPictureBuffer_BORDER_SIZE_CHR;
					while (y6 <= local_BORDER_SIZE_CHR - 1) {
						x6 = 0;
						local_BORDER_SIZE_CHR = HevcDecoder_DecodingPictureBuffer_BORDER_SIZE_CHR;
						while (x6 <= local_BORDER_SIZE_CHR - 1) {
							local_lastIdx = lastIdx;
							local_lastIdx = lastIdx;
							local_BORDER_SIZE_CHR = HevcDecoder_DecodingPictureBuffer_BORDER_SIZE_CHR;
							local_BORDER_SIZE_CHR = HevcDecoder_DecodingPictureBuffer_BORDER_SIZE_CHR;
							tmp_pictureBuffer6 = pictureBuffer[local_lastIdx][comp2][local_BORDER_SIZE_CHR][local_BORDER_SIZE_CHR];
							pictureBuffer[local_lastIdx][comp2][y6][x6] = tmp_pictureBuffer6;
							x6 = x6 + 1;
						}
						y6 = y6 + 1;
					}
					comp2 = comp2 + 1;
				}
			} else {
				if (rightEdge) {
					y7 = 0;
					local_BORDER_SIZE_LUM = HevcDecoder_DecodingPictureBuffer_BORDER_SIZE_LUM;
					while (y7 <= local_BORDER_SIZE_LUM - 1) {
						x7 = 0;
						local_BORDER_SIZE_LUM = HevcDecoder_DecodingPictureBuffer_BORDER_SIZE_LUM;
						while (x7 <= local_BORDER_SIZE_LUM - 1) {
							local_lastIdx = lastIdx;
							tmp_picSize3 = picSize[0];
							local_BORDER_SIZE_LUM = HevcDecoder_DecodingPictureBuffer_BORDER_SIZE_LUM;
							local_lastIdx = lastIdx;
							local_BORDER_SIZE_LUM = HevcDecoder_DecodingPictureBuffer_BORDER_SIZE_LUM;
							tmp_picSize4 = picSize[0];
							local_BORDER_SIZE_LUM = HevcDecoder_DecodingPictureBuffer_BORDER_SIZE_LUM;
							tmp_pictureBuffer7 = pictureBuffer[local_lastIdx][0][local_BORDER_SIZE_LUM][tmp_picSize4 + local_BORDER_SIZE_LUM - 1];
							pictureBuffer[local_lastIdx][0][y7][x7 + tmp_picSize3 + local_BORDER_SIZE_LUM] = tmp_pictureBuffer7;
							x7 = x7 + 1;
						}
						y7 = y7 + 1;
					}
					comp3 = 1;
					while (comp3 <= 2) {
						y8 = 0;
						local_BORDER_SIZE_CHR = HevcDecoder_DecodingPictureBuffer_BORDER_SIZE_CHR;
						while (y8 <= local_BORDER_SIZE_CHR - 1) {
							x8 = 0;
							local_BORDER_SIZE_CHR = HevcDecoder_DecodingPictureBuffer_BORDER_SIZE_CHR;
							while (x8 <= local_BORDER_SIZE_CHR - 1) {
								local_lastIdx = lastIdx;
								tmp_picSizeChr1 = picSizeChr[0];
								local_BORDER_SIZE_CHR = HevcDecoder_DecodingPictureBuffer_BORDER_SIZE_CHR;
								local_lastIdx = lastIdx;
								local_BORDER_SIZE_CHR = HevcDecoder_DecodingPictureBuffer_BORDER_SIZE_CHR;
								tmp_picSizeChr2 = picSizeChr[0];
								local_BORDER_SIZE_CHR = HevcDecoder_DecodingPictureBuffer_BORDER_SIZE_CHR;
								tmp_pictureBuffer8 = pictureBuffer[local_lastIdx][comp3][local_BORDER_SIZE_CHR][tmp_picSizeChr2 + local_BORDER_SIZE_CHR - 1];
								pictureBuffer[local_lastIdx][comp3][y8][x8 + tmp_picSizeChr1 + local_BORDER_SIZE_CHR] = tmp_pictureBuffer8;
								x8 = x8 + 1;
							}
							y8 = y8 + 1;
						}
						comp3 = comp3 + 1;
					}
				}
			}
		} else {
			if (downEdge) {
				y9 = 0;
				local_BORDER_SIZE_LUM = HevcDecoder_DecodingPictureBuffer_BORDER_SIZE_LUM;
				while (y9 <= local_BORDER_SIZE_LUM - 1) {
					x9 = xPixIdx;
					while (x9 <= xPixIdx + 15) {
						local_lastIdx = lastIdx;
						tmp_picSize5 = picSize[1];
						local_BORDER_SIZE_LUM = HevcDecoder_DecodingPictureBuffer_BORDER_SIZE_LUM;
						local_lastIdx = lastIdx;
						tmp_picSize6 = picSize[1];
						local_BORDER_SIZE_LUM = HevcDecoder_DecodingPictureBuffer_BORDER_SIZE_LUM;
						tmp_pictureBuffer9 = pictureBuffer[local_lastIdx][0][tmp_picSize6 + local_BORDER_SIZE_LUM - 1][x9];
						pictureBuffer[local_lastIdx][0][y9 + tmp_picSize5 + local_BORDER_SIZE_LUM][x9] = tmp_pictureBuffer9;
						x9 = x9 + 1;
					}
					y9 = y9 + 1;
				}
				comp4 = 1;
				while (comp4 <= 2) {
					y10 = 0;
					local_BORDER_SIZE_CHR = HevcDecoder_DecodingPictureBuffer_BORDER_SIZE_CHR;
					while (y10 <= local_BORDER_SIZE_CHR - 1) {
						x10 = xPixIdxChr;
						while (x10 <= xPixIdxChr + 7) {
							local_lastIdx = lastIdx;
							tmp_picSizeChr3 = picSizeChr[1];
							local_BORDER_SIZE_CHR = HevcDecoder_DecodingPictureBuffer_BORDER_SIZE_CHR;
							local_lastIdx = lastIdx;
							tmp_picSizeChr4 = picSizeChr[1];
							local_BORDER_SIZE_CHR = HevcDecoder_DecodingPictureBuffer_BORDER_SIZE_CHR;
							tmp_pictureBuffer10 = pictureBuffer[local_lastIdx][comp4][tmp_picSizeChr4 + local_BORDER_SIZE_CHR - 1][x10];
							pictureBuffer[local_lastIdx][comp4][y10 + tmp_picSizeChr3 + local_BORDER_SIZE_CHR][x10] = tmp_pictureBuffer10;
							x10 = x10 + 1;
						}
						y10 = y10 + 1;
					}
					comp4 = comp4 + 1;
				}
				if (leftEdge) {
					y11 = 0;
					local_BORDER_SIZE_LUM = HevcDecoder_DecodingPictureBuffer_BORDER_SIZE_LUM;
					while (y11 <= local_BORDER_SIZE_LUM - 1) {
						x11 = 0;
						local_BORDER_SIZE_LUM = HevcDecoder_DecodingPictureBuffer_BORDER_SIZE_LUM;
						while (x11 <= local_BORDER_SIZE_LUM - 1) {
							local_lastIdx = lastIdx;
							tmp_picSize7 = picSize[1];
							local_BORDER_SIZE_LUM = HevcDecoder_DecodingPictureBuffer_BORDER_SIZE_LUM;
							local_lastIdx = lastIdx;
							tmp_picSize8 = picSize[1];
							local_BORDER_SIZE_LUM = HevcDecoder_DecodingPictureBuffer_BORDER_SIZE_LUM;
							local_BORDER_SIZE_LUM = HevcDecoder_DecodingPictureBuffer_BORDER_SIZE_LUM;
							tmp_pictureBuffer11 = pictureBuffer[local_lastIdx][0][tmp_picSize8 + local_BORDER_SIZE_LUM - 1][local_BORDER_SIZE_LUM];
							pictureBuffer[local_lastIdx][0][y11 + tmp_picSize7 + local_BORDER_SIZE_LUM][x11] = tmp_pictureBuffer11;
							x11 = x11 + 1;
						}
						y11 = y11 + 1;
					}
					comp5 = 1;
					while (comp5 <= 2) {
						y12 = 0;
						local_BORDER_SIZE_CHR = HevcDecoder_DecodingPictureBuffer_BORDER_SIZE_CHR;
						while (y12 <= local_BORDER_SIZE_CHR - 1) {
							x12 = 0;
							local_BORDER_SIZE_CHR = HevcDecoder_DecodingPictureBuffer_BORDER_SIZE_CHR;
							while (x12 <= local_BORDER_SIZE_CHR - 1) {
								local_lastIdx = lastIdx;
								tmp_picSizeChr5 = picSizeChr[1];
								local_BORDER_SIZE_CHR = HevcDecoder_DecodingPictureBuffer_BORDER_SIZE_CHR;
								local_lastIdx = lastIdx;
								tmp_picSizeChr6 = picSizeChr[1];
								local_BORDER_SIZE_CHR = HevcDecoder_DecodingPictureBuffer_BORDER_SIZE_CHR;
								local_BORDER_SIZE_CHR = HevcDecoder_DecodingPictureBuffer_BORDER_SIZE_CHR;
								tmp_pictureBuffer12 = pictureBuffer[local_lastIdx][comp5][tmp_picSizeChr6 + local_BORDER_SIZE_CHR - 1][local_BORDER_SIZE_CHR];
								pictureBuffer[local_lastIdx][comp5][y12 + tmp_picSizeChr5 + local_BORDER_SIZE_CHR][x12] = tmp_pictureBuffer12;
								x12 = x12 + 1;
							}
							y12 = y12 + 1;
						}
						comp5 = comp5 + 1;
					}
				} else {
					if (rightEdge) {
						y13 = 0;
						local_BORDER_SIZE_LUM = HevcDecoder_DecodingPictureBuffer_BORDER_SIZE_LUM;
						while (y13 <= local_BORDER_SIZE_LUM - 1) {
							x13 = 0;
							local_BORDER_SIZE_LUM = HevcDecoder_DecodingPictureBuffer_BORDER_SIZE_LUM;
							while (x13 <= local_BORDER_SIZE_LUM - 1) {
								local_lastIdx = lastIdx;
								tmp_picSize9 = picSize[1];
								local_BORDER_SIZE_LUM = HevcDecoder_DecodingPictureBuffer_BORDER_SIZE_LUM;
								tmp_picSize10 = picSize[0];
								local_BORDER_SIZE_LUM = HevcDecoder_DecodingPictureBuffer_BORDER_SIZE_LUM;
								local_lastIdx = lastIdx;
								tmp_picSize11 = picSize[1];
								local_BORDER_SIZE_LUM = HevcDecoder_DecodingPictureBuffer_BORDER_SIZE_LUM;
								tmp_picSize12 = picSize[0];
								local_BORDER_SIZE_LUM = HevcDecoder_DecodingPictureBuffer_BORDER_SIZE_LUM;
								tmp_pictureBuffer13 = pictureBuffer[local_lastIdx][0][tmp_picSize11 + local_BORDER_SIZE_LUM - 1][tmp_picSize12 + local_BORDER_SIZE_LUM - 1];
								pictureBuffer[local_lastIdx][0][y13 + tmp_picSize9 + local_BORDER_SIZE_LUM][x13 + tmp_picSize10 + local_BORDER_SIZE_LUM] = tmp_pictureBuffer13;
								x13 = x13 + 1;
							}
							y13 = y13 + 1;
						}
						comp6 = 1;
						while (comp6 <= 2) {
							y14 = 0;
							local_BORDER_SIZE_CHR = HevcDecoder_DecodingPictureBuffer_BORDER_SIZE_CHR;
							while (y14 <= local_BORDER_SIZE_CHR - 1) {
								x14 = 0;
								local_BORDER_SIZE_CHR = HevcDecoder_DecodingPictureBuffer_BORDER_SIZE_CHR;
								while (x14 <= local_BORDER_SIZE_CHR - 1) {
									local_lastIdx = lastIdx;
									tmp_picSizeChr7 = picSizeChr[1];
									local_BORDER_SIZE_CHR = HevcDecoder_DecodingPictureBuffer_BORDER_SIZE_CHR;
									tmp_picSizeChr8 = picSizeChr[0];
									local_BORDER_SIZE_CHR = HevcDecoder_DecodingPictureBuffer_BORDER_SIZE_CHR;
									local_lastIdx = lastIdx;
									tmp_picSizeChr9 = picSizeChr[1];
									local_BORDER_SIZE_CHR = HevcDecoder_DecodingPictureBuffer_BORDER_SIZE_CHR;
									tmp_picSizeChr10 = picSizeChr[0];
									local_BORDER_SIZE_CHR = HevcDecoder_DecodingPictureBuffer_BORDER_SIZE_CHR;
									tmp_pictureBuffer14 = pictureBuffer[local_lastIdx][comp6][tmp_picSizeChr9 + local_BORDER_SIZE_CHR - 1][tmp_picSizeChr10 + local_BORDER_SIZE_CHR - 1];
									pictureBuffer[local_lastIdx][comp6][y14 + tmp_picSizeChr7 + local_BORDER_SIZE_CHR][x14 + tmp_picSizeChr8 + local_BORDER_SIZE_CHR] = tmp_pictureBuffer14;
									x14 = x14 + 1;
								}
								y14 = y14 + 1;
							}
							comp6 = comp6 + 1;
						}
					}
				}
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
// Actions
static i32 isSchedulable_getPix() {
	i32 result;
	u8 local_yIdx;
	u8 tmp_picSizeInCu;

	local_yIdx = yIdx;
	tmp_picSizeInCu = picSizeInCu[1];
	result = local_yIdx < tmp_picSizeInCu;
	return result;
}

static void getPix() {

	/* Here goes PAPI init action code */
	event_start(&(Papi_actions_HevcDecoder_DecodingPictureBuffer[0].eventSet), -1);
	u16 xPixIdx;
	u16 yPixIdx;
	u32 tokenOffset;
	u16 local_BORDER_SIZE_LUM;
	u8 local_xIdx;
	u8 local_yIdx;
	u32 y;
	u32 x;
	i8 local_lastIdx;
	u8 tmp_Sample;
	u16 local_BORDER_SIZE_CHR;
	u32 component;
	u32 y0;
	u32 x0;
	u8 tmp_Sample0;
	u8 tmp_picSizeInCu;

	local_BORDER_SIZE_LUM = HevcDecoder_DecodingPictureBuffer_BORDER_SIZE_LUM;
	local_xIdx = xIdx;
	xPixIdx = local_BORDER_SIZE_LUM + local_xIdx * 16;
	local_BORDER_SIZE_LUM = HevcDecoder_DecodingPictureBuffer_BORDER_SIZE_LUM;
	local_yIdx = yIdx;
	yPixIdx = local_BORDER_SIZE_LUM + local_yIdx * 16;
	y = 0;
	while (y <= 15) {
		x = 0;
		while (x <= 15) {
			local_lastIdx = lastIdx;
			tmp_Sample = tokens_Sample[(index_Sample + (x + y * 16)) % SIZE_Sample];
			pictureBuffer[local_lastIdx][0][yPixIdx + y][xPixIdx + x] = tmp_Sample;
			x = x + 1;
		}
		y = y + 1;
	}
	local_BORDER_SIZE_CHR = HevcDecoder_DecodingPictureBuffer_BORDER_SIZE_CHR;
	local_xIdx = xIdx;
	xPixIdx = local_BORDER_SIZE_CHR + local_xIdx * 8;
	local_BORDER_SIZE_CHR = HevcDecoder_DecodingPictureBuffer_BORDER_SIZE_CHR;
	local_yIdx = yIdx;
	yPixIdx = local_BORDER_SIZE_CHR + local_yIdx * 8;
	component = 1;
	while (component <= 2) {
		tokenOffset = 16 * 16 + 8 * 8 * (component - 1);
		y0 = 0;
		while (y0 <= 7) {
			x0 = 0;
			while (x0 <= 7) {
				local_lastIdx = lastIdx;
				tmp_Sample0 = tokens_Sample[(index_Sample + (x0 + y0 * 8 + tokenOffset)) % SIZE_Sample];
				pictureBuffer[local_lastIdx][component][yPixIdx + y0][xPixIdx + x0] = tmp_Sample0;
				x0 = x0 + 1;
			}
			y0 = y0 + 1;
		}
		component = component + 1;
	}
	fillBorder();
	local_xIdx = xIdx;
	xIdx = local_xIdx + 1;
	local_xIdx = xIdx;
	tmp_picSizeInCu = picSizeInCu[0];
	if (local_xIdx == tmp_picSizeInCu) {
		xIdx = 0;
		local_yIdx = yIdx;
		yIdx = local_yIdx + 1;
	}

	// Update ports indexes
	index_Sample += 384;
	read_end_Sample();
	event_stop(&(Papi_actions_HevcDecoder_DecodingPictureBuffer[0].eventSet), Papi_actions_HevcDecoder_DecodingPictureBuffer[0].eventCodeSetSize, Papi_actions_HevcDecoder_DecodingPictureBuffer[0].counterValues, -1);
	papi_output_HevcDecoder_DecodingPictureBuffer = fopen("papi-output/papi_output_HevcDecoder_DecodingPictureBuffer.csv","a+");
	fprintf(papi_output_HevcDecoder_DecodingPictureBuffer,
		"\"%s\";\"%s\";\"%lu\"\n",
		"HevcDecoder_DecodingPictureBuffer", Papi_actions_HevcDecoder_DecodingPictureBuffer[0].action_id,
		Papi_actions_HevcDecoder_DecodingPictureBuffer[0].counterValues[0]);
	fclose(papi_output_HevcDecoder_DecodingPictureBuffer);

	rate_Sample += 384;
}
static void getPix_aligned() {

	/* Here goes PAPI init action code */
	event_start(&(Papi_actions_HevcDecoder_DecodingPictureBuffer[0].eventSet), -1);
	u16 xPixIdx;
	u16 yPixIdx;
	u32 tokenOffset;
	u16 local_BORDER_SIZE_LUM;
	u8 local_xIdx;
	u8 local_yIdx;
	u32 y;
	u32 x;
	i8 local_lastIdx;
	u8 tmp_Sample;
	u16 local_BORDER_SIZE_CHR;
	u32 component;
	u32 y0;
	u32 x0;
	u8 tmp_Sample0;
	u8 tmp_picSizeInCu;

	local_BORDER_SIZE_LUM = HevcDecoder_DecodingPictureBuffer_BORDER_SIZE_LUM;
	local_xIdx = xIdx;
	xPixIdx = local_BORDER_SIZE_LUM + local_xIdx * 16;
	local_BORDER_SIZE_LUM = HevcDecoder_DecodingPictureBuffer_BORDER_SIZE_LUM;
	local_yIdx = yIdx;
	yPixIdx = local_BORDER_SIZE_LUM + local_yIdx * 16;
	y = 0;
	while (y <= 15) {
		x = 0;
		while (x <= 15) {
			local_lastIdx = lastIdx;
			tmp_Sample = tokens_Sample[(index_Sample % SIZE_Sample) + (x + y * 16)];
			pictureBuffer[local_lastIdx][0][yPixIdx + y][xPixIdx + x] = tmp_Sample;
			x = x + 1;
		}
		y = y + 1;
	}
	local_BORDER_SIZE_CHR = HevcDecoder_DecodingPictureBuffer_BORDER_SIZE_CHR;
	local_xIdx = xIdx;
	xPixIdx = local_BORDER_SIZE_CHR + local_xIdx * 8;
	local_BORDER_SIZE_CHR = HevcDecoder_DecodingPictureBuffer_BORDER_SIZE_CHR;
	local_yIdx = yIdx;
	yPixIdx = local_BORDER_SIZE_CHR + local_yIdx * 8;
	component = 1;
	while (component <= 2) {
		tokenOffset = 16 * 16 + 8 * 8 * (component - 1);
		y0 = 0;
		while (y0 <= 7) {
			x0 = 0;
			while (x0 <= 7) {
				local_lastIdx = lastIdx;
				tmp_Sample0 = tokens_Sample[(index_Sample % SIZE_Sample) + (x0 + y0 * 8 + tokenOffset)];
				pictureBuffer[local_lastIdx][component][yPixIdx + y0][xPixIdx + x0] = tmp_Sample0;
				x0 = x0 + 1;
			}
			y0 = y0 + 1;
		}
		component = component + 1;
	}
	fillBorder();
	local_xIdx = xIdx;
	xIdx = local_xIdx + 1;
	local_xIdx = xIdx;
	tmp_picSizeInCu = picSizeInCu[0];
	if (local_xIdx == tmp_picSizeInCu) {
		xIdx = 0;
		local_yIdx = yIdx;
		yIdx = local_yIdx + 1;
	}

	// Update ports indexes
	index_Sample += 384;
	read_end_Sample();
	event_stop(&(Papi_actions_HevcDecoder_DecodingPictureBuffer[0].eventSet), Papi_actions_HevcDecoder_DecodingPictureBuffer[0].eventCodeSetSize, Papi_actions_HevcDecoder_DecodingPictureBuffer[0].counterValues, -1);
	papi_output_HevcDecoder_DecodingPictureBuffer = fopen("papi-output/papi_output_HevcDecoder_DecodingPictureBuffer.csv","a+");
	fprintf(papi_output_HevcDecoder_DecodingPictureBuffer,
		"\"%s\";\"%s\";\"%lu\"\n",
		"HevcDecoder_DecodingPictureBuffer", Papi_actions_HevcDecoder_DecodingPictureBuffer[0].action_id,
		Papi_actions_HevcDecoder_DecodingPictureBuffer[0].counterValues[0]);
	fclose(papi_output_HevcDecoder_DecodingPictureBuffer);

	rate_Sample += 384;
}
static i32 isSchedulable_isNewSlice() {
	i32 result;
	u8 isPicSlc;
	i16 poc;
	u8 isRead;
	i16 local_currIdx;
	i32 tmp_if;
	i16 tmp_pocRef;

	isPicSlc = tokens_IsPicSlc[(index_IsPicSlc + (0)) % SIZE_IsPicSlc];
	poc = tokens_Poc[(index_Poc + (0)) % SIZE_Poc];
	isRead = tokens_IsReadOrNewSlc[(index_IsReadOrNewSlc + (0)) % SIZE_IsReadOrNewSlc];
	local_currIdx = currIdx;
	if (local_currIdx == -1) {
		tmp_if = 0;
	} else {
		local_currIdx = currIdx;
		tmp_pocRef = pocRef[local_currIdx];
		tmp_if = poc == tmp_pocRef;
	}
	result = isPicSlc == 1 && (isRead == 0 && tmp_if);
	return result;
}

static void isNewSlice() {

	/* Here goes PAPI init action code */
	event_start(&(Papi_actions_HevcDecoder_DecodingPictureBuffer[1].eventSet), -1);
	u8 isRead;
	u16 picWidthInPix;
	u16 picHeightInPix;
	i16 poc;
	u8 isPicSlc;
	i32 i;
	u8 local_DPB_SIZE;

	isRead = tokens_IsReadOrNewSlc[(index_IsReadOrNewSlc + (0)) % SIZE_IsReadOrNewSlc];
	picWidthInPix = tokens_PicSize[(index_PicSize + (0)) % SIZE_PicSize];
	picHeightInPix = tokens_PicSize[(index_PicSize + (1)) % SIZE_PicSize];
	poc = tokens_Poc[(index_Poc + (0)) % SIZE_Poc];
	isPicSlc = tokens_IsPicSlc[(index_IsPicSlc + (0)) % SIZE_IsPicSlc];
	isNewPicture = 0;
	nbList = 0;
	i = 0;
	local_DPB_SIZE = HevcDecoder_DecodingPictureBuffer_DPB_SIZE;
	while (i <= local_DPB_SIZE - 1) {
		isStillRef[i] = 0;
		i = i + 1;
	}

	// Update ports indexes
	index_IsReadOrNewSlc += 1;
	index_PicSize += 2;
	read_end_PicSize();
	index_Poc += 1;
	index_IsPicSlc += 1;
	event_stop(&(Papi_actions_HevcDecoder_DecodingPictureBuffer[1].eventSet), Papi_actions_HevcDecoder_DecodingPictureBuffer[1].eventCodeSetSize, Papi_actions_HevcDecoder_DecodingPictureBuffer[1].counterValues, -1);
	papi_output_HevcDecoder_DecodingPictureBuffer = fopen("papi-output/papi_output_HevcDecoder_DecodingPictureBuffer.csv","a+");
	fprintf(papi_output_HevcDecoder_DecodingPictureBuffer,
		"\"%s\";\"%s\";\"%lu\"\n",
		"HevcDecoder_DecodingPictureBuffer", Papi_actions_HevcDecoder_DecodingPictureBuffer[1].action_id,
		Papi_actions_HevcDecoder_DecodingPictureBuffer[1].counterValues[0]);
	fclose(papi_output_HevcDecoder_DecodingPictureBuffer);

	rate_IsReadOrNewSlc += 1;
	rate_PicSize += 2;
	rate_Poc += 1;
	rate_IsPicSlc += 1;
}
static void isNewSlice_aligned() {

	/* Here goes PAPI init action code */
	event_start(&(Papi_actions_HevcDecoder_DecodingPictureBuffer[1].eventSet), -1);
	u8 isRead;
	u16 picWidthInPix;
	u16 picHeightInPix;
	i16 poc;
	u8 isPicSlc;
	i32 i;
	u8 local_DPB_SIZE;

	isRead = tokens_IsReadOrNewSlc[(index_IsReadOrNewSlc + (0)) % SIZE_IsReadOrNewSlc];
	picWidthInPix = tokens_PicSize[(index_PicSize % SIZE_PicSize) + (0)];
	picHeightInPix = tokens_PicSize[(index_PicSize % SIZE_PicSize) + (1)];
	poc = tokens_Poc[(index_Poc + (0)) % SIZE_Poc];
	isPicSlc = tokens_IsPicSlc[(index_IsPicSlc + (0)) % SIZE_IsPicSlc];
	isNewPicture = 0;
	nbList = 0;
	i = 0;
	local_DPB_SIZE = HevcDecoder_DecodingPictureBuffer_DPB_SIZE;
	while (i <= local_DPB_SIZE - 1) {
		isStillRef[i] = 0;
		i = i + 1;
	}

	// Update ports indexes
	index_IsReadOrNewSlc += 1;
	index_PicSize += 2;
	read_end_PicSize();
	index_Poc += 1;
	index_IsPicSlc += 1;
	event_stop(&(Papi_actions_HevcDecoder_DecodingPictureBuffer[1].eventSet), Papi_actions_HevcDecoder_DecodingPictureBuffer[1].eventCodeSetSize, Papi_actions_HevcDecoder_DecodingPictureBuffer[1].counterValues, -1);
	papi_output_HevcDecoder_DecodingPictureBuffer = fopen("papi-output/papi_output_HevcDecoder_DecodingPictureBuffer.csv","a+");
	fprintf(papi_output_HevcDecoder_DecodingPictureBuffer,
		"\"%s\";\"%s\";\"%lu\"\n",
		"HevcDecoder_DecodingPictureBuffer", Papi_actions_HevcDecoder_DecodingPictureBuffer[1].action_id,
		Papi_actions_HevcDecoder_DecodingPictureBuffer[1].counterValues[0]);
	fclose(papi_output_HevcDecoder_DecodingPictureBuffer);

	rate_IsReadOrNewSlc += 1;
	rate_PicSize += 2;
	rate_Poc += 1;
	rate_IsPicSlc += 1;
}
static i32 isSchedulable_isNewPict() {
	i32 result;
	u8 isRead;
	u8 isPicSlc;
	i16 poc;
	i16 local_currIdx;
	i32 tmp_if;
	i16 tmp_pocRef;

	isRead = tokens_IsReadOrNewSlc[(index_IsReadOrNewSlc + (0)) % SIZE_IsReadOrNewSlc];
	isPicSlc = tokens_IsPicSlc[(index_IsPicSlc + (0)) % SIZE_IsPicSlc];
	poc = tokens_Poc[(index_Poc + (0)) % SIZE_Poc];
	local_currIdx = currIdx;
	if (local_currIdx == -1) {
		tmp_if = 0;
	} else {
		local_currIdx = currIdx;
		tmp_pocRef = pocRef[local_currIdx];
		tmp_if = poc == tmp_pocRef;
	}
	result = isPicSlc == 0 && (isRead == 0 && !tmp_if);
	return result;
}

static void isNewPict() {

	u8 isRead;
	u16 picWidthInPix;
	u16 picHeightInPix;
	i16 poc;
	u8 isPicSlc;
	u8 noOutputOfPriorPicsFlag;
	u8 spsNumReorderPics;
	u8 picOutputFlag;
	u8 videoSequenceId;
	i16 local_currIdx;
	u32 i;
	u8 local_DPB_SIZE;
	i32 tmp_isRef;
	i32 i0;

	isRead = tokens_IsReadOrNewSlc[(index_IsReadOrNewSlc + (0)) % SIZE_IsReadOrNewSlc];
	picWidthInPix = tokens_PicSize[(index_PicSize + (0)) % SIZE_PicSize];
	picHeightInPix = tokens_PicSize[(index_PicSize + (1)) % SIZE_PicSize];
	poc = tokens_Poc[(index_Poc + (0)) % SIZE_Poc];
	isPicSlc = tokens_IsPicSlc[(index_IsPicSlc + (0)) % SIZE_IsPicSlc];
	noOutputOfPriorPicsFlag = tokens_ReorderPics[(index_ReorderPics + (0)) % SIZE_ReorderPics];
	spsNumReorderPics = tokens_ReorderPics[(index_ReorderPics + (1)) % SIZE_ReorderPics];
	picOutputFlag = tokens_ReorderPics[(index_ReorderPics + (2)) % SIZE_ReorderPics];
	videoSequenceId = tokens_ReorderPics[(index_ReorderPics + (3)) % SIZE_ReorderPics];
	picSizeInCu[0] = (picWidthInPix + 15) / 16;
	picSizeInCu[1] = (picHeightInPix + 15) / 16;
	picSize[0] = picWidthInPix;
	picSize[1] = picHeightInPix;
	picSizeChr[0] = picWidthInPix / 2;
	picSizeChr[1] = picHeightInPix / 2;
	xIdx = 0;
	yIdx = 0;
	local_currIdx = currIdx;
	lastIdx = local_currIdx;
	i = 0;
	local_DPB_SIZE = HevcDecoder_DecodingPictureBuffer_DPB_SIZE;
	while (i <= local_DPB_SIZE - 1) {
		tmp_isRef = isRef[i];
		if (!tmp_isRef) {
			currIdx = i;
		}
		i = i + 1;
	}
	local_currIdx = currIdx;
	isRef[local_currIdx] = 1;
	local_currIdx = currIdx;
	pocRef[local_currIdx] = poc;
	isNewPicture = 1;
	nbList = 0;
	i0 = 0;
	local_DPB_SIZE = HevcDecoder_DecodingPictureBuffer_DPB_SIZE;
	while (i0 <= local_DPB_SIZE - 1) {
		isStillRef[i0] = 0;
		i0 = i0 + 1;
	}

	// Update ports indexes
	index_IsReadOrNewSlc += 1;
	index_PicSize += 2;
	read_end_PicSize();
	index_Poc += 1;
	index_IsPicSlc += 1;
	index_ReorderPics += 4;
	read_end_ReorderPics();

	rate_IsReadOrNewSlc += 1;
	rate_PicSize += 2;
	rate_Poc += 1;
	rate_IsPicSlc += 1;
	rate_ReorderPics += 4;
}
static void isNewPict_aligned() {

	u8 isRead;
	u16 picWidthInPix;
	u16 picHeightInPix;
	i16 poc;
	u8 isPicSlc;
	u8 noOutputOfPriorPicsFlag;
	u8 spsNumReorderPics;
	u8 picOutputFlag;
	u8 videoSequenceId;
	i16 local_currIdx;
	u32 i;
	u8 local_DPB_SIZE;
	i32 tmp_isRef;
	i32 i0;

	isRead = tokens_IsReadOrNewSlc[(index_IsReadOrNewSlc + (0)) % SIZE_IsReadOrNewSlc];
	picWidthInPix = tokens_PicSize[(index_PicSize % SIZE_PicSize) + (0)];
	picHeightInPix = tokens_PicSize[(index_PicSize % SIZE_PicSize) + (1)];
	poc = tokens_Poc[(index_Poc + (0)) % SIZE_Poc];
	isPicSlc = tokens_IsPicSlc[(index_IsPicSlc + (0)) % SIZE_IsPicSlc];
	noOutputOfPriorPicsFlag = tokens_ReorderPics[(index_ReorderPics % SIZE_ReorderPics) + (0)];
	spsNumReorderPics = tokens_ReorderPics[(index_ReorderPics % SIZE_ReorderPics) + (1)];
	picOutputFlag = tokens_ReorderPics[(index_ReorderPics % SIZE_ReorderPics) + (2)];
	videoSequenceId = tokens_ReorderPics[(index_ReorderPics % SIZE_ReorderPics) + (3)];
	picSizeInCu[0] = (picWidthInPix + 15) / 16;
	picSizeInCu[1] = (picHeightInPix + 15) / 16;
	picSize[0] = picWidthInPix;
	picSize[1] = picHeightInPix;
	picSizeChr[0] = picWidthInPix / 2;
	picSizeChr[1] = picHeightInPix / 2;
	xIdx = 0;
	yIdx = 0;
	local_currIdx = currIdx;
	lastIdx = local_currIdx;
	i = 0;
	local_DPB_SIZE = HevcDecoder_DecodingPictureBuffer_DPB_SIZE;
	while (i <= local_DPB_SIZE - 1) {
		tmp_isRef = isRef[i];
		if (!tmp_isRef) {
			currIdx = i;
		}
		i = i + 1;
	}
	local_currIdx = currIdx;
	isRef[local_currIdx] = 1;
	local_currIdx = currIdx;
	pocRef[local_currIdx] = poc;
	isNewPicture = 1;
	nbList = 0;
	i0 = 0;
	local_DPB_SIZE = HevcDecoder_DecodingPictureBuffer_DPB_SIZE;
	while (i0 <= local_DPB_SIZE - 1) {
		isStillRef[i0] = 0;
		i0 = i0 + 1;
	}

	// Update ports indexes
	index_IsReadOrNewSlc += 1;
	index_PicSize += 2;
	read_end_PicSize();
	index_Poc += 1;
	index_IsPicSlc += 1;
	index_ReorderPics += 4;
	read_end_ReorderPics();

	rate_IsReadOrNewSlc += 1;
	rate_PicSize += 2;
	rate_Poc += 1;
	rate_IsPicSlc += 1;
	rate_ReorderPics += 4;
}
static i32 isSchedulable_isNewPict_lastPict() {
	i32 result;
	u8 isRead;
	u8 isPicSlc;
	u8 noOutputOfPriorPicsFlag;
	u8 spsNumReorderPics;
	u8 picOutputFlag;
	u8 videoSequenceId;
	i16 local_currIdx;
	i8 local_lastIdx;

	isRead = tokens_IsReadOrNewSlc[(index_IsReadOrNewSlc + (0)) % SIZE_IsReadOrNewSlc];
	isPicSlc = tokens_IsPicSlc[(index_IsPicSlc + (0)) % SIZE_IsPicSlc];
	noOutputOfPriorPicsFlag = tokens_ReorderPics[(index_ReorderPics + (0)) % SIZE_ReorderPics];
	spsNumReorderPics = tokens_ReorderPics[(index_ReorderPics + (1)) % SIZE_ReorderPics];
	picOutputFlag = tokens_ReorderPics[(index_ReorderPics + (2)) % SIZE_ReorderPics];
	videoSequenceId = tokens_ReorderPics[(index_ReorderPics + (3)) % SIZE_ReorderPics];
	local_currIdx = currIdx;
	local_lastIdx = lastIdx;
	result = local_currIdx != -1 && local_lastIdx == -1 && videoSequenceId > 1 && isPicSlc == 0 && isRead == 0;
	return result;
}

static void isNewPict_lastPict() {

	u8 isRead;
	u16 picWidthInPix;
	u16 picHeightInPix;
	i16 poc;
	u8 isPicSlc;
	u8 noOutputOfPriorPicsFlag;
	u8 spsNumReorderPics;
	u8 picOutputFlag;
	u8 videoSequenceId;

	isRead = tokens_IsReadOrNewSlc[(index_IsReadOrNewSlc + (0)) % SIZE_IsReadOrNewSlc];
	picWidthInPix = tokens_PicSize[(index_PicSize + (0)) % SIZE_PicSize];
	picHeightInPix = tokens_PicSize[(index_PicSize + (1)) % SIZE_PicSize];
	poc = tokens_Poc[(index_Poc + (0)) % SIZE_Poc];
	isPicSlc = tokens_IsPicSlc[(index_IsPicSlc + (0)) % SIZE_IsPicSlc];
	noOutputOfPriorPicsFlag = tokens_ReorderPics[(index_ReorderPics + (0)) % SIZE_ReorderPics];
	spsNumReorderPics = tokens_ReorderPics[(index_ReorderPics + (1)) % SIZE_ReorderPics];
	picOutputFlag = tokens_ReorderPics[(index_ReorderPics + (2)) % SIZE_ReorderPics];
	videoSequenceId = tokens_ReorderPics[(index_ReorderPics + (3)) % SIZE_ReorderPics];
	picSizeInCu[0] = (picWidthInPix + 15) / 16;
	picSizeInCu[1] = (picHeightInPix + 15) / 16;
	picSize[0] = picWidthInPix;
	picSize[1] = picHeightInPix;
	picSizeChr[0] = picWidthInPix / 2;
	picSizeChr[1] = picHeightInPix / 2;
	lastIdx = 0;
	xIdx = 0;
	yIdx = 0;

	// Update ports indexes
	index_IsReadOrNewSlc += 1;
	index_PicSize += 2;
	read_end_PicSize();
	index_Poc += 1;
	index_IsPicSlc += 1;
	index_ReorderPics += 4;
	read_end_ReorderPics();

	rate_IsReadOrNewSlc += 1;
	rate_PicSize += 2;
	rate_Poc += 1;
	rate_IsPicSlc += 1;
	rate_ReorderPics += 4;
}
static void isNewPict_lastPict_aligned() {

	u8 isRead;
	u16 picWidthInPix;
	u16 picHeightInPix;
	i16 poc;
	u8 isPicSlc;
	u8 noOutputOfPriorPicsFlag;
	u8 spsNumReorderPics;
	u8 picOutputFlag;
	u8 videoSequenceId;

	isRead = tokens_IsReadOrNewSlc[(index_IsReadOrNewSlc + (0)) % SIZE_IsReadOrNewSlc];
	picWidthInPix = tokens_PicSize[(index_PicSize % SIZE_PicSize) + (0)];
	picHeightInPix = tokens_PicSize[(index_PicSize % SIZE_PicSize) + (1)];
	poc = tokens_Poc[(index_Poc + (0)) % SIZE_Poc];
	isPicSlc = tokens_IsPicSlc[(index_IsPicSlc + (0)) % SIZE_IsPicSlc];
	noOutputOfPriorPicsFlag = tokens_ReorderPics[(index_ReorderPics % SIZE_ReorderPics) + (0)];
	spsNumReorderPics = tokens_ReorderPics[(index_ReorderPics % SIZE_ReorderPics) + (1)];
	picOutputFlag = tokens_ReorderPics[(index_ReorderPics % SIZE_ReorderPics) + (2)];
	videoSequenceId = tokens_ReorderPics[(index_ReorderPics % SIZE_ReorderPics) + (3)];
	picSizeInCu[0] = (picWidthInPix + 15) / 16;
	picSizeInCu[1] = (picHeightInPix + 15) / 16;
	picSize[0] = picWidthInPix;
	picSize[1] = picHeightInPix;
	picSizeChr[0] = picWidthInPix / 2;
	picSizeChr[1] = picHeightInPix / 2;
	lastIdx = 0;
	xIdx = 0;
	yIdx = 0;

	// Update ports indexes
	index_IsReadOrNewSlc += 1;
	index_PicSize += 2;
	read_end_PicSize();
	index_Poc += 1;
	index_IsPicSlc += 1;
	index_ReorderPics += 4;
	read_end_ReorderPics();

	rate_IsReadOrNewSlc += 1;
	rate_PicSize += 2;
	rate_Poc += 1;
	rate_IsPicSlc += 1;
	rate_ReorderPics += 4;
}
static i32 isSchedulable_getRps_launch() {
	i32 result;
	u8 local_nbList;

	local_nbList = nbList;
	result = local_nbList < 5;
	return result;
}

static void getRps_launch() {

	i16 numPic;

	numPic = tokens_RpsPoc[(index_RpsPoc + (0)) % SIZE_RpsPoc];
	sizeOfList = numPic;

	// Update ports indexes
	index_RpsPoc += 1;

	rate_RpsPoc += 1;
}
static i32 isSchedulable_getRps_done() {
	i32 result;
	u8 local_nbList;

	local_nbList = nbList;
	result = local_nbList == 5;
	return result;
}

static void getRps_done() {

	i32 i;
	u8 local_DPB_SIZE;
	i32 tmp_isRef;
	i32 tmp_isStillRef;
	i16 local_currIdx;

	i = 0;
	local_DPB_SIZE = HevcDecoder_DecodingPictureBuffer_DPB_SIZE;
	while (i <= local_DPB_SIZE - 1) {
		tmp_isRef = isRef[i];
		tmp_isStillRef = isStillRef[i];
		isRef[i] = tmp_isRef && tmp_isStillRef;
		i = i + 1;
	}
	local_currIdx = currIdx;
	isRef[local_currIdx] = 1;

	// Update ports indexes

}
static i32 isSchedulable_getRpsPoc_launch() {
	i32 result;
	u8 local_sizeOfList;

	local_sizeOfList = sizeOfList;
	result = local_sizeOfList > 0;
	return result;
}

static void getRpsPoc_launch() {

	i16 pocVal;
	u8 local_sizeOfList;
	i32 i;
	u8 local_DPB_SIZE;
	i16 tmp_pocRef;

	pocVal = tokens_RpsPoc[(index_RpsPoc + (0)) % SIZE_RpsPoc];
	local_sizeOfList = sizeOfList;
	sizeOfList = local_sizeOfList - 1;
	i = 0;
	local_DPB_SIZE = HevcDecoder_DecodingPictureBuffer_DPB_SIZE;
	while (i <= local_DPB_SIZE - 1) {
		tmp_pocRef = pocRef[i];
		if (tmp_pocRef == pocVal) {
			isStillRef[i] = 1;
		}
		i = i + 1;
	}

	// Update ports indexes
	index_RpsPoc += 1;

	rate_RpsPoc += 1;
}
static i32 isSchedulable_getRpsPoc_done() {
	i32 result;
	u8 local_sizeOfList;

	local_sizeOfList = sizeOfList;
	result = local_sizeOfList == 0;
	return result;
}

static void getRpsPoc_done() {

	u8 local_nbList;

	local_nbList = nbList;
	nbList = local_nbList + 1;

	// Update ports indexes

}
static i32 isSchedulable_getCuPix_done() {
	i32 result;
	u8 local_yIdx;
	u8 tmp_picSizeInCu;

	local_yIdx = yIdx;
	tmp_picSizeInCu = picSizeInCu[1];
	result = local_yIdx == tmp_picSizeInCu;
	return result;
}

static void getCuPix_done() {



	// Update ports indexes

}
static i32 isSchedulable_getReadAddr() {
	i32 result;
	u8 isRead;

	isRead = tokens_IsReadOrNewSlc[(index_IsReadOrNewSlc + (0)) % SIZE_IsReadOrNewSlc];
	result = isRead == 1;
	return result;
}

static void getReadAddr() {

	u8 isRead;
	u8 isBiPredOrLx;
	u8 local_BI_PRED;

	isRead = tokens_IsReadOrNewSlc[(index_IsReadOrNewSlc + (0)) % SIZE_IsReadOrNewSlc];
	isBiPredOrLx = tokens_IsBiPredOrLx[(index_IsBiPredOrLx + (0)) % SIZE_IsBiPredOrLx];
	local_BI_PRED = HevcDecoder_DecodingPictureBuffer_BI_PRED;
	if (isBiPredOrLx == local_BI_PRED) {
		numPocRef = 2;
	} else {
		numPocRef = 1;
	}
	local_BI_PRED = HevcDecoder_DecodingPictureBuffer_BI_PRED;
	isBiPred = isBiPredOrLx == local_BI_PRED;

	// Update ports indexes
	index_IsReadOrNewSlc += 1;
	index_IsBiPredOrLx += 1;

	rate_IsReadOrNewSlc += 1;
	rate_IsBiPredOrLx += 1;
}
static i32 isSchedulable_getMvInfo_launch() {
	i32 result;
	i16 poc;
	u8 local_numPocRef;
	i32 local_isBiPred;
	i16 local_lastPocRef;
	i32 tmp_lastMvRef;
	i32 tmp_Mv;
	i32 tmp_lastMvRef0;
	i32 tmp_Mv0;

	poc = tokens_PocRef[(index_PocRef + (0)) % SIZE_PocRef];
	local_numPocRef = numPocRef;
	local_isBiPred = isBiPred;
	local_numPocRef = numPocRef;
	local_lastPocRef = lastPocRef;
	tmp_lastMvRef = lastMvRef[0];
	tmp_Mv = tokens_Mv[(index_Mv + (0)) % SIZE_Mv];
	tmp_lastMvRef0 = lastMvRef[1];
	tmp_Mv0 = tokens_Mv[(index_Mv + (1)) % SIZE_Mv];
	result = local_numPocRef != 0 && !(local_isBiPred && local_numPocRef == 1 && local_lastPocRef == poc && tmp_lastMvRef == tmp_Mv && tmp_lastMvRef0 == tmp_Mv0);
	return result;
}

static void getMvInfo_launch() {

	i16 poc;
	u8 sideMax;
	u8 sideMaxChr;
	i32 idx_Mv;
	i32 local_Mv;
	u8 tmp_PredCuSize;
	u8 tmp_PredCuSize0;
	i32 i;
	u8 tmp_PredCuSize1;
	i32 i0;
	u8 tmp_PredCuSize2;
	u32 i1;
	u8 local_DPB_SIZE;
	i16 tmp_pocRef;
	i32 tmp_isRef;
	i32 local_Mv0[2];
	i32 idx_Mv0;
	i32 local_Mv1;
	i32 local_Mv2[2];
	i32 idx_Mv1;
	i32 local_Mv3;
	u8 local_numPocRef;

	poc = tokens_PocRef[(index_PocRef + (0)) % SIZE_PocRef];
	lastPocRef = poc;
	idx_Mv = 0;
	while (idx_Mv < 2) {
		local_Mv = tokens_Mv[(index_Mv + (idx_Mv)) % SIZE_Mv];
		lastMvRef[idx_Mv] = local_Mv;
		idx_Mv = idx_Mv + 1;
	}
	tmp_PredCuSize = tokens_PredCuSize[(index_PredCuSize + (0)) % SIZE_PredCuSize];
	tmp_PredCuSize0 = tokens_PredCuSize[(index_PredCuSize + (1)) % SIZE_PredCuSize];
	sideMax = HevcDecoder_DecodingPictureBuffer_max(tmp_PredCuSize, tmp_PredCuSize0);
	i = 0;
	while (i <= 1) {
		tmp_PredCuSize1 = tokens_PredCuSize[(index_PredCuSize + (i)) % SIZE_PredCuSize];
		puSize[i] = tmp_PredCuSize1 + 7;
		i = i + 1;
	}
	i0 = 0;
	while (i0 <= 1) {
		tmp_PredCuSize2 = tokens_PredCuSize[(index_PredCuSize + (i0)) % SIZE_PredCuSize];
		puSizeChr[i0] = tmp_PredCuSize2 / 2 + 3;
		i0 = i0 + 1;
	}
	sideMaxChr = sideMax >> 1;
	refPicIdx = 0;
	i1 = 0;
	local_DPB_SIZE = HevcDecoder_DecodingPictureBuffer_DPB_SIZE;
	while (i1 <= local_DPB_SIZE - 1) {
		tmp_pocRef = pocRef[i1];
		tmp_isRef = isRef[i1];
		if (tmp_pocRef == poc && tmp_isRef) {
			refPicIdx = i1;
		}
		i1 = i1 + 1;
	}
	idx_Mv0 = 0;
	while (idx_Mv0 < 2) {
		local_Mv1 = tokens_Mv[(index_Mv + (idx_Mv0)) % SIZE_Mv];
		local_Mv0[idx_Mv0] = local_Mv1;
		idx_Mv0 = idx_Mv0 + 1;
	}
	HevcDecoder_DecodingPictureBuffer_computeMvOffsetLuma(mvOffset, local_Mv0, picSize, sideMax);
	idx_Mv1 = 0;
	while (idx_Mv1 < 2) {
		local_Mv3 = tokens_Mv[(index_Mv + (idx_Mv1)) % SIZE_Mv];
		local_Mv2[idx_Mv1] = local_Mv3;
		idx_Mv1 = idx_Mv1 + 1;
	}
	HevcDecoder_DecodingPictureBuffer_computeMvOffsetChroma(mvOffChr, local_Mv2, picSize, sideMaxChr);
	local_numPocRef = numPocRef;
	numPocRef = local_numPocRef - 1;
	iLoop = 0;
	jLoop = 0;

	// Update ports indexes
	index_PocRef += 1;
	index_PredCuSize += 2;
	read_end_PredCuSize();
	index_Mv += 2;
	read_end_Mv();

	rate_PocRef += 1;
	rate_PredCuSize += 2;
	rate_Mv += 2;
}
static void getMvInfo_launch_aligned() {

	i16 poc;
	u8 sideMax;
	u8 sideMaxChr;
	i32 idx_Mv;
	i32 local_Mv;
	u8 tmp_PredCuSize;
	u8 tmp_PredCuSize0;
	i32 i;
	u8 tmp_PredCuSize1;
	i32 i0;
	u8 tmp_PredCuSize2;
	u32 i1;
	u8 local_DPB_SIZE;
	i16 tmp_pocRef;
	i32 tmp_isRef;
	i32 local_Mv0[2];
	i32 idx_Mv0;
	i32 local_Mv1;
	i32 local_Mv2[2];
	i32 idx_Mv1;
	i32 local_Mv3;
	u8 local_numPocRef;

	poc = tokens_PocRef[(index_PocRef + (0)) % SIZE_PocRef];
	lastPocRef = poc;
	idx_Mv = 0;
	while (idx_Mv < 2) {
		local_Mv = tokens_Mv[(index_Mv % SIZE_Mv) + (idx_Mv)];
		lastMvRef[idx_Mv] = local_Mv;
		idx_Mv = idx_Mv + 1;
	}
	tmp_PredCuSize = tokens_PredCuSize[(index_PredCuSize % SIZE_PredCuSize) + (0)];
	tmp_PredCuSize0 = tokens_PredCuSize[(index_PredCuSize % SIZE_PredCuSize) + (1)];
	sideMax = HevcDecoder_DecodingPictureBuffer_max(tmp_PredCuSize, tmp_PredCuSize0);
	i = 0;
	while (i <= 1) {
		tmp_PredCuSize1 = tokens_PredCuSize[(index_PredCuSize % SIZE_PredCuSize) + (i)];
		puSize[i] = tmp_PredCuSize1 + 7;
		i = i + 1;
	}
	i0 = 0;
	while (i0 <= 1) {
		tmp_PredCuSize2 = tokens_PredCuSize[(index_PredCuSize % SIZE_PredCuSize) + (i0)];
		puSizeChr[i0] = tmp_PredCuSize2 / 2 + 3;
		i0 = i0 + 1;
	}
	sideMaxChr = sideMax >> 1;
	refPicIdx = 0;
	i1 = 0;
	local_DPB_SIZE = HevcDecoder_DecodingPictureBuffer_DPB_SIZE;
	while (i1 <= local_DPB_SIZE - 1) {
		tmp_pocRef = pocRef[i1];
		tmp_isRef = isRef[i1];
		if (tmp_pocRef == poc && tmp_isRef) {
			refPicIdx = i1;
		}
		i1 = i1 + 1;
	}
	idx_Mv0 = 0;
	HevcDecoder_DecodingPictureBuffer_computeMvOffsetLuma(mvOffset, &tokens_Mv[index_Mv % SIZE_Mv], picSize, sideMax);
	idx_Mv1 = 0;
	HevcDecoder_DecodingPictureBuffer_computeMvOffsetChroma(mvOffChr, &tokens_Mv[index_Mv % SIZE_Mv], picSize, sideMaxChr);
	local_numPocRef = numPocRef;
	numPocRef = local_numPocRef - 1;
	iLoop = 0;
	jLoop = 0;

	// Update ports indexes
	index_PocRef += 1;
	index_PredCuSize += 2;
	read_end_PredCuSize();
	index_Mv += 2;
	read_end_Mv();

	rate_PocRef += 1;
	rate_PredCuSize += 2;
	rate_Mv += 2;
}
static i32 isSchedulable_getMvInfo_skip() {
	i32 result;
	i16 poc;
	i32 mvX;
	i32 mvY;
	i32 local_isBiPred;
	u8 local_numPocRef;
	i16 local_lastPocRef;
	i32 tmp_lastMvRef;
	i32 tmp_lastMvRef0;

	poc = tokens_PocRef[(index_PocRef + (0)) % SIZE_PocRef];
	mvX = tokens_Mv[(index_Mv + (0)) % SIZE_Mv];
	mvY = tokens_Mv[(index_Mv + (1)) % SIZE_Mv];
	local_isBiPred = isBiPred;
	local_numPocRef = numPocRef;
	local_lastPocRef = lastPocRef;
	tmp_lastMvRef = lastMvRef[0];
	tmp_lastMvRef0 = lastMvRef[1];
	result = local_isBiPred && local_numPocRef == 1 && local_lastPocRef == poc && tmp_lastMvRef == mvX && tmp_lastMvRef0 == mvY;
	return result;
}

static void getMvInfo_skip() {

	i16 poc;
	i32 mvX;
	i32 mvY;

	poc = tokens_PocRef[(index_PocRef + (0)) % SIZE_PocRef];
	mvX = tokens_Mv[(index_Mv + (0)) % SIZE_Mv];
	mvY = tokens_Mv[(index_Mv + (1)) % SIZE_Mv];

	// Update ports indexes
	index_PocRef += 1;
	index_PredCuSize += 2;
	read_end_PredCuSize();
	index_Mv += 2;
	read_end_Mv();

	rate_PocRef += 1;
	rate_PredCuSize += 2;
	rate_Mv += 2;
}
static void getMvInfo_skip_aligned() {

	i16 poc;
	i32 mvX;
	i32 mvY;

	poc = tokens_PocRef[(index_PocRef + (0)) % SIZE_PocRef];
	mvX = tokens_Mv[(index_Mv % SIZE_Mv) + (0)];
	mvY = tokens_Mv[(index_Mv % SIZE_Mv) + (1)];

	// Update ports indexes
	index_PocRef += 1;
	index_PredCuSize += 2;
	read_end_PredCuSize();
	index_Mv += 2;
	read_end_Mv();

	rate_PocRef += 1;
	rate_PredCuSize += 2;
	rate_Mv += 2;
}
static i32 isSchedulable_getMvInfo_done() {
	i32 result;
	u8 local_numPocRef;

	local_numPocRef = numPocRef;
	result = local_numPocRef == 0;
	return result;
}

static void getMvInfo_done() {



	// Update ports indexes

}
static i32 isSchedulable_lumaWidth_is71() {
	i32 result;
	u8 tmp_puSize;

	tmp_puSize = puSize[0];
	result = tmp_puSize == 71;
	return result;
}

static void lumaWidth_is71() {



	// Update ports indexes

}
static i32 isSchedulable_lumaWidth_is39() {
	i32 result;
	u8 tmp_puSize;

	tmp_puSize = puSize[0];
	result = tmp_puSize == 39;
	return result;
}

static void lumaWidth_is39() {



	// Update ports indexes

}
static i32 isSchedulable_lumaWidth_is23() {
	i32 result;
	u8 tmp_puSize;

	tmp_puSize = puSize[0];
	result = tmp_puSize == 23;
	return result;
}

static void lumaWidth_is23() {



	// Update ports indexes

}
static i32 isSchedulable_lumaWidth_is15() {
	i32 result;
	u8 tmp_puSize;

	tmp_puSize = puSize[0];
	result = tmp_puSize == 15;
	return result;
}

static void lumaWidth_is15() {



	// Update ports indexes

}
static i32 isSchedulable_lumaWidth_is11() {
	i32 result;
	u8 tmp_puSize;

	tmp_puSize = puSize[0];
	result = tmp_puSize == 11;
	return result;
}

static void lumaWidth_is11() {



	// Update ports indexes

}
static i32 isSchedulable_chromaWidth_is35() {
	i32 result;
	u8 tmp_puSizeChr;

	tmp_puSizeChr = puSizeChr[0];
	result = tmp_puSizeChr == 35;
	return result;
}

static void chromaWidth_is35() {



	// Update ports indexes

}
static i32 isSchedulable_chromaWidth_is19() {
	i32 result;
	u8 tmp_puSizeChr;

	tmp_puSizeChr = puSizeChr[0];
	result = tmp_puSizeChr == 19;
	return result;
}

static void chromaWidth_is19() {



	// Update ports indexes

}
static i32 isSchedulable_chromaWidth_is11() {
	i32 result;
	u8 tmp_puSizeChr;

	tmp_puSizeChr = puSizeChr[0];
	result = tmp_puSizeChr == 11;
	return result;
}

static void chromaWidth_is11() {



	// Update ports indexes

}
static i32 isSchedulable_chromaWidth_is7() {
	i32 result;
	u8 tmp_puSizeChr;

	tmp_puSizeChr = puSizeChr[0];
	result = tmp_puSizeChr == 7;
	return result;
}

static void chromaWidth_is7() {



	// Update ports indexes

}
static i32 isSchedulable_chromaWidth_is5() {
	i32 result;
	u8 tmp_puSizeChr;

	tmp_puSizeChr = puSizeChr[0];
	result = tmp_puSizeChr == 5;
	return result;
}

static void chromaWidth_is5() {



	// Update ports indexes

}
static i32 isSchedulable_valWidth_isOther() {
	i32 result;

	result = 1;
	return result;
}

static void valWidth_isOther() {



	// Update ports indexes

}
static i32 isSchedulable_sendCu_luma_launch_is71() {
	i32 result;
	u8 local_jLoop;
	u8 tmp_puSize;

	local_jLoop = jLoop;
	tmp_puSize = puSize[1];
	result = local_jLoop < tmp_puSize;
	return result;
}

static void sendCu_luma_launch_is71() {

	i32 i;
	i16 local_refPicIdx;
	u8 local_jLoop;
	i32 tmp_mvOffset;
	i32 tmp_mvOffset0;
	u8 tmp_pictureBuffer;

	i = 0;
	while (i <= 70) {
		local_refPicIdx = refPicIdx;
		local_jLoop = jLoop;
		tmp_mvOffset = mvOffset[1];
		tmp_mvOffset0 = mvOffset[0];
		tmp_pictureBuffer = pictureBuffer[local_refPicIdx][0][local_jLoop + tmp_mvOffset][i + tmp_mvOffset0];
		tokens_RefSample[(index_RefSample + (i)) % SIZE_RefSample] = tmp_pictureBuffer;
		i = i + 1;
	}
	local_jLoop = jLoop;
	jLoop = local_jLoop + 1;

	// Update ports indexes
	index_RefSample += 71;
	write_end_RefSample();

}
static void sendCu_luma_launch_is71_aligned() {

	i32 i;
	i16 local_refPicIdx;
	u8 local_jLoop;
	i32 tmp_mvOffset;
	i32 tmp_mvOffset0;
	u8 tmp_pictureBuffer;

	i = 0;
	while (i <= 70) {
		local_refPicIdx = refPicIdx;
		local_jLoop = jLoop;
		tmp_mvOffset = mvOffset[1];
		tmp_mvOffset0 = mvOffset[0];
		tmp_pictureBuffer = pictureBuffer[local_refPicIdx][0][local_jLoop + tmp_mvOffset][i + tmp_mvOffset0];
		tokens_RefSample[(index_RefSample % SIZE_RefSample) + (i)] = tmp_pictureBuffer;
		i = i + 1;
	}
	local_jLoop = jLoop;
	jLoop = local_jLoop + 1;

	// Update ports indexes
	index_RefSample += 71;
	write_end_RefSample();

}
static i32 isSchedulable_sendCu_luma_launch_is39() {
	i32 result;
	u8 local_jLoop;
	u8 tmp_puSize;

	local_jLoop = jLoop;
	tmp_puSize = puSize[1];
	result = local_jLoop < tmp_puSize;
	return result;
}

static void sendCu_luma_launch_is39() {

	i32 i;
	i16 local_refPicIdx;
	u8 local_jLoop;
	i32 tmp_mvOffset;
	i32 tmp_mvOffset0;
	u8 tmp_pictureBuffer;

	i = 0;
	while (i <= 38) {
		local_refPicIdx = refPicIdx;
		local_jLoop = jLoop;
		tmp_mvOffset = mvOffset[1];
		tmp_mvOffset0 = mvOffset[0];
		tmp_pictureBuffer = pictureBuffer[local_refPicIdx][0][local_jLoop + tmp_mvOffset][i + tmp_mvOffset0];
		tokens_RefSample[(index_RefSample + (i)) % SIZE_RefSample] = tmp_pictureBuffer;
		i = i + 1;
	}
	local_jLoop = jLoop;
	jLoop = local_jLoop + 1;

	// Update ports indexes
	index_RefSample += 39;
	write_end_RefSample();

}
static void sendCu_luma_launch_is39_aligned() {

	i32 i;
	i16 local_refPicIdx;
	u8 local_jLoop;
	i32 tmp_mvOffset;
	i32 tmp_mvOffset0;
	u8 tmp_pictureBuffer;

	i = 0;
	while (i <= 38) {
		local_refPicIdx = refPicIdx;
		local_jLoop = jLoop;
		tmp_mvOffset = mvOffset[1];
		tmp_mvOffset0 = mvOffset[0];
		tmp_pictureBuffer = pictureBuffer[local_refPicIdx][0][local_jLoop + tmp_mvOffset][i + tmp_mvOffset0];
		tokens_RefSample[(index_RefSample % SIZE_RefSample) + (i)] = tmp_pictureBuffer;
		i = i + 1;
	}
	local_jLoop = jLoop;
	jLoop = local_jLoop + 1;

	// Update ports indexes
	index_RefSample += 39;
	write_end_RefSample();

}
static i32 isSchedulable_sendCu_luma_launch_is23() {
	i32 result;
	u8 local_jLoop;
	u8 tmp_puSize;

	local_jLoop = jLoop;
	tmp_puSize = puSize[1];
	result = local_jLoop < tmp_puSize;
	return result;
}

static void sendCu_luma_launch_is23() {

	i32 i;
	i16 local_refPicIdx;
	u8 local_jLoop;
	i32 tmp_mvOffset;
	i32 tmp_mvOffset0;
	u8 tmp_pictureBuffer;

	i = 0;
	while (i <= 22) {
		local_refPicIdx = refPicIdx;
		local_jLoop = jLoop;
		tmp_mvOffset = mvOffset[1];
		tmp_mvOffset0 = mvOffset[0];
		tmp_pictureBuffer = pictureBuffer[local_refPicIdx][0][local_jLoop + tmp_mvOffset][i + tmp_mvOffset0];
		tokens_RefSample[(index_RefSample + (i)) % SIZE_RefSample] = tmp_pictureBuffer;
		i = i + 1;
	}
	local_jLoop = jLoop;
	jLoop = local_jLoop + 1;

	// Update ports indexes
	index_RefSample += 23;
	write_end_RefSample();

}
static void sendCu_luma_launch_is23_aligned() {

	i32 i;
	i16 local_refPicIdx;
	u8 local_jLoop;
	i32 tmp_mvOffset;
	i32 tmp_mvOffset0;
	u8 tmp_pictureBuffer;

	i = 0;
	while (i <= 22) {
		local_refPicIdx = refPicIdx;
		local_jLoop = jLoop;
		tmp_mvOffset = mvOffset[1];
		tmp_mvOffset0 = mvOffset[0];
		tmp_pictureBuffer = pictureBuffer[local_refPicIdx][0][local_jLoop + tmp_mvOffset][i + tmp_mvOffset0];
		tokens_RefSample[(index_RefSample % SIZE_RefSample) + (i)] = tmp_pictureBuffer;
		i = i + 1;
	}
	local_jLoop = jLoop;
	jLoop = local_jLoop + 1;

	// Update ports indexes
	index_RefSample += 23;
	write_end_RefSample();

}
static i32 isSchedulable_sendCu_luma_launch_is15() {
	i32 result;
	u8 local_jLoop;
	u8 tmp_puSize;

	local_jLoop = jLoop;
	tmp_puSize = puSize[1];
	result = local_jLoop < tmp_puSize;
	return result;
}

static void sendCu_luma_launch_is15() {

	i32 i;
	i16 local_refPicIdx;
	u8 local_jLoop;
	i32 tmp_mvOffset;
	i32 tmp_mvOffset0;
	u8 tmp_pictureBuffer;

	i = 0;
	while (i <= 14) {
		local_refPicIdx = refPicIdx;
		local_jLoop = jLoop;
		tmp_mvOffset = mvOffset[1];
		tmp_mvOffset0 = mvOffset[0];
		tmp_pictureBuffer = pictureBuffer[local_refPicIdx][0][local_jLoop + tmp_mvOffset][i + tmp_mvOffset0];
		tokens_RefSample[(index_RefSample + (i)) % SIZE_RefSample] = tmp_pictureBuffer;
		i = i + 1;
	}
	local_jLoop = jLoop;
	jLoop = local_jLoop + 1;

	// Update ports indexes
	index_RefSample += 15;
	write_end_RefSample();

}
static void sendCu_luma_launch_is15_aligned() {

	i32 i;
	i16 local_refPicIdx;
	u8 local_jLoop;
	i32 tmp_mvOffset;
	i32 tmp_mvOffset0;
	u8 tmp_pictureBuffer;

	i = 0;
	while (i <= 14) {
		local_refPicIdx = refPicIdx;
		local_jLoop = jLoop;
		tmp_mvOffset = mvOffset[1];
		tmp_mvOffset0 = mvOffset[0];
		tmp_pictureBuffer = pictureBuffer[local_refPicIdx][0][local_jLoop + tmp_mvOffset][i + tmp_mvOffset0];
		tokens_RefSample[(index_RefSample % SIZE_RefSample) + (i)] = tmp_pictureBuffer;
		i = i + 1;
	}
	local_jLoop = jLoop;
	jLoop = local_jLoop + 1;

	// Update ports indexes
	index_RefSample += 15;
	write_end_RefSample();

}
static i32 isSchedulable_sendCu_luma_launch_is11() {
	i32 result;
	u8 local_jLoop;
	u8 tmp_puSize;

	local_jLoop = jLoop;
	tmp_puSize = puSize[1];
	result = local_jLoop < tmp_puSize;
	return result;
}

static void sendCu_luma_launch_is11() {

	i32 i;
	i16 local_refPicIdx;
	u8 local_jLoop;
	i32 tmp_mvOffset;
	i32 tmp_mvOffset0;
	u8 tmp_pictureBuffer;

	i = 0;
	while (i <= 10) {
		local_refPicIdx = refPicIdx;
		local_jLoop = jLoop;
		tmp_mvOffset = mvOffset[1];
		tmp_mvOffset0 = mvOffset[0];
		tmp_pictureBuffer = pictureBuffer[local_refPicIdx][0][local_jLoop + tmp_mvOffset][i + tmp_mvOffset0];
		tokens_RefSample[(index_RefSample + (i)) % SIZE_RefSample] = tmp_pictureBuffer;
		i = i + 1;
	}
	local_jLoop = jLoop;
	jLoop = local_jLoop + 1;

	// Update ports indexes
	index_RefSample += 11;
	write_end_RefSample();

}
static void sendCu_luma_launch_is11_aligned() {

	i32 i;
	i16 local_refPicIdx;
	u8 local_jLoop;
	i32 tmp_mvOffset;
	i32 tmp_mvOffset0;
	u8 tmp_pictureBuffer;

	i = 0;
	while (i <= 10) {
		local_refPicIdx = refPicIdx;
		local_jLoop = jLoop;
		tmp_mvOffset = mvOffset[1];
		tmp_mvOffset0 = mvOffset[0];
		tmp_pictureBuffer = pictureBuffer[local_refPicIdx][0][local_jLoop + tmp_mvOffset][i + tmp_mvOffset0];
		tokens_RefSample[(index_RefSample % SIZE_RefSample) + (i)] = tmp_pictureBuffer;
		i = i + 1;
	}
	local_jLoop = jLoop;
	jLoop = local_jLoop + 1;

	// Update ports indexes
	index_RefSample += 11;
	write_end_RefSample();

}
static i32 isSchedulable_sendCu_luma_launch_is1() {
	i32 result;
	u8 local_jLoop;
	u8 tmp_puSize;

	local_jLoop = jLoop;
	tmp_puSize = puSize[1];
	result = local_jLoop < tmp_puSize;
	return result;
}

static void sendCu_luma_launch_is1() {

	u8 sample;
	i16 local_refPicIdx;
	u8 local_jLoop;
	i32 tmp_mvOffset;
	u8 local_iLoop;
	i32 tmp_mvOffset0;
	u8 tmp_puSize;

	local_refPicIdx = refPicIdx;
	local_jLoop = jLoop;
	tmp_mvOffset = mvOffset[1];
	local_iLoop = iLoop;
	tmp_mvOffset0 = mvOffset[0];
	sample = pictureBuffer[local_refPicIdx][0][local_jLoop + tmp_mvOffset][local_iLoop + tmp_mvOffset0];
	local_iLoop = iLoop;
	iLoop = local_iLoop + 1;
	local_iLoop = iLoop;
	tmp_puSize = puSize[0];
	if (local_iLoop == tmp_puSize) {
		iLoop = 0;
		local_jLoop = jLoop;
		jLoop = local_jLoop + 1;
	}
	tokens_RefSample[(index_RefSample + (0)) % SIZE_RefSample] = sample;

	// Update ports indexes
	index_RefSample += 1;

}
static i32 isSchedulable_sendCu_luma_done() {
	i32 result;
	u8 local_jLoop;
	u8 tmp_puSize;

	local_jLoop = jLoop;
	tmp_puSize = puSize[1];
	result = local_jLoop == tmp_puSize;
	return result;
}

static void sendCu_luma_done() {


	iLoop = 0;
	jLoop = 0;
	compIdx = 1;

	// Update ports indexes

}
static i32 isSchedulable_sendCu_chroma_launch_is35() {
	i32 result;
	u8 local_compIdx;

	local_compIdx = compIdx;
	result = local_compIdx < 3;
	return result;
}

static void sendCu_chroma_launch_is35() {

	i32 i;
	i16 local_refPicIdx;
	u8 local_compIdx;
	u8 local_jLoop;
	i32 tmp_mvOffChr;
	i32 tmp_mvOffChr0;
	u8 tmp_pictureBuffer;
	u8 tmp_puSizeChr;

	i = 0;
	while (i <= 34) {
		local_refPicIdx = refPicIdx;
		local_compIdx = compIdx;
		local_jLoop = jLoop;
		tmp_mvOffChr = mvOffChr[1];
		tmp_mvOffChr0 = mvOffChr[0];
		tmp_pictureBuffer = pictureBuffer[local_refPicIdx][local_compIdx][local_jLoop + tmp_mvOffChr][i + tmp_mvOffChr0];
		tokens_RefSample[(index_RefSample + (i)) % SIZE_RefSample] = tmp_pictureBuffer;
		i = i + 1;
	}
	local_jLoop = jLoop;
	jLoop = local_jLoop + 1;
	local_jLoop = jLoop;
	tmp_puSizeChr = puSizeChr[1];
	if (local_jLoop == tmp_puSizeChr) {
		jLoop = 0;
		local_compIdx = compIdx;
		compIdx = local_compIdx + 1;
	}

	// Update ports indexes
	index_RefSample += 35;
	write_end_RefSample();

}
static void sendCu_chroma_launch_is35_aligned() {

	i32 i;
	i16 local_refPicIdx;
	u8 local_compIdx;
	u8 local_jLoop;
	i32 tmp_mvOffChr;
	i32 tmp_mvOffChr0;
	u8 tmp_pictureBuffer;
	u8 tmp_puSizeChr;

	i = 0;
	while (i <= 34) {
		local_refPicIdx = refPicIdx;
		local_compIdx = compIdx;
		local_jLoop = jLoop;
		tmp_mvOffChr = mvOffChr[1];
		tmp_mvOffChr0 = mvOffChr[0];
		tmp_pictureBuffer = pictureBuffer[local_refPicIdx][local_compIdx][local_jLoop + tmp_mvOffChr][i + tmp_mvOffChr0];
		tokens_RefSample[(index_RefSample % SIZE_RefSample) + (i)] = tmp_pictureBuffer;
		i = i + 1;
	}
	local_jLoop = jLoop;
	jLoop = local_jLoop + 1;
	local_jLoop = jLoop;
	tmp_puSizeChr = puSizeChr[1];
	if (local_jLoop == tmp_puSizeChr) {
		jLoop = 0;
		local_compIdx = compIdx;
		compIdx = local_compIdx + 1;
	}

	// Update ports indexes
	index_RefSample += 35;
	write_end_RefSample();

}
static i32 isSchedulable_sendCu_chroma_launch_is19() {
	i32 result;
	u8 local_compIdx;

	local_compIdx = compIdx;
	result = local_compIdx < 3;
	return result;
}

static void sendCu_chroma_launch_is19() {

	i32 i;
	i16 local_refPicIdx;
	u8 local_compIdx;
	u8 local_jLoop;
	i32 tmp_mvOffChr;
	i32 tmp_mvOffChr0;
	u8 tmp_pictureBuffer;
	u8 tmp_puSizeChr;

	i = 0;
	while (i <= 18) {
		local_refPicIdx = refPicIdx;
		local_compIdx = compIdx;
		local_jLoop = jLoop;
		tmp_mvOffChr = mvOffChr[1];
		tmp_mvOffChr0 = mvOffChr[0];
		tmp_pictureBuffer = pictureBuffer[local_refPicIdx][local_compIdx][local_jLoop + tmp_mvOffChr][i + tmp_mvOffChr0];
		tokens_RefSample[(index_RefSample + (i)) % SIZE_RefSample] = tmp_pictureBuffer;
		i = i + 1;
	}
	local_jLoop = jLoop;
	jLoop = local_jLoop + 1;
	local_jLoop = jLoop;
	tmp_puSizeChr = puSizeChr[1];
	if (local_jLoop == tmp_puSizeChr) {
		jLoop = 0;
		local_compIdx = compIdx;
		compIdx = local_compIdx + 1;
	}

	// Update ports indexes
	index_RefSample += 19;
	write_end_RefSample();

}
static void sendCu_chroma_launch_is19_aligned() {

	i32 i;
	i16 local_refPicIdx;
	u8 local_compIdx;
	u8 local_jLoop;
	i32 tmp_mvOffChr;
	i32 tmp_mvOffChr0;
	u8 tmp_pictureBuffer;
	u8 tmp_puSizeChr;

	i = 0;
	while (i <= 18) {
		local_refPicIdx = refPicIdx;
		local_compIdx = compIdx;
		local_jLoop = jLoop;
		tmp_mvOffChr = mvOffChr[1];
		tmp_mvOffChr0 = mvOffChr[0];
		tmp_pictureBuffer = pictureBuffer[local_refPicIdx][local_compIdx][local_jLoop + tmp_mvOffChr][i + tmp_mvOffChr0];
		tokens_RefSample[(index_RefSample % SIZE_RefSample) + (i)] = tmp_pictureBuffer;
		i = i + 1;
	}
	local_jLoop = jLoop;
	jLoop = local_jLoop + 1;
	local_jLoop = jLoop;
	tmp_puSizeChr = puSizeChr[1];
	if (local_jLoop == tmp_puSizeChr) {
		jLoop = 0;
		local_compIdx = compIdx;
		compIdx = local_compIdx + 1;
	}

	// Update ports indexes
	index_RefSample += 19;
	write_end_RefSample();

}
static i32 isSchedulable_sendCu_chroma_launch_is11() {
	i32 result;
	u8 local_compIdx;

	local_compIdx = compIdx;
	result = local_compIdx < 3;
	return result;
}

static void sendCu_chroma_launch_is11() {

	i32 i;
	i16 local_refPicIdx;
	u8 local_compIdx;
	u8 local_jLoop;
	i32 tmp_mvOffChr;
	i32 tmp_mvOffChr0;
	u8 tmp_pictureBuffer;
	u8 tmp_puSizeChr;

	i = 0;
	while (i <= 10) {
		local_refPicIdx = refPicIdx;
		local_compIdx = compIdx;
		local_jLoop = jLoop;
		tmp_mvOffChr = mvOffChr[1];
		tmp_mvOffChr0 = mvOffChr[0];
		tmp_pictureBuffer = pictureBuffer[local_refPicIdx][local_compIdx][local_jLoop + tmp_mvOffChr][i + tmp_mvOffChr0];
		tokens_RefSample[(index_RefSample + (i)) % SIZE_RefSample] = tmp_pictureBuffer;
		i = i + 1;
	}
	local_jLoop = jLoop;
	jLoop = local_jLoop + 1;
	local_jLoop = jLoop;
	tmp_puSizeChr = puSizeChr[1];
	if (local_jLoop == tmp_puSizeChr) {
		jLoop = 0;
		local_compIdx = compIdx;
		compIdx = local_compIdx + 1;
	}

	// Update ports indexes
	index_RefSample += 11;
	write_end_RefSample();

}
static void sendCu_chroma_launch_is11_aligned() {

	i32 i;
	i16 local_refPicIdx;
	u8 local_compIdx;
	u8 local_jLoop;
	i32 tmp_mvOffChr;
	i32 tmp_mvOffChr0;
	u8 tmp_pictureBuffer;
	u8 tmp_puSizeChr;

	i = 0;
	while (i <= 10) {
		local_refPicIdx = refPicIdx;
		local_compIdx = compIdx;
		local_jLoop = jLoop;
		tmp_mvOffChr = mvOffChr[1];
		tmp_mvOffChr0 = mvOffChr[0];
		tmp_pictureBuffer = pictureBuffer[local_refPicIdx][local_compIdx][local_jLoop + tmp_mvOffChr][i + tmp_mvOffChr0];
		tokens_RefSample[(index_RefSample % SIZE_RefSample) + (i)] = tmp_pictureBuffer;
		i = i + 1;
	}
	local_jLoop = jLoop;
	jLoop = local_jLoop + 1;
	local_jLoop = jLoop;
	tmp_puSizeChr = puSizeChr[1];
	if (local_jLoop == tmp_puSizeChr) {
		jLoop = 0;
		local_compIdx = compIdx;
		compIdx = local_compIdx + 1;
	}

	// Update ports indexes
	index_RefSample += 11;
	write_end_RefSample();

}
static i32 isSchedulable_sendCu_chroma_launch_is7() {
	i32 result;
	u8 local_compIdx;

	local_compIdx = compIdx;
	result = local_compIdx < 3;
	return result;
}

static void sendCu_chroma_launch_is7() {

	i32 i;
	i16 local_refPicIdx;
	u8 local_compIdx;
	u8 local_jLoop;
	i32 tmp_mvOffChr;
	i32 tmp_mvOffChr0;
	u8 tmp_pictureBuffer;
	u8 tmp_puSizeChr;

	i = 0;
	while (i <= 6) {
		local_refPicIdx = refPicIdx;
		local_compIdx = compIdx;
		local_jLoop = jLoop;
		tmp_mvOffChr = mvOffChr[1];
		tmp_mvOffChr0 = mvOffChr[0];
		tmp_pictureBuffer = pictureBuffer[local_refPicIdx][local_compIdx][local_jLoop + tmp_mvOffChr][i + tmp_mvOffChr0];
		tokens_RefSample[(index_RefSample + (i)) % SIZE_RefSample] = tmp_pictureBuffer;
		i = i + 1;
	}
	local_jLoop = jLoop;
	jLoop = local_jLoop + 1;
	local_jLoop = jLoop;
	tmp_puSizeChr = puSizeChr[1];
	if (local_jLoop == tmp_puSizeChr) {
		jLoop = 0;
		local_compIdx = compIdx;
		compIdx = local_compIdx + 1;
	}

	// Update ports indexes
	index_RefSample += 7;
	write_end_RefSample();

}
static void sendCu_chroma_launch_is7_aligned() {

	i32 i;
	i16 local_refPicIdx;
	u8 local_compIdx;
	u8 local_jLoop;
	i32 tmp_mvOffChr;
	i32 tmp_mvOffChr0;
	u8 tmp_pictureBuffer;
	u8 tmp_puSizeChr;

	i = 0;
	while (i <= 6) {
		local_refPicIdx = refPicIdx;
		local_compIdx = compIdx;
		local_jLoop = jLoop;
		tmp_mvOffChr = mvOffChr[1];
		tmp_mvOffChr0 = mvOffChr[0];
		tmp_pictureBuffer = pictureBuffer[local_refPicIdx][local_compIdx][local_jLoop + tmp_mvOffChr][i + tmp_mvOffChr0];
		tokens_RefSample[(index_RefSample % SIZE_RefSample) + (i)] = tmp_pictureBuffer;
		i = i + 1;
	}
	local_jLoop = jLoop;
	jLoop = local_jLoop + 1;
	local_jLoop = jLoop;
	tmp_puSizeChr = puSizeChr[1];
	if (local_jLoop == tmp_puSizeChr) {
		jLoop = 0;
		local_compIdx = compIdx;
		compIdx = local_compIdx + 1;
	}

	// Update ports indexes
	index_RefSample += 7;
	write_end_RefSample();

}
static i32 isSchedulable_sendCu_chroma_launch_is5() {
	i32 result;
	u8 local_compIdx;

	local_compIdx = compIdx;
	result = local_compIdx < 3;
	return result;
}

static void sendCu_chroma_launch_is5() {

	i32 i;
	i16 local_refPicIdx;
	u8 local_compIdx;
	u8 local_jLoop;
	i32 tmp_mvOffChr;
	i32 tmp_mvOffChr0;
	u8 tmp_pictureBuffer;
	u8 tmp_puSizeChr;

	i = 0;
	while (i <= 4) {
		local_refPicIdx = refPicIdx;
		local_compIdx = compIdx;
		local_jLoop = jLoop;
		tmp_mvOffChr = mvOffChr[1];
		tmp_mvOffChr0 = mvOffChr[0];
		tmp_pictureBuffer = pictureBuffer[local_refPicIdx][local_compIdx][local_jLoop + tmp_mvOffChr][i + tmp_mvOffChr0];
		tokens_RefSample[(index_RefSample + (i)) % SIZE_RefSample] = tmp_pictureBuffer;
		i = i + 1;
	}
	local_jLoop = jLoop;
	jLoop = local_jLoop + 1;
	local_jLoop = jLoop;
	tmp_puSizeChr = puSizeChr[1];
	if (local_jLoop == tmp_puSizeChr) {
		jLoop = 0;
		local_compIdx = compIdx;
		compIdx = local_compIdx + 1;
	}

	// Update ports indexes
	index_RefSample += 5;
	write_end_RefSample();

}
static void sendCu_chroma_launch_is5_aligned() {

	i32 i;
	i16 local_refPicIdx;
	u8 local_compIdx;
	u8 local_jLoop;
	i32 tmp_mvOffChr;
	i32 tmp_mvOffChr0;
	u8 tmp_pictureBuffer;
	u8 tmp_puSizeChr;

	i = 0;
	while (i <= 4) {
		local_refPicIdx = refPicIdx;
		local_compIdx = compIdx;
		local_jLoop = jLoop;
		tmp_mvOffChr = mvOffChr[1];
		tmp_mvOffChr0 = mvOffChr[0];
		tmp_pictureBuffer = pictureBuffer[local_refPicIdx][local_compIdx][local_jLoop + tmp_mvOffChr][i + tmp_mvOffChr0];
		tokens_RefSample[(index_RefSample % SIZE_RefSample) + (i)] = tmp_pictureBuffer;
		i = i + 1;
	}
	local_jLoop = jLoop;
	jLoop = local_jLoop + 1;
	local_jLoop = jLoop;
	tmp_puSizeChr = puSizeChr[1];
	if (local_jLoop == tmp_puSizeChr) {
		jLoop = 0;
		local_compIdx = compIdx;
		compIdx = local_compIdx + 1;
	}

	// Update ports indexes
	index_RefSample += 5;
	write_end_RefSample();

}
static i32 isSchedulable_sendCu_chroma_launch_is1() {
	i32 result;
	u8 local_compIdx;

	local_compIdx = compIdx;
	result = local_compIdx < 3;
	return result;
}

static void sendCu_chroma_launch_is1() {

	u8 sample;
	i16 local_refPicIdx;
	u8 local_compIdx;
	u8 local_jLoop;
	i32 tmp_mvOffChr;
	u8 local_iLoop;
	i32 tmp_mvOffChr0;
	u8 tmp_puSizeChr;
	u8 tmp_puSizeChr0;

	local_refPicIdx = refPicIdx;
	local_compIdx = compIdx;
	local_jLoop = jLoop;
	tmp_mvOffChr = mvOffChr[1];
	local_iLoop = iLoop;
	tmp_mvOffChr0 = mvOffChr[0];
	sample = pictureBuffer[local_refPicIdx][local_compIdx][local_jLoop + tmp_mvOffChr][local_iLoop + tmp_mvOffChr0];
	local_iLoop = iLoop;
	iLoop = local_iLoop + 1;
	local_iLoop = iLoop;
	tmp_puSizeChr = puSizeChr[0];
	if (local_iLoop == tmp_puSizeChr) {
		iLoop = 0;
		local_jLoop = jLoop;
		jLoop = local_jLoop + 1;
		local_jLoop = jLoop;
		tmp_puSizeChr0 = puSizeChr[1];
		if (local_jLoop == tmp_puSizeChr0) {
			jLoop = 0;
			local_compIdx = compIdx;
			compIdx = local_compIdx + 1;
		}
	}
	tokens_RefSample[(index_RefSample + (0)) % SIZE_RefSample] = sample;

	// Update ports indexes
	index_RefSample += 1;

}
static i32 isSchedulable_sendCu_chroma_done() {
	i32 result;
	u8 local_compIdx;

	local_compIdx = compIdx;
	result = local_compIdx == 3;
	return result;
}

static void sendCu_chroma_done() {



	// Update ports indexes

}
static i32 isSchedulable_checkIsNewPict_isTrue() {
	i32 result;
	i32 local_isNewPicture;

	local_isNewPicture = isNewPicture;
	result = local_isNewPicture;
	return result;
}

static void checkIsNewPict_isTrue() {



	// Update ports indexes

}
static i32 isSchedulable_checkIsNewPict_isFalse() {
	i32 result;
	i32 local_isNewPicture;

	local_isNewPicture = isNewPicture;
	result = !local_isNewPicture;
	return result;
}

static void checkIsNewPict_isFalse() {



	// Update ports indexes

}

////////////////////////////////////////////////////////////////////////////////
// Initializes

void HevcDecoder_DecodingPictureBuffer_initialize(schedinfo_t *si) {
	int i = 0;
	/* Papify initialization */
	mkdir("papi-output", 0777);
	Papi_actions_HevcDecoder_DecodingPictureBuffer = malloc(sizeof(papi_action_s) * 2);
	papi_output_HevcDecoder_DecodingPictureBuffer = fopen("papi-output/papi_output_HevcDecoder_DecodingPictureBuffer.csv","w");

	Papi_actions_HevcDecoder_DecodingPictureBuffer[0].action_id = malloc(strlen("getPix")+1);
	Papi_actions_HevcDecoder_DecodingPictureBuffer[0].action_id = "getPix";
	Papi_actions_HevcDecoder_DecodingPictureBuffer[0].eventCodeSetSize = 1;
	Papi_actions_HevcDecoder_DecodingPictureBuffer[0].eventCodeSet = malloc(sizeof(unsigned long) * Papi_actions_HevcDecoder_DecodingPictureBuffer[0].eventCodeSetSize);
	Papi_actions_HevcDecoder_DecodingPictureBuffer[0].eventCodeSet[0] = PAPI_TOT_INS;
	Papi_actions_HevcDecoder_DecodingPictureBuffer[0].eventSet = malloc(sizeof(int) * Papi_actions_HevcDecoder_DecodingPictureBuffer[0].eventCodeSetSize);
	Papi_actions_HevcDecoder_DecodingPictureBuffer[0].eventSet = PAPI_NULL;
	Papi_actions_HevcDecoder_DecodingPictureBuffer[0].counterValues = malloc(sizeof(unsigned long) * Papi_actions_HevcDecoder_DecodingPictureBuffer[0].eventCodeSetSize);
	Papi_actions_HevcDecoder_DecodingPictureBuffer[1].action_id = malloc(strlen("isNewSlice")+1);
	Papi_actions_HevcDecoder_DecodingPictureBuffer[1].action_id = "isNewSlice";
	Papi_actions_HevcDecoder_DecodingPictureBuffer[1].eventCodeSetSize = 1;
	Papi_actions_HevcDecoder_DecodingPictureBuffer[1].eventCodeSet = malloc(sizeof(unsigned long) * Papi_actions_HevcDecoder_DecodingPictureBuffer[1].eventCodeSetSize);
	Papi_actions_HevcDecoder_DecodingPictureBuffer[1].eventCodeSet[0] = PAPI_TOT_INS;
	Papi_actions_HevcDecoder_DecodingPictureBuffer[1].eventSet = malloc(sizeof(int) * Papi_actions_HevcDecoder_DecodingPictureBuffer[1].eventCodeSetSize);
	Papi_actions_HevcDecoder_DecodingPictureBuffer[1].eventSet = PAPI_NULL;
	Papi_actions_HevcDecoder_DecodingPictureBuffer[1].counterValues = malloc(sizeof(unsigned long) * Papi_actions_HevcDecoder_DecodingPictureBuffer[1].eventCodeSetSize);

	fprintf(papi_output_HevcDecoder_DecodingPictureBuffer,"Actor; Action; PAPI_TOT_INS\n");
	fclose(papi_output_HevcDecoder_DecodingPictureBuffer);
	event_init();

	printf("Creating eventlist for action getPix in actor HevcDecoder_DecodingPictureBuffer\n");
	event_create_eventList(&(Papi_actions_HevcDecoder_DecodingPictureBuffer[0].eventSet), Papi_actions_HevcDecoder_DecodingPictureBuffer[0].eventCodeSetSize, Papi_actions_HevcDecoder_DecodingPictureBuffer[0].eventCodeSet, -1);
	printf("Creating eventlist for action isNewSlice in actor HevcDecoder_DecodingPictureBuffer\n");
	event_create_eventList(&(Papi_actions_HevcDecoder_DecodingPictureBuffer[1].eventSet), Papi_actions_HevcDecoder_DecodingPictureBuffer[1].eventCodeSetSize, Papi_actions_HevcDecoder_DecodingPictureBuffer[1].eventCodeSet, -1);
	/* End of Papify initialization */

	write_RefSample();
	/* Set initial state to current FSM state */
	_FSM_state = my_state_IsFirstNewPic;
finished:
	write_end_RefSample();
	return;
}

////////////////////////////////////////////////////////////////////////////////
// Action scheduler

void HevcDecoder_DecodingPictureBuffer_scheduler(schedinfo_t *si) {
	int i = 0;

	read_IsPicSlc();
	read_ReorderPics();
	read_IsBiPredOrLx();
	read_IsReadOrNewSlc();
	read_Mv();
	read_PicSize();
	read_Poc();
	read_PocRef();
	read_PredCuSize();
	read_RpsPoc();
	read_Sample();
	write_RefSample();

	// jump to FSM state
	switch (_FSM_state) {
	case my_state_CheckChromaWidth:
		goto l_CheckChromaWidth;
	case my_state_CheckIsNewPict:
		goto l_CheckIsNewPict;
	case my_state_CheckLumaWidth:
		goto l_CheckLumaWidth;
	case my_state_GetCuPix:
		goto l_GetCuPix;
	case my_state_GetFirstRps:
		goto l_GetFirstRps;
	case my_state_GetMvInfo:
		goto l_GetMvInfo;
	case my_state_GetRps:
		goto l_GetRps;
	case my_state_GetRpsFirstPoc:
		goto l_GetRpsFirstPoc;
	case my_state_GetRpsPoc:
		goto l_GetRpsPoc;
	case my_state_IsFirstNewPic:
		goto l_IsFirstNewPic;
	case my_state_IsNewSlice:
		goto l_IsNewSlice;
	case my_state_SendCuChroma:
		goto l_SendCuChroma;
	case my_state_SendCuChroma11:
		goto l_SendCuChroma11;
	case my_state_SendCuChroma19:
		goto l_SendCuChroma19;
	case my_state_SendCuChroma35:
		goto l_SendCuChroma35;
	case my_state_SendCuChroma5:
		goto l_SendCuChroma5;
	case my_state_SendCuChroma7:
		goto l_SendCuChroma7;
	case my_state_SendCuLuma:
		goto l_SendCuLuma;
	case my_state_SendCuLuma11:
		goto l_SendCuLuma11;
	case my_state_SendCuLuma15:
		goto l_SendCuLuma15;
	case my_state_SendCuLuma23:
		goto l_SendCuLuma23;
	case my_state_SendCuLuma39:
		goto l_SendCuLuma39;
	case my_state_SendCuLuma71:
		goto l_SendCuLuma71;
	default:
		printf("unknown state in HevcDecoder_DecodingPictureBuffer.c : %s\n", stateNames[_FSM_state]);
		exit(1);
	}

	// FSM transitions
l_CheckChromaWidth:
	if (isSchedulable_chromaWidth_is35()) {
		chromaWidth_is35();
		i++;
		goto l_SendCuChroma35;
	} else if (isSchedulable_chromaWidth_is19()) {
		chromaWidth_is19();
		i++;
		goto l_SendCuChroma19;
	} else if (isSchedulable_chromaWidth_is11()) {
		chromaWidth_is11();
		i++;
		goto l_SendCuChroma11;
	} else if (isSchedulable_chromaWidth_is7()) {
		chromaWidth_is7();
		i++;
		goto l_SendCuChroma7;
	} else if (isSchedulable_chromaWidth_is5()) {
		chromaWidth_is5();
		i++;
		goto l_SendCuChroma5;
	} else if (isSchedulable_valWidth_isOther()) {
		valWidth_isOther();
		i++;
		goto l_SendCuChroma;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_CheckChromaWidth;
		goto finished;
	}
l_CheckIsNewPict:
	if (isSchedulable_checkIsNewPict_isTrue()) {
		checkIsNewPict_isTrue();
		i++;
		goto l_GetCuPix;
	} else if (isSchedulable_checkIsNewPict_isFalse()) {
		checkIsNewPict_isFalse();
		i++;
		goto l_IsNewSlice;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_CheckIsNewPict;
		goto finished;
	}
l_CheckLumaWidth:
	if (isSchedulable_lumaWidth_is71()) {
		lumaWidth_is71();
		i++;
		goto l_SendCuLuma71;
	} else if (isSchedulable_lumaWidth_is39()) {
		lumaWidth_is39();
		i++;
		goto l_SendCuLuma39;
	} else if (isSchedulable_lumaWidth_is23()) {
		lumaWidth_is23();
		i++;
		goto l_SendCuLuma23;
	} else if (isSchedulable_lumaWidth_is15()) {
		lumaWidth_is15();
		i++;
		goto l_SendCuLuma15;
	} else if (isSchedulable_lumaWidth_is11()) {
		lumaWidth_is11();
		i++;
		goto l_SendCuLuma11;
	} else if (isSchedulable_valWidth_isOther()) {
		valWidth_isOther();
		i++;
		goto l_SendCuLuma;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_CheckLumaWidth;
		goto finished;
	}
l_GetCuPix:
	if (numTokens_Sample - index_Sample >= 384 && isSchedulable_getPix()) {
		{
			int isAligned = 1;
			isAligned &= ((index_Sample % SIZE_Sample) < ((index_Sample + 384) % SIZE_Sample));
			if (isAligned) {
				getPix_aligned();
			} else {
				getPix();
			}
		}
		i++;
		goto l_GetCuPix;
	} else if (isSchedulable_getCuPix_done()) {
		getCuPix_done();
		i++;
		goto l_IsNewSlice;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetCuPix;
		goto finished;
	}
l_GetFirstRps:
	if (numTokens_RpsPoc - index_RpsPoc >= 1 && isSchedulable_getRps_launch()) {
		getRps_launch();
		i++;
		goto l_GetRpsFirstPoc;
	} else if (isSchedulable_getRps_done()) {
		getRps_done();
		i++;
		goto l_IsNewSlice;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetFirstRps;
		goto finished;
	}
l_GetMvInfo:
	if (numTokens_PocRef - index_PocRef >= 1 && numTokens_PredCuSize - index_PredCuSize >= 2 && numTokens_Mv - index_Mv >= 2 && isSchedulable_getMvInfo_launch()) {
		{
			int isAligned = 1;
			isAligned &= ((index_PredCuSize % SIZE_PredCuSize) < ((index_PredCuSize + 2) % SIZE_PredCuSize));
			isAligned &= ((index_Mv % SIZE_Mv) < ((index_Mv + 2) % SIZE_Mv));
			if (isAligned) {
				getMvInfo_launch_aligned();
			} else {
				getMvInfo_launch();
			}
		}
		i++;
		goto l_CheckLumaWidth;
	} else if (numTokens_PocRef - index_PocRef >= 1 && numTokens_PredCuSize - index_PredCuSize >= 2 && numTokens_Mv - index_Mv >= 2 && isSchedulable_getMvInfo_skip()) {
		{
			int isAligned = 1;
			isAligned &= ((index_PredCuSize % SIZE_PredCuSize) < ((index_PredCuSize + 2) % SIZE_PredCuSize));
			isAligned &= ((index_Mv % SIZE_Mv) < ((index_Mv + 2) % SIZE_Mv));
			if (isAligned) {
				getMvInfo_skip_aligned();
			} else {
				getMvInfo_skip();
			}
		}
		i++;
		goto l_IsNewSlice;
	} else if (isSchedulable_getMvInfo_done()) {
		getMvInfo_done();
		i++;
		goto l_IsNewSlice;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetMvInfo;
		goto finished;
	}
l_GetRps:
	if (numTokens_RpsPoc - index_RpsPoc >= 1 && isSchedulable_getRps_launch()) {
		getRps_launch();
		i++;
		goto l_GetRpsPoc;
	} else if (isSchedulable_getRps_done()) {
		getRps_done();
		i++;
		goto l_CheckIsNewPict;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetRps;
		goto finished;
	}
l_GetRpsFirstPoc:
	if (numTokens_RpsPoc - index_RpsPoc >= 1 && isSchedulable_getRpsPoc_launch()) {
		getRpsPoc_launch();
		i++;
		goto l_GetRpsFirstPoc;
	} else if (isSchedulable_getRpsPoc_done()) {
		getRpsPoc_done();
		i++;
		goto l_GetFirstRps;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetRpsFirstPoc;
		goto finished;
	}
l_GetRpsPoc:
	if (numTokens_RpsPoc - index_RpsPoc >= 1 && isSchedulable_getRpsPoc_launch()) {
		getRpsPoc_launch();
		i++;
		goto l_GetRpsPoc;
	} else if (isSchedulable_getRpsPoc_done()) {
		getRpsPoc_done();
		i++;
		goto l_GetRps;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetRpsPoc;
		goto finished;
	}
l_IsFirstNewPic:
	if (numTokens_IsReadOrNewSlc - index_IsReadOrNewSlc >= 1 && numTokens_PicSize - index_PicSize >= 2 && numTokens_Poc - index_Poc >= 1 && numTokens_IsPicSlc - index_IsPicSlc >= 1 && numTokens_ReorderPics - index_ReorderPics >= 4 && isSchedulable_isNewPict()) {
		{
			int isAligned = 1;
			isAligned &= ((index_PicSize % SIZE_PicSize) < ((index_PicSize + 2) % SIZE_PicSize));
			isAligned &= ((index_ReorderPics % SIZE_ReorderPics) < ((index_ReorderPics + 4) % SIZE_ReorderPics));
			if (isAligned) {
				isNewPict_aligned();
			} else {
				isNewPict();
			}
		}
		i++;
		goto l_GetFirstRps;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_IsFirstNewPic;
		goto finished;
	}
l_IsNewSlice:
	if (numTokens_IsReadOrNewSlc - index_IsReadOrNewSlc >= 1 && numTokens_PicSize - index_PicSize >= 2 && numTokens_Poc - index_Poc >= 1 && numTokens_IsPicSlc - index_IsPicSlc >= 1 && numTokens_ReorderPics - index_ReorderPics >= 4 && isSchedulable_isNewPict()) {
		{
			int isAligned = 1;
			isAligned &= ((index_PicSize % SIZE_PicSize) < ((index_PicSize + 2) % SIZE_PicSize));
			isAligned &= ((index_ReorderPics % SIZE_ReorderPics) < ((index_ReorderPics + 4) % SIZE_ReorderPics));
			if (isAligned) {
				isNewPict_aligned();
			} else {
				isNewPict();
			}
		}
		i++;
		goto l_GetRps;
	} else if (numTokens_IsReadOrNewSlc - index_IsReadOrNewSlc >= 1 && numTokens_IsBiPredOrLx - index_IsBiPredOrLx >= 1 && isSchedulable_getReadAddr()) {
		getReadAddr();
		i++;
		goto l_GetMvInfo;
	} else if (numTokens_IsReadOrNewSlc - index_IsReadOrNewSlc >= 1 && numTokens_PicSize - index_PicSize >= 2 && numTokens_Poc - index_Poc >= 1 && numTokens_IsPicSlc - index_IsPicSlc >= 1 && numTokens_ReorderPics - index_ReorderPics >= 4 && isSchedulable_isNewPict_lastPict()) {
		{
			int isAligned = 1;
			isAligned &= ((index_PicSize % SIZE_PicSize) < ((index_PicSize + 2) % SIZE_PicSize));
			isAligned &= ((index_ReorderPics % SIZE_ReorderPics) < ((index_ReorderPics + 4) % SIZE_ReorderPics));
			if (isAligned) {
				isNewPict_lastPict_aligned();
			} else {
				isNewPict_lastPict();
			}
		}
		i++;
		goto l_GetRps;
	} else if (numTokens_IsReadOrNewSlc - index_IsReadOrNewSlc >= 1 && numTokens_PicSize - index_PicSize >= 2 && numTokens_Poc - index_Poc >= 1 && numTokens_IsPicSlc - index_IsPicSlc >= 1 && isSchedulable_isNewSlice()) {
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
		goto l_GetRps;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_IsNewSlice;
		goto finished;
	}
l_SendCuChroma:
	if (isSchedulable_sendCu_chroma_launch_is1()) {
		int stop = 0;
		if (1 > SIZE_RefSample - index_RefSample + HevcDecoder_DecodingPictureBuffer_RefSample->read_inds[0]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_SendCuChroma;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		sendCu_chroma_launch_is1();
		i++;
		goto l_SendCuChroma;
	} else if (isSchedulable_sendCu_chroma_done()) {
		sendCu_chroma_done();
		i++;
		goto l_GetMvInfo;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_SendCuChroma;
		goto finished;
	}
l_SendCuChroma11:
	if (isSchedulable_sendCu_chroma_launch_is11()) {
		int stop = 0;
		if (11 > SIZE_RefSample - index_RefSample + HevcDecoder_DecodingPictureBuffer_RefSample->read_inds[0]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_SendCuChroma11;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		{
			int isAligned = 1;
			isAligned &= ((index_RefSample % SIZE_RefSample) < ((index_RefSample + 11) % SIZE_RefSample));
			if (isAligned) {
				sendCu_chroma_launch_is11_aligned();
			} else {
				sendCu_chroma_launch_is11();
			}
		}
		i++;
		goto l_SendCuChroma11;
	} else if (isSchedulable_sendCu_chroma_done()) {
		sendCu_chroma_done();
		i++;
		goto l_GetMvInfo;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_SendCuChroma11;
		goto finished;
	}
l_SendCuChroma19:
	if (isSchedulable_sendCu_chroma_launch_is19()) {
		int stop = 0;
		if (19 > SIZE_RefSample - index_RefSample + HevcDecoder_DecodingPictureBuffer_RefSample->read_inds[0]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_SendCuChroma19;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		{
			int isAligned = 1;
			isAligned &= ((index_RefSample % SIZE_RefSample) < ((index_RefSample + 19) % SIZE_RefSample));
			if (isAligned) {
				sendCu_chroma_launch_is19_aligned();
			} else {
				sendCu_chroma_launch_is19();
			}
		}
		i++;
		goto l_SendCuChroma19;
	} else if (isSchedulable_sendCu_chroma_done()) {
		sendCu_chroma_done();
		i++;
		goto l_GetMvInfo;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_SendCuChroma19;
		goto finished;
	}
l_SendCuChroma35:
	if (isSchedulable_sendCu_chroma_launch_is35()) {
		int stop = 0;
		if (35 > SIZE_RefSample - index_RefSample + HevcDecoder_DecodingPictureBuffer_RefSample->read_inds[0]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_SendCuChroma35;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		{
			int isAligned = 1;
			isAligned &= ((index_RefSample % SIZE_RefSample) < ((index_RefSample + 35) % SIZE_RefSample));
			if (isAligned) {
				sendCu_chroma_launch_is35_aligned();
			} else {
				sendCu_chroma_launch_is35();
			}
		}
		i++;
		goto l_SendCuChroma35;
	} else if (isSchedulable_sendCu_chroma_done()) {
		sendCu_chroma_done();
		i++;
		goto l_GetMvInfo;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_SendCuChroma35;
		goto finished;
	}
l_SendCuChroma5:
	if (isSchedulable_sendCu_chroma_launch_is5()) {
		int stop = 0;
		if (5 > SIZE_RefSample - index_RefSample + HevcDecoder_DecodingPictureBuffer_RefSample->read_inds[0]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_SendCuChroma5;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		{
			int isAligned = 1;
			isAligned &= ((index_RefSample % SIZE_RefSample) < ((index_RefSample + 5) % SIZE_RefSample));
			if (isAligned) {
				sendCu_chroma_launch_is5_aligned();
			} else {
				sendCu_chroma_launch_is5();
			}
		}
		i++;
		goto l_SendCuChroma5;
	} else if (isSchedulable_sendCu_chroma_done()) {
		sendCu_chroma_done();
		i++;
		goto l_GetMvInfo;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_SendCuChroma5;
		goto finished;
	}
l_SendCuChroma7:
	if (isSchedulable_sendCu_chroma_launch_is7()) {
		int stop = 0;
		if (7 > SIZE_RefSample - index_RefSample + HevcDecoder_DecodingPictureBuffer_RefSample->read_inds[0]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_SendCuChroma7;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		{
			int isAligned = 1;
			isAligned &= ((index_RefSample % SIZE_RefSample) < ((index_RefSample + 7) % SIZE_RefSample));
			if (isAligned) {
				sendCu_chroma_launch_is7_aligned();
			} else {
				sendCu_chroma_launch_is7();
			}
		}
		i++;
		goto l_SendCuChroma7;
	} else if (isSchedulable_sendCu_chroma_done()) {
		sendCu_chroma_done();
		i++;
		goto l_GetMvInfo;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_SendCuChroma7;
		goto finished;
	}
l_SendCuLuma:
	if (isSchedulable_sendCu_luma_launch_is1()) {
		int stop = 0;
		if (1 > SIZE_RefSample - index_RefSample + HevcDecoder_DecodingPictureBuffer_RefSample->read_inds[0]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_SendCuLuma;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		sendCu_luma_launch_is1();
		i++;
		goto l_SendCuLuma;
	} else if (isSchedulable_sendCu_luma_done()) {
		sendCu_luma_done();
		i++;
		goto l_CheckChromaWidth;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_SendCuLuma;
		goto finished;
	}
l_SendCuLuma11:
	if (isSchedulable_sendCu_luma_launch_is11()) {
		int stop = 0;
		if (11 > SIZE_RefSample - index_RefSample + HevcDecoder_DecodingPictureBuffer_RefSample->read_inds[0]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_SendCuLuma11;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		{
			int isAligned = 1;
			isAligned &= ((index_RefSample % SIZE_RefSample) < ((index_RefSample + 11) % SIZE_RefSample));
			if (isAligned) {
				sendCu_luma_launch_is11_aligned();
			} else {
				sendCu_luma_launch_is11();
			}
		}
		i++;
		goto l_SendCuLuma11;
	} else if (isSchedulable_sendCu_luma_done()) {
		sendCu_luma_done();
		i++;
		goto l_CheckChromaWidth;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_SendCuLuma11;
		goto finished;
	}
l_SendCuLuma15:
	if (isSchedulable_sendCu_luma_launch_is15()) {
		int stop = 0;
		if (15 > SIZE_RefSample - index_RefSample + HevcDecoder_DecodingPictureBuffer_RefSample->read_inds[0]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_SendCuLuma15;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		{
			int isAligned = 1;
			isAligned &= ((index_RefSample % SIZE_RefSample) < ((index_RefSample + 15) % SIZE_RefSample));
			if (isAligned) {
				sendCu_luma_launch_is15_aligned();
			} else {
				sendCu_luma_launch_is15();
			}
		}
		i++;
		goto l_SendCuLuma15;
	} else if (isSchedulable_sendCu_luma_done()) {
		sendCu_luma_done();
		i++;
		goto l_CheckChromaWidth;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_SendCuLuma15;
		goto finished;
	}
l_SendCuLuma23:
	if (isSchedulable_sendCu_luma_launch_is23()) {
		int stop = 0;
		if (23 > SIZE_RefSample - index_RefSample + HevcDecoder_DecodingPictureBuffer_RefSample->read_inds[0]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_SendCuLuma23;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		{
			int isAligned = 1;
			isAligned &= ((index_RefSample % SIZE_RefSample) < ((index_RefSample + 23) % SIZE_RefSample));
			if (isAligned) {
				sendCu_luma_launch_is23_aligned();
			} else {
				sendCu_luma_launch_is23();
			}
		}
		i++;
		goto l_SendCuLuma23;
	} else if (isSchedulable_sendCu_luma_done()) {
		sendCu_luma_done();
		i++;
		goto l_CheckChromaWidth;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_SendCuLuma23;
		goto finished;
	}
l_SendCuLuma39:
	if (isSchedulable_sendCu_luma_launch_is39()) {
		int stop = 0;
		if (39 > SIZE_RefSample - index_RefSample + HevcDecoder_DecodingPictureBuffer_RefSample->read_inds[0]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_SendCuLuma39;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		{
			int isAligned = 1;
			isAligned &= ((index_RefSample % SIZE_RefSample) < ((index_RefSample + 39) % SIZE_RefSample));
			if (isAligned) {
				sendCu_luma_launch_is39_aligned();
			} else {
				sendCu_luma_launch_is39();
			}
		}
		i++;
		goto l_SendCuLuma39;
	} else if (isSchedulable_sendCu_luma_done()) {
		sendCu_luma_done();
		i++;
		goto l_CheckChromaWidth;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_SendCuLuma39;
		goto finished;
	}
l_SendCuLuma71:
	if (isSchedulable_sendCu_luma_launch_is71()) {
		int stop = 0;
		if (71 > SIZE_RefSample - index_RefSample + HevcDecoder_DecodingPictureBuffer_RefSample->read_inds[0]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_SendCuLuma71;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		{
			int isAligned = 1;
			isAligned &= ((index_RefSample % SIZE_RefSample) < ((index_RefSample + 71) % SIZE_RefSample));
			if (isAligned) {
				sendCu_luma_launch_is71_aligned();
			} else {
				sendCu_luma_launch_is71();
			}
		}
		i++;
		goto l_SendCuLuma71;
	} else if (isSchedulable_sendCu_luma_done()) {
		sendCu_luma_done();
		i++;
		goto l_CheckChromaWidth;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_SendCuLuma71;
		goto finished;
	}
finished:
	read_end_IsPicSlc();
	read_end_ReorderPics();
	read_end_IsBiPredOrLx();
	read_end_IsReadOrNewSlc();
	read_end_Mv();
	read_end_PicSize();
	read_end_Poc();
	read_end_PocRef();
	read_end_PredCuSize();
	read_end_RpsPoc();
	read_end_Sample();
	write_end_RefSample();
}
