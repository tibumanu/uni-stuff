import random
import queue
from collections import deque


class DirectedGraph:
    def __init__(self):
        self.nodesIn = {}
        self.nodesOut = {}
        self.edges = {}

    def countNodes(self):
        return len(self.nodesIn)

    def countEdges(self):
        return len(self.edges)

    def addNode(self, node):
        if not (node in self.nodesIn):
            self.nodesIn[node] = []
            self.nodesOut[node] = []
            return True
        else:
            return False

    def removeNode(self, node):
        if not (self.checkNode(node)):
            return False
        for each in self.nodesIn:  # remove, where necessary, our node as an inbound neighbour for all other nodes
            if self.checkEdge(node, each):
                self.nodesIn[each].remove(node)
        for each in self.nodesOut:  # same as above but for our node as an outbound neighbour
            if self.checkEdge(each, node):
                self.nodesOut[each].remove(node)
        del self.nodesIn[node]
        del self.nodesOut[node]
        return True

    def checkNode(self, node):
        if node in self.nodesIn:
            return True
        return False

    def checkEdge(self, node1, node2):
        try:
            n1 = self.nodesOut[node1]
        except KeyError:
            return False

        if node2 in self.nodesOut[node1]:
            return True
        return False

    def addEdge(self, node1, node2, weight):
        if not (node1 in self.nodesIn):
            return -1
        if not (node2 in self.nodesIn):
            return -2
        if self.checkEdge(node1, node2):
            return -3
        else:
            self.nodesIn[node2].append(node1)
            self.nodesOut[node1].append(node2)
            self.edges[(node1, node2)] = weight
            return True

    def removeEdge(self, node1, node2):
        if not (node1 in self.nodesIn):
            return -1
        if not (node2 in self.nodesIn):
            return -2
        if not (self.checkEdge(node1, node2)):
            return -3
        else:
            self.nodesOut[node1].remove(node2)
            self.nodesIn[node2].remove(node1)
            del self.edges[(node1, node2)]
            return True

    def getWeight(self, node1, node2):
        return self.edges[(node1, node2)]

    def setWeight(self, node1, node2, weight):
        self.edges[(node1, node2)] = weight

    def getInDegree(self, node):
        return len(self.nodesIn[node])

    def getOutDegree(self, node):
        return len(self.nodesOut[node])

    def parseOut(self, node):
        outbound = []
        for each in self.nodesOut[node]:
            outbound.append(int(each))
        outbound.sort()
        return outbound

    def parseIn(self, node):
        inbound = []
        for each in self.nodesIn[node]:
            inbound.append(int(each))
        inbound.sort()
        return inbound

    def parseNodes(self):
        nodes = []
        for each in self.nodesIn:
            nodes.append(each)
        nodes.sort()
        return nodes

    def __str__(self):
        string = ""
        for edgeStart in self.nodesOut:
            for edgeFinish in self.nodesOut[edgeStart]:
                string += str(edgeStart) + " --> " + str(edgeFinish) + ", weight " + str(self.edges[(edgeStart,
                                                                                                     edgeFinish)]) + "\n"
        return string

    # def PW2(self, nodeStart, NodeEnd):
    #     q = queue.Queue(9999999)
    #     x = -1
    #     y = -1
    #     visited = set()
    #     distancesDict = {}
    #     nextDict = {}
    #     q.put(NodeEnd)
    #     visited.append(NodeEnd)
    #     while y != NodeEnd:
    #         x = q.get()
    #         y = self.parseIn(x)[0]

    def reverseBFS(self, start, end):
        visited = {end}
        queue = deque([(end, [])])
        while queue:
            node, path = queue.popleft()
            if node == start:
                path.append(node)
                path.reverse()
                return path
            for neighbor in self.nodesIn[node]:
                if neighbor not in visited:
                    visited.add(neighbor)
                    queue.append((neighbor, path + [node]))
        return None
