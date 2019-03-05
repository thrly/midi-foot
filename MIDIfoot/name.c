#include "usb_names.h"

#define MIDI_NAME   {'M','I','D','I',' ','f','o','o','t'}
#define MIDI_NAME_LEN  9 // match the number of characters in name.

// Do not alter:
struct usb_string_descriptor_struct usb_string_product_name = {
        2 + MIDI_NAME_LEN * 2,
        3,
        MIDI_NAME
};
