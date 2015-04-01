//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TObjectPropertiesForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormObjectPropertiesForm *FormObjectPropertiesForm;
//---------------------------------------------------------------------------
__fastcall TFormObjectPropertiesForm::TFormObjectPropertiesForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

extern void sendFeedback(AnsiString);


void __fastcall TFormObjectPropertiesForm::FormCreate(TObject *Sender)
{
  Constraints->MaxWidth=400;
  Constraints->MinWidth=400;
  Constraints->MaxHeight=280;
  Constraints->MinHeight=280;

  TrackBar1->Min=0;
  TrackBar2->Min=0;
  TrackBar3->Min=0;
  TrackBar4->Min=0;
  TrackBar5->Min=0;

  TrackBar1->Max=255;
  TrackBar2->Max=255;
  TrackBar3->Max=255;
  TrackBar4->Max=127;
  TrackBar5->Max=255;

  Button1->Left=(Width-Button1->Width)/2;
}
//---------------------------------------------------------------------------
void __fastcall TFormObjectPropertiesForm::TrackBar1Change(
      TObject *Sender)
{
  handleTrackBarChanges();
}
//---------------------------------------------------------------------------
void __fastcall TFormObjectPropertiesForm::TrackBar2Change(
      TObject *Sender)
{
  handleTrackBarChanges();
}
//---------------------------------------------------------------------------

void __fastcall TFormObjectPropertiesForm::TrackBar3Change(
      TObject *Sender)
{
  handleTrackBarChanges();
}
//---------------------------------------------------------------------------
void __fastcall TFormObjectPropertiesForm::TrackBar4Change(
      TObject *Sender)
{
  handleTrackBarChanges();
}
//---------------------------------------------------------------------------
void __fastcall TFormObjectPropertiesForm::TrackBar5Change(
      TObject *Sender)
{
  handleTrackBarChanges();
}
//---------------------------------------------------------------------------
void __fastcall TFormObjectPropertiesForm::setMarchingCubesScene(MarchingCubesScene* m)
{
  marchingCubesScene=m;
}
//---------------------------------------------------------------------------
void __fastcall TFormObjectPropertiesForm::handleTrackBarChanges()
{
  if (marchingCubesScene && marchingCubesScene->getSelectedObject())
  {
    Color3UnsignedChar c=Color3UnsignedChar(TrackBar1->Position, TrackBar2->Position, TrackBar3->Position);

    marchingCubesScene->getSelectedObject()->setName(Edit1->Text);
    marchingCubesScene->getSelectedObject()->setColor(c);

    marchingCubesScene->getSelectedObject()->setShininess(TrackBar4->Position);
    marchingCubesScene->getSelectedObject()->setAlpha(TrackBar5->Position);

    marchingCubesScene->setSceneState(STATE_NORMAL);
    marchingCubesScene->setObjectQualityState(OBJECT_QUALITY_LOW);
    marchingCubesScene->updateScene();

    Label1->Caption = marchingCubesScene->getSelectedObject()->getColor().red;
    Label2->Caption = marchingCubesScene->getSelectedObject()->getColor().green;
    Label3->Caption = marchingCubesScene->getSelectedObject()->getColor().blue;

    Label4->Caption = marchingCubesScene->getSelectedObject()->getShininess();
    Label5->Caption = marchingCubesScene->getSelectedObject()->getAlpha();

    FormObjectPropertiesForm->TrackBar5->Position =marchingCubesScene->getSelectedObject()->getAlpha();
    FormObjectPropertiesForm->Label5->Caption     =marchingCubesScene->getSelectedObject()->getAlpha();
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormObjectPropertiesForm::Button1Click(TObject *Sender)
{
  if (marchingCubesScene && marchingCubesScene->getSelectedObject())
  {
    marchingCubesScene->getSelectedObject()->setName(Edit1->Text);
    marchingCubesScene->setSceneState(STATE_NORMAL);
    marchingCubesScene->setObjectQualityState(OBJECT_QUALITY_HIGH);
    marchingCubesScene->updateScene();
  }

  Visible=false;
}
//---------------------------------------------------------------------------
void __fastcall TFormObjectPropertiesForm::FormClose(TObject *Sender,
      TCloseAction &Action)
{
  if (marchingCubesScene && marchingCubesScene->getSelectedObject())
  {
    marchingCubesScene->getSelectedObject()->setName(Edit1->Text);
    marchingCubesScene->setSceneState(STATE_NORMAL);
    marchingCubesScene->setObjectQualityState(OBJECT_QUALITY_HIGH);
    marchingCubesScene->updateScene();
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormObjectPropertiesForm::Panel1Click(TObject *Sender)
{
  if (marchingCubesScene && marchingCubesScene->getSelectedObject())
  {
    marchingCubesScene->setSceneState(STATE_NORMAL);
    marchingCubesScene->setObjectQualityState(OBJECT_QUALITY_LOW);
    marchingCubesScene->updateScene();
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormObjectPropertiesForm::GroupBox1Click(TObject *Sender)
{
  if (marchingCubesScene && marchingCubesScene->getSelectedObject())
  {
    marchingCubesScene->setSceneState(STATE_NORMAL);
    marchingCubesScene->setObjectQualityState(OBJECT_QUALITY_LOW);
    marchingCubesScene->updateScene();
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormObjectPropertiesForm::GroupBox4Click(TObject *Sender)
{
  if (marchingCubesScene && marchingCubesScene->getSelectedObject())
  {
    marchingCubesScene->setSceneState(STATE_NORMAL);
    marchingCubesScene->setObjectQualityState(OBJECT_QUALITY_LOW);
    marchingCubesScene->updateScene();
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormObjectPropertiesForm::Edit1Click(TObject *Sender)
{
  if (marchingCubesScene && marchingCubesScene->getSelectedObject())
  {
    marchingCubesScene->setSceneState(STATE_NORMAL);
    marchingCubesScene->setObjectQualityState(OBJECT_QUALITY_LOW);
    marchingCubesScene->updateScene();
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormObjectPropertiesForm::FormShow(TObject *Sender)
{
  if (marchingCubesScene && marchingCubesScene->getSelectedObject())
  {
    marchingCubesScene->setSceneState(STATE_NORMAL);
    marchingCubesScene->setObjectQualityState(OBJECT_QUALITY_LOW);
    marchingCubesScene->updateScene();

    Color3UnsignedChar c=marchingCubesScene->getSelectedObject()->getColor();

    int i=marchingCubesScene->getSelectedObject()->getShininess();
    int a=marchingCubesScene->getSelectedObject()->getAlpha();

    Edit1->Text=marchingCubesScene->getSelectedObject()->getName();

    TrackBar1->Position =c.red;
    Label1->Caption     =c.red;

    TrackBar2->Position =c.green;
    Label2->Caption     =c.green;

    TrackBar3->Position =c.blue;
    Label3->Caption     =c.blue;

    TrackBar4->Position =i;
    Label4->Caption     =i;

    TrackBar5->Position =a;
    Label5->Caption     =a;

    if (marchingCubesScene->getSelectedObject()->getID()==marchingCubesScene->getObjectAtIndex(marchingCubesScene->getTotalObjectCount()-1)->getID())
      TrackBar5->Visible=false;
    else
      TrackBar5->Visible=true;
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormObjectPropertiesForm::Edit1Change(TObject *Sender)
{
  if (marchingCubesScene && marchingCubesScene->getSelectedObject())
  {
    marchingCubesScene->getSelectedObject()->setName(Edit1->Text);
  }
}
//---------------------------------------------------------------------------

