//libfcgicpp is boost asio based fastcgi implementation, which uses asynchronous event model and io_service per cpu design
//Copyright (C) 2011 aladjev.andrew@gmail.com 
//This program is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. //This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
//You should have received a copy of the GNU Lesser General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.
#include <iostream>
#include <string>
#include <boost/exception/all.hpp>
#include "IOServicePool.hpp"
using namespace std;
using namespace fcgi;

int main()
{
	string unix_socket_name("/tmp/fcgi_test.sock");
	//remove previous bindings
	//example: your program that bind to this socket took SIGKILL and didn't unlink the socket - the socket will stay busy
	//you will catch "address already in use" exception if you want to bind to this socket
	//don't do this if you are not sure that there are no programs listening to this socket
	::unlink(unix_socket_name.c_str());
	try {
		IOServicePool pool(unix_socket_name, 2);
		pool.run();
	} catch (boost::exception &e) {
		cerr << diagnostic_information(e) << endl;
	} catch (std::exception &e) {
		cerr << e.what() << endl;
	}
	return 0;
}