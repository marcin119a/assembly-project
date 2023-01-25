import pandas as pd
import itertools

columns = ['a-bs', 'b-as', 's1', 's2', 'a', 'b', '?']
df = pd.read_csv('/puts_fasta_3.10.txt', sep=' ')
df.columns = columns
df.head()

from collections import defaultdict 


# Set to keep track of visited nodes of graph.
OVERLAP = 1
PAIR_B = 0
THE_BEST = 0 


def dfs(visited, graph, node, contig):  
    if node[PAIR_B] not in visited:
        #print (node)
        nodes = sorted(graph[node[PAIR_B]], key=lambda x: x[OVERLAP], reverse=True)
        ovcontigs.append((node[PAIR_B][node[OVERLAP]:]))

        if len(nodes) == 0:
          return contig
        #visited.add(nodes[0][0])
        visited.add(node[PAIR_B])
        visited_temp.add(node[PAIR_B])

        dfs(visited, graph, nodes[THE_BEST], contig)



# Driver Code
print("Following is the Depth-First Search")
nodes =[]
for key in graph:
  nodes.append(key)
contigss = []
visited = set() 
for node in nodes:
  visited_temp = set()
  ovcontigs = []
  contig = node
  dfs(visited, graph, (node, 0), contig)
  if len("".join(ovcontigs)) > 320:
    contigss.append("".join(ovcontigs))
  else:
    visited = visited.difference(visited_temp)
    
    
import textwrap
file = open('ouput3.fasta', 'w')
for i, conf in enumerate(contigss):
  r = f">read_{i}\n"
  for text in textwrap.wrap(conf, 60):
    r+= f"{text}\n"
  file.write(r)
file.close()
