#!/usr/bin/python

import doctest

"""
>>> add(1,2)
3
"""
def add(x, y):
    """
    >>> add(1,2)
    3
    """
    return x + y


if __name__ == '__main__':
    doctest.testmod()
