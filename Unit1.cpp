//---------------------------------------------------------------------------

#include <vcl.h>
#include <ctime>
#include <cstdlib.h>
#include <vector>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

void Game::buildMap(int dodged_x, int dodged_y) // buduje mape w pamieci; na polu x,y nie moze byc bomby, dla pominiecia uzyj [-1,-1]
{
                srand(std::time(NULL));
		for (int i=0; i<this->width; i++) // czyszczenie planszy
				for (int j=0; j<this->height; j++) this->map[i][j] = 0;

		// rozmieszczanie bomb
		int tmp_bombs = this->bombs_left;
		int x,y;
		while(tmp_bombs > 0)
		{
                        x = rand()%this->width;
                        y = rand()%this->height;
                        if (x == dodged_x && y == dodged_y) continue; // nie stawiaj bomby na podanych coordach!
                        if (this->map[x][y] != -1)
                        {
                                this->map[x][y] = -1;
                                tmp_bombs--;
                        }
		}

		// numerowanie innych pól
		for (int x=0; x<this->width; x++)
		{
                        for (int y=0; y<this->height; y++)
                        {
                                if (this->map[x][y] != -1) // puste pole, sprawdzamy otoczenie
                                {
                                        int bombs = 0;  // liczymy poziomo
                                        if (x-1 >= 0 && y-1 >= 0 && this->map[x-1][y-1] == -1) bombs++;
                                        if (y-1 >= 0 && this->map[x][y-1] == -1) bombs++;
                                        if (x+1 < this->width && this->map[x+1][y-1] == -1) bombs++;
                                        if (x-1 >= 0 && this->map[x-1][y] == -1) bombs++;
                                        // srodek
                                        if (x+1 < this->width && this->map[x+1][y] == -1) bombs++;
                                        if (x-1 >= 0 && y+1 < this->height && this->map[x-1][y+1] == -1) bombs++;
                                        if (y+1 < this->width && this->map[x][y+1] == -1) bombs++;
                                        if (x+1 < this->width && y+1 < this->height && this->map[x+1][y+1] == -1) bombs++;
                                        this->map[x][y] = bombs;
                                }
                        }
		}
}

void Game::buildButtons()
{
        int mapsize = (int)map.size()-1; // rzutowanie z unsigned inta
        for (int i=0; i<mapsize; i++)
        {
                for (int j=0; j<mapsize; j++)
                {
                        if (i < this->width && j < this->height) // biorace udzial w grze
                        {
                                if (!wsk_map[i][j] || !panels[i][j]) // jesli nie istnieje to utworz
                                {
                                        panels[i][j] = new TPanel(Form1);
                                        panels[i][j]->Parent = Form1;
                                        panels[i][j]->Caption = "";
                                        panels[i][j]->Left = i*25+25;
                                        panels[i][j]->Top = j*25+25;
                                        panels[i][j]->Width = 25;
                                        panels[i][j]->Height = 25;
                                        panels[i][j]->Enabled = true;
                                        panels[i][j]->Visible = true;
                                        panels[i][j]->Color = clWhite;
                                        panels[i][j]->Font->Style = TFontStyles() << fsBold; // pogrubienie

                                        wsk_map[i][j] = new TSpeedButton(panels[i][j]);
                                        wsk_map[i][j]->Parent = panels[i][j];
                                        wsk_map[i][j]->Caption = "";
                                        wsk_map[i][j]->Left = 0;
                                        wsk_map[i][j]->Top = 0;
                                        wsk_map[i][j]->Width = 25;
                                        wsk_map[i][j]->Height = 25;
                                        wsk_map[i][j]->Enabled = true;
                                        wsk_map[i][j]->Visible = true;
                                        wsk_map[i][j]->Transparent = true;
                                        wsk_map[i][j]->Flat = true;
                                        wsk_map[i][j]->OnClick = Form1->ButtonClicked;
                                        wsk_map[i][j]->OnMouseUp = Form1->MouseReleasedOnButton;
                                }
                                else // jesli istnieje to tylko odkryj
                                {
                                        wsk_map[i][j]->Caption = "";
                                        wsk_map[i][j]->Enabled = true;
                                        wsk_map[i][j]->Visible = true;
                                        wsk_map[i][j]->Transparent = true;
                                        wsk_map[i][j]->Flat = true;

                                        panels[i][j]->Enabled = true;
                                        panels[i][j]->Visible = true;
                                        panels[i][j]->Color = clWhite;
                                        panels[i][j]->Caption = "";
                                }
                        }
                        else // nie biorace udzial w grze (nieistniejace dla usera)
                        {
                                if (wsk_map[i][j] || panels[i][j])
                                {
                                        wsk_map[i][j]->Visible = false; // jesli istnieje to ukryj
                                        panels[i][j]->Visible = false;
                                }
                        }
                }
           }
}

