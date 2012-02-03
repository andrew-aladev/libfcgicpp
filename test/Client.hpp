// libfcgicpp is under the terms of the GNU Lesser General Public License
#ifndef CLIENT_HPP
#define	CLIENT_HPP

#include <iostream>
#include <string>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include "Connection.hpp"

namespace fcgi {
	using namespace boost::asio::local;
	using namespace boost::system;
	using namespace boost::asio;

	class Client {
	private:
		string unix_socket;
		stream_protocol::acceptor *acceptor;
		stream_protocol::socket *socket;

	public:

		Client(const string &unix_socket, io_service& io_service);
		void start_accept();
		virtual ~Client();

	private:

		void handle_accept(Connection::pointer new_connection, const error_code& error);
	};
}

#endif	/* CLIENT_HPP */