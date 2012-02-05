//libfcgicpp is boost asio based fastcgi implementation, which uses asynchronous event model and io_service per cpu design
//Copyright (C) 2011 aladjev.andrew@gmail.com 
//This program is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. //This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
//You should have received a copy of the GNU Lesser General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.
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