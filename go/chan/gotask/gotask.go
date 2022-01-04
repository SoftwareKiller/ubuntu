package gotask

import (
	"fmt"
	"runtime"
	"sync"
)

func GoTask() {
	runtime.GOMAXPROCS(1)
	var wg sync.WaitGroup
	wg.Add(2)

	go func() {
		defer wg.Done()
		for i := 0; i < 3; i++ {
			for c := 'a'; c < 'a'+26; c++ {
				fmt.Printf("%c ", c)
			}
		}
		fmt.Println()
	}()

	go func() {
		defer wg.Done()
		for i := 0; i < 3; i++ {
			for c := 'A'; c < 'A'+26; c++ {
				fmt.Printf("%c ", c)
			}
		}
		fmt.Println()
	}()

	wg.Wait()
}
