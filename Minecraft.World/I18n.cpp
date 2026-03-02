#include "stdafx.h"
#include "Language.h"
#include "I18n.h"

Language *I18n::lang = Language::getInstance();
wstring I18n::get(const wstring& id, ...)
{
#ifdef __PSVITA__		// 4J - vita doesn't like having a reference type as the last parameter passed to va_start - we shouldn't need this method anyway
	return L"";
#else
	return id;
#endif
}

wstring I18n::get(const wstring& id, va_list args)
{
	return lang->getElement(id, args);
}
