# Trough-air protocol (TAP) description
This section contains description of custom protocol used for communication
between nodes.

## Message types

### PING

| Name         | Data Type  | Description |
| :----------- | :--------- | :---------- |
| Link Address | uint8_t[6] |             |
| Message Type | uint8_t    | 0x01        |
| Queue Length | uint8_t    |             |
| CRC          | uint8_t    |             |

### ACK

| Name         | Data Type  | Description |
| :----------- | :--------- | :---------- |
| Link Address | uint8_t[6] |             |
| Message Type | uint8_t    | 0x02        |
| Message ID   | uint8_t    |             |
| ACK          | uint8_t    |             |
| CRC          | uint8_t    |             |

### DATA

| Name           | Data Type  | Description |
| :-----------   | :--------- | :---------- |
| Link Address   | uint8_t[6] |             |
| Message Type   | uint8_t    | 0x04        |
| Message ID     | uint8_t    |             |
| Parting Flags  | uint8_t    |             |
| Part Number    | uint8_t    |             |
| Data Length    | uint8_t    |             |
