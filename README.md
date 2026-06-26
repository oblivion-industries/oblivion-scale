# oblivion-scale
open source coffee scale

v0 body is modeled around non-standard parts 
-re-spec body around standard, AliExpress-available components

v0 wiring diagram is very messy 
-re-draw the diagram and add a 2 button version
/!\ data pins can be changed but wake button data must be on an RTC GPIO pin, otherwise it cannot wake the ESP32 from deep sleep

v0 code
-will need updating for faster refresh rate
-down the road, add BLE for phone app compatibility

BOM needs creating


===Roadmap===
Now (v0): working prototype: open-sourcing the body CAD and firmware as a starting point.
v1: Fully open & sourceable: redesign the body around standard, AliExpress-available parts so anyone can build it cheaply (bottlneck: load cell) and improve performance (bottleneck: ADC)
v2: Custom PCB: a purpose-built board to shrink it further and improve performance.
v3: Premium build: a refined aluminum-and-glass version.
