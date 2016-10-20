#ifndef HASH_HPP
#define HASH_HPP

#include <cstdint>

namespace rlib {

/**
 * \brief The Hash struct. This structure provides a set of simple and fast non-crypto
 * hash functions.
 */
struct Hash {

    /**
     * @brief mmh3_32 - murmurhash returning an unsigned 32-bit integer.
     * @param key char sequence to hash.
     * @param len length of char seqeuence
     * @param seed seed for the hash function.
     * @return
     */
    static uint32_t mmh3_32(const char *key, uint32_t len, uint32_t seed);

};

}

#endif // HASH_HPP
