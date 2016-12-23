
/////////////////////////////////////////
//prjoct name : polyfit_gray_pixel.cpp //
//Author        : Oopscheng            //
//Date          : 2016/12/21           //
/////////////////////////////////////////
 

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstring>
#include <iomanip>
#include <cmath>
#include <sstream>

using namespace cv;
using namespace std;
int bintodec(int x);
int main(int argc, char **argv){
	// Mat image = imread("ig31.jpg", CV_LOAD_IMAGE_COLOR);
	Mat imagegray = imread("ig31.jpg", CV_LOAD_IMAGE_GRAYSCALE );//always convert image to the grayscale
	printf("imagegray.cols = %d\n",imagegray.cols );
	printf("imagegray.rows = %d\n",imagegray.rows );
	int  array[imagegray.rows] = {0};
	for (int i = 0; i < imagegray.rows; i++){
		for (int j = 0; j < 1920; j++){
			int gray_value = (int)imagegray.at<uchar>(i,j);
			array[i] += gray_value;
		}
	}
	
	for (int i = 0; i < imagegray.rows ; i++){      
		array[i] = array[i]/1920;
		printf("array[%d]=%3d\n",i,array[i]);
	}


	
	////////////
	//polyfit //
	////////////
	 
	int i,j,k,n,N;
	cout.precision(4);                        //set precision
	cout.setf(ios::fixed);
	cout<<"\nEnter the no. of data pairs to be entered:\n";        //To find the size of arrays that will store x,y, and z values
	// cin>>N;
	N=imagegray.rows;
	double x[N],y[N];
	cout<<"\nEnter the x-axis values:\n";                //Input x-values
	for (i=0;i<N;i++){
		x[i] = i;
		printf("x[i] = %f\n",x[i]);
		// cin>>x[i];
	}
	cout<<"\nEnter the y-axis values:\n";                //Input y-values
	for (i=0;i<N;i++){
		y[i]=array[i];
		printf("y[i] = %f\n",y[i]);
		// cin>>y[i];
	}
	cout<<"\nWhat degree of Polynomial do you want to use for the fit?\n";
	cin>>n;                                // n is the degree of Polynomial 
	double X[2*n+1];                        //Array that will store the values of sigma(xi),sigma(xi^2),sigma(xi^3)....sigma(xi^2n)
	for (i=0;i<2*n+1;i++){
		X[i]=0;
		for (j=0;j<N;j++)
			X[i]=X[i]+pow(x[j],i);        //consecutive positions of the array will store N,sigma(xi),sigma(xi^2),sigma(xi^3)....sigma(xi^2n)
	}

	double B[n+1][n+2],a[n+1];            //B is the Normal matrix(augmented) that will store the equations, 'a' is for value of the final coefficients
	for (i=0;i<=n;i++)
		for (j=0;j<=n;j++)
			B[i][j]=X[i+j];            //Build the Normal matrix by storing the corresponding coefficients at the right positions except the last column of the matrix
	
	double Y[n+1];                    //Array to store the values of sigma(yi),sigma(xi*yi),sigma(xi^2*yi)...sigma(xi^n*yi)
	for (i=0;i<n+1;i++){    
		Y[i]=0;
		for (j=0;j<N;j++)
		Y[i]=Y[i]+pow(x[j],i)*y[j];        //consecutive positions will store sigma(yi),sigma(xi*yi),sigma(xi^2*yi)...sigma(xi^n*yi)
	}
	
	for (i=0;i<=n;i++)
		B[i][n+1]=Y[i];                //load the values of Y as the last column of B(Normal Matrix but augmented)
	n=n+1;                //n is made n+1 because the Gaussian Elimination part below was for n equations, but here n is the degree of polynomial and for n degree we get n+1 equations
	cout<<"\nThe Normal(Augmented Matrix) is as follows:\n";    
	for (i=0;i<n;i++)            //print the Normal-augmented matrix
	{
		for (j=0;j<=n;j++)
			cout<<B[i][j]<<setw(16);
		cout<<"\n";
	}    
	for (i=0;i<n;i++)                    //From now Gaussian Elimination starts(can be ignored) to solve the set of linear equations (Pivotisation)
		for (k=i+1;k<n;k++)
			if (B[i][i]<B[k][i])
				for (j=0;j<=n;j++)
				{
					double temp=B[i][j];
					B[i][j]=B[k][j];
					B[k][j]=temp;
				}
	
	for (i=0;i<n-1;i++)            //loop to perform the gauss elimination
		for (k=i+1;k<n;k++)
			{
				double t=B[k][i]/B[i][i];
				for (j=0;j<=n;j++)
					B[k][j]=B[k][j]-t*B[i][j];    //make the elements below the pivot elements equal to zero or elimnate the variables
			}
	for (i=n-1;i>=0;i--)                //back-substitution
	{                        //x is an array whose values correspond to the values of x,y,z..
		a[i]=B[i][n];                //make the variable to be calculated equal to the rhs of the last equation
		for (j=0;j<n;j++)
			if (j!=i)            //then subtract all the lhs values except the coefficient of the variable whose value                                   is being calculated
				a[i]=a[i]-B[i][j]*a[j];
		a[i]=a[i]/B[i][i];            //now finally divide the rhs by the coefficient of the variable to be calculated
	}
	cout<<"\nThe values of the coefficients are as follows:\n";
	for (i=0;i<n;i++)
		cout<<"x^"<<i<<"="<<a[i]<<endl;            // Print the values of x^0,x^1,x^2,x^3,....    
	cout<<"\nHence the fitted Polynomial is given by:\ny=";
	for (i=0;i<n;i++)
		cout<<" + ("<<a[i]<<")"<<"x^"<<i;
	cout<<"\n";
	printf("============================\n");

	//////////////////
	//polyfit value //
	//////////////////
	double fy[N];
	int fx[N];
	for ( i = 0; i < N; i++){
		fx[i] = i;
	}

	for ( i = 0; i < N; i++){
		fy[i] = a[0]+( a[1]*fx[i] )+( a[2]*(fx[i]*fx[i]) );
	}

	for ( i = 0; i < N; i++){
		printf("fy[%d] = %f\n",i,fy[i] );
	}
	printf("============================\n");

	/////////////////
	//Interception //
	/////////////////
	for ( i = 0; i < N; i++){
		if (array[i]>fy[i]){
			fy[i]=array[i];
		}else{
			fy[i] = 0;
		}
		// printf("============================\n");
		printf("fy[%d] = %f\n",i,fy[i] );
	}
		printf("============================\n");

	////////////////////
	//if logic 0 or 1 //
	////////////////////
	int sum_B =0;
	int sum_W = 0;
	int sum1 = 0;
	int sum2 = 0;
	int c = 0;
	
	char ch[200];
	for ( i = 0; i < N; i++){
		if (fy[i]==0)
		{
			sum_B = sum_B + 1;
			sum_W = 0;
		}
		if (sum_B == 7 )
		{
			sum_B = 0;
			cout<<("#");
			ch[c] ='0';
			c = c + 1;
			sum1 = sum1 +1;
		}

		if (fy[i]>10)
		{
			sum_W = sum_W + 1;
			sum_B = 0;
		}
		if (sum_W == 7)
		{
			sum_W = 0;
			printf("@");
			ch[c] ='1';
			c = c + 1;
			sum2 = sum2 +1;
		}
	}
	printf("\nblack = %d\n",sum1 );
	printf("white = %d\n",sum2 );
	printf("============================\n");

	for ( i = 0; i < sum1+sum2; i++){
		printf("fy[%d] = %c\n",i,ch[i] );
	}

	char str[11]="";
	char answer[25];
	int count =0;
	int c1 = 0;
	for (i = 0; i < sum1+sum2-40; i++)
	{
		sprintf( str, "%c%c%c%c%c%c%c%c%c%c", ch[i],ch[i+1],ch[i+2],ch[i+3],ch[i+4],ch[i+5],ch[i+6],ch[i+7],ch[i+8],ch[i+9] );          
		if (strcmp(str, "0010101011")==0)
		{
			printf("find header\n");
			for (j = i+10; j < i+40; j++)
			{
				printf("%c",ch[j]);
				if ((count%10)!=0 && (count%10)!=9)
				{
					// printf("!%d\n",count%10 );
					answer[c1] = ch[j];
					c1++;
				}
				count = count+ 1;
			}
			answer[c1++]='\0';
			count = 0;
			c1=0;
			printf("\n");

		}
	}

	for (i = 0; i < 23; i++)
	{
		printf("!%d",answer[i] );
	}
	/////////////
	// Reverse //
	/////////////
	char resever[25];
	for (i = 0,j=23; i < 25; i++,j--)
	{
		resever[i] = answer[j];
	}

	///////////////////
	//Char to string //
	///////////////////
	printf("\n%s\n",answer );
	printf("%s\n",resever);
	// printf("\n");
	printf("To String \n");
	char data1[8];
	char data2[8];
	char data3[8];
	sprintf( data1, "%c%c%c%c%c%c%c%c",resever[0],resever[1],resever[2],resever[3],resever[4],resever[5],resever[6],resever[7]);
	sprintf( data2, "%c%c%c%c%c%c%c%c",resever[8],resever[9],resever[10],resever[11],resever[12],resever[13],resever[14],resever[15]);
	sprintf( data3, "%c%c%c%c%c%c%c%c",resever[16],resever[17],resever[18],resever[19],resever[20],resever[21],resever[22],resever[23]);
	
	int d1 = atoi ( data1 ); // 將字串轉整數
	int d2 = atoi ( data2 ); // 將字串轉整數
	int d3 = atoi ( data3 ); // 將字串轉整數

	// cout << hex << bintodec(d1);
	// cout << hex << bintodec(d2);
	// cout << hex << bintodec(d3);
	

	char hexstr1[255];
	char hexstr2[255];
	char hexstr3[255];
	// long dexval=2598413015L;
	sprintf(hexstr1, "%X",bintodec(d1));
	sprintf(hexstr2, "%X",bintodec(d2));
	sprintf(hexstr3, "%X",bintodec(d3));
	cout<<hexstr1;
	cout<<hexstr2;
	cout<<hexstr3<<endl;
	// namedWindow("image",CV_WINDOW_AUTOSIZE);//AUTOSIZE 
	// imshow("image",imagegray);
	waitKey(0);
	return 0;
}
//////////////////
//binary to dec //
//////////////////
int bintodec(int x){
	int c2=1,Dec=0;
 	while(x>0)
	{
		Dec += (x%10)*c2;
		c2= c2*2;
		x/=10;
	} 
	// printf("%d",Dec);
	return Dec;
}