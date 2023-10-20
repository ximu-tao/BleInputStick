/********************************** (C) COPYRIGHT *******************************
 * File Name          : Main.c
 * Author             : WCH
 * Version            : V1.1
 * Date               : 2022/01/25
 * Description        : ģ��USB�����豸������֧��������
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for 
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/

#include "CH58x_common.h"

#define DevEP0SIZE    0x40

// ֧�ֵ����ӿ�����
#define USB_INTERFACE_MAX_NUM       2
#define SHIFT 0x00
// �ӿںŵ����ֵ
#define USB_INTERFACE_MAX_INDEX      1

// �豸������
const uint8_t MyDevDescr[] = {0x12, 0x01, 0x10, 0x01, 0x00, 0x00, 0x00, DevEP0SIZE, 0x3d, 0x41, 0x07, 0x21, 0x00, 0x00,
                              0x01, 0x02, 0x00, 0x01};
// ����������
const uint8_t MyCfgDescr[] = {
    0x09, 0x02, 0x3b, 0x00, 0x02, 0x01, 0x00, 0xA0, 0x32, //����������
    0x09, 0x04, 0x00, 0x00, 0x01, 0x03, 0x01, 0x01, 0x00, //�ӿ�������,����
    0x09, 0x21, 0x11, 0x01, 0x00, 0x01, 0x22, 0x3e, 0x00, //HID��������
    0x07, 0x05, 0x81, 0x03, 0x08, 0x00, 0x0a,             //�˵�������
    0x09, 0x04, 0x01, 0x00, 0x01, 0x03, 0x01, 0x02, 0x00, //�ӿ�������,���
    0x09, 0x21, 0x10, 0x01, 0x00, 0x01, 0x22, 0x34, 0x00, //HID��������
    0x07, 0x05, 0x82, 0x03, 0x04, 0x00, 0x0a              //�˵�������

};


static uint8_t asciimap[128] = {
    0x00,             // NUL
    0x00,             // SOH
    0x00,             // STX
    0x00,             // ETX
    0x00,             // EOT
    0x00,             // ENQ
    0x00,             // ACK
    0x00,             // BEL
    0x2a,           // BS   Backspace
    0x2b,           // TAB  Tab
    0x28,           // LF   Enter
    0x00,             // VT
    0x00,             // FF
    0x00,             // CR
    0x00,             // SO
    0x00,             // SI
    0x00,             // DEL
    0x00,             // DC1
    0x00,             // DC2
    0x00,             // DC3
    0x00,             // DC4
    0x00,             // NAK
    0x00,             // SYN
    0x00,             // ETB
    0x00,             // CAN
    0x00,             // EM
    0x00,             // SUB
    0x00,             // ESC
    0x00,             // FS
    0x00,             // GS
    0x00,             // RS
    0x00,             // US

    0x2c,          //  ' '
    0x1e|SHIFT,    // !
    0x34|SHIFT,    // "
    0x20|SHIFT,    // #
    0x21|SHIFT,    // $
    0x22|SHIFT,    // %
    0x24|SHIFT,    // &
    0x34,          // '
    0x26|SHIFT,    // (
    0x27|SHIFT,    // )
    0x25|SHIFT,    // *
    0x2e|SHIFT,    // +
    0x36,          // ,
    0x2d,          // -
    0x37,          // .
    0x38,          // /
    0x27,          // 0
    0x1e,          // 1
    0x1f,          // 2
    0x20,          // 3
    0x21,          // 4
    0x22,          // 5
    0x23,          // 6
    0x24,          // 7
    0x25,          // 8
    0x26,          // 9
    0x33|SHIFT,      // :
    0x33,          // ;
    0x36|SHIFT,      // <
    0x2e,          // =
    0x37|SHIFT,      // >
    0x38|SHIFT,      // ?
    0x1f|SHIFT,      // @
    0x04|SHIFT,      // A
    0x05|SHIFT,      // B
    0x06|SHIFT,      // C
    0x07|SHIFT,      // D
    0x08|SHIFT,      // E
    0x09|SHIFT,      // F
    0x0a|SHIFT,      // G
    0x0b|SHIFT,      // H
    0x0c|SHIFT,      // I
    0x0d|SHIFT,      // J
    0x0e|SHIFT,      // K
    0x0f|SHIFT,      // L
    0x10|SHIFT,      // M
    0x11|SHIFT,      // N
    0x12|SHIFT,      // O
    0x13|SHIFT,      // P
    0x14|SHIFT,      // Q
    0x15|SHIFT,      // R
    0x16|SHIFT,      // S
    0x17|SHIFT,      // T
    0x18|SHIFT,      // U
    0x19|SHIFT,      // V
    0x1a|SHIFT,      // W
    0x1b|SHIFT,      // X
    0x1c|SHIFT,      // Y
    0x1d|SHIFT,      // Z
    0x2f,          // [
    0x31,          // bslash
    0x30,          // ]
    0x23|SHIFT,    // ^
    0x2d|SHIFT,    // _
    0x35,          // `
    0x04,          // a
    0x05,          // b
    0x06,          // c
    0x07,          // d
    0x08,          // e
    0x09,          // f
    0x0a,          // g
    0x0b,          // h
    0x0c,          // i
    0x0d,          // j
    0x0e,          // k
    0x0f,          // l
    0x10,          // m
    0x11,          // n
    0x12,          // o
    0x13,          // p
    0x14,          // q
    0x15,          // r
    0x16,          // s
    0x17,          // t
    0x18,          // u
    0x19,          // v
    0x1a,          // w
    0x1b,          // x
    0x1c,          // y
    0x1d,          // z
    0x2f|SHIFT,    // {
    0x31|SHIFT,    // |
    0x30|SHIFT,    // }
    0x35|SHIFT,    // ~
    0               // DEL
};


/* USB�ٶ�ƥ�������� */
const uint8_t My_QueDescr[] = {0x0A, 0x06, 0x00, 0x02, 0xFF, 0x00, 0xFF, 0x40, 0x01, 0x00};

