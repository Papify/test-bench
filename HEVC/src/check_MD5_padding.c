// Source file is "L/RVC/src/org/sc29/wg11/mpegh/part2/common/padding.cal"

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
extern actor_t check_MD5_padding;

////////////////////////////////////////////////////////////////////////////////
// Input FIFOs
extern fifo_u64_t *check_MD5_padding_LENGTH;
extern fifo_u8_t *check_MD5_padding_DATA;

////////////////////////////////////////////////////////////////////////////////
// Input Fifo control variables
static unsigned int index_LENGTH;
static unsigned int numTokens_LENGTH;
#define SIZE_LENGTH SIZE
#define tokens_LENGTH check_MD5_padding_LENGTH->contents

extern connection_t connection_check_MD5_padding_LENGTH;
#define rate_LENGTH connection_check_MD5_padding_LENGTH.rate

static unsigned int index_DATA;
static unsigned int numTokens_DATA;
#define SIZE_DATA SIZE
#define tokens_DATA check_MD5_padding_DATA->contents

extern connection_t connection_check_MD5_padding_DATA;
#define rate_DATA connection_check_MD5_padding_DATA.rate

////////////////////////////////////////////////////////////////////////////////
// Predecessors
extern actor_t check_MD5_MD5SplitInfo;
extern actor_t check_MD5_MD5SplitInfo;

////////////////////////////////////////////////////////////////////////////////
// Output FIFOs
extern fifo_u8_t *check_MD5_padding_OUT;
extern fifo_u32_t *check_MD5_padding_NEWLENGTH;

////////////////////////////////////////////////////////////////////////////////
// Output Fifo control variables
static unsigned int index_OUT;
static unsigned int numFree_OUT;
#define NUM_READERS_OUT 1
#define SIZE_OUT SIZE
#define tokens_OUT check_MD5_padding_OUT->contents

static unsigned int index_NEWLENGTH;
static unsigned int numFree_NEWLENGTH;
#define NUM_READERS_NEWLENGTH 1
#define SIZE_NEWLENGTH SIZE
#define tokens_NEWLENGTH check_MD5_padding_NEWLENGTH->contents

////////////////////////////////////////////////////////////////////////////////
// Successors
extern actor_t check_MD5_shifter;
extern actor_t check_MD5_compute;


////////////////////////////////////////////////////////////////////////////////
// State variables of the actor
static u64 length;
static u64 new_len;
static u64 counter = 0;

////////////////////////////////////////////////////////////////////////////////
// Initial FSM state of the actor
enum states {
	my_state_copy,
	my_state_initLength,
	my_state_padding
};

static char *stateNames[] = {
	"copy",
	"initLength",
	"padding"
};

static enum states _FSM_state;



////////////////////////////////////////////////////////////////////////////////
// Token functions
static void read_LENGTH() {
	index_LENGTH = check_MD5_padding_LENGTH->read_inds[0];
	numTokens_LENGTH = index_LENGTH + fifo_u64_get_num_tokens(check_MD5_padding_LENGTH, 0);
}

static void read_end_LENGTH() {
	check_MD5_padding_LENGTH->read_inds[0] = index_LENGTH;
}
static void read_DATA() {
	index_DATA = check_MD5_padding_DATA->read_inds[0];
	numTokens_DATA = index_DATA + fifo_u8_get_num_tokens(check_MD5_padding_DATA, 0);
}

static void read_end_DATA() {
	check_MD5_padding_DATA->read_inds[0] = index_DATA;
}

static void write_OUT() {
	index_OUT = check_MD5_padding_OUT->write_ind;
	numFree_OUT = index_OUT + fifo_u8_get_room(check_MD5_padding_OUT, NUM_READERS_OUT, SIZE_OUT);
}

static void write_end_OUT() {
	check_MD5_padding_OUT->write_ind = index_OUT;
}
static void write_NEWLENGTH() {
	index_NEWLENGTH = check_MD5_padding_NEWLENGTH->write_ind;
	numFree_NEWLENGTH = index_NEWLENGTH + fifo_u32_get_room(check_MD5_padding_NEWLENGTH, NUM_READERS_NEWLENGTH, SIZE_NEWLENGTH);
}

