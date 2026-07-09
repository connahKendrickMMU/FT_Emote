# FT Emote
In this focus topic you will be using a finite-state-machine to add emotes to a character, I have created a base state machine for the wall controller for reference.

Use buttons 1,2 or 3 to emote. Walk along the platform with the console open and you will see the pause state trigger before the game begins.

## Overview
In this you are building a series of [Hole in the Wall](https://www.bbc.co.uk/programmes/p005fspv) style game. Where using an animation to get through a gap

## Where to find the relevant scripts

You will be developing your own script, but you should use the WallController and WallControllerBaseState_??? scripts.

## Task
Try to implement a state machine for the character:
- You will need to have more temple function for the input bindings, 
- Implement states for idle, moving and animating
## Hints  

As colliders are key for this **alt+c** will show colliders in the viewport. 

Make full use of the WallController and **WallControllerBaseState** as references. The state should be just a base **UObject** class.

## Changes from base project

# Animation
Animations where created by duplicating the Idle Animation and editing it in the sequencer. Then right click->Make animation Montage.
I also remove the IK for the foot floor attachment.
## Challenges

### Easy
- Loop the montages so they don't end until the player moves.
- Record the number of walls in a row the Player have survived, in one go.
- Ensure a different wall spawns each time (same wall wont appear twice in a row).

### Medium
- Allow the player to move slowly during the emote for slight position correct.
- Using the record of number of walls survived, increase the speed, resetting when players lose.
- Using the record of number of walls survived, decrease the pause phase, resetting when players lose.

### Hard 
- Try creating your own animation and binding it to the player with a new wall using just a basic blueprint.
- Research into the animation transitions on how to smooth the system, or import mixamo characters.
- Identify feedback techniques for the players.

# Reference
Content is made by Connah Kendrick (Connah.Kendrick@mmu.ac.uk) using the Unreal Engine Third Person Template for the MMU 1st year Game Mechanics Module taught to both Game Development and Game Design Students. 

