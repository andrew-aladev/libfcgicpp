// libfcgicpp is under the terms of the GNU Lesser General Public License
#ifndef STDIN_HPP
#define	STDIN_HPP
#include "Body.hpp"
#include <string>

namespace fcgi {
	using namespace std;

	class Stdin : public Body {
	private:
		string body;
	public:
		Stdin(const char *str, uint16_t content_length);
	};
}

#endif	/* STDIN_HPP */