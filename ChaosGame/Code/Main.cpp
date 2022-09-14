#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <time.h> 

using namespace std;
using namespace sf;

float getx(float xval[], float recentPoint, int count)
{
    /*
    srand(time(0));
    int randNum = rand() % 2;
    
    if (randNum == 2)
    {
        count = 2;
    }
    if (randNum == 1)
    {
        count = 1;
    }
    if (randNum == 0)
    {
        count = 0;
    }
    */

    int temp = count;
    float calc = xval[temp];

    float x1 = calc;
    float x2 = recentPoint;

    // Calculate middle of vertex and last point
    float val = (x1 + x2) / 2.0;


    return val;
}

float gety(float yval[], float recentPoint, int count)
{
    /*
    
    srand(time(0));
    int randNum = rand() % 2;

    if (randNum == 2)
    {
        count = 2;
    }
    if (randNum == 1)
    {
        count = 1;
    }
    if (randNum == 0)
    {
        count = 0;
    }
    */
 
    int temp = count;

    float calc = yval[temp];


    float y1 = calc;
    float y2 = recentPoint;

    // Calculate middle of vertex and last point
    float val = (y1 + y2) / 2.0;

    return val;
}

int main()
{
    RenderWindow window(VideoMode(800, 600), "My window");

   
    while (window.isOpen())
    {
        
        Event event;
        while (window.pollEvent(event))
        {
           
            if (event.type == Event::Closed)
                window.close();
        }

        CircleShape Triangle;
        Triangle.setRadius(100.f);
        Triangle.setPointCount(3);

        window.clear(Color::Black);

        int x1, x2, x3, x4;
        int y1, y2, y3, y4;

        x1 = 300;
        y1 = 300;

        x2 = 400;
        y2 = 300;

        x3 = 350;
        y3 = 100;

        x4 = 350;
        y4 = 250;

        // Use to hold points if needed
        float* cordsX = new float[100];
        float* cordsY = new float[100];
       


        cordsX[0] = x1;
        cordsX[1] = x2;
        cordsX[2] = x3;
        cordsX[3] = x4;

        cordsY[0] = y1;
        cordsY[1] = y2;
        cordsY[2] = y3;
        cordsY[3] = y4;

        // Array that holds the main verticies
        float MainCordsX[3] = { x1, x2, x3 };
        float MainCordsY[3] = { y1, y2, y3 };

        
        // Sample set of points 
        Vertex point(Vector2f(x1,y1), Color::Blue);
        window.draw(&point, 1, Points);

        Vertex point2(Vector2f(x2,y2), Color::Yellow);
        window.draw(&point2, 1, Points);

        Vertex point3(Vector2f(x3,y3), Color::Magenta);
        window.draw(&point3, 1, Points);

        Vertex points4(Vector2f(cordsX[3], cordsY[3]), sf::Color::White);
        window.draw(&points4, 1, Points);

        /*
        Vertex p[10] = {Vertex(Vector2f(30, 30), Color::Red),Vertex(Vector2f(200,  500), Color::Red)};
        p[3] = Vertex(Vector2f(300, 120), Color::Red);
        window.draw(p, 3, ::Points);
        */
        bool stop = false;
        int total = 0;
        while (!stop)
        {
            
            int count = 0;
            float lastXPoint = cordsX[3];
            float lastYPoint = cordsY[3];
            for (int index = 0; index < 2000; index++)
            {
                // Vertex array to hold points
                VertexArray points(::Points, 2000);
            
                // Calls funtion to get new coordinates for vector
                float XCord = getx(MainCordsX, lastXPoint, count);
                float YCord = gety(MainCordsY, lastYPoint, count);

                points[index].position = Vector2f(static_cast<int>(XCord), static_cast<int>(YCord));
                points[index].color = Color::Red;

                // Makes it so the last coordinate plotted is used in next get function
                lastXPoint = XCord;
                lastYPoint = YCord;

                // Trying to add more variables to make random
                count++;
                if (count > 2)
                {
                    count = 0;
                }
                if (total % 10 == 0)
                {
                    count = 2;
                }
                if (total % 3 == 0)
                {
                    count = 1;
                }

                //cout << " " << lastXPoint;// << " " << cordsY[index + 3];
                window.draw(points);
                total++;
            }
            stop = true;
            delete[] cordsX;
            delete[] cordsY;
        }
        window.display();

    }
    
    return 0;
}