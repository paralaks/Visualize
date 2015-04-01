//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("surfaceVisualizerProject.res");
USEFORM("TSceneInspectorForm.cpp", FormSceneInspectorForm);
USEFORM("TObjectPropertiesForm.cpp", FormObjectPropertiesForm);
USEFORM("TClippingVolumePropertiesForm.cpp", FormClippingVolumePropertiesForm);
USEFORM("TTexturedSurfacePropertiesForm.cpp", FormTexturedSurfacePropertiesForm);
USEUNIT("CAnalyze.cpp");
USEUNIT("CAnalyzeLibrary.cpp");
USEUNIT("CSlice.cpp");
USEUNIT("CVoxel.cpp");
USEUNIT("MarchingCubesScene.cpp");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TFormSceneInspectorForm), &FormSceneInspectorForm);
                 Application->CreateForm(__classid(TFormObjectPropertiesForm), &FormObjectPropertiesForm);
                 Application->CreateForm(__classid(TFormClippingVolumePropertiesForm), &FormClippingVolumePropertiesForm);
                 Application->CreateForm(__classid(TFormTexturedSurfacePropertiesForm), &FormTexturedSurfacePropertiesForm);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
