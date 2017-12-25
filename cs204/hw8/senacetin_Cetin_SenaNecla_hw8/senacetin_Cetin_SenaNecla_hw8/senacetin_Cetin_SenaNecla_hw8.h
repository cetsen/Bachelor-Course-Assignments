
// senacetin_Cetin_SenaNecla_hw8.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// Csenacetin_Cetin_SenaNecla_hw8App:
// See senacetin_Cetin_SenaNecla_hw8.cpp for the implementation of this class
//

class Csenacetin_Cetin_SenaNecla_hw8App : public CWinApp
{
public:
	Csenacetin_Cetin_SenaNecla_hw8App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern Csenacetin_Cetin_SenaNecla_hw8App theApp;