/* USBȫ��ģʽ,�����ٶ����������� */
uint8_t USB_FS_OSC_DESC[sizeof(MyCfgDescr)] = {
    0x09, 0x07, /* ��������ͨ�������� */
};

// ����������
const uint8_t MyLangDescr[] = {0x04, 0x03, 0x09, 0x04};
// ������Ϣ
const uint8_t MyManuInfo[] = {0x0E, 0x03, 'w', 0, 'c', 0, 'h', 0, '.', 0, 'c', 0, 'n', 0};
// ��Ʒ��Ϣ
const uint8_t MyProdInfo[] = {0x0C, 0x03, 'C', 0, 'H', 0, '5', 0, '8', 0, 'x', 0};
/*HID�౨��������*/
const uint8_t KeyRepDesc[] = {0x05, 0x01, 0x09, 0x06, 0xA1, 0x01, 0x05, 0x07, 0x19, 0xe0, 0x29, 0xe7, 0x15, 0x00, 0x25,
                              0x01, 0x75, 0x01, 0x95, 0x08, 0x81, 0x02, 0x95, 0x01, 0x75, 0x08, 0x81, 0x01, 0x95, 0x03,
                              0x75, 0x01, 0x05, 0x08, 0x19, 0x01, 0x29, 0x03, 0x91, 0x02, 0x95, 0x05, 0x75, 0x01, 0x91,
                              0x01, 0x95, 0x06, 0x75, 0x08, 0x26, 0xff, 0x00, 0x05, 0x07, 0x19, 0x00, 0x29, 0x91, 0x81,
                              0x00, 0xC0};
const uint8_t MouseRepDesc[] = {0x05, 0x01, 0x09, 0x02, 0xA1, 0x01, 0x09, 0x01, 0xA1, 0x00, 0x05, 0x09, 0x19, 0x01, 0x29,
                                0x03, 0x15, 0x00, 0x25, 0x01, 0x75, 0x01, 0x95, 0x03, 0x81, 0x02, 0x75, 0x05, 0x95, 0x01,
                                0x81, 0x01, 0x05, 0x01, 0x09, 0x30, 0x09, 0x31, 0x09, 0x38, 0x15, 0x81, 0x25, 0x7f, 0x75,
                                0x08, 0x95, 0x03, 0x81, 0x06, 0xC0, 0xC0};

/**********************************************************/
uint8_t        DevConfig, Ready;
uint8_t        SetupReqCode;
uint16_t       SetupReqLen;
const uint8_t *pDescr;
uint8_t        Report_Value[USB_INTERFACE_MAX_INDEX+1] = {0x00};
uint8_t        Idle_Value[USB_INTERFACE_MAX_INDEX+1] = {0x00};
uint8_t        USB_SleepStatus = 0x00; /* USB˯��״̬ */
uint8_t        CapsLock = 0;
/*����������*/
uint8_t HIDMouse[4] = {0x0, 0x0, 0x0, 0x0};
uint8_t HIDKey[8] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
/******** �û��Զ������˵�RAM ****************************************/
__attribute__((aligned(4))) uint8_t EP0_Databuf[64 + 64 + 64]; //ep0(64)+ep4_out(64)+ep4_in(64)
__attribute__((aligned(4))) uint8_t EP1_Databuf[64 + 64];      //ep1_out(64)+ep1_in(64)
__attribute__((aligned(4))) uint8_t EP2_Databuf[64 + 64];      //ep2_out(64)+ep2_in(64)
__attribute__((aligned(4))) uint8_t EP3_Databuf[64 + 64];      //ep3_out(64)+ep3_in(64)

