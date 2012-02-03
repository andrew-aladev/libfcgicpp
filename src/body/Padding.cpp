// libfcgicpp is under the terms of the GNU Lesser General Public License
#include "body/Padding.hpp"
#include <cstring>

void fcgi::Padding::resolve_padding(const char * str, uint8_t padding_length)
{
	uint8_t read_length;
	while (padding_length > 0) {
		if (PADDING_BUFFER_LENGTH < padding_length) {
			read_length = PADDING_BUFFER_LENGTH;
		} else {
			read_length = padding_length;
		}
		memcpy((void *) & this->padding_buffer, (void *) str, read_length);
		padding_length -= read_length;
	}
}