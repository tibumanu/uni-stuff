from service import *


def printMenu():
    print(" 1. Get number of nodes")
    print(" 2. Print parsing of nodes")
    print(" 3. Check edge")
    print(" 4. Get degrees of given node")
    print(" 5. Print parsing of outbound neighbours of given node")
    print(" 6. Print parsing of inbound neighbours of given node")
    print(" 7. Get edge weight")
    print(" 8. Set edge weight")
    print(" 9. Add node")
    print("10. Remove node")
    print("11. Add edge")
    print("12. Remove edge")
    print("13. Make copy")
    print("14. Change graph to last copy made")
    print("15. Read from file")
    print("16. Write to file")
    print("17. Create random graph")
    print("18. Print graph")
    print("19. Check node")
    print("20. Shortest path - reverse BFS")
    print(" 0. Exit\n")


class UI:
    def __init__(self):
        self.service = Service()

    def startMenu(self):
        command = -1
        while command != '0':
            printMenu()
            command = input("What to do?       >")
            match command:
                case '0':
                    return
                case '1':
                    print("# of nodes: ", self.service.countNodes())
                case '2':
                    print(self.service.parseNodes())
                case '3':
                    node1 = int(input("First node: "))
                    node2 = int(input("Second node: "))
                    if self.service.checkEdge(node1, node2):
                        print("Edge exists")
                    else:
                        print("Edge does not exist")

                case '4':
                    node = int(input("Node: "))
                    print("Out-degree is", self.service.getOutDegree(node), ", in-degree is",
                          self.service.getOutDegree(node))
                case '5':
                    node = int(input("Node: "))
                    print(self.service.parseOut(node))
                case '6':
                    node = int(input("Node: "))
                    print(self.service.parseIn(node))
                case '7':
                    node1 = int(input("First node: "))
                    node2 = int(input("Second node: "))
                    if not self.service.checkEdge(node1, node2):
                        print("Edge does not exist")
                    else:
                        print("Weight is ", self.service.getWeight(node1, node2))

                case '8':
                    node1 = int(input("First node: "))
                    node2 = int(input("Second node: "))
                    if not self.service.checkEdge(node1, node2):
                        print("Edge does not exist")
                    else:
                        newWeight = int(input("New weight: "))
                        self.service.setWeight(node1, node2, newWeight)

                case '9':
                    node = int(input("Node: "))
                    if self.service.checkNode(node):
                        print("Node already exists")
                    else:
                        self.service.addNode(node)

                case '10':
                    node = int(input("Node: "))
                    if not self.service.checkNode(node):
                        print("Node does not exist")
                    else:
                        self.service.removeNode(node)

                case '11':
                    node1 = int(input("First node: "))
                    node2 = int(input("Second node: "))
                    weight = int(input("Weight: "))
                    output = self.service.addEdge(node1, node2, weight)
                    match output:
                        case -1:
                            print(f"\n\tFirst given node ({node1}) does not exit.\n")
                        case -2:
                            print(f"\n\tSecond given node ({node2})does not exist.\n")
                        case -3:
                            print(f"\n\tEdge {node1} --> {node2} already exists.\n")
                        case _:
                            print("Added edge")

                case '12':
                    node1 = int(input("First node: "))
                    node2 = int(input("Second node: "))
                    output = self.service.removeEdge(node1, node2)
                    match output:
                        case - 1:
                            print(f"\n\tFirst given node ({node1}) does not exit.\n")
                        case -2:
                            print(f"\n\tSecond given node ({node2})does not exist.\n")
                        case -3:
                            print(f"\n\tEdge {node1} --> {node2} does not exists.\n")
                        case _:
                            print("Removed edge")

                case '13':
                    self.service.makeCopy()
                    print("Made copy")

                case '14':
                    if not self.service.changeGraphToCopy():
                        print("No copy made yet")

                case '15':
                    filename = input("Filename: ")
                    self.service.readGraph(filename)

                case '16':
                    filename = input("Filename: ")
                    self.service.writeGraph(filename)

                case '17':
                    noNodes = int(input("# of nodes: "))
                    noEdges = int(input("# of edges: "))
                    if self.service.createRandomGraph(noNodes, noEdges) == -1:
                        print("Too many edges")

                case '18':
                    print(self.service.__str__())

                case '19':
                    node = int(input("Node: "))
                    print(self.service.checkNode(node))

                case '20':
                    start = int(input("Start node: "))
                    end = int(input("End node: "))
                    path = self.service.reverseBFSS(start, end)
                    print(f"length is {len(path)}, path is {path}")

                case '21':
                    start = int(input("Start node: "))
                    end = int(input("End node: "))
                    fW, cost = floydWarshall(self.service.getGraph(), start, end)
                    print("shortest path is ", fW, " and costs", cost)

                case _:
                    print("Invalid command")
