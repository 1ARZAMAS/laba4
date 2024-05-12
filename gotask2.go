package main

import (
	"fmt"
	"math/rand"
	"sort"
	"time"
)

func main() {
	// 1. Определение и инициализация массива случайными числами
	rand.Seed(time.Now().UnixNano())
	n := 10
	randNums := make([]int, n)
	for i := range randNums {
		randNums[i] = rand.Intn(300-150+1) + 150
	}

	// 2. Поиск и вывод самой длинной последовательности в убывающем порядке
	var longest []int
	currentLength := 1
	maxLength := 0
	for i := 1; i < n; i++ {
		if randNums[i] > randNums[i-1] {
			currentLength++
		} else {
			if currentLength > maxLength {
				maxLength = currentLength
				longest = randNums[i-currentLength : i]
			}
			currentLength = 1
		}
	}
	if currentLength > maxLength {
		longest = randNums[n-currentLength:]
	}
	sort.Sort(sort.Reverse(sort.IntSlice(longest)))
	fmt.Println("Самая длинная последовательность в убывающем порядке:")
	fmt.Println(longest)

	// 3. Определение и инициализация нового массива меньше среднеарифметического
	sum := 0
	for _, num := range randNums {
		sum += num
	}
	avg := float64(sum) / float64(n)

	var newArr []int
	for _, num := range randNums {
		if float64(num) < avg {
			newArr = append(newArr, num)
		}
	}
	fmt.Println("Новый массив, состоящий из чисел меньше среднеарифметического:")
	fmt.Println(newArr)

	// 4. Модификация массива случайных символов
	symbolArr := make([]byte, n)
	for i := range symbolArr {
		symbolArr[i] = byte('A' + rand.Intn(26))
	}
	fmt.Println("Изначальный массив символов:")
	fmt.Println(symbolArr)
	rand.Shuffle(len(symbolArr), func(i, j int) {
		symbolArr[i], symbolArr[j] = symbolArr[j], symbolArr[i]
	})
	fmt.Println("Модифицированный массив символов:")
	fmt.Println(symbolArr)

	// 5. Определение и инициализация нового массива случайных чисел, его сортировка и подсчет повторяющихся цифр
	n = 20
	newNumbersArr := make([]int, n)
	for i := range newNumbersArr {
		newNumbersArr[i] = rand.Intn(900-100+1) + 100
	}
	sort.Sort(sort.Reverse(sort.IntSlice(newNumbersArr)))
	fmt.Println("Новый массив случайных чисел в порядке убывания:")
	fmt.Println(newNumbersArr)

	digitCount := make([]int, 10)
	for _, num := range newNumbersArr {
		for num > 0 {
			digitCount[num%10]++
			num /= 10
		}
	}
	fmt.Println("Количество повторяющихся цифр в новом массиве:")
	for i, count := range digitCount {
		fmt.Printf("%d: %d\t", i, count)
	}
	fmt.Println()
}
