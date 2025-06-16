/*
 * NewsLens - Arduino 控制程式
 * 
 * 功能：接收 Web Serial API 傳來的偏誤程度評估結果，依據不同層級控制 LED 燈
 * 
 * 命令格式：
 * - "HIGH1\n" - 紅燈閃爍 3 次（偏誤程度高）
 * - "HIGH2\n" - 紅燈常亮（偏誤程度中）
 * - "LOW\n" - 燈熄滅（偏誤程度低）
 */

// 定義 LED 腳位
const int LED_PIN = 13;  // 預設 LED 接在 D13

void setup() {
  // 初始化 Serial 通訊
  Serial.begin(9600);
  
  // 設定 LED 腳位為輸出模式
  pinMode(LED_PIN, OUTPUT);
  
  // 初始狀態：LED 熄滅
  digitalWrite(LED_PIN, LOW);
  
  // 啟動指示：閃爍兩次表示程式已啟動
  for (int i = 0; i < 2; i++) {
    digitalWrite(LED_PIN, HIGH);
    delay(100);
    digitalWrite(LED_PIN, LOW);
    delay(100);
  }
}

void loop() {
  // 檢查是否有新的 Serial 資料
  if (Serial.available() > 0) {
    // 讀取一行指令
    String command = Serial.readStringUntil('\n');
    command.trim();  // 移除空白字元
    
    // 依據不同指令控制 LED
    if (command == "HIGH1") {
      // 高偏誤：紅燈閃爍 3 次
      for (int i = 0; i < 3; i++) {
        digitalWrite(LED_PIN, HIGH);
        delay(300);
        digitalWrite(LED_PIN, LOW);
        delay(300);
      }
      
      // 確認已執行指令
      Serial.println("HIGH1 executed");
    } 
    else if (command == "HIGH2") {
      // 中偏誤：紅燈常亮
      digitalWrite(LED_PIN, HIGH);
      
      // 確認已執行指令
      Serial.println("HIGH2 executed");
    } 
    else if (command == "LOW") {
      // 低偏誤：燈熄滅
      digitalWrite(LED_PIN, LOW);
      
      // 確認已執行指令
      Serial.println("LOW executed");
    }
    else {
      // 不明指令
      Serial.println("Unknown command: " + command);
    }
  }
  
  // 短暫延遲以減少 CPU 負載
  delay(10);
}