static void write_end_NEWLENGTH() {
	check_MD5_padding_NEWLENGTH->write_ind = index_NEWLENGTH;
}

////////////////////////////////////////////////////////////////////////////////
// Functions/procedures


////////////////////////////////////////////////////////////////////////////////
// Actions
static i32 isSchedulable_computeNewLength() {
	i32 result;

	result = 1;
	return result;
}

static void computeNewLength() {

	u64 len;
	u64 local_length;
	u64 local_new_len;

	len = tokens_LENGTH[(index_LENGTH + (0)) % SIZE_LENGTH];
	length = len;
	local_length = length;
	new_len = (local_length << 3) + 1;
	local_new_len = new_len;
	while ((local_new_len & 511) != 448) {
		local_new_len = new_len;
		new_len = local_new_len + 1;
		local_new_len = new_len;
	}
	local_new_len = new_len;
	new_len = local_new_len >> 3;
	local_new_len = new_len;
	tokens_NEWLENGTH[(index_NEWLENGTH + (0)) % SIZE_NEWLENGTH] = local_new_len;

	// Update ports indexes
	index_LENGTH += 1;
	index_NEWLENGTH += 1;

	rate_LENGTH += 1;
}
static i32 isSchedulable_copyData() {
	i32 result;

	result = 1;
	return result;
}

static void copyData() {

	u8 i;
	u64 local_counter;

	i = tokens_DATA[(index_DATA + (0)) % SIZE_DATA];
	local_counter = counter;
	counter = local_counter + 1;
	tokens_OUT[(index_OUT + (0)) % SIZE_OUT] = i;

	// Update ports indexes
	index_DATA += 1;
	index_OUT += 1;

	rate_DATA += 1;
}
static i32 isSchedulable_endCopy() {
	i32 result;
	u64 local_counter;
	u64 local_length;

	local_counter = counter;
	local_length = length;
	result = local_counter == local_length;
	return result;
}

static void endCopy() {


	counter = 0;
	tokens_OUT[(index_OUT + (0)) % SIZE_OUT] = 128;

	// Update ports indexes
	index_OUT += 1;

}
static i32 isSchedulable_zeroPadding() {
	i32 result;

	result = 1;
	return result;
}

static void zeroPadding() {

	u64 local_counter;

	local_counter = counter;
	counter = local_counter + 1;
	tokens_OUT[(index_OUT + (0)) % SIZE_OUT] = 0;

	// Update ports indexes
	index_OUT += 1;

}
static i32 isSchedulable_endZeroPadding() {
	i32 result;
	u64 local_counter;
	u64 local_new_len;
	u64 local_length;

	local_counter = counter;
	local_new_len = new_len;
	local_length = length;
	result = local_counter == local_new_len + 8 - (local_length + 9);
	return result;
}

static void endZeroPadding() {

	u64 local_length;
	u64 length_tmp;

	local_length = length;
	length_tmp = local_length << 3;
	counter = 0;
	tokens_OUT[(index_OUT + (7)) % SIZE_OUT] = length_tmp >> 56 & 255;
	tokens_OUT[(index_OUT + (6)) % SIZE_OUT] = length_tmp >> 48 & 255;
	tokens_OUT[(index_OUT + (5)) % SIZE_OUT] = length_tmp >> 40 & 255;
	tokens_OUT[(index_OUT + (4)) % SIZE_OUT] = length_tmp >> 32 & 255;
	tokens_OUT[(index_OUT + (3)) % SIZE_OUT] = length_tmp >> 24 & 255;
	tokens_OUT[(index_OUT + (2)) % SIZE_OUT] = length_tmp >> 16 & 255;
	tokens_OUT[(index_OUT + (1)) % SIZE_OUT] = length_tmp >> 8 & 255;
	tokens_OUT[(index_OUT + (0)) % SIZE_OUT] = length_tmp >> 0 & 255;

	// Update ports indexes
	index_OUT += 8;
	write_end_OUT();

}
static void endZeroPadding_aligned() {

	u64 local_length;
	u64 length_tmp;

	local_length = length;
	length_tmp = local_length << 3;
	counter = 0;
	tokens_OUT[(index_OUT % SIZE_OUT) + (7)] = length_tmp >> 56 & 255;
	tokens_OUT[(index_OUT % SIZE_OUT) + (6)] = length_tmp >> 48 & 255;
	tokens_OUT[(index_OUT % SIZE_OUT) + (5)] = length_tmp >> 40 & 255;
	tokens_OUT[(index_OUT % SIZE_OUT) + (4)] = length_tmp >> 32 & 255;
	tokens_OUT[(index_OUT % SIZE_OUT) + (3)] = length_tmp >> 24 & 255;
	tokens_OUT[(index_OUT % SIZE_OUT) + (2)] = length_tmp >> 16 & 255;
	tokens_OUT[(index_OUT % SIZE_OUT) + (1)] = length_tmp >> 8 & 255;
	tokens_OUT[(index_OUT % SIZE_OUT) + (0)] = length_tmp >> 0 & 255;

	// Update ports indexes
	index_OUT += 8;
	write_end_OUT();

}

