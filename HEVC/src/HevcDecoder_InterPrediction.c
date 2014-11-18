// Source file is "L/RVC/src/org/sc29/wg11/mpegh/part2/main/inter/InterPrediction.cal"

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
extern actor_t HevcDecoder_InterPrediction;

////////////////////////////////////////////////////////////////////////////////
// Input FIFOs
extern fifo_u16_t *HevcDecoder_InterPrediction_CUInfo;
extern fifo_u8_t *HevcDecoder_InterPrediction_IsBiPredOrLx;
extern fifo_i32_t *HevcDecoder_InterPrediction_Mv;
extern fifo_u8_t *HevcDecoder_InterPrediction_PartMode;
extern fifo_i16_t *HevcDecoder_InterPrediction_Poc;
extern fifo_u8_t *HevcDecoder_InterPrediction_RefIdx;
extern fifo_i16_t *HevcDecoder_InterPrediction_RefList;
extern fifo_u8_t *HevcDecoder_InterPrediction_Sample;
extern fifo_u8_t *HevcDecoder_InterPrediction_SliceType;
extern fifo_i16_t *HevcDecoder_InterPrediction_WeightedPredSe;

////////////////////////////////////////////////////////////////////////////////
// Input Fifo control variables
static unsigned int index_CUInfo;
static unsigned int numTokens_CUInfo;
#define SIZE_CUInfo SIZE
#define tokens_CUInfo HevcDecoder_InterPrediction_CUInfo->contents

extern connection_t connection_HevcDecoder_InterPrediction_CUInfo;
#define rate_CUInfo connection_HevcDecoder_InterPrediction_CUInfo.rate

static unsigned int index_IsBiPredOrLx;
static unsigned int numTokens_IsBiPredOrLx;
#define SIZE_IsBiPredOrLx SIZE
#define tokens_IsBiPredOrLx HevcDecoder_InterPrediction_IsBiPredOrLx->contents

extern connection_t connection_HevcDecoder_InterPrediction_IsBiPredOrLx;
#define rate_IsBiPredOrLx connection_HevcDecoder_InterPrediction_IsBiPredOrLx.rate

static unsigned int index_Mv;
static unsigned int numTokens_Mv;
#define SIZE_Mv SIZE
#define tokens_Mv HevcDecoder_InterPrediction_Mv->contents

extern connection_t connection_HevcDecoder_InterPrediction_Mv;
#define rate_Mv connection_HevcDecoder_InterPrediction_Mv.rate

static unsigned int index_PartMode;
static unsigned int numTokens_PartMode;
#define SIZE_PartMode SIZE
#define tokens_PartMode HevcDecoder_InterPrediction_PartMode->contents

extern connection_t connection_HevcDecoder_InterPrediction_PartMode;
#define rate_PartMode connection_HevcDecoder_InterPrediction_PartMode.rate

static unsigned int index_Poc;
static unsigned int numTokens_Poc;
#define SIZE_Poc SIZE
#define tokens_Poc HevcDecoder_InterPrediction_Poc->contents

extern connection_t connection_HevcDecoder_InterPrediction_Poc;
#define rate_Poc connection_HevcDecoder_InterPrediction_Poc.rate

static unsigned int index_RefIdx;
static unsigned int numTokens_RefIdx;
#define SIZE_RefIdx SIZE
#define tokens_RefIdx HevcDecoder_InterPrediction_RefIdx->contents

extern connection_t connection_HevcDecoder_InterPrediction_RefIdx;
#define rate_RefIdx connection_HevcDecoder_InterPrediction_RefIdx.rate

static unsigned int index_RefList;
static unsigned int numTokens_RefList;
#define SIZE_RefList SIZE
#define tokens_RefList HevcDecoder_InterPrediction_RefList->contents

extern connection_t connection_HevcDecoder_InterPrediction_RefList;
#define rate_RefList connection_HevcDecoder_InterPrediction_RefList.rate

static unsigned int index_Sample;
static unsigned int numTokens_Sample;
#define SIZE_Sample SIZE
#define tokens_Sample HevcDecoder_InterPrediction_Sample->contents

extern connection_t connection_HevcDecoder_InterPrediction_Sample;
#define rate_Sample connection_HevcDecoder_InterPrediction_Sample.rate

static unsigned int index_SliceType;
static unsigned int numTokens_SliceType;
#define SIZE_SliceType SIZE
#define tokens_SliceType HevcDecoder_InterPrediction_SliceType->contents

extern connection_t connection_HevcDecoder_InterPrediction_SliceType;
#define rate_SliceType connection_HevcDecoder_InterPrediction_SliceType.rate

static unsigned int index_WeightedPredSe;
static unsigned int numTokens_WeightedPredSe;
#define SIZE_WeightedPredSe 16384
#define tokens_WeightedPredSe HevcDecoder_InterPrediction_WeightedPredSe->contents

extern connection_t connection_HevcDecoder_InterPrediction_WeightedPredSe;
#define rate_WeightedPredSe connection_HevcDecoder_InterPrediction_WeightedPredSe.rate

////////////////////////////////////////////////////////////////////////////////
// Predecessors
extern actor_t HevcDecoder_Algo_Parser;
extern actor_t HevcDecoder_generateInfo_MvComponentPred;
extern actor_t HevcDecoder_generateInfo_MvComponentPred;
extern actor_t HevcDecoder_Algo_Parser;
extern actor_t HevcDecoder_Algo_Parser;
extern actor_t HevcDecoder_generateInfo_MvComponentPred;
extern actor_t HevcDecoder_generateInfo_GenerateRefList;
extern actor_t HevcDecoder_DecodingPictureBuffer;
extern actor_t HevcDecoder_Algo_Parser;
extern actor_t HevcDecoder_Algo_Parser;

////////////////////////////////////////////////////////////////////////////////
// Output FIFOs
extern fifo_u8_t *HevcDecoder_InterPrediction_PredSample;

////////////////////////////////////////////////////////////////////////////////
// Output Fifo control variables
static unsigned int index_PredSample;
static unsigned int numFree_PredSample;
#define NUM_READERS_PredSample 1
#define SIZE_PredSample SIZE
#define tokens_PredSample HevcDecoder_InterPrediction_PredSample->contents

////////////////////////////////////////////////////////////////////////////////
// Successors
extern actor_t HevcDecoder_SelectCU;


////////////////////////////////////////////////////////////////////////////////
// State variables of the actor
#define HevcDecoder_InterPrediction_shift1 6
#define HevcDecoder_InterPrediction_B_SLICE 0
#define HevcDecoder_InterPrediction_PART_MODE_SLICE_DEP 9
#define HevcDecoder_InterPrediction_PART_MODE_SLICE_INDEP 10
#define HevcDecoder_InterPrediction_PART_MODE_PICT 8
static const u8 HevcDecoder_InterPrediction_partModeToNumPart[8] = {1, 2, 2, 4, 2, 2, 2, 2};
#define HevcDecoder_InterPrediction_INTER 0
#define HevcDecoder_InterPrediction_SKIP 2
#define HevcDecoder_InterPrediction_BI_PRED 2
#define HevcDecoder_InterPrediction_PRED_L0 0
#define HevcDecoder_InterPrediction_PRED_L1 1
static const i8 HevcDecoder_InterPrediction_ff_hevc_epel_filters[7][4] = {{-2, 58, 10, -2}, {-4, 54, 16, -2}, {-6, 46, 28, -4}, {-4, 36, 36, -4}, {-4, 28, 46, -6}, {-2, 16, 54, -4}, {-2, 10, 58, -2}};
#define HevcDecoder_InterPrediction_maxPixVal 255
#define SZ_REF_LIST 16
static i16 currPoc;
static u8 listIdx;
static u8 iLoop;
static u8 jLoop;
static u16 pixIdx;
static u16 pixIdxOff[2];
static u8 compIdx;
static i16 refListX[2][16];
static u8 wpIdc;
static u8 numRefIdxLxAct[2];
static i32 isBSlice;
static u8 refIdxLxAct;
static u8 log2WeightDenom[3];
static i32 weight[16][2][3];
static i32 offset[16][2][3];
static u8 numPartDecoded;
static u8 numPart;
static u8 puSize[2];
static u8 fullPuSize[2];
static u8 fullPuSizeChr[2];
static u8 cuMode;
static i32 logWD_y;
static i32 logWD_u;
static i32 logWD_v;
static i32 weightCu_y[2];
static i32 weightCu_u[2];
static i32 weightCu_v[2];
static i32 offsetCu_y[2];
static i32 offsetCu_u[2];
static i32 offsetCu_v[2];
static u8 isBiPredOrLx;
static i8 refIdxLx[2];
static i32 mvLx[2][2];
static u8 numList;
static u8 predCuSize;
static i32 logWDTab[17][17][3];
static i32 weightCuTab[17][17][3][2];
static i32 offsetCuTab[17][17][3][2];
static u8 refSamples_y[5041];
static u8 refSamples_u[5041];
static u8 refSamples_v[5041];
static i16 predSamples_y[2][4096];
static i16 predSamples_u[2][4096];
static i16 predSamples_v[2][4096];
static u8 weightSamples_y[4096];
static u8 weightSamples_u[4096];
static u8 weightSamples_v[4096];

////////////////////////////////////////////////////////////////////////////////
// Initial FSM state of the actor
enum states {
	my_state_CheckChromaWidth,
	my_state_CheckLumaWidth,
	my_state_GetChromaSamples,
	my_state_GetChromaSamples11,
	my_state_GetChromaSamples19,
	my_state_GetChromaSamples35,
	my_state_GetChromaSamples5,
	my_state_GetChromaSamples7,
	my_state_GetChromaWeightLX,
	my_state_GetCuInfo,
	my_state_GetCuMode,
	my_state_GetDeltaChrWtLX,
	my_state_GetDeltaLumWtLX,
	my_state_GetLumaSamples,
	my_state_GetLumaSamples11,
	my_state_GetLumaSamples15,
	my_state_GetLumaSamples23,
	my_state_GetLumaSamples39,
	my_state_GetLumaSamples71,
	my_state_GetLumaWeightLX,
	my_state_GetPartMode,
	my_state_GetRefIdx,
	my_state_GetRefList,
	my_state_GetSamples,
	my_state_GetSizeRefList,
	my_state_GetWeightDenom,
	my_state_GetWeightLX,
	my_state_InterpolateSamples,
	my_state_SendCu
};

static char *stateNames[] = {
	"CheckChromaWidth",
	"CheckLumaWidth",
	"GetChromaSamples",
	"GetChromaSamples11",
	"GetChromaSamples19",
	"GetChromaSamples35",
	"GetChromaSamples5",
	"GetChromaSamples7",
	"GetChromaWeightLX",
	"GetCuInfo",
	"GetCuMode",
	"GetDeltaChrWtLX",
	"GetDeltaLumWtLX",
	"GetLumaSamples",
	"GetLumaSamples11",
	"GetLumaSamples15",
	"GetLumaSamples23",
	"GetLumaSamples39",
	"GetLumaSamples71",
	"GetLumaWeightLX",
	"GetPartMode",
	"GetRefIdx",
	"GetRefList",
	"GetSamples",
	"GetSizeRefList",
	"GetWeightDenom",
	"GetWeightLX",
	"InterpolateSamples",
	"SendCu"
};

static enum states _FSM_state;



////////////////////////////////////////////////////////////////////////////////
// Token functions
static void read_CUInfo() {
	index_CUInfo = HevcDecoder_InterPrediction_CUInfo->read_inds[1];
	numTokens_CUInfo = index_CUInfo + fifo_u16_get_num_tokens(HevcDecoder_InterPrediction_CUInfo, 1);
}

static void read_end_CUInfo() {
	HevcDecoder_InterPrediction_CUInfo->read_inds[1] = index_CUInfo;
}
static void read_IsBiPredOrLx() {
	index_IsBiPredOrLx = HevcDecoder_InterPrediction_IsBiPredOrLx->read_inds[0];
	numTokens_IsBiPredOrLx = index_IsBiPredOrLx + fifo_u8_get_num_tokens(HevcDecoder_InterPrediction_IsBiPredOrLx, 0);
}

static void read_end_IsBiPredOrLx() {
	HevcDecoder_InterPrediction_IsBiPredOrLx->read_inds[0] = index_IsBiPredOrLx;
}
static void read_Mv() {
	index_Mv = HevcDecoder_InterPrediction_Mv->read_inds[0];
	numTokens_Mv = index_Mv + fifo_i32_get_num_tokens(HevcDecoder_InterPrediction_Mv, 0);
}

static void read_end_Mv() {
	HevcDecoder_InterPrediction_Mv->read_inds[0] = index_Mv;
}
static void read_PartMode() {
	index_PartMode = HevcDecoder_InterPrediction_PartMode->read_inds[2];
	numTokens_PartMode = index_PartMode + fifo_u8_get_num_tokens(HevcDecoder_InterPrediction_PartMode, 2);
}

static void read_end_PartMode() {
	HevcDecoder_InterPrediction_PartMode->read_inds[2] = index_PartMode;
}
static void read_Poc() {
	index_Poc = HevcDecoder_InterPrediction_Poc->read_inds[1];
	numTokens_Poc = index_Poc + fifo_i16_get_num_tokens(HevcDecoder_InterPrediction_Poc, 1);
}

static void read_end_Poc() {
	HevcDecoder_InterPrediction_Poc->read_inds[1] = index_Poc;
}
static void read_RefIdx() {
	index_RefIdx = HevcDecoder_InterPrediction_RefIdx->read_inds[0];
	numTokens_RefIdx = index_RefIdx + fifo_u8_get_num_tokens(HevcDecoder_InterPrediction_RefIdx, 0);
}

static void read_end_RefIdx() {
	HevcDecoder_InterPrediction_RefIdx->read_inds[0] = index_RefIdx;
}
static void read_RefList() {
	index_RefList = HevcDecoder_InterPrediction_RefList->read_inds[1];
	numTokens_RefList = index_RefList + fifo_i16_get_num_tokens(HevcDecoder_InterPrediction_RefList, 1);
}

static void read_end_RefList() {
	HevcDecoder_InterPrediction_RefList->read_inds[1] = index_RefList;
}
static void read_Sample() {
	index_Sample = HevcDecoder_InterPrediction_Sample->read_inds[0];
	numTokens_Sample = index_Sample + fifo_u8_get_num_tokens(HevcDecoder_InterPrediction_Sample, 0);
}

static void read_end_Sample() {
	HevcDecoder_InterPrediction_Sample->read_inds[0] = index_Sample;
}
static void read_SliceType() {
	index_SliceType = HevcDecoder_InterPrediction_SliceType->read_inds[0];
	numTokens_SliceType = index_SliceType + fifo_u8_get_num_tokens(HevcDecoder_InterPrediction_SliceType, 0);
}

static void read_end_SliceType() {
	HevcDecoder_InterPrediction_SliceType->read_inds[0] = index_SliceType;
}
static void read_WeightedPredSe() {
	index_WeightedPredSe = HevcDecoder_InterPrediction_WeightedPredSe->read_inds[0];
	numTokens_WeightedPredSe = index_WeightedPredSe + fifo_i16_get_num_tokens(HevcDecoder_InterPrediction_WeightedPredSe, 0);
}

static void read_end_WeightedPredSe() {
	HevcDecoder_InterPrediction_WeightedPredSe->read_inds[0] = index_WeightedPredSe;
}

static void write_PredSample() {
	index_PredSample = HevcDecoder_InterPrediction_PredSample->write_ind;
	numFree_PredSample = index_PredSample + fifo_u8_get_room(HevcDecoder_InterPrediction_PredSample, NUM_READERS_PredSample, SIZE_PredSample);
}

static void write_end_PredSample() {
	HevcDecoder_InterPrediction_PredSample->write_ind = index_PredSample;
}

////////////////////////////////////////////////////////////////////////////////
// Functions/procedures
static i32 HevcDecoder_InterPrediction_clip_i32(i32 Value, i32 minVal, i32 maxVal);
static i32 HevcDecoder_InterPrediction_abs(i32 x);
static i32 HevcDecoder_InterPrediction_max(i32 a, i32 b);
static i16 HevcDecoder_InterPrediction_QPEL_FILTER_3_H(u8 src[5041], u8 srcStride, u8 x, u8 y);
static i16 HevcDecoder_InterPrediction_QPEL_FILTER_2_H(u8 src[5041], u8 srcStride, u8 x, u8 y);
static i16 HevcDecoder_InterPrediction_QPEL_FILTER_1_H(u8 src[5041], u8 srcStride, u8 x, u8 y);
static i32 HevcDecoder_InterPrediction_QPEL_FILTER_3_V_16(i16 src[5041], u8 srcStride, u8 x, u8 y);
static i32 HevcDecoder_InterPrediction_QPEL_FILTER_2_V_16(i16 src[5041], u8 srcStride, u8 x, u8 y);
static i32 HevcDecoder_InterPrediction_QPEL_FILTER_1_V_16(i16 src[5041], u8 srcStride, u8 x, u8 y);
static void HevcDecoder_InterPrediction_put_hevc_qpel_hv_cal(i16 predSamples[2][4096], u8 listIdx, u8 refSamples[5041], u8 predCuSize, u8 width, u8 height, i32 mx, i32 my);
static i16 HevcDecoder_InterPrediction_QPEL_FILTER_3_V(u8 src[5041], u8 srcStride, u8 x, u8 y);
static i16 HevcDecoder_InterPrediction_QPEL_FILTER_2_V(u8 src[5041], u8 srcStride, u8 x, u8 y);
static i16 HevcDecoder_InterPrediction_QPEL_FILTER_1_V(u8 src[5041], u8 srcStride, u8 x, u8 y);
static void HevcDecoder_InterPrediction_put_hevc_qpel_v_cal(i16 predSamples[2][4096], u8 listIdx, u8 refSamples[5041], u8 predCuSize, u8 width, u8 height, i32 my);
static void HevcDecoder_InterPrediction_put_hevc_qpel_h_cal(i16 predSamples[2][4096], u8 listIdx, u8 refSamples[5041], u8 predCuSize, u8 width, u8 height, i32 mx);
static void HevcDecoder_InterPrediction_put_hevc_qpel_pixel_cal(i16 predSamples[2][4096], u8 listIdx, u8 refSamples[5041], u8 predCuSize, u8 width, u8 height);
static void HevcDecoder_InterPrediction_put_hevc_qpel_cal(i16 predSamples[2][4096], u8 listIdx, u8 refSamples[5041], u8 predCuSize, u8 width, u8 height, i32 mx, i32 my);
static i16 HevcDecoder_InterPrediction_EPEL_FILTER_H(u8 src[5041], u8 srcStride, u8 x, u8 y, i8 filter_0, i8 filter_1, i8 filter_2, i8 filter_3);
static i32 HevcDecoder_InterPrediction_EPEL_FILTER_V_16(i16 src[5041], u8 srcStride, i16 x, i16 y, i8 filter_0, i8 filter_1, i8 filter_2, i8 filter_3);
static void HevcDecoder_InterPrediction_put_hevc_epel_hv_cal(i16 predSamples[2][4096], u8 listIdx, u8 refSamples[5041], u8 predCuSize, u8 width, u8 height, i32 mx, i32 my);
static i16 HevcDecoder_InterPrediction_EPEL_FILTER_V(u8 src[5041], u8 srcStride, i16 x, i16 y, i8 filter_0, i8 filter_1, i8 filter_2, i8 filter_3);
static void HevcDecoder_InterPrediction_put_hevc_epel_v_cal(i16 predSamples[2][4096], u8 listIdx, u8 refSamples[5041], u8 predCuSize, u8 width, u8 height, i32 my);
static void HevcDecoder_InterPrediction_put_hevc_epel_h_cal(i16 predSamples[2][4096], u8 listIdx, u8 refSamples[5041], u8 predCuSize, u8 width, u8 height, i32 mx);
static void HevcDecoder_InterPrediction_put_hevc_epel_pixel_cal(i16 predSamples[2][4096], u8 listIdx, u8 refSamples[5041], u8 predCuSize, u8 width, u8 height);
static void HevcDecoder_InterPrediction_put_hevc_epel_cal(i16 predSamples[2][4096], u8 listIdx, u8 refSamples[5041], u8 predCuSize, u8 width, u8 height, i32 mx, i32 my);
static void HevcDecoder_InterPrediction_put_unweighted_pred(i16 src[2][4096], i32 width, i32 height, u8 rdList, u8 dst[4096]);
static void HevcDecoder_InterPrediction_weighted_pred(i32 logWD, i32 weightCu[2], i32 offsetCu[2], i16 src[2][4096], i32 width, i32 height, u8 rdList, u8 dst[4096]);
static void HevcDecoder_InterPrediction_weighted_pred_mono(i32 logWD, i32 weightCu[2], i32 offsetCu[2], i16 src[2][4096], i32 width, i32 height, u8 dst[4096]);
static void HevcDecoder_InterPrediction_put_weighted_pred_avg(i16 src[2][4096], i32 width, i32 height, u8 dst[4096]);
static void HevcDecoder_InterPrediction_weighted_pred_avg(i32 logWD, i32 weightCu[2], i32 offsetCu[2], i16 src[2][4096], i32 width, i32 height, u8 dst[4096]);
static void computeWeights(i32 refIdxL0, i32 refIdxL1);

