Games of peg solitaire take place on a board with an arrangement of holes and a number of pegs that occupy the holes. Usually all holes but one are occupied by pegs. In a single move the player takes a peg, jumps it over a neighboring peg, inserts it into a hole and removes the jumped over peg. Thus in each move the number of pegs reduces by one. The game terminates when no more moves are possible. The goal is to remove the maximum number of pegs. 
The code in this repository implements a backtracking algorithm that generates all solutions of a variant of solitaire peg known as the Cracker Barrel solitaire, shown in the photo.

![[Picture.png]]
The board has 15 ( = 1+2+3+4+5)  holes arranged in a triangular pattern, 14 of which are occupied by pegs. A single corner hole is left empty. The challenge is to remove all but one peg.
The code in the repository finds this sequence of moves: ![[Moves.png]]
