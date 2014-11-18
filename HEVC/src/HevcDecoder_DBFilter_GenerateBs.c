// Source file is "L/RVC/src/org/sc29/wg11/mpegh/part2/main/Filters/GenerateBs.cal"

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
extern actor_t HevcDecoder_DBFilter_GenerateBs;

////////////////////////////////////////////////////////////////////////////////
// Input FIFOs
extern fifo_i32_t *HevcDecoder_DBFilter_GenerateBs_Cbf;
extern fifo_u16_t *HevcDecoder_DBFilter_GenerateBs_CUInfo;
extern fifo_u8_t *HevcDecoder_DBFilter_GenerateBs_IsBiPredOrLx;
extern fifo_u8_t *HevcDecoder_DBFilter_GenerateBs_LcuSizeMax;
extern fifo_u8_t *HevcDecoder_DBFilter_GenerateBs_LFAcrossSlcTile;
extern fifo_i32_t *HevcDecoder_DBFilter_GenerateBs_Mv;
extern fifo_u8_t *HevcDecoder_DBFilter_GenerateBs_PartMode;
extern fifo_i16_t *HevcDecoder_DBFilter_GenerateBs_RefPoc;
extern fifo_u16_t *HevcDecoder_DBFilter_GenerateBs_SliceAddr;
extern fifo_i32_t *HevcDecoder_DBFilter_GenerateBs_SplitTransf;
extern fifo_u16_t *HevcDecoder_DBFilter_GenerateBs_TilesCoord;

////////////////////////////////////////////////////////////////////////////////
// Input Fifo control variables
static unsigned int index_Cbf;
static unsigned int numTokens_Cbf;
#define SIZE_Cbf SIZE
#define tokens_Cbf HevcDecoder_DBFilter_GenerateBs_Cbf->contents

extern connection_t connection_HevcDecoder_DBFilter_GenerateBs_Cbf;
#define rate_Cbf connection_HevcDecoder_DBFilter_GenerateBs_Cbf.rate

static unsigned int index_CUInfo;
static unsigned int numTokens_CUInfo;
#define SIZE_CUInfo SIZE
#define tokens_CUInfo HevcDecoder_DBFilter_GenerateBs_CUInfo->contents

extern connection_t connection_HevcDecoder_DBFilter_GenerateBs_CUInfo;
#define rate_CUInfo connection_HevcDecoder_DBFilter_GenerateBs_CUInfo.rate

static unsigned int index_IsBiPredOrLx;
static unsigned int numTokens_IsBiPredOrLx;
#define SIZE_IsBiPredOrLx SIZE
#define tokens_IsBiPredOrLx HevcDecoder_DBFilter_GenerateBs_IsBiPredOrLx->contents

extern connection_t connection_HevcDecoder_DBFilter_GenerateBs_IsBiPredOrLx;
#define rate_IsBiPredOrLx connection_HevcDecoder_DBFilter_GenerateBs_IsBiPredOrLx.rate

static unsigned int index_LcuSizeMax;
static unsigned int numTokens_LcuSizeMax;
#define SIZE_LcuSizeMax SIZE
#define tokens_LcuSizeMax HevcDecoder_DBFilter_GenerateBs_LcuSizeMax->contents

extern connection_t connection_HevcDecoder_DBFilter_GenerateBs_LcuSizeMax;
#define rate_LcuSizeMax connection_HevcDecoder_DBFilter_GenerateBs_LcuSizeMax.rate

static unsigned int index_LFAcrossSlcTile;
static unsigned int numTokens_LFAcrossSlcTile;
#define SIZE_LFAcrossSlcTile SIZE
#define tokens_LFAcrossSlcTile HevcDecoder_DBFilter_GenerateBs_LFAcrossSlcTile->contents

extern connection_t connection_HevcDecoder_DBFilter_GenerateBs_LFAcrossSlcTile;
#define rate_LFAcrossSlcTile connection_HevcDecoder_DBFilter_GenerateBs_LFAcrossSlcTile.rate

static unsigned int index_Mv;
static unsigned int numTokens_Mv;
#define SIZE_Mv SIZE
#define tokens_Mv HevcDecoder_DBFilter_GenerateBs_Mv->contents

extern connection_t connection_HevcDecoder_DBFilter_GenerateBs_Mv;
#define rate_Mv connection_HevcDecoder_DBFilter_GenerateBs_Mv.rate

static unsigned int index_PartMode;
static unsigned int numTokens_PartMode;
#define SIZE_PartMode SIZE
#define tokens_PartMode HevcDecoder_DBFilter_GenerateBs_PartMode->contents

extern connection_t connection_HevcDecoder_DBFilter_GenerateBs_PartMode;
#define rate_PartMode connection_HevcDecoder_DBFilter_GenerateBs_PartMode.rate

static unsigned int index_RefPoc;
static unsigned int numTokens_RefPoc;
#define SIZE_RefPoc SIZE
#define tokens_RefPoc HevcDecoder_DBFilter_GenerateBs_RefPoc->contents

extern connection_t connection_HevcDecoder_DBFilter_GenerateBs_RefPoc;
#define rate_RefPoc connection_HevcDecoder_DBFilter_GenerateBs_RefPoc.rate

static unsigned int index_SliceAddr;
static unsigned int numTokens_SliceAddr;
#define SIZE_SliceAddr SIZE
#define tokens_SliceAddr HevcDecoder_DBFilter_GenerateBs_SliceAddr->contents

extern connection_t connection_HevcDecoder_DBFilter_GenerateBs_SliceAddr;
#define rate_SliceAddr connection_HevcDecoder_DBFilter_GenerateBs_SliceAddr.rate

static unsigned int index_SplitTransf;
static unsigned int numTokens_SplitTransf;
#define SIZE_SplitTransf SIZE
#define tokens_SplitTransf HevcDecoder_DBFilter_GenerateBs_SplitTransf->contents

extern connection_t connection_HevcDecoder_DBFilter_GenerateBs_SplitTransf;
#define rate_SplitTransf connection_HevcDecoder_DBFilter_GenerateBs_SplitTransf.rate

static unsigned int index_TilesCoord;
static unsigned int numTokens_TilesCoord;
#define SIZE_TilesCoord SIZE
#define tokens_TilesCoord HevcDecoder_DBFilter_GenerateBs_TilesCoord->contents

extern connection_t connection_HevcDecoder_DBFilter_GenerateBs_TilesCoord;
#define rate_TilesCoord connection_HevcDecoder_DBFilter_GenerateBs_TilesCoord.rate

////////////////////////////////////////////////////////////////////////////////
// Predecessors
extern actor_t HevcDecoder_Algo_Parser;
extern actor_t HevcDecoder_Algo_Parser;
extern actor_t HevcDecoder_generateInfo_MvComponentPred;
extern actor_t HevcDecoder_Algo_Parser;
extern actor_t HevcDecoder_Algo_Parser;
extern actor_t HevcDecoder_generateInfo_MvComponentPred;
extern actor_t HevcDecoder_Algo_Parser;
extern actor_t HevcDecoder_generateInfo_MvComponentPred;
extern actor_t HevcDecoder_Algo_Parser;
extern actor_t HevcDecoder_Algo_Parser;
extern actor_t HevcDecoder_Algo_Parser;

////////////////////////////////////////////////////////////////////////////////
// Output FIFOs
extern fifo_u8_t *HevcDecoder_DBFilter_GenerateBs_BSHor;
extern fifo_u8_t *HevcDecoder_DBFilter_GenerateBs_BSVer;

////////////////////////////////////////////////////////////////////////////////
// Output Fifo control variables
static unsigned int index_BSHor;
static unsigned int numFree_BSHor;
#define NUM_READERS_BSHor 1
#define SIZE_BSHor SIZE
#define tokens_BSHor HevcDecoder_DBFilter_GenerateBs_BSHor->contents

static unsigned int index_BSVer;
static unsigned int numFree_BSVer;
#define NUM_READERS_BSVer 1
#define SIZE_BSVer SIZE
#define tokens_BSVer HevcDecoder_DBFilter_GenerateBs_BSVer->contents

////////////////////////////////////////////////////////////////////////////////
// Successors
extern actor_t HevcDecoder_DBFilter_DeblockFilt;
extern actor_t HevcDecoder_DBFilter_DeblockFilt;


////////////////////////////////////////////////////////////////////////////////
// State variables of the actor
#define HevcDecoder_DBFilter_GenerateBs_PICT_WIDTH_POW_2 4096
static const u8 HevcDecoder_DBFilter_GenerateBs_absCoordInBlkToZScanTable2[8][16] = {{0, 1, 2, 3, 8, 9, 10, 11, 32, 33, 34, 35, 40, 41, 42, 43}, {4, 5, 6, 7, 12, 13, 14, 15, 36, 37, 38, 39, 44, 45, 46, 47}, {16, 17, 18, 19, 24, 25, 26, 27, 48, 49, 50, 51, 56, 57, 58, 59}, {20, 21, 22, 23, 28, 29, 30, 31, 52, 53, 54, 55, 60, 61, 62, 63}, {64, 65, 66, 67, 72, 73, 74, 75, 96, 97, 98, 99, 104, 105, 106, 107}, {68, 69, 70, 71, 76, 77, 78, 79, 100, 101, 102, 103, 108, 109, 110, 111}, {80, 81, 82, 83, 88, 89, 90, 91, 112, 113, 114, 115, 120, 121, 122, 123}, {84, 85, 86, 87, 92, 93, 94, 95, 116, 117, 118, 119, 124, 125, 126, 127}};
#define HevcDecoder_DBFilter_GenerateBs_INTRA 1
static const u8 HevcDecoder_DBFilter_GenerateBs_absCoordInBlkToZScanTable3[16][8] = {{0, 2, 8, 10, 32, 34, 40, 42}, {1, 3, 9, 11, 33, 35, 41, 43}, {4, 6, 12, 14, 36, 38, 44, 46}, {5, 7, 13, 15, 37, 39, 45, 47}, {16, 18, 24, 26, 48, 50, 56, 58}, {17, 19, 25, 27, 49, 51, 57, 59}, {20, 22, 28, 30, 52, 54, 60, 62}, {21, 23, 29, 31, 53, 55, 61, 63}, {64, 66, 72, 74, 96, 98, 104, 106}, {65, 67, 73, 75, 97, 99, 105, 107}, {68, 70, 76, 78, 100, 102, 108, 110}, {69, 71, 77, 79, 101, 103, 109, 111}, {80, 82, 88, 90, 112, 114, 120, 122}, {81, 83, 89, 91, 113, 115, 121, 123}, {84, 86, 92, 94, 116, 118, 124, 126}, {85, 87, 93, 95, 117, 119, 125, 127}};
#define HevcDecoder_DBFilter_GenerateBs_PART_MODE_SLICE_INDEP 10
#define HevcDecoder_DBFilter_GenerateBs_PART_MODE_PICT 8
#define HevcDecoder_DBFilter_GenerateBs_PART_MODE_SLICE_DEP 9
#define HevcDecoder_DBFilter_GenerateBs_PART_2Nx2N 0
#define HevcDecoder_DBFilter_GenerateBs_PART_NxN 3
static const u8 HevcDecoder_DBFilter_GenerateBs_partModeToNumPart[8] = {1, 2, 2, 4, 2, 2, 2, 2};
#define HevcDecoder_DBFilter_GenerateBs_BI_PRED 2
#define HevcDecoder_DBFilter_GenerateBs_INTER 0
#define HevcDecoder_DBFilter_GenerateBs_SKIP 2
#define HevcDecoder_DBFilter_GenerateBs_OTHER 16
static const u8 HevcDecoder_DBFilter_GenerateBs_absCoordInBlkToZScanTable[16][16] = {{0, 1, 4, 5, 16, 17, 20, 21, 64, 65, 68, 69, 80, 81, 84, 85}, {2, 3, 6, 7, 18, 19, 22, 23, 66, 67, 70, 71, 82, 83, 86, 87}, {8, 9, 12, 13, 24, 25, 28, 29, 72, 73, 76, 77, 88, 89, 92, 93}, {10, 11, 14, 15, 26, 27, 30, 31, 74, 75, 78, 79, 90, 91, 94, 95}, {32, 33, 36, 37, 48, 49, 52, 53, 96, 97, 100, 101, 112, 113, 116, 117}, {34, 35, 38, 39, 50, 51, 54, 55, 98, 99, 102, 103, 114, 115, 118, 119}, {40, 41, 44, 45, 56, 57, 60, 61, 104, 105, 108, 109, 120, 121, 124, 125}, {42, 43, 46, 47, 58, 59, 62, 63, 106, 107, 110, 111, 122, 123, 126, 127}, {128, 129, 132, 133, 144, 145, 148, 149, 192, 193, 196, 197, 208, 209, 212, 213}, {130, 131, 134, 135, 146, 147, 150, 151, 194, 195, 198, 199, 210, 211, 214, 215}, {136, 137, 140, 141, 152, 153, 156, 157, 200, 201, 204, 205, 216, 217, 220, 221}, {138, 139, 142, 143, 154, 155, 158, 159, 202, 203, 206, 207, 218, 219, 222, 223}, {160, 161, 164, 165, 176, 177, 180, 181, 224, 225, 228, 229, 240, 241, 244, 245}, {162, 163, 166, 167, 178, 179, 182, 183, 226, 227, 230, 231, 242, 243, 246, 247}, {168, 169, 172, 173, 184, 185, 188, 189, 232, 233, 236, 237, 248, 249, 252, 253}, {170, 171, 174, 175, 186, 187, 190, 191, 234, 235, 238, 239, 250, 251, 254, 255}};
static u16 sliceAdr[2];
static i32 loopFilterAcrossSlc;
static i32 loopFilterAcrossTile;
static u8 lcuSizeMax;
static u8 nS;
static u16 cuAddr[2] = {-1, -1};
static u16 cuAddrNQT[2] = {-1, -1};
static u8 cuMode;
static u8 numPart;
static u8 numPartDecoded;
static i8 trafoTreeDepth;
static u8 trafoTreeIdx[6];
static i32 vertEdgeFlagVal[16] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
static i32 horEdgeFlagVal[16] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
static i16 iLoop;
static u16 numTiles;
static u16 currTileIdx;
static u16 tilesBeg[128][2];
static u16 tilesEnd[128][2];
static u8 predModeTab[1024][512];
static i32 cbfUpNeighb[1024];
static i32 cbfLeftNeighb[512];
static i32 isBiPredTab[1024][512];
static i16 refPocUpNeighb[1024][2];
static i16 refPocLeftNeighb[512][2];
static i32 mvUpNeighb[1024][2][2];
static i32 mvLeftNeighb[512][2][2];
static i16 coordMax1stPu[2];
static i16 xAddr2ndPu;
static i16 yAddr2ndPu;
static i32 isBiPred[2];
static i16 refPoc[2][2];
static i32 mv[2][2][2];
static u16 currIdx;
static u16 currIdxHor;
static u16 currIdxVer;
static i16 nbBlkToSend;
static u8 numMvInfo;
static u8 bsTable[2][128];
static u16 treeAddrInBlk[2];

////////////////////////////////////////////////////////////////////////////////
// Initial FSM state of the actor
enum states {
	my_state_GetCuInfo,
	my_state_GetCuInfoNonQT,
	my_state_GetCuMode,
	my_state_GetPartMode,
	my_state_GetRefPictInfo,
	my_state_GetRefPictInfo1,
	my_state_GetSplitTrafo,
	my_state_GetTilesCoord,
	my_state_SendBS
};

static char *stateNames[] = {
	"GetCuInfo",
	"GetCuInfoNonQT",
	"GetCuMode",
	"GetPartMode",
	"GetRefPictInfo",
	"GetRefPictInfo1",
	"GetSplitTrafo",
	"GetTilesCoord",
	"SendBS"
};

static enum states _FSM_state;



////////////////////////////////////////////////////////////////////////////////
// Token functions
static void read_Cbf() {
	index_Cbf = HevcDecoder_DBFilter_GenerateBs_Cbf->read_inds[0];
	numTokens_Cbf = index_Cbf + fifo_i32_get_num_tokens(HevcDecoder_DBFilter_GenerateBs_Cbf, 0);
}

static void read_end_Cbf() {
	HevcDecoder_DBFilter_GenerateBs_Cbf->read_inds[0] = index_Cbf;
}
static void read_CUInfo() {
	index_CUInfo = HevcDecoder_DBFilter_GenerateBs_CUInfo->read_inds[4];
	numTokens_CUInfo = index_CUInfo + fifo_u16_get_num_tokens(HevcDecoder_DBFilter_GenerateBs_CUInfo, 4);
}

static void read_end_CUInfo() {
	HevcDecoder_DBFilter_GenerateBs_CUInfo->read_inds[4] = index_CUInfo;
}
static void read_IsBiPredOrLx() {
	index_IsBiPredOrLx = HevcDecoder_DBFilter_GenerateBs_IsBiPredOrLx->read_inds[2];
	numTokens_IsBiPredOrLx = index_IsBiPredOrLx + fifo_u8_get_num_tokens(HevcDecoder_DBFilter_GenerateBs_IsBiPredOrLx, 2);
}

static void read_end_IsBiPredOrLx() {
	HevcDecoder_DBFilter_GenerateBs_IsBiPredOrLx->read_inds[2] = index_IsBiPredOrLx;
}
static void read_LcuSizeMax() {
	index_LcuSizeMax = HevcDecoder_DBFilter_GenerateBs_LcuSizeMax->read_inds[3];
	numTokens_LcuSizeMax = index_LcuSizeMax + fifo_u8_get_num_tokens(HevcDecoder_DBFilter_GenerateBs_LcuSizeMax, 3);
}

static void read_end_LcuSizeMax() {
	HevcDecoder_DBFilter_GenerateBs_LcuSizeMax->read_inds[3] = index_LcuSizeMax;
}
static void read_LFAcrossSlcTile() {
	index_LFAcrossSlcTile = HevcDecoder_DBFilter_GenerateBs_LFAcrossSlcTile->read_inds[1];
	numTokens_LFAcrossSlcTile = index_LFAcrossSlcTile + fifo_u8_get_num_tokens(HevcDecoder_DBFilter_GenerateBs_LFAcrossSlcTile, 1);
}

static void read_end_LFAcrossSlcTile() {
	HevcDecoder_DBFilter_GenerateBs_LFAcrossSlcTile->read_inds[1] = index_LFAcrossSlcTile;
}
static void read_Mv() {
	index_Mv = HevcDecoder_DBFilter_GenerateBs_Mv->read_inds[2];
	numTokens_Mv = index_Mv + fifo_i32_get_num_tokens(HevcDecoder_DBFilter_GenerateBs_Mv, 2);
}

static void read_end_Mv() {
	HevcDecoder_DBFilter_GenerateBs_Mv->read_inds[2] = index_Mv;
}
static void read_PartMode() {
	index_PartMode = HevcDecoder_DBFilter_GenerateBs_PartMode->read_inds[4];
	numTokens_PartMode = index_PartMode + fifo_u8_get_num_tokens(HevcDecoder_DBFilter_GenerateBs_PartMode, 4);
}

static void read_end_PartMode() {
	HevcDecoder_DBFilter_GenerateBs_PartMode->read_inds[4] = index_PartMode;
}
static void read_RefPoc() {
	index_RefPoc = HevcDecoder_DBFilter_GenerateBs_RefPoc->read_inds[1];
	numTokens_RefPoc = index_RefPoc + fifo_i16_get_num_tokens(HevcDecoder_DBFilter_GenerateBs_RefPoc, 1);
}

static void read_end_RefPoc() {
	HevcDecoder_DBFilter_GenerateBs_RefPoc->read_inds[1] = index_RefPoc;
}
static void read_SliceAddr() {
	index_SliceAddr = HevcDecoder_DBFilter_GenerateBs_SliceAddr->read_inds[2];
	numTokens_SliceAddr = index_SliceAddr + fifo_u16_get_num_tokens(HevcDecoder_DBFilter_GenerateBs_SliceAddr, 2);
}

