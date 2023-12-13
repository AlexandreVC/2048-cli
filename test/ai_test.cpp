#include <gtest/gtest.h>
#include "ai.h"
#include "engine.h"



// Test to check if ai_move returns a valid move
TEST(AIMoveTest, ReturnsValidMove) {
    struct gamestate g;

    char move = ai_move(&g);
    EXPECT_TRUE(move == 'w' || move == 'a' || move == 's' || move == 'd');
}

// Test to check behavior when interactive option is enabled
TEST(AIMoveTest, InteractiveOption) {
    struct gamestate g;

    char move = ai_move(&g);
    EXPECT_TRUE(move == 'w' || move == 'a' || move == 's' || move == 'd');
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