void Game::updateFlagsBar()
{
        Form1->StatusBar1->Panels->BeginUpdate();
        Form1->StatusBar1->Panels->Items[0]->Text = "Flagi: "+IntToStr(this->flags_left);
        Form1->StatusBar1->Panels->EndUpdate();
}

Game::Game() // konstruktor
{
        this->width = -1;
        this->height = -1;
        this->bombs_left = -1;
}

bool Game::getButtonPos(TSpeedButton* button, int &x, int &y) // znajdz pozycje przyciska, zwroc x,y w tablicy przez referencje i informacje czy istnieje przycisk ? (true/false)
{
		if (!button) return false; // czy w ogole istnieje taki przycisk ?
		for (int i=0; i<this->width; i++)
		{
				for (int j=0; j<this->height; j++)
				{
						if (button == wsk_map[i][j]) // znaleziony ! zwroc jego pozycje przez referencje
						{
								x = i;
								y = j;
								return true;
						}
				}
		}
		return false; // cos sie popsulo ...
}

void Game::init() // inicjacja gry z domyslnymi ustawieniami
{
		this->new_width = 10;
		this->new_height = 10;
		this->new_bombs = 10;
                this->width = 10;
                this->height = 10;
                this->bombs_left = 10;
                this->clicked = false;

                Form1->ClientWidth = 50+this->width*25;
                Form1->ClientHeight = 75+this->height*25;

		for (int i=0; i<MAX_WIDTH+1; i++)
		{
				this->map.push_back(std::vector<int>());
				this->wsk_map.push_back(std::vector<TSpeedButton*>());
                                this->panels.push_back(std::vector<TPanel*>());
				this->is_flagged.push_back(std::vector<bool>());
				this->is_discovered.push_back(std::vector<bool>());
				for (int j=0; j<MAX_HEIGHT+1; j++)
				{
                                        this->map[i].push_back(0);
                                        this->panels[i].push_back(NULL);
                                        panels[i][j] = new TPanel(Form1);
                                        panels[i][j]->Parent = Form1;
                                        panels[i][j]->Caption = "";
                                        panels[i][j]->Left = i*25+25;
                                        panels[i][j]->Top = j*25+25;
                                        panels[i][j]->Width = 25;
                                        panels[i][j]->Height = 25;
                                        panels[i][j]->Enabled = true;
                                        panels[i][j]->Visible = false; // tworzone wczesniej, ale nie widoczne
                                        panels[i][j]->Color = clWhite;
                                        panels[i][j]->Font->Style = TFontStyles() << fsBold;

                                        this->wsk_map[i].push_back(NULL);
                                        wsk_map[i][j] = new TSpeedButton(panels[i][j]);
                                        wsk_map[i][j]->Parent = panels[i][j];
                                        wsk_map[i][j]->Caption = "";
                                        wsk_map[i][j]->Left = 0;
                                        wsk_map[i][j]->Top = 0;
                                        wsk_map[i][j]->Width = 25;
                                        wsk_map[i][j]->Height = 25;
                                        wsk_map[i][j]->Enabled = true;
                                        wsk_map[i][j]->Visible = false; // niewidoczne
                                        wsk_map[i][j]->Transparent = true;
                                        wsk_map[i][j]->Flat = true;
                                        wsk_map[i][j]->OnClick = Form1->ButtonClicked;
                                        wsk_map[i][j]->OnMouseUp = Form1->MouseReleasedOnButton;
                                        this->is_flagged[i].push_back(false);
                                        this->is_discovered[i].push_back(false);
				}
		}
		buildMap(-1, -1);
		buildButtons();
                this->time = 0;
                Form1->StatusBar1->Panels->Items[1]->Text = "Czas: 0";
		this->state = 0;
                this->flags_left = 10;
		for (int i=0; i<this->width; i++)
		{
				for (int j=0; j<this->height; j++)
				{
						is_flagged[i][j] = false;
						is_discovered[i][j] = false;
				}
		}
}

