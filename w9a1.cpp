#include<iostream>
#include<math.h>
using namespace std;

class Shape
{
	public:
		long area;
		long curriculum;
		
		//-1表示该类为Shape类 
		int id()
		{
			return -1;
		}
		
		long getArea();
		long getCur();
}; 

class Rectangle : public Shape
{
	public:
		//顶点坐标 (从左上开始逆时针),高宽 
		int point[4][2]; 
		int height,width;
		
		Rectangle(const Rectangle &r1)
		{
			*this=r1;
		}
		
		long getArea()
		{
			return height*width;
		}
		
		long getCur()
		{
			return (height+width)*2;
		}
		
		Rectangle(int x1,int y1,int x2,int y2)
		{
			this->point[0][0]=x1;
			this->point[0][1]=y1;
			this->point[2][0]=x2;
			this->point[2][1]=y2;
			this->point[1][0]=x1;
			this->point[1][1]=y2;
			this->point[3][0]=x2;
			this->point[3][1]=y1;
			this->height=y1-y2;
			this->width=x2-x1;
			this->area=this->getArea();
			this->curriculum=this->getCur();
		}
		
		//4表示该类为Rec类 
		int id()
		{
			return 4;
		}
		
		//判断点是否在矩形内 
		bool include(int x,int y)
		{
			if((this->point[0][0])<=x&&(this->point[0][1]>=y))
			{
				if((this->point[2][0])>=x&&(this->point[2][1]<=y))
				{
					return true;
				}
			}
			return false;
		}
		
		//判断this中是否包含r2的一部分 ，返回包含的面积 
		int cover(Rectangle r2)
		{
			//this完全包围r2 
			if((this->point[0][0])<=r2.point[0][0]&&(this->point[0][1])>=r2.point[0][1])
			{
				if((this->point[2][0])>=r2.point[2][0]&&(this->point[2][1])<=r2.point[2][1])
				{
					return r2.area;
				}
			}
			
			//r2在this内的顶点数 
			int num=0;
			//存储r2在this内的顶点，最多两个 
			int pointIn[2][2]={0};
			int situation=0;
			
			for(int i=0;i<4;i++)
			{
				if(this->include(r2.point[i][0],r2.point[i][1]))
				{
					pointIn[num][0]=r2.point[i][0];
					pointIn[num][1]=r2.point[i][1];
					num++;
					if(situation==0&&i==0)
					{
						situation=1;//左上角 
					}
					else if(situation==0&&i==1)
					{
						situation=2;//左下角 
					}
					else if(situation==0&&i==2)
					{
						situation=3;//右下角 
					}
					else if(situation==0&&i==3)
					{
						situation=4;//右上角 
					}
					else if(situation==1)
					{
						if(i==1)
						{
							situation=5;//左边 
						} 
						else if(i==3)
						{
							situation=8;//上边 
						} 
					}
					else if(situation==2)
					{
						if(i==2)
						{
							situation=6;//下边 
						}
					}
					else if(situation==3)
					{
						if(i==3)
						{
							situation=7;//右边 
						 } 
					} 
				}
			} 
			
			if(num==0)
			{
				return 0;
			}
			
			else if(num==1)
			{
				if(situation==1) 
				{
					return (this->point[2][0]-pointIn[0][0])*(pointIn[0][1]-this->point[2][1]);
				}
				else if(situation==2) 
				{
					return (this->point[3][0]-pointIn[0][0])*(this->point[3][1]-pointIn[0][1]);
				}
				else if(situation==3) 
				{
					return (pointIn[0][0]-this->point[0][0])*(this->point[0][1]-pointIn[0][1]);
				}
				else if(situation==4) 
				{
					return (pointIn[0][0]-this->point[1][0])*(pointIn[0][1]-this->point[1][1]);
				}
			}
			
			else if(num==2)
			{
				if(situation==5) 
				{
					return r2.height*(this->point[2][0]-pointIn[0][0]);
				}
				else if(situation==6) 
				{
					return r2.width*(this->point[0][1]-pointIn[0][1]);
				}
				else if(situation==7) 
				{
					return r2.height*(pointIn[0][0]-this->point[0][0]);
				}
				else if(situation==8) 
				{
					return r2.width*(pointIn[0][1]-this->point[2][1]);
				}
			}
			
			return 0;
		}
		
		//题目要求的函数，判断this和r2的包含关系，再求解 
		int bothCover(Rectangle r2)
		{
			if(this->cover(r2)==0)
			{
				return r2.cover(*this);
			}
			else 
			{
				return this->cover(r2);
			}
		 } 
		 
		// 
		int adjust(int area)
		{
			int t=0;//用于break 
			int len=sqrt(area);
			int w=0,h=0;
			for(int i=len;i>0;i--)
			{
				for(int j=len;(i*j<=area);j++)
				{
					if(i*j==area)
					{
						w=i;
						h=j;
						t=1; 
						break;
					}
				}
				if(t==1)
				{
					break;
				}
			}
			this->width=w;
			this->height=h;
			
			this->point[2][0]=this->point[0][0]+w;
			this->point[2][1]=this->point[0][1]-h;

			this->point[1][1]=this->point[0][1]-h;
			this->point[3][0]=this->point[0][0]+w;

			this->area=this->getArea();
			this->curriculum=this->getCur();
			
			cout<<this->point[2][0]<<" "<<this->point[2][1]<<endl;
		}
};

class Circle : public Shape
{
	public:
		//圆心坐标，半径 
		int x1,y1,r;
		
		//0表示该类为Circle类 
		int id()
		{
			return 0;
		}
		
		long getArea()
		{
			return 3.14159*r*r;
		}
		
		long getCur()
		{
			return 2*3.14159*r;
		}
};

//获取顶点数量 
int getNum(Shape*p)
{
	return p->id();
}

int main()
{
	int x11,y11,x21,y21,x12,y12,x22,y22,area;
	cout<<"按顺序输入第一个矩形左上横坐标，左上纵坐标，右下横坐标，右下纵坐标，第二个矩形左上横坐标，左上纵坐标，右下横坐标，右下纵坐标"<<endl;
	cin>>x11>>y11>>x21>>y21>>x12>>y12>>x22>>y22;
	Rectangle r1=Rectangle(x11,y11,x21,y21);
	Rectangle r2=Rectangle(x12,y12,x22,y22);
	cout<<"重合面积为"<<r1.bothCover(r2)<<endl;
	cout<<"按顺序输入需要调整的矩形左上横坐标，左上纵坐标，右下横坐标，右下纵坐标，调整后的面积"<<endl; 
	cin>>x11>>y11>>x21>>y21>>area;
	Rectangle r3=Rectangle(x11,y11,x21,y21);
	cout<<"调整后的右下坐标为";
	r3.adjust(area);
	return 0;
}

