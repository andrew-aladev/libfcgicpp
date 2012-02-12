//libfcgicpp is boost asio based fastcgi implementation, which uses asynchronous event model and io_service per cpu design
//Copyright (C) 2011 aladjev.andrew@gmail.com 
//This program is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. //This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
//You should have received a copy of the GNU Lesser General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.
#ifndef UTIL_HPP
#define	UTIL_HPP

#include <string>
#include <sstream>
#include <boost/exception/all.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>

namespace fcgi {
	using namespace std;
	using namespace boost;
	using namespace boost::asio;
	using namespace boost::asio::local;

	typedef shared_ptr<io_service> io_service_ptr;
	typedef weak_ptr<io_service> io_service_weak_ptr;
	typedef shared_ptr<io_service::work> io_service_work_ptr;
	typedef shared_ptr<stream_protocol::acceptor> acceptor_ptr;
	typedef shared_ptr<thread> thread_ptr;

	class Exception : public virtual std::exception, public virtual boost::exception {
	private:
		string msg;

	public:

		Exception(string msg)
		{
			this->msg = msg;
		}

		virtual ~Exception() throw()
		{
			;
		}

		virtual const char* what() const throw()
		{
			return this->msg.c_str();
		}
	};
}

#endif	/* UTIL_HPP */