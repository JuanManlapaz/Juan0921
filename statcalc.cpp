#include <vector>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

string menu()
{		// displays options for menu
  cout << "\n\n\t\t\t";
	cout << "================================================";
  cout << "\n\t\t\t\t  C++ Statistics Calculator";
  cout << "\n\t\t\t================================================";
  cout << "\n\t\t\t [1] Load X data\n";
  cout << "\t\t\t [2] Load Y data\n";
  cout << "\t\t\t [3] Load X-Y data\n";
  cout << "\t\t\t [4] View X Data Statistics\n";
  cout << "\t\t\t [5] View Y Data Statistics\n";
  cout << "\t\t\t [6] View X-Y Data Statistics\n";
  cout << "\t\t\t [7] Line Fit & Residuals\n";
  cout << "\t\t\t [8] Statistics of Least Squares Fit Residuals\n";
  cout << "\t\t\t [9] Correlation\n";
  cout << "\t\t\t [10] Exit\n";
  cout << "\t\t\t================================================";
  cout << "\n\t\t\t     Developed by: Juan Glicerio Manlapaz\n";
  cout << "\t\t\t================================================";
  cout << "\n\t\t\tPlease input your choice of menu: ";
  string choice = "";
  getline(cin, choice);
  return choice;
}

void reload()
{
  cout << endl;
  system("pause");
  system("CLS");
}

vector <double> loadFile()
{		// loads x or y data
  string fname;
  vector <double> vec;
  double data;
  start:
  cout << "\t\t\tInput file name: ";
  getline(cin, fname);
  ifstream f (fname.c_str(), ios::in);
  if (!f.is_open())
  {
  	cerr << "\t\t\tFile not found. Input file again.\n";
		reload();
		cout << endl << endl;
		goto start;
  }

	while (!f.eof())
	{
		f >> data;
    vec.push_back(data);
	}

	if (vec.size() <= 1)
	{
		cout << "\n\t\t\tFile has insufficient data. Input file again.\n";
		reload();
		cout << endl << endl;
	  goto start;
	}
	cout << "\n\t\t\t";
	for (int i = 0; i < 3; i++)
		cout << vec[i] << " ";
	cout << "... ";
	for (int i = (vec.size()/2)-1; i <= (vec.size()/2)+1; i++)
		cout << vec[i] << " ";
	cout << "... ";
	for (int i = vec.size()-3; i < vec.size(); i++)
		cout << vec[i] << " ";
	cout << "\n\t\t\tDataset size (n): " << vec.size() << endl;
	return vec;
}

double sum, mean;
// global variables for calling to multiple functions

void getsum(vector <double> vec)
{		// calculates sum of x or y, and mean of x or y
  sum = 0, mean = 0;
  for (int i = 0; i < vec.size(); i++)
    sum = sum + vec[i];
  mean = sum / vec.size();
  cout << "\t\t\tSum:  " << sum;
  cout << "\n\t\t\tMean: " << mean;
}

void getvar(vector <double> vec)
{		// calculates population and sample variance
  double Sum = 0, svar, pvar;
  for (int i = 0; i < vec.size(); i++)
    Sum += (vec[i] - mean) * (vec[i] - mean);
  svar = Sum/(vec.size()-1);
  pvar = Sum/(vec.size());
  cout << "\n\t\t\tSample Variance: " << svar;
  cout << "\n\t\t\tPopulation Variance: " << pvar;
}

void getlocation(vector <double> vec)
{		// calculates minimum, maximum, median, and range
  int n = vec.size();
  double median, range;
	double max = vec [0], min = vec [0];

  if (n != 0)
	{
    sort (vec.begin(), vec.end());
    if (n%2 == 0)
      median = (vec[n/2] + (vec[(n/2) + 1]))/2;
    else
      median = vec[(n+1)/2];
    }

  for (int i = 1; i < vec.size(); i++)
	{
	  if (vec[i] > max)
      max = vec[i];
    if (vec[i] < min)
      min = vec[i];
	}

	range = max - min;

	cout << "\n\t\t\tMedian: " << median;
	cout << "\n\t\t\tMax: " << max;
	cout << "\n\t\t\tMin: " << min;
	cout << "\n\t\t\tRange: " << range;
}

void allstat(vector <double> vec)
{		// calls functions for sum, variance,
		// and location to display statistics of x or y
  getsum(vec);
  getvar(vec);
  getlocation(vec);
}

vector <double> vecx, vecy;
// global variables for calling to multiple functions

