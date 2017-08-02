//---------------------------------------------------------------------------

#ifndef EditH
#define EditH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TBDRYedit : public TForm
{
__published:	// IDE-managed Components
        TRichEdit *RichEdit1;
private:	// User declarations
public:		// User declarations
        __fastcall TBDRYedit(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TBDRYedit *BDRYedit;
//---------------------------------------------------------------------------
#endif
