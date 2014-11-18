// Generated from "org.sc29.wg11.mpegh.part2.Top_mpegh_part2_main"

#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "fifo.h"
#include "util.h"
#include "dataflow.h"
#include "serialize.h"
#include "options.h"
#include "scheduler.h"

#define SIZE 8192

/////////////////////////////////////////////////
// FIFO allocation
DECLARE_FIFO(u8, SIZE, 0, 1)
DECLARE_FIFO(u8, SIZE, 1, 5)
DECLARE_FIFO(u8, SIZE, 2, 1)
DECLARE_FIFO(i16, SIZE, 3, 3)
DECLARE_FIFO(u16, SIZE, 4, 1)
DECLARE_FIFO(u8, SIZE, 5, 2)
DECLARE_FIFO(u16, SIZE, 6, 3)
DECLARE_FIFO(i32, SIZE, 7, 1)
DECLARE_FIFO(i8, SIZE, 8, 1)
DECLARE_FIFO(u8, SIZE, 9, 1)
DECLARE_FIFO(u16, SIZE, 10, 5)
DECLARE_FIFO(u8, SIZE, 11, 2)
DECLARE_FIFO(i32, SIZE, 12, 2)
DECLARE_FIFO(u8, SIZE, 13, 1)
DECLARE_FIFO(i16, 16384, 14, 1)
DECLARE_FIFO(u16, SIZE, 15, 5)
DECLARE_FIFO(u16, SIZE, 16, 5)
DECLARE_FIFO(i32, SIZE, 17, 1)
DECLARE_FIFO(i8, SIZE, 18, 1)
DECLARE_FIFO(i16, SIZE, 19, 1)
DECLARE_FIFO(i16, SIZE, 20, 1)
DECLARE_FIFO(u8, SIZE, 21, 1)
DECLARE_FIFO(u16, SIZE, 22, 2)
DECLARE_FIFO(u8, SIZE, 23, 5)
DECLARE_FIFO(i16, 16384, 24, 1)
DECLARE_FIFO(i8, SIZE, 25, 3)
DECLARE_FIFO(i8, SIZE, 26, 1)
DECLARE_FIFO(i32, SIZE, 27, 1)
DECLARE_FIFO(u8, SIZE, 28, 1)
DECLARE_FIFO(i16, SIZE, 29, 3)
DECLARE_FIFO(u8, SIZE, 30, 2)
DECLARE_FIFO(u8, SIZE, 31, 1)
DECLARE_FIFO(u8, SIZE, 32, 2)
DECLARE_FIFO(u8, SIZE, 33, 1)
DECLARE_FIFO(u8, SIZE, 34, 1)
DECLARE_FIFO(u8, SIZE, 35, 3)
DECLARE_FIFO(i16, SIZE, 36, 1)
DECLARE_FIFO(i16, SIZE, 37, 1)
DECLARE_FIFO(i16, SIZE, 38, 1)
DECLARE_FIFO(i16, SIZE, 39, 1)
DECLARE_FIFO(i16, SIZE, 40, 1)
DECLARE_FIFO(i16, SIZE, 41, 1)
DECLARE_FIFO(i16, SIZE, 42, 1)
DECLARE_FIFO(i16, SIZE, 43, 1)
DECLARE_FIFO(i16, SIZE, 44, 1)
DECLARE_FIFO(i16, SIZE, 45, 1)
DECLARE_FIFO(i16, SIZE, 46, 1)
DECLARE_FIFO(i16, SIZE, 47, 1)
DECLARE_FIFO(i16, SIZE, 48, 1)
DECLARE_FIFO(i16, SIZE, 49, 1)
DECLARE_FIFO(i16, SIZE, 50, 1)
DECLARE_FIFO(i16, SIZE, 51, 1)
DECLARE_FIFO(i16, SIZE, 52, 1)
DECLARE_FIFO(i16, SIZE, 53, 1)
DECLARE_FIFO(i16, SIZE, 54, 1)
DECLARE_FIFO(i16, SIZE, 55, 1)
DECLARE_FIFO(i16, SIZE, 56, 1)
DECLARE_FIFO(i16, SIZE, 57, 1)
DECLARE_FIFO(i16, SIZE, 58, 1)
DECLARE_FIFO(i16, SIZE, 59, 1)
DECLARE_FIFO(i16, SIZE, 60, 1)
DECLARE_FIFO(i16, SIZE, 61, 1)
DECLARE_FIFO(i16, SIZE, 62, 2)
DECLARE_FIFO(i16, SIZE, 63, 2)
DECLARE_FIFO(u8, SIZE, 64, 1)
DECLARE_FIFO(u8, SIZE, 65, 1)
DECLARE_FIFO(u8, SIZE, 66, 1)
DECLARE_FIFO(i32, SIZE, 67, 3)
DECLARE_FIFO(u8, SIZE, 68, 3)
DECLARE_FIFO(u8, SIZE, 69, 1)
DECLARE_FIFO(u8, SIZE, 70, 1)
DECLARE_FIFO(u8, SIZE, 71, 1)
DECLARE_FIFO(u8, SIZE, 72, 1)
DECLARE_FIFO(u32, SIZE, 73, 1)
DECLARE_FIFO(u32, SIZE, 74, 1)
DECLARE_FIFO(u8, SIZE, 75, 1)
DECLARE_FIFO(u64, SIZE, 76, 1)

/////////////////////////////////////////////////
// FIFO pointer assignments
fifo_u8_t *Source_O = &fifo_0;
fifo_u8_t *HevcDecoder_Algo_Parser_byte = &fifo_0;

fifo_u8_t *HevcDecoder_Algo_Parser_PartMode = &fifo_1;
fifo_u8_t *HevcDecoder_IntraPrediction_PartMode = &fifo_1;
fifo_u8_t *HevcDecoder_SelectCU_PartMode = &fifo_1;
fifo_u8_t *HevcDecoder_InterPrediction_PartMode = &fifo_1;
fifo_u8_t *HevcDecoder_generateInfo_MvComponentPred_PartMode = &fifo_1;
fifo_u8_t *HevcDecoder_DBFilter_GenerateBs_PartMode = &fifo_1;

fifo_u8_t *HevcDecoder_Algo_Parser_NumRefIdxLxActive = &fifo_2;
fifo_u8_t *HevcDecoder_generateInfo_GenerateRefList_NumRefIdxLXAct = &fifo_2;

fifo_i16_t *HevcDecoder_Algo_Parser_Poc = &fifo_3;
fifo_i16_t *HevcDecoder_DecodingPictureBuffer_Poc = &fifo_3;
fifo_i16_t *HevcDecoder_InterPrediction_Poc = &fifo_3;
fifo_i16_t *HevcDecoder_generateInfo_MvComponentPred_Poc = &fifo_3;

fifo_u16_t *HevcDecoder_Algo_Parser_DispCoord = &fifo_4;
fifo_u16_t *display_DispCoord = &fifo_4;

fifo_u8_t *HevcDecoder_Algo_Parser_IsPicSlcLcu = &fifo_5;
fifo_u8_t *HevcDecoder_SAO_IsPicSlcLcu = &fifo_5;
fifo_u8_t *HevcDecoder_DBFilter_DeblockFilt_IsPicSlcLcu = &fifo_5;

fifo_u16_t *HevcDecoder_Algo_Parser_SliceAddr = &fifo_6;
fifo_u16_t *HevcDecoder_IntraPrediction_SliceAddr = &fifo_6;
fifo_u16_t *HevcDecoder_generateInfo_MvComponentPred_SliceAddr = &fifo_6;
fifo_u16_t *HevcDecoder_DBFilter_GenerateBs_SliceAddr = &fifo_6;

fifo_i32_t *HevcDecoder_Algo_Parser_Cbf = &fifo_7;
fifo_i32_t *HevcDecoder_DBFilter_GenerateBs_Cbf = &fifo_7;

fifo_i8_t *HevcDecoder_Algo_Parser_ReorderPics = &fifo_8;
fifo_u8_t *HevcDecoder_DecodingPictureBuffer_ReorderPics = &fifo_8;

fifo_u8_t *HevcDecoder_Algo_Parser_SEI_MD5 = &fifo_9;
fifo_u8_t *check_MD5_compute_SEI_MD5 = &fifo_9;

fifo_u16_t *HevcDecoder_Algo_Parser_TilesCoord = &fifo_10;
fifo_u16_t *HevcDecoder_IntraPrediction_TilesCoord = &fifo_10;
fifo_u16_t *HevcDecoder_SAO_TilesCoord = &fifo_10;
fifo_u16_t *HevcDecoder_generateInfo_MvComponentPred_TilesCoord = &fifo_10;
fifo_u16_t *HevcDecoder_DBFilter_GenerateBs_TilesCoord = &fifo_10;
fifo_u16_t *HevcDecoder_DBFilter_DeblockFilt_TilesCoord = &fifo_10;

fifo_u8_t *HevcDecoder_Algo_Parser_SliceType = &fifo_11;
fifo_u8_t *HevcDecoder_InterPrediction_SliceType = &fifo_11;
fifo_u8_t *HevcDecoder_generateInfo_MvComponentPred_SliceType = &fifo_11;

fifo_i32_t *HevcDecoder_Algo_Parser_SplitTransform = &fifo_12;
fifo_i32_t *HevcDecoder_IntraPrediction_SplitTransform = &fifo_12;
fifo_i32_t *HevcDecoder_DBFilter_GenerateBs_SplitTransf = &fifo_12;

fifo_u8_t *HevcDecoder_Algo_Parser_IntraPredMode = &fifo_13;
fifo_u8_t *HevcDecoder_IntraPrediction_IntraPredMode = &fifo_13;

fifo_i16_t *HevcDecoder_Algo_Parser_SaoSe = &fifo_14;
fifo_i16_t *HevcDecoder_SAO_SaoSe = &fifo_14;

fifo_u16_t *HevcDecoder_Algo_Parser_PictSize = &fifo_15;
fifo_u16_t *HevcDecoder_IntraPrediction_PictSize = &fifo_15;
fifo_u16_t *HevcDecoder_DecodingPictureBuffer_PicSize = &fifo_15;
fifo_u16_t *HevcDecoder_SAO_PicSize = &fifo_15;
fifo_u16_t *HevcDecoder_generateInfo_MvComponentPred_PicSize = &fifo_15;
fifo_u16_t *HevcDecoder_DBFilter_DeblockFilt_PicSize = &fifo_15;

