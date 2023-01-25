import pandas as pd
from collections import defaultdict
import textwrap
import argparse

parser = argparse.ArgumentParser(
    prog = 'Assembly project'
)
parser.add_argument('-f', '--filename_overlap')
parser.add_argument('-o', '--output_fasta')
parser.add_argument('-pm', '--percent_of_mismatches', type=float)
parser.add_argument('-size', '--minimal_size_contig', type=int)

args = parser.parse_args()


columns = ['a-bs', 'b-as', 's1', 's2', 'a', 'b', '?']
df = pd.read_csv(args.filename_overlap, sep=';')
df.columns = columns
df.head()

percent_of_mismatches = args.percent_of_mismatches


graph = defaultdict(set)
for i in df.index:
    if float(df.loc[i]['a-bs']) < percent_of_mismatches:
        graph[df.loc[i]['a']].add((df.loc[i]['b'], int(df.loc[i]['s1'])))

    if float(df.loc[i]['b-as']) < percent_of_mismatches:
        graph[df.loc[i]['b']].add((df.loc[i]['a'], int(df.loc[i]['s2'])))

# Set to keep track of visited nodes of graph.
OVERLAP = 1
PAIR_B = 0
THE_BEST = 0


def dfs(visited, graph, node, contig):
    if node[PAIR_B] not in visited:
        # print (node)
        nodes = sorted(graph[node[PAIR_B]], key=lambda x: x[OVERLAP], reverse=True)
        ovcontigs.append((node[PAIR_B][node[OVERLAP]:]))

        if len(nodes) == 0:
            return contig
        # visited.add(nodes[0][0])
        visited.add(node[PAIR_B])
        visited_temp.add(node[PAIR_B])

        dfs(visited, graph, nodes[THE_BEST], contig)


# Driver Code
print("Following is the Depth-First Search")
nodes = []
for key in graph:
    nodes.append(key)
contigss = []
visited = set()
for node in nodes:
    visited_temp = set()
    ovcontigs = []
    contig = node
    dfs(visited, graph, (node, 0), contig)
    if len("".join(ovcontigs)) > args.minimal_size_contig:
        contigss.append("".join(ovcontigs))
    else:
        visited = visited.difference(visited_temp)


if __name__ == "__main__":
    file = open(args.output_fasta, 'w')
    for i, conf in enumerate(contigss):
        r = f">read_{i}\n"
        for text in textwrap.wrap(conf, 60):
            r += f"{text}\n"
        file.write(r)
    file.close()
