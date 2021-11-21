# C API for the CSW Event Service

This is a binary release of a shared library `libcsw` providing the native C API for publishing events to 
the [CSW](https://github.com/tmtsoftware/csw) Event Service.
Subscribing to events is not yet implemented.

The binary release also contains the header files and shared library dependencies for Linux and MacOS
(This was generated and tested on Ubuntu-21.04 and MacOS-12 only.)

## Version compatibility

| csw-c | csw |
|--------|------|
| v4.0.1 | v4.0.0 |
| v4.0.0 | v4.0.0-RC1 |
| v3.0.1 | v3.0.1 |
| v3.0.1-M1 | v3.0.1-M1 |
| v2.0.0 | v2.0.0 |


Note that this library does not yet use the location service or the redis sentinel (cluster).
Instead, it connects to the default redis instance at localhost:6379, which is where csw-services starts it.

Events are encoded using [CBOR](https://cbor.io/) and stored in [Redis](https://redis.io/).

See [test/testPublisher.c](https://github.com/tmtsoftware/csw-c/blob/master/test/testPublisher.c) 
for examples of how to publish different kinds of events.

