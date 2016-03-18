CXX 	 := g++
CXXFLAGS += -O3 -std=c++11 
OXLI=third-party/oxli
TIME=time

all: oxli_fasta spirit_fasta spirit_fasta_streamer
time: oxli_fasta_time spirit_fasta_time spirit_fasta_streamer_time cat_time

oxli_fasta: oxli_test.cpp common.hpp
	$(CXX) $(CXXFLAGS) -std=c++11 -o $@ -I $(OXLI)/include $< $(OXLI)/lib/liboxli.a

spirit_fasta: fasta_grammar.cpp common.hpp
	$(CXX) $(CXXFLAGS) -std=c++11 -o $@ $<

spirit_fasta_streamer: fasta_streamer.cpp common.hpp
	$(CXX) $(CXXFLAGS) -std=c++11  -o $@ $< -lboost_iostreams -lboost_system -lboost_filesystem

cat_time: test.fa
	rm -f out.fa
	$(TIME) cat test.fa > out.fa

oxli_fasta_time: oxli_fasta
	rm -f out.fa
	$(TIME) ./oxli_fasta > out.fa
#	diff test.fa out.fa
	
spirit_fasta_time: spirit_fasta
	rm -f out.fa
	$(TIME) cat test.fa | ./spirit_fasta > out.fa
#	diff test.fa out.fa

spirit_fasta_streamer_time: spirit_fasta_streamer
	rm -f out.fa
	$(TIME) cat test.fa | ./spirit_fasta_streamer > out.fa
