# ir-freqs-extractor

## Check what IR frequencies ConsumerIR HAL reports

Useful if you want to easily get them to write a custom HAL/HIDL for your device's IR sensor

## Building
- Clone this repo in external/ir-freqs-extractor
- Lunch your device or whatever `generic_<arch>` device you want (as long as it's the same arch as your device)
- `make ir-freqs-extractor`

## Usage
- Copy `out/target/<device>/vendor/bin/ir-freqs-extractor` to `/vendor/bin/ir-freqs-extractor`
- Either use ADB or a Terminal Emulator app in your phone, but keep in mind that you need root
- `adb root` (ADB) or `su` (Terminal Emulator)
- `/vendor/bin/ir-freqs-extractor`
- It should print a piece of code, example:

```c
static hidl_vec<ConsumerIrFreqRange> rangeVec {
    {.min = 30000, .max = 30000},
    {.min = 33000, .max = 33000},
    {.min = 36000, .max = 36000},
    {.min = 38000, .max = 38000},
    {.min = 40000, .max = 40000},
    {.min = 56000, .max = 56000},
};
```

Copy this in your HAL/HIDL source code
- Enjoy!
