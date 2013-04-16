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

MyTraffic::MyTraffic() {
	// TODO Auto-generated constructor stub
	SetApplicationType(Application::APPLICATION_TYPE_MYTRAFFIC);
	bit_rate = 2000;
	m_stateON = false;
	off_period_start = 0;
	total_file_size = 0;
	total_transmission_time = 0;
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

	if (m_stateON == false) {

		// we need to transmit, right? Yes!
		m_stateON = true;
		int PacketSize = GetSize();
		total_file_size += PacketSize;
		on_period_num++;

/*
		std::cout << "\nStart to transmit -- @ " << Simulator::Init()->Now()
				<< " ms\n" << std::endl;

		std::cout << "File size is " << PacketSize << ", Bit rate is "
				<< bit_rate << std::endl;
*/
		off_period_start = PacketSize / bit_rate;
		do {
			m_stateDuration = GetInterval();
		} while (m_stateDuration < off_period_start);

		total_transmission_time += m_stateDuration;

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

		//Trace(packet);

		GetRadioBearer()->Enqueue(packet);
		ScheduleTransmit(off_period_start);

	} else {
		/*
		 * generating the next packet
		 */
		//std::cout << "\nOff period -- @ " << Simulator::Init()->Now() << "ms\n";
		m_stateON = false;
		/*
		if (m_stateDuration > 6.9) {
			m_stateDuration = 6.9;
		}
		*/
		//this is the next transmission
		ScheduleTransmit(m_stateDuration - off_period_start);
	}
}

int MyTraffic::GetSize(void) const {
	double random = rand() % 10000;
	random = -m_size * log(1 - ((double) random / 10000));
	return ((int) random);
}

void MyTraffic::SetSize(int size) {
	m_size = size;
}
void MyTraffic::SetSBitRate(double bitrate) {
	bit_rate = bitrate;
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
