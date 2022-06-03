#pragma once

#include "wx/wx.h"
#include "cMain.h"

class cApp : public wxApp
{
public:
	cApp();
	~cApp();

private:
	cMain* mainWindow = nullptr;

public:
	virtual bool OnInit();
};

