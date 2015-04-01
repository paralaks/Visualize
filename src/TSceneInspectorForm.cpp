//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "TSceneInspectorForm.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)
#pragma resource "*.dfm"


TFormSceneInspectorForm *FormSceneInspectorForm;
//---------------------------------------------------------------------------
__fastcall TFormSceneInspectorForm::TFormSceneInspectorForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void sendFeedback(AnsiString s)
{
  FormSceneInspectorForm->Memo1->Lines->Add(s);
}


void __fastcall TFormSceneInspectorForm::FormCreate(TObject *Sender)
{
  Top=0;
  Left=0;
  
  Panel0->Left=0;
  Panel0->Top=0;
  Panel0->Width=100;
  Panel0->Height=1;

  Panel1->Top=Panel0->Top+4;
  Panel2->Top=Panel1->Top+Panel1->Height+2;
  Panel3->Top=Panel2->Top;
  Panel4->Top=Panel2->Top;
  Panel5->Top=Panel2->Top;

  Panel1->Left=2;
  Panel2->Left=2;
  Panel3->Left=2;
  Panel4->Left=2;
  Panel5->Left=2;
  Panel6->Left=2;
  Panel7->Left=2;
  Memo1->Left=2;

  SpeedButton1->Down=true;
  SpeedButton1->Visible=false;
  SpeedButton2->Visible=false;
  SpeedButton3->Visible=false;
  SpeedButton4->Visible=false;

  Button1->Visible=false;
  Button2->Visible=false;

  StaticText1->Left=(Width-StaticText1->Width)/2;
  StaticText2->Left=(Width-StaticText2->Width)/2;
  StaticText3->Left=(Width-StaticText3->Width)/2;
  StaticText4->Left=(Width-StaticText4->Width)/2;

  TrackBar2->Min=0;
  TrackBar3->Min=0;
  TrackBar4->Min=0;
  TrackBar5->Min=0;

  TrackBar2->Max=200;
  TrackBar3->Max=200;
  TrackBar4->Max=200;
  TrackBar5->Max=255;


  Label1->Caption=AnsiString(0);
  Label2->Caption=AnsiString(0);
  Label3->Caption=AnsiString(0);
  Label4->Caption=AnsiString(0);

  oldPanel=Panel2;

  Button8->Visible=false;

  imageSet=new CAnalyze();

  TrackBar1->Min=0;
  TrackBar1->Max=0;
  Image1->Left=0;
  Image1->Top=45;

  Panel6->Left=2;
  Panel6->Top=Panel2->Top+Panel2->Height+2;

  Image1->Width=0;
  Image1->Height=0;

  Panel7->Left=2;
  Panel7->Top=Panel6->Top+Panel6->Height+2;
  Panel7->Height=Image1->Top+Image1->Height+2;

  Memo1->Left=2;
  Memo1->Top=Panel7->Top+Panel7->Height+2;

  ClientWidth=Panel1->Width+4;
  ClientHeight=Memo1->Top+Memo1->Height+2;

  imageSetLoaded=false;
  marchingCubesScene=NULL;

  trackBarsMiddleValue=100;
  TrackBar2->Max=2*trackBarsMiddleValue;
  TrackBar3->Max=2*trackBarsMiddleValue;
  TrackBar4->Max=2*trackBarsMiddleValue;
}
//---------------------------------------------------------------------------
void __fastcall TFormSceneInspectorForm::SpeedButton1Click(TObject *Sender)
{
  oldPanel->Visible=false;
  Panel2->Visible=true;
  oldPanel=Panel2;
}
//---------------------------------------------------------------------------
void __fastcall TFormSceneInspectorForm::SpeedButton2Click(TObject *Sender)
{
  oldPanel->Visible=false;
  Panel3->Visible=true;
  oldPanel=Panel3;
}
//---------------------------------------------------------------------------

void __fastcall TFormSceneInspectorForm::SpeedButton3Click(TObject *Sender)
{
  oldPanel->Visible=false;
  Panel4->Visible=true;
  oldPanel=Panel4;
}
//---------------------------------------------------------------------------

