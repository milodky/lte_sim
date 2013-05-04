/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2010,2011,2012 TELEMATICS LAB, Politecnico di Bari
 *
 * This file is part of LTE-Sim
 *
 * LTE-Sim is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation;
 *
 * LTE-Sim is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with LTE-Sim; if not, see <http://www.gnu.org/licenses/>.
 *
 * Author: Francesco Capozzi <f.capozzi@poliba.it>
 */


#include "power-based-ho-manager.h"
#include "../../../device/NetworkNode.h"
#include "../../../device/UserEquipment.h"
#include "../../../device/ENodeB.h"
#include "../../../device/HeNodeB.h"
#include "../../../componentManagers/NetworkManager.h"
#include "../../../core/spectrum/bandwidth-manager.h"
#include "../../../phy/lte-phy.h"
#include "../../../utility/ComputePathLoss.h"

PowerBasedHoManager::PowerBasedHoManager()
{
  m_target = NULL;
}

PowerBasedHoManager::~PowerBasedHoManager()
{
  m_target = NULL;
}

bool
PowerBasedHoManager::CheckHandoverNeed (UserEquipment* ue)
{
	if (ue->GetNodeState() == NetworkNode::STATE_DETACHED){
		return false;
	}
  NetworkNode *targetNode = ue->GetTargetNode ();

  double TXpower = 10 * log10 (
		  pow (10., (targetNode->GetPhy()->GetTxPower() - 30)/10)
		  /
		  targetNode->GetPhy()->GetBandwidthManager()->GetDlSubChannels().size () );
  double pathLoss = ComputePathLossForInterference(targetNode, ue);

  double targetRXpower = TXpower - pathLoss;

	
	if (targetNode->GetNodeState() == NetworkNode::STATE_SLEEP) {
		targetRXpower = -1 * std::numeric_limits<double>::max();
//		std::cout << "targetRXpower(" << ue->GetIDNetworkNode()<< ")"<< targetRXpower << std::endl;
	}

  double RXpower;


  std::vector<ENodeB*> *listOfNodes = NetworkManager::Init ()->GetENodeBContainer ();
  std::vector<ENodeB*>::iterator it;
  for (it = listOfNodes->begin (); it != listOfNodes->end (); it++)
    {
	    
	  if ((*it)->GetIDNetworkNode () != targetNode->GetIDNetworkNode () )
	    {

	      NetworkNode *probableNewTargetNode = (*it);

	      TXpower = 10 * log10 (
				  pow (10., (probableNewTargetNode->GetPhy()->GetTxPower() - 30)/10)
				  /
				  probableNewTargetNode->GetPhy()->GetBandwidthManager()->GetDlSubChannels().size () );
	      pathLoss = ComputePathLossForInterference(probableNewTargetNode, ue);

	      RXpower = TXpower - pathLoss;
//		    std::cout << "RXpower1(" << ue->GetIDNetworkNode()<< ")"<< RXpower << std::endl;

	      if (RXpower > targetRXpower)
	        {
	    	  if (NetworkManager::Init()->CheckHandoverPermissions(probableNewTargetNode,ue))
	    	  {
		    	  targetRXpower = RXpower;
			      targetNode = probableNewTargetNode;
	    	  }
	        }
	    }
    }
	
//	if (ue->GetTargetNode()->GetNodeState() == NetworkNode::STATE_SLEEP) {
//		m_target = targetNode;
//		return true;
//	}

	
  std::vector<HeNodeB*> *listOfNodes2 = NetworkManager::Init ()->GetHomeENodeBContainer();
  std::vector<HeNodeB*>::iterator it2;
  for (it2 = listOfNodes2->begin (); it2 != listOfNodes2->end (); it2++)
    {
	    if ((*it2)->GetNodeState() == NetworkNode::STATE_SLEEP){
		    continue;
	    }
//	    std::cout<< "Nodestate " << (*it2)->GetNodeState() << std::endl;

	  if ((*it2)->GetIDNetworkNode () != targetNode->GetIDNetworkNode () )
	    {

	      NetworkNode *probableNewTargetNode = (*it2);

	      TXpower =   10 * log10 (
				  pow (10., (probableNewTargetNode->GetPhy()->GetTxPower() - 30)/10)
				  /
				  probableNewTargetNode->GetPhy()->GetBandwidthManager()->GetDlSubChannels().size () );

	      pathLoss = ComputePathLossForInterference(probableNewTargetNode, ue);

	      RXpower = TXpower - pathLoss;
//		    std::cout << "RXpower2(" << ue->GetIDNetworkNode()<< ")"<< RXpower << std::endl;

	      if (RXpower > targetRXpower)
	        {
	    	  if (NetworkManager::Init()->CheckHandoverPermissions(probableNewTargetNode,ue))
	    	  {
		    	  targetRXpower = RXpower;
			      targetNode = probableNewTargetNode;
	    	  }
	        }
	    }
    }

  if (ue->GetTargetNode ()->GetIDNetworkNode () != targetNode->GetIDNetworkNode ())
    {
	  m_target = targetNode;
//	    std::cout << "CheckHandoverNeed:from " << ue->GetIDNetworkNode()<<":to "<<targetNode->GetIDNetworkNode() << std::endl;

	  return true;
    }
  else
    {
	  return false;
    }
}
