# Exercise — Debugging Log

A written companion to ex01–ex03. Instead of writing new code, this
one is about documenting your actual debugging process — the habit of
narrating what you're doing (and why) is half of what makes debugging
fast later on.

## Part 1 — Walk through ex01 (segfault) step by step

Fill this in while actually running `ex01_fix_segfault.cpp` under gdb.

1. Command used to compile with debug symbols:
2. Command(s) used to run it under gdb:
3. What did `backtrace` show right after the crash? (paste it)
4. Which exact line was the bug on?
5. What was the root cause, in one sentence?
6. How did you fix it?

## Part 2 — Walk through ex02 (silent wrong output)

Fill this in while stepping through `ex02_step_through_gdb.cpp`.

1. What value did you expect `total` to be at the end, and what did it
   actually turn out to be before the fix?
2. At which loop iteration did the value first diverge from what you
   expected? How did you find that iteration (which gdb commands)?
3. What was the root cause, in one sentence?

## Part 3 — Walk through ex03 (memory leak)

Fill this in while running `ex03_valgrind_leak.cpp` under valgrind or
with AddressSanitizer.

1. Tool used (valgrind or ASan):
2. Paste the relevant leak summary/report line(s):
3. Which allocation (line number) was never freed?
4. How did you fix it — manual `delete`, or would smart pointers avoid
   this entirely? (Note: smart pointers likely a later topic, but
   worth naming here if you already know about them.)

## Part 4 — Reflection

- Which of the three bugs would print-debugging have caught fastest,
  and which absolutely needed a real tool (gdb/valgrind/ASan)? Why?
- Write down the exact gdb command sequence you'd reach for first the
  next time a program segfaults, from memory, without looking it up.
- Any tool from notes.md you haven't tried yet (sanitizers, core dump
  loading, assertions)? Pick one and try it on any of the three
  exercises, then note what you saw.
