# oblivion-scale

Early **v0 prototype** - open-sourcing the CAD and firmware as a starting point. The rough edges below are exactly where help is welcome.

## Known issues / help wanted

**Body** - v0 is modeled around non-standard parts.
- Re-spec the body around standard, AliExpress-available components.

**Wiring diagram** - v0 is very messy.
- Re-draw the diagram and add a 2-button version.

> [!WARNING]
> Data pins can be changed, but the **wake button** data line **must** be on an **RTC GPIO pin**; otherwise it cannot wake the ESP32 from deep sleep.

**Code** - works, but needs improvement.
- Update for a faster refresh rate.
- Later: add BLE for phone-app compatibility.

**BOM** — needs creating.

## Roadmap

- **Now (v0) - Working prototype:** open-sourcing the body CAD and firmware as a starting point.
- **v1 - Fully open & sourceable:** redesign the body around standard, AliExpress-available parts so anyone can build it cheaply *(bottleneck: load cell)* and improve performance *(bottleneck: ADC)*.
- **v2 - Custom PCB:** a purpose-built board to shrink it further and improve performance.
- **v3 - "Premium" build:** a aluminium and glass version.
