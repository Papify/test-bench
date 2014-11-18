// Source file is "L/RVC/src/org/sc29/wg11/mpegh/part2/main/inter/MvComponentPred.cal"

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
extern actor_t HevcDecoder_generateInfo_MvComponentPred;

////////////////////////////////////////////////////////////////////////////////
// Input FIFOs
extern fifo_u16_t *HevcDecoder_generateInfo_MvComponentPred_CUInfo;
extern fifo_u8_t *HevcDecoder_generateInfo_MvComponentPred_LcuSizeMax;
extern fifo_u8_t *HevcDecoder_generateInfo_MvComponentPred_PartMode;
extern fifo_u16_t *HevcDecoder_generateInfo_MvComponentPred_PicSize;
extern fifo_i16_t *HevcDecoder_generateInfo_MvComponentPred_Poc;
extern fifo_i16_t *HevcDecoder_generateInfo_MvComponentPred_RefList;
extern fifo_i16_t *HevcDecoder_generateInfo_MvComponentPred_RpsPoc;
extern fifo_u16_t *HevcDecoder_generateInfo_MvComponentPred_SliceAddr;
extern fifo_u8_t *HevcDecoder_generateInfo_MvComponentPred_SliceType;
extern fifo_i16_t *HevcDecoder_generateInfo_MvComponentPred_SyntaxElem;
extern fifo_u16_t *HevcDecoder_generateInfo_MvComponentPred_TilesCoord;

////////////////////////////////////////////////////////////////////////////////
// Input Fifo control variables
static unsigned int index_CUInfo;
static unsigned int numTokens_CUInfo;
#define SIZE_CUInfo SIZE
#define tokens_CUInfo HevcDecoder_generateInfo_MvComponentPred_CUInfo->contents

extern connection_t connection_HevcDecoder_generateInfo_MvComponentPred_CUInfo;
#define rate_CUInfo connection_HevcDecoder_generateInfo_MvComponentPred_CUInfo.rate

static unsigned int index_LcuSizeMax;
static unsigned int numTokens_LcuSizeMax;
#define SIZE_LcuSizeMax SIZE
#define tokens_LcuSizeMax HevcDecoder_generateInfo_MvComponentPred_LcuSizeMax->contents

extern connection_t connection_HevcDecoder_generateInfo_MvComponentPred_LcuSizeMax;
#define rate_LcuSizeMax connection_HevcDecoder_generateInfo_MvComponentPred_LcuSizeMax.rate

static unsigned int index_PartMode;
static unsigned int numTokens_PartMode;
#define SIZE_PartMode SIZE
#define tokens_PartMode HevcDecoder_generateInfo_MvComponentPred_PartMode->contents

extern connection_t connection_HevcDecoder_generateInfo_MvComponentPred_PartMode;
#define rate_PartMode connection_HevcDecoder_generateInfo_MvComponentPred_PartMode.rate

static unsigned int index_PicSize;
static unsigned int numTokens_PicSize;
#define SIZE_PicSize SIZE
#define tokens_PicSize HevcDecoder_generateInfo_MvComponentPred_PicSize->contents

extern connection_t connection_HevcDecoder_generateInfo_MvComponentPred_PicSize;
#define rate_PicSize connection_HevcDecoder_generateInfo_MvComponentPred_PicSize.rate

static unsigned int index_Poc;
static unsigned int numTokens_Poc;
#define SIZE_Poc SIZE
#define tokens_Poc HevcDecoder_generateInfo_MvComponentPred_Poc->contents

extern connection_t connection_HevcDecoder_generateInfo_MvComponentPred_Poc;
#define rate_Poc connection_HevcDecoder_generateInfo_MvComponentPred_Poc.rate

static unsigned int index_RefList;
static unsigned int numTokens_RefList;
#define SIZE_RefList SIZE
#define tokens_RefList HevcDecoder_generateInfo_MvComponentPred_RefList->contents

extern connection_t connection_HevcDecoder_generateInfo_MvComponentPred_RefList;
#define rate_RefList connection_HevcDecoder_generateInfo_MvComponentPred_RefList.rate

static unsigned int index_RpsPoc;
static unsigned int numTokens_RpsPoc;
#define SIZE_RpsPoc SIZE
#define tokens_RpsPoc HevcDecoder_generateInfo_MvComponentPred_RpsPoc->contents

extern connection_t connection_HevcDecoder_generateInfo_MvComponentPred_RpsPoc;
#define rate_RpsPoc connection_HevcDecoder_generateInfo_MvComponentPred_RpsPoc.rate

static unsigned int index_SliceAddr;
static unsigned int numTokens_SliceAddr;
#define SIZE_SliceAddr SIZE
#define tokens_SliceAddr HevcDecoder_generateInfo_MvComponentPred_SliceAddr->contents

extern connection_t connection_HevcDecoder_generateInfo_MvComponentPred_SliceAddr;
#define rate_SliceAddr connection_HevcDecoder_generateInfo_MvComponentPred_SliceAddr.rate

static unsigned int index_SliceType;
static unsigned int numTokens_SliceType;
#define SIZE_SliceType SIZE
#define tokens_SliceType HevcDecoder_generateInfo_MvComponentPred_SliceType->contents

extern connection_t connection_HevcDecoder_generateInfo_MvComponentPred_SliceType;
#define rate_SliceType connection_HevcDecoder_generateInfo_MvComponentPred_SliceType.rate

static unsigned int index_SyntaxElem;
static unsigned int numTokens_SyntaxElem;
#define SIZE_SyntaxElem SIZE
#define tokens_SyntaxElem HevcDecoder_generateInfo_MvComponentPred_SyntaxElem->contents

extern connection_t connection_HevcDecoder_generateInfo_MvComponentPred_SyntaxElem;
#define rate_SyntaxElem connection_HevcDecoder_generateInfo_MvComponentPred_SyntaxElem.rate

static unsigned int index_TilesCoord;
static unsigned int numTokens_TilesCoord;
#define SIZE_TilesCoord SIZE
#define tokens_TilesCoord HevcDecoder_generateInfo_MvComponentPred_TilesCoord->contents

extern connection_t connection_HevcDecoder_generateInfo_MvComponentPred_TilesCoord;
#define rate_TilesCoord connection_HevcDecoder_generateInfo_MvComponentPred_TilesCoord.rate

////////////////////////////////////////////////////////////////////////////////
// Predecessors
extern actor_t HevcDecoder_Algo_Parser;
extern actor_t HevcDecoder_Algo_Parser;
extern actor_t HevcDecoder_Algo_Parser;
extern actor_t HevcDecoder_Algo_Parser;
extern actor_t HevcDecoder_Algo_Parser;
extern actor_t HevcDecoder_generateInfo_GenerateRefList;
extern actor_t HevcDecoder_Algo_Parser;
extern actor_t HevcDecoder_Algo_Parser;
extern actor_t HevcDecoder_Algo_Parser;
extern actor_t HevcDecoder_Algo_Parser;
extern actor_t HevcDecoder_Algo_Parser;

////////////////////////////////////////////////////////////////////////////////
// Output FIFOs
extern fifo_u8_t *HevcDecoder_generateInfo_MvComponentPred_IsBiPredOrLx;
extern fifo_u8_t *HevcDecoder_generateInfo_MvComponentPred_IsReadOrNewSlice;
extern fifo_i32_t *HevcDecoder_generateInfo_MvComponentPred_Mv;
extern fifo_i16_t *HevcDecoder_generateInfo_MvComponentPred_PocRef;
extern fifo_u8_t *HevcDecoder_generateInfo_MvComponentPred_PredCuSize;
extern fifo_u8_t *HevcDecoder_generateInfo_MvComponentPred_RefIdx;

////////////////////////////////////////////////////////////////////////////////
// Output Fifo control variables
static unsigned int index_IsBiPredOrLx;
static unsigned int numFree_IsBiPredOrLx;
#define NUM_READERS_IsBiPredOrLx 3
#define SIZE_IsBiPredOrLx SIZE
#define tokens_IsBiPredOrLx HevcDecoder_generateInfo_MvComponentPred_IsBiPredOrLx->contents

static unsigned int index_IsReadOrNewSlice;
static unsigned int numFree_IsReadOrNewSlice;
#define NUM_READERS_IsReadOrNewSlice 1
#define SIZE_IsReadOrNewSlice SIZE
#define tokens_IsReadOrNewSlice HevcDecoder_generateInfo_MvComponentPred_IsReadOrNewSlice->contents

static unsigned int index_Mv;
static unsigned int numFree_Mv;
#define NUM_READERS_Mv 3
#define SIZE_Mv SIZE
#define tokens_Mv HevcDecoder_generateInfo_MvComponentPred_Mv->contents

static unsigned int index_PocRef;
static unsigned int numFree_PocRef;
#define NUM_READERS_PocRef 2
#define SIZE_PocRef SIZE
#define tokens_PocRef HevcDecoder_generateInfo_MvComponentPred_PocRef->contents

static unsigned int index_PredCuSize;
static unsigned int numFree_PredCuSize;
#define NUM_READERS_PredCuSize 1
#define SIZE_PredCuSize SIZE
#define tokens_PredCuSize HevcDecoder_generateInfo_MvComponentPred_PredCuSize->contents

static unsigned int index_RefIdx;
static unsigned int numFree_RefIdx;
#define NUM_READERS_RefIdx 1
#define SIZE_RefIdx SIZE
#define tokens_RefIdx HevcDecoder_generateInfo_MvComponentPred_RefIdx->contents

////////////////////////////////////////////////////////////////////////////////
// Successors
extern actor_t HevcDecoder_InterPrediction;
extern actor_t HevcDecoder_DecodingPictureBuffer;
extern actor_t HevcDecoder_DBFilter_GenerateBs;
extern actor_t HevcDecoder_DecodingPictureBuffer;
extern actor_t HevcDecoder_InterPrediction;
extern actor_t HevcDecoder_DecodingPictureBuffer;
extern actor_t HevcDecoder_DBFilter_GenerateBs;
extern actor_t HevcDecoder_DecodingPictureBuffer;
extern actor_t HevcDecoder_DBFilter_GenerateBs;
extern actor_t HevcDecoder_DecodingPictureBuffer;
extern actor_t HevcDecoder_InterPrediction;


