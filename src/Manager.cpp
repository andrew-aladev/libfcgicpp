// libfcgicpp is under the terms of the GNU Lesser General Public License
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
	case FCGI_STDOUT:
	case FCGI_STDERR:
	case FCGI_DATA:
	case FCGI_GET_VALUES:
	case FCGI_GET_VALUES_RESULT:
	default:
		stringstream text;
		text << "Could not resolve body with type " << this->head.getType();
		BOOST_THROW_EXCEPTION(HeadException(text.str()) << bad_number(this->head.getType()));
		break;
	}
	this->body = NULL;
	this->padding.resolve_padding(str, this->head.getPaddingLength());
}