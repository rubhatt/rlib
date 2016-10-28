#include <prob_bloomfilter.hpp>

#include <gtest/gtest.h>

TEST(BloomFilter, SimpleHeterogenousBloomFilter) {
    using namespace rlib;
    BloomFilter f{5, 1000};

    f.add(10);
    f.add(32);
    f.add("test string");
    f.add(static_cast<uint64_t>(45));

    ASSERT_TRUE(f.present_maybe(10));
    ASSERT_TRUE(f.present_maybe(32));
    ASSERT_TRUE(f.present_maybe(static_cast<uint64_t>(45)));
    ASSERT_TRUE(f.present_maybe("test string"));

    /* with the Bloom filter as it is, this works. Though if the hash
     * function changes, it may not work in the future. */
    EXPECT_FALSE(f.present_maybe(5000));
}
