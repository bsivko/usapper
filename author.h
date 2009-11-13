//---------------------------------------------------------------------------

#ifndef authorH
#define authorH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TF_Author : public TForm
{
__published:	// IDE-managed Components
    TMemo *Memo1;
    TTimer *Timer1;
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall Timer1Timer(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TF_Author(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TF_Author *F_Author;
//---------------------------------------------------------------------------
#endif
