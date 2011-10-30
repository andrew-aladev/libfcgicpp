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
	if (this->str != NULL) {
		delete[] this->str;
	}
	this->socket.close();
}

fcgi::Connection::pointer fcgi::Connection::create(io_service &io_service) {
	return fcgi::Connection::pointer(new fcgi::Connection(io_service));
}

void fcgi::Connection::bind_read_head() {
	if (this->str != NULL) {
		delete[] this->str;
		this->str = NULL;
	}
	this->str = new char[FCGI_HEADER_LENGTH];
	async_read(
			this->socket,
			boost::asio::buffer(this->str, FCGI_HEADER_LENGTH),
			boost::bind(
			&Connection::handle_read_head,
			shared_from_this(),
			placeholders::error,
			placeholders::bytes_transferred
			));
}

void fcgi::Connection::handle_read_head(const error_code& ec, size_t bytes_transferred) {
	if (bytes_transferred != FCGI_HEADER_LENGTH || ec == error::eof) {
		//connection closed
		return;
	} else if (ec) {
		throw system_error(ec);
	}

	try {
		this->header.resolveHead(this->str);
	} catch (const HeaderInvalidException &ex) {
		error_code fault = error::make_error_code(error::fault);
		this->close(fault);
		return;
	} catch (const body::RequestBodyInvalidException &ex) {
		error_code fault = error::make_error_code(error::fault);
		this->close(fault);
		return;
	}

	this->bind_read_body();
}

void fcgi::Connection::bind_read_body() {
	if (this->str != NULL) {
		delete[] this->str;
		this->str = NULL;
	}
	uint16_t body_length = this->header.getBodyLength();
	this->str = new char[body_length];
	async_read(
			this->socket,
			boost::asio::buffer(this->str, body_length),
			boost::bind(
			&Connection::handle_read_body,
			shared_from_this(),
			placeholders::error,
			placeholders::bytes_transferred,
			body_length
			));
}

void fcgi::Connection::handle_read_body(const error_code& ec, size_t bytes_transferred, uint16_t body_length) {
	if (bytes_transferred != body_length || ec == error::eof) {
		//connection closed
		return;
	} else if (ec) {
		throw system_error(ec);
	}

	try {
		this->header.resolveBody(this->str);
		this->header.resolvePadding(this->str);
	} catch (const HeaderInvalidException &ex) {
		error_code fault = error::make_error_code(error::fault);
		this->close(fault);
		return;
	} catch (const body::RequestBodyInvalidException &ex) {
		error_code fault = error::make_error_code(error::fault);
		this->close(fault);
		return;
	}

	this->bind_read_head();
}

stream_protocol::socket & fcgi::Connection::getSocket() {
	return this->socket;
}

void fcgi::Connection::close(error_code &ec) {
	this->socket.close(ec);
}