static void read_end_SliceAddr() {
	HevcDecoder_DBFilter_GenerateBs_SliceAddr->read_inds[2] = index_SliceAddr;
}
static void read_SplitTransf() {
	index_SplitTransf = HevcDecoder_DBFilter_GenerateBs_SplitTransf->read_inds[1];
	numTokens_SplitTransf = index_SplitTransf + fifo_i32_get_num_tokens(HevcDecoder_DBFilter_GenerateBs_SplitTransf, 1);
}

static void read_end_SplitTransf() {
	HevcDecoder_DBFilter_GenerateBs_SplitTransf->read_inds[1] = index_SplitTransf;
}
static void read_TilesCoord() {
	index_TilesCoord = HevcDecoder_DBFilter_GenerateBs_TilesCoord->read_inds[3];
	numTokens_TilesCoord = index_TilesCoord + fifo_u16_get_num_tokens(HevcDecoder_DBFilter_GenerateBs_TilesCoord, 3);
}

static void read_end_TilesCoord() {
	HevcDecoder_DBFilter_GenerateBs_TilesCoord->read_inds[3] = index_TilesCoord;
}

static void write_BSHor() {
	index_BSHor = HevcDecoder_DBFilter_GenerateBs_BSHor->write_ind;
	numFree_BSHor = index_BSHor + fifo_u8_get_room(HevcDecoder_DBFilter_GenerateBs_BSHor, NUM_READERS_BSHor, SIZE_BSHor);
}

static void write_end_BSHor() {
	HevcDecoder_DBFilter_GenerateBs_BSHor->write_ind = index_BSHor;
}
static void write_BSVer() {
	index_BSVer = HevcDecoder_DBFilter_GenerateBs_BSVer->write_ind;
	numFree_BSVer = index_BSVer + fifo_u8_get_room(HevcDecoder_DBFilter_GenerateBs_BSVer, NUM_READERS_BSVer, SIZE_BSVer);
}

static void write_end_BSVer() {
	HevcDecoder_DBFilter_GenerateBs_BSVer->write_ind = index_BSVer;
}

////////////////////////////////////////////////////////////////////////////////
// Functions/procedures
static i32 HevcDecoder_DBFilter_GenerateBs_castBoolToInt(i32 a);
static u16 HevcDecoder_DBFilter_GenerateBs_absCoordInBlkToZScan2(u16 addr[2]);
static i32 HevcDecoder_DBFilter_GenerateBs_abs(i32 x);
static u16 HevcDecoder_DBFilter_GenerateBs_absCoordInBlkToZScan3(u16 addr[2]);
static u16 HevcDecoder_DBFilter_GenerateBs_absCoordToZScan2(u16 addr[2]);
static u16 HevcDecoder_DBFilter_GenerateBs_absCoordToZScan3(u16 addr[2]);
static i32 HevcDecoder_DBFilter_GenerateBs_max(i32 a, i32 b);
static u16 HevcDecoder_DBFilter_GenerateBs_absCoordToZScan(u16 addr[2]);
static void findCurrTile(u16 xPixAddr, u16 yPixAddr);
static void savePredInfoTu(u16 treeAddrInBlk[2], u8 treeSizeInBlk);
static void savePredPuEdge(u16 addr[2], u8 puSize[2], i32 edgeIsHoriz);
static void rstEdgeTables(u16 addr[2]);
static void processTUBoundaries(i32 cbf, u16 treeAddr[2], u8 treeNS);
static void processPUBoundary(u16 addr[2], u8 puSize[2], i32 edgeIsHoriz);
static void boundaryStrength0(u8 bS[1], i32 mvP0[2][2], i32 mvQ0[2][2]);
static void boundaryStrength1(u8 bS[1], i32 mvP0[2][2], i32 mvQ0[2][2]);
static void boundaryStrength2(u8 bS[1], i32 mvP0[2][2], i32 mvQ0[2][2]);
static void boundaryStrength3(u8 bS[1], u8 predModeP0, u8 predModeQ0, i32 mvP0[2][2], i32 mvQ0[2][2]);
static void genBoundFilterStrengthTUVert(u8 bS[1], u16 addrInBlk[2], i32 cbfQ0, u8 partIdx);
static void genBoundFilterStrengthTUHor(u8 bS[1], u16 addrInBlk[2], i32 cbfQ0, u8 partIdx);
static void genBoundFilterStrengthCorePU(u8 bS[1], u16 addrInBlk[2], i32 isVerticalEdge, i32 mvP0[2][2], i32 mvQ0[2][2], i16 refPocP0[2], i16 refPocQ0[2]);

