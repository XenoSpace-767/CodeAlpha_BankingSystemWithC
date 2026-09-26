# CodeAlpha_BankingSystemWithC

# Bank Account Management System — C

A persistent, structure-based C application that manages customer bank accounts, deposit/withdrawal routines, balance queries, and account listing using binary file storage (`fopen`, `fwrite`, `fread`, `fseek`)[cite: 5].

Developed as part of the **CodeAlpha C Programming Internship**[cite: 5].

---

## Features
* **File Persistence:** Saves account data inside binary database files (`bank_accounts.dat`)[cite: 5].
* **Deposit & Withdrawal Operations:** Updates account balances directly in place using `fseek`[cite: 5].
* **Balance Enquiry:** Fetches and displays account information by account number[cite: 5].
* **Formatted Output:** Renders formatted tabular summaries of registered accounts.

---

## How to Run

### Compilation & Execution

1. **Clone the repository:**
   ```bash
   git clone [https://github.com/YOUR_USERNAME/CodeAlpha_BankingSystem.git](https://github.com/YOUR_USERNAME/CodeAlpha_BankingSystem.git)
   cd CodeAlpha_BankingSystem
