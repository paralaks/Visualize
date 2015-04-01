//---------------------------------------------------------------------------

#ifndef TSceneInspectorFormH
#define TSceneInspectorFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <CheckLst.hpp>
#include <Dialogs.hpp>

#include "CAnalyze.h"
#include "LightSource.h"

#include "TObjectPropertiesForm.h"
#include "TClippingVolumePropertiesForm.h"
#include "TTexturedSurfacePropertiesForm.h"

#include "MarchingCubesScene.h"
#include <ComCtrls.hpp>
#include <NMEcho.hpp>
#include <Psock.hpp>

//---------------------------------------------------------------------------
class TFormSceneInspectorForm : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel0;
        TPanel *Panel2;
        TCheckListBox *CheckListBox1;
        TButton *Button1;
        TStaticText *StaticText1;
        TPanel *Panel3;
        TButton *Button3;
        TStaticText *StaticText2;
        TPanel *Panel4;
        TCheckListBox *CheckListBox3;
        TStaticText *StaticText3;
        TPanel *Panel5;
        TStaticText *StaticText4;
        TGroupBox *GroupBox1;
        TStaticText *StaticText7;
        TStaticText *StaticText6;
        TStaticText *StaticText5;
        TStaticText *StaticText8;
        TButton *Button5;
        TButton *Button4;
        TButton *Button6;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TOpenDialog *OpenDialog1;
        TMemo *Memo1;
        TTrackBar *TrackBar5;
        TTrackBar *TrackBar4;
        TTrackBar *TrackBar3;
        TTrackBar *TrackBar2;
  TListBox *ListBox1;
        TButton *Button2;
        TPanel *Panel7;
        TImage *Image1;
        TTrackBar *TrackBar1;
        TPanel *Panel6;
        TButton *Button7;
        TButton *Button8;
        TPanel *Panel1;
        TSpeedButton *SpeedButton1;
        TSpeedButton *SpeedButton2;
        TSpeedButton *SpeedButton3;
        TSpeedButton *SpeedButton4;
        void __fastcall SpeedButton1Click(TObject *Sender);
        void __fastcall SpeedButton2Click(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall SpeedButton3Click(TObject *Sender);
        void __fastcall SpeedButton4Click(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall Button5Click(TObject *Sender);
        void __fastcall Button8Click(TObject *Sender);
  void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall TrackBar2Change(TObject *Sender);
        void __fastcall TrackBar3Change(TObject *Sender);
        void __fastcall TrackBar4Change(TObject *Sender);
        void __fastcall TrackBar5Change(TObject *Sender);
  void __fastcall CheckListBox1Click(TObject *Sender);
  void __fastcall FormActivate(TObject *Sender);
  void __fastcall ListBox1Click(TObject *Sender);
  void __fastcall Button4Click(TObject *Sender);
        void __fastcall Button7Click(TObject *Sender);
        void __fastcall TrackBar1Change(TObject *Sender);
        void __fastcall Image1MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall Image1MouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall FormResize(TObject *Sender);
private:	// User declarations

  Graphics::TBitmap* displayBitmap;

  TPanel* oldPanel;

  CAnalyze *imageSet;

  bool       imageSetLoaded;

  MarchingCubesScene *marchingCubesScene;

  float trackBarsMiddleValue;


public:		// User declarations
        __fastcall TFormSceneInspectorForm(TComponent* Owner);

  void __fastcall handleTrackBarChanges();
  void __fastcall generatePalette();
  void __fastcall displaySlice();
};
//---------------------------------------------------------------------------
extern PACKAGE TFormSceneInspectorForm *FormSceneInspectorForm;
//---------------------------------------------------------------------------
#endif
