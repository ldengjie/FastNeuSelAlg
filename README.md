# How to run a new data version ?

- modify `run/gen.sh`

`
    listPath="/dybfs/rec/P14A/minirec_GoodRun_v2"
    dataPath="/afs/ihep.ac.cn/users/l/lidj/largedata/FastNeuSel/P14A"
    logPath="/afs/ihep.ac.cn/users/l/lidj/largedata/FastNeuSel/P14A/log"
    scriptPath=$PWD/P14A
`
- create corresponding `data directory` `scriptDir` `logDir` ,this has been done by `run/gen.sh`

- check `TimeShift/*.txt` for this data version
> codes from XiaXin
> `/publicfs/dyb/user/xiax/workarea/TimeShiftAlg`


