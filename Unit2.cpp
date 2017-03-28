//---------------------------------------------------------------------------

#include <vcl.h>
#include <string>
#include <sstream>
#include <cstring>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma resource "*.dfm"
TForm2 *Form2;
extern class TForm1* Form1;
extern class Game* gra;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void updateForm2Info() // aktualizuj informacje na biezaco przy zmianie parametrow
{
        if (Form2->Edit1->Text.IsEmpty() || Form2->Edit2->Text.IsEmpty() || Form2->Edit1->Text.IsEmpty()) return; // nie reaguj gdy jakis jest pusty
        Form2->Label4->Caption = "Iloœæ pól: "+IntToStr(StrToInt(Form2->Edit1->Text)*StrToInt(Form2->Edit2->Text));
        int output = (StrToInt(Form2->Edit1->Text)*StrToInt(Form2->Edit2->Text)*0.9) - StrToInt(Form2->Edit3->Text);
        if (output < 0) output = 0;
        Form2->Label5->Caption = "Miny do wykorzystania: "+IntToStr(output);
}

void __fastcall TForm2::Button1Click(TObject *Sender) // weryfikuj formularz
{
        int width, height, bombs;
        try
        {
                width = StrToInt(Edit1->Text);
                height = StrToInt(Edit2->Text);
                bombs = StrToInt(Edit3->Text);

                AnsiString as1, as2, as3, as4;
                as1.sprintf("Szerokosc nie moze byc mniejsza niz %i !",MIN_WIDTH);
                as2.sprintf("Szerokosc nie moze byc wieksza niz %i !",MAX_WIDTH);
                as3.sprintf("Wysokosc nie moze byc mniejsza niz %i !",MIN_HEIGHT);
                as4.sprintf("Wysokosc nie moze byc wieksza niz %i !",MAX_HEIGHT);


                if (width < MIN_WIDTH)
                {
                        ShowMessage(as1);
                        return;
                }
                else if (width > MAX_WIDTH)
                {
                        ShowMessage(as2);
                        return;
                }

                if (height < MIN_HEIGHT)
                {
                        ShowMessage(as3);
                        return;
                }
                else if (height > MAX_WIDTH)
                {
                        ShowMessage(as4);
                        return;
                }

                if (((width * height * 0.9) - bombs) <= 0)
                {
                        Application->MessageBoxA("Bomby mog¹ stanowiæ co najwy¿ej 90% pola gry!","Uwaga!", MB_OK | MB_ICONEXCLAMATION);
                        return;
                }
                else if (bombs+1 <= (width * height) * 0.1)
                {
                        Application->MessageBoxA("Bomby musz¹ stanowiæ przynajmniej 10% pola gry!","Uwaga!", MB_OK | MB_ICONEXCLAMATION);
                        return;
                }

                gra->setWidth(width);
                gra->setHeight(height);
                gra->setBombs(bombs);
        }
        catch(...)
        {
                Application->MessageBoxA("Wyst¹pi³ problem z wprowadzonymi danymi!\nSprawdŸ czy poda³es dodatnie liczby.","B³¹d",MB_OK | MB_ICONERROR);
        }
}
//---------------------------------------------------------------------------



void __fastcall TForm2::FormCreate(TObject *Sender) // wpisz aktualne ustawienia do formularza
{
        Edit1->Text = IntToStr(gra->getWidth());
        Edit2->Text = IntToStr(gra->getHeight());

        updateForm2Info();
}
//---------------------------------------------------------------------------

