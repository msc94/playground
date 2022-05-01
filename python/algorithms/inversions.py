# Inversions: 1 + 3 + 2 + 1 = 7
a = [12, 36, 24, 2, 43, 21]

def countsplitandmerge(s1, s2):
  r = []
  s = 0

  while True:
    if len(s1) == 0 and len(s2) == 0:
      break
    if len(s1) == 0:
      r.append(s2.pop(0))
      continue
    if len(s2) == 0:
      r.append(s1.pop(0))
      continue
    if s1[0] < s2[0]:
      r.append(s1.pop(0))
      continue
    s += len(s1)
    r.append(s2.pop(0))
    
  return (r, s)


def inversions(a):
  if len(a) <= 1:
    return (a, 0)
  
  half = int(len(a) / 2)
  (s1, x) = inversions(a[:half])
  (s2, y) = inversions(a[half:])
  (s3, z) = countsplitandmerge(s1, s2)
  
  return (s3, x + y + z)

a = []
with open("IntegerArray.txt", "r") as f:
  for s in f:
    a.append(int(s))

res = inversions(a)
print(res[0])
print(res[1])