static i32 HevcDecoder_DBFilter_GenerateBs_castBoolToInt(i32 a) {
	u8 tmp_if;

	if (a) {
		tmp_if = 1;
	} else {
		tmp_if = 0;
	}
	return tmp_if;
}
static u16 HevcDecoder_DBFilter_GenerateBs_absCoordInBlkToZScan2(u16 addr[2]) {
	u16 tmp_addr;
	u16 tmp_addr0;
	u8 tmp_absCoordInBlkToZScanTable2;

	tmp_addr = addr[1];
	tmp_addr0 = addr[0];
	tmp_absCoordInBlkToZScanTable2 = HevcDecoder_DBFilter_GenerateBs_absCoordInBlkToZScanTable2[tmp_addr][tmp_addr0];
	return tmp_absCoordInBlkToZScanTable2;
}
static i32 HevcDecoder_DBFilter_GenerateBs_abs(i32 x) {
	i32 tmp_if;

	if (x > 0) {
		tmp_if = x;
	} else {
		tmp_if = -x;
	}
	return tmp_if;
}
static u16 HevcDecoder_DBFilter_GenerateBs_absCoordInBlkToZScan3(u16 addr[2]) {
	u16 tmp_addr;
	u16 tmp_addr0;
	u8 tmp_absCoordInBlkToZScanTable3;

	tmp_addr = addr[1];
	tmp_addr0 = addr[0];
	tmp_absCoordInBlkToZScanTable3 = HevcDecoder_DBFilter_GenerateBs_absCoordInBlkToZScanTable3[tmp_addr][tmp_addr0];
	return tmp_absCoordInBlkToZScanTable3;
}
static u16 HevcDecoder_DBFilter_GenerateBs_absCoordToZScan2(u16 addr[2]) {
	u16 tmp_addr;
	u16 tmp_addr0;
	u16 addrBlk[2];
	u16 tmp_addrBlk;
	u16 tmp_addrBlk0;
	u8 tmp_absCoordInBlkToZScanTable2;

	tmp_addr = addr[0];
	addrBlk[0] = tmp_addr >> 2;
	tmp_addr0 = addr[1];
	addrBlk[1] = tmp_addr0 >> 3;
	tmp_addrBlk = addrBlk[1];
	tmp_addrBlk0 = addrBlk[0];
	tmp_absCoordInBlkToZScanTable2 = HevcDecoder_DBFilter_GenerateBs_absCoordInBlkToZScanTable2[tmp_addrBlk][tmp_addrBlk0];
	return tmp_absCoordInBlkToZScanTable2;
}
static u16 HevcDecoder_DBFilter_GenerateBs_absCoordToZScan3(u16 addr[2]) {
	u16 tmp_addr;
	u16 tmp_addr0;
	u16 addrBlk[2];
	u16 tmp_addrBlk;
	u16 tmp_addrBlk0;
	u8 tmp_absCoordInBlkToZScanTable3;

	tmp_addr = addr[0];
	addrBlk[0] = tmp_addr >> 3;
	tmp_addr0 = addr[1];
	addrBlk[1] = tmp_addr0 >> 2;
	tmp_addrBlk = addrBlk[1];
	tmp_addrBlk0 = addrBlk[0];
	tmp_absCoordInBlkToZScanTable3 = HevcDecoder_DBFilter_GenerateBs_absCoordInBlkToZScanTable3[tmp_addrBlk][tmp_addrBlk0];
	return tmp_absCoordInBlkToZScanTable3;
}
static i32 HevcDecoder_DBFilter_GenerateBs_max(i32 a, i32 b) {
	i32 tmp_if;

	if (a > b) {
		tmp_if = a;
	} else {
		tmp_if = b;
	}
	return tmp_if;
}
static u16 HevcDecoder_DBFilter_GenerateBs_absCoordToZScan(u16 addr[2]) {
	u16 tmp_addr;
	u16 tmp_addr0;
	u16 addrBlk[2];
	u16 tmp_addrBlk;
	u16 tmp_addrBlk0;
	u8 tmp_absCoordInBlkToZScanTable;

	tmp_addr = addr[0];
	addrBlk[0] = tmp_addr >> 2;
	tmp_addr0 = addr[1];
	addrBlk[1] = tmp_addr0 >> 2;
	tmp_addrBlk = addrBlk[1];
	tmp_addrBlk0 = addrBlk[0];
	tmp_absCoordInBlkToZScanTable = HevcDecoder_DBFilter_GenerateBs_absCoordInBlkToZScanTable[tmp_addrBlk][tmp_addrBlk0];
	return tmp_absCoordInBlkToZScanTable;
}
static void findCurrTile(u16 xPixAddr, u16 yPixAddr) {
	i32 tileIdx;
	u16 local_numTiles;
	u16 tmp_tilesBeg;
	u16 tmp_tilesEnd;
	u16 tmp_tilesBeg0;
	u16 tmp_tilesEnd0;

	tileIdx = 0;
	local_numTiles = numTiles;
	while (tileIdx <= local_numTiles - 1) {
		tmp_tilesBeg = tilesBeg[tileIdx][0];
		tmp_tilesEnd = tilesEnd[tileIdx][0];
		if (xPixAddr >= tmp_tilesBeg && xPixAddr < tmp_tilesEnd) {
			tmp_tilesBeg0 = tilesBeg[tileIdx][1];
			tmp_tilesEnd0 = tilesEnd[tileIdx][1];
			if (yPixAddr >= tmp_tilesBeg0 && yPixAddr < tmp_tilesEnd0) {
				currTileIdx = tileIdx;
			}
		}
		tileIdx = tileIdx + 1;
	}
}
static void savePredInfoTu(u16 treeAddrInBlk[2], u8 treeSizeInBlk) {
	u16 tmp_treeAddrInBlk;
	i32 local_PICT_WIDTH_POW_2;
	u16 xMin;
	u16 tmp_treeAddrInBlk0;
	u16 xMax;
	u16 yMin;
	u16 tmp_treeAddrInBlk1;
	u16 yMax;
	u8 partIdx;
	u8 local_numMvInfo;
	u32 x;
	u8 local_cuMode;
	i32 tmp_isBiPred;
	i32 tmp_isBiPred0;
	u32 y;
	i32 tmp_isBiPred1;
	i32 tmp_isBiPred2;
	u32 x0;
	i16 local_xAddr2ndPu;
	i16 local_yAddr2ndPu;
	i32 tmp_isBiPred3;
	i32 tmp_isBiPred4;
	u32 y0;
	i32 tmp_isBiPred5;
	i32 tmp_isBiPred6;

	tmp_treeAddrInBlk = treeAddrInBlk[0];
	local_PICT_WIDTH_POW_2 = HevcDecoder_DBFilter_GenerateBs_PICT_WIDTH_POW_2;
	xMin = tmp_treeAddrInBlk & local_PICT_WIDTH_POW_2 / 4 - 1;
	tmp_treeAddrInBlk0 = treeAddrInBlk[0];
	local_PICT_WIDTH_POW_2 = HevcDecoder_DBFilter_GenerateBs_PICT_WIDTH_POW_2;
	xMax = tmp_treeAddrInBlk0 + treeSizeInBlk & local_PICT_WIDTH_POW_2 / 4 - 1;
	yMin = treeAddrInBlk[1];
	tmp_treeAddrInBlk1 = treeAddrInBlk[1];
	yMax = tmp_treeAddrInBlk1 + treeSizeInBlk;
	local_numMvInfo = numMvInfo;
	if (local_numMvInfo != 2) {
		x = xMin;
		while (x <= xMax - 1) {
			local_cuMode = cuMode;
			predModeTab[x][yMin] = local_cuMode;
			tmp_isBiPred = isBiPred[0];
			isBiPredTab[x][yMin] = tmp_isBiPred;
			local_cuMode = cuMode;
			predModeTab[x][yMax - 1] = local_cuMode;
			tmp_isBiPred0 = isBiPred[0];
			isBiPredTab[x][yMax - 1] = tmp_isBiPred0;
			x = x + 1;
		}
		y = yMin;
		while (y <= yMax - 1) {
			local_cuMode = cuMode;
			predModeTab[xMin][y] = local_cuMode;
			tmp_isBiPred1 = isBiPred[0];
			isBiPredTab[xMin][y] = tmp_isBiPred1;
			local_cuMode = cuMode;
			predModeTab[xMax - 1][y] = local_cuMode;
			tmp_isBiPred2 = isBiPred[0];
			isBiPredTab[xMax - 1][y] = tmp_isBiPred2;
			y = y + 1;
		}
	} else {
		x0 = xMin;
		while (x0 <= xMax - 1) {
			local_xAddr2ndPu = xAddr2ndPu;
			local_yAddr2ndPu = yAddr2ndPu;
			partIdx = HevcDecoder_DBFilter_GenerateBs_castBoolToInt(x0 >= local_xAddr2ndPu || yMin >= local_yAddr2ndPu);
			local_cuMode = cuMode;
			predModeTab[x0][yMin] = local_cuMode;
			tmp_isBiPred3 = isBiPred[partIdx];
			isBiPredTab[x0][yMin] = tmp_isBiPred3;
			local_xAddr2ndPu = xAddr2ndPu;
			local_yAddr2ndPu = yAddr2ndPu;
			partIdx = HevcDecoder_DBFilter_GenerateBs_castBoolToInt(x0 >= local_xAddr2ndPu || yMax - 1 >= local_yAddr2ndPu);
			local_cuMode = cuMode;
			predModeTab[x0][yMax - 1] = local_cuMode;
			tmp_isBiPred4 = isBiPred[partIdx];
			isBiPredTab[x0][yMax - 1] = tmp_isBiPred4;
			x0 = x0 + 1;
		}
		y0 = yMin;
		while (y0 <= yMax - 1) {
			local_xAddr2ndPu = xAddr2ndPu;
			local_yAddr2ndPu = yAddr2ndPu;
			partIdx = HevcDecoder_DBFilter_GenerateBs_castBoolToInt(xMin >= local_xAddr2ndPu || y0 >= local_yAddr2ndPu);
			local_cuMode = cuMode;
			predModeTab[xMin][y0] = local_cuMode;
			tmp_isBiPred5 = isBiPred[partIdx];
			isBiPredTab[xMin][y0] = tmp_isBiPred5;
			local_xAddr2ndPu = xAddr2ndPu;
			local_yAddr2ndPu = yAddr2ndPu;
			partIdx = HevcDecoder_DBFilter_GenerateBs_castBoolToInt(xMax - 1 >= local_xAddr2ndPu || y0 >= local_yAddr2ndPu);
			local_cuMode = cuMode;
			predModeTab[xMax - 1][y0] = local_cuMode;
			tmp_isBiPred6 = isBiPred[partIdx];
			isBiPredTab[xMax - 1][y0] = tmp_isBiPred6;
			y0 = y0 + 1;
		}
	}
}
static void savePredPuEdge(u16 addr[2], u8 puSize[2], i32 edgeIsHoriz) {
	u16 tmp_addr;
	i32 local_PICT_WIDTH_POW_2;
	u16 xMin;
	u16 tmp_addr0;
	u8 tmp_puSize;
	u16 xMax;
	u16 tmp_addr1;
	u16 yMin;
	u16 tmp_addr2;
	u8 tmp_puSize0;
	u16 yMax;
	u32 x;
	u8 local_cuMode;
	i32 tmp_isBiPred;
	i32 tmp_isBiPred0;
	u32 y;
	i32 tmp_isBiPred1;
	i32 tmp_isBiPred2;

	tmp_addr = addr[0];
	local_PICT_WIDTH_POW_2 = HevcDecoder_DBFilter_GenerateBs_PICT_WIDTH_POW_2;
	xMin = tmp_addr >> 2 & local_PICT_WIDTH_POW_2 / 4 - 1;
	tmp_addr0 = addr[0];
	tmp_puSize = puSize[0];
	local_PICT_WIDTH_POW_2 = HevcDecoder_DBFilter_GenerateBs_PICT_WIDTH_POW_2;
	xMax = (tmp_addr0 + tmp_puSize) / 4 & local_PICT_WIDTH_POW_2 / 4 - 1;
	tmp_addr1 = addr[1];
	yMin = tmp_addr1 / 4;
	tmp_addr2 = addr[1];
	tmp_puSize0 = puSize[1];
	yMax = (tmp_addr2 + tmp_puSize0) / 4;
	if (edgeIsHoriz) {
		x = xMin;
		while (x <= xMax - 1) {
			local_cuMode = cuMode;
			predModeTab[x][yMax - 1] = local_cuMode;
			tmp_isBiPred = isBiPred[0];
			isBiPredTab[x][yMax - 1] = tmp_isBiPred;
			local_cuMode = cuMode;
			predModeTab[x][yMax] = local_cuMode;
			tmp_isBiPred0 = isBiPred[1];
			isBiPredTab[x][yMax] = tmp_isBiPred0;
			x = x + 1;
		}
	} else {
		y = yMin;
		while (y <= yMax - 1) {
			local_cuMode = cuMode;
			predModeTab[xMax - 1][y] = local_cuMode;
			tmp_isBiPred1 = isBiPred[0];
			isBiPredTab[xMax - 1][y] = tmp_isBiPred1;
			local_cuMode = cuMode;
			predModeTab[xMax][y] = local_cuMode;
			tmp_isBiPred2 = isBiPred[1];
			isBiPredTab[xMax][y] = tmp_isBiPred2;
			y = y + 1;
		}
	}
}
static void rstEdgeTables(u16 addr[2]) {
	u16 tmp_addr;
	u16 tmp_addr0;
	u16 tmp_addr1;
	i32 local_loopFilterAcrossSlc;
	u16 tmp_sliceAdr;
	u16 tmp_addr2;
	u16 tmp_sliceAdr0;
	u16 tmp_addr3;
	i32 local_loopFilterAcrossTile;
	u16 tmp_addr4;
	u16 local_currTileIdx;
	u16 tmp_tilesBeg;
	u16 tmp_addr5;
	u16 tmp_sliceAdr1;
	u16 tmp_addr6;
	u16 tmp_sliceAdr2;
	u8 local_lcuSizeMax;
	u16 tmp_addr7;
	u16 tmp_addr8;
	u16 tmp_sliceAdr3;
	u16 tmp_addr9;
	u16 tmp_tilesBeg0;

	tmp_addr = addr[0];
	vertEdgeFlagVal[0] = tmp_addr != 0;
	tmp_addr0 = addr[1];
	horEdgeFlagVal[0] = tmp_addr0 != 0;
	tmp_addr1 = addr[0];
	local_loopFilterAcrossSlc = loopFilterAcrossSlc;
	tmp_sliceAdr = sliceAdr[0];
	tmp_addr2 = addr[0];
	tmp_sliceAdr0 = sliceAdr[1];
	tmp_addr3 = addr[1];
	local_loopFilterAcrossTile = loopFilterAcrossTile;
	tmp_addr4 = addr[0];
	local_currTileIdx = currTileIdx;
	tmp_tilesBeg = tilesBeg[local_currTileIdx][0];
	vertEdgeFlagVal[0] = !(tmp_addr1 == 0 || !local_loopFilterAcrossSlc && tmp_sliceAdr == tmp_addr2 && tmp_sliceAdr0 == tmp_addr3 || !local_loopFilterAcrossTile && tmp_addr4 == tmp_tilesBeg);
	tmp_addr5 = addr[1];
	if (tmp_addr5 == 0) {
		horEdgeFlagVal[0] = 0;
	} else {
		local_loopFilterAcrossSlc = loopFilterAcrossSlc;
		tmp_sliceAdr1 = sliceAdr[1];
		tmp_addr6 = addr[1];
		tmp_sliceAdr2 = sliceAdr[1];
		local_lcuSizeMax = lcuSizeMax;
		tmp_addr7 = addr[1];
		tmp_addr8 = addr[0];
		tmp_sliceAdr3 = sliceAdr[0];
		if (!local_loopFilterAcrossSlc && (tmp_sliceAdr1 == tmp_addr6 || tmp_sliceAdr2 + local_lcuSizeMax == tmp_addr7 && tmp_addr8 < tmp_sliceAdr3)) {
			horEdgeFlagVal[0] = 0;
		} else {
			local_loopFilterAcrossTile = loopFilterAcrossTile;
			tmp_addr9 = addr[1];
			local_currTileIdx = currTileIdx;
			tmp_tilesBeg0 = tilesBeg[local_currTileIdx][1];
			if (!local_loopFilterAcrossTile && tmp_addr9 == tmp_tilesBeg0) {
				horEdgeFlagVal[0] = 0;
			} else {
				horEdgeFlagVal[0] = 1;
			}
		}
	}
}
static void processTUBoundaries(i32 cbf, u16 treeAddr[2], u8 treeNS) {
	u16 xMin;
	u16 xMax;
	u16 yMin;
	u16 yMax;
	u8 bS[1];
	u16 addrBlk[2];
	u16 addrTUInBlk[2];
	u16 rasterIdx;
	u8 partIdx;
	u16 tmp_treeAddr;
	u8 local_lcuSizeMax;
	u16 tmp_treeAddr0;
	i32 tmp_horEdgeFlagVal;
	i32 i;
	u16 tmp_treeAddr1;
	u16 tmp_treeAddr2;
	u16 tmp_cuAddr;
	u16 tmp_treeAddr3;
	u16 tmp_cuAddr0;
	u16 tmp_addrBlk;
	i32 x;
	i16 tmp_coordMax1stPu;
	i16 tmp_coordMax1stPu0;
	u8 tmp_bS;
	u16 tmp_addrBlk0;
	u16 tmp_addrTUInBlk;
	i32 tmp_vertEdgeFlagVal;
	i32 i0;
	u16 tmp_treeAddr4;
	u16 tmp_treeAddr5;
	u16 tmp_cuAddr1;
	u16 tmp_treeAddr6;
	u16 tmp_cuAddr2;
	u16 tmp_addrBlk1;
	i32 y;
	i16 tmp_coordMax1stPu1;
	i16 tmp_coordMax1stPu2;
	u8 tmp_bS0;
	u16 tmp_addrBlk2;
	u16 tmp_addrTUInBlk0;

	tmp_treeAddr = treeAddr[0];
	local_lcuSizeMax = lcuSizeMax;
	xMin = (tmp_treeAddr & local_lcuSizeMax - 1) >> 2;
	xMax = xMin + (treeNS >> 2);
	tmp_treeAddr0 = treeAddr[1];
	local_lcuSizeMax = lcuSizeMax;
	yMin = (tmp_treeAddr0 & local_lcuSizeMax - 1) >> 2;
	yMax = yMin + (treeNS >> 2);
	tmp_horEdgeFlagVal = horEdgeFlagVal[yMin];
	if (tmp_horEdgeFlagVal) {
		i = 0;
		while (i <= 1) {
			tmp_treeAddr1 = treeAddr[i];
			addrBlk[i] = tmp_treeAddr1 >> 2;
			i = i + 1;
		}
		tmp_treeAddr2 = treeAddr[0];
		tmp_cuAddr = cuAddr[0];
		addrTUInBlk[0] = (tmp_treeAddr2 - tmp_cuAddr) >> 2;
		tmp_treeAddr3 = treeAddr[1];
		tmp_cuAddr0 = cuAddr[1];
		addrTUInBlk[1] = (tmp_treeAddr3 - tmp_cuAddr0) >> 3;
		tmp_addrBlk = addrBlk[1];
		if ((tmp_addrBlk & 1) != 1) {
			x = xMin;
			while (x <= xMax - 1) {
				rasterIdx = HevcDecoder_DBFilter_GenerateBs_absCoordInBlkToZScan2(addrTUInBlk);
				tmp_coordMax1stPu = coordMax1stPu[0];
				tmp_coordMax1stPu0 = coordMax1stPu[1];
				partIdx = HevcDecoder_DBFilter_GenerateBs_castBoolToInt(!(x < tmp_coordMax1stPu && yMin < tmp_coordMax1stPu0));
				genBoundFilterStrengthTUHor(bS, addrBlk, cbf, partIdx);
				tmp_bS = bS[0];
				bsTable[1][rasterIdx] = tmp_bS;
				tmp_addrBlk0 = addrBlk[0];
				addrBlk[0] = tmp_addrBlk0 + 1;
				tmp_addrTUInBlk = addrTUInBlk[0];
				addrTUInBlk[0] = tmp_addrTUInBlk + 1;
				x = x + 1;
			}
		}
	}
	tmp_vertEdgeFlagVal = vertEdgeFlagVal[xMin];
	if (tmp_vertEdgeFlagVal) {
		i0 = 0;
		while (i0 <= 1) {
			tmp_treeAddr4 = treeAddr[i0];
			addrBlk[i0] = tmp_treeAddr4 >> 2;
			i0 = i0 + 1;
		}
		tmp_treeAddr5 = treeAddr[0];
		tmp_cuAddr1 = cuAddr[0];
		addrTUInBlk[0] = (tmp_treeAddr5 - tmp_cuAddr1) >> 3;
		tmp_treeAddr6 = treeAddr[1];
		tmp_cuAddr2 = cuAddr[1];
		addrTUInBlk[1] = (tmp_treeAddr6 - tmp_cuAddr2) >> 2;
		tmp_addrBlk1 = addrBlk[0];
		if ((tmp_addrBlk1 & 1) != 1) {
			y = yMin;
			while (y <= yMax - 1) {
				rasterIdx = HevcDecoder_DBFilter_GenerateBs_absCoordInBlkToZScan3(addrTUInBlk);
				tmp_coordMax1stPu1 = coordMax1stPu[0];
				tmp_coordMax1stPu2 = coordMax1stPu[1];
				partIdx = HevcDecoder_DBFilter_GenerateBs_castBoolToInt(!(xMin < tmp_coordMax1stPu1 && y < tmp_coordMax1stPu2));
				genBoundFilterStrengthTUVert(bS, addrBlk, cbf, partIdx);
				tmp_bS0 = bS[0];
				bsTable[0][rasterIdx] = tmp_bS0;
				tmp_addrBlk2 = addrBlk[1];
				addrBlk[1] = tmp_addrBlk2 + 1;
				tmp_addrTUInBlk0 = addrTUInBlk[1];
				addrTUInBlk[1] = tmp_addrTUInBlk0 + 1;
				y = y + 1;
			}
		}
	}
}
static void processPUBoundary(u16 addr[2], u8 puSize[2], i32 edgeIsHoriz) {
	u16 tmp_addr;
	u8 local_lcuSizeMax;
	i32 xMin;
	u8 tmp_puSize;
	i32 xMax;
	u16 tmp_addr0;
	i32 yMin;
	u8 tmp_puSize0;
	i32 yMax;
	u8 bS[1];
	u16 addrBlk[2];
	u16 addrTU[2];
	u16 rasterIdx;
	i32 i;
	i32 j;
	i32 tmp_mv;
	i32 mvQ0Pu1[2][2];
	i32 i0;
	i32 j0;
	i32 tmp_mv0;
	i32 mvQ0Pu2[2][2];
	i32 i1;
	i16 tmp_refPoc;
	i16 refPocQ0Pu1[2];
	i32 i2;
	i16 tmp_refPoc0;
	i16 refPocQ0Pu2[2];
	i32 i3;
	u16 tmp_addr1;
	i32 tmp_horEdgeFlagVal;
	u16 tmp_addrBlk;
	u16 tmp_addr2;
	u16 tmp_cuAddr;
	u16 tmp_addr3;
	u16 tmp_cuAddr0;
	i32 x;
	u8 tmp_bS;
	u16 tmp_addrBlk0;
	u16 tmp_addrTU;
	i32 tmp_vertEdgeFlagVal;
	u16 tmp_addrBlk1;
	u16 tmp_addr4;
	u16 tmp_cuAddr1;
	u16 tmp_addr5;
	u16 tmp_cuAddr2;
	i32 y;
	u8 tmp_bS0;
	u16 tmp_addrBlk2;
	u16 tmp_addrTU0;

	tmp_addr = addr[0];
	local_lcuSizeMax = lcuSizeMax;
	xMin = (tmp_addr & local_lcuSizeMax - 1) >> 2;
	tmp_puSize = puSize[0];
	xMax = xMin + (tmp_puSize >> 2);
	tmp_addr0 = addr[1];
	local_lcuSizeMax = lcuSizeMax;
	yMin = (tmp_addr0 & local_lcuSizeMax - 1) >> 2;
	tmp_puSize0 = puSize[1];
	yMax = yMin + (tmp_puSize0 >> 2);
	i = 0;
	while (i <= 1) {
		j = 0;
		while (j <= 1) {
			tmp_mv = mv[0][i][j];
			mvQ0Pu1[i][j] = tmp_mv;
			j = j + 1;
		}
		i = i + 1;
	}
	i0 = 0;
	while (i0 <= 1) {
		j0 = 0;
		while (j0 <= 1) {
			tmp_mv0 = mv[1][i0][j0];
			mvQ0Pu2[i0][j0] = tmp_mv0;
			j0 = j0 + 1;
		}
		i0 = i0 + 1;
	}
	i1 = 0;
	while (i1 <= 1) {
		tmp_refPoc = refPoc[0][i1];
		refPocQ0Pu1[i1] = tmp_refPoc;
		i1 = i1 + 1;
	}
	i2 = 0;
	while (i2 <= 1) {
		tmp_refPoc0 = refPoc[1][i2];
		refPocQ0Pu2[i2] = tmp_refPoc0;
		i2 = i2 + 1;
	}
	i3 = 0;
	while (i3 <= 1) {
		tmp_addr1 = addr[i3];
		addrBlk[i3] = tmp_addr1 >> 2;
		i3 = i3 + 1;
	}
	if (edgeIsHoriz) {
		tmp_horEdgeFlagVal = horEdgeFlagVal[yMin];
		if (tmp_horEdgeFlagVal) {
			tmp_addrBlk = addrBlk[1];
			if ((tmp_addrBlk & 1) != 1) {
				tmp_addr2 = addr[0];
				tmp_cuAddr = cuAddr[0];
				addrTU[0] = tmp_addr2 - tmp_cuAddr;
				tmp_addr3 = addr[1];
				tmp_cuAddr0 = cuAddr[1];
				addrTU[1] = tmp_addr3 - tmp_cuAddr0;
				x = xMin;
				while (x <= xMax - 1) {
					rasterIdx = HevcDecoder_DBFilter_GenerateBs_absCoordToZScan2(addrTU);
					genBoundFilterStrengthCorePU(bS, addrBlk, 0, mvQ0Pu1, mvQ0Pu2, refPocQ0Pu1, refPocQ0Pu2);
					tmp_bS = bS[0];
					bsTable[1][rasterIdx] = tmp_bS;
					tmp_addrBlk0 = addrBlk[0];
					addrBlk[0] = tmp_addrBlk0 + 1;
					tmp_addrTU = addrTU[0];
					addrTU[0] = tmp_addrTU + 4;
					x = x + 1;
				}
			}
		}
	} else {
		tmp_vertEdgeFlagVal = vertEdgeFlagVal[xMin];
		if (tmp_vertEdgeFlagVal) {
			tmp_addrBlk1 = addrBlk[0];
			if ((tmp_addrBlk1 & 1) != 1) {
				tmp_addr4 = addr[0];
				tmp_cuAddr1 = cuAddr[0];
				addrTU[0] = tmp_addr4 - tmp_cuAddr1;
				tmp_addr5 = addr[1];
				tmp_cuAddr2 = cuAddr[1];
				addrTU[1] = tmp_addr5 - tmp_cuAddr2;
				y = yMin;
				while (y <= yMax - 1) {
					rasterIdx = HevcDecoder_DBFilter_GenerateBs_absCoordToZScan3(addrTU);
					genBoundFilterStrengthCorePU(bS, addrBlk, 1, mvQ0Pu1, mvQ0Pu2, refPocQ0Pu1, refPocQ0Pu2);
					tmp_bS0 = bS[0];
					bsTable[0][rasterIdx] = tmp_bS0;
					tmp_addrBlk2 = addrBlk[1];
					addrBlk[1] = tmp_addrBlk2 + 1;
					tmp_addrTU0 = addrTU[1];
					addrTU[1] = tmp_addrTU0 + 4;
					y = y + 1;
				}
			}
		}
	}
}
static void boundaryStrength0(u8 bS[1], i32 mvP0[2][2], i32 mvQ0[2][2]) {
	#if defined(SSE_ENABLE) && HAVE_SSE4
	boundaryStrength0_mv32_orcc(bS, mvP0, mvQ0);
	#else
	i32 tmp_mvP0;
	i32 tmp_mvQ0;
	i32 tmp_abs;
	i32 tmp_mvP00;
	i32 tmp_mvQ00;
	i32 tmp_abs0;
	i32 tmp_mvP01;
	i32 tmp_mvQ01;
	i32 tmp_abs1;
	i32 tmp_mvP02;
	i32 tmp_mvQ02;
	i32 tmp_abs2;
	i32 tmp_mvP03;
	i32 tmp_mvQ03;
	i32 tmp_abs3;
	i32 tmp_mvP04;
	i32 tmp_mvQ04;
	i32 tmp_abs4;
	i32 tmp_mvP05;
	i32 tmp_mvQ05;
	i32 tmp_abs5;
	i32 tmp_mvP06;
	i32 tmp_mvQ06;
	i32 tmp_abs6;

	tmp_mvP0 = mvP0[0][0];
	tmp_mvQ0 = mvQ0[0][0];
	tmp_abs = HevcDecoder_DBFilter_GenerateBs_abs(tmp_mvP0 - tmp_mvQ0);
	tmp_mvP00 = mvP0[0][1];
	tmp_mvQ00 = mvQ0[0][1];
	tmp_abs0 = HevcDecoder_DBFilter_GenerateBs_abs(tmp_mvP00 - tmp_mvQ00);
	tmp_mvP01 = mvP0[1][0];
	tmp_mvQ01 = mvQ0[1][0];
	tmp_abs1 = HevcDecoder_DBFilter_GenerateBs_abs(tmp_mvP01 - tmp_mvQ01);
	tmp_mvP02 = mvP0[1][1];
	tmp_mvQ02 = mvQ0[1][1];
	tmp_abs2 = HevcDecoder_DBFilter_GenerateBs_abs(tmp_mvP02 - tmp_mvQ02);
	tmp_mvP03 = mvP0[1][0];
	tmp_mvQ03 = mvQ0[0][0];
	tmp_abs3 = HevcDecoder_DBFilter_GenerateBs_abs(tmp_mvP03 - tmp_mvQ03);
	tmp_mvP04 = mvP0[1][1];
	tmp_mvQ04 = mvQ0[0][1];
	tmp_abs4 = HevcDecoder_DBFilter_GenerateBs_abs(tmp_mvP04 - tmp_mvQ04);
	tmp_mvP05 = mvP0[0][0];
	tmp_mvQ05 = mvQ0[1][0];
	tmp_abs5 = HevcDecoder_DBFilter_GenerateBs_abs(tmp_mvP05 - tmp_mvQ05);
	tmp_mvP06 = mvP0[0][1];
	tmp_mvQ06 = mvQ0[1][1];
	tmp_abs6 = HevcDecoder_DBFilter_GenerateBs_abs(tmp_mvP06 - tmp_mvQ06);
	if ((tmp_abs >= 4 || tmp_abs0 >= 4 || tmp_abs1 >= 4 || tmp_abs2 >= 4) && (tmp_abs3 >= 4 || tmp_abs4 >= 4 || tmp_abs5 >= 4 || tmp_abs6 >= 4)) {
		bS[0] = 1;
	} else {
		bS[0] = 0;
	}
	#endif // defined(SSE_ENABLE) && HAVE_SSE4
}
static void boundaryStrength1(u8 bS[1], i32 mvP0[2][2], i32 mvQ0[2][2]) {
	#if defined(SSE_ENABLE) && HAVE_SSE4
	boundaryStrength1_mv32_orcc(bS, mvP0, mvQ0);
	#else
	i32 tmp_mvP0;
	i32 tmp_mvQ0;
	i32 tmp_abs;
	i32 tmp_mvP00;
	i32 tmp_mvQ00;
	i32 tmp_abs0;
	i32 tmp_mvP01;
	i32 tmp_mvQ01;
	i32 tmp_abs1;
	i32 tmp_mvP02;
	i32 tmp_mvQ02;
	i32 tmp_abs2;

	tmp_mvP0 = mvP0[0][0];
	tmp_mvQ0 = mvQ0[0][0];
	tmp_abs = HevcDecoder_DBFilter_GenerateBs_abs(tmp_mvP0 - tmp_mvQ0);
	tmp_mvP00 = mvP0[0][1];
	tmp_mvQ00 = mvQ0[0][1];
	tmp_abs0 = HevcDecoder_DBFilter_GenerateBs_abs(tmp_mvP00 - tmp_mvQ00);
	tmp_mvP01 = mvP0[1][0];
	tmp_mvQ01 = mvQ0[1][0];
	tmp_abs1 = HevcDecoder_DBFilter_GenerateBs_abs(tmp_mvP01 - tmp_mvQ01);
	tmp_mvP02 = mvP0[1][1];
	tmp_mvQ02 = mvQ0[1][1];
	tmp_abs2 = HevcDecoder_DBFilter_GenerateBs_abs(tmp_mvP02 - tmp_mvQ02);
	if (tmp_abs >= 4 || tmp_abs0 >= 4 || tmp_abs1 >= 4 || tmp_abs2 >= 4) {
		bS[0] = 1;
	} else {
		bS[0] = 0;
	}
	#endif // defined(SSE_ENABLE) && HAVE_SSE4
}
static void boundaryStrength2(u8 bS[1], i32 mvP0[2][2], i32 mvQ0[2][2]) {
	#if defined(SSE_ENABLE) && HAVE_SSE4
	boundaryStrength2_mv32_orcc(bS, mvP0, mvQ0);
	#else
	i32 tmp_mvP0;
	i32 tmp_mvQ0;
	i32 tmp_abs;
	i32 tmp_mvP00;
	i32 tmp_mvQ00;
	i32 tmp_abs0;
	i32 tmp_mvP01;
	i32 tmp_mvQ01;
	i32 tmp_abs1;
	i32 tmp_mvP02;
	i32 tmp_mvQ02;
	i32 tmp_abs2;

	tmp_mvP0 = mvP0[1][0];
	tmp_mvQ0 = mvQ0[0][0];
	tmp_abs = HevcDecoder_DBFilter_GenerateBs_abs(tmp_mvP0 - tmp_mvQ0);
	tmp_mvP00 = mvP0[1][1];
	tmp_mvQ00 = mvQ0[0][1];
	tmp_abs0 = HevcDecoder_DBFilter_GenerateBs_abs(tmp_mvP00 - tmp_mvQ00);
	tmp_mvP01 = mvP0[0][0];
	tmp_mvQ01 = mvQ0[1][0];
	tmp_abs1 = HevcDecoder_DBFilter_GenerateBs_abs(tmp_mvP01 - tmp_mvQ01);
	tmp_mvP02 = mvP0[0][1];
	tmp_mvQ02 = mvQ0[1][1];
	tmp_abs2 = HevcDecoder_DBFilter_GenerateBs_abs(tmp_mvP02 - tmp_mvQ02);
	if (tmp_abs >= 4 || tmp_abs0 >= 4 || tmp_abs1 >= 4 || tmp_abs2 >= 4) {
		bS[0] = 1;
	} else {
		bS[0] = 0;
	}
	#endif // defined(SSE_ENABLE) && HAVE_SSE4
}
static void boundaryStrength3(u8 bS[1], u8 predModeP0, u8 predModeQ0, i32 mvP0[2][2], i32 mvQ0[2][2]) {
	#if defined(SSE_ENABLE) && HAVE_SSE4
	boundaryStrength3_mv32_orcc(bS, predModeP0, predModeQ0, mvP0, mvQ0);
	#else
	i32 vA[2];
	i32 vB[2];
	i32 tmp_mvQ0;
	i32 tmp_mvQ00;
	i32 tmp_mvP0;
	i32 tmp_mvP00;
	i32 tmp_vA;
	i32 tmp_vB;
	i32 tmp_abs;
	i32 tmp_vA0;
	i32 tmp_vB0;
	i32 tmp_abs0;

	tmp_mvQ0 = mvQ0[predModeQ0][0];
	vA[0] = tmp_mvQ0;
	tmp_mvQ00 = mvQ0[predModeQ0][1];
	vA[1] = tmp_mvQ00;
	tmp_mvP0 = mvP0[predModeP0][0];
	vB[0] = tmp_mvP0;
	tmp_mvP00 = mvP0[predModeP0][1];
	vB[1] = tmp_mvP00;
	tmp_vA = vA[0];
	tmp_vB = vB[0];
	tmp_abs = HevcDecoder_DBFilter_GenerateBs_abs(tmp_vA - tmp_vB);
	tmp_vA0 = vA[1];
	tmp_vB0 = vB[1];
	tmp_abs0 = HevcDecoder_DBFilter_GenerateBs_abs(tmp_vA0 - tmp_vB0);
	if (tmp_abs >= 4 || tmp_abs0 >= 4) {
		bS[0] = 1;
	} else {
		bS[0] = 0;
	}
	#endif // defined(SSE_ENABLE) && HAVE_SSE4
}
static void genBoundFilterStrengthTUVert(u8 bS[1], u16 addrInBlk[2], i32 cbfQ0, u8 partIdx) {
	u16 tmp_addrInBlk;
	i32 local_PICT_WIDTH_POW_2;
	u16 tmp_addrInBlk0;
	u16 q0[2];
	u16 tmp_q0;
	u16 tmp_q00;
	u16 p0[2];
	i32 i;
	i32 j;
	u16 tmp_q01;
	i32 tmp_mvLeftNeighb;
	i32 mvP0[2][2];
	i32 i0;
	i32 j0;
	i32 tmp_mv;
	i32 mvQ0[2][2];
	i32 i1;
	u16 tmp_q02;
	i16 tmp_refPocLeftNeighb;
	i16 refPocP0[2];
	i32 i2;
	i16 tmp_refPoc;
	i16 refPocQ0[2];
	u16 tmp_q03;
	i32 cbfP0;
	u8 predModeQ0;
	u8 predModeP0;
	u16 tmp_p0;
	u16 tmp_p00;
	u8 tmp_predModeTab;
	u8 local_INTRA;
	u16 tmp_q04;
	u16 tmp_q05;
	u8 tmp_predModeTab0;
	u16 tmp_p01;
	u16 tmp_p02;
	i32 tmp_isBiPredTab;
	u16 tmp_q06;
	u16 tmp_q07;
	i32 tmp_isBiPredTab0;
	i16 tmp_refPocQ0;
	i16 tmp_refPocP0;
	i16 tmp_refPocQ00;
	i16 tmp_refPocQ01;
	i16 tmp_refPocP00;
	i16 tmp_refPocP01;
	i16 tmp_refPocP02;
	i16 tmp_refPocQ02;
	i16 tmp_refPocP03;
	i16 tmp_refPocQ03;
	i16 tmp_refPocP04;
	i16 tmp_refPocQ04;
	u16 tmp_p03;
	u16 tmp_p04;
	i32 tmp_isBiPredTab1;
	u16 tmp_q08;
	u16 tmp_q09;
	i32 tmp_isBiPredTab2;
	u16 tmp_q010;
	u16 tmp_q011;
	u8 tmp_predModeTab1;
	u16 tmp_p05;
	u16 tmp_p06;
	u8 tmp_predModeTab2;
	i16 tmp_refPocQ05;
	i16 tmp_refPocP05;

	tmp_addrInBlk = addrInBlk[0];
	local_PICT_WIDTH_POW_2 = HevcDecoder_DBFilter_GenerateBs_PICT_WIDTH_POW_2;
	q0[0] = tmp_addrInBlk & local_PICT_WIDTH_POW_2 / 4 - 1;
	tmp_addrInBlk0 = addrInBlk[1];
	q0[1] = tmp_addrInBlk0;
	tmp_q0 = q0[0];
	p0[0] = tmp_q0 - 1;
	tmp_q00 = q0[1];
	p0[1] = tmp_q00;
	i = 0;
	while (i <= 1) {
		j = 0;
		while (j <= 1) {
			tmp_q01 = q0[1];
			tmp_mvLeftNeighb = mvLeftNeighb[tmp_q01][i][j];
			mvP0[i][j] = tmp_mvLeftNeighb;
			j = j + 1;
		}
		i = i + 1;
	}
	i0 = 0;
	while (i0 <= 1) {
		j0 = 0;
		while (j0 <= 1) {
			tmp_mv = mv[partIdx][i0][j0];
			mvQ0[i0][j0] = tmp_mv;
			j0 = j0 + 1;
		}
		i0 = i0 + 1;
	}
	i1 = 0;
	while (i1 <= 1) {
		tmp_q02 = q0[1];
		tmp_refPocLeftNeighb = refPocLeftNeighb[tmp_q02][i1];
		refPocP0[i1] = tmp_refPocLeftNeighb;
		i1 = i1 + 1;
	}
	i2 = 0;
	while (i2 <= 1) {
		tmp_refPoc = refPoc[partIdx][i2];
		refPocQ0[i2] = tmp_refPoc;
		i2 = i2 + 1;
	}
	tmp_q03 = q0[1];
	cbfP0 = cbfLeftNeighb[tmp_q03];
	tmp_p0 = p0[0];
	tmp_p00 = p0[1];
	tmp_predModeTab = predModeTab[tmp_p0][tmp_p00];
	local_INTRA = HevcDecoder_DBFilter_GenerateBs_INTRA;
	tmp_q04 = q0[0];
	tmp_q05 = q0[1];
	tmp_predModeTab0 = predModeTab[tmp_q04][tmp_q05];
	local_INTRA = HevcDecoder_DBFilter_GenerateBs_INTRA;
	if (tmp_predModeTab == local_INTRA || tmp_predModeTab0 == local_INTRA) {
		bS[0] = 2;
	} else {
		if (cbfP0 || cbfQ0) {
			bS[0] = 1;
		} else {
			bS[0] = 1;
			tmp_p01 = p0[0];
			tmp_p02 = p0[1];
			tmp_isBiPredTab = isBiPredTab[tmp_p01][tmp_p02];
			tmp_q06 = q0[0];
			tmp_q07 = q0[1];
			tmp_isBiPredTab0 = isBiPredTab[tmp_q06][tmp_q07];
			if (tmp_isBiPredTab && tmp_isBiPredTab0) {
				tmp_refPocQ0 = refPocQ0[0];
				tmp_refPocP0 = refPocP0[0];
				if (tmp_refPocQ0 == tmp_refPocP0) {
					tmp_refPocQ00 = refPocQ0[0];
					tmp_refPocQ01 = refPocQ0[1];
					tmp_refPocP00 = refPocP0[0];
					tmp_refPocP01 = refPocP0[1];
					if (tmp_refPocQ00 == tmp_refPocQ01 && tmp_refPocP00 == tmp_refPocP01) {
						boundaryStrength0(bS, mvP0, mvQ0);
					} else {
						tmp_refPocP02 = refPocP0[1];
						tmp_refPocQ02 = refPocQ0[1];
						if (tmp_refPocP02 == tmp_refPocQ02) {
							boundaryStrength1(bS, mvP0, mvQ0);
						}
					}
				} else {
					tmp_refPocP03 = refPocP0[1];
					tmp_refPocQ03 = refPocQ0[0];
					tmp_refPocP04 = refPocP0[0];
					tmp_refPocQ04 = refPocQ0[1];
					if (tmp_refPocP03 == tmp_refPocQ03 && tmp_refPocP04 == tmp_refPocQ04) {
						boundaryStrength2(bS, mvP0, mvQ0);
					}
				}
			} else {
				tmp_p03 = p0[0];
				tmp_p04 = p0[1];
				tmp_isBiPredTab1 = isBiPredTab[tmp_p03][tmp_p04];
				tmp_q08 = q0[0];
				tmp_q09 = q0[1];
				tmp_isBiPredTab2 = isBiPredTab[tmp_q08][tmp_q09];
				if (!tmp_isBiPredTab1 && !tmp_isBiPredTab2) {
					tmp_q010 = q0[0];
					tmp_q011 = q0[1];
					tmp_predModeTab1 = predModeTab[tmp_q010][tmp_q011];
					predModeQ0 = tmp_predModeTab1 & 1;
					tmp_p05 = p0[0];
					tmp_p06 = p0[1];
					tmp_predModeTab2 = predModeTab[tmp_p05][tmp_p06];
					predModeP0 = tmp_predModeTab2 & 1;
					tmp_refPocQ05 = refPocQ0[predModeQ0];
					tmp_refPocP05 = refPocP0[predModeP0];
					if (tmp_refPocQ05 == tmp_refPocP05) {
						boundaryStrength3(bS, predModeP0, predModeQ0, mvP0, mvQ0);
					}
				}
			}
		}
	}
}
static void genBoundFilterStrengthTUHor(u8 bS[1], u16 addrInBlk[2], i32 cbfQ0, u8 partIdx) {
	u16 tmp_addrInBlk;
	i32 local_PICT_WIDTH_POW_2;
	u16 tmp_addrInBlk0;
	u16 q0[2];
	i32 i;
	i32 j;
	u16 tmp_q0;
	i32 tmp_mvUpNeighb;
	i32 mvP0[2][2];
	i32 i0;
	i32 j0;
	i32 tmp_mv;
	i32 mvQ0[2][2];
	i32 i1;
	u16 tmp_q00;
	i16 tmp_refPocUpNeighb;
	i16 refPocP0[2];
	i32 i2;
	i16 tmp_refPoc;
	i16 refPocQ0[2];
	u16 tmp_q01;
	u16 tmp_q02;
	u16 p0[2];
	u16 tmp_q03;
	i32 cbfP0;
	u8 predModeQ0;
	u8 predModeP0;
	u16 tmp_p0;
	u16 tmp_p00;
	u8 tmp_predModeTab;
	u8 local_INTRA;
	u16 tmp_q04;
	u16 tmp_q05;
	u8 tmp_predModeTab0;
	u16 tmp_p01;
	u16 tmp_p02;
	i32 tmp_isBiPredTab;
	u16 tmp_q06;
	u16 tmp_q07;
	i32 tmp_isBiPredTab0;
	i16 tmp_refPocQ0;
	i16 tmp_refPocP0;
	i16 tmp_refPocQ00;
	i16 tmp_refPocQ01;
	i16 tmp_refPocP00;
	i16 tmp_refPocP01;
	i16 tmp_refPocP02;
	i16 tmp_refPocQ02;
	i16 tmp_refPocP03;
	i16 tmp_refPocQ03;
	i16 tmp_refPocP04;
	i16 tmp_refPocQ04;
	u16 tmp_p03;
	u16 tmp_p04;
	i32 tmp_isBiPredTab1;
	u16 tmp_q08;
	u16 tmp_q09;
	i32 tmp_isBiPredTab2;
	u16 tmp_q010;
	u16 tmp_q011;
	u8 tmp_predModeTab1;
	u16 tmp_p05;
	u16 tmp_p06;
	u8 tmp_predModeTab2;
	i16 tmp_refPocQ05;
	i16 tmp_refPocP05;

	tmp_addrInBlk = addrInBlk[0];
	local_PICT_WIDTH_POW_2 = HevcDecoder_DBFilter_GenerateBs_PICT_WIDTH_POW_2;
	q0[0] = tmp_addrInBlk & local_PICT_WIDTH_POW_2 / 4 - 1;
	tmp_addrInBlk0 = addrInBlk[1];
	q0[1] = tmp_addrInBlk0;
	i = 0;
	while (i <= 1) {
		j = 0;
		while (j <= 1) {
			tmp_q0 = q0[0];
			tmp_mvUpNeighb = mvUpNeighb[tmp_q0][i][j];
			mvP0[i][j] = tmp_mvUpNeighb;
			j = j + 1;
		}
		i = i + 1;
	}
	i0 = 0;
	while (i0 <= 1) {
		j0 = 0;
		while (j0 <= 1) {
			tmp_mv = mv[partIdx][i0][j0];
			mvQ0[i0][j0] = tmp_mv;
			j0 = j0 + 1;
		}
		i0 = i0 + 1;
	}
	i1 = 0;
	while (i1 <= 1) {
		tmp_q00 = q0[0];
		tmp_refPocUpNeighb = refPocUpNeighb[tmp_q00][i1];
		refPocP0[i1] = tmp_refPocUpNeighb;
		i1 = i1 + 1;
	}
	i2 = 0;
	while (i2 <= 1) {
		tmp_refPoc = refPoc[partIdx][i2];
		refPocQ0[i2] = tmp_refPoc;
		i2 = i2 + 1;
	}
	tmp_q01 = q0[0];
	p0[0] = tmp_q01;
	tmp_q02 = q0[1];
	p0[1] = tmp_q02 - 1;
	tmp_q03 = q0[0];
	cbfP0 = cbfUpNeighb[tmp_q03];
	tmp_p0 = p0[0];
	tmp_p00 = p0[1];
	tmp_predModeTab = predModeTab[tmp_p0][tmp_p00];
	local_INTRA = HevcDecoder_DBFilter_GenerateBs_INTRA;
	tmp_q04 = q0[0];
	tmp_q05 = q0[1];
	tmp_predModeTab0 = predModeTab[tmp_q04][tmp_q05];
	local_INTRA = HevcDecoder_DBFilter_GenerateBs_INTRA;
	if (tmp_predModeTab == local_INTRA || tmp_predModeTab0 == local_INTRA) {
		bS[0] = 2;
	} else {
		if (cbfP0 || cbfQ0) {
			bS[0] = 1;
		} else {
			bS[0] = 1;
			tmp_p01 = p0[0];
			tmp_p02 = p0[1];
			tmp_isBiPredTab = isBiPredTab[tmp_p01][tmp_p02];
			tmp_q06 = q0[0];
			tmp_q07 = q0[1];
			tmp_isBiPredTab0 = isBiPredTab[tmp_q06][tmp_q07];
			if (tmp_isBiPredTab && tmp_isBiPredTab0) {
				tmp_refPocQ0 = refPocQ0[0];
				tmp_refPocP0 = refPocP0[0];
				if (tmp_refPocQ0 == tmp_refPocP0) {
					tmp_refPocQ00 = refPocQ0[0];
					tmp_refPocQ01 = refPocQ0[1];
					tmp_refPocP00 = refPocP0[0];
					tmp_refPocP01 = refPocP0[1];
					if (tmp_refPocQ00 == tmp_refPocQ01 && tmp_refPocP00 == tmp_refPocP01) {
						boundaryStrength0(bS, mvP0, mvQ0);
					} else {
						tmp_refPocP02 = refPocP0[1];
						tmp_refPocQ02 = refPocQ0[1];
						if (tmp_refPocP02 == tmp_refPocQ02) {
							boundaryStrength1(bS, mvP0, mvQ0);
						}
					}
				} else {
					tmp_refPocP03 = refPocP0[1];
					tmp_refPocQ03 = refPocQ0[0];
					tmp_refPocP04 = refPocP0[0];
					tmp_refPocQ04 = refPocQ0[1];
					if (tmp_refPocP03 == tmp_refPocQ03 && tmp_refPocP04 == tmp_refPocQ04) {
						boundaryStrength2(bS, mvP0, mvQ0);
					}
				}
			} else {
				tmp_p03 = p0[0];
				tmp_p04 = p0[1];
				tmp_isBiPredTab1 = isBiPredTab[tmp_p03][tmp_p04];
				tmp_q08 = q0[0];
				tmp_q09 = q0[1];
				tmp_isBiPredTab2 = isBiPredTab[tmp_q08][tmp_q09];
				if (!tmp_isBiPredTab1 && !tmp_isBiPredTab2) {
					tmp_q010 = q0[0];
					tmp_q011 = q0[1];
					tmp_predModeTab1 = predModeTab[tmp_q010][tmp_q011];
					predModeQ0 = tmp_predModeTab1 & 1;
					tmp_p05 = p0[0];
					tmp_p06 = p0[1];
					tmp_predModeTab2 = predModeTab[tmp_p05][tmp_p06];
					predModeP0 = tmp_predModeTab2 & 1;
					tmp_refPocQ05 = refPocQ0[predModeQ0];
					tmp_refPocP05 = refPocP0[predModeP0];
					if (tmp_refPocQ05 == tmp_refPocP05) {
						boundaryStrength3(bS, predModeP0, predModeQ0, mvP0, mvQ0);
					}
				}
			}
		}
	}
}
static void genBoundFilterStrengthCorePU(u8 bS[1], u16 addrInBlk[2], i32 isVerticalEdge, i32 mvP0[2][2], i32 mvQ0[2][2], i16 refPocP0[2], i16 refPocQ0[2]) {
	u16 tmp_addrInBlk;
	i32 local_PICT_WIDTH_POW_2;
	u16 tmp_addrInBlk0;
	u16 q0[2];
	u16 tmp_q0;
	u16 tmp_q00;
	u16 tmp_q01;
	u16 tmp_q02;
	u16 p0[2];
	u8 predModeQ0;
	u8 predModeP0;
	u16 tmp_p0;
	u16 tmp_p00;
	u8 tmp_predModeTab;
	u8 local_INTRA;
	u16 tmp_q03;
	u16 tmp_q04;
	u8 tmp_predModeTab0;
	u16 tmp_p01;
	u16 tmp_p02;
	i32 tmp_isBiPredTab;
	u16 tmp_q05;
	u16 tmp_q06;
	i32 tmp_isBiPredTab0;
	i16 tmp_refPocQ0;
	i16 tmp_refPocP0;
	i16 tmp_refPocQ00;
	i16 tmp_refPocQ01;
	i16 tmp_refPocP00;
	i16 tmp_refPocP01;
	i16 tmp_refPocP02;
	i16 tmp_refPocQ02;
	i16 tmp_refPocP03;
	i16 tmp_refPocQ03;
	i16 tmp_refPocP04;
	i16 tmp_refPocQ04;
	u16 tmp_p03;
	u16 tmp_p04;
	i32 tmp_isBiPredTab1;
	u16 tmp_q07;
	u16 tmp_q08;
	i32 tmp_isBiPredTab2;
	u16 tmp_q09;
	u16 tmp_q010;
	u8 tmp_predModeTab1;
	u16 tmp_p05;
	u16 tmp_p06;
	u8 tmp_predModeTab2;
	i16 tmp_refPocQ05;
	i16 tmp_refPocP05;

	tmp_addrInBlk = addrInBlk[0];
	local_PICT_WIDTH_POW_2 = HevcDecoder_DBFilter_GenerateBs_PICT_WIDTH_POW_2;
	q0[0] = tmp_addrInBlk & local_PICT_WIDTH_POW_2 / 4 - 1;
	tmp_addrInBlk0 = addrInBlk[1];
	q0[1] = tmp_addrInBlk0;
	if (isVerticalEdge) {
		tmp_q0 = q0[0];
		p0[0] = tmp_q0 - 1;
		tmp_q00 = q0[1];
		p0[1] = tmp_q00;
	} else {
		tmp_q01 = q0[0];
		p0[0] = tmp_q01;
		tmp_q02 = q0[1];
		p0[1] = tmp_q02 - 1;
	}
	tmp_p0 = p0[0];
	tmp_p00 = p0[1];
	tmp_predModeTab = predModeTab[tmp_p0][tmp_p00];
	local_INTRA = HevcDecoder_DBFilter_GenerateBs_INTRA;
	tmp_q03 = q0[0];
	tmp_q04 = q0[1];
	tmp_predModeTab0 = predModeTab[tmp_q03][tmp_q04];
	local_INTRA = HevcDecoder_DBFilter_GenerateBs_INTRA;
	if (tmp_predModeTab == local_INTRA || tmp_predModeTab0 == local_INTRA) {
		bS[0] = 2;
	} else {
		bS[0] = 1;
		tmp_p01 = p0[0];
		tmp_p02 = p0[1];
		tmp_isBiPredTab = isBiPredTab[tmp_p01][tmp_p02];
		tmp_q05 = q0[0];
		tmp_q06 = q0[1];
		tmp_isBiPredTab0 = isBiPredTab[tmp_q05][tmp_q06];
		if (tmp_isBiPredTab && tmp_isBiPredTab0) {
			tmp_refPocQ0 = refPocQ0[0];
			tmp_refPocP0 = refPocP0[0];
			if (tmp_refPocQ0 == tmp_refPocP0) {
				tmp_refPocQ00 = refPocQ0[0];
				tmp_refPocQ01 = refPocQ0[1];
				tmp_refPocP00 = refPocP0[0];
				tmp_refPocP01 = refPocP0[1];
				if (tmp_refPocQ00 == tmp_refPocQ01 && tmp_refPocP00 == tmp_refPocP01) {
					boundaryStrength0(bS, mvP0, mvQ0);
				} else {
					tmp_refPocP02 = refPocP0[1];
					tmp_refPocQ02 = refPocQ0[1];
					if (tmp_refPocP02 == tmp_refPocQ02) {
						boundaryStrength1(bS, mvP0, mvQ0);
					}
				}
			} else {
				tmp_refPocP03 = refPocP0[1];
				tmp_refPocQ03 = refPocQ0[0];
				tmp_refPocP04 = refPocP0[0];
				tmp_refPocQ04 = refPocQ0[1];
				if (tmp_refPocP03 == tmp_refPocQ03 && tmp_refPocP04 == tmp_refPocQ04) {
					boundaryStrength2(bS, mvP0, mvQ0);
				}
			}
		} else {
			tmp_p03 = p0[0];
			tmp_p04 = p0[1];
			tmp_isBiPredTab1 = isBiPredTab[tmp_p03][tmp_p04];
			tmp_q07 = q0[0];
			tmp_q08 = q0[1];
			tmp_isBiPredTab2 = isBiPredTab[tmp_q07][tmp_q08];
			if (!tmp_isBiPredTab1 && !tmp_isBiPredTab2) {
				tmp_q09 = q0[0];
				tmp_q010 = q0[1];
				tmp_predModeTab1 = predModeTab[tmp_q09][tmp_q010];
				predModeQ0 = tmp_predModeTab1 & 1;
				tmp_p05 = p0[0];
				tmp_p06 = p0[1];
				tmp_predModeTab2 = predModeTab[tmp_p05][tmp_p06];
				predModeP0 = tmp_predModeTab2 & 1;
				tmp_refPocQ05 = refPocQ0[predModeQ0];
				tmp_refPocP05 = refPocP0[predModeP0];
				if (tmp_refPocQ05 == tmp_refPocP05) {
					boundaryStrength3(bS, predModeP0, predModeQ0, mvP0, mvQ0);
				}
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
// Actions
static i32 isSchedulable_isNewSliceOrPict_isNotDep() {
	i32 result;
	u8 partMode;
	u8 local_PART_MODE_SLICE_INDEP;
	u8 local_PART_MODE_PICT;

	partMode = tokens_PartMode[(index_PartMode + (0)) % SIZE_PartMode];
	local_PART_MODE_SLICE_INDEP = HevcDecoder_DBFilter_GenerateBs_PART_MODE_SLICE_INDEP;
	local_PART_MODE_PICT = HevcDecoder_DBFilter_GenerateBs_PART_MODE_PICT;
	result = partMode == local_PART_MODE_SLICE_INDEP || partMode == local_PART_MODE_PICT;
	return result;
}

static void isNewSliceOrPict_isNotDep() {

	u8 log2LcuSz;
	u8 partMode;
	u8 lfAcrossSlcTile;
	u16 valNumTiles;
	u16 tmp_SliceAddr;
	u16 tmp_SliceAddr0;

	log2LcuSz = tokens_LcuSizeMax[(index_LcuSizeMax + (0)) % SIZE_LcuSizeMax];
	partMode = tokens_PartMode[(index_PartMode + (0)) % SIZE_PartMode];
	lfAcrossSlcTile = tokens_LFAcrossSlcTile[(index_LFAcrossSlcTile + (0)) % SIZE_LFAcrossSlcTile];
	valNumTiles = tokens_TilesCoord[(index_TilesCoord + (0)) % SIZE_TilesCoord];
	lcuSizeMax = 1 << log2LcuSz;
	numTiles = valNumTiles;
	iLoop = 0;
	tmp_SliceAddr = tokens_SliceAddr[(index_SliceAddr + (0)) % SIZE_SliceAddr];
	sliceAdr[0] = tmp_SliceAddr;
	tmp_SliceAddr0 = tokens_SliceAddr[(index_SliceAddr + (1)) % SIZE_SliceAddr];
	sliceAdr[1] = tmp_SliceAddr0;
	loopFilterAcrossSlc = (lfAcrossSlcTile & 1) != 0;
	loopFilterAcrossTile = (lfAcrossSlcTile & 2) != 0;

	// Update ports indexes
	index_LcuSizeMax += 1;
	index_PartMode += 1;
	index_SliceAddr += 2;
	read_end_SliceAddr();
	index_LFAcrossSlcTile += 1;
	index_TilesCoord += 1;

	rate_LcuSizeMax += 1;
	rate_PartMode += 1;
	rate_SliceAddr += 2;
	rate_LFAcrossSlcTile += 1;
	rate_TilesCoord += 1;
}
static void isNewSliceOrPict_isNotDep_aligned() {

	u8 log2LcuSz;
	u8 partMode;
	u8 lfAcrossSlcTile;
	u16 valNumTiles;
	u16 tmp_SliceAddr;
	u16 tmp_SliceAddr0;

	log2LcuSz = tokens_LcuSizeMax[(index_LcuSizeMax + (0)) % SIZE_LcuSizeMax];
	partMode = tokens_PartMode[(index_PartMode + (0)) % SIZE_PartMode];
	lfAcrossSlcTile = tokens_LFAcrossSlcTile[(index_LFAcrossSlcTile + (0)) % SIZE_LFAcrossSlcTile];
	valNumTiles = tokens_TilesCoord[(index_TilesCoord + (0)) % SIZE_TilesCoord];
	lcuSizeMax = 1 << log2LcuSz;
	numTiles = valNumTiles;
	iLoop = 0;
	tmp_SliceAddr = tokens_SliceAddr[(index_SliceAddr % SIZE_SliceAddr) + (0)];
	sliceAdr[0] = tmp_SliceAddr;
	tmp_SliceAddr0 = tokens_SliceAddr[(index_SliceAddr % SIZE_SliceAddr) + (1)];
	sliceAdr[1] = tmp_SliceAddr0;
	loopFilterAcrossSlc = (lfAcrossSlcTile & 1) != 0;
	loopFilterAcrossTile = (lfAcrossSlcTile & 2) != 0;

	// Update ports indexes
	index_LcuSizeMax += 1;
	index_PartMode += 1;
	index_SliceAddr += 2;
	read_end_SliceAddr();
	index_LFAcrossSlcTile += 1;
	index_TilesCoord += 1;

	rate_LcuSizeMax += 1;
	rate_PartMode += 1;
	rate_SliceAddr += 2;
	rate_LFAcrossSlcTile += 1;
	rate_TilesCoord += 1;
}
static i32 isSchedulable_isNewSliceOrPict_isDep() {
	i32 result;
	u8 partMode;
	u8 local_PART_MODE_SLICE_DEP;

	partMode = tokens_PartMode[(index_PartMode + (0)) % SIZE_PartMode];
	local_PART_MODE_SLICE_DEP = HevcDecoder_DBFilter_GenerateBs_PART_MODE_SLICE_DEP;
	result = partMode == local_PART_MODE_SLICE_DEP;
	return result;
}

static void isNewSliceOrPict_isDep() {

	u8 partMode;
	u16 tmp_SliceAddr;
	u16 tmp_SliceAddr0;

	partMode = tokens_PartMode[(index_PartMode + (0)) % SIZE_PartMode];
	tmp_SliceAddr = tokens_SliceAddr[(index_SliceAddr + (0)) % SIZE_SliceAddr];
	sliceAdr[0] = tmp_SliceAddr;
	tmp_SliceAddr0 = tokens_SliceAddr[(index_SliceAddr + (1)) % SIZE_SliceAddr];
	sliceAdr[1] = tmp_SliceAddr0;

	// Update ports indexes
	index_PartMode += 1;
	index_SliceAddr += 2;
	read_end_SliceAddr();

	rate_PartMode += 1;
	rate_SliceAddr += 2;
}
static void isNewSliceOrPict_isDep_aligned() {

	u8 partMode;
	u16 tmp_SliceAddr;
	u16 tmp_SliceAddr0;

	partMode = tokens_PartMode[(index_PartMode + (0)) % SIZE_PartMode];
	tmp_SliceAddr = tokens_SliceAddr[(index_SliceAddr % SIZE_SliceAddr) + (0)];
	sliceAdr[0] = tmp_SliceAddr;
	tmp_SliceAddr0 = tokens_SliceAddr[(index_SliceAddr % SIZE_SliceAddr) + (1)];
	sliceAdr[1] = tmp_SliceAddr0;

	// Update ports indexes
	index_PartMode += 1;
	index_SliceAddr += 2;
	read_end_SliceAddr();

	rate_PartMode += 1;
	rate_SliceAddr += 2;
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
	local_PART_MODE_SLICE_DEP = HevcDecoder_DBFilter_GenerateBs_PART_MODE_SLICE_DEP;
	local_PART_MODE_SLICE_INDEP = HevcDecoder_DBFilter_GenerateBs_PART_MODE_SLICE_INDEP;
	local_PART_MODE_PICT = HevcDecoder_DBFilter_GenerateBs_PART_MODE_PICT;
	local_PART_2Nx2N = HevcDecoder_DBFilter_GenerateBs_PART_2Nx2N;
	local_PART_NxN = HevcDecoder_DBFilter_GenerateBs_PART_NxN;
	result = partMode != local_PART_MODE_SLICE_DEP && partMode != local_PART_MODE_SLICE_INDEP && partMode != local_PART_MODE_PICT && (partMode != local_PART_2Nx2N && partMode != local_PART_NxN);
	return result;
}

static void getPartMode_isNonQuadTree() {

	u8 partMode;

	partMode = tokens_PartMode[(index_PartMode + (0)) % SIZE_PartMode];
	currIdx = 0;
	currIdxHor = 0;
	currIdxVer = 0;
	numMvInfo = 2;

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
	local_PART_2Nx2N = HevcDecoder_DBFilter_GenerateBs_PART_2Nx2N;
	local_PART_NxN = HevcDecoder_DBFilter_GenerateBs_PART_NxN;
	result = partMode == local_PART_2Nx2N || partMode == local_PART_NxN;
	return result;
}

static void getPartMode_isQuadTree() {

	u8 partMode;
	u8 tmp_partModeToNumPart;

	partMode = tokens_PartMode[(index_PartMode + (0)) % SIZE_PartMode];
	tmp_partModeToNumPart = HevcDecoder_DBFilter_GenerateBs_partModeToNumPart[partMode];
	numPart = tmp_partModeToNumPart;
	numPartDecoded = 0;

	// Update ports indexes
	index_PartMode += 1;

	rate_PartMode += 1;
}
static i32 isSchedulable_getRefPictInfo_launch_isNotBiPred() {
	i32 result;
	u8 isBiPredOrLx;
	u8 local_BI_PRED;
	u16 local_currIdx;
	u8 local_numMvInfo;

	isBiPredOrLx = tokens_IsBiPredOrLx[(index_IsBiPredOrLx + (0)) % SIZE_IsBiPredOrLx];
	local_BI_PRED = HevcDecoder_DBFilter_GenerateBs_BI_PRED;
	local_currIdx = currIdx;
	local_numMvInfo = numMvInfo;
	result = isBiPredOrLx != local_BI_PRED && local_currIdx < local_numMvInfo;
	return result;
}

static void getRefPictInfo_launch_isNotBiPred() {

	u8 isBiPredOrLx;
	i16 refPocVal;
	u16 local_currIdx;
	u8 local_BI_PRED;
	u32 i;
	i32 tmp_Mv;

	isBiPredOrLx = tokens_IsBiPredOrLx[(index_IsBiPredOrLx + (0)) % SIZE_IsBiPredOrLx];
	refPocVal = tokens_RefPoc[(index_RefPoc + (0)) % SIZE_RefPoc];
	local_currIdx = currIdx;
	local_BI_PRED = HevcDecoder_DBFilter_GenerateBs_BI_PRED;
	isBiPred[local_currIdx] = isBiPredOrLx == local_BI_PRED;
	local_currIdx = currIdx;
	refPoc[local_currIdx][0] = refPocVal;
	local_currIdx = currIdx;
	i = 0;
	while (i <= 1) {
		tmp_Mv = tokens_Mv[(index_Mv + (i)) % SIZE_Mv];
		mv[local_currIdx][0][i] = tmp_Mv;
		i = i + 1;
	}
	local_currIdx = currIdx;
	currIdx = local_currIdx + 1;

	// Update ports indexes
	index_IsBiPredOrLx += 1;
	index_RefPoc += 1;
	index_Mv += 2;
	read_end_Mv();

	rate_IsBiPredOrLx += 1;
	rate_RefPoc += 1;
	rate_Mv += 2;
}
static void getRefPictInfo_launch_isNotBiPred_aligned() {

	u8 isBiPredOrLx;
	i16 refPocVal;
	u16 local_currIdx;
	u8 local_BI_PRED;
	u32 i;
	i32 tmp_Mv;

	isBiPredOrLx = tokens_IsBiPredOrLx[(index_IsBiPredOrLx + (0)) % SIZE_IsBiPredOrLx];
	refPocVal = tokens_RefPoc[(index_RefPoc + (0)) % SIZE_RefPoc];
	local_currIdx = currIdx;
	local_BI_PRED = HevcDecoder_DBFilter_GenerateBs_BI_PRED;
	isBiPred[local_currIdx] = isBiPredOrLx == local_BI_PRED;
	local_currIdx = currIdx;
	refPoc[local_currIdx][0] = refPocVal;
	local_currIdx = currIdx;
	i = 0;
	while (i <= 1) {
		tmp_Mv = tokens_Mv[(index_Mv % SIZE_Mv) + (i)];
		mv[local_currIdx][0][i] = tmp_Mv;
		i = i + 1;
	}
	local_currIdx = currIdx;
	currIdx = local_currIdx + 1;

	// Update ports indexes
	index_IsBiPredOrLx += 1;
	index_RefPoc += 1;
	index_Mv += 2;
	read_end_Mv();

	rate_IsBiPredOrLx += 1;
	rate_RefPoc += 1;
	rate_Mv += 2;
}
static i32 isSchedulable_getRefPictInfo_launch_isBiPred() {
	i32 result;
	u8 isBiPredOrLx;
	u8 local_BI_PRED;
	u16 local_currIdx;
	u8 local_numMvInfo;

	isBiPredOrLx = tokens_IsBiPredOrLx[(index_IsBiPredOrLx + (0)) % SIZE_IsBiPredOrLx];
	local_BI_PRED = HevcDecoder_DBFilter_GenerateBs_BI_PRED;
	local_currIdx = currIdx;
	local_numMvInfo = numMvInfo;
	result = isBiPredOrLx == local_BI_PRED && local_currIdx < local_numMvInfo;
	return result;
}

static void getRefPictInfo_launch_isBiPred() {

	u8 isBiPredOrLx;
	u16 local_currIdx;
	u8 local_BI_PRED;
	u32 i;
	i16 tmp_RefPoc;
	u32 j;
	u32 i0;
	i32 tmp_Mv;

	isBiPredOrLx = tokens_IsBiPredOrLx[(index_IsBiPredOrLx + (0)) % SIZE_IsBiPredOrLx];
	local_currIdx = currIdx;
	local_BI_PRED = HevcDecoder_DBFilter_GenerateBs_BI_PRED;
	isBiPred[local_currIdx] = isBiPredOrLx == local_BI_PRED;
	local_currIdx = currIdx;
	i = 0;
	while (i <= 1) {
		tmp_RefPoc = tokens_RefPoc[(index_RefPoc + (i)) % SIZE_RefPoc];
		refPoc[local_currIdx][i] = tmp_RefPoc;
		i = i + 1;
	}
	local_currIdx = currIdx;
	j = 0;
	while (j <= 1) {
		i0 = 0;
		while (i0 <= 1) {
			tmp_Mv = tokens_Mv[(index_Mv + (i0 + 2 * j)) % SIZE_Mv];
			mv[local_currIdx][j][i0] = tmp_Mv;
			i0 = i0 + 1;
		}
		j = j + 1;
	}
	local_currIdx = currIdx;
	currIdx = local_currIdx + 1;

	// Update ports indexes
	index_IsBiPredOrLx += 1;
	index_RefPoc += 2;
	read_end_RefPoc();
	index_Mv += 4;
	read_end_Mv();

	rate_IsBiPredOrLx += 1;
	rate_RefPoc += 2;
	rate_Mv += 4;
}
static void getRefPictInfo_launch_isBiPred_aligned() {

	u8 isBiPredOrLx;
	u16 local_currIdx;
	u8 local_BI_PRED;
	u32 i;
	i16 tmp_RefPoc;
	u32 j;
	u32 i0;
	i32 tmp_Mv;

	isBiPredOrLx = tokens_IsBiPredOrLx[(index_IsBiPredOrLx + (0)) % SIZE_IsBiPredOrLx];
	local_currIdx = currIdx;
	local_BI_PRED = HevcDecoder_DBFilter_GenerateBs_BI_PRED;
	isBiPred[local_currIdx] = isBiPredOrLx == local_BI_PRED;
	local_currIdx = currIdx;
	i = 0;
	while (i <= 1) {
		tmp_RefPoc = tokens_RefPoc[(index_RefPoc % SIZE_RefPoc) + (i)];
		refPoc[local_currIdx][i] = tmp_RefPoc;
		i = i + 1;
	}
	local_currIdx = currIdx;
	j = 0;
	while (j <= 1) {
		i0 = 0;
		while (i0 <= 1) {
			tmp_Mv = tokens_Mv[(index_Mv % SIZE_Mv) + (i0 + 2 * j)];
			mv[local_currIdx][j][i0] = tmp_Mv;
			i0 = i0 + 1;
		}
		j = j + 1;
	}
	local_currIdx = currIdx;
	currIdx = local_currIdx + 1;

	// Update ports indexes
	index_IsBiPredOrLx += 1;
	index_RefPoc += 2;
	read_end_RefPoc();
	index_Mv += 4;
	read_end_Mv();

	rate_IsBiPredOrLx += 1;
	rate_RefPoc += 2;
	rate_Mv += 4;
}
static i32 isSchedulable_getRefPictInfo_done() {
	i32 result;
	u16 local_currIdx;
	u8 local_numMvInfo;

	local_currIdx = currIdx;
	local_numMvInfo = numMvInfo;
	result = local_currIdx == local_numMvInfo;
	return result;
}

static void getRefPictInfo_done() {

	u8 local_numMvInfo;
	i32 i;
	i32 j;
	i32 tmp_mv;
	u16 tmp_cuAddr;
	i32 tmp_mv0;
	u16 tmp_cuAddrNQT;

	local_numMvInfo = numMvInfo;
	local_numMvInfo = numMvInfo;
	if (local_numMvInfo == 1 || local_numMvInfo == 0) {
		i = 0;
		while (i <= 1) {
			j = 0;
			while (j <= 1) {
				tmp_mv = mv[0][i][j];
				tmp_cuAddr = cuAddr[j];
				mv[0][i][j] = tmp_mv - (tmp_cuAddr << 2);
				tmp_mv0 = mv[1][i][j];
				tmp_cuAddrNQT = cuAddrNQT[j];
				mv[1][i][j] = tmp_mv0 - (tmp_cuAddrNQT << 2);
				j = j + 1;
			}
			i = i + 1;
		}
	}

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
	u16 tmp_CUInfo0;
	u16 tmp_CUInfo1;
	u8 local_lcuSizeMax;
	u16 tmp_cuAddr;
	u16 tmp_CUInfo2;
	u16 tmp_cuAddr0;
	u16 tmp_CUInfo3;
	u16 tmp_CUInfo4;
	u16 tmp_list[2];
	u16 tmp_CUInfo5;
	u16 tmp_CUInfo6;
	u16 tmp_CUInfo7;
	u16 tmp_CUInfo8;
	u16 tmp_cuAddr1;
	u16 tmp_CUInfo9;
	u16 tmp_cuAddr2;
	u16 tmp_CUInfo10;
	u8 local_numPartDecoded;

	tmp_CUInfo = tokens_CUInfo[(index_CUInfo + (0)) % SIZE_CUInfo];
	cuMode = tmp_CUInfo;
	tmp_CUInfo0 = tokens_CUInfo[(index_CUInfo + (3)) % SIZE_CUInfo];
	nS = tmp_CUInfo0;
	tmp_CUInfo1 = tokens_CUInfo[(index_CUInfo + (1)) % SIZE_CUInfo];
	local_lcuSizeMax = lcuSizeMax;
	tmp_cuAddr = cuAddr[0];
	local_lcuSizeMax = lcuSizeMax;
	tmp_CUInfo2 = tokens_CUInfo[(index_CUInfo + (2)) % SIZE_CUInfo];
	local_lcuSizeMax = lcuSizeMax;
	tmp_cuAddr0 = cuAddr[1];
	local_lcuSizeMax = lcuSizeMax;
	if ((tmp_CUInfo1 & ~(local_lcuSizeMax - 1)) != (tmp_cuAddr & ~(local_lcuSizeMax - 1)) || (tmp_CUInfo2 & ~(local_lcuSizeMax - 1)) != (tmp_cuAddr0 & ~(local_lcuSizeMax - 1))) {
		tmp_CUInfo3 = tokens_CUInfo[(index_CUInfo + (1)) % SIZE_CUInfo];
		tmp_CUInfo4 = tokens_CUInfo[(index_CUInfo + (2)) % SIZE_CUInfo];
		findCurrTile(tmp_CUInfo3, tmp_CUInfo4);
		tmp_CUInfo5 = tokens_CUInfo[(index_CUInfo + (1)) % SIZE_CUInfo];
		tmp_list[0] = tmp_CUInfo5;
		tmp_CUInfo6 = tokens_CUInfo[(index_CUInfo + (2)) % SIZE_CUInfo];
		tmp_list[1] = tmp_CUInfo6;
		rstEdgeTables(tmp_list);
	}
	tmp_CUInfo7 = tokens_CUInfo[(index_CUInfo + (1)) % SIZE_CUInfo];
	cuAddr[0] = tmp_CUInfo7;
	tmp_CUInfo8 = tokens_CUInfo[(index_CUInfo + (2)) % SIZE_CUInfo];
	cuAddr[1] = tmp_CUInfo8;
	tmp_cuAddr1 = cuAddr[0];
	local_lcuSizeMax = lcuSizeMax;
	tmp_CUInfo9 = tokens_CUInfo[(index_CUInfo + (3)) % SIZE_CUInfo];
	coordMax1stPu[0] = ((tmp_cuAddr1 & local_lcuSizeMax - 1) + tmp_CUInfo9) >> 2;
	tmp_cuAddr2 = cuAddr[1];
	local_lcuSizeMax = lcuSizeMax;
	tmp_CUInfo10 = tokens_CUInfo[(index_CUInfo + (4)) % SIZE_CUInfo];
	coordMax1stPu[1] = ((tmp_cuAddr2 & local_lcuSizeMax - 1) + tmp_CUInfo10) >> 2;
	local_numPartDecoded = numPartDecoded;
	numPartDecoded = local_numPartDecoded + 1;

	// Update ports indexes
	index_CUInfo += 5;
	read_end_CUInfo();

	rate_CUInfo += 5;
}
static void getCuInfo_launch_aligned() {

	u16 tmp_CUInfo;
	u16 tmp_CUInfo0;
	u16 tmp_CUInfo1;
	u8 local_lcuSizeMax;
	u16 tmp_cuAddr;
	u16 tmp_CUInfo2;
	u16 tmp_cuAddr0;
	u16 tmp_CUInfo3;
	u16 tmp_CUInfo4;
	u16 tmp_list[2];
	u16 tmp_CUInfo5;
	u16 tmp_CUInfo6;
	u16 tmp_CUInfo7;
	u16 tmp_CUInfo8;
	u16 tmp_cuAddr1;
	u16 tmp_CUInfo9;
	u16 tmp_cuAddr2;
	u16 tmp_CUInfo10;
	u8 local_numPartDecoded;

	tmp_CUInfo = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (0)];
	cuMode = tmp_CUInfo;
	tmp_CUInfo0 = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (3)];
	nS = tmp_CUInfo0;
	tmp_CUInfo1 = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (1)];
	local_lcuSizeMax = lcuSizeMax;
	tmp_cuAddr = cuAddr[0];
	local_lcuSizeMax = lcuSizeMax;
	tmp_CUInfo2 = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (2)];
	local_lcuSizeMax = lcuSizeMax;
	tmp_cuAddr0 = cuAddr[1];
	local_lcuSizeMax = lcuSizeMax;
	if ((tmp_CUInfo1 & ~(local_lcuSizeMax - 1)) != (tmp_cuAddr & ~(local_lcuSizeMax - 1)) || (tmp_CUInfo2 & ~(local_lcuSizeMax - 1)) != (tmp_cuAddr0 & ~(local_lcuSizeMax - 1))) {
		tmp_CUInfo3 = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (1)];
		tmp_CUInfo4 = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (2)];
		findCurrTile(tmp_CUInfo3, tmp_CUInfo4);
		tmp_CUInfo5 = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (1)];
		tmp_list[0] = tmp_CUInfo5;
		tmp_CUInfo6 = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (2)];
		tmp_list[1] = tmp_CUInfo6;
		rstEdgeTables(tmp_list);
	}
	tmp_CUInfo7 = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (1)];
	cuAddr[0] = tmp_CUInfo7;
	tmp_CUInfo8 = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (2)];
	cuAddr[1] = tmp_CUInfo8;
	tmp_cuAddr1 = cuAddr[0];
	local_lcuSizeMax = lcuSizeMax;
	tmp_CUInfo9 = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (3)];
	coordMax1stPu[0] = ((tmp_cuAddr1 & local_lcuSizeMax - 1) + tmp_CUInfo9) >> 2;
	tmp_cuAddr2 = cuAddr[1];
	local_lcuSizeMax = lcuSizeMax;
	tmp_CUInfo10 = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (4)];
	coordMax1stPu[1] = ((tmp_cuAddr2 & local_lcuSizeMax - 1) + tmp_CUInfo10) >> 2;
	local_numPartDecoded = numPartDecoded;
	numPartDecoded = local_numPartDecoded + 1;

	// Update ports indexes
	index_CUInfo += 5;
	read_end_CUInfo();

	rate_CUInfo += 5;
}
static i32 isSchedulable_getCuInfo_nonQT() {
	i32 result;

	result = 1;
	return result;
}

