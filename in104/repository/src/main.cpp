#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <cmath>
#include <iostream>
#include <thread>
#include "CheckPoint.h"
#include "fonctions.h"
#define PI 3.1415927
// fonction qui renvoie un booléen : True si les deux points sont suffisaments proches 
    int near(float ciblex,float cibley,sf::Vector2f pos,float distance){
        float norme=sqrt((pos.x-ciblex)*(pos.x-ciblex)+(pos.y-cibley)*(pos.y-cibley));
        return norme<distance;
    }

// fonction modulo
    float mod(float x,float pi){
        float val;
        if (x<0){val=fmod(-x,pi);}
        else {val=fmod(x,pi);}
        if (val>pi/2){val-=pi;}
        if (val<-pi/2){val+=pi;}
        if (x<0){val=-val;}
        return val;
    }

// Fonction qui donne l'angle d'un vecteur en radians
    float vect2rad(sf::Vector2f vect){
        float angle ;
        if (vect.x==0) {
            if (vect.y>0) {angle=PI/2;}
            else{angle=-PI/2;}
        }
        if(vect.x>0){
            angle = std::atan(vect.y/vect.x);
        }
        if(vect.x<0){
            angle = std::atan(vect.y/vect.x);
            if (vect.y>0) {angle+=PI;}
            else{angle-=PI;}
        }
        return fmod(angle,2*PI);
    }

// Donne l'angle en degrés
    float vect2deg(sf::Vector2f vect){
        return vect2rad(vect)*180/PI;
    }

//Mesure la distance entre deux points grâce à la norme du vecteur reliant ces deux points
    float vect2dist(sf::Vector2f vect){
        float dist=sqrt(vect.x*vect.x+vect.y*vect.y);
        return dist;
    }

// calcul de la puissance utilisé pour le vaisseau 2
    float puissance(float dist,float distfr,float angsuivant){
        float p=100;
        if(dist<distfr){p=p*(1-sin(std::abs(angsuivant))*((distfr-dist)/distfr));}
        return p;    
    }



