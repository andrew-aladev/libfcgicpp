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