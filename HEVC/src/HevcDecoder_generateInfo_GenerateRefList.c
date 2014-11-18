// Source file is "L/RVC/src/org/sc29/wg11/mpegh/part2/main/inter/GenerateRefList.cal"

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
extern actor_t HevcDecoder_generateInfo_GenerateRefList;

////////////////////////////////////////////////////////////////////////////////
// Input FIFOs
extern fifo_i16_t *HevcDecoder_generateInfo_GenerateRefList_RefPoc;
extern fifo_u8_t *HevcDecoder_generateInfo_GenerateRefList_NumRefIdxLXAct;
extern fifo_u8_t *HevcDecoder_generateInfo_GenerateRefList_RefPicListModif;

////////////////////////////////////////////////////////////////////////////////
// Input Fifo control variables
static unsigned int index_RefPoc;
static unsigned int numTokens_RefPoc;
#define SIZE_RefPoc SIZE
#define tokens_RefPoc HevcDecoder_generateInfo_GenerateRefList_RefPoc->contents

extern connection_t connection_HevcDecoder_generateInfo_GenerateRefList_RefPoc;
#define rate_RefPoc connection_HevcDecoder_generateInfo_GenerateRefList_RefPoc.rate

static unsigned int index_NumRefIdxLXAct;
static unsigned int numTokens_NumRefIdxLXAct;
#define SIZE_NumRefIdxLXAct SIZE
#define tokens_NumRefIdxLXAct HevcDecoder_generateInfo_GenerateRefList_NumRefIdxLXAct->contents

extern connection_t connection_HevcDecoder_generateInfo_GenerateRefList_NumRefIdxLXAct;
#define rate_NumRefIdxLXAct connection_HevcDecoder_generateInfo_GenerateRefList_NumRefIdxLXAct.rate

static unsigned int index_RefPicListModif;
static unsigned int numTokens_RefPicListModif;
#define SIZE_RefPicListModif SIZE
#define tokens_RefPicListModif HevcDecoder_generateInfo_GenerateRefList_RefPicListModif->contents

extern connection_t connection_HevcDecoder_generateInfo_GenerateRefList_RefPicListModif;
#define rate_RefPicListModif connection_HevcDecoder_generateInfo_GenerateRefList_RefPicListModif.rate

////////////////////////////////////////////////////////////////////////////////
// Predecessors
extern actor_t HevcDecoder_Algo_Parser;
extern actor_t HevcDecoder_Algo_Parser;
extern actor_t HevcDecoder_Algo_Parser;

////////////////////////////////////////////////////////////////////////////////
// Output FIFOs
extern fifo_i16_t *HevcDecoder_generateInfo_GenerateRefList_RefList;

////////////////////////////////////////////////////////////////////////////////
// Output Fifo control variables
static unsigned int index_RefList;
static unsigned int numFree_RefList;
#define NUM_READERS_RefList 2
#define SIZE_RefList SIZE
#define tokens_RefList HevcDecoder_generateInfo_GenerateRefList_RefList->contents

////////////////////////////////////////////////////////////////////////////////
// Successors
extern actor_t HevcDecoder_generateInfo_MvComponentPred;
extern actor_t HevcDecoder_InterPrediction;


////////////////////////////////////////////////////////////////////////////////
// State variables of the actor
#define HevcDecoder_generateInfo_GenerateRefList_ST_CURR_BEF 0
#define HevcDecoder_generateInfo_GenerateRefList_ST_CURR_AFT 1
#define HevcDecoder_generateInfo_GenerateRefList_LT_CURR 3
static u8 numListRemain;
static u8 numRefIdxLxAct[2];
static u32 iLoop;
static u8 listIdx;
static i32 refPicListX[2][16];
static i32 numPic[5];
static i32 pocTables[5][16];

////////////////////////////////////////////////////////////////////////////////
// Initial FSM state of the actor
enum states {
	my_state_GetListModif,
	my_state_GetNumRefIdxLX,
	my_state_GetRefPocContent,
	my_state_GetSizeList,
	my_state_SendingModifiedList,
	my_state_SendingUnmodifiedList
};

static char *stateNames[] = {
	"GetListModif",
	"GetNumRefIdxLX",
	"GetRefPocContent",
	"GetSizeList",
	"SendingModifiedList",
	"SendingUnmodifiedList"
};

static enum states _FSM_state;



