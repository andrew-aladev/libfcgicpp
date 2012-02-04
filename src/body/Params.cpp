// libfcgicpp is under the terms of the GNU Lesser General Public License
#include "body/Params.hpp"
#include <iostream>
#include <bitset>
#include <boost/foreach.hpp>
using namespace boost;
using namespace std;

/*
 * str consist of "name-value" pairs which means:
 * {name_length, value_length, name, value}
 * order of bytes in name_length (value_length) - big endian
 * first bit in name_length and value_length is signal
 * if signal bit is 0 name_length (value_length) is less than 2 ^ 7 - 1
 * else name_length (value_length) is less than 2 ^ 31 - 1
 * we should read more 3 bytes and solve name_length (value_length) as (7 bits) * 2 ^ 24 + (24 bits)
 * to obtain name (value) we should read name_length (value_length) bytes
 */
fcgi::Params::Params(const char *str, uint16_t content_length) : fcgi::Body(content_length)
{
	cout << "<----Params---->" << endl;

	uint8_t name_length, value_length;
	uint32_t name_length_big, value_length_big;
	bool is_name_length_big, is_value_length_big;
	string name, value;
	uint16_t i = 0;
	while (i < content_length) {
		name_length = str[i];
		if (name_length >> 7 == 1) {
			if (i + 4 > content_length) {
				BOOST_THROW_EXCEPTION(BodyException("corrupted params stream"));
			}
			name_length_big =
				((name_length & 0x7f) << 24) +
				(((uint8_t) str[i + 1]) << 16) +
				(((uint8_t) str[i + 2]) << 8) +
				(((uint8_t) str[i + 3]));
			i += 4;
			if (!name_length_big) {
				continue;
			}
			is_name_length_big = true;
		} else {
			if (i + 1 > content_length) {
				BOOST_THROW_EXCEPTION(BodyException("corrupted params stream"));
			}
			i++;
			if (!name_length) {
				continue;
			}
			is_name_length_big = false;
		}

		value_length = str[i];
		if (value_length >> 7 == 1) {
			if (i + 4 > content_length) {
				BOOST_THROW_EXCEPTION(BodyException("corrupted params stream"));
			}
			value_length_big =
				((value_length & 0x7f) << 24) +
				(((uint8_t) str[i + 1]) << 16) +
				(((uint8_t) str[i + 2]) << 8) +
				(((uint8_t) str[i + 3]));
			i += 4;
			is_value_length_big = true;
		} else {
			if (i + 1 > content_length) {
				BOOST_THROW_EXCEPTION(BodyException("corrupted params stream"));
			}
			i++;
			is_value_length_big = false;
		}

		if (is_name_length_big) {
			if (i + name_length_big > content_length) {
				BOOST_THROW_EXCEPTION(BodyException("corrupted params stream"));
			}
			name.assign(str + i, name_length_big);
			i += name_length_big;
		} else {
			if (i + name_length > content_length) {
				BOOST_THROW_EXCEPTION(BodyException("corrupted params stream"));
			}
			name.assign(str + i, name_length);
			i += name_length;
		}

		if (is_value_length_big) {
			if (i + value_length_big > content_length) {
				BOOST_THROW_EXCEPTION(BodyException("corrupted params stream"));
			}
			value.assign(str + i, value_length_big);
			i += value_length_big;
		} else {
			if (i + value_length > content_length) {
				BOOST_THROW_EXCEPTION(BodyException("corrupted params stream"));
			}
			value.assign(str + i, value_length);
			i += value_length;
		}

		this->map[name] = value;
	}

	BOOST_FOREACH(map_type::value_type j, this->map)
	{
		cout << "{" << j.first << ", " << j.second << "}" << endl;
	}
}