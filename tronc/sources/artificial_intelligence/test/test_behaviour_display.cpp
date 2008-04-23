#include <artificial_intelligence/implementation/vehicle.h>
#include <artificial_intelligence/implementation/steering_behaviour.h>
#include <kernel/string.h>
#include <kernel/parameters.h>
#include <kernel/log.h>
#include <ClanLib/core.h>
#include <ClanLib/application.h>
#include <ClanLib/display.h>
#include <ClanLib/gl.h>
#include <ClanLib/ttf.h>

using namespace ProjetUnivers::Kernel ;

#include <stdio.h>
#include <time.h>

using namespace ProjetUnivers::ArtificialIntelligence::Implementation ;

// wait some time
void wait (float seconds)
{
  clock_t endwait;
  endwait = clock () + (int)(seconds * CLOCKS_PER_SEC) ;
  while (clock() < endwait) {}
}

// screen size
const int size = 300 ;

class TestBehaviour : public CL_ClanApplication
{
public:

  virtual char *get_title() 
  { 
    return "TestBehaviour"; 
  }
  
  virtual int main(int argc, char **argv)
  {
    ProjetUnivers::Kernel::Parameters::load("test.config") ;
    ProjetUnivers::Kernel::Log::init() ;
    CL_SetupCore::init();
    CL_SetupDisplay::init();
    CL_SetupTTF::init();
    
    // Insert game code here
    CL_Display::set_videomode(size,size,8) ;

    CL_ResourceManager* resources = new CL_ResourceManager("ttf.scr", false);
    
    // Load in the font
    CL_Font *font = CL_Font::load("Fonts/fnt_clansoft", resources);

    // A vehicle to seek (not too speedy to be able to catch it)
    Vehicle target(Ogre::Vector3(50,100,0),
                   Ogre::Quaternion(),
                   Ogre::Vector3(0,5,0),
                   9) ;
    
    std::set<Vehicle*> targets ;
    targets.insert(&target) ;
    
    // A vehicle seeking
    Vehicle seeker(Ogre::Vector3(0,50,0),
                   Ogre::Quaternion(),
                   Ogre::Vector3(-5,0,0),
                   10) ;
    
    Ogre::Vector3 zero = Ogre::Vector3::ZERO ;
    
    // A "simulation" loop : calculate steering and apply it 
    for(int i = 1 ; i <= 1000 ; ++i)
    {
      font->change_size(20);
      font->change_colour(80,210,110,255);

      CL_Display::clear_display() ;

//      Ogre::Vector3 steering_target = SteeringBehaviour::evade(target,seeker) ;
//      target.simulate(steering_target) ;
      target.simulate(zero) ;

      Ogre::Vector3 steering = SteeringBehaviour::pursuit(seeker,target) ;
      Ogre::Vector3 steering2 = SteeringBehaviour::separate(seeker,targets,0.1) ; 
      if (steering2.length() != 0)
        steering = steering2 ;
//      steering += steering2 ; 
      font->print_center(size/2,size/2, "separation x =" + toString(steering2.x)) ;
      font->print_center(size/2,size/2+10, "separation y =" + toString(steering2.y)) ;
      
      seeker.simulate(steering) ;

      displayVehicle(seeker,true) ;
      displayVehicle(target,false) ;

//      wait(0.02) ;
      // refresh
      CL_Display::flip_display() ;
    }
    
    CL_SetupCore::deinit();
    CL_SetupDisplay::deinit();
    return 1;
  }
  
  void displayVehicle(const Vehicle& vehicle, bool seeker)
  {
    Ogre::Vector3 position(vehicle.getPosition()) ;
    
    int x = (int)(position.x) ;
    int y = (int)(position.y) ;
    
    if (fabs(x)>size)
      x = x%size ;
    if (x<0)
      x += size ;
    if (fabs(y)>size)
      y = y%size ;
    if (y<0)
      y += size ;
    
    const float size = 10 ;
    
    Ogre::Vector3 forward = vehicle.getForward() ;
    forward.normalise() ;
    
    forward *= size/2 ;
    
    Ogre::Vector3 side = vehicle.getSide() ;
    side.normalise() ;
    side *= size/3 ;
    
    // a triangle heading to forward
    CL_Display::draw_line((int)(x+forward.x),
                          (int)(y+forward.y),
                          (int)(x+side.x-forward.x),
                          (int)(y+side.y-forward.y),seeker?1:0,seeker?0:1,0) ;
    CL_Display::draw_line((int)(x+forward.x),
                          (int)(y+forward.y),
                          (int)(x-side.x-forward.x),
                          (int)(y-side.y-forward.y),seeker?1:0,seeker?0:1,0) ;

    CL_Display::draw_line((int)(x+side.x-forward.x),
                          (int)(y+side.y-forward.y),
                          (int)(x-side.x-forward.x),
                          (int)(y-side.y-forward.y),seeker?1:0,seeker?0:1,0) ;
    
  }
  
} application ;
