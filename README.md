[![GitHub](https://img.shields.io/github/license/asmaloney/GDExtensionTemplate)](LICENSE) ![Build](https://github.com/asmaloney/GDExtensionTemplate/actions/workflows/main.yml/badge.svg)

# GDExtensionTemplate

This project is meant as a starting point for creating new C++/CMake-based Godot 4 extensions. The goal is to lower the barrier to entry to building a GDExtension using CMake. It is currently set up to work with **Godot 4.0 beta 10**.

Since the majority of C++ open source projects use CMake, I wanted to offer an alternative to the _scons_ system for building Godot extensions (if you use _scons_, check out Nathan Franke's [gdextension](https://github.com/nathanfranke/gdextension) template or Patrick's [GDExtensionSummator](https://github.com/paddy-exe/GDExtensionSummator) template).

> **Note:** This project is not meant to be a dependency. It is intended to be copied (not forked) and made into your own project. Git itself doesn't provide a nice way to do this (as far as I can tell), but GitHub provides a **Use this template** button (beside where you clone a repo). This will [create a copy for you](https://docs.github.com/en/repositories/creating-and-managing-repositories/creating-a-repository-from-a-template) without all the history.

This template project handles a lot of the details to set up a robust project:

- includes [godot-cpp](https://github.com/godotengine/godot-cpp) as a submodule and links it statically to your shared library
- uses [ccache](https://ccache.dev/) (if available) for faster local rebuilds
- builds universal library (x86_64 and arm64) on macOS
- creates `<project>.gdextension` files based on your project name
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
- change `GDExtensionTemplate` in the `project` macro in _CMakeLists.txt_ to the name of your extension
- replace the example code in `src` with your own
  > **note:** if you change the entry symbol `GDExtensionInit` in _RegisterExtension.cpp_, you will need to update your `templates/*.gdextension.in` files
- replace this `README.md` with your own

Optional:

- [contribute to the project](#how-to-contribute) (it's not just 💰!)
- change the platforms/architectures you want to support
  - edit the gdextension templates (`templates/*.gdextension.in`)
  - change the GitHub workflows to build the right stuff
- change the `.clang-format` config file to fit your C++ style
- change the LICENSE

## How To Contribute

These are some of the things you can do to contribute to the project:

### ✍ Write About The Project

If you find the project useful, spread the word! Articles, mastodon posts, tweets, blog posts, instagram photos - whatever you're into. Please include a referral back to the repository page: https://github.com/asmaloney/GDExtensionTemplate

### ⭐️ Add a Star

If you found this project useful, please consider starring it! It helps me gauge how useful this project is.

### ☝ Raise Issues

If you run into something which doesn't work as expected, raising [an issue](https://github.com/asmaloney/GDExtensionTemplate/issues) with all the relevant information to reproduce it would be helpful.

### 🐞 Bug Fixes & 🧪 New Things

I am happy to review any [pull requests](https://github.com/asmaloney/GDExtensionTemplate/pulls). Please keep them as short as possible. Each pull request should be atomic and only address one issue. This helps with the review process.

Note that I will not accept everything, but I welcome discussion. If you are proposing a big change, please raise it as [an issue](https://github.com/asmaloney/GDExtensionTemplate/issues) first for discussion.

### 💰 Financial

Given that I'm an independent developer without funding, financial support is always appreciated. If you would like to support the project financially, you can use the [sponsors page](https://github.com/sponsors/asmaloney) for one-off or recurring support. Thank you!
