#include <gtest/gtest.h>
#include "highscore.h"

// Test to check high score retrieval
TEST(HighScoreTest, RetrieveHighScore) {
    const char* highscore_file = highscore_retrieve_file();
    
    // Check if the highscore file path is non-null
    EXPECT_NE(highscore_file, nullptr);
}

// Test to check high score storage
TEST(HighScoreTest, StoreHighScore) {
    bool success = store_high_score(100); // Mock high score value

    EXPECT_TRUE(success);

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