static i32 HevcDecoder_InterPrediction_clip_i32(i32 Value, i32 minVal, i32 maxVal) {
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
static i32 HevcDecoder_InterPrediction_abs(i32 x) {
	i32 tmp_if;

	if (x > 0) {
		tmp_if = x;
	} else {
		tmp_if = -x;
	}
	return tmp_if;
}
static i32 HevcDecoder_InterPrediction_max(i32 a, i32 b) {
	i32 tmp_if;

	if (a > b) {
		tmp_if = a;
	} else {
		tmp_if = b;
	}
	return tmp_if;
}
static i16 HevcDecoder_InterPrediction_QPEL_FILTER_3_H(u8 src[5041], u8 srcStride, u8 x, u8 y) {
	u8 tmp_src;
	u8 tmp_src0;
	u8 tmp_src1;
	u8 tmp_src2;
	u8 tmp_src3;
	u8 tmp_src4;
	u8 tmp_src5;

	tmp_src = src[x - 2 + y * srcStride];
	tmp_src0 = src[x - 1 + y * srcStride];
	tmp_src1 = src[x + y * srcStride];
	tmp_src2 = src[x + 1 + y * srcStride];
	tmp_src3 = src[x + 2 + y * srcStride];
	tmp_src4 = src[x + 3 + y * srcStride];
	tmp_src5 = src[x + 4 + y * srcStride];
	return tmp_src - 5 * tmp_src0 + 17 * tmp_src1 + 58 * tmp_src2 - 10 * tmp_src3 + 4 * tmp_src4 - tmp_src5;
}
static i16 HevcDecoder_InterPrediction_QPEL_FILTER_2_H(u8 src[5041], u8 srcStride, u8 x, u8 y) {
	u8 tmp_src;
	u8 tmp_src0;
	u8 tmp_src1;
	u8 tmp_src2;
	u8 tmp_src3;
	u8 tmp_src4;
	u8 tmp_src5;
	u8 tmp_src6;

	tmp_src = src[x - 3 + y * srcStride];
	tmp_src0 = src[x - 2 + y * srcStride];
	tmp_src1 = src[x - 1 + y * srcStride];
	tmp_src2 = src[x + y * srcStride];
	tmp_src3 = src[x + 1 + y * srcStride];
	tmp_src4 = src[x + 2 + y * srcStride];
	tmp_src5 = src[x + 3 + y * srcStride];
	tmp_src6 = src[x + 4 + y * srcStride];
	return -tmp_src + 4 * tmp_src0 - 11 * tmp_src1 + 40 * tmp_src2 + 40 * tmp_src3 - 11 * tmp_src4 + 4 * tmp_src5 - tmp_src6;
}
static i16 HevcDecoder_InterPrediction_QPEL_FILTER_1_H(u8 src[5041], u8 srcStride, u8 x, u8 y) {
	u8 tmp_src;
	u8 tmp_src0;
	u8 tmp_src1;
	u8 tmp_src2;
	u8 tmp_src3;
	u8 tmp_src4;
	u8 tmp_src5;

	tmp_src = src[x - 3 + y * srcStride];
	tmp_src0 = src[x - 2 + y * srcStride];
	tmp_src1 = src[x - 1 + y * srcStride];
	tmp_src2 = src[x + y * srcStride];
	tmp_src3 = src[x + 1 + y * srcStride];
	tmp_src4 = src[x + 2 + y * srcStride];
	tmp_src5 = src[x + 3 + y * srcStride];
	return -tmp_src + 4 * tmp_src0 - 10 * tmp_src1 + 58 * tmp_src2 + 17 * tmp_src3 - 5 * tmp_src4 + 1 * tmp_src5;
}
static i32 HevcDecoder_InterPrediction_QPEL_FILTER_3_V_16(i16 src[5041], u8 srcStride, u8 x, u8 y) {
	i16 tmp_src;
	i16 tmp_src0;
	i16 tmp_src1;
	i16 tmp_src2;
	i16 tmp_src3;
	i16 tmp_src4;
	i16 tmp_src5;

	tmp_src = src[x + (y - 2) * srcStride];
	tmp_src0 = src[x + (y - 1) * srcStride];
	tmp_src1 = src[x + y * srcStride];
	tmp_src2 = src[x + (y + 1) * srcStride];
	tmp_src3 = src[x + (y + 2) * srcStride];
	tmp_src4 = src[x + (y + 3) * srcStride];
	tmp_src5 = src[x + (y + 4) * srcStride];
	return tmp_src - 5 * tmp_src0 + 17 * tmp_src1 + 58 * tmp_src2 - 10 * tmp_src3 + 4 * tmp_src4 - tmp_src5;
}
static i32 HevcDecoder_InterPrediction_QPEL_FILTER_2_V_16(i16 src[5041], u8 srcStride, u8 x, u8 y) {
	i16 tmp_src;
	i16 tmp_src0;
	i16 tmp_src1;
	i16 tmp_src2;
	i16 tmp_src3;
	i16 tmp_src4;
	i16 tmp_src5;
	i16 tmp_src6;

	tmp_src = src[x + (y - 3) * srcStride];
	tmp_src0 = src[x + (y - 2) * srcStride];
	tmp_src1 = src[x + (y - 1) * srcStride];
	tmp_src2 = src[x + y * srcStride];
	tmp_src3 = src[x + (y + 1) * srcStride];
	tmp_src4 = src[x + (y + 2) * srcStride];
	tmp_src5 = src[x + (y + 3) * srcStride];
	tmp_src6 = src[x + (y + 4) * srcStride];
	return -tmp_src + 4 * tmp_src0 - 11 * tmp_src1 + 40 * tmp_src2 + 40 * tmp_src3 - 11 * tmp_src4 + 4 * tmp_src5 - tmp_src6;
}
static i32 HevcDecoder_InterPrediction_QPEL_FILTER_1_V_16(i16 src[5041], u8 srcStride, u8 x, u8 y) {
	i16 tmp_src;
	i16 tmp_src0;
	i16 tmp_src1;
	i16 tmp_src2;
	i16 tmp_src3;
	i16 tmp_src4;
	i16 tmp_src5;

	tmp_src = src[x + (y - 3) * srcStride];
	tmp_src0 = src[x + (y - 2) * srcStride];
	tmp_src1 = src[x + (y - 1) * srcStride];
	tmp_src2 = src[x + y * srcStride];
	tmp_src3 = src[x + (y + 1) * srcStride];
	tmp_src4 = src[x + (y + 2) * srcStride];
	tmp_src5 = src[x + (y + 3) * srcStride];
	return -tmp_src + 4 * tmp_src0 - 10 * tmp_src1 + 58 * tmp_src2 + 17 * tmp_src3 - 5 * tmp_src4 + 1 * tmp_src5;
}
static void HevcDecoder_InterPrediction_put_hevc_qpel_hv_cal(i16 predSamples[2][4096], u8 listIdx, u8 refSamples[5041], u8 predCuSize, u8 width, u8 height, i32 mx, i32 my) {
	i16 intermSamples[5041];
	i32 y;
	i32 x;
	i16 tmp_QPEL_FILTER_1_H;
	i32 y0;
	i32 x0;
	i16 tmp_QPEL_FILTER_2_H;
	i32 y1;
	i32 x1;
	i16 tmp_QPEL_FILTER_3_H;
	i32 y2;
	i32 x2;
	i32 tmp_QPEL_FILTER_1_V_16;
	i32 y3;
	i32 x3;
	i32 tmp_QPEL_FILTER_2_V_16;
	i32 y4;
	i32 x4;
	i32 tmp_QPEL_FILTER_3_V_16;

	if (mx == 1) {
		y = 0;
		while (y <= height + 7) {
			x = 0;
			while (x <= width) {
				tmp_QPEL_FILTER_1_H = HevcDecoder_InterPrediction_QPEL_FILTER_1_H(refSamples, predCuSize, x + 3, y);
				intermSamples[x + y * predCuSize] = tmp_QPEL_FILTER_1_H - 8192;
				x = x + 1;
			}
			y = y + 1;
		}
	} else {
		if (mx == 2) {
			y0 = 0;
			while (y0 <= height + 7) {
				x0 = 0;
				while (x0 <= width) {
					tmp_QPEL_FILTER_2_H = HevcDecoder_InterPrediction_QPEL_FILTER_2_H(refSamples, predCuSize, x0 + 3, y0);
					intermSamples[x0 + y0 * predCuSize] = tmp_QPEL_FILTER_2_H - 8192;
					x0 = x0 + 1;
				}
				y0 = y0 + 1;
			}
		} else {
			if (mx == 3) {
				y1 = 0;
				while (y1 <= height + 7) {
					x1 = 0;
					while (x1 <= width) {
						tmp_QPEL_FILTER_3_H = HevcDecoder_InterPrediction_QPEL_FILTER_3_H(refSamples, predCuSize, x1 + 3, y1);
						intermSamples[x1 + y1 * predCuSize] = tmp_QPEL_FILTER_3_H - 8192;
						x1 = x1 + 1;
					}
					y1 = y1 + 1;
				}
			}
		}
	}
	if (my == 1) {
		y2 = 0;
		while (y2 <= height) {
			x2 = 0;
			while (x2 <= width) {
				tmp_QPEL_FILTER_1_V_16 = HevcDecoder_InterPrediction_QPEL_FILTER_1_V_16(intermSamples, predCuSize, x2, y2 + 3);
				predSamples[listIdx][x2 + y2 * (width + 1)] = (tmp_QPEL_FILTER_1_V_16 + 524288) >> 6;
				x2 = x2 + 1;
			}
			y2 = y2 + 1;
		}
	} else {
		if (my == 2) {
			y3 = 0;
			while (y3 <= height) {
				x3 = 0;
				while (x3 <= width) {
					tmp_QPEL_FILTER_2_V_16 = HevcDecoder_InterPrediction_QPEL_FILTER_2_V_16(intermSamples, predCuSize, x3, y3 + 3);
					predSamples[listIdx][x3 + y3 * (width + 1)] = (tmp_QPEL_FILTER_2_V_16 + 524288) >> 6;
					x3 = x3 + 1;
				}
				y3 = y3 + 1;
			}
		} else {
			if (my == 3) {
				y4 = 0;
				while (y4 <= height) {
					x4 = 0;
					while (x4 <= width) {
						tmp_QPEL_FILTER_3_V_16 = HevcDecoder_InterPrediction_QPEL_FILTER_3_V_16(intermSamples, predCuSize, x4, y4 + 3);
						predSamples[listIdx][x4 + y4 * (width + 1)] = (tmp_QPEL_FILTER_3_V_16 + 524288) >> 6;
						x4 = x4 + 1;
					}
					y4 = y4 + 1;
				}
			}
		}
	}
}
static i16 HevcDecoder_InterPrediction_QPEL_FILTER_3_V(u8 src[5041], u8 srcStride, u8 x, u8 y) {
	u8 tmp_src;
	u8 tmp_src0;
	u8 tmp_src1;
	u8 tmp_src2;
	u8 tmp_src3;
	u8 tmp_src4;
	u8 tmp_src5;

	tmp_src = src[x + (y - 2) * srcStride];
	tmp_src0 = src[x + (y - 1) * srcStride];
	tmp_src1 = src[x + y * srcStride];
	tmp_src2 = src[x + (y + 1) * srcStride];
	tmp_src3 = src[x + (y + 2) * srcStride];
	tmp_src4 = src[x + (y + 3) * srcStride];
	tmp_src5 = src[x + (y + 4) * srcStride];
	return tmp_src - 5 * tmp_src0 + 17 * tmp_src1 + 58 * tmp_src2 - 10 * tmp_src3 + 4 * tmp_src4 - tmp_src5;
}
static i16 HevcDecoder_InterPrediction_QPEL_FILTER_2_V(u8 src[5041], u8 srcStride, u8 x, u8 y) {
	u8 tmp_src;
	u8 tmp_src0;
	u8 tmp_src1;
	u8 tmp_src2;
	u8 tmp_src3;
	u8 tmp_src4;
	u8 tmp_src5;
	u8 tmp_src6;

	tmp_src = src[x + (y - 3) * srcStride];
	tmp_src0 = src[x + (y - 2) * srcStride];
	tmp_src1 = src[x + (y - 1) * srcStride];
	tmp_src2 = src[x + y * srcStride];
	tmp_src3 = src[x + (y + 1) * srcStride];
	tmp_src4 = src[x + (y + 2) * srcStride];
	tmp_src5 = src[x + (y + 3) * srcStride];
	tmp_src6 = src[x + (y + 4) * srcStride];
	return -tmp_src + 4 * tmp_src0 - 11 * tmp_src1 + 40 * tmp_src2 + 40 * tmp_src3 - 11 * tmp_src4 + 4 * tmp_src5 - tmp_src6;
}
static i16 HevcDecoder_InterPrediction_QPEL_FILTER_1_V(u8 src[5041], u8 srcStride, u8 x, u8 y) {
	u8 tmp_src;
	u8 tmp_src0;
	u8 tmp_src1;
	u8 tmp_src2;
	u8 tmp_src3;
	u8 tmp_src4;
	u8 tmp_src5;

	tmp_src = src[x + (y - 3) * srcStride];
	tmp_src0 = src[x + (y - 2) * srcStride];
	tmp_src1 = src[x + (y - 1) * srcStride];
	tmp_src2 = src[x + y * srcStride];
	tmp_src3 = src[x + (y + 1) * srcStride];
	tmp_src4 = src[x + (y + 2) * srcStride];
	tmp_src5 = src[x + (y + 3) * srcStride];
	return -tmp_src + 4 * tmp_src0 - 10 * tmp_src1 + 58 * tmp_src2 + 17 * tmp_src3 - 5 * tmp_src4 + 1 * tmp_src5;
}
static void HevcDecoder_InterPrediction_put_hevc_qpel_v_cal(i16 predSamples[2][4096], u8 listIdx, u8 refSamples[5041], u8 predCuSize, u8 width, u8 height, i32 my) {
	i32 y;
	i32 x;
	i16 tmp_QPEL_FILTER_1_V;
	i32 y0;
	i32 x0;
	i16 tmp_QPEL_FILTER_2_V;
	i32 y1;
	i32 x1;
	i16 tmp_QPEL_FILTER_3_V;

	if (my == 1) {
		y = 0;
		while (y <= height) {
			x = 0;
			while (x <= width) {
				tmp_QPEL_FILTER_1_V = HevcDecoder_InterPrediction_QPEL_FILTER_1_V(refSamples, predCuSize, x + 3, y + 3);
				predSamples[listIdx][x + y * (width + 1)] = tmp_QPEL_FILTER_1_V;
				x = x + 1;
			}
			y = y + 1;
		}
	} else {
		if (my == 2) {
			y0 = 0;
			while (y0 <= height) {
				x0 = 0;
				while (x0 <= width) {
					tmp_QPEL_FILTER_2_V = HevcDecoder_InterPrediction_QPEL_FILTER_2_V(refSamples, predCuSize, x0 + 3, y0 + 3);
					predSamples[listIdx][x0 + y0 * (width + 1)] = tmp_QPEL_FILTER_2_V;
					x0 = x0 + 1;
				}
				y0 = y0 + 1;
			}
		} else {
			if (my == 3) {
				y1 = 0;
				while (y1 <= height) {
					x1 = 0;
					while (x1 <= width) {
						tmp_QPEL_FILTER_3_V = HevcDecoder_InterPrediction_QPEL_FILTER_3_V(refSamples, predCuSize, x1 + 3, y1 + 3);
						predSamples[listIdx][x1 + y1 * (width + 1)] = tmp_QPEL_FILTER_3_V;
						x1 = x1 + 1;
					}
					y1 = y1 + 1;
				}
			}
		}
	}
}
static void HevcDecoder_InterPrediction_put_hevc_qpel_h_cal(i16 predSamples[2][4096], u8 listIdx, u8 refSamples[5041], u8 predCuSize, u8 width, u8 height, i32 mx) {
	i32 y;
	i32 x;
	i16 tmp_QPEL_FILTER_1_H;
	i32 y0;
	i32 x0;
	i16 tmp_QPEL_FILTER_2_H;
	i32 y1;
	i32 x1;
	i16 tmp_QPEL_FILTER_3_H;

	if (mx == 1) {
		y = 0;
		while (y <= height) {
			x = 0;
			while (x <= width) {
				tmp_QPEL_FILTER_1_H = HevcDecoder_InterPrediction_QPEL_FILTER_1_H(refSamples, predCuSize, x + 3, y + 3);
				predSamples[listIdx][x + y * (width + 1)] = tmp_QPEL_FILTER_1_H;
				x = x + 1;
			}
			y = y + 1;
		}
	} else {
		if (mx == 2) {
			y0 = 0;
			while (y0 <= height) {
				x0 = 0;
				while (x0 <= width) {
					tmp_QPEL_FILTER_2_H = HevcDecoder_InterPrediction_QPEL_FILTER_2_H(refSamples, predCuSize, x0 + 3, y0 + 3);
					predSamples[listIdx][x0 + y0 * (width + 1)] = tmp_QPEL_FILTER_2_H;
					x0 = x0 + 1;
				}
				y0 = y0 + 1;
			}
		} else {
			if (mx == 3) {
				y1 = 0;
				while (y1 <= height) {
					x1 = 0;
					while (x1 <= width) {
						tmp_QPEL_FILTER_3_H = HevcDecoder_InterPrediction_QPEL_FILTER_3_H(refSamples, predCuSize, x1 + 3, y1 + 3);
						predSamples[listIdx][x1 + y1 * (width + 1)] = tmp_QPEL_FILTER_3_H;
						x1 = x1 + 1;
					}
					y1 = y1 + 1;
				}
			}
		}
	}
}
static void HevcDecoder_InterPrediction_put_hevc_qpel_pixel_cal(i16 predSamples[2][4096], u8 listIdx, u8 refSamples[5041], u8 predCuSize, u8 width, u8 height) {
	u32 srcStride;
	u32 dstStride;
	i32 y;
	i32 x;
	u8 tmp_refSamples;
	i32 local_shift1;

	srcStride = 3 * predCuSize;
	dstStride = 0;
	y = 0;
	while (y <= height) {
		x = 0;
		while (x <= width) {
			tmp_refSamples = refSamples[x + 3 + srcStride];
			local_shift1 = HevcDecoder_InterPrediction_shift1;
			predSamples[listIdx][x + dstStride] = tmp_refSamples << local_shift1;
			x = x + 1;
		}
		dstStride = dstStride + width + 1;
		srcStride = srcStride + predCuSize;
		y = y + 1;
	}
}
static void HevcDecoder_InterPrediction_put_hevc_qpel_cal(i16 predSamples[2][4096], u8 listIdx, u8 refSamples[5041], u8 predCuSize, u8 width, u8 height, i32 mx, i32 my) {
	#if defined(OPENHEVC_ENABLE)
	put_hevc_qpel_orcc(predSamples, listIdx, refSamples, predCuSize, width, height, mx, my);
	#else

	if (mx == 0 && my == 0) {
		HevcDecoder_InterPrediction_put_hevc_qpel_pixel_cal(predSamples, listIdx, refSamples, predCuSize, width, height);
	} else {
		if (my == 0) {
			HevcDecoder_InterPrediction_put_hevc_qpel_h_cal(predSamples, listIdx, refSamples, predCuSize, width, height, mx);
		} else {
			if (mx == 0) {
				HevcDecoder_InterPrediction_put_hevc_qpel_v_cal(predSamples, listIdx, refSamples, predCuSize, width, height, my);
			} else {
				HevcDecoder_InterPrediction_put_hevc_qpel_hv_cal(predSamples, listIdx, refSamples, predCuSize, width, height, mx, my);
			}
		}
	}
	#endif // defined(OPENHEVC_ENABLE)
}
static i16 HevcDecoder_InterPrediction_EPEL_FILTER_H(u8 src[5041], u8 srcStride, u8 x, u8 y, i8 filter_0, i8 filter_1, i8 filter_2, i8 filter_3) {
	u8 tmp_src;
	u8 tmp_src0;
	u8 tmp_src1;
	u8 tmp_src2;

	tmp_src = src[x - 1 + y * srcStride];
	tmp_src0 = src[x + y * srcStride];
	tmp_src1 = src[x + 1 + y * srcStride];
	tmp_src2 = src[x + 2 + y * srcStride];
	return filter_0 * tmp_src + filter_1 * tmp_src0 + filter_2 * tmp_src1 + filter_3 * tmp_src2;
}
static i32 HevcDecoder_InterPrediction_EPEL_FILTER_V_16(i16 src[5041], u8 srcStride, i16 x, i16 y, i8 filter_0, i8 filter_1, i8 filter_2, i8 filter_3) {
	i16 tmp_src;
	i16 tmp_src0;
	i16 tmp_src1;
	i16 tmp_src2;

	tmp_src = src[x + (y - 1) * srcStride];
	tmp_src0 = src[x + y * srcStride];
	tmp_src1 = src[x + (y + 1) * srcStride];
	tmp_src2 = src[x + (y + 2) * srcStride];
	return filter_0 * tmp_src + filter_1 * tmp_src0 + filter_2 * tmp_src1 + filter_3 * tmp_src2;
}
static void HevcDecoder_InterPrediction_put_hevc_epel_hv_cal(i16 predSamples[2][4096], u8 listIdx, u8 refSamples[5041], u8 predCuSize, u8 width, u8 height, i32 mx, i32 my) {
	i16 intermSamples[5041];
	i8 filter_0;
	i8 filter_1;
	i8 filter_2;
	i8 filter_3;
	i32 y;
	i32 x;
	i16 tmp_EPEL_FILTER_H;
	i32 y0;
	i32 x0;
	i32 tmp_EPEL_FILTER_V_16;

	filter_0 = HevcDecoder_InterPrediction_ff_hevc_epel_filters[mx - 1][0];
	filter_1 = HevcDecoder_InterPrediction_ff_hevc_epel_filters[mx - 1][1];
	filter_2 = HevcDecoder_InterPrediction_ff_hevc_epel_filters[mx - 1][2];
	filter_3 = HevcDecoder_InterPrediction_ff_hevc_epel_filters[mx - 1][3];
	y = 0;
	while (y <= height + 3) {
		x = 0;
		while (x <= width) {
			tmp_EPEL_FILTER_H = HevcDecoder_InterPrediction_EPEL_FILTER_H(refSamples, predCuSize, x + 1, y, filter_0, filter_1, filter_2, filter_3);
			intermSamples[x + y * predCuSize] = tmp_EPEL_FILTER_H - 8192;
			x = x + 1;
		}
		y = y + 1;
	}
	filter_0 = HevcDecoder_InterPrediction_ff_hevc_epel_filters[my - 1][0];
	filter_1 = HevcDecoder_InterPrediction_ff_hevc_epel_filters[my - 1][1];
	filter_2 = HevcDecoder_InterPrediction_ff_hevc_epel_filters[my - 1][2];
	filter_3 = HevcDecoder_InterPrediction_ff_hevc_epel_filters[my - 1][3];
	y0 = 0;
	while (y0 <= height) {
		x0 = 0;
		while (x0 <= width) {
			tmp_EPEL_FILTER_V_16 = HevcDecoder_InterPrediction_EPEL_FILTER_V_16(intermSamples, predCuSize, x0, y0 + 1, filter_0, filter_1, filter_2, filter_3);
			predSamples[listIdx][x0 + y0 * (width + 1)] = (tmp_EPEL_FILTER_V_16 + 524288) >> 6;
			x0 = x0 + 1;
		}
		y0 = y0 + 1;
	}
}
static i16 HevcDecoder_InterPrediction_EPEL_FILTER_V(u8 src[5041], u8 srcStride, i16 x, i16 y, i8 filter_0, i8 filter_1, i8 filter_2, i8 filter_3) {
	u8 tmp_src;
	u8 tmp_src0;
	u8 tmp_src1;
	u8 tmp_src2;

	tmp_src = src[x + (y - 1) * srcStride];
	tmp_src0 = src[x + y * srcStride];
	tmp_src1 = src[x + (y + 1) * srcStride];
	tmp_src2 = src[x + (y + 2) * srcStride];
	return filter_0 * tmp_src + filter_1 * tmp_src0 + filter_2 * tmp_src1 + filter_3 * tmp_src2;
}
static void HevcDecoder_InterPrediction_put_hevc_epel_v_cal(i16 predSamples[2][4096], u8 listIdx, u8 refSamples[5041], u8 predCuSize, u8 width, u8 height, i32 my) {
	i8 filter_0;
	i8 filter_1;
	i8 filter_2;
	i8 filter_3;
	i32 y;
	i32 x;
	i16 tmp_EPEL_FILTER_V;

	filter_0 = HevcDecoder_InterPrediction_ff_hevc_epel_filters[my - 1][0];
	filter_1 = HevcDecoder_InterPrediction_ff_hevc_epel_filters[my - 1][1];
	filter_2 = HevcDecoder_InterPrediction_ff_hevc_epel_filters[my - 1][2];
	filter_3 = HevcDecoder_InterPrediction_ff_hevc_epel_filters[my - 1][3];
	y = 0;
	while (y <= height) {
		x = 0;
		while (x <= width) {
			tmp_EPEL_FILTER_V = HevcDecoder_InterPrediction_EPEL_FILTER_V(refSamples, predCuSize, x + 1, y + 1, filter_0, filter_1, filter_2, filter_3);
			predSamples[listIdx][x + y * (width + 1)] = tmp_EPEL_FILTER_V;
			x = x + 1;
		}
		y = y + 1;
	}
}
static void HevcDecoder_InterPrediction_put_hevc_epel_h_cal(i16 predSamples[2][4096], u8 listIdx, u8 refSamples[5041], u8 predCuSize, u8 width, u8 height, i32 mx) {
	i8 filter_0;
	i8 filter_1;
	i8 filter_2;
	i8 filter_3;
	i32 y;
	i32 x;
	i16 tmp_EPEL_FILTER_H;

	filter_0 = HevcDecoder_InterPrediction_ff_hevc_epel_filters[mx - 1][0];
	filter_1 = HevcDecoder_InterPrediction_ff_hevc_epel_filters[mx - 1][1];
	filter_2 = HevcDecoder_InterPrediction_ff_hevc_epel_filters[mx - 1][2];
	filter_3 = HevcDecoder_InterPrediction_ff_hevc_epel_filters[mx - 1][3];
	y = 0;
	while (y <= height) {
		x = 0;
		while (x <= width) {
			tmp_EPEL_FILTER_H = HevcDecoder_InterPrediction_EPEL_FILTER_H(refSamples, predCuSize, x + 1, y + 1, filter_0, filter_1, filter_2, filter_3);
			predSamples[listIdx][x + y * (width + 1)] = tmp_EPEL_FILTER_H;
			x = x + 1;
		}
		y = y + 1;
	}
}
static void HevcDecoder_InterPrediction_put_hevc_epel_pixel_cal(i16 predSamples[2][4096], u8 listIdx, u8 refSamples[5041], u8 predCuSize, u8 width, u8 height) {
	i32 y;
	i32 x;
	u8 tmp_refSamples;
	i32 local_shift1;

	y = 0;
	while (y <= height) {
		x = 0;
		while (x <= width) {
			tmp_refSamples = refSamples[x + 1 + (y + 1) * predCuSize];
			local_shift1 = HevcDecoder_InterPrediction_shift1;
			predSamples[listIdx][x + y * (width + 1)] = tmp_refSamples << local_shift1;
			x = x + 1;
		}
		y = y + 1;
	}
}
static void HevcDecoder_InterPrediction_put_hevc_epel_cal(i16 predSamples[2][4096], u8 listIdx, u8 refSamples[5041], u8 predCuSize, u8 width, u8 height, i32 mx, i32 my) {
	#if defined(OPENHEVC_ENABLE)
	put_hevc_epel_orcc(predSamples, listIdx, refSamples, predCuSize, width, height, mx, my);
	#else

	if (mx == 0 && my == 0) {
		HevcDecoder_InterPrediction_put_hevc_epel_pixel_cal(predSamples, listIdx, refSamples, predCuSize, width, height);
	} else {
		if (my == 0) {
			HevcDecoder_InterPrediction_put_hevc_epel_h_cal(predSamples, listIdx, refSamples, predCuSize, width, height, mx);
		} else {
			if (mx == 0) {
				HevcDecoder_InterPrediction_put_hevc_epel_v_cal(predSamples, listIdx, refSamples, predCuSize, width, height, my);
			} else {
				HevcDecoder_InterPrediction_put_hevc_epel_hv_cal(predSamples, listIdx, refSamples, predCuSize, width, height, mx, my);
			}
		}
	}
	#endif // defined(OPENHEVC_ENABLE)
}
static void HevcDecoder_InterPrediction_put_unweighted_pred(i16 src[2][4096], i32 width, i32 height, u8 rdList, u8 dst[4096]) {
	#if defined(OPENHEVC_ENABLE)
	put_unweighted_pred_orcc(src, width, height, rdList, dst);
	#else
	i32 y;
	i32 x;
	i16 tmp_src;
	i32 local_shift1;
	i16 tmp_src0;
	u16 local_maxPixVal;
	i32 tmp_clip_i32;

	y = 0;
	while (y <= height) {
		x = 0;
		while (x <= width) {
			tmp_src = src[rdList][x + y * (width + 1)];
			local_shift1 = HevcDecoder_InterPrediction_shift1;
			local_shift1 = HevcDecoder_InterPrediction_shift1;
			src[0][x + y * (width + 1)] = (tmp_src + (1 << (local_shift1 - 1))) >> local_shift1;
			tmp_src0 = src[0][x + y * (width + 1)];
			local_maxPixVal = HevcDecoder_InterPrediction_maxPixVal;
			tmp_clip_i32 = HevcDecoder_InterPrediction_clip_i32(tmp_src0, 0, local_maxPixVal);
			dst[x + y * (width + 1)] = tmp_clip_i32;
			x = x + 1;
		}
		y = y + 1;
	}
	#endif // defined(OPENHEVC_ENABLE)
}
static void HevcDecoder_InterPrediction_weighted_pred(i32 logWD, i32 weightCu[2], i32 offsetCu[2], i16 src[2][4096], i32 width, i32 height, u8 rdList, u8 dst[4096]) {
	#if defined(OPENHEVC_ENABLE)
	weighted_pred_orcc(logWD, weightCu, offsetCu, src, width, height, rdList, dst);
	#else
	i32 locLogWD;
	i32 wX;
	i32 oX;
	i32 y;
	i32 x;
	i16 tmp_src;
	i16 tmp_src0;
	i16 tmp_src1;
	u16 local_maxPixVal;
	i32 tmp_clip_i32;

	locLogWD = logWD;
	wX = weightCu[rdList];
	oX = offsetCu[rdList];
	y = 0;
	while (y <= height) {
		x = 0;
		while (x <= width) {
			if (locLogWD >= 1) {
				tmp_src = src[rdList][x + y * (width + 1)];
				src[0][x + y * (width + 1)] = ((tmp_src * wX + (1 << (locLogWD - 1))) >> locLogWD) + oX;
			} else {
				tmp_src0 = src[rdList][x + y * (width + 1)];
				src[0][x + y * (width + 1)] = tmp_src0 * wX + oX;
			}
			tmp_src1 = src[0][x + y * (width + 1)];
			local_maxPixVal = HevcDecoder_InterPrediction_maxPixVal;
			tmp_clip_i32 = HevcDecoder_InterPrediction_clip_i32(tmp_src1, 0, local_maxPixVal);
			dst[x + y * (width + 1)] = tmp_clip_i32;
			x = x + 1;
		}
		y = y + 1;
	}
	#endif // defined(OPENHEVC_ENABLE)
}
static void HevcDecoder_InterPrediction_weighted_pred_mono(i32 logWD, i32 weightCu[2], i32 offsetCu[2], i16 src[2][4096], i32 width, i32 height, u8 dst[4096]) {
	#if defined(SSE_ENABLE) && HAVE_SSE4
	weighted_pred_mono_orcc(logWD, weightCu, offsetCu, src, width, height, dst);
	#else
	i32 locLogWD;
	i32 tmp_weightCu;
	i32 tmp_weightCu0;
	i32 wX;
	i32 tmp_offsetCu;
	i32 tmp_offsetCu0;
	i32 oX;
	i32 y;
	i32 x;
	i16 tmp_src;
	i16 tmp_src0;
	u16 local_maxPixVal;
	i32 tmp_clip_i32;

	locLogWD = logWD + 1;
	tmp_weightCu = weightCu[0];
	tmp_weightCu0 = weightCu[1];
	wX = tmp_weightCu + tmp_weightCu0;
	tmp_offsetCu = offsetCu[0];
	tmp_offsetCu0 = offsetCu[1];
	oX = tmp_offsetCu + tmp_offsetCu0 + 1;
	y = 0;
	while (y <= height) {
		x = 0;
		while (x <= width) {
			tmp_src = src[0][x + y * (width + 1)];
			src[0][x + y * (width + 1)] = (tmp_src * wX + (oX << (locLogWD - 1))) >> locLogWD;
			tmp_src0 = src[0][x + y * (width + 1)];
			local_maxPixVal = HevcDecoder_InterPrediction_maxPixVal;
			tmp_clip_i32 = HevcDecoder_InterPrediction_clip_i32(tmp_src0, 0, local_maxPixVal);
			dst[x + y * (width + 1)] = tmp_clip_i32;
			x = x + 1;
		}
		y = y + 1;
	}
	#endif // defined(SSE_ENABLE) && HAVE_SSE4
}
static void HevcDecoder_InterPrediction_put_weighted_pred_avg(i16 src[2][4096], i32 width, i32 height, u8 dst[4096]) {
	#if defined(OPENHEVC_ENABLE)
	put_weighted_pred_avg_orcc(src, width, height, dst);
	#else
	i32 y;
	i32 x;
	i16 tmp_src;
	i16 tmp_src0;
	i16 tmp_src1;
	u16 local_maxPixVal;
	i32 tmp_clip_i32;

	y = 0;
	while (y <= height) {
		x = 0;
		while (x <= width) {
			tmp_src = src[0][x + y * (width + 1)];
			tmp_src0 = src[1][x + y * (width + 1)];
			src[0][x + y * (width + 1)] = (tmp_src + tmp_src0 + 64) >> 7;
			tmp_src1 = src[0][x + y * (width + 1)];
			local_maxPixVal = HevcDecoder_InterPrediction_maxPixVal;
			tmp_clip_i32 = HevcDecoder_InterPrediction_clip_i32(tmp_src1, 0, local_maxPixVal);
			dst[x + y * (width + 1)] = tmp_clip_i32;
			x = x + 1;
		}
		y = y + 1;
	}
	#endif // defined(OPENHEVC_ENABLE)
}
static void HevcDecoder_InterPrediction_weighted_pred_avg(i32 logWD, i32 weightCu[2], i32 offsetCu[2], i16 src[2][4096], i32 width, i32 height, u8 dst[4096]) {
	#if defined(OPENHEVC_ENABLE)
	weighted_pred_avg_orcc(logWD, weightCu, offsetCu, src, width, height, dst);
	#else
	i32 locLogWD;
	i32 w0;
	i32 w1;
	i32 o0;
	i32 o1;
	i32 y;
	i32 x;
	i16 tmp_src;
	i16 tmp_src0;
	i16 tmp_src1;
	u16 local_maxPixVal;
	i32 tmp_clip_i32;

	locLogWD = logWD;
	w0 = weightCu[0];
	w1 = weightCu[1];
	o0 = offsetCu[0];
	o1 = offsetCu[1];
	y = 0;
	while (y <= height) {
		x = 0;
		while (x <= width) {
			tmp_src = src[0][x + y * (width + 1)];
			tmp_src0 = src[1][x + y * (width + 1)];
			src[0][x + y * (width + 1)] = (tmp_src * w0 + tmp_src0 * w1 + ((o0 + o1 + 1) << locLogWD)) >> (locLogWD + 1);
			tmp_src1 = src[0][x + y * (width + 1)];
			local_maxPixVal = HevcDecoder_InterPrediction_maxPixVal;
			tmp_clip_i32 = HevcDecoder_InterPrediction_clip_i32(tmp_src1, 0, local_maxPixVal);
			dst[x + y * (width + 1)] = tmp_clip_i32;
			x = x + 1;
		}
		y = y + 1;
	}
	#endif // defined(OPENHEVC_ENABLE)
}
static void computeWeights(i32 refIdxL0, i32 refIdxL1) {
	i16 pocL0;
	i16 pocL1;
	i32 tb;
	i32 td;
	i32 tx;
	i32 weightScalFact;
	i32 w0;
	i32 w1;
	u8 idxL0;
	u8 idxL1;
	u8 local_wpIdc;
	i16 local_currPoc;
	i32 tmp_abs;
	i32 component;
	i32 local_shift1;
	i32 component0;
	i32 component1;
	u8 tmp_log2WeightDenom;
	i32 tmp_weight;
	i32 tmp_offset;
	i32 tmp_weight0;
	i32 tmp_offset0;

	idxL0 = refIdxL0 + 1;
	idxL1 = refIdxL1 + 1;
	local_wpIdc = wpIdc;
	if (local_wpIdc == 2) {
		if (refIdxL0 >= 0 && refIdxL1 >= 0) {
			if (refIdxL0 >= 0) {
				pocL0 = refListX[0][refIdxL0];
			}
			if (refIdxL1 >= 0) {
				pocL1 = refListX[1][refIdxL1];
			}
			local_currPoc = currPoc;
			tb = HevcDecoder_InterPrediction_clip_i32(local_currPoc - pocL0, -128, 127);
			td = HevcDecoder_InterPrediction_clip_i32(pocL1 - pocL0, -128, 127);
			if (td != 0) {
				tmp_abs = HevcDecoder_InterPrediction_abs(td);
				tx = (16384 + (tmp_abs >> 1)) / td;
				weightScalFact = HevcDecoder_InterPrediction_clip_i32((tb * tx + 32) >> 6, -1024, 1023);
			}
			if (pocL0 == pocL1 || weightScalFact >> 2 < -64 || weightScalFact >> 2 > 128) {
				w0 = 32;
				w1 = 32;
			} else {
				w0 = 64 - (weightScalFact >> 2);
				w1 = weightScalFact >> 2;
			}
			component = 0;
			while (component <= 2) {
				local_shift1 = HevcDecoder_InterPrediction_shift1;
				logWDTab[idxL0][idxL1][component] = 5 + local_shift1;
				offsetCuTab[idxL0][idxL1][component][0] = 0;
				offsetCuTab[idxL0][idxL1][component][1] = 0;
				weightCuTab[idxL0][idxL1][component][0] = w0;
				weightCuTab[idxL0][idxL1][component][1] = w1;
				component = component + 1;
			}
		} else {
			component0 = 0;
			while (component0 <= 2) {
				local_shift1 = HevcDecoder_InterPrediction_shift1;
				logWDTab[idxL0][idxL1][component0] = local_shift1;
				offsetCuTab[idxL0][idxL1][component0][0] = 0;
				offsetCuTab[idxL0][idxL1][component0][1] = 0;
				weightCuTab[idxL0][idxL1][component0][0] = 1;
				weightCuTab[idxL0][idxL1][component0][1] = 1;
				component0 = component0 + 1;
			}
		}
	} else {
		local_wpIdc = wpIdc;
		if (local_wpIdc == 1) {
			component1 = 0;
			while (component1 <= 2) {
				tmp_log2WeightDenom = log2WeightDenom[component1];
				local_shift1 = HevcDecoder_InterPrediction_shift1;
				logWDTab[idxL0][idxL1][component1] = tmp_log2WeightDenom + local_shift1;
				if (refIdxL0 >= 0) {
					tmp_weight = weight[refIdxL0][0][component1];
					weightCuTab[idxL0][idxL1][component1][0] = tmp_weight;
					tmp_offset = offset[refIdxL0][0][component1];
					offsetCuTab[idxL0][idxL1][component1][0] = tmp_offset;
				}
				if (refIdxL1 >= 0) {
					tmp_weight0 = weight[refIdxL1][1][component1];
					weightCuTab[idxL0][idxL1][component1][1] = tmp_weight0;
					tmp_offset0 = offset[refIdxL1][1][component1];
					offsetCuTab[idxL0][idxL1][component1][1] = tmp_offset0;
				}
				component1 = component1 + 1;
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
// Actions
static i32 isSchedulable_isNewSlice_notDep() {
	i32 result;

	result = 1;
	return result;
}

static void isNewSlice_notDep() {

	u8 partMode;
	i16 poc;
	u8 sliceType;
	i16 weightPredIdc;
	u8 local_B_SLICE;

	partMode = tokens_PartMode[(index_PartMode + (0)) % SIZE_PartMode];
	poc = tokens_Poc[(index_Poc + (0)) % SIZE_Poc];
	sliceType = tokens_SliceType[(index_SliceType + (0)) % SIZE_SliceType];
	weightPredIdc = tokens_WeightedPredSe[(index_WeightedPredSe + (0)) % SIZE_WeightedPredSe];
	local_B_SLICE = HevcDecoder_InterPrediction_B_SLICE;
	isBSlice = sliceType == local_B_SLICE;
	currPoc = poc;
	wpIdc = weightPredIdc;
	listIdx = 0;

	// Update ports indexes
	index_PartMode += 1;
	index_Poc += 1;
	index_SliceType += 1;
	index_WeightedPredSe += 1;

	rate_PartMode += 1;
	rate_Poc += 1;
	rate_SliceType += 1;
	rate_WeightedPredSe += 1;
}
static i32 isSchedulable_isNewSlice_dep() {
	i32 result;
	u8 partMode;
	u8 local_PART_MODE_SLICE_DEP;

	partMode = tokens_PartMode[(index_PartMode + (0)) % SIZE_PartMode];
	local_PART_MODE_SLICE_DEP = HevcDecoder_InterPrediction_PART_MODE_SLICE_DEP;
	result = partMode == local_PART_MODE_SLICE_DEP;
	return result;
}

static void isNewSlice_dep() {

	u8 partMode;

	partMode = tokens_PartMode[(index_PartMode + (0)) % SIZE_PartMode];

	// Update ports indexes
	index_PartMode += 1;

	rate_PartMode += 1;
}
static i32 isSchedulable_getPartMode() {
	i32 result;
	u8 partMode;
	u8 local_PART_MODE_SLICE_DEP;
	u8 local_PART_MODE_SLICE_INDEP;
	u8 local_PART_MODE_PICT;

	partMode = tokens_PartMode[(index_PartMode + (0)) % SIZE_PartMode];
	local_PART_MODE_SLICE_DEP = HevcDecoder_InterPrediction_PART_MODE_SLICE_DEP;
	local_PART_MODE_SLICE_INDEP = HevcDecoder_InterPrediction_PART_MODE_SLICE_INDEP;
	local_PART_MODE_PICT = HevcDecoder_InterPrediction_PART_MODE_PICT;
	result = partMode != local_PART_MODE_SLICE_DEP && partMode != local_PART_MODE_SLICE_INDEP && partMode != local_PART_MODE_PICT;
	return result;
}

static void getPartMode() {

	u8 partMode;
	u8 tmp_partModeToNumPart;

	partMode = tokens_PartMode[(index_PartMode + (0)) % SIZE_PartMode];
	tmp_partModeToNumPart = HevcDecoder_InterPrediction_partModeToNumPart[partMode];
	numPart = tmp_partModeToNumPart;
	numPartDecoded = 0;

	// Update ports indexes
	index_PartMode += 1;

	rate_PartMode += 1;
}
static i32 isSchedulable_getSizeRefList_launch() {
	i32 result;
	u8 local_listIdx;

	local_listIdx = listIdx;
	result = local_listIdx < 2;
	return result;
}

static void getSizeRefList_launch() {

	i16 sizeList;
	u8 local_listIdx;

	sizeList = tokens_RefList[(index_RefList + (0)) % SIZE_RefList];
	local_listIdx = listIdx;
	numRefIdxLxAct[local_listIdx] = sizeList;
	iLoop = 0;

	// Update ports indexes
	index_RefList += 1;

	rate_RefList += 1;
}
static i32 isSchedulable_getSizeRefList_done() {
	i32 result;
	u8 local_listIdx;

	local_listIdx = listIdx;
	result = local_listIdx == 2;
	return result;
}

static void getSizeRefList_done() {



	// Update ports indexes

}
static i32 isSchedulable_getRefList_launch() {
	i32 result;
	u8 local_iLoop;
	u8 local_listIdx;
	u8 tmp_numRefIdxLxAct;

	local_iLoop = iLoop;
	local_listIdx = listIdx;
	tmp_numRefIdxLxAct = numRefIdxLxAct[local_listIdx];
	result = local_iLoop < tmp_numRefIdxLxAct;
	return result;
}

static void getRefList_launch() {

	i16 refPoc;
	u8 local_listIdx;
	u8 local_iLoop;

	refPoc = tokens_RefList[(index_RefList + (0)) % SIZE_RefList];
	local_listIdx = listIdx;
	local_iLoop = iLoop;
	refListX[local_listIdx][local_iLoop] = refPoc;
	local_iLoop = iLoop;
	iLoop = local_iLoop + 1;

	// Update ports indexes
	index_RefList += 1;

	rate_RefList += 1;
}
static i32 isSchedulable_getRefList_done() {
	i32 result;
	u8 local_iLoop;
	u8 local_listIdx;
	u8 tmp_numRefIdxLxAct;

	local_iLoop = iLoop;
	local_listIdx = listIdx;
	tmp_numRefIdxLxAct = numRefIdxLxAct[local_listIdx];
	result = local_iLoop == tmp_numRefIdxLxAct;
	return result;
}

static void getRefList_done() {

	u8 local_listIdx;

	local_listIdx = listIdx;
	listIdx = local_listIdx + 1;

	// Update ports indexes

}
static i32 isSchedulable_getWeightDenom_launch() {
	i32 result;
	u8 local_wpIdc;

	local_wpIdc = wpIdc;
	result = local_wpIdc == 1;
	return result;
}

static void getWeightDenom_launch() {

	i16 tmp_WeightedPredSe;
	i16 tmp_WeightedPredSe0;
	i16 tmp_WeightedPredSe1;
	i16 tmp_WeightedPredSe2;
	i16 tmp_WeightedPredSe3;

	listIdx = 0;
	tmp_WeightedPredSe = tokens_WeightedPredSe[(index_WeightedPredSe + (0)) % SIZE_WeightedPredSe];
	log2WeightDenom[0] = tmp_WeightedPredSe;
	tmp_WeightedPredSe0 = tokens_WeightedPredSe[(index_WeightedPredSe + (0)) % SIZE_WeightedPredSe];
	tmp_WeightedPredSe1 = tokens_WeightedPredSe[(index_WeightedPredSe + (1)) % SIZE_WeightedPredSe];
	log2WeightDenom[1] = tmp_WeightedPredSe0 + tmp_WeightedPredSe1;
	tmp_WeightedPredSe2 = tokens_WeightedPredSe[(index_WeightedPredSe + (0)) % SIZE_WeightedPredSe];
	tmp_WeightedPredSe3 = tokens_WeightedPredSe[(index_WeightedPredSe + (1)) % SIZE_WeightedPredSe];
	log2WeightDenom[2] = tmp_WeightedPredSe2 + tmp_WeightedPredSe3;

	// Update ports indexes
	index_WeightedPredSe += 2;
	read_end_WeightedPredSe();

	rate_WeightedPredSe += 2;
}
static void getWeightDenom_launch_aligned() {

	i16 tmp_WeightedPredSe;
	i16 tmp_WeightedPredSe0;
	i16 tmp_WeightedPredSe1;
	i16 tmp_WeightedPredSe2;
	i16 tmp_WeightedPredSe3;

	listIdx = 0;
	tmp_WeightedPredSe = tokens_WeightedPredSe[(index_WeightedPredSe % SIZE_WeightedPredSe) + (0)];
	log2WeightDenom[0] = tmp_WeightedPredSe;
	tmp_WeightedPredSe0 = tokens_WeightedPredSe[(index_WeightedPredSe % SIZE_WeightedPredSe) + (0)];
	tmp_WeightedPredSe1 = tokens_WeightedPredSe[(index_WeightedPredSe % SIZE_WeightedPredSe) + (1)];
	log2WeightDenom[1] = tmp_WeightedPredSe0 + tmp_WeightedPredSe1;
	tmp_WeightedPredSe2 = tokens_WeightedPredSe[(index_WeightedPredSe % SIZE_WeightedPredSe) + (0)];
	tmp_WeightedPredSe3 = tokens_WeightedPredSe[(index_WeightedPredSe % SIZE_WeightedPredSe) + (1)];
	log2WeightDenom[2] = tmp_WeightedPredSe2 + tmp_WeightedPredSe3;

	// Update ports indexes
	index_WeightedPredSe += 2;
	read_end_WeightedPredSe();

	rate_WeightedPredSe += 2;
}
static i32 isSchedulable_getWeightDenom_skip() {
	i32 result;
	u8 local_wpIdc;

	local_wpIdc = wpIdc;
	result = local_wpIdc != 1;
	return result;
}

static void getWeightDenom_skip() {

	u8 local_wpIdc;
	i32 idxL0;
	u8 tmp_numRefIdxLxAct;
	i32 idxL1;
	u8 tmp_numRefIdxLxAct0;

	local_wpIdc = wpIdc;
	if (local_wpIdc == 2) {
		idxL0 = -1;
		tmp_numRefIdxLxAct = numRefIdxLxAct[0];
		while (idxL0 <= tmp_numRefIdxLxAct - 1) {
			idxL1 = -1;
			tmp_numRefIdxLxAct0 = numRefIdxLxAct[1];
			while (idxL1 <= tmp_numRefIdxLxAct0 - 1) {
				computeWeights(idxL0, idxL1);
				idxL1 = idxL1 + 1;
			}
			idxL0 = idxL0 + 1;
		}
	}

	// Update ports indexes

}
static i32 isSchedulable_getWeightLX_launch() {
	i32 result;
	u8 local_listIdx;
	i32 local_isBSlice;

	local_listIdx = listIdx;
	local_listIdx = listIdx;
	local_isBSlice = isBSlice;
	result = local_listIdx == 0 || local_listIdx == 1 && local_isBSlice;
	return result;
}

static void getWeightLX_launch() {

	u8 local_listIdx;
	u8 tmp_numRefIdxLxAct;
	u8 tmp_numRefIdxLxAct0;

	iLoop = 0;
	local_listIdx = listIdx;
	if (local_listIdx == 0) {
		tmp_numRefIdxLxAct = numRefIdxLxAct[0];
		refIdxLxAct = tmp_numRefIdxLxAct;
	} else {
		tmp_numRefIdxLxAct0 = numRefIdxLxAct[1];
		refIdxLxAct = tmp_numRefIdxLxAct0;
	}

	// Update ports indexes

}
static i32 isSchedulable_getWeightLX_skip() {
	i32 result;
	u8 local_listIdx;

	local_listIdx = listIdx;
	result = local_listIdx != 2;
	return result;
}

static void getWeightLX_skip() {

	u8 local_listIdx;

	local_listIdx = listIdx;
	listIdx = local_listIdx + 1;

	// Update ports indexes

}
static i32 isSchedulable_getWeightLX_done() {
	i32 result;
	u8 local_listIdx;

	local_listIdx = listIdx;
	result = local_listIdx == 2;
	return result;
}

static void getWeightLX_done() {

	i32 idxL0;
	u8 tmp_numRefIdxLxAct;
	i32 idxL1;
	u8 tmp_numRefIdxLxAct0;

	idxL0 = -1;
	tmp_numRefIdxLxAct = numRefIdxLxAct[0];
	while (idxL0 <= tmp_numRefIdxLxAct - 1) {
		idxL1 = -1;
		tmp_numRefIdxLxAct0 = numRefIdxLxAct[1];
		while (idxL1 <= tmp_numRefIdxLxAct0 - 1) {
			computeWeights(idxL0, idxL1);
			idxL1 = idxL1 + 1;
		}
		idxL0 = idxL0 + 1;
	}

	// Update ports indexes

}
static i32 isSchedulable_getLumaWeightLX_launch() {
	i32 result;
	u8 local_iLoop;
	u8 local_refIdxLxAct;

	local_iLoop = iLoop;
	local_refIdxLxAct = refIdxLxAct;
	result = local_iLoop < local_refIdxLxAct;
	return result;
}

static void getLumaWeightLX_launch() {

	i16 lumWeightFlag;
	u8 local_iLoop;
	u8 local_listIdx;

	lumWeightFlag = tokens_WeightedPredSe[(index_WeightedPredSe + (0)) % SIZE_WeightedPredSe];
	local_iLoop = iLoop;
	local_listIdx = listIdx;
	weight[local_iLoop][local_listIdx][0] = lumWeightFlag;
	local_iLoop = iLoop;
	iLoop = local_iLoop + 1;

	// Update ports indexes
	index_WeightedPredSe += 1;

	rate_WeightedPredSe += 1;
}
static i32 isSchedulable_getLumaWeightLX_done() {
	i32 result;
	u8 local_iLoop;
	u8 local_refIdxLxAct;

	local_iLoop = iLoop;
	local_refIdxLxAct = refIdxLxAct;
	result = local_iLoop == local_refIdxLxAct;
	return result;
}

static void getLumaWeightLX_done() {


	iLoop = 0;

	// Update ports indexes

}
static i32 isSchedulable_getChromaWeightLX_launch() {
	i32 result;
	u8 local_iLoop;
	u8 local_refIdxLxAct;

	local_iLoop = iLoop;
	local_refIdxLxAct = refIdxLxAct;
	result = local_iLoop < local_refIdxLxAct;
	return result;
}

static void getChromaWeightLX_launch() {

	i16 chrWeightFlag;
	u8 local_iLoop;
	u8 local_listIdx;

	chrWeightFlag = tokens_WeightedPredSe[(index_WeightedPredSe + (0)) % SIZE_WeightedPredSe];
	local_iLoop = iLoop;
	local_listIdx = listIdx;
	weight[local_iLoop][local_listIdx][1] = chrWeightFlag;
	local_iLoop = iLoop;
	iLoop = local_iLoop + 1;

	// Update ports indexes
	index_WeightedPredSe += 1;

	rate_WeightedPredSe += 1;
}
static i32 isSchedulable_getChromaWeightLX_done() {
	i32 result;
	u8 local_iLoop;
	u8 local_refIdxLxAct;

	local_iLoop = iLoop;
	local_refIdxLxAct = refIdxLxAct;
	result = local_iLoop == local_refIdxLxAct;
	return result;
}

static void getChromaWeightLX_done() {


	iLoop = 0;

	// Update ports indexes

}
static i32 isSchedulable_getDeltaLumaWeight_launch() {
	i32 result;
	u8 local_iLoop;
	u8 local_refIdxLxAct;
	u8 local_listIdx;
	i32 tmp_weight;

	local_iLoop = iLoop;
	local_refIdxLxAct = refIdxLxAct;
	local_iLoop = iLoop;
	local_listIdx = listIdx;
	tmp_weight = weight[local_iLoop][local_listIdx][0];
	result = local_iLoop < local_refIdxLxAct && tmp_weight != 0;
	return result;
}

static void getDeltaLumaWeight_launch() {

	u8 local_iLoop;
	u8 local_listIdx;
	u8 tmp_log2WeightDenom;
	i16 tmp_WeightedPredSe;
	i16 tmp_WeightedPredSe0;

	local_iLoop = iLoop;
	local_listIdx = listIdx;
	tmp_log2WeightDenom = log2WeightDenom[0];
	tmp_WeightedPredSe = tokens_WeightedPredSe[(index_WeightedPredSe + (0)) % SIZE_WeightedPredSe];
	weight[local_iLoop][local_listIdx][0] = (1 << tmp_log2WeightDenom) + tmp_WeightedPredSe;
	local_iLoop = iLoop;
	local_listIdx = listIdx;
	tmp_WeightedPredSe0 = tokens_WeightedPredSe[(index_WeightedPredSe + (1)) % SIZE_WeightedPredSe];
	offset[local_iLoop][local_listIdx][0] = tmp_WeightedPredSe0;

	// Update ports indexes
	index_WeightedPredSe += 2;
	read_end_WeightedPredSe();

	rate_WeightedPredSe += 2;
}
static void getDeltaLumaWeight_launch_aligned() {

	u8 local_iLoop;
	u8 local_listIdx;
	u8 tmp_log2WeightDenom;
	i16 tmp_WeightedPredSe;
	i16 tmp_WeightedPredSe0;

	local_iLoop = iLoop;
	local_listIdx = listIdx;
	tmp_log2WeightDenom = log2WeightDenom[0];
	tmp_WeightedPredSe = tokens_WeightedPredSe[(index_WeightedPredSe % SIZE_WeightedPredSe) + (0)];
	weight[local_iLoop][local_listIdx][0] = (1 << tmp_log2WeightDenom) + tmp_WeightedPredSe;
	local_iLoop = iLoop;
	local_listIdx = listIdx;
	tmp_WeightedPredSe0 = tokens_WeightedPredSe[(index_WeightedPredSe % SIZE_WeightedPredSe) + (1)];
	offset[local_iLoop][local_listIdx][0] = tmp_WeightedPredSe0;

	// Update ports indexes
	index_WeightedPredSe += 2;
	read_end_WeightedPredSe();

	rate_WeightedPredSe += 2;
}
static i32 isSchedulable_getDeltaLumaWeight_skip() {
	i32 result;
	u8 local_iLoop;
	u8 local_refIdxLxAct;
	u8 local_listIdx;
	i32 tmp_weight;

	local_iLoop = iLoop;
	local_refIdxLxAct = refIdxLxAct;
	local_iLoop = iLoop;
	local_listIdx = listIdx;
	tmp_weight = weight[local_iLoop][local_listIdx][0];
	result = local_iLoop < local_refIdxLxAct && tmp_weight == 0;
	return result;
}

static void getDeltaLumaWeight_skip() {

	u8 local_iLoop;
	u8 local_listIdx;
	u8 tmp_log2WeightDenom;

	local_iLoop = iLoop;
	local_listIdx = listIdx;
	tmp_log2WeightDenom = log2WeightDenom[0];
	weight[local_iLoop][local_listIdx][0] = 1 << tmp_log2WeightDenom;
	local_iLoop = iLoop;
	local_listIdx = listIdx;
	offset[local_iLoop][local_listIdx][0] = 0;

	// Update ports indexes

}
static i32 isSchedulable_getDeltaLumaWeight_done() {
	i32 result;
	u8 local_iLoop;
	u8 local_refIdxLxAct;

	local_iLoop = iLoop;
	local_refIdxLxAct = refIdxLxAct;
	result = local_iLoop == local_refIdxLxAct;
	return result;
}

static void getDeltaLumaWeight_done() {

	u8 local_listIdx;

	iLoop = 0;
	local_listIdx = listIdx;
	listIdx = local_listIdx + 1;

	// Update ports indexes

}
static i32 isSchedulable_getDeltaChromaWeight_launch() {
	i32 result;
	u8 local_iLoop;
	u8 local_listIdx;
	i32 tmp_weight;

	local_iLoop = iLoop;
	local_listIdx = listIdx;
	tmp_weight = weight[local_iLoop][local_listIdx][1];
	result = tmp_weight != 0;
	return result;
}

static void getDeltaChromaWeight_launch() {

	i32 offPred;
	u8 local_iLoop;
	u8 local_listIdx;
	u8 tmp_log2WeightDenom;
	i16 tmp_WeightedPredSe;
	i32 tmp_weight;
	u8 tmp_log2WeightDenom0;
	i16 tmp_WeightedPredSe0;
	i32 tmp_clip_i32;
	u8 tmp_log2WeightDenom1;
	i16 tmp_WeightedPredSe1;
	i32 tmp_weight0;
	u8 tmp_log2WeightDenom2;
	i16 tmp_WeightedPredSe2;
	i32 tmp_clip_i320;

	local_iLoop = iLoop;
	local_listIdx = listIdx;
	tmp_log2WeightDenom = log2WeightDenom[1];
	tmp_WeightedPredSe = tokens_WeightedPredSe[(index_WeightedPredSe + (0)) % SIZE_WeightedPredSe];
	weight[local_iLoop][local_listIdx][1] = (1 << tmp_log2WeightDenom) + tmp_WeightedPredSe;
	local_iLoop = iLoop;
	local_listIdx = listIdx;
	tmp_weight = weight[local_iLoop][local_listIdx][1];
	tmp_log2WeightDenom0 = log2WeightDenom[1];
	offPred = 128 - ((128 * tmp_weight) >> tmp_log2WeightDenom0);
	local_iLoop = iLoop;
	local_listIdx = listIdx;
	tmp_WeightedPredSe0 = tokens_WeightedPredSe[(index_WeightedPredSe + (1)) % SIZE_WeightedPredSe];
	tmp_clip_i32 = HevcDecoder_InterPrediction_clip_i32(offPred + tmp_WeightedPredSe0, -128, 127);
	offset[local_iLoop][local_listIdx][1] = tmp_clip_i32;
	local_iLoop = iLoop;
	local_listIdx = listIdx;
	tmp_log2WeightDenom1 = log2WeightDenom[2];
	tmp_WeightedPredSe1 = tokens_WeightedPredSe[(index_WeightedPredSe + (2)) % SIZE_WeightedPredSe];
	weight[local_iLoop][local_listIdx][2] = (1 << tmp_log2WeightDenom1) + tmp_WeightedPredSe1;
	local_iLoop = iLoop;
	local_listIdx = listIdx;
	tmp_weight0 = weight[local_iLoop][local_listIdx][2];
	tmp_log2WeightDenom2 = log2WeightDenom[2];
	offPred = 128 - ((128 * tmp_weight0) >> tmp_log2WeightDenom2);
	local_iLoop = iLoop;
	local_listIdx = listIdx;
	tmp_WeightedPredSe2 = tokens_WeightedPredSe[(index_WeightedPredSe + (3)) % SIZE_WeightedPredSe];
	tmp_clip_i320 = HevcDecoder_InterPrediction_clip_i32(offPred + tmp_WeightedPredSe2, -128, 127);
	offset[local_iLoop][local_listIdx][2] = tmp_clip_i320;
	local_iLoop = iLoop;
	iLoop = local_iLoop + 1;

	// Update ports indexes
	index_WeightedPredSe += 4;
	read_end_WeightedPredSe();

	rate_WeightedPredSe += 4;
}
static void getDeltaChromaWeight_launch_aligned() {

	i32 offPred;
	u8 local_iLoop;
	u8 local_listIdx;
	u8 tmp_log2WeightDenom;
	i16 tmp_WeightedPredSe;
	i32 tmp_weight;
	u8 tmp_log2WeightDenom0;
	i16 tmp_WeightedPredSe0;
	i32 tmp_clip_i32;
	u8 tmp_log2WeightDenom1;
	i16 tmp_WeightedPredSe1;
	i32 tmp_weight0;
	u8 tmp_log2WeightDenom2;
	i16 tmp_WeightedPredSe2;
	i32 tmp_clip_i320;

	local_iLoop = iLoop;
	local_listIdx = listIdx;
	tmp_log2WeightDenom = log2WeightDenom[1];
	tmp_WeightedPredSe = tokens_WeightedPredSe[(index_WeightedPredSe % SIZE_WeightedPredSe) + (0)];
	weight[local_iLoop][local_listIdx][1] = (1 << tmp_log2WeightDenom) + tmp_WeightedPredSe;
	local_iLoop = iLoop;
	local_listIdx = listIdx;
	tmp_weight = weight[local_iLoop][local_listIdx][1];
	tmp_log2WeightDenom0 = log2WeightDenom[1];
	offPred = 128 - ((128 * tmp_weight) >> tmp_log2WeightDenom0);
	local_iLoop = iLoop;
	local_listIdx = listIdx;
	tmp_WeightedPredSe0 = tokens_WeightedPredSe[(index_WeightedPredSe % SIZE_WeightedPredSe) + (1)];
	tmp_clip_i32 = HevcDecoder_InterPrediction_clip_i32(offPred + tmp_WeightedPredSe0, -128, 127);
	offset[local_iLoop][local_listIdx][1] = tmp_clip_i32;
	local_iLoop = iLoop;
	local_listIdx = listIdx;
	tmp_log2WeightDenom1 = log2WeightDenom[2];
	tmp_WeightedPredSe1 = tokens_WeightedPredSe[(index_WeightedPredSe % SIZE_WeightedPredSe) + (2)];
	weight[local_iLoop][local_listIdx][2] = (1 << tmp_log2WeightDenom1) + tmp_WeightedPredSe1;
	local_iLoop = iLoop;
	local_listIdx = listIdx;
	tmp_weight0 = weight[local_iLoop][local_listIdx][2];
	tmp_log2WeightDenom2 = log2WeightDenom[2];
	offPred = 128 - ((128 * tmp_weight0) >> tmp_log2WeightDenom2);
	local_iLoop = iLoop;
	local_listIdx = listIdx;
	tmp_WeightedPredSe2 = tokens_WeightedPredSe[(index_WeightedPredSe % SIZE_WeightedPredSe) + (3)];
	tmp_clip_i320 = HevcDecoder_InterPrediction_clip_i32(offPred + tmp_WeightedPredSe2, -128, 127);
	offset[local_iLoop][local_listIdx][2] = tmp_clip_i320;
	local_iLoop = iLoop;
	iLoop = local_iLoop + 1;

	// Update ports indexes
	index_WeightedPredSe += 4;
	read_end_WeightedPredSe();

	rate_WeightedPredSe += 4;
}
static i32 isSchedulable_getDeltaChromaWeight_skip() {
	i32 result;
	u8 local_iLoop;
	u8 local_listIdx;
	i32 tmp_weight;

	local_iLoop = iLoop;
	local_listIdx = listIdx;
	tmp_weight = weight[local_iLoop][local_listIdx][1];
	result = tmp_weight == 0;
	return result;
}

static void getDeltaChromaWeight_skip() {

	u8 local_iLoop;
	u8 local_listIdx;
	u8 tmp_log2WeightDenom;
	u8 tmp_log2WeightDenom0;

	local_iLoop = iLoop;
	local_listIdx = listIdx;
	tmp_log2WeightDenom = log2WeightDenom[1];
	weight[local_iLoop][local_listIdx][1] = 1 << tmp_log2WeightDenom;
	local_iLoop = iLoop;
	local_listIdx = listIdx;
	offset[local_iLoop][local_listIdx][1] = 0;
	local_iLoop = iLoop;
	local_listIdx = listIdx;
	tmp_log2WeightDenom0 = log2WeightDenom[2];
	weight[local_iLoop][local_listIdx][2] = 1 << tmp_log2WeightDenom0;
	local_iLoop = iLoop;
	local_listIdx = listIdx;
	offset[local_iLoop][local_listIdx][2] = 0;
	local_iLoop = iLoop;
	iLoop = local_iLoop + 1;

	// Update ports indexes

}
static i32 isSchedulable_getCuInfo_launch() {
	i32 result;
	u8 local_numPartDecoded;
	u8 local_numPart;

	local_numPartDecoded = numPartDecoded;
	local_numPart = numPart;
	result = local_numPartDecoded < local_numPart;
	return result;
}

static void getCuInfo_launch() {

	u16 tmp_CUInfo;
	i32 i;
	u16 tmp_CUInfo0;
	i32 i0;
	u16 tmp_CUInfo1;
	i32 i1;
	u16 tmp_CUInfo2;
	u16 tmp_CUInfo3;
	u16 tmp_CUInfo4;
	i32 tmp_max;
	u8 local_predCuSize;
	u8 tmp_fullPuSize;
	u8 local_numPartDecoded;

	tmp_CUInfo = tokens_CUInfo[(index_CUInfo + (0)) % SIZE_CUInfo];
	cuMode = tmp_CUInfo;
	i = 3;
	while (i <= 4) {
		tmp_CUInfo0 = tokens_CUInfo[(index_CUInfo + (i)) % SIZE_CUInfo];
		puSize[i - 3] = tmp_CUInfo0;
		i = i + 1;
	}
	i0 = 3;
	while (i0 <= 4) {
		tmp_CUInfo1 = tokens_CUInfo[(index_CUInfo + (i0)) % SIZE_CUInfo];
		fullPuSize[i0 - 3] = tmp_CUInfo1 + 7;
		i0 = i0 + 1;
	}
	i1 = 3;
	while (i1 <= 4) {
		tmp_CUInfo2 = tokens_CUInfo[(index_CUInfo + (i1)) % SIZE_CUInfo];
		fullPuSizeChr[i1 - 3] = (tmp_CUInfo2 >> 1) + 3;
		i1 = i1 + 1;
	}
	tmp_CUInfo3 = tokens_CUInfo[(index_CUInfo + (3)) % SIZE_CUInfo];
	tmp_CUInfo4 = tokens_CUInfo[(index_CUInfo + (4)) % SIZE_CUInfo];
	tmp_max = HevcDecoder_InterPrediction_max(tmp_CUInfo3, tmp_CUInfo4);
	predCuSize = tmp_max;
	local_predCuSize = predCuSize;
	tmp_fullPuSize = fullPuSize[0];
	pixIdxOff[0] = local_predCuSize + 7 - tmp_fullPuSize;
	local_predCuSize = predCuSize;
	pixIdxOff[1] = local_predCuSize / 2 + 3;
	local_numPartDecoded = numPartDecoded;
	numPartDecoded = local_numPartDecoded + 1;

	// Update ports indexes
	index_CUInfo += 5;
	read_end_CUInfo();

	rate_CUInfo += 5;
}
static void getCuInfo_launch_aligned() {

	u16 tmp_CUInfo;
	i32 i;
	u16 tmp_CUInfo0;
	i32 i0;
	u16 tmp_CUInfo1;
	i32 i1;
	u16 tmp_CUInfo2;
	u16 tmp_CUInfo3;
	u16 tmp_CUInfo4;
	i32 tmp_max;
	u8 local_predCuSize;
	u8 tmp_fullPuSize;
	u8 local_numPartDecoded;

	tmp_CUInfo = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (0)];
	cuMode = tmp_CUInfo;
	i = 3;
	while (i <= 4) {
		tmp_CUInfo0 = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (i)];
		puSize[i - 3] = tmp_CUInfo0;
		i = i + 1;
	}
	i0 = 3;
	while (i0 <= 4) {
		tmp_CUInfo1 = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (i0)];
		fullPuSize[i0 - 3] = tmp_CUInfo1 + 7;
		i0 = i0 + 1;
	}
	i1 = 3;
	while (i1 <= 4) {
		tmp_CUInfo2 = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (i1)];
		fullPuSizeChr[i1 - 3] = (tmp_CUInfo2 >> 1) + 3;
		i1 = i1 + 1;
	}
	tmp_CUInfo3 = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (3)];
	tmp_CUInfo4 = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (4)];
	tmp_max = HevcDecoder_InterPrediction_max(tmp_CUInfo3, tmp_CUInfo4);
	predCuSize = tmp_max;
	local_predCuSize = predCuSize;
	tmp_fullPuSize = fullPuSize[0];
	pixIdxOff[0] = local_predCuSize + 7 - tmp_fullPuSize;
	local_predCuSize = predCuSize;
	pixIdxOff[1] = local_predCuSize / 2 + 3;
	local_numPartDecoded = numPartDecoded;
	numPartDecoded = local_numPartDecoded + 1;

	// Update ports indexes
	index_CUInfo += 5;
	read_end_CUInfo();

	rate_CUInfo += 5;
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
static i32 isSchedulable_getCuMode_isNotInter() {
	i32 result;
	u8 local_cuMode;
	u8 local_INTER;
	u8 local_SKIP;

	local_cuMode = cuMode;
	local_INTER = HevcDecoder_InterPrediction_INTER;
	local_cuMode = cuMode;
	local_SKIP = HevcDecoder_InterPrediction_SKIP;
	result = !(local_cuMode == local_INTER || local_cuMode == local_SKIP);
	return result;
}

