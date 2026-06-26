# MiniRedis

A lightweight **Redis-inspired in-memory key-value store** implemented from scratch in **C++17** using **Object-Oriented Programming (OOP)** and the **C++ Standard Template Library (STL)**. 
The project demonstrates the core principles of modern in-memory databases, including **constant-time** key-value operations, persistence, conditional insertion, and automatic key expiration (TTL).

---

## Overview

MiniRedis is a simplified implementation of an in-memory database designed to explore the internal concepts behind Redis. 
Instead of functioning as a traditional database, it acts as a **high-speed cache layer** for storing temporary and frequently accessed data.

The project emphasizes modular software design, efficient data structures, and backend engineering concepts while remaining lightweight and easy to understand.

---

## Features

- Fast in-memory key-value storage
- Constant average-time (`O(1)`) CRUD operations using `std::unordered_map`
- Persistent storage through `SAVE` and `LOAD`
- Conditional insertion using the `NX` option
- Time-To-Live (TTL) support for automatic key expiration
- Interactive command-line interface
- Modular object-oriented architecture
- Simple command parser
- Database utility commands (`COUNT`, `KEYS`, `CLEAR`)

---

## Supported Commands

| Command | Description |
|----------|-------------|
| `SET key value` | Insert or update a key |
| `SET key value NX` | Insert only if the key does not already exist |
| `SET key value EXPIRE seconds` | Insert a key with a Time-To-Live (TTL) |
| `GET key` | Retrieve the value associated with a key |
| `DELETE key` | Remove a key |
| `EXISTS key` | Check whether a key exists |
| `KEYS` | Display all active keys |
| `COUNT` | Display the total number of active keys |
| `CLEAR` | Remove all stored data |
| `SAVE` | Persist the database to disk |
| `LOAD` | Restore the database from disk |
| `HELP` | Display available commands |
| `EXIT` | Close the application |

---

# Project Structure

```
MiniRedis
│
├── main.cpp
├── KeyValueStore.h
├── KeyValueStore.cpp
├── CommandParser.h
├── CommandParser.cpp
├── Persistence.h
├── Persistence.cpp
├── README.md
└── .gitignore
```
## 🚀 Getting Started

### Prerequisites

Before running the project, ensure you have:

* A C++17 compatible compiler (`g++`)
* Git (optional, for cloning the repository)

---

## Clone the Repository

```bash
git clone https://github.com/bhargavsairajsanke/MiniRedis.git
cd MiniRedis
```

---

## Build the Project

### Linux / WSL

```bash
g++ main.cpp KeyValueStore.cpp CommandParser.cpp Persistence.cpp -std=c++17 -o miniredis
```

### Windows (MinGW)

```bash
g++ main.cpp KeyValueStore.cpp CommandParser.cpp Persistence.cpp -std=c++17 -o miniredis.exe
```

---

## Run the Application

### Linux / WSL

```bash
./miniredis
```

### Windows

```powershell
.\miniredis.exe
```

---

## Sample Commands

```text
SET name Bhargav
GET name

SET college IITKGP
GET college

SET otp_user123 483921 EXPIRE 5
GET otp_user123

(wait 6 seconds)

GET otp_user123

SET name Sai NX

EXISTS name

COUNT

KEYS

SAVE

EXIT
```

---

## Expected Output

```text
OK
Bhargav

OK
IITKGP

OK
483921

Key not found

Key already exists.

true

2

name
college

Database saved successfully.
```

---

# Architecture

```
                User
                  │
                  ▼
        +------------------+
        | Command Parser   |
        +------------------+
                  │
                  ▼
        +------------------+
        | KeyValueStore    |
        +------------------+
          │            │
          │            ▼
          │      TTL Manager
          │
          ▼
   std::unordered_map
          │
          ▼
     Persistence
      (SAVE / LOAD)
```

---

# Time Complexity

| Operation | Complexity |
|-----------|------------|
| SET | O(1) Average |
| GET | O(1) Average |
| DELETE | O(1) Average |
| EXISTS | O(1) Average |
| COUNT | O(1) |
| KEYS | O(n) |
| SAVE | O(n) |
| LOAD | O(n) |

---

# Technologies Used

- C++17
- Object-Oriented Programming
- Standard Template Library (STL)
- `unordered_map`
- File Handling
- Command Line Interface
- Modular Software Design

---

# Real-World Applications

Although simplified, MiniRedis models several practical backend use cases commonly implemented using Redis.

### Session Management

```
SET session_user123 user42 EXPIRE 1800
```

Stores user sessions temporarily and automatically removes them after expiration.

---

### OTP Storage

```
SET otp_9876543210 483921 EXPIRE 60
```

Stores one-time passwords that expire automatically after a specified duration.

---

### API Rate Limiting

```
SET api_user42_count 57 EXPIRE 60
```

Tracks API usage within a fixed time window.

---

### Temporary Caching

```
SET homepage_products cached_data EXPIRE 300
```

Caches frequently requested data to reduce repeated database access.

---

## Advantages

- Fast in-memory access using hash-based storage
- Reduces repeated database queries
- Automatic cleanup of temporary data using TTL
- Modular and extensible design
- Demonstrates backend caching concepts

---

# Example

```
> SET name Bhargav
OK

> GET name
Bhargav

> SET otp_user123 483921 EXPIRE 5
OK

> GET otp_user123
483921

(wait 6 seconds)

> GET otp_user123
Key not found

> SET name Sai NX
Key already exists.

> SAVE
Database saved successfully.
```

---

# Future Improvements

- Network-based client-server architecture
- Authentication support
- Persistent TTL metadata
- Background expiration thread
- Additional Redis-inspired commands
- Memory usage statistics

---

# Learning Outcomes

This project strengthened my understanding of:

- Object-Oriented Programming in C++
- Hash-table based storage systems
- Efficient data structures
- File persistence
- Command parsing
- Backend caching concepts
- Modular software architecture

---

# Author

**Bhargav Sai Raj Sanke**

B.Tech Computer Science and Engineering  
Indian Institute of Technology Kharagpur
