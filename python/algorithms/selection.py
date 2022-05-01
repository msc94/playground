import random
import numpy as np

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

# Gets the nth biggest element of A in O(n) time
def select(A, n):
    if len(A) == 1:
      assert(n == 1)
      return A[0]

    pivotidx = random.randint(0, len(A) - 1)
    pivotidx = partition(A, pivotidx)

    if pivotidx == n:
      return A[pivotidx]
    elif n > pivotidx:
      return select(A[pivotidx + 1:], n - pivotidx)
    return select(A[:pivotidx], n)


A = np.array([2, 3, 1, 4, 6, 5, 7])
assert(select(A, 0) == 1)
A = np.array([2, 3, 1, 4, 6, 5, 7])
assert(select(A, 2) == 3)
