/*
This file is part of libfcgipp.

libfcgipp is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

libfcgipp is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser Public License for more details.

You should have received a copy of the GNU Lesser Public License
along with libfcgipp.  If not, see <http://www.gnu.org/licenses/>.

Copyright (C) 2011 Andrew Aladjev <aladjev.andrew@gmail.com>
*/
#include "Header.hpp"
#include "Spec.hpp"
#include <iostream>
using namespace std;

void fcgi::Header::read(stringstream & stream) {
	stream.flush();
	stream.read((char *) &this->head, sizeof(spec::Header));
	this->empty = false;

	cout << "content_length: " << (int) this->head.content_length_b1 << (int) this->head.content_length_b0 << endl;
	cout << "padding_length: " << (int) this->head.padding_length << endl;
	cout << "request_id: " << (int) this->head.request_id_b1 << (int) this->head.request_id_b0 << endl;
	cout << "reserved: " << (int) this->head.reserved << endl;
	cout << "type: " << (int) this->head.type << endl;
	cout << "version: " << (int) this->head.version << endl;
}