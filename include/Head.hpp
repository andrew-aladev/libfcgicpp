//libfcgicpp is boost asio based fastcgi implementation, which uses asynchronous event model and io_service per cpu design
//Copyright (C) 2011 aladjev.andrew@gmail.com 
//This program is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. //This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
//You should have received a copy of the GNU Lesser General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.
#ifndef HEAD_HPP
#define	HEAD_HPP

#include "Spec.hpp"
#include "Util.hpp"
#include "body/Body.hpp"

namespace fcgi {
	using namespace std;

	class Head {
	private:
		uint16_t request_id;
		uint16_t content_length;
		Body *body;
		spec::Head head;
		bool head_empty;
		bool body_empty;

	public:

		Head()
		{
			this->content_length = 0;
			this->request_id = 0;
			this->head_empty = true;
			this->body_empty = true;
		}
		virtual ~Head();

		inline bool isHeadEmpty() const
		{
			return this->head_empty;
		}

		inline uint16_t getBodyLength() const
		{
			return this->content_length + this->head.padding_length;
		}
		
		inline uint8_t getPaddingLength() const
		{
			return this->head.padding_length;
		}

		inline bool isBodyEmpty() const
		{
			return this->body_empty;
		}

		inline uint8_t getType() const
		{
			return this->head.type;
		}
		void resolveHead(const char *str);
		void reset();
	};

	typedef boost::error_info<struct tag_bad_number, uint32_t> bad_number;

	struct HeadException : public Exception {

		HeadException(string msg) : Exception(msg)
		{
		}
	};
}

#endif	/* HEAD_HPP */