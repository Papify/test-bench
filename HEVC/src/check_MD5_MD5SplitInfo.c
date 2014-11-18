// Source file is "L/RVC/src/org/sc29/wg11/mpegh/part2/common/MD5SplitInfo.cal"

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
extern actor_t check_MD5_MD5SplitInfo;

////////////////////////////////////////////////////////////////////////////////
// Input FIFOs
extern fifo_u8_t *check_MD5_MD5SplitInfo_Byte;
extern fifo_u16_t *check_MD5_MD5SplitInfo_PictSize;

////////////////////////////////////////////////////////////////////////////////
// Input Fifo control variables
static unsigned int index_Byte;
static unsigned int numTokens_Byte;
#define SIZE_Byte SIZE
#define tokens_Byte check_MD5_MD5SplitInfo_Byte->contents

extern connection_t connection_check_MD5_MD5SplitInfo_Byte;
#define rate_Byte connection_check_MD5_MD5SplitInfo_Byte.rate

static unsigned int index_PictSize;
static unsigned int numTokens_PictSize;
#define SIZE_PictSize SIZE
#define tokens_PictSize check_MD5_MD5SplitInfo_PictSize->contents

extern connection_t connection_check_MD5_MD5SplitInfo_PictSize;
#define rate_PictSize connection_check_MD5_MD5SplitInfo_PictSize.rate

////////////////////////////////////////////////////////////////////////////////
// Predecessors
extern actor_t HevcDecoder_SAO;
extern actor_t HevcDecoder_Algo_Parser;

////////////////////////////////////////////////////////////////////////////////
// Output FIFOs
extern fifo_u64_t *check_MD5_MD5SplitInfo_Length;
extern fifo_u8_t *check_MD5_MD5SplitInfo_DataOut;

////////////////////////////////////////////////////////////////////////////////
// Output Fifo control variables
static unsigned int index_Length;
static unsigned int numFree_Length;
#define NUM_READERS_Length 1
#define SIZE_Length SIZE
#define tokens_Length check_MD5_MD5SplitInfo_Length->contents

static unsigned int index_DataOut;
static unsigned int numFree_DataOut;
#define NUM_READERS_DataOut 1
#define SIZE_DataOut SIZE
#define tokens_DataOut check_MD5_MD5SplitInfo_DataOut->contents

////////////////////////////////////////////////////////////////////////////////
// Successors
extern actor_t check_MD5_padding;
extern actor_t check_MD5_padding;

////////////////////////////////////////////////////////////////////////////////
// Parameter values of the instance
#define BLK_SIDE 16


////////////////////////////////////////////////////////////////////////////////
// State variables of the actor
static u8 pictureBufferY[8388608];
static u8 pictureBufferU[2097152];
static u8 pictureBufferV[2097152];
static i32 pictureSizeInMb;
static i32 nbBlockGot;
static u8 chromaComponent;
static u16 pictureWidthLuma;
static u16 cropPicWthLuma;
static u16 cropPicHghtLuma;
static u16 xIdxLuma;
static u16 yIdxLuma;
static u16 xIdxChroma;
static u32 yIdxChroma;
static u16 xMin;
static u16 xMax;
static u16 yMin;
static u16 yMax;
static u64 lumaSize;
static u64 chromaSize;
static u64 idx;

////////////////////////////////////////////////////////////////////////////////
// Initial FSM state of the actor
enum states {
	my_state_GetChroma1Block,
	my_state_GetChroma2Block,
	my_state_GetLumaBlock,
	my_state_GetPictureSize,
	my_state_outputLoopU,
	my_state_outputLoopV,
	my_state_outputLoopY
};

static char *stateNames[] = {
	"GetChroma1Block",
	"GetChroma2Block",
	"GetLumaBlock",
	"GetPictureSize",
	"outputLoopU",
	"outputLoopV",
	"outputLoopY"
};

static enum states _FSM_state;



////////////////////////////////////////////////////////////////////////////////
// Token functions
static void read_Byte() {
	index_Byte = check_MD5_MD5SplitInfo_Byte->read_inds[2];
	numTokens_Byte = index_Byte + fifo_u8_get_num_tokens(check_MD5_MD5SplitInfo_Byte, 2);
}

static void read_end_Byte() {
	check_MD5_MD5SplitInfo_Byte->read_inds[2] = index_Byte;
}
static void read_PictSize() {
	index_PictSize = check_MD5_MD5SplitInfo_PictSize->read_inds[1];
	numTokens_PictSize = index_PictSize + fifo_u16_get_num_tokens(check_MD5_MD5SplitInfo_PictSize, 1);
}

static void read_end_PictSize() {
	check_MD5_MD5SplitInfo_PictSize->read_inds[1] = index_PictSize;
}

static void write_Length() {
	index_Length = check_MD5_MD5SplitInfo_Length->write_ind;
	numFree_Length = index_Length + fifo_u64_get_room(check_MD5_MD5SplitInfo_Length, NUM_READERS_Length, SIZE_Length);
}

static void write_end_Length() {
	check_MD5_MD5SplitInfo_Length->write_ind = index_Length;
}
static void write_DataOut() {
	index_DataOut = check_MD5_MD5SplitInfo_DataOut->write_ind;
	numFree_DataOut = index_DataOut + fifo_u8_get_room(check_MD5_MD5SplitInfo_DataOut, NUM_READERS_DataOut, SIZE_DataOut);
}

static void write_end_DataOut() {
	check_MD5_MD5SplitInfo_DataOut->write_ind = index_DataOut;
}

////////////////////////////////////////////////////////////////////////////////
// Functions/procedures
static i32 check_MD5_MD5SplitInfo_max(i32 a, i32 b);
static i32 check_MD5_MD5SplitInfo_min(i32 a, i32 b);

static i32 check_MD5_MD5SplitInfo_max(i32 a, i32 b) {
	i32 tmp_if;

	if (a > b) {
		tmp_if = a;
	} else {
		tmp_if = b;
	}
	return tmp_if;
}
static i32 check_MD5_MD5SplitInfo_min(i32 a, i32 b) {
	i32 tmp_if;

	if (a < b) {
		tmp_if = a;
	} else {
		tmp_if = b;
	}
	return tmp_if;
}

////////////////////////////////////////////////////////////////////////////////
// Actions
static i32 isSchedulable_getPictureSize() {
	i32 result;

	result = 1;
	return result;
}