static void getCuMode_isNotInter() {



	// Update ports indexes

}
static i32 isSchedulable_getCuMode_isInter() {
	i32 result;
	u8 local_cuMode;
	u8 local_INTER;
	u8 local_SKIP;

	local_cuMode = cuMode;
	local_INTER = HevcDecoder_InterPrediction_INTER;
	local_cuMode = cuMode;
	local_SKIP = HevcDecoder_InterPrediction_SKIP;
	result = local_cuMode == local_INTER || local_cuMode == local_SKIP;
	return result;
}

static void getCuMode_isInter() {

	u8 isBiPredOrPredLX;

	isBiPredOrPredLX = tokens_IsBiPredOrLx[(index_IsBiPredOrLx + (0)) % SIZE_IsBiPredOrLx];
	isBiPredOrLx = isBiPredOrPredLX;

	// Update ports indexes
	index_IsBiPredOrLx += 1;

	rate_IsBiPredOrLx += 1;
}
static i32 isSchedulable_getRefIdx_monoPred() {
	i32 result;
	u8 local_isBiPredOrLx;
	u8 local_BI_PRED;

	local_isBiPredOrLx = isBiPredOrLx;
	local_BI_PRED = HevcDecoder_InterPrediction_BI_PRED;
	result = local_isBiPredOrLx != local_BI_PRED;
	return result;
}

