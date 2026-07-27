# Solution

## 1. Command used to compile with debug symbols

```bash
g++ -g main.cpp -o main
```

---

## 2. Command(s) used to run it under GDB

Start GDB:

```bash
gdb ./main
```

Inside GDB:

```gdb
run
```

After the crash:

```gdb
bt
```

---

## 3. What did `backtrace` show right after the crash?

```text
#0  0x0000555555555359 in main () at main.cpp:34
```

This indicates that the program crashed in `main()` on line 34.

---

## 4. Which exact line was the bug on?

The bug was on **line 34**, where the program attempted to access:

```cpp
std::cout << data[0] << std::endl;
```

after `data` had been set to `nullptr`.

---

## 5. What was the root cause?

The program dereferenced a null pointer by accessing `data[0]` after assigning `data = nullptr`, causing a segmentation fault.

---

## 6. How did you fix it?

I commented out the line that attempted to access `data[0]` after `data` had been set to `nullptr`. This prevented the null pointer dereference, allowing the program to terminate normally.

---

## Key Takeaways

- Compile with the `-g` flag to include debugging symbols.
- Use GDB to run the program and inspect crashes.
- The `bt` (backtrace) command shows where the program crashed.
- Dereferencing a null pointer results in undefined behavior and commonly causes a segmentation fault.
- Always ensure a pointer is valid before dereferencing it.
