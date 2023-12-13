#include <gtest/gtest.h>
#include "engine.h"

// Test to check initial state of the game
TEST(GameEngineTest, InitialState) {
    struct gamestate g;


    g->opts->grid_width = 4;
    g->opts->grid_height = 4;

    // Initialize the grid to zero
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            g.grid[i][j] = 0;
        }
    }

    // Check if the initial state is correct
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            EXPECT_EQ(g.grid[i][j], 0);
        }
    }
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

