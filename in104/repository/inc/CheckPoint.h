#ifndef CHECKPOINT
#define CHECKPOINT
#include <SFML/Graphics.hpp>

// déclaration de la classe checkpoint

class CheckPoint : public sf::Drawable{
public :
    CheckPoint();
    CheckPoint(int posx,int posy,int num);
    
private :    
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
// attributs
    int num_;
    double posx_;
    double posy_;
};

#endif
