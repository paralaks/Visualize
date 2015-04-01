//---------------------------------------------------------------------------

#ifndef TTexturedSurfacePropertiesFormH
#define TTexturedSurfacePropertiesFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>

#include "MarchingCubesScene.h"

//---------------------------------------------------------------------------
class TFormTexturedSurfacePropertiesForm : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TGroupBox *GroupBox1;
        TRadioButton *RadioButton1;
        TRadioButton *RadioButton2;
        TRadioButton *RadioButton3;
        TStaticText *StaticText1;
        TScrollBar *ScrollBar1;
        TLabel *Label1;
        TButton *Button1;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
private:	// User declarations

  MarchingCubesScene *marchingCubesScene;

public:		// User declarations
        __fastcall TFormTexturedSurfacePropertiesForm(TComponent* Owner);

  void __fastcall setMarchingCubesScene(MarchingCubesScene*);

};
//---------------------------------------------------------------------------
extern PACKAGE TFormTexturedSurfacePropertiesForm *FormTexturedSurfacePropertiesForm;
//---------------------------------------------------------------------------
#endif
