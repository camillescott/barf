#!/usr/bin/env python
from collections import namedtuple
import string
from screed.fasta import fasta_iter as parser

from sequencemodel import SequenceModel

FastaRecord = namedtuple('FastaRecord', ['header', 'sequence'])
HeaderModel = SequenceModel(string.printable)

def FastaRecordModel(sequence_model, header_model=HeaderModel):

    def factory(header, sequence):
        header_model.checkValid(header)
        sequence_model.checkValid(sequence)

        return FastaRecord(header=header, sequence=sequence)

    return factory
            

def writer(fastaRecord):
    return '>{0}\n{1}\n'.format(fastaRecord.header, 
                                fastaRecord.sequence)
