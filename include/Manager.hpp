// libfcgicpp is under the terms of the GNU Lesser General Public License
#ifndef MANAGER_HPP
#define	MANAGER_HPP
#include <stdint.h>
#include "Head.hpp"
#include "body/Body.hpp"
#include "body/Padding.hpp"
#include "body/BeginRequest.hpp"
#include "body/EndRequest.hpp"
#include "body/Params.hpp"
#include "body/Stdin.hpp"
#include "body/Unknown.hpp"

namespace fcgi {

	class Manager {
	private:
		Head head;
		Body *body;
		Padding padding;
	public:
		uint16_t read_head(const char *str);
		void read_body(const char *str);
		virtual ~Manager();
	};
}

#endif	/* MANAGER_HPP */