////////////////////////////////////////////////////////////////////////////////
// Token functions
static void read_RefPoc() {
	index_RefPoc = HevcDecoder_generateInfo_GenerateRefList_RefPoc->read_inds[1];
	numTokens_RefPoc = index_RefPoc + fifo_i16_get_num_tokens(HevcDecoder_generateInfo_GenerateRefList_RefPoc, 1);
}

static void read_end_RefPoc() {
	HevcDecoder_generateInfo_GenerateRefList_RefPoc->read_inds[1] = index_RefPoc;
}
static void read_NumRefIdxLXAct() {
	index_NumRefIdxLXAct = HevcDecoder_generateInfo_GenerateRefList_NumRefIdxLXAct->read_inds[0];
	numTokens_NumRefIdxLXAct = index_NumRefIdxLXAct + fifo_u8_get_num_tokens(HevcDecoder_generateInfo_GenerateRefList_NumRefIdxLXAct, 0);
}

static void read_end_NumRefIdxLXAct() {
	HevcDecoder_generateInfo_GenerateRefList_NumRefIdxLXAct->read_inds[0] = index_NumRefIdxLXAct;
}
static void read_RefPicListModif() {
	index_RefPicListModif = HevcDecoder_generateInfo_GenerateRefList_RefPicListModif->read_inds[0];
	numTokens_RefPicListModif = index_RefPicListModif + fifo_u8_get_num_tokens(HevcDecoder_generateInfo_GenerateRefList_RefPicListModif, 0);
}

static void read_end_RefPicListModif() {
	HevcDecoder_generateInfo_GenerateRefList_RefPicListModif->read_inds[0] = index_RefPicListModif;
}

static void write_RefList() {
	index_RefList = HevcDecoder_generateInfo_GenerateRefList_RefList->write_ind;
	numFree_RefList = index_RefList + fifo_i16_get_room(HevcDecoder_generateInfo_GenerateRefList_RefList, NUM_READERS_RefList, SIZE_RefList);
}

static void write_end_RefList() {
	HevcDecoder_generateInfo_GenerateRefList_RefList->write_ind = index_RefList;
}

////////////////////////////////////////////////////////////////////////////////
// Functions/procedures
static i32 HevcDecoder_generateInfo_GenerateRefList_max(i32 a, i32 b);
static void refListXInit(u8 listIdx, u32 numRefIdxLXAct);

