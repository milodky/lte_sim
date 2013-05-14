/*
 * RandomBurst.h
 *
 *  Created on: Feb 25, 2013
 *      Author: Tim
 */

#ifndef RANDOMBURST_H_
#define RANDOMBURST_H_

#include "Application.h"

class RandomBurst: public Application {

public:
	RandomBurst();
	virtual ~RandomBurst();

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





private:

	double m_interval;
	int m_size;
	double m_stateDuration;




};

#endif /* RandomBurst_H_ */
