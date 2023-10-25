# Emergent steering behaviors #

Demonstration of blending several steering behaviours together to form emergent behaviours such group evasion and flocking. The behaviours used are seek, flee, cohesion, avoidance, and wall avoidance. Each is blended in order of importance to form a final force that is applied to the entities.

### To Run on Windows ###

* Install SDL2
* ```mkdir build``` in the project folder
* Enter build and run ```cmake -G "NMake Makefiles" ..```
* run ```nmake```
* Copy params.txt into build folder 

### On Running ###

* Pressing 1 will use seek
* Pressing 2 will use flee

### Result ###
Seek

https://github.com/Jaromc/emergent_steering_behaviours/assets/89912906/57cb084a-88b8-4fcf-907e-c71e7be304c3

Flee

https://github.com/Jaromc/emergent_steering_behaviours/assets/89912906/c4716643-90f5-4d2a-bb5c-d937bda0d93c

