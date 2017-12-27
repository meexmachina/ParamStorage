#ifndef __PARAM_STORAGE_H__
#define __PARAM_STORAGE_H__

#include <vector>
#include "param.h"

using namespace std;

template <size_t MaxNumParams, uint32_t Offset>
class ParamStorage
{
private:
	static ParamBase* vec[MaxNumParams];
	static size_t numParams;
public:
	static void AddParam(ParamBase *p)
	{
		if (numParams >= MaxNumParams)
		{
			// Error
			return;
		}
		//cout << "Added " << p << " to storage" << endl;
		vec[numParams++] = p;
		p->setParamIndex((uint8_t)(numParams - 1));
	}

	static void print()
	{
		int accum = Offset;
		cout << "Num of elements: " << numParams << endl;
		for (size_t i = 0; i < numParams; i++)
		{
			cout << "Offset: " << accum << "  Value: ";
			vec[i]->print();
			accum += vec[i]->size();
		}
	}
};

template <size_t MaxNumParams, uint32_t Offset>
ParamBase* ParamStorage<MaxNumParams, Offset>::vec[MaxNumParams];
template <size_t MaxNumParams, uint32_t Offset>
size_t ParamStorage<MaxNumParams, Offset>::numParams = 0;


template <size_t MaxNumParams, uint32_t Offset>
class ParamStorageFlash : public ParamStorage<MaxNumParams, Offset>
{
public:
	static void updateParam(uint8_t param_index, uint8_t* buffer, uint8_t param_size)
	{
		// read from flash into buffer
	}

	static void commitParam(uint8_t param_index, uint8_t* buffer, uint8_t param_size)
	{
		// write into flash the contents of buffer
	}
};

template <size_t MaxNumParams, uint32_t Offset>
class ParamStorageEeprom : public ParamStorage<MaxNumParams, Offset>
{
public:
	static void updateParam(uint8_t param_index, uint8_t* buffer, uint8_t param_size)
	{
		// read from flash into buffer
	}

	static void commitParam(uint8_t param_index, uint8_t* buffer, uint8_t param_size)
	{
		// write into flash the contents of buffer
	}
};

#endif //__PARAM_STORAGE_H__