////////////////////////////////////////////////////////////////////////////////
// State variables of the actor
#define HevcDecoder_generateInfo_MvComponentPred_PART_2NxnD 5
#define HevcDecoder_generateInfo_MvComponentPred_PART_2NxnU 4
#define HevcDecoder_generateInfo_MvComponentPred_PART_nLx2N 6
#define HevcDecoder_generateInfo_MvComponentPred_PART_nRx2N 7
#define HevcDecoder_generateInfo_MvComponentPred_PART_Nx2N 2
#define HevcDecoder_generateInfo_MvComponentPred_PART_MODE_SLICE_DEP 9
#define HevcDecoder_generateInfo_MvComponentPred_PART_MODE_SLICE_INDEP 10
#define HevcDecoder_generateInfo_MvComponentPred_PART_MODE_PICT 8
#define HevcDecoder_generateInfo_MvComponentPred_B_SLICE 0
#define HevcDecoder_generateInfo_MvComponentPred_MIN_INT16 -32768
#define HevcDecoder_generateInfo_MvComponentPred_PICT_WIDTH_POW_2 4096
static const u8 HevcDecoder_generateInfo_MvComponentPred_partModeToNumPart[8] = {1, 2, 2, 4, 2, 2, 2, 2};
static const u8 HevcDecoder_generateInfo_MvComponentPred_absCoordInBlkToZScanTable[16][16] = {{0, 1, 4, 5, 16, 17, 20, 21, 64, 65, 68, 69, 80, 81, 84, 85}, {2, 3, 6, 7, 18, 19, 22, 23, 66, 67, 70, 71, 82, 83, 86, 87}, {8, 9, 12, 13, 24, 25, 28, 29, 72, 73, 76, 77, 88, 89, 92, 93}, {10, 11, 14, 15, 26, 27, 30, 31, 74, 75, 78, 79, 90, 91, 94, 95}, {32, 33, 36, 37, 48, 49, 52, 53, 96, 97, 100, 101, 112, 113, 116, 117}, {34, 35, 38, 39, 50, 51, 54, 55, 98, 99, 102, 103, 114, 115, 118, 119}, {40, 41, 44, 45, 56, 57, 60, 61, 104, 105, 108, 109, 120, 121, 124, 125}, {42, 43, 46, 47, 58, 59, 62, 63, 106, 107, 110, 111, 122, 123, 126, 127}, {128, 129, 132, 133, 144, 145, 148, 149, 192, 193, 196, 197, 208, 209, 212, 213}, {130, 131, 134, 135, 146, 147, 150, 151, 194, 195, 198, 199, 210, 211, 214, 215}, {136, 137, 140, 141, 152, 153, 156, 157, 200, 201, 204, 205, 216, 217, 220, 221}, {138, 139, 142, 143, 154, 155, 158, 159, 202, 203, 206, 207, 218, 219, 222, 223}, {160, 161, 164, 165, 176, 177, 180, 181, 224, 225, 228, 229, 240, 241, 244, 245}, {162, 163, 166, 167, 178, 179, 182, 183, 226, 227, 230, 231, 242, 243, 246, 247}, {168, 169, 172, 173, 184, 185, 188, 189, 232, 233, 236, 237, 248, 249, 252, 253}, {170, 171, 174, 175, 186, 187, 190, 191, 234, 235, 238, 239, 250, 251, 254, 255}};
#define HevcDecoder_generateInfo_MvComponentPred_INTER 0
#define HevcDecoder_generateInfo_MvComponentPred_SKIP 2
#define HevcDecoder_generateInfo_MvComponentPred_PART_2Nx2N 0
#define HevcDecoder_generateInfo_MvComponentPred_PART_2NxN 1
#define HevcDecoder_generateInfo_MvComponentPred_BI_PRED 2
#define HevcDecoder_generateInfo_MvComponentPred_PRED_L0 0
#define HevcDecoder_generateInfo_MvComponentPred_PRED_L1 1
#define DEBUG_CUInfo 0
#define DEBUG_PartMode 0
#define DEBUG_PicSize 0
#define DEBUG_RefList 0
#define DEBUG_RpsPoc 0
#define DEBUG_SyntaxElem 0
#define DEBUG_Mv 0
#define LEFT_BOTTOM 0
#define LEFT 1
#define ABOVE_RIGHT 2
#define ABOVE 3
#define ABOVE_LEFT 4
#define RIGHT_BOTTOM 5
#define CENTER 6
static const u8 combIdxToLXCandIdx[16][2] = {{0, 1}, {1, 0}, {0, 2}, {2, 0}, {1, 2}, {2, 1}, {0, 3}, {3, 0}, {1, 3}, {3, 1}, {2, 3}, {3, 2}};
#define L -1
#define R 1
#define U -64
#define D 64
#define UL -65
#define UR -63
#define DL 63
#define DR 65
static const i16 neighbLcuAddr[18][18] = {{-65, -64, -64, -64, -64, -64, -64, -64, -64, -64, -64, -64, -64, -64, -64, -64, -64, -63}, {-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {63, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 65}};
static const u16 neighbBlkAddr[18][18] = {{255, 170, 171, 174, 175, 186, 187, 190, 191, 234, 235, 238, 239, 250, 251, 254, 255, 170}, {85, 0, 1, 4, 5, 16, 17, 20, 21, 64, 65, 68, 69, 80, 81, 84, 85, 0}, {87, 2, 3, 6, 7, 18, 19, 22, 23, 66, 67, 70, 71, 82, 83, 86, 87, 2}, {93, 8, 9, 12, 13, 24, 25, 28, 29, 72, 73, 76, 77, 88, 89, 92, 93, 8}, {95, 10, 11, 14, 15, 26, 27, 30, 31, 74, 75, 78, 79, 90, 91, 94, 95, 10}, {117, 32, 33, 36, 37, 48, 49, 52, 53, 96, 97, 100, 101, 112, 113, 116, 117, 32}, {119, 34, 35, 38, 39, 50, 51, 54, 55, 98, 99, 102, 103, 114, 115, 118, 119, 34}, {125, 40, 41, 44, 45, 56, 57, 60, 61, 104, 105, 108, 109, 120, 121, 124, 125, 40}, {127, 42, 43, 46, 47, 58, 59, 62, 63, 106, 107, 110, 111, 122, 123, 126, 127, 42}, {213, 128, 129, 132, 133, 144, 145, 148, 149, 192, 193, 196, 197, 208, 209, 212, 213, 128}, {215, 130, 131, 134, 135, 146, 147, 150, 151, 194, 195, 198, 199, 210, 211, 214, 215, 130}, {221, 136, 137, 140, 141, 152, 153, 156, 157, 200, 201, 204, 205, 216, 217, 220, 221, 136}, {223, 138, 139, 142, 143, 154, 155, 158, 159, 202, 203, 206, 207, 218, 219, 222, 223, 138}, {245, 160, 161, 164, 165, 176, 177, 180, 181, 224, 225, 228, 229, 240, 241, 244, 245, 160}, {247, 162, 163, 166, 167, 178, 179, 182, 183, 226, 227, 230, 231, 242, 243, 246, 247, 162}, {253, 168, 169, 172, 173, 184, 185, 188, 189, 232, 233, 236, 237, 248, 249, 252, 253, 168}, {255, 170, 171, 174, 175, 186, 187, 190, 191, 234, 235, 238, 239, 250, 251, 254, 255, 170}, {85, 0, 1, 4, 5, 16, 17, 20, 21, 64, 65, 68, 69, 80, 81, 84, 85, 0}};
static u8 cuPartMode;
static i32 mergeIdx;
static i32 mvpIdx[2];
static i32 colPoc;
static i32 colRefIdx;
static u8 colocFromL0;
static u8 numPart;
static u8 numPartDecoded;
static u8 listIdx;
static u8 listSize;
static u8 sizeIdx;
static i16 maxPoc;
static i32 picSizeInPart[2];
static i32 useLN;
static i32 isBSlice;
static i32 partAddr[2];
static i32 partAddr1stPu[2];
static i32 cuAddr[2];
static u8 cuMode;
static i32 mvPred[5][2][2];
static i16 mvVal[2][2];
static i32 refIdxPred[5][2];
static i16 pocRef[17];
static u16 numSlcPerPict[17];
static i16 pocRefList[17][128][2][16];
static u16 slcAddrRef[17][128][2];
static i8 refIdxRef[17][2048][256][2];
static i16 mvRef[17][2048][256][2][2];
static i32 neighbLocation[2];
static i32 neighbLocIdx[2];
static i32 nPSH;
static i32 nPSW;
static i32 isRef[17];
static i32 isStillRef[17];
static i8 currIdx;
static u16 slcIdx;
static i16 colSlcIdx;
static i32 predFlag;
static i8 paralMergeLvl;
static i32 numCandidate;
static u32 sizeOfList;
static u32 nbList;
static u8 minSizeRefListX;
static i16 pocRefListX[2][16];
static u8 isBiPredOrLx;
static u8 predCuSize;
static u8 puSize[2];
static u8 cuSize[2];
static i32 enTmpMvp;
static u16 slcAddr[2];
static i32 dependSlc;
static i32 newPict;
static i16 iLoop;
static u16 numTiles;
static u16 tilesBeg[128][2];
static u16 tilesEnd[128][2];
static i16 puTilesBeg[2];
static i16 puTilesEnd[2];
static u8 lcuSizeMaxInPart;
static u8 maskLcuSzMax;
static u16 lcuAddr;
static u16 puAddrInLcu;
static u16 puAbsAddrInLcu[2];
static u16 puAbsAddrInLcu1stPu[2];

////////////////////////////////////////////////////////////////////////////////
// Initial FSM state of the actor
enum states {
	my_state_CheckIndepSlc,
	my_state_CheckMergeIdx,
	my_state_GetCuInfo,
	my_state_GetCuMode,
	my_state_GetMvd,
	my_state_GetPartMode,
	my_state_GetRefList,
	my_state_GetRps,
	my_state_GetRpsPoc,
	my_state_GetSizeRefList,
	my_state_GetTilesCoord,
	my_state_Send2ndMv
};

static char *stateNames[] = {
	"CheckIndepSlc",
	"CheckMergeIdx",
	"GetCuInfo",
	"GetCuMode",
	"GetMvd",
	"GetPartMode",
	"GetRefList",
	"GetRps",
	"GetRpsPoc",
	"GetSizeRefList",
	"GetTilesCoord",
	"Send2ndMv"
};

static enum states _FSM_state;



////////////////////////////////////////////////////////////////////////////////
// Token functions
static void read_CUInfo() {
	index_CUInfo = HevcDecoder_generateInfo_MvComponentPred_CUInfo->read_inds[3];
	numTokens_CUInfo = index_CUInfo + fifo_u16_get_num_tokens(HevcDecoder_generateInfo_MvComponentPred_CUInfo, 3);
}

static void read_end_CUInfo() {
	HevcDecoder_generateInfo_MvComponentPred_CUInfo->read_inds[3] = index_CUInfo;
}
static void read_LcuSizeMax() {
	index_LcuSizeMax = HevcDecoder_generateInfo_MvComponentPred_LcuSizeMax->read_inds[2];
	numTokens_LcuSizeMax = index_LcuSizeMax + fifo_u8_get_num_tokens(HevcDecoder_generateInfo_MvComponentPred_LcuSizeMax, 2);
}

static void read_end_LcuSizeMax() {
	HevcDecoder_generateInfo_MvComponentPred_LcuSizeMax->read_inds[2] = index_LcuSizeMax;
}
static void read_PartMode() {
	index_PartMode = HevcDecoder_generateInfo_MvComponentPred_PartMode->read_inds[3];
	numTokens_PartMode = index_PartMode + fifo_u8_get_num_tokens(HevcDecoder_generateInfo_MvComponentPred_PartMode, 3);
}

static void read_end_PartMode() {
	HevcDecoder_generateInfo_MvComponentPred_PartMode->read_inds[3] = index_PartMode;
}
static void read_PicSize() {
	index_PicSize = HevcDecoder_generateInfo_MvComponentPred_PicSize->read_inds[3];
	numTokens_PicSize = index_PicSize + fifo_u16_get_num_tokens(HevcDecoder_generateInfo_MvComponentPred_PicSize, 3);
}

static void read_end_PicSize() {
	HevcDecoder_generateInfo_MvComponentPred_PicSize->read_inds[3] = index_PicSize;
}
static void read_Poc() {
	index_Poc = HevcDecoder_generateInfo_MvComponentPred_Poc->read_inds[2];
	numTokens_Poc = index_Poc + fifo_i16_get_num_tokens(HevcDecoder_generateInfo_MvComponentPred_Poc, 2);
}

static void read_end_Poc() {
	HevcDecoder_generateInfo_MvComponentPred_Poc->read_inds[2] = index_Poc;
}
static void read_RefList() {
	index_RefList = HevcDecoder_generateInfo_MvComponentPred_RefList->read_inds[0];
	numTokens_RefList = index_RefList + fifo_i16_get_num_tokens(HevcDecoder_generateInfo_MvComponentPred_RefList, 0);
}

static void read_end_RefList() {
	HevcDecoder_generateInfo_MvComponentPred_RefList->read_inds[0] = index_RefList;
}
static void read_RpsPoc() {
	index_RpsPoc = HevcDecoder_generateInfo_MvComponentPred_RpsPoc->read_inds[2];
	numTokens_RpsPoc = index_RpsPoc + fifo_i16_get_num_tokens(HevcDecoder_generateInfo_MvComponentPred_RpsPoc, 2);
}

static void read_end_RpsPoc() {
	HevcDecoder_generateInfo_MvComponentPred_RpsPoc->read_inds[2] = index_RpsPoc;
}
static void read_SliceAddr() {
	index_SliceAddr = HevcDecoder_generateInfo_MvComponentPred_SliceAddr->read_inds[1];
	numTokens_SliceAddr = index_SliceAddr + fifo_u16_get_num_tokens(HevcDecoder_generateInfo_MvComponentPred_SliceAddr, 1);
}

static void read_end_SliceAddr() {
	HevcDecoder_generateInfo_MvComponentPred_SliceAddr->read_inds[1] = index_SliceAddr;
}
static void read_SliceType() {
	index_SliceType = HevcDecoder_generateInfo_MvComponentPred_SliceType->read_inds[1];
	numTokens_SliceType = index_SliceType + fifo_u8_get_num_tokens(HevcDecoder_generateInfo_MvComponentPred_SliceType, 1);
}

static void read_end_SliceType() {
	HevcDecoder_generateInfo_MvComponentPred_SliceType->read_inds[1] = index_SliceType;
}
static void read_SyntaxElem() {
	index_SyntaxElem = HevcDecoder_generateInfo_MvComponentPred_SyntaxElem->read_inds[0];
	numTokens_SyntaxElem = index_SyntaxElem + fifo_i16_get_num_tokens(HevcDecoder_generateInfo_MvComponentPred_SyntaxElem, 0);
}

static void read_end_SyntaxElem() {
	HevcDecoder_generateInfo_MvComponentPred_SyntaxElem->read_inds[0] = index_SyntaxElem;
}
static void read_TilesCoord() {
	index_TilesCoord = HevcDecoder_generateInfo_MvComponentPred_TilesCoord->read_inds[2];
	numTokens_TilesCoord = index_TilesCoord + fifo_u16_get_num_tokens(HevcDecoder_generateInfo_MvComponentPred_TilesCoord, 2);
}

static void read_end_TilesCoord() {
	HevcDecoder_generateInfo_MvComponentPred_TilesCoord->read_inds[2] = index_TilesCoord;
}

static void write_IsBiPredOrLx() {
	index_IsBiPredOrLx = HevcDecoder_generateInfo_MvComponentPred_IsBiPredOrLx->write_ind;
	numFree_IsBiPredOrLx = index_IsBiPredOrLx + fifo_u8_get_room(HevcDecoder_generateInfo_MvComponentPred_IsBiPredOrLx, NUM_READERS_IsBiPredOrLx, SIZE_IsBiPredOrLx);
}

static void write_end_IsBiPredOrLx() {
	HevcDecoder_generateInfo_MvComponentPred_IsBiPredOrLx->write_ind = index_IsBiPredOrLx;
}
static void write_IsReadOrNewSlice() {
	index_IsReadOrNewSlice = HevcDecoder_generateInfo_MvComponentPred_IsReadOrNewSlice->write_ind;
	numFree_IsReadOrNewSlice = index_IsReadOrNewSlice + fifo_u8_get_room(HevcDecoder_generateInfo_MvComponentPred_IsReadOrNewSlice, NUM_READERS_IsReadOrNewSlice, SIZE_IsReadOrNewSlice);
}

static void write_end_IsReadOrNewSlice() {
	HevcDecoder_generateInfo_MvComponentPred_IsReadOrNewSlice->write_ind = index_IsReadOrNewSlice;
}
static void write_Mv() {
	index_Mv = HevcDecoder_generateInfo_MvComponentPred_Mv->write_ind;
	numFree_Mv = index_Mv + fifo_i32_get_room(HevcDecoder_generateInfo_MvComponentPred_Mv, NUM_READERS_Mv, SIZE_Mv);
}

static void write_end_Mv() {
	HevcDecoder_generateInfo_MvComponentPred_Mv->write_ind = index_Mv;
}
static void write_PocRef() {
	index_PocRef = HevcDecoder_generateInfo_MvComponentPred_PocRef->write_ind;
	numFree_PocRef = index_PocRef + fifo_i16_get_room(HevcDecoder_generateInfo_MvComponentPred_PocRef, NUM_READERS_PocRef, SIZE_PocRef);
}

static void write_end_PocRef() {
	HevcDecoder_generateInfo_MvComponentPred_PocRef->write_ind = index_PocRef;
}
static void write_PredCuSize() {
	index_PredCuSize = HevcDecoder_generateInfo_MvComponentPred_PredCuSize->write_ind;
	numFree_PredCuSize = index_PredCuSize + fifo_u8_get_room(HevcDecoder_generateInfo_MvComponentPred_PredCuSize, NUM_READERS_PredCuSize, SIZE_PredCuSize);
}

static void write_end_PredCuSize() {
	HevcDecoder_generateInfo_MvComponentPred_PredCuSize->write_ind = index_PredCuSize;
}
static void write_RefIdx() {
	index_RefIdx = HevcDecoder_generateInfo_MvComponentPred_RefIdx->write_ind;
	numFree_RefIdx = index_RefIdx + fifo_u8_get_room(HevcDecoder_generateInfo_MvComponentPred_RefIdx, NUM_READERS_RefIdx, SIZE_RefIdx);
}

static void write_end_RefIdx() {
	HevcDecoder_generateInfo_MvComponentPred_RefIdx->write_ind = index_RefIdx;
}

////////////////////////////////////////////////////////////////////////////////
// Functions/procedures
static i32 HevcDecoder_generateInfo_MvComponentPred_clip_i32(i32 Value, i32 minVal, i32 maxVal);
static i32 HevcDecoder_generateInfo_MvComponentPred_abs(i32 x);
static i32 HevcDecoder_generateInfo_MvComponentPred_max(i32 a, i32 b);
static u16 HevcDecoder_generateInfo_MvComponentPred_absCoordInBlkToZScan(u16 addr[2]);
static i32 HevcDecoder_generateInfo_MvComponentPred_castBoolToInt(i32 a);
static i32 HevcDecoder_generateInfo_MvComponentPred_min(i32 a, i32 b);
static i32 isInter(i32 xN, i32 yN, i32 neighbLcuAddr, i32 neighbBlkAddr);
static i32 getIsAvailable();
static i32 checkSameComp(i32 orig[2], i32 neighb[2]);
static i32 hasNotSameMvComp(i32 orig[2], i32 neighb[2]);
static void searchColSlcAddr(i32 partAddr[2]);
static void saveRefIdx(i32 refIdxToSave[2], u8 cuSize[2], u8 cuPartMode, u8 numPartDecoded, i8 refIdxRef[17][2048][256][2], i8 currIdx, u16 lcuAddr, u16 puAddrInLcu);
static void saveMvComponent(i16 mvToSave[2][2], u8 cuSize[2], u8 cuPartMode, u8 numPartDecoded, i16 mvRef[17][2048][256][2][2], i8 currIdx, u16 lcuAddr, u16 puAddrInLcu);
static void getNeighbAddr(i32 location, i32 depSlcOrCol, i32 isColNeighb);
static void getNonMergedNeighbourMv(u32 listX);
static void getNeighbourMv_MergeIdx_isNotEqToMin1();
static void getNeighbourMvNonMergedNonScaled(u32 listX);
static void getNeighbourMvNonMergedScaled(u32 listX);
static void getNonMergedScaledMv(u32 listX);
static void mvScaling(i32 mv[2], i32 refIdxRefCurrPic, u32 listAvail, u32 listX, u32 pictIdx, i16 refList[2][16], i32 isColPict);
static void getColCandidate(i32 isMerged, u32 listX);
static void getColNeighbourMv(i32 isMerged, u32 listX);
static void biPredMergeCand(u32 maxNumCandidate);

static i32 HevcDecoder_generateInfo_MvComponentPred_clip_i32(i32 Value, i32 minVal, i32 maxVal) {
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
static i32 HevcDecoder_generateInfo_MvComponentPred_abs(i32 x) {
	i32 tmp_if;

	if (x > 0) {
		tmp_if = x;
	} else {
		tmp_if = -x;
	}
	return tmp_if;
}
static i32 HevcDecoder_generateInfo_MvComponentPred_max(i32 a, i32 b) {
	i32 tmp_if;

	if (a > b) {
		tmp_if = a;
	} else {
		tmp_if = b;
	}
	return tmp_if;
}
static u16 HevcDecoder_generateInfo_MvComponentPred_absCoordInBlkToZScan(u16 addr[2]) {
	u16 tmp_addr;
	u16 tmp_addr0;
	u8 tmp_absCoordInBlkToZScanTable;

	tmp_addr = addr[1];
	tmp_addr0 = addr[0];
	tmp_absCoordInBlkToZScanTable = HevcDecoder_generateInfo_MvComponentPred_absCoordInBlkToZScanTable[tmp_addr][tmp_addr0];
	return tmp_absCoordInBlkToZScanTable;
}
static i32 HevcDecoder_generateInfo_MvComponentPred_castBoolToInt(i32 a) {
	u8 tmp_if;

	if (a) {
		tmp_if = 1;
	} else {
		tmp_if = 0;
	}
	return tmp_if;
}
static i32 HevcDecoder_generateInfo_MvComponentPred_min(i32 a, i32 b) {
	i32 tmp_if;

	if (a < b) {
		tmp_if = a;
	} else {
		tmp_if = b;
	}
	return tmp_if;
}
static i32 isInter(i32 xN, i32 yN, i32 neighbLcuAddr, i32 neighbBlkAddr) {
	i32 tmp_if;
	i32 local_dependSlc;
	u16 tmp_slcAddr;
	u16 tmp_slcAddr0;
	u8 local_lcuSizeMaxInPart;
	u16 tmp_slcAddr1;
	i16 tmp_puTilesBeg;
	i16 tmp_puTilesEnd;
	i16 tmp_puTilesBeg0;
	i16 tmp_puTilesEnd0;
	i8 local_currIdx;
	i8 tmp_refIdxRef;
	i8 tmp_refIdxRef0;

	if (xN >= 0) {
		local_dependSlc = dependSlc;
		tmp_slcAddr = slcAddr[1];
		tmp_slcAddr0 = slcAddr[1];
		local_lcuSizeMaxInPart = lcuSizeMaxInPart;
		tmp_slcAddr1 = slcAddr[0];
		if (local_dependSlc || !(yN < tmp_slcAddr || yN < tmp_slcAddr0 + local_lcuSizeMaxInPart && xN < tmp_slcAddr1)) {
			tmp_puTilesBeg = puTilesBeg[0];
			tmp_puTilesEnd = puTilesEnd[0];
			tmp_puTilesBeg0 = puTilesBeg[1];
			tmp_puTilesEnd0 = puTilesEnd[1];
			if (xN >= tmp_puTilesBeg && xN < tmp_puTilesEnd && yN >= tmp_puTilesBeg0 && yN < tmp_puTilesEnd0) {
				local_currIdx = currIdx;
				tmp_refIdxRef = refIdxRef[local_currIdx][neighbLcuAddr][neighbBlkAddr][0];
				local_currIdx = currIdx;
				tmp_refIdxRef0 = refIdxRef[local_currIdx][neighbLcuAddr][neighbBlkAddr][1];
				tmp_if = tmp_refIdxRef != -1 || tmp_refIdxRef0 != -1;
			} else {
				tmp_if = 0;
			}
		} else {
			tmp_if = 0;
		}
	} else {
		tmp_if = 0;
	}
	return tmp_if;
}
static i32 getIsAvailable() {
	i32 neighbLcuAddr;
	i32 neighbBlkAddr;
	i32 tmp_if;
	i8 local_currIdx;
	i8 tmp_refIdxRef;
	i8 tmp_refIdxRef0;

	neighbLcuAddr = neighbLocIdx[0];
	neighbBlkAddr = neighbLocIdx[1];
	if (neighbLcuAddr >= 0) {
		local_currIdx = currIdx;
		tmp_refIdxRef = refIdxRef[local_currIdx][neighbLcuAddr][neighbBlkAddr][0];
		local_currIdx = currIdx;
		tmp_refIdxRef0 = refIdxRef[local_currIdx][neighbLcuAddr][neighbBlkAddr][1];
		tmp_if = tmp_refIdxRef != -1 || tmp_refIdxRef0 != -1;
	} else {
		tmp_if = 0;
	}
	return tmp_if;
}
static i32 checkSameComp(i32 orig[2], i32 neighb[2]) {
	i32 lcuAddrOrig;
	i32 blkAddrOrig;
	i32 lcuAddrNeighb;
	i32 blkAddrNeighb;
	i32 i;
	i8 local_currIdx;
	i8 tmp_refIdxRef;
	i32 refIdxCurrCu[2];
	i32 i0;
	i8 tmp_refIdxRef0;
	i32 refIdxNeighb[2];
	i32 i1;
	i32 j;
	i16 tmp_mvRef;
	i32 mvCurrCu[2][2];
	i32 i2;
	i32 j0;
	i16 tmp_mvRef0;
	i32 mvNeighb[2][2];
	i32 tmp_refIdxCurrCu;
	i32 tmp_refIdxNeighb;
	i32 tmp_refIdxCurrCu0;
	i32 tmp_refIdxNeighb0;
	i32 tmp_refIdxCurrCu1;
	i32 tmp_mvCurrCu;
	i32 tmp_mvNeighb;
	i32 tmp_mvCurrCu0;
	i32 tmp_mvNeighb0;
	i32 tmp_refIdxCurrCu2;
	i32 tmp_mvCurrCu1;
	i32 tmp_mvNeighb1;
	i32 tmp_mvCurrCu2;
	i32 tmp_mvNeighb2;

	lcuAddrOrig = orig[0];
	blkAddrOrig = orig[1];
	lcuAddrNeighb = neighb[0];
	blkAddrNeighb = neighb[1];
	i = 0;
	while (i <= 1) {
		local_currIdx = currIdx;
		tmp_refIdxRef = refIdxRef[local_currIdx][lcuAddrOrig][blkAddrOrig][i];
		refIdxCurrCu[i] = tmp_refIdxRef;
		i = i + 1;
	}
	i0 = 0;
	while (i0 <= 1) {
		local_currIdx = currIdx;
		tmp_refIdxRef0 = refIdxRef[local_currIdx][lcuAddrNeighb][blkAddrNeighb][i0];
		refIdxNeighb[i0] = tmp_refIdxRef0;
		i0 = i0 + 1;
	}
	i1 = 0;
	while (i1 <= 1) {
		j = 0;
		while (j <= 1) {
			local_currIdx = currIdx;
			tmp_mvRef = mvRef[local_currIdx][lcuAddrOrig][blkAddrOrig][i1][j];
			mvCurrCu[i1][j] = tmp_mvRef;
			j = j + 1;
		}
		i1 = i1 + 1;
	}
	i2 = 0;
	while (i2 <= 1) {
		j0 = 0;
		while (j0 <= 1) {
			local_currIdx = currIdx;
			tmp_mvRef0 = mvRef[local_currIdx][lcuAddrNeighb][blkAddrNeighb][i2][j0];
			mvNeighb[i2][j0] = tmp_mvRef0;
			j0 = j0 + 1;
		}
		i2 = i2 + 1;
	}
	tmp_refIdxCurrCu = refIdxCurrCu[0];
	tmp_refIdxNeighb = refIdxNeighb[0];
	tmp_refIdxCurrCu0 = refIdxCurrCu[1];
	tmp_refIdxNeighb0 = refIdxNeighb[1];
	tmp_refIdxCurrCu1 = refIdxCurrCu[0];
	tmp_mvCurrCu = mvCurrCu[0][0];
	tmp_mvNeighb = mvNeighb[0][0];
	tmp_mvCurrCu0 = mvCurrCu[0][1];
	tmp_mvNeighb0 = mvNeighb[0][1];
	tmp_refIdxCurrCu2 = refIdxCurrCu[1];
	tmp_mvCurrCu1 = mvCurrCu[1][0];
	tmp_mvNeighb1 = mvNeighb[1][0];
	tmp_mvCurrCu2 = mvCurrCu[1][1];
	tmp_mvNeighb2 = mvNeighb[1][1];
	return !(tmp_refIdxCurrCu == tmp_refIdxNeighb && tmp_refIdxCurrCu0 == tmp_refIdxNeighb0) || !((tmp_refIdxCurrCu1 == -1 || tmp_mvCurrCu == tmp_mvNeighb && tmp_mvCurrCu0 == tmp_mvNeighb0) && (tmp_refIdxCurrCu2 == -1 || tmp_mvCurrCu1 == tmp_mvNeighb1 && tmp_mvCurrCu2 == tmp_mvNeighb2));
}
static i32 hasNotSameMvComp(i32 orig[2], i32 neighb[2]) {
	i32 tmp_neighb;
	i32 tmp_if;
	i32 tmp_orig;

	tmp_neighb = neighb[0];
	if (tmp_neighb >= 0) {
		tmp_orig = orig[0];
		if (tmp_orig < 0) {
			tmp_if = 0;
		} else {
			tmp_if = checkSameComp(orig, neighb);
		}
	} else {
		tmp_if = 1;
	}
	return tmp_if;
}
static void searchColSlcAddr(i32 partAddr[2]) {
	i32 pocSlcAddr[2];
	i32 i;
	i32 local_colRefIdx;
	u16 tmp_numSlcPerPict;
	i32 j;
	u16 tmp_slcAddrRef;
	i32 tmp_partAddr;
	i32 tmp_pocSlcAddr;
	u8 local_lcuSizeMaxInPart;
	i32 tmp_partAddr0;
	i32 tmp_pocSlcAddr0;
	i32 tmp_partAddr1;
	i32 tmp_pocSlcAddr1;
	i16 local_colSlcIdx;
	i32 tmp_pocSlcAddr2;
	u16 tmp_slcAddrRef0;
	i32 tmp_pocSlcAddr3;
	u16 tmp_slcAddrRef1;
	i32 tmp_pocSlcAddr4;
	u16 tmp_slcAddrRef2;

	colSlcIdx = -1;
	i = 0;
	local_colRefIdx = colRefIdx;
	tmp_numSlcPerPict = numSlcPerPict[local_colRefIdx];
	while (i <= tmp_numSlcPerPict - 1) {
		j = 0;
		while (j <= 1) {
			local_colRefIdx = colRefIdx;
			tmp_slcAddrRef = slcAddrRef[local_colRefIdx][i][j];
			pocSlcAddr[j] = tmp_slcAddrRef;
			j = j + 1;
		}
		tmp_partAddr = partAddr[1];
		tmp_pocSlcAddr = pocSlcAddr[1];
		local_lcuSizeMaxInPart = lcuSizeMaxInPart;
		tmp_partAddr0 = partAddr[1];
		tmp_pocSlcAddr0 = pocSlcAddr[1];
		tmp_partAddr1 = partAddr[0];
		tmp_pocSlcAddr1 = pocSlcAddr[0];
		if (tmp_partAddr >= tmp_pocSlcAddr + local_lcuSizeMaxInPart || tmp_partAddr0 >= tmp_pocSlcAddr0 && tmp_partAddr1 >= tmp_pocSlcAddr1) {
			local_colSlcIdx = colSlcIdx;
			if (local_colSlcIdx != -1) {
				tmp_pocSlcAddr2 = pocSlcAddr[1];
				local_colRefIdx = colRefIdx;
				local_colSlcIdx = colSlcIdx;
				tmp_slcAddrRef0 = slcAddrRef[local_colRefIdx][local_colSlcIdx][1];
				tmp_pocSlcAddr3 = pocSlcAddr[1];
				local_colRefIdx = colRefIdx;
				local_colSlcIdx = colSlcIdx;
				tmp_slcAddrRef1 = slcAddrRef[local_colRefIdx][local_colSlcIdx][1];
				tmp_pocSlcAddr4 = pocSlcAddr[0];
				local_colRefIdx = colRefIdx;
				local_colSlcIdx = colSlcIdx;
				tmp_slcAddrRef2 = slcAddrRef[local_colRefIdx][local_colSlcIdx][0];
				if (tmp_pocSlcAddr2 > tmp_slcAddrRef0 || tmp_pocSlcAddr3 == tmp_slcAddrRef1 && tmp_pocSlcAddr4 > tmp_slcAddrRef2) {
					colSlcIdx = i;
				}
			} else {
				colSlcIdx = i;
			}
		}
		i = i + 1;
	}
}
static void saveRefIdx(i32 refIdxToSave[2], u8 cuSize[2], u8 cuPartMode, u8 numPartDecoded, i8 refIdxRef[17][2048][256][2], i8 currIdx, u16 lcuAddr, u16 puAddrInLcu) {
	u16 nbBlkInPu;
	u8 tmp_cuSize;
	u8 tmp_cuSize0;
	u8 local_PART_2NxnD;
	u8 local_PART_2NxnU;
	u8 local_PART_nLx2N;
	u8 local_PART_nRx2N;
	u8 local_PART_Nx2N;
	i32 i;
	i32 j;
	i32 tmp_refIdxToSave;
	u8 tmp_cuSize1;
	u8 tmp_cuSize2;
	i32 i0;
	i32 j0;
	i32 tmp_refIdxToSave0;
	i32 j1;
	i32 tmp_refIdxToSave1;
	u8 local_predCuSize;
	i32 i1;
	i32 j2;
	i32 tmp_refIdxToSave2;
	i32 i2;
	i32 j3;
	i32 tmp_refIdxToSave3;
	i32 i3;
	i32 j4;
	i32 tmp_refIdxToSave4;
	i32 i4;
	i32 j5;
	i32 tmp_refIdxToSave5;
	i32 i5;
	i32 j6;
	i32 tmp_refIdxToSave6;
	i32 j7;
	i32 tmp_refIdxToSave7;
	i32 i6;
	i32 j8;
	i32 tmp_refIdxToSave8;
	i32 i7;
	i32 j9;
	i32 tmp_refIdxToSave9;
	i32 i8;
	i32 j10;
	i32 tmp_refIdxToSave10;
	i32 j11;
	i32 tmp_refIdxToSave11;
	i32 i9;
	i32 j12;
	i32 tmp_refIdxToSave12;
	i32 j13;
	i32 tmp_refIdxToSave13;
	i32 i10;
	i32 j14;
	i32 tmp_refIdxToSave14;
	i32 j15;
	i32 tmp_refIdxToSave15;
	i32 j16;
	i32 tmp_refIdxToSave16;
	i32 j17;
	i32 tmp_refIdxToSave17;
	i32 i11;
	i32 j18;
	i32 tmp_refIdxToSave18;
	i32 j19;
	i32 tmp_refIdxToSave19;
	i32 j20;
	i32 tmp_refIdxToSave20;
	i32 j21;
	i32 tmp_refIdxToSave21;
	i32 i12;
	i32 j22;
	i32 tmp_refIdxToSave22;
	i32 j23;
	i32 tmp_refIdxToSave23;
	i32 i13;
	i32 j24;
	i32 tmp_refIdxToSave24;
	i32 j25;
	i32 tmp_refIdxToSave25;

	tmp_cuSize = cuSize[0];
	tmp_cuSize0 = cuSize[1];
	nbBlkInPu = tmp_cuSize * tmp_cuSize0 / 16;
	local_PART_2NxnD = HevcDecoder_generateInfo_MvComponentPred_PART_2NxnD;
	local_PART_2NxnU = HevcDecoder_generateInfo_MvComponentPred_PART_2NxnU;
	local_PART_nLx2N = HevcDecoder_generateInfo_MvComponentPred_PART_nLx2N;
	local_PART_nRx2N = HevcDecoder_generateInfo_MvComponentPred_PART_nRx2N;
	local_PART_Nx2N = HevcDecoder_generateInfo_MvComponentPred_PART_Nx2N;
	if (cuPartMode != local_PART_2NxnD && cuPartMode != local_PART_2NxnU && cuPartMode != local_PART_nLx2N && cuPartMode != local_PART_nRx2N && cuPartMode != local_PART_Nx2N) {
		i = 0;
		while (i <= nbBlkInPu - 1) {
			j = 0;
			while (j <= 1) {
				tmp_refIdxToSave = refIdxToSave[j];
				refIdxRef[currIdx][lcuAddr][puAddrInLcu + i][j] = tmp_refIdxToSave;
				j = j + 1;
			}
			i = i + 1;
		}
	} else {
		local_PART_Nx2N = HevcDecoder_generateInfo_MvComponentPred_PART_Nx2N;
		if (cuPartMode == local_PART_Nx2N) {
			tmp_cuSize1 = cuSize[0];
			tmp_cuSize2 = cuSize[1];
			nbBlkInPu = tmp_cuSize1 * tmp_cuSize2 / 16 / 2;
			i0 = 0;
			while (i0 <= nbBlkInPu - 1) {
				j0 = 0;
				while (j0 <= 1) {
					tmp_refIdxToSave0 = refIdxToSave[j0];
					refIdxRef[currIdx][lcuAddr][puAddrInLcu + i0][j0] = tmp_refIdxToSave0;
					j0 = j0 + 1;
				}
				j1 = 0;
				while (j1 <= 1) {
					tmp_refIdxToSave1 = refIdxToSave[j1];
					refIdxRef[currIdx][lcuAddr][2 * nbBlkInPu + puAddrInLcu + i0][j1] = tmp_refIdxToSave1;
					j1 = j1 + 1;
				}
				i0 = i0 + 1;
			}
		} else {
			local_PART_2NxnD = HevcDecoder_generateInfo_MvComponentPred_PART_2NxnD;
			if (cuPartMode == local_PART_2NxnD) {
				if (numPartDecoded == 1) {
					local_predCuSize = predCuSize;
					local_predCuSize = predCuSize;
					nbBlkInPu = local_predCuSize * local_predCuSize / 16 / 8;
					i1 = 0;
					while (i1 <= 5 * nbBlkInPu - 1) {
						j2 = 0;
						while (j2 <= 1) {
							tmp_refIdxToSave2 = refIdxToSave[j2];
							refIdxRef[currIdx][lcuAddr][puAddrInLcu + i1][j2] = tmp_refIdxToSave2;
							j2 = j2 + 1;
						}
						i1 = i1 + 1;
					}
					i2 = 6 * nbBlkInPu;
					while (i2 <= 7 * nbBlkInPu - 1) {
						j3 = 0;
						while (j3 <= 1) {
							tmp_refIdxToSave3 = refIdxToSave[j3];
							refIdxRef[currIdx][lcuAddr][puAddrInLcu + i2][j3] = tmp_refIdxToSave3;
							j3 = j3 + 1;
						}
						i2 = i2 + 1;
					}
				} else {
					i3 = 0;
					while (i3 <= nbBlkInPu / 2 - 1) {
						j4 = 0;
						while (j4 <= 1) {
							tmp_refIdxToSave4 = refIdxToSave[j4];
							refIdxRef[currIdx][lcuAddr][puAddrInLcu + i3][j4] = tmp_refIdxToSave4;
							j4 = j4 + 1;
						}
						i3 = i3 + 1;
					}
					i4 = nbBlkInPu;
					while (i4 <= nbBlkInPu + nbBlkInPu / 2 - 1) {
						j5 = 0;
						while (j5 <= 1) {
							tmp_refIdxToSave5 = refIdxToSave[j5];
							refIdxRef[currIdx][lcuAddr][puAddrInLcu + i4][j5] = tmp_refIdxToSave5;
							j5 = j5 + 1;
						}
						i4 = i4 + 1;
					}
				}
			} else {
				local_PART_2NxnU = HevcDecoder_generateInfo_MvComponentPred_PART_2NxnU;
				if (cuPartMode == local_PART_2NxnU) {
					if (numPartDecoded == 1) {
						i5 = 0;
						while (i5 <= nbBlkInPu / 2 - 1) {
							j6 = 0;
							while (j6 <= 1) {
								tmp_refIdxToSave6 = refIdxToSave[j6];
								refIdxRef[currIdx][lcuAddr][puAddrInLcu + i5][j6] = tmp_refIdxToSave6;
								j6 = j6 + 1;
							}
							j7 = 0;
							while (j7 <= 1) {
								tmp_refIdxToSave7 = refIdxToSave[j7];
								refIdxRef[currIdx][lcuAddr][nbBlkInPu + puAddrInLcu + i5][j7] = tmp_refIdxToSave7;
								j7 = j7 + 1;
							}
							i5 = i5 + 1;
						}
					} else {
						local_predCuSize = predCuSize;
						local_predCuSize = predCuSize;
						nbBlkInPu = local_predCuSize * local_predCuSize / 16 / 8;
						i6 = 0;
						while (i6 <= nbBlkInPu - 1) {
							j8 = 0;
							while (j8 <= 1) {
								tmp_refIdxToSave8 = refIdxToSave[j8];
								refIdxRef[currIdx][lcuAddr][puAddrInLcu + i6][j8] = tmp_refIdxToSave8;
								j8 = j8 + 1;
							}
							i6 = i6 + 1;
						}
						i7 = 2 * nbBlkInPu;
						while (i7 <= 7 * nbBlkInPu - 1) {
							j9 = 0;
							while (j9 <= 1) {
								tmp_refIdxToSave9 = refIdxToSave[j9];
								refIdxRef[currIdx][lcuAddr][puAddrInLcu + i7][j9] = tmp_refIdxToSave9;
								j9 = j9 + 1;
							}
							i7 = i7 + 1;
						}
					}
				} else {
					local_PART_nRx2N = HevcDecoder_generateInfo_MvComponentPred_PART_nRx2N;
					if (cuPartMode == local_PART_nRx2N) {
						local_predCuSize = predCuSize;
						local_predCuSize = predCuSize;
						nbBlkInPu = local_predCuSize * local_predCuSize / 16 / 16;
						if (numPartDecoded == 1) {
							i8 = 0;
							while (i8 <= 5 * nbBlkInPu - 1) {
								j10 = 0;
								while (j10 <= 1) {
									tmp_refIdxToSave10 = refIdxToSave[j10];
									refIdxRef[currIdx][lcuAddr][puAddrInLcu + i8][j10] = tmp_refIdxToSave10;
									j10 = j10 + 1;
								}
								j11 = 0;
								while (j11 <= 1) {
									tmp_refIdxToSave11 = refIdxToSave[j11];
									refIdxRef[currIdx][lcuAddr][8 * nbBlkInPu + puAddrInLcu + i8][j11] = tmp_refIdxToSave11;
									j11 = j11 + 1;
								}
								i8 = i8 + 1;
							}
							i9 = 6 * nbBlkInPu;
							while (i9 <= 7 * nbBlkInPu - 1) {
								j12 = 0;
								while (j12 <= 1) {
									tmp_refIdxToSave12 = refIdxToSave[j12];
									refIdxRef[currIdx][lcuAddr][puAddrInLcu + i9][j12] = tmp_refIdxToSave12;
									j12 = j12 + 1;
								}
								j13 = 0;
								while (j13 <= 1) {
									tmp_refIdxToSave13 = refIdxToSave[j13];
									refIdxRef[currIdx][lcuAddr][8 * nbBlkInPu + puAddrInLcu + i9][j13] = tmp_refIdxToSave13;
									j13 = j13 + 1;
								}
								i9 = i9 + 1;
							}
						} else {
							i10 = 0;
							while (i10 <= nbBlkInPu - 1) {
								j14 = 0;
								while (j14 <= 1) {
									tmp_refIdxToSave14 = refIdxToSave[j14];
									refIdxRef[currIdx][lcuAddr][0 * nbBlkInPu + puAddrInLcu + i10][j14] = tmp_refIdxToSave14;
									j14 = j14 + 1;
								}
								j15 = 0;
								while (j15 <= 1) {
									tmp_refIdxToSave15 = refIdxToSave[j15];
									refIdxRef[currIdx][lcuAddr][2 * nbBlkInPu + puAddrInLcu + i10][j15] = tmp_refIdxToSave15;
									j15 = j15 + 1;
								}
								j16 = 0;
								while (j16 <= 1) {
									tmp_refIdxToSave16 = refIdxToSave[j16];
									refIdxRef[currIdx][lcuAddr][8 * nbBlkInPu + puAddrInLcu + i10][j16] = tmp_refIdxToSave16;
									j16 = j16 + 1;
								}
								j17 = 0;
								while (j17 <= 1) {
									tmp_refIdxToSave17 = refIdxToSave[j17];
									refIdxRef[currIdx][lcuAddr][10 * nbBlkInPu + puAddrInLcu + i10][j17] = tmp_refIdxToSave17;
									j17 = j17 + 1;
								}
								i10 = i10 + 1;
							}
						}
					} else {
						local_predCuSize = predCuSize;
						local_predCuSize = predCuSize;
						nbBlkInPu = local_predCuSize * local_predCuSize / 16 / 16;
						if (numPartDecoded == 1) {
							i11 = 0;
							while (i11 <= nbBlkInPu - 1) {
								j18 = 0;
								while (j18 <= 1) {
									tmp_refIdxToSave18 = refIdxToSave[j18];
									refIdxRef[currIdx][lcuAddr][puAddrInLcu + i11][j18] = tmp_refIdxToSave18;
									j18 = j18 + 1;
								}
								j19 = 0;
								while (j19 <= 1) {
									tmp_refIdxToSave19 = refIdxToSave[j19];
									refIdxRef[currIdx][lcuAddr][2 * nbBlkInPu + puAddrInLcu + i11][j19] = tmp_refIdxToSave19;
									j19 = j19 + 1;
								}
								j20 = 0;
								while (j20 <= 1) {
									tmp_refIdxToSave20 = refIdxToSave[j20];
									refIdxRef[currIdx][lcuAddr][8 * nbBlkInPu + puAddrInLcu + i11][j20] = tmp_refIdxToSave20;
									j20 = j20 + 1;
								}
								j21 = 0;
								while (j21 <= 1) {
									tmp_refIdxToSave21 = refIdxToSave[j21];
									refIdxRef[currIdx][lcuAddr][10 * nbBlkInPu + puAddrInLcu + i11][j21] = tmp_refIdxToSave21;
									j21 = j21 + 1;
								}
								i11 = i11 + 1;
							}
						} else {
							i12 = 0;
							while (i12 <= nbBlkInPu - 1) {
								j22 = 0;
								while (j22 <= 1) {
									tmp_refIdxToSave22 = refIdxToSave[j22];
									refIdxRef[currIdx][lcuAddr][puAddrInLcu + i12][j22] = tmp_refIdxToSave22;
									j22 = j22 + 1;
								}
								j23 = 0;
								while (j23 <= 1) {
									tmp_refIdxToSave23 = refIdxToSave[j23];
									refIdxRef[currIdx][lcuAddr][8 * nbBlkInPu + puAddrInLcu + i12][j23] = tmp_refIdxToSave23;
									j23 = j23 + 1;
								}
								i12 = i12 + 1;
							}
							i13 = 2 * nbBlkInPu;
							while (i13 <= 7 * nbBlkInPu - 1) {
								j24 = 0;
								while (j24 <= 1) {
									tmp_refIdxToSave24 = refIdxToSave[j24];
									refIdxRef[currIdx][lcuAddr][puAddrInLcu + i13][j24] = tmp_refIdxToSave24;
									j24 = j24 + 1;
								}
								j25 = 0;
								while (j25 <= 1) {
									tmp_refIdxToSave25 = refIdxToSave[j25];
									refIdxRef[currIdx][lcuAddr][8 * nbBlkInPu + puAddrInLcu + i13][j25] = tmp_refIdxToSave25;
									j25 = j25 + 1;
								}
								i13 = i13 + 1;
							}
						}
					}
				}
			}
		}
	}
}
static void saveMvComponent(i16 mvToSave[2][2], u8 cuSize[2], u8 cuPartMode, u8 numPartDecoded, i16 mvRef[17][2048][256][2][2], i8 currIdx, u16 lcuAddr, u16 puAddrInLcu) {
	u16 nbBlkInPu;
	u8 tmp_cuSize;
	u8 tmp_cuSize0;
	u8 local_PART_2NxnD;
	u8 local_PART_2NxnU;
	u8 local_PART_nLx2N;
	u8 local_PART_nRx2N;
	u8 local_PART_Nx2N;
	i32 i;
	i32 k;
	i32 j;
	i16 tmp_mvToSave;
	u8 tmp_cuSize1;
	u8 tmp_cuSize2;
	i32 i0;
	i32 k0;
	i32 j0;
	i16 tmp_mvToSave0;
	i32 k1;
	i32 j1;
	i16 tmp_mvToSave1;
	u8 local_predCuSize;
	i32 i1;
	i32 k2;
	i32 j2;
	i16 tmp_mvToSave2;
	i32 i2;
	i32 k3;
	i32 j3;
	i16 tmp_mvToSave3;
	i32 i3;
	i32 k4;
	i32 j4;
	i16 tmp_mvToSave4;
	i32 i4;
	i32 k5;
	i32 j5;
	i16 tmp_mvToSave5;
	i32 i5;
	i32 k6;
	i32 j6;
	i16 tmp_mvToSave6;
	i32 k7;
	i32 j7;
	i16 tmp_mvToSave7;
	i32 i6;
	i32 k8;
	i32 j8;
	i16 tmp_mvToSave8;
	i32 i7;
	i32 k9;
	i32 j9;
	i16 tmp_mvToSave9;
	i32 i8;
	i32 k10;
	i32 j10;
	i16 tmp_mvToSave10;
	i32 k11;
	i32 j11;
	i16 tmp_mvToSave11;
	i32 i9;
	i32 k12;
	i32 j12;
	i16 tmp_mvToSave12;
	i32 k13;
	i32 j13;
	i16 tmp_mvToSave13;
	i32 i10;
	i32 k14;
	i32 j14;
	i16 tmp_mvToSave14;
	i32 k15;
	i32 j15;
	i16 tmp_mvToSave15;
	i32 k16;
	i32 j16;
	i16 tmp_mvToSave16;
	i32 k17;
	i32 j17;
	i16 tmp_mvToSave17;
	i32 i11;
	i32 k18;
	i32 j18;
	i16 tmp_mvToSave18;
	i32 k19;
	i32 j19;
	i16 tmp_mvToSave19;
	i32 k20;
	i32 j20;
	i16 tmp_mvToSave20;
	i32 k21;
	i32 j21;
	i16 tmp_mvToSave21;
	i32 i12;
	i32 k22;
	i32 j22;
	i16 tmp_mvToSave22;
	i32 k23;
	i32 j23;
	i16 tmp_mvToSave23;
	i32 i13;
	i32 k24;
	i32 j24;
	i16 tmp_mvToSave24;
	i32 k25;
	i32 j25;
	i16 tmp_mvToSave25;

	tmp_cuSize = cuSize[0];
	tmp_cuSize0 = cuSize[1];
	nbBlkInPu = tmp_cuSize * tmp_cuSize0 / 16;
	local_PART_2NxnD = HevcDecoder_generateInfo_MvComponentPred_PART_2NxnD;
	local_PART_2NxnU = HevcDecoder_generateInfo_MvComponentPred_PART_2NxnU;
	local_PART_nLx2N = HevcDecoder_generateInfo_MvComponentPred_PART_nLx2N;
	local_PART_nRx2N = HevcDecoder_generateInfo_MvComponentPred_PART_nRx2N;
	local_PART_Nx2N = HevcDecoder_generateInfo_MvComponentPred_PART_Nx2N;
	if (cuPartMode != local_PART_2NxnD && cuPartMode != local_PART_2NxnU && cuPartMode != local_PART_nLx2N && cuPartMode != local_PART_nRx2N && cuPartMode != local_PART_Nx2N) {
		i = 0;
		while (i <= nbBlkInPu - 1) {
			k = 0;
			while (k <= 1) {
				j = 0;
				while (j <= 1) {
					tmp_mvToSave = mvToSave[k][j];
					mvRef[currIdx][lcuAddr][puAddrInLcu + i][k][j] = tmp_mvToSave;
					j = j + 1;
				}
				k = k + 1;
			}
			i = i + 1;
		}
	} else {
		local_PART_Nx2N = HevcDecoder_generateInfo_MvComponentPred_PART_Nx2N;
		if (cuPartMode == local_PART_Nx2N) {
			tmp_cuSize1 = cuSize[0];
			tmp_cuSize2 = cuSize[1];
			nbBlkInPu = tmp_cuSize1 * tmp_cuSize2 / 16 / 2;
			i0 = 0;
			while (i0 <= nbBlkInPu - 1) {
				k0 = 0;
				while (k0 <= 1) {
					j0 = 0;
					while (j0 <= 1) {
						tmp_mvToSave0 = mvToSave[k0][j0];
						mvRef[currIdx][lcuAddr][puAddrInLcu + i0][k0][j0] = tmp_mvToSave0;
						j0 = j0 + 1;
					}
					k0 = k0 + 1;
				}
				k1 = 0;
				while (k1 <= 1) {
					j1 = 0;
					while (j1 <= 1) {
						tmp_mvToSave1 = mvToSave[k1][j1];
						mvRef[currIdx][lcuAddr][2 * nbBlkInPu + puAddrInLcu + i0][k1][j1] = tmp_mvToSave1;
						j1 = j1 + 1;
					}
					k1 = k1 + 1;
				}
				i0 = i0 + 1;
			}
		} else {
			local_PART_2NxnD = HevcDecoder_generateInfo_MvComponentPred_PART_2NxnD;
			if (cuPartMode == local_PART_2NxnD) {
				if (numPartDecoded == 1) {
					local_predCuSize = predCuSize;
					local_predCuSize = predCuSize;
					nbBlkInPu = local_predCuSize * local_predCuSize / 16 / 8;
					i1 = 0;
					while (i1 <= 5 * nbBlkInPu - 1) {
						k2 = 0;
						while (k2 <= 1) {
							j2 = 0;
							while (j2 <= 1) {
								tmp_mvToSave2 = mvToSave[k2][j2];
								mvRef[currIdx][lcuAddr][puAddrInLcu + i1][k2][j2] = tmp_mvToSave2;
								j2 = j2 + 1;
							}
							k2 = k2 + 1;
						}
						i1 = i1 + 1;
					}
					i2 = 6 * nbBlkInPu;
					while (i2 <= 7 * nbBlkInPu - 1) {
						k3 = 0;
						while (k3 <= 1) {
							j3 = 0;
							while (j3 <= 1) {
								tmp_mvToSave3 = mvToSave[k3][j3];
								mvRef[currIdx][lcuAddr][puAddrInLcu + i2][k3][j3] = tmp_mvToSave3;
								j3 = j3 + 1;
							}
							k3 = k3 + 1;
						}
						i2 = i2 + 1;
					}
				} else {
					i3 = 0;
					while (i3 <= nbBlkInPu / 2 - 1) {
						k4 = 0;
						while (k4 <= 1) {
							j4 = 0;
							while (j4 <= 1) {
								tmp_mvToSave4 = mvToSave[k4][j4];
								mvRef[currIdx][lcuAddr][puAddrInLcu + i3][k4][j4] = tmp_mvToSave4;
								j4 = j4 + 1;
							}
							k4 = k4 + 1;
						}
						i3 = i3 + 1;
					}
					i4 = nbBlkInPu;
					while (i4 <= nbBlkInPu + nbBlkInPu / 2 - 1) {
						k5 = 0;
						while (k5 <= 1) {
							j5 = 0;
							while (j5 <= 1) {
								tmp_mvToSave5 = mvToSave[k5][j5];
								mvRef[currIdx][lcuAddr][puAddrInLcu + i4][k5][j5] = tmp_mvToSave5;
								j5 = j5 + 1;
							}
							k5 = k5 + 1;
						}
						i4 = i4 + 1;
					}
				}
			} else {
				local_PART_2NxnU = HevcDecoder_generateInfo_MvComponentPred_PART_2NxnU;
				if (cuPartMode == local_PART_2NxnU) {
					if (numPartDecoded == 1) {
						i5 = 0;
						while (i5 <= nbBlkInPu / 2 - 1) {
							k6 = 0;
							while (k6 <= 1) {
								j6 = 0;
								while (j6 <= 1) {
									tmp_mvToSave6 = mvToSave[k6][j6];
									mvRef[currIdx][lcuAddr][puAddrInLcu + i5][k6][j6] = tmp_mvToSave6;
									j6 = j6 + 1;
								}
								k6 = k6 + 1;
							}
							k7 = 0;
							while (k7 <= 1) {
								j7 = 0;
								while (j7 <= 1) {
									tmp_mvToSave7 = mvToSave[k7][j7];
									mvRef[currIdx][lcuAddr][nbBlkInPu + puAddrInLcu + i5][k7][j7] = tmp_mvToSave7;
									j7 = j7 + 1;
								}
								k7 = k7 + 1;
							}
							i5 = i5 + 1;
						}
					} else {
						local_predCuSize = predCuSize;
						local_predCuSize = predCuSize;
						nbBlkInPu = local_predCuSize * local_predCuSize / 16 / 8;
						i6 = 0;
						while (i6 <= nbBlkInPu - 1) {
							k8 = 0;
							while (k8 <= 1) {
								j8 = 0;
								while (j8 <= 1) {
									tmp_mvToSave8 = mvToSave[k8][j8];
									mvRef[currIdx][lcuAddr][puAddrInLcu + i6][k8][j8] = tmp_mvToSave8;
									j8 = j8 + 1;
								}
								k8 = k8 + 1;
							}
							i6 = i6 + 1;
						}
						i7 = 2 * nbBlkInPu;
						while (i7 <= 7 * nbBlkInPu - 1) {
							k9 = 0;
							while (k9 <= 1) {
								j9 = 0;
								while (j9 <= 1) {
									tmp_mvToSave9 = mvToSave[k9][j9];
									mvRef[currIdx][lcuAddr][puAddrInLcu + i7][k9][j9] = tmp_mvToSave9;
									j9 = j9 + 1;
								}
								k9 = k9 + 1;
							}
							i7 = i7 + 1;
						}
					}
				} else {
					local_PART_nRx2N = HevcDecoder_generateInfo_MvComponentPred_PART_nRx2N;
					if (cuPartMode == local_PART_nRx2N) {
						local_predCuSize = predCuSize;
						local_predCuSize = predCuSize;
						nbBlkInPu = local_predCuSize * local_predCuSize / 16 / 16;
						if (numPartDecoded == 1) {
							i8 = 0;
							while (i8 <= 5 * nbBlkInPu - 1) {
								k10 = 0;
								while (k10 <= 1) {
									j10 = 0;
									while (j10 <= 1) {
										tmp_mvToSave10 = mvToSave[k10][j10];
										mvRef[currIdx][lcuAddr][puAddrInLcu + i8][k10][j10] = tmp_mvToSave10;
										j10 = j10 + 1;
									}
									k10 = k10 + 1;
								}
								k11 = 0;
								while (k11 <= 1) {
									j11 = 0;
									while (j11 <= 1) {
										tmp_mvToSave11 = mvToSave[k11][j11];
										mvRef[currIdx][lcuAddr][8 * nbBlkInPu + puAddrInLcu + i8][k11][j11] = tmp_mvToSave11;
										j11 = j11 + 1;
									}
									k11 = k11 + 1;
								}
								i8 = i8 + 1;
							}
							i9 = 6 * nbBlkInPu;
							while (i9 <= 7 * nbBlkInPu - 1) {
								k12 = 0;
								while (k12 <= 1) {
									j12 = 0;
									while (j12 <= 1) {
										tmp_mvToSave12 = mvToSave[k12][j12];
										mvRef[currIdx][lcuAddr][puAddrInLcu + i9][k12][j12] = tmp_mvToSave12;
										j12 = j12 + 1;
									}
									k12 = k12 + 1;
								}
								k13 = 0;
								while (k13 <= 1) {
									j13 = 0;
									while (j13 <= 1) {
										tmp_mvToSave13 = mvToSave[k13][j13];
										mvRef[currIdx][lcuAddr][8 * nbBlkInPu + puAddrInLcu + i9][k13][j13] = tmp_mvToSave13;
										j13 = j13 + 1;
									}
									k13 = k13 + 1;
								}
								i9 = i9 + 1;
							}
						} else {
							i10 = 0;
							while (i10 <= nbBlkInPu - 1) {
								k14 = 0;
								while (k14 <= 1) {
									j14 = 0;
									while (j14 <= 1) {
										tmp_mvToSave14 = mvToSave[k14][j14];
										mvRef[currIdx][lcuAddr][0 * nbBlkInPu + puAddrInLcu + i10][k14][j14] = tmp_mvToSave14;
										j14 = j14 + 1;
									}
									k14 = k14 + 1;
								}
								k15 = 0;
								while (k15 <= 1) {
									j15 = 0;
									while (j15 <= 1) {
										tmp_mvToSave15 = mvToSave[k15][j15];
										mvRef[currIdx][lcuAddr][2 * nbBlkInPu + puAddrInLcu + i10][k15][j15] = tmp_mvToSave15;
										j15 = j15 + 1;
									}
									k15 = k15 + 1;
								}
								k16 = 0;
								while (k16 <= 1) {
									j16 = 0;
									while (j16 <= 1) {
										tmp_mvToSave16 = mvToSave[k16][j16];
										mvRef[currIdx][lcuAddr][8 * nbBlkInPu + puAddrInLcu + i10][k16][j16] = tmp_mvToSave16;
										j16 = j16 + 1;
									}
									k16 = k16 + 1;
								}
								k17 = 0;
								while (k17 <= 1) {
									j17 = 0;
									while (j17 <= 1) {
										tmp_mvToSave17 = mvToSave[k17][j17];
										mvRef[currIdx][lcuAddr][10 * nbBlkInPu + puAddrInLcu + i10][k17][j17] = tmp_mvToSave17;
										j17 = j17 + 1;
									}
									k17 = k17 + 1;
								}
								i10 = i10 + 1;
							}
						}
					} else {
						local_predCuSize = predCuSize;
						local_predCuSize = predCuSize;
						nbBlkInPu = local_predCuSize * local_predCuSize / 16 / 16;
						if (numPartDecoded == 1) {
							i11 = 0;
							while (i11 <= nbBlkInPu - 1) {
								k18 = 0;
								while (k18 <= 1) {
									j18 = 0;
									while (j18 <= 1) {
										tmp_mvToSave18 = mvToSave[k18][j18];
										mvRef[currIdx][lcuAddr][puAddrInLcu + i11][k18][j18] = tmp_mvToSave18;
										j18 = j18 + 1;
									}
									k18 = k18 + 1;
								}
								k19 = 0;
								while (k19 <= 1) {
									j19 = 0;
									while (j19 <= 1) {
										tmp_mvToSave19 = mvToSave[k19][j19];
										mvRef[currIdx][lcuAddr][2 * nbBlkInPu + puAddrInLcu + i11][k19][j19] = tmp_mvToSave19;
										j19 = j19 + 1;
									}
									k19 = k19 + 1;
								}
								k20 = 0;
								while (k20 <= 1) {
									j20 = 0;
									while (j20 <= 1) {
										tmp_mvToSave20 = mvToSave[k20][j20];
										mvRef[currIdx][lcuAddr][8 * nbBlkInPu + puAddrInLcu + i11][k20][j20] = tmp_mvToSave20;
										j20 = j20 + 1;
									}
									k20 = k20 + 1;
								}
								k21 = 0;
								while (k21 <= 1) {
									j21 = 0;
									while (j21 <= 1) {
										tmp_mvToSave21 = mvToSave[k21][j21];
										mvRef[currIdx][lcuAddr][10 * nbBlkInPu + puAddrInLcu + i11][k21][j21] = tmp_mvToSave21;
										j21 = j21 + 1;
									}
									k21 = k21 + 1;
								}
								i11 = i11 + 1;
							}
						} else {
							i12 = 0;
							while (i12 <= nbBlkInPu - 1) {
								k22 = 0;
								while (k22 <= 1) {
									j22 = 0;
									while (j22 <= 1) {
										tmp_mvToSave22 = mvToSave[k22][j22];
										mvRef[currIdx][lcuAddr][puAddrInLcu + i12][k22][j22] = tmp_mvToSave22;
										j22 = j22 + 1;
									}
									k22 = k22 + 1;
								}
								k23 = 0;
								while (k23 <= 1) {
									j23 = 0;
									while (j23 <= 1) {
										tmp_mvToSave23 = mvToSave[k23][j23];
										mvRef[currIdx][lcuAddr][8 * nbBlkInPu + puAddrInLcu + i12][k23][j23] = tmp_mvToSave23;
										j23 = j23 + 1;
									}
									k23 = k23 + 1;
								}
								i12 = i12 + 1;
							}
							i13 = 2 * nbBlkInPu;
							while (i13 <= 7 * nbBlkInPu - 1) {
								k24 = 0;
								while (k24 <= 1) {
									j24 = 0;
									while (j24 <= 1) {
										tmp_mvToSave24 = mvToSave[k24][j24];
										mvRef[currIdx][lcuAddr][puAddrInLcu + i13][k24][j24] = tmp_mvToSave24;
										j24 = j24 + 1;
									}
									k24 = k24 + 1;
								}
								k25 = 0;
								while (k25 <= 1) {
									j25 = 0;
									while (j25 <= 1) {
										tmp_mvToSave25 = mvToSave[k25][j25];
										mvRef[currIdx][lcuAddr][8 * nbBlkInPu + puAddrInLcu + i13][k25][j25] = tmp_mvToSave25;
										j25 = j25 + 1;
									}
									k25 = k25 + 1;
								}
								i13 = i13 + 1;
							}
						}
					}
				}
			}
		}
	}
}
static void getNeighbAddr(i32 location, i32 depSlcOrCol, i32 isColNeighb) {
	i32 bitMod;
	i32 isNotInPict;
	i32 local_LEFT;
	i32 tmp_partAddr;
	i32 tmp_partAddr0;
	i32 local_nPSH;
	u16 local_lcuAddr;
	u16 tmp_puAbsAddrInLcu;
	u16 tmp_puAbsAddrInLcu0;
	i16 tmp_neighbLcuAddr;
	u16 tmp_puAbsAddrInLcu1;
	u16 tmp_puAbsAddrInLcu2;
	u16 tmp_neighbBlkAddr;
	i32 local_ABOVE;
	i32 tmp_partAddr1;
	i32 local_nPSW;
	i32 tmp_partAddr2;
	u16 tmp_puAbsAddrInLcu3;
	u16 tmp_puAbsAddrInLcu4;
	i16 tmp_neighbLcuAddr0;
	u16 tmp_puAbsAddrInLcu5;
	u16 tmp_puAbsAddrInLcu6;
	u16 tmp_neighbBlkAddr0;
	i32 local_ABOVE_RIGHT;
	i32 tmp_partAddr3;
	i32 tmp_partAddr4;
	u16 tmp_puAbsAddrInLcu7;
	u16 tmp_puAbsAddrInLcu8;
	i16 tmp_neighbLcuAddr1;
	u16 tmp_puAbsAddrInLcu9;
	u16 tmp_puAbsAddrInLcu10;
	u16 tmp_neighbBlkAddr1;
	i32 local_LEFT_BOTTOM;
	i32 tmp_partAddr5;
	i32 tmp_partAddr6;
	u16 tmp_puAbsAddrInLcu11;
	u16 tmp_puAbsAddrInLcu12;
	i16 tmp_neighbLcuAddr2;
	u16 tmp_puAbsAddrInLcu13;
	u16 tmp_puAbsAddrInLcu14;
	u16 tmp_neighbBlkAddr2;
	i32 local_ABOVE_LEFT;
	i32 tmp_partAddr7;
	i32 tmp_partAddr8;
	u16 tmp_puAbsAddrInLcu15;
	u16 tmp_puAbsAddrInLcu16;
	i16 tmp_neighbLcuAddr3;
	u16 tmp_puAbsAddrInLcu17;
	u16 tmp_puAbsAddrInLcu18;
	u16 tmp_neighbBlkAddr3;
	i32 local_RIGHT_BOTTOM;
	i32 tmp_partAddr9;
	i32 tmp_partAddr10;
	i32 tmp_neighbLocation;
	i32 tmp_picSizeInPart;
	i32 tmp_neighbLocation0;
	i32 tmp_picSizeInPart0;
	i32 tmp_neighbLocation1;
	u8 local_maskLcuSzMax;
	i32 tmp_neighbLocation2;
	i32 tmp_partAddr11;
	i32 tmp_neighbLocation3;
	i32 tmp_neighbLocation4;
	u16 tmp_puAbsAddrInLcu19;
	u16 tmp_puAbsAddrInLcu20;
	i16 tmp_neighbLcuAddr4;
	u16 tmp_puAbsAddrInLcu21;
	u16 tmp_puAbsAddrInLcu22;
	u16 tmp_neighbBlkAddr4;
	i32 tmp_partAddr12;
	i32 tmp_partAddr13;
	i32 tmp_neighbLocation5;
	i32 tmp_partAddr14;
	i32 tmp_neighbLocation6;
	i32 tmp_neighbLocation7;
	u16 tmp_puAbsAddrInLcu23;
	u16 tmp_puAbsAddrInLcu24;
	i16 tmp_neighbLcuAddr5;
	u16 tmp_puAbsAddrInLcu25;
	u16 tmp_puAbsAddrInLcu26;
	u16 tmp_neighbBlkAddr5;
	i32 tmp_neighbLocation8;
	i32 tmp_picSizeInPart1;
	i32 tmp_neighbLocation9;
	i32 tmp_neighbLocation10;
	i32 tmp_picSizeInPart2;
	i32 tmp_neighbLocation11;
	i32 tmp_neighbLocation12;
	i32 tmp_neighbLocIdx;
	i32 tmp_neighbLocation13;
	u16 tmp_slcAddr;
	i32 tmp_neighbLocation14;
	u16 tmp_slcAddr0;
	u8 local_lcuSizeMaxInPart;
	i32 tmp_neighbLocation15;
	u16 tmp_slcAddr1;
	i32 tmp_neighbLocation16;
	i16 tmp_puTilesBeg;
	i32 tmp_neighbLocation17;
	i16 tmp_puTilesEnd;
	i32 tmp_neighbLocation18;
	i16 tmp_puTilesBeg0;
	i32 tmp_neighbLocation19;
	i16 tmp_puTilesEnd0;

	bitMod = 3;
	local_LEFT = LEFT;
	if (location == local_LEFT) {
		tmp_partAddr = partAddr[0];
		neighbLocation[0] = tmp_partAddr - 1;
		tmp_partAddr0 = partAddr[1];
		local_nPSH = nPSH;
		neighbLocation[1] = tmp_partAddr0 + local_nPSH - 1;
		local_lcuAddr = lcuAddr;
		tmp_puAbsAddrInLcu = puAbsAddrInLcu[1];
		local_nPSH = nPSH;
		tmp_puAbsAddrInLcu0 = puAbsAddrInLcu[0];
		tmp_neighbLcuAddr = neighbLcuAddr[tmp_puAbsAddrInLcu + 1 + local_nPSH - 1][tmp_puAbsAddrInLcu0 + 1 - 1];
		neighbLocIdx[0] = local_lcuAddr + tmp_neighbLcuAddr;
		tmp_puAbsAddrInLcu1 = puAbsAddrInLcu[1];
		local_nPSH = nPSH;
		tmp_puAbsAddrInLcu2 = puAbsAddrInLcu[0];
		tmp_neighbBlkAddr = neighbBlkAddr[tmp_puAbsAddrInLcu1 + 1 + local_nPSH - 1][tmp_puAbsAddrInLcu2 + 1 - 1];
		neighbLocIdx[1] = tmp_neighbBlkAddr;
	} else {
		local_ABOVE = ABOVE;
		if (location == local_ABOVE) {
			tmp_partAddr1 = partAddr[0];
			local_nPSW = nPSW;
			neighbLocation[0] = tmp_partAddr1 + local_nPSW - 1;
			tmp_partAddr2 = partAddr[1];
			neighbLocation[1] = tmp_partAddr2 - 1;
			local_lcuAddr = lcuAddr;
			tmp_puAbsAddrInLcu3 = puAbsAddrInLcu[1];
			tmp_puAbsAddrInLcu4 = puAbsAddrInLcu[0];
			local_nPSW = nPSW;
			tmp_neighbLcuAddr0 = neighbLcuAddr[tmp_puAbsAddrInLcu3 + 1 - 1][tmp_puAbsAddrInLcu4 + 1 + local_nPSW - 1];
			neighbLocIdx[0] = local_lcuAddr + tmp_neighbLcuAddr0;
			tmp_puAbsAddrInLcu5 = puAbsAddrInLcu[1];
			tmp_puAbsAddrInLcu6 = puAbsAddrInLcu[0];
			local_nPSW = nPSW;
			tmp_neighbBlkAddr0 = neighbBlkAddr[tmp_puAbsAddrInLcu5 + 1 - 1][tmp_puAbsAddrInLcu6 + 1 + local_nPSW - 1];
			neighbLocIdx[1] = tmp_neighbBlkAddr0;
		} else {
			local_ABOVE_RIGHT = ABOVE_RIGHT;
			if (location == local_ABOVE_RIGHT) {
				tmp_partAddr3 = partAddr[0];
				local_nPSW = nPSW;
				neighbLocation[0] = tmp_partAddr3 + local_nPSW;
				tmp_partAddr4 = partAddr[1];
				neighbLocation[1] = tmp_partAddr4 - 1;
				local_lcuAddr = lcuAddr;
				tmp_puAbsAddrInLcu7 = puAbsAddrInLcu[1];
				tmp_puAbsAddrInLcu8 = puAbsAddrInLcu[0];
				local_nPSW = nPSW;
				tmp_neighbLcuAddr1 = neighbLcuAddr[tmp_puAbsAddrInLcu7 + 1 - 1][tmp_puAbsAddrInLcu8 + 1 + local_nPSW];
				neighbLocIdx[0] = local_lcuAddr + tmp_neighbLcuAddr1;
				tmp_puAbsAddrInLcu9 = puAbsAddrInLcu[1];
				tmp_puAbsAddrInLcu10 = puAbsAddrInLcu[0];
				local_nPSW = nPSW;
				tmp_neighbBlkAddr1 = neighbBlkAddr[tmp_puAbsAddrInLcu9 + 1 - 1][tmp_puAbsAddrInLcu10 + 1 + local_nPSW];
				neighbLocIdx[1] = tmp_neighbBlkAddr1;
			} else {
				local_LEFT_BOTTOM = LEFT_BOTTOM;
				if (location == local_LEFT_BOTTOM) {
					tmp_partAddr5 = partAddr[0];
					neighbLocation[0] = tmp_partAddr5 - 1;
					tmp_partAddr6 = partAddr[1];
					local_nPSH = nPSH;
					neighbLocation[1] = tmp_partAddr6 + local_nPSH;
					local_lcuAddr = lcuAddr;
					tmp_puAbsAddrInLcu11 = puAbsAddrInLcu[1];
					local_nPSH = nPSH;
					tmp_puAbsAddrInLcu12 = puAbsAddrInLcu[0];
					tmp_neighbLcuAddr2 = neighbLcuAddr[tmp_puAbsAddrInLcu11 + 1 + local_nPSH][tmp_puAbsAddrInLcu12 + 1 - 1];
					neighbLocIdx[0] = local_lcuAddr + tmp_neighbLcuAddr2;
					tmp_puAbsAddrInLcu13 = puAbsAddrInLcu[1];
					local_nPSH = nPSH;
					tmp_puAbsAddrInLcu14 = puAbsAddrInLcu[0];
					tmp_neighbBlkAddr2 = neighbBlkAddr[tmp_puAbsAddrInLcu13 + 1 + local_nPSH][tmp_puAbsAddrInLcu14 + 1 - 1];
					neighbLocIdx[1] = tmp_neighbBlkAddr2;
				} else {
					local_ABOVE_LEFT = ABOVE_LEFT;
					if (location == local_ABOVE_LEFT) {
						tmp_partAddr7 = partAddr[0];
						neighbLocation[0] = tmp_partAddr7 - 1;
						tmp_partAddr8 = partAddr[1];
						neighbLocation[1] = tmp_partAddr8 - 1;
						local_lcuAddr = lcuAddr;
						tmp_puAbsAddrInLcu15 = puAbsAddrInLcu[1];
						tmp_puAbsAddrInLcu16 = puAbsAddrInLcu[0];
						tmp_neighbLcuAddr3 = neighbLcuAddr[tmp_puAbsAddrInLcu15 + 1 - 1][tmp_puAbsAddrInLcu16 + 1 - 1];
						neighbLocIdx[0] = local_lcuAddr + tmp_neighbLcuAddr3;
						tmp_puAbsAddrInLcu17 = puAbsAddrInLcu[1];
						tmp_puAbsAddrInLcu18 = puAbsAddrInLcu[0];
						tmp_neighbBlkAddr3 = neighbBlkAddr[tmp_puAbsAddrInLcu17 + 1 - 1][tmp_puAbsAddrInLcu18 + 1 - 1];
						neighbLocIdx[1] = tmp_neighbBlkAddr3;
					} else {
						local_RIGHT_BOTTOM = RIGHT_BOTTOM;
						if (location == local_RIGHT_BOTTOM) {
							tmp_partAddr9 = partAddr[0];
							local_nPSW = nPSW;
							neighbLocation[0] = tmp_partAddr9 + local_nPSW;
							tmp_partAddr10 = partAddr[1];
							local_nPSH = nPSH;
							neighbLocation[1] = tmp_partAddr10 + local_nPSH;
							tmp_neighbLocation = neighbLocation[0];
							tmp_picSizeInPart = picSizeInPart[0];
							tmp_neighbLocation0 = neighbLocation[1];
							tmp_picSizeInPart0 = picSizeInPart[1];
							if (tmp_neighbLocation >= tmp_picSizeInPart || tmp_neighbLocation0 >= tmp_picSizeInPart0) {
								neighbLocation[0] = -1;
								neighbLocIdx[0] = -1;
							} else {
								tmp_neighbLocation1 = neighbLocation[1];
								local_maskLcuSzMax = maskLcuSzMax;
								tmp_neighbLocation2 = neighbLocation[1];
								tmp_partAddr11 = partAddr[1];
								if ((tmp_neighbLocation1 & local_maskLcuSzMax) == 0 || tmp_neighbLocation2 >> 4 != tmp_partAddr11 >> 4) {
									neighbLocation[0] = -1;
									neighbLocIdx[0] = -1;
								}
								tmp_neighbLocation3 = neighbLocation[0];
								neighbLocation[0] = tmp_neighbLocation3 & ~bitMod;
								tmp_neighbLocation4 = neighbLocation[1];
								neighbLocation[1] = tmp_neighbLocation4 & ~bitMod;
								local_lcuAddr = lcuAddr;
								tmp_puAbsAddrInLcu19 = puAbsAddrInLcu[1];
								local_nPSH = nPSH;
								tmp_puAbsAddrInLcu20 = puAbsAddrInLcu[0];
								local_nPSW = nPSW;
								tmp_neighbLcuAddr4 = neighbLcuAddr[(tmp_puAbsAddrInLcu19 + local_nPSH & ~bitMod) + 1][(tmp_puAbsAddrInLcu20 + local_nPSW & ~bitMod) + 1];
								neighbLocIdx[0] = local_lcuAddr + tmp_neighbLcuAddr4;
								tmp_puAbsAddrInLcu21 = puAbsAddrInLcu[1];
								local_nPSH = nPSH;
								tmp_puAbsAddrInLcu22 = puAbsAddrInLcu[0];
								local_nPSW = nPSW;
								tmp_neighbBlkAddr4 = neighbBlkAddr[(tmp_puAbsAddrInLcu21 + local_nPSH & ~bitMod) + 1][(tmp_puAbsAddrInLcu22 + local_nPSW & ~bitMod) + 1];
								neighbLocIdx[1] = tmp_neighbBlkAddr4;
							}
						} else {
							tmp_partAddr12 = partAddr[0];
							local_nPSW = nPSW;
							neighbLocation[0] = tmp_partAddr12 + local_nPSW / 2;
							tmp_partAddr13 = partAddr[1];
							local_nPSH = nPSH;
							neighbLocation[1] = tmp_partAddr13 + local_nPSH / 2;
							tmp_neighbLocation5 = neighbLocation[1];
							tmp_partAddr14 = partAddr[1];
							if (tmp_neighbLocation5 >> 4 != tmp_partAddr14 >> 4) {
								neighbLocation[1] = -1;
							}
							tmp_neighbLocation6 = neighbLocation[0];
							neighbLocation[0] = tmp_neighbLocation6 & ~bitMod;
							tmp_neighbLocation7 = neighbLocation[1];
							neighbLocation[1] = tmp_neighbLocation7 & ~bitMod;
							local_lcuAddr = lcuAddr;
							tmp_puAbsAddrInLcu23 = puAbsAddrInLcu[1];
							local_nPSH = nPSH;
							tmp_puAbsAddrInLcu24 = puAbsAddrInLcu[0];
							local_nPSW = nPSW;
							tmp_neighbLcuAddr5 = neighbLcuAddr[(tmp_puAbsAddrInLcu23 + local_nPSH / 2 & ~bitMod) + 1][(tmp_puAbsAddrInLcu24 + local_nPSW / 2 & ~bitMod) + 1];
							neighbLocIdx[0] = local_lcuAddr + tmp_neighbLcuAddr5;
							tmp_puAbsAddrInLcu25 = puAbsAddrInLcu[1];
							local_nPSH = nPSH;
							tmp_puAbsAddrInLcu26 = puAbsAddrInLcu[0];
							local_nPSW = nPSW;
							tmp_neighbBlkAddr5 = neighbBlkAddr[(tmp_puAbsAddrInLcu25 + local_nPSH / 2 & ~bitMod) + 1][(tmp_puAbsAddrInLcu26 + local_nPSW / 2 & ~bitMod) + 1];
							neighbLocIdx[1] = tmp_neighbBlkAddr5;
						}
					}
				}
			}
		}
	}
	tmp_neighbLocation8 = neighbLocation[0];
	isNotInPict = (tmp_neighbLocation8 >> 31) << 31;
	tmp_picSizeInPart1 = picSizeInPart[0];
	tmp_neighbLocation9 = neighbLocation[0];
	isNotInPict = isNotInPict | ((tmp_picSizeInPart1 - tmp_neighbLocation9 - 1) >> 31) << 31;
	tmp_neighbLocation10 = neighbLocation[1];
	isNotInPict = isNotInPict | (tmp_neighbLocation10 >> 31) << 31;
	tmp_picSizeInPart2 = picSizeInPart[1];
	tmp_neighbLocation11 = neighbLocation[1];
	isNotInPict = isNotInPict | ((tmp_picSizeInPart2 - tmp_neighbLocation11 - 1) >> 31) << 31;
	tmp_neighbLocation12 = neighbLocation[0];
	neighbLocation[0] = tmp_neighbLocation12 | isNotInPict;
	tmp_neighbLocIdx = neighbLocIdx[0];
	neighbLocIdx[0] = tmp_neighbLocIdx | isNotInPict;
	tmp_neighbLocation13 = neighbLocation[1];
	tmp_slcAddr = slcAddr[1];
	tmp_neighbLocation14 = neighbLocation[1];
	tmp_slcAddr0 = slcAddr[1];
	local_lcuSizeMaxInPart = lcuSizeMaxInPart;
	tmp_neighbLocation15 = neighbLocation[0];
	tmp_slcAddr1 = slcAddr[0];
	if (!depSlcOrCol && (tmp_neighbLocation13 < tmp_slcAddr || tmp_neighbLocation14 < tmp_slcAddr0 + local_lcuSizeMaxInPart && tmp_neighbLocation15 < tmp_slcAddr1)) {
		neighbLocation[0] = -1;
		neighbLocIdx[0] = -1;
	}
	tmp_neighbLocation16 = neighbLocation[0];
	tmp_puTilesBeg = puTilesBeg[0];
	tmp_neighbLocation17 = neighbLocation[0];
	tmp_puTilesEnd = puTilesEnd[0];
	tmp_neighbLocation18 = neighbLocation[1];
	tmp_puTilesBeg0 = puTilesBeg[1];
	tmp_neighbLocation19 = neighbLocation[1];
	tmp_puTilesEnd0 = puTilesEnd[1];
	if (!isColNeighb && (tmp_neighbLocation16 < tmp_puTilesBeg || tmp_neighbLocation17 >= tmp_puTilesEnd || tmp_neighbLocation18 < tmp_puTilesBeg0 || tmp_neighbLocation19 >= tmp_puTilesEnd0)) {
		neighbLocation[0] = -1;
		neighbLocIdx[0] = -1;
	}
}
static void getNonMergedNeighbourMv(u32 listX) {
	i32 neighbLcuAddr;
	i32 neighbBlkAddr;
	i32 sameComponent;
	i32 refIdx1;
	i32 refIdx2;
	i32 currMv[2];
	i32 i;
	i8 local_currIdx;
	i8 tmp_refIdxRef;
	u16 local_lcuAddr;
	u16 local_puAddrInLcu;
	i8 tmp_refIdxRef0;
	i16 tmp_pocRefListX;
	i16 tmp_pocRefListX0;
	i32 local_numCandidate;
	i32 j;
	i16 tmp_mvRef;
	i32 local_predFlag;
	i32 j0;
	i32 tmp_mvPred;
	i32 tmp_mvPred0;
	i32 tmp_currMv;
	i32 tmp_mvPred1;
	i32 tmp_currMv0;

	neighbLcuAddr = neighbLocIdx[0];
	neighbBlkAddr = neighbLocIdx[1];
	sameComponent = 0;
	i = 0;
	predFlag = 0;
	if (neighbLcuAddr >= 0) {
		local_currIdx = currIdx;
		tmp_refIdxRef = refIdxRef[local_currIdx][neighbLcuAddr][neighbBlkAddr][listX];
		local_currIdx = currIdx;
		local_lcuAddr = lcuAddr;
		local_puAddrInLcu = puAddrInLcu;
		tmp_refIdxRef0 = refIdxRef[local_currIdx][local_lcuAddr][local_puAddrInLcu][listX];
		if (tmp_refIdxRef == tmp_refIdxRef0) {
			getNeighbourMvNonMergedNonScaled(listX);
		} else {
			local_currIdx = currIdx;
			refIdx1 = refIdxRef[local_currIdx][neighbLcuAddr][neighbBlkAddr][listX ^ 1];
			local_currIdx = currIdx;
			local_lcuAddr = lcuAddr;
			local_puAddrInLcu = puAddrInLcu;
			refIdx2 = refIdxRef[local_currIdx][local_lcuAddr][local_puAddrInLcu][listX];
			if (refIdx1 != -1 && refIdx2 != -1) {
				tmp_pocRefListX = pocRefListX[listX ^ 1][refIdx1];
				tmp_pocRefListX0 = pocRefListX[listX][refIdx2];
				if (tmp_pocRefListX == tmp_pocRefListX0) {
					predFlag = 1;
					local_numCandidate = numCandidate;
					j = 0;
					while (j <= 1) {
						local_currIdx = currIdx;
						tmp_mvRef = mvRef[local_currIdx][neighbLcuAddr][neighbBlkAddr][listX ^ 1][j];
						mvPred[local_numCandidate][listX][j] = tmp_mvRef;
						j = j + 1;
					}
					local_numCandidate = numCandidate;
					numCandidate = local_numCandidate + 1;
				}
			}
		}
		local_predFlag = predFlag;
		if (local_predFlag) {
			j0 = 0;
			while (j0 <= 1) {
				local_numCandidate = numCandidate;
				tmp_mvPred = mvPred[local_numCandidate - 1][listX][j0];
				currMv[j0] = tmp_mvPred;
				j0 = j0 + 1;
			}
			local_numCandidate = numCandidate;
			while (i < local_numCandidate - 1 && !sameComponent) {
				tmp_mvPred0 = mvPred[i][listX][0];
				tmp_currMv = currMv[0];
				tmp_mvPred1 = mvPred[i][listX][1];
				tmp_currMv0 = currMv[1];
				if (tmp_mvPred0 == tmp_currMv && tmp_mvPred1 == tmp_currMv0) {
					local_numCandidate = numCandidate;
					numCandidate = local_numCandidate - 1;
					sameComponent = 1;
				}
				i = i + 1;
				local_numCandidate = numCandidate;
			}
		}
	}
}
static void getNeighbourMv_MergeIdx_isNotEqToMin1() {
	i32 xN;
	i32 yN;
	i32 neighbLcuAddr;
	i32 neighbBlkAddr;
	i32 tmp_partAddr;
	i8 local_paralMergeLvl;
	i32 tmp_partAddr0;
	i8 local_currIdx;
	i8 tmp_refIdxRef;
	i8 tmp_refIdxRef0;
	i32 local_predFlag;
	i32 local_numCandidate;
	i32 list;
	i32 i;
	i16 tmp_mvRef;
	i32 list0;
	i8 tmp_refIdxRef1;

	xN = neighbLocation[0];
	yN = neighbLocation[1];
	neighbLcuAddr = neighbLocIdx[0];
	neighbBlkAddr = neighbLocIdx[1];
	predFlag = 0;
	tmp_partAddr = partAddr[0];
	local_paralMergeLvl = paralMergeLvl;
	local_paralMergeLvl = paralMergeLvl;
	tmp_partAddr0 = partAddr[1];
	local_paralMergeLvl = paralMergeLvl;
	local_paralMergeLvl = paralMergeLvl;
	if (tmp_partAddr >> local_paralMergeLvl != xN >> local_paralMergeLvl || tmp_partAddr0 >> local_paralMergeLvl != yN >> local_paralMergeLvl) {
		if (neighbLcuAddr >= 0) {
			local_currIdx = currIdx;
			tmp_refIdxRef = refIdxRef[local_currIdx][neighbLcuAddr][neighbBlkAddr][0];
			local_currIdx = currIdx;
			tmp_refIdxRef0 = refIdxRef[local_currIdx][neighbLcuAddr][neighbBlkAddr][1];
			predFlag = tmp_refIdxRef != -1 || tmp_refIdxRef0 != -1;
			local_predFlag = predFlag;
			if (local_predFlag) {
				local_numCandidate = numCandidate;
				list = 0;
				while (list <= 1) {
					i = 0;
					while (i <= 1) {
						local_currIdx = currIdx;
						tmp_mvRef = mvRef[local_currIdx][neighbLcuAddr][neighbBlkAddr][list][i];
						mvPred[local_numCandidate][list][i] = tmp_mvRef;
						i = i + 1;
					}
					list = list + 1;
				}
				local_numCandidate = numCandidate;
				list0 = 0;
				while (list0 <= 1) {
					local_currIdx = currIdx;
					tmp_refIdxRef1 = refIdxRef[local_currIdx][neighbLcuAddr][neighbBlkAddr][list0];
					refIdxPred[local_numCandidate][list0] = tmp_refIdxRef1;
					list0 = list0 + 1;
				}
				local_numCandidate = numCandidate;
				numCandidate = local_numCandidate + 1;
			}
		}
	}
}
static void getNeighbourMvNonMergedNonScaled(u32 listX) {
	i32 neighbLcuAddr;
	i32 neighbBlkAddr;
	i32 sameComponent;
	u32 listAvail;
	i8 local_currIdx;
	i8 tmp_refIdxRef;
	i8 tmp_refIdxRef0;
	i32 local_predFlag;
	i32 i;
	i32 local_numCandidate;
	i32 tmp_mvPred;
	i16 tmp_mvRef;
	i32 tmp_mvPred0;
	i16 tmp_mvRef0;
	i32 tmp_mvPred1;
	i16 tmp_mvRef1;
	i32 tmp_mvPred2;
	i16 tmp_mvRef2;
	i8 tmp_refIdxRef1;
	i32 i0;
	i16 tmp_mvRef3;
	i8 tmp_refIdxRef2;

	neighbLcuAddr = neighbLocIdx[0];
	neighbBlkAddr = neighbLocIdx[1];
	sameComponent = 0;
	predFlag = 0;
	if (neighbLcuAddr >= 0) {
		local_currIdx = currIdx;
		tmp_refIdxRef = refIdxRef[local_currIdx][neighbLcuAddr][neighbBlkAddr][0];
		local_currIdx = currIdx;
		tmp_refIdxRef0 = refIdxRef[local_currIdx][neighbLcuAddr][neighbBlkAddr][1];
		predFlag = tmp_refIdxRef != -1 || tmp_refIdxRef0 != -1;
		local_predFlag = predFlag;
		if (local_predFlag) {
			i = 0;
			local_numCandidate = numCandidate;
			while (i <= local_numCandidate - 1) {
				tmp_mvPred = mvPred[i][0][0];
				local_currIdx = currIdx;
				tmp_mvRef = mvRef[local_currIdx][neighbLcuAddr][neighbBlkAddr][0][0];
				tmp_mvPred0 = mvPred[i][0][1];
				local_currIdx = currIdx;
				tmp_mvRef0 = mvRef[local_currIdx][neighbLcuAddr][neighbBlkAddr][0][1];
				tmp_mvPred1 = mvPred[i][1][0];
				local_currIdx = currIdx;
				tmp_mvRef1 = mvRef[local_currIdx][neighbLcuAddr][neighbBlkAddr][1][0];
				tmp_mvPred2 = mvPred[i][1][1];
				local_currIdx = currIdx;
				tmp_mvRef2 = mvRef[local_currIdx][neighbLcuAddr][neighbBlkAddr][1][1];
				sameComponent = sameComponent || tmp_mvPred == tmp_mvRef && tmp_mvPred0 == tmp_mvRef0 && tmp_mvPred1 == tmp_mvRef1 && tmp_mvPred2 == tmp_mvRef2;
				i = i + 1;
			}
			if (!sameComponent) {
				local_currIdx = currIdx;
				tmp_refIdxRef1 = refIdxRef[local_currIdx][neighbLcuAddr][neighbBlkAddr][listX];
				if (tmp_refIdxRef1 != -1) {
					listAvail = listX;
				} else {
					listAvail = listX ^ 1;
				}
				local_numCandidate = numCandidate;
				i0 = 0;
				while (i0 <= 1) {
					local_currIdx = currIdx;
					tmp_mvRef3 = mvRef[local_currIdx][neighbLcuAddr][neighbBlkAddr][listAvail][i0];
					mvPred[local_numCandidate][listX][i0] = tmp_mvRef3;
					i0 = i0 + 1;
				}
				local_numCandidate = numCandidate;
				local_currIdx = currIdx;
				tmp_refIdxRef2 = refIdxRef[local_currIdx][neighbLcuAddr][neighbBlkAddr][listAvail];
				refIdxPred[local_numCandidate][listX] = tmp_refIdxRef2;
				local_numCandidate = numCandidate;
				numCandidate = local_numCandidate + 1;
			}
		}
	}
}
static void getNeighbourMvNonMergedScaled(u32 listX) {
	i32 neighbLcuAddr;
	i32 neighbBlkAddr;
	u32 listAvail;
	i8 local_currIdx;
	i8 tmp_refIdxRef;
	i8 tmp_refIdxRef0;
	i32 local_predFlag;
	i8 tmp_refIdxRef1;
	i32 local_numCandidate;
	i32 i;
	i16 tmp_mvRef;
	i8 tmp_refIdxRef2;

	neighbLcuAddr = neighbLocIdx[0];
	neighbBlkAddr = neighbLocIdx[1];
	predFlag = 0;
	if (neighbLcuAddr >= 0) {
		local_currIdx = currIdx;
		tmp_refIdxRef = refIdxRef[local_currIdx][neighbLcuAddr][neighbBlkAddr][0];
		local_currIdx = currIdx;
		tmp_refIdxRef0 = refIdxRef[local_currIdx][neighbLcuAddr][neighbBlkAddr][1];
		predFlag = tmp_refIdxRef != -1 || tmp_refIdxRef0 != -1;
		local_predFlag = predFlag;
		if (local_predFlag) {
			local_currIdx = currIdx;
			tmp_refIdxRef1 = refIdxRef[local_currIdx][neighbLcuAddr][neighbBlkAddr][listX];
			if (tmp_refIdxRef1 != -1) {
				listAvail = listX;
			} else {
				listAvail = listX ^ 1;
			}
			local_numCandidate = numCandidate;
			i = 0;
			while (i <= 1) {
				local_currIdx = currIdx;
				tmp_mvRef = mvRef[local_currIdx][neighbLcuAddr][neighbBlkAddr][listAvail][i];
				mvPred[local_numCandidate][listX][i] = tmp_mvRef;
				i = i + 1;
			}
			local_numCandidate = numCandidate;
			local_currIdx = currIdx;
			tmp_refIdxRef2 = refIdxRef[local_currIdx][neighbLcuAddr][neighbBlkAddr][listAvail];
			refIdxPred[local_numCandidate][listX] = tmp_refIdxRef2;
			local_numCandidate = numCandidate;
			numCandidate = local_numCandidate + 1;
		}
	}
}
static void getNonMergedScaledMv(u32 listX) {
	i32 neighbLcuAddr;
	i32 neighbBlkAddr;
	i32 listAvail;
	i32 currMv[2];
	i32 refIdxRefCurrPic;
	i32 i;
	i32 sameComponent;
	i32 mvParam[2];
	i8 local_currIdx;
	i8 tmp_refIdxRef;
	i8 tmp_refIdxRef0;
	i8 tmp_refIdxRef1;
	u16 local_lcuAddr;
	u16 local_puAddrInLcu;
	i32 j;
	i32 local_numCandidate;
	i32 tmp_mvPred;
	i32 j0;
	i32 tmp_mvParam;
	i32 j1;
	i32 tmp_mvPred0;
	i32 tmp_mvPred1;
	i32 tmp_currMv;
	i32 tmp_mvPred2;
	i32 tmp_currMv0;

	neighbLcuAddr = neighbLocIdx[0];
	neighbBlkAddr = neighbLocIdx[1];
	i = 0;
	sameComponent = 0;
	predFlag = 0;
	if (neighbLcuAddr >= 0) {
		local_currIdx = currIdx;
		tmp_refIdxRef = refIdxRef[local_currIdx][neighbLcuAddr][neighbBlkAddr][0];
		local_currIdx = currIdx;
		tmp_refIdxRef0 = refIdxRef[local_currIdx][neighbLcuAddr][neighbBlkAddr][1];
		if (tmp_refIdxRef != -1 || tmp_refIdxRef0 != -1) {
			local_currIdx = currIdx;
			tmp_refIdxRef1 = refIdxRef[local_currIdx][neighbLcuAddr][neighbBlkAddr][listX];
			if (tmp_refIdxRef1 != -1) {
				listAvail = listX;
			} else {
				listAvail = listX ^ 1;
			}
			getNeighbourMvNonMergedScaled(listX);
			local_currIdx = currIdx;
			local_lcuAddr = lcuAddr;
			local_puAddrInLcu = puAddrInLcu;
			refIdxRefCurrPic = refIdxRef[local_currIdx][local_lcuAddr][local_puAddrInLcu][listX];
			if (refIdxRefCurrPic == -1) {
				refIdxRefCurrPic = 0;
			}
			j = 0;
			while (j <= 1) {
				local_numCandidate = numCandidate;
				tmp_mvPred = mvPred[local_numCandidate - 1][listX][j];
				mvParam[j] = tmp_mvPred;
				j = j + 1;
			}
			local_currIdx = currIdx;
			mvScaling(mvParam, refIdxRefCurrPic, listAvail, listX, local_currIdx, pocRefListX, 0);
			local_numCandidate = numCandidate;
			j0 = 0;
			while (j0 <= 1) {
				tmp_mvParam = mvParam[j0];
				mvPred[local_numCandidate - 1][listX][j0] = tmp_mvParam;
				j0 = j0 + 1;
			}
			j1 = 0;
			while (j1 <= 1) {
				local_numCandidate = numCandidate;
				tmp_mvPred0 = mvPred[local_numCandidate - 1][listX][j1];
				currMv[j1] = tmp_mvPred0;
				j1 = j1 + 1;
			}
			local_numCandidate = numCandidate;
			while (i < local_numCandidate - 1 && !sameComponent) {
				tmp_mvPred1 = mvPred[i][listX][0];
				tmp_currMv = currMv[0];
				tmp_mvPred2 = mvPred[i][listX][1];
				tmp_currMv0 = currMv[1];
				if (tmp_mvPred1 == tmp_currMv && tmp_mvPred2 == tmp_currMv0) {
					local_numCandidate = numCandidate;
					numCandidate = local_numCandidate - 1;
					sameComponent = 1;
				}
				i = i + 1;
				local_numCandidate = numCandidate;
			}
		}
	}
}
static void mvScaling(i32 mv[2], i32 refIdxRefCurrPic, u32 listAvail, u32 listX, u32 pictIdx, i16 refList[2][16], i32 isColPict) {
	i32 neighbLcuAddr;
	i32 neighbBlkAddr;
	i32 idxColRef;
	i32 local_colRefIdx;
	i16 local_colSlcIdx;
	i32 pocRefCol;
	i8 local_currIdx;
	u16 local_slcIdx;
	i32 pocRefCurrPic;
	i32 deltaColPic;
	i32 deltaCurrPic;
	i32 td;
	i32 tb;
	i32 tx;
	i32 distScaleFactor;
	i32 newMv;
	i16 tmp_pocRef;
	i16 tmp_pocRef0;
	i32 tmp_abs;
	i32 i;
	i32 tmp_mv;

	neighbLcuAddr = neighbLocIdx[0];
	neighbBlkAddr = neighbLocIdx[1];
	idxColRef = refIdxRef[pictIdx][neighbLcuAddr][neighbBlkAddr][listAvail];
	if (!isColPict) {
		pocRefCol = refList[listAvail][idxColRef];
	} else {
		local_colRefIdx = colRefIdx;
		local_colSlcIdx = colSlcIdx;
		pocRefCol = pocRefList[local_colRefIdx][local_colSlcIdx][listAvail][idxColRef];
	}
	local_currIdx = currIdx;
	local_slcIdx = slcIdx;
	pocRefCurrPic = pocRefList[local_currIdx][local_slcIdx][listX][refIdxRefCurrPic];
	tmp_pocRef = pocRef[pictIdx];
	deltaColPic = tmp_pocRef - pocRefCol;
	local_currIdx = currIdx;
	tmp_pocRef0 = pocRef[local_currIdx];
	deltaCurrPic = tmp_pocRef0 - pocRefCurrPic;
	if (deltaColPic != deltaCurrPic) {
		td = HevcDecoder_generateInfo_MvComponentPred_clip_i32(deltaColPic, -127, 128);
		tb = HevcDecoder_generateInfo_MvComponentPred_clip_i32(deltaCurrPic, -127, 128);
		tmp_abs = HevcDecoder_generateInfo_MvComponentPred_abs(td / 2);
		tx = (16384 + tmp_abs) / td;
		distScaleFactor = HevcDecoder_generateInfo_MvComponentPred_clip_i32((tb * tx + 32) >> 6, -4096, 4095);
		i = 0;
		while (i <= 1) {
			tmp_mv = mv[i];
			newMv = distScaleFactor * tmp_mv;
			if (newMv >= 0) {
				newMv = (newMv + 127) >> 8;
			} else {
				newMv = -((-newMv + 127) >> 8);
			}
			mv[i] = newMv;
			i = i + 1;
		}
	}
}
static void getColCandidate(i32 isMerged, u32 listX) {
	i32 local_RIGHT_BOTTOM;
	i32 local_predFlag;
	i32 local_CENTER;

	if (isMerged) {
		listX = 0;
	}
	local_RIGHT_BOTTOM = RIGHT_BOTTOM;
	getNeighbAddr(local_RIGHT_BOTTOM, 1, 1);
	getColNeighbourMv(isMerged, listX);
	local_predFlag = predFlag;
	if (!local_predFlag) {
		local_CENTER = CENTER;
		getNeighbAddr(local_CENTER, 1, 1);
		getColNeighbourMv(isMerged, listX);
	}
}
static void getColNeighbourMv(i32 isMerged, u32 listX) {
	i32 neighbLcuAddr;
	i32 neighbBlkAddr;
	i32 mv[2][2];
	i32 refIdxRefCurrPic;
	i32 refIdxRefCurrPicL1;
	i32 listAvail[2];
	i32 mvScal[2];
	i32 local_colRefIdx;
	i8 tmp_refIdxRef;
	i8 tmp_refIdxRef0;
	i32 local_predFlag;
	i32 i;
	i32 j;
	i16 tmp_mvRef;
	i8 tmp_refIdxRef1;
	i32 tmp_mv;
	i32 tmp_mv0;
	i8 tmp_refIdxRef2;
	i32 tmp_mv1;
	i32 tmp_mv2;
	i32 local_useLN;
	u8 local_colocFromL0;
	i32 tmp_mv3;
	i32 tmp_mv4;
	i32 tmp_mv5;
	i32 tmp_mv6;
	i32 i0;
	i32 tmp_mv7;
	i32 tmp_listAvail;
	i32 i1;
	i32 tmp_mvScal;
	i32 i2;
	i32 tmp_mv8;
	i32 tmp_listAvail0;
	i32 i3;
	i32 tmp_mvScal0;
	i32 local_numCandidate;
	i32 i4;
	i32 j0;
	i32 tmp_mv9;
	i8 tmp_refIdxRef3;
	i8 tmp_refIdxRef4;
	i8 tmp_refIdxRef5;
	i32 tmp_partAddr;
	i32 tmp_partAddr0;
	u16 local_lcuAddr;
	u16 local_puAddrInLcu;
	i32 tmp_isInter;
	i8 local_currIdx;
	i32 i5;
	i32 tmp_listAvail1;
	i32 tmp_mv10;
	i32 tmp_listAvail2;
	i32 tmp_listAvail3;
	i32 i6;
	i32 tmp_mvScal1;
	i32 i7;
	i32 tmp_listAvail4;
	i32 tmp_mv11;

	neighbLcuAddr = neighbLocIdx[0];
	neighbBlkAddr = neighbLocIdx[1];
	predFlag = 0;
	if (neighbLcuAddr >= 0) {
		local_colRefIdx = colRefIdx;
		tmp_refIdxRef = refIdxRef[local_colRefIdx][neighbLcuAddr][neighbBlkAddr][0];
		local_colRefIdx = colRefIdx;
		tmp_refIdxRef0 = refIdxRef[local_colRefIdx][neighbLcuAddr][neighbBlkAddr][1];
		predFlag = tmp_refIdxRef != -1 || tmp_refIdxRef0 != -1;
		local_predFlag = predFlag;
		if (local_predFlag) {
			i = 0;
			while (i <= 1) {
				j = 0;
				while (j <= 1) {
					local_colRefIdx = colRefIdx;
					tmp_mvRef = mvRef[local_colRefIdx][neighbLcuAddr][neighbBlkAddr][i][j];
					mv[i][j] = tmp_mvRef;
					j = j + 1;
				}
				i = i + 1;
			}
			if (isMerged) {
				refIdxRefCurrPic = 0;
				refIdxRefCurrPicL1 = 0;
				local_colRefIdx = colRefIdx;
				tmp_refIdxRef1 = refIdxRef[local_colRefIdx][neighbLcuAddr][neighbBlkAddr][1];
				if (tmp_refIdxRef1 == -1) {
					tmp_mv = mv[0][0];
					mv[1][0] = tmp_mv;
					tmp_mv0 = mv[0][1];
					mv[1][1] = tmp_mv0;
					listAvail[0] = 0;
					listAvail[1] = 0;
				} else {
					local_colRefIdx = colRefIdx;
					tmp_refIdxRef2 = refIdxRef[local_colRefIdx][neighbLcuAddr][neighbBlkAddr][0];
					if (tmp_refIdxRef2 == -1) {
						tmp_mv1 = mv[1][0];
						mv[0][0] = tmp_mv1;
						tmp_mv2 = mv[1][1];
						mv[0][1] = tmp_mv2;
						listAvail[0] = 1;
						listAvail[1] = 1;
					} else {
						local_useLN = useLN;
						if (local_useLN) {
							local_colocFromL0 = colocFromL0;
							if (local_colocFromL0 == 0) {
								tmp_mv3 = mv[0][0];
								mv[1][0] = tmp_mv3;
								tmp_mv4 = mv[0][1];
								mv[1][1] = tmp_mv4;
								listAvail[0] = 0;
								listAvail[1] = 0;
							} else {
								tmp_mv5 = mv[1][0];
								mv[0][0] = tmp_mv5;
								tmp_mv6 = mv[1][1];
								mv[0][1] = tmp_mv6;
								listAvail[0] = 1;
								listAvail[1] = 1;
							}
						} else {
							listAvail[0] = 0;
							listAvail[1] = 1;
						}
					}
				}
				searchColSlcAddr(neighbLocation);
				i0 = 0;
				while (i0 <= 1) {
					tmp_mv7 = mv[0][i0];
					mvScal[i0] = tmp_mv7;
					i0 = i0 + 1;
				}
				tmp_listAvail = listAvail[0];
				local_colRefIdx = colRefIdx;
				mvScaling(mvScal, refIdxRefCurrPic, tmp_listAvail, 0, local_colRefIdx, pocRefListX, 1);
				i1 = 0;
				while (i1 <= 1) {
					tmp_mvScal = mvScal[i1];
					mv[0][i1] = tmp_mvScal;
					i1 = i1 + 1;
				}
				i2 = 0;
				while (i2 <= 1) {
					tmp_mv8 = mv[1][i2];
					mvScal[i2] = tmp_mv8;
					i2 = i2 + 1;
				}
				tmp_listAvail0 = listAvail[1];
				local_colRefIdx = colRefIdx;
				mvScaling(mvScal, refIdxRefCurrPicL1, tmp_listAvail0, 1, local_colRefIdx, pocRefListX, 1);
				i3 = 0;
				while (i3 <= 1) {
					tmp_mvScal0 = mvScal[i3];
					mv[1][i3] = tmp_mvScal0;
					i3 = i3 + 1;
				}
				local_numCandidate = numCandidate;
				refIdxPred[local_numCandidate][0] = refIdxRefCurrPic;
				local_numCandidate = numCandidate;
				refIdxPred[local_numCandidate][1] = refIdxRefCurrPicL1;
				local_numCandidate = numCandidate;
				i4 = 0;
				while (i4 <= 1) {
					j0 = 0;
					while (j0 <= 1) {
						tmp_mv9 = mv[i4][j0];
						mvPred[local_numCandidate][i4][j0] = tmp_mv9;
						j0 = j0 + 1;
					}
					i4 = i4 + 1;
				}
			} else {
				local_colRefIdx = colRefIdx;
				tmp_refIdxRef3 = refIdxRef[local_colRefIdx][neighbLcuAddr][neighbBlkAddr][listX];
				if (tmp_refIdxRef3 != -1) {
					listAvail[0] = listX;
				} else {
					listAvail[0] = listX ^ 1;
				}
				local_colRefIdx = colRefIdx;
				tmp_refIdxRef4 = refIdxRef[local_colRefIdx][neighbLcuAddr][neighbBlkAddr][0];
				local_colRefIdx = colRefIdx;
				tmp_refIdxRef5 = refIdxRef[local_colRefIdx][neighbLcuAddr][neighbBlkAddr][1];
				local_useLN = useLN;
				if (tmp_refIdxRef4 != -1 && tmp_refIdxRef5 != -1 && local_useLN) {
					local_colocFromL0 = colocFromL0;
					listAvail[0] = local_colocFromL0;
				}
				tmp_partAddr = partAddr[0];
				tmp_partAddr0 = partAddr[1];
				local_lcuAddr = lcuAddr;
				local_puAddrInLcu = puAddrInLcu;
				tmp_isInter = isInter(tmp_partAddr, tmp_partAddr0, local_lcuAddr, local_puAddrInLcu);
				if (tmp_isInter) {
					local_currIdx = currIdx;
					local_lcuAddr = lcuAddr;
					local_puAddrInLcu = puAddrInLcu;
					refIdxRefCurrPic = refIdxRef[local_currIdx][local_lcuAddr][local_puAddrInLcu][listX];
				} else {
					refIdxRefCurrPic = 0;
				}
				if (refIdxRefCurrPic == -1) {
					refIdxRefCurrPic = 0;
				}
				searchColSlcAddr(neighbLocation);
				i5 = 0;
				while (i5 <= 1) {
					tmp_listAvail1 = listAvail[0];
					tmp_mv10 = mv[tmp_listAvail1][i5];
					mvScal[i5] = tmp_mv10;
					i5 = i5 + 1;
				}
				tmp_listAvail2 = listAvail[0];
				local_colRefIdx = colRefIdx;
				mvScaling(mvScal, refIdxRefCurrPic, tmp_listAvail2, listX, local_colRefIdx, pocRefListX, 1);
				tmp_listAvail3 = listAvail[0];
				i6 = 0;
				while (i6 <= 1) {
					tmp_mvScal1 = mvScal[i6];
					mv[tmp_listAvail3][i6] = tmp_mvScal1;
					i6 = i6 + 1;
				}
				local_numCandidate = numCandidate;
				i7 = 0;
				while (i7 <= 1) {
					tmp_listAvail4 = listAvail[0];
					tmp_mv11 = mv[tmp_listAvail4][i7];
					mvPred[local_numCandidate][listX][i7] = tmp_mv11;
					i7 = i7 + 1;
				}
				local_numCandidate = numCandidate;
				refIdxPred[local_numCandidate][listX] = refIdxRefCurrPic;
			}
			local_numCandidate = numCandidate;
			numCandidate = local_numCandidate + 1;
		}
	}
}
static void biPredMergeCand(u32 maxNumCandidate) {
	i32 local_numCandidate;
	i32 combIdxMax;
	i32 combIdx;
	u32 l0CandIdx;
	u32 l1CandIdx;
	i32 refIdxL0Cand;
	i32 refIdxL1Cand;
	u32 mvL0Cand[2];
	u32 mvL1Cand[2];
	i32 i;
	i32 tmp_mvPred;
	i32 i0;
	i32 tmp_mvPred0;
	i16 tmp_pocRefListX;
	i16 tmp_pocRefListX0;
	u32 tmp_mvL0Cand;
	u32 tmp_mvL1Cand;
	u32 tmp_mvL0Cand0;
	u32 tmp_mvL1Cand0;
	i32 i1;
	u32 tmp_mvL0Cand1;
	i32 i2;
	u32 tmp_mvL1Cand1;

	local_numCandidate = numCandidate;
	local_numCandidate = numCandidate;
	combIdxMax = local_numCandidate * (local_numCandidate - 1);
	combIdx = 0;
	local_numCandidate = numCandidate;
	while (combIdx != combIdxMax && local_numCandidate != maxNumCandidate) {
		l0CandIdx = combIdxToLXCandIdx[combIdx][0];
		l1CandIdx = combIdxToLXCandIdx[combIdx][1];
		refIdxL0Cand = refIdxPred[l0CandIdx][0];
		refIdxL1Cand = refIdxPred[l1CandIdx][1];
		i = 0;
		while (i <= 1) {
			tmp_mvPred = mvPred[l0CandIdx][0][i];
			mvL0Cand[i] = tmp_mvPred;
			i = i + 1;
		}
		i0 = 0;
		while (i0 <= 1) {
			tmp_mvPred0 = mvPred[l1CandIdx][1][i0];
			mvL1Cand[i0] = tmp_mvPred0;
			i0 = i0 + 1;
		}
		if (refIdxL0Cand != -1 && refIdxL1Cand != -1) {
			tmp_pocRefListX = pocRefListX[0][refIdxL0Cand];
			tmp_pocRefListX0 = pocRefListX[1][refIdxL1Cand];
			tmp_mvL0Cand = mvL0Cand[0];
			tmp_mvL1Cand = mvL1Cand[0];
			tmp_mvL0Cand0 = mvL0Cand[1];
			tmp_mvL1Cand0 = mvL1Cand[1];
			if (tmp_pocRefListX != tmp_pocRefListX0 || tmp_mvL0Cand != tmp_mvL1Cand || tmp_mvL0Cand0 != tmp_mvL1Cand0) {
				local_numCandidate = numCandidate;
				i1 = 0;
				while (i1 <= 1) {
					tmp_mvL0Cand1 = mvL0Cand[i1];
					mvPred[local_numCandidate][0][i1] = tmp_mvL0Cand1;
					i1 = i1 + 1;
				}
				local_numCandidate = numCandidate;
				i2 = 0;
				while (i2 <= 1) {
					tmp_mvL1Cand1 = mvL1Cand[i2];
					mvPred[local_numCandidate][1][i2] = tmp_mvL1Cand1;
					i2 = i2 + 1;
				}
				local_numCandidate = numCandidate;
				refIdxPred[local_numCandidate][0] = refIdxL0Cand;
				local_numCandidate = numCandidate;
				refIdxPred[local_numCandidate][1] = refIdxL1Cand;
				local_numCandidate = numCandidate;
				numCandidate = local_numCandidate + 1;
			}
		}
		combIdx = combIdx + 1;
		local_numCandidate = numCandidate;
	}
}

////////////////////////////////////////////////////////////////////////////////
// Actions
static i32 isSchedulable_isNewPicOrSlice() {
	i32 result;
	u8 partMode;
	u8 local_PART_MODE_SLICE_DEP;
	u8 local_PART_MODE_SLICE_INDEP;
	u8 local_PART_MODE_PICT;

	partMode = tokens_PartMode[(index_PartMode + (0)) % SIZE_PartMode];
	local_PART_MODE_SLICE_DEP = HevcDecoder_generateInfo_MvComponentPred_PART_MODE_SLICE_DEP;
	local_PART_MODE_SLICE_INDEP = HevcDecoder_generateInfo_MvComponentPred_PART_MODE_SLICE_INDEP;
	local_PART_MODE_PICT = HevcDecoder_generateInfo_MvComponentPred_PART_MODE_PICT;
	result = partMode == local_PART_MODE_SLICE_DEP || partMode == local_PART_MODE_SLICE_INDEP || partMode == local_PART_MODE_PICT;
	return result;
}

static void isNewPicOrSlice() {

	u8 partMode;
	i16 paralMergeLevel;
	i16 tmvpFlag;
	u16 tmp_SliceAddr;
	u16 tmp_SliceAddr0;
	u8 local_PART_MODE_SLICE_DEP;
	u8 local_PART_MODE_PICT;
	i32 local_DEBUG_PartMode;
	u8 local_PART_MODE_SLICE_INDEP;
	u16 local_slcIdx;
	i8 local_currIdx;
	i32 i;
	u16 tmp_slcAddr;
	u16 tmp_numSlcPerPict;

	partMode = tokens_PartMode[(index_PartMode + (0)) % SIZE_PartMode];
	paralMergeLevel = tokens_SyntaxElem[(index_SyntaxElem + (0)) % SIZE_SyntaxElem];
	tmvpFlag = tokens_SyntaxElem[(index_SyntaxElem + (1)) % SIZE_SyntaxElem];
	tmp_SliceAddr = tokens_SliceAddr[(index_SliceAddr % SIZE_SliceAddr) + (0)];
	slcAddr[0] = tmp_SliceAddr / 4;
	tmp_SliceAddr0 = tokens_SliceAddr[(index_SliceAddr % SIZE_SliceAddr) + (1)];
	slcAddr[1] = tmp_SliceAddr0 / 4;
	local_PART_MODE_SLICE_DEP = HevcDecoder_generateInfo_MvComponentPred_PART_MODE_SLICE_DEP;
	dependSlc = partMode == local_PART_MODE_SLICE_DEP;
	local_PART_MODE_PICT = HevcDecoder_generateInfo_MvComponentPred_PART_MODE_PICT;
	newPict = partMode == local_PART_MODE_PICT;
	enTmpMvp = tmvpFlag != 0;
	paralMergeLvl = paralMergeLevel - 2;
	local_DEBUG_PartMode = DEBUG_PartMode;
	if (local_DEBUG_PartMode) {
		printf("partMode = %u\n", partMode);
	}
	nbList = 0;
	local_PART_MODE_PICT = HevcDecoder_generateInfo_MvComponentPred_PART_MODE_PICT;
	if (partMode == local_PART_MODE_PICT) {
		slcIdx = 0;
	} else {
		local_PART_MODE_SLICE_INDEP = HevcDecoder_generateInfo_MvComponentPred_PART_MODE_SLICE_INDEP;
		if (partMode == local_PART_MODE_SLICE_INDEP) {
			local_slcIdx = slcIdx;
			slcIdx = local_slcIdx + 1;
			local_currIdx = currIdx;
			local_slcIdx = slcIdx;
			i = 0;
			while (i <= 1) {
				tmp_slcAddr = slcAddr[i];
				slcAddrRef[local_currIdx][local_slcIdx][i] = tmp_slcAddr;
				i = i + 1;
			}
			local_currIdx = currIdx;
			local_currIdx = currIdx;
			tmp_numSlcPerPict = numSlcPerPict[local_currIdx];
			numSlcPerPict[local_currIdx] = tmp_numSlcPerPict + 1;
		}
	}

	// Update ports indexes
	index_PartMode += 1;
	index_SliceAddr += 2;
	read_end_SliceAddr();
	index_SyntaxElem += 2;
	read_end_SyntaxElem();

	rate_PartMode += 1;
	rate_SliceAddr += 2;
	rate_SyntaxElem += 2;
}
static void isNewPicOrSlice_aligned() {

	u8 partMode;
	i16 paralMergeLevel;
	i16 tmvpFlag;
	u16 tmp_SliceAddr;
	u16 tmp_SliceAddr0;
	u8 local_PART_MODE_SLICE_DEP;
	u8 local_PART_MODE_PICT;
	i32 local_DEBUG_PartMode;
	u8 local_PART_MODE_SLICE_INDEP;
	u16 local_slcIdx;
	i8 local_currIdx;
	i32 i;
	u16 tmp_slcAddr;
	u16 tmp_numSlcPerPict;

	partMode = tokens_PartMode[(index_PartMode + (0)) % SIZE_PartMode];
	paralMergeLevel = tokens_SyntaxElem[(index_SyntaxElem % SIZE_SyntaxElem) + (0)];
	tmvpFlag = tokens_SyntaxElem[(index_SyntaxElem % SIZE_SyntaxElem) + (1)];
	tmp_SliceAddr = tokens_SliceAddr[(index_SliceAddr % SIZE_SliceAddr) + (0)];
	slcAddr[0] = tmp_SliceAddr / 4;
	tmp_SliceAddr0 = tokens_SliceAddr[(index_SliceAddr % SIZE_SliceAddr) + (1)];
	slcAddr[1] = tmp_SliceAddr0 / 4;
	local_PART_MODE_SLICE_DEP = HevcDecoder_generateInfo_MvComponentPred_PART_MODE_SLICE_DEP;
	dependSlc = partMode == local_PART_MODE_SLICE_DEP;
	local_PART_MODE_PICT = HevcDecoder_generateInfo_MvComponentPred_PART_MODE_PICT;
	newPict = partMode == local_PART_MODE_PICT;
	enTmpMvp = tmvpFlag != 0;
	paralMergeLvl = paralMergeLevel - 2;
	local_DEBUG_PartMode = DEBUG_PartMode;
	if (local_DEBUG_PartMode) {
		printf("partMode = %u\n", partMode);
	}
	nbList = 0;
	local_PART_MODE_PICT = HevcDecoder_generateInfo_MvComponentPred_PART_MODE_PICT;
	if (partMode == local_PART_MODE_PICT) {
		slcIdx = 0;
	} else {
		local_PART_MODE_SLICE_INDEP = HevcDecoder_generateInfo_MvComponentPred_PART_MODE_SLICE_INDEP;
		if (partMode == local_PART_MODE_SLICE_INDEP) {
			local_slcIdx = slcIdx;
			slcIdx = local_slcIdx + 1;
			local_currIdx = currIdx;
			local_slcIdx = slcIdx;
			i = 0;
			while (i <= 1) {
				tmp_slcAddr = slcAddr[i];
				slcAddrRef[local_currIdx][local_slcIdx][i] = tmp_slcAddr;
				i = i + 1;
			}
			local_currIdx = currIdx;
			local_currIdx = currIdx;
			tmp_numSlcPerPict = numSlcPerPict[local_currIdx];
			numSlcPerPict[local_currIdx] = tmp_numSlcPerPict + 1;
		}
	}

	// Update ports indexes
	index_PartMode += 1;
	index_SliceAddr += 2;
	read_end_SliceAddr();
	index_SyntaxElem += 2;
	read_end_SyntaxElem();

	rate_PartMode += 1;
	rate_SliceAddr += 2;
	rate_SyntaxElem += 2;
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
	tilesBeg[local_iLoop][0] = tmp_TilesCoord / 4;
	tmp_TilesCoord0 = tokens_TilesCoord[(index_TilesCoord + (1)) % SIZE_TilesCoord];
	tilesBeg[local_iLoop][1] = tmp_TilesCoord0 / 4;
	local_iLoop = iLoop;
	tmp_TilesCoord1 = tokens_TilesCoord[(index_TilesCoord + (2)) % SIZE_TilesCoord];
	tilesEnd[local_iLoop][0] = tmp_TilesCoord1 / 4;
	tmp_TilesCoord2 = tokens_TilesCoord[(index_TilesCoord + (3)) % SIZE_TilesCoord];
	tilesEnd[local_iLoop][1] = tmp_TilesCoord2 / 4;
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
	tilesBeg[local_iLoop][0] = tmp_TilesCoord / 4;
	tmp_TilesCoord0 = tokens_TilesCoord[(index_TilesCoord % SIZE_TilesCoord) + (1)];
	tilesBeg[local_iLoop][1] = tmp_TilesCoord0 / 4;
	local_iLoop = iLoop;
	tmp_TilesCoord1 = tokens_TilesCoord[(index_TilesCoord % SIZE_TilesCoord) + (2)];
	tilesEnd[local_iLoop][0] = tmp_TilesCoord1 / 4;
	tmp_TilesCoord2 = tokens_TilesCoord[(index_TilesCoord % SIZE_TilesCoord) + (3)];
	tilesEnd[local_iLoop][1] = tmp_TilesCoord2 / 4;
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
static i32 isSchedulable_checkDepSlc_isTrue() {
	i32 result;
	i32 local_dependSlc;

	local_dependSlc = dependSlc;
	result = local_dependSlc;
	return result;
}

static void checkDepSlc_isTrue() {



	// Update ports indexes

}
static i32 isSchedulable_checkDepSlc_isFalse() {
	i32 result;
	i32 local_dependSlc;

	local_dependSlc = dependSlc;
	result = !local_dependSlc;
	return result;
}

static void checkDepSlc_isFalse() {

	i16 colFromLX;
	i16 colRefIdxVal;
	u8 log2_lcuSz;
	i16 poc;
	u8 sliceType;
	u16 valNumTiles;
	u16 lcuIdxOff;
	u8 local_B_SLICE;
	i16 local_MIN_INT16;
	i32 i;
	i32 local_newPict;
	i32 i0;
	i8 local_currIdx;
	i32 tmp_isRef;
	i32 tmp_isRef0;
	i16 tmp_pocRef;
	i32 i1;
	u16 tmp_slcAddr;
	i32 y;
	u16 tmp_PicSize;
	i32 x;
	u16 tmp_PicSize0;
	i32 j;
	i32 local_PICT_WIDTH_POW_2;
	i32 local_isBSlice;
	i32 local_DEBUG_PicSize;
	u16 tmp_PicSize1;
	u16 tmp_PicSize2;
	u16 tmp_PicSize3;
	u16 tmp_PicSize4;
	u8 local_lcuSizeMaxInPart;

	colFromLX = tokens_SyntaxElem[(index_SyntaxElem + (0)) % SIZE_SyntaxElem];
	colRefIdxVal = tokens_SyntaxElem[(index_SyntaxElem + (1)) % SIZE_SyntaxElem];
	log2_lcuSz = tokens_LcuSizeMax[(index_LcuSizeMax + (0)) % SIZE_LcuSizeMax];
	poc = tokens_Poc[(index_Poc + (0)) % SIZE_Poc];
	sliceType = tokens_SliceType[(index_SliceType + (0)) % SIZE_SliceType];
	valNumTiles = tokens_TilesCoord[(index_TilesCoord + (0)) % SIZE_TilesCoord];
	local_B_SLICE = HevcDecoder_generateInfo_MvComponentPred_B_SLICE;
	isBSlice = sliceType == local_B_SLICE;
	listIdx = 0;
	local_MIN_INT16 = HevcDecoder_generateInfo_MvComponentPred_MIN_INT16;
	maxPoc = local_MIN_INT16;
	i = 0;
	while (i <= 16) {
		isStillRef[i] = 0;
		i = i + 1;
	}
	local_newPict = newPict;
	if (local_newPict) {
		currIdx = -1;
		i0 = 0;
		while (i0 <= 16) {
			local_currIdx = currIdx;
			tmp_isRef = isRef[i0];
			tmp_isRef0 = isRef[i0];
			tmp_pocRef = pocRef[i0];
			if (local_currIdx == -1 && !tmp_isRef || tmp_isRef0 && tmp_pocRef == poc) {
				currIdx = i0;
			}
			i0 = i0 + 1;
		}
		local_currIdx = currIdx;
		numSlcPerPict[local_currIdx] = 1;
		local_currIdx = currIdx;
		i1 = 0;
		while (i1 <= 1) {
			tmp_slcAddr = slcAddr[i1];
			slcAddrRef[local_currIdx][0][i1] = tmp_slcAddr;
			i1 = i1 + 1;
		}
		lcuIdxOff = 0;
		y = 0;
		tmp_PicSize = tokens_PicSize[(index_PicSize % SIZE_PicSize) + (1)];
		while (y <= (tmp_PicSize + 63) / 64 - 1) {
			x = 0;
			tmp_PicSize0 = tokens_PicSize[(index_PicSize % SIZE_PicSize) + (0)];
			while (x <= (tmp_PicSize0 + 63) / 64 - 1) {
				j = 0;
				while (j <= 255) {
					local_currIdx = currIdx;
					refIdxRef[local_currIdx][lcuIdxOff + x][j][0] = -1;
					refIdxRef[local_currIdx][lcuIdxOff + x][j][1] = -1;
					j = j + 1;
				}
				x = x + 1;
			}
			local_PICT_WIDTH_POW_2 = HevcDecoder_generateInfo_MvComponentPred_PICT_WIDTH_POW_2;
			lcuIdxOff = lcuIdxOff + local_PICT_WIDTH_POW_2 / 64;
			y = y + 1;
		}
	}
	local_currIdx = currIdx;
	isRef[local_currIdx] = 1;
	local_currIdx = currIdx;
	pocRef[local_currIdx] = poc;
	colRefIdx = colRefIdxVal & 15;
	local_isBSlice = isBSlice;
	if (local_isBSlice) {
		colFromLX = 1 - colFromLX;
	} else {
		colFromLX = 0;
	}
	colocFromL0 = colFromLX ^ 1;
	local_DEBUG_PicSize = DEBUG_PicSize;
	if (local_DEBUG_PicSize) {
		tmp_PicSize1 = tokens_PicSize[(index_PicSize % SIZE_PicSize) + (0)];
		tmp_PicSize2 = tokens_PicSize[(index_PicSize % SIZE_PicSize) + (1)];
		printf("picSize = %u %u\n", tmp_PicSize1, tmp_PicSize2);
	}
	tmp_PicSize3 = tokens_PicSize[(index_PicSize % SIZE_PicSize) + (0)];
	picSizeInPart[0] = tmp_PicSize3 / 4;
	tmp_PicSize4 = tokens_PicSize[(index_PicSize % SIZE_PicSize) + (1)];
	picSizeInPart[1] = tmp_PicSize4 / 4;
	numTiles = valNumTiles;
	iLoop = 0;
	lcuSizeMaxInPart = (1 << log2_lcuSz) / 4;
	local_lcuSizeMaxInPart = lcuSizeMaxInPart;
	maskLcuSzMax = local_lcuSizeMaxInPart - 1;
	tokens_IsReadOrNewSlice[(index_IsReadOrNewSlice + (0)) % SIZE_IsReadOrNewSlice] = 0;

	// Update ports indexes
	index_SyntaxElem += 2;
	read_end_SyntaxElem();
	index_LcuSizeMax += 1;
	index_PicSize += 2;
	read_end_PicSize();
	index_Poc += 1;
	index_SliceType += 1;
	index_TilesCoord += 1;
	index_IsReadOrNewSlice += 1;

	rate_SyntaxElem += 2;
	rate_LcuSizeMax += 1;
	rate_PicSize += 2;
	rate_Poc += 1;
	rate_SliceType += 1;
	rate_TilesCoord += 1;
}
static void checkDepSlc_isFalse_aligned() {

	i16 colFromLX;
	i16 colRefIdxVal;
	u8 log2_lcuSz;
	i16 poc;
	u8 sliceType;
	u16 valNumTiles;
	u16 lcuIdxOff;
	u8 local_B_SLICE;
	i16 local_MIN_INT16;
	i32 i;
	i32 local_newPict;
	i32 i0;
	i8 local_currIdx;
	i32 tmp_isRef;
	i32 tmp_isRef0;
	i16 tmp_pocRef;
	i32 i1;
	u16 tmp_slcAddr;
	i32 y;
	u16 tmp_PicSize;
	i32 x;
	u16 tmp_PicSize0;
	i32 j;
	i32 local_PICT_WIDTH_POW_2;
	i32 local_isBSlice;
	i32 local_DEBUG_PicSize;
	u16 tmp_PicSize1;
	u16 tmp_PicSize2;
	u16 tmp_PicSize3;
	u16 tmp_PicSize4;
	u8 local_lcuSizeMaxInPart;

	colFromLX = tokens_SyntaxElem[(index_SyntaxElem % SIZE_SyntaxElem) + (0)];
	colRefIdxVal = tokens_SyntaxElem[(index_SyntaxElem % SIZE_SyntaxElem) + (1)];
	log2_lcuSz = tokens_LcuSizeMax[(index_LcuSizeMax + (0)) % SIZE_LcuSizeMax];
	poc = tokens_Poc[(index_Poc + (0)) % SIZE_Poc];
	sliceType = tokens_SliceType[(index_SliceType + (0)) % SIZE_SliceType];
	valNumTiles = tokens_TilesCoord[(index_TilesCoord + (0)) % SIZE_TilesCoord];
	local_B_SLICE = HevcDecoder_generateInfo_MvComponentPred_B_SLICE;
	isBSlice = sliceType == local_B_SLICE;
	listIdx = 0;
	local_MIN_INT16 = HevcDecoder_generateInfo_MvComponentPred_MIN_INT16;
	maxPoc = local_MIN_INT16;
	i = 0;
	while (i <= 16) {
		isStillRef[i] = 0;
		i = i + 1;
	}
	local_newPict = newPict;
	if (local_newPict) {
		currIdx = -1;
		i0 = 0;
		while (i0 <= 16) {
			local_currIdx = currIdx;
			tmp_isRef = isRef[i0];
			tmp_isRef0 = isRef[i0];
			tmp_pocRef = pocRef[i0];
			if (local_currIdx == -1 && !tmp_isRef || tmp_isRef0 && tmp_pocRef == poc) {
				currIdx = i0;
			}
			i0 = i0 + 1;
		}
		local_currIdx = currIdx;
		numSlcPerPict[local_currIdx] = 1;
		local_currIdx = currIdx;
		i1 = 0;
		while (i1 <= 1) {
			tmp_slcAddr = slcAddr[i1];
			slcAddrRef[local_currIdx][0][i1] = tmp_slcAddr;
			i1 = i1 + 1;
		}
		lcuIdxOff = 0;
		y = 0;
		tmp_PicSize = tokens_PicSize[(index_PicSize % SIZE_PicSize) + (1)];
		while (y <= (tmp_PicSize + 63) / 64 - 1) {
			x = 0;
			tmp_PicSize0 = tokens_PicSize[(index_PicSize % SIZE_PicSize) + (0)];
			while (x <= (tmp_PicSize0 + 63) / 64 - 1) {
				j = 0;
				while (j <= 255) {
					local_currIdx = currIdx;
					refIdxRef[local_currIdx][lcuIdxOff + x][j][0] = -1;
					refIdxRef[local_currIdx][lcuIdxOff + x][j][1] = -1;
					j = j + 1;
				}
				x = x + 1;
			}
			local_PICT_WIDTH_POW_2 = HevcDecoder_generateInfo_MvComponentPred_PICT_WIDTH_POW_2;
			lcuIdxOff = lcuIdxOff + local_PICT_WIDTH_POW_2 / 64;
			y = y + 1;
		}
	}
	local_currIdx = currIdx;
	isRef[local_currIdx] = 1;
	local_currIdx = currIdx;
	pocRef[local_currIdx] = poc;
	colRefIdx = colRefIdxVal & 15;
	local_isBSlice = isBSlice;
	if (local_isBSlice) {
		colFromLX = 1 - colFromLX;
	} else {
		colFromLX = 0;
	}
	colocFromL0 = colFromLX ^ 1;
	local_DEBUG_PicSize = DEBUG_PicSize;
	if (local_DEBUG_PicSize) {
		tmp_PicSize1 = tokens_PicSize[(index_PicSize % SIZE_PicSize) + (0)];
		tmp_PicSize2 = tokens_PicSize[(index_PicSize % SIZE_PicSize) + (1)];
		printf("picSize = %u %u\n", tmp_PicSize1, tmp_PicSize2);
	}
	tmp_PicSize3 = tokens_PicSize[(index_PicSize % SIZE_PicSize) + (0)];
	picSizeInPart[0] = tmp_PicSize3 / 4;
	tmp_PicSize4 = tokens_PicSize[(index_PicSize % SIZE_PicSize) + (1)];
	picSizeInPart[1] = tmp_PicSize4 / 4;
	numTiles = valNumTiles;
	iLoop = 0;
	lcuSizeMaxInPart = (1 << log2_lcuSz) / 4;
	local_lcuSizeMaxInPart = lcuSizeMaxInPart;
	maskLcuSzMax = local_lcuSizeMaxInPart - 1;
	tokens_IsReadOrNewSlice[(index_IsReadOrNewSlice + (0)) % SIZE_IsReadOrNewSlice] = 0;

	// Update ports indexes
	index_SyntaxElem += 2;
	read_end_SyntaxElem();
	index_LcuSizeMax += 1;
	index_PicSize += 2;
	read_end_PicSize();
	index_Poc += 1;
	index_SliceType += 1;
	index_TilesCoord += 1;
	index_IsReadOrNewSlice += 1;

	rate_SyntaxElem += 2;
	rate_LcuSizeMax += 1;
	rate_PicSize += 2;
	rate_Poc += 1;
	rate_SliceType += 1;
	rate_TilesCoord += 1;
}
static i32 isSchedulable_getPartMode() {
	i32 result;
	u8 partMode;
	u8 local_PART_MODE_SLICE_DEP;
	u8 local_PART_MODE_SLICE_INDEP;
	u8 local_PART_MODE_PICT;

	partMode = tokens_PartMode[(index_PartMode + (0)) % SIZE_PartMode];
	local_PART_MODE_SLICE_DEP = HevcDecoder_generateInfo_MvComponentPred_PART_MODE_SLICE_DEP;
	local_PART_MODE_SLICE_INDEP = HevcDecoder_generateInfo_MvComponentPred_PART_MODE_SLICE_INDEP;
	local_PART_MODE_PICT = HevcDecoder_generateInfo_MvComponentPred_PART_MODE_PICT;
	result = partMode != local_PART_MODE_SLICE_DEP && partMode != local_PART_MODE_SLICE_INDEP && partMode != local_PART_MODE_PICT;
	return result;
}

static void getPartMode() {

	u8 partMode;
	u8 tmp_partModeToNumPart;
	i32 local_DEBUG_PartMode;

	partMode = tokens_PartMode[(index_PartMode + (0)) % SIZE_PartMode];
	tmp_partModeToNumPart = HevcDecoder_generateInfo_MvComponentPred_partModeToNumPart[partMode];
	numPart = tmp_partModeToNumPart;
	numPartDecoded = 0;
	cuPartMode = partMode;
	local_DEBUG_PartMode = DEBUG_PartMode;
	if (local_DEBUG_PartMode) {
		printf("partMode = %u\n", partMode);
	}

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
	result = local_numPartDecoded < local_numPart;
	return result;
}

static void getCuInfo_launch() {

	u16 tmp_CUInfo;
	u16 tmp_CUInfo0;
	u16 tmp_CUInfo1;
	i32 tmp_max;
	u16 tmp_CUInfo2;
	u16 tmp_CUInfo3;
	u16 tmp_CUInfo4;
	u16 tmp_CUInfo5;
	u16 tmp_CUInfo6;
	u16 tmp_CUInfo7;
	u16 tmp_CUInfo8;
	u16 tmp_CUInfo9;
	u16 tmp_CUInfo10;
	u16 tmp_CUInfo11;
	u16 tmp_CUInfo12;
	u16 tmp_CUInfo13;
	i32 local_PICT_WIDTH_POW_2;
	u16 tmp_CUInfo14;
	u16 tmp_CUInfo15;
	u16 tmp_absCoordInBlkToZScan;
	u8 local_numPartDecoded;
	i32 idx_partAddr;
	i32 local_partAddr;
	i32 idx_puAbsAddrInLcu;
	u16 local_puAbsAddrInLcu;
	i32 local_DEBUG_CUInfo;
	u16 tmp_CUInfo16;
	u16 tmp_CUInfo17;
	u16 tmp_CUInfo18;
	u16 tmp_CUInfo19;
	u16 tmp_CUInfo20;

	tmp_CUInfo = tokens_CUInfo[(index_CUInfo + (0)) % SIZE_CUInfo];
	cuMode = tmp_CUInfo;
	tmp_CUInfo0 = tokens_CUInfo[(index_CUInfo + (3)) % SIZE_CUInfo];
	tmp_CUInfo1 = tokens_CUInfo[(index_CUInfo + (4)) % SIZE_CUInfo];
	tmp_max = HevcDecoder_generateInfo_MvComponentPred_max(tmp_CUInfo0, tmp_CUInfo1);
	predCuSize = tmp_max;
	tmp_CUInfo2 = tokens_CUInfo[(index_CUInfo + (3)) % SIZE_CUInfo];
	puSize[0] = tmp_CUInfo2;
	tmp_CUInfo3 = tokens_CUInfo[(index_CUInfo + (4)) % SIZE_CUInfo];
	puSize[1] = tmp_CUInfo3;
	tmp_CUInfo4 = tokens_CUInfo[(index_CUInfo + (3)) % SIZE_CUInfo];
	cuSize[0] = tmp_CUInfo4;
	tmp_CUInfo5 = tokens_CUInfo[(index_CUInfo + (4)) % SIZE_CUInfo];
	cuSize[1] = tmp_CUInfo5;
	tmp_CUInfo6 = tokens_CUInfo[(index_CUInfo + (1)) % SIZE_CUInfo];
	partAddr[0] = tmp_CUInfo6 / 4;
	tmp_CUInfo7 = tokens_CUInfo[(index_CUInfo + (2)) % SIZE_CUInfo];
	partAddr[1] = tmp_CUInfo7 / 4;
	tmp_CUInfo8 = tokens_CUInfo[(index_CUInfo + (1)) % SIZE_CUInfo];
	cuAddr[0] = tmp_CUInfo8;
	tmp_CUInfo9 = tokens_CUInfo[(index_CUInfo + (2)) % SIZE_CUInfo];
	cuAddr[1] = tmp_CUInfo9;
	tmp_CUInfo10 = tokens_CUInfo[(index_CUInfo + (3)) % SIZE_CUInfo];
	nPSW = tmp_CUInfo10 / 4;
	tmp_CUInfo11 = tokens_CUInfo[(index_CUInfo + (4)) % SIZE_CUInfo];
	nPSH = tmp_CUInfo11 / 4;
	tmp_CUInfo12 = tokens_CUInfo[(index_CUInfo + (1)) % SIZE_CUInfo];
	tmp_CUInfo13 = tokens_CUInfo[(index_CUInfo + (2)) % SIZE_CUInfo];
	local_PICT_WIDTH_POW_2 = HevcDecoder_generateInfo_MvComponentPred_PICT_WIDTH_POW_2;
	lcuAddr = tmp_CUInfo12 / 64 + tmp_CUInfo13 / 64 * (local_PICT_WIDTH_POW_2 / 64);
	tmp_CUInfo14 = tokens_CUInfo[(index_CUInfo + (1)) % SIZE_CUInfo];
	puAbsAddrInLcu[0] = (tmp_CUInfo14 & 63) / 4;
	tmp_CUInfo15 = tokens_CUInfo[(index_CUInfo + (2)) % SIZE_CUInfo];
	puAbsAddrInLcu[1] = (tmp_CUInfo15 & 63) / 4;
	tmp_absCoordInBlkToZScan = HevcDecoder_generateInfo_MvComponentPred_absCoordInBlkToZScan(puAbsAddrInLcu);
	puAddrInLcu = tmp_absCoordInBlkToZScan;
	local_numPartDecoded = numPartDecoded;
	if (local_numPartDecoded == 0) {
		idx_partAddr = 0;
		while (idx_partAddr < 2) {
			local_partAddr = partAddr[idx_partAddr];
			partAddr1stPu[idx_partAddr] = local_partAddr;
			idx_partAddr = idx_partAddr + 1;
		}
		idx_puAbsAddrInLcu = 0;
		while (idx_puAbsAddrInLcu < 2) {
			local_puAbsAddrInLcu = puAbsAddrInLcu[idx_puAbsAddrInLcu];
			puAbsAddrInLcu1stPu[idx_puAbsAddrInLcu] = local_puAbsAddrInLcu;
			idx_puAbsAddrInLcu = idx_puAbsAddrInLcu + 1;
		}
	}
	local_numPartDecoded = numPartDecoded;
	numPartDecoded = local_numPartDecoded + 1;
	local_DEBUG_CUInfo = DEBUG_CUInfo;
	if (local_DEBUG_CUInfo) {
		tmp_CUInfo16 = tokens_CUInfo[(index_CUInfo + (0)) % SIZE_CUInfo];
		tmp_CUInfo17 = tokens_CUInfo[(index_CUInfo + (1)) % SIZE_CUInfo];
		tmp_CUInfo18 = tokens_CUInfo[(index_CUInfo + (2)) % SIZE_CUInfo];
		tmp_CUInfo19 = tokens_CUInfo[(index_CUInfo + (3)) % SIZE_CUInfo];
		tmp_CUInfo20 = tokens_CUInfo[(index_CUInfo + (4)) % SIZE_CUInfo];
		printf("CUInfo = %u %u %u %u %u\n", tmp_CUInfo16, tmp_CUInfo17, tmp_CUInfo18, tmp_CUInfo19, tmp_CUInfo20);
	}

	// Update ports indexes
	index_CUInfo += 5;
	read_end_CUInfo();

	rate_CUInfo += 5;
}
static void getCuInfo_launch_aligned() {

	u16 tmp_CUInfo;
	u16 tmp_CUInfo0;
	u16 tmp_CUInfo1;
	i32 tmp_max;
	u16 tmp_CUInfo2;
	u16 tmp_CUInfo3;
	u16 tmp_CUInfo4;
	u16 tmp_CUInfo5;
	u16 tmp_CUInfo6;
	u16 tmp_CUInfo7;
	u16 tmp_CUInfo8;
	u16 tmp_CUInfo9;
	u16 tmp_CUInfo10;
	u16 tmp_CUInfo11;
	u16 tmp_CUInfo12;
	u16 tmp_CUInfo13;
	i32 local_PICT_WIDTH_POW_2;
	u16 tmp_CUInfo14;
	u16 tmp_CUInfo15;
	u16 tmp_absCoordInBlkToZScan;
	u8 local_numPartDecoded;
	i32 idx_partAddr;
	i32 local_partAddr;
	i32 idx_puAbsAddrInLcu;
	u16 local_puAbsAddrInLcu;
	i32 local_DEBUG_CUInfo;
	u16 tmp_CUInfo16;
	u16 tmp_CUInfo17;
	u16 tmp_CUInfo18;
	u16 tmp_CUInfo19;
	u16 tmp_CUInfo20;

	tmp_CUInfo = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (0)];
	cuMode = tmp_CUInfo;
	tmp_CUInfo0 = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (3)];
	tmp_CUInfo1 = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (4)];
	tmp_max = HevcDecoder_generateInfo_MvComponentPred_max(tmp_CUInfo0, tmp_CUInfo1);
	predCuSize = tmp_max;
	tmp_CUInfo2 = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (3)];
	puSize[0] = tmp_CUInfo2;
	tmp_CUInfo3 = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (4)];
	puSize[1] = tmp_CUInfo3;
	tmp_CUInfo4 = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (3)];
	cuSize[0] = tmp_CUInfo4;
	tmp_CUInfo5 = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (4)];
	cuSize[1] = tmp_CUInfo5;
	tmp_CUInfo6 = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (1)];
	partAddr[0] = tmp_CUInfo6 / 4;
	tmp_CUInfo7 = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (2)];
	partAddr[1] = tmp_CUInfo7 / 4;
	tmp_CUInfo8 = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (1)];
	cuAddr[0] = tmp_CUInfo8;
	tmp_CUInfo9 = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (2)];
	cuAddr[1] = tmp_CUInfo9;
	tmp_CUInfo10 = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (3)];
	nPSW = tmp_CUInfo10 / 4;
	tmp_CUInfo11 = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (4)];
	nPSH = tmp_CUInfo11 / 4;
	tmp_CUInfo12 = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (1)];
	tmp_CUInfo13 = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (2)];
	local_PICT_WIDTH_POW_2 = HevcDecoder_generateInfo_MvComponentPred_PICT_WIDTH_POW_2;
	lcuAddr = tmp_CUInfo12 / 64 + tmp_CUInfo13 / 64 * (local_PICT_WIDTH_POW_2 / 64);
	tmp_CUInfo14 = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (1)];
	puAbsAddrInLcu[0] = (tmp_CUInfo14 & 63) / 4;
	tmp_CUInfo15 = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (2)];
	puAbsAddrInLcu[1] = (tmp_CUInfo15 & 63) / 4;
	tmp_absCoordInBlkToZScan = HevcDecoder_generateInfo_MvComponentPred_absCoordInBlkToZScan(puAbsAddrInLcu);
	puAddrInLcu = tmp_absCoordInBlkToZScan;
	local_numPartDecoded = numPartDecoded;
	if (local_numPartDecoded == 0) {
		idx_partAddr = 0;
		while (idx_partAddr < 2) {
			local_partAddr = partAddr[idx_partAddr];
			partAddr1stPu[idx_partAddr] = local_partAddr;
			idx_partAddr = idx_partAddr + 1;
		}
		idx_puAbsAddrInLcu = 0;
		while (idx_puAbsAddrInLcu < 2) {
			local_puAbsAddrInLcu = puAbsAddrInLcu[idx_puAbsAddrInLcu];
			puAbsAddrInLcu1stPu[idx_puAbsAddrInLcu] = local_puAbsAddrInLcu;
			idx_puAbsAddrInLcu = idx_puAbsAddrInLcu + 1;
		}
	}
	local_numPartDecoded = numPartDecoded;
	numPartDecoded = local_numPartDecoded + 1;
	local_DEBUG_CUInfo = DEBUG_CUInfo;
	if (local_DEBUG_CUInfo) {
		tmp_CUInfo16 = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (0)];
		tmp_CUInfo17 = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (1)];
		tmp_CUInfo18 = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (2)];
		tmp_CUInfo19 = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (3)];
		tmp_CUInfo20 = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (4)];
		printf("CUInfo = %u %u %u %u %u\n", tmp_CUInfo16, tmp_CUInfo17, tmp_CUInfo18, tmp_CUInfo19, tmp_CUInfo20);
	}

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
	local_INTER = HevcDecoder_generateInfo_MvComponentPred_INTER;
	local_cuMode = cuMode;
	local_SKIP = HevcDecoder_generateInfo_MvComponentPred_SKIP;
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
	local_INTER = HevcDecoder_generateInfo_MvComponentPred_INTER;
	local_cuMode = cuMode;
	local_SKIP = HevcDecoder_generateInfo_MvComponentPred_SKIP;
	result = local_cuMode == local_INTER || local_cuMode == local_SKIP;
	return result;
}

