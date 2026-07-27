# Mini Project — Bug Hunt

A small "inventory tracker" program with several bugs baked in on purpose.
The goal isn't to write new code — it's to practice the debugging toolkit
from this topic on something bigger than a single-bug exercise.

## What it does (once fixed)

Reads a list of items with quantities, lets you add/remove stock, and
prints a running total. Right now it has at least three bugs:

1. A crash when removing more stock than exists (array bounds issue).
2. A memory leak when items are removed (allocated memory never freed).
3. A silently wrong running total (logic bug — no crash, just bad output).

## How to work through it

1. Write `inventory.cpp` here implementing the description above (or use
   your own earlier exercise code as a starting point) and deliberately
   introduce the three bugs, OR pull in a buggy version if you already
   have one lying around from class/practice.
2. Compile with debug symbols: `g++ -g inventory.cpp -o inventory`
3. Bug 1 (crash): reproduce it, then find the exact line with
   `gdb ./inventory` + `run` + `backtrace`.
4. Bug 2 (leak): run under `valgrind --leak-check=full ./inventory` or
   rebuild with `-fsanitize=address` and check the report.
5. Bug 3 (wrong output, no crash): step through with `gdb` using
   `break`, `next`, and `print` on the running total until the value
   diverges from what you expect.
6. Fix each bug, and note in this README what the root cause was and
   which tool caught it.

## What I found (fill in after doing it)

- Bug 1 root cause:
- Bug 2 root cause:
- Bug 3 root cause:
- Which tool was most useful for each:

- # Mini Project — Bug Hunt

This project is designed to practice using debugging tools on a slightly larger program containing multiple independent bugs.

---

## Objective

The program implements a small inventory tracker that stores a list of items and their quantities. It intentionally contains three different types of bugs.

Your task is to locate, diagnose, and fix each bug using the appropriate debugging tool.

---

## Program Features

- Stores an inventory of items and quantities.
- Calculates a running inventory total.
- Removes stock from an item.
- Prints inventory information.

---

## Intentional Bugs

### Bug 1 — Crash

Removing more stock than exists results in a negative quantity.

That negative quantity is mistakenly used as an array index, eventually causing an out-of-bounds access and program crash.

**Recommended tool**

- GDB

Commands:

```bash
g++ -g inventory.cpp -o inventory
gdb ./inventory
```

Inside GDB:

```gdb
run
backtrace
```

Record:

- Exact line number
- Root cause

---

### Bug 2 — Memory Leak

When an item is removed, memory is dynamically allocated but never released.

The program finishes successfully, but memory remains allocated.

**Recommended tool**

Valgrind

```bash
valgrind --leak-check=full ./inventory
```

or

AddressSanitizer

```bash
g++ -g -fsanitize=address inventory.cpp -o inventory
./inventory
```

Record:

- Leak report
- Allocation line
- Fix

---

### Bug 3 — Wrong Running Total

The program calculates the running total incorrectly.

The program does **not** crash.

Instead, it silently produces an incorrect answer.

Use GDB to step through the calculation until the incorrect value appears.

Useful commands:

```gdb
break calculateTotal
run
next
print total
print i
```

Record:

- Expected total
- Actual total
- First incorrect iteration
- Root cause

---

## After Fixing

Answer the following.

### Bug 1

Root cause:

---

### Bug 2

Root cause:

---

### Bug 3

Root cause:

---

### Which debugging tool was most useful?

| Bug | Tool |
|------|------|
| Crash | |
| Memory Leak | |
| Wrong Output | |

---

## Learning Objectives

After completing this exercise you should be able to:

- Compile with debugging symbols (`-g`)
- Use GDB to locate crashes
- Read a backtrace
- Step through code with `next`
- Inspect variables with `print` and `info locals`
- Detect memory leaks with Valgrind or AddressSanitizer
- Distinguish between crashes, leaks, and logic errors
