# TODO LIST

## CONSTRAINTS ##

* Limit generator engine to the stuff that requires perpixel iterative calculation

## IMMIDIATE ##

* Restructure code so that multiple different types of fractals can be rendered
* Have a systems to properly set and retrieve the values of a uniform
* Changing the way stuff is rendered depending on the user's choise

* Render Julia Sets
* Render Mandelbrot Sets
* Render Newton's Fractals
* Render Burning Ship Fractal

## AFTER BURNER ##

* Add on screen UI for ease of use
* Add UI to control the varius variables
* Add Ability to change the way stuff is rendered
* Animate the moving of the camera

## MAYBE ##

* Add multiple Different Color Schemes
* Allowing users to define their own color themes for stuff
* Add blurring or dithering to remove the bs pixelation that occurs at very high zoom levels
* Find someway to make this stuff infinitely zoomable or some stuff

## BUGS ##

* The scaling is not uniform throughout all the zoom levels [works now]


## Arch ##

Keep all state as global, initialize the global state.
A Fractal is basically a mathematical computation happening in gpu, so the only cpu thing is uniform values
this means they will have to handle their own ui. cool

[ Load Assets ]
[ Initilize Configs ]
[ Connect with GPU ]
[ Start Rendering ]
[ Free Assets ]

What does a fractal contain????

A Shader for computation, 
a Few Uniforms to control the data,
Config that can be edited by elements

you know what to use here, question is do you want to use it??
OH HELL YEAH WHY IN THE WORLD NOT!!!

!!!

OK LETS DO SOMETHING, LETS HAVE GLOBAL VARIABLES FOR STUFF OK!!
DON'T BE FANCY JUST GET THIS DONE, LET EXTENSIBILITY BURN AND DIE!!
CLEAN CODE IS A MYTH AND YOU ARE ONLY ONE MAN!!

!!!

