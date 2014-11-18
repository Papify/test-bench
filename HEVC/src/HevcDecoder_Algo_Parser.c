// Source file is "L/RVC/src/org/sc29/wg11/mpegh/part2/main/synParser/Algo_Parser.cal"

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
extern actor_t HevcDecoder_Algo_Parser;

////////////////////////////////////////////////////////////////////////////////
// Input FIFOs
extern fifo_u8_t *HevcDecoder_Algo_Parser_byte;

////////////////////////////////////////////////////////////////////////////////
// Input Fifo control variables
static unsigned int index_byte;
static unsigned int numTokens_byte;
#define SIZE_byte SIZE
#define tokens_byte HevcDecoder_Algo_Parser_byte->contents

extern connection_t connection_HevcDecoder_Algo_Parser_byte;
#define rate_byte connection_HevcDecoder_Algo_Parser_byte.rate

////////////////////////////////////////////////////////////////////////////////
// Predecessors
extern actor_t Source;

////////////////////////////////////////////////////////////////////////////////
// Output FIFOs
extern fifo_u16_t *HevcDecoder_Algo_Parser_CUInfo;
extern fifo_u8_t *HevcDecoder_Algo_Parser_IntraPredMode;
extern fifo_u16_t *HevcDecoder_Algo_Parser_SliceAddr;
extern fifo_u16_t *HevcDecoder_Algo_Parser_TilesCoord;
extern fifo_u8_t *HevcDecoder_Algo_Parser_LcuSizeMax;
extern fifo_u8_t *HevcDecoder_Algo_Parser_PartMode;
extern fifo_u8_t *HevcDecoder_Algo_Parser_IsPicSlcLcu;
extern fifo_u8_t *HevcDecoder_Algo_Parser_IsPicSlc;
extern fifo_u8_t *HevcDecoder_Algo_Parser_LFAcrossSlcTile;
extern fifo_u16_t *HevcDecoder_Algo_Parser_PictSize;
extern fifo_i16_t *HevcDecoder_Algo_Parser_Poc;
extern fifo_i16_t *HevcDecoder_Algo_Parser_SaoSe;
extern fifo_u8_t *HevcDecoder_Algo_Parser_SEI_MD5;
extern fifo_u8_t *HevcDecoder_Algo_Parser_SliceType;
extern fifo_i32_t *HevcDecoder_Algo_Parser_SplitTransform;
extern fifo_i8_t *HevcDecoder_Algo_Parser_TUSize;
extern fifo_i16_t *HevcDecoder_Algo_Parser_Coeff;
extern fifo_i32_t *HevcDecoder_Algo_Parser_StrongIntraSmoothing;
extern fifo_u16_t *HevcDecoder_Algo_Parser_DispCoord;
extern fifo_u16_t *HevcDecoder_Algo_Parser_PicSizeInMb;
extern fifo_u8_t *HevcDecoder_Algo_Parser_NumRefIdxLxActive;
extern fifo_u8_t *HevcDecoder_Algo_Parser_RefPicListModif;
extern fifo_i16_t *HevcDecoder_Algo_Parser_RefPoc;
extern fifo_i16_t *HevcDecoder_Algo_Parser_MvPredSyntaxElem;
extern fifo_i32_t *HevcDecoder_Algo_Parser_Cbf;
extern fifo_i32_t *HevcDecoder_Algo_Parser_DBFDisable;
extern fifo_i8_t *HevcDecoder_Algo_Parser_DbfSe;
extern fifo_i8_t *HevcDecoder_Algo_Parser_ReorderPics;
extern fifo_i16_t *HevcDecoder_Algo_Parser_WeightedPred;
extern fifo_i8_t *HevcDecoder_Algo_Parser_Qp;

////////////////////////////////////////////////////////////////////////////////
// Output Fifo control variables
static unsigned int index_CUInfo;
static unsigned int numFree_CUInfo;
#define NUM_READERS_CUInfo 5
#define SIZE_CUInfo SIZE
#define tokens_CUInfo HevcDecoder_Algo_Parser_CUInfo->contents

static unsigned int index_IntraPredMode;
static unsigned int numFree_IntraPredMode;
#define NUM_READERS_IntraPredMode 1
#define SIZE_IntraPredMode SIZE
#define tokens_IntraPredMode HevcDecoder_Algo_Parser_IntraPredMode->contents

static unsigned int index_SliceAddr;
static unsigned int numFree_SliceAddr;
#define NUM_READERS_SliceAddr 3
#define SIZE_SliceAddr SIZE
#define tokens_SliceAddr HevcDecoder_Algo_Parser_SliceAddr->contents

static unsigned int index_TilesCoord;
static unsigned int numFree_TilesCoord;
#define NUM_READERS_TilesCoord 5
#define SIZE_TilesCoord SIZE
#define tokens_TilesCoord HevcDecoder_Algo_Parser_TilesCoord->contents

static unsigned int index_LcuSizeMax;
static unsigned int numFree_LcuSizeMax;
#define NUM_READERS_LcuSizeMax 5
#define SIZE_LcuSizeMax SIZE
#define tokens_LcuSizeMax HevcDecoder_Algo_Parser_LcuSizeMax->contents

static unsigned int index_PartMode;
static unsigned int numFree_PartMode;
#define NUM_READERS_PartMode 5
#define SIZE_PartMode SIZE
#define tokens_PartMode HevcDecoder_Algo_Parser_PartMode->contents

static unsigned int index_IsPicSlcLcu;
static unsigned int numFree_IsPicSlcLcu;
#define NUM_READERS_IsPicSlcLcu 2
#define SIZE_IsPicSlcLcu SIZE
#define tokens_IsPicSlcLcu HevcDecoder_Algo_Parser_IsPicSlcLcu->contents

static unsigned int index_IsPicSlc;
static unsigned int numFree_IsPicSlc;
#define NUM_READERS_IsPicSlc 1
#define SIZE_IsPicSlc SIZE
#define tokens_IsPicSlc HevcDecoder_Algo_Parser_IsPicSlc->contents

static unsigned int index_LFAcrossSlcTile;
static unsigned int numFree_LFAcrossSlcTile;
#define NUM_READERS_LFAcrossSlcTile 2
#define SIZE_LFAcrossSlcTile SIZE
#define tokens_LFAcrossSlcTile HevcDecoder_Algo_Parser_LFAcrossSlcTile->contents

static unsigned int index_PictSize;
static unsigned int numFree_PictSize;
#define NUM_READERS_PictSize 5
#define SIZE_PictSize SIZE
#define tokens_PictSize HevcDecoder_Algo_Parser_PictSize->contents

static unsigned int index_Poc;
static unsigned int numFree_Poc;
#define NUM_READERS_Poc 3
#define SIZE_Poc SIZE
#define tokens_Poc HevcDecoder_Algo_Parser_Poc->contents

static unsigned int index_SaoSe;
static unsigned int numFree_SaoSe;
#define NUM_READERS_SaoSe 1
#define SIZE_SaoSe 16384
#define tokens_SaoSe HevcDecoder_Algo_Parser_SaoSe->contents

static unsigned int index_SEI_MD5;
static unsigned int numFree_SEI_MD5;
#define NUM_READERS_SEI_MD5 1
#define SIZE_SEI_MD5 SIZE
#define tokens_SEI_MD5 HevcDecoder_Algo_Parser_SEI_MD5->contents

static unsigned int index_SliceType;
static unsigned int numFree_SliceType;
#define NUM_READERS_SliceType 2
#define SIZE_SliceType SIZE
#define tokens_SliceType HevcDecoder_Algo_Parser_SliceType->contents

static unsigned int index_SplitTransform;
static unsigned int numFree_SplitTransform;
#define NUM_READERS_SplitTransform 2
#define SIZE_SplitTransform SIZE
#define tokens_SplitTransform HevcDecoder_Algo_Parser_SplitTransform->contents

static unsigned int index_TUSize;
static unsigned int numFree_TUSize;
#define NUM_READERS_TUSize 3
#define SIZE_TUSize SIZE
#define tokens_TUSize HevcDecoder_Algo_Parser_TUSize->contents

static unsigned int index_Coeff;
static unsigned int numFree_Coeff;
#define NUM_READERS_Coeff 1
#define SIZE_Coeff SIZE
#define tokens_Coeff HevcDecoder_Algo_Parser_Coeff->contents

static unsigned int index_StrongIntraSmoothing;
static unsigned int numFree_StrongIntraSmoothing;
#define NUM_READERS_StrongIntraSmoothing 1
#define SIZE_StrongIntraSmoothing SIZE
#define tokens_StrongIntraSmoothing HevcDecoder_Algo_Parser_StrongIntraSmoothing->contents

static unsigned int index_DispCoord;
static unsigned int numFree_DispCoord;
#define NUM_READERS_DispCoord 1
#define SIZE_DispCoord SIZE
#define tokens_DispCoord HevcDecoder_Algo_Parser_DispCoord->contents

static unsigned int index_PicSizeInMb;
static unsigned int numFree_PicSizeInMb;
#define NUM_READERS_PicSizeInMb 2
#define SIZE_PicSizeInMb SIZE
#define tokens_PicSizeInMb HevcDecoder_Algo_Parser_PicSizeInMb->contents

static unsigned int index_NumRefIdxLxActive;
static unsigned int numFree_NumRefIdxLxActive;
#define NUM_READERS_NumRefIdxLxActive 1
#define SIZE_NumRefIdxLxActive SIZE
#define tokens_NumRefIdxLxActive HevcDecoder_Algo_Parser_NumRefIdxLxActive->contents

static unsigned int index_RefPicListModif;
static unsigned int numFree_RefPicListModif;
#define NUM_READERS_RefPicListModif 1
#define SIZE_RefPicListModif SIZE
#define tokens_RefPicListModif HevcDecoder_Algo_Parser_RefPicListModif->contents

static unsigned int index_RefPoc;
static unsigned int numFree_RefPoc;
#define NUM_READERS_RefPoc 3
#define SIZE_RefPoc SIZE
#define tokens_RefPoc HevcDecoder_Algo_Parser_RefPoc->contents

static unsigned int index_MvPredSyntaxElem;
static unsigned int numFree_MvPredSyntaxElem;
#define NUM_READERS_MvPredSyntaxElem 1
#define SIZE_MvPredSyntaxElem SIZE
#define tokens_MvPredSyntaxElem HevcDecoder_Algo_Parser_MvPredSyntaxElem->contents

static unsigned int index_Cbf;
static unsigned int numFree_Cbf;
#define NUM_READERS_Cbf 1
#define SIZE_Cbf SIZE
#define tokens_Cbf HevcDecoder_Algo_Parser_Cbf->contents

static unsigned int index_DBFDisable;
static unsigned int numFree_DBFDisable;
#define NUM_READERS_DBFDisable 1
#define SIZE_DBFDisable SIZE
#define tokens_DBFDisable HevcDecoder_Algo_Parser_DBFDisable->contents

static unsigned int index_DbfSe;
static unsigned int numFree_DbfSe;
#define NUM_READERS_DbfSe 1
#define SIZE_DbfSe SIZE
#define tokens_DbfSe HevcDecoder_Algo_Parser_DbfSe->contents

static unsigned int index_ReorderPics;
static unsigned int numFree_ReorderPics;
#define NUM_READERS_ReorderPics 1
#define SIZE_ReorderPics SIZE
#define tokens_ReorderPics HevcDecoder_Algo_Parser_ReorderPics->contents

static unsigned int index_WeightedPred;
static unsigned int numFree_WeightedPred;
#define NUM_READERS_WeightedPred 1
#define SIZE_WeightedPred 16384
#define tokens_WeightedPred HevcDecoder_Algo_Parser_WeightedPred->contents

static unsigned int index_Qp;
static unsigned int numFree_Qp;
#define NUM_READERS_Qp 1
#define SIZE_Qp SIZE
#define tokens_Qp HevcDecoder_Algo_Parser_Qp->contents

////////////////////////////////////////////////////////////////////////////////
// Successors
extern actor_t HevcDecoder_IntraPrediction;
extern actor_t HevcDecoder_InterPrediction;
extern actor_t HevcDecoder_SelectCU;
extern actor_t HevcDecoder_generateInfo_MvComponentPred;
extern actor_t HevcDecoder_DBFilter_GenerateBs;
extern actor_t HevcDecoder_IntraPrediction;
extern actor_t HevcDecoder_IntraPrediction;
extern actor_t HevcDecoder_generateInfo_MvComponentPred;
extern actor_t HevcDecoder_DBFilter_GenerateBs;
extern actor_t HevcDecoder_IntraPrediction;
extern actor_t HevcDecoder_SAO;
extern actor_t HevcDecoder_generateInfo_MvComponentPred;
extern actor_t HevcDecoder_DBFilter_GenerateBs;
extern actor_t HevcDecoder_DBFilter_DeblockFilt;
extern actor_t HevcDecoder_IntraPrediction;
extern actor_t HevcDecoder_SAO;
extern actor_t HevcDecoder_generateInfo_MvComponentPred;
extern actor_t HevcDecoder_DBFilter_GenerateBs;
extern actor_t HevcDecoder_DBFilter_DeblockFilt;
extern actor_t HevcDecoder_IntraPrediction;
extern actor_t HevcDecoder_SelectCU;
extern actor_t HevcDecoder_InterPrediction;
extern actor_t HevcDecoder_generateInfo_MvComponentPred;
extern actor_t HevcDecoder_DBFilter_GenerateBs;
extern actor_t HevcDecoder_SAO;
extern actor_t HevcDecoder_DBFilter_DeblockFilt;
extern actor_t HevcDecoder_DecodingPictureBuffer;
extern actor_t HevcDecoder_SAO;
extern actor_t HevcDecoder_DBFilter_GenerateBs;
extern actor_t HevcDecoder_IntraPrediction;
extern actor_t HevcDecoder_DecodingPictureBuffer;
extern actor_t HevcDecoder_SAO;
extern actor_t HevcDecoder_generateInfo_MvComponentPred;
extern actor_t HevcDecoder_DBFilter_DeblockFilt;
extern actor_t HevcDecoder_DecodingPictureBuffer;
extern actor_t HevcDecoder_InterPrediction;
extern actor_t HevcDecoder_generateInfo_MvComponentPred;
extern actor_t HevcDecoder_SAO;
extern actor_t check_MD5_compute;
extern actor_t HevcDecoder_InterPrediction;
extern actor_t HevcDecoder_generateInfo_MvComponentPred;
extern actor_t HevcDecoder_IntraPrediction;
extern actor_t HevcDecoder_DBFilter_GenerateBs;
extern actor_t HevcDecoder_xIT_IT_Splitter;
extern actor_t HevcDecoder_xIT_IT_Merger;
extern actor_t HevcDecoder_xIT_Block_Merger;
extern actor_t HevcDecoder_xIT_IT_Splitter;
extern actor_t HevcDecoder_IntraPrediction;
extern actor_t display;
extern actor_t display;
extern actor_t check_MD5_MD5SplitInfo;
extern actor_t HevcDecoder_generateInfo_GenerateRefList;
extern actor_t HevcDecoder_generateInfo_GenerateRefList;
extern actor_t HevcDecoder_DecodingPictureBuffer;
extern actor_t HevcDecoder_generateInfo_GenerateRefList;
extern actor_t HevcDecoder_generateInfo_MvComponentPred;
extern actor_t HevcDecoder_generateInfo_MvComponentPred;
extern actor_t HevcDecoder_DBFilter_GenerateBs;
extern actor_t HevcDecoder_DBFilter_DeblockFilt;
extern actor_t HevcDecoder_DBFilter_DeblockFilt;
extern actor_t HevcDecoder_DecodingPictureBuffer;
extern actor_t HevcDecoder_InterPrediction;
extern actor_t HevcDecoder_DBFilter_DeblockFilt;

////////////////////////////////////////////////////////////////////////////////
// Parameter values of the instance
#define TILE_INDEX 0
#define TILE_SPLIT_ENABLE 0


////////////////////////////////////////////////////////////////////////////////
// State variables of the actor
#define HevcDecoder_Algo_Parser_NAL_BLA_W_LP 16
#define HevcDecoder_Algo_Parser_NAL_BLA_W_RADL 17
#define HevcDecoder_Algo_Parser_NAL_BLA_N_LP 18
#define HevcDecoder_Algo_Parser_NUM_NEGATIVE_PICS 0
#define HevcDecoder_Algo_Parser_USED 67
#define HevcDecoder_Algo_Parser_ST_CURR_BEF 0
#define HevcDecoder_Algo_Parser_DELTAPOC 3
#define HevcDecoder_Algo_Parser_ST_FOLL 2
#define HevcDecoder_Algo_Parser_NUM_PICS 2
#define HevcDecoder_Algo_Parser_ST_CURR_AFT 1
#define HevcDecoder_Algo_Parser_LT_CURR 3
#define HevcDecoder_Algo_Parser_LT_FOLL 4
#define HevcDecoder_Algo_Parser_FIFO_CPT_BITS 8
#define HevcDecoder_Algo_Parser_FIFO_SIZE 8
#define HevcDecoder_Algo_Parser_FIFO_IDX 9
#define HevcDecoder_Algo_Parser_EPR_VALUE 3
#define HevcDecoder_Algo_Parser_START_CODE_VALUE 1
#define HevcDecoder_Algo_Parser_START_CODE_FLAG 256
#define HevcDecoder_Algo_Parser_DEBUG_BITSTREAM 0
#define HevcDecoder_Algo_Parser_FIFO_DEPTH 9
#define HevcDecoder_Algo_Parser_DEBUG_PARSER 0
#define HevcDecoder_Algo_Parser_NAL_VPS 32
#define HevcDecoder_Algo_Parser_NAL_SEI_PREFIX 39
#define HevcDecoder_Algo_Parser_NAL_SEI_SUFFIX 40
#define HevcDecoder_Algo_Parser_NAL_SPS 33
#define HevcDecoder_Algo_Parser_NAL_PPS 34
#define HevcDecoder_Algo_Parser_NAL_TRAIL_R 0
#define HevcDecoder_Algo_Parser_NAL_TSA_N 2
#define HevcDecoder_Algo_Parser_NAL_TSA_R 3
#define HevcDecoder_Algo_Parser_NAL_TRAIL_N 1
#define HevcDecoder_Algo_Parser_NAL_STSA_N 4
#define HevcDecoder_Algo_Parser_NAL_STSA_R 5
#define HevcDecoder_Algo_Parser_NAL_RADL_N 6
#define HevcDecoder_Algo_Parser_NAL_RADL_R 7
#define HevcDecoder_Algo_Parser_NAL_RASL_N 8
#define HevcDecoder_Algo_Parser_NAL_RASL_R 9
#define HevcDecoder_Algo_Parser_NAL_IDR_N_LP 20
#define HevcDecoder_Algo_Parser_NAL_IDR_W_DLP 19
#define HevcDecoder_Algo_Parser_NAL_CRA_NUT 21
static const u8 HevcDecoder_Algo_Parser_default_scaling_list_intra[64] = {16, 16, 16, 16, 17, 18, 21, 24, 16, 16, 16, 16, 17, 19, 22, 25, 16, 16, 17, 18, 20, 22, 25, 29, 16, 16, 18, 21, 24, 27, 31, 36, 17, 17, 20, 24, 30, 35, 41, 47, 18, 19, 22, 27, 35, 44, 54, 65, 21, 22, 25, 31, 41, 54, 70, 88, 24, 25, 29, 36, 47, 65, 88, 115};
static const u8 HevcDecoder_Algo_Parser_default_scaling_list_inter[64] = {16, 16, 16, 16, 17, 18, 20, 24, 16, 16, 16, 17, 18, 20, 24, 25, 16, 16, 17, 18, 20, 24, 25, 28, 16, 17, 18, 20, 24, 25, 28, 33, 17, 18, 20, 24, 25, 28, 33, 41, 18, 20, 24, 25, 28, 33, 41, 54, 20, 24, 25, 28, 33, 41, 54, 71, 24, 25, 28, 33, 41, 54, 71, 91};
static const i8 HevcDecoder_Algo_Parser_hevc_diag_scan4x4_y[16] = {0, 1, 0, 2, 1, 0, 3, 2, 1, 0, 3, 2, 1, 3, 2, 3};
static const u8 HevcDecoder_Algo_Parser_hevc_diag_scan4x4_x[16] = {0, 0, 1, 0, 1, 2, 0, 1, 2, 3, 1, 2, 3, 2, 3, 3};
static const i8 HevcDecoder_Algo_Parser_hevc_diag_scan8x8_y[64] = {0, 1, 0, 2, 1, 0, 3, 2, 1, 0, 4, 3, 2, 1, 0, 5, 4, 3, 2, 1, 0, 6, 5, 4, 3, 2, 1, 0, 7, 6, 5, 4, 3, 2, 1, 0, 7, 6, 5, 4, 3, 2, 1, 7, 6, 5, 4, 3, 2, 7, 6, 5, 4, 3, 7, 6, 5, 4, 7, 6, 5, 7, 6, 7};
static const i8 HevcDecoder_Algo_Parser_hevc_diag_scan8x8_x[64] = {0, 0, 1, 0, 1, 2, 0, 1, 2, 3, 0, 1, 2, 3, 4, 0, 1, 2, 3, 4, 5, 0, 1, 2, 3, 4, 5, 6, 0, 1, 2, 3, 4, 5, 6, 7, 1, 2, 3, 4, 5, 6, 7, 2, 3, 4, 5, 6, 7, 3, 4, 5, 6, 7, 4, 5, 6, 7, 5, 6, 7, 6, 7, 7};
#define HevcDecoder_Algo_Parser_NUM_POSITIVE_PICS 1
#define HevcDecoder_Algo_Parser_PICT_WIDTH 4096
#define HevcDecoder_Algo_Parser_MIN_CTB_SIZE_Y 8
#define HevcDecoder_Algo_Parser_PICT_HEIGHT 2048
static const u8 HevcDecoder_Algo_Parser_log2_tab[256] = {0, 0, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7};
#define HevcDecoder_Algo_Parser_PART_MODE_PICT 8
#define HevcDecoder_Algo_Parser_PART_MODE_SLICE_INDEP 10
#define HevcDecoder_Algo_Parser_PART_MODE_SLICE_DEP 9
#define HevcDecoder_Algo_Parser_PC_RPS_STRUCT_SIZE 131
#define HevcDecoder_Algo_Parser_P_SLICE 1
#define HevcDecoder_Algo_Parser_B_SLICE 0
#define HevcDecoder_Algo_Parser_DEBUG_CABAC 0
#define HevcDecoder_Algo_Parser_CHECK_CABAC 0
#define HevcDecoder_Algo_Parser_INTRA_DC 1
#define HevcDecoder_Algo_Parser_CTB_ADDR_TS_MAX 4096
#define HevcDecoder_Algo_Parser_NB_MAX_SE 30
#define HevcDecoder_Algo_Parser_NB_MAX_NUM_CTX 48
static const u8 HevcDecoder_Algo_Parser_NUM_SE_CONTEXT_INDEX[30] = {1, 1, 1, 3, 1, 3, 3, 1, 4, 1, 1, 1, 1, 5, 2, 2, 2, 2, 1, 1, 3, 5, 5, 30, 30, 4, 42, 24, 6, 2};
static const u8 HevcDecoder_Algo_Parser_InitContextIndex[30][3][48] = {{{0}, {0}, {0}}, {{153}, {153}, {153}}, {{160}, {185}, {200}}, {{107, 139, 126}, {107, 139, 126}, {139, 141, 157}}, {{154}, {154}, {154}}, {{197, 185, 201}, {197, 185, 201}, {154, 154, 154}}, {{154, 154, 154}, {154, 154, 154}, {154, 154, 154}}, {{134}, {149}, {154}}, {{154, 139, 154, 154}, {154, 139, 154, 154}, {184, 154, 154, 154}}, {{183}, {154}, {184}}, {{152}, {152}, {63}}, {{154}, {110}, {154}}, {{137}, {122}, {154}}, {{95, 79, 63, 31, 31}, {95, 79, 63, 31, 31}, {154, 154, 154, 154, 154}}, {{153, 153}, {153, 153}, {154, 154}}, {{153, 153}, {153, 153}, {154, 154}}, {{169, 198}, {140, 198}, {154, 154}}, {{169, 198}, {140, 198}, {154, 154}}, {{168}, {168}, {154}}, {{79}, {79}, {154}}, {{224, 167, 122}, {124, 138, 94}, {153, 138, 138}}, {{153, 111, 154, 154, 154}, {153, 111, 154, 154, 154}, {111, 141, 154, 154, 154}}, {{149, 92, 167, 154, 154}, {149, 107, 167, 154, 154}, {94, 138, 182, 154, 154}}, {{125, 110, 124, 110, 95, 94, 125, 111, 111, 79, 125, 126, 111, 111, 79, 108, 123, 93, 154, 154, 154, 154, 154, 154, 154, 154, 154, 154, 154, 154}, {125, 110, 94, 110, 95, 79, 125, 111, 110, 78, 110, 111, 111, 95, 94, 108, 123, 108, 154, 154, 154, 154, 154, 154, 154, 154, 154, 154, 154, 154}, {110, 110, 124, 125, 140, 153, 125, 127, 140, 109, 111, 143, 127, 111, 79, 108, 123, 63, 154, 154, 154, 154, 154, 154, 154, 154, 154, 154, 154, 154}}, {{125, 110, 124, 110, 95, 94, 125, 111, 111, 79, 125, 126, 111, 111, 79, 108, 123, 93, 154, 154, 154, 154, 154, 154, 154, 154, 154, 154, 154, 154}, {125, 110, 94, 110, 95, 79, 125, 111, 110, 78, 110, 111, 111, 95, 94, 108, 123, 108, 154, 154, 154, 154, 154, 154, 154, 154, 154, 154, 154, 154}, {110, 110, 124, 125, 140, 153, 125, 127, 140, 109, 111, 143, 127, 111, 79, 108, 123, 63, 154, 154, 154, 154, 154, 154, 154, 154, 154, 154, 154, 154}}, {{121, 140, 61, 154}, {121, 140, 61, 154}, {91, 171, 134, 141}}, {{170, 154, 139, 153, 139, 123, 123, 63, 124, 166, 183, 140, 136, 153, 154, 166, 183, 140, 136, 153, 154, 166, 183, 140, 136, 153, 154, 170, 153, 138, 138, 122, 121, 122, 121, 167, 151, 183, 140, 151, 183, 140}, {155, 154, 139, 153, 139, 123, 123, 63, 153, 166, 183, 140, 136, 153, 154, 166, 183, 140, 136, 153, 154, 166, 183, 140, 136, 153, 154, 170, 153, 123, 123, 107, 121, 107, 121, 167, 151, 183, 140, 151, 183, 140}, {111, 111, 125, 110, 110, 94, 124, 108, 124, 107, 125, 141, 179, 153, 125, 107, 125, 141, 179, 153, 125, 107, 125, 141, 179, 153, 125, 140, 139, 182, 182, 152, 136, 152, 136, 153, 136, 139, 111, 136, 139, 111}}, {{154, 196, 167, 167, 154, 152, 167, 182, 182, 134, 149, 136, 153, 121, 136, 122, 169, 208, 166, 167, 154, 152, 167, 182}, {154, 196, 196, 167, 154, 152, 167, 182, 182, 134, 149, 136, 153, 121, 136, 137, 169, 194, 166, 167, 154, 167, 137, 182}, {140, 92, 137, 138, 140, 152, 138, 139, 153, 74, 149, 92, 139, 107, 122, 152, 140, 179, 166, 182, 140, 227, 122, 197}}, {{107, 167, 91, 107, 107, 167}, {107, 167, 91, 122, 107, 167}, {138, 153, 136, 167, 152, 152}}, {{139, 139}, {139, 139}, {139, 139}}};
#define HevcDecoder_Algo_Parser_CT_idx 0
#define HevcDecoder_Algo_Parser_CT_x0 1
#define HevcDecoder_Algo_Parser_CT_y0 2
#define HevcDecoder_Algo_Parser_CT_log2CbSize 5
#define HevcDecoder_Algo_Parser_CT_ctDepth 6
#define HevcDecoder_Algo_Parser_NEW_LCU 2
#define HevcDecoder_Algo_Parser_SAO_NO_MERGE 0
static const u16 HevcDecoder_Algo_Parser_rangeTabLPS[64][4] = {{128, 176, 208, 240}, {128, 167, 197, 227}, {128, 158, 187, 216}, {123, 150, 178, 205}, {116, 142, 169, 195}, {111, 135, 160, 185}, {105, 128, 152, 175}, {100, 122, 144, 166}, {95, 116, 137, 158}, {90, 110, 130, 150}, {85, 104, 123, 142}, {81, 99, 117, 135}, {77, 94, 111, 128}, {73, 89, 105, 122}, {69, 85, 100, 116}, {66, 80, 95, 110}, {62, 76, 90, 104}, {59, 72, 86, 99}, {56, 69, 81, 94}, {53, 65, 77, 89}, {51, 62, 73, 85}, {48, 59, 69, 80}, {46, 56, 66, 76}, {43, 53, 63, 72}, {41, 50, 59, 69}, {39, 48, 56, 65}, {37, 45, 54, 62}, {35, 43, 51, 59}, {33, 41, 48, 56}, {32, 39, 46, 53}, {30, 37, 43, 50}, {29, 35, 41, 48}, {27, 33, 39, 45}, {26, 31, 37, 43}, {24, 30, 35, 41}, {23, 28, 33, 39}, {22, 27, 32, 37}, {21, 26, 30, 35}, {20, 24, 29, 33}, {19, 23, 27, 31}, {18, 22, 26, 30}, {17, 21, 25, 28}, {16, 20, 23, 27}, {15, 19, 22, 25}, {14, 18, 21, 24}, {14, 17, 20, 23}, {13, 16, 19, 22}, {12, 15, 18, 21}, {12, 14, 17, 20}, {11, 14, 16, 19}, {11, 13, 15, 18}, {10, 12, 15, 17}, {10, 12, 14, 16}, {9, 11, 13, 15}, {9, 11, 12, 14}, {8, 10, 12, 14}, {8, 9, 11, 13}, {7, 9, 11, 12}, {7, 9, 10, 12}, {7, 8, 10, 11}, {6, 8, 9, 11}, {6, 7, 9, 10}, {6, 7, 8, 9}, {2, 2, 2, 2}};
static const u8 HevcDecoder_Algo_Parser_transIdxLPS[64] = {0, 0, 1, 2, 2, 4, 4, 5, 6, 7, 8, 9, 9, 11, 11, 12, 13, 13, 15, 15, 16, 16, 18, 18, 19, 19, 21, 21, 22, 22, 23, 24, 24, 25, 26, 26, 27, 27, 28, 29, 29, 30, 30, 30, 31, 32, 32, 33, 33, 33, 34, 34, 35, 35, 35, 36, 36, 36, 37, 37, 37, 38, 38, 63};
static const u8 HevcDecoder_Algo_Parser_transIdxMPS[64] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 62, 63};
#define HevcDecoder_Algo_Parser_SE_SAO_MERGE_FLAG 1
#define HevcDecoder_Algo_Parser_SAO_MERGE_LEFT 1
#define HevcDecoder_Algo_Parser_SAO_MERGE_UP 2
#define HevcDecoder_Algo_Parser_SAO_NOT_APPLIED 0
#define HevcDecoder_Algo_Parser_SE_SAO_TYPE_IDX 2
#define HevcDecoder_Algo_Parser_SAO_BAND 1
#define HevcDecoder_Algo_Parser_SAO_EDGE 2
#define HevcDecoder_Algo_Parser_DEBIN_TU9 8
#define HevcDecoder_Algo_Parser_DEBUG_TRACE1 0
#define HevcDecoder_Algo_Parser_SE_SPLIT_CODING_UNIT_FLAG 3
#define HevcDecoder_Algo_Parser_CT_x1 3
#define HevcDecoder_Algo_Parser_CT_y1 4
#define HevcDecoder_Algo_Parser_OTHER 16
#define HevcDecoder_Algo_Parser_PART_2Nx2N 0
#define HevcDecoder_Algo_Parser_INTRA 1
#define HevcDecoder_Algo_Parser_SE_CU_TRANSQUANT_BYPASS_FLAG 4
#define HevcDecoder_Algo_Parser_I_SLICE 2
#define HevcDecoder_Algo_Parser_SE_SKIP_FLAG 5
#define HevcDecoder_Algo_Parser_SKIP 2
#define HevcDecoder_Algo_Parser_INTER 0
#define HevcDecoder_Algo_Parser_PART_NxN 3
#define HevcDecoder_Algo_Parser_TEXT_LUMA 0
#define HevcDecoder_Algo_Parser_TEXT_CHROMA_U 1
#define HevcDecoder_Algo_Parser_TEXT_CHROMA_V 2
#define HevcDecoder_Algo_Parser_SE_PRED_MODE_FLAG 7
#define HevcDecoder_Algo_Parser_SE_PART_MODE 8
#define HevcDecoder_Algo_Parser_PART_2NxN 1
#define HevcDecoder_Algo_Parser_PART_Nx2N 2
#define HevcDecoder_Algo_Parser_PART_2NxnD 5
#define HevcDecoder_Algo_Parser_PART_2NxnU 4
#define HevcDecoder_Algo_Parser_PART_nRx2N 7
#define HevcDecoder_Algo_Parser_PART_nLx2N 6
#define HevcDecoder_Algo_Parser_SE_PREV_INTRA_LUMA_PRED_FLAG 9
#define HevcDecoder_Algo_Parser_DEBIN_TU2 1
#define HevcDecoder_Algo_Parser_INTRA_PLANAR 0
#define HevcDecoder_Algo_Parser_INTRA_ANGULAR_26 26
#define HevcDecoder_Algo_Parser_SE_INTRA_CHROMA_PRED_MODE 10
static const u8 HevcDecoder_Algo_Parser_partModeToNumPart[8] = {1, 2, 2, 4, 2, 2, 2, 2};
#define HevcDecoder_Algo_Parser_SE_NO_RESIDUAL_SYNTAX_FLAG 19
#define HevcDecoder_Algo_Parser_TT_idx 0
#define HevcDecoder_Algo_Parser_TT_x0 1
#define HevcDecoder_Algo_Parser_TT_y0 2
#define HevcDecoder_Algo_Parser_TT_xBase 5
#define HevcDecoder_Algo_Parser_TT_yBase 6
#define HevcDecoder_Algo_Parser_TT_log2TrafoSize 7
#define HevcDecoder_Algo_Parser_TT_trafoDepth 8
#define HevcDecoder_Algo_Parser_TT_blkIdx 9
#define HevcDecoder_Algo_Parser_PRED_L0 0
#define HevcDecoder_Algo_Parser_SE_MERGE_IDX 12
#define HevcDecoder_Algo_Parser_SE_MERGE_FLAG 11
#define HevcDecoder_Algo_Parser_SE_INTER_PRED_IDC 13
#define HevcDecoder_Algo_Parser_BI_PRED 2
#define HevcDecoder_Algo_Parser_PRED_L1 1
#define HevcDecoder_Algo_Parser_SE_REF_IDX_L0 14
#define HevcDecoder_Algo_Parser_SE_MVP_LX_FLAG 18
#define HevcDecoder_Algo_Parser_SE_ABS_MVD_GREATER0_FLAG 16
#define HevcDecoder_Algo_Parser_SE_SPLIT_TRANSFORM_FLAG 20
#define HevcDecoder_Algo_Parser_SE_CBF_CB_CR 22
#define HevcDecoder_Algo_Parser_TT_x1 3
#define HevcDecoder_Algo_Parser_TT_y1 4
#define HevcDecoder_Algo_Parser_SE_CBF_LUMA 21
#define HevcDecoder_Algo_Parser_SE_CU_QP_DELTA 6
#define HevcDecoder_Algo_Parser_DEBIN_TU5 4
#define HevcDecoder_Algo_Parser_SCAN_VER 2
#define HevcDecoder_Algo_Parser_SCAN_HOR 1
#define HevcDecoder_Algo_Parser_SCAN_ZIGZAG 0
static const u8 HevcDecoder_Algo_Parser_rem6[64] = {0, 1, 2, 3, 4, 5, 0, 1, 2, 3, 4, 5, 0, 1, 2, 3, 4, 5, 0, 1, 2, 3, 4, 5, 0, 1, 2, 3, 4, 5, 0, 1, 2, 3, 4, 5, 0, 1, 2, 3, 4, 5, 0, 1, 2, 3, 4, 5, 0, 1, 2, 3, 4, 5, 0, 1, 2, 3, 4, 5, 0, 1, 2, 3};
static const u8 HevcDecoder_Algo_Parser_div6[64] = {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 10, 10, 10, 10};
#define HevcDecoder_Algo_Parser_SE_TRANSFORM_SKIP_FLAG 29
#define HevcDecoder_Algo_Parser_SE_LAST_SIGNIFICANT_COEFF_X_PREFIX 23
#define HevcDecoder_Algo_Parser_SE_LAST_SIGNIFICANT_COEFF_Y_PREFIX 24
static const u8 HevcDecoder_Algo_Parser_diag_scan4x4_inv[4][4] = {{0, 2, 5, 9}, {1, 4, 8, 12}, {3, 7, 11, 14}, {6, 10, 13, 15}};
static const u8 HevcDecoder_Algo_Parser_diag_scan2x2_inv[2][2] = {{0, 2}, {1, 3}};
static const u8 HevcDecoder_Algo_Parser_diag_scan8x8_inv[8][8] = {{0, 2, 5, 9, 14, 20, 27, 35}, {1, 4, 8, 13, 19, 26, 34, 42}, {3, 7, 12, 18, 25, 33, 41, 48}, {6, 11, 17, 24, 32, 40, 47, 53}, {10, 16, 23, 31, 39, 46, 52, 57}, {15, 22, 30, 38, 45, 51, 56, 60}, {21, 29, 37, 44, 50, 55, 59, 62}, {28, 36, 43, 49, 54, 58, 61, 63}};
static const u8 HevcDecoder_Algo_Parser_horiz_scan8x8_inv[8][8] = {{0, 1, 2, 3, 16, 17, 18, 19}, {4, 5, 6, 7, 20, 21, 22, 23}, {8, 9, 10, 11, 24, 25, 26, 27}, {12, 13, 14, 15, 28, 29, 30, 31}, {32, 33, 34, 35, 48, 49, 50, 51}, {36, 37, 38, 39, 52, 53, 54, 55}, {40, 41, 42, 43, 56, 57, 58, 59}, {44, 45, 46, 47, 60, 61, 62, 63}};
#define HevcDecoder_Algo_Parser_SE_CODED_SUB_BLOCK_FLAG 25
static const u8 HevcDecoder_Algo_Parser_ctxInMap[16] = {0, 1, 4, 5, 2, 3, 4, 5, 6, 6, 8, 8, 7, 7, 8, 8};
#define HevcDecoder_Algo_Parser_SE_SIGNIFICANT_COEFF_FLAG 26
#define HevcDecoder_Algo_Parser_SE_COEFF_ABS_LEVEL_GREATER1_FLAG 27
#define HevcDecoder_Algo_Parser_SE_COEFF_ABS_LEVEL_GREATER2_FLAG 28
static u16 fifo[10];
static u8 zeroByte = 0;
static u16 se_idx;
static u32 cnt_i;
static u16 sps_id;
static u16 pps_id;
static u8 localizeAEB = 0;
#define NUM_ENTRY_MAX 64
static u32 entryOffsetsTab[64];
static i32 byPassFlag = 0;
static u8 TilesInfo[2];
static u32 counterByte = 0;
static u32 temporal_id = 0;
static u8 nal_unit_type;
static u8 vps_max_sub_layers_minus1;
static u8 vps_max_nuh_reserved_zero_layer_id;
static u8 vps_timing_info_present_flag;
static u16 vps_num_op_sets_minus1;
static u16 vps_num_hrd_parameters;
static u8 video_sequence_id = 0;
static i32 profile_present_flag = 1;
static i32 sub_layer_profile_present_flag;
static i32 sub_layer_level_present_flag;
static u16 sei_payloadType;
static u16 sei_payloadSize;
static u16 sei_payloadPosition;
static u8 sei_idx;
static u8 sei_cIdx;
static u8 sei_i;
static u8 sei_hash_type;
static u8 sps_max_sub_layers_minus1[15];
static u16 sps_pic_width_in_luma_samples[15];
static u16 sps_pic_height_in_luma_samples[15];
static u8 sps_separate_colour_plane_flag[15];
static u8 sps_chroma_format_idc[15];
static i32 sps_sub_layer_level_present_flag = 0;
static i32 sps_profile_present_flag = 1;
static i32 sps_sub_layer_profile_present_flag = 0;
static u8 sps_log2_max_pic_order_cnt_lsb_minus4[15];
static u32 max_poc_lsb[15];
static i32 sps_bit_depth_luma_minus8[15];
static i32 sps_bit_depth_chroma_minus8[15];
static u32 sps_num_reorder_pics[15];
static u8 sps_log2_min_coding_block_size[15];
static u8 sps_log2_min_pu_size[15];
static u8 sps_min_pu_width[15];
static u8 sps_log2_diff_max_min_coding_block_size[15];
static u8 sps_log2_min_transform_block_size[15];
static u8 sps_log2_diff_max_min_transform_block_size[15];
static u16 sps_maxCUWidth[15];
static u16 sps_addCUDepth[15];
static u8 sps_max_transform_hierarchy_depth_inter[15];
static u8 sps_max_transform_hierarchy_depth_intra[15];
static u8 sps_scaling_list_enabled_flag[15];
static u16 sps_ctb_width[15];
static u16 sps_ctb_height[15];
static u16 sps_log2_ctb_size[15];
static i32 min_cb_width;
static u8 sps_sample_adaptive_offset_enabled_flag[15];
static u8 sps_num_short_term_ref_pic_sets[15];
static u8 sps_pcm_enabled_flag[15];
static u8 amp_enabled_flag;
static u8 sps_sl[15][4][6][64];
static u8 sps_sl_dc[15][2][6];
static i32 sps_size_id = 0;
static i32 sps_size_id_matrixCase;
static i32 sps_matrix_id = 0;
static i32 sps_coef_num = 0;
static i32 sps_pos;
static i32 sps_scaling_list_delta_coef;
static i32 sps_next_coef;
static u32 log2_min_pcm_cb_size[15];
static u32 log2_max_pcm_cb_size[15];
static u32 pcm_bit_depth[15];
static u32 pcm_bit_depth_chroma[15];
static u32 pcm_loop_filter_disable_flag[15];
static i8 pcRPS[15][65][131];
static u8 sps_long_term_ref_pics_present_flag[15];
static u8 sps_temporal_mvp_enable_flag[15];
static i32 sps_strong_intra_smoothing_enable_flag[15];
static u8 sps_num_long_term_ref_pics_sps[15];
static u16 lt_ref_pic_poc_lsb_sps[32];
static u8 used_by_curr_pic_lt_sps_flag[32];
static u8 pps_sps_id[15];
static u8 pps_tiles_enabled_flag[15];
static u8 pps_dependent_slice_segments_enabled_flag[15];
static u8 pps_output_flag_present_flag[15];
static u8 pps_num_extra_slice_header_bits[15];
static u8 pps_sign_data_hiding_flag[15];
static u8 pps_cabac_init_present_flag[15];
static u8 pps_num_ref_idx_l0_default_active_minus1[15];
static u8 pps_num_ref_idx_l1_default_active_minus1[15];
static i32 pps_init_qp_minus26[15];
static u8 pps_transform_skip_enabled_flag[15];
static i32 pps_constrained_intra_pred_flag[15];
static u8 pps_cu_qp_delta_enabled_flag[15];
static u16 pps_diff_cu_qp_delta_depth[15];
static i8 pps_cb_qp_offset[15];
static i8 pps_cr_qp_offset[15];
static u8 pps_slice_chroma_qp_offsets_present_flag[15];
static u8 pps_weighted_pred_flag[15];
static u8 pps_weighted_bipred_flag[15];
static u8 pps_transquant_bypass_enable_flag[15];
static u8 pps_entropy_coding_sync_enabled_flag[15];
static u8 pps_num_tile_columns_minus1[15];
static u8 pps_num_tile_rows_minus1[15];
static u8 pps_uniform_spacing_flag[15];
static u16 pps_column_width[15][512];
static u16 pps_row_height[15][256];
static u8 pps_scaling_list_data_present_flag[15];
static i32 sum = 0;
static u8 pps_deblocking_filter_control_present_flag[15];
static u8 deblocking_filter_override_enabled_flag[15];
static u8 pps_loop_filter_across_slice_enabled_flag[15];
static u8 pps_lists_modification_present_flag[15];
static u8 pps_slice_segment_header_extension_present_flag[15];
static u8 pps_disable_deblocking_filter_flag[15];
static u8 pps_beta_offset[15];
static u8 pps_tc_offset[15];
static u8 pps_log2_parallel_merge_level[15];
static u8 pps_sl[15][4][6][64];
static u8 pps_sl_dc[15][2][6];
static i32 pps_matrix_id = 0;
static i32 pps_size_id = 0;
static i32 pps_next_coef;
static i32 pps_coef_num;
static i32 pps_scaling_list_delta_coef;
static i32 pps_pos;
static i32 pps_size_id_matrixCase;
static u8 Log2CtbSize;
static u8 Log2MinCbSize;
static u16 PicWidthInCtbsY;
static u16 PicHeightInCtbsY;
static u16 PicSizeInCtbsY;
static u8 slice_temporal_mvp_enable_flag;
static i32 poc;
static u8 slice_type;
static u32 slice_segment_address;
static u8 slice_sample_adaptive_offset_flag[4];
static u8 first_slice_segment_in_pic_flag = 1;
static u8 dependent_slice_segment_flag;
static u16 pictSize[2];
static u16 num_long_term_sps = 0;
static u16 num_long_term_pics = 0;
static u8 poc_lsb_lt[32];
static u8 UsedByCurrPicLt[32];
static u8 DeltaPocMsbCycleLt[32];
static u8 delta_poc_msb_present_flag[32];
static i32 pic_order_cnt_lsb;
static u16 pictOrTileSize[2] = {0, 0};
static u32 rowIndex = 0;
static u32 colIndex = 0;
static u16 prevTileCoord[2] = {0, 0};
static u32 prevRowIndex = 0;
static u32 prevColIndex = 0;
static u32 slice_addr = 0;
static i32 slice_idx = 0;
static i32 idx = 0;
static u32 no_output_of_prior_pics_flag;
static u32 pic_output_flag;
static u8 short_term_ref_pic_set_sps_flag;
static i32 prev;
static u8 num_ref_idx_l0_active;
static u8 num_ref_idx_l1_active;
static u8 mvd_l1_zero_flag;
static u8 ref_pic_list_modification_flag_lx[2] = {0, 0};
static u8 list_entry_lx[2][32];
static i16 pocTables[5][64];
static i32 numPic[5];
static u8 idxNumPic;
static u8 idxRefPoc;
static i8 slice_qp;
static i8 slice_cb_qp_offset;
static i8 slice_cr_qp_offset;
static u16 MaxNumMergeCand;
static u8 cabac_init_flag;
static u8 collocated_from_lX = 0;
static u8 collocated_ref_idx = 0;
static u8 luma_weight_l0_flag[16];
static u8 chroma_weight_l0_flag[16];
static i8 delta_luma_weight_l0;
static i8 luma_offset_l0;
static i8 delta_chroma_weight_l00;
static i8 delta_chroma_weight_l01;
static i16 delta_chroma_offset_l00;
static i16 delta_chroma_offset_l01;
static u8 luma_weight_l1_flag[16];
static u8 chroma_weight_l1_flag[16];
static i8 delta_luma_weight_l1;
static i8 luma_offset_l1;
static i8 delta_chroma_weight_l10;
static i8 delta_chroma_weight_l11;
static i16 delta_chroma_offset_l10;
static i16 delta_chroma_offset_l11;
static u16 qp_bd_offset_luma;
static u16 num_entry_point_offsets = 0;
static u16 offset_len;
static u16 slice_segment_header_extension_length;
static u32 num_entry_offsets = 0;
static u32 totalByPass = 0;
static i32 countAEB = 0;
static u16 codIRange[1];
static u16 codIOffset[1];
static u16 ctxTable[30][48];
static u16 ctxTableWPP[30][48];
static u8 sliceData_idx;
static u8 prev_pps_id;
static u8 Log2MinTrafoSize;
static u8 Log2MaxTrafoSize;
static u16 ctbAddrRStoTS[4096];
static u16 ctbAddrTStoRS[4096];
static u16 TileId[4096];
static u16 nbCtbTile[128] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
static u16 colTileInPix[128] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
static u16 rowTileInPix[128] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
static u32 tile_idx = 0;
static u8 skip_flag_tab[4096][2];
static u8 intraPredMode[4096][2];
static u16 colWidth[15][512];
static u16 rowHeight[15][256];
static u32 countRow = 0;
static u32 countCol = 0;
static u32 CtbAddrRS;
static u32 CtbAddrTS;
static u32 end_of_slice_flag;
static i32 counter = 0;
static u16 xCtb;
static u16 yCtb;
static u8 codingTree_idx;
static u8 ctStack_idx;
static u16 ctStack[5][7];
static u8 first_qp_group;
static i32 ctb_left_flag;
static i32 ctb_up_flag;
static i32 ctb_addr_in_slice;
static u8 sao_cIdx;
static u16 sao_rx;
static u16 sao_ry;
static u8 sao_idx;
static i16 sao_typeIdx;
static i16 sao_eo;
static u8 IsCuQpDeltaCoded;
static i16 CuQpDelta;
static u8 ct_log2CbSize;
static u8 cu_idx;
static u16 cu_x0;
static u16 cu_y0;
static u8 cu_log2CbSize;
static u8 cu_ctDepth;
static u8 predMode;
static u8 partMode;
static u8 IntraSplitFlag;
static u8 MaxTrafoDepth;
static u8 cu_transquant_bypass_flag;
static u8 cu_top_ctDepth[4096];
static u8 cu_left_ctDepth[4096];
static u8 skip_flag;
static u8 merge_flag;
static u8 intraChrPredModIdx;
static const u8 intraPredModeC[5][5] = {{34, 0, 0, 0, 0}, {26, 34, 26, 26, 26}, {10, 10, 34, 10, 10}, {1, 1, 1, 34, 1}, {0, 26, 10, 1, 0}};
static i32 qp_block_mask = 0;
static u8 cu_nCbS;
static i32 counterfillSkip = 0;
static i32 QPCounter = 0;
static u8 intra_pred_mode[4];
static u8 intra_pred_mode_c;
static i32 qPy_pred = 0;
static u8 length;
static u8 pu_idx;
static u8 pu_PbW;
static u8 pu_PbH;
static u8 pcm_flag;
static u8 inter_pred_idc;
static i16 mergeIdx;
static i16 mvp_lx[2];
static i16 ref_idx_lx[2];
static i16 mvd[4];
static i32 mvd_x;
static i32 mvd_y;
static u8 abs_mvd_greater1_flag_1;
static u8 abs_mvd_greater0_flag_1;
static u8 pcm_sample_luma[4096];
static u8 pcm_sample_chroma[4096];
static u8 is_pcm[4096];
static i32 pcm_skip_length;
static u8 ttStack_idx;
static u16 ttStack[10][10];
static u8 cbf_cb[32][32][4];
static u8 cbf_cr[32][32][4];
static u8 cbf_luma;
static u8 cur_intra_pred_mode;
static u8 split_transform_flag;
static u16 cbf_xBase;
static u16 cbf_yBase;
static u8 tu_idx;
static u16 tu_x0;
static u16 tu_y0;
static u16 tu_xBase;
static u16 tu_yBase;
static u8 tu_trafoDepth;
static u8 tu_blkIdx;
static u8 tu_log2TrafoSize;
static i8 qp_y_tab[131072];
static u16 rc_x0;
static u16 rc_y0;
static u8 rc_log2TrafoSize;
static u8 rc_scanIdx;
static u8 rc_cIdx;
static u8 ScanOrder[4][3][256][2];
static u8 significant_coeff_flag_idx[16];
static u8 nb_significant_coeff_flag;
static u8 coded_sub_block_flag[8][8];
static u8 LastSignificantCoeffX;
static u8 LastSignificantCoeffY;
static u16 num_coeff;
static u8 rc_lastScanPos;
static i8 rc_lastSubBlock;
static i8 rc_i;
static i16 tabTransCoeffLevel[1024];
static i32 add = 0;
static i32 scale;
static i32 scale_m;
static i32 dc_scale = 0;
static u8 scale_matrix[64];
static u8 shift = 0;
static i8 qp_y = 0;
static i16 qp;
static u16 rc_xS;
static u16 rc_yS;
static i8 m_end;
static u8 rc_ctxSet[1];
static u8 rc_greater1Ctx[1];
static u8 rc_firstSigScanPos;
static i8 rc_firstGreater1ScanPos;
static i8 rc_m;
static u8 coeff_abs_level_greater1_flag[16];
static u8 coeff_abs_level_greater2_flag;
static u16 coeff_sign_flag;
static u8 rc_signHidden;
static u8 rc_numSigCoeff;
static u8 rc_sumAbsLevel;
static u8 rc_cLastRiceParam;

////////////////////////////////////////////////////////////////////////////////
// Initial FSM state of the actor
enum states {
	my_state_byte_align,
	my_state_find_header,
	my_state_read_CodingQuadTree,
	my_state_read_CodingTree,
	my_state_read_CodingUnit,
	my_state_read_MVDCoding,
	my_state_read_MVDCoding_end,
	my_state_read_Nal_unit_header,
	my_state_read_PCMSample,
	my_state_read_PCMSampleLoop,
	my_state_read_PPS_Header,
	my_state_read_PredictionUnit,
	my_state_read_ResidualCoding,
	my_state_read_ResidualCodingGetCoeff,
	my_state_read_ResidualCodingGreater1,
	my_state_read_ResidualCodingStart,
	my_state_read_SEI_Header,
	my_state_read_SPS_Header,
	my_state_read_SaoParam,
	my_state_read_SliceData,
	my_state_read_SliceHeader,
	my_state_read_TransformTree,
	my_state_read_TransformUnit,
	my_state_read_VPS_Header,
	my_state_sendQp,
	my_state_send_IntraPredMode,
	my_state_start_code,
	my_state_weightedChroma0,
	my_state_weightedChroma0Offset,
	my_state_weightedChroma1,
	my_state_weightedChroma1Offset,
	my_state_weightedDeltaChroma0,
	my_state_weightedDeltaChroma1,
	my_state_weightedDeltaLuma0,
	my_state_weightedDeltaLuma1,
	my_state_weightedLuma0,
	my_state_weightedLuma1
};

static char *stateNames[] = {
	"byte_align",
	"find_header",
	"read_CodingQuadTree",
	"read_CodingTree",
	"read_CodingUnit",
	"read_MVDCoding",
	"read_MVDCoding_end",
	"read_Nal_unit_header",
	"read_PCMSample",
	"read_PCMSampleLoop",
	"read_PPS_Header",
	"read_PredictionUnit",
	"read_ResidualCoding",
	"read_ResidualCodingGetCoeff",
	"read_ResidualCodingGreater1",
	"read_ResidualCodingStart",
	"read_SEI_Header",
	"read_SPS_Header",
	"read_SaoParam",
	"read_SliceData",
	"read_SliceHeader",
	"read_TransformTree",
	"read_TransformUnit",
	"read_VPS_Header",
	"sendQp",
	"send_IntraPredMode",
	"start_code",
	"weightedChroma0",
	"weightedChroma0Offset",
	"weightedChroma1",
	"weightedChroma1Offset",
	"weightedDeltaChroma0",
	"weightedDeltaChroma1",
	"weightedDeltaLuma0",
	"weightedDeltaLuma1",
	"weightedLuma0",
	"weightedLuma1"
};

static enum states _FSM_state;



////////////////////////////////////////////////////////////////////////////////
// Token functions
static void read_byte() {
	index_byte = HevcDecoder_Algo_Parser_byte->read_inds[0];
	numTokens_byte = index_byte + fifo_u8_get_num_tokens(HevcDecoder_Algo_Parser_byte, 0);
}

static void read_end_byte() {
	HevcDecoder_Algo_Parser_byte->read_inds[0] = index_byte;
}

static void write_CUInfo() {
	index_CUInfo = HevcDecoder_Algo_Parser_CUInfo->write_ind;
	numFree_CUInfo = index_CUInfo + fifo_u16_get_room(HevcDecoder_Algo_Parser_CUInfo, NUM_READERS_CUInfo, SIZE_CUInfo);
}

static void write_end_CUInfo() {
	HevcDecoder_Algo_Parser_CUInfo->write_ind = index_CUInfo;
}
static void write_IntraPredMode() {
	index_IntraPredMode = HevcDecoder_Algo_Parser_IntraPredMode->write_ind;
	numFree_IntraPredMode = index_IntraPredMode + fifo_u8_get_room(HevcDecoder_Algo_Parser_IntraPredMode, NUM_READERS_IntraPredMode, SIZE_IntraPredMode);
}

static void write_end_IntraPredMode() {
	HevcDecoder_Algo_Parser_IntraPredMode->write_ind = index_IntraPredMode;
}
static void write_SliceAddr() {
	index_SliceAddr = HevcDecoder_Algo_Parser_SliceAddr->write_ind;
	numFree_SliceAddr = index_SliceAddr + fifo_u16_get_room(HevcDecoder_Algo_Parser_SliceAddr, NUM_READERS_SliceAddr, SIZE_SliceAddr);
}

static void write_end_SliceAddr() {
	HevcDecoder_Algo_Parser_SliceAddr->write_ind = index_SliceAddr;
}
static void write_TilesCoord() {
	index_TilesCoord = HevcDecoder_Algo_Parser_TilesCoord->write_ind;
	numFree_TilesCoord = index_TilesCoord + fifo_u16_get_room(HevcDecoder_Algo_Parser_TilesCoord, NUM_READERS_TilesCoord, SIZE_TilesCoord);
}

static void write_end_TilesCoord() {
	HevcDecoder_Algo_Parser_TilesCoord->write_ind = index_TilesCoord;
}
static void write_LcuSizeMax() {
	index_LcuSizeMax = HevcDecoder_Algo_Parser_LcuSizeMax->write_ind;
	numFree_LcuSizeMax = index_LcuSizeMax + fifo_u8_get_room(HevcDecoder_Algo_Parser_LcuSizeMax, NUM_READERS_LcuSizeMax, SIZE_LcuSizeMax);
}

static void write_end_LcuSizeMax() {
	HevcDecoder_Algo_Parser_LcuSizeMax->write_ind = index_LcuSizeMax;
}
static void write_PartMode() {
	index_PartMode = HevcDecoder_Algo_Parser_PartMode->write_ind;
	numFree_PartMode = index_PartMode + fifo_u8_get_room(HevcDecoder_Algo_Parser_PartMode, NUM_READERS_PartMode, SIZE_PartMode);
}

static void write_end_PartMode() {
	HevcDecoder_Algo_Parser_PartMode->write_ind = index_PartMode;
}
static void write_IsPicSlcLcu() {
	index_IsPicSlcLcu = HevcDecoder_Algo_Parser_IsPicSlcLcu->write_ind;
	numFree_IsPicSlcLcu = index_IsPicSlcLcu + fifo_u8_get_room(HevcDecoder_Algo_Parser_IsPicSlcLcu, NUM_READERS_IsPicSlcLcu, SIZE_IsPicSlcLcu);
}

static void write_end_IsPicSlcLcu() {
	HevcDecoder_Algo_Parser_IsPicSlcLcu->write_ind = index_IsPicSlcLcu;
}
static void write_IsPicSlc() {
	index_IsPicSlc = HevcDecoder_Algo_Parser_IsPicSlc->write_ind;
	numFree_IsPicSlc = index_IsPicSlc + fifo_u8_get_room(HevcDecoder_Algo_Parser_IsPicSlc, NUM_READERS_IsPicSlc, SIZE_IsPicSlc);
}

static void write_end_IsPicSlc() {
	HevcDecoder_Algo_Parser_IsPicSlc->write_ind = index_IsPicSlc;
}
static void write_LFAcrossSlcTile() {
	index_LFAcrossSlcTile = HevcDecoder_Algo_Parser_LFAcrossSlcTile->write_ind;
	numFree_LFAcrossSlcTile = index_LFAcrossSlcTile + fifo_u8_get_room(HevcDecoder_Algo_Parser_LFAcrossSlcTile, NUM_READERS_LFAcrossSlcTile, SIZE_LFAcrossSlcTile);
}

static void write_end_LFAcrossSlcTile() {
	HevcDecoder_Algo_Parser_LFAcrossSlcTile->write_ind = index_LFAcrossSlcTile;
}
static void write_PictSize() {
	index_PictSize = HevcDecoder_Algo_Parser_PictSize->write_ind;
	numFree_PictSize = index_PictSize + fifo_u16_get_room(HevcDecoder_Algo_Parser_PictSize, NUM_READERS_PictSize, SIZE_PictSize);
}

static void write_end_PictSize() {
	HevcDecoder_Algo_Parser_PictSize->write_ind = index_PictSize;
}
static void write_Poc() {
	index_Poc = HevcDecoder_Algo_Parser_Poc->write_ind;
	numFree_Poc = index_Poc + fifo_i16_get_room(HevcDecoder_Algo_Parser_Poc, NUM_READERS_Poc, SIZE_Poc);
}

static void write_end_Poc() {
	HevcDecoder_Algo_Parser_Poc->write_ind = index_Poc;
}
static void write_SaoSe() {
	index_SaoSe = HevcDecoder_Algo_Parser_SaoSe->write_ind;
	numFree_SaoSe = index_SaoSe + fifo_i16_get_room(HevcDecoder_Algo_Parser_SaoSe, NUM_READERS_SaoSe, SIZE_SaoSe);
}

static void write_end_SaoSe() {
	HevcDecoder_Algo_Parser_SaoSe->write_ind = index_SaoSe;
}
static void write_SEI_MD5() {
	index_SEI_MD5 = HevcDecoder_Algo_Parser_SEI_MD5->write_ind;
	numFree_SEI_MD5 = index_SEI_MD5 + fifo_u8_get_room(HevcDecoder_Algo_Parser_SEI_MD5, NUM_READERS_SEI_MD5, SIZE_SEI_MD5);
}

static void write_end_SEI_MD5() {
	HevcDecoder_Algo_Parser_SEI_MD5->write_ind = index_SEI_MD5;
}
static void write_SliceType() {
	index_SliceType = HevcDecoder_Algo_Parser_SliceType->write_ind;
	numFree_SliceType = index_SliceType + fifo_u8_get_room(HevcDecoder_Algo_Parser_SliceType, NUM_READERS_SliceType, SIZE_SliceType);
}

static void write_end_SliceType() {
	HevcDecoder_Algo_Parser_SliceType->write_ind = index_SliceType;
}
static void write_SplitTransform() {
	index_SplitTransform = HevcDecoder_Algo_Parser_SplitTransform->write_ind;
	numFree_SplitTransform = index_SplitTransform + fifo_i32_get_room(HevcDecoder_Algo_Parser_SplitTransform, NUM_READERS_SplitTransform, SIZE_SplitTransform);
}

static void write_end_SplitTransform() {
	HevcDecoder_Algo_Parser_SplitTransform->write_ind = index_SplitTransform;
}
static void write_TUSize() {
	index_TUSize = HevcDecoder_Algo_Parser_TUSize->write_ind;
	numFree_TUSize = index_TUSize + fifo_i8_get_room(HevcDecoder_Algo_Parser_TUSize, NUM_READERS_TUSize, SIZE_TUSize);
}

static void write_end_TUSize() {
	HevcDecoder_Algo_Parser_TUSize->write_ind = index_TUSize;
}
static void write_Coeff() {
	index_Coeff = HevcDecoder_Algo_Parser_Coeff->write_ind;
	numFree_Coeff = index_Coeff + fifo_i16_get_room(HevcDecoder_Algo_Parser_Coeff, NUM_READERS_Coeff, SIZE_Coeff);
}

static void write_end_Coeff() {
	HevcDecoder_Algo_Parser_Coeff->write_ind = index_Coeff;
}
static void write_StrongIntraSmoothing() {
	index_StrongIntraSmoothing = HevcDecoder_Algo_Parser_StrongIntraSmoothing->write_ind;
	numFree_StrongIntraSmoothing = index_StrongIntraSmoothing + fifo_i32_get_room(HevcDecoder_Algo_Parser_StrongIntraSmoothing, NUM_READERS_StrongIntraSmoothing, SIZE_StrongIntraSmoothing);
}

static void write_end_StrongIntraSmoothing() {
	HevcDecoder_Algo_Parser_StrongIntraSmoothing->write_ind = index_StrongIntraSmoothing;
}
static void write_DispCoord() {
	index_DispCoord = HevcDecoder_Algo_Parser_DispCoord->write_ind;
	numFree_DispCoord = index_DispCoord + fifo_u16_get_room(HevcDecoder_Algo_Parser_DispCoord, NUM_READERS_DispCoord, SIZE_DispCoord);
}

static void write_end_DispCoord() {
	HevcDecoder_Algo_Parser_DispCoord->write_ind = index_DispCoord;
}
static void write_PicSizeInMb() {
	index_PicSizeInMb = HevcDecoder_Algo_Parser_PicSizeInMb->write_ind;
	numFree_PicSizeInMb = index_PicSizeInMb + fifo_u16_get_room(HevcDecoder_Algo_Parser_PicSizeInMb, NUM_READERS_PicSizeInMb, SIZE_PicSizeInMb);
}

static void write_end_PicSizeInMb() {
	HevcDecoder_Algo_Parser_PicSizeInMb->write_ind = index_PicSizeInMb;
}
static void write_NumRefIdxLxActive() {
	index_NumRefIdxLxActive = HevcDecoder_Algo_Parser_NumRefIdxLxActive->write_ind;
	numFree_NumRefIdxLxActive = index_NumRefIdxLxActive + fifo_u8_get_room(HevcDecoder_Algo_Parser_NumRefIdxLxActive, NUM_READERS_NumRefIdxLxActive, SIZE_NumRefIdxLxActive);
}

static void write_end_NumRefIdxLxActive() {
	HevcDecoder_Algo_Parser_NumRefIdxLxActive->write_ind = index_NumRefIdxLxActive;
}
static void write_RefPicListModif() {
	index_RefPicListModif = HevcDecoder_Algo_Parser_RefPicListModif->write_ind;
	numFree_RefPicListModif = index_RefPicListModif + fifo_u8_get_room(HevcDecoder_Algo_Parser_RefPicListModif, NUM_READERS_RefPicListModif, SIZE_RefPicListModif);
}

static void write_end_RefPicListModif() {
	HevcDecoder_Algo_Parser_RefPicListModif->write_ind = index_RefPicListModif;
}
static void write_RefPoc() {
	index_RefPoc = HevcDecoder_Algo_Parser_RefPoc->write_ind;
	numFree_RefPoc = index_RefPoc + fifo_i16_get_room(HevcDecoder_Algo_Parser_RefPoc, NUM_READERS_RefPoc, SIZE_RefPoc);
}

static void write_end_RefPoc() {
	HevcDecoder_Algo_Parser_RefPoc->write_ind = index_RefPoc;
}
static void write_MvPredSyntaxElem() {
	index_MvPredSyntaxElem = HevcDecoder_Algo_Parser_MvPredSyntaxElem->write_ind;
	numFree_MvPredSyntaxElem = index_MvPredSyntaxElem + fifo_i16_get_room(HevcDecoder_Algo_Parser_MvPredSyntaxElem, NUM_READERS_MvPredSyntaxElem, SIZE_MvPredSyntaxElem);
}

static void write_end_MvPredSyntaxElem() {
	HevcDecoder_Algo_Parser_MvPredSyntaxElem->write_ind = index_MvPredSyntaxElem;
}
static void write_Cbf() {
	index_Cbf = HevcDecoder_Algo_Parser_Cbf->write_ind;
	numFree_Cbf = index_Cbf + fifo_i32_get_room(HevcDecoder_Algo_Parser_Cbf, NUM_READERS_Cbf, SIZE_Cbf);
}

static void write_end_Cbf() {
	HevcDecoder_Algo_Parser_Cbf->write_ind = index_Cbf;
}
static void write_DBFDisable() {
	index_DBFDisable = HevcDecoder_Algo_Parser_DBFDisable->write_ind;
	numFree_DBFDisable = index_DBFDisable + fifo_i32_get_room(HevcDecoder_Algo_Parser_DBFDisable, NUM_READERS_DBFDisable, SIZE_DBFDisable);
}

static void write_end_DBFDisable() {
	HevcDecoder_Algo_Parser_DBFDisable->write_ind = index_DBFDisable;
}
static void write_DbfSe() {
	index_DbfSe = HevcDecoder_Algo_Parser_DbfSe->write_ind;
	numFree_DbfSe = index_DbfSe + fifo_i8_get_room(HevcDecoder_Algo_Parser_DbfSe, NUM_READERS_DbfSe, SIZE_DbfSe);
}

static void write_end_DbfSe() {
	HevcDecoder_Algo_Parser_DbfSe->write_ind = index_DbfSe;
}
static void write_ReorderPics() {
	index_ReorderPics = HevcDecoder_Algo_Parser_ReorderPics->write_ind;
	numFree_ReorderPics = index_ReorderPics + fifo_i8_get_room(HevcDecoder_Algo_Parser_ReorderPics, NUM_READERS_ReorderPics, SIZE_ReorderPics);
}

static void write_end_ReorderPics() {
	HevcDecoder_Algo_Parser_ReorderPics->write_ind = index_ReorderPics;
}
static void write_WeightedPred() {
	index_WeightedPred = HevcDecoder_Algo_Parser_WeightedPred->write_ind;
	numFree_WeightedPred = index_WeightedPred + fifo_i16_get_room(HevcDecoder_Algo_Parser_WeightedPred, NUM_READERS_WeightedPred, SIZE_WeightedPred);
}

static void write_end_WeightedPred() {
	HevcDecoder_Algo_Parser_WeightedPred->write_ind = index_WeightedPred;
}
static void write_Qp() {
	index_Qp = HevcDecoder_Algo_Parser_Qp->write_ind;
	numFree_Qp = index_Qp + fifo_i8_get_room(HevcDecoder_Algo_Parser_Qp, NUM_READERS_Qp, SIZE_Qp);
}

static void write_end_Qp() {
	HevcDecoder_Algo_Parser_Qp->write_ind = index_Qp;
}

////////////////////////////////////////////////////////////////////////////////
// Functions/procedures
static i32 HevcDecoder_Algo_Parser_min(i32 a, i32 b);
static i32 HevcDecoder_Algo_Parser_isFifoFull(u16 fifo[10]);
static void HevcDecoder_Algo_Parser_byte_align(u16 fifo[10]);
static u16 HevcDecoder_Algo_Parser_getFifoIdx(u16 cptBits, u16 fifo[10]);
static i32 HevcDecoder_Algo_Parser_IsStartCode(u16 fifo[10]);
static void HevcDecoder_Algo_Parser_flushBits(u8 nb, u16 fifo[10]);
static void HevcDecoder_Algo_Parser_flushBits_name(u8 nb, u16 fifo[10], char * name);
static void HevcDecoder_Algo_Parser_showXBits(u8 nb, u16 fifo[10], u32 res[1]);
static void HevcDecoder_Algo_Parser_getBits(u8 nb, u16 fifo[10], i32 res[1]);
static void HevcDecoder_Algo_Parser_vld_u(u8 nb, u16 fifo[10], i32 res[1]);
static void HevcDecoder_Algo_Parser_vld_u_name(u8 nb, u16 fifo[10], i32 res[1], char * name);
static void HevcDecoder_Algo_Parser_vld_ue(u16 fifo[10], i32 res[1]);
static void HevcDecoder_Algo_Parser_vld_ue_name(u16 fifo[10], i32 res[1], char * name);
static i32 HevcDecoder_Algo_Parser_isByteAlign(u16 fifo[10]);
static void HevcDecoder_Algo_Parser_vld_se(u16 fifo[10], i32 res[1]);
static void HevcDecoder_Algo_Parser_vld_se_name(u16 fifo[10], i32 res[1], char * name);
static void HevcDecoder_Algo_Parser_sortDeltaPOC(u32 sps_id, u32 idx, i8 pcRPS[15][65][131]);
static void HevcDecoder_Algo_Parser_parseShortTermRefPicSet(u32 sps_id, u32 idx, u8 num_short_term_ref_pic_sets, u16 fifo[10], i8 pcRPS[15][65][131]);
static i32 HevcDecoder_Algo_Parser_log2(i32 v);
static void HevcDecoder_Algo_Parser_InitScanningArray(u8 ScanOrder[4][3][256][2]);
static u32 HevcDecoder_Algo_Parser_InverseRasterScan(u32 a, u32 b, u32 c, u32 d, u32 e);
static i32 HevcDecoder_Algo_Parser_log2_i16(i32 v);
static void HevcDecoder_Algo_Parser_renormD(u16 codIRange[1], u16 codIOffset[1], u16 fifo[10]);
static void HevcDecoder_Algo_Parser_decodeTerminate(u16 codIRange[1], u16 codIOffset[1], u32 binVal[1], u16 fifo[10]);
static void HevcDecoder_Algo_Parser_decodeTerminateTop(u32 binString[1], u16 codIRange[1], u16 codIOffset[1], u16 fifo[10]);
static void HevcDecoder_Algo_Parser_get_END_OF_SLICE_FLAG(u16 codIRange[1], u16 codIOffset[1], u16 fifo[10], u32 debinValue[1]);
static void HevcDecoder_Algo_Parser_byte_alignment(u16 fifo[10]);
static void HevcDecoder_Algo_Parser_decodeStart(u16 codIRange[1], u16 codIOffset[1], u16 fifo[10]);
static i32 HevcDecoder_Algo_Parser_clip_i32(i32 Value, i32 minVal, i32 maxVal);
static void HevcDecoder_Algo_Parser_contextInit(u8 qp, u8 sliceType, u16 ctxTable[30][48], u8 cabac_init_flag);
static void HevcDecoder_Algo_Parser_decodeReInit(u16 codIRange[1], u16 codIOffset[1], u16 fifo[10]);
static void HevcDecoder_Algo_Parser_get_END_OF_SUB_STREAM_ONE_BIT(u16 codIRange[1], u16 codIOffset[1], u16 fifo[10], u32 debinValue[1]);
static void HevcDecoder_Algo_Parser_decodeDecision(u16 codIRange[1], u16 codIOffset[1], u8 state[1], u8 mps[1], u8 binVal[1], u16 fifo[10]);
static void HevcDecoder_Algo_Parser_decodeDecisionTop(u16 ctxIdx, u32 binString[1], u16 codIRange[1], u16 codIOffset[1], u16 ctxTable[30][48], u8 se, u16 fifo[10]);
static void HevcDecoder_Algo_Parser_get_SAO_MERGE_FLAG(u16 codIRange[1], u16 codIOffset[1], u16 ctxTable[30][48], u16 fifo[10], u32 debinValue[1]);
static void HevcDecoder_Algo_Parser_decodeBypass(u16 codIRange[1], u16 codIOffset[1], u8 binVal[1], u16 fifo[10]);
static void HevcDecoder_Algo_Parser_decodeBypassTop(u32 binString[1], u16 codIRange[1], u16 codIOffset[1], u16 fifo[10]);
static void HevcDecoder_Algo_Parser_get_SAO_TYPE_IDX(u16 codIRange[1], u16 codIOffset[1], u16 ctxTable[30][48], u16 fifo[10], u32 debinValue[1]);
static void HevcDecoder_Algo_Parser_debinTU(u32 binString, u8 binIdx, u8 binarization, u8 debinCompleted[1], u32 debinValue[1], u8 discard_suffix[1]);
static void HevcDecoder_Algo_Parser_get_SAO_OFFSET_ABS(u8 offsetTh, u16 codIRange[1], u16 codIOffset[1], u16 fifo[10], u32 debinValue[1]);
static void HevcDecoder_Algo_Parser_get_SAO_OFFSET_SIGN(u16 codIRange[1], u16 codIOffset[1], u16 fifo[10], u32 debinValue[1]);
static void HevcDecoder_Algo_Parser_decodeBinsEP(u8 numBins, u32 binString[1], u16 codIRange[1], u16 codIOffset[1], u16 fifo[10]);
static void HevcDecoder_Algo_Parser_get_SAO_BAND_POSITION(u16 codIRange[1], u16 codIOffset[1], u16 fifo[10], u32 debinValue[1]);
static void HevcDecoder_Algo_Parser_get_SAO_EO(u16 codIRange[1], u16 codIOffset[1], u16 fifo[10], u32 debinValue[1]);
static u8 HevcDecoder_Algo_Parser_context_93311_SKIP_CU_FLAG(u8 depthSubPart, i32 availableA, u8 depthSubPartA, i32 availableB, u8 depthSubPartB);
static void HevcDecoder_Algo_Parser_get_SPLIT_CODING_UNIT_FLAG(u16 codIRange[1], u16 codIOffset[1], u16 ctxTable[30][48], u16 fifo[10], u32 debinValue[1], u8 depthSubPart, i32 availableA, u8 depthSubPartA, i32 availableB, u8 depthSubPartB);
static void HevcDecoder_Algo_Parser_get_CU_TRANSQUANT_BYPASS_FLAG(u16 codIRange[1], u16 codIOffset[1], u16 ctxTable[30][48], u16 fifo[10], u32 debinValue[1]);
static void HevcDecoder_Algo_Parser_get_SKIP_FLAG(u16 codIRange[1], u16 codIOffset[1], u16 ctxTable[30][48], u16 fifo[10], u32 debinValue[1], u8 skip_flag[4096][2], u16 cu_x0, u16 cu_y0, i32 leftFlag, i32 upFlag);
static void HevcDecoder_Algo_Parser_intra_prediction_unit_default_value(u16 x0, u16 y0, u8 log2_cb_size, u8 part_mode, u8 log2_min_pu_size, u8 intraPredMode[4096][2]);
static void HevcDecoder_Algo_Parser_get_PRED_MODE_FLAG(u16 codIRange[1], u16 codIOffset[1], u16 ctxTable[30][48], u16 fifo[10], u32 debinValue[1]);
static void HevcDecoder_Algo_Parser_get_PART_SIZE(u16 codIRange[1], u16 codIOffset[1], u16 ctxTable[30][48], u16 fifo[10], u32 debinValue[1], i32 isIntra, u8 cu_log2CbSize, u8 Log2MinCbSize, u8 amp_enabled_flag);
static void HevcDecoder_Algo_Parser_get_PCM_FLAG(u16 codIRange[1], u16 codIOffset[1], u16 fifo[10], u32 debinValue[1]);
static void HevcDecoder_Algo_Parser_get_PREV_INTRA_LUMA_PRED_FLAG(u16 codIRange[1], u16 codIOffset[1], u16 ctxTable[30][48], u16 fifo[10], u32 debinValue[1]);
static void HevcDecoder_Algo_Parser_get_MPM_IDX(u16 codIRange[1], u16 codIOffset[1], u16 fifo[10], u32 debinValue[1]);
static void HevcDecoder_Algo_Parser_get_REM_INTRA_LUMA_PRED_MODE(u16 codIRange[1], u16 codIOffset[1], u16 fifo[10], i32 debinValue[1]);
static void HevcDecoder_Algo_Parser_luma_intra_pred_mode(u16 x0, u16 y0, u8 pu_size, u8 prev_intra_luma_pred_flag, u32 mpm_idx_or_rem_intra_luma_pred_mode, u32 ret[1], u8 log2_min_pu_size, u8 log2_ctb_size, u8 intraPredMode[4096][2], i32 upFlag, i32 leftFlag);
static void HevcDecoder_Algo_Parser_get_INTRA_CHROMA_PRED_MODE(u16 codIRange[1], u16 codIOffset[1], u16 ctxTable[30][48], u16 fifo[10], u32 debinValue[1]);
static void HevcDecoder_Algo_Parser_get_NO_RESIDUAL_SYNTAX_FLAG(u16 codIRange[1], u16 codIOffset[1], u16 ctxTable[30][48], u16 fifo[10], u32 debinValue[1]);
static void HevcDecoder_Algo_Parser_get_MERGE_IDX(u16 codIRange[1], u16 codIOffset[1], u16 ctxTable[30][48], u16 fifo[10], u32 debinValue[1], u8 MaxNumMergeCand);
static void HevcDecoder_Algo_Parser_get_MERGE_FLAG(u16 codIRange[1], u16 codIOffset[1], u16 ctxTable[30][48], u16 fifo[10], u32 debinValue[1]);
static void HevcDecoder_Algo_Parser_get_INTER_PRED_IDC(u16 codIRange[1], u16 codIOffset[1], u16 ctxTable[30][48], u16 fifo[10], u32 debinValue[1], u8 partMode, u8 PbW, u8 PbH, u8 ctDepth);
static void HevcDecoder_Algo_Parser_get_REF_IDX_LX(u16 codIRange[1], u16 codIOffset[1], u16 ctxTable[30][48], u16 fifo[10], u32 debinValue[1], u8 num_ref_idx_lx_active_minus1);
static void HevcDecoder_Algo_Parser_get_MVP_LX_FLAG(u16 codIRange[1], u16 codIOffset[1], u16 ctxTable[30][48], u16 fifo[10], u32 debinValue[1]);
static void HevcDecoder_Algo_Parser_get_ABS_MVD_GREATER0_FLAG(u16 codIRange[1], u16 codIOffset[1], u16 ctxTable[30][48], u16 fifo[10], u32 debinValue[1]);
static void HevcDecoder_Algo_Parser_get_ABS_MVD_GREATER1_FLAG(u16 codIRange[1], u16 codIOffset[1], u16 ctxTable[30][48], u16 fifo[10], u32 debinValue[1]);
static void HevcDecoder_Algo_Parser_xReadEpExGolomb(u32 count_int, u32 debinValue[1], u16 codIRange[1], u16 codIOffset[1], u16 fifo[10]);
static void HevcDecoder_Algo_Parser_get_ABS_MVD_MINUS2(u16 codIRange[1], u16 codIOffset[1], u16 fifo[10], u32 debinValue[1]);
static void HevcDecoder_Algo_Parser_get_MVD_SIGN_FLAG(u16 codIRange[1], u16 codIOffset[1], u16 fifo[10], u32 debinValue[1]);
static void HevcDecoder_Algo_Parser_get_SPLIT_TRANSFORM_FLAG(u16 codIRange[1], u16 codIOffset[1], u16 ctxTable[30][48], u16 fifo[10], u32 debinValue[1], u8 log2TransformBlockSize);
static void HevcDecoder_Algo_Parser_get_CBF_CB_CR(u16 codIRange[1], u16 codIOffset[1], u16 ctxTable[30][48], u16 fifo[10], u32 debinValue[1], u8 trafoDepth);
static void HevcDecoder_Algo_Parser_get_CBF_LUMA(u16 codIRange[1], u16 codIOffset[1], u16 ctxTable[30][48], u16 fifo[10], u32 debinValue[1], u8 trafoDepth);
static void HevcDecoder_Algo_Parser_get_CU_QP_DELTA_ABS(u16 codIRange[1], u16 codIOffset[1], u16 ctxTable[30][48], u16 fifo[10], u32 debinValue[1]);
static void HevcDecoder_Algo_Parser_get_CU_QP_DELTA_SIGN_FLAG(u16 codIRange[1], u16 codIOffset[1], u16 fifo[10], u32 debinValue[1]);
static u8 HevcDecoder_Algo_Parser_getScanIdx(u8 predMode, u8 log2TrafoSize, u8 intraPredMode);
static void HevcDecoder_Algo_Parser_get_TRANSFORM_SKIP_FLAG(u16 codIRange[1], u16 codIOffset[1], u16 ctxTable[30][48], u16 fifo[10], u32 debinValue[1], u8 rc_TType);
static u8 HevcDecoder_Algo_Parser_context_93312(u8 binIdx, u8 log2TrafoSize, u8 cIdx);
static void HevcDecoder_Algo_Parser_get_LAST_SIGNIFICANT_COEFF_X_PREFIX(u16 codIRange[1], u16 codIOffset[1], u16 ctxTable[30][48], u16 fifo[10], u32 debinValue[1], u8 log2TrafoWidth, u8 cIdx);
static void HevcDecoder_Algo_Parser_get_LAST_SIGNIFICANT_COEFF_Y_PREFIX(u16 codIRange[1], u16 codIOffset[1], u16 ctxTable[30][48], u16 fifo[10], u32 debinValue[1], u8 log2TrafoHeight, u8 cIdx);
static void HevcDecoder_Algo_Parser_get_LAST_SIGNIFICANT_COEFF_XY_SUFFIX(u16 codIRange[1], u16 codIOffset[1], u16 fifo[10], u32 debinValue[1], u8 prefix);
static void HevcDecoder_Algo_Parser_context_93313(u8 coded_sub_block_flag[8][8], u16 xS, u16 yS, u8 cIdx, u8 log2TrafoSize, u16 ctxIdx[1]);
static void HevcDecoder_Algo_Parser_get_CODED_SUB_BLOCK_FLAG(u16 codIRange[1], u16 codIOffset[1], u16 ctxTable[30][48], u16 fifo[10], u32 debinValue[1], u8 coded_sub_block_flag[8][8], u16 xC, u16 yC, u8 cIdx, u8 log2TrafoSize);
static void HevcDecoder_Algo_Parser_context_93314(u8 coded_sub_block_flag[8][8], u16 xC, u16 yC, u8 cIdx, u8 log2TrafoSize, u8 scanIdx, u16 ctxIdx[1]);
static void HevcDecoder_Algo_Parser_get_SIGNIFICANT_COEFF_FLAG(u16 codIRange[1], u16 codIOffset[1], u16 ctxTable[30][48], u16 fifo[10], u32 debinValue[1], u8 coded_sub_block_flag[8][8], u16 xC, u16 yC, u8 cIdx, u8 log2TrafoSize, u8 scanIdx);
static void HevcDecoder_Algo_Parser_context_93315(u8 cIdx, i8 i, i32 first_elem, i32 first_subset, u8 ctxSet[1], u8 greater1Ctx[1], u16 ctxIdxInc[1]);
static void HevcDecoder_Algo_Parser_get_COEFF_ABS_LEVEL_GREATER1_FLAG(u16 codIRange[1], u16 codIOffset[1], u16 ctxTable[30][48], u16 fifo[10], i32 debinValue[1], u16 ctxIdx);
static void HevcDecoder_Algo_Parser_get_COEFF_ABS_LEVEL_GREATER2_FLAG(u16 codIRange[1], u16 codIOffset[1], u16 ctxTable[30][48], u16 fifo[10], u32 debinValue[1], u8 cIdx, u8 ctxSet);
static void HevcDecoder_Algo_Parser_get_COEFF_SIGN_FLAG(u16 codIRange[1], u16 codIOffset[1], u16 fifo[10], u32 debinValue[1], u8 nb);
static void HevcDecoder_Algo_Parser_get_COEFF_ABS_LEVEL(u16 codIRange[1], u16 codIOffset[1], u16 fifo[10], u32 debinValue[1], u8 rParam);
static void compute_POC(i32 pic_order_cnt_lsb);
static void setRefTables(i32 sps_id, i32 idx, i8 pc_rps[15][65][131], i32 poc);
static void set_qPy();
static void set_deblocking_bypass(u16 x0, u16 y0, u8 logSize);

static i32 HevcDecoder_Algo_Parser_min(i32 a, i32 b) {
	i32 tmp_if;

	if (a < b) {
		tmp_if = a;
	} else {
		tmp_if = b;
	}
	return tmp_if;
}
static i32 HevcDecoder_Algo_Parser_isFifoFull(u16 fifo[10]) {
	u8 local_FIFO_CPT_BITS;
	u16 tmp_fifo;
	u8 local_FIFO_SIZE;

	local_FIFO_CPT_BITS = HevcDecoder_Algo_Parser_FIFO_CPT_BITS;
	tmp_fifo = fifo[local_FIFO_CPT_BITS];
	local_FIFO_SIZE = HevcDecoder_Algo_Parser_FIFO_SIZE;
	return tmp_fifo >= (local_FIFO_SIZE - 1) << 3;
}
static void HevcDecoder_Algo_Parser_byte_align(u16 fifo[10]) {
	u8 local_FIFO_CPT_BITS;
	u16 cptBits;

	local_FIFO_CPT_BITS = HevcDecoder_Algo_Parser_FIFO_CPT_BITS;
	cptBits = fifo[local_FIFO_CPT_BITS];
	local_FIFO_CPT_BITS = HevcDecoder_Algo_Parser_FIFO_CPT_BITS;
	fifo[local_FIFO_CPT_BITS] = cptBits - (cptBits & 7);
}
static u16 HevcDecoder_Algo_Parser_getFifoIdx(u16 cptBits, u16 fifo[10]) {
	u8 local_FIFO_IDX;
	u16 fifo_idx;
	u8 local_FIFO_SIZE;
	i16 tmp_if;

	local_FIFO_IDX = HevcDecoder_Algo_Parser_FIFO_IDX;
	fifo_idx = fifo[local_FIFO_IDX];
	local_FIFO_SIZE = HevcDecoder_Algo_Parser_FIFO_SIZE;
	if ((cptBits & local_FIFO_SIZE - 1) != 0) {
		local_FIFO_SIZE = HevcDecoder_Algo_Parser_FIFO_SIZE;
		tmp_if = fifo_idx - 1 - (cptBits >> 3) & local_FIFO_SIZE - 1;
	} else {
		local_FIFO_SIZE = HevcDecoder_Algo_Parser_FIFO_SIZE;
		tmp_if = fifo_idx - (cptBits >> 3) & local_FIFO_SIZE - 1;
	}
	return tmp_if;
}
static i32 HevcDecoder_Algo_Parser_IsStartCode(u16 fifo[10]) {
	u8 local_FIFO_CPT_BITS;
	u16 cptBits;
	u16 idx;
	u16 tmp_fifo;
	u8 local_FIFO_DEPTH;
	i32 tmp_if;

	local_FIFO_CPT_BITS = HevcDecoder_Algo_Parser_FIFO_CPT_BITS;
	cptBits = fifo[local_FIFO_CPT_BITS];
	idx = HevcDecoder_Algo_Parser_getFifoIdx(cptBits, fifo);
	tmp_fifo = fifo[idx];
	local_FIFO_DEPTH = HevcDecoder_Algo_Parser_FIFO_DEPTH;
	if ((tmp_fifo & 1 << (local_FIFO_DEPTH - 1)) != 0) {
		tmp_if = 1;
	} else {
		tmp_if = 0;
	}
	return tmp_if;
}
static void HevcDecoder_Algo_Parser_flushBits(u8 nb, u16 fifo[10]) {
	u8 local_FIFO_CPT_BITS;
	u16 tmp_fifo;

	local_FIFO_CPT_BITS = HevcDecoder_Algo_Parser_FIFO_CPT_BITS;
	local_FIFO_CPT_BITS = HevcDecoder_Algo_Parser_FIFO_CPT_BITS;
	tmp_fifo = fifo[local_FIFO_CPT_BITS];
	fifo[local_FIFO_CPT_BITS] = tmp_fifo - nb;
}
static void HevcDecoder_Algo_Parser_flushBits_name(u8 nb, u16 fifo[10], char * name) {
	i32 local_DEBUG_PARSER;

	HevcDecoder_Algo_Parser_flushBits(nb, fifo);
	local_DEBUG_PARSER = HevcDecoder_Algo_Parser_DEBUG_PARSER;
	if (local_DEBUG_PARSER) {
		printf("          %s u(%u) : 0\n", name, nb);
	}
}
static void HevcDecoder_Algo_Parser_showXBits(u8 nb, u16 fifo[10], u32 res[1]) {
	u8 local_FIFO_CPT_BITS;
	u16 cptBits;
	u16 idx;
	u8 local_FIFO_SIZE;
	u8 cpt;
	i32 local_DEBUG_PARSER;
	u16 tmp_fifo;
	u16 tmp_fifo0;
	u16 tmp_fifo1;
	u16 tmp_fifo2;
	u32 tmp_res;

	local_FIFO_CPT_BITS = HevcDecoder_Algo_Parser_FIFO_CPT_BITS;
	cptBits = fifo[local_FIFO_CPT_BITS];
	idx = HevcDecoder_Algo_Parser_getFifoIdx(cptBits, fifo);
	local_FIFO_SIZE = HevcDecoder_Algo_Parser_FIFO_SIZE;
	local_FIFO_SIZE = HevcDecoder_Algo_Parser_FIFO_SIZE;
	cpt = 8 - (cptBits & local_FIFO_SIZE - 1) & local_FIFO_SIZE - 1;
	local_DEBUG_PARSER = HevcDecoder_Algo_Parser_DEBUG_PARSER;
	if (local_DEBUG_PARSER) {
		if (nb > cptBits) {
			printf(" Error showBits : out of range !!! nb %u cptBits %u\n", nb, cptBits);
		}
	}
	tmp_fifo = fifo[idx];
	local_FIFO_SIZE = HevcDecoder_Algo_Parser_FIFO_SIZE;
	tmp_fifo0 = fifo[idx + 1 & local_FIFO_SIZE - 1];
	local_FIFO_SIZE = HevcDecoder_Algo_Parser_FIFO_SIZE;
	tmp_fifo1 = fifo[idx + 2 & local_FIFO_SIZE - 1];
	local_FIFO_SIZE = HevcDecoder_Algo_Parser_FIFO_SIZE;
	tmp_fifo2 = fifo[idx + 3 & local_FIFO_SIZE - 1];
	res[0] = tmp_fifo << 24 | tmp_fifo0 << 16 | tmp_fifo1 << 8 | tmp_fifo2;
	tmp_res = res[0];
	res[0] = (tmp_res << cpt) >> (32 - nb) & (1 << nb) - 1;
}
static void HevcDecoder_Algo_Parser_getBits(u8 nb, u16 fifo[10], i32 res[1]) {

	if (nb == 0) {
		res[0] = 0;
	} else {
		HevcDecoder_Algo_Parser_showXBits(nb, fifo, res);
		HevcDecoder_Algo_Parser_flushBits(nb, fifo);
	}
}
static void HevcDecoder_Algo_Parser_vld_u(u8 nb, u16 fifo[10], i32 res[1]) {

	HevcDecoder_Algo_Parser_getBits(nb, fifo, res);
}
static void HevcDecoder_Algo_Parser_vld_u_name(u8 nb, u16 fifo[10], i32 res[1], char * name) {
	i32 local_DEBUG_PARSER;
	i32 tmp_res;

	HevcDecoder_Algo_Parser_vld_u(nb, fifo, res);
	local_DEBUG_PARSER = HevcDecoder_Algo_Parser_DEBUG_PARSER;
	if (local_DEBUG_PARSER) {
		tmp_res = res[0];
		printf("          %s u(%u) : %i\n", name, nb, tmp_res);
	}
}
static void HevcDecoder_Algo_Parser_vld_ue(u16 fifo[10], i32 res[1]) {
	u8 local_FIFO_CPT_BITS;
	u16 cptBits;
	u16 idx;
	u8 local_FIFO_SIZE;
	u8 cpt;
	u16 cptSave;
	u32 codeLen;
	u16 tmp_fifo;
	i32 local_DEBUG_PARSER;
	i32 tmp_res;

	local_FIFO_CPT_BITS = HevcDecoder_Algo_Parser_FIFO_CPT_BITS;
	cptBits = fifo[local_FIFO_CPT_BITS];
	idx = HevcDecoder_Algo_Parser_getFifoIdx(cptBits, fifo);
	local_FIFO_SIZE = HevcDecoder_Algo_Parser_FIFO_SIZE;
	cpt = cptBits - 1 & local_FIFO_SIZE - 1;
	cptSave = cptBits;
	tmp_fifo = fifo[idx];
	while ((tmp_fifo >> cpt & 1) == 0) {
		local_DEBUG_PARSER = HevcDecoder_Algo_Parser_DEBUG_PARSER;
		if (local_DEBUG_PARSER) {
			if (cptBits == 0) {
				printf(" Error vld_ue : out of range !!!\n");
			}
		}
		cptBits = cptBits - 1;
		idx = HevcDecoder_Algo_Parser_getFifoIdx(cptBits, fifo);
		local_FIFO_SIZE = HevcDecoder_Algo_Parser_FIFO_SIZE;
		cpt = cpt - 1 & local_FIFO_SIZE - 1;
		tmp_fifo = fifo[idx];
	}
	codeLen = cptSave - cptBits;
	local_FIFO_CPT_BITS = HevcDecoder_Algo_Parser_FIFO_CPT_BITS;
	fifo[local_FIFO_CPT_BITS] = cptBits - 1;
	HevcDecoder_Algo_Parser_vld_u(codeLen, fifo, res);
	tmp_res = res[0];
	res[0] = (1 << codeLen) + tmp_res - 1;
}
static void HevcDecoder_Algo_Parser_vld_ue_name(u16 fifo[10], i32 res[1], char * name) {
	i32 local_DEBUG_PARSER;
	i32 tmp_res;

	HevcDecoder_Algo_Parser_vld_ue(fifo, res);
	local_DEBUG_PARSER = HevcDecoder_Algo_Parser_DEBUG_PARSER;
	if (local_DEBUG_PARSER) {
		tmp_res = res[0];
		printf("          %s u(v) : %i\n", name, tmp_res);
	}
}
static i32 HevcDecoder_Algo_Parser_isByteAlign(u16 fifo[10]) {
	u8 local_FIFO_CPT_BITS;
	u16 cptBits;

	local_FIFO_CPT_BITS = HevcDecoder_Algo_Parser_FIFO_CPT_BITS;
	cptBits = fifo[local_FIFO_CPT_BITS];
	return (cptBits & 7) == 0;
}
static void HevcDecoder_Algo_Parser_vld_se(u16 fifo[10], i32 res[1]) {
	i32 tmp_res;
	i32 tmp_res0;
	i32 tmp_res1;

	HevcDecoder_Algo_Parser_vld_ue(fifo, res);
	tmp_res = res[0];
	if ((tmp_res & 1) == 0) {
		tmp_res0 = res[0];
		res[0] = -(tmp_res0 >> 1);
	} else {
		tmp_res1 = res[0];
		res[0] = (tmp_res1 >> 1) + 1;
	}
}
static void HevcDecoder_Algo_Parser_vld_se_name(u16 fifo[10], i32 res[1], char * name) {
	i32 local_DEBUG_PARSER;
	i32 tmp_res;

	HevcDecoder_Algo_Parser_vld_se(fifo, res);
	local_DEBUG_PARSER = HevcDecoder_Algo_Parser_DEBUG_PARSER;
	if (local_DEBUG_PARSER) {
		tmp_res = res[0];
		printf("          %s s(v) : %i\n", name, tmp_res);
	}
}
static void HevcDecoder_Algo_Parser_sortDeltaPOC(u32 sps_id, u32 idx, i8 pcRPS[15][65][131]) {
	i32 deltaPOC_v;
	i8 used_v;
	u32 k;
	i32 tmp;
	u8 local_NUM_PICS;
	i8 tmp_pcRPS;
	u8 i;
	i8 tmp_pcRPS0;
	u8 local_DELTAPOC;
	u8 local_USED;
	u8 j;
	i8 tmp_pcRPS1;
	u8 local_NUM_NEGATIVE_PICS;
	i8 tmp_pcRPS2;
	i8 tmp_pcRPS3;
	u8 i0;
	i8 tmp_pcRPS4;
	i8 tmp_pcRPS5;
	i8 tmp_pcRPS6;

	local_NUM_PICS = HevcDecoder_Algo_Parser_NUM_PICS;
	tmp_pcRPS = pcRPS[sps_id][idx][local_NUM_PICS];
	if (tmp_pcRPS != 0) {
		i = 1;
		local_NUM_PICS = HevcDecoder_Algo_Parser_NUM_PICS;
		tmp_pcRPS0 = pcRPS[sps_id][idx][local_NUM_PICS];
		while (i <= tmp_pcRPS0 - 1) {
			local_DELTAPOC = HevcDecoder_Algo_Parser_DELTAPOC;
			deltaPOC_v = pcRPS[sps_id][idx][local_DELTAPOC + i];
			local_USED = HevcDecoder_Algo_Parser_USED;
			used_v = pcRPS[sps_id][idx][local_USED + i];
			j = 0;
			while (j <= i - 1) {
				k = i - 1 - j;
				local_DELTAPOC = HevcDecoder_Algo_Parser_DELTAPOC;
				tmp = pcRPS[sps_id][idx][local_DELTAPOC + k];
				if (deltaPOC_v < tmp) {
					local_DELTAPOC = HevcDecoder_Algo_Parser_DELTAPOC;
					pcRPS[sps_id][idx][local_DELTAPOC + k + 1] = tmp;
					local_USED = HevcDecoder_Algo_Parser_USED;
					local_USED = HevcDecoder_Algo_Parser_USED;
					tmp_pcRPS1 = pcRPS[sps_id][idx][local_USED + k];
					pcRPS[sps_id][idx][local_USED + k + 1] = tmp_pcRPS1;
					local_DELTAPOC = HevcDecoder_Algo_Parser_DELTAPOC;
					pcRPS[sps_id][idx][local_DELTAPOC + k] = deltaPOC_v;
					local_USED = HevcDecoder_Algo_Parser_USED;
					pcRPS[sps_id][idx][local_USED + k] = used_v;
				}
				j = j + 1;
			}
			i = i + 1;
		}
	}
	local_NUM_NEGATIVE_PICS = HevcDecoder_Algo_Parser_NUM_NEGATIVE_PICS;
	tmp_pcRPS2 = pcRPS[sps_id][idx][local_NUM_NEGATIVE_PICS];
	if (tmp_pcRPS2 >> 1 != 0) {
		local_NUM_NEGATIVE_PICS = HevcDecoder_Algo_Parser_NUM_NEGATIVE_PICS;
		tmp_pcRPS3 = pcRPS[sps_id][idx][local_NUM_NEGATIVE_PICS];
		k = tmp_pcRPS3 - 1;
		i0 = 0;
		local_NUM_NEGATIVE_PICS = HevcDecoder_Algo_Parser_NUM_NEGATIVE_PICS;
		tmp_pcRPS4 = pcRPS[sps_id][idx][local_NUM_NEGATIVE_PICS];
		while (i0 <= (tmp_pcRPS4 >> 1) - 1) {
			local_DELTAPOC = HevcDecoder_Algo_Parser_DELTAPOC;
			deltaPOC_v = pcRPS[sps_id][idx][local_DELTAPOC + i0];
			local_USED = HevcDecoder_Algo_Parser_USED;
			used_v = pcRPS[sps_id][idx][local_USED + i0];
			local_DELTAPOC = HevcDecoder_Algo_Parser_DELTAPOC;
			local_DELTAPOC = HevcDecoder_Algo_Parser_DELTAPOC;
			tmp_pcRPS5 = pcRPS[sps_id][idx][local_DELTAPOC + k];
			pcRPS[sps_id][idx][local_DELTAPOC + i0] = tmp_pcRPS5;
			local_USED = HevcDecoder_Algo_Parser_USED;
			local_USED = HevcDecoder_Algo_Parser_USED;
			tmp_pcRPS6 = pcRPS[sps_id][idx][local_USED + k];
			pcRPS[sps_id][idx][local_USED + i0] = tmp_pcRPS6;
			local_DELTAPOC = HevcDecoder_Algo_Parser_DELTAPOC;
			pcRPS[sps_id][idx][local_DELTAPOC + k] = deltaPOC_v;
			local_USED = HevcDecoder_Algo_Parser_USED;
			pcRPS[sps_id][idx][local_USED + k] = used_v;
			k = k - 1;
			i0 = i0 + 1;
		}
	}
}
static void HevcDecoder_Algo_Parser_parseShortTermRefPicSet(u32 sps_id, u32 idx, u8 num_short_term_ref_pic_sets, u16 fifo[10], i8 pcRPS[15][65][131]) {
	u32 res[1];
	u8 inter_rps_flag;
	u16 delta_idx;
	u8 rIdx;
	i32 deltaRPS;
	i32 deltaPOC;
	i32 k;
	i32 k0;
	i32 k1;
	i32 prev;
	i32 delta_rps_sign;
	i32 abs_delta_rps;
	u32 tmp_res;
	u32 tmp_res0;
	u8 i;
	u8 local_NUM_PICS;
	i8 tmp_pcRPS;
	u32 tmp_res1;
	u32 tmp_res2;
	u32 tmp_res3;
	u32 tmp_res4;
	i8 tmp_pcRPS0;
	u8 local_DELTAPOC;
	i8 tmp_pcRPS1;
	u8 local_USED;
	u32 tmp_res5;
	u8 local_NUM_NEGATIVE_PICS;
	u8 local_NUM_POSITIVE_PICS;
	u32 tmp_res6;
	u32 tmp_res7;
	i8 tmp_pcRPS2;
	u32 tmp_res8;
	i8 tmp_pcRPS3;
	u8 i0;
	i8 tmp_pcRPS4;
	u32 tmp_res9;
	u32 tmp_res10;
	i8 tmp_pcRPS5;
	u8 i1;
	i8 tmp_pcRPS6;
	u32 tmp_res11;
	u32 tmp_res12;

	inter_rps_flag = 0;
	delta_idx = 1;
	k = 0;
	k0 = 0;
	k1 = 0;
	prev = 0;
	if (idx != 0) {
		HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "inter_ref_pic_set_prediction_flag       ");
		inter_rps_flag = res[0];
	}
	if (inter_rps_flag == 1) {
		if (idx == num_short_term_ref_pic_sets) {
			HevcDecoder_Algo_Parser_vld_ue_name(fifo, res, "delta_idx_minus1                        ");
			tmp_res = res[0];
			delta_idx = tmp_res + 1;
		}
		rIdx = idx - delta_idx;
		HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "delta_rps_sign                          ");
		delta_rps_sign = res[0];
		HevcDecoder_Algo_Parser_vld_ue_name(fifo, res, "abs_delta_rps_minus1                    ");
		tmp_res0 = res[0];
		abs_delta_rps = tmp_res0 + 1;
		deltaRPS = (1 - (delta_rps_sign << 1)) * abs_delta_rps;
		i = 0;
		local_NUM_PICS = HevcDecoder_Algo_Parser_NUM_PICS;
		tmp_pcRPS = pcRPS[sps_id][rIdx][local_NUM_PICS];
		while (i <= tmp_pcRPS) {
			HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "used_by_curr_pic_flag                   ");
			tmp_res1 = res[0];
			if (tmp_res1 == 0) {
				HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "use_delta_flag                          ");
				tmp_res2 = res[0];
				res[0] = tmp_res2 << 1;
			}
			tmp_res3 = res[0];
			tmp_res4 = res[0];
			if (tmp_res3 == 1 || tmp_res4 == 2) {
				local_NUM_PICS = HevcDecoder_Algo_Parser_NUM_PICS;
				tmp_pcRPS0 = pcRPS[sps_id][rIdx][local_NUM_PICS];
				if (i < tmp_pcRPS0) {
					local_DELTAPOC = HevcDecoder_Algo_Parser_DELTAPOC;
					tmp_pcRPS1 = pcRPS[sps_id][rIdx][local_DELTAPOC + i];
					deltaPOC = deltaRPS + tmp_pcRPS1;
				} else {
					deltaPOC = deltaRPS;
				}
				local_DELTAPOC = HevcDecoder_Algo_Parser_DELTAPOC;
				pcRPS[sps_id][idx][local_DELTAPOC + k] = deltaPOC;
				local_USED = HevcDecoder_Algo_Parser_USED;
				tmp_res5 = res[0];
				if (tmp_res5 == 1) {
					pcRPS[sps_id][idx][local_USED + k] = 1;
				} else {
					pcRPS[sps_id][idx][local_USED + k] = 0;
				}
				if (deltaPOC < 0) {
					k0 = k0 + 1;
				} else {
					k1 = k1 + 1;
				}
				k = k + 1;
			}
			i = i + 1;
		}
		local_NUM_PICS = HevcDecoder_Algo_Parser_NUM_PICS;
		pcRPS[sps_id][idx][local_NUM_PICS] = k;
		local_NUM_NEGATIVE_PICS = HevcDecoder_Algo_Parser_NUM_NEGATIVE_PICS;
		pcRPS[sps_id][idx][local_NUM_NEGATIVE_PICS] = k0;
		local_NUM_POSITIVE_PICS = HevcDecoder_Algo_Parser_NUM_POSITIVE_PICS;
		pcRPS[sps_id][idx][local_NUM_POSITIVE_PICS] = k1;
		HevcDecoder_Algo_Parser_sortDeltaPOC(sps_id, idx, pcRPS);
	} else {
		HevcDecoder_Algo_Parser_vld_ue_name(fifo, res, "num_negative_pics                       ");
		local_NUM_NEGATIVE_PICS = HevcDecoder_Algo_Parser_NUM_NEGATIVE_PICS;
		tmp_res6 = res[0];
		pcRPS[sps_id][idx][local_NUM_NEGATIVE_PICS] = tmp_res6;
		HevcDecoder_Algo_Parser_vld_ue_name(fifo, res, "num_positive_pics                       ");
		local_NUM_POSITIVE_PICS = HevcDecoder_Algo_Parser_NUM_POSITIVE_PICS;
		tmp_res7 = res[0];
		pcRPS[sps_id][idx][local_NUM_POSITIVE_PICS] = tmp_res7;
		local_NUM_PICS = HevcDecoder_Algo_Parser_NUM_PICS;
		local_NUM_NEGATIVE_PICS = HevcDecoder_Algo_Parser_NUM_NEGATIVE_PICS;
		tmp_pcRPS2 = pcRPS[sps_id][idx][local_NUM_NEGATIVE_PICS];
		tmp_res8 = res[0];
		pcRPS[sps_id][idx][local_NUM_PICS] = tmp_pcRPS2 + tmp_res8;
		local_NUM_NEGATIVE_PICS = HevcDecoder_Algo_Parser_NUM_NEGATIVE_PICS;
		tmp_pcRPS3 = pcRPS[sps_id][idx][local_NUM_NEGATIVE_PICS];
		if (tmp_pcRPS3 != 0) {
			i0 = 0;
			local_NUM_NEGATIVE_PICS = HevcDecoder_Algo_Parser_NUM_NEGATIVE_PICS;
			tmp_pcRPS4 = pcRPS[sps_id][idx][local_NUM_NEGATIVE_PICS];
			while (i0 <= tmp_pcRPS4 - 1) {
				HevcDecoder_Algo_Parser_vld_ue_name(fifo, res, "delta_poc_s0_minus1                     ");
				tmp_res9 = res[0];
				prev = prev - tmp_res9 - 1;
				local_DELTAPOC = HevcDecoder_Algo_Parser_DELTAPOC;
				pcRPS[sps_id][idx][local_DELTAPOC + i0] = prev;
				HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "used_by_curr_pic_s0_flag                ");
				local_USED = HevcDecoder_Algo_Parser_USED;
				tmp_res10 = res[0];
				pcRPS[sps_id][idx][local_USED + i0] = tmp_res10;
				i0 = i0 + 1;
			}
		}
		prev = 0;
		local_NUM_POSITIVE_PICS = HevcDecoder_Algo_Parser_NUM_POSITIVE_PICS;
		tmp_pcRPS5 = pcRPS[sps_id][idx][local_NUM_POSITIVE_PICS];
		if (tmp_pcRPS5 != 0) {
			local_NUM_NEGATIVE_PICS = HevcDecoder_Algo_Parser_NUM_NEGATIVE_PICS;
			i1 = pcRPS[sps_id][idx][local_NUM_NEGATIVE_PICS];
			local_NUM_PICS = HevcDecoder_Algo_Parser_NUM_PICS;
			tmp_pcRPS6 = pcRPS[sps_id][idx][local_NUM_PICS];
			while (i1 <= tmp_pcRPS6 - 1) {
				HevcDecoder_Algo_Parser_vld_ue_name(fifo, res, "delta_poc_s1_minus1                     ");
				tmp_res11 = res[0];
				prev = prev + tmp_res11 + 1;
				local_DELTAPOC = HevcDecoder_Algo_Parser_DELTAPOC;
				pcRPS[sps_id][idx][local_DELTAPOC + i1] = prev;
				HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "used_by_curr_pic_s1_flag                ");
				local_USED = HevcDecoder_Algo_Parser_USED;
				tmp_res12 = res[0];
				pcRPS[sps_id][idx][local_USED + i1] = tmp_res12;
				i1 = i1 + 1;
			}
		}
	}
}
static i32 HevcDecoder_Algo_Parser_log2(i32 v) {
	i32 v1;
	i32 n1;
	i32 v2;
	i32 n2;
	u8 tmp_log2_tab;

	if ((v & 4294901760L) != 0) {
		v1 = v >> 16;
	} else {
		v1 = v;
	}
	if ((v & 4294901760L) != 0) {
		n1 = 16;
	} else {
		n1 = 0;
	}
	if ((v1 & 65280) != 0) {
		v2 = v1 >> 8;
	} else {
		v2 = v1;
	}
	if ((v1 & 65280) != 0) {
		n2 = n1 + 8;
	} else {
		n2 = n1;
	}
	tmp_log2_tab = HevcDecoder_Algo_Parser_log2_tab[v2];
	return n2 + tmp_log2_tab;
}
static void HevcDecoder_Algo_Parser_InitScanningArray(u8 ScanOrder[4][3][256][2]) {
	u8 blkSize;
	u8 i;
	u8 x;
	i8 y;
	i32 stopLoop;
	i32 iTrafosize;
	i32 n;

	iTrafosize = 0;
	while (iTrafosize <= 3) {
		blkSize = 1 << iTrafosize;
		i = 0;
		x = 0;
		y = 0;
		stopLoop = 0;
		n = 0;
		while (n <= blkSize - 1) {
			ScanOrder[iTrafosize][0][n][0] = 0;
			ScanOrder[iTrafosize][0][n][1] = 0;
			ScanOrder[iTrafosize][1][n][0] = 0;
			ScanOrder[iTrafosize][1][n][1] = 0;
			ScanOrder[iTrafosize][2][n][0] = 0;
			ScanOrder[iTrafosize][2][n][1] = 0;
			n = n + 1;
		}
		while (!stopLoop) {
			while (y >= 0) {
				if (x < blkSize && y < blkSize) {
					ScanOrder[iTrafosize][0][i][0] = x;
					ScanOrder[iTrafosize][0][i][1] = y;
					i = i + 1;
				}
				y = y - 1;
				x = x + 1;
			}
			y = x;
			x = 0;
			if (i >= blkSize * blkSize) {
				stopLoop = 1;
			}
		}
		i = 0;
		y = 0;
		while (y < blkSize) {
			x = 0;
			while (x < blkSize) {
				ScanOrder[iTrafosize][1][i][0] = x;
				ScanOrder[iTrafosize][1][i][1] = y;
				x = x + 1;
				i = i + 1;
			}
			y = y + 1;
		}
		i = 0;
		x = 0;
		while (x < blkSize) {
			y = 0;
			while (y < blkSize) {
				ScanOrder[iTrafosize][2][i][0] = x;
				ScanOrder[iTrafosize][2][i][1] = y;
				y = y + 1;
				i = i + 1;
			}
			x = x + 1;
		}
		iTrafosize = iTrafosize + 1;
	}
}
static u32 HevcDecoder_Algo_Parser_InverseRasterScan(u32 a, u32 b, u32 c, u32 d, u32 e) {
	i64 tmp_if;

	if (e == 0) {
		tmp_if = a % ((d + b - 1) / b) * b;
	} else {
		tmp_if = a / ((d + b - 1) / b) * c;
	}
	return tmp_if;
}
static i32 HevcDecoder_Algo_Parser_log2_i16(i32 v) {
	i32 n;
	i32 v2;
	i32 n2;
	u8 tmp_log2_tab;

	n = 0;
	if ((v & 65280) != 0) {
		v2 = v >> 8;
	} else {
		v2 = v;
	}
	if ((v & 65280) != 0) {
		n2 = n + 8;
	} else {
		n2 = n;
	}
	tmp_log2_tab = HevcDecoder_Algo_Parser_log2_tab[v2];
	return n2 + tmp_log2_tab;
}
static void HevcDecoder_Algo_Parser_renormD(u16 codIRange[1], u16 codIOffset[1], u16 fifo[10]) {
	u32 res[1];
	u32 count;
	u16 tmp_codIRange;
	i32 tmp_log2_i16;
	u16 tmp_codIRange0;
	u16 tmp_codIOffset;
	u32 tmp_res;

	tmp_codIRange = codIRange[0];
	tmp_log2_i16 = HevcDecoder_Algo_Parser_log2_i16(tmp_codIRange);
	count = 8 - tmp_log2_i16;
	if (count > 0) {
		HevcDecoder_Algo_Parser_vld_u(count, fifo, res);
		tmp_codIRange0 = codIRange[0];
		codIRange[0] = tmp_codIRange0 << count;
		tmp_codIOffset = codIOffset[0];
		tmp_res = res[0];
		codIOffset[0] = (tmp_codIOffset << count) + tmp_res;
	}
}
static void HevcDecoder_Algo_Parser_decodeTerminate(u16 codIRange[1], u16 codIOffset[1], u32 binVal[1], u16 fifo[10]) {
	u16 tmp_codIRange;
	u16 tmp_codIOffset;
	u16 tmp_codIRange0;

	tmp_codIRange = codIRange[0];
	codIRange[0] = tmp_codIRange - 2;
	tmp_codIOffset = codIOffset[0];
	tmp_codIRange0 = codIRange[0];
	if (tmp_codIOffset >= tmp_codIRange0) {
		binVal[0] = 1;
	} else {
		binVal[0] = 0;
		HevcDecoder_Algo_Parser_renormD(codIRange, codIOffset, fifo);
	}
}
static void HevcDecoder_Algo_Parser_decodeTerminateTop(u32 binString[1], u16 codIRange[1], u16 codIOffset[1], u16 fifo[10]) {
	i32 local_DEBUG_CABAC;

	HevcDecoder_Algo_Parser_decodeTerminate(codIRange, codIOffset, binString, fifo);
	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
	}
}
static void HevcDecoder_Algo_Parser_get_END_OF_SLICE_FLAG(u16 codIRange[1], u16 codIOffset[1], u16 fifo[10], u32 debinValue[1]) {
	i32 local_DEBUG_CABAC;
	u16 tmp_codIRange;
	u16 tmp_codIOffset;
	i32 local_CHECK_CABAC;
	u32 tmp_debinValue;

	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
		printf(" END_OF_SLICE_FLAG ==>\n");
		tmp_codIRange = codIRange[0];
		tmp_codIOffset = codIOffset[0];
		printf("codIRange := %u codIOffset := %u\n", tmp_codIRange, tmp_codIOffset);
	}
	HevcDecoder_Algo_Parser_decodeTerminateTop(debinValue, codIRange, codIOffset, fifo);
	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
	}
	local_CHECK_CABAC = HevcDecoder_Algo_Parser_CHECK_CABAC;
	tmp_debinValue = debinValue[0];
	if (local_CHECK_CABAC && tmp_debinValue == 1) {
	}
}
static void HevcDecoder_Algo_Parser_byte_alignment(u16 fifo[10]) {

	HevcDecoder_Algo_Parser_flushBits(1, fifo);
	HevcDecoder_Algo_Parser_byte_align(fifo);
}
static void HevcDecoder_Algo_Parser_decodeStart(u16 codIRange[1], u16 codIOffset[1], u16 fifo[10]) {
	u32 res[1];
	u32 tmp_res;

	codIRange[0] = 510;
	HevcDecoder_Algo_Parser_byte_alignment(fifo);
	HevcDecoder_Algo_Parser_getBits(9, fifo, res);
	tmp_res = res[0];
	codIOffset[0] = tmp_res;
}
static i32 HevcDecoder_Algo_Parser_clip_i32(i32 Value, i32 minVal, i32 maxVal) {
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
static void HevcDecoder_Algo_Parser_contextInit(u8 qp, u8 sliceType, u16 ctxTable[30][48], u8 cabac_init_flag) {
	u8 qp_clip3;
	u8 initValue;
	i8 slope;
	i8 offset;
	u8 initState;
	u8 mpState;
	u8 pStateIdx;
	u8 sliceType_i;
	u8 local_P_SLICE;
	u8 local_B_SLICE;
	u8 i;
	u8 local_NB_MAX_SE;
	u8 j;
	u8 tmp_NUM_SE_CONTEXT_INDEX;
	u16 tmp_ctxTable;

	qp_clip3 = HevcDecoder_Algo_Parser_clip_i32(qp, 0, 51);
	sliceType_i = sliceType;
	if (cabac_init_flag == 1) {
		local_P_SLICE = HevcDecoder_Algo_Parser_P_SLICE;
		if (sliceType == local_P_SLICE) {
			local_B_SLICE = HevcDecoder_Algo_Parser_B_SLICE;
			sliceType_i = local_B_SLICE;
		} else {
			local_B_SLICE = HevcDecoder_Algo_Parser_B_SLICE;
			if (sliceType == local_B_SLICE) {
				local_P_SLICE = HevcDecoder_Algo_Parser_P_SLICE;
				sliceType_i = local_P_SLICE;
			}
		}
	}
	i = 0;
	local_NB_MAX_SE = HevcDecoder_Algo_Parser_NB_MAX_SE;
	while (i <= local_NB_MAX_SE - 1) {
		j = 0;
		tmp_NUM_SE_CONTEXT_INDEX = HevcDecoder_Algo_Parser_NUM_SE_CONTEXT_INDEX[i];
		while (j <= tmp_NUM_SE_CONTEXT_INDEX - 1) {
			initValue = HevcDecoder_Algo_Parser_InitContextIndex[i][sliceType_i][j];
			slope = (initValue >> 4) * 5 - 45;
			offset = ((initValue & 15) << 3) - 16;
			initState = HevcDecoder_Algo_Parser_clip_i32(((qp_clip3 * slope) >> 4) + offset, 1, 126);
			if (initState >= 64) {
				mpState = 1;
			} else {
				mpState = 0;
			}
			if (initState >= 64) {
				pStateIdx = initState - 64;
			} else {
				pStateIdx = 63 - initState;
			}
			ctxTable[i][j] = (pStateIdx << 1) + mpState;
			local_NB_MAX_SE = HevcDecoder_Algo_Parser_NB_MAX_SE;
			if (i == local_NB_MAX_SE) {
				tmp_ctxTable = ctxTable[i][j];
				printf(" initValue = %u slope = %i offset = %i state = %u mps = %u ucState = %u\n", initValue, slope, offset, initState, mpState, tmp_ctxTable);
			}
			j = j + 1;
		}
		i = i + 1;
	}
}
static void HevcDecoder_Algo_Parser_decodeReInit(u16 codIRange[1], u16 codIOffset[1], u16 fifo[10]) {
	u32 res[1];
	u32 tmp_res;

	codIRange[0] = 510;
	HevcDecoder_Algo_Parser_byte_align(fifo);
	HevcDecoder_Algo_Parser_getBits(9, fifo, res);
	tmp_res = res[0];
	codIOffset[0] = tmp_res;
}
static void HevcDecoder_Algo_Parser_get_END_OF_SUB_STREAM_ONE_BIT(u16 codIRange[1], u16 codIOffset[1], u16 fifo[10], u32 debinValue[1]) {
	i32 local_DEBUG_CABAC;
	u16 tmp_codIRange;
	u16 tmp_codIOffset;
	u16 tmp_codIRange0;
	u16 tmp_codIOffset0;

	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
		printf(" END_OF_SUB_STREAM_ONE_BIT ==>\n");
		tmp_codIRange = codIRange[0];
		tmp_codIOffset = codIOffset[0];
		printf("codIRange := %u codIOffset := %u\n", tmp_codIRange, tmp_codIOffset);
	}
	HevcDecoder_Algo_Parser_decodeTerminateTop(debinValue, codIRange, codIOffset, fifo);
	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
		tmp_codIRange0 = codIRange[0];
		tmp_codIOffset0 = codIOffset[0];
		printf("codIRange := %u codIOffset := %u\n", tmp_codIRange0, tmp_codIOffset0);
	}
}
static void HevcDecoder_Algo_Parser_decodeDecision(u16 codIRange[1], u16 codIOffset[1], u8 state[1], u8 mps[1], u8 binVal[1], u16 fifo[10]) {
	u16 tmp_codIRange;
	u8 qCodIRangeIdx;
	u8 tmp_state;
	u16 codIRangeLPS;
	u16 tmp_codIRange0;
	u16 tmp_codIOffset;
	u16 tmp_codIRange1;
	u8 tmp_mps;
	u16 tmp_codIOffset0;
	u16 tmp_codIRange2;
	u8 tmp_state0;
	u8 tmp_mps0;
	u8 tmp_state1;
	u8 tmp_transIdxLPS;
	u8 tmp_mps1;
	u8 tmp_state2;
	u8 tmp_transIdxMPS;

	tmp_codIRange = codIRange[0];
	qCodIRangeIdx = tmp_codIRange >> 6 & 3;
	tmp_state = state[0];
	codIRangeLPS = HevcDecoder_Algo_Parser_rangeTabLPS[tmp_state][qCodIRangeIdx];
	tmp_codIRange0 = codIRange[0];
	codIRange[0] = tmp_codIRange0 - codIRangeLPS;
	tmp_codIOffset = codIOffset[0];
	tmp_codIRange1 = codIRange[0];
	if (tmp_codIOffset >= tmp_codIRange1) {
		tmp_mps = mps[0];
		binVal[0] = 1 - tmp_mps;
		tmp_codIOffset0 = codIOffset[0];
		tmp_codIRange2 = codIRange[0];
		codIOffset[0] = tmp_codIOffset0 - tmp_codIRange2;
		codIRange[0] = codIRangeLPS;
		tmp_state0 = state[0];
		if (tmp_state0 == 0) {
			tmp_mps0 = mps[0];
			mps[0] = 1 - tmp_mps0;
		}
		tmp_state1 = state[0];
		tmp_transIdxLPS = HevcDecoder_Algo_Parser_transIdxLPS[tmp_state1];
		state[0] = tmp_transIdxLPS;
	} else {
		tmp_mps1 = mps[0];
		binVal[0] = tmp_mps1;
		tmp_state2 = state[0];
		tmp_transIdxMPS = HevcDecoder_Algo_Parser_transIdxMPS[tmp_state2];
		state[0] = tmp_transIdxMPS;
	}
	HevcDecoder_Algo_Parser_renormD(codIRange, codIOffset, fifo);
}
static void HevcDecoder_Algo_Parser_decodeDecisionTop(u16 ctxIdx, u32 binString[1], u16 codIRange[1], u16 codIOffset[1], u16 ctxTable[30][48], u8 se, u16 fifo[10]) {
	u8 state[1];
	u8 mps[1];
	u8 binVal[1];
	u16 tmp_ctxTable;
	u16 tmp_ctxTable0;
	i32 local_DEBUG_CABAC;
	u8 tmp_state;
	u8 tmp_mps;
	u32 tmp_binString;
	u8 tmp_binVal;

	state[0] = 0;
	mps[0] = 0;
	binVal[0] = 0;
	tmp_ctxTable = ctxTable[se][ctxIdx];
	state[0] = tmp_ctxTable >> 1;
	tmp_ctxTable0 = ctxTable[se][ctxIdx];
	mps[0] = tmp_ctxTable0 & 1;
	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
	}
	HevcDecoder_Algo_Parser_decodeDecision(codIRange, codIOffset, state, mps, binVal, fifo);
	tmp_state = state[0];
	tmp_mps = mps[0];
	ctxTable[se][ctxIdx] = (tmp_state << 1) + tmp_mps;
	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
	}
	tmp_binString = binString[0];
	tmp_binVal = binVal[0];
	binString[0] = (tmp_binString << 1) + tmp_binVal;
}
static void HevcDecoder_Algo_Parser_get_SAO_MERGE_FLAG(u16 codIRange[1], u16 codIOffset[1], u16 ctxTable[30][48], u16 fifo[10], u32 debinValue[1]) {
	i32 local_DEBUG_CABAC;
	u16 tmp_codIRange;
	u16 tmp_codIOffset;
	u8 local_SE_SAO_MERGE_FLAG;
	u16 tmp_codIRange0;
	u16 tmp_codIOffset0;

	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
		printf(" SAO_MERGE_FLAG ==>\n");
		tmp_codIRange = codIRange[0];
		tmp_codIOffset = codIOffset[0];
		printf("codIRange := %u codIOffset := %u\n", tmp_codIRange, tmp_codIOffset);
	}
	debinValue[0] = 0;
	local_SE_SAO_MERGE_FLAG = HevcDecoder_Algo_Parser_SE_SAO_MERGE_FLAG;
	HevcDecoder_Algo_Parser_decodeDecisionTop(0, debinValue, codIRange, codIOffset, ctxTable, local_SE_SAO_MERGE_FLAG, fifo);
	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
		tmp_codIRange0 = codIRange[0];
		tmp_codIOffset0 = codIOffset[0];
		printf("codIRange := %u codIOffset := %u\n", tmp_codIRange0, tmp_codIOffset0);
	}
}
static void HevcDecoder_Algo_Parser_decodeBypass(u16 codIRange[1], u16 codIOffset[1], u8 binVal[1], u16 fifo[10]) {
	u32 res[1];
	u16 tmp_codIOffset;
	u32 tmp_res;
	u16 tmp_codIOffset0;
	u16 tmp_codIRange;
	u16 tmp_codIOffset1;
	u16 tmp_codIRange0;

	HevcDecoder_Algo_Parser_vld_u(1, fifo, res);
	tmp_codIOffset = codIOffset[0];
	tmp_res = res[0];
	codIOffset[0] = (tmp_codIOffset << 1) + tmp_res;
	tmp_codIOffset0 = codIOffset[0];
	tmp_codIRange = codIRange[0];
	if (tmp_codIOffset0 >= tmp_codIRange) {
		binVal[0] = 1;
		tmp_codIOffset1 = codIOffset[0];
		tmp_codIRange0 = codIRange[0];
		codIOffset[0] = tmp_codIOffset1 - tmp_codIRange0;
	} else {
		binVal[0] = 0;
	}
}
static void HevcDecoder_Algo_Parser_decodeBypassTop(u32 binString[1], u16 codIRange[1], u16 codIOffset[1], u16 fifo[10]) {
	u8 binVal[1];
	u8 tmp_binVal;
	i32 local_DEBUG_CABAC;

	HevcDecoder_Algo_Parser_decodeBypass(codIRange, codIOffset, binVal, fifo);
	tmp_binVal = binVal[0];
	binString[0] = tmp_binVal;
	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
	}
}
static void HevcDecoder_Algo_Parser_get_SAO_TYPE_IDX(u16 codIRange[1], u16 codIOffset[1], u16 ctxTable[30][48], u16 fifo[10], u32 debinValue[1]) {
	u32 binString[1];
	i32 local_DEBUG_CABAC;
	u16 tmp_codIRange;
	u16 tmp_codIOffset;
	u8 local_SE_SAO_TYPE_IDX;
	u32 tmp_binString;
	u8 local_SAO_NOT_APPLIED;
	u32 tmp_binString0;
	u8 local_SAO_BAND;
	u8 local_SAO_EDGE;
	u16 tmp_codIRange0;
	u16 tmp_codIOffset0;

	binString[0] = 0;
	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
		printf(" SAO_TYPE_IDX ==>\n");
		tmp_codIRange = codIRange[0];
		tmp_codIOffset = codIOffset[0];
		printf("codIRange := %u codIOffset := %u\n", tmp_codIRange, tmp_codIOffset);
	}
	local_SE_SAO_TYPE_IDX = HevcDecoder_Algo_Parser_SE_SAO_TYPE_IDX;
	HevcDecoder_Algo_Parser_decodeDecisionTop(0, binString, codIRange, codIOffset, ctxTable, local_SE_SAO_TYPE_IDX, fifo);
	tmp_binString = binString[0];
	if (tmp_binString == 0) {
		local_SAO_NOT_APPLIED = HevcDecoder_Algo_Parser_SAO_NOT_APPLIED;
		debinValue[0] = local_SAO_NOT_APPLIED;
	} else {
		HevcDecoder_Algo_Parser_decodeBypassTop(binString, codIRange, codIOffset, fifo);
		tmp_binString0 = binString[0];
		if (tmp_binString0 == 0) {
			local_SAO_BAND = HevcDecoder_Algo_Parser_SAO_BAND;
			debinValue[0] = local_SAO_BAND;
		} else {
			local_SAO_EDGE = HevcDecoder_Algo_Parser_SAO_EDGE;
			debinValue[0] = local_SAO_EDGE;
		}
	}
	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
		tmp_codIRange0 = codIRange[0];
		tmp_codIOffset0 = codIOffset[0];
		printf("codIRange := %u codIOffset := %u\n", tmp_codIRange0, tmp_codIOffset0);
	}
}
static void HevcDecoder_Algo_Parser_debinTU(u32 binString, u8 binIdx, u8 binarization, u8 debinCompleted[1], u32 debinValue[1], u8 discard_suffix[1]) {
	u8 local_DEBIN_TU9;

	if (binIdx == binarization) {
		debinCompleted[0] = 1;
	} else {
		debinCompleted[0] = 1 - (binString & 1);
	}
	local_DEBIN_TU9 = HevcDecoder_Algo_Parser_DEBIN_TU9;
	if (binarization != local_DEBIN_TU9) {
		discard_suffix[0] = binString & 1;
	} else {
		discard_suffix[0] = 0;
	}
	debinValue[0] = binIdx + (binString & 1);
}
static void HevcDecoder_Algo_Parser_get_SAO_OFFSET_ABS(u8 offsetTh, u16 codIRange[1], u16 codIOffset[1], u16 fifo[10], u32 debinValue[1]) {
	u8 binIdx;
	u8 debinCompleted[1];
	u8 discard_suffix[1];
	u32 binString[1];
	i32 local_DEBUG_CABAC;
	u16 tmp_codIRange;
	u16 tmp_codIOffset;
	u8 tmp_debinCompleted;
	u32 tmp_binString;

	binIdx = 0;
	debinCompleted[0] = 0;
	discard_suffix[0] = 0;
	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
		printf(" SAO_OFFSET_ABS ==> %u\n", offsetTh);
		tmp_codIRange = codIRange[0];
		tmp_codIOffset = codIOffset[0];
		printf("codIRange := %u codIOffset := %u\n", tmp_codIRange, tmp_codIOffset);
	}
	tmp_debinCompleted = debinCompleted[0];
	while (tmp_debinCompleted == 0) {
		HevcDecoder_Algo_Parser_decodeBypassTop(binString, codIRange, codIOffset, fifo);
		tmp_binString = binString[0];
		HevcDecoder_Algo_Parser_debinTU(tmp_binString, binIdx, offsetTh - 1, debinCompleted, debinValue, discard_suffix);
		binIdx = binIdx + 1;
		tmp_debinCompleted = debinCompleted[0];
	}
	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
	}
}
static void HevcDecoder_Algo_Parser_get_SAO_OFFSET_SIGN(u16 codIRange[1], u16 codIOffset[1], u16 fifo[10], u32 debinValue[1]) {
	i32 local_DEBUG_CABAC;
	u16 tmp_codIRange;
	u16 tmp_codIOffset;

	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
		printf(" SAO_OFFSET_SIGN ==>\n");
		tmp_codIRange = codIRange[0];
		tmp_codIOffset = codIOffset[0];
		printf("codIRange := %u codIOffset := %u\n", tmp_codIRange, tmp_codIOffset);
	}
	HevcDecoder_Algo_Parser_decodeBypassTop(debinValue, codIRange, codIOffset, fifo);
	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
	}
}
static void HevcDecoder_Algo_Parser_decodeBinsEP(u8 numBins, u32 binString[1], u16 codIRange[1], u16 codIOffset[1], u16 fifo[10]) {
	u32 binVal[1];
	i32 i;
	u32 tmp_binString;
	u32 tmp_binVal;

	if (numBins != 1) {
		binString[0] = 0;
		i = 0;
		while (i <= numBins - 1) {
			HevcDecoder_Algo_Parser_decodeBypassTop(binVal, codIRange, codIOffset, fifo);
			tmp_binString = binString[0];
			tmp_binVal = binVal[0];
			binString[0] = (tmp_binString << 1) + tmp_binVal;
			i = i + 1;
		}
	} else {
		HevcDecoder_Algo_Parser_decodeBypassTop(binString, codIRange, codIOffset, fifo);
	}
}
static void HevcDecoder_Algo_Parser_get_SAO_BAND_POSITION(u16 codIRange[1], u16 codIOffset[1], u16 fifo[10], u32 debinValue[1]) {
	i32 local_DEBUG_CABAC;
	u16 tmp_codIRange;
	u16 tmp_codIOffset;

	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
		printf(" SAO_BAND_POSITION ==>\n");
		tmp_codIRange = codIRange[0];
		tmp_codIOffset = codIOffset[0];
		printf("codIRange := %u codIOffset := %u\n", tmp_codIRange, tmp_codIOffset);
	}
	HevcDecoder_Algo_Parser_decodeBinsEP(5, debinValue, codIRange, codIOffset, fifo);
	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
	}
}
static void HevcDecoder_Algo_Parser_get_SAO_EO(u16 codIRange[1], u16 codIOffset[1], u16 fifo[10], u32 debinValue[1]) {
	i32 local_DEBUG_CABAC;
	u16 tmp_codIRange;
	u16 tmp_codIOffset;

	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
		printf(" SAO_EO ==>\n");
		tmp_codIRange = codIRange[0];
		tmp_codIOffset = codIOffset[0];
		printf("codIRange := %u codIOffset := %u\n", tmp_codIRange, tmp_codIOffset);
	}
	HevcDecoder_Algo_Parser_decodeBinsEP(2, debinValue, codIRange, codIOffset, fifo);
	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
	}
}
static u8 HevcDecoder_Algo_Parser_context_93311_SKIP_CU_FLAG(u8 depthSubPart, i32 availableA, u8 depthSubPartA, i32 availableB, u8 depthSubPartB) {
	u8 condTermA;
	u8 condTermB;

	if (depthSubPartA > depthSubPart && availableA == 1) {
		condTermA = 1;
	} else {
		condTermA = 0;
	}
	if (depthSubPartB > depthSubPart && availableB == 1) {
		condTermB = 1;
	} else {
		condTermB = 0;
	}
	return condTermA + condTermB;
}
static void HevcDecoder_Algo_Parser_get_SPLIT_CODING_UNIT_FLAG(u16 codIRange[1], u16 codIOffset[1], u16 ctxTable[30][48], u16 fifo[10], u32 debinValue[1], u8 depthSubPart, i32 availableA, u8 depthSubPartA, i32 availableB, u8 depthSubPartB) {
	u16 ctxIdx;
	i32 local_DEBUG_CABAC;
	u16 tmp_codIRange;
	u16 tmp_codIOffset;
	u8 local_SE_SPLIT_CODING_UNIT_FLAG;

	ctxIdx = HevcDecoder_Algo_Parser_context_93311_SKIP_CU_FLAG(depthSubPart, availableA, depthSubPartA, availableB, depthSubPartB);
	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
		printf(" SPLIT_CODING_UNIT_FLAG ==> ctxIdx := %u\n", ctxIdx);
		tmp_codIRange = codIRange[0];
		tmp_codIOffset = codIOffset[0];
		printf("codIRange := %u codIOffset := %u\n", tmp_codIRange, tmp_codIOffset);
	}
	debinValue[0] = 0;
	local_SE_SPLIT_CODING_UNIT_FLAG = HevcDecoder_Algo_Parser_SE_SPLIT_CODING_UNIT_FLAG;
	HevcDecoder_Algo_Parser_decodeDecisionTop(ctxIdx, debinValue, codIRange, codIOffset, ctxTable, local_SE_SPLIT_CODING_UNIT_FLAG, fifo);
	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
	}
}
static void HevcDecoder_Algo_Parser_get_CU_TRANSQUANT_BYPASS_FLAG(u16 codIRange[1], u16 codIOffset[1], u16 ctxTable[30][48], u16 fifo[10], u32 debinValue[1]) {
	i32 local_DEBUG_CABAC;
	u16 tmp_codIRange;
	u16 tmp_codIOffset;
	u8 local_SE_CU_TRANSQUANT_BYPASS_FLAG;

	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
		printf(" CU_TRANSQUANT_BYPASS_FLAG ==>\n");
		tmp_codIRange = codIRange[0];
		tmp_codIOffset = codIOffset[0];
		printf("codIRange := %u codIOffset := %u\n", tmp_codIRange, tmp_codIOffset);
	}
	debinValue[0] = 0;
	local_SE_CU_TRANSQUANT_BYPASS_FLAG = HevcDecoder_Algo_Parser_SE_CU_TRANSQUANT_BYPASS_FLAG;
	HevcDecoder_Algo_Parser_decodeDecisionTop(0, debinValue, codIRange, codIOffset, ctxTable, local_SE_CU_TRANSQUANT_BYPASS_FLAG, fifo);
	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
	}
}
static void HevcDecoder_Algo_Parser_get_SKIP_FLAG(u16 codIRange[1], u16 codIOffset[1], u16 ctxTable[30][48], u16 fifo[10], u32 debinValue[1], u8 skip_flag[4096][2], u16 cu_x0, u16 cu_y0, i32 leftFlag, i32 upFlag) {
	u16 ctxIdx;
	u8 availableA;
	u8 availableB;
	i32 local_DEBUG_CABAC;
	u16 tmp_codIRange;
	u16 tmp_codIOffset;
	u8 local_SE_SKIP_FLAG;

	if (leftFlag) {
		availableA = skip_flag[cu_y0][1];
	} else {
		availableA = 0;
	}
	if (upFlag) {
		availableB = skip_flag[cu_x0][0];
	} else {
		availableB = 0;
	}
	ctxIdx = availableA + availableB;
	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
		printf(" SKIP_FLAG ==> %u\n", ctxIdx);
		tmp_codIRange = codIRange[0];
		tmp_codIOffset = codIOffset[0];
		printf("codIRange := %u codIOffset := %u\n", tmp_codIRange, tmp_codIOffset);
	}
	debinValue[0] = 0;
	local_SE_SKIP_FLAG = HevcDecoder_Algo_Parser_SE_SKIP_FLAG;
	HevcDecoder_Algo_Parser_decodeDecisionTop(ctxIdx, debinValue, codIRange, codIOffset, ctxTable, local_SE_SKIP_FLAG, fifo);
	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
	}
}
static void HevcDecoder_Algo_Parser_intra_prediction_unit_default_value(u16 x0, u16 y0, u8 log2_cb_size, u8 part_mode, u8 log2_min_pu_size, u8 intraPredMode[4096][2]) {
	u8 local_PART_NxN;
	u16 split;
	u16 pb_size;
	u16 side;
	u8 size_in_pus;
	u16 x_pu;
	u16 y_pu;
	i32 i;
	i32 j;
	u8 local_INTRA_DC;

	local_PART_NxN = HevcDecoder_Algo_Parser_PART_NxN;
	if (part_mode == local_PART_NxN) {
		split = 1;
	} else {
		split = 0;
	}
	pb_size = (1 << log2_cb_size) >> split;
	side = split + 1;
	size_in_pus = pb_size >> log2_min_pu_size;
	i = 0;
	while (i <= side - 1) {
		x_pu = (x0 + pb_size * i) >> log2_min_pu_size;
		y_pu = (y0 + pb_size * i) >> log2_min_pu_size;
		j = 0;
		while (j <= size_in_pus - 1) {
			local_INTRA_DC = HevcDecoder_Algo_Parser_INTRA_DC;
			intraPredMode[x_pu + j][0] = local_INTRA_DC;
			local_INTRA_DC = HevcDecoder_Algo_Parser_INTRA_DC;
			intraPredMode[y_pu + j][1] = local_INTRA_DC;
			j = j + 1;
		}
		i = i + 1;
	}
}
static void HevcDecoder_Algo_Parser_get_PRED_MODE_FLAG(u16 codIRange[1], u16 codIOffset[1], u16 ctxTable[30][48], u16 fifo[10], u32 debinValue[1]) {
	u32 binString[1];
	i32 local_DEBUG_CABAC;
	u16 tmp_codIRange;
	u16 tmp_codIOffset;
	u8 local_SE_PRED_MODE_FLAG;
	u8 local_INTER;
	u32 tmp_binString;

	binString[0] = 0;
	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
		printf(" PRED_MODE_FLAG ==>\n");
		tmp_codIRange = codIRange[0];
		tmp_codIOffset = codIOffset[0];
		printf("codIRange := %u codIOffset := %u\n", tmp_codIRange, tmp_codIOffset);
	}
	local_SE_PRED_MODE_FLAG = HevcDecoder_Algo_Parser_SE_PRED_MODE_FLAG;
	HevcDecoder_Algo_Parser_decodeDecisionTop(0, binString, codIRange, codIOffset, ctxTable, local_SE_PRED_MODE_FLAG, fifo);
	local_INTER = HevcDecoder_Algo_Parser_INTER;
	tmp_binString = binString[0];
	debinValue[0] = local_INTER + tmp_binString;
	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
	}
}
static void HevcDecoder_Algo_Parser_get_PART_SIZE(u16 codIRange[1], u16 codIOffset[1], u16 ctxTable[30][48], u16 fifo[10], u32 debinValue[1], i32 isIntra, u8 cu_log2CbSize, u8 Log2MinCbSize, u8 amp_enabled_flag) {
	u32 binString[1];
	i32 local_DEBUG_CABAC;
	u16 tmp_codIRange;
	u16 tmp_codIOffset;
	u8 local_SE_PART_MODE;
	u32 tmp_binString;
	u8 local_PART_2Nx2N;
	u8 local_PART_NxN;
	u32 tmp_binString0;
	u8 local_PART_2NxN;
	u8 local_PART_Nx2N;
	u32 tmp_binString1;
	u32 tmp_binString2;
	u32 tmp_binString3;
	u32 tmp_binString4;
	u32 tmp_binString5;
	u8 local_PART_2NxnD;
	u8 local_PART_2NxnU;
	u32 tmp_binString6;
	u32 tmp_binString7;
	u8 local_PART_nRx2N;
	u8 local_PART_nLx2N;

	binString[0] = 0;
	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
		printf(" PART_MODE ==>\n");
		tmp_codIRange = codIRange[0];
		tmp_codIOffset = codIOffset[0];
		printf("codIRange := %u codIOffset := %u\n", tmp_codIRange, tmp_codIOffset);
	}
	local_SE_PART_MODE = HevcDecoder_Algo_Parser_SE_PART_MODE;
	HevcDecoder_Algo_Parser_decodeDecisionTop(0, binString, codIRange, codIOffset, ctxTable, local_SE_PART_MODE, fifo);
	tmp_binString = binString[0];
	if (tmp_binString != 0) {
		local_PART_2Nx2N = HevcDecoder_Algo_Parser_PART_2Nx2N;
		debinValue[0] = local_PART_2Nx2N;
	} else {
		if (cu_log2CbSize == Log2MinCbSize) {
			if (isIntra) {
				local_PART_NxN = HevcDecoder_Algo_Parser_PART_NxN;
				debinValue[0] = local_PART_NxN;
			} else {
				local_SE_PART_MODE = HevcDecoder_Algo_Parser_SE_PART_MODE;
				HevcDecoder_Algo_Parser_decodeDecisionTop(1, binString, codIRange, codIOffset, ctxTable, local_SE_PART_MODE, fifo);
				tmp_binString0 = binString[0];
				if (tmp_binString0 != 0) {
					local_PART_2NxN = HevcDecoder_Algo_Parser_PART_2NxN;
					debinValue[0] = local_PART_2NxN;
				} else {
					if (cu_log2CbSize == 3) {
						local_PART_Nx2N = HevcDecoder_Algo_Parser_PART_Nx2N;
						debinValue[0] = local_PART_Nx2N;
					} else {
						local_SE_PART_MODE = HevcDecoder_Algo_Parser_SE_PART_MODE;
						HevcDecoder_Algo_Parser_decodeDecisionTop(2, binString, codIRange, codIOffset, ctxTable, local_SE_PART_MODE, fifo);
						tmp_binString1 = binString[0];
						if (tmp_binString1 != 0) {
							local_PART_Nx2N = HevcDecoder_Algo_Parser_PART_Nx2N;
							debinValue[0] = local_PART_Nx2N;
						} else {
							local_PART_NxN = HevcDecoder_Algo_Parser_PART_NxN;
							debinValue[0] = local_PART_NxN;
						}
					}
				}
			}
		} else {
			if (amp_enabled_flag == 0) {
				local_SE_PART_MODE = HevcDecoder_Algo_Parser_SE_PART_MODE;
				HevcDecoder_Algo_Parser_decodeDecisionTop(1, binString, codIRange, codIOffset, ctxTable, local_SE_PART_MODE, fifo);
				tmp_binString2 = binString[0];
				if (tmp_binString2 != 0) {
					local_PART_2NxN = HevcDecoder_Algo_Parser_PART_2NxN;
					debinValue[0] = local_PART_2NxN;
				} else {
					local_PART_Nx2N = HevcDecoder_Algo_Parser_PART_Nx2N;
					debinValue[0] = local_PART_Nx2N;
				}
			} else {
				local_SE_PART_MODE = HevcDecoder_Algo_Parser_SE_PART_MODE;
				HevcDecoder_Algo_Parser_decodeDecisionTop(1, binString, codIRange, codIOffset, ctxTable, local_SE_PART_MODE, fifo);
				tmp_binString3 = binString[0];
				if (tmp_binString3 != 0) {
					binString[0] = 0;
					local_SE_PART_MODE = HevcDecoder_Algo_Parser_SE_PART_MODE;
					HevcDecoder_Algo_Parser_decodeDecisionTop(3, binString, codIRange, codIOffset, ctxTable, local_SE_PART_MODE, fifo);
					tmp_binString4 = binString[0];
					if (tmp_binString4 == 1) {
						local_PART_2NxN = HevcDecoder_Algo_Parser_PART_2NxN;
						debinValue[0] = local_PART_2NxN;
					} else {
						HevcDecoder_Algo_Parser_decodeBypassTop(binString, codIRange, codIOffset, fifo);
						tmp_binString5 = binString[0];
						if (tmp_binString5 != 0) {
							local_PART_2NxnD = HevcDecoder_Algo_Parser_PART_2NxnD;
							debinValue[0] = local_PART_2NxnD;
						} else {
							local_PART_2NxnU = HevcDecoder_Algo_Parser_PART_2NxnU;
							debinValue[0] = local_PART_2NxnU;
						}
					}
				} else {
					local_SE_PART_MODE = HevcDecoder_Algo_Parser_SE_PART_MODE;
					HevcDecoder_Algo_Parser_decodeDecisionTop(3, binString, codIRange, codIOffset, ctxTable, local_SE_PART_MODE, fifo);
					tmp_binString6 = binString[0];
					if (tmp_binString6 != 0) {
						local_PART_Nx2N = HevcDecoder_Algo_Parser_PART_Nx2N;
						debinValue[0] = local_PART_Nx2N;
					} else {
						HevcDecoder_Algo_Parser_decodeBypassTop(binString, codIRange, codIOffset, fifo);
						tmp_binString7 = binString[0];
						if (tmp_binString7 != 0) {
							local_PART_nRx2N = HevcDecoder_Algo_Parser_PART_nRx2N;
							debinValue[0] = local_PART_nRx2N;
						} else {
							local_PART_nLx2N = HevcDecoder_Algo_Parser_PART_nLx2N;
							debinValue[0] = local_PART_nLx2N;
						}
					}
				}
			}
		}
	}
	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
	}
}
static void HevcDecoder_Algo_Parser_get_PCM_FLAG(u16 codIRange[1], u16 codIOffset[1], u16 fifo[10], u32 debinValue[1]) {
	i32 local_DEBUG_CABAC;
	u16 tmp_codIRange;
	u16 tmp_codIOffset;

	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
		printf(" PCM_FLAG ==>\n");
		tmp_codIRange = codIRange[0];
		tmp_codIOffset = codIOffset[0];
		printf("codIRange := %u codIOffset := %u\n", tmp_codIRange, tmp_codIOffset);
	}
	HevcDecoder_Algo_Parser_decodeTerminateTop(debinValue, codIRange, codIOffset, fifo);
	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
	}
}
static void HevcDecoder_Algo_Parser_get_PREV_INTRA_LUMA_PRED_FLAG(u16 codIRange[1], u16 codIOffset[1], u16 ctxTable[30][48], u16 fifo[10], u32 debinValue[1]) {
	i32 local_DEBUG_CABAC;
	u16 tmp_codIRange;
	u16 tmp_codIOffset;
	u8 local_SE_PREV_INTRA_LUMA_PRED_FLAG;

	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
		printf(" PREV_INTRA_LUMA_PRED_FLAG ==>\n");
		tmp_codIRange = codIRange[0];
		tmp_codIOffset = codIOffset[0];
		printf("codIRange := %u codIOffset := %u\n", tmp_codIRange, tmp_codIOffset);
	}
	debinValue[0] = 0;
	local_SE_PREV_INTRA_LUMA_PRED_FLAG = HevcDecoder_Algo_Parser_SE_PREV_INTRA_LUMA_PRED_FLAG;
	HevcDecoder_Algo_Parser_decodeDecisionTop(0, debinValue, codIRange, codIOffset, ctxTable, local_SE_PREV_INTRA_LUMA_PRED_FLAG, fifo);
	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
	}
}
static void HevcDecoder_Algo_Parser_get_MPM_IDX(u16 codIRange[1], u16 codIOffset[1], u16 fifo[10], u32 debinValue[1]) {
	u8 binIdx;
	u8 debinCompleted[1];
	u8 discard_suffix[1];
	u32 binString[1];
	i32 local_DEBUG_CABAC;
	u16 tmp_codIRange;
	u16 tmp_codIOffset;
	u8 tmp_debinCompleted;
	u32 tmp_binString;
	u8 local_DEBIN_TU2;

	binIdx = 0;
	debinCompleted[0] = 0;
	discard_suffix[0] = 0;
	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
		printf(" MPM_IDX ==>\n");
		tmp_codIRange = codIRange[0];
		tmp_codIOffset = codIOffset[0];
		printf("codIRange := %u codIOffset := %u\n", tmp_codIRange, tmp_codIOffset);
	}
	tmp_debinCompleted = debinCompleted[0];
	while (tmp_debinCompleted == 0) {
		HevcDecoder_Algo_Parser_decodeBypassTop(binString, codIRange, codIOffset, fifo);
		tmp_binString = binString[0];
		local_DEBIN_TU2 = HevcDecoder_Algo_Parser_DEBIN_TU2;
		HevcDecoder_Algo_Parser_debinTU(tmp_binString, binIdx, local_DEBIN_TU2, debinCompleted, debinValue, discard_suffix);
		binIdx = binIdx + 1;
		tmp_debinCompleted = debinCompleted[0];
	}
	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
	}
}
static void HevcDecoder_Algo_Parser_get_REM_INTRA_LUMA_PRED_MODE(u16 codIRange[1], u16 codIOffset[1], u16 fifo[10], i32 debinValue[1]) {
	i32 local_DEBUG_CABAC;
	u16 tmp_codIRange;
	u16 tmp_codIOffset;

	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
		printf(" REM_INTRA_LUMA_PRED_MODE ==>\n");
		tmp_codIRange = codIRange[0];
		tmp_codIOffset = codIOffset[0];
		printf("codIRange := %u codIOffset := %u\n", tmp_codIRange, tmp_codIOffset);
	}
	HevcDecoder_Algo_Parser_decodeBinsEP(5, debinValue, codIRange, codIOffset, fifo);
	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
	}
}
static void HevcDecoder_Algo_Parser_luma_intra_pred_mode(u16 x0, u16 y0, u8 pu_size, u8 prev_intra_luma_pred_flag, u32 mpm_idx_or_rem_intra_luma_pred_mode, u32 ret[1], u8 log2_min_pu_size, u8 log2_ctb_size, u8 intraPredMode[4096][2], i32 upFlag, i32 leftFlag) {
	i16 x0b;
	i16 y0b;
	u8 candidate[4];
	u16 x_pu;
	u16 y_pu;
	u8 size_in_pus;
	u8 local_INTRA_DC;
	u8 cand_up;
	u8 cand_left;
	u16 y_ctb;
	u8 local_INTRA_PLANAR;
	u8 local_INTRA_ANGULAR_26;
	u8 tmp_candidate;
	u8 tmp_candidate0;
	u8 tmp_candidate1;
	u8 tmp_candidate2;
	u8 tmp_candidate3;
	u8 tmp_candidate4;
	u8 tmp_candidate5;
	u8 tmp_candidate6;
	u8 tmp_candidate7;
	u8 tmp_candidate8;
	u8 tmp_candidate9;
	u8 tmp_candidate10;
	u8 tmp_candidate11;
	u8 tmp_candidate12;
	u8 tmp_candidate13;
	u8 tmp_candidate14;
	u8 tmp_candidate15;
	u8 tmp_candidate16;
	u8 tmp_candidate17;
	u8 tmp_candidate18;
	i32 i;
	u32 tmp_ret;
	u8 tmp_candidate19;
	u32 tmp_ret0;
	i32 i0;
	u32 tmp_ret1;
	u32 tmp_ret2;

	x0b = x0 & (1 << log2_ctb_size) - 1;
	y0b = y0 & (1 << log2_ctb_size) - 1;
	candidate[0] = 0;
	candidate[1] = 0;
	candidate[2] = 0;
	candidate[3] = 0;
	x_pu = x0 >> log2_min_pu_size;
	y_pu = y0 >> log2_min_pu_size;
	size_in_pus = pu_size >> log2_min_pu_size;
	if (upFlag || y0b > 0) {
		cand_up = intraPredMode[x_pu][0];
	} else {
		local_INTRA_DC = HevcDecoder_Algo_Parser_INTRA_DC;
		cand_up = local_INTRA_DC;
	}
	if (leftFlag || x0b > 0) {
		cand_left = intraPredMode[y_pu][1];
	} else {
		local_INTRA_DC = HevcDecoder_Algo_Parser_INTRA_DC;
		cand_left = local_INTRA_DC;
	}
	y_ctb = (y0 >> log2_ctb_size) << log2_ctb_size;
	if (y0 - 1 < y_ctb) {
		local_INTRA_DC = HevcDecoder_Algo_Parser_INTRA_DC;
		cand_up = local_INTRA_DC;
	}
	if (cand_left == cand_up) {
		if (cand_left < 2) {
			local_INTRA_PLANAR = HevcDecoder_Algo_Parser_INTRA_PLANAR;
			candidate[0] = local_INTRA_PLANAR;
			local_INTRA_DC = HevcDecoder_Algo_Parser_INTRA_DC;
			candidate[1] = local_INTRA_DC;
			local_INTRA_ANGULAR_26 = HevcDecoder_Algo_Parser_INTRA_ANGULAR_26;
			candidate[2] = local_INTRA_ANGULAR_26;
		} else {
			candidate[0] = cand_left;
			candidate[1] = 2 + (cand_left - 2 - 1 + 32 & 31);
			candidate[2] = 2 + (cand_left - 2 + 1 & 31);
		}
	} else {
		candidate[0] = cand_left;
		candidate[1] = cand_up;
		tmp_candidate = candidate[0];
		local_INTRA_PLANAR = HevcDecoder_Algo_Parser_INTRA_PLANAR;
		tmp_candidate0 = candidate[1];
		local_INTRA_PLANAR = HevcDecoder_Algo_Parser_INTRA_PLANAR;
		if (tmp_candidate != local_INTRA_PLANAR && tmp_candidate0 != local_INTRA_PLANAR) {
			local_INTRA_PLANAR = HevcDecoder_Algo_Parser_INTRA_PLANAR;
			candidate[2] = local_INTRA_PLANAR;
		} else {
			tmp_candidate1 = candidate[0];
			local_INTRA_DC = HevcDecoder_Algo_Parser_INTRA_DC;
			tmp_candidate2 = candidate[1];
			local_INTRA_DC = HevcDecoder_Algo_Parser_INTRA_DC;
			if (tmp_candidate1 != local_INTRA_DC && tmp_candidate2 != local_INTRA_DC) {
				local_INTRA_DC = HevcDecoder_Algo_Parser_INTRA_DC;
				candidate[2] = local_INTRA_DC;
			} else {
				local_INTRA_ANGULAR_26 = HevcDecoder_Algo_Parser_INTRA_ANGULAR_26;
				candidate[2] = local_INTRA_ANGULAR_26;
			}
		}
	}
	if (prev_intra_luma_pred_flag == 1) {
		tmp_candidate3 = candidate[mpm_idx_or_rem_intra_luma_pred_mode];
		ret[0] = tmp_candidate3;
	} else {
		tmp_candidate4 = candidate[0];
		tmp_candidate5 = candidate[1];
		if (tmp_candidate4 > tmp_candidate5) {
			tmp_candidate6 = candidate[0];
			candidate[3] = tmp_candidate6;
			tmp_candidate7 = candidate[1];
			candidate[0] = tmp_candidate7;
			tmp_candidate8 = candidate[3];
			candidate[1] = tmp_candidate8;
		}
		tmp_candidate9 = candidate[0];
		tmp_candidate10 = candidate[2];
		if (tmp_candidate9 > tmp_candidate10) {
			tmp_candidate11 = candidate[0];
			candidate[3] = tmp_candidate11;
			tmp_candidate12 = candidate[2];
			candidate[0] = tmp_candidate12;
			tmp_candidate13 = candidate[3];
			candidate[2] = tmp_candidate13;
		}
		tmp_candidate14 = candidate[1];
		tmp_candidate15 = candidate[2];
		if (tmp_candidate14 > tmp_candidate15) {
			tmp_candidate16 = candidate[1];
			candidate[3] = tmp_candidate16;
			tmp_candidate17 = candidate[2];
			candidate[1] = tmp_candidate17;
			tmp_candidate18 = candidate[3];
			candidate[2] = tmp_candidate18;
		}
		ret[0] = mpm_idx_or_rem_intra_luma_pred_mode;
		i = 0;
		while (i <= 2) {
			tmp_ret = ret[0];
			tmp_candidate19 = candidate[i];
			if (tmp_ret >= tmp_candidate19) {
				tmp_ret0 = ret[0];
				ret[0] = tmp_ret0 + 1;
			}
			i = i + 1;
		}
	}
	i0 = 0;
	while (i0 <= size_in_pus - 1) {
		tmp_ret1 = ret[0];
		intraPredMode[x_pu + i0][0] = tmp_ret1;
		tmp_ret2 = ret[0];
		intraPredMode[y_pu + i0][1] = tmp_ret2;
		i0 = i0 + 1;
	}
}
static void HevcDecoder_Algo_Parser_get_INTRA_CHROMA_PRED_MODE(u16 codIRange[1], u16 codIOffset[1], u16 ctxTable[30][48], u16 fifo[10], u32 debinValue[1]) {
	u32 binString[1];
	i32 local_DEBUG_CABAC;
	u16 tmp_codIRange;
	u16 tmp_codIOffset;
	u8 local_SE_INTRA_CHROMA_PRED_MODE;
	u32 tmp_binString;

	binString[0] = 0;
	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
		printf(" INTRA_CHROMA_PRED_MODE ==>\n");
		tmp_codIRange = codIRange[0];
		tmp_codIOffset = codIOffset[0];
		printf("codIRange := %u codIOffset := %u\n", tmp_codIRange, tmp_codIOffset);
	}
	local_SE_INTRA_CHROMA_PRED_MODE = HevcDecoder_Algo_Parser_SE_INTRA_CHROMA_PRED_MODE;
	HevcDecoder_Algo_Parser_decodeDecisionTop(0, binString, codIRange, codIOffset, ctxTable, local_SE_INTRA_CHROMA_PRED_MODE, fifo);
	tmp_binString = binString[0];
	if (tmp_binString == 0) {
		debinValue[0] = 4;
	} else {
		HevcDecoder_Algo_Parser_decodeBinsEP(2, debinValue, codIRange, codIOffset, fifo);
	}
	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
	}
}
static void HevcDecoder_Algo_Parser_get_NO_RESIDUAL_SYNTAX_FLAG(u16 codIRange[1], u16 codIOffset[1], u16 ctxTable[30][48], u16 fifo[10], u32 debinValue[1]) {
	i32 local_DEBUG_CABAC;
	u16 tmp_codIRange;
	u16 tmp_codIOffset;
	u8 local_SE_NO_RESIDUAL_SYNTAX_FLAG;

	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
		printf(" NO_RESIDUAL_SYNTAX_FLAG ==>\n");
		tmp_codIRange = codIRange[0];
		tmp_codIOffset = codIOffset[0];
		printf("codIRange := %u codIOffset := %u\n", tmp_codIRange, tmp_codIOffset);
	}
	debinValue[0] = 0;
	local_SE_NO_RESIDUAL_SYNTAX_FLAG = HevcDecoder_Algo_Parser_SE_NO_RESIDUAL_SYNTAX_FLAG;
	HevcDecoder_Algo_Parser_decodeDecisionTop(0, debinValue, codIRange, codIOffset, ctxTable, local_SE_NO_RESIDUAL_SYNTAX_FLAG, fifo);
	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
	}
}
static void HevcDecoder_Algo_Parser_get_MERGE_IDX(u16 codIRange[1], u16 codIOffset[1], u16 ctxTable[30][48], u16 fifo[10], u32 debinValue[1], u8 MaxNumMergeCand) {
	u32 binString[1];
	u8 binIdx;
	i32 local_DEBUG_CABAC;
	u16 tmp_codIRange;
	u16 tmp_codIOffset;
	u8 local_SE_MERGE_IDX;
	u32 tmp_binString;
	u32 tmp_binString0;

	binString[0] = 0;
	binIdx = 1;
	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
		printf(" MERGE_IDX ==>\n");
		tmp_codIRange = codIRange[0];
		tmp_codIOffset = codIOffset[0];
		printf("codIRange := %u codIOffset := %u\n", tmp_codIRange, tmp_codIOffset);
	}
	if (MaxNumMergeCand > 1) {
		local_SE_MERGE_IDX = HevcDecoder_Algo_Parser_SE_MERGE_IDX;
		HevcDecoder_Algo_Parser_decodeDecisionTop(0, binString, codIRange, codIOffset, ctxTable, local_SE_MERGE_IDX, fifo);
		tmp_binString = binString[0];
		while (tmp_binString != 0 && binIdx < MaxNumMergeCand - 1) {
			HevcDecoder_Algo_Parser_decodeBypassTop(binString, codIRange, codIOffset, fifo);
			binIdx = binIdx + 1;
			tmp_binString = binString[0];
		}
	}
	tmp_binString0 = binString[0];
	if (tmp_binString0 == 0) {
		debinValue[0] = binIdx - 1;
	} else {
		debinValue[0] = binIdx;
	}
	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
	}
}
static void HevcDecoder_Algo_Parser_get_MERGE_FLAG(u16 codIRange[1], u16 codIOffset[1], u16 ctxTable[30][48], u16 fifo[10], u32 debinValue[1]) {
	i32 local_DEBUG_CABAC;
	u16 tmp_codIRange;
	u16 tmp_codIOffset;
	u8 local_SE_MERGE_FLAG;

	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
		printf(" MERGE_FLAG ==>\n");
		tmp_codIRange = codIRange[0];
		tmp_codIOffset = codIOffset[0];
		printf("codIRange := %u codIOffset := %u\n", tmp_codIRange, tmp_codIOffset);
	}
	debinValue[0] = 0;
	local_SE_MERGE_FLAG = HevcDecoder_Algo_Parser_SE_MERGE_FLAG;
	HevcDecoder_Algo_Parser_decodeDecisionTop(0, debinValue, codIRange, codIOffset, ctxTable, local_SE_MERGE_FLAG, fifo);
	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
	}
}
static void HevcDecoder_Algo_Parser_get_INTER_PRED_IDC(u16 codIRange[1], u16 codIOffset[1], u16 ctxTable[30][48], u16 fifo[10], u32 debinValue[1], u8 partMode, u8 PbW, u8 PbH, u8 ctDepth) {
	u32 binString[1];
	i32 local_DEBUG_CABAC;
	u16 tmp_codIRange;
	u16 tmp_codIOffset;
	u8 local_SE_INTER_PRED_IDC;
	u32 tmp_binString;
	u32 tmp_binString0;
	u32 tmp_debinValue;
	u8 local_BI_PRED;
	u32 tmp_binString1;

	binString[0] = 0;
	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
		printf(" INTER_PRED_IDC ==> %u\n", ctDepth);
		tmp_codIRange = codIRange[0];
		tmp_codIOffset = codIOffset[0];
		printf("codIRange := %u codIOffset := %u\n", tmp_codIRange, tmp_codIOffset);
	}
	if (PbW + PbH == 12) {
		local_SE_INTER_PRED_IDC = HevcDecoder_Algo_Parser_SE_INTER_PRED_IDC;
		HevcDecoder_Algo_Parser_decodeDecisionTop(4, binString, codIRange, codIOffset, ctxTable, local_SE_INTER_PRED_IDC, fifo);
		tmp_binString = binString[0];
		debinValue[0] = tmp_binString;
	} else {
		local_SE_INTER_PRED_IDC = HevcDecoder_Algo_Parser_SE_INTER_PRED_IDC;
		HevcDecoder_Algo_Parser_decodeDecisionTop(ctDepth, binString, codIRange, codIOffset, ctxTable, local_SE_INTER_PRED_IDC, fifo);
		tmp_binString0 = binString[0];
		debinValue[0] = tmp_binString0;
		tmp_debinValue = debinValue[0];
		if (tmp_debinValue != 0) {
			local_BI_PRED = HevcDecoder_Algo_Parser_BI_PRED;
			debinValue[0] = local_BI_PRED;
		} else {
			local_SE_INTER_PRED_IDC = HevcDecoder_Algo_Parser_SE_INTER_PRED_IDC;
			HevcDecoder_Algo_Parser_decodeDecisionTop(4, binString, codIRange, codIOffset, ctxTable, local_SE_INTER_PRED_IDC, fifo);
			tmp_binString1 = binString[0];
			debinValue[0] = tmp_binString1;
		}
	}
	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
	}
}
static void HevcDecoder_Algo_Parser_get_REF_IDX_LX(u16 codIRange[1], u16 codIOffset[1], u16 ctxTable[30][48], u16 fifo[10], u32 debinValue[1], u8 num_ref_idx_lx_active_minus1) {
	u32 binString[1];
	u8 binIdx;
	i32 local_DEBUG_CABAC;
	u16 tmp_codIRange;
	u16 tmp_codIOffset;
	u8 local_SE_REF_IDX_L0;
	u32 tmp_binString;
	u32 tmp_binString0;
	u32 tmp_binString1;
	u32 tmp_binString2;

	binString[0] = 0;
	binIdx = 1;
	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
		printf(" REF_IDX_L0 ==>\n");
		tmp_codIRange = codIRange[0];
		tmp_codIOffset = codIOffset[0];
		printf("codIRange := %u codIOffset := %u\n", tmp_codIRange, tmp_codIOffset);
	}
	local_SE_REF_IDX_L0 = HevcDecoder_Algo_Parser_SE_REF_IDX_L0;
	HevcDecoder_Algo_Parser_decodeDecisionTop(0, binString, codIRange, codIOffset, ctxTable, local_SE_REF_IDX_L0, fifo);
	tmp_binString = binString[0];
	debinValue[0] = tmp_binString;
	tmp_binString0 = binString[0];
	if (tmp_binString0 == 1 && num_ref_idx_lx_active_minus1 > 1) {
		binString[0] = 0;
		local_SE_REF_IDX_L0 = HevcDecoder_Algo_Parser_SE_REF_IDX_L0;
		HevcDecoder_Algo_Parser_decodeDecisionTop(1, binString, codIRange, codIOffset, ctxTable, local_SE_REF_IDX_L0, fifo);
		binIdx = binIdx + 1;
		tmp_binString1 = binString[0];
		while (tmp_binString1 != 0 && binIdx < num_ref_idx_lx_active_minus1) {
			HevcDecoder_Algo_Parser_decodeBypassTop(binString, codIRange, codIOffset, fifo);
			binIdx = binIdx + 1;
			tmp_binString1 = binString[0];
		}
		tmp_binString2 = binString[0];
		if (tmp_binString2 == 0) {
			debinValue[0] = binIdx - 1;
		} else {
			debinValue[0] = binIdx;
		}
	}
	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
	}
}
static void HevcDecoder_Algo_Parser_get_MVP_LX_FLAG(u16 codIRange[1], u16 codIOffset[1], u16 ctxTable[30][48], u16 fifo[10], u32 debinValue[1]) {
	i32 local_DEBUG_CABAC;
	u16 tmp_codIRange;
	u16 tmp_codIOffset;
	u8 local_SE_MVP_LX_FLAG;

	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
		printf(" MVP_LX_FLAG ==>\n");
		tmp_codIRange = codIRange[0];
		tmp_codIOffset = codIOffset[0];
		printf("codIRange := %u codIOffset := %u\n", tmp_codIRange, tmp_codIOffset);
	}
	debinValue[0] = 0;
	local_SE_MVP_LX_FLAG = HevcDecoder_Algo_Parser_SE_MVP_LX_FLAG;
	HevcDecoder_Algo_Parser_decodeDecisionTop(0, debinValue, codIRange, codIOffset, ctxTable, local_SE_MVP_LX_FLAG, fifo);
	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
	}
}
static void HevcDecoder_Algo_Parser_get_ABS_MVD_GREATER0_FLAG(u16 codIRange[1], u16 codIOffset[1], u16 ctxTable[30][48], u16 fifo[10], u32 debinValue[1]) {
	i32 local_DEBUG_CABAC;
	u16 tmp_codIRange;
	u16 tmp_codIOffset;
	u8 local_SE_ABS_MVD_GREATER0_FLAG;

	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
		printf(" ABS_MVD_GREATER0_FLAG ==>\n");
		tmp_codIRange = codIRange[0];
		tmp_codIOffset = codIOffset[0];
		printf("codIRange := %u codIOffset := %u\n", tmp_codIRange, tmp_codIOffset);
	}
	debinValue[0] = 0;
	local_SE_ABS_MVD_GREATER0_FLAG = HevcDecoder_Algo_Parser_SE_ABS_MVD_GREATER0_FLAG;
	HevcDecoder_Algo_Parser_decodeDecisionTop(0, debinValue, codIRange, codIOffset, ctxTable, local_SE_ABS_MVD_GREATER0_FLAG, fifo);
	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
	}
}
static void HevcDecoder_Algo_Parser_get_ABS_MVD_GREATER1_FLAG(u16 codIRange[1], u16 codIOffset[1], u16 ctxTable[30][48], u16 fifo[10], u32 debinValue[1]) {
	i32 local_DEBUG_CABAC;
	u16 tmp_codIRange;
	u16 tmp_codIOffset;
	u8 local_SE_ABS_MVD_GREATER0_FLAG;

	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
		printf(" ABS_MVD_GREATER1_FLAG ==>\n");
		tmp_codIRange = codIRange[0];
		tmp_codIOffset = codIOffset[0];
		printf("codIRange := %u codIOffset := %u\n", tmp_codIRange, tmp_codIOffset);
	}
	debinValue[0] = 0;
	local_SE_ABS_MVD_GREATER0_FLAG = HevcDecoder_Algo_Parser_SE_ABS_MVD_GREATER0_FLAG;
	HevcDecoder_Algo_Parser_decodeDecisionTop(1, debinValue, codIRange, codIOffset, ctxTable, local_SE_ABS_MVD_GREATER0_FLAG, fifo);
	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
	}
}
static void HevcDecoder_Algo_Parser_xReadEpExGolomb(u32 count_int, u32 debinValue[1], u16 codIRange[1], u16 codIOffset[1], u16 fifo[10]) {
	u32 count;
	u32 bit[1];
	u32 binString[1];
	u32 tmp_bit;
	u32 tmp_debinValue;
	u32 tmp_bit0;
	u32 tmp_debinValue0;
	u32 tmp_binString;

	count = count_int;
	bit[0] = 1;
	binString[0] = 0;
	debinValue[0] = 0;
	tmp_bit = bit[0];
	while (tmp_bit == 1) {
		HevcDecoder_Algo_Parser_decodeBypassTop(bit, codIRange, codIOffset, fifo);
		tmp_debinValue = debinValue[0];
		tmp_bit0 = bit[0];
		debinValue[0] = tmp_debinValue + (tmp_bit0 << count);
		count = count + 1;
		tmp_bit = bit[0];
	}
	count = count - 1;
	if (count != 0) {
		HevcDecoder_Algo_Parser_decodeBinsEP(count, binString, codIRange, codIOffset, fifo);
		tmp_debinValue0 = debinValue[0];
		tmp_binString = binString[0];
		debinValue[0] = tmp_debinValue0 + tmp_binString;
	}
}
static void HevcDecoder_Algo_Parser_get_ABS_MVD_MINUS2(u16 codIRange[1], u16 codIOffset[1], u16 fifo[10], u32 debinValue[1]) {
	i32 local_DEBUG_CABAC;
	u16 tmp_codIRange;
	u16 tmp_codIOffset;

	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
		printf(" ABS_MVD_MINUS2 ==>\n");
		tmp_codIRange = codIRange[0];
		tmp_codIOffset = codIOffset[0];
		printf("codIRange := %u codIOffset := %u\n", tmp_codIRange, tmp_codIOffset);
	}
	debinValue[0] = 0;
	HevcDecoder_Algo_Parser_xReadEpExGolomb(1, debinValue, codIRange, codIOffset, fifo);
	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
	}
}
static void HevcDecoder_Algo_Parser_get_MVD_SIGN_FLAG(u16 codIRange[1], u16 codIOffset[1], u16 fifo[10], u32 debinValue[1]) {
	i32 local_DEBUG_CABAC;
	u16 tmp_codIRange;
	u16 tmp_codIOffset;

	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
		printf(" MVD_SIGN_FLAG ==>\n");
		tmp_codIRange = codIRange[0];
		tmp_codIOffset = codIOffset[0];
		printf("codIRange := %u codIOffset := %u\n", tmp_codIRange, tmp_codIOffset);
	}
	HevcDecoder_Algo_Parser_decodeBypassTop(debinValue, codIRange, codIOffset, fifo);
	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
	}
}
static void HevcDecoder_Algo_Parser_get_SPLIT_TRANSFORM_FLAG(u16 codIRange[1], u16 codIOffset[1], u16 ctxTable[30][48], u16 fifo[10], u32 debinValue[1], u8 log2TransformBlockSize) {
	i32 local_DEBUG_CABAC;
	u16 tmp_codIRange;
	u16 tmp_codIOffset;
	u8 local_SE_SPLIT_TRANSFORM_FLAG;

	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
		printf(" SPLIT_TRANSFORM_FLAG ==> %i\n", 5 - log2TransformBlockSize);
		tmp_codIRange = codIRange[0];
		tmp_codIOffset = codIOffset[0];
		printf("codIRange := %u codIOffset := %u\n", tmp_codIRange, tmp_codIOffset);
	}
	debinValue[0] = 0;
	local_SE_SPLIT_TRANSFORM_FLAG = HevcDecoder_Algo_Parser_SE_SPLIT_TRANSFORM_FLAG;
	HevcDecoder_Algo_Parser_decodeDecisionTop(5 - log2TransformBlockSize, debinValue, codIRange, codIOffset, ctxTable, local_SE_SPLIT_TRANSFORM_FLAG, fifo);
	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
	}
}
static void HevcDecoder_Algo_Parser_get_CBF_CB_CR(u16 codIRange[1], u16 codIOffset[1], u16 ctxTable[30][48], u16 fifo[10], u32 debinValue[1], u8 trafoDepth) {
	i32 local_DEBUG_CABAC;
	u16 tmp_codIRange;
	u16 tmp_codIOffset;
	u8 local_SE_CBF_CB_CR;

	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
		printf(" CBF_CB_CR ==> %u\n", trafoDepth);
		tmp_codIRange = codIRange[0];
		tmp_codIOffset = codIOffset[0];
		printf("codIRange := %u codIOffset := %u\n", tmp_codIRange, tmp_codIOffset);
	}
	debinValue[0] = 0;
	local_SE_CBF_CB_CR = HevcDecoder_Algo_Parser_SE_CBF_CB_CR;
	HevcDecoder_Algo_Parser_decodeDecisionTop(trafoDepth, debinValue, codIRange, codIOffset, ctxTable, local_SE_CBF_CB_CR, fifo);
	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
	}
}
static void HevcDecoder_Algo_Parser_get_CBF_LUMA(u16 codIRange[1], u16 codIOffset[1], u16 ctxTable[30][48], u16 fifo[10], u32 debinValue[1], u8 trafoDepth) {
	u16 ctxIdx;
	i32 local_DEBUG_CABAC;
	u16 tmp_codIRange;
	u16 tmp_codIOffset;
	u8 local_SE_CBF_LUMA;

	if (trafoDepth == 0) {
		ctxIdx = 1;
	} else {
		ctxIdx = 0;
	}
	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
		printf(" CBF_LUMA ==> %u\n", ctxIdx);
		tmp_codIRange = codIRange[0];
		tmp_codIOffset = codIOffset[0];
		printf("codIRange := %u codIOffset := %u\n", tmp_codIRange, tmp_codIOffset);
	}
	debinValue[0] = 0;
	local_SE_CBF_LUMA = HevcDecoder_Algo_Parser_SE_CBF_LUMA;
	HevcDecoder_Algo_Parser_decodeDecisionTop(ctxIdx, debinValue, codIRange, codIOffset, ctxTable, local_SE_CBF_LUMA, fifo);
	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
	}
}
static void HevcDecoder_Algo_Parser_get_CU_QP_DELTA_ABS(u16 codIRange[1], u16 codIOffset[1], u16 ctxTable[30][48], u16 fifo[10], u32 debinValue[1]) {
	u8 prefixVal;
	u16 ctxIdx;
	u8 binIdx;
	u32 binString[1];
	u8 discard_suffix[1];
	u8 debinCompleted[1];
	i32 local_DEBUG_CABAC;
	u16 tmp_codIRange;
	u16 tmp_codIOffset;
	u8 tmp_debinCompleted;
	u8 local_SE_CU_QP_DELTA;
	u32 tmp_binString;
	u8 local_DEBIN_TU5;
	u32 tmp_debinValue;

	prefixVal = 0;
	ctxIdx = 0;
	binIdx = 0;
	binString[0] = 0;
	discard_suffix[0] = 0;
	debinCompleted[0] = 0;
	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
		printf(" CU_QP_DELTA_ABS ==>\n");
		tmp_codIRange = codIRange[0];
		tmp_codIOffset = codIOffset[0];
		printf("codIRange := %u codIOffset := %u\n", tmp_codIRange, tmp_codIOffset);
	}
	debinValue[0] = 0;
	tmp_debinCompleted = debinCompleted[0];
	while (tmp_debinCompleted == 0) {
		local_SE_CU_QP_DELTA = HevcDecoder_Algo_Parser_SE_CU_QP_DELTA;
		HevcDecoder_Algo_Parser_decodeDecisionTop(ctxIdx, binString, codIRange, codIOffset, ctxTable, local_SE_CU_QP_DELTA, fifo);
		tmp_binString = binString[0];
		local_DEBIN_TU5 = HevcDecoder_Algo_Parser_DEBIN_TU5;
		HevcDecoder_Algo_Parser_debinTU(tmp_binString, binIdx, local_DEBIN_TU5, debinCompleted, debinValue, discard_suffix);
		ctxIdx = 1;
		binIdx = binIdx + 1;
		tmp_debinCompleted = debinCompleted[0];
	}
	prefixVal = debinValue[0];
	if (prefixVal >= 5) {
		HevcDecoder_Algo_Parser_xReadEpExGolomb(0, debinValue, codIRange, codIOffset, fifo);
		tmp_debinValue = debinValue[0];
		debinValue[0] = tmp_debinValue + prefixVal;
	}
	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
	}
}
static void HevcDecoder_Algo_Parser_get_CU_QP_DELTA_SIGN_FLAG(u16 codIRange[1], u16 codIOffset[1], u16 fifo[10], u32 debinValue[1]) {
	i32 local_DEBUG_CABAC;
	u16 tmp_codIRange;
	u16 tmp_codIOffset;

	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
		printf(" CU_QP_DELTA_SIGN_FLAG ==>\n");
		tmp_codIRange = codIRange[0];
		tmp_codIOffset = codIOffset[0];
		printf("codIRange := %u codIOffset := %u\n", tmp_codIRange, tmp_codIOffset);
	}
	HevcDecoder_Algo_Parser_decodeBypassTop(debinValue, codIRange, codIOffset, fifo);
	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
	}
}
static u8 HevcDecoder_Algo_Parser_getScanIdx(u8 predMode, u8 log2TrafoSize, u8 intraPredMode) {
	u8 local_INTRA;
	u8 tmp_if;
	u8 local_SCAN_VER;
	u8 local_SCAN_HOR;
	u8 local_SCAN_ZIGZAG;

	local_INTRA = HevcDecoder_Algo_Parser_INTRA;
	if (predMode == local_INTRA && log2TrafoSize < 4) {
		if (intraPredMode >= 6 && intraPredMode <= 14) {
			local_SCAN_VER = HevcDecoder_Algo_Parser_SCAN_VER;
			tmp_if = local_SCAN_VER;
		} else {
			if (intraPredMode >= 22 && intraPredMode <= 30) {
				local_SCAN_HOR = HevcDecoder_Algo_Parser_SCAN_HOR;
				tmp_if = local_SCAN_HOR;
			} else {
				local_SCAN_ZIGZAG = HevcDecoder_Algo_Parser_SCAN_ZIGZAG;
				tmp_if = local_SCAN_ZIGZAG;
			}
		}
	} else {
		local_SCAN_ZIGZAG = HevcDecoder_Algo_Parser_SCAN_ZIGZAG;
		tmp_if = local_SCAN_ZIGZAG;
	}
	return tmp_if;
}
static void HevcDecoder_Algo_Parser_get_TRANSFORM_SKIP_FLAG(u16 codIRange[1], u16 codIOffset[1], u16 ctxTable[30][48], u16 fifo[10], u32 debinValue[1], u8 rc_TType) {
	u8 local_TEXT_LUMA;
	u16 ctxIdx;
	i32 local_DEBUG_CABAC;
	u16 tmp_codIRange;
	u16 tmp_codIOffset;
	u8 local_SE_TRANSFORM_SKIP_FLAG;

	local_TEXT_LUMA = HevcDecoder_Algo_Parser_TEXT_LUMA;
	if (rc_TType == local_TEXT_LUMA) {
		ctxIdx = 0;
	} else {
		ctxIdx = 1;
	}
	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
		printf(" TRANSFORM_SKIP_FLAG ==>\n");
		tmp_codIRange = codIRange[0];
		tmp_codIOffset = codIOffset[0];
		printf("codIRange := %u codIOffset := %u\n", tmp_codIRange, tmp_codIOffset);
	}
	debinValue[0] = 0;
	local_SE_TRANSFORM_SKIP_FLAG = HevcDecoder_Algo_Parser_SE_TRANSFORM_SKIP_FLAG;
	HevcDecoder_Algo_Parser_decodeDecisionTop(ctxIdx, debinValue, codIRange, codIOffset, ctxTable, local_SE_TRANSFORM_SKIP_FLAG, fifo);
	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
	}
}
static u8 HevcDecoder_Algo_Parser_context_93312(u8 binIdx, u8 log2TrafoSize, u8 cIdx) {
	u8 ctx_offset;
	u8 ctx_shift;

	if (cIdx == 0) {
		ctx_offset = 3 * (log2TrafoSize - 2) + ((log2TrafoSize - 1) >> 2);
	} else {
		ctx_offset = 15;
	}
	if (cIdx == 0) {
		ctx_shift = (log2TrafoSize + 1) >> 2;
	} else {
		ctx_shift = log2TrafoSize - 2;
	}
	return (binIdx >> ctx_shift) + ctx_offset;
}
static void HevcDecoder_Algo_Parser_get_LAST_SIGNIFICANT_COEFF_X_PREFIX(u16 codIRange[1], u16 codIOffset[1], u16 ctxTable[30][48], u16 fifo[10], u32 debinValue[1], u8 log2TrafoWidth, u8 cIdx) {
	u16 ctxIdx;
	u8 binIdx;
	u32 binString[1];
	u8 discard_suffix[1];
	u8 debinCompleted[1];
	i32 local_DEBUG_CABAC;
	u16 tmp_codIRange;
	u16 tmp_codIOffset;
	u8 tmp_debinCompleted;
	u8 local_SE_LAST_SIGNIFICANT_COEFF_X_PREFIX;
	u32 tmp_binString;

	binIdx = 0;
	binString[0] = 0;
	discard_suffix[0] = 0;
	debinCompleted[0] = 0;
	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
		printf(" LAST_SIGNIFICANT_COEFF_X_PREFIX ==> %llu\n", 1 << log2TrafoWidth);
		tmp_codIRange = codIRange[0];
		tmp_codIOffset = codIOffset[0];
		printf("codIRange := %u codIOffset := %u\n", tmp_codIRange, tmp_codIOffset);
	}
	tmp_debinCompleted = debinCompleted[0];
	while (tmp_debinCompleted == 0) {
		ctxIdx = HevcDecoder_Algo_Parser_context_93312(binIdx, log2TrafoWidth, cIdx);
		local_SE_LAST_SIGNIFICANT_COEFF_X_PREFIX = HevcDecoder_Algo_Parser_SE_LAST_SIGNIFICANT_COEFF_X_PREFIX;
		HevcDecoder_Algo_Parser_decodeDecisionTop(ctxIdx, binString, codIRange, codIOffset, ctxTable, local_SE_LAST_SIGNIFICANT_COEFF_X_PREFIX, fifo);
		tmp_binString = binString[0];
		HevcDecoder_Algo_Parser_debinTU(tmp_binString, binIdx, (log2TrafoWidth << 1) - 2, debinCompleted, debinValue, discard_suffix);
		binIdx = binIdx + 1;
		tmp_debinCompleted = debinCompleted[0];
	}
	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
	}
}
static void HevcDecoder_Algo_Parser_get_LAST_SIGNIFICANT_COEFF_Y_PREFIX(u16 codIRange[1], u16 codIOffset[1], u16 ctxTable[30][48], u16 fifo[10], u32 debinValue[1], u8 log2TrafoHeight, u8 cIdx) {
	u16 ctxIdx;
	u8 binIdx;
	u32 binString[1];
	u8 discard_suffix[1];
	u8 debinCompleted[1];
	i32 local_DEBUG_CABAC;
	u16 tmp_codIRange;
	u16 tmp_codIOffset;
	u8 tmp_debinCompleted;
	u8 local_SE_LAST_SIGNIFICANT_COEFF_Y_PREFIX;
	u32 tmp_binString;

	binIdx = 0;
	binString[0] = 0;
	discard_suffix[0] = 0;
	debinCompleted[0] = 0;
	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
		printf(" LAST_SIGNIFICANT_COEFF_Y_PREFIX ==> %llu\n", 1 << log2TrafoHeight);
		tmp_codIRange = codIRange[0];
		tmp_codIOffset = codIOffset[0];
		printf("codIRange := %u codIOffset := %u\n", tmp_codIRange, tmp_codIOffset);
	}
	tmp_debinCompleted = debinCompleted[0];
	while (tmp_debinCompleted == 0) {
		ctxIdx = HevcDecoder_Algo_Parser_context_93312(binIdx, log2TrafoHeight, cIdx);
		local_SE_LAST_SIGNIFICANT_COEFF_Y_PREFIX = HevcDecoder_Algo_Parser_SE_LAST_SIGNIFICANT_COEFF_Y_PREFIX;
		HevcDecoder_Algo_Parser_decodeDecisionTop(ctxIdx, binString, codIRange, codIOffset, ctxTable, local_SE_LAST_SIGNIFICANT_COEFF_Y_PREFIX, fifo);
		tmp_binString = binString[0];
		HevcDecoder_Algo_Parser_debinTU(tmp_binString, binIdx, (log2TrafoHeight << 1) - 2, debinCompleted, debinValue, discard_suffix);
		binIdx = binIdx + 1;
		tmp_debinCompleted = debinCompleted[0];
	}
	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
	}
}
static void HevcDecoder_Algo_Parser_get_LAST_SIGNIFICANT_COEFF_XY_SUFFIX(u16 codIRange[1], u16 codIOffset[1], u16 fifo[10], u32 debinValue[1], u8 prefix) {
	i32 local_DEBUG_CABAC;
	u16 tmp_codIRange;
	u16 tmp_codIOffset;

	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
		printf(" LAST_SIGNIFICANT_COEFF_XY_SUFFIX ==>\n");
		tmp_codIRange = codIRange[0];
		tmp_codIOffset = codIOffset[0];
		printf("codIRange := %u codIOffset := %u\n", tmp_codIRange, tmp_codIOffset);
	}
	HevcDecoder_Algo_Parser_decodeBinsEP((prefix >> 1) - 1, debinValue, codIRange, codIOffset, fifo);
	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
	}
}
static void HevcDecoder_Algo_Parser_context_93313(u8 coded_sub_block_flag[8][8], u16 xS, u16 yS, u8 cIdx, u8 log2TrafoSize, u16 ctxIdx[1]) {
	u8 csbfCtx;
	u8 trafoSize;
	u8 tmp_coded_sub_block_flag;
	i32 tmp_min;
	u8 tmp_if;

	csbfCtx = 0;
	trafoSize = (1 << (log2TrafoSize - 2)) - 1;
	if (xS < trafoSize) {
		csbfCtx = coded_sub_block_flag[xS + 1][yS];
	}
	if (yS < trafoSize) {
		tmp_coded_sub_block_flag = coded_sub_block_flag[xS][yS + 1];
		csbfCtx = csbfCtx + tmp_coded_sub_block_flag;
	}
	tmp_min = HevcDecoder_Algo_Parser_min(csbfCtx, 1);
	if (cIdx == 0) {
		tmp_if = 0;
	} else {
		tmp_if = 2;
	}
	ctxIdx[0] = tmp_min + tmp_if;
}
static void HevcDecoder_Algo_Parser_get_CODED_SUB_BLOCK_FLAG(u16 codIRange[1], u16 codIOffset[1], u16 ctxTable[30][48], u16 fifo[10], u32 debinValue[1], u8 coded_sub_block_flag[8][8], u16 xC, u16 yC, u8 cIdx, u8 log2TrafoSize) {
	u16 ctxIdx[1];
	i32 local_DEBUG_CABAC;
	u16 tmp_ctxIdx;
	u16 tmp_codIRange;
	u16 tmp_codIOffset;
	u16 tmp_ctxIdx0;
	u8 local_SE_CODED_SUB_BLOCK_FLAG;

	HevcDecoder_Algo_Parser_context_93313(coded_sub_block_flag, xC, yC, cIdx, log2TrafoSize, ctxIdx);
	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
		tmp_ctxIdx = ctxIdx[0];
		printf(" CODED_SUB_BLOCK_FLAG ==> %u\n", tmp_ctxIdx & 1);
		tmp_codIRange = codIRange[0];
		tmp_codIOffset = codIOffset[0];
		printf("codIRange := %u codIOffset := %u\n", tmp_codIRange, tmp_codIOffset);
	}
	debinValue[0] = 0;
	tmp_ctxIdx0 = ctxIdx[0];
	local_SE_CODED_SUB_BLOCK_FLAG = HevcDecoder_Algo_Parser_SE_CODED_SUB_BLOCK_FLAG;
	HevcDecoder_Algo_Parser_decodeDecisionTop(tmp_ctxIdx0, debinValue, codIRange, codIOffset, ctxTable, local_SE_CODED_SUB_BLOCK_FLAG, fifo);
	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
	}
}
static void HevcDecoder_Algo_Parser_context_93314(u8 coded_sub_block_flag[8][8], u16 xC, u16 yC, u8 cIdx, u8 log2TrafoSize, u8 scanIdx, u16 ctxIdx[1]) {
	u16 xS;
	u16 yS;
	u8 xP;
	u8 yP;
	u8 sigCtx;
	u8 prevCsbf;
	u8 trafoSize;
	u8 tmp_coded_sub_block_flag;
	u8 tmp_coded_sub_block_flag0;
	u8 tmp_if;

	xS = xC >> 2;
	yS = yC >> 2;
	xP = xC & 3;
	yP = yC & 3;
	prevCsbf = 0;
	trafoSize = ((1 << log2TrafoSize) - 1) >> 2;
	if (xC + yC == 0) {
		sigCtx = 0;
	} else {
		if (log2TrafoSize == 2) {
			sigCtx = HevcDecoder_Algo_Parser_ctxInMap[(yC << 2) + xC];
		} else {
			if (xS < trafoSize) {
				tmp_coded_sub_block_flag = coded_sub_block_flag[xS + 1][yS];
				prevCsbf = prevCsbf + tmp_coded_sub_block_flag;
			}
			if (yS < trafoSize) {
				tmp_coded_sub_block_flag0 = coded_sub_block_flag[xS][yS + 1];
				prevCsbf = prevCsbf + (tmp_coded_sub_block_flag0 << 1);
			}
			if (prevCsbf == 0) {
				if (xP + yP == 0) {
					sigCtx = 2;
				} else {
					if (xP + yP < 3) {
						sigCtx = 1;
					} else {
						sigCtx = 0;
					}
				}
			} else {
				if (prevCsbf == 1) {
					if (yP == 0) {
						sigCtx = 2;
					} else {
						if (yP == 1) {
							sigCtx = 1;
						} else {
							sigCtx = 0;
						}
					}
				} else {
					if (prevCsbf == 2) {
						if (xP == 0) {
							sigCtx = 2;
						} else {
							if (xP == 1) {
								sigCtx = 1;
							} else {
								sigCtx = 0;
							}
						}
					} else {
						sigCtx = 2;
					}
				}
			}
			if (cIdx == 0) {
				if (xS + yS > 0) {
					sigCtx = sigCtx + 3;
				}
				if (log2TrafoSize == 3) {
					if (scanIdx == 0) {
						tmp_if = 9;
					} else {
						tmp_if = 15;
					}
					sigCtx = sigCtx + tmp_if;
				} else {
					sigCtx = sigCtx + 21;
				}
			} else {
				if (log2TrafoSize == 3) {
					sigCtx = sigCtx + 9;
				} else {
					sigCtx = sigCtx + 12;
				}
			}
		}
	}
	if (cIdx == 0) {
		ctxIdx[0] = sigCtx;
	} else {
		ctxIdx[0] = 27 + sigCtx;
	}
}
static void HevcDecoder_Algo_Parser_get_SIGNIFICANT_COEFF_FLAG(u16 codIRange[1], u16 codIOffset[1], u16 ctxTable[30][48], u16 fifo[10], u32 debinValue[1], u8 coded_sub_block_flag[8][8], u16 xC, u16 yC, u8 cIdx, u8 log2TrafoSize, u8 scanIdx) {
	u16 ctxIdx[1];
	i32 local_DEBUG_CABAC;
	u16 tmp_ctxIdx;
	u16 tmp_codIRange;
	u16 tmp_codIOffset;
	u16 tmp_ctxIdx0;
	u8 local_SE_SIGNIFICANT_COEFF_FLAG;

	HevcDecoder_Algo_Parser_context_93314(coded_sub_block_flag, xC, yC, cIdx, log2TrafoSize, scanIdx, ctxIdx);
	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
		tmp_ctxIdx = ctxIdx[0];
		printf(" SIGNIFICANT_COEFF_FLAG ==> %u\n", tmp_ctxIdx);
		tmp_codIRange = codIRange[0];
		tmp_codIOffset = codIOffset[0];
		printf("codIRange := %u codIOffset := %u\n", tmp_codIRange, tmp_codIOffset);
	}
	debinValue[0] = 0;
	tmp_ctxIdx0 = ctxIdx[0];
	local_SE_SIGNIFICANT_COEFF_FLAG = HevcDecoder_Algo_Parser_SE_SIGNIFICANT_COEFF_FLAG;
	HevcDecoder_Algo_Parser_decodeDecisionTop(tmp_ctxIdx0, debinValue, codIRange, codIOffset, ctxTable, local_SE_SIGNIFICANT_COEFF_FLAG, fifo);
	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
	}
}
static void HevcDecoder_Algo_Parser_context_93315(u8 cIdx, i8 i, i32 first_elem, i32 first_subset, u8 ctxSet[1], u8 greater1Ctx[1], u16 ctxIdxInc[1]) {
	u8 tmp_greater1Ctx;
	u8 tmp_ctxSet;
	u8 tmp_ctxSet0;
	u8 tmp_greater1Ctx0;
	u16 tmp_ctxIdxInc;

	if (first_elem == 1) {
		if (i > 0 && cIdx == 0) {
			ctxSet[0] = 2;
		} else {
			ctxSet[0] = 0;
		}
		tmp_greater1Ctx = greater1Ctx[0];
		if (first_subset == 0 && tmp_greater1Ctx == 0) {
			tmp_ctxSet = ctxSet[0];
			ctxSet[0] = tmp_ctxSet + 1;
		}
		greater1Ctx[0] = 1;
	}
	tmp_ctxSet0 = ctxSet[0];
	tmp_greater1Ctx0 = greater1Ctx[0];
	ctxIdxInc[0] = (tmp_ctxSet0 << 2) + tmp_greater1Ctx0;
	if (cIdx > 0) {
		tmp_ctxIdxInc = ctxIdxInc[0];
		ctxIdxInc[0] = tmp_ctxIdxInc + 16;
	}
}
static void HevcDecoder_Algo_Parser_get_COEFF_ABS_LEVEL_GREATER1_FLAG(u16 codIRange[1], u16 codIOffset[1], u16 ctxTable[30][48], u16 fifo[10], i32 debinValue[1], u16 ctxIdx) {
	i32 local_DEBUG_CABAC;
	u16 tmp_codIRange;
	u16 tmp_codIOffset;
	u8 local_SE_COEFF_ABS_LEVEL_GREATER1_FLAG;

	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
		printf(" COEFF_ABS_LEVEL_GREATER1_FLAG ==> %u\n", ctxIdx);
		tmp_codIRange = codIRange[0];
		tmp_codIOffset = codIOffset[0];
		printf("codIRange := %u codIOffset := %u\n", tmp_codIRange, tmp_codIOffset);
	}
	debinValue[0] = 0;
	local_SE_COEFF_ABS_LEVEL_GREATER1_FLAG = HevcDecoder_Algo_Parser_SE_COEFF_ABS_LEVEL_GREATER1_FLAG;
	HevcDecoder_Algo_Parser_decodeDecisionTop(ctxIdx, debinValue, codIRange, codIOffset, ctxTable, local_SE_COEFF_ABS_LEVEL_GREATER1_FLAG, fifo);
	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
	}
}
static void HevcDecoder_Algo_Parser_get_COEFF_ABS_LEVEL_GREATER2_FLAG(u16 codIRange[1], u16 codIOffset[1], u16 ctxTable[30][48], u16 fifo[10], u32 debinValue[1], u8 cIdx, u8 ctxSet) {
	u8 tmp_if;
	u16 ctxIdx;
	i32 local_DEBUG_CABAC;
	u16 tmp_codIRange;
	u16 tmp_codIOffset;
	u8 local_SE_COEFF_ABS_LEVEL_GREATER2_FLAG;

	if (cIdx != 0) {
		tmp_if = 4;
	} else {
		tmp_if = 0;
	}
	ctxIdx = ctxSet + tmp_if;
	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
		printf(" COEFF_ABS_LEVEL_GREATER2_FLAG ==> %u\n", ctxIdx);
		tmp_codIRange = codIRange[0];
		tmp_codIOffset = codIOffset[0];
		printf("codIRange := %u codIOffset := %u\n", tmp_codIRange, tmp_codIOffset);
	}
	debinValue[0] = 0;
	local_SE_COEFF_ABS_LEVEL_GREATER2_FLAG = HevcDecoder_Algo_Parser_SE_COEFF_ABS_LEVEL_GREATER2_FLAG;
	HevcDecoder_Algo_Parser_decodeDecisionTop(ctxIdx, debinValue, codIRange, codIOffset, ctxTable, local_SE_COEFF_ABS_LEVEL_GREATER2_FLAG, fifo);
	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
	}
}
static void HevcDecoder_Algo_Parser_get_COEFF_SIGN_FLAG(u16 codIRange[1], u16 codIOffset[1], u16 fifo[10], u32 debinValue[1], u8 nb) {
	i32 local_DEBUG_CABAC;
	u16 tmp_codIRange;
	u16 tmp_codIOffset;

	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC && nb != 0) {
		printf(" COEFF_SIGN_FLAG ==> %u\n", nb);
		tmp_codIRange = codIRange[0];
		tmp_codIOffset = codIOffset[0];
		printf("codIRange := %u codIOffset := %u\n", tmp_codIRange, tmp_codIOffset);
	}
	HevcDecoder_Algo_Parser_decodeBinsEP(nb, debinValue, codIRange, codIOffset, fifo);
	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC && nb != 0) {
	}
}
static void HevcDecoder_Algo_Parser_get_COEFF_ABS_LEVEL(u16 codIRange[1], u16 codIOffset[1], u16 fifo[10], u32 debinValue[1], u8 rParam) {
	u16 prefix;
	u32 codeWord[1];
	i32 local_DEBUG_CABAC;
	u16 tmp_codIRange;
	u16 tmp_codIOffset;
	u32 tmp_codeWord;
	u32 tmp_codeWord0;
	u32 tmp_codeWord1;
	u32 tmp_codeWord2;
	u32 tmp_codeWord3;

	prefix = 0;
	codeWord[0] = 1;
	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
		printf(" COEFF_ABS_LEVEL ==> %u\n", rParam);
		tmp_codIRange = codIRange[0];
		tmp_codIOffset = codIOffset[0];
		printf("codIRange := %u codIOffset := %u\n", tmp_codIRange, tmp_codIOffset);
	}
	tmp_codeWord = codeWord[0];
	while (tmp_codeWord == 1) {
		prefix = prefix + 1;
		HevcDecoder_Algo_Parser_decodeBypassTop(codeWord, codIRange, codIOffset, fifo);
		tmp_codeWord = codeWord[0];
	}
	tmp_codeWord0 = codeWord[0];
	codeWord[0] = 1 - tmp_codeWord0;
	tmp_codeWord1 = codeWord[0];
	prefix = prefix - tmp_codeWord1;
	if (prefix < 3) {
		HevcDecoder_Algo_Parser_decodeBinsEP(rParam, codeWord, codIRange, codIOffset, fifo);
		tmp_codeWord2 = codeWord[0];
		debinValue[0] = (prefix << rParam) + tmp_codeWord2;
	} else {
		HevcDecoder_Algo_Parser_decodeBinsEP(prefix - 3 + rParam, codeWord, codIRange, codIOffset, fifo);
		tmp_codeWord3 = codeWord[0];
		debinValue[0] = (((1 << (prefix - 3)) + 3 - 1) << rParam) + tmp_codeWord3;
	}
	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
	}
}
static void compute_POC(i32 pic_order_cnt_lsb) {
	i32 iPOClsb;
	i32 local_poc;
	i32 iPrevPOC;
	u16 local_sps_id;
	i32 iMaxPOClsb;
	i32 iPrevPOClsb;
	i32 iPrevPOCmsb;
	i32 iPOCmsb;
	u8 local_nal_unit_type;
	u8 local_NAL_BLA_W_LP;
	u8 local_NAL_BLA_W_RADL;
	u8 local_NAL_BLA_N_LP;

	iPOClsb = pic_order_cnt_lsb;
	local_poc = poc;
	iPrevPOC = local_poc;
	local_sps_id = sps_id;
	iMaxPOClsb = max_poc_lsb[local_sps_id];
	iPrevPOClsb = iPrevPOC % iMaxPOClsb;
	iPrevPOCmsb = iPrevPOC - iPrevPOClsb;
	if (iPOClsb < iPrevPOClsb && iPrevPOClsb - iPOClsb >= iMaxPOClsb / 2) {
		iPOCmsb = iPrevPOCmsb + iMaxPOClsb;
	} else {
		if (iPOClsb > iPrevPOClsb && iPOClsb - iPrevPOClsb > iMaxPOClsb / 2) {
			iPOCmsb = iPrevPOCmsb - iMaxPOClsb;
		} else {
			iPOCmsb = iPrevPOCmsb;
		}
	}
	local_nal_unit_type = nal_unit_type;
	local_NAL_BLA_W_LP = HevcDecoder_Algo_Parser_NAL_BLA_W_LP;
	local_nal_unit_type = nal_unit_type;
	local_NAL_BLA_W_RADL = HevcDecoder_Algo_Parser_NAL_BLA_W_RADL;
	local_nal_unit_type = nal_unit_type;
	local_NAL_BLA_N_LP = HevcDecoder_Algo_Parser_NAL_BLA_N_LP;
	if (local_nal_unit_type == local_NAL_BLA_W_LP || local_nal_unit_type == local_NAL_BLA_W_RADL || local_nal_unit_type == local_NAL_BLA_N_LP) {
		iPOCmsb = 0;
	}
	poc = iPOCmsb + iPOClsb;
}
static void setRefTables(i32 sps_id, i32 idx, i8 pc_rps[15][65][131], i32 poc) {
	u32 j;
	u32 k;
	i32 pocLt;
	i32 i;
	u8 local_NUM_NEGATIVE_PICS;
	i8 tmp_pc_rps;
	u8 local_USED;
	i8 tmp_pc_rps0;
	u8 local_ST_CURR_BEF;
	u8 local_DELTAPOC;
	i8 tmp_pc_rps1;
	u8 local_ST_FOLL;
	i8 tmp_pc_rps2;
	i32 i0;
	u8 local_NUM_PICS;
	i8 tmp_pc_rps3;
	i8 tmp_pc_rps4;
	u8 local_ST_CURR_AFT;
	i8 tmp_pc_rps5;
	i8 tmp_pc_rps6;
	i32 i1;
	u16 local_num_long_term_sps;
	u16 local_num_long_term_pics;
	u8 tmp_delta_poc_msb_present_flag;
	u8 tmp_DeltaPocMsbCycleLt;
	u32 tmp_max_poc_lsb;
	i32 local_pic_order_cnt_lsb;
	u8 tmp_UsedByCurrPicLt;
	u8 local_LT_CURR;
	u8 local_LT_FOLL;

	j = 0;
	k = 0;
	pocLt = poc_lsb_lt[0];
	i = 0;
	local_NUM_NEGATIVE_PICS = HevcDecoder_Algo_Parser_NUM_NEGATIVE_PICS;
	tmp_pc_rps = pc_rps[sps_id][idx][local_NUM_NEGATIVE_PICS];
	while (i <= tmp_pc_rps - 1) {
		local_USED = HevcDecoder_Algo_Parser_USED;
		tmp_pc_rps0 = pc_rps[sps_id][idx][local_USED + i];
		if (tmp_pc_rps0 == 1) {
			local_ST_CURR_BEF = HevcDecoder_Algo_Parser_ST_CURR_BEF;
			local_DELTAPOC = HevcDecoder_Algo_Parser_DELTAPOC;
			tmp_pc_rps1 = pc_rps[sps_id][idx][local_DELTAPOC + i];
			pocTables[local_ST_CURR_BEF][j] = poc + tmp_pc_rps1;
			j = j + 1;
		} else {
			local_ST_FOLL = HevcDecoder_Algo_Parser_ST_FOLL;
			local_DELTAPOC = HevcDecoder_Algo_Parser_DELTAPOC;
			tmp_pc_rps2 = pc_rps[sps_id][idx][local_DELTAPOC + i];
			pocTables[local_ST_FOLL][k] = poc + tmp_pc_rps2;
			k = k + 1;
		}
		i = i + 1;
	}
	local_ST_CURR_BEF = HevcDecoder_Algo_Parser_ST_CURR_BEF;
	numPic[local_ST_CURR_BEF] = j;
	j = 0;
	local_NUM_NEGATIVE_PICS = HevcDecoder_Algo_Parser_NUM_NEGATIVE_PICS;
	i0 = pc_rps[sps_id][idx][local_NUM_NEGATIVE_PICS];
	local_NUM_PICS = HevcDecoder_Algo_Parser_NUM_PICS;
	tmp_pc_rps3 = pc_rps[sps_id][idx][local_NUM_PICS];
	while (i0 <= tmp_pc_rps3 - 1) {
		local_USED = HevcDecoder_Algo_Parser_USED;
		tmp_pc_rps4 = pc_rps[sps_id][idx][local_USED + i0];
		if (tmp_pc_rps4 == 1) {
			local_ST_CURR_AFT = HevcDecoder_Algo_Parser_ST_CURR_AFT;
			local_DELTAPOC = HevcDecoder_Algo_Parser_DELTAPOC;
			tmp_pc_rps5 = pc_rps[sps_id][idx][local_DELTAPOC + i0];
			pocTables[local_ST_CURR_AFT][j] = poc + tmp_pc_rps5;
			j = j + 1;
		} else {
			local_ST_FOLL = HevcDecoder_Algo_Parser_ST_FOLL;
			local_DELTAPOC = HevcDecoder_Algo_Parser_DELTAPOC;
			tmp_pc_rps6 = pc_rps[sps_id][idx][local_DELTAPOC + i0];
			pocTables[local_ST_FOLL][k] = poc + tmp_pc_rps6;
			k = k + 1;
		}
		i0 = i0 + 1;
	}
	local_ST_CURR_AFT = HevcDecoder_Algo_Parser_ST_CURR_AFT;
	numPic[local_ST_CURR_AFT] = j;
	local_ST_FOLL = HevcDecoder_Algo_Parser_ST_FOLL;
	numPic[local_ST_FOLL] = k;
	j = 0;
	k = 0;
	i1 = 0;
	local_num_long_term_sps = num_long_term_sps;
	local_num_long_term_pics = num_long_term_pics;
	while (i1 <= local_num_long_term_sps + local_num_long_term_pics - 1) {
		pocLt = poc_lsb_lt[i1];
		tmp_delta_poc_msb_present_flag = delta_poc_msb_present_flag[i1];
		if (tmp_delta_poc_msb_present_flag == 1) {
			tmp_DeltaPocMsbCycleLt = DeltaPocMsbCycleLt[i1];
			tmp_max_poc_lsb = max_poc_lsb[sps_id];
			local_pic_order_cnt_lsb = pic_order_cnt_lsb;
			pocLt = pocLt + poc - tmp_DeltaPocMsbCycleLt * tmp_max_poc_lsb - local_pic_order_cnt_lsb;
		}
		tmp_UsedByCurrPicLt = UsedByCurrPicLt[i1];
		if (tmp_UsedByCurrPicLt == 1) {
			local_LT_CURR = HevcDecoder_Algo_Parser_LT_CURR;
			pocTables[local_LT_CURR][j] = pocLt;
			j = j + 1;
		} else {
			local_LT_FOLL = HevcDecoder_Algo_Parser_LT_FOLL;
			pocTables[local_LT_FOLL][k] = pocLt;
			k = k + 1;
		}
		i1 = i1 + 1;
	}
	local_LT_CURR = HevcDecoder_Algo_Parser_LT_CURR;
	numPic[local_LT_CURR] = j;
	local_LT_FOLL = HevcDecoder_Algo_Parser_LT_FOLL;
	numPic[local_LT_FOLL] = k;
}
static void set_qPy() {
	u8 local_Log2CtbSize;
	i32 ctb_size_mask;
	u16 local_pps_id;
	u16 tmp_pps_diff_cu_qp_delta_depth;
	i32 MinCuQpDeltaSizeMask;
	u16 local_cu_x0;
	i32 xQgBase;
	u16 local_cu_y0;
	i32 yQgBase;
	u8 local_Log2MinCbSize;
	i32 x_cb;
	i32 y_cb;
	i32 availableA;
	i32 availableB;
	i32 qPy_local;
	i32 qPy_a;
	i32 qPy_b;
	i32 local_qPy_pred;
	u8 local_first_qp_group;
	u8 local_IsCuQpDeltaCoded;
	i8 local_slice_qp;
	i32 local_min_cb_width;
	i16 local_CuQpDelta;
	u16 local_qp_bd_offset_luma;

	local_Log2CtbSize = Log2CtbSize;
	ctb_size_mask = (1 << local_Log2CtbSize) - 1;
	local_Log2CtbSize = Log2CtbSize;
	local_pps_id = pps_id;
	tmp_pps_diff_cu_qp_delta_depth = pps_diff_cu_qp_delta_depth[local_pps_id];
	MinCuQpDeltaSizeMask = (1 << (local_Log2CtbSize - tmp_pps_diff_cu_qp_delta_depth)) - 1;
	local_cu_x0 = cu_x0;
	local_cu_x0 = cu_x0;
	xQgBase = local_cu_x0 - (local_cu_x0 & MinCuQpDeltaSizeMask);
	local_cu_y0 = cu_y0;
	local_cu_y0 = cu_y0;
	yQgBase = local_cu_y0 - (local_cu_y0 & MinCuQpDeltaSizeMask);
	local_Log2MinCbSize = Log2MinCbSize;
	x_cb = xQgBase >> local_Log2MinCbSize;
	local_Log2MinCbSize = Log2MinCbSize;
	y_cb = yQgBase >> local_Log2MinCbSize;
	local_cu_x0 = cu_x0;
	if ((local_cu_x0 & ctb_size_mask) != 0 && (xQgBase & ctb_size_mask) != 0) {
		availableA = 1;
	} else {
		availableA = 0;
	}
	local_cu_y0 = cu_y0;
	if ((local_cu_y0 & ctb_size_mask) != 0 && (yQgBase & ctb_size_mask) != 0) {
		availableB = 1;
	} else {
		availableB = 0;
	}
	qPy_local = 0;
	qPy_a = 0;
	qPy_b = 0;
	local_qPy_pred = 0;
	local_first_qp_group = first_qp_group;
	if (local_first_qp_group != 0 || xQgBase == 0 && yQgBase == 0) {
		local_IsCuQpDeltaCoded = IsCuQpDeltaCoded;
		if (local_IsCuQpDeltaCoded != 0) {
			first_qp_group = 0;
		} else {
			first_qp_group = 1;
		}
		local_slice_qp = slice_qp;
		local_qPy_pred = local_slice_qp;
	} else {
		local_qPy_pred = qPy_pred;
		local_qPy_pred = local_qPy_pred;
	}
	if (availableA == 0) {
		qPy_a = local_qPy_pred;
	} else {
		local_min_cb_width = min_cb_width;
		qPy_a = qp_y_tab[x_cb - 1 + y_cb * local_min_cb_width];
	}
	if (availableB == 0) {
		qPy_b = local_qPy_pred;
	} else {
		local_min_cb_width = min_cb_width;
		qPy_b = qp_y_tab[x_cb + (y_cb - 1) * local_min_cb_width];
	}
	qPy_local = (qPy_a + qPy_b + 1) >> 1;
	local_CuQpDelta = CuQpDelta;
	if (local_CuQpDelta != 0) {
		local_CuQpDelta = CuQpDelta;
		local_qp_bd_offset_luma = qp_bd_offset_luma;
		local_qp_bd_offset_luma = qp_bd_offset_luma;
		local_qp_bd_offset_luma = qp_bd_offset_luma;
		qp_y = (qPy_local + local_CuQpDelta + 52 + 2 * local_qp_bd_offset_luma) % (52 + local_qp_bd_offset_luma) - local_qp_bd_offset_luma;
	} else {
		qp_y = qPy_local;
	}
}
static void set_deblocking_bypass(u16 x0, u16 y0, u8 logSize) {
	u16 local_sps_id;
	i32 min_pu_width;
	u16 tmp_sps_pic_width_in_luma_samples;
	i32 x_end;
	u16 tmp_sps_pic_height_in_luma_samples;
	i32 y_end;
	i32 j;
	u8 tmp_sps_log2_min_pu_size;
	u8 tmp_sps_log2_min_pu_size0;
	i32 i;
	u8 tmp_sps_log2_min_pu_size1;
	u8 tmp_sps_log2_min_pu_size2;

	local_sps_id = sps_id;
	min_pu_width = sps_min_pu_width[local_sps_id];
	local_sps_id = sps_id;
	tmp_sps_pic_width_in_luma_samples = sps_pic_width_in_luma_samples[local_sps_id];
	x_end = HevcDecoder_Algo_Parser_min(x0 + logSize, tmp_sps_pic_width_in_luma_samples);
	local_sps_id = sps_id;
	tmp_sps_pic_height_in_luma_samples = sps_pic_height_in_luma_samples[local_sps_id];
	y_end = HevcDecoder_Algo_Parser_min(y0 + logSize, tmp_sps_pic_height_in_luma_samples);
	local_sps_id = sps_id;
	tmp_sps_log2_min_pu_size = sps_log2_min_pu_size[local_sps_id];
	j = y0 >> tmp_sps_log2_min_pu_size;
	local_sps_id = sps_id;
	tmp_sps_log2_min_pu_size0 = sps_log2_min_pu_size[local_sps_id];
	while (j <= (y_end >> tmp_sps_log2_min_pu_size0) - 1) {
		local_sps_id = sps_id;
		tmp_sps_log2_min_pu_size1 = sps_log2_min_pu_size[local_sps_id];
		i = x0 >> tmp_sps_log2_min_pu_size1;
		local_sps_id = sps_id;
		tmp_sps_log2_min_pu_size2 = sps_log2_min_pu_size[local_sps_id];
		while (i <= (x_end >> tmp_sps_log2_min_pu_size2) - 1) {
			is_pcm[i + j * min_pu_width] = 2;
			i = i + 1;
		}
		j = j + 1;
	}
}

////////////////////////////////////////////////////////////////////////////////
// Actions
static i32 isSchedulable_untagged_0() {
	i32 result;
	i32 tmp_isFifoFull;

	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	result = !tmp_isFifoFull;
	return result;
}

static void untagged_0() {

	u8 b;
	u8 local_FIFO_IDX;
	u8 fifo_idx;
	u32 local_counterByte;
	u8 local_EPR_VALUE;
	u8 local_zeroByte;
	u8 local_START_CODE_VALUE;
	u16 local_START_CODE_FLAG;
	u8 local_FIFO_CPT_BITS;
	u16 tmp_fifo;
	i32 local_DEBUG_BITSTREAM;
	u8 local_FIFO_SIZE;

	b = tokens_byte[(index_byte + (0)) % SIZE_byte];
	local_FIFO_IDX = HevcDecoder_Algo_Parser_FIFO_IDX;
	fifo_idx = fifo[local_FIFO_IDX];
	local_counterByte = counterByte;
	counterByte = local_counterByte + 1;
	local_EPR_VALUE = HevcDecoder_Algo_Parser_EPR_VALUE;
	local_zeroByte = zeroByte;
	if (b != local_EPR_VALUE || local_zeroByte != 3) {
		local_START_CODE_VALUE = HevcDecoder_Algo_Parser_START_CODE_VALUE;
		local_zeroByte = zeroByte;
		if (b == local_START_CODE_VALUE && local_zeroByte == 3) {
			local_START_CODE_FLAG = HevcDecoder_Algo_Parser_START_CODE_FLAG;
			fifo[fifo_idx] = b + local_START_CODE_FLAG;
		} else {
			fifo[fifo_idx] = b;
		}
		local_FIFO_CPT_BITS = HevcDecoder_Algo_Parser_FIFO_CPT_BITS;
		local_FIFO_CPT_BITS = HevcDecoder_Algo_Parser_FIFO_CPT_BITS;
		tmp_fifo = fifo[local_FIFO_CPT_BITS];
		fifo[local_FIFO_CPT_BITS] = tmp_fifo + 8;
		local_DEBUG_BITSTREAM = HevcDecoder_Algo_Parser_DEBUG_BITSTREAM;
		if (local_DEBUG_BITSTREAM) {
			printf("fifo[%u] := %u\n", fifo_idx, b);
		}
		local_FIFO_IDX = HevcDecoder_Algo_Parser_FIFO_IDX;
		local_FIFO_SIZE = HevcDecoder_Algo_Parser_FIFO_SIZE;
		fifo[local_FIFO_IDX] = fifo_idx + 1 & local_FIFO_SIZE - 1;
	} else {
		local_EPR_VALUE = HevcDecoder_Algo_Parser_EPR_VALUE;
		if (b == local_EPR_VALUE) {
		}
	}
	if (b == 0) {
		local_zeroByte = zeroByte;
		zeroByte = (local_zeroByte << 1) + 1 & 3;
	} else {
		zeroByte = 0;
	}

	// Update ports indexes
	index_byte += 1;

	rate_byte += 1;
}
static i32 isSchedulable_byte_align_a() {
	i32 result;
	i32 tmp_isFifoFull;

	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	result = tmp_isFifoFull;
	return result;
}

static void byte_align_a() {


	HevcDecoder_Algo_Parser_byte_align(fifo);

	// Update ports indexes

}
static i32 isSchedulable_start_code_search() {
	i32 result;
	i32 tmp_IsStartCode;
	i32 tmp_isFifoFull;

	tmp_IsStartCode = HevcDecoder_Algo_Parser_IsStartCode(fifo);
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	result = !tmp_IsStartCode && tmp_isFifoFull;
	return result;
}

static void start_code_search() {

	i32 local_DEBUG_BITSTREAM;

	HevcDecoder_Algo_Parser_flushBits(8, fifo);
	local_DEBUG_BITSTREAM = HevcDecoder_Algo_Parser_DEBUG_BITSTREAM;
	if (local_DEBUG_BITSTREAM) {
		printf("start_code.search\n");
	}

	// Update ports indexes

}
static i32 isSchedulable_start_code_done() {
	i32 result;
	i32 tmp_IsStartCode;
	i32 tmp_isFifoFull;

	tmp_IsStartCode = HevcDecoder_Algo_Parser_IsStartCode(fifo);
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	result = tmp_IsStartCode && tmp_isFifoFull;
	return result;
}

static void start_code_done() {

	i32 local_DEBUG_BITSTREAM;

	HevcDecoder_Algo_Parser_flushBits(8, fifo);
	local_DEBUG_BITSTREAM = HevcDecoder_Algo_Parser_DEBUG_BITSTREAM;
	if (local_DEBUG_BITSTREAM) {
		printf("start_code.done\n");
	}

	// Update ports indexes

}
static i32 isSchedulable_read_nal_unit_header() {
	i32 result;
	i32 tmp_isFifoFull;

	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	result = tmp_isFifoFull;
	return result;
}

static void read_nal_unit_header() {

	u32 res[1];
	i32 local_DEBUG_BITSTREAM;
	u32 tmp_res;
	u32 tmp_res0;
	u32 tmp_res1;

	local_DEBUG_BITSTREAM = HevcDecoder_Algo_Parser_DEBUG_BITSTREAM;
	if (local_DEBUG_BITSTREAM) {
		printf("=========== NAL_UNIT ===========\n");
		HevcDecoder_Algo_Parser_flushBits_name(1, fifo, "forbidden_zero_bit                      ");
		HevcDecoder_Algo_Parser_vld_u_name(6, fifo, res, "nal_unit_type                           ");
		tmp_res = res[0];
		nal_unit_type = tmp_res;
		HevcDecoder_Algo_Parser_flushBits_name(6, fifo, "nuh_reserved_zero_6bits                 ");
		HevcDecoder_Algo_Parser_vld_u_name(3, fifo, res, "nuh_temporal_id_plus1                   ");
	} else {
		HevcDecoder_Algo_Parser_flushBits(1, fifo);
		HevcDecoder_Algo_Parser_vld_u(6, fifo, res);
		tmp_res0 = res[0];
		nal_unit_type = tmp_res0;
		HevcDecoder_Algo_Parser_flushBits(6, fifo);
		HevcDecoder_Algo_Parser_vld_u(3, fifo, res);
		tmp_res1 = res[0];
		temporal_id = tmp_res1 - 1;
	}
	se_idx = 1;

	// Update ports indexes

}
static i32 isSchedulable_look_for_VPS_header() {
	i32 result;
	u8 local_nal_unit_type;
	u8 local_NAL_VPS;

	local_nal_unit_type = nal_unit_type;
	local_NAL_VPS = HevcDecoder_Algo_Parser_NAL_VPS;
	result = local_nal_unit_type == local_NAL_VPS;
	return result;
}

static void look_for_VPS_header() {

	i32 local_DEBUG_PARSER;

	local_DEBUG_PARSER = HevcDecoder_Algo_Parser_DEBUG_PARSER;
	if (local_DEBUG_PARSER) {
		printf("=========== Video Parameter Set ID:   ===========\n");
	}

	// Update ports indexes

}
static i32 isSchedulable_look_for_SEI_header() {
	i32 result;
	u8 local_nal_unit_type;
	u8 local_NAL_SEI_PREFIX;
	u8 local_NAL_SEI_SUFFIX;

	local_nal_unit_type = nal_unit_type;
	local_NAL_SEI_PREFIX = HevcDecoder_Algo_Parser_NAL_SEI_PREFIX;
	local_nal_unit_type = nal_unit_type;
	local_NAL_SEI_SUFFIX = HevcDecoder_Algo_Parser_NAL_SEI_SUFFIX;
	result = local_nal_unit_type == local_NAL_SEI_PREFIX || local_nal_unit_type == local_NAL_SEI_SUFFIX;
	return result;
}

static void look_for_SEI_header() {

	i32 local_DEBUG_PARSER;

	local_DEBUG_PARSER = HevcDecoder_Algo_Parser_DEBUG_PARSER;
	if (local_DEBUG_PARSER) {
		printf("=========== SEI message ===========\n");
	}

	// Update ports indexes

}
static i32 isSchedulable_look_for_SPS_header() {
	i32 result;
	u8 local_nal_unit_type;
	u8 local_NAL_SPS;

	local_nal_unit_type = nal_unit_type;
	local_NAL_SPS = HevcDecoder_Algo_Parser_NAL_SPS;
	result = local_nal_unit_type == local_NAL_SPS;
	return result;
}

static void look_for_SPS_header() {

	i32 local_DEBUG_PARSER;

	local_DEBUG_PARSER = HevcDecoder_Algo_Parser_DEBUG_PARSER;
	if (local_DEBUG_PARSER) {
		printf("=========== Sequence Parameter Set ID:   ===========\n");
	}

	// Update ports indexes

}
static i32 isSchedulable_look_for_PPS_header() {
	i32 result;
	u8 local_nal_unit_type;
	u8 local_NAL_PPS;

	local_nal_unit_type = nal_unit_type;
	local_NAL_PPS = HevcDecoder_Algo_Parser_NAL_PPS;
	result = local_nal_unit_type == local_NAL_PPS;
	return result;
}

static void look_for_PPS_header() {

	i32 local_DEBUG_PARSER;

	local_DEBUG_PARSER = HevcDecoder_Algo_Parser_DEBUG_PARSER;
	if (local_DEBUG_PARSER) {
		printf("=========== Picture Parameter Set ID:   ===========\n");
	}

	// Update ports indexes

}
static i32 isSchedulable_look_for_Slice_header() {
	i32 result;
	u8 local_nal_unit_type;
	u8 local_NAL_TRAIL_R;
	u8 local_NAL_TSA_N;
	u8 local_NAL_TSA_R;
	u8 local_NAL_TRAIL_N;
	u8 local_NAL_STSA_N;
	u8 local_NAL_STSA_R;
	u8 local_NAL_RADL_N;
	u8 local_NAL_RADL_R;
	u8 local_NAL_RASL_N;
	u8 local_NAL_RASL_R;
	u8 local_NAL_IDR_N_LP;
	u8 local_NAL_BLA_W_LP;
	u8 local_NAL_BLA_W_RADL;
	u8 local_NAL_BLA_N_LP;
	u8 local_NAL_IDR_W_DLP;
	u8 local_NAL_CRA_NUT;

	local_nal_unit_type = nal_unit_type;
	local_NAL_TRAIL_R = HevcDecoder_Algo_Parser_NAL_TRAIL_R;
	local_nal_unit_type = nal_unit_type;
	local_NAL_TSA_N = HevcDecoder_Algo_Parser_NAL_TSA_N;
	local_nal_unit_type = nal_unit_type;
	local_NAL_TSA_R = HevcDecoder_Algo_Parser_NAL_TSA_R;
	local_nal_unit_type = nal_unit_type;
	local_NAL_TRAIL_N = HevcDecoder_Algo_Parser_NAL_TRAIL_N;
	local_nal_unit_type = nal_unit_type;
	local_NAL_STSA_N = HevcDecoder_Algo_Parser_NAL_STSA_N;
	local_nal_unit_type = nal_unit_type;
	local_NAL_STSA_R = HevcDecoder_Algo_Parser_NAL_STSA_R;
	local_nal_unit_type = nal_unit_type;
	local_NAL_RADL_N = HevcDecoder_Algo_Parser_NAL_RADL_N;
	local_nal_unit_type = nal_unit_type;
	local_NAL_RADL_R = HevcDecoder_Algo_Parser_NAL_RADL_R;
	local_nal_unit_type = nal_unit_type;
	local_NAL_RASL_N = HevcDecoder_Algo_Parser_NAL_RASL_N;
	local_nal_unit_type = nal_unit_type;
	local_NAL_RASL_R = HevcDecoder_Algo_Parser_NAL_RASL_R;
	local_nal_unit_type = nal_unit_type;
	local_NAL_IDR_N_LP = HevcDecoder_Algo_Parser_NAL_IDR_N_LP;
	local_nal_unit_type = nal_unit_type;
	local_NAL_BLA_W_LP = HevcDecoder_Algo_Parser_NAL_BLA_W_LP;
	local_nal_unit_type = nal_unit_type;
	local_NAL_BLA_W_RADL = HevcDecoder_Algo_Parser_NAL_BLA_W_RADL;
	local_nal_unit_type = nal_unit_type;
	local_NAL_BLA_N_LP = HevcDecoder_Algo_Parser_NAL_BLA_N_LP;
	local_nal_unit_type = nal_unit_type;
	local_NAL_IDR_W_DLP = HevcDecoder_Algo_Parser_NAL_IDR_W_DLP;
	local_nal_unit_type = nal_unit_type;
	local_NAL_CRA_NUT = HevcDecoder_Algo_Parser_NAL_CRA_NUT;
	local_nal_unit_type = nal_unit_type;
	local_NAL_RASL_R = HevcDecoder_Algo_Parser_NAL_RASL_R;
	result = local_nal_unit_type == local_NAL_TRAIL_R || local_nal_unit_type == local_NAL_TSA_N || local_nal_unit_type == local_NAL_TSA_R || local_nal_unit_type == local_NAL_TRAIL_N || local_nal_unit_type == local_NAL_STSA_N || local_nal_unit_type == local_NAL_STSA_R || local_nal_unit_type == local_NAL_RADL_N || local_nal_unit_type == local_NAL_RADL_R || local_nal_unit_type == local_NAL_RASL_N || local_nal_unit_type == local_NAL_RASL_R || local_nal_unit_type == local_NAL_IDR_N_LP || local_nal_unit_type == local_NAL_BLA_W_LP || local_nal_unit_type == local_NAL_BLA_W_RADL || local_nal_unit_type == local_NAL_BLA_N_LP || local_nal_unit_type == local_NAL_IDR_W_DLP || local_nal_unit_type == local_NAL_CRA_NUT || local_nal_unit_type == local_NAL_RASL_R;
	return result;
}

static void look_for_Slice_header() {

	i32 local_DEBUG_PARSER;

	local_DEBUG_PARSER = HevcDecoder_Algo_Parser_DEBUG_PARSER;
	if (local_DEBUG_PARSER) {
		printf("=========== Slice ===========\n");
	}

	// Update ports indexes

}
static i32 isSchedulable_look_for_other_header() {
	i32 result;

	result = 1;
	return result;
}

static void look_for_other_header() {



	// Update ports indexes

}
static i32 isSchedulable_read_VPS_Header_se_idx_1() {
	i32 result;
	u16 local_se_idx;
	i32 tmp_isFifoFull;

	local_se_idx = se_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	result = local_se_idx == 1 && tmp_isFifoFull;
	return result;
}

static void read_VPS_Header_se_idx_1() {

	u32 res[1];
	u8 local_video_sequence_id;
	u32 tmp_res;
	u16 local_se_idx;

	local_video_sequence_id = video_sequence_id;
	video_sequence_id = local_video_sequence_id + 1;
	HevcDecoder_Algo_Parser_vld_u_name(4, fifo, res, "vps_video_parameter_set_id              ");
	HevcDecoder_Algo_Parser_vld_u_name(2, fifo, res, "vps_reserved_three_2bits                ");
	HevcDecoder_Algo_Parser_vld_u_name(6, fifo, res, "vps_reserved_zero_6bits                 ");
	HevcDecoder_Algo_Parser_vld_u_name(3, fifo, res, "vps_max_sub_layers_minus1               ");
	tmp_res = res[0];
	vps_max_sub_layers_minus1 = tmp_res;
	HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "vps_temporal_id_nesting_flag            ");
	HevcDecoder_Algo_Parser_vld_u_name(16, fifo, res, "vps_reserved_ffff_16bits                ");
	local_se_idx = se_idx;
	se_idx = local_se_idx + 1;

	// Update ports indexes

}
static i32 isSchedulable_read_VPS_Header_se_idx_2() {
	i32 result;
	u16 local_se_idx;
	i32 tmp_isFifoFull;

	local_se_idx = se_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	result = local_se_idx == 2 && tmp_isFifoFull;
	return result;
}

static void read_VPS_Header_se_idx_2() {

	i32 profile_present_flag;
	u32 res[1];
	i32 i;
	u16 local_se_idx;

	profile_present_flag = 1;
	if (profile_present_flag) {
		HevcDecoder_Algo_Parser_vld_u_name(2, fifo, res, "XXX_profile_space[]                     ");
		HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "XXX_tier_flag[]                         ");
		HevcDecoder_Algo_Parser_vld_u_name(5, fifo, res, "XXX_profile_idc[]                       ");
		i = 0;
		while (i <= 31) {
			HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "XXX_profile_compatibility_flag[][j]     ");
			i = i + 1;
		}
		HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "general_progressive_source_flag         ");
		HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "general_interlaced_source_flag          ");
		HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "general_non_packed_constraint_flag      ");
		HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "general_frame_only_constraint_flag      ");
	}
	local_se_idx = se_idx;
	se_idx = local_se_idx + 1;

	// Update ports indexes

}
static i32 isSchedulable_read_VPS_Header_se_idx_3() {
	i32 result;
	u16 local_se_idx;
	i32 tmp_isFifoFull;

	local_se_idx = se_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	result = local_se_idx == 3 && tmp_isFifoFull;
	return result;
}

static void read_VPS_Header_se_idx_3() {

	i32 profile_present_flag;
	u32 res[1];
	u16 local_se_idx;

	profile_present_flag = 1;
	if (profile_present_flag) {
		HevcDecoder_Algo_Parser_vld_u_name(16, fifo, res, "XXX_reserved_zero_44bits[0..15]         ");
		HevcDecoder_Algo_Parser_vld_u_name(16, fifo, res, "XXX_reserved_zero_44bits[16..31]        ");
		HevcDecoder_Algo_Parser_vld_u_name(12, fifo, res, "XXX_reserved_zero_44bits[32..43]        ");
	}
	HevcDecoder_Algo_Parser_vld_u_name(8, fifo, res, "general_level_idc                       ");
	cnt_i = 0;
	local_se_idx = se_idx;
	se_idx = local_se_idx + 1;

	// Update ports indexes

}
static i32 isSchedulable_read_VPS_Header_se_idx_4_loop1() {
	i32 result;
	u16 local_se_idx;
	i32 tmp_isFifoFull;
	u32 local_cnt_i;
	u8 local_vps_max_sub_layers_minus1;

	local_se_idx = se_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	local_cnt_i = cnt_i;
	local_vps_max_sub_layers_minus1 = vps_max_sub_layers_minus1;
	result = local_se_idx == 4 && tmp_isFifoFull && local_cnt_i < local_vps_max_sub_layers_minus1;
	return result;
}

static void read_VPS_Header_se_idx_4_loop1() {

	u32 res[1];
	i32 local_profile_present_flag;
	u32 tmp_res;
	u32 tmp_res0;
	u32 local_cnt_i;

	res[0] = 0;
	local_profile_present_flag = profile_present_flag;
	if (local_profile_present_flag) {
		HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "sub_layer_profile_present_flag[i]       ");
	}
	tmp_res = res[0];
	sub_layer_profile_present_flag = tmp_res == 1;
	HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "sub_layer_level_present_flag[i]         ");
	tmp_res0 = res[0];
	sub_layer_level_present_flag = tmp_res0 == 1;
	local_cnt_i = cnt_i;
	cnt_i = local_cnt_i + 1;

	// Update ports indexes

}
static i32 isSchedulable_read_VPS_Header_se_idx_4_insertedCond() {
	i32 result;
	u16 local_se_idx;
	i32 tmp_isFifoFull;

	local_se_idx = se_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	result = local_se_idx == 40 && tmp_isFifoFull;
	return result;
}

static void read_VPS_Header_se_idx_4_insertedCond() {

	u8 local_vps_max_sub_layers_minus1;
	i32 k;

	local_vps_max_sub_layers_minus1 = vps_max_sub_layers_minus1;
	if (local_vps_max_sub_layers_minus1 > 0) {
		local_vps_max_sub_layers_minus1 = vps_max_sub_layers_minus1;
		k = local_vps_max_sub_layers_minus1;
		while (k <= 7) {
			HevcDecoder_Algo_Parser_flushBits_name(2, fifo, "reserved_zero_2bits[ i ]                ");
			k = k + 1;
		}
	}
	se_idx = 41;

	// Update ports indexes

}
static i32 isSchedulable_read_VPS_Header_se_idx_4_loop2() {
	i32 result;
	u16 local_se_idx;
	i32 tmp_isFifoFull;
	u32 local_cnt_i;
	u8 local_vps_max_sub_layers_minus1;

	local_se_idx = se_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	local_cnt_i = cnt_i;
	local_vps_max_sub_layers_minus1 = vps_max_sub_layers_minus1;
	result = local_se_idx == 41 && tmp_isFifoFull && local_cnt_i < local_vps_max_sub_layers_minus1;
	return result;
}

static void read_VPS_Header_se_idx_4_loop2() {

	u32 res[1];
	i32 local_profile_present_flag;
	i32 local_sub_layer_profile_present_flag;
	i32 j;
	i32 local_sub_layer_level_present_flag;
	u32 local_cnt_i;

	local_profile_present_flag = profile_present_flag;
	local_sub_layer_profile_present_flag = sub_layer_profile_present_flag;
	if (local_profile_present_flag && local_sub_layer_profile_present_flag) {
		HevcDecoder_Algo_Parser_vld_u_name(2, fifo, res, "sub_layer_profile_space[i]              ");
		HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "sub_layer_tier_flag[i]                  ");
		HevcDecoder_Algo_Parser_vld_u_name(5, fifo, res, "sub_layer_profile_idc[i]                ");
		j = 0;
		while (j <= 31) {
			HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "sub_layer_profile_compatibility_flags[i][j]");
			j = j + 1;
		}
		HevcDecoder_Algo_Parser_flushBits_name(16, fifo, "sub_layer_reserved_zero_16bits[i]         ");
	}
	local_sub_layer_level_present_flag = sub_layer_level_present_flag;
	if (local_sub_layer_level_present_flag) {
		HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "sub_layer_level_idc[i]                  ");
	}
	local_cnt_i = cnt_i;
	cnt_i = local_cnt_i + 1;

	// Update ports indexes

}
static i32 isSchedulable_read_VPS_Header_se_idx_4_loop1End() {
	i32 result;
	u16 local_se_idx;
	u32 local_cnt_i;
	u8 local_vps_max_sub_layers_minus1;

	local_se_idx = se_idx;
	local_cnt_i = cnt_i;
	local_vps_max_sub_layers_minus1 = vps_max_sub_layers_minus1;
	result = local_se_idx == 4 && local_cnt_i == local_vps_max_sub_layers_minus1;
	return result;
}

static void read_VPS_Header_se_idx_4_loop1End() {


	cnt_i = 0;
	se_idx = 40;

	// Update ports indexes

}
static i32 isSchedulable_read_VPS_Header_se_idx_4_loop2End() {
	i32 result;
	u16 local_se_idx;
	u32 local_cnt_i;
	u8 local_vps_max_sub_layers_minus1;

	local_se_idx = se_idx;
	local_cnt_i = cnt_i;
	local_vps_max_sub_layers_minus1 = vps_max_sub_layers_minus1;
	result = local_se_idx == 41 && local_cnt_i == local_vps_max_sub_layers_minus1;
	return result;
}

static void read_VPS_Header_se_idx_4_loop2End() {


	se_idx = 42;
	cnt_i = 0;

	// Update ports indexes

}
static i32 isSchedulable_read_VPS_Header_se_idx_4_decodeInfoPresentFlag() {
	i32 result;
	u16 local_se_idx;
	i32 tmp_isFifoFull;

	local_se_idx = se_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	result = local_se_idx == 42 && tmp_isFifoFull;
	return result;
}

static void read_VPS_Header_se_idx_4_decodeInfoPresentFlag() {

	u32 res[1];
	u32 tmp_res;
	u8 local_vps_max_sub_layers_minus1;

	HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "vps_sub_layer_ordering_info_present_flag");
	tmp_res = res[0];
	if (tmp_res == 1) {
		cnt_i = 0;
	} else {
		local_vps_max_sub_layers_minus1 = vps_max_sub_layers_minus1;
		cnt_i = local_vps_max_sub_layers_minus1;
	}
	se_idx = 5;

	// Update ports indexes

}
static i32 isSchedulable_read_VPS_Header_se_idx_5_loop11() {
	i32 result;
	u16 local_se_idx;
	i32 tmp_isFifoFull;
	u32 local_cnt_i;
	u8 local_vps_max_sub_layers_minus1;

	local_se_idx = se_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	local_cnt_i = cnt_i;
	local_vps_max_sub_layers_minus1 = vps_max_sub_layers_minus1;
	result = local_se_idx == 5 && tmp_isFifoFull && local_cnt_i < local_vps_max_sub_layers_minus1 + 1;
	return result;
}

static void read_VPS_Header_se_idx_5_loop11() {

	i32 res[1];
	u32 local_cnt_i;

	HevcDecoder_Algo_Parser_vld_ue_name(fifo, res, "vps_max_dec_pic_buffering[i]            ");
	HevcDecoder_Algo_Parser_vld_ue_name(fifo, res, "vps_num_reorder_pics[i]                 ");
	HevcDecoder_Algo_Parser_vld_ue_name(fifo, res, "vps_max_latency_increase[i]             ");
	local_cnt_i = cnt_i;
	cnt_i = local_cnt_i + 1;

	// Update ports indexes

}
static i32 isSchedulable_read_VPS_Header_se_idx_5_loopEnd() {
	i32 result;
	u16 local_se_idx;
	i32 tmp_isFifoFull;
	u32 local_cnt_i;
	u8 local_vps_max_sub_layers_minus1;

	local_se_idx = se_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	local_cnt_i = cnt_i;
	local_vps_max_sub_layers_minus1 = vps_max_sub_layers_minus1;
	result = local_se_idx == 5 && tmp_isFifoFull && local_cnt_i == local_vps_max_sub_layers_minus1 + 1;
	return result;
}

static void read_VPS_Header_se_idx_5_loopEnd() {

	u32 res[1];
	u32 tmp_res;
	u32 tmp_res0;
	u16 local_vps_num_op_sets_minus1;

	HevcDecoder_Algo_Parser_vld_u_name(6, fifo, res, "vps_max_nuh_reserved_zero_layer_id      ");
	tmp_res = res[0];
	vps_max_nuh_reserved_zero_layer_id = tmp_res;
	HevcDecoder_Algo_Parser_vld_ue_name(fifo, res, "vps_max_op_sets_minus1                  ");
	tmp_res0 = res[0];
	vps_num_op_sets_minus1 = tmp_res0;
	cnt_i = 1;
	local_vps_num_op_sets_minus1 = vps_num_op_sets_minus1;
	cnt_i = local_vps_num_op_sets_minus1 + 1;
	se_idx = 6;

	// Update ports indexes

}
static i32 isSchedulable_read_VPS_Header_se_idx_6_loop() {
	i32 result;
	u16 local_se_idx;
	i32 tmp_isFifoFull;
	u32 local_cnt_i;
	u16 local_vps_num_op_sets_minus1;

	local_se_idx = se_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	local_cnt_i = cnt_i;
	local_vps_num_op_sets_minus1 = vps_num_op_sets_minus1;
	result = local_se_idx == 6 && tmp_isFifoFull && local_cnt_i <= local_vps_num_op_sets_minus1;
	return result;
}

static void read_VPS_Header_se_idx_6_loop() {

	u32 res[1];
	i8 i;
	u8 local_vps_max_nuh_reserved_zero_layer_id;
	u32 local_cnt_i;

	i = 0;
	local_vps_max_nuh_reserved_zero_layer_id = vps_max_nuh_reserved_zero_layer_id;
	while (i <= local_vps_max_nuh_reserved_zero_layer_id - 1) {
		HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "layer_id_included_flag[][i]             ");
		i = i + 1;
	}
	local_cnt_i = cnt_i;
	cnt_i = local_cnt_i + 1;

	// Update ports indexes

}
static i32 isSchedulable_read_VPS_Header_se_idx_6_loopEnd() {
	i32 result;
	u16 local_se_idx;
	i32 tmp_isFifoFull;
	u32 local_cnt_i;
	u16 local_vps_num_op_sets_minus1;

	local_se_idx = se_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	local_cnt_i = cnt_i;
	local_vps_num_op_sets_minus1 = vps_num_op_sets_minus1;
	result = local_se_idx == 6 && tmp_isFifoFull && local_cnt_i == local_vps_num_op_sets_minus1 + 1;
	return result;
}

static void read_VPS_Header_se_idx_6_loopEnd() {

	u32 res[1];
	u32 tmp_res;
	u8 local_vps_timing_info_present_flag;
	u16 local_se_idx;

	HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "vps_timing_info_present_flag            ");
	tmp_res = res[0];
	vps_timing_info_present_flag = tmp_res;
	local_vps_timing_info_present_flag = vps_timing_info_present_flag;
	if (local_vps_timing_info_present_flag == 1) {
		local_se_idx = se_idx;
		se_idx = local_se_idx + 1;
	} else {
		se_idx = 10;
	}

	// Update ports indexes

}
static i32 isSchedulable_read_VPS_Header_se_idx_7() {
	i32 result;
	u16 local_se_idx;
	i32 tmp_isFifoFull;

	local_se_idx = se_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	result = local_se_idx == 7 && tmp_isFifoFull;
	return result;
}

static void read_VPS_Header_se_idx_7() {

	u32 res[1];
	u16 local_se_idx;

	HevcDecoder_Algo_Parser_vld_u_name(32, fifo, res, "vps_num_units_in_tick                   ");
	HevcDecoder_Algo_Parser_vld_u_name(32, fifo, res, "vps_time_scale                          ");
	local_se_idx = se_idx;
	se_idx = local_se_idx + 1;

	// Update ports indexes

}
static i32 isSchedulable_read_VPS_Header_se_idx_8() {
	i32 result;
	u16 local_se_idx;
	i32 tmp_isFifoFull;

	local_se_idx = se_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	result = local_se_idx == 8 && tmp_isFifoFull;
	return result;
}

static void read_VPS_Header_se_idx_8() {

	u32 res[1];
	u32 tmp_res;
	u32 tmp_res0;
	u16 local_se_idx;

	HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "vps_poc_proportional_to_timing_flag     ");
	tmp_res = res[0];
	if (tmp_res == 1) {
		HevcDecoder_Algo_Parser_vld_ue_name(fifo, res, "vps_num_ticks_poc_diff_one_minus1       ");
	}
	HevcDecoder_Algo_Parser_vld_ue_name(fifo, res, "vps_num_hrd_parameters                  ");
	tmp_res0 = res[0];
	vps_num_hrd_parameters = tmp_res0;
	local_se_idx = se_idx;
	se_idx = local_se_idx + 1;

	// Update ports indexes

}
static i32 isSchedulable_read_VPS_Header_se_idx_9_loop() {
	i32 result;
	u16 local_se_idx;
	i32 tmp_isFifoFull;
	u32 local_cnt_i;
	u16 local_vps_num_hrd_parameters;

	local_se_idx = se_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	local_cnt_i = cnt_i;
	local_vps_num_hrd_parameters = vps_num_hrd_parameters;
	result = local_se_idx == 9 && tmp_isFifoFull && local_cnt_i < local_vps_num_hrd_parameters;
	return result;
}

static void read_VPS_Header_se_idx_9_loop() {

	u32 res[1];
	u8 cprms_present_flag;
	u32 local_cnt_i;

	cprms_present_flag = 0;
	HevcDecoder_Algo_Parser_vld_ue_name(fifo, res, "hrd_op_set_idx[i]                       ");
	local_cnt_i = cnt_i;
	if (local_cnt_i > 0) {
		HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "cprms_present_flag[i]                   ");
		cprms_present_flag = res[0];
	}
	if (cprms_present_flag == 1) {
		printf("not support for vps_num_hrd_parameters != 0\n");
	}
	local_cnt_i = cnt_i;
	cnt_i = local_cnt_i + 1;

	// Update ports indexes

}
static i32 isSchedulable_read_VPS_Header_se_idx_9_loopEnd() {
	i32 result;
	u16 local_se_idx;
	u32 local_cnt_i;
	u16 local_vps_num_hrd_parameters;

	local_se_idx = se_idx;
	local_cnt_i = cnt_i;
	local_vps_num_hrd_parameters = vps_num_hrd_parameters;
	result = local_se_idx == 9 && local_cnt_i == local_vps_num_hrd_parameters;
	return result;
}

static void read_VPS_Header_se_idx_9_loopEnd() {

	u16 local_se_idx;

	local_se_idx = se_idx;
	se_idx = local_se_idx + 1;

	// Update ports indexes

}
static i32 isSchedulable_read_VPS_Header_done() {
	i32 result;
	u16 local_se_idx;
	i32 tmp_isFifoFull;

	local_se_idx = se_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	result = local_se_idx == 10 && tmp_isFifoFull;
	return result;
}

static void read_VPS_Header_done() {

	u32 res[1];
	u32 tmp_res;

	HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "vps_extension_flag                      ");
	tmp_res = res[0];
	if (tmp_res == 1) {
		printf("not support for vps_extension_flag != 0\n");
	}

	// Update ports indexes

}
static i32 isSchedulable_read_SEI_Header_init() {
	i32 result;
	u16 local_se_idx;
	i32 tmp_isFifoFull;

	local_se_idx = se_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	result = local_se_idx == 1 && tmp_isFifoFull;
	return result;
}

static void read_SEI_Header_init() {

	u16 local_se_idx;

	sei_payloadType = 0;
	sei_payloadSize = 0;
	sei_payloadPosition = 0;
	local_se_idx = se_idx;
	se_idx = local_se_idx + 1;
	sei_idx = 1;

	// Update ports indexes

}
static i32 isSchedulable_read_SEI_Header_payload_type() {
	i32 result;
	u16 local_se_idx;
	i32 tmp_isFifoFull;

	local_se_idx = se_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	result = local_se_idx == 2 && tmp_isFifoFull;
	return result;
}

static void read_SEI_Header_payload_type() {

	u32 res[1];
	u16 local_sei_payloadType;
	u32 tmp_res;
	u32 tmp_res0;
	u16 local_se_idx;

	HevcDecoder_Algo_Parser_vld_u_name(8, fifo, res, "payload_type                            ");
	local_sei_payloadType = sei_payloadType;
	tmp_res = res[0];
	sei_payloadType = local_sei_payloadType + tmp_res;
	tmp_res0 = res[0];
	if (tmp_res0 != 255) {
		local_se_idx = se_idx;
		se_idx = local_se_idx + 1;
	} else {
		se_idx = 6;
	}

	// Update ports indexes

}
static i32 isSchedulable_read_SEI_Header_payload_size() {
	i32 result;
	u16 local_se_idx;
	i32 tmp_isFifoFull;

	local_se_idx = se_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	result = local_se_idx == 3 && tmp_isFifoFull;
	return result;
}

static void read_SEI_Header_payload_size() {

	u32 res[1];
	u16 local_sei_payloadSize;
	u32 tmp_res;
	u32 tmp_res0;
	u16 local_se_idx;

	HevcDecoder_Algo_Parser_vld_u_name(8, fifo, res, "payload_size                            ");
	local_sei_payloadSize = sei_payloadSize;
	tmp_res = res[0];
	sei_payloadSize = local_sei_payloadSize + tmp_res;
	tmp_res0 = res[0];
	if (tmp_res0 != 255) {
		local_se_idx = se_idx;
		se_idx = local_se_idx + 1;
	} else {
		se_idx = 6;
	}

	// Update ports indexes

}
static i32 isSchedulable_read_SEI_Header_skipSEI() {
	i32 result;
	u16 local_se_idx;
	i32 tmp_isFifoFull;
	u8 local_sei_idx;
	u16 local_sei_payloadType;

	local_se_idx = se_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	local_sei_idx = sei_idx;
	local_sei_payloadType = sei_payloadType;
	result = local_se_idx == 4 && tmp_isFifoFull && (local_sei_idx == 1 && local_sei_payloadType != 132);
	return result;
}

static void read_SEI_Header_skipSEI() {


	se_idx = 6;

	// Update ports indexes

}
static i32 isSchedulable_read_SEI_Header_decoded_picture_hash_init() {
	i32 result;
	u16 local_se_idx;
	i32 tmp_isFifoFull;
	u8 local_sei_idx;
	u16 local_sei_payloadType;

	local_se_idx = se_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	local_sei_idx = sei_idx;
	local_sei_payloadType = sei_payloadType;
	result = local_se_idx == 4 && tmp_isFifoFull && (local_sei_idx == 1 && local_sei_payloadType == 132);
	return result;
}

static void read_SEI_Header_decoded_picture_hash_init() {

	u32 res[1];
	i32 local_DEBUG_PARSER;
	u16 local_sei_payloadPosition;
	u32 tmp_res;
	u8 local_sei_idx;

	local_DEBUG_PARSER = HevcDecoder_Algo_Parser_DEBUG_PARSER;
	if (local_DEBUG_PARSER) {
		printf("=========== Decoded picture hash SEI message ===========\n");
	}
	HevcDecoder_Algo_Parser_vld_u_name(8, fifo, res, "hash_type                               ");
	local_sei_payloadPosition = sei_payloadPosition;
	sei_payloadPosition = local_sei_payloadPosition + 8;
	tmp_res = res[0];
	sei_hash_type = tmp_res;
	sei_cIdx = 0;
	sei_i = 0;
	local_sei_idx = sei_idx;
	sei_idx = local_sei_idx + 1;

	// Update ports indexes

}
static i32 isSchedulable_read_SEI_Header_decoded_picture_hash_loop() {
	i32 result;
	u16 local_se_idx;
	i32 tmp_isFifoFull;
	u8 local_sei_idx;
	u16 local_sei_payloadType;
	u8 local_sei_cIdx;
	u8 local_sei_i;
	u8 local_sei_hash_type;

	local_se_idx = se_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	local_sei_idx = sei_idx;
	local_sei_payloadType = sei_payloadType;
	local_sei_cIdx = sei_cIdx;
	local_sei_i = sei_i;
	local_sei_hash_type = sei_hash_type;
	result = local_se_idx == 4 && tmp_isFifoFull && (local_sei_idx == 2 && local_sei_payloadType == 132) && local_sei_cIdx < 3 && local_sei_i < 16 && local_sei_hash_type == 0;
	return result;
}

static void read_SEI_Header_decoded_picture_hash_loop() {

	u32 res[1];
	u16 local_sei_payloadPosition;
	u8 local_sei_i;
	u8 local_sei_cIdx;
	u16 local_se_idx;
	u32 tmp_res;

	HevcDecoder_Algo_Parser_vld_u_name(8, fifo, res, "picture_md5                             ");
	local_sei_payloadPosition = sei_payloadPosition;
	sei_payloadPosition = local_sei_payloadPosition + 8;
	local_sei_i = sei_i;
	sei_i = local_sei_i + 1;
	local_sei_i = sei_i;
	if (local_sei_i == 16) {
		sei_i = 0;
		local_sei_cIdx = sei_cIdx;
		sei_cIdx = local_sei_cIdx + 1;
		local_sei_cIdx = sei_cIdx;
		if (local_sei_cIdx == 3) {
			local_se_idx = se_idx;
			se_idx = local_se_idx + 1;
		}
	}
	tmp_res = res[0];
	tokens_SEI_MD5[(index_SEI_MD5 + (0)) % SIZE_SEI_MD5] = tmp_res;

	// Update ports indexes
	index_SEI_MD5 += 1;

}
static i32 isSchedulable_read_SEI_Header_decoded_picture_hash_skip() {
	i32 result;
	u16 local_se_idx;
	i32 tmp_isFifoFull;
	u8 local_sei_idx;
	u16 local_sei_payloadType;
	u8 local_sei_cIdx;
	u8 local_sei_i;
	u8 local_sei_hash_type;

	local_se_idx = se_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	local_sei_idx = sei_idx;
	local_sei_payloadType = sei_payloadType;
	local_sei_cIdx = sei_cIdx;
	local_sei_i = sei_i;
	local_sei_hash_type = sei_hash_type;
	result = local_se_idx == 4 && tmp_isFifoFull && (local_sei_idx == 2 && local_sei_payloadType == 132) && local_sei_cIdx < 3 && local_sei_i < 16 && local_sei_hash_type != 0;
	return result;
}

static void read_SEI_Header_decoded_picture_hash_skip() {

	u32 res[1];
	u8 local_sei_hash_type;
	u16 local_sei_payloadPosition;
	u8 local_sei_i;
	u8 local_sei_cIdx;
	u16 local_se_idx;

	printf("no support for crc or checksum ! (support only md5)\n");
	local_sei_hash_type = sei_hash_type;
	if (local_sei_hash_type == 1) {
		HevcDecoder_Algo_Parser_vld_u_name(16, fifo, res, "picture_crc                             ");
		local_sei_payloadPosition = sei_payloadPosition;
		sei_payloadPosition = local_sei_payloadPosition + 16;
		sei_i = 16;
	} else {
		local_sei_hash_type = sei_hash_type;
		if (local_sei_hash_type == 2) {
			HevcDecoder_Algo_Parser_vld_u_name(32, fifo, res, "picture_checksum                        ");
			local_sei_payloadPosition = sei_payloadPosition;
			sei_payloadPosition = local_sei_payloadPosition + 32;
			sei_i = 16;
		}
	}
	local_sei_i = sei_i;
	if (local_sei_i == 16) {
		sei_i = 0;
		local_sei_cIdx = sei_cIdx;
		sei_cIdx = local_sei_cIdx + 1;
		local_sei_cIdx = sei_cIdx;
		if (local_sei_cIdx == 3) {
			local_se_idx = se_idx;
			se_idx = local_se_idx + 1;
		}
	}

	// Update ports indexes

}
static i32 isSchedulable_read_SEI_Header_sei_payload_end() {
	i32 result;
	u16 local_se_idx;
	i32 tmp_isFifoFull;

	local_se_idx = se_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	result = local_se_idx == 5 && tmp_isFifoFull;
	return result;
}

static void read_SEI_Header_sei_payload_end() {

	u32 res[1];
	i32 tmp_isByteAlign;
	u16 local_sei_payloadPosition;
	u16 local_sei_payloadSize;
	i32 tmp_isByteAlign0;
	u16 local_se_idx;

	tmp_isByteAlign = HevcDecoder_Algo_Parser_isByteAlign(fifo);
	local_sei_payloadPosition = sei_payloadPosition;
	local_sei_payloadSize = sei_payloadSize;
	if (!(tmp_isByteAlign && local_sei_payloadPosition == local_sei_payloadSize << 3)) {
		HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "bit_equal_to_one                        ");
		tmp_isByteAlign0 = HevcDecoder_Algo_Parser_isByteAlign(fifo);
		while (!tmp_isByteAlign0) {
			HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "bit_equal_to_zero                       ");
			tmp_isByteAlign0 = HevcDecoder_Algo_Parser_isByteAlign(fifo);
		}
	}
	local_se_idx = se_idx;
	se_idx = local_se_idx + 1;

	// Update ports indexes

}
static i32 isSchedulable_read_SEI_Header_done() {
	i32 result;
	u16 local_se_idx;
	i32 tmp_isFifoFull;

	local_se_idx = se_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	result = local_se_idx == 6 && tmp_isFifoFull;
	return result;
}

static void read_SEI_Header_done() {

	u32 res[1];

	HevcDecoder_Algo_Parser_vld_u_name(8, fifo, res, "rbsp_trailing_bits");

	// Update ports indexes

}
static i32 isSchedulable_read_SPS_Header_se_idx_1() {
	i32 result;
	u16 local_se_idx;
	i32 tmp_isFifoFull;

	local_se_idx = se_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	result = local_se_idx == 1 && tmp_isFifoFull;
	return result;
}

static void read_SPS_Header_se_idx_1() {

	u32 res[1];
	u16 local_sps_id;
	u32 tmp_res;

	HevcDecoder_Algo_Parser_vld_u_name(4, fifo, res, "sps_video_parameter_set_id              ");
	HevcDecoder_Algo_Parser_vld_u_name(3, fifo, res, "sps_max_sub_layers_minus1               ");
	local_sps_id = sps_id;
	tmp_res = res[0];
	sps_max_sub_layers_minus1[local_sps_id] = tmp_res;
	HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "sps_temporal_id_nesting_flag            ");
	se_idx = 20;

	// Update ports indexes

}
static i32 isSchedulable_read_SPS_Header_se_idx_20() {
	i32 result;
	u16 local_se_idx;
	i32 tmp_isFifoFull;

	local_se_idx = se_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	result = local_se_idx == 20 && tmp_isFifoFull;
	return result;
}

static void read_SPS_Header_se_idx_20() {

	i32 profile_present_flag;
	u32 res[1];
	i32 i;
	u16 local_se_idx;

	profile_present_flag = 1;
	if (profile_present_flag) {
		HevcDecoder_Algo_Parser_vld_u_name(2, fifo, res, "XXX_profile_space[]                     ");
		HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "XXX_tier_flag[]                         ");
		HevcDecoder_Algo_Parser_vld_u_name(5, fifo, res, "XXX_profile_idc[]                       ");
		i = 0;
		while (i <= 31) {
			HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "XXX_profile_compatibility_flag[][j]     ");
			i = i + 1;
		}
		HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "general_progressive_source_flag         ");
		HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "general_interlaced_source_flag          ");
		HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "general_non_packed_constraint_flag      ");
		HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "general_frame_only_constraint_flag      ");
	}
	local_se_idx = se_idx;
	se_idx = local_se_idx + 1;

	// Update ports indexes

}
static i32 isSchedulable_read_SPS_Header_se_idx_21() {
	i32 result;
	u16 local_se_idx;
	i32 tmp_isFifoFull;

	local_se_idx = se_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	result = local_se_idx == 21 && tmp_isFifoFull;
	return result;
}

static void read_SPS_Header_se_idx_21() {

	i32 profile_present_flag;
	u32 res[1];
	u16 local_se_idx;

	profile_present_flag = 1;
	if (profile_present_flag) {
		HevcDecoder_Algo_Parser_vld_u_name(16, fifo, res, "XXX_reserved_zero_44bits[0..15]         ");
		HevcDecoder_Algo_Parser_vld_u_name(16, fifo, res, "XXX_reserved_zero_44bits[16..31]        ");
		HevcDecoder_Algo_Parser_vld_u_name(12, fifo, res, "XXX_reserved_zero_44bits[32..43]        ");
	}
	HevcDecoder_Algo_Parser_vld_u_name(8, fifo, res, "general_level_idc                       ");
	cnt_i = 0;
	local_se_idx = se_idx;
	se_idx = local_se_idx + 1;

	// Update ports indexes

}
static i32 isSchedulable_read_SPS_Header_se_idx_22_loop1() {
	i32 result;
	u16 local_se_idx;
	i32 tmp_isFifoFull;
	u32 local_cnt_i;
	u16 local_sps_id;
	u8 tmp_sps_max_sub_layers_minus1;

	local_se_idx = se_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	local_cnt_i = cnt_i;
	local_sps_id = sps_id;
	tmp_sps_max_sub_layers_minus1 = sps_max_sub_layers_minus1[local_sps_id];
	result = local_se_idx == 22 && tmp_isFifoFull && local_cnt_i < tmp_sps_max_sub_layers_minus1;
	return result;
}

static void read_SPS_Header_se_idx_22_loop1() {

	u32 res[1];
	i32 local_sps_profile_present_flag;
	u32 tmp_res;
	u32 tmp_res0;
	u32 local_cnt_i;

	res[0] = 0;
	local_sps_profile_present_flag = sps_profile_present_flag;
	if (local_sps_profile_present_flag) {
		HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "sub_layer_profile_present_flag[i]       ");
	}
	tmp_res = res[0];
	sps_sub_layer_profile_present_flag = tmp_res == 1;
	HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "sub_layer_level_present_flag[i]         ");
	tmp_res0 = res[0];
	sps_sub_layer_level_present_flag = tmp_res0 == 1;
	local_cnt_i = cnt_i;
	cnt_i = local_cnt_i + 1;

	// Update ports indexes

}
static i32 isSchedulable_read_SPS_Header_se_idx_22_loopEnd1() {
	i32 result;
	u16 local_se_idx;
	i32 tmp_isFifoFull;
	u32 local_cnt_i;
	u16 local_sps_id;
	u8 tmp_sps_max_sub_layers_minus1;

	local_se_idx = se_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	local_cnt_i = cnt_i;
	local_sps_id = sps_id;
	tmp_sps_max_sub_layers_minus1 = sps_max_sub_layers_minus1[local_sps_id];
	result = local_se_idx == 22 && tmp_isFifoFull && local_cnt_i == tmp_sps_max_sub_layers_minus1;
	return result;
}

static void read_SPS_Header_se_idx_22_loopEnd1() {


	cnt_i = 0;
	se_idx = 221;

	// Update ports indexes

}
static i32 isSchedulable_read_SPS_Header_se_idx_22_indertedCond() {
	i32 result;
	u16 local_se_idx;
	i32 tmp_isFifoFull;

	local_se_idx = se_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	result = local_se_idx == 221 && tmp_isFifoFull;
	return result;
}

static void read_SPS_Header_se_idx_22_indertedCond() {

	u16 local_sps_id;
	u8 tmp_sps_max_sub_layers_minus1;
	i32 i;

	local_sps_id = sps_id;
	tmp_sps_max_sub_layers_minus1 = sps_max_sub_layers_minus1[local_sps_id];
	if (tmp_sps_max_sub_layers_minus1 > 0) {
		local_sps_id = sps_id;
		i = sps_max_sub_layers_minus1[local_sps_id];
		while (i <= 7) {
			HevcDecoder_Algo_Parser_flushBits_name(2, fifo, "reserved_zero_2bits[i]                    ");
			i = i + 1;
		}
	}
	se_idx = 222;

	// Update ports indexes

}
static i32 isSchedulable_read_SPS_Header_se_idx_22_loop2() {
	i32 result;
	u16 local_se_idx;
	i32 tmp_isFifoFull;
	u32 local_cnt_i;
	u16 local_sps_id;
	u8 tmp_sps_max_sub_layers_minus1;

	local_se_idx = se_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	local_cnt_i = cnt_i;
	local_sps_id = sps_id;
	tmp_sps_max_sub_layers_minus1 = sps_max_sub_layers_minus1[local_sps_id];
	result = local_se_idx == 222 && tmp_isFifoFull && local_cnt_i < tmp_sps_max_sub_layers_minus1;
	return result;
}

static void read_SPS_Header_se_idx_22_loop2() {

	u32 res[1];
	i32 local_sps_profile_present_flag;
	i32 local_sps_sub_layer_profile_present_flag;
	i32 j;
	i32 local_sps_sub_layer_level_present_flag;
	u32 local_cnt_i;

	local_sps_profile_present_flag = sps_profile_present_flag;
	local_sps_sub_layer_profile_present_flag = sps_sub_layer_profile_present_flag;
	if (local_sps_profile_present_flag && local_sps_sub_layer_profile_present_flag) {
		HevcDecoder_Algo_Parser_vld_u_name(2, fifo, res, "sub_layer_profile_space[i]              ");
		HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "sub_layer_tier_flag[i]                  ");
		HevcDecoder_Algo_Parser_vld_u_name(5, fifo, res, "sub_layer_profile_idc[i]                ");
		j = 0;
		while (j <= 31) {
			HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "sub_layer_profile_compatibility_flags[i][j]");
			j = j + 1;
		}
		HevcDecoder_Algo_Parser_flushBits_name(16, fifo, "sub_layer_reserved_zero_16bits[i]         ");
	}
	local_sps_sub_layer_level_present_flag = sps_sub_layer_level_present_flag;
	if (local_sps_sub_layer_level_present_flag) {
		HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "sub_layer_level_idc[i]                  ");
	}
	local_cnt_i = cnt_i;
	cnt_i = local_cnt_i + 1;

	// Update ports indexes

}
static i32 isSchedulable_read_SPS_Header_se_idx_22_loopEnd() {
	i32 result;
	u16 local_se_idx;
	i32 tmp_isFifoFull;
	u32 local_cnt_i;
	u16 local_sps_id;
	u8 tmp_sps_max_sub_layers_minus1;

	local_se_idx = se_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	local_cnt_i = cnt_i;
	local_sps_id = sps_id;
	tmp_sps_max_sub_layers_minus1 = sps_max_sub_layers_minus1[local_sps_id];
	result = local_se_idx == 222 && tmp_isFifoFull && local_cnt_i == tmp_sps_max_sub_layers_minus1;
	return result;
}

static void read_SPS_Header_se_idx_22_loopEnd() {


	se_idx = 11;

	// Update ports indexes

}
static i32 isSchedulable_read_SPS_Header_se_idx_1_1() {
	i32 result;
	u16 local_se_idx;
	i32 tmp_isFifoFull;

	local_se_idx = se_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	result = local_se_idx == 11 && tmp_isFifoFull;
	return result;
}

static void read_SPS_Header_se_idx_1_1() {

	u32 res[1];
	u32 tmp_res;
	u16 local_sps_id;
	u32 tmp_res0;
	u32 tmp_res1;
	u32 tmp_res2;
	u32 tmp_res3;
	u32 tmp_res4;

	HevcDecoder_Algo_Parser_vld_ue_name(fifo, res, "sps_seq_parameter_set_id                ");
	tmp_res = res[0];
	sps_id = tmp_res;
	HevcDecoder_Algo_Parser_vld_ue_name(fifo, res, "chroma_format_idc                       ");
	local_sps_id = sps_id;
	tmp_res0 = res[0];
	sps_chroma_format_idc[local_sps_id] = tmp_res0;
	tmp_res1 = res[0];
	if (tmp_res1 == 3) {
		HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "separate_colour_plane_flag              ");
		local_sps_id = sps_id;
		tmp_res2 = res[0];
		sps_separate_colour_plane_flag[local_sps_id] = tmp_res2;
	}
	HevcDecoder_Algo_Parser_vld_ue_name(fifo, res, "pic_width_in_luma_samples               ");
	local_sps_id = sps_id;
	tmp_res3 = res[0];
	sps_pic_width_in_luma_samples[local_sps_id] = tmp_res3;
	HevcDecoder_Algo_Parser_vld_ue_name(fifo, res, "pic_height_in_luma_samples              ");
	local_sps_id = sps_id;
	tmp_res4 = res[0];
	sps_pic_height_in_luma_samples[local_sps_id] = tmp_res4;
	se_idx = 2;

	// Update ports indexes

}
static i32 isSchedulable_read_SPS_Header_se_idx_2() {
	i32 result;
	u16 local_se_idx;
	i32 tmp_isFifoFull;

	local_se_idx = se_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	result = local_se_idx == 2 && tmp_isFifoFull;
	return result;
}

static void read_SPS_Header_se_idx_2() {

	u32 res[1];
	u8 conformance_window_flag;
	u16 local_sps_id;
	u32 tmp_res;
	u32 tmp_res0;
	u32 tmp_res1;
	u8 tmp_sps_log2_max_pic_order_cnt_lsb_minus4;
	u32 tmp_res2;
	u8 tmp_sps_max_sub_layers_minus1;
	u16 local_se_idx;

	HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "conformance_window_flag                 ");
	conformance_window_flag = res[0];
	if (conformance_window_flag == 1) {
		HevcDecoder_Algo_Parser_vld_ue_name(fifo, res, "conf_win_left_offset                    ");
		HevcDecoder_Algo_Parser_vld_ue_name(fifo, res, "conf_win_right_offset                   ");
		HevcDecoder_Algo_Parser_vld_ue_name(fifo, res, "conf_win_top_offset                     ");
		HevcDecoder_Algo_Parser_vld_ue_name(fifo, res, "conf_win_bottom_offset                  ");
	}
	HevcDecoder_Algo_Parser_vld_ue_name(fifo, res, "sps_bit_depth_luma_minus8                   ");
	local_sps_id = sps_id;
	tmp_res = res[0];
	sps_bit_depth_luma_minus8[local_sps_id] = tmp_res;
	HevcDecoder_Algo_Parser_vld_ue_name(fifo, res, "sps_bit_depth_chroma_minus8                 ");
	local_sps_id = sps_id;
	tmp_res0 = res[0];
	sps_bit_depth_chroma_minus8[local_sps_id] = tmp_res0;
	HevcDecoder_Algo_Parser_vld_ue_name(fifo, res, "log2_max_pic_order_cnt_lsb_minus4       ");
	local_sps_id = sps_id;
	tmp_res1 = res[0];
	sps_log2_max_pic_order_cnt_lsb_minus4[local_sps_id] = tmp_res1;
	local_sps_id = sps_id;
	local_sps_id = sps_id;
	tmp_sps_log2_max_pic_order_cnt_lsb_minus4 = sps_log2_max_pic_order_cnt_lsb_minus4[local_sps_id];
	max_poc_lsb[local_sps_id] = 1 << (tmp_sps_log2_max_pic_order_cnt_lsb_minus4 + 4);
	HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "sps_sub_layer_ordering_info_present_flag");
	tmp_res2 = res[0];
	if (tmp_res2 == 1) {
		cnt_i = 0;
	} else {
		local_sps_id = sps_id;
		tmp_sps_max_sub_layers_minus1 = sps_max_sub_layers_minus1[local_sps_id];
		cnt_i = tmp_sps_max_sub_layers_minus1;
	}
	local_se_idx = se_idx;
	se_idx = local_se_idx + 1;

	// Update ports indexes

}
static i32 isSchedulable_read_SPS_Header_se_idx_3_loop() {
	i32 result;
	u16 local_se_idx;
	i32 tmp_isFifoFull;
	u32 local_cnt_i;
	u16 local_sps_id;
	u8 tmp_sps_max_sub_layers_minus1;

	local_se_idx = se_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	local_cnt_i = cnt_i;
	local_sps_id = sps_id;
	tmp_sps_max_sub_layers_minus1 = sps_max_sub_layers_minus1[local_sps_id];
	result = local_se_idx == 3 && tmp_isFifoFull && local_cnt_i <= tmp_sps_max_sub_layers_minus1;
	return result;
}

static void read_SPS_Header_se_idx_3_loop() {

	u32 res[1];
	u16 local_sps_id;
	u32 tmp_res;
	u32 local_cnt_i;

	HevcDecoder_Algo_Parser_vld_ue_name(fifo, res, "sps_max_dec_pic_buffering               ");
	HevcDecoder_Algo_Parser_vld_ue_name(fifo, res, "sps_num_reorder_pics                    ");
	local_sps_id = sps_id;
	tmp_res = res[0];
	sps_num_reorder_pics[local_sps_id] = tmp_res;
	HevcDecoder_Algo_Parser_vld_ue_name(fifo, res, "sps_max_latency_increase                ");
	local_cnt_i = cnt_i;
	cnt_i = local_cnt_i + 1;

	// Update ports indexes

}
static i32 isSchedulable_read_SPS_Header_se_idx_3_loopEnd() {
	i32 result;
	u16 local_se_idx;
	u32 local_cnt_i;
	u16 local_sps_id;
	u8 tmp_sps_max_sub_layers_minus1;

	local_se_idx = se_idx;
	local_cnt_i = cnt_i;
	local_sps_id = sps_id;
	tmp_sps_max_sub_layers_minus1 = sps_max_sub_layers_minus1[local_sps_id];
	result = local_se_idx == 3 && local_cnt_i == tmp_sps_max_sub_layers_minus1 + 1;
	return result;
}

static void read_SPS_Header_se_idx_3_loopEnd() {

	u16 local_se_idx;

	local_se_idx = se_idx;
	se_idx = local_se_idx + 1;

	// Update ports indexes

}
static i32 isSchedulable_read_SPS_Header_se_idx_4() {
	i32 result;
	u16 local_se_idx;
	i32 tmp_isFifoFull;

	local_se_idx = se_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	result = local_se_idx == 4 && tmp_isFifoFull;
	return result;
}

static void read_SPS_Header_se_idx_4() {

	u32 res[1];
	u16 local_sps_id;
	u32 tmp_res;
	u32 tmp_res0;
	u32 tmp_res1;
	u32 tmp_res2;
	u8 local_Log2MinCbSize;
	u8 tmp_sps_log2_diff_max_min_coding_block_size;
	u16 tmp_sps_maxCUWidth;
	u8 tmp_sps_log2_diff_max_min_coding_block_size0;
	u8 tmp_sps_log2_min_transform_block_size;
	u8 tmp_sps_log2_diff_max_min_coding_block_size1;
	u16 tmp_sps_addCUDepth;
	u8 tmp_sps_log2_min_coding_block_size;
	u16 tmp_sps_pic_width_in_luma_samples;
	u8 tmp_sps_log2_min_pu_size;
	u16 local_se_idx;

	HevcDecoder_Algo_Parser_vld_ue_name(fifo, res, "log2_min_coding_block_size_minus3       ");
	local_sps_id = sps_id;
	tmp_res = res[0];
	sps_log2_min_coding_block_size[local_sps_id] = tmp_res + 3;
	HevcDecoder_Algo_Parser_vld_ue_name(fifo, res, "log2_diff_max_min_coding_block_size     ");
	local_sps_id = sps_id;
	tmp_res0 = res[0];
	sps_log2_diff_max_min_coding_block_size[local_sps_id] = tmp_res0;
	HevcDecoder_Algo_Parser_vld_ue_name(fifo, res, "log2_min_transform_block_size_minus2    ");
	local_sps_id = sps_id;
	tmp_res1 = res[0];
	sps_log2_min_transform_block_size[local_sps_id] = tmp_res1 + 2;
	HevcDecoder_Algo_Parser_vld_ue_name(fifo, res, "log2_diff_max_min_transform_block_size  ");
	local_sps_id = sps_id;
	tmp_res2 = res[0];
	sps_log2_diff_max_min_transform_block_size[local_sps_id] = tmp_res2;
	local_sps_id = sps_id;
	local_Log2MinCbSize = Log2MinCbSize;
	local_sps_id = sps_id;
	tmp_sps_log2_diff_max_min_coding_block_size = sps_log2_diff_max_min_coding_block_size[local_sps_id];
	sps_maxCUWidth[local_sps_id] = 1 << (local_Log2MinCbSize + tmp_sps_log2_diff_max_min_coding_block_size);
	local_sps_id = sps_id;
	sps_addCUDepth[local_sps_id] = 0;
	local_sps_id = sps_id;
	tmp_sps_maxCUWidth = sps_maxCUWidth[local_sps_id];
	local_sps_id = sps_id;
	tmp_sps_log2_diff_max_min_coding_block_size0 = sps_log2_diff_max_min_coding_block_size[local_sps_id];
	local_sps_id = sps_id;
	tmp_sps_log2_min_transform_block_size = sps_log2_min_transform_block_size[local_sps_id];
	local_sps_id = sps_id;
	tmp_sps_log2_diff_max_min_coding_block_size1 = sps_log2_diff_max_min_coding_block_size[local_sps_id];
	while (tmp_sps_maxCUWidth >> tmp_sps_log2_diff_max_min_coding_block_size0 > 1 << (tmp_sps_log2_min_transform_block_size + tmp_sps_log2_diff_max_min_coding_block_size1)) {
		local_sps_id = sps_id;
		local_sps_id = sps_id;
		tmp_sps_addCUDepth = sps_addCUDepth[local_sps_id];
		sps_addCUDepth[local_sps_id] = tmp_sps_addCUDepth + 1;
		local_sps_id = sps_id;
		tmp_sps_maxCUWidth = sps_maxCUWidth[local_sps_id];
		local_sps_id = sps_id;
		tmp_sps_log2_diff_max_min_coding_block_size0 = sps_log2_diff_max_min_coding_block_size[local_sps_id];
		local_sps_id = sps_id;
		tmp_sps_log2_min_transform_block_size = sps_log2_min_transform_block_size[local_sps_id];
		local_sps_id = sps_id;
		tmp_sps_log2_diff_max_min_coding_block_size1 = sps_log2_diff_max_min_coding_block_size[local_sps_id];
	}
	local_sps_id = sps_id;
	local_sps_id = sps_id;
	tmp_sps_log2_min_coding_block_size = sps_log2_min_coding_block_size[local_sps_id];
	sps_log2_min_pu_size[local_sps_id] = tmp_sps_log2_min_coding_block_size - 1;
	local_sps_id = sps_id;
	local_sps_id = sps_id;
	tmp_sps_pic_width_in_luma_samples = sps_pic_width_in_luma_samples[local_sps_id];
	local_sps_id = sps_id;
	tmp_sps_log2_min_pu_size = sps_log2_min_pu_size[local_sps_id];
	sps_min_pu_width[local_sps_id] = tmp_sps_pic_width_in_luma_samples >> tmp_sps_log2_min_pu_size;
	local_se_idx = se_idx;
	se_idx = local_se_idx + 1;

	// Update ports indexes

}
static i32 isSchedulable_read_SPS_Header_se_idx_5() {
	i32 result;
	u16 local_se_idx;
	i32 tmp_isFifoFull;

	local_se_idx = se_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	result = local_se_idx == 5 && tmp_isFifoFull;
	return result;
}

static void read_SPS_Header_se_idx_5() {

	u32 res[1];
	u16 local_sps_id;
	u32 tmp_res;
	u32 tmp_res0;
	u32 tmp_res1;
	u16 tmp_sps_pic_width_in_luma_samples;
	u8 tmp_sps_log2_min_coding_block_size;
	u8 tmp_sps_log2_min_coding_block_size0;
	u8 tmp_sps_log2_diff_max_min_coding_block_size;
	u16 tmp_sps_pic_width_in_luma_samples0;
	u16 tmp_sps_log2_ctb_size;
	u16 tmp_sps_log2_ctb_size0;
	u16 tmp_sps_pic_height_in_luma_samples;
	u16 tmp_sps_log2_ctb_size1;
	u16 tmp_sps_log2_ctb_size2;
	u8 tmp_sps_scaling_list_enabled_flag;

	HevcDecoder_Algo_Parser_vld_ue_name(fifo, res, "max_transform_hierarchy_depth_inter     ");
	local_sps_id = sps_id;
	tmp_res = res[0];
	sps_max_transform_hierarchy_depth_inter[local_sps_id] = tmp_res;
	HevcDecoder_Algo_Parser_vld_ue_name(fifo, res, "max_transform_hierarchy_depth_intra     ");
	local_sps_id = sps_id;
	tmp_res0 = res[0];
	sps_max_transform_hierarchy_depth_intra[local_sps_id] = tmp_res0;
	HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "sps_scaling_list_enabled_flag           ");
	local_sps_id = sps_id;
	tmp_res1 = res[0];
	sps_scaling_list_enabled_flag[local_sps_id] = tmp_res1;
	local_sps_id = sps_id;
	tmp_sps_pic_width_in_luma_samples = sps_pic_width_in_luma_samples[local_sps_id];
	local_sps_id = sps_id;
	tmp_sps_log2_min_coding_block_size = sps_log2_min_coding_block_size[local_sps_id];
	min_cb_width = tmp_sps_pic_width_in_luma_samples >> tmp_sps_log2_min_coding_block_size;
	local_sps_id = sps_id;
	local_sps_id = sps_id;
	tmp_sps_log2_min_coding_block_size0 = sps_log2_min_coding_block_size[local_sps_id];
	local_sps_id = sps_id;
	tmp_sps_log2_diff_max_min_coding_block_size = sps_log2_diff_max_min_coding_block_size[local_sps_id];
	sps_log2_ctb_size[local_sps_id] = tmp_sps_log2_min_coding_block_size0 + tmp_sps_log2_diff_max_min_coding_block_size;
	local_sps_id = sps_id;
	local_sps_id = sps_id;
	tmp_sps_pic_width_in_luma_samples0 = sps_pic_width_in_luma_samples[local_sps_id];
	local_sps_id = sps_id;
	tmp_sps_log2_ctb_size = sps_log2_ctb_size[local_sps_id];
	local_sps_id = sps_id;
	tmp_sps_log2_ctb_size0 = sps_log2_ctb_size[local_sps_id];
	sps_ctb_width[local_sps_id] = (tmp_sps_pic_width_in_luma_samples0 + (1 << tmp_sps_log2_ctb_size) - 1) >> tmp_sps_log2_ctb_size0;
	local_sps_id = sps_id;
	local_sps_id = sps_id;
	tmp_sps_pic_height_in_luma_samples = sps_pic_height_in_luma_samples[local_sps_id];
	local_sps_id = sps_id;
	tmp_sps_log2_ctb_size1 = sps_log2_ctb_size[local_sps_id];
	local_sps_id = sps_id;
	tmp_sps_log2_ctb_size2 = sps_log2_ctb_size[local_sps_id];
	sps_ctb_height[local_sps_id] = (tmp_sps_pic_height_in_luma_samples + (1 << tmp_sps_log2_ctb_size1) - 1) >> tmp_sps_log2_ctb_size2;
	local_sps_id = sps_id;
	tmp_sps_scaling_list_enabled_flag = sps_scaling_list_enabled_flag[local_sps_id];
	if (tmp_sps_scaling_list_enabled_flag == 1) {
		se_idx = 60;
	} else {
		se_idx = 6;
	}

	// Update ports indexes

}
static i32 isSchedulable_read_SPS_Header_se_idx_60() {
	i32 result;
	u16 local_se_idx;
	i32 tmp_isFifoFull;

	local_se_idx = se_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	result = local_se_idx == 60 && tmp_isFifoFull;
	return result;
}

static void read_SPS_Header_se_idx_60() {

	u32 res[1];
	u8 sps_scaling_list_data_present_flag;
	i32 matrixId;
	i32 i;
	u16 local_sps_id;
	i32 i0;
	u8 tmp_default_scaling_list_intra;
	u8 tmp_default_scaling_list_intra0;
	u8 tmp_default_scaling_list_intra1;
	u8 tmp_default_scaling_list_inter;
	u8 tmp_default_scaling_list_inter0;
	u8 tmp_default_scaling_list_inter1;
	u8 tmp_default_scaling_list_intra2;
	u8 tmp_default_scaling_list_intra3;
	u8 tmp_default_scaling_list_intra4;
	u8 tmp_default_scaling_list_inter2;
	u8 tmp_default_scaling_list_inter3;
	u8 tmp_default_scaling_list_inter4;
	u8 tmp_default_scaling_list_intra5;
	u8 tmp_default_scaling_list_inter5;

	matrixId = 0;
	while (matrixId <= 5) {
		i = 0;
		while (i <= 15) {
			local_sps_id = sps_id;
			sps_sl[local_sps_id][0][matrixId][i] = 16;
			i = i + 1;
		}
		local_sps_id = sps_id;
		sps_sl_dc[local_sps_id][0][matrixId] = 16;
		local_sps_id = sps_id;
		sps_sl_dc[local_sps_id][1][matrixId] = 16;
		matrixId = matrixId + 1;
	}
	i0 = 0;
	while (i0 <= 63) {
		local_sps_id = sps_id;
		tmp_default_scaling_list_intra = HevcDecoder_Algo_Parser_default_scaling_list_intra[i0];
		sps_sl[local_sps_id][1][0][i0] = tmp_default_scaling_list_intra;
		local_sps_id = sps_id;
		tmp_default_scaling_list_intra0 = HevcDecoder_Algo_Parser_default_scaling_list_intra[i0];
		sps_sl[local_sps_id][1][1][i0] = tmp_default_scaling_list_intra0;
		local_sps_id = sps_id;
		tmp_default_scaling_list_intra1 = HevcDecoder_Algo_Parser_default_scaling_list_intra[i0];
		sps_sl[local_sps_id][1][2][i0] = tmp_default_scaling_list_intra1;
		local_sps_id = sps_id;
		tmp_default_scaling_list_inter = HevcDecoder_Algo_Parser_default_scaling_list_inter[i0];
		sps_sl[local_sps_id][1][3][i0] = tmp_default_scaling_list_inter;
		local_sps_id = sps_id;
		tmp_default_scaling_list_inter0 = HevcDecoder_Algo_Parser_default_scaling_list_inter[i0];
		sps_sl[local_sps_id][1][4][i0] = tmp_default_scaling_list_inter0;
		local_sps_id = sps_id;
		tmp_default_scaling_list_inter1 = HevcDecoder_Algo_Parser_default_scaling_list_inter[i0];
		sps_sl[local_sps_id][1][5][i0] = tmp_default_scaling_list_inter1;
		local_sps_id = sps_id;
		tmp_default_scaling_list_intra2 = HevcDecoder_Algo_Parser_default_scaling_list_intra[i0];
		sps_sl[local_sps_id][2][0][i0] = tmp_default_scaling_list_intra2;
		local_sps_id = sps_id;
		tmp_default_scaling_list_intra3 = HevcDecoder_Algo_Parser_default_scaling_list_intra[i0];
		sps_sl[local_sps_id][2][1][i0] = tmp_default_scaling_list_intra3;
		local_sps_id = sps_id;
		tmp_default_scaling_list_intra4 = HevcDecoder_Algo_Parser_default_scaling_list_intra[i0];
		sps_sl[local_sps_id][2][2][i0] = tmp_default_scaling_list_intra4;
		local_sps_id = sps_id;
		tmp_default_scaling_list_inter2 = HevcDecoder_Algo_Parser_default_scaling_list_inter[i0];
		sps_sl[local_sps_id][2][3][i0] = tmp_default_scaling_list_inter2;
		local_sps_id = sps_id;
		tmp_default_scaling_list_inter3 = HevcDecoder_Algo_Parser_default_scaling_list_inter[i0];
		sps_sl[local_sps_id][2][4][i0] = tmp_default_scaling_list_inter3;
		local_sps_id = sps_id;
		tmp_default_scaling_list_inter4 = HevcDecoder_Algo_Parser_default_scaling_list_inter[i0];
		sps_sl[local_sps_id][2][5][i0] = tmp_default_scaling_list_inter4;
		local_sps_id = sps_id;
		tmp_default_scaling_list_intra5 = HevcDecoder_Algo_Parser_default_scaling_list_intra[i0];
		sps_sl[local_sps_id][3][0][i0] = tmp_default_scaling_list_intra5;
		local_sps_id = sps_id;
		tmp_default_scaling_list_inter5 = HevcDecoder_Algo_Parser_default_scaling_list_inter[i0];
		sps_sl[local_sps_id][3][1][i0] = tmp_default_scaling_list_inter5;
		i0 = i0 + 1;
	}
	HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "sps_scaling_list_data_present_flag      ");
	sps_scaling_list_data_present_flag = res[0];
	if (sps_scaling_list_data_present_flag == 1) {
		se_idx = 61;
	} else {
		se_idx = 6;
	}

	// Update ports indexes

}
static i32 isSchedulable_read_SPS_Header_se_idx_61_loopSize_id() {
	i32 result;
	u16 local_se_idx;
	i32 tmp_isFifoFull;
	i32 local_sps_size_id;

	local_se_idx = se_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	local_sps_size_id = sps_size_id;
	result = local_se_idx == 61 && tmp_isFifoFull && local_sps_size_id < 4;
	return result;
}

static void read_SPS_Header_se_idx_61_loopSize_id() {

	i32 local_sps_size_id;

	local_sps_size_id = sps_size_id;
	if (local_sps_size_id == 3) {
		sps_size_id_matrixCase = 2;
	} else {
		sps_size_id_matrixCase = 6;
	}
	se_idx = 62;

	// Update ports indexes

}
static i32 isSchedulable_read_SPS_Header_se_idx_61_loopMatrix_id() {
	i32 result;
	u16 local_se_idx;
	i32 tmp_isFifoFull;
	i32 local_sps_matrix_id;
	i32 local_sps_size_id_matrixCase;

	local_se_idx = se_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	local_sps_matrix_id = sps_matrix_id;
	local_sps_size_id_matrixCase = sps_size_id_matrixCase;
	result = local_se_idx == 62 && tmp_isFifoFull && local_sps_matrix_id < local_sps_size_id_matrixCase;
	return result;
}

static void read_SPS_Header_se_idx_61_loopMatrix_id() {

	u32 res[1];
	i32 delta;
	i32 size_id_memcpyCase;
	u8 sps_scaling_list_pred_mode_flag[4][6];
	u32 sps_scaling_list_dc_coef[2][6];
	i32 local_sps_size_id;
	i32 local_sps_matrix_id;
	u32 tmp_res;
	u8 tmp_sps_scaling_list_pred_mode_flag;
	i32 k;
	u16 local_sps_id;
	u8 tmp_sps_sl;
	u8 tmp_sps_sl_dc;
	i32 tmp_min;
	u32 tmp_res0;
	u32 tmp_sps_scaling_list_dc_coef;
	i32 local_sps_next_coef;

	HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "scaling_list_pred_mode_flag             ");
	local_sps_size_id = sps_size_id;
	local_sps_matrix_id = sps_matrix_id;
	tmp_res = res[0];
	sps_scaling_list_pred_mode_flag[local_sps_size_id][local_sps_matrix_id] = tmp_res;
	local_sps_size_id = sps_size_id;
	local_sps_matrix_id = sps_matrix_id;
	tmp_sps_scaling_list_pred_mode_flag = sps_scaling_list_pred_mode_flag[local_sps_size_id][local_sps_matrix_id];
	if (tmp_sps_scaling_list_pred_mode_flag == 0) {
		HevcDecoder_Algo_Parser_vld_ue_name(fifo, res, "delta                                   ");
		delta = res[0];
		if (delta != 0) {
			local_sps_matrix_id = sps_matrix_id;
			if (local_sps_matrix_id - delta < 0) {
				printf("Invalid delta in scaling list data\n");
			}
			local_sps_size_id = sps_size_id;
			if (local_sps_size_id > 0) {
				size_id_memcpyCase = 64;
			} else {
				size_id_memcpyCase = 16;
			}
			k = 0;
			while (k <= size_id_memcpyCase - 1) {
				local_sps_id = sps_id;
				local_sps_size_id = sps_size_id;
				local_sps_matrix_id = sps_matrix_id;
				local_sps_id = sps_id;
				local_sps_size_id = sps_size_id;
				local_sps_matrix_id = sps_matrix_id;
				tmp_sps_sl = sps_sl[local_sps_id][local_sps_size_id][local_sps_matrix_id - delta][k];
				sps_sl[local_sps_id][local_sps_size_id][local_sps_matrix_id][k] = tmp_sps_sl;
				k = k + 1;
			}
			local_sps_size_id = sps_size_id;
			if (local_sps_size_id > 1) {
				local_sps_id = sps_id;
				local_sps_size_id = sps_size_id;
				local_sps_matrix_id = sps_matrix_id;
				local_sps_id = sps_id;
				local_sps_size_id = sps_size_id;
				local_sps_matrix_id = sps_matrix_id;
				tmp_sps_sl_dc = sps_sl_dc[local_sps_id][local_sps_size_id - 2][local_sps_matrix_id - delta];
				sps_sl_dc[local_sps_id][local_sps_size_id - 2][local_sps_matrix_id] = tmp_sps_sl_dc;
			}
		}
		local_sps_matrix_id = sps_matrix_id;
		sps_matrix_id = local_sps_matrix_id + 1;
	} else {
		sps_next_coef = 8;
		local_sps_size_id = sps_size_id;
		tmp_min = HevcDecoder_Algo_Parser_min(64, 1 << (4 + (local_sps_size_id << 1)));
		sps_coef_num = tmp_min;
		local_sps_size_id = sps_size_id;
		if (local_sps_size_id > 1) {
			HevcDecoder_Algo_Parser_vld_se_name(fifo, res, "scaling_list_dc_coef                    ");
			local_sps_size_id = sps_size_id;
			local_sps_matrix_id = sps_matrix_id;
			tmp_res0 = res[0];
			sps_scaling_list_dc_coef[local_sps_size_id - 2][local_sps_matrix_id] = tmp_res0 + 8;
			local_sps_size_id = sps_size_id;
			local_sps_matrix_id = sps_matrix_id;
			tmp_sps_scaling_list_dc_coef = sps_scaling_list_dc_coef[local_sps_size_id - 2][local_sps_matrix_id];
			sps_next_coef = tmp_sps_scaling_list_dc_coef;
			local_sps_id = sps_id;
			local_sps_size_id = sps_size_id;
			local_sps_matrix_id = sps_matrix_id;
			local_sps_next_coef = sps_next_coef;
			sps_sl_dc[local_sps_id][local_sps_size_id - 2][local_sps_matrix_id] = local_sps_next_coef;
		}
		se_idx = 63;
		cnt_i = 0;
	}

	// Update ports indexes

}
static i32 isSchedulable_read_SPS_Header_se_idx_63_loopNumCoef() {
	i32 result;
	u16 local_se_idx;
	i32 tmp_isFifoFull;
	u32 local_cnt_i;
	i32 local_sps_coef_num;

	local_se_idx = se_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	local_cnt_i = cnt_i;
	local_sps_coef_num = sps_coef_num;
	result = local_se_idx == 63 && tmp_isFifoFull && local_cnt_i < local_sps_coef_num;
	return result;
}

static void read_SPS_Header_se_idx_63_loopNumCoef() {

	u32 res[1];
	i32 local_sps_size_id;
	u32 local_cnt_i;
	i8 tmp_hevc_diag_scan4x4_y;
	u8 tmp_hevc_diag_scan4x4_x;
	i8 tmp_hevc_diag_scan8x8_y;
	i8 tmp_hevc_diag_scan8x8_x;
	u32 tmp_res;
	i32 local_sps_next_coef;
	i32 local_sps_scaling_list_delta_coef;
	u16 local_sps_id;
	i32 local_sps_matrix_id;
	i32 local_sps_pos;

	local_sps_size_id = sps_size_id;
	if (local_sps_size_id == 0) {
		local_cnt_i = cnt_i;
		tmp_hevc_diag_scan4x4_y = HevcDecoder_Algo_Parser_hevc_diag_scan4x4_y[local_cnt_i];
		local_cnt_i = cnt_i;
		tmp_hevc_diag_scan4x4_x = HevcDecoder_Algo_Parser_hevc_diag_scan4x4_x[local_cnt_i];
		sps_pos = 4 * tmp_hevc_diag_scan4x4_y + tmp_hevc_diag_scan4x4_x;
	} else {
		local_cnt_i = cnt_i;
		tmp_hevc_diag_scan8x8_y = HevcDecoder_Algo_Parser_hevc_diag_scan8x8_y[local_cnt_i];
		local_cnt_i = cnt_i;
		tmp_hevc_diag_scan8x8_x = HevcDecoder_Algo_Parser_hevc_diag_scan8x8_x[local_cnt_i];
		sps_pos = 8 * tmp_hevc_diag_scan8x8_y + tmp_hevc_diag_scan8x8_x;
	}
	HevcDecoder_Algo_Parser_vld_se_name(fifo, res, "scaling_list_delta_coef                 ");
	tmp_res = res[0];
	sps_scaling_list_delta_coef = tmp_res;
	local_sps_next_coef = sps_next_coef;
	local_sps_scaling_list_delta_coef = sps_scaling_list_delta_coef;
	sps_next_coef = (local_sps_next_coef + local_sps_scaling_list_delta_coef + 256) % 256;
	local_sps_id = sps_id;
	local_sps_size_id = sps_size_id;
	local_sps_matrix_id = sps_matrix_id;
	local_sps_pos = sps_pos;
	local_sps_next_coef = sps_next_coef;
	sps_sl[local_sps_id][local_sps_size_id][local_sps_matrix_id][local_sps_pos] = local_sps_next_coef;
	local_cnt_i = cnt_i;
	cnt_i = local_cnt_i + 1;

	// Update ports indexes

}
static i32 isSchedulable_read_SPS_Header_se_idx_63_loopNumCoefEnd() {
	i32 result;
	u16 local_se_idx;
	i32 tmp_isFifoFull;
	u32 local_cnt_i;
	i32 local_sps_coef_num;

	local_se_idx = se_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	local_cnt_i = cnt_i;
	local_sps_coef_num = sps_coef_num;
	result = local_se_idx == 63 && tmp_isFifoFull && local_cnt_i == local_sps_coef_num;
	return result;
}

static void read_SPS_Header_se_idx_63_loopNumCoefEnd() {

	i32 local_sps_matrix_id;

	cnt_i = 0;
	local_sps_matrix_id = sps_matrix_id;
	sps_matrix_id = local_sps_matrix_id + 1;
	se_idx = 62;

	// Update ports indexes

}
static i32 isSchedulable_read_SPS_Header_se_idx_62_loopMatrix_id_End() {
	i32 result;
	u16 local_se_idx;
	i32 tmp_isFifoFull;
	i32 local_sps_matrix_id;
	i32 local_sps_size_id_matrixCase;

	local_se_idx = se_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	local_sps_matrix_id = sps_matrix_id;
	local_sps_size_id_matrixCase = sps_size_id_matrixCase;
	result = local_se_idx == 62 && tmp_isFifoFull && local_sps_matrix_id == local_sps_size_id_matrixCase;
	return result;
}

static void read_SPS_Header_se_idx_62_loopMatrix_id_End() {

	i32 local_sps_size_id;

	local_sps_size_id = sps_size_id;
	sps_size_id = local_sps_size_id + 1;
	sps_matrix_id = 0;
	se_idx = 61;

	// Update ports indexes

}
static i32 isSchedulable_read_SPS_Header_se_idx_61_size_id_loopEnd() {
	i32 result;
	u16 local_se_idx;
	i32 tmp_isFifoFull;
	i32 local_sps_size_id;

	local_se_idx = se_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	local_sps_size_id = sps_size_id;
	result = local_se_idx == 61 && tmp_isFifoFull && local_sps_size_id == 4;
	return result;
}

static void read_SPS_Header_se_idx_61_size_id_loopEnd() {


	sps_size_id = 0;
	se_idx = 6;

	// Update ports indexes

}
static i32 isSchedulable_read_SPS_Header_se_idx_6() {
	i32 result;
	u16 local_se_idx;
	i32 tmp_isFifoFull;

	local_se_idx = se_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	result = local_se_idx == 6 && tmp_isFifoFull;
	return result;
}

static void read_SPS_Header_se_idx_6() {

	u32 res[1];
	u32 tmp_res;
	u16 local_sps_id;
	u32 tmp_res0;
	u32 tmp_res1;
	u8 tmp_sps_pcm_enabled_flag;
	u32 tmp_res2;
	u32 tmp_res3;
	u32 tmp_res4;
	u32 tmp_log2_min_pcm_cb_size;
	u32 tmp_res5;
	u32 tmp_res6;
	u32 tmp_res7;
	u16 local_se_idx;

	HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "amp_enabled_flag                        ");
	tmp_res = res[0];
	amp_enabled_flag = tmp_res;
	HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "sample_adaptive_offset_enabled_flag     ");
	local_sps_id = sps_id;
	tmp_res0 = res[0];
	sps_sample_adaptive_offset_enabled_flag[local_sps_id] = tmp_res0;
	HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "pcm_enabled_flag                        ");
	local_sps_id = sps_id;
	tmp_res1 = res[0];
	sps_pcm_enabled_flag[local_sps_id] = tmp_res1;
	local_sps_id = sps_id;
	tmp_sps_pcm_enabled_flag = sps_pcm_enabled_flag[local_sps_id];
	if (tmp_sps_pcm_enabled_flag == 1) {
		HevcDecoder_Algo_Parser_vld_u_name(4, fifo, res, "pcm_sample_bit_depth_luma_minus1        ");
		local_sps_id = sps_id;
		tmp_res2 = res[0];
		pcm_bit_depth[local_sps_id] = tmp_res2 + 1;
		HevcDecoder_Algo_Parser_vld_u_name(4, fifo, res, "pcm_sample_bit_depth_chroma_minus1      ");
		local_sps_id = sps_id;
		tmp_res3 = res[0];
		pcm_bit_depth_chroma[local_sps_id] = tmp_res3 + 1;
		HevcDecoder_Algo_Parser_vld_ue_name(fifo, res, "log2_min_pcm_luma_coding_block_size_minus3");
		local_sps_id = sps_id;
		tmp_res4 = res[0];
		log2_min_pcm_cb_size[local_sps_id] = tmp_res4 + 3;
		HevcDecoder_Algo_Parser_vld_ue_name(fifo, res, "log2_diff_max_min_pcm_luma_coding_block_size");
		local_sps_id = sps_id;
		local_sps_id = sps_id;
		tmp_log2_min_pcm_cb_size = log2_min_pcm_cb_size[local_sps_id];
		tmp_res5 = res[0];
		log2_max_pcm_cb_size[local_sps_id] = tmp_log2_min_pcm_cb_size + tmp_res5;
		HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "pcm_loop_filter_disable_flag            ");
		local_sps_id = sps_id;
		tmp_res6 = res[0];
		pcm_loop_filter_disable_flag[local_sps_id] = tmp_res6;
	}
	HevcDecoder_Algo_Parser_vld_ue_name(fifo, res, "num_short_term_ref_pic_sets             ");
	local_sps_id = sps_id;
	tmp_res7 = res[0];
	sps_num_short_term_ref_pic_sets[local_sps_id] = tmp_res7;
	local_se_idx = se_idx;
	se_idx = local_se_idx + 1;
	cnt_i = 0;

	// Update ports indexes

}
static i32 isSchedulable_read_SPS_Header_se_idx_7_loop() {
	i32 result;
	u16 local_se_idx;
	i32 tmp_isFifoFull;
	u32 local_cnt_i;
	u16 local_sps_id;
	u8 tmp_sps_num_short_term_ref_pic_sets;

	local_se_idx = se_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	local_cnt_i = cnt_i;
	local_sps_id = sps_id;
	tmp_sps_num_short_term_ref_pic_sets = sps_num_short_term_ref_pic_sets[local_sps_id];
	result = local_se_idx == 7 && tmp_isFifoFull && local_cnt_i < tmp_sps_num_short_term_ref_pic_sets;
	return result;
}

static void read_SPS_Header_se_idx_7_loop() {

	u16 local_sps_id;
	u32 local_cnt_i;
	u8 tmp_sps_num_short_term_ref_pic_sets;

	local_sps_id = sps_id;
	local_cnt_i = cnt_i;
	local_sps_id = sps_id;
	tmp_sps_num_short_term_ref_pic_sets = sps_num_short_term_ref_pic_sets[local_sps_id];
	HevcDecoder_Algo_Parser_parseShortTermRefPicSet(local_sps_id, local_cnt_i, tmp_sps_num_short_term_ref_pic_sets, fifo, pcRPS);
	local_cnt_i = cnt_i;
	cnt_i = local_cnt_i + 1;

	// Update ports indexes

}
static i32 isSchedulable_read_SPS_Header_se_idx_7_loopEnd() {
	i32 result;
	u16 local_se_idx;
	u32 local_cnt_i;
	u16 local_sps_id;
	u8 tmp_sps_num_short_term_ref_pic_sets;

	local_se_idx = se_idx;
	local_cnt_i = cnt_i;
	local_sps_id = sps_id;
	tmp_sps_num_short_term_ref_pic_sets = sps_num_short_term_ref_pic_sets[local_sps_id];
	result = local_se_idx == 7 && local_cnt_i == tmp_sps_num_short_term_ref_pic_sets;
	return result;
}

static void read_SPS_Header_se_idx_7_loopEnd() {

	u16 local_se_idx;

	local_se_idx = se_idx;
	se_idx = local_se_idx + 1;
	cnt_i = 0;

	// Update ports indexes

}
static i32 isSchedulable_read_SPS_Header_se_idx_8() {
	i32 result;
	u16 local_se_idx;
	i32 tmp_isFifoFull;

	local_se_idx = se_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	result = local_se_idx == 8 && tmp_isFifoFull;
	return result;
}

static void read_SPS_Header_se_idx_8() {

	u32 res[1];
	u16 local_sps_id;
	u32 tmp_res;
	u32 tmp_res0;
	u32 tmp_res1;
	i32 i;
	u8 tmp_sps_num_long_term_ref_pics_sps;
	u8 tmp_sps_log2_max_pic_order_cnt_lsb_minus4;
	u32 tmp_res2;
	u32 tmp_res3;
	u32 tmp_res4;
	u32 tmp_res5;
	u32 tmp_res6;
	u16 local_se_idx;

	HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "long_term_ref_pics_present_flag         ");
	local_sps_id = sps_id;
	tmp_res = res[0];
	sps_long_term_ref_pics_present_flag[local_sps_id] = tmp_res;
	tmp_res0 = res[0];
	if (tmp_res0 == 1) {
		HevcDecoder_Algo_Parser_vld_ue_name(fifo, res, "num_long_term_ref_pics_sps              ");
		local_sps_id = sps_id;
		tmp_res1 = res[0];
		sps_num_long_term_ref_pics_sps[local_sps_id] = tmp_res1;
		i = 0;
		local_sps_id = sps_id;
		tmp_sps_num_long_term_ref_pics_sps = sps_num_long_term_ref_pics_sps[local_sps_id];
		while (i <= tmp_sps_num_long_term_ref_pics_sps - 1) {
			local_sps_id = sps_id;
			tmp_sps_log2_max_pic_order_cnt_lsb_minus4 = sps_log2_max_pic_order_cnt_lsb_minus4[local_sps_id];
			HevcDecoder_Algo_Parser_vld_u_name(tmp_sps_log2_max_pic_order_cnt_lsb_minus4 + 4, fifo, res, "lt_ref_pic_poc_lsb_sps                  ");
			tmp_res2 = res[0];
			lt_ref_pic_poc_lsb_sps[i] = tmp_res2;
			HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "used_by_curr_pic_lt_sps_flag            ");
			tmp_res3 = res[0];
			used_by_curr_pic_lt_sps_flag[i] = tmp_res3;
			i = i + 1;
		}
	}
	HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "sps_temporal_mvp_enable_flag            ");
	local_sps_id = sps_id;
	tmp_res4 = res[0];
	sps_temporal_mvp_enable_flag[local_sps_id] = tmp_res4;
	HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "sps_strong_intra_smoothing_enable_flag  ");
	local_sps_id = sps_id;
	tmp_res5 = res[0];
	sps_strong_intra_smoothing_enable_flag[local_sps_id] = tmp_res5 == 1;
	HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "vui_parameters_present_flag             ");
	tmp_res6 = res[0];
	if (tmp_res6 == 1) {
		printf("not support for vui_parameters_present_flag != 0\n");
	}
	local_se_idx = se_idx;
	se_idx = local_se_idx + 1;

	// Update ports indexes

}
static i32 isSchedulable_read_SPS_Header_done() {
	i32 result;
	u16 local_se_idx;
	i32 tmp_isFifoFull;

	local_se_idx = se_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	result = local_se_idx == 9 && tmp_isFifoFull;
	return result;
}

static void read_SPS_Header_done() {

	u32 res[1];
	u32 tmp_res;

	HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "sps_extension_flag                      ");
	tmp_res = res[0];
	if (tmp_res == 1) {
		printf("not support for sps_extension_flag != 0\n");
	}

	// Update ports indexes

}
static i32 isSchedulable_read_PPS_Header_se_idx_1() {
	i32 result;
	u16 local_se_idx;
	i32 tmp_isFifoFull;

	local_se_idx = se_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	result = local_se_idx == 1 && tmp_isFifoFull;
	return result;
}

static void read_PPS_Header_se_idx_1() {

	u32 res[1];
	u32 tmp_res;
	u32 tmp_res0;
	u16 local_pps_id;
	u32 tmp_res1;
	u16 local_se_idx;

	HevcDecoder_Algo_Parser_vld_ue_name(fifo, res, "pps_pic_parameter_set_id                ");
	tmp_res = res[0];
	pps_id = tmp_res;
	HevcDecoder_Algo_Parser_vld_ue_name(fifo, res, "pps_seq_parameter_set_id                ");
	tmp_res0 = res[0];
	sps_id = tmp_res0;
	local_pps_id = pps_id;
	tmp_res1 = res[0];
	pps_sps_id[local_pps_id] = tmp_res1;
	local_se_idx = se_idx;
	se_idx = local_se_idx + 1;
	cnt_i = 0;
	local_pps_id = pps_id;
	pps_num_tile_columns_minus1[local_pps_id] = 0;
	local_pps_id = pps_id;
	pps_num_tile_rows_minus1[local_pps_id] = 0;
	local_pps_id = pps_id;
	pps_uniform_spacing_flag[local_pps_id] = 1;

	// Update ports indexes

}
static i32 isSchedulable_read_PPS_Header_se_idx_2() {
	i32 result;
	u16 local_se_idx;
	i32 tmp_isFifoFull;

	local_se_idx = se_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	result = local_se_idx == 2 && tmp_isFifoFull;
	return result;
}

static void read_PPS_Header_se_idx_2() {

	u32 res[1];
	u16 local_pps_id;
	u32 tmp_res;
	u32 tmp_res0;
	u32 tmp_res1;
	u32 tmp_res2;
	u32 tmp_res3;
	u32 tmp_res4;
	u32 tmp_res5;
	u32 tmp_res6;
	u32 tmp_res7;
	u32 tmp_res8;
	u32 tmp_res9;
	u32 tmp_res10;
	u32 tmp_res11;
	u32 tmp_res12;
	u32 tmp_res13;
	u32 tmp_res14;
	u32 tmp_res15;
	u32 tmp_res16;
	u32 tmp_res17;
	u32 tmp_res18;
	u32 tmp_res19;
	u8 tmp_pps_tiles_enabled_flag;
	u32 tmp_res20;
	u32 tmp_res21;
	u32 tmp_res22;
	u16 local_se_idx;

	HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "dependent_slice_segments_enabled_flag   ");
	local_pps_id = pps_id;
	tmp_res = res[0];
	pps_dependent_slice_segments_enabled_flag[local_pps_id] = tmp_res;
	HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "output_flag_present_flag                ");
	local_pps_id = pps_id;
	tmp_res0 = res[0];
	pps_output_flag_present_flag[local_pps_id] = tmp_res0;
	HevcDecoder_Algo_Parser_vld_u_name(3, fifo, res, "num_extra_slice_header_bits             ");
	local_pps_id = pps_id;
	tmp_res1 = res[0];
	pps_num_extra_slice_header_bits[local_pps_id] = tmp_res1;
	HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "sign_data_hiding_flag                   ");
	local_pps_id = pps_id;
	tmp_res2 = res[0];
	pps_sign_data_hiding_flag[local_pps_id] = tmp_res2;
	HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "cabac_init_present_flag                 ");
	local_pps_id = pps_id;
	tmp_res3 = res[0];
	pps_cabac_init_present_flag[local_pps_id] = tmp_res3;
	HevcDecoder_Algo_Parser_vld_ue_name(fifo, res, "num_ref_idx_l0_default_active_minus1    ");
	local_pps_id = pps_id;
	tmp_res4 = res[0];
	pps_num_ref_idx_l0_default_active_minus1[local_pps_id] = tmp_res4;
	HevcDecoder_Algo_Parser_vld_ue_name(fifo, res, "num_ref_idx_l1_default_active_minus1    ");
	local_pps_id = pps_id;
	tmp_res5 = res[0];
	pps_num_ref_idx_l1_default_active_minus1[local_pps_id] = tmp_res5;
	HevcDecoder_Algo_Parser_vld_se_name(fifo, res, "init_qp_minus26                         ");
	local_pps_id = pps_id;
	tmp_res6 = res[0];
	pps_init_qp_minus26[local_pps_id] = tmp_res6;
	HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "constrained_intra_pred_flag             ");
	local_pps_id = pps_id;
	tmp_res7 = res[0];
	pps_constrained_intra_pred_flag[local_pps_id] = tmp_res7 != 0;
	HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "transform_skip_enabled_flag             ");
	local_pps_id = pps_id;
	tmp_res8 = res[0];
	pps_transform_skip_enabled_flag[local_pps_id] = tmp_res8;
	HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "cu_qp_delta_enabled_flag                ");
	local_pps_id = pps_id;
	tmp_res9 = res[0];
	pps_cu_qp_delta_enabled_flag[local_pps_id] = tmp_res9;
	tmp_res10 = res[0];
	if (tmp_res10 == 1) {
		HevcDecoder_Algo_Parser_vld_ue_name(fifo, res, "diff_cu_qp_delta_depth                  ");
		local_pps_id = pps_id;
		tmp_res11 = res[0];
		pps_diff_cu_qp_delta_depth[local_pps_id] = tmp_res11;
	} else {
		local_pps_id = pps_id;
		pps_diff_cu_qp_delta_depth[local_pps_id] = 0;
	}
	HevcDecoder_Algo_Parser_vld_se_name(fifo, res, "pps_cb_qp_offset                        ");
	local_pps_id = pps_id;
	tmp_res12 = res[0];
	pps_cb_qp_offset[local_pps_id] = tmp_res12;
	HevcDecoder_Algo_Parser_vld_se_name(fifo, res, "pps_cr_qp_offset                        ");
	local_pps_id = pps_id;
	tmp_res13 = res[0];
	pps_cr_qp_offset[local_pps_id] = tmp_res13;
	HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "pps_slice_chroma_qp_offsets_present_flag");
	local_pps_id = pps_id;
	tmp_res14 = res[0];
	pps_slice_chroma_qp_offsets_present_flag[local_pps_id] = tmp_res14;
	HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "weighted_pred_flag                      ");
	local_pps_id = pps_id;
	tmp_res15 = res[0];
	pps_weighted_pred_flag[local_pps_id] = tmp_res15;
	HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "weighted_bipred_flag                    ");
	local_pps_id = pps_id;
	tmp_res16 = res[0];
	pps_weighted_bipred_flag[local_pps_id] = tmp_res16;
	HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "transquant_bypass_enable_flag           ");
	local_pps_id = pps_id;
	tmp_res17 = res[0];
	pps_transquant_bypass_enable_flag[local_pps_id] = tmp_res17;
	HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "tiles_enabled_flag                      ");
	local_pps_id = pps_id;
	tmp_res18 = res[0];
	pps_tiles_enabled_flag[local_pps_id] = tmp_res18;
	HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "entropy_coding_sync_enabled_flag        ");
	local_pps_id = pps_id;
	tmp_res19 = res[0];
	pps_entropy_coding_sync_enabled_flag[local_pps_id] = tmp_res19;
	local_pps_id = pps_id;
	pps_num_tile_columns_minus1[local_pps_id] = 0;
	local_pps_id = pps_id;
	pps_num_tile_rows_minus1[local_pps_id] = 0;
	local_pps_id = pps_id;
	pps_uniform_spacing_flag[local_pps_id] = 1;
	local_pps_id = pps_id;
	tmp_pps_tiles_enabled_flag = pps_tiles_enabled_flag[local_pps_id];
	if (tmp_pps_tiles_enabled_flag == 1) {
		HevcDecoder_Algo_Parser_vld_ue_name(fifo, res, "num_tile_columns_minus1                 ");
		local_pps_id = pps_id;
		tmp_res20 = res[0];
		pps_num_tile_columns_minus1[local_pps_id] = tmp_res20;
		HevcDecoder_Algo_Parser_vld_ue_name(fifo, res, "num_tile_rows_minus1                    ");
		local_pps_id = pps_id;
		tmp_res21 = res[0];
		pps_num_tile_rows_minus1[local_pps_id] = tmp_res21;
		HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "uniform_spacing_flag                    ");
		local_pps_id = pps_id;
		tmp_res22 = res[0];
		pps_uniform_spacing_flag[local_pps_id] = tmp_res22;
	}
	local_se_idx = se_idx;
	se_idx = local_se_idx + 1;
	cnt_i = 0;

	// Update ports indexes

}
static i32 isSchedulable_read_PPS_Header_se_idx_3_loop() {
	i32 result;
	u16 local_se_idx;
	i32 tmp_isFifoFull;
	u16 local_pps_id;
	u8 tmp_pps_uniform_spacing_flag;
	u32 local_cnt_i;
	u8 tmp_pps_num_tile_columns_minus1;

	local_se_idx = se_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	local_pps_id = pps_id;
	tmp_pps_uniform_spacing_flag = pps_uniform_spacing_flag[local_pps_id];
	local_cnt_i = cnt_i;
	local_pps_id = pps_id;
	tmp_pps_num_tile_columns_minus1 = pps_num_tile_columns_minus1[local_pps_id];
	result = local_se_idx == 3 && tmp_isFifoFull && (tmp_pps_uniform_spacing_flag == 0 && local_cnt_i < tmp_pps_num_tile_columns_minus1);
	return result;
}

static void read_PPS_Header_se_idx_3_loop() {

	u32 res[1];
	u16 local_pps_id;
	u32 local_cnt_i;
	u32 tmp_res;
	i32 local_sum;
	u16 tmp_pps_column_width;
	i32 local_PICT_WIDTH;
	u8 local_MIN_CTB_SIZE_Y;

	HevcDecoder_Algo_Parser_vld_ue_name(fifo, res, "column_width[ ]                         ");
	local_pps_id = pps_id;
	local_cnt_i = cnt_i;
	tmp_res = res[0];
	pps_column_width[local_pps_id][local_cnt_i] = tmp_res + 1;
	local_sum = sum;
	local_pps_id = pps_id;
	local_cnt_i = cnt_i;
	tmp_pps_column_width = pps_column_width[local_pps_id][local_cnt_i];
	sum = local_sum + tmp_pps_column_width;
	local_cnt_i = cnt_i;
	local_PICT_WIDTH = HevcDecoder_Algo_Parser_PICT_WIDTH;
	local_MIN_CTB_SIZE_Y = HevcDecoder_Algo_Parser_MIN_CTB_SIZE_Y;
	if (local_cnt_i >= local_PICT_WIDTH / local_MIN_CTB_SIZE_Y) {
		local_cnt_i = cnt_i;
		local_PICT_WIDTH = HevcDecoder_Algo_Parser_PICT_WIDTH;
		local_MIN_CTB_SIZE_Y = HevcDecoder_Algo_Parser_MIN_CTB_SIZE_Y;
		printf("Error read_PPS_Header.se_idx_3.loop : %u >= %i\n", local_cnt_i, local_PICT_WIDTH / local_MIN_CTB_SIZE_Y);
	}
	local_cnt_i = cnt_i;
	cnt_i = local_cnt_i + 1;

	// Update ports indexes

}
static i32 isSchedulable_read_PPS_Header_se_idx_3_loopEnd() {
	i32 result;
	u16 local_se_idx;
	u16 local_pps_id;
	u8 tmp_pps_uniform_spacing_flag;
	u32 local_cnt_i;
	u8 tmp_pps_num_tile_columns_minus1;

	local_se_idx = se_idx;
	local_pps_id = pps_id;
	tmp_pps_uniform_spacing_flag = pps_uniform_spacing_flag[local_pps_id];
	local_cnt_i = cnt_i;
	local_pps_id = pps_id;
	tmp_pps_num_tile_columns_minus1 = pps_num_tile_columns_minus1[local_pps_id];
	result = local_se_idx == 3 && (tmp_pps_uniform_spacing_flag == 0 && local_cnt_i == tmp_pps_num_tile_columns_minus1);
	return result;
}

static void read_PPS_Header_se_idx_3_loopEnd() {

	u16 local_pps_id;
	u8 tmp_pps_num_tile_columns_minus1;
	u16 local_sps_id;
	u16 tmp_sps_ctb_width;
	i32 local_sum;
	u16 local_se_idx;

	local_pps_id = pps_id;
	local_pps_id = pps_id;
	tmp_pps_num_tile_columns_minus1 = pps_num_tile_columns_minus1[local_pps_id];
	local_sps_id = sps_id;
	tmp_sps_ctb_width = sps_ctb_width[local_sps_id];
	local_sum = sum;
	pps_column_width[local_pps_id][tmp_pps_num_tile_columns_minus1] = tmp_sps_ctb_width - local_sum;
	local_se_idx = se_idx;
	se_idx = local_se_idx + 1;
	cnt_i = 0;
	sum = 0;

	// Update ports indexes

}
static i32 isSchedulable_read_PPS_Header_se_idx_3_noLoop() {
	i32 result;
	u16 local_se_idx;
	u16 local_pps_id;
	u8 tmp_pps_uniform_spacing_flag;

	local_se_idx = se_idx;
	local_pps_id = pps_id;
	tmp_pps_uniform_spacing_flag = pps_uniform_spacing_flag[local_pps_id];
	result = local_se_idx == 3 && tmp_pps_uniform_spacing_flag == 1;
	return result;
}

static void read_PPS_Header_se_idx_3_noLoop() {

	u16 local_se_idx;

	local_se_idx = se_idx;
	se_idx = local_se_idx + 2;

	// Update ports indexes

}
static i32 isSchedulable_read_PPS_Header_se_idx_4_loop() {
	i32 result;
	u16 local_se_idx;
	i32 tmp_isFifoFull;
	u16 local_pps_id;
	u8 tmp_pps_uniform_spacing_flag;
	u32 local_cnt_i;
	u8 tmp_pps_num_tile_rows_minus1;

	local_se_idx = se_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	local_pps_id = pps_id;
	tmp_pps_uniform_spacing_flag = pps_uniform_spacing_flag[local_pps_id];
	local_cnt_i = cnt_i;
	local_pps_id = pps_id;
	tmp_pps_num_tile_rows_minus1 = pps_num_tile_rows_minus1[local_pps_id];
	result = local_se_idx == 4 && tmp_isFifoFull && (tmp_pps_uniform_spacing_flag == 0 && local_cnt_i < tmp_pps_num_tile_rows_minus1);
	return result;
}

static void read_PPS_Header_se_idx_4_loop() {

	u32 res[1];
	u16 local_pps_id;
	u32 local_cnt_i;
	u32 tmp_res;
	i32 local_sum;
	u16 tmp_pps_row_height;
	i32 local_PICT_HEIGHT;
	u8 local_MIN_CTB_SIZE_Y;

	HevcDecoder_Algo_Parser_vld_ue_name(fifo, res, "row_height[ ]                           ");
	local_pps_id = pps_id;
	local_cnt_i = cnt_i;
	tmp_res = res[0];
	pps_row_height[local_pps_id][local_cnt_i] = tmp_res + 1;
	local_sum = sum;
	local_pps_id = pps_id;
	local_cnt_i = cnt_i;
	tmp_pps_row_height = pps_row_height[local_pps_id][local_cnt_i];
	sum = local_sum + tmp_pps_row_height;
	local_cnt_i = cnt_i;
	local_PICT_HEIGHT = HevcDecoder_Algo_Parser_PICT_HEIGHT;
	local_MIN_CTB_SIZE_Y = HevcDecoder_Algo_Parser_MIN_CTB_SIZE_Y;
	if (local_cnt_i >= local_PICT_HEIGHT / local_MIN_CTB_SIZE_Y) {
		local_cnt_i = cnt_i;
		local_PICT_HEIGHT = HevcDecoder_Algo_Parser_PICT_HEIGHT;
		local_MIN_CTB_SIZE_Y = HevcDecoder_Algo_Parser_MIN_CTB_SIZE_Y;
		printf("Error read_PPS_Header.se_idx_4.loop : %u >= %i\n", local_cnt_i, local_PICT_HEIGHT / local_MIN_CTB_SIZE_Y);
	}
	local_cnt_i = cnt_i;
	cnt_i = local_cnt_i + 1;

	// Update ports indexes

}
static i32 isSchedulable_read_PPS_Header_se_idx_4_loopEnd() {
	i32 result;
	u16 local_se_idx;
	u16 local_pps_id;
	u8 tmp_pps_uniform_spacing_flag;
	u32 local_cnt_i;
	u8 tmp_pps_num_tile_rows_minus1;

	local_se_idx = se_idx;
	local_pps_id = pps_id;
	tmp_pps_uniform_spacing_flag = pps_uniform_spacing_flag[local_pps_id];
	local_cnt_i = cnt_i;
	local_pps_id = pps_id;
	tmp_pps_num_tile_rows_minus1 = pps_num_tile_rows_minus1[local_pps_id];
	result = local_se_idx == 4 && (tmp_pps_uniform_spacing_flag == 0 && local_cnt_i == tmp_pps_num_tile_rows_minus1);
	return result;
}

static void read_PPS_Header_se_idx_4_loopEnd() {

	u16 local_pps_id;
	u8 tmp_pps_num_tile_rows_minus1;
	u16 local_sps_id;
	u16 tmp_sps_ctb_height;
	i32 local_sum;

	local_pps_id = pps_id;
	local_pps_id = pps_id;
	tmp_pps_num_tile_rows_minus1 = pps_num_tile_rows_minus1[local_pps_id];
	local_sps_id = sps_id;
	tmp_sps_ctb_height = sps_ctb_height[local_sps_id];
	local_sum = sum;
	pps_row_height[local_pps_id][tmp_pps_num_tile_rows_minus1] = tmp_sps_ctb_height - local_sum;
	cnt_i = 0;
	se_idx = 5;
	sum = 0;

	// Update ports indexes

}
static i32 isSchedulable_read_PPS_Header_se_idx_5() {
	i32 result;
	u16 local_se_idx;
	i32 tmp_isFifoFull;

	local_se_idx = se_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	result = local_se_idx == 5 && tmp_isFifoFull;
	return result;
}

static void read_PPS_Header_se_idx_5() {

	u32 res[1];
	u16 local_pps_id;
	u8 tmp_pps_tiles_enabled_flag;
	u32 tmp_res;
	u32 tmp_res0;
	u8 tmp_pps_deblocking_filter_control_present_flag;
	u32 tmp_res1;
	u32 tmp_res2;
	u32 tmp_res3;
	u32 tmp_res4;
	u32 tmp_res5;
	u32 tmp_res6;
	u8 tmp_pps_scaling_list_data_present_flag;

	local_pps_id = pps_id;
	tmp_pps_tiles_enabled_flag = pps_tiles_enabled_flag[local_pps_id];
	if (tmp_pps_tiles_enabled_flag == 1) {
		HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "loop_filter_across_tiles_enabled_flag   ");
	}
	HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "loop_filter_across_slices_enabled_flag  ");
	local_pps_id = pps_id;
	tmp_res = res[0];
	pps_loop_filter_across_slice_enabled_flag[local_pps_id] = tmp_res;
	HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "deblocking_filter_control_present_flag  ");
	local_pps_id = pps_id;
	tmp_res0 = res[0];
	pps_deblocking_filter_control_present_flag[local_pps_id] = tmp_res0;
	local_pps_id = pps_id;
	deblocking_filter_override_enabled_flag[local_pps_id] = 0;
	local_pps_id = pps_id;
	tmp_pps_deblocking_filter_control_present_flag = pps_deblocking_filter_control_present_flag[local_pps_id];
	if (tmp_pps_deblocking_filter_control_present_flag == 1) {
		HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "deblocking_filter_override_enabled_flag ");
		local_pps_id = pps_id;
		tmp_res1 = res[0];
		deblocking_filter_override_enabled_flag[local_pps_id] = tmp_res1;
		HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "pps_disable_deblocking_filter_flag      ");
		local_pps_id = pps_id;
		tmp_res2 = res[0];
		pps_disable_deblocking_filter_flag[local_pps_id] = tmp_res2;
		tmp_res3 = res[0];
		if (tmp_res3 == 0) {
			HevcDecoder_Algo_Parser_vld_se_name(fifo, res, "pps_beta_offset_div2                    ");
			local_pps_id = pps_id;
			tmp_res4 = res[0];
			pps_beta_offset[local_pps_id] = tmp_res4 << 1;
			HevcDecoder_Algo_Parser_vld_se_name(fifo, res, "pps_tc_offset_div2                      ");
			local_pps_id = pps_id;
			tmp_res5 = res[0];
			pps_tc_offset[local_pps_id] = tmp_res5 << 1;
		}
	}
	HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "pps_scaling_list_data_present_flag      ");
	local_pps_id = pps_id;
	tmp_res6 = res[0];
	pps_scaling_list_data_present_flag[local_pps_id] = tmp_res6;
	local_pps_id = pps_id;
	tmp_pps_scaling_list_data_present_flag = pps_scaling_list_data_present_flag[local_pps_id];
	if (tmp_pps_scaling_list_data_present_flag == 0) {
		se_idx = 52;
	} else {
		se_idx = 50;
	}

	// Update ports indexes

}
static i32 isSchedulable_read_PPS_Header_se_idx_51() {
	i32 result;
	u16 local_se_idx;
	i32 tmp_isFifoFull;

	local_se_idx = se_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	result = local_se_idx == 52 && tmp_isFifoFull;
	return result;
}

static void read_PPS_Header_se_idx_51() {

	u32 res[1];
	u16 local_pps_id;
	u32 tmp_res;
	u32 tmp_res0;
	u32 tmp_res1;
	u32 tmp_res2;

	HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "lists_modification_present_flag         ");
	local_pps_id = pps_id;
	tmp_res = res[0];
	pps_lists_modification_present_flag[local_pps_id] = tmp_res;
	HevcDecoder_Algo_Parser_vld_ue_name(fifo, res, "log2_parallel_merge_level_minus2        ");
	local_pps_id = pps_id;
	tmp_res0 = res[0];
	pps_log2_parallel_merge_level[local_pps_id] = tmp_res0 + 2;
	HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "slice_segment_header_extension_present_flag");
	local_pps_id = pps_id;
	tmp_res1 = res[0];
	pps_slice_segment_header_extension_present_flag[local_pps_id] = tmp_res1;
	HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "pps_extension_flag                      ");
	tmp_res2 = res[0];
	if (tmp_res2 == 1) {
		printf("not support for pps_extension_flag != 0\n");
	}
	se_idx = 6;

	// Update ports indexes

}
static i32 isSchedulable_read_PPS_Header_se_idx_50() {
	i32 result;
	u16 local_se_idx;
	i32 tmp_isFifoFull;

	local_se_idx = se_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	result = local_se_idx == 50 && tmp_isFifoFull;
	return result;
}

static void read_PPS_Header_se_idx_50() {

	i32 matrixId;
	i32 i;
	u16 local_pps_id;
	i32 i0;
	u8 tmp_default_scaling_list_intra;
	u8 tmp_default_scaling_list_intra0;
	u8 tmp_default_scaling_list_intra1;
	u8 tmp_default_scaling_list_inter;
	u8 tmp_default_scaling_list_inter0;
	u8 tmp_default_scaling_list_inter1;
	u8 tmp_default_scaling_list_intra2;
	u8 tmp_default_scaling_list_intra3;
	u8 tmp_default_scaling_list_intra4;
	u8 tmp_default_scaling_list_inter2;
	u8 tmp_default_scaling_list_inter3;
	u8 tmp_default_scaling_list_inter4;
	u8 tmp_default_scaling_list_intra5;
	u8 tmp_default_scaling_list_inter5;

	matrixId = 0;
	while (matrixId <= 5) {
		i = 0;
		while (i <= 15) {
			local_pps_id = pps_id;
			pps_sl[local_pps_id][0][matrixId][i] = 16;
			i = i + 1;
		}
		local_pps_id = pps_id;
		pps_sl_dc[local_pps_id][0][matrixId] = 16;
		local_pps_id = pps_id;
		pps_sl_dc[local_pps_id][1][matrixId] = 16;
		matrixId = matrixId + 1;
	}
	i0 = 0;
	while (i0 <= 63) {
		local_pps_id = pps_id;
		tmp_default_scaling_list_intra = HevcDecoder_Algo_Parser_default_scaling_list_intra[i0];
		pps_sl[local_pps_id][1][0][i0] = tmp_default_scaling_list_intra;
		local_pps_id = pps_id;
		tmp_default_scaling_list_intra0 = HevcDecoder_Algo_Parser_default_scaling_list_intra[i0];
		pps_sl[local_pps_id][1][1][i0] = tmp_default_scaling_list_intra0;
		local_pps_id = pps_id;
		tmp_default_scaling_list_intra1 = HevcDecoder_Algo_Parser_default_scaling_list_intra[i0];
		pps_sl[local_pps_id][1][2][i0] = tmp_default_scaling_list_intra1;
		local_pps_id = pps_id;
		tmp_default_scaling_list_inter = HevcDecoder_Algo_Parser_default_scaling_list_inter[i0];
		pps_sl[local_pps_id][1][3][i0] = tmp_default_scaling_list_inter;
		local_pps_id = pps_id;
		tmp_default_scaling_list_inter0 = HevcDecoder_Algo_Parser_default_scaling_list_inter[i0];
		pps_sl[local_pps_id][1][4][i0] = tmp_default_scaling_list_inter0;
		local_pps_id = pps_id;
		tmp_default_scaling_list_inter1 = HevcDecoder_Algo_Parser_default_scaling_list_inter[i0];
		pps_sl[local_pps_id][1][5][i0] = tmp_default_scaling_list_inter1;
		local_pps_id = pps_id;
		tmp_default_scaling_list_intra2 = HevcDecoder_Algo_Parser_default_scaling_list_intra[i0];
		pps_sl[local_pps_id][2][0][i0] = tmp_default_scaling_list_intra2;
		local_pps_id = pps_id;
		tmp_default_scaling_list_intra3 = HevcDecoder_Algo_Parser_default_scaling_list_intra[i0];
		pps_sl[local_pps_id][2][1][i0] = tmp_default_scaling_list_intra3;
		local_pps_id = pps_id;
		tmp_default_scaling_list_intra4 = HevcDecoder_Algo_Parser_default_scaling_list_intra[i0];
		pps_sl[local_pps_id][2][2][i0] = tmp_default_scaling_list_intra4;
		local_pps_id = pps_id;
		tmp_default_scaling_list_inter2 = HevcDecoder_Algo_Parser_default_scaling_list_inter[i0];
		pps_sl[local_pps_id][2][3][i0] = tmp_default_scaling_list_inter2;
		local_pps_id = pps_id;
		tmp_default_scaling_list_inter3 = HevcDecoder_Algo_Parser_default_scaling_list_inter[i0];
		pps_sl[local_pps_id][2][4][i0] = tmp_default_scaling_list_inter3;
		local_pps_id = pps_id;
		tmp_default_scaling_list_inter4 = HevcDecoder_Algo_Parser_default_scaling_list_inter[i0];
		pps_sl[local_pps_id][2][5][i0] = tmp_default_scaling_list_inter4;
		local_pps_id = pps_id;
		tmp_default_scaling_list_intra5 = HevcDecoder_Algo_Parser_default_scaling_list_intra[i0];
		pps_sl[local_pps_id][3][0][i0] = tmp_default_scaling_list_intra5;
		local_pps_id = pps_id;
		tmp_default_scaling_list_inter5 = HevcDecoder_Algo_Parser_default_scaling_list_inter[i0];
		pps_sl[local_pps_id][3][1][i0] = tmp_default_scaling_list_inter5;
		i0 = i0 + 1;
	}
	se_idx = 51;

	// Update ports indexes

}
static i32 isSchedulable_read_PPS_Header_se_idx_51_loopSize_id() {
	i32 result;
	u16 local_se_idx;
	i32 tmp_isFifoFull;
	i32 local_pps_size_id;

	local_se_idx = se_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	local_pps_size_id = pps_size_id;
	result = local_se_idx == 51 && tmp_isFifoFull && local_pps_size_id < 4;
	return result;
}

static void read_PPS_Header_se_idx_51_loopSize_id() {

	i32 local_pps_size_id;

	local_pps_size_id = pps_size_id;
	if (local_pps_size_id == 3) {
		pps_size_id_matrixCase = 2;
	} else {
		pps_size_id_matrixCase = 6;
	}
	se_idx = 53;

	// Update ports indexes

}
static i32 isSchedulable_read_PPS_Header_se_idx_53_loopMatrix_id() {
	i32 result;
	u16 local_se_idx;
	i32 tmp_isFifoFull;
	i32 local_pps_matrix_id;
	i32 local_pps_size_id_matrixCase;

	local_se_idx = se_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	local_pps_matrix_id = pps_matrix_id;
	local_pps_size_id_matrixCase = pps_size_id_matrixCase;
	result = local_se_idx == 53 && tmp_isFifoFull && local_pps_matrix_id < local_pps_size_id_matrixCase;
	return result;
}

static void read_PPS_Header_se_idx_53_loopMatrix_id() {

	u32 res[1];
	i32 delta;
	i32 size_id_memcpyCase;
	u8 pps_scaling_list_pred_mode_flag[4][6];
	u32 pps_scaling_list_dc_coef[2][6];
	i32 local_pps_size_id;
	i32 local_pps_matrix_id;
	u32 tmp_res;
	u8 tmp_pps_scaling_list_pred_mode_flag;
	i32 k;
	u16 local_pps_id;
	u8 tmp_pps_sl;
	u8 tmp_pps_sl_dc;
	i32 tmp_min;
	u32 tmp_res0;
	u32 tmp_pps_scaling_list_dc_coef;
	i32 local_pps_next_coef;

	HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "scaling_list_pred_mode_flag             ");
	local_pps_size_id = pps_size_id;
	local_pps_matrix_id = pps_matrix_id;
	tmp_res = res[0];
	pps_scaling_list_pred_mode_flag[local_pps_size_id][local_pps_matrix_id] = tmp_res;
	local_pps_size_id = pps_size_id;
	local_pps_matrix_id = pps_matrix_id;
	tmp_pps_scaling_list_pred_mode_flag = pps_scaling_list_pred_mode_flag[local_pps_size_id][local_pps_matrix_id];
	if (tmp_pps_scaling_list_pred_mode_flag == 0) {
		HevcDecoder_Algo_Parser_vld_ue_name(fifo, res, "delta                                   ");
		delta = res[0];
		if (delta != 0) {
			local_pps_matrix_id = pps_matrix_id;
			if (local_pps_matrix_id - delta < 0) {
				printf("Invalid delta in scaling list data\n");
			}
			local_pps_size_id = pps_size_id;
			if (local_pps_size_id > 0) {
				size_id_memcpyCase = 64;
			} else {
				size_id_memcpyCase = 16;
			}
			k = 0;
			while (k <= size_id_memcpyCase) {
				local_pps_id = pps_id;
				local_pps_size_id = pps_size_id;
				local_pps_matrix_id = pps_matrix_id;
				local_pps_id = pps_id;
				local_pps_size_id = pps_size_id;
				local_pps_matrix_id = pps_matrix_id;
				tmp_pps_sl = pps_sl[local_pps_id][local_pps_size_id][local_pps_matrix_id - delta][k];
				pps_sl[local_pps_id][local_pps_size_id][local_pps_matrix_id][k] = tmp_pps_sl;
				k = k + 1;
			}
			local_pps_size_id = pps_size_id;
			if (local_pps_size_id > 1) {
				local_pps_id = pps_id;
				local_pps_size_id = pps_size_id;
				local_pps_matrix_id = pps_matrix_id;
				local_pps_id = pps_id;
				local_pps_size_id = pps_size_id;
				local_pps_matrix_id = pps_matrix_id;
				tmp_pps_sl_dc = pps_sl_dc[local_pps_id][local_pps_size_id - 2][local_pps_matrix_id - delta];
				pps_sl_dc[local_pps_id][local_pps_size_id - 2][local_pps_matrix_id] = tmp_pps_sl_dc;
			}
		}
		local_pps_matrix_id = pps_matrix_id;
		pps_matrix_id = local_pps_matrix_id + 1;
	} else {
		pps_next_coef = 8;
		local_pps_size_id = pps_size_id;
		tmp_min = HevcDecoder_Algo_Parser_min(64, 1 << (4 + (local_pps_size_id << 1)));
		pps_coef_num = tmp_min;
		local_pps_size_id = pps_size_id;
		if (local_pps_size_id > 1) {
			HevcDecoder_Algo_Parser_vld_se_name(fifo, res, "scaling_list_dc_coef                    ");
			local_pps_size_id = pps_size_id;
			local_pps_matrix_id = pps_matrix_id;
			tmp_res0 = res[0];
			pps_scaling_list_dc_coef[local_pps_size_id - 2][local_pps_matrix_id] = tmp_res0 + 8;
			local_pps_size_id = pps_size_id;
			local_pps_matrix_id = pps_matrix_id;
			tmp_pps_scaling_list_dc_coef = pps_scaling_list_dc_coef[local_pps_size_id - 2][local_pps_matrix_id];
			pps_next_coef = tmp_pps_scaling_list_dc_coef;
			local_pps_id = pps_id;
			local_pps_size_id = pps_size_id;
			local_pps_matrix_id = pps_matrix_id;
			local_pps_next_coef = pps_next_coef;
			pps_sl_dc[local_pps_id][local_pps_size_id - 2][local_pps_matrix_id] = local_pps_next_coef;
		}
		se_idx = 54;
		cnt_i = 0;
	}

	// Update ports indexes

}
static i32 isSchedulable_read_PPS_Header_se_idx_54_loopNumCoef() {
	i32 result;
	u16 local_se_idx;
	i32 tmp_isFifoFull;
	u32 local_cnt_i;
	i32 local_pps_coef_num;

	local_se_idx = se_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	local_cnt_i = cnt_i;
	local_pps_coef_num = pps_coef_num;
	result = local_se_idx == 54 && tmp_isFifoFull && local_cnt_i < local_pps_coef_num;
	return result;
}

static void read_PPS_Header_se_idx_54_loopNumCoef() {

	u32 res[1];
	i32 local_pps_size_id;
	u32 local_cnt_i;
	i8 tmp_hevc_diag_scan4x4_y;
	u8 tmp_hevc_diag_scan4x4_x;
	i8 tmp_hevc_diag_scan8x8_y;
	i8 tmp_hevc_diag_scan8x8_x;
	u32 tmp_res;
	i32 local_pps_next_coef;
	i32 local_pps_scaling_list_delta_coef;
	u16 local_pps_id;
	i32 local_pps_matrix_id;
	i32 local_pps_pos;

	local_pps_size_id = pps_size_id;
	if (local_pps_size_id == 0) {
		local_cnt_i = cnt_i;
		tmp_hevc_diag_scan4x4_y = HevcDecoder_Algo_Parser_hevc_diag_scan4x4_y[local_cnt_i];
		local_cnt_i = cnt_i;
		tmp_hevc_diag_scan4x4_x = HevcDecoder_Algo_Parser_hevc_diag_scan4x4_x[local_cnt_i];
		pps_pos = 4 * tmp_hevc_diag_scan4x4_y + tmp_hevc_diag_scan4x4_x;
	} else {
		local_cnt_i = cnt_i;
		tmp_hevc_diag_scan8x8_y = HevcDecoder_Algo_Parser_hevc_diag_scan8x8_y[local_cnt_i];
		local_cnt_i = cnt_i;
		tmp_hevc_diag_scan8x8_x = HevcDecoder_Algo_Parser_hevc_diag_scan8x8_x[local_cnt_i];
		pps_pos = 8 * tmp_hevc_diag_scan8x8_y + tmp_hevc_diag_scan8x8_x;
	}
	HevcDecoder_Algo_Parser_vld_se_name(fifo, res, "scaling_list_delta_coef                 ");
	tmp_res = res[0];
	pps_scaling_list_delta_coef = tmp_res;
	local_pps_next_coef = pps_next_coef;
	local_pps_scaling_list_delta_coef = pps_scaling_list_delta_coef;
	pps_next_coef = local_pps_next_coef + local_pps_scaling_list_delta_coef + 256 & 255;
	local_pps_id = pps_id;
	local_pps_size_id = pps_size_id;
	local_pps_matrix_id = pps_matrix_id;
	local_pps_pos = pps_pos;
	local_pps_next_coef = pps_next_coef;
	pps_sl[local_pps_id][local_pps_size_id][local_pps_matrix_id][local_pps_pos] = local_pps_next_coef;
	local_cnt_i = cnt_i;
	cnt_i = local_cnt_i + 1;

	// Update ports indexes

}
static i32 isSchedulable_read_PPS_Header_se_idx_54_loopNumCoefEnd() {
	i32 result;
	u16 local_se_idx;
	i32 tmp_isFifoFull;
	u32 local_cnt_i;
	i32 local_pps_coef_num;

	local_se_idx = se_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	local_cnt_i = cnt_i;
	local_pps_coef_num = pps_coef_num;
	result = local_se_idx == 54 && tmp_isFifoFull && local_cnt_i == local_pps_coef_num;
	return result;
}

static void read_PPS_Header_se_idx_54_loopNumCoefEnd() {

	i32 local_pps_matrix_id;

	cnt_i = 0;
	local_pps_matrix_id = pps_matrix_id;
	pps_matrix_id = local_pps_matrix_id + 1;
	se_idx = 53;

	// Update ports indexes

}
static i32 isSchedulable_read_PPS_Header_se_idx_53_loopMatrix_id_End() {
	i32 result;
	u16 local_se_idx;
	i32 tmp_isFifoFull;
	i32 local_pps_matrix_id;
	i32 local_pps_size_id_matrixCase;

	local_se_idx = se_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	local_pps_matrix_id = pps_matrix_id;
	local_pps_size_id_matrixCase = pps_size_id_matrixCase;
	result = local_se_idx == 53 && tmp_isFifoFull && local_pps_matrix_id == local_pps_size_id_matrixCase;
	return result;
}

static void read_PPS_Header_se_idx_53_loopMatrix_id_End() {

	i32 local_pps_size_id;

	local_pps_size_id = pps_size_id;
	pps_size_id = local_pps_size_id + 1;
	pps_matrix_id = 0;
	se_idx = 51;

	// Update ports indexes

}
static i32 isSchedulable_read_PPS_Header_se_idx_51_loopSize_id_End() {
	i32 result;
	u16 local_se_idx;
	i32 tmp_isFifoFull;
	i32 local_pps_size_id;

	local_se_idx = se_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	local_pps_size_id = pps_size_id;
	result = local_se_idx == 51 && tmp_isFifoFull && local_pps_size_id == 4;
	return result;
}

static void read_PPS_Header_se_idx_51_loopSize_id_End() {


	pps_size_id = 0;
	se_idx = 52;

	// Update ports indexes

}
static i32 isSchedulable_read_PPS_Header_done() {
	i32 result;
	u16 local_se_idx;

	local_se_idx = se_idx;
	result = local_se_idx == 6;
	return result;
}

static void read_PPS_Header_done() {



	// Update ports indexes

}
static i32 isSchedulable_read_SliceHeader_se_idx_1() {
	i32 result;
	u16 local_se_idx;
	i32 local_idx;
	i32 tmp_isFifoFull;

	local_se_idx = se_idx;
	local_idx = idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	result = local_se_idx == 1 && local_idx == 0 && tmp_isFifoFull;
	return result;
}

static void read_SliceHeader_se_idx_1() {

	u32 res[1];
	u8 part_mode;
	u16 local_sps_id;
	u8 tmp_sps_log2_min_coding_block_size;
	u8 local_Log2MinCbSize;
	u8 tmp_sps_log2_diff_max_min_coding_block_size;
	u16 tmp_sps_pic_width_in_luma_samples;
	u8 local_Log2CtbSize;
	u16 tmp_sps_pic_height_in_luma_samples;
	u16 local_PicWidthInCtbsY;
	u16 local_PicHeightInCtbsY;
	u32 local_TILE_SPLIT_ENABLE;
	u32 local_TILE_INDEX;
	u32 tmp_res;
	u8 local_nal_unit_type;
	u32 tmp_res0;
	u32 tmp_res1;
	u16 local_pps_id;
	u8 tmp_pps_sps_id;
	u8 local_first_slice_segment_in_pic_flag;
	u8 tmp_pps_dependent_slice_segments_enabled_flag;
	u32 tmp_res2;
	u16 local_PicSizeInCtbsY;
	i32 tmp_log2;
	u32 tmp_res3;
	u8 local_dependent_slice_segment_flag;
	u32 local_slice_segment_address;
	i32 local_slice_idx;
	u16 tmp_sps_pic_width_in_luma_samples0;
	u16 tmp_sps_pic_height_in_luma_samples0;
	u8 local_PART_MODE_PICT;
	u8 local_PART_MODE_SLICE_INDEP;
	u8 local_PART_MODE_SLICE_DEP;

	local_sps_id = sps_id;
	tmp_sps_log2_min_coding_block_size = sps_log2_min_coding_block_size[local_sps_id];
	Log2MinCbSize = tmp_sps_log2_min_coding_block_size;
	local_Log2MinCbSize = Log2MinCbSize;
	local_sps_id = sps_id;
	tmp_sps_log2_diff_max_min_coding_block_size = sps_log2_diff_max_min_coding_block_size[local_sps_id];
	Log2CtbSize = local_Log2MinCbSize + tmp_sps_log2_diff_max_min_coding_block_size;
	local_sps_id = sps_id;
	tmp_sps_pic_width_in_luma_samples = sps_pic_width_in_luma_samples[local_sps_id];
	local_Log2CtbSize = Log2CtbSize;
	local_Log2CtbSize = Log2CtbSize;
	PicWidthInCtbsY = (tmp_sps_pic_width_in_luma_samples + (1 << local_Log2CtbSize) - 1) >> local_Log2CtbSize;
	local_sps_id = sps_id;
	tmp_sps_pic_height_in_luma_samples = sps_pic_height_in_luma_samples[local_sps_id];
	local_Log2CtbSize = Log2CtbSize;
	local_Log2CtbSize = Log2CtbSize;
	PicHeightInCtbsY = (tmp_sps_pic_height_in_luma_samples + (1 << local_Log2CtbSize) - 1) >> local_Log2CtbSize;
	local_PicWidthInCtbsY = PicWidthInCtbsY;
	local_PicHeightInCtbsY = PicHeightInCtbsY;
	PicSizeInCtbsY = local_PicWidthInCtbsY * local_PicHeightInCtbsY;
	local_TILE_SPLIT_ENABLE = TILE_SPLIT_ENABLE;
	TilesInfo[0] = local_TILE_SPLIT_ENABLE;
	local_TILE_INDEX = TILE_INDEX;
	TilesInfo[1] = local_TILE_INDEX;
	HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "first_slice_segment_in_pic_flag         ");
	tmp_res = res[0];
	first_slice_segment_in_pic_flag = tmp_res;
	no_output_of_prior_pics_flag = 0;
	local_nal_unit_type = nal_unit_type;
	local_nal_unit_type = nal_unit_type;
	if (local_nal_unit_type >= 16 && local_nal_unit_type <= 23) {
		HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "no_output_of_prior_pics_flag            ");
		tmp_res0 = res[0];
		no_output_of_prior_pics_flag = tmp_res0;
	}
	HevcDecoder_Algo_Parser_vld_ue_name(fifo, res, "slice_pic_parameter_set_id              ");
	tmp_res1 = res[0];
	pps_id = tmp_res1;
	local_pps_id = pps_id;
	tmp_pps_sps_id = pps_sps_id[local_pps_id];
	sps_id = tmp_pps_sps_id;
	dependent_slice_segment_flag = 0;
	local_first_slice_segment_in_pic_flag = first_slice_segment_in_pic_flag;
	if (local_first_slice_segment_in_pic_flag == 0) {
		local_pps_id = pps_id;
		tmp_pps_dependent_slice_segments_enabled_flag = pps_dependent_slice_segments_enabled_flag[local_pps_id];
		if (tmp_pps_dependent_slice_segments_enabled_flag == 1) {
			HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "dependent_slice_segment_flag                    ");
			tmp_res2 = res[0];
			dependent_slice_segment_flag = tmp_res2;
		}
		local_PicSizeInCtbsY = PicSizeInCtbsY;
		tmp_log2 = HevcDecoder_Algo_Parser_log2((local_PicSizeInCtbsY - 1) << 1);
		HevcDecoder_Algo_Parser_vld_u_name(tmp_log2, fifo, res, "slice_segment_address                   ");
		tmp_res3 = res[0];
		slice_segment_address = tmp_res3;
		local_dependent_slice_segment_flag = dependent_slice_segment_flag;
		if (local_dependent_slice_segment_flag == 0) {
			local_slice_segment_address = slice_segment_address;
			slice_addr = local_slice_segment_address;
			local_slice_idx = slice_idx;
			slice_idx = local_slice_idx + 1;
		}
	} else {
		slice_segment_address = 0;
		slice_addr = 0;
	}
	local_sps_id = sps_id;
	tmp_sps_pic_width_in_luma_samples0 = sps_pic_width_in_luma_samples[local_sps_id];
	pictSize[0] = tmp_sps_pic_width_in_luma_samples0;
	local_sps_id = sps_id;
	tmp_sps_pic_height_in_luma_samples0 = sps_pic_height_in_luma_samples[local_sps_id];
	pictSize[1] = tmp_sps_pic_height_in_luma_samples0;
	local_first_slice_segment_in_pic_flag = first_slice_segment_in_pic_flag;
	if (local_first_slice_segment_in_pic_flag == 1) {
		local_PART_MODE_PICT = HevcDecoder_Algo_Parser_PART_MODE_PICT;
		part_mode = local_PART_MODE_PICT;
	} else {
		local_dependent_slice_segment_flag = dependent_slice_segment_flag;
		if (local_dependent_slice_segment_flag == 0) {
			local_PART_MODE_SLICE_INDEP = HevcDecoder_Algo_Parser_PART_MODE_SLICE_INDEP;
			part_mode = local_PART_MODE_SLICE_INDEP;
		} else {
			local_PART_MODE_SLICE_DEP = HevcDecoder_Algo_Parser_PART_MODE_SLICE_DEP;
			part_mode = local_PART_MODE_SLICE_DEP;
		}
	}
	local_dependent_slice_segment_flag = dependent_slice_segment_flag;
	if (local_dependent_slice_segment_flag == 0) {
		se_idx = 200;
	} else {
		se_idx = 6;
	}
	tokens_PartMode[(index_PartMode + (0)) % SIZE_PartMode] = part_mode;

	// Update ports indexes
	index_PartMode += 1;

}
static i32 isSchedulable_read_SliceHeader_se_idx_11() {
	i32 result;
	u16 local_se_idx;
	i32 tmp_isFifoFull;

	local_se_idx = se_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	result = local_se_idx == 200 && tmp_isFifoFull;
	return result;
}

static void read_SliceHeader_se_idx_11() {

	u32 res[1];
	u8 numbits;
	i32 i;
	u16 local_pps_id;
	u8 tmp_pps_num_extra_slice_header_bits;
	u32 tmp_res;
	u8 tmp_pps_output_flag_present_flag;
	u32 tmp_res0;
	u16 local_sps_id;
	u8 tmp_sps_separate_colour_plane_flag;
	u8 local_nal_unit_type;
	u8 local_NAL_IDR_W_DLP;
	u8 local_NAL_IDR_N_LP;
	u8 tmp_sps_log2_max_pic_order_cnt_lsb_minus4;
	u32 tmp_res1;
	u32 tmp_res2;
	u32 tmp_res3;
	u8 local_short_term_ref_pic_set_sps_flag;
	u8 tmp_sps_num_short_term_ref_pic_sets;
	u8 tmp_sps_num_short_term_ref_pic_sets0;
	i32 i0;
	u8 local_PC_RPS_STRUCT_SIZE;
	u32 tmp_res4;
	i8 tmp_pcRPS;
	i32 local_poc;
	u8 local_slice_type;
	u8 local_Log2CtbSize;

	numbits = 0;
	i = 0;
	local_pps_id = pps_id;
	tmp_pps_num_extra_slice_header_bits = pps_num_extra_slice_header_bits[local_pps_id];
	while (i <= tmp_pps_num_extra_slice_header_bits - 1) {
		HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "slice_reserved_undetermined_flag[i]     ");
		i = i + 1;
	}
	HevcDecoder_Algo_Parser_vld_ue_name(fifo, res, "slice_type                              ");
	tmp_res = res[0];
	slice_type = tmp_res;
	slice_temporal_mvp_enable_flag = 0;
	idx = 0;
	pic_output_flag = 1;
	local_pps_id = pps_id;
	tmp_pps_output_flag_present_flag = pps_output_flag_present_flag[local_pps_id];
	if (tmp_pps_output_flag_present_flag == 1) {
		HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "pic_output_flag                         ");
		tmp_res0 = res[0];
		pic_output_flag = tmp_res0;
	}
	local_sps_id = sps_id;
	tmp_sps_separate_colour_plane_flag = sps_separate_colour_plane_flag[local_sps_id];
	if (tmp_sps_separate_colour_plane_flag == 1) {
		HevcDecoder_Algo_Parser_vld_u_name(2, fifo, res, "colour_plane_id                         ");
	}
	local_nal_unit_type = nal_unit_type;
	local_NAL_IDR_W_DLP = HevcDecoder_Algo_Parser_NAL_IDR_W_DLP;
	local_nal_unit_type = nal_unit_type;
	local_NAL_IDR_N_LP = HevcDecoder_Algo_Parser_NAL_IDR_N_LP;
	if (local_nal_unit_type == local_NAL_IDR_W_DLP || local_nal_unit_type == local_NAL_IDR_N_LP) {
		poc = 0;
		se_idx = 302;
	} else {
		local_sps_id = sps_id;
		tmp_sps_log2_max_pic_order_cnt_lsb_minus4 = sps_log2_max_pic_order_cnt_lsb_minus4[local_sps_id];
		HevcDecoder_Algo_Parser_vld_u_name(tmp_sps_log2_max_pic_order_cnt_lsb_minus4 + 4, fifo, res, "pic_order_cnt_lsb                       ");
		tmp_res1 = res[0];
		pic_order_cnt_lsb = tmp_res1;
		tmp_res2 = res[0];
		compute_POC(tmp_res2);
		HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "short_term_ref_pic_set_sps_flag         ");
		tmp_res3 = res[0];
		short_term_ref_pic_set_sps_flag = tmp_res3;
		local_short_term_ref_pic_set_sps_flag = short_term_ref_pic_set_sps_flag;
		if (local_short_term_ref_pic_set_sps_flag != 0) {
			local_sps_id = sps_id;
			tmp_sps_num_short_term_ref_pic_sets = sps_num_short_term_ref_pic_sets[local_sps_id];
			while (1 << numbits < tmp_sps_num_short_term_ref_pic_sets) {
				numbits = numbits + 1;
				local_sps_id = sps_id;
				tmp_sps_num_short_term_ref_pic_sets = sps_num_short_term_ref_pic_sets[local_sps_id];
			}
			res[0] = 0;
			if (numbits > 0) {
				HevcDecoder_Algo_Parser_vld_u_name(numbits, fifo, res, "short_term_ref_pic_set_idx              ");
			}
			local_sps_id = sps_id;
			local_sps_id = sps_id;
			tmp_sps_num_short_term_ref_pic_sets0 = sps_num_short_term_ref_pic_sets[local_sps_id];
			i0 = 0;
			local_PC_RPS_STRUCT_SIZE = HevcDecoder_Algo_Parser_PC_RPS_STRUCT_SIZE;
			while (i0 <= local_PC_RPS_STRUCT_SIZE - 1) {
				local_sps_id = sps_id;
				tmp_res4 = res[0];
				tmp_pcRPS = pcRPS[local_sps_id][tmp_res4][i0];
				pcRPS[local_sps_id][tmp_sps_num_short_term_ref_pic_sets0][i0] = tmp_pcRPS;
				i0 = i0 + 1;
			}
			se_idx = 301;
		} else {
			se_idx = 300;
		}
	}
	local_poc = poc;
	tokens_Poc[(index_Poc + (0)) % SIZE_Poc] = local_poc;
	local_slice_type = slice_type;
	tokens_SliceType[(index_SliceType + (0)) % SIZE_SliceType] = local_slice_type;
	local_Log2CtbSize = Log2CtbSize;
	tokens_LcuSizeMax[(index_LcuSizeMax + (0)) % SIZE_LcuSizeMax] = local_Log2CtbSize;

	// Update ports indexes
	index_Poc += 1;
	index_SliceType += 1;
	index_LcuSizeMax += 1;

}
static i32 isSchedulable_read_SliceHeader_se_idx_12() {
	i32 result;
	u16 local_se_idx;
	i32 tmp_isFifoFull;

	local_se_idx = se_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	result = local_se_idx == 300 && tmp_isFifoFull;
	return result;
}

static void read_SliceHeader_se_idx_12() {

	u32 res[1];
	u8 inter_rps_flag;
	u16 delta_idx;
	u8 rIdx;
	i32 deltaRPS;
	i32 deltaPOC;
	i32 k;
	i32 k0;
	i32 k1;
	i32 delta_rps_sign;
	i32 abs_delta_rps;
	u16 local_sps_id;
	u8 tmp_sps_num_short_term_ref_pic_sets;
	u32 tmp_res;
	u8 tmp_sps_num_short_term_ref_pic_sets0;
	u32 tmp_res0;
	u8 i;
	u8 local_NUM_PICS;
	i8 tmp_pcRPS;
	u32 tmp_res1;
	u32 tmp_res2;
	u32 tmp_res3;
	u32 tmp_res4;
	i8 tmp_pcRPS0;
	u8 local_DELTAPOC;
	i8 tmp_pcRPS1;
	u8 tmp_sps_num_short_term_ref_pic_sets1;
	u8 tmp_sps_num_short_term_ref_pic_sets2;
	u8 local_USED;
	u32 tmp_res5;
	u8 tmp_sps_num_short_term_ref_pic_sets3;
	u8 tmp_sps_num_short_term_ref_pic_sets4;
	u8 local_NUM_NEGATIVE_PICS;
	u8 tmp_sps_num_short_term_ref_pic_sets5;
	u8 local_NUM_POSITIVE_PICS;
	u8 tmp_sps_num_short_term_ref_pic_sets6;
	u8 tmp_sps_num_short_term_ref_pic_sets7;
	u32 tmp_res6;
	u8 tmp_sps_num_short_term_ref_pic_sets8;
	u32 tmp_res7;
	u8 tmp_sps_num_short_term_ref_pic_sets9;
	u8 tmp_sps_num_short_term_ref_pic_sets10;
	i8 tmp_pcRPS2;
	u32 tmp_res8;
	u8 tmp_sps_num_short_term_ref_pic_sets11;
	i8 tmp_pcRPS3;
	u8 tmp_sps_num_short_term_ref_pic_sets12;
	i8 tmp_pcRPS4;
	u8 tmp_sps_num_short_term_ref_pic_sets13;
	i8 tmp_pcRPS5;

	inter_rps_flag = 0;
	delta_idx = 1;
	k = 0;
	k0 = 0;
	k1 = 0;
	prev = 0;
	cnt_i = 0;
	se_idx = 301;
	local_sps_id = sps_id;
	tmp_sps_num_short_term_ref_pic_sets = sps_num_short_term_ref_pic_sets[local_sps_id];
	if (tmp_sps_num_short_term_ref_pic_sets != 0) {
		HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "inter_ref_pic_set_prediction_flag       ");
		inter_rps_flag = res[0];
	}
	if (inter_rps_flag == 1) {
		HevcDecoder_Algo_Parser_vld_ue_name(fifo, res, "delta_idx_minus1                        ");
		tmp_res = res[0];
		delta_idx = tmp_res + 1;
		local_sps_id = sps_id;
		tmp_sps_num_short_term_ref_pic_sets0 = sps_num_short_term_ref_pic_sets[local_sps_id];
		rIdx = tmp_sps_num_short_term_ref_pic_sets0 - delta_idx;
		HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "delta_rps_sign                          ");
		delta_rps_sign = res[0];
		HevcDecoder_Algo_Parser_vld_ue_name(fifo, res, "abs_delta_rps_minus1                    ");
		tmp_res0 = res[0];
		abs_delta_rps = tmp_res0 + 1;
		deltaRPS = (1 - (delta_rps_sign << 1)) * abs_delta_rps;
		i = 0;
		local_sps_id = sps_id;
		local_NUM_PICS = HevcDecoder_Algo_Parser_NUM_PICS;
		tmp_pcRPS = pcRPS[local_sps_id][rIdx][local_NUM_PICS];
		while (i <= tmp_pcRPS) {
			HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "used_by_curr_pic_flag                   ");
			tmp_res1 = res[0];
			if (tmp_res1 == 0) {
				HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "use_delta_flag                          ");
				tmp_res2 = res[0];
				res[0] = tmp_res2 << 1;
			}
			tmp_res3 = res[0];
			tmp_res4 = res[0];
			if (tmp_res3 == 1 || tmp_res4 == 2) {
				local_sps_id = sps_id;
				local_NUM_PICS = HevcDecoder_Algo_Parser_NUM_PICS;
				tmp_pcRPS0 = pcRPS[local_sps_id][rIdx][local_NUM_PICS];
				if (i < tmp_pcRPS0) {
					local_sps_id = sps_id;
					local_DELTAPOC = HevcDecoder_Algo_Parser_DELTAPOC;
					tmp_pcRPS1 = pcRPS[local_sps_id][rIdx][local_DELTAPOC + i];
					deltaPOC = deltaRPS + tmp_pcRPS1;
				} else {
					deltaPOC = deltaRPS;
				}
				local_sps_id = sps_id;
				local_sps_id = sps_id;
				tmp_sps_num_short_term_ref_pic_sets1 = sps_num_short_term_ref_pic_sets[local_sps_id];
				local_DELTAPOC = HevcDecoder_Algo_Parser_DELTAPOC;
				pcRPS[local_sps_id][tmp_sps_num_short_term_ref_pic_sets1][local_DELTAPOC + k] = deltaPOC;
				local_sps_id = sps_id;
				local_sps_id = sps_id;
				tmp_sps_num_short_term_ref_pic_sets2 = sps_num_short_term_ref_pic_sets[local_sps_id];
				local_USED = HevcDecoder_Algo_Parser_USED;
				tmp_res5 = res[0];
				if (tmp_res5 == 1) {
					pcRPS[local_sps_id][tmp_sps_num_short_term_ref_pic_sets2][local_USED + k] = 1;
				} else {
					pcRPS[local_sps_id][tmp_sps_num_short_term_ref_pic_sets2][local_USED + k] = 0;
				}
				if (deltaPOC < 0) {
					k0 = k0 + 1;
				} else {
					k1 = k1 + 1;
				}
				k = k + 1;
			}
			i = i + 1;
		}
		local_sps_id = sps_id;
		local_sps_id = sps_id;
		tmp_sps_num_short_term_ref_pic_sets3 = sps_num_short_term_ref_pic_sets[local_sps_id];
		local_NUM_PICS = HevcDecoder_Algo_Parser_NUM_PICS;
		pcRPS[local_sps_id][tmp_sps_num_short_term_ref_pic_sets3][local_NUM_PICS] = k;
		local_sps_id = sps_id;
		local_sps_id = sps_id;
		tmp_sps_num_short_term_ref_pic_sets4 = sps_num_short_term_ref_pic_sets[local_sps_id];
		local_NUM_NEGATIVE_PICS = HevcDecoder_Algo_Parser_NUM_NEGATIVE_PICS;
		pcRPS[local_sps_id][tmp_sps_num_short_term_ref_pic_sets4][local_NUM_NEGATIVE_PICS] = k0;
		local_sps_id = sps_id;
		local_sps_id = sps_id;
		tmp_sps_num_short_term_ref_pic_sets5 = sps_num_short_term_ref_pic_sets[local_sps_id];
		local_NUM_POSITIVE_PICS = HevcDecoder_Algo_Parser_NUM_POSITIVE_PICS;
		pcRPS[local_sps_id][tmp_sps_num_short_term_ref_pic_sets5][local_NUM_POSITIVE_PICS] = k1;
		local_sps_id = sps_id;
		local_sps_id = sps_id;
		tmp_sps_num_short_term_ref_pic_sets6 = sps_num_short_term_ref_pic_sets[local_sps_id];
		HevcDecoder_Algo_Parser_sortDeltaPOC(local_sps_id, tmp_sps_num_short_term_ref_pic_sets6, pcRPS);
	} else {
		HevcDecoder_Algo_Parser_vld_ue_name(fifo, res, "num_negative_pics                       ");
		local_sps_id = sps_id;
		local_sps_id = sps_id;
		tmp_sps_num_short_term_ref_pic_sets7 = sps_num_short_term_ref_pic_sets[local_sps_id];
		local_NUM_NEGATIVE_PICS = HevcDecoder_Algo_Parser_NUM_NEGATIVE_PICS;
		tmp_res6 = res[0];
		pcRPS[local_sps_id][tmp_sps_num_short_term_ref_pic_sets7][local_NUM_NEGATIVE_PICS] = tmp_res6;
		HevcDecoder_Algo_Parser_vld_ue_name(fifo, res, "num_positive_pics                       ");
		local_sps_id = sps_id;
		local_sps_id = sps_id;
		tmp_sps_num_short_term_ref_pic_sets8 = sps_num_short_term_ref_pic_sets[local_sps_id];
		local_NUM_POSITIVE_PICS = HevcDecoder_Algo_Parser_NUM_POSITIVE_PICS;
		tmp_res7 = res[0];
		pcRPS[local_sps_id][tmp_sps_num_short_term_ref_pic_sets8][local_NUM_POSITIVE_PICS] = tmp_res7;
		local_sps_id = sps_id;
		local_sps_id = sps_id;
		tmp_sps_num_short_term_ref_pic_sets9 = sps_num_short_term_ref_pic_sets[local_sps_id];
		local_NUM_PICS = HevcDecoder_Algo_Parser_NUM_PICS;
		local_sps_id = sps_id;
		local_sps_id = sps_id;
		tmp_sps_num_short_term_ref_pic_sets10 = sps_num_short_term_ref_pic_sets[local_sps_id];
		local_NUM_NEGATIVE_PICS = HevcDecoder_Algo_Parser_NUM_NEGATIVE_PICS;
		tmp_pcRPS2 = pcRPS[local_sps_id][tmp_sps_num_short_term_ref_pic_sets10][local_NUM_NEGATIVE_PICS];
		tmp_res8 = res[0];
		pcRPS[local_sps_id][tmp_sps_num_short_term_ref_pic_sets9][local_NUM_PICS] = tmp_pcRPS2 + tmp_res8;
		local_sps_id = sps_id;
		local_sps_id = sps_id;
		tmp_sps_num_short_term_ref_pic_sets11 = sps_num_short_term_ref_pic_sets[local_sps_id];
		local_NUM_NEGATIVE_PICS = HevcDecoder_Algo_Parser_NUM_NEGATIVE_PICS;
		tmp_pcRPS3 = pcRPS[local_sps_id][tmp_sps_num_short_term_ref_pic_sets11][local_NUM_NEGATIVE_PICS];
		if (tmp_pcRPS3 != 0) {
			se_idx = 310;
		} else {
			prev = 0;
			local_sps_id = sps_id;
			local_sps_id = sps_id;
			tmp_sps_num_short_term_ref_pic_sets12 = sps_num_short_term_ref_pic_sets[local_sps_id];
			local_NUM_POSITIVE_PICS = HevcDecoder_Algo_Parser_NUM_POSITIVE_PICS;
			tmp_pcRPS4 = pcRPS[local_sps_id][tmp_sps_num_short_term_ref_pic_sets12][local_NUM_POSITIVE_PICS];
			if (tmp_pcRPS4 != 0) {
				se_idx = 320;
				local_sps_id = sps_id;
				local_sps_id = sps_id;
				tmp_sps_num_short_term_ref_pic_sets13 = sps_num_short_term_ref_pic_sets[local_sps_id];
				local_NUM_NEGATIVE_PICS = HevcDecoder_Algo_Parser_NUM_NEGATIVE_PICS;
				tmp_pcRPS5 = pcRPS[local_sps_id][tmp_sps_num_short_term_ref_pic_sets13][local_NUM_NEGATIVE_PICS];
				cnt_i = tmp_pcRPS5;
			}
		}
	}

	// Update ports indexes

}
static i32 isSchedulable_read_SliceHeader_se_idx_12_loop1() {
	i32 result;
	u16 local_se_idx;
	i32 tmp_isFifoFull;
	u32 local_cnt_i;
	u16 local_sps_id;
	u8 tmp_sps_num_short_term_ref_pic_sets;
	u8 local_NUM_NEGATIVE_PICS;
	i8 tmp_pcRPS;

	local_se_idx = se_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	local_cnt_i = cnt_i;
	local_sps_id = sps_id;
	local_sps_id = sps_id;
	tmp_sps_num_short_term_ref_pic_sets = sps_num_short_term_ref_pic_sets[local_sps_id];
	local_NUM_NEGATIVE_PICS = HevcDecoder_Algo_Parser_NUM_NEGATIVE_PICS;
	tmp_pcRPS = pcRPS[local_sps_id][tmp_sps_num_short_term_ref_pic_sets][local_NUM_NEGATIVE_PICS];
	result = local_se_idx == 310 && tmp_isFifoFull && local_cnt_i < tmp_pcRPS;
	return result;
}

static void read_SliceHeader_se_idx_12_loop1() {

	u32 res[1];
	i32 local_prev;
	u32 tmp_res;
	u16 local_sps_id;
	u8 tmp_sps_num_short_term_ref_pic_sets;
	u8 local_DELTAPOC;
	u32 local_cnt_i;
	u8 tmp_sps_num_short_term_ref_pic_sets0;
	u8 local_USED;
	u32 tmp_res0;

	HevcDecoder_Algo_Parser_vld_ue_name(fifo, res, "delta_poc_s0_minus1                     ");
	local_prev = prev;
	tmp_res = res[0];
	prev = local_prev - tmp_res - 1;
	local_sps_id = sps_id;
	local_sps_id = sps_id;
	tmp_sps_num_short_term_ref_pic_sets = sps_num_short_term_ref_pic_sets[local_sps_id];
	local_DELTAPOC = HevcDecoder_Algo_Parser_DELTAPOC;
	local_cnt_i = cnt_i;
	local_prev = prev;
	pcRPS[local_sps_id][tmp_sps_num_short_term_ref_pic_sets][local_DELTAPOC + local_cnt_i] = local_prev;
	HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "used_by_curr_pic_s0_flag                ");
	local_sps_id = sps_id;
	local_sps_id = sps_id;
	tmp_sps_num_short_term_ref_pic_sets0 = sps_num_short_term_ref_pic_sets[local_sps_id];
	local_USED = HevcDecoder_Algo_Parser_USED;
	local_cnt_i = cnt_i;
	tmp_res0 = res[0];
	pcRPS[local_sps_id][tmp_sps_num_short_term_ref_pic_sets0][local_USED + local_cnt_i] = tmp_res0;
	local_cnt_i = cnt_i;
	cnt_i = local_cnt_i + 1;

	// Update ports indexes

}
static i32 isSchedulable_read_SliceHeader_se_idx_12_end_loop1() {
	i32 result;
	u16 local_se_idx;
	u32 local_cnt_i;
	u16 local_sps_id;
	u8 tmp_sps_num_short_term_ref_pic_sets;
	u8 local_NUM_NEGATIVE_PICS;
	i8 tmp_pcRPS;

	local_se_idx = se_idx;
	local_cnt_i = cnt_i;
	local_sps_id = sps_id;
	local_sps_id = sps_id;
	tmp_sps_num_short_term_ref_pic_sets = sps_num_short_term_ref_pic_sets[local_sps_id];
	local_NUM_NEGATIVE_PICS = HevcDecoder_Algo_Parser_NUM_NEGATIVE_PICS;
	tmp_pcRPS = pcRPS[local_sps_id][tmp_sps_num_short_term_ref_pic_sets][local_NUM_NEGATIVE_PICS];
	result = local_se_idx == 310 && local_cnt_i == tmp_pcRPS;
	return result;
}

static void read_SliceHeader_se_idx_12_end_loop1() {

	u16 local_sps_id;
	u8 tmp_sps_num_short_term_ref_pic_sets;
	u8 local_NUM_POSITIVE_PICS;
	i8 tmp_pcRPS;

	local_sps_id = sps_id;
	local_sps_id = sps_id;
	tmp_sps_num_short_term_ref_pic_sets = sps_num_short_term_ref_pic_sets[local_sps_id];
	local_NUM_POSITIVE_PICS = HevcDecoder_Algo_Parser_NUM_POSITIVE_PICS;
	tmp_pcRPS = pcRPS[local_sps_id][tmp_sps_num_short_term_ref_pic_sets][local_NUM_POSITIVE_PICS];
	if (tmp_pcRPS != 0) {
		se_idx = 320;
		prev = 0;
	} else {
		se_idx = 301;
		cnt_i = 0;
	}

	// Update ports indexes

}
static i32 isSchedulable_read_SliceHeader_se_idx_12_loop2() {
	i32 result;
	u16 local_se_idx;
	i32 tmp_isFifoFull;
	u32 local_cnt_i;
	u16 local_sps_id;
	u8 tmp_sps_num_short_term_ref_pic_sets;
	u8 local_NUM_PICS;
	i8 tmp_pcRPS;

	local_se_idx = se_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	local_cnt_i = cnt_i;
	local_sps_id = sps_id;
	local_sps_id = sps_id;
	tmp_sps_num_short_term_ref_pic_sets = sps_num_short_term_ref_pic_sets[local_sps_id];
	local_NUM_PICS = HevcDecoder_Algo_Parser_NUM_PICS;
	tmp_pcRPS = pcRPS[local_sps_id][tmp_sps_num_short_term_ref_pic_sets][local_NUM_PICS];
	result = local_se_idx == 320 && tmp_isFifoFull && local_cnt_i < tmp_pcRPS;
	return result;
}

static void read_SliceHeader_se_idx_12_loop2() {

	u32 res[1];
	i32 local_prev;
	u32 tmp_res;
	u16 local_sps_id;
	u8 tmp_sps_num_short_term_ref_pic_sets;
	u8 local_DELTAPOC;
	u32 local_cnt_i;
	u8 tmp_sps_num_short_term_ref_pic_sets0;
	u8 local_USED;
	u32 tmp_res0;

	HevcDecoder_Algo_Parser_vld_ue_name(fifo, res, "delta_poc_s1_minus1                     ");
	local_prev = prev;
	tmp_res = res[0];
	prev = local_prev + tmp_res + 1;
	local_sps_id = sps_id;
	local_sps_id = sps_id;
	tmp_sps_num_short_term_ref_pic_sets = sps_num_short_term_ref_pic_sets[local_sps_id];
	local_DELTAPOC = HevcDecoder_Algo_Parser_DELTAPOC;
	local_cnt_i = cnt_i;
	local_prev = prev;
	pcRPS[local_sps_id][tmp_sps_num_short_term_ref_pic_sets][local_DELTAPOC + local_cnt_i] = local_prev;
	HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "used_by_curr_pic_s1_flag                ");
	local_sps_id = sps_id;
	local_sps_id = sps_id;
	tmp_sps_num_short_term_ref_pic_sets0 = sps_num_short_term_ref_pic_sets[local_sps_id];
	local_USED = HevcDecoder_Algo_Parser_USED;
	local_cnt_i = cnt_i;
	tmp_res0 = res[0];
	pcRPS[local_sps_id][tmp_sps_num_short_term_ref_pic_sets0][local_USED + local_cnt_i] = tmp_res0;
	local_cnt_i = cnt_i;
	cnt_i = local_cnt_i + 1;

	// Update ports indexes

}
static i32 isSchedulable_read_SliceHeader_se_idx_12_end_loop2() {
	i32 result;
	u16 local_se_idx;
	u32 local_cnt_i;
	u16 local_sps_id;
	u8 tmp_sps_num_short_term_ref_pic_sets;
	u8 local_NUM_PICS;
	i8 tmp_pcRPS;

	local_se_idx = se_idx;
	local_cnt_i = cnt_i;
	local_sps_id = sps_id;
	local_sps_id = sps_id;
	tmp_sps_num_short_term_ref_pic_sets = sps_num_short_term_ref_pic_sets[local_sps_id];
	local_NUM_PICS = HevcDecoder_Algo_Parser_NUM_PICS;
	tmp_pcRPS = pcRPS[local_sps_id][tmp_sps_num_short_term_ref_pic_sets][local_NUM_PICS];
	result = local_se_idx == 320 && local_cnt_i == tmp_pcRPS;
	return result;
}

static void read_SliceHeader_se_idx_12_end_loop2() {


	se_idx = 301;
	cnt_i = 0;

	// Update ports indexes

}
static i32 isSchedulable_read_SliceHeader_se_idx_13() {
	i32 result;
	u16 local_se_idx;
	i32 tmp_isFifoFull;

	local_se_idx = se_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	result = local_se_idx == 301 && tmp_isFifoFull;
	return result;
}

static void read_SliceHeader_se_idx_13() {

	u32 res[1];
	u8 lt_idx_sps;
	u8 prevDeltaMSB;
	u16 local_sps_id;
	u8 tmp_sps_long_term_ref_pics_present_flag;
	u8 tmp_sps_num_long_term_ref_pics_sps;
	u32 tmp_res;
	u32 tmp_res0;
	i32 i;
	u16 local_num_long_term_sps;
	u16 local_num_long_term_pics;
	u16 local_PicSizeInCtbsY;
	i32 tmp_log2;
	u16 tmp_lt_ref_pic_poc_lsb_sps;
	u8 tmp_used_by_curr_pic_lt_sps_flag;
	u8 tmp_sps_log2_max_pic_order_cnt_lsb_minus4;
	u32 tmp_res1;
	u32 tmp_res2;
	u32 tmp_res3;
	u32 tmp_res4;
	u32 tmp_res5;
	u32 tmp_res6;
	u8 tmp_sps_temporal_mvp_enable_flag;
	u32 tmp_res7;

	lt_idx_sps = 0;
	prevDeltaMSB = 0;
	num_long_term_sps = 0;
	num_long_term_pics = 0;
	local_sps_id = sps_id;
	tmp_sps_long_term_ref_pics_present_flag = sps_long_term_ref_pics_present_flag[local_sps_id];
	if (tmp_sps_long_term_ref_pics_present_flag == 1) {
		local_sps_id = sps_id;
		tmp_sps_num_long_term_ref_pics_sps = sps_num_long_term_ref_pics_sps[local_sps_id];
		if (tmp_sps_num_long_term_ref_pics_sps > 0) {
			HevcDecoder_Algo_Parser_vld_ue_name(fifo, res, "num_long_term_sps                       ");
			tmp_res = res[0];
			num_long_term_sps = tmp_res;
		}
		HevcDecoder_Algo_Parser_vld_ue_name(fifo, res, "num_long_term_pics                      ");
		tmp_res0 = res[0];
		num_long_term_pics = tmp_res0;
		i = 0;
		local_num_long_term_sps = num_long_term_sps;
		local_num_long_term_pics = num_long_term_pics;
		while (i <= local_num_long_term_sps + local_num_long_term_pics - 1) {
			local_num_long_term_sps = num_long_term_sps;
			if (i < local_num_long_term_sps) {
				local_num_long_term_pics = num_long_term_pics;
				if (local_num_long_term_pics > 1) {
					local_PicSizeInCtbsY = PicSizeInCtbsY;
					tmp_log2 = HevcDecoder_Algo_Parser_log2((local_PicSizeInCtbsY - 1) << 1);
					HevcDecoder_Algo_Parser_vld_u_name(tmp_log2, fifo, res, "lt_idx_sps                              ");
					lt_idx_sps = res[0];
				}
				tmp_lt_ref_pic_poc_lsb_sps = lt_ref_pic_poc_lsb_sps[lt_idx_sps];
				poc_lsb_lt[i] = tmp_lt_ref_pic_poc_lsb_sps;
				tmp_used_by_curr_pic_lt_sps_flag = used_by_curr_pic_lt_sps_flag[lt_idx_sps];
				UsedByCurrPicLt[i] = tmp_used_by_curr_pic_lt_sps_flag;
			} else {
				local_sps_id = sps_id;
				tmp_sps_log2_max_pic_order_cnt_lsb_minus4 = sps_log2_max_pic_order_cnt_lsb_minus4[local_sps_id];
				HevcDecoder_Algo_Parser_vld_u_name(tmp_sps_log2_max_pic_order_cnt_lsb_minus4 + 4, fifo, res, "poc_lsb_lt                              ");
				tmp_res1 = res[0];
				poc_lsb_lt[i] = tmp_res1;
				HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "used_by_curr_pic_lt_flag                ");
				tmp_res2 = res[0];
				UsedByCurrPicLt[i] = tmp_res2;
			}
			HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "delta_poc_msb_present_flag              ");
			tmp_res3 = res[0];
			delta_poc_msb_present_flag[i] = tmp_res3;
			tmp_res4 = res[0];
			if (tmp_res4 == 1) {
				local_num_long_term_sps = num_long_term_sps;
				if (i == 0 || i == local_num_long_term_sps) {
					HevcDecoder_Algo_Parser_vld_ue_name(fifo, res, "delta_poc_msb_cycle_lt_minus1                ");
					tmp_res5 = res[0];
					DeltaPocMsbCycleLt[i] = tmp_res5;
				} else {
					HevcDecoder_Algo_Parser_vld_ue_name(fifo, res, "delta_poc_msb_cycle_lt_minus1                ");
					tmp_res6 = res[0];
					DeltaPocMsbCycleLt[i] = tmp_res6 + prevDeltaMSB;
				}
				prevDeltaMSB = DeltaPocMsbCycleLt[i];
			}
			i = i + 1;
		}
	}
	local_sps_id = sps_id;
	tmp_sps_temporal_mvp_enable_flag = sps_temporal_mvp_enable_flag[local_sps_id];
	if (tmp_sps_temporal_mvp_enable_flag == 1) {
		HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "slice_temporal_mvp_enable_flag          ");
		tmp_res7 = res[0];
		slice_temporal_mvp_enable_flag = tmp_res7;
	} else {
		slice_temporal_mvp_enable_flag = 0;
	}
	se_idx = 302;

	// Update ports indexes

}
static i32 isSchedulable_read_SliceHeader_se_idx_14() {
	i32 result;
	u16 local_se_idx;
	i32 tmp_isFifoFull;

	local_se_idx = se_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	result = local_se_idx == 302 && tmp_isFifoFull;
	return result;
}

static void read_SliceHeader_se_idx_14() {

	u32 res[1];
	i32 i;
	i32 local_PICT_WIDTH;
	u8 local_MIN_CTB_SIZE_Y;
	u16 local_pps_id;
	u16 tmp_pps_column_width;
	u16 column_width[512];
	i32 i0;
	i32 local_PICT_HEIGHT;
	u16 tmp_pps_row_height;
	u16 row_height[256];
	u8 num_tile_columns_minus1;
	u8 num_tile_rows_minus1;
	u8 uniform_spacing_flag;
	u32 local_temporal_id;
	u8 local_nal_unit_type;
	u8 local_NAL_TRAIL_N;
	u8 local_NAL_TSA_N;
	u8 local_NAL_STSA_N;
	u8 local_NAL_RADL_N;
	u8 local_NAL_RADL_R;
	u8 local_NAL_RASL_N;
	u8 local_NAL_RASL_R;
	u16 local_sps_id;
	u8 tmp_sps_sample_adaptive_offset_enabled_flag;
	u32 tmp_res;
	u32 tmp_res0;
	u32 tmp_res1;
	i32 i1;
	u16 local_PicWidthInCtbsY;
	u16 tmp_colWidth;
	u8 local_Log2CtbSize;
	u16 tmp_colTileInPix;
	u16 tmp_pictSize;
	u16 tmp_pictSize0;
	i32 i2;
	u16 tmp_column_width;
	u16 tmp_colWidth0;
	u16 tmp_colWidth1;
	u16 tmp_colWidth2;
	u16 tmp_colTileInPix0;
	u16 tmp_pictSize1;
	i32 i3;
	u16 local_PicHeightInCtbsY;
	u16 tmp_rowHeight;
	u16 tmp_rowTileInPix;
	u16 tmp_pictSize2;
	u16 tmp_pictSize3;
	i32 i4;
	u16 tmp_row_height;
	u16 tmp_rowHeight0;
	u16 tmp_rowHeight1;
	u16 tmp_rowHeight2;
	u16 tmp_rowTileInPix0;
	u16 tmp_pictSize4;
	u32 local_TILE_SPLIT_ENABLE;
	u16 tmp_pictSize5;
	u16 tmp_pictSize6;
	u8 tmp_TilesInfo;
	u8 tmp_TilesInfo0;
	u32 local_colIndex;
	u16 tmp_colTileInPix1;
	u16 tmp_colTileInPix2;
	u32 local_rowIndex;
	u16 tmp_rowTileInPix1;
	u16 tmp_rowTileInPix2;
	u8 tmp_TilesInfo1;
	u8 tmp_TilesInfo2;
	u8 tmp_TilesInfo3;
	u32 local_prevColIndex;
	u16 tmp_colTileInPix3;
	u32 local_prevRowIndex;
	u16 tmp_rowTileInPix3;

	i = 0;
	local_PICT_WIDTH = HevcDecoder_Algo_Parser_PICT_WIDTH;
	local_MIN_CTB_SIZE_Y = HevcDecoder_Algo_Parser_MIN_CTB_SIZE_Y;
	while (i <= local_PICT_WIDTH / local_MIN_CTB_SIZE_Y - 1) {
		local_pps_id = pps_id;
		tmp_pps_column_width = pps_column_width[local_pps_id][i];
		column_width[i] = tmp_pps_column_width;
		i = i + 1;
	}
	i0 = 0;
	local_PICT_HEIGHT = HevcDecoder_Algo_Parser_PICT_HEIGHT;
	local_MIN_CTB_SIZE_Y = HevcDecoder_Algo_Parser_MIN_CTB_SIZE_Y;
	while (i0 <= local_PICT_HEIGHT / local_MIN_CTB_SIZE_Y - 1) {
		local_pps_id = pps_id;
		tmp_pps_row_height = pps_row_height[local_pps_id][i0];
		row_height[i0] = tmp_pps_row_height;
		i0 = i0 + 1;
	}
	local_pps_id = pps_id;
	num_tile_columns_minus1 = pps_num_tile_columns_minus1[local_pps_id];
	local_pps_id = pps_id;
	num_tile_rows_minus1 = pps_num_tile_rows_minus1[local_pps_id];
	local_pps_id = pps_id;
	uniform_spacing_flag = pps_uniform_spacing_flag[local_pps_id];
	local_temporal_id = temporal_id;
	local_nal_unit_type = nal_unit_type;
	local_NAL_TRAIL_N = HevcDecoder_Algo_Parser_NAL_TRAIL_N;
	local_nal_unit_type = nal_unit_type;
	local_NAL_TSA_N = HevcDecoder_Algo_Parser_NAL_TSA_N;
	local_nal_unit_type = nal_unit_type;
	local_NAL_STSA_N = HevcDecoder_Algo_Parser_NAL_STSA_N;
	local_nal_unit_type = nal_unit_type;
	local_NAL_RADL_N = HevcDecoder_Algo_Parser_NAL_RADL_N;
	local_nal_unit_type = nal_unit_type;
	local_NAL_RADL_R = HevcDecoder_Algo_Parser_NAL_RADL_R;
	local_nal_unit_type = nal_unit_type;
	local_NAL_RASL_N = HevcDecoder_Algo_Parser_NAL_RASL_N;
	local_nal_unit_type = nal_unit_type;
	local_NAL_RASL_R = HevcDecoder_Algo_Parser_NAL_RASL_R;
	if (local_temporal_id == 0 && local_nal_unit_type != local_NAL_TRAIL_N && local_nal_unit_type != local_NAL_TSA_N && local_nal_unit_type != local_NAL_STSA_N && local_nal_unit_type != local_NAL_RADL_N && local_nal_unit_type != local_NAL_RADL_R && local_nal_unit_type != local_NAL_RASL_N && local_nal_unit_type != local_NAL_RASL_R) {
	}
	local_sps_id = sps_id;
	tmp_sps_sample_adaptive_offset_enabled_flag = sps_sample_adaptive_offset_enabled_flag[local_sps_id];
	if (tmp_sps_sample_adaptive_offset_enabled_flag == 1) {
		HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "slice_sao_luma_flag                     ");
		tmp_res = res[0];
		slice_sample_adaptive_offset_flag[0] = tmp_res;
		HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "slice_sao_chroma_flag                   ");
		tmp_res0 = res[0];
		slice_sample_adaptive_offset_flag[1] = tmp_res0;
		tmp_res1 = res[0];
		slice_sample_adaptive_offset_flag[2] = tmp_res1;
	} else {
		slice_sample_adaptive_offset_flag[0] = 0;
		slice_sample_adaptive_offset_flag[1] = 0;
		slice_sample_adaptive_offset_flag[2] = 0;
	}
	local_PICT_WIDTH = HevcDecoder_Algo_Parser_PICT_WIDTH;
	local_MIN_CTB_SIZE_Y = HevcDecoder_Algo_Parser_MIN_CTB_SIZE_Y;
	if (num_tile_columns_minus1 >= local_PICT_WIDTH / local_MIN_CTB_SIZE_Y) {
		local_PICT_WIDTH = HevcDecoder_Algo_Parser_PICT_WIDTH;
		local_MIN_CTB_SIZE_Y = HevcDecoder_Algo_Parser_MIN_CTB_SIZE_Y;
		printf("Error read_SliceData.init : ColumnWidth : %u >= %i\n", num_tile_columns_minus1, local_PICT_WIDTH / local_MIN_CTB_SIZE_Y);
	}
	if (uniform_spacing_flag == 1) {
		i1 = 0;
		while (i1 <= num_tile_columns_minus1) {
			local_pps_id = pps_id;
			local_PicWidthInCtbsY = PicWidthInCtbsY;
			local_PicWidthInCtbsY = PicWidthInCtbsY;
			colWidth[local_pps_id][i1] = (i1 + 1) * local_PicWidthInCtbsY / (num_tile_columns_minus1 + 1) - i1 * local_PicWidthInCtbsY / (num_tile_columns_minus1 + 1);
			local_pps_id = pps_id;
			tmp_colWidth = colWidth[local_pps_id][i1];
			local_Log2CtbSize = Log2CtbSize;
			tmp_colTileInPix = colTileInPix[i1];
			colTileInPix[i1 + 1] = (tmp_colWidth << local_Log2CtbSize) + tmp_colTileInPix;
			if (i1 == num_tile_columns_minus1) {
				tmp_pictSize = pictSize[0];
				colTileInPix[i1 + 1] = tmp_pictSize;
			}
			i1 = i1 + 1;
		}
	} else {
		local_pps_id = pps_id;
		local_PicWidthInCtbsY = PicWidthInCtbsY;
		colWidth[local_pps_id][num_tile_columns_minus1] = local_PicWidthInCtbsY;
		if (num_tile_columns_minus1 == 0) {
			tmp_pictSize0 = pictSize[0];
			colTileInPix[1] = tmp_pictSize0;
		} else {
			i2 = 0;
			while (i2 <= num_tile_columns_minus1 - 1) {
				local_pps_id = pps_id;
				tmp_column_width = column_width[i2];
				colWidth[local_pps_id][i2] = tmp_column_width;
				local_pps_id = pps_id;
				local_pps_id = pps_id;
				tmp_colWidth0 = colWidth[local_pps_id][num_tile_columns_minus1];
				local_pps_id = pps_id;
				tmp_colWidth1 = colWidth[local_pps_id][i2];
				colWidth[local_pps_id][num_tile_columns_minus1] = tmp_colWidth0 - tmp_colWidth1;
				local_pps_id = pps_id;
				tmp_colWidth2 = colWidth[local_pps_id][i2];
				local_Log2CtbSize = Log2CtbSize;
				tmp_colTileInPix0 = colTileInPix[i2];
				colTileInPix[i2 + 1] = (tmp_colWidth2 << local_Log2CtbSize) + tmp_colTileInPix0;
				if (i2 == num_tile_columns_minus1 - 1) {
					tmp_pictSize1 = pictSize[0];
					colTileInPix[i2 + 2] = tmp_pictSize1;
				}
				i2 = i2 + 1;
			}
		}
	}
	local_PICT_HEIGHT = HevcDecoder_Algo_Parser_PICT_HEIGHT;
	local_MIN_CTB_SIZE_Y = HevcDecoder_Algo_Parser_MIN_CTB_SIZE_Y;
	if (num_tile_rows_minus1 >= local_PICT_HEIGHT / local_MIN_CTB_SIZE_Y) {
		local_PICT_HEIGHT = HevcDecoder_Algo_Parser_PICT_HEIGHT;
		local_MIN_CTB_SIZE_Y = HevcDecoder_Algo_Parser_MIN_CTB_SIZE_Y;
		printf("Error read_SliceData.init : RowHeight : %u >= %i\n", num_tile_rows_minus1, local_PICT_HEIGHT / local_MIN_CTB_SIZE_Y);
	}
	if (uniform_spacing_flag == 1) {
		i3 = 0;
		while (i3 <= num_tile_rows_minus1) {
			local_pps_id = pps_id;
			local_PicHeightInCtbsY = PicHeightInCtbsY;
			local_PicHeightInCtbsY = PicHeightInCtbsY;
			rowHeight[local_pps_id][i3] = (i3 + 1) * local_PicHeightInCtbsY / (num_tile_rows_minus1 + 1) - i3 * local_PicHeightInCtbsY / (num_tile_rows_minus1 + 1);
			local_pps_id = pps_id;
			tmp_rowHeight = rowHeight[local_pps_id][i3];
			local_Log2CtbSize = Log2CtbSize;
			tmp_rowTileInPix = rowTileInPix[i3];
			rowTileInPix[i3 + 1] = (tmp_rowHeight << local_Log2CtbSize) + tmp_rowTileInPix;
			if (i3 == num_tile_rows_minus1) {
				tmp_pictSize2 = pictSize[1];
				rowTileInPix[i3 + 1] = tmp_pictSize2;
			}
			i3 = i3 + 1;
		}
	} else {
		local_pps_id = pps_id;
		local_PicHeightInCtbsY = PicHeightInCtbsY;
		rowHeight[local_pps_id][num_tile_rows_minus1] = local_PicHeightInCtbsY;
		if (num_tile_rows_minus1 == 0) {
			tmp_pictSize3 = pictSize[1];
			rowTileInPix[1] = tmp_pictSize3;
		} else {
			i4 = 0;
			while (i4 <= num_tile_rows_minus1 - 1) {
				local_pps_id = pps_id;
				tmp_row_height = row_height[i4];
				rowHeight[local_pps_id][i4] = tmp_row_height;
				local_pps_id = pps_id;
				local_pps_id = pps_id;
				tmp_rowHeight0 = rowHeight[local_pps_id][num_tile_columns_minus1];
				local_pps_id = pps_id;
				tmp_rowHeight1 = rowHeight[local_pps_id][i4];
				rowHeight[local_pps_id][num_tile_rows_minus1] = tmp_rowHeight0 - tmp_rowHeight1;
				local_pps_id = pps_id;
				tmp_rowHeight2 = rowHeight[local_pps_id][i4];
				local_Log2CtbSize = Log2CtbSize;
				tmp_rowTileInPix0 = rowTileInPix[i4];
				rowTileInPix[i4 + 1] = (tmp_rowHeight2 << local_Log2CtbSize) + tmp_rowTileInPix0;
				if (i4 == num_tile_rows_minus1 - 1) {
					tmp_pictSize4 = pictSize[1];
					rowTileInPix[i4 + 2] = tmp_pictSize4;
				}
				i4 = i4 + 1;
			}
		}
	}
	local_TILE_SPLIT_ENABLE = TILE_SPLIT_ENABLE;
	if (local_TILE_SPLIT_ENABLE == 0) {
		tmp_pictSize5 = pictSize[0];
		pictOrTileSize[0] = tmp_pictSize5;
		tmp_pictSize6 = pictSize[1];
		pictOrTileSize[1] = tmp_pictSize6;
	} else {
		tmp_TilesInfo = TilesInfo[1];
		colIndex = tmp_TilesInfo % (num_tile_columns_minus1 + 1);
		tmp_TilesInfo0 = TilesInfo[1];
		rowIndex = tmp_TilesInfo0 / (num_tile_columns_minus1 + 1);
		local_colIndex = colIndex;
		tmp_colTileInPix1 = colTileInPix[local_colIndex + 1];
		local_colIndex = colIndex;
		tmp_colTileInPix2 = colTileInPix[local_colIndex];
		pictOrTileSize[0] = tmp_colTileInPix1 - tmp_colTileInPix2;
		local_rowIndex = rowIndex;
		tmp_rowTileInPix1 = rowTileInPix[local_rowIndex + 1];
		local_rowIndex = rowIndex;
		tmp_rowTileInPix2 = rowTileInPix[local_rowIndex];
		pictOrTileSize[1] = tmp_rowTileInPix1 - tmp_rowTileInPix2;
		tmp_TilesInfo1 = TilesInfo[1];
		if (tmp_TilesInfo1 != 0) {
			tmp_TilesInfo2 = TilesInfo[1];
			prevColIndex = (tmp_TilesInfo2 - 1) % (num_tile_rows_minus1 + 1);
			tmp_TilesInfo3 = TilesInfo[1];
			prevRowIndex = (tmp_TilesInfo3 - 1) / (num_tile_columns_minus1 + 1);
			local_prevColIndex = prevColIndex;
			tmp_colTileInPix3 = colTileInPix[local_prevColIndex + 1];
			prevTileCoord[0] = tmp_colTileInPix3;
			local_prevRowIndex = prevRowIndex;
			tmp_rowTileInPix3 = rowTileInPix[local_prevRowIndex + 1];
			prevTileCoord[1] = tmp_rowTileInPix3;
		}
	}
	se_idx = 2;

	// Update ports indexes

}
static i32 isSchedulable_read_SliceHeader_se_idx_2() {
	i32 result;
	u16 local_se_idx;
	i32 tmp_isFifoFull;

	local_se_idx = se_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	result = local_se_idx == 2 && tmp_isFifoFull;
	return result;
}

static void read_SliceHeader_se_idx_2() {

	u32 res[1];
	i32 NumPocTotalCurr;
	u8 local_slice_type;
	u8 local_P_SLICE;
	u8 local_B_SLICE;
	u16 local_pps_id;
	u8 tmp_pps_num_ref_idx_l0_default_active_minus1;
	u8 tmp_pps_num_ref_idx_l1_default_active_minus1;
	u32 tmp_res;
	u32 tmp_res0;
	u32 tmp_res1;
	i32 i;
	u16 local_sps_id;
	u8 tmp_sps_num_short_term_ref_pic_sets;
	u8 local_NUM_NEGATIVE_PICS;
	i8 tmp_pcRPS;
	u8 tmp_sps_num_short_term_ref_pic_sets0;
	u8 local_USED;
	i8 tmp_pcRPS0;
	i32 i0;
	u8 tmp_sps_num_short_term_ref_pic_sets1;
	u8 tmp_sps_num_short_term_ref_pic_sets2;
	u8 local_NUM_PICS;
	i8 tmp_pcRPS1;
	u8 tmp_sps_num_short_term_ref_pic_sets3;
	i8 tmp_pcRPS2;
	i32 i1;
	u16 local_num_long_term_sps;
	u16 local_num_long_term_pics;
	u8 tmp_UsedByCurrPicLt;
	u8 tmp_pps_lists_modification_present_flag;
	u32 tmp_res2;
	u8 tmp_ref_pic_list_modification_flag_lx;
	i32 i2;
	u8 local_num_ref_idx_l0_active;
	i32 tmp_log2;
	u32 tmp_res3;
	u32 tmp_res4;
	u8 tmp_ref_pic_list_modification_flag_lx0;
	i32 i3;
	u8 local_num_ref_idx_l1_active;
	i32 tmp_log20;
	u32 tmp_res5;
	u32 tmp_res6;

	NumPocTotalCurr = 0;
	num_ref_idx_l0_active = 0;
	num_ref_idx_l1_active = 0;
	mvd_l1_zero_flag = 0;
	local_slice_type = slice_type;
	local_P_SLICE = HevcDecoder_Algo_Parser_P_SLICE;
	local_slice_type = slice_type;
	local_B_SLICE = HevcDecoder_Algo_Parser_B_SLICE;
	if (local_slice_type == local_P_SLICE || local_slice_type == local_B_SLICE) {
		local_pps_id = pps_id;
		tmp_pps_num_ref_idx_l0_default_active_minus1 = pps_num_ref_idx_l0_default_active_minus1[local_pps_id];
		num_ref_idx_l0_active = tmp_pps_num_ref_idx_l0_default_active_minus1 + 1;
		local_slice_type = slice_type;
		local_B_SLICE = HevcDecoder_Algo_Parser_B_SLICE;
		if (local_slice_type == local_B_SLICE) {
			local_pps_id = pps_id;
			tmp_pps_num_ref_idx_l1_default_active_minus1 = pps_num_ref_idx_l1_default_active_minus1[local_pps_id];
			num_ref_idx_l1_active = tmp_pps_num_ref_idx_l1_default_active_minus1 + 1;
		}
		HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "num_ref_idx_active_override_flag        ");
		tmp_res = res[0];
		if (tmp_res == 1) {
			HevcDecoder_Algo_Parser_vld_ue_name(fifo, res, "num_ref_idx_l0_active_minus1            ");
			tmp_res0 = res[0];
			num_ref_idx_l0_active = tmp_res0 + 1;
			local_slice_type = slice_type;
			local_B_SLICE = HevcDecoder_Algo_Parser_B_SLICE;
			if (local_slice_type == local_B_SLICE) {
				HevcDecoder_Algo_Parser_vld_ue_name(fifo, res, "num_ref_idx_l1_active_minus1            ");
				tmp_res1 = res[0];
				num_ref_idx_l1_active = tmp_res1 + 1;
			}
		}
		ref_pic_list_modification_flag_lx[0] = 0;
		ref_pic_list_modification_flag_lx[1] = 0;
		i = 0;
		local_sps_id = sps_id;
		local_sps_id = sps_id;
		tmp_sps_num_short_term_ref_pic_sets = sps_num_short_term_ref_pic_sets[local_sps_id];
		local_NUM_NEGATIVE_PICS = HevcDecoder_Algo_Parser_NUM_NEGATIVE_PICS;
		tmp_pcRPS = pcRPS[local_sps_id][tmp_sps_num_short_term_ref_pic_sets][local_NUM_NEGATIVE_PICS];
		while (i <= tmp_pcRPS - 1) {
			local_sps_id = sps_id;
			local_sps_id = sps_id;
			tmp_sps_num_short_term_ref_pic_sets0 = sps_num_short_term_ref_pic_sets[local_sps_id];
			local_USED = HevcDecoder_Algo_Parser_USED;
			tmp_pcRPS0 = pcRPS[local_sps_id][tmp_sps_num_short_term_ref_pic_sets0][local_USED + i];
			if (tmp_pcRPS0 == 1) {
				NumPocTotalCurr = NumPocTotalCurr + 1;
			}
			i = i + 1;
		}
		local_sps_id = sps_id;
		local_sps_id = sps_id;
		tmp_sps_num_short_term_ref_pic_sets1 = sps_num_short_term_ref_pic_sets[local_sps_id];
		local_NUM_NEGATIVE_PICS = HevcDecoder_Algo_Parser_NUM_NEGATIVE_PICS;
		i0 = pcRPS[local_sps_id][tmp_sps_num_short_term_ref_pic_sets1][local_NUM_NEGATIVE_PICS];
		local_sps_id = sps_id;
		local_sps_id = sps_id;
		tmp_sps_num_short_term_ref_pic_sets2 = sps_num_short_term_ref_pic_sets[local_sps_id];
		local_NUM_PICS = HevcDecoder_Algo_Parser_NUM_PICS;
		tmp_pcRPS1 = pcRPS[local_sps_id][tmp_sps_num_short_term_ref_pic_sets2][local_NUM_PICS];
		while (i0 <= tmp_pcRPS1 - 1) {
			local_sps_id = sps_id;
			local_sps_id = sps_id;
			tmp_sps_num_short_term_ref_pic_sets3 = sps_num_short_term_ref_pic_sets[local_sps_id];
			local_USED = HevcDecoder_Algo_Parser_USED;
			tmp_pcRPS2 = pcRPS[local_sps_id][tmp_sps_num_short_term_ref_pic_sets3][local_USED + i0];
			if (tmp_pcRPS2 == 1) {
				NumPocTotalCurr = NumPocTotalCurr + 1;
			}
			i0 = i0 + 1;
		}
		i1 = 0;
		local_num_long_term_sps = num_long_term_sps;
		local_num_long_term_pics = num_long_term_pics;
		while (i1 <= local_num_long_term_sps + local_num_long_term_pics - 1) {
			tmp_UsedByCurrPicLt = UsedByCurrPicLt[i1];
			if (tmp_UsedByCurrPicLt == 1) {
				NumPocTotalCurr = NumPocTotalCurr + 1;
			}
			i1 = i1 + 1;
		}
		local_pps_id = pps_id;
		tmp_pps_lists_modification_present_flag = pps_lists_modification_present_flag[local_pps_id];
		if (tmp_pps_lists_modification_present_flag == 1 && NumPocTotalCurr > 1) {
			HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "ref_pic_list_modification_flag_l0       ");
			tmp_res2 = res[0];
			ref_pic_list_modification_flag_lx[0] = tmp_res2;
			tmp_ref_pic_list_modification_flag_lx = ref_pic_list_modification_flag_lx[0];
			if (tmp_ref_pic_list_modification_flag_lx == 1) {
				i2 = 0;
				local_num_ref_idx_l0_active = num_ref_idx_l0_active;
				while (i2 <= local_num_ref_idx_l0_active - 1) {
					tmp_log2 = HevcDecoder_Algo_Parser_log2((NumPocTotalCurr - 1) << 1);
					HevcDecoder_Algo_Parser_vld_u_name(tmp_log2, fifo, res, "list_entry_lx                           ");
					tmp_res3 = res[0];
					list_entry_lx[0][i2] = tmp_res3;
					i2 = i2 + 1;
				}
			}
			local_slice_type = slice_type;
			local_B_SLICE = HevcDecoder_Algo_Parser_B_SLICE;
			if (local_slice_type == local_B_SLICE) {
				HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "ref_pic_list_modification_flag_l1       ");
				tmp_res4 = res[0];
				ref_pic_list_modification_flag_lx[1] = tmp_res4;
				tmp_ref_pic_list_modification_flag_lx0 = ref_pic_list_modification_flag_lx[1];
				if (tmp_ref_pic_list_modification_flag_lx0 == 1) {
					i3 = 0;
					local_num_ref_idx_l1_active = num_ref_idx_l1_active;
					while (i3 <= local_num_ref_idx_l1_active - 1) {
						tmp_log20 = HevcDecoder_Algo_Parser_log2((NumPocTotalCurr - 1) << 1);
						HevcDecoder_Algo_Parser_vld_u_name(tmp_log20, fifo, res, "list_entry_lx                           ");
						tmp_res5 = res[0];
						list_entry_lx[1][i3] = tmp_res5;
						i3 = i3 + 1;
					}
				}
			}
		}
		local_slice_type = slice_type;
		local_B_SLICE = HevcDecoder_Algo_Parser_B_SLICE;
		if (local_slice_type == local_B_SLICE) {
			HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "mvd_l1_zero_flag                        ");
			tmp_res6 = res[0];
			mvd_l1_zero_flag = tmp_res6;
		}
	}
	se_idx = 10;

	// Update ports indexes

}
static i32 isSchedulable_read_SliceHeader_sendRefPOC_init() {
	i32 result;
	u16 local_se_idx;

	local_se_idx = se_idx;
	result = local_se_idx == 10;
	return result;
}

static void read_SliceHeader_sendRefPOC_init_aligned() {

	u16 local_sps_id;
	u8 tmp_sps_num_short_term_ref_pic_sets;
	i32 local_poc;
	u8 local_num_ref_idx_l0_active;
	u8 local_num_ref_idx_l1_active;

	local_sps_id = sps_id;
	local_sps_id = sps_id;
	tmp_sps_num_short_term_ref_pic_sets = sps_num_short_term_ref_pic_sets[local_sps_id];
	local_poc = poc;
	setRefTables(local_sps_id, tmp_sps_num_short_term_ref_pic_sets, pcRPS, local_poc);
	idxNumPic = 0;
	se_idx = 101;
	local_num_ref_idx_l0_active = num_ref_idx_l0_active;
	tokens_NumRefIdxLxActive[(index_NumRefIdxLxActive % SIZE_NumRefIdxLxActive) + (0)] = local_num_ref_idx_l0_active;
	local_num_ref_idx_l1_active = num_ref_idx_l1_active;
	tokens_NumRefIdxLxActive[(index_NumRefIdxLxActive % SIZE_NumRefIdxLxActive) + (1)] = local_num_ref_idx_l1_active;

	// Update ports indexes
	index_NumRefIdxLxActive += 2;
	write_end_NumRefIdxLxActive();

}
static i32 isSchedulable_read_SliceHeader_sendListEntryL0Flag() {
	i32 result;
	u16 local_se_idx;

	local_se_idx = se_idx;
	result = local_se_idx == 101;
	return result;
}

static void read_SliceHeader_sendListEntryL0Flag() {

	u8 tmp_ref_pic_list_modification_flag_lx;
	u8 tmp_ref_pic_list_modification_flag_lx0;

	tmp_ref_pic_list_modification_flag_lx = ref_pic_list_modification_flag_lx[0];
	if (tmp_ref_pic_list_modification_flag_lx == 0) {
		se_idx = 201;
	} else {
		se_idx = 102;
	}
	tmp_ref_pic_list_modification_flag_lx0 = ref_pic_list_modification_flag_lx[0];
	tokens_RefPicListModif[(index_RefPicListModif + (0)) % SIZE_RefPicListModif] = tmp_ref_pic_list_modification_flag_lx0;

	// Update ports indexes
	index_RefPicListModif += 1;

}
static i32 isSchedulable_read_SliceHeader_sendListEntryL0Loop() {
	i32 result;
	u16 local_se_idx;
	u32 local_cnt_i;
	u8 local_num_ref_idx_l0_active;

	local_se_idx = se_idx;
	local_cnt_i = cnt_i;
	local_num_ref_idx_l0_active = num_ref_idx_l0_active;
	result = local_se_idx == 102 && local_cnt_i < local_num_ref_idx_l0_active;
	return result;
}

static void read_SliceHeader_sendListEntryL0Loop() {

	u32 local_cnt_i;
	u8 tmp_list_entry_lx;

	local_cnt_i = cnt_i;
	cnt_i = local_cnt_i + 1;
	local_cnt_i = cnt_i;
	tmp_list_entry_lx = list_entry_lx[0][local_cnt_i - 1];
	tokens_RefPicListModif[(index_RefPicListModif + (0)) % SIZE_RefPicListModif] = tmp_list_entry_lx;

	// Update ports indexes
	index_RefPicListModif += 1;

}
static i32 isSchedulable_read_SliceHeader_sendListEntryL0End() {
	i32 result;
	u16 local_se_idx;
	u32 local_cnt_i;
	u8 local_num_ref_idx_l0_active;

	local_se_idx = se_idx;
	local_cnt_i = cnt_i;
	local_num_ref_idx_l0_active = num_ref_idx_l0_active;
	result = local_se_idx == 102 && local_cnt_i == local_num_ref_idx_l0_active;
	return result;
}

static void read_SliceHeader_sendListEntryL0End() {


	cnt_i = 0;
	se_idx = 201;

	// Update ports indexes

}
static i32 isSchedulable_read_SliceHeader_sendListEntryL1Flag() {
	i32 result;
	u16 local_se_idx;

	local_se_idx = se_idx;
	result = local_se_idx == 201;
	return result;
}

static void read_SliceHeader_sendListEntryL1Flag() {

	u8 tmp_ref_pic_list_modification_flag_lx;
	u8 tmp_ref_pic_list_modification_flag_lx0;

	tmp_ref_pic_list_modification_flag_lx = ref_pic_list_modification_flag_lx[1];
	if (tmp_ref_pic_list_modification_flag_lx == 0) {
		se_idx = 11;
	} else {
		se_idx = 202;
	}
	tmp_ref_pic_list_modification_flag_lx0 = ref_pic_list_modification_flag_lx[1];
	tokens_RefPicListModif[(index_RefPicListModif + (0)) % SIZE_RefPicListModif] = tmp_ref_pic_list_modification_flag_lx0;

	// Update ports indexes
	index_RefPicListModif += 1;

}
static i32 isSchedulable_read_SliceHeader_sendListEntryL1Loop() {
	i32 result;
	u16 local_se_idx;
	u32 local_cnt_i;
	u8 local_num_ref_idx_l1_active;

	local_se_idx = se_idx;
	local_cnt_i = cnt_i;
	local_num_ref_idx_l1_active = num_ref_idx_l1_active;
	result = local_se_idx == 202 && local_cnt_i < local_num_ref_idx_l1_active;
	return result;
}

static void read_SliceHeader_sendListEntryL1Loop() {

	u32 local_cnt_i;
	u8 tmp_list_entry_lx;

	local_cnt_i = cnt_i;
	cnt_i = local_cnt_i + 1;
	local_cnt_i = cnt_i;
	tmp_list_entry_lx = list_entry_lx[1][local_cnt_i - 1];
	tokens_RefPicListModif[(index_RefPicListModif + (0)) % SIZE_RefPicListModif] = tmp_list_entry_lx;

	// Update ports indexes
	index_RefPicListModif += 1;

}
static i32 isSchedulable_read_SliceHeader_sendListEntryL1End() {
	i32 result;
	u16 local_se_idx;
	u32 local_cnt_i;
	u8 local_num_ref_idx_l1_active;

	local_se_idx = se_idx;
	local_cnt_i = cnt_i;
	local_num_ref_idx_l1_active = num_ref_idx_l1_active;
	result = local_se_idx == 202 && local_cnt_i == local_num_ref_idx_l1_active;
	return result;
}

static void read_SliceHeader_sendListEntryL1End() {


	cnt_i = 0;
	se_idx = 11;

	// Update ports indexes

}
static i32 isSchedulable_read_SliceHeader_sendRefPOC_sendSize() {
	i32 result;
	u16 local_se_idx;

	local_se_idx = se_idx;
	result = local_se_idx == 11;
	return result;
}

static void read_SliceHeader_sendRefPOC_sendSize() {

	u8 local_idxNumPic;
	i16 refPocSize;
	i32 tmp_numPic;

	local_idxNumPic = idxNumPic;
	refPocSize = numPic[local_idxNumPic];
	local_idxNumPic = idxNumPic;
	tmp_numPic = numPic[local_idxNumPic];
	if (tmp_numPic == 0) {
		local_idxNumPic = idxNumPic;
		idxNumPic = local_idxNumPic + 1;
		local_idxNumPic = idxNumPic;
		if (local_idxNumPic == 5) {
			se_idx = 3;
		}
	} else {
		idxRefPoc = 0;
		se_idx = 12;
	}
	tokens_RefPoc[(index_RefPoc + (0)) % SIZE_RefPoc] = refPocSize;

	// Update ports indexes
	index_RefPoc += 1;

}
static i32 isSchedulable_read_SliceHeader_sendRefPOC_sendRefPoc() {
	i32 result;
	u16 local_se_idx;

	local_se_idx = se_idx;
	result = local_se_idx == 12;
	return result;
}

static void read_SliceHeader_sendRefPOC_sendRefPoc() {

	u8 local_idxNumPic;
	u8 local_idxRefPoc;
	i16 refPoc;
	i32 tmp_numPic;

	local_idxNumPic = idxNumPic;
	local_idxRefPoc = idxRefPoc;
	refPoc = pocTables[local_idxNumPic][local_idxRefPoc];
	local_idxRefPoc = idxRefPoc;
	idxRefPoc = local_idxRefPoc + 1;
	local_idxRefPoc = idxRefPoc;
	local_idxNumPic = idxNumPic;
	tmp_numPic = numPic[local_idxNumPic];
	if (local_idxRefPoc == tmp_numPic) {
		local_idxNumPic = idxNumPic;
		idxNumPic = local_idxNumPic + 1;
		local_idxNumPic = idxNumPic;
		if (local_idxNumPic == 5) {
			se_idx = 3;
		} else {
			se_idx = 11;
		}
	}
	tokens_RefPoc[(index_RefPoc + (0)) % SIZE_RefPoc] = refPoc;

	// Update ports indexes
	index_RefPoc += 1;

}
static i32 isSchedulable_read_SliceHeader_se_idx_3() {
	i32 result;
	u16 local_se_idx;
	i32 tmp_isFifoFull;

	local_se_idx = se_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	result = local_se_idx == 3 && tmp_isFifoFull;
	return result;
}

static void read_SliceHeader_se_idx_3() {

	u32 res[1];
	u8 weighted_pred_flag;
	u8 collocated_from_l0_flag;
	u8 local_slice_type;
	u8 local_P_SLICE;
	u8 local_B_SLICE;
	u16 local_pps_id;
	u8 tmp_pps_cabac_init_present_flag;
	u32 tmp_res;
	u8 local_slice_temporal_mvp_enable_flag;
	u32 tmp_res0;
	u8 local_num_ref_idx_l0_active;
	u8 local_num_ref_idx_l1_active;
	u32 tmp_res1;
	u8 tmp_pps_weighted_pred_flag;
	u8 tmp_pps_weighted_bipred_flag;

	weighted_pred_flag = 0;
	collocated_from_l0_flag = 1;
	collocated_from_lX = 0;
	collocated_ref_idx = 0;
	cabac_init_flag = 0;
	se_idx = 5;
	local_slice_type = slice_type;
	local_P_SLICE = HevcDecoder_Algo_Parser_P_SLICE;
	local_slice_type = slice_type;
	local_B_SLICE = HevcDecoder_Algo_Parser_B_SLICE;
	if (local_slice_type == local_P_SLICE || local_slice_type == local_B_SLICE) {
		local_pps_id = pps_id;
		tmp_pps_cabac_init_present_flag = pps_cabac_init_present_flag[local_pps_id];
		if (tmp_pps_cabac_init_present_flag == 1) {
			HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "cabac_init_flag                         ");
			tmp_res = res[0];
			cabac_init_flag = tmp_res;
		}
		local_slice_temporal_mvp_enable_flag = slice_temporal_mvp_enable_flag;
		if (local_slice_temporal_mvp_enable_flag == 1) {
			res[0] = 1;
			local_slice_type = slice_type;
			local_B_SLICE = HevcDecoder_Algo_Parser_B_SLICE;
			if (local_slice_type == local_B_SLICE) {
				HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "collocated_from_l0_flag                 ");
				collocated_from_l0_flag = res[0];
				tmp_res0 = res[0];
				collocated_from_lX = tmp_res0;
			}
			local_num_ref_idx_l0_active = num_ref_idx_l0_active;
			local_num_ref_idx_l1_active = num_ref_idx_l1_active;
			if (collocated_from_l0_flag == 1 && local_num_ref_idx_l0_active > 1 || collocated_from_l0_flag == 0 && local_num_ref_idx_l1_active > 1) {
				HevcDecoder_Algo_Parser_vld_ue_name(fifo, res, "collocated_ref_idx                      ");
				tmp_res1 = res[0];
				collocated_ref_idx = tmp_res1;
			}
		}
		local_pps_id = pps_id;
		tmp_pps_weighted_pred_flag = pps_weighted_pred_flag[local_pps_id];
		local_pps_id = pps_id;
		tmp_pps_weighted_bipred_flag = pps_weighted_bipred_flag[local_pps_id];
		if (tmp_pps_weighted_pred_flag == 1 || tmp_pps_weighted_bipred_flag == 1) {
			weighted_pred_flag = 1;
		}
		if (weighted_pred_flag != 0) {
			se_idx = 4;
		}
	}
	tokens_WeightedPred[(index_WeightedPred + (0)) % SIZE_WeightedPred] = weighted_pred_flag;

	// Update ports indexes
	index_WeightedPred += 1;

}
static i32 isSchedulable_weighted_start() {
	i32 result;
	u16 local_se_idx;
	i32 tmp_isFifoFull;
	u8 local_slice_type;
	u8 local_P_SLICE;
	u8 local_B_SLICE;
	u16 local_pps_id;
	u8 tmp_pps_weighted_pred_flag;
	u8 tmp_pps_weighted_bipred_flag;

	local_se_idx = se_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	local_slice_type = slice_type;
	local_P_SLICE = HevcDecoder_Algo_Parser_P_SLICE;
	local_slice_type = slice_type;
	local_B_SLICE = HevcDecoder_Algo_Parser_B_SLICE;
	local_pps_id = pps_id;
	tmp_pps_weighted_pred_flag = pps_weighted_pred_flag[local_pps_id];
	local_slice_type = slice_type;
	local_P_SLICE = HevcDecoder_Algo_Parser_P_SLICE;
	local_pps_id = pps_id;
	tmp_pps_weighted_bipred_flag = pps_weighted_bipred_flag[local_pps_id];
	local_slice_type = slice_type;
	local_B_SLICE = HevcDecoder_Algo_Parser_B_SLICE;
	result = local_se_idx == 4 && tmp_isFifoFull && (local_slice_type == local_P_SLICE || local_slice_type == local_B_SLICE) && (tmp_pps_weighted_pred_flag == 1 && local_slice_type == local_P_SLICE || tmp_pps_weighted_bipred_flag == 1 && local_slice_type == local_B_SLICE);
	return result;
}

static void weighted_start() {

	u32 res[1];
	u8 luma_log2_weight_denom;
	i8 delta_chroma_log2_weight_denom;
	u16 local_sps_id;
	u8 tmp_sps_chroma_format_idc;

	luma_log2_weight_denom = 0;
	delta_chroma_log2_weight_denom = 0;
	HevcDecoder_Algo_Parser_vld_ue_name(fifo, res, "luma_log2_weight_denom                  ");
	luma_log2_weight_denom = res[0];
	local_sps_id = sps_id;
	tmp_sps_chroma_format_idc = sps_chroma_format_idc[local_sps_id];
	if (tmp_sps_chroma_format_idc != 0) {
		HevcDecoder_Algo_Parser_vld_se_name(fifo, res, "delta_chroma_log2_weight_denom          ");
		delta_chroma_log2_weight_denom = res[0];
	}
	tokens_WeightedPred[(index_WeightedPred + (0)) % SIZE_WeightedPred] = luma_log2_weight_denom;
	tokens_WeightedPred[(index_WeightedPred + (1)) % SIZE_WeightedPred] = delta_chroma_log2_weight_denom;

	// Update ports indexes
	index_WeightedPred += 2;
	write_end_WeightedPred();

}
static void weighted_start_aligned() {

	u32 res[1];
	u8 luma_log2_weight_denom;
	i8 delta_chroma_log2_weight_denom;
	u16 local_sps_id;
	u8 tmp_sps_chroma_format_idc;

	luma_log2_weight_denom = 0;
	delta_chroma_log2_weight_denom = 0;
	HevcDecoder_Algo_Parser_vld_ue_name(fifo, res, "luma_log2_weight_denom                  ");
	luma_log2_weight_denom = res[0];
	local_sps_id = sps_id;
	tmp_sps_chroma_format_idc = sps_chroma_format_idc[local_sps_id];
	if (tmp_sps_chroma_format_idc != 0) {
		HevcDecoder_Algo_Parser_vld_se_name(fifo, res, "delta_chroma_log2_weight_denom          ");
		delta_chroma_log2_weight_denom = res[0];
	}
	tokens_WeightedPred[(index_WeightedPred % SIZE_WeightedPred) + (0)] = luma_log2_weight_denom;
	tokens_WeightedPred[(index_WeightedPred % SIZE_WeightedPred) + (1)] = delta_chroma_log2_weight_denom;

	// Update ports indexes
	index_WeightedPred += 2;
	write_end_WeightedPred();

}
static i32 isSchedulable_weighted_luma_l0() {
	i32 result;
	i32 tmp_isFifoFull;

	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	result = tmp_isFifoFull;
	return result;
}

static void weighted_luma_l0() {

	u32 res[1];
	u32 local_cnt_i;
	u32 tmp_res;
	u8 tmp_luma_weight_l0_flag;

	HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "luma_weight_lX_flag                     ");
	local_cnt_i = cnt_i;
	tmp_res = res[0];
	luma_weight_l0_flag[local_cnt_i] = tmp_res;
	local_cnt_i = cnt_i;
	cnt_i = local_cnt_i + 1;
	local_cnt_i = cnt_i;
	tmp_luma_weight_l0_flag = luma_weight_l0_flag[local_cnt_i - 1];
	tokens_WeightedPred[(index_WeightedPred + (0)) % SIZE_WeightedPred] = tmp_luma_weight_l0_flag;

	// Update ports indexes
	index_WeightedPred += 1;

}
static i32 isSchedulable_weighted_end_luma_l0() {
	i32 result;
	i32 tmp_isFifoFull;
	u32 local_cnt_i;
	u8 local_num_ref_idx_l0_active;

	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	local_cnt_i = cnt_i;
	local_num_ref_idx_l0_active = num_ref_idx_l0_active;
	result = tmp_isFifoFull && local_cnt_i == local_num_ref_idx_l0_active;
	return result;
}

static void weighted_end_luma_l0() {


	cnt_i = 0;

	// Update ports indexes

}
static i32 isSchedulable_weighted_chroma_l0() {
	i32 result;
	i32 tmp_isFifoFull;
	u16 local_sps_id;
	u8 tmp_sps_chroma_format_idc;

	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	local_sps_id = sps_id;
	tmp_sps_chroma_format_idc = sps_chroma_format_idc[local_sps_id];
	result = tmp_isFifoFull && tmp_sps_chroma_format_idc == 1;
	return result;
}

static void weighted_chroma_l0() {

	u32 res[1];
	u32 local_cnt_i;
	u32 tmp_res;
	u8 tmp_chroma_weight_l0_flag;

	HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "chroma_weight_lX_flag                   ");
	local_cnt_i = cnt_i;
	tmp_res = res[0];
	chroma_weight_l0_flag[local_cnt_i] = tmp_res;
	local_cnt_i = cnt_i;
	cnt_i = local_cnt_i + 1;
	local_cnt_i = cnt_i;
	tmp_chroma_weight_l0_flag = chroma_weight_l0_flag[local_cnt_i - 1];
	tokens_WeightedPred[(index_WeightedPred + (0)) % SIZE_WeightedPred] = tmp_chroma_weight_l0_flag;

	// Update ports indexes
	index_WeightedPred += 1;

}
static i32 isSchedulable_weighted_end_chroma_l0() {
	i32 result;
	i32 tmp_isFifoFull;
	u32 local_cnt_i;
	u8 local_num_ref_idx_l0_active;

	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	local_cnt_i = cnt_i;
	local_num_ref_idx_l0_active = num_ref_idx_l0_active;
	result = tmp_isFifoFull && local_cnt_i == local_num_ref_idx_l0_active;
	return result;
}

static void weighted_end_chroma_l0() {


	cnt_i = 0;

	// Update ports indexes

}
static i32 isSchedulable_weighted_deltaLuma_l0_skip_loop() {
	i32 result;
	i32 tmp_isFifoFull;
	u32 local_cnt_i;
	u8 tmp_luma_weight_l0_flag;
	u8 tmp_chroma_weight_l0_flag;
	u8 local_num_ref_idx_l0_active;

	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	local_cnt_i = cnt_i;
	tmp_luma_weight_l0_flag = luma_weight_l0_flag[local_cnt_i];
	local_cnt_i = cnt_i;
	tmp_chroma_weight_l0_flag = chroma_weight_l0_flag[local_cnt_i];
	local_cnt_i = cnt_i;
	local_num_ref_idx_l0_active = num_ref_idx_l0_active;
	result = tmp_isFifoFull && tmp_luma_weight_l0_flag == 0 && tmp_chroma_weight_l0_flag == 0 && local_cnt_i < local_num_ref_idx_l0_active;
	return result;
}

static void weighted_deltaLuma_l0_skip_loop() {

	u32 local_cnt_i;

	local_cnt_i = cnt_i;
	cnt_i = local_cnt_i + 1;

	// Update ports indexes

}
static i32 isSchedulable_weighted_deltaLuma_l0_skip_loop_done() {
	i32 result;
	i32 tmp_isFifoFull;
	u32 local_cnt_i;
	u8 local_num_ref_idx_l0_active;
	u8 local_slice_type;
	u8 local_B_SLICE;

	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	local_cnt_i = cnt_i;
	local_num_ref_idx_l0_active = num_ref_idx_l0_active;
	local_slice_type = slice_type;
	local_B_SLICE = HevcDecoder_Algo_Parser_B_SLICE;
	result = tmp_isFifoFull && local_cnt_i == local_num_ref_idx_l0_active && local_slice_type == local_B_SLICE;
	return result;
}

static void weighted_deltaLuma_l0_skip_loop_done() {


	cnt_i = 0;

	// Update ports indexes

}
static i32 isSchedulable_weighted_deltaLuma_l0__skip_all() {
	i32 result;
	i32 tmp_isFifoFull;
	u32 local_cnt_i;
	u8 local_num_ref_idx_l0_active;
	u8 local_slice_type;
	u8 local_B_SLICE;

	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	local_cnt_i = cnt_i;
	local_num_ref_idx_l0_active = num_ref_idx_l0_active;
	local_slice_type = slice_type;
	local_B_SLICE = HevcDecoder_Algo_Parser_B_SLICE;
	result = tmp_isFifoFull && local_cnt_i == local_num_ref_idx_l0_active && local_slice_type != local_B_SLICE;
	return result;
}

static void weighted_deltaLuma_l0__skip_all() {


	cnt_i = 0;
	se_idx = 5;

	// Update ports indexes

}
static i32 isSchedulable_weighted_deltaLuma_l0_send() {
	i32 result;
	i32 tmp_isFifoFull;
	u32 local_cnt_i;
	u8 tmp_luma_weight_l0_flag;
	u8 local_num_ref_idx_l0_active;

	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	local_cnt_i = cnt_i;
	tmp_luma_weight_l0_flag = luma_weight_l0_flag[local_cnt_i];
	local_cnt_i = cnt_i;
	local_num_ref_idx_l0_active = num_ref_idx_l0_active;
	result = tmp_isFifoFull && tmp_luma_weight_l0_flag == 1 && local_cnt_i < local_num_ref_idx_l0_active;
	return result;
}

static void weighted_deltaLuma_l0_send() {

	u32 res[1];
	u32 tmp_res;
	u32 tmp_res0;
	i8 local_delta_luma_weight_l0;
	i8 local_luma_offset_l0;

	HevcDecoder_Algo_Parser_vld_se_name(fifo, res, "delta_luma_weight_lX                    ");
	tmp_res = res[0];
	delta_luma_weight_l0 = tmp_res;
	HevcDecoder_Algo_Parser_vld_se_name(fifo, res, "luma_offset_lX                          ");
	tmp_res0 = res[0];
	luma_offset_l0 = tmp_res0;
	local_delta_luma_weight_l0 = delta_luma_weight_l0;
	tokens_WeightedPred[(index_WeightedPred + (0)) % SIZE_WeightedPred] = local_delta_luma_weight_l0;
	local_luma_offset_l0 = luma_offset_l0;
	tokens_WeightedPred[(index_WeightedPred + (1)) % SIZE_WeightedPred] = local_luma_offset_l0;

	// Update ports indexes
	index_WeightedPred += 2;
	write_end_WeightedPred();

}
static void weighted_deltaLuma_l0_send_aligned() {

	u32 res[1];
	u32 tmp_res;
	u32 tmp_res0;
	i8 local_delta_luma_weight_l0;
	i8 local_luma_offset_l0;

	HevcDecoder_Algo_Parser_vld_se_name(fifo, res, "delta_luma_weight_lX                    ");
	tmp_res = res[0];
	delta_luma_weight_l0 = tmp_res;
	HevcDecoder_Algo_Parser_vld_se_name(fifo, res, "luma_offset_lX                          ");
	tmp_res0 = res[0];
	luma_offset_l0 = tmp_res0;
	local_delta_luma_weight_l0 = delta_luma_weight_l0;
	tokens_WeightedPred[(index_WeightedPred % SIZE_WeightedPred) + (0)] = local_delta_luma_weight_l0;
	local_luma_offset_l0 = luma_offset_l0;
	tokens_WeightedPred[(index_WeightedPred % SIZE_WeightedPred) + (1)] = local_luma_offset_l0;

	// Update ports indexes
	index_WeightedPred += 2;
	write_end_WeightedPred();

}
static i32 isSchedulable_weighted_deltaLuma_l0_skip() {
	i32 result;
	i32 tmp_isFifoFull;
	u32 local_cnt_i;
	u8 local_num_ref_idx_l0_active;
	u8 tmp_luma_weight_l0_flag;

	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	local_cnt_i = cnt_i;
	local_num_ref_idx_l0_active = num_ref_idx_l0_active;
	local_cnt_i = cnt_i;
	tmp_luma_weight_l0_flag = luma_weight_l0_flag[local_cnt_i];
	result = tmp_isFifoFull && local_cnt_i < local_num_ref_idx_l0_active && tmp_luma_weight_l0_flag == 0;
	return result;
}

static void weighted_deltaLuma_l0_skip() {



	// Update ports indexes

}
static i32 isSchedulable_weighted_deltaChroma_l0_skip() {
	i32 result;
	i32 tmp_isFifoFull;
	u32 local_cnt_i;
	u8 local_num_ref_idx_l0_active;
	u8 tmp_chroma_weight_l0_flag;

	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	local_cnt_i = cnt_i;
	local_num_ref_idx_l0_active = num_ref_idx_l0_active;
	local_cnt_i = cnt_i;
	tmp_chroma_weight_l0_flag = chroma_weight_l0_flag[local_cnt_i];
	result = tmp_isFifoFull && local_cnt_i < local_num_ref_idx_l0_active && tmp_chroma_weight_l0_flag == 0;
	return result;
}

static void weighted_deltaChroma_l0_skip() {

	u32 local_cnt_i;

	local_cnt_i = cnt_i;
	cnt_i = local_cnt_i + 1;

	// Update ports indexes

}
static i32 isSchedulable_weighted_deltaChroma_l0_send() {
	i32 result;
	i32 tmp_isFifoFull;
	u32 local_cnt_i;
	u8 local_num_ref_idx_l0_active;
	u8 tmp_chroma_weight_l0_flag;

	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	local_cnt_i = cnt_i;
	local_num_ref_idx_l0_active = num_ref_idx_l0_active;
	local_cnt_i = cnt_i;
	tmp_chroma_weight_l0_flag = chroma_weight_l0_flag[local_cnt_i];
	result = tmp_isFifoFull && local_cnt_i < local_num_ref_idx_l0_active && tmp_chroma_weight_l0_flag == 1;
	return result;
}

static void weighted_deltaChroma_l0_send() {

	u32 res[1];
	u32 tmp_res;
	i8 local_delta_chroma_weight_l00;

	HevcDecoder_Algo_Parser_vld_se_name(fifo, res, "delta_chroma_weight_lX                  ");
	tmp_res = res[0];
	delta_chroma_weight_l00 = tmp_res;
	local_delta_chroma_weight_l00 = delta_chroma_weight_l00;
	tokens_WeightedPred[(index_WeightedPred + (0)) % SIZE_WeightedPred] = local_delta_chroma_weight_l00;

	// Update ports indexes
	index_WeightedPred += 1;

}
static i32 isSchedulable_weighted_deltaChroma_offset_l0_send() {
	i32 result;
	i32 tmp_isFifoFull;
	u32 local_cnt_i;
	u8 local_num_ref_idx_l0_active;
	u8 tmp_chroma_weight_l0_flag;

	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	local_cnt_i = cnt_i;
	local_num_ref_idx_l0_active = num_ref_idx_l0_active;
	local_cnt_i = cnt_i;
	tmp_chroma_weight_l0_flag = chroma_weight_l0_flag[local_cnt_i];
	result = tmp_isFifoFull && local_cnt_i < local_num_ref_idx_l0_active && tmp_chroma_weight_l0_flag == 1;
	return result;
}

static void weighted_deltaChroma_offset_l0_send() {

	u32 res[1];
	u32 tmp_res;
	u32 tmp_res0;
	u32 tmp_res1;
	u32 local_cnt_i;
	i16 local_delta_chroma_offset_l00;
	i8 local_delta_chroma_weight_l01;
	i16 local_delta_chroma_offset_l01;

	HevcDecoder_Algo_Parser_vld_se_name(fifo, res, "delta_chroma_offset_lX                  ");
	tmp_res = res[0];
	delta_chroma_offset_l00 = tmp_res;
	HevcDecoder_Algo_Parser_vld_se_name(fifo, res, "delta_chroma_weight_lX                  ");
	tmp_res0 = res[0];
	delta_chroma_weight_l01 = tmp_res0;
	HevcDecoder_Algo_Parser_vld_se_name(fifo, res, "delta_chroma_offset_lX                  ");
	tmp_res1 = res[0];
	delta_chroma_offset_l01 = tmp_res1;
	local_cnt_i = cnt_i;
	cnt_i = local_cnt_i + 1;
	local_delta_chroma_offset_l00 = delta_chroma_offset_l00;
	tokens_WeightedPred[(index_WeightedPred + (0)) % SIZE_WeightedPred] = local_delta_chroma_offset_l00;
	local_delta_chroma_weight_l01 = delta_chroma_weight_l01;
	tokens_WeightedPred[(index_WeightedPred + (1)) % SIZE_WeightedPred] = local_delta_chroma_weight_l01;
	local_delta_chroma_offset_l01 = delta_chroma_offset_l01;
	tokens_WeightedPred[(index_WeightedPred + (2)) % SIZE_WeightedPred] = local_delta_chroma_offset_l01;

	// Update ports indexes
	index_WeightedPred += 3;
	write_end_WeightedPred();

}
static void weighted_deltaChroma_offset_l0_send_aligned() {

	u32 res[1];
	u32 tmp_res;
	u32 tmp_res0;
	u32 tmp_res1;
	u32 local_cnt_i;
	i16 local_delta_chroma_offset_l00;
	i8 local_delta_chroma_weight_l01;
	i16 local_delta_chroma_offset_l01;

	HevcDecoder_Algo_Parser_vld_se_name(fifo, res, "delta_chroma_offset_lX                  ");
	tmp_res = res[0];
	delta_chroma_offset_l00 = tmp_res;
	HevcDecoder_Algo_Parser_vld_se_name(fifo, res, "delta_chroma_weight_lX                  ");
	tmp_res0 = res[0];
	delta_chroma_weight_l01 = tmp_res0;
	HevcDecoder_Algo_Parser_vld_se_name(fifo, res, "delta_chroma_offset_lX                  ");
	tmp_res1 = res[0];
	delta_chroma_offset_l01 = tmp_res1;
	local_cnt_i = cnt_i;
	cnt_i = local_cnt_i + 1;
	local_delta_chroma_offset_l00 = delta_chroma_offset_l00;
	tokens_WeightedPred[(index_WeightedPred % SIZE_WeightedPred) + (0)] = local_delta_chroma_offset_l00;
	local_delta_chroma_weight_l01 = delta_chroma_weight_l01;
	tokens_WeightedPred[(index_WeightedPred % SIZE_WeightedPred) + (1)] = local_delta_chroma_weight_l01;
	local_delta_chroma_offset_l01 = delta_chroma_offset_l01;
	tokens_WeightedPred[(index_WeightedPred % SIZE_WeightedPred) + (2)] = local_delta_chroma_offset_l01;

	// Update ports indexes
	index_WeightedPred += 3;
	write_end_WeightedPred();

}
static i32 isSchedulable_weighted_luma_l1() {
	i32 result;
	i32 tmp_isFifoFull;
	u8 local_slice_type;
	u8 local_B_SLICE;

	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	local_slice_type = slice_type;
	local_B_SLICE = HevcDecoder_Algo_Parser_B_SLICE;
	result = tmp_isFifoFull && local_slice_type == local_B_SLICE;
	return result;
}

static void weighted_luma_l1() {

	u32 res[1];
	u32 local_cnt_i;
	u32 tmp_res;
	u8 tmp_luma_weight_l1_flag;

	HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "luma_weight_lX_flag                     ");
	local_cnt_i = cnt_i;
	tmp_res = res[0];
	luma_weight_l1_flag[local_cnt_i] = tmp_res;
	local_cnt_i = cnt_i;
	cnt_i = local_cnt_i + 1;
	local_cnt_i = cnt_i;
	tmp_luma_weight_l1_flag = luma_weight_l1_flag[local_cnt_i - 1];
	tokens_WeightedPred[(index_WeightedPred + (0)) % SIZE_WeightedPred] = tmp_luma_weight_l1_flag;

	// Update ports indexes
	index_WeightedPred += 1;

}
static i32 isSchedulable_weighted_end_luma_l1() {
	i32 result;
	i32 tmp_isFifoFull;
	u8 local_slice_type;
	u8 local_B_SLICE;
	u32 local_cnt_i;
	u8 local_num_ref_idx_l1_active;

	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	local_slice_type = slice_type;
	local_B_SLICE = HevcDecoder_Algo_Parser_B_SLICE;
	local_cnt_i = cnt_i;
	local_num_ref_idx_l1_active = num_ref_idx_l1_active;
	result = tmp_isFifoFull && local_slice_type == local_B_SLICE && local_cnt_i == local_num_ref_idx_l1_active;
	return result;
}

static void weighted_end_luma_l1() {


	cnt_i = 0;

	// Update ports indexes

}
static i32 isSchedulable_weighted_chroma_l1_skip() {
	i32 result;
	i32 tmp_isFifoFull;
	u16 local_sps_id;
	u8 tmp_sps_chroma_format_idc;

	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	local_sps_id = sps_id;
	tmp_sps_chroma_format_idc = sps_chroma_format_idc[local_sps_id];
	result = tmp_isFifoFull && tmp_sps_chroma_format_idc == 0;
	return result;
}

static void weighted_chroma_l1_skip() {


	cnt_i = 0;

	// Update ports indexes

}
static i32 isSchedulable_weighted_chroma_l1() {
	i32 result;
	i32 tmp_isFifoFull;
	u16 local_sps_id;
	u8 tmp_sps_chroma_format_idc;

	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	local_sps_id = sps_id;
	tmp_sps_chroma_format_idc = sps_chroma_format_idc[local_sps_id];
	result = tmp_isFifoFull && tmp_sps_chroma_format_idc != 0;
	return result;
}

static void weighted_chroma_l1() {

	u32 res[1];
	u32 local_cnt_i;
	u32 tmp_res;
	u8 tmp_chroma_weight_l1_flag;

	HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "chroma_weight_lX_flag                   ");
	local_cnt_i = cnt_i;
	tmp_res = res[0];
	chroma_weight_l1_flag[local_cnt_i] = tmp_res;
	local_cnt_i = cnt_i;
	cnt_i = local_cnt_i + 1;
	local_cnt_i = cnt_i;
	tmp_chroma_weight_l1_flag = chroma_weight_l1_flag[local_cnt_i - 1];
	tokens_WeightedPred[(index_WeightedPred + (0)) % SIZE_WeightedPred] = tmp_chroma_weight_l1_flag;

	// Update ports indexes
	index_WeightedPred += 1;

}
static i32 isSchedulable_weighted_end_chroma_l1() {
	i32 result;
	i32 tmp_isFifoFull;
	u16 local_sps_id;
	u8 tmp_sps_chroma_format_idc;
	u32 local_cnt_i;
	u8 local_num_ref_idx_l1_active;

	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	local_sps_id = sps_id;
	tmp_sps_chroma_format_idc = sps_chroma_format_idc[local_sps_id];
	local_cnt_i = cnt_i;
	local_num_ref_idx_l1_active = num_ref_idx_l1_active;
	result = tmp_isFifoFull && tmp_sps_chroma_format_idc != 0 && local_cnt_i == local_num_ref_idx_l1_active;
	return result;
}

static void weighted_end_chroma_l1() {


	cnt_i = 0;

	// Update ports indexes

}
static i32 isSchedulable_weighted_deltaLuma_l1_skip_loop() {
	i32 result;
	i32 tmp_isFifoFull;
	u32 local_cnt_i;
	u8 tmp_luma_weight_l1_flag;
	u8 tmp_chroma_weight_l1_flag;

	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	local_cnt_i = cnt_i;
	tmp_luma_weight_l1_flag = luma_weight_l1_flag[local_cnt_i];
	local_cnt_i = cnt_i;
	tmp_chroma_weight_l1_flag = chroma_weight_l1_flag[local_cnt_i];
	result = tmp_isFifoFull && tmp_luma_weight_l1_flag == 0 && tmp_chroma_weight_l1_flag == 0;
	return result;
}

static void weighted_deltaLuma_l1_skip_loop() {

	u32 local_cnt_i;

	local_cnt_i = cnt_i;
	cnt_i = local_cnt_i + 1;

	// Update ports indexes

}
static i32 isSchedulable_weighted_deltaLuma_l1_skip_loop_done() {
	i32 result;
	i32 tmp_isFifoFull;
	u32 local_cnt_i;
	u8 local_num_ref_idx_l1_active;

	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	local_cnt_i = cnt_i;
	local_num_ref_idx_l1_active = num_ref_idx_l1_active;
	result = tmp_isFifoFull && local_cnt_i == local_num_ref_idx_l1_active;
	return result;
}

static void weighted_deltaLuma_l1_skip_loop_done() {


	cnt_i = 0;
	se_idx = 5;

	// Update ports indexes

}
static i32 isSchedulable_weighted_deltaLuma_l1_send() {
	i32 result;
	i32 tmp_isFifoFull;
	u32 local_cnt_i;
	u8 local_num_ref_idx_l1_active;
	u8 tmp_luma_weight_l1_flag;

	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	local_cnt_i = cnt_i;
	local_num_ref_idx_l1_active = num_ref_idx_l1_active;
	local_cnt_i = cnt_i;
	tmp_luma_weight_l1_flag = luma_weight_l1_flag[local_cnt_i];
	result = tmp_isFifoFull && local_cnt_i < local_num_ref_idx_l1_active && tmp_luma_weight_l1_flag == 1;
	return result;
}

static void weighted_deltaLuma_l1_send() {

	u32 res[1];
	u32 tmp_res;
	u32 tmp_res0;
	i8 local_delta_luma_weight_l1;
	i8 local_luma_offset_l1;

	HevcDecoder_Algo_Parser_vld_se_name(fifo, res, "delta_luma_weight_lX                    ");
	tmp_res = res[0];
	delta_luma_weight_l1 = tmp_res;
	HevcDecoder_Algo_Parser_vld_se_name(fifo, res, "luma_offset_lX                          ");
	tmp_res0 = res[0];
	luma_offset_l1 = tmp_res0;
	local_delta_luma_weight_l1 = delta_luma_weight_l1;
	tokens_WeightedPred[(index_WeightedPred + (0)) % SIZE_WeightedPred] = local_delta_luma_weight_l1;
	local_luma_offset_l1 = luma_offset_l1;
	tokens_WeightedPred[(index_WeightedPred + (1)) % SIZE_WeightedPred] = local_luma_offset_l1;

	// Update ports indexes
	index_WeightedPred += 2;
	write_end_WeightedPred();

}
static void weighted_deltaLuma_l1_send_aligned() {

	u32 res[1];
	u32 tmp_res;
	u32 tmp_res0;
	i8 local_delta_luma_weight_l1;
	i8 local_luma_offset_l1;

	HevcDecoder_Algo_Parser_vld_se_name(fifo, res, "delta_luma_weight_lX                    ");
	tmp_res = res[0];
	delta_luma_weight_l1 = tmp_res;
	HevcDecoder_Algo_Parser_vld_se_name(fifo, res, "luma_offset_lX                          ");
	tmp_res0 = res[0];
	luma_offset_l1 = tmp_res0;
	local_delta_luma_weight_l1 = delta_luma_weight_l1;
	tokens_WeightedPred[(index_WeightedPred % SIZE_WeightedPred) + (0)] = local_delta_luma_weight_l1;
	local_luma_offset_l1 = luma_offset_l1;
	tokens_WeightedPred[(index_WeightedPred % SIZE_WeightedPred) + (1)] = local_luma_offset_l1;

	// Update ports indexes
	index_WeightedPred += 2;
	write_end_WeightedPred();

}
static i32 isSchedulable_weighted_deltaLuma_l1_skip() {
	i32 result;
	i32 tmp_isFifoFull;
	u32 local_cnt_i;
	u8 local_num_ref_idx_l1_active;
	u8 tmp_luma_weight_l1_flag;

	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	local_cnt_i = cnt_i;
	local_num_ref_idx_l1_active = num_ref_idx_l1_active;
	local_cnt_i = cnt_i;
	tmp_luma_weight_l1_flag = luma_weight_l1_flag[local_cnt_i];
	result = tmp_isFifoFull && local_cnt_i < local_num_ref_idx_l1_active && tmp_luma_weight_l1_flag == 0;
	return result;
}

static void weighted_deltaLuma_l1_skip() {



	// Update ports indexes

}
static i32 isSchedulable_weighted_deltaChroma_l1_skip() {
	i32 result;
	i32 tmp_isFifoFull;
	u32 local_cnt_i;
	u8 local_num_ref_idx_l1_active;
	u8 tmp_chroma_weight_l1_flag;

	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	local_cnt_i = cnt_i;
	local_num_ref_idx_l1_active = num_ref_idx_l1_active;
	local_cnt_i = cnt_i;
	tmp_chroma_weight_l1_flag = chroma_weight_l1_flag[local_cnt_i];
	result = tmp_isFifoFull && local_cnt_i < local_num_ref_idx_l1_active && tmp_chroma_weight_l1_flag == 0;
	return result;
}

static void weighted_deltaChroma_l1_skip() {

	u32 local_cnt_i;

	local_cnt_i = cnt_i;
	cnt_i = local_cnt_i + 1;

	// Update ports indexes

}
static i32 isSchedulable_weighted_deltaChroma_l1_send() {
	i32 result;
	i32 tmp_isFifoFull;
	u32 local_cnt_i;
	u8 local_num_ref_idx_l1_active;
	u8 tmp_chroma_weight_l1_flag;

	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	local_cnt_i = cnt_i;
	local_num_ref_idx_l1_active = num_ref_idx_l1_active;
	local_cnt_i = cnt_i;
	tmp_chroma_weight_l1_flag = chroma_weight_l1_flag[local_cnt_i];
	result = tmp_isFifoFull && local_cnt_i < local_num_ref_idx_l1_active && tmp_chroma_weight_l1_flag == 1;
	return result;
}

static void weighted_deltaChroma_l1_send() {

	u32 res[1];
	u32 tmp_res;
	i8 local_delta_chroma_weight_l10;

	HevcDecoder_Algo_Parser_vld_se_name(fifo, res, "delta_chroma_weight_lX                  ");
	tmp_res = res[0];
	delta_chroma_weight_l10 = tmp_res;
	local_delta_chroma_weight_l10 = delta_chroma_weight_l10;
	tokens_WeightedPred[(index_WeightedPred + (0)) % SIZE_WeightedPred] = local_delta_chroma_weight_l10;

	// Update ports indexes
	index_WeightedPred += 1;

}
static i32 isSchedulable_weighted_deltaChroma_offset_l1_send() {
	i32 result;
	i32 tmp_isFifoFull;
	u32 local_cnt_i;
	u8 local_num_ref_idx_l1_active;
	u8 tmp_chroma_weight_l1_flag;

	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	local_cnt_i = cnt_i;
	local_num_ref_idx_l1_active = num_ref_idx_l1_active;
	local_cnt_i = cnt_i;
	tmp_chroma_weight_l1_flag = chroma_weight_l1_flag[local_cnt_i];
	result = tmp_isFifoFull && local_cnt_i < local_num_ref_idx_l1_active && tmp_chroma_weight_l1_flag == 1;
	return result;
}

static void weighted_deltaChroma_offset_l1_send() {

	u32 res[1];
	u32 tmp_res;
	u32 tmp_res0;
	u32 tmp_res1;
	u32 local_cnt_i;
	i16 local_delta_chroma_offset_l10;
	i8 local_delta_chroma_weight_l11;
	i16 local_delta_chroma_offset_l11;

	HevcDecoder_Algo_Parser_vld_se_name(fifo, res, "delta_chroma_offset_lX                  ");
	tmp_res = res[0];
	delta_chroma_offset_l10 = tmp_res;
	HevcDecoder_Algo_Parser_vld_se_name(fifo, res, "delta_chroma_weight_lX                  ");
	tmp_res0 = res[0];
	delta_chroma_weight_l11 = tmp_res0;
	HevcDecoder_Algo_Parser_vld_se_name(fifo, res, "delta_chroma_offset_lX                  ");
	tmp_res1 = res[0];
	delta_chroma_offset_l11 = tmp_res1;
	local_cnt_i = cnt_i;
	cnt_i = local_cnt_i + 1;
	local_delta_chroma_offset_l10 = delta_chroma_offset_l10;
	tokens_WeightedPred[(index_WeightedPred + (0)) % SIZE_WeightedPred] = local_delta_chroma_offset_l10;
	local_delta_chroma_weight_l11 = delta_chroma_weight_l11;
	tokens_WeightedPred[(index_WeightedPred + (1)) % SIZE_WeightedPred] = local_delta_chroma_weight_l11;
	local_delta_chroma_offset_l11 = delta_chroma_offset_l11;
	tokens_WeightedPred[(index_WeightedPred + (2)) % SIZE_WeightedPred] = local_delta_chroma_offset_l11;

	// Update ports indexes
	index_WeightedPred += 3;
	write_end_WeightedPred();

}
static void weighted_deltaChroma_offset_l1_send_aligned() {

	u32 res[1];
	u32 tmp_res;
	u32 tmp_res0;
	u32 tmp_res1;
	u32 local_cnt_i;
	i16 local_delta_chroma_offset_l10;
	i8 local_delta_chroma_weight_l11;
	i16 local_delta_chroma_offset_l11;

	HevcDecoder_Algo_Parser_vld_se_name(fifo, res, "delta_chroma_offset_lX                  ");
	tmp_res = res[0];
	delta_chroma_offset_l10 = tmp_res;
	HevcDecoder_Algo_Parser_vld_se_name(fifo, res, "delta_chroma_weight_lX                  ");
	tmp_res0 = res[0];
	delta_chroma_weight_l11 = tmp_res0;
	HevcDecoder_Algo_Parser_vld_se_name(fifo, res, "delta_chroma_offset_lX                  ");
	tmp_res1 = res[0];
	delta_chroma_offset_l11 = tmp_res1;
	local_cnt_i = cnt_i;
	cnt_i = local_cnt_i + 1;
	local_delta_chroma_offset_l10 = delta_chroma_offset_l10;
	tokens_WeightedPred[(index_WeightedPred % SIZE_WeightedPred) + (0)] = local_delta_chroma_offset_l10;
	local_delta_chroma_weight_l11 = delta_chroma_weight_l11;
	tokens_WeightedPred[(index_WeightedPred % SIZE_WeightedPred) + (1)] = local_delta_chroma_weight_l11;
	local_delta_chroma_offset_l11 = delta_chroma_offset_l11;
	tokens_WeightedPred[(index_WeightedPred % SIZE_WeightedPred) + (2)] = local_delta_chroma_offset_l11;

	// Update ports indexes
	index_WeightedPred += 3;
	write_end_WeightedPred();

}
static i32 isSchedulable_read_SliceHeader_se_idx_5() {
	i32 result;
	u16 local_se_idx;
	i32 tmp_isFifoFull;

	local_se_idx = se_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	result = local_se_idx == 5 && tmp_isFifoFull;
	return result;
}

static void read_SliceHeader_se_idx_5() {

	u32 res[1];
	u16 local_pps_id;
	u8 slice_disable_deblocking_filter_flag;
	i8 betaOff;
	i8 tcOff;
	u8 local_slice_type;
	u8 local_P_SLICE;
	u8 local_B_SLICE;
	u32 tmp_res;
	i32 tmp_pps_init_qp_minus26;
	u32 tmp_res0;
	u8 tmp_pps_slice_chroma_qp_offsets_present_flag;
	u32 tmp_res1;
	u32 tmp_res2;
	u8 tmp_pps_deblocking_filter_control_present_flag;
	u8 tmp_deblocking_filter_override_enabled_flag;
	u32 tmp_res3;
	u32 tmp_res4;
	u32 tmp_res5;
	u16 local_sps_id;
	u8 tmp_pps_loop_filter_across_slice_enabled_flag;
	u8 tmp_slice_sample_adaptive_offset_flag;
	u8 tmp_slice_sample_adaptive_offset_flag0;
	u16 local_se_idx;
	i8 tmp_pps_cb_qp_offset;
	i8 local_slice_cb_qp_offset;
	i8 tmp_pps_cr_qp_offset;
	i8 local_slice_cr_qp_offset;

	local_pps_id = pps_id;
	slice_disable_deblocking_filter_flag = pps_disable_deblocking_filter_flag[local_pps_id];
	local_pps_id = pps_id;
	betaOff = pps_beta_offset[local_pps_id];
	local_pps_id = pps_id;
	tcOff = pps_tc_offset[local_pps_id];
	local_slice_type = slice_type;
	local_P_SLICE = HevcDecoder_Algo_Parser_P_SLICE;
	local_slice_type = slice_type;
	local_B_SLICE = HevcDecoder_Algo_Parser_B_SLICE;
	if (local_slice_type == local_P_SLICE || local_slice_type == local_B_SLICE) {
		HevcDecoder_Algo_Parser_vld_ue_name(fifo, res, "five_minus_max_num_merge_cand           ");
		tmp_res = res[0];
		MaxNumMergeCand = 5 - tmp_res;
	}
	HevcDecoder_Algo_Parser_vld_se_name(fifo, res, "slice_qp_delta                          ");
	local_pps_id = pps_id;
	tmp_pps_init_qp_minus26 = pps_init_qp_minus26[local_pps_id];
	tmp_res0 = res[0];
	slice_qp = tmp_pps_init_qp_minus26 + 26 + tmp_res0;
	slice_cb_qp_offset = 0;
	slice_cr_qp_offset = 0;
	local_pps_id = pps_id;
	tmp_pps_slice_chroma_qp_offsets_present_flag = pps_slice_chroma_qp_offsets_present_flag[local_pps_id];
	if (tmp_pps_slice_chroma_qp_offsets_present_flag == 1) {
		HevcDecoder_Algo_Parser_vld_se_name(fifo, res, "slice_cb_qp_offset                      ");
		tmp_res1 = res[0];
		slice_cb_qp_offset = tmp_res1;
		HevcDecoder_Algo_Parser_vld_se_name(fifo, res, "slice_cr_qp_offset                      ");
		tmp_res2 = res[0];
		slice_cr_qp_offset = tmp_res2;
	}
	local_pps_id = pps_id;
	tmp_pps_deblocking_filter_control_present_flag = pps_deblocking_filter_control_present_flag[local_pps_id];
	if (tmp_pps_deblocking_filter_control_present_flag == 1) {
		res[0] = 0;
		local_pps_id = pps_id;
		tmp_deblocking_filter_override_enabled_flag = deblocking_filter_override_enabled_flag[local_pps_id];
		if (tmp_deblocking_filter_override_enabled_flag == 1) {
			HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "deblocking_filter_override_flag         ");
		}
		tmp_res3 = res[0];
		if (tmp_res3 == 1) {
			HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "slice_disable_deblocking_filter_flag    ");
			slice_disable_deblocking_filter_flag = res[0];
			if (slice_disable_deblocking_filter_flag == 0) {
				HevcDecoder_Algo_Parser_vld_se_name(fifo, res, "beta_offset_div2                        ");
				tmp_res4 = res[0];
				betaOff = tmp_res4 << 1;
				HevcDecoder_Algo_Parser_vld_se_name(fifo, res, "tc_offset_div2                          ");
				tmp_res5 = res[0];
				tcOff = tmp_res5 << 1;
			}
		}
	}
	local_sps_id = sps_id;
	tmp_pps_loop_filter_across_slice_enabled_flag = pps_loop_filter_across_slice_enabled_flag[local_sps_id];
	tmp_slice_sample_adaptive_offset_flag = slice_sample_adaptive_offset_flag[0];
	tmp_slice_sample_adaptive_offset_flag0 = slice_sample_adaptive_offset_flag[1];
	if (tmp_pps_loop_filter_across_slice_enabled_flag == 1 && (tmp_slice_sample_adaptive_offset_flag == 1 || tmp_slice_sample_adaptive_offset_flag0 == 1 || slice_disable_deblocking_filter_flag == 0)) {
		HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "slice_loop_filter_across_slices_enabled_flag");
	}
	local_se_idx = se_idx;
	se_idx = local_se_idx + 1;
	tokens_DBFDisable[(index_DBFDisable + (0)) % SIZE_DBFDisable] = slice_disable_deblocking_filter_flag != 0;
	tokens_DbfSe[(index_DbfSe % SIZE_DbfSe) + (0)] = betaOff;
	tokens_DbfSe[(index_DbfSe % SIZE_DbfSe) + (1)] = tcOff;
	local_pps_id = pps_id;
	tmp_pps_cb_qp_offset = pps_cb_qp_offset[local_pps_id];
	local_slice_cb_qp_offset = slice_cb_qp_offset;
	tokens_DbfSe[(index_DbfSe % SIZE_DbfSe) + (2)] = tmp_pps_cb_qp_offset + local_slice_cb_qp_offset;
	local_pps_id = pps_id;
	tmp_pps_cr_qp_offset = pps_cr_qp_offset[local_pps_id];
	local_slice_cr_qp_offset = slice_cr_qp_offset;
	tokens_DbfSe[(index_DbfSe % SIZE_DbfSe) + (3)] = tmp_pps_cr_qp_offset + local_slice_cr_qp_offset;

	// Update ports indexes
	index_DBFDisable += 1;
	index_DbfSe += 4;
	write_end_DbfSe();

}
static void read_SliceHeader_se_idx_5_aligned() {

	u32 res[1];
	u16 local_pps_id;
	u8 slice_disable_deblocking_filter_flag;
	i8 betaOff;
	i8 tcOff;
	u8 local_slice_type;
	u8 local_P_SLICE;
	u8 local_B_SLICE;
	u32 tmp_res;
	i32 tmp_pps_init_qp_minus26;
	u32 tmp_res0;
	u8 tmp_pps_slice_chroma_qp_offsets_present_flag;
	u32 tmp_res1;
	u32 tmp_res2;
	u8 tmp_pps_deblocking_filter_control_present_flag;
	u8 tmp_deblocking_filter_override_enabled_flag;
	u32 tmp_res3;
	u32 tmp_res4;
	u32 tmp_res5;
	u16 local_sps_id;
	u8 tmp_pps_loop_filter_across_slice_enabled_flag;
	u8 tmp_slice_sample_adaptive_offset_flag;
	u8 tmp_slice_sample_adaptive_offset_flag0;
	u16 local_se_idx;
	i8 tmp_pps_cb_qp_offset;
	i8 local_slice_cb_qp_offset;
	i8 tmp_pps_cr_qp_offset;
	i8 local_slice_cr_qp_offset;

	local_pps_id = pps_id;
	slice_disable_deblocking_filter_flag = pps_disable_deblocking_filter_flag[local_pps_id];
	local_pps_id = pps_id;
	betaOff = pps_beta_offset[local_pps_id];
	local_pps_id = pps_id;
	tcOff = pps_tc_offset[local_pps_id];
	local_slice_type = slice_type;
	local_P_SLICE = HevcDecoder_Algo_Parser_P_SLICE;
	local_slice_type = slice_type;
	local_B_SLICE = HevcDecoder_Algo_Parser_B_SLICE;
	if (local_slice_type == local_P_SLICE || local_slice_type == local_B_SLICE) {
		HevcDecoder_Algo_Parser_vld_ue_name(fifo, res, "five_minus_max_num_merge_cand           ");
		tmp_res = res[0];
		MaxNumMergeCand = 5 - tmp_res;
	}
	HevcDecoder_Algo_Parser_vld_se_name(fifo, res, "slice_qp_delta                          ");
	local_pps_id = pps_id;
	tmp_pps_init_qp_minus26 = pps_init_qp_minus26[local_pps_id];
	tmp_res0 = res[0];
	slice_qp = tmp_pps_init_qp_minus26 + 26 + tmp_res0;
	slice_cb_qp_offset = 0;
	slice_cr_qp_offset = 0;
	local_pps_id = pps_id;
	tmp_pps_slice_chroma_qp_offsets_present_flag = pps_slice_chroma_qp_offsets_present_flag[local_pps_id];
	if (tmp_pps_slice_chroma_qp_offsets_present_flag == 1) {
		HevcDecoder_Algo_Parser_vld_se_name(fifo, res, "slice_cb_qp_offset                      ");
		tmp_res1 = res[0];
		slice_cb_qp_offset = tmp_res1;
		HevcDecoder_Algo_Parser_vld_se_name(fifo, res, "slice_cr_qp_offset                      ");
		tmp_res2 = res[0];
		slice_cr_qp_offset = tmp_res2;
	}
	local_pps_id = pps_id;
	tmp_pps_deblocking_filter_control_present_flag = pps_deblocking_filter_control_present_flag[local_pps_id];
	if (tmp_pps_deblocking_filter_control_present_flag == 1) {
		res[0] = 0;
		local_pps_id = pps_id;
		tmp_deblocking_filter_override_enabled_flag = deblocking_filter_override_enabled_flag[local_pps_id];
		if (tmp_deblocking_filter_override_enabled_flag == 1) {
			HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "deblocking_filter_override_flag         ");
		}
		tmp_res3 = res[0];
		if (tmp_res3 == 1) {
			HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "slice_disable_deblocking_filter_flag    ");
			slice_disable_deblocking_filter_flag = res[0];
			if (slice_disable_deblocking_filter_flag == 0) {
				HevcDecoder_Algo_Parser_vld_se_name(fifo, res, "beta_offset_div2                        ");
				tmp_res4 = res[0];
				betaOff = tmp_res4 << 1;
				HevcDecoder_Algo_Parser_vld_se_name(fifo, res, "tc_offset_div2                          ");
				tmp_res5 = res[0];
				tcOff = tmp_res5 << 1;
			}
		}
	}
	local_sps_id = sps_id;
	tmp_pps_loop_filter_across_slice_enabled_flag = pps_loop_filter_across_slice_enabled_flag[local_sps_id];
	tmp_slice_sample_adaptive_offset_flag = slice_sample_adaptive_offset_flag[0];
	tmp_slice_sample_adaptive_offset_flag0 = slice_sample_adaptive_offset_flag[1];
	if (tmp_pps_loop_filter_across_slice_enabled_flag == 1 && (tmp_slice_sample_adaptive_offset_flag == 1 || tmp_slice_sample_adaptive_offset_flag0 == 1 || slice_disable_deblocking_filter_flag == 0)) {
		HevcDecoder_Algo_Parser_vld_u_name(1, fifo, res, "slice_loop_filter_across_slices_enabled_flag");
	}
	local_se_idx = se_idx;
	se_idx = local_se_idx + 1;
	tokens_DBFDisable[(index_DBFDisable + (0)) % SIZE_DBFDisable] = slice_disable_deblocking_filter_flag != 0;
	tokens_DbfSe[(index_DbfSe % SIZE_DbfSe) + (0)] = betaOff;
	tokens_DbfSe[(index_DbfSe % SIZE_DbfSe) + (1)] = tcOff;
	local_pps_id = pps_id;
	tmp_pps_cb_qp_offset = pps_cb_qp_offset[local_pps_id];
	local_slice_cb_qp_offset = slice_cb_qp_offset;
	tokens_DbfSe[(index_DbfSe % SIZE_DbfSe) + (2)] = tmp_pps_cb_qp_offset + local_slice_cb_qp_offset;
	local_pps_id = pps_id;
	tmp_pps_cr_qp_offset = pps_cr_qp_offset[local_pps_id];
	local_slice_cr_qp_offset = slice_cr_qp_offset;
	tokens_DbfSe[(index_DbfSe % SIZE_DbfSe) + (3)] = tmp_pps_cr_qp_offset + local_slice_cr_qp_offset;

	// Update ports indexes
	index_DBFDisable += 1;
	index_DbfSe += 4;
	write_end_DbfSe();

}
static i32 isSchedulable_read_SliceHeader_se_idx_6() {
	i32 result;
	u16 local_se_idx;
	i32 tmp_isFifoFull;

	local_se_idx = se_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	result = local_se_idx == 6 && tmp_isFifoFull;
	return result;
}

static void read_SliceHeader_se_idx_6() {

	u32 res[1];
	u16 local_pps_id;
	u8 tmp_pps_tiles_enabled_flag;
	u8 tmp_pps_entropy_coding_sync_enabled_flag;
	u32 tmp_res;
	u16 local_num_entry_point_offsets;
	u32 local_NUM_ENTRY_MAX;
	u32 tmp_res0;
	u32 local_TILE_SPLIT_ENABLE;
	u8 tmp_pps_num_tile_columns_minus1;
	u8 tmp_pps_num_tile_rows_minus1;

	se_idx = 8;
	local_pps_id = pps_id;
	tmp_pps_tiles_enabled_flag = pps_tiles_enabled_flag[local_pps_id];
	local_pps_id = pps_id;
	tmp_pps_entropy_coding_sync_enabled_flag = pps_entropy_coding_sync_enabled_flag[local_pps_id];
	if (tmp_pps_tiles_enabled_flag == 1 || tmp_pps_entropy_coding_sync_enabled_flag == 1) {
		HevcDecoder_Algo_Parser_vld_ue_name(fifo, res, "num_entry_point_offsets                 ");
		tmp_res = res[0];
		num_entry_point_offsets = tmp_res;
		local_num_entry_point_offsets = num_entry_point_offsets;
		local_NUM_ENTRY_MAX = NUM_ENTRY_MAX;
		if (local_num_entry_point_offsets > local_NUM_ENTRY_MAX) {
			printf("ERROR: fix NUM_ENTRY_MAX\n");
		}
		local_num_entry_point_offsets = num_entry_point_offsets;
		if (local_num_entry_point_offsets > 0) {
			HevcDecoder_Algo_Parser_vld_ue_name(fifo, res, "offset_len_minus1                       ");
			tmp_res0 = res[0];
			offset_len = tmp_res0 + 1;
			se_idx = 7;
		}
	}
	local_TILE_SPLIT_ENABLE = TILE_SPLIT_ENABLE;
	if (local_TILE_SPLIT_ENABLE != 0) {
		num_entry_offsets = 1;
	} else {
		local_pps_id = pps_id;
		tmp_pps_num_tile_columns_minus1 = pps_num_tile_columns_minus1[local_pps_id];
		local_pps_id = pps_id;
		tmp_pps_num_tile_rows_minus1 = pps_num_tile_rows_minus1[local_pps_id];
		num_entry_offsets = (tmp_pps_num_tile_columns_minus1 + 1) * (tmp_pps_num_tile_rows_minus1 + 1);
	}

	// Update ports indexes

}
static i32 isSchedulable_read_SliceHeader_se_idx_7_loop() {
	i32 result;
	u16 local_se_idx;
	i32 tmp_isFifoFull;
	u32 local_cnt_i;
	u16 local_num_entry_point_offsets;

	local_se_idx = se_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	local_cnt_i = cnt_i;
	local_num_entry_point_offsets = num_entry_point_offsets;
	result = local_se_idx == 7 && tmp_isFifoFull && local_cnt_i < local_num_entry_point_offsets;
	return result;
}

static void read_SliceHeader_se_idx_7_loop() {

	u32 res[1];
	u16 local_offset_len;
	u32 local_cnt_i;
	u32 tmp_res;

	local_offset_len = offset_len;
	if (local_offset_len > 32) {
		printf("ERROR with vld_ue : check offset_len size\n");
	}
	local_offset_len = offset_len;
	HevcDecoder_Algo_Parser_vld_u_name(local_offset_len, fifo, res, "entry_point_offset                      ");
	local_cnt_i = cnt_i;
	tmp_res = res[0];
	entryOffsetsTab[local_cnt_i] = tmp_res;
	local_cnt_i = cnt_i;
	cnt_i = local_cnt_i + 1;

	// Update ports indexes

}
static i32 isSchedulable_read_SliceHeader_se_idx_7_endLoop() {
	i32 result;
	u16 local_se_idx;
	i32 tmp_isFifoFull;
	u32 local_cnt_i;
	u16 local_num_entry_point_offsets;

	local_se_idx = se_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	local_cnt_i = cnt_i;
	local_num_entry_point_offsets = num_entry_point_offsets;
	result = local_se_idx == 7 && tmp_isFifoFull && local_cnt_i == local_num_entry_point_offsets;
	return result;
}

static void read_SliceHeader_se_idx_7_endLoop() {


	cnt_i = 0;
	se_idx = 8;

	// Update ports indexes

}
static i32 isSchedulable_read_SliceHeader_se_idx_8() {
	i32 result;
	u16 local_se_idx;
	i32 tmp_isFifoFull;

	local_se_idx = se_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	result = local_se_idx == 8 && tmp_isFifoFull;
	return result;
}

static void read_SliceHeader_se_idx_8() {

	i32 res[1];
	u16 local_pps_id;
	u8 tmp_pps_slice_segment_header_extension_present_flag;
	i32 tmp_res;

	se_idx = 100;
	local_pps_id = pps_id;
	tmp_pps_slice_segment_header_extension_present_flag = pps_slice_segment_header_extension_present_flag[local_pps_id];
	if (tmp_pps_slice_segment_header_extension_present_flag == 1) {
		HevcDecoder_Algo_Parser_vld_ue_name(fifo, res, "slice_segment_header_extension_length   ");
		tmp_res = res[0];
		slice_segment_header_extension_length = tmp_res;
		se_idx = 9;
		cnt_i = 0;
	}

	// Update ports indexes

}
static i32 isSchedulable_read_SliceHeader_se_idx_9_loop() {
	i32 result;
	u16 local_se_idx;
	i32 tmp_isFifoFull;
	u32 local_cnt_i;
	u16 local_slice_segment_header_extension_length;

	local_se_idx = se_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	local_cnt_i = cnt_i;
	local_slice_segment_header_extension_length = slice_segment_header_extension_length;
	result = local_se_idx == 9 && tmp_isFifoFull && local_cnt_i < local_slice_segment_header_extension_length;
	return result;
}

static void read_SliceHeader_se_idx_9_loop() {

	u32 res[1];
	u32 local_cnt_i;

	HevcDecoder_Algo_Parser_vld_u_name(8, fifo, res, "slice_segment_header_extension_data_byte");
	local_cnt_i = cnt_i;
	cnt_i = local_cnt_i + 1;

	// Update ports indexes

}
static i32 isSchedulable_read_SliceHeader_se_idx_9_endLoop() {
	i32 result;
	u16 local_se_idx;
	i32 tmp_isFifoFull;
	u32 local_cnt_i;
	u16 local_slice_segment_header_extension_length;

	local_se_idx = se_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	local_cnt_i = cnt_i;
	local_slice_segment_header_extension_length = slice_segment_header_extension_length;
	result = local_se_idx == 9 && tmp_isFifoFull && local_cnt_i == local_slice_segment_header_extension_length;
	return result;
}

static void read_SliceHeader_se_idx_9_endLoop() {


	cnt_i = 0;
	se_idx = 100;

	// Update ports indexes

}
static i32 isSchedulable_read_SliceHeader_done() {
	i32 result;
	u16 local_se_idx;

	local_se_idx = se_idx;
	result = local_se_idx == 100;
	return result;
}

static void read_SliceHeader_done_aligned() {

	i32 local_DEBUG_CABAC;
	i32 local_CHECK_CABAC;
	i32 local_poc;
	u8 local_dependent_slice_segment_flag;
	u16 local_pps_id;
	u8 tmp_pps_cu_qp_delta_enabled_flag;
	i8 local_slice_qp;
	u16 local_num_entry_point_offsets;
	u32 local_TILE_SPLIT_ENABLE;
	u8 tmp_TilesInfo;
	i32 k;
	u8 tmp_TilesInfo0;
	u32 local_totalByPass;
	u32 tmp_entryOffsetsTab;
	u16 local_sps_id;
	i32 tmp_sps_strong_intra_smoothing_enable_flag;
	i32 tmp_pps_constrained_intra_pred_flag;

	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	local_CHECK_CABAC = HevcDecoder_Algo_Parser_CHECK_CABAC;
	if (local_DEBUG_CABAC || local_CHECK_CABAC) {
		local_poc = poc;
		printf("\tPOC: %i\n", local_poc);
	}
	local_dependent_slice_segment_flag = dependent_slice_segment_flag;
	if (local_dependent_slice_segment_flag == 1) {
		first_qp_group = 0;
	} else {
		first_qp_group = 1;
	}
	local_pps_id = pps_id;
	tmp_pps_cu_qp_delta_enabled_flag = pps_cu_qp_delta_enabled_flag[local_pps_id];
	if (tmp_pps_cu_qp_delta_enabled_flag == 0) {
		local_slice_qp = slice_qp;
		qp_y = local_slice_qp;
	}
	sliceData_idx = 1;
	totalByPass = 0;
	local_num_entry_point_offsets = num_entry_point_offsets;
	local_TILE_SPLIT_ENABLE = TILE_SPLIT_ENABLE;
	if (local_num_entry_point_offsets > 0 && local_TILE_SPLIT_ENABLE != 0) {
		tmp_TilesInfo = TilesInfo[1];
		if (tmp_TilesInfo != 0) {
			byPassFlag = 1;
			HevcDecoder_Algo_Parser_byte_align(fifo);
			k = 0;
			tmp_TilesInfo0 = TilesInfo[1];
			while (k <= tmp_TilesInfo0 - 1) {
				local_totalByPass = totalByPass;
				tmp_entryOffsetsTab = entryOffsetsTab[k];
				totalByPass = local_totalByPass + tmp_entryOffsetsTab;
				k = k + 1;
			}
		}
	}
	local_sps_id = sps_id;
	tmp_sps_strong_intra_smoothing_enable_flag = sps_strong_intra_smoothing_enable_flag[local_sps_id];
	tokens_StrongIntraSmoothing[(index_StrongIntraSmoothing % SIZE_StrongIntraSmoothing) + (0)] = tmp_sps_strong_intra_smoothing_enable_flag;
	local_pps_id = pps_id;
	tmp_pps_constrained_intra_pred_flag = pps_constrained_intra_pred_flag[local_pps_id];
	tokens_StrongIntraSmoothing[(index_StrongIntraSmoothing % SIZE_StrongIntraSmoothing) + (1)] = tmp_pps_constrained_intra_pred_flag;

	// Update ports indexes
	index_StrongIntraSmoothing += 2;
	write_end_StrongIntraSmoothing();

}
static i32 isSchedulable_read_SliceData_init() {
	i32 result;
	u8 local_sliceData_idx;
	i32 tmp_isFifoFull;
	u8 local_first_slice_segment_in_pic_flag;
	u8 local_prev_pps_id;
	u16 local_pps_id;

	local_sliceData_idx = sliceData_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	local_first_slice_segment_in_pic_flag = first_slice_segment_in_pic_flag;
	local_prev_pps_id = prev_pps_id;
	local_pps_id = pps_id;
	result = local_sliceData_idx == 1 && tmp_isFifoFull && (local_first_slice_segment_in_pic_flag == 1 || local_prev_pps_id != local_pps_id);
	return result;
}

static void read_SliceData_init() {

	u16 local_pps_id;
	u8 num_tile_columns_minus1;
	u8 num_tile_rows_minus1;
	u16 ColBd[512];
	u16 RowBd[256];
	u16 tileX;
	u16 tileY;
	u16 val;
	u16 tbX;
	u16 tbY;
	u16 tIdx;
	u32 count;
	i32 i;
	i32 local_PICT_WIDTH;
	i32 j;
	i32 i0;
	i32 j0;
	u8 local_INTRA_DC;
	u16 local_sps_id;
	u8 tmp_sps_log2_min_transform_block_size;
	u8 local_Log2MinTrafoSize;
	u8 tmp_sps_log2_diff_max_min_transform_block_size;
	i32 i1;
	i32 j1;
	u16 tmp_rowHeight;
	u16 tmp_colWidth;
	u16 tmp_nbCtbTile;
	u16 tmp_rowHeight0;
	u16 tmp_colWidth0;
	i32 i2;
	u16 tmp_ColBd;
	u16 tmp_colWidth1;
	i32 i3;
	u16 tmp_RowBd;
	u16 tmp_rowHeight1;
	u16 local_PicHeightInCtbsY;
	u16 local_PicWidthInCtbsY;
	u32 local_CTB_ADDR_TS_MAX;
	i32 ctbAddrRS_v;
	u16 local_PicSizeInCtbsY;
	i32 i4;
	u16 tmp_ColBd0;
	i32 j2;
	u16 tmp_RowBd0;
	i32 i5;
	u16 tmp_rowHeight2;
	u16 tmp_colWidth2;
	i32 j3;
	u16 tmp_rowHeight3;
	u16 tmp_RowBd1;
	u16 tmp_colWidth3;
	u16 tmp_ColBd1;
	i32 j4;
	i32 i6;
	i32 y;
	u16 tmp_RowBd2;
	i32 x;
	u16 tmp_ColBd2;
	u16 tmp_ctbAddrRStoTS;
	u32 local_num_entry_offsets;
	u8 tmp_pps_log2_parallel_merge_level;
	u8 local_slice_temporal_mvp_enable_flag;
	u8 local_collocated_from_lX;
	u8 local_collocated_ref_idx;
	u8 tmp_slice_sample_adaptive_offset_flag;
	u8 tmp_slice_sample_adaptive_offset_flag0;
	i32 idx_pictSize;
	u16 local_pictSize;
	u16 tmp_pictSize;
	u16 tmp_pictSize0;
	u8 tmp_pps_loop_filter_across_slice_enabled_flag;
	u8 tmp_pps_loop_filter_across_slice_enabled_flag0;
	u32 local_no_output_of_prior_pics_flag;
	u32 tmp_sps_num_reorder_pics;
	u32 local_pic_output_flag;
	u8 local_video_sequence_id;
	i32 idx_pictSize0;
	u16 local_pictSize0;
	i32 idx_pictOrTileSize;
	u16 local_pictOrTileSize;

	local_pps_id = pps_id;
	num_tile_columns_minus1 = pps_num_tile_columns_minus1[local_pps_id];
	local_pps_id = pps_id;
	num_tile_rows_minus1 = pps_num_tile_rows_minus1[local_pps_id];
	count = 0;
	local_pps_id = pps_id;
	prev_pps_id = local_pps_id;
	i = 0;
	local_PICT_WIDTH = HevcDecoder_Algo_Parser_PICT_WIDTH;
	while (i <= local_PICT_WIDTH - 1) {
		j = 0;
		while (j <= 1) {
			skip_flag_tab[i][j] = 0;
			j = j + 1;
		}
		i = i + 1;
	}
	i0 = 0;
	local_PICT_WIDTH = HevcDecoder_Algo_Parser_PICT_WIDTH;
	while (i0 <= local_PICT_WIDTH - 1) {
		j0 = 0;
		while (j0 <= 1) {
			local_INTRA_DC = HevcDecoder_Algo_Parser_INTRA_DC;
			intraPredMode[i0][j0] = local_INTRA_DC;
			j0 = j0 + 1;
		}
		i0 = i0 + 1;
	}
	local_sps_id = sps_id;
	tmp_sps_log2_min_transform_block_size = sps_log2_min_transform_block_size[local_sps_id];
	Log2MinTrafoSize = tmp_sps_log2_min_transform_block_size;
	local_Log2MinTrafoSize = Log2MinTrafoSize;
	local_sps_id = sps_id;
	tmp_sps_log2_diff_max_min_transform_block_size = sps_log2_diff_max_min_transform_block_size[local_sps_id];
	Log2MaxTrafoSize = local_Log2MinTrafoSize + tmp_sps_log2_diff_max_min_transform_block_size;
	i1 = 0;
	while (i1 <= num_tile_rows_minus1) {
		j1 = 0;
		while (j1 <= num_tile_columns_minus1) {
			if (count == 0) {
				local_pps_id = pps_id;
				tmp_rowHeight = rowHeight[local_pps_id][i1];
				local_pps_id = pps_id;
				tmp_colWidth = colWidth[local_pps_id][j1];
				nbCtbTile[count] = tmp_rowHeight * tmp_colWidth;
			} else {
				tmp_nbCtbTile = nbCtbTile[count - 1];
				local_pps_id = pps_id;
				tmp_rowHeight0 = rowHeight[local_pps_id][i1];
				local_pps_id = pps_id;
				tmp_colWidth0 = colWidth[local_pps_id][j1];
				nbCtbTile[count] = tmp_nbCtbTile + tmp_rowHeight0 * tmp_colWidth0;
			}
			count = count + 1;
			j1 = j1 + 1;
		}
		i1 = i1 + 1;
	}
	ColBd[0] = 0;
	i2 = 0;
	while (i2 <= num_tile_columns_minus1) {
		tmp_ColBd = ColBd[i2];
		local_pps_id = pps_id;
		tmp_colWidth1 = colWidth[local_pps_id][i2];
		ColBd[i2 + 1] = tmp_ColBd + tmp_colWidth1;
		i2 = i2 + 1;
	}
	RowBd[0] = 0;
	i3 = 0;
	while (i3 <= num_tile_rows_minus1) {
		tmp_RowBd = RowBd[i3];
		local_pps_id = pps_id;
		tmp_rowHeight1 = rowHeight[local_pps_id][i3];
		RowBd[i3 + 1] = tmp_RowBd + tmp_rowHeight1;
		i3 = i3 + 1;
	}
	local_PicHeightInCtbsY = PicHeightInCtbsY;
	local_PicWidthInCtbsY = PicWidthInCtbsY;
	local_CTB_ADDR_TS_MAX = HevcDecoder_Algo_Parser_CTB_ADDR_TS_MAX;
	if (local_PicHeightInCtbsY * local_PicWidthInCtbsY >= local_CTB_ADDR_TS_MAX) {
		local_PicHeightInCtbsY = PicHeightInCtbsY;
		local_PicWidthInCtbsY = PicWidthInCtbsY;
		local_CTB_ADDR_TS_MAX = HevcDecoder_Algo_Parser_CTB_ADDR_TS_MAX;
		printf("Error read_SliceData.init : CtbAddrTS : %u >= %u\n", local_PicHeightInCtbsY * local_PicWidthInCtbsY, local_CTB_ADDR_TS_MAX);
	}
	ctbAddrRS_v = 0;
	local_PicSizeInCtbsY = PicSizeInCtbsY;
	while (ctbAddrRS_v <= local_PicSizeInCtbsY - 1) {
		local_PicWidthInCtbsY = PicWidthInCtbsY;
		tbX = ctbAddrRS_v % local_PicWidthInCtbsY;
		local_PicWidthInCtbsY = PicWidthInCtbsY;
		tbY = ctbAddrRS_v / local_PicWidthInCtbsY;
		tileX = 0;
		tileY = 0;
		i4 = 0;
		while (i4 <= num_tile_columns_minus1) {
			tmp_ColBd0 = ColBd[i4 + 1];
			if (tbX < tmp_ColBd0) {
				tileX = i4;
				i4 = num_tile_columns_minus1;
			}
			i4 = i4 + 1;
		}
		j2 = 0;
		while (j2 <= num_tile_rows_minus1) {
			tmp_RowBd0 = RowBd[j2 + 1];
			if (tbY < tmp_RowBd0) {
				tileY = j2;
				j2 = num_tile_rows_minus1;
			}
			j2 = j2 + 1;
		}
		val = 0;
		i5 = 0;
		while (i5 <= tileX - 1) {
			local_pps_id = pps_id;
			tmp_rowHeight2 = rowHeight[local_pps_id][tileY];
			local_pps_id = pps_id;
			tmp_colWidth2 = colWidth[local_pps_id][i5];
			val = val + tmp_rowHeight2 * tmp_colWidth2;
			i5 = i5 + 1;
		}
		j3 = 0;
		while (j3 <= tileY - 1) {
			local_PicWidthInCtbsY = PicWidthInCtbsY;
			local_pps_id = pps_id;
			tmp_rowHeight3 = rowHeight[local_pps_id][j3];
			val = val + local_PicWidthInCtbsY * tmp_rowHeight3;
			j3 = j3 + 1;
		}
		tmp_RowBd1 = RowBd[tileY];
		local_pps_id = pps_id;
		tmp_colWidth3 = colWidth[local_pps_id][tileX];
		tmp_ColBd1 = ColBd[tileX];
		val = val + (tbY - tmp_RowBd1) * tmp_colWidth3 + tbX - tmp_ColBd1;
		ctbAddrRStoTS[ctbAddrRS_v] = val;
		ctbAddrTStoRS[val] = ctbAddrRS_v;
		ctbAddrRS_v = ctbAddrRS_v + 1;
	}
	tIdx = 0;
	j4 = 0;
	while (j4 <= num_tile_rows_minus1) {
		i6 = 0;
		while (i6 <= num_tile_columns_minus1) {
			y = RowBd[j4];
			tmp_RowBd2 = RowBd[j4 + 1];
			while (y <= tmp_RowBd2 - 1) {
				x = ColBd[i6];
				tmp_ColBd2 = ColBd[i6 + 1];
				while (x <= tmp_ColBd2 - 1) {
					local_PicWidthInCtbsY = PicWidthInCtbsY;
					tmp_ctbAddrRStoTS = ctbAddrRStoTS[y * local_PicWidthInCtbsY + x];
					TileId[tmp_ctbAddrRStoTS] = tIdx;
					x = x + 1;
				}
				y = y + 1;
			}
			tIdx = tIdx + 1;
			i6 = i6 + 1;
		}
		j4 = j4 + 1;
	}
	HevcDecoder_Algo_Parser_InitScanningArray(ScanOrder);
	local_num_entry_offsets = num_entry_offsets;
	if (local_num_entry_offsets > 0) {
		sliceData_idx = 20;
	} else {
		sliceData_idx = 21;
	}
	tokens_IsPicSlcLcu[(index_IsPicSlcLcu + (0)) % SIZE_IsPicSlcLcu] = 0;
	tokens_IsPicSlc[(index_IsPicSlc + (0)) % SIZE_IsPicSlc] = 0;
	local_pps_id = pps_id;
	tmp_pps_log2_parallel_merge_level = pps_log2_parallel_merge_level[local_pps_id];
	tokens_MvPredSyntaxElem[(index_MvPredSyntaxElem + (0)) % SIZE_MvPredSyntaxElem] = tmp_pps_log2_parallel_merge_level;
	local_slice_temporal_mvp_enable_flag = slice_temporal_mvp_enable_flag;
	tokens_MvPredSyntaxElem[(index_MvPredSyntaxElem + (1)) % SIZE_MvPredSyntaxElem] = local_slice_temporal_mvp_enable_flag;
	local_collocated_from_lX = collocated_from_lX;
	tokens_MvPredSyntaxElem[(index_MvPredSyntaxElem + (2)) % SIZE_MvPredSyntaxElem] = local_collocated_from_lX;
	local_collocated_ref_idx = collocated_ref_idx;
	tokens_MvPredSyntaxElem[(index_MvPredSyntaxElem + (3)) % SIZE_MvPredSyntaxElem] = local_collocated_ref_idx;
	tmp_slice_sample_adaptive_offset_flag = slice_sample_adaptive_offset_flag[0];
	tmp_slice_sample_adaptive_offset_flag0 = slice_sample_adaptive_offset_flag[1];
	tokens_SaoSe[(index_SaoSe + (0)) % SIZE_SaoSe] = tmp_slice_sample_adaptive_offset_flag + (tmp_slice_sample_adaptive_offset_flag0 << 1);
	local_num_entry_offsets = num_entry_offsets;
	tokens_TilesCoord[(index_TilesCoord + (0)) % SIZE_TilesCoord] = local_num_entry_offsets;
	local_num_entry_offsets = num_entry_offsets;
	idx_pictSize = 0;
	while (idx_pictSize < 2) {
		local_pictSize = pictSize[idx_pictSize];
		tokens_PicSizeInMb[(index_PicSizeInMb % SIZE_PicSizeInMb) + (idx_pictSize)] = local_pictSize;
		idx_pictSize = idx_pictSize + 1;
	}
	tokens_DispCoord[(index_DispCoord % SIZE_DispCoord) + (0)] = 0;
	tmp_pictSize = pictSize[0];
	tokens_DispCoord[(index_DispCoord % SIZE_DispCoord) + (1)] = tmp_pictSize - 1;
	tokens_DispCoord[(index_DispCoord % SIZE_DispCoord) + (2)] = 0;
	tmp_pictSize0 = pictSize[1];
	tokens_DispCoord[(index_DispCoord % SIZE_DispCoord) + (3)] = tmp_pictSize0 - 1;
	local_pps_id = pps_id;
	tmp_pps_loop_filter_across_slice_enabled_flag = pps_loop_filter_across_slice_enabled_flag[local_pps_id];
	local_pps_id = pps_id;
	tmp_pps_loop_filter_across_slice_enabled_flag0 = pps_loop_filter_across_slice_enabled_flag[local_pps_id];
	tokens_LFAcrossSlcTile[(index_LFAcrossSlcTile + (0)) % SIZE_LFAcrossSlcTile] = tmp_pps_loop_filter_across_slice_enabled_flag + (tmp_pps_loop_filter_across_slice_enabled_flag0 << 1);
	local_no_output_of_prior_pics_flag = no_output_of_prior_pics_flag;
	tokens_ReorderPics[(index_ReorderPics % SIZE_ReorderPics) + (0)] = local_no_output_of_prior_pics_flag;
	local_sps_id = sps_id;
	tmp_sps_num_reorder_pics = sps_num_reorder_pics[local_sps_id];
	tokens_ReorderPics[(index_ReorderPics % SIZE_ReorderPics) + (1)] = tmp_sps_num_reorder_pics;
	local_pic_output_flag = pic_output_flag;
	tokens_ReorderPics[(index_ReorderPics % SIZE_ReorderPics) + (2)] = local_pic_output_flag;
	local_video_sequence_id = video_sequence_id;
	tokens_ReorderPics[(index_ReorderPics % SIZE_ReorderPics) + (3)] = local_video_sequence_id;
	idx_pictSize0 = 0;
	while (idx_pictSize0 < 2) {
		local_pictSize0 = pictSize[idx_pictSize0];
		tokens_PictSize[(index_PictSize + (idx_pictSize0)) % SIZE_PictSize] = local_pictSize0;
		idx_pictSize0 = idx_pictSize0 + 1;
	}
	idx_pictOrTileSize = 0;
	while (idx_pictOrTileSize < 2) {
		local_pictOrTileSize = pictOrTileSize[idx_pictOrTileSize];
		idx_pictOrTileSize = idx_pictOrTileSize + 1;
	}

	// Update ports indexes
	index_IsPicSlcLcu += 1;
	index_IsPicSlc += 1;
	index_MvPredSyntaxElem += 4;
	write_end_MvPredSyntaxElem();
	index_SaoSe += 1;
	index_TilesCoord += 1;
	index_PicSizeInMb += 2;
	write_end_PicSizeInMb();
	index_DispCoord += 4;
	write_end_DispCoord();
	index_LFAcrossSlcTile += 1;
	index_ReorderPics += 4;
	write_end_ReorderPics();
	index_PictSize += 2;
	write_end_PictSize();

}
static void read_SliceData_init_aligned() {

	u16 local_pps_id;
	u8 num_tile_columns_minus1;
	u8 num_tile_rows_minus1;
	u16 ColBd[512];
	u16 RowBd[256];
	u16 tileX;
	u16 tileY;
	u16 val;
	u16 tbX;
	u16 tbY;
	u16 tIdx;
	u32 count;
	i32 i;
	i32 local_PICT_WIDTH;
	i32 j;
	i32 i0;
	i32 j0;
	u8 local_INTRA_DC;
	u16 local_sps_id;
	u8 tmp_sps_log2_min_transform_block_size;
	u8 local_Log2MinTrafoSize;
	u8 tmp_sps_log2_diff_max_min_transform_block_size;
	i32 i1;
	i32 j1;
	u16 tmp_rowHeight;
	u16 tmp_colWidth;
	u16 tmp_nbCtbTile;
	u16 tmp_rowHeight0;
	u16 tmp_colWidth0;
	i32 i2;
	u16 tmp_ColBd;
	u16 tmp_colWidth1;
	i32 i3;
	u16 tmp_RowBd;
	u16 tmp_rowHeight1;
	u16 local_PicHeightInCtbsY;
	u16 local_PicWidthInCtbsY;
	u32 local_CTB_ADDR_TS_MAX;
	i32 ctbAddrRS_v;
	u16 local_PicSizeInCtbsY;
	i32 i4;
	u16 tmp_ColBd0;
	i32 j2;
	u16 tmp_RowBd0;
	i32 i5;
	u16 tmp_rowHeight2;
	u16 tmp_colWidth2;
	i32 j3;
	u16 tmp_rowHeight3;
	u16 tmp_RowBd1;
	u16 tmp_colWidth3;
	u16 tmp_ColBd1;
	i32 j4;
	i32 i6;
	i32 y;
	u16 tmp_RowBd2;
	i32 x;
	u16 tmp_ColBd2;
	u16 tmp_ctbAddrRStoTS;
	u32 local_num_entry_offsets;
	u8 tmp_pps_log2_parallel_merge_level;
	u8 local_slice_temporal_mvp_enable_flag;
	u8 local_collocated_from_lX;
	u8 local_collocated_ref_idx;
	u8 tmp_slice_sample_adaptive_offset_flag;
	u8 tmp_slice_sample_adaptive_offset_flag0;
	i32 idx_pictSize;
	u16 local_pictSize;
	u16 tmp_pictSize;
	u16 tmp_pictSize0;
	u8 tmp_pps_loop_filter_across_slice_enabled_flag;
	u8 tmp_pps_loop_filter_across_slice_enabled_flag0;
	u32 local_no_output_of_prior_pics_flag;
	u32 tmp_sps_num_reorder_pics;
	u32 local_pic_output_flag;
	u8 local_video_sequence_id;
	i32 idx_pictSize0;
	u16 local_pictSize0;
	i32 idx_pictOrTileSize;
	u16 local_pictOrTileSize;

	local_pps_id = pps_id;
	num_tile_columns_minus1 = pps_num_tile_columns_minus1[local_pps_id];
	local_pps_id = pps_id;
	num_tile_rows_minus1 = pps_num_tile_rows_minus1[local_pps_id];
	count = 0;
	local_pps_id = pps_id;
	prev_pps_id = local_pps_id;
	i = 0;
	local_PICT_WIDTH = HevcDecoder_Algo_Parser_PICT_WIDTH;
	while (i <= local_PICT_WIDTH - 1) {
		j = 0;
		while (j <= 1) {
			skip_flag_tab[i][j] = 0;
			j = j + 1;
		}
		i = i + 1;
	}
	i0 = 0;
	local_PICT_WIDTH = HevcDecoder_Algo_Parser_PICT_WIDTH;
	while (i0 <= local_PICT_WIDTH - 1) {
		j0 = 0;
		while (j0 <= 1) {
			local_INTRA_DC = HevcDecoder_Algo_Parser_INTRA_DC;
			intraPredMode[i0][j0] = local_INTRA_DC;
			j0 = j0 + 1;
		}
		i0 = i0 + 1;
	}
	local_sps_id = sps_id;
	tmp_sps_log2_min_transform_block_size = sps_log2_min_transform_block_size[local_sps_id];
	Log2MinTrafoSize = tmp_sps_log2_min_transform_block_size;
	local_Log2MinTrafoSize = Log2MinTrafoSize;
	local_sps_id = sps_id;
	tmp_sps_log2_diff_max_min_transform_block_size = sps_log2_diff_max_min_transform_block_size[local_sps_id];
	Log2MaxTrafoSize = local_Log2MinTrafoSize + tmp_sps_log2_diff_max_min_transform_block_size;
	i1 = 0;
	while (i1 <= num_tile_rows_minus1) {
		j1 = 0;
		while (j1 <= num_tile_columns_minus1) {
			if (count == 0) {
				local_pps_id = pps_id;
				tmp_rowHeight = rowHeight[local_pps_id][i1];
				local_pps_id = pps_id;
				tmp_colWidth = colWidth[local_pps_id][j1];
				nbCtbTile[count] = tmp_rowHeight * tmp_colWidth;
			} else {
				tmp_nbCtbTile = nbCtbTile[count - 1];
				local_pps_id = pps_id;
				tmp_rowHeight0 = rowHeight[local_pps_id][i1];
				local_pps_id = pps_id;
				tmp_colWidth0 = colWidth[local_pps_id][j1];
				nbCtbTile[count] = tmp_nbCtbTile + tmp_rowHeight0 * tmp_colWidth0;
			}
			count = count + 1;
			j1 = j1 + 1;
		}
		i1 = i1 + 1;
	}
	ColBd[0] = 0;
	i2 = 0;
	while (i2 <= num_tile_columns_minus1) {
		tmp_ColBd = ColBd[i2];
		local_pps_id = pps_id;
		tmp_colWidth1 = colWidth[local_pps_id][i2];
		ColBd[i2 + 1] = tmp_ColBd + tmp_colWidth1;
		i2 = i2 + 1;
	}
	RowBd[0] = 0;
	i3 = 0;
	while (i3 <= num_tile_rows_minus1) {
		tmp_RowBd = RowBd[i3];
		local_pps_id = pps_id;
		tmp_rowHeight1 = rowHeight[local_pps_id][i3];
		RowBd[i3 + 1] = tmp_RowBd + tmp_rowHeight1;
		i3 = i3 + 1;
	}
	local_PicHeightInCtbsY = PicHeightInCtbsY;
	local_PicWidthInCtbsY = PicWidthInCtbsY;
	local_CTB_ADDR_TS_MAX = HevcDecoder_Algo_Parser_CTB_ADDR_TS_MAX;
	if (local_PicHeightInCtbsY * local_PicWidthInCtbsY >= local_CTB_ADDR_TS_MAX) {
		local_PicHeightInCtbsY = PicHeightInCtbsY;
		local_PicWidthInCtbsY = PicWidthInCtbsY;
		local_CTB_ADDR_TS_MAX = HevcDecoder_Algo_Parser_CTB_ADDR_TS_MAX;
		printf("Error read_SliceData.init : CtbAddrTS : %u >= %u\n", local_PicHeightInCtbsY * local_PicWidthInCtbsY, local_CTB_ADDR_TS_MAX);
	}
	ctbAddrRS_v = 0;
	local_PicSizeInCtbsY = PicSizeInCtbsY;
	while (ctbAddrRS_v <= local_PicSizeInCtbsY - 1) {
		local_PicWidthInCtbsY = PicWidthInCtbsY;
		tbX = ctbAddrRS_v % local_PicWidthInCtbsY;
		local_PicWidthInCtbsY = PicWidthInCtbsY;
		tbY = ctbAddrRS_v / local_PicWidthInCtbsY;
		tileX = 0;
		tileY = 0;
		i4 = 0;
		while (i4 <= num_tile_columns_minus1) {
			tmp_ColBd0 = ColBd[i4 + 1];
			if (tbX < tmp_ColBd0) {
				tileX = i4;
				i4 = num_tile_columns_minus1;
			}
			i4 = i4 + 1;
		}
		j2 = 0;
		while (j2 <= num_tile_rows_minus1) {
			tmp_RowBd0 = RowBd[j2 + 1];
			if (tbY < tmp_RowBd0) {
				tileY = j2;
				j2 = num_tile_rows_minus1;
			}
			j2 = j2 + 1;
		}
		val = 0;
		i5 = 0;
		while (i5 <= tileX - 1) {
			local_pps_id = pps_id;
			tmp_rowHeight2 = rowHeight[local_pps_id][tileY];
			local_pps_id = pps_id;
			tmp_colWidth2 = colWidth[local_pps_id][i5];
			val = val + tmp_rowHeight2 * tmp_colWidth2;
			i5 = i5 + 1;
		}
		j3 = 0;
		while (j3 <= tileY - 1) {
			local_PicWidthInCtbsY = PicWidthInCtbsY;
			local_pps_id = pps_id;
			tmp_rowHeight3 = rowHeight[local_pps_id][j3];
			val = val + local_PicWidthInCtbsY * tmp_rowHeight3;
			j3 = j3 + 1;
		}
		tmp_RowBd1 = RowBd[tileY];
		local_pps_id = pps_id;
		tmp_colWidth3 = colWidth[local_pps_id][tileX];
		tmp_ColBd1 = ColBd[tileX];
		val = val + (tbY - tmp_RowBd1) * tmp_colWidth3 + tbX - tmp_ColBd1;
		ctbAddrRStoTS[ctbAddrRS_v] = val;
		ctbAddrTStoRS[val] = ctbAddrRS_v;
		ctbAddrRS_v = ctbAddrRS_v + 1;
	}
	tIdx = 0;
	j4 = 0;
	while (j4 <= num_tile_rows_minus1) {
		i6 = 0;
		while (i6 <= num_tile_columns_minus1) {
			y = RowBd[j4];
			tmp_RowBd2 = RowBd[j4 + 1];
			while (y <= tmp_RowBd2 - 1) {
				x = ColBd[i6];
				tmp_ColBd2 = ColBd[i6 + 1];
				while (x <= tmp_ColBd2 - 1) {
					local_PicWidthInCtbsY = PicWidthInCtbsY;
					tmp_ctbAddrRStoTS = ctbAddrRStoTS[y * local_PicWidthInCtbsY + x];
					TileId[tmp_ctbAddrRStoTS] = tIdx;
					x = x + 1;
				}
				y = y + 1;
			}
			tIdx = tIdx + 1;
			i6 = i6 + 1;
		}
		j4 = j4 + 1;
	}
	HevcDecoder_Algo_Parser_InitScanningArray(ScanOrder);
	local_num_entry_offsets = num_entry_offsets;
	if (local_num_entry_offsets > 0) {
		sliceData_idx = 20;
	} else {
		sliceData_idx = 21;
	}
	tokens_IsPicSlcLcu[(index_IsPicSlcLcu + (0)) % SIZE_IsPicSlcLcu] = 0;
	tokens_IsPicSlc[(index_IsPicSlc + (0)) % SIZE_IsPicSlc] = 0;
	local_pps_id = pps_id;
	tmp_pps_log2_parallel_merge_level = pps_log2_parallel_merge_level[local_pps_id];
	tokens_MvPredSyntaxElem[(index_MvPredSyntaxElem % SIZE_MvPredSyntaxElem) + (0)] = tmp_pps_log2_parallel_merge_level;
	local_slice_temporal_mvp_enable_flag = slice_temporal_mvp_enable_flag;
	tokens_MvPredSyntaxElem[(index_MvPredSyntaxElem % SIZE_MvPredSyntaxElem) + (1)] = local_slice_temporal_mvp_enable_flag;
	local_collocated_from_lX = collocated_from_lX;
	tokens_MvPredSyntaxElem[(index_MvPredSyntaxElem % SIZE_MvPredSyntaxElem) + (2)] = local_collocated_from_lX;
	local_collocated_ref_idx = collocated_ref_idx;
	tokens_MvPredSyntaxElem[(index_MvPredSyntaxElem % SIZE_MvPredSyntaxElem) + (3)] = local_collocated_ref_idx;
	tmp_slice_sample_adaptive_offset_flag = slice_sample_adaptive_offset_flag[0];
	tmp_slice_sample_adaptive_offset_flag0 = slice_sample_adaptive_offset_flag[1];
	tokens_SaoSe[(index_SaoSe + (0)) % SIZE_SaoSe] = tmp_slice_sample_adaptive_offset_flag + (tmp_slice_sample_adaptive_offset_flag0 << 1);
	local_num_entry_offsets = num_entry_offsets;
	tokens_TilesCoord[(index_TilesCoord + (0)) % SIZE_TilesCoord] = local_num_entry_offsets;
	local_num_entry_offsets = num_entry_offsets;
	idx_pictSize = 0;
	while (idx_pictSize < 2) {
		local_pictSize = pictSize[idx_pictSize];
		tokens_PicSizeInMb[(index_PicSizeInMb % SIZE_PicSizeInMb) + (idx_pictSize)] = local_pictSize;
		idx_pictSize = idx_pictSize + 1;
	}
	tokens_DispCoord[(index_DispCoord % SIZE_DispCoord) + (0)] = 0;
	tmp_pictSize = pictSize[0];
	tokens_DispCoord[(index_DispCoord % SIZE_DispCoord) + (1)] = tmp_pictSize - 1;
	tokens_DispCoord[(index_DispCoord % SIZE_DispCoord) + (2)] = 0;
	tmp_pictSize0 = pictSize[1];
	tokens_DispCoord[(index_DispCoord % SIZE_DispCoord) + (3)] = tmp_pictSize0 - 1;
	local_pps_id = pps_id;
	tmp_pps_loop_filter_across_slice_enabled_flag = pps_loop_filter_across_slice_enabled_flag[local_pps_id];
	local_pps_id = pps_id;
	tmp_pps_loop_filter_across_slice_enabled_flag0 = pps_loop_filter_across_slice_enabled_flag[local_pps_id];
	tokens_LFAcrossSlcTile[(index_LFAcrossSlcTile + (0)) % SIZE_LFAcrossSlcTile] = tmp_pps_loop_filter_across_slice_enabled_flag + (tmp_pps_loop_filter_across_slice_enabled_flag0 << 1);
	local_no_output_of_prior_pics_flag = no_output_of_prior_pics_flag;
	tokens_ReorderPics[(index_ReorderPics % SIZE_ReorderPics) + (0)] = local_no_output_of_prior_pics_flag;
	local_sps_id = sps_id;
	tmp_sps_num_reorder_pics = sps_num_reorder_pics[local_sps_id];
	tokens_ReorderPics[(index_ReorderPics % SIZE_ReorderPics) + (1)] = tmp_sps_num_reorder_pics;
	local_pic_output_flag = pic_output_flag;
	tokens_ReorderPics[(index_ReorderPics % SIZE_ReorderPics) + (2)] = local_pic_output_flag;
	local_video_sequence_id = video_sequence_id;
	tokens_ReorderPics[(index_ReorderPics % SIZE_ReorderPics) + (3)] = local_video_sequence_id;
	idx_pictSize0 = 0;
	while (idx_pictSize0 < 2) {
		local_pictSize0 = pictSize[idx_pictSize0];
		tokens_PictSize[(index_PictSize % SIZE_PictSize) + (idx_pictSize0)] = local_pictSize0;
		idx_pictSize0 = idx_pictSize0 + 1;
	}
	idx_pictOrTileSize = 0;
	while (idx_pictOrTileSize < 2) {
		local_pictOrTileSize = pictOrTileSize[idx_pictOrTileSize];
		idx_pictOrTileSize = idx_pictOrTileSize + 1;
	}

	// Update ports indexes
	index_IsPicSlcLcu += 1;
	index_IsPicSlc += 1;
	index_MvPredSyntaxElem += 4;
	write_end_MvPredSyntaxElem();
	index_SaoSe += 1;
	index_TilesCoord += 1;
	index_PicSizeInMb += 2;
	write_end_PicSizeInMb();
	index_DispCoord += 4;
	write_end_DispCoord();
	index_LFAcrossSlcTile += 1;
	index_ReorderPics += 4;
	write_end_ReorderPics();
	index_PictSize += 2;
	write_end_PictSize();

}
static i32 isSchedulable_read_SliceData_sendInfoSlice() {
	i32 result;
	u8 local_sliceData_idx;

	local_sliceData_idx = sliceData_idx;
	result = local_sliceData_idx == 21;
	return result;
}

static void read_SliceData_sendInfoSlice() {

	u16 tmp_pictSize;
	u16 tmp_pictSize0;

	sliceData_idx = 2;
	tokens_TilesCoord[(index_TilesCoord + (0)) % SIZE_TilesCoord] = 0;
	tokens_TilesCoord[(index_TilesCoord + (1)) % SIZE_TilesCoord] = 0;
	tmp_pictSize = pictSize[0];
	tokens_TilesCoord[(index_TilesCoord + (2)) % SIZE_TilesCoord] = tmp_pictSize;
	tmp_pictSize0 = pictSize[1];
	tokens_TilesCoord[(index_TilesCoord + (3)) % SIZE_TilesCoord] = tmp_pictSize0;

	// Update ports indexes
	index_TilesCoord += 4;
	write_end_TilesCoord();

}
static void read_SliceData_sendInfoSlice_aligned() {

	u16 tmp_pictSize;
	u16 tmp_pictSize0;

	sliceData_idx = 2;
	tokens_TilesCoord[(index_TilesCoord % SIZE_TilesCoord) + (0)] = 0;
	tokens_TilesCoord[(index_TilesCoord % SIZE_TilesCoord) + (1)] = 0;
	tmp_pictSize = pictSize[0];
	tokens_TilesCoord[(index_TilesCoord % SIZE_TilesCoord) + (2)] = tmp_pictSize;
	tmp_pictSize0 = pictSize[1];
	tokens_TilesCoord[(index_TilesCoord % SIZE_TilesCoord) + (3)] = tmp_pictSize0;

	// Update ports indexes
	index_TilesCoord += 4;
	write_end_TilesCoord();

}
static i32 isSchedulable_read_SliceData_sendInfoTilesLoop() {
	i32 result;
	u8 local_sliceData_idx;
	u32 local_cnt_i;
	u32 local_num_entry_offsets;

	local_sliceData_idx = sliceData_idx;
	local_cnt_i = cnt_i;
	local_num_entry_offsets = num_entry_offsets;
	result = local_sliceData_idx == 20 && local_cnt_i < local_num_entry_offsets;
	return result;
}

static void read_SliceData_sendInfoTilesLoop() {

	u32 x0;
	u32 y0;
	u32 x1;
	u32 y1;
	u32 local_countCol;
	u32 local_countRow;
	u16 local_pps_id;
	u8 tmp_pps_num_tile_columns_minus1;
	u32 local_cnt_i;
	u32 local_TILE_SPLIT_ENABLE;

	x0 = 0;
	y0 = 0;
	x1 = pictSize[0];
	y1 = pictSize[1];
	local_countCol = countCol;
	x0 = colTileInPix[local_countCol];
	local_countCol = countCol;
	x1 = colTileInPix[local_countCol + 1];
	local_countRow = countRow;
	y0 = rowTileInPix[local_countRow];
	local_countRow = countRow;
	y1 = rowTileInPix[local_countRow + 1];
	local_countCol = countCol;
	countCol = local_countCol + 1;
	local_countCol = countCol;
	local_pps_id = pps_id;
	tmp_pps_num_tile_columns_minus1 = pps_num_tile_columns_minus1[local_pps_id];
	if (local_countCol == tmp_pps_num_tile_columns_minus1 + 1) {
		countCol = 0;
		local_countRow = countRow;
		countRow = local_countRow + 1;
	}
	local_cnt_i = cnt_i;
	cnt_i = local_cnt_i + 1;
	local_TILE_SPLIT_ENABLE = TILE_SPLIT_ENABLE;
	if (local_TILE_SPLIT_ENABLE == 1) {
		x0 = 0;
		x1 = pictOrTileSize[0];
		y0 = 0;
		y1 = pictOrTileSize[1];
	}
	tokens_TilesCoord[(index_TilesCoord + (0)) % SIZE_TilesCoord] = x0;
	tokens_TilesCoord[(index_TilesCoord + (1)) % SIZE_TilesCoord] = y0;
	tokens_TilesCoord[(index_TilesCoord + (2)) % SIZE_TilesCoord] = x1;
	tokens_TilesCoord[(index_TilesCoord + (3)) % SIZE_TilesCoord] = y1;

	// Update ports indexes
	index_TilesCoord += 4;
	write_end_TilesCoord();

}
static void read_SliceData_sendInfoTilesLoop_aligned() {

	u32 x0;
	u32 y0;
	u32 x1;
	u32 y1;
	u32 local_countCol;
	u32 local_countRow;
	u16 local_pps_id;
	u8 tmp_pps_num_tile_columns_minus1;
	u32 local_cnt_i;
	u32 local_TILE_SPLIT_ENABLE;

	x0 = 0;
	y0 = 0;
	x1 = pictSize[0];
	y1 = pictSize[1];
	local_countCol = countCol;
	x0 = colTileInPix[local_countCol];
	local_countCol = countCol;
	x1 = colTileInPix[local_countCol + 1];
	local_countRow = countRow;
	y0 = rowTileInPix[local_countRow];
	local_countRow = countRow;
	y1 = rowTileInPix[local_countRow + 1];
	local_countCol = countCol;
	countCol = local_countCol + 1;
	local_countCol = countCol;
	local_pps_id = pps_id;
	tmp_pps_num_tile_columns_minus1 = pps_num_tile_columns_minus1[local_pps_id];
	if (local_countCol == tmp_pps_num_tile_columns_minus1 + 1) {
		countCol = 0;
		local_countRow = countRow;
		countRow = local_countRow + 1;
	}
	local_cnt_i = cnt_i;
	cnt_i = local_cnt_i + 1;
	local_TILE_SPLIT_ENABLE = TILE_SPLIT_ENABLE;
	if (local_TILE_SPLIT_ENABLE == 1) {
		x0 = 0;
		x1 = pictOrTileSize[0];
		y0 = 0;
		y1 = pictOrTileSize[1];
	}
	tokens_TilesCoord[(index_TilesCoord % SIZE_TilesCoord) + (0)] = x0;
	tokens_TilesCoord[(index_TilesCoord % SIZE_TilesCoord) + (1)] = y0;
	tokens_TilesCoord[(index_TilesCoord % SIZE_TilesCoord) + (2)] = x1;
	tokens_TilesCoord[(index_TilesCoord % SIZE_TilesCoord) + (3)] = y1;

	// Update ports indexes
	index_TilesCoord += 4;
	write_end_TilesCoord();

}
static i32 isSchedulable_read_SliceData_sendRealInfoTilesLoop() {
	i32 result;
	u8 local_sliceData_idx;
	u32 local_cnt_i;
	u32 local_num_entry_offsets;

	local_sliceData_idx = sliceData_idx;
	local_cnt_i = cnt_i;
	local_num_entry_offsets = num_entry_offsets;
	result = local_sliceData_idx == 22 && local_cnt_i < local_num_entry_offsets;
	return result;
}

static void read_SliceData_sendRealInfoTilesLoop() {

	u32 x0;
	u32 y0;
	u32 x1;
	u32 y1;
	u32 local_countCol;
	u32 local_countRow;
	u16 local_pps_id;
	u8 tmp_pps_num_tile_columns_minus1;
	u32 local_cnt_i;

	x0 = 0;
	y0 = 0;
	x1 = pictSize[0];
	y1 = pictSize[1];
	local_countCol = countCol;
	x0 = colTileInPix[local_countCol];
	local_countCol = countCol;
	x1 = colTileInPix[local_countCol + 1];
	local_countRow = countRow;
	y0 = rowTileInPix[local_countRow];
	local_countRow = countRow;
	y1 = rowTileInPix[local_countRow + 1];
	local_countCol = countCol;
	countCol = local_countCol + 1;
	local_countCol = countCol;
	local_pps_id = pps_id;
	tmp_pps_num_tile_columns_minus1 = pps_num_tile_columns_minus1[local_pps_id];
	if (local_countCol == tmp_pps_num_tile_columns_minus1 + 1) {
		countCol = 0;
		local_countRow = countRow;
		countRow = local_countRow + 1;
	}
	local_cnt_i = cnt_i;
	cnt_i = local_cnt_i + 1;

	// Update ports indexes

}
static i32 isSchedulable_read_SliceData_senInfoTilesEnd() {
	i32 result;
	u8 local_sliceData_idx;
	u32 local_cnt_i;
	u32 local_num_entry_offsets;

	local_sliceData_idx = sliceData_idx;
	local_cnt_i = cnt_i;
	local_num_entry_offsets = num_entry_offsets;
	result = local_sliceData_idx == 20 && local_cnt_i == local_num_entry_offsets;
	return result;
}

static void read_SliceData_senInfoTilesEnd() {


	countCol = 0;
	countRow = 0;
	cnt_i = 0;
	sliceData_idx = 22;

	// Update ports indexes

}
static i32 isSchedulable_read_SliceData_senRealInfoTilesEnd() {
	i32 result;
	u8 local_sliceData_idx;
	u32 local_cnt_i;
	u32 local_num_entry_offsets;

	local_sliceData_idx = sliceData_idx;
	local_cnt_i = cnt_i;
	local_num_entry_offsets = num_entry_offsets;
	result = local_sliceData_idx == 22 && local_cnt_i == local_num_entry_offsets;
	return result;
}

static void read_SliceData_senRealInfoTilesEnd() {


	countCol = 0;
	countRow = 0;
	cnt_i = 0;
	sliceData_idx = 2;

	// Update ports indexes

}
static i32 isSchedulable_read_SliceData_noInit() {
	i32 result;
	u8 local_sliceData_idx;
	u8 local_first_slice_segment_in_pic_flag;
	u8 local_dependent_slice_segment_flag;
	u8 local_prev_pps_id;
	u16 local_pps_id;

	local_sliceData_idx = sliceData_idx;
	local_first_slice_segment_in_pic_flag = first_slice_segment_in_pic_flag;
	local_dependent_slice_segment_flag = dependent_slice_segment_flag;
	local_prev_pps_id = prev_pps_id;
	local_pps_id = pps_id;
	result = local_sliceData_idx == 1 && (local_first_slice_segment_in_pic_flag == 0 && local_dependent_slice_segment_flag == 1 && local_prev_pps_id == local_pps_id);
	return result;
}

static void read_SliceData_noInit() {

	u16 local_pps_id;
	u8 tmp_pps_log2_parallel_merge_level;
	u8 local_slice_temporal_mvp_enable_flag;

	sliceData_idx = 2;
	local_pps_id = pps_id;
	tmp_pps_log2_parallel_merge_level = pps_log2_parallel_merge_level[local_pps_id];
	tokens_MvPredSyntaxElem[(index_MvPredSyntaxElem + (0)) % SIZE_MvPredSyntaxElem] = tmp_pps_log2_parallel_merge_level;
	local_slice_temporal_mvp_enable_flag = slice_temporal_mvp_enable_flag;
	tokens_MvPredSyntaxElem[(index_MvPredSyntaxElem + (1)) % SIZE_MvPredSyntaxElem] = local_slice_temporal_mvp_enable_flag;

	// Update ports indexes
	index_MvPredSyntaxElem += 2;
	write_end_MvPredSyntaxElem();

}
static void read_SliceData_noInit_aligned() {

	u16 local_pps_id;
	u8 tmp_pps_log2_parallel_merge_level;
	u8 local_slice_temporal_mvp_enable_flag;

	sliceData_idx = 2;
	local_pps_id = pps_id;
	tmp_pps_log2_parallel_merge_level = pps_log2_parallel_merge_level[local_pps_id];
	tokens_MvPredSyntaxElem[(index_MvPredSyntaxElem % SIZE_MvPredSyntaxElem) + (0)] = tmp_pps_log2_parallel_merge_level;
	local_slice_temporal_mvp_enable_flag = slice_temporal_mvp_enable_flag;
	tokens_MvPredSyntaxElem[(index_MvPredSyntaxElem % SIZE_MvPredSyntaxElem) + (1)] = local_slice_temporal_mvp_enable_flag;

	// Update ports indexes
	index_MvPredSyntaxElem += 2;
	write_end_MvPredSyntaxElem();

}
static i32 isSchedulable_read_SliceData_noInit_isSlc() {
	i32 result;
	u8 local_sliceData_idx;
	u8 local_first_slice_segment_in_pic_flag;
	u8 local_dependent_slice_segment_flag;
	u8 local_prev_pps_id;
	u16 local_pps_id;

	local_sliceData_idx = sliceData_idx;
	local_first_slice_segment_in_pic_flag = first_slice_segment_in_pic_flag;
	local_dependent_slice_segment_flag = dependent_slice_segment_flag;
	local_prev_pps_id = prev_pps_id;
	local_pps_id = pps_id;
	result = local_sliceData_idx == 1 && (local_first_slice_segment_in_pic_flag == 0 && local_dependent_slice_segment_flag == 0 && local_prev_pps_id == local_pps_id);
	return result;
}

static void read_SliceData_noInit_isSlc() {

	u32 local_num_entry_offsets;
	u16 local_pps_id;
	u8 tmp_pps_log2_parallel_merge_level;
	u8 local_slice_temporal_mvp_enable_flag;
	u8 local_collocated_from_lX;
	u8 local_collocated_ref_idx;
	u8 tmp_pps_loop_filter_across_slice_enabled_flag;
	u8 tmp_pps_loop_filter_across_slice_enabled_flag0;
	i32 idx_pictSize;
	u16 local_pictSize;
	i32 idx_pictOrTileSize;
	u16 local_pictOrTileSize;

	local_num_entry_offsets = num_entry_offsets;
	if (local_num_entry_offsets > 0) {
		sliceData_idx = 20;
	} else {
		sliceData_idx = 21;
	}
	local_pps_id = pps_id;
	tmp_pps_log2_parallel_merge_level = pps_log2_parallel_merge_level[local_pps_id];
	tokens_MvPredSyntaxElem[(index_MvPredSyntaxElem + (0)) % SIZE_MvPredSyntaxElem] = tmp_pps_log2_parallel_merge_level;
	local_slice_temporal_mvp_enable_flag = slice_temporal_mvp_enable_flag;
	tokens_MvPredSyntaxElem[(index_MvPredSyntaxElem + (1)) % SIZE_MvPredSyntaxElem] = local_slice_temporal_mvp_enable_flag;
	local_collocated_from_lX = collocated_from_lX;
	tokens_MvPredSyntaxElem[(index_MvPredSyntaxElem + (2)) % SIZE_MvPredSyntaxElem] = local_collocated_from_lX;
	local_collocated_ref_idx = collocated_ref_idx;
	tokens_MvPredSyntaxElem[(index_MvPredSyntaxElem + (3)) % SIZE_MvPredSyntaxElem] = local_collocated_ref_idx;
	tokens_IsPicSlcLcu[(index_IsPicSlcLcu + (0)) % SIZE_IsPicSlcLcu] = 1;
	local_num_entry_offsets = num_entry_offsets;
	tokens_TilesCoord[(index_TilesCoord + (0)) % SIZE_TilesCoord] = local_num_entry_offsets;
	local_num_entry_offsets = num_entry_offsets;
	local_pps_id = pps_id;
	tmp_pps_loop_filter_across_slice_enabled_flag = pps_loop_filter_across_slice_enabled_flag[local_pps_id];
	local_pps_id = pps_id;
	tmp_pps_loop_filter_across_slice_enabled_flag0 = pps_loop_filter_across_slice_enabled_flag[local_pps_id];
	tokens_LFAcrossSlcTile[(index_LFAcrossSlcTile + (0)) % SIZE_LFAcrossSlcTile] = tmp_pps_loop_filter_across_slice_enabled_flag + (tmp_pps_loop_filter_across_slice_enabled_flag0 << 1);
	idx_pictSize = 0;
	while (idx_pictSize < 2) {
		local_pictSize = pictSize[idx_pictSize];
		tokens_PictSize[(index_PictSize + (idx_pictSize)) % SIZE_PictSize] = local_pictSize;
		idx_pictSize = idx_pictSize + 1;
	}
	idx_pictOrTileSize = 0;
	while (idx_pictOrTileSize < 2) {
		local_pictOrTileSize = pictOrTileSize[idx_pictOrTileSize];
		idx_pictOrTileSize = idx_pictOrTileSize + 1;
	}
	tokens_IsPicSlc[(index_IsPicSlc + (0)) % SIZE_IsPicSlc] = 1;

	// Update ports indexes
	index_MvPredSyntaxElem += 4;
	write_end_MvPredSyntaxElem();
	index_IsPicSlcLcu += 1;
	index_TilesCoord += 1;
	index_LFAcrossSlcTile += 1;
	index_PictSize += 2;
	write_end_PictSize();
	index_IsPicSlc += 1;

}
static void read_SliceData_noInit_isSlc_aligned() {

	u32 local_num_entry_offsets;
	u16 local_pps_id;
	u8 tmp_pps_log2_parallel_merge_level;
	u8 local_slice_temporal_mvp_enable_flag;
	u8 local_collocated_from_lX;
	u8 local_collocated_ref_idx;
	u8 tmp_pps_loop_filter_across_slice_enabled_flag;
	u8 tmp_pps_loop_filter_across_slice_enabled_flag0;
	i32 idx_pictSize;
	u16 local_pictSize;
	i32 idx_pictOrTileSize;
	u16 local_pictOrTileSize;

	local_num_entry_offsets = num_entry_offsets;
	if (local_num_entry_offsets > 0) {
		sliceData_idx = 20;
	} else {
		sliceData_idx = 21;
	}
	local_pps_id = pps_id;
	tmp_pps_log2_parallel_merge_level = pps_log2_parallel_merge_level[local_pps_id];
	tokens_MvPredSyntaxElem[(index_MvPredSyntaxElem % SIZE_MvPredSyntaxElem) + (0)] = tmp_pps_log2_parallel_merge_level;
	local_slice_temporal_mvp_enable_flag = slice_temporal_mvp_enable_flag;
	tokens_MvPredSyntaxElem[(index_MvPredSyntaxElem % SIZE_MvPredSyntaxElem) + (1)] = local_slice_temporal_mvp_enable_flag;
	local_collocated_from_lX = collocated_from_lX;
	tokens_MvPredSyntaxElem[(index_MvPredSyntaxElem % SIZE_MvPredSyntaxElem) + (2)] = local_collocated_from_lX;
	local_collocated_ref_idx = collocated_ref_idx;
	tokens_MvPredSyntaxElem[(index_MvPredSyntaxElem % SIZE_MvPredSyntaxElem) + (3)] = local_collocated_ref_idx;
	tokens_IsPicSlcLcu[(index_IsPicSlcLcu + (0)) % SIZE_IsPicSlcLcu] = 1;
	local_num_entry_offsets = num_entry_offsets;
	tokens_TilesCoord[(index_TilesCoord + (0)) % SIZE_TilesCoord] = local_num_entry_offsets;
	local_num_entry_offsets = num_entry_offsets;
	local_pps_id = pps_id;
	tmp_pps_loop_filter_across_slice_enabled_flag = pps_loop_filter_across_slice_enabled_flag[local_pps_id];
	local_pps_id = pps_id;
	tmp_pps_loop_filter_across_slice_enabled_flag0 = pps_loop_filter_across_slice_enabled_flag[local_pps_id];
	tokens_LFAcrossSlcTile[(index_LFAcrossSlcTile + (0)) % SIZE_LFAcrossSlcTile] = tmp_pps_loop_filter_across_slice_enabled_flag + (tmp_pps_loop_filter_across_slice_enabled_flag0 << 1);
	idx_pictSize = 0;
	while (idx_pictSize < 2) {
		local_pictSize = pictSize[idx_pictSize];
		tokens_PictSize[(index_PictSize % SIZE_PictSize) + (idx_pictSize)] = local_pictSize;
		idx_pictSize = idx_pictSize + 1;
	}
	idx_pictOrTileSize = 0;
	while (idx_pictOrTileSize < 2) {
		local_pictOrTileSize = pictOrTileSize[idx_pictOrTileSize];
		idx_pictOrTileSize = idx_pictOrTileSize + 1;
	}
	tokens_IsPicSlc[(index_IsPicSlc + (0)) % SIZE_IsPicSlc] = 1;

	// Update ports indexes
	index_MvPredSyntaxElem += 4;
	write_end_MvPredSyntaxElem();
	index_IsPicSlcLcu += 1;
	index_TilesCoord += 1;
	index_LFAcrossSlcTile += 1;
	index_PictSize += 2;
	write_end_PictSize();
	index_IsPicSlc += 1;

}
static i32 isSchedulable_read_SliceData_start() {
	i32 result;
	u8 local_sliceData_idx;

	local_sliceData_idx = sliceData_idx;
	result = local_sliceData_idx == 2;
	return result;
}

static void read_SliceData_start_aligned() {

	u8 local_Log2CtbSize;
	u32 CtbSize;
	u32 local_slice_segment_address;
	u32 local_CtbAddrRS;
	u16 tmp_ctbAddrRStoTS;
	u16 local_sps_id;
	u16 tmp_sps_pic_width_in_luma_samples;
	u32 tmp_InverseRasterScan;
	u16 tmp_sps_pic_width_in_luma_samples0;
	u32 tmp_InverseRasterScan0;
	u16 local_xCtb;
	u16 local_yCtb;

	local_Log2CtbSize = Log2CtbSize;
	CtbSize = 1 << local_Log2CtbSize;
	local_slice_segment_address = slice_segment_address;
	CtbAddrRS = local_slice_segment_address;
	local_CtbAddrRS = CtbAddrRS;
	tmp_ctbAddrRStoTS = ctbAddrRStoTS[local_CtbAddrRS];
	CtbAddrTS = tmp_ctbAddrRStoTS;
	local_CtbAddrRS = CtbAddrRS;
	local_sps_id = sps_id;
	tmp_sps_pic_width_in_luma_samples = sps_pic_width_in_luma_samples[local_sps_id];
	tmp_InverseRasterScan = HevcDecoder_Algo_Parser_InverseRasterScan(local_CtbAddrRS, CtbSize, CtbSize, tmp_sps_pic_width_in_luma_samples, 0);
	xCtb = tmp_InverseRasterScan;
	local_CtbAddrRS = CtbAddrRS;
	local_sps_id = sps_id;
	tmp_sps_pic_width_in_luma_samples0 = sps_pic_width_in_luma_samples[local_sps_id];
	tmp_InverseRasterScan0 = HevcDecoder_Algo_Parser_InverseRasterScan(local_CtbAddrRS, CtbSize, CtbSize, tmp_sps_pic_width_in_luma_samples0, 1);
	yCtb = tmp_InverseRasterScan0;
	end_of_slice_flag = 0;
	sliceData_idx = 3;
	local_xCtb = xCtb;
	tokens_SliceAddr[(index_SliceAddr % SIZE_SliceAddr) + (0)] = local_xCtb;
	local_yCtb = yCtb;
	tokens_SliceAddr[(index_SliceAddr % SIZE_SliceAddr) + (1)] = local_yCtb;

	// Update ports indexes
	index_SliceAddr += 2;
	write_end_SliceAddr();

}
static i32 isSchedulable_read_SliceData_gotoCodingTree_start() {
	i32 result;
	u8 local_sliceData_idx;
	i32 local_byPassFlag;

	local_sliceData_idx = sliceData_idx;
	local_byPassFlag = byPassFlag;
	result = local_sliceData_idx == 3 && local_byPassFlag == 0;
	return result;
}

static void read_SliceData_gotoCodingTree_start() {


	sliceData_idx = 4;
	codingTree_idx = 1;

	// Update ports indexes

}
static i32 isSchedulable_read_SliceData_gotoCodingTree_byPass() {
	i32 result;
	u8 local_sliceData_idx;
	i32 local_byPassFlag;

	local_sliceData_idx = sliceData_idx;
	local_byPassFlag = byPassFlag;
	result = local_sliceData_idx == 3 && local_byPassFlag == 1;
	return result;
}

static void read_SliceData_gotoCodingTree_byPass() {


	sliceData_idx = 4;
	codingTree_idx = 0;

	// Update ports indexes

}
static i32 isSchedulable_read_CodingTree_byPassBeforeTileLoop() {
	i32 result;
	u8 local_codingTree_idx;
	i32 tmp_isFifoFull;
	u32 local_cnt_i;
	u32 local_totalByPass;
	u8 tmp_TilesInfo;

	local_codingTree_idx = codingTree_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	local_cnt_i = cnt_i;
	local_totalByPass = totalByPass;
	tmp_TilesInfo = TilesInfo[1];
	result = local_codingTree_idx == 0 && tmp_isFifoFull && local_cnt_i < local_totalByPass + tmp_TilesInfo;
	return result;
}

static void read_CodingTree_byPassBeforeTileLoop() {

	u8 local_localizeAEB;
	i32 local_countAEB;
	u32 local_cnt_i;

	local_localizeAEB = localizeAEB;
	if ((local_localizeAEB & 1) == 0) {
		HevcDecoder_Algo_Parser_flushBits_name(8, fifo, "bypassed");
	} else {
		local_countAEB = countAEB;
		countAEB = local_countAEB + 1;
	}
	local_cnt_i = cnt_i;
	cnt_i = local_cnt_i + 1;

	// Update ports indexes

}
static i32 isSchedulable_read_CodingTree_byPassBeforeTileEnd() {
	i32 result;
	u8 local_codingTree_idx;
	i32 tmp_isFifoFull;
	u32 local_cnt_i;
	u32 local_totalByPass;
	u8 tmp_TilesInfo;

	local_codingTree_idx = codingTree_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	local_cnt_i = cnt_i;
	local_totalByPass = totalByPass;
	tmp_TilesInfo = TilesInfo[1];
	result = local_codingTree_idx == 0 && tmp_isFifoFull && local_cnt_i == local_totalByPass + tmp_TilesInfo;
	return result;
}

static void read_CodingTree_byPassBeforeTileEnd() {

	u8 tmp_TilesInfo;
	u32 local_tile_idx;
	u16 tmp_nbCtbTile;
	u32 local_CtbAddrTS;
	u16 tmp_ctbAddrTStoRS;

	cnt_i = 0;
	byPassFlag = 0;
	codingTree_idx = 1;
	tmp_TilesInfo = TilesInfo[1];
	tile_idx = tmp_TilesInfo;
	local_tile_idx = tile_idx;
	tmp_nbCtbTile = nbCtbTile[local_tile_idx - 1];
	CtbAddrTS = tmp_nbCtbTile;
	local_CtbAddrTS = CtbAddrTS;
	tmp_ctbAddrTStoRS = ctbAddrTStoRS[local_CtbAddrTS];
	CtbAddrRS = tmp_ctbAddrTStoRS;

	// Update ports indexes

}
static i32 isSchedulable_read_SliceData_retCodingTree() {
	i32 result;
	u8 local_sliceData_idx;
	i32 tmp_isFifoFull;

	local_sliceData_idx = sliceData_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	result = local_sliceData_idx == 4 && tmp_isFifoFull;
	return result;
}

static void read_SliceData_retCodingTree() {

	u32 res[1];
	u32 tmp_res;
	u32 local_CtbAddrTS;
	u16 tmp_ctbAddrTStoRS;
	u16 local_pps_id;
	u8 tmp_pps_entropy_coding_sync_enabled_flag;
	u16 local_PicWidthInCtbsY;
	u16 local_sps_id;
	u16 tmp_sps_ctb_width;
	u16 tmp_sps_ctb_width0;
	i32 i;
	u8 local_NB_MAX_SE;
	i32 j;
	u8 local_NB_MAX_NUM_CTX;
	u16 tmp_ctxTable;
	u32 local_end_of_slice_flag;
	u8 tmp_pps_tiles_enabled_flag;
	u16 tmp_TileId;
	u16 tmp_TileId0;
	u32 local_TILE_SPLIT_ENABLE;
	i32 local_counter;

	res[0] = 0;
	HevcDecoder_Algo_Parser_get_END_OF_SLICE_FLAG(codIRange, codIOffset, fifo, res);
	tmp_res = res[0];
	end_of_slice_flag = tmp_res;
	local_CtbAddrTS = CtbAddrTS;
	CtbAddrTS = local_CtbAddrTS + 1;
	local_CtbAddrTS = CtbAddrTS;
	tmp_ctbAddrTStoRS = ctbAddrTStoRS[local_CtbAddrTS];
	CtbAddrRS = tmp_ctbAddrTStoRS;
	local_pps_id = pps_id;
	tmp_pps_entropy_coding_sync_enabled_flag = pps_entropy_coding_sync_enabled_flag[local_pps_id];
	local_CtbAddrTS = CtbAddrTS;
	local_PicWidthInCtbsY = PicWidthInCtbsY;
	local_sps_id = sps_id;
	tmp_sps_ctb_width = sps_ctb_width[local_sps_id];
	local_CtbAddrTS = CtbAddrTS;
	local_sps_id = sps_id;
	tmp_sps_ctb_width0 = sps_ctb_width[local_sps_id];
	if (tmp_pps_entropy_coding_sync_enabled_flag != 0 && (local_CtbAddrTS % local_PicWidthInCtbsY == 2 || tmp_sps_ctb_width == 2 && local_CtbAddrTS % tmp_sps_ctb_width0 == 0)) {
		i = 0;
		local_NB_MAX_SE = HevcDecoder_Algo_Parser_NB_MAX_SE;
		while (i <= local_NB_MAX_SE - 1) {
			j = 0;
			local_NB_MAX_NUM_CTX = HevcDecoder_Algo_Parser_NB_MAX_NUM_CTX;
			while (j <= local_NB_MAX_NUM_CTX - 1) {
				tmp_ctxTable = ctxTable[i][j];
				ctxTableWPP[i][j] = tmp_ctxTable;
				j = j + 1;
			}
			i = i + 1;
		}
	}
	local_end_of_slice_flag = end_of_slice_flag;
	if (local_end_of_slice_flag == 0) {
		sliceData_idx = 3;
		local_pps_id = pps_id;
		tmp_pps_tiles_enabled_flag = pps_tiles_enabled_flag[local_pps_id];
		local_CtbAddrTS = CtbAddrTS;
		tmp_TileId = TileId[local_CtbAddrTS];
		local_CtbAddrTS = CtbAddrTS;
		tmp_TileId0 = TileId[local_CtbAddrTS - 1];
		if (tmp_pps_tiles_enabled_flag != 0 && tmp_TileId != tmp_TileId0) {
			local_TILE_SPLIT_ENABLE = TILE_SPLIT_ENABLE;
			if (local_TILE_SPLIT_ENABLE == 0) {
				sliceData_idx = 3;
			} else {
				sliceData_idx = 5;
			}
		}
	} else {
		local_counter = counter;
		counter = local_counter + 1;
		sliceData_idx = 5;
		CtbAddrTS = 0;
		CtbAddrRS = 0;
		byPassFlag = 0;
	}

	// Update ports indexes

}
static i32 isSchedulable_read_SliceData_end() {
	i32 result;
	u8 local_sliceData_idx;

	local_sliceData_idx = sliceData_idx;
	result = local_sliceData_idx == 5;
	return result;
}

static void read_SliceData_end() {



	// Update ports indexes

}
static i32 isSchedulable_read_CodingTree_start() {
	i32 result;
	u8 local_codingTree_idx;
	i32 tmp_isFifoFull;

	local_codingTree_idx = codingTree_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	result = local_codingTree_idx == 1 && tmp_isFifoFull;
	return result;
}

static void read_CodingTree_start() {

	u32 res[1];
	u8 local_Log2CtbSize;
	u32 CtbSize;
	u32 local_CtbAddrTS;
	u32 CtbAddrRS;
	i32 tile_left_boundary;
	i32 tile_up_boundary;
	u32 indexTS;
	u32 indexRS_0;
	u32 indexRS_1;
	u32 local_slice_addr;
	u16 local_sps_id;
	u16 tmp_sps_ctb_width;
	u16 tmp_sps_ctb_width0;
	u16 tmp_sps_pic_width_in_luma_samples;
	u32 tmp_InverseRasterScan;
	u16 tmp_sps_pic_width_in_luma_samples0;
	u32 tmp_InverseRasterScan0;
	u16 local_pps_id;
	u8 tmp_pps_entropy_coding_sync_enabled_flag;
	u16 local_xCtb;
	u16 local_yCtb;
	u8 tmp_pps_tiles_enabled_flag;
	u16 tmp_TileId;
	u16 tmp_TileId0;
	u8 tmp_pps_tiles_enabled_flag0;
	u16 tmp_TileId1;
	u16 tmp_ctbAddrRStoTS;
	u16 tmp_TileId2;
	u16 tmp_TileId3;
	u16 tmp_ctbAddrRStoTS0;
	u16 tmp_TileId4;
	i32 local_ctb_addr_in_slice;
	u16 tmp_sps_ctb_width1;
	u32 local_slice_segment_address;
	u16 tmp_ctbAddrRStoTS1;
	u8 local_dependent_slice_segment_flag;
	u8 tmp_pps_tiles_enabled_flag1;
	u16 tmp_TileId5;
	u16 tmp_TileId6;
	i8 local_slice_qp;
	u8 local_slice_type;
	u8 local_cabac_init_flag;
	u8 local_first_slice_segment_in_pic_flag;
	u8 tmp_pps_entropy_coding_sync_enabled_flag0;
	u16 local_PicWidthInCtbsY;
	i32 i;
	u8 local_NB_MAX_SE;
	i32 j;
	u8 local_NB_MAX_NUM_CTX;
	u16 tmp_ctxTableWPP;
	u8 tmp_pps_tiles_enabled_flag2;
	u16 tmp_TileId7;
	u16 tmp_TileId8;
	u8 tmp_pps_entropy_coding_sync_enabled_flag1;
	i32 i0;
	i32 j0;
	u16 tmp_ctxTableWPP0;

	local_Log2CtbSize = Log2CtbSize;
	CtbSize = 1 << local_Log2CtbSize;
	local_CtbAddrTS = CtbAddrTS;
	CtbAddrRS = ctbAddrTStoRS[local_CtbAddrTS];
	indexTS = 0;
	indexRS_0 = 0;
	indexRS_1 = 0;
	local_slice_addr = slice_addr;
	ctb_addr_in_slice = CtbAddrRS - local_slice_addr;
	local_CtbAddrTS = CtbAddrTS;
	if (local_CtbAddrTS != 0) {
		local_CtbAddrTS = CtbAddrTS;
		indexTS = local_CtbAddrTS - 1;
	}
	if (CtbAddrRS != 0) {
		indexRS_0 = CtbAddrRS - 1;
	}
	local_sps_id = sps_id;
	tmp_sps_ctb_width = sps_ctb_width[local_sps_id];
	if (CtbAddrRS >= tmp_sps_ctb_width) {
		local_sps_id = sps_id;
		tmp_sps_ctb_width0 = sps_ctb_width[local_sps_id];
		indexRS_1 = CtbAddrRS - tmp_sps_ctb_width0;
	}
	local_sps_id = sps_id;
	tmp_sps_pic_width_in_luma_samples = sps_pic_width_in_luma_samples[local_sps_id];
	tmp_InverseRasterScan = HevcDecoder_Algo_Parser_InverseRasterScan(CtbAddrRS, CtbSize, CtbSize, tmp_sps_pic_width_in_luma_samples, 0);
	xCtb = tmp_InverseRasterScan;
	local_sps_id = sps_id;
	tmp_sps_pic_width_in_luma_samples0 = sps_pic_width_in_luma_samples[local_sps_id];
	tmp_InverseRasterScan0 = HevcDecoder_Algo_Parser_InverseRasterScan(CtbAddrRS, CtbSize, CtbSize, tmp_sps_pic_width_in_luma_samples0, 1);
	yCtb = tmp_InverseRasterScan0;
	local_pps_id = pps_id;
	tmp_pps_entropy_coding_sync_enabled_flag = pps_entropy_coding_sync_enabled_flag[local_pps_id];
	if (tmp_pps_entropy_coding_sync_enabled_flag != 0) {
		local_xCtb = xCtb;
		local_yCtb = yCtb;
		if (local_xCtb == 0 && (local_yCtb & CtbSize - 1) == 0) {
			first_qp_group = 1;
		}
	} else {
		local_pps_id = pps_id;
		tmp_pps_tiles_enabled_flag = pps_tiles_enabled_flag[local_pps_id];
		if (tmp_pps_tiles_enabled_flag != 0) {
			local_CtbAddrTS = CtbAddrTS;
			local_CtbAddrTS = CtbAddrTS;
			tmp_TileId = TileId[local_CtbAddrTS];
			tmp_TileId0 = TileId[indexTS];
			if (local_CtbAddrTS != 0 && tmp_TileId != tmp_TileId0) {
				first_qp_group = 1;
			}
		}
	}
	local_pps_id = pps_id;
	tmp_pps_tiles_enabled_flag0 = pps_tiles_enabled_flag[local_pps_id];
	if (tmp_pps_tiles_enabled_flag0 == 1) {
		local_xCtb = xCtb;
		local_CtbAddrTS = CtbAddrTS;
		tmp_TileId1 = TileId[local_CtbAddrTS];
		tmp_ctbAddrRStoTS = ctbAddrRStoTS[indexRS_0];
		tmp_TileId2 = TileId[tmp_ctbAddrRStoTS];
		if (local_xCtb > 0 && tmp_TileId1 != tmp_TileId2) {
			tile_left_boundary = 1;
		} else {
			tile_left_boundary = 0;
		}
		local_yCtb = yCtb;
		local_CtbAddrTS = CtbAddrTS;
		tmp_TileId3 = TileId[local_CtbAddrTS];
		tmp_ctbAddrRStoTS0 = ctbAddrRStoTS[indexRS_1];
		tmp_TileId4 = TileId[tmp_ctbAddrRStoTS0];
		if (local_yCtb > 0 && tmp_TileId3 != tmp_TileId4) {
			tile_up_boundary = 1;
		} else {
			tile_up_boundary = 0;
		}
	} else {
		tile_left_boundary = 0;
		tile_up_boundary = 0;
	}
	local_xCtb = xCtb;
	local_ctb_addr_in_slice = ctb_addr_in_slice;
	ctb_left_flag = local_xCtb > 0 && local_ctb_addr_in_slice > 0 && tile_left_boundary == 0;
	local_yCtb = yCtb;
	local_ctb_addr_in_slice = ctb_addr_in_slice;
	local_sps_id = sps_id;
	tmp_sps_ctb_width1 = sps_ctb_width[local_sps_id];
	ctb_up_flag = local_yCtb > 0 && local_ctb_addr_in_slice >= tmp_sps_ctb_width1 && tile_up_boundary == 0;
	codingTree_idx = 2;
	local_CtbAddrTS = CtbAddrTS;
	local_slice_segment_address = slice_segment_address;
	tmp_ctbAddrRStoTS1 = ctbAddrRStoTS[local_slice_segment_address];
	if (local_CtbAddrTS == tmp_ctbAddrRStoTS1) {
		HevcDecoder_Algo_Parser_decodeStart(codIRange, codIOffset, fifo);
		local_dependent_slice_segment_flag = dependent_slice_segment_flag;
		local_pps_id = pps_id;
		tmp_pps_tiles_enabled_flag1 = pps_tiles_enabled_flag[local_pps_id];
		local_CtbAddrTS = CtbAddrTS;
		tmp_TileId5 = TileId[local_CtbAddrTS];
		tmp_TileId6 = TileId[indexTS];
		if (local_dependent_slice_segment_flag == 0 || tmp_pps_tiles_enabled_flag1 != 0 && tmp_TileId5 != tmp_TileId6) {
			local_slice_qp = slice_qp;
			local_slice_type = slice_type;
			local_cabac_init_flag = cabac_init_flag;
			HevcDecoder_Algo_Parser_contextInit(local_slice_qp, local_slice_type, ctxTable, local_cabac_init_flag);
		}
		local_first_slice_segment_in_pic_flag = first_slice_segment_in_pic_flag;
		local_pps_id = pps_id;
		tmp_pps_entropy_coding_sync_enabled_flag0 = pps_entropy_coding_sync_enabled_flag[local_pps_id];
		if (local_first_slice_segment_in_pic_flag == 0 && tmp_pps_entropy_coding_sync_enabled_flag0 != 0) {
			local_CtbAddrTS = CtbAddrTS;
			local_PicWidthInCtbsY = PicWidthInCtbsY;
			if (local_CtbAddrTS % local_PicWidthInCtbsY == 0) {
				local_PicWidthInCtbsY = PicWidthInCtbsY;
				if (local_PicWidthInCtbsY == 1) {
					local_slice_qp = slice_qp;
					local_slice_type = slice_type;
					local_cabac_init_flag = cabac_init_flag;
					HevcDecoder_Algo_Parser_contextInit(local_slice_qp, local_slice_type, ctxTable, local_cabac_init_flag);
				} else {
					local_dependent_slice_segment_flag = dependent_slice_segment_flag;
					if (local_dependent_slice_segment_flag != 0) {
						i = 0;
						local_NB_MAX_SE = HevcDecoder_Algo_Parser_NB_MAX_SE;
						while (i <= local_NB_MAX_SE - 1) {
							j = 0;
							local_NB_MAX_NUM_CTX = HevcDecoder_Algo_Parser_NB_MAX_NUM_CTX;
							while (j <= local_NB_MAX_NUM_CTX - 1) {
								tmp_ctxTableWPP = ctxTableWPP[i][j];
								ctxTable[i][j] = tmp_ctxTableWPP;
								j = j + 1;
							}
							i = i + 1;
						}
					}
				}
			}
		}
	} else {
		local_CtbAddrTS = CtbAddrTS;
		local_pps_id = pps_id;
		tmp_pps_tiles_enabled_flag2 = pps_tiles_enabled_flag[local_pps_id];
		local_CtbAddrTS = CtbAddrTS;
		tmp_TileId7 = TileId[local_CtbAddrTS];
		tmp_TileId8 = TileId[indexTS];
		if (local_CtbAddrTS == 0 || tmp_pps_tiles_enabled_flag2 != 0 && tmp_TileId7 != tmp_TileId8) {
			HevcDecoder_Algo_Parser_decodeReInit(codIRange, codIOffset, fifo);
			local_slice_qp = slice_qp;
			local_slice_type = slice_type;
			local_cabac_init_flag = cabac_init_flag;
			HevcDecoder_Algo_Parser_contextInit(local_slice_qp, local_slice_type, ctxTable, local_cabac_init_flag);
		}
		local_pps_id = pps_id;
		tmp_pps_entropy_coding_sync_enabled_flag1 = pps_entropy_coding_sync_enabled_flag[local_pps_id];
		if (tmp_pps_entropy_coding_sync_enabled_flag1 != 0) {
			local_CtbAddrTS = CtbAddrTS;
			local_PicWidthInCtbsY = PicWidthInCtbsY;
			if (local_CtbAddrTS % local_PicWidthInCtbsY == 0) {
				HevcDecoder_Algo_Parser_get_END_OF_SUB_STREAM_ONE_BIT(codIRange, codIOffset, fifo, res);
				HevcDecoder_Algo_Parser_decodeReInit(codIRange, codIOffset, fifo);
				local_PicWidthInCtbsY = PicWidthInCtbsY;
				if (local_PicWidthInCtbsY == 1) {
					local_slice_qp = slice_qp;
					local_slice_type = slice_type;
					local_cabac_init_flag = cabac_init_flag;
					HevcDecoder_Algo_Parser_contextInit(local_slice_qp, local_slice_type, ctxTable, local_cabac_init_flag);
				} else {
					i0 = 0;
					local_NB_MAX_SE = HevcDecoder_Algo_Parser_NB_MAX_SE;
					while (i0 <= local_NB_MAX_SE - 1) {
						j0 = 0;
						local_NB_MAX_NUM_CTX = HevcDecoder_Algo_Parser_NB_MAX_NUM_CTX;
						while (j0 <= local_NB_MAX_NUM_CTX - 1) {
							tmp_ctxTableWPP0 = ctxTableWPP[i0][j0];
							ctxTable[i0][j0] = tmp_ctxTableWPP0;
							j0 = j0 + 1;
						}
						i0 = i0 + 1;
					}
				}
			}
		}
	}

	// Update ports indexes

}
static i32 isSchedulable_read_CodingTree_gotoSaoParam() {
	i32 result;
	u8 local_codingTree_idx;
	u8 tmp_slice_sample_adaptive_offset_flag;
	u8 tmp_slice_sample_adaptive_offset_flag0;

	local_codingTree_idx = codingTree_idx;
	tmp_slice_sample_adaptive_offset_flag = slice_sample_adaptive_offset_flag[0];
	tmp_slice_sample_adaptive_offset_flag0 = slice_sample_adaptive_offset_flag[1];
	result = local_codingTree_idx == 2 && (tmp_slice_sample_adaptive_offset_flag == 1 || tmp_slice_sample_adaptive_offset_flag0 == 1);
	return result;
}

static void read_CodingTree_gotoSaoParam() {

	u16 local_xCtb;
	u8 local_Log2CtbSize;
	u16 local_yCtb;

	codingTree_idx = 3;
	sao_idx = 1;
	local_xCtb = xCtb;
	local_Log2CtbSize = Log2CtbSize;
	sao_rx = local_xCtb >> local_Log2CtbSize;
	local_yCtb = yCtb;
	local_Log2CtbSize = Log2CtbSize;
	sao_ry = local_yCtb >> local_Log2CtbSize;
	sao_cIdx = 0;

	// Update ports indexes

}
static i32 isSchedulable_read_CodingTree_noGotoSaoParam() {
	i32 result;
	u8 local_codingTree_idx;
	u8 tmp_slice_sample_adaptive_offset_flag;
	u8 tmp_slice_sample_adaptive_offset_flag0;

	local_codingTree_idx = codingTree_idx;
	tmp_slice_sample_adaptive_offset_flag = slice_sample_adaptive_offset_flag[0];
	tmp_slice_sample_adaptive_offset_flag0 = slice_sample_adaptive_offset_flag[1];
	result = local_codingTree_idx == 2 && (tmp_slice_sample_adaptive_offset_flag == 0 && tmp_slice_sample_adaptive_offset_flag0 == 0);
	return result;
}

static void read_CodingTree_noGotoSaoParam() {


	codingTree_idx = 3;

	// Update ports indexes

}
static i32 isSchedulable_read_CodingTree_gotoCodingQuadTree() {
	i32 result;
	u8 local_codingTree_idx;

	local_codingTree_idx = codingTree_idx;
	result = local_codingTree_idx == 3;
	return result;
}

static void read_CodingTree_gotoCodingQuadTree() {

	u8 local_CT_idx;
	u16 local_CT_x0;
	u16 local_xCtb;
	u16 local_CT_y0;
	u16 local_yCtb;
	u8 local_CT_log2CbSize;
	u8 local_Log2CtbSize;
	u8 local_CT_ctDepth;
	u8 local_NEW_LCU;

	codingTree_idx = 4;
	ctStack_idx = 0;
	local_CT_idx = HevcDecoder_Algo_Parser_CT_idx;
	ctStack[0][local_CT_idx] = 1;
	local_CT_x0 = HevcDecoder_Algo_Parser_CT_x0;
	local_xCtb = xCtb;
	ctStack[0][local_CT_x0] = local_xCtb;
	local_CT_y0 = HevcDecoder_Algo_Parser_CT_y0;
	local_yCtb = yCtb;
	ctStack[0][local_CT_y0] = local_yCtb;
	local_CT_log2CbSize = HevcDecoder_Algo_Parser_CT_log2CbSize;
	local_Log2CtbSize = Log2CtbSize;
	ctStack[0][local_CT_log2CbSize] = local_Log2CtbSize;
	local_CT_ctDepth = HevcDecoder_Algo_Parser_CT_ctDepth;
	ctStack[0][local_CT_ctDepth] = 0;
	local_NEW_LCU = HevcDecoder_Algo_Parser_NEW_LCU;
	tokens_IsPicSlcLcu[(index_IsPicSlcLcu + (0)) % SIZE_IsPicSlcLcu] = local_NEW_LCU;

	// Update ports indexes
	index_IsPicSlcLcu += 1;

}
static i32 isSchedulable_read_CodingTree_end() {
	i32 result;
	u8 local_codingTree_idx;

	local_codingTree_idx = codingTree_idx;
	result = local_codingTree_idx == 4;
	return result;
}

static void read_CodingTree_end() {



	// Update ports indexes

}
static i32 isSchedulable_read_SaoParam_start() {
	i32 result;
	u8 local_sao_idx;
	i32 tmp_isFifoFull;

	local_sao_idx = sao_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	result = local_sao_idx == 1 && tmp_isFifoFull;
	return result;
}

static void read_SaoParam_start() {

	i32 res[1];
	u8 sao_merge_left_flag;
	u8 sao_merge_up_flag;
	u8 local_SAO_NO_MERGE;
	i16 sao_merge;
	u16 local_sao_rx;
	i32 local_ctb_left_flag;
	u8 local_SAO_MERGE_LEFT;
	u16 local_sao_ry;
	i32 local_ctb_up_flag;
	u8 local_SAO_MERGE_UP;

	sao_merge_left_flag = 0;
	sao_merge_up_flag = 0;
	local_SAO_NO_MERGE = HevcDecoder_Algo_Parser_SAO_NO_MERGE;
	sao_merge = local_SAO_NO_MERGE;
	local_sao_rx = sao_rx;
	if (local_sao_rx > 0) {
		local_ctb_left_flag = ctb_left_flag;
		if (local_ctb_left_flag) {
			HevcDecoder_Algo_Parser_get_SAO_MERGE_FLAG(codIRange, codIOffset, ctxTable, fifo, res);
			sao_merge_left_flag = res[0];
			if (sao_merge_left_flag == 1) {
				local_SAO_MERGE_LEFT = HevcDecoder_Algo_Parser_SAO_MERGE_LEFT;
				sao_merge = local_SAO_MERGE_LEFT;
			}
		}
	}
	local_sao_ry = sao_ry;
	if (local_sao_ry > 0 && sao_merge_left_flag == 0) {
		local_ctb_up_flag = ctb_up_flag;
		if (local_ctb_up_flag) {
			HevcDecoder_Algo_Parser_get_SAO_MERGE_FLAG(codIRange, codIOffset, ctxTable, fifo, res);
			sao_merge_up_flag = res[0];
			if (sao_merge_up_flag == 1) {
				local_SAO_MERGE_UP = HevcDecoder_Algo_Parser_SAO_MERGE_UP;
				sao_merge = local_SAO_MERGE_UP;
			}
		}
	}
	sao_idx = 2;
	if (sao_merge_left_flag == 0 && sao_merge_up_flag == 0) {
		sao_cIdx = 0;
	} else {
		sao_cIdx = 3;
	}
	tokens_SaoSe[(index_SaoSe + (0)) % SIZE_SaoSe] = sao_merge;

	// Update ports indexes
	index_SaoSe += 1;

}
static i32 isSchedulable_read_SaoParam_loop1() {
	i32 result;
	u8 local_sao_idx;
	i32 tmp_isFifoFull;
	u8 local_sao_cIdx;
	u8 tmp_slice_sample_adaptive_offset_flag;

	local_sao_idx = sao_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	local_sao_cIdx = sao_cIdx;
	local_sao_cIdx = sao_cIdx;
	tmp_slice_sample_adaptive_offset_flag = slice_sample_adaptive_offset_flag[local_sao_cIdx];
	result = local_sao_idx == 2 && tmp_isFifoFull && (local_sao_cIdx < 3 && tmp_slice_sample_adaptive_offset_flag == 1);
	return result;
}

static void read_SaoParam_loop1() {

	i32 res[1];
	u8 local_sao_cIdx;
	u8 local_SAO_NOT_APPLIED;
	i32 tmp_res;
	i16 local_sao_typeIdx;

	local_sao_cIdx = sao_cIdx;
	if (local_sao_cIdx != 2) {
		local_SAO_NOT_APPLIED = HevcDecoder_Algo_Parser_SAO_NOT_APPLIED;
		sao_typeIdx = local_SAO_NOT_APPLIED;
		HevcDecoder_Algo_Parser_get_SAO_TYPE_IDX(codIRange, codIOffset, ctxTable, fifo, res);
		tmp_res = res[0];
		sao_typeIdx = tmp_res;
	}
	local_sao_typeIdx = sao_typeIdx;
	local_SAO_NOT_APPLIED = HevcDecoder_Algo_Parser_SAO_NOT_APPLIED;
	if (local_sao_typeIdx != local_SAO_NOT_APPLIED) {
		sao_idx = 3;
	} else {
		local_sao_cIdx = sao_cIdx;
		sao_cIdx = local_sao_cIdx + 1;
	}
	local_sao_typeIdx = sao_typeIdx;
	tokens_SaoSe[(index_SaoSe + (0)) % SIZE_SaoSe] = local_sao_typeIdx;

	// Update ports indexes
	index_SaoSe += 1;

}
static i32 isSchedulable_read_SaoParam_loop2() {
	i32 result;
	u8 local_sao_idx;
	i32 tmp_isFifoFull;

	local_sao_idx = sao_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	result = local_sao_idx == 3 && tmp_isFifoFull;
	return result;
}

static void read_SaoParam_loop2() {

	u8 offsetTh;
	i16 offset[4];
	i32 res[1];
	i32 i;
	i32 tmp_res;
	i16 local_sao_typeIdx;
	u8 local_SAO_BAND;
	i32 i0;
	i16 tmp_offset;
	i32 tmp_res0;
	i16 tmp_offset0;
	i32 tmp_res1;
	i16 tmp_offset1;
	i16 tmp_offset2;
	u8 local_sao_cIdx;
	i32 tmp_res2;
	i16 tmp_offset3;
	i16 tmp_offset4;
	i16 tmp_offset5;
	i16 tmp_offset6;
	i16 local_sao_eo;

	offsetTh = (1 << 3) - 1;
	offset[0] = 0;
	offset[1] = 0;
	offset[2] = 0;
	offset[3] = 0;
	res[0] = 0;
	i = 0;
	while (i <= 3) {
		HevcDecoder_Algo_Parser_get_SAO_OFFSET_ABS(offsetTh, codIRange, codIOffset, fifo, res);
		tmp_res = res[0];
		offset[i] = tmp_res;
		i = i + 1;
	}
	local_sao_typeIdx = sao_typeIdx;
	local_SAO_BAND = HevcDecoder_Algo_Parser_SAO_BAND;
	if (local_sao_typeIdx == local_SAO_BAND) {
		i0 = 0;
		while (i0 <= 3) {
			tmp_offset = offset[i0];
			if (tmp_offset != 0) {
				HevcDecoder_Algo_Parser_get_SAO_OFFSET_SIGN(codIRange, codIOffset, fifo, res);
				tmp_res0 = res[0];
				if (tmp_res0 != 0) {
					tmp_offset0 = offset[i0];
					offset[i0] = -tmp_offset0;
				}
			}
			i0 = i0 + 1;
		}
		HevcDecoder_Algo_Parser_get_SAO_BAND_POSITION(codIRange, codIOffset, fifo, res);
		tmp_res1 = res[0];
		sao_eo = tmp_res1;
	} else {
		tmp_offset1 = offset[2];
		offset[2] = -tmp_offset1;
		tmp_offset2 = offset[3];
		offset[3] = -tmp_offset2;
		local_sao_cIdx = sao_cIdx;
		if (local_sao_cIdx != 2) {
			HevcDecoder_Algo_Parser_get_SAO_EO(codIRange, codIOffset, fifo, res);
			tmp_res2 = res[0];
			sao_eo = tmp_res2;
		}
	}
	local_sao_cIdx = sao_cIdx;
	sao_cIdx = local_sao_cIdx + 1;
	sao_idx = 2;
	tmp_offset3 = offset[0];
	tokens_SaoSe[(index_SaoSe + (0)) % SIZE_SaoSe] = tmp_offset3;
	tmp_offset4 = offset[1];
	tokens_SaoSe[(index_SaoSe + (1)) % SIZE_SaoSe] = tmp_offset4;
	tmp_offset5 = offset[2];
	tokens_SaoSe[(index_SaoSe + (2)) % SIZE_SaoSe] = tmp_offset5;
	tmp_offset6 = offset[3];
	tokens_SaoSe[(index_SaoSe + (3)) % SIZE_SaoSe] = tmp_offset6;
	local_sao_eo = sao_eo;
	tokens_SaoSe[(index_SaoSe + (4)) % SIZE_SaoSe] = local_sao_eo;

	// Update ports indexes
	index_SaoSe += 5;
	write_end_SaoSe();

}
static void read_SaoParam_loop2_aligned() {

	u8 offsetTh;
	i16 offset[4];
	i32 res[1];
	i32 i;
	i32 tmp_res;
	i16 local_sao_typeIdx;
	u8 local_SAO_BAND;
	i32 i0;
	i16 tmp_offset;
	i32 tmp_res0;
	i16 tmp_offset0;
	i32 tmp_res1;
	i16 tmp_offset1;
	i16 tmp_offset2;
	u8 local_sao_cIdx;
	i32 tmp_res2;
	i16 tmp_offset3;
	i16 tmp_offset4;
	i16 tmp_offset5;
	i16 tmp_offset6;
	i16 local_sao_eo;

	offsetTh = (1 << 3) - 1;
	offset[0] = 0;
	offset[1] = 0;
	offset[2] = 0;
	offset[3] = 0;
	res[0] = 0;
	i = 0;
	while (i <= 3) {
		HevcDecoder_Algo_Parser_get_SAO_OFFSET_ABS(offsetTh, codIRange, codIOffset, fifo, res);
		tmp_res = res[0];
		offset[i] = tmp_res;
		i = i + 1;
	}
	local_sao_typeIdx = sao_typeIdx;
	local_SAO_BAND = HevcDecoder_Algo_Parser_SAO_BAND;
	if (local_sao_typeIdx == local_SAO_BAND) {
		i0 = 0;
		while (i0 <= 3) {
			tmp_offset = offset[i0];
			if (tmp_offset != 0) {
				HevcDecoder_Algo_Parser_get_SAO_OFFSET_SIGN(codIRange, codIOffset, fifo, res);
				tmp_res0 = res[0];
				if (tmp_res0 != 0) {
					tmp_offset0 = offset[i0];
					offset[i0] = -tmp_offset0;
				}
			}
			i0 = i0 + 1;
		}
		HevcDecoder_Algo_Parser_get_SAO_BAND_POSITION(codIRange, codIOffset, fifo, res);
		tmp_res1 = res[0];
		sao_eo = tmp_res1;
	} else {
		tmp_offset1 = offset[2];
		offset[2] = -tmp_offset1;
		tmp_offset2 = offset[3];
		offset[3] = -tmp_offset2;
		local_sao_cIdx = sao_cIdx;
		if (local_sao_cIdx != 2) {
			HevcDecoder_Algo_Parser_get_SAO_EO(codIRange, codIOffset, fifo, res);
			tmp_res2 = res[0];
			sao_eo = tmp_res2;
		}
	}
	local_sao_cIdx = sao_cIdx;
	sao_cIdx = local_sao_cIdx + 1;
	sao_idx = 2;
	tmp_offset3 = offset[0];
	tokens_SaoSe[(index_SaoSe % SIZE_SaoSe) + (0)] = tmp_offset3;
	tmp_offset4 = offset[1];
	tokens_SaoSe[(index_SaoSe % SIZE_SaoSe) + (1)] = tmp_offset4;
	tmp_offset5 = offset[2];
	tokens_SaoSe[(index_SaoSe % SIZE_SaoSe) + (2)] = tmp_offset5;
	tmp_offset6 = offset[3];
	tokens_SaoSe[(index_SaoSe % SIZE_SaoSe) + (3)] = tmp_offset6;
	local_sao_eo = sao_eo;
	tokens_SaoSe[(index_SaoSe % SIZE_SaoSe) + (4)] = local_sao_eo;

	// Update ports indexes
	index_SaoSe += 5;
	write_end_SaoSe();

}
static i32 isSchedulable_read_SaoParam_nextLoop() {
	i32 result;
	u8 local_sao_idx;
	u8 local_sao_cIdx;
	u8 tmp_slice_sample_adaptive_offset_flag;

	local_sao_idx = sao_idx;
	local_sao_cIdx = sao_cIdx;
	local_sao_cIdx = sao_cIdx;
	tmp_slice_sample_adaptive_offset_flag = slice_sample_adaptive_offset_flag[local_sao_cIdx];
	result = local_sao_idx == 2 && (local_sao_cIdx < 3 && tmp_slice_sample_adaptive_offset_flag == 0);
	return result;
}

static void read_SaoParam_nextLoop() {

	u8 local_sao_cIdx;

	local_sao_cIdx = sao_cIdx;
	sao_cIdx = local_sao_cIdx + 1;

	// Update ports indexes

}
static i32 isSchedulable_read_SaoParam_endLoop() {
	i32 result;
	u8 local_sao_idx;
	u8 local_sao_cIdx;

	local_sao_idx = sao_idx;
	local_sao_cIdx = sao_cIdx;
	result = local_sao_idx == 2 && local_sao_cIdx == 3;
	return result;
}

static void read_SaoParam_endLoop() {



	// Update ports indexes

}
static i32 isSchedulable_read_CodingQuadTree_start() {
	i32 result;
	u8 local_ctStack_idx;
	u8 local_CT_idx;
	u16 tmp_ctStack;
	i32 tmp_isFifoFull;

	local_ctStack_idx = ctStack_idx;
	local_CT_idx = HevcDecoder_Algo_Parser_CT_idx;
	tmp_ctStack = ctStack[local_ctStack_idx][local_CT_idx];
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	result = tmp_ctStack == 1 && tmp_isFifoFull;
	return result;
}

static void read_CodingQuadTree_start() {

	u32 res[1];
	u8 local_ctStack_idx;
	u16 local_CT_x0;
	u16 ct_x0;
	u16 local_CT_y0;
	u16 ct_y0;
	u8 local_CT_ctDepth;
	u8 ct_ctDepth;
	u8 local_Log2MinCbSize;
	u8 top_ctDepth;
	u8 left_ctDepth;
	u8 split_cu_flag;
	u8 local_Log2CtbSize;
	u16 local_pps_id;
	u16 tmp_pps_diff_cu_qp_delta_depth;
	u8 Log2MinCuQpDeltaSize;
	u16 tbX;
	u16 tbY;
	u16 MinCbAddrZS;
	u16 m;
	u16 x0b;
	u16 y0b;
	u16 local_sps_id;
	u16 tmp_sps_log2_ctb_size;
	u16 tmp_pps_diff_cu_qp_delta_depth0;
	u8 local_CT_log2CbSize;
	u16 tmp_ctStack;
	u16 local_PicWidthInCtbsY;
	u32 local_CtbAddrRS;
	u16 tmp_ctbAddrRStoTS;
	i32 local_DEBUG_CABAC;
	i32 local_DEBUG_TRACE1;
	u8 local_ct_log2CbSize;
	u16 tmp_ctStack0;
	i32 i;
	u32 tmp_if;
	u64 tmp_if0;
	i32 local_ctb_left_flag;
	i32 local_ctb_up_flag;
	u16 tmp_sps_pic_width_in_luma_samples;
	u16 tmp_sps_pic_height_in_luma_samples;
	u8 tmp_pps_cu_qp_delta_enabled_flag;
	u16 local_CT_x1;
	u16 local_CT_y1;
	u8 local_CT_idx;

	local_ctStack_idx = ctStack_idx;
	local_CT_x0 = HevcDecoder_Algo_Parser_CT_x0;
	ct_x0 = ctStack[local_ctStack_idx][local_CT_x0];
	local_ctStack_idx = ctStack_idx;
	local_CT_y0 = HevcDecoder_Algo_Parser_CT_y0;
	ct_y0 = ctStack[local_ctStack_idx][local_CT_y0];
	local_ctStack_idx = ctStack_idx;
	local_CT_ctDepth = HevcDecoder_Algo_Parser_CT_ctDepth;
	ct_ctDepth = ctStack[local_ctStack_idx][local_CT_ctDepth];
	local_Log2MinCbSize = Log2MinCbSize;
	top_ctDepth = cu_top_ctDepth[ct_x0 >> local_Log2MinCbSize];
	local_Log2MinCbSize = Log2MinCbSize;
	left_ctDepth = cu_left_ctDepth[ct_y0 >> local_Log2MinCbSize];
	local_Log2CtbSize = Log2CtbSize;
	local_pps_id = pps_id;
	tmp_pps_diff_cu_qp_delta_depth = pps_diff_cu_qp_delta_depth[local_pps_id];
	Log2MinCuQpDeltaSize = local_Log2CtbSize - tmp_pps_diff_cu_qp_delta_depth;
	local_Log2MinCbSize = Log2MinCbSize;
	local_Log2MinCbSize = Log2MinCbSize;
	local_Log2CtbSize = Log2CtbSize;
	tbX = ((ct_x0 >> local_Log2MinCbSize) << local_Log2MinCbSize) >> local_Log2CtbSize;
	local_Log2MinCbSize = Log2MinCbSize;
	local_Log2MinCbSize = Log2MinCbSize;
	local_Log2CtbSize = Log2CtbSize;
	tbY = ((ct_y0 >> local_Log2MinCbSize) << local_Log2MinCbSize) >> local_Log2CtbSize;
	local_Log2CtbSize = Log2CtbSize;
	x0b = ct_x0 & (1 << local_Log2CtbSize) - 1;
	local_Log2CtbSize = Log2CtbSize;
	y0b = ct_y0 & (1 << local_Log2CtbSize) - 1;
	local_sps_id = sps_id;
	tmp_sps_log2_ctb_size = sps_log2_ctb_size[local_sps_id];
	local_pps_id = pps_id;
	tmp_pps_diff_cu_qp_delta_depth0 = pps_diff_cu_qp_delta_depth[local_pps_id];
	qp_block_mask = (1 << (tmp_sps_log2_ctb_size - tmp_pps_diff_cu_qp_delta_depth0)) - 1;
	local_ctStack_idx = ctStack_idx;
	local_CT_log2CbSize = HevcDecoder_Algo_Parser_CT_log2CbSize;
	tmp_ctStack = ctStack[local_ctStack_idx][local_CT_log2CbSize];
	ct_log2CbSize = tmp_ctStack;
	local_PicWidthInCtbsY = PicWidthInCtbsY;
	CtbAddrRS = local_PicWidthInCtbsY * tbY + tbX;
	local_CtbAddrRS = CtbAddrRS;
	tmp_ctbAddrRStoTS = ctbAddrRStoTS[local_CtbAddrRS];
	local_Log2CtbSize = Log2CtbSize;
	local_Log2MinCbSize = Log2MinCbSize;
	MinCbAddrZS = tmp_ctbAddrRStoTS << ((local_Log2CtbSize - local_Log2MinCbSize) * 2);
	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	local_DEBUG_TRACE1 = HevcDecoder_Algo_Parser_DEBUG_TRACE1;
	if (local_DEBUG_CABAC && local_DEBUG_TRACE1) {
		local_ct_log2CbSize = ct_log2CbSize;
		local_ctStack_idx = ctStack_idx;
		local_CT_ctDepth = HevcDecoder_Algo_Parser_CT_ctDepth;
		tmp_ctStack0 = ctStack[local_ctStack_idx][local_CT_ctDepth];
		printf("read_CodingTree.start (%u, %u, %llu, %u)\n", ct_x0, ct_y0, 1 << local_ct_log2CbSize, tmp_ctStack0);
	} else {
		local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
		if (local_DEBUG_CABAC) {
			printf("read_CodingTree.start\n");
		}
	}
	i = 0;
	local_Log2CtbSize = Log2CtbSize;
	local_Log2MinCbSize = Log2MinCbSize;
	while (i <= local_Log2CtbSize - local_Log2MinCbSize - 1) {
		m = 1 << i;
		local_Log2MinCbSize = Log2MinCbSize;
		if ((m & ct_x0 >> local_Log2MinCbSize) != 0) {
			tmp_if = m * m;
		} else {
			tmp_if = 0;
		}
		local_Log2MinCbSize = Log2MinCbSize;
		if ((m & ct_y0 >> local_Log2MinCbSize) != 0) {
			tmp_if0 = 2 * m * m;
		} else {
			tmp_if0 = 0;
		}
		MinCbAddrZS = MinCbAddrZS + tmp_if + tmp_if0;
		i = i + 1;
	}
	local_ctb_left_flag = ctb_left_flag;
	if (local_ctb_left_flag || x0b > 0) {
		local_Log2MinCbSize = Log2MinCbSize;
		left_ctDepth = cu_left_ctDepth[ct_y0 >> local_Log2MinCbSize];
	}
	local_ctb_up_flag = ctb_up_flag;
	if (local_ctb_up_flag || y0b > 0) {
		local_Log2MinCbSize = Log2MinCbSize;
		top_ctDepth = cu_top_ctDepth[ct_x0 >> local_Log2MinCbSize];
	}
	local_ct_log2CbSize = ct_log2CbSize;
	local_sps_id = sps_id;
	tmp_sps_pic_width_in_luma_samples = sps_pic_width_in_luma_samples[local_sps_id];
	local_ct_log2CbSize = ct_log2CbSize;
	local_sps_id = sps_id;
	tmp_sps_pic_height_in_luma_samples = sps_pic_height_in_luma_samples[local_sps_id];
	local_ct_log2CbSize = ct_log2CbSize;
	local_Log2MinCbSize = Log2MinCbSize;
	if (ct_x0 + (1 << local_ct_log2CbSize) <= tmp_sps_pic_width_in_luma_samples && ct_y0 + (1 << local_ct_log2CbSize) <= tmp_sps_pic_height_in_luma_samples && local_ct_log2CbSize > local_Log2MinCbSize) {
		local_ctb_left_flag = ctb_left_flag;
		local_ctb_up_flag = ctb_up_flag;
		HevcDecoder_Algo_Parser_get_SPLIT_CODING_UNIT_FLAG(codIRange, codIOffset, ctxTable, fifo, res, ct_ctDepth, local_ctb_left_flag || x0b > 0, left_ctDepth, local_ctb_up_flag || y0b > 0, top_ctDepth);
		split_cu_flag = res[0];
	} else {
		local_ct_log2CbSize = ct_log2CbSize;
		local_Log2MinCbSize = Log2MinCbSize;
		if (local_ct_log2CbSize > local_Log2MinCbSize) {
			split_cu_flag = 1;
		} else {
			split_cu_flag = 0;
		}
	}
	local_pps_id = pps_id;
	tmp_pps_cu_qp_delta_enabled_flag = pps_cu_qp_delta_enabled_flag[local_pps_id];
	local_ct_log2CbSize = ct_log2CbSize;
	if (tmp_pps_cu_qp_delta_enabled_flag != 0 && local_ct_log2CbSize >= Log2MinCuQpDeltaSize) {
		IsCuQpDeltaCoded = 0;
		CuQpDelta = 0;
	}
	if (split_cu_flag == 1) {
		local_ctStack_idx = ctStack_idx;
		local_CT_x1 = HevcDecoder_Algo_Parser_CT_x1;
		local_ct_log2CbSize = ct_log2CbSize;
		ctStack[local_ctStack_idx][local_CT_x1] = ct_x0 + ((1 << local_ct_log2CbSize) >> 1);
		local_ctStack_idx = ctStack_idx;
		local_CT_y1 = HevcDecoder_Algo_Parser_CT_y1;
		local_ct_log2CbSize = ct_log2CbSize;
		ctStack[local_ctStack_idx][local_CT_y1] = ct_y0 + ((1 << local_ct_log2CbSize) >> 1);
		local_ctStack_idx = ctStack_idx;
		local_CT_idx = HevcDecoder_Algo_Parser_CT_idx;
		ctStack[local_ctStack_idx][local_CT_idx] = 2;
	} else {
		local_ctStack_idx = ctStack_idx;
		local_CT_idx = HevcDecoder_Algo_Parser_CT_idx;
		ctStack[local_ctStack_idx][local_CT_idx] = 6;
	}

	// Update ports indexes

}
static i32 isSchedulable_read_CodingQuadTree_case1() {
	i32 result;
	u8 local_ctStack_idx;
	u8 local_CT_idx;
	u16 tmp_ctStack;

	local_ctStack_idx = ctStack_idx;
	local_CT_idx = HevcDecoder_Algo_Parser_CT_idx;
	tmp_ctStack = ctStack[local_ctStack_idx][local_CT_idx];
	result = tmp_ctStack == 2;
	return result;
}

static void read_CodingQuadTree_case1() {

	u8 local_ctStack_idx;
	u8 idx;
	u8 local_CT_idx;
	u16 local_CT_x0;
	u16 tmp_ctStack;
	u16 local_CT_y0;
	u16 tmp_ctStack0;
	u8 local_CT_log2CbSize;
	u16 tmp_ctStack1;
	u8 local_CT_ctDepth;
	u16 tmp_ctStack2;

	local_ctStack_idx = ctStack_idx;
	idx = local_ctStack_idx;
	local_ctStack_idx = ctStack_idx;
	local_CT_idx = HevcDecoder_Algo_Parser_CT_idx;
	ctStack[local_ctStack_idx][local_CT_idx] = 3;
	local_ctStack_idx = ctStack_idx;
	ctStack_idx = local_ctStack_idx + 1;
	local_ctStack_idx = ctStack_idx;
	local_CT_idx = HevcDecoder_Algo_Parser_CT_idx;
	ctStack[local_ctStack_idx][local_CT_idx] = 1;
	local_ctStack_idx = ctStack_idx;
	local_CT_x0 = HevcDecoder_Algo_Parser_CT_x0;
	local_CT_x0 = HevcDecoder_Algo_Parser_CT_x0;
	tmp_ctStack = ctStack[idx][local_CT_x0];
	ctStack[local_ctStack_idx][local_CT_x0] = tmp_ctStack;
	local_ctStack_idx = ctStack_idx;
	local_CT_y0 = HevcDecoder_Algo_Parser_CT_y0;
	local_CT_y0 = HevcDecoder_Algo_Parser_CT_y0;
	tmp_ctStack0 = ctStack[idx][local_CT_y0];
	ctStack[local_ctStack_idx][local_CT_y0] = tmp_ctStack0;
	local_ctStack_idx = ctStack_idx;
	local_CT_log2CbSize = HevcDecoder_Algo_Parser_CT_log2CbSize;
	local_CT_log2CbSize = HevcDecoder_Algo_Parser_CT_log2CbSize;
	tmp_ctStack1 = ctStack[idx][local_CT_log2CbSize];
	ctStack[local_ctStack_idx][local_CT_log2CbSize] = tmp_ctStack1 - 1;
	local_ctStack_idx = ctStack_idx;
	local_CT_ctDepth = HevcDecoder_Algo_Parser_CT_ctDepth;
	local_CT_ctDepth = HevcDecoder_Algo_Parser_CT_ctDepth;
	tmp_ctStack2 = ctStack[idx][local_CT_ctDepth];
	ctStack[local_ctStack_idx][local_CT_ctDepth] = tmp_ctStack2 + 1;

	// Update ports indexes

}
static i32 isSchedulable_read_CodingQuadTree_case2() {
	i32 result;
	u8 local_ctStack_idx;
	u8 local_CT_idx;
	u16 tmp_ctStack;
	u16 local_CT_x1;
	u16 tmp_ctStack0;
	u16 local_sps_id;
	u16 tmp_sps_pic_width_in_luma_samples;

	local_ctStack_idx = ctStack_idx;
	local_CT_idx = HevcDecoder_Algo_Parser_CT_idx;
	tmp_ctStack = ctStack[local_ctStack_idx][local_CT_idx];
	local_ctStack_idx = ctStack_idx;
	local_CT_x1 = HevcDecoder_Algo_Parser_CT_x1;
	tmp_ctStack0 = ctStack[local_ctStack_idx][local_CT_x1];
	local_sps_id = sps_id;
	tmp_sps_pic_width_in_luma_samples = sps_pic_width_in_luma_samples[local_sps_id];
	result = tmp_ctStack == 3 && tmp_ctStack0 < tmp_sps_pic_width_in_luma_samples;
	return result;
}

static void read_CodingQuadTree_case2() {

	u8 local_ctStack_idx;
	u8 idx;
	u8 local_CT_idx;
	u16 local_CT_x0;
	u16 local_CT_x1;
	u16 tmp_ctStack;
	u16 local_CT_y0;
	u16 tmp_ctStack0;
	u8 local_CT_log2CbSize;
	u16 tmp_ctStack1;
	u8 local_CT_ctDepth;
	u16 tmp_ctStack2;

	local_ctStack_idx = ctStack_idx;
	idx = local_ctStack_idx;
	local_ctStack_idx = ctStack_idx;
	local_CT_idx = HevcDecoder_Algo_Parser_CT_idx;
	ctStack[local_ctStack_idx][local_CT_idx] = 4;
	local_ctStack_idx = ctStack_idx;
	ctStack_idx = local_ctStack_idx + 1;
	local_ctStack_idx = ctStack_idx;
	local_CT_idx = HevcDecoder_Algo_Parser_CT_idx;
	ctStack[local_ctStack_idx][local_CT_idx] = 1;
	local_ctStack_idx = ctStack_idx;
	local_CT_x0 = HevcDecoder_Algo_Parser_CT_x0;
	local_CT_x1 = HevcDecoder_Algo_Parser_CT_x1;
	tmp_ctStack = ctStack[idx][local_CT_x1];
	ctStack[local_ctStack_idx][local_CT_x0] = tmp_ctStack;
	local_ctStack_idx = ctStack_idx;
	local_CT_y0 = HevcDecoder_Algo_Parser_CT_y0;
	local_CT_y0 = HevcDecoder_Algo_Parser_CT_y0;
	tmp_ctStack0 = ctStack[idx][local_CT_y0];
	ctStack[local_ctStack_idx][local_CT_y0] = tmp_ctStack0;
	local_ctStack_idx = ctStack_idx;
	local_CT_log2CbSize = HevcDecoder_Algo_Parser_CT_log2CbSize;
	local_CT_log2CbSize = HevcDecoder_Algo_Parser_CT_log2CbSize;
	tmp_ctStack1 = ctStack[idx][local_CT_log2CbSize];
	ctStack[local_ctStack_idx][local_CT_log2CbSize] = tmp_ctStack1 - 1;
	local_ctStack_idx = ctStack_idx;
	local_CT_ctDepth = HevcDecoder_Algo_Parser_CT_ctDepth;
	local_CT_ctDepth = HevcDecoder_Algo_Parser_CT_ctDepth;
	tmp_ctStack2 = ctStack[idx][local_CT_ctDepth];
	ctStack[local_ctStack_idx][local_CT_ctDepth] = tmp_ctStack2 + 1;

	// Update ports indexes

}
static i32 isSchedulable_read_CodingQuadTree_noCase2() {
	i32 result;
	u8 local_ctStack_idx;
	u8 local_CT_idx;
	u16 tmp_ctStack;
	u16 local_CT_x1;
	u16 tmp_ctStack0;
	u16 local_sps_id;
	u16 tmp_sps_pic_width_in_luma_samples;

	local_ctStack_idx = ctStack_idx;
	local_CT_idx = HevcDecoder_Algo_Parser_CT_idx;
	tmp_ctStack = ctStack[local_ctStack_idx][local_CT_idx];
	local_ctStack_idx = ctStack_idx;
	local_CT_x1 = HevcDecoder_Algo_Parser_CT_x1;
	tmp_ctStack0 = ctStack[local_ctStack_idx][local_CT_x1];
	local_sps_id = sps_id;
	tmp_sps_pic_width_in_luma_samples = sps_pic_width_in_luma_samples[local_sps_id];
	result = tmp_ctStack == 3 && tmp_ctStack0 >= tmp_sps_pic_width_in_luma_samples;
	return result;
}

static void read_CodingQuadTree_noCase2() {

	u8 local_OTHER;
	u8 local_ctStack_idx;
	u16 local_CT_x1;
	u16 tmp_ctStack;
	u32 local_colIndex;
	u16 tmp_colTileInPix;
	u16 local_CT_y0;
	u16 tmp_ctStack0;
	u32 local_rowIndex;
	u16 tmp_rowTileInPix;
	u8 local_CT_log2CbSize;
	u16 tmp_ctStack1;
	u16 tmp_ctStack2;
	u16 tmp_ctStack3;
	u16 tmp_ctStack4;
	u16 tmp_ctStack5;
	u16 tmp_ctStack6;
	u8 local_CT_idx;
	u8 local_PART_2Nx2N;

	local_OTHER = HevcDecoder_Algo_Parser_OTHER;
	local_ctStack_idx = ctStack_idx;
	local_CT_x1 = HevcDecoder_Algo_Parser_CT_x1;
	tmp_ctStack = ctStack[local_ctStack_idx][local_CT_x1];
	local_colIndex = colIndex;
	tmp_colTileInPix = colTileInPix[local_colIndex];
	local_ctStack_idx = ctStack_idx;
	local_CT_y0 = HevcDecoder_Algo_Parser_CT_y0;
	tmp_ctStack0 = ctStack[local_ctStack_idx][local_CT_y0];
	local_rowIndex = rowIndex;
	tmp_rowTileInPix = rowTileInPix[local_rowIndex];
	local_ctStack_idx = ctStack_idx;
	local_CT_log2CbSize = HevcDecoder_Algo_Parser_CT_log2CbSize;
	tmp_ctStack1 = ctStack[local_ctStack_idx][local_CT_log2CbSize];
	local_ctStack_idx = ctStack_idx;
	local_CT_log2CbSize = HevcDecoder_Algo_Parser_CT_log2CbSize;
	tmp_ctStack2 = ctStack[local_ctStack_idx][local_CT_log2CbSize];
	local_OTHER = HevcDecoder_Algo_Parser_OTHER;
	tokens_CUInfo[(index_CUInfo + (0)) % SIZE_CUInfo] = local_OTHER;
	local_ctStack_idx = ctStack_idx;
	local_CT_x1 = HevcDecoder_Algo_Parser_CT_x1;
	tmp_ctStack3 = ctStack[local_ctStack_idx][local_CT_x1];
	tokens_CUInfo[(index_CUInfo + (1)) % SIZE_CUInfo] = tmp_ctStack3;
	local_ctStack_idx = ctStack_idx;
	local_CT_y0 = HevcDecoder_Algo_Parser_CT_y0;
	tmp_ctStack4 = ctStack[local_ctStack_idx][local_CT_y0];
	tokens_CUInfo[(index_CUInfo + (2)) % SIZE_CUInfo] = tmp_ctStack4;
	local_ctStack_idx = ctStack_idx;
	local_CT_log2CbSize = HevcDecoder_Algo_Parser_CT_log2CbSize;
	tmp_ctStack5 = ctStack[local_ctStack_idx][local_CT_log2CbSize];
	tokens_CUInfo[(index_CUInfo + (3)) % SIZE_CUInfo] = 1 << (tmp_ctStack5 - 1);
	local_ctStack_idx = ctStack_idx;
	local_CT_log2CbSize = HevcDecoder_Algo_Parser_CT_log2CbSize;
	tmp_ctStack6 = ctStack[local_ctStack_idx][local_CT_log2CbSize];
	tokens_CUInfo[(index_CUInfo + (4)) % SIZE_CUInfo] = 1 << (tmp_ctStack6 - 1);
	local_ctStack_idx = ctStack_idx;
	local_CT_idx = HevcDecoder_Algo_Parser_CT_idx;
	ctStack[local_ctStack_idx][local_CT_idx] = 4;
	local_PART_2Nx2N = HevcDecoder_Algo_Parser_PART_2Nx2N;
	tokens_PartMode[(index_PartMode + (0)) % SIZE_PartMode] = local_PART_2Nx2N;

	// Update ports indexes
	index_CUInfo += 5;
	write_end_CUInfo();
	index_PartMode += 1;

}
static void read_CodingQuadTree_noCase2_aligned() {

	u8 local_OTHER;
	u8 local_ctStack_idx;
	u16 local_CT_x1;
	u16 tmp_ctStack;
	u32 local_colIndex;
	u16 tmp_colTileInPix;
	u16 local_CT_y0;
	u16 tmp_ctStack0;
	u32 local_rowIndex;
	u16 tmp_rowTileInPix;
	u8 local_CT_log2CbSize;
	u16 tmp_ctStack1;
	u16 tmp_ctStack2;
	u16 tmp_ctStack3;
	u16 tmp_ctStack4;
	u16 tmp_ctStack5;
	u16 tmp_ctStack6;
	u8 local_CT_idx;
	u8 local_PART_2Nx2N;

	local_OTHER = HevcDecoder_Algo_Parser_OTHER;
	local_ctStack_idx = ctStack_idx;
	local_CT_x1 = HevcDecoder_Algo_Parser_CT_x1;
	tmp_ctStack = ctStack[local_ctStack_idx][local_CT_x1];
	local_colIndex = colIndex;
	tmp_colTileInPix = colTileInPix[local_colIndex];
	local_ctStack_idx = ctStack_idx;
	local_CT_y0 = HevcDecoder_Algo_Parser_CT_y0;
	tmp_ctStack0 = ctStack[local_ctStack_idx][local_CT_y0];
	local_rowIndex = rowIndex;
	tmp_rowTileInPix = rowTileInPix[local_rowIndex];
	local_ctStack_idx = ctStack_idx;
	local_CT_log2CbSize = HevcDecoder_Algo_Parser_CT_log2CbSize;
	tmp_ctStack1 = ctStack[local_ctStack_idx][local_CT_log2CbSize];
	local_ctStack_idx = ctStack_idx;
	local_CT_log2CbSize = HevcDecoder_Algo_Parser_CT_log2CbSize;
	tmp_ctStack2 = ctStack[local_ctStack_idx][local_CT_log2CbSize];
	local_OTHER = HevcDecoder_Algo_Parser_OTHER;
	tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (0)] = local_OTHER;
	local_ctStack_idx = ctStack_idx;
	local_CT_x1 = HevcDecoder_Algo_Parser_CT_x1;
	tmp_ctStack3 = ctStack[local_ctStack_idx][local_CT_x1];
	tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (1)] = tmp_ctStack3;
	local_ctStack_idx = ctStack_idx;
	local_CT_y0 = HevcDecoder_Algo_Parser_CT_y0;
	tmp_ctStack4 = ctStack[local_ctStack_idx][local_CT_y0];
	tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (2)] = tmp_ctStack4;
	local_ctStack_idx = ctStack_idx;
	local_CT_log2CbSize = HevcDecoder_Algo_Parser_CT_log2CbSize;
	tmp_ctStack5 = ctStack[local_ctStack_idx][local_CT_log2CbSize];
	tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (3)] = 1 << (tmp_ctStack5 - 1);
	local_ctStack_idx = ctStack_idx;
	local_CT_log2CbSize = HevcDecoder_Algo_Parser_CT_log2CbSize;
	tmp_ctStack6 = ctStack[local_ctStack_idx][local_CT_log2CbSize];
	tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (4)] = 1 << (tmp_ctStack6 - 1);
	local_ctStack_idx = ctStack_idx;
	local_CT_idx = HevcDecoder_Algo_Parser_CT_idx;
	ctStack[local_ctStack_idx][local_CT_idx] = 4;
	local_PART_2Nx2N = HevcDecoder_Algo_Parser_PART_2Nx2N;
	tokens_PartMode[(index_PartMode + (0)) % SIZE_PartMode] = local_PART_2Nx2N;

	// Update ports indexes
	index_CUInfo += 5;
	write_end_CUInfo();
	index_PartMode += 1;

}
static i32 isSchedulable_read_CodingQuadTree_case3() {
	i32 result;
	u8 local_ctStack_idx;
	u8 local_CT_idx;
	u16 tmp_ctStack;
	u16 local_CT_y1;
	u16 tmp_ctStack0;
	u16 local_sps_id;
	u16 tmp_sps_pic_height_in_luma_samples;

	local_ctStack_idx = ctStack_idx;
	local_CT_idx = HevcDecoder_Algo_Parser_CT_idx;
	tmp_ctStack = ctStack[local_ctStack_idx][local_CT_idx];
	local_ctStack_idx = ctStack_idx;
	local_CT_y1 = HevcDecoder_Algo_Parser_CT_y1;
	tmp_ctStack0 = ctStack[local_ctStack_idx][local_CT_y1];
	local_sps_id = sps_id;
	tmp_sps_pic_height_in_luma_samples = sps_pic_height_in_luma_samples[local_sps_id];
	result = tmp_ctStack == 4 && tmp_ctStack0 < tmp_sps_pic_height_in_luma_samples;
	return result;
}

static void read_CodingQuadTree_case3() {

	u8 local_ctStack_idx;
	u8 idx;
	u8 local_CT_idx;
	u16 local_CT_x0;
	u16 tmp_ctStack;
	u16 local_CT_y0;
	u16 local_CT_y1;
	u16 tmp_ctStack0;
	u8 local_CT_log2CbSize;
	u16 tmp_ctStack1;
	u8 local_CT_ctDepth;
	u16 tmp_ctStack2;

	local_ctStack_idx = ctStack_idx;
	idx = local_ctStack_idx;
	local_ctStack_idx = ctStack_idx;
	local_CT_idx = HevcDecoder_Algo_Parser_CT_idx;
	ctStack[local_ctStack_idx][local_CT_idx] = 5;
	local_ctStack_idx = ctStack_idx;
	ctStack_idx = local_ctStack_idx + 1;
	local_ctStack_idx = ctStack_idx;
	local_CT_idx = HevcDecoder_Algo_Parser_CT_idx;
	ctStack[local_ctStack_idx][local_CT_idx] = 1;
	local_ctStack_idx = ctStack_idx;
	local_CT_x0 = HevcDecoder_Algo_Parser_CT_x0;
	local_CT_x0 = HevcDecoder_Algo_Parser_CT_x0;
	tmp_ctStack = ctStack[idx][local_CT_x0];
	ctStack[local_ctStack_idx][local_CT_x0] = tmp_ctStack;
	local_ctStack_idx = ctStack_idx;
	local_CT_y0 = HevcDecoder_Algo_Parser_CT_y0;
	local_CT_y1 = HevcDecoder_Algo_Parser_CT_y1;
	tmp_ctStack0 = ctStack[idx][local_CT_y1];
	ctStack[local_ctStack_idx][local_CT_y0] = tmp_ctStack0;
	local_ctStack_idx = ctStack_idx;
	local_CT_log2CbSize = HevcDecoder_Algo_Parser_CT_log2CbSize;
	local_CT_log2CbSize = HevcDecoder_Algo_Parser_CT_log2CbSize;
	tmp_ctStack1 = ctStack[idx][local_CT_log2CbSize];
	ctStack[local_ctStack_idx][local_CT_log2CbSize] = tmp_ctStack1 - 1;
	local_ctStack_idx = ctStack_idx;
	local_CT_ctDepth = HevcDecoder_Algo_Parser_CT_ctDepth;
	local_CT_ctDepth = HevcDecoder_Algo_Parser_CT_ctDepth;
	tmp_ctStack2 = ctStack[idx][local_CT_ctDepth];
	ctStack[local_ctStack_idx][local_CT_ctDepth] = tmp_ctStack2 + 1;

	// Update ports indexes

}
static i32 isSchedulable_read_CodingQuadTree_noCase3() {
	i32 result;
	u8 local_ctStack_idx;
	u8 local_CT_idx;
	u16 tmp_ctStack;
	u16 local_CT_y1;
	u16 tmp_ctStack0;
	u16 local_sps_id;
	u16 tmp_sps_pic_height_in_luma_samples;

	local_ctStack_idx = ctStack_idx;
	local_CT_idx = HevcDecoder_Algo_Parser_CT_idx;
	tmp_ctStack = ctStack[local_ctStack_idx][local_CT_idx];
	local_ctStack_idx = ctStack_idx;
	local_CT_y1 = HevcDecoder_Algo_Parser_CT_y1;
	tmp_ctStack0 = ctStack[local_ctStack_idx][local_CT_y1];
	local_sps_id = sps_id;
	tmp_sps_pic_height_in_luma_samples = sps_pic_height_in_luma_samples[local_sps_id];
	result = tmp_ctStack == 4 && tmp_ctStack0 >= tmp_sps_pic_height_in_luma_samples;
	return result;
}

static void read_CodingQuadTree_noCase3() {

	u8 local_OTHER;
	u8 local_ctStack_idx;
	u16 local_CT_x0;
	u16 tmp_ctStack;
	u32 local_colIndex;
	u16 tmp_colTileInPix;
	u16 local_CT_y1;
	u16 tmp_ctStack0;
	u32 local_rowIndex;
	u16 tmp_rowTileInPix;
	u8 local_CT_log2CbSize;
	u16 tmp_ctStack1;
	u16 tmp_ctStack2;
	u16 tmp_ctStack3;
	u16 tmp_ctStack4;
	u16 tmp_ctStack5;
	u16 tmp_ctStack6;
	u8 local_CT_idx;
	u8 local_PART_2Nx2N;

	local_OTHER = HevcDecoder_Algo_Parser_OTHER;
	local_ctStack_idx = ctStack_idx;
	local_CT_x0 = HevcDecoder_Algo_Parser_CT_x0;
	tmp_ctStack = ctStack[local_ctStack_idx][local_CT_x0];
	local_colIndex = colIndex;
	tmp_colTileInPix = colTileInPix[local_colIndex];
	local_ctStack_idx = ctStack_idx;
	local_CT_y1 = HevcDecoder_Algo_Parser_CT_y1;
	tmp_ctStack0 = ctStack[local_ctStack_idx][local_CT_y1];
	local_rowIndex = rowIndex;
	tmp_rowTileInPix = rowTileInPix[local_rowIndex];
	local_ctStack_idx = ctStack_idx;
	local_CT_log2CbSize = HevcDecoder_Algo_Parser_CT_log2CbSize;
	tmp_ctStack1 = ctStack[local_ctStack_idx][local_CT_log2CbSize];
	local_ctStack_idx = ctStack_idx;
	local_CT_log2CbSize = HevcDecoder_Algo_Parser_CT_log2CbSize;
	tmp_ctStack2 = ctStack[local_ctStack_idx][local_CT_log2CbSize];
	local_OTHER = HevcDecoder_Algo_Parser_OTHER;
	tokens_CUInfo[(index_CUInfo + (0)) % SIZE_CUInfo] = local_OTHER;
	local_ctStack_idx = ctStack_idx;
	local_CT_x0 = HevcDecoder_Algo_Parser_CT_x0;
	tmp_ctStack3 = ctStack[local_ctStack_idx][local_CT_x0];
	tokens_CUInfo[(index_CUInfo + (1)) % SIZE_CUInfo] = tmp_ctStack3;
	local_ctStack_idx = ctStack_idx;
	local_CT_y1 = HevcDecoder_Algo_Parser_CT_y1;
	tmp_ctStack4 = ctStack[local_ctStack_idx][local_CT_y1];
	tokens_CUInfo[(index_CUInfo + (2)) % SIZE_CUInfo] = tmp_ctStack4;
	local_ctStack_idx = ctStack_idx;
	local_CT_log2CbSize = HevcDecoder_Algo_Parser_CT_log2CbSize;
	tmp_ctStack5 = ctStack[local_ctStack_idx][local_CT_log2CbSize];
	tokens_CUInfo[(index_CUInfo + (3)) % SIZE_CUInfo] = 1 << (tmp_ctStack5 - 1);
	local_ctStack_idx = ctStack_idx;
	local_CT_log2CbSize = HevcDecoder_Algo_Parser_CT_log2CbSize;
	tmp_ctStack6 = ctStack[local_ctStack_idx][local_CT_log2CbSize];
	tokens_CUInfo[(index_CUInfo + (4)) % SIZE_CUInfo] = 1 << (tmp_ctStack6 - 1);
	local_ctStack_idx = ctStack_idx;
	local_CT_idx = HevcDecoder_Algo_Parser_CT_idx;
	ctStack[local_ctStack_idx][local_CT_idx] = 5;
	local_PART_2Nx2N = HevcDecoder_Algo_Parser_PART_2Nx2N;
	tokens_PartMode[(index_PartMode + (0)) % SIZE_PartMode] = local_PART_2Nx2N;

	// Update ports indexes
	index_CUInfo += 5;
	write_end_CUInfo();
	index_PartMode += 1;

}
static void read_CodingQuadTree_noCase3_aligned() {

	u8 local_OTHER;
	u8 local_ctStack_idx;
	u16 local_CT_x0;
	u16 tmp_ctStack;
	u32 local_colIndex;
	u16 tmp_colTileInPix;
	u16 local_CT_y1;
	u16 tmp_ctStack0;
	u32 local_rowIndex;
	u16 tmp_rowTileInPix;
	u8 local_CT_log2CbSize;
	u16 tmp_ctStack1;
	u16 tmp_ctStack2;
	u16 tmp_ctStack3;
	u16 tmp_ctStack4;
	u16 tmp_ctStack5;
	u16 tmp_ctStack6;
	u8 local_CT_idx;
	u8 local_PART_2Nx2N;

	local_OTHER = HevcDecoder_Algo_Parser_OTHER;
	local_ctStack_idx = ctStack_idx;
	local_CT_x0 = HevcDecoder_Algo_Parser_CT_x0;
	tmp_ctStack = ctStack[local_ctStack_idx][local_CT_x0];
	local_colIndex = colIndex;
	tmp_colTileInPix = colTileInPix[local_colIndex];
	local_ctStack_idx = ctStack_idx;
	local_CT_y1 = HevcDecoder_Algo_Parser_CT_y1;
	tmp_ctStack0 = ctStack[local_ctStack_idx][local_CT_y1];
	local_rowIndex = rowIndex;
	tmp_rowTileInPix = rowTileInPix[local_rowIndex];
	local_ctStack_idx = ctStack_idx;
	local_CT_log2CbSize = HevcDecoder_Algo_Parser_CT_log2CbSize;
	tmp_ctStack1 = ctStack[local_ctStack_idx][local_CT_log2CbSize];
	local_ctStack_idx = ctStack_idx;
	local_CT_log2CbSize = HevcDecoder_Algo_Parser_CT_log2CbSize;
	tmp_ctStack2 = ctStack[local_ctStack_idx][local_CT_log2CbSize];
	local_OTHER = HevcDecoder_Algo_Parser_OTHER;
	tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (0)] = local_OTHER;
	local_ctStack_idx = ctStack_idx;
	local_CT_x0 = HevcDecoder_Algo_Parser_CT_x0;
	tmp_ctStack3 = ctStack[local_ctStack_idx][local_CT_x0];
	tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (1)] = tmp_ctStack3;
	local_ctStack_idx = ctStack_idx;
	local_CT_y1 = HevcDecoder_Algo_Parser_CT_y1;
	tmp_ctStack4 = ctStack[local_ctStack_idx][local_CT_y1];
	tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (2)] = tmp_ctStack4;
	local_ctStack_idx = ctStack_idx;
	local_CT_log2CbSize = HevcDecoder_Algo_Parser_CT_log2CbSize;
	tmp_ctStack5 = ctStack[local_ctStack_idx][local_CT_log2CbSize];
	tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (3)] = 1 << (tmp_ctStack5 - 1);
	local_ctStack_idx = ctStack_idx;
	local_CT_log2CbSize = HevcDecoder_Algo_Parser_CT_log2CbSize;
	tmp_ctStack6 = ctStack[local_ctStack_idx][local_CT_log2CbSize];
	tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (4)] = 1 << (tmp_ctStack6 - 1);
	local_ctStack_idx = ctStack_idx;
	local_CT_idx = HevcDecoder_Algo_Parser_CT_idx;
	ctStack[local_ctStack_idx][local_CT_idx] = 5;
	local_PART_2Nx2N = HevcDecoder_Algo_Parser_PART_2Nx2N;
	tokens_PartMode[(index_PartMode + (0)) % SIZE_PartMode] = local_PART_2Nx2N;

	// Update ports indexes
	index_CUInfo += 5;
	write_end_CUInfo();
	index_PartMode += 1;

}
static i32 isSchedulable_read_CodingQuadTree_case4() {
	i32 result;
	u8 local_ctStack_idx;
	u8 local_CT_idx;
	u16 tmp_ctStack;
	u16 local_CT_x1;
	u16 tmp_ctStack0;
	u16 local_sps_id;
	u16 tmp_sps_pic_width_in_luma_samples;
	u16 local_CT_y1;
	u16 tmp_ctStack1;
	u16 tmp_sps_pic_height_in_luma_samples;

	local_ctStack_idx = ctStack_idx;
	local_CT_idx = HevcDecoder_Algo_Parser_CT_idx;
	tmp_ctStack = ctStack[local_ctStack_idx][local_CT_idx];
	local_ctStack_idx = ctStack_idx;
	local_CT_x1 = HevcDecoder_Algo_Parser_CT_x1;
	tmp_ctStack0 = ctStack[local_ctStack_idx][local_CT_x1];
	local_sps_id = sps_id;
	tmp_sps_pic_width_in_luma_samples = sps_pic_width_in_luma_samples[local_sps_id];
	local_ctStack_idx = ctStack_idx;
	local_CT_y1 = HevcDecoder_Algo_Parser_CT_y1;
	tmp_ctStack1 = ctStack[local_ctStack_idx][local_CT_y1];
	local_sps_id = sps_id;
	tmp_sps_pic_height_in_luma_samples = sps_pic_height_in_luma_samples[local_sps_id];
	result = tmp_ctStack == 5 && tmp_ctStack0 < tmp_sps_pic_width_in_luma_samples && tmp_ctStack1 < tmp_sps_pic_height_in_luma_samples;
	return result;
}

static void read_CodingQuadTree_case4() {

	u8 local_ctStack_idx;
	u8 idx;
	u8 local_CT_idx;
	u16 local_CT_x0;
	u16 local_CT_x1;
	u16 tmp_ctStack;
	u16 local_CT_y0;
	u16 local_CT_y1;
	u16 tmp_ctStack0;
	u8 local_CT_log2CbSize;
	u16 tmp_ctStack1;
	u8 local_CT_ctDepth;
	u16 tmp_ctStack2;

	local_ctStack_idx = ctStack_idx;
	idx = local_ctStack_idx;
	local_ctStack_idx = ctStack_idx;
	local_CT_idx = HevcDecoder_Algo_Parser_CT_idx;
	ctStack[local_ctStack_idx][local_CT_idx] = 7;
	local_ctStack_idx = ctStack_idx;
	ctStack_idx = local_ctStack_idx + 1;
	local_ctStack_idx = ctStack_idx;
	local_CT_idx = HevcDecoder_Algo_Parser_CT_idx;
	ctStack[local_ctStack_idx][local_CT_idx] = 1;
	local_ctStack_idx = ctStack_idx;
	local_CT_x0 = HevcDecoder_Algo_Parser_CT_x0;
	local_CT_x1 = HevcDecoder_Algo_Parser_CT_x1;
	tmp_ctStack = ctStack[idx][local_CT_x1];
	ctStack[local_ctStack_idx][local_CT_x0] = tmp_ctStack;
	local_ctStack_idx = ctStack_idx;
	local_CT_y0 = HevcDecoder_Algo_Parser_CT_y0;
	local_CT_y1 = HevcDecoder_Algo_Parser_CT_y1;
	tmp_ctStack0 = ctStack[idx][local_CT_y1];
	ctStack[local_ctStack_idx][local_CT_y0] = tmp_ctStack0;
	local_ctStack_idx = ctStack_idx;
	local_CT_log2CbSize = HevcDecoder_Algo_Parser_CT_log2CbSize;
	local_CT_log2CbSize = HevcDecoder_Algo_Parser_CT_log2CbSize;
	tmp_ctStack1 = ctStack[idx][local_CT_log2CbSize];
	ctStack[local_ctStack_idx][local_CT_log2CbSize] = tmp_ctStack1 - 1;
	local_ctStack_idx = ctStack_idx;
	local_CT_ctDepth = HevcDecoder_Algo_Parser_CT_ctDepth;
	local_CT_ctDepth = HevcDecoder_Algo_Parser_CT_ctDepth;
	tmp_ctStack2 = ctStack[idx][local_CT_ctDepth];
	ctStack[local_ctStack_idx][local_CT_ctDepth] = tmp_ctStack2 + 1;

	// Update ports indexes

}
static i32 isSchedulable_read_CodingQuadTree_noCase4() {
	i32 result;
	u8 local_ctStack_idx;
	u8 local_CT_idx;
	u16 tmp_ctStack;
	u16 local_CT_x1;
	u16 tmp_ctStack0;
	u16 local_sps_id;
	u16 tmp_sps_pic_width_in_luma_samples;
	u16 local_CT_y1;
	u16 tmp_ctStack1;
	u16 tmp_sps_pic_height_in_luma_samples;

	local_ctStack_idx = ctStack_idx;
	local_CT_idx = HevcDecoder_Algo_Parser_CT_idx;
	tmp_ctStack = ctStack[local_ctStack_idx][local_CT_idx];
	local_ctStack_idx = ctStack_idx;
	local_CT_x1 = HevcDecoder_Algo_Parser_CT_x1;
	tmp_ctStack0 = ctStack[local_ctStack_idx][local_CT_x1];
	local_sps_id = sps_id;
	tmp_sps_pic_width_in_luma_samples = sps_pic_width_in_luma_samples[local_sps_id];
	local_ctStack_idx = ctStack_idx;
	local_CT_y1 = HevcDecoder_Algo_Parser_CT_y1;
	tmp_ctStack1 = ctStack[local_ctStack_idx][local_CT_y1];
	local_sps_id = sps_id;
	tmp_sps_pic_height_in_luma_samples = sps_pic_height_in_luma_samples[local_sps_id];
	result = tmp_ctStack == 5 && (tmp_ctStack0 >= tmp_sps_pic_width_in_luma_samples || tmp_ctStack1 >= tmp_sps_pic_height_in_luma_samples);
	return result;
}

static void read_CodingQuadTree_noCase4() {

	u8 local_OTHER;
	u8 local_ctStack_idx;
	u16 local_CT_x1;
	u16 tmp_ctStack;
	u32 local_colIndex;
	u16 tmp_colTileInPix;
	u16 local_CT_y1;
	u16 tmp_ctStack0;
	u32 local_rowIndex;
	u16 tmp_rowTileInPix;
	u8 local_CT_log2CbSize;
	u16 tmp_ctStack1;
	u16 tmp_ctStack2;
	u16 tmp_ctStack3;
	u16 tmp_ctStack4;
	u16 tmp_ctStack5;
	u16 tmp_ctStack6;
	u8 local_CT_idx;
	u8 local_PART_2Nx2N;

	local_OTHER = HevcDecoder_Algo_Parser_OTHER;
	local_ctStack_idx = ctStack_idx;
	local_CT_x1 = HevcDecoder_Algo_Parser_CT_x1;
	tmp_ctStack = ctStack[local_ctStack_idx][local_CT_x1];
	local_colIndex = colIndex;
	tmp_colTileInPix = colTileInPix[local_colIndex];
	local_ctStack_idx = ctStack_idx;
	local_CT_y1 = HevcDecoder_Algo_Parser_CT_y1;
	tmp_ctStack0 = ctStack[local_ctStack_idx][local_CT_y1];
	local_rowIndex = rowIndex;
	tmp_rowTileInPix = rowTileInPix[local_rowIndex];
	local_ctStack_idx = ctStack_idx;
	local_CT_log2CbSize = HevcDecoder_Algo_Parser_CT_log2CbSize;
	tmp_ctStack1 = ctStack[local_ctStack_idx][local_CT_log2CbSize];
	local_ctStack_idx = ctStack_idx;
	local_CT_log2CbSize = HevcDecoder_Algo_Parser_CT_log2CbSize;
	tmp_ctStack2 = ctStack[local_ctStack_idx][local_CT_log2CbSize];
	local_OTHER = HevcDecoder_Algo_Parser_OTHER;
	tokens_CUInfo[(index_CUInfo + (0)) % SIZE_CUInfo] = local_OTHER;
	local_ctStack_idx = ctStack_idx;
	local_CT_x1 = HevcDecoder_Algo_Parser_CT_x1;
	tmp_ctStack3 = ctStack[local_ctStack_idx][local_CT_x1];
	tokens_CUInfo[(index_CUInfo + (1)) % SIZE_CUInfo] = tmp_ctStack3;
	local_ctStack_idx = ctStack_idx;
	local_CT_y1 = HevcDecoder_Algo_Parser_CT_y1;
	tmp_ctStack4 = ctStack[local_ctStack_idx][local_CT_y1];
	tokens_CUInfo[(index_CUInfo + (2)) % SIZE_CUInfo] = tmp_ctStack4;
	local_ctStack_idx = ctStack_idx;
	local_CT_log2CbSize = HevcDecoder_Algo_Parser_CT_log2CbSize;
	tmp_ctStack5 = ctStack[local_ctStack_idx][local_CT_log2CbSize];
	tokens_CUInfo[(index_CUInfo + (3)) % SIZE_CUInfo] = 1 << (tmp_ctStack5 - 1);
	local_ctStack_idx = ctStack_idx;
	local_CT_log2CbSize = HevcDecoder_Algo_Parser_CT_log2CbSize;
	tmp_ctStack6 = ctStack[local_ctStack_idx][local_CT_log2CbSize];
	tokens_CUInfo[(index_CUInfo + (4)) % SIZE_CUInfo] = 1 << (tmp_ctStack6 - 1);
	local_ctStack_idx = ctStack_idx;
	local_CT_idx = HevcDecoder_Algo_Parser_CT_idx;
	ctStack[local_ctStack_idx][local_CT_idx] = 7;
	local_PART_2Nx2N = HevcDecoder_Algo_Parser_PART_2Nx2N;
	tokens_PartMode[(index_PartMode + (0)) % SIZE_PartMode] = local_PART_2Nx2N;

	// Update ports indexes
	index_CUInfo += 5;
	write_end_CUInfo();
	index_PartMode += 1;

}
static void read_CodingQuadTree_noCase4_aligned() {

	u8 local_OTHER;
	u8 local_ctStack_idx;
	u16 local_CT_x1;
	u16 tmp_ctStack;
	u32 local_colIndex;
	u16 tmp_colTileInPix;
	u16 local_CT_y1;
	u16 tmp_ctStack0;
	u32 local_rowIndex;
	u16 tmp_rowTileInPix;
	u8 local_CT_log2CbSize;
	u16 tmp_ctStack1;
	u16 tmp_ctStack2;
	u16 tmp_ctStack3;
	u16 tmp_ctStack4;
	u16 tmp_ctStack5;
	u16 tmp_ctStack6;
	u8 local_CT_idx;
	u8 local_PART_2Nx2N;

	local_OTHER = HevcDecoder_Algo_Parser_OTHER;
	local_ctStack_idx = ctStack_idx;
	local_CT_x1 = HevcDecoder_Algo_Parser_CT_x1;
	tmp_ctStack = ctStack[local_ctStack_idx][local_CT_x1];
	local_colIndex = colIndex;
	tmp_colTileInPix = colTileInPix[local_colIndex];
	local_ctStack_idx = ctStack_idx;
	local_CT_y1 = HevcDecoder_Algo_Parser_CT_y1;
	tmp_ctStack0 = ctStack[local_ctStack_idx][local_CT_y1];
	local_rowIndex = rowIndex;
	tmp_rowTileInPix = rowTileInPix[local_rowIndex];
	local_ctStack_idx = ctStack_idx;
	local_CT_log2CbSize = HevcDecoder_Algo_Parser_CT_log2CbSize;
	tmp_ctStack1 = ctStack[local_ctStack_idx][local_CT_log2CbSize];
	local_ctStack_idx = ctStack_idx;
	local_CT_log2CbSize = HevcDecoder_Algo_Parser_CT_log2CbSize;
	tmp_ctStack2 = ctStack[local_ctStack_idx][local_CT_log2CbSize];
	local_OTHER = HevcDecoder_Algo_Parser_OTHER;
	tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (0)] = local_OTHER;
	local_ctStack_idx = ctStack_idx;
	local_CT_x1 = HevcDecoder_Algo_Parser_CT_x1;
	tmp_ctStack3 = ctStack[local_ctStack_idx][local_CT_x1];
	tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (1)] = tmp_ctStack3;
	local_ctStack_idx = ctStack_idx;
	local_CT_y1 = HevcDecoder_Algo_Parser_CT_y1;
	tmp_ctStack4 = ctStack[local_ctStack_idx][local_CT_y1];
	tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (2)] = tmp_ctStack4;
	local_ctStack_idx = ctStack_idx;
	local_CT_log2CbSize = HevcDecoder_Algo_Parser_CT_log2CbSize;
	tmp_ctStack5 = ctStack[local_ctStack_idx][local_CT_log2CbSize];
	tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (3)] = 1 << (tmp_ctStack5 - 1);
	local_ctStack_idx = ctStack_idx;
	local_CT_log2CbSize = HevcDecoder_Algo_Parser_CT_log2CbSize;
	tmp_ctStack6 = ctStack[local_ctStack_idx][local_CT_log2CbSize];
	tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (4)] = 1 << (tmp_ctStack6 - 1);
	local_ctStack_idx = ctStack_idx;
	local_CT_idx = HevcDecoder_Algo_Parser_CT_idx;
	ctStack[local_ctStack_idx][local_CT_idx] = 7;
	local_PART_2Nx2N = HevcDecoder_Algo_Parser_PART_2Nx2N;
	tokens_PartMode[(index_PartMode + (0)) % SIZE_PartMode] = local_PART_2Nx2N;

	// Update ports indexes
	index_CUInfo += 5;
	write_end_CUInfo();
	index_PartMode += 1;

}
static i32 isSchedulable_read_CodingQuadTree_gotoCodingUnit() {
	i32 result;
	u8 local_ctStack_idx;
	u8 local_CT_idx;
	u16 tmp_ctStack;

	local_ctStack_idx = ctStack_idx;
	local_CT_idx = HevcDecoder_Algo_Parser_CT_idx;
	tmp_ctStack = ctStack[local_ctStack_idx][local_CT_idx];
	result = tmp_ctStack == 6;
	return result;
}

static void read_CodingQuadTree_gotoCodingUnit() {

	u8 local_ctStack_idx;
	u8 local_CT_idx;
	u16 local_CT_x0;
	u16 tmp_ctStack;
	u16 local_CT_y0;
	u16 tmp_ctStack0;
	u8 local_CT_log2CbSize;
	u16 tmp_ctStack1;
	u8 local_CT_ctDepth;
	u16 tmp_ctStack2;

	local_ctStack_idx = ctStack_idx;
	local_CT_idx = HevcDecoder_Algo_Parser_CT_idx;
	ctStack[local_ctStack_idx][local_CT_idx] = 7;
	cu_idx = 1;
	local_ctStack_idx = ctStack_idx;
	local_CT_x0 = HevcDecoder_Algo_Parser_CT_x0;
	tmp_ctStack = ctStack[local_ctStack_idx][local_CT_x0];
	cu_x0 = tmp_ctStack;
	local_ctStack_idx = ctStack_idx;
	local_CT_y0 = HevcDecoder_Algo_Parser_CT_y0;
	tmp_ctStack0 = ctStack[local_ctStack_idx][local_CT_y0];
	cu_y0 = tmp_ctStack0;
	local_ctStack_idx = ctStack_idx;
	local_CT_log2CbSize = HevcDecoder_Algo_Parser_CT_log2CbSize;
	tmp_ctStack1 = ctStack[local_ctStack_idx][local_CT_log2CbSize];
	cu_log2CbSize = tmp_ctStack1;
	local_ctStack_idx = ctStack_idx;
	local_CT_ctDepth = HevcDecoder_Algo_Parser_CT_ctDepth;
	tmp_ctStack2 = ctStack[local_ctStack_idx][local_CT_ctDepth];
	cu_ctDepth = tmp_ctStack2;

	// Update ports indexes

}
static i32 isSchedulable_read_CodingQuadTree_noEnd() {
	i32 result;
	u8 local_ctStack_idx;
	u8 local_CT_idx;
	u16 tmp_ctStack;

	local_ctStack_idx = ctStack_idx;
	local_CT_idx = HevcDecoder_Algo_Parser_CT_idx;
	tmp_ctStack = ctStack[local_ctStack_idx][local_CT_idx];
	local_ctStack_idx = ctStack_idx;
	result = tmp_ctStack == 7 && local_ctStack_idx != 0;
	return result;
}

static void read_CodingQuadTree_noEnd() {

	u8 local_ctStack_idx;

	local_ctStack_idx = ctStack_idx;
	ctStack_idx = local_ctStack_idx - 1;

	// Update ports indexes

}
static i32 isSchedulable_read_CodingQuadTree_end() {
	i32 result;
	u8 local_ctStack_idx;
	u8 local_CT_idx;
	u16 tmp_ctStack;

	local_ctStack_idx = ctStack_idx;
	local_CT_idx = HevcDecoder_Algo_Parser_CT_idx;
	tmp_ctStack = ctStack[local_ctStack_idx][local_CT_idx];
	local_ctStack_idx = ctStack_idx;
	result = tmp_ctStack == 7 && local_ctStack_idx == 0;
	return result;
}

static void read_CodingQuadTree_end() {

	u16 local_cu_x0;
	u8 local_cu_log2CbSize;
	i32 local_qp_block_mask;
	u16 local_cu_y0;
	i8 local_qp_y;

	local_cu_x0 = cu_x0;
	local_cu_log2CbSize = cu_log2CbSize;
	local_qp_block_mask = qp_block_mask;
	local_cu_y0 = cu_y0;
	local_cu_log2CbSize = cu_log2CbSize;
	local_qp_block_mask = qp_block_mask;
	if ((local_cu_x0 + (1 << local_cu_log2CbSize) & local_qp_block_mask) == 0 && (local_cu_y0 + (1 << local_cu_log2CbSize) & local_qp_block_mask) == 0) {
		local_qp_y = qp_y;
		qPy_pred = local_qp_y;
	}

	// Update ports indexes

}
static i32 isSchedulable_read_CodingUnit_start() {
	i32 result;
	u8 local_cu_idx;
	i32 tmp_isFifoFull;

	local_cu_idx = cu_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	result = local_cu_idx == 1 && tmp_isFifoFull;
	return result;
}

static void read_CodingUnit_start() {

	u32 res[1];
	u8 local_cu_log2CbSize;
	u8 local_Log2MinCbSize;
	u8 length;
	u16 local_cu_x0;
	i32 x_cb;
	u16 local_cu_y0;
	i32 y_cb;
	u8 local_ctStack_idx;
	u16 local_CT_x0;
	i32 ct_x0;
	u16 local_CT_y0;
	i32 ct_y0;
	u8 local_Log2CtbSize;
	i32 x0b;
	i32 y0b;
	i32 leftFlag;
	i32 upFlag;
	u16 local_sps_id;
	u16 tmp_sps_log2_ctb_size;
	u16 local_pps_id;
	u16 tmp_pps_diff_cu_qp_delta_depth;
	i32 local_ctb_left_flag;
	i32 local_ctb_up_flag;
	i32 i;
	i32 local_DEBUG_CABAC;
	i32 local_DEBUG_TRACE1;
	u8 local_INTRA;
	u8 tmp_pps_transquant_bypass_enable_flag;
	u32 tmp_res;
	u8 local_cu_transquant_bypass_flag;
	u8 local_slice_type;
	u8 local_I_SLICE;
	u32 tmp_res0;
	u8 local_SKIP;
	u8 local_skip_flag;
	u8 local_INTER;
	u32 i0;
	i32 local_counterfillSkip;
	u8 local_PART_2Nx2N;

	local_cu_log2CbSize = cu_log2CbSize;
	local_Log2MinCbSize = Log2MinCbSize;
	length = (1 << local_cu_log2CbSize) >> local_Log2MinCbSize;
	local_cu_x0 = cu_x0;
	local_Log2MinCbSize = Log2MinCbSize;
	x_cb = local_cu_x0 >> local_Log2MinCbSize;
	local_cu_y0 = cu_y0;
	local_Log2MinCbSize = Log2MinCbSize;
	y_cb = local_cu_y0 >> local_Log2MinCbSize;
	local_ctStack_idx = ctStack_idx;
	local_CT_x0 = HevcDecoder_Algo_Parser_CT_x0;
	ct_x0 = ctStack[local_ctStack_idx][local_CT_x0];
	local_ctStack_idx = ctStack_idx;
	local_CT_y0 = HevcDecoder_Algo_Parser_CT_y0;
	ct_y0 = ctStack[local_ctStack_idx][local_CT_y0];
	local_Log2CtbSize = Log2CtbSize;
	x0b = ct_x0 & (1 << local_Log2CtbSize) - 1;
	local_Log2CtbSize = Log2CtbSize;
	y0b = ct_y0 & (1 << local_Log2CtbSize) - 1;
	local_sps_id = sps_id;
	tmp_sps_log2_ctb_size = sps_log2_ctb_size[local_sps_id];
	local_pps_id = pps_id;
	tmp_pps_diff_cu_qp_delta_depth = pps_diff_cu_qp_delta_depth[local_pps_id];
	qp_block_mask = (1 << (tmp_sps_log2_ctb_size - tmp_pps_diff_cu_qp_delta_depth)) - 1;
	pcm_flag = 0;
	local_ctb_left_flag = ctb_left_flag;
	leftFlag = local_ctb_left_flag || x0b > 0;
	local_ctb_up_flag = ctb_up_flag;
	upFlag = local_ctb_up_flag || y0b > 0;
	skip_flag = 0;
	merge_flag = 0;
	i = 0;
	while (i <= 3) {
		intra_pred_mode[i] = 1;
		i = i + 1;
	}
	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	local_DEBUG_TRACE1 = HevcDecoder_Algo_Parser_DEBUG_TRACE1;
	if (local_DEBUG_CABAC && local_DEBUG_TRACE1) {
		local_cu_x0 = cu_x0;
		local_cu_y0 = cu_y0;
		local_cu_log2CbSize = cu_log2CbSize;
		printf("read_CodingUnit.start (%u, %u, %u)\n", local_cu_x0, local_cu_y0, local_cu_log2CbSize);
	} else {
		local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
		if (local_DEBUG_CABAC) {
			printf("read_CodingUnit.start\n");
		}
	}
	local_INTRA = HevcDecoder_Algo_Parser_INTRA;
	predMode = local_INTRA;
	local_pps_id = pps_id;
	tmp_pps_transquant_bypass_enable_flag = pps_transquant_bypass_enable_flag[local_pps_id];
	if (tmp_pps_transquant_bypass_enable_flag != 0) {
		HevcDecoder_Algo_Parser_get_CU_TRANSQUANT_BYPASS_FLAG(codIRange, codIOffset, ctxTable, fifo, res);
		tmp_res = res[0];
		cu_transquant_bypass_flag = tmp_res;
		local_cu_transquant_bypass_flag = cu_transquant_bypass_flag;
		if (local_cu_transquant_bypass_flag != 0) {
			local_cu_x0 = cu_x0;
			local_cu_y0 = cu_y0;
			local_cu_log2CbSize = cu_log2CbSize;
			set_deblocking_bypass(local_cu_x0, local_cu_y0, local_cu_log2CbSize);
		}
	} else {
		cu_transquant_bypass_flag = 0;
	}
	local_slice_type = slice_type;
	local_I_SLICE = HevcDecoder_Algo_Parser_I_SLICE;
	if (local_slice_type != local_I_SLICE) {
		HevcDecoder_Algo_Parser_get_SKIP_FLAG(codIRange, codIOffset, ctxTable, fifo, res, skip_flag_tab, x_cb, y_cb, leftFlag, upFlag);
		tmp_res0 = res[0];
		skip_flag = tmp_res0;
		local_SKIP = HevcDecoder_Algo_Parser_SKIP;
		predMode = local_SKIP;
		local_skip_flag = skip_flag;
		if (local_skip_flag == 1) {
			local_SKIP = HevcDecoder_Algo_Parser_SKIP;
			predMode = local_SKIP;
		} else {
			local_INTER = HevcDecoder_Algo_Parser_INTER;
			predMode = local_INTER;
		}
		i0 = 0;
		while (i0 <= length - 1) {
			local_skip_flag = skip_flag;
			skip_flag_tab[x_cb + i0][0] = local_skip_flag;
			local_skip_flag = skip_flag;
			skip_flag_tab[y_cb + i0][1] = local_skip_flag;
			i0 = i0 + 1;
		}
		local_counterfillSkip = counterfillSkip;
		counterfillSkip = local_counterfillSkip + 1;
	}
	local_cu_log2CbSize = cu_log2CbSize;
	cu_nCbS = 1 << local_cu_log2CbSize;
	local_PART_2Nx2N = HevcDecoder_Algo_Parser_PART_2Nx2N;
	partMode = local_PART_2Nx2N;
	cu_idx = 2;

	// Update ports indexes

}
static i32 isSchedulable_read_CodingUnit_gotoPredictionUnit_goto1() {
	i32 result;
	u8 local_cu_idx;
	u8 local_skip_flag;

	local_cu_idx = cu_idx;
	local_skip_flag = skip_flag;
	result = local_cu_idx == 2 && local_skip_flag != 0;
	return result;
}

static void read_CodingUnit_gotoPredictionUnit_goto1() {

	u8 local_SKIP;
	u8 local_ctStack_idx;
	u16 local_CT_x0;
	u16 tmp_ctStack;
	u32 local_colIndex;
	u16 tmp_colTileInPix;
	u16 local_CT_y0;
	u16 tmp_ctStack0;
	u32 local_rowIndex;
	u16 tmp_rowTileInPix;
	u8 local_cu_log2CbSize;
	u16 tmp_ctStack1;
	u16 tmp_ctStack2;
	u8 local_cu_nCbS;
	u16 local_cu_x0;
	u16 local_cu_y0;
	u8 local_partMode;
	u8 local_Log2MinCbSize;
	u8 local_PART_2Nx2N;
	i8 local_slice_qp;
	u8 local_TEXT_LUMA;
	u8 local_TEXT_CHROMA_U;
	u8 local_TEXT_CHROMA_V;

	local_SKIP = HevcDecoder_Algo_Parser_SKIP;
	local_ctStack_idx = ctStack_idx;
	local_CT_x0 = HevcDecoder_Algo_Parser_CT_x0;
	tmp_ctStack = ctStack[local_ctStack_idx][local_CT_x0];
	local_colIndex = colIndex;
	tmp_colTileInPix = colTileInPix[local_colIndex];
	local_ctStack_idx = ctStack_idx;
	local_CT_y0 = HevcDecoder_Algo_Parser_CT_y0;
	tmp_ctStack0 = ctStack[local_ctStack_idx][local_CT_y0];
	local_rowIndex = rowIndex;
	tmp_rowTileInPix = rowTileInPix[local_rowIndex];
	local_cu_log2CbSize = cu_log2CbSize;
	local_cu_log2CbSize = cu_log2CbSize;
	local_SKIP = HevcDecoder_Algo_Parser_SKIP;
	tokens_CUInfo[(index_CUInfo + (0)) % SIZE_CUInfo] = local_SKIP;
	local_ctStack_idx = ctStack_idx;
	local_CT_x0 = HevcDecoder_Algo_Parser_CT_x0;
	tmp_ctStack1 = ctStack[local_ctStack_idx][local_CT_x0];
	tokens_CUInfo[(index_CUInfo + (1)) % SIZE_CUInfo] = tmp_ctStack1;
	local_ctStack_idx = ctStack_idx;
	local_CT_y0 = HevcDecoder_Algo_Parser_CT_y0;
	tmp_ctStack2 = ctStack[local_ctStack_idx][local_CT_y0];
	tokens_CUInfo[(index_CUInfo + (2)) % SIZE_CUInfo] = tmp_ctStack2;
	local_cu_log2CbSize = cu_log2CbSize;
	tokens_CUInfo[(index_CUInfo + (3)) % SIZE_CUInfo] = 1 << local_cu_log2CbSize;
	local_cu_log2CbSize = cu_log2CbSize;
	tokens_CUInfo[(index_CUInfo + (4)) % SIZE_CUInfo] = 1 << local_cu_log2CbSize;
	cu_idx = 10;
	pu_idx = 1;
	local_cu_nCbS = cu_nCbS;
	pu_PbW = local_cu_nCbS;
	local_cu_nCbS = cu_nCbS;
	pu_PbH = local_cu_nCbS;
	local_cu_x0 = cu_x0;
	local_cu_y0 = cu_y0;
	local_cu_log2CbSize = cu_log2CbSize;
	local_partMode = partMode;
	local_Log2MinCbSize = Log2MinCbSize;
	HevcDecoder_Algo_Parser_intra_prediction_unit_default_value(local_cu_x0, local_cu_y0, local_cu_log2CbSize, local_partMode, local_Log2MinCbSize - 1, intraPredMode);
	tokens_Cbf[(index_Cbf + (0)) % SIZE_Cbf] = 0;
	local_PART_2Nx2N = HevcDecoder_Algo_Parser_PART_2Nx2N;
	tokens_PartMode[(index_PartMode + (0)) % SIZE_PartMode] = local_PART_2Nx2N;
	tokens_SplitTransform[(index_SplitTransform + (0)) % SIZE_SplitTransform] = 0;
	local_cu_log2CbSize = cu_log2CbSize;
	tokens_TUSize[(index_TUSize + (0)) % SIZE_TUSize] = 1 << local_cu_log2CbSize;
	tokens_TUSize[(index_TUSize + (1)) % SIZE_TUSize] = 1;
	tokens_TUSize[(index_TUSize + (2)) % SIZE_TUSize] = 0;
	tokens_TUSize[(index_TUSize + (3)) % SIZE_TUSize] = 0;
	local_slice_qp = slice_qp;
	tokens_TUSize[(index_TUSize + (4)) % SIZE_TUSize] = local_slice_qp;
	local_TEXT_LUMA = HevcDecoder_Algo_Parser_TEXT_LUMA;
	tokens_TUSize[(index_TUSize + (5)) % SIZE_TUSize] = local_TEXT_LUMA;
	tokens_TUSize[(index_TUSize + (6)) % SIZE_TUSize] = 0;
	local_cu_log2CbSize = cu_log2CbSize;
	tokens_TUSize[(index_TUSize + (7)) % SIZE_TUSize] = 1 << (local_cu_log2CbSize - 1);
	tokens_TUSize[(index_TUSize + (8)) % SIZE_TUSize] = 1;
	tokens_TUSize[(index_TUSize + (9)) % SIZE_TUSize] = 0;
	tokens_TUSize[(index_TUSize + (10)) % SIZE_TUSize] = 0;
	tokens_TUSize[(index_TUSize + (11)) % SIZE_TUSize] = 0;
	local_TEXT_CHROMA_U = HevcDecoder_Algo_Parser_TEXT_CHROMA_U;
	tokens_TUSize[(index_TUSize + (12)) % SIZE_TUSize] = local_TEXT_CHROMA_U;
	tokens_TUSize[(index_TUSize + (13)) % SIZE_TUSize] = 0;
	local_cu_log2CbSize = cu_log2CbSize;
	tokens_TUSize[(index_TUSize + (14)) % SIZE_TUSize] = 1 << (local_cu_log2CbSize - 1);
	tokens_TUSize[(index_TUSize + (15)) % SIZE_TUSize] = 1;
	tokens_TUSize[(index_TUSize + (16)) % SIZE_TUSize] = 0;
	tokens_TUSize[(index_TUSize + (17)) % SIZE_TUSize] = 0;
	tokens_TUSize[(index_TUSize + (18)) % SIZE_TUSize] = 0;
	local_TEXT_CHROMA_V = HevcDecoder_Algo_Parser_TEXT_CHROMA_V;
	tokens_TUSize[(index_TUSize + (19)) % SIZE_TUSize] = local_TEXT_CHROMA_V;
	tokens_TUSize[(index_TUSize + (20)) % SIZE_TUSize] = 0;

	// Update ports indexes
	index_CUInfo += 5;
	write_end_CUInfo();
	index_Cbf += 1;
	index_PartMode += 1;
	index_SplitTransform += 1;
	index_TUSize += 21;
	write_end_TUSize();

}
static void read_CodingUnit_gotoPredictionUnit_goto1_aligned() {

	u8 local_SKIP;
	u8 local_ctStack_idx;
	u16 local_CT_x0;
	u16 tmp_ctStack;
	u32 local_colIndex;
	u16 tmp_colTileInPix;
	u16 local_CT_y0;
	u16 tmp_ctStack0;
	u32 local_rowIndex;
	u16 tmp_rowTileInPix;
	u8 local_cu_log2CbSize;
	u16 tmp_ctStack1;
	u16 tmp_ctStack2;
	u8 local_cu_nCbS;
	u16 local_cu_x0;
	u16 local_cu_y0;
	u8 local_partMode;
	u8 local_Log2MinCbSize;
	u8 local_PART_2Nx2N;
	i8 local_slice_qp;
	u8 local_TEXT_LUMA;
	u8 local_TEXT_CHROMA_U;
	u8 local_TEXT_CHROMA_V;

	local_SKIP = HevcDecoder_Algo_Parser_SKIP;
	local_ctStack_idx = ctStack_idx;
	local_CT_x0 = HevcDecoder_Algo_Parser_CT_x0;
	tmp_ctStack = ctStack[local_ctStack_idx][local_CT_x0];
	local_colIndex = colIndex;
	tmp_colTileInPix = colTileInPix[local_colIndex];
	local_ctStack_idx = ctStack_idx;
	local_CT_y0 = HevcDecoder_Algo_Parser_CT_y0;
	tmp_ctStack0 = ctStack[local_ctStack_idx][local_CT_y0];
	local_rowIndex = rowIndex;
	tmp_rowTileInPix = rowTileInPix[local_rowIndex];
	local_cu_log2CbSize = cu_log2CbSize;
	local_cu_log2CbSize = cu_log2CbSize;
	local_SKIP = HevcDecoder_Algo_Parser_SKIP;
	tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (0)] = local_SKIP;
	local_ctStack_idx = ctStack_idx;
	local_CT_x0 = HevcDecoder_Algo_Parser_CT_x0;
	tmp_ctStack1 = ctStack[local_ctStack_idx][local_CT_x0];
	tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (1)] = tmp_ctStack1;
	local_ctStack_idx = ctStack_idx;
	local_CT_y0 = HevcDecoder_Algo_Parser_CT_y0;
	tmp_ctStack2 = ctStack[local_ctStack_idx][local_CT_y0];
	tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (2)] = tmp_ctStack2;
	local_cu_log2CbSize = cu_log2CbSize;
	tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (3)] = 1 << local_cu_log2CbSize;
	local_cu_log2CbSize = cu_log2CbSize;
	tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (4)] = 1 << local_cu_log2CbSize;
	cu_idx = 10;
	pu_idx = 1;
	local_cu_nCbS = cu_nCbS;
	pu_PbW = local_cu_nCbS;
	local_cu_nCbS = cu_nCbS;
	pu_PbH = local_cu_nCbS;
	local_cu_x0 = cu_x0;
	local_cu_y0 = cu_y0;
	local_cu_log2CbSize = cu_log2CbSize;
	local_partMode = partMode;
	local_Log2MinCbSize = Log2MinCbSize;
	HevcDecoder_Algo_Parser_intra_prediction_unit_default_value(local_cu_x0, local_cu_y0, local_cu_log2CbSize, local_partMode, local_Log2MinCbSize - 1, intraPredMode);
	tokens_Cbf[(index_Cbf + (0)) % SIZE_Cbf] = 0;
	local_PART_2Nx2N = HevcDecoder_Algo_Parser_PART_2Nx2N;
	tokens_PartMode[(index_PartMode + (0)) % SIZE_PartMode] = local_PART_2Nx2N;
	tokens_SplitTransform[(index_SplitTransform + (0)) % SIZE_SplitTransform] = 0;
	local_cu_log2CbSize = cu_log2CbSize;
	tokens_TUSize[(index_TUSize % SIZE_TUSize) + (0)] = 1 << local_cu_log2CbSize;
	tokens_TUSize[(index_TUSize % SIZE_TUSize) + (1)] = 1;
	tokens_TUSize[(index_TUSize % SIZE_TUSize) + (2)] = 0;
	tokens_TUSize[(index_TUSize % SIZE_TUSize) + (3)] = 0;
	local_slice_qp = slice_qp;
	tokens_TUSize[(index_TUSize % SIZE_TUSize) + (4)] = local_slice_qp;
	local_TEXT_LUMA = HevcDecoder_Algo_Parser_TEXT_LUMA;
	tokens_TUSize[(index_TUSize % SIZE_TUSize) + (5)] = local_TEXT_LUMA;
	tokens_TUSize[(index_TUSize % SIZE_TUSize) + (6)] = 0;
	local_cu_log2CbSize = cu_log2CbSize;
	tokens_TUSize[(index_TUSize % SIZE_TUSize) + (7)] = 1 << (local_cu_log2CbSize - 1);
	tokens_TUSize[(index_TUSize % SIZE_TUSize) + (8)] = 1;
	tokens_TUSize[(index_TUSize % SIZE_TUSize) + (9)] = 0;
	tokens_TUSize[(index_TUSize % SIZE_TUSize) + (10)] = 0;
	tokens_TUSize[(index_TUSize % SIZE_TUSize) + (11)] = 0;
	local_TEXT_CHROMA_U = HevcDecoder_Algo_Parser_TEXT_CHROMA_U;
	tokens_TUSize[(index_TUSize % SIZE_TUSize) + (12)] = local_TEXT_CHROMA_U;
	tokens_TUSize[(index_TUSize % SIZE_TUSize) + (13)] = 0;
	local_cu_log2CbSize = cu_log2CbSize;
	tokens_TUSize[(index_TUSize % SIZE_TUSize) + (14)] = 1 << (local_cu_log2CbSize - 1);
	tokens_TUSize[(index_TUSize % SIZE_TUSize) + (15)] = 1;
	tokens_TUSize[(index_TUSize % SIZE_TUSize) + (16)] = 0;
	tokens_TUSize[(index_TUSize % SIZE_TUSize) + (17)] = 0;
	tokens_TUSize[(index_TUSize % SIZE_TUSize) + (18)] = 0;
	local_TEXT_CHROMA_V = HevcDecoder_Algo_Parser_TEXT_CHROMA_V;
	tokens_TUSize[(index_TUSize % SIZE_TUSize) + (19)] = local_TEXT_CHROMA_V;
	tokens_TUSize[(index_TUSize % SIZE_TUSize) + (20)] = 0;

	// Update ports indexes
	index_CUInfo += 5;
	write_end_CUInfo();
	index_Cbf += 1;
	index_PartMode += 1;
	index_SplitTransform += 1;
	index_TUSize += 21;
	write_end_TUSize();

}
static i32 isSchedulable_read_CodingUnit_noGoto1() {
	i32 result;
	u8 local_cu_idx;
	i32 tmp_isFifoFull;
	u8 local_skip_flag;

	local_cu_idx = cu_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	local_skip_flag = skip_flag;
	result = local_cu_idx == 2 && tmp_isFifoFull && local_skip_flag == 0;
	return result;
}

static void read_CodingUnit_noGoto1() {

	u8 prev_intra_luma_pred_flag[4];
	u8 intra_chroma_table[4];
	u32 res[1];
	u8 local_Log2MinCbSize;
	u8 Log2MinIPCMCUSize;
	u8 pbOffset;
	u8 pbEnd;
	u8 local_slice_type;
	u8 local_I_SLICE;
	u32 tmp_res;
	u8 local_predMode;
	u8 local_INTRA;
	u8 local_cu_log2CbSize;
	u8 local_amp_enabled_flag;
	u32 tmp_res0;
	u8 local_partMode;
	u8 local_PART_NxN;
	u8 local_PART_2Nx2N;
	u16 local_sps_id;
	u8 tmp_sps_pcm_enabled_flag;
	u32 tmp_log2_min_pcm_cb_size;
	u32 tmp_log2_max_pcm_cb_size;
	u32 tmp_res1;
	u8 local_pcm_flag;
	u16 local_cu_x0;
	u16 local_cu_y0;
	u8 local_cu_nCbS;
	i32 i;
	i32 j;
	u32 tmp_res2;
	i32 i0;
	i32 j0;
	u8 tmp_prev_intra_luma_pred_flag;
	u8 tmp_prev_intra_luma_pred_flag0;
	u32 tmp_res3;
	u8 local_Log2CtbSize;
	i32 local_ctb_up_flag;
	i32 local_ctb_left_flag;
	u32 tmp_res4;
	u32 tmp_res5;
	u32 tmp_res6;
	u8 tmp_intra_pred_mode;
	u32 tmp_res7;
	u8 tmp_intra_chroma_table;
	u32 tmp_res8;
	u8 tmp_intra_chroma_table0;
	u8 tmp_intra_pred_mode0;

	intra_chroma_table[0] = 0;
	intra_chroma_table[1] = 26;
	intra_chroma_table[2] = 10;
	intra_chroma_table[3] = 1;
	local_Log2MinCbSize = Log2MinCbSize;
	Log2MinIPCMCUSize = local_Log2MinCbSize;
	IntraSplitFlag = 0;
	local_slice_type = slice_type;
	local_I_SLICE = HevcDecoder_Algo_Parser_I_SLICE;
	if (local_slice_type != local_I_SLICE) {
		HevcDecoder_Algo_Parser_get_PRED_MODE_FLAG(codIRange, codIOffset, ctxTable, fifo, res);
		tmp_res = res[0];
		predMode = tmp_res;
	}
	local_predMode = predMode;
	local_INTRA = HevcDecoder_Algo_Parser_INTRA;
	local_cu_log2CbSize = cu_log2CbSize;
	local_Log2MinCbSize = Log2MinCbSize;
	if (local_predMode != local_INTRA || local_cu_log2CbSize == local_Log2MinCbSize) {
		local_predMode = predMode;
		local_INTRA = HevcDecoder_Algo_Parser_INTRA;
		local_cu_log2CbSize = cu_log2CbSize;
		local_Log2MinCbSize = Log2MinCbSize;
		local_amp_enabled_flag = amp_enabled_flag;
		HevcDecoder_Algo_Parser_get_PART_SIZE(codIRange, codIOffset, ctxTable, fifo, res, local_predMode == local_INTRA, local_cu_log2CbSize, local_Log2MinCbSize, local_amp_enabled_flag);
		tmp_res0 = res[0];
		partMode = tmp_res0;
		local_partMode = partMode;
		local_PART_NxN = HevcDecoder_Algo_Parser_PART_NxN;
		local_predMode = predMode;
		local_INTRA = HevcDecoder_Algo_Parser_INTRA;
		if (local_partMode == local_PART_NxN && local_predMode == local_INTRA) {
			IntraSplitFlag = 1;
		} else {
			IntraSplitFlag = 0;
		}
	}
	cu_idx = 4;
	local_predMode = predMode;
	local_INTRA = HevcDecoder_Algo_Parser_INTRA;
	if (local_predMode == local_INTRA) {
		pcm_flag = 0;
		local_partMode = partMode;
		local_PART_2Nx2N = HevcDecoder_Algo_Parser_PART_2Nx2N;
		local_sps_id = sps_id;
		tmp_sps_pcm_enabled_flag = sps_pcm_enabled_flag[local_sps_id];
		local_cu_log2CbSize = cu_log2CbSize;
		local_sps_id = sps_id;
		tmp_log2_min_pcm_cb_size = log2_min_pcm_cb_size[local_sps_id];
		local_cu_log2CbSize = cu_log2CbSize;
		local_sps_id = sps_id;
		tmp_log2_max_pcm_cb_size = log2_max_pcm_cb_size[local_sps_id];
		if (local_partMode == local_PART_2Nx2N && tmp_sps_pcm_enabled_flag == 1 && local_cu_log2CbSize >= tmp_log2_min_pcm_cb_size && local_cu_log2CbSize <= tmp_log2_max_pcm_cb_size) {
			HevcDecoder_Algo_Parser_get_PCM_FLAG(codIRange, codIOffset, fifo, res);
			tmp_res1 = res[0];
			pcm_flag = tmp_res1;
		}
		local_pcm_flag = pcm_flag;
		if (local_pcm_flag != 0) {
			local_cu_x0 = cu_x0;
			local_cu_y0 = cu_y0;
			local_cu_log2CbSize = cu_log2CbSize;
			local_partMode = partMode;
			local_Log2MinCbSize = Log2MinCbSize;
			HevcDecoder_Algo_Parser_intra_prediction_unit_default_value(local_cu_x0, local_cu_y0, local_cu_log2CbSize, local_partMode, local_Log2MinCbSize - 1, intraPredMode);
			cu_idx = 3;
		} else {
			local_partMode = partMode;
			local_PART_NxN = HevcDecoder_Algo_Parser_PART_NxN;
			if (local_partMode == local_PART_NxN) {
				local_cu_nCbS = cu_nCbS;
				pbOffset = local_cu_nCbS >> 1;
			} else {
				local_cu_nCbS = cu_nCbS;
				pbOffset = local_cu_nCbS;
			}
			local_partMode = partMode;
			local_PART_NxN = HevcDecoder_Algo_Parser_PART_NxN;
			if (local_partMode == local_PART_NxN) {
				pbEnd = 1;
			} else {
				pbEnd = 0;
			}
			i = 0;
			while (i <= pbEnd) {
				j = 0;
				while (j <= pbEnd) {
					HevcDecoder_Algo_Parser_get_PREV_INTRA_LUMA_PRED_FLAG(codIRange, codIOffset, ctxTable, fifo, res);
					tmp_res2 = res[0];
					prev_intra_luma_pred_flag[(i << 1) + j] = tmp_res2;
					j = j + 1;
				}
				i = i + 1;
			}
			i0 = 0;
			while (i0 <= pbEnd) {
				j0 = 0;
				while (j0 <= pbEnd) {
					tmp_prev_intra_luma_pred_flag = prev_intra_luma_pred_flag[(i0 << 1) + j0];
					if (tmp_prev_intra_luma_pred_flag == 1) {
						HevcDecoder_Algo_Parser_get_MPM_IDX(codIRange, codIOffset, fifo, res);
					} else {
						HevcDecoder_Algo_Parser_get_REM_INTRA_LUMA_PRED_MODE(codIRange, codIOffset, fifo, res);
					}
					local_cu_x0 = cu_x0;
					local_cu_y0 = cu_y0;
					tmp_prev_intra_luma_pred_flag0 = prev_intra_luma_pred_flag[(i0 << 1) + j0];
					tmp_res3 = res[0];
					local_Log2CtbSize = Log2CtbSize;
					local_ctb_up_flag = ctb_up_flag;
					local_ctb_left_flag = ctb_left_flag;
					HevcDecoder_Algo_Parser_luma_intra_pred_mode(local_cu_x0 + j0 * pbOffset, local_cu_y0 + i0 * pbOffset, pbOffset, tmp_prev_intra_luma_pred_flag0, tmp_res3, res, Log2MinIPCMCUSize - 1, local_Log2CtbSize, intraPredMode, local_ctb_up_flag, local_ctb_left_flag);
					tmp_res4 = res[0];
					intra_pred_mode[(i0 << 1) + j0] = tmp_res4;
					j0 = j0 + 1;
				}
				i0 = i0 + 1;
			}
			HevcDecoder_Algo_Parser_get_INTRA_CHROMA_PRED_MODE(codIRange, codIOffset, ctxTable, fifo, res);
			tmp_res5 = res[0];
			intraChrPredModIdx = tmp_res5;
			tmp_res6 = res[0];
			if (tmp_res6 != 4) {
				tmp_intra_pred_mode = intra_pred_mode[0];
				tmp_res7 = res[0];
				tmp_intra_chroma_table = intra_chroma_table[tmp_res7];
				if (tmp_intra_pred_mode == tmp_intra_chroma_table) {
					intra_pred_mode_c = 34;
				} else {
					tmp_res8 = res[0];
					tmp_intra_chroma_table0 = intra_chroma_table[tmp_res8];
					intra_pred_mode_c = tmp_intra_chroma_table0;
				}
			} else {
				tmp_intra_pred_mode0 = intra_pred_mode[0];
				intra_pred_mode_c = tmp_intra_pred_mode0;
			}
			cu_idx = 8;
		}
	} else {
		local_cu_x0 = cu_x0;
		local_cu_y0 = cu_y0;
		local_cu_log2CbSize = cu_log2CbSize;
		local_partMode = partMode;
		local_Log2MinCbSize = Log2MinCbSize;
		HevcDecoder_Algo_Parser_intra_prediction_unit_default_value(local_cu_x0, local_cu_y0, local_cu_log2CbSize, local_partMode, local_Log2MinCbSize - 1, intraPredMode);
	}
	local_partMode = partMode;
	tokens_PartMode[(index_PartMode + (0)) % SIZE_PartMode] = local_partMode;

	// Update ports indexes
	index_PartMode += 1;

}
static i32 isSchedulable_sendIntraPredMode_skip() {
	i32 result;
	u8 local_predMode;
	u8 local_INTRA;

	local_predMode = predMode;
	local_INTRA = HevcDecoder_Algo_Parser_INTRA;
	result = local_predMode != local_INTRA;
	return result;
}

static void sendIntraPredMode_skip() {



	// Update ports indexes

}
static i32 isSchedulable_sendIntraPredMode_part2Nx2N() {
	i32 result;
	u8 local_partMode;
	u8 tmp_partModeToNumPart;
	u8 local_predMode;
	u8 local_INTRA;

	local_partMode = partMode;
	tmp_partModeToNumPart = HevcDecoder_Algo_Parser_partModeToNumPart[local_partMode];
	local_predMode = predMode;
	local_INTRA = HevcDecoder_Algo_Parser_INTRA;
	result = tmp_partModeToNumPart == 1 && local_predMode == local_INTRA;
	return result;
}

static void sendIntraPredMode_part2Nx2N() {

	u8 local_predMode;
	u8 local_ctStack_idx;
	u16 local_CT_x0;
	u16 tmp_ctStack;
	u32 local_colIndex;
	u16 tmp_colTileInPix;
	u16 local_CT_y0;
	u16 tmp_ctStack0;
	u32 local_rowIndex;
	u16 tmp_rowTileInPix;
	u8 local_cu_log2CbSize;
	u16 tmp_ctStack1;
	u16 tmp_ctStack2;
	u8 predMode_v;
	u8 idx;
	u8 local_intraChrPredModIdx;
	u8 tmp_intra_pred_mode;
	u8 tmp_intra_pred_mode0;
	u8 tmp_intra_pred_mode1;
	u8 tmp_intra_pred_mode2;
	u8 tmp_intra_pred_mode3;

	local_predMode = predMode;
	local_ctStack_idx = ctStack_idx;
	local_CT_x0 = HevcDecoder_Algo_Parser_CT_x0;
	tmp_ctStack = ctStack[local_ctStack_idx][local_CT_x0];
	local_colIndex = colIndex;
	tmp_colTileInPix = colTileInPix[local_colIndex];
	local_ctStack_idx = ctStack_idx;
	local_CT_y0 = HevcDecoder_Algo_Parser_CT_y0;
	tmp_ctStack0 = ctStack[local_ctStack_idx][local_CT_y0];
	local_rowIndex = rowIndex;
	tmp_rowTileInPix = rowTileInPix[local_rowIndex];
	local_cu_log2CbSize = cu_log2CbSize;
	local_cu_log2CbSize = cu_log2CbSize;
	local_predMode = predMode;
	tokens_CUInfo[(index_CUInfo + (0)) % SIZE_CUInfo] = local_predMode;
	local_ctStack_idx = ctStack_idx;
	local_CT_x0 = HevcDecoder_Algo_Parser_CT_x0;
	tmp_ctStack1 = ctStack[local_ctStack_idx][local_CT_x0];
	tokens_CUInfo[(index_CUInfo + (1)) % SIZE_CUInfo] = tmp_ctStack1;
	local_ctStack_idx = ctStack_idx;
	local_CT_y0 = HevcDecoder_Algo_Parser_CT_y0;
	tmp_ctStack2 = ctStack[local_ctStack_idx][local_CT_y0];
	tokens_CUInfo[(index_CUInfo + (2)) % SIZE_CUInfo] = tmp_ctStack2;
	local_cu_log2CbSize = cu_log2CbSize;
	tokens_CUInfo[(index_CUInfo + (3)) % SIZE_CUInfo] = 1 << local_cu_log2CbSize;
	local_cu_log2CbSize = cu_log2CbSize;
	tokens_CUInfo[(index_CUInfo + (4)) % SIZE_CUInfo] = 1 << local_cu_log2CbSize;
	local_intraChrPredModIdx = intraChrPredModIdx;
	if (local_intraChrPredModIdx == 4) {
		predMode_v = intra_pred_mode[0];
	} else {
		tmp_intra_pred_mode = intra_pred_mode[0];
		if (tmp_intra_pred_mode == 0) {
			idx = 0;
		} else {
			tmp_intra_pred_mode0 = intra_pred_mode[0];
			if (tmp_intra_pred_mode0 == 26) {
				idx = 1;
			} else {
				tmp_intra_pred_mode1 = intra_pred_mode[0];
				if (tmp_intra_pred_mode1 == 10) {
					idx = 2;
				} else {
					tmp_intra_pred_mode2 = intra_pred_mode[0];
					if (tmp_intra_pred_mode2 == 1) {
						idx = 3;
					} else {
						idx = 4;
					}
				}
			}
		}
		local_intraChrPredModIdx = intraChrPredModIdx;
		predMode_v = intraPredModeC[local_intraChrPredModIdx][idx];
	}
	tmp_intra_pred_mode3 = intra_pred_mode[0];
	tokens_IntraPredMode[(index_IntraPredMode + (0)) % SIZE_IntraPredMode] = tmp_intra_pred_mode3;
	tokens_IntraPredMode[(index_IntraPredMode + (1)) % SIZE_IntraPredMode] = predMode_v;

	// Update ports indexes
	index_IntraPredMode += 2;
	write_end_IntraPredMode();
	index_CUInfo += 5;
	write_end_CUInfo();

}
static void sendIntraPredMode_part2Nx2N_aligned() {

	u8 local_predMode;
	u8 local_ctStack_idx;
	u16 local_CT_x0;
	u16 tmp_ctStack;
	u32 local_colIndex;
	u16 tmp_colTileInPix;
	u16 local_CT_y0;
	u16 tmp_ctStack0;
	u32 local_rowIndex;
	u16 tmp_rowTileInPix;
	u8 local_cu_log2CbSize;
	u16 tmp_ctStack1;
	u16 tmp_ctStack2;
	u8 predMode_v;
	u8 idx;
	u8 local_intraChrPredModIdx;
	u8 tmp_intra_pred_mode;
	u8 tmp_intra_pred_mode0;
	u8 tmp_intra_pred_mode1;
	u8 tmp_intra_pred_mode2;
	u8 tmp_intra_pred_mode3;

	local_predMode = predMode;
	local_ctStack_idx = ctStack_idx;
	local_CT_x0 = HevcDecoder_Algo_Parser_CT_x0;
	tmp_ctStack = ctStack[local_ctStack_idx][local_CT_x0];
	local_colIndex = colIndex;
	tmp_colTileInPix = colTileInPix[local_colIndex];
	local_ctStack_idx = ctStack_idx;
	local_CT_y0 = HevcDecoder_Algo_Parser_CT_y0;
	tmp_ctStack0 = ctStack[local_ctStack_idx][local_CT_y0];
	local_rowIndex = rowIndex;
	tmp_rowTileInPix = rowTileInPix[local_rowIndex];
	local_cu_log2CbSize = cu_log2CbSize;
	local_cu_log2CbSize = cu_log2CbSize;
	local_predMode = predMode;
	tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (0)] = local_predMode;
	local_ctStack_idx = ctStack_idx;
	local_CT_x0 = HevcDecoder_Algo_Parser_CT_x0;
	tmp_ctStack1 = ctStack[local_ctStack_idx][local_CT_x0];
	tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (1)] = tmp_ctStack1;
	local_ctStack_idx = ctStack_idx;
	local_CT_y0 = HevcDecoder_Algo_Parser_CT_y0;
	tmp_ctStack2 = ctStack[local_ctStack_idx][local_CT_y0];
	tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (2)] = tmp_ctStack2;
	local_cu_log2CbSize = cu_log2CbSize;
	tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (3)] = 1 << local_cu_log2CbSize;
	local_cu_log2CbSize = cu_log2CbSize;
	tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (4)] = 1 << local_cu_log2CbSize;
	local_intraChrPredModIdx = intraChrPredModIdx;
	if (local_intraChrPredModIdx == 4) {
		predMode_v = intra_pred_mode[0];
	} else {
		tmp_intra_pred_mode = intra_pred_mode[0];
		if (tmp_intra_pred_mode == 0) {
			idx = 0;
		} else {
			tmp_intra_pred_mode0 = intra_pred_mode[0];
			if (tmp_intra_pred_mode0 == 26) {
				idx = 1;
			} else {
				tmp_intra_pred_mode1 = intra_pred_mode[0];
				if (tmp_intra_pred_mode1 == 10) {
					idx = 2;
				} else {
					tmp_intra_pred_mode2 = intra_pred_mode[0];
					if (tmp_intra_pred_mode2 == 1) {
						idx = 3;
					} else {
						idx = 4;
					}
				}
			}
		}
		local_intraChrPredModIdx = intraChrPredModIdx;
		predMode_v = intraPredModeC[local_intraChrPredModIdx][idx];
	}
	tmp_intra_pred_mode3 = intra_pred_mode[0];
	tokens_IntraPredMode[(index_IntraPredMode % SIZE_IntraPredMode) + (0)] = tmp_intra_pred_mode3;
	tokens_IntraPredMode[(index_IntraPredMode % SIZE_IntraPredMode) + (1)] = predMode_v;

	// Update ports indexes
	index_IntraPredMode += 2;
	write_end_IntraPredMode();
	index_CUInfo += 5;
	write_end_CUInfo();

}
static i32 isSchedulable_sendIntraPredMode_partNxN() {
	i32 result;
	u8 local_partMode;
	u8 tmp_partModeToNumPart;
	u8 local_predMode;
	u8 local_INTRA;

	local_partMode = partMode;
	tmp_partModeToNumPart = HevcDecoder_Algo_Parser_partModeToNumPart[local_partMode];
	local_predMode = predMode;
	local_INTRA = HevcDecoder_Algo_Parser_INTRA;
	result = tmp_partModeToNumPart != 1 && local_predMode == local_INTRA;
	return result;
}

static void sendIntraPredMode_partNxN() {

	u8 local_cu_log2CbSize;
	u8 CUSize;
	u8 local_predMode;
	u8 local_ctStack_idx;
	u16 local_CT_x0;
	u16 tmp_ctStack;
	u32 local_colIndex;
	u16 tmp_colTileInPix;
	u16 local_CT_y0;
	u16 tmp_ctStack0;
	u32 local_rowIndex;
	u16 tmp_rowTileInPix;
	u16 tmp_ctStack1;
	u16 tmp_colTileInPix0;
	u16 tmp_ctStack2;
	u16 tmp_rowTileInPix0;
	u16 tmp_ctStack3;
	u16 tmp_colTileInPix1;
	u16 tmp_ctStack4;
	u16 tmp_rowTileInPix1;
	u16 tmp_ctStack5;
	u16 tmp_colTileInPix2;
	u16 tmp_ctStack6;
	u16 tmp_rowTileInPix2;
	u16 tmp_ctStack7;
	u16 tmp_ctStack8;
	u16 tmp_ctStack9;
	u16 tmp_ctStack10;
	u16 tmp_ctStack11;
	u16 tmp_ctStack12;
	u16 tmp_ctStack13;
	u16 tmp_ctStack14;
	u8 idx;
	u32 i;
	u8 tmp_intra_pred_mode;
	u8 local_intraChrPredModIdx;
	u8 tmp_intra_pred_mode0;
	u8 tmp_intra_pred_mode1;
	u8 tmp_intra_pred_mode2;
	u8 tmp_intra_pred_mode3;
	u8 tmp_intra_pred_mode4;
	u8 tmp_intraPredModeC;

	local_cu_log2CbSize = cu_log2CbSize;
	CUSize = 1 << (local_cu_log2CbSize - 1);
	local_predMode = predMode;
	local_ctStack_idx = ctStack_idx;
	local_CT_x0 = HevcDecoder_Algo_Parser_CT_x0;
	tmp_ctStack = ctStack[local_ctStack_idx][local_CT_x0];
	local_colIndex = colIndex;
	tmp_colTileInPix = colTileInPix[local_colIndex];
	local_ctStack_idx = ctStack_idx;
	local_CT_y0 = HevcDecoder_Algo_Parser_CT_y0;
	tmp_ctStack0 = ctStack[local_ctStack_idx][local_CT_y0];
	local_rowIndex = rowIndex;
	tmp_rowTileInPix = rowTileInPix[local_rowIndex];
	local_predMode = predMode;
	local_ctStack_idx = ctStack_idx;
	local_CT_x0 = HevcDecoder_Algo_Parser_CT_x0;
	tmp_ctStack1 = ctStack[local_ctStack_idx][local_CT_x0];
	local_colIndex = colIndex;
	tmp_colTileInPix0 = colTileInPix[local_colIndex];
	local_ctStack_idx = ctStack_idx;
	local_CT_y0 = HevcDecoder_Algo_Parser_CT_y0;
	tmp_ctStack2 = ctStack[local_ctStack_idx][local_CT_y0];
	local_rowIndex = rowIndex;
	tmp_rowTileInPix0 = rowTileInPix[local_rowIndex];
	local_predMode = predMode;
	local_ctStack_idx = ctStack_idx;
	local_CT_x0 = HevcDecoder_Algo_Parser_CT_x0;
	tmp_ctStack3 = ctStack[local_ctStack_idx][local_CT_x0];
	local_colIndex = colIndex;
	tmp_colTileInPix1 = colTileInPix[local_colIndex];
	local_ctStack_idx = ctStack_idx;
	local_CT_y0 = HevcDecoder_Algo_Parser_CT_y0;
	tmp_ctStack4 = ctStack[local_ctStack_idx][local_CT_y0];
	local_rowIndex = rowIndex;
	tmp_rowTileInPix1 = rowTileInPix[local_rowIndex];
	local_predMode = predMode;
	local_ctStack_idx = ctStack_idx;
	local_CT_x0 = HevcDecoder_Algo_Parser_CT_x0;
	tmp_ctStack5 = ctStack[local_ctStack_idx][local_CT_x0];
	local_colIndex = colIndex;
	tmp_colTileInPix2 = colTileInPix[local_colIndex];
	local_ctStack_idx = ctStack_idx;
	local_CT_y0 = HevcDecoder_Algo_Parser_CT_y0;
	tmp_ctStack6 = ctStack[local_ctStack_idx][local_CT_y0];
	local_rowIndex = rowIndex;
	tmp_rowTileInPix2 = rowTileInPix[local_rowIndex];
	local_predMode = predMode;
	tokens_CUInfo[(index_CUInfo + (0)) % SIZE_CUInfo] = local_predMode;
	local_ctStack_idx = ctStack_idx;
	local_CT_x0 = HevcDecoder_Algo_Parser_CT_x0;
	tmp_ctStack7 = ctStack[local_ctStack_idx][local_CT_x0];
	tokens_CUInfo[(index_CUInfo + (1)) % SIZE_CUInfo] = tmp_ctStack7;
	local_ctStack_idx = ctStack_idx;
	local_CT_y0 = HevcDecoder_Algo_Parser_CT_y0;
	tmp_ctStack8 = ctStack[local_ctStack_idx][local_CT_y0];
	tokens_CUInfo[(index_CUInfo + (2)) % SIZE_CUInfo] = tmp_ctStack8;
	tokens_CUInfo[(index_CUInfo + (3)) % SIZE_CUInfo] = CUSize;
	tokens_CUInfo[(index_CUInfo + (4)) % SIZE_CUInfo] = CUSize;
	local_predMode = predMode;
	tokens_CUInfo[(index_CUInfo + (5)) % SIZE_CUInfo] = local_predMode;
	local_ctStack_idx = ctStack_idx;
	local_CT_x0 = HevcDecoder_Algo_Parser_CT_x0;
	tmp_ctStack9 = ctStack[local_ctStack_idx][local_CT_x0];
	tokens_CUInfo[(index_CUInfo + (6)) % SIZE_CUInfo] = tmp_ctStack9 + CUSize;
	local_ctStack_idx = ctStack_idx;
	local_CT_y0 = HevcDecoder_Algo_Parser_CT_y0;
	tmp_ctStack10 = ctStack[local_ctStack_idx][local_CT_y0];
	tokens_CUInfo[(index_CUInfo + (7)) % SIZE_CUInfo] = tmp_ctStack10;
	tokens_CUInfo[(index_CUInfo + (8)) % SIZE_CUInfo] = CUSize;
	tokens_CUInfo[(index_CUInfo + (9)) % SIZE_CUInfo] = CUSize;
	local_predMode = predMode;
	tokens_CUInfo[(index_CUInfo + (10)) % SIZE_CUInfo] = local_predMode;
	local_ctStack_idx = ctStack_idx;
	local_CT_x0 = HevcDecoder_Algo_Parser_CT_x0;
	tmp_ctStack11 = ctStack[local_ctStack_idx][local_CT_x0];
	tokens_CUInfo[(index_CUInfo + (11)) % SIZE_CUInfo] = tmp_ctStack11;
	local_ctStack_idx = ctStack_idx;
	local_CT_y0 = HevcDecoder_Algo_Parser_CT_y0;
	tmp_ctStack12 = ctStack[local_ctStack_idx][local_CT_y0];
	tokens_CUInfo[(index_CUInfo + (12)) % SIZE_CUInfo] = tmp_ctStack12 + CUSize;
	tokens_CUInfo[(index_CUInfo + (13)) % SIZE_CUInfo] = CUSize;
	tokens_CUInfo[(index_CUInfo + (14)) % SIZE_CUInfo] = CUSize;
	local_predMode = predMode;
	tokens_CUInfo[(index_CUInfo + (15)) % SIZE_CUInfo] = local_predMode;
	local_ctStack_idx = ctStack_idx;
	local_CT_x0 = HevcDecoder_Algo_Parser_CT_x0;
	tmp_ctStack13 = ctStack[local_ctStack_idx][local_CT_x0];
	tokens_CUInfo[(index_CUInfo + (16)) % SIZE_CUInfo] = tmp_ctStack13 + CUSize;
	local_ctStack_idx = ctStack_idx;
	local_CT_y0 = HevcDecoder_Algo_Parser_CT_y0;
	tmp_ctStack14 = ctStack[local_ctStack_idx][local_CT_y0];
	tokens_CUInfo[(index_CUInfo + (17)) % SIZE_CUInfo] = tmp_ctStack14 + CUSize;
	tokens_CUInfo[(index_CUInfo + (18)) % SIZE_CUInfo] = CUSize;
	tokens_CUInfo[(index_CUInfo + (19)) % SIZE_CUInfo] = CUSize;
	i = 0;
	while (i <= 3) {
		tmp_intra_pred_mode = intra_pred_mode[i];
		tokens_IntraPredMode[(index_IntraPredMode + (2 * i)) % SIZE_IntraPredMode] = tmp_intra_pred_mode;
		local_intraChrPredModIdx = intraChrPredModIdx;
		if (local_intraChrPredModIdx == 4) {
			tmp_intra_pred_mode0 = intra_pred_mode[i];
			tokens_IntraPredMode[(index_IntraPredMode + (2 * i + 1)) % SIZE_IntraPredMode] = tmp_intra_pred_mode0;
		} else {
			tmp_intra_pred_mode1 = intra_pred_mode[i];
			if (tmp_intra_pred_mode1 == 0) {
				idx = 0;
			} else {
				tmp_intra_pred_mode2 = intra_pred_mode[i];
				if (tmp_intra_pred_mode2 == 26) {
					idx = 1;
				} else {
					tmp_intra_pred_mode3 = intra_pred_mode[i];
					if (tmp_intra_pred_mode3 == 10) {
						idx = 2;
					} else {
						tmp_intra_pred_mode4 = intra_pred_mode[i];
						if (tmp_intra_pred_mode4 == 1) {
							idx = 3;
						} else {
							idx = 4;
						}
					}
				}
			}
			local_intraChrPredModIdx = intraChrPredModIdx;
			tmp_intraPredModeC = intraPredModeC[local_intraChrPredModIdx][idx];
			tokens_IntraPredMode[(index_IntraPredMode + (2 * i + 1)) % SIZE_IntraPredMode] = tmp_intraPredModeC;
		}
		i = i + 1;
	}

	// Update ports indexes
	index_IntraPredMode += 8;
	write_end_IntraPredMode();
	index_CUInfo += 20;
	write_end_CUInfo();

}
static void sendIntraPredMode_partNxN_aligned() {

	u8 local_cu_log2CbSize;
	u8 CUSize;
	u8 local_predMode;
	u8 local_ctStack_idx;
	u16 local_CT_x0;
	u16 tmp_ctStack;
	u32 local_colIndex;
	u16 tmp_colTileInPix;
	u16 local_CT_y0;
	u16 tmp_ctStack0;
	u32 local_rowIndex;
	u16 tmp_rowTileInPix;
	u16 tmp_ctStack1;
	u16 tmp_colTileInPix0;
	u16 tmp_ctStack2;
	u16 tmp_rowTileInPix0;
	u16 tmp_ctStack3;
	u16 tmp_colTileInPix1;
	u16 tmp_ctStack4;
	u16 tmp_rowTileInPix1;
	u16 tmp_ctStack5;
	u16 tmp_colTileInPix2;
	u16 tmp_ctStack6;
	u16 tmp_rowTileInPix2;
	u16 tmp_ctStack7;
	u16 tmp_ctStack8;
	u16 tmp_ctStack9;
	u16 tmp_ctStack10;
	u16 tmp_ctStack11;
	u16 tmp_ctStack12;
	u16 tmp_ctStack13;
	u16 tmp_ctStack14;
	u8 idx;
	u32 i;
	u8 tmp_intra_pred_mode;
	u8 local_intraChrPredModIdx;
	u8 tmp_intra_pred_mode0;
	u8 tmp_intra_pred_mode1;
	u8 tmp_intra_pred_mode2;
	u8 tmp_intra_pred_mode3;
	u8 tmp_intra_pred_mode4;
	u8 tmp_intraPredModeC;

	local_cu_log2CbSize = cu_log2CbSize;
	CUSize = 1 << (local_cu_log2CbSize - 1);
	local_predMode = predMode;
	local_ctStack_idx = ctStack_idx;
	local_CT_x0 = HevcDecoder_Algo_Parser_CT_x0;
	tmp_ctStack = ctStack[local_ctStack_idx][local_CT_x0];
	local_colIndex = colIndex;
	tmp_colTileInPix = colTileInPix[local_colIndex];
	local_ctStack_idx = ctStack_idx;
	local_CT_y0 = HevcDecoder_Algo_Parser_CT_y0;
	tmp_ctStack0 = ctStack[local_ctStack_idx][local_CT_y0];
	local_rowIndex = rowIndex;
	tmp_rowTileInPix = rowTileInPix[local_rowIndex];
	local_predMode = predMode;
	local_ctStack_idx = ctStack_idx;
	local_CT_x0 = HevcDecoder_Algo_Parser_CT_x0;
	tmp_ctStack1 = ctStack[local_ctStack_idx][local_CT_x0];
	local_colIndex = colIndex;
	tmp_colTileInPix0 = colTileInPix[local_colIndex];
	local_ctStack_idx = ctStack_idx;
	local_CT_y0 = HevcDecoder_Algo_Parser_CT_y0;
	tmp_ctStack2 = ctStack[local_ctStack_idx][local_CT_y0];
	local_rowIndex = rowIndex;
	tmp_rowTileInPix0 = rowTileInPix[local_rowIndex];
	local_predMode = predMode;
	local_ctStack_idx = ctStack_idx;
	local_CT_x0 = HevcDecoder_Algo_Parser_CT_x0;
	tmp_ctStack3 = ctStack[local_ctStack_idx][local_CT_x0];
	local_colIndex = colIndex;
	tmp_colTileInPix1 = colTileInPix[local_colIndex];
	local_ctStack_idx = ctStack_idx;
	local_CT_y0 = HevcDecoder_Algo_Parser_CT_y0;
	tmp_ctStack4 = ctStack[local_ctStack_idx][local_CT_y0];
	local_rowIndex = rowIndex;
	tmp_rowTileInPix1 = rowTileInPix[local_rowIndex];
	local_predMode = predMode;
	local_ctStack_idx = ctStack_idx;
	local_CT_x0 = HevcDecoder_Algo_Parser_CT_x0;
	tmp_ctStack5 = ctStack[local_ctStack_idx][local_CT_x0];
	local_colIndex = colIndex;
	tmp_colTileInPix2 = colTileInPix[local_colIndex];
	local_ctStack_idx = ctStack_idx;
	local_CT_y0 = HevcDecoder_Algo_Parser_CT_y0;
	tmp_ctStack6 = ctStack[local_ctStack_idx][local_CT_y0];
	local_rowIndex = rowIndex;
	tmp_rowTileInPix2 = rowTileInPix[local_rowIndex];
	local_predMode = predMode;
	tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (0)] = local_predMode;
	local_ctStack_idx = ctStack_idx;
	local_CT_x0 = HevcDecoder_Algo_Parser_CT_x0;
	tmp_ctStack7 = ctStack[local_ctStack_idx][local_CT_x0];
	tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (1)] = tmp_ctStack7;
	local_ctStack_idx = ctStack_idx;
	local_CT_y0 = HevcDecoder_Algo_Parser_CT_y0;
	tmp_ctStack8 = ctStack[local_ctStack_idx][local_CT_y0];
	tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (2)] = tmp_ctStack8;
	tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (3)] = CUSize;
	tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (4)] = CUSize;
	local_predMode = predMode;
	tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (5)] = local_predMode;
	local_ctStack_idx = ctStack_idx;
	local_CT_x0 = HevcDecoder_Algo_Parser_CT_x0;
	tmp_ctStack9 = ctStack[local_ctStack_idx][local_CT_x0];
	tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (6)] = tmp_ctStack9 + CUSize;
	local_ctStack_idx = ctStack_idx;
	local_CT_y0 = HevcDecoder_Algo_Parser_CT_y0;
	tmp_ctStack10 = ctStack[local_ctStack_idx][local_CT_y0];
	tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (7)] = tmp_ctStack10;
	tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (8)] = CUSize;
	tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (9)] = CUSize;
	local_predMode = predMode;
	tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (10)] = local_predMode;
	local_ctStack_idx = ctStack_idx;
	local_CT_x0 = HevcDecoder_Algo_Parser_CT_x0;
	tmp_ctStack11 = ctStack[local_ctStack_idx][local_CT_x0];
	tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (11)] = tmp_ctStack11;
	local_ctStack_idx = ctStack_idx;
	local_CT_y0 = HevcDecoder_Algo_Parser_CT_y0;
	tmp_ctStack12 = ctStack[local_ctStack_idx][local_CT_y0];
	tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (12)] = tmp_ctStack12 + CUSize;
	tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (13)] = CUSize;
	tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (14)] = CUSize;
	local_predMode = predMode;
	tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (15)] = local_predMode;
	local_ctStack_idx = ctStack_idx;
	local_CT_x0 = HevcDecoder_Algo_Parser_CT_x0;
	tmp_ctStack13 = ctStack[local_ctStack_idx][local_CT_x0];
	tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (16)] = tmp_ctStack13 + CUSize;
	local_ctStack_idx = ctStack_idx;
	local_CT_y0 = HevcDecoder_Algo_Parser_CT_y0;
	tmp_ctStack14 = ctStack[local_ctStack_idx][local_CT_y0];
	tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (17)] = tmp_ctStack14 + CUSize;
	tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (18)] = CUSize;
	tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (19)] = CUSize;
	i = 0;
	while (i <= 3) {
		tmp_intra_pred_mode = intra_pred_mode[i];
		tokens_IntraPredMode[(index_IntraPredMode % SIZE_IntraPredMode) + (2 * i)] = tmp_intra_pred_mode;
		local_intraChrPredModIdx = intraChrPredModIdx;
		if (local_intraChrPredModIdx == 4) {
			tmp_intra_pred_mode0 = intra_pred_mode[i];
			tokens_IntraPredMode[(index_IntraPredMode % SIZE_IntraPredMode) + (2 * i + 1)] = tmp_intra_pred_mode0;
		} else {
			tmp_intra_pred_mode1 = intra_pred_mode[i];
			if (tmp_intra_pred_mode1 == 0) {
				idx = 0;
			} else {
				tmp_intra_pred_mode2 = intra_pred_mode[i];
				if (tmp_intra_pred_mode2 == 26) {
					idx = 1;
				} else {
					tmp_intra_pred_mode3 = intra_pred_mode[i];
					if (tmp_intra_pred_mode3 == 10) {
						idx = 2;
					} else {
						tmp_intra_pred_mode4 = intra_pred_mode[i];
						if (tmp_intra_pred_mode4 == 1) {
							idx = 3;
						} else {
							idx = 4;
						}
					}
				}
			}
			local_intraChrPredModIdx = intraChrPredModIdx;
			tmp_intraPredModeC = intraPredModeC[local_intraChrPredModIdx][idx];
			tokens_IntraPredMode[(index_IntraPredMode % SIZE_IntraPredMode) + (2 * i + 1)] = tmp_intraPredModeC;
		}
		i = i + 1;
	}

	// Update ports indexes
	index_IntraPredMode += 8;
	write_end_IntraPredMode();
	index_CUInfo += 20;
	write_end_CUInfo();

}
static i32 isSchedulable_read_CodingUnit_gotoPCMSample() {
	i32 result;
	u8 local_cu_idx;

	local_cu_idx = cu_idx;
	result = local_cu_idx == 3;
	return result;
}

static void read_CodingUnit_gotoPCMSample() {


	cu_idx = 8;

	// Update ports indexes

}
static i32 isSchedulable_read_CodingUnit_gotoPredictionUnit_goto2() {
	i32 result;
	u8 local_cu_idx;

	local_cu_idx = cu_idx;
	local_cu_idx = cu_idx;
	local_cu_idx = cu_idx;
	local_cu_idx = cu_idx;
	result = local_cu_idx == 4 || local_cu_idx == 5 || local_cu_idx == 6 || local_cu_idx == 7;
	return result;
}

static void read_CodingUnit_gotoPredictionUnit_goto2() {

	u8 local_cu_nCbS;
	u8 nCbS_2;
	u8 nCbS_4;
	u8 nCbS_3_4;
	u8 local_ctStack_idx;
	u16 local_CT_x0;
	i32 x0;
	u16 local_CT_y0;
	i32 y0;
	u8 local_partMode;
	u8 local_PART_2Nx2N;
	u8 local_PART_2NxN;
	u8 local_cu_idx;
	u8 local_PART_Nx2N;
	u8 local_PART_2NxnU;
	u8 local_PART_2NxnD;
	u8 local_PART_nLx2N;
	u8 local_PART_nRx2N;
	u8 local_predMode;
	u32 local_colIndex;
	u16 tmp_colTileInPix;
	u32 local_rowIndex;
	u16 tmp_rowTileInPix;
	u8 local_pu_PbW;
	u8 local_pu_PbH;

	local_cu_nCbS = cu_nCbS;
	nCbS_2 = local_cu_nCbS >> 1;
	local_cu_nCbS = cu_nCbS;
	nCbS_4 = local_cu_nCbS >> 2;
	local_cu_nCbS = cu_nCbS;
	nCbS_3_4 = local_cu_nCbS - nCbS_4;
	local_ctStack_idx = ctStack_idx;
	local_CT_x0 = HevcDecoder_Algo_Parser_CT_x0;
	x0 = ctStack[local_ctStack_idx][local_CT_x0];
	local_ctStack_idx = ctStack_idx;
	local_CT_y0 = HevcDecoder_Algo_Parser_CT_y0;
	y0 = ctStack[local_ctStack_idx][local_CT_y0];
	pu_idx = 1;
	local_cu_nCbS = cu_nCbS;
	pu_PbW = local_cu_nCbS;
	local_cu_nCbS = cu_nCbS;
	pu_PbH = local_cu_nCbS;
	local_partMode = partMode;
	local_PART_2Nx2N = HevcDecoder_Algo_Parser_PART_2Nx2N;
	if (local_partMode == local_PART_2Nx2N) {
		cu_idx = 8;
	} else {
		local_partMode = partMode;
		local_PART_2NxN = HevcDecoder_Algo_Parser_PART_2NxN;
		if (local_partMode == local_PART_2NxN) {
			pu_PbH = nCbS_2;
			local_cu_idx = cu_idx;
			if (local_cu_idx == 4) {
				cu_idx = 5;
			} else {
				cu_idx = 8;
				y0 = y0 + nCbS_2;
			}
		} else {
			local_partMode = partMode;
			local_PART_Nx2N = HevcDecoder_Algo_Parser_PART_Nx2N;
			if (local_partMode == local_PART_Nx2N) {
				pu_PbW = nCbS_2;
				local_cu_idx = cu_idx;
				if (local_cu_idx == 4) {
					cu_idx = 5;
				} else {
					cu_idx = 8;
					x0 = x0 + nCbS_2;
				}
			} else {
				local_partMode = partMode;
				local_PART_2NxnU = HevcDecoder_Algo_Parser_PART_2NxnU;
				if (local_partMode == local_PART_2NxnU) {
					pu_PbH = nCbS_4;
					local_cu_idx = cu_idx;
					if (local_cu_idx == 4) {
						cu_idx = 5;
					} else {
						pu_PbH = nCbS_3_4;
						cu_idx = 8;
						y0 = y0 + nCbS_4;
					}
				} else {
					local_partMode = partMode;
					local_PART_2NxnD = HevcDecoder_Algo_Parser_PART_2NxnD;
					if (local_partMode == local_PART_2NxnD) {
						local_cu_idx = cu_idx;
						if (local_cu_idx == 4) {
							pu_PbH = nCbS_3_4;
							cu_idx = 5;
						} else {
							pu_PbH = nCbS_4;
							cu_idx = 8;
							y0 = y0 + nCbS_3_4;
						}
					} else {
						local_partMode = partMode;
						local_PART_nLx2N = HevcDecoder_Algo_Parser_PART_nLx2N;
						if (local_partMode == local_PART_nLx2N) {
							local_cu_idx = cu_idx;
							if (local_cu_idx == 4) {
								pu_PbW = nCbS_4;
								cu_idx = 5;
							} else {
								pu_PbW = nCbS_3_4;
								x0 = x0 + nCbS_4;
								cu_idx = 8;
							}
						} else {
							local_partMode = partMode;
							local_PART_nRx2N = HevcDecoder_Algo_Parser_PART_nRx2N;
							if (local_partMode == local_PART_nRx2N) {
								local_cu_idx = cu_idx;
								if (local_cu_idx == 4) {
									pu_PbW = nCbS_3_4;
									cu_idx = 5;
								} else {
									pu_PbW = nCbS_4;
									x0 = x0 + nCbS_3_4;
									cu_idx = 8;
								}
							} else {
								pu_PbW = nCbS_2;
								pu_PbH = nCbS_2;
								local_cu_idx = cu_idx;
								if (local_cu_idx == 4) {
									cu_idx = 5;
								} else {
									local_cu_idx = cu_idx;
									if (local_cu_idx == 5) {
										x0 = x0 + nCbS_2;
										cu_idx = 6;
									} else {
										local_cu_idx = cu_idx;
										if (local_cu_idx == 6) {
											y0 = y0 + nCbS_2;
											cu_idx = 7;
										} else {
											x0 = x0 + nCbS_2;
											y0 = y0 + nCbS_2;
											cu_idx = 8;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	local_predMode = predMode;
	local_colIndex = colIndex;
	tmp_colTileInPix = colTileInPix[local_colIndex];
	local_rowIndex = rowIndex;
	tmp_rowTileInPix = rowTileInPix[local_rowIndex];
	local_pu_PbW = pu_PbW;
	local_pu_PbH = pu_PbH;
	local_predMode = predMode;
	tokens_CUInfo[(index_CUInfo + (0)) % SIZE_CUInfo] = local_predMode;
	tokens_CUInfo[(index_CUInfo + (1)) % SIZE_CUInfo] = x0;
	tokens_CUInfo[(index_CUInfo + (2)) % SIZE_CUInfo] = y0;
	local_pu_PbW = pu_PbW;
	tokens_CUInfo[(index_CUInfo + (3)) % SIZE_CUInfo] = local_pu_PbW;
	local_pu_PbH = pu_PbH;
	tokens_CUInfo[(index_CUInfo + (4)) % SIZE_CUInfo] = local_pu_PbH;

	// Update ports indexes
	index_CUInfo += 5;
	write_end_CUInfo();

}
static void read_CodingUnit_gotoPredictionUnit_goto2_aligned() {

	u8 local_cu_nCbS;
	u8 nCbS_2;
	u8 nCbS_4;
	u8 nCbS_3_4;
	u8 local_ctStack_idx;
	u16 local_CT_x0;
	i32 x0;
	u16 local_CT_y0;
	i32 y0;
	u8 local_partMode;
	u8 local_PART_2Nx2N;
	u8 local_PART_2NxN;
	u8 local_cu_idx;
	u8 local_PART_Nx2N;
	u8 local_PART_2NxnU;
	u8 local_PART_2NxnD;
	u8 local_PART_nLx2N;
	u8 local_PART_nRx2N;
	u8 local_predMode;
	u32 local_colIndex;
	u16 tmp_colTileInPix;
	u32 local_rowIndex;
	u16 tmp_rowTileInPix;
	u8 local_pu_PbW;
	u8 local_pu_PbH;

	local_cu_nCbS = cu_nCbS;
	nCbS_2 = local_cu_nCbS >> 1;
	local_cu_nCbS = cu_nCbS;
	nCbS_4 = local_cu_nCbS >> 2;
	local_cu_nCbS = cu_nCbS;
	nCbS_3_4 = local_cu_nCbS - nCbS_4;
	local_ctStack_idx = ctStack_idx;
	local_CT_x0 = HevcDecoder_Algo_Parser_CT_x0;
	x0 = ctStack[local_ctStack_idx][local_CT_x0];
	local_ctStack_idx = ctStack_idx;
	local_CT_y0 = HevcDecoder_Algo_Parser_CT_y0;
	y0 = ctStack[local_ctStack_idx][local_CT_y0];
	pu_idx = 1;
	local_cu_nCbS = cu_nCbS;
	pu_PbW = local_cu_nCbS;
	local_cu_nCbS = cu_nCbS;
	pu_PbH = local_cu_nCbS;
	local_partMode = partMode;
	local_PART_2Nx2N = HevcDecoder_Algo_Parser_PART_2Nx2N;
	if (local_partMode == local_PART_2Nx2N) {
		cu_idx = 8;
	} else {
		local_partMode = partMode;
		local_PART_2NxN = HevcDecoder_Algo_Parser_PART_2NxN;
		if (local_partMode == local_PART_2NxN) {
			pu_PbH = nCbS_2;
			local_cu_idx = cu_idx;
			if (local_cu_idx == 4) {
				cu_idx = 5;
			} else {
				cu_idx = 8;
				y0 = y0 + nCbS_2;
			}
		} else {
			local_partMode = partMode;
			local_PART_Nx2N = HevcDecoder_Algo_Parser_PART_Nx2N;
			if (local_partMode == local_PART_Nx2N) {
				pu_PbW = nCbS_2;
				local_cu_idx = cu_idx;
				if (local_cu_idx == 4) {
					cu_idx = 5;
				} else {
					cu_idx = 8;
					x0 = x0 + nCbS_2;
				}
			} else {
				local_partMode = partMode;
				local_PART_2NxnU = HevcDecoder_Algo_Parser_PART_2NxnU;
				if (local_partMode == local_PART_2NxnU) {
					pu_PbH = nCbS_4;
					local_cu_idx = cu_idx;
					if (local_cu_idx == 4) {
						cu_idx = 5;
					} else {
						pu_PbH = nCbS_3_4;
						cu_idx = 8;
						y0 = y0 + nCbS_4;
					}
				} else {
					local_partMode = partMode;
					local_PART_2NxnD = HevcDecoder_Algo_Parser_PART_2NxnD;
					if (local_partMode == local_PART_2NxnD) {
						local_cu_idx = cu_idx;
						if (local_cu_idx == 4) {
							pu_PbH = nCbS_3_4;
							cu_idx = 5;
						} else {
							pu_PbH = nCbS_4;
							cu_idx = 8;
							y0 = y0 + nCbS_3_4;
						}
					} else {
						local_partMode = partMode;
						local_PART_nLx2N = HevcDecoder_Algo_Parser_PART_nLx2N;
						if (local_partMode == local_PART_nLx2N) {
							local_cu_idx = cu_idx;
							if (local_cu_idx == 4) {
								pu_PbW = nCbS_4;
								cu_idx = 5;
							} else {
								pu_PbW = nCbS_3_4;
								x0 = x0 + nCbS_4;
								cu_idx = 8;
							}
						} else {
							local_partMode = partMode;
							local_PART_nRx2N = HevcDecoder_Algo_Parser_PART_nRx2N;
							if (local_partMode == local_PART_nRx2N) {
								local_cu_idx = cu_idx;
								if (local_cu_idx == 4) {
									pu_PbW = nCbS_3_4;
									cu_idx = 5;
								} else {
									pu_PbW = nCbS_4;
									x0 = x0 + nCbS_3_4;
									cu_idx = 8;
								}
							} else {
								pu_PbW = nCbS_2;
								pu_PbH = nCbS_2;
								local_cu_idx = cu_idx;
								if (local_cu_idx == 4) {
									cu_idx = 5;
								} else {
									local_cu_idx = cu_idx;
									if (local_cu_idx == 5) {
										x0 = x0 + nCbS_2;
										cu_idx = 6;
									} else {
										local_cu_idx = cu_idx;
										if (local_cu_idx == 6) {
											y0 = y0 + nCbS_2;
											cu_idx = 7;
										} else {
											x0 = x0 + nCbS_2;
											y0 = y0 + nCbS_2;
											cu_idx = 8;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	local_predMode = predMode;
	local_colIndex = colIndex;
	tmp_colTileInPix = colTileInPix[local_colIndex];
	local_rowIndex = rowIndex;
	tmp_rowTileInPix = rowTileInPix[local_rowIndex];
	local_pu_PbW = pu_PbW;
	local_pu_PbH = pu_PbH;
	local_predMode = predMode;
	tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (0)] = local_predMode;
	tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (1)] = x0;
	tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (2)] = y0;
	local_pu_PbW = pu_PbW;
	tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (3)] = local_pu_PbW;
	local_pu_PbH = pu_PbH;
	tokens_CUInfo[(index_CUInfo % SIZE_CUInfo) + (4)] = local_pu_PbH;

	// Update ports indexes
	index_CUInfo += 5;
	write_end_CUInfo();

}
static i32 isSchedulable_read_CodingUnit_endFunction() {
	i32 result;
	u8 local_cu_idx;
	i32 tmp_isFifoFull;

	local_cu_idx = cu_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	result = local_cu_idx == 8 && tmp_isFifoFull;
	return result;
}

static void read_CodingUnit_endFunction() {

	u32 res[1];
	u8 local_pcm_flag;
	u8 local_predMode;
	u8 local_INTRA;
	u8 local_partMode;
	u8 local_PART_2Nx2N;
	u8 local_merge_flag;
	u32 tmp_res;
	u16 local_sps_id;
	u8 tmp_sps_max_transform_hierarchy_depth_intra;
	u8 local_IntraSplitFlag;
	u8 tmp_sps_max_transform_hierarchy_depth_inter;

	res[0] = 1;
	cu_idx = 10;
	local_pcm_flag = pcm_flag;
	if (local_pcm_flag == 0) {
		local_predMode = predMode;
		local_INTRA = HevcDecoder_Algo_Parser_INTRA;
		local_partMode = partMode;
		local_PART_2Nx2N = HevcDecoder_Algo_Parser_PART_2Nx2N;
		local_merge_flag = merge_flag;
		if (local_predMode != local_INTRA && !(local_partMode == local_PART_2Nx2N && local_merge_flag == 1)) {
			HevcDecoder_Algo_Parser_get_NO_RESIDUAL_SYNTAX_FLAG(codIRange, codIOffset, ctxTable, fifo, res);
		}
		tmp_res = res[0];
		if (tmp_res != 0) {
			local_predMode = predMode;
			local_INTRA = HevcDecoder_Algo_Parser_INTRA;
			if (local_predMode == local_INTRA) {
				local_sps_id = sps_id;
				tmp_sps_max_transform_hierarchy_depth_intra = sps_max_transform_hierarchy_depth_intra[local_sps_id];
				local_IntraSplitFlag = IntraSplitFlag;
				MaxTrafoDepth = tmp_sps_max_transform_hierarchy_depth_intra + local_IntraSplitFlag;
			} else {
				local_sps_id = sps_id;
				tmp_sps_max_transform_hierarchy_depth_inter = sps_max_transform_hierarchy_depth_inter[local_sps_id];
				MaxTrafoDepth = tmp_sps_max_transform_hierarchy_depth_inter;
			}
			cu_idx = 9;
		} else {
			local_predMode = predMode;
			local_INTRA = HevcDecoder_Algo_Parser_INTRA;
			if (local_predMode != local_INTRA) {
				cu_idx = 11;
			}
		}
	}

	// Update ports indexes

}
static i32 isSchedulable_read_CodingUnit_endFunctionSend() {
	i32 result;
	u8 local_cu_idx;

	local_cu_idx = cu_idx;
	result = local_cu_idx == 11;
	return result;
}

static void read_CodingUnit_endFunctionSend() {

	u8 local_cu_log2CbSize;
	i8 local_slice_qp;
	u8 local_TEXT_LUMA;
	u8 local_TEXT_CHROMA_U;
	u8 local_TEXT_CHROMA_V;

	cu_idx = 10;
	tokens_SplitTransform[(index_SplitTransform + (0)) % SIZE_SplitTransform] = 0;
	local_cu_log2CbSize = cu_log2CbSize;
	tokens_TUSize[(index_TUSize + (0)) % SIZE_TUSize] = 1 << local_cu_log2CbSize;
	tokens_TUSize[(index_TUSize + (1)) % SIZE_TUSize] = 1;
	tokens_TUSize[(index_TUSize + (2)) % SIZE_TUSize] = 0;
	tokens_TUSize[(index_TUSize + (3)) % SIZE_TUSize] = 0;
	local_slice_qp = slice_qp;
	tokens_TUSize[(index_TUSize + (4)) % SIZE_TUSize] = local_slice_qp;
	local_TEXT_LUMA = HevcDecoder_Algo_Parser_TEXT_LUMA;
	tokens_TUSize[(index_TUSize + (5)) % SIZE_TUSize] = local_TEXT_LUMA;
	tokens_TUSize[(index_TUSize + (6)) % SIZE_TUSize] = 0;
	local_cu_log2CbSize = cu_log2CbSize;
	tokens_TUSize[(index_TUSize + (7)) % SIZE_TUSize] = 1 << (local_cu_log2CbSize - 1);
	tokens_TUSize[(index_TUSize + (8)) % SIZE_TUSize] = 1;
	tokens_TUSize[(index_TUSize + (9)) % SIZE_TUSize] = 0;
	tokens_TUSize[(index_TUSize + (10)) % SIZE_TUSize] = 0;
	tokens_TUSize[(index_TUSize + (11)) % SIZE_TUSize] = 0;
	local_TEXT_CHROMA_U = HevcDecoder_Algo_Parser_TEXT_CHROMA_U;
	tokens_TUSize[(index_TUSize + (12)) % SIZE_TUSize] = local_TEXT_CHROMA_U;
	tokens_TUSize[(index_TUSize + (13)) % SIZE_TUSize] = 0;
	local_cu_log2CbSize = cu_log2CbSize;
	tokens_TUSize[(index_TUSize + (14)) % SIZE_TUSize] = 1 << (local_cu_log2CbSize - 1);
	tokens_TUSize[(index_TUSize + (15)) % SIZE_TUSize] = 1;
	tokens_TUSize[(index_TUSize + (16)) % SIZE_TUSize] = 0;
	tokens_TUSize[(index_TUSize + (17)) % SIZE_TUSize] = 0;
	tokens_TUSize[(index_TUSize + (18)) % SIZE_TUSize] = 0;
	local_TEXT_CHROMA_V = HevcDecoder_Algo_Parser_TEXT_CHROMA_V;
	tokens_TUSize[(index_TUSize + (19)) % SIZE_TUSize] = local_TEXT_CHROMA_V;
	tokens_TUSize[(index_TUSize + (20)) % SIZE_TUSize] = 0;
	tokens_Cbf[(index_Cbf + (0)) % SIZE_Cbf] = 0;

	// Update ports indexes
	index_SplitTransform += 1;
	index_TUSize += 21;
	write_end_TUSize();
	index_Cbf += 1;

}
static void read_CodingUnit_endFunctionSend_aligned() {

	u8 local_cu_log2CbSize;
	i8 local_slice_qp;
	u8 local_TEXT_LUMA;
	u8 local_TEXT_CHROMA_U;
	u8 local_TEXT_CHROMA_V;

	cu_idx = 10;
	tokens_SplitTransform[(index_SplitTransform + (0)) % SIZE_SplitTransform] = 0;
	local_cu_log2CbSize = cu_log2CbSize;
	tokens_TUSize[(index_TUSize % SIZE_TUSize) + (0)] = 1 << local_cu_log2CbSize;
	tokens_TUSize[(index_TUSize % SIZE_TUSize) + (1)] = 1;
	tokens_TUSize[(index_TUSize % SIZE_TUSize) + (2)] = 0;
	tokens_TUSize[(index_TUSize % SIZE_TUSize) + (3)] = 0;
	local_slice_qp = slice_qp;
	tokens_TUSize[(index_TUSize % SIZE_TUSize) + (4)] = local_slice_qp;
	local_TEXT_LUMA = HevcDecoder_Algo_Parser_TEXT_LUMA;
	tokens_TUSize[(index_TUSize % SIZE_TUSize) + (5)] = local_TEXT_LUMA;
	tokens_TUSize[(index_TUSize % SIZE_TUSize) + (6)] = 0;
	local_cu_log2CbSize = cu_log2CbSize;
	tokens_TUSize[(index_TUSize % SIZE_TUSize) + (7)] = 1 << (local_cu_log2CbSize - 1);
	tokens_TUSize[(index_TUSize % SIZE_TUSize) + (8)] = 1;
	tokens_TUSize[(index_TUSize % SIZE_TUSize) + (9)] = 0;
	tokens_TUSize[(index_TUSize % SIZE_TUSize) + (10)] = 0;
	tokens_TUSize[(index_TUSize % SIZE_TUSize) + (11)] = 0;
	local_TEXT_CHROMA_U = HevcDecoder_Algo_Parser_TEXT_CHROMA_U;
	tokens_TUSize[(index_TUSize % SIZE_TUSize) + (12)] = local_TEXT_CHROMA_U;
	tokens_TUSize[(index_TUSize % SIZE_TUSize) + (13)] = 0;
	local_cu_log2CbSize = cu_log2CbSize;
	tokens_TUSize[(index_TUSize % SIZE_TUSize) + (14)] = 1 << (local_cu_log2CbSize - 1);
	tokens_TUSize[(index_TUSize % SIZE_TUSize) + (15)] = 1;
	tokens_TUSize[(index_TUSize % SIZE_TUSize) + (16)] = 0;
	tokens_TUSize[(index_TUSize % SIZE_TUSize) + (17)] = 0;
	tokens_TUSize[(index_TUSize % SIZE_TUSize) + (18)] = 0;
	local_TEXT_CHROMA_V = HevcDecoder_Algo_Parser_TEXT_CHROMA_V;
	tokens_TUSize[(index_TUSize % SIZE_TUSize) + (19)] = local_TEXT_CHROMA_V;
	tokens_TUSize[(index_TUSize % SIZE_TUSize) + (20)] = 0;
	tokens_Cbf[(index_Cbf + (0)) % SIZE_Cbf] = 0;

	// Update ports indexes
	index_SplitTransform += 1;
	index_TUSize += 21;
	write_end_TUSize();
	index_Cbf += 1;

}
static i32 isSchedulable_read_CodingUnit_gotoTransformTree() {
	i32 result;
	u8 local_cu_idx;

	local_cu_idx = cu_idx;
	result = local_cu_idx == 9;
	return result;
}

static void read_CodingUnit_gotoTransformTree() {

	u8 local_TT_idx;
	u16 local_TT_x0;
	u16 local_cu_x0;
	u16 local_TT_y0;
	u16 local_cu_y0;
	u16 local_TT_xBase;
	u16 local_TT_yBase;
	u8 local_TT_log2TrafoSize;
	u8 local_cu_log2CbSize;
	u8 local_TT_trafoDepth;
	u8 local_TT_blkIdx;

	cu_idx = 10;
	ttStack_idx = 0;
	local_TT_idx = HevcDecoder_Algo_Parser_TT_idx;
	ttStack[0][local_TT_idx] = 1;
	local_TT_x0 = HevcDecoder_Algo_Parser_TT_x0;
	local_cu_x0 = cu_x0;
	ttStack[0][local_TT_x0] = local_cu_x0;
	local_TT_y0 = HevcDecoder_Algo_Parser_TT_y0;
	local_cu_y0 = cu_y0;
	ttStack[0][local_TT_y0] = local_cu_y0;
	local_TT_xBase = HevcDecoder_Algo_Parser_TT_xBase;
	local_cu_x0 = cu_x0;
	ttStack[0][local_TT_xBase] = local_cu_x0;
	local_TT_yBase = HevcDecoder_Algo_Parser_TT_yBase;
	local_cu_y0 = cu_y0;
	ttStack[0][local_TT_yBase] = local_cu_y0;
	local_TT_log2TrafoSize = HevcDecoder_Algo_Parser_TT_log2TrafoSize;
	local_cu_log2CbSize = cu_log2CbSize;
	ttStack[0][local_TT_log2TrafoSize] = local_cu_log2CbSize;
	local_TT_trafoDepth = HevcDecoder_Algo_Parser_TT_trafoDepth;
	ttStack[0][local_TT_trafoDepth] = 0;
	local_TT_blkIdx = HevcDecoder_Algo_Parser_TT_blkIdx;
	ttStack[0][local_TT_blkIdx] = 0;

	// Update ports indexes

}
static i32 isSchedulable_read_CodingUnit_end() {
	i32 result;
	u8 local_cu_idx;

	local_cu_idx = cu_idx;
	result = local_cu_idx == 10;
	return result;
}

static void read_CodingUnit_end() {

	u16 local_cu_x0;
	u8 local_Log2MinCbSize;
	u16 ct_x_cb;
	u16 local_cu_y0;
	u16 ct_y_cb;
	i32 x;
	u8 local_cu_log2CbSize;
	u16 local_pps_id;
	u8 tmp_pps_cu_qp_delta_enabled_flag;
	u8 local_IsCuQpDeltaCoded;
	i32 local_min_cb_width;
	i32 y;
	u8 local_length;
	i32 i;
	i8 local_qp_y;
	i32 local_qp_block_mask;
	u32 i0;
	u8 local_cu_ctDepth;

	local_cu_x0 = cu_x0;
	local_Log2MinCbSize = Log2MinCbSize;
	ct_x_cb = local_cu_x0 >> local_Log2MinCbSize;
	local_cu_y0 = cu_y0;
	local_Log2MinCbSize = Log2MinCbSize;
	ct_y_cb = local_cu_y0 >> local_Log2MinCbSize;
	x = 0;
	local_cu_log2CbSize = cu_log2CbSize;
	local_Log2MinCbSize = Log2MinCbSize;
	length = (1 << local_cu_log2CbSize) >> local_Log2MinCbSize;
	local_pps_id = pps_id;
	tmp_pps_cu_qp_delta_enabled_flag = pps_cu_qp_delta_enabled_flag[local_pps_id];
	local_IsCuQpDeltaCoded = IsCuQpDeltaCoded;
	if (tmp_pps_cu_qp_delta_enabled_flag != 0 && local_IsCuQpDeltaCoded == 0) {
		set_qPy();
	}
	local_min_cb_width = min_cb_width;
	x = ct_y_cb * local_min_cb_width + ct_x_cb;
	y = 0;
	local_length = length;
	while (y <= local_length - 1) {
		i = 0;
		local_length = length;
		while (i <= local_length - 1) {
			local_qp_y = qp_y;
			qp_y_tab[x + i] = local_qp_y;
			i = i + 1;
		}
		local_min_cb_width = min_cb_width;
		x = x + local_min_cb_width;
		y = y + 1;
	}
	local_cu_x0 = cu_x0;
	local_cu_log2CbSize = cu_log2CbSize;
	local_qp_block_mask = qp_block_mask;
	local_cu_y0 = cu_y0;
	local_cu_log2CbSize = cu_log2CbSize;
	local_qp_block_mask = qp_block_mask;
	if ((local_cu_x0 + (1 << local_cu_log2CbSize) & local_qp_block_mask) == 0 && (local_cu_y0 + (1 << local_cu_log2CbSize) & local_qp_block_mask) == 0) {
		local_qp_y = qp_y;
		qPy_pred = local_qp_y;
	}
	i0 = 0;
	local_length = length;
	while (i0 <= local_length - 1) {
		local_cu_ctDepth = cu_ctDepth;
		cu_top_ctDepth[ct_x_cb + i0] = local_cu_ctDepth;
		local_cu_ctDepth = cu_ctDepth;
		cu_left_ctDepth[ct_y_cb + i0] = local_cu_ctDepth;
		i0 = i0 + 1;
	}

	// Update ports indexes

}
static i32 isSchedulable_read_CodingUnit_end_sendQp_blk4x4() {
	i32 result;
	u8 local_length;

	local_length = length;
	result = local_length == 0;
	return result;
}

static void read_CodingUnit_end_sendQp_blk4x4() {

	i8 local_qp_y;

	local_qp_y = qp_y;
	tokens_Qp[(index_Qp + (0)) % SIZE_Qp] = local_qp_y;

	// Update ports indexes
	index_Qp += 1;

}
static i32 isSchedulable_read_CodingUnit_end_sendQp_blk8x8() {
	i32 result;
	u8 local_length;

	local_length = length;
	result = local_length == 1;
	return result;
}

static void read_CodingUnit_end_sendQp_blk8x8() {

	i32 k;
	i8 local_qp_y;

	k = 0;
	while (k <= 3) {
		local_qp_y = qp_y;
		tokens_Qp[(index_Qp + (k)) % SIZE_Qp] = local_qp_y;
		k = k + 1;
	}

	// Update ports indexes
	index_Qp += 4;
	write_end_Qp();

}
static void read_CodingUnit_end_sendQp_blk8x8_aligned() {

	i32 k;
	i8 local_qp_y;

	k = 0;
	while (k <= 3) {
		local_qp_y = qp_y;
		tokens_Qp[(index_Qp % SIZE_Qp) + (k)] = local_qp_y;
		k = k + 1;
	}

	// Update ports indexes
	index_Qp += 4;
	write_end_Qp();

}
static i32 isSchedulable_read_CodingUnit_end_sendQp_blk16x16() {
	i32 result;
	u8 local_length;

	local_length = length;
	result = local_length == 2;
	return result;
}

static void read_CodingUnit_end_sendQp_blk16x16() {

	i32 k;
	i8 local_qp_y;

	k = 0;
	while (k <= 15) {
		local_qp_y = qp_y;
		tokens_Qp[(index_Qp + (k)) % SIZE_Qp] = local_qp_y;
		k = k + 1;
	}

	// Update ports indexes
	index_Qp += 16;
	write_end_Qp();

}
static void read_CodingUnit_end_sendQp_blk16x16_aligned() {

	i32 k;
	i8 local_qp_y;

	k = 0;
	while (k <= 15) {
		local_qp_y = qp_y;
		tokens_Qp[(index_Qp % SIZE_Qp) + (k)] = local_qp_y;
		k = k + 1;
	}

	// Update ports indexes
	index_Qp += 16;
	write_end_Qp();

}
static i32 isSchedulable_read_CodingUnit_end_sendQp_blk32x32() {
	i32 result;
	u8 local_length;

	local_length = length;
	result = local_length == 4;
	return result;
}

static void read_CodingUnit_end_sendQp_blk32x32() {

	i32 k;
	i8 local_qp_y;

	k = 0;
	while (k <= 63) {
		local_qp_y = qp_y;
		tokens_Qp[(index_Qp + (k)) % SIZE_Qp] = local_qp_y;
		k = k + 1;
	}

	// Update ports indexes
	index_Qp += 64;
	write_end_Qp();

}
static void read_CodingUnit_end_sendQp_blk32x32_aligned() {

	i32 k;
	i8 local_qp_y;

	k = 0;
	while (k <= 63) {
		local_qp_y = qp_y;
		tokens_Qp[(index_Qp % SIZE_Qp) + (k)] = local_qp_y;
		k = k + 1;
	}

	// Update ports indexes
	index_Qp += 64;
	write_end_Qp();

}
static i32 isSchedulable_read_CodingUnit_end_sendQp_blk64x64() {
	i32 result;
	u8 local_length;

	local_length = length;
	result = local_length == 8;
	return result;
}

static void read_CodingUnit_end_sendQp_blk64x64() {

	i32 k;
	i8 local_qp_y;

	k = 0;
	while (k <= 255) {
		local_qp_y = qp_y;
		tokens_Qp[(index_Qp + (k)) % SIZE_Qp] = local_qp_y;
		k = k + 1;
	}

	// Update ports indexes
	index_Qp += 256;
	write_end_Qp();

}
static void read_CodingUnit_end_sendQp_blk64x64_aligned() {

	i32 k;
	i8 local_qp_y;

	k = 0;
	while (k <= 255) {
		local_qp_y = qp_y;
		tokens_Qp[(index_Qp % SIZE_Qp) + (k)] = local_qp_y;
		k = k + 1;
	}

	// Update ports indexes
	index_Qp += 256;
	write_end_Qp();

}
static i32 isSchedulable_read_PredictionUnit_start() {
	i32 result;
	i32 tmp_isFifoFull;
	u8 local_pu_idx;

	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	local_pu_idx = pu_idx;
	result = tmp_isFifoFull && local_pu_idx == 1;
	return result;
}

static void read_PredictionUnit_start() {

	u32 res[1];
	u8 local_PRED_L0;
	u8 local_skip_flag;
	u16 local_MaxNumMergeCand;
	u32 tmp_res;
	u32 tmp_res0;
	u32 tmp_res1;
	u32 tmp_res2;
	u8 local_slice_type;
	u8 local_B_SLICE;
	u8 local_partMode;
	u8 local_pu_PbW;
	u8 local_pu_PbH;
	u8 local_cu_ctDepth;
	u32 tmp_res3;
	u8 local_inter_pred_idc;
	u8 local_PRED_L1;
	u8 local_num_ref_idx_l0_active;
	u32 tmp_res4;

	local_PRED_L0 = HevcDecoder_Algo_Parser_PRED_L0;
	inter_pred_idc = local_PRED_L0;
	mergeIdx = -1;
	mvp_lx[0] = -1;
	mvp_lx[1] = -1;
	ref_idx_lx[0] = -1;
	ref_idx_lx[1] = -1;
	mvd[0] = 0;
	mvd[1] = 0;
	mvd[2] = 0;
	mvd[3] = 0;
	mvd_x = 0;
	mvd_y = 0;
	local_skip_flag = skip_flag;
	if (local_skip_flag == 1) {
		local_MaxNumMergeCand = MaxNumMergeCand;
		if (local_MaxNumMergeCand > 1) {
			local_MaxNumMergeCand = MaxNumMergeCand;
			HevcDecoder_Algo_Parser_get_MERGE_IDX(codIRange, codIOffset, ctxTable, fifo, res, local_MaxNumMergeCand);
			tmp_res = res[0];
			mergeIdx = tmp_res;
		} else {
			mergeIdx = 0;
		}
		pu_idx = 7;
	} else {
		HevcDecoder_Algo_Parser_get_MERGE_FLAG(codIRange, codIOffset, ctxTable, fifo, res);
		tmp_res0 = res[0];
		merge_flag = tmp_res0;
		tmp_res1 = res[0];
		if (tmp_res1 == 1) {
			local_MaxNumMergeCand = MaxNumMergeCand;
			if (local_MaxNumMergeCand > 1) {
				local_MaxNumMergeCand = MaxNumMergeCand;
				HevcDecoder_Algo_Parser_get_MERGE_IDX(codIRange, codIOffset, ctxTable, fifo, res, local_MaxNumMergeCand);
				tmp_res2 = res[0];
				mergeIdx = tmp_res2;
			} else {
				mergeIdx = 0;
			}
			pu_idx = 7;
		} else {
			local_slice_type = slice_type;
			local_B_SLICE = HevcDecoder_Algo_Parser_B_SLICE;
			if (local_slice_type == local_B_SLICE) {
				local_partMode = partMode;
				local_pu_PbW = pu_PbW;
				local_pu_PbH = pu_PbH;
				local_cu_ctDepth = cu_ctDepth;
				HevcDecoder_Algo_Parser_get_INTER_PRED_IDC(codIRange, codIOffset, ctxTable, fifo, res, local_partMode, local_pu_PbW, local_pu_PbH, local_cu_ctDepth);
				tmp_res3 = res[0];
				inter_pred_idc = tmp_res3;
			}
			local_inter_pred_idc = inter_pred_idc;
			local_PRED_L1 = HevcDecoder_Algo_Parser_PRED_L1;
			if (local_inter_pred_idc != local_PRED_L1) {
				ref_idx_lx[0] = 0;
				local_num_ref_idx_l0_active = num_ref_idx_l0_active;
				if (local_num_ref_idx_l0_active > 1) {
					local_num_ref_idx_l0_active = num_ref_idx_l0_active;
					HevcDecoder_Algo_Parser_get_REF_IDX_LX(codIRange, codIOffset, ctxTable, fifo, res, local_num_ref_idx_l0_active - 1);
					tmp_res4 = res[0];
					ref_idx_lx[0] = tmp_res4;
				}
				pu_idx = 3;
			} else {
				pu_idx = 4;
			}
		}
	}

	// Update ports indexes

}
static i32 isSchedulable_read_PredictionUnit_retMVDcoding_goto1() {
	i32 result;
	u8 local_pu_idx;
	i32 tmp_isFifoFull;

	local_pu_idx = pu_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	result = local_pu_idx == 4 && tmp_isFifoFull;
	return result;
}

static void read_PredictionUnit_retMVDcoding_goto1() {

	u32 res[1];
	i32 local_mvd_x;
	i32 local_mvd_y;
	u8 local_inter_pred_idc;
	u8 local_PRED_L1;
	u32 tmp_res;
	u8 local_PRED_L0;
	u8 local_num_ref_idx_l1_active;
	u32 tmp_res0;
	u8 local_mvd_l1_zero_flag;
	u8 local_BI_PRED;

	local_mvd_x = mvd_x;
	mvd[0] = local_mvd_x;
	local_mvd_y = mvd_y;
	mvd[1] = local_mvd_y;
	mvd_x = 0;
	mvd_y = 0;
	local_inter_pred_idc = inter_pred_idc;
	local_PRED_L1 = HevcDecoder_Algo_Parser_PRED_L1;
	if (local_inter_pred_idc != local_PRED_L1) {
		HevcDecoder_Algo_Parser_get_MVP_LX_FLAG(codIRange, codIOffset, ctxTable, fifo, res);
		tmp_res = res[0];
		mvp_lx[0] = tmp_res;
	}
	pu_idx = 7;
	local_inter_pred_idc = inter_pred_idc;
	local_PRED_L0 = HevcDecoder_Algo_Parser_PRED_L0;
	if (local_inter_pred_idc != local_PRED_L0) {
		ref_idx_lx[1] = 0;
		local_num_ref_idx_l1_active = num_ref_idx_l1_active;
		if (local_num_ref_idx_l1_active > 1) {
			local_num_ref_idx_l1_active = num_ref_idx_l1_active;
			HevcDecoder_Algo_Parser_get_REF_IDX_LX(codIRange, codIOffset, ctxTable, fifo, res, local_num_ref_idx_l1_active - 1);
			tmp_res0 = res[0];
			ref_idx_lx[1] = tmp_res0;
		}
		local_mvd_l1_zero_flag = mvd_l1_zero_flag;
		local_inter_pred_idc = inter_pred_idc;
		local_BI_PRED = HevcDecoder_Algo_Parser_BI_PRED;
		if (local_mvd_l1_zero_flag == 1 && local_inter_pred_idc == local_BI_PRED) {
			pu_idx = 6;
		} else {
			pu_idx = 5;
		}
	}

	// Update ports indexes

}
static i32 isSchedulable_read_PredictionUnit_gotoMVDCoding() {
	i32 result;
	u8 local_pu_idx;

	local_pu_idx = pu_idx;
	local_pu_idx = pu_idx;
	result = local_pu_idx == 3 || local_pu_idx == 5;
	return result;
}

static void read_PredictionUnit_gotoMVDCoding() {

	u8 local_pu_idx;

	local_pu_idx = pu_idx;
	pu_idx = local_pu_idx + 1;

	// Update ports indexes

}
static i32 isSchedulable_read_PredictionUnit_retMVDcoding_goto2() {
	i32 result;
	u8 local_pu_idx;
	i32 tmp_isFifoFull;

	local_pu_idx = pu_idx;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	result = local_pu_idx == 6 && tmp_isFifoFull;
	return result;
}

static void read_PredictionUnit_retMVDcoding_goto2() {

	u32 res[1];
	i32 local_mvd_x;
	i32 local_mvd_y;
	u32 tmp_res;

	local_mvd_x = mvd_x;
	mvd[2] = local_mvd_x;
	local_mvd_y = mvd_y;
	mvd[3] = local_mvd_y;
	HevcDecoder_Algo_Parser_get_MVP_LX_FLAG(codIRange, codIOffset, ctxTable, fifo, res);
	tmp_res = res[0];
	mvp_lx[1] = tmp_res;
	pu_idx = 7;

	// Update ports indexes

}
static i32 isSchedulable_read_PredictionUnit_end_mergeIdx_Eq_min1() {
	i32 result;
	u8 local_pu_idx;
	i16 local_mergeIdx;

	local_pu_idx = pu_idx;
	local_mergeIdx = mergeIdx;
	result = local_pu_idx == 7 && local_mergeIdx == -1;
	return result;
}

static void read_PredictionUnit_end_mergeIdx_Eq_min1() {

	i16 local_mergeIdx;
	i16 tmp_mvp_lx;
	i16 tmp_mvp_lx0;
	i16 tmp_ref_idx_lx;
	i16 tmp_ref_idx_lx0;
	i16 tmp_mvd;
	i16 tmp_mvd0;
	i16 tmp_mvd1;
	i16 tmp_mvd2;

	local_mergeIdx = mergeIdx;
	tokens_MvPredSyntaxElem[(index_MvPredSyntaxElem + (0)) % SIZE_MvPredSyntaxElem] = local_mergeIdx;
	tmp_mvp_lx = mvp_lx[0];
	tokens_MvPredSyntaxElem[(index_MvPredSyntaxElem + (1)) % SIZE_MvPredSyntaxElem] = tmp_mvp_lx;
	tmp_mvp_lx0 = mvp_lx[1];
	tokens_MvPredSyntaxElem[(index_MvPredSyntaxElem + (2)) % SIZE_MvPredSyntaxElem] = tmp_mvp_lx0;
	tmp_ref_idx_lx = ref_idx_lx[0];
	tokens_MvPredSyntaxElem[(index_MvPredSyntaxElem + (3)) % SIZE_MvPredSyntaxElem] = tmp_ref_idx_lx;
	tmp_ref_idx_lx0 = ref_idx_lx[1];
	tokens_MvPredSyntaxElem[(index_MvPredSyntaxElem + (4)) % SIZE_MvPredSyntaxElem] = tmp_ref_idx_lx0;
	tmp_mvd = mvd[0];
	tokens_MvPredSyntaxElem[(index_MvPredSyntaxElem + (5)) % SIZE_MvPredSyntaxElem] = tmp_mvd;
	tmp_mvd0 = mvd[1];
	tokens_MvPredSyntaxElem[(index_MvPredSyntaxElem + (6)) % SIZE_MvPredSyntaxElem] = tmp_mvd0;
	tmp_mvd1 = mvd[2];
	tokens_MvPredSyntaxElem[(index_MvPredSyntaxElem + (7)) % SIZE_MvPredSyntaxElem] = tmp_mvd1;
	tmp_mvd2 = mvd[3];
	tokens_MvPredSyntaxElem[(index_MvPredSyntaxElem + (8)) % SIZE_MvPredSyntaxElem] = tmp_mvd2;

	// Update ports indexes
	index_MvPredSyntaxElem += 9;
	write_end_MvPredSyntaxElem();

}
static void read_PredictionUnit_end_mergeIdx_Eq_min1_aligned() {

	i16 local_mergeIdx;
	i16 tmp_mvp_lx;
	i16 tmp_mvp_lx0;
	i16 tmp_ref_idx_lx;
	i16 tmp_ref_idx_lx0;
	i16 tmp_mvd;
	i16 tmp_mvd0;
	i16 tmp_mvd1;
	i16 tmp_mvd2;

	local_mergeIdx = mergeIdx;
	tokens_MvPredSyntaxElem[(index_MvPredSyntaxElem % SIZE_MvPredSyntaxElem) + (0)] = local_mergeIdx;
	tmp_mvp_lx = mvp_lx[0];
	tokens_MvPredSyntaxElem[(index_MvPredSyntaxElem % SIZE_MvPredSyntaxElem) + (1)] = tmp_mvp_lx;
	tmp_mvp_lx0 = mvp_lx[1];
	tokens_MvPredSyntaxElem[(index_MvPredSyntaxElem % SIZE_MvPredSyntaxElem) + (2)] = tmp_mvp_lx0;
	tmp_ref_idx_lx = ref_idx_lx[0];
	tokens_MvPredSyntaxElem[(index_MvPredSyntaxElem % SIZE_MvPredSyntaxElem) + (3)] = tmp_ref_idx_lx;
	tmp_ref_idx_lx0 = ref_idx_lx[1];
	tokens_MvPredSyntaxElem[(index_MvPredSyntaxElem % SIZE_MvPredSyntaxElem) + (4)] = tmp_ref_idx_lx0;
	tmp_mvd = mvd[0];
	tokens_MvPredSyntaxElem[(index_MvPredSyntaxElem % SIZE_MvPredSyntaxElem) + (5)] = tmp_mvd;
	tmp_mvd0 = mvd[1];
	tokens_MvPredSyntaxElem[(index_MvPredSyntaxElem % SIZE_MvPredSyntaxElem) + (6)] = tmp_mvd0;
	tmp_mvd1 = mvd[2];
	tokens_MvPredSyntaxElem[(index_MvPredSyntaxElem % SIZE_MvPredSyntaxElem) + (7)] = tmp_mvd1;
	tmp_mvd2 = mvd[3];
	tokens_MvPredSyntaxElem[(index_MvPredSyntaxElem % SIZE_MvPredSyntaxElem) + (8)] = tmp_mvd2;

	// Update ports indexes
	index_MvPredSyntaxElem += 9;
	write_end_MvPredSyntaxElem();

}
static i32 isSchedulable_read_PredictionUnit_end_mergeIdx_notEq_min1() {
	i32 result;
	u8 local_pu_idx;
	i16 local_mergeIdx;

	local_pu_idx = pu_idx;
	local_mergeIdx = mergeIdx;
	result = local_pu_idx == 7 && local_mergeIdx != -1;
	return result;
}

static void read_PredictionUnit_end_mergeIdx_notEq_min1() {

	i16 local_mergeIdx;
	i16 tmp_mvd;
	i16 tmp_mvd0;
	i16 tmp_mvd1;
	i16 tmp_mvd2;

	local_mergeIdx = mergeIdx;
	tokens_MvPredSyntaxElem[(index_MvPredSyntaxElem + (0)) % SIZE_MvPredSyntaxElem] = local_mergeIdx;
	tmp_mvd = mvd[0];
	tokens_MvPredSyntaxElem[(index_MvPredSyntaxElem + (1)) % SIZE_MvPredSyntaxElem] = tmp_mvd;
	tmp_mvd0 = mvd[1];
	tokens_MvPredSyntaxElem[(index_MvPredSyntaxElem + (2)) % SIZE_MvPredSyntaxElem] = tmp_mvd0;
	tmp_mvd1 = mvd[2];
	tokens_MvPredSyntaxElem[(index_MvPredSyntaxElem + (3)) % SIZE_MvPredSyntaxElem] = tmp_mvd1;
	tmp_mvd2 = mvd[3];
	tokens_MvPredSyntaxElem[(index_MvPredSyntaxElem + (4)) % SIZE_MvPredSyntaxElem] = tmp_mvd2;

	// Update ports indexes
	index_MvPredSyntaxElem += 5;
	write_end_MvPredSyntaxElem();

}
static void read_PredictionUnit_end_mergeIdx_notEq_min1_aligned() {

	i16 local_mergeIdx;
	i16 tmp_mvd;
	i16 tmp_mvd0;
	i16 tmp_mvd1;
	i16 tmp_mvd2;

	local_mergeIdx = mergeIdx;
	tokens_MvPredSyntaxElem[(index_MvPredSyntaxElem % SIZE_MvPredSyntaxElem) + (0)] = local_mergeIdx;
	tmp_mvd = mvd[0];
	tokens_MvPredSyntaxElem[(index_MvPredSyntaxElem % SIZE_MvPredSyntaxElem) + (1)] = tmp_mvd;
	tmp_mvd0 = mvd[1];
	tokens_MvPredSyntaxElem[(index_MvPredSyntaxElem % SIZE_MvPredSyntaxElem) + (2)] = tmp_mvd0;
	tmp_mvd1 = mvd[2];
	tokens_MvPredSyntaxElem[(index_MvPredSyntaxElem % SIZE_MvPredSyntaxElem) + (3)] = tmp_mvd1;
	tmp_mvd2 = mvd[3];
	tokens_MvPredSyntaxElem[(index_MvPredSyntaxElem % SIZE_MvPredSyntaxElem) + (4)] = tmp_mvd2;

	// Update ports indexes
	index_MvPredSyntaxElem += 5;
	write_end_MvPredSyntaxElem();

}
static i32 isSchedulable_read_MVDCoding_start() {
	i32 result;
	i32 tmp_isFifoFull;

	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	result = tmp_isFifoFull;
	return result;
}

static void read_MVDCoding_start() {

	u32 res[1];
	u8 abs_mvd_greater0_flag_0;
	u8 abs_mvd_greater1_flag_0;
	i16 abs_mvd_minus2_0;
	u8 mvd_sign_flag_0;
	u32 tmp_res;
	u8 local_abs_mvd_greater0_flag_1;
	u32 tmp_res0;

	abs_mvd_minus2_0 = 0;
	mvd_sign_flag_0 = 0;
	HevcDecoder_Algo_Parser_get_ABS_MVD_GREATER0_FLAG(codIRange, codIOffset, ctxTable, fifo, res);
	abs_mvd_greater0_flag_0 = res[0];
	HevcDecoder_Algo_Parser_get_ABS_MVD_GREATER0_FLAG(codIRange, codIOffset, ctxTable, fifo, res);
	tmp_res = res[0];
	abs_mvd_greater0_flag_1 = tmp_res;
	if (abs_mvd_greater0_flag_0 == 1) {
		HevcDecoder_Algo_Parser_get_ABS_MVD_GREATER1_FLAG(codIRange, codIOffset, ctxTable, fifo, res);
		abs_mvd_greater1_flag_0 = res[0];
	}
	local_abs_mvd_greater0_flag_1 = abs_mvd_greater0_flag_1;
	if (local_abs_mvd_greater0_flag_1 == 1) {
		HevcDecoder_Algo_Parser_get_ABS_MVD_GREATER1_FLAG(codIRange, codIOffset, ctxTable, fifo, res);
		tmp_res0 = res[0];
		abs_mvd_greater1_flag_1 = tmp_res0;
	}
	if (abs_mvd_greater0_flag_0 == 1) {
		abs_mvd_minus2_0 = -1;
		if (abs_mvd_greater1_flag_0 == 1) {
			HevcDecoder_Algo_Parser_get_ABS_MVD_MINUS2(codIRange, codIOffset, fifo, res);
			abs_mvd_minus2_0 = res[0];
		}
		HevcDecoder_Algo_Parser_get_MVD_SIGN_FLAG(codIRange, codIOffset, fifo, res);
		mvd_sign_flag_0 = res[0];
	}
	mvd_x = abs_mvd_greater0_flag_0 * (abs_mvd_minus2_0 + 2) * (1 - (mvd_sign_flag_0 << 1));

	// Update ports indexes

}
static i32 isSchedulable_read_MVDCoding_ended() {
	i32 result;
	i32 tmp_isFifoFull;

	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	result = tmp_isFifoFull;
	return result;
}

static void read_MVDCoding_ended() {

	u32 res[1];
	i16 abs_mvd_minus2_1;
	u8 mvd_sign_flag_1;
	u8 local_abs_mvd_greater0_flag_1;
	u8 local_abs_mvd_greater1_flag_1;

	abs_mvd_minus2_1 = 0;
	mvd_sign_flag_1 = 0;
	local_abs_mvd_greater0_flag_1 = abs_mvd_greater0_flag_1;
	if (local_abs_mvd_greater0_flag_1 == 1) {
		abs_mvd_minus2_1 = -1;
		local_abs_mvd_greater1_flag_1 = abs_mvd_greater1_flag_1;
		if (local_abs_mvd_greater1_flag_1 == 1) {
			HevcDecoder_Algo_Parser_get_ABS_MVD_MINUS2(codIRange, codIOffset, fifo, res);
			abs_mvd_minus2_1 = res[0];
		}
		HevcDecoder_Algo_Parser_get_MVD_SIGN_FLAG(codIRange, codIOffset, fifo, res);
		mvd_sign_flag_1 = res[0];
	}
	local_abs_mvd_greater0_flag_1 = abs_mvd_greater0_flag_1;
	mvd_y = local_abs_mvd_greater0_flag_1 * (abs_mvd_minus2_1 + 2) * (1 - (mvd_sign_flag_1 << 1));

	// Update ports indexes

}
static i32 isSchedulable_read_PCMSample_start() {
	i32 result;

	result = 1;
	return result;
}

static void read_PCMSample_start() {

	u8 local_cu_log2CbSize;
	i32 cb_size;
	i32 length;
	i32 local_DEBUG_CABAC;
	u16 local_sps_id;
	u32 tmp_pcm_bit_depth;
	u32 tmp_pcm_bit_depth_chroma;

	local_cu_log2CbSize = cu_log2CbSize;
	cb_size = 1 << local_cu_log2CbSize;
	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
		printf("read_PCMSample\n");
	}
	local_sps_id = sps_id;
	tmp_pcm_bit_depth = pcm_bit_depth[local_sps_id];
	local_sps_id = sps_id;
	tmp_pcm_bit_depth_chroma = pcm_bit_depth_chroma[local_sps_id];
	length = cb_size * cb_size * tmp_pcm_bit_depth + ((cb_size * cb_size) >> 1) * tmp_pcm_bit_depth_chroma;
	pcm_skip_length = (length + 7) >> 3;
	cnt_i = 0;

	// Update ports indexes

}
static i32 isSchedulable_read_PCMSample_skipLoop() {
	i32 result;
	u32 local_cnt_i;
	i32 local_pcm_skip_length;
	i32 tmp_isFifoFull;

	local_cnt_i = cnt_i;
	local_pcm_skip_length = pcm_skip_length;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	result = local_cnt_i < local_pcm_skip_length && tmp_isFifoFull;
	return result;
}

static void read_PCMSample_skipLoop() {

	u32 local_cnt_i;

	HevcDecoder_Algo_Parser_flushBits(8, fifo);
	local_cnt_i = cnt_i;
	cnt_i = local_cnt_i + 1;

	// Update ports indexes

}
static i32 isSchedulable_read_PCMSample_skipLoop_end() {
	i32 result;
	u32 local_cnt_i;
	i32 local_pcm_skip_length;
	i32 tmp_isFifoFull;

	local_cnt_i = cnt_i;
	local_pcm_skip_length = pcm_skip_length;
	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	result = local_cnt_i == local_pcm_skip_length && tmp_isFifoFull;
	return result;
}

static void read_PCMSample_skipLoop_end() {

	i32 i;
	u8 local_cu_log2CbSize;
	u16 local_sps_id;
	u32 tmp_pcm_bit_depth;
	i32 i0;
	u32 tmp_pcm_bit_depth_chroma;
	u32 tmp_pcm_loop_filter_disable_flag;
	u16 local_cu_x0;
	u16 local_cu_y0;

	cnt_i = 0;
	HevcDecoder_Algo_Parser_decodeReInit(codIRange, codIOffset, fifo);
	i = 0;
	local_cu_log2CbSize = cu_log2CbSize;
	while (i <= 1 << local_cu_log2CbSize) {
		local_sps_id = sps_id;
		tmp_pcm_bit_depth = pcm_bit_depth[local_sps_id];
		pcm_sample_luma[i] = tmp_pcm_bit_depth;
		i = i + 1;
	}
	i0 = 0;
	local_cu_log2CbSize = cu_log2CbSize;
	while (i0 <= 1 << (local_cu_log2CbSize << 1)) {
		local_sps_id = sps_id;
		tmp_pcm_bit_depth_chroma = pcm_bit_depth_chroma[local_sps_id];
		pcm_sample_chroma[i0] = tmp_pcm_bit_depth_chroma;
		i0 = i0 + 1;
	}
	local_sps_id = sps_id;
	tmp_pcm_loop_filter_disable_flag = pcm_loop_filter_disable_flag[local_sps_id];
	if (tmp_pcm_loop_filter_disable_flag != 0) {
		local_cu_x0 = cu_x0;
		local_cu_y0 = cu_y0;
		local_cu_log2CbSize = cu_log2CbSize;
		set_deblocking_bypass(local_cu_x0, local_cu_y0, local_cu_log2CbSize);
	}

	// Update ports indexes

}
static i32 isSchedulable_read_TransformTree_start() {
	i32 result;
	i32 tmp_isFifoFull;
	u8 local_ttStack_idx;
	u8 local_TT_idx;
	u16 tmp_ttStack;

	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	local_ttStack_idx = ttStack_idx;
	local_TT_idx = HevcDecoder_Algo_Parser_TT_idx;
	tmp_ttStack = ttStack[local_ttStack_idx][local_TT_idx];
	result = tmp_isFifoFull && tmp_ttStack == 1;
	return result;
}

static void read_TransformTree_start() {

	u8 local_ttStack_idx;
	u16 local_TT_x0;
	u16 x0;
	u16 local_TT_y0;
	u16 y0;
	u16 local_TT_xBase;
	u16 xBase;
	u16 local_TT_yBase;
	u16 yBase;
	u8 local_TT_log2TrafoSize;
	u8 log2TrafoSize;
	u8 local_TT_trafoDepth;
	u8 trafoDepth;
	u16 cbf_x0;
	u16 cbf_y0;
	u32 res[1];
	u8 local_predMode;
	u8 local_INTRA;
	u8 local_partMode;
	u8 local_PART_NxN;
	u8 IntraSplitFlag;
	u16 local_sps_id;
	u8 tmp_sps_max_transform_hierarchy_depth_inter;
	u8 local_INTER;
	u8 local_PART_2Nx2N;
	u8 InterSplitFlag;
	i32 local_DEBUG_CABAC;
	i32 local_DEBUG_TRACE1;
	u8 local_TT_blkIdx;
	u16 tmp_ttStack;
	u16 tmp_ttStack0;
	u8 tmp_intra_pred_mode;
	u8 tmp_intra_pred_mode0;
	u8 local_Log2MaxTrafoSize;
	u8 local_Log2MinTrafoSize;
	u8 local_MaxTrafoDepth;
	u32 tmp_res;
	u32 tmp_res0;
	u32 tmp_res1;
	u16 local_cbf_xBase;
	u16 local_cbf_yBase;
	u8 tmp_cbf_cb;
	u32 tmp_res2;
	u8 tmp_cbf_cr;
	u32 tmp_res3;
	u8 tmp_cbf_cb0;
	u8 tmp_cbf_cr0;
	u8 local_split_transform_flag;
	u16 local_TT_x1;
	u16 local_TT_y1;
	u8 local_TT_idx;
	u8 tmp_cbf_cb1;
	u8 tmp_cbf_cr1;
	u32 tmp_res4;
	u16 tmp_ttStack1;

	local_ttStack_idx = ttStack_idx;
	local_TT_x0 = HevcDecoder_Algo_Parser_TT_x0;
	x0 = ttStack[local_ttStack_idx][local_TT_x0];
	local_ttStack_idx = ttStack_idx;
	local_TT_y0 = HevcDecoder_Algo_Parser_TT_y0;
	y0 = ttStack[local_ttStack_idx][local_TT_y0];
	local_ttStack_idx = ttStack_idx;
	local_TT_xBase = HevcDecoder_Algo_Parser_TT_xBase;
	xBase = ttStack[local_ttStack_idx][local_TT_xBase];
	local_ttStack_idx = ttStack_idx;
	local_TT_yBase = HevcDecoder_Algo_Parser_TT_yBase;
	yBase = ttStack[local_ttStack_idx][local_TT_yBase];
	local_ttStack_idx = ttStack_idx;
	local_TT_log2TrafoSize = HevcDecoder_Algo_Parser_TT_log2TrafoSize;
	log2TrafoSize = ttStack[local_ttStack_idx][local_TT_log2TrafoSize];
	local_ttStack_idx = ttStack_idx;
	local_TT_trafoDepth = HevcDecoder_Algo_Parser_TT_trafoDepth;
	trafoDepth = ttStack[local_ttStack_idx][local_TT_trafoDepth];
	cbf_x0 = x0 & (1 << log2TrafoSize) - 1;
	cbf_y0 = y0 & (1 << log2TrafoSize) - 1;
	res[0] = 0;
	local_predMode = predMode;
	local_INTRA = HevcDecoder_Algo_Parser_INTRA;
	local_partMode = partMode;
	local_PART_NxN = HevcDecoder_Algo_Parser_PART_NxN;
	if (local_predMode == local_INTRA && local_partMode == local_PART_NxN) {
		IntraSplitFlag = 1;
	} else {
		IntraSplitFlag = 0;
	}
	local_sps_id = sps_id;
	tmp_sps_max_transform_hierarchy_depth_inter = sps_max_transform_hierarchy_depth_inter[local_sps_id];
	local_predMode = predMode;
	local_INTER = HevcDecoder_Algo_Parser_INTER;
	local_partMode = partMode;
	local_PART_2Nx2N = HevcDecoder_Algo_Parser_PART_2Nx2N;
	if (tmp_sps_max_transform_hierarchy_depth_inter == 0 && local_predMode == local_INTER && local_partMode != local_PART_2Nx2N && trafoDepth == 0) {
		InterSplitFlag = 1;
	} else {
		InterSplitFlag = 0;
	}
	cbf_xBase = xBase & (1 << log2TrafoSize) - 1;
	cbf_yBase = yBase & (1 << log2TrafoSize) - 1;
	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	local_DEBUG_TRACE1 = HevcDecoder_Algo_Parser_DEBUG_TRACE1;
	if (local_DEBUG_CABAC && local_DEBUG_TRACE1) {
		local_ttStack_idx = ttStack_idx;
		local_TT_blkIdx = HevcDecoder_Algo_Parser_TT_blkIdx;
		tmp_ttStack = ttStack[local_ttStack_idx][local_TT_blkIdx];
		printf("read_TransformTree.start(%u, %u, %u, %u, %u, %u, %u)\n", x0, y0, xBase, yBase, log2TrafoSize, trafoDepth, tmp_ttStack);
	} else {
		local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
		if (local_DEBUG_CABAC) {
			printf("read_TransformTree.start\n");
		}
	}
	if (IntraSplitFlag == 1) {
		if (trafoDepth == 1) {
			local_ttStack_idx = ttStack_idx;
			local_TT_blkIdx = HevcDecoder_Algo_Parser_TT_blkIdx;
			tmp_ttStack0 = ttStack[local_ttStack_idx][local_TT_blkIdx];
			tmp_intra_pred_mode = intra_pred_mode[tmp_ttStack0];
			cur_intra_pred_mode = tmp_intra_pred_mode;
		}
	} else {
		tmp_intra_pred_mode0 = intra_pred_mode[0];
		cur_intra_pred_mode = tmp_intra_pred_mode0;
	}
	split_transform_flag = 0;
	local_Log2MaxTrafoSize = Log2MaxTrafoSize;
	local_Log2MinTrafoSize = Log2MinTrafoSize;
	local_MaxTrafoDepth = MaxTrafoDepth;
	if (log2TrafoSize <= local_Log2MaxTrafoSize && log2TrafoSize > local_Log2MinTrafoSize && trafoDepth < local_MaxTrafoDepth && !(IntraSplitFlag == 1 && trafoDepth == 0)) {
		HevcDecoder_Algo_Parser_get_SPLIT_TRANSFORM_FLAG(codIRange, codIOffset, ctxTable, fifo, res, log2TrafoSize);
		tmp_res = res[0];
		split_transform_flag = tmp_res;
	} else {
		local_Log2MaxTrafoSize = Log2MaxTrafoSize;
		if (log2TrafoSize > local_Log2MaxTrafoSize || IntraSplitFlag == 1 && trafoDepth == 0 || InterSplitFlag == 1) {
			split_transform_flag = 1;
		}
	}
	cbf_cb[cbf_x0][cbf_y0][trafoDepth] = 0;
	cbf_cr[cbf_x0][cbf_y0][trafoDepth] = 0;
	if (trafoDepth == 0 || log2TrafoSize > 2) {
		if (trafoDepth == 0) {
			HevcDecoder_Algo_Parser_get_CBF_CB_CR(codIRange, codIOffset, ctxTable, fifo, res, trafoDepth);
			tmp_res0 = res[0];
			cbf_cb[cbf_x0][cbf_y0][trafoDepth] = tmp_res0;
			HevcDecoder_Algo_Parser_get_CBF_CB_CR(codIRange, codIOffset, ctxTable, fifo, res, trafoDepth);
			tmp_res1 = res[0];
			cbf_cr[cbf_x0][cbf_y0][trafoDepth] = tmp_res1;
		} else {
			local_cbf_xBase = cbf_xBase;
			local_cbf_yBase = cbf_yBase;
			tmp_cbf_cb = cbf_cb[local_cbf_xBase][local_cbf_yBase][trafoDepth - 1];
			if (tmp_cbf_cb == 1) {
				HevcDecoder_Algo_Parser_get_CBF_CB_CR(codIRange, codIOffset, ctxTable, fifo, res, trafoDepth);
				tmp_res2 = res[0];
				cbf_cb[cbf_x0][cbf_y0][trafoDepth] = tmp_res2;
			}
			local_cbf_xBase = cbf_xBase;
			local_cbf_yBase = cbf_yBase;
			tmp_cbf_cr = cbf_cr[local_cbf_xBase][local_cbf_yBase][trafoDepth - 1];
			if (tmp_cbf_cr == 1) {
				HevcDecoder_Algo_Parser_get_CBF_CB_CR(codIRange, codIOffset, ctxTable, fifo, res, trafoDepth);
				tmp_res3 = res[0];
				cbf_cr[cbf_x0][cbf_y0][trafoDepth] = tmp_res3;
			}
		}
	}
	if (trafoDepth > 0 && log2TrafoSize == 2) {
		local_cbf_xBase = cbf_xBase;
		local_cbf_yBase = cbf_yBase;
		tmp_cbf_cb0 = cbf_cb[local_cbf_xBase][local_cbf_yBase][trafoDepth - 1];
		cbf_cb[cbf_x0][cbf_y0][trafoDepth] = tmp_cbf_cb0;
		local_cbf_xBase = cbf_xBase;
		local_cbf_yBase = cbf_yBase;
		tmp_cbf_cr0 = cbf_cr[local_cbf_xBase][local_cbf_yBase][trafoDepth - 1];
		cbf_cr[cbf_x0][cbf_y0][trafoDepth] = tmp_cbf_cr0;
	}
	local_split_transform_flag = split_transform_flag;
	if (local_split_transform_flag == 1) {
		local_ttStack_idx = ttStack_idx;
		local_TT_x1 = HevcDecoder_Algo_Parser_TT_x1;
		ttStack[local_ttStack_idx][local_TT_x1] = x0 + ((1 << log2TrafoSize) >> 1);
		local_ttStack_idx = ttStack_idx;
		local_TT_y1 = HevcDecoder_Algo_Parser_TT_y1;
		ttStack[local_ttStack_idx][local_TT_y1] = y0 + ((1 << log2TrafoSize) >> 1);
		local_ttStack_idx = ttStack_idx;
		local_TT_idx = HevcDecoder_Algo_Parser_TT_idx;
		ttStack[local_ttStack_idx][local_TT_idx] = 3;
	} else {
		cbf_luma = 1;
		local_predMode = predMode;
		local_INTRA = HevcDecoder_Algo_Parser_INTRA;
		tmp_cbf_cb1 = cbf_cb[cbf_x0][cbf_y0][trafoDepth];
		tmp_cbf_cr1 = cbf_cr[cbf_x0][cbf_y0][trafoDepth];
		if (local_predMode == local_INTRA || trafoDepth != 0 || tmp_cbf_cb1 == 1 || tmp_cbf_cr1 == 1) {
			HevcDecoder_Algo_Parser_get_CBF_LUMA(codIRange, codIOffset, ctxTable, fifo, res, trafoDepth);
			tmp_res4 = res[0];
			cbf_luma = tmp_res4;
		}
		local_ttStack_idx = ttStack_idx;
		local_TT_idx = HevcDecoder_Algo_Parser_TT_idx;
		ttStack[local_ttStack_idx][local_TT_idx] = 2;
	}
	local_partMode = partMode;
	local_PART_NxN = HevcDecoder_Algo_Parser_PART_NxN;
	local_ttStack_idx = ttStack_idx;
	local_TT_trafoDepth = HevcDecoder_Algo_Parser_TT_trafoDepth;
	tmp_ttStack1 = ttStack[local_ttStack_idx][local_TT_trafoDepth];
	if (!(local_partMode == local_PART_NxN && tmp_ttStack1 == 0)) {
		local_ttStack_idx = ttStack_idx;
		local_TT_idx = HevcDecoder_Algo_Parser_TT_idx;
		ttStack[local_ttStack_idx][local_TT_idx] = 10;
	}

	// Update ports indexes

}
static i32 isSchedulable_read_TransformTree_start_nonPartNxN() {
	i32 result;
	u8 local_ttStack_idx;
	u8 local_TT_idx;
	u16 tmp_ttStack;

	local_ttStack_idx = ttStack_idx;
	local_TT_idx = HevcDecoder_Algo_Parser_TT_idx;
	tmp_ttStack = ttStack[local_ttStack_idx][local_TT_idx];
	result = tmp_ttStack == 10;
	return result;
}

static void read_TransformTree_start_nonPartNxN() {

	u8 local_ttStack_idx;
	u8 local_TT_idx;
	u8 local_split_transform_flag;

	local_ttStack_idx = ttStack_idx;
	local_TT_idx = HevcDecoder_Algo_Parser_TT_idx;
	local_split_transform_flag = split_transform_flag;
	ttStack[local_ttStack_idx][local_TT_idx] = 2 + local_split_transform_flag;
	local_split_transform_flag = split_transform_flag;
	tokens_SplitTransform[(index_SplitTransform + (0)) % SIZE_SplitTransform] = local_split_transform_flag != 0;

	// Update ports indexes
	index_SplitTransform += 1;

}
static i32 isSchedulable_read_TransformTree_gotoTransformUnit() {
	i32 result;
	u8 local_ttStack_idx;
	u8 local_TT_idx;
	u16 tmp_ttStack;

	local_ttStack_idx = ttStack_idx;
	local_TT_idx = HevcDecoder_Algo_Parser_TT_idx;
	tmp_ttStack = ttStack[local_ttStack_idx][local_TT_idx];
	result = tmp_ttStack == 2;
	return result;
}

static void read_TransformTree_gotoTransformUnit() {

	u8 local_ttStack_idx;
	u8 local_TT_idx;
	u16 local_TT_x0;
	u16 tmp_ttStack;
	u16 local_TT_y0;
	u16 tmp_ttStack0;
	u16 local_TT_xBase;
	u16 tmp_ttStack1;
	u16 local_TT_yBase;
	u16 tmp_ttStack2;
	u8 local_TT_log2TrafoSize;
	u16 tmp_ttStack3;
	u8 local_TT_trafoDepth;
	u16 tmp_ttStack4;
	u8 local_TT_blkIdx;
	u16 tmp_ttStack5;
	u8 local_cbf_luma;

	local_ttStack_idx = ttStack_idx;
	local_TT_idx = HevcDecoder_Algo_Parser_TT_idx;
	ttStack[local_ttStack_idx][local_TT_idx] = 7;
	tu_idx = 1;
	local_ttStack_idx = ttStack_idx;
	local_TT_x0 = HevcDecoder_Algo_Parser_TT_x0;
	tmp_ttStack = ttStack[local_ttStack_idx][local_TT_x0];
	tu_x0 = tmp_ttStack;
	local_ttStack_idx = ttStack_idx;
	local_TT_y0 = HevcDecoder_Algo_Parser_TT_y0;
	tmp_ttStack0 = ttStack[local_ttStack_idx][local_TT_y0];
	tu_y0 = tmp_ttStack0;
	local_ttStack_idx = ttStack_idx;
	local_TT_xBase = HevcDecoder_Algo_Parser_TT_xBase;
	tmp_ttStack1 = ttStack[local_ttStack_idx][local_TT_xBase];
	tu_xBase = tmp_ttStack1;
	local_ttStack_idx = ttStack_idx;
	local_TT_yBase = HevcDecoder_Algo_Parser_TT_yBase;
	tmp_ttStack2 = ttStack[local_ttStack_idx][local_TT_yBase];
	tu_yBase = tmp_ttStack2;
	local_ttStack_idx = ttStack_idx;
	local_TT_log2TrafoSize = HevcDecoder_Algo_Parser_TT_log2TrafoSize;
	tmp_ttStack3 = ttStack[local_ttStack_idx][local_TT_log2TrafoSize];
	tu_log2TrafoSize = tmp_ttStack3;
	local_ttStack_idx = ttStack_idx;
	local_TT_trafoDepth = HevcDecoder_Algo_Parser_TT_trafoDepth;
	tmp_ttStack4 = ttStack[local_ttStack_idx][local_TT_trafoDepth];
	tu_trafoDepth = tmp_ttStack4;
	local_ttStack_idx = ttStack_idx;
	local_TT_blkIdx = HevcDecoder_Algo_Parser_TT_blkIdx;
	tmp_ttStack5 = ttStack[local_ttStack_idx][local_TT_blkIdx];
	tu_blkIdx = tmp_ttStack5;
	local_cbf_luma = cbf_luma;
	tokens_Cbf[(index_Cbf + (0)) % SIZE_Cbf] = local_cbf_luma == 1;

	// Update ports indexes
	index_Cbf += 1;

}
static i32 isSchedulable_read_TransformTree_gotoTransformTree() {
	i32 result;
	u8 local_ttStack_idx;
	u8 local_TT_idx;
	u16 tmp_ttStack;
	u16 tmp_ttStack0;
	u16 tmp_ttStack1;
	u16 tmp_ttStack2;

	local_ttStack_idx = ttStack_idx;
	local_TT_idx = HevcDecoder_Algo_Parser_TT_idx;
	tmp_ttStack = ttStack[local_ttStack_idx][local_TT_idx];
	local_ttStack_idx = ttStack_idx;
	local_TT_idx = HevcDecoder_Algo_Parser_TT_idx;
	tmp_ttStack0 = ttStack[local_ttStack_idx][local_TT_idx];
	local_ttStack_idx = ttStack_idx;
	local_TT_idx = HevcDecoder_Algo_Parser_TT_idx;
	tmp_ttStack1 = ttStack[local_ttStack_idx][local_TT_idx];
	local_ttStack_idx = ttStack_idx;
	local_TT_idx = HevcDecoder_Algo_Parser_TT_idx;
	tmp_ttStack2 = ttStack[local_ttStack_idx][local_TT_idx];
	result = tmp_ttStack == 3 || tmp_ttStack0 == 4 || tmp_ttStack1 == 5 || tmp_ttStack2 == 6;
	return result;
}

static void read_TransformTree_gotoTransformTree() {

	u8 local_ttStack_idx;
	u8 idx;
	u8 local_TT_idx;
	u16 tmp_ttStack;
	u16 local_TT_x0;
	u16 tmp_ttStack0;
	u16 local_TT_y0;
	u16 tmp_ttStack1;
	u16 local_TT_xBase;
	u16 tmp_ttStack2;
	u16 local_TT_yBase;
	u16 tmp_ttStack3;
	u8 local_TT_log2TrafoSize;
	u16 tmp_ttStack4;
	u8 local_TT_trafoDepth;
	u16 tmp_ttStack5;
	u16 tmp_ttStack6;
	u8 local_TT_blkIdx;
	u16 tmp_ttStack7;
	u16 local_TT_x1;
	u16 tmp_ttStack8;
	u16 tmp_ttStack9;
	u16 local_TT_y1;
	u16 tmp_ttStack10;
	u16 tmp_ttStack11;
	u16 tmp_ttStack12;

	local_ttStack_idx = ttStack_idx;
	idx = local_ttStack_idx;
	local_ttStack_idx = ttStack_idx;
	local_TT_idx = HevcDecoder_Algo_Parser_TT_idx;
	local_ttStack_idx = ttStack_idx;
	local_TT_idx = HevcDecoder_Algo_Parser_TT_idx;
	tmp_ttStack = ttStack[local_ttStack_idx][local_TT_idx];
	ttStack[local_ttStack_idx][local_TT_idx] = tmp_ttStack + 1;
	local_ttStack_idx = ttStack_idx;
	ttStack_idx = local_ttStack_idx + 1;
	local_ttStack_idx = ttStack_idx;
	local_TT_idx = HevcDecoder_Algo_Parser_TT_idx;
	ttStack[local_ttStack_idx][local_TT_idx] = 1;
	local_ttStack_idx = ttStack_idx;
	local_TT_x0 = HevcDecoder_Algo_Parser_TT_x0;
	local_TT_x0 = HevcDecoder_Algo_Parser_TT_x0;
	tmp_ttStack0 = ttStack[idx][local_TT_x0];
	ttStack[local_ttStack_idx][local_TT_x0] = tmp_ttStack0;
	local_ttStack_idx = ttStack_idx;
	local_TT_y0 = HevcDecoder_Algo_Parser_TT_y0;
	local_TT_y0 = HevcDecoder_Algo_Parser_TT_y0;
	tmp_ttStack1 = ttStack[idx][local_TT_y0];
	ttStack[local_ttStack_idx][local_TT_y0] = tmp_ttStack1;
	local_ttStack_idx = ttStack_idx;
	local_TT_xBase = HevcDecoder_Algo_Parser_TT_xBase;
	local_TT_x0 = HevcDecoder_Algo_Parser_TT_x0;
	tmp_ttStack2 = ttStack[idx][local_TT_x0];
	ttStack[local_ttStack_idx][local_TT_xBase] = tmp_ttStack2;
	local_ttStack_idx = ttStack_idx;
	local_TT_yBase = HevcDecoder_Algo_Parser_TT_yBase;
	local_TT_y0 = HevcDecoder_Algo_Parser_TT_y0;
	tmp_ttStack3 = ttStack[idx][local_TT_y0];
	ttStack[local_ttStack_idx][local_TT_yBase] = tmp_ttStack3;
	local_ttStack_idx = ttStack_idx;
	local_TT_log2TrafoSize = HevcDecoder_Algo_Parser_TT_log2TrafoSize;
	local_TT_log2TrafoSize = HevcDecoder_Algo_Parser_TT_log2TrafoSize;
	tmp_ttStack4 = ttStack[idx][local_TT_log2TrafoSize];
	ttStack[local_ttStack_idx][local_TT_log2TrafoSize] = tmp_ttStack4 - 1;
	local_ttStack_idx = ttStack_idx;
	local_TT_trafoDepth = HevcDecoder_Algo_Parser_TT_trafoDepth;
	local_TT_trafoDepth = HevcDecoder_Algo_Parser_TT_trafoDepth;
	tmp_ttStack5 = ttStack[idx][local_TT_trafoDepth];
	ttStack[local_ttStack_idx][local_TT_trafoDepth] = tmp_ttStack5 + 1;
	local_TT_idx = HevcDecoder_Algo_Parser_TT_idx;
	tmp_ttStack6 = ttStack[idx][local_TT_idx];
	if (tmp_ttStack6 == 4) {
		local_ttStack_idx = ttStack_idx;
		local_TT_blkIdx = HevcDecoder_Algo_Parser_TT_blkIdx;
		ttStack[local_ttStack_idx][local_TT_blkIdx] = 0;
	} else {
		local_TT_idx = HevcDecoder_Algo_Parser_TT_idx;
		tmp_ttStack7 = ttStack[idx][local_TT_idx];
		if (tmp_ttStack7 == 5) {
			local_ttStack_idx = ttStack_idx;
			local_TT_x0 = HevcDecoder_Algo_Parser_TT_x0;
			local_TT_x1 = HevcDecoder_Algo_Parser_TT_x1;
			tmp_ttStack8 = ttStack[idx][local_TT_x1];
			ttStack[local_ttStack_idx][local_TT_x0] = tmp_ttStack8;
			local_ttStack_idx = ttStack_idx;
			local_TT_blkIdx = HevcDecoder_Algo_Parser_TT_blkIdx;
			ttStack[local_ttStack_idx][local_TT_blkIdx] = 1;
		} else {
			local_TT_idx = HevcDecoder_Algo_Parser_TT_idx;
			tmp_ttStack9 = ttStack[idx][local_TT_idx];
			if (tmp_ttStack9 == 6) {
				local_ttStack_idx = ttStack_idx;
				local_TT_y0 = HevcDecoder_Algo_Parser_TT_y0;
				local_TT_y1 = HevcDecoder_Algo_Parser_TT_y1;
				tmp_ttStack10 = ttStack[idx][local_TT_y1];
				ttStack[local_ttStack_idx][local_TT_y0] = tmp_ttStack10;
				local_ttStack_idx = ttStack_idx;
				local_TT_blkIdx = HevcDecoder_Algo_Parser_TT_blkIdx;
				ttStack[local_ttStack_idx][local_TT_blkIdx] = 2;
			} else {
				local_ttStack_idx = ttStack_idx;
				local_TT_x0 = HevcDecoder_Algo_Parser_TT_x0;
				local_TT_x1 = HevcDecoder_Algo_Parser_TT_x1;
				tmp_ttStack11 = ttStack[idx][local_TT_x1];
				ttStack[local_ttStack_idx][local_TT_x0] = tmp_ttStack11;
				local_ttStack_idx = ttStack_idx;
				local_TT_y0 = HevcDecoder_Algo_Parser_TT_y0;
				local_TT_y1 = HevcDecoder_Algo_Parser_TT_y1;
				tmp_ttStack12 = ttStack[idx][local_TT_y1];
				ttStack[local_ttStack_idx][local_TT_y0] = tmp_ttStack12;
				local_ttStack_idx = ttStack_idx;
				local_TT_blkIdx = HevcDecoder_Algo_Parser_TT_blkIdx;
				ttStack[local_ttStack_idx][local_TT_blkIdx] = 3;
			}
		}
	}

	// Update ports indexes

}
static i32 isSchedulable_read_TransformTree_end() {
	i32 result;
	u8 local_ttStack_idx;
	u8 local_TT_idx;
	u16 tmp_ttStack;

	local_ttStack_idx = ttStack_idx;
	local_TT_idx = HevcDecoder_Algo_Parser_TT_idx;
	tmp_ttStack = ttStack[local_ttStack_idx][local_TT_idx];
	local_ttStack_idx = ttStack_idx;
	result = tmp_ttStack == 7 && local_ttStack_idx == 0;
	return result;
}

static void read_TransformTree_end() {



	// Update ports indexes

}
static i32 isSchedulable_read_TransformTree_endCall() {
	i32 result;
	u8 local_ttStack_idx;
	u8 local_TT_idx;
	u16 tmp_ttStack;

	local_ttStack_idx = ttStack_idx;
	local_TT_idx = HevcDecoder_Algo_Parser_TT_idx;
	tmp_ttStack = ttStack[local_ttStack_idx][local_TT_idx];
	local_ttStack_idx = ttStack_idx;
	result = tmp_ttStack == 7 && local_ttStack_idx != 0;
	return result;
}

static void read_TransformTree_endCall() {

	u8 local_ttStack_idx;

	local_ttStack_idx = ttStack_idx;
	ttStack_idx = local_ttStack_idx - 1;

	// Update ports indexes

}
static i32 isSchedulable_read_TransformUnit_start() {
	i32 result;
	i32 tmp_isFifoFull;
	u8 local_tu_idx;

	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	local_tu_idx = tu_idx;
	result = tmp_isFifoFull && local_tu_idx == 1;
	return result;
}

static void read_TransformUnit_start() {

	u32 res[1];
	u16 local_cu_x0;
	u8 local_tu_log2TrafoSize;
	u16 cbf_x0;
	u16 local_cu_y0;
	u16 cbf_y0;
	i32 local_DEBUG_CABAC;
	i32 local_DEBUG_TRACE1;
	u16 local_tu_x0;
	u16 local_tu_y0;
	u16 local_tu_xBase;
	u16 local_tu_yBase;
	u8 local_tu_trafoDepth;
	u8 local_tu_blkIdx;
	u8 local_cbf_luma;
	u8 tmp_cbf_cb;
	u8 tmp_cbf_cr;
	u16 local_pps_id;
	u8 tmp_pps_cu_qp_delta_enabled_flag;
	u8 local_IsCuQpDeltaCoded;
	u32 tmp_res;
	i16 local_CuQpDelta;
	u32 tmp_res0;
	u8 local_predMode;
	u8 local_cur_intra_pred_mode;
	u8 tmp_getScanIdx;
	u8 local_TEXT_LUMA;

	res[0] = 0;
	local_cu_x0 = cu_x0;
	local_tu_log2TrafoSize = tu_log2TrafoSize;
	cbf_x0 = local_cu_x0 & (1 << local_tu_log2TrafoSize) - 1;
	local_cu_y0 = cu_y0;
	local_tu_log2TrafoSize = tu_log2TrafoSize;
	cbf_y0 = local_cu_y0 & (1 << local_tu_log2TrafoSize) - 1;
	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	local_DEBUG_TRACE1 = HevcDecoder_Algo_Parser_DEBUG_TRACE1;
	if (local_DEBUG_CABAC && local_DEBUG_TRACE1) {
		local_tu_x0 = tu_x0;
		local_tu_y0 = tu_y0;
		local_tu_xBase = tu_xBase;
		local_tu_yBase = tu_yBase;
		local_tu_log2TrafoSize = tu_log2TrafoSize;
		local_tu_log2TrafoSize = tu_log2TrafoSize;
		local_tu_trafoDepth = tu_trafoDepth;
		local_tu_blkIdx = tu_blkIdx;
		printf("read_TransformUnit.start(%u, %u, %u, %u, %u, %u, %u, %u)\n", local_tu_x0, local_tu_y0, local_tu_xBase, local_tu_yBase, local_tu_log2TrafoSize, local_tu_log2TrafoSize, local_tu_trafoDepth, local_tu_blkIdx);
	} else {
		local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
		if (local_DEBUG_CABAC) {
			printf("read_TransformUnit.start\n");
		}
	}
	local_cbf_luma = cbf_luma;
	local_tu_trafoDepth = tu_trafoDepth;
	tmp_cbf_cb = cbf_cb[cbf_x0][cbf_y0][local_tu_trafoDepth];
	local_tu_trafoDepth = tu_trafoDepth;
	tmp_cbf_cr = cbf_cr[cbf_x0][cbf_y0][local_tu_trafoDepth];
	if (local_cbf_luma != 0 || tmp_cbf_cb != 0 || tmp_cbf_cr != 0) {
		local_pps_id = pps_id;
		tmp_pps_cu_qp_delta_enabled_flag = pps_cu_qp_delta_enabled_flag[local_pps_id];
		local_IsCuQpDeltaCoded = IsCuQpDeltaCoded;
		if (tmp_pps_cu_qp_delta_enabled_flag != 0 && local_IsCuQpDeltaCoded == 0) {
			HevcDecoder_Algo_Parser_get_CU_QP_DELTA_ABS(codIRange, codIOffset, ctxTable, fifo, res);
			tmp_res = res[0];
			CuQpDelta = tmp_res;
			local_CuQpDelta = CuQpDelta;
			if (local_CuQpDelta != 0) {
				HevcDecoder_Algo_Parser_get_CU_QP_DELTA_SIGN_FLAG(codIRange, codIOffset, fifo, res);
				tmp_res0 = res[0];
				if (tmp_res0 == 1) {
					local_CuQpDelta = CuQpDelta;
					CuQpDelta = -local_CuQpDelta;
				}
			}
			IsCuQpDeltaCoded = 1;
			set_qPy();
		}
	}
	tu_idx = 8;
	local_tu_x0 = tu_x0;
	rc_x0 = local_tu_x0;
	local_tu_y0 = tu_y0;
	rc_y0 = local_tu_y0;
	local_tu_log2TrafoSize = tu_log2TrafoSize;
	rc_log2TrafoSize = local_tu_log2TrafoSize;
	local_predMode = predMode;
	local_tu_log2TrafoSize = tu_log2TrafoSize;
	local_cur_intra_pred_mode = cur_intra_pred_mode;
	tmp_getScanIdx = HevcDecoder_Algo_Parser_getScanIdx(local_predMode, local_tu_log2TrafoSize, local_cur_intra_pred_mode);
	rc_scanIdx = tmp_getScanIdx;
	local_TEXT_LUMA = HevcDecoder_Algo_Parser_TEXT_LUMA;
	rc_cIdx = local_TEXT_LUMA;
	local_cbf_luma = cbf_luma;
	if (local_cbf_luma == 1) {
		tu_idx = 2;
	}

	// Update ports indexes

}
static i32 isSchedulable_read_TransformUnit_retLuma() {
	i32 result;
	u8 local_tu_idx;

	local_tu_idx = tu_idx;
	result = local_tu_idx == 3;
	return result;
}

static void read_TransformUnit_retLuma() {

	u16 local_tu_x0;
	u8 local_tu_log2TrafoSize;
	u16 cbf_x0;
	u16 local_tu_y0;
	u16 cbf_y0;
	u16 local_tu_xBase;
	u16 cbf_xBase;
	u16 local_tu_yBase;
	u16 cbf_yBase;
	u8 local_predMode;
	u8 local_rc_log2TrafoSize;
	u8 local_intra_pred_mode_c;
	u8 tmp_getScanIdx;
	u8 local_TEXT_CHROMA_U;
	u8 local_tu_trafoDepth;
	u8 tmp_cbf_cb;
	u8 local_tu_blkIdx;
	u8 tmp_cbf_cb0;

	local_tu_x0 = tu_x0;
	local_tu_log2TrafoSize = tu_log2TrafoSize;
	cbf_x0 = local_tu_x0 & (1 << local_tu_log2TrafoSize) - 1;
	local_tu_y0 = tu_y0;
	local_tu_log2TrafoSize = tu_log2TrafoSize;
	cbf_y0 = local_tu_y0 & (1 << local_tu_log2TrafoSize) - 1;
	local_tu_xBase = tu_xBase;
	local_tu_log2TrafoSize = tu_log2TrafoSize;
	cbf_xBase = local_tu_xBase & (1 << local_tu_log2TrafoSize) - 1;
	local_tu_yBase = tu_yBase;
	local_tu_log2TrafoSize = tu_log2TrafoSize;
	cbf_yBase = local_tu_yBase & (1 << local_tu_log2TrafoSize) - 1;
	tu_idx = 5;
	local_tu_log2TrafoSize = tu_log2TrafoSize;
	rc_log2TrafoSize = local_tu_log2TrafoSize;
	local_predMode = predMode;
	local_rc_log2TrafoSize = rc_log2TrafoSize;
	local_intra_pred_mode_c = intra_pred_mode_c;
	tmp_getScanIdx = HevcDecoder_Algo_Parser_getScanIdx(local_predMode, local_rc_log2TrafoSize, local_intra_pred_mode_c);
	rc_scanIdx = tmp_getScanIdx;
	local_TEXT_CHROMA_U = HevcDecoder_Algo_Parser_TEXT_CHROMA_U;
	rc_cIdx = local_TEXT_CHROMA_U;
	local_tu_log2TrafoSize = tu_log2TrafoSize;
	if (local_tu_log2TrafoSize > 2) {
		tu_idx = 10;
		local_tu_x0 = tu_x0;
		rc_x0 = local_tu_x0;
		local_tu_y0 = tu_y0;
		rc_y0 = local_tu_y0;
		local_tu_log2TrafoSize = tu_log2TrafoSize;
		rc_log2TrafoSize = local_tu_log2TrafoSize - 1;
		local_tu_trafoDepth = tu_trafoDepth;
		tmp_cbf_cb = cbf_cb[cbf_x0][cbf_y0][local_tu_trafoDepth];
		if (tmp_cbf_cb == 1) {
			tu_idx = 4;
		}
	} else {
		local_tu_blkIdx = tu_blkIdx;
		if (local_tu_blkIdx == 3) {
			tu_idx = 10;
			local_tu_xBase = tu_xBase;
			rc_x0 = local_tu_xBase;
			local_tu_yBase = tu_yBase;
			rc_y0 = local_tu_yBase;
			local_tu_trafoDepth = tu_trafoDepth;
			tmp_cbf_cb0 = cbf_cb[cbf_xBase][cbf_yBase][local_tu_trafoDepth];
			if (tmp_cbf_cb0 == 1) {
				tu_idx = 4;
			}
		}
	}

	// Update ports indexes

}
static i32 isSchedulable_read_TransformUnit_retCb() {
	i32 result;
	u8 local_tu_idx;

	local_tu_idx = tu_idx;
	result = local_tu_idx == 5;
	return result;
}

static void read_TransformUnit_retCb() {

	u16 local_tu_x0;
	u8 local_tu_log2TrafoSize;
	u16 cbf_x0;
	u16 local_tu_y0;
	u16 cbf_y0;
	u16 local_tu_xBase;
	u16 cbf_xBase;
	u16 local_tu_yBase;
	u16 cbf_yBase;
	u8 local_TEXT_CHROMA_V;
	u8 local_tu_trafoDepth;
	u8 tmp_cbf_cr;
	u8 local_tu_blkIdx;
	u8 tmp_cbf_cr0;

	local_tu_x0 = tu_x0;
	local_tu_log2TrafoSize = tu_log2TrafoSize;
	cbf_x0 = local_tu_x0 & (1 << local_tu_log2TrafoSize) - 1;
	local_tu_y0 = tu_y0;
	local_tu_log2TrafoSize = tu_log2TrafoSize;
	cbf_y0 = local_tu_y0 & (1 << local_tu_log2TrafoSize) - 1;
	local_tu_xBase = tu_xBase;
	local_tu_log2TrafoSize = tu_log2TrafoSize;
	cbf_xBase = local_tu_xBase & (1 << local_tu_log2TrafoSize) - 1;
	local_tu_yBase = tu_yBase;
	local_tu_log2TrafoSize = tu_log2TrafoSize;
	cbf_yBase = local_tu_yBase & (1 << local_tu_log2TrafoSize) - 1;
	tu_idx = 7;
	local_TEXT_CHROMA_V = HevcDecoder_Algo_Parser_TEXT_CHROMA_V;
	rc_cIdx = local_TEXT_CHROMA_V;
	local_tu_log2TrafoSize = tu_log2TrafoSize;
	if (local_tu_log2TrafoSize > 2) {
		tu_idx = 12;
		local_tu_log2TrafoSize = tu_log2TrafoSize;
		rc_log2TrafoSize = local_tu_log2TrafoSize - 1;
		local_tu_trafoDepth = tu_trafoDepth;
		tmp_cbf_cr = cbf_cr[cbf_x0][cbf_y0][local_tu_trafoDepth];
		if (tmp_cbf_cr == 1) {
			tu_idx = 6;
		}
	} else {
		local_tu_blkIdx = tu_blkIdx;
		if (local_tu_blkIdx == 3) {
			tu_idx = 12;
			local_tu_trafoDepth = tu_trafoDepth;
			tmp_cbf_cr0 = cbf_cr[cbf_xBase][cbf_yBase][local_tu_trafoDepth];
			if (tmp_cbf_cr0 == 1) {
				tu_idx = 6;
			}
		}
	}

	// Update ports indexes

}
static i32 isSchedulable_read_TransformUnit_gotoResidualCoding() {
	i32 result;
	u8 local_tu_idx;

	local_tu_idx = tu_idx;
	local_tu_idx = tu_idx;
	local_tu_idx = tu_idx;
	result = local_tu_idx == 2 || local_tu_idx == 4 || local_tu_idx == 6;
	return result;
}

static void read_TransformUnit_gotoResidualCoding() {

	u8 local_tu_idx;

	local_tu_idx = tu_idx;
	tu_idx = local_tu_idx + 1;

	// Update ports indexes

}
static i32 isSchedulable_read_TransformUnit_skipResidualCoding() {
	i32 result;
	u8 local_tu_idx;

	local_tu_idx = tu_idx;
	local_tu_idx = tu_idx;
	local_tu_idx = tu_idx;
	result = local_tu_idx == 8 || local_tu_idx == 10 || local_tu_idx == 12;
	return result;
}

static void read_TransformUnit_skipResidualCoding() {

	u8 local_tu_idx;
	i8 local_qp_y;
	u16 local_qp_bd_offset_luma;
	u8 local_rc_cIdx;
	u8 local_rc_log2TrafoSize;
	i8 local_slice_qp;

	local_tu_idx = tu_idx;
	tu_idx = local_tu_idx - 5;
	local_qp_y = qp_y;
	local_qp_bd_offset_luma = qp_bd_offset_luma;
	qp = local_qp_y + local_qp_bd_offset_luma;
	local_rc_cIdx = rc_cIdx;
	if (local_rc_cIdx == 0) {
	}
	local_rc_log2TrafoSize = rc_log2TrafoSize;
	tokens_TUSize[(index_TUSize + (0)) % SIZE_TUSize] = 1 << local_rc_log2TrafoSize;
	tokens_TUSize[(index_TUSize + (1)) % SIZE_TUSize] = 2;
	tokens_TUSize[(index_TUSize + (2)) % SIZE_TUSize] = 0;
	tokens_TUSize[(index_TUSize + (3)) % SIZE_TUSize] = 0;
	local_slice_qp = slice_qp;
	tokens_TUSize[(index_TUSize + (4)) % SIZE_TUSize] = local_slice_qp;
	local_rc_cIdx = rc_cIdx;
	tokens_TUSize[(index_TUSize + (5)) % SIZE_TUSize] = local_rc_cIdx;
	tokens_TUSize[(index_TUSize + (6)) % SIZE_TUSize] = 0;

	// Update ports indexes
	index_TUSize += 7;
	write_end_TUSize();

}
static void read_TransformUnit_skipResidualCoding_aligned() {

	u8 local_tu_idx;
	i8 local_qp_y;
	u16 local_qp_bd_offset_luma;
	u8 local_rc_cIdx;
	u8 local_rc_log2TrafoSize;
	i8 local_slice_qp;

	local_tu_idx = tu_idx;
	tu_idx = local_tu_idx - 5;
	local_qp_y = qp_y;
	local_qp_bd_offset_luma = qp_bd_offset_luma;
	qp = local_qp_y + local_qp_bd_offset_luma;
	local_rc_cIdx = rc_cIdx;
	if (local_rc_cIdx == 0) {
	}
	local_rc_log2TrafoSize = rc_log2TrafoSize;
	tokens_TUSize[(index_TUSize % SIZE_TUSize) + (0)] = 1 << local_rc_log2TrafoSize;
	tokens_TUSize[(index_TUSize % SIZE_TUSize) + (1)] = 2;
	tokens_TUSize[(index_TUSize % SIZE_TUSize) + (2)] = 0;
	tokens_TUSize[(index_TUSize % SIZE_TUSize) + (3)] = 0;
	local_slice_qp = slice_qp;
	tokens_TUSize[(index_TUSize % SIZE_TUSize) + (4)] = local_slice_qp;
	local_rc_cIdx = rc_cIdx;
	tokens_TUSize[(index_TUSize % SIZE_TUSize) + (5)] = local_rc_cIdx;
	tokens_TUSize[(index_TUSize % SIZE_TUSize) + (6)] = 0;

	// Update ports indexes
	index_TUSize += 7;
	write_end_TUSize();

}
static i32 isSchedulable_read_TransformUnit_end() {
	i32 result;
	u8 local_tu_idx;

	local_tu_idx = tu_idx;
	result = local_tu_idx == 7;
	return result;
}

static void read_TransformUnit_end() {

	i32 local_DEBUG_CABAC;

	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
		printf("read_TransformUnit_end\n");
	}

	// Update ports indexes

}
static i32 isSchedulable_read_ResidualCoding_start() {
	i32 result;
	i32 tmp_isFifoFull;

	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	result = tmp_isFifoFull;
	return result;
}

static void read_ResidualCoding_start() {

	i32 res[1];
	u8 local_rc_log2TrafoSize;
	i32 sz;
	u8 transform_skip_flag;
	i32 matrix_id;
	i32 qp_offset;
	i16 qp_i;
	i32 x_cg_last_sig;
	i32 y_cg_last_sig;
	i32 last_x_c;
	i32 last_y_c;
	u8 qp_c[15];
	u8 levelScale[6];
	u8 local_predMode;
	u8 local_INTRA;
	u8 local_rc_cIdx;
	u8 local_TEXT_LUMA;
	u8 isDST;
	i32 local_DEBUG_CABAC;
	i32 local_DEBUG_TRACE1;
	char * tmp_if;
	u8 local_TEXT_CHROMA_U;
	u16 local_rc_x0;
	u16 local_rc_y0;
	u8 local_rc_scanIdx;
	char * tmp_if0;
	u8 local_cu_transquant_bypass_flag;
	u16 local_sps_id;
	i32 tmp_sps_bit_depth_luma_minus8;
	i32 tmp_sps_bit_depth_chroma_minus8;
	i8 local_qp_y;
	u16 local_qp_bd_offset_luma;
	u16 local_pps_id;
	i8 tmp_pps_cb_qp_offset;
	i8 local_slice_cb_qp_offset;
	i8 tmp_pps_cr_qp_offset;
	i8 local_slice_cr_qp_offset;
	u8 tmp_qp_c;
	i16 local_qp;
	u8 local_shift;
	u8 tmp_rem6;
	u8 tmp_levelScale;
	u8 tmp_div6;
	u8 tmp_sps_scaling_list_enabled_flag;
	u8 tmp_pps_scaling_list_data_present_flag;
	i32 i;
	u8 tmp_pps_sl;
	u8 tmp_pps_sl_dc;
	i32 i0;
	u8 tmp_sps_sl;
	u8 tmp_sps_sl_dc;
	i32 i1;
	i32 i2;
	i32 j;
	u8 tmp_pps_transform_skip_enabled_flag;
	i32 tmp_res;
	i32 tmp_res0;
	u8 local_LastSignificantCoeffX;
	i32 tmp_res1;
	u8 local_LastSignificantCoeffY;
	i32 tmp_res2;
	u8 local_SCAN_VER;
	i32 tmp_res3;
	u8 tmp_diag_scan4x4_inv;
	u16 local_num_coeff;
	u8 tmp_diag_scan2x2_inv;
	u8 tmp_diag_scan4x4_inv0;
	u8 tmp_diag_scan8x8_inv;
	u8 tmp_horiz_scan8x8_inv;
	u8 tmp_horiz_scan8x8_inv0;
	i8 local_rc_lastSubBlock;
	i8 local_slice_qp;
	i8 tmp_pps_cb_qp_offset0;
	i8 tmp_pps_cr_qp_offset0;

	local_rc_log2TrafoSize = rc_log2TrafoSize;
	sz = 1 << local_rc_log2TrafoSize;
	qp_c[0] = 29;
	qp_c[1] = 30;
	qp_c[2] = 31;
	qp_c[3] = 32;
	qp_c[4] = 33;
	qp_c[5] = 33;
	qp_c[6] = 34;
	qp_c[7] = 34;
	qp_c[8] = 35;
	qp_c[9] = 35;
	qp_c[10] = 36;
	qp_c[11] = 36;
	qp_c[12] = 37;
	qp_c[13] = 37;
	levelScale[0] = 40;
	levelScale[1] = 45;
	levelScale[2] = 51;
	levelScale[3] = 57;
	levelScale[4] = 64;
	levelScale[5] = 72;
	local_predMode = predMode;
	local_INTRA = HevcDecoder_Algo_Parser_INTRA;
	local_rc_cIdx = rc_cIdx;
	local_TEXT_LUMA = HevcDecoder_Algo_Parser_TEXT_LUMA;
	if (local_predMode == local_INTRA && local_rc_cIdx == local_TEXT_LUMA && sz == 4) {
		isDST = 1;
	} else {
		isDST = 0;
	}
	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	local_DEBUG_TRACE1 = HevcDecoder_Algo_Parser_DEBUG_TRACE1;
	if (local_DEBUG_CABAC && local_DEBUG_TRACE1) {
		local_rc_cIdx = rc_cIdx;
		local_TEXT_LUMA = HevcDecoder_Algo_Parser_TEXT_LUMA;
		if (local_rc_cIdx == local_TEXT_LUMA) {
			tmp_if = "cbY";
		} else {
			local_rc_cIdx = rc_cIdx;
			local_TEXT_CHROMA_U = HevcDecoder_Algo_Parser_TEXT_CHROMA_U;
			if (local_rc_cIdx == local_TEXT_CHROMA_U) {
				tmp_if = "cbU";
			} else {
				tmp_if = "cbV";
			}
		}
		local_rc_x0 = rc_x0;
		local_rc_y0 = rc_y0;
		local_rc_log2TrafoSize = rc_log2TrafoSize;
		local_rc_scanIdx = rc_scanIdx;
		local_rc_cIdx = rc_cIdx;
		printf("read_ResidualCoding.start %s(%u, %u, %u, %u, %u)\n", tmp_if, local_rc_x0, local_rc_y0, local_rc_log2TrafoSize, local_rc_scanIdx, local_rc_cIdx);
	} else {
		local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
		if (local_DEBUG_CABAC) {
			local_rc_cIdx = rc_cIdx;
			local_TEXT_LUMA = HevcDecoder_Algo_Parser_TEXT_LUMA;
			if (local_rc_cIdx == local_TEXT_LUMA) {
				tmp_if0 = "cbY";
			} else {
				local_rc_cIdx = rc_cIdx;
				local_TEXT_CHROMA_U = HevcDecoder_Algo_Parser_TEXT_CHROMA_U;
				if (local_rc_cIdx == local_TEXT_CHROMA_U) {
					tmp_if0 = "cbU";
				} else {
					tmp_if0 = "cbV";
				}
			}
			printf("read_ResidualCoding.start %s\n", tmp_if0);
		}
	}
	local_cu_transquant_bypass_flag = cu_transquant_bypass_flag;
	if (local_cu_transquant_bypass_flag == 0) {
		local_rc_cIdx = rc_cIdx;
		if (local_rc_cIdx == 0) {
			local_sps_id = sps_id;
			tmp_sps_bit_depth_luma_minus8 = sps_bit_depth_luma_minus8[local_sps_id];
			local_rc_log2TrafoSize = rc_log2TrafoSize;
			shift = tmp_sps_bit_depth_luma_minus8 + 8 + local_rc_log2TrafoSize - 5;
		} else {
			local_sps_id = sps_id;
			tmp_sps_bit_depth_chroma_minus8 = sps_bit_depth_chroma_minus8[local_sps_id];
			local_rc_log2TrafoSize = rc_log2TrafoSize;
			shift = tmp_sps_bit_depth_chroma_minus8 + 8 + local_rc_log2TrafoSize - 5;
		}
		local_rc_cIdx = rc_cIdx;
		if (local_rc_cIdx == 0) {
			local_qp_y = qp_y;
			local_qp_bd_offset_luma = qp_bd_offset_luma;
			qp = local_qp_y + local_qp_bd_offset_luma;
		} else {
			local_rc_cIdx = rc_cIdx;
			if (local_rc_cIdx == 1) {
				local_pps_id = pps_id;
				tmp_pps_cb_qp_offset = pps_cb_qp_offset[local_pps_id];
				local_slice_cb_qp_offset = slice_cb_qp_offset;
				qp_offset = tmp_pps_cb_qp_offset + local_slice_cb_qp_offset;
			} else {
				local_pps_id = pps_id;
				tmp_pps_cr_qp_offset = pps_cr_qp_offset[local_pps_id];
				local_slice_cr_qp_offset = slice_cr_qp_offset;
				qp_offset = tmp_pps_cr_qp_offset + local_slice_cr_qp_offset;
			}
			local_qp_y = qp_y;
			local_qp_bd_offset_luma = qp_bd_offset_luma;
			qp_i = HevcDecoder_Algo_Parser_clip_i32(local_qp_y + qp_offset, -local_qp_bd_offset_luma, 57);
			if (qp_i < 30) {
				qp = qp_i;
			} else {
				if (qp_i > 43) {
					qp = qp_i - 6;
				} else {
					tmp_qp_c = qp_c[qp_i - 30];
					qp = tmp_qp_c;
				}
			}
			local_qp = qp;
			local_qp_bd_offset_luma = qp_bd_offset_luma;
			qp = local_qp + local_qp_bd_offset_luma;
		}
		local_shift = shift;
		add = 1 << (local_shift - 1);
		local_qp = qp;
		tmp_rem6 = HevcDecoder_Algo_Parser_rem6[local_qp];
		tmp_levelScale = levelScale[tmp_rem6];
		local_qp = qp;
		tmp_div6 = HevcDecoder_Algo_Parser_div6[local_qp];
		scale = tmp_levelScale << tmp_div6;
		scale_m = 16;
		dc_scale = 16;
		local_sps_id = sps_id;
		tmp_sps_scaling_list_enabled_flag = sps_scaling_list_enabled_flag[local_sps_id];
		if (tmp_sps_scaling_list_enabled_flag == 1) {
			local_predMode = predMode;
			local_INTRA = HevcDecoder_Algo_Parser_INTRA;
			if (local_predMode != local_INTRA) {
				matrix_id = 1;
			} else {
				matrix_id = 0;
			}
			local_rc_log2TrafoSize = rc_log2TrafoSize;
			if (local_rc_log2TrafoSize != 5) {
				local_rc_cIdx = rc_cIdx;
				matrix_id = 3 * matrix_id + local_rc_cIdx;
			}
			local_pps_id = pps_id;
			tmp_pps_scaling_list_data_present_flag = pps_scaling_list_data_present_flag[local_pps_id];
			if (tmp_pps_scaling_list_data_present_flag == 1) {
				i = 0;
				while (i <= 63) {
					local_pps_id = pps_id;
					local_rc_log2TrafoSize = rc_log2TrafoSize;
					tmp_pps_sl = pps_sl[local_pps_id][local_rc_log2TrafoSize - 2][matrix_id][i];
					scale_matrix[i] = tmp_pps_sl;
					i = i + 1;
				}
				local_rc_log2TrafoSize = rc_log2TrafoSize;
				if (local_rc_log2TrafoSize >= 4) {
					local_pps_id = pps_id;
					local_rc_log2TrafoSize = rc_log2TrafoSize;
					tmp_pps_sl_dc = pps_sl_dc[local_pps_id][local_rc_log2TrafoSize - 4][matrix_id];
					dc_scale = tmp_pps_sl_dc;
				}
			} else {
				i0 = 0;
				while (i0 <= 63) {
					local_sps_id = sps_id;
					local_rc_log2TrafoSize = rc_log2TrafoSize;
					tmp_sps_sl = sps_sl[local_sps_id][local_rc_log2TrafoSize - 2][matrix_id][i0];
					scale_matrix[i0] = tmp_sps_sl;
					i0 = i0 + 1;
				}
				local_rc_log2TrafoSize = rc_log2TrafoSize;
				if (local_rc_log2TrafoSize >= 4) {
					local_sps_id = sps_id;
					local_rc_log2TrafoSize = rc_log2TrafoSize;
					tmp_sps_sl_dc = sps_sl_dc[local_sps_id][local_rc_log2TrafoSize - 4][matrix_id];
					dc_scale = tmp_sps_sl_dc;
				}
			}
		}
	} else {
		shift = 0;
		add = 0;
		scale = 0;
		dc_scale = 0;
	}
	i1 = 0;
	while (i1 <= sz * sz - 1) {
		tabTransCoeffLevel[i1] = 0;
		i1 = i1 + 1;
	}
	i2 = 0;
	while (i2 <= 7) {
		j = 0;
		while (j <= 7) {
			coded_sub_block_flag[i2][j] = 0;
			j = j + 1;
		}
		i2 = i2 + 1;
	}
	local_pps_id = pps_id;
	tmp_pps_transform_skip_enabled_flag = pps_transform_skip_enabled_flag[local_pps_id];
	local_cu_transquant_bypass_flag = cu_transquant_bypass_flag;
	local_rc_log2TrafoSize = rc_log2TrafoSize;
	if (tmp_pps_transform_skip_enabled_flag == 1 && local_cu_transquant_bypass_flag == 0 && local_rc_log2TrafoSize == 2) {
		local_rc_cIdx = rc_cIdx;
		HevcDecoder_Algo_Parser_get_TRANSFORM_SKIP_FLAG(codIRange, codIOffset, ctxTable, fifo, res, local_rc_cIdx);
		transform_skip_flag = res[0];
	} else {
		transform_skip_flag = 0;
	}
	local_rc_log2TrafoSize = rc_log2TrafoSize;
	local_rc_cIdx = rc_cIdx;
	HevcDecoder_Algo_Parser_get_LAST_SIGNIFICANT_COEFF_X_PREFIX(codIRange, codIOffset, ctxTable, fifo, res, local_rc_log2TrafoSize, local_rc_cIdx);
	tmp_res = res[0];
	LastSignificantCoeffX = tmp_res;
	local_rc_log2TrafoSize = rc_log2TrafoSize;
	local_rc_cIdx = rc_cIdx;
	HevcDecoder_Algo_Parser_get_LAST_SIGNIFICANT_COEFF_Y_PREFIX(codIRange, codIOffset, ctxTable, fifo, res, local_rc_log2TrafoSize, local_rc_cIdx);
	tmp_res0 = res[0];
	LastSignificantCoeffY = tmp_res0;
	local_LastSignificantCoeffX = LastSignificantCoeffX;
	if (local_LastSignificantCoeffX > 3) {
		local_LastSignificantCoeffX = LastSignificantCoeffX;
		HevcDecoder_Algo_Parser_get_LAST_SIGNIFICANT_COEFF_XY_SUFFIX(codIRange, codIOffset, fifo, res, local_LastSignificantCoeffX);
		local_LastSignificantCoeffX = LastSignificantCoeffX;
		local_LastSignificantCoeffX = LastSignificantCoeffX;
		tmp_res1 = res[0];
		LastSignificantCoeffX = (1 << ((local_LastSignificantCoeffX >> 1) - 1)) * (2 + (local_LastSignificantCoeffX & 1)) + tmp_res1;
	}
	local_LastSignificantCoeffY = LastSignificantCoeffY;
	if (local_LastSignificantCoeffY > 3) {
		local_LastSignificantCoeffY = LastSignificantCoeffY;
		HevcDecoder_Algo_Parser_get_LAST_SIGNIFICANT_COEFF_XY_SUFFIX(codIRange, codIOffset, fifo, res, local_LastSignificantCoeffY);
		local_LastSignificantCoeffY = LastSignificantCoeffY;
		local_LastSignificantCoeffY = LastSignificantCoeffY;
		tmp_res2 = res[0];
		LastSignificantCoeffY = (1 << ((local_LastSignificantCoeffY >> 1) - 1)) * (2 + (local_LastSignificantCoeffY & 1)) + tmp_res2;
	}
	local_rc_scanIdx = rc_scanIdx;
	local_SCAN_VER = HevcDecoder_Algo_Parser_SCAN_VER;
	if (local_rc_scanIdx == local_SCAN_VER) {
		local_LastSignificantCoeffX = LastSignificantCoeffX;
		res[0] = local_LastSignificantCoeffX;
		local_LastSignificantCoeffY = LastSignificantCoeffY;
		LastSignificantCoeffX = local_LastSignificantCoeffY;
		tmp_res3 = res[0];
		LastSignificantCoeffY = tmp_res3;
	}
	local_LastSignificantCoeffX = LastSignificantCoeffX;
	x_cg_last_sig = local_LastSignificantCoeffX >> 2;
	local_LastSignificantCoeffY = LastSignificantCoeffY;
	y_cg_last_sig = local_LastSignificantCoeffY >> 2;
	local_rc_scanIdx = rc_scanIdx;
	if (local_rc_scanIdx == 0) {
		local_LastSignificantCoeffX = LastSignificantCoeffX;
		last_x_c = local_LastSignificantCoeffX & 3;
		local_LastSignificantCoeffY = LastSignificantCoeffY;
		last_y_c = local_LastSignificantCoeffY & 3;
		tmp_diag_scan4x4_inv = HevcDecoder_Algo_Parser_diag_scan4x4_inv[last_y_c][last_x_c];
		num_coeff = tmp_diag_scan4x4_inv;
		local_rc_log2TrafoSize = rc_log2TrafoSize;
		if (local_rc_log2TrafoSize == 3) {
			local_num_coeff = num_coeff;
			tmp_diag_scan2x2_inv = HevcDecoder_Algo_Parser_diag_scan2x2_inv[y_cg_last_sig][x_cg_last_sig];
			num_coeff = local_num_coeff + (tmp_diag_scan2x2_inv << 4);
		} else {
			local_rc_log2TrafoSize = rc_log2TrafoSize;
			if (local_rc_log2TrafoSize == 4) {
				local_num_coeff = num_coeff;
				tmp_diag_scan4x4_inv0 = HevcDecoder_Algo_Parser_diag_scan4x4_inv[y_cg_last_sig][x_cg_last_sig];
				num_coeff = local_num_coeff + (tmp_diag_scan4x4_inv0 << 4);
			} else {
				local_num_coeff = num_coeff;
				tmp_diag_scan8x8_inv = HevcDecoder_Algo_Parser_diag_scan8x8_inv[y_cg_last_sig][x_cg_last_sig];
				num_coeff = local_num_coeff + (tmp_diag_scan8x8_inv << 4);
			}
		}
	} else {
		local_rc_scanIdx = rc_scanIdx;
		if (local_rc_scanIdx == 1) {
			local_LastSignificantCoeffY = LastSignificantCoeffY;
			local_LastSignificantCoeffX = LastSignificantCoeffX;
			tmp_horiz_scan8x8_inv = HevcDecoder_Algo_Parser_horiz_scan8x8_inv[local_LastSignificantCoeffY][local_LastSignificantCoeffX];
			num_coeff = tmp_horiz_scan8x8_inv;
		} else {
			local_rc_scanIdx = rc_scanIdx;
			if (local_rc_scanIdx == 2) {
				local_LastSignificantCoeffX = LastSignificantCoeffX;
				local_LastSignificantCoeffY = LastSignificantCoeffY;
				tmp_horiz_scan8x8_inv0 = HevcDecoder_Algo_Parser_horiz_scan8x8_inv[local_LastSignificantCoeffX][local_LastSignificantCoeffY];
				num_coeff = tmp_horiz_scan8x8_inv0;
			}
		}
	}
	local_num_coeff = num_coeff;
	num_coeff = local_num_coeff + 1;
	local_num_coeff = num_coeff;
	rc_lastSubBlock = (local_num_coeff - 1) >> 4;
	local_num_coeff = num_coeff;
	local_rc_lastSubBlock = rc_lastSubBlock;
	rc_lastScanPos = local_num_coeff - (local_rc_lastSubBlock << 4) - 1;
	local_rc_lastSubBlock = rc_lastSubBlock;
	rc_i = local_rc_lastSubBlock;
	local_rc_cIdx = rc_cIdx;
	if (local_rc_cIdx == 0) {
	}
	tokens_TUSize[(index_TUSize + (0)) % SIZE_TUSize] = sz;
	tokens_TUSize[(index_TUSize + (1)) % SIZE_TUSize] = 0;
	tokens_TUSize[(index_TUSize + (2)) % SIZE_TUSize] = isDST;
	tokens_TUSize[(index_TUSize + (3)) % SIZE_TUSize] = transform_skip_flag;
	local_slice_qp = slice_qp;
	tokens_TUSize[(index_TUSize + (4)) % SIZE_TUSize] = local_slice_qp;
	local_rc_cIdx = rc_cIdx;
	tokens_TUSize[(index_TUSize + (5)) % SIZE_TUSize] = local_rc_cIdx;
	local_rc_cIdx = rc_cIdx;
	local_TEXT_CHROMA_U = HevcDecoder_Algo_Parser_TEXT_CHROMA_U;
	if (local_rc_cIdx == local_TEXT_CHROMA_U) {
		local_pps_id = pps_id;
		tmp_pps_cb_qp_offset0 = pps_cb_qp_offset[local_pps_id];
		local_slice_cb_qp_offset = slice_cb_qp_offset;
		tokens_TUSize[(index_TUSize + (6)) % SIZE_TUSize] = tmp_pps_cb_qp_offset0 + local_slice_cb_qp_offset;
	} else {
		local_pps_id = pps_id;
		tmp_pps_cr_qp_offset0 = pps_cr_qp_offset[local_pps_id];
		local_slice_cr_qp_offset = slice_cr_qp_offset;
		tokens_TUSize[(index_TUSize + (6)) % SIZE_TUSize] = tmp_pps_cr_qp_offset0 + local_slice_cr_qp_offset;
	}

	// Update ports indexes
	index_TUSize += 7;
	write_end_TUSize();

}
static void read_ResidualCoding_start_aligned() {

	i32 res[1];
	u8 local_rc_log2TrafoSize;
	i32 sz;
	u8 transform_skip_flag;
	i32 matrix_id;
	i32 qp_offset;
	i16 qp_i;
	i32 x_cg_last_sig;
	i32 y_cg_last_sig;
	i32 last_x_c;
	i32 last_y_c;
	u8 qp_c[15];
	u8 levelScale[6];
	u8 local_predMode;
	u8 local_INTRA;
	u8 local_rc_cIdx;
	u8 local_TEXT_LUMA;
	u8 isDST;
	i32 local_DEBUG_CABAC;
	i32 local_DEBUG_TRACE1;
	char * tmp_if;
	u8 local_TEXT_CHROMA_U;
	u16 local_rc_x0;
	u16 local_rc_y0;
	u8 local_rc_scanIdx;
	char * tmp_if0;
	u8 local_cu_transquant_bypass_flag;
	u16 local_sps_id;
	i32 tmp_sps_bit_depth_luma_minus8;
	i32 tmp_sps_bit_depth_chroma_minus8;
	i8 local_qp_y;
	u16 local_qp_bd_offset_luma;
	u16 local_pps_id;
	i8 tmp_pps_cb_qp_offset;
	i8 local_slice_cb_qp_offset;
	i8 tmp_pps_cr_qp_offset;
	i8 local_slice_cr_qp_offset;
	u8 tmp_qp_c;
	i16 local_qp;
	u8 local_shift;
	u8 tmp_rem6;
	u8 tmp_levelScale;
	u8 tmp_div6;
	u8 tmp_sps_scaling_list_enabled_flag;
	u8 tmp_pps_scaling_list_data_present_flag;
	i32 i;
	u8 tmp_pps_sl;
	u8 tmp_pps_sl_dc;
	i32 i0;
	u8 tmp_sps_sl;
	u8 tmp_sps_sl_dc;
	i32 i1;
	i32 i2;
	i32 j;
	u8 tmp_pps_transform_skip_enabled_flag;
	i32 tmp_res;
	i32 tmp_res0;
	u8 local_LastSignificantCoeffX;
	i32 tmp_res1;
	u8 local_LastSignificantCoeffY;
	i32 tmp_res2;
	u8 local_SCAN_VER;
	i32 tmp_res3;
	u8 tmp_diag_scan4x4_inv;
	u16 local_num_coeff;
	u8 tmp_diag_scan2x2_inv;
	u8 tmp_diag_scan4x4_inv0;
	u8 tmp_diag_scan8x8_inv;
	u8 tmp_horiz_scan8x8_inv;
	u8 tmp_horiz_scan8x8_inv0;
	i8 local_rc_lastSubBlock;
	i8 local_slice_qp;
	i8 tmp_pps_cb_qp_offset0;
	i8 tmp_pps_cr_qp_offset0;

	local_rc_log2TrafoSize = rc_log2TrafoSize;
	sz = 1 << local_rc_log2TrafoSize;
	qp_c[0] = 29;
	qp_c[1] = 30;
	qp_c[2] = 31;
	qp_c[3] = 32;
	qp_c[4] = 33;
	qp_c[5] = 33;
	qp_c[6] = 34;
	qp_c[7] = 34;
	qp_c[8] = 35;
	qp_c[9] = 35;
	qp_c[10] = 36;
	qp_c[11] = 36;
	qp_c[12] = 37;
	qp_c[13] = 37;
	levelScale[0] = 40;
	levelScale[1] = 45;
	levelScale[2] = 51;
	levelScale[3] = 57;
	levelScale[4] = 64;
	levelScale[5] = 72;
	local_predMode = predMode;
	local_INTRA = HevcDecoder_Algo_Parser_INTRA;
	local_rc_cIdx = rc_cIdx;
	local_TEXT_LUMA = HevcDecoder_Algo_Parser_TEXT_LUMA;
	if (local_predMode == local_INTRA && local_rc_cIdx == local_TEXT_LUMA && sz == 4) {
		isDST = 1;
	} else {
		isDST = 0;
	}
	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	local_DEBUG_TRACE1 = HevcDecoder_Algo_Parser_DEBUG_TRACE1;
	if (local_DEBUG_CABAC && local_DEBUG_TRACE1) {
		local_rc_cIdx = rc_cIdx;
		local_TEXT_LUMA = HevcDecoder_Algo_Parser_TEXT_LUMA;
		if (local_rc_cIdx == local_TEXT_LUMA) {
			tmp_if = "cbY";
		} else {
			local_rc_cIdx = rc_cIdx;
			local_TEXT_CHROMA_U = HevcDecoder_Algo_Parser_TEXT_CHROMA_U;
			if (local_rc_cIdx == local_TEXT_CHROMA_U) {
				tmp_if = "cbU";
			} else {
				tmp_if = "cbV";
			}
		}
		local_rc_x0 = rc_x0;
		local_rc_y0 = rc_y0;
		local_rc_log2TrafoSize = rc_log2TrafoSize;
		local_rc_scanIdx = rc_scanIdx;
		local_rc_cIdx = rc_cIdx;
		printf("read_ResidualCoding.start %s(%u, %u, %u, %u, %u)\n", tmp_if, local_rc_x0, local_rc_y0, local_rc_log2TrafoSize, local_rc_scanIdx, local_rc_cIdx);
	} else {
		local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
		if (local_DEBUG_CABAC) {
			local_rc_cIdx = rc_cIdx;
			local_TEXT_LUMA = HevcDecoder_Algo_Parser_TEXT_LUMA;
			if (local_rc_cIdx == local_TEXT_LUMA) {
				tmp_if0 = "cbY";
			} else {
				local_rc_cIdx = rc_cIdx;
				local_TEXT_CHROMA_U = HevcDecoder_Algo_Parser_TEXT_CHROMA_U;
				if (local_rc_cIdx == local_TEXT_CHROMA_U) {
					tmp_if0 = "cbU";
				} else {
					tmp_if0 = "cbV";
				}
			}
			printf("read_ResidualCoding.start %s\n", tmp_if0);
		}
	}
	local_cu_transquant_bypass_flag = cu_transquant_bypass_flag;
	if (local_cu_transquant_bypass_flag == 0) {
		local_rc_cIdx = rc_cIdx;
		if (local_rc_cIdx == 0) {
			local_sps_id = sps_id;
			tmp_sps_bit_depth_luma_minus8 = sps_bit_depth_luma_minus8[local_sps_id];
			local_rc_log2TrafoSize = rc_log2TrafoSize;
			shift = tmp_sps_bit_depth_luma_minus8 + 8 + local_rc_log2TrafoSize - 5;
		} else {
			local_sps_id = sps_id;
			tmp_sps_bit_depth_chroma_minus8 = sps_bit_depth_chroma_minus8[local_sps_id];
			local_rc_log2TrafoSize = rc_log2TrafoSize;
			shift = tmp_sps_bit_depth_chroma_minus8 + 8 + local_rc_log2TrafoSize - 5;
		}
		local_rc_cIdx = rc_cIdx;
		if (local_rc_cIdx == 0) {
			local_qp_y = qp_y;
			local_qp_bd_offset_luma = qp_bd_offset_luma;
			qp = local_qp_y + local_qp_bd_offset_luma;
		} else {
			local_rc_cIdx = rc_cIdx;
			if (local_rc_cIdx == 1) {
				local_pps_id = pps_id;
				tmp_pps_cb_qp_offset = pps_cb_qp_offset[local_pps_id];
				local_slice_cb_qp_offset = slice_cb_qp_offset;
				qp_offset = tmp_pps_cb_qp_offset + local_slice_cb_qp_offset;
			} else {
				local_pps_id = pps_id;
				tmp_pps_cr_qp_offset = pps_cr_qp_offset[local_pps_id];
				local_slice_cr_qp_offset = slice_cr_qp_offset;
				qp_offset = tmp_pps_cr_qp_offset + local_slice_cr_qp_offset;
			}
			local_qp_y = qp_y;
			local_qp_bd_offset_luma = qp_bd_offset_luma;
			qp_i = HevcDecoder_Algo_Parser_clip_i32(local_qp_y + qp_offset, -local_qp_bd_offset_luma, 57);
			if (qp_i < 30) {
				qp = qp_i;
			} else {
				if (qp_i > 43) {
					qp = qp_i - 6;
				} else {
					tmp_qp_c = qp_c[qp_i - 30];
					qp = tmp_qp_c;
				}
			}
			local_qp = qp;
			local_qp_bd_offset_luma = qp_bd_offset_luma;
			qp = local_qp + local_qp_bd_offset_luma;
		}
		local_shift = shift;
		add = 1 << (local_shift - 1);
		local_qp = qp;
		tmp_rem6 = HevcDecoder_Algo_Parser_rem6[local_qp];
		tmp_levelScale = levelScale[tmp_rem6];
		local_qp = qp;
		tmp_div6 = HevcDecoder_Algo_Parser_div6[local_qp];
		scale = tmp_levelScale << tmp_div6;
		scale_m = 16;
		dc_scale = 16;
		local_sps_id = sps_id;
		tmp_sps_scaling_list_enabled_flag = sps_scaling_list_enabled_flag[local_sps_id];
		if (tmp_sps_scaling_list_enabled_flag == 1) {
			local_predMode = predMode;
			local_INTRA = HevcDecoder_Algo_Parser_INTRA;
			if (local_predMode != local_INTRA) {
				matrix_id = 1;
			} else {
				matrix_id = 0;
			}
			local_rc_log2TrafoSize = rc_log2TrafoSize;
			if (local_rc_log2TrafoSize != 5) {
				local_rc_cIdx = rc_cIdx;
				matrix_id = 3 * matrix_id + local_rc_cIdx;
			}
			local_pps_id = pps_id;
			tmp_pps_scaling_list_data_present_flag = pps_scaling_list_data_present_flag[local_pps_id];
			if (tmp_pps_scaling_list_data_present_flag == 1) {
				i = 0;
				while (i <= 63) {
					local_pps_id = pps_id;
					local_rc_log2TrafoSize = rc_log2TrafoSize;
					tmp_pps_sl = pps_sl[local_pps_id][local_rc_log2TrafoSize - 2][matrix_id][i];
					scale_matrix[i] = tmp_pps_sl;
					i = i + 1;
				}
				local_rc_log2TrafoSize = rc_log2TrafoSize;
				if (local_rc_log2TrafoSize >= 4) {
					local_pps_id = pps_id;
					local_rc_log2TrafoSize = rc_log2TrafoSize;
					tmp_pps_sl_dc = pps_sl_dc[local_pps_id][local_rc_log2TrafoSize - 4][matrix_id];
					dc_scale = tmp_pps_sl_dc;
				}
			} else {
				i0 = 0;
				while (i0 <= 63) {
					local_sps_id = sps_id;
					local_rc_log2TrafoSize = rc_log2TrafoSize;
					tmp_sps_sl = sps_sl[local_sps_id][local_rc_log2TrafoSize - 2][matrix_id][i0];
					scale_matrix[i0] = tmp_sps_sl;
					i0 = i0 + 1;
				}
				local_rc_log2TrafoSize = rc_log2TrafoSize;
				if (local_rc_log2TrafoSize >= 4) {
					local_sps_id = sps_id;
					local_rc_log2TrafoSize = rc_log2TrafoSize;
					tmp_sps_sl_dc = sps_sl_dc[local_sps_id][local_rc_log2TrafoSize - 4][matrix_id];
					dc_scale = tmp_sps_sl_dc;
				}
			}
		}
	} else {
		shift = 0;
		add = 0;
		scale = 0;
		dc_scale = 0;
	}
	i1 = 0;
	while (i1 <= sz * sz - 1) {
		tabTransCoeffLevel[i1] = 0;
		i1 = i1 + 1;
	}
	i2 = 0;
	while (i2 <= 7) {
		j = 0;
		while (j <= 7) {
			coded_sub_block_flag[i2][j] = 0;
			j = j + 1;
		}
		i2 = i2 + 1;
	}
	local_pps_id = pps_id;
	tmp_pps_transform_skip_enabled_flag = pps_transform_skip_enabled_flag[local_pps_id];
	local_cu_transquant_bypass_flag = cu_transquant_bypass_flag;
	local_rc_log2TrafoSize = rc_log2TrafoSize;
	if (tmp_pps_transform_skip_enabled_flag == 1 && local_cu_transquant_bypass_flag == 0 && local_rc_log2TrafoSize == 2) {
		local_rc_cIdx = rc_cIdx;
		HevcDecoder_Algo_Parser_get_TRANSFORM_SKIP_FLAG(codIRange, codIOffset, ctxTable, fifo, res, local_rc_cIdx);
		transform_skip_flag = res[0];
	} else {
		transform_skip_flag = 0;
	}
	local_rc_log2TrafoSize = rc_log2TrafoSize;
	local_rc_cIdx = rc_cIdx;
	HevcDecoder_Algo_Parser_get_LAST_SIGNIFICANT_COEFF_X_PREFIX(codIRange, codIOffset, ctxTable, fifo, res, local_rc_log2TrafoSize, local_rc_cIdx);
	tmp_res = res[0];
	LastSignificantCoeffX = tmp_res;
	local_rc_log2TrafoSize = rc_log2TrafoSize;
	local_rc_cIdx = rc_cIdx;
	HevcDecoder_Algo_Parser_get_LAST_SIGNIFICANT_COEFF_Y_PREFIX(codIRange, codIOffset, ctxTable, fifo, res, local_rc_log2TrafoSize, local_rc_cIdx);
	tmp_res0 = res[0];
	LastSignificantCoeffY = tmp_res0;
	local_LastSignificantCoeffX = LastSignificantCoeffX;
	if (local_LastSignificantCoeffX > 3) {
		local_LastSignificantCoeffX = LastSignificantCoeffX;
		HevcDecoder_Algo_Parser_get_LAST_SIGNIFICANT_COEFF_XY_SUFFIX(codIRange, codIOffset, fifo, res, local_LastSignificantCoeffX);
		local_LastSignificantCoeffX = LastSignificantCoeffX;
		local_LastSignificantCoeffX = LastSignificantCoeffX;
		tmp_res1 = res[0];
		LastSignificantCoeffX = (1 << ((local_LastSignificantCoeffX >> 1) - 1)) * (2 + (local_LastSignificantCoeffX & 1)) + tmp_res1;
	}
	local_LastSignificantCoeffY = LastSignificantCoeffY;
	if (local_LastSignificantCoeffY > 3) {
		local_LastSignificantCoeffY = LastSignificantCoeffY;
		HevcDecoder_Algo_Parser_get_LAST_SIGNIFICANT_COEFF_XY_SUFFIX(codIRange, codIOffset, fifo, res, local_LastSignificantCoeffY);
		local_LastSignificantCoeffY = LastSignificantCoeffY;
		local_LastSignificantCoeffY = LastSignificantCoeffY;
		tmp_res2 = res[0];
		LastSignificantCoeffY = (1 << ((local_LastSignificantCoeffY >> 1) - 1)) * (2 + (local_LastSignificantCoeffY & 1)) + tmp_res2;
	}
	local_rc_scanIdx = rc_scanIdx;
	local_SCAN_VER = HevcDecoder_Algo_Parser_SCAN_VER;
	if (local_rc_scanIdx == local_SCAN_VER) {
		local_LastSignificantCoeffX = LastSignificantCoeffX;
		res[0] = local_LastSignificantCoeffX;
		local_LastSignificantCoeffY = LastSignificantCoeffY;
		LastSignificantCoeffX = local_LastSignificantCoeffY;
		tmp_res3 = res[0];
		LastSignificantCoeffY = tmp_res3;
	}
	local_LastSignificantCoeffX = LastSignificantCoeffX;
	x_cg_last_sig = local_LastSignificantCoeffX >> 2;
	local_LastSignificantCoeffY = LastSignificantCoeffY;
	y_cg_last_sig = local_LastSignificantCoeffY >> 2;
	local_rc_scanIdx = rc_scanIdx;
	if (local_rc_scanIdx == 0) {
		local_LastSignificantCoeffX = LastSignificantCoeffX;
		last_x_c = local_LastSignificantCoeffX & 3;
		local_LastSignificantCoeffY = LastSignificantCoeffY;
		last_y_c = local_LastSignificantCoeffY & 3;
		tmp_diag_scan4x4_inv = HevcDecoder_Algo_Parser_diag_scan4x4_inv[last_y_c][last_x_c];
		num_coeff = tmp_diag_scan4x4_inv;
		local_rc_log2TrafoSize = rc_log2TrafoSize;
		if (local_rc_log2TrafoSize == 3) {
			local_num_coeff = num_coeff;
			tmp_diag_scan2x2_inv = HevcDecoder_Algo_Parser_diag_scan2x2_inv[y_cg_last_sig][x_cg_last_sig];
			num_coeff = local_num_coeff + (tmp_diag_scan2x2_inv << 4);
		} else {
			local_rc_log2TrafoSize = rc_log2TrafoSize;
			if (local_rc_log2TrafoSize == 4) {
				local_num_coeff = num_coeff;
				tmp_diag_scan4x4_inv0 = HevcDecoder_Algo_Parser_diag_scan4x4_inv[y_cg_last_sig][x_cg_last_sig];
				num_coeff = local_num_coeff + (tmp_diag_scan4x4_inv0 << 4);
			} else {
				local_num_coeff = num_coeff;
				tmp_diag_scan8x8_inv = HevcDecoder_Algo_Parser_diag_scan8x8_inv[y_cg_last_sig][x_cg_last_sig];
				num_coeff = local_num_coeff + (tmp_diag_scan8x8_inv << 4);
			}
		}
	} else {
		local_rc_scanIdx = rc_scanIdx;
		if (local_rc_scanIdx == 1) {
			local_LastSignificantCoeffY = LastSignificantCoeffY;
			local_LastSignificantCoeffX = LastSignificantCoeffX;
			tmp_horiz_scan8x8_inv = HevcDecoder_Algo_Parser_horiz_scan8x8_inv[local_LastSignificantCoeffY][local_LastSignificantCoeffX];
			num_coeff = tmp_horiz_scan8x8_inv;
		} else {
			local_rc_scanIdx = rc_scanIdx;
			if (local_rc_scanIdx == 2) {
				local_LastSignificantCoeffX = LastSignificantCoeffX;
				local_LastSignificantCoeffY = LastSignificantCoeffY;
				tmp_horiz_scan8x8_inv0 = HevcDecoder_Algo_Parser_horiz_scan8x8_inv[local_LastSignificantCoeffX][local_LastSignificantCoeffY];
				num_coeff = tmp_horiz_scan8x8_inv0;
			}
		}
	}
	local_num_coeff = num_coeff;
	num_coeff = local_num_coeff + 1;
	local_num_coeff = num_coeff;
	rc_lastSubBlock = (local_num_coeff - 1) >> 4;
	local_num_coeff = num_coeff;
	local_rc_lastSubBlock = rc_lastSubBlock;
	rc_lastScanPos = local_num_coeff - (local_rc_lastSubBlock << 4) - 1;
	local_rc_lastSubBlock = rc_lastSubBlock;
	rc_i = local_rc_lastSubBlock;
	local_rc_cIdx = rc_cIdx;
	if (local_rc_cIdx == 0) {
	}
	tokens_TUSize[(index_TUSize % SIZE_TUSize) + (0)] = sz;
	tokens_TUSize[(index_TUSize % SIZE_TUSize) + (1)] = 0;
	tokens_TUSize[(index_TUSize % SIZE_TUSize) + (2)] = isDST;
	tokens_TUSize[(index_TUSize % SIZE_TUSize) + (3)] = transform_skip_flag;
	local_slice_qp = slice_qp;
	tokens_TUSize[(index_TUSize % SIZE_TUSize) + (4)] = local_slice_qp;
	local_rc_cIdx = rc_cIdx;
	tokens_TUSize[(index_TUSize % SIZE_TUSize) + (5)] = local_rc_cIdx;
	local_rc_cIdx = rc_cIdx;
	local_TEXT_CHROMA_U = HevcDecoder_Algo_Parser_TEXT_CHROMA_U;
	if (local_rc_cIdx == local_TEXT_CHROMA_U) {
		local_pps_id = pps_id;
		tmp_pps_cb_qp_offset0 = pps_cb_qp_offset[local_pps_id];
		local_slice_cb_qp_offset = slice_cb_qp_offset;
		tokens_TUSize[(index_TUSize % SIZE_TUSize) + (6)] = tmp_pps_cb_qp_offset0 + local_slice_cb_qp_offset;
	} else {
		local_pps_id = pps_id;
		tmp_pps_cr_qp_offset0 = pps_cr_qp_offset[local_pps_id];
		local_slice_cr_qp_offset = slice_cr_qp_offset;
		tokens_TUSize[(index_TUSize % SIZE_TUSize) + (6)] = tmp_pps_cr_qp_offset0 + local_slice_cr_qp_offset;
	}

	// Update ports indexes
	index_TUSize += 7;
	write_end_TUSize();

}
static i32 isSchedulable_read_ResidualCoding_for_numLastSubset_start() {
	i32 result;
	i32 tmp_isFifoFull;

	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	result = tmp_isFifoFull;
	return result;
}

static void read_ResidualCoding_for_numLastSubset_start() {

	i32 res[1];
	u8 n;
	u16 xC;
	u16 yC;
	u8 inferSigCoeffFlag;
	u8 local_rc_log2TrafoSize;
	u8 local_rc_scanIdx;
	i8 local_rc_i;
	u8 tmp_ScanOrder;
	u8 tmp_ScanOrder0;
	i8 local_rc_lastSubBlock;
	u16 local_rc_xS;
	u16 local_rc_yS;
	u8 local_rc_cIdx;
	i32 tmp_res;
	u8 local_LastSignificantCoeffX;
	u8 local_LastSignificantCoeffY;
	u8 local_rc_lastScanPos;
	i32 m;
	i8 local_m_end;
	u8 tmp_ScanOrder1;
	u8 tmp_ScanOrder2;
	u8 tmp_coded_sub_block_flag;
	i32 tmp_res0;
	u8 local_nb_significant_coeff_flag;
	u8 tmp_coded_sub_block_flag0;

	local_rc_log2TrafoSize = rc_log2TrafoSize;
	local_rc_scanIdx = rc_scanIdx;
	local_rc_i = rc_i;
	tmp_ScanOrder = ScanOrder[local_rc_log2TrafoSize - 2][local_rc_scanIdx][local_rc_i][0];
	rc_xS = tmp_ScanOrder;
	local_rc_log2TrafoSize = rc_log2TrafoSize;
	local_rc_scanIdx = rc_scanIdx;
	local_rc_i = rc_i;
	tmp_ScanOrder0 = ScanOrder[local_rc_log2TrafoSize - 2][local_rc_scanIdx][local_rc_i][1];
	rc_yS = tmp_ScanOrder0;
	inferSigCoeffFlag = 0;
	local_rc_i = rc_i;
	local_rc_lastSubBlock = rc_lastSubBlock;
	local_rc_i = rc_i;
	if (local_rc_i < local_rc_lastSubBlock && local_rc_i > 0) {
		local_rc_xS = rc_xS;
		local_rc_yS = rc_yS;
		local_rc_cIdx = rc_cIdx;
		local_rc_log2TrafoSize = rc_log2TrafoSize;
		HevcDecoder_Algo_Parser_get_CODED_SUB_BLOCK_FLAG(codIRange, codIOffset, ctxTable, fifo, res, coded_sub_block_flag, local_rc_xS, local_rc_yS, local_rc_cIdx, local_rc_log2TrafoSize);
		local_rc_xS = rc_xS;
		local_rc_yS = rc_yS;
		tmp_res = res[0];
		coded_sub_block_flag[local_rc_xS][local_rc_yS] = tmp_res;
		inferSigCoeffFlag = 1;
	} else {
		local_rc_xS = rc_xS;
		local_LastSignificantCoeffX = LastSignificantCoeffX;
		local_rc_yS = rc_yS;
		local_LastSignificantCoeffY = LastSignificantCoeffY;
		local_rc_xS = rc_xS;
		local_rc_yS = rc_yS;
		if (local_rc_xS == local_LastSignificantCoeffX >> 2 && local_rc_yS == local_LastSignificantCoeffY >> 2 || local_rc_xS == 0 && local_rc_yS == 0) {
			local_rc_xS = rc_xS;
			local_rc_yS = rc_yS;
			coded_sub_block_flag[local_rc_xS][local_rc_yS] = 1;
		}
	}
	m_end = 15;
	nb_significant_coeff_flag = 0;
	local_rc_i = rc_i;
	local_rc_lastSubBlock = rc_lastSubBlock;
	if (local_rc_i == local_rc_lastSubBlock) {
		local_rc_lastScanPos = rc_lastScanPos;
		m_end = local_rc_lastScanPos - 1;
		local_rc_lastScanPos = rc_lastScanPos;
		significant_coeff_flag_idx[0] = local_rc_lastScanPos;
		nb_significant_coeff_flag = 1;
	}
	m = 0;
	local_m_end = m_end;
	while (m <= local_m_end) {
		local_m_end = m_end;
		n = local_m_end - m;
		local_rc_xS = rc_xS;
		local_rc_scanIdx = rc_scanIdx;
		tmp_ScanOrder1 = ScanOrder[2][local_rc_scanIdx][n][0];
		xC = (local_rc_xS << 2) + tmp_ScanOrder1;
		local_rc_yS = rc_yS;
		local_rc_scanIdx = rc_scanIdx;
		tmp_ScanOrder2 = ScanOrder[2][local_rc_scanIdx][n][1];
		yC = (local_rc_yS << 2) + tmp_ScanOrder2;
		local_rc_xS = rc_xS;
		local_rc_yS = rc_yS;
		tmp_coded_sub_block_flag = coded_sub_block_flag[local_rc_xS][local_rc_yS];
		if (tmp_coded_sub_block_flag == 1 && (n > 0 || inferSigCoeffFlag == 0)) {
			local_rc_cIdx = rc_cIdx;
			local_rc_log2TrafoSize = rc_log2TrafoSize;
			local_rc_scanIdx = rc_scanIdx;
			HevcDecoder_Algo_Parser_get_SIGNIFICANT_COEFF_FLAG(codIRange, codIOffset, ctxTable, fifo, res, coded_sub_block_flag, xC, yC, local_rc_cIdx, local_rc_log2TrafoSize, local_rc_scanIdx);
			tmp_res0 = res[0];
			if (tmp_res0 == 1) {
				local_nb_significant_coeff_flag = nb_significant_coeff_flag;
				significant_coeff_flag_idx[local_nb_significant_coeff_flag] = n;
				local_nb_significant_coeff_flag = nb_significant_coeff_flag;
				nb_significant_coeff_flag = local_nb_significant_coeff_flag + 1;
				inferSigCoeffFlag = 0;
			}
		} else {
			local_LastSignificantCoeffX = LastSignificantCoeffX;
			local_LastSignificantCoeffY = LastSignificantCoeffY;
			local_rc_xS = rc_xS;
			local_rc_yS = rc_yS;
			tmp_coded_sub_block_flag0 = coded_sub_block_flag[local_rc_xS][local_rc_yS];
			if (xC == local_LastSignificantCoeffX && yC == local_LastSignificantCoeffY || (xC & 3) == 0 && (yC & 3) == 0 && inferSigCoeffFlag == 1 && tmp_coded_sub_block_flag0 == 1) {
				local_nb_significant_coeff_flag = nb_significant_coeff_flag;
				significant_coeff_flag_idx[local_nb_significant_coeff_flag] = n;
				local_nb_significant_coeff_flag = nb_significant_coeff_flag;
				nb_significant_coeff_flag = local_nb_significant_coeff_flag + 1;
			}
		}
		m = m + 1;
	}
	local_nb_significant_coeff_flag = nb_significant_coeff_flag;
	m_end = local_nb_significant_coeff_flag - 1;

	// Update ports indexes

}
static i32 isSchedulable_read_ResidualCoding_end_xIT4() {
	i32 result;
	i8 local_rc_i;
	u8 local_rc_log2TrafoSize;

	local_rc_i = rc_i;
	local_rc_log2TrafoSize = rc_log2TrafoSize;
	result = local_rc_i < 0 && local_rc_log2TrafoSize == 2;
	return result;
}

static void read_ResidualCoding_end_xIT4() {

	i32 local_DEBUG_CABAC;
	i32 i;
	i16 tmp_tabTransCoeffLevel;

	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
		printf("read_ResidualCoding_end\n");
	}
	i = 0;
	while (i <= 4 * 4 - 1) {
		tmp_tabTransCoeffLevel = tabTransCoeffLevel[i];
		tokens_Coeff[(index_Coeff + (i)) % SIZE_Coeff] = tmp_tabTransCoeffLevel;
		i = i + 1;
	}

	// Update ports indexes
	index_Coeff += 16;
	write_end_Coeff();

}
static void read_ResidualCoding_end_xIT4_aligned() {

	i32 local_DEBUG_CABAC;
	i32 i;
	i16 tmp_tabTransCoeffLevel;

	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
		printf("read_ResidualCoding_end\n");
	}
	i = 0;
	while (i <= 4 * 4 - 1) {
		tmp_tabTransCoeffLevel = tabTransCoeffLevel[i];
		tokens_Coeff[(index_Coeff % SIZE_Coeff) + (i)] = tmp_tabTransCoeffLevel;
		i = i + 1;
	}

	// Update ports indexes
	index_Coeff += 16;
	write_end_Coeff();

}
static i32 isSchedulable_read_ResidualCoding_end_xIT8() {
	i32 result;
	i8 local_rc_i;
	u8 local_rc_log2TrafoSize;

	local_rc_i = rc_i;
	local_rc_log2TrafoSize = rc_log2TrafoSize;
	result = local_rc_i < 0 && local_rc_log2TrafoSize == 3;
	return result;
}

static void read_ResidualCoding_end_xIT8() {

	i32 local_DEBUG_CABAC;
	i32 i;
	i16 tmp_tabTransCoeffLevel;

	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
		printf("read_ResidualCoding_end\n");
	}
	i = 0;
	while (i <= 8 * 8 - 1) {
		tmp_tabTransCoeffLevel = tabTransCoeffLevel[i];
		tokens_Coeff[(index_Coeff + (i)) % SIZE_Coeff] = tmp_tabTransCoeffLevel;
		i = i + 1;
	}

	// Update ports indexes
	index_Coeff += 64;
	write_end_Coeff();

}
static void read_ResidualCoding_end_xIT8_aligned() {

	i32 local_DEBUG_CABAC;
	i32 i;
	i16 tmp_tabTransCoeffLevel;

	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
		printf("read_ResidualCoding_end\n");
	}
	i = 0;
	while (i <= 8 * 8 - 1) {
		tmp_tabTransCoeffLevel = tabTransCoeffLevel[i];
		tokens_Coeff[(index_Coeff % SIZE_Coeff) + (i)] = tmp_tabTransCoeffLevel;
		i = i + 1;
	}

	// Update ports indexes
	index_Coeff += 64;
	write_end_Coeff();

}
static i32 isSchedulable_read_ResidualCoding_end_xIT16() {
	i32 result;
	i8 local_rc_i;
	u8 local_rc_log2TrafoSize;

	local_rc_i = rc_i;
	local_rc_log2TrafoSize = rc_log2TrafoSize;
	result = local_rc_i < 0 && local_rc_log2TrafoSize == 4;
	return result;
}

static void read_ResidualCoding_end_xIT16() {

	i32 local_DEBUG_CABAC;
	i32 i;
	i16 tmp_tabTransCoeffLevel;

	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
		printf("read_ResidualCoding_end\n");
	}
	i = 0;
	while (i <= 16 * 16 - 1) {
		tmp_tabTransCoeffLevel = tabTransCoeffLevel[i];
		tokens_Coeff[(index_Coeff + (i)) % SIZE_Coeff] = tmp_tabTransCoeffLevel;
		i = i + 1;
	}

	// Update ports indexes
	index_Coeff += 256;
	write_end_Coeff();

}
static void read_ResidualCoding_end_xIT16_aligned() {

	i32 local_DEBUG_CABAC;
	i32 i;
	i16 tmp_tabTransCoeffLevel;

	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
		printf("read_ResidualCoding_end\n");
	}
	i = 0;
	while (i <= 16 * 16 - 1) {
		tmp_tabTransCoeffLevel = tabTransCoeffLevel[i];
		tokens_Coeff[(index_Coeff % SIZE_Coeff) + (i)] = tmp_tabTransCoeffLevel;
		i = i + 1;
	}

	// Update ports indexes
	index_Coeff += 256;
	write_end_Coeff();

}
static i32 isSchedulable_read_ResidualCoding_end_xIT32() {
	i32 result;
	i8 local_rc_i;
	u8 local_rc_log2TrafoSize;

	local_rc_i = rc_i;
	local_rc_log2TrafoSize = rc_log2TrafoSize;
	result = local_rc_i < 0 && local_rc_log2TrafoSize == 5;
	return result;
}

static void read_ResidualCoding_end_xIT32() {

	i32 local_DEBUG_CABAC;
	i32 i;
	i16 tmp_tabTransCoeffLevel;

	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
		printf("read_ResidualCoding_end\n");
	}
	i = 0;
	while (i <= 32 * 32 - 1) {
		tmp_tabTransCoeffLevel = tabTransCoeffLevel[i];
		tokens_Coeff[(index_Coeff + (i)) % SIZE_Coeff] = tmp_tabTransCoeffLevel;
		i = i + 1;
	}

	// Update ports indexes
	index_Coeff += 1024;
	write_end_Coeff();

}
static void read_ResidualCoding_end_xIT32_aligned() {

	i32 local_DEBUG_CABAC;
	i32 i;
	i16 tmp_tabTransCoeffLevel;

	local_DEBUG_CABAC = HevcDecoder_Algo_Parser_DEBUG_CABAC;
	if (local_DEBUG_CABAC) {
		printf("read_ResidualCoding_end\n");
	}
	i = 0;
	while (i <= 32 * 32 - 1) {
		tmp_tabTransCoeffLevel = tabTransCoeffLevel[i];
		tokens_Coeff[(index_Coeff % SIZE_Coeff) + (i)] = tmp_tabTransCoeffLevel;
		i = i + 1;
	}

	// Update ports indexes
	index_Coeff += 1024;
	write_end_Coeff();

}
static i32 isSchedulable_read_ResidualCoding_for_numLastSubset_get_COEFF_ABS_LEVEL_GREATER1_FLAG() {
	i32 result;
	i32 tmp_isFifoFull;

	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	result = tmp_isFifoFull;
	return result;
}

static void read_ResidualCoding_for_numLastSubset_get_COEFF_ABS_LEVEL_GREATER1_FLAG() {

	i32 res[1];
	i32 n;
	i8 lastSigScanPos;
	u8 numGreater1Flag;
	u16 ctxIdxInc[1];
	i32 i;
	i32 m;
	i8 local_m_end;
	u8 local_rc_cIdx;
	i8 local_rc_i;
	i8 local_rc_lastSubBlock;
	u16 tmp_ctxIdxInc;
	i32 tmp_res;
	u8 tmp_rc_greater1Ctx;
	u8 tmp_rc_greater1Ctx0;
	u8 tmp_rc_greater1Ctx1;
	i32 tmp_res0;
	u8 tmp_coeff_abs_level_greater1_flag;
	i8 local_rc_firstGreater1ScanPos;
	u8 local_rc_firstSigScanPos;
	u8 local_cu_transquant_bypass_flag;
	u8 tmp_rc_ctxSet;
	i32 tmp_res1;
	u16 local_pps_id;
	u8 tmp_pps_sign_data_hiding_flag;
	u8 local_rc_signHidden;
	u8 local_nb_significant_coeff_flag;
	i32 tmp_res2;
	i32 tmp_res3;

	res[0] = 0;
	lastSigScanPos = -1;
	numGreater1Flag = 0;
	rc_firstSigScanPos = 16;
	rc_firstGreater1ScanPos = -1;
	i = 0;
	while (i <= 15) {
		coeff_abs_level_greater1_flag[i] = 0;
		i = i + 1;
	}
	m = 0;
	local_m_end = m_end;
	while (m <= local_m_end) {
		n = significant_coeff_flag_idx[m];
		if (numGreater1Flag < 8) {
			local_rc_cIdx = rc_cIdx;
			local_rc_i = rc_i;
			local_rc_i = rc_i;
			local_rc_lastSubBlock = rc_lastSubBlock;
			HevcDecoder_Algo_Parser_context_93315(local_rc_cIdx, local_rc_i, numGreater1Flag == 0, local_rc_i == local_rc_lastSubBlock, rc_ctxSet, rc_greater1Ctx, ctxIdxInc);
			tmp_ctxIdxInc = ctxIdxInc[0];
			HevcDecoder_Algo_Parser_get_COEFF_ABS_LEVEL_GREATER1_FLAG(codIRange, codIOffset, ctxTable, fifo, res, tmp_ctxIdxInc);
			tmp_res = res[0];
			if (tmp_res == 1) {
				rc_greater1Ctx[0] = 0;
			} else {
				tmp_rc_greater1Ctx = rc_greater1Ctx[0];
				tmp_rc_greater1Ctx0 = rc_greater1Ctx[0];
				if (tmp_rc_greater1Ctx > 0 && tmp_rc_greater1Ctx0 < 3) {
					tmp_rc_greater1Ctx1 = rc_greater1Ctx[0];
					rc_greater1Ctx[0] = tmp_rc_greater1Ctx1 + 1;
				}
			}
			tmp_res0 = res[0];
			coeff_abs_level_greater1_flag[n] = tmp_res0;
			numGreater1Flag = numGreater1Flag + 1;
			tmp_coeff_abs_level_greater1_flag = coeff_abs_level_greater1_flag[n];
			local_rc_firstGreater1ScanPos = rc_firstGreater1ScanPos;
			if (tmp_coeff_abs_level_greater1_flag == 1 && local_rc_firstGreater1ScanPos == -1) {
				rc_firstGreater1ScanPos = n;
			}
		}
		if (lastSigScanPos == -1) {
			lastSigScanPos = n;
		}
		rc_firstSigScanPos = n;
		m = m + 1;
	}
	local_rc_firstSigScanPos = rc_firstSigScanPos;
	local_cu_transquant_bypass_flag = cu_transquant_bypass_flag;
	if (lastSigScanPos - local_rc_firstSigScanPos > 3 && local_cu_transquant_bypass_flag == 0) {
		rc_signHidden = 1;
	} else {
		rc_signHidden = 0;
	}
	local_rc_firstGreater1ScanPos = rc_firstGreater1ScanPos;
	if (local_rc_firstGreater1ScanPos != -1) {
		local_rc_cIdx = rc_cIdx;
		tmp_rc_ctxSet = rc_ctxSet[0];
		HevcDecoder_Algo_Parser_get_COEFF_ABS_LEVEL_GREATER2_FLAG(codIRange, codIOffset, ctxTable, fifo, res, local_rc_cIdx, tmp_rc_ctxSet);
		tmp_res1 = res[0];
		coeff_abs_level_greater2_flag = tmp_res1;
	}
	local_pps_id = pps_id;
	tmp_pps_sign_data_hiding_flag = pps_sign_data_hiding_flag[local_pps_id];
	local_rc_signHidden = rc_signHidden;
	if (tmp_pps_sign_data_hiding_flag == 0 || local_rc_signHidden == 0) {
		local_nb_significant_coeff_flag = nb_significant_coeff_flag;
		HevcDecoder_Algo_Parser_get_COEFF_SIGN_FLAG(codIRange, codIOffset, fifo, res, local_nb_significant_coeff_flag);
		tmp_res2 = res[0];
		local_nb_significant_coeff_flag = nb_significant_coeff_flag;
		coeff_sign_flag = tmp_res2 << (16 - local_nb_significant_coeff_flag);
	} else {
		local_nb_significant_coeff_flag = nb_significant_coeff_flag;
		HevcDecoder_Algo_Parser_get_COEFF_SIGN_FLAG(codIRange, codIOffset, fifo, res, local_nb_significant_coeff_flag - 1);
		tmp_res3 = res[0];
		local_nb_significant_coeff_flag = nb_significant_coeff_flag;
		coeff_sign_flag = tmp_res3 << (16 - (local_nb_significant_coeff_flag - 1));
	}
	rc_numSigCoeff = 0;
	rc_sumAbsLevel = 0;
	rc_cLastRiceParam = 0;
	rc_m = 0;

	// Update ports indexes

}
static i32 isSchedulable_read_ResidualCoding_for_numLastSubset_get_COEFF_ABS_LEVEL() {
	i32 result;
	i32 tmp_isFifoFull;

	tmp_isFifoFull = HevcDecoder_Algo_Parser_isFifoFull(fifo);
	result = tmp_isFifoFull;
	return result;
}

static void read_ResidualCoding_for_numLastSubset_get_COEFF_ABS_LEVEL() {

	i32 res[1];
	i8 local_rc_m;
	i32 n;
	i16 transCoeffLevel;
	i32 pos;
	u16 xC;
	u16 yC;
	u16 local_rc_xS;
	u8 local_rc_scanIdx;
	u8 tmp_ScanOrder;
	u16 local_rc_yS;
	u8 tmp_ScanOrder0;
	u8 tmp_coeff_abs_level_greater1_flag;
	i8 local_rc_firstGreater1ScanPos;
	u8 tmp_if;
	u8 local_coeff_abs_level_greater2_flag;
	u8 local_rc_numSigCoeff;
	u8 tmp_if0;
	u8 local_rc_cLastRiceParam;
	i32 tmp_res;
	u16 tmp_if1;
	i32 tmp_min;
	u16 local_pps_id;
	u8 tmp_pps_sign_data_hiding_flag;
	u8 local_rc_signHidden;
	u8 local_rc_sumAbsLevel;
	u8 local_rc_firstSigScanPos;
	u16 local_coeff_sign_flag;
	u8 local_cu_transquant_bypass_flag;
	u16 local_sps_id;
	u8 tmp_sps_scaling_list_enabled_flag;
	u8 local_rc_log2TrafoSize;
	u8 tmp_scale_matrix;
	i32 local_dc_scale;
	i32 local_scale_m;
	i32 local_scale;
	i32 local_add;
	u8 local_shift;

	res[0] = 0;
	local_rc_m = rc_m;
	n = significant_coeff_flag_idx[local_rc_m];
	transCoeffLevel = 0;
	local_rc_xS = rc_xS;
	local_rc_scanIdx = rc_scanIdx;
	tmp_ScanOrder = ScanOrder[2][local_rc_scanIdx][n][0];
	xC = (local_rc_xS << 2) + tmp_ScanOrder;
	local_rc_yS = rc_yS;
	local_rc_scanIdx = rc_scanIdx;
	tmp_ScanOrder0 = ScanOrder[2][local_rc_scanIdx][n][1];
	yC = (local_rc_yS << 2) + tmp_ScanOrder0;
	tmp_coeff_abs_level_greater1_flag = coeff_abs_level_greater1_flag[n];
	local_rc_firstGreater1ScanPos = rc_firstGreater1ScanPos;
	if (n == local_rc_firstGreater1ScanPos) {
		local_coeff_abs_level_greater2_flag = coeff_abs_level_greater2_flag;
		tmp_if = local_coeff_abs_level_greater2_flag;
	} else {
		tmp_if = 0;
	}
	transCoeffLevel = 1 + tmp_coeff_abs_level_greater1_flag + tmp_if;
	local_rc_numSigCoeff = rc_numSigCoeff;
	if (local_rc_numSigCoeff < 8) {
		local_rc_firstGreater1ScanPos = rc_firstGreater1ScanPos;
		if (n == local_rc_firstGreater1ScanPos) {
			tmp_if0 = 3;
		} else {
			tmp_if0 = 2;
		}
	} else {
		tmp_if0 = 1;
	}
	if (transCoeffLevel == tmp_if0) {
		local_rc_cLastRiceParam = rc_cLastRiceParam;
		HevcDecoder_Algo_Parser_get_COEFF_ABS_LEVEL(codIRange, codIOffset, fifo, res, local_rc_cLastRiceParam);
		tmp_res = res[0];
		transCoeffLevel = transCoeffLevel + tmp_res;
		local_rc_cLastRiceParam = rc_cLastRiceParam;
		if (transCoeffLevel > 3 * (1 << local_rc_cLastRiceParam)) {
			local_rc_cLastRiceParam = rc_cLastRiceParam;
			tmp_if1 = local_rc_cLastRiceParam + 1;
		} else {
			local_rc_cLastRiceParam = rc_cLastRiceParam;
			tmp_if1 = local_rc_cLastRiceParam;
		}
		tmp_min = HevcDecoder_Algo_Parser_min(tmp_if1, 4);
		rc_cLastRiceParam = tmp_min;
	}
	local_pps_id = pps_id;
	tmp_pps_sign_data_hiding_flag = pps_sign_data_hiding_flag[local_pps_id];
	local_rc_signHidden = rc_signHidden;
	if (tmp_pps_sign_data_hiding_flag == 1 && local_rc_signHidden == 1) {
		local_rc_sumAbsLevel = rc_sumAbsLevel;
		rc_sumAbsLevel = local_rc_sumAbsLevel + transCoeffLevel;
		local_rc_firstSigScanPos = rc_firstSigScanPos;
		local_rc_sumAbsLevel = rc_sumAbsLevel;
		if (n == local_rc_firstSigScanPos && (local_rc_sumAbsLevel & 1) == 1) {
			transCoeffLevel = -transCoeffLevel;
		}
	}
	local_coeff_sign_flag = coeff_sign_flag;
	if (local_coeff_sign_flag >> 15 == 1) {
		transCoeffLevel = -transCoeffLevel;
	}
	local_coeff_sign_flag = coeff_sign_flag;
	coeff_sign_flag = local_coeff_sign_flag << 1;
	local_cu_transquant_bypass_flag = cu_transquant_bypass_flag;
	if (local_cu_transquant_bypass_flag == 0) {
		local_sps_id = sps_id;
		tmp_sps_scaling_list_enabled_flag = sps_scaling_list_enabled_flag[local_sps_id];
		if (tmp_sps_scaling_list_enabled_flag == 1) {
			local_rc_log2TrafoSize = rc_log2TrafoSize;
			if (yC != 0 || xC != 0 || local_rc_log2TrafoSize < 4) {
				local_rc_log2TrafoSize = rc_log2TrafoSize;
				if (local_rc_log2TrafoSize == 3) {
					pos = (yC << 3) + xC;
				} else {
					local_rc_log2TrafoSize = rc_log2TrafoSize;
					if (local_rc_log2TrafoSize == 4) {
						pos = ((yC >> 1) << 3) + (xC >> 1);
					} else {
						local_rc_log2TrafoSize = rc_log2TrafoSize;
						if (local_rc_log2TrafoSize == 5) {
							pos = ((yC >> 2) << 3) + (xC >> 2);
						} else {
							pos = (yC << 2) + xC;
						}
					}
				}
				tmp_scale_matrix = scale_matrix[pos];
				scale_m = tmp_scale_matrix;
			} else {
				local_dc_scale = dc_scale;
				scale_m = local_dc_scale;
			}
		}
		local_scale_m = scale_m;
		local_scale = scale;
		local_add = add;
		local_shift = shift;
		transCoeffLevel = HevcDecoder_Algo_Parser_clip_i32((transCoeffLevel * local_scale_m * local_scale + local_add) >> local_shift, -32768, 32767);
	}
	local_rc_log2TrafoSize = rc_log2TrafoSize;
	tabTransCoeffLevel[xC + (1 << local_rc_log2TrafoSize) * yC] = transCoeffLevel;
	local_rc_numSigCoeff = rc_numSigCoeff;
	rc_numSigCoeff = local_rc_numSigCoeff + 1;
	local_rc_m = rc_m;
	rc_m = local_rc_m + 1;

	// Update ports indexes

}
static i32 isSchedulable_read_ResidualCoding_for_numLastSubset_get_COEFF_ABS_LEVEL_end() {
	i32 result;
	i8 local_rc_m;
	i8 local_m_end;

	local_rc_m = rc_m;
	local_m_end = m_end;
	result = local_rc_m > local_m_end;
	return result;
}

static void read_ResidualCoding_for_numLastSubset_get_COEFF_ABS_LEVEL_end() {

	i8 local_rc_i;

	local_rc_i = rc_i;
	rc_i = local_rc_i - 1;

	// Update ports indexes

}

////////////////////////////////////////////////////////////////////////////////
// Initializes

void HevcDecoder_Algo_Parser_initialize(schedinfo_t *si) {
	int i = 0;
	write_CUInfo();
	write_IntraPredMode();
	write_SliceAddr();
	write_TilesCoord();
	write_LcuSizeMax();
	write_PartMode();
	write_IsPicSlcLcu();
	write_IsPicSlc();
	write_LFAcrossSlcTile();
	write_PictSize();
	write_Poc();
	write_SaoSe();
	write_SEI_MD5();
	write_SliceType();
	write_SplitTransform();
	write_TUSize();
	write_Coeff();
	write_StrongIntraSmoothing();
	write_DispCoord();
	write_PicSizeInMb();
	write_NumRefIdxLxActive();
	write_RefPicListModif();
	write_RefPoc();
	write_MvPredSyntaxElem();
	write_Cbf();
	write_DBFDisable();
	write_DbfSe();
	write_ReorderPics();
	write_WeightedPred();
	write_Qp();
	/* Set initial state to current FSM state */
	_FSM_state = my_state_start_code;
finished:
	write_end_CUInfo();
	write_end_IntraPredMode();
	write_end_SliceAddr();
	write_end_TilesCoord();
	write_end_LcuSizeMax();
	write_end_PartMode();
	write_end_IsPicSlcLcu();
	write_end_IsPicSlc();
	write_end_LFAcrossSlcTile();
	write_end_PictSize();
	write_end_Poc();
	write_end_SaoSe();
	write_end_SEI_MD5();
	write_end_SliceType();
	write_end_SplitTransform();
	write_end_TUSize();
	write_end_Coeff();
	write_end_StrongIntraSmoothing();
	write_end_DispCoord();
	write_end_PicSizeInMb();
	write_end_NumRefIdxLxActive();
	write_end_RefPicListModif();
	write_end_RefPoc();
	write_end_MvPredSyntaxElem();
	write_end_Cbf();
	write_end_DBFDisable();
	write_end_DbfSe();
	write_end_ReorderPics();
	write_end_WeightedPred();
	write_end_Qp();
	return;
}

////////////////////////////////////////////////////////////////////////////////
// Action scheduler
void HevcDecoder_Algo_Parser_outside_FSM_scheduler(schedinfo_t *si) {
	int i = 0;
	while (1) {
		if (numTokens_byte - index_byte >= 1 && isSchedulable_untagged_0()) {
			untagged_0();
			i++;
		} else {
			si->num_firings = i;
			si->reason = starved;
			goto finished;
		}
	}
finished:
	// no read_end/write_end here!
	return;
}

void HevcDecoder_Algo_Parser_scheduler(schedinfo_t *si) {
	int i = 0;

	read_byte();
	write_CUInfo();
	write_IntraPredMode();
	write_SliceAddr();
	write_TilesCoord();
	write_LcuSizeMax();
	write_PartMode();
	write_IsPicSlcLcu();
	write_IsPicSlc();
	write_LFAcrossSlcTile();
	write_PictSize();
	write_Poc();
	write_SaoSe();
	write_SEI_MD5();
	write_SliceType();
	write_SplitTransform();
	write_TUSize();
	write_Coeff();
	write_StrongIntraSmoothing();
	write_DispCoord();
	write_PicSizeInMb();
	write_NumRefIdxLxActive();
	write_RefPicListModif();
	write_RefPoc();
	write_MvPredSyntaxElem();
	write_Cbf();
	write_DBFDisable();
	write_DbfSe();
	write_ReorderPics();
	write_WeightedPred();
	write_Qp();

	// jump to FSM state
	switch (_FSM_state) {
	case my_state_byte_align:
		goto l_byte_align;
	case my_state_find_header:
		goto l_find_header;
	case my_state_read_CodingQuadTree:
		goto l_read_CodingQuadTree;
	case my_state_read_CodingTree:
		goto l_read_CodingTree;
	case my_state_read_CodingUnit:
		goto l_read_CodingUnit;
	case my_state_read_MVDCoding:
		goto l_read_MVDCoding;
	case my_state_read_MVDCoding_end:
		goto l_read_MVDCoding_end;
	case my_state_read_Nal_unit_header:
		goto l_read_Nal_unit_header;
	case my_state_read_PCMSample:
		goto l_read_PCMSample;
	case my_state_read_PCMSampleLoop:
		goto l_read_PCMSampleLoop;
	case my_state_read_PPS_Header:
		goto l_read_PPS_Header;
	case my_state_read_PredictionUnit:
		goto l_read_PredictionUnit;
	case my_state_read_ResidualCoding:
		goto l_read_ResidualCoding;
	case my_state_read_ResidualCodingGetCoeff:
		goto l_read_ResidualCodingGetCoeff;
	case my_state_read_ResidualCodingGreater1:
		goto l_read_ResidualCodingGreater1;
	case my_state_read_ResidualCodingStart:
		goto l_read_ResidualCodingStart;
	case my_state_read_SEI_Header:
		goto l_read_SEI_Header;
	case my_state_read_SPS_Header:
		goto l_read_SPS_Header;
	case my_state_read_SaoParam:
		goto l_read_SaoParam;
	case my_state_read_SliceData:
		goto l_read_SliceData;
	case my_state_read_SliceHeader:
		goto l_read_SliceHeader;
	case my_state_read_TransformTree:
		goto l_read_TransformTree;
	case my_state_read_TransformUnit:
		goto l_read_TransformUnit;
	case my_state_read_VPS_Header:
		goto l_read_VPS_Header;
	case my_state_sendQp:
		goto l_sendQp;
	case my_state_send_IntraPredMode:
		goto l_send_IntraPredMode;
	case my_state_start_code:
		goto l_start_code;
	case my_state_weightedChroma0:
		goto l_weightedChroma0;
	case my_state_weightedChroma0Offset:
		goto l_weightedChroma0Offset;
	case my_state_weightedChroma1:
		goto l_weightedChroma1;
	case my_state_weightedChroma1Offset:
		goto l_weightedChroma1Offset;
	case my_state_weightedDeltaChroma0:
		goto l_weightedDeltaChroma0;
	case my_state_weightedDeltaChroma1:
		goto l_weightedDeltaChroma1;
	case my_state_weightedDeltaLuma0:
		goto l_weightedDeltaLuma0;
	case my_state_weightedDeltaLuma1:
		goto l_weightedDeltaLuma1;
	case my_state_weightedLuma0:
		goto l_weightedLuma0;
	case my_state_weightedLuma1:
		goto l_weightedLuma1;
	default:
		printf("unknown state in HevcDecoder_Algo_Parser.c : %s\n", stateNames[_FSM_state]);
		exit(1);
	}

	// FSM transitions
l_byte_align:
	HevcDecoder_Algo_Parser_outside_FSM_scheduler(si);
	i += si->num_firings;
	if (isSchedulable_byte_align_a()) {
		byte_align_a();
		i++;
		goto l_start_code;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_byte_align;
		goto finished;
	}
l_find_header:
	HevcDecoder_Algo_Parser_outside_FSM_scheduler(si);
	i += si->num_firings;
	if (isSchedulable_look_for_VPS_header()) {
		look_for_VPS_header();
		i++;
		goto l_read_VPS_Header;
	} else if (isSchedulable_look_for_SEI_header()) {
		look_for_SEI_header();
		i++;
		goto l_read_SEI_Header;
	} else if (isSchedulable_look_for_SPS_header()) {
		look_for_SPS_header();
		i++;
		goto l_read_SPS_Header;
	} else if (isSchedulable_look_for_PPS_header()) {
		look_for_PPS_header();
		i++;
		goto l_read_PPS_Header;
	} else if (isSchedulable_look_for_Slice_header()) {
		look_for_Slice_header();
		i++;
		goto l_read_SliceHeader;
	} else if (isSchedulable_look_for_other_header()) {
		look_for_other_header();
		i++;
		goto l_byte_align;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_find_header;
		goto finished;
	}
l_read_CodingQuadTree:
	HevcDecoder_Algo_Parser_outside_FSM_scheduler(si);
	i += si->num_firings;
	if (isSchedulable_read_CodingQuadTree_start()) {
		read_CodingQuadTree_start();
		i++;
		goto l_read_CodingQuadTree;
	} else if (isSchedulable_read_CodingQuadTree_case1()) {
		read_CodingQuadTree_case1();
		i++;
		goto l_read_CodingQuadTree;
	} else if (isSchedulable_read_CodingQuadTree_case2()) {
		read_CodingQuadTree_case2();
		i++;
		goto l_read_CodingQuadTree;
	} else if (isSchedulable_read_CodingQuadTree_noCase2()) {
		int stop = 0;
		if (5 > SIZE_CUInfo - index_CUInfo + HevcDecoder_Algo_Parser_CUInfo->read_inds[0]) {
			stop = 1;
		}
		if (5 > SIZE_CUInfo - index_CUInfo + HevcDecoder_Algo_Parser_CUInfo->read_inds[1]) {
			stop = 1;
		}
		if (5 > SIZE_CUInfo - index_CUInfo + HevcDecoder_Algo_Parser_CUInfo->read_inds[2]) {
			stop = 1;
		}
		if (5 > SIZE_CUInfo - index_CUInfo + HevcDecoder_Algo_Parser_CUInfo->read_inds[3]) {
			stop = 1;
		}
		if (5 > SIZE_CUInfo - index_CUInfo + HevcDecoder_Algo_Parser_CUInfo->read_inds[4]) {
			stop = 1;
		}
		if (1 > SIZE_PartMode - index_PartMode + HevcDecoder_Algo_Parser_PartMode->read_inds[0]) {
			stop = 1;
		}
		if (1 > SIZE_PartMode - index_PartMode + HevcDecoder_Algo_Parser_PartMode->read_inds[1]) {
			stop = 1;
		}
		if (1 > SIZE_PartMode - index_PartMode + HevcDecoder_Algo_Parser_PartMode->read_inds[2]) {
			stop = 1;
		}
		if (1 > SIZE_PartMode - index_PartMode + HevcDecoder_Algo_Parser_PartMode->read_inds[3]) {
			stop = 1;
		}
		if (1 > SIZE_PartMode - index_PartMode + HevcDecoder_Algo_Parser_PartMode->read_inds[4]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_read_CodingQuadTree;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		{
			int isAligned = 1;
			isAligned &= ((index_CUInfo % SIZE_CUInfo) < ((index_CUInfo + 5) % SIZE_CUInfo));
			if (isAligned) {
				read_CodingQuadTree_noCase2_aligned();
			} else {
				read_CodingQuadTree_noCase2();
			}
		}
		i++;
		goto l_read_CodingQuadTree;
	} else if (isSchedulable_read_CodingQuadTree_case3()) {
		read_CodingQuadTree_case3();
		i++;
		goto l_read_CodingQuadTree;
	} else if (isSchedulable_read_CodingQuadTree_noCase3()) {
		int stop = 0;
		if (5 > SIZE_CUInfo - index_CUInfo + HevcDecoder_Algo_Parser_CUInfo->read_inds[0]) {
			stop = 1;
		}
		if (5 > SIZE_CUInfo - index_CUInfo + HevcDecoder_Algo_Parser_CUInfo->read_inds[1]) {
			stop = 1;
		}
		if (5 > SIZE_CUInfo - index_CUInfo + HevcDecoder_Algo_Parser_CUInfo->read_inds[2]) {
			stop = 1;
		}
		if (5 > SIZE_CUInfo - index_CUInfo + HevcDecoder_Algo_Parser_CUInfo->read_inds[3]) {
			stop = 1;
		}
		if (5 > SIZE_CUInfo - index_CUInfo + HevcDecoder_Algo_Parser_CUInfo->read_inds[4]) {
			stop = 1;
		}
		if (1 > SIZE_PartMode - index_PartMode + HevcDecoder_Algo_Parser_PartMode->read_inds[0]) {
			stop = 1;
		}
		if (1 > SIZE_PartMode - index_PartMode + HevcDecoder_Algo_Parser_PartMode->read_inds[1]) {
			stop = 1;
		}
		if (1 > SIZE_PartMode - index_PartMode + HevcDecoder_Algo_Parser_PartMode->read_inds[2]) {
			stop = 1;
		}
		if (1 > SIZE_PartMode - index_PartMode + HevcDecoder_Algo_Parser_PartMode->read_inds[3]) {
			stop = 1;
		}
		if (1 > SIZE_PartMode - index_PartMode + HevcDecoder_Algo_Parser_PartMode->read_inds[4]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_read_CodingQuadTree;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		{
			int isAligned = 1;
			isAligned &= ((index_CUInfo % SIZE_CUInfo) < ((index_CUInfo + 5) % SIZE_CUInfo));
			if (isAligned) {
				read_CodingQuadTree_noCase3_aligned();
			} else {
				read_CodingQuadTree_noCase3();
			}
		}
		i++;
		goto l_read_CodingQuadTree;
	} else if (isSchedulable_read_CodingQuadTree_case4()) {
		read_CodingQuadTree_case4();
		i++;
		goto l_read_CodingQuadTree;
	} else if (isSchedulable_read_CodingQuadTree_noCase4()) {
		int stop = 0;
		if (5 > SIZE_CUInfo - index_CUInfo + HevcDecoder_Algo_Parser_CUInfo->read_inds[0]) {
			stop = 1;
		}
		if (5 > SIZE_CUInfo - index_CUInfo + HevcDecoder_Algo_Parser_CUInfo->read_inds[1]) {
			stop = 1;
		}
		if (5 > SIZE_CUInfo - index_CUInfo + HevcDecoder_Algo_Parser_CUInfo->read_inds[2]) {
			stop = 1;
		}
		if (5 > SIZE_CUInfo - index_CUInfo + HevcDecoder_Algo_Parser_CUInfo->read_inds[3]) {
			stop = 1;
		}
		if (5 > SIZE_CUInfo - index_CUInfo + HevcDecoder_Algo_Parser_CUInfo->read_inds[4]) {
			stop = 1;
		}
		if (1 > SIZE_PartMode - index_PartMode + HevcDecoder_Algo_Parser_PartMode->read_inds[0]) {
			stop = 1;
		}
		if (1 > SIZE_PartMode - index_PartMode + HevcDecoder_Algo_Parser_PartMode->read_inds[1]) {
			stop = 1;
		}
		if (1 > SIZE_PartMode - index_PartMode + HevcDecoder_Algo_Parser_PartMode->read_inds[2]) {
			stop = 1;
		}
		if (1 > SIZE_PartMode - index_PartMode + HevcDecoder_Algo_Parser_PartMode->read_inds[3]) {
			stop = 1;
		}
		if (1 > SIZE_PartMode - index_PartMode + HevcDecoder_Algo_Parser_PartMode->read_inds[4]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_read_CodingQuadTree;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		{
			int isAligned = 1;
			isAligned &= ((index_CUInfo % SIZE_CUInfo) < ((index_CUInfo + 5) % SIZE_CUInfo));
			if (isAligned) {
				read_CodingQuadTree_noCase4_aligned();
			} else {
				read_CodingQuadTree_noCase4();
			}
		}
		i++;
		goto l_read_CodingQuadTree;
	} else if (isSchedulable_read_CodingQuadTree_gotoCodingUnit()) {
		read_CodingQuadTree_gotoCodingUnit();
		i++;
		goto l_read_CodingUnit;
	} else if (isSchedulable_read_CodingQuadTree_noEnd()) {
		read_CodingQuadTree_noEnd();
		i++;
		goto l_read_CodingQuadTree;
	} else if (isSchedulable_read_CodingQuadTree_end()) {
		read_CodingQuadTree_end();
		i++;
		goto l_read_CodingTree;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_read_CodingQuadTree;
		goto finished;
	}
l_read_CodingTree:
	HevcDecoder_Algo_Parser_outside_FSM_scheduler(si);
	i += si->num_firings;
	if (isSchedulable_read_CodingTree_byPassBeforeTileLoop()) {
		read_CodingTree_byPassBeforeTileLoop();
		i++;
		goto l_read_CodingTree;
	} else if (isSchedulable_read_CodingTree_byPassBeforeTileEnd()) {
		read_CodingTree_byPassBeforeTileEnd();
		i++;
		goto l_read_CodingTree;
	} else if (isSchedulable_read_CodingTree_start()) {
		read_CodingTree_start();
		i++;
		goto l_read_CodingTree;
	} else if (isSchedulable_read_CodingTree_gotoSaoParam()) {
		read_CodingTree_gotoSaoParam();
		i++;
		goto l_read_SaoParam;
	} else if (isSchedulable_read_CodingTree_noGotoSaoParam()) {
		read_CodingTree_noGotoSaoParam();
		i++;
		goto l_read_CodingTree;
	} else if (isSchedulable_read_CodingTree_gotoCodingQuadTree()) {
		int stop = 0;
		if (1 > SIZE_IsPicSlcLcu - index_IsPicSlcLcu + HevcDecoder_Algo_Parser_IsPicSlcLcu->read_inds[0]) {
			stop = 1;
		}
		if (1 > SIZE_IsPicSlcLcu - index_IsPicSlcLcu + HevcDecoder_Algo_Parser_IsPicSlcLcu->read_inds[1]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_read_CodingTree;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		read_CodingTree_gotoCodingQuadTree();
		i++;
		goto l_read_CodingQuadTree;
	} else if (isSchedulable_read_CodingTree_end()) {
		read_CodingTree_end();
		i++;
		goto l_read_SliceData;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_read_CodingTree;
		goto finished;
	}
l_read_CodingUnit:
	HevcDecoder_Algo_Parser_outside_FSM_scheduler(si);
	i += si->num_firings;
	if (isSchedulable_read_CodingUnit_start()) {
		read_CodingUnit_start();
		i++;
		goto l_read_CodingUnit;
	} else if (isSchedulable_read_CodingUnit_gotoPredictionUnit_goto1()) {
		int stop = 0;
		if (5 > SIZE_CUInfo - index_CUInfo + HevcDecoder_Algo_Parser_CUInfo->read_inds[0]) {
			stop = 1;
		}
		if (5 > SIZE_CUInfo - index_CUInfo + HevcDecoder_Algo_Parser_CUInfo->read_inds[1]) {
			stop = 1;
		}
		if (5 > SIZE_CUInfo - index_CUInfo + HevcDecoder_Algo_Parser_CUInfo->read_inds[2]) {
			stop = 1;
		}
		if (5 > SIZE_CUInfo - index_CUInfo + HevcDecoder_Algo_Parser_CUInfo->read_inds[3]) {
			stop = 1;
		}
		if (5 > SIZE_CUInfo - index_CUInfo + HevcDecoder_Algo_Parser_CUInfo->read_inds[4]) {
			stop = 1;
		}
		if (1 > SIZE_Cbf - index_Cbf + HevcDecoder_Algo_Parser_Cbf->read_inds[0]) {
			stop = 1;
		}
		if (1 > SIZE_PartMode - index_PartMode + HevcDecoder_Algo_Parser_PartMode->read_inds[0]) {
			stop = 1;
		}
		if (1 > SIZE_PartMode - index_PartMode + HevcDecoder_Algo_Parser_PartMode->read_inds[1]) {
			stop = 1;
		}
		if (1 > SIZE_PartMode - index_PartMode + HevcDecoder_Algo_Parser_PartMode->read_inds[2]) {
			stop = 1;
		}
		if (1 > SIZE_PartMode - index_PartMode + HevcDecoder_Algo_Parser_PartMode->read_inds[3]) {
			stop = 1;
		}
		if (1 > SIZE_PartMode - index_PartMode + HevcDecoder_Algo_Parser_PartMode->read_inds[4]) {
			stop = 1;
		}
		if (1 > SIZE_SplitTransform - index_SplitTransform + HevcDecoder_Algo_Parser_SplitTransform->read_inds[0]) {
			stop = 1;
		}
		if (1 > SIZE_SplitTransform - index_SplitTransform + HevcDecoder_Algo_Parser_SplitTransform->read_inds[1]) {
			stop = 1;
		}
		if (21 > SIZE_TUSize - index_TUSize + HevcDecoder_Algo_Parser_TUSize->read_inds[0]) {
			stop = 1;
		}
		if (21 > SIZE_TUSize - index_TUSize + HevcDecoder_Algo_Parser_TUSize->read_inds[1]) {
			stop = 1;
		}
		if (21 > SIZE_TUSize - index_TUSize + HevcDecoder_Algo_Parser_TUSize->read_inds[2]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_read_CodingUnit;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		{
			int isAligned = 1;
			isAligned &= ((index_CUInfo % SIZE_CUInfo) < ((index_CUInfo + 5) % SIZE_CUInfo));
			isAligned &= ((index_TUSize % SIZE_TUSize) < ((index_TUSize + 21) % SIZE_TUSize));
			if (isAligned) {
				read_CodingUnit_gotoPredictionUnit_goto1_aligned();
			} else {
				read_CodingUnit_gotoPredictionUnit_goto1();
			}
		}
		i++;
		goto l_read_PredictionUnit;
	} else if (isSchedulable_read_CodingUnit_noGoto1()) {
		int stop = 0;
		if (1 > SIZE_PartMode - index_PartMode + HevcDecoder_Algo_Parser_PartMode->read_inds[0]) {
			stop = 1;
		}
		if (1 > SIZE_PartMode - index_PartMode + HevcDecoder_Algo_Parser_PartMode->read_inds[1]) {
			stop = 1;
		}
		if (1 > SIZE_PartMode - index_PartMode + HevcDecoder_Algo_Parser_PartMode->read_inds[2]) {
			stop = 1;
		}
		if (1 > SIZE_PartMode - index_PartMode + HevcDecoder_Algo_Parser_PartMode->read_inds[3]) {
			stop = 1;
		}
		if (1 > SIZE_PartMode - index_PartMode + HevcDecoder_Algo_Parser_PartMode->read_inds[4]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_read_CodingUnit;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		read_CodingUnit_noGoto1();
		i++;
		goto l_send_IntraPredMode;
	} else if (isSchedulable_read_CodingUnit_gotoPCMSample()) {
		read_CodingUnit_gotoPCMSample();
		i++;
		goto l_read_PCMSample;
	} else if (isSchedulable_read_CodingUnit_gotoPredictionUnit_goto2()) {
		int stop = 0;
		if (5 > SIZE_CUInfo - index_CUInfo + HevcDecoder_Algo_Parser_CUInfo->read_inds[0]) {
			stop = 1;
		}
		if (5 > SIZE_CUInfo - index_CUInfo + HevcDecoder_Algo_Parser_CUInfo->read_inds[1]) {
			stop = 1;
		}
		if (5 > SIZE_CUInfo - index_CUInfo + HevcDecoder_Algo_Parser_CUInfo->read_inds[2]) {
			stop = 1;
		}
		if (5 > SIZE_CUInfo - index_CUInfo + HevcDecoder_Algo_Parser_CUInfo->read_inds[3]) {
			stop = 1;
		}
		if (5 > SIZE_CUInfo - index_CUInfo + HevcDecoder_Algo_Parser_CUInfo->read_inds[4]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_read_CodingUnit;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		{
			int isAligned = 1;
			isAligned &= ((index_CUInfo % SIZE_CUInfo) < ((index_CUInfo + 5) % SIZE_CUInfo));
			if (isAligned) {
				read_CodingUnit_gotoPredictionUnit_goto2_aligned();
			} else {
				read_CodingUnit_gotoPredictionUnit_goto2();
			}
		}
		i++;
		goto l_read_PredictionUnit;
	} else if (isSchedulable_read_CodingUnit_endFunction()) {
		read_CodingUnit_endFunction();
		i++;
		goto l_read_CodingUnit;
	} else if (isSchedulable_read_CodingUnit_endFunctionSend()) {
		int stop = 0;
		if (1 > SIZE_SplitTransform - index_SplitTransform + HevcDecoder_Algo_Parser_SplitTransform->read_inds[0]) {
			stop = 1;
		}
		if (1 > SIZE_SplitTransform - index_SplitTransform + HevcDecoder_Algo_Parser_SplitTransform->read_inds[1]) {
			stop = 1;
		}
		if (21 > SIZE_TUSize - index_TUSize + HevcDecoder_Algo_Parser_TUSize->read_inds[0]) {
			stop = 1;
		}
		if (21 > SIZE_TUSize - index_TUSize + HevcDecoder_Algo_Parser_TUSize->read_inds[1]) {
			stop = 1;
		}
		if (21 > SIZE_TUSize - index_TUSize + HevcDecoder_Algo_Parser_TUSize->read_inds[2]) {
			stop = 1;
		}
		if (1 > SIZE_Cbf - index_Cbf + HevcDecoder_Algo_Parser_Cbf->read_inds[0]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_read_CodingUnit;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		{
			int isAligned = 1;
			isAligned &= ((index_TUSize % SIZE_TUSize) < ((index_TUSize + 21) % SIZE_TUSize));
			if (isAligned) {
				read_CodingUnit_endFunctionSend_aligned();
			} else {
				read_CodingUnit_endFunctionSend();
			}
		}
		i++;
		goto l_read_CodingUnit;
	} else if (isSchedulable_read_CodingUnit_gotoTransformTree()) {
		read_CodingUnit_gotoTransformTree();
		i++;
		goto l_read_TransformTree;
	} else if (isSchedulable_read_CodingUnit_end()) {
		read_CodingUnit_end();
		i++;
		goto l_sendQp;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_read_CodingUnit;
		goto finished;
	}
l_read_MVDCoding:
	HevcDecoder_Algo_Parser_outside_FSM_scheduler(si);
	i += si->num_firings;
	if (isSchedulable_read_MVDCoding_start()) {
		read_MVDCoding_start();
		i++;
		goto l_read_MVDCoding_end;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_read_MVDCoding;
		goto finished;
	}
l_read_MVDCoding_end:
	HevcDecoder_Algo_Parser_outside_FSM_scheduler(si);
	i += si->num_firings;
	if (isSchedulable_read_MVDCoding_ended()) {
		read_MVDCoding_ended();
		i++;
		goto l_read_PredictionUnit;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_read_MVDCoding_end;
		goto finished;
	}
l_read_Nal_unit_header:
	HevcDecoder_Algo_Parser_outside_FSM_scheduler(si);
	i += si->num_firings;
	if (isSchedulable_read_nal_unit_header()) {
		read_nal_unit_header();
		i++;
		goto l_find_header;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_read_Nal_unit_header;
		goto finished;
	}
l_read_PCMSample:
	HevcDecoder_Algo_Parser_outside_FSM_scheduler(si);
	i += si->num_firings;
	if (isSchedulable_read_PCMSample_start()) {
		read_PCMSample_start();
		i++;
		goto l_read_PCMSampleLoop;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_read_PCMSample;
		goto finished;
	}
l_read_PCMSampleLoop:
	HevcDecoder_Algo_Parser_outside_FSM_scheduler(si);
	i += si->num_firings;
	if (isSchedulable_read_PCMSample_skipLoop()) {
		read_PCMSample_skipLoop();
		i++;
		goto l_read_PCMSampleLoop;
	} else if (isSchedulable_read_PCMSample_skipLoop_end()) {
		read_PCMSample_skipLoop_end();
		i++;
		goto l_read_CodingUnit;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_read_PCMSampleLoop;
		goto finished;
	}
l_read_PPS_Header:
	HevcDecoder_Algo_Parser_outside_FSM_scheduler(si);
	i += si->num_firings;
	if (isSchedulable_read_PPS_Header_se_idx_1()) {
		read_PPS_Header_se_idx_1();
		i++;
		goto l_read_PPS_Header;
	} else if (isSchedulable_read_PPS_Header_se_idx_2()) {
		read_PPS_Header_se_idx_2();
		i++;
		goto l_read_PPS_Header;
	} else if (isSchedulable_read_PPS_Header_se_idx_3_loop()) {
		read_PPS_Header_se_idx_3_loop();
		i++;
		goto l_read_PPS_Header;
	} else if (isSchedulable_read_PPS_Header_se_idx_3_loopEnd()) {
		read_PPS_Header_se_idx_3_loopEnd();
		i++;
		goto l_read_PPS_Header;
	} else if (isSchedulable_read_PPS_Header_se_idx_3_noLoop()) {
		read_PPS_Header_se_idx_3_noLoop();
		i++;
		goto l_read_PPS_Header;
	} else if (isSchedulable_read_PPS_Header_se_idx_4_loop()) {
		read_PPS_Header_se_idx_4_loop();
		i++;
		goto l_read_PPS_Header;
	} else if (isSchedulable_read_PPS_Header_se_idx_4_loopEnd()) {
		read_PPS_Header_se_idx_4_loopEnd();
		i++;
		goto l_read_PPS_Header;
	} else if (isSchedulable_read_PPS_Header_se_idx_5()) {
		read_PPS_Header_se_idx_5();
		i++;
		goto l_read_PPS_Header;
	} else if (isSchedulable_read_PPS_Header_se_idx_51()) {
		read_PPS_Header_se_idx_51();
		i++;
		goto l_read_PPS_Header;
	} else if (isSchedulable_read_PPS_Header_se_idx_50()) {
		read_PPS_Header_se_idx_50();
		i++;
		goto l_read_PPS_Header;
	} else if (isSchedulable_read_PPS_Header_se_idx_51_loopSize_id()) {
		read_PPS_Header_se_idx_51_loopSize_id();
		i++;
		goto l_read_PPS_Header;
	} else if (isSchedulable_read_PPS_Header_se_idx_53_loopMatrix_id()) {
		read_PPS_Header_se_idx_53_loopMatrix_id();
		i++;
		goto l_read_PPS_Header;
	} else if (isSchedulable_read_PPS_Header_se_idx_54_loopNumCoef()) {
		read_PPS_Header_se_idx_54_loopNumCoef();
		i++;
		goto l_read_PPS_Header;
	} else if (isSchedulable_read_PPS_Header_se_idx_54_loopNumCoefEnd()) {
		read_PPS_Header_se_idx_54_loopNumCoefEnd();
		i++;
		goto l_read_PPS_Header;
	} else if (isSchedulable_read_PPS_Header_se_idx_53_loopMatrix_id_End()) {
		read_PPS_Header_se_idx_53_loopMatrix_id_End();
		i++;
		goto l_read_PPS_Header;
	} else if (isSchedulable_read_PPS_Header_se_idx_51_loopSize_id_End()) {
		read_PPS_Header_se_idx_51_loopSize_id_End();
		i++;
		goto l_read_PPS_Header;
	} else if (isSchedulable_read_PPS_Header_done()) {
		read_PPS_Header_done();
		i++;
		goto l_byte_align;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_read_PPS_Header;
		goto finished;
	}
l_read_PredictionUnit:
	HevcDecoder_Algo_Parser_outside_FSM_scheduler(si);
	i += si->num_firings;
	if (isSchedulable_read_PredictionUnit_start()) {
		read_PredictionUnit_start();
		i++;
		goto l_read_PredictionUnit;
	} else if (isSchedulable_read_PredictionUnit_retMVDcoding_goto1()) {
		read_PredictionUnit_retMVDcoding_goto1();
		i++;
		goto l_read_PredictionUnit;
	} else if (isSchedulable_read_PredictionUnit_gotoMVDCoding()) {
		read_PredictionUnit_gotoMVDCoding();
		i++;
		goto l_read_MVDCoding;
	} else if (isSchedulable_read_PredictionUnit_retMVDcoding_goto2()) {
		read_PredictionUnit_retMVDcoding_goto2();
		i++;
		goto l_read_PredictionUnit;
	} else if (isSchedulable_read_PredictionUnit_end_mergeIdx_Eq_min1()) {
		int stop = 0;
		if (9 > SIZE_MvPredSyntaxElem - index_MvPredSyntaxElem + HevcDecoder_Algo_Parser_MvPredSyntaxElem->read_inds[0]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_read_PredictionUnit;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		{
			int isAligned = 1;
			isAligned &= ((index_MvPredSyntaxElem % SIZE_MvPredSyntaxElem) < ((index_MvPredSyntaxElem + 9) % SIZE_MvPredSyntaxElem));
			if (isAligned) {
				read_PredictionUnit_end_mergeIdx_Eq_min1_aligned();
			} else {
				read_PredictionUnit_end_mergeIdx_Eq_min1();
			}
		}
		i++;
		goto l_read_CodingUnit;
	} else if (isSchedulable_read_PredictionUnit_end_mergeIdx_notEq_min1()) {
		int stop = 0;
		if (5 > SIZE_MvPredSyntaxElem - index_MvPredSyntaxElem + HevcDecoder_Algo_Parser_MvPredSyntaxElem->read_inds[0]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_read_PredictionUnit;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		{
			int isAligned = 1;
			isAligned &= ((index_MvPredSyntaxElem % SIZE_MvPredSyntaxElem) < ((index_MvPredSyntaxElem + 5) % SIZE_MvPredSyntaxElem));
			if (isAligned) {
				read_PredictionUnit_end_mergeIdx_notEq_min1_aligned();
			} else {
				read_PredictionUnit_end_mergeIdx_notEq_min1();
			}
		}
		i++;
		goto l_read_CodingUnit;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_read_PredictionUnit;
		goto finished;
	}
l_read_ResidualCoding:
	HevcDecoder_Algo_Parser_outside_FSM_scheduler(si);
	i += si->num_firings;
	if (isSchedulable_read_ResidualCoding_start()) {
		int stop = 0;
		if (7 > SIZE_TUSize - index_TUSize + HevcDecoder_Algo_Parser_TUSize->read_inds[0]) {
			stop = 1;
		}
		if (7 > SIZE_TUSize - index_TUSize + HevcDecoder_Algo_Parser_TUSize->read_inds[1]) {
			stop = 1;
		}
		if (7 > SIZE_TUSize - index_TUSize + HevcDecoder_Algo_Parser_TUSize->read_inds[2]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_read_ResidualCoding;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		{
			int isAligned = 1;
			isAligned &= ((index_TUSize % SIZE_TUSize) < ((index_TUSize + 7) % SIZE_TUSize));
			if (isAligned) {
				read_ResidualCoding_start_aligned();
			} else {
				read_ResidualCoding_start();
			}
		}
		i++;
		goto l_read_ResidualCodingStart;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_read_ResidualCoding;
		goto finished;
	}
l_read_ResidualCodingGetCoeff:
	HevcDecoder_Algo_Parser_outside_FSM_scheduler(si);
	i += si->num_firings;
	if (isSchedulable_read_ResidualCoding_for_numLastSubset_get_COEFF_ABS_LEVEL_end()) {
		read_ResidualCoding_for_numLastSubset_get_COEFF_ABS_LEVEL_end();
		i++;
		goto l_read_ResidualCodingStart;
	} else if (isSchedulable_read_ResidualCoding_for_numLastSubset_get_COEFF_ABS_LEVEL()) {
		read_ResidualCoding_for_numLastSubset_get_COEFF_ABS_LEVEL();
		i++;
		goto l_read_ResidualCodingGetCoeff;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_read_ResidualCodingGetCoeff;
		goto finished;
	}
l_read_ResidualCodingGreater1:
	HevcDecoder_Algo_Parser_outside_FSM_scheduler(si);
	i += si->num_firings;
	if (isSchedulable_read_ResidualCoding_for_numLastSubset_get_COEFF_ABS_LEVEL_GREATER1_FLAG()) {
		read_ResidualCoding_for_numLastSubset_get_COEFF_ABS_LEVEL_GREATER1_FLAG();
		i++;
		goto l_read_ResidualCodingGetCoeff;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_read_ResidualCodingGreater1;
		goto finished;
	}
l_read_ResidualCodingStart:
	HevcDecoder_Algo_Parser_outside_FSM_scheduler(si);
	i += si->num_firings;
	if (isSchedulable_read_ResidualCoding_end_xIT4()) {
		int stop = 0;
		if (16 > SIZE_Coeff - index_Coeff + HevcDecoder_Algo_Parser_Coeff->read_inds[0]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_read_ResidualCodingStart;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		{
			int isAligned = 1;
			isAligned &= ((index_Coeff % SIZE_Coeff) < ((index_Coeff + 16) % SIZE_Coeff));
			if (isAligned) {
				read_ResidualCoding_end_xIT4_aligned();
			} else {
				read_ResidualCoding_end_xIT4();
			}
		}
		i++;
		goto l_read_TransformUnit;
	} else if (isSchedulable_read_ResidualCoding_end_xIT8()) {
		int stop = 0;
		if (64 > SIZE_Coeff - index_Coeff + HevcDecoder_Algo_Parser_Coeff->read_inds[0]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_read_ResidualCodingStart;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		{
			int isAligned = 1;
			isAligned &= ((index_Coeff % SIZE_Coeff) < ((index_Coeff + 64) % SIZE_Coeff));
			if (isAligned) {
				read_ResidualCoding_end_xIT8_aligned();
			} else {
				read_ResidualCoding_end_xIT8();
			}
		}
		i++;
		goto l_read_TransformUnit;
	} else if (isSchedulable_read_ResidualCoding_end_xIT16()) {
		int stop = 0;
		if (256 > SIZE_Coeff - index_Coeff + HevcDecoder_Algo_Parser_Coeff->read_inds[0]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_read_ResidualCodingStart;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		{
			int isAligned = 1;
			isAligned &= ((index_Coeff % SIZE_Coeff) < ((index_Coeff + 256) % SIZE_Coeff));
			if (isAligned) {
				read_ResidualCoding_end_xIT16_aligned();
			} else {
				read_ResidualCoding_end_xIT16();
			}
		}
		i++;
		goto l_read_TransformUnit;
	} else if (isSchedulable_read_ResidualCoding_end_xIT32()) {
		int stop = 0;
		if (1024 > SIZE_Coeff - index_Coeff + HevcDecoder_Algo_Parser_Coeff->read_inds[0]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_read_ResidualCodingStart;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		{
			int isAligned = 1;
			isAligned &= ((index_Coeff % SIZE_Coeff) < ((index_Coeff + 1024) % SIZE_Coeff));
			if (isAligned) {
				read_ResidualCoding_end_xIT32_aligned();
			} else {
				read_ResidualCoding_end_xIT32();
			}
		}
		i++;
		goto l_read_TransformUnit;
	} else if (isSchedulable_read_ResidualCoding_for_numLastSubset_start()) {
		read_ResidualCoding_for_numLastSubset_start();
		i++;
		goto l_read_ResidualCodingGreater1;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_read_ResidualCodingStart;
		goto finished;
	}
l_read_SEI_Header:
	HevcDecoder_Algo_Parser_outside_FSM_scheduler(si);
	i += si->num_firings;
	if (isSchedulable_read_SEI_Header_init()) {
		read_SEI_Header_init();
		i++;
		goto l_read_SEI_Header;
	} else if (isSchedulable_read_SEI_Header_payload_type()) {
		read_SEI_Header_payload_type();
		i++;
		goto l_read_SEI_Header;
	} else if (isSchedulable_read_SEI_Header_payload_size()) {
		read_SEI_Header_payload_size();
		i++;
		goto l_read_SEI_Header;
	} else if (isSchedulable_read_SEI_Header_skipSEI()) {
		read_SEI_Header_skipSEI();
		i++;
		goto l_read_SEI_Header;
	} else if (isSchedulable_read_SEI_Header_decoded_picture_hash_init()) {
		read_SEI_Header_decoded_picture_hash_init();
		i++;
		goto l_read_SEI_Header;
	} else if (isSchedulable_read_SEI_Header_decoded_picture_hash_loop()) {
		int stop = 0;
		if (1 > SIZE_SEI_MD5 - index_SEI_MD5 + HevcDecoder_Algo_Parser_SEI_MD5->read_inds[0]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_read_SEI_Header;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		read_SEI_Header_decoded_picture_hash_loop();
		i++;
		goto l_read_SEI_Header;
	} else if (isSchedulable_read_SEI_Header_decoded_picture_hash_skip()) {
		read_SEI_Header_decoded_picture_hash_skip();
		i++;
		goto l_read_SEI_Header;
	} else if (isSchedulable_read_SEI_Header_sei_payload_end()) {
		read_SEI_Header_sei_payload_end();
		i++;
		goto l_read_SEI_Header;
	} else if (isSchedulable_read_SEI_Header_done()) {
		read_SEI_Header_done();
		i++;
		goto l_byte_align;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_read_SEI_Header;
		goto finished;
	}
l_read_SPS_Header:
	HevcDecoder_Algo_Parser_outside_FSM_scheduler(si);
	i += si->num_firings;
	if (isSchedulable_read_SPS_Header_se_idx_1()) {
		read_SPS_Header_se_idx_1();
		i++;
		goto l_read_SPS_Header;
	} else if (isSchedulable_read_SPS_Header_se_idx_20()) {
		read_SPS_Header_se_idx_20();
		i++;
		goto l_read_SPS_Header;
	} else if (isSchedulable_read_SPS_Header_se_idx_21()) {
		read_SPS_Header_se_idx_21();
		i++;
		goto l_read_SPS_Header;
	} else if (isSchedulable_read_SPS_Header_se_idx_22_loop1()) {
		read_SPS_Header_se_idx_22_loop1();
		i++;
		goto l_read_SPS_Header;
	} else if (isSchedulable_read_SPS_Header_se_idx_22_loopEnd1()) {
		read_SPS_Header_se_idx_22_loopEnd1();
		i++;
		goto l_read_SPS_Header;
	} else if (isSchedulable_read_SPS_Header_se_idx_22_indertedCond()) {
		read_SPS_Header_se_idx_22_indertedCond();
		i++;
		goto l_read_SPS_Header;
	} else if (isSchedulable_read_SPS_Header_se_idx_22_loop2()) {
		read_SPS_Header_se_idx_22_loop2();
		i++;
		goto l_read_SPS_Header;
	} else if (isSchedulable_read_SPS_Header_se_idx_22_loopEnd()) {
		read_SPS_Header_se_idx_22_loopEnd();
		i++;
		goto l_read_SPS_Header;
	} else if (isSchedulable_read_SPS_Header_se_idx_1_1()) {
		read_SPS_Header_se_idx_1_1();
		i++;
		goto l_read_SPS_Header;
	} else if (isSchedulable_read_SPS_Header_se_idx_2()) {
		read_SPS_Header_se_idx_2();
		i++;
		goto l_read_SPS_Header;
	} else if (isSchedulable_read_SPS_Header_se_idx_3_loop()) {
		read_SPS_Header_se_idx_3_loop();
		i++;
		goto l_read_SPS_Header;
	} else if (isSchedulable_read_SPS_Header_se_idx_3_loopEnd()) {
		read_SPS_Header_se_idx_3_loopEnd();
		i++;
		goto l_read_SPS_Header;
	} else if (isSchedulable_read_SPS_Header_se_idx_4()) {
		read_SPS_Header_se_idx_4();
		i++;
		goto l_read_SPS_Header;
	} else if (isSchedulable_read_SPS_Header_se_idx_5()) {
		read_SPS_Header_se_idx_5();
		i++;
		goto l_read_SPS_Header;
	} else if (isSchedulable_read_SPS_Header_se_idx_60()) {
		read_SPS_Header_se_idx_60();
		i++;
		goto l_read_SPS_Header;
	} else if (isSchedulable_read_SPS_Header_se_idx_61_loopSize_id()) {
		read_SPS_Header_se_idx_61_loopSize_id();
		i++;
		goto l_read_SPS_Header;
	} else if (isSchedulable_read_SPS_Header_se_idx_61_loopMatrix_id()) {
		read_SPS_Header_se_idx_61_loopMatrix_id();
		i++;
		goto l_read_SPS_Header;
	} else if (isSchedulable_read_SPS_Header_se_idx_63_loopNumCoef()) {
		read_SPS_Header_se_idx_63_loopNumCoef();
		i++;
		goto l_read_SPS_Header;
	} else if (isSchedulable_read_SPS_Header_se_idx_63_loopNumCoefEnd()) {
		read_SPS_Header_se_idx_63_loopNumCoefEnd();
		i++;
		goto l_read_SPS_Header;
	} else if (isSchedulable_read_SPS_Header_se_idx_62_loopMatrix_id_End()) {
		read_SPS_Header_se_idx_62_loopMatrix_id_End();
		i++;
		goto l_read_SPS_Header;
	} else if (isSchedulable_read_SPS_Header_se_idx_61_size_id_loopEnd()) {
		read_SPS_Header_se_idx_61_size_id_loopEnd();
		i++;
		goto l_read_SPS_Header;
	} else if (isSchedulable_read_SPS_Header_se_idx_6()) {
		read_SPS_Header_se_idx_6();
		i++;
		goto l_read_SPS_Header;
	} else if (isSchedulable_read_SPS_Header_se_idx_7_loop()) {
		read_SPS_Header_se_idx_7_loop();
		i++;
		goto l_read_SPS_Header;
	} else if (isSchedulable_read_SPS_Header_se_idx_7_loopEnd()) {
		read_SPS_Header_se_idx_7_loopEnd();
		i++;
		goto l_read_SPS_Header;
	} else if (isSchedulable_read_SPS_Header_se_idx_8()) {
		read_SPS_Header_se_idx_8();
		i++;
		goto l_read_SPS_Header;
	} else if (isSchedulable_read_SPS_Header_done()) {
		read_SPS_Header_done();
		i++;
		goto l_byte_align;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_read_SPS_Header;
		goto finished;
	}
l_read_SaoParam:
	HevcDecoder_Algo_Parser_outside_FSM_scheduler(si);
	i += si->num_firings;
	if (isSchedulable_read_SaoParam_start()) {
		int stop = 0;
		if (1 > SIZE_SaoSe - index_SaoSe + HevcDecoder_Algo_Parser_SaoSe->read_inds[0]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_read_SaoParam;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		read_SaoParam_start();
		i++;
		goto l_read_SaoParam;
	} else if (isSchedulable_read_SaoParam_loop1()) {
		int stop = 0;
		if (1 > SIZE_SaoSe - index_SaoSe + HevcDecoder_Algo_Parser_SaoSe->read_inds[0]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_read_SaoParam;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		read_SaoParam_loop1();
		i++;
		goto l_read_SaoParam;
	} else if (isSchedulable_read_SaoParam_loop2()) {
		int stop = 0;
		if (5 > SIZE_SaoSe - index_SaoSe + HevcDecoder_Algo_Parser_SaoSe->read_inds[0]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_read_SaoParam;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		{
			int isAligned = 1;
			isAligned &= ((index_SaoSe % SIZE_SaoSe) < ((index_SaoSe + 5) % SIZE_SaoSe));
			if (isAligned) {
				read_SaoParam_loop2_aligned();
			} else {
				read_SaoParam_loop2();
			}
		}
		i++;
		goto l_read_SaoParam;
	} else if (isSchedulable_read_SaoParam_nextLoop()) {
		read_SaoParam_nextLoop();
		i++;
		goto l_read_SaoParam;
	} else if (isSchedulable_read_SaoParam_endLoop()) {
		read_SaoParam_endLoop();
		i++;
		goto l_read_CodingTree;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_read_SaoParam;
		goto finished;
	}
l_read_SliceData:
	HevcDecoder_Algo_Parser_outside_FSM_scheduler(si);
	i += si->num_firings;
	if (isSchedulable_read_SliceData_init()) {
		int stop = 0;
		if (1 > SIZE_IsPicSlcLcu - index_IsPicSlcLcu + HevcDecoder_Algo_Parser_IsPicSlcLcu->read_inds[0]) {
			stop = 1;
		}
		if (1 > SIZE_IsPicSlcLcu - index_IsPicSlcLcu + HevcDecoder_Algo_Parser_IsPicSlcLcu->read_inds[1]) {
			stop = 1;
		}
		if (1 > SIZE_IsPicSlc - index_IsPicSlc + HevcDecoder_Algo_Parser_IsPicSlc->read_inds[0]) {
			stop = 1;
		}
		if (4 > SIZE_MvPredSyntaxElem - index_MvPredSyntaxElem + HevcDecoder_Algo_Parser_MvPredSyntaxElem->read_inds[0]) {
			stop = 1;
		}
		if (1 > SIZE_SaoSe - index_SaoSe + HevcDecoder_Algo_Parser_SaoSe->read_inds[0]) {
			stop = 1;
		}
		if (1 > SIZE_TilesCoord - index_TilesCoord + HevcDecoder_Algo_Parser_TilesCoord->read_inds[0]) {
			stop = 1;
		}
		if (1 > SIZE_TilesCoord - index_TilesCoord + HevcDecoder_Algo_Parser_TilesCoord->read_inds[1]) {
			stop = 1;
		}
		if (1 > SIZE_TilesCoord - index_TilesCoord + HevcDecoder_Algo_Parser_TilesCoord->read_inds[2]) {
			stop = 1;
		}
		if (1 > SIZE_TilesCoord - index_TilesCoord + HevcDecoder_Algo_Parser_TilesCoord->read_inds[3]) {
			stop = 1;
		}
		if (1 > SIZE_TilesCoord - index_TilesCoord + HevcDecoder_Algo_Parser_TilesCoord->read_inds[4]) {
			stop = 1;
		}
		if (2 > SIZE_PicSizeInMb - index_PicSizeInMb + HevcDecoder_Algo_Parser_PicSizeInMb->read_inds[0]) {
			stop = 1;
		}
		if (2 > SIZE_PicSizeInMb - index_PicSizeInMb + HevcDecoder_Algo_Parser_PicSizeInMb->read_inds[1]) {
			stop = 1;
		}
		if (4 > SIZE_DispCoord - index_DispCoord + HevcDecoder_Algo_Parser_DispCoord->read_inds[0]) {
			stop = 1;
		}
		if (1 > SIZE_LFAcrossSlcTile - index_LFAcrossSlcTile + HevcDecoder_Algo_Parser_LFAcrossSlcTile->read_inds[0]) {
			stop = 1;
		}
		if (1 > SIZE_LFAcrossSlcTile - index_LFAcrossSlcTile + HevcDecoder_Algo_Parser_LFAcrossSlcTile->read_inds[1]) {
			stop = 1;
		}
		if (4 > SIZE_ReorderPics - index_ReorderPics + HevcDecoder_Algo_Parser_ReorderPics->read_inds[0]) {
			stop = 1;
		}
		if (2 > SIZE_PictSize - index_PictSize + HevcDecoder_Algo_Parser_PictSize->read_inds[0]) {
			stop = 1;
		}
		if (2 > SIZE_PictSize - index_PictSize + HevcDecoder_Algo_Parser_PictSize->read_inds[1]) {
			stop = 1;
		}
		if (2 > SIZE_PictSize - index_PictSize + HevcDecoder_Algo_Parser_PictSize->read_inds[2]) {
			stop = 1;
		}
		if (2 > SIZE_PictSize - index_PictSize + HevcDecoder_Algo_Parser_PictSize->read_inds[3]) {
			stop = 1;
		}
		if (2 > SIZE_PictSize - index_PictSize + HevcDecoder_Algo_Parser_PictSize->read_inds[4]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_read_SliceData;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		{
			int isAligned = 1;
			isAligned &= ((index_MvPredSyntaxElem % SIZE_MvPredSyntaxElem) < ((index_MvPredSyntaxElem + 4) % SIZE_MvPredSyntaxElem));
			isAligned &= ((index_PictSize % SIZE_PictSize) < ((index_PictSize + 2) % SIZE_PictSize));
			if (isAligned) {
				read_SliceData_init_aligned();
			} else {
				read_SliceData_init();
			}
		}
		i++;
		goto l_read_SliceData;
	} else if (isSchedulable_read_SliceData_sendInfoSlice()) {
		int stop = 0;
		if (4 > SIZE_TilesCoord - index_TilesCoord + HevcDecoder_Algo_Parser_TilesCoord->read_inds[0]) {
			stop = 1;
		}
		if (4 > SIZE_TilesCoord - index_TilesCoord + HevcDecoder_Algo_Parser_TilesCoord->read_inds[1]) {
			stop = 1;
		}
		if (4 > SIZE_TilesCoord - index_TilesCoord + HevcDecoder_Algo_Parser_TilesCoord->read_inds[2]) {
			stop = 1;
		}
		if (4 > SIZE_TilesCoord - index_TilesCoord + HevcDecoder_Algo_Parser_TilesCoord->read_inds[3]) {
			stop = 1;
		}
		if (4 > SIZE_TilesCoord - index_TilesCoord + HevcDecoder_Algo_Parser_TilesCoord->read_inds[4]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_read_SliceData;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		{
			int isAligned = 1;
			isAligned &= ((index_TilesCoord % SIZE_TilesCoord) < ((index_TilesCoord + 4) % SIZE_TilesCoord));
			if (isAligned) {
				read_SliceData_sendInfoSlice_aligned();
			} else {
				read_SliceData_sendInfoSlice();
			}
		}
		i++;
		goto l_read_SliceData;
	} else if (isSchedulable_read_SliceData_sendInfoTilesLoop()) {
		int stop = 0;
		if (4 > SIZE_TilesCoord - index_TilesCoord + HevcDecoder_Algo_Parser_TilesCoord->read_inds[0]) {
			stop = 1;
		}
		if (4 > SIZE_TilesCoord - index_TilesCoord + HevcDecoder_Algo_Parser_TilesCoord->read_inds[1]) {
			stop = 1;
		}
		if (4 > SIZE_TilesCoord - index_TilesCoord + HevcDecoder_Algo_Parser_TilesCoord->read_inds[2]) {
			stop = 1;
		}
		if (4 > SIZE_TilesCoord - index_TilesCoord + HevcDecoder_Algo_Parser_TilesCoord->read_inds[3]) {
			stop = 1;
		}
		if (4 > SIZE_TilesCoord - index_TilesCoord + HevcDecoder_Algo_Parser_TilesCoord->read_inds[4]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_read_SliceData;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		{
			int isAligned = 1;
			isAligned &= ((index_TilesCoord % SIZE_TilesCoord) < ((index_TilesCoord + 4) % SIZE_TilesCoord));
			if (isAligned) {
				read_SliceData_sendInfoTilesLoop_aligned();
			} else {
				read_SliceData_sendInfoTilesLoop();
			}
		}
		i++;
		goto l_read_SliceData;
	} else if (isSchedulable_read_SliceData_sendRealInfoTilesLoop()) {
		read_SliceData_sendRealInfoTilesLoop();
		i++;
		goto l_read_SliceData;
	} else if (isSchedulable_read_SliceData_senInfoTilesEnd()) {
		read_SliceData_senInfoTilesEnd();
		i++;
		goto l_read_SliceData;
	} else if (isSchedulable_read_SliceData_senRealInfoTilesEnd()) {
		read_SliceData_senRealInfoTilesEnd();
		i++;
		goto l_read_SliceData;
	} else if (isSchedulable_read_SliceData_noInit()) {
		int stop = 0;
		if (2 > SIZE_MvPredSyntaxElem - index_MvPredSyntaxElem + HevcDecoder_Algo_Parser_MvPredSyntaxElem->read_inds[0]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_read_SliceData;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		{
			int isAligned = 1;
			isAligned &= ((index_MvPredSyntaxElem % SIZE_MvPredSyntaxElem) < ((index_MvPredSyntaxElem + 2) % SIZE_MvPredSyntaxElem));
			if (isAligned) {
				read_SliceData_noInit_aligned();
			} else {
				read_SliceData_noInit();
			}
		}
		i++;
		goto l_read_SliceData;
	} else if (isSchedulable_read_SliceData_noInit_isSlc()) {
		int stop = 0;
		if (4 > SIZE_MvPredSyntaxElem - index_MvPredSyntaxElem + HevcDecoder_Algo_Parser_MvPredSyntaxElem->read_inds[0]) {
			stop = 1;
		}
		if (1 > SIZE_IsPicSlcLcu - index_IsPicSlcLcu + HevcDecoder_Algo_Parser_IsPicSlcLcu->read_inds[0]) {
			stop = 1;
		}
		if (1 > SIZE_IsPicSlcLcu - index_IsPicSlcLcu + HevcDecoder_Algo_Parser_IsPicSlcLcu->read_inds[1]) {
			stop = 1;
		}
		if (1 > SIZE_TilesCoord - index_TilesCoord + HevcDecoder_Algo_Parser_TilesCoord->read_inds[0]) {
			stop = 1;
		}
		if (1 > SIZE_TilesCoord - index_TilesCoord + HevcDecoder_Algo_Parser_TilesCoord->read_inds[1]) {
			stop = 1;
		}
		if (1 > SIZE_TilesCoord - index_TilesCoord + HevcDecoder_Algo_Parser_TilesCoord->read_inds[2]) {
			stop = 1;
		}
		if (1 > SIZE_TilesCoord - index_TilesCoord + HevcDecoder_Algo_Parser_TilesCoord->read_inds[3]) {
			stop = 1;
		}
		if (1 > SIZE_TilesCoord - index_TilesCoord + HevcDecoder_Algo_Parser_TilesCoord->read_inds[4]) {
			stop = 1;
		}
		if (1 > SIZE_LFAcrossSlcTile - index_LFAcrossSlcTile + HevcDecoder_Algo_Parser_LFAcrossSlcTile->read_inds[0]) {
			stop = 1;
		}
		if (1 > SIZE_LFAcrossSlcTile - index_LFAcrossSlcTile + HevcDecoder_Algo_Parser_LFAcrossSlcTile->read_inds[1]) {
			stop = 1;
		}
		if (2 > SIZE_PictSize - index_PictSize + HevcDecoder_Algo_Parser_PictSize->read_inds[0]) {
			stop = 1;
		}
		if (2 > SIZE_PictSize - index_PictSize + HevcDecoder_Algo_Parser_PictSize->read_inds[1]) {
			stop = 1;
		}
		if (2 > SIZE_PictSize - index_PictSize + HevcDecoder_Algo_Parser_PictSize->read_inds[2]) {
			stop = 1;
		}
		if (2 > SIZE_PictSize - index_PictSize + HevcDecoder_Algo_Parser_PictSize->read_inds[3]) {
			stop = 1;
		}
		if (2 > SIZE_PictSize - index_PictSize + HevcDecoder_Algo_Parser_PictSize->read_inds[4]) {
			stop = 1;
		}
		if (1 > SIZE_IsPicSlc - index_IsPicSlc + HevcDecoder_Algo_Parser_IsPicSlc->read_inds[0]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_read_SliceData;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		{
			int isAligned = 1;
			isAligned &= ((index_MvPredSyntaxElem % SIZE_MvPredSyntaxElem) < ((index_MvPredSyntaxElem + 4) % SIZE_MvPredSyntaxElem));
			isAligned &= ((index_PictSize % SIZE_PictSize) < ((index_PictSize + 2) % SIZE_PictSize));
			if (isAligned) {
				read_SliceData_noInit_isSlc_aligned();
			} else {
				read_SliceData_noInit_isSlc();
			}
		}
		i++;
		goto l_read_SliceData;
	} else if (isSchedulable_read_SliceData_start()) {
		int stop = 0;
		if (2 > SIZE_SliceAddr - index_SliceAddr + HevcDecoder_Algo_Parser_SliceAddr->read_inds[0]) {
			stop = 1;
		}
		if (2 > SIZE_SliceAddr - index_SliceAddr + HevcDecoder_Algo_Parser_SliceAddr->read_inds[1]) {
			stop = 1;
		}
		if (2 > SIZE_SliceAddr - index_SliceAddr + HevcDecoder_Algo_Parser_SliceAddr->read_inds[2]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_read_SliceData;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		read_SliceData_start_aligned();
		i++;
		goto l_read_SliceData;
	} else if (isSchedulable_read_SliceData_gotoCodingTree_start()) {
		read_SliceData_gotoCodingTree_start();
		i++;
		goto l_read_CodingTree;
	} else if (isSchedulable_read_SliceData_gotoCodingTree_byPass()) {
		read_SliceData_gotoCodingTree_byPass();
		i++;
		goto l_read_CodingTree;
	} else if (isSchedulable_read_SliceData_retCodingTree()) {
		read_SliceData_retCodingTree();
		i++;
		goto l_read_SliceData;
	} else if (isSchedulable_read_SliceData_end()) {
		read_SliceData_end();
		i++;
		goto l_byte_align;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_read_SliceData;
		goto finished;
	}
l_read_SliceHeader:
	HevcDecoder_Algo_Parser_outside_FSM_scheduler(si);
	i += si->num_firings;
	if (isSchedulable_read_SliceHeader_se_idx_1()) {
		int stop = 0;
		if (1 > SIZE_PartMode - index_PartMode + HevcDecoder_Algo_Parser_PartMode->read_inds[0]) {
			stop = 1;
		}
		if (1 > SIZE_PartMode - index_PartMode + HevcDecoder_Algo_Parser_PartMode->read_inds[1]) {
			stop = 1;
		}
		if (1 > SIZE_PartMode - index_PartMode + HevcDecoder_Algo_Parser_PartMode->read_inds[2]) {
			stop = 1;
		}
		if (1 > SIZE_PartMode - index_PartMode + HevcDecoder_Algo_Parser_PartMode->read_inds[3]) {
			stop = 1;
		}
		if (1 > SIZE_PartMode - index_PartMode + HevcDecoder_Algo_Parser_PartMode->read_inds[4]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_read_SliceHeader;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		read_SliceHeader_se_idx_1();
		i++;
		goto l_read_SliceHeader;
	} else if (isSchedulable_read_SliceHeader_se_idx_11()) {
		int stop = 0;
		if (1 > SIZE_Poc - index_Poc + HevcDecoder_Algo_Parser_Poc->read_inds[0]) {
			stop = 1;
		}
		if (1 > SIZE_Poc - index_Poc + HevcDecoder_Algo_Parser_Poc->read_inds[1]) {
			stop = 1;
		}
		if (1 > SIZE_Poc - index_Poc + HevcDecoder_Algo_Parser_Poc->read_inds[2]) {
			stop = 1;
		}
		if (1 > SIZE_SliceType - index_SliceType + HevcDecoder_Algo_Parser_SliceType->read_inds[0]) {
			stop = 1;
		}
		if (1 > SIZE_SliceType - index_SliceType + HevcDecoder_Algo_Parser_SliceType->read_inds[1]) {
			stop = 1;
		}
		if (1 > SIZE_LcuSizeMax - index_LcuSizeMax + HevcDecoder_Algo_Parser_LcuSizeMax->read_inds[0]) {
			stop = 1;
		}
		if (1 > SIZE_LcuSizeMax - index_LcuSizeMax + HevcDecoder_Algo_Parser_LcuSizeMax->read_inds[1]) {
			stop = 1;
		}
		if (1 > SIZE_LcuSizeMax - index_LcuSizeMax + HevcDecoder_Algo_Parser_LcuSizeMax->read_inds[2]) {
			stop = 1;
		}
		if (1 > SIZE_LcuSizeMax - index_LcuSizeMax + HevcDecoder_Algo_Parser_LcuSizeMax->read_inds[3]) {
			stop = 1;
		}
		if (1 > SIZE_LcuSizeMax - index_LcuSizeMax + HevcDecoder_Algo_Parser_LcuSizeMax->read_inds[4]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_read_SliceHeader;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		read_SliceHeader_se_idx_11();
		i++;
		goto l_read_SliceHeader;
	} else if (isSchedulable_read_SliceHeader_se_idx_12()) {
		read_SliceHeader_se_idx_12();
		i++;
		goto l_read_SliceHeader;
	} else if (isSchedulable_read_SliceHeader_se_idx_12_loop1()) {
		read_SliceHeader_se_idx_12_loop1();
		i++;
		goto l_read_SliceHeader;
	} else if (isSchedulable_read_SliceHeader_se_idx_12_end_loop1()) {
		read_SliceHeader_se_idx_12_end_loop1();
		i++;
		goto l_read_SliceHeader;
	} else if (isSchedulable_read_SliceHeader_se_idx_12_loop2()) {
		read_SliceHeader_se_idx_12_loop2();
		i++;
		goto l_read_SliceHeader;
	} else if (isSchedulable_read_SliceHeader_se_idx_12_end_loop2()) {
		read_SliceHeader_se_idx_12_end_loop2();
		i++;
		goto l_read_SliceHeader;
	} else if (isSchedulable_read_SliceHeader_se_idx_13()) {
		read_SliceHeader_se_idx_13();
		i++;
		goto l_read_SliceHeader;
	} else if (isSchedulable_read_SliceHeader_se_idx_14()) {
		read_SliceHeader_se_idx_14();
		i++;
		goto l_read_SliceHeader;
	} else if (isSchedulable_read_SliceHeader_se_idx_2()) {
		read_SliceHeader_se_idx_2();
		i++;
		goto l_read_SliceHeader;
	} else if (isSchedulable_read_SliceHeader_sendRefPOC_init()) {
		int stop = 0;
		if (2 > SIZE_NumRefIdxLxActive - index_NumRefIdxLxActive + HevcDecoder_Algo_Parser_NumRefIdxLxActive->read_inds[0]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_read_SliceHeader;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		read_SliceHeader_sendRefPOC_init_aligned();
		i++;
		goto l_read_SliceHeader;
	} else if (isSchedulable_read_SliceHeader_sendListEntryL0Flag()) {
		int stop = 0;
		if (1 > SIZE_RefPicListModif - index_RefPicListModif + HevcDecoder_Algo_Parser_RefPicListModif->read_inds[0]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_read_SliceHeader;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		read_SliceHeader_sendListEntryL0Flag();
		i++;
		goto l_read_SliceHeader;
	} else if (isSchedulable_read_SliceHeader_sendListEntryL0Loop()) {
		int stop = 0;
		if (1 > SIZE_RefPicListModif - index_RefPicListModif + HevcDecoder_Algo_Parser_RefPicListModif->read_inds[0]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_read_SliceHeader;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		read_SliceHeader_sendListEntryL0Loop();
		i++;
		goto l_read_SliceHeader;
	} else if (isSchedulable_read_SliceHeader_sendListEntryL0End()) {
		read_SliceHeader_sendListEntryL0End();
		i++;
		goto l_read_SliceHeader;
	} else if (isSchedulable_read_SliceHeader_sendListEntryL1Flag()) {
		int stop = 0;
		if (1 > SIZE_RefPicListModif - index_RefPicListModif + HevcDecoder_Algo_Parser_RefPicListModif->read_inds[0]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_read_SliceHeader;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		read_SliceHeader_sendListEntryL1Flag();
		i++;
		goto l_read_SliceHeader;
	} else if (isSchedulable_read_SliceHeader_sendListEntryL1Loop()) {
		int stop = 0;
		if (1 > SIZE_RefPicListModif - index_RefPicListModif + HevcDecoder_Algo_Parser_RefPicListModif->read_inds[0]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_read_SliceHeader;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		read_SliceHeader_sendListEntryL1Loop();
		i++;
		goto l_read_SliceHeader;
	} else if (isSchedulable_read_SliceHeader_sendListEntryL1End()) {
		read_SliceHeader_sendListEntryL1End();
		i++;
		goto l_read_SliceHeader;
	} else if (isSchedulable_read_SliceHeader_sendRefPOC_sendSize()) {
		int stop = 0;
		if (1 > SIZE_RefPoc - index_RefPoc + HevcDecoder_Algo_Parser_RefPoc->read_inds[0]) {
			stop = 1;
		}
		if (1 > SIZE_RefPoc - index_RefPoc + HevcDecoder_Algo_Parser_RefPoc->read_inds[1]) {
			stop = 1;
		}
		if (1 > SIZE_RefPoc - index_RefPoc + HevcDecoder_Algo_Parser_RefPoc->read_inds[2]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_read_SliceHeader;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		read_SliceHeader_sendRefPOC_sendSize();
		i++;
		goto l_read_SliceHeader;
	} else if (isSchedulable_read_SliceHeader_sendRefPOC_sendRefPoc()) {
		int stop = 0;
		if (1 > SIZE_RefPoc - index_RefPoc + HevcDecoder_Algo_Parser_RefPoc->read_inds[0]) {
			stop = 1;
		}
		if (1 > SIZE_RefPoc - index_RefPoc + HevcDecoder_Algo_Parser_RefPoc->read_inds[1]) {
			stop = 1;
		}
		if (1 > SIZE_RefPoc - index_RefPoc + HevcDecoder_Algo_Parser_RefPoc->read_inds[2]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_read_SliceHeader;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		read_SliceHeader_sendRefPOC_sendRefPoc();
		i++;
		goto l_read_SliceHeader;
	} else if (isSchedulable_read_SliceHeader_se_idx_3()) {
		int stop = 0;
		if (1 > SIZE_WeightedPred - index_WeightedPred + HevcDecoder_Algo_Parser_WeightedPred->read_inds[0]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_read_SliceHeader;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		read_SliceHeader_se_idx_3();
		i++;
		goto l_read_SliceHeader;
	} else if (isSchedulable_weighted_start()) {
		int stop = 0;
		if (2 > SIZE_WeightedPred - index_WeightedPred + HevcDecoder_Algo_Parser_WeightedPred->read_inds[0]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_read_SliceHeader;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		{
			int isAligned = 1;
			isAligned &= ((index_WeightedPred % SIZE_WeightedPred) < ((index_WeightedPred + 2) % SIZE_WeightedPred));
			if (isAligned) {
				weighted_start_aligned();
			} else {
				weighted_start();
			}
		}
		i++;
		goto l_weightedLuma0;
	} else if (isSchedulable_read_SliceHeader_se_idx_5()) {
		int stop = 0;
		if (1 > SIZE_DBFDisable - index_DBFDisable + HevcDecoder_Algo_Parser_DBFDisable->read_inds[0]) {
			stop = 1;
		}
		if (4 > SIZE_DbfSe - index_DbfSe + HevcDecoder_Algo_Parser_DbfSe->read_inds[0]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_read_SliceHeader;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		{
			int isAligned = 1;
			if (isAligned) {
				read_SliceHeader_se_idx_5_aligned();
			} else {
				read_SliceHeader_se_idx_5();
			}
		}
		i++;
		goto l_read_SliceHeader;
	} else if (isSchedulable_read_SliceHeader_se_idx_6()) {
		read_SliceHeader_se_idx_6();
		i++;
		goto l_read_SliceHeader;
	} else if (isSchedulable_read_SliceHeader_se_idx_7_loop()) {
		read_SliceHeader_se_idx_7_loop();
		i++;
		goto l_read_SliceHeader;
	} else if (isSchedulable_read_SliceHeader_se_idx_7_endLoop()) {
		read_SliceHeader_se_idx_7_endLoop();
		i++;
		goto l_read_SliceHeader;
	} else if (isSchedulable_read_SliceHeader_se_idx_8()) {
		read_SliceHeader_se_idx_8();
		i++;
		goto l_read_SliceHeader;
	} else if (isSchedulable_read_SliceHeader_se_idx_9_loop()) {
		read_SliceHeader_se_idx_9_loop();
		i++;
		goto l_read_SliceHeader;
	} else if (isSchedulable_read_SliceHeader_se_idx_9_endLoop()) {
		read_SliceHeader_se_idx_9_endLoop();
		i++;
		goto l_read_SliceHeader;
	} else if (isSchedulable_read_SliceHeader_done()) {
		int stop = 0;
		if (2 > SIZE_StrongIntraSmoothing - index_StrongIntraSmoothing + HevcDecoder_Algo_Parser_StrongIntraSmoothing->read_inds[0]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_read_SliceHeader;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		read_SliceHeader_done_aligned();
		i++;
		goto l_read_SliceData;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_read_SliceHeader;
		goto finished;
	}
l_read_TransformTree:
	HevcDecoder_Algo_Parser_outside_FSM_scheduler(si);
	i += si->num_firings;
	if (isSchedulable_read_TransformTree_start()) {
		read_TransformTree_start();
		i++;
		goto l_read_TransformTree;
	} else if (isSchedulable_read_TransformTree_start_nonPartNxN()) {
		int stop = 0;
		if (1 > SIZE_SplitTransform - index_SplitTransform + HevcDecoder_Algo_Parser_SplitTransform->read_inds[0]) {
			stop = 1;
		}
		if (1 > SIZE_SplitTransform - index_SplitTransform + HevcDecoder_Algo_Parser_SplitTransform->read_inds[1]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_read_TransformTree;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		read_TransformTree_start_nonPartNxN();
		i++;
		goto l_read_TransformTree;
	} else if (isSchedulable_read_TransformTree_gotoTransformUnit()) {
		int stop = 0;
		if (1 > SIZE_Cbf - index_Cbf + HevcDecoder_Algo_Parser_Cbf->read_inds[0]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_read_TransformTree;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		read_TransformTree_gotoTransformUnit();
		i++;
		goto l_read_TransformUnit;
	} else if (isSchedulable_read_TransformTree_gotoTransformTree()) {
		read_TransformTree_gotoTransformTree();
		i++;
		goto l_read_TransformTree;
	} else if (isSchedulable_read_TransformTree_end()) {
		read_TransformTree_end();
		i++;
		goto l_read_CodingUnit;
	} else if (isSchedulable_read_TransformTree_endCall()) {
		read_TransformTree_endCall();
		i++;
		goto l_read_TransformTree;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_read_TransformTree;
		goto finished;
	}
l_read_TransformUnit:
	HevcDecoder_Algo_Parser_outside_FSM_scheduler(si);
	i += si->num_firings;
	if (isSchedulable_read_TransformUnit_start()) {
		read_TransformUnit_start();
		i++;
		goto l_read_TransformUnit;
	} else if (isSchedulable_read_TransformUnit_retLuma()) {
		read_TransformUnit_retLuma();
		i++;
		goto l_read_TransformUnit;
	} else if (isSchedulable_read_TransformUnit_retCb()) {
		read_TransformUnit_retCb();
		i++;
		goto l_read_TransformUnit;
	} else if (isSchedulable_read_TransformUnit_gotoResidualCoding()) {
		read_TransformUnit_gotoResidualCoding();
		i++;
		goto l_read_ResidualCoding;
	} else if (isSchedulable_read_TransformUnit_skipResidualCoding()) {
		int stop = 0;
		if (7 > SIZE_TUSize - index_TUSize + HevcDecoder_Algo_Parser_TUSize->read_inds[0]) {
			stop = 1;
		}
		if (7 > SIZE_TUSize - index_TUSize + HevcDecoder_Algo_Parser_TUSize->read_inds[1]) {
			stop = 1;
		}
		if (7 > SIZE_TUSize - index_TUSize + HevcDecoder_Algo_Parser_TUSize->read_inds[2]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_read_TransformUnit;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		{
			int isAligned = 1;
			isAligned &= ((index_TUSize % SIZE_TUSize) < ((index_TUSize + 7) % SIZE_TUSize));
			if (isAligned) {
				read_TransformUnit_skipResidualCoding_aligned();
			} else {
				read_TransformUnit_skipResidualCoding();
			}
		}
		i++;
		goto l_read_TransformUnit;
	} else if (isSchedulable_read_TransformUnit_end()) {
		read_TransformUnit_end();
		i++;
		goto l_read_TransformTree;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_read_TransformUnit;
		goto finished;
	}
l_read_VPS_Header:
	HevcDecoder_Algo_Parser_outside_FSM_scheduler(si);
	i += si->num_firings;
	if (isSchedulable_read_VPS_Header_se_idx_1()) {
		read_VPS_Header_se_idx_1();
		i++;
		goto l_read_VPS_Header;
	} else if (isSchedulable_read_VPS_Header_se_idx_2()) {
		read_VPS_Header_se_idx_2();
		i++;
		goto l_read_VPS_Header;
	} else if (isSchedulable_read_VPS_Header_se_idx_3()) {
		read_VPS_Header_se_idx_3();
		i++;
		goto l_read_VPS_Header;
	} else if (isSchedulable_read_VPS_Header_se_idx_4_loop1()) {
		read_VPS_Header_se_idx_4_loop1();
		i++;
		goto l_read_VPS_Header;
	} else if (isSchedulable_read_VPS_Header_se_idx_4_insertedCond()) {
		read_VPS_Header_se_idx_4_insertedCond();
		i++;
		goto l_read_VPS_Header;
	} else if (isSchedulable_read_VPS_Header_se_idx_4_loop2()) {
		read_VPS_Header_se_idx_4_loop2();
		i++;
		goto l_read_VPS_Header;
	} else if (isSchedulable_read_VPS_Header_se_idx_4_loop1End()) {
		read_VPS_Header_se_idx_4_loop1End();
		i++;
		goto l_read_VPS_Header;
	} else if (isSchedulable_read_VPS_Header_se_idx_4_loop2End()) {
		read_VPS_Header_se_idx_4_loop2End();
		i++;
		goto l_read_VPS_Header;
	} else if (isSchedulable_read_VPS_Header_se_idx_4_decodeInfoPresentFlag()) {
		read_VPS_Header_se_idx_4_decodeInfoPresentFlag();
		i++;
		goto l_read_VPS_Header;
	} else if (isSchedulable_read_VPS_Header_se_idx_5_loop11()) {
		read_VPS_Header_se_idx_5_loop11();
		i++;
		goto l_read_VPS_Header;
	} else if (isSchedulable_read_VPS_Header_se_idx_5_loopEnd()) {
		read_VPS_Header_se_idx_5_loopEnd();
		i++;
		goto l_read_VPS_Header;
	} else if (isSchedulable_read_VPS_Header_se_idx_6_loop()) {
		read_VPS_Header_se_idx_6_loop();
		i++;
		goto l_read_VPS_Header;
	} else if (isSchedulable_read_VPS_Header_se_idx_6_loopEnd()) {
		read_VPS_Header_se_idx_6_loopEnd();
		i++;
		goto l_read_VPS_Header;
	} else if (isSchedulable_read_VPS_Header_se_idx_7()) {
		read_VPS_Header_se_idx_7();
		i++;
		goto l_read_VPS_Header;
	} else if (isSchedulable_read_VPS_Header_se_idx_8()) {
		read_VPS_Header_se_idx_8();
		i++;
		goto l_read_VPS_Header;
	} else if (isSchedulable_read_VPS_Header_se_idx_9_loop()) {
		read_VPS_Header_se_idx_9_loop();
		i++;
		goto l_read_VPS_Header;
	} else if (isSchedulable_read_VPS_Header_se_idx_9_loopEnd()) {
		read_VPS_Header_se_idx_9_loopEnd();
		i++;
		goto l_read_VPS_Header;
	} else if (isSchedulable_read_VPS_Header_done()) {
		read_VPS_Header_done();
		i++;
		goto l_byte_align;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_read_VPS_Header;
		goto finished;
	}
l_sendQp:
	HevcDecoder_Algo_Parser_outside_FSM_scheduler(si);
	i += si->num_firings;
	if (isSchedulable_read_CodingUnit_end_sendQp_blk4x4()) {
		int stop = 0;
		if (1 > SIZE_Qp - index_Qp + HevcDecoder_Algo_Parser_Qp->read_inds[0]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_sendQp;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		read_CodingUnit_end_sendQp_blk4x4();
		i++;
		goto l_read_CodingQuadTree;
	} else if (isSchedulable_read_CodingUnit_end_sendQp_blk8x8()) {
		int stop = 0;
		if (4 > SIZE_Qp - index_Qp + HevcDecoder_Algo_Parser_Qp->read_inds[0]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_sendQp;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		{
			int isAligned = 1;
			isAligned &= ((index_Qp % SIZE_Qp) < ((index_Qp + 4) % SIZE_Qp));
			if (isAligned) {
				read_CodingUnit_end_sendQp_blk8x8_aligned();
			} else {
				read_CodingUnit_end_sendQp_blk8x8();
			}
		}
		i++;
		goto l_read_CodingQuadTree;
	} else if (isSchedulable_read_CodingUnit_end_sendQp_blk16x16()) {
		int stop = 0;
		if (16 > SIZE_Qp - index_Qp + HevcDecoder_Algo_Parser_Qp->read_inds[0]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_sendQp;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		{
			int isAligned = 1;
			isAligned &= ((index_Qp % SIZE_Qp) < ((index_Qp + 16) % SIZE_Qp));
			if (isAligned) {
				read_CodingUnit_end_sendQp_blk16x16_aligned();
			} else {
				read_CodingUnit_end_sendQp_blk16x16();
			}
		}
		i++;
		goto l_read_CodingQuadTree;
	} else if (isSchedulable_read_CodingUnit_end_sendQp_blk32x32()) {
		int stop = 0;
		if (64 > SIZE_Qp - index_Qp + HevcDecoder_Algo_Parser_Qp->read_inds[0]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_sendQp;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		{
			int isAligned = 1;
			isAligned &= ((index_Qp % SIZE_Qp) < ((index_Qp + 64) % SIZE_Qp));
			if (isAligned) {
				read_CodingUnit_end_sendQp_blk32x32_aligned();
			} else {
				read_CodingUnit_end_sendQp_blk32x32();
			}
		}
		i++;
		goto l_read_CodingQuadTree;
	} else if (isSchedulable_read_CodingUnit_end_sendQp_blk64x64()) {
		int stop = 0;
		if (256 > SIZE_Qp - index_Qp + HevcDecoder_Algo_Parser_Qp->read_inds[0]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_sendQp;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		{
			int isAligned = 1;
			isAligned &= ((index_Qp % SIZE_Qp) < ((index_Qp + 256) % SIZE_Qp));
			if (isAligned) {
				read_CodingUnit_end_sendQp_blk64x64_aligned();
			} else {
				read_CodingUnit_end_sendQp_blk64x64();
			}
		}
		i++;
		goto l_read_CodingQuadTree;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_sendQp;
		goto finished;
	}
l_send_IntraPredMode:
	HevcDecoder_Algo_Parser_outside_FSM_scheduler(si);
	i += si->num_firings;
	if (isSchedulable_sendIntraPredMode_skip()) {
		sendIntraPredMode_skip();
		i++;
		goto l_read_CodingUnit;
	} else if (isSchedulable_sendIntraPredMode_part2Nx2N()) {
		int stop = 0;
		if (2 > SIZE_IntraPredMode - index_IntraPredMode + HevcDecoder_Algo_Parser_IntraPredMode->read_inds[0]) {
			stop = 1;
		}
		if (5 > SIZE_CUInfo - index_CUInfo + HevcDecoder_Algo_Parser_CUInfo->read_inds[0]) {
			stop = 1;
		}
		if (5 > SIZE_CUInfo - index_CUInfo + HevcDecoder_Algo_Parser_CUInfo->read_inds[1]) {
			stop = 1;
		}
		if (5 > SIZE_CUInfo - index_CUInfo + HevcDecoder_Algo_Parser_CUInfo->read_inds[2]) {
			stop = 1;
		}
		if (5 > SIZE_CUInfo - index_CUInfo + HevcDecoder_Algo_Parser_CUInfo->read_inds[3]) {
			stop = 1;
		}
		if (5 > SIZE_CUInfo - index_CUInfo + HevcDecoder_Algo_Parser_CUInfo->read_inds[4]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_send_IntraPredMode;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		{
			int isAligned = 1;
			isAligned &= ((index_IntraPredMode % SIZE_IntraPredMode) < ((index_IntraPredMode + 2) % SIZE_IntraPredMode));
			isAligned &= ((index_CUInfo % SIZE_CUInfo) < ((index_CUInfo + 5) % SIZE_CUInfo));
			if (isAligned) {
				sendIntraPredMode_part2Nx2N_aligned();
			} else {
				sendIntraPredMode_part2Nx2N();
			}
		}
		i++;
		goto l_read_CodingUnit;
	} else if (isSchedulable_sendIntraPredMode_partNxN()) {
		int stop = 0;
		if (8 > SIZE_IntraPredMode - index_IntraPredMode + HevcDecoder_Algo_Parser_IntraPredMode->read_inds[0]) {
			stop = 1;
		}
		if (20 > SIZE_CUInfo - index_CUInfo + HevcDecoder_Algo_Parser_CUInfo->read_inds[0]) {
			stop = 1;
		}
		if (20 > SIZE_CUInfo - index_CUInfo + HevcDecoder_Algo_Parser_CUInfo->read_inds[1]) {
			stop = 1;
		}
		if (20 > SIZE_CUInfo - index_CUInfo + HevcDecoder_Algo_Parser_CUInfo->read_inds[2]) {
			stop = 1;
		}
		if (20 > SIZE_CUInfo - index_CUInfo + HevcDecoder_Algo_Parser_CUInfo->read_inds[3]) {
			stop = 1;
		}
		if (20 > SIZE_CUInfo - index_CUInfo + HevcDecoder_Algo_Parser_CUInfo->read_inds[4]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_send_IntraPredMode;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		{
			int isAligned = 1;
			isAligned &= ((index_IntraPredMode % SIZE_IntraPredMode) < ((index_IntraPredMode + 8) % SIZE_IntraPredMode));
			isAligned &= ((index_CUInfo % SIZE_CUInfo) < ((index_CUInfo + 20) % SIZE_CUInfo));
			if (isAligned) {
				sendIntraPredMode_partNxN_aligned();
			} else {
				sendIntraPredMode_partNxN();
			}
		}
		i++;
		goto l_read_CodingUnit;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_send_IntraPredMode;
		goto finished;
	}
l_start_code:
	HevcDecoder_Algo_Parser_outside_FSM_scheduler(si);
	i += si->num_firings;
	if (isSchedulable_start_code_search()) {
		start_code_search();
		i++;
		goto l_start_code;
	} else if (isSchedulable_start_code_done()) {
		start_code_done();
		i++;
		goto l_read_Nal_unit_header;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_start_code;
		goto finished;
	}
l_weightedChroma0:
	HevcDecoder_Algo_Parser_outside_FSM_scheduler(si);
	i += si->num_firings;
	if (isSchedulable_weighted_end_chroma_l0()) {
		weighted_end_chroma_l0();
		i++;
		goto l_weightedDeltaLuma0;
	} else if (isSchedulable_weighted_chroma_l0()) {
		int stop = 0;
		if (1 > SIZE_WeightedPred - index_WeightedPred + HevcDecoder_Algo_Parser_WeightedPred->read_inds[0]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_weightedChroma0;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		weighted_chroma_l0();
		i++;
		goto l_weightedChroma0;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_weightedChroma0;
		goto finished;
	}
l_weightedChroma0Offset:
	HevcDecoder_Algo_Parser_outside_FSM_scheduler(si);
	i += si->num_firings;
	if (isSchedulable_weighted_deltaChroma_offset_l0_send()) {
		int stop = 0;
		if (3 > SIZE_WeightedPred - index_WeightedPred + HevcDecoder_Algo_Parser_WeightedPred->read_inds[0]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_weightedChroma0Offset;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		{
			int isAligned = 1;
			isAligned &= ((index_WeightedPred % SIZE_WeightedPred) < ((index_WeightedPred + 3) % SIZE_WeightedPred));
			if (isAligned) {
				weighted_deltaChroma_offset_l0_send_aligned();
			} else {
				weighted_deltaChroma_offset_l0_send();
			}
		}
		i++;
		goto l_weightedDeltaLuma0;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_weightedChroma0Offset;
		goto finished;
	}
l_weightedChroma1:
	HevcDecoder_Algo_Parser_outside_FSM_scheduler(si);
	i += si->num_firings;
	if (isSchedulable_weighted_chroma_l1_skip()) {
		weighted_chroma_l1_skip();
		i++;
		goto l_weightedDeltaLuma1;
	} else if (isSchedulable_weighted_end_chroma_l1()) {
		weighted_end_chroma_l1();
		i++;
		goto l_weightedDeltaLuma1;
	} else if (isSchedulable_weighted_chroma_l1()) {
		int stop = 0;
		if (1 > SIZE_WeightedPred - index_WeightedPred + HevcDecoder_Algo_Parser_WeightedPred->read_inds[0]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_weightedChroma1;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		weighted_chroma_l1();
		i++;
		goto l_weightedChroma1;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_weightedChroma1;
		goto finished;
	}
l_weightedChroma1Offset:
	HevcDecoder_Algo_Parser_outside_FSM_scheduler(si);
	i += si->num_firings;
	if (isSchedulable_weighted_deltaChroma_offset_l1_send()) {
		int stop = 0;
		if (3 > SIZE_WeightedPred - index_WeightedPred + HevcDecoder_Algo_Parser_WeightedPred->read_inds[0]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_weightedChroma1Offset;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		{
			int isAligned = 1;
			isAligned &= ((index_WeightedPred % SIZE_WeightedPred) < ((index_WeightedPred + 3) % SIZE_WeightedPred));
			if (isAligned) {
				weighted_deltaChroma_offset_l1_send_aligned();
			} else {
				weighted_deltaChroma_offset_l1_send();
			}
		}
		i++;
		goto l_weightedDeltaLuma1;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_weightedChroma1Offset;
		goto finished;
	}
l_weightedDeltaChroma0:
	HevcDecoder_Algo_Parser_outside_FSM_scheduler(si);
	i += si->num_firings;
	if (isSchedulable_weighted_deltaChroma_l0_skip()) {
		weighted_deltaChroma_l0_skip();
		i++;
		goto l_weightedDeltaLuma0;
	} else if (isSchedulable_weighted_deltaChroma_l0_send()) {
		int stop = 0;
		if (1 > SIZE_WeightedPred - index_WeightedPred + HevcDecoder_Algo_Parser_WeightedPred->read_inds[0]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_weightedDeltaChroma0;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		weighted_deltaChroma_l0_send();
		i++;
		goto l_weightedChroma0Offset;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_weightedDeltaChroma0;
		goto finished;
	}
l_weightedDeltaChroma1:
	HevcDecoder_Algo_Parser_outside_FSM_scheduler(si);
	i += si->num_firings;
	if (isSchedulable_weighted_deltaChroma_l1_skip()) {
		weighted_deltaChroma_l1_skip();
		i++;
		goto l_weightedDeltaLuma1;
	} else if (isSchedulable_weighted_deltaChroma_l1_send()) {
		int stop = 0;
		if (1 > SIZE_WeightedPred - index_WeightedPred + HevcDecoder_Algo_Parser_WeightedPred->read_inds[0]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_weightedDeltaChroma1;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		weighted_deltaChroma_l1_send();
		i++;
		goto l_weightedChroma1Offset;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_weightedDeltaChroma1;
		goto finished;
	}
l_weightedDeltaLuma0:
	HevcDecoder_Algo_Parser_outside_FSM_scheduler(si);
	i += si->num_firings;
	if (isSchedulable_weighted_deltaLuma_l0_skip_loop_done()) {
		weighted_deltaLuma_l0_skip_loop_done();
		i++;
		goto l_weightedLuma1;
	} else if (isSchedulable_weighted_deltaLuma_l0__skip_all()) {
		weighted_deltaLuma_l0__skip_all();
		i++;
		goto l_read_SliceHeader;
	} else if (isSchedulable_weighted_deltaLuma_l0_send()) {
		int stop = 0;
		if (2 > SIZE_WeightedPred - index_WeightedPred + HevcDecoder_Algo_Parser_WeightedPred->read_inds[0]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_weightedDeltaLuma0;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		{
			int isAligned = 1;
			isAligned &= ((index_WeightedPred % SIZE_WeightedPred) < ((index_WeightedPred + 2) % SIZE_WeightedPred));
			if (isAligned) {
				weighted_deltaLuma_l0_send_aligned();
			} else {
				weighted_deltaLuma_l0_send();
			}
		}
		i++;
		goto l_weightedDeltaChroma0;
	} else if (isSchedulable_weighted_deltaLuma_l0_skip()) {
		weighted_deltaLuma_l0_skip();
		i++;
		goto l_weightedDeltaChroma0;
	} else if (isSchedulable_weighted_deltaLuma_l0_skip_loop()) {
		weighted_deltaLuma_l0_skip_loop();
		i++;
		goto l_weightedDeltaLuma0;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_weightedDeltaLuma0;
		goto finished;
	}
l_weightedDeltaLuma1:
	HevcDecoder_Algo_Parser_outside_FSM_scheduler(si);
	i += si->num_firings;
	if (isSchedulable_weighted_deltaLuma_l1_skip_loop_done()) {
		weighted_deltaLuma_l1_skip_loop_done();
		i++;
		goto l_read_SliceHeader;
	} else if (isSchedulable_weighted_deltaLuma_l1_send()) {
		int stop = 0;
		if (2 > SIZE_WeightedPred - index_WeightedPred + HevcDecoder_Algo_Parser_WeightedPred->read_inds[0]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_weightedDeltaLuma1;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		{
			int isAligned = 1;
			isAligned &= ((index_WeightedPred % SIZE_WeightedPred) < ((index_WeightedPred + 2) % SIZE_WeightedPred));
			if (isAligned) {
				weighted_deltaLuma_l1_send_aligned();
			} else {
				weighted_deltaLuma_l1_send();
			}
		}
		i++;
		goto l_weightedDeltaChroma1;
	} else if (isSchedulable_weighted_deltaLuma_l1_skip()) {
		weighted_deltaLuma_l1_skip();
		i++;
		goto l_weightedDeltaChroma1;
	} else if (isSchedulable_weighted_deltaLuma_l1_skip_loop()) {
		weighted_deltaLuma_l1_skip_loop();
		i++;
		goto l_weightedDeltaLuma1;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_weightedDeltaLuma1;
		goto finished;
	}
l_weightedLuma0:
	HevcDecoder_Algo_Parser_outside_FSM_scheduler(si);
	i += si->num_firings;
	if (isSchedulable_weighted_end_luma_l0()) {
		weighted_end_luma_l0();
		i++;
		goto l_weightedChroma0;
	} else if (isSchedulable_weighted_luma_l0()) {
		int stop = 0;
		if (1 > SIZE_WeightedPred - index_WeightedPred + HevcDecoder_Algo_Parser_WeightedPred->read_inds[0]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_weightedLuma0;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		weighted_luma_l0();
		i++;
		goto l_weightedLuma0;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_weightedLuma0;
		goto finished;
	}
l_weightedLuma1:
	HevcDecoder_Algo_Parser_outside_FSM_scheduler(si);
	i += si->num_firings;
	if (isSchedulable_weighted_end_luma_l1()) {
		weighted_end_luma_l1();
		i++;
		goto l_weightedChroma1;
	} else if (isSchedulable_weighted_luma_l1()) {
		int stop = 0;
		if (1 > SIZE_WeightedPred - index_WeightedPred + HevcDecoder_Algo_Parser_WeightedPred->read_inds[0]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_weightedLuma1;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		weighted_luma_l1();
		i++;
		goto l_weightedLuma1;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_weightedLuma1;
		goto finished;
	}
finished:
	read_end_byte();
	write_end_CUInfo();
	write_end_IntraPredMode();
	write_end_SliceAddr();
	write_end_TilesCoord();
	write_end_LcuSizeMax();
	write_end_PartMode();
	write_end_IsPicSlcLcu();
	write_end_IsPicSlc();
	write_end_LFAcrossSlcTile();
	write_end_PictSize();
	write_end_Poc();
	write_end_SaoSe();
	write_end_SEI_MD5();
	write_end_SliceType();
	write_end_SplitTransform();
	write_end_TUSize();
	write_end_Coeff();
	write_end_StrongIntraSmoothing();
	write_end_DispCoord();
	write_end_PicSizeInMb();
	write_end_NumRefIdxLxActive();
	write_end_RefPicListModif();
	write_end_RefPoc();
	write_end_MvPredSyntaxElem();
	write_end_Cbf();
	write_end_DBFDisable();
	write_end_DbfSe();
	write_end_ReorderPics();
	write_end_WeightedPred();
	write_end_Qp();
}
