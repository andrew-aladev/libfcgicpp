#ifndef UTIL_HPP
#define	UTIL_HPP

#include <string>
#include <sstream>

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