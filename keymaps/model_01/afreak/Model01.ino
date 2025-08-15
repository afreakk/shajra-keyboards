#include "Kaleidoscope.h"
#include "Kaleidoscope-IdleLEDs.h"
#include "Kaleidoscope-MouseKeys.h"
#include "Kaleidoscope-LEDControl.h"
#include "Kaleidoscope-HostPowerManagement.h"
#include "Kaleidoscope-USB-Quirks.h"


enum { PRIMARY, FUNCTION, GAMING, NORWEGIAN }; // layers

KEYMAPS(

  [PRIMARY] = KEYMAP_STACKED
(
    LockLayer(NORWEGIAN), Key_1, Key_2, Key_3, Key_4, Key_5, LSHIFT(Key_LeftGui),
    Key_Backtick,         Key_Q, Key_W, Key_F, Key_P, Key_G, Key_Tab,
    Key_PageUp,           Key_A, Key_R, Key_S, Key_T, Key_D,
    Key_PageDown,         Key_Z, Key_X, Key_C, Key_V, Key_B, Key_Escape,
    Key_LeftControl, Key_Backspace, Key_LeftGui, Key_LeftShift,
    ShiftToLayer(FUNCTION),
    
    LockLayer(PRIMARY),  Key_6, Key_7, Key_8,     Key_9,      Key_0,         LockLayer(GAMING),//LockLayer(NUMPAD),
    Key_Enter,          Key_J, Key_L, Key_U,     Key_Y,      Key_Semicolon, Key_Equals,
                        Key_H, Key_N, Key_E,     Key_I,      Key_O,         Key_Quote,
    Key_Escape,         Key_K, Key_M, Key_Comma, Key_Period, Key_Slash,     Key_Minus,
    Key_RightShift, Key_LeftAlt, Key_Spacebar, Key_RightControl,
    ShiftToLayer(FUNCTION)
),

  [FUNCTION] =  KEYMAP_STACKED
  (___,       Key_F1,           Key_F2,             Key_F3,         Key_F4,           Key_F5,           Key_LEDEffectNext,
   Key_Tab,   Key_mouseWarpNW,  Key_mouseScrollUp,  Key_mouseBtnL,  Key_mouseWarpNE,  Key_mouseWarpEnd, ___,
   Key_Home,  Key_mouseL,       Key_mouseDn,        Key_mouseUp,    Key_mouseR,       Key_mouseBtnM,
   Key_End,   Key_mouseWarpSW,  Key_mouseScrollDn,  Key_mouseBtnR,  Key_mouseWarpSE,  Key_PrintScreen,  ___,
   ___,       Key_Delete,       ___,          ___,
   ___,

   Consumer_ScanPreviousTrack, Key_F6,                 Key_F7,                   Key_F8,                   Key_F9,          Key_F10,          Key_F11,
   Consumer_PlaySlashPause,    Consumer_ScanNextTrack, Key_LeftCurlyBracket,     Key_RightCurlyBracket,    Key_LeftBracket, Key_RightBracket, Key_F12,
                               Key_LeftArrow,          Key_DownArrow,            Key_UpArrow,              Key_RightArrow,  Key_Escape,    ___,
   Key_PcApplication,          Consumer_Mute,          Consumer_VolumeDecrement, Consumer_VolumeIncrement, ___,             Key_Backslash,    Key_Pipe,
   ___, ___, Key_Enter, ___,
   ___),

  [GAMING] =  KEYMAP_STACKED
  (___, ___,   ___,   ___,   ___,   ___,   ___,
   ___, Key_Q, Key_W, Key_E, Key_R, Key_T, ___,
   ___, Key_A, Key_S, Key_D, Key_F, Key_G,
   ___, Key_Z, Key_X, Key_C, Key_V, Key_B, ___,
   Key_Tab, Key_Spacebar, Key_LeftControl, Key_RightAlt,
   Key_LeftShift,

   ___, ___,   ___,   ___,   ___,   ___,   ___,
   ___, Key_Y, Key_U, Key_I, Key_O, Key_P, ___,
        Key_H, Key_J, Key_K, Key_L, Key_Semicolon, ___,
   ___, Key_N, Key_M, ___,   ___,   ___,   ___,
   Key_RightShift, Key_LeftAlt, Key_LeftGui, Key_RightControl,
   ___),


  [NORWEGIAN] =  KEYMAP_STACKED
  (___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___,
   ___,

   ___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, Key_F23, Key_F24,
   ___, ___, ___, ___, ___, Key_F22,
   ___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___,
   ___)
)


