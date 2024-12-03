package main

import (
	"bufio"
	"fmt"
	"math"
	"os"
	"sort"
	"strconv"
	"strings"
)

func main() {

	if len(os.Args) < 2 {
		panic("Missing input file argument")
	}

	inputFile := os.Args[1]

	file, err := os.Open(inputFile)

	if err != nil {
		panic("Error opening file")
	}

	defer file.Close()

	scanner := bufio.NewScanner(file)

	var list1 []int
	var list2 []int

	for scanner.Scan() {
		line := scanner.Text()
		vals := strings.Split(line, "   ")

		val1, err := strconv.Atoi(vals[0])

		if err != nil {
			panic("invalid number")
		}

		val2, err := strconv.Atoi(vals[1])
		if err != nil {
			panic("invalid number")
		}

		list1 = append(list1, val1)
		list2 = append(list2, val2)
	}

	sort.Ints(list1)
	sort.Ints(list2)

	res := 0

	for i := range list1 {
		res += (int(math.Abs(float64(list1[i] - list2[i]))))
	}

	fmt.Println("Difference between reports: ", res)

	mp := map[int]int{}

	for _, num := range list2 {
		mp[num]++
	}

	ans := 0

	for _, num := range list1 {

		ans += (num * mp[num])
	}

	fmt.Println("The similarity score is: ", ans)

}