static void getPictureSize() {

	u16 picWidthInPix;
	u16 picHeightInPix;
	u8 local_BLK_SIDE;
	u16 picWidth;
	u16 picHeight;
	u64 local_lumaSize;
	u16 local_xMax;
	u16 local_xMin;
	u16 local_yMax;
	u16 local_yMin;
	u64 local_chromaSize;

	picWidthInPix = tokens_PictSize[(index_PictSize % SIZE_PictSize) + (0)];
	picHeightInPix = tokens_PictSize[(index_PictSize % SIZE_PictSize) + (1)];
	local_BLK_SIDE = BLK_SIDE;
	local_BLK_SIDE = BLK_SIDE;
	picWidth = (picWidthInPix + local_BLK_SIDE - 1) / local_BLK_SIDE;
	local_BLK_SIDE = BLK_SIDE;
	local_BLK_SIDE = BLK_SIDE;
	picHeight = (picHeightInPix + local_BLK_SIDE - 1) / local_BLK_SIDE;
	lumaSize = picWidthInPix * picHeightInPix;
	local_lumaSize = lumaSize;
	chromaSize = local_lumaSize >> 2;
	local_BLK_SIDE = BLK_SIDE;
	pictureWidthLuma = picWidth * local_BLK_SIDE;
	pictureSizeInMb = picWidth * picHeight;
	xMin = 0;
	xMax = picWidthInPix - 1;
	yMin = 0;
	yMax = picHeightInPix - 1;
	local_xMax = xMax;
	local_xMin = xMin;
	cropPicWthLuma = local_xMax - local_xMin + 1;
	local_yMax = yMax;
	local_yMin = yMin;
	cropPicHghtLuma = local_yMax - local_yMin + 1;
	nbBlockGot = 0;
	xIdxLuma = 0;
	yIdxLuma = 0;
	xIdxChroma = 0;
	yIdxChroma = 0;
	local_lumaSize = lumaSize;
	tokens_Length[(index_Length + (0)) % SIZE_Length] = local_lumaSize;
	local_chromaSize = chromaSize;
	tokens_Length[(index_Length + (1)) % SIZE_Length] = local_chromaSize;
	local_chromaSize = chromaSize;
	tokens_Length[(index_Length + (2)) % SIZE_Length] = local_chromaSize;

	// Update ports indexes
	index_PictSize += 2;
	read_end_PictSize();
	index_Length += 3;
	write_end_Length();

	rate_PictSize += 2;
}
static void getPictureSize_aligned() {

	u16 picWidthInPix;
	u16 picHeightInPix;
	u8 local_BLK_SIDE;
	u16 picWidth;
	u16 picHeight;
	u64 local_lumaSize;
	u16 local_xMax;
	u16 local_xMin;
	u16 local_yMax;
	u16 local_yMin;
	u64 local_chromaSize;

	picWidthInPix = tokens_PictSize[(index_PictSize % SIZE_PictSize) + (0)];
	picHeightInPix = tokens_PictSize[(index_PictSize % SIZE_PictSize) + (1)];
	local_BLK_SIDE = BLK_SIDE;
	local_BLK_SIDE = BLK_SIDE;
	picWidth = (picWidthInPix + local_BLK_SIDE - 1) / local_BLK_SIDE;
	local_BLK_SIDE = BLK_SIDE;
	local_BLK_SIDE = BLK_SIDE;
	picHeight = (picHeightInPix + local_BLK_SIDE - 1) / local_BLK_SIDE;
	lumaSize = picWidthInPix * picHeightInPix;
	local_lumaSize = lumaSize;
	chromaSize = local_lumaSize >> 2;
	local_BLK_SIDE = BLK_SIDE;
	pictureWidthLuma = picWidth * local_BLK_SIDE;
	pictureSizeInMb = picWidth * picHeight;
	xMin = 0;
	xMax = picWidthInPix - 1;
	yMin = 0;
	yMax = picHeightInPix - 1;
	local_xMax = xMax;
	local_xMin = xMin;
	cropPicWthLuma = local_xMax - local_xMin + 1;
	local_yMax = yMax;
	local_yMin = yMin;
	cropPicHghtLuma = local_yMax - local_yMin + 1;
	nbBlockGot = 0;
	xIdxLuma = 0;
	yIdxLuma = 0;
	xIdxChroma = 0;
	yIdxChroma = 0;
	local_lumaSize = lumaSize;
	tokens_Length[(index_Length % SIZE_Length) + (0)] = local_lumaSize;
	local_chromaSize = chromaSize;
	tokens_Length[(index_Length % SIZE_Length) + (1)] = local_chromaSize;
	local_chromaSize = chromaSize;
	tokens_Length[(index_Length % SIZE_Length) + (2)] = local_chromaSize;

	// Update ports indexes
	index_PictSize += 2;
	read_end_PictSize();
	index_Length += 3;
	write_end_Length();

	rate_PictSize += 2;
}
static i32 isSchedulable_getPixValue_launch_Luma_blk16x16() {
	i32 result;
	i32 local_nbBlockGot;
	i32 local_pictureSizeInMb;
	u8 local_BLK_SIDE;

	local_nbBlockGot = nbBlockGot;
	local_pictureSizeInMb = pictureSizeInMb;
	local_BLK_SIDE = BLK_SIDE;
	result = local_nbBlockGot < local_pictureSizeInMb && local_BLK_SIDE == 16;
	return result;
}

