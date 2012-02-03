// libfcgicpp is under the terms of the GNU Lesser General Public License
#include "Request.hpp"

fcgi::Request::Request(io_service &io_service) : conn(io_service)
{
}

fcgi::Request::pointer fcgi::Request::create(io_service& io_service)
{
	return Request::pointer(new Request(io_service));
}