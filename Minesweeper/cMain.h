#pragma once

#include "wx/wx.h"

class cMain : public wxFrame
{
public:
	cMain();
	~cMain();

public:
	int gridWidth = 10;
	int gridHeight = 10;
	wxButton** buttons;

	int* mines = nullptr;
	bool firstClick = true;

	void OnButtonClicked(wxCommandEvent &evt);
};

