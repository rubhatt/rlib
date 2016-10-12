#include <prob_bitfield.hpp>

#include <gtest/gtest.h>

TEST(Bitfield, Basic) {

    using namespace rlib;

    Bitfield bf(44);

    EXPECT_EQ(48, 8 * bf.capacity());

    bf.flip(10, true);
    EXPECT_TRUE(bf.value(10));

    bf.flip(10, false);
    EXPECT_FALSE(bf.value(10));

}