fifo_u16_t *HevcDecoder_Algo_Parser_CUInfo = &fifo_16;
fifo_u16_t *HevcDecoder_IntraPrediction_CUInfo = &fifo_16;
fifo_u16_t *HevcDecoder_InterPrediction_CUInfo = &fifo_16;
fifo_u16_t *HevcDecoder_SelectCU_CUInfo = &fifo_16;
fifo_u16_t *HevcDecoder_generateInfo_MvComponentPred_CUInfo = &fifo_16;
fifo_u16_t *HevcDecoder_DBFilter_GenerateBs_CUInfo = &fifo_16;

fifo_i32_t *HevcDecoder_Algo_Parser_DBFDisable = &fifo_17;
fifo_i32_t *HevcDecoder_DBFilter_DeblockFilt_DBFDisable = &fifo_17;

fifo_i8_t *HevcDecoder_Algo_Parser_DbfSe = &fifo_18;
fifo_i8_t *HevcDecoder_DBFilter_DeblockFilt_SyntaxElem = &fifo_18;

fifo_i16_t *HevcDecoder_Algo_Parser_MvPredSyntaxElem = &fifo_19;
fifo_i16_t *HevcDecoder_generateInfo_MvComponentPred_SyntaxElem = &fifo_19;

fifo_i16_t *HevcDecoder_Algo_Parser_Coeff = &fifo_20;
fifo_i16_t *HevcDecoder_xIT_IT_Splitter_Coeff = &fifo_20;

fifo_u8_t *HevcDecoder_Algo_Parser_IsPicSlc = &fifo_21;
fifo_u8_t *HevcDecoder_DecodingPictureBuffer_IsPicSlc = &fifo_21;

fifo_u16_t *HevcDecoder_Algo_Parser_PicSizeInMb = &fifo_22;
fifo_u16_t *display_PicSizeInMb = &fifo_22;
fifo_u16_t *check_MD5_MD5SplitInfo_PictSize = &fifo_22;

fifo_u8_t *HevcDecoder_Algo_Parser_LcuSizeMax = &fifo_23;
fifo_u8_t *HevcDecoder_IntraPrediction_LcuSizeMax = &fifo_23;
fifo_u8_t *HevcDecoder_SAO_LcuSizeMax = &fifo_23;
fifo_u8_t *HevcDecoder_generateInfo_MvComponentPred_LcuSizeMax = &fifo_23;
fifo_u8_t *HevcDecoder_DBFilter_GenerateBs_LcuSizeMax = &fifo_23;
fifo_u8_t *HevcDecoder_DBFilter_DeblockFilt_LcuSizeMax = &fifo_23;

fifo_i16_t *HevcDecoder_Algo_Parser_WeightedPred = &fifo_24;
fifo_i16_t *HevcDecoder_InterPrediction_WeightedPredSe = &fifo_24;

fifo_i8_t *HevcDecoder_Algo_Parser_TUSize = &fifo_25;
fifo_i8_t *HevcDecoder_xIT_IT_Splitter_Size = &fifo_25;
fifo_i8_t *HevcDecoder_xIT_IT_Merger_Size = &fifo_25;
fifo_i8_t *HevcDecoder_xIT_Block_Merger_Size = &fifo_25;

fifo_i8_t *HevcDecoder_Algo_Parser_Qp = &fifo_26;
fifo_i8_t *HevcDecoder_DBFilter_DeblockFilt_Qp = &fifo_26;

fifo_i32_t *HevcDecoder_Algo_Parser_StrongIntraSmoothing = &fifo_27;
fifo_i32_t *HevcDecoder_IntraPrediction_StrongIntraSmoothing = &fifo_27;

fifo_u8_t *HevcDecoder_Algo_Parser_RefPicListModif = &fifo_28;
fifo_u8_t *HevcDecoder_generateInfo_GenerateRefList_RefPicListModif = &fifo_28;

fifo_i16_t *HevcDecoder_Algo_Parser_RefPoc = &fifo_29;
fifo_i16_t *HevcDecoder_DecodingPictureBuffer_RpsPoc = &fifo_29;
fifo_i16_t *HevcDecoder_generateInfo_GenerateRefList_RefPoc = &fifo_29;
fifo_i16_t *HevcDecoder_generateInfo_MvComponentPred_RpsPoc = &fifo_29;

fifo_u8_t *HevcDecoder_Algo_Parser_LFAcrossSlcTile = &fifo_30;
fifo_u8_t *HevcDecoder_SAO_LFAcrossSlcTile = &fifo_30;
fifo_u8_t *HevcDecoder_DBFilter_GenerateBs_LFAcrossSlcTile = &fifo_30;

fifo_u8_t *HevcDecoder_IntraPrediction_PredSample = &fifo_31;
fifo_u8_t *HevcDecoder_SelectCU_IntraSample = &fifo_31;

fifo_u8_t *HevcDecoder_SelectCU_Sample = &fifo_32;
fifo_u8_t *HevcDecoder_IntraPrediction_Sample = &fifo_32;
fifo_u8_t *HevcDecoder_DBFilter_DeblockFilt_SampleIn = &fifo_32;

fifo_u8_t *HevcDecoder_DecodingPictureBuffer_RefSample = &fifo_33;
fifo_u8_t *HevcDecoder_InterPrediction_Sample = &fifo_33;

fifo_u8_t *HevcDecoder_InterPrediction_PredSample = &fifo_34;
fifo_u8_t *HevcDecoder_SelectCU_InterSample = &fifo_34;

fifo_u8_t *HevcDecoder_SAO_FiltSample = &fifo_35;
fifo_u8_t *HevcDecoder_DecodingPictureBuffer_Sample = &fifo_35;
fifo_u8_t *display_Byte = &fifo_35;
fifo_u8_t *check_MD5_MD5SplitInfo_Byte = &fifo_35;

fifo_i16_t *HevcDecoder_xIT_IT_Splitter_Coeff_32x32 = &fifo_36;
fifo_i16_t *HevcDecoder_xIT_IT32x32_Transpose32x32_0_Src = &fifo_36;

fifo_i16_t *HevcDecoder_xIT_IT_Splitter_Coeff_skip = &fifo_37;
fifo_i16_t *HevcDecoder_xIT_IT_Merger_Block_skip = &fifo_37;

fifo_i16_t *HevcDecoder_xIT_IT_Splitter_Coeff_4x4_DST = &fifo_38;
fifo_i16_t *HevcDecoder_xIT_invDST4x4_1st_IN = &fifo_38;

fifo_i16_t *HevcDecoder_xIT_IT_Splitter_Coeff_8x8 = &fifo_39;
fifo_i16_t *HevcDecoder_xIT_IT8x8_Transpose8x8_0_Src = &fifo_39;

fifo_i16_t *HevcDecoder_xIT_IT_Splitter_Coeff_16x16 = &fifo_40;
fifo_i16_t *HevcDecoder_xIT_IT16x16_Transpose16x16_0_Src = &fifo_40;

fifo_i16_t *HevcDecoder_xIT_IT_Splitter_Coeff_4x4_IT = &fifo_41;
fifo_i16_t *HevcDecoder_xIT_IT4x4_Transpose4x4_0_Src = &fifo_41;

fifo_i16_t *HevcDecoder_xIT_IT_Merger_Block = &fifo_42;
fifo_i16_t *HevcDecoder_xIT_Block_Merger_Block_in = &fifo_42;

fifo_i16_t *HevcDecoder_xIT_invDST4x4_1st_OUT = &fifo_43;
fifo_i16_t *HevcDecoder_xIT_invDST4x4_2nd_IN = &fifo_43;

fifo_i16_t *HevcDecoder_xIT_invDST4x4_2nd_OUT = &fifo_44;
fifo_i16_t *HevcDecoder_xIT_IT_Merger_Block_4x4_DST = &fifo_44;

fifo_i16_t *HevcDecoder_xIT_Block_Merger_Block = &fifo_45;
fifo_i16_t *HevcDecoder_SelectCU_ResidualSample = &fifo_45;

fifo_i16_t *HevcDecoder_xIT_IT4x4_IT4x4_1d_0_Dst = &fifo_46;
fifo_i16_t *HevcDecoder_xIT_IT4x4_Transpose4x4_1_Src = &fifo_46;

fifo_i16_t *HevcDecoder_xIT_IT4x4_Transpose4x4_0_Dst = &fifo_47;
fifo_i16_t *HevcDecoder_xIT_IT4x4_IT4x4_1d_0_Src = &fifo_47;

fifo_i16_t *HevcDecoder_xIT_IT4x4_IT4x4_1d_1_Dst = &fifo_48;
fifo_i16_t *HevcDecoder_xIT_IT_Merger_Block_4x4_IT = &fifo_48;

fifo_i16_t *HevcDecoder_xIT_IT4x4_Transpose4x4_1_Dst = &fifo_49;
fifo_i16_t *HevcDecoder_xIT_IT4x4_IT4x4_1d_1_Src = &fifo_49;

fifo_i16_t *HevcDecoder_xIT_IT8x8_IT8x8_1d_0_Dst = &fifo_50;
fifo_i16_t *HevcDecoder_xIT_IT8x8_Transpose8x8_1_Src = &fifo_50;

fifo_i16_t *HevcDecoder_xIT_IT8x8_Transpose8x8_0_Dst = &fifo_51;
fifo_i16_t *HevcDecoder_xIT_IT8x8_IT8x8_1d_0_Src = &fifo_51;

fifo_i16_t *HevcDecoder_xIT_IT8x8_IT8x8_1d_1_Dst = &fifo_52;
fifo_i16_t *HevcDecoder_xIT_IT_Merger_Block_8x8 = &fifo_52;

fifo_i16_t *HevcDecoder_xIT_IT8x8_Transpose8x8_1_Dst = &fifo_53;
fifo_i16_t *HevcDecoder_xIT_IT8x8_IT8x8_1d_1_Src = &fifo_53;

fifo_i16_t *HevcDecoder_xIT_IT16x16_IT16x16_1d_0_Dst = &fifo_54;
fifo_i16_t *HevcDecoder_xIT_IT16x16_Transpose16x16_1_Src = &fifo_54;

fifo_i16_t *HevcDecoder_xIT_IT16x16_Transpose16x16_0_Dst = &fifo_55;
fifo_i16_t *HevcDecoder_xIT_IT16x16_IT16x16_1d_0_Src = &fifo_55;

