// !!! DO NOT ADD #pragma once !!! //

// Step 1.
// Declare custom effects using the RGB_MATRIX_EFFECT macro
// (note the lack of semicolon after the macro!)
RGB_MATRIX_EFFECT(red_underglow)
RGB_MATRIX_EFFECT(white_underglow)

// Step 2.
// Define effects inside the `RGB_MATRIX_CUSTOM_EFFECT_IMPLS` ifdef block
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#define UNDERGLOW_INDEX (62)
// e.g: A simple effect, self-contained within a single method
static bool red_underglow(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);
  for (uint8_t i = led_min; i < led_max; i++) {
      if (i < UNDERGLOW_INDEX)
        rgb_matrix_set_color(i, 0x00, 0x00, 0x00);
      else
        rgb_matrix_set_color(i, 0xff, 0x00, 0x00);
  }
  return led_max < DRIVER_LED_TOTAL;
}

// e.g: A simple effect, self-contained within a single method
static bool white_underglow(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);
  for (uint8_t i = led_min; i < led_max; i++) {
      if (i < UNDERGLOW_INDEX)
        rgb_matrix_set_color(i, 0x00, 0x00, 0x00);
      else
        rgb_matrix_set_color(i, 0xff, 0xff, 0xff);
  }
  return led_max < DRIVER_LED_TOTAL;
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
