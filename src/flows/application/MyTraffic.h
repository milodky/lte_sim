/*
 * MyTraffic.h
 *
 *  Created on: Feb 25, 2013
 *      Author: Tim
 */

#ifndef MYTRAFFIC_H_
#define MYTRAFFIC_H_

#include "Application.h"

class MyTraffic: public Application {

public:
	MyTraffic();
	virtual ~MyTraffic();

	virtual void DoStart (void);
	virtual void DoStop (void);

    void
    ScheduleTransmit (double time);
    void
    Send (void);

    void
    SetSize(int size);
    void
    SetSBitRate(double bitrate);
    int
    GetSize (void) const;
    void
    SetInterval(double interval);
    double
    GetInterval (void);



    int on_period_num;

    unsigned int total_file_size;
    double total_transmission_time;
	double bit_rate; //in KBps

private:

	double m_interval;
	int m_size;
	bool m_stateON;
	double off_period_start;
	double m_startState;
	double m_stateDuration;
	double m_endState;




};

#endif /* MYTRAFFIC_H_ */