int main()
{
    sf::Clock clock; // démarre le chrono
    sf::RenderWindow window(sf::VideoMode(16000, 9000), "leopopo c'est le plus beau!");
    sf::View view(sf::FloatRect(0.f, 0.f, 16000.f, 9000.f));
    
    // Initialisation de la jauge direction/puissance du vaisseau 2
    sf::RectangleShape rectangle(sf::Vector2f(2000,20));
    rectangle.setFillColor(sf::Color::Green);
    sf::RectangleShape rectangle2(sf::Vector2f(2000,20));
    rectangle2.setFillColor(sf::Color::Red);
 

    // Initialisation des vaisseaux
    sf::Texture vaisseau1Texture;
    vaisseau1Texture.loadFromFile("../repository/Images/SWAnakinsPod.png");
    sf::Sprite vaisseau1;
    vaisseau1.setTexture(vaisseau1Texture);
    scaleToMaxSize(vaisseau1,800,800);
    auto rect=vaisseau1.getLocalBounds();
    vaisseau1.setOrigin(rect.width/2,rect.height/2);
    vaisseau1.setPosition(1000,1000);

    sf::Texture vaisseau2Texture;
    vaisseau2Texture.loadFromFile("../repository/Images/SWMilleniumFalcon.png");
    sf::Sprite vaisseau2;
    vaisseau2.setTexture(vaisseau2Texture);
    scaleToMaxSize(vaisseau2,800,800);
    auto rect2=vaisseau2.getLocalBounds();
    vaisseau2.setOrigin(rect2.width/2,rect2.height/2);
    vaisseau2.setPosition(1000,1000);

    //sf::Texture vaisseau3Texture;
    //vaisseau3Texture.loadFromFile("../repository/Images/SWAnakinsPod.png");
    //sf::Sprite vaisseau3;
    //vaisseau3.setTexture(vaisseau3Texture);
    //scaleToMaxSize(vaisseau3,800,800);
    //auto rect3=vaisseau3.getLocalBounds();
    //vaisseau3.setOrigin(rect3.width/2,rect3.height/2);
    //vaisseau3.setPosition(1000,1000);

    sf::Texture vaisseau4Texture;
    vaisseau4Texture.loadFromFile("../repository/Images/NMSFighterG.png");
    sf::Sprite vaisseau4;
    vaisseau4.setTexture(vaisseau4Texture);
    scaleToMaxSize(vaisseau4,800,800);
    auto rect4=vaisseau4.getLocalBounds();
    vaisseau4.setOrigin(rect4.width/2,rect4.height/2);
    vaisseau4.setPosition(1000,1000);

    // intitialisation du fond 
    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("../repository/Images/background.png");
    sf::Sprite background(backgroundTexture);
    scaleToMinSize(background,16000,9000);
    
    // création des checkpoints (arbitrairement), la liste est répétée 3 fois pour avoir 3 tours
    float CIBLEX[18]={10000,14000,9000,5000,1500,1000,10000,14000,9000,5000,1500,1000,10000,14000,9000,5000,1500,1000};
    float CIBLEY[18]={2000,7000,6000,8000,5000,1000,2000,7000,6000,8000,5000,1000,2000,7000,6000,8000,5000,1000};

    CheckPoint ch0(1000,1000,0);
    CheckPoint ch1(10000,2000,1);
    CheckPoint ch2(14000,7000,2);
    CheckPoint ch3(9000,6000,3);
    CheckPoint ch4(5000,8000,4);
    CheckPoint ch5(1500,5000,5);

    
    sf::Time elapsed1 = clock.getElapsedTime();
    sf::Time elapsed2 = clock.getElapsedTime();
    sf::Time elapsed3 = clock.getElapsedTime();
    sf::Time elapsed4 = clock.getElapsedTime();

    int fps=1; // initialisation
    
    //Initialisation des variables (position, vitesse, cible) de chaque vaisseau
    int icible=0;
    float ciblex=CIBLEX[icible];
    float cibley=CIBLEY[icible];
    
    int icible2=0;
    float ciblex2=CIBLEX[icible2];
    float cibley2=CIBLEY[icible2];
   
    // int icible3=0;
    // float ciblex3=CIBLEX[icible3];
    // float cibley3=CIBLEY[icible3];
   
    int icible4=0;
    float ciblex4=CIBLEX[icible4];
    float cibley4=CIBLEY[icible4];
    
    
    sf::Vector2f Vplus(0,0);
    sf::Vector2f Vmoin(0.09,0.01);
    sf::Vector2f U(0,0);
    sf::Vector2f Uplus(0,0);
    
    sf::Vector2f Vplus2(0,0);
    sf::Vector2f Vmoin2(0.09,0.01);
    sf::Vector2f U2(0,0);
    sf::Vector2f Uplus2(0,0);
    
    // sf::Vector2f Vplus3(0,0);
    // sf::Vector2f Vmoin3(0.09,0.01);
    // sf::Vector2f U3(0,0);
    // sf::Vector2f Uplus3(0,0);
    // float Cangle3=1.5;
    
    sf::Vector2f Vplus4(0,0);
    sf::Vector2f Vmoin4(0.09,0.01);
    sf::Vector2f U4(0,0);
    sf::Vector2f Uplus4(0,0);
    
    
    
    //Chargement de la police des FPS
    sf::Font font;
        if (!font.loadFromFile("../repository/Fredoka-Bold.ttf"))
        {
            // error...
        }
    sf::Text textfps;
    textfps.setFont(font); 
    textfps.setCharacterSize(300); 
    textfps.setOutlineThickness(20);
    textfps.setPosition(15000,300);
    textfps.setFillColor(sf::Color(255, 255, 255, 255));
    char temp[256];
    sprintf(temp, "FPS: %d", fps);
    textfps.setString(sf::String(temp));

    clock.restart();

    
    //Boucle d'affichage de l'interface graphique
    while (window.isOpen())
    {   
        // pour l'actualisation des fps
        if(1==1){
            elapsed1 = clock.getElapsedTime();
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }
            if(elapsed1.asSeconds()-elapsed2.asSeconds()>=1){
                // printf("%d \n",fps);
                elapsed2 = clock.getElapsedTime();

                sprintf(temp, "FPS: %d", fps);
                textfps.setString(sf::String(temp));

                fps=0;
            }
            else{
                fps++;
            }
        }
        window.clear();
        window.draw(background);
        
        
        
        //======================================= V1 ==============================
        // Vaisseau élémentaire
        
        // On vérifie si on a atteint le checkpoint, si oui, on change de cible (nouveau checkpoint)
        U=vaisseau1.getPosition();
        if(near(ciblex,cibley,U,600)==1){
            icible++;
            ciblex=CIBLEX[icible];
            cibley=CIBLEY[icible];
        }
        
        sf::Vector2f C(ciblex,cibley); // On actualise la cible
        float Cangle=vect2rad(U-C); // Calcul de l'angle entre la droite reliant le vaisseau et le checkpoint et l'horizontale.
        float p=100; // La puissance est toujours maximale

        sf::Vector2f Cbis(cos(Cangle),sin(Cangle));
        Vplus=float(0.85)*(Vmoin-p*Cbis); // On crée vecteur vitesse
        // On vérifie que l'écart ne dépasse pas pi/10
        if (mod(vect2rad(Vplus)-vect2rad(Vmoin),2*PI)<-PI/10 ){
            float Vangle=vect2rad(Vmoin);
            sf::Vector2f Vnorm(cos(Vangle-PI/10),sin(Vangle-PI/10));
            Vplus=vect2dist(Vplus)*Vnorm;
            }
        if (mod(vect2rad(Vplus)-vect2rad(Vmoin),2*PI)>PI/10 ){
            float Vangle=vect2rad(Vmoin);
            sf::Vector2f Vnorm(cos(Vangle+PI/10),sin(Vangle+PI/10));
            Vplus=vect2dist(Vplus)*Vnorm;
        }
        // Actualisation des positions
        Uplus=U+Vplus;
        Vmoin=Vplus;

        // actualisation graphique
        vaisseau1.setPosition(Uplus);
        vaisseau1.setRotation(vect2deg(Vplus)); 

//======================================================== V2 ==================================================
// Intelligent
        U2=vaisseau2.getPosition();
        if(near(ciblex2,cibley2,U2,600)==1){
            icible2++;
            ciblex2=CIBLEX[icible2];
            cibley2=CIBLEY[icible2];
        }

        sf::Vector2f C2(ciblex2,cibley2);
        float Cangle2=vect2rad(U2-C2);
        // printf("%f \n",mod(mod(vect2deg(-Vmoin2),360)-mod(vect2deg(U2-C2),360),360));
        if (abs(mod(vect2deg(-Vmoin2)-vect2deg(U2-C2),360))<90){
            Cangle2=Cangle2+vect2dist(U2-C2)*(-mod(mod(vect2deg(-Vmoin2),360)-mod(vect2deg(U2-C2),360),360))*0.000002;
        }
        // actualisation de la jauge
        rectangle.setRotation(180+Cangle2*180/PI);rectangle2.setRotation(180+Cangle2*180/PI);
        rectangle.setPosition(U2);rectangle2.setPosition(U2);
        
        sf::Vector2f suiv2(CIBLEX[icible2]-CIBLEX[icible2+1],CIBLEY[icible2]-CIBLEY[icible2+1]);
        float p2=puissance(vect2dist(U2-C2),3000,(-mod(vect2rad(suiv2)-vect2rad(U2-C2),2*PI))); // Calcul de la puissance
        rectangle2.setSize(sf::Vector2f(p2*20,20));
        

        // printf("%f %f %f \n",Cangle2,Canglemoin2,mod(Cangle2-Canglemoin2,2*PI));
        sf::Vector2f Cbis2(cos(Cangle2),sin(Cangle2));
        Vplus2=float(0.85)*(Vmoin2-p2*Cbis2);
        if (mod(vect2rad(Vplus2)-vect2rad(Vmoin2),2*PI)<-PI/10 ){
            float Vangle=vect2rad(Vmoin2);
            sf::Vector2f Vnorm(cos(Vangle-PI/10),sin(Vangle-PI/10));
            Vplus2=vect2dist(Vplus2)*Vnorm;
        }
        if (mod(vect2rad(Vplus2)-vect2rad(Vmoin2),2*PI)>PI/10 ){
            float Vangle=vect2rad(Vmoin2);
            sf::Vector2f Vnorm(cos(Vangle+PI/10),sin(Vangle+PI/10));
            Vplus2=vect2dist(Vplus2)*Vnorm;
        }
        // actualisation de la position
        Uplus2=U2+Vplus2;
        Vmoin2=Vplus2;
        
        // Actualisation graphique
        vaisseau2.setPosition(Uplus2);
        vaisseau2.setRotation(vect2deg(Vplus2));
        
        

//========================================================= v3 =============================================
        // Cette partie de code est commentée car le vaisseau qui y est associé est dirigé à l'aide des flèches du clavier et ce n'est pas pratique, 
        // nous avons préféré laisser celui dirigé avec la souris
        
        // U3=vaisseau3.getPosition();
        // if(near(ciblex3,cibley3,U3,600)==1){
        //     icible3++;
        //     ciblex3=CIBLEX[icible3];
        //     cibley3=CIBLEY[icible3];
        // }
        
        // sf::Vector2f C3(ciblex3,cibley3);
        // float p3=10;
        // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        // {
        //     Cangle3-=PI/10;
        // }
        // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        // {
        //     Cangle3+=PI/10;
        // }
        // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        // {
        //     p3=100;
        // }

        // sf::Vector2f Cbis3(cos(Cangle3),sin(Cangle3));
        // Vplus3=float(0.85)*(Vmoin3-p3*Cbis3);
        // if (mod(vect2rad(Vplus3)-vect2rad(Vmoin3),2*PI)<-PI/10 ){
        //     float Vangle=vect2rad(Vmoin3);
        //     sf::Vector2f Vnorm(cos(Vangle-PI/10),sin(Vangle-PI/10));
        //     Vplus3=vect2dist(Vplus3)*Vnorm;
        //     }
        // if (mod(vect2rad(Vplus)-vect2rad(Vmoin),2*PI)>PI/10 ){
        //     float Vangle=vect2rad(Vmoin3);
        //     sf::Vector2f Vnorm(cos(Vangle+PI/10),sin(Vangle+PI/10));
        //     Vplus3=vect2dist(Vplus3)*Vnorm;
        // }
        // Uplus3=U3+Vplus3;
        // Vmoin3=Vplus3;


        // vaisseau3.setPosition(Uplus3);
        // vaisseau3.setRotation(vect2deg(Vplus3));

//=============================================================== v4 =====================================================
// Vaisseau dirigé à la souris
        
        // Récupération de la position relative de la souris par rapport à la fenêtre
        sf::Vector2i CC4 = sf::Mouse::getPosition(window);
        sf::Vector2f C4=sf::Vector2f(CC4.x*16000/window.getSize().x, CC4.y*9000/window.getSize().y);
        
        U4=vaisseau4.getPosition();
        
        if(near(ciblex4,cibley4,U4,600)==1){
            // Surbrillance verte pour signaler le passage dans le chackpoint
            sf::CircleShape circle(600.f);
            circle.setFillColor(sf::Color(0, 0, 0, 63));
            circle.setOutlineThickness(50);
            circle.setOutlineColor(sf::Color(0, 255, 0));
            circle.setPosition(ciblex4-600,cibley4-600);
            window.draw(circle);

            icible4++;
            ciblex4=CIBLEX[icible4];
            cibley4=CIBLEY[icible4];
        }
        
        float Cangle4=vect2rad(U4-C4);
        float p4=10; // Si on n'appuie pas sur la touche espace (on met à 10 pour pouvoir tourner à l'arrêt)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            p4=100;
        }

        sf::Vector2f Cbis4(cos(Cangle4),sin(Cangle4));
        Vplus4=float(0.85)*(Vmoin4-p4*Cbis4);
        if (mod(vect2rad(Vplus4)-vect2rad(Vmoin4),2*PI)<-PI/10 ){
            float Vangle=vect2rad(Vmoin4);
            sf::Vector2f Vnorm(cos(Vangle-PI/10),sin(Vangle-PI/10));
            Vplus4=vect2dist(Vplus4)*Vnorm;
            }
        if (mod(vect2rad(Vplus4)-vect2rad(Vmoin4),2*PI)>PI/10 ){
            float Vangle=vect2rad(Vmoin4);
            sf::Vector2f Vnorm(cos(Vangle+PI/10),sin(Vangle+PI/10));
            Vplus4=vect2dist(Vplus4)*Vnorm;
        }
        Uplus4=U4+Vplus4;
        Vmoin4=Vplus4;


        vaisseau4.setPosition(Uplus4);
        vaisseau4.setRotation(vect2deg(Vplus4));

        // Affichage de tous les éléments sauf le background déjà affiché en amont
        window.draw(vaisseau1);
        window.draw(vaisseau2);
        // window.draw(vaisseau3);
        window.draw(vaisseau4);
        window.draw(rectangle);  
        window.draw(rectangle2); 
        window.draw(ch0); 
        window.draw(ch1); 
        window.draw(ch2);  
        window.draw(ch3); 
        window.draw(ch4); 
        window.draw(ch5); 
        window.draw(textfps); 
        window.setView(view);
        window.display();






        // le if(1==1) sert pour pouvoir cacher le code sous vscode
        if(1==1){ 
            // pour obtenir un temps constant
            elapsed3 = clock.getElapsedTime();
            while(elapsed3.asSeconds()-elapsed4.asSeconds()<=0.1){
                elapsed3 = clock.getElapsedTime();
            }
            elapsed4 = clock.getElapsedTime();

        }
    }
    return 0;
}
