# GENADEV_OS

#### _An AArch64 hobbyist OS for the Raspberry Pi 3 B+ made with ❤️ by the [German Low-Level discord server community](https://disboard.org/server/819953014953476126) written in C and AArch64 Assembly_

<a href="https://discord.gg/jPNNeZqMwR"> <img src="https://img.shields.io/discord/819953014953476126?label=discord"> <img src="https://img.shields.io/github/license/GENADEV/GENADEV_OS"> </a>

## Screenshots
<img src="https://github.com/GENADEV/GENADEV_OS/blob/main/screenshots/uart%20output.png"> </a>
<img src="https://github.com/GENADEV/GENADEV_OS/blob/main/screenshots/framebuffer.png"> </a>

## Emulation on Linux

- Packages you need
  - Debian based linux distributions:
    - git
    - qemu-system-arm
    - make
    - astyle
    - gdb-multiarch
  - Arch based linux distributions:
    - git
    - qemu
    - qemu-arch-extra
    - make
    - ncurses
    - astyle

- To run it
  - git clone https://github.com/GENADEV/GENADEV_OS.git --recursive
  - cd GENADEV_OS
  - make setup (untar the cross compiler)
  - make run   (compile, link and run)
  - By default `make run` will use the uart0 for debugging output, you can change this to use the mini uart aswell via `make run_uart1`
  - ### Important:
    - We have recently discovered that qemu segfaults when using the framebuffer, this is qemu bug and issues regarding this will be closed.
    - In order to see the display you need to follow these instructions:
      ```bash
      # In this example we will use vinagre as a VNC client but you can use any software you wish
      sudo apt install vinagre # This command may vary based on your distro
      make run # GENADEV_OS will start executing
      vinagre :5901 # Start the VNC client
      # A GUI window should have opened, now click `connect`, enter 127.0.0.1:1 as the host and connect. You should now see the the screen of GENADEV_OS
      ```

## Contributing

For those interested in contributing, please refer to the [contributing guidelines](https://github.com/GENADEV/GENADEV_OS/blob/main/CONTRIBUTING.md).
