//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <AppEvnts.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
#include <vector>

//Parametry gry:
#define MIN_WIDTH 5
#define MIN_HEIGHT 5
#define MAX_WIDTH 20
#define MAX_HEIGHT 20

class Game
{
        private:
        int state; // 0 - gra, 1 - wygrana, 2 - przegrana
        int flags_left; // pozostale flagi do uzycia
        int bombs_left; // pozostale bomby do odkrycia
        std::vector <std::vector<int> > map; // tablica z oznaczeniami pól: 0 - puste, -1 - bomba, kolejno cyfry ... 1=1, 2=2 itd.
        std::vector <std::vector<TSpeedButton*> > wsk_map; // tablica z wskaznikami na speedbuttony, pozycja w tablicy odpowiada pozycji na planszy
        std::vector <std::vector<TPanel*> > panels; // tablica z wskaznikami na panel
        std::vector <std::vector<bool> > is_flagged; // tablica typu logicznego, oznacza czy pole jest oflagowane
        std::vector <std::vector<bool> > is_discovered; // tablica typu logicznego, oznacza czy pole jest odkryte
        int width; // aktualna szerokosc
        int height; // aktualna wysokosc
        int new_width; // nowa szerokosc, ustalona przez form2, przepisuje do glownego pola po restarcie
        int new_height; // nowa wysokosc
        int new_bombs; // nowe bomby
        bool clicked; // czy jakiekolwiek pole zostalo juz klikniete ?
        int time; // czas gry

        void buildMap(int dodged_x, int dodged_y); // rozmiesc bomby i ponumeruj plansze
        void buildButtons(); // budowanie przycisków na dwuwymiarowej tablicy wskaznikow
        void updateFlagsBar(); // aktualizuj pasek na dole

        public:
        Game(); // konstruktor
        bool getButtonPos(TSpeedButton* button, int &x, int &y); // znajdz pozycje przyciska, zwroc x,y w tablicy i informacje czy jest blad znalezienia
        void init(); // inicjacja gry (tylko przy starcie programu !)
        void putFlag(TSpeedButton* button); // polozenie flagi przez usera
        void removeFlag(TSpeedButton* button); // usuniecie flagi przez usera
        void regularClick(TSpeedButton* button, bool quickdiscovery); // obsluga zwyklego klikniecia w pole, quickdiscovery - okresla czy wykonywane jest szybkie odkrywanie
        bool doesPlayerWins(); // czy gracz wygral ?
        void failGame(); // przegrana
        void winGame(); // wygrana
        void discoveringMap(TSpeedButton* button); // odkrywanie planszy po kliknieciu w puste pole (bez cyfry lub bomby)
        void restartGame(); // restart gry - alias dla inicjalizacji
        TColor generateColor(int x, int y); // generuje kolor dla cyfry
        bool isQuickDiscovery(TSpeedButton* button); // czy wykonac szybkie odkrywanie ?
        void quickDiscovery(TSpeedButton* button); // szybkie odkrywanie

        bool isButtonFlagged(TSpeedButton* button); // czy przycisk jest oflagowany ?
        void setWidth(int width); // ustaw szerokosc
        void setHeight(int height); // ustaw wysokosc
        void setBombs(int bombs); // ustaw bomby
        void setTime(int time); // ustaw czas

        int getWidth(); // pobierz szerokosc
        int getHeight(); // pobierz wysokosc
        int getTime(); // pobierz czas
        int getMapByXY(int x, int y); // pobierz wartosc przycisku
        bool isClicked(); // czy wystapilo juz jakiekolwiek klikniecie ?
};

class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TMainMenu *MainMenu1;
        TMenuItem *Gra1;
        TMenuItem *Nowagra1;
        TMenuItem *Wyj1;
        TMenuItem *Informacje1;
        TMenuItem *Wyjdz1;
        TMenuItem *Instrukcjagry1;
        TMenuItem *OProjekcie1;
        TStatusBar *StatusBar1;
        TTimer *Timer1;
        void __fastcall ButtonClicked(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall Nowagra1Click(TObject *Sender);
        void __fastcall Wyjdz1Click(TObject *Sender);
        void __fastcall Wyj1Click(TObject *Sender);
        void __fastcall MouseReleasedOnButton(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall OProjekcie1Click(TObject *Sender);
        void __fastcall Instrukcjagry1Click(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
