[![GitHub](https://img.shields.io/github/license/asmaloney/GDExtensionTemplate)](LICENSE) ![Build](https://github.com/asmaloney/GDExtensionTemplate/actions/workflows/main.yml/badge.svg)

# GDExtensionTemplate

This project is meant as a starting point for creating new C++/CMake-based Godot 4 extensions. The goal is to lower the barrier to entry to building a GDExtension using [CMake](https://cmake.org).

It is currently set up to work with the **[Godot 4.0](https://github.com/godotengine/godot/releases/tag/4.0-stable)** release (see [tags](https://github.com/asmaloney/GDExtensionTemplate/tags) for other versions).

Since the majority of C++ open source projects use CMake, I wanted to offer an alternative to the _scons_ system for building Godot extensions (if you use _scons_, check out Nathan Franke's [gdextension](https://github.com/nathanfranke/gdextension) template or Patrick's [GDExtensionSummator](https://github.com/paddy-exe/GDExtensionSummator) template).

> **Note:** This project is not meant to be a dependency. It is intended to be copied (not forked) and made into your own project. Git itself doesn't provide a nice way to do this (as far as I can tell), but GitHub provides a **Use this template** button (beside where you clone a repo). This will [create a copy for you](https://docs.github.com/en/repositories/creating-and-managing-repositories/creating-a-repository-from-a-template) without all the history.

## Features

This template project sets up a lot of the build details so you can get started and focus on your code:

- includes **[godot-cpp](https://github.com/godotengine/godot-cpp) as a submodule** and links it statically to your shared library
- creates `<project>.gdextension` files based on your project name
- automatically generates a _**Version.h**_ header file which:
  - includes a preprocessor macro for conditional compilation
    ```cpp
    #if GDEXTENSIONTEMPLATE_VERSION < GDEXTENSIONTEMPLATE_VERSION_CHECK(2, 1, 0)
      // do stuff
    #endif
    ```
  - includes git information in the version strings (e.g. `GDExtensionTemplate v1.0.1-gf6446f8`)
  - includes an example which exposes the version string to GDScript so you can call it like this
    ```py
    print( GDExtensionTemplate.version() )
    ```
  - keeps itself up-to-date when the git branch/tag/HEAD changes
- uses **[ccache](https://ccache.dev/)** (if available) for faster rebuilds
- builds **universal library** (x86_64 and arm64) on macOS
- provides **cmake targets**:
  - _install_: install all files with the correct structure to `CMAKE_INSTALL_PREFIX`
  - _clang-format_: runs `clang-format` on all sources
- includes **GitHub workflows** (CI) for:
  - building the extension on **Linux x86_64** (gcc), **macOS universal** (clang), and **Windows x86_64** (MSVC)
  - generating debug & release packages on each commit
  - using `ccache` to improve CI build times when available
  - checking code formatting using `clang-format`

## Prerequisites

To use this locally on your machine, you will need the following:

- **[CMake](https://cmake.org/)** v3.22+
- C++ Compiler with at least **C++17** support (any recent compiler)
- (optional) **[ccache](https://ccache.dev/)** for faster rebuilds
- (optional) **[clang-format](https://clang.llvm.org/docs/ClangFormat.html)** for linting and automatic code formatting (CI uses clang-format version 15)

The GitHub actions (CI) are set up to include all of these tools. To see how to download them on your platform, take a look at the [workflow](.github/workflows/main.yml) file.

## How To Use

### Setup

To use this for your own project:

- _copy_ this repository and rename the directory to the name of your extension
  > GitHub provides a **Use this template** button (beside where you clone a repo). This will [create a copy for you](https://docs.github.com/en/repositories/creating-and-managing-repositories/creating-a-repository-from-a-template) without all the history.
- in _CMakeLists.txt_, change `GDExtensionTemplate` in the `project` macro to the name of your extension
  ```cmake
  project( <your_extension_name_here>
    LANGUAGES
        CXX
    VERSION
        0.1.0
  )
  ```
  If you also have plain C files in your project, add `C` to the languages.
- replace the example code in `src` with your own (I would suggest keeping _RegisterExtension.cpp_ and using it to register your classes)
  > **Note:** If you change the entry symbol (`GDExtensionInit`) in _RegisterExtension.cpp_, you will need to update your `templates/*.gdextension.in` files.
- replace this `README.md` with your own

Optional:

- [contribute to the project](#how-to-contribute) (it's not just 💰!)
- change the platforms/architectures you want to support:
  - edit the gdextension templates (`templates/*.gdextension.in`)
  - change the GitHub workflows to build the right stuff
- change the `.clang-format` config file to fit your C++ style ([option documentation](https://clang.llvm.org/docs/ClangFormatStyleOptions.html))
- change the compiler warnings you want to enforce (see [CompilerWarnings.cmake](cmake/CompilerWarnings.cmake))
- change the LICENSE

### Build & Install

Here's an example of how to build & install a release version (use the terminal to run the following commands in the parent directory of this repo):

#### Not MSVC

```sh
$ cmake -B GDExtensionTemplate-build -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=GDExtensionTemplate-install GDExtensionTemplate
$ cmake --build GDExtensionTemplate-build --parallel
$ cmake --install GDExtensionTemplate-build
```

#### MSVC

```sh
$ cmake -B GDExtensionTemplate-build -G"Visual Studio 17 2022"  -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=GDExtensionTemplate-install GDExtensionTemplate
$ cmake --build GDExtensionTemplate-build --config Release
$ cmake --install GDExtensionTemplate-build
```

This tells CMake to use `Visual Studio 2022`. There is a list of Visual Studio generators [on the CMake site](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html#visual-studio-generators) - pick the one you are using.

### Cmake Options

This template defines the following additional CMake options:

| Option                                                                   | Description                                      | Default                                                                                                 |
| ------------------------------------------------------------------------ | ------------------------------------------------ | ------------------------------------------------------------------------------------------------------- |
| `CCACHE_PROGRAM`                                                         | Path to `ccache` for faster rebuilds             | This is automatically set **ON** if `ccache` is found. If you do not want to use it, set this to "".    |
| `CLANG_FORMAT_PROGRAM`                                                   | Path to `clang-format` for code formatting.      | This is automatically set **ON** if `clang-format` is on. If you do not want to use it, set this to "". |
| `${PROJECT_NAME_UPPERCASE}_WARN_EVERYTHING` (e.g. FOO_WARN_EVERYTHING)   | Turns on all warnings. (Not available for MSVC.) | **OFF** (too noisy, but can be useful sometimes)                                                        |
| `${PROJECT_NAME_UPPERCASE}_WARNING_AS_ERROR` (e.g. FOO_WARNING_AS_ERROR) | Turns warnings into errors.                      | **ON**                                                                                                  |

## How To Contribute

These are some of the things you can do to contribute to the project:

### ✍ Write About The Project

If you find the project useful, spread the word! Articles, mastodon posts, tweets, blog posts, instagram photos - whatever you're into.

### ⭐️ Add a Star

If you found this project useful, please consider starring it! It helps me gauge how useful this project is.

### ☝ Raise Issues

If you run into something which doesn't work as expected, raising [an issue](https://github.com/asmaloney/GDExtensionTemplate/issues) with all the relevant information to reproduce it would be helpful.

### 🐞 Bug Fixes & 🧪 New Things

I am happy to review any [pull requests](https://github.com/asmaloney/GDExtensionTemplate/pulls). Please keep them as short as possible. Each pull request should be atomic and only address one issue. This helps with the review process.

Note that I will not accept everything, but I welcome discussion. If you are proposing a big change, please raise it as [an issue](https://github.com/asmaloney/GDExtensionTemplate/issues) first for discussion.

### 💰 Financial

Given that I'm an independent developer without funding, financial support is always appreciated. If you would like to support the project financially, you can use [GitHub sponsors](https://github.com/sponsors/asmaloney) or [Ko-fi](https://ko-fi.com/asmaloney) for one-off or recurring support. Thank you!
