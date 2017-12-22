/**
 * Functions to animate the neoPixel LED strips/rings
 * @package neozipper
 * @author Lon Koenig <lon@lonk.me>
 * @license https://opensource.org/licenses/MIT
 */

/**
 * Begin an animation by calling StartAnimation()
 * Update display by calling UpdateAnimation()
 *
 * Animation IDs are defined in neo_goggles.h
 *
 * @param uint8_t which_animation ID of the animation
 */
void StartAnimation(uint8_t which_animation){
  // globals:
  // animation_frame
  // current_animation
  // pixels_dirty
  current_animation = which_animation;
  animation_frame = 0;
  pixels_dirty = true;
  dprint("StartAnimation:")
  dprintln(which_animation);

  switch (which_animation){
    case SPARKS_ANIM:
    case CENTER_OUT_ANIM:
      ClearPanel(false);
    break;

    case SOLID_ANIM:

    SolidPanel(FadedColor(0,0), true);
  }
  if (SOLID_ANIM == which_animation){


  }
}

/**
 * Background update function to draw
 * next frame of current animation
 */
void UpdateAnimation(){
// globals
// current_animation
// animation_frame
// animation_color

uint16_t frame_duration = 200;
uint8_t delta = 0;
switch(current_animation) {




 case SPARKS_ANIM: // Random sparks - just one LED on at a time
 // ======================================================
  i = random(MAX_PIXELS);

  pixels.setPixelColor(i, pixels.Color(RandomSteppedColor(), RandomSteppedColor(), RandomSteppedColor() ));
  pixels.show();
  BackgroundDelay(10);
  pixels.setPixelColor(i, 0);
  frame_duration = 5;
  pixels_dirty =  true;
  break;


case CENTER_OUT_ANIM:
  ClearPanel(false);
  dprintln(animation_frame);

  if ( 5 == animation_frame){
    frame_duration = 2000;
  } else {
    frame_duration = 100;
    switch (animation_frame){
      case 0:
        DrawPanelRow(2,0,0);
      break;

      case 1:
        DrawPanelRow(2,0,1);
        DrawPanelRow(1,0,0);
        DrawPanelRow(3,0,0);
      break;

      case 2:
        DrawPanelRow(2,0,2);
        DrawPanelRow(1,0,1);
        DrawPanelRow(3,0,1);
        DrawPanelRow(0,0,0);
        DrawPanelRow(4,0,0);
      break;

      case 3:
        DrawPanelRow(1,0,2);
        DrawPanelRow(3,0,2);
        DrawPanelRow(0,0,1);
        DrawPanelRow(4,0,1);
      break;

      case 4:
        DrawPanelRow(0,0,2);
        DrawPanelRow(4,0,2);
      break;
    } // switch animation_frame
  } // if last frame
  if ((++animation_frame)>4) {
    animation_frame = 0;
  }
  pixels_dirty =  true;

break;

case TEST_ROW_ANIM:


  ClearPanel(false);
  uint8_t current_row = animation_frame; // 0 - 9
  if (current_row >= PANEL_HEIGHT){
    current_row = (PANEL_HEIGHT*2-2)-current_row;
  }
  DrawPanelRow(current_row,0,0);

  frame_duration = 40;
  if ((++animation_frame)>(PANEL_HEIGHT*2-2)) {animation_frame = 0;}
      pixels_dirty =  true;
break;

/*
  case FLASH_ANIM:
  // blinky
    this_color = animation_color;
    if (1 == animation_frame){ this_color = 0; }

      for(i=0; i<16; i++) { //count around the ring of pixels
        pixels.setPixelColor( i, this_color); // First eye
        pixels.setPixelColor(16 + i  , this_color); //
      }

    if ((++animation_frame)>1) {animation_frame = 0;}
    frame_duration = 1000;
    pixels_dirty =  true;
  break;

*/

/*
  case GOOGLY_ANIM:
 // googly
 // ======================================================

  inertia = ((inertia -  (hires_pos /3 )) * friction) /denom;
 // inertia = moment;
  hires_pos = hires_pos + inertia;
  if (hires_pos >= system_size){
    // FlashRing();
    hires_pos = -(hires_pos - system_size);
    inertia = -inertia;
  } else if (hires_pos < (-system_size)) {
   //  FlashRing();
    hires_pos = system_size + hires_pos;
    inertia = -inertia;
  }
  // + 8  to rotate 0 to bottom
 ring_pos = NormalizeRingPos(8+ (hires_pos / scale2pixel));

  ClearPanel(false);
  for(i=0; i<RING_SIZE; i++) {
    this_color = 0;
    delta = RingDistance(ring_pos, i);
    if(delta <2 ){
      //  pixels.setPixelColor(    NormalizeRingPos(i+leftOff )  , this_color); // First eye
      //  pixels.setPixelColor( 16 +NormalizeRingPos(i+rightOff) , this_color); // Second eye (not flipped)
    // replace ^
        DrawRingPixel(i  , 1 + delta * 2 , false, 1, false);
    }
  }
  frame_duration = 24;
  pixels_dirty =  true;

  // if inertia settles to low level goose it. --todo
  // randomly add an impulse:
  if (random(60) == 1){
   inertia = inertia + random(800);

  }


  break;

*/

/*
    case LARSON_SCANNER_ANIM: // larson scanner:
// ======================================================
// actually, just a spinner in this version
    for(i=0; i<16; i++) {
    this_color = 0; // turn off non-selected pixels
    if(testpos == i) {this_color = 0xFFFF00;} // 4 pixels on...
    pixels.setPixelColor(  NormalizeRingPos(i+leftOff), this_color); // First eye
    pixels.setPixelColor(16 + NormalizeRingPos(i+rightOff)  , this_color); // Second eye (flipped)
  }
  testpos++;
  if (testpos>15){testpos=0;}
  BackgroundDelay(60);
  pixels.show();

  break;
*/


//  SolidPanel(FadedColor(0, 3), false);


//  DrawRingPixel(animation_frame  , 1 , true, 8, false);
  /*
  * @param uint8_t position which pixel to light up
  * @param palette_index index of this color in the palette
  * @param boolean reflection true = mirror to other eye. False copy to other eye
  * @param multiple how many times to draw (recommended values: 1, 2, 4, 8)
  * @param boolean true = alternat color with secondary palette
  * */
/*
  for(i=0; i<MAX_PIXELS; i=i+1){ // light every other pixel
      if ((i%2) == (byte) animation_frame ){
    pixels.setPixelColor(i, animation_color);

  } else {
    pixels.setPixelColor(i, pixels.Color(0,40,0));

  }
  */
 /*
  if (++animation_frame > 1){ animation_frame = 0;}
  pixels_dirty = true;

  break;
*/

} // end the big switch
  BackgroundDelay(frame_duration);
  //BackgroundDelay
  if (pixels_dirty){
    pixels.show();
    pixels_dirty = false;
  }

}



