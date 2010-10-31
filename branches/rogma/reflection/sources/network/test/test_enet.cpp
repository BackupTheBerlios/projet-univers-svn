// enet example application, written 2006-06-27 by gerald.franz at viremo.de
// based on the enet tutorial. Thanks to the original author!

// modifications made accoarding following licence
/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2010 Mathieu ROGER                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include <enet/enet.h>

extern "C"
{
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
}
#include <iostream>

#include <sys/timeb.h>
#if !defined (WIN32)
#  include <sys/time.h>
#else
# include <windows.h>
#endif

//--- function timestamp-------------------------------------------
double timestamp()
{
#if defined (WIN32)
  __int64 freq, count ;
  //check for high resolution timer
  if(QueryPerformanceFrequency((LARGE_INTEGER*)&freq))
  {
    //high resolution timer available - use it!
    double dResolution = 1.0 / (double)freq ;
    QueryPerformanceCounter((LARGE_INTEGER*)&count) ;
    return (double)count * dResolution ;
  }
  else
  {
    struct timeb tp ;
    ftime(&tp) ;
    return (double)tp.time+0.001*(double)tp.millitm ;
  }
#else
  static struct timeval time ;
  gettimeofday(&time, 0) ;
  static long secsFirstCall = time.tv_sec ;
  return (double) (time.tv_sec - secsFirstCall) + (double) time.tv_usec
      / (1000.0 * 1000.0) ;
#endif
}

//--- main---------------------------------------------------------

