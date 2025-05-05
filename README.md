
# Tank Battle Game - Advanced Topics in Programming (Spring 2025B)

**Authors:**  
- Ameer Ahmed - 324993690  
- Maya Khuri - 212719124  

---

## 📥 Input Format

The input consists of a map defined by a grid of characters. The first line contains two integers representing the **height** and **width** of the map.

Example:

```
height,width
############
# 1      2 #
####  ######
#          #
#  @    @  #
#####  #####
#          #
####  ######
#          #
############
```

### Legend:
- `#` → Wall  
- `@` → Mine  
- `1` → Player 1 Tank  
- `2` → Player 2 Tank  

---

## 📤 Output Format

The output file contains all game steps in a structured format.

### Example:

```
Game step: 0
Player 1 move: rotate right by 90 degrees
Player 2 move: forward

Game step: 1
Player 1 move: forward
Player 2 move: shoot
```

If a player attempts an invalid move, it will be indicated like this:

```
Bad step: Tank 1 can't shoot!
```

At the end of the game, the result will be printed:

```
Game Over! It's a tie due to time out!
```

Or:

```
Game Over! Player 1 won!
```

Or:

```
Game Over! Player 2 won!
```

---

## 🔧 Compilation & Execution

To compile the project, run:

```bash
make
```

To run the executable:

```bash
./tanks_game < input.txt >
```

