/* This file is part of libfcgipp.
libfcgipp is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
libfcgipp is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with libfcgipp.  If not, see <http://www.gnu.org/licenses/>.

Copyright (C) 2011 Andrew Aladjev <aladjev.andrew@gmail.com>
 */
#include "Header.hpp"
#include "Spec.hpp"
#include <iostream>
#include <boost/lexical_cast.hpp>
using namespace std;
using namespace boost;

void fcgi::Header::read(stringstream & stream) {
	stream.flush();
	stream.read((char *) & this->head, FCGI_HEADER_LENGTH);
	this->request_id = (this->head.request_id_b1 << 8) + this->head.request_id_b0; //big endian
	this->content_length = (this->head.content_length_b1 << 8) + this->head.content_length_b0; //big endian
	this->empty = false;

	if (this->head.version != FCGI_VERSION) {
		stringstream text;
		text << "Headers version should be equals " << FCGI_VERSION;
		BOOST_THROW_EXCEPTION(
				HeaderInvalidException(text.str()) << bad_number((int) this->head.version)
				);
	}

	if (this->head.type < 0 || this->head.type > FCGI_MAXTYPE) {
		stringstream text;
		text << "Header type should belongs to [0, " << FCGI_MAXTYPE << "]";
		BOOST_THROW_EXCEPTION(
				HeaderInvalidException(text.str()) << bad_number((int) this->head.type)
				);
	}

	cout << "content_length: " << (int) this->content_length << endl;
	cout << "padding_length: " << (int) this->head.padding_length << endl;
	cout << "request_id: " << (int) this->request_id << endl;
	cout << "reserved: " << (int) this->head.reserved << endl;
	cout << "type: " << (int) this->head.type << endl;
	cout << "version: " << (int) this->head.version << endl;
}