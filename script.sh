#!/usr/bin/env bash
set -e

INPUT="./data/circles_alg.txt"
OUT="./results/results.csv"
PROG="./src/prog"

mkdir -p "$(dirname "$OUT")"
echo "rect,N,seed,Shat" > results/results.csv
for rect in narrow wide; do
  for N in $(seq 100 500 100000); do
    [ "$N" -gt 100000 ] && break
    val=$(./src/prog --rect "$rect" --N "$N" --seed 123456 < data/circles_alg.txt)
    printf "%s,%s,%s,%s\n" "$rect" "$N" 123456 "$val" >> results/results.csv
  done
done

