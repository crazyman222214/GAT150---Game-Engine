#include "Transform.h"

void Transform::Read(const json_t& value)
{
	READ_DATA(value, position);
	READ_DATA(value, rotation);
	READ_DATA(value, scale);
}

void Transform::Write(json_t& value)
{
	WRITE_DATA(value, position);
	WRITE_DATA(value, rotation);
	WRITE_DATA(value, scale);
}
