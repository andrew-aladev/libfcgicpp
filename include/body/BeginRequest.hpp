// libfcgicpp is under the terms of the GNU Lesser General Public License
#ifndef BEGINREQUEST_HPP
#define	BEGINREQUEST_HPP
#include "Body.hpp"
#include "Spec.hpp"

namespace fcgi {
	using namespace std;

	class BeginRequest : public Body {
	private:
		uint16_t role;
		spec::BeginRequest body;
	public:
		BeginRequest(const char *str, uint16_t content_length);
	};
}

#endif	/* BEGINREQUEST_HPP */