/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2012 Centre Tecnologic de Telecomunicacions de Catalunya (CTTC)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Nicola Baldo <nbaldo@cttc.es>
 */


#ifndef RADIO_ENVIRONMENT_MAP_HELPER_H
#define RADIO_ENVIRONMENT_MAP_HELPER_H


#include <ns3/object.h>



namespace ns3 {

class RemSpectrumPhy;
class Node;
class NetDevice;
class SpectrumChannel;
class BuildingsMobilityModel;

/** 
 * Generates a 2D map of the SINR from the strongest transmitter. 
 * 
 */
class RadioEnvironmentMapHelper : public Object
{
public:  

  RadioEnvironmentMapHelper ();

  virtual ~RadioEnvironmentMapHelper ();
  
  // inherited from Object
  virtual void DoDispose (void);
  static TypeId GetTypeId (void);

  void Install ();

private:

  void Connect ();
  void PrintAndDeactivate ();


  struct RemPoint 
  {
    Ptr<RemSpectrumPhy> phy;
    Ptr<Node> node;
    Ptr<NetDevice> dev;
    Ptr<BuildingsMobilityModel> bmm;
  };

  std::list<std::list<RemPoint> > m_rem;

  double m_xMin;
  double m_xMax;
  uint32_t m_xRes;

  double m_yMin;
  double m_yMax;
  uint32_t m_yRes;
  
  double m_z;

  std::string m_channelPath;
  std::string m_outputFile;

  bool m_exitWhenDone;
  
  Ptr<SpectrumChannel> m_channel;
};


}

#endif /* RADIO_ENVIRONMENT_MAP_HELPER_H */
