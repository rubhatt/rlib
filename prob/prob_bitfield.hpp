#ifndef INCLUDED_PROB_BITFIELD
#define INCLUDED_PROB_BITFIELD

#include <vector>

namespace rlib {

class Bitfield {

public:
    Bitfield(const std::size_t sz);

    void flip(std::size_t pos, bool value);

    bool value(std::size_t pos);

    std::size_t capacity() const { 
	return m_bytearray.size();
    }

private:
    std::vector<unsigned char> m_bytearray;

};

} // close rlib

#endif
