// libfcgicpp is under the terms of the GNU Lesser General Public License
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