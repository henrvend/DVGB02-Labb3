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
            for (int j = 0; j < 4; j++)
            {
                pkt.mincost[j] = table->costs[node][j];
            }

            tolayer2(pkt);
        }
    }
}

void rtupdate(struct distance_table *table, int node, struct rtpkt *pkt)
{

    bool changed = false;
    int mincost;
    for (int i = 0; i < 4; i++)
    {
        if (is_neighbor(pkt->sourceid, i))
        {
            if ((pkt->mincost[i] + table->costs[node][pkt->sourceid] < table->costs[node][i]))
            {
                table->costs[node][i] = pkt->mincost[i] + table->costs[node][pkt->sourceid];
                changed = true;
            }
        }
    }

    if (changed)
    {
        struct rtpkt update_pkt;
        update_pkt.sourceid = node;
        for (int i = 0; i < 4; i++)
        {
            if (is_neighbor(node, i))
            {
                update_pkt.destid = i;
                for (int j = 0; j < 4; j++)
                {
                    update_pkt.mincost[j] = table->costs[node][j];
                }

                tolayer2(update_pkt);
            }
        }
        printdt(table, node);
    }
}
