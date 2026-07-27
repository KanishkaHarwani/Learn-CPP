# Solution

## 1. Tool used

**Valgrind**

Command used:

```bash
g++ -g ex03_valgrind_leak.cpp -o ex03
valgrind --leak-check=full ./ex03
```

---

## 2. Relevant leak summary/report

Initial Valgrind output:

```text
==11770== HEAP SUMMARY:
==11770==     in use at exit: 160 bytes in 10 blocks
==11770==   total heap usage: 12 allocs, 2 frees, 73,888 bytes allocated

==11770== 160 (16 direct, 144 indirect) bytes in 1 blocks are definitely lost in loss record 2 of 2
==11770==    by 0x1091D2: buildList(int) (main.cpp:24)

==11770== LEAK SUMMARY:
==11770==    definitely lost: 16 bytes in 1 blocks
==11770==    indirectly lost: 144 bytes in 9 blocks
==11770==      possibly lost: 0 bytes in 0 blocks
==11770==    still reachable: 0 bytes in 0 blocks
```

Valgrind reported that memory allocated while building the linked list was never released.

---

## 3. Which allocation (line number) was never freed?

The leaked allocation occurred on the line containing:

```cpp
Node* n = new Node{i, head};
```

Each iteration of the loop allocated a new `Node` on the heap using `new`, but none of those nodes were deleted before `buildList()` returned.

---

## 4. How did you fix it?

I manually freed every node in the linked list before returning from `buildList()`.

### Original function

```cpp
void buildList(int count) {
    Node* head = nullptr;

    for (int i = 0; i < count; i++) {
        Node* n = new Node{i, head};
        head = n;
    }

    // Memory leak:
    // The linked list is never deleted.
}
```

### Fixed function

```cpp
void buildList(int count) {
    Node* head = nullptr;

    for (int i = 0; i < count; i++) {
        Node* n = new Node{i, head};
        head = n;
    }

    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}
```

### Explanation of the fix

The linked list was built by repeatedly allocating nodes with `new`, so every allocated node needed a corresponding `delete`.

The cleanup loop works as follows:

1. Store the current node in a temporary pointer.
2. Move `head` to the next node.
3. Delete the old node.
4. Repeat until `head` becomes `nullptr`.

This ensures that every dynamically allocated node is released exactly once.

A more modern C++ solution would be to use **smart pointers** (such as `std::unique_ptr`), which automatically free memory when it is no longer needed and help prevent memory leaks.

---

## 5. Verification after the fix

Running Valgrind again produced:

```text
==12020== HEAP SUMMARY:
==12020==     in use at exit: 0 bytes in 0 blocks
==12020==   total heap usage: 12 allocs, 12 frees, 73,888 bytes allocated

==12020== All heap blocks were freed -- no leaks are possible

==12020== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

This confirms that:

- Every allocation was matched with a corresponding `delete`.
- No memory leaks remain.
- Valgrind detected **0 memory errors**.

---

## Key Takeaways

- Every object created with `new` must eventually be released with `delete`.
- Losing the pointer to dynamically allocated memory causes a memory leak.
- Valgrind is an effective tool for identifying memory leaks and locating the allocation responsible.
- Traversing a linked list and deleting each node is the standard manual cleanup technique.
- Smart pointers can automate memory management and greatly reduce the risk of leaks in modern C++.
