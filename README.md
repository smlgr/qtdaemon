# qtdaemon
Qt Daemon for SolarMax Inverter

This project is a Qt-based Console-only Application like the original C-only smlgr daemon.
This version uses signal-slot interaction of Qt libraries and has a better support for DB integration.

This daemon has different components. The query component has an indipendent timer which send a query every 2 seconds. It emits a signal every time it has a valid answer from the inverter.
The signal is connected to two different classes: one is responsible of updating a very simple JSON used for Android App, the other has an internal queue used to keep all data in a fifo stack and a timer which "transfer" the queue to permanent DB storage using a PostgreSQL connector.
