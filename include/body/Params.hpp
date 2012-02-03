// libfcgicpp is under the terms of the GNU Lesser General Public License
#ifndef PARAMS_HPP
#define	PARAMS_HPP
#include "Body.hpp"
#include <string>

namespace fcgi {
	using namespace std;

	class Params : public Body {
	private:
		string body;
	public:
		Params(const char *str, uint16_t content_length);
	};
}

#endif	/* PARAMS_HPP */