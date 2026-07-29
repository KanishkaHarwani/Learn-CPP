# Solution – `ex02_signed_unsigned_pitfalls.cpp`

## Objective

Explore common pitfalls when working with signed and unsigned integer types in C++. The exercise demonstrates how unsigned arithmetic behaves differently from signed arithmetic, particularly with overflow and comparisons.

---

## Solution

### 1. Unsigned Countdown Loop

```cpp
for (unsigned int i = 5; i >= 0; i--) {
    std::cout << "i = " << i << '\n';

    // Stop after wraparound to avoid an infinite loop.
    if (i > 5) {
        break;
    }
}
```

---

### 2. Signed vs. Unsigned Overflow

```cpp
int value = INT_MAX;
std::cout << "3) int max = " << value << '\n';
std::cout << "3) int max + 1 = " << value + 1 << '\n';

unsigned int uvalue = UINT_MAX;
std::cout << "4) unsigned max = " << uvalue << '\n';
std::cout << "4) unsigned max + 1 = " << uvalue + 1 << '\n';
```

---

## Explanation

### Unsigned Countdown

At first glance, the loop appears to count down from `5` to `0`:

```text
5
4
3
2
1
0
```

However, `unsigned int` can never store negative values. When `i` reaches `0` and is decremented, it wraps around to the largest representable unsigned value instead of becoming `-1`.

For a typical 32-bit `unsigned int`:

```text
0
↓
4294967295
```

Since every unsigned integer is greater than or equal to `0`, the condition

```cpp
i >= 0
```

is always true.

Without the `break` statement, the loop would continue indefinitely.

---

### Signed Integer Overflow

`INT_MAX` represents the largest value that can be stored in an `int`.

Attempting to compute

```cpp
INT_MAX + 1
```

causes **signed integer overflow**.

Unlike unsigned integers, signed overflow is **undefined behavior** in C++. The language standard does not specify what must happen. Different compilers, optimization levels, or systems may produce different results.

Although many systems appear to wrap the value to `INT_MIN`, this behavior should never be relied upon.

---

### Unsigned Integer Overflow

Unsigned integer arithmetic is different.

When an unsigned integer exceeds its maximum value, it wraps around to `0`. This behavior is **well-defined** by the C++ standard and occurs modulo `2^N`, where `N` is the number of bits in the type.

For example:

```text
UINT_MAX + 1
```

becomes

```text
0
```

on every conforming C++ implementation.

---

## Expected Output

The exact values may vary depending on the platform, but a typical run will resemble:

```text
i = 5
i = 4
i = 3
i = 2
i = 1
i = 0
i = 4294967295

3) int max = 2147483647
3) int max + 1 = -2147483648   // Example only; result is undefined.

4) unsigned max = 4294967295
4) unsigned max + 1 = 0
```

---

## Key Takeaways

- Unsigned integers cannot represent negative values.
- Decrementing `0` for an unsigned type wraps around to the maximum representable value.
- A loop using an unsigned variable with the condition `>= 0` never terminates.
- Signed integer overflow is **undefined behavior** and should always be avoided.
- Unsigned integer overflow is **well-defined** and wraps around modulo `2^N`.
- Be careful when mixing signed and unsigned types, as implicit conversions can produce unexpected results.
