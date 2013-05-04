/*
 * MyScenario.h
 *
 *  Created on: Mar 13, 2013
 *      Author: Tim
 */

#ifndef MYSCENARIO_H_
#define MYSCENARIO_H_

#include "../channel/LteChannel.h"
#include "../core/spectrum/bandwidth-manager.h"
#include "../networkTopology/Cell.h"
#include "../core/eventScheduler/simulator.h"
#include "../flows/application/InfiniteBuffer.h"
#include "../flows/QoS/QoSParameters.h"
#include "../componentManagers/FrameManager.h"
#include "../componentManagers/FlowsManager.h"
#include "../device/ENodeB.h"
#include "../flows/application/MyTraffic.h"
#include "../device/IPClassifier/ClassifierParameters.h"


static void my_scenario(int file_size_miu, double time_miu, double simulation_end_time) {



	  // CREATE COMPONENT MANAGERS
	  Simulator *simulator = Simulator::Init();
	  FrameManager *frameManager = FrameManager::Init();
	  NetworkManager* networkManager = NetworkManager::Init();
	  FlowsManager* flowsManager = FlowsManager::Init ();


	  //Create CHANNELS
	  LteChannel *dlCh = new LteChannel ();
	  LteChannel *ulCh = new LteChannel ();


	  // CREATE SPECTRUM
	  BandwidthManager* spectrum = new BandwidthManager (5, 5, 0, 0);


	  // CREATE CELL
	  int idCell = 0;
	  int radius = 1; //km
	  int minDistance = 0.0035; //km
	  int posX = 0;
	  int posY = 0;
	  Cell* cell = networkManager->CreateCell (idCell, radius, minDistance, posX, posY);


	  //Create ENodeB
	  int idEnb = 1;
	  ENodeB* enb = networkManager->CreateEnodeb (idEnb, cell, posX, posY, dlCh, ulCh, spectrum);
	  enb->SetDLScheduler (ENodeB::DLScheduler_TYPE_PROPORTIONAL_FAIR);


	  //Create GW
	  Gateway *gw = networkManager->CreateGateway ();


	  //Create UE
	  int idUe = 2;
	  int posX_ue = 40; //m
	  int posY_ue = 0;  //m
	  int speed = 3;    //km/h
	  double speeDirection = 0;
	  UserEquipment* ue = networkManager->CreateUserEquipment (idUe, posX_ue, posY_ue, speed, speeDirection, cell, enb);

	  //Create an Application
	  QoSParameters *qos = new QoSParameters ();
	  int applicationID = 0;
	  int srcPort = 0;
	  int dstPort = 100;
	  double startTime = 0.1; //s
	  double stopTime = simulation_end_time;  //s
	  ClassifierParameters *cp = new ClassifierParameters (gw->GetIDNetworkNode(),
			  	  	  	  	  ue->GetIDNetworkNode(),
			   	  	  	  	  srcPort,
  	   	  	  	  	  	  	  dstPort,
  	   	  	  	  	  	  	  TransportProtocol::TRANSPORT_PROTOCOL_TYPE_UDP);

	  MyTraffic MyTrafficApplication[1];

	  MyTrafficApplication->SetSource (gw);
	  MyTrafficApplication->SetDestination (ue);
	  MyTrafficApplication->SetApplicationID (applicationID);
	  MyTrafficApplication->SetStartTime(startTime);
	  MyTrafficApplication->SetStopTime(stopTime);
	  MyTrafficApplication->SetInterval (time_miu);
	  MyTrafficApplication->SetSize (file_size_miu);

	//  MyTrafficApplication->SetSBitRate(bitrate);

	  MyTrafficApplication->SetClassifierParameters (cp);
	  MyTrafficApplication->SetQoSParameters (qos);

/*

	  Application* be = flowsManager->CreateApplication (applicationID,
							  gw, ue,
							  srcPort, dstPort, TransportProtocol::TRANSPORT_PROTOCOL_TYPE_UDP ,
							  Application::APPLICATION_TYPE_MYTRAFFIC,
							  qos,
							  startTime, stopTime);

*/
	  simulator->SetStop(simulation_end_time);
	  simulator->Run ();
	  double average_file_size = MyTrafficApplication->total_file_size / MyTrafficApplication->on_period_num;
/*
	  std::cout << "Total Packets sent is" << MyTrafficApplication->on_period_num
	  	  	  << "\nAverage file size is "
			  << average_file_size
			  << "B;\nAverage interval period is "
			  << MyTrafficApplication->total_transmission_time / MyTrafficApplication->on_period_num
			  << "ms\n";

*/
}





#endif /* MYSCENARIO_H_ */
