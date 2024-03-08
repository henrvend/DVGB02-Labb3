#include "node.h"

void rtinit(struct distance_table *table, int node)
{
    // Tables are already initialized
    printdt(table, node);

    for (int i = 0; i < 4; i++)
    {
        if (is_neighbor(node, i))
        {
            struct rtpkt pkt;
            pkt.sourceid = node;
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

    for (int i = 0; i < 4; i++)
    {
        if (table->costs[pkt->sourceid][i] == INF)
        {
            table->costs[pkt->sourceid][i] = pkt->mincost[i];
            changed = true;
        }

        for (int j = 0; j < 4; j++)
        {
            if ((table->costs[i][j] > table->costs[i][pkt->sourceid] + pkt->mincost[j]))
            {
                table->costs[i][j] = pkt->mincost[j] + table->costs[i][pkt->sourceid];
                changed = true;
            }
        }
    }

    if (changed)
    {
        for (int i = 0; i < 4; i++)
        {
            if (is_neighbor(node, i))
            {
                struct rtpkt pkt;
                pkt.sourceid = node;
                pkt.destid = i;
                for (int j = 0; j < 4; j++)
                {
                    pkt.mincost[j] = table->costs[node][j];
                }
                tolayer2(pkt);
            }
        }
        printdt(table, node);
    }
}
