#include "Font.h"
#include <iostream>


bool Font::Load(const std::string& name, int fontSize)
{
	m_ttfFont = TTF_OpenFont(name.c_str(), fontSize);
	if (m_ttfFont == nullptr)
	{
		std::cerr << "Could not load font: " << name << std::endl;
		return false;
	}

	return true;
}

bool Font::Create(std::string filename, ...)
{
	va_list args;
	va_start(args, filename);
	int fontSize = va_arg(args, int);
	va_end(args);

	return Load(filename, fontSize);
}
