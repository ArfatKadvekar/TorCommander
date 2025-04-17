# 🛡️ TorCommander – The Toralizer

![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)
![Platform](https://img.shields.io/badge/Platform-Linux-informational)
![Status](https://img.shields.io/badge/Status-Active-brightgreen)
![Open Source](https://img.shields.io/badge/Open--Source-Yes-green)

---

## 🔍 Overview

**TorCommander** is a lightweight, open-source Linux tool that anonymizes terminal command executions by routing traffic through the **Tor network**. Designed with simplicity and privacy in mind, it helps users protect their identity and bypass restrictive firewalls.

Inspired by cybersecurity advocate **Dr. Jones Birch**, the project takes the concept further—offering a practical, minimal, and easily extensible tool for secure, command-line-based internet access.

---

## 🚀 Features

- 🔐 **Tor Integration** – Automatically channels commands through the Tor network.
- 🧠 **Toralization via Keyword** – Just use `toralize` before a command to anonymize it.
- 🌍 **IP & Location Masking** – Your real IP address and geolocation stay hidden.
- ⚖️ **LD_PRELOAD Technique** – Seamlessly intercepts network calls using dynamic linking.
- 📚 **Educational & Research Friendly** – Great for learning about system-level privacy and dynamic linking.
- 📁 **Modular Codebase** – Clean structure with `toralize.c`, `toralize.h`, and `Makefile` for easy builds.

---

## ⚙️ Installation

### Prerequisites

Make sure the following dependencies are installed on your Linux system:

- **Tor**
- **GCC**
- **Make**

### Steps

```bash
sudo apt update
sudo apt install tor gcc make
```

1. **Clone the repository**:
```bash
git clone https://github.com/Anay-Patil/torcommander.git
cd torcommander
```

2. **Compile the program**:
```bash
make
```

3. **Install the `toralize` script globally**:

There are **two approaches** to use `toralize` globally:

### Approach 1: With Provided Script
If the `toralize.sh` script is already available:
```bash
sudo cp toralize.sh /usr/bin/toralize
sudo chmod +x /usr/bin/toralize
```

### Approach 2: Manually Create the Script
If you do not have `toralize.sh`, manually create it:
```bash
echo -e '#!/bin/bash\n\nexport LD_PRELOAD=/path/to/toralize.so\n${@}\nunset LD_PRELOAD' | sudo tee /usr/bin/toralize > /dev/null
sudo chmod +x /usr/bin/toralize
```
> Replace `/path/to/toralize.so` with the actual path where `toralize.so` is located, for example `/home/user/TorCommander/toralize.so`.

---

## ⚠️ Troubleshooting
If a command doesn't work properly, try using:
```bash
toralize curl --resolve http://example.com
```

---

## ⌨️ Usage

To run any command anonymously, just prefix it with `toralize`:
```bash
toralize curl http://check.torproject.org
```

### Supported Commands
The following types of commands are compatible:
- `curl`, `wget`, `ping`
- Any command making socket-based network calls
- DNS resolution and TCP-based communication tools

> Note: Not all system commands go through the network; `toralize` affects only those that do.

---

## 🌐 Applications

- 🔐 **Privacy-First App Testing**: Useful for devs testing privacy-focused applications.
- ⚖️ **Cybersecurity Research**: Ideal for experiments in anonymity, censorship, or secure networking.
- 🏫 **Education**: A hands-on tool for OS and networking labs demonstrating LD_PRELOAD and socket redirection.
- 🎓 **Restricted Network Use**: Helps users access educational or public resources in filtered environments.
- 📰 **Journalism & Activism**: Enhances anonymity for users in sensitive regions.
- 🌟 **End-User Benefit**: General users can stay private online with minimal setup and technical know-how.

---

## 🌿 Sustainability Goals

This project aligns with:
- **SDG 9**: Promotes robust, secure, and innovative digital infrastructure.
- **SDG 16**: Strengthens digital rights, privacy, and fair access.

---

## 📄 License

This project is licensed under the **MIT License**. Feel free to modify and use it as needed. See the [LICENSE](LICENSE) file for details.

---

## 📖 References

| Sr. No | Reference Title                          | Source                                                      |
|--------|------------------------------------------|-------------------------------------------------------------|
| 1      | The Tor Project Documentation            | https://www.torproject.org                                  |
| 2      | SOCKS4 Protocol Specification            | https://www.openssh.com/txt/socks4.protocol                 |
| 3      | LD_PRELOAD in Linux                      | https://man7.org/linux/man-pages/man8/ld.so.8.html          |
| 4      | POSIX Socket Programming Concepts        | https://man7.org/linux/man-pages/man2/connect.2.html        |
| 5      | Understanding SOCKS Proxies              | https://www.haproxy.org/download/1.8/doc/proxy-protocol.txt |

---

## 🚀 Contributing

We welcome contributions from the open-source community!

### How to Contribute

1. **Fork** this repository.
2. Create a **new branch** with your feature or fix.
3. **Commit** your changes and push the branch.
4. Open a **Pull Request** and describe your changes.

Please ensure your code follows standard conventions and is well-documented.

---

**TorCommander** is community-supported. Contributions and feedback are welcome!

> Made with ❤️ for freedom and privacy. By Arfat Kadvekar, Inspired by Dr. Jones Birch
