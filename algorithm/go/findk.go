package main

import (
	"fmt"
	"math/rand"
)

func partition(v []int, l, r int) int {
	val := v[r]
	i := l - 1
	for j := l; j < r; j++ {
		if v[j] <= val {
			i++
			v[i], v[j] = v[j], v[i]
		}
	}
	v[i+1], v[r] = v[r], v[i+1]
	return i + 1
}

func randomPartition(v []int, l, r int) int {
	i := rand.Int()%(r-l+1) + l
	v[i], v[r] = v[r], v[i]
	return partition(v, l, r)
}

func quickSelect(v []int, l int, r int, index int){
	ret := randomPartition(v, l, r)
	if ret == index {
		return
	} else if ret > index {
		quickSelect(v, l, ret-1, index)
	} else {
		quickSelect(v, ret+1, r, index)
	}
}

func findK(v []int, k int) {
	quickSelect(v, 0, len(v)-1, len(v)-k)
}

func main() {
	var v = []int{1, 9, 4, 2, 7, 11, 33}
	findK(v, 3)
	fmt.Println(v[len(v) - 3])
    fmt.Println(v)
}