static void getCuInfo_nonQT() {

	u8 puSize[2];
	u16 tmp_CUInfo;
	u16 tmp_CUInfo0;
	u8 local_lcuSizeMax;
	u16 tmp_cuAddr;
	u16 tmp_CUInfo1;
	u16 tmp_cuAddr0;
	u16 tmp_CUInfo2;
	u16 tmp_CUInfo3;
	u16 tmp_list[2];
	u16 tmp_CUInfo4;
	u16 tmp_CUInfo5;
	u16 tmp_CUInfo6;
	u16 tmp_CUInfo7;
	u16 tmp_CUInfo8;
	u16 tmp_CUInfo9;
	i32 i;
	i32 j;
	i32 tmp_mv;
	u16 tmp_cuAddr1;
	i32 tmp_mv0;
	u16 tmp_cuAddrNQT;
	u16 tmp_CUInfo10;
	u16 tmp_CUInfo11;
	i32 tmp_max;
	u16 tmp_CUInfo12;
	u16 tmp_CUInfo13;
	u16 tmp_CUInfo14;
	u16 tmp_CUInfo15;
	u16 tmp_CUInfo16;
	u16 tmp_CUInfo17;
	u16 tmp_CUInfo18;
	u16 tmp_CUInfo19;
	u16 tmp_cuAddr2;
	u16 tmp_CUInfo20;
	u16 tmp_cuAddr3;
	u16 tmp_CUInfo21;
	u16 tmp_cuAddr4;
	u16 tmp_CUInfo22;
	u16 tmp_cuAddr5;
	u16 tmp_CUInfo23;

	tmp_CUInfo = tokens_CUInfo[(index_CUInfo + (0)) % SIZE_CUInfo];
	cuMode = tmp_CUInfo;
	tmp_CUInfo0 = tokens_CUInfo[(index_CUInfo + (1)) % SIZE_CUInfo];
	local_lcuSizeMax = lcuSizeMax;
	tmp_cuAddr = cuAddr[0];
	local_lcuSizeMax = lcuSizeMax;
	tmp_CUInfo1 = tokens_CUInfo[(index_CUInfo + (2)) % SIZE_CUInfo];
	local_lcuSizeMax = lcuSizeMax;
	tmp_cuAddr0 = cuAddr[1];
	local_lcuSizeMax = lcuSizeMax;
	if ((tmp_CUInfo0 & ~(local_lcuSizeMax - 1)) != (tmp_cuAddr & ~(local_lcuSizeMax - 1)) || (tmp_CUInfo1 & ~(local_lcuSizeMax - 1)) != (tmp_cuAddr0 & ~(local_lcuSizeMax - 1))) {
		tmp_CUInfo2 = tokens_CUInfo[(index_CUInfo + (1)) % SIZE_CUInfo];
		tmp_CUInfo3 = tokens_CUInfo[(index_CUInfo + (2)) % SIZE_CUInfo];
		findCurrTile(tmp_CUInfo2, tmp_CUInfo3);
		tmp_CUInfo4 = tokens_CUInfo[(index_CUInfo + (1)) % SIZE_CUInfo];
		tmp_list[0] = tmp_CUInfo4;
		tmp_CUInfo5 = tokens_CUInfo[(index_CUInfo + (2)) % SIZE_CUInfo];
		tmp_list[1] = tmp_CUInfo5;
		rstEdgeTables(tmp_list);
	}
	tmp_CUInfo6 = tokens_CUInfo[(index_CUInfo + (1)) % SIZE_CUInfo];
	cuAddr[0] = tmp_CUInfo6;
	tmp_CUInfo7 = tokens_CUInfo[(index_CUInfo + (2)) % SIZE_CUInfo];
	cuAddr[1] = tmp_CUInfo7;
	tmp_CUInfo8 = tokens_CUInfo[(index_CUInfo + (6)) % SIZE_CUInfo];
	cuAddrNQT[0] = tmp_CUInfo8;
	tmp_CUInfo9 = tokens_CUInfo[(index_CUInfo + (7)) % SIZE_CUInfo];
	cuAddrNQT[1] = tmp_CUInfo9;
	i = 0;
	while (i <= 1) {
		j = 0;
		while (j <= 1) {
			tmp_mv = mv[0][i][j];
			tmp_cuAddr1 = cuAddr[j];
			mv[0][i][j] = tmp_mv - (tmp_cuAddr1 << 2);
			tmp_mv0 = mv[1][i][j];
			tmp_cuAddrNQT = cuAddrNQT[j];
			mv[1][i][j] = tmp_mv0 - (tmp_cuAddrNQT << 2);
			j = j + 1;
		}
		i = i + 1;
	}
	tmp_CUInfo10 = tokens_CUInfo[(index_CUInfo + (3)) % SIZE_CUInfo];
	tmp_CUInfo11 = tokens_CUInfo[(index_CUInfo + (4)) % SIZE_CUInfo];
	tmp_max = HevcDecoder_DBFilter_GenerateBs_max(tmp_CUInfo10, tmp_CUInfo11);
	nS = tmp_max;
	tmp_CUInfo12 = tokens_CUInfo[(index_CUInfo + (3)) % SIZE_CUInfo];
	puSize[0] = tmp_CUInfo12;
	tmp_CUInfo13 = tokens_CUInfo[(index_CUInfo + (4)) % SIZE_CUInfo];
	puSize[1] = tmp_CUInfo13;
	tmp_CUInfo14 = tokens_CUInfo[(index_CUInfo + (2)) % SIZE_CUInfo];
	tmp_CUInfo15 = tokens_CUInfo[(index_CUInfo + (7)) % SIZE_CUInfo];
	savePredPuEdge(cuAddr, puSize, tmp_CUInfo14 != tmp_CUInfo15);
	tmp_CUInfo16 = tokens_CUInfo[(index_CUInfo + (8)) % SIZE_CUInfo];
	puSize[0] = tmp_CUInfo16;
	tmp_CUInfo17 = tokens_CUInfo[(index_CUInfo + (9)) % SIZE_CUInfo];
	puSize[1] = tmp_CUInfo17;
	tmp_CUInfo18 = tokens_CUInfo[(index_CUInfo + (2)) % SIZE_CUInfo];
	tmp_CUInfo19 = tokens_CUInfo[(index_CUInfo + (7)) % SIZE_CUInfo];
	processPUBoundary(cuAddrNQT, puSize, tmp_CUInfo18 != tmp_CUInfo19);
	numPart = 2;
	numPartDecoded = 2;
	trafoTreeDepth = 0;
	trafoTreeIdx[0] = 3;
	tmp_cuAddr2 = cuAddr[0];
	local_lcuSizeMax = lcuSizeMax;
	tmp_CUInfo20 = tokens_CUInfo[(index_CUInfo + (3)) % SIZE_CUInfo];
	coordMax1stPu[0] = ((tmp_cuAddr2 & local_lcuSizeMax - 1) + tmp_CUInfo20) >> 2;
	tmp_cuAddr3 = cuAddr[0];
	tmp_CUInfo21 = tokens_CUInfo[(index_CUInfo + (3)) % SIZE_CUInfo];
	xAddr2ndPu = (tmp_cuAddr3 + tmp_CUInfo21) >> 2;
	tmp_cuAddr4 = cuAddr[1];
	tmp_CUInfo22 = tokens_CUInfo[(index_CUInfo + (4)) % SIZE_CUInfo];
	yAddr2ndPu = (tmp_cuAddr4 + tmp_CUInfo22) >> 2;
	tmp_cuAddr5 = cuAddr[1];
	local_lcuSizeMax = lcuSizeMax;
	tmp_CUInfo23 = tokens_CUInfo[(index_CUInfo + (4)) % SIZE_CUInfo];
	coordMax1stPu[1] = ((tmp_cuAddr5 & local_lcuSizeMax - 1) + tmp_CUInfo23) >> 2;

	// Update ports indexes
	index_CUInfo += 10;
	read_end_CUInfo();

	rate_CUInfo += 10;
}
static void getCuInfo_nonQT_aligned() {

	u8 puSize[2];
	u16 tmp_CUInfo;
	u16 tmp_CUInfo0;
	u8 local_lcuSizeMax;
	u16 tmp_cuAddr;
	u16 tmp_CUInfo1;
	u16 tmp_cuAddr0;
	u16 tmp_CUInfo2;
	u16 tmp_CUInfo3;
	u16 tmp_list[2];
	u16 tmp_CUInfo4;
	u16 tmp_CUInfo5;
	u16 tmp_CUInfo6;
	u16 tmp_CUInfo7;
	u16 tmp_CUInfo8;
	u16 tmp_CUInfo9;
	i32 i;
	i32 j;
	i32 tmp_mv;
	u16 tmp_cuAddr1;
	i32 tmp_mv0;
	u16 tmp_cuAddrNQT;
	u16 tmp_CUInfo10;
	u16 tmp_CUInfo11;
	i32 tmp_max;
	u16 tmp_CUInfo12;
	u16 tmp_CUInfo13;
	u16 tmp_CUInfo14;
	u16 tmp_CUInfo15;
	u16 tmp_CUInfo16;
	u16 tmp_CUInfo17;
	u16 tmp_CUInfo18;
	u16 tmp_CUInfo19;
	u16 tmp_cuAddr2;
	u16 tmp_CUInfo20;
	u16 tmp_cuAddr3;
	u16 tmp_CUInfo21;
	u16 tmp_cuAddr4;
	u16 tmp_CUInfo22;
	u16 tmp_cuAddr5;
	u16 tmp_CUInfo23;

	tmp_CUInfo = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (0)];
	cuMode = tmp_CUInfo;
	tmp_CUInfo0 = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (1)];
	local_lcuSizeMax = lcuSizeMax;
	tmp_cuAddr = cuAddr[0];
	local_lcuSizeMax = lcuSizeMax;
	tmp_CUInfo1 = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (2)];
	local_lcuSizeMax = lcuSizeMax;
	tmp_cuAddr0 = cuAddr[1];
	local_lcuSizeMax = lcuSizeMax;
	if ((tmp_CUInfo0 & ~(local_lcuSizeMax - 1)) != (tmp_cuAddr & ~(local_lcuSizeMax - 1)) || (tmp_CUInfo1 & ~(local_lcuSizeMax - 1)) != (tmp_cuAddr0 & ~(local_lcuSizeMax - 1))) {
		tmp_CUInfo2 = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (1)];
		tmp_CUInfo3 = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (2)];
		findCurrTile(tmp_CUInfo2, tmp_CUInfo3);
		tmp_CUInfo4 = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (1)];
		tmp_list[0] = tmp_CUInfo4;
		tmp_CUInfo5 = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (2)];
		tmp_list[1] = tmp_CUInfo5;
		rstEdgeTables(tmp_list);
	}
	tmp_CUInfo6 = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (1)];
	cuAddr[0] = tmp_CUInfo6;
	tmp_CUInfo7 = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (2)];
	cuAddr[1] = tmp_CUInfo7;
	tmp_CUInfo8 = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (6)];
	cuAddrNQT[0] = tmp_CUInfo8;
	tmp_CUInfo9 = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (7)];
	cuAddrNQT[1] = tmp_CUInfo9;
	i = 0;
	while (i <= 1) {
		j = 0;
		while (j <= 1) {
			tmp_mv = mv[0][i][j];
			tmp_cuAddr1 = cuAddr[j];
			mv[0][i][j] = tmp_mv - (tmp_cuAddr1 << 2);
			tmp_mv0 = mv[1][i][j];
			tmp_cuAddrNQT = cuAddrNQT[j];
			mv[1][i][j] = tmp_mv0 - (tmp_cuAddrNQT << 2);
			j = j + 1;
		}
		i = i + 1;
	}
	tmp_CUInfo10 = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (3)];
	tmp_CUInfo11 = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (4)];
	tmp_max = HevcDecoder_DBFilter_GenerateBs_max(tmp_CUInfo10, tmp_CUInfo11);
	nS = tmp_max;
	tmp_CUInfo12 = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (3)];
	puSize[0] = tmp_CUInfo12;
	tmp_CUInfo13 = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (4)];
	puSize[1] = tmp_CUInfo13;
	tmp_CUInfo14 = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (2)];
	tmp_CUInfo15 = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (7)];
	savePredPuEdge(cuAddr, puSize, tmp_CUInfo14 != tmp_CUInfo15);
	tmp_CUInfo16 = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (8)];
	puSize[0] = tmp_CUInfo16;
	tmp_CUInfo17 = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (9)];
	puSize[1] = tmp_CUInfo17;
	tmp_CUInfo18 = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (2)];
	tmp_CUInfo19 = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (7)];
	processPUBoundary(cuAddrNQT, puSize, tmp_CUInfo18 != tmp_CUInfo19);
	numPart = 2;
	numPartDecoded = 2;
	trafoTreeDepth = 0;
	trafoTreeIdx[0] = 3;
	tmp_cuAddr2 = cuAddr[0];
	local_lcuSizeMax = lcuSizeMax;
	tmp_CUInfo20 = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (3)];
	coordMax1stPu[0] = ((tmp_cuAddr2 & local_lcuSizeMax - 1) + tmp_CUInfo20) >> 2;
	tmp_cuAddr3 = cuAddr[0];
	tmp_CUInfo21 = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (3)];
	xAddr2ndPu = (tmp_cuAddr3 + tmp_CUInfo21) >> 2;
	tmp_cuAddr4 = cuAddr[1];
	tmp_CUInfo22 = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (4)];
	yAddr2ndPu = (tmp_cuAddr4 + tmp_CUInfo22) >> 2;
	tmp_cuAddr5 = cuAddr[1];
	local_lcuSizeMax = lcuSizeMax;
	tmp_CUInfo23 = tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (4)];
	coordMax1stPu[1] = ((tmp_cuAddr5 & local_lcuSizeMax - 1) + tmp_CUInfo23) >> 2;

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

	u8 local_nS;
	i32 idxMax;
	i32 i;

	local_nS = nS;
	local_nS = nS;
	idxMax = local_nS * local_nS / 32;
	i = 0;
	while (i <= idxMax - 1) {
		bsTable[0][i] = 0;
		bsTable[1][i] = 0;
		i = i + 1;
	}

	// Update ports indexes

}
static i32 isSchedulable_getCuMode_isNotOther() {
	i32 result;
	u8 local_cuMode;
	u8 local_INTER;
	u8 local_SKIP;
	u8 local_INTRA;

	local_cuMode = cuMode;
	local_INTER = HevcDecoder_DBFilter_GenerateBs_INTER;
	local_cuMode = cuMode;
	local_SKIP = HevcDecoder_DBFilter_GenerateBs_SKIP;
	local_cuMode = cuMode;
	local_INTRA = HevcDecoder_DBFilter_GenerateBs_INTRA;
	result = local_cuMode == local_INTER || local_cuMode == local_SKIP || local_cuMode == local_INTRA;
	return result;
}

