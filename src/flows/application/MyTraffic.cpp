/*
 * MyTraffic.cpp
 *
 *Created on: Feb 25, 2013
 *Author: Tim
 */

#include "MyTraffic.h"
#include <cstdlib>
#include "../../componentManagers/NetworkManager.h"
#include "../radio-bearer.h"
#include <math.h>

#define MTU 1490

MyTraffic::MyTraffic() {
	// TODO Auto-generated constructor stub
	SetApplicationType(Application::APPLICATION_TYPE_MYTRAFFIC);
	m_stateON = false;
	off_period_start = 0;
	total_file_size = 0;
	off_transmission_time = 0;
	on_period_num = 0;
}

MyTraffic::~MyTraffic() {
	// TODO Auto-generated destructor stub
	Destroy();

}

void MyTraffic::DoStart(void) {
	Simulator::Init()->Schedule(0.0, &MyTraffic::Send, this);
}

void MyTraffic::DoStop(void) {
}

void MyTraffic::ScheduleTransmit(double time) {
	if ((Simulator::Init()->Now() + time) < GetStopTime()) {
		Simulator::Init()->Schedule(time, &MyTraffic::Send, this);
	}
}

void MyTraffic::Send(void) {
	int tmp;
//CREATE A NEW PACKET (ADDING UDP, IP and PDCP HEADERS)

// we need to transmit, right? Yes!
	m_stateON = true;
	int PacketSize = GetSize();
	total_file_size += PacketSize;
	on_period_num++;

	int PacketNum = PacketSize / MTU;
	int ReminderSize = PacketSize % MTU;
/*
	for (int i = 0; i < PacketNum; i++) {
		Packet *packet = new Packet();

		int uid = Simulator::Init()->GetUID();

		packet->SetID(uid);

		packet->SetTimeStamp(Simulator::Init()->Now());

		packet->SetSize(MTU);

		PacketTAGs *tags = new PacketTAGs();

		tags->SetApplicationType(PacketTAGs::APPLICATION_TYPE_MYTRAFFIC);

		tags->SetApplicationSize(packet->GetSize());

		packet->SetPacketTags(tags);

		UDPHeader *udp = new UDPHeader(
				GetClassifierParameters()->GetSourcePort(),
				GetClassifierParameters()->GetDestinationPort());

		packet->AddUDPHeader(udp);

		IPHeader *ip = new IPHeader(GetClassifierParameters()->GetSourceID(),
				GetClassifierParameters()->GetDestinationID());

		packet->AddIPHeader(ip);

		PDCPHeader *pdcp = new PDCPHeader();

		packet->AddPDCPHeader(pdcp);

		Trace(packet);

		GetRadioBearer()->Enqueue(packet);
	}
*/
	if (1) {
		Packet *packet = new Packet();

		int uid = Simulator::Init()->GetUID();

		packet->SetID(uid);

		packet->SetTimeStamp(Simulator::Init()->Now());

		packet->SetSize(PacketSize);

		PacketTAGs *tags = new PacketTAGs();

		tags->SetApplicationType(PacketTAGs::APPLICATION_TYPE_MYTRAFFIC);

		tags->SetApplicationSize(packet->GetSize());

		packet->SetPacketTags(tags);

		UDPHeader *udp = new UDPHeader(
				GetClassifierParameters()->GetSourcePort(),
				GetClassifierParameters()->GetDestinationPort());

		packet->AddUDPHeader(udp);

		IPHeader *ip = new IPHeader(GetClassifierParameters()->GetSourceID(),
				GetClassifierParameters()->GetDestinationID());

		packet->AddIPHeader(ip);

		PDCPHeader *pdcp = new PDCPHeader();

		packet->AddPDCPHeader(pdcp);

	//	Trace(packet);

		GetRadioBearer()->Enqueue(packet);
	}

	m_stateON = false;
	m_stateDuration = GetInterval();

	off_transmission_time += m_stateDuration;

	//std::cout << Simulator::Init()->Now() << std::endl;
//	std::cout << "next transmission is "
	//		<< Simulator::Init()->Now() + m_stateDuration << std::endl;
	ScheduleTransmit(m_stateDuration);

}

int MyTraffic::GetSize(void) const {
	double random = rand() % 10000;
	random = -m_size * log((1 - (double) random / 10000));
	return ((int) random);
}

void MyTraffic::SetSize(int size) {
	m_size = size;
}

void MyTraffic::SetInterval(double interval) {
	m_interval = interval;
}

double MyTraffic::GetInterval(void) {

	int tmp;
	double random = rand() % 10000;
	random = -m_interval * log(1 - ((double) random / 10000));
	tmp = (int) (random * 1000);
	random = ((double) tmp) / 1000;
	return random;
}
