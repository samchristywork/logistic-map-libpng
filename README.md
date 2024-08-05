![Banner](https://s-christy.com/status-banner-service/logistic-map-libpng/banner-slim.svg)

<p align="center">
  <img src="./sample/sample.png" width="500" />
</p>

## Overview

The bifurcation diagram of the logistic map is a great way to understand how the
logistic formula works, and is also a great way to illustrate non-stable
population simulations.

The logistic function has some pretty interesting structural elements that vary
wildly based on the starting parameters. In this way it exhibits sensitive
dependence on initial conditions, or "chaotic behavior". This visualization
should show that this behavior is less chaotic than it initially appears.

## Setup

Simply run the command `make build`. This will place the executable in the
`build/` directory.

`make run` has been added as a convenience to generate a sample file like the
one shown above at `build/output.png`.

## Usage

```
Usage: ./build/main [-n iterations] [-x width] [-y height] [-o outFile]
 -n     Number of iterations (Default 100).
 -x     Image width (Default 1920).
 -y     Image height (Default 1080).
 -o     Output file (Default standard output).
 -a     The r1 boundary (Default 3.5).
 -b     The r2 boundary (Default 4).
 -h     Print this usage message.
```

## Dependencies

```
gcc
libpng-dev
make
```

## License

This work is licensed under the GNU General Public License version 3 (GPLv3).

[<img src="https://s-christy.com/status-banner-service/GPLv3_Logo.svg" width="150" />](https://www.gnu.org/licenses/gpl-3.0.en.html)
