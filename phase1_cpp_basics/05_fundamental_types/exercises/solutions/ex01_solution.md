# Solution – `ex01_sizeof_and_limits.cpp`

## Objective

Complete the exercise by adding the fixed-width integer types from `<cstdint>` and compare their sizes and ranges with the built-in C++ fundamental types.

---

## Solution

Add the following code after printing the built-in data types:

```cpp
std::cout << "These are the data types available with <cstdint>" << std::endl;
printInfo<int8_t>("int8_t");
printInfo<uint8_t>("uint8_t");
printInfo<int32_t>("int32_t");
std::cout << std::endl;
```

---

## Explanation

The `<cstdint>` header provides integer types with guaranteed widths. Unlike the built-in types (`int`, `long`, etc.), these types have a fixed number of bits regardless of the platform (provided the implementation supports them).

The added code prints:

- The size of each type using `sizeof`
- The minimum value using `std::numeric_limits<T>::min()`
- The maximum value using `std::numeric_limits<T>::max()`

The existing `printInfo()` template works for any type, so no additional functions are required.

---

## Comparison

| Type | Description | Expected Size |
|------|-------------|--------------:|
| `int8_t` | Signed 8-bit integer | 1 byte |
| `uint8_t` | Unsigned 8-bit integer | 1 byte |
| `int32_t` | Signed 32-bit integer | 4 bytes |

These can be compared with the built-in types printed earlier:

- `short`
- `int`
- `long`
- `long long`
- `unsigned int`

Depending on the operating system and compiler, the sizes of the built-in types may differ, while the fixed-width types always represent the specified number of bits.

---

## Example Output

```
These are the data types available with <cstdint>

int8_t | size: 1 bytes | min: ... | max: ...
uint8_t | size: 1 bytes | min: ... | max: ...
int32_t | size: 4 bytes | min: -2147483648 | max: 2147483647
```

(The exact formatting and values displayed depend on the implementation.)

---

## Key Takeaways

- `sizeof` returns the memory occupied by a type in bytes.
- `std::numeric_limits` provides the minimum and maximum values for a type.
- Built-in integer types (`int`, `long`, etc.) have implementation-defined sizes.
- Fixed-width integer types from `<cstdint>` provide predictable sizes, making them useful for binary file formats, networking, embedded systems, and cross-platform programming.
