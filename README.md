# bitdog-patroLibs

A collection of modular and reusable C libraries for Raspberry Pi Pico (RP2040) projects, developed for use with BitDogLab systems.

## 📦 Overview

This repository contains multiple standalone libraries organized into folders. Each library provides specific functionality such as button handling, analog input, PWM control, and more.

All libraries are written in C and designed to be easily integrated into CMake-based projects using `FetchContent`.

## 🛠️ How to Use

You can integrate this repository into your project using CMake's `FetchContent` module:

```cmake
include(FetchContent)

FetchContent_Declare(
  bitdoglibs
  GIT_REPOSITORY https://github.com/luisfpatrocinio/bitdog-patroLibs.git
  GIT_TAG main
)

FetchContent_MakeAvailable(bitdoglibs)

target_link_libraries(your_project
  PRIVATE
    bitdog::patrolibs
)
```

## 📄 License

This project is licensed under the MIT License.  
Feel free to use it in your projects -- just make sure to credit **Luis Felipe Patrocinio**.  
See the [LICENSE](./LICENSE) file for full details.
