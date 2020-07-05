# C API for the CSW Event Service

This project provides a C API for publishing events to the [CSW](https://github.com/tmtsoftware/csw) Event Service.
Subscribing to events is not yet implemented.

Events are encoded using [CBOR](https://cbor.io/) and stored in [Redis](https://redis.io/).

See [test/testPublisher.c](./test/testPublisher.c) for examples of how to publish different kinds of events.


## Dependencies
This project depends on these packages, which can be installed with `yum`, `dnf`, `apt`, 
depending on the Linux flavor (or `brew`, `port` for Macs). Alternatively, you can
install them from the source code. The makefiles will look for them in the standard places:

* cmake
* libcbor, libcbor-devel (for Fedora, CentOS) or libcbor-dev (for Ubuntu)
* libuuid, libuuid-devel (Fedora), uuid-dev (Ubuntu)
* hiredis, hiredis-devel (Fedora), libhiredis-dev (Ubuntu)

<!--* libev, libev-devel  (Not currently needed: Will be needed if event subscription is implemented)-->

* Note: For CentOS-7 you need to install cmake-3.14 and libcbor manually.

* Note: For MacOS, you can install the dependencies as follows:
```
    brew tap pjk/libcbor
    brew install libcbor
    brew install hiredis
    brew install ossp-uuid
```
<!--    brew install libev   (Not currently needed: Will be needed if event subscription is implemented)-->


## Building and Installing


To build the the library (libcsw) and the example applications, run:

    make

To run the tests:

    make test

Note that this requires that csw-services.sh and sbt are in your shell path. 
`make test` compiles and runs a Scala based assembly in the background and uses it
to test for correct serialization and communication.

To install (optional) run:

    sudo make install

The sudo is needed, since by default the install directory is /usr/local on Linux.
You can change the target install directory like this:

    make install INSTALL_DIR=$HOME/myDir

Other make targets include:

    make clean

which removes the local build directory and:

    make uninstall

which removes the installed files.


## Running the Tests

See [test/README.md](test/README.md) for additional instructions on how to run the test.

