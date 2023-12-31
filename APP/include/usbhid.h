/*
 * usbhid.h
 *
 *  Created on: 2023��10��19��
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

extern void USBHIDMouseReport(uint8_t * mouse);

extern void USBHIDMouseMoveReport( uint8_t x , uint8_t y);

extern void DevHIDKeyReport(uint8_t key);

extern void USBHIDReleaseAllKey();

extern void DevASCIIKeyReport( uint8_t c );

extern void USBHIDASCIIString( uint8_t * c , uint8_t len );

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