static void getCuMode_isInter() {

	i16 mergeIndex;
	i32 tileIdx;
	u16 local_numTiles;
	i32 tmp_partAddr;
	u16 tmp_tilesBeg;
	i32 tmp_partAddr0;
	u16 tmp_tilesEnd;
	i32 tmp_partAddr1;
	u16 tmp_tilesBeg0;
	i32 tmp_partAddr2;
	u16 tmp_tilesEnd0;
	u16 tmp_tilesBeg1;
	u16 tmp_tilesBeg2;
	u16 tmp_tilesEnd1;
	u16 tmp_tilesEnd2;
	i32 local_DEBUG_SyntaxElem;
	i32 local_mergeIdx;

	mergeIndex = tokens_SyntaxElem[(index_SyntaxElem + (0)) % SIZE_SyntaxElem];
	tileIdx = 0;
	local_numTiles = numTiles;
	while (tileIdx <= local_numTiles - 1) {
		tmp_partAddr = partAddr[0];
		tmp_tilesBeg = tilesBeg[tileIdx][0];
		tmp_partAddr0 = partAddr[0];
		tmp_tilesEnd = tilesEnd[tileIdx][0];
		tmp_partAddr1 = partAddr[1];
		tmp_tilesBeg0 = tilesBeg[tileIdx][1];
		tmp_partAddr2 = partAddr[1];
		tmp_tilesEnd0 = tilesEnd[tileIdx][1];
		if (tmp_partAddr >= tmp_tilesBeg && tmp_partAddr0 < tmp_tilesEnd && tmp_partAddr1 >= tmp_tilesBeg0 && tmp_partAddr2 < tmp_tilesEnd0) {
			tmp_tilesBeg1 = tilesBeg[tileIdx][0];
			puTilesBeg[0] = tmp_tilesBeg1;
			tmp_tilesBeg2 = tilesBeg[tileIdx][1];
			puTilesBeg[1] = tmp_tilesBeg2;
			tmp_tilesEnd1 = tilesEnd[tileIdx][0];
			puTilesEnd[0] = tmp_tilesEnd1;
			tmp_tilesEnd2 = tilesEnd[tileIdx][1];
			puTilesEnd[1] = tmp_tilesEnd2;
		}
		tileIdx = tileIdx + 1;
	}
	mergeIdx = mergeIndex;
	local_DEBUG_SyntaxElem = DEBUG_SyntaxElem;
	if (local_DEBUG_SyntaxElem) {
		local_mergeIdx = mergeIdx;
		printf("mergeIdx = %i\n", local_mergeIdx);
	}

	// Update ports indexes
	index_SyntaxElem += 1;

	rate_SyntaxElem += 1;
}
static i32 isSchedulable_checkMergeIdx_isNotEqToMin1() {
	i32 result;
	i32 local_mergeIdx;

	local_mergeIdx = mergeIdx;
	result = local_mergeIdx != -1;
	return result;
}

