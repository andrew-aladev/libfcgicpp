// libfcgicpp is under the terms of the GNU Lesser General Public License
#include "body/BeginRequest.hpp"
#include <iostream>
using namespace std;

fcgi::BeginRequest::BeginRequest(const char *str, uint16_t content_length) : fcgi::Body(content_length)
{
	memcpy((void *) & this->body, (void *) str, this->content_length);
	this->role = (this->body.role_b1 << 8) + this->body.role_b0;

	if (this->role < 0 || this->role > FCGI_MAXROLE) {
		stringstream text;
		text << "BeginRequest role should belongs to [0, " << FCGI_MAXROLE << "]";
		BOOST_THROW_EXCEPTION(
			RequestBodyInvalidException(text.str()) << bad_number((int) this->role)
			);
	}

	cout << "<----BeginRequest---->" << endl;
	cout << "flags: " << (int) this->body.flags << endl;
	cout << "reserved: ";
	for (int i = 0; i < 5; i++) {
		cout << (int) this->body.reserved[i];
	}
	cout << endl;
	cout << "role: " << (int) this->role << endl;
}