/**
 * Light an LED at specified location
 *
 * @param uint8_t x position which pixel to light up
 * @param uint8_t y position which pixel to light up
 * @param which palette (0 or 1)
 * @param palette_index index of this color in the palette
 * @param boolean true = alternat color with secondary palette
 */

void DrawPanelPixel(
  uint8_t x,
  uint8_t y,
  uint8_t palette_select,
  uint8_t palette_index
//  uint8_t fade_amount
//  boolean alternate
){


  //  this_color = FadedColor((clone_count%2), palette_index); // gives us our 32-bit color
  this_color = FadedColor(palette_select, palette_index); // gives us our 32-bit color
  while(x>=PANEL_WIDTH){x = x - PANEL_WIDTH;}
  while(y>=PANEL_HEIGHT){y = y - PANEL_HEIGHT;}

  pixels.setPixelColor(  panel_coords2pixel[x*PANEL_HEIGHT + y] , this_color);

}


/**
 * Light horizontal row
 *
 * @param uint8_t y position which pixel to light up
 * @param which palette (0 or 1)
 * @param palette_index index of this color in the palette
 */
void DrawPanelRow(
  uint8_t y,
  uint8_t palette_select,
  uint8_t palette_index
){
  uint8_t horiz = 0;
  for(horiz=0; horiz<PANEL_WIDTH; horiz++){
    DrawPanelPixel(horiz,y,palette_select,palette_index);
  }
}



