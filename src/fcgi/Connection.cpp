/* This file is part of libfcgipp.
libfcgipp is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
libfcgipp is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with libfcgipp.  If not, see <http://www.gnu.org/licenses/>.

Copyright (C) 2011 Andrew Aladjev <aladjev.andrew@gmail.com>
*/
#include "Connection.hpp"
#include "Spec.hpp"

using namespace boost::asio::local;
using namespace boost::system;
using namespace boost::asio;
using namespace boost;
using namespace std;

fcgi::Connection::~Connection() {
	this->socket.close();
}

fcgi::Connection::pointer fcgi::Connection::create(io_service &io_service) {
	return fcgi::Connection::pointer(new fcgi::Connection(io_service));
}

void fcgi::Connection::bind() {
	async_read(
			this->socket,
			boost::asio::buffer(this->str, BUFFER_SIZE),
			boost::bind(
			&Connection::handle_read,
			shared_from_this(),
			placeholders::error,
			placeholders::bytes_transferred
			));
}

void fcgi::Connection::handle_read(const error_code& ec, size_t bytes_transferred) {
	this->str_stream.write(this->str, bytes_transferred);
	this->stream_size += bytes_transferred;

	if (this->header.isEmpty() && this->stream_size > FCGI_HEADER_LENGTH) {
		this->header.read(this->str_stream);
	}

	if (ec == error::eof) {
		//connection closed
		return;
	} else if (ec) {
		throw system_error(ec);
	}
	this->bind();
}

stream_protocol::socket & fcgi::Connection::getSocket() {
	return this->socket;
}