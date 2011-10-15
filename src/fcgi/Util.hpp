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
#ifndef UTIL_HPP
#define	UTIL_HPP

#include <string>
#include <sstream>
#include <boost/exception/all.hpp>

namespace fcgi {
	using namespace std;

	class Exception : public virtual exception, public virtual boost::exception {
	private:
		string msg;
		
	public:
		Exception(string msg) {
			this->msg = msg;
		}
		virtual ~Exception() throw() {
			;
		}

		virtual const char* what() const throw () {
			return this->msg.c_str();
		}
	};
}

#endif	/* UTIL_HPP */