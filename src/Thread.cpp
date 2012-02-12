//libfcgicpp is boost asio based fastcgi implementation, which uses asynchronous event model and io_service per cpu design
//Copyright (C) 2011 aladjev.andrew@gmail.com 
//This program is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. //This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
//You should have received a copy of the GNU Lesser General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.

#include <boost/bind.hpp>
#include "Thread.hpp"

using namespace std;
using namespace boost;
using namespace boost::system;
using namespace boost::asio;
using namespace boost::asio::local;

fcgi::Thread::Thread(const string& _unix_socket, io_service_ptr _io, acceptor_ptr _acceptor, function<void (const exception_ptr& error) > _error_callback)
: io(_io), acceptor(_acceptor), unix_socket(_unix_socket), error_callback(_error_callback)
{
	this->work = thread_ptr(new thread(
		bind(&Thread::start_accept, this)
		));
}

void fcgi::Thread::start_accept()
{	
	try {
		this->accept();
		this->io.get()->run();
	} catch (boost::exception &e) {
		this->error_callback(current_exception());
	} catch (std::exception &e) {
		enable_current_exception(e);
		this->error_callback(current_exception());
	}
}

void fcgi::Thread::accept()
{
	this->connection = Connection::create(this->io);
	this->acceptor->async_accept(
		this->connection.get()->getSocket(),
		bind(
		&Thread::handle_accept, this, placeholders::error
		));
}

void fcgi::Thread::handle_accept(const error_code& ec)
{
	if (!ec) {
		this->connection.get()->start_accept();
	} else {
		throw system_error(ec);
	}
}

void fcgi::Thread::join()
{
	this->work->join();
}