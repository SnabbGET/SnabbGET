<h1 align="center">SnabbGET 🐐</h1>

<p align="center">
	<a href="https://snabbget.github.io/">
		<img src="https://github.com/SnabbGET/.github/blob/main/logo_small.png" alt="SnabbGET logo">
	</a>
</p>

*Graphic and fast terminal in C/C++.*

---

<p align="center">
	<a href="https://forthebadge.com"><img title="Powered" height="35" src="https://forthebadge.com/images/badges/powered-by-electricity.svg" /></a>
	<a href="https://forthebadge.com"><img title="Build" height="35" src="https://forthebadge.com/images/badges/built-by-developers.svg" /></a>
	<a href="https://forthebadge.com"><img title="Made" height="35" src="https://forthebadge.com/images/badges/made-with-c-plus-plus.svg" /></a>
	<a href="https://forthebadge.com"><img title="Open" height="35" src="https://forthebadge.com/images/badges/open-source.svg" /></a>
	<a href="https://forthebadge.com"><img title="Uses" height="35" src="https://forthebadge.com/images/badges/uses-badges.svg" /></a>
	<a href="src/core/shell.cpp"><img title="v0.2.0" height="35" src="https://img.shields.io/badge/Version-0.2.0-9cf?style=for-the-badge" /></a>
	<a href="https://forthebadge.com"><img title="forthebadge" height="35" src="https://forthebadge.com/images/badges/works-on-my-machine.svg" /></a>
	<a href="https://forthebadge.com"><img title="Gluten" height="35" src="https://forthebadge.com/images/badges/gluten-free.svg" /></a>
	<a href="https://forthebadge.com"><img title="Contains" height="35" src="https://user-images.githubusercontent.com/97749743/202749038-e8e5be0e-0253-41ce-a077-364479331bbd.svg" /></a>
</p>

[![CodeFactor](https://www.codefactor.io/repository/github/snabbget/snabbget/badge)](https://www.codefactor.io/repository/github/snabbget/snabbget)

---

## What is SnabbGET?

<p align="center">
	<a href="https://snabbget.github.io/more/"><img src="https://user-images.githubusercontent.com/97749743/215259179-b06d1422-fd8b-4cd1-914c-d4f0a2ee2340.png" alt="SnabbGET demo image" width="80%" /></a>
</p>

<p align="right">
	<sup>Made with <a href="https://asciinema.org/">Asciinema</a></sup>
</p>

SnabbGET is a 'guified' terminal built with love ❤ for all beginners learning how to use a terminal. <!--_It's not meant for professional uses._-->

The idea of creating this kind of terminal came out because we tought that it's pretty easy to be confused using a terminal, as a beginner.
This terminal makes everything easier with an user interface! We will do our best to do the most beginner-friendly & easy to use terminal.

We'll focus on OS such as Windows and Linux. No MacOS for the moment, sorry :(

## Compiling

Compiling the terminal edition (CLI):

### Tools required

> * Version of C++ used : C++17.
> * Any Linux architecture but a 64 bits arch. is required for Windows (MacOS not available).
> * `make` (Required only for the first use, we work on that.)
> * The `Makefile` use `g++` and `gdb` to compile and debug.

### First use

```sh

make first_time
./output
```

### Contribute

If you want to change something, you must recompile the file:

* File in `cmd`? `compile_cmds` or recompile only the file with the command.
* `utils.cpp`? `compile_utils`.
* `utils.hpp`, `shell.hpp` or `errors.hpp`? you can recompile all. Just wite `make`.
* `shell.cpp`, `errors.cpp`, `reader.cpp` or `cli.cpp`? `compile_shell`
* `main.cpp`? `compile_main`

```sh
make # <your command here>
make link
./output #.exe
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
under the GNU GPL License, and the
[exprtk library](https://github.com/ArashPartow/exprtk) under the MIT License.

I use and adapt
[torrycrass' image converter](https://github.com/torrycrass/image-to-ansi) to
generate the images in /assets.
The image came form [Pixbay](https://pixabay.com/images/search/background/).

# License

SnabbGET is under the
[MIT License](https://github.com/SnabbGET/SnabbGET/blob/main/LICENSE.txt).
