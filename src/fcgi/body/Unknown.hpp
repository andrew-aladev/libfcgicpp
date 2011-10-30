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
#ifndef UNKNOWN_HPP
#define	UNKNOWN_HPP
#include "RequestBody.hpp"
#include "../Spec.hpp"

namespace fcgi {

	namespace body {
		using namespace std;

		class Unknown : public RequestBody {
		private:
			spec::Unknown body;
		public:
			Unknown(char *str, uint16_t content_length);
		};
	}
}

#endif	/* UNKNOWN_HPP */