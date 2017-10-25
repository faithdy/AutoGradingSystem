#단계별 학생 통과율을 확인하기 위한 쉘 스크립트
rm DeathTest.txt DeathReport.txt UnitTest.txt UnitReport.txt
echo DeathTest; find -name "DeathTest" | wc -l
find -name "DeathTest" >> DeathTest.txt
echo DeathReport; find -name "DeathReport.xml" | wc -l
find -name "DeathReport.xml" >> DeathReport.txt
echo UnitTest; find -name "UnitTest" | wc -l
find -name "UnitTest" >> UnitTest.txt
echo UnitReport; find -name "UnitReport.xml" | wc -l
find -name "UnitReport.xml" >> UnitReport.txt
