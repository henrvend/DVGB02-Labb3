#include "node.h"

void rtinit(struct distance_table *table, int node)
{
    // Tables are already initialized
    printdt(table, node);
}

void rtupdate(struct distance_table *table, int node, struct rtpkt *pkt)
{
    printdt(table, node);
}

void tolayertwo(struct rtpkt packet)
{

    for (int i = 0; i < 4; i++)
    {
        if (i != packet.sourceid && is_neighbor(packet.sourceid, i))
        {
            packet.destid = i;

            tolayer2(packet);
        }
    }
}
