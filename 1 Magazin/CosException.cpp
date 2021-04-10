#include "CosException.h"

const string& CosException::getMessage() const noexcept
{
	return msg; // return this->msg;
}