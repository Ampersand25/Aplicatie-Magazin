#include "RepoException.h"

const string& RepoException::getMessage() const noexcept
{
	return msg; // return this->msg;
}