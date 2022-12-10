<h1 align="center">SnabbGET 🐐</h1>

<p align="center">
	<a href="https://snabbget.github.io/">
		<img src="https://github.com/SnabbGET/.github/blob/main/logo_small.png" alt="SnabbGET logo">
	</a>
</p>

*Graphic and fast terminal in C/C++.*

---

[![Powered](https://forthebadge.com/images/badges/powered-by-electricity.svg)](https://forthebadge.com)
[![Build](https://forthebadge.com/images/badges/built-by-developers.svg)](https://forthebadge.com)
[![Made](https://forthebadge.com/images/badges/made-with-c-plus-plus.svg)](https://forthebadge.com)
[![Open](https://forthebadge.com/images/badges/open-source.svg)](https://forthebadge.com)
[![Uses](https://forthebadge.com/images/badges/uses-badges.svg)](https://forthebadge.com)
<a href="src/core/shell.cpp">
	<img title="v0.2.0" height="35" src="https://img.shields.io/badge/Version-0.2.0-9cf?style=for-the-badge" />
</a>
<a href="https://forthebadge.com">
	<img title="forthebadge" height="35" src="https://forthebadge.com/images/badges/works-on-my-machine.svg" />
</a>
[![Gluten](https://forthebadge.com/images/badges/gluten-free.svg)](https://forthebadge.com)
[![Contains](https://user-images.githubusercontent.com/97749743/202749038-e8e5be0e-0253-41ce-a077-364479331bbd.svg)](https://forthebadge.com)

[![CodeFactor](https://www.codefactor.io/repository/github/snabbget/snabbget/badge)](https://www.codefactor.io/repository/github/snabbget/snabbget)

---

## What is SnabbGET?

SnabbGET is a guified terminal to be intuitive for beginners and easy to use for
all devs.

The idea of creating a terminal like that came out because we tought that it's
pretty easy to be lost using a terminal, as a beginner.
And we are mainly lost because we use commands, parameters...
With our terminal, you won't be able to be lost! We will do our best to do the
most beginner-friendly & easy to use terminal.

SnabbGET is cross-platform, a single language (SnabbScript) for *all* OS.

## Compile

***Warning! For the first use, you must execute the step commented in***
***Makefile! Else, it doesn't work!***

Use the termial version (CLI):

> Warning! You must have C++ 17!

### Makefile

```sh
#make libs # First use
# The ./configure shouldn't work on Windows (not tested.) (see in Makefile)

make DEBUG=off
./output #.exe
```

**Debug**:

```sh
make
make run
```

To use the GUI version (in dev), you must have a JDK installed:

```sh
make runGui
```

### Linux

```sh
./Make.sh
```

### Windows

```bat
./Make.bat
```
