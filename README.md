[![GitHub](https://img.shields.io/github/license/asmaloney/GDExtensionTemplate)](LICENSE) ![Build](https://github.com/asmaloney/GDExtensionTemplate/actions/workflows/build.yml/badge.svg)

# GDExtensionTemplate

This project is a template meant as a starting point for creating new C++/CMake-based Godot 4 extensions. It is currently set up to work with **Godot 4.0 beta 7**.

Since the majority of C++ open source projects use CMake, I wanted to offer an alternative to the _scons_ system for building Godot extensions (if you use scons, check out Nathan Franke's [gdextension](https://github.com/nathanfranke/gdextension) template).

**Note:** This project is not meant to be a dependency for your project. It is intended to be copied (not forked) and made into your own project. git itself doesn't provide a nice way to do this (as far as I can tell), but GitHub provides a green "Use this template" button beside the normal place you clone a repo. This should [create a copy for you](https://docs.github.com/en/repositories/creating-and-managing-repositories/creating-a-repository-from-a-template).

There are a lot of little things to get right when starting a GDExtension project - naming, file location, etc.. The goal of this project is to lower the barrier to entry to building a GDExtension using CMake by making it easy to get started & easy to maintain.

This template:

- includes [godot-cpp](https://github.com/godotengine/godot-cpp) as a submodule and links it statically to your shared library
- creates a `<project>.gdextension` file based on your project name
- uses [ccache](https://ccache.dev/) (if available) for faster rebuilds
- provides a cmake target (`install`) to install the files with the correct structure to a given location (set `CMAKE_INSTALL_PREFIX`)
- provides a cmake target (`clang-format`) for running `clang-format` on all the sources at once
- includes GitHub actions (CI) for building the extension on Linux (gcc), macOS (clang), and Windows (MSVC)
- includes GitHub actions (CI) for checking code formatting using clang-format

## How To Use

To use this for your own project:

- copy this repository (see note above about copy vs. clone/fork)
- rename the directory to the name of your extension
- change `GDExtensionTemplate` in the `project` macro in _CMakeLists.txt_ to the name of your extension
- replace the example code in `src` with your own (**note:** if you change the entry symbol `GDExtensionInit` in _register_types.cpp_, you will need to update the `templates/template.gdextension.in` file)
- replace this `README.md` with your own
- remove/replace `.github/FUNDING.yml`

Optional:

- [contribute to the project](#how-to-contribute) (not just 💰!)
- edit `templates/template.gdextension.in` to add/remove supported platform/architectures
- change `.clang-format` to fit your C++ style
- change the LICENSE

## How To Contribute

These are some of the things you can do to contribute to the project:

### ✍ Write About The Project

If you find the project useful, spread the word! Articles, mastodon posts, tweets, blog posts, instagram photos - whatever you're into. Please include a referral back to the repository page: https://github.com/asmaloney/GDExtensionTemplate

### ☝ Raise Issues

If you run into something which doesn't work as expected, raising [an issue](https://github.com/asmaloney/GDExtensionTemplate/issues) with all the relevant information to reproduce it would be helpful.

### 🐞 Bug Fixes & 🧪 New Things

I am happy to review any [pull requests](https://github.com/asmaloney/GDExtensionTemplate/pulls). Please keep them as short as possible. Each pull request should be atomic and only address one issue. This helps with the review process.

Note that I will not accept everything, but I welcome discussion. So if it's a big change you are proposing, please raise it as [an issue](https://github.com/asmaloney/GDExtensionTemplate/issues) first for discussion.

### 💰 Financial

Given that I'm an independent developer without funding, financial support is always appreciated. If you would like to support the project financially, you can use the **Sponsor** button at the top of the [GDExtensionTemplate](https://github.com/asmaloney/GDExtensionTemplate) repository page for one-off or recurring support.