/*********************************************************************
 * @fn      USB_DevTransProcess
 *
 * @brief   USB ���䴦������
 *
 * @return  none
 */
void USB_DevTransProcess(void)
{
    uint8_t len, chtype;
    uint8_t intflag, errflag = 0;

    intflag = R8_USB_INT_FG;
    if(intflag & RB_UIF_TRANSFER)
    {
        if((R8_USB_INT_ST & MASK_UIS_TOKEN) != MASK_UIS_TOKEN) // �ǿ���
        {
            switch(R8_USB_INT_ST & (MASK_UIS_TOKEN | MASK_UIS_ENDP))
            // �����������ƺͶ˵��
            {
                case UIS_TOKEN_IN:
                {
                    switch(SetupReqCode)
                    {
                        case USB_GET_DESCRIPTOR:
                            len = SetupReqLen >= DevEP0SIZE ? DevEP0SIZE : SetupReqLen; // ���δ��䳤��
                            memcpy(pEP0_DataBuf, pDescr, len);                          /* �����ϴ����� */
                            SetupReqLen -= len;
                            pDescr += len;
                            R8_UEP0_T_LEN = len;
                            R8_UEP0_CTRL ^= RB_UEP_T_TOG; // ��ת
                            break;
                        case USB_SET_ADDRESS:
                            R8_USB_DEV_AD = (R8_USB_DEV_AD & RB_UDA_GP_BIT) | SetupReqLen;
                            R8_UEP0_CTRL = UEP_R_RES_ACK | UEP_T_RES_NAK;
                            break;

                        case USB_SET_FEATURE:
                            break;

                        default:
                            R8_UEP0_T_LEN = 0; // ״̬�׶�����жϻ�����ǿ���ϴ�0�������ݰ��������ƴ���
                            R8_UEP0_CTRL = UEP_R_RES_ACK | UEP_T_RES_NAK;
                            break;
                    }
                }
                break;

                case UIS_TOKEN_OUT:
                {
                    len = R8_USB_RX_LEN;
                    if(SetupReqCode == 0x09)
                    {
                        CapsLock = pEP0_DataBuf[0] & (1<<1);
                        PRINT("[%s] Num Lock\t", (pEP0_DataBuf[0] & (1<<0)) ? "*" : " ");
                        PRINT("[%s] Caps Lock\t", (pEP0_DataBuf[0] & (1<<1)) ? "*" : " ");
                        PRINT("[%s] Scroll Lock\n", (pEP0_DataBuf[0] & (1<<2)) ? "*" : " ");
                    }
                }
                break;

                case UIS_TOKEN_OUT | 1:
                {
                    if(R8_USB_INT_ST & RB_UIS_TOG_OK)
                    { // ��ͬ�������ݰ�������
                        R8_UEP1_CTRL ^= RB_UEP_R_TOG;
                        len = R8_USB_RX_LEN;
                        DevEP1_OUT_Deal(len);
                    }
                }
                break;

                case UIS_TOKEN_IN | 1:
                    R8_UEP1_CTRL ^= RB_UEP_T_TOG;
                    R8_UEP1_CTRL = (R8_UEP1_CTRL & ~MASK_UEP_T_RES) | UEP_T_RES_NAK;
                    break;

                case UIS_TOKEN_OUT | 2:
                {
                    if(R8_USB_INT_ST & RB_UIS_TOG_OK)
                    { // ��ͬ�������ݰ�������
                        R8_UEP2_CTRL ^= RB_UEP_R_TOG;
                        len = R8_USB_RX_LEN;
                        DevEP2_OUT_Deal(len);
                    }
                }
                break;

                case UIS_TOKEN_IN | 2:
                    R8_UEP2_CTRL ^= RB_UEP_T_TOG;
                    R8_UEP2_CTRL = (R8_UEP2_CTRL & ~MASK_UEP_T_RES) | UEP_T_RES_NAK;
                    break;

                case UIS_TOKEN_OUT | 3:
                {
                    if(R8_USB_INT_ST & RB_UIS_TOG_OK)
                    { // ��ͬ�������ݰ�������
                        R8_UEP3_CTRL ^= RB_UEP_R_TOG;
                        len = R8_USB_RX_LEN;
                        DevEP3_OUT_Deal(len);
                    }
                }
                break;

                case UIS_TOKEN_IN | 3:
                    R8_UEP3_CTRL ^= RB_UEP_T_TOG;
                    R8_UEP3_CTRL = (R8_UEP3_CTRL & ~MASK_UEP_T_RES) | UEP_T_RES_NAK;
                    break;

                case UIS_TOKEN_OUT | 4:
                {
                    if(R8_USB_INT_ST & RB_UIS_TOG_OK)
                    {
                        R8_UEP4_CTRL ^= RB_UEP_R_TOG;
                        len = R8_USB_RX_LEN;
                        DevEP4_OUT_Deal(len);
                    }
                }
                break;

                case UIS_TOKEN_IN | 4:
                    R8_UEP4_CTRL ^= RB_UEP_T_TOG;
                    R8_UEP4_CTRL = (R8_UEP4_CTRL & ~MASK_UEP_T_RES) | UEP_T_RES_NAK;
                    break;

                default:
                    break;
            }
            R8_USB_INT_FG = RB_UIF_TRANSFER;
        }
        if(R8_USB_INT_ST & RB_UIS_SETUP_ACT) // Setup������
        {
            R8_UEP0_CTRL = RB_UEP_R_TOG | RB_UEP_T_TOG | UEP_R_RES_ACK | UEP_T_RES_NAK;
            SetupReqLen = pSetupReqPak->wLength;
            SetupReqCode = pSetupReqPak->bRequest;
            chtype = pSetupReqPak->bRequestType;

            len = 0;
            errflag = 0;
            if((pSetupReqPak->bRequestType & USB_REQ_TYP_MASK) != USB_REQ_TYP_STANDARD)
            {
                /* �Ǳ�׼���� */
                /* ��������,�������󣬲�������� */
                if(pSetupReqPak->bRequestType & 0x40)
                {
                    /* �������� */
                }
                else if(pSetupReqPak->bRequestType & 0x20)
                {
                    switch(SetupReqCode)
                    {
                        case DEF_USB_SET_IDLE: /* 0x0A: SET_IDLE */         //����������HID�豸�ض����뱨���Ŀ���ʱ����
                            Idle_Value[pSetupReqPak->wIndex] = (uint8_t)(pSetupReqPak->wValue>>8);
                            break; //���һ��Ҫ��

                        case DEF_USB_SET_REPORT: /* 0x09: SET_REPORT */     //����������HID�豸�ı���������
                            break;

                        case DEF_USB_SET_PROTOCOL: /* 0x0B: SET_PROTOCOL */ //����������HID�豸��ǰ��ʹ�õ�Э��
                            Report_Value[pSetupReqPak->wIndex] = (uint8_t)(pSetupReqPak->wValue);
                            break;

                        case DEF_USB_GET_IDLE: /* 0x02: GET_IDLE */         //�������ȡHID�豸�ض����뱨���ĵ�ǰ�Ŀ��б���
                            EP0_Databuf[0] = Idle_Value[pSetupReqPak->wIndex];
                            len = 1;
                            break;

                        case DEF_USB_GET_PROTOCOL: /* 0x03: GET_PROTOCOL */     //��������HID�豸��ǰ��ʹ�õ�Э��
                            EP0_Databuf[0] = Report_Value[pSetupReqPak->wIndex];
                            len = 1;
                            break;

                        default:
                            errflag = 0xFF;
                    }
                }
            }
            else /* ��׼���� */
            {
                switch(SetupReqCode)
                {
                    case USB_GET_DESCRIPTOR:
                    {
                        switch(((pSetupReqPak->wValue) >> 8))
                        {
                            case USB_DESCR_TYP_DEVICE:
                            {
                                pDescr = MyDevDescr;
                                len = MyDevDescr[0];
                            }
                            break;

                            case USB_DESCR_TYP_CONFIG:
                            {
                                pDescr = MyCfgDescr;
                                len = MyCfgDescr[2];
                            }
                            break;

                            case USB_DESCR_TYP_HID:
                                switch((pSetupReqPak->wIndex) & 0xff)
                                {
                                    /* ѡ��ӿ� */
                                    case 0:
                                        pDescr = (uint8_t *)(&MyCfgDescr[18]);
                                        len = 9;
                                        break;

                                    case 1:
                                        pDescr = (uint8_t *)(&MyCfgDescr[43]);
                                        len = 9;
                                        break;

                                    default:
                                        /* ��֧�ֵ��ַ��������� */
                                        errflag = 0xff;
                                        break;
                                }
                                break;

                            case USB_DESCR_TYP_REPORT:
                            {
                                if(((pSetupReqPak->wIndex) & 0xff) == 0) //�ӿ�0����������
                                {
                                    pDescr = KeyRepDesc; //����׼���ϴ�
                                    len = sizeof(KeyRepDesc);
                                }
                                else if(((pSetupReqPak->wIndex) & 0xff) == 1) //�ӿ�1����������
                                {
                                    pDescr = MouseRepDesc; //����׼���ϴ�
                                    len = sizeof(MouseRepDesc);
                                    Ready = 1; //����и���ӿڣ��ñ�׼λӦ�������һ���ӿ�������ɺ���Ч
                                }
                                else
                                    len = 0xff; //������ֻ��2���ӿڣ���仰����������ִ��
                            }
                            break;

                            case USB_DESCR_TYP_STRING:
                            {
                                switch((pSetupReqPak->wValue) & 0xff)
                                {
                                    case 1:
                                        pDescr = MyManuInfo;
                                        len = MyManuInfo[0];
                                        break;
                                    case 2:
                                        pDescr = MyProdInfo;
                                        len = MyProdInfo[0];
                                        break;
                                    case 0:
                                        pDescr = MyLangDescr;
                                        len = MyLangDescr[0];
                                        break;
                                    default:
                                        errflag = 0xFF; // ��֧�ֵ��ַ���������
                                        break;
                                }
                            }
                            break;

                            case 0x06:
                                pDescr = (uint8_t *)(&My_QueDescr[0]);
                                len = sizeof(My_QueDescr);
                                break;

                            case 0x07:
                                memcpy(&USB_FS_OSC_DESC[2], &MyCfgDescr[2], sizeof(MyCfgDescr) - 2);
                                pDescr = (uint8_t *)(&USB_FS_OSC_DESC[0]);
                                len = sizeof(USB_FS_OSC_DESC);
                                break;

                            default:
                                errflag = 0xff;
                                break;
                        }
                        if(SetupReqLen > len)
                            SetupReqLen = len; //ʵ�����ϴ��ܳ���
                        len = (SetupReqLen >= DevEP0SIZE) ? DevEP0SIZE : SetupReqLen;
                        memcpy(pEP0_DataBuf, pDescr, len);
                        pDescr += len;
                    }
                    break;

                    case USB_SET_ADDRESS:
                        SetupReqLen = (pSetupReqPak->wValue) & 0xff;
                        break;

                    case USB_GET_CONFIGURATION:
                        pEP0_DataBuf[0] = DevConfig;
                        if(SetupReqLen > 1)
                            SetupReqLen = 1;
                        break;

                    case USB_SET_CONFIGURATION:
                        DevConfig = (pSetupReqPak->wValue) & 0xff;
                        break;

                    case USB_CLEAR_FEATURE:
                    {
                        if((pSetupReqPak->bRequestType & USB_REQ_RECIP_MASK) == USB_REQ_RECIP_ENDP) // �˵�
                        {
                            switch((pSetupReqPak->wIndex) & 0xff)
                            {
                                case 0x83:
                                    R8_UEP3_CTRL = (R8_UEP3_CTRL & ~(RB_UEP_T_TOG | MASK_UEP_T_RES)) | UEP_T_RES_NAK;
                                    break;
                                case 0x03:
                                    R8_UEP3_CTRL = (R8_UEP3_CTRL & ~(RB_UEP_R_TOG | MASK_UEP_R_RES)) | UEP_R_RES_ACK;
                                    break;
                                case 0x82:
                                    R8_UEP2_CTRL = (R8_UEP2_CTRL & ~(RB_UEP_T_TOG | MASK_UEP_T_RES)) | UEP_T_RES_NAK;
                                    break;
                                case 0x02:
                                    R8_UEP2_CTRL = (R8_UEP2_CTRL & ~(RB_UEP_R_TOG | MASK_UEP_R_RES)) | UEP_R_RES_ACK;
                                    break;
                                case 0x81:
                                    R8_UEP1_CTRL = (R8_UEP1_CTRL & ~(RB_UEP_T_TOG | MASK_UEP_T_RES)) | UEP_T_RES_NAK;
                                    break;
                                case 0x01:
                                    R8_UEP1_CTRL = (R8_UEP1_CTRL & ~(RB_UEP_R_TOG | MASK_UEP_R_RES)) | UEP_R_RES_ACK;
                                    break;
                                default:
                                    errflag = 0xFF; // ��֧�ֵĶ˵�
                                    break;
                            }
                        }
                        else if((pSetupReqPak->bRequestType & USB_REQ_RECIP_MASK) == USB_REQ_RECIP_DEVICE)
                        {
                            if(pSetupReqPak->wValue == 1)
                            {
                                USB_SleepStatus &= ~0x01;
                            }
                        }
                        else
                        {
                            errflag = 0xFF;
                        }
                    }
                    break;

                    case USB_SET_FEATURE:
                        if((pSetupReqPak->bRequestType & USB_REQ_RECIP_MASK) == USB_REQ_RECIP_ENDP)
                        {
                            /* �˵� */
                            switch(pSetupReqPak->wIndex)
                            {
                                case 0x83:
                                    R8_UEP3_CTRL = (R8_UEP3_CTRL & ~(RB_UEP_T_TOG | MASK_UEP_T_RES)) | UEP_T_RES_STALL;
                                    break;
                                case 0x03:
                                    R8_UEP3_CTRL = (R8_UEP3_CTRL & ~(RB_UEP_R_TOG | MASK_UEP_R_RES)) | UEP_R_RES_STALL;
                                    break;
                                case 0x82:
                                    R8_UEP2_CTRL = (R8_UEP2_CTRL & ~(RB_UEP_T_TOG | MASK_UEP_T_RES)) | UEP_T_RES_STALL;
                                    break;
                                case 0x02:
                                    R8_UEP2_CTRL = (R8_UEP2_CTRL & ~(RB_UEP_R_TOG | MASK_UEP_R_RES)) | UEP_R_RES_STALL;
                                    break;
                                case 0x81:
                                    R8_UEP1_CTRL = (R8_UEP1_CTRL & ~(RB_UEP_T_TOG | MASK_UEP_T_RES)) | UEP_T_RES_STALL;
                                    break;
                                case 0x01:
                                    R8_UEP1_CTRL = (R8_UEP1_CTRL & ~(RB_UEP_R_TOG | MASK_UEP_R_RES)) | UEP_R_RES_STALL;
                                    break;
                                default:
                                    /* ��֧�ֵĶ˵� */
                                    errflag = 0xFF; // ��֧�ֵĶ˵�
                                    break;
                            }
                        }
                        else if((pSetupReqPak->bRequestType & USB_REQ_RECIP_MASK) == USB_REQ_RECIP_DEVICE)
                        {
                            if(pSetupReqPak->wValue == 1)
                            {
                                /* ����˯�� */
                                USB_SleepStatus |= 0x01;
                            }
                        }
                        else
                        {
                            errflag = 0xFF;
                        }
                        break;

                    case USB_GET_INTERFACE:
                        pEP0_DataBuf[0] = 0x00;
                        if(SetupReqLen > 1)
                            SetupReqLen = 1;
                        break;

                    case USB_SET_INTERFACE:
                        break;

                    case USB_GET_STATUS:
                        if((pSetupReqPak->bRequestType & USB_REQ_RECIP_MASK) == USB_REQ_RECIP_ENDP)
                        {
                            /* �˵� */
                            pEP0_DataBuf[0] = 0x00;
                            switch(pSetupReqPak->wIndex)
                            {
                                case 0x83:
                                    if((R8_UEP3_CTRL & (RB_UEP_T_TOG | MASK_UEP_T_RES)) == UEP_T_RES_STALL)
                                    {
                                        pEP0_DataBuf[0] = 0x01;
                                    }
                                    break;

                                case 0x03:
                                    if((R8_UEP3_CTRL & (RB_UEP_R_TOG | MASK_UEP_R_RES)) == UEP_R_RES_STALL)
                                    {
                                        pEP0_DataBuf[0] = 0x01;
                                    }
                                    break;

                                case 0x82:
                                    if((R8_UEP2_CTRL & (RB_UEP_T_TOG | MASK_UEP_T_RES)) == UEP_T_RES_STALL)
                                    {
                                        pEP0_DataBuf[0] = 0x01;
                                    }
                                    break;

                                case 0x02:
                                    if((R8_UEP2_CTRL & (RB_UEP_R_TOG | MASK_UEP_R_RES)) == UEP_R_RES_STALL)
                                    {
                                        pEP0_DataBuf[0] = 0x01;
                                    }
                                    break;

                                case 0x81:
                                    if((R8_UEP1_CTRL & (RB_UEP_T_TOG | MASK_UEP_T_RES)) == UEP_T_RES_STALL)
                                    {
                                        pEP0_DataBuf[0] = 0x01;
                                    }
                                    break;

                                case 0x01:
                                    if((R8_UEP1_CTRL & (RB_UEP_R_TOG | MASK_UEP_R_RES)) == UEP_R_RES_STALL)
                                    {
                                        pEP0_DataBuf[0] = 0x01;
                                    }
                                    break;
                            }
                        }
                        else if((pSetupReqPak->bRequestType & USB_REQ_RECIP_MASK) == USB_REQ_RECIP_DEVICE)
                        {
                            pEP0_DataBuf[0] = 0x00;
                            if(USB_SleepStatus)
                            {
                                pEP0_DataBuf[0] = 0x02;
                            }
                            else
                            {
                                pEP0_DataBuf[0] = 0x00;
                            }
                        }
                        pEP0_DataBuf[1] = 0;
                        if(SetupReqLen >= 2)
                        {
                            SetupReqLen = 2;
                        }
                        break;

                    default:
                        errflag = 0xff;
                        break;
                }
            }
            if(errflag == 0xff) // �����֧��
            {
                //                  SetupReqCode = 0xFF;
                R8_UEP0_CTRL = RB_UEP_R_TOG | RB_UEP_T_TOG | UEP_R_RES_STALL | UEP_T_RES_STALL; // STALL
            }
            else
            {
                if(chtype & 0x80) // �ϴ�
                {
                    len = (SetupReqLen > DevEP0SIZE) ? DevEP0SIZE : SetupReqLen;
                    SetupReqLen -= len;
                }
                else
                    len = 0; // �´�
                R8_UEP0_T_LEN = len;
                R8_UEP0_CTRL = RB_UEP_R_TOG | RB_UEP_T_TOG | UEP_R_RES_ACK | UEP_T_RES_ACK; // Ĭ�����ݰ���DATA1
            }

            R8_USB_INT_FG = RB_UIF_TRANSFER;
        }
    }
    else if(intflag & RB_UIF_BUS_RST)
    {
        R8_USB_DEV_AD = 0;
        R8_UEP0_CTRL = UEP_R_RES_ACK | UEP_T_RES_NAK;
        R8_UEP1_CTRL = UEP_R_RES_ACK | UEP_T_RES_NAK;
        R8_UEP2_CTRL = UEP_R_RES_ACK | UEP_T_RES_NAK;
        R8_UEP3_CTRL = UEP_R_RES_ACK | UEP_T_RES_NAK;
        R8_USB_INT_FG = RB_UIF_BUS_RST;
    }
    else if(intflag & RB_UIF_SUSPEND)
    {
        if(R8_USB_MIS_ST & RB_UMS_SUSPEND)
        {
            ;
        } // ����
        else
        {
            ;
        } // ����
        R8_USB_INT_FG = RB_UIF_SUSPEND;
    }
    else
    {
        R8_USB_INT_FG = intflag;
    }
}

