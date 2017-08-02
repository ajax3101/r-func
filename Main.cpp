//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#include <Math.hpp>
#include <math.h>
#pragma hdrstop

#include "Main.h"
#include "Edit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
        : TForm(Owner)
{
        XY = new TStringList;
        MX = MY = MinDouble;
        mX = mY = MaxDouble;
        IsBoundary = false;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::Button1Click(TObject *Sender)
{
        double CX = StrToFloat(ECX->Text), // Координаты центра локатора
               CY = StrToFloat(ECY->Text),
               N  = StrToInt(ENum->Value), // Количество шагов (узлов на границе R-функции)
               delta = 2.0 * M_PI / N,
               x,
               y,
               fi = 0,
               Radius = 100; // Радиус окружности, содержащей R-функцию


        XY->Clear();
        for (int i = 0; i < int(N); i++)
         {
//            if (GetRFuncCoordinate(x,y,CX,CY,fi,Radius)) PlotXY(x,y);
            if (GetRFuncCoordinate(x,y,CX,CY,fi,Radius))
             {
               if (x > MX) MX = x;
               if (y > MY) MY = y;
               if (x < mX) mX = x;
               if (y < mY) mY = y;
               XY->Add(FloatToStr(x)+" "+FloatToStr(y));
             }
            fi += delta;
         }
/*        CX = 0.45;
        CY = 0;
        for (int i = 0; i < int(N); i++)
         {
            if (GetRFuncCoordinate(x,y,CX,CY,fi,Radius)) PlotXY(x,y);
            fi += delta;
         }
*/
        Invalidate();
}
//---------------------------------------------------------------------------
// R-Функция
//---------------------------------------------------------------------------
double __fastcall TMainForm::RFunc(double X,double Y)
{
       // Круг с вырезом
/*         double R = 0.4,
                R1 = 0.4,
                W1 = - (R1 * R1 - (X - 0.6) * (X - 0.6) - Y * Y),
                W2 = - (R * R - X * X - Y * Y),
                W  = W1 + W2 - pow(W1 * W1 + W2 * W2, 0.5);
*/

         double R = 0.4,
                R1 = 0.25,
                W1 = - (R1 * R1 - (X - 0.6) * (X - 0.6) - Y * Y),
                W2 = - (R * R - X * X - Y * Y),
                W3 = - (R1 * R1 - (X + 0.6) * (X + 0.6) - Y * Y),
                W  = W1 + W3 + W2 - pow(W1 * W1 + W2 * W2 + W3 * W3, 0.5);

/*
         // Прикольно!!!
         double R = 0.4,
                W1 = - (R * R - X * X - Y * Y),
                W2 = - (X + Y),
                W3 = - (X - Y),
                W  = W1 + W2 + W3 - pow(W1 * W1 + W2 * W2 + W3 * W3, 0.5);
*/

/*         double R = 0.4,
                W1 = - (R * R - X * X - Y * Y),
                W2 = - (X + Y),
                W3 = - (0.25*X * X - Y),
                W  = W1 - W3 - pow(W1 * W1 + W3 * W3, 0.5);
*/
        return W;
}
//---------------------------------------------------------------------------
// Функция определения координат пересечения R-функции и луча, исходящего из точки (CX,CY) под углом fi
//---------------------------------------------------------------------------
bool __fastcall TMainForm::GetRFuncCoordinate(double& ResX,double& ResY,double CX,double CY,double fi,double Radius)
{
        double R1 = 0,
               R2 = Radius,
               R,
               x1 = R1 * cos(fi) + CX,
               y1 = R1 * sin(fi) + CY,
               x2 = R2 * cos(fi) + CX,
               y2 = R2 * sin(fi) + CY,
               tx,
               ty,
               Eps = 0.0001;
        int    S1 = Sign(RFunc(x1,y1)),
               S2 = Sign(RFunc(x2,y2)),
               TS;

        if (S1 == S2) return false;

        do
         {
            R  = (R1 + R2) * 0.5;
            x1 = R1 * cos(fi) + CX;
            y1 = R1 * sin(fi) + CY;
            x2 = R2 * cos(fi) + CX;
            y2 = R2 * sin(fi) + CY;
            tx = R * cos(fi) + CX;
            ty = R * sin(fi) + CY;
            TS = Sign(RFunc(tx,ty));

//            if (TS > 0)
//             PlotXY(tx,ty,clBlue);
//            else
//             PlotXY(tx,ty,clGreen);

            if (TS == S1)
             R1 = R;
            else
             R2 = R;
         }
        while (fabs(RFunc(tx,ty)) > Eps);

        ResX = tx;
        ResY = ty;
        return true;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::PlotXY(double x,double y,TColor col)
{
        Canvas->Pixels[_X_(x)][_Y_(y)] = col;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormResize(TObject *Sender)
{
        Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormPaint(TObject *Sender)
{
        String Str;
        double x,
               y;

        if (!XY->Count) return;
        kx1 = MX - mX;
        kx2 = mX;
        ky1 = MY - mY;
        ky2 = MY;
        Axx = (double)(ClientWidth - 20) / kx1;
        Ayy = (double)(ClientHeight - Panel1->Height - 20) / ky1;
        Ax = Axx * kx2;
        Ay = Ayy * ky2;

        for (int i = 0; i < XY->Count; i++)
         {
            Str = XY->Strings[i];
            sscanf(Str.c_str(),"%lf %lf",&x,&y);
            PlotXY(x,y);
         }
        if (IsBoundary)
         {
          Str = XY->Strings[0];
          sscanf(Str.c_str(),"%lf %lf",&x,&y);
          Canvas->MoveTo(_X_(x),_Y_(y));
          for (int i = 1; i < XY->Count; i++)
           {
             Str = XY->Strings[i];
             sscanf(Str.c_str(),"%lf %lf",&x,&y);
             Canvas->LineTo(_X_(x),_Y_(y));
           }
          Str = XY->Strings[0];
          sscanf(Str.c_str(),"%lf %lf",&x,&y);
          Canvas->LineTo(_X_(x),_Y_(y));
         }

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormCreate(TObject *Sender)
{
        DecimalSeparator = '.';
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::Button2Click(TObject *Sender)
{
        int    Num = XY->Count,
               Index;
        float  xi,
               yi,
               xj,
               yj,
               x,
               y,
               Len;
        String Str;

        if (!Num) return;

        for (int i = 0; i < Num - 1; i++)
        {
         sscanf(XY->Strings[i].c_str(),"%f %f",&xi,&yi);
         sscanf(XY->Strings[i + 1].c_str(),"%f %f",&xj,&yj);
         Len   = (xi - xj)*(xi - xj) + (yi - yj)*(yi - yj);

         if (Len == 0) Application->MessageBox("Обнаружены совпадающие узлы", "Ошибка");
         Index = i + 1;
         for (int j = i + 2; j < Num; j++)
         {
          sscanf(XY->Strings[j].c_str(),"%f %f",&xj,&yj);
          if ((xi - xj)*(xi - xj) + (yi - yj)*(yi - yj) < Len)
           {
             Len   = (xi - xj)*(xi - xj) + (yi - yj)*(yi - yj);
             Index = j;
             if (Len == 0) Application->MessageBox("Обнаружены совпадающие узлы", "Ошибка");
           }
         }
         Str = XY->Strings[Index];
         XY->Delete(Index);
         XY->Insert(i + 1,Str);
        }
       BDRYedit->RichEdit1->Lines->Clear();
       BDRYedit->RichEdit1->Lines->Add(IntToStr(Num) + " " + IntToStr(Num));
       BDRYedit->RichEdit1->Lines->AddStrings(XY);
       Str = "polyline r 1 b 1 " + IntToStr(Num + 1) + " ";
       for (int i = 0; i < Num; i++) Str += (IntToStr(i) + " ");
       Str += "0";
       BDRYedit->RichEdit1->Lines->Add(Str);
       BDRYedit->Show();
       IsBoundary = true;
       Invalidate();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormShow(TObject *Sender)
{
        MX =  2;
        mX = -2;
        MY =  2;
        mY = -2;

        kx1 = MX - mX;
        kx2 = mX;
        ky1 = MY - mY;
        ky2 = MY;
        Axx = (double)(ClientWidth - 20) / kx1;
        Ayy = (double)(ClientHeight - Panel1->Height - 20) / ky1;
        Ax = Axx * kx2;
        Ay = Ayy * ky2;
}
//---------------------------------------------------------------------------

