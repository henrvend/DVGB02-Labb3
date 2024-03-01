#include <stdio.h>

#include "sim_engine.h"
#include "node.h"

extern int TRACE;
extern int YES;
extern int NO;

struct distance_table dt0;

void rtinit0()
{
	for (int i = 0; i < 16; i++)
		dt0.costs[i % 4][i / 4] = 999;
	dt0.costs[0][0] = 0;
	dt0.costs[0][1] = 1;
	dt0.costs[0][2] = 3;
	dt0.costs[0][3] = 7;
	rtinit(&dt0, 0);

	struct rtpkt start_values;
	start_values.destid = 999;
	start_values.sourceid = 0;
	for (int i = 0; i < 4; i++)
	{
		start_values.mincost[i]=dt0.costs[0][i];
	}
	tolayertwo(start_values);
}

void rtupdate0(struct rtpkt *rcvdpkt)
{
	rtupdate(&dt0, 0, rcvdpkt);
}

void linkhandler0(int linkid, int newcost)
{
	/* DON'T CHANGE */
}
