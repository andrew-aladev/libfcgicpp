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
#include "Header.hpp"
#include "Spec.hpp"
#include <iostream>
#include <boost/lexical_cast.hpp>
#include "body/BeginRequest.hpp"
#include "body/EndRequest.hpp"
#include "body/Unknown.hpp"
using namespace std;
using namespace boost;

fcgi::Header::~Header() {
	if(this->body) {
		delete this->body;
	}
}

void fcgi::Header::resolveHead(stringstream & stream) {
	stream.flush();
	stream.read((char *) & this->head, FCGI_HEADER_LENGTH);
	this->request_id = (this->head.request_id_b1 << 8) + this->head.request_id_b0; //big endian
	this->content_length = (this->head.content_length_b1 << 8) + this->head.content_length_b0; //big endian
	this->head_empty = false;

	if (this->head.version != FCGI_VERSION) {
		stringstream text;
		text << "Headers version should be equals " << FCGI_VERSION;
		BOOST_THROW_EXCEPTION(
				HeaderInvalidException(text.str()) << bad_number((int) this->head.version)
				);
	}

	if (this->head.type <= 0 || this->head.type > FCGI_MAXTYPE) {
		stringstream text;
		text << "Header type should belongs to [0, " << FCGI_MAXTYPE << "]";
		BOOST_THROW_EXCEPTION(
				HeaderInvalidException(text.str()) << bad_number((int) this->head.type)
				);
	}

	cout << "<----Header---->" << endl;
	cout << "content_length: " << (int) this->content_length << endl;
	cout << "padding_length: " << (int) this->head.padding_length << endl;
	cout << "request_id: " << (int) this->request_id << endl;
	cout << "reserved: " << (int) this->head.reserved << endl;
	cout << "type: " << (int) this->head.type << endl;
	cout << "version: " << (int) this->head.version << endl;
}

void fcgi::Header::resolveBody(stringstream & stream) {
	stream.flush();
	switch (this->head.type) {
		case FCGI_BEGIN_REQUEST:
			this->body = new body::BeginRequest(stream, this->content_length);
			break;
		case FCGI_ABORT_REQUEST:
			break;
		case FCGI_END_REQUEST:
			this->body = new body::EndRequest(stream, this->content_length);
			break;
		case FCGI_PARAMS:
			break;
		case FCGI_STDIN:
			break;
		case FCGI_STDOUT:
			break;
		case FCGI_STDERR:
			break;
		case FCGI_DATA:
			break;
		case FCGI_GET_VALUES:
			break;
		case FCGI_GET_VALUES_RESULT:
			break;
		case FCGI_UNKNOWN_TYPE:
			this->body = new body::Unknown(stream, this->content_length);
			break;
		default:
			stringstream text;
			text << "Could not resolve body";
			BOOST_THROW_EXCEPTION(
					HeaderInvalidException(text.str())
					);
			break;
	}
	this->body_empty = false;
}

void fcgi::Header::resolvePadding(stringstream & stream) {
	uint8_t padding_length = this->head.padding_length;
	uint8_t read_length;
	while(padding_length > 0) {
		if(PADDING_BUFFER_LENGTH < padding_length) {
			read_length = PADDING_BUFFER_LENGTH;
		} else {
			read_length = padding_length;
		}
		stream.read((char *) & this->padding_buffer, read_length);
		padding_length -= read_length;
	}
}