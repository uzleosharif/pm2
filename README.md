# Password Manager
A console based password-management system intended for Linux devices.

## Pre-requisites
- Install uz::crypto library (in `/usr/local/*`).
- Needs `g++-14` compiler and `cmake-3.22` for building the app.

## Build
```
$ git clone <repo link>
$ cmake -B Release -S . -DCMAKE_BUILD_TYPE=Release
$ cmake --build Release
```

## Run
```
$ Release/pm
```