void __fastcall TFormSceneInspectorForm::SpeedButton4Click(TObject *Sender)
{
  if (marchingCubesScene)
  {
    float x,y,z;
    unsigned char i;

    x=marchingCubesScene->getLightSource()->getLightDirectionX();
    y=marchingCubesScene->getLightSource()->getLightDirectionY();
    z=marchingCubesScene->getLightSource()->getLightDirectionZ();
    i=marchingCubesScene->getLightSource()->getLightIntensity();

    Label1->Caption    =x;
    Label2->Caption    =y;
    Label3->Caption    =z;
    Label4->Caption    =i;

    TrackBar2->Position=trackBarsMiddleValue*(x+1);
    TrackBar3->Position=trackBarsMiddleValue*(y+1);
    TrackBar4->Position=trackBarsMiddleValue*(z+1);
    TrackBar5->Position=i;
  }
  else
  {
    TrackBar1->Position=0;
    Label1->Caption    =0;

    TrackBar2->Position=0;
    Label2->Caption    =0;

    TrackBar3->Position=0;
    Label3->Caption    =0;

    TrackBar4->Position=0;
    Label4->Caption    =0;

  }

  oldPanel->Visible=false;
  Panel5->Visible=true;
  oldPanel=Panel5;
}
//---------------------------------------------------------------------------
void __fastcall TFormSceneInspectorForm::Button1Click(TObject *Sender)
{
  FormObjectPropertiesForm->Visible=true;
}
//---------------------------------------------------------------------------
void __fastcall TFormSceneInspectorForm::Button3Click(TObject *Sender)
{
  FormClippingVolumePropertiesForm->Visible=true;
}
//---------------------------------------------------------------------------

