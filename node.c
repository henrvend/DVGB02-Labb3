#include "node.h"

void rtinit(struct distance_table *table, int node)
{
    // Tables are already initialized
    printdt(table, node);

    struct rtpkt pkt;
    pkt.sourceid = node;

    for (int i = 0; i < 4; i++)
    {
        if (is_neighbor(node, i))
        {
            pkt.destid = i;
            pkt.mincost[i] = table->costs[node][i];
            tolayer2(pkt);
        }
    }

    // rtupdate(table, node, &pkt);
}

void rtupdate(struct distance_table *table, int node, struct rtpkt *pkt)
{

    bool changed = false;

    for (int i = 0; i < sizeof(pkt->mincost)/sizeof(pkt->mincost[0]); i++)
    {
        if ((pkt->mincost[i] + table->costs[i][node] < table->costs[node][i])/*&& i!=node*/)
        {
            table->costs[node][i] = pkt->mincost[i] + table->costs[i][node];
            changed = true;
        }
    }

    if (changed)
    {
        struct rtpkt update_pkt;
        update_pkt.sourceid = node;
        for (int i = 0; i < 4; i++)
        {           
                update_pkt.destid = i;
                update_pkt.mincost[i] = table->costs[node][i];
                
        }tolayer2(update_pkt);
    }
    printdt(table, node);
}
