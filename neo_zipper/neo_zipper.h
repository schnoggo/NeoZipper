/**
 * Constants and macros for the neoGoggles projects
 * @package neogoggles
 * @author Lon Koenig <lon@lonk.me>
 * @license https://opensource.org/licenses/MIT
 */

// code compile-time options:

// if true, compile in the flame effect:
#define USE_FLAME false

// How far to step around the color wheel when we change colors:
#define COLOR_WHEEL_STEP 16

// Describe the hardware:
// height is how many pixels in a strip
// width is how many strips
// we assume strips are connecter zip-zag (snake) style
#define PANEL_HEIGHT 5
#define PANEL_WIDTH 3
#define MAX_PIXELS PANEL_HEIGHT*PANEL_WIDTH
// Data pin for NeoPixels:
#define NEOPIXEL_PIN 0



// Input pins vibration sensor
#define VIBRATION_PIN 1


//

// NeoPixel Ring Animations:
#define SPARKS_ANIM 0
#define BARBER_POLE_ANIM 1
#define FLASH_ANIM 2
#define LARSON_SCANNER_ANIM 3
#define SOLID_ANIM 4
#define ARROW_LEFT_ANIM 5
#define ARROW_RIGHT_ANIM 6
#define CENTER_OUT_ANIM 7


// other animation Constants:
#define FADE_LENGTH 5

// #define PRDBG
// macros:
// create Serial.print macros:
#ifdef PRDBG
#define dprint(ccc) Serial.print(ccc);
#define dprintln(ccc) Serial.println(ccc);
#else
#define dprint(ccc) ""
#define dprintln(ccc) ""
#endif