static void getPixValue_launch_Luma_blk16x16() {

	u16 local_xIdxLuma;
	u16 local_xMin;
	u16 xIdxMin;
	u8 local_BLK_SIDE;
	u16 local_xMax;
	u16 xIdxMax;
	u16 local_yIdxLuma;
	u16 local_yMin;
	u16 yIdxMin;
	u16 local_yMax;
	u16 yIdxMax;
	i32 local_nbBlockGot;
	i32 y;
	i32 x;
	u16 local_cropPicWthLuma;
	u8 tmp_Byte;

	local_xIdxLuma = xIdxLuma;
	local_xMin = xMin;
	xIdxMin = check_MD5_MD5SplitInfo_max(local_xIdxLuma, local_xMin);
	local_xIdxLuma = xIdxLuma;
	local_BLK_SIDE = BLK_SIDE;
	local_xMax = xMax;
	xIdxMax = check_MD5_MD5SplitInfo_min(local_xIdxLuma + local_BLK_SIDE - 1, local_xMax);
	local_yIdxLuma = yIdxLuma;
	local_yMin = yMin;
	yIdxMin = check_MD5_MD5SplitInfo_max(local_yIdxLuma, local_yMin);
	local_yIdxLuma = yIdxLuma;
	local_BLK_SIDE = BLK_SIDE;
	local_yMax = yMax;
	yIdxMax = check_MD5_MD5SplitInfo_min(local_yIdxLuma + local_BLK_SIDE - 1, local_yMax);
	local_nbBlockGot = nbBlockGot;
	nbBlockGot = local_nbBlockGot + 1;
	y = yIdxMin;
	while (y <= yIdxMax) {
		x = xIdxMin;
		while (x <= xIdxMax) {
			local_yMin = yMin;
			local_cropPicWthLuma = cropPicWthLuma;
			local_xMin = xMin;
			local_yIdxLuma = yIdxLuma;
			local_BLK_SIDE = BLK_SIDE;
			local_xIdxLuma = xIdxLuma;
			tmp_Byte = tokens_Byte[(index_Byte + ((y - local_yIdxLuma) * local_BLK_SIDE + x - local_xIdxLuma)) % SIZE_Byte];
			pictureBufferY[(y - local_yMin) * local_cropPicWthLuma + x - local_xMin] = tmp_Byte;
			x = x + 1;
		}
		y = y + 1;
	}
	local_xIdxLuma = xIdxLuma;
	local_BLK_SIDE = BLK_SIDE;
	xIdxLuma = local_xIdxLuma + local_BLK_SIDE;
	chromaComponent = 0;

	// Update ports indexes
	index_Byte += 256;
	read_end_Byte();

	rate_Byte += 256;
}
static void getPixValue_launch_Luma_blk16x16_aligned() {

	u16 local_xIdxLuma;
	u16 local_xMin;
	u16 xIdxMin;
	u8 local_BLK_SIDE;
	u16 local_xMax;
	u16 xIdxMax;
	u16 local_yIdxLuma;
	u16 local_yMin;
	u16 yIdxMin;
	u16 local_yMax;
	u16 yIdxMax;
	i32 local_nbBlockGot;
	i32 y;
	i32 x;
	u16 local_cropPicWthLuma;
	u8 tmp_Byte;

	local_xIdxLuma = xIdxLuma;
	local_xMin = xMin;
	xIdxMin = check_MD5_MD5SplitInfo_max(local_xIdxLuma, local_xMin);
	local_xIdxLuma = xIdxLuma;
	local_BLK_SIDE = BLK_SIDE;
	local_xMax = xMax;
	xIdxMax = check_MD5_MD5SplitInfo_min(local_xIdxLuma + local_BLK_SIDE - 1, local_xMax);
	local_yIdxLuma = yIdxLuma;
	local_yMin = yMin;
	yIdxMin = check_MD5_MD5SplitInfo_max(local_yIdxLuma, local_yMin);
	local_yIdxLuma = yIdxLuma;
	local_BLK_SIDE = BLK_SIDE;
	local_yMax = yMax;
	yIdxMax = check_MD5_MD5SplitInfo_min(local_yIdxLuma + local_BLK_SIDE - 1, local_yMax);
	local_nbBlockGot = nbBlockGot;
	nbBlockGot = local_nbBlockGot + 1;
	y = yIdxMin;
	while (y <= yIdxMax) {
		x = xIdxMin;
		while (x <= xIdxMax) {
			local_yMin = yMin;
			local_cropPicWthLuma = cropPicWthLuma;
			local_xMin = xMin;
			local_yIdxLuma = yIdxLuma;
			local_BLK_SIDE = BLK_SIDE;
			local_xIdxLuma = xIdxLuma;
			tmp_Byte = tokens_Byte[(index_Byte % SIZE_Byte) + ((y - local_yIdxLuma) * local_BLK_SIDE + x - local_xIdxLuma)];
			pictureBufferY[(y - local_yMin) * local_cropPicWthLuma + x - local_xMin] = tmp_Byte;
			x = x + 1;
		}
		y = y + 1;
	}
	local_xIdxLuma = xIdxLuma;
	local_BLK_SIDE = BLK_SIDE;
	xIdxLuma = local_xIdxLuma + local_BLK_SIDE;
	chromaComponent = 0;

	// Update ports indexes
	index_Byte += 256;
	read_end_Byte();

	rate_Byte += 256;
}
static i32 isSchedulable_getPixValue_launch_Luma_blk64x64() {
	i32 result;
	i32 local_nbBlockGot;
	i32 local_pictureSizeInMb;
	u8 local_BLK_SIDE;

	local_nbBlockGot = nbBlockGot;
	local_pictureSizeInMb = pictureSizeInMb;
	local_BLK_SIDE = BLK_SIDE;
	result = local_nbBlockGot < local_pictureSizeInMb && local_BLK_SIDE == 64;
	return result;
}