static void checkMergeIdx_isNotEqToMin1() {

	i32 numNeighbSelect;
	i32 tryGetNeighbour;
	i32 locationUp[2];
	i32 locationLeft[2];
	i32 locationUpBis[2];
	i32 locationLeftBis[2];
	i32 refIdxVal;
	u8 local_numPartDecoded;
	i32 partIdx;
	i32 isAvailableA1;
	i32 isAvailableB1;
	i32 local_nPSH;
	u8 nPSHInit;
	i32 local_nPSW;
	u8 nPSWInit;
	u8 local_cuPartMode;
	u8 cuPartModeInit;
	i32 idx_partAddr;
	i32 local_partAddr;
	i32 partAddrInit[2];
	i8 local_paralMergeLvl;
	u8 local_PART_2Nx2N;
	u8 local_predCuSize;
	i32 tmp_max;
	i32 idx_partAddr1stPu;
	i32 local_partAddr1stPu;
	i32 idx_puAbsAddrInLcu1stPu;
	u16 local_puAbsAddrInLcu1stPu;
	i32 local_ABOVE;
	i32 local_dependSlc;
	i32 idx_neighbLocation;
	i32 local_neighbLocation;
	i32 idx_neighbLocIdx;
	i32 local_neighbLocIdx;
	i32 local_LEFT;
	i32 idx_neighbLocation0;
	i32 local_neighbLocation0;
	i32 idx_neighbLocIdx0;
	i32 local_neighbLocIdx0;
	u8 local_PART_Nx2N;
	u8 local_PART_nLx2N;
	u8 local_PART_nRx2N;
	i32 tmp_getIsAvailable;
	i32 tmp_locationLeft;
	i32 tmp_partAddr;
	i32 tmp_locationLeft0;
	i32 tmp_partAddr0;
	i32 local_predFlag;
	i32 local_numCandidate;
	i32 local_mergeIdx;
	u8 local_PART_2NxN;
	u8 local_PART_2NxnU;
	u8 local_PART_2NxnD;
	i32 tmp_hasNotSameMvComp;
	i32 idx_locationUp;
	i32 local_locationUp;
	i32 idx_locationUpBis;
	i32 local_locationUpBis;
	i32 tmp_getIsAvailable0;
	i32 tmp_locationUp;
	i32 tmp_partAddr1;
	i32 tmp_locationUp0;
	i32 tmp_partAddr2;
	i32 tmp_castBoolToInt;
	i32 local_ABOVE_RIGHT;
	i32 tmp_hasNotSameMvComp0;
	i32 tmp_castBoolToInt0;
	i32 local_LEFT_BOTTOM;
	i32 tmp_hasNotSameMvComp1;
	i32 tmp_castBoolToInt1;
	i32 local_ABOVE_LEFT;
	i32 tmp_hasNotSameMvComp2;
	i32 tmp_hasNotSameMvComp3;
	i32 local_enTmpMvp;
	i32 local_isBSlice;
	i32 i;
	u8 local_minSizeRefListX;
	i32 idx_partAddrInit;
	i32 local_partAddrInit;

	numNeighbSelect = 0;
	refIdxVal = 0;
	local_numPartDecoded = numPartDecoded;
	partIdx = local_numPartDecoded - 1;
	isAvailableA1 = 0;
	isAvailableB1 = 0;
	local_nPSH = nPSH;
	nPSHInit = local_nPSH;
	local_nPSW = nPSW;
	nPSWInit = local_nPSW;
	local_cuPartMode = cuPartMode;
	cuPartModeInit = local_cuPartMode;
	idx_partAddr = 0;
	while (idx_partAddr < 2) {
		local_partAddr = partAddr[idx_partAddr];
		partAddrInit[idx_partAddr] = local_partAddr;
		idx_partAddr = idx_partAddr + 1;
	}
	local_paralMergeLvl = paralMergeLvl;
	local_cuPartMode = cuPartMode;
	local_PART_2Nx2N = HevcDecoder_generateInfo_MvComponentPred_PART_2Nx2N;
	local_predCuSize = predCuSize;
	if (local_paralMergeLvl > 0 && local_cuPartMode != local_PART_2Nx2N && local_predCuSize <= 8) {
		local_nPSW = nPSW;
		local_nPSH = nPSH;
		tmp_max = HevcDecoder_generateInfo_MvComponentPred_max(local_nPSW, local_nPSH);
		nPSW = tmp_max;
		local_nPSW = nPSW;
		nPSH = local_nPSW;
		local_PART_2Nx2N = HevcDecoder_generateInfo_MvComponentPred_PART_2Nx2N;
		cuPartMode = local_PART_2Nx2N;
		idx_partAddr1stPu = 0;
		while (idx_partAddr1stPu < 2) {
			local_partAddr1stPu = partAddr1stPu[idx_partAddr1stPu];
			partAddr[idx_partAddr1stPu] = local_partAddr1stPu;
			idx_partAddr1stPu = idx_partAddr1stPu + 1;
		}
		idx_puAbsAddrInLcu1stPu = 0;
		while (idx_puAbsAddrInLcu1stPu < 2) {
			local_puAbsAddrInLcu1stPu = puAbsAddrInLcu1stPu[idx_puAbsAddrInLcu1stPu];
			puAbsAddrInLcu[idx_puAbsAddrInLcu1stPu] = local_puAbsAddrInLcu1stPu;
			idx_puAbsAddrInLcu1stPu = idx_puAbsAddrInLcu1stPu + 1;
		}
	}
	numCandidate = 0;
	local_ABOVE = ABOVE;
	local_dependSlc = dependSlc;
	getNeighbAddr(local_ABOVE, local_dependSlc, 0);
	idx_neighbLocation = 0;
	while (idx_neighbLocation < 2) {
		local_neighbLocation = neighbLocation[idx_neighbLocation];
		locationUp[idx_neighbLocation] = local_neighbLocation;
		idx_neighbLocation = idx_neighbLocation + 1;
	}
	idx_neighbLocIdx = 0;
	while (idx_neighbLocIdx < 2) {
		local_neighbLocIdx = neighbLocIdx[idx_neighbLocIdx];
		locationUpBis[idx_neighbLocIdx] = local_neighbLocIdx;
		idx_neighbLocIdx = idx_neighbLocIdx + 1;
	}
	local_LEFT = LEFT;
	local_dependSlc = dependSlc;
	getNeighbAddr(local_LEFT, local_dependSlc, 0);
	idx_neighbLocation0 = 0;
	while (idx_neighbLocation0 < 2) {
		local_neighbLocation0 = neighbLocation[idx_neighbLocation0];
		locationLeft[idx_neighbLocation0] = local_neighbLocation0;
		idx_neighbLocation0 = idx_neighbLocation0 + 1;
	}
	idx_neighbLocIdx0 = 0;
	while (idx_neighbLocIdx0 < 2) {
		local_neighbLocIdx0 = neighbLocIdx[idx_neighbLocIdx0];
		locationLeftBis[idx_neighbLocIdx0] = local_neighbLocIdx0;
		idx_neighbLocIdx0 = idx_neighbLocIdx0 + 1;
	}
	local_cuPartMode = cuPartMode;
	local_PART_Nx2N = HevcDecoder_generateInfo_MvComponentPred_PART_Nx2N;
	local_cuPartMode = cuPartMode;
	local_PART_nLx2N = HevcDecoder_generateInfo_MvComponentPred_PART_nLx2N;
	local_cuPartMode = cuPartMode;
	local_PART_nRx2N = HevcDecoder_generateInfo_MvComponentPred_PART_nRx2N;
	if (!(local_cuPartMode == local_PART_Nx2N || local_cuPartMode == local_PART_nLx2N || local_cuPartMode == local_PART_nRx2N) || partIdx != 1) {
		tmp_getIsAvailable = getIsAvailable();
		tmp_locationLeft = locationLeft[0];
		local_paralMergeLvl = paralMergeLvl;
		tmp_partAddr = partAddr[0];
		local_paralMergeLvl = paralMergeLvl;
		tmp_locationLeft0 = locationLeft[1];
		local_paralMergeLvl = paralMergeLvl;
		tmp_partAddr0 = partAddr[1];
		local_paralMergeLvl = paralMergeLvl;
		isAvailableA1 = tmp_getIsAvailable && (tmp_locationLeft >> local_paralMergeLvl != tmp_partAddr >> local_paralMergeLvl || tmp_locationLeft0 >> local_paralMergeLvl != tmp_partAddr0 >> local_paralMergeLvl);
		getNeighbourMv_MergeIdx_isNotEqToMin1();
		local_predFlag = predFlag;
		numNeighbSelect = HevcDecoder_generateInfo_MvComponentPred_castBoolToInt(local_predFlag);
	}
	local_numCandidate = numCandidate;
	local_mergeIdx = mergeIdx;
	if (local_numCandidate <= local_mergeIdx) {
		local_cuPartMode = cuPartMode;
		local_PART_2NxN = HevcDecoder_generateInfo_MvComponentPred_PART_2NxN;
		local_cuPartMode = cuPartMode;
		local_PART_2NxnU = HevcDecoder_generateInfo_MvComponentPred_PART_2NxnU;
		local_cuPartMode = cuPartMode;
		local_PART_2NxnD = HevcDecoder_generateInfo_MvComponentPred_PART_2NxnD;
		if (!(local_cuPartMode == local_PART_2NxN || local_cuPartMode == local_PART_2NxnU || local_cuPartMode == local_PART_2NxnD) || partIdx != 1) {
			tmp_hasNotSameMvComp = hasNotSameMvComp(locationUpBis, locationLeftBis);
			tryGetNeighbour = !isAvailableA1 || tmp_hasNotSameMvComp;
			idx_locationUp = 0;
			while (idx_locationUp < 2) {
				local_locationUp = locationUp[idx_locationUp];
				neighbLocation[idx_locationUp] = local_locationUp;
				idx_locationUp = idx_locationUp + 1;
			}
			idx_locationUpBis = 0;
			while (idx_locationUpBis < 2) {
				local_locationUpBis = locationUpBis[idx_locationUpBis];
				neighbLocIdx[idx_locationUpBis] = local_locationUpBis;
				idx_locationUpBis = idx_locationUpBis + 1;
			}
			tmp_getIsAvailable0 = getIsAvailable();
			tmp_locationUp = locationUp[0];
			local_paralMergeLvl = paralMergeLvl;
			tmp_partAddr1 = partAddr[0];
			local_paralMergeLvl = paralMergeLvl;
			tmp_locationUp0 = locationUp[1];
			local_paralMergeLvl = paralMergeLvl;
			tmp_partAddr2 = partAddr[1];
			local_paralMergeLvl = paralMergeLvl;
			isAvailableB1 = tmp_getIsAvailable0 && (tmp_locationUp >> local_paralMergeLvl != tmp_partAddr1 >> local_paralMergeLvl || tmp_locationUp0 >> local_paralMergeLvl != tmp_partAddr2 >> local_paralMergeLvl);
			if (tryGetNeighbour) {
				getNeighbourMv_MergeIdx_isNotEqToMin1();
				local_predFlag = predFlag;
				tmp_castBoolToInt = HevcDecoder_generateInfo_MvComponentPred_castBoolToInt(local_predFlag);
				numNeighbSelect = numNeighbSelect + tmp_castBoolToInt;
			}
		}
		local_numCandidate = numCandidate;
		local_mergeIdx = mergeIdx;
		if (local_numCandidate <= local_mergeIdx) {
			local_ABOVE_RIGHT = ABOVE_RIGHT;
			local_dependSlc = dependSlc;
			getNeighbAddr(local_ABOVE_RIGHT, local_dependSlc, 0);
			tmp_hasNotSameMvComp0 = hasNotSameMvComp(neighbLocIdx, locationUpBis);
			tryGetNeighbour = !isAvailableB1 || tmp_hasNotSameMvComp0;
			if (tryGetNeighbour) {
				getNeighbourMv_MergeIdx_isNotEqToMin1();
				local_predFlag = predFlag;
				tmp_castBoolToInt0 = HevcDecoder_generateInfo_MvComponentPred_castBoolToInt(local_predFlag);
				numNeighbSelect = numNeighbSelect + tmp_castBoolToInt0;
			}
			local_numCandidate = numCandidate;
			local_mergeIdx = mergeIdx;
			if (local_numCandidate <= local_mergeIdx) {
				local_LEFT_BOTTOM = LEFT_BOTTOM;
				local_dependSlc = dependSlc;
				getNeighbAddr(local_LEFT_BOTTOM, local_dependSlc, 0);
				tmp_hasNotSameMvComp1 = hasNotSameMvComp(neighbLocIdx, locationLeftBis);
				tryGetNeighbour = !isAvailableA1 || tmp_hasNotSameMvComp1;
				if (tryGetNeighbour) {
					getNeighbourMv_MergeIdx_isNotEqToMin1();
					local_predFlag = predFlag;
					tmp_castBoolToInt1 = HevcDecoder_generateInfo_MvComponentPred_castBoolToInt(local_predFlag);
					numNeighbSelect = numNeighbSelect + tmp_castBoolToInt1;
				}
				local_numCandidate = numCandidate;
				local_mergeIdx = mergeIdx;
				if (local_numCandidate <= local_mergeIdx) {
					if (numNeighbSelect < 4) {
						local_ABOVE_LEFT = ABOVE_LEFT;
						local_dependSlc = dependSlc;
						getNeighbAddr(local_ABOVE_LEFT, local_dependSlc, 0);
						tmp_hasNotSameMvComp2 = hasNotSameMvComp(neighbLocIdx, locationUpBis);
						tryGetNeighbour = !isAvailableB1 || tmp_hasNotSameMvComp2;
						tmp_hasNotSameMvComp3 = hasNotSameMvComp(neighbLocIdx, locationLeftBis);
						tryGetNeighbour = tryGetNeighbour && (!isAvailableA1 || tmp_hasNotSameMvComp3);
						if (tryGetNeighbour) {
							getNeighbourMv_MergeIdx_isNotEqToMin1();
						}
					}
					local_numCandidate = numCandidate;
					local_mergeIdx = mergeIdx;
					if (local_numCandidate <= local_mergeIdx) {
						local_enTmpMvp = enTmpMvp;
						if (local_enTmpMvp) {
							getColCandidate(1, 0);
						}
						local_numCandidate = numCandidate;
						local_mergeIdx = mergeIdx;
						if (local_numCandidate <= local_mergeIdx) {
							local_isBSlice = isBSlice;
							if (local_isBSlice) {
								biPredMergeCand(5);
							}
							local_numCandidate = numCandidate;
							local_mergeIdx = mergeIdx;
							if (local_numCandidate <= local_mergeIdx) {
								local_numCandidate = numCandidate;
								i = local_numCandidate;
								while (i <= 4) {
									mvPred[i][0][0] = 0;
									mvPred[i][0][1] = 0;
									mvPred[i][1][0] = 0;
									mvPred[i][1][1] = 0;
									refIdxPred[i][0] = refIdxVal;
									refIdxPred[i][1] = refIdxVal;
									local_minSizeRefListX = minSizeRefListX;
									if (refIdxVal == local_minSizeRefListX - 1) {
										refIdxVal = 0;
									} else {
										refIdxVal = refIdxVal + 1;
									}
									i = i + 1;
								}
							}
						}
					}
				}
			}
		}
	}
	nPSH = nPSHInit;
	nPSW = nPSWInit;
	cuPartMode = cuPartModeInit;
	idx_partAddrInit = 0;
	while (idx_partAddrInit < 2) {
		local_partAddrInit = partAddrInit[idx_partAddrInit];
		partAddr[idx_partAddrInit] = local_partAddrInit;
		idx_partAddrInit = idx_partAddrInit + 1;
	}

	// Update ports indexes

}
static i32 isSchedulable_checkMergeIdx_isEqToMin1() {
	i32 result;
	i32 local_mergeIdx;

	local_mergeIdx = mergeIdx;
	result = local_mergeIdx == -1;
	return result;
}

