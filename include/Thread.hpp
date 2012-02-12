//libfcgicpp is boost asio based fastcgi implementation, which uses asynchronous event model and io_service per cpu design
//Copyright (C) 2011 aladjev.andrew@gmail.com 
//This program is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. //This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
//You should have received a copy of the GNU Lesser General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.
#ifndef THREAD_HPP
#define	THREAD_HPP

#include <boost/function.hpp>
#include <boost/thread.hpp>
#include <boost/asio.hpp>
#include <boost/exception_ptr.hpp>
#include "Connection.hpp"
#include "Util.hpp"

namespace fcgi {
	using namespace std;
	using namespace boost;
	using namespace boost::asio;
	using namespace boost::asio::local;

	class Thread {
	private:
		string unix_socket;
		thread_ptr work;
		io_service_ptr io;
		acceptor_ptr acceptor;
		connection_ptr connection;
		function<void (const exception_ptr& error) > error_callback;

		void start_accept();
		void accept();

	public:

		Thread(const string &unix_socket, io_service_ptr io_service, acceptor_ptr acceptor, function<void (const exception_ptr& error) > error_callback);
		void handle_accept(const error_code& error);
		void join();
	};
}

#endif	/* THREAD_HPP */