static void getPixValue_launch_Luma_blk64x64() {

	u16 local_xIdxLuma;
	u16 local_xMin;
	u16 xIdxMin;
	u8 local_BLK_SIDE;
	u16 local_xMax;
	u16 xIdxMax;
	u16 local_yIdxLuma;
	u16 local_yMin;
	u16 yIdxMin;
	u16 local_yMax;
	u16 yIdxMax;
	i32 local_nbBlockGot;
	i32 y;
	i32 x;
	u16 local_cropPicWthLuma;
	u8 tmp_Byte;

	local_xIdxLuma = xIdxLuma;
	local_xMin = xMin;
	xIdxMin = check_MD5_MD5SplitInfo_max(local_xIdxLuma, local_xMin);
	local_xIdxLuma = xIdxLuma;
	local_BLK_SIDE = BLK_SIDE;
	local_xMax = xMax;
	xIdxMax = check_MD5_MD5SplitInfo_min(local_xIdxLuma + local_BLK_SIDE - 1, local_xMax);
	local_yIdxLuma = yIdxLuma;
	local_yMin = yMin;
	yIdxMin = check_MD5_MD5SplitInfo_max(local_yIdxLuma, local_yMin);
	local_yIdxLuma = yIdxLuma;
	local_BLK_SIDE = BLK_SIDE;
	local_yMax = yMax;
	yIdxMax = check_MD5_MD5SplitInfo_min(local_yIdxLuma + local_BLK_SIDE - 1, local_yMax);
	local_nbBlockGot = nbBlockGot;
	nbBlockGot = local_nbBlockGot + 1;
	y = yIdxMin;
	while (y <= yIdxMax) {
		x = xIdxMin;
		while (x <= xIdxMax) {
			local_yMin = yMin;
			local_cropPicWthLuma = cropPicWthLuma;
			local_xMin = xMin;
			local_yIdxLuma = yIdxLuma;
			local_BLK_SIDE = BLK_SIDE;
			local_xIdxLuma = xIdxLuma;
			tmp_Byte = tokens_Byte[(index_Byte + ((y - local_yIdxLuma) * local_BLK_SIDE + x - local_xIdxLuma)) % SIZE_Byte];
			pictureBufferY[(y - local_yMin) * local_cropPicWthLuma + x - local_xMin] = tmp_Byte;
			x = x + 1;
		}
		y = y + 1;
	}
	local_xIdxLuma = xIdxLuma;
	local_BLK_SIDE = BLK_SIDE;
	xIdxLuma = local_xIdxLuma + local_BLK_SIDE;
	chromaComponent = 0;

	// Update ports indexes
	index_Byte += 4096;
	read_end_Byte();

	rate_Byte += 4096;
}
static void getPixValue_launch_Luma_blk64x64_aligned() {

	u16 local_xIdxLuma;
	u16 local_xMin;
	u16 xIdxMin;
	u8 local_BLK_SIDE;
	u16 local_xMax;
	u16 xIdxMax;
	u16 local_yIdxLuma;
	u16 local_yMin;
	u16 yIdxMin;
	u16 local_yMax;
	u16 yIdxMax;
	i32 local_nbBlockGot;
	i32 y;
	i32 x;
	u16 local_cropPicWthLuma;
	u8 tmp_Byte;

	local_xIdxLuma = xIdxLuma;
	local_xMin = xMin;
	xIdxMin = check_MD5_MD5SplitInfo_max(local_xIdxLuma, local_xMin);
	local_xIdxLuma = xIdxLuma;
	local_BLK_SIDE = BLK_SIDE;
	local_xMax = xMax;
	xIdxMax = check_MD5_MD5SplitInfo_min(local_xIdxLuma + local_BLK_SIDE - 1, local_xMax);
	local_yIdxLuma = yIdxLuma;
	local_yMin = yMin;
	yIdxMin = check_MD5_MD5SplitInfo_max(local_yIdxLuma, local_yMin);
	local_yIdxLuma = yIdxLuma;
	local_BLK_SIDE = BLK_SIDE;
	local_yMax = yMax;
	yIdxMax = check_MD5_MD5SplitInfo_min(local_yIdxLuma + local_BLK_SIDE - 1, local_yMax);
	local_nbBlockGot = nbBlockGot;
	nbBlockGot = local_nbBlockGot + 1;
	y = yIdxMin;
	while (y <= yIdxMax) {
		x = xIdxMin;
		while (x <= xIdxMax) {
			local_yMin = yMin;
			local_cropPicWthLuma = cropPicWthLuma;
			local_xMin = xMin;
			local_yIdxLuma = yIdxLuma;
			local_BLK_SIDE = BLK_SIDE;
			local_xIdxLuma = xIdxLuma;
			tmp_Byte = tokens_Byte[(index_Byte % SIZE_Byte) + ((y - local_yIdxLuma) * local_BLK_SIDE + x - local_xIdxLuma)];
			pictureBufferY[(y - local_yMin) * local_cropPicWthLuma + x - local_xMin] = tmp_Byte;
			x = x + 1;
		}
		y = y + 1;
	}
	local_xIdxLuma = xIdxLuma;
	local_BLK_SIDE = BLK_SIDE;
	xIdxLuma = local_xIdxLuma + local_BLK_SIDE;
	chromaComponent = 0;

	// Update ports indexes
	index_Byte += 4096;
	read_end_Byte();

	rate_Byte += 4096;
}
static i32 isSchedulable_getPixValue_launch_Chroma_blk16x16() {
	i32 result;
	u8 local_BLK_SIDE;

	local_BLK_SIDE = BLK_SIDE;
	result = local_BLK_SIDE == 16;
	return result;
}

