
#include<iostream>
#include<stdio.h>
#include<math.h>
#include<time.h>
#include<Eigen/Dense>
#include<algorithm>
#include<utility>

using namespace std;
using namespace Eigen;

struct line{
    Vector3d pos_vec;
    Vector3d Dir_vec;
    double points_avg;
    double inlier_ratio;
};

double calculate_dist(Vector3d P, Vector3d Q, Vector3d R)
{
    Vector3d num_vec,den_vec;
    double numerator, denominator, result;
   num_vec = (R - P).cross(R-Q);
   numerator = num_vec.norm();
   den_vec = Q -P;
   denominator = den_vec.norm();
   result = numerator/denominator;

   return result;
}

line line_fitting(double,double, vector<Vector3d>& points);


int main()
{

//parameters

double ransac_thresh = 3.0;
float ransac_ratio = 0.6;
int n_samples = 100;

//line fitting function declaration



srand(time(NULL));
//set the sample data

//double m = 0.05;
float random = 0.5f;
float noise = 0.f;

const static int q = 15;
const static float c1 = (1 << q) - 1;
const static float c2 = ((int)(c1 / 3)) + 1;
const static float c3 = 1.f / c1;

random = ((float)rand()/(float)RAND_MAX + 1);
noise = (2.f * ((random * c2) + (random * c2) + (random * c2)) - 3.f * (c2 - 1.f)) * c3;
float noise_scale = 2.0;

//vector<Vector3d>points;
//Vector3d ind;
//Vector3d Noise(noise*noise_scale,noise*noise_scale,noise*noise_scale);

//for(int i = 0;i<n_samples;i++)
//{

//    int j=0;
//    while(j<3)
//    {
//        if(j ==0)
//            ind(0) = i;
//        if(j == 1)
//            ind(1) = pow(ind(0)+1,2);
//        if(j == 2)
//            ind(2) = 2*(ind(1) + 1);
//        j++;
//    }
//        points.push_back(ind);
//}
//for(int j=0;j<points.size();j++)
//{
//    if(j > 40 && j<50)
//        points.at(j) = points.at(j) + Noise;
//    cout<<points.at(j).transpose()<<endl;

//}

vector<Vector3d>points;
Vector3d p1 = Vector3d(1,1.5,0.5);
Vector3d p2 = Vector3d(2,3,1);
Vector3d p3 = Vector3d(4,0,19);
Vector3d p4 = Vector3d(6,9,-3);

points.push_back(p1);
points.push_back(p2);
points.push_back(p3);
points.push_back(p4);




//line fitting
line new_line = line_fitting(ransac_ratio,ransac_thresh,points);
Vector3d Dir = new_line.Dir_vec;
Vector3d Pos = new_line.pos_vec;
cout<<"Direction vector is: "<<Dir(0)<<" "<<Dir(1)<<" "<<Dir(2)<<endl;
cout<<"Position vector of the line is: "<<Pos(0)<<" "<<Pos(1)<<" "<<Pos(2)<<endl;
cout<<"The average sum of points is: "<<new_line.points_avg<<endl;
cout<<"The inlier ratio is: "<<new_line.inlier_ratio<<endl;
return (0);
}

//function for line fitting


