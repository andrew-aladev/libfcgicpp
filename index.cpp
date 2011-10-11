#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include "Client.hpp"
using namespace std;
using namespace fcgi;

int main() {
	try {
		boost::asio::io_service io_service;
		Client cl(string("/tmp/fcgi_test.sock"), io_service);
		cl.start_accept();
		io_service.run();
	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
