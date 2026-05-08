# ELFS (Extremely Large File System)
**Scale:** 100 Hellabytes (Virtual)
**Platform:** Windows/C++17

## 1. Overview
ELFS is a simulated filesystem designed to handle massive address spaces using sparse file technology. It implements a strict directory hierarchy for system and user files.

### Directory Mapping
| Directory | File Extensions | Category |
| :--- | :--- | :--- |
| `/sys` | `.sys`, `.init`, `.iosf` | System Core |
| `/bin` | `.img`, `.iso`, `.bin` | Executables/Images |
| `/usr` | Everything else | User Data |

## 2. Prerequisites
- **Compiler:** GCC/G++ (MinGW on Windows)
- **Environment:** PowerShell or CMD
- **Standard:** C++17

## 3. Tutorial: How to Use

### Step 1: Compilation
Open your terminal in the project folder and run:
```bash
make
