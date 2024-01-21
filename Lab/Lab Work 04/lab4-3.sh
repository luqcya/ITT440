#!/bin/bash

echo "Enter a number: "
read number

while [[ ! $number =~ ^[0-9]+$ ]]; do
    echo "Invalid input. Please enter a valid number: "
    read number
done

if [ $((number%2)) -eq 0 ]; then
    echo "The entered number $number is even"
else
    echo "The entered number $number is odd"
fi