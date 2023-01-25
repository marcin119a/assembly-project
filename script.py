from collections import defaultdict
import textwrap
import argparse
import csv


parser = argparse.ArgumentParser(
    prog = 'Assembly project'
)
parser.add_argument('-f', '--filename_overlap')
parser.add_argument('-o', '--output_fasta')
parser.add_argument('-pm', '--percent_of_mismatches', type=float)
parser.add_argument('-size', '--minimal_size_contig', type=int)

args = parser.parse_args()


percent_of_mismatches = args.percent_of_mismatches
S1 = 2
S2 = 3
A = 4
B = 5
ABS = 0
BAS = 1

graph = defaultdict(set)
with open(args.filename_overlap, newline='\n') as csvfile:
    reader = csv.reader(csvfile, delimiter=';', quotechar='|')

    for row in reader:
        if float(row[ABS]) < percent_of_mismatches:
            graph[row[A]].add((row[B], int(row[S1])))

        if float(row[BAS]) < percent_of_mismatches:
            graph[row[B]].add((row[A], int(row[S2])))




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
minimal_size_contig = args.minimal_size_contig
visited = set()
for node in nodes:
    visited_temp = set()
    ovcontigs = []
    contig = node
    dfs(visited, graph, (node, 0), contig)
    if len("".join(ovcontigs)) > minimal_size_contig:
        contigss.append("".join(ovcontigs))
    else:
        visited = visited.difference(visited_temp)


if __name__ == "__main__":
    file = open(f"{percent_of_mismatches}_{minimal_size_contig}_{args.output_fasta}", 'w')
    for i, conf in enumerate(contigss):
        r = f">read_{i}\n"
        for text in textwrap.wrap(conf, 60):
            r += f"{text}\n"
        file.write(r)
    file.close()
