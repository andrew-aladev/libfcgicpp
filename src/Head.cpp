//libfcgicpp is boost asio based fastcgi implementation, which uses asynchronous event model and io_service per cpu design
//Copyright (C) 2011 aladjev.andrew@gmail.com 
//This program is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. //This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
//You should have received a copy of the GNU Lesser General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.
#include "Head.hpp"
#include <iostream>
#include "body/BeginRequest.hpp"
#include "body/EndRequest.hpp"
#include "body/Unknown.hpp"
#include "body/Params.hpp"
using namespace std;
using namespace boost;
using namespace fcgi;

fcgi::Head::~Head()
{
	if (this->body != NULL) {
		delete this->body;
	}
}

void fcgi::Head::reset()
{
	if (this->body != NULL) {
		delete this->body;
		this->body = NULL;
	}
	this->content_length = 0;
	this->request_id = 0;
	this->head_empty = true;
	this->body_empty = true;
}

void fcgi::Head::resolveHead(const char *str)
{
	memcpy((void *) & this->head, (void *) str, FCGI_HEADER_LENGTH);
	this->request_id = (this->head.request_id_b1 << 8) + this->head.request_id_b0; //big endian
	this->content_length = (this->head.content_length_b1 << 8) + this->head.content_length_b0; //big endian
	this->head_empty = false;

	if (this->head.version != FCGI_VERSION) {
		stringstream text;
		text << "Heads version should be equals " << FCGI_VERSION;
		BOOST_THROW_EXCEPTION(HeadException(text.str()) << bad_number(this->head.version));
	}

	if (this->head.type <= 0 || this->head.type > FCGI_MAXTYPE) {
		stringstream text;
		text << "Head type should belongs to [0, " << FCGI_MAXTYPE << "]";
		BOOST_THROW_EXCEPTION(HeadException(text.str()) << bad_number(this->head.type));
	}

	cout << "<----Head---->" << endl;
	cout << "content_length: " << (int) this->content_length << endl;
	cout << "padding_length: " << (int) this->head.padding_length << endl;
	cout << "request_id: " << (int) this->request_id << endl;
	cout << "reserved: " << (int) this->head.reserved << endl;
	cout << "type: " << (int) this->head.type << endl;
	cout << "version: " << (int) this->head.version << endl;
}