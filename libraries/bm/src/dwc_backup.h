#ifndef DWC_BM_BACKUP_H
#define DWC_BM_BACKUP_H

#include <nitro.h>

typedef struct DWCBMApInfo {
    u8 ispId[32];
    u8 ispPass[32];
    u8 ssid[2][32];
    u8 wep[4][16];
    u8 ip[4];
    u8 gateway[4];
    u8 dns[2][4];
    u8 netmask;
    u8 wep2[4][5];
    u8 authType;
    u8 wepMode : 2;
    u8 wepNotation : 6;
    u8 setType;
    u8 rsv[7];
    u8 state;
} DWCBMApInfo;

typedef struct DWCMemPage {
    DWCBMApInfo ap;
    u8 wifi[14];
    u16 crc;
} DWCMemPage;

typedef struct DWCMemMap {
    DWCMemPage page[4];
} DWCMemMap;

typedef struct MEMINIT {
    DWCMemMap mm;
    u8 work[256];
    MATHCRC16Table table;
} MEMINIT;

typedef struct DWCWiFiInfo {
    u64 attestedUserId;
    u64 notAttestedId;
    u16 pass;
    u16 randomHistory;
} DWCWiFiInfo;

BOOL DWCi_BM_GetApInfo(DWCMemPage *buf);
void DWCi_BM_GetWiFiInfo(DWCWiFiInfo *buf);
BOOL DWCi_BM_SetWiFiInfo(DWCWiFiInfo *info, void *work);
BOOL DWCi_BACKUPlInit(void *work);
BOOL DWCi_BACKUPlRead(DWCMemMap *mem);
BOOL DWCi_BACKUPlWritePage(DWCMemMap *data, BOOL *page, void *work);
BOOL DWCi_BACKUPlWriteAll(MEMINIT* work);
void DWCi_BACKUPlSetWiFi(u8 *wifi);
u8 DWCi_BACKUPlConvMaskCidr(u8 *mask);
void DWCi_BACKUPlConvMaskAddr(int mask, u8 *buf);
BOOL DWC_BACKUPlCheckSsid(u8 *ssid);
BOOL DWC_BACKUPlCheckIp(u8 *ip, u8 *mask);
BOOL DWC_BACKUPlCheckAddress(u8* address);
u8 *DWCi_BACKUPlConvWifiInfo(const DWCWiFiInfo *info);
void *DWCi_BACKUPlGetWifi(void);

#endif // DWC_BM_BACKUP_H