void Game::putFlag(TSpeedButton* button)
{
		if (this->state != 0) return;
		if (flags_left > 0)
		{
				int x,y;
				if (!getButtonPos(button,x,y)) return;
				if (this->panels[x][y]->Caption != "F" && !is_flagged[x][y] && !is_discovered[x][y])
				{
                                                panels[x][y]->Caption = "F";
						flags_left--;
						is_flagged[x][y] = true; // oznacz pole
						Form1->StatusBar1->Panels->BeginUpdate();
						Form1->StatusBar1->Panels->Items[0]->Text = "Flagi: "+IntToStr(this->flags_left);
						Form1->StatusBar1->Panels->EndUpdate();
						if (doesPlayerWins()) winGame(); // czy gracz wygral ?
				}
		}
		else
		{
				Application->MessageBoxA("Wykorzystales juz wszystkie flagi!","Flagi",MB_OK | MB_ICONEXCLAMATION);
		}
}

void Game::removeFlag(TSpeedButton* button)
{
		if (this->state != 0) return;
		int x,y;
		if (!getButtonPos(button, x, y)) return;
		if (this->panels[x][y]->Caption == "F" && is_flagged[x][y] && !is_discovered[x][y])
		{
				this->panels[x][y]->Caption = "";
				is_flagged[x][y] = false;
				this->flags_left++;
				Form1->StatusBar1->Panels->BeginUpdate();
				Form1->StatusBar1->Panels->Items[0]->Text = "Flagi: "+IntToStr(this->flags_left);
				Form1->StatusBar1->Panels->EndUpdate();
		}
}

void Game::regularClick(TSpeedButton* button, bool quickdiscovery)
{
        if (this->state != 0) return;
        int x,y;
        if (!getButtonPos(button, x, y)) return; // nie ma takiego przycisku
        if (is_discovered[x][y] || is_flagged[x][y]) return; // gdy odkryty lub oflagowany to nic nie rob
        if (quickdiscovery && !this->clicked) return; // jesli nic nie jest klikniete i wlaczone jest szybkie odkrywanie
        switch (this->map[x][y])
        {
                case -1:
                {
                        if (!this->clicked) // czy bylo juz pierwsze klikniecie ?
                        {
                                while (this->map[x][y] == -1) buildMap(x,y); // jesli przy pierwszym kliknieciu znalazl bombe to przebuduj plansze
                                this->clicked = true;
                                regularClick(button,false);
                        }
                        else failGame();
                        break;
                }
                case 0:
                {
                        discoveringMap(button); // puste pole, rozpoczyna rekurencyjne odkrywanie
                        this->clicked = true;
                        if (doesPlayerWins()) winGame();
                        break;
                }
                default: // klikniecie w liczbe, odkrycie pola
                {
                        is_discovered[x][y] = true;
                        panels[x][y]->Caption = IntToStr(this->map[x][y]);
                        panels[x][y]->Font->Color = generateColor(x,y);
                        panels[x][y]->Color = TColor(0xD3D3D3);
                        this->clicked = true;
                        if (doesPlayerWins()) winGame(); // czy gracz wygral ?
                        break;
                }
        }
}

