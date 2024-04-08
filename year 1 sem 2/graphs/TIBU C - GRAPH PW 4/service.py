import copy

from graph import *
from copy import deepcopy

INF = 99999

class Service:
    def __init__(self):
        self._graph = DirectedGraph()
        self._copies = []

    def getGraph(self):
        return self._graph

    def countNodes(self):
        return self._graph.countNodes()

    def countEdges(self):
        return self._graph.countEdges()

    def addNode(self, node):
        return self._graph.addNode(node)

    def removeNode(self, node):
        return self._graph.removeNode(node)

    def checkNode(self, node):
        return self._graph.checkNode(node)

    def checkEdge(self, node1, node2):
        return self._graph.checkEdge(node1, node2)

    def addEdge(self, node1, node2, weight):
        return self._graph.addEdge(node1, node2, weight)

    def removeEdge(self, node1, node2):
        return self._graph.removeEdge(node1, node2)

    def getWeight(self, node1, node2):
        return self._graph.getWeight(node1, node2)

    def setWeight(self, node1, node2, weight):
        return self._graph.setWeight(node1, node2, weight)

    def getInDegree(self, node):
        return self._graph.getInDegree(node)

    def getOutDegree(self, node):
        return self._graph.getOutDegree(node)

    def parseOut(self, node):
        return self._graph.parseOut(node)

    def parseIn(self, node):
        return self._graph.parseIn(node)

    def parseNodes(self):
        return self._graph.parseNodes()

    def makeCopy(self):
        self._copies.append(deepcopy(self._graph))

    def changeGraphToCopy(self):
        if len(self._copies) == 0:
            return False
        self._graph = self._copies[-1]
        self._copies.pop(-1)

    def __str__(self):
        return self._graph.__str__()

    def readGraph(self, filename: str):
        return readGraph(self._graph, filename)

    def writeGraph(self, filename: str):
        return writeGraph(self._graph, filename)

    def reverseBFSS(self, start, end):
        return self._graph.reverseBFS(start, end)

    def createRandomGraph(self, noNodes: int, noEdges: int):
        if createRandomGraph(noNodes, noEdges) == -1:
            return -1
        self._graph = createRandomGraph(noNodes, noEdges)


def readGraph(graph: DirectedGraph, filename: str):
    fin = open(filename, "rt")
    firstLine = fin.readline()
    firstLine = firstLine.split()
    noNodes = int(firstLine[0])  # number of nodes
    noEdges = int(firstLine[1])

    for line in fin:
        line = line.strip().split()
        node1, node2, weight = int(line[0]), int(line[1]), int(line[2])
        if not graph.checkNode(node1):
            graph.addNode(node1)
        if not graph.checkNode(node2):
            graph.addNode(node2)
        graph.addEdge(node1, node2, weight)
    fin.close()


def writeGraph(graph: DirectedGraph, filename: str):
    fout = open(filename, "wt")
    firstLine = str(graph.countNodes()) + " " + str(graph.countEdges()) + "\n"
    fout.write(firstLine)

    for edgeStart in graph.nodesOut:
        for edgeFinish in graph.nodesOut[edgeStart]:
            line = ""
            line += str(edgeStart) + " " + str(edgeFinish) + " " + str(graph.edges[edgeStart, edgeFinish]) + "\n"
            fout.write(line)
    fout.close()


def createRandomGraph(noNodes: int, noEdges: int):
    if noEdges > noNodes * (noNodes - 1):
        return -1
    graph = DirectedGraph()
    noEdgesTillNow = 0
    while noEdgesTillNow < noEdges:
        node1 = random.randint(1, noNodes)
        node2 = random.randint(1, noNodes)
        # while not graph.addNode(node1):
        #     node1 = random.randint(1, noNodes)
        # while not graph.addNode(node2):
        #     node2 = random.randint(2, noNodes)
        graph.addNode(node1)
        graph.addNode(node2)
        if graph.addEdge(node1, node2, random.randint(1, 100)) == True:
            noEdgesTillNow += 1
    return graph


def floydWarshall(graph: DirectedGraph, x, y):
    v = graph.countNodes()
    tempArr = []
    for i in range(v+1):
        tempArr.append(INF)
    matrix = [copy.deepcopy(tempArr) for i in range(v+1)]
    nextN = [copy.deepcopy(tempArr) for i in range(v+1)]
    for i in range(v+1):
        for j in range(v+1):
            if graph.checkEdge(i, j):
                matrix[i][j] = graph.getWeight(i, j)
                nextN[i][j] = j
            else:
                matrix[i][j] = INF
                nextN[i][j] = -1

    for k in range(1, v+1):
        for i in range(1, v+1):
            for j in range(1, v+1):
                if matrix[i][k] == INF or matrix[k][j] == INF:
                    continue
                if matrix[i][j] > (matrix[i][k] + matrix[k][j]):
                    matrix[i][j] = matrix[i][k] + matrix[k][j]
                    nextN[i][j] = nextN[i][k]

    # Now, the matrix is complete
    # Reconstructing the path...
    if nextN[x][y] == -1:
        return []
    path = [x]
    while x != y:
        x = nextN[x][y]
        path.append(x)
    return path

def prim(graph: DirectedGraph):
    no = graph.countNodes()
    nodes = graph.parseNodes()
    matrixC = [INF for _ in range(no+1)]
    matrixE = [-1 for _ in range(no+1)]
    result = []
    resultList = []
    cheapestCostYet = 99999
    cheapestNodeYet = -1
    for each in nodes:
        cheapestNode, cheapestCost = graph.cheapestNeighbour(each)
        matrixC[each] = cheapestCost
        matrixE[each] = cheapestNode
        if cheapestCost < cheapestCostYet:
            cheapestNodeYet = cheapestNode
            cheapestCostYet = cheapestCost

    while nodes:
        smallest = -1
        minCost = 99999
        for i in nodes:
            if matrixC[i] < minCost:
                smallest = i
                minCost = matrixC[i]
        cheapestNodeYet = smallest
        nodes.remove(cheapestNodeYet)
        result.append(cheapestNodeYet)
        resultList.append([cheapestNodeYet, matrixE[cheapestNodeYet]])
        for each in graph.parseIn(cheapestNodeYet):
            if graph.getWeight(cheapestNodeYet, each) < matrixC[each]:
                matrixC[each] = graph.getWeight(cheapestNodeYet, each)
                matrixE[each] = 1
                cheapestNodeYet = each
    return result, resultList



def getCheapestWalk(matrix, node1, node2):
    cost = matrix[node1][node2]
    if cost < 0:
        return -1
    walk = [[] for i in range(matrix[-1][-1])]
