//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TClippingVolumePropertiesForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormClippingVolumePropertiesForm *FormClippingVolumePropertiesForm;
//---------------------------------------------------------------------------
__fastcall TFormClippingVolumePropertiesForm::TFormClippingVolumePropertiesForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormClippingVolumePropertiesForm::FormCreate(
      TObject *Sender)
{
  Constraints->MaxWidth=380;
  Constraints->MinWidth=380;
  Constraints->MaxHeight=418;
  Constraints->MinHeight=418;

  Button1->Left=(Width-Button1->Width)/2;
}
//---------------------------------------------------------------------------
void __fastcall TFormClippingVolumePropertiesForm::TrackBar1Change(
      TObject *Sender)
{
  handleTrackBarChanges();
}
//---------------------------------------------------------------------------

void __fastcall TFormClippingVolumePropertiesForm::TrackBar2Change(
      TObject *Sender)
{
  handleTrackBarChanges();
}
//---------------------------------------------------------------------------
void __fastcall TFormClippingVolumePropertiesForm::TrackBar3Change(
      TObject *Sender)
{
  handleTrackBarChanges();
}
//---------------------------------------------------------------------------

void __fastcall TFormClippingVolumePropertiesForm::TrackBar4Change(
      TObject *Sender)
{
  handleTrackBarChanges();
}
//---------------------------------------------------------------------------
void __fastcall TFormClippingVolumePropertiesForm::TrackBar5Change(
      TObject *Sender)
{
  handleTrackBarChanges();
}
//---------------------------------------------------------------------------
void __fastcall TFormClippingVolumePropertiesForm::TrackBar6Change(
      TObject *Sender)
{
  handleTrackBarChanges();
}
//---------------------------------------------------------------------------
void __fastcall TFormClippingVolumePropertiesForm::setMarchingCubesScene(MarchingCubesScene* m)
{
  marchingCubesScene=m;
}
//---------------------------------------------------------------------------
void __fastcall TFormClippingVolumePropertiesForm::handleTrackBarChanges()
{
  if (marchingCubesScene && marchingCubesScene->getSelectedClippingVolume())
  {
    marchingCubesScene->getSelectedClippingVolume()->setName(Edit1->Text);

    marchingCubesScene->getSelectedClippingVolume()->setCornerIndexI(TrackBar1->Position);
    marchingCubesScene->getSelectedClippingVolume()->setCornerIndexJ(TrackBar2->Position);
    marchingCubesScene->getSelectedClippingVolume()->setCornerIndexK(TrackBar3->Position);

    marchingCubesScene->getSelectedClippingVolume()->setVolumeWidth(TrackBar4->Position);
    marchingCubesScene->getSelectedClippingVolume()->setVolumeHeight(TrackBar5->Position);
    marchingCubesScene->getSelectedClippingVolume()->setVolumeDepth(TrackBar6->Position);

    marchingCubesScene->setSceneState(STATE_CLIPPING_VOLUME);
    marchingCubesScene->setObjectQualityState(OBJECT_QUALITY_LOW);
    marchingCubesScene->updateScene();


    Label1->Caption = marchingCubesScene->getSelectedClippingVolume()->getCornerIndexI();
    Label2->Caption = marchingCubesScene->getSelectedClippingVolume()->getCornerIndexJ();
    Label3->Caption = marchingCubesScene->getSelectedClippingVolume()->getCornerIndexK();

    Label4->Caption = marchingCubesScene->getSelectedClippingVolume()->getVolumeWidth();
    Label5->Caption = marchingCubesScene->getSelectedClippingVolume()->getVolumeHeight();
    Label6->Caption = marchingCubesScene->getSelectedClippingVolume()->getVolumeDepth();
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormClippingVolumePropertiesForm::CheckListBox1Click(
      TObject *Sender)
{
  if (marchingCubesScene && marchingCubesScene->getSelectedClippingVolume())
  {
    if (CheckListBox1->Checked[CheckListBox1->ItemIndex]==true)
      marchingCubesScene->getSelectedClippingVolume()->setClippedStateAtIndex(CheckListBox1->ItemIndex, true);
    else
      marchingCubesScene->getSelectedClippingVolume()->setClippedStateAtIndex(CheckListBox1->ItemIndex, false);
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormClippingVolumePropertiesForm::Button1Click(
      TObject *Sender)
{
  if (marchingCubesScene && marchingCubesScene->getSelectedClippingVolume())
  {
    marchingCubesScene->getSelectedClippingVolume()->setName(Edit1->Text);


    Word sHour, sMin, sSec, sMSec;
    TDateTime sPresent = Now();
    DecodeTime(sPresent, sHour, sMin, sSec, sMSec);


    marchingCubesScene->generateLists();


    Word eHour, eMin, eSec, eMSec;
    TDateTime ePresent = Now();
    DecodeTime(ePresent, eHour, eMin, eSec, eMSec);
    double start= ((sHour *60 + sMin) *60 + sSec) * 1000 + sMSec;
    double stop = ((eHour *60 + eMin) *60 + eSec) * 1000 + eMSec;
    sendFeedback("Process took "+ FloatToStr(1.0*abs(stop-start)/1000) + " seconds.");


    marchingCubesScene->setSceneState(STATE_NORMAL);
    marchingCubesScene->setObjectQualityState(OBJECT_QUALITY_HIGH);
    marchingCubesScene->updateScene();
  }

  Visible=false;
}
//---------------------------------------------------------------------------

void __fastcall TFormClippingVolumePropertiesForm::FormClose(
      TObject *Sender, TCloseAction &Action)
{
  if (marchingCubesScene && marchingCubesScene->getSelectedClippingVolume())
  {
    marchingCubesScene->setSceneState(STATE_NORMAL);
    marchingCubesScene->setObjectQualityState(OBJECT_QUALITY_HIGH);
    marchingCubesScene->updateScene();
  }

  Visible=false;
}
//---------------------------------------------------------------------------

void __fastcall TFormClippingVolumePropertiesForm::Panel1Click(
      TObject *Sender)
{
  if (marchingCubesScene && marchingCubesScene->getSelectedClippingVolume())
  {
    marchingCubesScene->setSceneState(STATE_CLIPPING_VOLUME);
    marchingCubesScene->setObjectQualityState(OBJECT_QUALITY_LOW);
    marchingCubesScene->updateScene();
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormClippingVolumePropertiesForm::GroupBox1Click(
      TObject *Sender)
{
  if (marchingCubesScene && marchingCubesScene->getSelectedClippingVolume())
  {
    marchingCubesScene->setSceneState(STATE_CLIPPING_VOLUME);
    marchingCubesScene->setObjectQualityState(OBJECT_QUALITY_LOW);
    marchingCubesScene->updateScene();
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormClippingVolumePropertiesForm::GroupBox2Click(
      TObject *Sender)
{
  if (marchingCubesScene && marchingCubesScene->getSelectedClippingVolume())
  {
    marchingCubesScene->setSceneState(STATE_CLIPPING_VOLUME);
    marchingCubesScene->setObjectQualityState(OBJECT_QUALITY_LOW);
    marchingCubesScene->updateScene();
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormClippingVolumePropertiesForm::Edit1Click(
      TObject *Sender)
{
  if (marchingCubesScene && marchingCubesScene->getSelectedClippingVolume())
  {
    marchingCubesScene->setSceneState(STATE_CLIPPING_VOLUME);
    marchingCubesScene->setObjectQualityState(OBJECT_QUALITY_LOW);
    marchingCubesScene->updateScene();
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormClippingVolumePropertiesForm::FormShow(
      TObject *Sender)
{
  if (marchingCubesScene && marchingCubesScene->getSelectedClippingVolume())
  {
    marchingCubesScene->setSceneState(STATE_CLIPPING_VOLUME);
    marchingCubesScene->setObjectQualityState(OBJECT_QUALITY_LOW);
    marchingCubesScene->updateScene();
  
    TrackBar1->Max=marchingCubesScene->getImageSet()->getWidth();
    TrackBar2->Max=marchingCubesScene->getImageSet()->getHeight();
    TrackBar3->Max=marchingCubesScene->getImageSet()->getSliceCount();

    TrackBar4->Max=marchingCubesScene->getImageSet()->getWidth();
    TrackBar5->Max=marchingCubesScene->getImageSet()->getHeight();
    TrackBar6->Max=marchingCubesScene->getImageSet()->getSliceCount();

    int i=marchingCubesScene->getSelectedClippingVolume()->getCornerIndexI(),
        j=marchingCubesScene->getSelectedClippingVolume()->getCornerIndexJ(),
        k=marchingCubesScene->getSelectedClippingVolume()->getCornerIndexK(),
        w=marchingCubesScene->getSelectedClippingVolume()->getVolumeWidth(),
        h=marchingCubesScene->getSelectedClippingVolume()->getVolumeHeight(),
        d=marchingCubesScene->getSelectedClippingVolume()->getVolumeDepth();

    Edit1->Text=marchingCubesScene->getSelectedClippingVolume()->getName();

    TrackBar1->Position = i;
    Label1->Caption     = i;

    TrackBar2->Position = j;
    Label2->Caption     = j;

    TrackBar3->Position = k;
    Label3->Caption     = k;


    TrackBar4->Position = w;
    Label4->Caption     = w;

    TrackBar5->Position = h;
    Label5->Caption     = h;

    TrackBar6->Position = d;
    Label6->Caption     = d;


    CheckListBox1->Clear();

    for (int i=0; i<marchingCubesScene->getTotalObjectCount(); i++ )
    {
      CheckListBox1->Items->Add(marchingCubesScene->getObjectAtIndex(i)->getName());

      if (marchingCubesScene->getSelectedClippingVolume()->getClippedStateAtIndex(i)==false)
        CheckListBox1->Checked[i]=false;
      else
        CheckListBox1->Checked[i]=true;
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormClippingVolumePropertiesForm::Edit1Change(
      TObject *Sender)
{
  if (marchingCubesScene && marchingCubesScene->getSelectedClippingVolume())
  {
    marchingCubesScene->getSelectedClippingVolume()->setName(Edit1->Text);
  }
}
//---------------------------------------------------------------------------

