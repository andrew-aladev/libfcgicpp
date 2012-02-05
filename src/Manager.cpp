//libfcgicpp is boost asio based fastcgi implementation, which uses asynchronous event model and io_service per cpu design
//Copyright (C) 2011 aladjev.andrew@gmail.com 
//This program is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. //This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
//You should have received a copy of the GNU Lesser General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.
#include "Manager.hpp"
#include "Spec.hpp"
using namespace std;

fcgi::Manager::~Manager()
{
	if (this->body != NULL) {
		delete this->body;
	}
}

uint16_t fcgi::Manager::read_head(const char *str)
{
	this->head.resolveHead(str);
	return this->head.getBodyLength();
}

void fcgi::Manager::read_body(const char *str)
{
	switch (this->head.getType()) {
	case FCGI_BEGIN_REQUEST:
		this->body = new BeginRequest(str, this->head.getBodyLength());
		break;
	case FCGI_END_REQUEST:
		this->body = new EndRequest(str, this->head.getBodyLength());
		break;
	case FCGI_UNKNOWN_TYPE:
		this->body = new Unknown(str, this->head.getBodyLength());
		break;
	case FCGI_PARAMS:
		this->body = new Params(str, this->head.getBodyLength());
		break;
	case FCGI_ABORT_REQUEST:
	case FCGI_STDIN:
		this->body = new Stdin(str, this->head.getBodyLength());
		//break;
	case FCGI_STDOUT:
	case FCGI_STDERR:
	case FCGI_DATA:
	case FCGI_GET_VALUES:
	case FCGI_GET_VALUES_RESULT:
	default:
		stringstream text;
		text << "Could not resolve body with type " << (uint32_t) this->head.getType();
		BOOST_THROW_EXCEPTION(HeadException(text.str()) << bad_number(this->head.getType()));
		break;
	}
	this->body = NULL;
	this->padding.resolve_padding(str, this->head.getPaddingLength());
}