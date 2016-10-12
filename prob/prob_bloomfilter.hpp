#ifndef INCLUDED_PROB_BLOOMFILTER
#define INCLUDED_PROB_BLOOMFILTER

#include <prob_bitfield.hpp>

namespace rlib {

class BloomFilter {
public:
    template<typename T>
    void add(const T &item) ;

    template<typename T>
    bool present_maybe(const T &item) ;

private:

    Bitfield m_field;
};


} // close rlib

#endif
