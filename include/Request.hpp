// libfcgicpp is under the terms of the GNU Lesser General Public License
#ifndef REQUEST_HPP
#define	REQUEST_HPP

#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include "Connection.hpp"

using namespace boost;
using namespace boost::asio;

namespace fcgi {

	class Request : public enable_shared_from_this<Request> {
	private:
		Connection conn;

		Request(io_service &io_service);

	public:
		typedef shared_ptr<Request> pointer;
		static pointer create(io_service &io_service);

		inline const Connection & getConnection() {
			return this->conn;
		}
	};
}

#endif	/* REQUEST_HPP */