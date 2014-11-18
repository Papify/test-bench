// Source file is "L/RVC/src/org/sc29/wg11/common/DisplayYUVWithCrop.cal"

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
extern actor_t display;

////////////////////////////////////////////////////////////////////////////////
// Input FIFOs
extern fifo_u8_t *display_Byte;
extern fifo_u16_t *display_DispCoord;
extern fifo_u16_t *display_PicSizeInMb;

////////////////////////////////////////////////////////////////////////////////
// Input Fifo control variables
static unsigned int index_Byte;
static unsigned int numTokens_Byte;
#define SIZE_Byte SIZE
#define tokens_Byte display_Byte->contents

extern connection_t connection_display_Byte;
#define rate_Byte connection_display_Byte.rate

static unsigned int index_DispCoord;
static unsigned int numTokens_DispCoord;
#define SIZE_DispCoord SIZE
#define tokens_DispCoord display_DispCoord->contents

extern connection_t connection_display_DispCoord;
#define rate_DispCoord connection_display_DispCoord.rate

static unsigned int index_PicSizeInMb;
static unsigned int numTokens_PicSizeInMb;
#define SIZE_PicSizeInMb SIZE
#define tokens_PicSizeInMb display_PicSizeInMb->contents

extern connection_t connection_display_PicSizeInMb;
#define rate_PicSizeInMb connection_display_PicSizeInMb.rate

////////////////////////////////////////////////////////////////////////////////
// Predecessors
extern actor_t HevcDecoder_SAO;
extern actor_t HevcDecoder_Algo_Parser;
extern actor_t HevcDecoder_Algo_Parser;

////////////////////////////////////////////////////////////////////////////////
// Parameter values of the instance
#define BLK_SIDE 16


////////////////////////////////////////////////////////////////////////////////
// State variables of the actor
#define display_MB_SIZE_LUMA 16
#define display_MB_SIZE_CHROMA 8
#define display_DISP_ENABLE 1
static u8 pictureBufferY[8388608];
static u8 pictureBufferU[2097152];
static u8 pictureBufferV[2097152];
static i32 pictureSizeInMb;
static i32 nbBlockGot;
static i32 nbFrameDecoded;
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
static i32 isTerminated = 0;

////////////////////////////////////////////////////////////////////////////////
// Initial FSM state of the actor
enum states {
	my_state_GetChroma1Block,
	my_state_GetChroma2Block,
	my_state_GetLumaBlock,
	my_state_GetPictureSize
};

static char *stateNames[] = {
	"GetChroma1Block",
	"GetChroma2Block",
	"GetLumaBlock",
	"GetPictureSize"
};

static enum states _FSM_state;



////////////////////////////////////////////////////////////////////////////////
// Token functions
static void read_Byte() {
	index_Byte = display_Byte->read_inds[1];
	numTokens_Byte = index_Byte + fifo_u8_get_num_tokens(display_Byte, 1);
}

static void read_end_Byte() {
	display_Byte->read_inds[1] = index_Byte;
}
static void read_DispCoord() {
	index_DispCoord = display_DispCoord->read_inds[0];
	numTokens_DispCoord = index_DispCoord + fifo_u16_get_num_tokens(display_DispCoord, 0);
}

static void read_end_DispCoord() {
	display_DispCoord->read_inds[0] = index_DispCoord;
}
static void read_PicSizeInMb() {
	index_PicSizeInMb = display_PicSizeInMb->read_inds[0];
	numTokens_PicSizeInMb = index_PicSizeInMb + fifo_u16_get_num_tokens(display_PicSizeInMb, 0);
}

static void read_end_PicSizeInMb() {
	display_PicSizeInMb->read_inds[0] = index_PicSizeInMb;
}


