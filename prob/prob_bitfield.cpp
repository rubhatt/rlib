#include <prob_bitfield.hpp>

#include <tuple>

namespace rlib {

static int k_NumBitsPerByte = 8;

namespace detail {

unsigned closest_factor_ceil(unsigned num, unsigned mult) {
    if (num % mult == 0) {
	return num / mult;
    }
    return num / mult + 1;
}

typedef std::tuple<unsigned, unsigned> DividerRemPair;

DividerRemPair bitfield_index(unsigned num) {
    unsigned rem = num % k_NumBitsPerByte;

    return std::make_tuple(num / k_NumBitsPerByte, rem);
}

} // close detail


Bitfield::Bitfield(const std::size_t sz) {
    m_bytearray.resize(detail::closest_factor_ceil(sz, k_NumBitsPerByte), '\0');

}

void Bitfield::flip(std::size_t pos, bool value) {

    auto div_rem = detail::bitfield_index(pos);

    unsigned div = std::get<0>(div_rem);
    if (div >= m_bytearray.size()) {
	return;
    }
    unsigned rem = std::get<1>(div_rem);

    unsigned char & ch = m_bytearray[div];
    if (value) {
	// 1000 0000 shifted remainder number of bits.
	unsigned char target = 0x80 >> rem;
	ch |= target;
    } else {
	// 1000 0000 shifted remainder number of bits, flip bits.
	unsigned char target = (0x80 >> rem) ^ (0xFF);
	ch &= target;
    }
}

bool Bitfield::value(std::size_t pos) {
    auto div_rem = detail::bitfield_index(pos);
    unsigned div = std::get<0>(div_rem);
    if (div >= m_bytearray.size()) {
	return false;
    }
    unsigned rem = std::get<1>(div_rem);

    auto ch = m_bytearray[div];

    return ((ch >> (k_NumBitsPerByte - rem - 1) & 0x01));

}

} // close rlib