static void getRefIdx_monoPred() {

	u8 refIndexLx;
	u32 idxL0;
	u32 idxL1;
	u8 local_isBiPredOrLx;
	u8 local_PRED_L0;
	i32 i;
	i32 tmp_Mv;
	i32 i0;
	i32 tmp_Mv0;
	i8 tmp_refIdxLx;
	i8 tmp_refIdxLx0;
	i32 tmp_logWDTab;
	i32 tmp_logWDTab0;
	i32 tmp_logWDTab1;
	i32 list;
	i32 tmp_weightCuTab;
	i32 tmp_offsetCuTab;
	i32 tmp_weightCuTab0;
	i32 tmp_offsetCuTab0;
	i32 tmp_weightCuTab1;
	i32 tmp_offsetCuTab1;

	refIndexLx = tokens_RefIdx[(index_RefIdx + (0)) % SIZE_RefIdx];
	local_isBiPredOrLx = isBiPredOrLx;
	local_PRED_L0 = HevcDecoder_InterPrediction_PRED_L0;
	if (local_isBiPredOrLx == local_PRED_L0) {
		i = 0;
		while (i <= 1) {
			tmp_Mv = tokens_Mv[(index_Mv + (i)) % SIZE_Mv];
			mvLx[0][i] = tmp_Mv;
			i = i + 1;
		}
		mvLx[1][0] = 0;
		mvLx[1][1] = 0;
		refIdxLx[0] = refIndexLx;
		refIdxLx[1] = -1;
		listIdx = 0;
	} else {
		i0 = 0;
		while (i0 <= 1) {
			tmp_Mv0 = tokens_Mv[(index_Mv + (i0)) % SIZE_Mv];
			mvLx[1][i0] = tmp_Mv0;
			i0 = i0 + 1;
		}
		mvLx[0][0] = 0;
		mvLx[0][1] = 0;
		refIdxLx[0] = -1;
		refIdxLx[1] = refIndexLx;
		listIdx = 1;
	}
	tmp_refIdxLx = refIdxLx[0];
	idxL0 = tmp_refIdxLx + 1;
	tmp_refIdxLx0 = refIdxLx[1];
	idxL1 = tmp_refIdxLx0 + 1;
	tmp_logWDTab = logWDTab[idxL0][idxL1][0];
	logWD_y = tmp_logWDTab;
	tmp_logWDTab0 = logWDTab[idxL0][idxL1][1];
	logWD_u = tmp_logWDTab0;
	tmp_logWDTab1 = logWDTab[idxL0][idxL1][2];
	logWD_v = tmp_logWDTab1;
	list = 0;
	while (list <= 1) {
		tmp_weightCuTab = weightCuTab[idxL0][idxL1][0][list];
		weightCu_y[list] = tmp_weightCuTab;
		tmp_offsetCuTab = offsetCuTab[idxL0][idxL1][0][list];
		offsetCu_y[list] = tmp_offsetCuTab;
		tmp_weightCuTab0 = weightCuTab[idxL0][idxL1][1][list];
		weightCu_u[list] = tmp_weightCuTab0;
		tmp_offsetCuTab0 = offsetCuTab[idxL0][idxL1][1][list];
		offsetCu_u[list] = tmp_offsetCuTab0;
		tmp_weightCuTab1 = weightCuTab[idxL0][idxL1][2][list];
		weightCu_v[list] = tmp_weightCuTab1;
		tmp_offsetCuTab1 = offsetCuTab[idxL0][idxL1][2][list];
		offsetCu_v[list] = tmp_offsetCuTab1;
		list = list + 1;
	}
	numList = 1;

	// Update ports indexes
	index_RefIdx += 1;
	index_Mv += 2;
	read_end_Mv();

	rate_RefIdx += 1;
	rate_Mv += 2;
}
static void getRefIdx_monoPred_aligned() {

	u8 refIndexLx;
	u32 idxL0;
	u32 idxL1;
	u8 local_isBiPredOrLx;
	u8 local_PRED_L0;
	i32 i;
	i32 tmp_Mv;
	i32 i0;
	i32 tmp_Mv0;
	i8 tmp_refIdxLx;
	i8 tmp_refIdxLx0;
	i32 tmp_logWDTab;
	i32 tmp_logWDTab0;
	i32 tmp_logWDTab1;
	i32 list;
	i32 tmp_weightCuTab;
	i32 tmp_offsetCuTab;
	i32 tmp_weightCuTab0;
	i32 tmp_offsetCuTab0;
	i32 tmp_weightCuTab1;
	i32 tmp_offsetCuTab1;

	refIndexLx = tokens_RefIdx[(index_RefIdx + (0)) % SIZE_RefIdx];
	local_isBiPredOrLx = isBiPredOrLx;
	local_PRED_L0 = HevcDecoder_InterPrediction_PRED_L0;
	if (local_isBiPredOrLx == local_PRED_L0) {
		i = 0;
		while (i <= 1) {
			tmp_Mv = tokens_Mv[(index_Mv % SIZE_Mv) + (i)];
			mvLx[0][i] = tmp_Mv;
			i = i + 1;
		}
		mvLx[1][0] = 0;
		mvLx[1][1] = 0;
		refIdxLx[0] = refIndexLx;
		refIdxLx[1] = -1;
		listIdx = 0;
	} else {
		i0 = 0;
		while (i0 <= 1) {
			tmp_Mv0 = tokens_Mv[(index_Mv % SIZE_Mv) + (i0)];
			mvLx[1][i0] = tmp_Mv0;
			i0 = i0 + 1;
		}
		mvLx[0][0] = 0;
		mvLx[0][1] = 0;
		refIdxLx[0] = -1;
		refIdxLx[1] = refIndexLx;
		listIdx = 1;
	}
	tmp_refIdxLx = refIdxLx[0];
	idxL0 = tmp_refIdxLx + 1;
	tmp_refIdxLx0 = refIdxLx[1];
	idxL1 = tmp_refIdxLx0 + 1;
	tmp_logWDTab = logWDTab[idxL0][idxL1][0];
	logWD_y = tmp_logWDTab;
	tmp_logWDTab0 = logWDTab[idxL0][idxL1][1];
	logWD_u = tmp_logWDTab0;
	tmp_logWDTab1 = logWDTab[idxL0][idxL1][2];
	logWD_v = tmp_logWDTab1;
	list = 0;
	while (list <= 1) {
		tmp_weightCuTab = weightCuTab[idxL0][idxL1][0][list];
		weightCu_y[list] = tmp_weightCuTab;
		tmp_offsetCuTab = offsetCuTab[idxL0][idxL1][0][list];
		offsetCu_y[list] = tmp_offsetCuTab;
		tmp_weightCuTab0 = weightCuTab[idxL0][idxL1][1][list];
		weightCu_u[list] = tmp_weightCuTab0;
		tmp_offsetCuTab0 = offsetCuTab[idxL0][idxL1][1][list];
		offsetCu_u[list] = tmp_offsetCuTab0;
		tmp_weightCuTab1 = weightCuTab[idxL0][idxL1][2][list];
		weightCu_v[list] = tmp_weightCuTab1;
		tmp_offsetCuTab1 = offsetCuTab[idxL0][idxL1][2][list];
		offsetCu_v[list] = tmp_offsetCuTab1;
		list = list + 1;
	}
	numList = 1;

	// Update ports indexes
	index_RefIdx += 1;
	index_Mv += 2;
	read_end_Mv();

	rate_RefIdx += 1;
	rate_Mv += 2;
}
static i32 isSchedulable_getRefIdx_biPred() {
	i32 result;
	u8 local_isBiPredOrLx;
	u8 local_BI_PRED;

	local_isBiPredOrLx = isBiPredOrLx;
	local_BI_PRED = HevcDecoder_InterPrediction_BI_PRED;
	result = local_isBiPredOrLx == local_BI_PRED;
	return result;
}