static void getPixValue_launch_Chroma_blk16x16() {

	u16 local_xIdxChroma;
	u16 local_xMin;
	u16 xIdxMin;
	u8 local_BLK_SIDE;
	u16 local_xMax;
	u16 xIdxMax;
	u32 local_yIdxChroma;
	u16 local_yMin;
	u16 yIdxMin;
	u16 local_yMax;
	u16 yIdxMax;
	u8 local_chromaComponent;
	i32 bCondition;
	i32 y;
	i32 x;
	u16 local_cropPicWthLuma;
	u8 tmp_Byte;
	u8 tmp_Byte0;
	u16 local_xIdxLuma;
	u16 local_pictureWidthLuma;
	u16 local_yIdxLuma;

	local_xIdxChroma = xIdxChroma;
	local_xMin = xMin;
	xIdxMin = check_MD5_MD5SplitInfo_max(local_xIdxChroma, local_xMin / 2);
	local_xIdxChroma = xIdxChroma;
	local_BLK_SIDE = BLK_SIDE;
	local_xMax = xMax;
	xIdxMax = check_MD5_MD5SplitInfo_min(local_xIdxChroma + (local_BLK_SIDE >> 1) - 1, local_xMax / 2);
	local_yIdxChroma = yIdxChroma;
	local_yMin = yMin;
	yIdxMin = check_MD5_MD5SplitInfo_max(local_yIdxChroma, local_yMin / 2);
	local_yIdxChroma = yIdxChroma;
	local_BLK_SIDE = BLK_SIDE;
	local_yMax = yMax;
	yIdxMax = check_MD5_MD5SplitInfo_min(local_yIdxChroma + (local_BLK_SIDE >> 1) - 1, local_yMax / 2);
	local_chromaComponent = chromaComponent;
	bCondition = local_chromaComponent == 0;
	y = yIdxMin;
	while (y <= yIdxMax) {
		x = xIdxMin;
		while (x <= xIdxMax) {
			if (bCondition) {
				local_yMin = yMin;
				local_cropPicWthLuma = cropPicWthLuma;
				local_xMin = xMin;
				local_yIdxChroma = yIdxChroma;
				local_BLK_SIDE = BLK_SIDE;
				local_xIdxChroma = xIdxChroma;
				tmp_Byte = tokens_Byte[(index_Byte + ((y - local_yIdxChroma) * (local_BLK_SIDE >> 1) + x - local_xIdxChroma)) % SIZE_Byte];
				pictureBufferU[(y - local_yMin / 2) * local_cropPicWthLuma / 2 + x - local_xMin / 2] = tmp_Byte;
			} else {
				local_yMin = yMin;
				local_cropPicWthLuma = cropPicWthLuma;
				local_xMin = xMin;
				local_yIdxChroma = yIdxChroma;
				local_BLK_SIDE = BLK_SIDE;
				local_xIdxChroma = xIdxChroma;
				tmp_Byte0 = tokens_Byte[(index_Byte + ((y - local_yIdxChroma) * (local_BLK_SIDE >> 1) + x - local_xIdxChroma)) % SIZE_Byte];
				pictureBufferV[(y - local_yMin / 2) * local_cropPicWthLuma / 2 + x - local_xMin / 2] = tmp_Byte0;
			}
			x = x + 1;
		}
		y = y + 1;
	}
	local_chromaComponent = chromaComponent;
	if (local_chromaComponent != 0) {
		local_xIdxChroma = xIdxChroma;
		local_BLK_SIDE = BLK_SIDE;
		xIdxChroma = local_xIdxChroma + (local_BLK_SIDE >> 1);
		local_xIdxLuma = xIdxLuma;
		local_pictureWidthLuma = pictureWidthLuma;
		if (local_xIdxLuma == local_pictureWidthLuma) {
			xIdxLuma = 0;
			xIdxChroma = 0;
			local_yIdxLuma = yIdxLuma;
			local_BLK_SIDE = BLK_SIDE;
			yIdxLuma = local_yIdxLuma + local_BLK_SIDE;
			local_yIdxChroma = yIdxChroma;
			local_BLK_SIDE = BLK_SIDE;
			yIdxChroma = local_yIdxChroma + (local_BLK_SIDE >> 1);
		}
	}
	chromaComponent = 1;

	// Update ports indexes
	index_Byte += 64;
	read_end_Byte();

	rate_Byte += 64;
}
static void getPixValue_launch_Chroma_blk16x16_aligned() {

	u16 local_xIdxChroma;
	u16 local_xMin;
	u16 xIdxMin;
	u8 local_BLK_SIDE;
	u16 local_xMax;
	u16 xIdxMax;
	u32 local_yIdxChroma;
	u16 local_yMin;
	u16 yIdxMin;
	u16 local_yMax;
	u16 yIdxMax;
	u8 local_chromaComponent;
	i32 bCondition;
	i32 y;
	i32 x;
	u16 local_cropPicWthLuma;
	u8 tmp_Byte;
	u8 tmp_Byte0;
	u16 local_xIdxLuma;
	u16 local_pictureWidthLuma;
	u16 local_yIdxLuma;

	local_xIdxChroma = xIdxChroma;
	local_xMin = xMin;
	xIdxMin = check_MD5_MD5SplitInfo_max(local_xIdxChroma, local_xMin / 2);
	local_xIdxChroma = xIdxChroma;
	local_BLK_SIDE = BLK_SIDE;
	local_xMax = xMax;
	xIdxMax = check_MD5_MD5SplitInfo_min(local_xIdxChroma + (local_BLK_SIDE >> 1) - 1, local_xMax / 2);
	local_yIdxChroma = yIdxChroma;
	local_yMin = yMin;
	yIdxMin = check_MD5_MD5SplitInfo_max(local_yIdxChroma, local_yMin / 2);
	local_yIdxChroma = yIdxChroma;
	local_BLK_SIDE = BLK_SIDE;
	local_yMax = yMax;
	yIdxMax = check_MD5_MD5SplitInfo_min(local_yIdxChroma + (local_BLK_SIDE >> 1) - 1, local_yMax / 2);
	local_chromaComponent = chromaComponent;
	bCondition = local_chromaComponent == 0;
	y = yIdxMin;
	while (y <= yIdxMax) {
		x = xIdxMin;
		while (x <= xIdxMax) {
			if (bCondition) {
				local_yMin = yMin;
				local_cropPicWthLuma = cropPicWthLuma;
				local_xMin = xMin;
				local_yIdxChroma = yIdxChroma;
				local_BLK_SIDE = BLK_SIDE;
				local_xIdxChroma = xIdxChroma;
				tmp_Byte = tokens_Byte[(index_Byte % SIZE_Byte) + ((y - local_yIdxChroma) * (local_BLK_SIDE >> 1) + x - local_xIdxChroma)];
				pictureBufferU[(y - local_yMin / 2) * local_cropPicWthLuma / 2 + x - local_xMin / 2] = tmp_Byte;
			} else {
				local_yMin = yMin;
				local_cropPicWthLuma = cropPicWthLuma;
				local_xMin = xMin;
				local_yIdxChroma = yIdxChroma;
				local_BLK_SIDE = BLK_SIDE;
				local_xIdxChroma = xIdxChroma;
				tmp_Byte0 = tokens_Byte[(index_Byte % SIZE_Byte) + ((y - local_yIdxChroma) * (local_BLK_SIDE >> 1) + x - local_xIdxChroma)];
				pictureBufferV[(y - local_yMin / 2) * local_cropPicWthLuma / 2 + x - local_xMin / 2] = tmp_Byte0;
			}
			x = x + 1;
		}
		y = y + 1;
	}
	local_chromaComponent = chromaComponent;
	if (local_chromaComponent != 0) {
		local_xIdxChroma = xIdxChroma;
		local_BLK_SIDE = BLK_SIDE;
		xIdxChroma = local_xIdxChroma + (local_BLK_SIDE >> 1);
		local_xIdxLuma = xIdxLuma;
		local_pictureWidthLuma = pictureWidthLuma;
		if (local_xIdxLuma == local_pictureWidthLuma) {
			xIdxLuma = 0;
			xIdxChroma = 0;
			local_yIdxLuma = yIdxLuma;
			local_BLK_SIDE = BLK_SIDE;
			yIdxLuma = local_yIdxLuma + local_BLK_SIDE;
			local_yIdxChroma = yIdxChroma;
			local_BLK_SIDE = BLK_SIDE;
			yIdxChroma = local_yIdxChroma + (local_BLK_SIDE >> 1);
		}
	}
	chromaComponent = 1;

	// Update ports indexes
	index_Byte += 64;
	read_end_Byte();

	rate_Byte += 64;
}
static i32 isSchedulable_getPixValue_launch_Chroma_blk64x64() {
	i32 result;
	u8 local_BLK_SIDE;

	local_BLK_SIDE = BLK_SIDE;
	result = local_BLK_SIDE == 64;
	return result;
}

