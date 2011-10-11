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