fifo_i16_t *HevcDecoder_xIT_IT16x16_IT16x16_1d_1_Dst = &fifo_56;
fifo_i16_t *HevcDecoder_xIT_IT_Merger_Block_16x16 = &fifo_56;

fifo_i16_t *HevcDecoder_xIT_IT16x16_Transpose16x16_1_Dst = &fifo_57;
fifo_i16_t *HevcDecoder_xIT_IT16x16_IT16x16_1d_1_Src = &fifo_57;

fifo_i16_t *HevcDecoder_xIT_IT32x32_IT32x32_1d_0_Dst = &fifo_58;
fifo_i16_t *HevcDecoder_xIT_IT32x32_Transpose32x32_1_Src = &fifo_58;

fifo_i16_t *HevcDecoder_xIT_IT32x32_Transpose32x32_0_Dst = &fifo_59;
fifo_i16_t *HevcDecoder_xIT_IT32x32_IT32x32_1d_0_Src = &fifo_59;

fifo_i16_t *HevcDecoder_xIT_IT32x32_IT32x32_1d_1_Dst = &fifo_60;
fifo_i16_t *HevcDecoder_xIT_IT_Merger_Block_32x32 = &fifo_60;

fifo_i16_t *HevcDecoder_xIT_IT32x32_Transpose32x32_1_Dst = &fifo_61;
fifo_i16_t *HevcDecoder_xIT_IT32x32_IT32x32_1d_1_Src = &fifo_61;

fifo_i16_t *HevcDecoder_generateInfo_GenerateRefList_RefList = &fifo_62;
fifo_i16_t *HevcDecoder_generateInfo_MvComponentPred_RefList = &fifo_62;
fifo_i16_t *HevcDecoder_InterPrediction_RefList = &fifo_62;

fifo_i16_t *HevcDecoder_generateInfo_MvComponentPred_PocRef = &fifo_63;
fifo_i16_t *HevcDecoder_DecodingPictureBuffer_PocRef = &fifo_63;
fifo_i16_t *HevcDecoder_DBFilter_GenerateBs_RefPoc = &fifo_63;

fifo_u8_t *HevcDecoder_generateInfo_MvComponentPred_RefIdx = &fifo_64;
fifo_u8_t *HevcDecoder_InterPrediction_RefIdx = &fifo_64;

fifo_u8_t *HevcDecoder_generateInfo_MvComponentPred_IsReadOrNewSlice = &fifo_65;
fifo_u8_t *HevcDecoder_DecodingPictureBuffer_IsReadOrNewSlc = &fifo_65;

fifo_u8_t *HevcDecoder_generateInfo_MvComponentPred_PredCuSize = &fifo_66;
fifo_u8_t *HevcDecoder_DecodingPictureBuffer_PredCuSize = &fifo_66;

fifo_i32_t *HevcDecoder_generateInfo_MvComponentPred_Mv = &fifo_67;
fifo_i32_t *HevcDecoder_InterPrediction_Mv = &fifo_67;
fifo_i32_t *HevcDecoder_DecodingPictureBuffer_Mv = &fifo_67;
fifo_i32_t *HevcDecoder_DBFilter_GenerateBs_Mv = &fifo_67;

fifo_u8_t *HevcDecoder_generateInfo_MvComponentPred_IsBiPredOrLx = &fifo_68;
fifo_u8_t *HevcDecoder_InterPrediction_IsBiPredOrLx = &fifo_68;
fifo_u8_t *HevcDecoder_DecodingPictureBuffer_IsBiPredOrLx = &fifo_68;
fifo_u8_t *HevcDecoder_DBFilter_GenerateBs_IsBiPredOrLx = &fifo_68;

fifo_u8_t *HevcDecoder_DBFilter_DeblockFilt_FiltSample = &fifo_69;
fifo_u8_t *HevcDecoder_SAO_SampleIn = &fifo_69;

fifo_u8_t *HevcDecoder_DBFilter_GenerateBs_BSVer = &fifo_70;
fifo_u8_t *HevcDecoder_DBFilter_DeblockFilt_BsVer = &fifo_70;

fifo_u8_t *HevcDecoder_DBFilter_GenerateBs_BSHor = &fifo_71;
fifo_u8_t *HevcDecoder_DBFilter_DeblockFilt_BsHor = &fifo_71;

fifo_u8_t *check_MD5_padding_OUT = &fifo_72;
fifo_u8_t *check_MD5_shifter_IN = &fifo_72;

fifo_u32_t *check_MD5_padding_NEWLENGTH = &fifo_73;
fifo_u32_t *check_MD5_compute_NEWLENGTH = &fifo_73;

fifo_u32_t *check_MD5_shifter_OUT = &fifo_74;
fifo_u32_t *check_MD5_compute_IN = &fifo_74;

fifo_u8_t *check_MD5_MD5SplitInfo_DataOut = &fifo_75;
fifo_u8_t *check_MD5_padding_DATA = &fifo_75;

fifo_u64_t *check_MD5_MD5SplitInfo_Length = &fifo_76;
fifo_u64_t *check_MD5_padding_LENGTH = &fifo_76;




/////////////////////////////////////////////////
// Actor functions
extern void Source_initialize(schedinfo_t *si);
extern void Source_scheduler(schedinfo_t *si);
extern void display_initialize(schedinfo_t *si);
extern void display_scheduler(schedinfo_t *si);
extern void HevcDecoder_Algo_Parser_initialize(schedinfo_t *si);
extern void HevcDecoder_Algo_Parser_scheduler(schedinfo_t *si);
extern void HevcDecoder_IntraPrediction_initialize(schedinfo_t *si);
extern void HevcDecoder_IntraPrediction_scheduler(schedinfo_t *si);
extern void HevcDecoder_SelectCU_initialize(schedinfo_t *si);
extern void HevcDecoder_SelectCU_scheduler(schedinfo_t *si);
extern void HevcDecoder_DecodingPictureBuffer_initialize(schedinfo_t *si);
extern void HevcDecoder_DecodingPictureBuffer_scheduler(schedinfo_t *si);
extern void HevcDecoder_InterPrediction_initialize(schedinfo_t *si);
extern void HevcDecoder_InterPrediction_scheduler(schedinfo_t *si);
extern void HevcDecoder_SAO_initialize(schedinfo_t *si);
extern void HevcDecoder_SAO_scheduler(schedinfo_t *si);
extern void HevcDecoder_xIT_IT_Splitter_initialize(schedinfo_t *si);
extern void HevcDecoder_xIT_IT_Splitter_scheduler(schedinfo_t *si);
extern void HevcDecoder_xIT_IT_Merger_initialize(schedinfo_t *si);
extern void HevcDecoder_xIT_IT_Merger_scheduler(schedinfo_t *si);
extern void HevcDecoder_xIT_invDST4x4_1st_initialize(schedinfo_t *si);
extern void HevcDecoder_xIT_invDST4x4_1st_scheduler(schedinfo_t *si);
extern void HevcDecoder_xIT_invDST4x4_2nd_initialize(schedinfo_t *si);
extern void HevcDecoder_xIT_invDST4x4_2nd_scheduler(schedinfo_t *si);
extern void HevcDecoder_xIT_Block_Merger_initialize(schedinfo_t *si);
extern void HevcDecoder_xIT_Block_Merger_scheduler(schedinfo_t *si);
extern void HevcDecoder_xIT_IT4x4_IT4x4_1d_0_initialize(schedinfo_t *si);
extern void HevcDecoder_xIT_IT4x4_IT4x4_1d_0_scheduler(schedinfo_t *si);
extern void HevcDecoder_xIT_IT4x4_Transpose4x4_0_initialize(schedinfo_t *si);
extern void HevcDecoder_xIT_IT4x4_Transpose4x4_0_scheduler(schedinfo_t *si);
extern void HevcDecoder_xIT_IT4x4_IT4x4_1d_1_initialize(schedinfo_t *si);
extern void HevcDecoder_xIT_IT4x4_IT4x4_1d_1_scheduler(schedinfo_t *si);
extern void HevcDecoder_xIT_IT4x4_Transpose4x4_1_initialize(schedinfo_t *si);
extern void HevcDecoder_xIT_IT4x4_Transpose4x4_1_scheduler(schedinfo_t *si);
extern void HevcDecoder_xIT_IT8x8_IT8x8_1d_0_initialize(schedinfo_t *si);
extern void HevcDecoder_xIT_IT8x8_IT8x8_1d_0_scheduler(schedinfo_t *si);
extern void HevcDecoder_xIT_IT8x8_Transpose8x8_0_initialize(schedinfo_t *si);
extern void HevcDecoder_xIT_IT8x8_Transpose8x8_0_scheduler(schedinfo_t *si);
extern void HevcDecoder_xIT_IT8x8_IT8x8_1d_1_initialize(schedinfo_t *si);
extern void HevcDecoder_xIT_IT8x8_IT8x8_1d_1_scheduler(schedinfo_t *si);
extern void HevcDecoder_xIT_IT8x8_Transpose8x8_1_initialize(schedinfo_t *si);
extern void HevcDecoder_xIT_IT8x8_Transpose8x8_1_scheduler(schedinfo_t *si);
extern void HevcDecoder_xIT_IT16x16_IT16x16_1d_0_initialize(schedinfo_t *si);
extern void HevcDecoder_xIT_IT16x16_IT16x16_1d_0_scheduler(schedinfo_t *si);
extern void HevcDecoder_xIT_IT16x16_Transpose16x16_0_initialize(schedinfo_t *si);
extern void HevcDecoder_xIT_IT16x16_Transpose16x16_0_scheduler(schedinfo_t *si);
extern void HevcDecoder_xIT_IT16x16_IT16x16_1d_1_initialize(schedinfo_t *si);
extern void HevcDecoder_xIT_IT16x16_IT16x16_1d_1_scheduler(schedinfo_t *si);
extern void HevcDecoder_xIT_IT16x16_Transpose16x16_1_initialize(schedinfo_t *si);
extern void HevcDecoder_xIT_IT16x16_Transpose16x16_1_scheduler(schedinfo_t *si);
extern void HevcDecoder_xIT_IT32x32_IT32x32_1d_0_initialize(schedinfo_t *si);
extern void HevcDecoder_xIT_IT32x32_IT32x32_1d_0_scheduler(schedinfo_t *si);
extern void HevcDecoder_xIT_IT32x32_Transpose32x32_0_initialize(schedinfo_t *si);
extern void HevcDecoder_xIT_IT32x32_Transpose32x32_0_scheduler(schedinfo_t *si);
extern void HevcDecoder_xIT_IT32x32_IT32x32_1d_1_initialize(schedinfo_t *si);
extern void HevcDecoder_xIT_IT32x32_IT32x32_1d_1_scheduler(schedinfo_t *si);
extern void HevcDecoder_xIT_IT32x32_Transpose32x32_1_initialize(schedinfo_t *si);
extern void HevcDecoder_xIT_IT32x32_Transpose32x32_1_scheduler(schedinfo_t *si);
extern void HevcDecoder_generateInfo_GenerateRefList_initialize(schedinfo_t *si);
extern void HevcDecoder_generateInfo_GenerateRefList_scheduler(schedinfo_t *si);
extern void HevcDecoder_generateInfo_MvComponentPred_initialize(schedinfo_t *si);
extern void HevcDecoder_generateInfo_MvComponentPred_scheduler(schedinfo_t *si);
extern void HevcDecoder_DBFilter_DeblockFilt_initialize(schedinfo_t *si);
extern void HevcDecoder_DBFilter_DeblockFilt_scheduler(schedinfo_t *si);
extern void HevcDecoder_DBFilter_GenerateBs_initialize(schedinfo_t *si);
extern void HevcDecoder_DBFilter_GenerateBs_scheduler(schedinfo_t *si);
extern void check_MD5_padding_initialize(schedinfo_t *si);
extern void check_MD5_padding_scheduler(schedinfo_t *si);
extern void check_MD5_shifter_initialize(schedinfo_t *si);
extern void check_MD5_shifter_scheduler(schedinfo_t *si);
extern void check_MD5_compute_initialize(schedinfo_t *si);
extern void check_MD5_compute_scheduler(schedinfo_t *si);
extern void check_MD5_MD5SplitInfo_initialize(schedinfo_t *si);
extern void check_MD5_MD5SplitInfo_scheduler(schedinfo_t *si);

