#!/bin/bash
#comments

#the 1st argument is the number of transmissions in one execution
NbSim=$1
#the 2nd argument is the number of executions
IterNUM=$2

#################################################
#sleep interval vector, and it can be modified
Interval=(0.25 0.5)
#average session interval vector, and it can be modified
AverSession=(3 5 7 9 11)

#################################################
nbBuildings=1           #Number of Buildings
Buildingtype=0          #Buidling Type
activeRatio=1           #Active Ratio of the femto cell, must be less than or equal to 1
radius=1                #radius of macro cell
nbUE=1                  #Number of UE in a macro cell
nbFemtoUE=2             #Number of UE in a femto cell
nbVoip=0                #Number of VOIP application
nbVideo=0               #Number of Video(or trace) application
nbBE=0                  #Number of Inffinite buffer application
nbCBR=0                 #Number of Constant bit rate application
nbRB=1                  #Number of Random burst application 
sched_type=1            #scheduling type
frame_struct=1          #frame struct
speed=3                 #speed, chosen from {0, 3, 30, 120}
accessPolicy=0          #Access policy
maxDelay=0.1            #Maximum Delay
videoBitRate=128        #Bit rate of the video application
fsize=2000000		#Average file size
IdleInterval=1          #Idle interval of the femto cell

###   All the above parameters can be modified ###
##################################################


##################################################
##### can comment the echos below to get a #######
#####           continuous output          #######
##################################################
for Sleep_Interval in ${Interval[@]};
do
	echo "sleep interval is ${Sleep_Interval}s"
	for AverSessionInterval in ${AverSession[@]};
	do
		echo "${nbFemtoUE} FemtoUEs, file size of each is ${fsize}s"
		# the iteration of executions
		for ((j = 0; j < $IterNUM; j+=1));
		do
                        ./LTE-Sim Randomburst \
                         $nbBuildings \
                         $Buildingtype \
                         $activeRatio \
                         $radius \
                         $nbUE \
                         $nbFemtoUE \
                         $nbVoip \
                         $nbVideo \
                         $nbBE \
                         $nbCBR \
                         $nbRB \
                         $sched_type \
                         $frame_struct \
                         $speed \
                         $accessPolicy \
                         $maxDelay \
                         $videoBitRate \
                         $fsize \
                         $NbSim \
                         $AverSessionInterval \
                         $IdleInterval \
                         $Sleep_Interval
		done
	done
done
