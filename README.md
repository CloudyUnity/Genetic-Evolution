This is a C++ SDL2 project where little creatures all have their own neural network brains    
After running a simulation it will pick the best creatures of the generation and allow them to reproduce for the next generation  
Each creature will have a mutated brain of a creature from the previous generation  
Run on release mode for the best performance  

Make sure the SDL2-2.28.4/lib/_x64 library in in the environment path variables otherwise you may get an error: "SDL2.dll cannot be found"  
Restart Visual Studio after doing this  
 
Modify the settings in "EvoProj V2.cpp"  

How the brains work:  
  - Brains are composed of input, internal and output neurons  
  - Neurons have connections with each other of varying weights  
  - Every frame the input neurons will trigger based on what type of input neuron they are  
  - Some inputs include sight rays, age, oscillator, current rotation, distance to border and random  
  - Internal neurons exist to allow more complex functions to take place. They can have any number of inputs and outputs  
  - Output neurons cause the creature to move or rotate based on whether the input reaches a certain threshold  
  - Brains are defined by a list of ints, each being a connection between two neurons and a weight  
  - Mutations involve changing random bits of the genome  
  - Creatures are rewarded based on how many gates they pass through  

Controls:  
  - You can pan the camera around by holding the mouse wheel  
  - Zoom in/out by scrolling the mouse wheel  
  - Click on a creature to view its brain at the top left of the map   
  - Blue squares are inputs, grey are internal, red are outputs. It's not readable enough to be useful but I was finished the project before I improved it  
  - You can also see the sight rays of a selected creature  
  - Use the pause and speed up buttons on the GUI to change the timespeed    
  - The restart button restarts the simulation and gives creatures new random brains  
  
![image](https://github.com/user-attachments/assets/10c73e99-63ba-43d6-8430-4cf651f38e10)
![image](https://github.com/user-attachments/assets/f6a4e566-a049-4ddb-9010-ab3622e80f9b)