#define gruvboxFG  CRGB(235, 219, 178)
#define gruvboxBG  CRGB( 40,  40,  40)
#define gruvboxAccent  CRGB(254, 128, 25)
#define gruvboxRed  CRGB(204, 36, 29)
#define gruvboxBlue  CRGB(69, 133, 136)
#define gruvboxGreen  CRGB(152, 151, 26)
#define gruvboxYellow  CRGB(215, 153, 33)
#define gruvboxOrange  CRGB(214, 93, 14)
#define gruvboxPurple  CRGB(177, 98, 134)



// use https://github.com/keyboardio/Kaleidoscope/blob/master/plugins/Kaleidoscope-Hardware-Keyboardio-Model01/src/kaleidoscope/device/keyboardio/Model01.h#L160 for reference
namespace kaleidoscope {
    namespace plugin {
        class LocalLEDEffect :  public Plugin {
            public:
                EventHandlerResult onSetup() {
                    return onLayerChange();
                }

                EventHandlerResult onLayerChange() {
                    for (auto keyAddr : KeyAddr::all()) {
                        ::LEDControl.setCrgbAt(KeyAddr(keyAddr), CRGB(0,0,0));
                    }
                    if (Layer.isActive(NORWEGIAN)) {
                        // Norwegian layer
                        ::LEDControl.setCrgbAt(KeyAddr(0,0), gruvboxAccent);
                        // ÆØÅ keys
                        ::LEDControl.setCrgbAt(KeyAddr(1,15), gruvboxRed);
                        ::LEDControl.setCrgbAt(KeyAddr(2,14), gruvboxBlue);
                        ::LEDControl.setCrgbAt(KeyAddr(2,15), gruvboxFG);
                    }
                    
                    if (Layer.isActive(GAMING)) {
                        // Gaming layer 
                        ::LEDControl.setCrgbAt(KeyAddr(0,15), gruvboxAccent);
                        // WASD keys
                        ::LEDControl.setCrgbAt(KeyAddr(1,2), gruvboxBlue);
                        ::LEDControl.setCrgbAt(KeyAddr(2,1), gruvboxBlue);
                        ::LEDControl.setCrgbAt(KeyAddr(2,2), gruvboxBlue);
                        ::LEDControl.setCrgbAt(KeyAddr(2,3), gruvboxBlue);

                        ::LEDControl.setCrgbAt(KeyAddr(1,7), gruvboxRed);
                    }
                    
                    if (Layer.isActive(FUNCTION)) {
                        // Function layer
                        ::LEDControl.setCrgbAt(KeyAddr(3,6), gruvboxAccent);
                        ::LEDControl.setCrgbAt(KeyAddr(3,9), gruvboxAccent);
                        // F1-F12 keys
                        ::LEDControl.setCrgbAt(KeyAddr(0,1), gruvboxFG);
                        ::LEDControl.setCrgbAt(KeyAddr(0,2), gruvboxFG);
                        ::LEDControl.setCrgbAt(KeyAddr(0,3), gruvboxFG);
                        ::LEDControl.setCrgbAt(KeyAddr(0,4), gruvboxFG);
                        ::LEDControl.setCrgbAt(KeyAddr(0,5), gruvboxFG);
                        ::LEDControl.setCrgbAt(KeyAddr(0,10), gruvboxFG);
                        ::LEDControl.setCrgbAt(KeyAddr(0,11), gruvboxFG);
                        ::LEDControl.setCrgbAt(KeyAddr(0,12), gruvboxFG);
                        ::LEDControl.setCrgbAt(KeyAddr(0,13), gruvboxFG);
                        ::LEDControl.setCrgbAt(KeyAddr(0,14), gruvboxFG);
                        ::LEDControl.setCrgbAt(KeyAddr(0,15), gruvboxFG);
                        ::LEDControl.setCrgbAt(KeyAddr(1,15), gruvboxFG);

                        // mouse-move
                        ::LEDControl.setCrgbAt(KeyAddr(2,1), gruvboxOrange);
                        ::LEDControl.setCrgbAt(KeyAddr(2,2), gruvboxOrange);
                        ::LEDControl.setCrgbAt(KeyAddr(2,3), gruvboxOrange);
                        ::LEDControl.setCrgbAt(KeyAddr(2,4), gruvboxOrange);

                        // mouseBtnM
                        ::LEDControl.setCrgbAt(KeyAddr(2,5), gruvboxPurple);
                        //  scrollup
                        ::LEDControl.setCrgbAt(KeyAddr(1,2), gruvboxGreen);
                        //  scrolldown
                        ::LEDControl.setCrgbAt(KeyAddr(3,2), gruvboxGreen);
                        // mouseBtnL
                        ::LEDControl.setCrgbAt(KeyAddr(1,3), gruvboxYellow);
                        // mouseBtnR
                        ::LEDControl.setCrgbAt(KeyAddr(3,3), gruvboxYellow);

                        // mouseWarpNW
                        ::LEDControl.setCrgbAt(KeyAddr(1,1), gruvboxBlue);
                        // mouseWarpNE
                        ::LEDControl.setCrgbAt(KeyAddr(1,4), gruvboxBlue);
                        // mouseWarpSW
                        ::LEDControl.setCrgbAt(KeyAddr(3,1), gruvboxBlue);
                        // mouseWarpSE
                        ::LEDControl.setCrgbAt(KeyAddr(3,4), gruvboxBlue);


                        // Consumer_ScanPreviousTrack
                        ::LEDControl.setCrgbAt(KeyAddr(0,9), gruvboxBlue);
                        // Consumer_PlaySlashPause
                        ::LEDControl.setCrgbAt(KeyAddr(1,9), gruvboxBlue);
                        // Consumer_ScanNextTrack
                        ::LEDControl.setCrgbAt(KeyAddr(1,10), gruvboxBlue);
                        // curlybrackets
                        ::LEDControl.setCrgbAt(KeyAddr(1,11), gruvboxRed);
                        ::LEDControl.setCrgbAt(KeyAddr(1,12), gruvboxRed);

                        // brackets
                        ::LEDControl.setCrgbAt(KeyAddr(1,13), gruvboxBlue);
                        ::LEDControl.setCrgbAt(KeyAddr(1,14), gruvboxBlue);

                        // consumer_mute  
                        ::LEDControl.setCrgbAt(KeyAddr(3,10), gruvboxRed);
                        ::LEDControl.setCrgbAt(KeyAddr(3,11), gruvboxGreen);
                        ::LEDControl.setCrgbAt(KeyAddr(3,12), gruvboxGreen);
                    }
                    
                    return EventHandlerResult::OK;
                }
        };
    }
}
kaleidoscope::plugin::LocalLEDEffect LocalLEDEffect;  // singleton instance



