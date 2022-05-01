

a = [1, 2, 3, 4, 5, 6, 7, 6]

def findmax(a):
  if len(a) < 2:
    return ("inc", -1)
  if len(a) == 2:
    return ("inc", -1) if a[1] > a[0] else ("dec", -1)

  s = int(len(a) / 2)
  r1 = findmax(a[:s])
  r2 = findmax(a[s:])

  if r1[0] == "":
    return ("", r1[1])
  elif r2[0] == "":
    return ("", r2[1])
  elif r1[0] == "inc" and r2[0] == "inc":
    return ("inc", -1)
  elif r1[0] == "dec" and r2[0] == "dec":
    return ("dec", -1)
  elif r1[0] == "inc" and r2[0] == "dec":
    return ("", a[s-1])


print(findmax(a))