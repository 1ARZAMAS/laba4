package main

import (
	"fmt"
	"math/rand"
	"time"
)

// Алгоритм 1: всегда сотрудничает
func algorithm1(roundNumber int, selfChoices, enemyChoices []bool) bool {
	return true
}

// Алгоритм 2: всегда предает
func algorithm2(roundNumber int, selfChoices, enemyChoices []bool) bool {
	return false
}

// Алгоритм 3: предает, если противник предавал в предыдущем раунде, иначе сотрудничает
func algorithm3(roundNumber int, selfChoices, enemyChoices []bool) bool {
	if roundNumber == 0 {
		return true
	}
	return !enemyChoices[roundNumber-1]
}

func main() {
	rand.Seed(time.Now().UnixNano())

	// Генерация случайного количества раундов
	numRounds := rand.Intn(101) + 100

	// Инициализация счетчиков очков для каждого алгоритма
	score1, score2, score3 := 0, 0, 0

	// Массивы для хранения выборов каждого алгоритма
	choices1 := make([]bool, numRounds)
	choices2 := make([]bool, numRounds)
	choices3 := make([]bool, numRounds)

	for round := 0; round < numRounds; round++ {
		// Вызов алгоритмов для получения их выборов
		choice1 := algorithm1(round, choices1, choices2)
		choice2 := algorithm2(round, choices2, choices1)
		choice3 := algorithm3(round, choices3, choices2)

		// Обновление счетчиков очков
		if choice1 && choice2 {
			score1 += 24
			score2 += 24
		} else if choice1 && !choice2 {
			score2 += 20
		} else if !choice1 && choice2 {
			score1 += 20
		} else {
			score1 += 4
			score2 += 4
		}

		if choice1 && choice3 {
			score1 += 24
			score3 += 24
		} else if choice1 && !choice3 {
			score3 += 20
		} else if !choice1 && choice3 {
			score1 += 20
		} else {
			score1 += 4
			score3 += 4
		}

		if choice2 && choice3 {
			score2 += 24
			score3 += 24
		} else if choice2 && !choice3 {
			score3 += 20
		} else if !choice2 && choice3 {
			score2 += 20
		} else {
			score2 += 4
			score3 += 4
		}

		// Сохранение выборов для каждого алгоритма
		choices1[round] = choice1
		choices2[round] = choice2
		choices3[round] = choice3
	}

	// Вывод результатов
	fmt.Println("Количество раундов:", numRounds)
	fmt.Println("Всегда сотрудничаем:", score1)
	fmt.Println("Всегда предаем:", score2)
	fmt.Println("Око за око:", score3)
}
