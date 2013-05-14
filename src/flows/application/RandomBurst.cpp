/*
 * RandomBurst.cpp
 *
 *Created on: Feb 25, 2013
 *Author: Tim
 */

#include "RandomBurst.h"
#include <cstdlib>
#include "../../componentManagers/NetworkManager.h"
#include "../radio-bearer.h"
#include <math.h>

RandomBurst::RandomBurst() {
	// TODO Auto-generated constructor stub
	SetApplicationType(Application::APPLICATION_TYPE_RANDOMBURST);
	m_size = 0;
	m_interval = 0;
	m_stateDuration = 0;
}

RandomBurst::~RandomBurst() {
	// TODO Auto-generated destructor stub
	Destroy();

}

void RandomBurst::DoStart(void) {
	Simulator::Init()->Schedule(0.0, &RandomBurst::Send, this);
}

void RandomBurst::DoStop(void) {
}

void RandomBurst::ScheduleTransmit(double time) {
	if ((Simulator::Init()->Now() + time) < GetStopTime()) {
		Simulator::Init()->Schedule(time, &RandomBurst::Send, this);
	}
}

void RandomBurst::Send(void) {
// we need to transmit, right? Yes!

	/* get the randomly generated file size */
	int PacketSize = GetSize();
	/* create a packet */
	Packet *packet = new Packet();
	int uid = Simulator::Init()->GetUID();
	packet->SetID(uid);
	packet->SetTimeStamp(Simulator::Init()->Now());
	packet->SetSize(PacketSize);
	PacketTAGs *tags = new PacketTAGs();
	tags->SetApplicationType(PacketTAGs::APPLICATION_TYPE_RANDOMBURST);
	tags->SetApplicationSize(packet->GetSize());
	packet->SetPacketTags(tags);
	UDPHeader *udp = new UDPHeader(GetClassifierParameters()->GetSourcePort(),
			GetClassifierParameters()->GetDestinationPort());
	packet->AddUDPHeader(udp);
	IPHeader *ip = new IPHeader(GetClassifierParameters()->GetSourceID(),
			GetClassifierParameters()->GetDestinationID());
	packet->AddIPHeader(ip);
	PDCPHeader *pdcp = new PDCPHeader();
	packet->AddPDCPHeader(pdcp);
#ifdef __DISPLAY__
	Trace(packet);
#endif
	/* enqueue this packet */
	GetRadioBearer()->Enqueue(packet);

	/* schedule the next transmission */
	m_stateDuration = GetInterval();

	ScheduleTransmit(m_stateDuration);

}
/* generate file size */
int RandomBurst::GetSize(void) const {
	double random = rand() % 10000;
	random = -m_size * log((1 - (double) random / 10000));
	/* 
	 * set the maximum file size to be 1GB
	 * in case that int variable overflows 
	 */
	if (random > 100000000)
		random = 100000000;
	return ((int) random);
}
/* set the average file size */
void RandomBurst::SetSize(int size) {
	m_size = size;
}
/* set the average session interval */
void RandomBurst::SetInterval(double interval) {
	m_interval = interval;
}
/* generate session interval */
double RandomBurst::GetInterval(void) {
	int tmp;
	double random = rand() % 10000;
	random = -m_interval * log(1 - ((double) random / 10000));
	tmp = (int) (random * 1000);
	random = ((double) tmp) / 1000;
	return random;
}
