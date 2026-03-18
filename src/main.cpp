#include <Arduino.h>

// --- 全局变量 ---
bool ledState = false;         // 记录灯是否应该闪烁
unsigned long lastTime = 0;    // 记录上一次按下的时间，用于消抖

// --- 中断处理函数 ---
// 使用 IRAM_ATTR 确保函数运行在高速内存中
void IRAM_ATTR handleButton() {
    unsigned long now = millis();
    // 消抖逻辑：如果距离上次触发超过 50 毫秒，才认为是一次真实的按下
    if (now - lastTime > 50) {
        ledState = !ledState;  // 翻转模式
        lastTime = now;        // 更新时间
    }
}

void setup() {
    Serial.begin(115200);

    // 配置引脚模式
    pinMode(0, INPUT_PULLUP);         // BOOT 按键引脚
    pinMode(48, OUTPUT);       // 板载 LED 引脚

    // 绑定硬件中断
    // 当 0 号引脚出现下降沿（FALLING，即按下）时，执行 handleButton
    attachInterrupt(digitalPinToInterrupt(0), handleButton, FALLING);

    Serial.println("程序已启动，请按 BOOT 键切换闪烁模式");
}

void loop() {
    // 根据中断修改的 ledState 决定行为
    if (ledState == true) {
        // 模式 A：闪烁（跑马灯逻辑）
        digitalWrite(48, HIGH);
        delay(500);
        digitalWrite(48, LOW);
        delay(500);
    } else {
        // 模式 B：常灭
        digitalWrite(48, LOW);
    }
}