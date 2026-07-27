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


# Mini Project — Bug Hunt (Result)

This project combines the debugging techniques learned in this chapter into a single exercise. The program is a simple inventory tracker containing three intentionally introduced bugs: a crash, a memory leak, and a logic error.

## Objective

Use the appropriate debugging tools to identify, diagnose, and fix each bug.

## Program Features

- Stores a small inventory of items and their quantities.
- Calculates the total quantity of all items.
- Removes stock from an item.
- Displays the inventory and running total.

---

## Intentional Bugs

### Bug 1 — Crash

Removing more stock than an item contains results in a crash caused by an invalid array access.

**Recommended tool:** GDB

```bash
g++ -g inventory.cpp -o inventory
gdb ./inventory
```

Useful GDB commands:

```gdb
run
backtrace
```

---

### Bug 2 — Memory Leak

Memory is dynamically allocated while removing an item but is never released.

**Recommended tool:** Valgrind (or AddressSanitizer)

```bash
valgrind --leak-check=full ./inventory
```

or

```bash
g++ -g -fsanitize=address inventory.cpp -o inventory
./inventory
```

---

### Bug 3 — Wrong Running Total

The program runs successfully but produces an incorrect total quantity.

**Recommended tool:** GDB

Useful commands:

```gdb
break calculateTotal
run
next
print total
print i
```

---

## Workflow

1. Compile the program with debugging symbols.

   ```bash
   g++ -g inventory.cpp -o inventory
   ```

2. Use **GDB** to locate and fix the crash.

3. Use **Valgrind** (or **AddressSanitizer**) to detect and fix the memory leak.

4. Use **GDB** to step through the program and identify the incorrect running total.

5. Verify that all three bugs have been fixed.

---

# Results

## Bug 1

**Root cause:**

Removing more stock than available caused the item's quantity to become negative. That negative value was then used as an array index, resulting in an out-of-bounds array access and a crash.

**Tool used:**

GDB (`run` and `backtrace`)

**Fix:**

Check that the removal amount does not exceed the available quantity before subtracting, or validate the index before accessing the array.

---

## Bug 2

**Root cause:**

Memory allocated using `new` for `removedItem` was never released, producing a memory leak.

**Tool used:**

Valgrind (`--leak-check=full`)

**Fix:**

Release the dynamically allocated object with:

```cpp
delete removedItem;
```

A modern alternative would be to use `std::unique_ptr`, which automatically manages memory.

---

## Bug 3

**Root cause:**

The running total was calculated incorrectly because the loop added `1` for each inventory item instead of adding the item's quantity.

Incorrect code:

```cpp
total += 1;
```

Correct code:

```cpp
total += inventory[i].quantity;
```

**Tool used:**

GDB (`break`, `next`, `print`)

**Fix:**

Replace the incorrect increment with the item's quantity.

---

# Summary

| Bug | Tool Used |
|------|-----------|
| Crash | GDB |
| Memory Leak | Valgrind |
| Wrong Running Total | GDB |

---

## Learning Objectives

After completing this exercise, you should be able to:

- Compile programs with debugging symbols (`-g`).
- Use GDB to locate crashes with `backtrace`.
- Step through code using `break`, `next`, and `print`.
- Inspect variables during execution.
- Detect memory leaks with Valgrind or AddressSanitizer.
- Distinguish between runtime crashes, memory leaks, and logic errors.
- Select the appropriate debugging tool for different categories of bugs.