bool Game::isQuickDiscovery(TSpeedButton* button)
{
        int x,y;
        if (!getButtonPos(button, x, y)) return false; // gdy nie istnieje
        if (is_discovered[x][y])
        {
                int flags = 0; // liczymy poziomo
                if (x-1 >= 0 && y-1 >= 0 && is_flagged[x-1][y-1]) flags++;
                if (y-1 >= 0 && is_flagged[x][y-1]) flags++;
                if (x+1 < this->width && y-1 >= 0 && is_flagged[x+1][y-1]) flags++;
                if (x-1 >= 0 && is_flagged[x-1][y]) flags++;
                // srodek[x,y]
                if (x+1 < this->width && is_flagged[x+1][y]) flags++;
                if (x-1 >= 0 && y+1 < this->height && is_flagged[x-1][y+1]) flags++;
                if (y+1 < this->height && is_flagged[x][y+1]) flags++;
                if (x+1 < this->width && y+1 < this->height && is_flagged[x+1][y+1]) flags++;
                if (flags == map[x][y]) return true; // ilosc flag jest rowna cyfrze ktora nacislismy
        }
        return false;
}

void Game::quickDiscovery(TSpeedButton* button)
{
        int x,y;
        if (!getButtonPos(button, x, y)) return; // nie potrzeba sprawdzac odkrycia i oflagowania, poniewaz metoda discoveringmap juz to robi
        if (x-1 >= 0 && y-1 >= 0) regularClick(this->wsk_map[x-1][y-1],true);
        if (y-1 >= 0) regularClick(this->wsk_map[x][y-1],true);
        if (x+1 < this->width && y-1 >= 0) regularClick(this->wsk_map[x+1][y-1],true);
        if (x-1 >= 0) regularClick(this->wsk_map[x-1][y],true);
        // srodek[x,y]
        if (x+1 < this->width) regularClick(this->wsk_map[x+1][y],true);
        if (x-1 >= 0 && y+1 < this->height) regularClick(this->wsk_map[x-1][y+1],true);
        if (y+1 < this->height) regularClick(this->wsk_map[x][y+1],true);
        if (x+1 < this->width && y+1 < this->height) regularClick(this->wsk_map[x+1][y+1],true);
}

bool Game::doesPlayerWins()
{
	 int discovered = 0;
	 for (int i=0; i<this->width; i++)
	 {
		for (int j=0; j<this->height; j++)
		{
				if (this->is_discovered[i][j]) discovered++;
		}
	 }
	 if (this->width* this->height - discovered == this->bombs_left) return true; // warunek zwyciestwa -> rozmiar - odkryte == flagi
	 return false;
}

void Game::failGame()
{
        this->state = 2;
        this->clicked = false;
        for (int i=0; i<this->width; i++)
        {
                for (int j=0; j<this->height; j++)
                {
                        is_discovered[i][j] = true;
                        is_flagged[i][j] = false;
                        switch(map[i][j])
                        {
                                case -1: // bomby
                                {
                                        panels[i][j]->Caption = "X";
                                        panels[i][j]->Color = clRed;
                                        break;
                                }
                                default: // wszystko inne
                                {
                                        if (this->map[i][j] > 0)
                                        {
                                                panels[i][j]->Caption = IntToStr(map[i][j]);
                                                panels[i][j]->Color = TColor(0xD3D3D3);
                                                panels[i][j]->Font->Color = generateColor(i,j);
                                        }
                                        panels[i][j]->Color = TColor(0xD3D3D3);
                                        break;
                                }
                        }
                }
        }
        int answer = Application->MessageBoxA("Przegrales :(\nCzy chcesz powtorzyc gre ?","Przegrana",MB_YESNO | MB_ICONQUESTION);
        if (answer == 6) restartGame();
}

