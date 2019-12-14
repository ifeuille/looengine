#include "token.h"

namespace loo
{
#if defined(DEBUG_LOOREFLECT)
const char *tokenTypeName (Token t)
{
	switch (t) {
	#define CREATE_CASE(Name) case Name: return #Name;
		FOR_ALL_TOKENS (CREATE_CASE)
	#undef CREATE_CASE
	}
	return "";
}
#endif
}