void loadxy()
{		// loads x- and y- data
  double x, y;
  int n;
  string fname, choice1, choice2;
  start:
  cout << "\n\t\t\tAre your data sets in one file? [Y/N] ";
  getline(cin, choice1);
  if (choice1 == "y" || choice1 == "Y")
  {
    start1:
    cout << "\n\t\t\tInput file name: ";
    getline(cin, fname);
    ifstream f (fname.c_str(), ios::in);

    vecx.clear();
    vecy.clear();

    if (!f.is_open())
    {
      cerr << "\n\t\t\tFile not found. Input file again.\n";
      reload();
      cout << endl << endl;
      goto start1;
    }

    while (!f.eof())
    {
      f >> x >> y;
      vecx.push_back(x);
      vecy.push_back(y);
    }
    n = vecx.size();
	}
	else if (choice1 == "n" || choice1 == "N")
  {
    start2:
    cout << "\n\t\t\tInput file name of X-data: ";
    getline(cin, fname);
    ifstream f (fname.c_str(), ios::in);

    vecx.clear();
    if (!f.is_open())
    {
      cerr << "\n\t\t\tFile not found. Input file again.\n";
      reload();
      cout << endl << endl;
      goto start2;
    }

    while (!f.eof())
    {
      f >> x;
      vecx.push_back(x);
    }

    start3:
    cout << "\t\t\tInput file name of Y-data: ";
    getline(cin, fname);
    ifstream g (fname.c_str(), ios::in);

    vecy.clear();
    if (!g.is_open())
    {
      cerr << "\n\t\t\tFile not found. Input file again.\n";
      reload();
      cout << endl;
      goto start3;
    }

    while (!g.eof())
    {
      g >> y;
      vecy.push_back(y);
    }
    if (vecx.size() != vecy.size())
    {
      start4:
			cout << "\n\t\t\tYour inputs do not have the same sizes. "
			<< "Would you like to reload files? [Y/N] ";
      getline(cin, choice2);
      if (choice2 == "y" || choice2 == "Y")
      {
        reload();
        cout << endl;
        goto start2;
      }
      else if (choice2 == "n" || choice2 == "N")
      {   // the vector with the smaller size will set the data size
        if (vecx.size() > vecy.size())
          n = vecy.size();
        else
          n = vecx.size();
      }
      else
	    {
	      cout << "\t\t\tInvalid input. Kindly re-enter either Y or N";
	  	  cout << endl;
				reload();
	  	  goto start4;
			}
    }
    else
    	n = vecx.size();
  }

  else
  {
  	cout << "\n\t\t\tInvalid input. Kindly re-enter either Y or N";
  	cout << endl;
  	reload();
  	goto start;
	}

	cout << "\t\t\tX:\tY:\n"; // displays first, middle, and final data
	for (int i = 0; i < 3; i++)
    cout << "\t\t\t" << vecx[i] << "\t" << vecy[i] << endl;
	cout << "\t\t\t...\t...\n";
	for (int i = (n/2)-1; i <= (n/2)+1; i++)
		cout << "\t\t\t" << vecx[i] << "\t" << vecy[i] << endl;
	cout << "\t\t\t...\t...\n";
	for (int i = n-3; i < n; i++)
		cout << "\t\t\t" <<vecx[i]<<"\t" << vecy[i] << endl;
	cout << "\n\t\t\tData Size: " << n;
}

double sumx, sumy, sumx2, sumy2, sumxy, meanx, meany;
// global variables for calling to multiple functions

double getsumx(vector <double> vectorx, string n)
{		// calculates sum of x, x^2, and mean of x
  sumx = 0, sumx2 = 0; meanx = 0;
	for (int i = 0; i < vectorx.size(); i++)
	{
    sumx += vectorx[i];
		sumx2 += pow(vectorx[i], 2);
  }
  meanx = sumx / vectorx.size();
  if (n == "sum")
    return sumx;
  if (n == "sum2")
    return sumx2;
  if (n == "mean")
    return meanx;
  cout << "\t\t\tSum X:    "  << sumx << endl;
  cout << "\t\t\tSum X^2:  " << sumx2 << endl;
	cout << "\t\t\tMean X:   " << meanx << endl;
}

double getsumy(vector <double> vectory, string n)
{		// calculates sum of y, y^2 and mean of y
	sumy = 0, sumy2 = 0; meany = 0;
  for (int i = 0; i < vectory.size(); i++)
	{
    sumy += vectory[i];
		sumy2 += pow(vectory[i], 2);
  }
	meany = sumy / vectory.size();
	if (n == "sum")
    return sumy;
  if (n == "sum2")
    return sumy2;
  if (n == "mean")
    return meany;
  cout << "\t\t\tSum Y:    " << sumy << endl;
  cout << "\t\t\tSum Y^2:  " << sumy2 << endl;
  cout << "\t\t\tMean Y:   " << meany << endl;
}

