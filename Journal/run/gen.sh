#!/bin/bash
if [ "${useFILE1:+1}"="1" ]
then
    unset useFILE1
fi
sitePostfix="_AS_TimeAlign"
NuWaConfigScript="/afs/ihep.ac.cn/users/l/lidj/.laf_opt"
listPath="/dybfs/rec/P12E/GoodRun/rec"
dataPath="/afs/ihep.ac.cn/users/l/lidj/largedata/FastNeuSel"
logPath="/afs/ihep.ac.cn/users/l/lidj/largedata/FastNeuSel/log"
recTree="AdSimple" # AdSimple or AdScaled
outputFile2Name="runRUNNUM_Fast_neutron.root"
#useFILE1="TOutputSvc.Output" #if not use FILE1 ,just comment out this line
outputFile1Name="RUNNUM_hists.root"
inputSvc="ReconInputSvc" # MiniReconInputSvc or ReconInputSvc
useRPC="FALSE" #FALSE or TRUE
targetdir=$PWD
scriptPath=$PWD

for site in EH1 EH2 EH3
do
    siteFullName=$site$sitePostfix
    echo  "$dataPath/$siteFullName"
    if [ -d "$dataPath/$siteFullName" ];then
        echo "dataDir : $dataPath/$siteFullName/ exits !!!"
    else
        mkdir -p "$dataPath/$siteFullName/"
        echo "mkdir dataDir : $dataPath/$siteFullName/"
    fi
    if [ -d "$logPath/$siteFullName/" ];then
        echo "logDir : $logPath/$siteFullName/ exits !!!"
    else
        mkdir -p "$logPath/$siteFullName/"
        echo "mkdir logDir : $logPath/$siteFullName/"
    fi
    if [ -d "$scriptPath/$siteFullName/" ];then
        echo "scriptDir : $scriptPath/$siteFullName/ exits !!!"
    else
        mkdir -p "$scriptPath/$siteFullName/"
        echo "mkdir scriptDir : $scriptPath/$siteFullName/"
    fi
	firstlist=1
	pushd $listPath/$site/
	for filename in `ls *.list `;
	do
		#  runNum=${filename:3:5}
		temprunNum1=${filename:3:5}
		if test "${temprunNum1//[0-9]/}" #is not int
		then
			temprunNum2=${filename:0:5}
			if test "${temprunNum2//[0-9]/}" #is not int
			then
				echo -e "\e[31;44;1m ! bad run number : ${filename}==>${temprunNum1} or ${temprunNum2} ,skip this list !\e[0m"
				continue
			else
				runNum=${filename:0:5}
			fi
		else
			runNum=${filename:3:5}
		fi

		echo $filename, $runNum
			sed -e "s/RUNNUM/${runNum}/g"  \
				-e "s#INPUTFILELISTPATH#${listPath}#g"  \
				-e "s#FILENAME#${filename}#g"  \
				-e "s#INPUTSVC#${inputSvc}#g"  \
				-e "s#^//TOutputSvc.Output#${useFILE1:=//TOutputSvc.Output}#g"  \
				-e "s#FILE1NAME#${outputFile1Name/RUNNUM/$runNum}#g"  \
				-e "s#FILE2NAME#${outputFile2Name/RUNNUM/$runNum}#g"  \
				-e "s#USERPC#${useRPC}#g"  \
				-e "s#RECTREE#${recTree}#g"  \
				-e "s#OUTPUTFILEPATH#${dataPath}#g"  \
                -e "s/LISTSITE/$site/g" \
				-e "s/SITE/$siteFullName/g"  $targetdir/config_temp.txt > $scriptPath/$siteFullName/config_run${runNum}.txt

			sed -e "s/RUNNUM/${runNum}/g" \
				-e "s#TARGETDIR#$targetdir#g"  \
				-e "s#LOGPATH#$logPath#g"  \
				-e "s#NuWaConfigScript#${NuWaConfigScript}#g"  \
				-e "s/SITE/$siteFullName/g"   $targetdir/job_temp.csh > $scriptPath/$siteFullName/job_${runNum}.csh
		if [ $firstlist -eq 1 ];then
			if [ -f "$scriptPath/$siteFullName/submit.sh" ];then
				echo "submit.sh already exists,delete it,create a new one"
				rm -rf "$scriptPath/$siteFullName/submit.sh"
			else
				echo "submit.sh not exists,create one"
			fi
		fi
		echo "qsub -q dyb64q job_${runNum}.csh -o $logPath/$siteFullName/ -e $logPath/$siteFullName/" >> $scriptPath/$siteFullName/submit.sh
		let "firstlist += 1"
	done
	popd
done
exit
