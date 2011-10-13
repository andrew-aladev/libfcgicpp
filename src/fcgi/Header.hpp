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
#ifndef HEADER_HPP
#define	HEADER_HPP

#include <sstream>
#include "Spec.hpp"
#include "Util.hpp"
#include "body/RequestBody.hpp"

namespace fcgi {
	using namespace std;

	class Header {
	private:
		uint16_t request_id;
		uint16_t content_length;
		body::RequestBody *body;
		spec::Header head;
		bool head_empty;
		bool body_empty;

	public:

		Header() {
			this->head_empty = true;
			this->body_empty = true;
		}
		~Header();

		inline bool isHeadEmpty() const {
			return this->head_empty;
		}
		inline bool isBodyEmpty() const {
			return this->body_empty;
		}
		void resolveHead(stringstream & stream);
		void resolveBody(stringstream & stream);
	};

	typedef boost::error_info<struct tag_bad_number, int> bad_number;

	struct HeaderInvalidException : public Exception {

		HeaderInvalidException(string msg) : Exception(msg) {
		}
	};
}

#endif	/* HEADER_HPP */