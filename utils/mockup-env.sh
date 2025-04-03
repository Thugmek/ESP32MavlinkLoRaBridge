#!/usr/bin/sh

sudo -v

sudo socat -d -d pty,raw,echo=0,link=/dev/ttyNodeA pty,raw,echo=0,link=/dev/ttyNodeAInner 2> /dev/null &
SERIAL_A_PID=$!

sudo socat -d -d pty,raw,echo=0,link=/dev/ttyNodeB pty,raw,echo=0,link=/dev/ttyNodeBInner 2> /dev/null &
SERIAL_B_PID=$!

echo "Virtual Serial PIDs: $SERIAL_A_PID, $SERIAL_B_PID"

cleanup() {
    echo "Script is exiting. Cleaning up..."
    if ps -p $SERIAL_A_PID > /dev/null; then
        kill $SERIAL_A_PID 2>/dev/null
        sleep 0.5
        if ps -p $SERIAL_A_PID > /dev/null; then
            echo "Process $SERIAL_A_PID still running, sending SIGKILL..."
            kill -9 $SERIAL_A_PID 2>/dev/null
        fi
    fi

    if ps -p $SERIAL_B_PID > /dev/null; then
        kill $SERIAL_B_PID 2>/dev/null
        sleep 0.5
        if ps -p $SERIAL_B_PID > /dev/null; then
            echo "Process $SERIAL_B_PID still running, sending SIGKILL..."
            kill -9 $SERIAL_B_PID 2>/dev/null
        fi
    fi
}

trap cleanup EXIT TERM INT HUP

echo "Dev environment running. Press Ctrl+C to exit."
sleep 2147483647