static void checkMergeIdx_isEqToMin1() {

	i16 tmp_SyntaxElem;
	i16 tmp_SyntaxElem0;
	i32 refIdx[2];
	i32 numNeighbSelect;
	i32 neighbIdxLB[2];
	i32 neighbIdxL[2];
	i32 local_DEBUG_SyntaxElem;
	i16 tmp_SyntaxElem1;
	i16 tmp_SyntaxElem2;
	i16 tmp_SyntaxElem3;
	i16 tmp_SyntaxElem4;
	u8 local_cuPartMode;
	u8 local_numPartDecoded;
	i8 local_currIdx;
	u16 local_lcuAddr;
	u16 local_puAddrInLcu;
	i16 tmp_SyntaxElem5;
	i16 tmp_SyntaxElem6;
	i32 list;
	i32 local_LEFT_BOTTOM;
	i32 local_dependSlc;
	i32 idx_neighbLocIdx;
	i32 local_neighbLocIdx;
	i32 local_LEFT;
	i32 idx_neighbLocIdx0;
	i32 local_neighbLocIdx0;
	i32 local_predFlag;
	i32 local_numCandidate;
	i32 tmp_mvpIdx;
	i32 local_ABOVE_RIGHT;
	i32 local_ABOVE;
	i32 local_ABOVE_LEFT;
	i32 tmp_castBoolToInt;
	i32 tmp_mvpIdx0;
	i32 tmp_partAddr;
	i32 tmp_partAddr0;
	i32 local_nPSH;
	i32 tmp_neighbIdxLB;
	i32 tmp_neighbIdxLB0;
	i32 tmp_isInter;
	i32 tmp_partAddr1;
	i32 tmp_partAddr2;
	i32 tmp_neighbIdxL;
	i32 tmp_neighbIdxL0;
	i32 tmp_isInter0;
	i32 tmp_mvpIdx1;
	i32 local_enTmpMvp;
	i32 tmp_mvpIdx2;
	i32 i;

	tmp_SyntaxElem = tokens_SyntaxElem[(index_SyntaxElem + (2)) % SIZE_SyntaxElem];
	refIdx[0] = tmp_SyntaxElem;
	tmp_SyntaxElem0 = tokens_SyntaxElem[(index_SyntaxElem + (3)) % SIZE_SyntaxElem];
	refIdx[1] = tmp_SyntaxElem0;
	local_DEBUG_SyntaxElem = DEBUG_SyntaxElem;
	if (local_DEBUG_SyntaxElem) {
		tmp_SyntaxElem1 = tokens_SyntaxElem[(index_SyntaxElem + (0)) % SIZE_SyntaxElem];
		tmp_SyntaxElem2 = tokens_SyntaxElem[(index_SyntaxElem + (1)) % SIZE_SyntaxElem];
		printf("mvp_l0 = %i : mvp_l1 = %i\n", tmp_SyntaxElem1, tmp_SyntaxElem2);
		tmp_SyntaxElem3 = tokens_SyntaxElem[(index_SyntaxElem + (2)) % SIZE_SyntaxElem];
		tmp_SyntaxElem4 = tokens_SyntaxElem[(index_SyntaxElem + (3)) % SIZE_SyntaxElem];
		printf("refIdx_l0 = %i : refIdx_l1 = %i\n", tmp_SyntaxElem3, tmp_SyntaxElem4);
	}
	local_cuPartMode = cuPartMode;
	local_numPartDecoded = numPartDecoded;
	local_currIdx = currIdx;
	local_lcuAddr = lcuAddr;
	local_puAddrInLcu = puAddrInLcu;
	saveRefIdx(refIdx, cuSize, local_cuPartMode, local_numPartDecoded, refIdxRef, local_currIdx, local_lcuAddr, local_puAddrInLcu);
	tmp_SyntaxElem5 = tokens_SyntaxElem[(index_SyntaxElem + (0)) % SIZE_SyntaxElem];
	mvpIdx[0] = tmp_SyntaxElem5;
	tmp_SyntaxElem6 = tokens_SyntaxElem[(index_SyntaxElem + (1)) % SIZE_SyntaxElem];
	mvpIdx[1] = tmp_SyntaxElem6;
	list = 0;
	while (list <= 1) {
		numCandidate = 0;
		local_LEFT_BOTTOM = LEFT_BOTTOM;
		local_dependSlc = dependSlc;
		getNeighbAddr(local_LEFT_BOTTOM, local_dependSlc, 0);
		idx_neighbLocIdx = 0;
		while (idx_neighbLocIdx < 2) {
			local_neighbLocIdx = neighbLocIdx[idx_neighbLocIdx];
			neighbIdxLB[idx_neighbLocIdx] = local_neighbLocIdx;
			idx_neighbLocIdx = idx_neighbLocIdx + 1;
		}
		getNonMergedNeighbourMv(list);
		local_LEFT = LEFT;
		local_dependSlc = dependSlc;
		getNeighbAddr(local_LEFT, local_dependSlc, 0);
		idx_neighbLocIdx0 = 0;
		while (idx_neighbLocIdx0 < 2) {
			local_neighbLocIdx0 = neighbLocIdx[idx_neighbLocIdx0];
			neighbIdxL[idx_neighbLocIdx0] = local_neighbLocIdx0;
			idx_neighbLocIdx0 = idx_neighbLocIdx0 + 1;
		}
		local_predFlag = predFlag;
		if (!local_predFlag) {
			getNonMergedNeighbourMv(list);
		}
		local_predFlag = predFlag;
		if (!local_predFlag) {
			local_LEFT_BOTTOM = LEFT_BOTTOM;
			local_dependSlc = dependSlc;
			getNeighbAddr(local_LEFT_BOTTOM, local_dependSlc, 0);
			getNonMergedScaledMv(list);
		}
		local_predFlag = predFlag;
		if (!local_predFlag) {
			local_LEFT = LEFT;
			local_dependSlc = dependSlc;
			getNeighbAddr(local_LEFT, local_dependSlc, 0);
			getNonMergedScaledMv(list);
		}
		local_predFlag = predFlag;
		numNeighbSelect = HevcDecoder_generateInfo_MvComponentPred_castBoolToInt(local_predFlag);
		local_numCandidate = numCandidate;
		tmp_mvpIdx = mvpIdx[list];
		if (local_numCandidate <= tmp_mvpIdx) {
			local_ABOVE_RIGHT = ABOVE_RIGHT;
			local_dependSlc = dependSlc;
			getNeighbAddr(local_ABOVE_RIGHT, local_dependSlc, 0);
			getNonMergedNeighbourMv(list);
			local_predFlag = predFlag;
			if (!local_predFlag) {
				local_ABOVE = ABOVE;
				local_dependSlc = dependSlc;
				getNeighbAddr(local_ABOVE, local_dependSlc, 0);
				getNonMergedNeighbourMv(list);
			}
			local_predFlag = predFlag;
			if (!local_predFlag) {
				local_ABOVE_LEFT = ABOVE_LEFT;
				local_dependSlc = dependSlc;
				getNeighbAddr(local_ABOVE_LEFT, local_dependSlc, 0);
				getNonMergedNeighbourMv(list);
			}
			local_predFlag = predFlag;
			tmp_castBoolToInt = HevcDecoder_generateInfo_MvComponentPred_castBoolToInt(local_predFlag);
			numNeighbSelect = numNeighbSelect + tmp_castBoolToInt;
			local_numCandidate = numCandidate;
			tmp_mvpIdx0 = mvpIdx[list];
			if (local_numCandidate <= tmp_mvpIdx0) {
				if (numNeighbSelect != 2) {
					tmp_partAddr = partAddr[0];
					tmp_partAddr0 = partAddr[1];
					local_nPSH = nPSH;
					tmp_neighbIdxLB = neighbIdxLB[0];
					tmp_neighbIdxLB0 = neighbIdxLB[1];
					tmp_isInter = isInter(tmp_partAddr - 1, tmp_partAddr0 + local_nPSH, tmp_neighbIdxLB, tmp_neighbIdxLB0);
					tmp_partAddr1 = partAddr[0];
					tmp_partAddr2 = partAddr[1];
					local_nPSH = nPSH;
					tmp_neighbIdxL = neighbIdxL[0];
					tmp_neighbIdxL0 = neighbIdxL[1];
					tmp_isInter0 = isInter(tmp_partAddr1 - 1, tmp_partAddr2 + local_nPSH - 1, tmp_neighbIdxL, tmp_neighbIdxL0);
					predFlag = tmp_isInter || tmp_isInter0;
				} else {
					predFlag = 1;
				}
				local_predFlag = predFlag;
				if (!local_predFlag) {
					local_ABOVE_RIGHT = ABOVE_RIGHT;
					local_dependSlc = dependSlc;
					getNeighbAddr(local_ABOVE_RIGHT, local_dependSlc, 0);
					getNonMergedScaledMv(list);
				}
				local_predFlag = predFlag;
				if (!local_predFlag) {
					local_ABOVE = ABOVE;
					local_dependSlc = dependSlc;
					getNeighbAddr(local_ABOVE, local_dependSlc, 0);
					getNonMergedScaledMv(list);
				}
				local_predFlag = predFlag;
				if (!local_predFlag) {
					local_ABOVE_LEFT = ABOVE_LEFT;
					local_dependSlc = dependSlc;
					getNeighbAddr(local_ABOVE_LEFT, local_dependSlc, 0);
					getNonMergedScaledMv(list);
				}
				local_numCandidate = numCandidate;
				tmp_mvpIdx1 = mvpIdx[list];
				if (local_numCandidate <= tmp_mvpIdx1) {
					local_enTmpMvp = enTmpMvp;
					if (local_enTmpMvp) {
						getColCandidate(0, list);
					}
					local_numCandidate = numCandidate;
					tmp_mvpIdx2 = mvpIdx[list];
					if (local_numCandidate <= tmp_mvpIdx2) {
						local_numCandidate = numCandidate;
						i = local_numCandidate;
						while (i <= 4) {
							mvPred[i][list][0] = 0;
							mvPred[i][list][1] = 0;
							i = i + 1;
						}
					}
				}
			}
		}
		list = list + 1;
	}

	// Update ports indexes
	index_SyntaxElem += 4;
	read_end_SyntaxElem();

	rate_SyntaxElem += 4;
}
static void checkMergeIdx_isEqToMin1_aligned() {

	i16 tmp_SyntaxElem;
	i16 tmp_SyntaxElem0;
	i32 refIdx[2];
	i32 numNeighbSelect;
	i32 neighbIdxLB[2];
	i32 neighbIdxL[2];
	i32 local_DEBUG_SyntaxElem;
	i16 tmp_SyntaxElem1;
	i16 tmp_SyntaxElem2;
	i16 tmp_SyntaxElem3;
	i16 tmp_SyntaxElem4;
	u8 local_cuPartMode;
	u8 local_numPartDecoded;
	i8 local_currIdx;
	u16 local_lcuAddr;
	u16 local_puAddrInLcu;
	i16 tmp_SyntaxElem5;
	i16 tmp_SyntaxElem6;
	i32 list;
	i32 local_LEFT_BOTTOM;
	i32 local_dependSlc;
	i32 idx_neighbLocIdx;
	i32 local_neighbLocIdx;
	i32 local_LEFT;
	i32 idx_neighbLocIdx0;
	i32 local_neighbLocIdx0;
	i32 local_predFlag;
	i32 local_numCandidate;
	i32 tmp_mvpIdx;
	i32 local_ABOVE_RIGHT;
	i32 local_ABOVE;
	i32 local_ABOVE_LEFT;
	i32 tmp_castBoolToInt;
	i32 tmp_mvpIdx0;
	i32 tmp_partAddr;
	i32 tmp_partAddr0;
	i32 local_nPSH;
	i32 tmp_neighbIdxLB;
	i32 tmp_neighbIdxLB0;
	i32 tmp_isInter;
	i32 tmp_partAddr1;
	i32 tmp_partAddr2;
	i32 tmp_neighbIdxL;
	i32 tmp_neighbIdxL0;
	i32 tmp_isInter0;
	i32 tmp_mvpIdx1;
	i32 local_enTmpMvp;
	i32 tmp_mvpIdx2;
	i32 i;

	tmp_SyntaxElem = tokens_SyntaxElem[(index_SyntaxElem % SIZE_SyntaxElem) + (2)];
	refIdx[0] = tmp_SyntaxElem;
	tmp_SyntaxElem0 = tokens_SyntaxElem[(index_SyntaxElem % SIZE_SyntaxElem) + (3)];
	refIdx[1] = tmp_SyntaxElem0;
	local_DEBUG_SyntaxElem = DEBUG_SyntaxElem;
	if (local_DEBUG_SyntaxElem) {
		tmp_SyntaxElem1 = tokens_SyntaxElem[(index_SyntaxElem % SIZE_SyntaxElem) + (0)];
		tmp_SyntaxElem2 = tokens_SyntaxElem[(index_SyntaxElem % SIZE_SyntaxElem) + (1)];
		printf("mvp_l0 = %i : mvp_l1 = %i\n", tmp_SyntaxElem1, tmp_SyntaxElem2);
		tmp_SyntaxElem3 = tokens_SyntaxElem[(index_SyntaxElem % SIZE_SyntaxElem) + (2)];
		tmp_SyntaxElem4 = tokens_SyntaxElem[(index_SyntaxElem % SIZE_SyntaxElem) + (3)];
		printf("refIdx_l0 = %i : refIdx_l1 = %i\n", tmp_SyntaxElem3, tmp_SyntaxElem4);
	}
	local_cuPartMode = cuPartMode;
	local_numPartDecoded = numPartDecoded;
	local_currIdx = currIdx;
	local_lcuAddr = lcuAddr;
	local_puAddrInLcu = puAddrInLcu;
	saveRefIdx(refIdx, cuSize, local_cuPartMode, local_numPartDecoded, refIdxRef, local_currIdx, local_lcuAddr, local_puAddrInLcu);
	tmp_SyntaxElem5 = tokens_SyntaxElem[(index_SyntaxElem % SIZE_SyntaxElem) + (0)];
	mvpIdx[0] = tmp_SyntaxElem5;
	tmp_SyntaxElem6 = tokens_SyntaxElem[(index_SyntaxElem % SIZE_SyntaxElem) + (1)];
	mvpIdx[1] = tmp_SyntaxElem6;
	list = 0;
	while (list <= 1) {
		numCandidate = 0;
		local_LEFT_BOTTOM = LEFT_BOTTOM;
		local_dependSlc = dependSlc;
		getNeighbAddr(local_LEFT_BOTTOM, local_dependSlc, 0);
		idx_neighbLocIdx = 0;
		while (idx_neighbLocIdx < 2) {
			local_neighbLocIdx = neighbLocIdx[idx_neighbLocIdx];
			neighbIdxLB[idx_neighbLocIdx] = local_neighbLocIdx;
			idx_neighbLocIdx = idx_neighbLocIdx + 1;
		}
		getNonMergedNeighbourMv(list);
		local_LEFT = LEFT;
		local_dependSlc = dependSlc;
		getNeighbAddr(local_LEFT, local_dependSlc, 0);
		idx_neighbLocIdx0 = 0;
		while (idx_neighbLocIdx0 < 2) {
			local_neighbLocIdx0 = neighbLocIdx[idx_neighbLocIdx0];
			neighbIdxL[idx_neighbLocIdx0] = local_neighbLocIdx0;
			idx_neighbLocIdx0 = idx_neighbLocIdx0 + 1;
		}
		local_predFlag = predFlag;
		if (!local_predFlag) {
			getNonMergedNeighbourMv(list);
		}
		local_predFlag = predFlag;
		if (!local_predFlag) {
			local_LEFT_BOTTOM = LEFT_BOTTOM;
			local_dependSlc = dependSlc;
			getNeighbAddr(local_LEFT_BOTTOM, local_dependSlc, 0);
			getNonMergedScaledMv(list);
		}
		local_predFlag = predFlag;
		if (!local_predFlag) {
			local_LEFT = LEFT;
			local_dependSlc = dependSlc;
			getNeighbAddr(local_LEFT, local_dependSlc, 0);
			getNonMergedScaledMv(list);
		}
		local_predFlag = predFlag;
		numNeighbSelect = HevcDecoder_generateInfo_MvComponentPred_castBoolToInt(local_predFlag);
		local_numCandidate = numCandidate;
		tmp_mvpIdx = mvpIdx[list];
		if (local_numCandidate <= tmp_mvpIdx) {
			local_ABOVE_RIGHT = ABOVE_RIGHT;
			local_dependSlc = dependSlc;
			getNeighbAddr(local_ABOVE_RIGHT, local_dependSlc, 0);
			getNonMergedNeighbourMv(list);
			local_predFlag = predFlag;
			if (!local_predFlag) {
				local_ABOVE = ABOVE;
				local_dependSlc = dependSlc;
				getNeighbAddr(local_ABOVE, local_dependSlc, 0);
				getNonMergedNeighbourMv(list);
			}
			local_predFlag = predFlag;
			if (!local_predFlag) {
				local_ABOVE_LEFT = ABOVE_LEFT;
				local_dependSlc = dependSlc;
				getNeighbAddr(local_ABOVE_LEFT, local_dependSlc, 0);
				getNonMergedNeighbourMv(list);
			}
			local_predFlag = predFlag;
			tmp_castBoolToInt = HevcDecoder_generateInfo_MvComponentPred_castBoolToInt(local_predFlag);
			numNeighbSelect = numNeighbSelect + tmp_castBoolToInt;
			local_numCandidate = numCandidate;
			tmp_mvpIdx0 = mvpIdx[list];
			if (local_numCandidate <= tmp_mvpIdx0) {
				if (numNeighbSelect != 2) {
					tmp_partAddr = partAddr[0];
					tmp_partAddr0 = partAddr[1];
					local_nPSH = nPSH;
					tmp_neighbIdxLB = neighbIdxLB[0];
					tmp_neighbIdxLB0 = neighbIdxLB[1];
					tmp_isInter = isInter(tmp_partAddr - 1, tmp_partAddr0 + local_nPSH, tmp_neighbIdxLB, tmp_neighbIdxLB0);
					tmp_partAddr1 = partAddr[0];
					tmp_partAddr2 = partAddr[1];
					local_nPSH = nPSH;
					tmp_neighbIdxL = neighbIdxL[0];
					tmp_neighbIdxL0 = neighbIdxL[1];
					tmp_isInter0 = isInter(tmp_partAddr1 - 1, tmp_partAddr2 + local_nPSH - 1, tmp_neighbIdxL, tmp_neighbIdxL0);
					predFlag = tmp_isInter || tmp_isInter0;
				} else {
					predFlag = 1;
				}
				local_predFlag = predFlag;
				if (!local_predFlag) {
					local_ABOVE_RIGHT = ABOVE_RIGHT;
					local_dependSlc = dependSlc;
					getNeighbAddr(local_ABOVE_RIGHT, local_dependSlc, 0);
					getNonMergedScaledMv(list);
				}
				local_predFlag = predFlag;
				if (!local_predFlag) {
					local_ABOVE = ABOVE;
					local_dependSlc = dependSlc;
					getNeighbAddr(local_ABOVE, local_dependSlc, 0);
					getNonMergedScaledMv(list);
				}
				local_predFlag = predFlag;
				if (!local_predFlag) {
					local_ABOVE_LEFT = ABOVE_LEFT;
					local_dependSlc = dependSlc;
					getNeighbAddr(local_ABOVE_LEFT, local_dependSlc, 0);
					getNonMergedScaledMv(list);
				}
				local_numCandidate = numCandidate;
				tmp_mvpIdx1 = mvpIdx[list];
				if (local_numCandidate <= tmp_mvpIdx1) {
					local_enTmpMvp = enTmpMvp;
					if (local_enTmpMvp) {
						getColCandidate(0, list);
					}
					local_numCandidate = numCandidate;
					tmp_mvpIdx2 = mvpIdx[list];
					if (local_numCandidate <= tmp_mvpIdx2) {
						local_numCandidate = numCandidate;
						i = local_numCandidate;
						while (i <= 4) {
							mvPred[i][list][0] = 0;
							mvPred[i][list][1] = 0;
							i = i + 1;
						}
					}
				}
			}
		}
		list = list + 1;
	}

	// Update ports indexes
	index_SyntaxElem += 4;
	read_end_SyntaxElem();

	rate_SyntaxElem += 4;
}
static i32 isSchedulable_getMvd() {
	i32 result;

	result = 1;
	return result;
}