static void getPixValue_launch_Chroma_blk64x64() {

	u16 local_xIdxChroma;
	u16 local_xMin;
	u16 xIdxMin;
	u8 local_BLK_SIDE;
	u16 local_xMax;
	u16 xIdxMax;
	u32 local_yIdxChroma;
	u16 local_yMin;
	u16 yIdxMin;
	u16 local_yMax;
	u16 yIdxMax;
	u8 local_chromaComponent;
	i32 bCondition;
	i32 y;
	i32 x;
	u16 local_cropPicWthLuma;
	u8 tmp_Byte;
	u8 tmp_Byte0;
	u16 local_xIdxLuma;
	u16 local_pictureWidthLuma;
	u16 local_yIdxLuma;

	local_xIdxChroma = xIdxChroma;
	local_xMin = xMin;
	xIdxMin = check_MD5_MD5SplitInfo_max(local_xIdxChroma, local_xMin / 2);
	local_xIdxChroma = xIdxChroma;
	local_BLK_SIDE = BLK_SIDE;
	local_xMax = xMax;
	xIdxMax = check_MD5_MD5SplitInfo_min(local_xIdxChroma + (local_BLK_SIDE >> 1) - 1, local_xMax / 2);
	local_yIdxChroma = yIdxChroma;
	local_yMin = yMin;
	yIdxMin = check_MD5_MD5SplitInfo_max(local_yIdxChroma, local_yMin / 2);
	local_yIdxChroma = yIdxChroma;
	local_BLK_SIDE = BLK_SIDE;
	local_yMax = yMax;
	yIdxMax = check_MD5_MD5SplitInfo_min(local_yIdxChroma + (local_BLK_SIDE >> 1) - 1, local_yMax / 2);
	local_chromaComponent = chromaComponent;
	bCondition = local_chromaComponent == 0;
	y = yIdxMin;
	while (y <= yIdxMax) {
		x = xIdxMin;
		while (x <= xIdxMax) {
			if (bCondition) {
				local_yMin = yMin;
				local_cropPicWthLuma = cropPicWthLuma;
				local_xMin = xMin;
				local_yIdxChroma = yIdxChroma;
				local_BLK_SIDE = BLK_SIDE;
				local_xIdxChroma = xIdxChroma;
				tmp_Byte = tokens_Byte[(index_Byte + ((y - local_yIdxChroma) * (local_BLK_SIDE >> 1) + x - local_xIdxChroma)) % SIZE_Byte];
				pictureBufferU[(y - local_yMin / 2) * local_cropPicWthLuma / 2 + x - local_xMin / 2] = tmp_Byte;
			} else {
				local_yMin = yMin;
				local_cropPicWthLuma = cropPicWthLuma;
				local_xMin = xMin;
				local_yIdxChroma = yIdxChroma;
				local_BLK_SIDE = BLK_SIDE;
				local_xIdxChroma = xIdxChroma;
				tmp_Byte0 = tokens_Byte[(index_Byte + ((y - local_yIdxChroma) * (local_BLK_SIDE >> 1) + x - local_xIdxChroma)) % SIZE_Byte];
				pictureBufferV[(y - local_yMin / 2) * local_cropPicWthLuma / 2 + x - local_xMin / 2] = tmp_Byte0;
			}
			x = x + 1;
		}
		y = y + 1;
	}
	local_chromaComponent = chromaComponent;
	if (local_chromaComponent != 0) {
		local_xIdxChroma = xIdxChroma;
		local_BLK_SIDE = BLK_SIDE;
		xIdxChroma = local_xIdxChroma + (local_BLK_SIDE >> 1);
		local_xIdxLuma = xIdxLuma;
		local_pictureWidthLuma = pictureWidthLuma;
		if (local_xIdxLuma == local_pictureWidthLuma) {
			xIdxLuma = 0;
			xIdxChroma = 0;
			local_yIdxLuma = yIdxLuma;
			local_BLK_SIDE = BLK_SIDE;
			yIdxLuma = local_yIdxLuma + local_BLK_SIDE;
			local_yIdxChroma = yIdxChroma;
			local_BLK_SIDE = BLK_SIDE;
			yIdxChroma = local_yIdxChroma + (local_BLK_SIDE >> 1);
		}
	}
	chromaComponent = 1;

	// Update ports indexes
	index_Byte += 1024;
	read_end_Byte();

	rate_Byte += 1024;
}
static void getPixValue_launch_Chroma_blk64x64_aligned() {

	u16 local_xIdxChroma;
	u16 local_xMin;
	u16 xIdxMin;
	u8 local_BLK_SIDE;
	u16 local_xMax;
	u16 xIdxMax;
	u32 local_yIdxChroma;
	u16 local_yMin;
	u16 yIdxMin;
	u16 local_yMax;
	u16 yIdxMax;
	u8 local_chromaComponent;
	i32 bCondition;
	i32 y;
	i32 x;
	u16 local_cropPicWthLuma;
	u8 tmp_Byte;
	u8 tmp_Byte0;
	u16 local_xIdxLuma;
	u16 local_pictureWidthLuma;
	u16 local_yIdxLuma;

	local_xIdxChroma = xIdxChroma;
	local_xMin = xMin;
	xIdxMin = check_MD5_MD5SplitInfo_max(local_xIdxChroma, local_xMin / 2);
	local_xIdxChroma = xIdxChroma;
	local_BLK_SIDE = BLK_SIDE;
	local_xMax = xMax;
	xIdxMax = check_MD5_MD5SplitInfo_min(local_xIdxChroma + (local_BLK_SIDE >> 1) - 1, local_xMax / 2);
	local_yIdxChroma = yIdxChroma;
	local_yMin = yMin;
	yIdxMin = check_MD5_MD5SplitInfo_max(local_yIdxChroma, local_yMin / 2);
	local_yIdxChroma = yIdxChroma;
	local_BLK_SIDE = BLK_SIDE;
	local_yMax = yMax;
	yIdxMax = check_MD5_MD5SplitInfo_min(local_yIdxChroma + (local_BLK_SIDE >> 1) - 1, local_yMax / 2);
	local_chromaComponent = chromaComponent;
	bCondition = local_chromaComponent == 0;
	y = yIdxMin;
	while (y <= yIdxMax) {
		x = xIdxMin;
		while (x <= xIdxMax) {
			if (bCondition) {
				local_yMin = yMin;
				local_cropPicWthLuma = cropPicWthLuma;
				local_xMin = xMin;
				local_yIdxChroma = yIdxChroma;
				local_BLK_SIDE = BLK_SIDE;
				local_xIdxChroma = xIdxChroma;
				tmp_Byte = tokens_Byte[(index_Byte % SIZE_Byte) + ((y - local_yIdxChroma) * (local_BLK_SIDE >> 1) + x - local_xIdxChroma)];
				pictureBufferU[(y - local_yMin / 2) * local_cropPicWthLuma / 2 + x - local_xMin / 2] = tmp_Byte;
			} else {
				local_yMin = yMin;
				local_cropPicWthLuma = cropPicWthLuma;
				local_xMin = xMin;
				local_yIdxChroma = yIdxChroma;
				local_BLK_SIDE = BLK_SIDE;
				local_xIdxChroma = xIdxChroma;
				tmp_Byte0 = tokens_Byte[(index_Byte % SIZE_Byte) + ((y - local_yIdxChroma) * (local_BLK_SIDE >> 1) + x - local_xIdxChroma)];
				pictureBufferV[(y - local_yMin / 2) * local_cropPicWthLuma / 2 + x - local_xMin / 2] = tmp_Byte0;
			}
			x = x + 1;
		}
		y = y + 1;
	}
	local_chromaComponent = chromaComponent;
	if (local_chromaComponent != 0) {
		local_xIdxChroma = xIdxChroma;
		local_BLK_SIDE = BLK_SIDE;
		xIdxChroma = local_xIdxChroma + (local_BLK_SIDE >> 1);
		local_xIdxLuma = xIdxLuma;
		local_pictureWidthLuma = pictureWidthLuma;
		if (local_xIdxLuma == local_pictureWidthLuma) {
			xIdxLuma = 0;
			xIdxChroma = 0;
			local_yIdxLuma = yIdxLuma;
			local_BLK_SIDE = BLK_SIDE;
			yIdxLuma = local_yIdxLuma + local_BLK_SIDE;
			local_yIdxChroma = yIdxChroma;
			local_BLK_SIDE = BLK_SIDE;
			yIdxChroma = local_yIdxChroma + (local_BLK_SIDE >> 1);
		}
	}
	chromaComponent = 1;

	// Update ports indexes
	index_Byte += 1024;
	read_end_Byte();

	rate_Byte += 1024;
}
static i32 isSchedulable_initOutputLoop() {
	i32 result;
	i32 local_nbBlockGot;
	i32 local_pictureSizeInMb;

	local_nbBlockGot = nbBlockGot;
	local_pictureSizeInMb = pictureSizeInMb;
	result = local_nbBlockGot >= local_pictureSizeInMb;
	return result;
}

