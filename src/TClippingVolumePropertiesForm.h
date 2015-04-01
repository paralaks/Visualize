//---------------------------------------------------------------------------

#ifndef TClippingVolumePropertiesFormH
#define TClippingVolumePropertiesFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>

#include "MarchingCubesScene.h"
#include <ComCtrls.hpp>
#include <CheckLst.hpp>

//---------------------------------------------------------------------------
class TFormClippingVolumePropertiesForm : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TGroupBox *GroupBox1;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TStaticText *StaticText5;
        TStaticText *StaticText6;
        TStaticText *StaticText7;
        TGroupBox *GroupBox2;
        TLabel *Label4;
        TLabel *Label5;
        TLabel *Label6;
        TStaticText *StaticText1;
        TStaticText *StaticText2;
        TStaticText *StaticText3;
        TButton *Button1;
        TTrackBar *TrackBar1;
        TTrackBar *TrackBar3;
        TTrackBar *TrackBar2;
        TTrackBar *TrackBar6;
        TTrackBar *TrackBar5;
        TTrackBar *TrackBar4;
  TStaticText *StaticText4;
  TEdit *Edit1;
  TGroupBox *GroupBox3;
  TCheckListBox *CheckListBox1;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
  void __fastcall TrackBar1Change(TObject *Sender);
  void __fastcall TrackBar2Change(TObject *Sender);
  void __fastcall TrackBar3Change(TObject *Sender);
  void __fastcall TrackBar4Change(TObject *Sender);
  void __fastcall TrackBar5Change(TObject *Sender);
  void __fastcall TrackBar6Change(TObject *Sender);
  void __fastcall CheckListBox1Click(TObject *Sender);
  void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall Panel1Click(TObject *Sender);
        void __fastcall GroupBox1Click(TObject *Sender);
        void __fastcall GroupBox2Click(TObject *Sender);
        void __fastcall Edit1Click(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall Edit1Change(TObject *Sender);
private:	// User declarations

  MarchingCubesScene *marchingCubesScene;


public:		// User declarations

       __fastcall TFormClippingVolumePropertiesForm(TComponent* Owner);
  void __fastcall setMarchingCubesScene(MarchingCubesScene*);
  void __fastcall handleTrackBarChanges();


};
//---------------------------------------------------------------------------
extern PACKAGE TFormClippingVolumePropertiesForm *FormClippingVolumePropertiesForm;
//---------------------------------------------------------------------------
#endif
