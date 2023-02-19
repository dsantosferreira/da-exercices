// By: Gonçalo Leão

#include "exercises.h"

#include "TestAux.h"
#include <queue>

using namespace std;

std::vector<int> IntroGraph::bfs(const int & source) const {
    std::vector<int> res;

    for (Vertex *v : vertexSet) {
        v->setVisited(false);
    }

    queue<int> q;
    q.push(source);
    Vertex *curr;
    findVertex(source)->setVisited(true);

    while (!q.empty()) {
        curr = findVertex(q.front());
        res.push_back(q.front());

        for (Edge *e : curr->getAdj()) {
            if (!e->getDest()->isVisited()) {
                e->getDest()->setVisited(true);
                q.push(e->getDest()->getId());
            }
        }

        q.pop();
    }


    return res;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP1_Ex3, test_bfs) {
    IntroGraph graph;
    createNetwork(graph);
    std::vector<int> vs = graph.bfs(1);

    unsigned int ids[] = {1, 2, 3, 4, 5, 6, 7};
    EXPECT_EQ(vs.size(), 7);
    for (unsigned int i = 0; i < vs.size(); i++) {
        EXPECT_EQ(vs[i], ids[i]);
    }
}