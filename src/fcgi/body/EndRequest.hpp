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
			uint32_t app_status;
			spec::EndRequest body;
		public:
			EndRequest(stringstream & stream);
		};
	}
}

#endif	/* ENDREQUEST_HPP */