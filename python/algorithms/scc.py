import sys
import enum

class Color(enum.Enum):
  BLACK = 0
  GREY = 1
  WHITE = 2

class Node():
  def __init__(self, name):
    self.adjacency_list = []
    self.name = name
    self.color = Color.WHITE

leader = -1
nodelist = []


def dfs(G, node):
  queue = [node]

  while len(queue) > 0:
    v = queue[0]
    # print(f"Start node {v.name}")

    if v.color == Color.WHITE:
      v.color = Color.GREY
      for n in v.adjacency_list:
        g = G[n]
        if g.color == Color.WHITE:
          queue.insert(0, g)
    else:
      # Node already seen
      if v.color == Color.GREY:
        # print(f"Finish node {v.name}")
        if nodelist is not None:
          nodelist.insert(0, v.name)
        if leader != -1:
          v.leader = leader
      queue.pop(0)
    
G = dict()
G_rev = dict()

def backward():
  for node in G_rev.values():
    if node.color == Color.WHITE:
      dfs(G_rev, node)

def forward():
  for node_name in nodelist.copy():
    node = G[node_name]
    if node.color == Color.WHITE:
      global leader
      leader = node.name
      dfs(G, node)

with open("scc.txt", "r") as f:
  for line in f:
    split = line.split(" ")
    first = int(split[0])
    second = int(split[1])

    G.setdefault(first, Node(first)).adjacency_list.append(second)
    G.setdefault(second, Node(second))

    G_rev.setdefault(second, Node(second)).adjacency_list.append(first)
    G_rev.setdefault(first, Node(first))
    
print("Done with reading")

backward()
print("Done with backward pass")
forward()
print("Done with forward pass")

leader_dict = dict()
for node in G.values():
  leader_dict.setdefault(node.leader, []).append(node)

with open("result.txt", "w") as f:
  for i, v in leader_dict.items():
    f.write(f"{i} has {len(v)} items")