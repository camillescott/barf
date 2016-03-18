#!/usr/bin/env python

from pybloom import ScalableBloomFilter

class CollectionModel(object):

    def __init__(self, record_model):
        self.record_model = record_model
        self.collection = ScalableBloomFilter(mode=ScalableBloomFilter.SMALL_SET_GROWTH)

    def checkIn(self, data):
        self.record_model.checkValid(data)
        if data not in self.collection:
            raise AssertionError('{0} not in input collection!'.format(data))

    def add(self, data):
        self.record_model.checkValid(data)
        self.collection.add(data)
