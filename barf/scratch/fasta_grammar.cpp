//#define BOOST_SPIRIT_DEBUG
#include <iostream>
#include <string>
#include <vector>
#include <utility>

#include <boost/spirit/include/qi_skip.hpp>
#include "common.hpp"

namespace barf {

    typedef std::pair<std::string, std::string> FastaRecord;
    typedef std::vector<FastaRecord> FastaVector;

    template <typename Iterator>
    struct fasta_parser : qi::grammar< Iterator, FastaVector() > {
        
        fasta_parser() : fasta_parser::base_type(fasta) {
            using ascii::char_;
            using qi::skip;
            using qi::lit;

            record = ( '>' >> *~char_('\n')
                >> '\n'
                >> skip(ascii::space)[+char_(DNA_SYMBOLS)] );

            fasta = *record >> qi::eoi;
            
            //BOOST_SPIRIT_DEBUG_NODES((fasta)(record));
        }

        qi::rule<Iterator, FastaRecord() > record;
        qi::rule<Iterator, FastaVector() > fasta;
    };
}

int main() {
    using namespace barf;

    typedef boost::spirit::istream_iterator IteratorType;
    std::cin.unsetf(std::ios::skipws);
    IteratorType it(std::cin), end;
 
    typedef fasta_parser<IteratorType> parser;

    FastaVector data;
    parser g;

    if (qi::phrase_parse(it, end, g, qi::blank, data)) {
        BOOST_FOREACH(FastaRecord const& record, data) {
            std::cout << ">" << record.first << std::endl << record.second << std::endl;
        }
    }
    else {
        std::cerr << "FAIL" << std::endl;
        exit(1);
    }
    return 0;
}

