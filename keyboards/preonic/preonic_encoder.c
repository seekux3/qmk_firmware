#include "preonic.h"
#include "tmk_core/common/eeprom.h"

float music_enc_mode[][2] = SONG(PLOVER_SOUND);

void pre_encoder_mode_change(){
  // Do nothing
}

void post_encoder_mode_change(){
  // Do nothing
}

void change_encoder_mode(bool negative){
  pre_encoder_mode_change();
  uint8_t old_enc_mode = encoder_mode;
  if(enabled_encoder_modes == 0){
    enabled_encoder_modes = 0x1F;
  }
  do {
    if(negative){
      if (encoder_mode == 0){
        encoder_mode = _NUM_ENCODER_MODES - 1;
      } else{
        encoder_mode = encoder_mode - 1;
      }
    } else {
        encoder_mode = (encoder_mode + 1) % _NUM_ENCODER_MODES;
    }
  } while(((1 << encoder_mode) & enabled_encoder_modes) == 0);
  if (old_enc_mode != encoder_mode)
    PLAY_SONG(music_enc_mode);
  post_encoder_mode_change();
}

uint16_t handle_encoder_clockwise(){
  uint16_t mapped_code = 0;
  switch(encoder_mode){
    default:
    case ENC_MODE_VOLUME:
      mapped_code = KC_VOLU;
      break;
    case ENC_MODE_MEDIA:
      mapped_code = KC_MEDIA_NEXT_TRACK;
      break;
    case ENC_MODE_SCROLL:
      mapped_code = KC_WH_D;
      break;
    case ENC_MODE_BRIGHTNESS:
      mapped_code = KC_BRIGHTNESS_UP;
      break;
#ifdef DYNAMIC_KEYMAP_ENABLE
    case ENC_MODE_CUSTOM0:
      mapped_code = retrieve_custom_encoder_config(0, ENC_CUSTOM_CW);
      break;
    case ENC_MODE_CUSTOM1:
      mapped_code = retrieve_custom_encoder_config(1, ENC_CUSTOM_CW);
      break;
    case ENC_MODE_CUSTOM2:
      mapped_code = retrieve_custom_encoder_config(2, ENC_CUSTOM_CW);
      break;
#endif
  }
  return mapped_code;
}

uint16_t handle_encoder_ccw(){
  uint16_t mapped_code = 0;
  switch(encoder_mode){
    default:
    case ENC_MODE_VOLUME:
      mapped_code = KC_VOLD;
      break;
    case ENC_MODE_MEDIA:
      mapped_code = KC_MEDIA_PREV_TRACK;
      break;
    case ENC_MODE_SCROLL:
      mapped_code = KC_WH_U;
      break;
    case ENC_MODE_BRIGHTNESS:
      mapped_code = KC_BRIGHTNESS_DOWN;
      break;
#ifdef DYNAMIC_KEYMAP_ENABLE
    case ENC_MODE_CUSTOM0:
      mapped_code = retrieve_custom_encoder_config(0, ENC_CUSTOM_CCW);
      break;
    case ENC_MODE_CUSTOM1:
      mapped_code = retrieve_custom_encoder_config(1, ENC_CUSTOM_CCW);
      break;
    case ENC_MODE_CUSTOM2:
      mapped_code = retrieve_custom_encoder_config(2, ENC_CUSTOM_CCW);
      break;
#endif
  }
  return mapped_code;
}

uint16_t handle_encoder_press(){
  uint16_t mapped_code = 0;
  switch(encoder_mode){
    case ENC_MODE_VOLUME:
      mapped_code = KC_MUTE;
      break;
    default:
    case ENC_MODE_MEDIA:
      mapped_code = KC_MEDIA_PLAY_PAUSE;
      break;
    case ENC_MODE_SCROLL:
      mapped_code = KC_BTN3;
      break;
#ifdef DYNAMIC_KEYMAP_ENABLE
    case ENC_MODE_CUSTOM0:
      mapped_code = retrieve_custom_encoder_config(0, ENC_CUSTOM_PRESS);
      break;
    case ENC_MODE_CUSTOM1:
      mapped_code = retrieve_custom_encoder_config(1, ENC_CUSTOM_PRESS);
      break;
    case ENC_MODE_CUSTOM2:
      mapped_code = retrieve_custom_encoder_config(2, ENC_CUSTOM_PRESS);
      break;
#endif
    case ENC_MODE_BRIGHTNESS:
      break;
  }
  return mapped_code;
}

uint16_t retrieve_custom_encoder_config(uint8_t encoder_idx, uint8_t behavior){
#ifdef DYNAMIC_KEYMAP_ENABLE
    void* addr = (void*)(EEPROM_CUSTOM_ENCODER + (encoder_idx * 6) + (behavior * 2));
    //big endian
    uint16_t keycode = eeprom_read_byte(addr) << 8;
    keycode |= eeprom_read_byte(addr + 1);
    return keycode;
#else
    return 0;
#endif
}

void set_custom_encoder_config(uint8_t encoder_idx, uint8_t behavior, uint16_t new_code){
#ifdef DYNAMIC_KEYMAP_ENABLE
    void* addr = (void*)(EEPROM_CUSTOM_ENCODER + (encoder_idx * 6) + (behavior * 2));
    eeprom_update_byte(addr, (uint8_t)(new_code >> 8));
    eeprom_update_byte(addr + 1, (uint8_t)(new_code & 0xFF));
#endif
}
