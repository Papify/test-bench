// Source file is "L/RVC/src/org/sc29/wg11/mpegh/part2/common/MD5Shifter.cal"

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
extern actor_t check_MD5_shifter;

////////////////////////////////////////////////////////////////////////////////
// Input FIFOs
extern fifo_u8_t *check_MD5_shifter_IN;

////////////////////////////////////////////////////////////////////////////////
// Input Fifo control variables
static unsigned int index_IN;
static unsigned int numTokens_IN;
#define SIZE_IN SIZE
#define tokens_IN check_MD5_shifter_IN->contents

extern connection_t connection_check_MD5_shifter_IN;
#define rate_IN connection_check_MD5_shifter_IN.rate

////////////////////////////////////////////////////////////////////////////////
// Predecessors
extern actor_t check_MD5_padding;

////////////////////////////////////////////////////////////////////////////////
// Output FIFOs
extern fifo_u32_t *check_MD5_shifter_OUT;

////////////////////////////////////////////////////////////////////////////////
// Output Fifo control variables
static unsigned int index_OUT;
static unsigned int numFree_OUT;
#define NUM_READERS_OUT 1
#define SIZE_OUT SIZE
#define tokens_OUT check_MD5_shifter_OUT->contents

////////////////////////////////////////////////////////////////////////////////
// Successors
extern actor_t check_MD5_compute;




////////////////////////////////////////////////////////////////////////////////
// Token functions
static void read_IN() {
	index_IN = check_MD5_shifter_IN->read_inds[0];
	numTokens_IN = index_IN + fifo_u8_get_num_tokens(check_MD5_shifter_IN, 0);
}

static void read_end_IN() {
	check_MD5_shifter_IN->read_inds[0] = index_IN;
}

static void write_OUT() {
	index_OUT = check_MD5_shifter_OUT->write_ind;
	numFree_OUT = index_OUT + fifo_u32_get_room(check_MD5_shifter_OUT, NUM_READERS_OUT, SIZE_OUT);
}

static void write_end_OUT() {
	check_MD5_shifter_OUT->write_ind = index_OUT;
}

////////////////////////////////////////////////////////////////////////////////
// Functions/procedures


////////////////////////////////////////////////////////////////////////////////
// Actions
static i32 isSchedulable_shiftAction() {
	i32 result;

	result = 1;
	return result;
}

static void shiftAction() {

	u8 tmp_IN;
	u8 tmp_IN0;
	u8 tmp_IN1;
	u8 tmp_IN2;
	u32 DataOut;

	tmp_IN = tokens_IN[(index_IN % SIZE_IN) + (3)];
	tmp_IN0 = tokens_IN[(index_IN % SIZE_IN) + (2)];
	tmp_IN1 = tokens_IN[(index_IN % SIZE_IN) + (1)];
	tmp_IN2 = tokens_IN[(index_IN % SIZE_IN) + (0)];
	DataOut = (tmp_IN << 24) + (tmp_IN0 << 16) + (tmp_IN1 << 8) + tmp_IN2;
	tokens_OUT[(index_OUT + (0)) % SIZE_OUT] = DataOut;

	// Update ports indexes
	index_IN += 4;
	read_end_IN();
	index_OUT += 1;

	rate_IN += 4;
}
static void shiftAction_aligned() {

	u8 tmp_IN;
	u8 tmp_IN0;
	u8 tmp_IN1;
	u8 tmp_IN2;
	u32 DataOut;

	tmp_IN = tokens_IN[(index_IN % SIZE_IN) + (3)];
	tmp_IN0 = tokens_IN[(index_IN % SIZE_IN) + (2)];
	tmp_IN1 = tokens_IN[(index_IN % SIZE_IN) + (1)];
	tmp_IN2 = tokens_IN[(index_IN % SIZE_IN) + (0)];
	DataOut = (tmp_IN << 24) + (tmp_IN0 << 16) + (tmp_IN1 << 8) + tmp_IN2;
	tokens_OUT[(index_OUT + (0)) % SIZE_OUT] = DataOut;

	// Update ports indexes
	index_IN += 4;
	read_end_IN();
	index_OUT += 1;

	rate_IN += 4;
}

////////////////////////////////////////////////////////////////////////////////
// Initializes

void check_MD5_shifter_initialize(schedinfo_t *si) {
	int i = 0;
	write_OUT();
finished:
	write_end_OUT();
	return;
}

////////////////////////////////////////////////////////////////////////////////
// Action scheduler
void check_MD5_shifter_scheduler(schedinfo_t *si) {
	int i = 0;
	si->ports = 0;

	read_IN();
	write_OUT();

	while (1) {
		if (numTokens_IN - index_IN >= 4 && isSchedulable_shiftAction()) {
			int stop = 0;
			if (1 > SIZE_OUT - index_OUT + check_MD5_shifter_OUT->read_inds[0]) {
				stop = 1;
			}
			if (stop != 0) {
				si->num_firings = i;
				si->reason = full;
				goto finished;
			}
			{
				int isAligned = 1;
				if (isAligned) {
					shiftAction_aligned();
				} else {
					shiftAction();
				}
			}
			i++;
		} else {
			si->num_firings = i;
			si->reason = starved;
			goto finished;
		}
	}

finished:

	read_end_IN();
	write_end_OUT();
}
