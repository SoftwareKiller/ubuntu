package msgqueue

import (
	"fmt"
	"sync"
	"time"
)

var qu chan int
var data int
var wg sync.WaitGroup
var mtx sync.Mutex
var maxval int

func init() {
	data = 0
	qu = make(chan int, 10)
	maxval = 1000000
}

func write() {
	defer wg.Done()
	for {
		mtx.Lock()
		data++
		val := data
		mtx.Unlock()
		// data 在锁外，可能在加锁范围已经修改
		// qu <- data
		qu <- val
		// time.Sleep(100 * time.Millisecond)
		if data >= maxval {
			return
		}
	}
}

func read() {
	defer wg.Done()
	for {
		msg := <-qu
		fmt.Println("data:", msg)
		if msg >= maxval {
			close(qu)
			return
		}
	}
}

func Start() {
	start := time.Now()
	wg.Add(20)

	for i := 0; i < 19; i++ {
		go write()
	}

	go read()

	wg.Wait()

	fmt.Println("Use time:", time.Since(start))
}
