#ifndef __MINILZO_UTILS_H__
#define __MINILZO_UTILS_H__
#ifdef __cplusplus
extern "C" {
#endif
#include "../common/cbasetypes.h"
#include "../config/xa_patch.h"
#include "../common/malloc.h"
#include "stdio.h"
#include <lz4.h>

#define cc8 const char

#define LZ4HEADERSIGN "LZ4\0"
typedef struct {
  unsigned char sign[4];
  uint32  originalSize;
  uint32  compressedSize;
}
lz4_header_t;

#define PACKER_LZ4 1
size_t CALC_MAX_OUT_LEN(int compresserId,size_t in_len);
cc8* Lz4Decode(cc8* inbuffer,size_t in_len,size_t* out_len);
cc8* Lz4Encode(cc8* inbuffer,size_t in_len,size_t* out_len);


#ifdef __cplusplus
}
#endif
#endif // __MINILZO_UTILS_H__
