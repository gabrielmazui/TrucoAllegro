# Truco Allegro

![C Language](https://img.shields.io/badge/Language-C-blue?style=flat-square)
![Allegro](https://img.shields.io/badge/Framework-Allegro-red?style=flat-square)
![UFSM](https://img.shields.io/badge/Institution-UFSM-orange?style=flat-square)

## Overview

This is a **simple Truco card game** developed in **C** using the **Allegro 5** library, created as a **coursework project for the Algorithms and Programming course at UFSM**.
The project features:

* Real human voice sounds for characters
* Simple AI decisions based on **probability calculations** and **random choices**
* Interactive gameplay with mouse/keyboard controls
* Basic graphics and menus built with Allegro 5

> Note: The game is a work in progress and contains several known bugs.

---

## Gameplay

* Play against AI or other players (local multiplayer if implemented)
* AI decisions: evaluates probability and randomness to choose moves
* Sounds triggered for player actions and game events
* Simple menu system for starting a game, selecting characters, and quitting

---

## Requirements

* **C compiler** (GCC or equivalent)
* **Allegro 5** installed
* Windows or Linux compatible

---

## Compilation

```sh
gcc -o TrucoAllegro main.c game/*.c ui/*.c -lallegro -lallegro_image -lallegro_audio -lallegro_acodec -lallegro_font
```

> Adjust source files as needed. Ensure Allegro 5 is properly linked.

---

## Notes

* The project is intended for learning and experimentation with **Allegro 5**, **C**, and **basic AI logic**
* AI is simple: it does not cheat, it just calculates probabilities and makes random decisions

---

## Acknowledgements

* Voices recorded by friends and collaborators
* Based on the classic Brazilian Truco card game
* Developed as part of a **coursework project for the Algorithms and Programming course at UFSM**
