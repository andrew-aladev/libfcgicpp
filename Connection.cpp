#include "Connection.hpp"
#include "Client.hpp"
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