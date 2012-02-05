//libfcgicpp is boost asio based fastcgi implementation, which uses asynchronous event model and io_service per cpu design
//Copyright (C) 2011 aladjev.andrew@gmail.com 
//This program is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. //This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
//You should have received a copy of the GNU Lesser General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.
#ifndef BODY_HPP
#define	BODY_HPP

#include "Util.hpp"
#include <stdint.h>

namespace fcgi {

	class Body {
	protected:
		uint16_t content_length;

	public:

		Body(uint16_t _content_length) : content_length(_content_length)
		{
		}

		inline size_t getContentLength()
		{
			return this->content_length;
		}
	};

	typedef boost::error_info<struct tag_bad_number, uint32_t> bad_number;

	struct BodyException : public Exception {

		BodyException(string msg) : Exception(msg)
		{
		}
	};
}

#endif	/* BODY_HPP */