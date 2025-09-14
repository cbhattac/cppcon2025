## Instructions to Compile

### LLVM-MINGW Environment Variable

Set the environment variable `LLVM_MINGW_ROOT` to the root directory of your LLVM-Mingw installation. For example:

```
set LLVM_MINGW_ROOT=C:\work\projects\llvm-mingw-20250709\llvm-mingw-20250709-ucrt-x86_64
```

### Build Commands

```
"%LLVM_MINGW_ROOT%\bin\clang++.exe" -std=c++20 -O3 -Wall -Werror better.cc better_main.cc -o better.exe -stdlib=libc++
```

```
"%LLVM_MINGW_ROOT%\bin\clang++.exe" -std=c++20 -O3 -Wall -Werror non_optimal.cc non_optimal_main.cc -o non_optimal.exe -stdlib=libc++
```

Add LLVM-Mingw to your PATH:
```
set PATH=%PATH%;%LLVM_MINGW_ROOT%\bin
```

Then run: `better.exe` or `non_optimal.exe`

Both will output:
```
Hello from MyFunction!
```

## Additional info

## extern-func-decls

-----

### `non_optimal.cc`

```cpp
// TODO: Not manually validated.

// clang-tidy check: modernize-use-using
// Clang-C++ warning: none

// extern is redundant for function declarations
extern void MyFunction();

void MyFunction() {
  // Function implementation
}

int main() {
  MyFunction();
  return 0;
}
```

-----

### `better.cc`

```cpp
// TODO: Not manually validated.

void MyFunction();

void MyFunction() {
  // Function implementation
}

int main() {
  MyFunction();
  return 0;
}
```

### Extern is not Necessary in Header Files for Function Declaration

In C++, the `extern` keyword is used to declare a variable or function that has external linkage, meaning it can be accessed from other translation units (source files). While `extern` is necessary when declaring global variables that are defined in another file, it's **redundant and generally discouraged** for function declarations in header files.

#### Why `extern` is redundant for function declarations

Functions in C++ implicitly have external linkage unless declared `static`. When you declare a function in a header file, its purpose is to make that function's signature available to other source files that include the header. The compiler already assumes external linkage for functions, so explicitly adding `extern` provides no additional information or benefit. It can, however, make the code slightly more verbose and potentially confusing, suggesting a distinction that doesn't exist for functions.

#### Problems if `extern` is not avoided

While not strictly a "problem" in terms of compilation errors, using `extern` for function declarations in headers can:

  * **Increase verbosity:** It adds unnecessary keywords, making the code slightly harder to read and maintain.
  * **Create false impressions:** For developers new to C++, it might imply that functions require `extern` for cross-file visibility, which is incorrect and could lead to misunderstanding of linkage rules.
  * **Violate style guides:** Many established C++ coding guidelines recommend against its use for functions.

#### Better approach

Simply declare the function signature without the `extern` keyword. This keeps the code clean, concise, and correctly conveys the default external linkage of functions.
