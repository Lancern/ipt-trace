# Build `ipt-trace` From Source

`ipt-trace` consists of a kernel module and a user-space utility program, which can be built seperately.

## Build the Kernel Module

### Prerequisites

You need a working C compiler toolchain and a kernel header suite to build the kernel module. To install the C compiler toolchain and the kernel header suite, execute the following command:

```shell
sudo apt install build-essential linux-headers-$(uname -r)
```

### Build

Change the working directory to the `kernel` subdirectory and then build:

```shell
cd kernel
make
```

The generated kernel module is `ipt.ko`.

## Build the Utility Program

> This part is under development.
