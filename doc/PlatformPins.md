# GPIO pins usage on supported platforms

## Radiomaster Bandit Nano

| GPIO | Function                | Description                                                                                                                          |
| ---- | ----------------------- | ------------------------------------------------------------------------------------------------------------------------------------ |
| 0    |                         |                                                                                                                                      |
| 1    | USB-UART TX             |                                                                                                                                      |
| 2    | misc_fan_en             | Pin used to enable a cooling FAN (active HIGH)                                                                                       |
| 3    | USB-UART RX             |                                                                                                                                      |
| 4    | radio_nss               | Chip select pin for first SX1280/127x                                                                                                |
| 5    | radio_rst               | Reset pin connected to (possibly) multiple SX1280/127x                                                                               |
| 6    |                         |                                                                                                                                      |
| 7    |                         |                                                                                                                                      |
| 8    |                         |                                                                                                                                      |
| 9    |                         |                                                                                                                                      |
| 10   |                         |                                                                                                                                      |
| 11   |                         |                                                                                                                                      |
| 12   | screen_sck              | Screen Clock (either SPI or I2C)                                                                                                     |
| 13   | serial_rx, serial_tx    | Pin used to receive CRSF signal from the handset, Pin used to transmit CRSF telemetry to the handset (may be the same as the RX PIN) |
| 14   | screen_sda              | Screen Data (I2C)                                                                                                                    |
| 15   | led_red                 | If there are multiple LEDs, then this is the pin for the RED LED                                                                     |
| 16   | debug_backpack_rx       | Connected to TX pin on backpack                                                                                                      |
| 17   | debug_backpack_tx       | Connected to RX pin on backpack                                                                                                      |
| 18   | radio_sck               | Clock pin connected to (possibly) multiple SX1280/127x                                                                               |
| 19   | radio_miso              | MISO connected to (possibly) multiple SX1280/127x                                                                                    |
| 20   |                         |                                                                                                                                      |
| 21   | radio_dio1              | Interrupt pin for SX128x                                                                                                             |
| 22   | radio_dio0              | Unused on SX128x, Interrupt pin for SX127x                                                                                           |
| 23   | radio_mosi              | MOSI connected to (possibly) multiple SX1280/127x                                                                                    |
| 24   |                         |                                                                                                                                      |
| 25   | backpack_en             | Pin connected to EN pin on backpack ESP8285, allows passthrough flashing                                                             |
| 26   | power_apc2              | Power amplifier control voltage                                                                                                      |
| 27   |                         |                                                                                                                                      |
| 28   |                         |                                                                                                                                      |
| 29   |                         |                                                                                                                                      |
| 30   |                         |                                                                                                                                      |
| 31   |                         |                                                                                                                                      |
| 32   | backpack_boot           | Pin connected to GPIO0 pin on backpack ESP8285, allows passthrough flashing                                                          |
| 33   | power_txen              | Enable TX mode PA (active high)                                                                                                      |
| 34   |                         |                                                                                                                                      |
| 35   |                         |                                                                                                                                      |
| 36   |                         |                                                                                                                                      |
| 37   |                         |                                                                                                                                      |
| 38   |                         |                                                                                                                                      |
| 39   | joystick                | Analog Input (3.3V max) use to read joystick direction using a resistor network                                                      |

## Radiomaster BR3

| GPIO | Function   | Description                                                                        |
| ---- | ---------- | ---------------------------------------------------------------------------------- |
| 0    |            |                                                                                    |
| 1    | serial_tx  | Pin used to transmit CRSF telemetry to the handset (may be the same as the RX PIN) |
| 2    | radio_rst  | Reset pin connected to (possibly) multiple SX1280/127x                             |
| 3    | serial_rx  | Pin used to receive CRSF signal from the handset                                   |
| 4    | radio_dio0 | Unused on SX128x, Interrupt pin for SX127x                                         |
| 5    | radio_dio1 | Interrupt pin for SX128x                                                           |
| 6    |            |                                                                                    |
| 7    |            |                                                                                    |
| 8    |            |                                                                                    |
| 9    | ant_ctrl   | Pin connected to Antenna select pin on power amplifier                             |
| 10   | power_txen | Enable TX mode PA (active high)                                                    |
| 11   |            |                                                                                    |
| 12   | radio_miso | MISO connected to (possibly) multiple SX1280/127x                                  |
| 13   | radio_mosi | MOSI connected to (possibly) multiple SX1280/127x                                  |
| 14   | radio_sck  | Clock pin connected to (possibly) multiple SX1280/127x                             |
| 15   | radio_nss  | Chip select pin for first SX1280/127x                                              |
| 16   | led        | Only use when only a single LED is used                                            |
| 17   |            |                                                                                    |
| 18   |            |                                                                                    |
| 19   |            |                                                                                    |
| 20   |            |                                                                                    |
| 21   |            |                                                                                    |
| 22   |            |                                                                                    |
| 23   |            |                                                                                    |
| 24   |            |                                                                                    |
| 25   |            |                                                                                    |
| 26   |            |                                                                                    |
| 27   |            |                                                                                    |
| 28   |            |                                                                                    |
| 29   |            |                                                                                    |
| 30   |            |                                                                                    |
| 31   |            |                                                                                    |
| 32   |            |                                                                                    |
| 33   |            |                                                                                    |
| 34   |            |                                                                                    |
| 35   |            |                                                                                    |
| 36   |            |                                                                                    |
| 37   |            |                                                                                    |
| 38   |            |                                                                                    |
| 39   |            |                                                                                    |

