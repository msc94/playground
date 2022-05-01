import random
import sys

class Node:
  def __init__(self):
    self.names = []
    self.adjacency_list = []

def node_with_name(G, name):
  for node in G:
    if name in node.names:
      return node

def delete_node_with_name(G, name):
  return [n for n in G if name not in n.names]

def mincut(G):
  if len(G) == 2:
    return G

  firstnode = G[random.randint(0, len(G) - 1)]
  al = firstnode.adjacency_list
  secondname = al[random.randint(0, len(al) - 1)]
  secondnode = node_with_name(G, secondname)

  # print(f"Deleting edge ({firstnode.names[0]}, {secondnode.names[0]})")

  G = delete_node_with_name(G, firstnode.names[0])
  G = delete_node_with_name(G, secondnode.names[0])

  merged = Node()
  merged.names = firstnode.names + secondnode.names

  # Delete self loops
  merged.adjacency_list = [
    n for n in firstnode.adjacency_list + secondnode.adjacency_list
    if n not in merged.names
  ]

  G.append(merged)

  return mincut(G)

G = []

with open("kargermincut.txt", "r") as f:
  for s in f:
    node = Node()
    for i, k in enumerate(s.split("\t")):
      if i == 0:
        node.names.append(int(k))
      elif k != "\n":
        node.adjacency_list.append(int(k))
    G.append(node)

i = 0
m = sys.maxsize
while True:
  g = mincut(G)
  m = min([
    m,
    len(g[1].adjacency_list),
    len(g[0].adjacency_list)
  ])
  if i % 100 == 0:
    print(f"{m} ({i})")
  i = i + 1