static i32 HevcDecoder_generateInfo_GenerateRefList_max(i32 a, i32 b) {
	i32 tmp_if;

	if (a > b) {
		tmp_if = a;
	} else {
		tmp_if = b;
	}
	return tmp_if;
}
static void refListXInit(u8 listIdx, u32 numRefIdxLXAct) {
	u32 cIdx;
	u32 numPocTotalCurr;
	u32 numRpsCurrLX;
	u32 firstList;
	u32 secList;
	u8 local_ST_CURR_BEF;
	u8 local_ST_CURR_AFT;
	i32 tmp_numPic;
	i32 tmp_numPic0;
	u8 local_LT_CURR;
	i32 tmp_numPic1;
	i32 i;
	i32 tmp_numPic2;
	i32 tmp_pocTables;
	i32 i0;
	i32 tmp_numPic3;
	i32 tmp_pocTables0;
	i32 i1;
	i32 tmp_numPic4;
	i32 tmp_pocTables1;

	if (listIdx == 0) {
		local_ST_CURR_BEF = HevcDecoder_generateInfo_GenerateRefList_ST_CURR_BEF;
		firstList = local_ST_CURR_BEF;
	} else {
		local_ST_CURR_AFT = HevcDecoder_generateInfo_GenerateRefList_ST_CURR_AFT;
		firstList = local_ST_CURR_AFT;
	}
	if (listIdx == 0) {
		local_ST_CURR_AFT = HevcDecoder_generateInfo_GenerateRefList_ST_CURR_AFT;
		secList = local_ST_CURR_AFT;
	} else {
		local_ST_CURR_BEF = HevcDecoder_generateInfo_GenerateRefList_ST_CURR_BEF;
		secList = local_ST_CURR_BEF;
	}
	local_ST_CURR_BEF = HevcDecoder_generateInfo_GenerateRefList_ST_CURR_BEF;
	tmp_numPic = numPic[local_ST_CURR_BEF];
	local_ST_CURR_AFT = HevcDecoder_generateInfo_GenerateRefList_ST_CURR_AFT;
	tmp_numPic0 = numPic[local_ST_CURR_AFT];
	local_LT_CURR = HevcDecoder_generateInfo_GenerateRefList_LT_CURR;
	tmp_numPic1 = numPic[local_LT_CURR];
	numPocTotalCurr = tmp_numPic + tmp_numPic0 + tmp_numPic1;
	numRpsCurrLX = HevcDecoder_generateInfo_GenerateRefList_max(numPocTotalCurr, numRefIdxLXAct);
	cIdx = 0;
	while (cIdx < numRpsCurrLX) {
		i = 0;
		tmp_numPic2 = numPic[firstList];
		while (i <= tmp_numPic2 - 1) {
			tmp_pocTables = pocTables[firstList][i];
			refPicListX[listIdx][cIdx] = tmp_pocTables;
			cIdx = cIdx + 1;
			i = i + 1;
		}
		i0 = 0;
		tmp_numPic3 = numPic[secList];
		while (i0 <= tmp_numPic3 - 1) {
			tmp_pocTables0 = pocTables[secList][i0];
			refPicListX[listIdx][cIdx] = tmp_pocTables0;
			cIdx = cIdx + 1;
			i0 = i0 + 1;
		}
		i1 = 0;
		local_LT_CURR = HevcDecoder_generateInfo_GenerateRefList_LT_CURR;
		tmp_numPic4 = numPic[local_LT_CURR];
		while (i1 <= tmp_numPic4 - 1) {
			local_LT_CURR = HevcDecoder_generateInfo_GenerateRefList_LT_CURR;
			tmp_pocTables1 = pocTables[local_LT_CURR][i1];
			refPicListX[listIdx][cIdx] = tmp_pocTables1;
			cIdx = cIdx + 1;
			i1 = i1 + 1;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
// Actions
static i32 isSchedulable_getNumRefIdxLX() {
	i32 result;

	result = 1;
	return result;
}

static void getNumRefIdxLX_aligned() {

	u8 tmp_NumRefIdxLXAct;
	u8 tmp_NumRefIdxLXAct0;

	numListRemain = 5;
	tmp_NumRefIdxLXAct = tokens_NumRefIdxLXAct[(index_NumRefIdxLXAct % SIZE_NumRefIdxLXAct) + (0)];
	numRefIdxLxAct[0] = tmp_NumRefIdxLXAct;
	tmp_NumRefIdxLXAct0 = tokens_NumRefIdxLXAct[(index_NumRefIdxLXAct % SIZE_NumRefIdxLXAct) + (1)];
	numRefIdxLxAct[1] = tmp_NumRefIdxLXAct0;

	// Update ports indexes
	index_NumRefIdxLXAct += 2;
	read_end_NumRefIdxLXAct();

	rate_NumRefIdxLXAct += 2;
}
static i32 isSchedulable_getSizeList_launch() {
	i32 result;
	u8 local_numListRemain;

	local_numListRemain = numListRemain;
	result = local_numListRemain > 0;
	return result;
}

static void getSizeList_launch() {

	i16 szList;
	u8 local_numListRemain;

	szList = tokens_RefPoc[(index_RefPoc + (0)) % SIZE_RefPoc];
	local_numListRemain = numListRemain;
	numPic[5 - local_numListRemain] = szList;
	iLoop = 0;

	// Update ports indexes
	index_RefPoc += 1;

	rate_RefPoc += 1;
}
static i32 isSchedulable_getSizeList_done() {
	i32 result;
	u8 local_numListRemain;

	local_numListRemain = numListRemain;
	result = local_numListRemain == 0;
	return result;
}

static void getSizeList_done() {

	u8 tmp_numRefIdxLxAct;
	u8 tmp_numRefIdxLxAct0;
	u8 tmp_numRefIdxLxAct1;
	u8 tmp_numRefIdxLxAct2;

	tmp_numRefIdxLxAct = numRefIdxLxAct[0];
	if (tmp_numRefIdxLxAct > 0) {
		tmp_numRefIdxLxAct0 = numRefIdxLxAct[0];
		refListXInit(0, tmp_numRefIdxLxAct0);
	}
	tmp_numRefIdxLxAct1 = numRefIdxLxAct[1];
	if (tmp_numRefIdxLxAct1 > 0) {
		tmp_numRefIdxLxAct2 = numRefIdxLxAct[1];
		refListXInit(1, tmp_numRefIdxLxAct2);
	}
	listIdx = 0;

	// Update ports indexes

}
static i32 isSchedulable_getRefPocContent_launch() {
	i32 result;
	u32 local_iLoop;
	u8 local_numListRemain;
	i32 tmp_numPic;

	local_iLoop = iLoop;
	local_numListRemain = numListRemain;
	tmp_numPic = numPic[5 - local_numListRemain];
	result = local_iLoop < tmp_numPic;
	return result;
}

static void getRefPocContent_launch() {

	i16 pocVal;
	u8 local_numListRemain;
	u32 local_iLoop;

	pocVal = tokens_RefPoc[(index_RefPoc + (0)) % SIZE_RefPoc];
	local_numListRemain = numListRemain;
	local_iLoop = iLoop;
	pocTables[5 - local_numListRemain][local_iLoop] = pocVal;
	local_iLoop = iLoop;
	iLoop = local_iLoop + 1;

	// Update ports indexes
	index_RefPoc += 1;

	rate_RefPoc += 1;
}
static i32 isSchedulable_getRefPocContent_done() {
	i32 result;
	u32 local_iLoop;
	u8 local_numListRemain;
	i32 tmp_numPic;

	local_iLoop = iLoop;
	local_numListRemain = numListRemain;
	tmp_numPic = numPic[5 - local_numListRemain];
	result = local_iLoop == tmp_numPic;
	return result;
}

static void getRefPocContent_done() {

	u8 local_numListRemain;

	local_numListRemain = numListRemain;
	numListRemain = local_numListRemain - 1;

	// Update ports indexes

}
static i32 isSchedulable_getListModif_isFalse() {
	i32 result;
	u8 listModif;
	u8 local_listIdx;

	listModif = tokens_RefPicListModif[(index_RefPicListModif + (0)) % SIZE_RefPicListModif];
	local_listIdx = listIdx;
	result = local_listIdx < 2 && listModif == 0;
	return result;
}

static void getListModif_isFalse() {

	u8 listModif;
	u8 local_listIdx;
	u8 tmp_numRefIdxLxAct;

	listModif = tokens_RefPicListModif[(index_RefPicListModif + (0)) % SIZE_RefPicListModif];
	iLoop = 0;
	local_listIdx = listIdx;
	tmp_numRefIdxLxAct = numRefIdxLxAct[local_listIdx];
	tokens_RefList[(index_RefList + (0)) % SIZE_RefList] = tmp_numRefIdxLxAct;

	// Update ports indexes
	index_RefPicListModif += 1;
	index_RefList += 1;

	rate_RefPicListModif += 1;
}
static i32 isSchedulable_sendingUnmodifiedList_launch() {
	i32 result;
	u32 local_iLoop;
	u8 local_listIdx;
	u8 tmp_numRefIdxLxAct;

	local_iLoop = iLoop;
	local_listIdx = listIdx;
	tmp_numRefIdxLxAct = numRefIdxLxAct[local_listIdx];
	result = local_iLoop < tmp_numRefIdxLxAct;
	return result;
}

static void sendingUnmodifiedList_launch() {

	u32 local_iLoop;
	u8 local_listIdx;
	i32 tmp_refPicListX;

	local_iLoop = iLoop;
	iLoop = local_iLoop + 1;
	local_listIdx = listIdx;
	local_iLoop = iLoop;
	tmp_refPicListX = refPicListX[local_listIdx][local_iLoop - 1];
	tokens_RefList[(index_RefList + (0)) % SIZE_RefList] = tmp_refPicListX;

	// Update ports indexes
	index_RefList += 1;

}
static i32 isSchedulable_sendingUnmodifiedList_done() {
	i32 result;
	u32 local_iLoop;
	u8 local_listIdx;
	u8 tmp_numRefIdxLxAct;

	local_iLoop = iLoop;
	local_listIdx = listIdx;
	tmp_numRefIdxLxAct = numRefIdxLxAct[local_listIdx];
	result = local_iLoop == tmp_numRefIdxLxAct;
	return result;
}

static void sendingUnmodifiedList_done() {

	u8 local_listIdx;

	local_listIdx = listIdx;
	listIdx = local_listIdx + 1;

	// Update ports indexes

}
static i32 isSchedulable_getListModif_isTrue() {
	i32 result;
	u8 listModif;
	u8 local_listIdx;

	listModif = tokens_RefPicListModif[(index_RefPicListModif + (0)) % SIZE_RefPicListModif];
	local_listIdx = listIdx;
	result = local_listIdx < 2 && listModif == 1;
	return result;
}

static void getListModif_isTrue() {

	u8 listModif;
	u8 local_listIdx;
	u8 tmp_numRefIdxLxAct;

	listModif = tokens_RefPicListModif[(index_RefPicListModif + (0)) % SIZE_RefPicListModif];
	iLoop = 0;
	local_listIdx = listIdx;
	tmp_numRefIdxLxAct = numRefIdxLxAct[local_listIdx];
	tokens_RefList[(index_RefList + (0)) % SIZE_RefList] = tmp_numRefIdxLxAct;

	// Update ports indexes
	index_RefPicListModif += 1;
	index_RefList += 1;

	rate_RefPicListModif += 1;
}
static i32 isSchedulable_sendingModifiedList_launch() {
	i32 result;
	u32 local_iLoop;
	u8 local_listIdx;
	u8 tmp_numRefIdxLxAct;

	local_iLoop = iLoop;
	local_listIdx = listIdx;
	tmp_numRefIdxLxAct = numRefIdxLxAct[local_listIdx];
	result = local_iLoop < tmp_numRefIdxLxAct;
	return result;
}

static void sendingModifiedList_launch() {

	u8 listEntry;
	u32 local_iLoop;
	u8 local_listIdx;
	i32 tmp_refPicListX;

	listEntry = tokens_RefPicListModif[(index_RefPicListModif + (0)) % SIZE_RefPicListModif];
	local_iLoop = iLoop;
	iLoop = local_iLoop + 1;
	local_listIdx = listIdx;
	tmp_refPicListX = refPicListX[local_listIdx][listEntry];
	tokens_RefList[(index_RefList + (0)) % SIZE_RefList] = tmp_refPicListX;

	// Update ports indexes
	index_RefPicListModif += 1;
	index_RefList += 1;

	rate_RefPicListModif += 1;
}
static i32 isSchedulable_sendingModifiedList_done() {
	i32 result;
	u32 local_iLoop;
	u8 local_listIdx;
	u8 tmp_numRefIdxLxAct;

	local_iLoop = iLoop;
	local_listIdx = listIdx;
	tmp_numRefIdxLxAct = numRefIdxLxAct[local_listIdx];
	result = local_iLoop == tmp_numRefIdxLxAct;
	return result;
}

static void sendingModifiedList_done() {

	u8 local_listIdx;

	local_listIdx = listIdx;
	listIdx = local_listIdx + 1;

	// Update ports indexes

}
static i32 isSchedulable_getListModif_done() {
	i32 result;
	u8 local_listIdx;

	local_listIdx = listIdx;
	result = local_listIdx == 2;
	return result;
}

static void getListModif_done() {


	iLoop = 0;

	// Update ports indexes

}

////////////////////////////////////////////////////////////////////////////////
// Initializes

void HevcDecoder_generateInfo_GenerateRefList_initialize(schedinfo_t *si) {
	int i = 0;
	write_RefList();
	/* Set initial state to current FSM state */
	_FSM_state = my_state_GetNumRefIdxLX;
finished:
	write_end_RefList();
	return;
}

////////////////////////////////////////////////////////////////////////////////
// Action scheduler

void HevcDecoder_generateInfo_GenerateRefList_scheduler(schedinfo_t *si) {
	int i = 0;

	read_RefPoc();
	read_NumRefIdxLXAct();
	read_RefPicListModif();
	write_RefList();

	// jump to FSM state
	switch (_FSM_state) {
	case my_state_GetListModif:
		goto l_GetListModif;
	case my_state_GetNumRefIdxLX:
		goto l_GetNumRefIdxLX;
	case my_state_GetRefPocContent:
		goto l_GetRefPocContent;
	case my_state_GetSizeList:
		goto l_GetSizeList;
	case my_state_SendingModifiedList:
		goto l_SendingModifiedList;
	case my_state_SendingUnmodifiedList:
		goto l_SendingUnmodifiedList;
	default:
		printf("unknown state in HevcDecoder_generateInfo_GenerateRefList.c : %s\n", stateNames[_FSM_state]);
		exit(1);
	}

	// FSM transitions
l_GetListModif:
	if (numTokens_RefPicListModif - index_RefPicListModif >= 1 && isSchedulable_getListModif_isFalse()) {
		int stop = 0;
		if (1 > SIZE_RefList - index_RefList + HevcDecoder_generateInfo_GenerateRefList_RefList->read_inds[0]) {
			stop = 1;
		}
		if (1 > SIZE_RefList - index_RefList + HevcDecoder_generateInfo_GenerateRefList_RefList->read_inds[1]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_GetListModif;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		getListModif_isFalse();
		i++;
		goto l_SendingUnmodifiedList;
	} else if (numTokens_RefPicListModif - index_RefPicListModif >= 1 && isSchedulable_getListModif_isTrue()) {
		int stop = 0;
		if (1 > SIZE_RefList - index_RefList + HevcDecoder_generateInfo_GenerateRefList_RefList->read_inds[0]) {
			stop = 1;
		}
		if (1 > SIZE_RefList - index_RefList + HevcDecoder_generateInfo_GenerateRefList_RefList->read_inds[1]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_GetListModif;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		getListModif_isTrue();
		i++;
		goto l_SendingModifiedList;
	} else if (isSchedulable_getListModif_done()) {
		getListModif_done();
		i++;
		goto l_GetNumRefIdxLX;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetListModif;
		goto finished;
	}
l_GetNumRefIdxLX:
	if (numTokens_NumRefIdxLXAct - index_NumRefIdxLXAct >= 2 && isSchedulable_getNumRefIdxLX()) {
		getNumRefIdxLX_aligned();
		i++;
		goto l_GetSizeList;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetNumRefIdxLX;
		goto finished;
	}
l_GetRefPocContent:
	if (numTokens_RefPoc - index_RefPoc >= 1 && isSchedulable_getRefPocContent_launch()) {
		getRefPocContent_launch();
		i++;
		goto l_GetRefPocContent;
	} else if (isSchedulable_getRefPocContent_done()) {
		getRefPocContent_done();
		i++;
		goto l_GetSizeList;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetRefPocContent;
		goto finished;
	}
l_GetSizeList:
	if (numTokens_RefPoc - index_RefPoc >= 1 && isSchedulable_getSizeList_launch()) {
		getSizeList_launch();
		i++;
		goto l_GetRefPocContent;
	} else if (isSchedulable_getSizeList_done()) {
		getSizeList_done();
		i++;
		goto l_GetListModif;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_GetSizeList;
		goto finished;
	}
l_SendingModifiedList:
	if (numTokens_RefPicListModif - index_RefPicListModif >= 1 && isSchedulable_sendingModifiedList_launch()) {
		int stop = 0;
		if (1 > SIZE_RefList - index_RefList + HevcDecoder_generateInfo_GenerateRefList_RefList->read_inds[0]) {
			stop = 1;
		}
		if (1 > SIZE_RefList - index_RefList + HevcDecoder_generateInfo_GenerateRefList_RefList->read_inds[1]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_SendingModifiedList;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		sendingModifiedList_launch();
		i++;
		goto l_SendingModifiedList;
	} else if (isSchedulable_sendingModifiedList_done()) {
		sendingModifiedList_done();
		i++;
		goto l_GetListModif;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_SendingModifiedList;
		goto finished;
	}
l_SendingUnmodifiedList:
	if (isSchedulable_sendingUnmodifiedList_launch()) {
		int stop = 0;
		if (1 > SIZE_RefList - index_RefList + HevcDecoder_generateInfo_GenerateRefList_RefList->read_inds[0]) {
			stop = 1;
		}
		if (1 > SIZE_RefList - index_RefList + HevcDecoder_generateInfo_GenerateRefList_RefList->read_inds[1]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_SendingUnmodifiedList;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		sendingUnmodifiedList_launch();
		i++;
		goto l_SendingUnmodifiedList;
	} else if (isSchedulable_sendingUnmodifiedList_done()) {
		sendingUnmodifiedList_done();
		i++;
		goto l_GetListModif;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_SendingUnmodifiedList;
		goto finished;
	}
finished:
	read_end_RefPoc();
	read_end_NumRefIdxLXAct();
	read_end_RefPicListModif();
	write_end_RefList();
}
