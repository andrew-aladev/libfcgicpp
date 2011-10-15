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

#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/exception/all.hpp>
#include "../test/Client.hpp"
using namespace std;
using namespace fcgi;

int main() {
	try {
		boost::asio::io_service io_service;
		Client cl(string("/tmp/fcgi_test.sock"), io_service);
		cl.start_accept();
		io_service.run();
	} catch(boost::exception &e) {
		cerr << boost::diagnostic_information(e) << endl;
	} catch (std::exception &e) {
		cerr << e.what() << endl;
	}
	return 0;
}