/*********************************************************************
 * @fn      DevHIDMouseReport
 *
 * @brief   �ϱ��������
 *
 * @return  none
 */
void DevHIDMouseReport(uint8_t mouse)
{
    HIDMouse[0] = mouse;
    memcpy(pEP2_IN_DataBuf, HIDMouse, sizeof(HIDMouse));
    DevEP2_IN_Deal(sizeof(HIDMouse));
}

/*********************************************************************
 * @fn      DevHIDKeyReport
 *
 * @brief   �ϱ���������
 *
 * @return  none
 */
void DevHIDKeyReport(uint8_t key)
{
    HIDKey[2] = key;
    memcpy(pEP1_IN_DataBuf, HIDKey, sizeof(HIDKey));
    DevEP1_IN_Deal(sizeof(HIDKey));
}


void DevASCIIKeyReport( uint8_t c ){
    HIDKey[2] = asciimap[c];
    memcpy(pEP1_IN_DataBuf, HIDKey, sizeof(HIDKey));
    DevEP1_IN_Deal(sizeof(HIDKey));
}


/*********************************************************************
 * @fn      DevWakeup
 *
 * @brief   �豸ģʽ��������
 *
 * @return  none
 */
void DevWakeup(void)
{
    R16_PIN_ANALOG_IE &= ~(RB_PIN_USB_DP_PU);
    R8_UDEV_CTRL |= RB_UD_LOW_SPEED;
    mDelaymS(2);
    R8_UDEV_CTRL &= ~RB_UD_LOW_SPEED;
    R16_PIN_ANALOG_IE |= RB_PIN_USB_DP_PU;
}

