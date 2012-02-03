// libfcgicpp is under the terms of the GNU Lesser General Public License
#include "body/EndRequest.hpp"
using namespace std;

fcgi::EndRequest::EndRequest(const char *str, uint16_t content_length) : fcgi::Body(content_length)
{
	memcpy((void *) & this->body, (void *) str, this->content_length);
	this->app_status = (this->body.app_status_b4 << 24) + (this->body.app_status_b3 << 16)
		+ (this->body.app_status_b2 << 8) + this->body.app_status_b1; // big endian
}