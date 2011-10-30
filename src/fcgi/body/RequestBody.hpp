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
#ifndef REQUESTBODY_HPP
#define	REQUESTBODY_HPP

#include "../Util.hpp"
#include <stdint.h>

namespace fcgi {
	namespace body {

		class RequestBody {
		protected:
			uint16_t content_length;

		public:

			RequestBody(uint16_t _content_length) : content_length(_content_length) {
			}

			inline size_t getContentLength() {
				return this->content_length;
			}
		};

		typedef boost::error_info<struct tag_bad_number, int> bad_number;

		struct RequestBodyInvalidException : public Exception {

			RequestBodyInvalidException(string msg) : Exception(msg) {
			}
		};
	}
}

#endif	/* REQUESTBODY_HPP */

