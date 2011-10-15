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
#ifndef CLIENT_HPP
#define	CLIENT_HPP

#include <iostream>
#include <string>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include "../fcgi/Connection.hpp"

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

