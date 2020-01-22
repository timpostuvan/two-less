import matplotlib as mpl
import matplotlib.pyplot as plt
import networkx as nx

def convert(n, x, y, z):
	return n * n * x + n * y + z


def less_2(x, y):
	cnt = 0
	for i in range(3):
		if(x[i] < y[i]):
			cnt += 1

	return (cnt >= 2)


def add_edges(G, n):
	for i in range(n):
		for j in range(n):
			for k in range(n):
				x = (i, j, k)
				num_x = convert(n, i, j, k)

				for i1 in range(n):
					for j1 in range(n):
						for k1 in range(n):
							y = (i1, j1, k1)
							num_y = convert(n, i1, j1, k1)

							if(less_2(x, y)):
								G.add_edge(num_y, num_x)


n = 3

G = nx.DiGraph()
add_edges(G, n)

pos = nx.layout.spring_layout(G)
#pos = nx.layout.circular_layout(G)


nodes = nx.draw_networkx_nodes(G, pos, node_color='blue')
edges = nx.draw_networkx_edges(G, pos, arrowstyle='->',arrowsize=10, width=2)

H = G.to_undirected()
print("Triangles:", nx.triangles(H, 0))
print("Edges:", H.number_of_edges())

plt.show()