/** toggleLedsOnSuspendResume toggles the LEDs off when the host goes to sleep,
 * and turns them back on when it wakes up.
 */
void toggleLedsOnSuspendResume(kaleidoscope::plugin::HostPowerManagement::Event event) {
  switch (event) {
  case kaleidoscope::plugin::HostPowerManagement::Suspend:
    LEDControl.disable();
    break;
  case kaleidoscope::plugin::HostPowerManagement::Resume:
    LEDControl.enable();
    break;
  case kaleidoscope::plugin::HostPowerManagement::Sleep:
    break;
  }
}

/** hostPowerManagementEventHandler dispatches power management events (suspend,
 * resume, and sleep) to other functions that perform action based on these
 * events.
 */
void hostPowerManagementEventHandler(kaleidoscope::plugin::HostPowerManagement::Event event) {
  toggleLedsOnSuspendResume(event);
}

KALEIDOSCOPE_INIT_PLUGINS(

  // LEDControl provides support for other LED modes
  LEDControl,

  IdleLEDs,

  // We start with the LED effect that turns off all the LEDs.
  LEDOff,


  // The MouseKeys plugin lets you add keys to your keymap which move the mouse.
  MouseKeys,

  // The HostPowerManagement plugin allows us to turn LEDs off when then host
  // goes to sleep, and resume them when it wakes up.
  HostPowerManagement,

  // The USBQuirks plugin lets you do some things with USB that we aren't
  // comfortable - or able - to do automatically, but can be useful
  // nevertheless. Such as toggling the key report protocol between Boot (used
  // by BIOSes) and Report (NKRO).
  USBQuirks,
  LocalLEDEffect
);

/** The 'setup' function is one of the two standard Arduino sketch functions.
 * It's called when your keyboard first powers up. This is where you set up
 * Kaleidoscope and any plugins.
 */
void setup() {
  Kaleidoscope.setup();
}

/** loop is the second of the standard Arduino sketch functions.
  * As you might expect, it runs in a loop, never exiting.
  *
  * For Kaleidoscope-based keyboard firmware, you usually just want to
  * call Kaleidoscope.loop(); and not do anything custom here.
  */

void loop() {
  Kaleidoscope.loop();
}
