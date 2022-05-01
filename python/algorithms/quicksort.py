import numpy as np
import math

PIVOT_TYPE = 2

def median(A):
    l = len(A)
    middle = int(l / 2) - 1 if l % 2 == 0 else int(l / 2)
    median = sorted([A[0], A[middle], A[l - 1]])[1]
    for i, v in enumerate(A):
        if v == median:
            return i
    return -1

assert(median([1, 2, 3, 4]) == 1)
assert(median([1, 2, 3]) == 1)

def pivot(A):
    if PIVOT_TYPE == 0:
        return 0
    if PIVOT_TYPE == 1:
        return len(A) - 1
    if PIVOT_TYPE == 2:
        return median(A)


def swap(A, a, b):
    if a == b:
        return
    tmp = A[a]
    A[a] = A[b]
    A[b] = tmp


def partition(A, pivotidx):
    swap(A, 0, pivotidx)
    i = 1
    for j in range(1, len(A)):
        if A[j] < A[0]:
            swap(A, j, i)
            i += 1
    swap(A, 0, i - 1)
    return i - 1


totalcomp = 0

def quicksort(A):
    if len(A) in [0, 1]:
        return A

    pivotidx = pivot(A)
    pivotidx = partition(A, pivotidx)

    global totalcomp
    totalcomp += len(A) - 1
    quicksort(A[:pivotidx])
    quicksort(A[pivotidx+1:])

A = []
with open("QuickSort.txt", "r") as f:
    for s in f:
        A.append(int(s))

ANP = np.array(A)

print(len(ANP))
quicksort(ANP)
print(ANP)
print(totalcomp)
