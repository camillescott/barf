#include <iostream>
#include <string>
#include <iomanip>

#include <boost/spirit/include/qi_skip.hpp>
#include <boost/iostreams/device/mapped_file.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/fstream.hpp>

#include "common.hpp"

namespace barf {


    template <typename Iterator>
    struct fasta_parser : qi::grammar< Iterator, unsigned() > {
        
        fasta_parser() : fasta_parser::base_type(fasta) {
            using ascii::char_;
            using ascii::space;
            using qi::skip;
            using qi::_val;
            using qi::_1;
            using qi::eps;
            using qi::raw;
            using phoenix::ref;

            fasta = eps                 [_val = 0] 
                >> *('>' 
                >> raw[*~char_('\n')]        [std::cout << ">" << _1 << std::endl]
                >> '\n'
                >> raw[skip(space)[+char_(DNA_SYMBOLS)]]
                                        [std::cout << _1]
                    )                   [_val += 1]
                >> qi::eoi;
            
        }

        qi::rule< Iterator, unsigned() > fasta;
    };
}


int main(int argc, char **argv) {
    using namespace barf;
    namespace io = boost::iostreams;
    namespace fs = boost::filesystem;

    //fs::path file("test.fa");
    io::mapped_file_source mmap(argv[1]);
    
    typedef char const* IteratorType;
    typedef fasta_parser<IteratorType> parser;
    IteratorType it(mmap.data()), end(mmap.end());

    unsigned n_records = 0;
    parser g;

    bool result = qi::phrase_parse(it, end, g, qi::blank, n_records);
    if (!result) {
        std::cerr << "FAIL" << std::endl;
        exit(1);
    } else {
        std::cerr << "Parsed " << n_records << " records." << std::endl;
    }
    return 0;
}
