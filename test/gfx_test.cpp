#include <gtest/gtest.h>
#include "gfx.h"


// Test for gfx_init function
TEST(GfxTest, GfxInit) {
    struct gamestate g;

    struct gfx_state* gfx = gfx_init(&g);
    EXPECT_NE(gfx, nullptr);

}

// Test for gfx_draw function
TEST(GfxTest, GfxDraw) {
    struct gfx_state gfx;
    struct gamestate g;
    // Call gfx_draw and expect no errors
    gfx_draw(&gfx, &g);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