static void getMvd() {

	i32 idxMvInfo;
	i32 refIdx[2];
	i32 refIdxToSend;
	i16 pocToSend;
	i32 local_DEBUG_SyntaxElem;
	i16 tmp_SyntaxElem;
	i16 tmp_SyntaxElem0;
	i16 tmp_SyntaxElem1;
	i16 tmp_SyntaxElem2;
	i32 i;
	i32 local_mergeIdx;
	i32 tmp_mvPred;
	i32 tmp_mvPred0;
	i32 tmp_mvPred1;
	i32 tmp_mvPred2;
	i32 tmp_mvPred3;
	i16 tmp_SyntaxElem3;
	i32 tmp_mvPred4;
	i16 tmp_SyntaxElem4;
	i32 tmp_refIdxPred;
	i32 i0;
	i8 local_currIdx;
	u16 local_lcuAddr;
	u16 local_puAddrInLcu;
	i8 tmp_refIdxRef;
	i32 local_isBSlice;
	i32 tmp_refIdx;
	i32 tmp_refIdx0;
	u8 local_predCuSize;
	u8 tmp_cuSize;
	u8 tmp_cuSize0;
	i32 tmp_refIdx1;
	i32 tmp_refIdx2;
	u8 local_cuPartMode;
	u8 local_numPartDecoded;
	i32 tmp_refIdx3;
	i32 tmp_refIdx4;
	u8 local_BI_PRED;
	i32 tmp_refIdx5;
	u8 local_PRED_L0;
	u8 local_PRED_L1;
	i32 tmp_refIdx6;
	i32 tmp_refIdx7;
	i32 i1;
	i16 tmp_mvVal;
	i32 tmp_cuAddr;
	i32 tmp_refIdx8;
	i32 i2;
	i16 tmp_mvVal0;
	i32 tmp_cuAddr0;
	i32 local_DEBUG_Mv;
	i32 tmp_mvToSend;
	i32 tmp_mvToSend0;
	u8 local_isBiPredOrLx;
	i32 idx_puSize;
	u8 local_puSize;

	local_DEBUG_SyntaxElem = DEBUG_SyntaxElem;
	if (local_DEBUG_SyntaxElem) {
		tmp_SyntaxElem = tokens_SyntaxElem[(index_SyntaxElem + (0)) % SIZE_SyntaxElem];
		tmp_SyntaxElem0 = tokens_SyntaxElem[(index_SyntaxElem + (1)) % SIZE_SyntaxElem];
		printf("mvd_0_x = %i : mvd_0_y = %i\n", tmp_SyntaxElem, tmp_SyntaxElem0);
		tmp_SyntaxElem1 = tokens_SyntaxElem[(index_SyntaxElem + (2)) % SIZE_SyntaxElem];
		tmp_SyntaxElem2 = tokens_SyntaxElem[(index_SyntaxElem + (3)) % SIZE_SyntaxElem];
		printf("mvd_1_x = %i : mvd_1_y = %i\n", tmp_SyntaxElem1, tmp_SyntaxElem2);
	}
	i = 0;
	while (i <= 1) {
		local_mergeIdx = mergeIdx;
		if (local_mergeIdx >= 0) {
			local_mergeIdx = mergeIdx;
			idxMvInfo = local_mergeIdx;
		} else {
			idxMvInfo = mvpIdx[i];
		}
		if (idxMvInfo > -1 && idxMvInfo < 5) {
			tmp_mvPred = mvPred[idxMvInfo][i][0];
			if (tmp_mvPred > 32767) {
				mvPred[idxMvInfo][i][0] = 32767;
			}
			tmp_mvPred0 = mvPred[idxMvInfo][i][0];
			if (tmp_mvPred0 < -32768) {
				mvPred[idxMvInfo][i][0] = -32768;
			}
			tmp_mvPred1 = mvPred[idxMvInfo][i][1];
			if (tmp_mvPred1 > 32767) {
				mvPred[idxMvInfo][i][1] = 32767;
			}
			tmp_mvPred2 = mvPred[idxMvInfo][i][1];
			if (tmp_mvPred2 < -32768) {
				mvPred[idxMvInfo][i][1] = -32768;
			}
			tmp_mvPred3 = mvPred[idxMvInfo][i][0];
			tmp_SyntaxElem3 = tokens_SyntaxElem[(index_SyntaxElem + (2 * i)) % SIZE_SyntaxElem];
			mvVal[i][0] = tmp_mvPred3 + tmp_SyntaxElem3;
			tmp_mvPred4 = mvPred[idxMvInfo][i][1];
			tmp_SyntaxElem4 = tokens_SyntaxElem[(index_SyntaxElem + (2 * i + 1)) % SIZE_SyntaxElem];
			mvVal[i][1] = tmp_mvPred4 + tmp_SyntaxElem4;
			tmp_refIdxPred = refIdxPred[idxMvInfo][i];
			refIdx[i] = tmp_refIdxPred;
		}
		i = i + 1;
	}
	local_mergeIdx = mergeIdx;
	if (local_mergeIdx == -1) {
		i0 = 0;
		while (i0 <= 1) {
			local_currIdx = currIdx;
			local_lcuAddr = lcuAddr;
			local_puAddrInLcu = puAddrInLcu;
			tmp_refIdxRef = refIdxRef[local_currIdx][local_lcuAddr][local_puAddrInLcu][i0];
			refIdx[i0] = tmp_refIdxRef;
			i0 = i0 + 1;
		}
	}
	local_isBSlice = isBSlice;
	tmp_refIdx = refIdx[0];
	tmp_refIdx0 = refIdx[1];
	local_predCuSize = predCuSize;
	tmp_cuSize = cuSize[0];
	tmp_cuSize0 = cuSize[1];
	if (!local_isBSlice || tmp_refIdx != -1 && tmp_refIdx0 != -1 && local_predCuSize == 8 && (tmp_cuSize < 8 || tmp_cuSize0 < 8)) {
		refIdx[1] = -1;
		mvVal[1][0] = 0;
		mvVal[1][1] = 0;
	}
	tmp_refIdx1 = refIdx[0];
	if (tmp_refIdx1 == -1) {
		mvVal[0][0] = 0;
		mvVal[0][1] = 0;
	}
	tmp_refIdx2 = refIdx[1];
	if (tmp_refIdx2 == -1) {
		mvVal[1][0] = 0;
		mvVal[1][1] = 0;
	}
	local_mergeIdx = mergeIdx;
	if (local_mergeIdx != -1) {
		local_cuPartMode = cuPartMode;
		local_numPartDecoded = numPartDecoded;
		local_currIdx = currIdx;
		local_lcuAddr = lcuAddr;
		local_puAddrInLcu = puAddrInLcu;
		saveRefIdx(refIdx, cuSize, local_cuPartMode, local_numPartDecoded, refIdxRef, local_currIdx, local_lcuAddr, local_puAddrInLcu);
	}
	local_cuPartMode = cuPartMode;
	local_numPartDecoded = numPartDecoded;
	local_currIdx = currIdx;
	local_lcuAddr = lcuAddr;
	local_puAddrInLcu = puAddrInLcu;
	saveMvComponent(mvVal, cuSize, local_cuPartMode, local_numPartDecoded, mvRef, local_currIdx, local_lcuAddr, local_puAddrInLcu);
	tmp_refIdx3 = refIdx[0];
	tmp_refIdx4 = refIdx[1];
	if (tmp_refIdx3 != -1 && tmp_refIdx4 != -1) {
		local_BI_PRED = HevcDecoder_generateInfo_MvComponentPred_BI_PRED;
		isBiPredOrLx = local_BI_PRED;
	} else {
		tmp_refIdx5 = refIdx[0];
		if (tmp_refIdx5 != -1) {
			local_PRED_L0 = HevcDecoder_generateInfo_MvComponentPred_PRED_L0;
			isBiPredOrLx = local_PRED_L0;
		} else {
			local_PRED_L1 = HevcDecoder_generateInfo_MvComponentPred_PRED_L1;
			isBiPredOrLx = local_PRED_L1;
		}
	}
	tmp_refIdx6 = refIdx[0];
	if (tmp_refIdx6 != -1) {
		refIdxToSend = refIdx[0];
		tmp_refIdx7 = refIdx[0];
		pocToSend = pocRefListX[0][tmp_refIdx7];
		i1 = 0;
		while (i1 <= 1) {
			tmp_mvVal = mvVal[0][i1];
			tmp_cuAddr = cuAddr[i1];
			tokens_Mv[(index_Mv + (i1)) % SIZE_Mv] = tmp_mvVal + (tmp_cuAddr << 2);
			i1 = i1 + 1;
		}
	} else {
		refIdxToSend = refIdx[1];
		tmp_refIdx8 = refIdx[1];
		pocToSend = pocRefListX[1][tmp_refIdx8];
		i2 = 0;
		while (i2 <= 1) {
			tmp_mvVal0 = mvVal[1][i2];
			tmp_cuAddr0 = cuAddr[i2];
			tokens_Mv[(index_Mv + (i2)) % SIZE_Mv] = tmp_mvVal0 + (tmp_cuAddr0 << 2);
			i2 = i2 + 1;
		}
	}
	local_DEBUG_Mv = DEBUG_Mv;
	if (local_DEBUG_Mv) {
		tmp_mvToSend = tokens_Mv[(index_Mv + (0)) % SIZE_Mv];
		tmp_mvToSend0 = tokens_Mv[(index_Mv + (1)) % SIZE_Mv];
		printf("mv = %i, %i\n", tmp_mvToSend, tmp_mvToSend0);
	}
	local_isBiPredOrLx = isBiPredOrLx;
	tokens_IsBiPredOrLx[(index_IsBiPredOrLx + (0)) % SIZE_IsBiPredOrLx] = local_isBiPredOrLx;
	tokens_IsReadOrNewSlice[(index_IsReadOrNewSlice + (0)) % SIZE_IsReadOrNewSlice] = 1;
	tokens_RefIdx[(index_RefIdx + (0)) % SIZE_RefIdx] = refIdxToSend;
	tokens_PocRef[(index_PocRef + (0)) % SIZE_PocRef] = pocToSend;
	idx_puSize = 0;
	while (idx_puSize < 2) {
		local_puSize = puSize[idx_puSize];
		tokens_PredCuSize[(index_PredCuSize + (idx_puSize)) % SIZE_PredCuSize] = local_puSize;
		idx_puSize = idx_puSize + 1;
	}

	// Update ports indexes
	index_SyntaxElem += 4;
	read_end_SyntaxElem();
	index_IsBiPredOrLx += 1;
	index_IsReadOrNewSlice += 1;
	index_Mv += 2;
	write_end_Mv();
	index_RefIdx += 1;
	index_PocRef += 1;
	index_PredCuSize += 2;
	write_end_PredCuSize();

	rate_SyntaxElem += 4;
}
static void getMvd_aligned() {

	i32 idxMvInfo;
	i32 refIdx[2];
	i32 refIdxToSend;
	i16 pocToSend;
	i32 local_DEBUG_SyntaxElem;
	i16 tmp_SyntaxElem;
	i16 tmp_SyntaxElem0;
	i16 tmp_SyntaxElem1;
	i16 tmp_SyntaxElem2;
	i32 i;
	i32 local_mergeIdx;
	i32 tmp_mvPred;
	i32 tmp_mvPred0;
	i32 tmp_mvPred1;
	i32 tmp_mvPred2;
	i32 tmp_mvPred3;
	i16 tmp_SyntaxElem3;
	i32 tmp_mvPred4;
	i16 tmp_SyntaxElem4;
	i32 tmp_refIdxPred;
	i32 i0;
	i8 local_currIdx;
	u16 local_lcuAddr;
	u16 local_puAddrInLcu;
	i8 tmp_refIdxRef;
	i32 local_isBSlice;
	i32 tmp_refIdx;
	i32 tmp_refIdx0;
	u8 local_predCuSize;
	u8 tmp_cuSize;
	u8 tmp_cuSize0;
	i32 tmp_refIdx1;
	i32 tmp_refIdx2;
	u8 local_cuPartMode;
	u8 local_numPartDecoded;
	i32 tmp_refIdx3;
	i32 tmp_refIdx4;
	u8 local_BI_PRED;
	i32 tmp_refIdx5;
	u8 local_PRED_L0;
	u8 local_PRED_L1;
	i32 tmp_refIdx6;
	i32 tmp_refIdx7;
	i32 i1;
	i16 tmp_mvVal;
	i32 tmp_cuAddr;
	i32 tmp_refIdx8;
	i32 i2;
	i16 tmp_mvVal0;
	i32 tmp_cuAddr0;
	i32 local_DEBUG_Mv;
	i32 tmp_mvToSend;
	i32 tmp_mvToSend0;
	u8 local_isBiPredOrLx;
	i32 idx_puSize;
	u8 local_puSize;

	local_DEBUG_SyntaxElem = DEBUG_SyntaxElem;
	if (local_DEBUG_SyntaxElem) {
		tmp_SyntaxElem = tokens_SyntaxElem[(index_SyntaxElem % SIZE_SyntaxElem) + (0)];
		tmp_SyntaxElem0 = tokens_SyntaxElem[(index_SyntaxElem % SIZE_SyntaxElem) + (1)];
		printf("mvd_0_x = %i : mvd_0_y = %i\n", tmp_SyntaxElem, tmp_SyntaxElem0);
		tmp_SyntaxElem1 = tokens_SyntaxElem[(index_SyntaxElem % SIZE_SyntaxElem) + (2)];
		tmp_SyntaxElem2 = tokens_SyntaxElem[(index_SyntaxElem % SIZE_SyntaxElem) + (3)];
		printf("mvd_1_x = %i : mvd_1_y = %i\n", tmp_SyntaxElem1, tmp_SyntaxElem2);
	}
	i = 0;
	while (i <= 1) {
		local_mergeIdx = mergeIdx;
		if (local_mergeIdx >= 0) {
			local_mergeIdx = mergeIdx;
			idxMvInfo = local_mergeIdx;
		} else {
			idxMvInfo = mvpIdx[i];
		}
		if (idxMvInfo > -1 && idxMvInfo < 5) {
			tmp_mvPred = mvPred[idxMvInfo][i][0];
			if (tmp_mvPred > 32767) {
				mvPred[idxMvInfo][i][0] = 32767;
			}
			tmp_mvPred0 = mvPred[idxMvInfo][i][0];
			if (tmp_mvPred0 < -32768) {
				mvPred[idxMvInfo][i][0] = -32768;
			}
			tmp_mvPred1 = mvPred[idxMvInfo][i][1];
			if (tmp_mvPred1 > 32767) {
				mvPred[idxMvInfo][i][1] = 32767;
			}
			tmp_mvPred2 = mvPred[idxMvInfo][i][1];
			if (tmp_mvPred2 < -32768) {
				mvPred[idxMvInfo][i][1] = -32768;
			}
			tmp_mvPred3 = mvPred[idxMvInfo][i][0];
			tmp_SyntaxElem3 = tokens_SyntaxElem[(index_SyntaxElem % SIZE_SyntaxElem) + (2 * i)];
			mvVal[i][0] = tmp_mvPred3 + tmp_SyntaxElem3;
			tmp_mvPred4 = mvPred[idxMvInfo][i][1];
			tmp_SyntaxElem4 = tokens_SyntaxElem[(index_SyntaxElem % SIZE_SyntaxElem) + (2 * i + 1)];
			mvVal[i][1] = tmp_mvPred4 + tmp_SyntaxElem4;
			tmp_refIdxPred = refIdxPred[idxMvInfo][i];
			refIdx[i] = tmp_refIdxPred;
		}
		i = i + 1;
	}
	local_mergeIdx = mergeIdx;
	if (local_mergeIdx == -1) {
		i0 = 0;
		while (i0 <= 1) {
			local_currIdx = currIdx;
			local_lcuAddr = lcuAddr;
			local_puAddrInLcu = puAddrInLcu;
			tmp_refIdxRef = refIdxRef[local_currIdx][local_lcuAddr][local_puAddrInLcu][i0];
			refIdx[i0] = tmp_refIdxRef;
			i0 = i0 + 1;
		}
	}
	local_isBSlice = isBSlice;
	tmp_refIdx = refIdx[0];
	tmp_refIdx0 = refIdx[1];
	local_predCuSize = predCuSize;
	tmp_cuSize = cuSize[0];
	tmp_cuSize0 = cuSize[1];
	if (!local_isBSlice || tmp_refIdx != -1 && tmp_refIdx0 != -1 && local_predCuSize == 8 && (tmp_cuSize < 8 || tmp_cuSize0 < 8)) {
		refIdx[1] = -1;
		mvVal[1][0] = 0;
		mvVal[1][1] = 0;
	}
	tmp_refIdx1 = refIdx[0];
	if (tmp_refIdx1 == -1) {
		mvVal[0][0] = 0;
		mvVal[0][1] = 0;
	}
	tmp_refIdx2 = refIdx[1];
	if (tmp_refIdx2 == -1) {
		mvVal[1][0] = 0;
		mvVal[1][1] = 0;
	}
	local_mergeIdx = mergeIdx;
	if (local_mergeIdx != -1) {
		local_cuPartMode = cuPartMode;
		local_numPartDecoded = numPartDecoded;
		local_currIdx = currIdx;
		local_lcuAddr = lcuAddr;
		local_puAddrInLcu = puAddrInLcu;
		saveRefIdx(refIdx, cuSize, local_cuPartMode, local_numPartDecoded, refIdxRef, local_currIdx, local_lcuAddr, local_puAddrInLcu);
	}
	local_cuPartMode = cuPartMode;
	local_numPartDecoded = numPartDecoded;
	local_currIdx = currIdx;
	local_lcuAddr = lcuAddr;
	local_puAddrInLcu = puAddrInLcu;
	saveMvComponent(mvVal, cuSize, local_cuPartMode, local_numPartDecoded, mvRef, local_currIdx, local_lcuAddr, local_puAddrInLcu);
	tmp_refIdx3 = refIdx[0];
	tmp_refIdx4 = refIdx[1];
	if (tmp_refIdx3 != -1 && tmp_refIdx4 != -1) {
		local_BI_PRED = HevcDecoder_generateInfo_MvComponentPred_BI_PRED;
		isBiPredOrLx = local_BI_PRED;
	} else {
		tmp_refIdx5 = refIdx[0];
		if (tmp_refIdx5 != -1) {
			local_PRED_L0 = HevcDecoder_generateInfo_MvComponentPred_PRED_L0;
			isBiPredOrLx = local_PRED_L0;
		} else {
			local_PRED_L1 = HevcDecoder_generateInfo_MvComponentPred_PRED_L1;
			isBiPredOrLx = local_PRED_L1;
		}
	}
	tmp_refIdx6 = refIdx[0];
	if (tmp_refIdx6 != -1) {
		refIdxToSend = refIdx[0];
		tmp_refIdx7 = refIdx[0];
		pocToSend = pocRefListX[0][tmp_refIdx7];
		i1 = 0;
		while (i1 <= 1) {
			tmp_mvVal = mvVal[0][i1];
			tmp_cuAddr = cuAddr[i1];
			tokens_Mv[(index_Mv % SIZE_Mv) + (i1)] = tmp_mvVal + (tmp_cuAddr << 2);
			i1 = i1 + 1;
		}
	} else {
		refIdxToSend = refIdx[1];
		tmp_refIdx8 = refIdx[1];
		pocToSend = pocRefListX[1][tmp_refIdx8];
		i2 = 0;
		while (i2 <= 1) {
			tmp_mvVal0 = mvVal[1][i2];
			tmp_cuAddr0 = cuAddr[i2];
			tokens_Mv[(index_Mv % SIZE_Mv) + (i2)] = tmp_mvVal0 + (tmp_cuAddr0 << 2);
			i2 = i2 + 1;
		}
	}
	local_DEBUG_Mv = DEBUG_Mv;
	if (local_DEBUG_Mv) {
		tmp_mvToSend = tokens_Mv[(index_Mv % SIZE_Mv) + (0)];
		tmp_mvToSend0 = tokens_Mv[(index_Mv % SIZE_Mv) + (1)];
		printf("mv = %i, %i\n", tmp_mvToSend, tmp_mvToSend0);
	}
	local_isBiPredOrLx = isBiPredOrLx;
	tokens_IsBiPredOrLx[(index_IsBiPredOrLx + (0)) % SIZE_IsBiPredOrLx] = local_isBiPredOrLx;
	tokens_IsReadOrNewSlice[(index_IsReadOrNewSlice + (0)) % SIZE_IsReadOrNewSlice] = 1;
	tokens_RefIdx[(index_RefIdx + (0)) % SIZE_RefIdx] = refIdxToSend;
	tokens_PocRef[(index_PocRef + (0)) % SIZE_PocRef] = pocToSend;
	idx_puSize = 0;
	while (idx_puSize < 2) {
		local_puSize = puSize[idx_puSize];
		tokens_PredCuSize[(index_PredCuSize % SIZE_PredCuSize) + (idx_puSize)] = local_puSize;
		idx_puSize = idx_puSize + 1;
	}

	// Update ports indexes
	index_SyntaxElem += 4;
	read_end_SyntaxElem();
	index_IsBiPredOrLx += 1;
	index_IsReadOrNewSlice += 1;
	index_Mv += 2;
	write_end_Mv();
	index_RefIdx += 1;
	index_PocRef += 1;
	index_PredCuSize += 2;
	write_end_PredCuSize();

	rate_SyntaxElem += 4;
}
static i32 isSchedulable_getRps_launch() {
	i32 result;
	u32 local_nbList;

	local_nbList = nbList;
	result = local_nbList < 5;
	return result;
}

