# 🐍 Snake Game in C (SDL3 + Linked List)

A classic Snake game implemented in **C using the SDL3 graphics library**, with the snake body represented as a **linked list** and all movement, growth, and memory handled manually using pointers.

This project was built primarily as a learning exercise to understand low-level concepts like dynamic memory allocation, pointer management, and data structures in a real-time application.

---

## ✨ Features

- Grid-based Snake game
- Real-time movement using keyboard input
- Apple spawning and snake growth
- Collision detection (walls + self collision)
- Snake body implemented as a linked list
- Manual memory management using `malloc` and `free`
- Built using SDL3 for graphics and input handling

---

## 🧠 Why Linked List?

The snake could have been implemented using a simple array, but a **linked list was chosen intentionally** to:

- Practice dynamic memory allocation
- Understand pointer ownership and lifetime
- Learn how to grow and move a dynamic structure in real time
- Gain experience debugging low-level memory issues (segmentation faults, invalid frees, etc.)

This made the project more challenging, but also more educational.

---

## 🛠️ Tech Stack

| Component | Description |
|----------|-------------|
| Language | C |
| Graphics | SDL3 |
| Data Structure | Singly Linked List |
| Build Tool | GCC (MinGW on Windows) |
| Platform | Windows |

---

## 🎮 Controls

| Key | Action |
|-----|--------|
| ↑ | Move up |
| ↓ | Move down |
| ← | Move left |
| → | Move right |
| Close window | Quit game |

---
# Demo 

./demo.mp4


---

## ⚙️ Build Instructions

### 🔹 Prerequisites

- GCC (MinGW recommended on Windows)
- SDL3 installed and available in your include/lib path

---

### 🔹 Compile

```bash
gcc snake.c -o snake.exe -I "C:\MinGW\include\SDL3" -L "C:\MinGW\lib" -lSDL3  #change path for sdl if installed elsewhere

./snake.exe # to run compiled file 

```



### 🐍 Snake Representation
Each node represents one segment of the snake. The head is the first node.

### 🎮 Movement
* **Head:** Moves based on the current direction.
* **Body:** Each segment takes the position of the previous segment.

### 🍎 Growth
When the snake eats an apple:
1.  A new node is allocated using `malloc`.
2.  Inserted at the **head** of the list.
3.  The list grows dynamically.

### 💥 Collision Detection
* **Wall collision:** Checks if the head is outside the grid boundaries.
* **Self collision:** Checks if the head coordinates match any body segment.

### 💾 Memory Management
* All new snake segments are allocated dynamically on the **heap**.
* On game over, all heap memory is freed properly to prevent leaks.
* Stack memory is **not** freed manually.

---

### 🐞 Common Bugs Faced
This project involved a lot of debugging and learning, including:
* **Segmentation faults** due to incorrect `sizeof` in `malloc`.
* Attempting to free **stack memory** instead of heap memory.
* **Off-by-one errors** in boundary checks.
* Forgetting to seed the random number generator (`srand`).
* Snake growing into walls.
* Snake segments not appearing due to pointer mismanagement.

*All of these helped in understanding how sensitive low-level programming can be.*

### 📌 Learning Outcomes
* Stronger understanding of **pointers** and **memory management**.
* Hands-on experience with **linked lists** in real-time systems.
* Debugging segmentation faults and undefined behavior.
* Using **SDL3** for simple 2D graphics.
* Designing stateful systems in C.