## Pin functions as defined in ELRS firmware

|                   |                                                                                                    |
| ----------------- | -------------------------------------------------------------------------------------------------- |
| serial_rx         | Pin used to receive CRSF signal from the handset                                                   |
| serial_tx         | Pin used to transmit CRSF telemetry to the handset (may be the same as the RX PIN)                 |
| serial1_rx        | Serial2 RX - ESP32 targets only                                                                    |
| serial1_tx        | Serial2 TX - ESP32 targets only                                                                    |
| radio_busy        | GPIO Input connected to SX128x busy pin                                                            |
| radio_dio0        | Unused on SX128x, Interrupt pin for SX127x                                                         |
| radio_dio1        | Interrupt pin for SX128x                                                                           |
| radio_miso        | MISO connected to (possibly) multiple SX1280/127x                                                  |
| radio_mosi        | MOSI connected to (possibly) multiple SX1280/127x                                                  |
| radio_nss         | Chip select pin for first SX1280/127x                                                              |
| radio_rst         | Reset pin connected to (possibly) multiple SX1280/127x                                             |
| radio_sck         | Clock pin connected to (possibly) multiple SX1280/127x                                             |
| radio_busy_2      | Busy pin for second SX1280                                                                         |
| radio_dio0_2      | Interrupt pin for second SX127x                                                                    |
| radio_dio1_2      | Interrupt pin for second SX1280                                                                    |
| radio_nss_2       | Chip select pin for second SX1280                                                                  |
| radio_rst_2       | Reset pin connected to second SX1280/127x                                                          |
| radio_dcdc        | Use the SX1280 DC-DC converter rather than LDO voltage regulator (15uH inductor must be present)   |
| radio_rfo_hf      | SX127x PA to use, either the RFO_HF or PA_BOOST (depends on circuit design)                        |
| ant_ctrl          | Pin connected to Antenna select pin on power amplifier                                             |
| ant_ctrl_compl    | Inverted CTRL for devices using antenna selectors that need separate pins for A/B selection        |
| power_enable      | Enable the power amplifier (active high)                                                           |
| power_apc2        | Power amplifier control voltage                                                                    |
| power_rxen        | Enable RX mode LNA (active high)                                                                   |
| power_txen        | Enable TX mode PA (active high)                                                                    |
| power_rxen_2      | Enable RX mode LNA on second SX1280 (active high)                                                  |
| power_txen_2      | Enable TX mode PA on second SX1280 (active high)                                                   |
| power_pdet        | Analog input (up to 1.1V) connected to 'power detect' pin on PA for adjustment of the power output |
| joystick          | Analog Input (3.3V max) use to read joystick direction using a resistor network                    |
| five_way1         | These 3 pins create a binary value for the joystick direction                                      |
| five_way2         | 7 = IDLE, 6 = OK, 5 = DOWN                                                                         |
| five_way3         | 4 = RIGHT, 3 = UP, 2 = LEFT                                                                        |
| led_rgb           | Signal pin for WS2812 RGB LED or LED strip                                                         |
| led               | Only use when only a single LED is used                                                            |
| led_red           | If there are multiple LEDs, then this is the pin for the RED LED                                   |
| led_green         | If there is a GREEN LED as well as RED above                                                       |
| led_blue          | Pin for a 3rd, BLUE, LED!                                                                          |
| button            | Single/first (active low) button                                                                   |
| button2           | Second (active low) button                                                                         |
| screen_cs         | Screen Chip Select (if using SPI)                                                                  |
| screen_dc         | Screen Data/Command Select (if using SPI)                                                          |
| screen_mosi       | Screen Data (if using SPI)                                                                         |
| screen_rst        | Screen Reset                                                                                       |
| screen_sck        | Screen Clock (either SPI or I2C)                                                                   |
| screen_sda        | Screen Data (I2C)                                                                                  |
| screen_bl         | Screen Backlight                                                                                   |
| debug_backpack_rx | Connected to TX pin on backpack                                                                    |
| debug_backpack_tx | Connected to RX pin on backpack                                                                    |
| backpack_boot     | Pin connected to GPIO0 pin on backpack ESP8285, allows passthrough flashing                        |
| backpack_en       | Pin connected to EN pin on backpack ESP8285, allows passthrough flashing                           |
| i2c_scl           | I2C clock pin used to communicate with I2C devices (may be the same as OLED I2C)                   |
| i2c_sda           | I2C data pin used to communicate with I2C devices (may be the same as OLED I2C)                    |
| misc_fan_en       | Pin used to enable a cooling FAN (active HIGH)                                                     |
| misc_fan_pwm      | If the fan is controlled by PWM                                                                    |
| misc_fan_tacho    | If the fan has a "tachometer" interrupt pin                                                        |
| misc_gsensor_int  | Pin connected the STK8xxx g-sensor for interrupts                                                  |