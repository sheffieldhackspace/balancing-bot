You'll first need to upload **deadbands.ino** to the Nano.

Optimize the parameters **m1ndb**, **m1pdb**, **m2ndb**, **m2pdb** (as instructed in the code) so that the motors barely run in both directions. Lay the robot flat to find the values for the motors going in one direction, and then flip it over to get the values going in the opposite direction.

If you're using 3xAA batteries then subtract 2 from these values and put them into **../ember/ember.ino**, and if you're using Li-ion batteries then subtract 10 from them.

You may need to tinker with the paramaters a bit to get the optimum values for smooth balancing (once you've uploaded them into **ember.ino** that is). If there's a slight rotational drift then trying adding 1 to both **m1ndb** and **m2ndb** (or subtracting 1 from **m2ndb** and **m2pdb**).
