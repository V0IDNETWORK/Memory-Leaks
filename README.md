# Preventing Memory Leaks in Modern C++

<div align="center">

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

Example:

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

Example:

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

Include:

```cpp
#include <memory>
```

---

# `std::unique_ptr`

Single ownership.

```cpp
auto player = std::make_unique<Player>();
```

Recommended by default.

---

# `std::shared_ptr`

Shared ownership.

```cpp
auto texture = std::make_shared<Texture>();
```

Useful when multiple systems need access to the same object.

---

# `std::weak_ptr`

Used to avoid circular references.

```cpp
std::weak_ptr<Node> parent;
```

---

# Circular References

Problematic example:

```cpp
a->next = b;
b->next = a;
```

If both are `shared_ptr`, memory may never be released.

Use `weak_ptr` when ownership is not required.

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

If `riskyFunction()` throws, memory leaks.

Better:

```cpp
void process()
{
    auto data = std::make_unique<int[]>(100);

    riskyFunction();
}
```

---

# STL Containers

Prefer:

- `std::vector`
- `std::array`
- `std::string`
- `std::map`
- `std::unordered_map`

Instead of manual memory management.

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
- Manual ownership transfer
- Naked owning pointers

---

