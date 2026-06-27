# Bill of Materials, Open-Source Coffee Scale (v0)

This BOM reflects the v0 prototype. It's a working starting point, not a final parts list. Please read the two notes below before sourcing parts.

## Notes before you buy

**1. Load cell.**
v0 uses a specific, hard-to-source load cell. Selecting a widely-available equivalent is a goal for v1. Changing the load cell will require changes to the v0 CAD.

**2. Part footprints.**
The HX711, TTP223, and OLED ship on breakout boards whose dimensions vary between manufacturers. The v0 CAD is built around the specific boards used in the prototype, so boards of a different size may not fit the enclosure.

## Parts

| # | Part | Qty | Spec / what to get | Notes |
|---|------|-----|--------------------|-------|
| 1 | Microcontroller | 1 | Seeed XIAO ESP32-C3 | Built and tested on the C3. The XIAO ESP32-C6 is likely pin-compatible but untested; verify deep-sleep wake before relying on it. |
| 2 | Load cell | 1 | (see Note 1) | v0 used a specific hard-to-source cell. A different cell will require CAD changes. |
| 3 | Load cell ADC | 1 | HX711 24-bit ADC | The board used in the prototype is roughly 24 x 16 mm. Other footprints may not fit. |
| 4 | Touch sensor | 1 | TTP223 capacitive touch | The board used in the prototype is roughly 11 x 15 mm. Other footprints may not fit. |
| 5 | Display | 1 | 0.91" 128x32 OLED, I2C, SSD1306 driver | I2C address typically 0x3C; 4-pin (VCC / GND / SCL / SDA). PCB size varies by maker; the one used in the prototype is roughly 38 x 12 mm. |
| 6 | Battery | 1 | 502030 1S LiPo, 3.7 V | Connector type varies by supplier; source a matching connector to solder to the ESP32 accordingly. Check polarity before connecting: 1S LiPo connector polarity isn't standardized, and reversing it can damage the board. |
| 7 | Threaded inserts | as needed | M3 heat-set inserts | Paired with the M3 bolts below. |
| 8 | Bolts | as needed | M3 bolts | Length depends on final assembly. |
| 9 | Wire | as needed | Hookup wire, gauge to suit | No strict requirement; anything that looks right for low-current signal and power wiring will generally work fine. |
