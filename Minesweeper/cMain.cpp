#include "cMain.h"

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "Minesweeper", wxPoint(400, 150), wxSize(1000,800))
{
	buttons = new wxButton * [gridWidth * gridHeight];
	wxGridSizer* grid = new wxGridSizer(gridWidth, gridHeight, 0, 0);

	mines = new int[gridWidth * gridHeight];

	wxFont font(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false);

	for (int x = 0; x < gridWidth; x++)
	{
		for (int y = 0; y < gridHeight; y++)
		{
			buttons[y * gridWidth + x] = new wxButton(this, 10000 + (y * gridWidth + x));
			buttons[y * gridWidth + x]->SetFont(font);
			grid->Add(buttons[y * gridWidth + x], 1, wxEXPAND | wxALL);

			buttons[y * gridWidth + x]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::OnButtonClicked, this);
			mines[y * gridWidth + x] = 0;
		}
	}

	this->SetSizer(grid);
	grid->Layout();
}

cMain::~cMain()
{
	delete[] buttons;
}

void cMain::OnButtonClicked(wxCommandEvent& evt)
{
	int x = (evt.GetId() - 10000) % gridWidth;
	int y = (evt.GetId() - 10000) / gridHeight;

	if (firstClick)
	{
		int mineAmount = 30;

		while (mineAmount)
		{
			int rx = rand() % gridWidth;
			int ry = rand() % gridHeight;

			if (mines[ry * gridWidth + rx] == 0 && rx != x && ry != 0)
			{
				mines[ry * gridWidth + rx] = -1;
				mineAmount--;
			}
		}
		firstClick = false;
	}
	buttons[y * gridWidth + x]->Enable(false);

	if (mines[y * gridWidth + x] == -1)
	{
		wxMessageBox("You touched a mine! GAME OVER!:(");

		firstClick = true;
		for (int x = 0; x < gridWidth; x++)
		{
			for (int y = 0; y < gridHeight; y++)
			{
				mines[y * gridWidth + x] = 0;
				buttons[y * gridWidth + x]->SetLabel("");
				buttons[y * gridWidth + x]->Enable(true);
			}
		}
	}
	else
	{
		int neighbouringMines = 0;
		for (int i = -1; i < 2; i++)
		{
			for (int j = -1; j < 2; j++)
			{
				if (x + i >= 0 && x + i < gridWidth && y + j >= 0 && y + j < gridHeight)
				{
					if (mines[(y + j) * gridWidth + (x + i)] == -1)
					{
						neighbouringMines++;
					}
				}
			}
		}

		if (neighbouringMines > 0)
		{
			buttons[y * gridWidth + x]->SetLabel(std::to_string(neighbouringMines));
		}
	}

	evt.Skip();
}