static void getRefIdx_biPred() {

	u32 idxL0;
	u32 idxL1;
	i32 i;
	u32 j;
	i32 tmp_Mv;
	u32 i0;
	u8 tmp_RefIdx;
	i8 tmp_refIdxLx;
	i8 tmp_refIdxLx0;
	i32 tmp_logWDTab;
	i32 tmp_logWDTab0;
	i32 tmp_logWDTab1;
	i32 list;
	i32 tmp_weightCuTab;
	i32 tmp_offsetCuTab;
	i32 tmp_weightCuTab0;
	i32 tmp_offsetCuTab0;
	i32 tmp_weightCuTab1;
	i32 tmp_offsetCuTab1;
	i8 tmp_refIdxLx1;
	i16 tmp_refListX;
	i8 tmp_refIdxLx2;
	i16 tmp_refListX0;
	i32 tmp_mvLx;
	i32 tmp_mvLx0;
	i32 tmp_mvLx1;
	i32 tmp_mvLx2;
	i8 tmp_refIdxLx3;
	i8 tmp_refIdxLx4;

	i = 0;
	while (i <= 1) {
		j = 0;
		while (j <= 1) {
			tmp_Mv = tokens_Mv[(index_Mv + (2 * i + j)) % SIZE_Mv];
			mvLx[i][j] = tmp_Mv;
			j = j + 1;
		}
		i = i + 1;
	}
	i0 = 0;
	while (i0 <= 1) {
		tmp_RefIdx = tokens_RefIdx[(index_RefIdx + (i0)) % SIZE_RefIdx];
		refIdxLx[i0] = tmp_RefIdx;
		i0 = i0 + 1;
	}
	tmp_refIdxLx = refIdxLx[0];
	idxL0 = tmp_refIdxLx + 1;
	tmp_refIdxLx0 = refIdxLx[1];
	idxL1 = tmp_refIdxLx0 + 1;
	tmp_logWDTab = logWDTab[idxL0][idxL1][0];
	logWD_y = tmp_logWDTab;
	tmp_logWDTab0 = logWDTab[idxL0][idxL1][1];
	logWD_u = tmp_logWDTab0;
	tmp_logWDTab1 = logWDTab[idxL0][idxL1][2];
	logWD_v = tmp_logWDTab1;
	list = 0;
	while (list <= 1) {
		tmp_weightCuTab = weightCuTab[idxL0][idxL1][0][list];
		weightCu_y[list] = tmp_weightCuTab;
		tmp_offsetCuTab = offsetCuTab[idxL0][idxL1][0][list];
		offsetCu_y[list] = tmp_offsetCuTab;
		tmp_weightCuTab0 = weightCuTab[idxL0][idxL1][1][list];
		weightCu_u[list] = tmp_weightCuTab0;
		tmp_offsetCuTab0 = offsetCuTab[idxL0][idxL1][1][list];
		offsetCu_u[list] = tmp_offsetCuTab0;
		tmp_weightCuTab1 = weightCuTab[idxL0][idxL1][2][list];
		weightCu_v[list] = tmp_weightCuTab1;
		tmp_offsetCuTab1 = offsetCuTab[idxL0][idxL1][2][list];
		offsetCu_v[list] = tmp_offsetCuTab1;
		list = list + 1;
	}
	listIdx = 0;
	tmp_refIdxLx1 = refIdxLx[0];
	tmp_refListX = refListX[0][tmp_refIdxLx1];
	tmp_refIdxLx2 = refIdxLx[1];
	tmp_refListX0 = refListX[1][tmp_refIdxLx2];
	tmp_mvLx = mvLx[0][0];
	tmp_mvLx0 = mvLx[1][0];
	tmp_mvLx1 = mvLx[0][1];
	tmp_mvLx2 = mvLx[1][1];
	tmp_refIdxLx3 = refIdxLx[0];
	tmp_refIdxLx4 = refIdxLx[1];
	if (tmp_refListX == tmp_refListX0 && tmp_mvLx == tmp_mvLx0 && tmp_mvLx1 == tmp_mvLx2 && tmp_refIdxLx3 == tmp_refIdxLx4) {
		numList = 1;
	} else {
		numList = 2;
	}

	// Update ports indexes
	index_RefIdx += 2;
	read_end_RefIdx();
	index_Mv += 4;
	read_end_Mv();

	rate_RefIdx += 2;
	rate_Mv += 4;
}
static void getRefIdx_biPred_aligned() {

	u32 idxL0;
	u32 idxL1;
	i32 i;
	u32 j;
	i32 tmp_Mv;
	u32 i0;
	u8 tmp_RefIdx;
	i8 tmp_refIdxLx;
	i8 tmp_refIdxLx0;
	i32 tmp_logWDTab;
	i32 tmp_logWDTab0;
	i32 tmp_logWDTab1;
	i32 list;
	i32 tmp_weightCuTab;
	i32 tmp_offsetCuTab;
	i32 tmp_weightCuTab0;
	i32 tmp_offsetCuTab0;
	i32 tmp_weightCuTab1;
	i32 tmp_offsetCuTab1;
	i8 tmp_refIdxLx1;
	i16 tmp_refListX;
	i8 tmp_refIdxLx2;
	i16 tmp_refListX0;
	i32 tmp_mvLx;
	i32 tmp_mvLx0;
	i32 tmp_mvLx1;
	i32 tmp_mvLx2;
	i8 tmp_refIdxLx3;
	i8 tmp_refIdxLx4;

	i = 0;
	while (i <= 1) {
		j = 0;
		while (j <= 1) {
			tmp_Mv = tokens_Mv[(index_Mv % SIZE_Mv) + (2 * i + j)];
			mvLx[i][j] = tmp_Mv;
			j = j + 1;
		}
		i = i + 1;
	}
	i0 = 0;
	while (i0 <= 1) {
		tmp_RefIdx = tokens_RefIdx[(index_RefIdx % SIZE_RefIdx) + (i0)];
		refIdxLx[i0] = tmp_RefIdx;
		i0 = i0 + 1;
	}
	tmp_refIdxLx = refIdxLx[0];
	idxL0 = tmp_refIdxLx + 1;
	tmp_refIdxLx0 = refIdxLx[1];
	idxL1 = tmp_refIdxLx0 + 1;
	tmp_logWDTab = logWDTab[idxL0][idxL1][0];
	logWD_y = tmp_logWDTab;
	tmp_logWDTab0 = logWDTab[idxL0][idxL1][1];
	logWD_u = tmp_logWDTab0;
	tmp_logWDTab1 = logWDTab[idxL0][idxL1][2];
	logWD_v = tmp_logWDTab1;
	list = 0;
	while (list <= 1) {
		tmp_weightCuTab = weightCuTab[idxL0][idxL1][0][list];
		weightCu_y[list] = tmp_weightCuTab;
		tmp_offsetCuTab = offsetCuTab[idxL0][idxL1][0][list];
		offsetCu_y[list] = tmp_offsetCuTab;
		tmp_weightCuTab0 = weightCuTab[idxL0][idxL1][1][list];
		weightCu_u[list] = tmp_weightCuTab0;
		tmp_offsetCuTab0 = offsetCuTab[idxL0][idxL1][1][list];
		offsetCu_u[list] = tmp_offsetCuTab0;
		tmp_weightCuTab1 = weightCuTab[idxL0][idxL1][2][list];
		weightCu_v[list] = tmp_weightCuTab1;
		tmp_offsetCuTab1 = offsetCuTab[idxL0][idxL1][2][list];
		offsetCu_v[list] = tmp_offsetCuTab1;
		list = list + 1;
	}
	listIdx = 0;
	tmp_refIdxLx1 = refIdxLx[0];
	tmp_refListX = refListX[0][tmp_refIdxLx1];
	tmp_refIdxLx2 = refIdxLx[1];
	tmp_refListX0 = refListX[1][tmp_refIdxLx2];
	tmp_mvLx = mvLx[0][0];
	tmp_mvLx0 = mvLx[1][0];
	tmp_mvLx1 = mvLx[0][1];
	tmp_mvLx2 = mvLx[1][1];
	tmp_refIdxLx3 = refIdxLx[0];
	tmp_refIdxLx4 = refIdxLx[1];
	if (tmp_refListX == tmp_refListX0 && tmp_mvLx == tmp_mvLx0 && tmp_mvLx1 == tmp_mvLx2 && tmp_refIdxLx3 == tmp_refIdxLx4) {
		numList = 1;
	} else {
		numList = 2;
	}

	// Update ports indexes
	index_RefIdx += 2;
	read_end_RefIdx();
	index_Mv += 4;
	read_end_Mv();

	rate_RefIdx += 2;
	rate_Mv += 4;
}
static i32 isSchedulable_getAllSamples_launch() {
	i32 result;
	u8 local_numList;
	u8 local_listIdx;
	u8 local_isBiPredOrLx;
	u8 local_BI_PRED;
	u8 local_PRED_L1;

	local_numList = numList;
	local_listIdx = listIdx;
	local_isBiPredOrLx = isBiPredOrLx;
	local_BI_PRED = HevcDecoder_InterPrediction_BI_PRED;
	local_listIdx = listIdx;
	local_listIdx = listIdx;
	local_isBiPredOrLx = isBiPredOrLx;
	local_BI_PRED = HevcDecoder_InterPrediction_BI_PRED;
	local_isBiPredOrLx = isBiPredOrLx;
	local_PRED_L1 = HevcDecoder_InterPrediction_PRED_L1;
	result = !(local_numList == 1 && local_listIdx == 1 && local_isBiPredOrLx == local_BI_PRED) && (local_listIdx == 0 || local_listIdx == 1 && (local_isBiPredOrLx == local_BI_PRED || local_isBiPredOrLx == local_PRED_L1));
	return result;
}

static void getAllSamples_launch() {


	pixIdx = 0;
	iLoop = 0;
	jLoop = 0;

	// Update ports indexes

}
static i32 isSchedulable_lumaWidth_is71() {
	i32 result;
	u8 tmp_fullPuSize;

	tmp_fullPuSize = fullPuSize[0];
	result = tmp_fullPuSize == 71;
	return result;
}

static void lumaWidth_is71() {



	// Update ports indexes

}
static i32 isSchedulable_lumaWidth_is39() {
	i32 result;
	u8 tmp_fullPuSize;

	tmp_fullPuSize = fullPuSize[0];
	result = tmp_fullPuSize == 39;
	return result;
}

static void lumaWidth_is39() {



	// Update ports indexes

}
static i32 isSchedulable_lumaWidth_is23() {
	i32 result;
	u8 tmp_fullPuSize;

	tmp_fullPuSize = fullPuSize[0];
	result = tmp_fullPuSize == 23;
	return result;
}

static void lumaWidth_is23() {



	// Update ports indexes

}
static i32 isSchedulable_lumaWidth_is15() {
	i32 result;
	u8 tmp_fullPuSize;

	tmp_fullPuSize = fullPuSize[0];
	result = tmp_fullPuSize == 15;
	return result;
}

static void lumaWidth_is15() {



	// Update ports indexes

}
static i32 isSchedulable_lumaWidth_is11() {
	i32 result;
	u8 tmp_fullPuSize;

	tmp_fullPuSize = fullPuSize[0];
	result = tmp_fullPuSize == 11;
	return result;
}

static void lumaWidth_is11() {



	// Update ports indexes

}
static i32 isSchedulable_chromaWidth_is35() {
	i32 result;
	u8 tmp_fullPuSizeChr;

	tmp_fullPuSizeChr = fullPuSizeChr[0];
	result = tmp_fullPuSizeChr == 35;
	return result;
}

static void chromaWidth_is35() {



	// Update ports indexes

}
static i32 isSchedulable_chromaWidth_is19() {
	i32 result;
	u8 tmp_fullPuSizeChr;

	tmp_fullPuSizeChr = fullPuSizeChr[0];
	result = tmp_fullPuSizeChr == 19;
	return result;
}

static void chromaWidth_is19() {



	// Update ports indexes

}
static i32 isSchedulable_chromaWidth_is11() {
	i32 result;
	u8 tmp_fullPuSizeChr;

	tmp_fullPuSizeChr = fullPuSizeChr[0];
	result = tmp_fullPuSizeChr == 11;
	return result;
}

static void chromaWidth_is11() {



	// Update ports indexes

}
static i32 isSchedulable_chromaWidth_is7() {
	i32 result;
	u8 tmp_fullPuSizeChr;

	tmp_fullPuSizeChr = fullPuSizeChr[0];
	result = tmp_fullPuSizeChr == 7;
	return result;
}

