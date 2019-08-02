# C API for the CSW Event Service

This project provides a C API for publishing events to the [CSW](https://github.com/tmtsoftware/csw) Event Service.
Subscribing to events is not yet implemented.

Events are encoded using [CBOR](https://cbor.io/) and stored in [Redis](https://redis.io/).

See the [examples](./examples) directory for examples of how to publish different kinds of events.

This is a *Work in progress*.
