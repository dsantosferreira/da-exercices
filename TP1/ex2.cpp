// By: Gonçalo Leão

#include "exercises.h"

#include "TestAux.h"

using namespace std;

void IntroGraph::simpleDfs(std::vector<int> &res, int v) const {
    Vertex *curr = findVertex(v);
    curr->setVisited(true);
    res.push_back(v);

    auto adj = curr->getAdj();

    for (Edge *e : adj) {
        if(!e->getDest()->isVisited()) {
            simpleDfs(res, e->getDest()->getId());
        }
    }
}

std::vector<int> IntroGraph::dfs(const int & source) const {
    std::vector<int> res;

    for (auto v: vertexSet) {
        v->setVisited(false);
    }

    simpleDfs(res, source);

    return res;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP1_Ex2, test_dfs) {
    IntroGraph graph;
    createNetwork(graph);
    std::vector<int> vs = graph.dfs(1);

    unsigned int ids[] = {1, 2, 5, 6, 3, 7, 4};
    EXPECT_EQ(vs.size(), 7);
    for (unsigned int i = 0; i < vs.size(); i++) {
        EXPECT_EQ(vs[i], ids[i]);
    }
}