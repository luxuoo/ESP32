# ESP32-S3 按键中断控制 LED

基于 [PlatformIO](https://platformio.org/) + Arduino 框架的 ESP32-S3 入门示例。通过板载 **BOOT 按键** 的硬件中断来切换板载 **LED** 的闪烁模式。

## 功能说明

- 使用硬件中断（`attachInterrupt`）监听 BOOT 按键的下降沿（按下）。
- 中断处理函数带 **50ms 消抖** 逻辑，避免按键抖动导致误触发。
- 每次按下切换一次模式：
  - **模式 A**：LED 以 500ms 间隔闪烁。
  - **模式 B**：LED 常灭。
- 中断处理函数标注 `IRAM_ATTR`，运行在高速内存中。

## 硬件与引脚

| 项目 | 说明 |
| --- | --- |
| 开发板 | ESP32-S3-DevKitC-1 |
| 框架 | Arduino |
| BOOT 按键 | GPIO 0（`INPUT_PULLUP`） |
| 板载 LED | GPIO 48（`OUTPUT`） |
| 串口波特率 | 115200 |

> 不同型号的 ESP32-S3 开发板板载 LED 引脚可能不同（常见为 GPIO 48 或 GPIO 38），如果 LED 无反应请根据自己的板子修改 `src/main.cpp` 中的引脚号。

## 目录结构

```
├── include/          # 头文件
├── lib/              # 私有库
├── src/
│   └── main.cpp      # 主程序
├── test/             # 单元测试
└── platformio.ini    # PlatformIO 工程配置
```

## 编译与烧录

安装 [PlatformIO](https://platformio.org/install)（VS Code 插件或 CLI）后：

```bash
# 编译
pio run

# 编译并烧录到开发板
pio run --target upload

# 打开串口监视器（波特率 115200）
pio device monitor -b 115200
```

## 使用方法

1. 烧录程序后，打开串口监视器会看到提示：`程序已启动，请按 BOOT 键切换闪烁模式`。
2. 按一下 BOOT 键，LED 开始闪烁；再按一下，LED 熄灭。