////////////////////////////////////////////////////////////////////////////////
// Initializes

void check_MD5_padding_initialize(schedinfo_t *si) {
	int i = 0;
	write_OUT();
	write_NEWLENGTH();
	/* Set initial state to current FSM state */
	_FSM_state = my_state_initLength;
finished:
	write_end_OUT();
	write_end_NEWLENGTH();
	return;
}

////////////////////////////////////////////////////////////////////////////////
// Action scheduler

void check_MD5_padding_scheduler(schedinfo_t *si) {
	int i = 0;

	read_LENGTH();
	read_DATA();
	write_OUT();
	write_NEWLENGTH();

	// jump to FSM state
	switch (_FSM_state) {
	case my_state_copy:
		goto l_copy;
	case my_state_initLength:
		goto l_initLength;
	case my_state_padding:
		goto l_padding;
	default:
		printf("unknown state in check_MD5_padding.c : %s\n", stateNames[_FSM_state]);
		exit(1);
	}

	// FSM transitions
l_copy:
	if (isSchedulable_endCopy()) {
		int stop = 0;
		if (1 > SIZE_OUT - index_OUT + check_MD5_padding_OUT->read_inds[0]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_copy;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		endCopy();
		i++;
		goto l_padding;
	} else if (numTokens_DATA - index_DATA >= 1 && isSchedulable_copyData()) {
		int stop = 0;
		if (1 > SIZE_OUT - index_OUT + check_MD5_padding_OUT->read_inds[0]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_copy;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		copyData();
		i++;
		goto l_copy;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_copy;
		goto finished;
	}
l_initLength:
	if (numTokens_LENGTH - index_LENGTH >= 1 && isSchedulable_computeNewLength()) {
		int stop = 0;
		if (1 > SIZE_NEWLENGTH - index_NEWLENGTH + check_MD5_padding_NEWLENGTH->read_inds[0]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_initLength;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		computeNewLength();
		i++;
		goto l_copy;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_initLength;
		goto finished;
	}
l_padding:
	if (isSchedulable_endZeroPadding()) {
		int stop = 0;
		if (8 > SIZE_OUT - index_OUT + check_MD5_padding_OUT->read_inds[0]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_padding;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		{
			int isAligned = 1;
			isAligned &= ((index_OUT % SIZE_OUT) < ((index_OUT + 8) % SIZE_OUT));
			if (isAligned) {
				endZeroPadding_aligned();
			} else {
				endZeroPadding();
			}
		}
		i++;
		goto l_initLength;
	} else if (isSchedulable_zeroPadding()) {
		int stop = 0;
		if (1 > SIZE_OUT - index_OUT + check_MD5_padding_OUT->read_inds[0]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_padding;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		zeroPadding();
		i++;
		goto l_padding;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_padding;
		goto finished;
	}
finished:
	read_end_LENGTH();
	read_end_DATA();
	write_end_OUT();
	write_end_NEWLENGTH();
}