void Game::winGame()
{
	this->state = 1;
        this->clicked = false;
	for (int i=0; i<this->width; i++)
	{
			for (int j=0; j<this->height; j++)
			{
					is_discovered[i][j] = true; // zamrozenie wszystkich pol
					if (map[i][j] == -1)
                                        {
                                                panels[i][j]->Color = clRed;
                                                panels[i][j]->Caption = "X"; // pokazanie bomb
                                        }
			}
	}
	int answer = Application->MessageBoxA("Wygrales!\nCzy chcesz powtórzyæ grê?","Wygrana!",MB_YESNO | MB_ICONINFORMATION);
	if (answer == 6) restartGame(); // yes = 6
}

void Game::discoveringMap(TSpeedButton* button)
{
	if (this->state != 0) return;
	int x,y;
	if (!getButtonPos(button, x, y)) return; // czy przycisk istnieje ?
	if (this->is_flagged[x][y] || this->is_discovered[x][y]) return;
	if (map[x][y] > 0) // cyfry
	{
			this->panels[x][y]->Caption = IntToStr(map[x][y]);
                        this->panels[x][y]->Color = TColor(0xD3D3D3);
			is_discovered[x][y] = true;
                        this->panels[x][y]->Font->Color = generateColor(x,y);
			//wsk_map[x][y]->Enabled = false;
	}
	else if (map[x][y] == 0) // puste pola
	{
                        this->panels[x][y]->Color = TColor(0xD3D3D3);
			//wsk_map[x][y]->Enabled = false;
			this->panels[x][y]->Caption = "";
			is_discovered[x][y] = true;
			if (x-1 >= 0 && y-1 >= 0) discoveringMap(wsk_map[x-1][y-1]);
			if (y-1 >= 0) discoveringMap(wsk_map[x][y-1]);
			if (x+1 < this->width && y-1 >= 0) discoveringMap(wsk_map[x+1][y-1]);
			if (x-1 >= 0) discoveringMap(wsk_map[x-1][y]);
			if (x+1 < this->width) discoveringMap(wsk_map[x+1][y]);
			if (x-1 >= 0 && y+1 < this->height) discoveringMap(wsk_map[x-1][y+1]);
			if (y+1 < this->width) discoveringMap(wsk_map[x][y+1]);
			if (x+1 < this->width && y+1 <= this->height) discoveringMap(wsk_map[x+1][y+1]);
	}
}

void Game::restartGame()
{
        this->width = this->new_width;
        this->height = this->new_height;
        this->bombs_left = this->new_bombs;
        this->flags_left = this->new_bombs;
        this->clicked = false;

        Form1->ClientWidth = 50+this->width*25;
        Form1->ClientHeight = 75+this->height*25;
        Form1->BorderStyle = bsSingle;
        buildMap(-1, -1); // zbuduj mape domyslnie
        buildButtons();
        this->state = 0;
        this->time = 0;
        for (int i=0; i<this->width; i++)
        {
                for (int j=0; j<this->height; j++)
                {
                        is_flagged[i][j] = false;
                        is_discovered[i][j] = false;
                        this->panels[i][j]->Font->Color = TColor(0x000000);
                }
        }
        Form1->StatusBar1->Panels->BeginUpdate();
        Form1->StatusBar1->Panels->Items[0]->Text = "Flagi: "+IntToStr(this->flags_left);
        Form1->StatusBar1->Panels->Items[1]->Text = "Czas: 0";
        Form1->StatusBar1->Panels->EndUpdate();
}

bool Game::isButtonFlagged(TSpeedButton* button)
{
		int x,y;
		if (!getButtonPos(button, x, y)) return false; // upewnij sie ze pole istnieje
		if (this->is_flagged[x][y]) return true;
		return false;
}

