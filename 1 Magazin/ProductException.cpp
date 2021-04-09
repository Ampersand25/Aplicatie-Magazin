#include "ProductException.h"

const string& ProductException::getMessage() const noexcept
{
	return msg; // return this->msg;
}