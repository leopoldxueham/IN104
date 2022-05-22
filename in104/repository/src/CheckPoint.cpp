#include "CheckPoint.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include "fonctions.h"


//Initialisation avec la position et le numéro du checkpoint
CheckPoint::CheckPoint() {
    posx_=0.;
    posy_=0.;
    num_=0;
}

CheckPoint::CheckPoint(int posx,int posy,int num):num_(num),posx_(posx),posy_(posy){};

void CheckPoint::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    sf::CircleShape circle(600.f);
    circle.setFillColor(sf::Color(0, 0, 0, 63));
    circle.setOutlineThickness(-50);
    circle.setOutlineColor(sf::Color(0, 0, 0));
    circle.setOrigin(600.f,600.f);
    circle.setPosition(posx_,posy_);
    target.draw(circle, states);

    if(num_==0){
        // Gestion du départ : affichage différent et position en haut à gauche de la fenêtre
        sf::Texture vaisseau1Texture;
        vaisseau1Texture.loadFromFile("../repository/Images/checkeredFlag.png");
        sf::Sprite flag;
        flag.setTexture(vaisseau1Texture);
        scaleToMaxSize(flag,600,600);
        flag.setPosition(posx_-300,posy_-300);
        target.draw(flag);
    }

    else{
        
        // Notons qu'il serait préférable d'avoir cette variable comme variable globale afin de ne pas recharger la police à chaque fois
        sf::Font font;
        if (!font.loadFromFile("../repository/Fredoka-Bold.ttf"))
        {
            // error...
        }
        //=================================================
        sf::Text text;
        text.setFont(font); 
        char temp[256];
        sprintf(temp, "%d", num_);
        text.setString(sf::String(temp));
        text.setCharacterSize(500); 
        text.setOutlineThickness(100);
        text.setPosition(posx_-120,posy_-360);
        text.setFillColor(sf::Color(255, 255, 255, 255));
        target.draw(text, states);
    }
}



