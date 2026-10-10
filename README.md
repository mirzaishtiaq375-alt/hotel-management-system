# Hotel Management System

A simple hotel management system website with a C++ backend and an admin portal.

## Default admin login

- Username: admin
- Password: admin123

## Features

- Admin login portal
- Dashboard overview with occupancy and revenue summary
- Room availability management
- Guest booking overview
- Responsive web interface

## Run the app

### Option 1: Using g++

```bash
g++ -std=c++17 -O2 -Wall -Wextra -pedantic src/main.cpp -o hotel_server
./hotel_server
```

Then open:

- http://localhost:8080

### Option 2: Using CMake

```bash
cmake -S . -B build
cmake --build build
./build/hotel_server
```

## Project structure

- `src/main.cpp` — C++ HTTP server and API logic
- `static/index.html` — login page and dashboard UI
- `static/styles.css` — styling
- `static/app.js` — frontend logic

## Notes

This is a lightweight demo project designed to run locally as a hotel management system website. It uses a custom C++ HTTP server so there are no external dependencies.