static void initOutputLoop() {


	idx = 0;

	// Update ports indexes

}
static i32 isSchedulable_outputLoop_Y_loop() {
	i32 result;
	u64 local_idx;
	u64 local_lumaSize;

	local_idx = idx;
	local_lumaSize = lumaSize;
	result = local_idx < local_lumaSize;
	return result;
}

static void outputLoop_Y_loop() {

	u64 local_idx;
	u64 tmp;
	u8 tmp_pictureBufferY;

	local_idx = idx;
	tmp = local_idx;
	local_idx = idx;
	idx = local_idx + 1;
	tmp_pictureBufferY = pictureBufferY[tmp];
	tokens_DataOut[(index_DataOut + (0)) % SIZE_DataOut] = tmp_pictureBufferY;

	// Update ports indexes
	index_DataOut += 1;

}
static i32 isSchedulable_outputLoop_Y_endLoop() {
	i32 result;
	u64 local_idx;
	u64 local_lumaSize;

	local_idx = idx;
	local_lumaSize = lumaSize;
	result = local_idx == local_lumaSize;
	return result;
}

static void outputLoop_Y_endLoop() {


	idx = 0;

	// Update ports indexes

}
static i32 isSchedulable_outputLoop_U_loop() {
	i32 result;
	u64 local_idx;
	u64 local_chromaSize;

	local_idx = idx;
	local_chromaSize = chromaSize;
	result = local_idx < local_chromaSize;
	return result;
}

static void outputLoop_U_loop() {

	u64 local_idx;
	u64 tmp;
	u8 tmp_pictureBufferU;

	local_idx = idx;
	tmp = local_idx;
	local_idx = idx;
	idx = local_idx + 1;
	tmp_pictureBufferU = pictureBufferU[tmp];
	tokens_DataOut[(index_DataOut + (0)) % SIZE_DataOut] = tmp_pictureBufferU;

	// Update ports indexes
	index_DataOut += 1;

}
static i32 isSchedulable_outputLoop_U_endLoop() {
	i32 result;
	u64 local_idx;
	u64 local_chromaSize;

	local_idx = idx;
	local_chromaSize = chromaSize;
	result = local_idx == local_chromaSize;
	return result;
}

static void outputLoop_U_endLoop() {


	idx = 0;

	// Update ports indexes

}
static i32 isSchedulable_outputLoop_V_loop() {
	i32 result;
	u64 local_idx;
	u64 local_chromaSize;

	local_idx = idx;
	local_chromaSize = chromaSize;
	result = local_idx < local_chromaSize;
	return result;
}

static void outputLoop_V_loop() {

	u64 local_idx;
	u64 tmp;
	u8 tmp_pictureBufferV;

	local_idx = idx;
	tmp = local_idx;
	local_idx = idx;
	idx = local_idx + 1;
	tmp_pictureBufferV = pictureBufferV[tmp];
	tokens_DataOut[(index_DataOut + (0)) % SIZE_DataOut] = tmp_pictureBufferV;

	// Update ports indexes
	index_DataOut += 1;

}
static i32 isSchedulable_outputLoop_V_endLoop() {
	i32 result;
	u64 local_idx;
	u64 local_chromaSize;

	local_idx = idx;
	local_chromaSize = chromaSize;
	result = local_idx == local_chromaSize;
	return result;
}

static void outputLoop_V_endLoop() {


	idx = 0;

	// Update ports indexes

}

////////////////////////////////////////////////////////////////////////////////
// Initializes

void check_MD5_MD5SplitInfo_initialize(schedinfo_t *si) {
	int i = 0;
	write_Length();
	write_DataOut();
	/* Set initial state to current FSM state */
	_FSM_state = my_state_GetPictureSize;
finished:
	write_end_Length();
	write_end_DataOut();
	return;
}

////////////////////////////////////////////////////////////////////////////////
// Action scheduler

