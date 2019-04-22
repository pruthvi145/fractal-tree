#include<iostream>
#include<graphics.h>
#include<vector>
#include<math.h>
#define PI 3.1415
using namespace std;

const float changingangle = PI/6;
const float changinglength = 0.8;
class Point
{
    public:
        int x,y;

        Point(){}

        Point(int x, int y)
        {
            this->x = x;
            this->y = y;
        }
        void print()
        {
            cout<<"x: "<<this->x<<endl;
            cout<<"y: "<<this->y<<endl;
            cout<<endl;
        }
        Point operator+(Point b)
        {
            Point res;
            res.x = this->x + b.x;
            res.y = this->y + b.y;
            return res;
        }

        Point operator-(Point a)
        {
            Point res;
            res.x = this->x - a.x;
            res.y = this->y - a.y;
            return res;
        }

        Point operator*(float m)
        {
            Point res;
            res.x = this->x*m;
            res.y = this->y*m;
            return res;
        }
          void rotate(float angle)
        {
            float r = sqrt(pow(this->x,2) + pow(this->y,2));
            this->x = r * cos(angle);
            this->y = r * sin(angle);
        }
};

class Branch
{
    private:
        Point a,b;
        float angle;
    public:

        Branch(){}
        Branch(Point a, Point b)
        {
            this->a = a;
            this->b = b;
        }

        void setpoints(Point a, Point b)
        {
            this->a = a;
            this->b = b;
        }
        void setangle(float angle)
        {
            this->angle = angle;
        }
        void show()
        {
            line(a.x, a.y, b.x, b.y);
        }

        float getangle()
        {
            return atan2((this->b.y - this->a.y), (this->b.x - this->a.x));
        }

        Branch* generatechild()
        {
            Branch static children[2];
            Point v = b-a;

            v = v*changinglength;
            float angle = this->getangle();
            v.rotate(angle+changingangle);
            Point b1 = b+v;
            children[0].setpoints(this->b, b1);

            v.rotate(angle-changingangle);
            Point b2 = b+v;
            children[1].setpoints(this->b, b2);

            return children;
        }
};
/////////////////////////////////////////////////////////
vector<Branch> allbranches;

void setup()
{
    Point a(getmaxx()/2, getmaxy());
    Point b(getmaxx()/2, getmaxy()-150);
    Branch b1(a,b);
    allbranches.push_back(b1);
    Branch *children = b1.generatechild();

}
void showallbranches()
{
    unsigned i;
    for(i=0; i<allbranches.size(); i++)
        allbranches[i].show();
      cout<<allbranches.size()<<" - Segments Drawn!"<<endl;
}
void loop()
{
    //getch();
    delay(100);
    cleardevice();
    showallbranches();
    vector<Branch> nextchildren;

    for(unsigned i=0; i<allbranches.size(); i++) //unsigned given more +ve values for loop
    {
        Branch* children = allbranches[i].generatechild();
        for(unsigned j=0; j<2; j++)
            nextchildren.push_back(children[j]);
    }
    for(unsigned i=0; i<nextchildren.size(); i++)
            allbranches.push_back(nextchildren[i]);

}

int main()
{
    initwindow(1200,800);
    setup();
    setcolor(GREEN);
    for(short i=1; i<=11; i++)
    {
        cout<<"START: "<<i<<endl;
        cout<<"-----------"<<endl;
        loop();
        cout<<"-----------"<<endl;
        cout<<"DONE: "<<i<<endl<<endl;
    }

    getch();
    closegraph();
    return 0;
}