TColor Game::generateColor(int x, int y) // generuj kolor dla odpowiedniej liczby
{
        switch(this->map[x][y])
        {
                case 1: return TColor(0x1E90FF); // dodger blue
                case 2: return TColor(0xFFD700); // gold
                case 3: return TColor(0x7CFC00); // lime green
                case 4: return TColor(0xFF4500); // orange red
                case 5: return TColor(0x9400D3); // dark violet
                case 6: return TColor(0xFAEBD7); // antique white  / midnight blue
                case 7: return TColor(0x000000); // black
                case 8: return TColor(0xDAA520); // golden rod
                case 9: return TColor(0xFF0000); // red
                default: return TColor(NULL);
        }
}
// set'ery
void Game::setWidth(int width)
{
        this->new_width = width;
}

int Game::getWidth()
{
        return this->width;
}

void Game::setHeight(int height)
{
        this->new_height = height;
}

int Game::getHeight()
{
        return this->height;
}

void Game::setBombs(int bombs)
{
        this->new_bombs = bombs;
}

void Game::setTime(int time)
{
        this->time = time;
}

// get'ery

bool Game::isClicked()
{
        return this->clicked;
}

int Game::getTime()
{
        return this->time;
}

int Game::getMapByXY(int x, int y)
{
        return this->map[x][y];
}

Game *gra = new Game(); // start gry

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
        gra->init();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ButtonClicked(TObject *Sender)
{
        TSpeedButton *btn = (TSpeedButton*) Sender;
        if (gra->isQuickDiscovery(btn)) gra->quickDiscovery(btn);
        else gra->regularClick(btn,false);
}

void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
        delete gra;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Nowagra1Click(TObject *Sender)
{
        gra->restartGame();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Wyjdz1Click(TObject *Sender)
{
        Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Wyj1Click(TObject *Sender)
{
        Form2->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::MouseReleasedOnButton(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
        TSpeedButton *btn = (TSpeedButton*) Sender;
        if (Button == mbRight) // obsluga prawego przycisku myszy
        {
                int x,y;
                if (!gra->getButtonPos(btn,x,y)) return; // czy przycisk istnieje ?
                if (gra->isButtonFlagged(btn)) gra->removeFlag(btn); // jesli pole oflagowane to zdejmij flage, w przeciwnym wypadku postaw
                else gra->putFlag(btn);
        }
}
void __fastcall TForm1::OProjekcie1Click(TObject *Sender)
{
        Application->MessageBoxA("Projekt nr 1 - Saper w VCL/C++\nWykona³ Marcin Kosmala Gr. ISI1","Informacje",MB_OK | MB_ICONINFORMATION);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Instrukcjagry1Click(TObject *Sender)
{
        Application->MessageBoxA("Gra \"Saper\"\nAby wygraæ nale¿y odkryæ wszystkie czyste pola i oflagowaæ bomby.\nCyfry oznaczaj¹ ile bomb znajduje sie wokó³ danego pola.\nNie mo¿esz przegraæ przy pierwszym klikniêciu.\nJeœli oflagujemy odpowiednia iloœæ pól wokó³ liczby to mo¿emy wykonaæ szybkie odkrywanie klikaj¹c w ni¹.\nPowodzenia!","Zasady gry",MB_OK | MB_ICONINFORMATION);
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Timer1Timer(TObject *Sender) // obsluga timera, zwiekszaj o 1 co sekunde
{
        if (gra->isClicked() && !Form2->Visible) // jesli gra sie rozpoczela (pierwsze klikniecie) i okno z ustawieniami nie jest widoczne to timer pracuje
        {
                int czas = gra->getTime();
                czas++;
                gra->setTime(czas);
                Form1->StatusBar1->Panels->BeginUpdate();
                Form1->StatusBar1->Panels->Items[1]->Text = "Czas: "+IntToStr(czas);
                Form1->StatusBar1->Panels->EndUpdate();
        }
}
//---------------------------------------------------------------------------

