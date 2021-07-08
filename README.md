<!--
*** Thanks for checking out the Best-README-Template. If you have a suggestion
*** that would make this better, please fork the repo and create a pull request
*** or simply open an issue with the tag "enhancement".
*** Thanks again! Now go create something AMAZING! :D
Ref: https://github.com/othneildrew/Best-README-Template/edit/master/README.md
-->



<!-- PROJECT SHIELDS -->
<!--
*** I'm using markdown "reference style" links for readability.
*** Reference links are enclosed in brackets [ ] instead of parentheses ( ).
*** See the bottom of this document for the declaration of the reference variables
*** for contributors-url, forks-url, etc. This is an optional, concise syntax you may use.
*** https://www.markdownguide.org/basic-syntax/#reference-style-links
-->
<!-- 
[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url]
[![LinkedIn][linkedin-shield]][linkedin-url]
-->


<!-- PROJECT LOGO -->
<!--
<br />
<p align="center">
  <a href="https://github.com/othneildrew/Best-README-Template">
    <img src="images/logo.png" alt="Logo" width="80" height="80">
  </a>

  <h3 align="center">Best-README-Template</h3>

  <p align="center">
    An awesome README template to jumpstart your projects!
    <br />
    <a href="https://github.com/othneildrew/Best-README-Template"><strong>Explore the docs »</strong></a>
    <br />
    <br />
    <a href="https://github.com/othneildrew/Best-README-Template">View Demo</a>
    ·
    <a href="https://github.com/othneildrew/Best-README-Template/issues">Report Bug</a>
    ·
    <a href="https://github.com/othneildrew/Best-README-Template/issues">Request Feature</a>
  </p>
</p>
-->


<!-- TABLE OF CONTENTS -->
<!--
<details open="open">
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#roadmap">Roadmap</a></li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#acknowledgements">Acknowledgements</a></li>
  </ol>
</details>
-->



<!-- ABOUT THE PROJECT -->
# About the project

The Arduino board is used to communicate with the external device through RS-485 Modbus-RTU. 
The device responses are resolved by the Arduino with cyclic redundancy check (CRC) and outputted to the human-machine interface (HMI).


