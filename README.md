<h1 align="center">SnabbGET 🐐</h1>

<p align="center">
    <a href="https://snabbget.github.io/">
        <img src="https://github.com/SnabbGET/.github/blob/main/logo_small.png"
        alt="SnabbGET logo">
    </a>
</p>

*Graphic and fast shell and chatbox in C/C++.*

---

<p align="center">
    <a href="https://www.codefactor.io/repository/github/snabbget/snabbget"><img title="Codefactor" height="35"
    src="https://www.codefactor.io/repository/github/snabbget/snabbget/badge?style=for-the-badge" /></a>
    <a href="https://img.shields.io"><img title="Maintenance" height="35"
    src="https://img.shields.io/github/commit-activity/t/SnabbGET/SnabbGET?style=for-the-badge"/></a>
    <a href="https://img.shields.io"><img title="Contributors" height="35"
    src="https://img.shields.io/github/contributors/SnabbGET/SnabbGET?style=for-the-badge" /></a>
    <a href="https://img.shields.io"><img title="Issues" height="35"
    src="https://img.shields.io/github/issues/SnabbGET/SnabbGET?style=for-the-badge" /></a>
    <a href="https://img.shields.io"><img title="OpenSource" height="35"
    src="https://img.shields.io/badge/Open-Source-777?style=for-the-badge" /></a>
    <a href="https://img.shields.io"><img title="Last commit" height="35"
    src="https://img.shields.io/github/last-commit/SnabbGET/SnabbGET/in-dev?style=for-the-badge" /></a>
    <a href="https://img.shields.io"><img title="License" height="35"
    src="https://img.shields.io/github/license/SnabbGET/SnabbGET?style=for-the-badge"></a>
    <a href="src/core/shell.cpp"><img title="v0.3.0" height="35"
    src="https://img.shields.io/badge/Version-0.3.0-9cf?style=for-the-badge" /></a>
    <a href="https://img.shields.io"><img title="C++" height="35"
    src="https://img.shields.io/github/languages/top/SnabbGET/SnabbGET?style=for-the-badge" /></a>
    <a href="https://img.shields.io"><img title="Contains" height="35"
    src="https://img.shields.io/badge/Contains-Code-0aa?style=for-the-badge" /></a>
</p>

---

## What is SnabbGET?

A video of the shell:

<p align="center">
    <a href="https://snabbget.github.io/more/">
        <img src="https://user-images.githubusercontent.com/97749743/215259179-b06d1422-fd8b-4cd1-914c-d4f0a2ee2340.png"
        alt="SnabbGET demo image" width="80%" /></a>
</p>

<p align="right">
    <sup>Made with <a href="https://asciinema.org/">Asciinema</a></sup>
</p>

SnabbGET is a 'guified' terminal built with love ❤ for all beginners learning
how to use a terminal.<!--_It's not meant for professional uses._-->

The idea of creating this kind of terminal came out because we tought that it's
pretty easy to be confused using a terminal, as a beginner.
This terminal makes everything easier with an user interface! We will do our
best to do the most beginner-friendly & easy to use terminal.

We'll focus on OS such as Windows and Linux. No MacOS for the moment, sorry :(

You can use the SnabbGET shell or the chatbox. Same features.

## Compiling

Compiling the terminal edition (CLI):

### Tools required

<!-- > * Any Linux architecture but a 64 bits arch. is required for Windows
    (MacOS not available).-->

> * Version of C++ used : C++17.
> * `make` (Required only for the first on Linux if you want to use the shell),
>   or Execute the Make.* file
> * A C++ compiler (with lld)

### First use

Warning! Use that command only if tou use Linux and the SnabbGET shell!

```sh
make first_time
./output
```

The chatbox (available for Windows):

```batch
make lib_exprtk
make chatbox
./output
```

### Contribute

If you want to change something, you must recompile the file:

* File in `cmd`? `<path/to/file>`.
* `utils.cpp`? `compile_utils`.
* `utils.hpp`, `shell.hpp` or `errors.hpp`? you can recompile all. Just wite `make`.
* `shell.cpp`, `errors.cpp`, `reader.cpp` or `cli.cpp`? `compile_shell`.
* `main.cpp`? `compile_main`.
* `chatbox.cpp`? `compile_chatbox`.
* You created a file, and you won't modify the Makefile? `<path/to/file>`

```sh
make # <your command here>
make link # or link_chatbox
./output # [_chatbox] [.exe]
```

**Debug**:

```sh
make
make run
```

*More informaitons about the GUI version will be given soon.*

# FAQ & Links

You have questions about SnabbGET?

[Open an issue](https://github.com/SnabbGET/SnabbGET/issues/new/choose),
[ask us for information](https://github.com/SnabbGET/SnabbGET/discussions/categories/q-a),
[see the wiki](https://github.com/SnabbGET/SnabbGET/wiki) or
[see our project](https://github.com/orgs/SnabbGET/projects/1/views/1?query=is%3Aopen+sort%3Aupdated-desc).

You can also open [a PR](https://github.com/SnabbGET/SnabbGET/pulls)
to contribute to this project.

# Thanks

SnabbGET use the
[GNU Readline library 8.2](https://git.savannah.gnu.org/cgit/readline.git)
under the GNU GPL License, the
[exprtk library](https://github.com/ArashPartow/exprtk) under the MIT License,
and the library
"[Lohmann, N. (2022). JSON for Modern C++ (Version 3.11.2) [Computer software].](https://github.com/nlohmann)".

I used and adapt
[torrycrass' image converter](https://github.com/torrycrass/image-to-ansi) to
generate the images in `/assets``.
The image came form [Pixbay](https://pixabay.com/images/search/background/).

# License

SnabbGET is under the
[MIT License](https://github.com/SnabbGET/SnabbGET/blob/main/LICENSE.txt).
