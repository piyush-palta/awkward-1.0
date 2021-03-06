# BSD 3-Clause License; see https://github.com/jpivarski/awkward-1.0/blob/master/LICENSE

from __future__ import absolute_import

import sys

import pytest
import numpy

import awkward1

numba = pytest.importorskip("numba")

py27 = (sys.version_info[0] < 3)

def test_string():
    array = awkward1.Array(["one", "two", "three", "four", "five"], checkvalid=True)

    @numba.njit
    def f1(x, i):
        return x[i]

    assert f1(array, 0) == "one"
    assert f1(array, 1) == "two"
    assert f1(array, 2) == "three"

    if not py27:
        @numba.njit
        def f2(x, i, j):
            return x[i] + x[j]

        assert f2(array, 1, 3) == "twofour"
