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
#include "Client.hpp"

using namespace boost::asio::local;
using namespace boost::system;
using namespace boost::asio;
using namespace boost;
using namespace std;

fcgi::Client::Client(const string &unix_socket, io_service& io_service)
: unix_socket(unix_socket) {
	::unlink(this->unix_socket.c_str());
	this->acceptor = new stream_protocol::acceptor(
			io_service,
			stream_protocol::endpoint(this->unix_socket)
			);
}

void fcgi::Client::start_accept() {
	Connection::pointer new_connection = Connection::create(this->acceptor->io_service());

	this->acceptor->async_accept(
			new_connection.get()->getSocket(),
			boost::bind(
			&Client::handle_accept, this, new_connection, placeholders::error
			));
}

fcgi::Client::~Client() {
	::unlink(this->unix_socket.c_str());
	delete this->acceptor;
}

void fcgi::Client::handle_accept(fcgi::Connection::pointer new_connection, const error_code& ec) {
	if (!ec) {
		new_connection.get()->bind_read_head();
		this->start_accept();
	} else {
		throw system_error(ec);
	}
}