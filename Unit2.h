//---------------------------------------------------------------------------

#ifndef Unit2H
#define Unit2H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "CSPIN.h"
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TForm2 : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label1;
        TLabel *Label2;
        TButton *Button1;
        TLabel *Label3;
        TLabel *Label4;
        TEdit *Edit1;
        TEdit *Edit2;
        TEdit *Edit3;
        TCSpinButton *CSpinButton1;
        TCSpinButton *CSpinButton2;
        TCSpinButton *CSpinButton3;
        TLabel *Label5;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall CSpinButton1UpClick(TObject *Sender);
        void __fastcall CSpinButton1DownClick(TObject *Sender);
        void __fastcall CSpinButton2UpClick(TObject *Sender);
        void __fastcall CSpinButton2DownClick(TObject *Sender);
        void __fastcall CSpinButton3UpClick(TObject *Sender);
        void __fastcall CSpinButton3DownClick(TObject *Sender);
        void __fastcall Edit1Change(TObject *Sender);
        void __fastcall Edit2Change(TObject *Sender);
        void __fastcall Edit3Change(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm2(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
