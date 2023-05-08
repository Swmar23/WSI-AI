#!/bin/bash

for i in {1..100}
do
  # awk -v var="$i" 'NR==var {print; exit}' test_instances.txt | ./solver --testMDLC >> "resultsMDLC.txt"
  # awk -v var="$i" 'NR==var {print; exit}' test_instances.txt | ./solver --testMAXMDID >> "resultsMAXMDID.txt"
  awk -v var="$i" 'NR==var {print; exit}' test_instances.txt | ./solver --testMD >> "resultsMD.txt"
  echo $i
  sleep 1
done