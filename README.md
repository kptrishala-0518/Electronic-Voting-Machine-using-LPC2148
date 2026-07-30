# Electronic-Voting-Machine-using-LPC2148
Password-Protected Electronic Voting Machine using LPC2148 ARM7 with LCD, Keypad, Push Buttons, LEDs, Keil µVision and Proteus Simulation.

# Electronic Voting Machine using LPC2148

## Overview

The **Electronic Voting Machine (EVM) using LPC2148** is an embedded systems project designed to demonstrate a secure and user-friendly electronic voting process using the ARM7-based LPC2148 microcontroller. The project integrates password-based voter authentication, candidate selection through push buttons, real-time vote confirmation using LEDs, and result display on a 16×2 LCD. The objective of the system is to ensure that only authorized users can cast their vote while maintaining the principle of **one person, one vote**.

The application was developed in **Embedded C** using **Keil µVision**, where the source code was compiled to generate a HEX file. This HEX file was then loaded into the **Proteus 8 Professional** simulation environment to emulate the complete hardware setup. The project demonstrates the complete embedded development workflow, from software development and compilation to hardware simulation and verification.

---

## Objectives

The primary objective of this project is to design and implement a simple, secure, and reliable electronic voting system that demonstrates the practical application of embedded systems in real-world scenarios. The system aims to authenticate voters using predefined passwords, prevent unauthorized voting, provide an intuitive user interface through an LCD and keypad, accurately count votes, and display the final election results automatically.

---

## Key Features

The Electronic Voting Machine incorporates several features that enhance both functionality and security:

- Password-based voter authentication before allowing access to the voting process.
- One person–one vote mechanism to prevent duplicate voting.
- Four voting options, including three political parties and a NOTA (None of the Above) option.
- LCD-based user interface for displaying instructions, authentication status, voting confirmation, and election results.
- LED indication to provide immediate visual confirmation after a successful vote.
- Automatic vote counting and result computation.
- Manual termination of the voting process through a dedicated end button.
- Automatic declaration of the winning candidate or display of appropriate messages in case of a tie or NOTA majority.

---

## Hardware Components

The hardware components used in this project include:

- LPC2148 ARM7TDMI Microcontroller
- 16×2 Alphanumeric LCD Display
- 4×3 Matrix Keypad
- Push Buttons for Candidate Selection
- LEDs for Vote Confirmation
- Resistors and Supporting Circuit Components

---

## Software and Development Tools

The project was developed and tested using the following software tools:

- Embedded C Programming Language
- Keil µVision IDE
- ARM Compiler
- Proteus 8 Professional Simulation Software

---

## Development Workflow

The implementation of the project follows the standard embedded systems development process.

```text
Embedded C Source Code
          │
          ▼
   Keil µVision IDE
          │
          ▼
   ARM Compiler
          │
          ▼
  HEX File Generation
          │
          ▼
 Proteus 8 Simulation
          │
          ▼
 LPC2148 Microcontroller
          │
          ▼
 LCD + Keypad + LEDs + Push Buttons
```

---

## Working Principle

The system begins by initializing all peripheral devices, including the LCD, keypad, GPIO ports, and LEDs. Once initialized, the LCD displays a welcome message indicating that the voting process has started.

Each voter is prompted to enter a predefined four-digit password using the matrix keypad. The entered password is validated against a list of stored passwords. A maximum of three attempts is allowed for authentication. Upon successful verification, the voter is granted access to cast a vote. If authentication fails three consecutive times, access is denied and the voter is locked out.

After successful authentication, the voter selects one of the available candidates using dedicated push buttons. Once a button is pressed, the corresponding vote counter is incremented, an LED briefly illuminates to confirm the vote, and the LCD displays a confirmation message indicating that the vote has been successfully recorded.

The voting process continues until either all registered voters have voted or the designated end button is pressed. Once voting is complete, the system displays the total number of votes received by each candidate and the NOTA option. Based on the vote counts, the microcontroller determines the winner and displays the final result on the LCD. If no candidate achieves a clear majority, an appropriate message is displayed.

---

## Project Structure

```
Electronic-Voting-Machine-LPC2148
│
├── Source_Code/
├── Keil_Project/
├── Hex_File/
├── Proteus/
├── Documentation/
└── README.md
```

---

## Applications

The proposed Electronic Voting Machine can be used for educational demonstrations, laboratory experiments, prototype development, small-scale elections, student council elections, mock polling activities, and embedded systems training. It serves as an excellent example of secure embedded application development using ARM-based microcontrollers.

---

## Future Scope

Although the current implementation demonstrates the fundamental concepts of electronic voting, the system can be further enhanced by incorporating additional security and storage mechanisms. Possible future improvements include:

- Fingerprint-based biometric authentication.
- RFID or Smart Card-based voter identification.
- External EEPROM or SD card for permanent vote storage.
- Wireless transmission of election results.
- AES-based encryption for enhanced data security.
- Real-Time Clock (RTC) integration for timestamping votes.
- IoT-based remote monitoring and centralized result management.

---

## Learning Outcomes

Through this project, the following concepts were explored and implemented:

- ARM7 LPC2148 Microcontroller Programming
- Embedded C Programming
- GPIO Configuration
- LCD Interfacing
- Matrix Keypad Interfacing
- Push Button Handling
- Embedded System Design
- Keil µVision Development
- HEX File Generation
- Proteus-Based Hardware Simulation
- Secure Embedded Application Development

---

## Author
**Trishala K**
Department of Electronics and Communication Engineering
Amrita Vishwa Vidyapeetam, Bengaluru Campus

B.Tech Electronics and Computer Engineering  
Amrita Vishwa Vidyapeetham, Bengaluru