static void getCuMode_isNotOther() {

	u8 local_cuMode;
	u8 local_INTRA;

	trafoTreeDepth = 0;
	trafoTreeIdx[0] = 3;
	currIdx = 0;
	currIdxHor = 0;
	currIdxVer = 0;
	local_cuMode = cuMode;
	local_INTRA = HevcDecoder_DBFilter_GenerateBs_INTRA;
	if (local_cuMode == local_INTRA) {
		numMvInfo = 0;
	} else {
		numMvInfo = 1;
	}

	// Update ports indexes

}
static i32 isSchedulable_getCuMode_isOther() {
	i32 result;
	u8 local_cuMode;
	u8 local_OTHER;

	local_cuMode = cuMode;
	local_OTHER = HevcDecoder_DBFilter_GenerateBs_OTHER;
	result = local_cuMode == local_OTHER;
	return result;
}

static void getCuMode_isOther() {



	// Update ports indexes

}
static i32 isSchedulable_getSplitTrafo_launch_isTrue() {
	i32 result;
	i32 splitTrafo;
	i8 local_trafoTreeDepth;

	splitTrafo = tokens_SplitTransf[(index_SplitTransf + (0)) % SIZE_SplitTransf];
	local_trafoTreeDepth = trafoTreeDepth;
	result = local_trafoTreeDepth > -1 && splitTrafo;
	return result;
}