/*********************************************************************
 * @fn      DebugInit
 *
 * @brief   ���Գ�ʼ��
 *
 * @return  none
 */
void DebugInit(void)
{
    GPIOA_SetBits(GPIO_Pin_9);
    GPIOA_ModeCfg(GPIO_Pin_8, GPIO_ModeIN_PU);
    GPIOA_ModeCfg(GPIO_Pin_9, GPIO_ModeOut_PP_5mA);
    UART1_DefInit();
}

/*********************************************************************
 * @fn      main
 *
 * @brief   ������
 *
 * @return  none
 */
int usb_main()
{
    SetSysClock(CLK_SOURCE_PLL_60MHz);

    DebugInit();
    PRINT("start\n");

    pEP0_RAM_Addr = EP0_Databuf;
    pEP1_RAM_Addr = EP1_Databuf;
    pEP2_RAM_Addr = EP2_Databuf;
    pEP3_RAM_Addr = EP3_Databuf;

    USB_DeviceInit();

    PFIC_EnableIRQ(USB_IRQn);

    while(1)
    {
//        mDelaymS(1000);
//        //������
//        DevHIDMouseReport(0x01);
//        mDelaymS(100);
//        DevHIDMouseReport(0x00);
//        mDelaymS(200);

        //���̰�����wch��
        mDelaymS(100);
        DevHIDKeyReport(0x1A);
        mDelaymS(20);
        DevHIDKeyReport(0x00);
        mDelaymS(20);
        DevHIDKeyReport(0x06);
        mDelaymS(20);
        DevHIDKeyReport(0x00);
        mDelaymS(20);
        DevHIDKeyReport(0x0B);
        mDelaymS(20);
        DevHIDKeyReport(0x00);
    }
}


