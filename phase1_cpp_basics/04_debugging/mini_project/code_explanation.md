# Code Explanation

This document explains how `inventory.cpp` is intended to work. It can be used alongside the program's output and debugging tools to understand where the program behaves incorrectly.

---

# Program Flow

```text
Start
  │
  ▼
Create inventory
  │
  ▼
Populate items
  │
  ▼
Print inventory
  │
  ▼
Calculate total stock
  │
  ▼
Remove stock
  │
  ▼
Print updated total
  │
  ▼
Free allocated memory
  │
  ▼
Exit
```

---

# 1. Inventory Structure

Each inventory item stores two pieces of information.

```cpp
struct Item {
    std::string name;
    int quantity;
};
```

Example:

| Item | Quantity |
|------|---------:|
| Apple | 10 |
| Banana | 15 |
| Orange | 8 |
| Milk | 12 |
| Bread | 20 |

---

# 2. Inventory Allocation

The inventory is dynamically allocated.

```cpp
Item* inventory = new Item[SIZE];
```

Memory layout:

```text
inventory
    │
    ▼

+----------------+
| Item 0         |
+----------------+
| Item 1         |
+----------------+
| Item 2         |
+----------------+
| Item 3         |
+----------------+
| Item 4         |
+----------------+
```

The inventory remains valid until it is released with

```cpp
delete[] inventory;
```

---

# 3. Initial Inventory

The program creates five items.

```text
Apple      10
Banana     15
Orange      8
Milk       12
Bread      20
```

Expected total quantity:

```text
10 + 15 + 8 + 12 + 20 = 65
```

---

# 4. Calculating the Running Total

The function

```cpp
calculateTotal()
```

iterates through every inventory item.

Expected execution:

```text
total = 0

Apple
total = 10

Banana
total = 25

Orange
total = 33

Milk
total = 45

Bread
total = 65
```

If the printed total is different, inspect this function first.

Useful GDB commands:

```gdb
break calculateTotal
run
next
print total
print i
```

---

# 5. Removing Stock

The program removes stock from one item.

Variables used:

```cpp
itemIndex
removeAmount
```

The selected item's quantity is reduced.

Example:

```text
Orange

Before: 8

Remove: 20

After: -12
```

A negative quantity usually indicates something has gone wrong.

---

# 6. Accessing the Inventory

Inventory elements should only be accessed using valid indexes.

Valid indexes are

```text
0
1
2
3
4
```

Any index outside this range produces undefined behavior.

Examples:

```text
inventory[2]
```

Valid.

```text
inventory[-1]
```

Invalid.

```text
inventory[10]
```

Invalid.

If the program crashes after removing stock, inspect the index being used.

Useful GDB commands:

```gdb
backtrace
print itemIndex
print inventory[itemIndex].quantity
```

---

# 7. Dynamically Allocated Objects

The program also creates another object dynamically.

```cpp
Item* removedItem = new Item;
```

Every allocation using

```cpp
new
```

must eventually be matched by

```cpp
delete
```

If it is not released, memory remains allocated after the program exits.

Valgrind reports this as a memory leak.

Useful command:

```bash
valgrind --leak-check=full ./inventory
```

---

# 8. Program Output

When the program is working correctly, you should expect something similar to:

```text
Inventory:
Apple : 10
Banana : 15
Orange : 8
Milk : 12
Bread : 20

Total Stock: 65

Updated Total: 45
```

---

# Debugging Checklist

## If the program crashes

Check:

- Array indexes
- Negative quantities
- GDB backtrace

Useful commands:

```gdb
run
backtrace
print itemIndex
print inventory[itemIndex].quantity
```

---

## If Valgrind reports a leak

Check:

- Every `new`
- Every `delete`
- Missing cleanup before program exit

Useful command:

```bash
valgrind --leak-check=full ./inventory
```

---

## If the output is incorrect

Step through the calculation.

Useful commands:

```gdb
break calculateTotal
run
next
print total
print i
```

Watch how `total` changes after each iteration.

---

# Summary

| Symptom | Likely Area to Inspect | Recommended Tool |
|----------|------------------------|------------------|
| Program crashes | Array indexing | GDB (`backtrace`) |
| Wrong total | `calculateTotal()` | GDB (`break`, `next`, `print`) |
| Memory leak | Dynamic allocations (`new`) | Valgrind / AddressSanitizer |

---

# Expected Learning Outcome

After completing this exercise, you should be able to:

- Trace a crash using GDB.
- Read a backtrace.
- Step through code and inspect variables.
- Identify logic errors by observing program state.
- Detect memory leaks using Valgrind or AddressSanitizer.
- Relate a program's output to the section of code responsible for producing it.
