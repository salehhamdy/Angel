# The Gate of Encryption — Multi‑Algorithm File Crypter (C++ / Crypto++)

A terminal‑based utility that lets you **encrypt or decrypt any file** with your choice of **AES‑128, Twofish‑128, Triple DES (3DES) or Blowfish** in CBC mode.  
The tool is entirely self‑contained in a single **`main.cpp`** file and depends only on the [Crypto++](https://www.cryptopp.com/) library.

```
        +-+-+-+-+-+ +-+-+-+-+-+-+ +-+-+ +-+-+-+-+-+-+-+-+-+-+
        |T|h|e| |G|a|t|e| |O|f| |E|n|c|r|y|p|t|i|o|n|
        +-+-+-+-+-+ +-+-+-+-+-+-+ +-+-+ +-+-+-+-+-+-+-+-+-+-+
```

> **Author credits:** Mohamed Ashraf (aka *TheKnower0x0*), Shady Salem, Ahmed Amin, Saleh Ayoub, and Mokhtar Khalifa.  
> *Version 1.1*  — Find the original repo at <https://github.com/TheKnower0x0/The-Guardian-Angel>.

---

## Features

- 🔑 **Four industry algorithms** – AES‑128, Twofish‑128, Triple DES (EDE3), Blowfish‑128.
- 🔐 **Symmetric encryption & decryption** in CBC mode with zero‑IV (easy to swap in random IV).
- 🗂️ **Any file type** – works on text, images, executables, archives, etc.
- 💾 **Non‑destructive** – output written to `<file>.enc` (encrypt) or `<file>.dec` (decrypt) alongside the original.
- 🎨 **ASCII art banners** – colourful intro / success screens for extra flair.

---

## Folder / File Tree

```
📁 project_root/
└── main.cpp          # The complete source (shown above)
```

*(All other screenshots/files shown previously are unrelated; keep only what you need.)*

---

## Build Instructions

### Prerequisites

| Requirement | Notes |
|-------------|-------|
| **C++17 compiler** | g++ ≥ 9, clang ≥ 10, or MSVC 2019+ |
| **Crypto++ 8.9+** | Build & install (or link via `vcpkg install cryptopp`) |

### Linux / macOS / WSL

```bash
# 1) Install Crypto++ (Ubuntu example)
sudo apt install libcrypto++-dev libcrypto++-doc

# 2) Compile
g++ -std=c++17 -Wall -Wextra -O2 main.cpp -lcryptopp -o the_gate
```

### Windows (MSVC)

```powershell
# Assuming Crypto++ compiled as static library cryptlib.lib
cl /std:c++17 /EHsc main.cpp cryptlib.lib /Fe:the_gate.exe
```

Or via **vcpkg**:

```bash
vcpkg install cryptopp
# then add the include/lib paths when invoking g++/clang++
```

---

## Usage

```text
$ ./the_gate

█████████  The Gate of Encryption  v1.1  █████████

Enter 'e' to encrypt or 'd' to decrypt: e
[1] AES
[2] Twofish
[3] Triple DES
[4] Blowfish
[0] Exit
Choose an algorithm: 1
Enter the file path: secret.pdf
Enter the security key password: p@55w0rd!

Encryption completed successfully.
```

- **Encrypt:** choose *e*, pick algorithm, supply file path and a password (key).  Creates `secret.pdf.enc`.
- **Decrypt:** choose *d* with the same algorithm + password used during encryption.  Produces `secret.pdf.dec`.

> **Key length:** the password is truncated / padded to the algorithm’s default key length (16 bytes for AES/TWF/Blowfish, 24 bytes for 3DES).  Increase entropy by using long, random passphrases.

---

## Security Notes & Recommendations

* The IV is currently **all‑zero** for simplicity.  For production, generate a random IV per file and prepend/store it with the ciphertext.
* Passwords are used **directly as keys** (no KDF).  Integrate PBKDF2, scrypt or Argon2 to derive keys securely.
* CBC mode provides confidentiality but no authenticity.  Consider adding an HMAC or switch to an authenticated mode like GCM or EAX.
* Do **not** rely on this demo for sensitive data without the above hardening.

---

## Extending the Tool

| Idea | Quick Hint |
|------|-----------|
| Add **GUI** | Wrap the binary with Qt or Dear ImGui. |
| **Random IV** support | `AutoSeededRandomPool prng; prng.GenerateBlock(iv, AES::BLOCKSIZE);` |
| **KDF** | Use `PKCS5_PBKDF2_HMAC<SHA256>` to expand user password. |
| Switch to **GCM** | Replace `CBC_Mode` with `GCM<AES>` for AEAD. |
| **Multi‑thread** | Spawn threads for batch file encryption. |

---

## License

Code is provided under the **MIT License** – see upstream repository for details.

---

## Acknowledgments

Built with the excellent **Crypto++** library by Wei Dai and contributors.
