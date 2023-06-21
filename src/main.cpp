#include <Arduino.h>
#include "FT62XXTouchScreen.h"
#include "TFT_eSPI.h"
#include "Calibri12.h"
#include "Calibri13.h"
#include "Calibri16.h"

TFT_eSPI tft = TFT_eSPI();
FT62XXTouchScreen touchScreen = FT62XXTouchScreen(320, PIN_SDA, PIN_SCL);

bool ScreenIsPoweredDown;

#if ORIENTATION==1  // Landscape
#define WIDTH   TFT_HEIGHT
#define HEIGHT  TFT_WIDTH
#else
#define WIDTH   TFT_WIDTH
#define HEIGHT  TFT_HEIGHT
#endif
#define SMALL_FONT &Calibri12
#define MEDIUM_FONT &Calibri13
#define LARGE_FONT &Calibri16


/**
 * Draw text with optional formatting
 */
void DrawXY(int x, int y, const char *s, ...) {
    va_list args;
    va_start(args, s);
    char buf[80];
    vsnprintf(buf, 80, s, args);
    tft.drawString(buf, x, y, 1);
    va_end(args);
}

/**
 * Power down screen
 * This function is missing in TFT_eSPI, so we write directly
 * to the R61529 command port
 */
void ScreenPowerDown() {
    if (!ScreenIsPoweredDown) {
        ledcWrite(1, 0);
        ScreenIsPoweredDown = true;
        tft.begin_nin_write();
        tft.writecommand(0x10); // This is the TFT_SLPIN command
        tft.end_nin_write();
    }
}

/**
 * Main loop
 */
void loop() {
    int x,y;
    TouchPoint touchPos = touchScreen.read();
#if ORIENTATION==0
    y = touchPos.xPos;
    x = WIDTH - touchPos.yPos;
#else
    x = touchPos.xPos;
    y = touchPos.yPos;
#endif
    if ((x!=0)&&(y!=0)) {
        tft.fillRect(x-5, y-5, 10, 10, TFT_RED);
    }
    delay(10);
}

/*
 * Main initialization code
 */
void setup() {
    // Set the power on pin high as soon as possible
    pinMode(PIN_PWRON, OUTPUT);
    digitalWrite(PIN_PWRON, 1);

    // Initialize serial port
    Serial.begin(115200);

    touchScreen.begin();

    tft.init();
    // Set landscape mode. Use 0 for portrait mode.
    tft.setRotation(ORIENTATION);
    // Clear the screen to all black
    tft.fillScreen(TFT_BLACK);

    // Setup pwm for back-light of lcd panel
    pinMode(LCD_PWM_PIN, OUTPUT);
    digitalWrite(LCD_PWM_PIN, 1);
    ledcAttachPin(LCD_PWM_PIN, 1);
    ledcSetup(1, 1000, 8);
    ledcWrite(1, 255);

    tft.setFreeFont(LARGE_FONT);
    tft.setTextDatum(MC_DATUM);
    tft.setTextColor(TFT_YELLOW, TFT_YELLOW);
    DrawXY(WIDTH / 2, HEIGHT / 3, "Test touch");
    tft.setFreeFont(SMALL_FONT);
    DrawXY(WIDTH / 2, HEIGHT / 2, "Touch the screen!");

}