////////////////////////////////////////////////////////////////////////////////
// Functions/procedures
extern i32 source_isMaxLoopsReached();
extern i32 displayYUV_getNbFrames();
extern void source_exit(i32 exitCode);
static i32 display_max(i32 a, i32 b);
static i32 display_min(i32 a, i32 b);
static void display_displayYUV_crop_16_cal(u8 Bytes[256], u8 pictureBuffer[8388608], u16 xMin, u16 xMax, u16 yMin, u16 yMax, u16 xIdx, u16 yIdx, u16 cropPicWth);
static void display_displayYUV_crop_64_cal(u8 Bytes[4096], u8 pictureBuffer[8388608], u16 xMin, u16 xMax, u16 yMin, u16 yMax, u16 xIdx, u16 yIdx, u16 cropPicWth);
static void display_displayYUV_crop_8_cal(u8 Bytes[64], u8 pictureBuffer[2097152], u16 xMin, u16 xMax, u16 yMin, u16 yMax, u16 xIdx, u16 yIdx, u16 cropPicWth);
static void display_displayYUV_crop_32_cal(u8 Bytes[1024], u8 pictureBuffer[8388608], u16 xMin, u16 xMax, u16 yMin, u16 yMax, u16 xIdx, u16 yIdx, u16 cropPicWth);
extern void fpsPrintNewPicDecoded();
extern u8 displayYUV_getFlags();
extern void displayYUV_displayPicture(u8 pictureBufferY[8388608], u8 pictureBufferU[8388608], u8 pictureBufferV[8388608], i16 pictureWidth, i16 pictureSize);
extern void compareYUV_comparePicture(u8 pictureBufferY[8388608], u8 pictureBufferU[8388608], u8 pictureBufferV[8388608], i16 pictureWidth, i16 pictureSize);
extern void displayYUV_init();
extern void compareYUV_init();
extern void fpsPrintInit();

static i32 display_max(i32 a, i32 b) {
	i32 tmp_if;

	if (a > b) {
		tmp_if = a;
	} else {
		tmp_if = b;
	}
	return tmp_if;
}
static i32 display_min(i32 a, i32 b) {
	i32 tmp_if;

	if (a < b) {
		tmp_if = a;
	} else {
		tmp_if = b;
	}
	return tmp_if;
}
static void display_displayYUV_crop_16_cal(u8 Bytes[256], u8 pictureBuffer[8388608], u16 xMin, u16 xMax, u16 yMin, u16 yMax, u16 xIdx, u16 yIdx, u16 cropPicWth) {
	#if defined(SSE_ENABLE)
	displayYUV_crop_16_orcc(Bytes, pictureBuffer, xMin, xMax, yMin, yMax, xIdx, yIdx, cropPicWth);
	#else
	u16 xIdxMin;
	u16 xIdxMax;
	u16 yIdxMin;
	u16 yIdxMax;
	i32 y;
	i32 x;
	u8 tmp_Bytes;

	xIdxMin = display_max(xIdx, xMin);
	xIdxMax = display_min(xIdx + 15, xMax);
	yIdxMin = display_max(yIdx, yMin);
	yIdxMax = display_min(yIdx + 15, yMax);
	y = yIdxMin;
	while (y <= yIdxMax) {
		x = xIdxMin;
		while (x <= xIdxMax) {
			tmp_Bytes = Bytes[(y - yIdx) * 16 + x - xIdx];
			pictureBuffer[(y - yMin) * cropPicWth + x - xMin] = tmp_Bytes;
			x = x + 1;
		}
		y = y + 1;
	}
	#endif // defined(SSE_ENABLE)
}
static void display_displayYUV_crop_64_cal(u8 Bytes[4096], u8 pictureBuffer[8388608], u16 xMin, u16 xMax, u16 yMin, u16 yMax, u16 xIdx, u16 yIdx, u16 cropPicWth) {
	#if defined(SSE_ENABLE)
	displayYUV_crop_64_orcc(Bytes, pictureBuffer, xMin, xMax, yMin, yMax, xIdx, yIdx, cropPicWth);
	#else
	u16 xIdxMin;
	u16 xIdxMax;
	u16 yIdxMin;
	u16 yIdxMax;
	i32 y;
	i32 x;
	u8 tmp_Bytes;

	xIdxMin = display_max(xIdx, xMin);
	xIdxMax = display_min(xIdx + 63, xMax);
	yIdxMin = display_max(yIdx, yMin);
	yIdxMax = display_min(yIdx + 63, yMax);
	y = yIdxMin;
	while (y <= yIdxMax) {
		x = xIdxMin;
		while (x <= xIdxMax) {
			tmp_Bytes = Bytes[(y - yIdx) * 64 + x - xIdx];
			pictureBuffer[(y - yMin) * cropPicWth + x - xMin] = tmp_Bytes;
			x = x + 1;
		}
		y = y + 1;
	}
	#endif // defined(SSE_ENABLE)
}
static void display_displayYUV_crop_8_cal(u8 Bytes[64], u8 pictureBuffer[2097152], u16 xMin, u16 xMax, u16 yMin, u16 yMax, u16 xIdx, u16 yIdx, u16 cropPicWth) {
	#if defined(SSE_ENABLE)
	displayYUV_crop_8_orcc(Bytes, pictureBuffer, xMin, xMax, yMin, yMax, xIdx, yIdx, cropPicWth);
	#else
	u16 xIdxMin;
	u16 xIdxMax;
	u16 yIdxMin;
	u16 yIdxMax;
	i32 y;
	i32 x;
	u8 tmp_Bytes;

	xIdxMin = display_max(xIdx, xMin);
	xIdxMax = display_min(xIdx + 7, xMax);
	yIdxMin = display_max(yIdx, yMin);
	yIdxMax = display_min(yIdx + 7, yMax);
	y = yIdxMin;
	while (y <= yIdxMax) {
		x = xIdxMin;
		while (x <= xIdxMax) {
			tmp_Bytes = Bytes[(y - yIdx) * 8 + x - xIdx];
			pictureBuffer[(y - yMin) * cropPicWth + x - xMin] = tmp_Bytes;
			x = x + 1;
		}
		y = y + 1;
	}
	#endif // defined(SSE_ENABLE)
}
static void display_displayYUV_crop_32_cal(u8 Bytes[1024], u8 pictureBuffer[8388608], u16 xMin, u16 xMax, u16 yMin, u16 yMax, u16 xIdx, u16 yIdx, u16 cropPicWth) {
	#if defined(SSE_ENABLE)
	displayYUV_crop_32_orcc(Bytes, pictureBuffer, xMin, xMax, yMin, yMax, xIdx, yIdx, cropPicWth);
	#else
	u16 xIdxMin;
	u16 xIdxMax;
	u16 yIdxMin;
	u16 yIdxMax;
	i32 y;
	i32 x;
	u8 tmp_Bytes;

	xIdxMin = display_max(xIdx, xMin);
	xIdxMax = display_min(xIdx + 31, xMax);
	yIdxMin = display_max(yIdx, yMin);
	yIdxMax = display_min(yIdx + 31, yMax);
	y = yIdxMin;
	while (y <= yIdxMax) {
		x = xIdxMin;
		while (x <= xIdxMax) {
			tmp_Bytes = Bytes[(y - yIdx) * 32 + x - xIdx];
			pictureBuffer[(y - yMin) * cropPicWth + x - xMin] = tmp_Bytes;
			x = x + 1;
		}
		y = y + 1;
	}
	#endif // defined(SSE_ENABLE)
}

