// By: Gonçalo Leão

#include "exercises.h"

using namespace std;

bool IntroGraph::topSortDfs(std::vector<int> &res, int v) const {
    bool isDAG = false;
    Vertex *curr = findVertex(v);
    curr->setProcesssing(true);

    for (Edge *e : curr->getAdj()) {
        if (e->getDest()->isProcessing())
            isDAG = true;
        else if (!e->getDest()->isVisited()) {
            if (topSortDfs(res, e->getDest()->getId()))
                isDAG = true;
        }
    }

    res.insert(res.begin(), v);
    curr->setProcesssing(false);
    curr->setVisited(true);
    return isDAG;
}

std::vector<int> IntroGraph::topsort() const {
    vector<int> res;
    queue<int> q;
    Vertex *curr;

    for (Vertex *v : vertexSet) {
        v->setVisited(false);
        v->setIndegree(v->getIncoming().size());
        if (v->getIndegree() == 0) {
            q.push(v->getId());
        }
    }

    while (!q.empty()) {
        curr = findVertex(q.front());
        curr->setVisited(true);
        res.push_back(q.front());

        for (Edge *e : curr->getAdj()) {
            if (e->getDest()->isVisited()) {
                res.clear();
                return res;
            }

            if (e->getDest()->getIndegree() == 1) {
                q.push(e->getDest()->getId());
            }
            else {
                e->getDest()->setIndegree(e->getDest()->getIndegree()-1);
            }
        }

        q.pop();
    }

    return res;
}

/// TESTS ///
#include <gtest/gtest.h>

void expectTopSort(const IntroGraph graph, std::vector<int> topOrder){
    for(auto u: graph.getVertexSet()) {
        auto itrU = std::find(topOrder.begin(), topOrder.end(), u->getId());
        unsigned int indexU = std::distance(topOrder.begin(), itrU);
        for(auto edge: u->getAdj()) {
            auto v = edge->getDest();
            auto itrV = std::find(topOrder.begin(), topOrder.end(), v->getId());
            unsigned int indexV = std::distance(topOrder.begin(), itrV);
            EXPECT_LT(indexU,indexV);
        }
    }
}

TEST(TP1_Ex4, test_topsort) {
    IntroGraph myGraph;
    myGraph.addVertex(1); myGraph.addVertex(2); myGraph.addVertex(3); myGraph.addVertex(4);
    myGraph.addVertex(5); myGraph.addVertex(6); myGraph.addVertex(7);

    myGraph.addEdge(1, 2, 0);
    myGraph.addEdge(1, 4, 0);
    myGraph.addEdge(1, 3, 0);
    myGraph.addEdge(2, 5, 0);
    myGraph.addEdge(2, 4, 0);
    myGraph.addEdge(3, 6, 0);
    myGraph.addEdge(4, 3, 0);
    myGraph.addEdge(4, 6, 0);
    myGraph.addEdge(4, 7, 0);
    myGraph.addEdge(5, 4, 0);
    myGraph.addEdge(5, 7, 0);
    myGraph.addEdge(7, 6, 0);

    std::vector<int> topOrder = myGraph.topsort();
    EXPECT_EQ(topOrder.size(), 7);
    expectTopSort(myGraph, topOrder); // example of two valid topsorts: "1 2 5 4 3 7 6" and "1 2 5 4 7 3 6"

    // to test including a cycle in the graph
    myGraph.addEdge(3, 1, 0);

    topOrder = myGraph.topsort();
    EXPECT_EQ(topOrder.size(), 0);
}