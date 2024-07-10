@echo OFF
cd %~dp0

set rawLensFileAdd= ./TestData/lens/
set rawCommFileAdd= ./TestData/comm/
set fileTagRaw=*.raw
set fileTagBmp=*.bmp

del ".\confidenceLists.txt"
del ".\20200618_516_100M_commonPhase\confidenceLists.txt"

del ".\imageLists.txt"
del ".\20200618_516_100M_commonPhase\imageLists.txt"

call ./20200618_516_100M_commonPhase/readfilename.bat %rawLensFileAdd% %fileTagRaw% confidenceList.txt confidenceLists.txt
move ./confidenceLists.txt ./20200618_516_100M_commonPhase/confidenceLists.txt
TofCalib.exe ./Config_ro516_3.conf


call ./20200618_516_100M_commonPhase/readfilename.bat %rawLensFileAdd% %fileTagBmp% imageList.txt imageLists.txt
move ./imageLists.txt ./20200618_516_100M_commonPhase/imageLists.txt


call ./20200618_516_100M_commonPhase/readfilename.bat %rawCommFileAdd% %fileTagRaw% phaseListsCommon.txt phaseListsCommon_1.txt
move ./phaseListsCommon_1.txt ./20200618_516_100M_commonPhase/phaseListsCommon_1.txt


TofCalib.exe ./Config_ro516_2.conf

pause