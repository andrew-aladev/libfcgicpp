//libfcgicpp is boost asio based fastcgi implementation, which uses asynchronous event model and io_service per cpu design
//Copyright (C) 2011 aladjev.andrew@gmail.com 
//This program is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. //This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
//You should have received a copy of the GNU Lesser General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.
#include <boost/bind.hpp>
#include <boost/exception_ptr.hpp>
#include "IOServicePool.hpp"
using namespace std;
using namespace boost;
using namespace boost::asio;

fcgi::IOServicePool::IOServicePool(const string &unix_socket, size_t pool_size) : unix_socket(unix_socket)
{
	if (pool_size == 0) {
		BOOST_THROW_EXCEPTION(PoolException("cannot init empty pool") << bad_number(pool_size));
	}

	for (size_t i = 0; i < pool_size; ++i) {
		io_service_ptr io(new io_service());
		io_service_work_ptr work(new io_service::work(*io));
		this->io_services.push_back(io);
		this->io_services_work.push_back(work);
	}
	this->next_io_service = this->io_services.begin();
}

void fcgi::IOServicePool::run()
{
	list<io_service_ptr>::iterator it;
	list<thread_ptr> threads;
	exception_ptr error;
	for (it = this->io_services.begin(); it != this->io_services.end(); it++) {
		threads.push_back(thread_ptr(new Thread(this->unix_socket, *(*it), error)));
	}

	list<thread_ptr>::iterator jt;
	for (jt = threads.begin(); jt != threads.end(); jt++) {
		(*jt)->join();
	}
	if (error) {
		rethrow_exception(error);
	}
}

void fcgi::IOServicePool::stop()
{
	list<io_service_ptr>::iterator it;
	for (it = this->io_services.begin(); it != this->io_services.end(); it++) {
		(*it)->stop();
	}
}

io_service& fcgi::IOServicePool::get_io_service()
{
	io_service_ptr io_service = *this->next_io_service;
	this->next_io_service++;
	if (this->next_io_service == this->io_services.end()) {
		this->next_io_service = this->io_services.begin();
	}
	return *io_service;
}