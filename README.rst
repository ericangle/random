.. role:: raw-math(raw)
    :format: latex html

random
=============

Problem Statement:

* From a text file, read in the dimension of the space, and a series of points, each with a corresponding volume.

* For each point, (1) Construct a hypercube "box" around the point with the specifed volume, such that each vertex of the unit hypercube is moved the same fractional distance to the point, and (2) generate (a) 3 random points inside the box, and (b) 1 random point inside the unit hypercube, and outside the box.

* Output the coordinates of all generated points to a text file.
 
Some assumptions/simplifications made:

* The input text file will be in tab delimited form.

* Random numbers should be generated from a uniform distribution.

* Volume is greater than 0 and less than 1.

* Have hard coded 2BI and 2BII to generate 3 and 1 points, respectively. Could make this more generic.

Run Tests
------------------

To run the tests, ...
