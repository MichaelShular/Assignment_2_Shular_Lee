Assignment 2 

Doodle Jump Demo

Michael Shular 101273089
Daekoen Lee 101076401

This program is to show our understanding of ogre with Doodle Jump

Controls
@note: move player with A and D
@note: press the on screen button to reset the game
@note: quit application Esc

GamePlay
@note: If player moves outside of the screen view the will appear on the other side
@note: Reach the checkered finish line to win
@note: Fall off screen will lose you the game

Installing
@note: Replace "Examples.material" script in ...ogre-sdk-v2.1\Samples\Media\materials\scripts with the new "Examples.material" which is in the project's media folder
@note: VVVVV In the project properties added the three edits below VVVVV
@note: First in "C/C++, General, Additional Include Directories" click and edit a new line to "$(SolutionDir)include"
@note: Second in "Linker, General, Additional Library Directories" click and edit a new line to "$(SolutionDir)lib\Winx64-visualStudio"
@note: Third in "Linker, Input, Additional Dependencies" click and edit a new line to "irrKlang.lib"