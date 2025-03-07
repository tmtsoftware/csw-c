# C API for the CSW Event Service

This project provides a C API for publishing events to the [CSW](https://github.com/tmtsoftware/csw) Event Service.
Subscribing to events is not yet implemented.

## Version compatibility

| csw-c     | csw        |
|-----------|------------|
| v6.0.0    | v6.0.0     |
| v5.0.0    | v5.0.0     |
| v4.0.3    | v4.0.1     |
| v4.0.2    | v4.0.0     |
| v4.0.1    | v4.0.0     |
| v4.0.0    | v4.0.0-RC1 |
| v3.0.1    | v3.0.1     |
| v3.0.1-M1 | v3.0.1-M1  |
| v2.0.0    | v2.0.0     |


Note that this library does not yet use the location service or the redis sentinel (cluster).
Instead, it connects to the default redis instance at localhost:6379, which is where csw-services starts it.

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
* zlog (from source on Linux, brew on Mac)

## Making a release dir: install.sh

The install.sh script creates an OS specific directory with all of the native dependencies.
It assumes that the native shared libs for csw-c are already installed in /usr/local/lib
and copies them to install/csw-c/lib/`uname`, where `uname` is Darwin for MacOS, or Linux.

This was tested on Ubuntu-21.04 and MacOS-12.

### Logging
The CSW standard logging library for C is [zlog](https://github.com/HardySimpson/zlog), which needs to be installed
from the source (by default also in /usr/local). 
Note that your application's main() must initialize the zlog library at startup.
See the [zlog API](https://hardysimpson.github.io/zlog/UsersGuide-EN.html#sec:dzlog-API) for details.

* Note: For CentOS-7 you need to install cmake-3.14 and libcbor manually.

* Note: For MacOS, you can install the dependencies as follows:
```
    brew tap pjk/libcbor
    brew install libcbor
    brew install hiredis
    brew install ossp-uuid
    brew install zlog
```

## Building and Installing

To build the the library (libcsw) and the example applications, run:

    make

or 

    make PREFIX=/my/dir

Default install dir is /usr/local, but that can be changed by adding PREFIX=... to the make command line.
Install the library with:

    make install

To run the tests:

    make test

Note that this requires that csw-services and sbt are in your shell path. 
`make test` compiles and runs a Scala based assembly in the background and uses it
to test for correct serialization and communication.

To install (optional) run:

    sudo make install

The sudo is needed, since by default the install directory is /usr/local on Linux.
You can change the target install directory like this:

    make install INSTALL_DIR=$HOME/myDir

This installs the shared library libcsw.so.

Other make targets include:

    make clean

which removes the local build directory and:

    make uninstall

which removes the installed files.


## Running the Tests

See [test/README.md](test/README.md) for additional instructions on how to run the test.

