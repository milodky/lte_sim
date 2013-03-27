/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2010,2011,2012 TELEMATICS LAB, Politecnico di Bari
 *
 * This file is part of LTE-Sim
 *
 * LTE-Sim is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation;
 * LTE-Sim is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with LTE-Sim; if not, see <http://www.gnu.org/licenses/>.
 *
 * Author: Giuseppe Piro <g.piro@poliba.it>
 */

#include "dl-fls-packet-scheduler.h"
#include "../mac-entity.h"
#include "../../packet/Packet.h"
#include "../../packet/packet-burst.h"
#include "../../../device/NetworkNode.h"
#include "../../../flows/radio-bearer.h"
#include "../../../protocolStack/rrc/rrc-entity.h"
#include "../../../flows/application/Application.h"
#include "../../../device/ENodeB.h"
#include "../../../protocolStack/mac/AMCModule.h"
#include "../../../phy/lte-phy.h"
#include "../../../core/spectrum/bandwidth-manager.h"
#include "../../../flows/QoS/QoSForFLS.h"
#include "../../../flows/MacQueue.h"

DL_FLS_PacketScheduler::DL_FLS_PacketScheduler()
{}

DL_FLS_PacketScheduler::~DL_FLS_PacketScheduler()
{}

void
DL_FLS_PacketScheduler::SetLowerLevelSchedulerType (LowerLevelSchedulerType type)
{}

DL_FLS_PacketScheduler::LowerLevelSchedulerType
DL_FLS_PacketScheduler::GetLowerLevelSchedulerType (void) const
{
  return m_lowerLevelSchedulerType;
}

void
DL_FLS_PacketScheduler::DoSchedule ()
{}

void
DL_FLS_PacketScheduler::DoStopSchedule (void)
{}

double
DL_FLS_PacketScheduler::ComputeSchedulingMetric (RadioBearer *bearer, double spectralEfficiency, int subChannel)
{}

void
DL_FLS_PacketScheduler::RunControlLaw ()
{}

void
DL_FLS_PacketScheduler::Select_RT_FlowsToSchedule ()
{}

void
DL_FLS_PacketScheduler::Select_NRT_FlowsToSchedule ()
{}
