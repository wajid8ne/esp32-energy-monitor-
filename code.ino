#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED display size
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// Create display object
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Simulated values
float currentReading = 0.0;
float voltage = 230.0; // Fixed voltage for simulation

void setup() {
  // Start serial monitor
  Serial.begin(115200);

  // Initialize the OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("Couldn't find OLED display");
    while (true); // Stop here if display isn't found
  }

  // Clear the screen and set text settings
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
}

void loop() {
  // Simulate current sensor: random value between 1.00A and 2.00A
  currentReading = random(100, 200) / 100.0;

  // Calculate power (P = V × I)
  float power = voltage * currentReading;

  // Show data on OLED
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("🔌 ESP32 Energy Monitor");
  display.print("Current: ");
  display.print(currentReading, 2);
  display.println(" A");
  display.print("Power:   ");
  display.print(power, 2);
  display.println(" W");
  display.display();

  // Also print to Serial Monitor for debugging
  Serial.print("Current: ");
  Serial.print(currentReading);
  Serial.print(" A | Power: ");
  Serial.print(power);
  Serial.println(" W");

  // Wait 1 second before next reading
  delay(1000);
}