void __fastcall TFormSceneInspectorForm::Button5Click(TObject *Sender)
{
  FormTexturedSurfacePropertiesForm->Visible=true;
}
//---------------------------------------------------------------------------
void __fastcall TFormSceneInspectorForm::Button8Click(TObject *Sender)
{
  if (imageSetLoaded && marchingCubesScene)
  {
    Word sHour, sMin, sSec, sMSec;
    TDateTime sPresent = Now();
    DecodeTime(sPresent, sHour, sMin, sSec, sMSec);

    marchingCubesScene->marchTheCubes();

    Word eHour, eMin, eSec, eMSec;
    TDateTime ePresent = Now();
    DecodeTime(ePresent, eHour, eMin, eSec, eMSec);

    double start= ((sHour *60 + sMin) *60 + sSec) * 1000 + sMSec;
    double stop = ((eHour *60 + eMin) *60 + eSec) * 1000 + eMSec;

    Memo1->Lines->Add("Process took "+ FloatToStr(1.0*abs(stop-start)/1000) + " seconds.");

    marchingCubesScene->updateScene();
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormSceneInspectorForm::FormClose(TObject *Sender,
      TCloseAction &Action)
{
  if (imageSet)
    delete imageSet;
  if (marchingCubesScene)
    delete marchingCubesScene;
}
//---------------------------------------------------------------------------
void __fastcall TFormSceneInspectorForm::handleTrackBarChanges()
{
  if (marchingCubesScene)
  {
    marchingCubesScene->getLightSource()->setLightDirectionX((TrackBar2->Position-trackBarsMiddleValue)/trackBarsMiddleValue);
    marchingCubesScene->getLightSource()->setLightDirectionY((TrackBar3->Position-trackBarsMiddleValue)/trackBarsMiddleValue);
    marchingCubesScene->getLightSource()->setLightDirectionZ((TrackBar4->Position-trackBarsMiddleValue)/trackBarsMiddleValue);

    marchingCubesScene->getLightSource()->setLightIntensity(TrackBar5->Position);

    marchingCubesScene->updateScene();

    Label1->Caption=AnsiString(marchingCubesScene->getLightSource()->getLightDirectionX());
    Label2->Caption=AnsiString(marchingCubesScene->getLightSource()->getLightDirectionY());
    Label3->Caption=AnsiString(marchingCubesScene->getLightSource()->getLightDirectionZ());
    Label4->Caption=AnsiString(marchingCubesScene->getLightSource()->getLightIntensity());
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormSceneInspectorForm::TrackBar2Change(TObject *Sender)
{
  handleTrackBarChanges();
}
//---------------------------------------------------------------------------

void __fastcall TFormSceneInspectorForm::TrackBar3Change(TObject *Sender)
{
  handleTrackBarChanges();        
}
//---------------------------------------------------------------------------

void __fastcall TFormSceneInspectorForm::TrackBar4Change(TObject *Sender)
{
  handleTrackBarChanges();        
}
//---------------------------------------------------------------------------

void __fastcall TFormSceneInspectorForm::TrackBar5Change(TObject *Sender)
{
  handleTrackBarChanges();
}
//---------------------------------------------------------------------------
void __fastcall TFormSceneInspectorForm::CheckListBox1Click(
      TObject *Sender)
{
  bool wasVisible=FormObjectPropertiesForm->Visible;

  FormObjectPropertiesForm->Visible=false;

  marchingCubesScene->setSelectedObjectAtIndex(CheckListBox1->ItemIndex);
  if (CheckListBox1->Checked[CheckListBox1->ItemIndex])
    marchingCubesScene->getObjectAtIndex(CheckListBox1->ItemIndex)->setVisible(true);
  else
    marchingCubesScene->getObjectAtIndex(CheckListBox1->ItemIndex)->setVisible(false);
  marchingCubesScene->updateScene();

  displaySlice();

  FormObjectPropertiesForm->Visible=wasVisible;
}
//---------------------------------------------------------------------------
void __fastcall TFormSceneInspectorForm::FormActivate(TObject *Sender)
{
  if (marchingCubesScene)
  {
    for (int i=0; i<marchingCubesScene->getTotalObjectCount(); i++)
      CheckListBox1->Items->Strings[i]=marchingCubesScene->getObjectAtIndex(i)->getName();

    for (int i=marchingCubesScene->getTotalClippingVolumeCount()-1; i>=0; i--)
      ListBox1->Items->Strings[i]=marchingCubesScene->getClippingVolumeAtIndex(i)->getName();
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormSceneInspectorForm::ListBox1Click(TObject *Sender)
{
  bool wasVisible=FormClippingVolumePropertiesForm->Visible;

  FormClippingVolumePropertiesForm->Visible=false;

  marchingCubesScene->setSelectedClippingVolumeAtIndex(ListBox1->ItemIndex);

    FormClippingVolumePropertiesForm->Visible=wasVisible;
}
//---------------------------------------------------------------------------

void __fastcall TFormSceneInspectorForm::Button4Click(TObject *Sender)
{
  if (marchingCubesScene)
  {
    ListBox1->Clear();

    marchingCubesScene->addClippingVolume();

    for (int i=0; i<marchingCubesScene->getTotalClippingVolumeCount(); i++)
      ListBox1->Items->Add(marchingCubesScene->getClippingVolumeAtIndex(i)->getName());
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormSceneInspectorForm::Button2Click(TObject *Sender)
{
  if (marchingCubesScene)
  {
    CheckListBox1->Clear();

    marchingCubesScene->addObject();

    for (int i=0; i<marchingCubesScene->getTotalObjectCount(); i++)
    {
      CheckListBox1->Items->Add(marchingCubesScene->getObjectAtIndex(i)->getName());
      CheckListBox1->Checked[i]=true;
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormSceneInspectorForm::Button7Click(TObject *Sender)
{
  OpenDialog1->Execute();

  if (OpenDialog1->FileName!="")
    if (imageSet->loadImage(OpenDialog1->FileName.c_str()))
      imageSetLoaded=true;

  if (imageSetLoaded==true)
  {
    TrackBar1->Max=imageSet->getSliceCount()-1;
    TrackBar1->Position=imageSet->getSliceCount() / 2;

    Image1->Width=imageSet->getWidth();
    Image1->Height=imageSet->getHeight();


    Panel7->Top=Panel6->Top+Panel6->Height+2;
    Panel7->Height=Image1->Top+Image1->Height+4;
    Memo1->Left=2;
    Memo1->Top=Panel7->Top+Panel7->Height+2;
    ClientWidth=Panel1->Width+4;
    ClientHeight=Memo1->Top+Memo1->Height+2;


    Image1->Left=(Panel7->Width-Image1->Width)/2;

    Image1->Picture->Bitmap->Width=imageSet->getWidth();
    Image1->Picture->Bitmap->Height=imageSet->getHeight();


    SpeedButton1->Down=true;
    SpeedButton1->Visible=true;
    SpeedButton2->Visible=true;
//      SpeedButton3->Visible=true;
    SpeedButton4->Visible=true;

    Button1->Visible=true;
    Button2->Visible=true;
    Button8->Visible=true;


    oldPanel->Visible=false;
    Panel2->Visible=true;
    oldPanel=Panel2;

    CheckListBox1->Clear();
    ListBox1->Clear();
    CheckListBox3->Clear();
    FormClippingVolumePropertiesForm->CheckListBox1->Clear();


    displaySlice();
    if (marchingCubesScene==NULL)
    {
      marchingCubesScene=new MarchingCubesScene();

      marchingCubesScene->setImageSet(imageSet);

      FormObjectPropertiesForm->setMarchingCubesScene(marchingCubesScene);
      FormClippingVolumePropertiesForm->setMarchingCubesScene(marchingCubesScene);
      FormTexturedSurfacePropertiesForm->setMarchingCubesScene(marchingCubesScene);

      marchingCubesScene->initializeMarchingCubesScene();
    }
    else
    {
      marchingCubesScene->setImageSet(imageSet);
      marchingCubesScene->reshapeForNewImageSet();

      FormObjectPropertiesForm->Visible=false;
      FormClippingVolumePropertiesForm->Visible=false;
      FormTexturedSurfacePropertiesForm->Visible=false;

      marchingCubesScene->updateScene();
    }

    displaySlice();
  }
}
//---------------------------------------------------------------------------
/*void __fastcall TFormSceneInspectorForm::generatePalette()
{
  if (!imageSet || !marchingCubesScene)
    return;

  int thresholdColor=256;

  if (marchingCubesScene->getSelectedObject())
    thresholdColor=marchingCubesScene->getSelectedObject()->getThresholdIntensity();

  LOGPALETTE *imagePalette= (LOGPALETTE*) new char[ sizeof(LOGPALETTE) + sizeof(PALETTEENTRY) * 256];
  imagePalette->palVersion = 0x300;
  imagePalette->palNumEntries = 256;

  for (int i=0; i<thresholdColor; i++)
  {
    imagePalette->palPalEntry[i].peRed=i;
    imagePalette->palPalEntry[i].peGreen=i;
    imagePalette->palPalEntry[i].peBlue=i;
  }

  for (int i=thresholdColor; i<256; i++)
  {
    imagePalette->palPalEntry[i].peRed=255;
    imagePalette->palPalEntry[i].peGreen=255;
    imagePalette->palPalEntry[i].peBlue=0;
  }

  displayBitmap->Palette=CreatePalette(imagePalette);
  delete imagePalette;
}
*///---------------------------------------------------------------------------
void __fastcall TFormSceneInspectorForm::displaySlice()
{
  if (!imageSet)
    return;

  if (displayBitmap)
    delete displayBitmap;

  displayBitmap=new Graphics::TBitmap();

  int thresholdColor;

  if (marchingCubesScene)
    if (marchingCubesScene->getSelectedObject())
      thresholdColor=marchingCubesScene->getSelectedObject()->getThresholdIntensity();
    else
      thresholdColor=255;
  else
    thresholdColor=255;

  if (displayBitmap)
  {
    unsigned int width=imageSet->getWidth();
    unsigned int height=imageSet->getHeight();
    unsigned int widthIndex=0, heightIndex=0;
    unsigned char* ptr;
    int colorIndex=0;

    displayBitmap->Width=imageSet->getWidth();
    displayBitmap->Height=imageSet->getHeight();
    displayBitmap->PixelFormat=pf8bit;
    displayBitmap->HandleType=bmDIB;

    LOGPALETTE *imagePalette= (LOGPALETTE*) new char[ sizeof(LOGPALETTE) + sizeof(PALETTEENTRY) * 256];
    imagePalette->palVersion = 0x300;
    imagePalette->palNumEntries = 256;


    for ( ; colorIndex<thresholdColor; colorIndex++)
    {
      imagePalette->palPalEntry[colorIndex].peRed  =colorIndex;
      imagePalette->palPalEntry[colorIndex].peGreen=colorIndex;
      imagePalette->palPalEntry[colorIndex].peBlue =colorIndex;
    }
    for ( ; colorIndex<256; colorIndex++)
    {
      imagePalette->palPalEntry[colorIndex].peRed  =255;
      imagePalette->palPalEntry[colorIndex].peGreen=255;
      imagePalette->palPalEntry[colorIndex].peBlue =0;
    }

    displayBitmap->Palette=CreatePalette(imagePalette);
    delete imagePalette;


    for (heightIndex=0 ; heightIndex<height; heightIndex++)
    {
      ptr=(unsigned char*) displayBitmap->ScanLine[heightIndex];
      for (widthIndex=0 ; widthIndex<width; widthIndex++)
      {
        *ptr=imageSet->getSlice(TrackBar1->Position)->getVoxelGray(widthIndex,heightIndex);
        ptr++;
      }
    }

    Image1->Canvas->Draw(0,0, displayBitmap);
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormSceneInspectorForm::TrackBar1Change(TObject *Sender)
{
  TrackBar1->Hint="Slice "+AnsiString(TrackBar1->Position + 1);

  displaySlice();
}
//---------------------------------------------------------------------------
void __fastcall TFormSceneInspectorForm::Image1MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  if (!imageSet || !marchingCubesScene)
    return;

  if (!marchingCubesScene->getSelectedObject())
    return;

  if (Shift.Contains(ssLeft))
  {
    marchingCubesScene->getSelectedObject()->setThresholdIntensity(imageSet->getSlice(TrackBar1->Position)->getVoxelGray(X,Y));
    displaySlice();
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormSceneInspectorForm::Image1MouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
  if (!imageSet || !marchingCubesScene)
    return;

  if (!marchingCubesScene->getSelectedObject())
    return;

  if (Shift.Contains(ssLeft))
  {
    marchingCubesScene->getSelectedObject()->setThresholdIntensity(imageSet->getSlice(TrackBar1->Position)->getVoxelGray(X,Y));
    displaySlice();
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormSceneInspectorForm::FormResize(TObject *Sender)
{
  Panel7->Top=Panel6->Top+Panel6->Height+2;
  Panel7->Height=Image1->Top+Image1->Height+4;
  Memo1->Left=2;
  Memo1->Top=Panel7->Top+Panel7->Height+2;
  ClientWidth=Panel1->Width+4;
  ClientHeight=Memo1->Top+Memo1->Height+2;
}
//---------------------------------------------------------------------------

