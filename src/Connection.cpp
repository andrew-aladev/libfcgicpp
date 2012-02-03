// libfcgicpp is under the terms of the GNU Lesser General Public License
#include "Connection.hpp"
#include "Spec.hpp"

using namespace boost::asio::local;
using namespace boost::system;
using namespace boost::asio;
using namespace boost;
using namespace std;

fcgi::Connection::~Connection()
{
	if (this->body_str != NULL) {
		delete[] this->body_str;
	}
	this->socket.close();
}

fcgi::Connection::pointer fcgi::Connection::create(io_service &io_service)
{
	return fcgi::Connection::pointer(new fcgi::Connection(io_service));
}

void fcgi::Connection::start_accept()
{
	this->bind_read_head();
}

void fcgi::Connection::bind_read_head()
{
	async_read(
		this->socket,
		boost::asio::buffer(this->head_str, FCGI_HEADER_LENGTH),
		boost::bind(
		&Connection::handle_read_head,
		shared_from_this(),
		placeholders::error,
		placeholders::bytes_transferred
		));
}

void fcgi::Connection::handle_read_head(const error_code& ec, size_t bytes_transferred)
{
	if (bytes_transferred != FCGI_HEADER_LENGTH || ec == error::eof) {
		//connection closed
		error_code fault = error::make_error_code(error::fault);
		this->close(fault);
		return;
	} else if (ec) {
		throw system_error(ec);
	}

	uint16_t count_bits = this->manager.read_head(this->head_str);
	this->bind_read_body(count_bits);
}

void fcgi::Connection::bind_read_body(uint16_t body_length)
{
	if (this->body_str != NULL) {
		delete[] this->body_str;
	}
	this->body_str = new char[body_length];
	async_read(
		this->socket,
		boost::asio::buffer(this->body_str, body_length),
		boost::bind(
		&Connection::handle_read_body,
		shared_from_this(),
		placeholders::error,
		placeholders::bytes_transferred,
		body_length
		));
}

void fcgi::Connection::handle_read_body(const error_code& ec, size_t bytes_transferred, uint16_t body_length)
{
	if (bytes_transferred != body_length || ec == error::eof) {
		//connection closed
		error_code fault = error::make_error_code(error::fault);
		this->close(fault);
		return;
	} else if (ec) {
		throw system_error(ec);
	}

	this->manager.read_body(this->body_str);
	this->bind_read_head();
}

stream_protocol::socket & fcgi::Connection::getSocket()
{
	return this->socket;
}

void fcgi::Connection::close(error_code &ec)
{
	this->socket.close(ec);
}