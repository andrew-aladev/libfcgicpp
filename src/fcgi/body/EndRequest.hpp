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
#ifndef ENDREQUEST_HPP
#define	ENDREQUEST_HPP
#include "RequestBody.hpp"
#include "../Spec.hpp"
#include <sstream>

namespace fcgi {

	namespace body {
		using namespace std;

		class EndRequest : public RequestBody {
		private:
			uint16_t content_length;
			uint32_t app_status;
			spec::EndRequest body;
		public:
			EndRequest(stringstream & stream, uint16_t content_length);
		};
	}
}

#endif	/* ENDREQUEST_HPP */