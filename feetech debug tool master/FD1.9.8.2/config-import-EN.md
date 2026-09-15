# FD debug tool — servo configuration import (translated from the original Chinese docs)

English summary of `导入本地参数.docx` ("Import local parameters") and `导入离线参数.docx` ("Import offline
parameters"), which are almost entirely screenshots with little text of their own — extracted and
translated here rather than editing the original `.docx` files in place.

Original filename of the (empty) companion `.txt` file, translated: *"Import local parameters is for testing
firmware; import offline parameters is for situations with no network."*

## Background

On first launch, FD.exe (the official Feetech servo debug tool) tries to fetch a servo model/configuration
database from the internet so it can recognize a servo's model number after a bus search. Without a network
connection this fails with a dialog:

> **Runtime error** — "Unable to import servo configuration file, please check network!"
> (Chinese: 运行错误 / 无法导入舵机配置文件，请检查网络！)

Until this database is imported, a found servo shows as `未知型号` ("Unknown model") in the servo list, and
the feedback panel shows `状态: 通信超时` ("Status: communication timeout").

## Workflow 1 — Import local parameters (`Ctrl+N`)

For a machine where the database was already downloaded at some point (cached locally):

1. Switch to the **调试 (Debug)** tab.
2. Click **搜索 (Search)** to scan the bus for servos.
3. Click the servo entry in the ID/model list to select it, then press **Ctrl+N**.
4. A confirmation dialog appears: **"导入本地配置文件!"** ("Local config file imported!").
5. Click **搜索 (Search)** again and re-select the servo — its model now resolves (e.g. `SM85-360M`
   instead of `未知型号`), and the feedback panel shows `状态: 通信正常` ("Status: communication normal").

## Workflow 2 — Import offline parameters (`Ctrl+M`)

For a fully air-gapped machine, with a configuration file placed manually next to `FD.exe`
(same folder as `FD.exe` / `FDUpdate.exe`):

1. Drop the offline configuration file in the same directory as `FD.exe`.
2. In the servo list, click the entry then press **Ctrl+M**.
3. A confirmation dialog appears: **"导入离线配置文件!"** ("Offline config file imported!").

## Why this matters for Feetech Control

This confirms the same constraint our own roadmap already designed around (see the roadmap of the
**Feetech Control** project, a separate repo): a servo debug tool needs a model/register
database to be *useful offline*, and the official vendor tool's own failure mode when that database isn't
locally available is exactly the kind of "network trap" we want to avoid — our plan bundles the servo
memory-table constants (SMS_STS/SCSCL/HLSCL) directly inline in the web app instead of fetching them, so
Feetech Control never hits an equivalent "please check network" dead end, whether opened locally or from
robot-maker.com.

The main debug window (`调试`, i.e. "Debug" tab) is also a useful reference for our own V3/V4 roadmap phases:
- A live multi-channel chart with checkboxes to toggle position (黑/black), torque (红/red), speed
  (绿/green), current (青/cyan), temperature (米/tan), voltage (紫/purple), plus horizontal pan/zoom and
  upper/lower axis limits.
- A feedback panel showing voltage, torque, current, speed, temperature, position, moving state, target,
  and a communication status string.
- A "自动调试" (auto-sweep) section: start/end position, scan delay, step count/delay, with "扫描" (scan)
  and "步进" (step) actions — a back-and-forth sweep between two positions, logging the readings.
- A "数据分析" (data analysis) section: recording duration in seconds, a line counter, and export/clear
  buttons writing to `record.txt`.