// obsluga "spin'ow"
void __fastcall TForm2::CSpinButton1UpClick(TObject *Sender)
{
        try
        {
                int width = StrToInt(Edit1->Text);
                if (width >= MAX_WIDTH) // za du¿o
                {
                        Application->MessageBoxA("To jest maksymalny rozmiar !","Uwaga", MB_OK | MB_ICONINFORMATION);
                        return;
                }
                width++;
                Edit1->Text = IntToStr(width);
                updateForm2Info();
        }
        catch(...)
        {
                Application->MessageBoxA("Mo¿esz wpisaæ tylko liczby calkowite dodatnie !","B³ad", MB_OK | MB_ICONERROR);
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm2::CSpinButton1DownClick(TObject *Sender)
{
        try
        {
                int width = StrToInt(Edit1->Text);
                if (width <= MIN_WIDTH)
                {
                        Application->MessageBoxA("To jest minimalny rozmiar !","Uwaga", MB_OK | MB_ICONINFORMATION);
                        return;
                }
                width--;
                Edit1->Text = IntToStr(width);
                updateForm2Info();
        }
        catch(...)
        {
              Application->MessageBoxA("Mo¿esz wpisaæ tylko liczby calkowite dodatnie !","B³ad", MB_OK | MB_ICONERROR);
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm2::CSpinButton2UpClick(TObject *Sender)
{
        try
        {
                int height = StrToInt(Edit2->Text);
                if (height >= MAX_HEIGHT) // za du¿o
                {
                        Application->MessageBoxA("To jest maksymalny rozmiar !","Uwaga", MB_OK | MB_ICONINFORMATION);
                        return;
                }
                height++;
                Edit2->Text = IntToStr(height);
                updateForm2Info();
        }
        catch(...)
        {
                Application->MessageBoxA("Mo¿esz wpisaæ tylko liczby calkowite dodatnie !","B³ad", MB_OK | MB_ICONERROR);
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm2::CSpinButton2DownClick(TObject *Sender)
{
        try
        {
                int height = StrToInt(Edit2->Text);
                if (height <= MIN_HEIGHT)
                {
                        Application->MessageBoxA("To jest minimalny rozmiar !","Uwaga", MB_OK | MB_ICONINFORMATION);
                        return;
                }
                height--;
                Edit2->Text = IntToStr(height);
                updateForm2Info();
        }
        catch(...)
        {
              Application->MessageBoxA("Mo¿esz wpisaæ tylko liczby calkowite dodatnie !","B³ad", MB_OK | MB_ICONERROR);
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm2::CSpinButton3UpClick(TObject *Sender)
{
        try
        {
                int bombs = StrToInt(Edit3->Text);
                int width = StrToInt(Edit1->Text);
                int height = StrToInt(Edit2->Text);

                if (((width * height * 0.9) - bombs)-1 <= 0)
                {
                        Application->MessageBoxA("Bomby mog¹ stanowiæ co najwy¿ej 90% pola gry!","Uwaga!", MB_OK | MB_ICONEXCLAMATION);
                        return;
                }

                bombs++;
                Edit3->Text = IntToStr(bombs);
                updateForm2Info();
        }
        catch(...)
        {
             Application->MessageBoxA("Mo¿esz wpisaæ tylko liczby calkowite dodatnie !","B³ad", MB_OK | MB_ICONERROR);
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm2::CSpinButton3DownClick(TObject *Sender)
{
        try
        {
                int bombs = StrToInt(Edit3->Text);
                int width = StrToInt(Edit1->Text);
                int height = StrToInt(Edit2->Text);

                if (bombs < (width * height) * 0.1)
                {
                        Application->MessageBoxA("Bomby musz¹ stanowiæ przynajmniej 10% pola gry!","Uwaga!", MB_OK | MB_ICONEXCLAMATION);
                        return;
                }

                bombs--;
                Edit3->Text = IntToStr(bombs);
                updateForm2Info();
        }
        catch(...)
        {
             Application->MessageBoxA("Mo¿esz wpisaæ tylko liczby calkowite dodatnie !","B³ad", MB_OK | MB_ICONERROR);
        }
}
//---------------------------------------------------------------------------

// rêczna edycja pól
void __fastcall TForm2::Edit1Change(TObject *Sender)
{
        try
        {
                updateForm2Info();
        }
        catch(...)
        {
                Application->MessageBoxA("Mo¿esz wpisaæ tylko liczby calkowite dodatnie !","B³ad", MB_OK | MB_ICONERROR);
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Edit2Change(TObject *Sender)
{
        try
        {
                updateForm2Info();
        }
        catch(...)
        {
                Application->MessageBoxA("Mo¿esz wpisaæ tylko liczby calkowite dodatnie !","B³ad", MB_OK | MB_ICONERROR);
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Edit3Change(TObject *Sender)
{
        try
        {
                updateForm2Info();
        }
        catch(...)
        {
                Application->MessageBoxA("Mo¿esz wpisaæ tylko liczby calkowite dodatnie !","B³ad", MB_OK | MB_ICONERROR);
        }
}
//---------------------------------------------------------------------------

