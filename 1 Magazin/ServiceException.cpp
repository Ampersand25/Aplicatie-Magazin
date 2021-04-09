#include "ServiceException.h"

const string& ServiceException::getMessage() const noexcept
{
	return msg; // return this->msg;
}