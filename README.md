# FeetechServo

Arduino library for Feetech bus servos: SCSCL, SMS/STS (SMSBL/SMSCL/STSCL) and HLSCL (HTS/HLS) series.

Originally forked in 2023 from Feetech's own `SCServoSDK` (published on Gitee at
`gitee.com/ftservo/SCServoSDK`), maintained since by [Robot-Maker-SAS](https://github.com/Robot-Maker-SAS).
Feetech's [FTServo_Arduino](https://github.com/ftservo/FTServo_Arduino) on GitHub is a separate, later
publication (Nov. 2024) by the same "ftservo" maintainer — not a direct ancestor of this repo, but close
enough in protocol and structure that comparing the two periodically is useful. See `说明.txt` for the
class hierarchy and file layout, and `examples/` for one example folder per instruction/servo family.

## Servo families

| Class     | Series               | Header/source          |
| --------- | -------------------- | ----------------------- |
| `SCSCL`   | SCSCL                 | `SCSCL.h` / `SCSCL.cpp`   |
| `SMS_STS` | SMSBL / SMSCL / STSCL | `SMS_STS.h` / `SMS_STS.cpp` |
| `HLSCL`   | HTS / HLS             | `HLSCL.h` / `HLSCL.cpp`   |

All three inherit from `SCSerial` (hardware interface) and `SCS` (communication protocol: framing,
checksum, ping/read/write/sync instructions).

## Usage

```cpp
#include <SCServo.h>

SMS_STS sms_sts;

void setup() {
  Serial1.begin(1000000);
  sms_sts.pSerial = &Serial1;
}
```

See `examples/` for complete sketches (ping, read/write position, synchronized multi-servo writes, EEPROM
programming...).

## Reading multiple values at once

`ReadStatus(ID, ServoStatus&)` runs `FeedBack` then fills a `ServoStatus` struct (position, speed, load,
voltage, temperature, moving state, current) in one call, instead of calling each `Readxxx(-1)` separately:

```cpp
ServoStatus status;
if (sms_sts.ReadStatus(1, status)) {
  Serial.println(status.Position);
}
```

## Retrying a flaky read

`readByteRetry`/`readWordRetry(ID, MemAddr, Retry = 5, DelayMs = 10)` (on `SCSerial`, available on all
three families) retry a read until it stops returning `-1`, instead of writing a manual retry loop.

## Communication errors vs servo status

`getState()` returns the servo's own alarm/status byte; `getLastError()` returns the last communication
error (`ERR_NO_REPLY`, `ERR_SLAVE_ID`, `ERR_BUFF_LEN`, `ERR_CRC_CMP`, from `INST.h`) — distinguishing a
timeout from an unexpected ID or a checksum mismatch, rather than a single ambiguous status byte.