static void getSplitTrafo_launch_isTrue() {

	i32 splitTrafo;
	i8 local_trafoTreeDepth;

	splitTrafo = tokens_SplitTransf[(index_SplitTransf + (0)) % SIZE_SplitTransf];
	local_trafoTreeDepth = trafoTreeDepth;
	trafoTreeDepth = local_trafoTreeDepth + 1;
	local_trafoTreeDepth = trafoTreeDepth;
	trafoTreeIdx[local_trafoTreeDepth] = 0;

	// Update ports indexes
	index_SplitTransf += 1;

	rate_SplitTransf += 1;
}
static i32 isSchedulable_getSplitTrafo_launch_isFalse() {
	i32 result;
	i32 splitTrafo;
	i8 local_trafoTreeDepth;

	splitTrafo = tokens_SplitTransf[(index_SplitTransf + (0)) % SIZE_SplitTransf];
	local_trafoTreeDepth = trafoTreeDepth;
	result = local_trafoTreeDepth > -1 && !splitTrafo;
	return result;
}

static void getSplitTrafo_launch_isFalse() {

	i32 splitTrafo;
	i32 cbf;
	u8 partIdx;
	u8 treeNS;
	u16 treeAddr[2];
	u16 xMin;
	u16 xMax;
	u16 yMin;
	u16 yMax;
	u8 local_nS;
	i32 i;
	u16 tmp_cuAddr;
	u32 idx;
	i8 local_trafoTreeDepth;
	u8 tmp_trafoTreeIdx;
	u16 tmp_treeAddr;
	u8 tmp_trafoTreeIdx0;
	u16 tmp_treeAddr0;
	i32 i0;
	u16 tmp_treeAddr1;
	u16 tmp_treeAddr2;
	u8 local_lcuSizeMax;
	u16 tmp_treeAddr3;
	i32 x;
	u16 tmp_treeAddrInBlk;
	u8 local_numMvInfo;
	i16 local_xAddr2ndPu;
	i16 tmp_coordMax1stPu;
	i32 i1;
	i32 tmp_mv;
	i32 tmp_mv0;
	i16 tmp_refPoc;
	i32 y;
	u16 tmp_treeAddrInBlk0;
	i16 tmp_coordMax1stPu0;
	i16 tmp_coordMax1stPu1;
	i32 i2;
	u16 tmp_treeAddrInBlk1;
	i32 tmp_mv1;
	u16 tmp_treeAddrInBlk2;
	i32 tmp_mv2;
	u16 tmp_treeAddrInBlk3;
	i16 tmp_refPoc0;
	u8 tmp_trafoTreeIdx1;
	i32 tmp_if;
	u8 tmp_trafoTreeIdx2;
	u8 tmp_trafoTreeIdx3;

	splitTrafo = tokens_SplitTransf[(index_SplitTransf + (0)) % SIZE_SplitTransf];
	cbf = tokens_Cbf[(index_Cbf + (0)) % SIZE_Cbf];
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
	i0 = 0;
	while (i0 <= 1) {
		tmp_treeAddr1 = treeAddr[i0];
		treeAddrInBlk[i0] = tmp_treeAddr1 >> 2;
		i0 = i0 + 1;
	}
	savePredInfoTu(treeAddrInBlk, treeNS >> 2);
	tmp_treeAddr2 = treeAddr[0];
	local_lcuSizeMax = lcuSizeMax;
	xMin = (tmp_treeAddr2 & local_lcuSizeMax - 1) >> 2;
	xMax = xMin + (treeNS >> 2);
	tmp_treeAddr3 = treeAddr[1];
	local_lcuSizeMax = lcuSizeMax;
	yMin = (tmp_treeAddr3 & local_lcuSizeMax - 1) >> 2;
	yMax = yMin + (treeNS >> 2);
	processTUBoundaries(cbf, treeAddr, treeNS);
	x = treeAddrInBlk[0];
	tmp_treeAddrInBlk = treeAddrInBlk[0];
	while (x <= tmp_treeAddrInBlk + (treeNS >> 2) - 1) {
		cbfUpNeighb[x] = cbf;
		local_numMvInfo = numMvInfo;
		local_xAddr2ndPu = xAddr2ndPu;
		tmp_coordMax1stPu = coordMax1stPu[1];
		partIdx = HevcDecoder_DBFilter_GenerateBs_castBoolToInt(!(local_numMvInfo == 1 || x < local_xAddr2ndPu && yMax - 1 < tmp_coordMax1stPu));
		i1 = 0;
		while (i1 <= 1) {
			tmp_mv = mv[partIdx][i1][0];
			mvUpNeighb[x][i1][0] = tmp_mv;
			tmp_mv0 = mv[partIdx][i1][1];
			mvUpNeighb[x][i1][1] = tmp_mv0;
			tmp_refPoc = refPoc[partIdx][i1];
			refPocUpNeighb[x][i1] = tmp_refPoc;
			i1 = i1 + 1;
		}
		x = x + 1;
	}
	y = yMin;
	while (y <= yMax - 1) {
		tmp_treeAddrInBlk0 = treeAddrInBlk[1];
		cbfLeftNeighb[tmp_treeAddrInBlk0 + y - yMin] = cbf;
		local_numMvInfo = numMvInfo;
		tmp_coordMax1stPu0 = coordMax1stPu[0];
		tmp_coordMax1stPu1 = coordMax1stPu[1];
		partIdx = HevcDecoder_DBFilter_GenerateBs_castBoolToInt(!(local_numMvInfo == 1 || xMax - 1 < tmp_coordMax1stPu0 && y < tmp_coordMax1stPu1));
		i2 = 0;
		while (i2 <= 1) {
			tmp_treeAddrInBlk1 = treeAddrInBlk[1];
			tmp_mv1 = mv[partIdx][i2][0];
			mvLeftNeighb[tmp_treeAddrInBlk1 + y - yMin][i2][0] = tmp_mv1;
			tmp_treeAddrInBlk2 = treeAddrInBlk[1];
			tmp_mv2 = mv[partIdx][i2][1];
			mvLeftNeighb[tmp_treeAddrInBlk2 + y - yMin][i2][1] = tmp_mv2;
			tmp_treeAddrInBlk3 = treeAddrInBlk[1];
			tmp_refPoc0 = refPoc[partIdx][i2];
			refPocLeftNeighb[tmp_treeAddrInBlk3 + y - yMin][i2] = tmp_refPoc0;
			i2 = i2 + 1;
		}
		y = y + 1;
	}
	nbBlkToSend = treeNS * treeNS / 16;
	local_trafoTreeDepth = trafoTreeDepth;
	local_trafoTreeDepth = trafoTreeDepth;
	tmp_trafoTreeIdx1 = trafoTreeIdx[local_trafoTreeDepth];
	trafoTreeIdx[local_trafoTreeDepth] = tmp_trafoTreeIdx1 + 1;
	local_trafoTreeDepth = trafoTreeDepth;
	if (local_trafoTreeDepth > -1) {
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
		if (local_trafoTreeDepth > -1) {
			local_trafoTreeDepth = trafoTreeDepth;
			tmp_trafoTreeIdx2 = trafoTreeIdx[local_trafoTreeDepth];
			tmp_if = tmp_trafoTreeIdx2 == 4;
		} else {
			tmp_if = 0;
		}
	}

	// Update ports indexes
	index_SplitTransf += 1;
	index_Cbf += 1;

	rate_SplitTransf += 1;
	rate_Cbf += 1;
}
static i32 isSchedulable_getSplitTrafo_done() {
	i32 result;
	i8 local_trafoTreeDepth;

	local_trafoTreeDepth = trafoTreeDepth;
	result = local_trafoTreeDepth == -1;
	return result;
}

