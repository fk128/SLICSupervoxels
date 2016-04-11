
// SLICSuperpixels.h : main header file for the PROJECT_NAME application
//

#pragma once



#include "resource.h"		// main symbols


// CSLICSuperpixelsApp:
// See SLICSuperpixels.cpp for the implementation of this class
//

class CSLICSuperpixelsApp : public CWinAppEx
{
public:
	CSLICSuperpixelsApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CSLICSuperpixelsApp theApp;
