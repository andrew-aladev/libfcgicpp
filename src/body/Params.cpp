// libfcgicpp is under the terms of the GNU Lesser General Public License
#include "body/Params.hpp"
#include <iostream>
using namespace std;

fcgi::Params::Params(const char *str, uint16_t content_length) : fcgi::Body(content_length)
{
	this->body.assign(str, this->content_length);

	cout << "<----Params---->" << endl;
	for (uint16_t i = 0; i < content_length; i++) {
		cout << (int) *(this->body.begin() + i) << " ";
	}
	cout << endl << this->body << endl;
}