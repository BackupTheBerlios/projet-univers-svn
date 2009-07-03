#include <artificial_intelligence/implementation/vehicle.h>
#include <artificial_intelligence/implementation/steering_behaviour.h>
#include <kernel/string.h>
#include <kernel/parameters.h>
#include <kernel/log.h>
#include <ClanLib/core.h>
#include <ClanLib/application.h>
#include <ClanLib/display.h>
#include <ClanLib/gl.h>

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
    CL_SetupCore core ;
    CL_SetupDisplay display;
    CL_SetupGL gl ;

    // Insert game code here
    window = CL_DisplayWindow("TicTacToeApp",size,size) ;
    CL_Display::set_current_window(&window) ;
    gc = window.get_gc() ;

    testSeekStatic() ;
//    testPursuitEvade() ;
//    testAvoidObstacle() ;


    return 1;
  }

  void testSeekStatic()
  {
    // A vehicle to seek (not too speedy to be able to catch it)
    Vehicle target(Ogre::Vector3(50,0,100),
                   Ogre::Quaternion(),
                   Ogre::Vector3(0,0,0),
                   9) ;

    // A vehicle seeking
    Vehicle seeker(Ogre::Vector3(25,0,50),
                   Ogre::Quaternion(),
                   Ogre::Vector3(0,0,5),
                   10) ;

    seeker.setTurningRate(Ogre::Degree(90)) ;

    Ogre::Vector3 zero = Ogre::Vector3::ZERO ;

    // A "simulation" loop : calculate steering and apply it
    for(int i = 1 ; i <= 1000 ; ++i)
    {

      gc->clear() ;

      Ogre::Vector3 steering = SteeringBehaviour::offsetPursuit(seeker,target,Ogre::Vector3(0,0,-target.getRadius())) ;

      seeker.simulate(steering,1) ;

      displayVehicle(seeker,true) ;
      displayVehicle(target,false) ;
      displaySteering(seeker,steering) ;

      wait(0.01) ;
      // refresh
      window.flip() ;
    }
  }

  void testPursuitEvade()
  {
    // A vehicle to seek (not too speedy to be able to catch it)
    Vehicle target(Ogre::Vector3(50,0,100),
                   Ogre::Quaternion(),
                   Ogre::Vector3(0,0,5),
                   9) ;

    std::set<Vehicle*> targets ;
    targets.insert(&target) ;

    // A vehicle seeking
    Vehicle seeker(Ogre::Vector3(0,0,50),
                   Ogre::Quaternion(),
                   Ogre::Vector3(-5,0,0),
                   10) ;
    Ogre::Vector3 zero = Ogre::Vector3::ZERO ;

    // A "simulation" loop : calculate steering and apply it
    for(int i = 1 ; i <= 1000 ; ++i)
    {
//      font->change_size(20);
//      font->change_colour(80,210,110,255);

      CL_Display::clear() ;

      Ogre::Vector3 steering_target = SteeringBehaviour::evade(target,seeker) ;
      target.simulate(steering_target,1) ;
//      target.simulate(zero) ;

      Ogre::Vector3 steering = SteeringBehaviour::offsetPursuit(seeker,target,Ogre::Vector3(0,0,-target.getRadius())) ;
//      Ogre::Vector3 steering2 = SteeringBehaviour::separate(seeker,targets,0.1) ;
//      if (steering2.length() != 0)
//        steering = steering2 ;
//      steering += steering2 ;
//      font->print_center(size/2,size/2, "separation x =" + toString(steering2.x)) ;
//      font->print_center(size/2,size/2+10, "separation y =" + toString(steering2.y)) ;

      seeker.simulate(steering,1) ;

      displayVehicle(seeker,true) ;
      displayVehicle(target,false) ;

      displaySteering(seeker,steering) ;

      wait(0.02) ;
      // refresh
      CL_Display::flip() ;
    }

  }


  void testAvoidObstacle()
  {
    // A vehicle to seek (not too speedy to be able to catch it)
    Vehicle target(Ogre::Vector3(0,0,0),
                   Ogre::Quaternion(),
                   Ogre::Vector3(0,0,0),
                   9) ;

    std::set<Vehicle*> obstacles ;

    Vehicle obstacle1(Ogre::Vector3(50,0,0),
                      Ogre::Quaternion(),
                      Ogre::Vector3(0,0,0)) ;

    Vehicle obstacle2(Ogre::Vector3(120,0,100),
                      Ogre::Quaternion(),
                      Ogre::Vector3(0,0,0)) ;

    Vehicle obstacle3(Ogre::Vector3(135,0,80),
                      Ogre::Quaternion(),
                      Ogre::Vector3(0,0,0)) ;

    obstacles.insert(&obstacle1) ;
//    obstacles.insert(&obstacle2) ;
//    obstacles.insert(&obstacle3) ;
//

    // A vehicle seeking
    Vehicle seeker(Ogre::Vector3(100,0,0),
                   Ogre::Quaternion(),
                   Ogre::Vector3(0,0,0),
                   10) ;

    seeker.setTurningRate(Ogre::Degree(10)) ;

    Ogre::Vector3 zero = Ogre::Vector3::ZERO ;

    // A "simulation" loop : calculate steering and apply it
    for(int i = 1 ; i <= 1000 ; ++i)
    {
      CL_Display::clear() ;

      for(std::set<Vehicle*>::iterator obstacle = obstacles.begin() ;
          obstacle != obstacles.end() ;
          ++obstacle)
      {
        displayObstacle(**obstacle) ;
        if ((seeker.getPosition()-(*obstacle)->getPosition()).length() <
            (seeker.getRadius()+(*obstacle)->getRadius()))
          std::cout << "collision" << std::endl ;

      }

      Ogre::Vector3 steering = SteeringBehaviour::seek(seeker,target) ;
      Ogre::Vector3 avoidance = SteeringBehaviour::obstacleAvoidance(seeker,obstacles) ;

      if (avoidance.length()>0)
        seeker.simulate(avoidance) ;
      else
        seeker.simulate(steering) ;


      displayVehicle(seeker,true) ;
      displayVehicle(target,false) ;

      displaySteering(seeker,steering) ;

      wait(0.08) ;

      // refresh
      CL_Display::flip() ;
    }

  }

  Ogre::Vector3 convert(const Ogre::Vector3& position)
  {
    int x = (int)(position.x) ;
    int z = (int)(position.z) ;

    if (fabs(x)>size)
      x = x%size ;
    if (x<0)
      x += size ;
    if (fabs(z)>size)
      z = z%size ;
    if (z<0)
      z += size ;

    return Ogre::Vector3(x,0,z) ;
  }

  void displayVehicle(const Vehicle& vehicle, bool seeker)
  {
    Ogre::Vector3 position(convert(vehicle.getPosition())) ;

    const float size = 10 ;

    Ogre::Vector3 forward = vehicle.getForward() ;
    forward.normalise() ;

    forward *= size/2 ;

    Ogre::Vector3 side = vehicle.getSide() ;
    side.normalise() ;
    side *= size/3 ;

    // a triangle heading to forward
    CL_Display::draw_line((int)(position.x+forward.x),
                          (int)(position.z+forward.z),
                          (int)(position.x+side.x-forward.x),
                          (int)(position.z+side.z-forward.z),
                          CL_Color(seeker?1:0,seeker?0:1,0)) ;
    CL_Display::draw_line((int)(position.x+forward.x),
                          (int)(position.z+forward.z),
                          (int)(position.x-side.x-forward.x),
                          (int)(position.z-side.z-forward.z),
                          CL_Color(seeker?1:0,seeker?0:1,0)) ;

    CL_Display::draw_line((int)(position.x+side.x-forward.x),
                          (int)(position.z+side.z-forward.z),
                          (int)(position.x-side.x-forward.x),
                          (int)(position.z-side.z-forward.z),
                          CL_Color(seeker?1:0,seeker?0:1,0)) ;

    displayObstacle(vehicle) ;
  }

  void displayObstacle(const Vehicle& vehicle)
  {
    const float pi = 3.14159265 ;

    Ogre::Vector3 position(convert(vehicle.getPosition())) ;

    for (int angle=0 ; angle <= 360 ; ++angle)
    {
      int x = (int)(position.x+vehicle.getRadius()*cos(pi*angle/180)) ;
      int z = (int)(position.z+vehicle.getRadius()*sin(pi*angle/180)) ;

      CL_Display::draw_line(x,z,x,z,CL_Color(0,1,0)) ;
    }
  }

  void displaySteering(const Vehicle& vehicle,const Ogre::Vector3& force)
  {
    Ogre::Vector3 position(convert(vehicle.getPosition())) ;
    Ogre::Vector3 steering(convert(vehicle.getPosition()+force)) ;

    CL_Display::draw_line((int)position.x,(int)position.z,(int)steering.x,(int)steering.z,CL_Color(0,1,0)) ;

  }

  CL_GraphicContext* gc ;
  CL_DisplayWindow window ;

} application ;
