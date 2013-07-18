[![Build Status](https://travis-ci.org/joninvski/imep_lib.png?branch=master)](https://travis-ci.org/joninvski/imep_lib)

Internet MANET Encapsulation Protocol (IMEP) c++ lib
====================================================

Functionalities it provides:

    - Keeps updated a list of available connections

In more detail:

    - At each X time it sends BEACON messages with node ID
    - At each X time it checks which nodes have sent me BEACONS
        - If it has bean longer than Y then remove link from active connection

The user can:

    - Get a list of available connections
    - Explicitly indicate that a link is considered as broken
    - Explicitly indicate that a link is up

API:

    IMEP object:

     * Constructur()
     * PassTime()
     * ReceivedHello()
     * GetAvailableConnections()
     * ConsiderLinkUp()
     * ConsiderLinkDown()

The user has to pass a callback to IMEP which allows it to send messages

Optional: The user may set the callback function which it wishes to be called when a broken connection occurs
