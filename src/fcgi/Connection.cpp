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
#include "Connection.hpp"
#include "Spec.hpp"
#include "Header.hpp"
#include "body/RequestBody.hpp"

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

	try {
		if (this->header.isHeadEmpty() && this->stream_size > FCGI_HEADER_LENGTH) {
			this->header.resolveHead(this->str_stream);
		}
		if (this->header.isBodyEmpty() && this->stream_size > FCGI_HEADER_LENGTH + FCGI_BODY_LENGTH) {
			this->header.resolveBody(this->str_stream);
		}
	} catch (const HeaderInvalidException &ex) {
		error_code fault = error::make_error_code(error::fault);
		this->close(fault);
		return;
	} catch (const body::RequestBodyInvalidException &ex) {
		error_code fault = error::make_error_code(error::fault);
		this->close(fault);
		return;
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
void fcgi::Connection::close(error_code &ec) {
	this->socket.close(ec);
}