# autodrive_examples_cpp

Metacar C++ API 示例程序。通过 CMake FetchContent 自动拉取 [autodrive_api_cpp](https://github.com/YDL-Simulation/autodrive_api_cpp) 库，无需手动下载依赖。

## 前置要求

- CMake 3.14+
- 支持 C++20 的编译器（MSVC 2019+、GCC 10+、Clang 12+）

## 构建

```bash
cmake -B build
cmake --build build
```

构建完成后可执行文件位于 `build/example_basic/` 目录。

## 示例说明

### example_basic

最小示例：连接仿真器 → 逐帧接收数据 → 发送油门控制指令。运行前请先启动 Metacar 仿真器。
