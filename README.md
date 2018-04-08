# **Line-Fitting using RANSAC Algorithm**

RANSAC METHOD
---

- RANSAC or (*RANDOM SAMPLE CONSENSUS*) is an iterative method to estimate parameters of a mathematical model from a set of observe data which contain the outliers.
- The randomly chosen points are called *hypothetical inliers* and all other points are tested against this fitted model.
- Those points that fit the estimated model well are considered as a part of the consensus set.
- The estimated model is good if sufficiently many points are classified as inliers.
- This procedure is repeated for a fixed number of times, every time iteration producing a new model.

  ***Calculation of number of iterations(N)***
  *N* is chosen high enough to ensure the probability *p*(usually set to 0.99) that at least one of the sets of the random samples does not include an outlier. Let *u* represent that any selected data point is an inlier *v = 1 - u*, the probablity of observing an outlier.
  
  
  N iterations of the number of points denoted m are required, where   
	      **1-p = (1-u)<sup>m</sup>** 
				
  **N = log(1-p)/log(1-(1-v)<sup>m</sup>**
  
  ***3D Line***
  
  
  ![alt text](https://github.com/soumyadeep94/Line-Fitting/blob/master/3d%20Line.gif)
  
  Let *r<sub>0</sub>* and *r* be the position vectors for P<sub>0</sub> and P respectively. Let us define *a* to be a vector with representation *P<sub>0</sub>P*.  *v* is the vector parallel to the line. We can write *r* as
  
  *r = r<sub>0</sub> + a*
  
  Since vector *a* and *v* are parallel. So, *a = tv*
  
  Thus the vector form of the equation of the line is   ***r = r<sub>0</sub> + tv***
  
  **(x<sub>0</sub>,y<sub>0</sub>,z<sub>0</sub>)** is the **position vector** of the line.
  ***(a,b,c)*** is the **direction vector** of the line.
  
 ## **Distance of a point from line**
 
 The vector v along the line specified by 2 points *x<sub>1</sub> = (x<sub>1</sub>, y<sub>1</sub>, z<sub>1</sub>)*, *x<sub>2</sub> = (x<sub>2</sub>, y<sub>2</sub>, z<sub>2</sub>)* is given by
 
 ![alt text](https://github.com/soumyadeep94/Line-Fitting/blob/master/vector_line.gif)
 
 The squared distance between a point on the line with parameter t and a point x<sub>0</sub> = (x<sub>0</sub>, y<sub>0</sub>, z<sub>0</sub>) is
 
 d<sup>2</sup> = [(x<sub>1</sub> - x<sub>0</sub>) + (x<sub>2</sub> - x<sub>1</sub>)t]<sup>2</sup> + [(y<sub>1</sub> - y<sub>0</sub>) + (y<sub>2</sub> - y<sub>1</sub>)t]<sup>2</sup> + [(z<sub>1</sub> - z<sub>0</sub>) + (z<sub>2</sub> - z<sub>1</sub>)t]<sup>2</sup>
	
Minimizing the distance, solving for t and using the vector quadruple product (AxB)<sup>2</sup> = A<sup>2</sup>B<sup>2</sup> - (A.B)<sup>2</sup>, we obtain distance,


d = |(x<sub>0</sub> - x<sub>1</sub>) x (x<sub>0</sub> - x<sub>2</sub>)|/|(x<sub>2</sub> - x<sub>0</sub>)|

## ALGORITHM
- We first generate indices vector of the size same as that of the dataset. This
vector will extract the points from the dataset. We extract the first two points
and consider them as *hypothetical inliers(maybe_pts)* as only 2 points are
sufficient to describe a line. The rest of the points are said to be the *test
points(test_pts)*.
- We shuffle this indices vector each iteration randomly so as to get different
hypothetical inliers each time.
- From the hypothetical inliers, we calculate the **position vector** and the
**direction vector** of the estimated line model.
- We, then test all the test points over this estimated model and calculate the
distance of it from this line using the formula shown above.
- If the distance is less than the threshold value, it is classified as inliers or else
as outliers and we calculate the **inlier ratio** for that model.
- We calculate the **average of the sum of all the test points** for this model.
- We iterate this algorithm for a fixed number of N, whose value was calculated
previously. We stop this iteration if we have obtained sufficient number of
inliers
- If we don’t get sufficient number of inliers till the end of all iterations, we say
**“No Model Found!!!”**.

## SOFTWARE
- [Qt 5.9](https://www1.qt.io/qt5-9/)

## DEPENDENCIES
- [Eigen](http://eigen.tuxfamily.org/index.php?title=Main_Page#Download)
   (Header only matrix math library)
   
 ## REFERERENCES
 - To know more about equation of lines click [here](http://tutorial.math.lamar.edu/Classes/CalcIII/EqnsOfLines.aspx)
 - To find more about the math regarding distance of point from line..let's dive [here](mathworld.wolfram.com/Point-LineDistance3-Dimensional.html)
 - I recommend [Alexey Abramov's Blog post](https://salzis.wordpress.com/2014/06/10/robust-linear-model-estimation-using-ransac-python-implementation/) regarding the Python implementation of Line Fit estimation
	
	
	
 
 
  
  
   
       
  
  
  
  
	
	
  
  