/////////////////////////////////////////////////
// Declaration of the actors array
actor_t Source = {"Source", Source_initialize, Source_scheduler, 0, 0, 0, 0, NULL, -1, 0, 0, 1, 0, 0, 0, NULL, 0, 0, "", 0, 0, 0};
actor_t display = {"display", display_initialize, display_scheduler, 0, 0, 0, 0, NULL, -1, 1, 0, 1, 0, 0, 0, NULL, 0, 0, "", 0, 0, 0};
actor_t HevcDecoder_Algo_Parser = {"HevcDecoder_Algo_Parser", HevcDecoder_Algo_Parser_initialize, HevcDecoder_Algo_Parser_scheduler, 0, 0, 0, 0, NULL, -1, 2, 0, 1, 0, 0, 0, NULL, 0, 0, "", 0, 0, 0};
actor_t HevcDecoder_IntraPrediction = {"HevcDecoder_IntraPrediction", HevcDecoder_IntraPrediction_initialize, HevcDecoder_IntraPrediction_scheduler, 0, 0, 0, 0, NULL, -1, 3, 0, 1, 0, 0, 0, NULL, 0, 0, "", 0, 0, 0};
actor_t HevcDecoder_SelectCU = {"HevcDecoder_SelectCU", HevcDecoder_SelectCU_initialize, HevcDecoder_SelectCU_scheduler, 0, 0, 0, 0, NULL, -1, 4, 0, 1, 0, 0, 0, NULL, 0, 0, "", 0, 0, 0};
actor_t HevcDecoder_DecodingPictureBuffer = {"HevcDecoder_DecodingPictureBuffer", HevcDecoder_DecodingPictureBuffer_initialize, HevcDecoder_DecodingPictureBuffer_scheduler, 0, 0, 0, 0, NULL, -1, 5, 0, 1, 0, 0, 0, NULL, 0, 0, "", 0, 0, 0};
actor_t HevcDecoder_InterPrediction = {"HevcDecoder_InterPrediction", HevcDecoder_InterPrediction_initialize, HevcDecoder_InterPrediction_scheduler, 0, 0, 0, 0, NULL, -1, 6, 0, 1, 0, 0, 0, NULL, 0, 0, "", 0, 0, 0};
actor_t HevcDecoder_SAO = {"HevcDecoder_SAO", HevcDecoder_SAO_initialize, HevcDecoder_SAO_scheduler, 0, 0, 0, 0, NULL, -1, 7, 0, 1, 0, 0, 0, NULL, 0, 0, "", 0, 0, 0};
actor_t HevcDecoder_xIT_IT_Splitter = {"HevcDecoder_xIT_IT_Splitter", HevcDecoder_xIT_IT_Splitter_initialize, HevcDecoder_xIT_IT_Splitter_scheduler, 0, 0, 0, 0, NULL, -1, 8, 0, 1, 0, 0, 0, NULL, 0, 0, "", 0, 0, 0};
actor_t HevcDecoder_xIT_IT_Merger = {"HevcDecoder_xIT_IT_Merger", HevcDecoder_xIT_IT_Merger_initialize, HevcDecoder_xIT_IT_Merger_scheduler, 0, 0, 0, 0, NULL, -1, 9, 0, 1, 0, 0, 0, NULL, 0, 0, "", 0, 0, 0};
actor_t HevcDecoder_xIT_invDST4x4_1st = {"HevcDecoder_xIT_invDST4x4_1st", HevcDecoder_xIT_invDST4x4_1st_initialize, HevcDecoder_xIT_invDST4x4_1st_scheduler, 0, 0, 0, 0, NULL, -1, 10, 0, 1, 0, 0, 0, NULL, 0, 0, "", 0, 0, 0};
actor_t HevcDecoder_xIT_invDST4x4_2nd = {"HevcDecoder_xIT_invDST4x4_2nd", HevcDecoder_xIT_invDST4x4_2nd_initialize, HevcDecoder_xIT_invDST4x4_2nd_scheduler, 0, 0, 0, 0, NULL, -1, 11, 0, 1, 0, 0, 0, NULL, 0, 0, "", 0, 0, 0};
actor_t HevcDecoder_xIT_Block_Merger = {"HevcDecoder_xIT_Block_Merger", HevcDecoder_xIT_Block_Merger_initialize, HevcDecoder_xIT_Block_Merger_scheduler, 0, 0, 0, 0, NULL, -1, 12, 0, 1, 0, 0, 0, NULL, 0, 0, "", 0, 0, 0};
actor_t HevcDecoder_xIT_IT4x4_IT4x4_1d_0 = {"HevcDecoder_xIT_IT4x4_IT4x4_1d_0", HevcDecoder_xIT_IT4x4_IT4x4_1d_0_initialize, HevcDecoder_xIT_IT4x4_IT4x4_1d_0_scheduler, 0, 0, 0, 0, NULL, -1, 13, 0, 1, 0, 0, 0, NULL, 0, 0, "", 0, 0, 0};
actor_t HevcDecoder_xIT_IT4x4_Transpose4x4_0 = {"HevcDecoder_xIT_IT4x4_Transpose4x4_0", HevcDecoder_xIT_IT4x4_Transpose4x4_0_initialize, HevcDecoder_xIT_IT4x4_Transpose4x4_0_scheduler, 0, 0, 0, 0, NULL, -1, 14, 0, 1, 0, 0, 0, NULL, 0, 0, "", 0, 0, 0};
actor_t HevcDecoder_xIT_IT4x4_IT4x4_1d_1 = {"HevcDecoder_xIT_IT4x4_IT4x4_1d_1", HevcDecoder_xIT_IT4x4_IT4x4_1d_1_initialize, HevcDecoder_xIT_IT4x4_IT4x4_1d_1_scheduler, 0, 0, 0, 0, NULL, -1, 15, 0, 1, 0, 0, 0, NULL, 0, 0, "", 0, 0, 0};
actor_t HevcDecoder_xIT_IT4x4_Transpose4x4_1 = {"HevcDecoder_xIT_IT4x4_Transpose4x4_1", HevcDecoder_xIT_IT4x4_Transpose4x4_1_initialize, HevcDecoder_xIT_IT4x4_Transpose4x4_1_scheduler, 0, 0, 0, 0, NULL, -1, 16, 0, 1, 0, 0, 0, NULL, 0, 0, "", 0, 0, 0};
actor_t HevcDecoder_xIT_IT8x8_IT8x8_1d_0 = {"HevcDecoder_xIT_IT8x8_IT8x8_1d_0", HevcDecoder_xIT_IT8x8_IT8x8_1d_0_initialize, HevcDecoder_xIT_IT8x8_IT8x8_1d_0_scheduler, 0, 0, 0, 0, NULL, -1, 17, 0, 1, 0, 0, 0, NULL, 0, 0, "", 0, 0, 0};
actor_t HevcDecoder_xIT_IT8x8_Transpose8x8_0 = {"HevcDecoder_xIT_IT8x8_Transpose8x8_0", HevcDecoder_xIT_IT8x8_Transpose8x8_0_initialize, HevcDecoder_xIT_IT8x8_Transpose8x8_0_scheduler, 0, 0, 0, 0, NULL, -1, 18, 0, 1, 0, 0, 0, NULL, 0, 0, "", 0, 0, 0};
actor_t HevcDecoder_xIT_IT8x8_IT8x8_1d_1 = {"HevcDecoder_xIT_IT8x8_IT8x8_1d_1", HevcDecoder_xIT_IT8x8_IT8x8_1d_1_initialize, HevcDecoder_xIT_IT8x8_IT8x8_1d_1_scheduler, 0, 0, 0, 0, NULL, -1, 19, 0, 1, 0, 0, 0, NULL, 0, 0, "", 0, 0, 0};
actor_t HevcDecoder_xIT_IT8x8_Transpose8x8_1 = {"HevcDecoder_xIT_IT8x8_Transpose8x8_1", HevcDecoder_xIT_IT8x8_Transpose8x8_1_initialize, HevcDecoder_xIT_IT8x8_Transpose8x8_1_scheduler, 0, 0, 0, 0, NULL, -1, 20, 0, 1, 0, 0, 0, NULL, 0, 0, "", 0, 0, 0};
actor_t HevcDecoder_xIT_IT16x16_IT16x16_1d_0 = {"HevcDecoder_xIT_IT16x16_IT16x16_1d_0", HevcDecoder_xIT_IT16x16_IT16x16_1d_0_initialize, HevcDecoder_xIT_IT16x16_IT16x16_1d_0_scheduler, 0, 0, 0, 0, NULL, -1, 21, 0, 1, 0, 0, 0, NULL, 0, 0, "", 0, 0, 0};
actor_t HevcDecoder_xIT_IT16x16_Transpose16x16_0 = {"HevcDecoder_xIT_IT16x16_Transpose16x16_0", HevcDecoder_xIT_IT16x16_Transpose16x16_0_initialize, HevcDecoder_xIT_IT16x16_Transpose16x16_0_scheduler, 0, 0, 0, 0, NULL, -1, 22, 0, 1, 0, 0, 0, NULL, 0, 0, "", 0, 0, 0};
actor_t HevcDecoder_xIT_IT16x16_IT16x16_1d_1 = {"HevcDecoder_xIT_IT16x16_IT16x16_1d_1", HevcDecoder_xIT_IT16x16_IT16x16_1d_1_initialize, HevcDecoder_xIT_IT16x16_IT16x16_1d_1_scheduler, 0, 0, 0, 0, NULL, -1, 23, 0, 1, 0, 0, 0, NULL, 0, 0, "", 0, 0, 0};
actor_t HevcDecoder_xIT_IT16x16_Transpose16x16_1 = {"HevcDecoder_xIT_IT16x16_Transpose16x16_1", HevcDecoder_xIT_IT16x16_Transpose16x16_1_initialize, HevcDecoder_xIT_IT16x16_Transpose16x16_1_scheduler, 0, 0, 0, 0, NULL, -1, 24, 0, 1, 0, 0, 0, NULL, 0, 0, "", 0, 0, 0};
actor_t HevcDecoder_xIT_IT32x32_IT32x32_1d_0 = {"HevcDecoder_xIT_IT32x32_IT32x32_1d_0", HevcDecoder_xIT_IT32x32_IT32x32_1d_0_initialize, HevcDecoder_xIT_IT32x32_IT32x32_1d_0_scheduler, 0, 0, 0, 0, NULL, -1, 25, 0, 1, 0, 0, 0, NULL, 0, 0, "", 0, 0, 0};
actor_t HevcDecoder_xIT_IT32x32_Transpose32x32_0 = {"HevcDecoder_xIT_IT32x32_Transpose32x32_0", HevcDecoder_xIT_IT32x32_Transpose32x32_0_initialize, HevcDecoder_xIT_IT32x32_Transpose32x32_0_scheduler, 0, 0, 0, 0, NULL, -1, 26, 0, 1, 0, 0, 0, NULL, 0, 0, "", 0, 0, 0};
actor_t HevcDecoder_xIT_IT32x32_IT32x32_1d_1 = {"HevcDecoder_xIT_IT32x32_IT32x32_1d_1", HevcDecoder_xIT_IT32x32_IT32x32_1d_1_initialize, HevcDecoder_xIT_IT32x32_IT32x32_1d_1_scheduler, 0, 0, 0, 0, NULL, -1, 27, 0, 1, 0, 0, 0, NULL, 0, 0, "", 0, 0, 0};
actor_t HevcDecoder_xIT_IT32x32_Transpose32x32_1 = {"HevcDecoder_xIT_IT32x32_Transpose32x32_1", HevcDecoder_xIT_IT32x32_Transpose32x32_1_initialize, HevcDecoder_xIT_IT32x32_Transpose32x32_1_scheduler, 0, 0, 0, 0, NULL, -1, 28, 0, 1, 0, 0, 0, NULL, 0, 0, "", 0, 0, 0};
actor_t HevcDecoder_generateInfo_GenerateRefList = {"HevcDecoder_generateInfo_GenerateRefList", HevcDecoder_generateInfo_GenerateRefList_initialize, HevcDecoder_generateInfo_GenerateRefList_scheduler, 0, 0, 0, 0, NULL, -1, 29, 0, 1, 0, 0, 0, NULL, 0, 0, "", 0, 0, 0};
actor_t HevcDecoder_generateInfo_MvComponentPred = {"HevcDecoder_generateInfo_MvComponentPred", HevcDecoder_generateInfo_MvComponentPred_initialize, HevcDecoder_generateInfo_MvComponentPred_scheduler, 0, 0, 0, 0, NULL, -1, 30, 0, 1, 0, 0, 0, NULL, 0, 0, "", 0, 0, 0};
actor_t HevcDecoder_DBFilter_DeblockFilt = {"HevcDecoder_DBFilter_DeblockFilt", HevcDecoder_DBFilter_DeblockFilt_initialize, HevcDecoder_DBFilter_DeblockFilt_scheduler, 0, 0, 0, 0, NULL, -1, 31, 0, 1, 0, 0, 0, NULL, 0, 0, "", 0, 0, 0};
actor_t HevcDecoder_DBFilter_GenerateBs = {"HevcDecoder_DBFilter_GenerateBs", HevcDecoder_DBFilter_GenerateBs_initialize, HevcDecoder_DBFilter_GenerateBs_scheduler, 0, 0, 0, 0, NULL, -1, 32, 0, 1, 0, 0, 0, NULL, 0, 0, "", 0, 0, 0};
actor_t check_MD5_padding = {"check_MD5_padding", check_MD5_padding_initialize, check_MD5_padding_scheduler, 0, 0, 0, 0, NULL, -1, 33, 0, 1, 0, 0, 0, NULL, 0, 0, "", 0, 0, 0};
actor_t check_MD5_shifter = {"check_MD5_shifter", check_MD5_shifter_initialize, check_MD5_shifter_scheduler, 0, 0, 0, 0, NULL, -1, 34, 0, 1, 0, 0, 0, NULL, 0, 0, "", 0, 0, 0};
actor_t check_MD5_compute = {"check_MD5_compute", check_MD5_compute_initialize, check_MD5_compute_scheduler, 0, 0, 0, 0, NULL, -1, 35, 0, 1, 0, 0, 0, NULL, 0, 0, "", 0, 0, 0};
actor_t check_MD5_MD5SplitInfo = {"check_MD5_MD5SplitInfo", check_MD5_MD5SplitInfo_initialize, check_MD5_MD5SplitInfo_scheduler, 0, 0, 0, 0, NULL, -1, 36, 0, 1, 0, 0, 0, NULL, 0, 0, "", 0, 0, 0};

