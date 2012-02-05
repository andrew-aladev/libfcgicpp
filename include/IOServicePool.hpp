//libfcgicpp is boost asio based fastcgi implementation, which uses asynchronous event model and io_service per cpu design
//Copyright (C) 2011 aladjev.andrew@gmail.com 
//This program is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. //This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
//You should have received a copy of the GNU Lesser General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.
#ifndef IOSERVICEPOOL_HPP
#define	IOSERVICEPOOL_HPP

#include <list>
#include <boost/noncopyable.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/shared_ptr.hpp>
#include "Thread.hpp"
#include "Util.hpp"

namespace fcgi {
	using namespace std;
	using namespace boost;
	using namespace boost::asio;

	class IOServicePool : private noncopyable {
	private:
		typedef shared_ptr<Thread> thread_ptr;
		typedef shared_ptr<io_service> io_service_ptr;
		typedef shared_ptr<io_service::work> io_service_work_ptr;

		string unix_socket;
		list<io_service_ptr> io_services;
		list<io_service_work_ptr> io_services_work;
		list<io_service_ptr>::iterator next_io_service;

	public:

		explicit IOServicePool(const string &unix_socket, size_t pool_size);
		void run();
		void stop();
		io_service& get_io_service();
	};

	typedef error_info<struct tag_bad_number, uint32_t> bad_number;

	struct PoolException : public Exception {

		PoolException(string msg) : Exception(msg)
		{
		}
	};
}

#endif	/* IOSERVICEPOOL_HPP */