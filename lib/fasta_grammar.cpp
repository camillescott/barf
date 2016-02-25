#define BOOST_SPIRIT_DEBUG
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
            
            BOOST_SPIRIT_DEBUG_NODES((fasta)(record));
        }

        qi::rule<Iterator, FastaRecord() > record;
        qi::rule<Iterator, FastaVector() > fasta;
    };
}

int main() {
    using namespace barf;
    std::string input = ">a test fasta record\nATTTGCTGGAA\nAGCTCGAGCAATGC\n>test 2\nATCGGTAGGCTGA";
    
    typedef std::string::iterator iterator_type;
    typedef fasta_parser<iterator_type> parser;

    FastaVector data;
    iterator_type iter = input.begin();
    iterator_type end = input.end();
    parser g; // Our grammar

    bool ok = qi::phrase_parse(iter, end, g, qi::blank, data);

    std::cout << "original:\n" << input << std::endl << "*****" << std::endl;
    if (ok) {
        std::cout << "success (" << data.size() << " records)\n";
        for (auto i = data.begin(); i != data.end(); ++i) {
            std::cout << i->second << std::endl;
        }
    } else std::cout << "failed\n";

    if (iter != end)
        std::cout << "Remaining unparsed: '" << std::string(iter,end) << "'\n";
}

