# Overview of project
2048 AI using expectimax and montecarlo policy (two separate algorithms)

# Brief Description of the game
2048 is played on a plain 4×4 grid, with numbered tiles that slide when a player moves them using the four arrow keys. Every turn, a new tile randomly appears in an empty spot on the board with a value of either 2 or 4. Tiles slide as far as possible in the chosen direction until they are stopped by either another tile or the edge of the grid. If two tiles of the same number collide while moving, they will merge into a tile with the total value of the two tiles that collided. The resulting tile cannot merge with another tile again in the same move. Higher-scoring tiles emit a soft glow; the highest possible tile is 131,072.
(Cited from Wikipedia - https://en.wikipedia.org/wiki/2048_(video_game))

# How to run the code
### Git clone
```bash
git clone https://github.com/yshimizu20/2048_ai.git
git clone https://github.com/yshimizu20/2048_ai_cpp.git
```

### To run montecarlo or expectimax
```bash
cd 2048_ai_cpp/2048/
#to run montecarlo
make clean; make montecarlo; ./montecarlo;
#to run expectimax
make clean; make expectimax; ./expectimax;
```

### to run python experimentation code used to optimize heuristic values for expectimax
```bash
#switch to montecarlo testing branch
git checkout 01_test_algorithm
#switch to expectimax algorithm 01
git checkout 02_heuristics
#switch to expectimax algorithm 02
git checkout 03_heuristics02
#switch to expectimax algorithm 03 - same as c++ code algorithm
git checkout 04_heuristics_extensive_search

#to run code
cd 2048_ai/drivers; python3 main,py;
```

*To access the code/commits during the experimentation, please refer to https://github.com/yshimizu20/2048_ai.


# Algorithms
### Challenges of the game
High branching factor based on stocasity
The worst state complexity = (4*32)^depth -> not suitable for MCTS

### Solution
The bottleneck of solving the game is the branching factor and the large state space.
The two algorithms implemented here are effective in evaluating an action without requiring large amounts of data stored.

##### Algorithm 1: Montecarlo
```bash
#pseudocode
For each iteration:
    For each state after performing "up", "down", "left", "right" on state:
        100-500 random playouts until game over from each state
    Make 1 move among "up" "down" "left" "right" with highest EV
```

##### Algorithm 2: Expectimax
```bash
#pseudocode
For each iteration:
    Make complete expectimax tree of all possible states within 3 moves and find the heuristic value of all depth=0 states
    Evaluate which depth=2 state has the highest expectation heuristic value 2 layers below
    Make move out of "up" "down" "left" "right" with highest expectimax EV
```

The expectimax algorithm required a lot of parameter/heuristic tuning. I noted the process of the optimization in the “Approach” column in this document.


# Evaluating the results
The performance of algorithms were evaluated using the ratio of the biggest tile achieved in each game. A random agent will usually perform between 128 and 256.

# Results for Montecarlo
Ran 500 games each for 100/300/500 playouts per move (for up, down, left, right from each given state), and measured the algorithm by the number of the largest tile on the board. For the 500 playouts per move case, each move takes 0.1 seconds, and a game takes 30 seconds to 1 minute to run.

| Largest tile # | 100 playouts | 300 playouts | 500 playouts |
|----------------|--------------|--------------|--------------|
| 512            | 1            | 0            | 0            |
| 1024           | 63           | 42           | 12           |
| 2048           | 436          | 458          | 477          |
| 4096           | 0            | 0            | 11           |



# Results for Expectimax
Ran 500 games with the depth 3 expectimax algorithm on the zoo. Each move takes around 0.2-0.3 seconds, and a game lasts around 5 minutes. Running depth 4 expectimax was very very slow even with c++ code.

| Largest tile # | depth=3      |
|----------------|--------------|
| 512            | 2            |
| 1024           | 67           |
| 2048           | 429          |
| 4096           | 2            |


# Github
https://github.com/yshimizu20/2048_ai
https://github.com/yshimizu20/2048_ai_cpp
*I implemented everything on the first github repo, and since it was virtually impossible to run hundreds of tests in Python, I rewrote the code in c++ in the second repo. Thus, although the second repo is cleaner and more organized, all the experimentation and optimization steps are stored in the first repo.

# Approach
In the branches of https://github.com/yshimizu20/2048_ai

```bash
#montecarlo01 branch
git checkout 01_test_algorithm
```
### Basically Montecarlo algorithm but only 5-20 round * 200-800 playouts
Best moved decided by the highest average scoring move after 10-20 rounds
Results are stored in the backend/results directory. The first number is the number of rounds and the second number is the number of playouts. As you can see, most of the results are 1024.
Doing full-game playouts was virtually impossible using python3 (not pypy3 since I implemented using numpy) and this was one of the reasons I decided to reimplement everything using c++. Turned out, full-game playouts enabled with c++ drastically improved the algorithm.

```bash
#expectimax algorithm 01
git checkout 02_heuristics
```
### Implemented the montecarlo policy with heuristics
Instead of just calculating the 2048 game score after 5-10 depths playouts, set some heuristics to evaluate the board so that it would play similar to how I play.
The heuristics I used here was “number of empty cells” and “steady increment.” Good heuristics if tiles in all rows/cols were increasing towards the same direction.
Although I did not test it thoroughly, this algorithm achieved 2048 around 40% of the time, and the other 60% was 1024.
From here, I start tuning the parameters and the heuristics which leads to the next branch.

```bash
#expectimax algorithm 02
git checkout 03_heuristics02
```
### Searching for a better heuristic algorithm
Added a “proximity” heuristic, that is, for each tile, find the adjacent tile whose tile difference is smaller than any other adjacent tile, and sum it up. The biggest the sum is, the worse the board state. This reduces the probability of game over since proximity == easier for the tiles to merge and create a bigger number and open up a space.
Changed the “steady increment” heuristic so that it would incorporate the “snake method” explained here. To do this, I changed the steady increment heuristic to allow different increment directions for each row/col. Originally, the algorithm was penalizing the snake method, but this way, the algorithm will no longer penalize the snake method.
This algorithm achieved 2048 arund 40%, 4096 around 50% and 1024 around 10%.

```bash
#expectimax algorithm 03 - same as c++ code algorithm
git checkout 04_heuristics_extensive_search
```

### Searching for a better tree traversing algorithm
Originally, the algorithm was doing 200 random playouts for depth=8 and applying the heuristic function to the resulting states. Instead, getting hints from my cribbage algorithm implementation, I decided to explore every possible state reachable in depth=3, and weighing it with the probability of reaching the state (since 2048 is a stochastic game), found the move with the highest expected heuristic value. This turned out to be the greatest modification and now, the algorithm reaches 8192 85% of the time.

Finally, to test the results running 500 rounds, it was virtually impossible to do it with python, and since I was studying c++ in the meanwhile, decided to rewrite everything using c++.
