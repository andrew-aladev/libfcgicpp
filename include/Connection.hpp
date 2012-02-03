// libfcgicpp is under the terms of the GNU Lesser General Public License
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

namespace fcgi {
	using namespace boost::asio::local;
	using namespace boost::system;
	using namespace boost::asio;
	using namespace boost;
	using namespace std;

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
		typedef shared_ptr<Connection> pointer;

		void start_accept();

		void bind_read_head();
		void bind_read_body(uint16_t body_length);

		stream_protocol::socket & getSocket();
		virtual ~Connection();

		static pointer create(io_service &io_service);
	};
}

#endif	/* CONNECTION_HPP */