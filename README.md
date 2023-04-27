# CPPAssignment Update 27-Apr-23 (Kindly Redowload the Build to Play the Updated Version)

Architecture
1. The goal was to create a decoupled module as much as possible. The attempt is to keep most of the processing in CPP and Use Blueprints only for Data as much as possible. 
2. Destroyables : An Interface that is implemented by the Obstacles and will be implmented by the projectiles. Havin an Interface allows us to ensure that we dont store hard references to anything and only focus on behaviours if a particular collision Actor implments the interface. 
3. Observer Pattern: The Move Speed is transmitted using Delegates to ensure that a common speed is maintained. Further Computational Changes are made by the actors themselves. 
4. Object Pooling: The Level Manager resuses Static Mesh Components and Will Generate the necessary number in its constructor. Thee Mesh Componenets are reused and switch between meshes provided in an Array stored by the Level Manager. 

Feature Creation
The Game Currently Features the following capabilities. 
1. Scoring based on Distance Covered.
2. 3 Lives are provided. 
3. A small safe time is provided when you colllide with an Obstacle
4. Save and Load the High Scores Which are Showcased by the Start Screen
