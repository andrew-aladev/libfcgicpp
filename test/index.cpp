// libfcgicpp is under the terms of the GNU Lesser General Public License
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/exception/all.hpp>
#include "Client.hpp"
using namespace std;
using namespace fcgi;

int main()
{
	try {
		boost::asio::io_service io_service;
		Client client(string("/tmp/fcgi_test.sock"), io_service);
		client.start_accept();
		io_service.run();
	} catch (boost::exception &e) {
		cerr << boost::diagnostic_information(e) << endl;
	} catch (std::exception &e) {
		cerr << e.what() << endl;
	}
	return 0;
}