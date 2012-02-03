// libfcgicpp is under the terms of the GNU Lesser General Public License
#ifndef PADDING_HPP
#define	PADDING_HPP

#include <stdint.h>

#define PADDING_BUFFER_LENGTH 255

namespace fcgi {

	class Padding {
	private:
		char padding_buffer[PADDING_BUFFER_LENGTH];

	public:
		void resolve_padding(const char * str, uint8_t padding_length);
	};
}

#endif	/* PADDING_HPP */