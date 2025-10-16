#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>

// Define the LCD pins and size
const int LCD_COLS = 16;
const int LCD_ROWS = 2;

// Define the PCF8574T backpack address
const int LCD_ADDRESS = 0x27;  // Try 0x3F if this doesn't work

hd44780_I2Cexp lcd(LCD_ADDRESS, LCD_COLS, LCD_ROWS);

// Variables for scrolling
String scrollText = "Beste {Naam student}, van harte gefeliciteerd met je diploma! Groeten van de opleiding ICT";
int stringLength = 0;
int position = 0;

int amount_icons = 15;

uint8_t happy[8] = {
    // happy face
    0b00000, 0b10001, 0b00000, 0b00000, 0b10001, 0b01110, 0b00000, 0b00000,
};

uint8_t wow[8] = {
    // wow face
    0b00000, 0b10001, 0b00000, 0b01110, 0b10001, 0b01110, 0b00000, 0b00000,
};

uint8_t anchor[8] = {
    // anchor bit array
    0b01110, 0b01010, 0b01110, 0b00100, 0b10101, 0b10101, 0b01110, 0b00100};

uint8_t snow[8] = {
    // snow bit array
    0b01000, 0b11101, 0b01011, 0b00001, 0b00100, 0b01110, 0b00100, 0b10000};

uint8_t heart[8] = {
  B00000,
  B01010,
  B11111,
  B11111,
  B01110,
  B00100,
  B00000,
  B00000
};

uint8_t bell[8] = {
  B00100,
  B01110,
  B01110,
  B01110,
  B11111,
  B00000,
  B00100,
  B00000
};

uint8_t sand[] = {0x1f, 0x11, 0x0e, 0x04, 0x04, 0x0a, 0x11, 0x1f};
uint8_t music[] = {0x00, 0x00, 0x0f, 0x09, 0x09, 0x09, 0x1b, 0x1b};
uint8_t plant[] = {0x1b, 0x15, 0x0e, 0x04, 0x04, 0x0a, 0x11, 0x1f};
uint8_t house[] = {0x04, 0x0e, 0x1f, 0x1f, 0x11, 0x15, 0x15, 0x1f};
uint8_t lightning[] = {0x01, 0x02, 0x04, 0x08, 0x1f, 0x02, 0x04, 0x08};
uint8_t tower[] = {0x00, 0x00, 0x00, 0x04, 0x00, 0x0e, 0x00, 0x1f};
uint8_t cow[] = {0x00, 0x11, 0x00, 0x1f, 0x15, 0x1f, 0x00, 0x00};
uint8_t creep[] = {0x1b, 0x1b, 0x0e, 0x11, 0x11, 0x11, 0x15, 0x0e};
uint8_t spaceship[] = {0x03, 0x06, 0x09, 0x13, 0x09, 0x06, 0x03, 0x00};


int iters = 0;


void setup() {
  stringLength = scrollText.length();
  Serial.begin(115200);
  Serial.println("Starting LCD Debug Test");
  
  // Initialize I2C with your custom pins
  Wire.begin(19, 22);
  
  // Test I2C communication
  Serial.println("Testing I2C communication...");
  byte error;
  Wire.beginTransmission(LCD_ADDRESS);
  error = Wire.endTransmission();
  
  if (error == 0) {
    Serial.println("I2C device found at address 0x27");
  } else {
    Serial.print("I2C error: ");
    Serial.println(error);
    Serial.println("Try these addresses: 0x3F, 0x20");
    while(1);  // Stop here if I2C communication fails
  }
  
  // Initialize the LCD
  Serial.println("Initializing LCD...");
  lcd.init();
  
  // Test basic LCD functionality
  lcd.home();  // Move cursor to home position
  lcd.createChar(0, happy);
  lcd.createChar(1, wow);
  lcd.createChar(2, anchor);
  lcd.createChar(3, snow);
  lcd.createChar(4, bell);
  lcd.createChar(5, heart);
  lcd.createChar(6, sand);
  lcd.createChar(7, music);
  lcd.createChar(8, plant);
  lcd.createChar(9, house);
  lcd.createChar(10, lightning);
  lcd.createChar(11, cow);
  lcd.createChar(12, tower);
  lcd.createChar(13, creep);
  lcd.createChar(14, spaceship);

  lcd.print("Test");  // Try printing a simple message
  
}

void loop() {
  // Clear both lines
  lcd.setCursor(0, 0); // Top line
  lcd.print("                ");

  int c;
  if (iters == 5) {
  lcd.setCursor(2, 1); // Bottom line
  c = random(amount_icons);
  lcd.write(c);
  lcd.setCursor(6, 1);
  c = random(amount_icons);
  lcd.write(c);
  lcd.setCursor(10, 1);
  c = random(amount_icons);
  lcd.write(c);
  lcd.setCursor(14, 1);
  c = random(amount_icons);
  lcd.write(c);
  iters = 0;
  }

  iters++;

  // Display scrolling text
  lcd.setCursor(0, 0);
  lcd.print(scrollText.substring(position, position+16));
  
  // Move text one character to the left
  position++;
  
  // Reset position if we've scrolled past the end
  if (position > stringLength + 5) {
    position = 0;
  }
  if (position == 0) {
    delay(2000);
  }

  delay(300); // Adjust scrolling speed
}
