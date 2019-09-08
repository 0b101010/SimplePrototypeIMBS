# SimplePrototypeIMBS
A Simple prototype for a internet movie booking system.

NOTE this application is a work in progress and is not finished.

## Dependencies
* [gn](https://gn.googlesource.com/gn) binary for
[Linux](https://chrome-infra-packages.appspot.com/dl/gn/gn/linux-amd64/+/latest),
[macOS](https://chrome-infra-packages.appspot.com/dl/gn/gn/mac-amd64/+/latest) or
[Windows](https://chrome-infra-packages.appspot.com/dl/gn/gn/windows-amd64/+/latest)
* [ninja](https://ninja-build.org)
* GNU C++ Compiler
* BOOST
* [nlohmann json library](https://github.com/nlohmann/json)

NOTE that currently the build system configuration only includes Linux.

## Design

The `HTMLServer` receiving HTML request with JSON encoded data.
It has a `boost::asio::io_context` ruining in a thread pool.
When receiving a request it calls the matching method on the internal `Server`.

The Internal `Server` has a `boost::asio::io_context` running on a single thread.
All API calls on it contains a callback that together with the actual work that should be done for the request is dispatched on the io_context.
The deserialization of the request is done before the task is dispatched on the single thread.

The `TheaterMgr` together with the `dataEntities` do the single threaded work on the data of the system.
Methods on the TheaterMgr is called in the tasks that the Internal `Server` has dispatched.
