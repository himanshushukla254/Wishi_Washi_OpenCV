# wishi-washi
The age old PS game using opencv library in C++. 

Please Youtube the topic to understand what this game does.
To mimic the game, I find the difference between two frames. Difference here means the difference between the pixel values.
The absdiff() return me a 2D array of all the differences. Each value is then compared to the threhold to see if we really had some movement in the game. If the value is higher than than the threshold, we make that pixel visible in the screen while other pixel remains black. In this manner we compare the differences and get the desired screen.