static void getRps_launch() {

	i16 numPic;
	i32 local_DEBUG_RpsPoc;
	u32 local_nbList;
	u32 local_sizeOfList;

	numPic = tokens_RpsPoc[(index_RpsPoc + (0)) % SIZE_RpsPoc];
	sizeOfList = numPic;
	local_DEBUG_RpsPoc = DEBUG_RpsPoc;
	if (local_DEBUG_RpsPoc) {
		local_nbList = nbList;
		local_sizeOfList = sizeOfList;
		printf("RefPocSize[%u] = %u\n", local_nbList, local_sizeOfList);
	}

	// Update ports indexes
	index_RpsPoc += 1;

	rate_RpsPoc += 1;
}
static i32 isSchedulable_getRps_done() {
	i32 result;
	u32 local_nbList;

	local_nbList = nbList;
	result = local_nbList == 5;
	return result;
}

static void getRps_done() {

	i32 i;
	i32 tmp_isRef;
	i32 tmp_isStillRef;
	i8 local_currIdx;

	i = 0;
	while (i <= 16) {
		tmp_isRef = isRef[i];
		tmp_isStillRef = isStillRef[i];
		isRef[i] = tmp_isRef && tmp_isStillRef;
		i = i + 1;
	}
	local_currIdx = currIdx;
	isRef[local_currIdx] = 1;
	minSizeRefListX = 31;

	// Update ports indexes

}
static i32 isSchedulable_getRpsPoc_launch() {
	i32 result;
	u32 local_sizeOfList;

	local_sizeOfList = sizeOfList;
	result = local_sizeOfList > 0;
	return result;
}