double getsum(vector <double> vectorx, vector <double> vectory,
  char n)
{		// calculates sum of x*y
	sumxy = 0;
	for (int i = 0; i < vectorx.size(); i++)
    sumxy += (vectorx[i]) * (vectory[i]);
  if (n != ' ')
    return sumxy;
  cout << "Sum XY:   " << sumxy << endl;
}

void allstatxy(vector <double> vectorx, vector <double> vectory)
{		// calls functions for sum of x & y, x^2 & y^2,
		// means of x & y, and sum of x*y
	getsumx(vectorx, "aa");
	getsumy(vectory, "aa");
	cout << "\t\t\tSum XY:   " << getsum(vectorx, vectory, 'a') << endl;
}

double getlreg(vector <double> vectorx, vector <double> vectory)
{		// calculates for elements of linear regression
  int n = vectorx.size();
  double b1 = 0, b1n = 0, b1d = 0, b0 = 0, b0n = 0, e,e2;

	b1n = n * getsum(vectorx, vectory, 'a') - getsumx(vectorx, "sum")
	* getsumy(vectory, "sum");
  b1d = n * getsumy(vectorx, "sum2")
    - pow(getsumx(vectorx, "sum"), 2);
  b1 = b1n / b1d;
  b0n = getsumy(vectory, "sum") - b1 * getsumx(vectorx, "sum");
  b0 = b0n / n;

	cout << "Regression Line: ";
	if (b0 < 0)
    	cout << "y = " << b1 << "x - " << -b0 << endl;
  else
		cout << "y = " << b1 << "x + " << b0 << endl;

	cout << "\nX:\t\tY (Observed):\tY0 (Predicted):\tResiduals:\n";
	for (int i = 0; i < vectorx.size(); i++)
	{
	  e = vectory[i]-((b1)*(vectorx[i])+(b0));
	  e2 = e*e;
    cout << vectorx[i] << "\t\t" << vectory[i] << "\t\t"
    << ((b1)*(vectorx[i])+(b0)) << "\t\t" << e << endl;
  }
}

void getresidstats (vector <double> vectorx, vector <double> vectory)
{
  int n = vectorx.size();
  double b1 = 0, b1n = 0, b1d = 0, b0 = 0, b0n = 0,
	e, sse, mse, e2, se = 0, me = 0;

	b1n = n * getsum(vectorx, vectory, 'a') - getsumx(vectorx, "sum")
  * getsumy(vectory, "sum");
	b1d = n * getsumy(vectorx, "sum2")
    - pow(getsumx(vectorx, "sum"), 2);
  b1 = b1n / b1d;
  b0n = getsumy(vectory, "sum") - b1 * getsumx(vectorx, "sum");
  b0 = b0n / n;

  for (int i = 0; i < vectorx.size(); i++)
	{
	  e = vectory[i]-(b1*vectorx[i]+b0);
	  e2 = e*e;
	  sse += e2;
	  se += e;
	  mse = sse/(vectorx.size()-2);
	  me = se/vectorx.size();
  }

  cout << "\n\t\t\tSum of Residuals: " << se;
  cout << "\n\t\t\tMean of Residuals: " << me;
  cout << "\n\t\t\tSum of Squared Errors (SSE): " << sse;
  cout << "\n\t\t\tMean Squared Error (MSE): " << mse <<endl;
}

void getcorrel(vector <double> vectorx, vector <double> vectory)
{		// calculates for elements of correlation of x & y, with r and R^2
  double sxx = 0, syy = 0, sxy = 0, r, r2;
  for (int i = 0; i < vectorx.size(); i++)
	{
    sxx = sxx + pow((vectorx[i] - getsumx(vectorx, "mean")), 2);
    syy = syy + pow((vectory[i] - getsumy(vectory, "mean")), 2);
    sxy = sxy + (vectorx[i] - getsumx(vectorx, "mean"))
    * (vectory[i] - getsumy(vectory, "mean"));
  }

  r = (sxy/sqrt(sxx*syy));
  r2 = pow(r, 2);
  cout << "\t\t\tCorrelation: ";
	cout << "\n\t\t\tSxx: " << sxx;
  cout << "\n\t\t\tSyy: " << syy;
  cout << "\n\t\t\tSxy: " << sxy;
  cout << "\n\t\t\tCorrelation Coefficient (r): " << r << endl;

  if (r==-1)
      cout << "\t\t\tThis shows a perfect negative relationship\n";
  else if (r>-1 && r<=-0.75)
      cout << "\t\t\tThis shows a strong negative relationship\n";
  else if (r>-0.75 && r<=-0.5)
      cout << "\t\t\tThis shows a moderate negative relationship\n";
  else if (r>-0.5 && r<=-0.3)
      cout << "\t\t\tThis shows a weak negative relationship\n";
  else if (r==0)
      cout << "\t\t\tNo Relationship\n";
  else if (r>=0.3 && r<0.5)
      cout << "\t\t\tThis shows a weak positive relationship\n";
  else if (r>=0.5 && r<0.75)
      cout << "\t\t\tThis shows a moderate positive relationship\n";
  else if (r>=0.75 && r<1)
      cout << "\t\t\tThis shows a strong positive relationship\n";
  else if (r==1)
      cout << "\t\t\tThis shows a perfect positive relationship\n";

  cout << "\t\t\tCoefficient of Determination (R^2): "<< r2
	<<" \n\t\t\t-> " << r2*100
	<< " % of the y-values are accounted for by the x-values.";
}

