/*
 * usbhid.h
 *
 *  Created on: 2023Äê10ÔÂ19ÈÕ
 *      Author: tao
 */

#ifndef USBHID_H
#define USBHID_H

#ifdef __cplusplus
extern "C" {
#endif

#define USB_HID_DELAY_MS   10

/*********************************************************************
 * FUNCTIONS
 */

/*
 * Task Initialization for the BLE Application
 */
extern void USB_DevTransProcess(void);

/*
 * Task Event Processor for the BLE Application
 */
extern void DevHIDMouseReport(uint8_t mouse);

extern void DevHIDKeyReport(uint8_t key);

extern void USBHIDReleaseAllKey();

extern void DevASCIIKeyReport( uint8_t c );

extern void DevWakeup(void);


extern void DebugInit(void);

extern void DevEP1_OUT_Deal(uint8_t l);


extern void DevEP2_OUT_Deal(uint8_t l);

extern void DevEP3_OUT_Deal(uint8_t l);

extern void DevEP4_OUT_Deal(uint8_t l);

extern void USB_IRQHandler(void);

extern void USB_INIT(void);

#ifdef __cplusplus
}
#endif

#endif
