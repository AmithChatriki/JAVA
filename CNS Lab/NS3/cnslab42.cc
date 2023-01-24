#include "ns3/core-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/network-module.h"
#include "ns3/applications-module.h"
#include "ns3/wifi-module.h"
#include "ns3/mobility-module.h"
#include "ns3/internet-module.h"

// Default Network Topology
//
// Number of wifi or csma nodes can be increased up to 250
//                          |
// -------------------------|----------------------------
//   Wifi 10.1.3.0
//                 AP
//  *    *    *    *
//  |    |    |    |    10.1.1.0
// n5   n6   n7   n0 -------------- n1   
//                   point-to-point  |    
//                                   ================

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("ThirdScriptExample");

int 
main (int argc, char *argv[])
{
  //bool verbose = true;
  uint32_t nWifi = 3;
 // bool tracing = false;

  CommandLine cmd;
  //cmd.AddValue ("nWifi", "Number of wifi STA devices", nWifi);
  //cmd.AddValue ("verbose", "Tell echo applications to log if true", verbose);
 // cmd.AddValue ("tracing", "Enable pcap tracing", tracing);

  cmd.Parse (argc,argv);

  //if (verbose)
  //  {
     // LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO);
    //  LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);
   // }

  NodeContainer p2pNodes;
  p2pNodes.Create (2);

  PointToPointHelper pointToPoint;
  pointToPoint.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
  pointToPoint.SetChannelAttribute ("Delay", StringValue ("2ms"));

  NetDeviceContainer p2pDevices;
  p2pDevices = pointToPoint.Install (p2pNodes);

  NodeContainer wifiStaNodes;
  wifiStaNodes.Create (nWifi);
  NodeContainer wifiApNode = p2pNodes.Get (0);

//YansWifiChannelHelper-manage and create wifi channel objects for the yans model. 
//YansWifiPhyHelper-create and manage PHY objects for the YANS model. 

  YansWifiChannelHelper channel = YansWifiChannelHelper::Default ();
  YansWifiPhyHelper phy = YansWifiPhyHelper::Default ();
  phy.SetChannel (channel.Create ());

//SetRemoteStationManager-Holds a list of remote station states.  

  WifiHelper wifi;
  wifi.SetRemoteStationManager ("ns3::AarfWifiManager");

//AARF-Adptive Auto Rate Fallback i.e Rate Control algorithm


//StaWifiMac-This class can create MACs of type ns3::ApWifiMac, ns3::StaWifiMac and ns3::AdhocWifiMac. Its purpose is to allow a WifiHelper to configure and install WifiMac objects on a collection of nodes. 
  

//ActiveProbing: If true, we send probe requests. If false, we don't. NOTE: if more than one STA in your simulation is using active probing, you should enable it at a different simulation time for each STA, otherwise all the STAs will start sending probes at the same time resulting in collisions. 


WifiMacHelper mac;
  Ssid ssid = Ssid ("ns-3-ssid");
  mac.SetType ("ns3::StaWifiMac",
               "Ssid", SsidValue (ssid),
               "ActiveProbing", BooleanValue (false));

  NetDeviceContainer staDevices;
  staDevices = wifi.Install (phy, mac, wifiStaNodes);

 
//ApWifiMac-Wi-Fi AP state machine, Handle association, dis-association and authentication, of STAs within an infrastructure BSS. 
 mac.SetType ("ns3::ApWifiMac",
               "Ssid", SsidValue (ssid));

  NetDeviceContainer apDevices;
  apDevices = wifi.Install (phy, mac, wifiApNode);

  MobilityHelper mobility;

  mobility.SetMobilityModel ("ns3::RandomWalk2dMobilityModel",
                             "Bounds", RectangleValue (Rectangle (-500, 50, -50, 500)));

  
  mobility.Install (wifiStaNodes);

  //mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
  //mobility.SetMobilityModel("ns3::RandomWalk2dMobilityModel");
  mobility.Install (wifiApNode);

  InternetStackHelper stack;
  stack.Install (p2pNodes.Get(1));
  stack.Install (wifiApNode);
  stack.Install (wifiStaNodes);

  Ipv4AddressHelper address;

  address.SetBase ("10.1.1.0", "255.255.255.0");
  Ipv4InterfaceContainer p2pInterfaces;
  p2pInterfaces = address.Assign (p2pDevices);

  address.SetBase ("10.1.3.0", "255.255.255.0");
  address.Assign (staDevices);
  address.Assign (apDevices);

  UdpEchoServerHelper echoServer (9);

  ApplicationContainer serverApps = echoServer.Install (p2pNodes.Get (1));
  serverApps.Start (Seconds (1.0));
  serverApps.Stop (Seconds (10.0));

  UdpEchoClientHelper echoClient (p2pInterfaces.GetAddress (1), 9);
  echoClient.SetAttribute ("MaxPackets", UintegerValue (1));
  echoClient.SetAttribute ("Interval", TimeValue (Seconds (1.0)));
  echoClient.SetAttribute ("PacketSize", UintegerValue (1024));

  ApplicationContainer clientApps = 
    echoClient.Install (wifiStaNodes.Get (nWifi-1));
  clientApps.Start (Seconds (2.0));
  clientApps.Stop (Seconds (10.0));

  Ipv4GlobalRoutingHelper::PopulateRoutingTables ();

  Simulator::Stop (Seconds (10.0));

  AsciiTraceHelper ascii;
  pointToPoint.EnableAsciiAll (ascii.CreateFileStream ("Tracefilewif.tr"));

  Simulator::Run ();
  Simulator::Destroy ();
  return 0;
}
