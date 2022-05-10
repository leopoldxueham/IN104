#ifndef CHECKPOINT
#define CHECKPOINT
#include <SFML/Graphics.hpp>

class CheckPoint : public sf::Drawable{
public :
    CheckPoint();
    CheckPoint(int posx,int posy,int num);
    
private :    
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    int num_;
    double posx_;
    double posy_;
};

#endif