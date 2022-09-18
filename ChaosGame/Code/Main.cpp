// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

// Make code easier to type with "using namespace"
using namespace sf;
using namespace std;

float lastXPoint;
float lastYPoint;
float* cordsX = new float[10];
float* cordsY = new float[10];

float getx(float xval[], float recentPoint, int count)
{

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
    // Create a video mode object
    VideoMode vm(1920, 1080);

    // Create and open a window for the game
    RenderWindow window(vm, "Sierpinski Triangle", Style::Default);

    bool paused = true;

    // Draw some text
    Text messageText;
    // We need to choose a font
    Font font;
    font.loadFromFile("fonts/KOMIKAP_.ttf");
    // Set the font to our message
    messageText.setFont(font);
    // Assign the actual message
    messageText.setString("Please pick three points on the screen");
    // Make it really big
    messageText.setCharacterSize(30);

    //Choose a color
    messageText.setFillColor(Color::White);

    // Position the text
    FloatRect textRect = messageText.getLocalBounds();
    messageText.setOrigin(textRect.left +
        textRect.width / 2.0f,
        textRect.top +
        textRect.height / 2.0f);
    messageText.setPosition(1920 / 2.0f, 100.0f);

    float x1, x2, x3, x4;
    float y1, y2, y3, y4;


    bool go = false;

    Vector2f clicked;
    int count1 = 0;

    vector<VertexArray> vertexArrays;

    std::srand(time(0));

    while (window.isOpen())
    {
        if (paused)
        {
            // Draw our message         
            window.draw(messageText);
        }
        window.display();

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }


            if (event.type == sf::Event::MouseButtonPressed)
            {
                paused = false;

                if (count1 < 3)
                {
                    if (event.mouseButton.button == Mouse::Left)
                    {
                        cout << " ";
                        cout << event.mouseButton.x << endl;
                        cout << event.mouseButton.y << endl;

                        Vector2i mousePos = Mouse::getPosition(window);
                        float temp1 = mousePos.x;
                        float temp2 = mousePos.y;
                        cordsX[count1] = temp1;
                        cordsY[count1] = temp2;

                        Vertex pointf(Vector2f(mousePos.x, mousePos.y), Color::Red);
                        window.draw(&pointf, 1, Points);
                        window.display();

                        count1++;
                    }

                }
                if (count1 == 3)
                {
                    go = true;
                    x1 = cordsX[0];
                    x2 = cordsX[1];
                    x3 = cordsX[2];
                    x4 = cordsX[3];

                    y1 = cordsY[0];
                    y2 = cordsY[1];
                    y3 = cordsY[2];
                    y4 = cordsY[3];


                }

            }

        }

        while (go)
        {

            // Array that holds the main verticies
            float MainCordsX[3] = { x1, x2, x3 };
            float MainCordsY[3] = { y1, y2, y3 };

            float lastXPoint = x3;
            float lastYPoint = y3;


            bool stop = false;
            int total = 0;

            while (!stop)
            {
                int count = rand() % 3;

                for (int index = 0; index < 5; index++)
                {
                    // Vertex array to hold points
                    VertexArray points(Points, 5);

                    // Calls funtion to get new coordinates for vector
                    float XCord = getx(MainCordsX, lastXPoint, count);
                    float YCord = gety(MainCordsY, lastYPoint, count);

                    if (XCord > x1 && XCord < ((x1 + x3) / 2) && (YCord > ((y1 + y2) / 2)))
                    {
                        points[index].position = Vector2f(XCord, YCord);
                        points[index].color = Color::Green;
                    }
                    else if (XCord > x1 && XCord > ((x1 + x3) / 2) && (YCord > ((y1 + y2) / 2)))
                    {
                        points[index].position = Vector2f(XCord, YCord);
                        points[index].color = Color::Blue;
                    }
                    else
                    {
                        points[index].position = Vector2f(XCord, YCord);
                        points[index].color = Color::Magenta;
                    }


                    // Makes it so the last coordinate plotted is used in next get function
                    lastXPoint = XCord;
                    lastYPoint = YCord;

                    count = rand() % 3;


                    ///window.draw(points);
                    vertexArrays.push_back(points);
                    total++;

                }
                stop = true;

            }

            // These are just to test verticies - remove when needed
            window.clear(Color::Black);
            Vertex point(Vector2f(x1, y1), Color::Magenta);
            window.draw(&point, 1, Points);

            Vertex point2(Vector2f(x2, y2), Color::Green);
            window.draw(&point2, 1, Points);

            Vertex point3(Vector2f(x3, y3), Color::Blue);
            window.draw(&point3, 1, Points);




            for (int i = 0; i < vertexArrays.size(); i++)
            {
                window.draw(vertexArrays.at(i));
            }
            window.display();

        }

    }
    delete[] cordsX;
    delete[] cordsY;
    return 0;
}