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
#ifndef HEADER_HPP
#define	HEADER_HPP

#include <sstream>

#include "Spec.hpp"

namespace fcgi {
    using namespace std;

    class Header {
    private:
        spec::Header head;
        bool empty;

    public:

        Header() {
            this->empty = true;
        }
        bool isEmpty() const {
            return this->empty;
        }
        void read(stringstream & stream);
    };
}

#endif	/* HEADER_HPP */