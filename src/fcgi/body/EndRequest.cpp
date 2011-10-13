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
#include "EndRequest.hpp"
using namespace std;

fcgi::body::EndRequest::EndRequest(stringstream & stream) {
	stream.read((char *) & this->body, FCGI_BODY_LENGTH);
	this->app_status = (this->body.app_status_b4 << 24) + (this->body.app_status_b3 << 16)
			+ (this->body.app_status_b2 << 8) + this->body.app_status_b1; // big endian
}