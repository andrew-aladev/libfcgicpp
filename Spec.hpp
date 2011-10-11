#ifndef SPECIFICATION_HPP
#define	SPECIFICATION_HPP
#include <stdint.h>

#define FCGI_HEADER_LENGTH 8
#define FCGI_VERSION 1
#define FCGI_BEGIN_REQUEST_LENGTH 8
#define FCGI_END_REQUEST_LENGTH 8
namespace fcgi {

	namespace spec {
		using namespace std;

		struct Header {
			uint8_t version;
			uint8_t type;
			uint8_t request_id_b1;
			uint8_t request_id_b0;
			uint8_t content_length_b1;
			uint8_t content_length_b0;
			uint8_t padding_length;
			uint8_t reserved;
		};

		struct BeginRequest {
			uint8_t role_b1;
			uint8_t role_b0;
			uint8_t flags;
			uint8_t reserved[5];
		};

		struct EndRequest {
			uint8_t app_status_b4;
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