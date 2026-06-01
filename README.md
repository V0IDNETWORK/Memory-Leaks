# Preventing Memory Leaks in Modern C++

<div align="center">

![C++](https://img.shields.io/badge/C%2B%2B-Modern-blue?style=for-the-badge&logo=c%2B%2B)
![Memory Safety](https://img.shields.io/badge/Memory-Safe-success?style=for-the-badge)
![RAII](https://img.shields.io/badge/RAII-Core%20Concept-orange?style=for-the-badge)

# Modern C++ Memory Safety Guide

A deep dive into memory management, RAII, smart pointers, ownership models, and leak prevention techniques.

</div>

---

# Introduction

Memory leaks are one of the most dangerous problems in systems programming.

A C++ application may work perfectly during testing and still slowly destroy itself in production because of unmanaged memory growth.

This README explains how professional C++ developers prevent memory leaks using modern C++ practices.

---

# Why Memory Leaks Matter

Memory leaks can cause:

- Performance degradation
- Increased RAM usage
- Application instability
- Random crashes
- Resource exhaustion
- Long-term production failures

The most dangerous thing about memory leaks is that they are often silent.

---

# What Is a Memory Leak?

A memory leak happens when dynamically allocated memory is never released.

```cpp
void leak()
{
    int* data = new int[100];
}
```

The memory remains allocated even after the function exits.

---

# Avoid Raw `new` and `delete`

Bad:

```cpp
int* data = new int[100];
```

Better:

```cpp
std::vector<int> data(100);
```

Modern C++ containers manage memory automatically.

---

# RAII (Resource Acquisition Is Initialization)

RAII is one of the most important concepts in modern C++.

The idea:

- Objects acquire resources in constructors
- Objects release resources in destructors

```cpp
class File
{
private:
    FILE* file;

public:
    File(const char* path)
    {
        file = fopen(path, "r");
    }

    ~File()
    {
        if(file)
            fclose(file);
    }
};
```

This guarantees cleanup.

---

# Smart Pointers

## `std::unique_ptr`

```cpp
auto player = std::make_unique<Player>();
```

Single ownership. Recommended by default.

---

## `std::shared_ptr`

```cpp
auto texture = std::make_shared<Texture>();
```

Shared ownership across multiple systems.

---

## `std::weak_ptr`

```cpp
std::weak_ptr<Node> parent;
```

Used to avoid circular references.

---

# Circular References

```cpp
a->next = b;
b->next = a;
```

If both are `shared_ptr`, memory may never be released.

Use `weak_ptr` where ownership is not required.

---

# Exception Safety

Bad:

```cpp
void process()
{
    int* data = new int[100];

    riskyFunction();

    delete[] data;
}
```

Better:

```cpp
void process()
{
    auto data = std::make_unique<int[]>(100);

    riskyFunction();
}
```

---

# Memory Ownership Diagrams

## Stack vs Heap

```text
STACK MEMORY                    HEAP MEMORY
-------------------            -------------------
Automatic Lifetime             Manual / Managed Lifetime
Fast Allocation                Dynamic Allocation
Scope-Based Cleanup            Requires Ownership Model
Cache Friendly                 Flexible Lifetime
```

---

## Ownership Graph

```text
Application
    |
    +--> unique_ptr<Game>
              |
              +--> unique_ptr<Player>
              |
              +--> shared_ptr<Texture>
                         |
                  shared across systems
```

---

# Bad vs Good Examples

## BAD

```cpp
Player* player = new Player();
```

## GOOD

```cpp
auto player = std::make_unique<Player>();
```

---

# Example Project Structure

```text
/examples
    raw_pointer_leak.cpp
    unique_ptr_fix.cpp
    shared_ptr_cycle.cpp
    weak_ptr_solution.cpp
    raii_file_wrapper.cpp
    asan_demo.cpp
```

---

# Leak Detection Tools

## Valgrind

```bash
valgrind --leak-check=full ./app
```

## AddressSanitizer (ASan)

```bash
g++ -fsanitize=address -g main.cpp
```

## Visual Studio Diagnostic Tools

Useful for Windows debugging and memory inspection.

---

# GitHub Actions Example

```yaml
name: C++ Sanitizer Build

on: [push, pull_request]

jobs:
  build:
    runs-on: ubuntu-latest

    steps:
    - uses: actions/checkout@v4

    - name: Build with ASan
      run: |
        g++ -fsanitize=address -g main.cpp -o app
```

---

# Performance Comparison

| Method | Leak Safe | Performance | Complexity |
|---|---|---|---|
| Raw pointers | ❌ | Very Fast | Dangerous |
| unique_ptr | ✅ | Very Fast | Safe |
| shared_ptr | ✅ | Moderate | Flexible |
| weak_ptr | ✅ | Very Fast | Observer Only |

---

# Best Practices

Always prefer:

- Stack allocation
- RAII
- STL containers
- `unique_ptr`
- Automatic cleanup

Avoid unless necessary:

- Raw `new`
- Raw `delete`
- Naked owning pointers

---
