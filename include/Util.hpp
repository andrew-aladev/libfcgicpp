// libfcgicpp is under the terms of the GNU Lesser General Public License
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