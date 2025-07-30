# 🗣️ Minitalk

This project is a lightweight client-server communication system built in C, utilizing UNIX signals to transmit messages. The client sends a message to the server, which receives and displays it character by character.

<img width="1904" height="987" alt="image" src="https://github.com/user-attachments/assets/04250274-a5fb-48f2-9c69-04345bf7ac9f" />


## 📖 Table of Contents

- [Usage](#usage)
- [How Minitalk Works](#how-minitalk-works)
  - [Client](#client)
  - [Server](#server)
  - [Bonus Features](#bonus-features)
  - [Key Functions](#key-functions)
- [Credits](#credits)

## Usage

1. Clone the repository:

   ```bash
   git clone https://github.com/your-username/minitalk.git
   ```

2. Compile the source code using the provided Makefile:

   ```bash
   make
   ```

   This generates two executables: `client` and `server`.

3. Launch the server:

   ```bash
   ./server
   ```

   The server will display its process ID (PID).

4. In a separate terminal, run the client with the server’s PID and a message:

   ```bash
   ./client <server_pid> <message>
   ```

   Example:

   ```bash
   ./client 12345 "Hello, World!"
   ```

   The server will display the message: `Hello, World!`

5. Repeat step 4 to send additional messages.

## How Minitalk Works

Minitalk uses UNIX signals (`SIGUSR1` and `SIGUSR2`) to enable communication between the client and server. Each character in the message is converted into an 8-bit binary sequence and transmitted bit by bit.

### Client

- Reads the server’s PID and message from command-line arguments.
- Iterates through each character in the message.
- Converts each character into 8 bits and sends them as signals (`SIGUSR1` for 1, `SIGUSR2` for 0).
- Uses `usleep(42)` to introduce a delay between signals, ensuring the server can process them.

### Server

- Displays its PID upon startup.
- Configures signal handlers for `SIGUSR1` and `SIGUSR2` using `sigaction`.
- Enters an infinite loop, waiting for signals with `pause`.
- Reconstructs each character from received bits and prints it using `ft_printf`.
- Sends acknowledgment signals back to the client for each received bit.

### Bonus Features

The bonus version (`client_bonus.c` and `server_bonus.c`) includes:

- Support for Unicode characters (e.g., 🦁).
- Read receipt mechanism:
  - The client logs each sent bit (`Received bit 1` for `SIGUSR1`, `Received bit 0` for `SIGUSR2`).
  - The server acknowledges each bit by sending the same signal back to the client.

### Key Functions

#### `send_signal` (client)

```c
void send_signal(int pid, unsigned char character)
```

- Converts a character into 8 bits using a temporary buffer.
- Shifts the character rightward to extract each bit.
- Sends `SIGUSR1` for odd (1) or `SIGUSR2` for even (0) bits based on modulo 2.

#### `handle_signal` (server)

```c
void handle_signal(int signal)
```

- Uses static variables `current_char` and `bit_index` to track the character being built.
- Extracts bit value using `current_char |= (signal == SIGUSR1)`.
- Shifts bits left and prints the character once 8 bits are received.
