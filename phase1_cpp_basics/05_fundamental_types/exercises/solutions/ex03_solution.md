# Solution – `ex03_casts_and_float_compare.cpp`

## Objective

Practice explicit type casting and understand why comparing floating-point values using `==` is unreliable. Implement a safe conversion from `double` to `int` by verifying that the value fits within the range of the `int` data type before performing the conversion.

---

## Solution

### Safe `double` to `int` Conversion

```cpp
void safeDoubleToInt(double value) {
    if (value < std::numeric_limits<int>::min() ||
        value > std::numeric_limits<int>::max()) {
        std::cout << "Error: value is outside the range of int.\n";
    }
    else {
        int converted = static_cast<int>(value);
        std::cout << "Converted value: " << converted << '\n';
    }
}
```

Call the function from `main()` after reading user input:

```cpp
std::cout << "\nEnter a decimal value: ";

double input_d;
std::cin >> input_d;

safeDoubleToInt(input_d);
```

---

## Explanation

### Implicit vs. Explicit Casting

The program first demonstrates two ways of converting a `double` to an `int`.

```cpp
double pi = 3.14159;

int truncated = pi;
```

This is an **implicit conversion**. The compiler automatically converts the `double` to an `int`, silently discarding the fractional part.

```cpp
int truncatedExplicit = static_cast<int>(pi);
```

This is an **explicit conversion** using `static_cast`. It produces the same result but clearly communicates that the conversion is intentional.

---

### Floating-Point Comparison

The exercise also demonstrates why comparing floating-point values with `==` is unreliable.

```cpp
double x = 0.1 + 0.2;

if (x == 0.3)
```

Although this appears mathematically correct, the comparison usually evaluates to `false`.

This happens because decimal values such as `0.1` and `0.2` cannot be represented exactly in binary floating-point format. Small rounding errors occur during storage and arithmetic, resulting in a value that is extremely close to `0.3`, but not exactly equal.

Instead of using `==`, the program uses:

```cpp
nearlyEqual(x, 0.3)
```

The `nearlyEqual()` function compares the absolute difference between two numbers against a small tolerance (`epsilon`), making it the preferred way to compare floating-point values.

---

### Safe Conversion Function

The TODO requires writing a function that safely converts a `double` to an `int`.

Before performing the conversion, the function verifies that the value lies within the valid range of the `int` type.

```cpp
if (value < std::numeric_limits<int>::min() ||
    value > std::numeric_limits<int>::max())
```

If the value is outside this range, an error message is printed and no conversion is performed.

Otherwise, the value is converted using

```cpp
static_cast<int>(value)
```

Although the conversion is safe with respect to the range, the fractional part is still discarded because converting from `double` to `int` truncates toward zero.

For example:

| Input | Output |
|-------:|-------:|
| `42.9` | `42` |
| `-7.8` | `-7` |
| `3.14159` | `3` |

---

## Expected Output

Example run:

```text
1) implicit double->int: 3
2) explicit static_cast: 3
3) 0.1 + 0.2 == 0.3 ? false
   0.1 + 0.2 = 0.3 (not exactly 0.3!)
   nearlyEqual check -> true

Enter a decimal value: 123.45
Converted value: 123
```

Example with an out-of-range value:

```text
Enter a decimal value: 1e20
Error: value is outside the range of int.
```

---

## Key Takeaways

- Implicit conversions happen automatically and may silently lose information.
- `static_cast` makes type conversions explicit and easier to understand.
- Converting a `double` to an `int` truncates the fractional part.
- Always verify that a value fits within the destination type before converting it.
- Comparing floating-point values with `==` is unreliable because of precision limitations.
- Use a tolerance-based comparison (such as `nearlyEqual()`) when checking floating-point values for equality.
```
