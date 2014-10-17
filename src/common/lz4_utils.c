
#if defined(__cplusplus)
extern "C" {
#endif
#include <stdlib.h>   /* malloc, calloc, free */
#include <string.h>
#include "../config/xa_patch.h"
#include "../common/lz4_utils.h"

size_t CALC_MAX_OUT_LEN(int compresserId,size_t in_len)
{
  switch(compresserId)
  {
    case PACKER_LZ4:
    default:
      return LZ4_compressBound(in_len)+ sizeof(lz4_header_t);
  };
}

//----------------------------------------------------------------//
/**	@name	lzoDecode
 @text	If a string is provided, decodes it as a lzo compressed string.  Otherwise, decodes the current data stored in this object as a lzo compressed sequence of bytes.

 @opt	MOAIDataBuffer self
 @opt	string data				The string data to decode.  You must either provide either a MOAIDataBuffer (via a :lzoDecode type call) or string data (via a .lzoDecode type call), but not both.
 @out	string output			If passed a string, returns either a string or nil depending on whether it could be decoded.  Otherwise the decoding occurs inline on the existing data buffer in this object, and nil is returned.
 */

cc8* Lz4Decode(cc8* inbuffer,size_t in_len,size_t* out_len)
{
	int packerId = PACKER_LZ4;
	cc8* outBuffer = NULL;
	int r;
	int retvalue = 0;
	size_t new_len;
	lz4_header_t* header = (lz4_header_t*)inbuffer;
	if ( in_len<sizeof(lz4_header_t) ) return NULL;
	if (strcmp((char*)(header->sign),LZ4HEADERSIGN)==0)
		{
			packerId = PACKER_LZ4;
		}
	else
	{
		return NULL;
	};

	outBuffer = (cc8*)calloc(header->originalSize,1);

	switch (packerId)
	{
		case PACKER_LZ4:
		default:
			{

			r = LZ4_decompress_fast((char*)(inbuffer+sizeof(lz4_header_t)),(char*)outBuffer,header->originalSize);
			if (r>0)
				{
				*out_len = header->originalSize;
				return outBuffer;
				}
			}
			break;
	}

	free((void*)outBuffer);
	return NULL;
}

cc8* Lz4Encode(cc8* inbuffer,size_t in_len,size_t* out_len)
{
	int r;
	size_t new_len;
	cc8* outBuffer = NULL;
	lz4_header_t* header = NULL;
	outBuffer = (cc8*)calloc(CALC_MAX_OUT_LEN(PACKER_LZ4,in_len),1);
	header = (lz4_header_t*)outBuffer;
	strcpy((char*)(&(header->sign)),LZ4HEADERSIGN);


	r = LZ4_compress((char*)inbuffer,(char*)(outBuffer+sizeof(lz4_header_t)),(size_t)in_len);
	if (r >0 )
	{
		new_len = r;
		*out_len = new_len+sizeof(lz4_header_t);
		header->originalSize = in_len;
		header->compressedSize = new_len;
		return outBuffer;
	}
	free((void*)outBuffer);
	return NULL;
}
#ifdef __cplusplus
}
#endif
