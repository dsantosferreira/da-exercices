// By: Gonçalo Leão

#include "exercises.h"

bool IntroGraph::dagDfs(int v) const {
    bool isDAG = true;
    Vertex *curr = findVertex(v);
    curr->setProcesssing(true);

    for (Edge *e : curr->getAdj()) {
        if (e->getDest()->isProcessing()) {
            return false;
        }
        else if (!e->getDest()->isVisited()) {
            if (!dagDfs(e->getDest()->getId()))
                isDAG = false;
        }
    }

    curr->setProcesssing(false);
    curr->setVisited(true);
    return isDAG;
}

bool IntroGraph::isDAG() const {
    for (Vertex *v : vertexSet) {
        v->setVisited(false);
        v->setProcesssing(false);
    }

    for (Vertex *v : vertexSet) {
        if (!v->isVisited()) {
            if (!dagDfs(v->getId()))
                return false;
        }
    }

    return true;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP1_Ex5, test_isDAG) {
    IntroGraph myGraph;

    for(unsigned int i = 0; i < 6; i++) {
        myGraph.addVertex(i);
    }

    myGraph.addEdge(1, 2, 0);
    myGraph.addEdge(2, 5, 0);
    myGraph.addEdge(5, 4, 0);
    myGraph.addEdge(3, 1, 0);
    myGraph.addEdge(0, 4, 0);

    EXPECT_EQ(myGraph.isDAG(), true);

    myGraph.addEdge(4, 1, 0);

    EXPECT_EQ(myGraph.isDAG(), false);
}