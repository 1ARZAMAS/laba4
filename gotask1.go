package main

import (
	"fmt"
	"math"
)

func f(x float64) float64 {
	return x*x - 3*math.Sin(x)
}

func df(x float64) float64 {
	return 2*x - 3*math.Cos(x)
}

func printTable(iteration int, leftEdge float64, rightEdge float64) {
	fmt.Printf("-----------------------------------\n")
	fmt.Printf("%2d|%10.3f%10.3f%10.3f\n", iteration, leftEdge, rightEdge, rightEdge-leftEdge)
}

func graphMethod(leftEdge float64, rightEdge float64) []float64 {
	roots := make([]float64, 0)
	step := 0.01
	x := leftEdge
	for x < rightEdge {
		y1 := f(x)
		y2 := f(x + step)
		if (y1 > 0 && y2 < 0) || (y1 < 0 && y2 > 0) {
			root := (x + x + step) / 2
			roots = append(roots, root)
		}
		x += step
	}
	return roots
}

func bisectionMethod(leftEdge float64, rightEdge float64, eps float64, root float64) float64 {
	iteration := 1
	middlePoint := 0.0
	if f(leftEdge)*f(rightEdge) < 0 {
		for math.Abs(rightEdge-leftEdge) > eps {
			middlePoint = (rightEdge + leftEdge) / 2
			printTable(iteration, leftEdge, rightEdge)
			if f(leftEdge)*f(middlePoint) < 0 {
				rightEdge = middlePoint
			} else {
				leftEdge = middlePoint
			}
			iteration++
		}
	}
	return middlePoint
}

func newtonMethod(root float64, eps float64) {
	iteration := 1
	for {
		root1 := root - f(root)/df(root)
		printTable(iteration, root1, root)
		if math.Abs(root1-root) < eps {
			break
		}
		root = root1
		iteration++
	}
}

func chordMethod(leftEdge float64, rightEdge float64, eps float64) float64 {
	iteration := 1
	for math.Abs(rightEdge-leftEdge) >= eps {
		leftEdge = leftEdge - (rightEdge-leftEdge)*f(leftEdge)/(f(rightEdge)-f(leftEdge))
		rightEdge = rightEdge - (leftEdge-rightEdge)*f(rightEdge)/(f(leftEdge)-f(rightEdge))
		printTable(iteration, leftEdge, rightEdge)
		iteration++
	}
	return rightEdge
}

func main() {
	leftEdge := -0.5
	rightEdge := 3.0
	roots := graphMethod(leftEdge, rightEdge)
	eps := 0.0001

	fmt.Println("Результаты методом половинного деления для первого корня:")
	root := roots[0]
	leftEdge = root - 1.0
	rightEdge = root + 1.0
	fmt.Printf("N\t a\t   b\t     b - a\n")
	bisectionMethod(leftEdge, rightEdge, eps, root)

	fmt.Println("\nРезультаты методом Ньютона для первого корня:")
	fmt.Printf("N\t x(n)\t x(n+1)\t x(n+1) - x(n)\n")
	newtonMethod(root, eps)

	fmt.Println("\nРезультаты методом хорд для первого корня:")
	fmt.Printf("N\t a\t   b\t     b - a\n")
	chordMethod(leftEdge, rightEdge, eps)

	fmt.Println("\nРезультаты методом половинного деления для второго корня:")
	root = roots[1]
	leftEdge = root - 1.0
	rightEdge = root + 1.0
	fmt.Printf("N\t a\t   b\t     b - a\n")
	bisectionMethod(leftEdge, rightEdge, eps, root)

	fmt.Println("\nРезультаты методом Ньютона для второго корня:")
	root = roots[1]
	fmt.Printf("N\t x(k)\t x(k+1)\t x(k+1) - x(k)\n")
	newtonMethod(root, eps)

	fmt.Println("\nРезультаты методом хорд для второго корня:")
	fmt.Printf("N\t a\t   b\t     b - a\n")
	chordMethod(leftEdge, rightEdge, eps)
}