actor_t *actors[] = {
	&Source,
	&display,
	&HevcDecoder_Algo_Parser,
	&HevcDecoder_IntraPrediction,
	&HevcDecoder_SelectCU,
	&HevcDecoder_DecodingPictureBuffer,
	&HevcDecoder_InterPrediction,
	&HevcDecoder_SAO,
	&HevcDecoder_xIT_IT_Splitter,
	&HevcDecoder_xIT_IT_Merger,
	&HevcDecoder_xIT_invDST4x4_1st,
	&HevcDecoder_xIT_invDST4x4_2nd,
	&HevcDecoder_xIT_Block_Merger,
	&HevcDecoder_xIT_IT4x4_IT4x4_1d_0,
	&HevcDecoder_xIT_IT4x4_Transpose4x4_0,
	&HevcDecoder_xIT_IT4x4_IT4x4_1d_1,
	&HevcDecoder_xIT_IT4x4_Transpose4x4_1,
	&HevcDecoder_xIT_IT8x8_IT8x8_1d_0,
	&HevcDecoder_xIT_IT8x8_Transpose8x8_0,
	&HevcDecoder_xIT_IT8x8_IT8x8_1d_1,
	&HevcDecoder_xIT_IT8x8_Transpose8x8_1,
	&HevcDecoder_xIT_IT16x16_IT16x16_1d_0,
	&HevcDecoder_xIT_IT16x16_Transpose16x16_0,
	&HevcDecoder_xIT_IT16x16_IT16x16_1d_1,
	&HevcDecoder_xIT_IT16x16_Transpose16x16_1,
	&HevcDecoder_xIT_IT32x32_IT32x32_1d_0,
	&HevcDecoder_xIT_IT32x32_Transpose32x32_0,
	&HevcDecoder_xIT_IT32x32_IT32x32_1d_1,
	&HevcDecoder_xIT_IT32x32_Transpose32x32_1,
	&HevcDecoder_generateInfo_GenerateRefList,
	&HevcDecoder_generateInfo_MvComponentPred,
	&HevcDecoder_DBFilter_DeblockFilt,
	&HevcDecoder_DBFilter_GenerateBs,
	&check_MD5_padding,
	&check_MD5_shifter,
	&check_MD5_compute,
	&check_MD5_MD5SplitInfo
};

