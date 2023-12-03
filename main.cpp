#include <SFML/Graphics.hpp>
#include "main.hpp"
#include "paddle.hpp"
#include <sstream>
#include <stdbool.h>

//HANDLING BALL
pong::pong(float x, float y){
Position.x= x;
Position.y= y;

ball.setSize(sf::Vector2f(BALL_SIDE,BALL_SIDE));
ball.setPosition(Position);
}

sf::RectangleShape pong::get_shape(){
    return ball;
}

sf::FloatRect pong::get_position(){ 
return ball.getGlobalBounds();
}

float pong::velocityy(){
   directiony=-0.9 + static_cast<float>(std::rand()) / RAND_MAX * (0.9 + 0.9);
   return directiony;
}

void pong::update(sf::Time dt){
Position.x += directionx*SPEED*dt.asSeconds();
Position.y += directiony*SPEED*dt.asSeconds();

ball.setPosition(Position);
}

void pong::bounce(){
directionx = -directionx;
}

void pong::bouncey(){
    directiony = -directiony;
}

void pong::bounce_bottom(){
  if (ball.getPosition().y > 580){
        directiony = -directiony;
        ball.setPosition(ball.getPosition().x, 580); 
}
}

//HANDELING PADDLE
paddle::paddle(float paddlex, float paddley){
    paddlex=paddle_Position.x;
    paddley=paddle_Position.y;

    paddle_shape.setSize(sf::Vector2f(PADDLE_WIDTH,PADDLE_HEIGHT));
    paddle_shape.setPosition(paddle_Position);
    
}

sf::FloatRect paddle::get_paddle_position(){
    return paddle_shape.getGlobalBounds();
}

sf::RectangleShape paddle::get_paddle_shape(){
    return paddle_shape;
}

void paddle::updatepaddle1(sf::Time dt){
  
 if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
    paddle_Position.y -= speed*dt.asSeconds();
 }
 if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
    paddle_Position.y += speed*dt.asSeconds();
 }

 paddle_shape.setPosition(paddle_Position);
}

void paddle::updatepaddle2(sf::Time dt){
  
 if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
    paddle_Position. y-= speed*dt.asSeconds();
 }
 if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
    paddle_Position.y += speed*dt.asSeconds();
 }

 paddle_shape.setPosition(paddle_Position);
}



int main()
{
  int score1=0;
  int score2=0;
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT),"pong game" );
    sf::Clock clock;
    pong ball(SCREEN_WIDTH/2,SCREEN_HEIGHT/2);
    paddle paddle1(30, 300);
    paddle paddle2(1170, 300);
    sf::Time dt;

    //HANDELING SCORE
    sf::Font font;
    font.loadFromFile ("C:\\Users\\anshu\\OneDrive\\Desktop\\tight_pixel_6917455");
    sf::Text fonthud;
     sf::Text fonthud2;
    fonthud.setFont(font);
    fonthud.setPosition(SCREEN_WIDTH/2 - 100 , 200);
    fonthud.setCharacterSize(500);
        fonthud2.setFont(font);
    fonthud2.setPosition(SCREEN_WIDTH - 300 , 200);
    fonthud2.setCharacterSize(500);
    std::stringstream s;
    std::stringstream ss;

    s<<score1;
    ss<<score2;

    fonthud.setString(s.str());
    fonthud2.setString(ss.str());

    while (window.isOpen())
    {   


         dt = clock.restart();  

        if(ball.get_position().intersects(paddle1.get_paddle_position())){
             ball.bounce();
             ball.velocityy() ;

        }

        if(ball.get_position().intersects(paddle2.get_paddle_position())){
             ball.bounce();
             ball.velocityy() ;
        }

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }


        if (ball.get_position().top<1){
        ball.bouncey();
    }
        
     

        window.clear();

        ball.update(dt);
        ball.bounce_bottom();
        window.draw(ball.get_shape());

if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)||sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        paddle1.updatepaddle1(dt);
}

if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)||sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        paddle2.updatepaddle2(dt);  
}
  window.draw(paddle1.get_paddle_shape());
window.draw(paddle2.get_paddle_shape());
window.draw(fonthud);
window.draw(fonthud2);

  if(ball.get_position().intersects(paddle1.get_paddle_position())==1){
         score2++;
         ss<<score2;
    }
        if(ball.get_position().intersects(paddle2.get_paddle_position())==1){
         score1++;
         s<<score1;
    }



//column of squares
   for (int i = 0; i < 19; i++){
                sf::RectangleShape square(sf::Vector2f(BALL_SIDE,BALL_SIDE));
                square.setPosition(SCREEN_WIDTH/2 - 10, BALL_SIDE + BALL_SIDE * 2*i);
                window.draw(square);
            }

        window.display();
    }

    return 0;
}