/**
 * Turn all LEDs off
 * @param boolean show true = display immediately. false = don't call show()
 */
void ClearPanel(boolean show){
    SolidPanel(0, show);
}

/**
 * Turn all the LEDs same color
 * @param uint32_t c packed 32-bit color for neoPixel library
 * @param boolean show true = display immediately. false = don't call show()
 */
void SolidPanel(uint32_t c, boolean show){
    int pixel_offset;
    for(pixel_offset=0; pixel_offset<MAX_PIXELS; pixel_offset++){
      pixels.setPixelColor(pixel_offset, c);
    }
    if (show){
      pixels.show();
    }
}

/**
 * Specify the animation color (in terms of color wheel index)
 * @param uint8_t new_color color wheen index (8 bit)
 */
void SetAnimationColor(uint8_t new_color){
// globals:
// animation_color

  dprint("SetAnimationColor: ");
  dprintln(new_color);
  animation_color =  NeoWheel(new_color);
  animation_color = new_color; // set the global single color
  CreateFadeValues(new_color); // set faded colors table

}
void NextColor(){
  // globals:
  // color_wheel_position
  color_wheel_position += COLOR_WHEEL_STEP;
  SetAnimationColor(color_wheel_position);
}



uint8_t ReflectVertical(uint8_t pos1){
}

 uint8_t RandomSteppedColor(){
   // return a non-continuous value for a color axis
   return random(4)*64;
 }

 /**
  * @param palette numer (0 primary, 1, secondary)
  * @param uint8_t offset into color table
  *
  * @return uint8_t color wheel index
  */
 uint32_t FadedColor(uint8_t  which_palette, uint8_t fade_amount){
   // globals:
   //palette -- array of colors
   return palette[which_palette][fade_amount];
 }

/**
 * initialize the color palette for fade effects
 * @param uint8_t wheel_index color wheel index of starting color
 */
 void CreateFadeValues(uint8_t wheel_index){
  // globals:
  //palette -- array of colors
  uint32_t calc_color;
  uint8_t rgb[3];
  uint8_t channel;
  int channel_value;
  uint8_t palette_index = 0;

  dprint("CreateFadeValues wheel index: ");
  dprintln(wheel_index);

// make 2 palettes:
  while (palette_index < 2){
  calc_color = NeoWheel(wheel_index); // convert index to actual 32-bit color
  // split up original color into channels
  rgb[0] = (uint8_t)(calc_color >> 0);
  rgb[1] = (uint8_t)(calc_color >> 8);
  rgb[2] = (uint8_t)(calc_color >> 16);

  // fill in palette with faded values:
    for(i=0; i<FADE_LENGTH; i++){
      palette[palette_index][i] = pixels.Color(rgb[0], rgb[1], rgb[2]); // base color on current split-up color channels
      // now fade it for next slot in array:
      for(channel=0; channel<3; channel++){ // step through RGB channels
        channel_value = rgb[channel]; // copy it to an int for bigger math
        rgb[channel] = (channel_value * 40) /  100;
      }
    }
    palette_index++;
    wheel_index = wheel_index - 40; // 30 works for sure
  }
}

uint32_t NeoWheel(byte WheelPos) {
/* (From Adafruit sample code)
  Globals:
    pixels Adafruit Neopixel object

  Inputs:
    WheelPos (byte) Position on the color wheel (0 - 255)
    The colours are a transition r - g - b - back to r

  Outputs:
    packed color value as used in Adafruit libraries
*/

/*
  if(WheelPos < 85) {
   return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  */
  uint8_t red = 0;
  uint8_t green = 0;
  uint8_t blue = 0;
  if(WheelPos < 85) {
  //  return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
    red = WheelPos * 3;
    green = 255 - WheelPos;

  } else if(WheelPos < 170) {
    WheelPos -= 85;
    //  return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
    red = 255 - WheelPos * 3;
    blue = WheelPos * 3;

  } else {
    WheelPos -= 170;
    // return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
    green = WheelPos * 3;
    blue = 255 - WheelPos * 3;
  }
  return pixels.Color(red, green, blue);
}
