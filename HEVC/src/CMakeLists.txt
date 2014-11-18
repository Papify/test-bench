# Generated from Top_mpegh_part2_main

set(filenames
	Top_mpegh_part2_main.c
	Source.c
	display.c
	HevcDecoder_Algo_Parser.c
	HevcDecoder_IntraPrediction.c
	HevcDecoder_SelectCU.c
	HevcDecoder_DecodingPictureBuffer.c
	HevcDecoder_InterPrediction.c
	HevcDecoder_SAO.c
	HevcDecoder_xIT_IT_Splitter.c
	HevcDecoder_xIT_IT_Merger.c
	HevcDecoder_xIT_invDST4x4_1st.c
	HevcDecoder_xIT_invDST4x4_2nd.c
	HevcDecoder_xIT_Block_Merger.c
	HevcDecoder_xIT_IT4x4_IT4x4_1d_0.c
	HevcDecoder_xIT_IT4x4_Transpose4x4_0.c
	HevcDecoder_xIT_IT4x4_IT4x4_1d_1.c
	HevcDecoder_xIT_IT4x4_Transpose4x4_1.c
	HevcDecoder_xIT_IT8x8_IT8x8_1d_0.c
	HevcDecoder_xIT_IT8x8_Transpose8x8_0.c
	HevcDecoder_xIT_IT8x8_IT8x8_1d_1.c
	HevcDecoder_xIT_IT8x8_Transpose8x8_1.c
	HevcDecoder_xIT_IT16x16_IT16x16_1d_0.c
	HevcDecoder_xIT_IT16x16_Transpose16x16_0.c
	HevcDecoder_xIT_IT16x16_IT16x16_1d_1.c
	HevcDecoder_xIT_IT16x16_Transpose16x16_1.c
	HevcDecoder_xIT_IT32x32_IT32x32_1d_0.c
	HevcDecoder_xIT_IT32x32_Transpose32x32_0.c
	HevcDecoder_xIT_IT32x32_IT32x32_1d_1.c
	HevcDecoder_xIT_IT32x32_Transpose32x32_1.c
	HevcDecoder_generateInfo_GenerateRefList.c
	HevcDecoder_generateInfo_MvComponentPred.c
	HevcDecoder_DBFilter_DeblockFilt.c
	HevcDecoder_DBFilter_GenerateBs.c
	check_MD5_padding.c
	check_MD5_shifter.c
	check_MD5_compute.c
	check_MD5_MD5SplitInfo.c
)

include_directories(${extra_includes})
add_definitions(${extra_definitions})
add_executable(Top_mpegh_part2_main ${filenames})

# Build library without any external library required
target_link_libraries(Top_mpegh_part2_main orcc-native orcc-runtime ${extra_libraries})
