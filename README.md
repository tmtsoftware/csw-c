# C API for the CSW Event Service

This project provides a C API for publishing events to the [CSW](https://github.com/tmtsoftware/csw) Event Service.
Subscribing to events is not yet implemented.

Events are encoded using [CBOR](https://cbor.io/) and stored in [Redis](https://redis.io/).

See the [examples](./examples) directory for examples of how to publish different kinds of events.

# Building and Installing

## Dependencies
This project depends on these packages, which can be installed with `yum`, `dnf`, `apt`, 
depending on the Linux flavor (or `brew`, `port` for Macs). Alternatively, you can
install them from the source code. The makefiles will look for them in the standard places:

* cmake
* libev, libev-devel
* libcbor, libcbor-devel
* libuuid, libuuid-devel
* hiredis, hiredis-devel

This is a *Work in progress*.
