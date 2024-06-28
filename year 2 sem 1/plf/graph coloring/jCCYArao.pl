% graph below
% Nodes = [1, 2, 3, 4, 5].
% Colors = [1, 2, 3].

adjacent(1, 2).
adjacent(2, 1).

adjacent(2, 3).
adjacent(3, 2).

adjacent(3, 4).
adjacent(4, 3).

adjacent(3, 5).
adjacent(5, 3).

adjacent(1, 4).
adjacent(4, 1).

adjacent(1, 3).
adjacent(3, 1).


conflictingColor(Node, Color, Coloring):-
    member((AdjNode, Color), Coloring),
    adjacent(Node, AdjNode).

colorNodes([], _, Coloring, Coloring).
colorNodes([Node|NodesRest], ColorsList, PartialColoring, Coloring):-
    member(Color, ColorsList), 
    \+ conflictingColor(Node, Color, PartialColoring),
    colorNodes(NodesRest, ColorsList, [(Node, Color)|PartialColoring], Coloring).

colorMain(Nodes, ColorList, Coloring):-
    colorNodes(Nodes, ColorList, [], Coloring).



