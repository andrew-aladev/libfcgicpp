/* This file is part of libfcgicpp.
libfcgicpp is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
libfcgicpp is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with libfcgicpp.  If not, see <http://www.gnu.org/licenses/>.

Copyright (C) 2011 Andrew Aladjev <aladjev.andrew@gmail.com>
 */
#include "body/EndRequest.hpp"
using namespace std;

fcgi::body::EndRequest::EndRequest(char *str, uint16_t content_length) : fcgi::body::RequestBody(content_length) {
	memcpy((void *) & this->body, (void *) str, this->content_length);
	this->app_status = (this->body.app_status_b4 << 24) + (this->body.app_status_b3 << 16)
			+ (this->body.app_status_b2 << 8) + this->body.app_status_b1; // big endian
}