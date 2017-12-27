#ifndef __PARAM_STORAGE_RAM_H__
#define __PARAM_STORAGE_RAM_H__

#include "paramstorage.h"

template <size_t MaxNumParams, uint32_t Offset>
class ParamStorageRam : public ParamStorage<MaxNumParams, Offset>
{
public:
	static void updateParam(uint8_t param_index, uint8_t* buffer, uint8_t param_size)
	{	
	}

	static void commitParam(uint8_t param_index, uint8_t* buffer, uint8_t param_size)
	{
	}
};

#endif // __PARAM_STORAGE_RAM_H__