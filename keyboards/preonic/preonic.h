#pragma once

#include "quantum.h"

/**************************************************
** Include headers specific to keyboard revision **
**************************************************/
#ifdef KEYBOARD_preonic_rev1
  #include "rev1.h"
#endif

#ifdef KEYBOARD_preonic_rev2
  #include "rev2.h"
#endif

#ifdef KEYBOARD_preonic_rev3
  #include "rev3.h"
#endif

// Start these at the USER code range in VIA
enum my_keycodes {
  ENC_PRS = 0x5F80,	//ENC_PRESS
};

enum encoder_modes {
  ENC_MODE_VOLUME,
  ENC_MODE_MEDIA,
  ENC_MODE_SCROLL,
  ENC_MODE_BRIGHTNESS,
  ENC_MODE_CUSTOM0,
  ENC_MODE_CUSTOM1,
  ENC_MODE_CUSTOM2,
  _NUM_ENCODER_MODES,
};

enum custom_encoder_behavior {
    ENC_CUSTOM_CW = 0,
    ENC_CUSTOM_CCW,
    ENC_CUSTOM_PRESS
};

// Encoder Behavior
extern uint8_t encoder_value;
extern uint8_t encoder_mode;
extern uint8_t enabled_encoder_modes;

void pre_encoder_mode_change(void);
void post_encoder_mode_change(void);
void change_encoder_mode(bool negative);
uint16_t handle_encoder_clockwise(void);
uint16_t handle_encoder_ccw(void);
uint16_t handle_encoder_press(void);
uint16_t retrieve_custom_encoder_config(uint8_t encoder_idx, uint8_t behavior);
void set_custom_encoder_config(uint8_t encoder_idx, uint8_t behavior, uint16_t new_code);

/**************************************************
** Layout macros aliases common to all revisions **
**                                               **
**      Name of Alias     Matrix Name:           **
******* ----------------- ------------------- ****/
#define LAYOUT_ortho_5x12 LAYOUT_preonic_grid
