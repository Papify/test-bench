// Source file is "L/RVC/src/org/sc29/wg11/mpegh/part2/main/IT/IT16x16_1d.cal"

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
extern actor_t HevcDecoder_xIT_IT16x16_IT16x16_1d_0;

////////////////////////////////////////////////////////////////////////////////
// Input FIFOs
extern fifo_i16_t *HevcDecoder_xIT_IT16x16_IT16x16_1d_0_Src;

////////////////////////////////////////////////////////////////////////////////
// Input Fifo control variables
static unsigned int index_Src;
static unsigned int numTokens_Src;
#define SIZE_Src SIZE
#define tokens_Src HevcDecoder_xIT_IT16x16_IT16x16_1d_0_Src->contents

extern connection_t connection_HevcDecoder_xIT_IT16x16_IT16x16_1d_0_Src;
#define rate_Src connection_HevcDecoder_xIT_IT16x16_IT16x16_1d_0_Src.rate

////////////////////////////////////////////////////////////////////////////////
// Predecessors
extern actor_t HevcDecoder_xIT_IT16x16_Transpose16x16_0;

////////////////////////////////////////////////////////////////////////////////
// Output FIFOs
extern fifo_i16_t *HevcDecoder_xIT_IT16x16_IT16x16_1d_0_Dst;

////////////////////////////////////////////////////////////////////////////////
// Output Fifo control variables
static unsigned int index_Dst;
static unsigned int numFree_Dst;
#define NUM_READERS_Dst 1
#define SIZE_Dst SIZE
#define tokens_Dst HevcDecoder_xIT_IT16x16_IT16x16_1d_0_Dst->contents

////////////////////////////////////////////////////////////////////////////////
// Successors
extern actor_t HevcDecoder_xIT_IT16x16_Transpose16x16_1;

////////////////////////////////////////////////////////////////////////////////
// Parameter values of the instance
#define shift 7


////////////////////////////////////////////////////////////////////////////////
// State variables of the actor
static const i8 HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[16][16] = {{64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64}, {90, 87, 80, 70, 57, 43, 25, 9, -9, -25, -43, -57, -70, -80, -87, -90}, {89, 75, 50, 18, -18, -50, -75, -89, -89, -75, -50, -18, 18, 50, 75, 89}, {87, 57, 9, -43, -80, -90, -70, -25, 25, 70, 90, 80, 43, -9, -57, -87}, {83, 36, -36, -83, -83, -36, 36, 83, 83, 36, -36, -83, -83, -36, 36, 83}, {80, 9, -70, -87, -25, 57, 90, 43, -43, -90, -57, 25, 87, 70, -9, -80}, {75, -18, -89, -50, 50, 89, 18, -75, -75, 18, 89, 50, -50, -89, -18, 75}, {70, -43, -87, 9, 90, 25, -80, -57, 57, 80, -25, -90, -9, 87, 43, -70}, {64, -64, -64, 64, 64, -64, -64, 64, 64, -64, -64, 64, 64, -64, -64, 64}, {57, -80, -25, 90, -9, -87, 43, 70, -70, -43, 87, 9, -90, 25, 80, -57}, {50, -89, 18, 75, -75, -18, 89, -50, -50, 89, -18, -75, 75, 18, -89, 50}, {43, -90, 57, 25, -87, 70, 9, -80, 80, -9, -70, 87, -25, -57, 90, -43}, {36, -83, 83, -36, -36, 83, -83, 36, 36, -83, 83, -36, -36, 83, -83, 36}, {25, -70, 90, -80, 43, 9, -57, 87, -87, 57, -9, -43, 80, -90, 70, -25}, {18, -50, 75, -89, 89, -75, 50, -18, -18, 50, -75, 89, -89, 75, -50, 18}, {9, -25, 43, -57, 70, -80, 87, -90, 90, -87, 80, -70, 57, -43, 25, -9}};



////////////////////////////////////////////////////////////////////////////////
// Token functions
static void read_Src() {
	index_Src = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_Src->read_inds[0];
	numTokens_Src = index_Src + fifo_i16_get_num_tokens(HevcDecoder_xIT_IT16x16_IT16x16_1d_0_Src, 0);
}

static void read_end_Src() {
	HevcDecoder_xIT_IT16x16_IT16x16_1d_0_Src->read_inds[0] = index_Src;
}

static void write_Dst() {
	index_Dst = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_Dst->write_ind;
	numFree_Dst = index_Dst + fifo_i16_get_room(HevcDecoder_xIT_IT16x16_IT16x16_1d_0_Dst, NUM_READERS_Dst, SIZE_Dst);
}

static void write_end_Dst() {
	HevcDecoder_xIT_IT16x16_IT16x16_1d_0_Dst->write_ind = index_Dst;
}

