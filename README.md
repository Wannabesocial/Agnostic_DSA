# C Data Structures Library (C11)

A type-agnostic Data Structures library implemented in C11\. Built with strict memory safety checks, unit tests, AddressSanitizer, and zero-warning compilation.


## Key Features 
- **Type-Agnostic / Generic**: Stores any data type (`int`, `struct`, pointers) using `void*` and shallow copy (`memcpy`).
- **Encapsulation**: Opaque pointer implementation hides internal structure details from the public API.
- **Robust Error Handling**: Almost all state-modifying functions return explicit status codes via enum.
- **Memory Safety &amp; Overflow Protection**: Proactive checks against `SIZE_MAX` integer overflows before allocation. Safe `realloc` usage prevents memory leaks on failure.
- **Non-Owning / Shallow Container**: The Data Structures manages its internal storage buffer; element lifetime management remains strictly with the caller.
- **Zero-Warning Pipeline**: Clean compilation under `-Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wsign-conversion -Wvla`.
- **Sanitizer Ready**: Built-in support for AddressSanitizer (`ASan`) and UndefinedBehaviorSanitizer (`UBSan`).


## Supported Data Structures
| Data Structure | Type          | Detailed Documentation        |
| :---           | :---          | :---                          |
| **Vector**     | Dynamic Array | [Vector Docs](docs/vector.md) |


## Global Build &amp; Testing
```bash
make                            # Builds all Modules
make 'module1' 'module2' ...    # Builds Specific Modules
make clean                      # Cleans build
```


## Main Directory Structure
```text
.
├── README.md
├── Makefile     # Build Pipeline
├── inc          # Public API Header
│   └── vector.h
├── src          # Implementation
│   └── vector.c
└── tests        # Unit Testing
    └── vector
        ├── test_vector.h
        ├── main_test.c
        ├── test_capacity.c
        ├── test_constructors.c
        ├── test_destructors.c
        ├── test_element_access.c
        └── test_modifiers.c
```