static void getSplitTrafo_done() {

	u16 tmp_absCoordToZScan;
	u16 tmp_absCoordToZScan2;
	u16 tmp_absCoordToZScan3;

	tmp_absCoordToZScan = HevcDecoder_DBFilter_GenerateBs_absCoordToZScan(cuAddr);
	currIdx = tmp_absCoordToZScan;
	tmp_absCoordToZScan2 = HevcDecoder_DBFilter_GenerateBs_absCoordToZScan2(cuAddr);
	currIdxHor = tmp_absCoordToZScan2;
	tmp_absCoordToZScan3 = HevcDecoder_DBFilter_GenerateBs_absCoordToZScan3(cuAddr);
	currIdxVer = tmp_absCoordToZScan3;

	// Update ports indexes

}
static i32 isSchedulable_sendBS_launch_is4x4_isbSHorVer() {
	i32 result;
	i16 local_nbBlkToSend;
	u16 tmp_treeAddrInBlk;
	u16 tmp_treeAddrInBlk0;

	local_nbBlkToSend = nbBlkToSend;
	tmp_treeAddrInBlk = treeAddrInBlk[0];
	tmp_treeAddrInBlk0 = treeAddrInBlk[1];
	result = local_nbBlkToSend == 1 && (tmp_treeAddrInBlk & 1) != 1 && (tmp_treeAddrInBlk0 & 1) != 1;
	return result;
}

static void sendBS_launch_is4x4_isbSHorVer() {

	u8 bsHor;
	u8 bsVer;
	u16 local_currIdxHor;
	u16 local_currIdxVer;

	local_currIdxHor = currIdxHor;
	bsHor = bsTable[1][local_currIdxHor];
	local_currIdxVer = currIdxVer;
	bsVer = bsTable[0][local_currIdxVer];
	local_currIdxVer = currIdxVer;
	bsTable[0][local_currIdxVer] = 0;
	local_currIdxHor = currIdxHor;
	bsTable[1][local_currIdxHor] = 0;
	local_currIdxHor = currIdxHor;
	currIdxHor = local_currIdxHor + 1;
	local_currIdxVer = currIdxVer;
	currIdxVer = local_currIdxVer + 1;
	tokens_BSHor[(index_BSHor + (0)) % SIZE_BSHor] = bsHor;
	tokens_BSVer[(index_BSVer + (0)) % SIZE_BSVer] = bsVer;

	// Update ports indexes
	index_BSHor += 1;
	index_BSVer += 1;

}
static i32 isSchedulable_sendBS_launch_is4x4_isbSHor() {
	i32 result;
	i16 local_nbBlkToSend;
	u16 tmp_treeAddrInBlk;

	local_nbBlkToSend = nbBlkToSend;
	tmp_treeAddrInBlk = treeAddrInBlk[1];
	result = local_nbBlkToSend == 1 && (tmp_treeAddrInBlk & 1) != 1;
	return result;
}

static void sendBS_launch_is4x4_isbSHor() {

	u8 bsHor;
	u16 local_currIdxHor;

	local_currIdxHor = currIdxHor;
	bsHor = bsTable[1][local_currIdxHor];
	local_currIdxHor = currIdxHor;
	bsTable[1][local_currIdxHor] = 0;
	local_currIdxHor = currIdxHor;
	currIdxHor = local_currIdxHor + 1;
	tokens_BSHor[(index_BSHor + (0)) % SIZE_BSHor] = bsHor;

	// Update ports indexes
	index_BSHor += 1;

}
static i32 isSchedulable_sendBS_launch_is4x4_isbSVer() {
	i32 result;
	i16 local_nbBlkToSend;
	u16 tmp_treeAddrInBlk;

	local_nbBlkToSend = nbBlkToSend;
	tmp_treeAddrInBlk = treeAddrInBlk[0];
	result = local_nbBlkToSend == 1 && (tmp_treeAddrInBlk & 1) != 1;
	return result;
}

static void sendBS_launch_is4x4_isbSVer() {

	u8 bsVer;
	u16 local_currIdxVer;

	local_currIdxVer = currIdxVer;
	bsVer = bsTable[0][local_currIdxVer];
	local_currIdxVer = currIdxVer;
	bsTable[0][local_currIdxVer] = 0;
	local_currIdxVer = currIdxVer;
	currIdxVer = local_currIdxVer + 1;
	tokens_BSVer[(index_BSVer + (0)) % SIZE_BSVer] = bsVer;

	// Update ports indexes
	index_BSVer += 1;

}
static i32 isSchedulable_sendBS_launch_is4x4() {
	i32 result;
	i16 local_nbBlkToSend;

	local_nbBlkToSend = nbBlkToSend;
	result = local_nbBlkToSend == 1;
	return result;
}

static void sendBS_launch_is4x4() {



	// Update ports indexes

}
static i32 isSchedulable_sendBS_launch_is8x8() {
	i32 result;
	i16 local_nbBlkToSend;

	local_nbBlkToSend = nbBlkToSend;
	result = local_nbBlkToSend == 4;
	return result;
}

static void sendBS_launch_is8x8() {

	u32 i;
	u16 local_currIdxVer;
	u8 tmp_bsTable;
	u16 local_currIdxHor;
	u8 tmp_bsTable0;

	i = 0;
	while (i <= 1) {
		local_currIdxVer = currIdxVer;
		tmp_bsTable = bsTable[0][local_currIdxVer + i];
		tokens_BSVer[(index_BSVer + (i)) % SIZE_BSVer] = tmp_bsTable;
		local_currIdxHor = currIdxHor;
		tmp_bsTable0 = bsTable[1][local_currIdxHor + i];
		tokens_BSHor[(index_BSHor + (i)) % SIZE_BSHor] = tmp_bsTable0;
		i = i + 1;
	}
	local_currIdxHor = currIdxHor;
	currIdxHor = local_currIdxHor + 2;
	local_currIdxVer = currIdxVer;
	currIdxVer = local_currIdxVer + 2;

	// Update ports indexes
	index_BSHor += 2;
	write_end_BSHor();
	index_BSVer += 2;
	write_end_BSVer();

}
static void sendBS_launch_is8x8_aligned() {

	u32 i;
	u16 local_currIdxVer;
	u8 tmp_bsTable;
	u16 local_currIdxHor;
	u8 tmp_bsTable0;

	i = 0;
	while (i <= 1) {
		local_currIdxVer = currIdxVer;
		tmp_bsTable = bsTable[0][local_currIdxVer + i];
		tokens_BSVer[(index_BSVer % SIZE_BSVer) + (i)] = tmp_bsTable;
		local_currIdxHor = currIdxHor;
		tmp_bsTable0 = bsTable[1][local_currIdxHor + i];
		tokens_BSHor[(index_BSHor % SIZE_BSHor) + (i)] = tmp_bsTable0;
		i = i + 1;
	}
	local_currIdxHor = currIdxHor;
	currIdxHor = local_currIdxHor + 2;
	local_currIdxVer = currIdxVer;
	currIdxVer = local_currIdxVer + 2;

	// Update ports indexes
	index_BSHor += 2;
	write_end_BSHor();
	index_BSVer += 2;
	write_end_BSVer();

}
static i32 isSchedulable_sendBS_launch_is16x16() {
	i32 result;
	i16 local_nbBlkToSend;

	local_nbBlkToSend = nbBlkToSend;
	result = local_nbBlkToSend == 16;
	return result;
}

