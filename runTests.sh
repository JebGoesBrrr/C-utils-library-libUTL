date > testResults.txt
echo "" >> testResults.txt
./build/utl_tests.exe >> testResults.txt
cat testResults.txt