# GENADEV_OS

#### _An AArch64 hobbyist OS for the Raspberry Pi 3 B+ made with ❤️ by the [German OSDev & Lang Dev discord server community](https://disboard.org/server/819953014953476126) written in C and AArch64 Assembly_

## Emulation on Linux

- Packages you need
  - Debian based linux distributions:
    - git
    - qemu-system-arm
    - make
    - libncurses5
  - Arch based linux distributions:
    - git
    - qemu
    - qemu-arch-extra
    - make
    - ncurses

- To run it
  - git clone https://github.com/GENADEV/GENADEV_OS.git --recursive
  - cd GENADEV_OS
  - make setup (untar the cross compiler)
  - make run   (compile, link and run)

## Contributing

For those interested in contributing, please refer to the [contributing guidelines](https://github.com/GENADEV/GENADEV_OS/blob/main/CONTRIBUTING.md).
