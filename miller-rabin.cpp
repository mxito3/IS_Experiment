#include "iostream"
#include "time.h"
#include "stdlib.h"
#include "math.h"
using namespace std;
class miller
{
	public:
	static int random;
	int check(int m)
	{
	//	if()
	}
	int* getQAndK(int m)
	{
		int times=0;
		int init=m-1;
		static int result[2];
		while(init%2==0)
		{
			times++;
			init=init/2;
		}
		result[0]=times;
		result[1]=init;
		return result;
	}
        int getRandom(int m)
	{
		srand((unsigned)time(NULL));
		return rand()%(m-3)+2;
	}
	int check1(int number)
	{
		if((int)(pow(random,getQAndK(number)[1])-1)%number==0)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
        int check2(int number)
	{
		 int *result;

                result=getQAndK(number);
		int q=result[1];
                int k=result[0];

		for(int j=1;j<=k;j++)
		{
			if((int)(pow(getRandom(number),pow(2,j-1)*q)-(number-1))%number==0)
			{
				return 1;
    			}
			else
			{
				return 0;
			}
		}
	}
};
int miller::random=0;
int main()
{
	miller mi;
	int number;
	int *result;
	cin>>number;
	//result=mi.getQAndK(number);
	//cout<<result[0]<<"   "<<result[1]<<endl;
	//cout<<mi.getRandom(number)<<endl;
	miller::random=mi.getRandom(number);
        cout<<mi.check1(number)<<"   "<<mi.check2(number)<<endl;        
	int successTime=0;
        if(mi.check1(number))
	successTime++;
	if(mi.check2(number))
        successTime++;
        if(successTime==1)
        cout<<" 是素数"<<endl;
        else
	cout<<" 不是素数"<<endl;
        
}

