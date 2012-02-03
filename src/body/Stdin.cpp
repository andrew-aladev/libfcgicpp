// libfcgicpp is under the terms of the GNU Lesser General Public License
#include "body/Stdin.hpp"
#include <iostream>
using namespace std;

fcgi::Stdin::Stdin(const char *str, uint16_t content_length) : fcgi::Body(content_length)
{
	this->body.assign(str, this->content_length);

	cout << "<----Stdin---->" << endl;
	cout << this->body << endl;
}