void USB_INIT(void){
    pEP0_RAM_Addr = EP0_Databuf;
    pEP1_RAM_Addr = EP1_Databuf;
    pEP2_RAM_Addr = EP2_Databuf;
    pEP3_RAM_Addr = EP3_Databuf;

    USB_DeviceInit();
    PFIC_EnableIRQ(USB_IRQn);
}

/*********************************************************************
 * @fn      DevEP1_OUT_Deal
 *
 * @brief   �˵�1���ݴ���
 *
 * @return  none
 */
void DevEP1_OUT_Deal(uint8_t l)
{ /* �û����Զ��� */
    uint8_t i;

    for(i = 0; i < l; i++)
    {
        pEP1_IN_DataBuf[i] = ~pEP1_OUT_DataBuf[i];
    }
    DevEP1_IN_Deal(l);
}

/*********************************************************************
 * @fn      DevEP2_OUT_Deal
 *
 * @brief   �˵�2���ݴ���
 *
 * @return  none
 */
void DevEP2_OUT_Deal(uint8_t l)
{ /* �û����Զ��� */
    uint8_t i;

    for(i = 0; i < l; i++)
    {
        pEP2_IN_DataBuf[i] = ~pEP2_OUT_DataBuf[i];
    }
    DevEP2_IN_Deal(l);
}

/*********************************************************************
 * @fn      DevEP3_OUT_Deal
 *
 * @brief   �˵�3���ݴ���
 *
 * @return  none
 */
void DevEP3_OUT_Deal(uint8_t l)
{ /* �û����Զ��� */
    uint8_t i;

    for(i = 0; i < l; i++)
    {
        pEP3_IN_DataBuf[i] = ~pEP3_OUT_DataBuf[i];
    }
    DevEP3_IN_Deal(l);
}

/*********************************************************************
 * @fn      DevEP4_OUT_Deal
 *
 * @brief   �˵�4���ݴ���
 *
 * @return  none
 */
void DevEP4_OUT_Deal(uint8_t l)
{ /* �û����Զ��� */
    uint8_t i;

    for(i = 0; i < l; i++)
    {
        pEP4_IN_DataBuf[i] = ~pEP4_OUT_DataBuf[i];
    }
    DevEP4_IN_Deal(l);
}

/*********************************************************************
 * @fn      USB_IRQHandler
 *
 * @brief   USB�жϺ���
 *
 * @return  none
 */
__INTERRUPT
__HIGH_CODE
void USB_IRQHandler(void) /* USB�жϷ������,ʹ�üĴ�����1 */
{
    USB_DevTransProcess();
}