line line_fitting(double ransac_ratio, double ransac_thresh,vector<Vector3d>& points)
{
    line l;
    int n_samples = points.size();
random_device rd;
mt19937 g(rd());
double ratio = 0.0;

  vector<int>indices;



for(int i = 0;i<n_samples;i++)
    indices.push_back(i);


double pt1,pt2;
double pro = 0.99;  //probability that at least 1 subset of the data does not contain any outliers
double ransac_iter = log(1 -pro)/log(1 - pow(ransac_ratio,3));
//perform ransac iterations
for (int it = 0;it<(int)ransac_iter;it++)
{
    cout<<"it "<<it<<endl;
    int p=0;
     Vector3d P,Q, dir_vec;



    vector<vector<double>>maybe_pts;
    vector<vector<double>>test_pts;
    shuffle(indices.begin(),indices.end(),g);
    //cout << indices.size()<< endl;
    for(int j=0;j<indices.size();j++)
    {
        vector<double>maybe;
        vector<double>test;
        if(j<2)
        {
            int idx1 = indices.at(j);
            while(p<3)
            {
               //pt1 = data[idx1][p];
                pt1 = (points.at(idx1))(p);
               maybe.push_back(pt1);
              // cout<<maybe.at(p)<<endl;
               p++;


            }
            maybe_pts.push_back(maybe);

        }
        p = 0;
        if(j>= 2)
        {
            int idx2 = indices.at(j);
            while(p<3)
            {
                //pt2 = data[idx2][p];
                pt2 = (points.at(idx2))(p);
                test.push_back(pt2);
                p++;
            }
            test_pts.push_back(test);
        }
    }

    for(int i=0;i<2;i++)
    {
        if(i==0)
        {
            P(0) = maybe_pts.at(i).at(0);
            P(1) = maybe_pts.at(i).at(1);
            P(2) = maybe_pts.at(i).at(2);
            cout<<"P0: "<<P(0)<<endl;
            cout<<"P1: "<<P(1)<<endl;
            cout<<"P2: "<<P(2)<<endl;

        }
        if(i==1)
        {
            Q(0) = maybe_pts.at(i).at(0);
            Q(1) = maybe_pts.at(i).at(1);
            Q(2) = maybe_pts.at(i).at(2);
            cout<<"Q0: "<<Q(0)<<endl;
            cout<<"Q1: "<<Q(1)<<endl;
            cout<<"Q2: "<<Q(2)<<endl;


        }
    }
   dir_vec = Q - P;
  // dir_vec.normalize();



  vector<double>x_outliers;
  vector<double>y_outliers;
  vector<double>z_outliers;
  vector<double>out_dist;
  vector<double>points_dist;
  Vector3d test_points;
int num = 0;
double dist;
double Sum = 0;
for(int id = 0;id<test_pts.size();id++)
{
   double x0 = test_pts.at(id).at(0);
   double y0 = test_pts.at(id).at(1);
   double z0 = test_pts.at(id).at(2);
   cout<<"x: "<<x0<<" y:"<<y0<<" :z "<<z0<<endl;
   test_points(0) = x0;
   test_points(1) = y0;
   test_points(2) = z0;
   //calculate the distance from point to the model
  dist = calculate_dist(P,Q,test_points);
  points_dist.push_back(dist);
  cout<<"dist: "<<dist<<endl;
   if(dist <= ransac_thresh)
   {
//       x_inliers.push_back(x0);
//       y_inliers.push_back(y0);
//       z_inliers.push_back(z0);
       num++;


   }
   if(dist > ransac_thresh)
   {
       out_dist.push_back(dist);
       x_outliers.push_back(x0);
       y_outliers.push_back(y0);
       z_outliers.push_back(z0);

   }
}
for(int i=0;i<points_dist.size();i++)
{
    Sum += points_dist.at(i);
}
double avg = Sum/n_samples;

cout<<"avg is: "<<avg<<endl;
for(int i=0;i<x_outliers.size();i++)
{
    cout<<"outliers: "<<x_outliers.at(i)<<" "<<y_outliers.at(i)<<" "<<z_outliers.at(i)<<endl;
    cout<<"outliers distance: "<<out_dist.at(i)<<endl<<endl;

}
num = num+2;
  // cout<<"num: "<<num<<endl;
//   //if the model is better-cache it
   if(num/(float)n_samples > ratio)
   {
       ratio = (num)/(float)n_samples;
       l.Dir_vec = dir_vec;
       l.pos_vec = P;
       l.inlier_ratio = ratio;
       l.points_avg = avg;


   }
   cout<<"Inlier ratio = "<<ratio<<endl;



   if(num > n_samples*ransac_ratio)
   {
       cout<<"The model is found"<<endl;
       break;
   }
   else if(num < n_samples*ransac_ratio && it == (ransac_iter-1))
   {


       cout<<"Model not found!!!"<<endl;
   }


}
return l;
}





