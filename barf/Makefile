test: badfasta extrarecord

noop:
	cat test.500.fasta | ./barf --sequence-model DNA cat > test.out.fa
	head test.out.fa

badfasta:
	cat badfasta.fa | ./barf --sequence-model DNA cat > test.out.fa

extrarecord:
	cat test.500.fasta | ./barf --sequence-model DNA ./fraudster.py > /dev/null
