# Ice Cream Shop GUI (Java AWT)

A desktop GUI application simulating an ice cream shop, built with Java's AWT library as a university assignment.

## What it does

- Displays a window representing an ice cream shop with dispensing apparatus
- Lets the user define custom ice cream flavours with names and colours
- Dynamically creates a button for each added flavour
- Manages flavour selection and tracks the current order

## Key concepts demonstrated

| Concept | Implementation detail |
|---------|-----------------------|
| AWT GUI | `Frame`, `Panel`, `Button`, `TextField`, `TextArea`, `Label` — no Swing |
| Layout management | `GridLayout` and `BorderLayout` for dynamic button grid and main window sections |
| Event handling | `ActionListener` attached to dynamically created flavour buttons |
| OOP design | `Sladoledzinica` (main window), `AparatZaTocenje` (dispenser), `Sladoled` (model), `Ukus` (flavour), `MestoZaTocenje` (slot) |
| Dynamic UI | Buttons created at runtime as flavours are added; layout revalidated |

## Building & running

```bash
javac *.java
java Sladoledzinica
```
