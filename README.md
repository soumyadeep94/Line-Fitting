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
 
 
  
  
   
       
  
  
  
  
	
	
  
  



