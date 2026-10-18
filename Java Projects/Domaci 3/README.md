# Whack-a-Mole Game (Java AWT + Threads)

An interactive whack-a-mole style game built with Java AWT and multithreading as a university assignment.

## What it does

- Renders a garden (game board) with holes where moles appear and disappear
- Moles move independently — each is driven by its own thread
- The player clicks on visible moles to score points and protect the garden's crops
- Three difficulty levels (Easy, Medium, Hard) control how fast moles appear and how long they stay visible
- A vegetable counter tracks how many crops the moles have destroyed
- The game ends when the crop count reaches zero or the player wins

## Key concepts demonstrated

| Concept | Implementation detail |
|---------|-----------------------|
| Multithreading | Each `Krtica` (mole) runs as a separate `Thread`; the garden (`Basta`) manages the thread pool |
| Thread synchronisation | Shared game state (crop count, active moles) protected against race conditions |
| AWT game loop | `Basta` extends `Canvas` and repaints on each thread tick |
| Event-driven input | `MouseListener` on the canvas detects clicks on mole positions |
| Difficulty via `CheckboxGroup` | Three radio-style checkboxes adjust thread sleep intervals |
| OOP hierarchy | `Zivotinja` base class → `Krtica` subclass; `Rupa` models each hole slot |

## Building & running

```bash
javac *.java
java Igra
```
