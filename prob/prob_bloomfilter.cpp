#include <prob_bloomfilter.hpp>

namespace rlib {

// all prime numbers from 47 -> 1000. useful as seeds for hashing.
const std::array<uint32_t, BloomFilter::k_NumMaxSeeds> BloomFilter::s_Seeds = {
    47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137,
    139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229,
    233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331,
    337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433,
    439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547,
    557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643, 647,
    653, 659, 661, 673, 677, 683, 691, 701, 709, 719, 727, 733, 739, 743, 751, 757, 761,
    769, 773, 787, 797, 809, 811, 821, 823, 827, 829, 839, 853, 857, 859, 863, 877, 881,
    883, 887, 907, 911, 919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991, 997
};

BloomFilter::BloomFilter(int num_hash_functions, int bloom_capacity)
    : num_hash_functions_(num_hash_functions),
      bitfield_(bloom_capacity)
{
}

// This function should work fine for all primitive types. Do not use for non-primitive
// types.
template<typename T>
uint32_t hash_primitive(T & t, uint32_t seed) {
    const char *bytes = reinterpret_cast<char *>(&t);
    return Hash::mmh3_32(bytes, sizeof(T), seed);
}


uint32_t Hashing_Base::hash(const std::string &s, uint32_t seed) {
    return Hash::mmh3_32(s.c_str(), s.size(), seed);
}

uint32_t Hashing_Base::hash(int32_t value, uint32_t seed) {
    return hash_primitive(value, seed);
}

uint32_t Hashing_Base::hash(int64_t value, uint32_t seed) {
    return hash_primitive(value, seed);
}

uint32_t Hashing_Base::hash(uint32_t value, uint32_t seed) {
    return hash_primitive(value, seed);
}

uint32_t Hashing_Base::hash(uint64_t value, uint32_t seed) {
    return hash_primitive(value, seed);
}


}
