// Source file is "L/RVC/src/org/sc29/wg11/mpegh/part2/common/MD5Compute.cal"

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
extern actor_t check_MD5_compute;

////////////////////////////////////////////////////////////////////////////////
// Input FIFOs
extern fifo_u32_t *check_MD5_compute_IN;
extern fifo_u32_t *check_MD5_compute_NEWLENGTH;
extern fifo_u8_t *check_MD5_compute_SEI_MD5;

////////////////////////////////////////////////////////////////////////////////
// Input Fifo control variables
static unsigned int index_IN;
static unsigned int numTokens_IN;
#define SIZE_IN SIZE
#define tokens_IN check_MD5_compute_IN->contents

extern connection_t connection_check_MD5_compute_IN;
#define rate_IN connection_check_MD5_compute_IN.rate

static unsigned int index_NEWLENGTH;
static unsigned int numTokens_NEWLENGTH;
#define SIZE_NEWLENGTH SIZE
#define tokens_NEWLENGTH check_MD5_compute_NEWLENGTH->contents

extern connection_t connection_check_MD5_compute_NEWLENGTH;
#define rate_NEWLENGTH connection_check_MD5_compute_NEWLENGTH.rate

static unsigned int index_SEI_MD5;
static unsigned int numTokens_SEI_MD5;
#define SIZE_SEI_MD5 SIZE
#define tokens_SEI_MD5 check_MD5_compute_SEI_MD5->contents

extern connection_t connection_check_MD5_compute_SEI_MD5;
#define rate_SEI_MD5 connection_check_MD5_compute_SEI_MD5.rate

////////////////////////////////////////////////////////////////////////////////
// Predecessors
extern actor_t check_MD5_shifter;
extern actor_t check_MD5_padding;
extern actor_t HevcDecoder_Algo_Parser;


////////////////////////////////////////////////////////////////////////////////
// State variables of the actor
static u32 refKey[4];
static u32 genKey[4];
static u32 newLength;
static u32 counter = 0;

////////////////////////////////////////////////////////////////////////////////
// Initial FSM state of the actor
enum states {
	my_state_compare,
	my_state_getLength,
	my_state_getRefKey,
	my_state_md5
};

static char *stateNames[] = {
	"compare",
	"getLength",
	"getRefKey",
	"md5"
};

static enum states _FSM_state;



////////////////////////////////////////////////////////////////////////////////
// Token functions
static void read_IN() {
	index_IN = check_MD5_compute_IN->read_inds[0];
	numTokens_IN = index_IN + fifo_u32_get_num_tokens(check_MD5_compute_IN, 0);
}

static void read_end_IN() {
	check_MD5_compute_IN->read_inds[0] = index_IN;
}
static void read_NEWLENGTH() {
	index_NEWLENGTH = check_MD5_compute_NEWLENGTH->read_inds[0];
	numTokens_NEWLENGTH = index_NEWLENGTH + fifo_u32_get_num_tokens(check_MD5_compute_NEWLENGTH, 0);
}

static void read_end_NEWLENGTH() {
	check_MD5_compute_NEWLENGTH->read_inds[0] = index_NEWLENGTH;
}
static void read_SEI_MD5() {
	index_SEI_MD5 = check_MD5_compute_SEI_MD5->read_inds[0];
	numTokens_SEI_MD5 = index_SEI_MD5 + fifo_u8_get_num_tokens(check_MD5_compute_SEI_MD5, 0);
}

static void read_end_SEI_MD5() {
	check_MD5_compute_SEI_MD5->read_inds[0] = index_SEI_MD5;
}


////////////////////////////////////////////////////////////////////////////////
// Functions/procedures
static u32 leftRotate(u32 x, u32 c);
static void hexDigitPrint(u8 digit);
static void hexPrint(u32 val);

