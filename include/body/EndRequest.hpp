// libfcgicpp is under the terms of the GNU Lesser General Public License
#ifndef ENDREQUEST_HPP
#define	ENDREQUEST_HPP
#include "Body.hpp"
#include "Spec.hpp"

namespace fcgi {
	using namespace std;

	class EndRequest : public Body {
	private:
		uint32_t app_status;
		spec::EndRequest body;
	public:
		EndRequest(const char *str, uint16_t content_length);
	};
}

#endif	/* ENDREQUEST_HPP */