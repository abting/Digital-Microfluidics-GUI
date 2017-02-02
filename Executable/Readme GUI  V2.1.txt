This README document was made to give a few tips on using the 
software and some explanations of some of the functions.


/***Create New Layout***/
-When creating a new layout, make sure that two electrodes are 
not connected to the same contact pad
-Make sure you save your layout

/***Saving Layout***/
- When saving your layout use a unique name or identifier
i.e. Template-1-Layout.txt

/***Opening Layout***/
-When opening your layout, ENSURE that you are opening a text
file that has layout information
-This is why you should clearly label your layout when SAVING it
i.e. open -> Template-1-Layout.txt



/***Saving Sequence***/
-When you're saving a sequence/session, make sure you that you use 
a name or identifier that links it with its layout file, this
is to prevent mismatch and include the mode as well
-Save sequence will save the information depending on which mode you're
in. If in droplet mode, it will save the droplet session, if in electrode
mode, it will save the electrode session

i.e. Template-1A-Dmode-Sequence.txt

/***Opening Sequence***/
When you open a sequence/session, Make sure you are choosing 
a sequence text file (properly labeled). Furthermore, make sure 
you match the sequence/session with the proper layout
i.e. open -> Template-1A-Dmode-Sequence.txt

/***Arduino***/
Connect the Arduino to enable the start button


DROPLET MODE

/***Dispense***/
-To dispense, click on an electrode that has a droplet on it
Then, click on the electrodes that you want the droplet to dispense
on, these electrodes should be in adjacent to one another
-Click cancel to abort dispensing

/***Split***/
To split a droplet, click on an electrode that has a droplet,
Then click on the two adjacent electrodes that you want the 
droplet to split on
-Click cancel to abort dispensing

/***Preview***/
-Click Preview to watch a preview of your experiment
-The preview speed is set to 500ms

/***Start Button/Start experiment***/
-The start button will only be enabled if Arduino is connected
-Click start to begin your experiment
-Click cancel to pause/stop your experiment
-Use the slider to choose the starting point of your experiment
i.e. you can start your experiment at time slot:0   or time slot: 15
The information will begin sending from wherever the slider is set



ELECTRODE MODE
This mode gives the user more control over each electrode and
it very simple to use. No droplet information is being recorded

/***Turn On Electrode***/
-At the given time slot, select the electrodes you want to be turned on
-Once you're done, click the increment button or hit spacebar 
to move to the next time slot

/***Turn Off Electrode***/
Same as turn on, but it turns off the given electrode

/***Real-Time Actuation***/
-When the box is checkmarked, click on any electrode and it will 
turn on in real-time
-This can be very useful for debugging

/***Preview and Start***/
Same concept as in Droplet MODE

**Very IMPORTANT***
-The code does allow you to make edits to your path in the past,
however, it is important to be very cautious when doing so, there are
very specific cases that will cause the program to crash and this part
of the code still requires some more debugging.
If you are to make edits in the past, SAVE YOUR WORK.

***IMPORTANT***
-Bare in mind that droplet mode and electrode mode are two separate 
modes on the same chip
-You can move back and forth between the two, but they have no 
connection to one another
-It is highly suggested that you save your work at all times
-Please write down all suggestions, comments improvements that you 
would like to see in the software and send it to us.


If you have any questions, e-mail me or Abtin:
kaleem.corbin@gmail.com
abtinghoudssi@gmail.com