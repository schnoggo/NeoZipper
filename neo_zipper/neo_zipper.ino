/**
 * Animated zipper pull code for the Adafruit neoPixels
 * @package neozipper
 * @author Lon Koenig <lon@lonk.me>
 * @license https://opensource.org/licenses/MIT
 */
#include <Adafruit_NeoPixel.h>
#include "neo_zipper.h"
// ---------------- set up NeoPixels ---------------
// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)

//Adafruit_NeoPixel pixels = Adafruit_NeoPixel(32, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800 );
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(MAX_PIXELS , NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

#define ANIM_DURATION 10000 // 8 seconds on each effect

// Global reusable variables so we don't allocate inside functions and loops
long rgb[3]; // generic RGB values - long so we can calculate and scale
uint8_t  i; // generic index
uint32_t this_color = 0; // temporary color "register" so we can reuse the RAM
uint8_t  ring_pos = 8; // position on the ring (usually just one eye)

uint8_t  mode   = 0, // Current animation effect
// "left" is closest to cpu
         leftOff = 7, // Position of spinny eyes
         rightOff = 2;
boolean auto_advance =  true;
uint8_t animation_pool[] {
  TEST_ROW_ANIM,
  CENTER_OUT_ANIM,
  SPARKS_ANIM,
 //BARBER_POLE_ANIM,
// FLASH_ANIM,
 //LARSON_SCANNER_ANIM,
// SOLID_ANIM,
// ARROW_LEFT_ANIM,
 //ARROW_RIGHT_ANIM,


};
// Color and animation stuff:
uint8_t current_animation = SPARKS_ANIM;
uint32_t animation_frame = 0;
uint32_t animation_color  = 0xFF0000; // Start red
uint32_t palette[2][FADE_LENGTH + 1]; // array of color for animations (fades)

boolean pixels_dirty =  true;
uint8_t color_wheel_position = 0;

uint8_t panel_coords2pixel[] {
  0,1,2,3,4,
  9,8,7,6,5,
  10,11,12,13,14,
  19,18,17,16,15
};

#ifdef BUTTON_PIN
// momentary switch:
uint8_t seen_button_up = 1; //1:button has been up, 0 waiting for up
uint8_t hardware_button_state = 0;
uint8_t prev_button_state = 0xFF;
boolean button_seen_up = false;
unsigned long button_state_start_time = 0;
#endif
#define bounce_window 12 //  milliseconds to count as stable


#define BUTTON_BOUNCE_TIME 30
uint32_t last_button_change = 0;
boolean current_button_state = false;

// vibration sensor shake trigger:
boolean shaking = false;
boolean new_shake = false;
uint32_t shaking_latch_release = 0;
#define SHAKING_LATCH_DURATION 1500

uint32_t rez_range = 256*3;
uint8_t testpos = 0;
uint32_t nextModeChange = 0;
int32_t hires_pos = 0, // 256x actual pos so we can fake floats
  inertia = 0,
  moment =0,
  spring_force = 0;


#define system_size 8*256
#define scale2pixel 256
#define friction  230 // 90% of 256 = 10% drag
#define spring_constant 92 // 36% of 256
#define denom 256 // binary fraction time!
#

void setup() {
  SetHWPins(); // set pin modes (needed for trinket)
#ifdef PRDBG
	Serial.begin(9600);
#endif
  //delay(200);
  dprintln("START");
  // set up neopixel ring:
  pixels.begin();
  pixels.setBrightness(200); // was 80


}

void loop() {
  unsigned long now = millis();

  if((now > nextModeChange) ) {      // Every 8 seconds... change modes
    mode++;                        // Next mode
    if(mode >= sizeof( animation_pool)) { mode = 0;} // End of available animations?
    if (auto_advance) {
      NextColor(); // advence to next color in wheel
    }
    nextModeChange = now + ANIM_DURATION;
    dprint("new mode: ");
    dprintln(mode);
    StartAnimation(animation_pool[mode]);
  }
    UpdateAnimation();
}

// Replace regular delay() with something that can run background process
void BackgroundDelay(unsigned long delay_milliseconds){
    unsigned long now = millis();
    while ((now + delay_milliseconds) > millis()){
      UpdateButtonState(); // updates all inputs
      /*
      if (GetShakeState()) {
        nextModeChange = now + ANIM_DURATION;
        StartAnimation(GOOGLY_ANIM);
      //  break;
      }
*/
      if (GetButtonState()){
        /*
        SolidPanel(0x2222FF, true);
        delay(130);
        SolidPanel(0, true);
        */
       auto_advance = false; // if use sets color, lock it in
        NextColor();
        StartAnimation(animation_pool[mode]);

      //  nextModeChange = now; // immediately jump to next mode
      //  break;
      }
    }
}
