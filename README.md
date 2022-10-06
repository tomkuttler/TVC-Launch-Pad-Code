<div align="center">

# TVC-Launch-Pad-Code

![Arduino](https://img.shields.io/badge/-Arduino-00979D?style=for-the-badge&logo=Arduino&logoColor=white)
![C](https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white)
![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white)

This repository contains the source code for a launch pad specifically designed for model rockets with thrust vector control. The launch pad has the ability to detect a radio signal from a remote control, which triggers a 30-second countdown. It also includes various safety features such as stabilizers, strongback support, and clamp retraction to ensure a safe launch.

</div>

## Table of contents

- [Installation](#installation)
- [Usage](#usage)
- [Features](#features)
- [Contributing](#contributing)
- [License](#license)

## Installation

To use this software, you will need a Teensy 4.1 board and the Arduino IDE with the Teensy Loader Application. Follow these steps to install the software:

1. Clone the repository to your local machine.
2. Open the `Launch_Pad_Code.ino` file in the Arduino IDE.
3. Upload the code to your Teensy.

## Usage

On startup the strongback needs to be held vertically, so the stbilizer can grab the rocket. After the startup process has completed you will here a sound. The motor igniters need to be inserted in the rocket motors and afterwards connected to the board computer of the launch pad. After clearing the launch area, the countdown can be started with the remote control.

## Features

- Radio signal detection: The launch pad can detect the start radio signal from a remote control via a HC-12 radio module. The software for the remote control is uploaded on a separate [Github repository](https://github.com/tomkuttler/TVC-Launch-Pad-Remote).
- Countdown timer: The launch pad starts a countdown timer once the radio signal is detected. The countdown is 30 seconds long.
- Stabilizers: 15 seconds before launch, the stabilizers, which provided additional stability to the rocket, will open.
- Strongback retraction: 13 seconds before launch, the strongback of the launch pad will retract to clear the way for the rocket.
- Clamps retraction: 150 milliseconds before launch, the clamps that hold the rocket to the pad will be retracted, allowing the rocket to take off.
- Pyrochannel: At launch, the launch pad will fire its pyrochannel to ignite the rocket motors.

## Contributing

If you would like to contribute to this project, please follow these steps:

1. Fork the repository to your own account.
2. Create a new branch with your changes.
3. Submit a pull request with your changes.

## License

</a>This work is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/">Creative Commons Attribution-ShareAlike 4.0 International License</a>.
You are free to use, copy, modify, distribute, and display the work, as well as make derivative works based on it, as long as you give attribution to the original author and share any derivative works under the same license. For more information about the license, please see the `LICENSE.md` file.
<div align="center">
<a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-sa/4.0/88x31.png" /></div>