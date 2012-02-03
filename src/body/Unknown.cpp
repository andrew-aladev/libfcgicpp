// libfcgicpp is under the terms of the GNU Lesser General Public License
#include "body/Unknown.hpp"

fcgi::Unknown::Unknown(const char *str, uint16_t content_length) : fcgi::Body(content_length)
{
	memcpy((void *) & this->body, (void *) str, this->content_length);
}