void check_MD5_MD5SplitInfo_scheduler(schedinfo_t *si) {
	int i = 0;

	read_Byte();
	read_PictSize();
	write_Length();
	write_DataOut();

	// jump to FSM state
	switch (_FSM_state) {
	case my_state_GetChroma1Block:
		goto l_GetChroma1Block;
	case my_state_GetChroma2Block:
		goto l_GetChroma2Block;
	case my_state_GetLumaBlock:
		goto l_GetLumaBlock;
	case my_state_GetPictureSize:
		goto l_GetPictureSize;
	case my_state_outputLoopU:
		goto l_outputLoopU;
	case my_state_outputLoopV:
		goto l_outputLoopV;
	case my_state_outputLoopY:
		goto l_outputLoopY;
	default:
		printf("unknown state in check_MD5_MD5SplitInfo.c : %s\n", stateNames[_FSM_state]);
		exit(1);
	}

	// FSM transitions
l_GetChroma1Block:
	if (numTokens_Byte - index_Byte >= 64 && isSchedulable_getPixValue_launch_Chroma_blk16x16()) {
		{
			int isAligned = 1;
			isAligned &= ((index_Byte % SIZE_Byte) < ((index_Byte + 64) % SIZE_Byte));
			if (isAligned) {
				getPixValue_launch_Chroma_blk16x16_aligned();
			} else {
				getPixValue_launch_Chroma_blk16x16();
			}
		}
		i++;
		goto l_GetChroma2Block;
	} else if (numTokens_Byte - index_Byte >= 1024 && isSchedulable_getPixValue_launch_Chroma_blk64x64()) {
		{
			int isAligned = 1;
			isAligned &= ((index_Byte % SIZE_Byte) < ((index_Byte + 1024) % SIZE_Byte));
			if (isAligned) {
				getPixValue_launch_Chroma_blk64x64_aligned();
			} else {
				getPixValue_launch_Chroma_blk64x64();
			}
		}
		i++;
		goto l_GetChroma2Block;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetChroma1Block;
		goto finished;
	}
l_GetChroma2Block:
	if (numTokens_Byte - index_Byte >= 64 && isSchedulable_getPixValue_launch_Chroma_blk16x16()) {
		{
			int isAligned = 1;
			isAligned &= ((index_Byte % SIZE_Byte) < ((index_Byte + 64) % SIZE_Byte));
			if (isAligned) {
				getPixValue_launch_Chroma_blk16x16_aligned();
			} else {
				getPixValue_launch_Chroma_blk16x16();
			}
		}
		i++;
		goto l_GetLumaBlock;
	} else if (numTokens_Byte - index_Byte >= 1024 && isSchedulable_getPixValue_launch_Chroma_blk64x64()) {
		{
			int isAligned = 1;
			isAligned &= ((index_Byte % SIZE_Byte) < ((index_Byte + 1024) % SIZE_Byte));
			if (isAligned) {
				getPixValue_launch_Chroma_blk64x64_aligned();
			} else {
				getPixValue_launch_Chroma_blk64x64();
			}
		}
		i++;
		goto l_GetLumaBlock;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetChroma2Block;
		goto finished;
	}
l_GetLumaBlock:
	if (numTokens_Byte - index_Byte >= 256 && isSchedulable_getPixValue_launch_Luma_blk16x16()) {
		{
			int isAligned = 1;
			isAligned &= ((index_Byte % SIZE_Byte) < ((index_Byte + 256) % SIZE_Byte));
			if (isAligned) {
				getPixValue_launch_Luma_blk16x16_aligned();
			} else {
				getPixValue_launch_Luma_blk16x16();
			}
		}
		i++;
		goto l_GetChroma1Block;
	} else if (numTokens_Byte - index_Byte >= 4096 && isSchedulable_getPixValue_launch_Luma_blk64x64()) {
		{
			int isAligned = 1;
			isAligned &= ((index_Byte % SIZE_Byte) < ((index_Byte + 4096) % SIZE_Byte));
			if (isAligned) {
				getPixValue_launch_Luma_blk64x64_aligned();
			} else {
				getPixValue_launch_Luma_blk64x64();
			}
		}
		i++;
		goto l_GetChroma1Block;
	} else if (isSchedulable_initOutputLoop()) {
		initOutputLoop();
		i++;
		goto l_outputLoopY;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetLumaBlock;
		goto finished;
	}
l_GetPictureSize:
	if (numTokens_PictSize - index_PictSize >= 2 && isSchedulable_getPictureSize()) {
		int stop = 0;
		if (3 > SIZE_Length - index_Length + check_MD5_MD5SplitInfo_Length->read_inds[0]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_GetPictureSize;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		{
			int isAligned = 1;
			isAligned &= ((index_Length % SIZE_Length) < ((index_Length + 3) % SIZE_Length));
			if (isAligned) {
				getPictureSize_aligned();
			} else {
				getPictureSize();
			}
		}
		i++;
		goto l_GetLumaBlock;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetPictureSize;
		goto finished;
	}
l_outputLoopU:
	if (isSchedulable_outputLoop_U_loop()) {
		int stop = 0;
		if (1 > SIZE_DataOut - index_DataOut + check_MD5_MD5SplitInfo_DataOut->read_inds[0]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_outputLoopU;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		outputLoop_U_loop();
		i++;
		goto l_outputLoopU;
	} else if (isSchedulable_outputLoop_U_endLoop()) {
		outputLoop_U_endLoop();
		i++;
		goto l_outputLoopV;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_outputLoopU;
		goto finished;
	}
l_outputLoopV:
	if (isSchedulable_outputLoop_V_loop()) {
		int stop = 0;
		if (1 > SIZE_DataOut - index_DataOut + check_MD5_MD5SplitInfo_DataOut->read_inds[0]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_outputLoopV;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		outputLoop_V_loop();
		i++;
		goto l_outputLoopV;
	} else if (isSchedulable_outputLoop_V_endLoop()) {
		outputLoop_V_endLoop();
		i++;
		goto l_GetPictureSize;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_outputLoopV;
		goto finished;
	}
l_outputLoopY:
	if (isSchedulable_outputLoop_Y_loop()) {
		int stop = 0;
		if (1 > SIZE_DataOut - index_DataOut + check_MD5_MD5SplitInfo_DataOut->read_inds[0]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_outputLoopY;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		outputLoop_Y_loop();
		i++;
		goto l_outputLoopY;
	} else if (isSchedulable_outputLoop_Y_endLoop()) {
		outputLoop_Y_endLoop();
		i++;
		goto l_outputLoopU;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_outputLoopY;
		goto finished;
	}
finished:
	read_end_Byte();
	read_end_PictSize();
	write_end_Length();
	write_end_DataOut();
}