[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)
[![Contributor Covenant](https://img.shields.io/badge/Contributor%20Covenant-2.0-4baaaa.svg)](code_of_conduct.md)


# Brief description

Suggested board: 
1. Arduino MEGA 2560 Rev3

Purpose: 
1. Send Modbus-RTU command to the device through RS-485 via the assigned "RS485_Serial."
1. Get responses from the device through RS-485.
1. Send the device responses to the human-machine interface (HMI) via the assigned "HMI_Serial."
1. Arduino can monitor the device responses from the serial monitor.

Suggested hardware setup: 
1. A "RS-485 to TTL module" is used to convert the RS-485 signal because Arduino MEGA 2560 Rev3 does not support RS-485 directly.
1. A HMI with the UART interface is used to show the device responses through the assigned HMI_Serial channel of the Arduino.
    


<!-- GETTING STARTED -->
<!--
# Getting Started

This is an example of how you may give instructions on setting up your project locally.
To get a local copy up and running follow these simple example steps.
-->


<!-- USAGE EXAMPLES -->
# Usage
The codes are in the [code](code) directory.

| #    | Sketch name and key differences                                                                                    | Date       |
| ---- | -------------------------------------------------------------------------------------------------- | ---------- |
|    5 | Name: <br/> [RS-485_Modbus-RTU_Call_Response_and_HMI_display_with_CRC.ino](code/RS-485_Modbus-RTU_Call_Response_and_HMI_display_with_CRC.ino) <br/> Difference: <br/> CRC function added. <br/> `#define HMI_Serial   Serial1 // Assign serial port` <br/>  `#define RS485_Serial Serial3 // Assign serial port` | 2021-07-08 |
|    4 | Name: <br/> [RS-485_Modbus-RTU_Call_Response_and_HMI_display_without_CRC_v04.ino](code/RS-485_Modbus-RTU_Call_Response_and_HMI_display_without_CRC_v04.ino) <br/> Difference: <br/>  `#define HMI_Serial   Serial1 // Assign serial port` <br/>  `#define RS485_Serial Serial3 // Assign serial port` | 2021-07-07 |
|    3 | Name: <br/> [RS-485_Modbus-RTU_Call_Response_and_HMI_display_without_CRC_v03.ino](code/RS-485_Modbus-RTU_Call_Response_and_HMI_display_without_CRC_v03.ino) <br/> Difference: <br/>  `Serial1.begin(  9600);  // Serial3 for RS-485 to TTL` <br/>  `Serial2.begin(115200);  // Serial1 for HMI with UART interface` | 2021-07-06 |
|    2 | Name: <br/> [RS-485_Modbus-RTU_Call_Response_and_HMI_display_without_CRC_v02.ino](code/RS-485_Modbus-RTU_Call_Response_and_HMI_display_without_CRC_v02.ino) <br/> Difference: <br/>  `Serial1.begin(  9600);  // Serial3 for RS-485 to TTL` <br/>  `Serial2.begin(115200);  // Serial2 for HMI with UART interface` | 2021-07-06 |
|    1 | Name: <br/> [RS-485_Modbus-RTU_Call_Response_and_HMI_display_without_CRC_v01.ino](code/RS-485_Modbus-RTU_Call_Response_and_HMI_display_without_CRC_v01.ino) <br/> Difference: <br/>  `Serial1.begin(  9600);  // Serial1 for RS-485 to TTL` <br/>  `Serial2.begin(115200);  // Serial2 for HMI with UART interface` | 2021-07-06 |




<!-- LICENSE -->
# License

Distributed under the [MIT License](LICENSE).



<!-- CONTACT -->
# Contact

Author: Dr. Hsien-Ching Chung

ORCID: https://orcid.org/0000-0001-9364-8858

Project Link: [https://github.com/HsienChing/RS-485_Modbus-RTU_Call_Response_and_HMI_Display_with_CRC_for_Arduino](https://github.com/HsienChing/RS-485_Modbus-RTU_Call_Response_and_HMI_Display_with_CRC_for_Arduino)



<!-- ACKNOWLEDGEMENTS -->
# Acknowledgements
<!--
* [GitHub Emoji Cheat Sheet](https://www.webpagefx.com/tools/emoji-cheat-sheet)
* [Img Shields](https://shields.io)
* [Choose an Open Source License](https://choosealicense.com)
* [GitHub Pages](https://pages.github.com)
* [Animate.css](https://daneden.github.io/animate.css)
* [Loaders.css](https://connoratherton.com/loaders)
* [Slick Carousel](https://kenwheeler.github.io/slick)
* [Smooth Scroll](https://github.com/cferdinandi/smooth-scroll)
* [Sticky Kit](http://leafo.net/sticky-kit)
* [JVectorMap](http://jvectormap.com)
* [Font Awesome](https://fontawesome.com)
-->
H.C. Chung thanks all the contributors to this article for their valuable discussions and recommendations, especially Jung-Feng Lin, Hsiao-Wen Yang, Yen-Kai Lo, An-De Andrew Chung.

This work was supported in part by Super Double Power Technology Co., Ltd., Taiwan under grant SDP-RD-PROJ-001-2020.



<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
<!--
[contributors-shield]: https://img.shields.io/github/contributors/othneildrew/Best-README-Template.svg?style=for-the-badge
[contributors-url]: https://github.com/othneildrew/Best-README-Template/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/othneildrew/Best-README-Template.svg?style=for-the-badge
[forks-url]: https://github.com/othneildrew/Best-README-Template/network/members
[stars-shield]: https://img.shields.io/github/stars/othneildrew/Best-README-Template.svg?style=for-the-badge
[stars-url]: https://github.com/othneildrew/Best-README-Template/stargazers
[issues-shield]: https://img.shields.io/github/issues/othneildrew/Best-README-Template.svg?style=for-the-badge
[issues-url]: https://github.com/othneildrew/Best-README-Template/issues
[license-shield]: https://img.shields.io/github/license/othneildrew/Best-README-Template.svg?style=for-the-badge
[license-url]: https://github.com/othneildrew/Best-README-Template/blob/master/LICENSE.txt
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://linkedin.com/in/othneildrew
[product-screenshot]: images/screenshot.png
-->