/////////////////////////////////////////////////
// Declaration of the connections array
connection_t connection_HevcDecoder_IntraPrediction_IntraPredMode = {&HevcDecoder_Algo_Parser, &HevcDecoder_IntraPrediction, 0, 0};
connection_t connection_HevcDecoder_IntraPrediction_PictSize = {&HevcDecoder_Algo_Parser, &HevcDecoder_IntraPrediction, 0, 0};
connection_t connection_HevcDecoder_IntraPrediction_PartMode = {&HevcDecoder_Algo_Parser, &HevcDecoder_IntraPrediction, 0, 0};
connection_t connection_HevcDecoder_IntraPrediction_SplitTransform = {&HevcDecoder_Algo_Parser, &HevcDecoder_IntraPrediction, 0, 0};
connection_t connection_HevcDecoder_IntraPrediction_SliceAddr = {&HevcDecoder_Algo_Parser, &HevcDecoder_IntraPrediction, 0, 0};
connection_t connection_HevcDecoder_SelectCU_IntraSample = {&HevcDecoder_IntraPrediction, &HevcDecoder_SelectCU, 0, 0};
connection_t connection_HevcDecoder_SelectCU_PartMode = {&HevcDecoder_Algo_Parser, &HevcDecoder_SelectCU, 0, 0};
connection_t connection_HevcDecoder_IntraPrediction_StrongIntraSmoothing = {&HevcDecoder_Algo_Parser, &HevcDecoder_IntraPrediction, 0, 0};
connection_t connection_HevcDecoder_DecodingPictureBuffer_Poc = {&HevcDecoder_Algo_Parser, &HevcDecoder_DecodingPictureBuffer, 0, 0};
connection_t connection_HevcDecoder_DecodingPictureBuffer_PicSize = {&HevcDecoder_Algo_Parser, &HevcDecoder_DecodingPictureBuffer, 0, 0};
connection_t connection_HevcDecoder_DecodingPictureBuffer_RpsPoc = {&HevcDecoder_Algo_Parser, &HevcDecoder_DecodingPictureBuffer, 0, 0};
connection_t connection_HevcDecoder_InterPrediction_PartMode = {&HevcDecoder_Algo_Parser, &HevcDecoder_InterPrediction, 0, 0};
connection_t connection_HevcDecoder_InterPrediction_Poc = {&HevcDecoder_Algo_Parser, &HevcDecoder_InterPrediction, 0, 0};
connection_t connection_HevcDecoder_InterPrediction_Sample = {&HevcDecoder_DecodingPictureBuffer, &HevcDecoder_InterPrediction, 0, 0};
connection_t connection_HevcDecoder_InterPrediction_SliceType = {&HevcDecoder_Algo_Parser, &HevcDecoder_InterPrediction, 0, 0};
connection_t connection_HevcDecoder_SelectCU_InterSample = {&HevcDecoder_InterPrediction, &HevcDecoder_SelectCU, 0, 0};
connection_t connection_HevcDecoder_IntraPrediction_Sample = {&HevcDecoder_SelectCU, &HevcDecoder_IntraPrediction, 0, 0};
connection_t connection_HevcDecoder_InterPrediction_WeightedPredSe = {&HevcDecoder_Algo_Parser, &HevcDecoder_InterPrediction, 0, 0};
connection_t connection_HevcDecoder_IntraPrediction_LcuSizeMax = {&HevcDecoder_Algo_Parser, &HevcDecoder_IntraPrediction, 0, 0};
connection_t connection_HevcDecoder_IntraPrediction_TilesCoord = {&HevcDecoder_Algo_Parser, &HevcDecoder_IntraPrediction, 0, 0};
connection_t connection_HevcDecoder_SAO_TilesCoord = {&HevcDecoder_Algo_Parser, &HevcDecoder_SAO, 0, 0};
connection_t connection_HevcDecoder_SAO_LcuSizeMax = {&HevcDecoder_Algo_Parser, &HevcDecoder_SAO, 0, 0};
connection_t connection_HevcDecoder_SAO_LFAcrossSlcTile = {&HevcDecoder_Algo_Parser, &HevcDecoder_SAO, 0, 0};
connection_t connection_HevcDecoder_SAO_PicSize = {&HevcDecoder_Algo_Parser, &HevcDecoder_SAO, 0, 0};
connection_t connection_HevcDecoder_SAO_IsPicSlcLcu = {&HevcDecoder_Algo_Parser, &HevcDecoder_SAO, 0, 0};
connection_t connection_HevcDecoder_SAO_SaoSe = {&HevcDecoder_Algo_Parser, &HevcDecoder_SAO, 0, 0};
connection_t connection_HevcDecoder_DecodingPictureBuffer_Sample = {&HevcDecoder_SAO, &HevcDecoder_DecodingPictureBuffer, 0, 0};
connection_t connection_HevcDecoder_IntraPrediction_CUInfo = {&HevcDecoder_Algo_Parser, &HevcDecoder_IntraPrediction, 0, 0};
connection_t connection_HevcDecoder_InterPrediction_CUInfo = {&HevcDecoder_Algo_Parser, &HevcDecoder_InterPrediction, 0, 0};
connection_t connection_HevcDecoder_SelectCU_CUInfo = {&HevcDecoder_Algo_Parser, &HevcDecoder_SelectCU, 0, 0};
connection_t connection_HevcDecoder_DecodingPictureBuffer_IsPicSlc = {&HevcDecoder_Algo_Parser, &HevcDecoder_DecodingPictureBuffer, 0, 0};
connection_t connection_HevcDecoder_DecodingPictureBuffer_ReorderPics = {&HevcDecoder_Algo_Parser, &HevcDecoder_DecodingPictureBuffer, 0, 0};
connection_t connection_HevcDecoder_xIT_invDST4x4_1st_IN = {&HevcDecoder_xIT_IT_Splitter, &HevcDecoder_xIT_invDST4x4_1st, 0, 0};
connection_t connection_HevcDecoder_xIT_invDST4x4_2nd_IN = {&HevcDecoder_xIT_invDST4x4_1st, &HevcDecoder_xIT_invDST4x4_2nd, 0, 0};
connection_t connection_HevcDecoder_xIT_IT_Merger_Block_4x4_DST = {&HevcDecoder_xIT_invDST4x4_2nd, &HevcDecoder_xIT_IT_Merger, 0, 0};
connection_t connection_HevcDecoder_xIT_IT_Merger_Block_skip = {&HevcDecoder_xIT_IT_Splitter, &HevcDecoder_xIT_IT_Merger, 0, 0};
connection_t connection_HevcDecoder_xIT_Block_Merger_Block_in = {&HevcDecoder_xIT_IT_Merger, &HevcDecoder_xIT_Block_Merger, 0, 0};
connection_t connection_HevcDecoder_xIT_IT4x4_Transpose4x4_1_Src = {&HevcDecoder_xIT_IT4x4_IT4x4_1d_0, &HevcDecoder_xIT_IT4x4_Transpose4x4_1, 0, 0};
connection_t connection_HevcDecoder_xIT_IT4x4_IT4x4_1d_1_Src = {&HevcDecoder_xIT_IT4x4_Transpose4x4_1, &HevcDecoder_xIT_IT4x4_IT4x4_1d_1, 0, 0};
connection_t connection_HevcDecoder_xIT_IT4x4_IT4x4_1d_0_Src = {&HevcDecoder_xIT_IT4x4_Transpose4x4_0, &HevcDecoder_xIT_IT4x4_IT4x4_1d_0, 0, 0};
connection_t connection_HevcDecoder_xIT_IT_Merger_Block_4x4_IT = {&HevcDecoder_xIT_IT4x4_IT4x4_1d_1, &HevcDecoder_xIT_IT_Merger, 0, 0};
connection_t connection_HevcDecoder_xIT_IT4x4_Transpose4x4_0_Src = {&HevcDecoder_xIT_IT_Splitter, &HevcDecoder_xIT_IT4x4_Transpose4x4_0, 0, 0};
connection_t connection_HevcDecoder_xIT_IT8x8_Transpose8x8_1_Src = {&HevcDecoder_xIT_IT8x8_IT8x8_1d_0, &HevcDecoder_xIT_IT8x8_Transpose8x8_1, 0, 0};
connection_t connection_HevcDecoder_xIT_IT8x8_IT8x8_1d_1_Src = {&HevcDecoder_xIT_IT8x8_Transpose8x8_1, &HevcDecoder_xIT_IT8x8_IT8x8_1d_1, 0, 0};
connection_t connection_HevcDecoder_xIT_IT8x8_IT8x8_1d_0_Src = {&HevcDecoder_xIT_IT8x8_Transpose8x8_0, &HevcDecoder_xIT_IT8x8_IT8x8_1d_0, 0, 0};
connection_t connection_HevcDecoder_xIT_IT_Merger_Block_8x8 = {&HevcDecoder_xIT_IT8x8_IT8x8_1d_1, &HevcDecoder_xIT_IT_Merger, 0, 0};
connection_t connection_HevcDecoder_xIT_IT8x8_Transpose8x8_0_Src = {&HevcDecoder_xIT_IT_Splitter, &HevcDecoder_xIT_IT8x8_Transpose8x8_0, 0, 0};
connection_t connection_HevcDecoder_xIT_IT16x16_Transpose16x16_1_Src = {&HevcDecoder_xIT_IT16x16_IT16x16_1d_0, &HevcDecoder_xIT_IT16x16_Transpose16x16_1, 0, 0};
connection_t connection_HevcDecoder_xIT_IT16x16_IT16x16_1d_1_Src = {&HevcDecoder_xIT_IT16x16_Transpose16x16_1, &HevcDecoder_xIT_IT16x16_IT16x16_1d_1, 0, 0};
connection_t connection_HevcDecoder_xIT_IT16x16_IT16x16_1d_0_Src = {&HevcDecoder_xIT_IT16x16_Transpose16x16_0, &HevcDecoder_xIT_IT16x16_IT16x16_1d_0, 0, 0};
connection_t connection_HevcDecoder_xIT_IT_Merger_Block_16x16 = {&HevcDecoder_xIT_IT16x16_IT16x16_1d_1, &HevcDecoder_xIT_IT_Merger, 0, 0};
connection_t connection_HevcDecoder_xIT_IT16x16_Transpose16x16_0_Src = {&HevcDecoder_xIT_IT_Splitter, &HevcDecoder_xIT_IT16x16_Transpose16x16_0, 0, 0};
connection_t connection_HevcDecoder_xIT_IT32x32_IT32x32_1d_1_Src = {&HevcDecoder_xIT_IT32x32_Transpose32x32_1, &HevcDecoder_xIT_IT32x32_IT32x32_1d_1, 0, 0};
connection_t connection_HevcDecoder_xIT_IT32x32_Transpose32x32_1_Src = {&HevcDecoder_xIT_IT32x32_IT32x32_1d_0, &HevcDecoder_xIT_IT32x32_Transpose32x32_1, 0, 0};
connection_t connection_HevcDecoder_xIT_IT32x32_IT32x32_1d_0_Src = {&HevcDecoder_xIT_IT32x32_Transpose32x32_0, &HevcDecoder_xIT_IT32x32_IT32x32_1d_0, 0, 0};
connection_t connection_HevcDecoder_xIT_IT_Merger_Block_32x32 = {&HevcDecoder_xIT_IT32x32_IT32x32_1d_1, &HevcDecoder_xIT_IT_Merger, 0, 0};
connection_t connection_HevcDecoder_xIT_IT32x32_Transpose32x32_0_Src = {&HevcDecoder_xIT_IT_Splitter, &HevcDecoder_xIT_IT32x32_Transpose32x32_0, 0, 0};
connection_t connection_HevcDecoder_SelectCU_ResidualSample = {&HevcDecoder_xIT_Block_Merger, &HevcDecoder_SelectCU, 0, 0};
connection_t connection_HevcDecoder_xIT_IT_Splitter_Size = {&HevcDecoder_Algo_Parser, &HevcDecoder_xIT_IT_Splitter, 0, 0};
connection_t connection_HevcDecoder_xIT_IT_Merger_Size = {&HevcDecoder_Algo_Parser, &HevcDecoder_xIT_IT_Merger, 0, 0};
connection_t connection_HevcDecoder_xIT_Block_Merger_Size = {&HevcDecoder_Algo_Parser, &HevcDecoder_xIT_Block_Merger, 0, 0};
connection_t connection_HevcDecoder_xIT_IT_Splitter_Coeff = {&HevcDecoder_Algo_Parser, &HevcDecoder_xIT_IT_Splitter, 0, 0};
connection_t connection_HevcDecoder_generateInfo_MvComponentPred_RefList = {&HevcDecoder_generateInfo_GenerateRefList, &HevcDecoder_generateInfo_MvComponentPred, 0, 0};
connection_t connection_HevcDecoder_InterPrediction_RefIdx = {&HevcDecoder_generateInfo_MvComponentPred, &HevcDecoder_InterPrediction, 0, 0};
connection_t connection_HevcDecoder_InterPrediction_RefList = {&HevcDecoder_generateInfo_GenerateRefList, &HevcDecoder_InterPrediction, 0, 0};
connection_t connection_HevcDecoder_InterPrediction_IsBiPredOrLx = {&HevcDecoder_generateInfo_MvComponentPred, &HevcDecoder_InterPrediction, 0, 0};
connection_t connection_HevcDecoder_InterPrediction_Mv = {&HevcDecoder_generateInfo_MvComponentPred, &HevcDecoder_InterPrediction, 0, 0};
connection_t connection_HevcDecoder_DecodingPictureBuffer_IsBiPredOrLx = {&HevcDecoder_generateInfo_MvComponentPred, &HevcDecoder_DecodingPictureBuffer, 0, 0};
connection_t connection_HevcDecoder_DecodingPictureBuffer_IsReadOrNewSlc = {&HevcDecoder_generateInfo_MvComponentPred, &HevcDecoder_DecodingPictureBuffer, 0, 0};
connection_t connection_HevcDecoder_DecodingPictureBuffer_Mv = {&HevcDecoder_generateInfo_MvComponentPred, &HevcDecoder_DecodingPictureBuffer, 0, 0};
connection_t connection_HevcDecoder_DecodingPictureBuffer_PredCuSize = {&HevcDecoder_generateInfo_MvComponentPred, &HevcDecoder_DecodingPictureBuffer, 0, 0};
connection_t connection_HevcDecoder_DecodingPictureBuffer_PocRef = {&HevcDecoder_generateInfo_MvComponentPred, &HevcDecoder_DecodingPictureBuffer, 0, 0};
connection_t connection_HevcDecoder_generateInfo_MvComponentPred_PartMode = {&HevcDecoder_Algo_Parser, &HevcDecoder_generateInfo_MvComponentPred, 0, 0};
connection_t connection_HevcDecoder_generateInfo_MvComponentPred_PicSize = {&HevcDecoder_Algo_Parser, &HevcDecoder_generateInfo_MvComponentPred, 0, 0};
connection_t connection_HevcDecoder_generateInfo_GenerateRefList_RefPoc = {&HevcDecoder_Algo_Parser, &HevcDecoder_generateInfo_GenerateRefList, 0, 0};
connection_t connection_HevcDecoder_generateInfo_MvComponentPred_RpsPoc = {&HevcDecoder_Algo_Parser, &HevcDecoder_generateInfo_MvComponentPred, 0, 0};
connection_t connection_HevcDecoder_generateInfo_MvComponentPred_SliceType = {&HevcDecoder_Algo_Parser, &HevcDecoder_generateInfo_MvComponentPred, 0, 0};
connection_t connection_HevcDecoder_generateInfo_MvComponentPred_SliceAddr = {&HevcDecoder_Algo_Parser, &HevcDecoder_generateInfo_MvComponentPred, 0, 0};
connection_t connection_HevcDecoder_generateInfo_MvComponentPred_Poc = {&HevcDecoder_Algo_Parser, &HevcDecoder_generateInfo_MvComponentPred, 0, 0};
connection_t connection_HevcDecoder_generateInfo_MvComponentPred_SyntaxElem = {&HevcDecoder_Algo_Parser, &HevcDecoder_generateInfo_MvComponentPred, 0, 0};
connection_t connection_HevcDecoder_generateInfo_GenerateRefList_NumRefIdxLXAct = {&HevcDecoder_Algo_Parser, &HevcDecoder_generateInfo_GenerateRefList, 0, 0};
connection_t connection_HevcDecoder_generateInfo_GenerateRefList_RefPicListModif = {&HevcDecoder_Algo_Parser, &HevcDecoder_generateInfo_GenerateRefList, 0, 0};
connection_t connection_HevcDecoder_generateInfo_MvComponentPred_LcuSizeMax = {&HevcDecoder_Algo_Parser, &HevcDecoder_generateInfo_MvComponentPred, 0, 0};
connection_t connection_HevcDecoder_generateInfo_MvComponentPred_TilesCoord = {&HevcDecoder_Algo_Parser, &HevcDecoder_generateInfo_MvComponentPred, 0, 0};
connection_t connection_HevcDecoder_generateInfo_MvComponentPred_CUInfo = {&HevcDecoder_Algo_Parser, &HevcDecoder_generateInfo_MvComponentPred, 0, 0};
connection_t connection_HevcDecoder_DBFilter_DeblockFilt_BsHor = {&HevcDecoder_DBFilter_GenerateBs, &HevcDecoder_DBFilter_DeblockFilt, 0, 0};
connection_t connection_HevcDecoder_DBFilter_DeblockFilt_BsVer = {&HevcDecoder_DBFilter_GenerateBs, &HevcDecoder_DBFilter_DeblockFilt, 0, 0};
connection_t connection_HevcDecoder_SAO_SampleIn = {&HevcDecoder_DBFilter_DeblockFilt, &HevcDecoder_SAO, 0, 0};
connection_t connection_HevcDecoder_DBFilter_GenerateBs_Cbf = {&HevcDecoder_Algo_Parser, &HevcDecoder_DBFilter_GenerateBs, 0, 0};
connection_t connection_HevcDecoder_DBFilter_GenerateBs_SplitTransf = {&HevcDecoder_Algo_Parser, &HevcDecoder_DBFilter_GenerateBs, 0, 0};
connection_t connection_HevcDecoder_DBFilter_GenerateBs_PartMode = {&HevcDecoder_Algo_Parser, &HevcDecoder_DBFilter_GenerateBs, 0, 0};
connection_t connection_HevcDecoder_DBFilter_GenerateBs_SliceAddr = {&HevcDecoder_Algo_Parser, &HevcDecoder_DBFilter_GenerateBs, 0, 0};
connection_t connection_HevcDecoder_DBFilter_DeblockFilt_PicSize = {&HevcDecoder_Algo_Parser, &HevcDecoder_DBFilter_DeblockFilt, 0, 0};
connection_t connection_HevcDecoder_DBFilter_DeblockFilt_IsPicSlcLcu = {&HevcDecoder_Algo_Parser, &HevcDecoder_DBFilter_DeblockFilt, 0, 0};
connection_t connection_HevcDecoder_DBFilter_DeblockFilt_DBFDisable = {&HevcDecoder_Algo_Parser, &HevcDecoder_DBFilter_DeblockFilt, 0, 0};
connection_t connection_HevcDecoder_DBFilter_DeblockFilt_SampleIn = {&HevcDecoder_SelectCU, &HevcDecoder_DBFilter_DeblockFilt, 0, 0};
connection_t connection_HevcDecoder_DBFilter_GenerateBs_LFAcrossSlcTile = {&HevcDecoder_Algo_Parser, &HevcDecoder_DBFilter_GenerateBs, 0, 0};
connection_t connection_HevcDecoder_DBFilter_GenerateBs_LcuSizeMax = {&HevcDecoder_Algo_Parser, &HevcDecoder_DBFilter_GenerateBs, 0, 0};
connection_t connection_HevcDecoder_DBFilter_DeblockFilt_LcuSizeMax = {&HevcDecoder_Algo_Parser, &HevcDecoder_DBFilter_DeblockFilt, 0, 0};
connection_t connection_HevcDecoder_DBFilter_GenerateBs_TilesCoord = {&HevcDecoder_Algo_Parser, &HevcDecoder_DBFilter_GenerateBs, 0, 0};
connection_t connection_HevcDecoder_DBFilter_DeblockFilt_TilesCoord = {&HevcDecoder_Algo_Parser, &HevcDecoder_DBFilter_DeblockFilt, 0, 0};
connection_t connection_HevcDecoder_DBFilter_DeblockFilt_SyntaxElem = {&HevcDecoder_Algo_Parser, &HevcDecoder_DBFilter_DeblockFilt, 0, 0};
connection_t connection_HevcDecoder_DBFilter_GenerateBs_CUInfo = {&HevcDecoder_Algo_Parser, &HevcDecoder_DBFilter_GenerateBs, 0, 0};
connection_t connection_HevcDecoder_DBFilter_DeblockFilt_Qp = {&HevcDecoder_Algo_Parser, &HevcDecoder_DBFilter_DeblockFilt, 0, 0};
connection_t connection_HevcDecoder_DBFilter_GenerateBs_Mv = {&HevcDecoder_generateInfo_MvComponentPred, &HevcDecoder_DBFilter_GenerateBs, 0, 0};
connection_t connection_HevcDecoder_DBFilter_GenerateBs_IsBiPredOrLx = {&HevcDecoder_generateInfo_MvComponentPred, &HevcDecoder_DBFilter_GenerateBs, 0, 0};
connection_t connection_HevcDecoder_DBFilter_GenerateBs_RefPoc = {&HevcDecoder_generateInfo_MvComponentPred, &HevcDecoder_DBFilter_GenerateBs, 0, 0};
connection_t connection_display_DispCoord = {&HevcDecoder_Algo_Parser, &display, 0, 0};
connection_t connection_display_PicSizeInMb = {&HevcDecoder_Algo_Parser, &display, 0, 0};
connection_t connection_display_Byte = {&HevcDecoder_SAO, &display, 0, 0};
connection_t connection_HevcDecoder_Algo_Parser_byte = {&Source, &HevcDecoder_Algo_Parser, 0, 0};
connection_t connection_check_MD5_shifter_IN = {&check_MD5_padding, &check_MD5_shifter, 0, 0};
connection_t connection_check_MD5_padding_DATA = {&check_MD5_MD5SplitInfo, &check_MD5_padding, 0, 0};
connection_t connection_check_MD5_padding_LENGTH = {&check_MD5_MD5SplitInfo, &check_MD5_padding, 0, 0};
connection_t connection_check_MD5_compute_IN = {&check_MD5_shifter, &check_MD5_compute, 0, 0};
connection_t connection_check_MD5_compute_NEWLENGTH = {&check_MD5_padding, &check_MD5_compute, 0, 0};
connection_t connection_check_MD5_MD5SplitInfo_Byte = {&HevcDecoder_SAO, &check_MD5_MD5SplitInfo, 0, 0};
connection_t connection_check_MD5_compute_SEI_MD5 = {&HevcDecoder_Algo_Parser, &check_MD5_compute, 0, 0};
connection_t connection_check_MD5_MD5SplitInfo_PictSize = {&HevcDecoder_Algo_Parser, &check_MD5_MD5SplitInfo, 0, 0};

