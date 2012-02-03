// libfcgicpp is under the terms of the GNU Lesser General Public License
#ifndef SPECIFICATION_HPP
#define	SPECIFICATION_HPP
#include <stdint.h>

//----Header----
#define FCGI_HEADER_LENGTH 8

//version variants
#define FCGI_VERSION 1

//type variants
#define FCGI_BEGIN_REQUEST     1
#define FCGI_ABORT_REQUEST     2
#define FCGI_END_REQUEST       3
#define FCGI_PARAMS            4
#define FCGI_STDIN             5
#define FCGI_STDOUT            6
#define FCGI_STDERR            7
#define FCGI_DATA              8
#define FCGI_GET_VALUES        9
#define FCGI_GET_VALUES_RESULT 10
#define FCGI_UNKNOWN_TYPE      11
#define FCGI_MAXTYPE           11

//request_id variants
#define FCGI_NULL_REQUEST_ID 0

//----Begin Request----
//role variants
#define FCGI_RESPONDER  1
#define FCGI_AUTHORIZER 2
#define FCGI_FILTER     3

//----End Request----
//protocol_status variants
#define FCGI_REQUEST_COMPLETE 0
#define FCGI_CANT_MPX_CONN    1
#define FCGI_OVERLOADED       2
#define FCGI_UNKNOWN_ROLE     3
#define FCGI_MAXROLE          3

//----Unknown----
//----FCGI_GET_VALUES / FCGI_GET_VALUES_RESULT----
#define FCGI_MAX_CONNS  "FCGI_MAX_CONNS"
#define FCGI_MAX_REQS   "FCGI_MAX_REQS"
#define FCGI_MPXS_CONNS "FCGI_MPXS_CONNS"

namespace fcgi {

	namespace spec {
		using namespace std;

		struct Head {
			uint8_t version;
			uint8_t type;
			uint8_t request_id_b1; //big endian
			uint8_t request_id_b0;
			uint8_t content_length_b1; //big endian
			uint8_t content_length_b0;
			uint8_t padding_length;
			uint8_t reserved;
		};

		struct BeginRequest {
			uint8_t role_b1; //big endian
			uint8_t role_b0;
			uint8_t flags;
			uint8_t reserved[5];
		};

		struct EndRequest {
			uint8_t app_status_b4; //big endian
			uint8_t app_status_b3;
			uint8_t app_status_b2;
			uint8_t app_status_b1;
			uint8_t protocol_status;
			uint8_t reserved[3];
		};

		struct Unknown {
			uint8_t type;
			uint8_t reserved[7];
		};
	}
}

#endif	/* SPECIFICATION_HPP */