static void sendBS_launch_is16x16() {

	u32 i;
	u16 local_currIdxVer;
	u8 tmp_bsTable;
	u16 local_currIdxHor;
	u8 tmp_bsTable0;

	i = 0;
	while (i <= 7) {
		local_currIdxVer = currIdxVer;
		tmp_bsTable = bsTable[0][local_currIdxVer + i];
		tokens_BSVer[(index_BSVer + (i)) % SIZE_BSVer] = tmp_bsTable;
		local_currIdxHor = currIdxHor;
		tmp_bsTable0 = bsTable[1][local_currIdxHor + i];
		tokens_BSHor[(index_BSHor + (i)) % SIZE_BSHor] = tmp_bsTable0;
		i = i + 1;
	}
	local_currIdxHor = currIdxHor;
	currIdxHor = local_currIdxHor + 8;
	local_currIdxVer = currIdxVer;
	currIdxVer = local_currIdxVer + 8;

	// Update ports indexes
	index_BSHor += 8;
	write_end_BSHor();
	index_BSVer += 8;
	write_end_BSVer();

}
static void sendBS_launch_is16x16_aligned() {

	u32 i;
	u16 local_currIdxVer;
	u8 tmp_bsTable;
	u16 local_currIdxHor;
	u8 tmp_bsTable0;

	i = 0;
	while (i <= 7) {
		local_currIdxVer = currIdxVer;
		tmp_bsTable = bsTable[0][local_currIdxVer + i];
		tokens_BSVer[(index_BSVer % SIZE_BSVer) + (i)] = tmp_bsTable;
		local_currIdxHor = currIdxHor;
		tmp_bsTable0 = bsTable[1][local_currIdxHor + i];
		tokens_BSHor[(index_BSHor % SIZE_BSHor) + (i)] = tmp_bsTable0;
		i = i + 1;
	}
	local_currIdxHor = currIdxHor;
	currIdxHor = local_currIdxHor + 8;
	local_currIdxVer = currIdxVer;
	currIdxVer = local_currIdxVer + 8;

	// Update ports indexes
	index_BSHor += 8;
	write_end_BSHor();
	index_BSVer += 8;
	write_end_BSVer();

}
static i32 isSchedulable_sendBS_launch_is32x32() {
	i32 result;
	i16 local_nbBlkToSend;

	local_nbBlkToSend = nbBlkToSend;
	result = local_nbBlkToSend == 64;
	return result;
}

static void sendBS_launch_is32x32() {

	u32 i;
	u16 local_currIdxVer;
	u8 tmp_bsTable;
	u16 local_currIdxHor;
	u8 tmp_bsTable0;

	i = 0;
	while (i <= 31) {
		local_currIdxVer = currIdxVer;
		tmp_bsTable = bsTable[0][local_currIdxVer + i];
		tokens_BSVer[(index_BSVer + (i)) % SIZE_BSVer] = tmp_bsTable;
		local_currIdxHor = currIdxHor;
		tmp_bsTable0 = bsTable[1][local_currIdxHor + i];
		tokens_BSHor[(index_BSHor + (i)) % SIZE_BSHor] = tmp_bsTable0;
		i = i + 1;
	}
	local_currIdxHor = currIdxHor;
	currIdxHor = local_currIdxHor + 32;
	local_currIdxVer = currIdxVer;
	currIdxVer = local_currIdxVer + 32;

	// Update ports indexes
	index_BSHor += 32;
	write_end_BSHor();
	index_BSVer += 32;
	write_end_BSVer();

}
static void sendBS_launch_is32x32_aligned() {

	u32 i;
	u16 local_currIdxVer;
	u8 tmp_bsTable;
	u16 local_currIdxHor;
	u8 tmp_bsTable0;

	i = 0;
	while (i <= 31) {
		local_currIdxVer = currIdxVer;
		tmp_bsTable = bsTable[0][local_currIdxVer + i];
		tokens_BSVer[(index_BSVer % SIZE_BSVer) + (i)] = tmp_bsTable;
		local_currIdxHor = currIdxHor;
		tmp_bsTable0 = bsTable[1][local_currIdxHor + i];
		tokens_BSHor[(index_BSHor % SIZE_BSHor) + (i)] = tmp_bsTable0;
		i = i + 1;
	}
	local_currIdxHor = currIdxHor;
	currIdxHor = local_currIdxHor + 32;
	local_currIdxVer = currIdxVer;
	currIdxVer = local_currIdxVer + 32;

	// Update ports indexes
	index_BSHor += 32;
	write_end_BSHor();
	index_BSVer += 32;
	write_end_BSVer();

}
static i32 isSchedulable_sendBS_launch_is64x64() {
	i32 result;
	i16 local_nbBlkToSend;

	local_nbBlkToSend = nbBlkToSend;
	result = local_nbBlkToSend == 256;
	return result;
}

static void sendBS_launch_is64x64() {

	u32 i;
	u16 local_currIdxVer;
	u8 tmp_bsTable;
	u16 local_currIdxHor;
	u8 tmp_bsTable0;

	i = 0;
	while (i <= 127) {
		local_currIdxVer = currIdxVer;
		tmp_bsTable = bsTable[0][local_currIdxVer + i];
		tokens_BSVer[(index_BSVer + (i)) % SIZE_BSVer] = tmp_bsTable;
		local_currIdxHor = currIdxHor;
		tmp_bsTable0 = bsTable[1][local_currIdxHor + i];
		tokens_BSHor[(index_BSHor + (i)) % SIZE_BSHor] = tmp_bsTable0;
		i = i + 1;
	}
	local_currIdxHor = currIdxHor;
	currIdxHor = local_currIdxHor + 128;
	local_currIdxVer = currIdxVer;
	currIdxVer = local_currIdxVer + 128;

	// Update ports indexes
	index_BSHor += 128;
	write_end_BSHor();
	index_BSVer += 128;
	write_end_BSVer();

}
static void sendBS_launch_is64x64_aligned() {

	u32 i;
	u16 local_currIdxVer;
	u8 tmp_bsTable;
	u16 local_currIdxHor;
	u8 tmp_bsTable0;

	i = 0;
	while (i <= 127) {
		local_currIdxVer = currIdxVer;
		tmp_bsTable = bsTable[0][local_currIdxVer + i];
		tokens_BSVer[(index_BSVer % SIZE_BSVer) + (i)] = tmp_bsTable;
		local_currIdxHor = currIdxHor;
		tmp_bsTable0 = bsTable[1][local_currIdxHor + i];
		tokens_BSHor[(index_BSHor % SIZE_BSHor) + (i)] = tmp_bsTable0;
		i = i + 1;
	}
	local_currIdxHor = currIdxHor;
	currIdxHor = local_currIdxHor + 128;
	local_currIdxVer = currIdxVer;
	currIdxVer = local_currIdxVer + 128;

	// Update ports indexes
	index_BSHor += 128;
	write_end_BSHor();
	index_BSVer += 128;
	write_end_BSVer();

}

////////////////////////////////////////////////////////////////////////////////
// Initializes
static i32 isSchedulable_untagged_0() {
	i32 result;

	result = 1;
	return result;
}

static void untagged_0() {

	i32 j;
	i32 i;

	j = 0;
	while (j <= 1) {
		i = 0;
		while (i <= 127) {
			bsTable[j][i] = 0;
			i = i + 1;
		}
		j = j + 1;
	}

	// Update ports indexes

}

void HevcDecoder_DBFilter_GenerateBs_initialize(schedinfo_t *si) {
	int i = 0;
	write_BSHor();
	write_BSVer();
	/* Set initial state to current FSM state */
	_FSM_state = my_state_GetPartMode;
	if(isSchedulable_untagged_0()) {
		untagged_0();
	}
finished:
	write_end_BSHor();
	write_end_BSVer();
	return;
}

////////////////////////////////////////////////////////////////////////////////
// Action scheduler

void HevcDecoder_DBFilter_GenerateBs_scheduler(schedinfo_t *si) {
	int i = 0;

	read_Cbf();
	read_CUInfo();
	read_IsBiPredOrLx();
	read_LcuSizeMax();
	read_LFAcrossSlcTile();
	read_Mv();
	read_PartMode();
	read_RefPoc();
	read_SliceAddr();
	read_SplitTransf();
	read_TilesCoord();
	write_BSHor();
	write_BSVer();

	// jump to FSM state
	switch (_FSM_state) {
	case my_state_GetCuInfo:
		goto l_GetCuInfo;
	case my_state_GetCuInfoNonQT:
		goto l_GetCuInfoNonQT;
	case my_state_GetCuMode:
		goto l_GetCuMode;
	case my_state_GetPartMode:
		goto l_GetPartMode;
	case my_state_GetRefPictInfo:
		goto l_GetRefPictInfo;
	case my_state_GetRefPictInfo1:
		goto l_GetRefPictInfo1;
	case my_state_GetSplitTrafo:
		goto l_GetSplitTrafo;
	case my_state_GetTilesCoord:
		goto l_GetTilesCoord;
	case my_state_SendBS:
		goto l_SendBS;
	default:
		printf("unknown state in HevcDecoder_DBFilter_GenerateBs.c : %s\n", stateNames[_FSM_state]);
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
	if (numTokens_CUInfo - index_CUInfo >= 10 && isSchedulable_getCuInfo_nonQT()) {
		{
			int isAligned = 1;
			isAligned &= ((index_CUInfo % SIZE_CUInfo) < ((index_CUInfo + 10) % SIZE_CUInfo));
			if (isAligned) {
				getCuInfo_nonQT_aligned();
			} else {
				getCuInfo_nonQT();
			}
		}
		i++;
		goto l_GetSplitTrafo;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetCuInfoNonQT;
		goto finished;
	}
l_GetCuMode:
	if (isSchedulable_getCuMode_isNotOther()) {
		getCuMode_isNotOther();
		i++;
		goto l_GetRefPictInfo;
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
l_GetPartMode:
	if (numTokens_LcuSizeMax - index_LcuSizeMax >= 1 && numTokens_PartMode - index_PartMode >= 1 && numTokens_SliceAddr - index_SliceAddr >= 2 && numTokens_LFAcrossSlcTile - index_LFAcrossSlcTile >= 1 && numTokens_TilesCoord - index_TilesCoord >= 1 && isSchedulable_isNewSliceOrPict_isNotDep()) {
		{
			int isAligned = 1;
			isAligned &= ((index_SliceAddr % SIZE_SliceAddr) < ((index_SliceAddr + 2) % SIZE_SliceAddr));
			if (isAligned) {
				isNewSliceOrPict_isNotDep_aligned();
			} else {
				isNewSliceOrPict_isNotDep();
			}
		}
		i++;
		goto l_GetTilesCoord;
	} else if (numTokens_PartMode - index_PartMode >= 1 && numTokens_SliceAddr - index_SliceAddr >= 2 && isSchedulable_isNewSliceOrPict_isDep()) {
		{
			int isAligned = 1;
			isAligned &= ((index_SliceAddr % SIZE_SliceAddr) < ((index_SliceAddr + 2) % SIZE_SliceAddr));
			if (isAligned) {
				isNewSliceOrPict_isDep_aligned();
			} else {
				isNewSliceOrPict_isDep();
			}
		}
		i++;
		goto l_GetPartMode;
	} else if (numTokens_PartMode - index_PartMode >= 1 && isSchedulable_getPartMode_isNonQuadTree()) {
		getPartMode_isNonQuadTree();
		i++;
		goto l_GetRefPictInfo1;
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
l_GetRefPictInfo:
	if (numTokens_IsBiPredOrLx - index_IsBiPredOrLx >= 1 && numTokens_RefPoc - index_RefPoc >= 1 && numTokens_Mv - index_Mv >= 2 && isSchedulable_getRefPictInfo_launch_isNotBiPred()) {
		{
			int isAligned = 1;
			isAligned &= ((index_Mv % SIZE_Mv) < ((index_Mv + 2) % SIZE_Mv));
			if (isAligned) {
				getRefPictInfo_launch_isNotBiPred_aligned();
			} else {
				getRefPictInfo_launch_isNotBiPred();
			}
		}
		i++;
		goto l_GetRefPictInfo;
	} else if (numTokens_IsBiPredOrLx - index_IsBiPredOrLx >= 1 && numTokens_RefPoc - index_RefPoc >= 2 && numTokens_Mv - index_Mv >= 4 && isSchedulable_getRefPictInfo_launch_isBiPred()) {
		{
			int isAligned = 1;
			isAligned &= ((index_RefPoc % SIZE_RefPoc) < ((index_RefPoc + 2) % SIZE_RefPoc));
			isAligned &= ((index_Mv % SIZE_Mv) < ((index_Mv + 4) % SIZE_Mv));
			if (isAligned) {
				getRefPictInfo_launch_isBiPred_aligned();
			} else {
				getRefPictInfo_launch_isBiPred();
			}
		}
		i++;
		goto l_GetRefPictInfo;
	} else if (isSchedulable_getRefPictInfo_done()) {
		getRefPictInfo_done();
		i++;
		goto l_GetSplitTrafo;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetRefPictInfo;
		goto finished;
	}
l_GetRefPictInfo1:
	if (numTokens_IsBiPredOrLx - index_IsBiPredOrLx >= 1 && numTokens_RefPoc - index_RefPoc >= 1 && numTokens_Mv - index_Mv >= 2 && isSchedulable_getRefPictInfo_launch_isNotBiPred()) {
		{
			int isAligned = 1;
			isAligned &= ((index_Mv % SIZE_Mv) < ((index_Mv + 2) % SIZE_Mv));
			if (isAligned) {
				getRefPictInfo_launch_isNotBiPred_aligned();
			} else {
				getRefPictInfo_launch_isNotBiPred();
			}
		}
		i++;
		goto l_GetRefPictInfo1;
	} else if (numTokens_IsBiPredOrLx - index_IsBiPredOrLx >= 1 && numTokens_RefPoc - index_RefPoc >= 2 && numTokens_Mv - index_Mv >= 4 && isSchedulable_getRefPictInfo_launch_isBiPred()) {
		{
			int isAligned = 1;
			isAligned &= ((index_RefPoc % SIZE_RefPoc) < ((index_RefPoc + 2) % SIZE_RefPoc));
			isAligned &= ((index_Mv % SIZE_Mv) < ((index_Mv + 4) % SIZE_Mv));
			if (isAligned) {
				getRefPictInfo_launch_isBiPred_aligned();
			} else {
				getRefPictInfo_launch_isBiPred();
			}
		}
		i++;
		goto l_GetRefPictInfo1;
	} else if (isSchedulable_getRefPictInfo_done()) {
		getRefPictInfo_done();
		i++;
		goto l_GetCuInfoNonQT;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetRefPictInfo1;
		goto finished;
	}
l_GetSplitTrafo:
	if (numTokens_SplitTransf - index_SplitTransf >= 1 && isSchedulable_getSplitTrafo_launch_isTrue()) {
		getSplitTrafo_launch_isTrue();
		i++;
		goto l_GetSplitTrafo;
	} else if (numTokens_SplitTransf - index_SplitTransf >= 1 && numTokens_Cbf - index_Cbf >= 1 && isSchedulable_getSplitTrafo_launch_isFalse()) {
		getSplitTrafo_launch_isFalse();
		i++;
		goto l_SendBS;
	} else if (isSchedulable_getSplitTrafo_done()) {
		getSplitTrafo_done();
		i++;
		goto l_GetCuInfo;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetSplitTrafo;
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
l_SendBS:
	if (isSchedulable_sendBS_launch_is64x64()) {
		int stop = 0;
		if (128 > SIZE_BSHor - index_BSHor + HevcDecoder_DBFilter_GenerateBs_BSHor->read_inds[0]) {
			stop = 1;
		}
		if (128 > SIZE_BSVer - index_BSVer + HevcDecoder_DBFilter_GenerateBs_BSVer->read_inds[0]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_SendBS;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		{
			int isAligned = 1;
			isAligned &= ((index_BSHor % SIZE_BSHor) < ((index_BSHor + 128) % SIZE_BSHor));
			isAligned &= ((index_BSVer % SIZE_BSVer) < ((index_BSVer + 128) % SIZE_BSVer));
			if (isAligned) {
				sendBS_launch_is64x64_aligned();
			} else {
				sendBS_launch_is64x64();
			}
		}
		i++;
		goto l_GetSplitTrafo;
	} else if (isSchedulable_sendBS_launch_is32x32()) {
		int stop = 0;
		if (32 > SIZE_BSHor - index_BSHor + HevcDecoder_DBFilter_GenerateBs_BSHor->read_inds[0]) {
			stop = 1;
		}
		if (32 > SIZE_BSVer - index_BSVer + HevcDecoder_DBFilter_GenerateBs_BSVer->read_inds[0]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_SendBS;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		{
			int isAligned = 1;
			isAligned &= ((index_BSHor % SIZE_BSHor) < ((index_BSHor + 32) % SIZE_BSHor));
			isAligned &= ((index_BSVer % SIZE_BSVer) < ((index_BSVer + 32) % SIZE_BSVer));
			if (isAligned) {
				sendBS_launch_is32x32_aligned();
			} else {
				sendBS_launch_is32x32();
			}
		}
		i++;
		goto l_GetSplitTrafo;
	} else if (isSchedulable_sendBS_launch_is16x16()) {
		int stop = 0;
		if (8 > SIZE_BSHor - index_BSHor + HevcDecoder_DBFilter_GenerateBs_BSHor->read_inds[0]) {
			stop = 1;
		}
		if (8 > SIZE_BSVer - index_BSVer + HevcDecoder_DBFilter_GenerateBs_BSVer->read_inds[0]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_SendBS;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		{
			int isAligned = 1;
			isAligned &= ((index_BSHor % SIZE_BSHor) < ((index_BSHor + 8) % SIZE_BSHor));
			isAligned &= ((index_BSVer % SIZE_BSVer) < ((index_BSVer + 8) % SIZE_BSVer));
			if (isAligned) {
				sendBS_launch_is16x16_aligned();
			} else {
				sendBS_launch_is16x16();
			}
		}
		i++;
		goto l_GetSplitTrafo;
	} else if (isSchedulable_sendBS_launch_is8x8()) {
		int stop = 0;
		if (2 > SIZE_BSHor - index_BSHor + HevcDecoder_DBFilter_GenerateBs_BSHor->read_inds[0]) {
			stop = 1;
		}
		if (2 > SIZE_BSVer - index_BSVer + HevcDecoder_DBFilter_GenerateBs_BSVer->read_inds[0]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_SendBS;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		{
			int isAligned = 1;
			isAligned &= ((index_BSHor % SIZE_BSHor) < ((index_BSHor + 2) % SIZE_BSHor));
			isAligned &= ((index_BSVer % SIZE_BSVer) < ((index_BSVer + 2) % SIZE_BSVer));
			if (isAligned) {
				sendBS_launch_is8x8_aligned();
			} else {
				sendBS_launch_is8x8();
			}
		}
		i++;
		goto l_GetSplitTrafo;
	} else if (isSchedulable_sendBS_launch_is4x4_isbSHorVer()) {
		int stop = 0;
		if (1 > SIZE_BSHor - index_BSHor + HevcDecoder_DBFilter_GenerateBs_BSHor->read_inds[0]) {
			stop = 1;
		}
		if (1 > SIZE_BSVer - index_BSVer + HevcDecoder_DBFilter_GenerateBs_BSVer->read_inds[0]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_SendBS;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		sendBS_launch_is4x4_isbSHorVer();
		i++;
		goto l_GetSplitTrafo;
	} else if (isSchedulable_sendBS_launch_is4x4_isbSHor()) {
		int stop = 0;
		if (1 > SIZE_BSHor - index_BSHor + HevcDecoder_DBFilter_GenerateBs_BSHor->read_inds[0]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_SendBS;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		sendBS_launch_is4x4_isbSHor();
		i++;
		goto l_GetSplitTrafo;
	} else if (isSchedulable_sendBS_launch_is4x4_isbSVer()) {
		int stop = 0;
		if (1 > SIZE_BSVer - index_BSVer + HevcDecoder_DBFilter_GenerateBs_BSVer->read_inds[0]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_SendBS;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		sendBS_launch_is4x4_isbSVer();
		i++;
		goto l_GetSplitTrafo;
	} else if (isSchedulable_sendBS_launch_is4x4()) {
		sendBS_launch_is4x4();
		i++;
		goto l_GetSplitTrafo;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_SendBS;
		goto finished;
	}
finished:
	read_end_Cbf();
	read_end_CUInfo();
	read_end_IsBiPredOrLx();
	read_end_LcuSizeMax();
	read_end_LFAcrossSlcTile();
	read_end_Mv();
	read_end_PartMode();
	read_end_RefPoc();
	read_end_SliceAddr();
	read_end_SplitTransf();
	read_end_TilesCoord();
	write_end_BSHor();
	write_end_BSVer();
}
