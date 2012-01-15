/* This file is part of libfcgicpp.
libfcgicpp is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
libfcgicpp is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with libfcgicpp.  If not, see <http://www.gnu.org/licenses/>.

Copyright (C) 2011 Andrew Aladjev <aladjev.andrew@gmail.com>
 */
#ifndef REQUEST_HPP
#define	REQUEST_HPP

#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include "Connection.hpp"

using namespace boost;
using namespace boost::asio;

namespace fcgi {

	class Request : public enable_shared_from_this<Request> {
	private:
		Connection conn;

		Request(io_service &io_service);

	public:
		typedef shared_ptr<Request> pointer;
		static pointer create(io_service &io_service);

		inline const Connection & getConnection() {
			return this->conn;
		}
	};
}

#endif	/* REQUEST_HPP */