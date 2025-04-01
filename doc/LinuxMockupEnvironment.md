# Linux Mockup Environment

## Create Virtual Serial Ports

```
sudo socat -d -d pty,raw,echo=0,link=/dev/ttyNodeA pty,raw,echo=0,link=/dev/ttyNodeAInner
```
```
sudo socat -d -d pty,raw,echo=0,link=/dev/ttyNodeB pty,raw,echo=0,link=/dev/ttyNodeBInner
```