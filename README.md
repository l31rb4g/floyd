# Floyd - helps you type repeating things
---

![](https://travis-ci.org/l31rb4g/floyd.svg?branch=master)

## Dependencies
Floyd requires `xdotool`, `Qt5` and `cmake`.

#### Arch
`sudo pacman -S xdotool qt5-base cmake`

## Building
```shell
 mkdir build
 cd build
 cmake ../src
 make
 ```

## Configuration
Write a file `.floyd` in your home. Each line is an entry. Optionally, you can
type a "\n" in the end of the line.

