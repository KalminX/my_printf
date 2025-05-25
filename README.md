# 🖨️ Custom `printf` Implementation in C

A custom implementation of the C Standard Library's `printf` function, supporting a subset of its features with width, precision, and multiple format specifiers.

## ✅ Supported Format Specifiers

| Specifier | Description                  |
|----------:|------------------------------|
| `%c`      | Print a single character     |
| `%s`      | Print a string               |
| `%%`      | Print a literal `%` symbol   |
| `%d`/`%i` | Signed integer               |
| `%u`      | Unsigned integer             |
| `%x`      | Unsigned hex (lowercase)     |
| `%o`      | Unsigned octal               |

### 🔧 Features

- Variable width and precision (`%8.3d`, `%.5s`, etc.)
- Supports padding (space and zero)
- Clean function-pointer-based handler design
- Modular and testable

---

## 📁 Project Structure

```

.
├── Makefile
├── main.c             # Optional: for ad-hoc testing
├── custom_printf.c        # Core printf logic
├── custom_printf.h        # Header file with declarations
└── tests.c            # Tests comparing `my_printf` vs `printf`

````

---

## 🛠️ Build Instructions

### Build the project:

```bash
make
````



## 🧪 Running Tests

You can run the test suite using:

```bash
make test
```

This compares your `my_printf()` implementation with the standard `printf()` output for multiple format combinations (including width and precision).

---

## 🧹 Clean Build

```bash
make clean
```

This removes the compiled object files and test binary.

---

## 💡 Example Output

```c
printf   : [%8.4d]
my_printf: [%8.4d]

printf   : [  0042]
my_printf: [  0042]
```

---

## ✍️ Author

**KalminX** – Budding systems-level C developer passionate about building cool stuff with tight, efficient code.

---

## 📄 License

This project is open source and free to use under the [MIT License](LICENSE).
