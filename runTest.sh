date > testResults.txt
echo "" >> testResults.txt
./build/test.exe >> testResults.txt
cat testResults.txt