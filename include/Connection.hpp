//libfcgicpp is boost asio based fastcgi implementation, which uses asynchronous event model and io_service per cpu design
//Copyright (C) 2011 aladjev.andrew@gmail.com 
//This program is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. //This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
//You should have received a copy of the GNU Lesser General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.
#ifndef CONNECTION_HPP
#define	CONNECTION_HPP

#include <iostream>
#include <sstream>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include "Manager.hpp"
#include "Util.hpp"

namespace fcgi {
	using namespace std;
	using namespace boost;
	using namespace boost::system;
	using namespace boost::asio;
	using namespace boost::asio::local;

	class Connection : public enable_shared_from_this<Connection> {
	private:
		stream_protocol::socket socket;
		char head_str[FCGI_HEADER_LENGTH];
		char *body_str;
		stringstream str_stream;
		size_t stream_size;

		Manager manager;

		Connection(io_service &io_service) : socket(io_service)
		{
			this->stream_size = 0;
			this->body_str = NULL;
		}

		void handle_read_head(const error_code& ec, size_t bytes_transferred);
		void handle_read_body(const error_code& ec, size_t bytes_transferred, uint16_t body_length);
		void close(error_code &ec);

	public:
		typedef shared_ptr<Connection> connection_ptr;
		
		void start_accept();

		void bind_read_head();
		void bind_read_body(uint16_t body_length);

		stream_protocol::socket & getSocket();
		virtual ~Connection();

		static connection_ptr create(io_service_ptr io);
	};
	
	typedef Connection::connection_ptr connection_ptr;
}

#endif	/* CONNECTION_HPP */