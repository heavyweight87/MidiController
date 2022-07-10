/*
 * usbh_midi.h
 *
 *  Created on: Jul 10, 2022
 *      Author: gcbla
 */

#ifndef USBHOST_CLASS_AUDIO_INC_USBH_MIDI_H_
#define USBHOST_CLASS_AUDIO_INC_USBH_MIDI_H_

#include <stdint.h>
#include "usbh_def.h"

/* A.1 Class-Specific MS Interface Descriptor Subtypes */
#define MS_DESCRIPTOR_UNDEFINED						0x00
#define MS_HEADER                                   0x01U
#define MIDI_IN_JACK	                  			0x02U
#define MIDI_OUT_JACK 	                            0x03U
#define MS_ELEMENT                                  0x04U
#define UAC_SELECTOR_UNIT                           0x05U
#define UAC_FEATURE_UNIT                            0x06U
#define UAC_PROCESSING_UNIT                         0x07U
#define UAC_EXTENSION_UNIT                          0x08U

#define AUDIO_MIDI_MAX_NUM_INPUT_JACK				0x02U
#define AUDIO_MIDI_MAX_NUM_OUTPUT_JACK				0x02U

/* 6.1.2.1  Class-Specific MS Interface Header Descriptor */
typedef struct
{
	uint8_t  bLength;
	uint8_t  bDescriptorType;
	uint8_t  bDescriptorSubtype;
	uint8_t  bcdADC[2];
	uint8_t  wTotalLength[2];
}AUDIO_MSHeaderDescTypeDef;

/* 6.1.2.2 Midi IN jack descriptor Descriptor */
typedef struct
{
	uint8_t  bLength;
	uint8_t  bDescriptorType;
	uint8_t  bDescriptorSubtype;
	uint8_t  bJackType;
	uint8_t  bJackID;
	uint8_t  iJack;
}AUDIO_MidiINJackDescTypeDef;

/* 6.1.2.2 Midi OUT jack descriptor Descriptor */
typedef struct
{
	uint8_t  bLength;
	uint8_t  bDescriptorType;
	uint8_t  bDescriptorSubtype;
	uint8_t  bJackType;
	uint8_t  bJackID;
	uint8_t  bNrInputPins;
	uint8_t  baSourceID;
	uint8_t  BaSourcePin;
}AUDIO_MidiOUTJackDescTypeDef;

/* Class-Specific MS(Midi Streaming) Interface Descriptor*/
typedef struct
{
	AUDIO_MSHeaderDescTypeDef   *HeaderDesc;
	AUDIO_MidiINJackDescTypeDef *MidiINJackDesc[AUDIO_MIDI_MAX_NUM_INPUT_JACK];
	AUDIO_MidiOUTJackDescTypeDef *MidiOutJackDesc[AUDIO_MIDI_MAX_NUM_OUTPUT_JACK];
}AUDIO_MSDescTypeDef;



USBH_StatusTypeDef USBH_AUDIO_FindMidiStreamingIn(USBH_HandleTypeDef *phost);
USBH_StatusTypeDef USBH_AUDIO_FindMidiStreamingOut(USBH_HandleTypeDef *phost);

#endif /* USBHOST_CLASS_AUDIO_INC_USBH_MIDI_H_ */
