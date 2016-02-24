#include <iostream>
#include <string>
#include <vector>

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>

#include "common.hpp"

namespace barf {

    namespace qi = boost::spirit::qi;
    namespace ascii = boost::spirit::ascii;

    struct fasta_record {
        std::string header;
        std::string sequence;
    };

}

BOOST_FUSION_ADAPT_STRUCT(
    barf::fasta_record,
    (std::string, header)
    (std::string, sequence)
)

namespace barf {

    template <typename Iterator, typename Skipper>
    struct fasta_parser : qi::grammar<Iterator, fasta_record(), Skipper> {
        
        fasta_parser() : fasta_parser::base_type(record) {
            using ascii::char_;
            using qi::lit;

            // The FASTA header
            header %= qi::lexeme[*(char_ - '\n')];
            sequence %= +(+char_(DNA_SYMBOLS)) >> *lit('\n') >> *char_(DNA_SYMBOLS);

            record %= '>'
                >> header
                >> '\n'
                >> sequence
                >> -lit('\n');

            //fasta %= *record;
        }

        qi::rule<Iterator, std::string()> header;
        qi::rule<Iterator, std::string(), Skipper> sequence;
        qi::rule<Iterator, fasta_record(), Skipper> record;
        //qi::rule<Iterator, std::vector<fasta_record>, ascii::space_type> fasta;
    };
}

int main() {
    using namespace barf;
    const std::string input = ">a test fasta record\nATTTGCTGGAAAGCTCGAGCAATGC\n";
    
    fasta_record data;

    typedef std::string::const_iterator iterator_type;
    typedef fasta_parser<iterator_type, qi::blank_type> parser;

    iterator_type iter = input.begin();
    iterator_type end = input.end();
    parser g; // Our grammar

    bool ok = qi::phrase_parse(iter, end, g, qi::blank, data);
    if (ok) std::cout << "success\n";
    else std::cout << "failed\n";

    if (iter != end)
        std::cout << "Remaining unparsed: '" << std::string(iter,end) << "'\n";
}