static void getRpsPoc_launch() {

	i16 pocVal;
	u32 local_sizeOfList;
	i32 local_DEBUG_RpsPoc;
	i32 i;
	i16 tmp_pocRef;

	pocVal = tokens_RpsPoc[(index_RpsPoc + (0)) % SIZE_RpsPoc];
	local_sizeOfList = sizeOfList;
	sizeOfList = local_sizeOfList - 1;
	local_DEBUG_RpsPoc = DEBUG_RpsPoc;
	if (local_DEBUG_RpsPoc) {
		printf("RefPoc = %i\n", pocVal);
	}
	i = 0;
	while (i <= 16) {
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
	u32 local_sizeOfList;

	local_sizeOfList = sizeOfList;
	result = local_sizeOfList == 0;
	return result;
}

static void getRpsPoc_done() {

	u32 local_nbList;

	local_nbList = nbList;
	nbList = local_nbList + 1;

	// Update ports indexes

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
	u8 local_minSizeRefListX;
	i32 tmp_min;
	i32 local_DEBUG_RefList;
	u8 local_listIdx;
	u8 local_listSize;

	sizeList = tokens_RefList[(index_RefList + (0)) % SIZE_RefList];
	listSize = sizeList;
	local_minSizeRefListX = minSizeRefListX;
	tmp_min = HevcDecoder_generateInfo_MvComponentPred_min(sizeList, local_minSizeRefListX);
	minSizeRefListX = tmp_min;
	sizeIdx = 0;
	local_DEBUG_RefList = DEBUG_RefList;
	if (local_DEBUG_RefList) {
		local_listIdx = listIdx;
		local_listSize = listSize;
		printf("numRefIdxLxAct[%u] = %u\n", local_listIdx, local_listSize);
	}

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

	i16 local_maxPoc;
	i8 local_currIdx;
	i16 tmp_pocRef;
	i32 local_isBSlice;
	u8 local_colocFromL0;
	i32 local_colRefIdx;
	i16 tmp_pocRefListX;
	i32 i;
	i32 tmp_isRef;
	i16 tmp_pocRef0;
	i32 local_colPoc;

	local_maxPoc = maxPoc;
	local_currIdx = currIdx;
	tmp_pocRef = pocRef[local_currIdx];
	local_isBSlice = isBSlice;
	useLN = local_maxPoc > tmp_pocRef || !local_isBSlice;
	local_colocFromL0 = colocFromL0;
	local_colRefIdx = colRefIdx;
	tmp_pocRefListX = pocRefListX[local_colocFromL0 ^ 1][local_colRefIdx];
	colPoc = tmp_pocRefListX;
	colRefIdx = 0;
	i = 0;
	while (i <= 16) {
		tmp_isRef = isRef[i];
		tmp_pocRef0 = pocRef[i];
		local_colPoc = colPoc;
		if (tmp_isRef && tmp_pocRef0 == local_colPoc) {
			colRefIdx = i;
		}
		i = i + 1;
	}

	// Update ports indexes

}
static i32 isSchedulable_getRefList_launch() {
	i32 result;
	u8 local_sizeIdx;
	u8 local_listSize;

	local_sizeIdx = sizeIdx;
	local_listSize = listSize;
	result = local_sizeIdx < local_listSize;
	return result;
}

static void getRefList_launch() {

	i16 refPoc;
	i32 local_DEBUG_RefList;
	u8 local_listIdx;
	u8 local_sizeIdx;
	i16 local_maxPoc;
	i32 tmp_max;
	i8 local_currIdx;
	u16 local_slcIdx;

	refPoc = tokens_RefList[(index_RefList + (0)) % SIZE_RefList];
	local_DEBUG_RefList = DEBUG_RefList;
	if (local_DEBUG_RefList) {
		local_listIdx = listIdx;
		local_sizeIdx = sizeIdx;
		printf("RefList[%u][%u] = %i\n", local_listIdx, local_sizeIdx, refPoc);
	}
	local_maxPoc = maxPoc;
	tmp_max = HevcDecoder_generateInfo_MvComponentPred_max(local_maxPoc, refPoc);
	maxPoc = tmp_max;
	local_listIdx = listIdx;
	local_sizeIdx = sizeIdx;
	pocRefListX[local_listIdx][local_sizeIdx] = refPoc;
	local_currIdx = currIdx;
	local_slcIdx = slcIdx;
	local_listIdx = listIdx;
	local_sizeIdx = sizeIdx;
	pocRefList[local_currIdx][local_slcIdx][local_listIdx][local_sizeIdx] = refPoc;
	local_sizeIdx = sizeIdx;
	sizeIdx = local_sizeIdx + 1;

	// Update ports indexes
	index_RefList += 1;

	rate_RefList += 1;
}
static i32 isSchedulable_getRefList_done() {
	i32 result;
	u8 local_sizeIdx;
	u8 local_listSize;

	local_sizeIdx = sizeIdx;
	local_listSize = listSize;
	result = local_sizeIdx == local_listSize;
	return result;
}

static void getRefList_done() {

	u8 local_listIdx;

	local_listIdx = listIdx;
	listIdx = local_listIdx + 1;

	// Update ports indexes

}
static i32 isSchedulable_send2ndMv_launch() {
	i32 result;
	u8 local_isBiPredOrLx;
	u8 local_BI_PRED;

	local_isBiPredOrLx = isBiPredOrLx;
	local_BI_PRED = HevcDecoder_generateInfo_MvComponentPred_BI_PRED;
	result = local_isBiPredOrLx == local_BI_PRED;
	return result;
}

static void send2ndMv_launch() {

	i32 refIdxToSend;
	i16 pocToSend;
	i8 local_currIdx;
	u16 local_lcuAddr;
	u16 local_puAddrInLcu;
	i32 i;
	i16 tmp_mvVal;
	i32 tmp_cuAddr;
	i32 local_DEBUG_Mv;
	i32 tmp_mvToSend;
	i32 tmp_mvToSend0;
	i32 idx_puSize;
	u8 local_puSize;

	local_currIdx = currIdx;
	local_lcuAddr = lcuAddr;
	local_puAddrInLcu = puAddrInLcu;
	refIdxToSend = refIdxRef[local_currIdx][local_lcuAddr][local_puAddrInLcu][1];
	i = 0;
	while (i <= 1) {
		tmp_mvVal = mvVal[1][i];
		tmp_cuAddr = cuAddr[i];
		tokens_Mv[(index_Mv + (i)) % SIZE_Mv] = tmp_mvVal + (tmp_cuAddr << 2);
		i = i + 1;
	}
	pocToSend = pocRefListX[1][refIdxToSend];
	local_DEBUG_Mv = DEBUG_Mv;
	if (local_DEBUG_Mv) {
		tmp_mvToSend = tokens_Mv[(index_Mv + (0)) % SIZE_Mv];
		tmp_mvToSend0 = tokens_Mv[(index_Mv + (1)) % SIZE_Mv];
		printf("mv = %i, %i\n", tmp_mvToSend, tmp_mvToSend0);
	}
	tokens_PocRef[(index_PocRef + (0)) % SIZE_PocRef] = pocToSend;
	tokens_RefIdx[(index_RefIdx + (0)) % SIZE_RefIdx] = refIdxToSend;
	idx_puSize = 0;
	while (idx_puSize < 2) {
		local_puSize = puSize[idx_puSize];
		tokens_PredCuSize[(index_PredCuSize + (idx_puSize)) % SIZE_PredCuSize] = local_puSize;
		idx_puSize = idx_puSize + 1;
	}

	// Update ports indexes
	index_PocRef += 1;
	index_RefIdx += 1;
	index_Mv += 2;
	write_end_Mv();
	index_PredCuSize += 2;
	write_end_PredCuSize();

}
static void send2ndMv_launch_aligned() {

	i32 refIdxToSend;
	i16 pocToSend;
	i8 local_currIdx;
	u16 local_lcuAddr;
	u16 local_puAddrInLcu;
	i32 i;
	i16 tmp_mvVal;
	i32 tmp_cuAddr;
	i32 local_DEBUG_Mv;
	i32 tmp_mvToSend;
	i32 tmp_mvToSend0;
	i32 idx_puSize;
	u8 local_puSize;

	local_currIdx = currIdx;
	local_lcuAddr = lcuAddr;
	local_puAddrInLcu = puAddrInLcu;
	refIdxToSend = refIdxRef[local_currIdx][local_lcuAddr][local_puAddrInLcu][1];
	i = 0;
	while (i <= 1) {
		tmp_mvVal = mvVal[1][i];
		tmp_cuAddr = cuAddr[i];
		tokens_Mv[(index_Mv % SIZE_Mv) + (i)] = tmp_mvVal + (tmp_cuAddr << 2);
		i = i + 1;
	}
	pocToSend = pocRefListX[1][refIdxToSend];
	local_DEBUG_Mv = DEBUG_Mv;
	if (local_DEBUG_Mv) {
		tmp_mvToSend = tokens_Mv[(index_Mv % SIZE_Mv) + (0)];
		tmp_mvToSend0 = tokens_Mv[(index_Mv % SIZE_Mv) + (1)];
		printf("mv = %i, %i\n", tmp_mvToSend, tmp_mvToSend0);
	}
	tokens_PocRef[(index_PocRef + (0)) % SIZE_PocRef] = pocToSend;
	tokens_RefIdx[(index_RefIdx + (0)) % SIZE_RefIdx] = refIdxToSend;
	idx_puSize = 0;
	while (idx_puSize < 2) {
		local_puSize = puSize[idx_puSize];
		tokens_PredCuSize[(index_PredCuSize % SIZE_PredCuSize) + (idx_puSize)] = local_puSize;
		idx_puSize = idx_puSize + 1;
	}

	// Update ports indexes
	index_PocRef += 1;
	index_RefIdx += 1;
	index_Mv += 2;
	write_end_Mv();
	index_PredCuSize += 2;
	write_end_PredCuSize();

}
static i32 isSchedulable_send2ndMv_skip() {
	i32 result;
	u8 local_isBiPredOrLx;
	u8 local_BI_PRED;

	local_isBiPredOrLx = isBiPredOrLx;
	local_BI_PRED = HevcDecoder_generateInfo_MvComponentPred_BI_PRED;
	result = local_isBiPredOrLx != local_BI_PRED;
	return result;
}

static void send2ndMv_skip() {



	// Update ports indexes

}

////////////////////////////////////////////////////////////////////////////////
// Initializes

void HevcDecoder_generateInfo_MvComponentPred_initialize(schedinfo_t *si) {
	int i = 0;
	write_IsBiPredOrLx();
	write_IsReadOrNewSlice();
	write_Mv();
	write_PocRef();
	write_PredCuSize();
	write_RefIdx();
	/* Set initial state to current FSM state */
	_FSM_state = my_state_GetPartMode;
finished:
	write_end_IsBiPredOrLx();
	write_end_IsReadOrNewSlice();
	write_end_Mv();
	write_end_PocRef();
	write_end_PredCuSize();
	write_end_RefIdx();
	return;
}

////////////////////////////////////////////////////////////////////////////////
// Action scheduler

void HevcDecoder_generateInfo_MvComponentPred_scheduler(schedinfo_t *si) {
	int i = 0;

	read_CUInfo();
	read_LcuSizeMax();
	read_PartMode();
	read_PicSize();
	read_Poc();
	read_RefList();
	read_RpsPoc();
	read_SliceAddr();
	read_SliceType();
	read_SyntaxElem();
	read_TilesCoord();
	write_IsBiPredOrLx();
	write_IsReadOrNewSlice();
	write_Mv();
	write_PocRef();
	write_PredCuSize();
	write_RefIdx();

	// jump to FSM state
	switch (_FSM_state) {
	case my_state_CheckIndepSlc:
		goto l_CheckIndepSlc;
	case my_state_CheckMergeIdx:
		goto l_CheckMergeIdx;
	case my_state_GetCuInfo:
		goto l_GetCuInfo;
	case my_state_GetCuMode:
		goto l_GetCuMode;
	case my_state_GetMvd:
		goto l_GetMvd;
	case my_state_GetPartMode:
		goto l_GetPartMode;
	case my_state_GetRefList:
		goto l_GetRefList;
	case my_state_GetRps:
		goto l_GetRps;
	case my_state_GetRpsPoc:
		goto l_GetRpsPoc;
	case my_state_GetSizeRefList:
		goto l_GetSizeRefList;
	case my_state_GetTilesCoord:
		goto l_GetTilesCoord;
	case my_state_Send2ndMv:
		goto l_Send2ndMv;
	default:
		printf("unknown state in HevcDecoder_generateInfo_MvComponentPred.c : %s\n", stateNames[_FSM_state]);
		exit(1);
	}

	// FSM transitions
l_CheckIndepSlc:
	if (isSchedulable_checkDepSlc_isTrue()) {
		checkDepSlc_isTrue();
		i++;
		goto l_GetPartMode;
	} else if (numTokens_SyntaxElem - index_SyntaxElem >= 2 && numTokens_LcuSizeMax - index_LcuSizeMax >= 1 && numTokens_PicSize - index_PicSize >= 2 && numTokens_Poc - index_Poc >= 1 && numTokens_SliceType - index_SliceType >= 1 && numTokens_TilesCoord - index_TilesCoord >= 1 && isSchedulable_checkDepSlc_isFalse()) {
		int stop = 0;
		if (1 > SIZE_IsReadOrNewSlice - index_IsReadOrNewSlice + HevcDecoder_generateInfo_MvComponentPred_IsReadOrNewSlice->read_inds[0]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_CheckIndepSlc;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		{
			int isAligned = 1;
			isAligned &= ((index_SyntaxElem % SIZE_SyntaxElem) < ((index_SyntaxElem + 2) % SIZE_SyntaxElem));
			if (isAligned) {
				checkDepSlc_isFalse_aligned();
			} else {
				checkDepSlc_isFalse();
			}
		}
		i++;
		goto l_GetTilesCoord;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_CheckIndepSlc;
		goto finished;
	}
l_CheckMergeIdx:
	if (isSchedulable_checkMergeIdx_isNotEqToMin1()) {
		checkMergeIdx_isNotEqToMin1();
		i++;
		goto l_GetMvd;
	} else if (numTokens_SyntaxElem - index_SyntaxElem >= 4 && isSchedulable_checkMergeIdx_isEqToMin1()) {
		{
			int isAligned = 1;
			isAligned &= ((index_SyntaxElem % SIZE_SyntaxElem) < ((index_SyntaxElem + 4) % SIZE_SyntaxElem));
			if (isAligned) {
				checkMergeIdx_isEqToMin1_aligned();
			} else {
				checkMergeIdx_isEqToMin1();
			}
		}
		i++;
		goto l_GetMvd;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_CheckMergeIdx;
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
	} else if (numTokens_SyntaxElem - index_SyntaxElem >= 1 && isSchedulable_getCuMode_isInter()) {
		getCuMode_isInter();
		i++;
		goto l_CheckMergeIdx;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetCuMode;
		goto finished;
	}
l_GetMvd:
	if (numTokens_SyntaxElem - index_SyntaxElem >= 4 && isSchedulable_getMvd()) {
		int stop = 0;
		if (1 > SIZE_IsBiPredOrLx - index_IsBiPredOrLx + HevcDecoder_generateInfo_MvComponentPred_IsBiPredOrLx->read_inds[0]) {
			stop = 1;
		}
		if (1 > SIZE_IsBiPredOrLx - index_IsBiPredOrLx + HevcDecoder_generateInfo_MvComponentPred_IsBiPredOrLx->read_inds[1]) {
			stop = 1;
		}
		if (1 > SIZE_IsBiPredOrLx - index_IsBiPredOrLx + HevcDecoder_generateInfo_MvComponentPred_IsBiPredOrLx->read_inds[2]) {
			stop = 1;
		}
		if (1 > SIZE_IsReadOrNewSlice - index_IsReadOrNewSlice + HevcDecoder_generateInfo_MvComponentPred_IsReadOrNewSlice->read_inds[0]) {
			stop = 1;
		}
		if (2 > SIZE_Mv - index_Mv + HevcDecoder_generateInfo_MvComponentPred_Mv->read_inds[0]) {
			stop = 1;
		}
		if (2 > SIZE_Mv - index_Mv + HevcDecoder_generateInfo_MvComponentPred_Mv->read_inds[1]) {
			stop = 1;
		}
		if (2 > SIZE_Mv - index_Mv + HevcDecoder_generateInfo_MvComponentPred_Mv->read_inds[2]) {
			stop = 1;
		}
		if (1 > SIZE_RefIdx - index_RefIdx + HevcDecoder_generateInfo_MvComponentPred_RefIdx->read_inds[0]) {
			stop = 1;
		}
		if (1 > SIZE_PocRef - index_PocRef + HevcDecoder_generateInfo_MvComponentPred_PocRef->read_inds[0]) {
			stop = 1;
		}
		if (1 > SIZE_PocRef - index_PocRef + HevcDecoder_generateInfo_MvComponentPred_PocRef->read_inds[1]) {
			stop = 1;
		}
		if (2 > SIZE_PredCuSize - index_PredCuSize + HevcDecoder_generateInfo_MvComponentPred_PredCuSize->read_inds[0]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_GetMvd;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		{
			int isAligned = 1;
			isAligned &= ((index_SyntaxElem % SIZE_SyntaxElem) < ((index_SyntaxElem + 4) % SIZE_SyntaxElem));
			isAligned &= ((index_Mv % SIZE_Mv) < ((index_Mv + 2) % SIZE_Mv));
			isAligned &= ((index_PredCuSize % SIZE_PredCuSize) < ((index_PredCuSize + 2) % SIZE_PredCuSize));
			if (isAligned) {
				getMvd_aligned();
			} else {
				getMvd();
			}
		}
		i++;
		goto l_Send2ndMv;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetMvd;
		goto finished;
	}
l_GetPartMode:
	if (numTokens_PartMode - index_PartMode >= 1 && numTokens_SliceAddr - index_SliceAddr >= 2 && numTokens_SyntaxElem - index_SyntaxElem >= 2 && isSchedulable_isNewPicOrSlice()) {
		{
			int isAligned = 1;
			isAligned &= ((index_SyntaxElem % SIZE_SyntaxElem) < ((index_SyntaxElem + 2) % SIZE_SyntaxElem));
			if (isAligned) {
				isNewPicOrSlice_aligned();
			} else {
				isNewPicOrSlice();
			}
		}
		i++;
		goto l_CheckIndepSlc;
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
l_GetRps:
	if (numTokens_RpsPoc - index_RpsPoc >= 1 && isSchedulable_getRps_launch()) {
		getRps_launch();
		i++;
		goto l_GetRpsPoc;
	} else if (isSchedulable_getRps_done()) {
		getRps_done();
		i++;
		goto l_GetSizeRefList;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetRps;
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
l_GetSizeRefList:
	if (numTokens_RefList - index_RefList >= 1 && isSchedulable_getSizeRefList_launch()) {
		getSizeRefList_launch();
		i++;
		goto l_GetRefList;
	} else if (isSchedulable_getSizeRefList_done()) {
		getSizeRefList_done();
		i++;
		goto l_GetPartMode;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetSizeRefList;
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
		goto l_GetRps;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetTilesCoord;
		goto finished;
	}
l_Send2ndMv:
	if (isSchedulable_send2ndMv_launch()) {
		int stop = 0;
		if (1 > SIZE_PocRef - index_PocRef + HevcDecoder_generateInfo_MvComponentPred_PocRef->read_inds[0]) {
			stop = 1;
		}
		if (1 > SIZE_PocRef - index_PocRef + HevcDecoder_generateInfo_MvComponentPred_PocRef->read_inds[1]) {
			stop = 1;
		}
		if (1 > SIZE_RefIdx - index_RefIdx + HevcDecoder_generateInfo_MvComponentPred_RefIdx->read_inds[0]) {
			stop = 1;
		}
		if (2 > SIZE_Mv - index_Mv + HevcDecoder_generateInfo_MvComponentPred_Mv->read_inds[0]) {
			stop = 1;
		}
		if (2 > SIZE_Mv - index_Mv + HevcDecoder_generateInfo_MvComponentPred_Mv->read_inds[1]) {
			stop = 1;
		}
		if (2 > SIZE_Mv - index_Mv + HevcDecoder_generateInfo_MvComponentPred_Mv->read_inds[2]) {
			stop = 1;
		}
		if (2 > SIZE_PredCuSize - index_PredCuSize + HevcDecoder_generateInfo_MvComponentPred_PredCuSize->read_inds[0]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_Send2ndMv;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		{
			int isAligned = 1;
			isAligned &= ((index_Mv % SIZE_Mv) < ((index_Mv + 2) % SIZE_Mv));
			isAligned &= ((index_PredCuSize % SIZE_PredCuSize) < ((index_PredCuSize + 2) % SIZE_PredCuSize));
			if (isAligned) {
				send2ndMv_launch_aligned();
			} else {
				send2ndMv_launch();
			}
		}
		i++;
		goto l_GetCuInfo;
	} else if (isSchedulable_send2ndMv_skip()) {
		send2ndMv_skip();
		i++;
		goto l_GetCuInfo;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_Send2ndMv;
		goto finished;
	}
finished:
	read_end_CUInfo();
	read_end_LcuSizeMax();
	read_end_PartMode();
	read_end_PicSize();
	read_end_Poc();
	read_end_RefList();
	read_end_RpsPoc();
	read_end_SliceAddr();
	read_end_SliceType();
	read_end_SyntaxElem();
	read_end_TilesCoord();
	write_end_IsBiPredOrLx();
	write_end_IsReadOrNewSlice();
	write_end_Mv();
	write_end_PocRef();
	write_end_PredCuSize();
	write_end_RefIdx();
}
