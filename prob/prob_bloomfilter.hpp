#ifndef INCLUDED_PROB_BLOOMFILTER
#define INCLUDED_PROB_BLOOMFILTER

#include <prob_bitfield.hpp>

#include <stdint.h>
#include <string>
#include <array>

#include <hash.hpp>

namespace rlib {

/**
 * \brief Encapsulates a bunch of common hash functions.
 */
struct Hashing_Base {
    static uint32_t hash(uint32_t, uint32_t seed);
    static uint32_t hash(uint64_t, uint32_t seed);
    static uint32_t hash(int32_t, uint32_t seed);
    static uint32_t hash(int64_t, uint32_t seed);
    static uint32_t hash(const std::string &, uint32_t seed);
};

class BloomFilter : protected Hashing_Base {
public:

    typedef Hashing_Base Base;

    BloomFilter(int num_hash_functions, int bloom_capacity);

    template<typename T>
    void add(const T &item);

    template<typename T>
    bool present_maybe(const T &item) const;

private:
    int num_hash_functions_;
    Bitfield bitfield_;

    static const int k_NumMaxSeeds = 154;
    static const std::array<uint32_t, k_NumMaxSeeds> s_Seeds;
};


template<typename T>
void BloomFilter::add(const T &item) {

    for (int i = 0; i < num_hash_functions_; ++i) {
        // figure out the seed for the has based on the hash function being used.
        auto seed_index = i > s_Seeds.size() ? (i % s_Seeds.size()) : s_Seeds[i];

        // hash the item using given seed.
        auto hash_val = Base::hash(item, s_Seeds[seed_index]);


        bitfield_.flip(hash_val % bitfield_.capacity(), true);
    }
}

template<typename T>
bool BloomFilter::present_maybe(const T &item) const {
    for (int i = 0; i < num_hash_functions_; ++i) {
        auto seed_index = i > s_Seeds.size() ? (i % s_Seeds.size()) : s_Seeds[i];

        auto hash_val = Base::hash(item, s_Seeds[seed_index]);

        // if one of the slots a hashed value would've filled isn't filled, that means
        // that this value was definitely never added to the filter.
        if (!bitfield_.value(hash_val % bitfield_.capacity())) {
            return false;
        }
    }
    return true;
}


} // close rlib

#endif
