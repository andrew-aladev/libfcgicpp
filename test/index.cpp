//libfcgicpp is boost asio based fastcgi implementation, which uses asynchronous event model and io_service per cpu design
//Copyright (C) 2011 aladjev.andrew@gmail.com 
//This program is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. //This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
//You should have received a copy of the GNU Lesser General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/exception/all.hpp>
#include "IOServicePool.hpp"
using namespace std;
using namespace fcgi;

int main()
{
	try {
		IOServicePool pool(string("/tmp/fcgi_test.sock"), 2);
		pool.run();
	} catch (boost::exception &e) {
		cerr << boost::diagnostic_information(e) << endl;
	} catch (std::exception &e) {
		cerr << e.what() << endl;
	}
	return 0;
}