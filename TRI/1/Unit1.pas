unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  OpenGL,Math;


type
  TfrmGL = class(TForm)
    procedure FormCreate(Sender: TObject);
    procedure FormPaint(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
    procedure FormKeyDown(Sender: TObject; var Key: Word;
      Shift: TShiftState);
    procedure FormMouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);

  private
    hrc: HGLRC;
  end;

var
  frmGL: TfrmGL;

implementation

uses Unit2;

{$R *.DFM}

{=======================================================================
Перерисовка окна}
procedure TfrmGL.FormPaint(Sender: TObject);
const
 a = -Pi;    // начало интервала
 b = Pi;     // конец интервала
 num = 10;  // количество точек на интервале
 R=0.5;
 min=-1;
 max=1;
 alfa1=60;
 a1=0.3;
 var
 x,y,fi,alfa,x1,y1,step,omega,w1,w2 : GLfloat;
 i : GLint;
 //A, B: array of Integer;
begin
 wglMakeCurrent(Canvas.Handle, hrc);

 glViewPort (0, 0, ClientWidth, ClientHeight);

 glClearColor (0.5, 0.5, 0.75, 1.0);
 glClear (GL_COLOR_BUFFER_BIT);

 glEnable (GL_POINT_SMOOTH);
 glColor3f (1.0, 0.0, 0.5);

 glBegin (GL_POINTS);

   x1:=min;
   fi:=2*Pi/num;
   step:=(max-min)/num;
   omega:=0;
   Form2.Memo1.Lines.Clear;
   form2.show;
   For i := 0 to num do
   begin
    alfa:=i*fi;
    x:=R*cos(alfa);
    y:=R*sin(alfa);

    y1:=tan(alfa1)*x1+a1;

    w1:=-(y-tan(alfa1)*x-a1);
    w2:=-(sqr(R)-sqr(x)-sqr(y));
    omega:=w1+w2-sqrt(sqr(w1)+sqr(w2));
//    Form2.Memo1.lines.Add(inttostr(i)+': omega='+FloatToStr(omega));


    if Abs(omega) < 1.0E-6 then
     begin
      glVertex2f(x,y);
      Form2.Memo1.Lines.Add(FloatToStr(x) + ' ' + FloatToStr(y));

     end;

    w1:=(y1-tan(alfa1)*x1-a1);
    w2:=(sqr(R)-sqr(x1)-sqr(y1));
    omega:=w1+w2-sqrt(sqr(w1)+sqr(w2));
//    Form2.Memo1.lines.Add(inttostr(i)+': omega='+FloatToStr(omega));

    if Abs(omega) < 1.0E-6 then
     begin
      glVertex2f(x1,y1);
      Form2.Memo1.Lines.Add(FloatToStr(x1) + ' ' + FloatToStr(y1));
     end;

    x1:=x1+step;

   end;

 glEnd;

 SwapBuffers(Canvas.Handle);
 wglMakeCurrent(0, 0);
end;

{=======================================================================
Формат пикселя}
procedure SetDCPixelFormat (hdc : HDC);
var
 pfd : TPixelFormatDescriptor;
 nPixelFormat : Integer;
begin
 FillChar (pfd, SizeOf (pfd), 0);
 pfd.dwFlags  := PFD_DRAW_TO_WINDOW or PFD_SUPPORT_OPENGL or PFD_DOUBLEBUFFER;
 nPixelFormat := ChoosePixelFormat (hdc, @pfd);
 SetPixelFormat (hdc, nPixelFormat, @pfd);
end;

{=======================================================================
Создание формы}
procedure TfrmGL.FormCreate(Sender: TObject);
begin
 SetDCPixelFormat(Canvas.Handle);
 hrc := wglCreateContext(Canvas.Handle);
end;

{=======================================================================
Конец работы приложения}
procedure TfrmGL.FormDestroy(Sender: TObject);
begin
 wglDeleteContext(hrc);
end;

procedure TfrmGL.FormKeyDown(Sender: TObject; var Key: Word;
  Shift: TShiftState);
begin
    if key = VK_ESCAPE then close;
end;

procedure TfrmGL.FormMouseMove(Sender: TObject; Shift: TShiftState; X,
  Y: Integer);
var
   my_x,my_y:double;
begin
// box 0,0 - ClientWidth,ClientHeight
// mybox -1,1 - 1,-1
 my_x:=2.0*x/ClientWidth-1.0;
 my_y:=-2.0*y/ClientHeight+1.0;
 Caption := 'R-фунция   '+'x=' + FloatToStr (my_x) + ', y=' + FloatToStr (my_y);
end;

end.

