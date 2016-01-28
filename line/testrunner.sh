#! /bin/bash

echo "Ready the program: "
cd ..
make line
cd -
echo ""

echo "Running tests: "
for ((n = 0;;n++))
do
  if [ -f "testsuite/t$n.sh" ]
  then
	# run the 'nth' test
	./testsuite/t$n.sh > /dev/null

	if diff -q output.obj testsuite/r$n.obj
	then
	  echo "Test #$n passed."
	else
	  echo "Test #$n failed."
	fi 
  else
	break
  fi
done

echo "Ran $(($n)) test(s)"
