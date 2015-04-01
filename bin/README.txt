
How to install and run Visualize?
- Double click on Visualize.exe. If OpenGL library is installed on your system it will run successfully.
- Otherwise rename Opengl32-2.dll to OpenGL32.dll and try runing Visualize again. It should work this time.

How to use the program?
- Click on the "Load image set" button
- Load an Analyze file (a file with hdr extension). You can use samples in the testData folder.
- Lots of buttons will be enabled and an image representing the middle slice will appear
- Click on "Add object" 
- Under "Scene Objects" list you will see a checked item named "Object 0", highlight by clicking on it
- When an object in the list is selected, a threshold can be defined for it. Clicking on the image will use pixel value as threshold. All the voxels with a threshold value equal or greater than the selected threshold will be highlighted (yellow) to identify the portion of the object in the slice.
- If your dataset is suitable for adding multiple thresholds (ie: skin, brain etc) continue adding objects and define thresholds.
- You can browse slices using the trackbar above the slice image.
- Once objects are defined click on "Generate 3D objects" button and wait for a while. The object(s) will be constructed and displayed in the "Visualize - Reconstructed objects" window.
- When an object is selected you may click on "Modify object's properties" button and modify objects name, color, transparency, shininess properties.
- Use your mouse to rotate object(s) (keep right/left button pressed and move mouse)
  
  
