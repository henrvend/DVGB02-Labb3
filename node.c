#include "node.h"

void rtinit(struct distance_table *table, int node)
{
    // Tables are already initialized
    printdt(table, node);

    struct rtpkt pkt;
    pkt.sourceid = node;

    for (int i = 0; i < 4; i++)
    {
        pkt.destid = i;
        pkt.mincost[i] = table->costs[node][i];
    }
    rtupdate(table, node, &pkt);
}

void rtupdate(struct distance_table *table, int node, struct rtpkt *pkt)
{
    bool changed = false;
    int best_route = INT_MAX;
    int node_id = pkt->destid;

    for (int i = 0; i < 4; i++)
    {
        // Om vägen till granne plus vägen till destination är mindre än minCost.
        int new_cost = pkt->mincost[i] + table->costs[pkt->sourceid][node_id];
        if (new_cost < table->costs[i][pkt->sourceid])
        {
            table->costs[i][pkt->sourceid] = new_cost;
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
        }
        tolayer2(update_pkt);
    }

    printdt(table, node);
}