int main()
{		// main function; contains conditions for menu system
		// using if-else conditions to account for string error inputs
	vector <double> vx, vy;

	start:
	string choice = menu();
	if (choice == "1")
	{		// load x-data
		vx = loadFile();
		reload();
		goto start;
	}
	else if (choice == "2")
	{		// load y-data
		vy = loadFile();
		reload();
		goto start;
	}
	else if (choice == "3")
	{		// load x-y data
		loadxy();
		reload();
		goto start;
	}
	else if (choice == "4")
	{		// shows stats of x-data
		if (vx.size() == 0)
		{
			cout << "\n\t\t\tNo loaded data! Please load data first.\n";
			reload();
			goto start;
		}

    cout << "\t\t\tX-Data: \n";
    allstat(vx);
    reload();
    goto start;
	}
	else if (choice == "5")
	{		// shows stats of y-data
		if (vy.size() == 0)
		{
			cout << "\n\t\t\tNo loaded data! Please load data first.\n";
			reload();
			goto start;
		}
		cout << "\t\t\tY-Data: \n";
		allstat(vy);
		reload();
		goto start;
	}
	else if (choice == "6")
	{		// shows stats of x-y data
		if (vecx.size() == 0 || vecy.size() == 0)
		{
			cout << "\n\t\t\tNo loaded data! Please load data first.\n";
			reload();
			goto start;
		}
		cout << "\t\t\tXY-Data: \n";
		allstatxy(vecx, vecy);
		reload();
		goto start;
	}
	else if (choice == "7")
	{		// shows linear regression and line fit residuals
		if (vecx.size() == 0 || vecy.size() == 0)
		{
			cout << "\n\t\t\tNo loaded data! Please load data first.\n";
			reload();
			goto start;
		}
		system("CLS");
		getlreg(vecx, vecy);
		reload();
		goto start;
	}

	else if (choice == "8")
	{		// shows stats of residuals
		if (vecx.size() == 0 || vecy.size() == 0)
		{
			cout << "\n\t\t\tNo loaded data! Please load data first.\n";
			reload();
			goto start;
		}
		getresidstats(vecx, vecy);
    reload();
		goto start;
	}

	else if (choice == "9")
	{		// shows correlation data of x & y
		if (vecx.size() == 0 || vecy.size() == 0)
		{
			cout << "\n\t\t\tNo loaded data! Please load data first.\n";
			reload();
			goto start;
		}
		getcorrel(vecx, vecy);
		reload();
		goto start;
	}
	else if (choice == "10")
	{		// option for exit
	  system("CLS");
		cout << "\n\n\n\t\t\t"
		<< "Thanks for using C++ Statistics Calculator.\n";
		exit(1);
	}
    else if (choice == "0") //hidden feature
    {		// option for credits
		system("CLS");
		cout << "\n\t\t\tWe would like to thank the following: " << endl;
		cout << "\n\t\t\tLuisito Agustin, Ph.D" << endl;
		cout << "\t\t\tFr. Jett  Villarin, SJ" << endl;
		cout << "\t\t\tLoyola Schools Community" << endl;
		cout << "\t\t\tSchool of Science and Engineering" << endl;
		cout << "\t\t\tECCE Department" << endl;
		cout << "\t\t\tAECES" << endl;
		cout << "\t\t\tBlock QQ1" << endl;
		cout << "\t\t\tResidence Halls" << endl;
		cout << "\t\t\tUDN 109" << endl;
		cout << "\t\t\tFCC 4" << endl;
		cout << "\t\t\tFriends and Family" << endl;
		cout << "\t\t\tAMDG!" << endl;
		cout << "\t\t\tIntersession 2019" << endl;
		reload();
		goto start;
	}
	else
	{		// erroneous inputs
		cout << "\n\t\t\tOption not found. Kindly reselect.\n";
		reload();
		goto start;
	}
}
