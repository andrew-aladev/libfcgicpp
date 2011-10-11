#ifndef CONNECTION_HPP
#define	CONNECTION_HPP

#include <iostream>
#include <sstream>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include "Header.hpp"

#define BUFFER_SIZE 128

namespace fcgi {
    using namespace boost::asio::local;
    using namespace boost::system;
    using namespace boost::asio;
    using namespace boost;
    using namespace std;

    class Connection : public enable_shared_from_this<Connection> {
    private:
        stream_protocol::socket socket;
        char str[BUFFER_SIZE];
        stringstream str_stream;
        size_t stream_size;

        Header header;

        Connection(io_service &io_service)
        : socket(io_service) {
            this->stream_size = 0;
        }

        void handle_read(const error_code& ec, size_t bytes_transferred);

    public:
        typedef shared_ptr<Connection> pointer;

        void bind();
        stream_protocol::socket & getSocket();
        virtual ~Connection();

        static pointer create(io_service &io_service);
    };
}

#endif	/* CONNECTION_HPP */