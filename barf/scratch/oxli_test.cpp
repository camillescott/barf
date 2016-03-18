#include <oxli/read_parsers.hh>
#include <boost/spirit/include/qi.hpp>

#include <vector>
#include <iostream>

int main() {

    using namespace khmer;
    using namespace khmer::read_parsers;
    IParser * parser = IParser::get_parser ("test.fa");

    std::vector<Read> data;
    while(!parser->is_complete()) {
        try {
            data.push_back(parser->get_next_read());
        } catch (NoMoreReadsAvailable) {
            break;
        }
    }
    BOOST_FOREACH(Read const& record, data) {
        std::cout << ">" << record.name << std::endl << record.sequence << std::endl;
    }
    return 0;
}
