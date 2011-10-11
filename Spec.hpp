/*
This file is part of libfcgipp.

libfcgipp is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

libfcgipp is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser Public License for more details.

You should have received a copy of the GNU Lesser Public License
along with libfcgipp.  If not, see <http://www.gnu.org/licenses/>.

Copyright (C) 2011 Andrew Aladjev <aladjev.andrew@gmail.com>
*/
#ifndef SPECIFICATION_HPP
#define	SPECIFICATION_HPP
#include <stdint.h>

#define FCGI_HEADER_LENGTH 8
#define FCGI_VERSION 1
#define FCGI_BEGIN_REQUEST_LENGTH 8
#define FCGI_END_REQUEST_LENGTH 8
namespace fcgi {

	namespace spec {
		using namespace std;

		struct Header {
			uint8_t version;
			uint8_t type;
			uint8_t request_id_b1;
			uint8_t request_id_b0;
			uint8_t content_length_b1;
			uint8_t content_length_b0;
			uint8_t padding_length;
			uint8_t reserved;
		};

		struct BeginRequest {
			uint8_t role_b1;
			uint8_t role_b0;
			uint8_t flags;
			uint8_t reserved[5];
		};

		struct EndRequest {
			uint8_t app_status_b4;
			uint8_t app_status_b3;
			uint8_t app_status_b2;
			uint8_t app_status_b1;
			uint8_t protocol_status;
			uint8_t reserved[3];
		};

		struct Unknown {
			uint8_t type;
			uint8_t reserved[7];
		};
	}
}

#endif	/* SPECIFICATION_HPP */