connection_t *connections[] = {
	&connection_HevcDecoder_IntraPrediction_IntraPredMode,
	&connection_HevcDecoder_IntraPrediction_PictSize,
	&connection_HevcDecoder_IntraPrediction_PartMode,
	&connection_HevcDecoder_IntraPrediction_SplitTransform,
	&connection_HevcDecoder_IntraPrediction_SliceAddr,
	&connection_HevcDecoder_SelectCU_IntraSample,
	&connection_HevcDecoder_SelectCU_PartMode,
	&connection_HevcDecoder_IntraPrediction_StrongIntraSmoothing,
	&connection_HevcDecoder_DecodingPictureBuffer_Poc,
	&connection_HevcDecoder_DecodingPictureBuffer_PicSize,
	&connection_HevcDecoder_DecodingPictureBuffer_RpsPoc,
	&connection_HevcDecoder_InterPrediction_PartMode,
	&connection_HevcDecoder_InterPrediction_Poc,
	&connection_HevcDecoder_InterPrediction_Sample,
	&connection_HevcDecoder_InterPrediction_SliceType,
	&connection_HevcDecoder_SelectCU_InterSample,
	&connection_HevcDecoder_IntraPrediction_Sample,
	&connection_HevcDecoder_InterPrediction_WeightedPredSe,
	&connection_HevcDecoder_IntraPrediction_LcuSizeMax,
	&connection_HevcDecoder_IntraPrediction_TilesCoord,
	&connection_HevcDecoder_SAO_TilesCoord,
	&connection_HevcDecoder_SAO_LcuSizeMax,
	&connection_HevcDecoder_SAO_LFAcrossSlcTile,
	&connection_HevcDecoder_SAO_PicSize,
	&connection_HevcDecoder_SAO_IsPicSlcLcu,
	&connection_HevcDecoder_SAO_SaoSe,
	&connection_HevcDecoder_DecodingPictureBuffer_Sample,
	&connection_HevcDecoder_IntraPrediction_CUInfo,
	&connection_HevcDecoder_InterPrediction_CUInfo,
	&connection_HevcDecoder_SelectCU_CUInfo,
	&connection_HevcDecoder_DecodingPictureBuffer_IsPicSlc,
	&connection_HevcDecoder_DecodingPictureBuffer_ReorderPics,
	&connection_HevcDecoder_xIT_invDST4x4_1st_IN,
	&connection_HevcDecoder_xIT_invDST4x4_2nd_IN,
	&connection_HevcDecoder_xIT_IT_Merger_Block_4x4_DST,
	&connection_HevcDecoder_xIT_IT_Merger_Block_skip,
	&connection_HevcDecoder_xIT_Block_Merger_Block_in,
	&connection_HevcDecoder_xIT_IT4x4_Transpose4x4_1_Src,
	&connection_HevcDecoder_xIT_IT4x4_IT4x4_1d_1_Src,
	&connection_HevcDecoder_xIT_IT4x4_IT4x4_1d_0_Src,
	&connection_HevcDecoder_xIT_IT_Merger_Block_4x4_IT,
	&connection_HevcDecoder_xIT_IT4x4_Transpose4x4_0_Src,
	&connection_HevcDecoder_xIT_IT8x8_Transpose8x8_1_Src,
	&connection_HevcDecoder_xIT_IT8x8_IT8x8_1d_1_Src,
	&connection_HevcDecoder_xIT_IT8x8_IT8x8_1d_0_Src,
	&connection_HevcDecoder_xIT_IT_Merger_Block_8x8,
	&connection_HevcDecoder_xIT_IT8x8_Transpose8x8_0_Src,
	&connection_HevcDecoder_xIT_IT16x16_Transpose16x16_1_Src,
	&connection_HevcDecoder_xIT_IT16x16_IT16x16_1d_1_Src,
	&connection_HevcDecoder_xIT_IT16x16_IT16x16_1d_0_Src,
	&connection_HevcDecoder_xIT_IT_Merger_Block_16x16,
	&connection_HevcDecoder_xIT_IT16x16_Transpose16x16_0_Src,
	&connection_HevcDecoder_xIT_IT32x32_IT32x32_1d_1_Src,
	&connection_HevcDecoder_xIT_IT32x32_Transpose32x32_1_Src,
	&connection_HevcDecoder_xIT_IT32x32_IT32x32_1d_0_Src,
	&connection_HevcDecoder_xIT_IT_Merger_Block_32x32,
	&connection_HevcDecoder_xIT_IT32x32_Transpose32x32_0_Src,
	&connection_HevcDecoder_SelectCU_ResidualSample,
	&connection_HevcDecoder_xIT_IT_Splitter_Size,
	&connection_HevcDecoder_xIT_IT_Merger_Size,
	&connection_HevcDecoder_xIT_Block_Merger_Size,
	&connection_HevcDecoder_xIT_IT_Splitter_Coeff,
	&connection_HevcDecoder_generateInfo_MvComponentPred_RefList,
	&connection_HevcDecoder_InterPrediction_RefIdx,
	&connection_HevcDecoder_InterPrediction_RefList,
	&connection_HevcDecoder_InterPrediction_IsBiPredOrLx,
	&connection_HevcDecoder_InterPrediction_Mv,
	&connection_HevcDecoder_DecodingPictureBuffer_IsBiPredOrLx,
	&connection_HevcDecoder_DecodingPictureBuffer_IsReadOrNewSlc,
	&connection_HevcDecoder_DecodingPictureBuffer_Mv,
	&connection_HevcDecoder_DecodingPictureBuffer_PredCuSize,
	&connection_HevcDecoder_DecodingPictureBuffer_PocRef,
	&connection_HevcDecoder_generateInfo_MvComponentPred_PartMode,
	&connection_HevcDecoder_generateInfo_MvComponentPred_PicSize,
	&connection_HevcDecoder_generateInfo_GenerateRefList_RefPoc,
	&connection_HevcDecoder_generateInfo_MvComponentPred_RpsPoc,
	&connection_HevcDecoder_generateInfo_MvComponentPred_SliceType,
	&connection_HevcDecoder_generateInfo_MvComponentPred_SliceAddr,
	&connection_HevcDecoder_generateInfo_MvComponentPred_Poc,
	&connection_HevcDecoder_generateInfo_MvComponentPred_SyntaxElem,
	&connection_HevcDecoder_generateInfo_GenerateRefList_NumRefIdxLXAct,
	&connection_HevcDecoder_generateInfo_GenerateRefList_RefPicListModif,
	&connection_HevcDecoder_generateInfo_MvComponentPred_LcuSizeMax,
	&connection_HevcDecoder_generateInfo_MvComponentPred_TilesCoord,
	&connection_HevcDecoder_generateInfo_MvComponentPred_CUInfo,
	&connection_HevcDecoder_DBFilter_DeblockFilt_BsHor,
	&connection_HevcDecoder_DBFilter_DeblockFilt_BsVer,
	&connection_HevcDecoder_SAO_SampleIn,
	&connection_HevcDecoder_DBFilter_GenerateBs_Cbf,
	&connection_HevcDecoder_DBFilter_GenerateBs_SplitTransf,
	&connection_HevcDecoder_DBFilter_GenerateBs_PartMode,
	&connection_HevcDecoder_DBFilter_GenerateBs_SliceAddr,
	&connection_HevcDecoder_DBFilter_DeblockFilt_PicSize,
	&connection_HevcDecoder_DBFilter_DeblockFilt_IsPicSlcLcu,
	&connection_HevcDecoder_DBFilter_DeblockFilt_DBFDisable,
	&connection_HevcDecoder_DBFilter_DeblockFilt_SampleIn,
	&connection_HevcDecoder_DBFilter_GenerateBs_LFAcrossSlcTile,
	&connection_HevcDecoder_DBFilter_GenerateBs_LcuSizeMax,
	&connection_HevcDecoder_DBFilter_DeblockFilt_LcuSizeMax,
	&connection_HevcDecoder_DBFilter_GenerateBs_TilesCoord,
	&connection_HevcDecoder_DBFilter_DeblockFilt_TilesCoord,
	&connection_HevcDecoder_DBFilter_DeblockFilt_SyntaxElem,
	&connection_HevcDecoder_DBFilter_GenerateBs_CUInfo,
	&connection_HevcDecoder_DBFilter_DeblockFilt_Qp,
	&connection_HevcDecoder_DBFilter_GenerateBs_Mv,
	&connection_HevcDecoder_DBFilter_GenerateBs_IsBiPredOrLx,
	&connection_HevcDecoder_DBFilter_GenerateBs_RefPoc,
	&connection_display_DispCoord,
	&connection_display_PicSizeInMb,
	&connection_display_Byte,
	&connection_HevcDecoder_Algo_Parser_byte,
	&connection_check_MD5_shifter_IN,
	&connection_check_MD5_padding_DATA,
	&connection_check_MD5_padding_LENGTH,
	&connection_check_MD5_compute_IN,
	&connection_check_MD5_compute_NEWLENGTH,
	&connection_check_MD5_MD5SplitInfo_Byte,
	&connection_check_MD5_compute_SEI_MD5,
	&connection_check_MD5_MD5SplitInfo_PictSize
};

/////////////////////////////////////////////////
// Declaration of the network
network_t network = {"org.sc29.wg11.mpegh.part2.Top_mpegh_part2_main", actors, connections, 37, 119};


////////////////////////////////////////////////////////////////////////////////
// Main
int main(int argc, char *argv[]) {
	
	options_t *opt = init_orcc(argc, argv);
	set_scheduling_strategy("RR", opt);
	
	launcher(opt, &network);
	return compareErrors;
}
