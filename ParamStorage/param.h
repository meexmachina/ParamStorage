#ifndef PARAM_H_
#define PARAM_H_

#include <iostream>

#pragma pack(1)
typedef struct
{
	bool is_synced_with_storage : 1;			// is synchronized with the non-volatile memory
	bool commit_on_write : 1;					// when changing the paramater commit it immediatelly to non-volatile memory
	uint8_t param_size : 4;						// maximal param size is 16 bytes
	uint8_t reserved : 2;
} param_attr_t;

typedef enum
{
	flow_direction_ram2nv = 0,					// RAM -> Flash
	flow_direction_nv2ram = 1,					// Flash -> RAM
} flow_direction_en;
#pragma pack()

class ParamBase
{
protected:
	param_attr_t attr;
	uint8_t param_index;

public:
	ParamBase(bool commit_on_write = true)
		: param_index(0)
	{
		attr.is_synced_with_storage = false;
		attr.commit_on_write = commit_on_write;
		attr.param_size = 0;
	}
	~ParamBase() {}
	inline void setParamIndex(uint8_t ind) { param_index = ind; }
	virtual void print() = 0;
	inline uint8_t size() { return attr.param_size; }
	virtual void update(flow_direction_en dir) = 0;
};


template <class T, class StorageType>
class Param : public ParamBase
{
private:
	T value;
	
public:
	Param(T default_value, bool is_volatile = false, bool commit_on_write = true)
		: ParamBase(commit_on_write), value(default_value)
	{
		attr.param_size = sizeof(T);
		StorageType::AddParam(this);
	}

	~Param() {}

	operator T() const
	{
		if (!attr.is_synced_with_storage)
		{
			update(flow_direction_nv2ram);
		}
		return value;
	}

	virtual void print()
	{
		std::cout << this->value << endl;
	}

	T& operator=(const T& v)
	{
		if (value != v)
		{
			value = v;
			attr.is_synced_with_storage = false;
			if (attr.commit_on_write)
			{
				update(flow_direction_ram2nv);
			}
		}
		return value;
	}

	virtual void update(flow_direction_en dir)
	{
		if (attr.is_synced_with_storage) return;
		if (dir == flow_direction_ram2nv) StorageType::commitParam(param_index, (uint8_t*)(&value), attr.param_size);
		else StorageType::updateParam(param_index, (uint8_t*)(&value), attr.param_size);
		attr.is_synced_with_storage = true;
	}
};


#endif /* PARAM_H_ */
