# Solution

## 1. What value did you expect `total` to be at the end, and what did it actually turn out to be before the fix?

Expected:

```text
1 + 2 + 3 + 4 + 5 = 15
```

Actual output before the fix:

```text
10
```

The incorrect result was found by stepping through the function using GDB and inspecting the local variables with:

```gdb
step
info locals
```

---

## 2. At which loop iteration did the value first diverge from what you expected? How did you find that iteration (which gdb commands)?

The value first diverged when the loop finished after `i = 4`. The program should have executed one more iteration with `i = 5`, but instead exited the loop, leaving `total` equal to `10`.

The issue was identified by stepping through each iteration and monitoring the local variables.

Commands used:

```gdb
break main
run
step
info locals
```

Relevant GDB output:

```text
Breakpoint 1, sumUpTo (n=5) at main.cpp:17
17          int total = 0;

(gdb) step
20          for (int i = 1; i < n; i++) {

(gdb) step
21              total += i;

(gdb) info locals
i = 1
total = 0

(gdb) step
20          for (int i = 1; i < n; i++) {

(gdb) info locals
i = 1
total = 1

(gdb) step
21              total += i;

(gdb) info locals
i = 2
total = 1

(gdb) step
20          for (int i = 1; i < n; i++) {

(gdb) info locals
i = 2
total = 3

(gdb) step
21              total += i;

(gdb) step
20          for (int i = 1; i < n; i++) {

(gdb) info locals
i = 3
total = 6

(gdb) step
21              total += i;

(gdb) info locals
i = 4
total = 6

(gdb) step
20          for (int i = 1; i < n; i++) {

(gdb) info locals
i = 4
total = 10

(gdb) step
23          return total;

(gdb) info locals
total = 10
```

---

## 3. What was the root cause?

The loop condition used `i < n` instead of `i <= n`, causing the final value (`n`) to be excluded from the sum.

---

## 4. How did you fix it?

Changed the loop condition from:

```cpp
for (int i = 1; i < n; i++)
```

to:

```cpp
for (int i = 1; i <= n; i++)
```

This includes the final iteration (`i = n`), producing the correct total of **15**.

---

## Key Takeaways

- Use `break` to pause execution at the desired function.
- Use `step` to execute the program one statement at a time.
- Use `info locals` (or `print variable`) to inspect variable values.
- Off-by-one errors are common loop bugs and are easy to identify by stepping through each iteration.
- Always verify loop bounds when a program produces an incorrect result without crashing.
