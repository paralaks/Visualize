//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TTexturedSurfacePropertiesForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormTexturedSurfacePropertiesForm *FormTexturedSurfacePropertiesForm;
//---------------------------------------------------------------------------
__fastcall TFormTexturedSurfacePropertiesForm::TFormTexturedSurfacePropertiesForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormTexturedSurfacePropertiesForm::FormCreate(TObject *Sender)
{
  Constraints->MaxWidth=450;
  Constraints->MinWidth=450;
  Constraints->MaxHeight=168;
  Constraints->MinHeight=168;

  Button1->Left=(Width-Button1->Width)/2;
}
//---------------------------------------------------------------------------
void __fastcall TFormTexturedSurfacePropertiesForm::Button1Click(
      TObject *Sender)
{
  Visible=false;        
}
//---------------------------------------------------------------------------
void __fastcall TFormTexturedSurfacePropertiesForm::setMarchingCubesScene(MarchingCubesScene* m)
{
  marchingCubesScene=m;
}
