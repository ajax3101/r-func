//---------------------------------------------------------------------------

#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "CSPIN.h"
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TButton *Button1;
        TButton *Button2;
        TCSpinEdit *ENum;
        TEdit *ECX;
        TLabel *Label1;
        TLabel *Label2;
        TEdit *ECY;
        TLabel *Label3;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall FormResize(TObject *Sender);
        void __fastcall FormPaint(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
private:	// User declarations
        TStringList* XY;
        double       MX;
        double       mX;
        double       MY;
        double       mY;
        double       Ax;
        double       Axx;
        double       Ay;
        double       Ayy;
        double       kx1;
        double       kx2;
        double       ky1;
        double       ky2;
        bool         IsBoundary;
        int __fastcall _X_(double x) { return int(10 - Ax + x * Axx); }
        int __fastcall _Y_(double y) { return int(Panel1->Height + 10 + Ay - y * Ayy); }
        double __fastcall RFunc(double,double);
        bool  __fastcall GetRFuncCoordinate(double&,double&,double,double,double,double);
        void  __fastcall PlotXY(double,double,TColor col = clRed);
public:		// User declarations
        __fastcall TMainForm(TComponent* Owner);
        __fastcall ~TMainForm(void) { delete XY; }
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
