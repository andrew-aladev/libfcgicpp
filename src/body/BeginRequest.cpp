//libfcgicpp is boost asio based fastcgi implementation, which uses asynchronous event model and io_service per cpu design
//Copyright (C) 2011 aladjev.andrew@gmail.com 
//This program is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. //This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
//You should have received a copy of the GNU Lesser General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.
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
		BOOST_THROW_EXCEPTION(BodyException(text.str()) << bad_number(this->role));
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