////////////////////////////////////////////////////////////////////////////////
// Functions/procedures


////////////////////////////////////////////////////////////////////////////////
// Actions
static i32 isSchedulable_untagged_0() {
	i32 result;

	result = 1;
	return result;
}

static void untagged_0_aligned() {

	i32 evenEvenEven[2];
	i32 evenEvenOdd[2];
	i32 evenEven[4];
	i32 evenOdd[4];
	i32 even[8];
	i32 odd[8];
	i32 dst[16];
	i32 local_shift;
	i32 rouding_factor;
	i16 tmp_Src;
	i8 tmp_g_aiT16;
	i16 tmp_Src0;
	i8 tmp_g_aiT160;
	i16 tmp_Src1;
	i8 tmp_g_aiT161;
	i16 tmp_Src2;
	i8 tmp_g_aiT162;
	i16 tmp_Src3;
	i8 tmp_g_aiT163;
	i16 tmp_Src4;
	i8 tmp_g_aiT164;
	i16 tmp_Src5;
	i8 tmp_g_aiT165;
	i16 tmp_Src6;
	i8 tmp_g_aiT166;
	i32 tmp_evenEvenEven;
	i32 tmp_evenEvenOdd;
	i32 tmp_evenEvenEven0;
	i32 tmp_evenEvenOdd0;
	i32 tmp_evenEvenEven1;
	i32 tmp_evenEvenOdd1;
	i32 tmp_evenEvenEven2;
	i32 tmp_evenEvenOdd2;
	i16 tmp_Src7;
	i8 tmp_g_aiT167;
	i16 tmp_Src8;
	i8 tmp_g_aiT168;
	i16 tmp_Src9;
	i8 tmp_g_aiT169;
	i16 tmp_Src10;
	i8 tmp_g_aiT1610;
	i16 tmp_Src11;
	i8 tmp_g_aiT1611;
	i16 tmp_Src12;
	i8 tmp_g_aiT1612;
	i16 tmp_Src13;
	i8 tmp_g_aiT1613;
	i16 tmp_Src14;
	i8 tmp_g_aiT1614;
	i16 tmp_Src15;
	i8 tmp_g_aiT1615;
	i16 tmp_Src16;
	i8 tmp_g_aiT1616;
	i16 tmp_Src17;
	i8 tmp_g_aiT1617;
	i16 tmp_Src18;
	i8 tmp_g_aiT1618;
	i16 tmp_Src19;
	i8 tmp_g_aiT1619;
	i16 tmp_Src20;
	i8 tmp_g_aiT1620;
	i16 tmp_Src21;
	i8 tmp_g_aiT1621;
	i16 tmp_Src22;
	i8 tmp_g_aiT1622;
	i32 tmp_evenEven;
	i32 tmp_evenOdd;
	i32 tmp_evenEven0;
	i32 tmp_evenOdd0;
	i32 tmp_evenEven1;
	i32 tmp_evenOdd1;
	i32 tmp_evenEven2;
	i32 tmp_evenOdd2;
	i32 tmp_evenEven3;
	i32 tmp_evenOdd3;
	i32 tmp_evenEven4;
	i32 tmp_evenOdd4;
	i32 tmp_evenEven5;
	i32 tmp_evenOdd5;
	i32 tmp_evenEven6;
	i32 tmp_evenOdd6;
	i16 tmp_Src23;
	i8 tmp_g_aiT1623;
	i16 tmp_Src24;
	i8 tmp_g_aiT1624;
	i16 tmp_Src25;
	i8 tmp_g_aiT1625;
	i16 tmp_Src26;
	i8 tmp_g_aiT1626;
	i16 tmp_Src27;
	i8 tmp_g_aiT1627;
	i16 tmp_Src28;
	i8 tmp_g_aiT1628;
	i16 tmp_Src29;
	i8 tmp_g_aiT1629;
	i16 tmp_Src30;
	i8 tmp_g_aiT1630;
	i16 tmp_Src31;
	i8 tmp_g_aiT1631;
	i16 tmp_Src32;
	i8 tmp_g_aiT1632;
	i16 tmp_Src33;
	i8 tmp_g_aiT1633;
	i16 tmp_Src34;
	i8 tmp_g_aiT1634;
	i16 tmp_Src35;
	i8 tmp_g_aiT1635;
	i16 tmp_Src36;
	i8 tmp_g_aiT1636;
	i16 tmp_Src37;
	i8 tmp_g_aiT1637;
	i16 tmp_Src38;
	i8 tmp_g_aiT1638;
	i16 tmp_Src39;
	i8 tmp_g_aiT1639;
	i16 tmp_Src40;
	i8 tmp_g_aiT1640;
	i16 tmp_Src41;
	i8 tmp_g_aiT1641;
	i16 tmp_Src42;
	i8 tmp_g_aiT1642;
	i16 tmp_Src43;
	i8 tmp_g_aiT1643;
	i16 tmp_Src44;
	i8 tmp_g_aiT1644;
	i16 tmp_Src45;
	i8 tmp_g_aiT1645;
	i16 tmp_Src46;
	i8 tmp_g_aiT1646;
	i16 tmp_Src47;
	i8 tmp_g_aiT1647;
	i16 tmp_Src48;
	i8 tmp_g_aiT1648;
	i16 tmp_Src49;
	i8 tmp_g_aiT1649;
	i16 tmp_Src50;
	i8 tmp_g_aiT1650;
	i16 tmp_Src51;
	i8 tmp_g_aiT1651;
	i16 tmp_Src52;
	i8 tmp_g_aiT1652;
	i16 tmp_Src53;
	i8 tmp_g_aiT1653;
	i16 tmp_Src54;
	i8 tmp_g_aiT1654;
	i16 tmp_Src55;
	i8 tmp_g_aiT1655;
	i16 tmp_Src56;
	i8 tmp_g_aiT1656;
	i16 tmp_Src57;
	i8 tmp_g_aiT1657;
	i16 tmp_Src58;
	i8 tmp_g_aiT1658;
	i16 tmp_Src59;
	i8 tmp_g_aiT1659;
	i16 tmp_Src60;
	i8 tmp_g_aiT1660;
	i16 tmp_Src61;
	i8 tmp_g_aiT1661;
	i16 tmp_Src62;
	i8 tmp_g_aiT1662;
	i16 tmp_Src63;
	i8 tmp_g_aiT1663;
	i16 tmp_Src64;
	i8 tmp_g_aiT1664;
	i16 tmp_Src65;
	i8 tmp_g_aiT1665;
	i16 tmp_Src66;
	i8 tmp_g_aiT1666;
	i16 tmp_Src67;
	i8 tmp_g_aiT1667;
	i16 tmp_Src68;
	i8 tmp_g_aiT1668;
	i16 tmp_Src69;
	i8 tmp_g_aiT1669;
	i16 tmp_Src70;
	i8 tmp_g_aiT1670;
	i16 tmp_Src71;
	i8 tmp_g_aiT1671;
	i16 tmp_Src72;
	i8 tmp_g_aiT1672;
	i16 tmp_Src73;
	i8 tmp_g_aiT1673;
	i16 tmp_Src74;
	i8 tmp_g_aiT1674;
	i16 tmp_Src75;
	i8 tmp_g_aiT1675;
	i16 tmp_Src76;
	i8 tmp_g_aiT1676;
	i16 tmp_Src77;
	i8 tmp_g_aiT1677;
	i16 tmp_Src78;
	i8 tmp_g_aiT1678;
	i16 tmp_Src79;
	i8 tmp_g_aiT1679;
	i16 tmp_Src80;
	i8 tmp_g_aiT1680;
	i16 tmp_Src81;
	i8 tmp_g_aiT1681;
	i16 tmp_Src82;
	i8 tmp_g_aiT1682;
	i16 tmp_Src83;
	i8 tmp_g_aiT1683;
	i16 tmp_Src84;
	i8 tmp_g_aiT1684;
	i16 tmp_Src85;
	i8 tmp_g_aiT1685;
	i16 tmp_Src86;
	i8 tmp_g_aiT1686;
	i32 tmp_even;
	i32 tmp_odd;
	i32 tmp_even0;
	i32 tmp_odd0;
	i32 tmp_even1;
	i32 tmp_odd1;
	i32 tmp_even2;
	i32 tmp_odd2;
	i32 tmp_even3;
	i32 tmp_odd3;
	i32 tmp_even4;
	i32 tmp_odd4;
	i32 tmp_even5;
	i32 tmp_odd5;
	i32 tmp_even6;
	i32 tmp_odd6;
	i32 tmp_even7;
	i32 tmp_odd7;
	i32 tmp_even8;
	i32 tmp_odd8;
	i32 tmp_even9;
	i32 tmp_odd9;
	i32 tmp_even10;
	i32 tmp_odd10;
	i32 tmp_even11;
	i32 tmp_odd11;
	i32 tmp_even12;
	i32 tmp_odd12;
	i32 tmp_even13;
	i32 tmp_odd13;
	i32 tmp_even14;
	i32 tmp_odd14;
	i32 i;
	i32 tmp_dst;

	local_shift = shift;
	rouding_factor = 1 << (local_shift - 1);
	tmp_Src = tokens_Src[(index_Src % SIZE_Src) + (0)];
	tmp_g_aiT16 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[0][0];
	tmp_Src0 = tokens_Src[(index_Src % SIZE_Src) + (8)];
	tmp_g_aiT160 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[8][0];
	evenEvenEven[0] = tmp_Src * tmp_g_aiT16 + tmp_Src0 * tmp_g_aiT160;
	tmp_Src1 = tokens_Src[(index_Src % SIZE_Src) + (0)];
	tmp_g_aiT161 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[0][1];
	tmp_Src2 = tokens_Src[(index_Src % SIZE_Src) + (8)];
	tmp_g_aiT162 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[8][1];
	evenEvenEven[1] = tmp_Src1 * tmp_g_aiT161 + tmp_Src2 * tmp_g_aiT162;
	tmp_Src3 = tokens_Src[(index_Src % SIZE_Src) + (4)];
	tmp_g_aiT163 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[4][0];
	tmp_Src4 = tokens_Src[(index_Src % SIZE_Src) + (12)];
	tmp_g_aiT164 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[12][0];
	evenEvenOdd[0] = tmp_Src3 * tmp_g_aiT163 + tmp_Src4 * tmp_g_aiT164;
	tmp_Src5 = tokens_Src[(index_Src % SIZE_Src) + (4)];
	tmp_g_aiT165 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[4][1];
	tmp_Src6 = tokens_Src[(index_Src % SIZE_Src) + (12)];
	tmp_g_aiT166 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[12][1];
	evenEvenOdd[1] = tmp_Src5 * tmp_g_aiT165 + tmp_Src6 * tmp_g_aiT166;
	tmp_evenEvenEven = evenEvenEven[0];
	tmp_evenEvenOdd = evenEvenOdd[0];
	evenEven[0] = tmp_evenEvenEven + tmp_evenEvenOdd;
	tmp_evenEvenEven0 = evenEvenEven[1];
	tmp_evenEvenOdd0 = evenEvenOdd[1];
	evenEven[1] = tmp_evenEvenEven0 + tmp_evenEvenOdd0;
	tmp_evenEvenEven1 = evenEvenEven[1];
	tmp_evenEvenOdd1 = evenEvenOdd[1];
	evenEven[2] = tmp_evenEvenEven1 - tmp_evenEvenOdd1;
	tmp_evenEvenEven2 = evenEvenEven[0];
	tmp_evenEvenOdd2 = evenEvenOdd[0];
	evenEven[3] = tmp_evenEvenEven2 - tmp_evenEvenOdd2;
	tmp_Src7 = tokens_Src[(index_Src % SIZE_Src) + (2)];
	tmp_g_aiT167 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[2][0];
	tmp_Src8 = tokens_Src[(index_Src % SIZE_Src) + (6)];
	tmp_g_aiT168 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[6][0];
	tmp_Src9 = tokens_Src[(index_Src % SIZE_Src) + (10)];
	tmp_g_aiT169 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[10][0];
	tmp_Src10 = tokens_Src[(index_Src % SIZE_Src) + (14)];
	tmp_g_aiT1610 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[14][0];
	evenOdd[0] = tmp_Src7 * tmp_g_aiT167 + tmp_Src8 * tmp_g_aiT168 + tmp_Src9 * tmp_g_aiT169 + tmp_Src10 * tmp_g_aiT1610;
	tmp_Src11 = tokens_Src[(index_Src % SIZE_Src) + (2)];
	tmp_g_aiT1611 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[2][1];
	tmp_Src12 = tokens_Src[(index_Src % SIZE_Src) + (6)];
	tmp_g_aiT1612 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[6][1];
	tmp_Src13 = tokens_Src[(index_Src % SIZE_Src) + (10)];
	tmp_g_aiT1613 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[10][1];
	tmp_Src14 = tokens_Src[(index_Src % SIZE_Src) + (14)];
	tmp_g_aiT1614 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[14][1];
	evenOdd[1] = tmp_Src11 * tmp_g_aiT1611 + tmp_Src12 * tmp_g_aiT1612 + tmp_Src13 * tmp_g_aiT1613 + tmp_Src14 * tmp_g_aiT1614;
	tmp_Src15 = tokens_Src[(index_Src % SIZE_Src) + (2)];
	tmp_g_aiT1615 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[2][2];
	tmp_Src16 = tokens_Src[(index_Src % SIZE_Src) + (6)];
	tmp_g_aiT1616 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[6][2];
	tmp_Src17 = tokens_Src[(index_Src % SIZE_Src) + (10)];
	tmp_g_aiT1617 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[10][2];
	tmp_Src18 = tokens_Src[(index_Src % SIZE_Src) + (14)];
	tmp_g_aiT1618 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[14][2];
	evenOdd[2] = tmp_Src15 * tmp_g_aiT1615 + tmp_Src16 * tmp_g_aiT1616 + tmp_Src17 * tmp_g_aiT1617 + tmp_Src18 * tmp_g_aiT1618;
	tmp_Src19 = tokens_Src[(index_Src % SIZE_Src) + (2)];
	tmp_g_aiT1619 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[2][3];
	tmp_Src20 = tokens_Src[(index_Src % SIZE_Src) + (6)];
	tmp_g_aiT1620 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[6][3];
	tmp_Src21 = tokens_Src[(index_Src % SIZE_Src) + (10)];
	tmp_g_aiT1621 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[10][3];
	tmp_Src22 = tokens_Src[(index_Src % SIZE_Src) + (14)];
	tmp_g_aiT1622 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[14][3];
	evenOdd[3] = tmp_Src19 * tmp_g_aiT1619 + tmp_Src20 * tmp_g_aiT1620 + tmp_Src21 * tmp_g_aiT1621 + tmp_Src22 * tmp_g_aiT1622;
	tmp_evenEven = evenEven[0];
	tmp_evenOdd = evenOdd[0];
	even[0] = tmp_evenEven + tmp_evenOdd;
	tmp_evenEven0 = evenEven[1];
	tmp_evenOdd0 = evenOdd[1];
	even[1] = tmp_evenEven0 + tmp_evenOdd0;
	tmp_evenEven1 = evenEven[2];
	tmp_evenOdd1 = evenOdd[2];
	even[2] = tmp_evenEven1 + tmp_evenOdd1;
	tmp_evenEven2 = evenEven[3];
	tmp_evenOdd2 = evenOdd[3];
	even[3] = tmp_evenEven2 + tmp_evenOdd2;
	tmp_evenEven3 = evenEven[3];
	tmp_evenOdd3 = evenOdd[3];
	even[4] = tmp_evenEven3 - tmp_evenOdd3;
	tmp_evenEven4 = evenEven[2];
	tmp_evenOdd4 = evenOdd[2];
	even[5] = tmp_evenEven4 - tmp_evenOdd4;
	tmp_evenEven5 = evenEven[1];
	tmp_evenOdd5 = evenOdd[1];
	even[6] = tmp_evenEven5 - tmp_evenOdd5;
	tmp_evenEven6 = evenEven[0];
	tmp_evenOdd6 = evenOdd[0];
	even[7] = tmp_evenEven6 - tmp_evenOdd6;
	tmp_Src23 = tokens_Src[(index_Src % SIZE_Src) + (1)];
	tmp_g_aiT1623 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[1][0];
	tmp_Src24 = tokens_Src[(index_Src % SIZE_Src) + (3)];
	tmp_g_aiT1624 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[3][0];
	tmp_Src25 = tokens_Src[(index_Src % SIZE_Src) + (5)];
	tmp_g_aiT1625 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[5][0];
	tmp_Src26 = tokens_Src[(index_Src % SIZE_Src) + (7)];
	tmp_g_aiT1626 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[7][0];
	tmp_Src27 = tokens_Src[(index_Src % SIZE_Src) + (9)];
	tmp_g_aiT1627 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[9][0];
	tmp_Src28 = tokens_Src[(index_Src % SIZE_Src) + (11)];
	tmp_g_aiT1628 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[11][0];
	tmp_Src29 = tokens_Src[(index_Src % SIZE_Src) + (13)];
	tmp_g_aiT1629 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[13][0];
	tmp_Src30 = tokens_Src[(index_Src % SIZE_Src) + (15)];
	tmp_g_aiT1630 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[15][0];
	odd[0] = tmp_Src23 * tmp_g_aiT1623 + tmp_Src24 * tmp_g_aiT1624 + tmp_Src25 * tmp_g_aiT1625 + tmp_Src26 * tmp_g_aiT1626 + tmp_Src27 * tmp_g_aiT1627 + tmp_Src28 * tmp_g_aiT1628 + tmp_Src29 * tmp_g_aiT1629 + tmp_Src30 * tmp_g_aiT1630;
	tmp_Src31 = tokens_Src[(index_Src % SIZE_Src) + (1)];
	tmp_g_aiT1631 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[1][1];
	tmp_Src32 = tokens_Src[(index_Src % SIZE_Src) + (3)];
	tmp_g_aiT1632 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[3][1];
	tmp_Src33 = tokens_Src[(index_Src % SIZE_Src) + (5)];
	tmp_g_aiT1633 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[5][1];
	tmp_Src34 = tokens_Src[(index_Src % SIZE_Src) + (7)];
	tmp_g_aiT1634 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[7][1];
	tmp_Src35 = tokens_Src[(index_Src % SIZE_Src) + (9)];
	tmp_g_aiT1635 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[9][1];
	tmp_Src36 = tokens_Src[(index_Src % SIZE_Src) + (11)];
	tmp_g_aiT1636 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[11][1];
	tmp_Src37 = tokens_Src[(index_Src % SIZE_Src) + (13)];
	tmp_g_aiT1637 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[13][1];
	tmp_Src38 = tokens_Src[(index_Src % SIZE_Src) + (15)];
	tmp_g_aiT1638 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[15][1];
	odd[1] = tmp_Src31 * tmp_g_aiT1631 + tmp_Src32 * tmp_g_aiT1632 + tmp_Src33 * tmp_g_aiT1633 + tmp_Src34 * tmp_g_aiT1634 + tmp_Src35 * tmp_g_aiT1635 + tmp_Src36 * tmp_g_aiT1636 + tmp_Src37 * tmp_g_aiT1637 + tmp_Src38 * tmp_g_aiT1638;
	tmp_Src39 = tokens_Src[(index_Src % SIZE_Src) + (1)];
	tmp_g_aiT1639 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[1][2];
	tmp_Src40 = tokens_Src[(index_Src % SIZE_Src) + (3)];
	tmp_g_aiT1640 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[3][2];
	tmp_Src41 = tokens_Src[(index_Src % SIZE_Src) + (5)];
	tmp_g_aiT1641 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[5][2];
	tmp_Src42 = tokens_Src[(index_Src % SIZE_Src) + (7)];
	tmp_g_aiT1642 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[7][2];
	tmp_Src43 = tokens_Src[(index_Src % SIZE_Src) + (9)];
	tmp_g_aiT1643 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[9][2];
	tmp_Src44 = tokens_Src[(index_Src % SIZE_Src) + (11)];
	tmp_g_aiT1644 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[11][2];
	tmp_Src45 = tokens_Src[(index_Src % SIZE_Src) + (13)];
	tmp_g_aiT1645 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[13][2];
	tmp_Src46 = tokens_Src[(index_Src % SIZE_Src) + (15)];
	tmp_g_aiT1646 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[15][2];
	odd[2] = tmp_Src39 * tmp_g_aiT1639 + tmp_Src40 * tmp_g_aiT1640 + tmp_Src41 * tmp_g_aiT1641 + tmp_Src42 * tmp_g_aiT1642 + tmp_Src43 * tmp_g_aiT1643 + tmp_Src44 * tmp_g_aiT1644 + tmp_Src45 * tmp_g_aiT1645 + tmp_Src46 * tmp_g_aiT1646;
	tmp_Src47 = tokens_Src[(index_Src % SIZE_Src) + (1)];
	tmp_g_aiT1647 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[1][3];
	tmp_Src48 = tokens_Src[(index_Src % SIZE_Src) + (3)];
	tmp_g_aiT1648 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[3][3];
	tmp_Src49 = tokens_Src[(index_Src % SIZE_Src) + (5)];
	tmp_g_aiT1649 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[5][3];
	tmp_Src50 = tokens_Src[(index_Src % SIZE_Src) + (7)];
	tmp_g_aiT1650 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[7][3];
	tmp_Src51 = tokens_Src[(index_Src % SIZE_Src) + (9)];
	tmp_g_aiT1651 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[9][3];
	tmp_Src52 = tokens_Src[(index_Src % SIZE_Src) + (11)];
	tmp_g_aiT1652 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[11][3];
	tmp_Src53 = tokens_Src[(index_Src % SIZE_Src) + (13)];
	tmp_g_aiT1653 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[13][3];
	tmp_Src54 = tokens_Src[(index_Src % SIZE_Src) + (15)];
	tmp_g_aiT1654 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[15][3];
	odd[3] = tmp_Src47 * tmp_g_aiT1647 + tmp_Src48 * tmp_g_aiT1648 + tmp_Src49 * tmp_g_aiT1649 + tmp_Src50 * tmp_g_aiT1650 + tmp_Src51 * tmp_g_aiT1651 + tmp_Src52 * tmp_g_aiT1652 + tmp_Src53 * tmp_g_aiT1653 + tmp_Src54 * tmp_g_aiT1654;
	tmp_Src55 = tokens_Src[(index_Src % SIZE_Src) + (1)];
	tmp_g_aiT1655 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[1][4];
	tmp_Src56 = tokens_Src[(index_Src % SIZE_Src) + (3)];
	tmp_g_aiT1656 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[3][4];
	tmp_Src57 = tokens_Src[(index_Src % SIZE_Src) + (5)];
	tmp_g_aiT1657 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[5][4];
	tmp_Src58 = tokens_Src[(index_Src % SIZE_Src) + (7)];
	tmp_g_aiT1658 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[7][4];
	tmp_Src59 = tokens_Src[(index_Src % SIZE_Src) + (9)];
	tmp_g_aiT1659 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[9][4];
	tmp_Src60 = tokens_Src[(index_Src % SIZE_Src) + (11)];
	tmp_g_aiT1660 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[11][4];
	tmp_Src61 = tokens_Src[(index_Src % SIZE_Src) + (13)];
	tmp_g_aiT1661 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[13][4];
	tmp_Src62 = tokens_Src[(index_Src % SIZE_Src) + (15)];
	tmp_g_aiT1662 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[15][4];
	odd[4] = tmp_Src55 * tmp_g_aiT1655 + tmp_Src56 * tmp_g_aiT1656 + tmp_Src57 * tmp_g_aiT1657 + tmp_Src58 * tmp_g_aiT1658 + tmp_Src59 * tmp_g_aiT1659 + tmp_Src60 * tmp_g_aiT1660 + tmp_Src61 * tmp_g_aiT1661 + tmp_Src62 * tmp_g_aiT1662;
	tmp_Src63 = tokens_Src[(index_Src % SIZE_Src) + (1)];
	tmp_g_aiT1663 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[1][5];
	tmp_Src64 = tokens_Src[(index_Src % SIZE_Src) + (3)];
	tmp_g_aiT1664 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[3][5];
	tmp_Src65 = tokens_Src[(index_Src % SIZE_Src) + (5)];
	tmp_g_aiT1665 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[5][5];
	tmp_Src66 = tokens_Src[(index_Src % SIZE_Src) + (7)];
	tmp_g_aiT1666 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[7][5];
	tmp_Src67 = tokens_Src[(index_Src % SIZE_Src) + (9)];
	tmp_g_aiT1667 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[9][5];
	tmp_Src68 = tokens_Src[(index_Src % SIZE_Src) + (11)];
	tmp_g_aiT1668 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[11][5];
	tmp_Src69 = tokens_Src[(index_Src % SIZE_Src) + (13)];
	tmp_g_aiT1669 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[13][5];
	tmp_Src70 = tokens_Src[(index_Src % SIZE_Src) + (15)];
	tmp_g_aiT1670 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[15][5];
	odd[5] = tmp_Src63 * tmp_g_aiT1663 + tmp_Src64 * tmp_g_aiT1664 + tmp_Src65 * tmp_g_aiT1665 + tmp_Src66 * tmp_g_aiT1666 + tmp_Src67 * tmp_g_aiT1667 + tmp_Src68 * tmp_g_aiT1668 + tmp_Src69 * tmp_g_aiT1669 + tmp_Src70 * tmp_g_aiT1670;
	tmp_Src71 = tokens_Src[(index_Src % SIZE_Src) + (1)];
	tmp_g_aiT1671 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[1][6];
	tmp_Src72 = tokens_Src[(index_Src % SIZE_Src) + (3)];
	tmp_g_aiT1672 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[3][6];
	tmp_Src73 = tokens_Src[(index_Src % SIZE_Src) + (5)];
	tmp_g_aiT1673 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[5][6];
	tmp_Src74 = tokens_Src[(index_Src % SIZE_Src) + (7)];
	tmp_g_aiT1674 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[7][6];
	tmp_Src75 = tokens_Src[(index_Src % SIZE_Src) + (9)];
	tmp_g_aiT1675 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[9][6];
	tmp_Src76 = tokens_Src[(index_Src % SIZE_Src) + (11)];
	tmp_g_aiT1676 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[11][6];
	tmp_Src77 = tokens_Src[(index_Src % SIZE_Src) + (13)];
	tmp_g_aiT1677 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[13][6];
	tmp_Src78 = tokens_Src[(index_Src % SIZE_Src) + (15)];
	tmp_g_aiT1678 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[15][6];
	odd[6] = tmp_Src71 * tmp_g_aiT1671 + tmp_Src72 * tmp_g_aiT1672 + tmp_Src73 * tmp_g_aiT1673 + tmp_Src74 * tmp_g_aiT1674 + tmp_Src75 * tmp_g_aiT1675 + tmp_Src76 * tmp_g_aiT1676 + tmp_Src77 * tmp_g_aiT1677 + tmp_Src78 * tmp_g_aiT1678;
	tmp_Src79 = tokens_Src[(index_Src % SIZE_Src) + (1)];
	tmp_g_aiT1679 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[1][7];
	tmp_Src80 = tokens_Src[(index_Src % SIZE_Src) + (3)];
	tmp_g_aiT1680 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[3][7];
	tmp_Src81 = tokens_Src[(index_Src % SIZE_Src) + (5)];
	tmp_g_aiT1681 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[5][7];
	tmp_Src82 = tokens_Src[(index_Src % SIZE_Src) + (7)];
	tmp_g_aiT1682 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[7][7];
	tmp_Src83 = tokens_Src[(index_Src % SIZE_Src) + (9)];
	tmp_g_aiT1683 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[9][7];
	tmp_Src84 = tokens_Src[(index_Src % SIZE_Src) + (11)];
	tmp_g_aiT1684 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[11][7];
	tmp_Src85 = tokens_Src[(index_Src % SIZE_Src) + (13)];
	tmp_g_aiT1685 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[13][7];
	tmp_Src86 = tokens_Src[(index_Src % SIZE_Src) + (15)];
	tmp_g_aiT1686 = HevcDecoder_xIT_IT16x16_IT16x16_1d_0_g_aiT16[15][7];
	odd[7] = tmp_Src79 * tmp_g_aiT1679 + tmp_Src80 * tmp_g_aiT1680 + tmp_Src81 * tmp_g_aiT1681 + tmp_Src82 * tmp_g_aiT1682 + tmp_Src83 * tmp_g_aiT1683 + tmp_Src84 * tmp_g_aiT1684 + tmp_Src85 * tmp_g_aiT1685 + tmp_Src86 * tmp_g_aiT1686;
	tmp_even = even[0];
	tmp_odd = odd[0];
	dst[0] = tmp_even + tmp_odd;
	tmp_even0 = even[1];
	tmp_odd0 = odd[1];
	dst[1] = tmp_even0 + tmp_odd0;
	tmp_even1 = even[2];
	tmp_odd1 = odd[2];
	dst[2] = tmp_even1 + tmp_odd1;
	tmp_even2 = even[3];
	tmp_odd2 = odd[3];
	dst[3] = tmp_even2 + tmp_odd2;
	tmp_even3 = even[4];
	tmp_odd3 = odd[4];
	dst[4] = tmp_even3 + tmp_odd3;
	tmp_even4 = even[5];
	tmp_odd4 = odd[5];
	dst[5] = tmp_even4 + tmp_odd4;
	tmp_even5 = even[6];
	tmp_odd5 = odd[6];
	dst[6] = tmp_even5 + tmp_odd5;
	tmp_even6 = even[7];
	tmp_odd6 = odd[7];
	dst[7] = tmp_even6 + tmp_odd6;
	tmp_even7 = even[7];
	tmp_odd7 = odd[7];
	dst[8] = tmp_even7 - tmp_odd7;
	tmp_even8 = even[6];
	tmp_odd8 = odd[6];
	dst[9] = tmp_even8 - tmp_odd8;
	tmp_even9 = even[5];
	tmp_odd9 = odd[5];
	dst[10] = tmp_even9 - tmp_odd9;
	tmp_even10 = even[4];
	tmp_odd10 = odd[4];
	dst[11] = tmp_even10 - tmp_odd10;
	tmp_even11 = even[3];
	tmp_odd11 = odd[3];
	dst[12] = tmp_even11 - tmp_odd11;
	tmp_even12 = even[2];
	tmp_odd12 = odd[2];
	dst[13] = tmp_even12 - tmp_odd12;
	tmp_even13 = even[1];
	tmp_odd13 = odd[1];
	dst[14] = tmp_even13 - tmp_odd13;
	tmp_even14 = even[0];
	tmp_odd14 = odd[0];
	dst[15] = tmp_even14 - tmp_odd14;
	i = 0;
	while (i <= 15) {
		tmp_dst = dst[i];
		local_shift = shift;
		tokens_Dst[(index_Dst % SIZE_Dst) + (i)] = (tmp_dst + rouding_factor) >> local_shift;
		i = i + 1;
	}

	// Update ports indexes
	index_Src += 16;
	read_end_Src();
	index_Dst += 16;
	write_end_Dst();

	rate_Src += 16;
}

////////////////////////////////////////////////////////////////////////////////
// Initializes

void HevcDecoder_xIT_IT16x16_IT16x16_1d_0_initialize(schedinfo_t *si) {
	int i = 0;
	write_Dst();
finished:
	write_end_Dst();
	return;
}

////////////////////////////////////////////////////////////////////////////////
// Action scheduler
void HevcDecoder_xIT_IT16x16_IT16x16_1d_0_scheduler(schedinfo_t *si) {
	int i = 0;
	si->ports = 0;

	read_Src();
	write_Dst();

	while (1) {
		if (numTokens_Src - index_Src >= 16 && isSchedulable_untagged_0()) {
			int stop = 0;
			if (16 > SIZE_Dst - index_Dst + HevcDecoder_xIT_IT16x16_IT16x16_1d_0_Dst->read_inds[0]) {
				stop = 1;
			}
			if (stop != 0) {
				si->num_firings = i;
				si->reason = full;
				goto finished;
			}
			untagged_0_aligned();
			i++;
		} else {
			si->num_firings = i;
			si->reason = starved;
			goto finished;
		}
	}

finished:

	read_end_Src();
	write_end_Dst();
}
