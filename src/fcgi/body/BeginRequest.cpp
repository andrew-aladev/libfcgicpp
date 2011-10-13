/* This file is part of libfcgipp.
libfcgipp is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
libfcgipp is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with libfcgipp.  If not, see <http://www.gnu.org/licenses/>.

Copyright (C) 2011 Andrew Aladjev <aladjev.andrew@gmail.com>
 */
#include "BeginRequest.hpp"
#include <iostream>
using namespace std;

fcgi::body::BeginRequest::BeginRequest(stringstream & stream) {
	stream.read((char *) & this->body, FCGI_BODY_LENGTH);
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