# C API for the CSW Event Service

This project provides a C API for publishing events to the [CSW](https://github.com/tmtsoftware/csw) Event Service.
Subscribing to events is not yet implemented.

Events are encoded using [CBOR](https://cbor.io/) and stored in [Redis](https://redis.io/).

See the [examples](./examples) directory for examples of how to publish different kinds of events.

# Building and Installing

To build the the library (libcsw) and the example applications, run:

    make

And optionally:

    sudo make install

The sudo is needed, since by default the install directory is /usr/local on Linux.
You can change the target install directory like this:

    make install INSTALL_DIR=$HOME/myDir

Other make targets include:

    make clean

which removes the local build directory and:

    make uninstall

which removes the installed files.

## Dependencies
This project depends on these packages, which can be installed with `yum`, `dnf`, `apt`, 
depending on the Linux flavor (or `brew`, `port` for Macs). Alternatively, you can
install them from the source code. The makefiles will look for them in the standard places:

* cmake
* libev, libev-devel
* libcbor, libcbor-devel
* libuuid, libuuid-devel
* hiredis, hiredis-devel

