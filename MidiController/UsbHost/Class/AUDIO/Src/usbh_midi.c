/*
 * usbh_midi.c
 *
 *  Created on: Jul 10, 2022
 *      Author: gcbla
 */

#include "usbh_midi.h"
#include "usbh_audio.h"

USBH_StatusTypeDef USBH_AUDIO_FindMidiStreamingOut(USBH_HandleTypeDef *phost)
{
  uint8_t interface, alt_settings;
  USBH_StatusTypeDef status = USBH_FAIL ;
  AUDIO_HandleTypeDef *AUDIO_Handle;

  AUDIO_Handle = (AUDIO_HandleTypeDef *) phost->pActiveClass->pData;

  /* Look For AUDIOSTREAMING IN interface */
  alt_settings = 0U;
  for (interface = 0U; interface < USBH_MAX_NUM_INTERFACES; interface++)
  {
    if ((phost->device.CfgDesc.Itf_Desc[interface].bInterfaceClass == AC_CLASS) &&
        (phost->device.CfgDesc.Itf_Desc[interface].bInterfaceSubClass == USB_SUBCLASS_MIDISTREAMING))
    {
      if (((phost->device.CfgDesc.Itf_Desc[interface].Ep_Desc[0].bEndpointAddress & 0x80U) == 0x00U) &&
          (phost->device.CfgDesc.Itf_Desc[interface].Ep_Desc[0].wMaxPacketSize > 0U))
      {
        AUDIO_Handle->midi_stream_out[alt_settings].Ep = phost->device.CfgDesc.Itf_Desc[interface].Ep_Desc[0].bEndpointAddress;
        AUDIO_Handle->midi_stream_out[alt_settings].EpSize = phost->device.CfgDesc.Itf_Desc[interface].Ep_Desc[0].wMaxPacketSize;
        AUDIO_Handle->midi_stream_out[alt_settings].interface = phost->device.CfgDesc.Itf_Desc[interface].bInterfaceNumber;
        AUDIO_Handle->midi_stream_out[alt_settings].AltSettings = phost->device.CfgDesc.Itf_Desc[interface].bAlternateSetting;
        AUDIO_Handle->midi_stream_out[alt_settings].Poll = phost->device.CfgDesc.Itf_Desc[interface].Ep_Desc[0].bInterval;
        AUDIO_Handle->midi_stream_out[alt_settings].valid = 1U;
        alt_settings++;
      }
    }
  }

  if (alt_settings > 0U)
  {
    status = USBH_OK;
  }

  return status;
}


USBH_StatusTypeDef USBH_AUDIO_FindMidiStreamingIn(USBH_HandleTypeDef *phost)
{
  uint8_t interface, alt_settings;
  USBH_StatusTypeDef status = USBH_FAIL ;
  AUDIO_HandleTypeDef *AUDIO_Handle;

  AUDIO_Handle = (AUDIO_HandleTypeDef *) phost->pActiveClass->pData;

  /* Look For AUDIOSTREAMING IN interface */
  alt_settings = 0U;
  for (interface = 0U; interface < USBH_MAX_NUM_INTERFACES; interface++)
  {
    if ((phost->device.CfgDesc.Itf_Desc[interface].bInterfaceClass == AC_CLASS) &&
        (phost->device.CfgDesc.Itf_Desc[interface].bInterfaceSubClass == USB_SUBCLASS_MIDISTREAMING))
    {
      if (((phost->device.CfgDesc.Itf_Desc[interface].Ep_Desc[0].bEndpointAddress & 0x80U) != 0U) &&
          (phost->device.CfgDesc.Itf_Desc[interface].Ep_Desc[0].wMaxPacketSize > 0U))
      {
        AUDIO_Handle->midi_stream_in[alt_settings].Ep = phost->device.CfgDesc.Itf_Desc[interface].Ep_Desc[0].bEndpointAddress;
        AUDIO_Handle->midi_stream_in[alt_settings].EpSize = phost->device.CfgDesc.Itf_Desc[interface].Ep_Desc[0].wMaxPacketSize;
        AUDIO_Handle->midi_stream_in[alt_settings].interface = phost->device.CfgDesc.Itf_Desc[interface].bInterfaceNumber;
        AUDIO_Handle->midi_stream_in[alt_settings].AltSettings = phost->device.CfgDesc.Itf_Desc[interface].bAlternateSetting;
        AUDIO_Handle->midi_stream_in[alt_settings].Poll = phost->device.CfgDesc.Itf_Desc[interface].Ep_Desc[0].bInterval;
        AUDIO_Handle->midi_stream_in[alt_settings].valid = 1U;
        alt_settings++;
      }
    }
  }

  if (alt_settings > 0U)
  {
    status = USBH_OK;
  }

  return status;
}
