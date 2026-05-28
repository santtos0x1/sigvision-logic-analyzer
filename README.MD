# SigVision — Logic Analyzer

<p align="center">
  <img src="./docs/sigvision_logo/sigvision_ascii_logo.svg" width="680" alt="SigVision Logo"/>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/MCU-STM32F411-03234B?style=flat-square&logo=stmicroelectronics&logoColor=white" alt="MCU: STM32F411"/>
  <img src="https://img.shields.io/badge/Core-ARM%20Cortex--M4-00979D?style=flat-square&logo=arm&logoColor=white" alt="Core: ARM Cortex-M4"/>
  <img src="https://img.shields.io/badge/Clock-84MHz-brightgreen?style=flat-square" alt="Clock: 84MHz"/>
  <img src="https://img.shields.io/badge/Channels-8%20Digital-blue?style=flat-square" alt="Channels: 8 Digital"/>
  <img src="https://img.shields.io/badge/Language-C-A8B9CC?style=flat-square&logo=c&logoColor=white" alt="Language: C"/>
  <img src="https://img.shields.io/badge/License-MIT-yellow?style=flat-square" alt="License: MIT"/>
</p>

 SigVision is a high-performance embedded logic analyzer built around the STM32F411 microcontroller. It provides 8 digital probe channels, configurable sampling rates, real-time signal acquisition, and a modular firmware architecture designed for low-level debugging, protocol analysis, and embedded systems experimentation.

## Features

- 8 Digital Channels — 8 independent acquisition channels via GPIO, with digital probe support for simultaneous monitoring of multiple signals

- 84 MHz Sampling Engine — Configurable sampling rate leveraging the STM32F411's maximum clock, enabling high-frequency signal capture with precision

- Real-Time Signal Acquisition — Continuous low-latency signal capture, suitable for protocol debugging and timing analysis

- Modular Firmware Architecture — Firmware structure designed for easy extension, allowing new protocols, triggers, and acquisition modes to be added

- Budget-Friendly — Accessible hardware based on the STM32F411, making professional logic analysis viable without expensive lab equipment
