# 🎮 Pac-Man Game for LandTiger V2.0 LPC1768 Development Board

![Pac-Man Banner](https://upload.wikimedia.org/wikipedia/en/2/2e/Pac-Man.png)

This repository contains a Pac-Man game developed for the LandTiger V2.0 development board, which is based on the NXP LPC1768 ARM Cortex-M3 microcontroller. The game leverages the board's Graphical LCD (GLCD) and Touch Panel (TP) peripherals to deliver an engaging user experience.

## 📜 Table of Contents

- [📌 Project Overview](#-project-overview)
- [✨ Features](#-features)
- [🛠️ Hardware Requirements](#-hardware-requirements)
- [💻 Software Requirements](#-software-requirements)
- [⚙️ Installation and Setup](#-installation-and-setup)
- [🎮 Usage](#-usage)
- [🤝 Contributing](#-contributing)
- [📜 License](#-license)
- [💡 Acknowledgments](#-acknowledgments)

## 📌 Project Overview

The Pac-Man game is implemented in C and demonstrates the capabilities of the LandTiger V2.0 development board's GLCD and TP. It serves as both an entertaining application and a reference for developers interested in graphics and touch input handling on embedded systems.

## ✨ Features

- 🎮 **Classic Pac-Man gameplay**
- 📱 **Responsive touch controls via the Touch Panel**
- 🖥 **Visuals rendered on the Graphical LCD**
- 👻 **AI-Controlled Ghost (Blinky)**
  - Blinky chases Pac-Man, becoming faster and more aggressive as the game progresses.
  - Two movement strategies:
    - 🚀 **Chase Mode:** Actively pursues Pac-Man.
    - 😨 **Frightened Mode:** When Pac-Man eats a "Power Pill," Blinky turns blue, runs away, and can be eaten for extra points.
  - 🔄 Respawns after 3 seconds if eaten.
  - 🧠 Pathfinding implemented using an algorithm like A*.
- 🎵 **Sound Effects and Background Music**
  - The speaker plays background music and in-game sound effects.
- 🔗 **CAN Bus Communication**
  - Displays **🏆 Score, ❤️ Remaining Lives, and ⏳ Countdown Timer** via the CAN bus.
  - Uses **external loopback mode** for CAN communication.
  - CAN1 sends messages, CAN2 receives messages.
  - Encodes data in a **32-bit unsigned int**:
    - **8 bits** for ⏱ remaining time.
    - **8 bits** for ❤️ remaining lives.
    - **16 bits** for 🏆 score.

## 🛠️ Hardware Requirements

- 🖥 [LandTiger V2.0 LPC1768 Development Board](https://os.mbed.com/media/uploads/wim/landtiger_v2.0_manual.pdf)
- 🔌 USB cable for power and programming
- ⚡ Optional: External power supply (if not powering via USB)

## 💻 Software Requirements

- [Keil µVision IDE](https://www.keil.com/uvsoarm/)
- [NXP LPC1768 CMSIS Library](https://www.keil.com/dd2/pack/)
- USB drivers for the LandTiger board

## ⚙️ Installation and Setup

1. **Clone the Repository:**

   ```bash
   git clone https://github.com/andreunifi/PacMan-Game.git
   cd PacMan-Game
