//---------------------------------------------------------------------------

#ifndef TObjectPropertiesFormH
#define TObjectPropertiesFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>

#include "Object3D.h"
#include "Color3UnsignedChar.h"

#include "MarchingCubesScene.h"
#include <ComCtrls.hpp>

//---------------------------------------------------------------------------
class TFormObjectPropertiesForm : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TGroupBox *GroupBox1;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
  TStaticText *StaticText1;
  TStaticText *StaticText2;
  TStaticText *StaticText3;
        TGroupBox *GroupBox4;
  TLabel *Label4;
  TLabel *Label5;
  TStaticText *StaticText4;
  TStaticText *StaticText5;
        TButton *Button1;
  TStaticText *StaticText6;
        TEdit *Edit1;
  TTrackBar *TrackBar1;
  TTrackBar *TrackBar2;
  TTrackBar *TrackBar3;
  TTrackBar *TrackBar4;
  TTrackBar *TrackBar5;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
  void __fastcall TrackBar1Change(TObject *Sender);
  void __fastcall TrackBar2Change(TObject *Sender);
  void __fastcall TrackBar3Change(TObject *Sender);
  void __fastcall TrackBar4Change(TObject *Sender);
  void __fastcall TrackBar5Change(TObject *Sender);
  void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall Panel1Click(TObject *Sender);
        void __fastcall GroupBox1Click(TObject *Sender);
        void __fastcall GroupBox4Click(TObject *Sender);
        void __fastcall Edit1Click(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall Edit1Change(TObject *Sender);
private:	// User declarations

  void __fastcall      TFormObjectPropertiesForm::handleTrackBarChanges();

  MarchingCubesScene  *marchingCubesScene;

public:		// User declarations
  __fastcall TFormObjectPropertiesForm(TComponent* Owner);

  void __fastcall setMarchingCubesScene(MarchingCubesScene*);


};
//---------------------------------------------------------------------------
extern PACKAGE TFormObjectPropertiesForm *FormObjectPropertiesForm;
//---------------------------------------------------------------------------
#endif


