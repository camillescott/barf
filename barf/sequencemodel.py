#!/usr/bin/env python
import re
import string

class SequenceModel(object):

    def __init__(self, alphabet, flags=re.IGNORECASE):
        self.alphabet = alphabet
        self.pattern = re.compile(r'[{alphabet}]*$'.format(alphabet=alphabet),
                                  flags=flags)

    def __str__(self):
        return 'SequenceModel<{0}>'.format(self.alphabet)

    def checkValid(self, data):
        if self.pattern.match(data) is None:
            raise AssertionError('{0} failed to match "{1}"'.format(self, data))

dnaModel = SequenceModel('ACGT')
dnanModel = SequenceModel('ACGTN')
iupacModel = SequenceModel('ARNDCQEGHILKMFPSTWXVBZX')

models = {'DNA': dnaModel,
          'DNA+N': dnanModel,
          'IUPAC': iupacModel}
