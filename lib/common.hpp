#ifndef BARF_COMMON_HH
#define BARF_COMMON_HH

#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/adapted/std_pair.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/fusion/include/io.hpp>
#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/support_istream_iterator.hpp>

namespace barf {

    namespace qi = boost::spirit::qi;
    namespace ascii = boost::spirit::ascii;
    namespace phoenix = boost::phoenix;

    char * DNA_SYMBOLS = "actgnACTGN";
}

#endif
