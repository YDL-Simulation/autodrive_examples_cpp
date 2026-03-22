# autodrive_examples_cpp

MetaCar C++ API 项目模板。通过 CMake FetchContent 自动拉取 [autodrive_api_cpp](https://github.com/YDL-Simulation/autodrive_api_cpp) 库，无需手动下载任何依赖。

## 前置要求

- CMake 3.14+
- 支持 C++20 的编译器（MSVC 2019+、GCC 10+、Clang 12+）

## 快速开始

```bash
git clone https://github.com/YDL-Simulation/autodrive_examples_cpp.git
cd autodrive_examples_cpp
cmake -B build
cmake --build build
```

> **Windows 用户**：请在 Visual Studio Developer Terminal 中执行以上命令，确保 `cl.exe` 在 PATH 中。

构建完成后，可执行文件位于 `build/src/` 目录。运行前请先启动仿真器。

## 项目结构

```
autodrive_examples_cpp/
  CMakeLists.txt      ← 顶层配置，自动拉取 metacar 库
  src/
    CMakeLists.txt    ← 构建配置
    main.cpp          ← 在这里编写你的代码
```

## 文档

完整的 API 文档请参阅 [MetaCar C++ API 文档](https://github.com/YDL-Simulation/autodrive_api_cpp)。
