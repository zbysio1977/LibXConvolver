#pragma once

/*	
 *		Copyright (C) 2014 Achim Turan, Achim.Turan@o2online.de
 *		https://github.com/AchimTuran/LibXConvolver
 *
 *	This file is part of LibXConvolver
 *
 *	LibXConvolver is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	LibXConvolver is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with LibXConvolver.  If not, see <http://www.gnu.org/licenses/>.
 *
 */



#include "LXC_CException.h"

#include <iostream>
#include <string>

#if defined(TARGET_WINDOWS)
	#include "../../LibXConvolverUtils/LXC_System/windows/LXC_WindowsDefinitions.h"
#endif

class LXC_CExceptionCout : public LXC_CException
{
public:
	// Konstruktor ohne Modulename
	LXC_CExceptionCout(std::string strError, std::string strFilename, std::string strFunction, int iLine);
	// Konstruktor mit Modulname
	LXC_CExceptionCout(std::string strError, std::string strErrorModule, std::string strFilename, std::string strFunction, int iLine);
	~LXC_CExceptionCout(void);

	// virtuelle Funktion um Fehlermeldung über cout anzuzeigen
    virtual void showError();
};

// Makros zum werfen einer Fehlermeldung
#define LXC_EXCEPTION_COUT_HANDLER(strError)						LXC_CExceptionCout(strError, __FILE__, __func__, __LINE__)
#define LXC_EXCEPTION_COUT_HANDLER_MODULE(strError, strErrorModule)	LXC_CExceptionCout(strError, strErrorModule,  __FILE__, __func__, __LINE__)
