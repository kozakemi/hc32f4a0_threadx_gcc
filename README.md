# HC32F4A0 ThreadX GCC 项目

## 项目简介

本项目是基于华大半导体 HC32F4A0 系列微控制器的 ThreadX RTOS 开发模板，使用 GCC 工具链进行编译。项目集成了多个开源组件，为嵌入式开发提供了完整的实时操作系统解决方案。

建议使用vscode打开本项目，借助cortex-debug插件进行调试,可参照.vscode\settings.json 与 .vscode\launch.json

## 主要特性

- **微控制器**: HC32F4A0 系列 (ARM Cortex-M4 内核)
- **实时操作系统**: Eclipse ThreadX RTOS
- **编译工具链**: GCC ARM None EABI
- **构建系统**: CMake make/ninja
- **调试工具**: SEGGER RTT + SystemView
- **命令行交互**: nr_micro_shell

## 项目结构

```
├── drivers/                 # 驱动程序
│   ├── bsp/                # 板级支持包
│   ├── cmsis/              # CMSIS 标准接口
│   ├── hc32_ll_driver/     # HC32F4A0 底层驱动
│   ├── mcu/                # MCU 相关配置
│   └── linker/             # 链接脚本
├── middlewares/            # 中间件
│   └── threadx-6.4.2_rel-segger/  # ThreadX RTOS
├── src/                    # 源代码
│   ├── main.c              # 主程序
│   ├── module/             # 功能模块
│   │   ├── nr_micro_shell/ # 命令行交互模块
│   │   └── segger_rtt/     # RTT 调试模块
│   └── tx_initialize_low_level.S  # ThreadX 底层初始化
├── tools/                  # 开发工具
│   ├── SEGGER_RTT_V798d/   # RTT 工具
│   ├── SystemView_Src_V360e/ # SystemView 源码
│   └── nr_micro_shell-1.0.2/ # 命令行工具
└── CMakeLists.txt          # CMake 构建配置
```

## 组件来源

本项目基于以下开源项目构建，特此声明各组件的来源：

### 1. 项目模板
- **来源**: [https://github.com/nczyw/hc32f4a0-template](https://github.com/nczyw/hc32f4a0-template)
- **说明**: HC32F4A0 系列 CMake 工程模板，提供了基础的项目结构和驱动程序

### 2. ThreadX RTOS
- **来源**: [https://github.com/SEGGERMicro/threadx](https://github.com/SEGGERMicro/threadx)
- **版本**: 6.4.2 (SEGGER 版本)
- **说明**: Eclipse ThreadX 实时操作系统，集成了 SEGGER SystemView 支持

### 3. SEGGER SystemView
- **来源**: [https://github.com/SEGGERMicro/SystemView](https://github.com/SEGGERMicro/SystemView)
- **版本**: V3.60e
- **说明**: SEGGER SystemView 实时系统分析和可视化工具

### 4. SEGGER RTT
- **来源**: [https://github.com/SEGGERMicro/RTT](https://github.com/SEGGERMicro/RTT)
- **版本**: V7.98d
- **说明**: SEGGER Real Time Transfer 实时数据传输技术

### 5. nr_micro_shell
- **来源**: [https://github.com/Nrusher/nr_micro_shell](https://github.com/Nrusher/nr_micro_shell)
- **版本**: 1.0.2
- **说明**: 轻量级单片机命令行交互工具

## 开发环境要求

### 必需工具
Linux：
- **CMake**: 3.15 或更高版本
- **GCC ARM None EABI**: 推荐使用最新版本
- **Make**: 构建工具
- **OpenOCD** 或 **pyOCD**: 用于程序下载和调试

Windows：
- **CMake**: 3.15 或更高版本
- **GCC ARM None EABI**: 推荐使用最新版本
- **Make**: 构建工具
- **OpenOCD** 或 **pyOCD**: 用于程序下载和调试
- **MinGW**: 提供 Windows 下的 GNU 工具链

### 推荐工具
- **Visual Studio Code**: 配合 C/C++ 扩展
- **SEGGER J-Link**: 硬件调试器
- **SEGGER RTT**: 日志&终端
- **SEGGER SystemView**: 系统分析工具

## 快速开始

使用vscode执行生成任务或者参照tasks.json文件

## 许可证

本项目遵循各组件的原始许可证：
- ThreadX: MIT License
- SEGGER RTT/SystemView: SEGGER License
- nr_micro_shell: MIT License
- HC32F4A0 驱动: 华大半导体许可证


## 联系方式

如有问题或建议，请通过 GitHub Issues 联系。

---

**注意**: 使用本项目前，请确保已获得相应硬件和软件的合法使用权限。