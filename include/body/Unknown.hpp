// libfcgicpp is under the terms of the GNU Lesser General Public License
#ifndef UNKNOWN_HPP
#define	UNKNOWN_HPP
#include "Body.hpp"
#include "Spec.hpp"

namespace fcgi {
	using namespace std;

	class Unknown : public Body {
	private:
		spec::Unknown body;
	public:
		Unknown(const char *str, uint16_t content_length);
	};
}

#endif	/* UNKNOWN_HPP */