static u32 leftRotate(u32 x, u32 c) {

	return x << c | x >> (32 - c);
}
static void hexDigitPrint(u8 digit) {

	if (digit == 0) {
		printf("0");
	} else {
		if (digit == 1) {
			printf("1");
		} else {
			if (digit == 2) {
				printf("2");
			} else {
				if (digit == 3) {
					printf("3");
				} else {
					if (digit == 4) {
						printf("4");
					} else {
						if (digit == 5) {
							printf("5");
						} else {
							if (digit == 6) {
								printf("6");
							} else {
								if (digit == 7) {
									printf("7");
								} else {
									if (digit == 8) {
										printf("8");
									} else {
										if (digit == 9) {
											printf("9");
										} else {
											if (digit == 10) {
												printf("a");
											} else {
												if (digit == 11) {
													printf("b");
												} else {
													if (digit == 12) {
														printf("c");
													} else {
														if (digit == 13) {
															printf("d");
														} else {
															if (digit == 14) {
																printf("e");
															} else {
																if (digit == 15) {
																	printf("f");
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
						}
					}
				}
			}
		}
	}
}
static void hexPrint(u32 val) {
	i8 i;

	i = 0;
	while (i <= 3) {
		hexDigitPrint(val >> (28 - (((3 - i) * 2) << 2)) & 15);
		hexDigitPrint(val >> (28 - (((3 - i) * 2 + 1) << 2)) & 15);
		i = i + 1;
	}
}

////////////////////////////////////////////////////////////////////////////////
// Actions
static i32 isSchedulable_getLength() {
	i32 result;

	result = 1;
	return result;
}

static void getLength() {

	u32 length;

	length = tokens_NEWLENGTH[(index_NEWLENGTH + (0)) % SIZE_NEWLENGTH];
	newLength = length + 8;
	genKey[0] = 1732584193;
	genKey[1] = 4023233417L;
	genKey[2] = 2562383102L;
	genKey[3] = 271733878;

	// Update ports indexes
	index_NEWLENGTH += 1;

	rate_NEWLENGTH += 1;
}
static i32 isSchedulable_getRef() {
	i32 result;

	result = 1;
	return result;
}

static void getRef_aligned() {

	u32 md5;
	i32 k;
	u8 tmp_SEI_MD5;
	u8 tmp_SEI_MD50;
	u8 tmp_SEI_MD51;
	u8 tmp_SEI_MD52;

	k = 0;
	while (k <= 3) {
		tmp_SEI_MD5 = tokens_SEI_MD5[(index_SEI_MD5 % SIZE_SEI_MD5) + (3 + 4 * k)];
		tmp_SEI_MD50 = tokens_SEI_MD5[(index_SEI_MD5 % SIZE_SEI_MD5) + (2 + 4 * k)];
		tmp_SEI_MD51 = tokens_SEI_MD5[(index_SEI_MD5 % SIZE_SEI_MD5) + (1 + 4 * k)];
		tmp_SEI_MD52 = tokens_SEI_MD5[(index_SEI_MD5 % SIZE_SEI_MD5) + (4 * k)];
		md5 = (tmp_SEI_MD5 << 24) + (tmp_SEI_MD50 << 16) + (tmp_SEI_MD51 << 8) + tmp_SEI_MD52;
		refKey[k] = md5;
		k = k + 1;
	}

	// Update ports indexes
	index_SEI_MD5 += 16;
	read_end_SEI_MD5();

	rate_SEI_MD5 += 16;
}
static i32 isSchedulable_getNoRef() {
	i32 result;

	result = 1;
	return result;
}

static void getNoRef() {



	// Update ports indexes

}
static i32 isSchedulable_compareKey() {
	i32 result;

	result = 1;
	return result;
}

static void compareKey() {

	i32 flag;
	i32 i;
	u32 tmp_refKey;
	u32 tmp_genKey;
	u32 tmp_genKey0;
	u32 tmp_genKey1;
	u32 tmp_genKey2;
	u32 tmp_genKey3;

	flag = 0;
	i = 0;
	while (i <= 3) {
		tmp_refKey = refKey[i];
		tmp_genKey = genKey[i];
		if (tmp_refKey != tmp_genKey) {
			flag = 1;
		}
		i = i + 1;
	}
	if (flag == 1) {
		printf("error md5 : ");
		tmp_genKey0 = genKey[0];
		hexPrint(tmp_genKey0);
		tmp_genKey1 = genKey[1];
		hexPrint(tmp_genKey1);
		tmp_genKey2 = genKey[2];
		hexPrint(tmp_genKey2);
		tmp_genKey3 = genKey[3];
		hexPrint(tmp_genKey3);
		printf("\n");
	}

	// Update ports indexes

}
static i32 isSchedulable_md5() {
	i32 result;

	result = 1;
	return result;
}

static void md5_aligned() {

	u32 a;
	u32 b;
	u32 c;
	u32 d;
	u32 i;
	u32 f;
	u32 g;
	u32 temp;
	u32 k[64];
	u8 r[64];
	u32 tmp_k;
	u32 tmp_IN;
	u8 tmp_r;
	u32 tmp_leftRotate;
	u32 tmp_genKey;
	u32 tmp_genKey0;
	u32 tmp_genKey1;
	u32 tmp_genKey2;
	u32 local_counter;

	a = genKey[0];
	b = genKey[1];
	c = genKey[2];
	d = genKey[3];
	i = 0;
	k[0] = 3614090360L;
	k[1] = 3905402710L;
	k[2] = 606105819;
	k[3] = 3250441966L;
	k[4] = 4118548399L;
	k[5] = 1200080426;
	k[6] = 2821735955L;
	k[7] = 4249261313L;
	k[8] = 1770035416;
	k[9] = 2336552879L;
	k[10] = 4294925233L;
	k[11] = 2304563134L;
	k[12] = 1804603682;
	k[13] = 4254626195L;
	k[14] = 2792965006L;
	k[15] = 1236535329;
	k[16] = 4129170786L;
	k[17] = 3225465664L;
	k[18] = 643717713;
	k[19] = 3921069994L;
	k[20] = 3593408605L;
	k[21] = 38016083;
	k[22] = 3634488961L;
	k[23] = 3889429448L;
	k[24] = 568446438;
	k[25] = 3275163606L;
	k[26] = 4107603335L;
	k[27] = 1163531501;
	k[28] = 2850285829L;
	k[29] = 4243563512L;
	k[30] = 1735328473;
	k[31] = 2368359562L;
	k[32] = 4294588738L;
	k[33] = 2272392833L;
	k[34] = 1839030562;
	k[35] = 4259657740L;
	k[36] = 2763975236L;
	k[37] = 1272893353;
	k[38] = 4139469664L;
	k[39] = 3200236656L;
	k[40] = 681279174;
	k[41] = 3936430074L;
	k[42] = 3572445317L;
	k[43] = 76029189;
	k[44] = 3654602809L;
	k[45] = 3873151461L;
	k[46] = 530742520;
	k[47] = 3299628645L;
	k[48] = 4096336452L;
	k[49] = 1126891415;
	k[50] = 2878612391L;
	k[51] = 4237533241L;
	k[52] = 1700485571;
	k[53] = 2399980690L;
	k[54] = 4293915773L;
	k[55] = 2240044497L;
	k[56] = 1873313359;
	k[57] = 4264355552L;
	k[58] = 2734768916L;
	k[59] = 1309151649;
	k[60] = 4149444226L;
	k[61] = 3174756917L;
	k[62] = 718787259;
	k[63] = 3951481745L;
	r[0] = 7;
	r[1] = 12;
	r[2] = 17;
	r[3] = 22;
	r[4] = 7;
	r[5] = 12;
	r[6] = 17;
	r[7] = 22;
	r[8] = 7;
	r[9] = 12;
	r[10] = 17;
	r[11] = 22;
	r[12] = 7;
	r[13] = 12;
	r[14] = 17;
	r[15] = 22;
	r[16] = 5;
	r[17] = 9;
	r[18] = 14;
	r[19] = 20;
	r[20] = 5;
	r[21] = 9;
	r[22] = 14;
	r[23] = 20;
	r[24] = 5;
	r[25] = 9;
	r[26] = 14;
	r[27] = 20;
	r[28] = 5;
	r[29] = 9;
	r[30] = 14;
	r[31] = 20;
	r[32] = 4;
	r[33] = 11;
	r[34] = 16;
	r[35] = 23;
	r[36] = 4;
	r[37] = 11;
	r[38] = 16;
	r[39] = 23;
	r[40] = 4;
	r[41] = 11;
	r[42] = 16;
	r[43] = 23;
	r[44] = 4;
	r[45] = 11;
	r[46] = 16;
	r[47] = 23;
	r[48] = 6;
	r[49] = 10;
	r[50] = 15;
	r[51] = 21;
	r[52] = 6;
	r[53] = 10;
	r[54] = 15;
	r[55] = 21;
	r[56] = 6;
	r[57] = 10;
	r[58] = 15;
	r[59] = 21;
	r[60] = 6;
	r[61] = 10;
	r[62] = 15;
	r[63] = 21;
	while (i < 64) {
		if (i < 16) {
			f = b & c | ~b & d;
			g = i;
		} else {
			if (i < 32) {
				f = d & b | ~d & c;
				g = 5 * i + 1 & 15;
			} else {
				if (i < 48) {
					f = b ^ c ^ d;
					g = 3 * i + 5 & 15;
				} else {
					f = c ^ (b | ~d);
					g = 7 * i & 15;
				}
			}
		}
		temp = d;
		d = c;
		c = b;
		tmp_k = k[i];
		tmp_IN = tokens_IN[(index_IN % SIZE_IN) + (g)];
		tmp_r = r[i];
		tmp_leftRotate = leftRotate(a + f + tmp_k + tmp_IN, tmp_r);
		b = b + tmp_leftRotate;
		a = temp;
		i = i + 1;
	}
	tmp_genKey = genKey[0];
	genKey[0] = tmp_genKey + a;
	tmp_genKey0 = genKey[1];
	genKey[1] = tmp_genKey0 + b;
	tmp_genKey1 = genKey[2];
	genKey[2] = tmp_genKey1 + c;
	tmp_genKey2 = genKey[3];
	genKey[3] = tmp_genKey2 + d;
	local_counter = counter;
	counter = local_counter + 64;

	// Update ports indexes
	index_IN += 16;
	read_end_IN();

	rate_IN += 16;
}
static i32 isSchedulable_md5_done() {
	i32 result;
	u32 local_counter;
	u32 local_newLength;

	local_counter = counter;
	local_newLength = newLength;
	result = local_counter == local_newLength;
	return result;
}

static void md5_done() {


	counter = 0;

	// Update ports indexes

}

////////////////////////////////////////////////////////////////////////////////
// Initializes

void check_MD5_compute_initialize(schedinfo_t *si) {
	int i = 0;
	/* Set initial state to current FSM state */
	_FSM_state = my_state_getLength;
finished:
	return;
}

////////////////////////////////////////////////////////////////////////////////
// Action scheduler

void check_MD5_compute_scheduler(schedinfo_t *si) {
	int i = 0;

	read_IN();
	read_NEWLENGTH();
	read_SEI_MD5();

	// jump to FSM state
	switch (_FSM_state) {
	case my_state_compare:
		goto l_compare;
	case my_state_getLength:
		goto l_getLength;
	case my_state_getRefKey:
		goto l_getRefKey;
	case my_state_md5:
		goto l_md5;
	default:
		printf("unknown state in check_MD5_compute.c : %s\n", stateNames[_FSM_state]);
		exit(1);
	}

	// FSM transitions
l_compare:
	if (isSchedulable_compareKey()) {
		compareKey();
		i++;
		goto l_getLength;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_compare;
		goto finished;
	}
l_getLength:
	if (numTokens_NEWLENGTH - index_NEWLENGTH >= 1 && isSchedulable_getLength()) {
		getLength();
		i++;
		goto l_md5;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_getLength;
		goto finished;
	}
l_getRefKey:
	if (numTokens_SEI_MD5 - index_SEI_MD5 >= 16 && isSchedulable_getRef()) {
		getRef_aligned();
		i++;
		goto l_compare;
	} else if (isSchedulable_getNoRef()) {
		getNoRef();
		i++;
		goto l_getLength;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_getRefKey;
		goto finished;
	}
l_md5:
	if (isSchedulable_md5_done()) {
		md5_done();
		i++;
		goto l_getRefKey;
	} else if (numTokens_IN - index_IN >= 16 && isSchedulable_md5()) {
		md5_aligned();
		i++;
		goto l_md5;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_md5;
		goto finished;
	}
finished:
	read_end_IN();
	read_end_NEWLENGTH();
	read_end_SEI_MD5();
}
