#! /bin/bash

run_2d_tests ()
{
  echo "Running 2d test set: "
  echo "Ready the program: "
  cd ..
  make 2dt
  cd -
  echo ""

  echo "Running tests: "
  for ((n = 0;;n++))
  do
	if [ -f "testsuite/2d/t$n.sh" ]
	then
	  # run the 'nth' test
	  ./testsuite/2d/t$n.sh > /dev/null

	  if diff -q output.obj testsuite/2d/r$n.obj
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
}

# test type input
TYPE=$1

# only 2 valid types -- 2d and 3d
if [ "$TYPE" == "" ]; then 
  echo "Incorrect usuage. "
  echo "./testrunner.sh <type> "
  echo "    where <type> one of "
  echo "        2d  -- run 2d test set "
  echo "        3d  -- run 3d test set "
  echo "        all -- run all test sets "
  exit
fi

if [ "$TYPE" == "2d" ]; then
  run_2d_tests
fi
