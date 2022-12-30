[![GitHub](https://img.shields.io/github/license/asmaloney/GDExtensionTemplate)](LICENSE) ![Build](https://github.com/asmaloney/GDExtensionTemplate/actions/workflows/main.yml/badge.svg)

# GDExtensionTemplate

This project is meant as a starting point for creating new C++/CMake-based Godot 4 extensions. The goal is to lower the barrier to entry to building a GDExtension using [CMake](https://cmake.org).

It is currently set up to work with **Godot 4.0 beta 10** (see [tags](https://github.com/asmaloney/GDExtensionTemplate/tags) for other versions).

Since the majority of C++ open source projects use CMake, I wanted to offer an alternative to the _scons_ system for building Godot extensions (if you use _scons_, check out Nathan Franke's [gdextension](https://github.com/nathanfranke/gdextension) template or Patrick's [GDExtensionSummator](https://github.com/paddy-exe/GDExtensionSummator) template).

> **Note:** This project is not meant to be a dependency. It is intended to be copied (not forked) and made into your own project. Git itself doesn't provide a nice way to do this (as far as I can tell), but GitHub provides a **Use this template** button (beside where you clone a repo). This will [create a copy for you](https://docs.github.com/en/repositories/creating-and-managing-repositories/creating-a-repository-from-a-template) without all the history.

## What This Template Includes

This template project sets up a lot of the build details so you can get started and focus on your code:

- includes [godot-cpp](https://github.com/godotengine/godot-cpp) as a submodule and links it statically to your shared library
- uses [ccache](https://ccache.dev/) (if available) for faster local rebuilds
- builds universal library (x86_64 and arm64) on macOS
- creates `<project>.gdextension` files based on your project name
- automatically generates a _Version.h_ header file which:
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
- provides cmake targets:
  - _install_: install all files with the correct structure to `CMAKE_INSTALL_PREFIX`
  - _clang-format_: runs `clang-format` on all sources
- includes GitHub actions (CI) for:
  - building the extension on **Linux x86_64** (gcc), **macOS universal** (clang), and **Windows x86_64** (MSVC)
  - generating debug & release packages on each commit
  - using `ccache` to improve CI build times when available
  - checking code formatting using `clang-format`

## How To Use

To use this for your own project:

- _copy_ this repository (see note above about copy vs. clone/fork) and rename the directory to the name of your extension
- in _CMakeLists.txt_, change `GDExtensionTemplate` in the `project` macro to the name of your extension
- replace the example code in `src` with your own
  > **Note:** If you change the entry symbol (`GDExtensionInit`) in _RegisterExtension.cpp_, you will need to update your `templates/*.gdextension.in` files.
- replace this `README.md` with your own

Optional:

- [contribute to the project](#how-to-contribute) (it's not just 💰!)
- change the platforms/architectures you want to support:
  - edit the gdextension templates (`templates/*.gdextension.in`)
  - change the GitHub workflows to build the right stuff
- change the `.clang-format` config file to fit your C++ style
- change the LICENSE

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
