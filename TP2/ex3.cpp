// By: Gonçalo Leão

#include "exercises.h"

int maxSubsequenceBF(int A[], unsigned int n, unsigned int &i, unsigned int &j) {
    // TODO
    return 0;
}


/// TESTS ///
#include <gtest/gtest.h>

TEST(TP2_Ex3, maxSubsequence) {
    int A[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    unsigned int n = 9;
    unsigned int i, j;
    EXPECT_EQ(maxSubsequenceBF(A,n,i,j), 6);
    EXPECT_EQ(i, 3);
    EXPECT_EQ(j, 6);
}