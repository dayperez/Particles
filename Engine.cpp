#include "Engine.h"




Engine::Engine(){ 
  
   m_Window.create(VideoMode::getDesktopMode(), "Particles");

    if(!m_Music.openFromFile("1979.ogg")){

        cerr << "Error: Could not file '1979.ogg";
    }
    else {

        m_Music.setLoop(true);
        m_Music.play();
    }

    if(!m_BackgroundTexture.loadFromFile("Galaxy.png")){
        cerr << "Error: Could not load background image 'Galaxy.png'";
    }
    else{

        m_BackgroundSprite.setTexture(m_BackgroundTexture);

        Vector2u windowSize = m_Window.getSize();
        Vector2u textureSize = m_BackgroundTexture.getSize();

        float xScale = (float)windowSize.x / textureSize.x;
        float yScale = (float)windowSize.y / textureSize.y;

        m_BackgroundSprite.setScale(xScale, yScale);
    }

}




void Engine::run(){


   Clock clock;


   cout << "Starting Particle unit tests..." << endl;
   Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 });
   p.unitTests();
   cout << "Unit tests complete.  Starting engine..." << endl;


   while(m_Window.isOpen()){


       Time dt = clock.restart();
       float dtAsSeconds = dt.asSeconds();


       input();


       update(dtAsSeconds);


       draw();
   }




}




void Engine::input(){


   Event event;


   while(m_Window.pollEvent(event)){


       if (event.type == Event::Closed || event.type == Event::KeyPressed && event.key.code == Keyboard::Escape){


           m_Window.close();
       }


       if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left){


           Vector2i mouseClickPosition = {event.mouseButton.x, event.mouseButton.y};


           int numParticles = 5;


           for (int i = 0; i < numParticles; i++){


               int numPoints = (rand() % (50 - 25 + 1)) + 25;


               Particle newParticle(m_Window, numPoints, mouseClickPosition);


               m_particles.push_back(newParticle);
           }
       }
   }






}




void Engine::update(float dtAsSeconds){


   for (int i = 0; i < m_particles.size();){


       if (m_particles[i].getTTL() > 0.0){


           m_particles[i].update(dtAsSeconds);
          
           i++;
       }
       else {


           m_particles.erase(m_particles.begin() + i);
       }
   }




}




void Engine::draw(){

    m_Window.draw(m_BackgroundSprite);


   for (int i = 0; i < m_particles.size(); i++){

       m_Window.draw(m_particles[i]);
   }


   m_Window.display();


}