int main(int argc,char ** argv)
{
  // basic traffic control variables:

  // size of a single packet to be sent
  unsigned int packetSize = 256 ;

  // number of packets to be sent per frame
  unsigned int nPackets = 8 ;

  // total number of packets to before application terminates, use 0 to disable
  unsigned int nPacketsMax = 200000 ;

  // number of milliseconds to wait for network events, corresponding to time between frames
  unsigned int waitTime = 5 ;

  // should complete traffic be dumped to stdout?
  int verbose = 0 ;

  if (argc < 2)
  {
    std::cerr << "usage: " << argv[0] << " port [server name]\n" ;
    return 1 ;
  }

  // network initialization:
  if (enet_initialize() != 0)
  {
    std::cerr << "An error occurred while initializing ENet.\n" ;
    return 1 ;
  }
  atexit(enet_deinitialize) ;

  enet_time_set(0) ;
  ENetEvent event ;
  ENetHost * host = 0 ;
  ENetPeer * peer = 0 ;
  ENetAddress address ;
  // bind connection to this port
  address.port = atoi(argv[1]) ;
  int isServer = (argc < 3) ? 1 : 0 ;

  if (argc < 3)
  { // initialize server:
    std::cout << ("I am server...\n") ;
    std::cout.flush() ;

    // localhost
    address.host = ENET_HOST_ANY ;
    host = enet_host_create(&address, // the address to bind the server host to
                            32, // allow only 1 client and/or outgoing connections
                            0, // assume any amount of incoming bandwidth
                            0) ; // assume any amount of outgoing bandwidth

    if (!host)
    {
      std::cerr <<  "An error occurred while trying to create an ENet server host.\n" ;
      exit(EXIT_FAILURE) ;
    }
  }
  else
  { // initialize client:
    std::cout << "I am client...\n" ;
    std::cout.flush() ;

    host = enet_host_create(0, // create a client host
                            1, // allow only 1 outgoing connection
                            0, // use 57600 / 8 for 56K modem with 56 Kbps downstream bandwidth
                            0) ;// use 14400 / 8 for 56K modem with 14 Kbps upstream bandwidth

    if (!host)
    {
      std::cerr << "An error occurred while trying to create an ENet client host.\n" ;
      exit(EXIT_FAILURE) ;
    }

    // connect to server:
    enet_address_set_host(&address, argv[2]) ;
    peer = enet_host_connect(host, &address, 2) ;

    // use this as mark that connection is not yet acknowledged
    peer->data = 0 ;
    if (!peer)
    {
      std::cerr << "No available peers for initiating an ENet connection.\n" ;
      exit(EXIT_FAILURE) ;
    }
  }

  unsigned int sendCounter = 0 ;
  unsigned int recvCounter = 0 ;
  unsigned int sendPerSec = 0, recvPerSec = 0 ;
  double tLastFps = timestamp() ;
  unsigned int fps = 0 ;

  // main loop:
  int running = 1 ;
  while (running)
  {
    double tNow = timestamp() ;
    ++fps ;
    if (tNow >= tLastFps + 1.0)
    {
      printf("%f secs, %u fps, containers sent per sec:%u recv:%u total sent:%u recv: %u\n",
             tNow - tLastFps, fps, sendPerSec, recvPerSec, sendCounter,
             recvCounter) ;
      fflush(stdout) ;
      sendPerSec = recvPerSec = fps = 0 ;
      tLastFps = tNow ;
    }

    // processing incoming events:
    while (running && (enet_host_service(host, &event, waitTime) > 0))
    {
      switch (event.type)
      {
      case ENET_EVENT_TYPE_CONNECT:
      {
        printf("  A new connected has been established to %u:%u\n",
               event.peer -> address.host, event.peer -> address.port) ;
        fflush(stdout) ;

        char buf[64] ;
        sprintf(buf, "%u:%u", event.peer->address.host,
                event.peer -> address.port) ;
        int buflen = strlen(buf) ;
        event.peer -> data = malloc(buflen + 1) ;
        strncpy((char*) event.peer->data, buf, buflen) ;
        peer = event.peer ;
        break ;
      }
      case ENET_EVENT_TYPE_RECEIVE:
        ++recvCounter ;
        ++recvPerSec ;

        if (verbose)
        {
          printf("  A packet of length %u containing [%s] was received from %s on channel %u\n",
                 event.packet ->dataLength, event.packet -> data,
                 (char*) event.peer ->data, event.channelID) ;
          fflush(stdout) ;
        }

        // clean up the packet now that we're done using it
        enet_packet_destroy(event.packet) ;
        break ;

      case ENET_EVENT_TYPE_DISCONNECT:
        printf("  host disconnected.\n") ;
        fflush(stdout) ;
        free(event.peer -> data) ;
        // reset the peer's client information.
        event.peer -> data = 0 ;
        peer = 0 ;
        running = 0 ;
      default:
        break ;
      }
    }

    if (peer && peer->data)
    { // send some data:
      unsigned int i ;
      for (i = 0 ; i < nPackets ; ++i)
      {
        char * data = (char*) malloc(packetSize) ;
        int reliable = sendCounter % 2 ;
        ++sendPerSec ;
        sprintf(data, "msg by %s:%u, %s", isServer ? "server" : "client",
                ++sendCounter, reliable ? "reliable" : "unreliable") ;
        //warning: packet size must be large enough for all this information
        ENetPacket * packet =
            enet_packet_create(data, 256, reliable ? ENET_PACKET_FLAG_RELIABLE
                                                   : 0) ;

        // queue the packet to be sent to the peer over channel id 0
        enet_peer_send(peer, reliable, packet) ;
        free(data) ;
      }

      //enet_host_flush (host); // not necessary, included in enet_host_service
    }

    // gently terminate connection from client side after nPacketsMax:
    if (nPacketsMax && peer && !isServer && sendCounter >= nPacketsMax)
    {
      printf("disconnecting after %u sent packages...\n", nPacketsMax) ;
      fflush(stdout) ;
      enet_peer_disconnect(peer, 0) ;
    }
  } // main loop

  if (peer)
  {
    printf("resetting peer...") ;
    fflush(stdout) ;
    enet_peer_reset(peer) ;
    printf(" done.\n") ;
  }

  printf("closing down...") ;
  fflush(stdout) ;
  enet_host_destroy(host) ;
  printf(" done.\n") ;
  return 0 ;
}