////////////////////////////////////////////////////////////////////////////////
// Actions
static i32 isSchedulable_untagged_0() {
	i32 result;
	i32 local_isTerminated;
	i32 tmp_source_isMaxLoopsReached;
	i32 local_nbFrameDecoded;
	i32 tmp_displayYUV_getNbFrames;

	local_isTerminated = isTerminated;
	tmp_source_isMaxLoopsReached = source_isMaxLoopsReached();
	local_nbFrameDecoded = nbFrameDecoded;
	tmp_displayYUV_getNbFrames = displayYUV_getNbFrames();
	result = !local_isTerminated && (tmp_source_isMaxLoopsReached || local_nbFrameDecoded == tmp_displayYUV_getNbFrames);
	return result;
}

static void untagged_0() {


	isTerminated = 1;
	source_exit(0);

	// Update ports indexes

}
static i32 isSchedulable_getPictureSize() {
	i32 result;

	result = 1;
	return result;
}

static void getPictureSize_aligned() {

	u16 picWidthInPix;
	u16 picHeightInPix;
	u16 picWidth;
	u16 picHeight;
	u8 local_BLK_SIDE;
	u16 tmp_DispCoord;
	u16 tmp_DispCoord0;
	u16 tmp_DispCoord1;
	u16 tmp_DispCoord2;
	u16 local_xMax;
	u16 local_xMin;
	u16 local_yMax;
	u16 local_yMin;

	picWidthInPix = tokens_PicSizeInMb[(index_PicSizeInMb % SIZE_PicSizeInMb) + (0)];
	picHeightInPix = tokens_PicSizeInMb[(index_PicSizeInMb % SIZE_PicSizeInMb) + (1)];
	picWidth = (picWidthInPix + 15) / 16;
	picHeight = (picHeightInPix + 15) / 16;
	local_BLK_SIDE = BLK_SIDE;
	pictureWidthLuma = picWidth * local_BLK_SIDE;
	pictureSizeInMb = picWidth * picHeight;
	tmp_DispCoord = tokens_DispCoord[(index_DispCoord % SIZE_DispCoord) + (0)];
	xMin = tmp_DispCoord;
	tmp_DispCoord0 = tokens_DispCoord[(index_DispCoord % SIZE_DispCoord) + (1)];
	xMax = tmp_DispCoord0;
	tmp_DispCoord1 = tokens_DispCoord[(index_DispCoord % SIZE_DispCoord) + (2)];
	yMin = tmp_DispCoord1;
	tmp_DispCoord2 = tokens_DispCoord[(index_DispCoord % SIZE_DispCoord) + (3)];
	yMax = tmp_DispCoord2;
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

	// Update ports indexes
	index_DispCoord += 4;
	read_end_DispCoord();
	index_PicSizeInMb += 2;
	read_end_PicSizeInMb();

	rate_DispCoord += 4;
	rate_PicSizeInMb += 2;
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

	i32 local_nbBlockGot;
	u8 local_Byte[256];
	i32 idx_Byte;
	u8 local_Byte0;
	u16 local_xMin;
	u16 local_xMax;
	u16 local_yMin;
	u16 local_yMax;
	u16 local_xIdxLuma;
	u16 local_yIdxLuma;
	u16 local_cropPicWthLuma;
	u32 local_MB_SIZE_LUMA;

	local_nbBlockGot = nbBlockGot;
	nbBlockGot = local_nbBlockGot + 1;
	idx_Byte = 0;
	while (idx_Byte < 256) {
		local_Byte0 = tokens_Byte[(index_Byte + (idx_Byte)) % SIZE_Byte];
		local_Byte[idx_Byte] = local_Byte0;
		idx_Byte = idx_Byte + 1;
	}
	local_xMin = xMin;
	local_xMax = xMax;
	local_yMin = yMin;
	local_yMax = yMax;
	local_xIdxLuma = xIdxLuma;
	local_yIdxLuma = yIdxLuma;
	local_cropPicWthLuma = cropPicWthLuma;
	display_displayYUV_crop_16_cal(local_Byte, pictureBufferY, local_xMin, local_xMax, local_yMin, local_yMax, local_xIdxLuma, local_yIdxLuma, local_cropPicWthLuma);
	local_xIdxLuma = xIdxLuma;
	local_MB_SIZE_LUMA = display_MB_SIZE_LUMA;
	xIdxLuma = local_xIdxLuma + local_MB_SIZE_LUMA;
	chromaComponent = 0;

	// Update ports indexes
	index_Byte += 256;
	read_end_Byte();

	rate_Byte += 256;
}
static void getPixValue_launch_Luma_blk16x16_aligned() {

	i32 local_nbBlockGot;
	u8 local_Byte[256];
	i32 idx_Byte;
	u8 local_Byte0;
	u16 local_xMin;
	u16 local_xMax;
	u16 local_yMin;
	u16 local_yMax;
	u16 local_xIdxLuma;
	u16 local_yIdxLuma;
	u16 local_cropPicWthLuma;
	u32 local_MB_SIZE_LUMA;

	local_nbBlockGot = nbBlockGot;
	nbBlockGot = local_nbBlockGot + 1;
	idx_Byte = 0;
	local_xMin = xMin;
	local_xMax = xMax;
	local_yMin = yMin;
	local_yMax = yMax;
	local_xIdxLuma = xIdxLuma;
	local_yIdxLuma = yIdxLuma;
	local_cropPicWthLuma = cropPicWthLuma;
	display_displayYUV_crop_16_cal(&tokens_Byte[index_Byte % SIZE_Byte], pictureBufferY, local_xMin, local_xMax, local_yMin, local_yMax, local_xIdxLuma, local_yIdxLuma, local_cropPicWthLuma);
	local_xIdxLuma = xIdxLuma;
	local_MB_SIZE_LUMA = display_MB_SIZE_LUMA;
	xIdxLuma = local_xIdxLuma + local_MB_SIZE_LUMA;
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

	i32 local_nbBlockGot;
	u8 local_Byte[4096];
	i32 idx_Byte;
	u8 local_Byte0;
	u16 local_xMin;
	u16 local_xMax;
	u16 local_yMin;
	u16 local_yMax;
	u16 local_xIdxLuma;
	u16 local_yIdxLuma;
	u16 local_cropPicWthLuma;

	local_nbBlockGot = nbBlockGot;
	nbBlockGot = local_nbBlockGot + 1;
	idx_Byte = 0;
	while (idx_Byte < 4096) {
		local_Byte0 = tokens_Byte[(index_Byte + (idx_Byte)) % SIZE_Byte];
		local_Byte[idx_Byte] = local_Byte0;
		idx_Byte = idx_Byte + 1;
	}
	local_xMin = xMin;
	local_xMax = xMax;
	local_yMin = yMin;
	local_yMax = yMax;
	local_xIdxLuma = xIdxLuma;
	local_yIdxLuma = yIdxLuma;
	local_cropPicWthLuma = cropPicWthLuma;
	display_displayYUV_crop_64_cal(local_Byte, pictureBufferY, local_xMin, local_xMax, local_yMin, local_yMax, local_xIdxLuma, local_yIdxLuma, local_cropPicWthLuma);
	local_xIdxLuma = xIdxLuma;
	xIdxLuma = local_xIdxLuma + 64;
	chromaComponent = 0;

	// Update ports indexes
	index_Byte += 4096;
	read_end_Byte();

	rate_Byte += 4096;
}
static void getPixValue_launch_Luma_blk64x64_aligned() {

	i32 local_nbBlockGot;
	u8 local_Byte[4096];
	i32 idx_Byte;
	u8 local_Byte0;
	u16 local_xMin;
	u16 local_xMax;
	u16 local_yMin;
	u16 local_yMax;
	u16 local_xIdxLuma;
	u16 local_yIdxLuma;
	u16 local_cropPicWthLuma;

	local_nbBlockGot = nbBlockGot;
	nbBlockGot = local_nbBlockGot + 1;
	idx_Byte = 0;
	local_xMin = xMin;
	local_xMax = xMax;
	local_yMin = yMin;
	local_yMax = yMax;
	local_xIdxLuma = xIdxLuma;
	local_yIdxLuma = yIdxLuma;
	local_cropPicWthLuma = cropPicWthLuma;
	display_displayYUV_crop_64_cal(&tokens_Byte[index_Byte % SIZE_Byte], pictureBufferY, local_xMin, local_xMax, local_yMin, local_yMax, local_xIdxLuma, local_yIdxLuma, local_cropPicWthLuma);
	local_xIdxLuma = xIdxLuma;
	xIdxLuma = local_xIdxLuma + 64;
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

	u8 local_chromaComponent;
	u8 local_Byte[64];
	i32 idx_Byte;
	u8 local_Byte0;
	u16 local_xMin;
	u16 local_xMax;
	u16 local_yMin;
	u16 local_yMax;
	u16 local_xIdxChroma;
	u32 local_yIdxChroma;
	u16 local_cropPicWthLuma;
	u8 local_Byte1[64];
	i32 idx_Byte0;
	u8 local_Byte2;
	u32 local_MB_SIZE_CHROMA;
	u16 local_xIdxLuma;
	u16 local_pictureWidthLuma;
	u16 local_yIdxLuma;
	u32 local_MB_SIZE_LUMA;

	local_chromaComponent = chromaComponent;
	if (local_chromaComponent == 0) {
		idx_Byte = 0;
		while (idx_Byte < 64) {
			local_Byte0 = tokens_Byte[(index_Byte + (idx_Byte)) % SIZE_Byte];
			local_Byte[idx_Byte] = local_Byte0;
			idx_Byte = idx_Byte + 1;
		}
		local_xMin = xMin;
		local_xMax = xMax;
		local_yMin = yMin;
		local_yMax = yMax;
		local_xIdxChroma = xIdxChroma;
		local_yIdxChroma = yIdxChroma;
		local_cropPicWthLuma = cropPicWthLuma;
		display_displayYUV_crop_8_cal(local_Byte, pictureBufferU, local_xMin / 2, local_xMax / 2, local_yMin / 2, local_yMax / 2, local_xIdxChroma, local_yIdxChroma, local_cropPicWthLuma / 2);
	} else {
		idx_Byte0 = 0;
		while (idx_Byte0 < 64) {
			local_Byte2 = tokens_Byte[(index_Byte + (idx_Byte0)) % SIZE_Byte];
			local_Byte1[idx_Byte0] = local_Byte2;
			idx_Byte0 = idx_Byte0 + 1;
		}
		local_xMin = xMin;
		local_xMax = xMax;
		local_yMin = yMin;
		local_yMax = yMax;
		local_xIdxChroma = xIdxChroma;
		local_yIdxChroma = yIdxChroma;
		local_cropPicWthLuma = cropPicWthLuma;
		display_displayYUV_crop_8_cal(local_Byte1, pictureBufferV, local_xMin / 2, local_xMax / 2, local_yMin / 2, local_yMax / 2, local_xIdxChroma, local_yIdxChroma, local_cropPicWthLuma / 2);
	}
	local_chromaComponent = chromaComponent;
	if (local_chromaComponent != 0) {
		local_xIdxChroma = xIdxChroma;
		local_MB_SIZE_CHROMA = display_MB_SIZE_CHROMA;
		xIdxChroma = local_xIdxChroma + local_MB_SIZE_CHROMA;
		local_xIdxLuma = xIdxLuma;
		local_pictureWidthLuma = pictureWidthLuma;
		if (local_xIdxLuma == local_pictureWidthLuma) {
			xIdxLuma = 0;
			xIdxChroma = 0;
			local_yIdxLuma = yIdxLuma;
			local_MB_SIZE_LUMA = display_MB_SIZE_LUMA;
			yIdxLuma = local_yIdxLuma + local_MB_SIZE_LUMA;
			local_yIdxChroma = yIdxChroma;
			local_MB_SIZE_CHROMA = display_MB_SIZE_CHROMA;
			yIdxChroma = local_yIdxChroma + local_MB_SIZE_CHROMA;
		}
	}
	chromaComponent = 1;

	// Update ports indexes
	index_Byte += 64;
	read_end_Byte();

	rate_Byte += 64;
}
static void getPixValue_launch_Chroma_blk16x16_aligned() {

	u8 local_chromaComponent;
	u8 local_Byte[64];
	i32 idx_Byte;
	u8 local_Byte0;
	u16 local_xMin;
	u16 local_xMax;
	u16 local_yMin;
	u16 local_yMax;
	u16 local_xIdxChroma;
	u32 local_yIdxChroma;
	u16 local_cropPicWthLuma;
	u8 local_Byte1[64];
	i32 idx_Byte0;
	u8 local_Byte2;
	u32 local_MB_SIZE_CHROMA;
	u16 local_xIdxLuma;
	u16 local_pictureWidthLuma;
	u16 local_yIdxLuma;
	u32 local_MB_SIZE_LUMA;

	local_chromaComponent = chromaComponent;
	if (local_chromaComponent == 0) {
		idx_Byte = 0;
		local_xMin = xMin;
		local_xMax = xMax;
		local_yMin = yMin;
		local_yMax = yMax;
		local_xIdxChroma = xIdxChroma;
		local_yIdxChroma = yIdxChroma;
		local_cropPicWthLuma = cropPicWthLuma;
		display_displayYUV_crop_8_cal(&tokens_Byte[index_Byte % SIZE_Byte], pictureBufferU, local_xMin / 2, local_xMax / 2, local_yMin / 2, local_yMax / 2, local_xIdxChroma, local_yIdxChroma, local_cropPicWthLuma / 2);
	} else {
		idx_Byte0 = 0;
		local_xMin = xMin;
		local_xMax = xMax;
		local_yMin = yMin;
		local_yMax = yMax;
		local_xIdxChroma = xIdxChroma;
		local_yIdxChroma = yIdxChroma;
		local_cropPicWthLuma = cropPicWthLuma;
		display_displayYUV_crop_8_cal(&tokens_Byte[index_Byte % SIZE_Byte], pictureBufferV, local_xMin / 2, local_xMax / 2, local_yMin / 2, local_yMax / 2, local_xIdxChroma, local_yIdxChroma, local_cropPicWthLuma / 2);
	}
	local_chromaComponent = chromaComponent;
	if (local_chromaComponent != 0) {
		local_xIdxChroma = xIdxChroma;
		local_MB_SIZE_CHROMA = display_MB_SIZE_CHROMA;
		xIdxChroma = local_xIdxChroma + local_MB_SIZE_CHROMA;
		local_xIdxLuma = xIdxLuma;
		local_pictureWidthLuma = pictureWidthLuma;
		if (local_xIdxLuma == local_pictureWidthLuma) {
			xIdxLuma = 0;
			xIdxChroma = 0;
			local_yIdxLuma = yIdxLuma;
			local_MB_SIZE_LUMA = display_MB_SIZE_LUMA;
			yIdxLuma = local_yIdxLuma + local_MB_SIZE_LUMA;
			local_yIdxChroma = yIdxChroma;
			local_MB_SIZE_CHROMA = display_MB_SIZE_CHROMA;
			yIdxChroma = local_yIdxChroma + local_MB_SIZE_CHROMA;
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

	u8 local_chromaComponent;
	u8 local_Byte[1024];
	i32 idx_Byte;
	u8 local_Byte0;
	u16 local_xMin;
	u16 local_xMax;
	u16 local_yMin;
	u16 local_yMax;
	u16 local_xIdxChroma;
	u32 local_yIdxChroma;
	u16 local_cropPicWthLuma;
	u8 local_Byte1[1024];
	i32 idx_Byte0;
	u8 local_Byte2;
	u16 local_xIdxLuma;
	u16 local_pictureWidthLuma;
	u16 local_yIdxLuma;

	local_chromaComponent = chromaComponent;
	if (local_chromaComponent == 0) {
		idx_Byte = 0;
		while (idx_Byte < 1024) {
			local_Byte0 = tokens_Byte[(index_Byte + (idx_Byte)) % SIZE_Byte];
			local_Byte[idx_Byte] = local_Byte0;
			idx_Byte = idx_Byte + 1;
		}
		local_xMin = xMin;
		local_xMax = xMax;
		local_yMin = yMin;
		local_yMax = yMax;
		local_xIdxChroma = xIdxChroma;
		local_yIdxChroma = yIdxChroma;
		local_cropPicWthLuma = cropPicWthLuma;
		display_displayYUV_crop_32_cal(local_Byte, pictureBufferU, local_xMin / 2, local_xMax / 2, local_yMin / 2, local_yMax / 2, local_xIdxChroma, local_yIdxChroma, local_cropPicWthLuma / 2);
	} else {
		idx_Byte0 = 0;
		while (idx_Byte0 < 1024) {
			local_Byte2 = tokens_Byte[(index_Byte + (idx_Byte0)) % SIZE_Byte];
			local_Byte1[idx_Byte0] = local_Byte2;
			idx_Byte0 = idx_Byte0 + 1;
		}
		local_xMin = xMin;
		local_xMax = xMax;
		local_yMin = yMin;
		local_yMax = yMax;
		local_xIdxChroma = xIdxChroma;
		local_yIdxChroma = yIdxChroma;
		local_cropPicWthLuma = cropPicWthLuma;
		display_displayYUV_crop_32_cal(local_Byte1, pictureBufferV, local_xMin / 2, local_xMax / 2, local_yMin / 2, local_yMax / 2, local_xIdxChroma, local_yIdxChroma, local_cropPicWthLuma / 2);
	}
	local_chromaComponent = chromaComponent;
	if (local_chromaComponent != 0) {
		local_xIdxChroma = xIdxChroma;
		xIdxChroma = local_xIdxChroma + 32;
		local_xIdxLuma = xIdxLuma;
		local_pictureWidthLuma = pictureWidthLuma;
		if (local_xIdxLuma == local_pictureWidthLuma) {
			xIdxLuma = 0;
			xIdxChroma = 0;
			local_yIdxLuma = yIdxLuma;
			yIdxLuma = local_yIdxLuma + 64;
			local_yIdxChroma = yIdxChroma;
			yIdxChroma = local_yIdxChroma + 32;
		}
	}
	chromaComponent = 1;

	// Update ports indexes
	index_Byte += 1024;
	read_end_Byte();

	rate_Byte += 1024;
}
static void getPixValue_launch_Chroma_blk64x64_aligned() {

	u8 local_chromaComponent;
	u8 local_Byte[1024];
	i32 idx_Byte;
	u8 local_Byte0;
	u16 local_xMin;
	u16 local_xMax;
	u16 local_yMin;
	u16 local_yMax;
	u16 local_xIdxChroma;
	u32 local_yIdxChroma;
	u16 local_cropPicWthLuma;
	u8 local_Byte1[1024];
	i32 idx_Byte0;
	u8 local_Byte2;
	u16 local_xIdxLuma;
	u16 local_pictureWidthLuma;
	u16 local_yIdxLuma;

	local_chromaComponent = chromaComponent;
	if (local_chromaComponent == 0) {
		idx_Byte = 0;
		local_xMin = xMin;
		local_xMax = xMax;
		local_yMin = yMin;
		local_yMax = yMax;
		local_xIdxChroma = xIdxChroma;
		local_yIdxChroma = yIdxChroma;
		local_cropPicWthLuma = cropPicWthLuma;
		display_displayYUV_crop_32_cal(&tokens_Byte[index_Byte % SIZE_Byte], pictureBufferU, local_xMin / 2, local_xMax / 2, local_yMin / 2, local_yMax / 2, local_xIdxChroma, local_yIdxChroma, local_cropPicWthLuma / 2);
	} else {
		idx_Byte0 = 0;
		local_xMin = xMin;
		local_xMax = xMax;
		local_yMin = yMin;
		local_yMax = yMax;
		local_xIdxChroma = xIdxChroma;
		local_yIdxChroma = yIdxChroma;
		local_cropPicWthLuma = cropPicWthLuma;
		display_displayYUV_crop_32_cal(&tokens_Byte[index_Byte % SIZE_Byte], pictureBufferV, local_xMin / 2, local_xMax / 2, local_yMin / 2, local_yMax / 2, local_xIdxChroma, local_yIdxChroma, local_cropPicWthLuma / 2);
	}
	local_chromaComponent = chromaComponent;
	if (local_chromaComponent != 0) {
		local_xIdxChroma = xIdxChroma;
		xIdxChroma = local_xIdxChroma + 32;
		local_xIdxLuma = xIdxLuma;
		local_pictureWidthLuma = pictureWidthLuma;
		if (local_xIdxLuma == local_pictureWidthLuma) {
			xIdxLuma = 0;
			xIdxChroma = 0;
			local_yIdxLuma = yIdxLuma;
			yIdxLuma = local_yIdxLuma + 64;
			local_yIdxChroma = yIdxChroma;
			yIdxChroma = local_yIdxChroma + 32;
		}
	}
	chromaComponent = 1;

	// Update ports indexes
	index_Byte += 1024;
	read_end_Byte();

	rate_Byte += 1024;
}
static i32 isSchedulable_displayPicture() {
	i32 result;
	i32 local_nbBlockGot;
	i32 local_pictureSizeInMb;

	local_nbBlockGot = nbBlockGot;
	local_pictureSizeInMb = pictureSizeInMb;
	result = local_nbBlockGot >= local_pictureSizeInMb;
	return result;
}

static void displayPicture() {

	u8 tmp_displayYUV_getFlags;
	u8 local_DISP_ENABLE;
	u16 local_cropPicWthLuma;
	u16 local_cropPicHghtLuma;
	i32 local_nbFrameDecoded;

	fpsPrintNewPicDecoded();
	tmp_displayYUV_getFlags = displayYUV_getFlags();
	local_DISP_ENABLE = display_DISP_ENABLE;
	if ((tmp_displayYUV_getFlags & local_DISP_ENABLE) != 0) {
		local_cropPicWthLuma = cropPicWthLuma;
		local_cropPicHghtLuma = cropPicHghtLuma;
		displayYUV_displayPicture(pictureBufferY, pictureBufferU, pictureBufferV, local_cropPicWthLuma, local_cropPicHghtLuma);
	}
	local_cropPicWthLuma = cropPicWthLuma;
	local_cropPicHghtLuma = cropPicHghtLuma;
	compareYUV_comparePicture(pictureBufferY, pictureBufferU, pictureBufferV, local_cropPicWthLuma, local_cropPicHghtLuma);
	local_nbFrameDecoded = nbFrameDecoded;
	nbFrameDecoded = local_nbFrameDecoded + 1;

	// Update ports indexes

}

////////////////////////////////////////////////////////////////////////////////
// Initializes
static i32 isSchedulable_untagged_1() {
	i32 result;

	result = 1;
	return result;
}

static void untagged_1() {

	u8 tmp_displayYUV_getFlags;
	u8 local_DISP_ENABLE;

	tmp_displayYUV_getFlags = displayYUV_getFlags();
	local_DISP_ENABLE = display_DISP_ENABLE;
	if ((tmp_displayYUV_getFlags & local_DISP_ENABLE) != 0) {
		displayYUV_init();
	}
	compareYUV_init();
	fpsPrintInit();
	nbFrameDecoded = 0;

	// Update ports indexes

}

void display_initialize(schedinfo_t *si) {
	int i = 0;
	/* Set initial state to current FSM state */
	_FSM_state = my_state_GetPictureSize;
	if(isSchedulable_untagged_1()) {
		untagged_1();
	}
finished:
	return;
}

////////////////////////////////////////////////////////////////////////////////
// Action scheduler
void display_outside_FSM_scheduler(schedinfo_t *si) {
	int i = 0;
	while (1) {
		if (isSchedulable_untagged_0()) {
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

void display_scheduler(schedinfo_t *si) {
	int i = 0;

	read_Byte();
	read_DispCoord();
	read_PicSizeInMb();

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
	default:
		printf("unknown state in display.c : %s\n", stateNames[_FSM_state]);
		exit(1);
	}

	// FSM transitions
l_GetChroma1Block:
	display_outside_FSM_scheduler(si);
	i += si->num_firings;
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
	display_outside_FSM_scheduler(si);
	i += si->num_firings;
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
	display_outside_FSM_scheduler(si);
	i += si->num_firings;
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
	} else if (isSchedulable_displayPicture()) {
		displayPicture();
		i++;
		goto l_GetPictureSize;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetLumaBlock;
		goto finished;
	}
l_GetPictureSize:
	display_outside_FSM_scheduler(si);
	i += si->num_firings;
	if (numTokens_DispCoord - index_DispCoord >= 4 && numTokens_PicSizeInMb - index_PicSizeInMb >= 2 && isSchedulable_getPictureSize()) {
		getPictureSize_aligned();
		i++;
		goto l_GetLumaBlock;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetPictureSize;
		goto finished;
	}
finished:
	read_end_Byte();
	read_end_DispCoord();
	read_end_PicSizeInMb();
}
