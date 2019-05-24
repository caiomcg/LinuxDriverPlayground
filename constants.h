#ifndef  CONSTANTS_H
#define  CONSTANTS_H

// Name of the driver
#define MODULE_NAME "ldp"

#define LDP_USB_VENDOR  0x0d8c
#define LDP_USB_PRODUCT 0x1314

/*
* S means "Set" through a ptr,
* T means "Tell" directly with the argument value
* G means "Get": reply by setting through a pointer
* Q means "Query": response is on the return value
* X means "eXchange": switch G and S atomically
* H means "sHift": switch T and Q atomically
*/
#define LDP_MAGIC 0xE0

#define LDP_IOCRESET     _IO(LDP_MAGIC,  0x00)
#define LDP_IOGVERSION   _IOR(LDP_MAGIC, 0x01, int)
#define LDP_IOGDEPTH     _IOR(LDP_MAGIC, 0x03, int)
#define LDP_IOGRATE      _IOR(LDP_MAGIC, 0x04, int)
#define LDP_IOGCHANNELS  _IOR(LDP_MAGIC, 0x05, int)
#define LDP_IOSDEPTH     _IOW(LDP_MAGIC, 0x06, int)
#define LDP_IOSRATE      _IOW(LDP_MAGIC, 0x07, int)
#define LDP_IOSCHANNELS  _IOW(LDP_MAGIC, 0x08, int)
#define LDP_IOC_MAXNR    0x0E

#endif