static void chromaWidth_is7() {



	// Update ports indexes

}
static i32 isSchedulable_chromaWidth_is5() {
	i32 result;
	u8 tmp_fullPuSizeChr;

	tmp_fullPuSizeChr = fullPuSizeChr[0];
	result = tmp_fullPuSizeChr == 5;
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
static i32 isSchedulable_getSamples_luma_launch_is71() {
	i32 result;
	u8 local_jLoop;
	u8 tmp_fullPuSize;

	local_jLoop = jLoop;
	tmp_fullPuSize = fullPuSize[1];
	result = local_jLoop < tmp_fullPuSize;
	return result;
}

static void getSamples_luma_launch_is71() {

	i32 i;
	u16 local_pixIdx;
	u8 tmp_Sample;
	u8 local_predCuSize;
	u8 local_jLoop;

	i = 0;
	while (i <= 70) {
		local_pixIdx = pixIdx;
		tmp_Sample = tokens_Sample[(index_Sample + (i)) % SIZE_Sample];
		refSamples_y[local_pixIdx + i] = tmp_Sample;
		i = i + 1;
	}
	iLoop = 0;
	local_pixIdx = pixIdx;
	local_predCuSize = predCuSize;
	pixIdx = local_pixIdx + local_predCuSize + 7;
	local_jLoop = jLoop;
	jLoop = local_jLoop + 1;

	// Update ports indexes
	index_Sample += 71;
	read_end_Sample();

	rate_Sample += 71;
}
static void getSamples_luma_launch_is71_aligned() {

	i32 i;
	u16 local_pixIdx;
	u8 tmp_Sample;
	u8 local_predCuSize;
	u8 local_jLoop;

	i = 0;
	while (i <= 70) {
		local_pixIdx = pixIdx;
		tmp_Sample = tokens_Sample[(index_Sample % SIZE_Sample) + (i)];
		refSamples_y[local_pixIdx + i] = tmp_Sample;
		i = i + 1;
	}
	iLoop = 0;
	local_pixIdx = pixIdx;
	local_predCuSize = predCuSize;
	pixIdx = local_pixIdx + local_predCuSize + 7;
	local_jLoop = jLoop;
	jLoop = local_jLoop + 1;

	// Update ports indexes
	index_Sample += 71;
	read_end_Sample();

	rate_Sample += 71;
}
static i32 isSchedulable_getSamples_luma_launch_is39() {
	i32 result;
	u8 local_jLoop;
	u8 tmp_fullPuSize;

	local_jLoop = jLoop;
	tmp_fullPuSize = fullPuSize[1];
	result = local_jLoop < tmp_fullPuSize;
	return result;
}

static void getSamples_luma_launch_is39() {

	i32 i;
	u16 local_pixIdx;
	u8 tmp_Sample;
	u8 local_predCuSize;
	u8 local_jLoop;

	i = 0;
	while (i <= 38) {
		local_pixIdx = pixIdx;
		tmp_Sample = tokens_Sample[(index_Sample + (i)) % SIZE_Sample];
		refSamples_y[local_pixIdx + i] = tmp_Sample;
		i = i + 1;
	}
	iLoop = 0;
	local_pixIdx = pixIdx;
	local_predCuSize = predCuSize;
	pixIdx = local_pixIdx + local_predCuSize + 7;
	local_jLoop = jLoop;
	jLoop = local_jLoop + 1;

	// Update ports indexes
	index_Sample += 39;
	read_end_Sample();

	rate_Sample += 39;
}
static void getSamples_luma_launch_is39_aligned() {

	i32 i;
	u16 local_pixIdx;
	u8 tmp_Sample;
	u8 local_predCuSize;
	u8 local_jLoop;

	i = 0;
	while (i <= 38) {
		local_pixIdx = pixIdx;
		tmp_Sample = tokens_Sample[(index_Sample % SIZE_Sample) + (i)];
		refSamples_y[local_pixIdx + i] = tmp_Sample;
		i = i + 1;
	}
	iLoop = 0;
	local_pixIdx = pixIdx;
	local_predCuSize = predCuSize;
	pixIdx = local_pixIdx + local_predCuSize + 7;
	local_jLoop = jLoop;
	jLoop = local_jLoop + 1;

	// Update ports indexes
	index_Sample += 39;
	read_end_Sample();

	rate_Sample += 39;
}
static i32 isSchedulable_getSamples_luma_launch_is23() {
	i32 result;
	u8 local_jLoop;
	u8 tmp_fullPuSize;

	local_jLoop = jLoop;
	tmp_fullPuSize = fullPuSize[1];
	result = local_jLoop < tmp_fullPuSize;
	return result;
}

static void getSamples_luma_launch_is23() {

	i32 i;
	u16 local_pixIdx;
	u8 tmp_Sample;
	u8 local_predCuSize;
	u8 local_jLoop;

	i = 0;
	while (i <= 22) {
		local_pixIdx = pixIdx;
		tmp_Sample = tokens_Sample[(index_Sample + (i)) % SIZE_Sample];
		refSamples_y[local_pixIdx + i] = tmp_Sample;
		i = i + 1;
	}
	iLoop = 0;
	local_pixIdx = pixIdx;
	local_predCuSize = predCuSize;
	pixIdx = local_pixIdx + local_predCuSize + 7;
	local_jLoop = jLoop;
	jLoop = local_jLoop + 1;

	// Update ports indexes
	index_Sample += 23;
	read_end_Sample();

	rate_Sample += 23;
}
static void getSamples_luma_launch_is23_aligned() {

	i32 i;
	u16 local_pixIdx;
	u8 tmp_Sample;
	u8 local_predCuSize;
	u8 local_jLoop;

	i = 0;
	while (i <= 22) {
		local_pixIdx = pixIdx;
		tmp_Sample = tokens_Sample[(index_Sample % SIZE_Sample) + (i)];
		refSamples_y[local_pixIdx + i] = tmp_Sample;
		i = i + 1;
	}
	iLoop = 0;
	local_pixIdx = pixIdx;
	local_predCuSize = predCuSize;
	pixIdx = local_pixIdx + local_predCuSize + 7;
	local_jLoop = jLoop;
	jLoop = local_jLoop + 1;

	// Update ports indexes
	index_Sample += 23;
	read_end_Sample();

	rate_Sample += 23;
}
static i32 isSchedulable_getSamples_luma_launch_is15() {
	i32 result;
	u8 local_jLoop;
	u8 tmp_fullPuSize;

	local_jLoop = jLoop;
	tmp_fullPuSize = fullPuSize[1];
	result = local_jLoop < tmp_fullPuSize;
	return result;
}

static void getSamples_luma_launch_is15() {

	i32 i;
	u16 local_pixIdx;
	u8 tmp_Sample;
	u8 local_predCuSize;
	u8 local_jLoop;

	i = 0;
	while (i <= 14) {
		local_pixIdx = pixIdx;
		tmp_Sample = tokens_Sample[(index_Sample + (i)) % SIZE_Sample];
		refSamples_y[local_pixIdx + i] = tmp_Sample;
		i = i + 1;
	}
	iLoop = 0;
	local_pixIdx = pixIdx;
	local_predCuSize = predCuSize;
	pixIdx = local_pixIdx + local_predCuSize + 7;
	local_jLoop = jLoop;
	jLoop = local_jLoop + 1;

	// Update ports indexes
	index_Sample += 15;
	read_end_Sample();

	rate_Sample += 15;
}
static void getSamples_luma_launch_is15_aligned() {

	i32 i;
	u16 local_pixIdx;
	u8 tmp_Sample;
	u8 local_predCuSize;
	u8 local_jLoop;

	i = 0;
	while (i <= 14) {
		local_pixIdx = pixIdx;
		tmp_Sample = tokens_Sample[(index_Sample % SIZE_Sample) + (i)];
		refSamples_y[local_pixIdx + i] = tmp_Sample;
		i = i + 1;
	}
	iLoop = 0;
	local_pixIdx = pixIdx;
	local_predCuSize = predCuSize;
	pixIdx = local_pixIdx + local_predCuSize + 7;
	local_jLoop = jLoop;
	jLoop = local_jLoop + 1;

	// Update ports indexes
	index_Sample += 15;
	read_end_Sample();

	rate_Sample += 15;
}
static i32 isSchedulable_getSamples_luma_launch_is11() {
	i32 result;
	u8 local_jLoop;
	u8 tmp_fullPuSize;

	local_jLoop = jLoop;
	tmp_fullPuSize = fullPuSize[1];
	result = local_jLoop < tmp_fullPuSize;
	return result;
}

static void getSamples_luma_launch_is11() {

	i32 i;
	u16 local_pixIdx;
	u8 tmp_Sample;
	u8 local_predCuSize;
	u8 local_jLoop;

	i = 0;
	while (i <= 10) {
		local_pixIdx = pixIdx;
		tmp_Sample = tokens_Sample[(index_Sample + (i)) % SIZE_Sample];
		refSamples_y[local_pixIdx + i] = tmp_Sample;
		i = i + 1;
	}
	iLoop = 0;
	local_pixIdx = pixIdx;
	local_predCuSize = predCuSize;
	pixIdx = local_pixIdx + local_predCuSize + 7;
	local_jLoop = jLoop;
	jLoop = local_jLoop + 1;

	// Update ports indexes
	index_Sample += 11;
	read_end_Sample();

	rate_Sample += 11;
}
static void getSamples_luma_launch_is11_aligned() {

	i32 i;
	u16 local_pixIdx;
	u8 tmp_Sample;
	u8 local_predCuSize;
	u8 local_jLoop;

	i = 0;
	while (i <= 10) {
		local_pixIdx = pixIdx;
		tmp_Sample = tokens_Sample[(index_Sample % SIZE_Sample) + (i)];
		refSamples_y[local_pixIdx + i] = tmp_Sample;
		i = i + 1;
	}
	iLoop = 0;
	local_pixIdx = pixIdx;
	local_predCuSize = predCuSize;
	pixIdx = local_pixIdx + local_predCuSize + 7;
	local_jLoop = jLoop;
	jLoop = local_jLoop + 1;

	// Update ports indexes
	index_Sample += 11;
	read_end_Sample();

	rate_Sample += 11;
}
static i32 isSchedulable_getSamples_luma_launch_is1() {
	i32 result;
	u8 local_jLoop;
	u8 tmp_fullPuSize;

	local_jLoop = jLoop;
	tmp_fullPuSize = fullPuSize[1];
	result = local_jLoop < tmp_fullPuSize;
	return result;
}

static void getSamples_luma_launch_is1() {

	u8 sample;
	u16 local_pixIdx;
	u8 local_iLoop;
	u8 tmp_fullPuSize;
	u16 tmp_pixIdxOff;
	u8 local_jLoop;

	sample = tokens_Sample[(index_Sample + (0)) % SIZE_Sample];
	local_pixIdx = pixIdx;
	refSamples_y[local_pixIdx] = sample;
	local_pixIdx = pixIdx;
	pixIdx = local_pixIdx + 1;
	local_iLoop = iLoop;
	iLoop = local_iLoop + 1;
	local_iLoop = iLoop;
	tmp_fullPuSize = fullPuSize[0];
	if (local_iLoop == tmp_fullPuSize) {
		iLoop = 0;
		local_pixIdx = pixIdx;
		tmp_pixIdxOff = pixIdxOff[0];
		pixIdx = local_pixIdx + tmp_pixIdxOff;
		local_jLoop = jLoop;
		jLoop = local_jLoop + 1;
	}

	// Update ports indexes
	index_Sample += 1;

	rate_Sample += 1;
}
static i32 isSchedulable_getSamples_luma_done() {
	i32 result;
	u8 local_jLoop;
	u8 tmp_fullPuSize;

	local_jLoop = jLoop;
	tmp_fullPuSize = fullPuSize[1];
	result = local_jLoop == tmp_fullPuSize;
	return result;
}

static void getSamples_luma_done() {


	pixIdx = 0;
	compIdx = 1;
	jLoop = 0;

	// Update ports indexes

}
static i32 isSchedulable_getSamples_chroma_launch_is35() {
	i32 result;
	u8 local_compIdx;

	local_compIdx = compIdx;
	result = local_compIdx < 3;
	return result;
}

static void getSamples_chroma_launch_is35() {

	u8 local_compIdx;
	i32 i;
	u16 local_pixIdx;
	u8 tmp_Sample;
	i32 i0;
	u8 tmp_Sample0;
	u8 local_jLoop;
	u8 local_predCuSize;
	u8 tmp_fullPuSizeChr;

	local_compIdx = compIdx;
	if (local_compIdx == 1) {
		i = 0;
		while (i <= 34) {
			local_pixIdx = pixIdx;
			tmp_Sample = tokens_Sample[(index_Sample + (i)) % SIZE_Sample];
			refSamples_u[local_pixIdx + i] = tmp_Sample;
			i = i + 1;
		}
	} else {
		i0 = 0;
		while (i0 <= 34) {
			local_pixIdx = pixIdx;
			tmp_Sample0 = tokens_Sample[(index_Sample + (i0)) % SIZE_Sample];
			refSamples_v[local_pixIdx + i0] = tmp_Sample0;
			i0 = i0 + 1;
		}
	}
	local_jLoop = jLoop;
	jLoop = local_jLoop + 1;
	local_pixIdx = pixIdx;
	local_predCuSize = predCuSize;
	pixIdx = local_pixIdx + local_predCuSize / 2 + 3;
	local_jLoop = jLoop;
	tmp_fullPuSizeChr = fullPuSizeChr[1];
	if (local_jLoop == tmp_fullPuSizeChr) {
		pixIdx = 0;
		jLoop = 0;
		local_compIdx = compIdx;
		compIdx = local_compIdx + 1;
	}

	// Update ports indexes
	index_Sample += 35;
	read_end_Sample();

	rate_Sample += 35;
}
static void getSamples_chroma_launch_is35_aligned() {

	u8 local_compIdx;
	i32 i;
	u16 local_pixIdx;
	u8 tmp_Sample;
	i32 i0;
	u8 tmp_Sample0;
	u8 local_jLoop;
	u8 local_predCuSize;
	u8 tmp_fullPuSizeChr;

	local_compIdx = compIdx;
	if (local_compIdx == 1) {
		i = 0;
		while (i <= 34) {
			local_pixIdx = pixIdx;
			tmp_Sample = tokens_Sample[(index_Sample % SIZE_Sample) + (i)];
			refSamples_u[local_pixIdx + i] = tmp_Sample;
			i = i + 1;
		}
	} else {
		i0 = 0;
		while (i0 <= 34) {
			local_pixIdx = pixIdx;
			tmp_Sample0 = tokens_Sample[(index_Sample % SIZE_Sample) + (i0)];
			refSamples_v[local_pixIdx + i0] = tmp_Sample0;
			i0 = i0 + 1;
		}
	}
	local_jLoop = jLoop;
	jLoop = local_jLoop + 1;
	local_pixIdx = pixIdx;
	local_predCuSize = predCuSize;
	pixIdx = local_pixIdx + local_predCuSize / 2 + 3;
	local_jLoop = jLoop;
	tmp_fullPuSizeChr = fullPuSizeChr[1];
	if (local_jLoop == tmp_fullPuSizeChr) {
		pixIdx = 0;
		jLoop = 0;
		local_compIdx = compIdx;
		compIdx = local_compIdx + 1;
	}

	// Update ports indexes
	index_Sample += 35;
	read_end_Sample();

	rate_Sample += 35;
}
static i32 isSchedulable_getSamples_chroma_launch_is19() {
	i32 result;
	u8 local_compIdx;

	local_compIdx = compIdx;
	result = local_compIdx < 3;
	return result;
}

static void getSamples_chroma_launch_is19() {

	u8 local_compIdx;
	i32 i;
	u16 local_pixIdx;
	u8 tmp_Sample;
	i32 i0;
	u8 tmp_Sample0;
	u8 local_jLoop;
	u8 local_predCuSize;
	u8 tmp_fullPuSizeChr;

	local_compIdx = compIdx;
	if (local_compIdx == 1) {
		i = 0;
		while (i <= 18) {
			local_pixIdx = pixIdx;
			tmp_Sample = tokens_Sample[(index_Sample + (i)) % SIZE_Sample];
			refSamples_u[local_pixIdx + i] = tmp_Sample;
			i = i + 1;
		}
	} else {
		i0 = 0;
		while (i0 <= 18) {
			local_pixIdx = pixIdx;
			tmp_Sample0 = tokens_Sample[(index_Sample + (i0)) % SIZE_Sample];
			refSamples_v[local_pixIdx + i0] = tmp_Sample0;
			i0 = i0 + 1;
		}
	}
	local_jLoop = jLoop;
	jLoop = local_jLoop + 1;
	local_pixIdx = pixIdx;
	local_predCuSize = predCuSize;
	pixIdx = local_pixIdx + local_predCuSize / 2 + 3;
	local_jLoop = jLoop;
	tmp_fullPuSizeChr = fullPuSizeChr[1];
	if (local_jLoop == tmp_fullPuSizeChr) {
		pixIdx = 0;
		jLoop = 0;
		local_compIdx = compIdx;
		compIdx = local_compIdx + 1;
	}

	// Update ports indexes
	index_Sample += 19;
	read_end_Sample();

	rate_Sample += 19;
}
static void getSamples_chroma_launch_is19_aligned() {

	u8 local_compIdx;
	i32 i;
	u16 local_pixIdx;
	u8 tmp_Sample;
	i32 i0;
	u8 tmp_Sample0;
	u8 local_jLoop;
	u8 local_predCuSize;
	u8 tmp_fullPuSizeChr;

	local_compIdx = compIdx;
	if (local_compIdx == 1) {
		i = 0;
		while (i <= 18) {
			local_pixIdx = pixIdx;
			tmp_Sample = tokens_Sample[(index_Sample % SIZE_Sample) + (i)];
			refSamples_u[local_pixIdx + i] = tmp_Sample;
			i = i + 1;
		}
	} else {
		i0 = 0;
		while (i0 <= 18) {
			local_pixIdx = pixIdx;
			tmp_Sample0 = tokens_Sample[(index_Sample % SIZE_Sample) + (i0)];
			refSamples_v[local_pixIdx + i0] = tmp_Sample0;
			i0 = i0 + 1;
		}
	}
	local_jLoop = jLoop;
	jLoop = local_jLoop + 1;
	local_pixIdx = pixIdx;
	local_predCuSize = predCuSize;
	pixIdx = local_pixIdx + local_predCuSize / 2 + 3;
	local_jLoop = jLoop;
	tmp_fullPuSizeChr = fullPuSizeChr[1];
	if (local_jLoop == tmp_fullPuSizeChr) {
		pixIdx = 0;
		jLoop = 0;
		local_compIdx = compIdx;
		compIdx = local_compIdx + 1;
	}

	// Update ports indexes
	index_Sample += 19;
	read_end_Sample();

	rate_Sample += 19;
}
static i32 isSchedulable_getSamples_chroma_launch_is11() {
	i32 result;
	u8 local_compIdx;

	local_compIdx = compIdx;
	result = local_compIdx < 3;
	return result;
}

static void getSamples_chroma_launch_is11() {

	u8 local_compIdx;
	i32 i;
	u16 local_pixIdx;
	u8 tmp_Sample;
	i32 i0;
	u8 tmp_Sample0;
	u8 local_jLoop;
	u8 local_predCuSize;
	u8 tmp_fullPuSizeChr;

	local_compIdx = compIdx;
	if (local_compIdx == 1) {
		i = 0;
		while (i <= 10) {
			local_pixIdx = pixIdx;
			tmp_Sample = tokens_Sample[(index_Sample + (i)) % SIZE_Sample];
			refSamples_u[local_pixIdx + i] = tmp_Sample;
			i = i + 1;
		}
	} else {
		i0 = 0;
		while (i0 <= 10) {
			local_pixIdx = pixIdx;
			tmp_Sample0 = tokens_Sample[(index_Sample + (i0)) % SIZE_Sample];
			refSamples_v[local_pixIdx + i0] = tmp_Sample0;
			i0 = i0 + 1;
		}
	}
	local_jLoop = jLoop;
	jLoop = local_jLoop + 1;
	local_pixIdx = pixIdx;
	local_predCuSize = predCuSize;
	pixIdx = local_pixIdx + local_predCuSize / 2 + 3;
	local_jLoop = jLoop;
	tmp_fullPuSizeChr = fullPuSizeChr[1];
	if (local_jLoop == tmp_fullPuSizeChr) {
		pixIdx = 0;
		jLoop = 0;
		local_compIdx = compIdx;
		compIdx = local_compIdx + 1;
	}

	// Update ports indexes
	index_Sample += 11;
	read_end_Sample();

	rate_Sample += 11;
}
static void getSamples_chroma_launch_is11_aligned() {

	u8 local_compIdx;
	i32 i;
	u16 local_pixIdx;
	u8 tmp_Sample;
	i32 i0;
	u8 tmp_Sample0;
	u8 local_jLoop;
	u8 local_predCuSize;
	u8 tmp_fullPuSizeChr;

	local_compIdx = compIdx;
	if (local_compIdx == 1) {
		i = 0;
		while (i <= 10) {
			local_pixIdx = pixIdx;
			tmp_Sample = tokens_Sample[(index_Sample % SIZE_Sample) + (i)];
			refSamples_u[local_pixIdx + i] = tmp_Sample;
			i = i + 1;
		}
	} else {
		i0 = 0;
		while (i0 <= 10) {
			local_pixIdx = pixIdx;
			tmp_Sample0 = tokens_Sample[(index_Sample % SIZE_Sample) + (i0)];
			refSamples_v[local_pixIdx + i0] = tmp_Sample0;
			i0 = i0 + 1;
		}
	}
	local_jLoop = jLoop;
	jLoop = local_jLoop + 1;
	local_pixIdx = pixIdx;
	local_predCuSize = predCuSize;
	pixIdx = local_pixIdx + local_predCuSize / 2 + 3;
	local_jLoop = jLoop;
	tmp_fullPuSizeChr = fullPuSizeChr[1];
	if (local_jLoop == tmp_fullPuSizeChr) {
		pixIdx = 0;
		jLoop = 0;
		local_compIdx = compIdx;
		compIdx = local_compIdx + 1;
	}

	// Update ports indexes
	index_Sample += 11;
	read_end_Sample();

	rate_Sample += 11;
}
static i32 isSchedulable_getSamples_chroma_launch_is7() {
	i32 result;
	u8 local_compIdx;

	local_compIdx = compIdx;
	result = local_compIdx < 3;
	return result;
}

static void getSamples_chroma_launch_is7() {

	u8 local_compIdx;
	i32 i;
	u16 local_pixIdx;
	u8 tmp_Sample;
	i32 i0;
	u8 tmp_Sample0;
	u8 local_jLoop;
	u8 local_predCuSize;
	u8 tmp_fullPuSizeChr;

	local_compIdx = compIdx;
	if (local_compIdx == 1) {
		i = 0;
		while (i <= 6) {
			local_pixIdx = pixIdx;
			tmp_Sample = tokens_Sample[(index_Sample + (i)) % SIZE_Sample];
			refSamples_u[local_pixIdx + i] = tmp_Sample;
			i = i + 1;
		}
	} else {
		i0 = 0;
		while (i0 <= 6) {
			local_pixIdx = pixIdx;
			tmp_Sample0 = tokens_Sample[(index_Sample + (i0)) % SIZE_Sample];
			refSamples_v[local_pixIdx + i0] = tmp_Sample0;
			i0 = i0 + 1;
		}
	}
	local_jLoop = jLoop;
	jLoop = local_jLoop + 1;
	local_pixIdx = pixIdx;
	local_predCuSize = predCuSize;
	pixIdx = local_pixIdx + local_predCuSize / 2 + 3;
	local_jLoop = jLoop;
	tmp_fullPuSizeChr = fullPuSizeChr[1];
	if (local_jLoop == tmp_fullPuSizeChr) {
		pixIdx = 0;
		jLoop = 0;
		local_compIdx = compIdx;
		compIdx = local_compIdx + 1;
	}

	// Update ports indexes
	index_Sample += 7;
	read_end_Sample();

	rate_Sample += 7;
}
static void getSamples_chroma_launch_is7_aligned() {

	u8 local_compIdx;
	i32 i;
	u16 local_pixIdx;
	u8 tmp_Sample;
	i32 i0;
	u8 tmp_Sample0;
	u8 local_jLoop;
	u8 local_predCuSize;
	u8 tmp_fullPuSizeChr;

	local_compIdx = compIdx;
	if (local_compIdx == 1) {
		i = 0;
		while (i <= 6) {
			local_pixIdx = pixIdx;
			tmp_Sample = tokens_Sample[(index_Sample % SIZE_Sample) + (i)];
			refSamples_u[local_pixIdx + i] = tmp_Sample;
			i = i + 1;
		}
	} else {
		i0 = 0;
		while (i0 <= 6) {
			local_pixIdx = pixIdx;
			tmp_Sample0 = tokens_Sample[(index_Sample % SIZE_Sample) + (i0)];
			refSamples_v[local_pixIdx + i0] = tmp_Sample0;
			i0 = i0 + 1;
		}
	}
	local_jLoop = jLoop;
	jLoop = local_jLoop + 1;
	local_pixIdx = pixIdx;
	local_predCuSize = predCuSize;
	pixIdx = local_pixIdx + local_predCuSize / 2 + 3;
	local_jLoop = jLoop;
	tmp_fullPuSizeChr = fullPuSizeChr[1];
	if (local_jLoop == tmp_fullPuSizeChr) {
		pixIdx = 0;
		jLoop = 0;
		local_compIdx = compIdx;
		compIdx = local_compIdx + 1;
	}

	// Update ports indexes
	index_Sample += 7;
	read_end_Sample();

	rate_Sample += 7;
}
static i32 isSchedulable_getSamples_chroma_launch_is5() {
	i32 result;
	u8 local_compIdx;

	local_compIdx = compIdx;
	result = local_compIdx < 3;
	return result;
}

static void getSamples_chroma_launch_is5() {

	u8 local_compIdx;
	i32 i;
	u16 local_pixIdx;
	u8 tmp_Sample;
	i32 i0;
	u8 tmp_Sample0;
	u8 local_jLoop;
	u8 local_predCuSize;
	u8 tmp_fullPuSizeChr;

	local_compIdx = compIdx;
	if (local_compIdx == 1) {
		i = 0;
		while (i <= 4) {
			local_pixIdx = pixIdx;
			tmp_Sample = tokens_Sample[(index_Sample + (i)) % SIZE_Sample];
			refSamples_u[local_pixIdx + i] = tmp_Sample;
			i = i + 1;
		}
	} else {
		i0 = 0;
		while (i0 <= 4) {
			local_pixIdx = pixIdx;
			tmp_Sample0 = tokens_Sample[(index_Sample + (i0)) % SIZE_Sample];
			refSamples_v[local_pixIdx + i0] = tmp_Sample0;
			i0 = i0 + 1;
		}
	}
	local_jLoop = jLoop;
	jLoop = local_jLoop + 1;
	local_pixIdx = pixIdx;
	local_predCuSize = predCuSize;
	pixIdx = local_pixIdx + local_predCuSize / 2 + 3;
	local_jLoop = jLoop;
	tmp_fullPuSizeChr = fullPuSizeChr[1];
	if (local_jLoop == tmp_fullPuSizeChr) {
		pixIdx = 0;
		jLoop = 0;
		local_compIdx = compIdx;
		compIdx = local_compIdx + 1;
	}

	// Update ports indexes
	index_Sample += 5;
	read_end_Sample();

	rate_Sample += 5;
}
static void getSamples_chroma_launch_is5_aligned() {

	u8 local_compIdx;
	i32 i;
	u16 local_pixIdx;
	u8 tmp_Sample;
	i32 i0;
	u8 tmp_Sample0;
	u8 local_jLoop;
	u8 local_predCuSize;
	u8 tmp_fullPuSizeChr;

	local_compIdx = compIdx;
	if (local_compIdx == 1) {
		i = 0;
		while (i <= 4) {
			local_pixIdx = pixIdx;
			tmp_Sample = tokens_Sample[(index_Sample % SIZE_Sample) + (i)];
			refSamples_u[local_pixIdx + i] = tmp_Sample;
			i = i + 1;
		}
	} else {
		i0 = 0;
		while (i0 <= 4) {
			local_pixIdx = pixIdx;
			tmp_Sample0 = tokens_Sample[(index_Sample % SIZE_Sample) + (i0)];
			refSamples_v[local_pixIdx + i0] = tmp_Sample0;
			i0 = i0 + 1;
		}
	}
	local_jLoop = jLoop;
	jLoop = local_jLoop + 1;
	local_pixIdx = pixIdx;
	local_predCuSize = predCuSize;
	pixIdx = local_pixIdx + local_predCuSize / 2 + 3;
	local_jLoop = jLoop;
	tmp_fullPuSizeChr = fullPuSizeChr[1];
	if (local_jLoop == tmp_fullPuSizeChr) {
		pixIdx = 0;
		jLoop = 0;
		local_compIdx = compIdx;
		compIdx = local_compIdx + 1;
	}

	// Update ports indexes
	index_Sample += 5;
	read_end_Sample();

	rate_Sample += 5;
}
static i32 isSchedulable_getSamples_chroma_launch_is1() {
	i32 result;
	u8 local_compIdx;

	local_compIdx = compIdx;
	result = local_compIdx < 3;
	return result;
}

static void getSamples_chroma_launch_is1() {

	u8 sample;
	u8 local_compIdx;
	u16 local_pixIdx;
	u8 local_iLoop;
	u8 tmp_fullPuSizeChr;
	u8 local_jLoop;
	u16 tmp_pixIdxOff;
	u8 tmp_fullPuSizeChr0;
	u8 tmp_fullPuSizeChr1;

	sample = tokens_Sample[(index_Sample + (0)) % SIZE_Sample];
	local_compIdx = compIdx;
	if (local_compIdx == 1) {
		local_pixIdx = pixIdx;
		refSamples_u[local_pixIdx] = sample;
	} else {
		local_pixIdx = pixIdx;
		refSamples_v[local_pixIdx] = sample;
	}
	local_pixIdx = pixIdx;
	pixIdx = local_pixIdx + 1;
	local_iLoop = iLoop;
	iLoop = local_iLoop + 1;
	local_iLoop = iLoop;
	tmp_fullPuSizeChr = fullPuSizeChr[0];
	if (local_iLoop == tmp_fullPuSizeChr) {
		iLoop = 0;
		local_jLoop = jLoop;
		jLoop = local_jLoop + 1;
		local_pixIdx = pixIdx;
		tmp_pixIdxOff = pixIdxOff[1];
		tmp_fullPuSizeChr0 = fullPuSizeChr[0];
		pixIdx = local_pixIdx + tmp_pixIdxOff - tmp_fullPuSizeChr0;
		local_jLoop = jLoop;
		tmp_fullPuSizeChr1 = fullPuSizeChr[1];
		if (local_jLoop == tmp_fullPuSizeChr1) {
			pixIdx = 0;
			iLoop = 0;
			jLoop = 0;
			local_compIdx = compIdx;
			compIdx = local_compIdx + 1;
		}
	}

	// Update ports indexes
	index_Sample += 1;

	rate_Sample += 1;
}
static i32 isSchedulable_getSamples_chroma_done() {
	i32 result;
	u8 local_compIdx;

	local_compIdx = compIdx;
	result = local_compIdx == 3;
	return result;
}

static void getSamples_chroma_done() {



	// Update ports indexes

}
static i32 isSchedulable_interpolateSamples() {
	i32 result;

	result = 1;
	return result;
}

static void interpolateSamples() {

	u32 maskMv[3];
	i32 mvQuartPix[2];
	u8 compPuIdxMax[2];
	i32 i;
	u8 tmp_puSize;
	i32 component;
	i32 i0;
	u8 local_listIdx;
	i32 tmp_mvLx;
	u32 tmp_maskMv;
	u8 local_predCuSize;
	u8 tmp_compPuIdxMax;
	u8 tmp_compPuIdxMax0;
	i32 tmp_mvQuartPix;
	i32 tmp_mvQuartPix0;
	u8 tmp_compPuIdxMax1;
	u8 tmp_compPuIdxMax2;
	i32 tmp_mvQuartPix1;
	i32 tmp_mvQuartPix2;
	u8 tmp_compPuIdxMax3;
	u8 tmp_compPuIdxMax4;
	i32 tmp_mvQuartPix3;
	i32 tmp_mvQuartPix4;
	i32 i1;
	u8 tmp_puSize0;

	maskMv[0] = 3;
	maskMv[1] = 7;
	maskMv[2] = 7;
	i = 0;
	while (i <= 1) {
		tmp_puSize = puSize[i];
		compPuIdxMax[i] = tmp_puSize - 1;
		i = i + 1;
	}
	component = 0;
	while (component <= 2) {
		i0 = 0;
		while (i0 <= 1) {
			local_listIdx = listIdx;
			tmp_mvLx = mvLx[local_listIdx][i0];
			tmp_maskMv = maskMv[component];
			mvQuartPix[i0] = tmp_mvLx & tmp_maskMv;
			i0 = i0 + 1;
		}
		if (component == 0) {
			local_listIdx = listIdx;
			local_predCuSize = predCuSize;
			tmp_compPuIdxMax = compPuIdxMax[0];
			tmp_compPuIdxMax0 = compPuIdxMax[1];
			tmp_mvQuartPix = mvQuartPix[0];
			tmp_mvQuartPix0 = mvQuartPix[1];
			HevcDecoder_InterPrediction_put_hevc_qpel_cal(predSamples_y, local_listIdx, refSamples_y, local_predCuSize + 7, tmp_compPuIdxMax, tmp_compPuIdxMax0, tmp_mvQuartPix, tmp_mvQuartPix0);
		} else {
			if (component == 1) {
				local_listIdx = listIdx;
				local_predCuSize = predCuSize;
				tmp_compPuIdxMax1 = compPuIdxMax[0];
				tmp_compPuIdxMax2 = compPuIdxMax[1];
				tmp_mvQuartPix1 = mvQuartPix[0];
				tmp_mvQuartPix2 = mvQuartPix[1];
				HevcDecoder_InterPrediction_put_hevc_epel_cal(predSamples_u, local_listIdx, refSamples_u, (local_predCuSize >> 1) + 3, tmp_compPuIdxMax1, tmp_compPuIdxMax2, tmp_mvQuartPix1, tmp_mvQuartPix2);
			} else {
				local_listIdx = listIdx;
				local_predCuSize = predCuSize;
				tmp_compPuIdxMax3 = compPuIdxMax[0];
				tmp_compPuIdxMax4 = compPuIdxMax[1];
				tmp_mvQuartPix3 = mvQuartPix[0];
				tmp_mvQuartPix4 = mvQuartPix[1];
				HevcDecoder_InterPrediction_put_hevc_epel_cal(predSamples_v, local_listIdx, refSamples_v, (local_predCuSize >> 1) + 3, tmp_compPuIdxMax3, tmp_compPuIdxMax4, tmp_mvQuartPix3, tmp_mvQuartPix4);
			}
		}
		i1 = 0;
		while (i1 <= 1) {
			tmp_puSize0 = puSize[i1];
			compPuIdxMax[i1] = (tmp_puSize0 >> 1) - 1;
			i1 = i1 + 1;
		}
		component = component + 1;
	}
	local_listIdx = listIdx;
	listIdx = local_listIdx + 1;

	// Update ports indexes

}
static i32 isSchedulable_getAllSamples_done() {
	i32 result;
	u8 local_listIdx;
	u8 local_isBiPredOrLx;
	u8 local_PRED_L0;
	u8 local_numList;
	u8 local_BI_PRED;

	local_listIdx = listIdx;
	local_listIdx = listIdx;
	local_isBiPredOrLx = isBiPredOrLx;
	local_PRED_L0 = HevcDecoder_InterPrediction_PRED_L0;
	local_numList = numList;
	local_listIdx = listIdx;
	local_isBiPredOrLx = isBiPredOrLx;
	local_BI_PRED = HevcDecoder_InterPrediction_BI_PRED;
	result = local_listIdx == 2 || local_listIdx == 1 && local_isBiPredOrLx == local_PRED_L0 || local_numList == 1 && local_listIdx == 1 && local_isBiPredOrLx == local_BI_PRED;
	return result;
}

static void getAllSamples_done() {

	u8 compPuIdxMax[2];
	u8 local_isBiPredOrLx;
	u8 local_PRED_L1;
	u8 rdList;
	i32 i;
	u8 tmp_puSize;
	u8 local_numList;
	u8 local_wpIdc;
	u8 tmp_compPuIdxMax;
	u8 tmp_compPuIdxMax0;
	u8 tmp_compPuIdxMax1;
	u8 tmp_compPuIdxMax2;
	u8 tmp_compPuIdxMax3;
	u8 tmp_compPuIdxMax4;
	u8 local_BI_PRED;
	i32 local_logWD_y;
	u8 tmp_compPuIdxMax5;
	u8 tmp_compPuIdxMax6;
	i32 local_logWD_u;
	u8 tmp_compPuIdxMax7;
	u8 tmp_compPuIdxMax8;
	i32 local_logWD_v;
	u8 tmp_compPuIdxMax9;
	u8 tmp_compPuIdxMax10;
	u8 tmp_compPuIdxMax11;
	u8 tmp_compPuIdxMax12;
	u8 tmp_compPuIdxMax13;
	u8 tmp_compPuIdxMax14;
	u8 tmp_compPuIdxMax15;
	u8 tmp_compPuIdxMax16;
	u8 tmp_compPuIdxMax17;
	u8 tmp_compPuIdxMax18;
	u8 tmp_compPuIdxMax19;
	u8 tmp_compPuIdxMax20;
	u8 tmp_compPuIdxMax21;
	u8 tmp_compPuIdxMax22;
	u8 tmp_compPuIdxMax23;
	u8 tmp_compPuIdxMax24;
	u8 tmp_compPuIdxMax25;
	u8 tmp_compPuIdxMax26;
	u8 tmp_compPuIdxMax27;
	u8 tmp_compPuIdxMax28;

	local_isBiPredOrLx = isBiPredOrLx;
	local_PRED_L1 = HevcDecoder_InterPrediction_PRED_L1;
	if (local_isBiPredOrLx == local_PRED_L1) {
		rdList = 1;
	} else {
		rdList = 0;
	}
	i = 0;
	while (i <= 1) {
		tmp_puSize = puSize[i];
		compPuIdxMax[i] = tmp_puSize - 1;
		i = i + 1;
	}
	local_numList = numList;
	if (local_numList == 1) {
		local_wpIdc = wpIdc;
		if (local_wpIdc == 0) {
			tmp_compPuIdxMax = compPuIdxMax[0];
			tmp_compPuIdxMax0 = compPuIdxMax[1];
			HevcDecoder_InterPrediction_put_unweighted_pred(predSamples_y, tmp_compPuIdxMax, tmp_compPuIdxMax0, rdList, weightSamples_y);
			tmp_compPuIdxMax1 = compPuIdxMax[0];
			tmp_compPuIdxMax2 = compPuIdxMax[1];
			HevcDecoder_InterPrediction_put_unweighted_pred(predSamples_u, tmp_compPuIdxMax1, tmp_compPuIdxMax2, rdList, weightSamples_u);
			tmp_compPuIdxMax3 = compPuIdxMax[0];
			tmp_compPuIdxMax4 = compPuIdxMax[1];
			HevcDecoder_InterPrediction_put_unweighted_pred(predSamples_v, tmp_compPuIdxMax3, tmp_compPuIdxMax4, rdList, weightSamples_v);
		} else {
			local_isBiPredOrLx = isBiPredOrLx;
			local_BI_PRED = HevcDecoder_InterPrediction_BI_PRED;
			if (local_isBiPredOrLx != local_BI_PRED) {
				local_logWD_y = logWD_y;
				tmp_compPuIdxMax5 = compPuIdxMax[0];
				tmp_compPuIdxMax6 = compPuIdxMax[1];
				HevcDecoder_InterPrediction_weighted_pred(local_logWD_y, weightCu_y, offsetCu_y, predSamples_y, tmp_compPuIdxMax5, tmp_compPuIdxMax6, rdList, weightSamples_y);
				local_logWD_u = logWD_u;
				tmp_compPuIdxMax7 = compPuIdxMax[0];
				tmp_compPuIdxMax8 = compPuIdxMax[1];
				HevcDecoder_InterPrediction_weighted_pred(local_logWD_u, weightCu_u, offsetCu_u, predSamples_u, tmp_compPuIdxMax7, tmp_compPuIdxMax8, rdList, weightSamples_u);
				local_logWD_v = logWD_v;
				tmp_compPuIdxMax9 = compPuIdxMax[0];
				tmp_compPuIdxMax10 = compPuIdxMax[1];
				HevcDecoder_InterPrediction_weighted_pred(local_logWD_v, weightCu_v, offsetCu_v, predSamples_v, tmp_compPuIdxMax9, tmp_compPuIdxMax10, rdList, weightSamples_v);
			} else {
				local_logWD_y = logWD_y;
				tmp_compPuIdxMax11 = compPuIdxMax[0];
				tmp_compPuIdxMax12 = compPuIdxMax[1];
				HevcDecoder_InterPrediction_weighted_pred_mono(local_logWD_y, weightCu_y, offsetCu_y, predSamples_y, tmp_compPuIdxMax11, tmp_compPuIdxMax12, weightSamples_y);
				local_logWD_u = logWD_u;
				tmp_compPuIdxMax13 = compPuIdxMax[0];
				tmp_compPuIdxMax14 = compPuIdxMax[1];
				HevcDecoder_InterPrediction_weighted_pred_mono(local_logWD_u, weightCu_u, offsetCu_u, predSamples_u, tmp_compPuIdxMax13, tmp_compPuIdxMax14, weightSamples_u);
				local_logWD_v = logWD_v;
				tmp_compPuIdxMax15 = compPuIdxMax[0];
				tmp_compPuIdxMax16 = compPuIdxMax[1];
				HevcDecoder_InterPrediction_weighted_pred_mono(local_logWD_v, weightCu_v, offsetCu_v, predSamples_v, tmp_compPuIdxMax15, tmp_compPuIdxMax16, weightSamples_v);
			}
		}
	} else {
		local_wpIdc = wpIdc;
		if (local_wpIdc == 0) {
			tmp_compPuIdxMax17 = compPuIdxMax[0];
			tmp_compPuIdxMax18 = compPuIdxMax[1];
			HevcDecoder_InterPrediction_put_weighted_pred_avg(predSamples_y, tmp_compPuIdxMax17, tmp_compPuIdxMax18, weightSamples_y);
			tmp_compPuIdxMax19 = compPuIdxMax[0];
			tmp_compPuIdxMax20 = compPuIdxMax[1];
			HevcDecoder_InterPrediction_put_weighted_pred_avg(predSamples_u, tmp_compPuIdxMax19, tmp_compPuIdxMax20, weightSamples_u);
			tmp_compPuIdxMax21 = compPuIdxMax[0];
			tmp_compPuIdxMax22 = compPuIdxMax[1];
			HevcDecoder_InterPrediction_put_weighted_pred_avg(predSamples_v, tmp_compPuIdxMax21, tmp_compPuIdxMax22, weightSamples_v);
		} else {
			local_logWD_y = logWD_y;
			tmp_compPuIdxMax23 = compPuIdxMax[0];
			tmp_compPuIdxMax24 = compPuIdxMax[1];
			HevcDecoder_InterPrediction_weighted_pred_avg(local_logWD_y, weightCu_y, offsetCu_y, predSamples_y, tmp_compPuIdxMax23, tmp_compPuIdxMax24, weightSamples_y);
			local_logWD_u = logWD_u;
			tmp_compPuIdxMax25 = compPuIdxMax[0];
			tmp_compPuIdxMax26 = compPuIdxMax[1];
			HevcDecoder_InterPrediction_weighted_pred_avg(local_logWD_u, weightCu_u, offsetCu_u, predSamples_u, tmp_compPuIdxMax25, tmp_compPuIdxMax26, weightSamples_u);
			local_logWD_v = logWD_v;
			tmp_compPuIdxMax27 = compPuIdxMax[0];
			tmp_compPuIdxMax28 = compPuIdxMax[1];
			HevcDecoder_InterPrediction_weighted_pred_avg(local_logWD_v, weightCu_v, offsetCu_v, predSamples_v, tmp_compPuIdxMax27, tmp_compPuIdxMax28, weightSamples_v);
		}
	}
	iLoop = 0;
	jLoop = 0;

	// Update ports indexes

}
static i32 isSchedulable_sendCu_launch() {
	i32 result;
	u8 local_jLoop;
	u8 tmp_puSize;

	local_jLoop = jLoop;
	tmp_puSize = puSize[1];
	result = local_jLoop < tmp_puSize;
	return result;
}

static void sendCu_launch() {

	u32 y;
	u32 x;
	u8 local_iLoop;
	u8 local_jLoop;
	u8 tmp_puSize;
	u8 tmp_weightSamples_y;
	u32 y0;
	u32 x0;
	u8 tmp_puSize0;
	u8 tmp_weightSamples_u;
	u8 tmp_puSize1;
	u8 tmp_weightSamples_v;
	u8 tmp_puSize2;

	y = 0;
	while (y <= 3) {
		x = 0;
		while (x <= 3) {
			local_iLoop = iLoop;
			local_jLoop = jLoop;
			tmp_puSize = puSize[0];
			tmp_weightSamples_y = weightSamples_y[local_iLoop + x + (local_jLoop + y) * tmp_puSize];
			tokens_PredSample[(index_PredSample + (y * 4 + x)) % SIZE_PredSample] = tmp_weightSamples_y;
			x = x + 1;
		}
		y = y + 1;
	}
	y0 = 0;
	while (y0 <= 1) {
		x0 = 0;
		while (x0 <= 1) {
			local_iLoop = iLoop;
			local_jLoop = jLoop;
			tmp_puSize0 = puSize[0];
			tmp_weightSamples_u = weightSamples_u[local_iLoop / 2 + x0 + (local_jLoop / 2 + y0) * tmp_puSize0 / 2];
			tokens_PredSample[(index_PredSample + (16 + y0 * 2 + x0)) % SIZE_PredSample] = tmp_weightSamples_u;
			local_iLoop = iLoop;
			local_jLoop = jLoop;
			tmp_puSize1 = puSize[0];
			tmp_weightSamples_v = weightSamples_v[local_iLoop / 2 + x0 + (local_jLoop / 2 + y0) * tmp_puSize1 / 2];
			tokens_PredSample[(index_PredSample + (20 + y0 * 2 + x0)) % SIZE_PredSample] = tmp_weightSamples_v;
			x0 = x0 + 1;
		}
		y0 = y0 + 1;
	}
	local_iLoop = iLoop;
	iLoop = local_iLoop + 4;
	local_iLoop = iLoop;
	tmp_puSize2 = puSize[0];
	if (local_iLoop == tmp_puSize2) {
		iLoop = 0;
		local_jLoop = jLoop;
		jLoop = local_jLoop + 4;
	}

	// Update ports indexes
	index_PredSample += 24;
	write_end_PredSample();

}
static void sendCu_launch_aligned() {

	u32 y;
	u32 x;
	u8 local_iLoop;
	u8 local_jLoop;
	u8 tmp_puSize;
	u8 tmp_weightSamples_y;
	u32 y0;
	u32 x0;
	u8 tmp_puSize0;
	u8 tmp_weightSamples_u;
	u8 tmp_puSize1;
	u8 tmp_weightSamples_v;
	u8 tmp_puSize2;

	y = 0;
	while (y <= 3) {
		x = 0;
		while (x <= 3) {
			local_iLoop = iLoop;
			local_jLoop = jLoop;
			tmp_puSize = puSize[0];
			tmp_weightSamples_y = weightSamples_y[local_iLoop + x + (local_jLoop + y) * tmp_puSize];
			tokens_PredSample[(index_PredSample % SIZE_PredSample) + (y * 4 + x)] = tmp_weightSamples_y;
			x = x + 1;
		}
		y = y + 1;
	}
	y0 = 0;
	while (y0 <= 1) {
		x0 = 0;
		while (x0 <= 1) {
			local_iLoop = iLoop;
			local_jLoop = jLoop;
			tmp_puSize0 = puSize[0];
			tmp_weightSamples_u = weightSamples_u[local_iLoop / 2 + x0 + (local_jLoop / 2 + y0) * tmp_puSize0 / 2];
			tokens_PredSample[(index_PredSample % SIZE_PredSample) + (16 + y0 * 2 + x0)] = tmp_weightSamples_u;
			local_iLoop = iLoop;
			local_jLoop = jLoop;
			tmp_puSize1 = puSize[0];
			tmp_weightSamples_v = weightSamples_v[local_iLoop / 2 + x0 + (local_jLoop / 2 + y0) * tmp_puSize1 / 2];
			tokens_PredSample[(index_PredSample % SIZE_PredSample) + (20 + y0 * 2 + x0)] = tmp_weightSamples_v;
			x0 = x0 + 1;
		}
		y0 = y0 + 1;
	}
	local_iLoop = iLoop;
	iLoop = local_iLoop + 4;
	local_iLoop = iLoop;
	tmp_puSize2 = puSize[0];
	if (local_iLoop == tmp_puSize2) {
		iLoop = 0;
		local_jLoop = jLoop;
		jLoop = local_jLoop + 4;
	}

	// Update ports indexes
	index_PredSample += 24;
	write_end_PredSample();

}
static i32 isSchedulable_sendCu_done() {
	i32 result;
	u8 local_jLoop;
	u8 tmp_puSize;

	local_jLoop = jLoop;
	tmp_puSize = puSize[1];
	result = local_jLoop == tmp_puSize;
	return result;
}

static void sendCu_done() {


	iLoop = 0;
	jLoop = 0;

	// Update ports indexes

}

////////////////////////////////////////////////////////////////////////////////
// Initializes

void HevcDecoder_InterPrediction_initialize(schedinfo_t *si) {
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

void HevcDecoder_InterPrediction_scheduler(schedinfo_t *si) {
	int i = 0;

	read_CUInfo();
	read_IsBiPredOrLx();
	read_Mv();
	read_PartMode();
	read_Poc();
	read_RefIdx();
	read_RefList();
	read_Sample();
	read_SliceType();
	read_WeightedPredSe();
	write_PredSample();

	// jump to FSM state
	switch (_FSM_state) {
	case my_state_CheckChromaWidth:
		goto l_CheckChromaWidth;
	case my_state_CheckLumaWidth:
		goto l_CheckLumaWidth;
	case my_state_GetChromaSamples:
		goto l_GetChromaSamples;
	case my_state_GetChromaSamples11:
		goto l_GetChromaSamples11;
	case my_state_GetChromaSamples19:
		goto l_GetChromaSamples19;
	case my_state_GetChromaSamples35:
		goto l_GetChromaSamples35;
	case my_state_GetChromaSamples5:
		goto l_GetChromaSamples5;
	case my_state_GetChromaSamples7:
		goto l_GetChromaSamples7;
	case my_state_GetChromaWeightLX:
		goto l_GetChromaWeightLX;
	case my_state_GetCuInfo:
		goto l_GetCuInfo;
	case my_state_GetCuMode:
		goto l_GetCuMode;
	case my_state_GetDeltaChrWtLX:
		goto l_GetDeltaChrWtLX;
	case my_state_GetDeltaLumWtLX:
		goto l_GetDeltaLumWtLX;
	case my_state_GetLumaSamples:
		goto l_GetLumaSamples;
	case my_state_GetLumaSamples11:
		goto l_GetLumaSamples11;
	case my_state_GetLumaSamples15:
		goto l_GetLumaSamples15;
	case my_state_GetLumaSamples23:
		goto l_GetLumaSamples23;
	case my_state_GetLumaSamples39:
		goto l_GetLumaSamples39;
	case my_state_GetLumaSamples71:
		goto l_GetLumaSamples71;
	case my_state_GetLumaWeightLX:
		goto l_GetLumaWeightLX;
	case my_state_GetPartMode:
		goto l_GetPartMode;
	case my_state_GetRefIdx:
		goto l_GetRefIdx;
	case my_state_GetRefList:
		goto l_GetRefList;
	case my_state_GetSamples:
		goto l_GetSamples;
	case my_state_GetSizeRefList:
		goto l_GetSizeRefList;
	case my_state_GetWeightDenom:
		goto l_GetWeightDenom;
	case my_state_GetWeightLX:
		goto l_GetWeightLX;
	case my_state_InterpolateSamples:
		goto l_InterpolateSamples;
	case my_state_SendCu:
		goto l_SendCu;
	default:
		printf("unknown state in HevcDecoder_InterPrediction.c : %s\n", stateNames[_FSM_state]);
		exit(1);
	}

	// FSM transitions
l_CheckChromaWidth:
	if (isSchedulable_chromaWidth_is35()) {
		chromaWidth_is35();
		i++;
		goto l_GetChromaSamples35;
	} else if (isSchedulable_chromaWidth_is19()) {
		chromaWidth_is19();
		i++;
		goto l_GetChromaSamples19;
	} else if (isSchedulable_chromaWidth_is11()) {
		chromaWidth_is11();
		i++;
		goto l_GetChromaSamples11;
	} else if (isSchedulable_chromaWidth_is7()) {
		chromaWidth_is7();
		i++;
		goto l_GetChromaSamples7;
	} else if (isSchedulable_chromaWidth_is5()) {
		chromaWidth_is5();
		i++;
		goto l_GetChromaSamples5;
	} else if (isSchedulable_valWidth_isOther()) {
		valWidth_isOther();
		i++;
		goto l_GetChromaSamples;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_CheckChromaWidth;
		goto finished;
	}
l_CheckLumaWidth:
	if (isSchedulable_lumaWidth_is71()) {
		lumaWidth_is71();
		i++;
		goto l_GetLumaSamples71;
	} else if (isSchedulable_lumaWidth_is39()) {
		lumaWidth_is39();
		i++;
		goto l_GetLumaSamples39;
	} else if (isSchedulable_lumaWidth_is23()) {
		lumaWidth_is23();
		i++;
		goto l_GetLumaSamples23;
	} else if (isSchedulable_lumaWidth_is15()) {
		lumaWidth_is15();
		i++;
		goto l_GetLumaSamples15;
	} else if (isSchedulable_lumaWidth_is11()) {
		lumaWidth_is11();
		i++;
		goto l_GetLumaSamples11;
	} else if (isSchedulable_valWidth_isOther()) {
		valWidth_isOther();
		i++;
		goto l_GetLumaSamples;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_CheckLumaWidth;
		goto finished;
	}
l_GetChromaSamples:
	if (numTokens_Sample - index_Sample >= 1 && isSchedulable_getSamples_chroma_launch_is1()) {
		getSamples_chroma_launch_is1();
		i++;
		goto l_GetChromaSamples;
	} else if (isSchedulable_getSamples_chroma_done()) {
		getSamples_chroma_done();
		i++;
		goto l_InterpolateSamples;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetChromaSamples;
		goto finished;
	}
l_GetChromaSamples11:
	if (numTokens_Sample - index_Sample >= 11 && isSchedulable_getSamples_chroma_launch_is11()) {
		{
			int isAligned = 1;
			isAligned &= ((index_Sample % SIZE_Sample) < ((index_Sample + 11) % SIZE_Sample));
			if (isAligned) {
				getSamples_chroma_launch_is11_aligned();
			} else {
				getSamples_chroma_launch_is11();
			}
		}
		i++;
		goto l_GetChromaSamples11;
	} else if (isSchedulable_getSamples_chroma_done()) {
		getSamples_chroma_done();
		i++;
		goto l_InterpolateSamples;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetChromaSamples11;
		goto finished;
	}
l_GetChromaSamples19:
	if (numTokens_Sample - index_Sample >= 19 && isSchedulable_getSamples_chroma_launch_is19()) {
		{
			int isAligned = 1;
			isAligned &= ((index_Sample % SIZE_Sample) < ((index_Sample + 19) % SIZE_Sample));
			if (isAligned) {
				getSamples_chroma_launch_is19_aligned();
			} else {
				getSamples_chroma_launch_is19();
			}
		}
		i++;
		goto l_GetChromaSamples19;
	} else if (isSchedulable_getSamples_chroma_done()) {
		getSamples_chroma_done();
		i++;
		goto l_InterpolateSamples;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetChromaSamples19;
		goto finished;
	}
l_GetChromaSamples35:
	if (numTokens_Sample - index_Sample >= 35 && isSchedulable_getSamples_chroma_launch_is35()) {
		{
			int isAligned = 1;
			isAligned &= ((index_Sample % SIZE_Sample) < ((index_Sample + 35) % SIZE_Sample));
			if (isAligned) {
				getSamples_chroma_launch_is35_aligned();
			} else {
				getSamples_chroma_launch_is35();
			}
		}
		i++;
		goto l_GetChromaSamples35;
	} else if (isSchedulable_getSamples_chroma_done()) {
		getSamples_chroma_done();
		i++;
		goto l_InterpolateSamples;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetChromaSamples35;
		goto finished;
	}
l_GetChromaSamples5:
	if (numTokens_Sample - index_Sample >= 5 && isSchedulable_getSamples_chroma_launch_is5()) {
		{
			int isAligned = 1;
			isAligned &= ((index_Sample % SIZE_Sample) < ((index_Sample + 5) % SIZE_Sample));
			if (isAligned) {
				getSamples_chroma_launch_is5_aligned();
			} else {
				getSamples_chroma_launch_is5();
			}
		}
		i++;
		goto l_GetChromaSamples5;
	} else if (isSchedulable_getSamples_chroma_done()) {
		getSamples_chroma_done();
		i++;
		goto l_InterpolateSamples;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetChromaSamples5;
		goto finished;
	}
l_GetChromaSamples7:
	if (numTokens_Sample - index_Sample >= 7 && isSchedulable_getSamples_chroma_launch_is7()) {
		{
			int isAligned = 1;
			isAligned &= ((index_Sample % SIZE_Sample) < ((index_Sample + 7) % SIZE_Sample));
			if (isAligned) {
				getSamples_chroma_launch_is7_aligned();
			} else {
				getSamples_chroma_launch_is7();
			}
		}
		i++;
		goto l_GetChromaSamples7;
	} else if (isSchedulable_getSamples_chroma_done()) {
		getSamples_chroma_done();
		i++;
		goto l_InterpolateSamples;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetChromaSamples7;
		goto finished;
	}
l_GetChromaWeightLX:
	if (numTokens_WeightedPredSe - index_WeightedPredSe >= 1 && isSchedulable_getChromaWeightLX_launch()) {
		getChromaWeightLX_launch();
		i++;
		goto l_GetChromaWeightLX;
	} else if (isSchedulable_getChromaWeightLX_done()) {
		getChromaWeightLX_done();
		i++;
		goto l_GetDeltaLumWtLX;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetChromaWeightLX;
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
	if (isSchedulable_getCuMode_isNotInter()) {
		getCuMode_isNotInter();
		i++;
		goto l_GetCuInfo;
	} else if (numTokens_IsBiPredOrLx - index_IsBiPredOrLx >= 1 && isSchedulable_getCuMode_isInter()) {
		getCuMode_isInter();
		i++;
		goto l_GetRefIdx;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetCuMode;
		goto finished;
	}
l_GetDeltaChrWtLX:
	if (numTokens_WeightedPredSe - index_WeightedPredSe >= 4 && isSchedulable_getDeltaChromaWeight_launch()) {
		{
			int isAligned = 1;
			isAligned &= ((index_WeightedPredSe % SIZE_WeightedPredSe) < ((index_WeightedPredSe + 4) % SIZE_WeightedPredSe));
			if (isAligned) {
				getDeltaChromaWeight_launch_aligned();
			} else {
				getDeltaChromaWeight_launch();
			}
		}
		i++;
		goto l_GetDeltaLumWtLX;
	} else if (isSchedulable_getDeltaChromaWeight_skip()) {
		getDeltaChromaWeight_skip();
		i++;
		goto l_GetDeltaLumWtLX;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetDeltaChrWtLX;
		goto finished;
	}
l_GetDeltaLumWtLX:
	if (numTokens_WeightedPredSe - index_WeightedPredSe >= 2 && isSchedulable_getDeltaLumaWeight_launch()) {
		{
			int isAligned = 1;
			isAligned &= ((index_WeightedPredSe % SIZE_WeightedPredSe) < ((index_WeightedPredSe + 2) % SIZE_WeightedPredSe));
			if (isAligned) {
				getDeltaLumaWeight_launch_aligned();
			} else {
				getDeltaLumaWeight_launch();
			}
		}
		i++;
		goto l_GetDeltaChrWtLX;
	} else if (isSchedulable_getDeltaLumaWeight_skip()) {
		getDeltaLumaWeight_skip();
		i++;
		goto l_GetDeltaChrWtLX;
	} else if (isSchedulable_getDeltaLumaWeight_done()) {
		getDeltaLumaWeight_done();
		i++;
		goto l_GetWeightLX;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetDeltaLumWtLX;
		goto finished;
	}
l_GetLumaSamples:
	if (numTokens_Sample - index_Sample >= 1 && isSchedulable_getSamples_luma_launch_is1()) {
		getSamples_luma_launch_is1();
		i++;
		goto l_GetLumaSamples;
	} else if (isSchedulable_getSamples_luma_done()) {
		getSamples_luma_done();
		i++;
		goto l_CheckChromaWidth;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetLumaSamples;
		goto finished;
	}
l_GetLumaSamples11:
	if (numTokens_Sample - index_Sample >= 11 && isSchedulable_getSamples_luma_launch_is11()) {
		{
			int isAligned = 1;
			isAligned &= ((index_Sample % SIZE_Sample) < ((index_Sample + 11) % SIZE_Sample));
			if (isAligned) {
				getSamples_luma_launch_is11_aligned();
			} else {
				getSamples_luma_launch_is11();
			}
		}
		i++;
		goto l_GetLumaSamples11;
	} else if (isSchedulable_getSamples_luma_done()) {
		getSamples_luma_done();
		i++;
		goto l_CheckChromaWidth;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetLumaSamples11;
		goto finished;
	}
l_GetLumaSamples15:
	if (numTokens_Sample - index_Sample >= 15 && isSchedulable_getSamples_luma_launch_is15()) {
		{
			int isAligned = 1;
			isAligned &= ((index_Sample % SIZE_Sample) < ((index_Sample + 15) % SIZE_Sample));
			if (isAligned) {
				getSamples_luma_launch_is15_aligned();
			} else {
				getSamples_luma_launch_is15();
			}
		}
		i++;
		goto l_GetLumaSamples15;
	} else if (isSchedulable_getSamples_luma_done()) {
		getSamples_luma_done();
		i++;
		goto l_CheckChromaWidth;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetLumaSamples15;
		goto finished;
	}
l_GetLumaSamples23:
	if (numTokens_Sample - index_Sample >= 23 && isSchedulable_getSamples_luma_launch_is23()) {
		{
			int isAligned = 1;
			isAligned &= ((index_Sample % SIZE_Sample) < ((index_Sample + 23) % SIZE_Sample));
			if (isAligned) {
				getSamples_luma_launch_is23_aligned();
			} else {
				getSamples_luma_launch_is23();
			}
		}
		i++;
		goto l_GetLumaSamples23;
	} else if (isSchedulable_getSamples_luma_done()) {
		getSamples_luma_done();
		i++;
		goto l_CheckChromaWidth;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetLumaSamples23;
		goto finished;
	}
l_GetLumaSamples39:
	if (numTokens_Sample - index_Sample >= 39 && isSchedulable_getSamples_luma_launch_is39()) {
		{
			int isAligned = 1;
			isAligned &= ((index_Sample % SIZE_Sample) < ((index_Sample + 39) % SIZE_Sample));
			if (isAligned) {
				getSamples_luma_launch_is39_aligned();
			} else {
				getSamples_luma_launch_is39();
			}
		}
		i++;
		goto l_GetLumaSamples39;
	} else if (isSchedulable_getSamples_luma_done()) {
		getSamples_luma_done();
		i++;
		goto l_CheckChromaWidth;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetLumaSamples39;
		goto finished;
	}
l_GetLumaSamples71:
	if (numTokens_Sample - index_Sample >= 71 && isSchedulable_getSamples_luma_launch_is71()) {
		{
			int isAligned = 1;
			isAligned &= ((index_Sample % SIZE_Sample) < ((index_Sample + 71) % SIZE_Sample));
			if (isAligned) {
				getSamples_luma_launch_is71_aligned();
			} else {
				getSamples_luma_launch_is71();
			}
		}
		i++;
		goto l_GetLumaSamples71;
	} else if (isSchedulable_getSamples_luma_done()) {
		getSamples_luma_done();
		i++;
		goto l_CheckChromaWidth;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetLumaSamples71;
		goto finished;
	}
l_GetLumaWeightLX:
	if (numTokens_WeightedPredSe - index_WeightedPredSe >= 1 && isSchedulable_getLumaWeightLX_launch()) {
		getLumaWeightLX_launch();
		i++;
		goto l_GetLumaWeightLX;
	} else if (isSchedulable_getLumaWeightLX_done()) {
		getLumaWeightLX_done();
		i++;
		goto l_GetChromaWeightLX;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetLumaWeightLX;
		goto finished;
	}
l_GetPartMode:
	if (numTokens_PartMode - index_PartMode >= 1 && isSchedulable_getPartMode()) {
		getPartMode();
		i++;
		goto l_GetCuInfo;
	} else if (numTokens_PartMode - index_PartMode >= 1 && isSchedulable_isNewSlice_dep()) {
		isNewSlice_dep();
		i++;
		goto l_GetPartMode;
	} else if (numTokens_PartMode - index_PartMode >= 1 && numTokens_Poc - index_Poc >= 1 && numTokens_SliceType - index_SliceType >= 1 && numTokens_WeightedPredSe - index_WeightedPredSe >= 1 && isSchedulable_isNewSlice_notDep()) {
		isNewSlice_notDep();
		i++;
		goto l_GetSizeRefList;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetPartMode;
		goto finished;
	}
l_GetRefIdx:
	if (numTokens_RefIdx - index_RefIdx >= 1 && numTokens_Mv - index_Mv >= 2 && isSchedulable_getRefIdx_monoPred()) {
		{
			int isAligned = 1;
			isAligned &= ((index_Mv % SIZE_Mv) < ((index_Mv + 2) % SIZE_Mv));
			if (isAligned) {
				getRefIdx_monoPred_aligned();
			} else {
				getRefIdx_monoPred();
			}
		}
		i++;
		goto l_GetSamples;
	} else if (numTokens_RefIdx - index_RefIdx >= 2 && numTokens_Mv - index_Mv >= 4 && isSchedulable_getRefIdx_biPred()) {
		{
			int isAligned = 1;
			isAligned &= ((index_RefIdx % SIZE_RefIdx) < ((index_RefIdx + 2) % SIZE_RefIdx));
			isAligned &= ((index_Mv % SIZE_Mv) < ((index_Mv + 4) % SIZE_Mv));
			if (isAligned) {
				getRefIdx_biPred_aligned();
			} else {
				getRefIdx_biPred();
			}
		}
		i++;
		goto l_GetSamples;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetRefIdx;
		goto finished;
	}
l_GetRefList:
	if (numTokens_RefList - index_RefList >= 1 && isSchedulable_getRefList_launch()) {
		getRefList_launch();
		i++;
		goto l_GetRefList;
	} else if (isSchedulable_getRefList_done()) {
		getRefList_done();
		i++;
		goto l_GetSizeRefList;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetRefList;
		goto finished;
	}
l_GetSamples:
	if (isSchedulable_getAllSamples_launch()) {
		getAllSamples_launch();
		i++;
		goto l_CheckLumaWidth;
	} else if (isSchedulable_getAllSamples_done()) {
		getAllSamples_done();
		i++;
		goto l_SendCu;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetSamples;
		goto finished;
	}
l_GetSizeRefList:
	if (numTokens_RefList - index_RefList >= 1 && isSchedulable_getSizeRefList_launch()) {
		getSizeRefList_launch();
		i++;
		goto l_GetRefList;
	} else if (isSchedulable_getSizeRefList_done()) {
		getSizeRefList_done();
		i++;
		goto l_GetWeightDenom;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetSizeRefList;
		goto finished;
	}
l_GetWeightDenom:
	if (numTokens_WeightedPredSe - index_WeightedPredSe >= 2 && isSchedulable_getWeightDenom_launch()) {
		{
			int isAligned = 1;
			isAligned &= ((index_WeightedPredSe % SIZE_WeightedPredSe) < ((index_WeightedPredSe + 2) % SIZE_WeightedPredSe));
			if (isAligned) {
				getWeightDenom_launch_aligned();
			} else {
				getWeightDenom_launch();
			}
		}
		i++;
		goto l_GetWeightLX;
	} else if (isSchedulable_getWeightDenom_skip()) {
		getWeightDenom_skip();
		i++;
		goto l_GetPartMode;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetWeightDenom;
		goto finished;
	}
l_GetWeightLX:
	if (isSchedulable_getWeightLX_launch()) {
		getWeightLX_launch();
		i++;
		goto l_GetLumaWeightLX;
	} else if (isSchedulable_getWeightLX_skip()) {
		getWeightLX_skip();
		i++;
		goto l_GetWeightLX;
	} else if (isSchedulable_getWeightLX_done()) {
		getWeightLX_done();
		i++;
		goto l_GetPartMode;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetWeightLX;
		goto finished;
	}
l_InterpolateSamples:
	if (isSchedulable_interpolateSamples()) {
		interpolateSamples();
		i++;
		goto l_GetSamples;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_InterpolateSamples;
		goto finished;
	}
l_SendCu:
	if (isSchedulable_sendCu_launch()) {
		int stop = 0;
		if (24 > SIZE_PredSample - index_PredSample + HevcDecoder_InterPrediction_PredSample->read_inds[0]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_SendCu;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		{
			int isAligned = 1;
			isAligned &= ((index_PredSample % SIZE_PredSample) < ((index_PredSample + 24) % SIZE_PredSample));
			if (isAligned) {
				sendCu_launch_aligned();
			} else {
				sendCu_launch();
			}
		}
		i++;
		goto l_SendCu;
	} else if (isSchedulable_sendCu_done()) {
		sendCu_done();
		i++;
		goto l_GetCuInfo;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_SendCu;
		goto finished;
	}
finished:
	read_end_CUInfo();
	read_end_IsBiPredOrLx();
	read_end_Mv();
	read_end_PartMode();
	read_end_Poc();
	read_end_RefIdx();
	read_end_RefList();
	read_end_Sample();
	read_end_SliceType();
	read_end_WeightedPredSe();
	write_end_PredSample();
}
