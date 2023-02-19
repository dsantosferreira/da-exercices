// By: Gonçalo Leão

#include "exercises.h"

#include "TestAux.h"

using namespace std;

void IntroGraph::sscDfs(int v, std::vector<std::pair<int, int>> &numAndLow, std::vector<bool> &inStack,
                        std::stack<int> &visited, int &time, vector<std::vector<int>> &sccs) const {
    Vertex *curr = findVertex(v);
    numAndLow[v - 1] = {time, time};
    time++;
    inStack[v - 1] = true;
    visited.push(v);
    curr->setVisited(true);

    for (Edge *e : curr->getAdj()) {
        Vertex *dest = e->getDest();
        int destId = dest->getId();

        if (numAndLow[destId - 1].first == 0) {
            sscDfs(destId, numAndLow, inStack, visited, time, sccs);
            numAndLow[v - 1].second = min(numAndLow[v - 1].second, numAndLow[destId - 1].second);
        }
        else if (inStack[destId - 1]) {
            numAndLow[v - 1].second = min(numAndLow[v - 1].second, numAndLow[destId - 1].first);
        }
    }

    if (numAndLow[v - 1].first == numAndLow[v - 1].second) {
        vector<int> scc;
        while (v != visited.top()) {
            scc.insert(scc.begin(), visited.top());
            inStack[visited.top() - 1] = false;
            visited.pop();
        }
        scc.insert(scc.begin(), visited.top());
        visited.pop();
        sccs.push_back(scc);
        inStack[v - 1] = false;
    }
}

std::vector<std::vector<int>> IntroGraph::computeSCCs() const {
    std::vector<std::vector<int>> sccs;

    vector<pair<int, int>> numAndLow(getNumVertex());
    vector<bool> inStack(getNumVertex());
    int time = 1;
    stack<int> visited;

    for (int i = 1; i <= vertexSet.size(); i++) {
        inStack[i - 1] = false;
        numAndLow[i - 1] = {0, 0};
    }

    for (Vertex *v : vertexSet) {
        if (!v->isVisited()) {
            sscDfs(v->getId(), numAndLow, inStack, visited, time, sccs);
        }
    }

    return sccs;
}

/// TESTS ///
#include <gtest/gtest.h>
#include <gmock/gmock.h>

TEST(TP1_Ex6, test_SCC) {
    IntroGraph graph;
    createNetwork(graph);
    std::vector<std::vector<int>> sccs = graph.computeSCCs();

    EXPECT_EQ(sccs.size(), 3);
    EXPECT_THAT(sccs,  ::testing::UnorderedElementsAre(::testing::UnorderedElementsAre(1,2,3,5,6), ::testing::UnorderedElementsAre(4), ::testing::UnorderedElementsAre(7)));

    IntroGraph graph2;
    for(unsigned int i = 1; i <= 5; i++) {
        graph2.addVertex(i);
    }
    graph2.addEdge(1,3,0);
    graph2.addEdge(1,4,0);
    graph2.addEdge(2,1,0);
    graph2.addEdge(3,2,0);
    graph2.addEdge(4,5,0);
    sccs = graph2.computeSCCs();

    EXPECT_EQ(sccs.size(), 3);
    EXPECT_THAT(sccs,  ::testing::UnorderedElementsAre(::testing::UnorderedElementsAre(1,2,3), ::testing::UnorderedElementsAre(4), ::testing::UnorderedElementsAre(5)));
}