#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "fonctions.h"


void scaleToMinSize(sf::Sprite &target,int largeur,int hauteur){
    float sizex=target.getTexture()->getSize().x * target.getScale().x;
    float sizey=target.getTexture()->getSize().y * target.getScale().y;
    float up=std::min(largeur/sizex,hauteur/sizey);
    target.setScale(up,up);
}
void scaleToMaxSize(sf::Sprite &target,int largeur,int hauteur){
    float sizex=target.getTexture()->getSize().x * target.getScale().x;
    float sizey=target.getTexture()->getSize().y * target.getScale().y;
    float up=std::max(largeur/sizex,hauteur/sizey);
    target.setScale(up,up);
}
